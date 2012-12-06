/*
 *
 * @Component			OMAPCONF
 * @Filename			cm54xxes1-defs.h
 * @Description			OMAP5 ES1 CM Registers Definitions & Functions
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


#ifndef __CM54XXES1_DEFS_H__
#define __CM54XXES1_DEFS_H__

#include <reg.h>
#include <dpll.h>
#include <stdio.h>

#define OMAP5430ES1_CM_DSS_CLKSTCTRL				0x4a009100
extern reg omap5430es1_cm_dss_clkstctrl;
#define OMAP5430ES1_CM_DSS_STATICDEP				0x4a009104
extern reg omap5430es1_cm_dss_staticdep;
#define OMAP5430ES1_CM_DSS_DYNAMICDEP				0x4a009108
extern reg omap5430es1_cm_dss_dynamicdep;
#define OMAP5430ES1_CM_DSS_DSS_CLKCTRL				0x4a009120
extern reg omap5430es1_cm_dss_dss_clkctrl;
#define OMAP5430ES1_CM_DSS_BB2D_CLKCTRL				0x4a009130
extern reg omap5430es1_cm_dss_bb2d_clkctrl;
#define OMAP5430ES1_DSS_CM_CORE_MOD_REGCOUNT			5
extern reg *omap5430es1_dss_cm_core_mod[OMAP5430ES1_DSS_CM_CORE_MOD_REGCOUNT + 1];

#define OMAP5430ES1_CMI_IDENTICATION				0x4a009f00
extern reg omap5430es1_cmi_identication;
#define OMAP5430ES1_CMI_SYS_CONFIG				0x4a009f10
extern reg omap5430es1_cmi_sys_config;
#define OMAP5430ES1_CMI_STATUS					0x4a009f14
extern reg omap5430es1_cmi_status;
#define OMAP5430ES1_CMI_CONFIGURATION				0x4a009f24
extern reg omap5430es1_cmi_configuration;
#define OMAP5430ES1_CMI_CLASS_FILTERING				0x4a009f28
extern reg omap5430es1_cmi_class_filtering;
#define OMAP5430ES1_CMI_TRIGGERING				0x4a009f2c
extern reg omap5430es1_cmi_triggering;
#define OMAP5430ES1_CMI_SAMPLING				0x4a009f30
extern reg omap5430es1_cmi_sampling;
#define OMAP5430ES1_INSTR_CM_CORE_MOD_REGCOUNT			7
extern reg *omap5430es1_instr_cm_core_mod[OMAP5430ES1_INSTR_CM_CORE_MOD_REGCOUNT + 1];

#define OMAP5430ES1_CM_L3MAIN1_CLKSTCTRL			0x4a008700
extern reg omap5430es1_cm_l3main1_clkstctrl;
#define OMAP5430ES1_CM_L3MAIN1_DYNAMICDEP			0x4a008708
extern reg omap5430es1_cm_l3main1_dynamicdep;
#define OMAP5430ES1_CM_L3MAIN1_L3_MAIN_1_CLKCTRL		0x4a008720
extern reg omap5430es1_cm_l3main1_l3_main_1_clkctrl;
#define OMAP5430ES1_CM_L3MAIN2_CLKSTCTRL			0x4a008800
extern reg omap5430es1_cm_l3main2_clkstctrl;
#define OMAP5430ES1_CM_L3MAIN2_DYNAMICDEP			0x4a008808
extern reg omap5430es1_cm_l3main2_dynamicdep;
#define OMAP5430ES1_CM_L3MAIN2_L3_MAIN_2_CLKCTRL		0x4a008820
extern reg omap5430es1_cm_l3main2_l3_main_2_clkctrl;
#define OMAP5430ES1_CM_L3MAIN2_GPMC_CLKCTRL			0x4a008828
extern reg omap5430es1_cm_l3main2_gpmc_clkctrl;
#define OMAP5430ES1_CM_L3MAIN2_OCMC_RAM_CLKCTRL			0x4a008830
extern reg omap5430es1_cm_l3main2_ocmc_ram_clkctrl;
#define OMAP5430ES1_CM_IPU_CLKSTCTRL				0x4a008900
extern reg omap5430es1_cm_ipu_clkstctrl;
#define OMAP5430ES1_CM_IPU_STATICDEP				0x4a008904
extern reg omap5430es1_cm_ipu_staticdep;
#define OMAP5430ES1_CM_IPU_DYNAMICDEP				0x4a008908
extern reg omap5430es1_cm_ipu_dynamicdep;
#define OMAP5430ES1_CM_IPU_IPU_CLKCTRL				0x4a008920
extern reg omap5430es1_cm_ipu_ipu_clkctrl;
#define OMAP5430ES1_CM_DMA_CLKSTCTRL				0x4a008a00
extern reg omap5430es1_cm_dma_clkstctrl;
#define OMAP5430ES1_CM_DMA_STATICDEP				0x4a008a04
extern reg omap5430es1_cm_dma_staticdep;
#define OMAP5430ES1_CM_DMA_DYNAMICDEP				0x4a008a08
extern reg omap5430es1_cm_dma_dynamicdep;
#define OMAP5430ES1_CM_DMA_DMA_SYSTEM_CLKCTRL			0x4a008a20
extern reg omap5430es1_cm_dma_dma_system_clkctrl;
#define OMAP5430ES1_CM_EMIF_CLKSTCTRL				0x4a008b00
extern reg omap5430es1_cm_emif_clkstctrl;
#define OMAP5430ES1_CM_EMIF_DMM_CLKCTRL				0x4a008b20
extern reg omap5430es1_cm_emif_dmm_clkctrl;
#define OMAP5430ES1_CM_EMIF_EMIF_OCP_FW_CLKCTRL			0x4a008b28
extern reg omap5430es1_cm_emif_emif_ocp_fw_clkctrl;
#define OMAP5430ES1_CM_EMIF_EMIF1_CLKCTRL			0x4a008b30
extern reg omap5430es1_cm_emif_emif1_clkctrl;
#define OMAP5430ES1_CM_EMIF_EMIF2_CLKCTRL			0x4a008b38
extern reg omap5430es1_cm_emif_emif2_clkctrl;
#define OMAP5430ES1_CM_EMIF_EMIF_DLL_CLKCTRL			0x4a008b40
extern reg omap5430es1_cm_emif_emif_dll_clkctrl;
#define OMAP5430ES1_CM_C2C_CLKSTCTRL				0x4a008c00
extern reg omap5430es1_cm_c2c_clkstctrl;
#define OMAP5430ES1_CM_C2C_STATICDEP				0x4a008c04
extern reg omap5430es1_cm_c2c_staticdep;
#define OMAP5430ES1_CM_C2C_DYNAMICDEP				0x4a008c08
extern reg omap5430es1_cm_c2c_dynamicdep;
#define OMAP5430ES1_CM_C2C_C2C_CLKCTRL				0x4a008c20
extern reg omap5430es1_cm_c2c_c2c_clkctrl;
#define OMAP5430ES1_CM_C2C_MODEM_ICR_CLKCTRL			0x4a008c28
extern reg omap5430es1_cm_c2c_modem_icr_clkctrl;
#define OMAP5430ES1_CM_C2C_C2C_OCP_FW_CLKCTRL			0x4a008c30
extern reg omap5430es1_cm_c2c_c2c_ocp_fw_clkctrl;
#define OMAP5430ES1_CM_MIPIEXT_CLKSTCTRL			0x4a008c80
extern reg omap5430es1_cm_mipiext_clkstctrl;
#define OMAP5430ES1_CM_MIPIEXT_STATICDEP			0x4a008c84
extern reg omap5430es1_cm_mipiext_staticdep;
#define OMAP5430ES1_CM_MIPIEXT_DYNAMICDEP			0x4a008c88
extern reg omap5430es1_cm_mipiext_dynamicdep;
#define OMAP5430ES1_CM_MIPIEXT_UNIPRO1_CLKCTRL			0x4a008ca0
extern reg omap5430es1_cm_mipiext_unipro1_clkctrl;
#define OMAP5430ES1_CM_MIPIEXT_LLI_CLKCTRL			0x4a008ca8
extern reg omap5430es1_cm_mipiext_lli_clkctrl;
#define OMAP5430ES1_CM_MIPIEXT_LLI_OCP_FW_CLKCTRL		0x4a008cb0
extern reg omap5430es1_cm_mipiext_lli_ocp_fw_clkctrl;
#define OMAP5430ES1_CM_MIPIEXT_MPHY_CLKCTRL			0x4a008cb8
extern reg omap5430es1_cm_mipiext_mphy_clkctrl;
#define OMAP5430ES1_CM_L4CFG_CLKSTCTRL				0x4a008d00
extern reg omap5430es1_cm_l4cfg_clkstctrl;
#define OMAP5430ES1_CM_L4CFG_DYNAMICDEP				0x4a008d08
extern reg omap5430es1_cm_l4cfg_dynamicdep;
#define OMAP5430ES1_CM_L4CFG_L4_CFG_CLKCTRL			0x4a008d20
extern reg omap5430es1_cm_l4cfg_l4_cfg_clkctrl;
#define OMAP5430ES1_CM_L4CFG_SPINLOCK_CLKCTRL			0x4a008d28
extern reg omap5430es1_cm_l4cfg_spinlock_clkctrl;
#define OMAP5430ES1_CM_L4CFG_MAILBOX_CLKCTRL			0x4a008d30
extern reg omap5430es1_cm_l4cfg_mailbox_clkctrl;
#define OMAP5430ES1_CM_L4CFG_SAR_ROM_CLKCTRL			0x4a008d38
extern reg omap5430es1_cm_l4cfg_sar_rom_clkctrl;
#define OMAP5430ES1_CM_L4CFG_OCP2SCP2_CLKCTRL			0x4a008d40
extern reg omap5430es1_cm_l4cfg_ocp2scp2_clkctrl;
#define OMAP5430ES1_CM_L3INSTR_CLKSTCTRL			0x4a008e00
extern reg omap5430es1_cm_l3instr_clkstctrl;
#define OMAP5430ES1_CM_L3INSTR_L3_MAIN_3_CLKCTRL		0x4a008e20
extern reg omap5430es1_cm_l3instr_l3_main_3_clkctrl;
#define OMAP5430ES1_CM_L3INSTR_L3_INSTR_CLKCTRL			0x4a008e28
extern reg omap5430es1_cm_l3instr_l3_instr_clkctrl;
#define OMAP5430ES1_CM_L3INSTR_OCP_WP_NOC_CLKCTRL		0x4a008e40
extern reg omap5430es1_cm_l3instr_ocp_wp_noc_clkctrl;
#define OMAP5430ES1_CM_L3INSTR_DLL_AGING_CLKCTRL		0x4a008e48
extern reg omap5430es1_cm_l3instr_dll_aging_clkctrl;
#define OMAP5430ES1_CORE_CM_CORE_MOD_REGCOUNT			47
extern reg *omap5430es1_core_cm_core_mod[OMAP5430ES1_CORE_CM_CORE_MOD_REGCOUNT + 1];

#define OMAP5430ES1_CM_CUSTEFUSE_CLKSTCTRL			0x4a009600
extern reg omap5430es1_cm_custefuse_clkstctrl;
#define OMAP5430ES1_CM_CUSTEFUSE_EFUSE_CTRL_CUST_CLKCTRL	0x4a009620
extern reg omap5430es1_cm_custefuse_efuse_ctrl_cust_clkctrl;
#define OMAP5430ES1_CUSTEFUSE_CM_CORE_MOD_REGCOUNT		2
extern reg *omap5430es1_custefuse_cm_core_mod[OMAP5430ES1_CUSTEFUSE_CM_CORE_MOD_REGCOUNT + 1];

#define OMAP5430ES1_CM_ABE_CLKSTCTRL				0x4a004500
extern reg omap5430es1_cm_abe_clkstctrl;
#define OMAP5430ES1_CM_ABE_L4_ABE_CLKCTRL			0x4a004520
extern reg omap5430es1_cm_abe_l4_abe_clkctrl;
#define OMAP5430ES1_CM_ABE_AESS_CLKCTRL				0x4a004528
extern reg omap5430es1_cm_abe_aess_clkctrl;
#define OMAP5430ES1_CM_ABE_MCPDM_CLKCTRL			0x4a004530
extern reg omap5430es1_cm_abe_mcpdm_clkctrl;
#define OMAP5430ES1_CM_ABE_DMIC_CLKCTRL				0x4a004538
extern reg omap5430es1_cm_abe_dmic_clkctrl;
#define OMAP5430ES1_CM_ABE_MCASP_CLKCTRL			0x4a004540
extern reg omap5430es1_cm_abe_mcasp_clkctrl;
#define OMAP5430ES1_CM_ABE_MCBSP1_CLKCTRL			0x4a004548
extern reg omap5430es1_cm_abe_mcbsp1_clkctrl;
#define OMAP5430ES1_CM_ABE_MCBSP2_CLKCTRL			0x4a004550
extern reg omap5430es1_cm_abe_mcbsp2_clkctrl;
#define OMAP5430ES1_CM_ABE_MCBSP3_CLKCTRL			0x4a004558
extern reg omap5430es1_cm_abe_mcbsp3_clkctrl;
#define OMAP5430ES1_CM_ABE_SLIMBUS1_CLKCTRL			0x4a004560
extern reg omap5430es1_cm_abe_slimbus1_clkctrl;
#define OMAP5430ES1_CM_ABE_TIMER5_CLKCTRL			0x4a004568
extern reg omap5430es1_cm_abe_timer5_clkctrl;
#define OMAP5430ES1_CM_ABE_TIMER6_CLKCTRL			0x4a004570
extern reg omap5430es1_cm_abe_timer6_clkctrl;
#define OMAP5430ES1_CM_ABE_TIMER7_CLKCTRL			0x4a004578
extern reg omap5430es1_cm_abe_timer7_clkctrl;
#define OMAP5430ES1_CM_ABE_TIMER8_CLKCTRL			0x4a004580
extern reg omap5430es1_cm_abe_timer8_clkctrl;
#define OMAP5430ES1_CM_ABE_WD_TIMER3_CLKCTRL			0x4a004588
extern reg omap5430es1_cm_abe_wd_timer3_clkctrl;
#define OMAP5430ES1_ABE_CM_CORE_AON_MOD_REGCOUNT			15
extern reg *omap5430es1_abe_cm_core_aon_mod[OMAP5430ES1_ABE_CM_CORE_AON_MOD_REGCOUNT + 1];

#define OMAP5430ES1_CM_GPU_CLKSTCTRL				0x4a009200
extern reg omap5430es1_cm_gpu_clkstctrl;
#define OMAP5430ES1_CM_GPU_STATICDEP				0x4a009204
extern reg omap5430es1_cm_gpu_staticdep;
#define OMAP5430ES1_CM_GPU_DYNAMICDEP				0x4a009208
extern reg omap5430es1_cm_gpu_dynamicdep;
#define OMAP5430ES1_CM_GPU_GPU_CLKCTRL				0x4a009220
extern reg omap5430es1_cm_gpu_gpu_clkctrl;
#define OMAP5430ES1_GPU_CM_CORE_MOD_REGCOUNT			4
extern reg *omap5430es1_gpu_cm_core_mod[OMAP5430ES1_GPU_CM_CORE_MOD_REGCOUNT + 1];

#define OMAP5430ES1_CM_EMU_CLKSTCTRL				0x4ae07a00
extern reg omap5430es1_cm_emu_clkstctrl;
#define OMAP5430ES1_CM_EMU_DYNAMICDEP				0x4ae07a08
extern reg omap5430es1_cm_emu_dynamicdep;
#define OMAP5430ES1_CM_EMU_DEBUGSS_CLKCTRL			0x4ae07a20
extern reg omap5430es1_cm_emu_debugss_clkctrl;
#define OMAP5430ES1_EMU_CM_MOD_REGCOUNT				3
extern reg *omap5430es1_emu_cm_mod[OMAP5430ES1_EMU_CM_MOD_REGCOUNT + 1];

#define OMAP5430ES1_REVISION_CM_CORE				0x4a008000
extern reg omap5430es1_revision_cm_core;
#define OMAP5430ES1_CM_CM_CORE_PROFILING_CLKCTRL		0x4a008040
extern reg omap5430es1_cm_cm_core_profiling_clkctrl;
#define OMAP5430ES1_CM_CORE_DEBUG_CFG				0x4a0080f0
extern reg omap5430es1_cm_core_debug_cfg;
#define OMAP5430ES1_INTRCONN_SOCKET_CM_CORE_MOD_REGCOUNT		3
extern reg *omap5430es1_intrconn_socket_cm_core_mod[OMAP5430ES1_INTRCONN_SOCKET_CM_CORE_MOD_REGCOUNT + 1];

#define OMAP5430ES1_CMI_IDENTICATION_AON			0x4a004f00
extern reg omap5430es1_cmi_identication_aon;
#define OMAP5430ES1_CMI_SYS_CONFIG_AON				0x4a004f10
extern reg omap5430es1_cmi_sys_config_aon;
#define OMAP5430ES1_CMI_STATUS_AON				0x4a004f14
extern reg omap5430es1_cmi_status_aon;
#define OMAP5430ES1_CMI_CONFIGURATION_AON			0x4a004f24
extern reg omap5430es1_cmi_configuration_aon;
#define OMAP5430ES1_CMI_CLASS_FILTERING_AON			0x4a004f28
extern reg omap5430es1_cmi_class_filtering_aon;
#define OMAP5430ES1_CMI_TRIGGERING_AON				0x4a004f2c
extern reg omap5430es1_cmi_triggering_aon;
#define OMAP5430ES1_CMI_SAMPLING_AON				0x4a004f30
extern reg omap5430es1_cmi_sampling_aon;
#define OMAP5430ES1_INSTR_CM_CORE_AON_MOD_REGCOUNT			7
extern reg *omap5430es1_instr_cm_core_aon_mod[OMAP5430ES1_INSTR_CM_CORE_AON_MOD_REGCOUNT + 1];

#define OMAP5430ES1_CM_CLKSEL_CORE				0x4a004100
extern reg omap5430es1_cm_clksel_core;
#define OMAP5430ES1_CM_CLKSEL_ABE				0x4a004108
extern reg omap5430es1_cm_clksel_abe;
#define OMAP5430ES1_CM_DLL_CTRL					0x4a004110
extern reg omap5430es1_cm_dll_ctrl;
#define OMAP5430ES1_CM_CLKMODE_DPLL_CORE			0x4a004120
extern reg omap5430es1_cm_clkmode_dpll_core;
#define OMAP5430ES1_CM_IDLEST_DPLL_CORE				0x4a004124
extern reg omap5430es1_cm_idlest_dpll_core;
#define OMAP5430ES1_CM_AUTOIDLE_DPLL_CORE			0x4a004128
extern reg omap5430es1_cm_autoidle_dpll_core;
#define OMAP5430ES1_CM_CLKSEL_DPLL_CORE				0x4a00412c
extern reg omap5430es1_cm_clksel_dpll_core;
#define OMAP5430ES1_CM_DIV_M2_DPLL_CORE				0x4a004130
extern reg omap5430es1_cm_div_m2_dpll_core;
#define OMAP5430ES1_CM_DIV_M3_DPLL_CORE				0x4a004134
extern reg omap5430es1_cm_div_m3_dpll_core;
#define OMAP5430ES1_CM_DIV_H11_DPLL_CORE			0x4a004138
extern reg omap5430es1_cm_div_h11_dpll_core;
#define OMAP5430ES1_CM_DIV_H12_DPLL_CORE			0x4a00413c
extern reg omap5430es1_cm_div_h12_dpll_core;
#define OMAP5430ES1_CM_DIV_H13_DPLL_CORE			0x4a004140
extern reg omap5430es1_cm_div_h13_dpll_core;
#define OMAP5430ES1_CM_DIV_H14_DPLL_CORE			0x4a004144
extern reg omap5430es1_cm_div_h14_dpll_core;
#define OMAP5430ES1_CM_SSC_DELTAMSTEP_DPLL_CORE			0x4a004148
extern reg omap5430es1_cm_ssc_deltamstep_dpll_core;
#define OMAP5430ES1_CM_SSC_MODFREQDIV_DPLL_CORE			0x4a00414c
extern reg omap5430es1_cm_ssc_modfreqdiv_dpll_core;
#define OMAP5430ES1_CM_DIV_H22_DPLL_CORE			0x4a004154
extern reg omap5430es1_cm_div_h22_dpll_core;
#define OMAP5430ES1_CM_DIV_H23_DPLL_CORE			0x4a004158
extern reg omap5430es1_cm_div_h23_dpll_core;
#define OMAP5430ES1_CM_CLKMODE_DPLL_MPU				0x4a004160
extern reg omap5430es1_cm_clkmode_dpll_mpu;
#define OMAP5430ES1_CM_IDLEST_DPLL_MPU				0x4a004164
extern reg omap5430es1_cm_idlest_dpll_mpu;
#define OMAP5430ES1_CM_AUTOIDLE_DPLL_MPU			0x4a004168
extern reg omap5430es1_cm_autoidle_dpll_mpu;
#define OMAP5430ES1_CM_CLKSEL_DPLL_MPU				0x4a00416c
extern reg omap5430es1_cm_clksel_dpll_mpu;
#define OMAP5430ES1_CM_DIV_M2_DPLL_MPU				0x4a004170
extern reg omap5430es1_cm_div_m2_dpll_mpu;
#define OMAP5430ES1_CM_SSC_DELTAMSTEP_DPLL_MPU			0x4a004188
extern reg omap5430es1_cm_ssc_deltamstep_dpll_mpu;
#define OMAP5430ES1_CM_SSC_MODFREQDIV_DPLL_MPU			0x4a00418c
extern reg omap5430es1_cm_ssc_modfreqdiv_dpll_mpu;
#define OMAP5430ES1_CM_BYPCLK_DPLL_MPU				0x4a00419c
extern reg omap5430es1_cm_bypclk_dpll_mpu;
#define OMAP5430ES1_CM_CLKMODE_DPLL_IVA				0x4a0041a0
extern reg omap5430es1_cm_clkmode_dpll_iva;
#define OMAP5430ES1_CM_IDLEST_DPLL_IVA				0x4a0041a4
extern reg omap5430es1_cm_idlest_dpll_iva;
#define OMAP5430ES1_CM_AUTOIDLE_DPLL_IVA			0x4a0041a8
extern reg omap5430es1_cm_autoidle_dpll_iva;
#define OMAP5430ES1_CM_CLKSEL_DPLL_IVA				0x4a0041ac
extern reg omap5430es1_cm_clksel_dpll_iva;
#define OMAP5430ES1_CM_DIV_H11_DPLL_IVA				0x4a0041b8
extern reg omap5430es1_cm_div_h11_dpll_iva;
#define OMAP5430ES1_CM_DIV_H12_DPLL_IVA				0x4a0041bc
extern reg omap5430es1_cm_div_h12_dpll_iva;
#define OMAP5430ES1_CM_SSC_DELTAMSTEP_DPLL_IVA			0x4a0041c8
extern reg omap5430es1_cm_ssc_deltamstep_dpll_iva;
#define OMAP5430ES1_CM_SSC_MODFREQDIV_DPLL_IVA			0x4a0041cc
extern reg omap5430es1_cm_ssc_modfreqdiv_dpll_iva;
#define OMAP5430ES1_CM_BYPCLK_DPLL_IVA				0x4a0041dc
extern reg omap5430es1_cm_bypclk_dpll_iva;
#define OMAP5430ES1_CM_CLKMODE_DPLL_ABE				0x4a0041e0
extern reg omap5430es1_cm_clkmode_dpll_abe;
#define OMAP5430ES1_CM_IDLEST_DPLL_ABE				0x4a0041e4
extern reg omap5430es1_cm_idlest_dpll_abe;
#define OMAP5430ES1_CM_AUTOIDLE_DPLL_ABE			0x4a0041e8
extern reg omap5430es1_cm_autoidle_dpll_abe;
#define OMAP5430ES1_CM_CLKSEL_DPLL_ABE				0x4a0041ec
extern reg omap5430es1_cm_clksel_dpll_abe;
#define OMAP5430ES1_CM_DIV_M2_DPLL_ABE				0x4a0041f0
extern reg omap5430es1_cm_div_m2_dpll_abe;
#define OMAP5430ES1_CM_DIV_M3_DPLL_ABE				0x4a0041f4
extern reg omap5430es1_cm_div_m3_dpll_abe;
#define OMAP5430ES1_CM_SSC_DELTAMSTEP_DPLL_ABE			0x4a004208
extern reg omap5430es1_cm_ssc_deltamstep_dpll_abe;
#define OMAP5430ES1_CM_SSC_MODFREQDIV_DPLL_ABE			0x4a00420c
extern reg omap5430es1_cm_ssc_modfreqdiv_dpll_abe;
#define OMAP5430ES1_CM_SHADOW_FREQ_CONFIG1			0x4a004260
extern reg omap5430es1_cm_shadow_freq_config1;
#define OMAP5430ES1_CM_SHADOW_FREQ_CONFIG2			0x4a004264
extern reg omap5430es1_cm_shadow_freq_config2;
#define OMAP5430ES1_CM_DYN_DEP_PRESCAL				0x4a004270
extern reg omap5430es1_cm_dyn_dep_prescal;
#define OMAP5430ES1_CM_RESTORE_ST				0x4a004280
extern reg omap5430es1_cm_restore_st;
#define OMAP5430ES1_CKGEN_CM_CORE_AON_MOD_REGCOUNT		46
extern reg *omap5430es1_ckgen_cm_core_aon_mod[OMAP5430ES1_CKGEN_CM_CORE_AON_MOD_REGCOUNT + 1];

#define OMAP5430ES1_CM_CLKSEL_USB_60MHZ				0x4a008104
extern reg omap5430es1_cm_clksel_usb_60mhz;
#define OMAP5430ES1_CM_CLKMODE_DPLL_PER				0x4a008140
extern reg omap5430es1_cm_clkmode_dpll_per;
#define OMAP5430ES1_CM_IDLEST_DPLL_PER				0x4a008144
extern reg omap5430es1_cm_idlest_dpll_per;
#define OMAP5430ES1_CM_AUTOIDLE_DPLL_PER			0x4a008148
extern reg omap5430es1_cm_autoidle_dpll_per;
#define OMAP5430ES1_CM_CLKSEL_DPLL_PER				0x4a00814c
extern reg omap5430es1_cm_clksel_dpll_per;
#define OMAP5430ES1_CM_DIV_M2_DPLL_PER				0x4a008150
extern reg omap5430es1_cm_div_m2_dpll_per;
#define OMAP5430ES1_CM_DIV_M3_DPLL_PER				0x4a008154
extern reg omap5430es1_cm_div_m3_dpll_per;
#define OMAP5430ES1_CM_DIV_H11_DPLL_PER				0x4a008158
extern reg omap5430es1_cm_div_h11_dpll_per;
#define OMAP5430ES1_CM_DIV_H12_DPLL_PER				0x4a00815c
extern reg omap5430es1_cm_div_h12_dpll_per;
#define OMAP5430ES1_CM_DIV_H14_DPLL_PER				0x4a008164
extern reg omap5430es1_cm_div_h14_dpll_per;
#define OMAP5430ES1_CM_SSC_DELTAMSTEP_DPLL_PER			0x4a008168
extern reg omap5430es1_cm_ssc_deltamstep_dpll_per;
#define OMAP5430ES1_CM_SSC_MODFREQDIV_DPLL_PER			0x4a00816c
extern reg omap5430es1_cm_ssc_modfreqdiv_dpll_per;
#define OMAP5430ES1_CM_CLKMODE_DPLL_USB				0x4a008180
extern reg omap5430es1_cm_clkmode_dpll_usb;
#define OMAP5430ES1_CM_IDLEST_DPLL_USB				0x4a008184
extern reg omap5430es1_cm_idlest_dpll_usb;
#define OMAP5430ES1_CM_AUTOIDLE_DPLL_USB			0x4a008188
extern reg omap5430es1_cm_autoidle_dpll_usb;
#define OMAP5430ES1_CM_CLKSEL_DPLL_USB				0x4a00818c
extern reg omap5430es1_cm_clksel_dpll_usb;
#define OMAP5430ES1_CM_DIV_M2_DPLL_USB				0x4a008190
extern reg omap5430es1_cm_div_m2_dpll_usb;
#define OMAP5430ES1_CM_SSC_DELTAMSTEP_DPLL_USB			0x4a0081a8
extern reg omap5430es1_cm_ssc_deltamstep_dpll_usb;
#define OMAP5430ES1_CM_SSC_MODFREQDIV_DPLL_USB			0x4a0081ac
extern reg omap5430es1_cm_ssc_modfreqdiv_dpll_usb;
#define OMAP5430ES1_CM_CLKDCOLDO_DPLL_USB			0x4a0081b4
extern reg omap5430es1_cm_clkdcoldo_dpll_usb;
#define OMAP5430ES1_CM_CLKMODE_DPLL_UNIPRO2			0x4a0081c0
extern reg omap5430es1_cm_clkmode_dpll_unipro2;
#define OMAP5430ES1_CM_IDLEST_DPLL_UNIPRO2			0x4a0081c4
extern reg omap5430es1_cm_idlest_dpll_unipro2;
#define OMAP5430ES1_CM_AUTOIDLE_DPLL_UNIPRO2			0x4a0081c8
extern reg omap5430es1_cm_autoidle_dpll_unipro2;
#define OMAP5430ES1_CM_CLKSEL_DPLL_UNIPRO2			0x4a0081cc
extern reg omap5430es1_cm_clksel_dpll_unipro2;
#define OMAP5430ES1_CM_DIV_M2_DPLL_UNIPRO2			0x4a0081d0
extern reg omap5430es1_cm_div_m2_dpll_unipro2;
#define OMAP5430ES1_CM_SSC_DELTAMSTEP_DPLL_UNIPRO2		0x4a0081e8
extern reg omap5430es1_cm_ssc_deltamstep_dpll_unipro2;
#define OMAP5430ES1_CM_SSC_MODFREQDIV_DPLL_UNIPRO2		0x4a0081ec
extern reg omap5430es1_cm_ssc_modfreqdiv_dpll_unipro2;
#define OMAP5430ES1_CM_CLKDCOLDO_DPLL_UNIPRO2			0x4a0081f4
extern reg omap5430es1_cm_clkdcoldo_dpll_unipro2;
#define OMAP5430ES1_CM_CLKMODE_DPLL_UNIPRO1			0x4a008200
extern reg omap5430es1_cm_clkmode_dpll_unipro1;
#define OMAP5430ES1_CM_IDLEST_DPLL_UNIPRO1			0x4a008204
extern reg omap5430es1_cm_idlest_dpll_unipro1;
#define OMAP5430ES1_CM_AUTOIDLE_DPLL_UNIPRO1			0x4a008208
extern reg omap5430es1_cm_autoidle_dpll_unipro1;
#define OMAP5430ES1_CM_CLKSEL_DPLL_UNIPRO1			0x4a00820c
extern reg omap5430es1_cm_clksel_dpll_unipro1;
#define OMAP5430ES1_CM_DIV_M2_DPLL_UNIPRO1			0x4a008210
extern reg omap5430es1_cm_div_m2_dpll_unipro1;
#define OMAP5430ES1_CM_SSC_DELTAMSTEP_DPLL_UNIPRO1		0x4a008228
extern reg omap5430es1_cm_ssc_deltamstep_dpll_unipro1;
#define OMAP5430ES1_CM_SSC_MODFREQDIV_DPLL_UNIPRO1		0x4a00822c
extern reg omap5430es1_cm_ssc_modfreqdiv_dpll_unipro1;
#define OMAP5430ES1_CM_CLKDCOLDO_DPLL_UNIPRO1			0x4a008234
extern reg omap5430es1_cm_clkdcoldo_dpll_unipro1;
#define OMAP5430ES1_CKGEN_CM_CORE_MOD_REGCOUNT			36
extern reg *omap5430es1_ckgen_cm_core_mod[OMAP5430ES1_CKGEN_CM_CORE_MOD_REGCOUNT + 1];

#define OMAP5430ES1_CM_L4PER_CLKSTCTRL				0x4a009400
extern reg omap5430es1_cm_l4per_clkstctrl;
#define OMAP5430ES1_CM_L4PER_DYNAMICDEP				0x4a009408
extern reg omap5430es1_cm_l4per_dynamicdep;
#define OMAP5430ES1_CM_L4PER_TIMER10_CLKCTRL			0x4a009428
extern reg omap5430es1_cm_l4per_timer10_clkctrl;
#define OMAP5430ES1_CM_L4PER_TIMER11_CLKCTRL			0x4a009430
extern reg omap5430es1_cm_l4per_timer11_clkctrl;
#define OMAP5430ES1_CM_L4PER_TIMER2_CLKCTRL			0x4a009438
extern reg omap5430es1_cm_l4per_timer2_clkctrl;
#define OMAP5430ES1_CM_L4PER_TIMER3_CLKCTRL			0x4a009440
extern reg omap5430es1_cm_l4per_timer3_clkctrl;
#define OMAP5430ES1_CM_L4PER_TIMER4_CLKCTRL			0x4a009448
extern reg omap5430es1_cm_l4per_timer4_clkctrl;
#define OMAP5430ES1_CM_L4PER_TIMER9_CLKCTRL			0x4a009450
extern reg omap5430es1_cm_l4per_timer9_clkctrl;
#define OMAP5430ES1_CM_L4PER_ELM_CLKCTRL			0x4a009458
extern reg omap5430es1_cm_l4per_elm_clkctrl;
#define OMAP5430ES1_CM_L4PER_GPIO2_CLKCTRL			0x4a009460
extern reg omap5430es1_cm_l4per_gpio2_clkctrl;
#define OMAP5430ES1_CM_L4PER_GPIO3_CLKCTRL			0x4a009468
extern reg omap5430es1_cm_l4per_gpio3_clkctrl;
#define OMAP5430ES1_CM_L4PER_GPIO4_CLKCTRL			0x4a009470
extern reg omap5430es1_cm_l4per_gpio4_clkctrl;
#define OMAP5430ES1_CM_L4PER_GPIO5_CLKCTRL			0x4a009478
extern reg omap5430es1_cm_l4per_gpio5_clkctrl;
#define OMAP5430ES1_CM_L4PER_GPIO6_CLKCTRL			0x4a009480
extern reg omap5430es1_cm_l4per_gpio6_clkctrl;
#define OMAP5430ES1_CM_L4PER_HDQ1W_CLKCTRL			0x4a009488
extern reg omap5430es1_cm_l4per_hdq1w_clkctrl;
#define OMAP5430ES1_CM_L4PER_I2C1_CLKCTRL			0x4a0094a0
extern reg omap5430es1_cm_l4per_i2c1_clkctrl;
#define OMAP5430ES1_CM_L4PER_I2C2_CLKCTRL			0x4a0094a8
extern reg omap5430es1_cm_l4per_i2c2_clkctrl;
#define OMAP5430ES1_CM_L4PER_I2C3_CLKCTRL			0x4a0094b0
extern reg omap5430es1_cm_l4per_i2c3_clkctrl;
#define OMAP5430ES1_CM_L4PER_I2C4_CLKCTRL			0x4a0094b8
extern reg omap5430es1_cm_l4per_i2c4_clkctrl;
#define OMAP5430ES1_CM_L4PER_L4_PER_CLKCTRL			0x4a0094c0
extern reg omap5430es1_cm_l4per_l4_per_clkctrl;
#define OMAP5430ES1_CM_L4PER_MCSPI1_CLKCTRL			0x4a0094f0
extern reg omap5430es1_cm_l4per_mcspi1_clkctrl;
#define OMAP5430ES1_CM_L4PER_MCSPI2_CLKCTRL			0x4a0094f8
extern reg omap5430es1_cm_l4per_mcspi2_clkctrl;
#define OMAP5430ES1_CM_L4PER_MCSPI3_CLKCTRL			0x4a009500
extern reg omap5430es1_cm_l4per_mcspi3_clkctrl;
#define OMAP5430ES1_CM_L4PER_MCSPI4_CLKCTRL			0x4a009508
extern reg omap5430es1_cm_l4per_mcspi4_clkctrl;
#define OMAP5430ES1_CM_L4PER_GPIO7_CLKCTRL			0x4a009510
extern reg omap5430es1_cm_l4per_gpio7_clkctrl;
#define OMAP5430ES1_CM_L4PER_GPIO8_CLKCTRL			0x4a009518
extern reg omap5430es1_cm_l4per_gpio8_clkctrl;
#define OMAP5430ES1_CM_L4PER_MMC3_CLKCTRL			0x4a009520
extern reg omap5430es1_cm_l4per_mmc3_clkctrl;
#define OMAP5430ES1_CM_L4PER_MMC4_CLKCTRL			0x4a009528
extern reg omap5430es1_cm_l4per_mmc4_clkctrl;
#define OMAP5430ES1_CM_L4PER_SLIMBUS2_CLKCTRL			0x4a009538
extern reg omap5430es1_cm_l4per_slimbus2_clkctrl;
#define OMAP5430ES1_CM_L4PER_UART1_CLKCTRL			0x4a009540
extern reg omap5430es1_cm_l4per_uart1_clkctrl;
#define OMAP5430ES1_CM_L4PER_UART2_CLKCTRL			0x4a009548
extern reg omap5430es1_cm_l4per_uart2_clkctrl;
#define OMAP5430ES1_CM_L4PER_UART3_CLKCTRL			0x4a009550
extern reg omap5430es1_cm_l4per_uart3_clkctrl;
#define OMAP5430ES1_CM_L4PER_UART4_CLKCTRL			0x4a009558
extern reg omap5430es1_cm_l4per_uart4_clkctrl;
#define OMAP5430ES1_CM_L4PER_MMC5_CLKCTRL			0x4a009560
extern reg omap5430es1_cm_l4per_mmc5_clkctrl;
#define OMAP5430ES1_CM_L4PER_I2C5_CLKCTRL			0x4a009568
extern reg omap5430es1_cm_l4per_i2c5_clkctrl;
#define OMAP5430ES1_CM_L4PER_UART5_CLKCTRL			0x4a009570
extern reg omap5430es1_cm_l4per_uart5_clkctrl;
#define OMAP5430ES1_CM_L4PER_UART6_CLKCTRL			0x4a009578
extern reg omap5430es1_cm_l4per_uart6_clkctrl;
#define OMAP5430ES1_L4PER_CM_CORE_MOD_REGCOUNT			37
extern reg *omap5430es1_l4per_cm_core_mod[OMAP5430ES1_L4PER_CM_CORE_MOD_REGCOUNT + 1];

#define OMAP5430ES1_CM_L3INIT_CLKSTCTRL				0x4a009300
extern reg omap5430es1_cm_l3init_clkstctrl;
#define OMAP5430ES1_CM_L3INIT_STATICDEP				0x4a009304
extern reg omap5430es1_cm_l3init_staticdep;
#define OMAP5430ES1_CM_L3INIT_DYNAMICDEP			0x4a009308
extern reg omap5430es1_cm_l3init_dynamicdep;
#define OMAP5430ES1_CM_L3INIT_MMC1_CLKCTRL			0x4a009328
extern reg omap5430es1_cm_l3init_mmc1_clkctrl;
#define OMAP5430ES1_CM_L3INIT_MMC2_CLKCTRL			0x4a009330
extern reg omap5430es1_cm_l3init_mmc2_clkctrl;
#define OMAP5430ES1_CM_L3INIT_HSI_CLKCTRL			0x4a009338
extern reg omap5430es1_cm_l3init_hsi_clkctrl;
#define OMAP5430ES1_CM_L3INIT_UNIPRO2_CLKCTRL			0x4a009340
extern reg omap5430es1_cm_l3init_unipro2_clkctrl;
#define OMAP5430ES1_CM_L3INIT_MPHY_UNIPRO2_CLKCTRL		0x4a009348
extern reg omap5430es1_cm_l3init_mphy_unipro2_clkctrl;
#define OMAP5430ES1_CM_L3INIT_USB_HOST_HS_CLKCTRL		0x4a009358
extern reg omap5430es1_cm_l3init_usb_host_hs_clkctrl;
#define OMAP5430ES1_CM_L3INIT_USB_TLL_HS_CLKCTRL		0x4a009368
extern reg omap5430es1_cm_l3init_usb_tll_hs_clkctrl;
#define OMAP5430ES1_CM_L3INIT_IEEE1500_2_OCP_CLKCTRL		0x4a009378
extern reg omap5430es1_cm_l3init_ieee1500_2_ocp_clkctrl;
#define OMAP5430ES1_CM_L3INIT_SATA_CLKCTRL			0x4a009388
extern reg omap5430es1_cm_l3init_sata_clkctrl;
#define OMAP5430ES1_CM_L3INIT_OCP2SCP1_CLKCTRL			0x4a0093e0
extern reg omap5430es1_cm_l3init_ocp2scp1_clkctrl;
#define OMAP5430ES1_CM_L3INIT_OCP2SCP3_CLKCTRL			0x4a0093e8
extern reg omap5430es1_cm_l3init_ocp2scp3_clkctrl;
#define OMAP5430ES1_CM_L3INIT_USB_OTG_SS_CLKCTRL		0x4a0093f0
extern reg omap5430es1_cm_l3init_usb_otg_ss_clkctrl;
#define OMAP5430ES1_L3INIT_CM_CORE_MOD_REGCOUNT			15
extern reg *omap5430es1_l3init_cm_core_mod[OMAP5430ES1_L3INIT_CM_CORE_MOD_REGCOUNT + 1];

#define OMAP5430ES1_CM_WKUPAON_CLKSTCTRL			0x4ae07800
extern reg omap5430es1_cm_wkupaon_clkstctrl;
#define OMAP5430ES1_CM_WKUPAON_L4_WKUP_CLKCTRL			0x4ae07820
extern reg omap5430es1_cm_wkupaon_l4_wkup_clkctrl;
#define OMAP5430ES1_CM_WKUPAON_WD_TIMER2_CLKCTRL		0x4ae07830
extern reg omap5430es1_cm_wkupaon_wd_timer2_clkctrl;
#define OMAP5430ES1_CM_WKUPAON_GPIO1_CLKCTRL			0x4ae07838
extern reg omap5430es1_cm_wkupaon_gpio1_clkctrl;
#define OMAP5430ES1_CM_WKUPAON_TIMER1_CLKCTRL			0x4ae07840
extern reg omap5430es1_cm_wkupaon_timer1_clkctrl;
#define OMAP5430ES1_CM_WKUPAON_COUNTER_32K_CLKCTRL		0x4ae07850
extern reg omap5430es1_cm_wkupaon_counter_32k_clkctrl;
#define OMAP5430ES1_CM_WKUPAON_SAR_RAM_CLKCTRL			0x4ae07860
extern reg omap5430es1_cm_wkupaon_sar_ram_clkctrl;
#define OMAP5430ES1_CM_WKUPAON_KBD_CLKCTRL			0x4ae07878
extern reg omap5430es1_cm_wkupaon_kbd_clkctrl;
#define OMAP5430ES1_CM_WKUPAON_SCRM_CLKCTRL			0x4ae07890
extern reg omap5430es1_cm_wkupaon_scrm_clkctrl;
#define OMAP5430ES1_CM_WKUPAON_IO_SRCOMP_CLKCTRL		0x4ae07898
extern reg omap5430es1_cm_wkupaon_io_srcomp_clkctrl;
#define OMAP5430ES1_WKUPAON_CM_MOD_REGCOUNT			10
extern reg *omap5430es1_wkupaon_cm_mod[OMAP5430ES1_WKUPAON_CM_MOD_REGCOUNT + 1];

#define OMAP5430ES1_REVISION_CM_CORE_AON			0x4a004000
extern reg omap5430es1_revision_cm_core_aon;
#define OMAP5430ES1_CM_CM_CORE_AON_PROFILING_CLKCTRL		0x4a004040
extern reg omap5430es1_cm_cm_core_aon_profiling_clkctrl;
#define OMAP5430ES1_CM_CORE_AON_DEBUG_CFG			0x4a0040f0
extern reg omap5430es1_cm_core_aon_debug_cfg;
#define OMAP5430ES1_INTRCONN_SOCKET_CM_CORE_AON_MOD_REGCOUNT	3
extern reg *omap5430es1_intrconn_socket_cm_core_aon_mod[OMAP5430ES1_INTRCONN_SOCKET_CM_CORE_AON_MOD_REGCOUNT + 1];

#define OMAP5430ES1_CM_IVA_CLKSTCTRL				0x4a008f00
extern reg omap5430es1_cm_iva_clkstctrl;
#define OMAP5430ES1_CM_IVA_STATICDEP				0x4a008f04
extern reg omap5430es1_cm_iva_staticdep;
#define OMAP5430ES1_CM_IVA_DYNAMICDEP				0x4a008f08
extern reg omap5430es1_cm_iva_dynamicdep;
#define OMAP5430ES1_CM_IVA_IVA_CLKCTRL				0x4a008f20
extern reg omap5430es1_cm_iva_iva_clkctrl;
#define OMAP5430ES1_CM_IVA_SL2_CLKCTRL				0x4a008f28
extern reg omap5430es1_cm_iva_sl2_clkctrl;
#define OMAP5430ES1_IVA_CM_CORE_MOD_REGCOUNT			5
extern reg *omap5430es1_iva_cm_core_mod[OMAP5430ES1_IVA_CM_CORE_MOD_REGCOUNT + 1];

#define OMAP5430ES1_CM_COREAON_CLKSTCTRL			0x4a008600
extern reg omap5430es1_cm_coreaon_clkstctrl;
#define OMAP5430ES1_CM_COREAON_SMARTREFLEX_MPU_CLKCTRL		0x4a008628
extern reg omap5430es1_cm_coreaon_smartreflex_mpu_clkctrl;
#define OMAP5430ES1_CM_COREAON_SMARTREFLEX_MM_CLKCTRL		0x4a008630
extern reg omap5430es1_cm_coreaon_smartreflex_mm_clkctrl;
#define OMAP5430ES1_CM_COREAON_SMARTREFLEX_CORE_CLKCTRL		0x4a008638
extern reg omap5430es1_cm_coreaon_smartreflex_core_clkctrl;
#define OMAP5430ES1_CM_COREAON_USB_PHY_CORE_CLKCTRL		0x4a008640
extern reg omap5430es1_cm_coreaon_usb_phy_core_clkctrl;
#define OMAP5430ES1_CM_COREAON_BANDGAP_CLKCTRL			0x4a008648
extern reg omap5430es1_cm_coreaon_bandgap_clkctrl;
#define OMAP5430ES1_CM_COREAON_IO_SRCOMP_CLKCTRL		0x4a008650
extern reg omap5430es1_cm_coreaon_io_srcomp_clkctrl;
#define OMAP5430ES1_COREAON_CM_CORE_MOD_REGCOUNT		7
extern reg *omap5430es1_coreaon_cm_core_mod[OMAP5430ES1_COREAON_CM_CORE_MOD_REGCOUNT + 1];

#define OMAP5430ES1_CM_MPU_CLKSTCTRL				0x4a004300
extern reg omap5430es1_cm_mpu_clkstctrl;
#define OMAP5430ES1_CM_MPU_STATICDEP				0x4a004304
extern reg omap5430es1_cm_mpu_staticdep;
#define OMAP5430ES1_CM_MPU_DYNAMICDEP				0x4a004308
extern reg omap5430es1_cm_mpu_dynamicdep;
#define OMAP5430ES1_CM_MPU_MPU_CLKCTRL				0x4a004320
extern reg omap5430es1_cm_mpu_mpu_clkctrl;
#define OMAP5430ES1_MPU_CM_CORE_AON_MOD_REGCOUNT		4
extern reg *omap5430es1_mpu_cm_core_aon_mod[OMAP5430ES1_MPU_CM_CORE_AON_MOD_REGCOUNT + 1];

#define OMAP5430ES1_CM_CAM_CLKSTCTRL				0x4a009000
extern reg omap5430es1_cm_cam_clkstctrl;
#define OMAP5430ES1_CM_CAM_STATICDEP				0x4a009004
extern reg omap5430es1_cm_cam_staticdep;
#define OMAP5430ES1_CM_CAM_DYNAMICDEP				0x4a009008
extern reg omap5430es1_cm_cam_dynamicdep;
#define OMAP5430ES1_CM_CAM_ISS_CLKCTRL				0x4a009020
extern reg omap5430es1_cm_cam_iss_clkctrl;
#define OMAP5430ES1_CM_CAM_FDIF_CLKCTRL				0x4a009028
extern reg omap5430es1_cm_cam_fdif_clkctrl;
#define OMAP5430ES1_CM_CAM_CAL_CLKCTRL				0x4a009030
extern reg omap5430es1_cm_cam_cal_clkctrl;
#define OMAP5430ES1_CAM_CM_CORE_MOD_REGCOUNT			6
extern reg *omap5430es1_cam_cm_core_mod[OMAP5430ES1_CAM_CM_CORE_MOD_REGCOUNT + 1];

#define OMAP5430ES1_CM_DSP_CLKSTCTRL				0x4a004400
extern reg omap5430es1_cm_dsp_clkstctrl;
#define OMAP5430ES1_CM_DSP_STATICDEP				0x4a004404
extern reg omap5430es1_cm_dsp_staticdep;
#define OMAP5430ES1_CM_DSP_DYNAMICDEP				0x4a004408
extern reg omap5430es1_cm_dsp_dynamicdep;
#define OMAP5430ES1_CM_DSP_DSP_CLKCTRL				0x4a004420
extern reg omap5430es1_cm_dsp_dsp_clkctrl;
#define OMAP5430ES1_DSP_CM_CORE_AON_MOD_REGCOUNT		4
extern reg *omap5430es1_dsp_cm_core_aon_mod[OMAP5430ES1_DSP_CM_CORE_AON_MOD_REGCOUNT + 1];

typedef enum {
	CM54XX_DSS_CM_CORE,
	CM54XX_INSTR_CM_CORE,
	CM54XX_CORE_CM_CORE,
	CM54XX_CUSTEFUSE_CM_CORE,
	CM54XX_ABE_CM_CORE_AON,
	CM54XX_GPU_CM_CORE,
	CM54XX_EMU_CM,
	CM54XX_INTRCONN_SOCKET_CM_CORE,
	CM54XX_INSTR_CM_CORE_AON,
	CM54XX_CKGEN_CM_CORE_AON,
	CM54XX_CKGEN_CM_CORE,
	CM54XX_L4PER_CM_CORE,
	CM54XX_L3INIT_CM_CORE,
	CM54XX_WKUPAON_CM,
	CM54XX_INTRCONN_SOCKET_CM_CORE_AON,
	CM54XX_IVA_CM_CORE,
	CM54XX_COREAON_CM_CORE,
	CM54XX_MPU_CM_CORE_AON,
	CM54XX_CAM_CM_CORE,
	CM54XX_DSP_CM_CORE_AON,
	CM54XX_MODS_COUNT = 20
} cm54xx_mod_id;

extern reg **cm54xxes1_mods[CM54XX_MODS_COUNT + 1];

extern const char *cm54xx_mods_name[CM54XX_MODS_COUNT];

typedef enum {
	DPLL54XX_MPU,
	DPLL54XX_IVA,
	DPLL54XX_CORE,
	DPLL54XX_PER,
	DPLL54XX_ABE,
	DPLL54XX_USB,
	DPLL54XX_UNIPRO1,
	DPLL54XX_UNIPRO2,
	DPLL54XX_ID_MAX
} dpll54xx_id;


typedef enum {
	HSDIV54XX_H11,
	HSDIV54XX_H12,
	HSDIV54XX_H13,
	HSDIV54XX_H14,
	HSDIV54XX_H21,
	HSDIV54XX_H22,
	HSDIV54XX_H23,
	HSDIV54XX_H24,
	HSDIV54XX_ID_MAX
} hsdiv54xx_id;


extern const dpll_settings_regs dpll54xxes1_regs[DPLL54XX_ID_MAX];
extern const reg *dpll54xxes1_hsdiv_regs[DPLL54XX_ID_MAX][HSDIV54XX_ID_MAX];


#endif
