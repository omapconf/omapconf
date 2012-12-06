/*
 *
 * @Component			OMAPCONF
 * @Filename			dpll54xx.h
 * @Description			OMAP5 DPLL Definitions & Functions
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


#ifndef __DPLL54XX_H__
#define __DPLL54XX_H__


#include <dpll.h>
#include <cm54xxes1-defs.h>
#include <voltdm54xx.h>
#include <stdio.h>


typedef struct {
	hsdiv54xx_id id;
	unsigned short present;	/* 0 if no CM_DIV_Hmn_DPLL_xyz, 1 otherwise */
	unsigned short status;	/* CM_DIV_Hmn_DPLL_xyz.CLKST */
	unsigned int div;	/* CM_DIV_Hmn_DPLL_xyz.DIVHS */
	double rate;		/* CLKOUTX2_Hmn rate in MHz */
} hsdiv54xx_settings;


typedef struct {
	dpll_settings dpll;
	dpll_status status;
	hsdiv54xx_settings hsdiv[HSDIV54XX_ID_MAX];
} dpll54xx_settings;


typedef enum {
	DPLL54XX_CLKOUT_M2,
	DPLL54XX_CLKOUTX2_M2,
	DPLL54XX_CLKOUTX2_M3,
	DPLL54XX_CLKOUTX2_H11,
	DPLL54XX_CLKOUTX2_H12,
	DPLL54XX_CLKOUTX2_H13,
	DPLL54XX_CLKOUTX2_H14,
	DPLL54XX_CLKOUTX2_H21,
	DPLL54XX_CLKOUTX2_H22,
	DPLL54XX_CLKOUTX2_H23,
	DPLL54XX_CLKOUTX2_H24,
	DPLL54XX_CLK_DCO_LDO,
	DPLL54XX_OUTPUT_ID_MAX
} dpll54xx_output_id;


int dpll54xx_init(void);

int dpll54xx_free(void);

int dpll54xx_main(int argc, char *argv[]);

int dpll54xx_settings_extract(dpll54xx_settings *settings,
	unsigned int id, unsigned short ignore);

dpll54xx_settings *dpll54xx_settings_get(
	unsigned int id, unsigned short ignore);

dpll_status dpll54xx_status_get(dpll54xx_id id);

double dpll54xx_output_rate_get(
	dpll54xx_id id, dpll54xx_output_id out_id, unsigned short ignore);

int dpll54xx_audit(dpll54xx_id dpll_id, opp54xx_id opp_id,
	FILE *stream, unsigned int *err_nbr, unsigned int *wng_nbr);

dpll54xx_id dpll54xx_s2id(char *s);


int dpll54xx_dump(FILE *stream, dpll54xx_id id);
int dpll54xx_show(FILE *stream);


#endif
