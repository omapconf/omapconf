/*
 * sci.c
 *
 * Statistic Collector Instrumentation Library
 * - Statistic Collector module specific definitions
 * - Device specific configurations
 *
 * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/
#include "sci.h"
#include "sci_common.h"
#ifdef _STM_Logging
#include "StmSupport.h"
#include <stdio.h>
#endif
#include <stdio.h>
/*
 *
 * Public external function prototypes
 *
 */

#ifndef _DOXYGEN_IGNORE
extern void * cTools_memAlloc(size_t sizeInBytes);
extern void cTools_memFree(void * ptr);
extern void * cTools_memMap(unsigned int phyAddr, unsigned int mapSizeInBytes);
extern void cTools_memUnMap(void * vAddr, unsigned int mapSizeInBytes);
extern int cTools_mutexInit(uint32_t mutexId);
extern int cTools_mutexTrylock(uint32_t mutexId);
extern int cTools_mutexUnlock(uint32_t mutexId);
extern int mem_read(unsigned int reg_addr, unsigned int *reg_val);
#endif

/*
 *
 * Private decarations
 *
 */


enum sci_state {SCI_MOD_DISABLED, SCI_MOD_ENABLED };

struct sci_usecase_key_t {
    int module_index;
    int num_counters;
    int counter_index[2];
    int usecase;                         /* Either sci_sdram_usecase or sci_mstr_usecase */
    char * pmeta_data_buf;
    int meta_data_byte_cnt;
    struct sci_usecase_key_t * next;
    struct sci_usecase_key_t * prev;
};

struct sci_handle_t {
    enum sci_state mod_state;
    sci_callback psci_callback;
    uint32_t sdram_msg_rate;
    uint32_t mstr_msg_rate;
    bool trigger_enable;
    struct sci_usecase_key_t * pusecase_head;     /* use case link list pointer */
    enum sci_mode mode;
#ifdef _STM_Logging
    bool stm_log_enable;
    STMHandle *  pstm_handle;
    int32_t stm_ch;
    uint32_t data_options;
#endif
};

struct usecase_parms {
    int num_cntr_req;                      /* Number of SC counters required */
    uint32_t reqevt;
    uint32_t rspevt;
    int port_type;
    uint32_t op_sel[2];
    uint32_t evt_info_sel[2];
};

enum sci_err get_meta_data(psci_handle const phandle, struct sci_usecase_key_t * puc_key,
                           const char * probe_name,
                           const char * trans_type,
                           const char * master_or_slave_name,
                           uint32_t mask );
enum sci_err send_meta_data (psci_handle const phandle);
enum sci_err get_usecase_params( int usecase, struct usecase_parms * pusecase_parms);
enum sci_err get_cntr(enum sci_module_type mod_type, int probe_id, int usecase,
                      int num_filters, int num_cntr_req,
                      int * mod_index,  int * cntr_assigned);
void * get_cntr_addr( int mod, int cnt_index);
void * get_filter_addr ( int mod, int cnt_index, int filter_index);
void put_uckey(psci_handle const phandle, struct sci_usecase_key_t * puc_key);
int sys_to_phys_addr(int sys_addr);

/*
 * sci_open
 *
 */
enum sci_err sci_open(psci_handle * const pphandle, struct sci_config * const pcnfg)
{
    int i;
    int tmp_cnt = 0;
    uint32_t mode = 0; /* Default is SCI_MODE_STM */
    enum sci_err ret_val = SCI_SUCCESS;

    /* If pCPT_Handle is not NULL then return error */
    if (NULL != *pphandle)
        ret_val =   SCI_ERR_INVALID_HANDLE;


    /* If config parameters are provided test they are valid */
    if ((SCI_SUCCESS == ret_val) && ( NULL != pcnfg )){
        if ( 0 == pcnfg->sdram_msg_rate )
            ret_val =  SCI_ERR_INVALID_PARM;
        if ( 0 == pcnfg->mstr_msg_rate )
            ret_val =  SCI_ERR_INVALID_PARM;
    }

    if (SCI_SUCCESS == ret_val){
        /* Attempt to map the CP Tracer base address of each SC Module*/
        for ( i=0; i < mod_cnt; i++ ) {
            mod_map[i]->vbase_addr = (uint32_t *)cTools_memMap(mod_map[i]->base_addr,
                                                              mod_map[i]->mod_size);
            tmp_cnt++;
        }
        if ( 0 == tmp_cnt )
            ret_val =  SCI_ERR_MAPPING;
    }

   /* call sci_get_version to check compatibility with the hw module*/
   if ( SCI_SUCCESS == ret_val) {
        uint32_t plib_major_ver;
        uint32_t plib_minor_ver;
        uint32_t plib_func_id;
        uint32_t pmod_func_id;

        ret_val = sci_get_version(*pphandle, &plib_major_ver, &plib_minor_ver,
                                  &plib_func_id, &pmod_func_id );
   }

    /* Malloc the handle */
    if (SCI_SUCCESS == ret_val){
        * pphandle = (struct sci_handle_t *)cTools_memAlloc(sizeof(struct sci_handle_t));
        if ( NULL == * pphandle ) {
            ret_val = SCI_ERR_MEM_ALLOC;
        }
        else {
            /* Intialize the handle */
            (*pphandle)->mod_state = SCI_MOD_DISABLED;
            (*pphandle)->pusecase_head = NULL;
            if (NULL != pcnfg){
                (*pphandle)->psci_callback = pcnfg->errhandler;
                (*pphandle)->sdram_msg_rate = pcnfg->sdram_msg_rate;
                (*pphandle)->mstr_msg_rate = pcnfg->mstr_msg_rate;
                (*pphandle)->trigger_enable = pcnfg->trigger_enable;
                (*pphandle)->mode = pcnfg->mode;
#ifdef _STM_Logging
                (*pphandle)->stm_log_enable = pcnfg->stm_log_enable;
                (*pphandle)->pstm_handle = pcnfg->pstm_handle;
                (*pphandle)->stm_ch = pcnfg->stm_ch;
                (*pphandle)->data_options = pcnfg->data_options;
#endif
            }
            else {
                (*pphandle)->psci_callback = NULL;
                (*pphandle)->sdram_msg_rate = (uint32_t)-1;
                (*pphandle)->mstr_msg_rate = (uint32_t)-1;
                (*pphandle)->trigger_enable = false;
                (*pphandle)->mode = SCI_MODE_STM;
#ifdef _STM_Logging
                (*pphandle)->stm_log_enable = false;
                (*pphandle)->pstm_handle = NULL;
                (*pphandle)->stm_ch = 0;
                (*pphandle)->data_options = 0;
#endif
            }

            /* Decide on operation mode */

            /* mode already initialized to the default 0 (for SCI_MODE_STM) */
            if (NULL != pcnfg) {
                switch (pcnfg->mode){
		case SCI_MODE_DUMP:
			mode = 0x1;
			break;
#ifdef _SC_VER_1_16
		case SCI_MODE_STM_COND:
			mode = 0x2;
			break;
		case SCI_MODE_DUMP_COND:
			mode = 0x3;
			break;
		default:
			/*
			 * mode already initialized to the default 0
			 * (for SCI_MODE_STM).
			 * Just to remove compilation warning.
			 */
			break;
#endif
               }
            }

            /* Aquire ownership of each module mapped*/
            tmp_cnt = 0;
            for ( i=0; i < mod_cnt; i++ ) {

                if (NULL != mod_map[i]->vbase_addr){
                    switch (mod_map[i]->mod_type){
                    case SDRAM:
                        {
                            struct sc_sdram_regs * sc_regs;
                            sc_regs = (struct sc_sdram_regs *)mod_map[i]->vbase_addr;
                            /* Request ownership */
                            //if (0 == sc_regs->en)
				{
                                sc_regs->en = 1;
                                /* Check collection time to confirm ownership */
//TODO Put ownership conformation check back in
//                                if (0 == sc_regs->dump_collecttime)
                                {
                                    sc_regs->dump_collecttime = (*pphandle)->sdram_msg_rate;
                                    mod_map[i]->owner = true;
                                    tmp_cnt++;
                                    sc_regs->dump_manual = mode;
                                }
                                /* We are not going to clear sc_regs->en because
                                 * we don't know that the debugger has not set it
                                 * and we just got caught a race condition.
                                 */
                            }
                            break;
                        }
                    case MSTR:
                        {
                            struct sc_lat_regs * sc_regs;
                            sc_regs = (struct sc_lat_regs *)mod_map[i]->vbase_addr;
                            /* Request ownership */
                            //if (0 == sc_regs->en)
				{
                                sc_regs->en = 1;
                                /* Check collection time to confirm ownership */
//TODO Put ownership conformation check back in
//                              if (0 == sc_regs->dump_collecttime)
                                {
                                    sc_regs->dump_collecttime = (*pphandle)->mstr_msg_rate;
                                    mod_map[i]->owner = true;
                                    tmp_cnt++;
                                    sc_regs->dump_manual = mode;
                                }
                            }
                            break;
                        }
                    }
                }
            }
            if ( 0 == tmp_cnt ) {
                ret_val = SCI_ERR_SC_NOT_AVAILABLE;
            }
        }
    }

    //TODO for each module that is owned disable all the counters and filters.



    if ( SCI_SUCCESS != ret_val) {

        /* Must be a SCI_ERR_MEM_ALLOC or a SCI_ERR_OWNERSHIP */

        /* unmap each non-null mod_map[i]->vbase_addr */
        for ( i=0; i < mod_cnt; i++ ) {
            if ( NULL != mod_map[i]->vbase_addr ){
                cTools_memUnMap(mod_map[i]->vbase_addr, mod_map[i]->mod_size);
                mod_map[i]->vbase_addr = NULL;
            }
        }

        /* If handle non-null free it and set it back to NULL*/
        if ( NULL != *pphandle ){
            cTools_memFree(*pphandle);
            *pphandle = NULL;
        }

        /* Call callback - ok to call with NULL handle*/
        if ( NULL != pcnfg->errhandler)
            pcnfg->errhandler(*pphandle, __FUNCTION__, ret_val);

    }

    return ret_val;
}
/*
 * sci_close
 *
 */
enum sci_err sci_close(psci_handle * const pphandle)
{
    int i;

    if ( NULL == *pphandle )
        return SCI_ERR_INVALID_HANDLE;

    /* If any module is running need to disable */

    if (SCI_MOD_ENABLED == (*pphandle)->mod_state){
        sci_global_disable(*pphandle);
    }

    /* Remove any active use cases.
     * Note - no error handling on call to sci_remove_usecase because
     * we should only be able to add valid usecase pointers to the
     * link list.
     */
    while ( NULL != (*pphandle)->pusecase_head) {
        psci_usecase_key pusecase_key = (*pphandle)->pusecase_head;
        sci_remove_usecase (*pphandle, &pusecase_key);
    }

    /*Disable and release ownership of modules */
    for ( i=0; i < mod_cnt; i++ ) {

        if ((NULL != mod_map[i]->vbase_addr) && ( true == mod_map[i]->owner )){
            switch (mod_map[i]->mod_type){
            case SDRAM:
                {
                    struct sc_sdram_regs * sc_regs;
                    sc_regs = (struct sc_sdram_regs *)mod_map[i]->vbase_addr;
                    sc_regs->en = 0;
                    sc_regs->dump_collecttime = 0;
                    break;
                }
            case MSTR:
                {
                    struct sc_lat_regs * sc_regs;
                    sc_regs = (struct sc_lat_regs *)mod_map[i]->vbase_addr;
                    sc_regs->en = 0;
                    sc_regs->dump_collecttime = 0;
                    break;
                }
            }/* end of switch */
        }/* end of if */
    }/* end of for */

    /* unmap each non-null mod_map[i]->vbase_addr */
    for ( i=0; i < mod_cnt; i++ ) {
        if ( NULL != mod_map[i]->vbase_addr ){
            cTools_memUnMap(mod_map[i]->vbase_addr, mod_map[i]->mod_size);
            mod_map[i]->vbase_addr = NULL;
        }
    }

    if ( NULL != *pphandle )
        cTools_memFree(*pphandle);

    *pphandle = NULL;

    return SCI_SUCCESS;
}

enum sci_err sci_get_version(psci_handle const phandle, uint32_t * const plib_major_ver,
                                                       uint32_t * const plib_minor_ver,
                                                       uint32_t * const plib_func_id,
                                                       uint32_t * const pmod_func_id )
{
    int i;
    int tmp_cnt;
    uint32_t pmod_type_id;
    enum sci_err ret_err = SCI_SUCCESS;

    /* Note that this function can be called with a NULL handle since
     * in this case the handle is used only for error handling
     */

    * plib_major_ver = SCILIB_MAJOR_VERSION;
    * plib_minor_ver = SCILIB_MINOR_VERSION;
    * plib_func_id = SC_LIB_FUNC;


    /* We are making the assumption that for a device all the
     * SC modules are at least the same func and revision level.
     */

    /* Find the first module that is mapped */
    tmp_cnt = 0;
    for ( i=0; i < mod_cnt; i++ ) {
        if ( NULL != mod_map[i]->vbase_addr ){
            switch (mod_map[i]->mod_type){
            case SDRAM:
            {
                struct sc_sdram_regs * sc_regs = (struct sc_sdram_regs *)mod_map[i]->vbase_addr;
                /* Request ownership */
                pmod_type_id = *(uint32_t *)(&sc_regs->stdhosthdr_core);
                *pmod_func_id = GET_SCMOD_FUNC(*(uint32_t *)(&sc_regs->stdhosthdr_version));
                break;
            }
            case MSTR:
            {
                struct sc_lat_regs * sc_regs = (struct sc_lat_regs *)mod_map[i]->vbase_addr;
                /* Request ownership */
                pmod_type_id = *(uint32_t *)(&sc_regs->stdhosthdr_core);
                *pmod_func_id = GET_SCMOD_FUNC(*(uint32_t *)(&sc_regs->stdhosthdr_version));
                break;
            }
            }

            /* since we found a valid module can break out of for loop */
            tmp_cnt++;
            break;
        }

     }

     if ( 0 == tmp_cnt )
        ret_err = SCI_ERR_ACCESS;
     else
        if (mod_func_ver[i] != *pmod_func_id)
            ret_err = SCI_ERR_REVISION;
            if ( pmod_type_id != SC_MOD_TYPE )
                ret_err = SCI_ERR_REVISION;

    if (   (SCI_SUCCESS != ret_err) && (NULL != phandle)
        && (NULL != phandle->psci_callback))
        phandle->psci_callback(phandle, __FUNCTION__, ret_err);

    return ret_err;
}

enum sci_err sci_reg_usecase_sdram(psci_handle const phandle,
                        struct sci_config_sdram *  const pcfg,
                        psci_usecase_key * pusecase_key )
{
    int i,j,k;
    int cntr_assigned[2] = {-1,-1};        /* free counter assigned          */
    int mod;
    int num_filters = 1;
    struct usecase_parms uc_parms;
    struct sc_sdram_regs * sc_regs = NULL; /* SC register pointer            */
    struct sdram_filter filter[2];
    enum sci_err ret_err = SCI_SUCCESS;

    if ( NULL == phandle )
        return SCI_ERR_INVALID_HANDLE;

    if ((NULL != *pusecase_key) || ( NULL == pcfg ))
        ret_err =  SCI_ERR_INVALID_PARM;
    else
    {
        if (SCI_MOD_ENABLED == phandle->mod_state){
            ret_err = SCI_ERR_MODULE_ENABLED;
        }
        else
        {
            get_usecase_params( pcfg->usecase, &uc_parms);

            if (get_cntr(SDRAM, pcfg->probe_id, pcfg->usecase, pcfg->num_filters,
                         uc_parms.num_cntr_req, &mod,  cntr_assigned)){
                ret_err = SCI_ERR_SC_NOT_AVAILABLE;
            }
            else
            {
                /* Generate and initialize the usecase key */
                *pusecase_key = (struct sci_usecase_key_t *)cTools_memAlloc(sizeof(struct sci_usecase_key_t));
                if ( NULL == *pusecase_key )
                    ret_err = SCI_ERR_MEM_ALLOC;
            }
        }
    }

    if ( SCI_SUCCESS != ret_err ){
        if (NULL != phandle->psci_callback)
            phandle->psci_callback(phandle, __FUNCTION__, ret_err);
        return ret_err;
    }

    /* Note - no more errors possible after this point */

    (*pusecase_key)->module_index = mod;
    (*pusecase_key)->num_counters = uc_parms.num_cntr_req;
    (*pusecase_key)->counter_index[0] = cntr_assigned[0];
    (*pusecase_key)->counter_index[1] = cntr_assigned[1];
    (*pusecase_key)->usecase = pcfg->usecase;

    /* put usecase key in the handle's link list */
    put_uckey(phandle, *pusecase_key);

    /* If the number of filters requested by the user is zero
     * then setup the default values
     */
     if (0 == pcfg->num_filters) {
        filter[0].en = 1;
        filter[0].mask_mstaddr = 0;     /* Don't care - exclude from match */
        filter[0].mask_rd = 0;          /* Enable all reads */
        filter[0].mask_wr = 0;          /* Enable all writes */
        filter[0].mask_err = 0;         /* no errors */
        filter[0].mask_userinfo = 0;    /* Don't care - exclude from match */
        filter[0].match_mstaddr = 0;
        filter[0].match_rd = 0;
        filter[0].match_wr = 0;
        filter[0].match_err = 0;
        filter[0].match_userinfo = 0;
        filter[1].en = 0;

        pcfg->filter[0].trans_qual = SCI_RD_OR_WR_DONTCARE;
     }
     else {
        num_filters = pcfg->num_filters;
        for ( i= 0; i< pcfg->num_filters; i++){
#ifdef _OMAP4430_ES1
            filter[i].match_mstaddr = pcfg->filter[i].mstr_addr_match >>2;
#else
            filter[i].match_mstaddr = pcfg->filter[i].mstr_addr_match;
#endif
            if ( SCI_MASTID_ALL == pcfg->filter[i].mstr_addr_match)
                filter[i].mask_mstaddr = 0;
            else
                filter[i].mask_mstaddr = pcfg->filter[i].mstr_addr_mask;

            switch (pcfg->filter[i].trans_qual) {
            case SCI_RD_ONLY:
                filter[i].mask_rd = 1;
                filter[i].mask_wr = 1;
                filter[i].match_rd = 1;
                filter[i].match_wr = 0;
                break;
            case SCI_WR_ONLY:
                filter[i].mask_rd = 1;
                filter[i].mask_wr = 1;
                filter[i].match_rd = 0;
                filter[i].match_wr = 1;
                break;
            case SCI_RD_OR_WR_NONE:
                filter[i].mask_rd = 1;
                filter[i].mask_wr = 1;
                filter[i].match_rd = 0;
                filter[i].match_wr = 0;
                break;
            case SCI_RD_OR_WR_DONTCARE:
                filter[i].mask_rd = 0;
                filter[i].mask_wr = 0;
                filter[i].match_rd = 0;
                filter[i].match_wr = 0;
                break;
            default:
                return SCI_ERR_INVALID_PARM;
            }

            switch (pcfg->filter[i].error_qual ) {
            case SCI_ERR_ONLY:
                filter[i].mask_err = 1;
                filter[i].match_err = 1;
                break;
            case SCI_ERR_NONE:
                filter[i].mask_err = 1;
                filter[i].match_err = 0;
                break;
            case SCI_ERR_DONTCARE:
                filter[i].mask_err = 0;
                filter[i].match_err = 0;
                break;
            default:
                return SCI_ERR_INVALID_PARM;
            }

            /* Set userinfo to don't care */
            filter[i].mask_userinfo = 0;
            filter[i].match_userinfo = 0;

            /* All done so enable the filter last */
            filter[i].en = 1;
        }
     }

#ifdef _STM_Logging
    /* Setup the meta data */
    get_meta_data(phandle, *pusecase_key,
                  sdram_probe_name_table[pcfg->probe_id],
                  trans_type_table[pcfg->filter[0].trans_qual],
                  master_name_table[filter[0].match_mstaddr],
                  filter[0].mask_mstaddr );
#endif
    /* Mark the counters used */
    for ( j= 0; j < uc_parms.num_cntr_req; j++ ){
        (mod_map[mod]->cnt_map)[cntr_assigned[j]].used = true;
    }

    /* Set the use case */
    mod_map[mod]->usecase = pcfg->usecase;
    mod_map[mod]->usecase_cnt++;

    /* Program the sc module for the use case */
    sc_regs = (struct sc_sdram_regs *)mod_map[mod]->vbase_addr;

    if ( phandle->trigger_enable )
        sc_regs->trigen = 1;
    else
        sc_regs->trigen = 0;

    sc_regs->reqevt = uc_parms.reqevt;
    sc_regs->rspevt = uc_parms.rspevt;
    for ( j = 0; j < uc_parms.num_cntr_req; j++){
        sc_regs->evtmux_sel[cntr_assigned[j]] = (sdram_probe_map[pcfg->probe_id] * 2) + uc_parms.port_type;
    }

    /* Program the filters
     * Note that if two counters are needed for the use case, the filters of
     * both counters are set identically
     */
    for ( j=0; j < uc_parms.num_cntr_req; j++ ) {
        for ( k=0; k < num_filters; k++ ) {
            struct sdram_filter * sc_reg_filter = get_filter_addr(mod, cntr_assigned[j],k);
            *sc_reg_filter = filter[k];
        }
    }

    /*Program the counter */
    for ( k=0; k < uc_parms.num_cntr_req; k++ ) {
        int num_filters = sdram_cnt_map[cntr_assigned[k]].num_filters;
        if (2 == num_filters){
            struct sdram_cnt_filter2 * sc_cnt_addr =  (struct sdram_cnt_filter2 *)get_cntr_addr( mod, cntr_assigned[k]);
            sc_cnt_addr->op_sel = uc_parms.op_sel[k];
            sc_cnt_addr->op_evt_info_sel = uc_parms.evt_info_sel[k];
            sc_cnt_addr->globalen = 1;
#ifdef _SC_VER_1_16
            if (true == pcfg->addr_filter_enable){
                sc_cnt_addr->addren = 1;
                sc_cnt_addr->addrmax= sys_to_phys_addr(pcfg->addr_filter_max) >> 12;
                sc_cnt_addr->addrmin= sys_to_phys_addr(pcfg->addr_filter_min) >> 12;
            }
            else {
                sc_cnt_addr->addren = 0;
                sc_cnt_addr->addrmax= 0;
                sc_cnt_addr->addrmin= 0;
            }
#endif
        }
        if (1 == num_filters){
            struct sdram_cnt_filter1 * sc_cnt_addr =  (struct sdram_cnt_filter1 *)get_cntr_addr( mod, cntr_assigned[k]);
            sc_cnt_addr->op_sel = uc_parms.op_sel[k];
            sc_cnt_addr->op_evt_info_sel = uc_parms.evt_info_sel[k];
            sc_cnt_addr->globalen = 1;
#ifdef _SC_VER_1_16
            if (true == pcfg->addr_filter_enable){
                sc_cnt_addr->addren = 1;
                sc_cnt_addr->addrmax= sys_to_phys_addr(pcfg->addr_filter_max) >> 12;
                sc_cnt_addr->addrmin= sys_to_phys_addr(pcfg->addr_filter_min) >> 12;
            }
            else {
                sc_cnt_addr->addren = 0;
                sc_cnt_addr->addrmax= 0;
                sc_cnt_addr->addrmin= 0;
            }
#endif
        }
        if (0 == num_filters){
            struct sdram_cnt_filter0 * sc_cnt_addr =  (struct sdram_cnt_filter0 *)get_cntr_addr( mod, cntr_assigned[k]);
            sc_cnt_addr->op_sel = uc_parms.op_sel[k];
            sc_cnt_addr->op_evt_info_sel = uc_parms.evt_info_sel[k];
            sc_cnt_addr->globalen = 1;
#ifdef _SC_VER_1_16
            if (true == pcfg->addr_filter_enable){
                sc_cnt_addr->addren = 1;
                sc_cnt_addr->addrmax= sys_to_phys_addr(pcfg->addr_filter_max) >> 12;
                sc_cnt_addr->addrmin= sys_to_phys_addr(pcfg->addr_filter_min) >> 12;
            }
            else {
                sc_cnt_addr->addren = 0;
                sc_cnt_addr->addrmax= 0;
                sc_cnt_addr->addrmin= 0;
            }
#endif
        }
    }

    return SCI_SUCCESS;
}



enum sci_err sci_reg_usecase_mstr(psci_handle const phandle,
                        struct sci_config_mstr *  const pcfg,
                        psci_usecase_key * pusecase_key )
{
    int j,k;
    int cntr_assigned[2] = {-1,-1};        /* free counter assigned          */
    int mod;
    int num_filters = 1;
    struct usecase_parms uc_parms;
    struct sc_lat_regs * sc_regs = NULL; /* SC register pointer            */
    struct lat_filter filter;
    enum sci_err ret_err = SCI_SUCCESS;

    if ( NULL == phandle )
        return SCI_ERR_INVALID_HANDLE;

    if ((NULL != *pusecase_key) || ( NULL == pcfg ))
        ret_err =  SCI_ERR_INVALID_PARM;
    else
    {
        if (SCI_MOD_ENABLED == phandle->mod_state){
            ret_err = SCI_ERR_MODULE_ENABLED;
        }
        else {
            get_usecase_params( pcfg->usecase, &uc_parms);


            if (get_cntr(MSTR, pcfg->probe_id, pcfg->usecase, pcfg->num_filters,
                         uc_parms.num_cntr_req, &mod,  cntr_assigned))
                ret_err = SCI_ERR_SC_NOT_AVAILABLE;
            else {
                *pusecase_key = (struct sci_usecase_key_t *)cTools_memAlloc(sizeof(struct sci_usecase_key_t));
                if ( NULL == *pusecase_key )
                    ret_err = SCI_ERR_MEM_ALLOC;
            }
        }
    }

    if ( SCI_SUCCESS != ret_err ){
        if (NULL != phandle->psci_callback)
            phandle->psci_callback(phandle, __FUNCTION__, ret_err);
        return ret_err;
    }

    /* Note - no more errors possible after this point */

    /* Generate and initialize the usecase key */
    (*pusecase_key)->module_index = mod;
    (*pusecase_key)->num_counters = uc_parms.num_cntr_req;
    (*pusecase_key)->counter_index[0] = cntr_assigned[0];
    (*pusecase_key)->counter_index[1] = cntr_assigned[1];
    (*pusecase_key)->usecase = pcfg->usecase;

    /* put usecase key in the handle's link list */
    put_uckey(phandle, *pusecase_key);

    /* If the number of filters requested by the user is zero
     * then setup the default values
     */
     if (0 == pcfg->num_filters) {
        filter.en = 1;
        filter.mask_mstaddr = 0;     /* Don't care - exclude from match */
        filter.mask_rd = 0;          /* Enable all reads */
        filter.mask_wr = 0;          /* Enable all writes */
        filter.mask_err = 0;         /* Enable all errors */
        filter.mask_slvaddr = 0;
        filter.mask_requserinfo = 0;
        filter.mask_rspuserinfo = 0;
        filter.match_mstaddr = 0;
        filter.match_rd = 0;
        filter.match_wr = 0;
        filter.match_err = 0;
        filter.match_slvaddr = 0;
        filter.match_requserinfo = 0;
        filter.match_rspuserinfo = 0;

        pcfg->filter.trans_qual = SCI_RD_OR_WR_DONTCARE;

     }
     else {
        /* Only one filter */

        filter.match_mstaddr = 0;
        filter.mask_mstaddr = 0;

        filter.mask_requserinfo = 0;
        filter.mask_rspuserinfo = 0;
        filter.match_requserinfo = 0;
        filter.match_rspuserinfo = 0;

        filter.match_slvaddr = pcfg->filter.slave_addr_match;
        if ( SCI_SLVID_ALL == pcfg->filter.slave_addr_match)
            filter.mask_slvaddr = 0;
        else
            filter.mask_slvaddr = pcfg->filter.slave_addr_match;

        switch (pcfg->filter.trans_qual) {
        case SCI_RD_ONLY:
            filter.mask_rd = 1;
            filter.mask_wr = 1;
            filter.match_rd = 1;
            filter.match_wr = 0;
            break;
        case SCI_WR_ONLY:
            filter.mask_rd = 1;
            filter.mask_wr = 1;
            filter.match_rd = 0;
            filter.match_wr = 1;
            break;
        case SCI_RD_OR_WR_NONE:
            filter.mask_rd = 1;
            filter.mask_wr = 1;
            filter.match_rd = 0;
            filter.match_wr = 0;
            break;
        case SCI_RD_OR_WR_DONTCARE:
            filter.mask_rd = 0;
            filter.mask_wr = 0;
            filter.match_rd = 0;
            filter.match_wr = 0;
            break;
        default:
            return SCI_ERR_INVALID_PARM;
        }

        switch (pcfg->filter.error_qual ) {
        case SCI_ERR_ONLY:
            filter.mask_err = 1;
            filter.match_err = 1;
            break;
        case SCI_ERR_NONE:
            filter.mask_err = 1;
            filter.match_err = 0;
            break;
        case SCI_ERR_DONTCARE:
            filter.mask_err = 0;
            filter.match_err = 0;
            break;
        default:
            return SCI_ERR_INVALID_PARM;
        }

        /* All done so enable the filter last */
        filter.en = 1;
    }

#ifdef _STM_Logging
    /* Setup the meta data */
    get_meta_data(phandle, *pusecase_key,
                  mstr_probe_name_table[pcfg->probe_id],
                  trans_type_table[pcfg->filter.trans_qual],
                  master_name_table[filter.match_mstaddr],
                  filter.mask_mstaddr );
#endif

    /* Mark the counters used */
    for ( j= 0; j < uc_parms.num_cntr_req; j++ ){
        (mod_map[mod]->cnt_map)[cntr_assigned[j]].used = true;
    }

    /* Set the use case */
    mod_map[mod]->usecase = pcfg->usecase;
    mod_map[mod]->usecase_cnt++;

    /* Program the sc module for the use case */
    sc_regs = (struct sc_lat_regs *)mod_map[mod]->vbase_addr;

    if ( phandle->trigger_enable )
        sc_regs->trigen = 1;
    else
        sc_regs->trigen = 0;

    sc_regs->reqevt = uc_parms.reqevt;
    sc_regs->rspevt = uc_parms.rspevt;
    for ( j = 0; j < uc_parms.num_cntr_req; j++){
        if ( LAT0 == mod )
            sc_regs->evtmux_sel[cntr_assigned[j]] = (lat0_probe_map[pcfg->probe_id] * 2) + uc_parms.port_type;
        else
            sc_regs->evtmux_sel[cntr_assigned[j]] = (lat1_probe_map[pcfg->probe_id] * 2) + uc_parms.port_type;
    }

    /* Program the filters
     * Note that of two counters are needed for the use case, the filters of
     * both counters are set identically
     */

    for ( j=0; j < uc_parms.num_cntr_req; j++ ) {
        for ( k=0; k < num_filters; k++ ) {
            struct lat_filter * sc_reg_filter = get_filter_addr(mod, cntr_assigned[j],k);
            *sc_reg_filter = filter;
        }
    }

    /*Program the counter */
    for ( k=0; k < uc_parms.num_cntr_req; k++ ) {
        int num_filters = lat_cnt_map[cntr_assigned[k]].num_filters;
        if (1 == num_filters){
            struct lat_cnt_filter1 * sc_cnt_addr =  (struct lat_cnt_filter1 *)get_cntr_addr( mod, cntr_assigned[k]);
            sc_cnt_addr->op_sel = uc_parms.op_sel[k];
            sc_cnt_addr->op_evt_info_sel = uc_parms.evt_info_sel[k];
            sc_cnt_addr->globalen = 1;
        }
    }

    return SCI_SUCCESS;
}

enum sci_err sci_remove_usecase (psci_handle const phandle, psci_usecase_key * usecase_key)
{

    int i;
    int mod;
    enum sci_err ret_err = SCI_SUCCESS;

    if ( NULL == phandle )
        return SCI_ERR_INVALID_HANDLE;

    if (NULL == *usecase_key)
        ret_err = SCI_ERR_INVALID_PARM;
    else
        if (SCI_MOD_ENABLED == phandle->mod_state)
            ret_err = SCI_ERR_MODULE_ENABLED;

    if ( SCI_SUCCESS != ret_err ){
        if (NULL != phandle->psci_callback)
            phandle->psci_callback(phandle, __FUNCTION__, ret_err);
        return ret_err;
    }

    /* Can't set mod value until after parameter checks */
    mod = (*usecase_key)->module_index;

    /* Mark the counters not used */
    for ( i= 0; i < (*usecase_key)->num_counters; i++ ){
        (mod_map[mod]->cnt_map)[(*usecase_key)->counter_index[i]].used = false;
    }

    /*Disable each counter used */
    for ( i = 0; i < (*usecase_key)->num_counters; i++ ) {

        switch (mod_map[mod]->mod_type){
            case SDRAM:
            {
                int k;
                int num_filters = sdram_cnt_map[(*usecase_key)->counter_index[i]].num_filters;
                if (2 == num_filters){
                    struct sdram_cnt_filter2 * sc_cnt_addr =  (struct sdram_cnt_filter2 *)get_cntr_addr( mod, (*usecase_key)->counter_index[i]);
                    sc_cnt_addr->globalen = 0;

                }
                if (1 == num_filters){
                    struct sdram_cnt_filter1 * sc_cnt_addr =  (struct sdram_cnt_filter1 *)get_cntr_addr( mod, (*usecase_key)->counter_index[i]);
                    sc_cnt_addr->globalen = 0;

                }
                if (0 == num_filters){
                    struct sdram_cnt_filter0 * sc_cnt_addr =  (struct sdram_cnt_filter0 *)get_cntr_addr( mod, (*usecase_key)->counter_index[i]);
                    sc_cnt_addr->globalen = 0;
                }

                /* disable all filters for the counter(s) used */
                for (k=0; k < num_filters; k++){
                    struct sdram_filter * filter = (struct sdram_filter *)get_filter_addr( mod, (*usecase_key)->counter_index[i], k);
                    filter->en = 0;
                }

                break;

            }
            case MSTR:
            {
                struct lat_cnt_filter1 * sc_cnt_addr =  (struct lat_cnt_filter1 *)get_cntr_addr( mod, (*usecase_key)->counter_index[i]);
                struct sdram_filter * filter = (struct sdram_filter *)get_filter_addr( mod, (*usecase_key)->counter_index[i], 0);
                sc_cnt_addr->globalen = 0;
                filter->en = 0;

                break;
            }
            }


    }

    /* Unlink the usecase from the link list */
    if ( (*usecase_key) == phandle->pusecase_head) {
        phandle->pusecase_head = (*usecase_key)->next;
    }
    else {
        ((*usecase_key)->prev)->next = (*usecase_key)->next;
        ((*usecase_key)->next)->prev = (*usecase_key)->prev;
    }



    /* If this is the last use case using the module, free it for a new use case */
    if (0 == --mod_map[mod]->usecase_cnt)
            mod_map[mod]->usecase = -1;

    /* free the usecase buf and set the clients copy to NULL */
    cTools_memFree(*usecase_key);
    *usecase_key = NULL;

    return SCI_SUCCESS;
}

enum sci_err sci_global_enable(psci_handle const phandle)
{
    int i;
    if ( NULL == phandle )
        return SCI_ERR_INVALID_HANDLE;

    /* If the module's usecase count is > 0 then enable the module*/
    for ( i=0; i < mod_cnt; i++ ){
        if ( 0 < mod_map[i]->usecase_cnt ){
            switch (mod_map[i]->mod_type){
            case SDRAM:
            {
                struct sc_sdram_regs * sc_regs = (struct sc_sdram_regs *)mod_map[i]->vbase_addr;;
                sc_regs->soften = 1;
                break;
            }
            case MSTR:
            {
                struct sc_lat_regs * sc_regs = (struct sc_lat_regs *)mod_map[i]->vbase_addr;;
                sc_regs->soften = 1;
                break;
            }
            } /* End of switch */

        }

    }

    return SCI_SUCCESS;

}
enum sci_err sci_global_disable(psci_handle const phandle)
{
    int i;
    enum sci_err ret_err = SCI_SUCCESS;

    if ( NULL == phandle )
        return SCI_ERR_INVALID_HANDLE;

     /* If the module's usecase count is < 0 then disable the module */
    for ( i=0; i < mod_cnt; i++ ){
        if ( 0 < mod_map[i]->usecase_cnt ){
            switch (mod_map[i]->mod_type){
            case SDRAM:
            {
                struct sc_sdram_regs * sc_regs = (struct sc_sdram_regs *)mod_map[i]->vbase_addr;
                sc_regs->soften = 0;
                break;
            }
            case MSTR:
            {
                struct sc_lat_regs * sc_regs = (struct sc_lat_regs *)mod_map[i]->vbase_addr;
                sc_regs->soften = 0;
                break;
            }
            } /* End of switch */
        }

    }

    /* Send all meta data */
#ifdef _STM_Logging
    ret_err = send_meta_data(phandle);
#endif
    if ( SCI_SUCCESS != ret_err ){
        if (NULL != phandle->psci_callback)
            phandle->psci_callback(phandle, __FUNCTION__, ret_err);
        return ret_err;
    }


    return SCI_SUCCESS;
}

enum sci_err sci_dump(psci_handle const phandle )
{
    int i;
    /* Dump the counters for each module that has use cases enabled */
    if ( NULL == phandle )
        return SCI_ERR_INVALID_HANDLE;

    for ( i=0; i < mod_cnt; i++ ) {
        if ( 0 != mod_map[i]->usecase_cnt){
            switch (mod_map[i]->mod_type){
            case SDRAM:
            {
                struct sc_sdram_regs * sc_regs = (struct sc_sdram_regs *)mod_map[i]->vbase_addr;;
                sc_regs->dump_send = 1;
                break;
            }
            case MSTR:
            {
                struct sc_lat_regs * sc_regs = (struct sc_lat_regs *)mod_map[i]->vbase_addr;;
                sc_regs->dump_send = 1;
                break;
            }
            } /* End of switch */
        }
    }
    return SCI_SUCCESS;
}

#ifdef _SC_VER_1_16
enum sci_err sci_dump_info(psci_handle const phandle, psci_usecase_key usecase_key, int * num_sci_cntrs)
{
    enum sci_err ret_err = SCI_SUCCESS;

    if ( NULL == phandle )
        return SCI_ERR_INVALID_HANDLE;

    if (NULL == usecase_key) {
        ret_err = SCI_ERR_INVALID_PARM;
        if (NULL != phandle->psci_callback)
            phandle->psci_callback(phandle, __FUNCTION__, ret_err);
        return ret_err;
    }

    *num_sci_cntrs = usecase_key->num_counters;
    return ret_err;
}

enum sci_err sci_dump_sdram_cntrs(int num_sci_cntrs, uint32_t * pbuf)
{
	reg32_t *pdump_cntrs;
	int i;

	struct sc_sdram_regs *sc_regs = (struct sc_sdram_regs *)mod_map[0]->vbase_addr;
	pdump_cntrs = &sc_regs->dump_cnt[0];

	for (i=0; i< num_sci_cntrs; i++){
		*pbuf++ = pdump_cntrs[i];
	}
	return SCI_SUCCESS;
}

enum sci_err sci_dump_cntrs(psci_handle const phandle, psci_usecase_key usecase_key, int num_sci_cntrs, uint32_t * pbuf)
{
    /* Dump the counters to pbuf for the provided usecase_key */
    reg32_t * pdump_cntrs;

    enum sci_err ret_err = SCI_SUCCESS;

    if ( NULL == phandle )
        return SCI_ERR_INVALID_HANDLE;

    if (NULL == usecase_key) {
        ret_err = SCI_ERR_INVALID_PARM;
        if (NULL != phandle->psci_callback)
            phandle->psci_callback(phandle, __FUNCTION__, ret_err);
        return ret_err;
    }

    switch (mod_map[usecase_key->module_index]->mod_type){
    case SDRAM:
    {
        struct sc_sdram_regs * sc_regs = (struct sc_sdram_regs *)mod_map[usecase_key->module_index]->vbase_addr;
        pdump_cntrs = &sc_regs->dump_cnt[0];
        break;
    }
    case MSTR:
    {
        struct sc_lat_regs * sc_regs = (struct sc_lat_regs *)mod_map[usecase_key->module_index]->vbase_addr;
        pdump_cntrs = &sc_regs->dump_cnt[0];
        break;
    }
    } /* End of switch */

    /* return the counters requested */
    if (NULL != pbuf) {
        int i;

        for (i=0; i< num_sci_cntrs; i++){
            *pbuf++ = pdump_cntrs[usecase_key->counter_index[i]];
        }
    }

    return ret_err;
}

enum sci_err sci_dump_disable(psci_handle const phandle)
{
    int i;

    if ( NULL == phandle )
        return SCI_ERR_INVALID_HANDLE;

    /* Disable dumping for each module that has usecases assigned */
    for ( i=0; i < mod_cnt; i++ ) {
        if ( 0 != mod_map[i]->usecase_cnt){

            switch (mod_map[i]->mod_type){
            case SDRAM:
            {
                struct sc_sdram_regs * sc_regs = (struct sc_sdram_regs *)mod_map[i]->vbase_addr;;
                sc_regs->dump_disable = 1;
                break;
            }
            case MSTR:
            {
                struct sc_lat_regs * sc_regs = (struct sc_lat_regs *)mod_map[i]->vbase_addr;;
                sc_regs->dump_disable = 1;
                break;
            }
            } /* End of switch */
        }
    }

    return SCI_SUCCESS;
}
enum sci_err sci_dump_enable(psci_handle const phandle )
{
    int i;

    if ( NULL == phandle )
        return SCI_ERR_INVALID_HANDLE;

    /* Enable dumping for each module that has usecases assigned */
    for ( i=0; i < mod_cnt; i++ ) {
        if ( 0 != mod_map[i]->usecase_cnt){

            switch (mod_map[i]->mod_type){
            case SDRAM:
            {
                struct sc_sdram_regs * sc_regs = (struct sc_sdram_regs *)mod_map[i]->vbase_addr;;
                sc_regs->dump_disable = 0;
                break;
            }
            case MSTR:
            {
                struct sc_lat_regs * sc_regs = (struct sc_lat_regs *)mod_map[i]->vbase_addr;;
                sc_regs->dump_disable = 0;
                break;
            }
            } /* End of switch */
        }
    }
    return SCI_SUCCESS;
}
#endif
/*
 * Internal utility functions
 *
 */

enum sci_err get_usecase_params( int usecase, struct usecase_parms * pusecase_parms)
{

    /* Initialize use case paramters */
    switch (usecase){
    case SCI_SDRAM_THROUGHPUT:
    case SCI_MSTR_THROUGHPUT:
        pusecase_parms->num_cntr_req = 1;
        pusecase_parms->reqevt = SC_EVENT_SEL_PKT;
        pusecase_parms->rspevt = SC_EVENT_SEL_PKT;          //TODO - use to be SC_EVENT_SEL_NONE, but Joe is setting to PKT -
                                                            // so need to check throughput/sample with a short bursts to
                                                            // confrim byte count.
        pusecase_parms->port_type = SC_REQUEST_PROBE;
        pusecase_parms->op_sel[0] = SC_OPSEL_EVT_INFO;
        pusecase_parms->evt_info_sel[0] = SC_EVTINFOSEL_BYTELEN;
        break;
    case SCI_SDRAM_LINKOCCUPY_REQUEST:
    case SCI_MSTR_LINKOCCUPY_REQUEST:
        pusecase_parms->num_cntr_req = 1;
        pusecase_parms->reqevt = SC_EVENT_SEL_IDLE;
        pusecase_parms->rspevt = SC_EVENT_SEL_NONE;
        pusecase_parms->port_type = SC_REQUEST_PROBE;
        pusecase_parms->op_sel[0] = SC_OPSEL_FILTER_HIT;
        pusecase_parms->evt_info_sel[0] = 0;
        break;
    case SCI_SDRAM_LINKOCCUPY_RESPONSE:
    case SCI_MSTR_LINKOCCUPY_RESPONSE:
        pusecase_parms->num_cntr_req = 1;
        pusecase_parms->reqevt = SC_EVENT_SEL_NONE;
        pusecase_parms->rspevt = SC_EVENT_SEL_IDLE;
        pusecase_parms->port_type = SC_RESPONSE_PROBE;
        pusecase_parms->op_sel[0] = SC_OPSEL_FILTER_HIT;
        pusecase_parms->evt_info_sel[0] = 0;
        break;
    case SCI_SDRAM_AVGBURST_LENGTH:
    case SCI_MSTR_AVGBURST_LENGTH:
        pusecase_parms->num_cntr_req = 2;
        pusecase_parms->reqevt = SC_EVENT_SEL_PKT;
        pusecase_parms->rspevt = SC_EVENT_SEL_NONE;
        pusecase_parms->port_type = SC_REQUEST_PROBE;
        pusecase_parms->op_sel[0] = SC_OPSEL_EVT_INFO;
        pusecase_parms->evt_info_sel[0] = SC_EVTINFOSEL_BYTELEN;
        pusecase_parms->op_sel[1] = SC_OPSEL_FILTER_HIT;
        pusecase_parms->evt_info_sel[1] = 0;
        break;
    case SCI_MSTR_AVGLATENCY:
        pusecase_parms->num_cntr_req = 2;
        pusecase_parms->reqevt = SC_EVENT_SEL_LATENCY;
        pusecase_parms->rspevt = SC_EVENT_SEL_LATENCY;
        pusecase_parms->port_type = SC_RESPONSE_PROBE; //SC_REQUEST_PROBE;
        pusecase_parms->op_sel[0] = SC_OPSEL_EVT_INFO;
        pusecase_parms->evt_info_sel[0] = SC_EVTINFOSEL_LATENCY;
        pusecase_parms->op_sel[1] = SC_OPSEL_FILTER_HIT;
        pusecase_parms->evt_info_sel[1] = 0;
    default:
        return SCI_ERR_INVALID_PARM;
    };

    return SCI_SUCCESS;


}

enum sci_err get_cntr (enum sci_module_type mod_type, int probe_id, int usecase,
                       int num_filters, int num_cntr_req,
                       int * mod_index,  int * cntr_assigned)
{
    int i,j;
    int cntr_assigned_cnt = 0;
    int probe_num = -1;

    /* Search for a SDRAM SC module and available counter elements */
    for ( i=0; i < mod_cnt; i++ ) {
        if (    (NULL != mod_map[i]->vbase_addr)
            && (mod_type == mod_map[i]->mod_type)
            && (true == mod_map[i]->owner)) {

            /* Does the module support the probe */
            for (j=0; j < mod_map[i]->num_ports; j++){
                if (probe_id == mod_map[i]->port_map[j]) {
                    probe_num = j;
                    break;
                }
            }
            if ( -1 == probe_num ) continue;

            /* If the requested use case is not compatible
             * with the SC module's current use case, then
             * check the next module.
             */
#if 0
            if (  (0 != mod_map[i]->usecase_cnt)
               && (!usecase_compat_table[usecase][mod_map[i]->usecase]))
                continue;
#else
            if (   (0 != mod_map[i]->usecase_cnt)
                && (SC_GET_USECASE_COMPAT_VALUE(mod_map[i]->usecase) != 0)
                && (SC_GET_USECASE_COMPAT_VALUE(mod_map[i]->usecase)
                    != SC_GET_USECASE_COMPAT_VALUE(usecase)))
                continue;
#endif
            /* Are there counters available that meets our needs?
             * Note - this search function does not try to find the best
             * match, just the first counter that meets the criteria.
             */
            for ( j=0; j< mod_map[i]->num_counters; j++ ) {
                if (   ( false == (mod_map[i]->cnt_map)[j].used)
                    && ( num_filters <= (mod_map[i]->cnt_map)[j].num_filters) ){
                    cntr_assigned[cntr_assigned_cnt++] = j;
                }
                if ( num_cntr_req == cntr_assigned_cnt )
                    break;
            }

            /* If we could not find the right number release these
             * and try another module.
             */
            if ( num_cntr_req  != cntr_assigned_cnt )
                cntr_assigned_cnt = 0;
                /* now fall through to check next module */
            else
                break;
        }
    }

    if (0 == cntr_assigned_cnt) {
        return SCI_ERR_SC_NOT_AVAILABLE;
    }

    *mod_index = i;

    return SCI_SUCCESS;
}


void put_uckey(psci_handle const phandle, struct sci_usecase_key_t * puc_key)
{
    /* Add the usecase struct to the link list */

    struct sci_usecase_key_t * next = phandle->pusecase_head;
    if (NULL == next){
        /* First usecase in link list */
        phandle->pusecase_head = puc_key;
        puc_key->next = NULL;
        puc_key->prev = NULL;
    }
    else{
        /* Walk the list until we find the end */
        while ( NULL != next->next ){
            next = next->next;
        }
        puc_key->prev = next;
        puc_key->next = NULL;
        next->next = puc_key;
    }

}

#ifdef _STM_Logging
enum sci_err get_meta_data(psci_handle const phandle, struct sci_usecase_key_t * puc_key,
                           const char * probe_name,
                           const char * trans_type,
                           const char * master_or_slave_name,
                           uint32_t mask )
{

    int i;
    int32_t chr_cnt = 0;
    int32_t mod_id = puc_key->module_index;
    const char * cnt_name[2];
    char formula[32];
    int formula_size = sizeof(formula);
    int formula_cnt;
    const char * unit;
    int ofmask;
    uint32_t msg_rate = ( SDRAM == puc_key->module_index ) ? phandle->sdram_msg_rate
                                                          : phandle->mstr_msg_rate;

    //Malloc enough space for the attribute string
    puc_key->pmeta_data_buf = (char *)cTools_memAlloc(SCI_META_BUFSIZE);
    if ( NULL == puc_key->pmeta_data_buf )
    {
        return SCI_ERR_MEM_ALLOC;
    }

    chr_cnt += snprintf (puc_key->pmeta_data_buf, SCI_META_BUFSIZE,
                         "{type=SC,id=%d,name=%s,sw=%d,suppress=%d,probe=%s:%s:%s+0x%x,",
                         mod_id,
                         module_name_table[mod_id],
                         msg_rate,
                         phandle->data_options,
                         probe_name,
                         trans_type,
                         master_or_slave_name,
                         mask);

    /* This will get updated if the usecase uses a latency counter */
    ofmask = cnt_overflow_norm[puc_key->module_index];

    switch (puc_key->usecase){
    case SCI_SDRAM_THROUGHPUT:
    case SCI_MSTR_THROUGHPUT:
#ifdef _SC_VER_1_16
    case SCI_SDRAM_THROUGHPUT_MINALARM:
    case SCI_SDRAM_THROUGHPUT_MAXALARM:
    case SCI_MSTR_THROUGHPUT_MINALARM:
    case SCI_MSTR_THROUGHPUT_MAXALARM:
#endif
        cnt_name[0] = cntr_name_payload;
        formula_cnt = snprintf(formula, formula_size, "100*(#%d/%d):2",
                               puc_key->counter_index[0],
                               msg_rate);
        unit = usecase_units_bytesperwindow;
        break;
    case SCI_SDRAM_LINKOCCUPY_REQUEST:
    case SCI_SDRAM_LINKOCCUPY_RESPONSE:
    case SCI_MSTR_LINKOCCUPY_REQUEST:
    case SCI_MSTR_LINKOCCUPY_RESPONSE:
        cnt_name[0] = cntr_name_idle;
        formula_cnt = snprintf(formula, formula_size, "100*(#%d/%d):3",
                               puc_key->counter_index[0],
                               msg_rate);
        unit = usecase_units_percent;
        break;
    case SCI_SDRAM_AVGBURST_LENGTH:
    case SCI_MSTR_AVGBURST_LENGTH:
        cnt_name[0] = cntr_name_payload;
        cnt_name[1] = cntr_name_packcnt;
        formula_cnt = snprintf(formula, formula_size, "#%d/#%d):1",
                               puc_key->counter_index[0],
                               puc_key->counter_index[1]);
        unit = usecase_units_bytesperpacket;
        break;
    case SCI_MSTR_AVGLATENCY:
#ifdef _SC_VER_1_16
    case SCI_MSTR_LATENCY_MAXALARM:
#endif
        cnt_name[0] = cntr_name_latcyc;
        cnt_name[1] = cntr_name_lattrans;
        ofmask = cnt_overflow_lat[puc_key->module_index];
        formula_cnt = snprintf(formula, formula_size, "#%d/#%d):9",
                               puc_key->counter_index[0],
                               puc_key->counter_index[1]);
        unit = usecase_units_cyclespertrans;
        break;
    };

#ifdef _DEBUG
        if (0 == ofmask)
            return SCI_ERR_STM;
#endif

    if ( formula_size < formula_cnt )
        return SCI_ERR_STM;

    /* Add counter names */
    for (i=0; i< puc_key->num_counters; i++){
        chr_cnt += snprintf ( puc_key->pmeta_data_buf+chr_cnt, SCI_META_BUFSIZE,
                              "#%d=%s,", puc_key->counter_index[i], cnt_name[i]);
    }

    /* Add formula section */
    int usecase_index = SC_USECASE_MASK(puc_key->usecase);
    chr_cnt += snprintf ( puc_key->pmeta_data_buf+chr_cnt, SCI_META_BUFSIZE,
                         "/$name=%s,formula=%s,unit=%s,ofmask=%d,$/}\n",
//                         usecase_name_table[puc_key->usecase],
                         usecase_name_table[usecase_index],
                         formula,
                         unit,
                         ofmask);

    puc_key->meta_data_byte_cnt = chr_cnt;

    if ( SCI_META_BUFSIZE < chr_cnt )
    {
        return SCI_ERR_STM;
    }

    return SCI_SUCCESS;
}


enum sci_err send_meta_data(psci_handle const phandle)
{
    eSTM_STATUS stm_retval = eSTM_SUCCESS;
    enum sci_err sci_retval = SCI_SUCCESS;
#ifdef _DEBUG
    if (NULL == phandle->pusecase_head)
       return SCI_ERR_STM;
    if (NULL == phandle->pstm_handle)
       return SCI_SUCCESS;
#endif


    struct sci_usecase_key_t * next = phandle->pusecase_head;
    while (NULL != next){
        /* Export meta data */
#if 1
        stm_retval = STMExport_putMeta(phandle->pstm_handle,
                                next->pmeta_data_buf,
                                next->meta_data_byte_cnt);
#else
        /* Export with a putMsg for debugging meta data */
        stm_retval = STMXport_putMsg(phandle->pstm_handle, 0,
                                next->pmeta_data_buf,
                                next->meta_data_byte_cnt);
#endif
        if ( eSTM_SUCCESS != stm_retval )
        {
            sci_retval = SCI_ERR_STM;
        }
        next = next->next;
    }
    return sci_retval;
}
#endif

void * get_cntr_addr( int mod, int cnt_index)
{
    return (void *)((uint32_t)(mod_map[mod]->vbase_addr)
                               + mod_map[mod]->cnt_map[cnt_index].cnt_offset);
}
void * get_filter_addr ( int mod, int cnt_index, int filter_index)
{
    switch (mod) {
    case SDRAM0:
    {
        /* Not that sdram_cnt_filter2 and sdram_cnt_filter1 are identical
         * except for the number of filter elements in the array so use the
         * largest to determine the address for all.
         */
        struct sdram_cnt_filter2 * cnt_addr;
        cnt_addr = (struct sdram_cnt_filter2 *)get_cntr_addr( mod, cnt_index);
        return (void *)&(cnt_addr->filter[filter_index]);
    }
    case LAT0:
    case LAT1:
    {
        struct lat_cnt_filter1 * cnt_addr;
        cnt_addr = (struct lat_cnt_filter1 *)get_cntr_addr( mod, cnt_index);
        return (void *)&(cnt_addr->filter[filter_index]);
    }
    };

    return NULL;
}

#if defined(_SC_VER_1_16)
int sys_to_phys_addr(int sys_addr)
{
    int i;

    int phys_addr;
    int phys_addr_mask;
    int sys_addr_msb;
    DMM_LISA_MAP reg;
    for(i=3;i>=0;i--)
    {
        int sys_addr_mask;
        mem_read(DMM_LISA_MAP_BASE+i*4, &reg.val);
        //check if we hit the good section
        sys_addr_mask = (1 << 8) - (1 << reg.sys_size);
        sys_addr_msb = (sys_addr >> 24) & 0x000000FF;
        if(reg.sys_addr == (sys_addr_msb & sys_addr_mask))
            break;
    }
    if(i<0)
    {
        printf("Error: can't find a section that hit by sys address\n");
        return 0xFFFFFFFF;
    }

    phys_addr_mask = (1 << reg.sys_size) -1;
    phys_addr_mask <<= 24;
    phys_addr_mask |= 0x00FFFFFF;
    sys_addr &= phys_addr_mask;

    //if interliving is enable
    if(reg.sdrc_intl != 0)
    {
        int tmp;
        //compute lower address
        phys_addr_mask = (1 << (reg.sdrc_intl + 6)) -1;
        phys_addr = sys_addr & phys_addr_mask;

        tmp = (sys_addr >> reg.sdrc_intl) & ~phys_addr_mask;
        phys_addr |= (tmp & (0xFFFFFFFF >> reg.sdrc_intl));
    }
    else
    {
        phys_addr = sys_addr;
    }

    phys_addr |= reg.sdrc_addr << 24;

    return phys_addr;
}
#endif

