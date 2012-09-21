/*
 *
 * @Component			OMAPCONF
 * @Filename			dpll44xx-data.h
 * @Description			OMAP4 DPLL Definitions
 * @Author			Patrick Titiano (p-titiano@ti.com)
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


#ifndef __DPLL44XX_DATA_H__
#define __DPLL44XX_DATA_H__


#include <dpll44xx.h>
#include <clock44xx.h>
#include <voltdm44xx.h>
#include <lib.h>


typedef struct {
	/* Common DPLL type A & B */
	dpll_status status;
	dpll_mode mode;
	dpll_autoidle_mode autoidle_mode;
	int lpmode;
	short regm4xen;
	int dcc_en;
	double dcc_count; /* in us, not relevant if dcc_en != 1 */
	int M;
	int N;
	double fdpll;
	int M2;
	double M2_clkout_rate;		/* in MHz */
	double X2_M2_clkdcoldo_rate;	/* in MHz */
	int M3;
	double X2_M3_rate;	/* in MHz */
	/* DPLL type A only: HS Dividers (M4 to M7) */
	short hsdiv_present[4];
	int hsdiv[4];
	double hsdiv_rate[4];		/* in MHz */
} dpll44xx_audit_settings;


typedef enum {
	DPLL44XX_CLKOUT_M2,
	DPLL44XX_CLKOUTX2_M2,
	DPLL44XX_CLKOUTX2_M3,
	DPLL44XX_CLKOUTX2_M4,
	DPLL44XX_CLKOUTX2_M5,
	DPLL44XX_CLKOUTX2_M6,
	DPLL44XX_CLKOUTX2_M7,
	DPLL44XX_CLK_DCO_LDO,
	DPLL44XX_OUTPUT_ID_MAX
} dpll44xx_output_id;


typedef struct {
	unsigned int cm_clksel_dpll;
	unsigned int cm_div_m2_dpll;
	unsigned int cm_div_m3_dpll;
} omap4_dpll_MN_params_regs;


typedef struct {
	unsigned int cm_clkmode_dpll;
	unsigned int cm_ssc_deltamstep_dpll;
} omap4_dpll_SSC_params_regs;


typedef struct {
	unsigned int cm_clkmode_dpll;
	unsigned int cm_idlest_dpll;
	unsigned int cm_autoidle_dpll;
	unsigned int cm_clksel_dpll;
	unsigned int cm_bypclk_dpll;
	unsigned int cm_div_m2_dpll;
	unsigned int cm_div_m3_dpll;
} omap4_dpll_params_regs;


typedef struct {
	clock44xx_id ref_clk;
	clock44xx_id byp_clk_m2;
	clock44xx_id byp_clk_m3;
	clock44xx_id byp_clk_mx;
} omap4_dpll_clock_sources;


extern const char dpll44xx_names[DPLL44XX_ID_MAX + 1][DPLL_MAX_NAME_LENGTH];

extern const char
	dpll44xx_output_names[DPLL44XX_OUTPUT_ID_MAX + 1][DPLL_OUTPUT_MAX_NAME_LENGTH];

extern const dpll44xx_audit_settings
	**dpll4470_golden_settings_38_4MHz[DPLL44XX_ID_MAX];
extern const dpll44xx_audit_settings
	**dpll4460_golden_settings_38_4MHz[DPLL44XX_ID_MAX];
extern const dpll44xx_audit_settings
	**dpll4430_golden_settings_38_4MHz[DPLL44XX_ID_MAX];

extern const omap4_dpll_MN_params_regs omap4_dpll_MN_regs[DPLL44XX_ID_MAX];

extern const unsigned int omap4_dpll_hs_divider_regs[DPLL44XX_ID_MAX][4];

extern const omap4_dpll_params_regs omap4_dpll_regs[DPLL44XX_ID_MAX];

extern const omap4_dpll_clock_sources omap4_dpll_sources[DPLL44XX_ID_MAX];

extern reg_table dpll44xx_prcm_reg_table[80];


int dpll44xx_init_regtable(void);


#endif
