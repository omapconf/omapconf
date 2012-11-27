/*
 *
 * @Component			OMAPCONF
 * @Filename			ctrlmod_wkup54xx-defs.c
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


#include <ctrlmod_wkup54xx-defs.h>

reg omap5430_control_wkup_revision = {
	"CONTROL_WKUP_REVISION",
	OMAP5430_CONTROL_WKUP_REVISION,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_hwinfo = {
	"CONTROL_WKUP_HWINFO",
	OMAP5430_CONTROL_WKUP_HWINFO,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_sysconfig = {
	"CONTROL_WKUP_SYSCONFIG",
	OMAP5430_CONTROL_WKUP_SYSCONFIG,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_prot_ctrl = {
	"CONTROL_WKUP_PROT_CTRL",
	OMAP5430_CONTROL_WKUP_PROT_CTRL,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_ocpreg_spare = {
	"CONTROL_WKUP_OCPREG_SPARE",
	OMAP5430_CONTROL_WKUP_OCPREG_SPARE,
	0xDEADBEEF,
	0};

reg omap5430_control_prot_emif1_sdram_config = {
	"CONTROL_PROT_EMIF1_SDRAM_CONFIG",
	OMAP5430_CONTROL_PROT_EMIF1_SDRAM_CONFIG,
	0xDEADBEEF,
	0};

reg omap5430_control_prot_emif1_lpddr2_nvm_config = {
	"CONTROL_PROT_EMIF1_LPDDR2_NVM_CONFIG",
	OMAP5430_CONTROL_PROT_EMIF1_LPDDR2_NVM_CONFIG,
	0xDEADBEEF,
	0};

reg omap5430_control_prot_emif2_sdram_config = {
	"CONTROL_PROT_EMIF2_SDRAM_CONFIG",
	OMAP5430_CONTROL_PROT_EMIF2_SDRAM_CONFIG,
	0xDEADBEEF,
	0};

reg omap5430_control_prot_emif2_lpddr2_nvm_config2 = {
	"CONTROL_PROT_EMIF2_LPDDR2_NVM_CONFIG2",
	OMAP5430_CONTROL_PROT_EMIF2_LPDDR2_NVM_CONFIG2,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_usb_conf = {
	"CONTROL_STD_FUSE_USB_CONF",
	OMAP5430_CONTROL_STD_FUSE_USB_CONF,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_conf = {
	"CONTROL_STD_FUSE_CONF",
	OMAP5430_CONTROL_STD_FUSE_CONF,
	0xDEADBEEF,
	0};

reg omap5430_control_dpll_clk_trimming = {
	"CONTROL_DPLL_CLK_TRIMMING",
	OMAP5430_CONTROL_DPLL_CLK_TRIMMING,
	0xDEADBEEF,
	0};

reg omap5430_control_emif1_sdram_config_ext = {
	"CONTROL_EMIF1_SDRAM_CONFIG_EXT",
	OMAP5430_CONTROL_EMIF1_SDRAM_CONFIG_EXT,
	0xDEADBEEF,
	0};

reg omap5430_control_emif2_sdram_config_ext = {
	"CONTROL_EMIF2_SDRAM_CONFIG_EXT",
	OMAP5430_CONTROL_EMIF2_SDRAM_CONFIG_EXT,
	0xDEADBEEF,
	0};

reg omap5430_control_emif1_sdram_config_ext_1 = {
	"CONTROL_EMIF1_SDRAM_CONFIG_EXT_1",
	OMAP5430_CONTROL_EMIF1_SDRAM_CONFIG_EXT_1,
	0xDEADBEEF,
	0};

reg omap5430_control_emif2_sdram_config_ext_2 = {
	"CONTROL_EMIF2_SDRAM_CONFIG_EXT_2",
	OMAP5430_CONTROL_EMIF2_SDRAM_CONFIG_EXT_2,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_std_fuse_die_id_0 = {
	"CONTROL_WKUP_STD_FUSE_DIE_ID_0",
	OMAP5430_CONTROL_WKUP_STD_FUSE_DIE_ID_0,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_id_code = {
	"CONTROL_WKUP_ID_CODE",
	OMAP5430_CONTROL_WKUP_ID_CODE,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_std_fuse_die_id_1 = {
	"CONTROL_WKUP_STD_FUSE_DIE_ID_1",
	OMAP5430_CONTROL_WKUP_STD_FUSE_DIE_ID_1,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_std_fuse_die_id_2 = {
	"CONTROL_WKUP_STD_FUSE_DIE_ID_2",
	OMAP5430_CONTROL_WKUP_STD_FUSE_DIE_ID_2,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_std_fuse_die_id_3 = {
	"CONTROL_WKUP_STD_FUSE_DIE_ID_3",
	OMAP5430_CONTROL_WKUP_STD_FUSE_DIE_ID_3,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_std_fuse_prod_id_0 = {
	"CONTROL_WKUP_STD_FUSE_PROD_ID_0",
	OMAP5430_CONTROL_WKUP_STD_FUSE_PROD_ID_0,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_ldovbb_mm_voltage_ctrl = {
	"CONTROL_WKUP_LDOVBB_MM_VOLTAGE_CTRL",
	OMAP5430_CONTROL_WKUP_LDOVBB_MM_VOLTAGE_CTRL,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_ldovbb_mpu_voltage_ctrl = {
	"CONTROL_WKUP_LDOVBB_MPU_VOLTAGE_CTRL",
	OMAP5430_CONTROL_WKUP_LDOVBB_MPU_VOLTAGE_CTRL,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_ldosram_mm_voltage_ctrl = {
	"CONTROL_WKUP_LDOSRAM_MM_VOLTAGE_CTRL",
	OMAP5430_CONTROL_WKUP_LDOSRAM_MM_VOLTAGE_CTRL,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_ldosram_mpu_voltage_ctrl = {
	"CONTROL_WKUP_LDOSRAM_MPU_VOLTAGE_CTRL",
	OMAP5430_CONTROL_WKUP_LDOSRAM_MPU_VOLTAGE_CTRL,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_ldosram_core_voltage_ctrl = {
	"CONTROL_WKUP_LDOSRAM_CORE_VOLTAGE_CTRL",
	OMAP5430_CONTROL_WKUP_LDOSRAM_CORE_VOLTAGE_CTRL,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_ldosram_mpu_lvt_voltage_ctrl = {
	"CONTROL_WKUP_LDOSRAM_MPU_LVT_VOLTAGE_CTRL",
	OMAP5430_CONTROL_WKUP_LDOSRAM_MPU_LVT_VOLTAGE_CTRL,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_0 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_0",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_0,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_1 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_1",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_1,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_2 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_2",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_2,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_3 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_3",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_3,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_4 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_4",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_4,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_5 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_5",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_5,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_6 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_6",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_6,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_7 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_7",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_7,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_8 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_8",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_8,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_9 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_9",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_9,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_10 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_10",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_10,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_11 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_11",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_11,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_12 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_12",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_12,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_13 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_13",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_13,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_14 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_14",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_14,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_15 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_15",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_15,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_16 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_16",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_16,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_17 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_17",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_17,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_18 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_18",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_18,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_19 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_19",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_19,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_20 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_20",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_20,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_21 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_21",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_21,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_22 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_22",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_22,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_23 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_23",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_23,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_24 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_24",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_24,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_25 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_25",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_25,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_26 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_26",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_26,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_27 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_27",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_27,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_28 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_28",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_28,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_29 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_29",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_29,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_30 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_30",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_30,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_debug_sel_tst_31 = {
	"CONTROL_WKUP_CONF_DEBUG_SEL_TST_31",
	OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_31,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_xbar_sel_0 = {
	"CONTROL_WKUP_CONF_XBAR_SEL_0",
	OMAP5430_CONTROL_WKUP_CONF_XBAR_SEL_0,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_xbar_sel_4 = {
	"CONTROL_WKUP_CONF_XBAR_SEL_4",
	OMAP5430_CONTROL_WKUP_CONF_XBAR_SEL_4,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_xbar_sel_8 = {
	"CONTROL_WKUP_CONF_XBAR_SEL_8",
	OMAP5430_CONTROL_WKUP_CONF_XBAR_SEL_8,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_xbar_sel_12 = {
	"CONTROL_WKUP_CONF_XBAR_SEL_12",
	OMAP5430_CONTROL_WKUP_CONF_XBAR_SEL_12,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_xbar_sel_16 = {
	"CONTROL_WKUP_CONF_XBAR_SEL_16",
	OMAP5430_CONTROL_WKUP_CONF_XBAR_SEL_16,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_xbar_sel_20 = {
	"CONTROL_WKUP_CONF_XBAR_SEL_20",
	OMAP5430_CONTROL_WKUP_CONF_XBAR_SEL_20,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_xbar_sel_24 = {
	"CONTROL_WKUP_CONF_XBAR_SEL_24",
	OMAP5430_CONTROL_WKUP_CONF_XBAR_SEL_24,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_xbar_sel_28 = {
	"CONTROL_WKUP_CONF_XBAR_SEL_28",
	OMAP5430_CONTROL_WKUP_CONF_XBAR_SEL_28,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_conf_xbar_bypass = {
	"CONTROL_WKUP_CONF_XBAR_BYPASS",
	OMAP5430_CONTROL_WKUP_CONF_XBAR_BYPASS,
	0xDEADBEEF,
	0};

reg *omap5430es1_ctrl_module_wkup_mod[OMAP5430ES1_CTRL_MODULE_WKUP_MOD_REGCOUNT + 1] = {
	&omap5430_control_wkup_revision,
	&omap5430_control_wkup_hwinfo,
	&omap5430_control_wkup_sysconfig,
	&omap5430_control_wkup_ocpreg_spare,
	&omap5430_control_prot_emif1_sdram_config,
	&omap5430_control_prot_emif1_lpddr2_nvm_config,
	&omap5430_control_prot_emif2_sdram_config,
	&omap5430_control_prot_emif2_lpddr2_nvm_config2,
	&omap5430_control_std_fuse_usb_conf,
	&omap5430_control_std_fuse_conf,
	&omap5430_control_dpll_clk_trimming,
	&omap5430_control_emif1_sdram_config_ext,
	&omap5430_control_emif2_sdram_config_ext,
	&omap5430_control_emif1_sdram_config_ext_1,
	&omap5430_control_emif2_sdram_config_ext_2,
	&omap5430_control_wkup_std_fuse_die_id_0,
	&omap5430_control_wkup_id_code,
	&omap5430_control_wkup_std_fuse_die_id_1,
	&omap5430_control_wkup_std_fuse_die_id_2,
	&omap5430_control_wkup_std_fuse_die_id_3,
	&omap5430_control_wkup_std_fuse_prod_id_0,
	&omap5430_control_wkup_conf_debug_sel_tst_0,
	&omap5430_control_wkup_conf_debug_sel_tst_1,
	&omap5430_control_wkup_conf_debug_sel_tst_2,
	&omap5430_control_wkup_conf_debug_sel_tst_3,
	&omap5430_control_wkup_conf_debug_sel_tst_4,
	&omap5430_control_wkup_conf_debug_sel_tst_5,
	&omap5430_control_wkup_conf_debug_sel_tst_6,
	&omap5430_control_wkup_conf_debug_sel_tst_7,
	&omap5430_control_wkup_conf_debug_sel_tst_8,
	&omap5430_control_wkup_conf_debug_sel_tst_9,
	&omap5430_control_wkup_conf_debug_sel_tst_10,
	&omap5430_control_wkup_conf_debug_sel_tst_11,
	&omap5430_control_wkup_conf_debug_sel_tst_12,
	&omap5430_control_wkup_conf_debug_sel_tst_13,
	&omap5430_control_wkup_conf_debug_sel_tst_14,
	&omap5430_control_wkup_conf_debug_sel_tst_15,
	&omap5430_control_wkup_conf_debug_sel_tst_16,
	&omap5430_control_wkup_conf_debug_sel_tst_17,
	&omap5430_control_wkup_conf_debug_sel_tst_18,
	&omap5430_control_wkup_conf_debug_sel_tst_19,
	&omap5430_control_wkup_conf_debug_sel_tst_20,
	&omap5430_control_wkup_conf_debug_sel_tst_21,
	&omap5430_control_wkup_conf_debug_sel_tst_22,
	&omap5430_control_wkup_conf_debug_sel_tst_23,
	&omap5430_control_wkup_conf_debug_sel_tst_24,
	&omap5430_control_wkup_conf_debug_sel_tst_25,
	&omap5430_control_wkup_conf_debug_sel_tst_26,
	&omap5430_control_wkup_conf_debug_sel_tst_27,
	&omap5430_control_wkup_conf_debug_sel_tst_28,
	&omap5430_control_wkup_conf_debug_sel_tst_29,
	&omap5430_control_wkup_conf_debug_sel_tst_30,
	&omap5430_control_wkup_conf_debug_sel_tst_31,
	NULL};

reg *omap5430_ctrl_module_wkup_mod[OMAP5430_CTRL_MODULE_WKUP_MOD_REGCOUNT + 1] = {
	&omap5430_control_wkup_revision,
	&omap5430_control_wkup_hwinfo,
	&omap5430_control_wkup_sysconfig,
	&omap5430_control_wkup_prot_ctrl,
	&omap5430_control_wkup_ocpreg_spare,
	&omap5430_control_prot_emif1_sdram_config,
	&omap5430_control_prot_emif1_lpddr2_nvm_config,
	&omap5430_control_prot_emif2_sdram_config,
	&omap5430_control_prot_emif2_lpddr2_nvm_config2,
	&omap5430_control_std_fuse_usb_conf,
	&omap5430_control_std_fuse_conf,
	&omap5430_control_emif1_sdram_config_ext,
	&omap5430_control_emif2_sdram_config_ext,
	&omap5430_control_emif1_sdram_config_ext_1,
	&omap5430_control_emif2_sdram_config_ext_2,
	&omap5430_control_wkup_std_fuse_die_id_0,
	&omap5430_control_wkup_id_code,
	&omap5430_control_wkup_std_fuse_die_id_1,
	&omap5430_control_wkup_std_fuse_die_id_2,
	&omap5430_control_wkup_std_fuse_die_id_3,
	&omap5430_control_wkup_std_fuse_prod_id_0,
	&omap5430_control_wkup_ldovbb_mm_voltage_ctrl,
	&omap5430_control_wkup_ldovbb_mpu_voltage_ctrl,
	&omap5430_control_wkup_ldosram_mm_voltage_ctrl,
	&omap5430_control_wkup_ldosram_mpu_voltage_ctrl,
	&omap5430_control_wkup_ldosram_core_voltage_ctrl,
	&omap5430_control_wkup_ldosram_mpu_lvt_voltage_ctrl,
	&omap5430_control_wkup_conf_debug_sel_tst_0,
	&omap5430_control_wkup_conf_debug_sel_tst_1,
	&omap5430_control_wkup_conf_debug_sel_tst_2,
	&omap5430_control_wkup_conf_debug_sel_tst_3,
	&omap5430_control_wkup_conf_debug_sel_tst_4,
	&omap5430_control_wkup_conf_debug_sel_tst_5,
	&omap5430_control_wkup_conf_debug_sel_tst_6,
	&omap5430_control_wkup_conf_debug_sel_tst_7,
	&omap5430_control_wkup_conf_debug_sel_tst_8,
	&omap5430_control_wkup_conf_debug_sel_tst_9,
	&omap5430_control_wkup_conf_debug_sel_tst_10,
	&omap5430_control_wkup_conf_debug_sel_tst_11,
	&omap5430_control_wkup_conf_debug_sel_tst_12,
	&omap5430_control_wkup_conf_debug_sel_tst_13,
	&omap5430_control_wkup_conf_debug_sel_tst_14,
	&omap5430_control_wkup_conf_debug_sel_tst_15,
	&omap5430_control_wkup_conf_debug_sel_tst_16,
	&omap5430_control_wkup_conf_debug_sel_tst_17,
	&omap5430_control_wkup_conf_debug_sel_tst_18,
	&omap5430_control_wkup_conf_debug_sel_tst_19,
	&omap5430_control_wkup_conf_debug_sel_tst_20,
	&omap5430_control_wkup_conf_debug_sel_tst_21,
	&omap5430_control_wkup_conf_debug_sel_tst_22,
	&omap5430_control_wkup_conf_debug_sel_tst_23,
	&omap5430_control_wkup_conf_debug_sel_tst_24,
	&omap5430_control_wkup_conf_debug_sel_tst_25,
	&omap5430_control_wkup_conf_debug_sel_tst_26,
	&omap5430_control_wkup_conf_debug_sel_tst_27,
	&omap5430_control_wkup_conf_debug_sel_tst_28,
	&omap5430_control_wkup_conf_debug_sel_tst_29,
	&omap5430_control_wkup_conf_debug_sel_tst_30,
	&omap5430_control_wkup_conf_debug_sel_tst_31,
	&omap5430_control_wkup_conf_xbar_sel_0,
	&omap5430_control_wkup_conf_xbar_sel_4,
	&omap5430_control_wkup_conf_xbar_sel_8,
	&omap5430_control_wkup_conf_xbar_sel_12,
	&omap5430_control_wkup_conf_xbar_sel_16,
	&omap5430_control_wkup_conf_xbar_sel_20,
	&omap5430_control_wkup_conf_xbar_sel_24,
	&omap5430_control_wkup_conf_xbar_sel_28,
	&omap5430_control_wkup_conf_xbar_bypass,
	NULL};
