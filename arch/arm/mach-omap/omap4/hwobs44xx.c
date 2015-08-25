/*
 *
 * @Component			OMAPCONF
 * @Filename			hwobs44xx.c
 * @Description			OMAP4 HW Observability - Hardware Debug Signals
 *				Mux Configuration
 * @Author			Cedric Vamour (c-vamour@ti.com)
 * @Date			2010
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
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


#include <hwobs44xx.h>
#include <hwobs_regs44xx.h>
#include <lib44xx.h>
#include <lib.h>
#include <mem.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <help.h>
#include <cpuinfo.h>
#include <ctype.h>
#include <autoadjust_table.h>


/* #define HWOBS44XX_DEBUG */
#ifdef HWOBS44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


pad_cell hwobs_pad_reg_table[OMAP4430_HWOBS_MAX_NBR + 1];

reg_table hwobs_core_debug_mux_table[OMAP4430_HWOBS_MAX_NBR + 1];
reg_table hwobs_wkup_debug_mux_table[OMAP4430_HWOBS_MAX_NBR + 1];


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs44xx_padreg_read
 * @BRIEF		read 16 bits pad value at given pad address
 *			(word aligned)
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_MEM_DEV if mem device not available
 *			OMAPCONF_ERR_MEM_MAP if memory could not be mapped
 *			OMAPCONF_ERR_UNEXPECTED if adress is not word aligned
 * @param[in]		padreg_addr: 32-bit register address
 * @param[in,out]	pad_val: pointer where to store pad read value
 * @DESCRIPTION		read 16 bits pad value at given pad address
 *			(word aligned)
 *//*------------------------------------------------------------------------ */
int hwobs44xx_padreg_read(unsigned int padreg_addr, unsigned short *pad_val)
{
	int ret = 0;
	unsigned int reg_val;

	if (padreg_addr % 0x4 == 0) {
		ret = mem_read(padreg_addr, &reg_val);
		*pad_val = (((reg_val) &= 0x0000FFFF) >> 0);
	} else if (padreg_addr % 0x4 == 2) {
		ret = mem_read(padreg_addr - 2, &reg_val);
		*pad_val = (((reg_val) &= 0xFFFF0000) >> 16);
	} else {
		return OMAPCONF_ERR_UNEXPECTED;
	}

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs44xx_padreg_write
 * @BRIEF		write 16 bits pad value at given pad address
 *			(word aligned)
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_MEM_DEV if mem device not available
 *			OMAPCONF_ERR_MEM_MAP if memory could not be mapped
 *			OMAPCONF_ERR_UNEXPECTED if adress is not word aligned
 * @param[in]		padreg_addr: 32-bit register address
 * @param[in]		pad_val: value to be written into pad register
 * @DESCRIPTION		write 16 bits pad value at given pad address
 *			(word aligned)
 *//*------------------------------------------------------------------------ */
int hwobs44xx_padreg_write(unsigned int padreg_addr, unsigned short pad_val)
{
	int ret = 0;
	unsigned int reg_val;

	if (padreg_addr % 0x4 == 0) {
		ret = mem_read(padreg_addr, &reg_val);
		reg_val = (reg_val & 0xFFFF0000) | ((pad_val) << 0);
		ret = mem_write(padreg_addr, reg_val);
	} else if (padreg_addr % 0x4 == 2) {
		ret = mem_read(padreg_addr-2, &reg_val);
		reg_val = ((pad_val) << 16) | (reg_val & 0x0000FFFF);
		ret = mem_write(padreg_addr - 2, reg_val);
	} else {
		return OMAPCONF_ERR_UNEXPECTED;
	}

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs44xx_blkmuxreg_modify
 * @BRIEF		read/modify block muxing (8 bits) at given 32 bits mux
 *			reg address
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_MEM_DEV if mem device not available
 *			OMAPCONF_ERR_MEM_MAP if memory could not be mapped
 *			OMAPCONF_ERR_UNEXPECTED if block position is not valid
 * @param[in]		muxreg_addr: 32-bit register address
 * @param[in]		block_pos: position of block to be modified
 * @param[in]		mux_val: value to be written into mux register
 * @DESCRIPTION		read/modify block muxing (8 bits) at given 32 bits mux
 *			reg address
 *//*------------------------------------------------------------------------ */
int hwobs44xx_blkmuxreg_modify(unsigned int muxreg_addr,
	unsigned int block_pos, char mux_val)
{
	int ret = 0;
	unsigned int reg_val;

	ret = mem_read(muxreg_addr, &reg_val);

	if (ret == 0) {
		reg_val = (reg_val & char_mask[block_pos]) |
			((mux_val) << (block_pos * 8));
		ret = mem_write(muxreg_addr, reg_val);
	}

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs44xx_pad_regtable_init
 * @BRIEF		initialize regtable for pad registers
 * @RETURNS		0
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		initialize regtable for pad registers
 *//*------------------------------------------------------------------------ */
static int hwobs44xx_pad_regtable_init(void)
{
	int i = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	/* Init PADCONF registers table */
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_DPM_EMU0");
	hwobs_pad_reg_table[i++].addr = OMAP4430_CONTROL_CORE_PAD1_DPM_EMU0;
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_DPM_EMU1");
	hwobs_pad_reg_table[i++].addr = OMAP4430_CONTROL_CORE_PAD0_DPM_EMU1;
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_DPM_EMU2");
	hwobs_pad_reg_table[i++].addr = OMAP4430_CONTROL_CORE_PAD1_DPM_EMU2;
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_DPM_EMU3");
	hwobs_pad_reg_table[i++].addr = OMAP4430_CONTROL_CORE_PAD0_DPM_EMU3;
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_DPM_EMU4");
	hwobs_pad_reg_table[i++].addr = OMAP4430_CONTROL_CORE_PAD1_DPM_EMU4;
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_DPM_EMU5");
	hwobs_pad_reg_table[i++].addr = OMAP4430_CONTROL_CORE_PAD0_DPM_EMU5;
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_DPM_EMU6");
	hwobs_pad_reg_table[i++].addr = OMAP4430_CONTROL_CORE_PAD1_DPM_EMU6;
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_DPM_EMU7");
	hwobs_pad_reg_table[i++].addr = OMAP4430_CONTROL_CORE_PAD0_DPM_EMU7;
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_DPM_EMU8");
	hwobs_pad_reg_table[i++].addr = OMAP4430_CONTROL_CORE_PAD1_DPM_EMU8;
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_DPM_EMU9");
	hwobs_pad_reg_table[i++].addr = OMAP4430_CONTROL_CORE_PAD0_DPM_EMU9;
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_DPM_EMU10");
	hwobs_pad_reg_table[i++].addr = OMAP4430_CONTROL_CORE_PAD1_DPM_EMU10;
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_DPM_EMU11");
	hwobs_pad_reg_table[i++].addr = OMAP4430_CONTROL_CORE_PAD0_DPM_EMU11;
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_DPM_EMU12");
	hwobs_pad_reg_table[i++].addr = OMAP4430_CONTROL_CORE_PAD1_DPM_EMU12;
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_DPM_EMU13");
	hwobs_pad_reg_table[i++].addr = OMAP4430_CONTROL_CORE_PAD0_DPM_EMU13;
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_DPM_EMU14");
	hwobs_pad_reg_table[i++].addr = OMAP4430_CONTROL_CORE_PAD1_DPM_EMU14;
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_DPM_EMU15");
	hwobs_pad_reg_table[i++].addr = OMAP4430_CONTROL_CORE_PAD0_DPM_EMU15;
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_DPM_EMU16");
	hwobs_pad_reg_table[i++].addr = OMAP4430_CONTROL_CORE_PAD1_DPM_EMU16;
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_DPM_EMU17");
	hwobs_pad_reg_table[i++].addr = OMAP4430_CONTROL_CORE_PAD0_DPM_EMU17;
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_DPM_EMU18");
	hwobs_pad_reg_table[i++].addr = OMAP4430_CONTROL_CORE_PAD1_DPM_EMU18;
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_DPM_EMU19");
	hwobs_pad_reg_table[i++].addr = OMAP4430_CONTROL_CORE_PAD0_DPM_EMU19;

	strcpy(hwobs_pad_reg_table[i].name, "PAD1_USBB1_ULPITLL_CLK");
	hwobs_pad_reg_table[i++].addr =
		OMAP4430_CONTROL_CORE_PAD1_USBB1_ULPITLL_CLK;
	strcpy(hwobs_pad_reg_table[i].name, "PAD0_USBB1_ULPITLL_STP");
	hwobs_pad_reg_table[i++].addr =
		OMAP4430_CONTROL_CORE_PAD0_USBB1_ULPITLL_STP;
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_USBB1_ULPITLL_DIR");
	hwobs_pad_reg_table[i++].addr =
		OMAP4430_CONTROL_CORE_PAD1_USBB1_ULPITLL_DIR;
	strcpy(hwobs_pad_reg_table[i].name, "PAD0_USBB1_ULPITLL_NXT");
	hwobs_pad_reg_table[i++].addr =
		OMAP4430_CONTROL_CORE_PAD0_USBB1_ULPITLL_NXT;
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_USBB1_ULPITLL_DAT0");
	hwobs_pad_reg_table[i++].addr =
		OMAP4430_CONTROL_CORE_PAD1_USBB1_ULPITLL_DAT0;
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_USBB1_ULPITLL_DAT1");
	hwobs_pad_reg_table[i++].addr =
		OMAP4430_CONTROL_CORE_PAD0_USBB1_ULPITLL_DAT1;
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_USBB1_ULPITLL_DAT2");
	hwobs_pad_reg_table[i++].addr =
		OMAP4430_CONTROL_CORE_PAD1_USBB1_ULPITLL_DAT2;
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_USBB1_ULPITLL_DAT3");
	hwobs_pad_reg_table[i++].addr =
		OMAP4430_CONTROL_CORE_PAD0_USBB1_ULPITLL_DAT3;
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_USBB1_ULPITLL_DAT4");
	hwobs_pad_reg_table[i++].addr =
		OMAP4430_CONTROL_CORE_PAD1_USBB1_ULPITLL_DAT4;
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_USBB1_ULPITLL_DAT5");
	hwobs_pad_reg_table[i++].addr =
		OMAP4430_CONTROL_CORE_PAD0_USBB1_ULPITLL_DAT5;
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_USBB1_ULPITLL_DAT6");
	hwobs_pad_reg_table[i++].addr =
		OMAP4430_CONTROL_CORE_PAD1_USBB1_ULPITLL_DAT6;
	strcpy(hwobs_pad_reg_table[i].name, "PAD1_USBB1_ULPITLL_DAT7");
	hwobs_pad_reg_table[i++].addr =
		OMAP4430_CONTROL_CORE_PAD0_USBB1_ULPITLL_DAT7;

	strcpy(hwobs_pad_reg_table[i].name, "END");
	hwobs_pad_reg_table[i].addr = 0;
	dprintf("hwobs_pad_reg_table last index=%d, size=%d\n", i, i + 1);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs44xx_mux_regtable_init
 * @BRIEF		initialize regtable for mux registers
 * @RETURNS		0
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		initialize regtable for mux registers
 *//*------------------------------------------------------------------------ */
static int hwobs44xx_mux_regtable_init(void)
{
	unsigned int i = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	/* Init wkup mux registers table */
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_0;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_1;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_2;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_3;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_4;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_5;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_6;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_7;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_8;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_9;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_10;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_11;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_12;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_13;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_14;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_15;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_16;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_17;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_18;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_19;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_20;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_21;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_22;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_23;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_24;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_25;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_26;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_27;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_28;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_29;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_30;
	hwobs_wkup_debug_mux_table[i++].addr = OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_31;

	i = 0;

	/* Init core mux registers table */
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_0;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_1;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_2;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_3;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_4;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_5;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_6;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_7;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_8;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_9;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_10;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_11;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_12;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_13;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_14;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_15;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_16;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_17;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_18;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_19;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_20;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_21;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_22;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_23;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_24;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_25;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_26;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_27;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_28;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_29;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_30;
	hwobs_core_debug_mux_table[i++].addr = OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_31;

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs44xx_regtable_init
 * @BRIEF		initialize hwobs tables
 * @RETURNS		0
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		initialize hwobs tables
 *//*------------------------------------------------------------------------ */
static int hwobs44xx_regtable_init(void)
{
	int err = 0;

	err = hwobs44xx_pad_regtable_init();
	err |= hwobs44xx_mux_regtable_init();

	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs44xx_pinmux_check
 * @BRIEF		check hwobs pinmux is properly configured.
 * @RETURNS		0 in case of success
 *			number of non-configured pins otherwise
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		check hwobs pinmux is properly configured.
 *//*------------------------------------------------------------------------ */
static int hwobs44xx_pinmux_check(unsigned int check_field)
{
	unsigned int i = 0;
	unsigned short reg_pad_val;
	int err = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	hwobs44xx_regtable_init();

	if (check_field == OMAP4430_HWOBS_PAD_FULL_CHECK) {
		while (strcmp(hwobs_pad_reg_table[i].name, "END") != 0) {
			hwobs44xx_padreg_read(hwobs_pad_reg_table[i].addr, &reg_pad_val);
			if (((reg_pad_val) & 0x0006) != 0x0006)
				err++;
			i++;
		}

		if (err == OMAP4430_HWOBS_MAX_NBR) {
			printf("Note: Pinmux are not configured to drive HWOBS signals on external pads\n");
			printf("\n");
			printf("Use following command: ./omapconf hwobs setup pinmux\n");
			printf("\n");
		} else if (err != 0) {
			printf("Warning: NOT all Pinmux are configured to drive HWOBS signals on external pads:\n");
			printf("         > Number of non-configured Pinmux: %d\n", err);
			printf("\n");
			printf("Use following command: ./omapconf hwobs setup pinmux\n");
			printf("\n");
		}
	} else if (check_field < OMAP4430_HWOBS_MAX_NBR) {
		hwobs44xx_padreg_read(hwobs_pad_reg_table[check_field].addr, &reg_pad_val);
		if (((reg_pad_val) & 0x0006) != 0x0006)
			err++;
	}

	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs44xx_gating_check
 * @BRIEF		check hwobs signals are not gated or tied low/high.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_INTERNAL
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		check hwobs signals are not gated or tied low/high.
 *//*------------------------------------------------------------------------ */
static int hwobs44xx_gating_check()
{
	unsigned short reg_val;
	int err = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	hwobs44xx_regtable_init();

	hwobs44xx_padreg_read(OMAP4430_CONTROL_CORE_HWOBS_CONTROL, &reg_val);

	#ifdef HWOBS44XX_DEBUG
	reg_val = 0x7FEF9;
	#endif

	if (((reg_val) & 0x1) == 0x0) {
		printf("Warning: All HWOBS signals outputs are gated at hwobs ctrl mux level\n");
		err = OMAPCONF_ERR_INTERNAL;
	}

	if (((reg_val) & 0x2) == 0x2) {
		printf("Warning: All HWOBS signals outputs are tied to '1' at hwobs ctrl mux level\n");
		err = OMAPCONF_ERR_INTERNAL;
	}

	if (((reg_val) & 0x4) == 0x4) {
		printf("Warning: All HWOBS signals outputs are tied to '0' at hwobs ctrl mux level\n");
		err = OMAPCONF_ERR_INTERNAL;
	}

	if (((reg_val) & 0x100) == 0x100) {
		printf("Warning: All HWOBS signals output at the DPLL are gated\n");
		err = OMAPCONF_ERR_INTERNAL;
	}

	if (((reg_val) & 0xF8) == 0x0) {
		printf("Warning: CONTROL_CORE_HWOBS_CONTROL <HWOBS_CLKDIV_SEL> must be configured\n");
		err = OMAPCONF_ERR_INTERNAL;
	}

	if (err == OMAPCONF_ERR_INTERNAL) {
		printf("\n");
		printf("Use following command: ./omapconf hwobs test enable\n");
		printf("\n");
	}

	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs44xx_ctrl_cfg_show
 * @BRIEF		Print current OMAP44XX CONTROL_HWOBS_CONTROL register
 *			configuration.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		Print current OMAP44XX CONTROL_HWOBS_CONTROL register
 *			configuration.
 *//*------------------------------------------------------------------------ */
int hwobs44xx_ctrl_cfg_show(void)
{
	unsigned int ret = 0;
	unsigned int reg_val;

	char autoadjust_table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	hwobs44xx_regtable_init();

	autoadjust_table_init(autoadjust_table);
	strncpy(autoadjust_table[row][0], "HWOBS         Main Mux Settings",
		TABLE_MAX_ELT_LEN);
	strncpy(autoadjust_table[row][1], "Current", TABLE_MAX_ELT_LEN);
	strncpy(autoadjust_table[row++][2], "Reset Value", TABLE_MAX_ELT_LEN);

	ret = mem_read(OMAP4430_CONTROL_CORE_HWOBS_CONTROL, &reg_val);

#ifdef HWOBS44XX_DEBUG
	reg_val = 0x7FEF9;
#endif

	strncpy(autoadjust_table[row][0], "Observable Signals Gating",
		TABLE_MAX_ELT_LEN);
	if (((reg_val) & 0x1) == 0x0) {
		strncpy(autoadjust_table[row][1], "GATED", TABLE_MAX_ELT_LEN);
	} else {
		if (((reg_val) & 0x4) ==
			0x4) {
			strncpy(autoadjust_table[row][1], "FORCED ZERO",
				TABLE_MAX_ELT_LEN);
		} else if (((reg_val) & 0x2) ==
			0x2) {
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
	if (((reg_val) & 0x100) ==
		0x100) {
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
	snprintf(autoadjust_table[row][1], TABLE_MAX_ELT_LEN, "0x%02X",
		((reg_val) & 0xF8) >> 3);
	snprintf(autoadjust_table[row++][2], TABLE_MAX_ELT_LEN, "0x%02X", 0);
	strncpy(autoadjust_table[row][0], "    po_hwobs(1)", TABLE_MAX_ELT_LEN);
	snprintf(autoadjust_table[row][1], TABLE_MAX_ELT_LEN, "0x%02X",
		((reg_val) & 0x3E00) >> 9);
	snprintf(autoadjust_table[row++][2], TABLE_MAX_ELT_LEN, "0x%02X", 0);
	strncpy(autoadjust_table[row][0], "    po_hwobs(2)", TABLE_MAX_ELT_LEN);
	snprintf(autoadjust_table[row][1], TABLE_MAX_ELT_LEN, "0x%02X",
		((reg_val) & 0x7C000) >> 14);
	snprintf(autoadjust_table[row++][2], TABLE_MAX_ELT_LEN, "0x%02X", 0);

	autoadjust_table_print(autoadjust_table, row, 3);

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs44xx_test
 * @BRIEF		test HWOBS setup by using tie-low / tie-high feature
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 * @param[in]		level: == "low" to tie signals low,
 *			== "high" to tie signal high.
 * @DESCRIPTION		test HWOBS setup by using tie-low / tie-high feature
 *//*------------------------------------------------------------------------ */
int hwobs44xx_test(char *level)
{
	unsigned int ret = 0;
	int err = 0;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	hwobs44xx_regtable_init();

	if (hwobs44xx_pinmux_check(OMAP4430_HWOBS_PAD_FULL_CHECK) == 0) {
		if (strcmp(level, "zero") == 0) {
			/* write register mux tied low value */
			ret = mem_write(OMAP4430_CONTROL_CORE_HWOBS_CONTROL, 0xD);
			if (ret != 0) {
				fprintf(stderr, "omapconf: write error! (addr=0x%08X, err=%d)\n",
					OMAP4430_CONTROL_CORE_HWOBS_CONTROL, ret);
				err = OMAPCONF_ERR_REG_ACCESS;
			} else {
				printf("OK: All HWOBS signals should now be tied low (forced to '0')\n");
				printf("\n");
				printf("Note: If observations are NOT aligned, then there is probably an issue\n");
				printf("with observability HW (device, connector): modify your HW setup.\n");
				printf("\n");
			}
		} else if (strcmp(level, "one") == 0) {
			/* write register mux tied high value */
			ret = mem_write(OMAP4430_CONTROL_CORE_HWOBS_CONTROL, 0xB);
			if (ret != 0) {
				fprintf(stderr, "omapconf: write error! (addr=0x%08X, err=%d)\n",
					OMAP4430_CONTROL_CORE_HWOBS_CONTROL, ret);
				err = OMAPCONF_ERR_REG_ACCESS;
			} else {
				printf("OK: All HWOBS signals should now be tied high (forced to '1')\n");
				printf("\n");
				printf("Note: If observations are NOT aligned, then there is probably an issue\n");
				printf("with observability HW (device, connector): modify your HW setup.\n");
				printf("\n");
			}
		} else {
			goto hwobs44xx_test_err;
		}
	} else {
		ret = hwobs44xx_pads_config_show();
		printf("omapconf: all pinmux should be configured before "
			"testing setup!\n\n");
		err = OMAPCONF_ERR_INTERNAL;
	}

	hwobs44xx_ctrl_cfg_show();
	return err;

hwobs44xx_test_err:
	autoadjust_table_init(table);

	row = 0;
	autoadjust_table_strncpy(table, row, 0, "Category");
	autoadjust_table_strncpy(table, row, 1, "Command (## OMAP4-ONLY ##)");
	autoadjust_table_strncpy(table, row, 2, "Description & Options");
	row++;
	autoadjust_table_strncpy(table, row, 0,	"Arguments for HWOBS test:");
	row++;

	autoadjust_table_strncpy(table, row, 1, "omapconf hwobs test zero");
	autoadjust_table_strncpy(table, row, 2,
		"hw observability ports are all tied low '0'.");
	row++;
	autoadjust_table_strncpy(table, row, 1,	"omapconf hwobs test one");
	autoadjust_table_strncpy(table, row, 2,
		"hw observability ports are all tied high '1'.");
	row += 2;
	autoadjust_table_strncpy(table, row, 1,	"omapconf hwobs test enable");
	autoadjust_table_strncpy(table, row, 2,
		"Enable signals through hwobs main mux:");
	row++;
	autoadjust_table_strncpy(table, row, 2,
		"  not tied low/high, not gated.");
	row += 2;

	autoadjust_table_print(table, row, 3);
	return OMAPCONF_ERR_ARG;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs44xx_setup_enable
 * @BRIEF		Enable HWOBS signals at hwobs ctrl mux level
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		Enable HWOBS signals at hwobs ctrl mux level
 *//*------------------------------------------------------------------------ */
int hwobs44xx_setup_enable(void)
{
	unsigned int ret = 0;
	int err = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	hwobs44xx_regtable_init();

	if (hwobs44xx_pinmux_check(OMAP4430_HWOBS_PAD_FULL_CHECK) == 0) {
		/* write register mux enable value */
		ret = mem_write(OMAP4430_CONTROL_CORE_HWOBS_CONTROL, 0x9);
		if (ret != 0) {
			fprintf(stderr, "omapconf: write error! "
				"(addr=0x%08X, err=%d)\n",
				OMAP4430_CONTROL_CORE_HWOBS_CONTROL, ret);
			err = OMAPCONF_ERR_REG_ACCESS;
		} else {
			printf("OK: hwobs ctrl mux is now configured to output "
				"debug signals "
				"(not tied low/high, not gated)\n\n");
		}
	} else {
		ret = hwobs44xx_pads_config_show();
		printf("omapconf: all pinmux should be configured before "
			"enabling setup.\n\n");
		err = OMAPCONF_ERR_INTERNAL;
	}

	hwobs44xx_ctrl_cfg_show();
	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs44xx_signals_show
 * @BRIEF		Print current OMAP4 Mux Configuration.
 *			Print list of selected debug signals
 *			for each hw_dbg[0:31] debug pin.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		Print current OMAP4 Mux Configuration.
 *			Print list of selected debug signals
 *			for each hw_dbg[0:31] debug pin.
 *//*------------------------------------------------------------------------ */
int hwobs44xx_signals_show(void)
{
	unsigned int pad_check = 0, ret = 0, i = 0;
	int err = 0;

	unsigned int hwobs_mux, hwobs_mux_bit, debug_mux, final_mux, final_mux_bit;
	char str_final_mux[OMAPCONF_REG_NAME_MAX_LENGTH + 1] = "";
	char str_debug_mux[OMAPCONF_REG_NAME_MAX_LENGTH + 1] = "";
	char str_hwobs_sig[OMAPCONF_REG_NAME_MAX_LENGTH + 1] = "";
	char str_hwobs_bit[OMAPCONF_REG_NAME_MAX_LENGTH + 1] = "";
	char str_buf[OMAPCONF_REG_NAME_MAX_LENGTH + 1] = "";

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);;

	hwobs44xx_regtable_init();

	pad_check = hwobs44xx_pinmux_check(OMAP4430_HWOBS_PAD_FULL_CHECK);

	hwobs44xx_ctrl_cfg_show();
	hwobs44xx_gating_check();

	if (pad_check != OMAP4430_HWOBS_MAX_NBR) {
		pad_check = 0;

		ret = mem_read(OMAP4430_CONTROL_CORE_DEBOBS_FINAL_MUX_SEL, &final_mux);
		if (ret != 0) {
			fprintf(stderr, "omapconf: internal error (failed to read)!\n");
			return OMAPCONF_ERR_REG_ACCESS;
		}

		printf("|-------------------------------------------------------------------------|\n");
		printf("| %-3s | %-16s | %-10s | %-10s | %-21s |\n",
			"bit", "pin mux", "final mux", "debug mux", "hwobs debug signal");
		printf("|-------------------------------------------------------------------------|\n");


		while (strcmp(omap4430_hwobs_names[i], "END") != 0) {
			pad_check = hwobs44xx_pinmux_check(i);

			final_mux_bit = ((final_mux & (1 << i)) >> i);
			strcpy(str_final_mux, debobs_final_mux_sel_names[final_mux_bit]);
			strcpy(str_hwobs_sig, "");
			strcpy(str_hwobs_bit, "");

			if (final_mux_bit) {
				ret = mem_read(hwobs_core_debug_mux_table[i].addr, &debug_mux);
				debug_mux &= 0xF;
				strcpy(str_debug_mux, ctrl_core_conf_debug_sel_tst_names[debug_mux]);

				switch (debug_mux) {
				case 0x0:
					ret = mem_read(OMAP4430_CONTROL_CORE_DEBOBS_MMR_MPU, &hwobs_mux);
					break;

				case 0x5:
					ret = mem_read(OMAP4430_CM_CM2_DEBUG_CFG, &hwobs_mux);
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
				ret = mem_read(hwobs_wkup_debug_mux_table[i].addr, &debug_mux);
				debug_mux &= 0xF;
				strcpy(str_debug_mux, ctrl_wkup_conf_debug_sel_tst_names[debug_mux]);

				switch (debug_mux) {
				case 0x0:
					ret = mem_read(OMAP4430_PM_PRM_DEBUG_CFG,
						&hwobs_mux);
					break;

				case 0x1:
					ret = mem_read(OMAP4430_CM_CM1_DEBUG_CFG,
						&hwobs_mux);
					break;

				default:
					strcat(str_hwobs_sig, "???????????");
					strcat(str_hwobs_bit, "???????");
					break;
				}
			}

			/* PRCM signals formating */
			if (((final_mux_bit == 1) && (debug_mux == 0x5)) ||
				((final_mux_bit == 0) && (debug_mux == 0x0)) ||
				((final_mux_bit == 0) && (debug_mux == 0x1))) {
				strcat(str_hwobs_sig, "block: 0x");
				hwobs_mux = ((hwobs_mux & ~(char_mask[(i / 8)])) >> ((i / 8) * 8));
				sprintf(str_buf, "%x", hwobs_mux);
				strcat(str_hwobs_sig, str_buf);

				strcat(str_hwobs_bit, "bit: ");
				hwobs_mux_bit = (i % 8);
				sprintf(str_buf, "%u", hwobs_mux_bit);
				strcat(str_hwobs_bit, str_buf);
			/* MPUSS signals formating */
			} else if ((final_mux_bit == 1) && (debug_mux == 0x0)) {
				strcat(str_hwobs_sig, "mode : ");
				sprintf(str_buf, "%u", hwobs_mux);
				strcat(str_hwobs_sig, str_buf);

				strcat(str_hwobs_bit, "bit: ");
				sprintf(str_buf, "%u", i);
				strcat(str_hwobs_bit, str_buf);
			/* ABE SS signals formating */
			} else if ((final_mux_bit == 1) && (debug_mux == 0x8)) {
				if ((i >= OMAP4430_HWOBS_ABE_UNRESERVED_FIRST) && (i <= OMAP4430_HWOBS_ABE_UNRESERVED_LAST))
					strcat(str_hwobs_sig, "mode : n/a");
				else
					strcat(str_hwobs_sig, "reserved");

				strcat(str_hwobs_bit, "bit: ");
				sprintf(str_buf, "%u", i);
				strcat(str_hwobs_bit, str_buf);
			}

			/* display register pad name, addr & content (hex) */
			if (pad_check == 0)
				printf("| %-3d | %-16s | %-10s | %-10s | %-11s | %-7s |\n", i,
						omap4430_hwobs_names[i], str_final_mux, str_debug_mux, str_hwobs_sig, str_hwobs_bit);
			else
				printf("| %-3d | %-16s | %-10s | %-10s | %-11s | %-7s |\n", i,
						"not configured", str_final_mux, str_debug_mux, "???????????", "??????");

			if (i == 19)
				printf("|-------------------------------------------------------------------------|\n");

			i++;
		}

		printf("|-------------------------------------------------------------------------|\n");
	}

	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs44xx_pads_setup
 * @BRIEF		Change OMAP4 pinmux to drive HWOBS signals on
 *			external pads.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		Change OMAP4 pinmux to drive HWOBS signals on
 *			external pads.
 *//*------------------------------------------------------------------------ */
int hwobs44xx_pads_setup(void)
{
	unsigned int ret, i = 0;
	int err = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	hwobs44xx_regtable_init();

	while (strcmp(hwobs_pad_reg_table[i].name, "END") != 0) {
		/* write register pad value */
		ret = hwobs44xx_padreg_write(hwobs_pad_reg_table[i].addr, 0x0006);
		if (ret != 0) {
			fprintf(stderr, "omapconf: write error! (addr=0x%08X, err=%d)\n",
				(unsigned int)(hwobs_pad_reg_table[i].addr), ret);
			err = OMAPCONF_ERR_REG_ACCESS;
		}
		i++;
	}

	if (err == OMAPCONF_ERR_REG_ACCESS) {
		printf("Error: Pinmux configuration failed!\n");
		printf("\n");
	} else {
		printf("OK: Pinmux are now configured to drive HWOBS signals on external pads:\n");
		printf("\n");
	}

	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs44xx_prcm_setup
 * @BRIEF		Setup OMAP4 HWOBS Mux Configuration: allow selection of
 *			desired PRCM debug signals. Implicitly configure HWOBS
 *			muxes.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 * @param[in]		pos_s: block (8 bits) positon whithin 32 bits of
 *			observability
 * @param[in]		type_s: PRCM signals debug mux category
 * @param[in]		num_s: block number whithin selected signals category
 * @DESCRIPTION		Setup OMAP4 HWOBS Mux Configuration: allow selection of
 *			desired PRCM debug signals. Implicitly configure HWOBS
 *			muxes.
 *//*------------------------------------------------------------------------ */
int hwobs44xx_prcm_setup(char *pos_s, char *type_s, char *num_s)
{
	unsigned int ret, i = 0;
	unsigned int debug_mux, final_mux;
	unsigned int pos, num;

	int err = 0;
	char cat[OMAPCONF_REG_NAME_MAX_LENGTH + 1] = "";

	#ifdef HWOBS44XX_DEBUG
	unsigned int reg_val;
	#endif

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	if ((pos_s == NULL) || (type_s == NULL) || (num_s == NULL))
		goto hwobs44xx_prcm_setup_end;

	hwobs44xx_regtable_init();

	type_s = uppercase(type_s);
	num_s = uppercase(num_s);

	dprintf("%s(): pos_s=%s\n", __func__, pos_s);
	dprintf("%s(): type_s=%s\n", __func__, type_s);
	dprintf("%s(): num_s=%s\n", __func__, num_s);

	/* Retrieve and check block position */
	ret = sscanf(pos_s, "%u", &pos);
	if (ret != 1) {
		dprintf("%s(): could not retrieve block position\n", __func__);
		goto hwobs44xx_prcm_setup_end;
	}
	if (pos > 3) {
		printf("Invalid block position! (%s)\n\n", pos_s);
		goto hwobs44xx_prcm_setup_end;
	}

	/* Retrieve and check signals block category */
	if (isalpha(type_s[0])) {
		ret = sscanf(type_s, "%50s", (char *) cat);
		if (ret != 1) {
			dprintf("%s(): could not retrieve category string\n",
				__func__);
			goto hwobs44xx_prcm_setup_end;
		}
	} else {
		goto hwobs44xx_prcm_setup_end;
	}

	if ((strcmp(cat, ctrl_wkup_conf_debug_sel_tst_names[0]) != 0) &&
		(strcmp(cat, ctrl_wkup_conf_debug_sel_tst_names[1]) != 0) &&
		(strcmp(cat, ctrl_core_conf_debug_sel_tst_names[5]) != 0)) {
		printf("Invalid PRCM signals category! (%s)\n\n", type_s);
		goto hwobs44xx_prcm_setup_end;
	}

	/* Retrieve and check block number (hex) */
	if ((num_s[0] == '0') && (num_s[1] == 'X')) {
		/* Hexdecimal value must start with "0x" */
		ret = sscanf(num_s, "0X%x", &num);
		if (ret != 1) {
			printf("Invalid block number! (%s)\n\n", num_s);
			goto hwobs44xx_prcm_setup_end;
		}
	} else {
		printf("Invalid block number format! (%s)\n\n", num_s);
		goto hwobs44xx_prcm_setup_end;
	}

	dprintf("%s(): pos=%d\n", __func__, pos);
	dprintf("%s(): cat=%s\n", __func__, cat);
	dprintf("%s(): num=0x%x\n", __func__, num);

	if (strcmp(cat, ctrl_core_conf_debug_sel_tst_names[5]) == 0) {
		/* CORE - CM2 */
		final_mux = 0xFF;
		debug_mux = 0x5;
		ret = hwobs44xx_blkmuxreg_modify(OMAP4430_CM_CM2_DEBUG_CFG, pos, num);

		for (i = (pos * 8); i <= (pos * 8) + 7; i++) {
			ret = mem_write(hwobs_core_debug_mux_table[i].addr,
				debug_mux);
			#ifdef HWOBS44XX_DEBUG
			mem_read(hwobs_core_debug_mux_table[i].addr, &reg_val);
			printf("%s(): core_conf_debug_mux_id%d addr: "
				"0x%08x val: 0x%08x\n", __func__,
				i, hwobs_core_debug_mux_table[i].addr, reg_val);
			#endif
		}
	} else {
		final_mux = 0x00;

		/* WKUP - PRM */
		if (strcmp(cat, ctrl_wkup_conf_debug_sel_tst_names[0]) == 0) {
			debug_mux = 0x0;
			ret = hwobs44xx_blkmuxreg_modify(OMAP4430_PM_PRM_DEBUG_CFG,
				pos, num);

		/* WKUP - CM1 */
		} else {
			debug_mux = 0x1;
			ret = hwobs44xx_blkmuxreg_modify(OMAP4430_CM_CM1_DEBUG_CFG,
				pos, num);
		}

		for (i = (pos * 8); i <= (pos * 8) + 7; i++) {
			ret = mem_write(hwobs_wkup_debug_mux_table[i].addr,
				debug_mux);
			#ifdef HWOBS44XX_DEBUG
			mem_read(hwobs_wkup_debug_mux_table[i].addr, &reg_val);
			printf("%s(): wkup_conf_debug_mux_id%d addr: "
				"0x%08x val: 0x%08x\n", __func__, i,
				hwobs_wkup_debug_mux_table[i].addr, reg_val);
			#endif
		}
	}

	hwobs44xx_blkmuxreg_modify(OMAP4430_CONTROL_CORE_DEBOBS_FINAL_MUX_SEL,
		pos, final_mux);
	hwobs44xx_signals_show();

	return err;

hwobs44xx_prcm_setup_end:
	printf("SYNOPSIS:\n");
	printf("\n");
	printf("  omapconf hwobs setup prcm <pos> <type> <num>\n");
	printf("\n");
	printf("DESCRIPTION:\n");
	printf("\n");
	printf("  This hwobs setup command allows to control HWOBS mux configuration to select PRCM debug signals.\n");
	printf("  PRCM signals are split in 3 debug mux categories (CM1, CM2 and PRM) which are organized in 'blocks' of 8 debug signals.\n");
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
	printf(" <cat> select PRCM signals debug mux category: CM1, CM2 or PRM\n");
	printf("\n");
	printf("  CM1 -> map selected <pos> hw_dbg bits to CM1 category of hwobs signals\n");
	printf("  CM2 -> map selected <pos> hw_dbg bits to CM2 category of hwobs signals\n");
	printf("  PRM -> map selected <pos> hw_dbg bits to PRM category of hwobs signals\n");
	printf("\n");
	printf(" <num> block number whithin selected signals category (value in hexa-decimal)\n");
	printf("\n");
	printf("  0x? -> map <num> block from <cat> onto selected <pos> hw_dbg bits\n");
	printf("\n");
	printf("EXAMPLES:\n");
	printf("\n");
	printf("- Configure hw_dbg[00:07] bits with block 0x22 from CM1\n");
	printf("     omapconf hwobs setup prcm 0 CM1 0x22\n");
	printf("\n");
	printf("- Configure hw_dbg[16:23] bits with block 0x01 from PRM\n");
	printf("     omapconf hwobs setup prcm 2 PRM 0x01\n");
	printf("\n");
	printf("TIPS:\n");
	printf("\n");
	printf("  If you need to stick to the same observability settings following platform reboot, you can\n");
	printf("  create a shell script calling omapconf commands to keep your observability setup up-to-date.\n");
	printf("\n");
	return OMAPCONF_ERR_ARG;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs44xx_mpuss_setup
 * @BRIEF		Setup OMAP4 HWOBS Mux Configuration: allow selection of
 *			desired MPUSS debug signals. Implicitly configure
 *			HWOBS muxes.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		Setup OMAP4 HWOBS Mux Configuration: allow selection of
 *			desired MPUSS debug signals. Implicitly configure
 *			HWOBS muxes.
 *//*------------------------------------------------------------------------ */
int hwobs44xx_mpuss_setup(char *mode_s)
{
	unsigned int ret, i = 0;
	unsigned int debug_mux, final_mux;
	unsigned int mode;

	int err = 0;

	#ifdef HWOBS44XX_DEBUG
	unsigned int reg_val;
	#endif

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	hwobs44xx_regtable_init();

	/* Retrieve and check mpuss mux mode */
	if (mode_s == NULL)
		goto hwobs44xx_mpuss_setup_err;
	mode_s = uppercase(mode_s);
	dprintf("%s(): mode_s=%s\n", __func__, mode_s);
	ret = sscanf(mode_s, "%u", &mode);
	if (ret != 1) {
		dprintf("%s(): could not retrieve mpuss mux mode\n", __func__);
		goto hwobs44xx_mpuss_setup_err;
	}
	if (mode > 7) {
		printf("Invalid mpuss mux mode! (%s)\n\n", mode_s);
		goto hwobs44xx_mpuss_setup_err;
	}
	dprintf("%s(): mode=%d\n", __func__, mode);

	/* CORE - MPUSS */
	final_mux = 0xFFFFFFFF;
	debug_mux = 0x0;

	ret = mem_write(OMAP4430_CONTROL_CORE_DEBOBS_MMR_MPU, mode);

	for (i = 0; i < OMAP4430_HWOBS_MAX_NBR; i++) {
		ret = mem_write(hwobs_core_debug_mux_table[i].addr, debug_mux);
		#ifdef HWOBS44XX_DEBUG
		mem_read(hwobs_core_debug_mux_table[i].addr, &reg_val);
		printf("%s(): core_conf_debug_mux_id%d addr: "
			"0x%08x val: 0x%08x\n", __func__, i,
			hwobs_core_debug_mux_table[i].addr, reg_val);
		#endif
	}

	ret = mem_write(OMAP4430_CONTROL_CORE_DEBOBS_FINAL_MUX_SEL, final_mux);
	hwobs44xx_signals_show();

	return err;

hwobs44xx_mpuss_setup_err:
	printf("SYNOPSIS:\n");
	printf("\n");
	printf("  omapconf hwobs setup mpuss <mode>\n");
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
	printf("     omapconf hwobs setup mpuss 2\n");
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
	return OMAPCONF_ERR_ARG;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs44xx_abe_setup
 * @BRIEF		Setup OMAP4 HWOBS Mux Configuration: allow selection of
 *			desired ABE debug signals. Implicitly configure
 *			HWOBS muxes.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		Setup OMAP4 HWOBS Mux Configuration: allow selection of
 *			desired ABE debug signals. Implicitly configure
 *			HWOBS muxes.
 *//*------------------------------------------------------------------------ */
int hwobs44xx_abe_setup(char *enable)
{
	unsigned int i = 0;
	unsigned int debug_mux, final_mux;
	int err = 0;

	#ifdef HWOBS44XX_DEBUG
	unsigned int reg_val;
	#endif

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	hwobs44xx_regtable_init();

	/* Retrieve and check abe enable value */
	if (enable == NULL)
		goto hwobs44xx_abe_setup_err;
	enable = lowercase(enable);
	dprintf("%s(): enable=%s\n", __func__, enable);
	if ((strcmp(enable, "on") != 0) &&
		(strcmp(enable, "reserved") != 0)) {
		printf("Invalid abe enable option! (%s)\n\n", enable);
		goto hwobs44xx_abe_setup_err;
	}

	/* CORE - ABE */
	debug_mux = 0x08;

	if (strcmp(enable, "on") == 0) {
		mem_read(OMAP4430_CONTROL_CORE_DEBOBS_FINAL_MUX_SEL, &final_mux);
		final_mux |= OMAP4430_HWOBS_ABE_UNRESERVED_MASK;

		for (i = OMAP4430_HWOBS_ABE_UNRESERVED_FIRST;
			i <= OMAP4430_HWOBS_ABE_UNRESERVED_LAST; i++) {
			mem_write(hwobs_core_debug_mux_table[i].addr,
				debug_mux);
			#ifdef HWOBS44XX_DEBUG
			mem_read(hwobs_core_debug_mux_table[i].addr, &reg_val);
			printf("%s(): core_conf_debug_mux_id%d addr: "
				"0x%08x val: 0x%08x\n", __func__, i,
				hwobs_core_debug_mux_table[i].addr, reg_val);
			#endif
		}
	} else if (strcmp(enable, "reserved") == 0) {
		final_mux = 0xFFFFFFFF;

		for (i = 0; i < OMAP4430_HWOBS_MAX_NBR; i++) {
			mem_write(hwobs_core_debug_mux_table[i].addr,
				debug_mux);
			#ifdef HWOBS44XX_DEBUG
			mem_read(hwobs_core_debug_mux_table[i].addr, &reg_val);
			printf("%s(): core_conf_debug_mux_id%d addr: "
				"0x%08x val: 0x%08x\n", __func__, i,
				hwobs_core_debug_mux_table[i].addr, reg_val);
			#endif
		}
	} else {
		goto hwobs44xx_abe_setup_err;
	}

	mem_write(OMAP4430_CONTROL_CORE_DEBOBS_FINAL_MUX_SEL, final_mux);
	hwobs44xx_signals_show();

	return err;

hwobs44xx_abe_setup_err:
	printf("SYNOPSIS:\n");
	printf("\n");
	printf("  omapconf hwobs setup abe [on | reserved]\n");
	printf("\n");
	printf("DESCRIPTION:\n");
	printf("\n");
	printf("  This hwobs setup command allows to control HWOBS mux configuration to select ABE debug signals.\n");
	printf("  No observability signals multiplexing is implemented at ABE subsystem level. Each ABE SS signal is mapped\n");
	printf("  on a single HWOBS pin or hw_dbg bit. User should refer to TRM documentation detailing ABE SS debug signals.\n");
	printf("\n");
	printf("USAGE:\n");
	printf("\n");
	printf("- Configure hw_dbg[17:25] bits from ABE (other bits are reserved, hence not configured)\n");
	printf("     omapconf hwobs setup abe on\n");
	printf("\n");
	printf("- Configure hw_dbg[00:31] bits from ABE (force configuration of reserved bits as well)\n");
	printf("     omapconf hwobs setup abe reserved\n");
	printf("\n");
	printf("TIPS:\n");
	printf("\n");
	printf("  If you need to stick to the same observability settings following platform reboot, you can\n");
	printf("  create a shell script calling omapconf commands to keep your observability setup up-to-date.\n");
	printf("\n");
	return OMAPCONF_ERR_ARG;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs44xx_pads_config_show
 * @BRIEF		Dump OMAP4 HW Observability PADCONFs regs.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		Dump OMAP4 HW Observability PADCONFs regs.
 *//*------------------------------------------------------------------------ */
int hwobs44xx_pads_config_show(void)
{
	unsigned int ret, i = 0;
	unsigned short pad_val;
	int err = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	hwobs44xx_regtable_init();

	printf("|----------------------------------------------------------|\n");
	printf("| %-3s | %-25s | %-10s | %-9s |\n",
		"bit", "16 bits pad. reg.", "pad. addr", "pad. val.");
	printf("|----------------------------------------------------------|\n");

	while (strcmp(hwobs_pad_reg_table[i].name, "END") != 0) {
		/* display register pad name, addr & content (hex) */
		ret = hwobs44xx_padreg_read(hwobs_pad_reg_table[i].addr, &pad_val);
		if (ret == 0)
			printf("| %-3d | %-25s | 0x%08X |  0x%04X   |\n",
				i, hwobs_pad_reg_table[i].name,
				(unsigned int)(hwobs_pad_reg_table[i].addr),
				pad_val);
		else {
			fprintf(stderr,
				"omapconf: read error! (addr=0x%08X, err=%d)\n",
				(unsigned int)(hwobs_pad_reg_table[i].addr),
				ret);
			err = OMAPCONF_ERR_REG_ACCESS;
		}

		if (i == 19)
			printf("|----------------------------------------------------------|\n");
		i++;
	}

	printf("|----------------------------------------------------------|\n\n");

	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs44xx_setup_help
 * @BRIEF		display list of supported commands
 * @DESCRIPTION		display list of supported commands
 *//*------------------------------------------------------------------------ */
static void hwobs44xx_setup_help(void)
{
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row;

	autoadjust_table_init(table);

	row = 0;
	autoadjust_table_strncpy(table, row, 0, "Category");
	autoadjust_table_strncpy(table, row, 1, "Command (## OMAP4-ONLY ##)");
	autoadjust_table_strncpy(table, row, 2, "Description & Options");
	row++;
	autoadjust_table_strncpy(table, row, 0,	"Arguments for HWOBS setup:");
	row++;

	autoadjust_table_strncpy(table, row, 1, "omapconf hwobs setup pinmux");
	autoadjust_table_strncpy(table, row, 2,
		"Change pinmux to drive HWOBS signals on external pads.");
	row += 2;
	autoadjust_table_strncpy(table, row, 1,
		"omapconf hwobs setup prcm [pos][type][num]");
	autoadjust_table_strncpy(table, row, 2,
		"Select desired HWOBS PRCM 'block' Signals.");
	row++;
	autoadjust_table_strncpy(table, row, 1,
		"omapconf hwobs setup mpuss [mode]");
	autoadjust_table_strncpy(table, row, 2,
		"Select desired MPUSS mux mode and Signals.");
	row++;
	autoadjust_table_strncpy(table, row, 1,
		"omapconf hwobs setup abe [on | reserved]");
	autoadjust_table_strncpy(table, row, 2,
		"Select desired ABE SS mux mode and Signals.");
	row += 2;

	autoadjust_table_print(table, row, 3);
}


int hwobs44xx_config_show(void)
{
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	ret = hwobs44xx_regtable_init();
	ret |= hwobs44xx_pads_config_show();
	ret |= hwobs44xx_signals_show();

	return ret;
}


int hwobs44xx_pinmux_setup(void)
{
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	ret = hwobs44xx_regtable_init();
	ret |= hwobs44xx_pads_setup();
	ret |= hwobs44xx_pads_config_show();

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwobs44xx_main
 * @BRIEF		main entry point for omap4 hwobs
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		main entry point for omap4 hwobs
 *//*------------------------------------------------------------------------ */
int hwobs44xx_main(int argc, char *argv[])
{
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (argc >= 2) {
		hwobs44xx_regtable_init();
		/* HWOBS Setup Menu */
		if (strcmp(argv[1], "setup") == 0) {
			if ((argc == 3) &&
				(strcmp(argv[2], "pinmux") == 0)) {
				/* Setup HWOBS Pinmux */
				ret = hwobs44xx_pads_setup();
			} else if ((argc == 6) &&
				(strcmp(argv[2], "prcm") == 0)) {
				/* Setup HWOBS PRCM Debug Signals */
				ret = hwobs44xx_prcm_setup(
						argv[3], argv[4], argv[5]);
			} else if ((argc == 4) &&
				(strcmp(argv[2], "mpuss") == 0)) {
				/* Setup HWOBS MPUSS Debug Signals */
				ret = hwobs44xx_mpuss_setup(argv[3]);
			} else if ((argc == 4) &&
				(strcmp(argv[2], "abe") == 0)) {
				/* Setup HWOBS ABE Debug Signals */
				ret = hwobs44xx_abe_setup(argv[3]);
			} else {
				/* Setup Menu Help */
				hwobs44xx_setup_help();
				ret = OMAPCONF_ERR_ARG;
			}
		} else if (strcmp(argv[1], "test") == 0) {
			if (argc == 3) {
				if (strcmp(argv[2], "enable") == 0)
					ret = hwobs44xx_setup_enable();
				else
					ret = hwobs44xx_test(argv[2]);
			} else {
				/* Setup Menu Help */
				hwobs44xx_setup_help();
				ret = OMAPCONF_ERR_ARG;
			}
		} else if (strcmp(argv[1], "cfg") == 0) {
			/* HWOBS Display Current config */
			ret = hwobs44xx_pads_config_show();
			ret |= hwobs44xx_signals_show();
		} else {
			/* HWOBS Help */
			help(HELP_HWOBS);
			ret = OMAPCONF_ERR_ARG;
		}
	} else {
		/* HWOBS Help */
		help(HELP_HWOBS);
		ret = OMAPCONF_ERR_ARG;
	}

	return ret;
}
