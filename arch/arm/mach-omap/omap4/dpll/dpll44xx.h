/*
 *
 * @Component			OMAPCONF
 * @Filename			dpll44xx.h
 * @Description			OMAP4 DPLL PRCM Definitions & Functions
 * @Author			Patrick Titiano (p-titiano@ti.com)
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


#ifndef __DPLL44XX_H__
#define __DPLL44XX_H__


#include <dpll.h>
#include <stdio.h>
#include <voltdm44xx.h>


typedef enum {
	DPLL44XX_MPU = 0,
	DPLL44XX_IVA = 1,
	DPLL44XX_CORE = 2,
	DPLL44XX_PER = 3,
	DPLL44XX_ABE = 4,
	DPLL44XX_USB = 5,
	DPLL44XX_UNIPRO = 6,
	DPLL44XX_DDRPHY = 7,
	DPLL44XX_ID_MAX = 8
} dpll44xx_id;


typedef struct {
	char type[12];			/* CM_CLKMODE_DPLL_xxx.DPLL_SSC_TYPE */
	unsigned short downspread;	/* CM_CLKMODE_DPLL_xxx.DPLL_SSC_DOWNSPREAD */
	unsigned short mode;		/* CM_CLKMODE_DPLL_xxx.DPLL_SSC_EN */
	unsigned short status;		/* CM_CLKMODE_DPLL_xxx.DPLL_SSC_ACK */
	unsigned int deltaMStep;	/* CM_SSC_DELTAMSTEP_DPLL_xxx.DELTAMSTEP */
	unsigned int exponent;		/* CM_SSC_MODFREQDIV_DPLL_xxx.MODFREQDIV_MANTISSA */
	unsigned int mantissa;		/* CM_SSC_MODFREQDIV_DPLL_xxx.MODFREQDIV_MANTISSA */
	double fm;			/* Modulation Frequency = [DPLL_REFCLK/4]/MODFREQDIV */
					/* MODFREQDIV = MODFREQDIV_MANTISSA * 2^MODFREQDIV_EXPONENT */
} omap4_dpll_SSC_params;

typedef struct {
	unsigned short present;		/* 0 if DPLL_xyz if does not exist in CM_DIV_Mx_DPLL_xyz, 1 otherwise */
	unsigned short pwdn;		/* CM_DIV_Mx_DPLL_xyz.HSDIVIDER_CLKOUTx_PWDN */
	unsigned short status;		/* CM_DIV_Mx_DPLL_xyz.ST_HSDIVIDER_CLKOUTx */
	unsigned short autogating;	/* CM_DIV_Mx_DPLL_xyz.HSDIVIDER_CLKOUTx_GATE_CTRL */
	unsigned int div;		/* CM_DIV_Mx_DPLL_xyz.HSDIVIDER_CLKOUTx_DIV */
} omap4_dpll_hs_divider_params;

typedef struct {
	unsigned int N;			/* CM_CLKSEL_DPLL_xyz.DPLL_MULT */
	unsigned int M;			/* CM_CLKSEL_DPLL_xyz.DPLL_DIV */
	unsigned int M2;		/* CM_DIV_M2_DPLL_xyz.DPLL_CLKOUT_DIV */
	unsigned int M3;		/* CM_DIV_M3_DPLL_xyz.DPLL_CLKOUT_DIV */
} omap4_dpll_MN_params;

typedef struct {
	dpll44xx_id id;			/* DPLL ID */
	unsigned int lpmode;		/* CM_CLKMODE_DPLL_xyz.DPLL_LPMODE_EN */
	unsigned int relock_ramp_en;	/* CM_CLKMODE_DPLL_xyz.DPLL_RELOCK_RAMP_EN */
	unsigned int driftguard_en;	/* CM_CLKMODE_DPLL_xyz.DPLL_DRIFTGUARD_EN */
	unsigned int ramp_time;		/* CM_CLKMODE_DPLL_xyz.DPLL_RAMP_RATE */
	unsigned int ramp_level;	/* CM_CLKMODE_DPLL_xyz.DPLL_RAMP_LEVEL */
	unsigned short mode;		/* CM_CLKMODE_DPLL_xyz.DPLL_EN */
	unsigned short regm4xen;	/* CM_CLKMODE_DPLL_xyz.DPLL_REGM4XEN */
	unsigned int dcc_en;		/* CM_CLKSEL_DPLL_xyz.DCC_EN */
	unsigned int dcc_count;		/* CM_CLKSEL_DPLL_xyz.DCC_COUNT_MAX */
	dpll_status status;	/* CM_IDLEST_DPLL_xyz.ST_DPLL_CLK + CM_IDLEST_DPLL_xyz.ST_MN_BYPASS */
	unsigned short autoidle_mode;	/* CM_AUTOIDLE_DPLL_xyz.AUTO_DPLL_MODE */
	unsigned short bypass_clk;	/* CM_CLKSEL_DPLL_xyz.DPLL_BYP_CLKSEL */
	unsigned short bypass_clk_div;	/* CM_BYPCLK_DPLL_xyz.CLKSEL */
	unsigned short clkouthif_src;	/* CM_CLKSEL_DPLL_xyz.DPLL_CLKOUTHIF_CLKSEL */
	unsigned short M2_present;	/* 0 if DPLL_xyz if does not exist in CM_DIV_Mx_DPLL_xyz, 1 otherwise */
	unsigned short M2_clkout_st;	/* CM_DIV_M2_DPLL_xyz.ST_DPLL_CLKOUT */
	unsigned short M2_autogating;	/* CM_DIV_M2_DPLL_xyz.DPLL_CLKOUT_GATE_CTRL */
	unsigned short X2_M2_clkout_st;	/* CM_DIV_M2_DPLL_xyz.ST_DPLL_CLKOUTX2 */
	unsigned short X2_M2_autogating;/* CM_DIV_M2_DPLL_xyz.DPLL_CLKOUTX2_GATE_CTRL */
	unsigned short M3_present;	/* 0 if DPLL_xyz if does not exist in CM_DIV_Mx_DPLL_xyz, 1 otherwise */
	unsigned short X2_M3_clkout_st;	/* CM_DIV_M3_DPLL_xyz.ST_DPLL_CLKOUT */
	unsigned short X2_M3_autogating;/* CM_DIV_M3_DPLL_xyz.DPLL_CLKOUT_GATE_CTRL */
	omap4_dpll_SSC_params SSC_params;
	omap4_dpll_MN_params MN_params;
	omap4_dpll_hs_divider_params HS_M[4];

	double fref;		/* REF_CLK, in KHz */
	double fbyp_clk_m2;	/* M2 output bypass clock, in KHz */
	double fbyp_clk_m3;	/* M3 output bypass clock, in KHz */
	double fbyp_clk_mx;	/* HS dividers output bypass clock, in KHz */
	double fdpll;		/* in MHz */
	double M2_speed;	/* in MHz */
	double X2_M2_speed;	/* in MHz */
	double X2_M3_speed;	/* in MHz */
	double X2_M4_speed;	/* in MHz */
	double X2_M5_speed;	/* in MHz */
	double X2_M6_speed;	/* in MHz */
	double X2_M7_speed;	/* in MHz */
} omap4_dpll_params;


const char *dpll44xx_name_get(dpll44xx_id id);
int dpll44xx_dpll_params_get(dpll44xx_id dpll_id,
	omap4_dpll_params *dpll_params, unsigned short ignore_stop_status);
int dpll44xx_name2addr(char *name, unsigned int *addr);
int dpll44xx_dump(void);
int dpll44xx_main(int argc, char *argv[]);
int dpll44xx_config_show(FILE *stream);
int dpll44xx_audit(dpll44xx_id dpll_id, opp44xx_id opp_id,
	FILE *stream, unsigned int *err_nbr, unsigned int *wng_nbr);
dpll44xx_id dpll44xx_s2id(char *s);
double dpll44xx_dcc_count2us(unsigned int dcc_count);


#endif
