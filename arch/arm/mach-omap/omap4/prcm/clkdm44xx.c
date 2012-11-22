/*
 *
 * @Component			OMAPCONF
 * @Filename			clkdm44xx.c
 * @Description			OMAP4 Clock Domain Definitions & Functions
 * @Author			Patrick Titiano (p-titiano@ti.com)
 * @Date			2011
 * @Copyright			Texas Instruments Incorporated
 *
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


#include <lib.h>
#include <clockdomain.h>
#include <clkdm44xx.h>
#include <cm44xx.h>
#include <prm44xx.h>
#include <string.h>
#include <stdio.h>
#include <cpuinfo.h>
#include <reg.h>


/* #define CLKDM44XX_DEBUG */
#ifdef CLKDM44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

static const char
	clkdm44xx_name_table[OMAP4_CD_ID_MAX][CLKDM44XX_MAX_NAME_LENGTH] = {
	"L4WKUP",
	"EMU",
	"MPU",
	"ABE",
	"IVAHD",
	"DSP",
	"ALWONCORE",
	"L4CFG",
	"C2C",
	"SDMA",
	"MPU_M3",
	"L3_1",
	"L3_2",
	"L3INSTR",
	"MEMIF",
	"STD_EFUSE",
	"CUST_EFUSE",
	"CAM",
	"DSS",
	"GFX",
	"L3INIT",
	"L4SEC",
	"L4PER",
	"NONE (PRCM)"};


static const pwrdm44xx_id clkdm44xx_partition_table[OMAP4_CD_ID_MAX] = {
	OMAP4_PD_WKUP,
	OMAP4_PD_EMU,
	OMAP4_PD_MPU,
	OMAP4_PD_ABE,
	OMAP4_PD_IVA_HD,
	OMAP4_PD_DSP,
	OMAP4_PD_ALWON_CORE,
	OMAP4_PD_CORE,
	OMAP4_PD_CORE,
	OMAP4_PD_CORE,
	OMAP4_PD_CORE,
	OMAP4_PD_CORE,
	OMAP4_PD_CORE,
	OMAP4_PD_CORE,
	OMAP4_PD_CORE,
	OMAP4_PD_STD_EFUSE,
	OMAP4_PD_CUST_EFUSE,
	OMAP4_PD_CAM,
	OMAP4_PD_DSS,
	OMAP4_PD_GFX,
	OMAP4_PD_L3_INIT,
	OMAP4_PD_L4_PER,
	OMAP4_PD_L4_PER};


static const unsigned int *
	clkdm44xx_cm_clkstctrl_addr_table[OMAP4_CD_ID_MAX] = {
	(unsigned int *) OMAP4430_CM_WKUP_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_EMU_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_MPU_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM1_ABE_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_IVAHD_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_DSP_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_ALWON_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_L4CFG_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_C2C_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_SDMA_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_MPU_M3_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_L3_1_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_L3_2_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_L3INSTR_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_MEMIF_CLKSTCTRL,
	NULL,
	(unsigned int *) OMAP4430_CM_CEFUSE_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_CAM_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_DSS_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_GFX_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_L3INIT_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_L4SEC_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_L4PER_CLKSTCTRL,
	NULL};


static unsigned short clkdm44xx_init_done = 0;
genlist clkdm44xx_list;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm44xx_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void clkdm44xx_init(void)
{
	clkdm_info clkdm;

	if (clkdm44xx_init_done)
		return;

	genlist_init(&clkdm44xx_list);

	/* FIXME */
	clkdm = clkdm;

	clkdm44xx_init_done = 1;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm44xx_deinit
 * @BRIEF		free dynamically allocated internal data.
 * @DESCRIPTION		free dynamically allocated internal data.
 *			MUST BE CALLED AT END OF EXECUTION.
 *//*------------------------------------------------------------------------ */
void clkdm44xx_deinit(void)
{
	if (clkdm44xx_init_done) {
		genlist_free(&clkdm44xx_list);
		clkdm44xx_init_done = 0;

	}
	dprintf("%s(): deinit done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm44xx_list_get
 * @BRIEF		return the list of clock domains
 * @RETURNS		list of clock domains in case of success
 *			NULL in case of error
 * @DESCRIPTION		return the list of clock domains
 *//*------------------------------------------------------------------------ */
const genlist *clkdm44xx_list_get(void)
{
	clkdm44xx_init();

	return (const genlist *) &clkdm44xx_list;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm44xx_count_get
 * @BRIEF		return the number of clock domains
 * @RETURNS		number of clock domains (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @DESCRIPTION		return the number of clock domains
 *//*------------------------------------------------------------------------ */
int clkdm44xx_count_get(void)
{
	int count;

	clkdm44xx_init();

	count = genlist_getcount(&clkdm44xx_list);

	dprintf("%s() = %d\n", __func__, count);
	return count;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm44xx_get_name
 * @BRIEF		return clock domain name
 * @RETURNS		clock domain name on success
 *			NULL in case of error
 * @param[in]		id: clock domain ID
 * @param[in,out]	name: clock domain name
 * @DESCRIPTION		return clock domain name
 *//*------------------------------------------------------------------------ */
char *clkdm44xx_get_name(clkdm44xx_id id, char name[CLKDM44XX_MAX_NAME_LENGTH])
{
	if ((id >= OMAP4_CD_ID_MAX) || (name == NULL))
		return NULL;
	else
		strcpy(name, clkdm44xx_name_table[id]);

	return name;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm44xx_get_pwrdm
 * @BRIEF		return the ID of the power domain a given
 *			clock domain is part of.
 * @RETURNS		power domain ID a given clock domain is part of
 *			(< OMAP4_PD_ID_MAX)
 *			OMAP4_PD_ID_MAX in case of error
 * @param[in]		id: clock domain ID
 * @DESCRIPTION		return the ID of the power domain a given
 *			clock domain is part of.
 *//*------------------------------------------------------------------------ */
pwrdm44xx_id clkdm44xx_get_pwrdm(clkdm44xx_id id)
{
	if (id >= OMAP4_CD_ID_MAX) {
		fprintf(stderr, "%s: id >= OMAP4_CD_ID_MAX!!!\n",
			__func__);
		return OMAP4_PD_ID_MAX;
	}

	return clkdm44xx_partition_table[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm44xx_get_voltdm
 * @BRIEF		return the ID of the voltage domain a given clock
 *			domain is part of.
 * @RETURNS		voltage domain ID a given clock domain is part of
 *			(< OMAP4_VD_ID_MAX)
 *			OMAP4_VD_ID_MAX in case of error
 * @param[in]		id: clock domain ID
 * @DESCRIPTION		return the ID of the voltage domain a given clock
 *			domain is part of.
 *//*------------------------------------------------------------------------ */
voltdm44xx_id clkdm44xx_get_voltdm(clkdm44xx_id id)
{
	return pwrdm44xx_get_voltdm(clkdm44xx_get_pwrdm(id));
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm44xx_get_status
 * @BRIEF		extract clock domain status from register
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 * @param[in]		cd_id: Clock Domain ID (= CLKDM_STATUS_MAX in case of
 *			error)
 * @param[in,out]	clkst: Clock Domain status (must be pre-allocated)
 * @DESCRIPTION		extract clock domain status from register
 *//*------------------------------------------------------------------------ */
int clkdm44xx_get_status(clkdm44xx_id cd_id, clkdm_status *clkst)
{
	unsigned int *cm_clkstctrl_addr;
	reg cm_clkstctrl;

	#ifdef CLKDM44XX_DEBUG
	char clkdm_name[CLKDM44XX_MAX_NAME_LENGTH];
	#endif

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(clkst, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(cd_id, OMAP4_CD_ID_MAX, OMAPCONF_ERR_ARG);
	*clkst = CLKDM_STATUS_MAX;


	/* Retrieve registers address */
	cm_clkstctrl_addr = (unsigned int *)
		clkdm44xx_cm_clkstctrl_addr_table[cd_id];
	if (cm_clkstctrl_addr == NULL) {
		dprintf("%s(%u (%s)): no CM_xyz_CLKSTCTRL register, "
			"return CLKDM_RUNNING\n", __func__,
			cd_id, clkdm44xx_get_name(cd_id, clkdm_name));
		*clkst = CLKDM_RUNNING;
		return 0;
	}

	strcpy(cm_clkstctrl.name, "DUMMY CM_CLKSTCTRL");
	cm_clkstctrl.addr = (unsigned int) cm_clkstctrl_addr;
	cm_clkstctrl.data = 0xDEADBEEF;
	cm_clkstctrl.data_valid = 0;
	*clkst = clkdm_status_get(&cm_clkstctrl);
	if (*clkst == CLKDM_STATUS_MAX)
		return OMAPCONF_ERR_ARG;
	else
		return 0;
}
