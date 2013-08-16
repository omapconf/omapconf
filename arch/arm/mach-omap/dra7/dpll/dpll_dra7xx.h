/*
 *
 * @Component			OMAPCONF
 * @Filename			dpll_dra7xx.h
 * @Description			DRA7 DPLL Definitions & Functions
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


#ifndef __DPLL_DRA7XX_H__
#define __DPLL_DRA7XX_H__


#include <dpll.h>
#include <voltdm_dra7xx.h>
#include <cm_dra7xx-defs.h>
#include <stdio.h>


typedef struct {
	hsdiv_dra7xx_id id;
	unsigned short present;	/* 0 if no CM_DIV_Hmn_DPLL_xyz, 1 otherwise */
	unsigned short status;	/* CM_DIV_Hmn_DPLL_xyz.CLKST */
	unsigned int div;	/* CM_DIV_Hmn_DPLL_xyz.DIVHS */
	double rate;		/* CLKOUTX2_Hmn rate in MHz */
} hsdiv_dra7xx_settings;


typedef struct {
	dpll_settings dpll;
	dpll_status status;
	hsdiv_dra7xx_settings hsdiv[HSDIV_DRA7XX_ID_MAX];
} dpll_dra7xx_settings;


typedef enum {
	DPLL_DRA7XX_CLKOUT_M2,
	DPLL_DRA7XX_CLKOUTX2_M2,
	DPLL_DRA7XX_CLKOUTX2_M3,
	DPLL_DRA7XX_CLKOUTX2_H11,
	DPLL_DRA7XX_CLKOUTX2_H12,
	DPLL_DRA7XX_CLKOUTX2_H13,
	DPLL_DRA7XX_CLKOUTX2_H14,
	DPLL_DRA7XX_CLKOUTX2_H21,
	DPLL_DRA7XX_CLKOUTX2_H22,
	DPLL_DRA7XX_CLKOUTX2_H23,
	DPLL_DRA7XX_CLKOUTX2_H24,
	DPLL_DRA7XX_CLKOUTX2_M2_LDO,
	DPLL_DRA7XX_CLK_DCO_LDO,
	DPLL_DRA7XX_OUTPUT_ID_MAX
} dpll_dra7xx_output_id;


int dpll_dra7xx_init(void);
int dpll_dra7xx_free(void);

int dpll_dra7xx_settings_extract(dpll_dra7xx_settings *settings,
	unsigned int id, unsigned short ignore);

dpll_dra7xx_settings *dpll_dra7xx_settings_get(
	unsigned int id, unsigned short ignore);

dpll_status dpll_dra7xx_status_get(dpll_dra7xx_id id);

double dpll_dra7xx_output_rate_get(
	dpll_dra7xx_id id, dpll_dra7xx_output_id out_id, unsigned short ignore);

int dpll_dra7xx_audit(dpll_dra7xx_id dpll_id, opp_dra7xx_id opp_id,
	FILE *stream, unsigned int *err_nbr, unsigned int *wng_nbr);

int dpll_type_b_show(dpll_dra7xx_id start_id, dpll_dra7xx_id end_id, FILE *stream);
int dpll_type_a_show(dpll_dra7xx_id start_id, dpll_dra7xx_id end_id, FILE *stream);
dpll_dra7xx_id dpll_dra7xx_s2id(char *s);
int dpll_dra7xx_dump(FILE *stream, dpll_dra7xx_id id);
int dpll_dra7xx_show(FILE *stream);
int dpll_dra7xx_main(int argc, char *argv[]);


#endif
