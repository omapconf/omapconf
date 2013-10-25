/*
 *
 * @Component			OMAPCONF
 * @Filename			dpll54xx.c
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


#include <dpll54xx.h>
#include <dpll54xx-data.h>
#include <cm54xx-defs.h>
#include <clock54xx.h>
#include <voltdomain.h>
#include <autoadjust_table.h>
#include <stdio.h>
#include <lib.h>
#include <help.h>
#include <cpuinfo.h>
#include <string.h>
#include <opp.h>


/* #define DPLL54XX_DEBUG */
#ifdef DPLL54XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


#define DPLL54XX_AUDIT_SHOW_STATUS(curr, golden) \
		if (curr == golden) { \
			snprintf(table[row++][3], TABLE_MAX_ELT_LEN, "PASS"); \
		} else { \
			snprintf(table[row++][3], TABLE_MAX_ELT_LEN, "FAIL"); \
			(*err_nbr)++; \
		}


#define DPLL54XX_AUDIT_CHECK_GOLDEN_SETTING(setting, defval, gotolabel) \
		if (setting == defval) {\
			/* Golden setting not available */\
			snprintf(table[row][2], TABLE_MAX_ELT_LEN,\
				"Not available");\
			snprintf(table[row][3], TABLE_MAX_ELT_LEN, "warn.");\
			(*wng_nbr)++;\
			row++;\
			goto gotolabel;\
		}

dpll54xx_settings *dpll54xx_settings_table[DPLL54XX_ID_MAX] = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL};


dpll54xx_settings *dpll54xx_locked_settings_table[DPLL54XX_ID_MAX] = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll54xx_s2id
 * @BRIEF		convert string to valid DPLL ID
 * @RETURNS		DPLL54XX_MPU if s == "mpu"
 *			DPLL54XX_IVA if s == "iva"
 *			DPLL54XX_CORE if s == "core"
 *			DPLL54XX_PER if s == "per"
 *			DPLL54XX_ABE if s == "abe"
 *			DPLL54XX_USB if s == "usb"
 *			DPLL54XX_UNIPRO1 if s == "unipro1"
 *			DPLL54XX_UNIPRO2 if s == "unipro2"
 *			DPLL54XX_ID_MAX otherwise
 * @param[in,out]	s: string
 * @DESCRIPTION		convert string to valid DPLL ID
 *//*------------------------------------------------------------------------ */
dpll54xx_id dpll54xx_s2id(char *s)
{
	CHECK_NULL_ARG(s, DPLL54XX_ID_MAX);

	if (strcmp(s, "mpu") == 0)
		return  DPLL54XX_MPU;
	else if (strcmp(s, "iva") == 0)
		return  DPLL54XX_IVA;
	else if (strcmp(s, "core") == 0)
		return  DPLL54XX_CORE;
	else if (strcmp(s, "per") == 0)
		return  DPLL54XX_PER;
	else if (strcmp(s, "abe") == 0)
		return  DPLL54XX_ABE;
	else if (strcmp(s, "usb") == 0)
		return  DPLL54XX_USB;
	else if (strcmp(s, "unipro1") == 0)
		return  DPLL54XX_UNIPRO1;
	else if (strcmp(s, "unipro2") == 0)
		return  DPLL54XX_UNIPRO2;
	else
		return DPLL54XX_ID_MAX;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll54xx_name_get
 * @BRIEF		return DPLL name
 * @RETURNS		DPLL name
 *			NULL in case of incorrect id
 * @param[in]		id: DPLL ID
 * @DESCRIPTION		return DPLL name
 *//*------------------------------------------------------------------------ */
const char *dpll54xx_name_get(dpll54xx_id id)
{
	CHECK_ARG_LESS_THAN(id, DPLL54XX_ID_MAX, NULL);

	return dpll54xx_names[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll54xx_output_name_get
 * @BRIEF		return DPLL output name
 * @RETURNS		DPLL output name
 *			NULL in case of incorrect id
 * @param[in]		id: DPLL output ID
 * @DESCRIPTION		return DPLL output name
 *//*------------------------------------------------------------------------ */
const char *dpll54xx_output_name_get(dpll54xx_output_id id)
{
	CHECK_ARG_LESS_THAN(id, DPLL54XX_OUTPUT_ID_MAX, NULL);

	return dpll54xx_output_names[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hsdiv54xx_name_get
 * @BRIEF		return HS divider name
 * @RETURNS		HS divider name
 *			NULL in case of incorrect id
 * @param[in]		id: HS divider ID
 * @DESCRIPTION		return HS divider name
 *//*------------------------------------------------------------------------ */
const char *hsdiv54xx_name_get(hsdiv54xx_id id)
{
	CHECK_ARG_LESS_THAN(id, HSDIV54XX_ID_MAX, NULL);

	return hsdiv54xx_names[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll54xx_dump
 * @BRIEF		dump selected DPLL registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in, out]	stream: output stream
 * @param[in]		id: DPLL ID
 *			If id == DPLL54XX_ID_MAX, dump all DPLL registers.
 * @DESCRIPTION		dump selected DPLL registers and pretty-print it to
 *			output stream.
 *//*------------------------------------------------------------------------ */
int dpll54xx_dump(FILE *stream, dpll54xx_id id)
{
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row, i, val;
	int err = 0;
	dpll_settings_regs dpll_regs;
	dpll54xx_id dpll_id;
	reg *r;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(id, DPLL54XX_ID_MAX + 1, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(stream, OMAPCONF_ERR_ARG);

	for (dpll_id = DPLL54XX_MPU; dpll_id < DPLL54XX_ID_MAX; dpll_id++) {
		if ((id != DPLL54XX_ID_MAX) && (dpll_id != id))
			continue;
		else {
			autoadjust_table_init(table);
			row = 0;
			snprintf(table[row][0], TABLE_MAX_ELT_LEN,
				"%s Reg. Name",	dpll54xx_name_get(dpll_id));
			strncpy(table[row][1], "Reg. Address",
				TABLE_MAX_ELT_LEN);
			strncpy(table[row][2], "Reg. Value", TABLE_MAX_ELT_LEN);
			row++;

			if (cpu_revision_get() == REV_ES1_0)
				dpll_regs = dpll54xxes1_regs[dpll_id];
			else
				dpll_regs = dpll54xx_regs[dpll_id];
			for (i = 0; i < 10; i++) {
				switch (i) {
				case 0:
					r = dpll_regs.cm_clkmode_dpll;
					break;
				case 1:
					r = dpll_regs.cm_idlest_dpll;
					break;
				case 2:
					r = dpll_regs.cm_autoidle_dpll;
					break;
				case 3:
					r = dpll_regs.cm_clksel_dpll;
					break;
				case 4:
					r = dpll_regs.cm_bypclk_dpll;
					break;
				case 5:
					r = dpll_regs.cm_div_m2_dpll;
					break;
				case 6:
					r = dpll_regs.cm_div_m3_dpll;
					break;
				case 7:
					r = dpll_regs.cm_ssc_deltamstep_dpll;
					break;
				case 8:
					r = dpll_regs.cm_ssc_modfreqdiv_dpll;
					break;
				case 9:
					r = dpll_regs.cm_clkdcoldo_dpll;
					break;
				default:
					fprintf(stderr,
						"%s(): i=%u should have never "
						"happened?!\n", __func__, i);
				}

				if (r == NULL)
					continue;
				val = reg_read(r);
				/* Show register name, addr & content */
				snprintf(table[row][0],
					TABLE_MAX_ELT_LEN,
					"%s", r->name);
				snprintf(table[row][1],
					TABLE_MAX_ELT_LEN,
					"0x%08X", r->addr);
				snprintf(table[row][2],
					TABLE_MAX_ELT_LEN,
					"0x%08X", val);
				row++;
			}

			for (i = HSDIV54XX_H11; i < HSDIV54XX_ID_MAX; i++) {
				if (cpu_revision_get() == REV_ES1_0)
					r = (reg *) dpll54xxes1_hsdiv_regs[dpll_id][i];
				else
					r = (reg *) dpll54xx_hsdiv_regs[dpll_id][i];

				/* FIXME: import/export not yet implement */
				if (r == NULL)
					continue;
				val = reg_read(r);
				/* Show register name, addr & content */
				snprintf(table[row][0],
					TABLE_MAX_ELT_LEN,
					"%s", r->name);
				snprintf(table[row][1],
					TABLE_MAX_ELT_LEN,
					"0x%08X", r->addr);
				snprintf(table[row][2],
					TABLE_MAX_ELT_LEN,
					"0x%08X", val);
				row++;
			}

			autoadjust_table_print(table, row, 3);
		}
	}

	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll54xx_clk_sources_get
 * @BRIEF		retrieve DPLL input clock rates
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		settings: DPLL settings struct
 * @param[in]		ignore: do not consider DPLL STOP status.
 *			Useful for functions that needs the DPLL output
 *			frequencies even when DPLL is stopped
 *			(e.g. audit, clock tree, OPP detection, etc)
 * @DESCRIPTION		retrieve DPLL input clock rates
 *//*------------------------------------------------------------------------ */
int dpll54xx_clk_sources_get(dpll_settings *settings, unsigned short ignore)
{
	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(settings, OMAPCONF_ERR_ARG);

	if (dpll54xx_sources[settings->id].ref_clk != CLK54XX_ID_MAX)
		settings->fref = clk54xx_rate_get(
			(clk54xx_id) dpll54xx_sources[settings->id].ref_clk,
			ignore);
	else
		settings->fref = 0.0;

	if (dpll54xx_sources[settings->id].byp_clk_m2 != CLK54XX_ID_MAX)
		settings->fbyp_clk_m2 = clk54xx_rate_get(
			(clk54xx_id) dpll54xx_sources[settings->id].byp_clk_m2, ignore);
	else
		settings->fbyp_clk_m2 = 0.0;

	if (dpll54xx_sources[settings->id].byp_clk_m3 != CLK54XX_ID_MAX)
		settings->fbyp_clk_m3 = clk54xx_rate_get(
			(clk54xx_id) dpll54xx_sources[settings->id].byp_clk_m3, ignore);
	else
		settings->fbyp_clk_m3 = 0.0;

	if (dpll54xx_sources[settings->id].byp_clk_hsdiv != CLK54XX_ID_MAX)
		settings->fbyp_clk_hsdiv = clk54xx_rate_get(
			(clk54xx_id) dpll54xx_sources[settings->id].byp_clk_hsdiv, ignore);
	else
		settings->fbyp_clk_hsdiv = 0.0;

	dprintf("%s(): %s Fref=%lf MHz\n", __func__,
		dpll54xx_names[settings->id], settings->fref);
	dprintf("%s(): %s byp_clk_m2=%lf MHz\n", __func__,
		dpll54xx_names[settings->id], settings->fbyp_clk_m2);
	dprintf("%s(): %s byp_clk_m3=%lf MHz\n", __func__,
		dpll54xx_names[settings->id], settings->fbyp_clk_m3);
	dprintf("%s(): %s byp_clk_hsdiv=%lf MHz\n", __func__,
		dpll54xx_names[settings->id], settings->fbyp_clk_hsdiv);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hsdiv54xx_settings_extract
 * @BRIEF		extract OMAP5 HSDIV settings from registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		id: HSDIV valid ID
 * @param[in]		dpll_regs: dpll registers to extract from
 * @param[in, out]	settings: struct with extracted HSDIV settings
 * @DESCRIPTION		extract OMAP5 HSDIV settings from registers
 *//*------------------------------------------------------------------------ */
int hsdiv54xx_settings_extract(unsigned int id,
	 reg *hsdiv_reg, hsdiv54xx_settings *settings)
{
	unsigned int val;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(settings, OMAPCONF_ERR_ARG);

	settings->rate = 0.0;
	settings->id = (hsdiv54xx_id) id;

	if (hsdiv_reg == NULL) {
		settings->present = 0;
		settings->status = 0;
		settings->div = 1;
		dprintf("%s(): %s does not exist.\n", __func__,
			hsdiv54xx_name_get(id));
	} else {
		val = reg_read(hsdiv_reg);
		settings->present = 1;
		settings->div = extract_bitfield(val, 0, 6);
		settings->status = extract_bit(val, 9);
		dprintf("%s(): %s reg: %s = 0x%08X, DIV=%u, CLKST=%u\n",
			__func__, hsdiv54xx_name_get(id), hsdiv_reg->name, val,
			settings->div, settings->status);
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hsdiv54xx_rates_calc
 * @BRIEF		calculate DPLL HSDIV output rates
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		settings: DPLL settings struct
 * @param[in]		ignore: do not consider DPLL STOP status.
 *			Useful for functions that needs the DPLL output
 *			frequencies even when DPLL is stopped
 *			(e.g. audit, clock tree, OPP detection, etc)
 * @DESCRIPTION		calculate DPLL HSDIV output rates
 *//*------------------------------------------------------------------------ */
int hsdiv54xx_rates_calc(dpll54xx_settings *settings,
	unsigned short ignore)
{
	unsigned short i;
	dpll_status st;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(settings, OMAPCONF_ERR_ARG);

	/* Initialize all rates */
	for (i = 0; i < HSDIV54XX_ID_MAX; i++)
		(settings->hsdiv)[i].rate = 0.0;


	/* Determine DPLL outputs rate */
	if ((settings->status == DPLL_STATUS_STOPPED) && ignore) {
		st = DPLL_STATUS_LOCKED;
		dprintf("%s(): warning %s considered as locked\n", __func__,
			dpll54xx_name_get((settings->dpll).id));
	} else {
		st = settings->status;
	}

	switch (st) {
	case DPLL_STATUS_BYPASSED:
		for (i = 0; i < HSDIV54XX_ID_MAX; i++) {
			if ((settings->hsdiv)[i].present == 0)
				continue;
			(settings->hsdiv)[i].rate =
				(settings->dpll).fbyp_clk_hsdiv;
			dprintf("%s(): %s bypassed, %s=%lfMHz\n", __func__,
				dpll54xx_name_get((settings->dpll).id),
				hsdiv54xx_name_get(i),
				(settings->dpll).MN.M2_rate);
		}
		break;

	case DPLL_STATUS_LOCKED:
		for (i = 0; i < HSDIV54XX_ID_MAX; i++) {
			if ((settings->hsdiv)[i].present == 0)
				continue;
			/*
			 * Some 'nice' ES2.x HW hacks to handle ...
			 * There is an additional divider by 2,
			 * and special value '63' is actually a divider by 2.5.
			 */
			if ((cpu_revision_get() != REV_ES1_0) &&
					((settings->dpll).id == DPLL54XX_CORE) &&
					(i == HSDIV54XX_H14)) {
				if ((settings->hsdiv)[i].div != 63)
					(settings->hsdiv)[i].rate = (settings->dpll).fdpll /
						(double) (settings->hsdiv)[i].div / 2.0;
				else
					(settings->hsdiv)[i].rate = (settings->dpll).fdpll /
						2.5 / 2.0;
			} else {
				(settings->hsdiv)[i].rate = (settings->dpll).fdpll /
					(double) (settings->hsdiv)[i].div;
			}

			dprintf("%s(): %s locked, %s=%lfMHz\n", __func__,
				dpll54xx_name_get((settings->dpll).id),
				hsdiv54xx_name_get(i),
				(settings->dpll).MN.M2_rate);
		}
		break;

	case DPLL_STATUS_STOPPED:
		/* nothing to do, all HSDIV output rates already set to 0.0 */
		dprintf("%s(): %s stopped, all HSDIV rates=0.0MHz\n", __func__,
			dpll54xx_name_get((settings->dpll).id));
		break;

	default:
		fprintf(stderr, "%s(): incorrect %s status! (%u)\n", __func__,
			dpll54xx_names[(settings->dpll).id], st);
		return OMAPCONF_ERR_INTERNAL;
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll54xx_rates_calc
 * @BRIEF		calculate DPLL output rates
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		settings: DPLL settings struct
 * @param[in]		ignore: do not consider DPLL STOP status.
 *			Useful for functions that needs the DPLL output
 *			frequencies even when DPLL is stopped
 *			(e.g. audit, clock tree, OPP detection, etc)
 * @DESCRIPTION		calculate DPLL output rates
 *//*------------------------------------------------------------------------ */
int dpll54xx_rates_calc(dpll54xx_settings *settings,
	unsigned short ignore)
{
	dpll_status st;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(settings, OMAPCONF_ERR_ARG);

	/* Initialize all rates */
	(settings->dpll).fdpll = 0.0;
	(settings->dpll).MN.M2_rate = 0.0;
	(settings->dpll).MN.X2_M2_rate = 0.0;
	(settings->dpll).MN.X2_M3_rate = 0.0;
	(settings->dpll).MN.clkdcoldo_rate = 0.0;

	/* Compute DPLL lock frequency */
	dpll_lock_freq_calc(&(settings->dpll));
	dprintf("%s(): %s lock freq=%lfMHz\n", __func__,
		dpll54xx_name_get((settings->dpll).id), (settings->dpll).fdpll);

	/* Determine DPLL outputs rate */
	if ((settings->status == DPLL_STATUS_STOPPED) && ignore) {
		dprintf("%s(): warning %s considered as locked\n", __func__,
			dpll54xx_name_get((settings->dpll).id));
		st = DPLL_STATUS_LOCKED;
	} else {
		st = settings->status;
	}

	switch (st) {
	case DPLL_STATUS_BYPASSED:
		(settings->dpll).fdpll = 0.0;
		if ((settings->dpll).MN.M2_present == 0)
			goto m3_rate_bp_calc;
		(settings->dpll).MN.X2_M2_rate = (settings->dpll).fbyp_clk_m2;
		dprintf("%s(): %s bypassed, X2_M2=%lfMHz\n", __func__,
			dpll54xx_name_get((settings->dpll).id),
			(settings->dpll).MN.X2_M2_rate);
		(settings->dpll).MN.M2_rate = (settings->dpll).fbyp_clk_m2;
		dprintf("%s(): %s bypassed, M2=%lfMHz\n", __func__,
			dpll54xx_name_get((settings->dpll).id),
			(settings->dpll).MN.M2_rate);
		/*
		 * No bypass mode available for CLKDCOLDO output.
		 * clkdcoldo_rate already set to 0.0.
		 */
m3_rate_bp_calc:
		if ((settings->dpll).MN.M3_present == 0)
			break;
		(settings->dpll).MN.X2_M3_rate = (settings->dpll).fbyp_clk_m3 /
			(settings->dpll).MN.M3;
		dprintf("%s(): %s bypassed, X2_M3=%lfMHz\n", __func__,
			dpll54xx_name_get((settings->dpll).id),
			(settings->dpll).MN.X2_M3_rate);
		break;

	case DPLL_STATUS_LOCKED:
		if ((settings->dpll).MN.M2_present == 0)
			goto m3_rate_locked_calc;
		if ((settings->dpll).type == DPLL_TYPE_A) {
			(settings->dpll).MN.X2_M2_rate = (settings->dpll).fdpll
				/ (double) (settings->dpll).MN.M2;
			dprintf("%s(): %s locked, X2_M2=%lfMHz\n", __func__,
				dpll54xx_name_get((settings->dpll).id),
				(settings->dpll).MN.X2_M2_rate);
			if ((settings->dpll).DCC.en == 0)
				(settings->dpll).MN.M2_rate =
					(settings->dpll).MN.X2_M2_rate / 2.0;
			else
				(settings->dpll).MN.M2_rate =
					(settings->dpll).MN.X2_M2_rate;
			dprintf("%s(): %s locked, M2=%lfMHz\n", __func__,
				dpll54xx_name_get((settings->dpll).id),
				(settings->dpll).MN.M2_rate);
		} else {
			(settings->dpll).MN.M2_rate = (settings->dpll).fdpll /
				(double) (settings->dpll).MN.M2;
			(settings->dpll).MN.clkdcoldo_rate =
				(settings->dpll).fdpll;
			dprintf("%s(): %s locked, CLKOUT=%lfMHz "
				"CLKDCOLDO=%lfMHz\n", __func__,
				dpll54xx_name_get((settings->dpll).id),
				(settings->dpll).MN.M2_rate,
				(settings->dpll).MN.clkdcoldo_rate);
		}

m3_rate_locked_calc:
		if ((settings->dpll).MN.M3_present == 0)
			break;
		(settings->dpll).MN.X2_M3_rate = (settings->dpll).fdpll /
			(double) (settings->dpll).MN.M3;
		dprintf("%s(): %s locked, X2_M3=%lfMHz\n", __func__,
			dpll54xx_name_get((settings->dpll).id),
			(settings->dpll).MN.X2_M3_rate);
		break;

	case DPLL_STATUS_STOPPED:
		/* nothing to do, all output speeds already set to 0.0 */
		dprintf("%s(): %s stopped, all rates=0.0MHz\n", __func__,
			dpll54xx_name_get((settings->dpll).id));
		break;

	default:
		fprintf(stderr, "%s(): incorrect %s status! (%u)\n", __func__,
			dpll54xx_names[(settings->dpll).id], st);
		return OMAPCONF_ERR_INTERNAL;
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll54xx_settings_extract
 * @BRIEF		extract DPLL settings from registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	settings: struct with extracted DPLL settings
 * @param[in]		id: valid DPLL ID
 * @param[in]		ignore: do not consider DPLL STOP status.
 *			Useful for functions that needs the DPLL output
 *			frequencies even when DPLL is stopped
 *			(e.g. audit, clock tree, OPP detection, etc)
 * @DESCRIPTION		extract DPLL settings from registers
 *//*------------------------------------------------------------------------ */
int dpll54xx_settings_extract(dpll54xx_settings *settings,
	unsigned int id, unsigned short ignore)
{
	int ret;
	unsigned short i;
	unsigned int val;
	dpll_type type;
	dpll_settings_regs *dpll_regs;
	reg **hsdiv_regs;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(settings, OMAPCONF_ERR_ARG);

	switch (id) {
	case DPLL54XX_MPU:
	case DPLL54XX_IVA:
	case DPLL54XX_CORE:
	case DPLL54XX_PER:
	case DPLL54XX_ABE:
		type = DPLL_TYPE_A;
		break;
	case DPLL54XX_USB:
	case DPLL54XX_UNIPRO1:
	case DPLL54XX_UNIPRO2:
		type = DPLL_TYPE_B;
		break;
	default:
		return OMAPCONF_ERR_ARG;
	}

	dprintf("\n\n### %s() EXTRACTING %s SETTINGS (IGNORE=%u) ###\n",
		__func__, dpll54xx_name_get(id), ignore);

	if (cpu_revision_get() == REV_ES1_0) {
		dpll_regs = (dpll_settings_regs *) &(dpll54xxes1_regs[id]);
		hsdiv_regs = (reg **) dpll54xxes1_hsdiv_regs[id];
	} else {
		dpll_regs = (dpll_settings_regs *) &(dpll54xx_regs[id]);
		hsdiv_regs = (reg **) dpll54xx_hsdiv_regs[id];
	}

	ret = dpll_settings_extract(id, type, dpll_regs, &(settings->dpll));
	if (ret != 0)
		return ret;

	/* Set X2_M2_present flag (not register bit available) */
	switch ((dpll54xx_id) id) {
	case DPLL54XX_PER:
	case DPLL54XX_ABE:
		settings->dpll.MN.X2_M2_present = 1;
		break;

	case DPLL54XX_MPU:
	case DPLL54XX_IVA:
	case DPLL54XX_CORE:
	case DPLL54XX_USB:
	case DPLL54XX_UNIPRO1:
	case DPLL54XX_UNIPRO2:
	default:
		settings->dpll.MN.X2_M2_present = 0;
	}

	val = reg_read(dpll_regs->cm_idlest_dpll);
	dprintf("%s(): %s reg: %s = 0x%08X\n", __func__,
		dpll54xx_name_get(id),
		(dpll_regs->cm_idlest_dpll)->name, val);

	val = extract_bitfield(val, 1, 3);
	if ((settings->dpll).lock_status == 1) {
		settings->status = DPLL_STATUS_LOCKED;
	} else {
		switch (val) {
		case DPLL_LOW_POWER_STOP:
		case DPLL_FAST_RELOCK_STOP:
			settings->status = DPLL_STATUS_STOPPED;
			break;
		case DPLL_LOW_POWER_BYPASS:
		case DPLL_FAST_RELOCK_BYPASS:
			settings->status = DPLL_STATUS_BYPASSED;
			break;
		default:
			settings->status = DPLL_STATUS_MAX;
		}
	}
	dprintf("%s(): %s status: %s\n", __func__,
		dpll54xx_name_get(id),
		dpll_status_name_get(settings->status));

	for (i = HSDIV54XX_H11; i < HSDIV54XX_ID_MAX; i++) {
		ret = hsdiv54xx_settings_extract(i,
			hsdiv_regs[i], &((settings->hsdiv)[i]));
		if (ret != 0)
			return ret;
	}

	ret = dpll54xx_clk_sources_get(&(settings->dpll), ignore);
	if (ret != 0)
		return ret;
	ret = dpll54xx_rates_calc(settings, ignore);
	if (ret != 0)
		return ret;
	ret = hsdiv54xx_rates_calc(settings, ignore);
	if (ret != 0)
		return ret;

	(settings->dpll).initialized = 1;
	dprintf("### %s(): %s SETTINGS EXTRACTED (IGNORE=%u) ###\n",
		__func__, dpll54xx_name_get(id), ignore);

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll54xx_settings_get
 * @BRIEF		return DPLL settings struct pointer
 * @RETURNS		DPLL settings struct pointer in case of success
 *			NULL otherwise
 * @param[in]		id: valid DPLL ID
 * @param[in]		ignore: do not consider DPLL STOP status.
 *			Useful for functions that needs the DPLL output
 *			frequencies even when DPLL is stopped
 *			(e.g. audit, clock tree, OPP detection, etc)
 * @DESCRIPTION		return DPLL settings struct pointer
 *			If DPLL settings not yet extracted, do it.
 *//*------------------------------------------------------------------------ */
dpll54xx_settings *dpll54xx_settings_get(
	unsigned int id, unsigned short ignore)
{
	int ret;
	dpll54xx_settings *settings;

	CHECK_ARG_LESS_THAN(id, DPLL54XX_ID_MAX, NULL);

	/* Get struct pointer */
	if (ignore)
		settings = dpll54xx_locked_settings_table[id];
	else
		settings = dpll54xx_settings_table[id];

	/* If DPLL settings not yet extracted, do it */
	if ((settings->dpll).initialized == 0) {
		ret = dpll54xx_settings_extract(settings, id, ignore);
		if (ret < 0) {
			fprintf(stderr, "%s(): error while extracting %s "
				"parameters! (%d)", __func__,
				dpll54xx_name_get((dpll54xx_id) id), ret);
			settings = NULL;
		}
	}

	return settings;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll54xx_status_get
 * @BRIEF		return DPLL status.
 * @RETURNS		valid DPLL status (< DPLL_STATUS_MAX) in case of success
 *			DPLL_STATUS_MAX in case of error
 * @param[in]		id: valid DPLL ID
 * @DESCRIPTION		return DPLL status.
 *			If DPLL settings not yet extracted, do it.
 *//*------------------------------------------------------------------------ */
dpll_status dpll54xx_status_get(dpll54xx_id id)
{
	dpll54xx_settings *settings;
	int ret;

	CHECK_ARG_LESS_THAN(id, DPLL54XX_ID_MAX, DPLL_STATUS_MAX);

	/* Get struct pointer */
	settings = dpll54xx_settings_table[id];

	/* If DPLL settings not yet extracted, do it */
	if ((settings->dpll).initialized == 0) {
		ret = dpll54xx_settings_extract(settings, id, 0);
		if (ret < 0) {
			fprintf(stderr, "%s(): error while extracting %s "
				"parameters! (%d)", __func__,
				dpll54xx_name_get(id), ret);
			return DPLL_STATUS_MAX;
		}
	}

	/* Return DPLL status */
	return settings->status;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll54xx_output_rate_get
 * @BRIEF		return DPLL output clock rate (in MHz).
 * @RETURNS		DPLL output clock rate (in MHz) in case of success
 *			0.0 otherwise
 * @param[in]		id: valid DPLL ID
 * @param[in]		out_id: valid DPLL OUTPUT ID
 * @param[in]		ignore: do not consider DPLL STOP status.
 *			Useful for functions that needs the DPLL output
 *			frequencies even when DPLL is stopped
 *			(e.g. audit, clock tree, OPP detection, etc)
 * @DESCRIPTION		return DPLL output clock rate (in MHz).
 *			If DPLL settings not yet extracted, do it.
 *//*------------------------------------------------------------------------ */
double dpll54xx_output_rate_get(
	dpll54xx_id id, dpll54xx_output_id out_id, unsigned short ignore)
{
	int ret;
	dpll54xx_settings *settings;
	double rate;

	CHECK_ARG_LESS_THAN(id, DPLL54XX_ID_MAX, 0.0);
	CHECK_ARG_LESS_THAN(out_id, DPLL54XX_OUTPUT_ID_MAX, 0.0);

	/* Get struct pointer */
	if (ignore)
		settings = dpll54xx_locked_settings_table[id];
	else
		settings = dpll54xx_settings_table[id];

	/* If DPLL settings not yet extracted, do it */
	if ((settings->dpll).initialized == 0) {
		ret = dpll54xx_settings_extract(settings, id, ignore);
		if (ret < 0) {
			fprintf(stderr, "%s(): error while extracting %s "
				"parameters! (%d)", __func__,
				dpll54xx_name_get(id), ret);
			rate = 0.0;
			goto dpll54xx_output_rate_get_end;
		}
	}

	/* Get output rate */
	switch (out_id) {
	case DPLL54XX_CLKOUT_M2:
		rate = (settings->dpll).MN.M2_rate;
		break;
	case DPLL54XX_CLKOUTX2_M2:
		rate = (settings->dpll).MN.X2_M2_rate;
		break;
	case DPLL54XX_CLKOUTX2_M3:
		rate = (settings->dpll).MN.X2_M3_rate;
		break;
	case DPLL54XX_CLKOUTX2_H11:
		rate = (settings->hsdiv)[HSDIV54XX_H11].rate;
		break;
	case DPLL54XX_CLKOUTX2_H12:
		rate = (settings->hsdiv)[HSDIV54XX_H12].rate;
		break;
	case DPLL54XX_CLKOUTX2_H13:
		rate = (settings->hsdiv)[HSDIV54XX_H13].rate;
		break;
	case DPLL54XX_CLKOUTX2_H14:
		rate = (settings->hsdiv)[HSDIV54XX_H14].rate;
		break;
	case DPLL54XX_CLKOUTX2_H21:
		rate = (settings->hsdiv)[HSDIV54XX_H21].rate;
		break;
	case DPLL54XX_CLKOUTX2_H22:
		rate = (settings->hsdiv)[HSDIV54XX_H22].rate;
		break;
	case DPLL54XX_CLKOUTX2_H23:
		rate = (settings->hsdiv)[HSDIV54XX_H23].rate;
		break;
	case DPLL54XX_CLKOUTX2_H24:
		rate = (settings->hsdiv)[HSDIV54XX_H24].rate;
		break;
	case DPLL54XX_CLK_DCO_LDO:
		rate = (settings->dpll).MN.clkdcoldo_rate;
		break;
	default:
		/* should never happen, to remove compilation warning */
		rate = 0.0;

	}

dpll54xx_output_rate_get_end:
	dprintf("%s(%s, %s, %u)=%lfMHz\n", __func__,
		dpll54xx_name_get(id),
		dpll54xx_output_name_get(out_id),
		ignore, rate);
	return rate;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll54xx_show
 * @BRIEF		analyze PLLs configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_UNEXPECTED
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		stream: output stream
 * @DESCRIPTION		analyze PLLs configuration
 *//*------------------------------------------------------------------------ */
int dpll54xx_show(FILE *stream)
{
	int ret = 0;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row, row_max;
	dpll54xx_id id;
	hsdiv54xx_id hsdiv_id;
	dpll54xx_settings *settings, *settings_locked;

	autoadjust_table_init(table);
	row = 0;
	row_max = 0;
	strncpy(table[row][0], "DPLL Configuration", TABLE_MAX_ELT_LEN);

	for (id = DPLL54XX_USB; id < DPLL54XX_ID_MAX; id++) {
		row = 0;
		snprintf(table[row++][id - DPLL54XX_USB + 1],
			TABLE_MAX_ELT_LEN, "%s",
			dpll54xx_name_get(id));
		settings = dpll54xx_settings_get(id, 0);
		if (settings == NULL) {
			fprintf(stderr, "%s(): error while getting %s "
				"parameters! (%d)", __func__,
				dpll54xx_name_get(id), ret);
			return OMAPCONF_ERR_UNEXPECTED;
		}

		/*
		 * Also get DPLL params ignoring DPLL STOPPED status to also
		 * show all output speeds when DPLL is locked.
		 */
		settings_locked = dpll54xx_settings_get(id, 1);
		if (settings_locked == NULL) {
			fprintf(stderr, "%s(): error while getting %s "
				"locked parameters! (%d)", __func__,
				dpll54xx_name_get(id), ret);
			return OMAPCONF_ERR_UNEXPECTED;
		}

		strncpy(table[row][0], "Status", TABLE_MAX_ELT_LEN);;
		strncpy(table[row][id - DPLL54XX_USB + 1],
			dpll_status_name_get(settings->status),
			TABLE_MAX_ELT_LEN);
		row += 2;

		strncpy(table[row][0], "Mode", TABLE_MAX_ELT_LEN);
		strncpy(table[row++][id - DPLL54XX_USB + 1],
			dpll_mode_name_get(settings->dpll.mode),
			TABLE_MAX_ELT_LEN);

		strncpy(table[row][0], "Automatic Control", TABLE_MAX_ELT_LEN);
		strncpy(table[row++][id - DPLL54XX_USB + 1],
			dpll_autoidle_mode_name_get(
				settings->dpll.autoidle_mode),
			TABLE_MAX_ELT_LEN);

		strncpy(table[row++][0], " LPST = Low-Power STop",
			TABLE_MAX_ELT_LEN);
		strncpy(table[row++][0], " FRST = Fast-Relock STop",
			TABLE_MAX_ELT_LEN);
		strncpy(table[row++][0], " LPBP = Low-Power ByPass",
			TABLE_MAX_ELT_LEN);
		strncpy(table[row++][0], " FRBP = Fast-Relock ByPass",
			TABLE_MAX_ELT_LEN);
		strncpy(table[row++][0], " MNBP = MN ByPass",
			TABLE_MAX_ELT_LEN);
		row++;

		strncpy(table[row][0], "Sigma-Delta Divider",
			TABLE_MAX_ELT_LEN);
		snprintf(table[row++][id - DPLL54XX_USB + 1],
			TABLE_MAX_ELT_LEN, "%u",
			settings->dpll.sd_div);
		strncpy(table[row][0], "SELFREQDCO",
			TABLE_MAX_ELT_LEN);
		snprintf(table[row++][id - DPLL54XX_USB + 1],
			TABLE_MAX_ELT_LEN, "%u", settings->dpll.selfreqdco);
		row++;

		strncpy(table[row][0], "Ref. Frequency (MHz)",
			TABLE_MAX_ELT_LEN);
		snprintf(table[row++][id - DPLL54XX_USB + 1],
			TABLE_MAX_ELT_LEN, "%.3lf", settings->dpll.fref);
		strncpy(table[row][0], "M Multiplier Factor",
			TABLE_MAX_ELT_LEN);
		snprintf(table[row++][id - DPLL54XX_USB + 1],
			TABLE_MAX_ELT_LEN, "%u",
			settings->dpll.MN.M);

		strncpy(table[row][0], "N Divider Factor", TABLE_MAX_ELT_LEN);
		snprintf(table[row++][id - DPLL54XX_USB + 1],
			TABLE_MAX_ELT_LEN, "%u",
			settings->dpll.MN.N);

		strncpy(table[row][0], "Lock Frequency (MHz)",
			TABLE_MAX_ELT_LEN);
		if (settings->status == DPLL_STATUS_LOCKED)
			snprintf(table[row][id - DPLL54XX_USB + 1],
			TABLE_MAX_ELT_LEN,
			"%u", (unsigned int) settings->dpll.fdpll);
		else
			snprintf(table[row][id - DPLL54XX_USB + 1],
			TABLE_MAX_ELT_LEN,
				"%u (%u)",
				(unsigned int) settings->dpll.fdpll,
				(unsigned int) settings_locked->dpll.fdpll);
		row += 2;

		strncpy(table[row][0], "CLKOUT Output", TABLE_MAX_ELT_LEN);
		row++;
		strncpy(table[row][0], "  Status", TABLE_MAX_ELT_LEN);
		strncpy(table[row++][id - DPLL54XX_USB + 1],
			(settings->dpll.MN.M2_clkout_st == 1) ?
				"Enabled" : "Gated",
				TABLE_MAX_ELT_LEN);
		strncpy(table[row][0], "  Clock Divider",
			TABLE_MAX_ELT_LEN);
		snprintf(table[row++][id - DPLL54XX_USB + 1],
			TABLE_MAX_ELT_LEN,
			"%-5u (x%d)", settings->dpll.MN.M2,
			(settings->dpll.DCC.en == 1) ? 1 : 2);
		strncpy(table[row][0], "  Clock Speed (MHz)",
			TABLE_MAX_ELT_LEN);
		if (settings->status == DPLL_STATUS_LOCKED)
			snprintf(table[row++][id - DPLL54XX_USB + 1],
				TABLE_MAX_ELT_LEN, "%u",
				(unsigned int) settings->dpll.MN.M2_rate);
		else
			snprintf(table[row++][id - DPLL54XX_USB + 1],
				TABLE_MAX_ELT_LEN, "%u (%u)",
				(unsigned int) settings->dpll.MN.M2_rate,
				(unsigned int) settings_locked->dpll.MN.M2_rate);
		row++;

		strncpy(table[row++][0],
			"CLK_DCO_LDO Output", TABLE_MAX_ELT_LEN);
		strncpy(table[row][0], "  Status",
			TABLE_MAX_ELT_LEN);
		strncpy(table[row++][id - DPLL54XX_USB + 1],
			(settings->dpll.MN.clkdcoldo_clkout_st == 1)
				? "Enabled" : "Gated",
				TABLE_MAX_ELT_LEN);
		strncpy(table[row][0], "  Clock Speed (MHz)",
			TABLE_MAX_ELT_LEN);
		if (settings->status == DPLL_STATUS_LOCKED)
			snprintf(table[row++][id - DPLL54XX_USB + 1],
				TABLE_MAX_ELT_LEN, "%u",
				(unsigned int) settings->dpll.MN.clkdcoldo_rate);
		else
			snprintf(table[row++][id - DPLL54XX_USB + 1],
				TABLE_MAX_ELT_LEN, "%u (%u)",
				(unsigned int) settings->dpll.MN.clkdcoldo_rate,
				(unsigned int) settings_locked->dpll.MN.clkdcoldo_rate);

		if (row > row_max)
			row_max = row;
	}

	if (stream != NULL)
		autoadjust_table_fprint(stream,
			table, row_max, DPLL54XX_ID_MAX - DPLL54XX_USB + 1);

	autoadjust_table_init(table);
	row = 0;
	row_max = 0;
	strncpy(table[row][0], "DPLL Configuration", TABLE_MAX_ELT_LEN);

	for (id = DPLL54XX_MPU; id < DPLL54XX_USB; id++) {
		row = 0;
		snprintf(table[row++][id + 1], TABLE_MAX_ELT_LEN, "%s",
			dpll54xx_name_get(id));
		settings = dpll54xx_settings_get(id, 0);
		if (settings == NULL) {
			fprintf(stderr, "%s(): error while getting %s "
				"parameters! (%d)", __func__,
				dpll54xx_name_get(id), ret);
			return OMAPCONF_ERR_UNEXPECTED;
		}

		/*
		 * Also get DPLL params ignoring DPLL STOPPED status to also
		 * show all output speeds when DPLL is locked.
		 */
		settings_locked = dpll54xx_settings_get(id, 1);
		if (settings_locked == NULL) {
			fprintf(stderr, "%s(): error while getting %s "
				"locked parameters! (%d)", __func__,
				dpll54xx_name_get(id), ret);
			return OMAPCONF_ERR_UNEXPECTED;
		}

		strncpy(table[row][0], "Status", TABLE_MAX_ELT_LEN);;
		strncpy(table[row][id + 1],
			dpll_status_name_get(settings->status),
			TABLE_MAX_ELT_LEN);
		row += 2;

		strncpy(table[row][0], "Mode", TABLE_MAX_ELT_LEN);
		strncpy(table[row++][id + 1],
			dpll_mode_name_get(settings->dpll.mode),
			TABLE_MAX_ELT_LEN);

		strncpy(table[row][0], "Automatic Control", TABLE_MAX_ELT_LEN);
		strncpy(table[row++][id + 1],
			dpll_autoidle_mode_name_get(
				settings->dpll.autoidle_mode),
			TABLE_MAX_ELT_LEN);

		strncpy(table[row++][0], " LPST = Low-Power STop",
			TABLE_MAX_ELT_LEN);
		strncpy(table[row++][0], " FRST = Fast-Relock STop",
			TABLE_MAX_ELT_LEN);
		strncpy(table[row++][0], " LPBP = Low-Power ByPass",
			TABLE_MAX_ELT_LEN);
		strncpy(table[row++][0], " FRBP = Fast-Relock ByPass",
			TABLE_MAX_ELT_LEN);
		strncpy(table[row++][0], " MNBP = MN ByPass",
			TABLE_MAX_ELT_LEN);

		strncpy(table[row][0], "Low-Power Mode", TABLE_MAX_ELT_LEN);
		strncpy(table[row][id + 1],
			(settings->dpll.lpmode_en == 1) ?
				"Enabled" : "Disabled",
			TABLE_MAX_ELT_LEN);
		row += 2;

		strncpy(table[row][0], "Automatic Recalibration",
			TABLE_MAX_ELT_LEN);
		strncpy(table[row++][id + 1],
			(settings->dpll.driftguard_en == 1) ?
			"Enabled" : "Disabled",	TABLE_MAX_ELT_LEN);

		strncpy(table[row][0], "Clock Ramping during Relock",
				TABLE_MAX_ELT_LEN);
		strncpy(table[row++][id + 1],
			(settings->dpll.ramp.relock_ramp_en == 1) ?
			"Enabled" : "Disabled", TABLE_MAX_ELT_LEN);

		strncpy(table[row][0], "Ramping Rate (x REFCLK(s))",
			TABLE_MAX_ELT_LEN);
		snprintf(table[row++][id + 1], TABLE_MAX_ELT_LEN, "%u",
			settings->dpll.ramp.ramp_rate);

		strncpy(table[row][0], "Ramping Levels", TABLE_MAX_ELT_LEN);
		strncpy(table[row][id + 1],
			dpll_ramp_level_name_get((dpll_ramp_level)
				settings->dpll.ramp.ramp_level),
			TABLE_MAX_ELT_LEN);
		row += 2;

		strncpy(table[row][0], "Bypass Clock", TABLE_MAX_ELT_LEN);
		strncpy(table[row++][id + 1],
			dpll_bp_clk_src_name_get((dpll_bp_clk_src)
				settings->dpll.bypass_clk),
			TABLE_MAX_ELT_LEN);

		strncpy(table[row][0], "Bypass Clock Divider",
			TABLE_MAX_ELT_LEN);
		if (cpu_revision_get() == REV_ES1_0) {
			if (dpll54xxes1_regs[id].cm_bypclk_dpll != NULL)
				snprintf(table[row][id + 1], TABLE_MAX_ELT_LEN,
				"%u", settings->dpll.bypass_clk_div);
		} else {
			if (dpll54xx_regs[id].cm_bypclk_dpll != NULL)
				snprintf(table[row][id + 1], TABLE_MAX_ELT_LEN,
				"%u", settings->dpll.bypass_clk_div);
		}
		row++;

		strncpy(table[row][0], "REGM4XEN Mode",
			TABLE_MAX_ELT_LEN);
		if (settings->dpll.regm4xen == 0)
			snprintf(table[row][id + 1], TABLE_MAX_ELT_LEN,
				"Disabled");
		else
			snprintf(table[row][id + 1], TABLE_MAX_ELT_LEN,
				"Enabled");
		row++;

		strncpy(table[row][0], "Duty Cycle Correction (DCC)",
			TABLE_MAX_ELT_LEN);

		if ((id == DPLL54XX_MPU) && (settings->dpll.DCC.en == 1)) {
			snprintf(table[row][id + 1],
				TABLE_MAX_ELT_LEN,
				"Enabled");
		} else {
			snprintf(table[row][id + 1],
				TABLE_MAX_ELT_LEN,
				"Disabled");
		}
		row += 2;

		strncpy(table[row][0], "Ref. Frequency (MHz)",
			TABLE_MAX_ELT_LEN);
		snprintf(table[row++][id + 1],
			TABLE_MAX_ELT_LEN, "%.3lf", settings->dpll.fref);
		strncpy(table[row][0], "M Multiplier Factor",
			TABLE_MAX_ELT_LEN);
		snprintf(table[row++][id + 1], TABLE_MAX_ELT_LEN, "%u",
			settings->dpll.MN.M);

		strncpy(table[row][0], "N Divider Factor", TABLE_MAX_ELT_LEN);
		snprintf(table[row++][id + 1], TABLE_MAX_ELT_LEN, "%u",
			settings->dpll.MN.N);

		strncpy(table[row][0], "Lock Frequency (MHz)",
			TABLE_MAX_ELT_LEN);
		if (settings->status == DPLL_STATUS_LOCKED)
			snprintf(table[row][id + 1], TABLE_MAX_ELT_LEN,
			"%u", (unsigned int) settings->dpll.fdpll);
		else
			snprintf(table[row][id + 1], TABLE_MAX_ELT_LEN,
				"%u (%u)",
				(unsigned int) settings->dpll.fdpll,
				(unsigned int) settings_locked->dpll.fdpll);
		row += 2;
		strncpy(table[row][0], "M2 Output", TABLE_MAX_ELT_LEN);
		row++;

		if (settings->dpll.MN.M2_present) {
			strncpy(table[row][0], "  Status", TABLE_MAX_ELT_LEN);
			strncpy(table[row++][id + 1],
				(settings->dpll.MN.M2_clkout_st == 1) ?
					"Enabled" : "Gated",
					TABLE_MAX_ELT_LEN);
			strncpy(table[row][0], "  Clock Divider",
				TABLE_MAX_ELT_LEN);
			snprintf(table[row++][id + 1], TABLE_MAX_ELT_LEN,
				"%-5u (x2)", settings->dpll.MN.M2);
			strncpy(table[row][0], "  Clock Speed (MHz)",
				TABLE_MAX_ELT_LEN);
			if (settings->status == DPLL_STATUS_LOCKED)
				snprintf(table[row++][id + 1],
					TABLE_MAX_ELT_LEN, "%u",
					(unsigned int) settings->dpll.MN.M2_rate);
			else
				snprintf(table[row++][id + 1],
				TABLE_MAX_ELT_LEN, "%u (%u)",
				(unsigned int) settings->dpll.MN.M2_rate,
				(unsigned int) settings_locked->dpll.MN.M2_rate);
		} else {
			row += 3;
		}
		row++;



		strncpy(table[row++][0], "X2_M2 Output", TABLE_MAX_ELT_LEN);
		if (settings->dpll.MN.X2_M2_present) {
			strncpy(table[row][0], "  Status", TABLE_MAX_ELT_LEN);
			strncpy(table[row++][id + 1],
				(settings->dpll.MN.X2_M2_clkout_st == 1) ?
					"Enabled" : "Gated",
					TABLE_MAX_ELT_LEN);
			strncpy(table[row][0], "  Clock Divider",
				TABLE_MAX_ELT_LEN);
			snprintf(table[row++][id + 1], TABLE_MAX_ELT_LEN,
				"%-5u", settings->dpll.MN.M2);
			strncpy(table[row][0], "  Clock Speed (MHz)",
				TABLE_MAX_ELT_LEN);
			if (settings->status == DPLL_STATUS_LOCKED)
				snprintf(table[row++][id + 1],
					TABLE_MAX_ELT_LEN, "%u",
					(unsigned int) settings->dpll.MN.X2_M2_rate);
			else
				snprintf(table[row++][id + 1],
					TABLE_MAX_ELT_LEN, "%u (%u)",
					(unsigned int) settings->dpll.MN.X2_M2_rate,
					(unsigned int)
						settings_locked->dpll.MN.X2_M2_rate);
		} else {
			row += 3;
		}
		row++;

		strncpy(table[row++][0], "X2_M3 Output", TABLE_MAX_ELT_LEN);
		if (settings->dpll.MN.M3_present) {
			if (id != DPLL54XX_MPU) {
				strncpy(table[row][0], "  Status",
					TABLE_MAX_ELT_LEN);
				strncpy(table[row++][id + 1],
					(settings->dpll.MN.X2_M3_clkout_st == 1)
						? "Enabled" : "Gated",
						TABLE_MAX_ELT_LEN);
			}
			strncpy(table[row][0], "  Clock Divider",
				TABLE_MAX_ELT_LEN);
			snprintf(table[row++][id + 1], TABLE_MAX_ELT_LEN,
				"%-5u", settings->dpll.MN.M3);
			strncpy(table[row][0], "  Clock Speed (MHz)",
				TABLE_MAX_ELT_LEN);
			if (settings->status == DPLL_STATUS_LOCKED)
				snprintf(table[row++][id + 1],
					TABLE_MAX_ELT_LEN, "%u",
					(unsigned int) settings->dpll.MN.X2_M3_rate);
			else
				snprintf(table[row++][id + 1],
				TABLE_MAX_ELT_LEN, "%u (%u)",
				(unsigned int) settings->dpll.MN.X2_M3_rate,
				(unsigned int) settings_locked->dpll.MN.X2_M3_rate);
		} else {
			row += 3;
		}

		for (hsdiv_id = HSDIV54XX_H11; hsdiv_id < HSDIV54XX_ID_MAX; hsdiv_id++) {
			if ((cpu_revision_get() == REV_ES1_0) &&
				((hsdiv_id == HSDIV54XX_H21) || (hsdiv_id == HSDIV54XX_H24)))
				/* Never used */
				continue;

			row++;
			if ((settings->hsdiv)[hsdiv_id].present == 0) {
				row += 4;
			} else {
				snprintf(table[row++][0], TABLE_MAX_ELT_LEN,
					"%s Output",
					hsdiv54xx_name_get(hsdiv_id));
				strncpy(table[row][0], "  Status",
					TABLE_MAX_ELT_LEN);
				strncpy(table[row++][id + 1],
				((settings->hsdiv)[hsdiv_id].status == 1) ?
					"Enabled" : "Gated", TABLE_MAX_ELT_LEN);
				strncpy(table[row][0], "  Clock Divider",
					TABLE_MAX_ELT_LEN);
				/*
				 * Some 'nice' ES2.x HW hacks to handle ...
				 * There is an additional divider by 2,
				 * and special value '63' is actually a divider
				 * by 2.5.
				 */
				if ((cpu_revision_get() != REV_ES1_0) &&
					(id == DPLL54XX_CORE) &&
					(hsdiv_id == HSDIV54XX_H14)) {
					if ((settings->hsdiv)[hsdiv_id].div != 63)
						snprintf(table[row++][id + 1],
							TABLE_MAX_ELT_LEN,
							"%u (%u*2)",
							2 * (settings->hsdiv)[hsdiv_id].div,
							(settings->hsdiv)[hsdiv_id].div);
					else
						snprintf(table[row++][id + 1],
							TABLE_MAX_ELT_LEN,
							"2.5 (63)");
				} else {
					snprintf(table[row++][id + 1],
						TABLE_MAX_ELT_LEN,
						"%u",
						(settings->hsdiv)[hsdiv_id].div);
				}
				strncpy(table[row][0], "  Clock Speed (MHz)",
					TABLE_MAX_ELT_LEN);
				if (settings->status == DPLL_STATUS_LOCKED)
					snprintf(table[row++][id + 1],
						TABLE_MAX_ELT_LEN, "%u",
						(unsigned int) (settings->hsdiv)[hsdiv_id].rate);
				else
					snprintf(table[row++][id + 1],
					TABLE_MAX_ELT_LEN, "%u (%u)",
					(unsigned int) (settings->hsdiv)[hsdiv_id].rate,
					(unsigned int) (settings_locked->hsdiv)[hsdiv_id].rate);
			}
		}

		if (row > row_max)
			row_max = row;

	}

	if (stream != NULL)
		autoadjust_table_fprint(stream,
			table, row_max, DPLL54XX_ABE + 2);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll54xx_audit
 * @BRIEF		OMAP5 DPLLS settings audit.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		dpll_id: ID of the DPLL to be audited
 * @param[in]		opp_id: if != OPP54XX_ID_MAX,
 *			force audit at that given OPP
 * @param[in,out]	stream: output file - NULL: no output (silent)
 * @param[in,out]	err_nbr: pointer to return audit error number
 * @param[in,out]	wng_nbr: pointer to return audit warning number
 * @DESCRIPTION		OMAP5 DPLLS settings audit.
 *//*------------------------------------------------------------------------ */
int dpll54xx_audit(dpll54xx_id dpll_id, opp54xx_id opp_id,
	FILE *stream, unsigned int *err_nbr, unsigned int *wng_nbr)
{
	int ret = 0;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row;
	dpll54xx_id id;
	hsdiv54xx_id hsdiv_id;
	dpll54xx_settings *settings;
	dpll54xx_audited_settings *golden_settings;
	const char *opp_s;
	int opp_mpu, opp_mm, opp_core, opp;
	double sysclk;

	CHECK_ARG_LESS_THAN(dpll_id, DPLL54XX_ID_MAX + 1, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(opp_id, OPP54XX_ID_MAX + 1, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(err_nbr, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(wng_nbr, OMAPCONF_ERR_ARG);

	*err_nbr = 0;
	*wng_nbr = 0;
	sysclk = clk54xx_sysclk_rate_get();

	if (opp_id != OPP54XX_ID_MAX) {
		if (stream != NULL)
			fprintf(stream, "WARNING: using forced OPP %s!\n\n",
				opp54xx_name_get(opp_id));
		opp_mpu = opp_id;
		opp_mm = opp_id;
		opp_core = opp_id;
		(*wng_nbr)++;
	} else {
		opp_s = opp_get(VDD_MPU, 1);
		if (opp_s == NULL)
			opp_mpu = OPP54XX_ID_MAX;
		else
			opp_mpu = opp_s2id(opp_s);
		opp_s = opp_get(VDD_MM, 1);
		if (opp_s == NULL)
			opp_mm = OPP54XX_ID_MAX;
		else
			opp_mm = opp_s2id(opp_s);
		opp_s = opp_get(VDD_CORE, 1);
		if (opp_s == NULL)
			opp_core = OPP54XX_ID_MAX;
		else
			opp_core = opp_s2id(opp_s);

		if ((opp_mpu == OPP54XX_ID_MAX) || (opp_mm == OPP54XX_ID_MAX) ||
			(opp_core == OPP54XX_ID_MAX)) {
			if (stream != NULL) {
				fprintf(stream,
					"Sorry, OPP could not be detected, audit cannot be completed.\n");
				fprintf(stream,
					"Option \"-opp [dpll_casc|low|nom|high|speedbin]\" may be considered until OPP correctly setup.\n\n");
			}
			(*err_nbr)++;
			ret = OMAPCONF_ERR_NOT_AVAILABLE;
			goto dpll54xx_audit_end;
		}
	}

	for (id = DPLL54XX_MPU; id < DPLL54XX_ID_MAX; id++) {
		if ((dpll_id != DPLL54XX_ID_MAX) && (dpll_id != id))
			continue;

		switch (id) {
		case DPLL54XX_MPU:
			opp = opp_mpu;
			break;
		case DPLL54XX_IVA:
			opp = opp_mm;
			break;
		default:
			opp = opp_core;
		}

		autoadjust_table_init(table);
		row = 0;
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"%s AUDIT (@OPP %s, sysclk=%.1lfMHz)",
			dpll54xx_name_get(id), opp54xx_name_get(opp), sysclk);
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "Current Setting");
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "Expected");
		snprintf(table[row++][3], TABLE_MAX_ELT_LEN, "STATUS");

		settings = dpll54xx_settings_get(id, 0);
		if (settings == NULL) {
			fprintf(stderr, "%s(): error while getting %s "
				"parameters! (%d)", __func__,
				dpll54xx_name_get(id), ret);
			(*err_nbr)++;
			ret = OMAPCONF_ERR_INTERNAL;
			goto dpll54xx_audit_end;
		}

		if (sysclk == 19.2) {
			if (cpu_revision_get() == REV_ES1_0) {
				if ((dpll54xx_audited_settings **)
					dpll54xxes1_golden_settings_19_2MHz_table[id] == NULL) {
					if (stream != NULL)
						fprintf(stream,
							"WARNING: golden settings not available for %s.\n\n",
							dpll54xx_name_get(id));
					(*err_nbr)++;
					ret = OMAPCONF_ERR_NOT_AVAILABLE;
					goto dpll54xx_audit_end;
				}
				golden_settings =
					dpll54xxes1_golden_settings_19_2MHz_table[id][opp];
			} else if (cpu_is_omap5430()) {
				if ((dpll54xx_audited_settings **)
					dpll54xxes2_golden_settings_19_2MHz_table[id] == NULL) {
					if (stream != NULL)
						fprintf(stream,
							"WARNING: golden settings not available for %s.\n\n",
							dpll54xx_name_get(id));
					(*err_nbr)++;
					ret = OMAPCONF_ERR_NOT_AVAILABLE;
					goto dpll54xx_audit_end;
				}
				golden_settings =
					dpll54xxes2_golden_settings_19_2MHz_table[id][opp];
			} else if (strcmp(opp_get(VDD_MM, 1), OPP_HIGH) == 0) {
				/* 5432 + VDD_MM == OPP_HIGH */
				if ((dpll54xx_audited_settings **)
					dpll5432es2_vdd_mm_hi_golden_settings_19_2MHz_table[id] == NULL) {
					if (stream != NULL)
						fprintf(stream,
							"WARNING: golden settings not available for %s.\n\n",
							dpll54xx_name_get(id));
					(*err_nbr)++;
					ret = OMAPCONF_ERR_NOT_AVAILABLE;
					goto dpll54xx_audit_end;
				}
				golden_settings =
					dpll5432es2_vdd_mm_hi_golden_settings_19_2MHz_table[id][opp];
			} else {
				/* 5432 + VDD_MM == OPP_NOM */
				if ((dpll54xx_audited_settings **)
					dpll5432es2_golden_settings_19_2MHz_table[id] == NULL) {
					if (stream != NULL)
						fprintf(stream,
							"WARNING: golden settings not available for %s.\n\n",
							dpll54xx_name_get(id));
					(*err_nbr)++;
					ret = OMAPCONF_ERR_NOT_AVAILABLE;
					goto dpll54xx_audit_end;
				}
				golden_settings =
					dpll5432es2_golden_settings_19_2MHz_table[id][opp];
			}
		} else if (sysclk == 38.4) {
			if ((dpll54xx_audited_settings **)
				dpll54xx_golden_settings_38_4MHz_table[id] == NULL) {
				if (stream != NULL)
					fprintf(stream,
						"WARNING: golden settings not "
						"available for %s.\n\n",
						dpll54xx_name_get(id));
				(*err_nbr)++;
				ret = OMAPCONF_ERR_NOT_AVAILABLE;
				goto dpll54xx_audit_end;
			}
			golden_settings =
				dpll54xx_golden_settings_38_4MHz_table[id][opp];
		} else {
			if (stream != NULL)
				fprintf(stream,
					"WARNING: golden settings not "
					"available for %.1lfMHz sysclk.\n\n",
					sysclk);
			(*err_nbr)++;
			ret = OMAPCONF_ERR_NOT_AVAILABLE;
			goto dpll54xx_audit_end;
		}

		if (golden_settings == NULL) {
			if (stream != NULL)
				fprintf(stream,
					"WARNING: golden settings not "
					"available for this device.\n\n");
			(*err_nbr)++;
			ret = OMAPCONF_ERR_NOT_AVAILABLE;
			goto dpll54xx_audit_end;
		}

		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "Status");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
			dpll_status_name_get(settings->status));
		DPLL54XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->status,
			DPLL_STATUS_MAX, dpll54xx_audit_mode);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
			dpll_status_name_get(golden_settings->status));
		DPLL54XX_AUDIT_SHOW_STATUS(settings->status,
				golden_settings->status);

		if (golden_settings->status == DPLL_STATUS_STOPPED)
			/* All other DPLL settings are not relevant */
			goto dpll54xx_audit_table_show;

		if (settings->status == DPLL_STATUS_STOPPED) {
			snprintf(table[row - 1][3], TABLE_MAX_ELT_LEN, "warn.");
			(*err_nbr)--;
			(*wng_nbr)++;
			if (stream != NULL) {
				fprintf(stream, "WARNING: %s is stopped, audit "
					"cannot be completed!\n\n",
					dpll54xx_name_get(id));
				autoadjust_table_fprint(stream, table, row, 4);
			}
			continue;
		}

		if ((opp != OPP54XX_DPLL_CASC) &&
			(settings->status == DPLL_STATUS_BYPASSED)) {
			snprintf(table[row - 1][3], TABLE_MAX_ELT_LEN, "warn.");
			(*err_nbr)--;
			(*wng_nbr)++;
			if (stream != NULL) {
				fprintf(stream, "WARNING: %s is bypassed, audit"
					" cannot be completed!\n\n",
					dpll54xx_name_get(id));
				autoadjust_table_fprint(stream, table, row, 4);
			}
			continue;
		}

dpll54xx_audit_mode:
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "Mode");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
			dpll_mode_name_get((settings->dpll).mode));
		DPLL54XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->mode,
			DPLL_MODE_MAX, dpll54xx_audit_autoidle_mode);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
			dpll_mode_name_get(golden_settings->mode));
		DPLL54XX_AUDIT_SHOW_STATUS((settings->dpll).mode,
			golden_settings->mode);

dpll54xx_audit_autoidle_mode:
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "Autoidle Mode");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
			dpll_autoidle_mode_name_get(
				(settings->dpll).autoidle_mode));
		DPLL54XX_AUDIT_CHECK_GOLDEN_SETTING(
				golden_settings->autoidle_mode,
			DPLL_AUTOIDLE_MODE_MAX, dpll54xx_audit_dcc_en);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
			dpll_autoidle_mode_name_get(
				golden_settings->autoidle_mode));
		DPLL54XX_AUDIT_SHOW_STATUS((settings->dpll).autoidle_mode,
			golden_settings->autoidle_mode);

dpll54xx_audit_dcc_en:
		if ((settings->dpll).type == DPLL_TYPE_B)
			goto dpll54xx_audit_selfreqdco;
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"DCC");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u",
			(settings->dpll).DCC.en);
		DPLL54XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->dcc_en,
			-1, dpll54xx_audit_selfreqdco);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u",
			golden_settings->dcc_en);
		DPLL54XX_AUDIT_SHOW_STATUS((int) (settings->dpll).DCC.en,
			golden_settings->dcc_en);

dpll54xx_audit_selfreqdco:
		if ((settings->dpll).type == DPLL_TYPE_A)
			goto dpll54xx_audit_sd_div;
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"SELFREQDCO");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u",
			(settings->dpll).selfreqdco);
		DPLL54XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->selfreqdco,
			-1, dpll54xx_audit_sd_div);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u",
			golden_settings->selfreqdco);
		DPLL54XX_AUDIT_SHOW_STATUS((settings->dpll).selfreqdco,
			golden_settings->selfreqdco);

dpll54xx_audit_sd_div:
		if ((settings->dpll).type == DPLL_TYPE_A)
			goto dpll54xx_audit_fref;
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"Sigma-Delta Divider");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u",
			(settings->dpll).sd_div);
		DPLL54XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->sd_div,
			-1, dpll54xx_audit_fref);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u",
			golden_settings->sd_div);
		DPLL54XX_AUDIT_SHOW_STATUS((int) (settings->dpll).sd_div,
			golden_settings->sd_div);

dpll54xx_audit_fref:
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"Ref. Frequency (MHz)");
		if ((settings->dpll).fref < 1.0) {
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%lf",
				(settings->dpll).fref);
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%lf",
				golden_settings->fref);
		} else {
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%.3lf",
				(settings->dpll).fref);
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%.3lf",
				golden_settings->fref);
		}
		DPLL54XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->fref,
			-1, dpll54xx_audit_regm4xen);
		DPLL54XX_AUDIT_SHOW_STATUS((settings->dpll).fref,
			golden_settings->fref);

dpll54xx_audit_regm4xen:
		if ((settings->dpll).type == DPLL_TYPE_B)
			goto dpll54xx_audit_M;
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"REGM4XEN");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u",
			(settings->dpll).regm4xen);
		DPLL54XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->regm4xen,
			-1, dpll54xx_audit_M);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u",
			golden_settings->regm4xen);
		DPLL54XX_AUDIT_SHOW_STATUS((settings->dpll).regm4xen,
			golden_settings->regm4xen);

dpll54xx_audit_M:
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"M Divider");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u",
			(settings->dpll).MN.M);
		DPLL54XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->M,
			-1, dpll54xx_audit_N);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u",
			golden_settings->M);
		DPLL54XX_AUDIT_SHOW_STATUS((int) (settings->dpll).MN.M,
			golden_settings->M);


dpll54xx_audit_N:
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"N Divider");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u",
			(settings->dpll).MN.N);
		DPLL54XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->N,
			-1, dpll54xx_audit_fdpll);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u",
			golden_settings->N);
		DPLL54XX_AUDIT_SHOW_STATUS((int) (settings->dpll).MN.N,
			golden_settings->N);

dpll54xx_audit_fdpll:
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"Lock Frequency (MHz)");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%.3lf",
			(settings->dpll).fdpll);
		DPLL54XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->fdpll,
			-1, dpll54xx_audit_M2);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%.3lf",
			golden_settings->fdpll);
		DPLL54XX_AUDIT_SHOW_STATUS(
			(unsigned int) (settings->dpll).fdpll,
			(unsigned int) golden_settings->fdpll);

dpll54xx_audit_M2:
		if (settings->dpll.MN.M2_present == 0)
			goto dpll54xx_audit_M3;
		snprintf(table[row++][0], TABLE_MAX_ELT_LEN, "%s Output",
			dpll54xx_output_name_get(DPLL54XX_CLKOUT_M2));
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"  Clock Divider");
		if ((settings->dpll).type == DPLL_TYPE_A) {
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u (x%d)",
				(settings->dpll).MN.M2,
				((settings->dpll).DCC.en == 0) ? 2 : 1);
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u (x%d)",
				golden_settings->M2,
				(golden_settings->dcc_en == 0) ? 2 : 1);
		} else {
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u",
				(settings->dpll).MN.M2);
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u",
				golden_settings->M2);
		}
		DPLL54XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->M2,
			-1, dpll54xx_audit_M2_rate);
		DPLL54XX_AUDIT_SHOW_STATUS((int) (settings->dpll).MN.M2,
			golden_settings->M2);

dpll54xx_audit_M2_rate:
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"  Clock Speed (MHz)");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%.3lf",
			(settings->dpll).MN.M2_rate);
		DPLL54XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->M2_rate,
			-1, dpll54xx_audit_X2_M2);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%.3lf",
			golden_settings->M2_rate);
		DPLL54XX_AUDIT_SHOW_STATUS(
			(unsigned int) (settings->dpll).MN.M2_rate,
			(unsigned int) golden_settings->M2_rate);

dpll54xx_audit_X2_M2:
		if ((settings->dpll).type == DPLL_TYPE_B)
			goto dpll54xx_audit_clkdcoldo_rate;
		if (settings->dpll.MN.X2_M2_present == 0)
			goto dpll54xx_audit_M3;
		snprintf(table[row++][0], TABLE_MAX_ELT_LEN, "%s Output",
			dpll54xx_output_name_get(DPLL54XX_CLKOUTX2_M2));
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"  Clock Divider");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u",
			(settings->dpll).MN.M2);
		DPLL54XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->M2,
			-1, dpll54xx_audit_X2_M2_rate);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u",
			golden_settings->M2);
		DPLL54XX_AUDIT_SHOW_STATUS((int) (settings->dpll).MN.M2,
			golden_settings->M2);

dpll54xx_audit_X2_M2_rate:
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"  Clock Speed (MHz)");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%.3lf",
			(settings->dpll).MN.X2_M2_rate);
		DPLL54XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->X2_M2_rate,
			-1, dpll54xx_audit_M3);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%.3lf",
			golden_settings->X2_M2_rate);
		DPLL54XX_AUDIT_SHOW_STATUS(
			(unsigned int) (settings->dpll).MN.X2_M2_rate,
			(unsigned int) golden_settings->X2_M2_rate);

dpll54xx_audit_M3:
		if ((settings->dpll).type == DPLL_TYPE_B)
			goto dpll54xx_audit_clkdcoldo_rate;
		if (settings->dpll.MN.M3_present == 0)
			goto dpll54xx_audit_hsdiv;
		snprintf(table[row++][0], TABLE_MAX_ELT_LEN, "%s Output",
			dpll54xx_output_name_get(DPLL54XX_CLKOUTX2_M3));
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"  Clock Divider");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u",
			(settings->dpll).MN.M3);
		DPLL54XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->M3,
			-1, dpll54xx_audit_X2_M3_rate);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u",
			golden_settings->M3);
		DPLL54XX_AUDIT_SHOW_STATUS((int) (settings->dpll).MN.M3,
			golden_settings->M3);

dpll54xx_audit_X2_M3_rate:
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"  Clock Speed (MHz)");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%.3lf",
			(settings->dpll).MN.X2_M3_rate);
		DPLL54XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->X2_M3_rate,
			-1, dpll54xx_audit_hsdiv);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%.3lf",
			golden_settings->X2_M3_rate);
		DPLL54XX_AUDIT_SHOW_STATUS(
			(unsigned int) (settings->dpll).MN.X2_M3_rate,
			(unsigned int) golden_settings->X2_M3_rate);

dpll54xx_audit_hsdiv:
		for (hsdiv_id = HSDIV54XX_H11; hsdiv_id < HSDIV54XX_ID_MAX;
			hsdiv_id++) {
			if ((settings->hsdiv)[hsdiv_id].present != 1)
				continue;
			snprintf(table[row++][0], TABLE_MAX_ELT_LEN,
				"%s Output",
				hsdiv54xx_name_get(hsdiv_id));
			snprintf(table[row][0], TABLE_MAX_ELT_LEN,
				"  Clock Divider");
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u",
				(settings->hsdiv)[hsdiv_id].div);
			DPLL54XX_AUDIT_CHECK_GOLDEN_SETTING(
				(golden_settings->hsdiv_div)[hsdiv_id],
				-1, dpll54xx_audit_hsdiv_rate);
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u",
				(golden_settings->hsdiv_div)[hsdiv_id]);
			DPLL54XX_AUDIT_SHOW_STATUS(
				(int) (settings->hsdiv)[hsdiv_id].div,
				(golden_settings->hsdiv_div)[hsdiv_id]);

dpll54xx_audit_hsdiv_rate:
			snprintf(table[row][0], TABLE_MAX_ELT_LEN,
				"  Clock Speed (MHz)");
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%.3lf",
				(settings->hsdiv)[hsdiv_id].rate);
			if ((golden_settings->hsdiv_rate)[hsdiv_id] == -1) {
				/* Golden setting not available */
				snprintf(table[row][2], TABLE_MAX_ELT_LEN,
					"Not available");
				snprintf(table[row][3], TABLE_MAX_ELT_LEN,
					"warn.");
				(*wng_nbr)++;
				row++;
				continue;
			}
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%.3lf",
				(golden_settings->hsdiv_rate)[hsdiv_id]);
			DPLL54XX_AUDIT_SHOW_STATUS(
				(unsigned int) (settings->hsdiv)[hsdiv_id].rate,
				(unsigned int)
				(golden_settings->hsdiv_rate)[hsdiv_id]);
		}
		goto dpll54xx_audit_table_show;

dpll54xx_audit_clkdcoldo_rate:
		snprintf(table[row++][0], TABLE_MAX_ELT_LEN,
			"CLKDCOLDO Output");
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"  Clock Speed (MHz)");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%.3lf",
			(settings->dpll).MN.clkdcoldo_rate);
		DPLL54XX_AUDIT_CHECK_GOLDEN_SETTING(
			golden_settings->clkdcoldo_rate,
			-1, dpll54xx_audit_table_show);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%.3lf",
			golden_settings->clkdcoldo_rate);
		DPLL54XX_AUDIT_SHOW_STATUS(
			(unsigned int) (settings->dpll).MN.clkdcoldo_rate,
			(unsigned int) golden_settings->clkdcoldo_rate);

dpll54xx_audit_table_show:
		if (stream != NULL)
			autoadjust_table_fprint(stream, table, row, 4);
	}

	if (*err_nbr > 0)
		ret = OMAPCONF_ERR_AUDIT_FAIL;

dpll54xx_audit_end:
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll54xx_init
 * @BRIEF		allocate memory for dpll settings structs and save
 *			dpll settings in it.
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_UNEXPECTED
 * @DESCRIPTION		allocate memory for dpll settings structs and save
 *			dpll settings in it.
 *//*------------------------------------------------------------------------ */
int dpll54xx_init(void)
{
	dpll54xx_id id;
	unsigned int i;
	int ret;
	static const dpll54xx_id ordered_ids[DPLL54XX_ID_MAX] = {
		DPLL54XX_ABE,
		DPLL54XX_CORE,
		DPLL54XX_PER,
		DPLL54XX_MPU,
		DPLL54XX_IVA,
		DPLL54XX_USB,
		DPLL54XX_UNIPRO1,
		DPLL54XX_UNIPRO2};

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	dprintf("\n%s(): retrieving all DPLL settings\n", __func__);
	/*
	 * Allocate memory for dpll settings structs
	 * And save dpll settings into it.
	 */
	for (id = DPLL54XX_MPU; id < DPLL54XX_ID_MAX; id++) {
		dpll54xx_settings_table[id] =
			malloc(sizeof(dpll54xx_settings));
		if (dpll54xx_settings_table[id] == NULL)
			return OMAPCONF_ERR_UNEXPECTED;
		(dpll54xx_settings_table[id]->dpll).initialized = 0;
		dpll54xx_locked_settings_table[id] =
			malloc(sizeof(dpll54xx_settings));
		if (dpll54xx_locked_settings_table[id] == NULL)
			return OMAPCONF_ERR_UNEXPECTED;
		(dpll54xx_locked_settings_table[id]->dpll).initialized = 0;
	}

	for (i = 0; i < DPLL54XX_ID_MAX; i++) {
		id = ordered_ids[i];
		ret = dpll54xx_settings_extract(
			dpll54xx_settings_table[id], id, 0);
		if (ret < 0) {
			fprintf(stderr, "%s(): error while extracting %s "
				"parameters! (%d)", __func__,
				dpll54xx_name_get(id), ret);
			return ret;
		}

		/*
		 * Also get DPLL params ignoring DPLL STOPPED status to also
		 * show all output speeds when DPLL is locked.
		 */
		dpll54xx_settings_extract(
			dpll54xx_locked_settings_table[id], id, 1);
		if (ret < 0) {
			fprintf(stderr, "%s(): error while extracting %s "
				"parameters! (%d)", __func__,
				dpll54xx_name_get(id), ret);
			return ret;
		}


	}

	dprintf("%s(): all DPLL settings retrieved\n\n", __func__);
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll54xx_free
 * @BRIEF		free memory for dpll settings structs and save
 *			dpll settings in it.
 * @RETURNS		0 on success
 * @param[in]		none
 * @DESCRIPTION		allocate memory for dpll settings structs and save
 *			dpll settings in it.
 *//*------------------------------------------------------------------------ */
int dpll54xx_free(void)
{
	dpll54xx_id id;

	for (id = DPLL54XX_MPU; id < DPLL54XX_ID_MAX; id++) {
		if (dpll54xx_settings_table[id] != NULL)
			free(dpll54xx_settings_table[id]);
		if (dpll54xx_locked_settings_table[id] != NULL)
			free(dpll54xx_locked_settings_table[id]);
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll54xx_main
 * @BRIEF		main entry point for DPLL functions
 *
 *			### DEPRECATED, DO NOT USE ANYMORE ###
 *
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		main entry point for DPLL functions
 *			argv[0] = function ("dump", "cfg")
 *			argv[1] = DPLL ID ("mpu", "iva", "core", "per", "abe",
 *				"usb", "unipro1", "unipro2")
 *				argv[1] may be omitted (then "all" assumed)
 *//*------------------------------------------------------------------------ */
int dpll54xx_main(int argc, char *argv[])
{
	int ret = 0;
	dpll54xx_id id;

	if (argc == 1) {
		id = DPLL54XX_ID_MAX;
	} else if (argc != 2) {
		goto dpll54xx_main_err_arg;
	} else if (strcmp(argv[1], "all") == 0) {
		id = DPLL54XX_ID_MAX;
	} else {
		id = dpll54xx_s2id(argv[1]);
		if (id == DPLL54XX_ID_MAX)
			goto dpll54xx_main_err_arg;
	}

	if (strcmp(argv[0], "dump") == 0) {
		ret = dpll54xx_dump(stdout, id);
	} else if (strcmp(argv[0], "cfg") == 0) {
		ret = dpll54xx_show(stdout);
	} else {
		goto dpll54xx_main_err_arg;
	}
	goto dpll54xx_main_end;

dpll54xx_main_err_arg:
	help(HELP_DPLL);
	ret = OMAPCONF_ERR_ARG;

dpll54xx_main_end:
	return ret;
}
