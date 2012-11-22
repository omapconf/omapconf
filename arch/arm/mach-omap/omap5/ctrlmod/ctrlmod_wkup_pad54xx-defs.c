/*
 *
 * @Component			OMAPCONF
 * @Filename			ctrlmod_wkup_pad54xx-defs.c
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


#include <ctrlmod_wkup_pad54xx-defs.h>

reg omap5430_control_wkup_pad_revision = {
	"CONTROL_WKUP_PAD_REVISION",
	OMAP5430_CONTROL_WKUP_PAD_REVISION,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_pad_hwinfo = {
	"CONTROL_WKUP_PAD_HWINFO",
	OMAP5430_CONTROL_WKUP_PAD_HWINFO,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_pad_sysconfig = {
	"CONTROL_WKUP_PAD_SYSCONFIG",
	OMAP5430_CONTROL_WKUP_PAD_SYSCONFIG,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_pad0_llia_wakereqin_pad1_llib_wakereqin = {
	"CONTROL_WKUP_PAD0_LLIA_WAKEREQIN_PAD1_LLIB_WAKEREQIN",
	OMAP5430_CONTROL_WKUP_PAD0_LLIA_WAKEREQIN_PAD1_LLIB_WAKEREQIN,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_pad0_drm_emu0_pad1_drm_emu1 = {
	"CONTROL_WKUP_PAD0_DRM_EMU0_PAD1_DRM_EMU1",
	OMAP5430_CONTROL_WKUP_PAD0_DRM_EMU0_PAD1_DRM_EMU1,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_pad0_jtag_ntrst_pad1_jtag_tck = {
	"CONTROL_WKUP_PAD0_JTAG_NTRST_PAD1_JTAG_TCK",
	OMAP5430_CONTROL_WKUP_PAD0_JTAG_NTRST_PAD1_JTAG_TCK,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_pad0_jtag_rtck_pad1_jtag_tmsc = {
	"CONTROL_WKUP_PAD0_JTAG_RTCK_PAD1_JTAG_TMSC",
	OMAP5430_CONTROL_WKUP_PAD0_JTAG_RTCK_PAD1_JTAG_TMSC,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_pad0_jtag_tdi_pad1_jtag_tdo = {
	"CONTROL_WKUP_PAD0_JTAG_TDI_PAD1_JTAG_TDO",
	OMAP5430_CONTROL_WKUP_PAD0_JTAG_TDI_PAD1_JTAG_TDO,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_pad0_sys_32k_pad1_fref_clk_ioreq = {
	"CONTROL_WKUP_PAD0_SYS_32K_PAD1_FREF_CLK_IOREQ",
	OMAP5430_CONTROL_WKUP_PAD0_SYS_32K_PAD1_FREF_CLK_IOREQ,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_pad0_fref_clk0_out_pad1_fref_clk1_out = {
	"CONTROL_WKUP_PAD0_FREF_CLK0_OUT_PAD1_FREF_CLK1_OUT",
	OMAP5430_CONTROL_WKUP_PAD0_FREF_CLK0_OUT_PAD1_FREF_CLK1_OUT,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_pad0_fref_clk2_out_pad1_fref_clk2_req = {
	"CONTROL_WKUP_PAD0_FREF_CLK2_OUT_PAD1_FREF_CLK2_REQ",
	OMAP5430_CONTROL_WKUP_PAD0_FREF_CLK2_OUT_PAD1_FREF_CLK2_REQ,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_pad0_fref_clk1_req_pad1_sys_nrespwron = {
	"CONTROL_WKUP_PAD0_FREF_CLK1_REQ_PAD1_SYS_NRESPWRON",
	OMAP5430_CONTROL_WKUP_PAD0_FREF_CLK1_REQ_PAD1_SYS_NRESPWRON,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_pad0_sys_nreswarm_pad1_sys_pwr_req = {
	"CONTROL_WKUP_PAD0_SYS_NRESWARM_PAD1_SYS_PWR_REQ",
	OMAP5430_CONTROL_WKUP_PAD0_SYS_NRESWARM_PAD1_SYS_PWR_REQ,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_pad0_sys_nirq1_pad1_sys_nirq2 = {
	"CONTROL_WKUP_PAD0_SYS_NIRQ1_PAD1_SYS_NIRQ2",
	OMAP5430_CONTROL_WKUP_PAD0_SYS_NIRQ1_PAD1_SYS_NIRQ2,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_pad0_sr_pmic_scl_pad1_sr_pmic_sda = {
	"CONTROL_WKUP_PAD0_SR_PMIC_SCL_PAD1_SR_PMIC_SDA",
	OMAP5430_CONTROL_WKUP_PAD0_SR_PMIC_SCL_PAD1_SR_PMIC_SDA,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_pad0_sys_boot0_pad1_sys_boot1 = {
	"CONTROL_WKUP_PAD0_SYS_BOOT0_PAD1_SYS_BOOT1",
	OMAP5430_CONTROL_WKUP_PAD0_SYS_BOOT0_PAD1_SYS_BOOT1,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_pad0_sys_boot2_pad1_sys_boot3 = {
	"CONTROL_WKUP_PAD0_SYS_BOOT2_PAD1_SYS_BOOT3",
	OMAP5430_CONTROL_WKUP_PAD0_SYS_BOOT2_PAD1_SYS_BOOT3,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_pad0_sys_boot4_pad1_sys_boot5 = {
	"CONTROL_WKUP_PAD0_SYS_BOOT4_PAD1_SYS_BOOT5",
	OMAP5430_CONTROL_WKUP_PAD0_SYS_BOOT4_PAD1_SYS_BOOT5,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_padconf_wakeupevent_0 = {
	"CONTROL_WKUP_PADCONF_WAKEUPEVENT_0",
	OMAP5430_CONTROL_WKUP_PADCONF_WAKEUPEVENT_0,
	0xDEADBEEF,
	0};

reg omap5430_control_smart1nopmio_padconf_0 = {
	"CONTROL_SMART1NOPMIO_PADCONF_0",
	OMAP5430_CONTROL_SMART1NOPMIO_PADCONF_0,
	0xDEADBEEF,
	0};

reg omap5430_control_smart1nopmio_padconf_1 = {
	"CONTROL_SMART1NOPMIO_PADCONF_1",
	OMAP5430_CONTROL_SMART1NOPMIO_PADCONF_1,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_padconf_mode = {
	"CONTROL_WKUP_PADCONF_MODE",
	OMAP5430_CONTROL_WKUP_PADCONF_MODE,
	0xDEADBEEF,
	0};

reg omap5430_control_xtal_oscillator = {
	"CONTROL_XTAL_OSCILLATOR",
	OMAP5430_CONTROL_XTAL_OSCILLATOR,
	0xDEADBEEF,
	0};

reg omap5430_control_i2c_2 = {
	"CONTROL_I2C_2",
	OMAP5430_CONTROL_I2C_2,
	0xDEADBEEF,
	0};

reg omap5430_control_ckobuffer = {
	"CONTROL_CKOBUFFER",
	OMAP5430_CONTROL_CKOBUFFER,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_control_spare_rw = {
	"CONTROL_WKUP_CONTROL_SPARE_RW",
	OMAP5430_CONTROL_WKUP_CONTROL_SPARE_RW,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_control_spare_r = {
	"CONTROL_WKUP_CONTROL_SPARE_R",
	OMAP5430_CONTROL_WKUP_CONTROL_SPARE_R,
	0xDEADBEEF,
	0};

reg omap5430_control_wkup_control_spare_r_c0 = {
	"CONTROL_WKUP_CONTROL_SPARE_R_C0",
	OMAP5430_CONTROL_WKUP_CONTROL_SPARE_R_C0,
	0xDEADBEEF,
	0};

reg omap5430_control_srcomp_east_side_wkup = {
	"CONTROL_SRCOMP_EAST_SIDE_WKUP",
	OMAP5430_CONTROL_SRCOMP_EAST_SIDE_WKUP,
	0xDEADBEEF,
	0};

reg omap5430_control_efuse_2 = {
	"CONTROL_EFUSE_2",
	OMAP5430_CONTROL_EFUSE_2,
	0xDEADBEEF,
	0};

reg omap5430_control_efuse_3 = {
	"CONTROL_EFUSE_3",
	OMAP5430_CONTROL_EFUSE_3,
	0xDEADBEEF,
	0};

reg omap5430_control_efuse_4 = {
	"CONTROL_EFUSE_4",
	OMAP5430_CONTROL_EFUSE_4,
	0xDEADBEEF,
	0};

reg omap5430_control_efuse_5 = {
	"CONTROL_EFUSE_5",
	OMAP5430_CONTROL_EFUSE_5,
	0xDEADBEEF,
	0};

reg omap5430_control_efuse_6 = {
	"CONTROL_EFUSE_6",
	OMAP5430_CONTROL_EFUSE_6,
	0xDEADBEEF,
	0};

reg omap5430_control_efuse_7 = {
	"CONTROL_EFUSE_7",
	OMAP5430_CONTROL_EFUSE_7,
	0xDEADBEEF,
	0};

reg omap5430_control_efuse_8 = {
	"CONTROL_EFUSE_8",
	OMAP5430_CONTROL_EFUSE_8,
	0xDEADBEEF,
	0};

reg omap5430_control_efuse_9 = {
	"CONTROL_EFUSE_9",
	OMAP5430_CONTROL_EFUSE_9,
	0xDEADBEEF,
	0};

reg omap5430_control_efuse_10 = {
	"CONTROL_EFUSE_10",
	OMAP5430_CONTROL_EFUSE_10,
	0xDEADBEEF,
	0};

reg omap5430_control_efuse_1 = {
	"CONTROL_EFUSE_1",
	OMAP5430_CONTROL_EFUSE_1,
	0xDEADBEEF,
	0};

reg omap5430_control_efuse_12 = {
	"CONTROL_EFUSE_12",
	OMAP5430_CONTROL_EFUSE_12,
	0xDEADBEEF,
	0};

reg omap5430_control_efuse_13 = {
	"CONTROL_EFUSE_13",
	OMAP5430_CONTROL_EFUSE_13,
	0xDEADBEEF,
	0};

reg *omap5430_ctrl_module_wkup_pad_mod[OMAP5430_CTRL_MODULE_WKUP_PAD_MOD_REGCOUNT + 1] = {
	&omap5430_control_wkup_pad_revision,
	&omap5430_control_wkup_pad_hwinfo,
	&omap5430_control_wkup_pad_sysconfig,
	&omap5430_control_wkup_pad0_llia_wakereqin_pad1_llib_wakereqin,
	&omap5430_control_wkup_pad0_drm_emu0_pad1_drm_emu1,
	&omap5430_control_wkup_pad0_jtag_ntrst_pad1_jtag_tck,
	&omap5430_control_wkup_pad0_jtag_rtck_pad1_jtag_tmsc,
	&omap5430_control_wkup_pad0_jtag_tdi_pad1_jtag_tdo,
	&omap5430_control_wkup_pad0_sys_32k_pad1_fref_clk_ioreq,
	&omap5430_control_wkup_pad0_fref_clk0_out_pad1_fref_clk1_out,
	&omap5430_control_wkup_pad0_fref_clk2_out_pad1_fref_clk2_req,
	&omap5430_control_wkup_pad0_fref_clk1_req_pad1_sys_nrespwron,
	&omap5430_control_wkup_pad0_sys_nreswarm_pad1_sys_pwr_req,
	&omap5430_control_wkup_pad0_sys_nirq1_pad1_sys_nirq2,
	&omap5430_control_wkup_pad0_sr_pmic_scl_pad1_sr_pmic_sda,
	&omap5430_control_wkup_pad0_sys_boot0_pad1_sys_boot1,
	&omap5430_control_wkup_pad0_sys_boot2_pad1_sys_boot3,
	&omap5430_control_wkup_pad0_sys_boot4_pad1_sys_boot5,
	&omap5430_control_wkup_padconf_wakeupevent_0,
	&omap5430_control_smart1nopmio_padconf_0,
	&omap5430_control_smart1nopmio_padconf_1,
	&omap5430_control_wkup_padconf_mode,
	&omap5430_control_xtal_oscillator,
	&omap5430_control_i2c_2,
	&omap5430_control_ckobuffer,
	&omap5430_control_wkup_control_spare_rw,
	&omap5430_control_wkup_control_spare_r,
	&omap5430_control_wkup_control_spare_r_c0,
	&omap5430_control_srcomp_east_side_wkup,
	&omap5430_control_efuse_2,
	&omap5430_control_efuse_3,
	&omap5430_control_efuse_4,
	&omap5430_control_efuse_5,
	&omap5430_control_efuse_6,
	&omap5430_control_efuse_7,
	&omap5430_control_efuse_8,
	&omap5430_control_efuse_9,
	&omap5430_control_efuse_10,
	&omap5430_control_efuse_1,
	&omap5430_control_efuse_12,
	&omap5430_control_efuse_13,
	NULL};

