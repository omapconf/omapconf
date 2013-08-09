/*
 *
 * @Component			OMAPCONF
 * @Filename			dpll.c
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


#include <dpll.h>
#include <dpll44xx.h>
#include <cm44xx.h>
#include <lib.h>
#include <cpuinfo.h>
#include <string.h>


/* #define DPLL_DEBUG */
#ifdef DPLL_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static const char
	dpll_mode_names[DPLL_MODE_MAX][DPLL_MODE_MAX_NAME_LENGTH] = {
	"RESERVED",
	"LPST",
	"FRST",
	"RESERVED",
	"MNBP",
	"LPBP",
	"FRBP",
	"Lock"};


static const char
	dpll_ramp_level_names[DPLL_RAMP_LEVEL_MAX][DPLL_RAMP_LEVEL_MAX_NAME_LENGTH] = {
	"No Ramp",
	"8,4,2",
	"4,2,1.5",
	"RESERVED"};


static const char
	dpll_autoidle_mode_names[DPLL_AUTOIDLE_MODE_MAX][DPLL_AUTOIDLE_MODE_MAX_NAME_LENGTH] = {
	"Disabled",
	"Auto LPST",
	"Auto FRST",
	"RESERVED",
	"RESERVED",
	"Auto LPBP",
	"Auto FRBP",
	"RESERVED"};


static const char
	dpll_status_names[DPLL_STATUS_MAX][DPLL_STATUS_MAX_NAME_LENGTH] = {
	"Bypassed",
	"Locked",
	"Stopped",
	"Reserved"};


static const char
	dpll_bp_clk_src_names[DPLL_BP_CLK_SRC_ID_MAX][DPLL_BP_CLK_SRC_MAX_NAME_LENGTH] = {
	"CLKINP",
	"CLKINPULOW"};


static const char
	dpll_clkouthif_src_names[DPLL_CLKOUTHIF_SRC_ID_MAX][DPLL_CLKOUTHIF_SRC_MAX_NAME_LENGTH] = {
	"DCO",
	"CLKINPHIF"};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_mode_name_get
 * @BRIEF		return DPLL mode name
 * @RETURNS		pointer towards const string containing DPLL mode name
 *			"RESERVED" in case of 'mode' is invalid
 * @param[in]		mode: dpll mode extracted from register
 * @DESCRIPTION		return DPLL mode name
 *//*------------------------------------------------------------------------ */
const char *dpll_mode_name_get(dpll_mode mode)
{
	if (mode >= DPLL_MODE_MAX) {
		fprintf(stderr, "%s(): bad mode! (%u)\n", __func__, mode);
		return (char *) dpll_mode_names[DPLL_RESERVED_0];
	}

	return (char *) dpll_mode_names[mode];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_ramp_level_name_get
 * @BRIEF		return RAMP LEVEL string
 * @RETURNS		pointer towards const string containing
 *			DPLL RAMP LEVEL name
 *			"RESERVED" in case of 'mode' is invalid
 * @param[in]		level: RAMP LEVEL mode extracted from register
 * @DESCRIPTION		return RAMP LEVEL string
 *//*------------------------------------------------------------------------ */
const char *dpll_ramp_level_name_get(dpll_ramp_level level)
{
	if (level >= DPLL_RAMP_LEVEL_MAX) {
		fprintf(stderr, "%s(): bad level! (%u)\n", __func__, level);
		return (char *) dpll_ramp_level_names[DPLL_RAMP_RESERVED];
	}

	return (char *) dpll_ramp_level_names[level];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_autoidle_mode_name_get
 * @BRIEF		return DPLL autoidle mode name
 * @RETURNS		pointer towards const string containing
 *			DPLL autoidle mode name
 *			"RESERVED" in case of 'mode' is invalid
 * @param[in]		mode: dpll autoidle mode extracted from register
 * @DESCRIPTION		return DPLL autoidle mode name
 *//*------------------------------------------------------------------------ */
const char *dpll_autoidle_mode_name_get(dpll_autoidle_mode mode)
{
	if (mode >= DPLL_AUTOIDLE_MODE_MAX) {
		fprintf(stderr, "%s(): bad mode! (%u)\n", __func__, mode);
		return (char *) dpll_autoidle_mode_names[DPLL_AUTO_RESERVED_7];
	}

	return (char *) dpll_autoidle_mode_names[mode];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_status_name_get
 * @BRIEF		return DPLL status name
 * @RETURNS		pointer towards const string containing DPLL status name
 *			"RESERVED" in case of 'status' is invalid
 * @param[in]		status: dpll status extracted from register
 * @DESCRIPTION		return DPLL status name
 *//*------------------------------------------------------------------------ */
const char *dpll_status_name_get(dpll_status status)
{
	if (status >= DPLL_STATUS_MAX) {
		fprintf(stderr, "%s(): bad status! (%u)\n", __func__, status);
		return (char *) dpll_status_names[DPLL_STATUS_RESERVED];
	}

	return (char *) dpll_status_names[status];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_bp_clk_src_name_get
 * @BRIEF		return DPLL bypass source clock name
 * @RETURNS		bypass source clock name on success
 *			NULL in case of error
 * @param[in]		id: valid DPLL bypass source clock ID
 * @DESCRIPTION		return DPLL bypass source clock name
 *//*------------------------------------------------------------------------ */
const char *dpll_bp_clk_src_name_get(dpll_bp_clk_src id)
{
	CHECK_ARG_LESS_THAN(id, DPLL_BP_CLK_SRC_ID_MAX, NULL);

	return (char *) dpll_bp_clk_src_names[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_clkouthif_src_name_get
 * @BRIEF		return DPLL clkouthif source clock name
 * @RETURNS		clkouthif source clock name on success
 *			NULL in case of error
 * @param[in]		id: valid DPLL clkouthif source clock ID
 * @DESCRIPTION		return DPLL clkouthif source clock name
 *//*------------------------------------------------------------------------ */
const char *dpll_clkouthif_src_name_get(dpll_clkouthif_src id)
{
	CHECK_ARG_LESS_THAN(id, DPLL_CLKOUTHIF_SRC_ID_MAX, NULL);

	return (char *) dpll_clkouthif_src_names[id];
}


#ifndef DPLL_DEBUG
/* #define DPLL_SETTINGS_EXTRACT_DEBUG */
#ifdef DPLL_SETTINGS_EXTRACT_DEBUG
#undef dprintf
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif
#endif
/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_settings_extract
 * @BRIEF		extract DPLL settings from registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		id: valid DPLL ID
 * @param[in]		type: DPLL type
 * @param[in]		dpll_regs: dpll registers to extract settings from
 * @param[in,out]	settings: struct with extracted DPLL settings
 * @DESCRIPTION		extract DPLL settings from registers
 *//*------------------------------------------------------------------------ */
int dpll_settings_extract(unsigned int id, dpll_type type,
	dpll_settings_regs *dpll_regs, dpll_settings *settings)
{
	unsigned int val;
	CHECK_NULL_ARG(dpll_regs, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(settings, OMAPCONF_ERR_ARG);

	settings->id = id;
	settings->type = type;

	/* Extract data from CM_CLKMODE_DPLL_xyz */
	val = reg_read(dpll_regs->cm_clkmode_dpll);
	dprintf("%s(): DPLL reg: %s = 0x%08X\n", __func__,
		(dpll_regs->cm_clkmode_dpll)->name, val);

	settings->mode = extract_bitfield(val, 0, 3);
	(settings->ramp).ramp_level = extract_bitfield(val, 3, 2);
	(settings->ramp).ramp_rate = 1 << (extract_bitfield(val,
		5, 3) + 1);
	settings->driftguard_en = extract_bit(val, 8);
	(settings->ramp).relock_ramp_en = extract_bit(val, 9);
	settings->lpmode_en = extract_bit(val, 10);
	settings->regm4xen = extract_bit(val, 11);
	(settings->SSC).mode = extract_bit(val, 12);
	(settings->SSC).ack = extract_bit(val, 13);
	(settings->SSC).downspread = extract_bit(val, 14);

	dprintf("%s():   mode=0x%X (%s), lp_mode=%u, REGM4XEN=%u, "
		"DRIFTGUARD_EN=%u\n", __func__, settings->mode,
		dpll_mode_name_get(settings->mode), settings->lpmode_en,
		settings->regm4xen, settings->driftguard_en);
	dprintf("%s():   RAMP_EN=%u, RAMP_RATE=%uxREFCLK, RAMP_LEVEL=%u (%s)\n",
		__func__, (settings->ramp).relock_ramp_en,
		(settings->ramp).ramp_rate, (settings->ramp).ramp_level,
		dpll_ramp_level_name_get((settings->ramp).ramp_level));
	dprintf("%s():   SSC_EN=%u, SSC_ACK=%u, SSC_DOWNSPREAD=%u\n",
		__func__, (settings->SSC).mode,
		(settings->SSC).ack, (settings->SSC).downspread);

	/* Extract data from CM_IDLEST_DPLL_xyz */
	val = reg_read(dpll_regs->cm_idlest_dpll);
	dprintf("%s(): DPLL reg: %s = 0x%08X\n", __func__,
		(dpll_regs->cm_idlest_dpll)->name, val);

	settings->lock_status = extract_bit(val, 0);
	settings->mn_bypass_status = extract_bit(val, 8);

	dprintf("%s():   ST_DPLL_CLK=%u, ST_MN_BYPASS=%u\n",
		__func__, settings->lock_status, settings->mn_bypass_status);

	/* Extract data from CM_AUTOIDLE_DPLL_xyz */
	val = reg_read(dpll_regs->cm_autoidle_dpll);
	dprintf("%s(): DPLL reg: %s = 0x%08X\n", __func__,
		(dpll_regs->cm_autoidle_dpll)->name, val);

	settings->autoidle_mode = extract_bitfield(val, 0, 3);

	dprintf("%s():   AUTO_DPLL_MODE=%u (%s)\n", __func__,
		settings->autoidle_mode,
		dpll_autoidle_mode_name_get(settings->autoidle_mode));

	/* Extract data from CM_CLKSEL_DPLL_xyz */
	val = reg_read(dpll_regs->cm_clksel_dpll);
	dprintf("%s(): DPLL reg: %s = 0x%08X\n", __func__,
		(dpll_regs->cm_clksel_dpll)->name, val);

	settings->bypass_clk = extract_bit(val, 23);
	if (settings->type == DPLL_TYPE_A) {
		(settings->MN).N = extract_bitfield(val, 0, 7);
		(settings->MN).M = extract_bitfield(val, 8, 11);
		settings->clkouthif_src = extract_bit(val, 20);
		if (!cpu_is_omap4430()) {
			(settings->DCC).en = extract_bit(val, 22);
			(settings->DCC).count = extract_bitfield(val, 24, 8);
		} else {
			(settings->DCC).en = 0;
			(settings->DCC).count = 0;
		}
	} else {
		(settings->MN).N = extract_bitfield(val, 0, 8);
		(settings->MN).M = extract_bitfield(val, 8, 12);
		settings->selfreqdco = extract_bit(val, 21);
		settings->sd_div = extract_bitfield(val, 24, 8);
		dprintf("%s():   SELFREQDCO=%u, SD_DIV=%u\n", __func__,
			settings->selfreqdco, settings->sd_div);
	}
	dprintf("%s():   M=%u, N=%u, CLKOUTHIF_CLK=%u, BP_CLK=%u\n", __func__,
		(settings->MN).M, (settings->MN).N, settings->clkouthif_src,
		settings->bypass_clk);
	dprintf("%s():   DCC_EN=%u, DCC_COUNT=%u\n", __func__,
		(settings->DCC).en, (settings->DCC).count);

	/* Extract data from CM_BYPCLK_DPLL_XYZ */
	if ((void *) dpll_regs->cm_bypclk_dpll != NULL) {
		val = reg_read(dpll_regs->cm_bypclk_dpll);
		dprintf("%s(): DPLL reg: %s = 0x%08X\n", __func__,
			(dpll_regs->cm_bypclk_dpll)->name, val);

		settings->bypass_clk_div = 1 << extract_bitfield(val, 0, 2);

		dprintf("%s():   BP_CLK_DIV=%u\n", __func__,
			settings->bypass_clk_div);

	} else {
		settings->bypass_clk_div = 1;

		dprintf("%s(): BYPCLK register does not exist.\n", __func__);
	}

	/* Extract data from CM_DIV_M2_DPLL_XYZ */
	if ((void *) dpll_regs->cm_div_m2_dpll != NULL) {
		val = reg_read(dpll_regs->cm_div_m2_dpll);
		dprintf("%s(): DPLL reg: %s = 0x%08X\n", __func__,
			(dpll_regs->cm_div_m2_dpll)->name, val);

		(settings->MN).M2_present = 1;
		if (settings->type == DPLL_TYPE_A) {
			(settings->MN).M2 = extract_bitfield(val, 0, 5);
			(settings->MN).X2_M2_autogating =
				!extract_bit(val, 10);
			(settings->MN).X2_M2_clkout_st = extract_bit(val, 11);
		} else {
			(settings->MN).M2 = extract_bitfield(val, 0, 7);
		}
		(settings->MN).M2_autogating = !extract_bit(val, 8);
		(settings->MN).M2_clkout_st = extract_bit(val, 9);

		dprintf("%s():   M2 DIV=%u, AUTOGATING=%u, CLKST=%u\n",
			__func__, (settings->MN).M2,
			(settings->MN).M2_autogating,
			(settings->MN).M2_clkout_st);
		if (settings->type == DPLL_TYPE_A) {
			dprintf("%s():   X2_M2 AUTOGATING=%u, CLKST=%u\n",
				__func__, (settings->MN).X2_M2_autogating,
				(settings->MN).X2_M2_clkout_st);
		}
	} else {
		(settings->MN).M2_present = 0;

		dprintf("%s(): DIV_M2 register does not exist.\n", __func__);
	}

	/* Extract data from CM_DIV_M3_DPLL_XYZ */
	if ((void *) dpll_regs->cm_div_m3_dpll != NULL) {
		val = reg_read(dpll_regs->cm_div_m3_dpll);
		dprintf("%s(): DPLL reg: %s = 0x%08X\n", __func__,
			(dpll_regs->cm_div_m3_dpll)->name, val);

		(settings->MN).M3_present = 1;
		(settings->MN).M3 = extract_bitfield(val, 0, 5);
		(settings->MN).X2_M3_autogating = !extract_bit(val, 8);
		(settings->MN).X2_M3_clkout_st = extract_bit(val, 9);

		dprintf("%s():   X2_M3 DIV=%u, AUTOGATING=%u, CLKST=%u\n",
			__func__, (settings->MN).M3,
			(settings->MN).X2_M3_autogating,
			(settings->MN).X2_M3_clkout_st);
	} else {
		(settings->MN).M3_present = 0;

		dprintf("%s(): DIV_M3 register does not exist.\n", __func__);
	}

	/* Extract data from CM_DELTAMSTEP_DPLL_xyz */
	val = reg_read(dpll_regs->cm_ssc_deltamstep_dpll);
	dprintf("%s(): DPLL reg: %s = 0x%08X\n", __func__,
		(dpll_regs->cm_ssc_deltamstep_dpll)->name, val);

	(settings->SSC).deltaMStep = extract_bitfield(val, 0, 20);

	dprintf("%s():   deltaMStep=0x%X\n", __func__,
		(settings->SSC).deltaMStep);

	/* Extract data from CM_MODFREQDIV_DPLL_xyz */
	val = reg_read(dpll_regs->cm_ssc_modfreqdiv_dpll);
	dprintf("%s(): DPLL reg: %s = 0x%08X\n", __func__,
		(dpll_regs->cm_ssc_modfreqdiv_dpll)->name, val);

	(settings->SSC).mantissa = extract_bitfield(val, 0, 7);
	(settings->SSC).exponent = extract_bitfield(val, 8, 3);

	dprintf("%s():   mantissa=0x%X, exponent=0x%X\n", __func__,
		(settings->SSC).mantissa, (settings->SSC).exponent);

	/* Extract data from CM_CLKDCOLDO_DPLL_xyz */
	if ((void *) dpll_regs->cm_clkdcoldo_dpll != NULL) {
		val = reg_read(dpll_regs->cm_clkdcoldo_dpll);
		dprintf("%s(): DPLL reg: %s = 0x%08X\n", __func__,
			(dpll_regs->cm_clkdcoldo_dpll)->name, val);

		(settings->MN).clkdcoldo_autogating = !extract_bit(val, 8);
		(settings->MN).clkdcoldo_clkout_st = extract_bit(val, 9);

		dprintf("%s():   CLKDCOLDO AUTOGATING=%u, CLKST=%u\n",
			__func__,
			(settings->MN).clkdcoldo_autogating,
			(settings->MN).clkdcoldo_clkout_st);
	}
	return 0;
}
#ifdef DPLL_SETTINGS_EXTRACT_DEBUG
#undef dprintf
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_lock_freq_calc
 * @BRIEF		compute DPLL lock frequency (in MHz)
 * @RETURNS		lock frequency in case of success (in MHz)
 *			0.0 in case of error.
 * @param[in]		settings: DPLL settings with fields
 *			regm4xen, fref, MN.M, MN.N INITIALIZED
 * @DESCRIPTION		compute DPLL lock frequency (in MHz)
 *//*------------------------------------------------------------------------ */
double dpll_lock_freq_calc(dpll_settings *settings)
{
	CHECK_NULL_ARG(settings, 0.0);

	if (settings->type == DPLL_TYPE_A) {
		if (settings->regm4xen == 1)
			settings->fdpll =
				(settings->fref * 8.0 * (double) (settings->MN).M) /
				((double) (settings->MN).N + 1.0);
		else if ((settings->DCC).en == 1)
			settings->fdpll =
				(settings->fref * 1.0 * (double) (settings->MN).M) /
				((double) (settings->MN).N + 1.0);
		else
			settings->fdpll =
				(settings->fref * 2.0 * (double) (settings->MN).M) /
				((double) (settings->MN).N + 1.0);
		dprintf(
			"%s(%u): type=A regm4xen=%u DCC_EN=%u fref=%lfMHz M=%u N=%u => fdpll=%lfMHz\n",
			__func__, settings->id, settings->regm4xen,
			(settings->DCC).en, settings->fref, (settings->MN).M,
			(settings->MN).N, settings->fdpll);
	} else {
		settings->fdpll =
			(settings->fref * (double) (settings->MN).M) /
			((double) (settings->MN).N + 1.0);
		dprintf("%s(%u): type=B fref=%lfMHz M=%u N=%u => "
			"fdpll=%lfMHz\n", __func__, settings->id,
			settings->fref, (settings->MN).M,
			(settings->MN).N, settings->fdpll);
	}

	return settings->fdpll;
}
