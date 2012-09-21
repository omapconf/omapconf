/*
 *
 * @Component			OMAPCONF
 * @Filename			hwobs54xx.h
 * @Description			OMAP5 PRM Registers Functions
 * @Author			Cedric Vamour (c-vamour@ti.com)
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


#ifndef __HWOBS54XX_H__
#define __HWOBS54XX_H__


#include <hwobs44xx.h>
#include <prcm-common.h>


#define HWOBS54XX_SIG_MAX_NBR		32
#define HWOBS54XX_PAD_MAX_NBR		16
#define HWOBS54XX_MUX_FINAL_MAX		0x3
#define HWOBS54XX_MUX_WKUP_MAX		0x3
#define HWOBS54XX_MUX_CORE_MAX		0x1F

#define HWOBS54XX_NAME_LENGTH		16
#define HWOBS54XX_PAD_NAME_LENGTH	25
#define HWOBS54XX_MUX_NAME_LENGTH	10
#define HWOBS54XX_PAD_FULL_CHECK	255


int hwobs54xx_display_pads(pad_cell pad_reg_table[HWOBS54XX_PAD_MAX_NBR + 1]);
int hwobs54xx_display_signals(void);
int hwobs54xx_display_hwobs_ctrl_cfg(void);
int hwobs54xx_display_cfg(void);
int hwobs54xx_test(char *level);
int hwobs54xx_pinmux_setup(char *padset);
int hwobs54xx_prcm_setup(char *pos_s, char *cat_s, char *num_s);
int hwobs54xx_mpuss_setup(char *mode_s);
int hwobs54xx_enable(void);


/* DEPRECATED, DO NOT USE ANYMORE */
int hwobs54xx_main(int argc, char *argv[]);


typedef enum {
	HWOBS54XX_WKUP_CTRL_SYS_PADS,
	HWOBS54XX_CORE_CTRL_C2C_PADS,
	HWOBS54XX_CORE_CTRL_PER_PADS,
	HWOBS54XX_PADSET_SELECT_MAX_ID
} hwobs54xx_padset_select_id;

static const char hwobs54xx_padset_names
	[HWOBS54XX_PADSET_SELECT_MAX_ID+1][HWOBS54XX_NAME_LENGTH] = {
	"WKUP",
	"CORE_C2C",
	"CORE_PER",
	"ALL"};


/* OMAP54XX_CTRL_MODULE_PADCONFS: HWOBS signal names */
static const char hwobs54xx_signal_names[HWOBS54XX_SIG_MAX_NBR+1][HWOBS54XX_NAME_LENGTH] = {
	"hw_wkdbg0",
	"hw_wkdbg1",
	"hw_wkdbg2",
	"hw_wkdbg3",
	"hw_wkdbg4",
	"hw_wkdbg5",
	"hw_wkdbg6",
	"hw_wkdbg7",
	"hw_wkdbg8",
	"hw_wkdbg9",
	"hw_wkdbg10",
	"hw_wkdbg11",
	"hw_wkdbg12",
	"hw_wkdbg13",
	"hw_wkdbg14",
	"hw_wkdbg15",
	"hw_dbg16",
	"hw_dbg17",
	"hw_dbg18",
	"hw_dbg19",
	"hw_dbg20",
	"hw_dbg21",
	"hw_dbg22",
	"hw_dbg23",
	"hw_dbg24",
	"hw_dbg25",
	"hw_dbg26",
	"hw_dbg27",
	"hw_dbg28",
	"hw_dbg29",
	"hw_dbg30",
	"hw_dbg31",
	"END"};

/* OMAP54XX_CONTROL_CORE_DEBOBS_FINAL_MUX_SEL: Names depending on bit values */
static const char hwobs54xx_debobs_final_mux_sel_names
	[HWOBS54XX_MUX_FINAL_MAX][HWOBS54XX_MUX_NAME_LENGTH] = {
	"WKUP",
	"CORE",
	"END"};

/* OMAP54XX_CONTROL_WKUP_CONF_DEBUG_SEL_TST_i: Names depending on bit values */
static const char hwobs54xx_ctrl_wkup_conf_debug_sel_tst_names
	[HWOBS54XX_MUX_WKUP_MAX][HWOBS54XX_MUX_NAME_LENGTH] = {
	"PRM",
	"CM1",
	"END"};

/* OMAP54XX_CONTROL_CORE_CONF_DEBUG_SEL_TST_i: Names depending on bit values */
static const char hwobs54xx_ctrl_core_conf_debug_sel_tst_names
	[HWOBS54XX_MUX_CORE_MAX][HWOBS54XX_MUX_NAME_LENGTH] = {
	"MPUSS",
	"Reserved", /* FIXME: some bits contain other debug signals */
	"Reserved",
	"ISS",
	"Reserved", /* FIXME: some bits contain DSP, ISS & DMM debug signals */
	"CM2",
	"IVAHD",
	"DSS",
	"ABE",
	"DSPSS",
	"USB",
	"Reserved", /* FIXME: some bits contain other debug signals */
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"END"};

/* Used by CONTROL_HWOBS_CONTROL */
#define OMAP5430_HWOBS_MACRO_ENABLE_SHIFT			0
#define OMAP5430_HWOBS_MACRO_ENABLE_MASK			BITFIELD(0, 0)

/* Used by CONTROL_HWOBS_CONTROL */
#define OMAP5430_HWOBS_ALL_ONE_MODE_SHIFT			1
#define OMAP5430_HWOBS_ALL_ONE_MODE_MASK			BITFIELD(1, 1)

/* Used by CONTROL_HWOBS_CONTROL */
#define OMAP5430_HWOBS_ALL_ZERO_MODE_SHIFT			2
#define OMAP5430_HWOBS_ALL_ZERO_MODE_MASK			BITFIELD(2, 2)

/* Used by CONTROL_HWOBS_CONTROL */
#define OMAP5430_HWOBS_CLKDIV_SEL_SHIFT				3
#define OMAP5430_HWOBS_CLKDIV_SEL_MASK				BITFIELD(3, 7)

/* Used by CONTROL_HWOBS_CONTROL */
#define OMAP5430_HWOBS_CLKOBS_GATE_ENABLE_SHIFT			8
#define OMAP5430_HWOBS_CLKOBS_GATE_ENABLE_MASK			BITFIELD(8, 8)

/* Used by CONTROL_HWOBS_CONTROL */
#define OMAP5430_HWOBS_CLKDIV_SEL_1_SHIFT			9
#define OMAP5430_HWOBS_CLKDIV_SEL_1_MASK			BITFIELD(9, 13)

/* Used by CONTROL_HWOBS_CONTROL */
#define OMAP5430_HWOBS_CLKDIV_SEL_2_SHIFT			14
#define OMAP5430_HWOBS_CLKDIV_SEL_2_MASK			BITFIELD(14, 18)


#endif
