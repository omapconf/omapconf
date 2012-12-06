/*
 *
 * @Component			OMAPCONF
 * @Filename			ctrlmod_core54xx-defs.h
 * @Description			OMAP5 CONTROL MODULE Registers Definitions
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


#ifndef __CTRLMOD_CORE54XX_DEFS_H__
#define __CTRLMOD_CORE54XX_DEFS_H__

#include <reg.h>
#include <stdio.h>

#define OMAP5430_CONTROL_CORE_REVISION				0x4a002000
extern reg omap5430_control_core_revision;
#define OMAP5430_CONTROL_CORE_HWINFO				0x4a002004
extern reg omap5430_control_core_hwinfo;
#define OMAP5430_CONTROL_CORE_SYSCONFIG				0x4a002010
extern reg omap5430_control_core_sysconfig;
#define OMAP5430_CONTROL_L3_HW_FW_EXPORTED_VALUES_CONF_DBG	0x4a002114
extern reg omap5430_control_l3_hw_fw_exported_values_conf_dbg;
#define OMAP5430_CONTROL_L3_HW_FW_EXPORTED_VALUES_CONF_FUNC	0x4a002118
extern reg omap5430_control_l3_hw_fw_exported_values_conf_func;
#define OMAP5430_CONTROL_STATUS					0x4a002134
extern reg omap5430_control_status;
#define OMAP5430_CONTROL_SEC_ERR_STATUS_FUNC			0x4a002148
extern reg omap5430_control_sec_err_status_func;
#define OMAP5430_CONTROL_SEC_ERR_STATUS_DEBUG			0x4a002150
extern reg omap5430_control_sec_err_status_debug;
#define OMAP5430_CONTROL_FORCEWRNP				0x4a00215c
extern reg omap5430_control_forcewrnp;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MM_0			0x4a002194
extern reg omap5430_control_std_fuse_opp_vdd_mm_0;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MM_1			0x4a002198
extern reg omap5430_control_std_fuse_opp_vdd_mm_1;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MM_2			0x4a00219c
extern reg omap5430_control_std_fuse_opp_vdd_mm_2;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MM_3			0x4a0021a0
extern reg omap5430_control_std_fuse_opp_vdd_mm_3;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MM_4			0x4a0021a4
extern reg omap5430_control_std_fuse_opp_vdd_mm_4;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MM_5			0x4a0021a8
extern reg omap5430_control_std_fuse_opp_vdd_mm_5;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_0			0x4a0021ac
extern reg omap5430_control_std_fuse_opp_vdd_mpu_0;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_1			0x4a0021b0
extern reg omap5430_control_std_fuse_opp_vdd_mpu_1;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_2			0x4a0021b4
extern reg omap5430_control_std_fuse_opp_vdd_mpu_2;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_3			0x4a0021b8
extern reg omap5430_control_std_fuse_opp_vdd_mpu_3;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_4			0x4a0021bc
extern reg omap5430_control_std_fuse_opp_vdd_mpu_4;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_5			0x4a0021c0
extern reg omap5430_control_std_fuse_opp_vdd_mpu_5;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_6			0x4a0021c4
extern reg omap5430_control_std_fuse_opp_vdd_mpu_6;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_7			0x4a0021c8
extern reg omap5430_control_std_fuse_opp_vdd_mpu_7;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_CORE_0		0x4a0021cc
extern reg omap5430_control_std_fuse_opp_vdd_core_0;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_CORE_1		0x4a0021d0
extern reg omap5430_control_std_fuse_opp_vdd_core_1;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_CORE_2		0x4a0021d4
extern reg omap5430_control_std_fuse_opp_vdd_core_2;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_CORE_3		0x4a0021d8
extern reg omap5430_control_std_fuse_opp_vdd_core_3;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_CORE_4		0x4a0021dc
extern reg omap5430_control_std_fuse_opp_vdd_core_4;
#define OMAP5430_CONTROL_STD_FUSE_OPP_BGAP_MM			0x4a0021e0
extern reg omap5430_control_std_fuse_opp_bgap_mm;
#define OMAP5430_CONTROL_STD_FUSE_OPP_BGAP_MPU			0x4a0021e4
extern reg omap5430_control_std_fuse_opp_bgap_mpu;
#define OMAP5430_CONTROL_STD_FUSE_OPP_BGAP_CORE			0x4a0021e8
extern reg omap5430_control_std_fuse_opp_bgap_core;
#define OMAP5430_CONTROL_STD_FUSE_OPP_BGAP_MPU23		0x4a0021ec
extern reg omap5430_control_std_fuse_opp_bgap_mpu23;
#define OMAP5430_CONTROL_STD_FUSE_DIE_ID_0			0x4a002200
extern reg omap5430_control_std_fuse_die_id_0;
#define OMAP5430_CONTROL_STD_FUSE_DIE_ID_1			0x4a002208
extern reg omap5430_control_std_fuse_die_id_1;
#define OMAP5430_CONTROL_STD_FUSE_DIE_ID_2			0x4a00220c
extern reg omap5430_control_std_fuse_die_id_2;
#define OMAP5430_CONTROL_STD_FUSE_DIE_ID_3			0x4a002210
extern reg omap5430_control_std_fuse_die_id_3;
#define OMAP5430_CONTROL_STD_FUSE_PROD_ID			0x4a002214
extern reg omap5430_control_std_fuse_prod_id;
#define OMAP5430_CONTROL_STD_FUSE_CONF_ID_0			0x4a002218
extern reg omap5430_control_std_fuse_conf_id_0;
#define OMAP5430_CONTROL_STD_FUSE_CONF_ID_1			0x4a00221c
extern reg omap5430_control_std_fuse_conf_id_1;
#define OMAP5430_CONTROL_STD_FUSE_MPK_0				0x4a002220
extern reg omap5430_control_std_fuse_mpk_0;
#define OMAP5430_CONTROL_STD_FUSE_MPK_1				0x4a002224
extern reg omap5430_control_std_fuse_mpk_1;
#define OMAP5430_CONTROL_STD_FUSE_MPK_2				0x4a002228
extern reg omap5430_control_std_fuse_mpk_2;
#define OMAP5430_CONTROL_STD_FUSE_MPK_3				0x4a00222c
extern reg omap5430_control_std_fuse_mpk_3;
#define OMAP5430_CONTROL_STD_FUSE_MPK_4				0x4a002230
extern reg omap5430_control_std_fuse_mpk_4;
#define OMAP5430_CONTROL_STD_FUSE_MPK_5				0x4a002234
extern reg omap5430_control_std_fuse_mpk_5;
#define OMAP5430_CONTROL_STD_FUSE_MPK_6				0x4a002238
extern reg omap5430_control_std_fuse_mpk_6;
#define OMAP5430_CONTROL_STD_FUSE_MPK_7				0x4a00223c
extern reg omap5430_control_std_fuse_mpk_7;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MM_LVT_0		0x4a002240
extern reg omap5430_control_std_fuse_opp_vdd_mm_lvt_0;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MM_LVT_1		0x4a002244
extern reg omap5430_control_std_fuse_opp_vdd_mm_lvt_1;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MM_LVT_2		0x4a002248
extern reg omap5430_control_std_fuse_opp_vdd_mm_lvt_2;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MM_LVT_3		0x4a00224c
extern reg omap5430_control_std_fuse_opp_vdd_mm_lvt_3;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MM_LVT_4		0x4a002250
extern reg omap5430_control_std_fuse_opp_vdd_mm_lvt_4;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MM_LVT_5		0x4a002254
extern reg omap5430_control_std_fuse_opp_vdd_mm_lvt_5;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_LVT_0		0x4a002258
extern reg omap5430_control_std_fuse_opp_vdd_mpu_lvt_0;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_LVT_1		0x4a00225c
extern reg omap5430_control_std_fuse_opp_vdd_mpu_lvt_1;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_LVT_2		0x4a002260
extern reg omap5430_control_std_fuse_opp_vdd_mpu_lvt_2;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_LVT_3		0x4a002264
extern reg omap5430_control_std_fuse_opp_vdd_mpu_lvt_3;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_LVT_4		0x4a002268
extern reg omap5430_control_std_fuse_opp_vdd_mpu_lvt_4;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_LVT_5		0x4a00226c
extern reg omap5430_control_std_fuse_opp_vdd_mpu_lvt_5;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_LVT_6		0x4a002270
extern reg omap5430_control_std_fuse_opp_vdd_mpu_lvt_6;
#define OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_LVT_7		0x4a002274
extern reg omap5430_control_std_fuse_opp_vdd_mpu_lvt_7;
#define OMAP5430_CONTROL_CUST_FUSE_SWRV_0			0x4a0022bc
extern reg omap5430_control_cust_fuse_swrv_0;
#define OMAP5430_CONTROL_CUST_FUSE_SWRV_1			0x4a0022c0
extern reg omap5430_control_cust_fuse_swrv_1;
#define OMAP5430_CONTROL_CUST_FUSE_SWRV_2			0x4a0022c4
extern reg omap5430_control_cust_fuse_swrv_2;
#define OMAP5430_CONTROL_CUST_FUSE_SWRV_3			0x4a0022c8
extern reg omap5430_control_cust_fuse_swrv_3;
#define OMAP5430_CONTROL_CUST_FUSE_SWRV_4			0x4a0022cc
extern reg omap5430_control_cust_fuse_swrv_4;
#define OMAP5430_CONTROL_CUST_FUSE_SWRV_5			0x4a0022d0
extern reg omap5430_control_cust_fuse_swrv_5;
#define OMAP5430_CONTROL_CUST_FUSE_SWRV_6			0x4a0022d4
extern reg omap5430_control_cust_fuse_swrv_6;
#define OMAP5430_CONTROL_HWOBSDIVIDER1				0x4a0022d8
extern reg omap5430_control_hwobsdivider1;
#define OMAP5430_CONTROL_HWOBSDIVIDER2				0x4a0022dc
extern reg omap5430_control_hwobsdivider2;
#define OMAP5430_CONTROL_BREG_SELECTION				0x4a0022e0
extern reg omap5430_control_breg_selection;
#define OMAP5430_CONTROL_DPLL_BCLK				0x4a0022e4
extern reg omap5430_control_dpll_bclk;
#define OMAP5430_CONTROL_DPLL_BADDR_BDATAW			0x4a0022e8
extern reg omap5430_control_dpll_baddr_bdataw;
#define OMAP5430_CONTROL_DPLL_BDATAR				0x4a0022ec
extern reg omap5430_control_dpll_bdatar;
#define OMAP5430_CONTROL_DEV_CONF				0x4a002300
extern reg omap5430_control_dev_conf;
#define OMAP5430_CONTROL_DSP_BOOTADDR				0x4a002304
extern reg omap5430_control_dsp_bootaddr;
#define OMAP5430_CONTROL_TEMP_SENSOR_MPU			0x4a00232c
extern reg omap5430_control_temp_sensor_mpu;
#define OMAP5430_CONTROL_TEMP_SENSOR_MM				0x4a002330
extern reg omap5430_control_temp_sensor_mm;
#define OMAP5430_CONTROL_TEMP_SENSOR_CORE			0x4a002334
extern reg omap5430_control_temp_sensor_core;
#define OMAP5430_CONTROL_LDOSRAM_MPU_LVT_VOLTAGE_CTRL		0x4a002338
extern reg omap5430_control_ldosram_mpu_lvt_voltage_ctrl;
#define OMAP5430_CONTROL_CORTEX_M4_MMUADDRTRANSLTR		0x4a002358
extern reg omap5430_control_cortex_m4_mmuaddrtransltr;
#define OMAP5430_CONTROL_CORTEX_M4_MMUADDRLOGICTR		0x4a00235c
extern reg omap5430_control_cortex_m4_mmuaddrlogictr;
#define OMAP5430_CONTROL_HWOBS_CONTROL				0x4a002360
extern reg omap5430_control_hwobs_control;
#define OMAP5430_CONTROL_PCS1					0x4a002364
extern reg omap5430_control_pcs1;
#define OMAP5430_CONTROL_PCS2					0x4a002368
extern reg omap5430_control_pcs2;
#define OMAP5430_CONTROL_PCS_REVISION				0x4a00236c
extern reg omap5430_control_pcs_revision;
#define OMAP5430_CONTROL_PHY_POWER_USB				0x4a002370
extern reg omap5430_control_phy_power_usb;
#define OMAP5430_CONTROL_PHY_POWER_SATA				0x4a002374
extern reg omap5430_control_phy_power_sata;
#define OMAP5430_CONTROL_SLIMBUS_KEEPER				0x4a002378
extern reg omap5430_control_slimbus_keeper;
#define OMAP5430_CONTROL_PHY_SEL				0x4a00237c
extern reg omap5430_control_phy_sel;
#define OMAP5430_CONTROL_BANDGAP_MASK				0x4a002380
extern reg omap5430_control_bandgap_mask;
#define OMAP5430_CONTROL_BANDGAP_THRESHOLD_MPU			0x4a002384
extern reg omap5430_control_bandgap_threshold_mpu;
#define OMAP5430_CONTROL_BANDGAP_THRESHOLD_MM			0x4a002388
extern reg omap5430_control_bandgap_threshold_mm;
#define OMAP5430_CONTROL_BANDGAP_THRESHOLD_CORE			0x4a00238c
extern reg omap5430_control_bandgap_threshold_core;
#define OMAP5430_CONTROL_BANDGAP_TSHUT_MPU			0x4a002390
extern reg omap5430_control_bandgap_tshut_mpu;
#define OMAP5430_CONTROL_BANDGAP_TSHUT_MM			0x4a002394
extern reg omap5430_control_bandgap_tshut_mm;
#define OMAP5430_CONTROL_BANDGAP_TSHUT_CORE			0x4a002398
extern reg omap5430_control_bandgap_tshut_core;
#define OMAP5430_CONTROL_BANDGAP_COUNTER_MPU			0x4a00239c
extern reg omap5430_control_bandgap_counter_mpu;
#define OMAP5430_CONTROL_BANDGAP_COUNTER_MM			0x4a0023a0
extern reg omap5430_control_bandgap_counter_mm;
#define OMAP5430_CONTROL_BANDGAP_COUNTER_CORE			0x4a0023a4
extern reg omap5430_control_bandgap_counter_core;
/* ES2.0 */
#define OMAP5430_CONTROL_BANDGAP_CUMUL_DTEMP_MPU		0x4a00239c
extern reg omap5430_control_bandgap_cumul_dtemp_mpu;
#define OMAP5430_CONTROL_BANDGAP_CUMUL_DTEMP_MM			0x4a0023a0
extern reg omap5430_control_bandgap_cumul_dtemp_mm;
#define OMAP5430_CONTROL_BANDGAP_CUMUL_DTEMP_CORE		0x4a0023a4
extern reg omap5430_control_bandgap_cumul_dtemp_core;

#define OMAP5430_CONTROL_BANDGAP_STATUS				0x4a0023a8
extern reg omap5430_control_bandgap_status;
#define OMAP5430_CONTROL_SATA_EXT_MODE				0x4a0023ac
extern reg omap5430_control_sata_ext_mode;
#define OMAP5430_CONTROL_DTEMP_MPU_0				0x4a0023c0
extern reg omap5430_control_dtemp_mpu_0;
#define OMAP5430_CONTROL_DTEMP_MPU_1				0x4a0023c4
extern reg omap5430_control_dtemp_mpu_1;
#define OMAP5430_CONTROL_DTEMP_MPU_2				0x4a0023c8
extern reg omap5430_control_dtemp_mpu_2;
#define OMAP5430_CONTROL_DTEMP_MPU_3				0x4a0023cc
extern reg omap5430_control_dtemp_mpu_3;
#define OMAP5430_CONTROL_DTEMP_MPU_4				0x4a0023d0
extern reg omap5430_control_dtemp_mpu_4;
#define OMAP5430_CONTROL_DTEMP_MM_0				0x4a0023d4
extern reg omap5430_control_dtemp_mm_0;
#define OMAP5430_CONTROL_DTEMP_MM_1				0x4a0023d8
extern reg omap5430_control_dtemp_mm_1;
#define OMAP5430_CONTROL_DTEMP_MM_2				0x4a0023dc
extern reg omap5430_control_dtemp_mm_2;
#define OMAP5430_CONTROL_DTEMP_MM_3				0x4a0023e0
extern reg omap5430_control_dtemp_mm_3;
#define OMAP5430_CONTROL_DTEMP_MM_4				0x4a0023e4
extern reg omap5430_control_dtemp_mm_4;
#define OMAP5430_CONTROL_DTEMP_CORE_0				0x4a0023e8
extern reg omap5430_control_dtemp_core_0;
#define OMAP5430_CONTROL_DTEMP_CORE_1				0x4a0023ec
extern reg omap5430_control_dtemp_core_1;
#define OMAP5430_CONTROL_DTEMP_CORE_2				0x4a0023f0
extern reg omap5430_control_dtemp_core_2;
#define OMAP5430_CONTROL_DTEMP_CORE_3				0x4a0023f4
extern reg omap5430_control_dtemp_core_3;
#define OMAP5430_CONTROL_DTEMP_CORE_4				0x4a0023f8
extern reg omap5430_control_dtemp_core_4;
#define OMAP5430_CONTROL_OCPREG_SPARE				0x4a0023fc
extern reg omap5430_control_ocpreg_spare;
#define OMAP5430_CONTROL_DEBOBS_FINAL_MUX_SEL			0x4a002400
extern reg omap5430_control_debobs_final_mux_sel;
#define OMAP5430_CONTROL_DEBOBS_OCPWP_SYS_EVENT_SEL		0x4a002404
extern reg omap5430_control_debobs_ocpwp_sys_event_sel;
#define OMAP5430_CONTROL_DEBOBS_MMR_MPU				0x4a002408
extern reg omap5430_control_debobs_mmr_mpu;
#define OMAP5430_CONTROL_CONF_MDMA_REQ_SEL0			0x4a002410
extern reg omap5430_control_conf_mdma_req_sel0;
#define OMAP5430_CONTROL_CONF_MDMA_REQ_SEL1			0x4a002414
extern reg omap5430_control_conf_mdma_req_sel1;
#define OMAP5430_CONTROL_CONF_MDMA_REQ_SEL2			0x4a002418
extern reg omap5430_control_conf_mdma_req_sel2;
#define OMAP5430_CONTROL_CONF_MDMA_REQ_SEL3			0x4a00241c
extern reg omap5430_control_conf_mdma_req_sel3;
#define OMAP5430_CONTROL_CONF_MDMA_REQ_SEL4			0x4a002420
extern reg omap5430_control_conf_mdma_req_sel4;
#define OMAP5430_CONTROL_CONF_MDMA_REQ_SEL5			0x4a002424
extern reg omap5430_control_conf_mdma_req_sel5;
#define OMAP5430_CONTROL_CONF_SDMA_REQ_SEL0			0x4a00242c
extern reg omap5430_control_conf_sdma_req_sel0;
#define OMAP5430_CONTROL_CONF_SDMA_REQ_SEL1			0x4a002430
extern reg omap5430_control_conf_sdma_req_sel1;
#define OMAP5430_CONTROL_CONF_SDMA_REQ_SEL2			0x4a002434
extern reg omap5430_control_conf_sdma_req_sel2;
#define OMAP5430_CONTROL_CONF_SDMA_REQ_SEL3			0x4a002438
extern reg omap5430_control_conf_sdma_req_sel3;
#define OMAP5430_CONTROL_CONF_CLK_SEL0				0x4a002440
extern reg omap5430_control_conf_clk_sel0;
#define OMAP5430_CONTROL_CONF_CLK_SEL1				0x4a002444
extern reg omap5430_control_conf_clk_sel1;
#define OMAP5430_CONTROL_CONF_CLK_SEL2				0x4a002448
extern reg omap5430_control_conf_clk_sel2;
#define OMAP5430_CONTROL_CONF_DPLL_FREQLOCK_SEL			0x4a00244c
extern reg omap5430_control_conf_dpll_freqlock_sel;
#define OMAP5430_CONTROL_CONF_DPLL_TINITZ_SEL			0x4a002450
extern reg omap5430_control_conf_dpll_tinitz_sel;
#define OMAP5430_CONTROL_CONF_DPLL_PHASELOCK_SEL		0x4a002454
extern reg omap5430_control_conf_dpll_phaselock_sel;
#define OMAP5430_CONTROL_CONF_DPLL_TENABLE_SEL			0x4a002458
extern reg omap5430_control_conf_dpll_tenable_sel;
#define OMAP5430_CONTROL_CONF_DPLL_TENABLEDIV_SEL		0x4a00245c
extern reg omap5430_control_conf_dpll_tenablediv_sel;
#define OMAP5430_CONTROL_CONF_DPLL_BYPASSACK_SEL		0x4a002460
extern reg omap5430_control_conf_dpll_bypassack_sel;
#define OMAP5430_CONTROL_CONF_DPLL_IDLE_SEL			0x4a002464
extern reg omap5430_control_conf_dpll_idle_sel;
#define OMAP5430_CONTROL_CONF_DPLLCTRL_PLLLOCK_SEL		0x4a002468
extern reg omap5430_control_conf_dpllctrl_plllock_sel;
#define OMAP5430_CONTROL_CONF_DPLLCTRL_PLLRECAL_SEL		0x4a00246c
extern reg omap5430_control_conf_dpllctrl_pllrecal_sel;
#define OMAP5430_CONTROL_CONF_DPLLCTRL_STOPCLOCK_SEL		0x4a002470
extern reg omap5430_control_conf_dpllctrl_stopclock_sel;
#define OMAP5430_CONTROL_CONF_DPLLCTRL_STOPCLOCKACKZ_SEL	0x4a002474
extern reg omap5430_control_conf_dpllctrl_stopclockackz_sel;
#define OMAP5430_CONTROL_CONF_DPLLCTRL_DISPCUPDATESYNC_SEL	0x4a002478
extern reg omap5430_control_conf_dpllctrl_dispcupdatesync_sel;
#define OMAP5430_CONTROL_CONF_DPLLCTRL_SCPENPLLCTRL_SEL		0x4a00247c
extern reg omap5430_control_conf_dpllctrl_scpenpllctrl_sel;
#define OMAP5430_CONTROL_CONF_DPLLCTRL_SCPCMD1_SEL		0x4a002480
extern reg omap5430_control_conf_dpllctrl_scpcmd1_sel;
#define OMAP5430_CONTROL_CONF_DPLLCTRL_SCPCMD0_SEL		0x4a002484
extern reg omap5430_control_conf_dpllctrl_scpcmd0_sel;
#define OMAP5430_CONTROL_CONF_DPLLCTRL_SCPADDR3_SEL		0x4a002488
extern reg omap5430_control_conf_dpllctrl_scpaddr3_sel;
#define OMAP5430_CONTROL_CONF_DPLLCTRL_SCPADDR2_SEL		0x4a00248c
extern reg omap5430_control_conf_dpllctrl_scpaddr2_sel;
#define OMAP5430_CONTROL_CONF_DPLLCTRL_SCPADDR1_SEL		0x4a002490
extern reg omap5430_control_conf_dpllctrl_scpaddr1_sel;
#define OMAP5430_CONTROL_CONF_DPLLCTRL_SCPADDR0_SEL		0x4a002494
extern reg omap5430_control_conf_dpllctrl_scpaddr0_sel;
#define OMAP5430_CONTROL_CONF_DPLLCTRL_SCPOUT_SEL		0x4a002498
extern reg omap5430_control_conf_dpllctrl_scpout_sel;
#define OMAP5430_CONTROL_CONF_DPLLCTRL_SCPINPLLCTRL_SEL		0x4a00249c
extern reg omap5430_control_conf_dpllctrl_scpinpllctrl_sel;
#define OMAP5430_CONTROL_CONF_DPLLCTRL_SCPBUSY_SEL		0x4a0024a0
extern reg omap5430_control_conf_dpllctrl_scpbusy_sel;
#define OMAP5430_CONTROL_CONF_MMCX_ADPIDLE_SEL			0x4a0024ac
extern reg omap5430_control_conf_mmcx_adpidle_sel;
#define OMAP5430_CONTROL_CONF_MMCX_ADPDAT1PADEN_SEL		0x4a0024b0
extern reg omap5430_control_conf_mmcx_adpdat1paden_sel;
#define OMAP5430_CONTROL_CONF_MMCX_OCPL4IDLEREQ_SEL		0x4a0024b4
extern reg omap5430_control_conf_mmcx_ocpl4idlereq_sel;
#define OMAP5430_CONTROL_CONF_MMCX_OCPL3MWAIT_SEL		0x4a0024b8
extern reg omap5430_control_conf_mmcx_ocpl3mwait_sel;
#define OMAP5430_CONTROL_CONF_MMCX_PIRFFRET_SEL			0x4a0024bc
extern reg omap5430_control_conf_mmcx_pirffret_sel;
#define OMAP5430_CONTROL_CONF_MMCX_OCPL4SIDLEACKO1_SEL		0x4a0024c0
extern reg omap5430_control_conf_mmcx_ocpl4sidleacko1_sel;
#define OMAP5430_CONTROL_CONF_MMCX_OCPL4SIDLEACKO0_SEL		0x4a0024c4
extern reg omap5430_control_conf_mmcx_ocpl4sidleacko0_sel;
#define OMAP5430_CONTROL_CONF_MMCX_OCPL3MSTANDBYO_SEL		0x4a0024c8
extern reg omap5430_control_conf_mmcx_ocpl3mstandbyo_sel;
#define OMAP5430_CONTROL_CONF_MMCX_SWAKEUP_SEL			0x4a0024cc
extern reg omap5430_control_conf_mmcx_swakeup_sel;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_0		0x4a0024d0
extern reg omap5430_control_core_conf_debug_sel_tst_0;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_1		0x4a0024d4
extern reg omap5430_control_core_conf_debug_sel_tst_1;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_2		0x4a0024d8
extern reg omap5430_control_core_conf_debug_sel_tst_2;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_3		0x4a0024dc
extern reg omap5430_control_core_conf_debug_sel_tst_3;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_4		0x4a0024e0
extern reg omap5430_control_core_conf_debug_sel_tst_4;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_5		0x4a0024e4
extern reg omap5430_control_core_conf_debug_sel_tst_5;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_6		0x4a0024e8
extern reg omap5430_control_core_conf_debug_sel_tst_6;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_7		0x4a0024ec
extern reg omap5430_control_core_conf_debug_sel_tst_7;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_8		0x4a0024f0
extern reg omap5430_control_core_conf_debug_sel_tst_8;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_9		0x4a0024f4
extern reg omap5430_control_core_conf_debug_sel_tst_9;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_10		0x4a0024f8
extern reg omap5430_control_core_conf_debug_sel_tst_10;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_11		0x4a0024fc
extern reg omap5430_control_core_conf_debug_sel_tst_11;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_12		0x4a002500
extern reg omap5430_control_core_conf_debug_sel_tst_12;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_13		0x4a002504
extern reg omap5430_control_core_conf_debug_sel_tst_13;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_14		0x4a002508
extern reg omap5430_control_core_conf_debug_sel_tst_14;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_15		0x4a00250c
extern reg omap5430_control_core_conf_debug_sel_tst_15;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_16		0x4a002510
extern reg omap5430_control_core_conf_debug_sel_tst_16;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_17		0x4a002514
extern reg omap5430_control_core_conf_debug_sel_tst_17;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_18		0x4a002518
extern reg omap5430_control_core_conf_debug_sel_tst_18;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_19		0x4a00251c
extern reg omap5430_control_core_conf_debug_sel_tst_19;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_20		0x4a002520
extern reg omap5430_control_core_conf_debug_sel_tst_20;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_21		0x4a002524
extern reg omap5430_control_core_conf_debug_sel_tst_21;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_22		0x4a002528
extern reg omap5430_control_core_conf_debug_sel_tst_22;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_23		0x4a00252c
extern reg omap5430_control_core_conf_debug_sel_tst_23;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_24		0x4a002530
extern reg omap5430_control_core_conf_debug_sel_tst_24;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_25		0x4a002534
extern reg omap5430_control_core_conf_debug_sel_tst_25;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_26		0x4a002538
extern reg omap5430_control_core_conf_debug_sel_tst_26;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_27		0x4a00253c
extern reg omap5430_control_core_conf_debug_sel_tst_27;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_28		0x4a002540
extern reg omap5430_control_core_conf_debug_sel_tst_28;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_29		0x4a002544
extern reg omap5430_control_core_conf_debug_sel_tst_29;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_30		0x4a002548
extern reg omap5430_control_core_conf_debug_sel_tst_30;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_31		0x4a00254c
extern reg omap5430_control_core_conf_debug_sel_tst_31;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_32		0x4a002550
extern reg omap5430_control_core_conf_debug_sel_tst_32;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_33		0x4a002554
extern reg omap5430_control_core_conf_debug_sel_tst_33;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_34		0x4a002558
extern reg omap5430_control_core_conf_debug_sel_tst_34;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_35		0x4a00255c
extern reg omap5430_control_core_conf_debug_sel_tst_35;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_36		0x4a002560
extern reg omap5430_control_core_conf_debug_sel_tst_36;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_37		0x4a002564
extern reg omap5430_control_core_conf_debug_sel_tst_37;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_38		0x4a002568
extern reg omap5430_control_core_conf_debug_sel_tst_38;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_39		0x4a00256c
extern reg omap5430_control_core_conf_debug_sel_tst_39;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_40		0x4a002570
extern reg omap5430_control_core_conf_debug_sel_tst_40;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_41		0x4a002574
extern reg omap5430_control_core_conf_debug_sel_tst_41;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_42		0x4a002578
extern reg omap5430_control_core_conf_debug_sel_tst_42;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_43		0x4a00257c
extern reg omap5430_control_core_conf_debug_sel_tst_43;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_44		0x4a002580
extern reg omap5430_control_core_conf_debug_sel_tst_44;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_45		0x4a002584
extern reg omap5430_control_core_conf_debug_sel_tst_45;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_46		0x4a002588
extern reg omap5430_control_core_conf_debug_sel_tst_46;
#define OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_47		0x4a00258c
extern reg omap5430_control_core_conf_debug_sel_tst_47;
#define OMAP5430_CONTROL_CORE_CONF_XBAR_SEL_0			0x4a0025dc
extern reg omap5430_control_core_conf_xbar_sel_0;
#define OMAP5430_CONTROL_CORE_CONF_XBAR_SEL_4			0x4a0025e0
extern reg omap5430_control_core_conf_xbar_sel_4;
#define OMAP5430_CONTROL_CORE_CONF_XBAR_SEL_8			0x4a0025e4
extern reg omap5430_control_core_conf_xbar_sel_8;
#define OMAP5430_CONTROL_CORE_CONF_XBAR_SEL_12			0x4a0025e8
extern reg omap5430_control_core_conf_xbar_sel_12;
#define OMAP5430_CONTROL_CORE_CONF_XBAR_SEL_16			0x4a0025ec
extern reg omap5430_control_core_conf_xbar_sel_16;
#define OMAP5430_CONTROL_CORE_CONF_XBAR_SEL_20			0x4a0025f0
extern reg omap5430_control_core_conf_xbar_sel_20;
#define OMAP5430_CONTROL_CORE_CONF_XBAR_SEL_24			0x4a0025f4
extern reg omap5430_control_core_conf_xbar_sel_24;
#define OMAP5430_CONTROL_CORE_CONF_XBAR_SEL_28			0x4a0025f8
extern reg omap5430_control_core_conf_xbar_sel_28;
#define OMAP5430_CONTROL_CORE_CONF_XBAR_BYPASS			0x4a0025fc
extern reg omap5430_control_core_conf_xbar_bypass;
#define OMAP5430ES1_CTRL_MODULE_CORE_MOD_REGCOUNT		189
extern reg *omap5430es1_ctrl_module_core_mod[OMAP5430ES1_CTRL_MODULE_CORE_MOD_REGCOUNT + 1];
#define OMAP5430_CTRL_MODULE_CORE_MOD_REGCOUNT			204
extern reg *omap5430_ctrl_module_core_mod[OMAP5430_CTRL_MODULE_CORE_MOD_REGCOUNT + 1];


#endif
