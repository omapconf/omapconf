/*
 * sci_dra7xx.h
 *
 * Statistic Collector Instrumentation Library
 * - DRA7xx Statistic Collector register definitions
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef SCI_CONFIG_DRA7XX_H
#define SCI_CONFIG_DRA7XX_H

#include "sc_reg.h"

#define SC_INTERFACE_VERSION_DRA 1
#define SC_VER_DRA 116

#define SC_SDRAM_BASE_DRA  0x45001000
#define SC_LAT_0_BASE_DRA  0x45002000
#define SC_LAT_1_BASE_DRA  0x45003000
#define SC_LAT_2_BASE_DRA  0x45004000
#define SC_LAT_3_BASE_DRA  0x45005000
#define SC_LAT_4_BASE_DRA 0x45006000
#define SC_LAT_5_BASE_DRA  0x45007000
#define SC_LAT_6_BASE_DRA  0x45008000
#define SC_LAT_7_BASE_DRA  0x45009000
#define SC_LAT_8_BASE_DRA  0x4500A000

#define SC_SDRAM_NUM_CNTRS_DRA  8
#define SC_SDRAM_NUM_PROBES_DRA  4

#define SC_LAT_NUM_CNTRS_DRA  4
#define SC_LAT_0_NUM_PROBES_DRA  6
#define SC_LAT_1_NUM_PROBES_DRA  8
#define SC_LAT_2_NUM_PROBES_DRA  8 	/*4 reserved*/
#define SC_LAT_3_NUM_PROBES_DRA  8
#define SC_LAT_4_NUM_PROBES_DRA  8	/*2 reserved*/
#define SC_LAT_5_NUM_PROBES_DRA  8
#define SC_LAT_6_NUM_PROBES_DRA  8	/*6 reserved; Datasheet says 7 probes but lists eight ? */
#define SC_LAT_7_NUM_PROBES_DRA  8
#define SC_LAT_8_NUM_PROBES_DRA  8

/* SDRAM Statistic Collector counter register configurations */
struct sc_sdram_counters_dra {
	struct sc_sdram_cnt_filter2_dra cnt0;
	struct sc_sdram_cnt_filter1_dra cnt1;
	struct sc_sdram_cnt_filter2_dra cnt2;
	struct sc_sdram_cnt_filter1_dra cnt3;
	struct sc_sdram_cnt_filter1_dra cnt4;
	struct sc_sdram_cnt_filter1_dra cnt5;
	struct sc_sdram_cnt_filter1_dra cnt6;
	struct sc_sdram_cnt_filter1_dra cnt7;
};

/* LAT Statistic Collector counter register configurations */
struct sc_lat_counters_dra {
	struct sc_lat_cnt_filter1_dra cnt[4];
};

/* SDRAM Statistic Collector register configuration */
struct sc_sdram_reg_map_dra {
	sc_sdram_regs_dra regs;
	struct sc_sdram_counters_dra counters;
};

/* LAT Statistic Collector register configuration */
struct sc_lat_reg_map_dra {
	sc_lat_regs_dra regs;
	struct sc_lat_counters_dra counters;
};

/* Statistic Collector counter element definition*/
struct sc_cnt_elements_dra {
    int num_filters;
    uint32_t cnt_offset;
};

struct sc_cnt_elements_dra sdram_cnt_map_dra[8] = {
	{ 2, (uint32_t)(long)(&((struct sc_sdram_reg_map_dra *)0)->counters.cnt0) },
	{ 1, (uint32_t)(long)(&((struct sc_sdram_reg_map_dra *)0)->counters.cnt1) },
	{ 2, (uint32_t)(long)(&((struct sc_sdram_reg_map_dra *)0)->counters.cnt2) },
	{ 1, (uint32_t)(long)(&((struct sc_sdram_reg_map_dra *)0)->counters.cnt3) },
	{ 1, (uint32_t)(long)(&((struct sc_sdram_reg_map_dra *)0)->counters.cnt4) },
	{ 1, (uint32_t)(long)(&((struct sc_sdram_reg_map_dra *)0)->counters.cnt5) },
	{ 1, (uint32_t)(long)(&((struct sc_sdram_reg_map_dra *)0)->counters.cnt6) },
	{ 1, (uint32_t)(long)(&((struct sc_sdram_reg_map_dra *)0)->counters.cnt7) }
};

struct sc_cnt_elements_dra lat_cnt_map_dra[4] = {
	{ 1, (uint32_t)(long)(&((struct sc_lat_reg_map_dra *)0)->counters.cnt[0]) },
	{ 1, (uint32_t)(long)(&((struct sc_lat_reg_map_dra *)0)->counters.cnt[1]) },
	{ 1, (uint32_t)(long)(&((struct sc_lat_reg_map_dra *)0)->counters.cnt[2]) },
	{ 1, (uint32_t)(long)(&((struct sc_lat_reg_map_dra *)0)->counters.cnt[3]) }
};

struct sc_probe_element_dra {
	uint32_t probe_id;
	int32_t req_port_num;
	int32_t rsp_port_num;
};

struct sc_probe_element_dra sc_sdram_probe_map_dra[4] = {
	{SCI_EMIF1_DRA, 0, 1},
	{SCI_EMIF2_DRA, 2, 3},
	{SCI_MA_MPU_P1_DRA, 4, 5},
	{SCI_MA_MPU_P2_DRA, 6, 7}
};

enum sc_probe_valid_dra {
	SCI_INVALID_PROBE,
	SCI_VALID_PROBE
};


enum sc_probe_valid_dra sc_sdram_no_filter_valid_probe_map_dra[] = {
		SCI_VALID_PROBE, /*SCI_EMIF1 restricted - can not use */
		SCI_VALID_PROBE, /*SCI_EMIF2 restricted - can not use */
		SCI_VALID_PROBE, /*SCI_MA_MPU_P1 ok to use */
		SCI_VALID_PROBE /*SCI_MA_MPU_P2 ok to use */
};

struct sc_probe_element_dra sc_lat_0_probe_map_dra[] = {
	{SCI_MPU_DRA, 0, 1},
	{SCI_MMU1_DRA, 2, 3},
	{SCI_EDMA_TC0_RD_DRA, 4, 5},
	{SCI_EDMA_TC0_WR_DRA, 6, 7},
	{SCI_EDMA_TC1_RD_DRA, 8, 9},
	{SCI_EDMA_TC1_WR_DRA, 10, 11}
};

struct sc_probe_element_dra sc_lat_1_probe_map_dra[] = {
	{SCI_VIP1_P1_DRA, 0, 1},
	{SCI_VIP1_P2_DRA, 2, 3},
	{SCI_VIP2_P1_DRA, 4, 5},
	{SCI_VIP2_P2_DRA, 6, 7},
	{SCI_VIP3_P1_DRA, 8, 9},
	{SCI_VIP3_P2_DRA, 10, 11},
	{SCI_VPE_P1_DRA, 12, 13},
	{SCI_VPE_P2_DRA, 14, 15}
};

struct sc_probe_element_dra sc_lat_2_probe_map_dra[] = {
	{SCI_EVE1_TC0_DRA, 0, 1},
	{SCI_EVE1_TC1_DRA, 2, 3},
	{SCI_EVE2_TC0_DRA, 4, 5},
	{SCI_EVE2_TC1_DRA, 6, 7}
};

struct sc_probe_element_dra sc_lat_3_probe_map_dra[] = {
	{SCI_DSP1_MDMA_DRA, 0, 1},
	{SCI_DSP1_EDMA_DRA, 2, 3},
	{SCI_DSP2_MDMA_DRA, 4, 5},
	{SCI_DSP2_EDMA_DRA, 6, 7},
	{SCI_IVA_DRA, 8, 9},
	{SCI_GPU_P1_DRA, 10, 11},
	{SCI_GPU_P2_DRA, 12, 13},
	{SCI_BB2D_P1_DRA, 14, 15}
};

struct sc_probe_element_dra sc_lat_4_probe_map_dra[] = {
	{SCI_DSS_DRA, 0, 1},
	{SCI_MMU2_DRA, 4, 5},
	{SCI_IPU1_DRA, 6, 7},
	{SCI_IPU2_DRA, 8, 9},
	{SCI_DMA_SYSTEM_RD_DRA, 10, 11},
	{SCI_DMA_SYSTEM_WR_DRA, 12, 13}
};

struct sc_probe_element_dra sc_lat_5_probe_map_dra[] = {
	{SCI_USB1_DRA, 0, 1},
	{SCI_USB2_DRA, 2, 3},
	{SCI_USB3_DRA, 4, 5},
	{SCI_USB4_DRA, 6, 7},
	{SCI_PCIE_SS1_DRA, 8, 9},
	{SCI_PCIE_SS2_DRA, 10, 11},
	{SCI_DSP1_CFG_DRA, 12, 13},
	{SCI_DSP2_CFG_DRA, 14, 15}
};

struct sc_probe_element_dra sc_lat_6_probe_map_dra[] = {
	{SCI_GMAC_SW_DRA, 0, 1},
	{SCI_MPU_DRA, 14, 15}
};

struct sc_probe_element_dra sc_lat_7_probe_map_dra[] = {
	{SCI_MMC1_DRA, 0, 1},
	{SCI_MMC2_DRA, 2, 3},
	{SCI_SATA_DRA, 4, 5},
	{SCI_MLB_DRA, 6, 7},
	{SCI_BB2D_P2_DRA, 8, 9},
	{SCI_IEEE1500_DRA, 10, 11},
	{SCI_DEBUGSS_DRA, 12, 13},
	{SCI_VCP1_DRA, 14, 15}
};

struct sc_probe_element_dra sc_lat_8_probe_map_dra[] = {
	{SCI_OCMC_RAM1_DRA, 0, 1},
	{SCI_OCMC_RAM2_DRA, 2, 3},
	{SCI_OCMC_RAM3_DRA, 4, 5},
	{SCI_GPMC_DRA, 6, 7},
	{SCI_MCASP1_DRA, 8, 9},
	{SCI_MCASP2_DRA, 10, 11},
	{SCI_MCASP3_DRA, 12, 13},
	{SCI_VCP2_DRA, 14, 15}
};

/* Statistic Collector element definition */
enum sc_module_type_dra {SDRAM, MSTR};

struct sc_element_map_dra {
    enum sc_module_type_dra mod_type;
    uint32_t base_addr;
    int mod_size;                   /* In bytes */
    int num_counters;
    struct sc_cnt_elements_dra * cnt_map;
    int num_probes;
    struct sc_probe_element_dra * probe_map;
    enum sc_probe_valid_dra * sc_no_filter_valid_probe_map;
    uint32_t cnt_overflow_load;
    uint32_t cnt_overflow_lat;
};

/* Statistic Collector element maps */
struct sc_element_map_dra sc_sdram_map_dra = {
	SDRAM,
	SC_SDRAM_BASE_DRA,
	sizeof(struct sc_sdram_reg_map_dra),
	SC_SDRAM_NUM_CNTRS_DRA,
	sdram_cnt_map_dra,
	SC_SDRAM_NUM_PROBES_DRA,
	sc_sdram_probe_map_dra,
	sc_sdram_no_filter_valid_probe_map_dra,
	SC_SDRAM_LOAD_CNT_OVERFLOW_DRA,
	SC_SDRAM_LATENCY_CNT_OVERFLOW_DRA
};

struct sc_element_map_dra sc_lat_0_map_dra = {
	MSTR,
	SC_LAT_0_BASE_DRA,
	sizeof(struct sc_lat_reg_map_dra),
	SC_LAT_NUM_CNTRS_DRA,
	lat_cnt_map_dra,
	SC_LAT_0_NUM_PROBES_DRA,
	sc_lat_0_probe_map_dra,
	NULL,
	SC_LAT_LOAD_CNT_OVERFLOW_DRA,
	SC_LAT_LATENCY_CNT_OVERFLOW_DRA
};

struct sc_element_map_dra sc_lat_1_map_dra = {
	MSTR,
	SC_LAT_1_BASE_DRA,
	sizeof(struct sc_lat_reg_map_dra),
	SC_LAT_NUM_CNTRS_DRA,
	lat_cnt_map_dra,
	SC_LAT_1_NUM_PROBES_DRA,
	sc_lat_1_probe_map_dra,
	NULL,
	SC_LAT_LOAD_CNT_OVERFLOW_DRA,
	SC_LAT_LATENCY_CNT_OVERFLOW_DRA
};

struct sc_element_map_dra sc_lat_2_map_dra = {
	MSTR,
	SC_LAT_2_BASE_DRA,
	sizeof(struct sc_lat_reg_map_dra),
	SC_LAT_NUM_CNTRS_DRA,
	lat_cnt_map_dra,
	SC_LAT_2_NUM_PROBES_DRA,
	sc_lat_2_probe_map_dra,
	NULL,
	SC_LAT_LOAD_CNT_OVERFLOW_DRA,
	SC_LAT_LATENCY_CNT_OVERFLOW_DRA
};

struct sc_element_map_dra sc_lat_3_map_dra = {
	MSTR,
	SC_LAT_3_BASE_DRA,
	sizeof(struct sc_lat_reg_map_dra),
	SC_LAT_NUM_CNTRS_DRA,
	lat_cnt_map_dra,
	SC_LAT_3_NUM_PROBES_DRA,
	sc_lat_3_probe_map_dra,
	NULL,
	SC_LAT_LOAD_CNT_OVERFLOW_DRA,
	SC_LAT_LATENCY_CNT_OVERFLOW_DRA
};

struct sc_element_map_dra sc_lat_4_map_dra = {
	MSTR,
	SC_LAT_4_BASE_DRA,
	sizeof(struct sc_lat_reg_map_dra),
	SC_LAT_NUM_CNTRS_DRA,
	lat_cnt_map_dra,
	SC_LAT_4_NUM_PROBES_DRA,
	sc_lat_4_probe_map_dra,
	NULL,
	SC_LAT_LOAD_CNT_OVERFLOW_DRA,
	SC_LAT_LATENCY_CNT_OVERFLOW_DRA
};

struct sc_element_map_dra sc_lat_5_map_dra = {
	MSTR,
	SC_LAT_5_BASE_DRA,
	sizeof(struct sc_lat_reg_map_dra),
	SC_LAT_NUM_CNTRS_DRA,
	lat_cnt_map_dra,
	SC_LAT_5_NUM_PROBES_DRA,
	sc_lat_5_probe_map_dra,
	NULL,
	SC_LAT_LOAD_CNT_OVERFLOW_DRA,
	SC_LAT_LATENCY_CNT_OVERFLOW_DRA
};

struct sc_element_map_dra sc_lat_6_map_dra = {
	MSTR,
	SC_LAT_6_BASE_DRA,
	sizeof(struct sc_lat_reg_map_dra),
	SC_LAT_NUM_CNTRS_DRA,
	lat_cnt_map_dra,
	SC_LAT_6_NUM_PROBES_DRA,
	sc_lat_6_probe_map_dra,
	NULL,
	SC_LAT_LOAD_CNT_OVERFLOW_DRA,
	SC_LAT_LATENCY_CNT_OVERFLOW_DRA
};

struct sc_element_map_dra sc_lat_7_map_dra = {
	MSTR,
	SC_LAT_7_BASE_DRA,
	sizeof(struct sc_lat_reg_map_dra),
	SC_LAT_NUM_CNTRS_DRA,
	lat_cnt_map_dra,
	SC_LAT_7_NUM_PROBES_DRA,
	sc_lat_7_probe_map_dra,
	NULL,
	SC_LAT_LOAD_CNT_OVERFLOW_DRA,
	SC_LAT_LATENCY_CNT_OVERFLOW_DRA
};

struct sc_element_map_dra sc_lat_8_map_dra = {
	MSTR,
	SC_LAT_8_BASE_DRA,
	sizeof(struct sc_lat_reg_map_dra),
	SC_LAT_NUM_CNTRS_DRA,
	lat_cnt_map_dra,
	SC_LAT_8_NUM_PROBES_DRA,
	sc_lat_8_probe_map_dra,
	NULL,
	SC_LAT_LOAD_CNT_OVERFLOW_DRA,
	SC_LAT_LATENCY_CNT_OVERFLOW_DRA
};

struct sc_element_map_dra * sc_map_dra[] = {
	&sc_sdram_map_dra,
	&sc_lat_0_map_dra,
	&sc_lat_1_map_dra,
	&sc_lat_2_map_dra,
	&sc_lat_3_map_dra,
	&sc_lat_4_map_dra,
	&sc_lat_5_map_dra,
	&sc_lat_6_map_dra,
	&sc_lat_7_map_dra,
	&sc_lat_8_map_dra
};

/* Statistic Collector names are in sc_map order */
const char * sci_unit_name_table_dra[] = {
    "SDRAM",
    "LAT0",
    "LAT1",
    "LAT2",
    "LAT3",
    "LAT4",
    "LAT5",
    "LAT6",
    "LAT7",
    "LAT8"
};

/* Statistic Collector probe name tables */
const char * sci_sdram_probe_name_table_dra[] = {
    "EMIF1",
    "EMIF2",
    "MA_MPU_P1",
    "MA_MPU_P2"
};

const char * sci_mstr_probe_name_table_dra[] = {
    "MPU",
    "MMU1",
    "EDMA_TC0_RD",
    "EDMA_TC0_WR",
    "EDMA_TC1_RD",
    "EDMA_TC1_WR",
    "VIP1_P1",
    "VIP1_P2",
    "VIP2_P1",
    "VIP2_P2",
    "VIP3_P1",
    "VIP3_P2",
    "VPE_P1",
    "VPE_P2",
    "EVE1_TC0",
    "EVE1_TC1",
    "EVE2_TC0",
    "EVE2_TC1",
    "DSP1_MDMA",
    "DSP1_EDMA",
    "DSP2_MDMA",
    "DSP2_EDMA",
    "IVA",
    "GPU_P1",
    "GPU_P2",
    "BB2D_P1",
    "DSS",
    "MMU2",
    "IPU1",
    "IPU2",
    "DMA_SYSTEM_RD",
    "DMA_SYSTEM_WR",
    "USB1",
    "USB2",
    "USB3",
    "IUSB4",
    "PCIe_SS1",
    "PCIe_SS2",
    "DSP1_CFG",
    "DSP2_CFG",
    "GMAC_SW",
    "MPU",
    "MMC1",
    "MMC2",
    "SATA",
    "MLB",
    "BB2D_P2",
    "IEEE1500",
    "DEBUGSS",
    "OCMC_RAM1",
    "OCMC_RAM2",
    "OCMC_RAM3",
    "GPMC",
    "MCASP1",
    "MCASP2",
    "MCASP3",
	"VCP2"
};

/* Statistic Collector master address table */
enum sci_master_addr_dra sci_master_addr_table_dra[] = {
    SCI_MSTID_MPU_DRA,
    SCI_MSTID_DAP_DRA,
    SCI_MSTID_IEEE1500_2_OCP_DRA,
	SCI_MSTID_DSP1_MDMA_DRA,
	SCI_MSTID_DSP1_CFG_DRA,
	SCI_MSTID_DSP1_DMA_DRA,
	SCI_MSTID_DSP2_DMA_DRA,
	SCI_MSTID_DSP2_CFG_DRA,
	SCI_MSTID_DSP2_MDMA_DRA,
	SCI_MSTID_IVA_ICONT1_DRA,
	SCI_MSTID_EVE1_P1_DRA,
	SCI_MSTID_EVE2_P1_DRA,
	SCI_MSTID_IPU1_DRA,
	SCI_MSTID_IPU2_DRA,
	SCI_MSTID_SDMA_RD_DRA,
	SCI_MSTID_SDMA_WR_DRA,
	SCI_MSTID_EDMA_TC1_WR_DRA,
	SCI_MSTID_EDMA_TC1_RD_DRA,
	SCI_MSTID_EDMA_TC2_WR_DRA,
	SCI_MSTID_EDMA_TC2_RD_DRA,
	SCI_MSTID_DSS_DRA,
	SCI_MSTID_MLB_DRA,
	SCI_MSTID_MMU1_DRA,
	SCI_MSTID_PCIE_SS1_DRA,
	SCI_MSTID_PCIE_SS2_DRA,
	SCI_MSTID_MMU2_DRA,
	SCI_MSTID_VIP1_P1_DRA,
	SCI_MSTID_VIP1_P2_DRA,
	SCI_MSTID_VIP2_P1_DRA,
	SCI_MSTID_VIP2_P2_DRA,
	SCI_MSTID_VIP3_P1_DRA,
	SCI_MSTID_VIP3_P2_DRA,
	SCI_MSTID_VPE_P1_DRA,
	SCI_MSTID_VPE_P2_DRA,
	SCI_MSTID_MMC1_DRA,
	SCI_MSTID_GPU_P1_DRA,
	SCI_MSTID_MMC2_DRA,
	SCI_MSTID_GPU_P2_DRA,
	SCI_MSTID_BB2D_P1_DRA,
	SCI_MSTID_BB2D_P2_DRA,
	SCI_MSTID_GMAC_SW_DRA,
	SCI_MSTID_USB4_DRA,
	SCI_MSTID_USB1_DRA,
	SCI_MSTID_USB2_DRA,
	SCI_MSTID_USB3_DRA,
	SCI_MSTID_SATA_DRA,
	SCI_MSTID_EVE1_P2_DRA,
	SCI_MSTID_EVE2_P2_DRA,
	SCI_MASTID_ALL_DRA
};

/* Statistic Collector master name table.
 * In sci_master_addr_table order.
 */
const char * sci_master_name_table_dra[] = {
	"MPU",
	"CS_DAP",
	"IEEE1500_2_OCP",
	"DSP1_MDMA",
	"DSP1_CFG",
	"DSP1_DMA",
	"DSP2_DMA",
	"DSP2_CFG",
	"DSP2_MDMA",
	"IVA_ICONT 1",
	"EVE1_P1",
	"EVE2_P1",
	"IPU1",
	"IPU2",
	"DMA_SYSTEM_RD",
	"DMA_SYSTEM_WR",
	"EDMA_TC1_WR",
	"EDMA_TC1_RD",
	"EDMA_TC2_WR",
	"EDMA_TC2_RD",
	"DSS",
	"MLB",
	"MMU1",
	"PCIe_SS1",
	"PCIe_SS2",
	"MMU2",
	"VIP1_P1",
	"VIP1_P2",
	"VIP2_P1",
	"VIP2_P2",
	"VIP3_P1",
	"VIP3_P2",
	"VPE_P1",
	"VPE_P2",
	"MMC1",
	"GPU_P1",
	"MMC2",
	"GPU_P2",
	"BB2D_P1",
	"BB2D_P2",
	"GMAC_SW",
	"USB4",
	"USB1",
	"USB2",
	"USB3",
	"SATA",
	"EVE1_P2",
	"EVE2_P2"
};

/* Statistic Collector slave address table */
enum sci_slave_addr_dra sci_slave_addr_table_dra[] = {
	SCI_SLVID_DMM_P1_DRA,
	SCI_SLVID_DMM_P2_DRA,
	SCI_SLVID_DSP1_SDMA_DRA,
	SCI_SLVID_DSP2_SDMA_DRA,
	SCI_SLVID_DSS_DRA,
	SCI_SLVID_EVE1_DRA,
	SCI_SLVID_EVE2_DRA,
	SCI_SLVID_BB2D_DRA,
	SCI_SLVID_GPMC_DRA,
	SCI_SLVID_GPU_DRA,
	SCI_SLVID_HOST_CLK1_1_DRA,
	SCI_SLVID_HOST_CLK1_2_DRA,
	SCI_SLVID_IPU1_DRA,
	SCI_SLVID_IPU2_DRA,
	SCI_SLVID_IVA_CONFIG_DRA,
	SCI_SLVID_IVA_SL2IF_DRA,
	SCI_SLVID_L4_CFG_DRA,
	SCI_SLVID_L4_PER1_P1_DRA,
	SCI_SLVID_L4_PER1_P2_DRA,
	SCI_SLVID_L4_PER1_P3_DRA,
	SCI_SLVID_L4_PER2_P1_DRA,
	SCI_SLVID_L3_INSTR_DRA,
	SCI_SLVID_L4_PER2_P3_DRA,
	SCI_SLVID_L4_PER3_P1_DRA,
	SCI_SLVID_L4_PER3_P2_DRA,
	SCI_SLVID_L4_PER3_P3_DRA,
	SCI_SLVID_L4_WKUP_DRA,
	SCI_SLVID_MCASP1_DRA,
	SCI_SLVID_MCASP2_DRA,
	SCI_SLVID_MCASP3_DRA,
	SCI_SLVID_MMU1_DRA,
	SCI_SLVID_MMU2_DRA,
	SCI_SLVID_OCMC_RAM1_DRA,
	SCI_SLVID_OCMC_RAM2_DRA,
	SCI_SLVID_OCMC_RAM3_DRA,
	SCI_SLVID_OCMC_ROM_DRA,
	SCI_SLVID_PCIE_SS1_DRA,
	SCI_SLVID_PCIE_SS2_DRA,
	SCI_SLVID_EDMA_TPCC_DRA,
	SCI_SLVID_EDMA_TC1_DRA,
	SCI_SLVID_EDMA_TC2_DRA,
	SCI_SLVID_VCP1_DRA,
	SCI_SLVID_VCP2_DRA,
	SCI_SLVID_QSPI_DRA,
	SCI_SLVID_HOST_CLK2_1_DRA,
	SCI_SLVID_DEBUGSS_CT_TBR_DRA,
	SCI_SLVID_L4_PER2_P2_DRA,
	SCI_SLVID_ALL_DRA
};

/* Statistic Collector slave name table.
 * In sci_slave_addr_table order.
 */
const char * sci_slave_name_table_dra[] = {
	"DMM_P1",
	"DMM_P2",
	"DSP1_SDMA",
	"DSP2_SDMA",
	"DSS",
	"EVE1",
	"EVE2",
	"BB2D ",
	"GPMC",
	"GPU ",
	"HOST_CLK1_1",
	"HOST_CLK1_2",
	"IPU1",
	"IPU2",
	"IVA_CONFIG",
	"IVA_SL2IF",
	"L4_CFG",
	"L4_PER1_P1",
	"L4_PER1_P2 ",
	"L4_PER1_P3",
	"L4_PER2_P1",
	"L3_INSTR",
	"L4_PER2S_P3",
	"L4_PER3_P1",
	"L4_PER3_P2",
	"L4_PER3_P3",
	"L4_WKUP",
	"McASP1",
	"McASP2",
	"McASP3",
	"MMU1",
	"MMU2",
	"OCMC_RAM1",
	"OCMC_RAM2",
	"OCMC_RAM3",
	"OCMC_ROM",
	"PCIe_SS1",
	"PCIe_SS2",
	"EDMA_TPCC",
	"EDMA_TC1",
	"EDMA_TC2",
	"VCP1",
	"VCP2",
	"QSPI",
	"HOST_CLK2_1",
	"DEBUGSS_CT_TBR",
	"L4_PER2_P2"
};
#endif
