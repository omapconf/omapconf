/*
 *
 * @Component			OMAPCONF
 * @Filename			dpll.h
 * @Description			OMAP DPLL Common Definitions & Functions
 * @Author			Patrick Titiano (p-titiano@ti.com)
 * @Date			2006
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2006 Texas Instruments Incorporated - http://www.ti.com/
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


#ifndef __DPLL_H__
#define __DPLL_H__


#include <reg.h>


#define DPLL_MAX_NAME_LENGTH			16
#define DPLL_OUTPUT_MAX_NAME_LENGTH		16
#define HSDIV_MAX_NAME_LENGTH			4
#define DPLL_MODE_MAX_NAME_LENGTH		10
#define DPLL_RAMP_LEVEL_MAX_NAME_LENGTH		10
#define DPLL_AUTOIDLE_MODE_MAX_NAME_LENGTH	10
#define DPLL_STATUS_MAX_NAME_LENGTH		10
#define DPLL_BP_CLK_SRC_MAX_NAME_LENGTH		12
#define DPLL_CLKOUTHIF_SRC_MAX_NAME_LENGTH	12


typedef enum {
	DPLL_TYPE_A,		/* DPLLs MPU, IVA, ABE, CORE, PER */
	DPLL_TYPE_B,		/* DPLLs USB, UNIPRO[1-2]) */
	DPLL_TYPE_MAX
} dpll_type;


typedef enum {
	DPLL_RESERVED_0 = 0,
	DPLL_LOW_POWER_STOP = 1,
	DPLL_FAST_RELOCK_STOP = 2,
	DPLL_RESERVED_3 = 3,
	DPLL_MN_BYPASS = 4,
	DPLL_LOW_POWER_BYPASS = 5,
	DPLL_FAST_RELOCK_BYPASS = 6,
	DPLL_LOCK = 7,
	DPLL_MODE_MAX = 8
} dpll_mode;


typedef enum {
	DPLL_DISABLED = 0,
	DPLL_AUTO_LOW_POWER_STOP = 1,
	DPLL_AUTO_FAST_RELOCK_STOP = 2,
	DPLL_AUTO_RESERVED_3 = 3,
	DPLL_AUTO_RESERVED_4 = 4,
	DPLL_AUTO_BYPASS_LOW_POWER = 5,
	DPLL_AUTO_BYPASS_FAST_RELOCK = 6,
	DPLL_AUTO_RESERVED_7 = 7,
	DPLL_AUTOIDLE_MODE_MAX
} dpll_autoidle_mode;


typedef enum {
	DPLL_STATUS_BYPASSED = 0,
	DPLL_STATUS_LOCKED = 1,
	DPLL_STATUS_STOPPED = 2,
	DPLL_STATUS_RESERVED = 3,
	DPLL_STATUS_MAX
} dpll_status;


typedef enum {
	DPLL_RAMP_NO = 0,
	DPLL_RAMP_8_4_2_1 = 1,
	DPLL_RAMP_4_2_1_5 = 2,
	DPLL_RAMP_RESERVED = 3,
	DPLL_RAMP_LEVEL_MAX = 4
} dpll_ramp_level;


typedef enum {
	DPLL_BP_CLK_SRC_CLKINP = 0,
	DPLL_BP_CLK_SRC_CLKINPULOW = 1,
	DPLL_BP_CLK_SRC_ID_MAX
} dpll_bp_clk_src;


typedef enum {
	DPLL_CLKOUTHIF_SRC_DCO = 0,
	DPLL_CLKOUTHIF_SRC_CLKINPHIF = 1,
	DPLL_CLKOUTHIF_SRC_ID_MAX
} dpll_clkouthif_src;


typedef struct {
	reg *cm_clkmode_dpll;
	reg *cm_idlest_dpll;
	reg *cm_autoidle_dpll;
	reg *cm_clksel_dpll;
	reg *cm_bypclk_dpll;
	reg *cm_div_m2_dpll;
	reg *cm_div_m3_dpll;
	reg *cm_ssc_deltamstep_dpll;
	reg *cm_ssc_modfreqdiv_dpll;
	reg *cm_clkdcoldo_dpll;
} dpll_settings_regs;


typedef struct {
	unsigned int relock_ramp_en;	/* CM_CLKMODE_DPLL.DPLL_RELOCK_RAMP_EN */
	unsigned int ramp_rate;		/* CM_CLKMODE_DPLL.DPLL_RAMP_RATE */
	unsigned int ramp_level;	/* CM_CLKMODE_DPLL.DPLL_RAMP_LEVEL */
} dpll_ramp_settings;


typedef struct {
	/* Common DPLL types A & B */
	unsigned int M;				/* CM_CLKSEL_DPLL.DPLL_MULT */
	unsigned int N;				/* CM_CLKSEL_DPLL.DPLL_DIV */
	unsigned short M2_present;		/* 0 if does not exist in CM_DIV_M2_DPLL, 1 otherwise */
	unsigned int M2;			/* CM_DIV_M2_DPLL.DPLL_CLKOUT_DIV */
	double M2_rate;				/* in MHz (== CLKOUT for DPLL type B */
	/* DPLL type A only */
	unsigned short M2_clkout_st;		/* CM_DIV_M2_DPLL.ST_DPLL_CLKOUT */
	unsigned short M2_autogating;		/* CM_DIV_M2_DPLL.DPLL_CLKOUT_GATE_CTRL */
	unsigned short X2_M2_present;		/* 0 if does not exist in CM_DIV_M2_DPLL, 1 otherwise */
	double X2_M2_rate;			/* in MHz */
	unsigned short X2_M2_clkout_st;		/* CM_DIV_M2_DPLL.ST_DPLL_CLKOUTX2 */
	unsigned short X2_M2_autogating;	/* CM_DIV_M2_DPLL.DPLL_CLKOUTX2_GATE_CTRL */
	unsigned short M3_present;		/* 0 if does not exist in CM_DIV_M3_DPLL, 1 otherwise */
	unsigned int M3;			/* CM_DIV_M3_DPLL.DPLL_CLKOUT_DIV */
	double X2_M3_rate;			/* in MHz */
	unsigned short X2_M3_clkout_st;		/* CM_DIV_M3_DPLL.ST_DPLL_CLKOUT */
	unsigned short X2_M3_autogating;	/* CM_DIV_M3_DPLL.DPLL_CLKOUT_GATE_CTRL */
	/* DPLL type B only */
	unsigned short clkdcoldo_clkout_st;	/* CM_CLKDCOLDO_DPLL.ST_DPLL_CLKDCOLDO */
	unsigned short clkdcoldo_autogating;	/* CM_CLKDCOLDO_DPLL.DPLL_CLKDCOLDO_GATE_CTRL */
	double clkdcoldo_rate;			/* in MHz */
	unsigned short clkoutldo_st;		/* CM_DIV_M2_DPLL.CLKLDOST (ex: DPLL PCIE_REF for DRA7) */
	double clkoutldo_rate;			/* in MHz */
} dpll_MN_settings;


typedef struct {
	char type[12];			/* CM_CLKMODE_DPLL_xxx.DPLL_SSC_TYPE */
	unsigned short downspread;	/* CM_CLKMODE_DPLL_xxx.DPLL_SSC_DOWNSPREAD */
	unsigned short mode;		/* CM_CLKMODE_DPLL_xxx.DPLL_SSC_EN */
	unsigned short ack;		/* CM_CLKMODE_DPLL_xxx.DPLL_SSC_ACK */
	unsigned int deltaMStep;	/* CM_SSC_DELTAMSTEP_DPLL_xxx.DELTAMSTEP */
	unsigned int exponent;		/* CM_SSC_MODFREQDIV_DPLL_xxx.MODFREQDIV_MANTISSA */
	unsigned int mantissa;		/* CM_SSC_MODFREQDIV_DPLL_xxx.MODFREQDIV_MANTISSA */
	double fm;			/* Modulation Frequency = [DPLL_REFCLK/4]/MODFREQDIV */
					/* MODFREQDIV = MODFREQDIV_MANTISSA * 2^MODFREQDIV_EXPONENT */
} dpll_SSC_settings; /* Spread Spectrum Clocking */


typedef struct {
	unsigned int en;		/* CM_CLKSEL_DPLL.DCC_EN */
	unsigned int count;		/* CM_CLKSEL_DPLL.DCC_COUNT_MAX */
} dpll_DCC_settings; /* Duty Cycle Correction */


typedef struct {
	/* Common DPLL type A & B */
	unsigned int id;			/* DPLL ID */
	unsigned short initialized;
	dpll_type type;				/* A or B */
	dpll_mode mode;				/* CM_CLKMODE_DPLL.DPLL_EN */
	dpll_autoidle_mode autoidle_mode;	/* CM_AUTOIDLE_DPLL.AUTO_DPLL_MODE */
	dpll_MN_settings MN;
	dpll_SSC_settings SSC;
	double fref;				/* REF_CLK, in MHz */
	double fbyp_clk_m2;			/* M2 output bypass clock, in MHz */
	double fdpll;				/* in MHz */
	unsigned short lock_status;		/* CM_IDLEST_DPLL.ST_DPLL_CLK */
	unsigned short mn_bypass_status;	/* CM_IDLEST_DPLL.ST_MN_BYPASS */
	/* DPLL type A only */
	dpll_DCC_settings DCC;
	dpll_ramp_settings ramp;
	unsigned int lpmode_en;			/* CM_CLKMODE_DPLL.DPLL_LPMODE_EN */
	unsigned int driftguard_en;		/* CM_CLKMODE_DPLL.DPLL_DRIFTGUARD_EN */
	unsigned short regm4xen;		/* CM_CLKMODE_DPLL.DPLL_REGM4XEN */
	double fbyp_clk_m3;			/* M3 output bypass clock, in MHz */
	double fbyp_clk_hsdiv;			/* HS dividers output bypass clock, in MHz */
	unsigned short bypass_clk_div;		/* CM_BYPCLK_DPLL.CLKSEL */
	unsigned short bypass_clk;		/* CM_CLKSEL_DPLL.DPLL_BYP_CLKSEL */
	unsigned short clkouthif_src;		/* CM_CLKSEL_DPLL.DPLL_CLKOUTHIF_CLKSEL */
	/* DPLL type B only */
	unsigned int sd_div;			/* CM_CLKSEL_DPLL.DPLL_SD_DIV */
	unsigned short selfreqdco;		/* CM_CLKSEL_DPLL.SELFREQDCO */
} dpll_settings;


typedef struct {
	unsigned int ref_clk;
	unsigned int byp_clk_m2;
	unsigned int byp_clk_m3;
	unsigned int byp_clk_hsdiv;
} dpll_clk_sources;


const char *dpll_mode_name_get(dpll_mode mode);
const char *dpll_ramp_level_name_get(dpll_ramp_level level);
const char *dpll_autoidle_mode_name_get(dpll_autoidle_mode mode);
const char *dpll_status_name_get(dpll_status status);
const char *dpll_bp_clk_src_name_get(dpll_bp_clk_src id);
const char *dpll_clkouthif_src_name_get(dpll_clkouthif_src id);

double dpll_lock_freq_calc(dpll_settings *settings);

int dpll_settings_extract(unsigned int id, dpll_type type,
	dpll_settings_regs *dpll_regs, dpll_settings *settings);


#endif
