/*
 *
 * @Component			OMAPCONF
 * @Filename			ctrlmod_wkup_pad54xx-defs.h
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


#ifndef __CTRLMOD_WKUP_PAD54XX_DEFS_H__
#define __CTRLMOD_WKUP_PAD54XX_DEFS_H__

#include <reg.h>
#include <stdio.h>

#define OMAP5430_CONTROL_WKUP_PAD_REVISION				0x4ae0c800
extern reg omap5430_control_wkup_pad_revision;
#define OMAP5430_CONTROL_WKUP_PAD_HWINFO				0x4ae0c804
extern reg omap5430_control_wkup_pad_hwinfo;
#define OMAP5430_CONTROL_WKUP_PAD_SYSCONFIG				0x4ae0c810
extern reg omap5430_control_wkup_pad_sysconfig;
#define OMAP5430_CONTROL_WKUP_PAD0_LLIA_WAKEREQIN_PAD1_LLIB_WAKEREQIN	0x4ae0c840
extern reg omap5430_control_wkup_pad0_llia_wakereqin_pad1_llib_wakereqin;
#define OMAP5430_CONTROL_WKUP_PAD0_DRM_EMU0_PAD1_DRM_EMU1		0x4ae0c844
extern reg omap5430_control_wkup_pad0_drm_emu0_pad1_drm_emu1;
#define OMAP5430_CONTROL_WKUP_PAD0_JTAG_NTRST_PAD1_JTAG_TCK		0x4ae0c848
extern reg omap5430_control_wkup_pad0_jtag_ntrst_pad1_jtag_tck;
#define OMAP5430_CONTROL_WKUP_PAD0_JTAG_RTCK_PAD1_JTAG_TMSC		0x4ae0c84c
extern reg omap5430_control_wkup_pad0_jtag_rtck_pad1_jtag_tmsc;
#define OMAP5430_CONTROL_WKUP_PAD0_JTAG_TDI_PAD1_JTAG_TDO		0x4ae0c850
extern reg omap5430_control_wkup_pad0_jtag_tdi_pad1_jtag_tdo;
#define OMAP5430_CONTROL_WKUP_PAD0_SYS_32K_PAD1_FREF_CLK_IOREQ		0x4ae0c854
extern reg omap5430_control_wkup_pad0_sys_32k_pad1_fref_clk_ioreq;
#define OMAP5430_CONTROL_WKUP_PAD0_FREF_CLK0_OUT_PAD1_FREF_CLK1_OUT	0x4ae0c858
extern reg omap5430_control_wkup_pad0_fref_clk0_out_pad1_fref_clk1_out;
#define OMAP5430_CONTROL_WKUP_PAD0_FREF_CLK2_OUT_PAD1_FREF_CLK2_REQ	0x4ae0c85c
extern reg omap5430_control_wkup_pad0_fref_clk2_out_pad1_fref_clk2_req;
#define OMAP5430_CONTROL_WKUP_PAD0_FREF_CLK1_REQ_PAD1_SYS_NRESPWRON	0x4ae0c860
extern reg omap5430_control_wkup_pad0_fref_clk1_req_pad1_sys_nrespwron;
#define OMAP5430_CONTROL_WKUP_PAD0_SYS_NRESWARM_PAD1_SYS_PWR_REQ	0x4ae0c864
extern reg omap5430_control_wkup_pad0_sys_nreswarm_pad1_sys_pwr_req;
#define OMAP5430_CONTROL_WKUP_PAD0_SYS_NIRQ1_PAD1_SYS_NIRQ2		0x4ae0c868
extern reg omap5430_control_wkup_pad0_sys_nirq1_pad1_sys_nirq2;
#define OMAP5430_CONTROL_WKUP_PAD0_SR_PMIC_SCL_PAD1_SR_PMIC_SDA		0x4ae0c86c
extern reg omap5430_control_wkup_pad0_sr_pmic_scl_pad1_sr_pmic_sda;
#define OMAP5430_CONTROL_WKUP_PAD0_SYS_BOOT0_PAD1_SYS_BOOT1		0x4ae0c870
extern reg omap5430_control_wkup_pad0_sys_boot0_pad1_sys_boot1;
#define OMAP5430_CONTROL_WKUP_PAD0_SYS_BOOT2_PAD1_SYS_BOOT3		0x4ae0c874
extern reg omap5430_control_wkup_pad0_sys_boot2_pad1_sys_boot3;
#define OMAP5430_CONTROL_WKUP_PAD0_SYS_BOOT4_PAD1_SYS_BOOT5		0x4ae0c878
extern reg omap5430_control_wkup_pad0_sys_boot4_pad1_sys_boot5;
#define OMAP5430_CONTROL_WKUP_PADCONF_WAKEUPEVENT_0			0x4ae0c880
extern reg omap5430_control_wkup_padconf_wakeupevent_0;
#define OMAP5430_CONTROL_SMART1NOPMIO_PADCONF_0				0x4ae0cda0
extern reg omap5430_control_smart1nopmio_padconf_0;
#define OMAP5430_CONTROL_SMART1NOPMIO_PADCONF_1				0x4ae0cda4
extern reg omap5430_control_smart1nopmio_padconf_1;
#define OMAP5430_CONTROL_WKUP_PADCONF_MODE				0x4ae0cda8
extern reg omap5430_control_wkup_padconf_mode;
#define OMAP5430_CONTROL_XTAL_OSCILLATOR				0x4ae0cdac
extern reg omap5430_control_xtal_oscillator;
#define OMAP5430_CONTROL_I2C_2						0x4ae0cdb0
extern reg omap5430_control_i2c_2;
#define OMAP5430_CONTROL_CKOBUFFER					0x4ae0cdb4
extern reg omap5430_control_ckobuffer;
#define OMAP5430_CONTROL_WKUP_CONTROL_SPARE_RW				0x4ae0cdb8
extern reg omap5430_control_wkup_control_spare_rw;
#define OMAP5430_CONTROL_WKUP_CONTROL_SPARE_R				0x4ae0cdbc
extern reg omap5430_control_wkup_control_spare_r;
#define OMAP5430_CONTROL_WKUP_CONTROL_SPARE_R_C0			0x4ae0cdc0
extern reg omap5430_control_wkup_control_spare_r_c0;
#define OMAP5430_CONTROL_SRCOMP_EAST_SIDE_WKUP				0x4ae0cdc4
extern reg omap5430_control_srcomp_east_side_wkup;
#define OMAP5430_CONTROL_EFUSE_2					0x4ae0cdcc
extern reg omap5430_control_efuse_2;
#define OMAP5430_CONTROL_EFUSE_3					0x4ae0cdd0
extern reg omap5430_control_efuse_3;
#define OMAP5430_CONTROL_EFUSE_4					0x4ae0cdd4
extern reg omap5430_control_efuse_4;
#define OMAP5430_CONTROL_EFUSE_5					0x4ae0cdd8
extern reg omap5430_control_efuse_5;
#define OMAP5430_CONTROL_EFUSE_6					0x4ae0cddc
extern reg omap5430_control_efuse_6;
#define OMAP5430_CONTROL_EFUSE_7					0x4ae0cde0
extern reg omap5430_control_efuse_7;
#define OMAP5430_CONTROL_EFUSE_8					0x4ae0cde4
extern reg omap5430_control_efuse_8;
#define OMAP5430_CONTROL_EFUSE_9					0x4ae0cde8
extern reg omap5430_control_efuse_9;
#define OMAP5430_CONTROL_EFUSE_10					0x4ae0cdec
extern reg omap5430_control_efuse_10;
#define OMAP5430_CONTROL_EFUSE_1					0x4ae0cdf0
extern reg omap5430_control_efuse_1;
#define OMAP5430_CONTROL_EFUSE_12					0x4ae0cdf4
extern reg omap5430_control_efuse_12;
#define OMAP5430_CONTROL_EFUSE_13					0x4ae0cdf8
extern reg omap5430_control_efuse_13;
#define OMAP5430_CTRL_MODULE_WKUP_PAD_MOD_REGCOUNT			41
extern reg *omap5430_ctrl_module_wkup_pad_mod[OMAP5430_CTRL_MODULE_WKUP_PAD_MOD_REGCOUNT + 1];


#endif
