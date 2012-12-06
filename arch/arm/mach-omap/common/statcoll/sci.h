/*
 * sci.h
 *
 * Statistic Collector Instrumentation Library 
 * - API Definitions
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

/*! \file sci.h
    CPT Library Function Prototypes
*/

/* The following defines the generic APIs. sci_dev.h contains
 * device specific definitions.
 */

#ifndef SCI_H
#define SCI_H

#include <stdlib.h>
#include <stdint.h>              // The library uses C99 exact-width integer types 
#include "sci_dev.h"

#if !defined(__bool_true_false_are_defined) && !defined(_STM_Logging)
typedef enum
{ 
    false = 0,
    true = 1
    
}bool;
#endif

#ifdef _STM_Logging
#include "StmLibrary.h"
#endif

/* Note - the version definitions must have the end of line immediately
 * after the value (packaging script requirement)
 */
#define SCILIB_MAJOR_VERSION (0x0)
                                    /*!< Major version number 
                                       - Incremented for API changes*/
#define SCILIB_MINOR_VERSION (0x2)
                                     /*!< Minor version number 
                                       - Incremented for bug fixes  */
                                       
/*! \par sci_handle
   sci handle object. This is an incomplete structure, thus making the actual
   implementation private to the library.
*/
typedef struct sci_handle_t sci_handle; 

/*! \par psci_handle
    Pointer to a sci handle object
*/
typedef sci_handle * psci_handle;

/*! \par sci_err
    SCILib error codes
*/
enum sci_err { 
   SCI_SUCCESS,                     /*!< Function completed with no errors */
   SCI_ERR_INVALID_HANDLE = -1,     /*!< Invalid sci handle */
   SCI_ERR_INVALID_PARM = -2,       /*!< Invalid function parameter */
   SCI_ERR_MAPPING = -3,            /*!< Memory mapping error */
   SCI_ERR_SC_NOT_AVAILABLE = -4,   /*!< SC module not avaiable */
   SCI_ERR_MEM_ALLOC = -5,          /*!< Memory allocation error */
   SCI_ERR_ACCESS = -6,             /*!< SC module access error */
   SCI_ERR_REVISION = -7,           /*!< SC module unexpected revision */
   SCI_ERR_MODULE_ENABLED = -8,     /*!< Module must be disabled for operation */
   SCI_ERR_STM = -9                 /*!< STM error */                
};

/*! \par sci_callback
     \param[in] phandle SCILib handle.
     \param[in] func   Constant char pointer to the function name, normally
                       provided by the compiler using the __FUNCTION__ macro.
     \param[in] ::sci_err_t error returned by calling routine
     
     Definition of the user implmented callback funtion. See ::sci_config. 
     
*/
typedef void(*sci_callback)(psci_handle phandle, const char * func, enum sci_err);

/*! \par sci_mode SCI Library operating mode. Allows user to select SC Module 
                  counter export mode.
 */
#ifdef _SC_VER_1_16
enum sci_mode { 
    SCI_MODE_STM,                   /*!< Export SC Module counters periodically 
                                         via STM (normal operating mode). */ 
    SCI_MODE_DUMP,                  /*!< Export SC Module counters on demand 
                                         via STM (see ::sci_dump()). */
    SCI_MODE_STM_COND,              /*!< Export SC Module counters conditionally
                                         via STM */ 
    SCI_MODE_DUMP_COND              /*!< Export SC Module counters conditionally
                                         on demand (see ::sci_dump()).
                                    */
};
#else
enum sci_mode {
    SCI_MODE_STM,                   /*!< Export SC Module counters periodically 
                                         via STM (normal operating mode). */ 
    SCI_MODE_DUMP                   /*!< Export SC Module counters on demand 
                                         via STM (see ::sci_dump() */
};
#endif

/*! \par sci_config SCI Library configuration structure. If sci_open()is called
                    with a NULL sci_config pointer then the default value for
                    each parameter is utilized.
 */
struct sci_config {
    sci_callback errhandler;        /*!< Called by any SCI Library function
                                    prior to returning an error. May be set to
                                    NULL to disable this feature. Default is NULL.
                                    */ 
    uint32_t sdram_msg_rate;        /*!< 32-bit non-zero value used to set the
                                    rate at which messages are generated (based
                                    on SC Module clock rate).
                                    Setting to 0 is not legal and will result
                                    in sci_open() returning ::SCI_ERR_INVALID_PARM.
                                    Default is the maximum value the module 
                                    supports. A value that is too large may cause
                                    counter saturation. Reducing this value may 
                                    reduce or eliminate saturation errors, and 
                                    will increase the data resolution. 
                                    */
    uint32_t mstr_msg_rate;        /*!< 32-bit non-zero value used to set the
                                    rate at which messages are generated (based
                                    on SC Module clock rate).
                                    Setting to 0 is not legal and will result
                                    in sci_open() returning ::SCI_ERR_INVALID_PARM.
                                    Default is the maximum value the module 
                                    supports. A value that is too large may cause
                                    counter saturation. Reducing this value may 
                                    reduce or eliminate saturation errors, and 
                                    will increase the data resolution. 
                                   */
    bool trigger_enable;           /*!< Cross triggers enable/disable. Default 
                                   is disable. If Enabled EMU0 trigger enables, 
                                   EMU1 trigger disables the SC module.
                                   */
    uint32_t data_options;         /*!< This is a bit field that enables sw
                                   filtering of certain data characteristics.
                                   Bit 0 - If 1 suppress zero data, if 0 don't
                                   suppress zero data. If a SC Module is
                                   enabled during cycles where no accesses
                                   are performed this option allows the zero
                                   data provided in these cases to be suppressed
                                   from the data provided on the host.
                                   This option will have no effect on the actual
                                   STM bandwidth (in other words all data is
                                   transmitted), but it may reduce host file
                                   sizes significantly and in some cases decrease
                                   data processing times.   
                                   */
    enum sci_mode mode;            /*!< See ::sci_mode */
    
#ifdef _STM_Logging
    bool stm_log_enable;           /*!< Enable/disable library generated STM 
                                   logging messages. The default is disabled */ 
    STMHandle * pstm_handle;       /*!< A pointer to a STM Handle for logging
                                   and providing meta data (required by host
                                   tools). The default is NULL.*/
    int stm_ch;                    /*!< A STM channel to use for SCI Library
                                   logging messages.
                                   */
#endif    
};
/*! \par sci_open         
    
    Open the SCI Library API. 
    
    \param[out] pphandle        A pointer to a NULL ::psci_handle. If sci_open
                                exits with a return value of ::SCI_SUCCESS,
                                the ::psci_handle pointer is set to a valid
                                sci handle object pointer.
    \param[in] pconfig          A pointer to a ::sci_config structure. 
                                If pconfig is NULL all parameters are set to
                                their default values. 
                                
    \return enum ::sci_err      See details for conditions that cause the
                                following errors:
                                \li ::SCI_SUCCESS
                                \li ::SCI_ERR_INVALID_HANDLE
                                \li ::SCI_ERR_INVALID_PARM
                                \li ::SCI_ERR_MEM_ALLOC
                                \li ::SCI_ERR_SC_NOT_AVAILABLE
                                \li ::SCI_ERR_REVISION
                                \li ::SCI_ERR_MAPPING
 
    \par Details:
    \details   
    
    This function must be called and return ::SCI_SUCCESS prior to calling any
    other SCI Library function that requires a ::psci_handle. 
    If this function is called with a non-NULL ppHandle pointer this function
    will exit and return ::SCI_ERR_INVALID_HANDLE.
    
    Any errors found with pconfig parameters will cause the function to exit
    and return ::SCI_ERR_INVALID_PARM.
     
    If the device's SC module is not compatible with this version of the
    library, this function will exit and return ::SCI_ERR_REVISION.
    
    The library will attempt to acquire ownsership of every SC module in the
    system. Under normal circumstances only those SC modules used by the kernel
    will not be avaiable, although the debugger can also own modules. If no
    modules are avaiable then this function will exit and 
    return ::SCI_ERR_SC_NOT_AVAILABLE.                 
    
    Storage for sci_handle is allocated through a call to the client provided
    external function cTools_memAlloc(). If a memory allocation error occurs
    this function will exit and returns ::SCI_ERR_MEM_ALLOC.
    cTools_memMap(), also a client provided function, is called to map the
    physical SC Module base address to a virtual address space. If a mapping
    error occurs this function exits returns ::SCI_ERR_MAPPING.    
    
    If there are no errors detected the function exits with ::SC_SUCCESS.  
    
    If pconfig is a NULL pointer, the default configuration parameters are:
        \li errhandler is NULL.
        \li pstm_handle is NULL.
        \li SC STM messsage rate is set to the max value.

*/
enum sci_err sci_open (psci_handle * const pphandle, 
                       struct sci_config * const pconfig);
/*! \par sci_close         
    
    Close the SCI Library API. 
    
    \param[out] pphandle        A pointer to a ::psci_handle.

    \return enum ::sci_err      See details for conditions that cause the
                                following errors:
                                \li ::SCI_SUCCESS
                                \li ::SCI_ERR_INVALID_HANDLE
    
    \par Details:
    \details  
                                
    This function must be called and return ::SCI_SUCCESS to release resources
    acquired with sci_open(). Any usecases that have not been removed, see
    sci_remove_usecase(),  will also be removed. 
    This function will also set the phandle pointed to by pphandle to NULL.
    If pphandle points to a NULL phandle this function
    will exit and return ::SCI_ERR_INVALID_HANDLE.                                
                                
*/
enum sci_err sci_close (psci_handle * const pphandle);

/*! \par sci_get_version         
    
    Get version information ofthe SCILib and SC module. 
    
    \param[out] phandle         A pointer to a handle provided by sci_open.
    \param[in] plib_major_ver   A pointer to the location used to store the
                                libraries major version number.
    \param[in] plib_minor_ver   A pointer to the location used to store the
                                libraries minor version number.
    \param[in] plib_func_id     A pointer to the location used to store the 
                                libraries functional id value.                                                          
    \param[in] pmod_func_id     A pointer to the location used to store the 
                                SC module's functional id value.

    \return enum ::sci_err      See details for conditions that cause the
                                following errors:
                                \li ::SCI_SUCCESS
                                \li ::SCI_ERR_ACCESS
                                \li ::SCI_ERR_REVISION
    
    \par Details:
    \details  
    
    This function assumes that all the SC modules  in a device are the same
    revision and func id, so it only looks at the first module sci_open
    aquired ownership for. This function will aquire the module's func id and
    it's type identifier. If either do not match the values expected
    for this device, this function will exit with ::SCI_ERR_REVISION.
    If no SC modules are accessible (owned by an other application or debugger)
    this function exits with ::SCI_ERR_ACCESS.
    
*/
enum sci_err sci_get_version (psci_handle const phandle, 
                              uint32_t * const plib_major_ver,
                              uint32_t * const plib_minor_ver,
                              uint32_t * const plib_func_id,
                              uint32_t * const pmod_func_id );
                                                  

/*! \par sci_sdram_usecase Selects for sdram usecases */

/* Note that the usecase enums are encoded. The LS 16 bits are the normal 
 * usecase enumeration, and the MS 16 bits is a compatibility code. If the
 * compatibility code is 0 the usecase is not compatible with any others.
 * Bits 8:15 indicate the module type the usecase can be applied to, where:
 * 0x00 is the SDRAM module
 * 0x01 is the LAT moule
 */  
 
enum sci_sdram_usecase { 
    SCI_SDRAM_THROUGHPUT = 0x00010000,          /*!< Throughput in bytes per 
                                                sample window usecase select */
    SCI_SDRAM_LINKOCCUPY_REQUEST = 0x00000001,  /*!< Request Port Link occupancy 
                                                percentage usecase select */
    SCI_SDRAM_LINKOCCUPY_RESPONSE = 0x00000002, /*!< Response Port Link occupancy
                                                percentage usecase select */
    SCI_SDRAM_AVGBURST_LENGTH = 0x00010003      /*!< Average burst length in
                                                bytes usecase select */
/* Since SDRAM does not support latency usecase must skip enum 0x00000004 */
#ifdef _SC_VER_1_16
    ,
    SCI_SDRAM_THROUGHPUT_MINALARM = 0x00000005, /*!< Throughput minimum alarm
                                                usecase */ 
    SCI_SDRAM_THROUGHPUT_MAXALARM = 0x00000006  /*!< Throughput maximum alarm
                                                usecase */
/* Since SDRAM does not support latency usecase must skip enum 0x00000007 */
#endif
 };

/*! \par sci_mstr_usecase Selects for master usecases */

enum sci_mstr_usecase { 
    SCI_MSTR_THROUGHPUT = 0x00010100,           /*!< Throughput in bytes per 
                                                sample window usecase select */
    SCI_MSTR_LINKOCCUPY_REQUEST = 0x00000101,   /*!< Request Port Link occupancy 
                                                percentage usecase select */
    SCI_MSTR_LINKOCCUPY_RESPONSE = 0x00000102,  /*!< Response Port Link occupancy
                                                percentage usecase select */
    SCI_MSTR_AVGBURST_LENGTH = 0x000010103,      /*!< Average burst length in
                                                bytes usecase select */
    SCI_MSTR_AVGLATENCY = 0x00000104            /*!< Average latency in
                                                cycles usecase select */
#ifdef _SC_VER_1_16
    ,
    SCI_MSTR_THROUGHPUT_MINALARM = 0x00000105,  /*!< Throughput minimum alarm
                                                usecase select*/                 
    SCI_MSTR_THROUGHPUT_MAXALARM = 0x00000106,  /*!< Throughput maximum alarm
                                                usecase select*/
    SCI_MSTR_LATENCY_MAXALARM  = 0x00000107     /*< Average latency maximum 
                                                alarm usecase select */
#endif
};

/*! \par sci_trans_qual Transaction qualification selects for both sdram and
                        master usecases.
*/                                        
enum sci_trans_qual {
    SCI_RD_ONLY,            /*!< Read transactions only */
    SCI_WR_ONLY,            /*!< Write transactions only */
    SCI_RD_OR_WR_NONE,      /*!< No read or write transactions - only errors*/
    SCI_RD_OR_WR_DONTCARE   /*!< Either read or write transactions*/
};

/*! \par sci_error_qual Error qualification selects for sdram and master
                        usecases.
*/
enum sci_error_qual {
    SCI_ERR_ONLY,           /*!< Error transactions only */
    SCI_ERR_NONE,           /*!< No error transactions */
    SCI_ERR_DONTCARE};      /*!< Error transactions don't care */

/*! \par sci_filter_sdram Filter configuration structure for sdram usecases */
struct sci_filter_sdram
{
    enum sci_master_addr  mstr_addr_match;  /*!< Master address match */
    uint32_t  mstr_addr_mask;               /*!< Master address mask */
    enum sci_trans_qual trans_qual;         /*!< Tranaction qualifier */
    enum sci_error_qual error_qual;         /*!< Error qualifier */
//#if _SC_VER_1_16
//    bool addr_filter_enable;                /*!< Probe address filter enable */
//    uint32_t addr_filter_max;               /*!< Probe address maximum */
//    uint32_t addr_filter_min;               /*!< Probe address minimum */
//#endif        
};

/*! \par sci_filter_mstr Filter configuration structure for master usecases */
struct sci_filter_mstr {
    enum sci_slave_addr  slave_addr_match;  /*!< Slave address match */
    uint32_t  slave_addr_mask;              /*!< Slave address mask */
    enum sci_trans_qual trans_qual;         /*!< Tranaction qualifier */
    enum sci_error_qual error_qual;         /*!< Error qualifier */
};

/*! \par sci_alarm Alarm configuration structure */
#ifdef _SC_VER_1_16
struct sci_alarm {
    uint32_t alarm_min;                     /*!< Minimum alarm threshold */
    uint32_t alarm_max;                     /*!< Maximum alarm threshold */
    bool alarm_msg_enable;                  /*!< Enable STM messages on alarm */
 };
#endif

/*! \par sci_config_sdram Configuration structure for sdram usecases */
struct sci_config_sdram {
    enum sci_sdram_usecase usecase;         /*!< sdram usecase selection */
    enum probeid_sdram probe_id;            /*!< sdram probe selection */
    int num_filters;                        /*!< Number of filters required
                                            for the usecase (0,1 or 2). */
    struct sci_filter_sdram filter[2];      /*!< sdram filters configuration*/
#ifdef _SC_VER_1_16
    bool addr_filter_enable;                /*!< Probe address filter enable */
    uint32_t addr_filter_min;               /*!< Probe address minimum */
    uint32_t addr_filter_max;               /*!< Probe address maximum */
    struct sci_alarm alarm;                 /*!< Alarm configuration */
#endif
};

/*! \par sci_config_mstr Configuration structure for master usecases */
struct sci_config_mstr {
    enum sci_mstr_usecase usecase;          /*!< Master usecase selection */
    enum probeid_mstr probe_id;             /*!< Master probe selection */
    int num_filters;                        /*!< Number of filters required
                                            for the usecase (0 or 1). */
    struct sci_filter_mstr filter;          /*!< Master filter configuration */
#if _SCI_VER_1_16
    struct sci_alarm alarm;                 /*!< Alarm configuration */
#endif
};

/*! \par sci_usecase_key Usecase key opaque structure */
typedef struct sci_usecase_key_t sci_usecase_key; 
/*! \par sci_usecase_key Usecase key structure pointer */
typedef sci_usecase_key * psci_usecase_key;

/*! \par sci_reg_usecase_sdram         
    
    Register a sdram usecase. 
    
    \param[in]  phandle         A pointer to a handle provided by sci_open.
    
    \param[in]  pcfg            A pointer to the sci_config_sdram structure
                                that defines this usecase.
                                
    \param[out] usecase_key     A pointer to a usecase_key pointer. The 
                                usecase_key pointer must be initialized
                                to NULL.                  

    \return enum ::sci_err      See details for conditions that cause the
                                following errors:
                                \li ::SCI_SUCCESS
                                \li ::SCI_ERR_INVALID_HANDLE
                                \li ::SCI_ERR_INVALID_PARM
                                \li ::SCI_ERR_MODULE_ENABLED
                                \li ::SCI_ERR_SC_NOT_AVAILABLE
                                \li ::SCI_ERR_MEM_ALLOC
    
    \par Details:
    \details  
                                
    This function registers use cases for the sdram Statistic Collectors. 
    If ::SCI_SUCCESS is returned the function successfully registered and
    programmed the usecase. This function may only be called if the module
    has not been enabled (see sci_global_enable())or has been disabled 
    (see sci_global_disable()).
    
    If the number of filters is set to zero a default filter is used
    (all filter masks set to 0 which enables all cycles, or in other words 
    disables all filtering).
    
    If phandle is NULL the function exots with ::SCI_ERR_INVALID_HANDLE.
    if pcfg is NULL or the usecase key pointer is not NULL this function will
    exit with ::SCI_ERR_INVALID_PARM.
    If this function is called while the modules are enabled this function
    exits with ::SCI_ERR_MODULE_ENABLED.
    If a statistic counter that meets the requirements of the usecase is not
    avaiable then this function exits with ::SCI_ERR_SC_NOT_AVAILABLE.
    If memory allocation for the usecase key fails the function exits with
    ::SCI_ERR_MEM_ALLOC.                               
                                
*/       
enum sci_err sci_reg_usecase_sdram(psci_handle const phandle, 
                        struct sci_config_sdram *  const pcfg,
                        psci_usecase_key * usecase_key );

/*! \par sci_reg_usecase_mstr         
    
    Register a master usecase. 
    
    \param[in] phandle          A pointer to a handle provided by sci_open.
    
    \param[in] pcfg             A pointer to the sci_config_sdram structure
                                that defines this usecase.
                                
    \param[out] usecase_key     A pointer to a usecase_key pointer. The 
                                usecase_key pointer must be initialized
                                to NULL.                  

    \return enum ::sci_err      See details for conditions that cause the
                                following errors:
                                \li ::SCI_SUCCESS
                                \li ::SCI_ERR_INVALID_HANDLE
                                \li ::SCI_ERR_INVALID_PARM
                                \li ::SCI_ERR_MODULE_ENABLED
                                \li ::SCI_ERR_SC_NOT_AVAILABLE
                                \li ::SCI_ERR_MEM_ALLOC
    
    \par Details:
    \details  
                                
    This function registers use cases for the master Statistic Collectors. 
    If ::SCI_SUCCESS is returned the function successfully registered and
    programmed the usecase. This function may only be called if the module
    has not been enabled (see sci_global_enable())or has been disabled 
    (see sci_global_disable()).

    If the number of filters is set to zero a default filter is used
    (all filter masks set to 0 which enables all cycles, or in other words 
    disables all filtering).
    
    If phandle is NULL the function exots with ::SCI_ERR_INVALID_HANDLE.
    if pcfg is NULL or the usecase key pointer is not NULL this function will
    exit with ::SCI_ERR_INVALID_PARM.
    If this function is called while the modules are enabled this function
    exits with ::SCI_ERR_MODULE_ENABLED.
    If a statistic counter that meets the requirements of the usecase is not
    avaiable then this function exits with ::SCI_ERR_SC_NOT_AVAILABLE.
    If memory allocation for the usecase key fails the function exits with
    ::SCI_ERR_MEM_ALLOC.                               
                                
*/      
enum sci_err sci_reg_usecase_mstr(psci_handle const phandle,
                        struct sci_config_mstr * const pcfg,
                        psci_usecase_key * usecase_key );

/*! \par sci_remove_usecase         
    
    Remove a registered sdram or master usecase. 
    
    \param[in] phandle          A pointer to a handle provided by sci_open.
                                
    \param[in] usecase_key      A usecase_key pointer.

    \return enum ::sci_err      See details for conditions that cause the
                                following errors:
                                \li ::SCI_SUCCESS
                                \li ::SCI_ERR_INVALID_HANDLE
                                \li ::SCI_ERR_INVALID_PARM
                                \li ::SCI_ERR_MODULE_ENABLED
    
    \par Details:
    \details  
                                
    This function removes a registered use case for the sdram or master
    Statistic Collectors. 
    If ::SCI_SUCCESS is returned the function successfully removed the
    registered usecase. 
    This function may only be called if the module has not been enabled
    (see sci_global_enable())or has been disabled (see sci_global_disable()).
    
    If phandle is NULL the function exits with ::SCI_ERR_INVALID_HANDLE.
    If this function is called while the modules are enabled this function
    exits with ::SCI_ERR_MODULE_ENABLED. 
    If this function is called with a NULL usecase_key it exits with
    ::SCI_ERR_INVALID_PARM.                                
*/
                        
enum sci_err sci_remove_usecase (psci_handle const phandle, 
                                 psci_usecase_key * usecase_key);

/*! \par sci_global_enable         
    
    Enabled all registered sdram and master usecase. 
    
    \param[in] phandle          A pointer to a handle provided by sci_open.

    \return enum ::sci_err      See details for conditions that cause the
                                following errors:
                                \li ::SCI_SUCCESS
                                \li ::SCI_ERR_INVALID_HANDLE
    
    \par Details:
    \details  
                                
    This function enables all registered use case and starts STM message 
    generation (per sci_mode parameter set with sci_open()).
    
    If phandle is NULL the function exits with ::SCI_ERR_INVALID_HANDLE.
                                
*/

enum sci_err sci_global_enable(psci_handle const phandle);

/*! \par sci_global_disable         
    
    Disable all registered sdram and master usecase. 
    
    \param[in] phandle          A pointer to a handle provided by sci_open.

    \return enum ::sci_err      See details for conditions that cause the
                                following errors:
                                \li ::SCI_SUCCESS
                                \li ::SCI_ERR_INVALID_HANDLE
    
    \par Details:
    \details  
                                
    This function disables all registered use case and terminates STM message 
    generation (per sci_mode parameter set with sci_open). 
    
    This function also causes meta data (data required for host post processing)
    to be broadcast through STMLib if pstm_handle is not null (see ::sci_config).
    If pstm_handle is null, then meta data will not be made avaiable for post
    processing and only the raw counter values will be displayed.
    
    If phandle is NULL the function exits with ::SCI_ERR_INVALID_HANDLE.
                                
*/
enum sci_err sci_global_disable(psci_handle const phandle);

/*! \par sci_dump        
    
    Manually dump the counters for each module that has use cases enabled.  
    
    \param[in] phandle          A pointer to a handle provided by sci_open.

    \return enum ::sci_err      See details for conditions that cause the
                                following errors:
                                \li ::SCI_SUCCESS
                                \li ::SCI_ERR_INVALID_HANDLE
    
    \par Details:
    \details  
                                
    This function maually dumps (verses allowing the statistic counters
    to be dumped to STM periodically) the counters out STM. If the 
    Library is opended in a dump mode then this function must be called
    to export the statistic counters out STM. If opened in STM mode this
    function has no effect.
    
    If phandle is NULL the function exits with ::SCI_ERR_INVALID_HANDLE.
                                
*/
                              
enum sci_err sci_dump(psci_handle const phandle );

#ifdef _SC_VER_1_16
/*! \par sci_dump_info        
    
    For the provided usecase_key retrive the number of statistic counters used. 
    
    \param[in] phandle          A pointer to a handle provided by sci_open.
        
    \param[in] usecase_key      usecase key.

    \param[out] pnum_sci_cntrs  Pointer to where the number of counters utilized
                                by the usecase is stored.

    \return enum ::sci_err      See details for conditions that cause the
                                following errors:
                                \li ::SCI_SUCCESS
                                \li ::SCI_ERR_INVALID_HANDLE
                                \li ::SCI_ERR_INVALID_PARM
    
    \par Details:
    \details  
                                
    This function retrives the number of counters used by a specific usecase.
    This information is needed by the client to provide a large enough
    uint32_t array (pbuf) to the sci_dump_cntrs function (see ::sci_dump).
    
    If phandle is NULL the function exits with ::SCI_ERR_INVALID_HANDLE.
    If usecase_key is NULL this function exits with ::SCI_ERR_INVALID_PARM.
                                
*/
enum sci_err sci_dump_info(psci_handle const phandle, 
                              psci_usecase_key usecase_key, 
                              int * pnum_sci_cntrs);


/*! \par sci_dump_cntrs        
    
    Manually dump the counters for the provided use case to a buffer.  
    
    \param[in] phandle          A pointer to a handle provided by sci_open.
        
    \param[in] usecase_key      usecase key.

    \param[in] num_sci_cntrs    Number of counters to store in pbuf. 
                                ( from ::sci_get_dumpinfo).
                                
    \param[out] pbuf             Pointer to the where this function stores the
                                statistic counters if pbuf is not NULL.

    \return enum ::sci_err      See details for conditions that cause the
                                following errors:
                                \li ::SCI_SUCCESS
                                \li ::SCI_ERR_INVALID_HANDLE
                                \li ::SCI_ERR_INVALID_PARM
    
    \par Details:
    \details  
                                
    This function retrives the counters used by a specific usecase.
    This information is provided to the client to provide a large enough
    uint32_t array for the sci_dump function (see ::sci_dump).
    
    If phandle is NULL the function exits with ::SCI_ERR_INVALID_HANDLE.
    If usecase_key is NULL this function exits with ::SCI_ERR_INVALID_PARM.
                                
*/                      
enum sci_err sci_dump_cntrs(psci_handle const phandle,
                      psci_usecase_key usecase_key,
                      int num_sci_cntrs, uint32_t * pbuf);

enum sci_err sci_dump_sdram_cntrs(int num_sci_cntrs, uint32_t * pbuf);


/*! \par sci_dump_disabled        
    
    For each module that has usecases enabled, disable STM message dumping.  
    
    \param[in] phandle          A pointer to a handle provided by sci_open.

    \return enum ::sci_err      See details for conditions that cause the
                                following errors:
                                \li ::SCI_SUCCESS
                                \li ::SCI_ERR_INVALID_HANDLE
    
    \par Details:
    \details  
                                
    This function disables STM message dumping for each statistic collector
    module that has a usecase registered for it.
    
    If phandle is NULL the function exits with ::SCI_ERR_INVALID_HANDLE.
                                
*/                      
enum sci_err sci_dump_disable(psci_handle const phandle);

/*! \par sci_dump_enabled        
    
    For each module that has usecases enabled, enable STM message dumping.  
    
    \param[in] phandle          A pointer to a handle provided by sci_open.

    \return enum ::sci_err      See details for conditions that cause the
                                following errors:
                                \li ::SCI_SUCCESS
                                \li ::SCI_ERR_INVALID_HANDLE
    
    \par Details:
    \details  
                                
    This function enables STM message dumping for each statistic collector
    module that has a usecase registered for it.
    
    If phandle is NULL the function exits with ::SCI_ERR_INVALID_HANDLE.
                                
*/ 
enum sci_err sci_dump_enable(psci_handle const phandle);
#endif
/*! \mainpage
    The Statistic Collector Instrumentation (SCI) Library provides a use case
    based programming API for the sdram and master Statistic Collector modules.
    A Statistic Collector provide bus statistics for the selected probe that
    can be fitered. Filtering parameters are dependent on the statistic collector
    type. Depending on the operating mode messages that contain the counter values
    can be export via STM peridocally or on demand (dump mode).

    \par Devices Supported
    Devices currently supported by the library are:
    \li OMAP4430
    \li OMAP4460
    \li OMAP5430
    
    \par CPT Library Revision History
    
<TABLE>
<TR><TD> Revision </TD> <TD>Date</TD> <TD>Notes</TD></TR>
<TR><TD> 0.0 </TD> <TD> 9/14/2011 </TD> <TD> Alpha, OMAP4430 validation only</TD>
<TR><TD> 0.1 </TD> <TD> 10/06/2011 </TD> <TD> Alpha, OMAP4430 and OMAP5430 validation. 
                                             Modified dump API from version 0.0. 
                                             Fixed Latency usecase bug. </TD>
</TABLE>
    
    \par Conventions
    The following public naming conventions are used by the API
    \li sci_ - Prefix for public CPT Library functions, structures and enumerations
    
    \par Build Notes
    SCILib supports the following pre-defined symbols that if defined
    enable the functionality at compile time.  

    \li _STM_Logging - If defined the SCILib will depend on the STMLib.

    \n Note - The minimum revision STMLib that supports SCILib meta data
    transport is version 3.1.

    The library must be configure for a specific device by providing at compile
    time one of the following pre-defined symbols:
    \li _OMAP4430
    \li _OMAP4460
    \li _OMAP5430
    \li SCI_VER_1_16 (note only valid for OAP4460 and OMAP5430 builds)  

    \par Directory Structure
    
    SCILib is a component of cTools so it resides within the cTools directory structure.
    
    @code
    
    |--cTools
       |
       |-- SCILib
       |   |
       |   |-- doc
       |   |   |
       |   |   |--sci_omap4430_html
       |   |   |--sci_omap4460_html
       |   |   |--sci_omap5430_html
       |   |      |
       |   |      |-index.html (Doxygen API documentation)
       |   |     
       |   |-- include  (Public API include file)
       |   |-- src      (Private .c and .h files )
       |   |-- projects (Target specific library builds)
       |       |
       |       |--omap4430_A9
       |       |--omap4460_A9
       |       |--omap5430_A15
       |-- Examples     (Target specific stand-alone example projects)
           |
           |--common    (files common across examples)
           |--OMAP4430
           |--OMAP5430  
    
     
    @endcode

    \par Helper Functions
    
    Helper functions allow the library to be ported easily to different
    operating environments without modifications to the library directly.
    Within the library these functions are declared extern so the library
    will build but can not be linked without implementations for the following
    helper functions:
    
    \li void * cTools_memAlloc(size_t sizeInBytes); \n\n
    If allocation successful returns pointer to allocated memory, else if not
    successful return NULL.
    
    \li void * cTools_memMap(unsigned int phyAddr, unsigned int mapSizeInBytes); \n\n
    Map a physical address to a virtual address space. Return the virtual pointer
    if successful, else return NULL. Return phyAddr if virtual mapping not required.   
    
    \li void cTools_memFree(void * ptr); \n\n
    Free the memory at the ptr (returned from cTools_memAlloc()) call. 
    
    \li void cTools_memUnMap(void * vAddr, unsigned int mapSizeInBytes); \n\n
    Unmap virtual address space starting at vAddr (returned from cTools_memMap())
    of mapSizeInBytes length. If virtual address mapping not required simply return.    
    
    \par CPT Export Notes
    The Statistic Collector STM messages are enabled by CCS when the STM module is
    connected by default. If you have modified the defaults you may need to enable
    the export of Statistic Collector STM messages through the CSS Breakpoint view by
    creating a Trace job with the following Trace Properties:
    \li Trace Type: System
    \li STM Trace Type: Trace Export Configuration
    \li Enable HW Message Sources:
    \li Message Source N: Statstic Collection
    
    If you are working remotely from CCS and using the ETB to capture STM data 
    then you must provide your own application code to enable the CPT module's STM messages. 

*/
#endif /*SCI_H*/
