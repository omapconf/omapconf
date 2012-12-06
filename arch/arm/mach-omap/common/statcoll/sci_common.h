/*
 * sci_common.h
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

#ifndef SCI_COMMON_H
#define SCI_COMMON_H

#include <stdlib.h>
#include <stdint.h>

/* Statistic Collector register typedef */
typedef volatile uint32_t reg32_t;

/*
 * SC module sdram (OCP) and lat (NTTP) counter element structure definitions.
 * Note that these definitions are simply used for addressing purposes and
 * will not be used for defining specific bits per register.
*/



/*
 * sdram structure definitions
*/
struct sdram_filter {
#ifdef _SC_VER_1_12
        reg32_t en;
        reg32_t mask_mstaddr;
        reg32_t mask_rd;
        reg32_t mask_wr;
        reg32_t mask_err;
        reg32_t mask_reserved;
        reg32_t mask_userinfo;
        reg32_t match_mstaddr;
        reg32_t match_rd;
        reg32_t match_wr;
        reg32_t match_err;
        reg32_t match_reserved;
        reg32_t match_userinfo;
#endif
#ifdef _SC_VER_1_16
        reg32_t en;
        reg32_t mask_rd;
        reg32_t mask_wr;
        reg32_t mask_mstaddr;
        reg32_t reserved0;
        reg32_t mask_err;
        reg32_t mask_userinfo;
        reg32_t reserved1;
        reg32_t reserved2;
        reg32_t match_rd;
        reg32_t match_wr;
        reg32_t match_mstaddr;
        reg32_t reserved3;
        reg32_t match_err;
        reg32_t match_userinfo;
        reg32_t reserved4;
        reg32_t reserved5;
#endif
};

#ifdef _SC_VER_1_16
#define DMM_LISA_MAP_BASE 0x4e000040
typedef union DMM_LISA_MAP
{
    unsigned int val;
    struct {
        unsigned int sdrc_addr   :8;
        unsigned int sdrc_map    :2;
        unsigned int             :6;
        unsigned int sdrc_addrspc:2;
        unsigned int sdrc_intl   :2;
        unsigned int sys_size    :3;
        unsigned int             :1;
        unsigned int sys_addr    :8;
    };
}DMM_LISA_MAP;
#endif

// Counter with zero filter elements
struct sdram_cnt_filter0 {
        reg32_t globalen;
#ifdef _SC_VER_1_16
        reg32_t addrmin;
        reg32_t addrmax;
        reg32_t addren;
        reg32_t reserved0[77];
#endif
        reg32_t op_threshold_minval;
        reg32_t op_threshold_maxval;
        reg32_t op_evt_info_sel;
        reg32_t op_sel;
        reg32_t reserved;
};

// Counter with one filter elements
struct sdram_cnt_filter1 {
    reg32_t globalen;
#ifdef _SC_VER_1_16
    reg32_t addrmin;
    reg32_t addrmax;
    reg32_t addren;
#endif
    struct sdram_filter filter[1];
#ifdef _SC_VER_1_16
    reg32_t reserved0[60];
#endif
    reg32_t op_threshold_minval;
    reg32_t op_threshold_maxval;
    reg32_t op_evt_info_sel;
    reg32_t op_sel;
    reg32_t reserved;
};

// Counter with two filter elements
struct sdram_cnt_filter2 {
    reg32_t globalen;
#ifdef _SC_VER_1_16
    reg32_t addrmin;
    reg32_t addrmax;
    reg32_t addren;
#endif
    struct sdram_filter filter[2];
#ifdef _SC_VER_1_16
    reg32_t reserved0[43];
#endif
    reg32_t op_threshold_minval;
    reg32_t op_threshold_maxval;
    reg32_t op_evt_info_sel;
    reg32_t op_sel;
    reg32_t reserved1;
};

/*
 * NTTP mapping structure definitions
*/

struct lat_filter {
#ifdef _SC_VER_1_12
        reg32_t en;
        reg32_t mask_mstaddr;
        reg32_t mask_requserinfo;
        reg32_t mask_rspuserinfo;
        reg32_t mask_rd;
        reg32_t mask_wr;
        reg32_t mask_err;
        reg32_t mask_slvaddr;
        reg32_t match_mstaddr;
        reg32_t match_requserinfo;
        reg32_t match_rspuserinfo;
        reg32_t match_rd;
        reg32_t match_wr;
        reg32_t match_err;
        reg32_t match_slvaddr;
#endif
#ifdef _SC_VER_1_16
        reg32_t en;
        reg32_t mask_rd;
        reg32_t mask_wr;
        reg32_t mask_mstaddr;
        reg32_t mask_slvaddr;
        reg32_t mask_err;
        reg32_t mask_requserinfo;
        reg32_t mask_rspuserinfo;
        reg32_t reserved0;
        reg32_t match_rd;
        reg32_t match_wr;
        reg32_t match_mstaddr;
        reg32_t match_slvaddr;
        reg32_t match_err;
        reg32_t match_requserinfo;
        reg32_t match_rspuserinfo;
        reg32_t reserved1;
#endif
};

/* Counter with one filter elements */
struct lat_cnt_filter1 {
    reg32_t globalen;
#ifdef _SC_VER_1_16
    reg32_t reserved0;
    reg32_t reserved1;
    reg32_t reserved2;
#endif
    struct lat_filter filter[1];
#ifdef _SC_VER_1_16
    reg32_t reserved3[60];
#endif
    reg32_t op_threshold_minval;
    reg32_t op_threshold_maxval;
    reg32_t op_evt_info_sel;
    reg32_t op_sel;
    reg32_t reserved4;
};

/*
 * Register definitions
 *
 */
#define SC_REQUEST_PROBE        0x0
#define SC_RESPONSE_PROBE       0x1


#define SC_EVENT_SEL_NONE     0x0 /* No event selected */
#define SC_EVENT_SEL_ANY      0x1 /* Any clock cycles */
#define SC_EVENT_SEL_TRANSFER 0x2 /* Header, necker or data has been accepted by the receiver */
#define SC_EVENT_SEL_WAIT     0x3 /* Transfer initiated but the transmitter has no data to send */
#define SC_EVENT_SEL_BUSY     0x4 /* Receiver applies flow control */
#define SC_EVENT_SEL_PKT      0x5 /* Transfer of a new packet header */
#define SC_EVENT_SEL_DATA     0x6 /* Transfer of a payload word
                                     *   Request link: Store data
                                     *   Respose link: Load data
                                     */
#define SC_EVENT_SEL_IDLE     0x7 /* No communication over the link */
#define SC_EVENT_SEL_LATENCY  0x8 /* Debug bit detection */

/* If op_sel set to MIN_MAX_HIT or EVT_INFO then evt_info_sel applies */
#define SC_EVTINFOSEL_BYTELEN   0x0 /* Length of transfer in bytes */
#define SC_EVTINFOSEL_PRESSURE  0x1 /* Pressure */
#define SC_EVTINFOSEL_LATENCY   0x2 /* Amount of wait time */

/* op_sel determines how the counter functions */
#define SC_OPSEL_FILTER_HIT     0x0 /* Counter increments on a filter hit */
#define SC_OPSEL_MINMAX_HIT     0x1 /* Counter increments when the filter hits
                                     * and the selected event info is in range
                                     * (Min threshold <= Evt_Info <= Max threshold)
                                     */
#define SC_OPSEL_EVT_INFO       0x2 /* Selected Evt_Info added to the counter value
                                     * when the filter hits
                                     */
#define SC_OPSEL_AND_FILTER     0x3 /* Counter increments by one when all unit
                                     * filters hit.
                                     */
#define SC_OPSEL_OR_FILTER      0x4 /* Counter increments by one when at least
                                     * one unit filters hits.
                                     */
#define SC_OPSEL_SUM_REQ_EVT    0x5 /* Counter sums the events from any request
                                     * port.
                                     */
#define SC_OPSEL_SUM_RSP_EVT    0x6 /* Counter sums the events from any response
                                     * port.
                                     */
#define SC_OPSEL_SUM_ALL_EVT    0x7 /* Counter sums the events from any request
                                     * and response ports.
                                     */
#define SC_OPSEL_EX_EVT         0x8 /* Counter increments by one when the selected
                                     * ExtEvt input signal is sampled high
                                     */


/*
 * Generic mapping structure definitions
*/

enum sci_module_type {SDRAM, MSTR};

struct cnt_elements {
    bool used;
    int num_filters;
    uint32_t cnt_offset;
};

//TODO seprate into two structures, constants and modifiable
struct mod_element_map {
        enum sci_module_type mod_type;
        uint32_t base_addr;
        uint32_t * vbase_addr;
        bool owner;
        int usecase;                    /* First use case - used for compatibility testing */
        int usecase_cnt;                /* Number of use case jobs attached */
        int mod_size;                   /* In bytes */
        int num_counters;
        struct cnt_elements * cnt_map;
        int num_ports;
        int * port_map;
};

#ifdef _STM_Logging
/* The following are common strings and tables shared between all device types */

/* Trasaction type names */
const char trans_type_rd[] = "Rd";
const char trans_type_wr[] = "Wr";
const char trans_type_none[] = "RdWrNone";
const char trans_type_dontcare[] = "RdWrDontCare";

/* Use sci_trans_qual to select */
const char * trans_type_table[] = { trans_type_rd,
                                    trans_type_wr,
                                    trans_type_none,
                                    trans_type_dontcare};



/* Usecase enums for sdram and mstr sc module types are identical
    0 SCI_SDRAM_THROUGHPUT,                    SCI_MSTR_THROUGHPUT
    1 SCI_SDRAM_LINKOCCUPY_REQUEST,            SCI_MSTR_LINKOCCUPY_REQUEST
    2 SCI_SDRAM_LINKOCCUPY_RESPONSE,           SCI_MSTR_LINKOCCUPY_RESPONSE
    3 SCI_SDRAM_AVGBURST_LENGTH,               SCI_MSTR_AVGBURST_LENGTH
    4 SCI_SDRAM_AVGLATENCY_NOT_SUPPORTED       SCI_MSTR_AVGLATENCY
#if SCI_VER_1_16
    5 SCI_SDRAM_THROUGHPUT_MINALARM,           SCI_MSTR_THROUGHPUT_MINALARM
    6 SCI_SDRAM_THROUGHPUT_MAXALARM,           SCI_MSTR_THROUGHPUT_MAXALARM
    7 SCI_SDRAM_LATENCY_MAXALARM_NOT_SUPPORTED SCI_MSTR_LATENCY_MAXALARM
#endif
*/
const char usecase_name_tp[]  = "ThroughPut per Sampling Period";
const char usecase_name_reslo[] ="Request Port Link Occupancy";
const char usecase_name_rsplo[] ="Response Port Link Occupancy";
const char uusecase_name_abl[] = "Average Burst Length";
const char uusecase_name_ald[] = "Average Latency Distribution";
const char uusecase_name_tpmax[]  = "ThroughPut per Sample Period - Max Alarm";
const char uusecase_name_tpmin[]  = "ThroughPut per Sample Period - Min Alarm";
const char uusecase_name_aldmax[]  = "Average Latency - Max Alarm";

/* Use usecaseid to index */
const char * usecase_name_table[] = {
     usecase_name_tp,
     usecase_name_reslo,
     usecase_name_rsplo,
     uusecase_name_abl,
     uusecase_name_ald,
     uusecase_name_tpmax,
     uusecase_name_tpmin,
     uusecase_name_aldmax
};

/* Counter names */
const char cntr_name_payload[]= "Payload Length";
const char cntr_name_idle[] = "Idle";
const char cntr_name_packcnt[] = "Packet Count";
const char cntr_name_latcyc[] = "Latency Cycle Count";
const char cntr_name_lattrans[] = "Latency Transaction Count";

const int usecase_formula_table[] = {2,3,3,1,9,2,2,9};

const char usecase_units_bytesperpacket[] = "Bytes/Packet";
const char usecase_units_bytesperwindow[] = "Bytes/Sample Window";
const char usecase_units_percent[] ="%";
const char usecase_units_cyclespertrans[] = "Cycles/Transaction";

#define SCI_META_BUFSIZE 256

#endif //End of _STM_Logging

/*                                      TP      LOREQ   LORESP  ABL     AL      TA+      TA-    LA
 *      TP - Throughput                 true    false   false   true    false   false    false  false
 *      LOREQ - Link Occupancy Request  false   true    false   false   false   false    false  false
 *      LORSP - Link Occupancy Respose  false   false   true    false   false   false    false  false
 *      ABL- Average burst length       true    false   false   true    false   false     false  false
 *      AL - Average latency            false   false   false   false   true    false    false  false
 *      TA+ - Throughput Alarm Max      false   false   false   false   false   true     false  false
 *      TA- - Throughput Alarm Min      false   false   false   false   false   false    true    false
 *      LA - Latency alarm              false   false   false   false    false   false    false   true
 */
#if 0
bool usecase_compat_table[8][8] = { true, false, false, true, false, false, false, false,
                                    false, true, false, false, false, false, false, false,
                                    false, false, true, false, false, false, false, false,
                                    true, false, false, true, false, false, false, false,
                                    false, false, false, false, true, false, true, false,
                                    false, false, false, false, false, true, false, false,
                                    false, false, false, false, false, false, true, false,
                                    false, false, false, false, false, false, false, true};
#endif


#define SC_GET_USECASE_COMPAT_VALUE(n) ((n) >> 16)
#define SC_USECASE_MASK(n)             ((n) & 0x000000FF)

#define SC_MOD_TYPE (0x003A0001)     /* Identifies the module as a SC Module */

#define GET_SCMOD_FUNC(n) ((n) >> 24)

/*
 * The following are device specific internel definitions
 */

/*****************************************************************************/
/* OMAP4430 and OMAP4460 specific definitions                                */
/*****************************************************************************/
#if defined(_OMAP4430) || defined(_OMAP4460)

#define SC_SDRAM_BASE 0x45000400 /* sdram sc module base address */
#define SC_LAT0_BASE 0x45000600
#define SC_LAT1_BASE 0x45000800

#define SC_LIB_FUNC (0x0)   /* SC Module ID this library
                                       is compatible with  */
const uint32_t mod_func_ver[] = { 0x0, 0x0, 0x0 };

#define SC_SDRAM_NUM_CNTRS 5     /* sdram number of counter elements */
#define SC_SDRAM_NUM_PROBES 2

// LAT0 and LAT1 have identical register mappings

#define SC_LAT_NUM_CNTRS 4
#define SC_LAT0_NUM_PROBES 6
#define SC_LAT1_NUM_PROBES 5

/* This struct discribes the sdram SC Module address space*/
struct sc_sdram_regs {
        reg32_t stdhosthdr_core;
        reg32_t stdhosthdr_version;
        reg32_t en;
        reg32_t soften;
        reg32_t trigen;
        reg32_t reqevt;
        reg32_t rspevt;
        reg32_t evtmux_sel[SC_SDRAM_NUM_CNTRS];
        reg32_t dump_identifier;
        reg32_t dump_collecttime;
        reg32_t dump_slvaddr;
        reg32_t dump_mstaddr;
        reg32_t dump_slvofs;
        reg32_t dump_manual;
        reg32_t dump_send;
#ifdef _SC_VER_1_16
        reg32_t dump_disable;
        reg32_t dump_alarm_trig;
        reg32_t dump_alarm_minval;
        reg32_t dump_alarm_maxval;
        reg32_t dump_alarm_mode[SC_SDRAM_NUM_CNTRS];
        reg32_t dump_cnt[SC_SDRAM_NUM_CNTRS];
#endif
        // Note that the fitler mapping is device dependent - so use mod_element_map to access
        struct sdram_cnt_filter2 cnt0;
        struct sdram_cnt_filter1 cnt1;
        struct sdram_cnt_filter2 cnt2;
        struct sdram_cnt_filter1 cnt3;
        struct sdram_cnt_filter0 cnt4;
};


struct cnt_elements sdram_cnt_map[] = {
        false, 2, (uint32_t)(&((struct sc_sdram_regs *)0)->cnt0),
        false, 1, (uint32_t)(&((struct sc_sdram_regs *)0)->cnt1),
        false, 2, (uint32_t)(&((struct sc_sdram_regs *)0)->cnt2),
        false, 1, (uint32_t)(&((struct sc_sdram_regs *)0)->cnt3),
        false, 0, (uint32_t)(&((struct sc_sdram_regs *)0)->cnt4)
};

/*
 * The request port number is the index*2,
 * the respose port number is the index*2 +1
 */
int sdram_probe_map[] = { SCI_EMIF1,
                          SCI_EMIF2
};

struct mod_element_map mod_sdram_map = { SDRAM,
                                        SC_SDRAM_BASE,
                                        NULL,
                                        false,
                                        -1,
                                        0,
                                        sizeof(struct sc_sdram_regs),
                                        SC_SDRAM_NUM_CNTRS,
                                        sdram_cnt_map,
                                        SC_SDRAM_NUM_CNTRS,
                                        sdram_probe_map
};


struct sc_lat_regs {
        reg32_t stdhosthdr_core;
        reg32_t stdhosthdr_version;
        reg32_t en;
        reg32_t soften;
        reg32_t trigen;
        reg32_t reqevt;
        reg32_t rspevt;
        reg32_t evtmux_sel[SC_LAT_NUM_CNTRS];
        reg32_t dump_identifier;
        reg32_t dump_collecttime;
        reg32_t dump_slvaddr;
        reg32_t dump_mstaddr;
        reg32_t dump_slvofs;
        reg32_t dump_manual;
        reg32_t dump_send;
#ifdef _SC_VER_1_16
        reg32_t dump_disable;
        reg32_t dump_alarm_trig;
        reg32_t dump_alarm_minval;
        reg32_t dump_alarm_maxval;
        reg32_t dump_alarm_mode[SC_LAT_NUM_CNTRS];
        reg32_t dump_cnt[SC_LAT_NUM_CNTRS];
#endif
        // Note that the fitler mapping is device dependent - so use mod_element_map to access
        struct lat_cnt_filter1 cnt[4];
};


struct cnt_elements lat_cnt_map[] = {
        false, 1, (uint32_t)(&((struct sc_lat_regs *)0)->cnt[0]),
        false, 1, (uint32_t)(&((struct sc_lat_regs *)0)->cnt[1]),
        false, 1, (uint32_t)(&((struct sc_lat_regs *)0)->cnt[2]),
        false, 1, (uint32_t)(&((struct sc_lat_regs *)0)->cnt[3]),
};

/*
 * The request port number is the index*2,
 * the respose port number is the index*2 +1
 */
int lat0_probe_map[] = { SCI_MODENA,
                         SCI_TESLA,
                         SCI_SDMA_RD,
                         SCI_SDMA_WR,
                         SCI_DSS,
                         SCI_ISS,
};

int lat1_probe_map[] = { SCI_IVAHD,
                         SCI_MODENA,
                         SCI_SDMA_WR,
                         SCI_SGX,
                         SCI_DUCATI
};

struct mod_element_map mod_lat0_map = { MSTR,
                                        SC_LAT0_BASE,
                                        NULL,
                                        false,
                                        -1,
                                        0,
                                        sizeof(struct sc_lat_regs),
                                        SC_LAT_NUM_CNTRS,
                                        lat_cnt_map,
                                        SC_LAT0_NUM_PROBES,
                                        lat0_probe_map
};

struct mod_element_map mod_lat1_map = { MSTR,
                                        SC_LAT1_BASE,
                                        NULL,
                                        false,
                                        -1,
                                        0,
                                        sizeof(struct sc_lat_regs),
                                        SC_LAT_NUM_CNTRS,
                                        lat_cnt_map,
                                        SC_LAT1_NUM_PROBES,
                                        lat1_probe_map
};

enum module_id {SDRAM0, LAT0, LAT1} module_id;
struct mod_element_map * mod_map[] = { &mod_sdram_map, &mod_lat0_map, &mod_lat1_map };
//TODO confirm counter widths are correct
const int cnt_overflow_norm[] = {65535-32, 4096-128, 4096-128};
const int cnt_overflow_lat[] = {0, 1023-32, 1023-32};

const int mod_cnt = sizeof mod_map/sizeof mod_map[0];

#ifdef _STM_Logging
/*
 * The following are required for meta data generation
 */

/* Module names */
const char module_name_sdram[] = "SDRAM";
const char module_name_lat0[] = "LAT0";
const char module_name_lat1[] = "LAT1";

/* Use module number to index */
const char * module_name_table[] = {module_name_sdram,
                                   module_name_lat0,
                                   module_name_lat1};
/* SDRAM probe names */
const char probe_name_emif0[] = "EMIF1";
const char probe_name_emif1[] = "EMIF2";

/*Use sdram probe id to index */
const char * sdram_probe_name_table[] = { probe_name_emif0,
                                         probe_name_emif1};
/* MSTR probe names */
const char probe_name_mstr_mod[] = "MODENA";
const char probe_name_mstr_tes[] = "TESLA";
const char probe_name_mstr_sdmard[] = "SDMA_RD";
const char probe_name_mstr_sdmawr[] = "SDMA_WR";
const char probe_name_mstr_dss[] = "DSS";
const char probe_name_mstr_iss[] = "ISS";
const char probe_name_mstr_ivahd[] = "IVAHD";
const char probe_name_mstr_sgx[] = "SGX";
const char probe_name_mstr_duc[] = "DUCATI";

/* Use mastr probe id to index */
const char * mstr_probe_name_table[] = {probe_name_mstr_mod,
                                        probe_name_mstr_tes,
                                        probe_name_mstr_sdmard,
                                        probe_name_mstr_sdmawr,
                                        probe_name_mstr_dss,
                                        probe_name_mstr_iss,
                                        probe_name_mstr_ivahd,
                                        probe_name_mstr_sgx,
                                        probe_name_mstr_duc};


/* Master addr names */
const char master_name_mpuss[] = "MPUSS";
const char master_name_dap[] = "DAP";
const char master_name_ieee1500[] = "IEEE1500";
const char master_name_tesla[] = "Tesla";
const char master_name_ivahd[] = "IVAHD";
const char master_name_iss[] = "ISS";
const char master_name_ducati[] = "Ducati";
const char master_name_face[] = "Face Detect (SMP)";
const char master_name_sdramrd[] = "sDMA_RD";
const char master_name_sdramwr[] = "sDMA_WR";
const char master_name_sgx[] = "SGX";
const char master_name_dss[] = "DSS";
const char master_name_sad2d[] = "SAD2D (SMP)";
const char master_name_hsi[] = "HSI";
const char master_name_mmc1[] = "MMC1";
const char master_name_mmc2[] = "MMC2";
const char master_name_mmc6[] = "MMC6 (MDI)";
const char master_name_unipro[] = "UNIPRO1";
const char master_name_usbhost[] = "USB Host HS";
const char master_name_usbotghs[] = "USB OTG HS";
const char master_name_usbhostfs[] = "USB HOST FS (SMP)";

/* Use enum sci_master_addr >> 2 to index */
const char * master_name_table[] = {
    master_name_mpuss,      /* 0x00 */
    NULL,
    NULL,
    NULL,
    master_name_dap,        /* 0x04 */
    master_name_ieee1500,   /* 0x05 */
    NULL,
    NULL,
    master_name_tesla,      /* 0x08 */
    NULL,
    NULL,
    NULL,
    master_name_ivahd,      /* 0x0C */
    NULL,
    NULL,
    NULL,
    master_name_iss,        /* 0x10 */
    master_name_ducati,     /* 0x11 */
    master_name_face,       /* 0x12 */
    NULL,
    master_name_sdramrd,    /* 0x14 */
    master_name_sdramwr,    /* 0x15 */
    NULL,
    NULL,
    master_name_sgx,        /* 0x18 */
    NULL,
    NULL,
    NULL,
    master_name_dss,        /* 0x1C */
    NULL,
    NULL,
    NULL,
    master_name_sad2d,      /* 0x20 */
    NULL,
    NULL,
    NULL,
    master_name_hsi,        /* 0x24 */
    NULL,
    NULL,
    NULL,
    master_name_mmc1,       /* 0x28 */
    master_name_mmc2,       /* 0x29 */
    master_name_mmc6,       /* 0x2A */
    NULL,
    NULL,
    NULL,
    master_name_unipro,     /* 0x2C */
    NULL,
    NULL,
    NULL,
    master_name_usbhost,    /* 0x30 */
    master_name_usbotghs,   /* 0x31 */
    master_name_usbhostfs   /* 0x32 */
};

/* Slave addr names */
const char slave_name_hostclk1[] = "Host CLK1";
const char slave_name_dmm1[] = "DMM1 - NIU";
const char slave_name_dmm2[] = "DMM2 - NIU (SMP)";
const char slave_name_abe[] = "ABE - NIU";
const char slave_name_l4cfg[] = "L4CFG - NIU";
/* hole */
const char slave_name_hostclk2[] = "Host CLK2";
const char slave_name_gpmc[] = "GPMC - NIU";
const char slave_name_ocmram[] = "OCMRAM - NIU";
const char slave_name_dss[] = "DSS - NIU";
const char slave_name_iss[] = "ISS - NIU";
const char slave_name_ducati[] = "Ducati - NIU";
const char slave_name_sgx[] = "SGX - NIU";
const char slave_name_ivahd[] = "IVAHD - NIU";
const char slave_name_sl2[] = "SL2 - NIU";
const char slave_name_l4per0[] = "L4PER0 - NIU";
const char slave_name_l4per1[] = "L4PER1 - NIU";
const char slave_name_l4per2[] = "L4PER2 - NIU";
const char slave_name_l4per3[] = "L4PER3 - NIU";
const char slave_name_aes1[] = "AES1 - NIU";
const char slave_name_aes2[] = "AES2 - NIU";
const char slave_name_sha1[] = "SHA1 - NIU";
const char slave_name_mod[] = "Modem (MID)";
/*hole*/
const char slave_name_hostclk3[] = "Host CLK3";
const char slave_name_dbgss[] = "DebugSS - NIU";

const char * slave_name_table[] = {
    slave_name_hostclk1,
    slave_name_dmm1,
    slave_name_dmm2,
    slave_name_abe,
    slave_name_l4cfg,
    NULL,
    slave_name_hostclk2,
    slave_name_gpmc,
    slave_name_ocmram,
    slave_name_dss,
    slave_name_iss,
    slave_name_ducati,
    slave_name_sgx,
    slave_name_ivahd,
    slave_name_sl2,
    slave_name_l4per0,
    slave_name_l4per1,
    slave_name_l4per2,
    slave_name_l4per3,
    slave_name_aes1,
    slave_name_aes2,
    slave_name_sha1,
    slave_name_mod,
    NULL,
    slave_name_hostclk3,
    slave_name_dbgss
};


#endif //End of _STM_Logging

#endif /* End of _OMAP4430 */

#if defined(_OMAP5430) || defined(_OMAP4470)
/*****************************************************************************/
/* OMAP5430 specific definitions                                             */
/*****************************************************************************/
#define SC_SDRAM_BASE 0x45001000 /* sdram sc module base address */
#define SC_LAT0_BASE 0x45002000
#define SC_LAT1_BASE 0x45003000

const uint32_t mod_func_ver[] = { 0x1, 0x1, 0x1 };
#define SC_LIB_FUNC (0x1)   /* SC Module ID this library
                                       is compatible with  */

#define SC_SDRAM_NUM_CNTRS 8     /* sdram number of counter elements */
#define SC_SDRAM_NUM_PROBES 5

// LAT0 and LAT1 have identical register mappings

#define SC_LAT_NUM_CNTRS 4
#define SC_LAT0_NUM_PROBES 7
#define SC_LAT1_NUM_PROBES 5

/* This struct discribes the sdram SC Module address space*/
struct sc_sdram_regs {
        reg32_t stdhosthdr_core;
        reg32_t stdhosthdr_version;
        reg32_t en;
        reg32_t soften;
#ifdef _SC_VER_1_16
        reg32_t ignore_suspend;
#endif
        reg32_t trigen;
        reg32_t reqevt;
        reg32_t rspevt;
        reg32_t evtmux_sel[SC_SDRAM_NUM_CNTRS];
        reg32_t dump_identifier;
        reg32_t dump_collecttime;
        reg32_t dump_slvaddr;
        reg32_t dump_mstaddr;
        reg32_t dump_slvofs;
        reg32_t dump_manual;    /* dump_mode for version 1.16 */
        reg32_t dump_send;
#ifdef _SC_VER_1_16
        reg32_t dump_disable;
        reg32_t dump_alarm_trig;
        reg32_t dump_alarm_minval;
        reg32_t dump_alarm_maxval;
        reg32_t dump_alarm_mode[SC_SDRAM_NUM_CNTRS];
        reg32_t dump_cnt[SC_SDRAM_NUM_CNTRS];
#endif
        // Note that the fitler mapping is device dependent - so use mod_element_map to access
        struct sdram_cnt_filter2 cnt0;
        struct sdram_cnt_filter1 cnt1;
        struct sdram_cnt_filter2 cnt2;
        struct sdram_cnt_filter1 cnt3;
        struct sdram_cnt_filter1 cnt4;
        struct sdram_cnt_filter1 cnt5;
        struct sdram_cnt_filter0 cnt6;
        struct sdram_cnt_filter0 cnt7;
};


struct cnt_elements sdram_cnt_map[] = {
	{false, 2, (uint32_t)(&((struct sc_sdram_regs *)0)->cnt0)},
	{false, 1, (uint32_t)(&((struct sc_sdram_regs *)0)->cnt1)},
	{false, 2, (uint32_t)(&((struct sc_sdram_regs *)0)->cnt2)},
	{false, 1, (uint32_t)(&((struct sc_sdram_regs *)0)->cnt3)},
	{false, 1, (uint32_t)(&((struct sc_sdram_regs *)0)->cnt4)},
	{false, 1, (uint32_t)(&((struct sc_sdram_regs *)0)->cnt5)},
	{false, 0, (uint32_t)(&((struct sc_sdram_regs *)0)->cnt6)},
	{false, 0, (uint32_t)(&((struct sc_sdram_regs *)0)->cnt7)} };

/*
 * The request port number is the index*2,
 * the respose port number is the index*2 +1
 */
int sdram_probe_map[] = { SCI_EMIF1,
                          SCI_EMIF2,
                          SCI_MA_MPU_P1,
                          SCI_MA_MPU_P2,
                          SCI_EMIF_LL
};

struct mod_element_map mod_sdram_map = { SDRAM,
                                        SC_SDRAM_BASE,
                                        NULL,
                                        false,
                                        -1,
                                        0,
                                        sizeof(struct sc_sdram_regs),
                                        SC_SDRAM_NUM_CNTRS,
                                        sdram_cnt_map,
                                        SC_SDRAM_NUM_CNTRS,
                                        sdram_probe_map
};


struct sc_lat_regs {
        reg32_t stdhosthdr_core;
        reg32_t stdhosthdr_version;
        reg32_t en;
        reg32_t soften;
#ifdef _SC_VER_1_16
        reg32_t ignore_suspend;
#endif
        reg32_t trigen;
        reg32_t reqevt;
        reg32_t rspevt;
        reg32_t evtmux_sel[SC_LAT_NUM_CNTRS];
        reg32_t reserved0[4];
        reg32_t dump_identifier;
        reg32_t dump_collecttime;
        reg32_t dump_slvaddr;
        reg32_t dump_mstaddr;
        reg32_t dump_slvofs;
        reg32_t dump_manual;
        reg32_t dump_send;
#ifdef _SC_VER_1_16
        reg32_t dump_disable;
        reg32_t dump_alarm_trig;
        reg32_t dump_alarm_minval;
        reg32_t dump_alarm_maxval;
        reg32_t dump_alarm_mode[SC_LAT_NUM_CNTRS];
        reg32_t reserved1[4];
        reg32_t dump_cnt[SC_LAT_NUM_CNTRS];
        reg32_t reserved2[4];
#endif
        // Note that the fitler mapping is device dependent - so use mod_element_map to access
        struct lat_cnt_filter1 cnt[4];
};


struct cnt_elements lat_cnt_map[] = {
        {false, 1, (uint32_t)(&((struct sc_lat_regs *)0)->cnt[0])},
        {false, 1, (uint32_t)(&((struct sc_lat_regs *)0)->cnt[1])},
        {false, 1, (uint32_t)(&((struct sc_lat_regs *)0)->cnt[2])},
        {false, 1, (uint32_t)(&((struct sc_lat_regs *)0)->cnt[3])} };

/*
 * The request port number is the index*2,
 * the respose port number is the index*2 +1
 */
int lat0_probe_map[] = { SCI_MPU,
                         SCI_DSP,
                         SCI_SDMA_RD,
                         SCI_SDMA_WR,
                         SCI_DSS,
                         SCI_ISS,
                         SCI_GPU_P1
};

int lat1_probe_map[] = { SCI_IVA,
                         SCI_MPU,
                         SCI_SDMA_WR,
                         SCI_GPU_P2,
                         SCI_IPU
};

struct mod_element_map mod_lat0_map = { MSTR,
                                        SC_LAT0_BASE,
                                        NULL,
                                        false,
                                        -1,
                                        0,
                                        sizeof(struct sc_lat_regs),
                                        SC_LAT_NUM_CNTRS,
                                        lat_cnt_map,
                                        SC_LAT0_NUM_PROBES,
                                        lat0_probe_map
};

struct mod_element_map mod_lat1_map = { MSTR,
                                        SC_LAT1_BASE,
                                        NULL,
                                        false,
                                        -1,
                                        0,
                                        sizeof(struct sc_lat_regs),
                                        SC_LAT_NUM_CNTRS,
                                        lat_cnt_map,
                                        SC_LAT1_NUM_PROBES,
                                        lat1_probe_map
};

enum module_id {SDRAM0, LAT0, LAT1} module_id;
struct mod_element_map * mod_map[] = { &mod_sdram_map, &mod_lat0_map, &mod_lat1_map };
//TODO confirm counter widths are correct
const int cnt_overflow_norm[] = {65535-32, 4096-128, 4096-128};
const int cnt_overflow_lat[] = {0, 1023-32, 1023-32};

const int mod_cnt = sizeof mod_map/sizeof mod_map[0];

#ifdef _STM_Logging
/*
 * The following are required for meta data generation
 */

/* Module names */
const char module_name_sdram[] = "SDRAM";
const char module_name_lat0[] = "LAT0";
const char module_name_lat1[] = "LAT1";

/* Use module number to index */
const char * module_name_table[] = {module_name_sdram,
                                   module_name_lat0,
                                   module_name_lat1};
/* EMIF probe names */
const char probe_name_sdram0[] = "EMIF1_SYS";
const char probe_name_sdram1[] = "EMIF2_SYS";
const char probe_name_sdram2[] = "MA_MPU_P1";
const char probe_name_sdram3[] = "MA_MPU_P2";
const char probe_name_sdram4[] = "EMIF1_LL";

/*Use sdram probe id to index */
const char * sdram_probe_name_table[] = { probe_name_sdram0,
                                         probe_name_sdram1,
                                         probe_name_sdram2,
                                         probe_name_sdram3,
                                         probe_name_sdram4};


/* MSTR probe names */
const char probe_name_mstr_mpu[] = "MPU";
const char probe_name_mstr_dsp[] = "DSP";
const char probe_name_mstr_sdmard[] = "SDMA_RD";
const char probe_name_mstr_sdmawr[] = "SDMA_WR";
const char probe_name_mstr_dss[] = "DSS";
const char probe_name_mstr_iss[] = "ISS";
const char probe_name_mstr_gpu1[] = "GPU_P1";
const char probe_name_mstr_iva[] = "IVA";
const char probe_name_mstr_gpu2[] = "GPU_P2";
const char probe_name_mstr_ipu[] = "IPU";

/* Use mastr probe id to index */
const char * mstr_probe_name_table[] = {probe_name_mstr_mpu,
                                        probe_name_mstr_dsp,
                                        probe_name_mstr_sdmard,
                                        probe_name_mstr_sdmawr,
                                        probe_name_mstr_dss,
                                        probe_name_mstr_iss,
                                        probe_name_mstr_gpu1,
                                        probe_name_mstr_iva,
                                        probe_name_mstr_gpu2,
                                        probe_name_mstr_ipu};


/* Master addr names */
const char master_name_mpu[] = "MPU";
const char master_name_dap[] = "DAP";
const char master_name_dsp[] = "DSP";
const char master_name_iva[] = "IVA";
const char master_name_iss[] = "ISS";
const char master_name_ipu[] = "IPU";
const char master_name_fdif[] = "FDIF";
const char master_name_cal[] = "CAL";
const char master_name_sdramrd[] = "SDRAM_rd";
const char master_name_sdramwr[] = "SDRAM_wr";
const char master_name_gpu_p1[] = "GPU_P1";
const char master_name_gpu_p2[] = "GPU_P2";
const char master_name_dss[] = "DSS";
const char master_name_c2c[] = "C2C";
const char master_name_lli[] = "LLI";
const char master_name_hsi[] = "HSI";
const char master_name_unipro1[] = "UNIPRO1";
const char master_name_unipro2[] = "UNIPRO2";
const char master_name_mmc1[] = "MMC1";
const char master_name_mmc2[] = "MMC2";
const char master_name_sata[] = "SATA";
const char master_name_usbhosths[] = "USB Host HS";
const char master_name_usbotghs[] = "USB OTG HS";

/* Use enum sci_master_addr >> 2 to index */
const char * master_name_table[] = {
    master_name_mpu,        /* 0x00 */
    NULL,
    NULL,
    NULL,
    master_name_dap,        /* 0x04 */
    NULL,
    NULL,
    NULL,
    master_name_dsp,        /* 0x08 */
    NULL,
    NULL,
    NULL,
    master_name_iva,        /* 0x0C */
    NULL,
    NULL,
    NULL,
    master_name_iss,        /* 0x10 */
    master_name_ipu,        /* 0x11 */
    master_name_fdif,       /* 0x12 */
    master_name_cal,        /* 0x13 */
    master_name_sdramrd,    /* 0x14 */
    master_name_sdramwr,    /* 0x15 */
    NULL,
    NULL,
    master_name_gpu_p1,     /* 0x18 */
    master_name_gpu_p2,     /* 0x19 */
    NULL,
    NULL,
    master_name_dss,        /* 0x1C */
    NULL,
    NULL,
    NULL,
    master_name_c2c,        /* 0x20 */
    master_name_lli,
    NULL,
    NULL,
    master_name_hsi,        /* 0x24 */
    master_name_unipro1,
    master_name_unipro2,
    NULL,
    master_name_mmc1,       /* 0x28 */
    master_name_mmc2,       /* 0x29 */
    master_name_sata,       /* 0x2A */
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    master_name_usbhosths,    /* 0x30 */
    NULL,
    NULL,
    master_name_usbotghs   /* 0x33 */
};

/* Slave addr names */
const char slave_name_hostclk1[] = "HOST_CLK1";
const char slave_name_dmm1[] = "DMM_P1";
const char slave_name_dmm2[] = "DMM_P2";
const char slave_name_abe[] = "ABE";
const char slave_name_l4cfg[] = "L4CFG";
/* hole */
const char slave_name_hostclk2[] = "HOST_CLK2";
const char slave_name_gpmc[] = "GPMC";
const char slave_name_ocmram[] = "OCM_RAM";
const char slave_name_dss[] = "DSS";
const char slave_name_iss[] = "ISS";
const char slave_name_ipu[] = "IPU";
const char slave_name_gpu[] = "GPU";
const char slave_name_iva[] = "IVA";
const char slave_name_sl2[] = "SL2";
const char slave_name_l4per0[] = "L4_PER_P0";
const char slave_name_l4per1[] = "L4_PER_P1";
const char slave_name_l4per2[] = "L4_PER_P2";
const char slave_name_l4per3[] = "L4_PER_P3";
/*hole */
/*hole */
/*hole */
const char slave_name_c2c[] = "C2C";
const char slave_name_lli[] = "LLI";
const char slave_name_hostclk3[] = "HOST_CLK3";
const char slave_name_l3_instr[] = "L3_ONSTR";
const char slave_name_cal[] = "CAL";
/*hole */
const char slave_name_dbgss[] = "DebugSS_CT_TBR";

const char * slave_name_table[] = {
    slave_name_hostclk1,
    slave_name_dmm1,
    slave_name_dmm2,
    slave_name_abe,
    slave_name_l4cfg,
    NULL,
    slave_name_hostclk2,
    slave_name_gpmc,
    slave_name_ocmram,
    slave_name_dss,
    slave_name_iss,
    slave_name_ipu,
    slave_name_gpu,
    slave_name_iva,
    slave_name_sl2,
    slave_name_l4per0,
    slave_name_l4per1,
    slave_name_l4per2,
    slave_name_l4per3,
    NULL,
    NULL,
    NULL,
    slave_name_c2c,
    slave_name_lli,
    slave_name_hostclk3,
    slave_name_l3_instr,
    slave_name_cal,
    NULL,
    slave_name_dbgss

};


#endif //End of _STM_Logging

#endif //End of _OMAP5430


#endif //End of SCI_COMMON_H
