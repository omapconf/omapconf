/*
 *
 * @Component			OMAPCONF
 * @Filename			dpll_dra7xx-data.h
 * @Description			DRA7 DPLL Definitions
 * @Author			Jin Zheng (j-zheng@ti.com)
 * @Date			2013
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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


#ifndef __DPLL_DRA7XX_DATA_H__
#define __DPLL_DRA7XX_DATA_H__


#include <dpll_dra7xx.h>
#include <voltdm_dra7xx.h>


typedef struct {
	/* Common DPLL type A & B */
	dpll_status status;
	dpll_mode mode;
	dpll_autoidle_mode autoidle_mode;
	double fref;
	int M;
	int N;
	double fdpll;
	int M2;
	double M2_rate;
	/* DPLL type A only */
	int dcc_en;
	short regm4xen;
	double X2_M2_rate;
	int M3;
	double X2_M3_rate;
	int hsdiv_div[HSDIV_DRA7XX_ID_MAX];
	double hsdiv_rate[HSDIV_DRA7XX_ID_MAX];
	/* DPLL type B only */
	int sd_div;
	short selfreqdco;
	double clkdcoldo_rate;
	double clkoutldo_rate;
} dpll_dra7xx_audited_settings;


extern const char dpll_dra7xx_names[DPLL_DRA7XX_ID_MAX][DPLL_MAX_NAME_LENGTH];
extern const char dpll_dra7xx_strings[DPLL_DRA7XX_ID_MAX][DPLL_MAX_NAME_LENGTH];
extern const char hsdiv_dra7xx_names[HSDIV_DRA7XX_ID_MAX][HSDIV_MAX_NAME_LENGTH];
const char dpll_dra7xx_output_names[DPLL_DRA7XX_OUTPUT_ID_MAX][DPLL_OUTPUT_MAX_NAME_LENGTH];
const dpll_clk_sources dpll_dra7xx_sources[DPLL_DRA7XX_ID_MAX];

extern short dpll_dra7xx_ignore_m3[DPLL_DRA7XX_ID_MAX];
extern dpll_dra7xx_audited_settings
	*dpll_dra7xx_golden_settings_20MHz_table[DPLL_DRA7XX_ID_MAX][OPP_DRA7XX_ID_MAX];

#endif
