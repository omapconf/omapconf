/*
 *
 * @Component			OMAPCONF
 * @Filename			hwobs44xx.h
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


#ifndef __HWOBS44XX_H__
#define __HWOBS44XX_H__


#define OMAP4430_HWOBS_MAX_NBR 32
#define OMAP4430_HWOBS_NAME_LENGTH 16
#define OMAP4430_HWOBS_PAD_NAME_LENGTH 25
#define OMAP4430_HWOBS_MUX_NAME_LENGTH 10
#define OMAP4430_HWOBS_PAD_FULL_CHECK 255

#define OMAP4430_HWOBS_ABE_UNRESERVED_FIRST 17
#define OMAP4430_HWOBS_ABE_UNRESERVED_LAST 25
#define OMAP4430_HWOBS_ABE_UNRESERVED_MASK 0x03FE0000


typedef struct {
	char name[OMAP4430_HWOBS_PAD_NAME_LENGTH];
	unsigned int addr;
	unsigned short val;
} pad_cell;

static const unsigned int char_mask[4] = {
	0xFFFFFF00,
	0xFFFF00FF,
	0xFF00FFFF,
	0x00FFFFFF };

/* OMAP4430_CONTROL_CORE_PADCONFS: HWOBS signal names */
static const char omap4430_hwobs_names[OMAP4430_HWOBS_MAX_NBR+1][OMAP4430_HWOBS_NAME_LENGTH] = {
	"attila_hw_dbg0",
	"attila_hw_dbg1",
	"attila_hw_dbg2",
	"attila_hw_dbg3",
	"attila_hw_dbg4",
	"attila_hw_dbg5",
	"attila_hw_dbg6",
	"attila_hw_dbg7",
	"attila_hw_dbg8",
	"attila_hw_dbg9",
	"attila_hw_dbg10",
	"attila_hw_dbg11",
	"attila_hw_dbg12",
	"attila_hw_dbg13",
	"attila_hw_dbg14",
	"attila_hw_dbg15",
	"attila_hw_dbg16",
	"attila_hw_dbg17",
	"attila_hw_dbg18",
	"attila_hw_dbg19",
	"attila_hw_dbg20",
	"attila_hw_dbg21",
	"attila_hw_dbg22",
	"attila_hw_dbg23",
	"attila_hw_dbg24",
	"attila_hw_dbg25",
	"attila_hw_dbg26",
	"attila_hw_dbg27",
	"attila_hw_dbg28",
	"attila_hw_dbg29",
	"attila_hw_dbg30",
	"attila_hw_dbg31",
	"END"};

/* OMAP4430_CONTROL_CORE_DEBOBS_FINAL_MUX_SEL: Names depending on bit values */
static const char debobs_final_mux_sel_names[3][OMAP4430_HWOBS_MUX_NAME_LENGTH] = {
	"WKUP",
	"CORE",
	"END"};

/* OMAP4430_CONTROL_WKUP_CONF_DEBUG_SEL_TST_i: Names depending on bit values */
static const char ctrl_wkup_conf_debug_sel_tst_names[3][OMAP4430_HWOBS_MUX_NAME_LENGTH] = {
	"PRM",
	"CM1",
	"END"};

/* OMAP4430_CONTROL_CORE_CONF_DEBUG_SEL_TST_i: Names depending on bit values */
static const char ctrl_core_conf_debug_sel_tst_names[15][OMAP4430_HWOBS_MUX_NAME_LENGTH] = {
	"MPUSS",
	"reserved", /* FIXME: some bits contain dplls, clocks or usbotg debug signals */
	"reserved", /* FIXME: some bits contain sdma or clocks debug signals */
	"reserved",
	"reserved", /* FIXME: some bits contain additional dspss debug signals */
	"CM2",
	"IVAHD",
	"reserved",
	"ABE",
	"DSPSS",
	"reserved",
	"reserved", /* FIXME: some bits contain dss debug signals */
	"reserved", /* FIXME: some bits contain additional dspss or sdma debug signals */
	"END"};


int hwobs44xx_padreg_read(unsigned int padreg_addr, unsigned short *pad_val);
int hwobs44xx_padreg_write(unsigned int padreg_addr, unsigned short pad_val);
int hwobs44xx_blkmuxreg_modify(unsigned int muxreg_addr, unsigned int block_pos, char mux_val);

int hwobs44xx_pinmux_setup(void);
int hwobs44xx_test(char *level);
int hwobs44xx_pads_setup(void);
int hwobs44xx_pads_config_show(void);

int hwobs44xx_prcm_setup(char *pos_s, char *type_s, char *num_s);
int hwobs44xx_abe_setup(char *enable);
int hwobs44xx_mpuss_setup(char *mode_s);
int hwobs44xx_setup_enable(void);
int hwobs44xx_config_show(void);

/* DEPRECATED, DO NOT USE ANYMORE */
int hwobs44xx_main(int argc, char *argv[]);


#endif
