/*
 *
 * @Component			OMAPCONF
 * @Filename			ctrlmod_wkup54xx-defs.h
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


#ifndef __CTRLMOD_WKUP54XX_DEFS_H__
#define __CTRLMOD_WKUP54XX_DEFS_H__

#include <reg.h>
#include <stdio.h>

#define OMAP5430_CONTROL_WKUP_REVISION			0x4ae0c000
extern reg omap5430_control_wkup_revision;
#define OMAP5430_CONTROL_WKUP_HWINFO			0x4ae0c004
extern reg omap5430_control_wkup_hwinfo;
#define OMAP5430_CONTROL_WKUP_SYSCONFIG			0x4ae0c010
extern reg omap5430_control_wkup_sysconfig;
#define OMAP5430_CONTROL_WKUP_PROT_CTRL			0x4ae0c100
extern reg omap5430_control_wkup_prot_ctrl;
#define OMAP5430_CONTROL_WKUP_OCPREG_SPARE		0x4ae0c10c
extern reg omap5430_control_wkup_ocpreg_spare;
#define OMAP5430_CONTROL_PROT_EMIF1_SDRAM_CONFIG	0x4ae0c110
extern reg omap5430_control_prot_emif1_sdram_config;
#define OMAP5430_CONTROL_PROT_EMIF1_LPDDR2_NVM_CONFIG	0x4ae0c114
extern reg omap5430_control_prot_emif1_lpddr2_nvm_config;
#define OMAP5430_CONTROL_PROT_EMIF2_SDRAM_CONFIG	0x4ae0c118
extern reg omap5430_control_prot_emif2_sdram_config;
#define OMAP5430_CONTROL_PROT_EMIF2_LPDDR2_NVM_CONFIG2	0x4ae0c11c
extern reg omap5430_control_prot_emif2_lpddr2_nvm_config2;
#define OMAP5430_CONTROL_STD_FUSE_USB_CONF		0x4ae0c138
extern reg omap5430_control_std_fuse_usb_conf;
#define OMAP5430_CONTROL_STD_FUSE_CONF			0x4ae0c13c
extern reg omap5430_control_std_fuse_conf;
#define OMAP5430_CONTROL_DPLL_CLK_TRIMMING		0x4ae0c140
extern reg omap5430_control_dpll_clk_trimming;
#define OMAP5430_CONTROL_EMIF1_SDRAM_CONFIG_EXT		0x4ae0c144
extern reg omap5430_control_emif1_sdram_config_ext;
#define OMAP5430_CONTROL_EMIF2_SDRAM_CONFIG_EXT		0x4ae0c148
extern reg omap5430_control_emif2_sdram_config_ext;
#define OMAP5430_CONTROL_EMIF1_SDRAM_CONFIG_EXT_1	0x4ae0c14c
extern reg omap5430_control_emif1_sdram_config_ext_1;
#define OMAP5430_CONTROL_EMIF2_SDRAM_CONFIG_EXT_2	0x4ae0c150
extern reg omap5430_control_emif2_sdram_config_ext_2;
#define OMAP5430_CONTROL_WKUP_STD_FUSE_DIE_ID_0		0x4ae0c200
extern reg omap5430_control_wkup_std_fuse_die_id_0;
#define OMAP5430_CONTROL_WKUP_ID_CODE			0x4ae0c204
extern reg omap5430_control_wkup_id_code;
#define OMAP5430_CONTROL_WKUP_STD_FUSE_DIE_ID_1		0x4ae0c208
extern reg omap5430_control_wkup_std_fuse_die_id_1;
#define OMAP5430_CONTROL_WKUP_STD_FUSE_DIE_ID_2		0x4ae0c20c
extern reg omap5430_control_wkup_std_fuse_die_id_2;
#define OMAP5430_CONTROL_WKUP_STD_FUSE_DIE_ID_3		0x4ae0c210
extern reg omap5430_control_wkup_std_fuse_die_id_3;
#define OMAP5430_CONTROL_WKUP_STD_FUSE_PROD_ID_0	0x4ae0c214
extern reg omap5430_control_wkup_std_fuse_prod_id_0;
#define OMAP5430_CONTROL_WKUP_LDOVBB_MM_VOLTAGE_CTRL		0x4ae0c314
extern reg omap5430_control_wkup_ldovbb_mm_voltage_ctrl;
#define OMAP5430_CONTROL_WKUP_LDOVBB_MPU_VOLTAGE_CTRL		0x4ae0c318
extern reg omap5430_control_wkup_ldovbb_mpu_voltage_ctrl;
#define OMAP5430_CONTROL_WKUP_LDOSRAM_MM_VOLTAGE_CTRL		0x4ae0c31c
extern reg omap5430_control_wkup_ldosram_mm_voltage_ctrl;
#define OMAP5430_CONTROL_WKUP_LDOSRAM_MPU_VOLTAGE_CTRL		0x4ae0c324
extern reg omap5430_control_wkup_ldosram_mpu_voltage_ctrl;
#define OMAP5430_CONTROL_WKUP_LDOSRAM_CORE_VOLTAGE_CTRL		0x4ae0c328
extern reg omap5430_control_wkup_ldosram_core_voltage_ctrl;
#define OMAP5430_CONTROL_WKUP_LDOSRAM_MPU_LVT_VOLTAGE_CTRL	0x4ae0c338
extern reg omap5430_control_wkup_ldosram_mpu_lvt_voltage_ctrl;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_0	0x4ae0c460
extern reg omap5430_control_wkup_conf_debug_sel_tst_0;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_1	0x4ae0c464
extern reg omap5430_control_wkup_conf_debug_sel_tst_1;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_2	0x4ae0c468
extern reg omap5430_control_wkup_conf_debug_sel_tst_2;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_3	0x4ae0c46c
extern reg omap5430_control_wkup_conf_debug_sel_tst_3;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_4	0x4ae0c470
extern reg omap5430_control_wkup_conf_debug_sel_tst_4;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_5	0x4ae0c474
extern reg omap5430_control_wkup_conf_debug_sel_tst_5;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_6	0x4ae0c478
extern reg omap5430_control_wkup_conf_debug_sel_tst_6;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_7	0x4ae0c47c
extern reg omap5430_control_wkup_conf_debug_sel_tst_7;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_8	0x4ae0c480
extern reg omap5430_control_wkup_conf_debug_sel_tst_8;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_9	0x4ae0c484
extern reg omap5430_control_wkup_conf_debug_sel_tst_9;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_10	0x4ae0c488
extern reg omap5430_control_wkup_conf_debug_sel_tst_10;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_11	0x4ae0c48c
extern reg omap5430_control_wkup_conf_debug_sel_tst_11;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_12	0x4ae0c490
extern reg omap5430_control_wkup_conf_debug_sel_tst_12;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_13	0x4ae0c494
extern reg omap5430_control_wkup_conf_debug_sel_tst_13;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_14	0x4ae0c498
extern reg omap5430_control_wkup_conf_debug_sel_tst_14;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_15	0x4ae0c49c
extern reg omap5430_control_wkup_conf_debug_sel_tst_15;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_16	0x4ae0c4a0
extern reg omap5430_control_wkup_conf_debug_sel_tst_16;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_17	0x4ae0c4a4
extern reg omap5430_control_wkup_conf_debug_sel_tst_17;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_18	0x4ae0c4a8
extern reg omap5430_control_wkup_conf_debug_sel_tst_18;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_19	0x4ae0c4ac
extern reg omap5430_control_wkup_conf_debug_sel_tst_19;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_20	0x4ae0c4b0
extern reg omap5430_control_wkup_conf_debug_sel_tst_20;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_21	0x4ae0c4b4
extern reg omap5430_control_wkup_conf_debug_sel_tst_21;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_22	0x4ae0c4b8
extern reg omap5430_control_wkup_conf_debug_sel_tst_22;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_23	0x4ae0c4bc
extern reg omap5430_control_wkup_conf_debug_sel_tst_23;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_24	0x4ae0c4c0
extern reg omap5430_control_wkup_conf_debug_sel_tst_24;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_25	0x4ae0c4c4
extern reg omap5430_control_wkup_conf_debug_sel_tst_25;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_26	0x4ae0c4c8
extern reg omap5430_control_wkup_conf_debug_sel_tst_26;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_27	0x4ae0c4cc
extern reg omap5430_control_wkup_conf_debug_sel_tst_27;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_28	0x4ae0c4d0
extern reg omap5430_control_wkup_conf_debug_sel_tst_28;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_29	0x4ae0c4d4
extern reg omap5430_control_wkup_conf_debug_sel_tst_29;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_30	0x4ae0c4d8
extern reg omap5430_control_wkup_conf_debug_sel_tst_30;
#define OMAP5430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_31	0x4ae0c4dc
extern reg omap5430_control_wkup_conf_debug_sel_tst_31;
#define OMAP5430_CONTROL_WKUP_CONF_XBAR_SEL_0			0x4ae0c5dc
extern reg omap5430_control_wkup_conf_xbar_sel_0;
#define OMAP5430_CONTROL_WKUP_CONF_XBAR_SEL_4			0x4ae0c5e0
extern reg omap5430_control_wkup_conf_xbar_sel_4;
#define OMAP5430_CONTROL_WKUP_CONF_XBAR_SEL_8			0x4ae0c5e4
extern reg omap5430_control_wkup_conf_xbar_sel_8;
#define OMAP5430_CONTROL_WKUP_CONF_XBAR_SEL_12			0x4ae0c5e8
extern reg omap5430_control_wkup_conf_xbar_sel_12;
#define OMAP5430_CONTROL_WKUP_CONF_XBAR_SEL_16			0x4ae0c5ec
extern reg omap5430_control_wkup_conf_xbar_sel_16;
#define OMAP5430_CONTROL_WKUP_CONF_XBAR_SEL_20			0x4ae0c5f0
extern reg omap5430_control_wkup_conf_xbar_sel_20;
#define OMAP5430_CONTROL_WKUP_CONF_XBAR_SEL_24			0x4ae0c5f4
extern reg omap5430_control_wkup_conf_xbar_sel_24;
#define OMAP5430_CONTROL_WKUP_CONF_XBAR_SEL_28			0x4ae0c5f8
extern reg omap5430_control_wkup_conf_xbar_sel_28;
#define OMAP5430_CONTROL_WKUP_CONF_XBAR_BYPASS			0x4ae0c5fc
extern reg omap5430_control_wkup_conf_xbar_bypass;
#define OMAP5430ES1_CTRL_MODULE_WKUP_MOD_REGCOUNT		53
extern reg *omap5430es1_ctrl_module_wkup_mod[OMAP5430ES1_CTRL_MODULE_WKUP_MOD_REGCOUNT + 1];
#define OMAP5430_CTRL_MODULE_WKUP_MOD_REGCOUNT			68
extern reg *omap5430_ctrl_module_wkup_mod[OMAP5430_CTRL_MODULE_WKUP_MOD_REGCOUNT + 1];


#endif
