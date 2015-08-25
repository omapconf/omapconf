/*
 *
 * @Component			OMAPCONF
 * @Filename			hwobs54xx.c
 * @Description			OMAP5 PRM Registers Functions
 * @Author			Cedric Vamour (c-vamour@ti.com)s
 * @Date			2012
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
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


#include <hwobs54xx.h>
#include <hwobs44xx.h>
#include <lib.h>
#include <mem.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <help.h>
#include <cpuinfo.h>
#include <ctype.h>
#include <autoadjust_table.h>

#include <prm54xx-defs.h>
#include <cm54xx-defs.h>
#include <ctrlmod_core_pad54xx-defs.h>
#include <ctrlmod_core54xx-defs.h>
#include <ctrlmod_wkup_pad54xx-defs.h>
#include <ctrlmod_wkup54xx-defs.h>


/* #define HWOBS54XX_DEBUG */
#ifdef HWOBS44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


pad_cell hwobs54xx_wkup_sys_pad_reg_table[HWOBS54XX_PAD_MAX_NBR+1];
pad_cell hwobs54xx_core_c2c_pad_reg_table[HWOBS54XX_PAD_MAX_NBR+1];
pad_cell hwobs54xx_core_per_pad_reg_table[HWOBS54XX_PAD_MAX_NBR+1];

reg *hwobs54xx_core_debug_mux_table[HWOBS54XX_SIG_MAX_NBR+1] = {
	&omap5430_control_core_conf_debug_sel_tst_0,
	&omap5430_control_core_conf_debug_sel_tst_1,
	&omap5430_control_core_conf_debug_sel_tst_2,
	&omap5430_control_core_conf_debug_sel_tst_3,
	&omap5430_control_core_conf_debug_sel_tst_4,
	&omap5430_control_core_conf_debug_sel_tst_5,
	&omap5430_control_core_conf_debug_sel_tst_6,
	&omap5430_control_core_conf_debug_sel_tst_7,
	&omap5430_control_core_conf_debug_sel_tst_8,
	&omap5430_control_core_conf_debug_sel_tst_9,
	&omap5430_control_core_conf_debug_sel_tst_10,
	&omap5430_control_core_conf_debug_sel_tst_11,
	&omap5430_control_core_conf_debug_sel_tst_12,
	&omap5430_control_core_conf_debug_sel_tst_13,
	&omap5430_control_core_conf_debug_sel_tst_14,
	&omap5430_control_core_conf_debug_sel_tst_15,
	&omap5430_control_core_conf_debug_sel_tst_16,
	&omap5430_control_core_conf_debug_sel_tst_17,
	&omap5430_control_core_conf_debug_sel_tst_18,
	&omap5430_control_core_conf_debug_sel_tst_19,
	&omap5430_control_core_conf_debug_sel_tst_20,
	&omap5430_control_core_conf_debug_sel_tst_21,
	&omap5430_control_core_conf_debug_sel_tst_22,
	&omap5430_control_core_conf_debug_sel_tst_23,
	&omap5430_control_core_conf_debug_sel_tst_24,
	&omap5430_control_core_conf_debug_sel_tst_25,
	&omap5430_control_core_conf_debug_sel_tst_26,
	&omap5430_control_core_conf_debug_sel_tst_27,
	&omap5430_control_core_conf_debug_sel_tst_28,
	&omap5430_control_core_conf_debug_sel_tst_29,
	&omap5430_control_core_conf_debug_sel_tst_30,
	&omap5430_control_core_conf_debug_sel_tst_31};

reg *hwobs54xx_wkup_debug_mux_table[HWOBS54XX_SIG_MAX_NBR] = {
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
	&omap5430_control_wkup_conf_debug_sel_tst_31};


static int hwobs54xx_init_regtable(void);


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs54xx_wkup_sys_pad_table_init
 * @BRIEF		initialize regtable for wkup domain sysboot, fref, drm,
 *			llib, llia and sys_pwr_req pad registers
 * @RETURNS		0
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		initialize regtable for wkup domain sysboot, fref, drm,
 *			llib, llia and sys_pwr_req pad registers
 *//*------------------------------------------------------------------------ */
int hwobs54xx_wkup_sys_pad_table_init(void)
{
	int i = 0;

#if 0
	unsigned short reg_pad_val;
#endif

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	/* Init PADCONF registers table */
	strcpy(hwobs54xx_wkup_sys_pad_reg_table[i].name, "PAD0_SYS_BOOT0");
	hwobs54xx_wkup_sys_pad_reg_table[i++].addr =
		omap5430_control_wkup_pad0_sys_boot0_pad1_sys_boot1.addr;

	strcpy(hwobs54xx_wkup_sys_pad_reg_table[i].name, "PAD1_SYS_BOOT1");
	hwobs54xx_wkup_sys_pad_reg_table[i++].addr =
		omap5430_control_wkup_pad0_sys_boot0_pad1_sys_boot1.addr + 2;

	strcpy(hwobs54xx_wkup_sys_pad_reg_table[i].name, "PAD0_SYS_BOOT2");
	hwobs54xx_wkup_sys_pad_reg_table[i++].addr =
		omap5430_control_wkup_pad0_sys_boot2_pad1_sys_boot3.addr;

	strcpy(hwobs54xx_wkup_sys_pad_reg_table[i].name, "PAD1_SYS_BOOT3");
	hwobs54xx_wkup_sys_pad_reg_table[i++].addr =
		omap5430_control_wkup_pad0_sys_boot2_pad1_sys_boot3.addr + 2;

	strcpy(hwobs54xx_wkup_sys_pad_reg_table[i].name, "PAD0_SYS_BOOT4");
	hwobs54xx_wkup_sys_pad_reg_table[i++].addr =
		omap5430_control_wkup_pad0_sys_boot4_pad1_sys_boot5.addr;

	strcpy(hwobs54xx_wkup_sys_pad_reg_table[i].name, "PAD1_FREF_CLK1_OUT");
	hwobs54xx_wkup_sys_pad_reg_table[i++].addr =
		omap5430_control_wkup_pad0_fref_clk0_out_pad1_fref_clk1_out.addr + 2;

	strcpy(hwobs54xx_wkup_sys_pad_reg_table[i].name, "PAD0_DRM_EMU0");
	hwobs54xx_wkup_sys_pad_reg_table[i++].addr =
		omap5430_control_wkup_pad0_drm_emu0_pad1_drm_emu1.addr;

	strcpy(hwobs54xx_wkup_sys_pad_reg_table[i].name, "PAD1_DRM_EMU1");
	hwobs54xx_wkup_sys_pad_reg_table[i++].addr =
		omap5430_control_wkup_pad0_drm_emu0_pad1_drm_emu1.addr + 2;

	strcpy(hwobs54xx_wkup_sys_pad_reg_table[i].name, "PAD0_SYS_BOOT5");
	hwobs54xx_wkup_sys_pad_reg_table[i++].addr =
		omap5430_control_wkup_pad0_sys_boot4_pad1_sys_boot5.addr + 2;

	strcpy(hwobs54xx_wkup_sys_pad_reg_table[i].name, "PAD0_FREF_CLK0_OUT");
	hwobs54xx_wkup_sys_pad_reg_table[i++].addr =
		omap5430_control_wkup_pad0_fref_clk0_out_pad1_fref_clk1_out.addr;

	strcpy(hwobs54xx_wkup_sys_pad_reg_table[i].name, "PAD0_FREF_CLK2_OUT");
	hwobs54xx_wkup_sys_pad_reg_table[i++].addr =
		omap5430_control_wkup_pad0_fref_clk2_out_pad1_fref_clk2_req.addr;

	strcpy(hwobs54xx_wkup_sys_pad_reg_table[i].name, "PAD1_FREF_CLK2_REQ");
	hwobs54xx_wkup_sys_pad_reg_table[i++].addr =
		omap5430_control_wkup_pad0_fref_clk2_out_pad1_fref_clk2_req.addr + 2;

	strcpy(hwobs54xx_wkup_sys_pad_reg_table[i].name, "PAD0_FREF_CLK1_REQ");
	hwobs54xx_wkup_sys_pad_reg_table[i++].addr =
		omap5430_control_wkup_pad0_fref_clk1_req_pad1_sys_nrespwron.addr;

	strcpy(hwobs54xx_wkup_sys_pad_reg_table[i].name, "PAD1_LLIB_WAKEREQIN");
	hwobs54xx_wkup_sys_pad_reg_table[i++].addr =
		omap5430_control_wkup_pad0_llia_wakereqin_pad1_llib_wakereqin.addr + 2;

	strcpy(hwobs54xx_wkup_sys_pad_reg_table[i].name, "PAD0_LLIA_WAKEREQIN");
	hwobs54xx_wkup_sys_pad_reg_table[i++].addr =
		omap5430_control_wkup_pad0_llia_wakereqin_pad1_llib_wakereqin.addr;

	strcpy(hwobs54xx_wkup_sys_pad_reg_table[i].name, "PAD1_SYS_PWR_REQ");
	hwobs54xx_wkup_sys_pad_reg_table[i++].addr =
		omap5430_control_wkup_pad0_sys_nreswarm_pad1_sys_pwr_req.addr + 2;

	strcpy(hwobs54xx_wkup_sys_pad_reg_table[i].name, "END");
	hwobs54xx_wkup_sys_pad_reg_table[i].addr = 0;

#if 0
	/* TODO: Save original Pad registers settings into a file */
	/* in case intrusive changes needs to be restored */
	while (hwobs54xx_wkup_sys_pad_reg_table[i].name != NULL) {
		hwobs44xx_padreg_read(hwobs54xx_wkup_sys_pad_reg_table[i].addr, &reg_pad_val);
		hwobs54xx_wkup_sys_pad_reg_table[i++].data = reg_pad_val;
	}
#endif

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs54xx_core_c2c_pad_table_init
 * @BRIEF		initialize regtable for core domain c2c pad registers
 * @RETURNS		0
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		initialize regtable for core domain c2c pad registers
 *//*------------------------------------------------------------------------ */
int hwobs54xx_core_c2c_pad_table_init(void)
{
	int i = 0;

#if 0
	unsigned short reg_pad_val;
#endif

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	/* Init PADCONF registers table */
	strcpy(hwobs54xx_core_c2c_pad_reg_table[i].name, "PAD0_C2C_DATAOUT0");
	hwobs54xx_core_c2c_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_c2c_dataout0_pad1_c2c_dataout1.addr;

	strcpy(hwobs54xx_core_c2c_pad_reg_table[i].name, "PAD1_C2C_DATAOUT1");
	hwobs54xx_core_c2c_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_c2c_dataout0_pad1_c2c_dataout1.addr + 2;

	strcpy(hwobs54xx_core_c2c_pad_reg_table[i].name, "PAD0_C2C_DATAOUT2");
	hwobs54xx_core_c2c_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_c2c_dataout2_pad1_c2c_dataout3.addr;

	strcpy(hwobs54xx_core_c2c_pad_reg_table[i].name, "PAD1_C2C_DATAOUT3");
	hwobs54xx_core_c2c_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_c2c_dataout2_pad1_c2c_dataout3.addr + 2;

	strcpy(hwobs54xx_core_c2c_pad_reg_table[i].name, "PAD0_C2C_DATAOUT4");
	hwobs54xx_core_c2c_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_c2c_dataout4_pad1_c2c_dataout5.addr;

	strcpy(hwobs54xx_core_c2c_pad_reg_table[i].name, "PAD1_C2C_DATAOUT5");
	hwobs54xx_core_c2c_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_c2c_dataout4_pad1_c2c_dataout5.addr + 2;

	strcpy(hwobs54xx_core_c2c_pad_reg_table[i].name, "PAD0_C2C_DATAOUT6");
	hwobs54xx_core_c2c_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_c2c_dataout6_pad1_c2c_dataout7.addr;

	strcpy(hwobs54xx_core_c2c_pad_reg_table[i].name, "PAD1_C2C_DATAOUT7");
	hwobs54xx_core_c2c_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_c2c_dataout6_pad1_c2c_dataout7.addr + 2;

	strcpy(hwobs54xx_core_c2c_pad_reg_table[i].name, "PAD0_C2C_DATA8");
	hwobs54xx_core_c2c_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_c2c_data8_pad1_c2c_data9.addr;

	strcpy(hwobs54xx_core_c2c_pad_reg_table[i].name, "PAD1_C2C_DATA9");
	hwobs54xx_core_c2c_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_c2c_data8_pad1_c2c_data9.addr + 2;

	strcpy(hwobs54xx_core_c2c_pad_reg_table[i].name, "PAD0_C2C_DATA10");
	hwobs54xx_core_c2c_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_c2c_data10_pad1_c2c_data11.addr;

	strcpy(hwobs54xx_core_c2c_pad_reg_table[i].name, "PAD1_C2C_DATA11");
	hwobs54xx_core_c2c_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_c2c_data10_pad1_c2c_data11.addr + 2;

	strcpy(hwobs54xx_core_c2c_pad_reg_table[i].name, "PAD0_C2C_DATA12");
	hwobs54xx_core_c2c_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_c2c_data12_pad1_c2c_data13.addr;

	strcpy(hwobs54xx_core_c2c_pad_reg_table[i].name, "PAD1_C2C_DATA13");
	hwobs54xx_core_c2c_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_c2c_data12_pad1_c2c_data13.addr + 2;

	strcpy(hwobs54xx_core_c2c_pad_reg_table[i].name, "PAD0_C2C_DATA14");
	hwobs54xx_core_c2c_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_c2c_data14_pad1_c2c_data15.addr;

	strcpy(hwobs54xx_core_c2c_pad_reg_table[i].name, "PAD1_C2C_DATA15");
	hwobs54xx_core_c2c_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_c2c_data14_pad1_c2c_data15.addr+ 2;

	strcpy(hwobs54xx_core_c2c_pad_reg_table[i].name, "END");
	hwobs54xx_core_c2c_pad_reg_table[i].addr = 0;

#if 0
	/* TODO: Save original Pad registers settings into a file */
	/* in case intrusive changes needs to be restored */
	while (hwobs54xx_core_c2c_pad_reg_table[i].name != NULL) {
		hwobs44xx_padreg_read(hwobs54xx_core_c2c_pad_reg_table[i].addr, &reg_pad_val);
		hwobs54xx_core_c2c_pad_reg_table[i++].val = reg_pad_val;
	}
#endif

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs54xx_core_per_pad_table_init
 * @BRIEF		initialize regtable for core domain uart2, uart5,
 *			mcspi2, timer8, timer11 and gpio6 pad registers
 * @RETURNS		0
 *			OMAPCONF_ERR_CPU
 * @param[in]		none
 * @DESCRIPTION		initialize regtable for core domain uart2, uart5,
 *			mcspi2, timer8, timer11 and gpio6 pad registers
 *//*------------------------------------------------------------------------ */
int hwobs54xx_core_per_pad_table_init(void)
{
	int i = 0;

#if 0
	unsigned short reg_pad_val;
#endif

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	/* Init PADCONF registers table */
	strcpy(hwobs54xx_core_per_pad_reg_table[i].name, "PAD0_UART2_RTS");
	hwobs54xx_core_per_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_uart2_rts_pad1_uart2_cts.addr;

	strcpy(hwobs54xx_core_per_pad_reg_table[i].name, "PAD1_UART2_CTS");
	hwobs54xx_core_per_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_uart2_rts_pad1_uart2_cts.addr + 2;

	strcpy(hwobs54xx_core_per_pad_reg_table[i].name, "PAD0_UART2_RX");
	hwobs54xx_core_per_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_uart2_rx_pad1_uart2_tx.addr;

	strcpy(hwobs54xx_core_per_pad_reg_table[i].name, "PAD1_UART2_TX");
	hwobs54xx_core_per_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_uart2_rx_pad1_uart2_tx.addr + 2;

	strcpy(hwobs54xx_core_per_pad_reg_table[i].name, "PAD1_MCSPI2_SIMO");
	hwobs54xx_core_per_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_mcspi2_clk_pad1_mcspi2_simo.addr + 2;

	strcpy(hwobs54xx_core_per_pad_reg_table[i].name, "PAD0_MCSPI2_SOMI");
	hwobs54xx_core_per_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_mcspi2_somi_pad1_mcspi2_cs0.addr;

	strcpy(hwobs54xx_core_per_pad_reg_table[i].name, "PAD0_GPIO6_184");
	hwobs54xx_core_per_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_gpio6_184_pad1_gpio6_185.addr;

	strcpy(hwobs54xx_core_per_pad_reg_table[i].name, "PAD1_GPIO6_185");
	hwobs54xx_core_per_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_gpio6_184_pad1_gpio6_185.addr + 2;

	strcpy(hwobs54xx_core_per_pad_reg_table[i].name, "PAD0_GPIO6_186");
	hwobs54xx_core_per_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_gpio6_186_pad1_gpio6_187.addr;

	strcpy(hwobs54xx_core_per_pad_reg_table[i].name, "PAD1_GPIO6_187");
	hwobs54xx_core_per_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_gpio6_186_pad1_gpio6_187.addr + 2;

	strcpy(hwobs54xx_core_per_pad_reg_table[i].name, "PAD1_TIMER11_PWM_EVT");
	hwobs54xx_core_per_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_cam_globalreset_pad1_timer11_pwm_evt.addr + 2;

	strcpy(hwobs54xx_core_per_pad_reg_table[i].name, "PAD0_TIMER8_PWM_EVT");
	hwobs54xx_core_per_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_timer8_pwm_evt_pad1_i2c3_scl.addr;

	strcpy(hwobs54xx_core_per_pad_reg_table[i].name, "PAD0_UART5_RX");
	hwobs54xx_core_per_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_uart5_rx_pad1_uart5_tx.addr;

	strcpy(hwobs54xx_core_per_pad_reg_table[i].name, "PAD1_UART5_TX");
	hwobs54xx_core_per_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_uart5_rx_pad1_uart5_tx.addr + 2;

	strcpy(hwobs54xx_core_per_pad_reg_table[i].name, "PAD0_UART5_CTS");
	hwobs54xx_core_per_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_uart5_cts_pad1_uart5_rts.addr;

	strcpy(hwobs54xx_core_per_pad_reg_table[i].name, "PAD1_UART5_RTS");
	hwobs54xx_core_per_pad_reg_table[i++].addr =
		omap5430_control_core_pad0_uart5_cts_pad1_uart5_rts.addr;

	strcpy(hwobs54xx_core_per_pad_reg_table[i].name, "END");
	hwobs54xx_core_per_pad_reg_table[i].addr = 0;

#if 0
	/* TODO: Save original Pad registers settings into a file */
	/* in case intrusive changes needs to be restored */
	while (hwobs54xx_core_per_pad_reg_table[i].name != NULL) {
		hwobs44xx_padreg_read(hwobs54xx_core_per_pad_reg_table[i].addr, &reg_pad_val);
		hwobs54xx_core_per_pad_reg_table[i++].val = reg_pad_val;
	}
#endif

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs54xx_check_pinmux
 * @BRIEF		check hwobs pinmux is properly configured.
 * @RETURNS		0 in case of success
 *			number of non-configured pins otherwise
 *			OMAPCONF_ERR_CPU
 * @param[in]		check_field: the field to check
 * @DESCRIPTION		check hwobs pinmux is properly configured.
 *//*------------------------------------------------------------------------ */
int hwobs54xx_check_pinmux(unsigned int check_field)
{
	int err = 0;
#if 1
	unsigned int i = 0;
	unsigned short reg_pad_val1, reg_pad_val2;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	hwobs54xx_init_regtable();

	if (check_field == HWOBS54XX_PAD_FULL_CHECK) {
		for (i = 0; i < HWOBS54XX_SIG_MAX_NBR; i++) {
			if (i < 16) {
				hwobs44xx_padreg_read(hwobs54xx_wkup_sys_pad_reg_table[i].addr,
					&reg_pad_val1);
				if (((reg_pad_val1) & 0x0005) != 0x0005)
					err++;
			} else {
				hwobs44xx_padreg_read(hwobs54xx_core_c2c_pad_reg_table[i - 16].addr,
					&reg_pad_val1);
				hwobs44xx_padreg_read(hwobs54xx_core_per_pad_reg_table[i - 16].addr,
					&reg_pad_val2);
				if ((((reg_pad_val1) & 0x0005) != 0x0005) &&
					(((reg_pad_val2) & 0x0005) != 0x0005))
					err++;
			}
		}

		if (err == HWOBS54XX_SIG_MAX_NBR) {
			printf("Note: Pinmux are not configured to drive HWOBS signals on external pads\n");
			printf("\n");
			printf("Use following command: ./omapconf setup hwobs pinmux\n");
			printf("\n");
		} else if (err != 0) {
			printf("Warning: NOT all Pinmux are configured to drive HWOBS signals on external pads:\n");
			printf("         > Number of non-configured Pinmux: %d\n", err);
			printf("\n");
			printf("Use following command: ./omapconf setup hwobs pinmux\n");
			printf("\n");
		}
	} else if (check_field < 16) {
		hwobs44xx_padreg_read(hwobs54xx_wkup_sys_pad_reg_table[check_field].addr,
			&reg_pad_val1);
		if (((reg_pad_val1) & 0x0005) != 0x0005)
			err++;
	} else if (check_field < HWOBS54XX_SIG_MAX_NBR) {
		hwobs44xx_padreg_read(hwobs54xx_core_c2c_pad_reg_table[check_field - 16].addr,
			&reg_pad_val1);
		hwobs44xx_padreg_read(hwobs54xx_core_per_pad_reg_table[check_field - 16].addr,
			&reg_pad_val2);
		if ((((reg_pad_val1) & 0x0005) != 0x0005) &&
			(((reg_pad_val2) & 0x0005) != 0x0005))
			err++;
	}
#endif
	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs54xx_check_gating
 * @BRIEF		check hwobs signals are not gated or tied low/high.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_INTERNAL
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		check hwobs signals are not gated or tied low/high.
 *//*------------------------------------------------------------------------ */
int hwobs54xx_check_gating()
{
	unsigned short reg_val;
	int err = 0;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	hwobs54xx_init_regtable();

	hwobs44xx_padreg_read(omap5430_control_hwobs_control.addr, &reg_val);

#ifdef HWOBS54XX_DEBUG
	reg_val = 0x7FEF9;
#endif

	if (((reg_val) & OMAP5430_HWOBS_MACRO_ENABLE_MASK) == 0x0) {
		printf("Warning: All HWOBS signals outputs are gated at hwobs ctrl mux level\n");
		err = OMAPCONF_ERR_INTERNAL;
	}

	if (((reg_val) & OMAP5430_HWOBS_ALL_ONE_MODE_MASK) ==
		OMAP5430_HWOBS_ALL_ONE_MODE_MASK) {
		printf("Warning: All HWOBS signals outputs are tied to '1' at hwobs ctrl mux level\n");
		err = OMAPCONF_ERR_INTERNAL;
	}

	if (((reg_val) & OMAP5430_HWOBS_ALL_ZERO_MODE_MASK) ==
		OMAP5430_HWOBS_ALL_ZERO_MODE_MASK) {
		printf("Warning: All HWOBS signals outputs are tied to '0' at hwobs ctrl mux level\n");
		err = OMAPCONF_ERR_INTERNAL;
	}

	if (((reg_val) & OMAP5430_HWOBS_CLKOBS_GATE_ENABLE_MASK) ==
		OMAP5430_HWOBS_CLKOBS_GATE_ENABLE_MASK) {
		printf("Warning: All HWOBS signals output at the DPLL are gated\n");
		err = OMAPCONF_ERR_INTERNAL;
	}

	if (((reg_val) & OMAP5430_HWOBS_CLKDIV_SEL_MASK) == 0x0) {
		printf("Warning: CONTROL_CORE_HWOBS_CONTROL <HWOBS_CLKDIV_SEL> must be configured\n");
		err = OMAPCONF_ERR_INTERNAL;
	}

	if (err == OMAPCONF_ERR_INTERNAL) {
		printf("\n");
		printf("Use following command: ./omapconf enable hwobs\n");
		printf("\n");
	}

	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs54xx_enable
 * @BRIEF		Enable HWOBS signals at hwobs ctrl mux level
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		Enable HWOBS signals at hwobs ctrl mux level
 *//*------------------------------------------------------------------------ */
int hwobs54xx_enable(void)
{
	unsigned int ret;
	int err = 0;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	hwobs54xx_init_regtable();

	/* write register mux enable value */
	ret = mem_write(omap5430_control_hwobs_control.addr, 0x9);
	if (ret != 0) {
		fprintf(stderr,
			"omapconf: write error! (addr=0x%08X, err=%d)\n",
			omap5430_control_hwobs_control.addr, ret);
		err = OMAPCONF_ERR_REG_ACCESS;
	} else {
		printf("OK: hwobs ctrl mux is now configured to output debug "
			"signals (not tied low/high, not gated)\n\n");
		err = 0;
	}

	hwobs54xx_display_hwobs_ctrl_cfg();
	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs54xx_test_menu
 * @BRIEF		Test OMAP5430 HWOBS Mux Configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		Test OMAP5430 HWOBS Mux Configuration:
 *			modify hwobs main mux for test purpose.
 *			Check observability setup from external pads to probes.
 *//*------------------------------------------------------------------------ */
int hwobs54xx_test(char *level)
{
	unsigned int ret = 0, val;
	static const char tie_s[2][5] = {"low", "high"};
	char *s;
	char c;

	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	if (level == NULL) {
		fprintf(stderr, "Missing argument!\n\n");
		goto hwobs54xx_test_err_arg;
	}

	CHECK_NULL_ARG(level, OMAPCONF_ERR_ARG);

	hwobs54xx_init_regtable();

	if (hwobs54xx_check_pinmux(HWOBS54XX_PAD_FULL_CHECK) != 0) {
		goto hwobs54xx_test_nrdy;
	}

	if (strcmp(level, "zero") == 0) {
		val = 0xD;
		c = '0';
		s = (char *) tie_s[0];
	} else if (strcmp(level, "one") == 0) {
		val = 0xB;
		c = '1';
		s = (char *) tie_s[1];
	} else {
		printf("omapconf: non supported argument: (%s)\n\n", level);
		goto hwobs54xx_test_err_arg;
	}

	/* write register mux tied low value */
	ret = mem_write(omap5430_control_hwobs_control.addr, val);
	if (ret != 0) {
		fprintf(stderr,
			"omapconf: write error! (addr=0x%08X, err=%d)\n",
			omap5430_control_hwobs_control.addr, ret);
		return OMAPCONF_ERR_REG_ACCESS;
	} else {
		printf("OK: All HWOBS signals should now be tied %s "
			"(forced to '%c')\n", s, c);
		printf("Note: If observations are NOT aligned, then there is "
			"probably an issue with observability HW (device, "
			"connector): modify your HW setup.\n\n");
	}

	goto hwobs54xx_test_end;

hwobs54xx_test_err_arg:
	autoadjust_table_init(table);

	row = 0;
	autoadjust_table_strncpy(table, row, 0, "Category");
	autoadjust_table_strncpy(table, row, 1, "Command (## OMAP5-ONLY ##)");
	autoadjust_table_strncpy(table, row, 2, "Description & Options");
	row++;
	autoadjust_table_strncpy(table, row, 0,	"Arguments for HWOBS test:");
	row++;

	autoadjust_table_strncpy(table, row, 1, "omapconf test hwobs zero");
	autoadjust_table_strncpy(table, row, 2,
		"hw observability ports are all tied low '0'.");
	row++;
	autoadjust_table_strncpy(table, row, 1,	"omapconf test hwobs one");
	autoadjust_table_strncpy(table, row, 2,
		"hw observability ports are all tied high '1'.");
	row++;

	autoadjust_table_print(table, row, 3);
	return OMAPCONF_ERR_ARG;

hwobs54xx_test_nrdy:
	ret = hwobs54xx_display_pads(hwobs54xx_wkup_sys_pad_reg_table);
	ret = hwobs54xx_display_pads(hwobs54xx_core_c2c_pad_reg_table);
	ret = hwobs54xx_display_pads(hwobs54xx_core_per_pad_reg_table);

	printf("Test FAIL: All pinmux should be configured before doing this "
		"test\n\n");
	return 0;

hwobs54xx_test_end:
	hwobs54xx_display_hwobs_ctrl_cfg();
	return ret;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs54xx_write_pads
 * @BRIEF		Write OMAP54XX pads pinmux to drive HWOBS signals.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 * @param[in,out]	pad_reg_table: table of pad registers
 * @DESCRIPTION		Write OMAP54XX pads pinmux to drive HWOBS signals.
 *//*------------------------------------------------------------------------ */
int hwobs54xx_write_pads(pad_cell pad_reg_table[HWOBS54XX_PAD_MAX_NBR+1])
{
	unsigned int ret, i = 0;
	int err = 0;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	hwobs54xx_init_regtable();

	while (strcmp(pad_reg_table[i].name, "END") != 0) {

		/* write register pad value */
		ret = hwobs44xx_padreg_write(pad_reg_table[i].addr, 0x0005);

		if (ret != 0) {
			fprintf(stderr, "omapconf: write error! (addr=0x%08X, err=%d)\n",
				(unsigned int)(pad_reg_table[i].addr), ret);
			err = OMAPCONF_ERR_REG_ACCESS;
		}
		i++;
	}

	if (err == OMAPCONF_ERR_REG_ACCESS) {
		printf("Error: Pinmux configuration failed!\n");
		printf("\n");
	} else if (pad_reg_table == hwobs54xx_wkup_sys_pad_reg_table) {
		printf("OK: WKUP CTRL Pinmux are now configured to drive HWOBS[00:15] signals on (SYS) external pads\n");
	} else if (pad_reg_table == hwobs54xx_core_c2c_pad_reg_table) {
		printf("OK: CORE CTRL Pinmux are now configured to drive HWOBS[16:31] signals on (C2C) external pads\n");
	} else if (pad_reg_table == hwobs54xx_core_per_pad_reg_table) {
		printf("OK: CORE CTRL Pinmux are now configured to drive HWOBS[16:31] signals on (PER) external pads\n");
	} else {
#ifdef HWOBS54XX_DEBUG
		printf("%s(): invalid array pointer passed as argument\n", __func__);
#endif
	}

	printf("\n");
	err = hwobs54xx_display_pads(pad_reg_table);

	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs54xx_pinmux_setup
 * @BRIEF		Setup OMAP54XX pinmux to drive HWOBS signals on external pads.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		Setup OMAP54XX pinmux to drive HWOBS signals on external pads.
 *//*------------------------------------------------------------------------ */
int hwobs54xx_pinmux_setup(char *padset)
{
	unsigned int ret;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	if (padset == NULL) {
		fprintf(stderr, "Missing argument!\n\n");
		goto hwobs54xx_setup_pinmux_err_arg;
	}
	padset = uppercase(padset);

	hwobs54xx_init_regtable();

	if (strcmp(padset, hwobs54xx_padset_names[HWOBS54XX_WKUP_CTRL_SYS_PADS]) == 0) {
		ret = hwobs54xx_write_pads(hwobs54xx_wkup_sys_pad_reg_table);
	} else if (strcmp(padset, hwobs54xx_padset_names[HWOBS54XX_CORE_CTRL_C2C_PADS]) == 0) {
		ret = hwobs54xx_write_pads(hwobs54xx_core_c2c_pad_reg_table);
	} else if (strcmp(padset, hwobs54xx_padset_names[HWOBS54XX_CORE_CTRL_PER_PADS]) == 0) {
		ret = hwobs54xx_write_pads(hwobs54xx_core_per_pad_reg_table);
	} else if (strcmp(padset, hwobs54xx_padset_names[HWOBS54XX_PADSET_SELECT_MAX_ID]) == 0) {
		ret = hwobs54xx_write_pads(hwobs54xx_wkup_sys_pad_reg_table);
		ret |= hwobs54xx_write_pads(hwobs54xx_core_c2c_pad_reg_table);
		ret |= hwobs54xx_write_pads(hwobs54xx_core_per_pad_reg_table);
	} else {
		ret = OMAPCONF_ERR_ARG;
		printf("Invalid pinmux padset configuration! (%s)\n\n", padset);
		goto hwobs54xx_setup_pinmux_err_arg;
	}

	ret = hwobs54xx_enable();

	goto hwobs54xx_pinmux_end;

hwobs54xx_setup_pinmux_err_arg:
	printf("SYNOPSIS:\n");
	printf("\n");
	printf("  omapconf setup hwobs pinmux [padset_cfg]\n");
	printf("\n");
	printf("DESCRIPTION:\n");
	printf("\n");
	printf("  This hwobs setup command allows to change pinmuxing on selected PADS to drive HWOBS debug signals.\n");
	printf("  Since observability signals are muxed with other functionalities, this menu allows to change PAD sets\n");
	printf("  of interest in order to avoid disabling needed functionalities\n");
	printf("\n");
	printf("PARAMETERS:\n");
	printf("\n");
	printf(" [padset_cfg] select pinmux padset configuration: WKUP, CORE_C2C, CORE_PER or ALL\n");
	printf("\n");
	printf("  ALL      -> change pinmux for all PADS [00:31] allowing to drive HWOBS while disabling other functions\n");
	printf("\n");
	printf("  WKUP     -> change pinmux for WKUP PADS [00:15] allowing to drive HWOBS while disabling default functions from below PADS:\n");
	printf("\n");

	ret = hwobs54xx_display_pads(hwobs54xx_wkup_sys_pad_reg_table);

	printf("\n");
	printf("  CORE_C2C -> change pinmux for CORE_C2C PADS [16:31] allowing to drive HWOBS while disabling default functions from below PADS:\n");
	printf("\n");

	ret = hwobs54xx_display_pads(hwobs54xx_core_c2c_pad_reg_table);

	printf("\n");
	printf("  CORE_PER -> change pinmux for CORE_PER PADS [16:31] allowing to drive HWOBS while disabling default functions from below PADS:\n");
	printf("\n");

	ret = hwobs54xx_display_pads(hwobs54xx_core_per_pad_reg_table);

	printf("\n");
	printf("EXAMPLE:\n");
	printf("\n");
	printf("- drive observability on hw_dbg[00:15] bits\n");
	printf("	omapconf setup hwobs pinmux WKUP\n");
	printf("\n");
	printf("- drive observability on hw_dbg[16:31] bits (in place of C2C)\n");
	printf("	omapconf setup hwobs pinmux CORE_C2C\n");
	printf("\n");
	printf("- drive observability on hw_dbg[00:31] bits\n");
	printf("	omapconf setup hwobs pinmux ALL\n");
	printf("\n");
	return ret;

hwobs54xx_pinmux_end:
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs54xx_prcm_setup
 * @BRIEF		Setup OMAP54XX HWOBS Mux Configuration:
 *			allow selection of desired PRCM debug signals.
 *			Implicitly configure HWOBS muxes.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 * @param[in]		pos_s: block (8 bits) positon whithin 32 bits of
 *			observability
 * @param[in]		cat_s: PRCM signals debug mux category
 * @param[in]		num_s: block number whithin selected signals category
 * @DESCRIPTION		Setup OMAP54XX HWOBS Mux Configuration:
 *			allow selection of desired PRCM debug signals.
 *			Implicitly configure HWOBS muxes.
 *//*------------------------------------------------------------------------ */
int hwobs54xx_prcm_setup(char *pos_s, char *cat_s, char *num_s)
{
	unsigned int ret, i = 0;
	unsigned int debug_mux, final_mux;
	unsigned int pos, num;


	#ifdef HWOBS54XX_DEBUG
	unsigned int reg_val;
	#endif

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	if ((pos_s == NULL) || (cat_s == NULL) || (num_s == NULL)) {
		fprintf(stderr, "Missing argument!\n\n");
		goto hwobs54xx_setup_prcm_err_arg;
	}

	hwobs54xx_init_regtable();

	dprintf("%s(): pos_s=%s\n", __func__, pos_s);
	dprintf("%s(): cat_s=%s\n", __func__, cat_s);
	dprintf("%s(): num_s=%s\n", __func__, num_s);

	/* Retrieve and check block position */
	ret = sscanf(pos_s, "%u", &pos);
	if (ret != 1) {
		dprintf("%s(): could not retrieve block position\n", __func__);
		goto hwobs54xx_setup_prcm_err_arg;
	}
	if (pos > 3) {
		printf("Invalid block position! (%s)\n\n", pos_s);
		goto hwobs54xx_setup_prcm_err_arg;
	}

	/* Retrieve and check signals block category */
	cat_s = uppercase(cat_s);
	if ((strcmp(cat_s, hwobs54xx_ctrl_wkup_conf_debug_sel_tst_names[0]) != 0) &&
		(strcmp(cat_s, hwobs54xx_ctrl_wkup_conf_debug_sel_tst_names[1]) != 0) &&
		(strcmp(cat_s, hwobs54xx_ctrl_core_conf_debug_sel_tst_names[5]) != 0) &&
		(strcmp(cat_s, "CM_AON") != 0) && (strcmp(cat_s, "CM_CORE") != 0)) {
		printf("Invalid PRCM signals category! (%s)\n\n", cat_s);
		goto hwobs54xx_setup_prcm_err_arg;
	}

	/* Retrieve and check block number (hex) */
	/* Hexdecimal value must start with "0x" */
	ret = sscanf(uppercase(num_s), "0X%x", &num);
	if (ret != 1) {
		printf("Invalid block number! (%s)\n\n", num_s);
		goto hwobs54xx_setup_prcm_err_arg;
	}

	dprintf("%s(): pos=%d\n", __func__, pos);
	dprintf("%s(): cat_s=%s\n", __func__, cat_s);
	dprintf("%s(): num=0x%x\n", __func__, num);

	if ((strcmp(cat_s, hwobs54xx_ctrl_core_conf_debug_sel_tst_names[5]) == 0)
		|| (strcmp(cat_s, "CM_CORE") == 0)) {
		/* CORE - CM2 (CM_CORE) */
		final_mux = 0xFF;
		debug_mux = 0x5;
		if (cpu_revision_get() == REV_ES1_0)
			ret = hwobs44xx_blkmuxreg_modify(
				omap5430es1_cm_core_debug_cfg.addr, pos, num);
		else
				ret = hwobs44xx_blkmuxreg_modify(
				omap5430_cm_core_debug_cfg.addr, pos, num);
		for (i = (pos * 8); i <= (pos * 8) + 7; i++) {
			ret = mem_write(hwobs54xx_core_debug_mux_table[i]->addr,
				debug_mux);
			#ifdef HWOBS54XX_DEBUG
			mem_read(hwobs54xx_core_debug_mux_table[i]->addr,
				&reg_val);
			printf("%s(): core_conf_debug_mux_id%d addr: 0x%08x val: 0x%08x\n",
				__func__, i,
				hwobs54xx_core_debug_mux_table[i]->addr,
				reg_val);
			#endif
		}
	} else {
		final_mux = 0x00;

		/* WKUP - PRM */
		if (strcmp(cat_s,
			hwobs54xx_ctrl_wkup_conf_debug_sel_tst_names[0]) == 0) {
			debug_mux = 0x0;
			if (cpu_revision_get() == REV_ES1_0)
				ret = hwobs44xx_blkmuxreg_modify(
					omap5430es1_prm_debug_cfg.addr, pos, num);
			else
				ret = hwobs44xx_blkmuxreg_modify(
					omap5430_prm_debug_cfg.addr, pos, num);

		/* WKUP - CM1 (CM_AON) */
		} else {
			debug_mux = 0x1;
			if (cpu_revision_get() == REV_ES1_0)
				ret = hwobs44xx_blkmuxreg_modify(
					omap5430es1_cm_core_aon_debug_cfg.addr, pos, num);
			else
				ret = hwobs44xx_blkmuxreg_modify(
					omap5430_cm_core_aon_debug_cfg.addr, pos, num);
		}

		for (i = (pos * 8); i <= (pos * 8) + 7; i++) {
			ret |= mem_write(hwobs54xx_wkup_debug_mux_table[i]->addr,
				debug_mux);
			#ifdef HWOBS54XX_DEBUG
			mem_read(hwobs54xx_wkup_debug_mux_table[i]->addr, &reg_val);
			printf("%s(): wkup_conf_debug_mux_id%d addr: 0x%08x val: 0x%08x\n",
				__func__, i,
				hwobs54xx_wkup_debug_mux_table[i]->addr,
				reg_val);
			#endif
		}
	}

	ret = hwobs44xx_blkmuxreg_modify(
		omap5430_control_debobs_final_mux_sel.addr, pos, final_mux);
	ret |= hwobs54xx_display_signals();

	goto hwobs54xx_setup_prcm_end;

hwobs54xx_setup_prcm_err_arg:
	printf("SYNOPSIS:\n");
	printf("\n");
	printf("  omapconf setup hwobs prcm [pos] [cat] [num]\n");
	printf("\n");
	printf("DESCRIPTION:\n");
	printf("\n");
	printf("  This hwobs setup command allows to control HWOBS mux configuration to select PRCM debug signals.\n");
	printf("  PRCM signals are split in 3 debug mux categories (CM1/CM_AON, CM2/CM_CORE and PRM) which are organized in 'blocks' of 8 debug signals.\n");
	printf("  Each signal is being mapped on a single HWOBS pin or hw_dbg bit. In order to choose a given block of signals from\n");
	printf("  any of the PRCM signals debug mux category, user should refer to TRM documentation detailing all blocks signals content.\n");
	printf("\n");
	printf("PARAMETERS:\n");
	printf("\n");
	printf(" <pos> select block (8 bits) positon whithin 32 bits of observability\n");
	printf("\n");
	printf("   0  -> map selected block on hw_dbg[00:07] observability bits\n");
	printf("   1  -> map selected block on hw_dbg[08:15] observability bits\n");
	printf("   2  -> map selected block on hw_dbg[16:23] observability bits\n");
	printf("   3  -> map selected block on hw_dbg[24:31] observability bits\n");
	printf("\n");
	printf(" <cat> select PRCM signals debug mux category: CM1 (CM_AON), CM2 (CM_CORE) or PRM\n");
	printf("\n");
	printf("  CM1 or CM_AON  -> map selected <pos> hw_dbg bits to CM1 (CM_AON) category of hwobs signals\n");
	printf("  CM2 or CM_CORE -> map selected <pos> hw_dbg bits to CM2 (CM_CORE) category of hwobs signals\n");
	printf("  PRM            -> map selected <pos> hw_dbg bits to PRM category of hwobs signals\n");
	printf("\n");
	printf(" <num> block number whithin selected signals category (value in hexa-decimal)\n");
	printf("\n");
	printf("  0x? -> map <num> block from <cat> onto selected <pos> hw_dbg bits\n");
	printf("\n");
	printf("EXAMPLES:\n");
	printf("\n");
	printf("- Configure hw_dbg[00:07] bits with block 0x22 from CM1 (CM_AON)\n");
	printf("     omapconf setup hwobs prcm 0 CM1 0x22\n");
	printf("\n");
	printf("- Configure hw_dbg[16:23] bits with block 0x01 from PRM\n");
	printf("     omapconf setup hwobs prcm 2 PRM 0x01\n");
	printf("\n");
	printf("TIPS:\n");
	printf("\n");
	printf("  If you need to stick to the same observability settings following platform reboot, you can\n");
	printf("  create a shell script calling omapconf commands to keep your observability setup up-to-date.\n");
	printf("\n");
	return 0;

hwobs54xx_setup_prcm_end:
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs54xx_mpuss_setup
 * @BRIEF		Setup OMAP54XX HWOBS Mux Configuration:
 *			allow selection of desired MPUSS debug signals.
 *			Implicitly configure HWOBS muxes.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 * @param[in]		mode_s: mpuss mux mode value
 * @DESCRIPTION		Setup OMAP54XX HWOBS Mux Configuration:
 *			allow selection of desired MPUSS debug signals.
 *			Implicitly configure HWOBS muxes.
 *//*------------------------------------------------------------------------ */
int hwobs54xx_mpuss_setup(char *mode_s)
{
	unsigned int ret, i = 0;
	unsigned int debug_mux, final_mux;
	unsigned int mode;

	#ifdef HWOBS54XX_DEBUG
	unsigned int reg_val;
	#endif

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	if (mode_s == NULL) {
		fprintf(stderr, "Missing argument!\n\n");
		goto hwobs54xx_setup_mpuss_err_arg;
	}

	hwobs54xx_init_regtable();

	dprintf("%s(): mode_s=%s\n", __func__, mode_s);

	/* Retrieve and check mpuss mux mode */
	ret = sscanf(mode_s, "%u", &mode);
	if (ret != 1) {
		dprintf("%s(): could not retrieve mpuss mux mode\n", __func__);
		goto hwobs54xx_setup_mpuss_err_arg;
	}
	if (mode > 15) {
		printf("Invalid mpuss mux mode! (%s)\n\n", mode_s);
		goto hwobs54xx_setup_mpuss_err_arg;
	}

	dprintf("%s(): mode=%d\n", __func__, mode);

	/* CORE - MPUSS */
	final_mux = 0xFFFFFFFF;
	debug_mux = 0x0;

	ret = mem_write(omap5430_control_debobs_mmr_mpu.addr, mode);

	for (i = 0; i < HWOBS54XX_SIG_MAX_NBR; i++) {
		ret |= mem_write(hwobs54xx_core_debug_mux_table[i]->addr,
			debug_mux);
		#ifdef HWOBS54XX_DEBUG
		mem_read(hwobs54xx_core_debug_mux_table[i]->addr, &reg_val);
		printf("%s(): core_conf_debug_mux_id%d addr: 0x%08x val: 0x%08x\n",
				__func__, i,
				hwobs54xx_core_debug_mux_table[i]->addr,
				reg_val);
		#endif
	}

	ret |= mem_write(omap5430_control_debobs_final_mux_sel.addr, final_mux);
	ret |= hwobs54xx_display_signals();

	goto hwobs54xx_mpuss_end;

hwobs54xx_setup_mpuss_err_arg:
	printf("SYNOPSIS:\n");
	printf("\n");
	printf("  omapconf setup hwobs mpuss <mode>\n");
	printf("\n");
	printf("DESCRIPTION:\n");
	printf("\n");
	printf("  This hwobs setup command allows to control HWOBS mux configuration to select MPUSS debug signals.\n");
	printf("  MPUSS signals are split in 7 mux modes allowing to display various debug profiles over 32 bits.\n");
	printf("  Each signal is being mapped on a single HWOBS pin or hw_dbg bit. In order to choose a given mux mode\n");
	printf("  with particular debug signals of interest, user should refer to TRM documentation detailing mpuss mux modes.\n");
	printf("\n");
	printf("PARAMETERS:\n");
	printf("\n");
	printf(" <mode> mpuss mux mode value (decimal): mpuss mux modes range from mode 0 to mode 7\n");
	printf("\n");
	printf("EXAMPLE:\n");
	printf("\n");
	printf("- Configure hw_dbg[00:31] bits with mux mode 2 from MPUSS\n");
	printf("     omapconf setup hwobs mpuss 2\n");
	printf("\n");
	printf("TIPS:\n");
	printf("\n");
	printf("  If you need to mix MPUSS debug signals (32 bits) with PRCM debug signals (blocks of 8 bits):\n");
	printf("  You can configure MPUSS mux mode first (MPUSS debug bits can not be moved) then overwrite HWOBS\n");
	printf("  configuration of useless MPUSS signals with PRCM blocks of interest.\n");
	printf("\n");
	printf("  If you need to stick to the same observability settings following platform reboot, you can\n");
	printf("  create a shell script calling omapconf commands to keep your observability setup up-to-date.\n");
	printf("\n");
	return 0;

hwobs54xx_mpuss_end:
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs54xx_setup_menu
 * @BRIEF		Change OMAP54XX pinmux to drive HWOBS signals on
 *			external pads.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		Change OMAP54XX pinmux to drive HWOBS signals on
 *			external pads.
 *//*------------------------------------------------------------------------ */
int hwobs54xx_setup_menu(int argc, char *argv[])
{
	unsigned int ret = 0;

	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	hwobs54xx_init_regtable();

	if (argc < 2) {
		fprintf(stderr, "Missing argument!\n\n");
		goto hwobs54xx_setup_err_arg;
	}

	if (strcmp(argv[1], "pinmux") == 0) {
		ret = hwobs54xx_pinmux_setup(argv[2]);
	} else if (strcmp(argv[1], "prcm") == 0) {
		ret = hwobs54xx_prcm_setup(argv[2], argv[3], argv[4]);
	} else	if (strcmp(argv[1], "mpuss") == 0) {
		ret = hwobs54xx_mpuss_setup(argv[2]);
#if 0 /* FIXME */
	} else	if (strcmp(argv[1], "abe") == 0) {
		ret = hwobs54xx_setup_abe(argc, argv);
#endif
	} else {
		printf("Non supported argument: (%s)\n\n", argv[1]);
		goto hwobs54xx_setup_err_arg;
	}
	goto hwobs54xx_setup_end;

hwobs54xx_setup_err_arg:
	autoadjust_table_init(table);

	row = 0;
	autoadjust_table_strncpy(table, row, 0, "Category");
	autoadjust_table_strncpy(table, row, 1, "Command (## OMAP5-ONLY ##)");
	autoadjust_table_strncpy(table, row, 2, "Description & Options");
	row++;
	autoadjust_table_strncpy(table, row, 0,	"Arguments for HWOBS setup:");
	row++;

	autoadjust_table_strncpy(table, row, 1,
		"omapconf setup hwobs pinmux [padset_cfg]");
	autoadjust_table_strncpy(table, row, 2,
		"Change pinmux to drive HWOBS signals on external pads:");
	row++;
	autoadjust_table_strncpy(table, row, 2,
		"  Pads must be selected among 16 pads from WKUP CTRL Module");
	row++;
	autoadjust_table_strncpy(table, row, 2,
		"  and two sets of 16 pads from CORE CTRL Module.");
	row +=2;
	autoadjust_table_strncpy(table, row, 1,
		"omapconf setup hwobs prcm [pos][type][num]");
	autoadjust_table_strncpy(table, row, 2,
		"Select desired HWOBS PRCM 'block' Signals.");
	row++;
	autoadjust_table_strncpy(table, row, 1,
		"omapconf setup hwobs mpuss [mode]");
	autoadjust_table_strncpy(table, row, 2,
		"Select desired MPUSS mux mode and Signals.");
#if 0 /* FIXME */
	row++;
	autoadjust_table_strncpy(table, row, 1,	"omapconf setup hwobs abe");
	autoadjust_table_strncpy(table, row, 2,
		"Select desired ABE SS mux mode and Signals.");
#endif
	row += 2;

	autoadjust_table_print(table, row, 3);
	return 0;

hwobs54xx_setup_end:
	return ret;

}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs54xx_display_pads
 * @BRIEF		Dump OMAP54XX HW Observability PADCONFs regs.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	pad_reg_table: table of pad registers
 * @DESCRIPTION		Dump OMAP54XX HW Observability PADCONFs regs.
 *//*------------------------------------------------------------------------ */
int hwobs54xx_display_pads(pad_cell pad_reg_table[HWOBS54XX_PAD_MAX_NBR+1])
{
	unsigned int ret, pad_id = 0;
	unsigned short pad_val;
	int err = 0;

	char str_ctrl_mod[OMAPCONF_REG_NAME_MAX_LENGTH + 1] = "";
	char autoadjust_table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	hwobs54xx_init_regtable();

	if (pad_reg_table == hwobs54xx_wkup_sys_pad_reg_table) {
		pad_id = 0;
		strcpy(str_ctrl_mod, hwobs54xx_debobs_final_mux_sel_names[0]);
	} else if (pad_reg_table == hwobs54xx_core_c2c_pad_reg_table) {
		pad_id = 16;
		strcpy(str_ctrl_mod, hwobs54xx_debobs_final_mux_sel_names[1]);
	} else if (pad_reg_table == hwobs54xx_core_per_pad_reg_table) {
		pad_id = 16;
		strcpy(str_ctrl_mod, hwobs54xx_debobs_final_mux_sel_names[1]);
	} else {
		dprintf("%s(): invalid array pointer passed as argument\n", __func__);
	}

	autoadjust_table_init(autoadjust_table);

	row = 0;
	strncpy(autoadjust_table[row][0], "bit", TABLE_MAX_ELT_LEN);
	strncpy(autoadjust_table[row][1], "ctrl mod", TABLE_MAX_ELT_LEN);
	strncpy(autoadjust_table[row][2], "16 bits pad. reg.",
		TABLE_MAX_ELT_LEN);
	strncpy(autoadjust_table[row][3], "pad. addr.", TABLE_MAX_ELT_LEN);
	strncpy(autoadjust_table[row][4], "pad. val.", TABLE_MAX_ELT_LEN);

	while (strcmp(pad_reg_table[row].name, "END") != 0) {
		ret = hwobs44xx_padreg_read(pad_reg_table[row].addr, &pad_val);

		/* display register pad name, addr & content (hex) */
		if (ret == 0) {
			snprintf(autoadjust_table[row+1][0], TABLE_MAX_ELT_LEN, "%d",
				pad_id);
			snprintf(autoadjust_table[row+1][1], TABLE_MAX_ELT_LEN, "%s",
				str_ctrl_mod);
			snprintf(autoadjust_table[row+1][2], TABLE_MAX_ELT_LEN, "%s",
				pad_reg_table[row].name);
			snprintf(autoadjust_table[row+1][3], TABLE_MAX_ELT_LEN, "0x%08X",
				(unsigned int)(pad_reg_table[row].addr));
			snprintf(autoadjust_table[row+1][4], TABLE_MAX_ELT_LEN, "0x%04X",
				pad_val);
		} else {
			fprintf(stderr,
				"omapconf: read error! (addr=0x%08X, err=%d)\n",
				(unsigned int)(pad_reg_table[row].addr), ret);
			err = OMAPCONF_ERR_REG_ACCESS;
		}
		row++;
		pad_id++;
	}

	autoadjust_table_print(autoadjust_table, row+1, 5);

	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs54xx_display_signals
 * @BRIEF		Print current OMAP54XX Mux Configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 * @param[in]		none
 * @DESCRIPTION		Print current OMAP54XX Mux Configuration.
 *			Print list of selected debug signals
 *			for each hw_dbg[0:31] debug pin.
 *//*------------------------------------------------------------------------ */
int hwobs54xx_display_signals(void)
{
	unsigned int pad_check = 0, ret = 0;
	int err = 0;

	unsigned int hwobs_mux, hwobs_mux_bit, debug_mux, final_mux, final_mux_bit;
	char str_final_mux[OMAPCONF_REG_NAME_MAX_LENGTH + 1] = "";
	char str_debug_mux[OMAPCONF_REG_NAME_MAX_LENGTH + 1] = "";
	char str_hwobs_sig[OMAPCONF_REG_NAME_MAX_LENGTH + 1] = "";
	char str_hwobs_bit[OMAPCONF_REG_NAME_MAX_LENGTH + 1] = "";
	char str_buf[OMAPCONF_REG_NAME_MAX_LENGTH + 1] = "";

	char autoadjust_table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row = 0;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	hwobs54xx_init_regtable();

	pad_check = hwobs54xx_check_pinmux(HWOBS54XX_PAD_FULL_CHECK);

	hwobs54xx_display_hwobs_ctrl_cfg();
	hwobs54xx_check_gating();

	if (pad_check != HWOBS54XX_SIG_MAX_NBR) {
		pad_check = 0;

		ret = mem_read(omap5430_control_debobs_final_mux_sel.addr, &final_mux);
		if (ret != 0) {
			fprintf(stderr, "omapconf: internal error (failed to read)!\n");
			return OMAPCONF_ERR_REG_ACCESS;
	}

		#ifdef HWOBS54XX_DEBUG
		/* hardcoded register value for testing only */
		final_mux = 0x00FFFF00;
		#endif

		while (strcmp(hwobs54xx_signal_names[row], "END") != 0) {
			pad_check = hwobs54xx_check_pinmux(row);
			if ((row % 16) == 0) {
				autoadjust_table_init(autoadjust_table);

				strncpy(autoadjust_table[row % 16][0], "bit",
					TABLE_MAX_ELT_LEN);
				strncpy(autoadjust_table[row % 16][1], "pin mux",
					TABLE_MAX_ELT_LEN);
				strncpy(autoadjust_table[row % 16][2], "final mux",
					TABLE_MAX_ELT_LEN);
				strncpy(autoadjust_table[row % 16][3], "debug mux",
					TABLE_MAX_ELT_LEN);
				strncpy(autoadjust_table[row % 16][4], "debug signal",
					TABLE_MAX_ELT_LEN);
			}

			final_mux_bit = ((final_mux & (1 << row)) >> row);
			strcpy(str_final_mux, hwobs54xx_debobs_final_mux_sel_names[final_mux_bit]);
			strcpy(str_hwobs_sig, "");
			strcpy(str_hwobs_bit, "");

			if (final_mux_bit) {
				ret = mem_read(hwobs54xx_core_debug_mux_table[row]->addr, &debug_mux);
				debug_mux &= 0x1F;

				#ifdef HWOBS54XX_DEBUG
				/* hardcoded register value for testing only */
				if (row > 15)
					debug_mux = 0x0;
				else
					debug_mux = 0x5;
				#endif

				strcpy(str_debug_mux, hwobs54xx_ctrl_core_conf_debug_sel_tst_names[debug_mux]);

				switch (debug_mux) {
					case 0x0:
						ret = mem_read(omap5430_control_debobs_mmr_mpu.addr, &hwobs_mux);
						break;

					case 0x5:
						if (cpu_revision_get() == REV_ES1_0)
							ret = mem_read(omap5430es1_cm_core_debug_cfg.addr, &hwobs_mux);
						else
							ret = mem_read(omap5430_cm_core_debug_cfg.addr, &hwobs_mux);
						strcat(str_debug_mux, " (CM_CORE)");
						break;

					case 0x8:
						/* no internal mux for ABE Subsystem signals */
						break;

					default:
						strcat(str_hwobs_sig, "???????????");
						strcat(str_hwobs_bit, "???????");
						break;
				}
			} else {
				ret = mem_read(hwobs54xx_wkup_debug_mux_table[row]->addr, &debug_mux);
				debug_mux &= 0xF;

				#ifdef HWOBS54XX_DEBUG
				/* hardcoded register value for testing only */
				if (row > 15)
					debug_mux = 0x1;
				else
					debug_mux = 0x0;
				#endif

				strcpy(str_debug_mux, hwobs54xx_ctrl_wkup_conf_debug_sel_tst_names[debug_mux]);

				switch (debug_mux) {
					case 0x0:
						if (cpu_revision_get() == REV_ES1_0)
							ret = mem_read(omap5430es1_prm_debug_cfg.addr, &hwobs_mux);
						else
							ret = mem_read(omap5430_prm_debug_cfg.addr, &hwobs_mux);
						break;

					case 0x1:
						if (cpu_revision_get() == REV_ES1_0)
							ret = mem_read(omap5430es1_cm_core_aon_debug_cfg.addr, &hwobs_mux);
						else
							ret = mem_read(omap5430_cm_core_aon_debug_cfg.addr, &hwobs_mux);
						strcat(str_debug_mux, " (CM_AON)");
						break;

					default:
						strcat(str_hwobs_sig, "???????????");
						strcat(str_hwobs_bit, "???????");
						break;
				}
			}

			#ifdef HWOBS54XX_DEBUG
			/* hardcoded register value for testing only */
			hwobs_mux = 0x5;
			#endif

			/* PRCM signals formating */
			if (((final_mux_bit == 1) && (debug_mux == 0x5)) ||
				((final_mux_bit == 0) && (debug_mux == 0x0)) ||
				((final_mux_bit == 0) && (debug_mux == 0x1))) {
				strcat(str_hwobs_sig, "block: 0x");
				hwobs_mux = ((hwobs_mux & ~(char_mask[(row / 8)])) >> ((row / 8) * 8));
				sprintf(str_buf, "%x", hwobs_mux);
				strcat(str_hwobs_sig, str_buf);

				strcat(str_hwobs_bit, "bit: ");
				hwobs_mux_bit = (row % 8);
				sprintf(str_buf, "%u", hwobs_mux_bit);
				strcat(str_hwobs_bit, str_buf);
			/* MPUSS signals formating */
			} else if ((final_mux_bit == 1) && (debug_mux == 0x0)) {
				strcat(str_hwobs_sig, "mode : ");
				sprintf(str_buf, "%u", hwobs_mux);
				strcat(str_hwobs_sig, str_buf);

				strcat(str_hwobs_bit, "bit: ");
				sprintf(str_buf, "%u", row);
				strcat(str_hwobs_bit, str_buf);
			/* ABE SS signals formating */
			} else if ((final_mux_bit == 1) && (debug_mux == 0x8)) {
				#if 0
				if ((row >= OMAP4430_HWOBS_ABE_UNRESERVED_FIRST) && (row <= OMAP4430_HWOBS_ABE_UNRESERVED_LAST))
					strcat(str_hwobs_sig, "mode : n/a");
				else
					strcat(str_hwobs_sig, "reserved");
				#endif

				strcat(str_hwobs_bit, "bit: ");
				sprintf(str_buf, "%u", row);
				strcat(str_hwobs_bit, str_buf);
			}

			#ifdef HWOBS54XX_DEBUG
			printf("hwobs54xx_signal_names[row=%d] = %s\n",
				row , hwobs54xx_signal_names[row]);
			#endif
			/* display register pad name, addr & content (hex) */
			snprintf(autoadjust_table[(row % 16) + 1][0],
				TABLE_MAX_ELT_LEN, "%d", row);
			snprintf(autoadjust_table[(row % 16) + 1][2],
				TABLE_MAX_ELT_LEN, "%s", str_final_mux);
			snprintf(autoadjust_table[(row % 16) + 1][3],
				TABLE_MAX_ELT_LEN, "%s", str_debug_mux);

			if (pad_check == 0) {
				snprintf(autoadjust_table[(row % 16) + 1][1],
					TABLE_MAX_ELT_LEN, "%s",
					hwobs54xx_signal_names[row]);
				snprintf(autoadjust_table[(row % 16) + 1][4],
					TABLE_MAX_ELT_LEN, "%s", str_hwobs_sig);
				snprintf(autoadjust_table[(row % 16) + 1][5],
					TABLE_MAX_ELT_LEN, "%s", str_hwobs_bit);
			} else {
				snprintf(autoadjust_table[(row % 16) + 1][1],
					TABLE_MAX_ELT_LEN, "%s",
					"not configured");
				snprintf(autoadjust_table[(row % 16) + 1][4],
					TABLE_MAX_ELT_LEN, "%s", "???????????");
				snprintf(autoadjust_table[(row % 16) + 1][5],
					TABLE_MAX_ELT_LEN, "%s", "??????");
			}

			if ((row + 1) % 16 == 0) {
				autoadjust_table_print(autoadjust_table,
					(row % 16) + 2, 6);
			}

			row++;
		}
	}

	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs54xx_display_hwobs_ctrl_cfg
 * @BRIEF		Print current OMAP54XX CONTROL_HWOBS_CONTROL register
 *			configuration.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		Print current OMAP54XX CONTROL_HWOBS_CONTROL register
 *			configuration.
 *//*------------------------------------------------------------------------ */
int hwobs54xx_display_hwobs_ctrl_cfg(void)
{
	unsigned int ret = 0;
	unsigned int reg_val;

	char autoadjust_table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row = 0;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	hwobs54xx_init_regtable();

	autoadjust_table_init(autoadjust_table);
	strncpy(autoadjust_table[row][0], "HWOBS         Main Mux Settings",
		TABLE_MAX_ELT_LEN);
	strncpy(autoadjust_table[row][1], "Current", TABLE_MAX_ELT_LEN);
	strncpy(autoadjust_table[row++][2], "Reset Value", TABLE_MAX_ELT_LEN);

	ret = mem_read(omap5430_control_hwobs_control.addr, &reg_val);

#ifdef HWOBS54XX_DEBUG
	reg_val = 0x7FEF9;
#endif

	strncpy(autoadjust_table[row][0], "Observable Signals Gating",
		TABLE_MAX_ELT_LEN);
	if (((reg_val) & OMAP5430_HWOBS_MACRO_ENABLE_MASK) == 0x0) {
		strncpy(autoadjust_table[row][1], "GATED", TABLE_MAX_ELT_LEN);
	} else {
		if (((reg_val) & OMAP5430_HWOBS_ALL_ZERO_MODE_MASK) ==
			OMAP5430_HWOBS_ALL_ZERO_MODE_MASK) {
			strncpy(autoadjust_table[row][1], "FORCED ZERO",
				TABLE_MAX_ELT_LEN);
		} else if (((reg_val) & OMAP5430_HWOBS_ALL_ONE_MODE_MASK) ==
			OMAP5430_HWOBS_ALL_ONE_MODE_MASK) {
			strncpy(autoadjust_table[row][1], "FORCED ONE",
				TABLE_MAX_ELT_LEN);
		} else {
			strncpy(autoadjust_table[row][1], "ENABLED (NOT GATED)",
				TABLE_MAX_ELT_LEN);
		}
	}
	strncpy(autoadjust_table[row++][2], "GATED", TABLE_MAX_ELT_LEN);

	strncpy(autoadjust_table[row][0], "Observable DPLLs Signals Gating",
		TABLE_MAX_ELT_LEN);
	if (((reg_val) & OMAP5430_HWOBS_CLKOBS_GATE_ENABLE_MASK) ==
		OMAP5430_HWOBS_CLKOBS_GATE_ENABLE_MASK) {
		strncpy(autoadjust_table[row][1], "GATED",
			TABLE_MAX_ELT_LEN);
	} else {
		strncpy(autoadjust_table[row][1], "ENABLED (NOT GATED)",
			TABLE_MAX_ELT_LEN);
	}
	strncpy(autoadjust_table[row++][2], "ENABLED (NOT GATED)",
		TABLE_MAX_ELT_LEN);

	row++;
	strncpy(autoadjust_table[row++][0], "Clock Divider Selection",
		TABLE_MAX_ELT_LEN);
	strncpy(autoadjust_table[row][0], "    po_hwobs(0)", TABLE_MAX_ELT_LEN);
	snprintf(autoadjust_table[row][1], TABLE_MAX_ELT_LEN, "0x%02X",	((reg_val)
		& OMAP5430_HWOBS_CLKDIV_SEL_MASK) >> OMAP5430_HWOBS_CLKDIV_SEL_SHIFT);
	snprintf(autoadjust_table[row++][2], TABLE_MAX_ELT_LEN, "0x%02X", 0);
	strncpy(autoadjust_table[row][0], "    po_hwobs(1)", TABLE_MAX_ELT_LEN);
	snprintf(autoadjust_table[row][1], TABLE_MAX_ELT_LEN, "0x%02X", ((reg_val)
		& OMAP5430_HWOBS_CLKDIV_SEL_1_MASK) >> OMAP5430_HWOBS_CLKDIV_SEL_1_SHIFT);
	snprintf(autoadjust_table[row++][2], TABLE_MAX_ELT_LEN, "0x%02X", 0);
	strncpy(autoadjust_table[row][0], "    po_hwobs(2)", TABLE_MAX_ELT_LEN);
	snprintf(autoadjust_table[row][1], TABLE_MAX_ELT_LEN, "0x%02X", ((reg_val)
		& OMAP5430_HWOBS_CLKDIV_SEL_2_MASK) >> OMAP5430_HWOBS_CLKDIV_SEL_2_SHIFT);
	snprintf(autoadjust_table[row++][2], TABLE_MAX_ELT_LEN, "0x%02X", 0);

	autoadjust_table_print(autoadjust_table, row, 3);

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs54xx_display_cfg
 * @BRIEF		Dump overall OMAP54XX HW Observability configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		Dump overall OMAP54XX HW Observability configuration
 *//*------------------------------------------------------------------------ */
int hwobs54xx_display_cfg(void)
{
	unsigned int ret;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	hwobs54xx_init_regtable();

	ret = hwobs54xx_display_pads(hwobs54xx_wkup_sys_pad_reg_table);
	ret = hwobs54xx_display_pads(hwobs54xx_core_c2c_pad_reg_table);
	ret = hwobs54xx_display_pads(hwobs54xx_core_per_pad_reg_table);

	ret = hwobs54xx_display_signals();

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs54xx_init_regtable
 * @BRIEF		initialize hwobs tables
 * @DESCRIPTION		initialize hwobs tables
 *//*------------------------------------------------------------------------ */
static int hwobs54xx_init_regtable(void)
{
	int err = 0;
	static unsigned short done = 0;

	if (done == 0) {
		hwobs54xx_wkup_sys_pad_table_init();
		hwobs54xx_core_c2c_pad_table_init();
		hwobs54xx_core_per_pad_table_init();
		done = 1;
	}

	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs54xx_main
 * @BRIEF		main entry point for HWOBS functions
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		main entry point for HWOBS functions
 *			argv[0] = function ("setup", "test", "cfg")
 *			argv[1] = (optional) arguments vary based on function
 *			argv[2] = (optional) arguments vary based on function
 *			argv[3] = (optional) arguments vary based on function
 *			argv[4] = (optional)  arguments vary based on function
 *//*------------------------------------------------------------------------ */
int hwobs54xx_main(int argc, char *argv[])
{
	int ret = 0;

	if (argc == 0) {
		goto hwobs54xx_main_err_arg;
	}

	hwobs54xx_init_regtable();

	if (strcmp(argv[0], "setup") == 0) {
		ret = hwobs54xx_setup_menu(argc, argv);
	} else if (strcmp(argv[0], "test") == 0) {
		ret = hwobs54xx_test(argv[1]);
	} else if (strcmp(argv[0], "cfg") == 0) {
		ret = hwobs54xx_display_cfg();
	} else {
		goto hwobs54xx_main_err_arg;
	}
	goto hwobs54xx_main_end;

hwobs54xx_main_err_arg:
	help(HELP_HWOBS);
	ret = 0;

hwobs54xx_main_end:
	return ret;
}
