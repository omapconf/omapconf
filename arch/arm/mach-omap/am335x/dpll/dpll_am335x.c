/*
 *
 * @Component			OMAPCONF
 * @Filename			dpll_am335x.c
 * @Description			AM335X DPLL Definitions & Functions
 * @Author			Gilberto Rodriguez <gilrod@ti.com>
 * @Date			2014
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
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


#include <autoadjust_table.h>
#include <clock_am335x.h>
#include <cm_am335x-defs.h>
#include <cpuinfo.h>
#include <dpll_am335x.h>
#include <dpll_am335x-data.h>
#include <help.h>
#include <lib.h>
#include <mem.h>
#include <opp.h>
#include <stdio.h>
#include <string.h>
#include <voltdomain.h>


#ifdef DPLL_AM335X_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


dpll_am335x_settings *dpll_am335x_settings_table[DPLL_AM335X_ID_MAX] = {
	NULL, NULL, NULL, NULL, NULL};


dpll_am335x_settings *dpll_am335x_locked_settings_table[DPLL_AM335X_ID_MAX] = {
	NULL, NULL, NULL, NULL, NULL};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		am335x_print_reg
 * @BRIEF		Show register name, addr & content
 * @RETURNS		None
 * @param[in]		r: register. row: pointer to the row number
 * @DESCRIPTION		Show register name, addr & content
 *//*------------------------------------------------------------------------ */
void am335x_print_reg(char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN],
		reg *r, unsigned int *row)
{
	unsigned int val;
	if (r == NULL)
		return;
	val = reg_read(r);
	/* Show register name, addr & content */
	snprintf(table[*row][0], TABLE_MAX_ELT_LEN, "%s", r->name);
	snprintf(table[*row][1], TABLE_MAX_ELT_LEN, "0x%08X", r->addr);
	snprintf(table[*row][2], TABLE_MAX_ELT_LEN, "0x%08X", val);
	(*row)++;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_am335x_s2id
 * @BRIEF		convert string to valid DPLL ID
 * @RETURNS		DPLL_AM335X_PER if s == "per"
 *			DPLL_AM335X_CORE if s == "core"
 *			DPLL_AM335X_MPU if s == "mpu"
 *			DPLL_AM335X_DDR if s == "ddr"
 *			DPLL_AM335X_DISP if s == "disp"
 *			DPLL_AM335X_ID_MAX otherwise
 * @param[in,out]	s: string
 * @DESCRIPTION		convert string to valid DPLL ID
 *//*------------------------------------------------------------------------ */
dpll_am335x_id dpll_am335x_s2id(char *s)
{
	int index;
	CHECK_NULL_ARG(s, DPLL_AM335X_ID_MAX);

	for (index = 0; index < DPLL_AM335X_ID_MAX; index++)
		if (strcmp(s, dpll_am335x_strings[index]) == 0)
			return (dpll_am335x_id) index;
	return DPLL_AM335X_ID_MAX;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_am335x_name_get
 * @BRIEF		return DPLL name
 * @RETURNS		DPLL name
 *			NULL in case of incorrect id
 * @param[in]		id: DPLL ID
 * @DESCRIPTION		return DPLL name
 *//*------------------------------------------------------------------------ */
const char *dpll_am335x_name_get(dpll_am335x_id id)
{
	CHECK_ARG_LESS_THAN(id, DPLL_AM335X_ID_MAX, NULL);

	return dpll_am335x_names[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_am335x_output_name_get
 * @BRIEF		return DPLL output name
 * @RETURNS		DPLL output name
 *			NULL in case of incorrect id
 * @param[in]		id: DPLL output ID
 * @DESCRIPTION		return DPLL output name
 *//*------------------------------------------------------------------------ */
const char *dpll_am335x_output_name_get(dpll_am335x_output_id id)
{
	CHECK_ARG_LESS_THAN(id, DPLL_AM335X_OUTPUT_ID_MAX, NULL);

	return dpll_am335x_output_names[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hsdiv_am335x_name_get
 * @BRIEF		return HS divider name
 * @RETURNS		HS divider name
 *			NULL in case of incorrect id
 * @param[in]		id: HS divider ID
 * @DESCRIPTION		return HS divider name
 *//*------------------------------------------------------------------------ */
const char *hsdiv_am335x_name_get(hsdiv_am335x_id id)
{
	CHECK_ARG_LESS_THAN(id, HSDIV_AM335X_ID_MAX, NULL);

	return hsdiv_am335x_names[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_am335x_dump
 * @BRIEF		dump selected DPLL registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in, out]	stream: output stream
 * @param[in]		id: DPLL ID
 *			If id == DPLL_AM335X_ID_MAX, dump all DPLL registers.
 * @DESCRIPTION		dump selected DPLL registers and pretty-print it to
 *			output stream.
 *//*------------------------------------------------------------------------ */
int dpll_am335x_dump(FILE *stream, dpll_am335x_id id)
{
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row, i;
	dpll_settings_regs dpll_regs;
	dpll_am335x_id dpll_id;
	reg *r;

	CHECK_ARG_LESS_THAN(id, DPLL_AM335X_ID_MAX + 1, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(stream, OMAPCONF_ERR_ARG);

	for (dpll_id = DPLL_AM335X_PER; dpll_id < DPLL_AM335X_ID_MAX; dpll_id++) {
		if ((id != DPLL_AM335X_ID_MAX) && (dpll_id != id))
			continue;
		else {
			autoadjust_table_init(table);
			row = 0;
			snprintf(table[row][0], TABLE_MAX_ELT_LEN,
				"%s Reg. Name",	dpll_am335x_name_get(dpll_id));
			strncpy(table[row][1], "Reg. Address",
				TABLE_MAX_ELT_LEN);
			strncpy(table[row][2], "Reg. Value", TABLE_MAX_ELT_LEN);
			row++;

			dpll_regs = dpll_am335x_regs[dpll_id];
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
						"%s(): i=%u should not be "
						"reachable?!\n", __func__, i);
				}
				am335x_print_reg(table, r, &row);
			}

			for (i = HSDIV_AM335X_M4; i < HSDIV_AM335X_ID_MAX; i++) {
				r = (reg *) dpll_am335x_hsdiv_regs[dpll_id][i];
				am335x_print_reg(table, r, &row);
			}

			autoadjust_table_print(table, row, 3);
		}
	}
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_am335x_show
 * @BRIEF		analyze PLLs configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_UNEXPECTED
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		stream: output stream
 * @DESCRIPTION		analyze PLLs configuration
 *//*------------------------------------------------------------------------ */
int dpll_am335x_show(FILE *stream)
{
	int ret;

	ret = dpll_am335x_type_b_show(DPLL_AM335X_PER, DPLL_AM335X_CORE, stream);
	if (ret != 0)
		return ret;
	return dpll_am335x_type_a_show(DPLL_AM335X_CORE, DPLL_AM335X_ID_MAX,
		stream);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_am335x_type_b_show
 * @BRIEF		show tpye B dpll module configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_UNEXPECTED
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		stream: output stream
 * @DESCRIPTION		show tpye B dpll module configuration
 *//*------------------------------------------------------------------------ */
int dpll_am335x_type_b_show(dpll_am335x_id start_id, dpll_am335x_id end_id,
	FILE *stream)
{
	int ret = 0;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row, row_max;
	dpll_am335x_id id;
	dpll_am335x_settings *settings, *settings_locked;

	autoadjust_table_init(table);
	row = 0;
	row_max = 0;
	strncpy(table[row][0], "DPLL Configuration", TABLE_MAX_ELT_LEN);

	for (id = start_id; id < end_id; id++) {
		row = 0;
		snprintf(table[row++][id - start_id + 1],
			TABLE_MAX_ELT_LEN, "%s",
			dpll_am335x_name_get(id));
		settings = dpll_am335x_settings_get(id, 0);
		if (settings == NULL) {
			fprintf(stderr, "%s(): error while getting %s "
				"parameters! (%d)", __func__,
				dpll_am335x_name_get(id), ret);
			return OMAPCONF_ERR_UNEXPECTED;
		}

		/*
		 * Also get DPLL params ignoring DPLL STOPPED status to also
		 * show all output speeds when DPLL is locked.
		 */
		settings_locked = dpll_am335x_settings_get(id, 1);
		if (settings_locked == NULL) {
			fprintf(stderr, "%s(): error while getting %s "
				"locked parameters! (%d)", __func__,
				dpll_am335x_name_get(id), ret);
			return OMAPCONF_ERR_UNEXPECTED;
		}

		strncpy(table[row][0], "Status", TABLE_MAX_ELT_LEN);
		strncpy(table[row][id - start_id + 1],
			dpll_status_name_get(settings->status),
			TABLE_MAX_ELT_LEN);
		row += 2;

		strncpy(table[row][0], "Mode", TABLE_MAX_ELT_LEN);
		strncpy(table[row++][id - start_id + 1],
			dpll_mode_name_get(settings->dpll.mode),
			TABLE_MAX_ELT_LEN);

		strncpy(table[row][0], "Automatic Control", TABLE_MAX_ELT_LEN);
		strncpy(table[row++][id - start_id + 1], "Not Supported",
			TABLE_MAX_ELT_LEN);

		strncpy(table[row++][0], " LPST = Low-Power STop",
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
		snprintf(table[row++][id - start_id + 1],
			TABLE_MAX_ELT_LEN, "%u",
			settings->dpll.sd_div);
		strncpy(table[row][0], "SELFREQDCO",
			TABLE_MAX_ELT_LEN);
		snprintf(table[row++][id - start_id + 1],
			TABLE_MAX_ELT_LEN, "%u", settings->dpll.selfreqdco);
		row++;

		strncpy(table[row][0], "Ref. Frequency (MHz)",
			TABLE_MAX_ELT_LEN);
		snprintf(table[row++][id - start_id + 1],
			TABLE_MAX_ELT_LEN, "%.3lf", settings->dpll.fref);
		strncpy(table[row][0], "M Multiplier Factor",
			TABLE_MAX_ELT_LEN);
		snprintf(table[row++][id - start_id + 1],
			TABLE_MAX_ELT_LEN, "%u",
			settings->dpll.MN.M);

		strncpy(table[row][0], "N Divider Factor", TABLE_MAX_ELT_LEN);
		snprintf(table[row++][id - start_id + 1],
			TABLE_MAX_ELT_LEN, "%u",
			settings->dpll.MN.N);

		strncpy(table[row][0], "Lock Frequency (MHz)",
			TABLE_MAX_ELT_LEN);
		if (settings->status == DPLL_STATUS_LOCKED)
			snprintf(table[row][id - start_id + 1],
			TABLE_MAX_ELT_LEN,
			"%u", (unsigned int) settings->dpll.fdpll);
		else
			snprintf(table[row][id - start_id + 1],
			TABLE_MAX_ELT_LEN,
				"%u (%u)",
				(unsigned int) settings->dpll.fdpll,
				(unsigned int) settings_locked->dpll.fdpll);
		row += 2;

		strncpy(table[row][0], "CLKOUT Output", TABLE_MAX_ELT_LEN);
		row++;
		strncpy(table[row][0], "  Status", TABLE_MAX_ELT_LEN);
		strncpy(table[row++][id - start_id + 1],
			(settings->dpll.MN.M2_clkout_st == 1) ?
				"Enabled" : "Gated",
				TABLE_MAX_ELT_LEN);
		strncpy(table[row][0], "  Clock Divider",
			TABLE_MAX_ELT_LEN);
		snprintf(table[row++][id - start_id + 1],
			TABLE_MAX_ELT_LEN,
			"%-5u", settings->dpll.MN.M2);
		strncpy(table[row][0], "  Clock Speed (MHz)",
			TABLE_MAX_ELT_LEN);
		if (settings->status == DPLL_STATUS_LOCKED)
			snprintf(table[row++][id - start_id + 1],
				TABLE_MAX_ELT_LEN, "%u",
				(unsigned int) settings->dpll.MN.M2_rate);
		else
			snprintf(table[row++][id - start_id + 1],
				TABLE_MAX_ELT_LEN, "%u (%u)",
				(unsigned int) settings->dpll.MN.M2_rate,
				(unsigned int) settings_locked->dpll.MN.M2_rate);
		row++;

		strncpy(table[row++][0],
			"CLK_DCO_LDO Output", TABLE_MAX_ELT_LEN);
		strncpy(table[row][0], "  Status",
			TABLE_MAX_ELT_LEN);
		strncpy(table[row++][id - start_id + 1],
			(settings->dpll.MN.clkdcoldo_clkout_st == 1) ? "Enabled"
			: "Gated",TABLE_MAX_ELT_LEN);
		strncpy(table[row][0], "  Clock Speed (MHz)", TABLE_MAX_ELT_LEN);

		if (settings->status == DPLL_STATUS_LOCKED)
			snprintf(table[row++][id - start_id + 1],
				TABLE_MAX_ELT_LEN, "%u",
				(unsigned int) settings->dpll.MN.clkdcoldo_rate);
		else
			snprintf(table[row++][id - start_id + 1],
				TABLE_MAX_ELT_LEN, "%u (%u)",
				(unsigned int) settings->dpll.MN.clkdcoldo_rate,
				(unsigned int) settings_locked->dpll.MN.clkdcoldo_rate);
		row++;

		if (row > row_max)
			row_max = row;
	}

	if (stream != NULL)
		autoadjust_table_fprint(stream,
			table, row_max, end_id - start_id + 1);
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_am335x_type_a_show
 * @BRIEF		show tpye A dpll module configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_UNEXPECTED
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		stream: output stream
 * @DESCRIPTION		show tpye A dpll module configuration
 *//*------------------------------------------------------------------------ */
int dpll_am335x_type_a_show(dpll_am335x_id start_id, dpll_am335x_id end_id,
	FILE *stream)
{
	int ret = 0;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row, row_max;
	dpll_am335x_id id;
	hsdiv_am335x_id hsdiv_id;
	dpll_am335x_settings *settings, *settings_locked;

	autoadjust_table_init(table);
	row = 0;
	row_max = 0;
	strncpy(table[row][0], "DPLL Configuration", TABLE_MAX_ELT_LEN);

	for (id = start_id; id < end_id; id++) {
		row = 0;
		snprintf(table[row++][id - start_id + 1], TABLE_MAX_ELT_LEN, "%s",
			dpll_am335x_name_get(id));
		settings = dpll_am335x_settings_get(id, 0);
		if (settings == NULL) {
			fprintf(stderr, "%s(): error while getting %s "
				"parameters! (%d)", __func__,
				dpll_am335x_name_get(id), ret);
			return OMAPCONF_ERR_UNEXPECTED;
		}

		/*
		 * Also get DPLL params ignoring DPLL STOPPED status to also
		 * show all output speeds when DPLL is locked.
		 */
		settings_locked = dpll_am335x_settings_get(id, 1);
		if (settings_locked == NULL) {
			fprintf(stderr, "%s(): error while getting %s "
				"locked parameters! (%d)", __func__,
				dpll_am335x_name_get(id), ret);
			return OMAPCONF_ERR_UNEXPECTED;
		}

		strncpy(table[row][0], "Status", TABLE_MAX_ELT_LEN);
		strncpy(table[row][id - start_id + 1],
			dpll_status_name_get(settings->status),
			TABLE_MAX_ELT_LEN);
		row += 2;

		strncpy(table[row][0], "Mode", TABLE_MAX_ELT_LEN);
		strncpy(table[row++][id - start_id + 1],
			dpll_mode_name_get(settings->dpll.mode),
			TABLE_MAX_ELT_LEN);

		strncpy(table[row][0], "Automatic Control", TABLE_MAX_ELT_LEN);
		strncpy(table[row++][id - start_id + 1], "Not Supported",
			TABLE_MAX_ELT_LEN);

		strncpy(table[row++][0], " LPBP = Low-Power ByPass",
			TABLE_MAX_ELT_LEN);
		strncpy(table[row++][0], " FRBP = Fast-Relock ByPass",
			TABLE_MAX_ELT_LEN);
		strncpy(table[row++][0], " MNBP = MN ByPass",
			TABLE_MAX_ELT_LEN);

		strncpy(table[row][0], "Low-Power Mode", TABLE_MAX_ELT_LEN);
		strncpy(table[row][id - start_id + 1],
			(settings->dpll.lpmode_en == 1) ?
				"Enabled" : "Disabled",
			TABLE_MAX_ELT_LEN);
		row += 2;

		strncpy(table[row][0], "Automatic Recalibration",
			TABLE_MAX_ELT_LEN);
		strncpy(table[row++][id - start_id + 1],
			(settings->dpll.driftguard_en == 1) ?
			"Enabled" : "Disabled",	TABLE_MAX_ELT_LEN);

		strncpy(table[row][0], "Clock Ramping during Relock",
				TABLE_MAX_ELT_LEN);
		strncpy(table[row++][id - start_id + 1],
			(settings->dpll.ramp.relock_ramp_en == 1) ?
			"Enabled" : "Disabled", TABLE_MAX_ELT_LEN);

		strncpy(table[row][0], "Ramping Rate (x REFCLK(s))",
			TABLE_MAX_ELT_LEN);
		snprintf(table[row++][id - start_id + 1], TABLE_MAX_ELT_LEN, "%u",
			settings->dpll.ramp.ramp_rate);

		strncpy(table[row][0], "Ramping Levels", TABLE_MAX_ELT_LEN);
		strncpy(table[row][id - start_id + 1],
			dpll_ramp_level_name_get((dpll_ramp_level)
				settings->dpll.ramp.ramp_level),
			TABLE_MAX_ELT_LEN);
		row += 2;

		strncpy(table[row][0], "Bypass Clock", TABLE_MAX_ELT_LEN);
		strncpy(table[row++][id - start_id + 1],
			dpll_bp_clk_src_name_get((dpll_bp_clk_src)
				settings->dpll.bypass_clk),
			TABLE_MAX_ELT_LEN);

		strncpy(table[row][0], "Bypass Clock Divider",
			TABLE_MAX_ELT_LEN);
		if (dpll_am335x_regs[id].cm_bypclk_dpll != NULL)
			snprintf(table[row][id - start_id + 1], TABLE_MAX_ELT_LEN,
			"%u", settings->dpll.bypass_clk_div);
		row++;

		strncpy(table[row][0], "REGM4XEN Mode",
			TABLE_MAX_ELT_LEN);
		if (settings->dpll.regm4xen == 0)
			snprintf(table[row][id - start_id + 1], TABLE_MAX_ELT_LEN,
				"Disabled");
		else
			snprintf(table[row][id - start_id + 1], TABLE_MAX_ELT_LEN,
				"Enabled");
		row += 2;

		strncpy(table[row][0], "Ref. Frequency (MHz)",
			TABLE_MAX_ELT_LEN);
		snprintf(table[row++][id - start_id + 1],
			TABLE_MAX_ELT_LEN, "%.3lf", settings->dpll.fref);
		strncpy(table[row][0], "M Multiplier Factor",
			TABLE_MAX_ELT_LEN);
		snprintf(table[row++][id - start_id + 1], TABLE_MAX_ELT_LEN, "%u",
			settings->dpll.MN.M);

		strncpy(table[row][0], "N Divider Factor", TABLE_MAX_ELT_LEN);
		snprintf(table[row++][id - start_id + 1], TABLE_MAX_ELT_LEN, "%u",
			settings->dpll.MN.N);

		strncpy(table[row][0], "Lock Frequency (MHz)",
			TABLE_MAX_ELT_LEN);
		if (settings->status == DPLL_STATUS_LOCKED)
			snprintf(table[row][id - start_id + 1], TABLE_MAX_ELT_LEN,
			"%u", (unsigned int) settings->dpll.fdpll);
		else
			snprintf(table[row][id - start_id + 1], TABLE_MAX_ELT_LEN,
				"%u (%u)",
				(unsigned int) settings->dpll.fdpll,
				(unsigned int) settings_locked->dpll.fdpll);
		row += 2;
		strncpy(table[row][0], "M2 Output", TABLE_MAX_ELT_LEN);
		row++;

		if (settings->dpll.MN.M2_present) {
			strncpy(table[row][0], "  Status", TABLE_MAX_ELT_LEN);
			strncpy(table[row++][id - start_id + 1],
				(settings->dpll.MN.M2_clkout_st == 1) ?
					"Enabled" : "Gated",
					TABLE_MAX_ELT_LEN);
			strncpy(table[row][0], "  Clock Divider",
				TABLE_MAX_ELT_LEN);
			snprintf(table[row++][id - start_id + 1],
				TABLE_MAX_ELT_LEN, "%-5u",
				settings->dpll.MN.M2);
			strncpy(table[row][0], "  Clock Speed (MHz)",
				TABLE_MAX_ELT_LEN);
			if (settings->status == DPLL_STATUS_LOCKED)
				snprintf(table[row++][id - start_id + 1],
					TABLE_MAX_ELT_LEN, "%u",
					(unsigned int) settings->dpll.MN.M2_rate);
			else
				snprintf(table[row++][id - start_id + 1],
				TABLE_MAX_ELT_LEN, "%u (%u)",
				(unsigned int) settings->dpll.MN.M2_rate,
				(unsigned int) settings_locked->dpll.MN.M2_rate);
		} else {
			row += 3;
		}
		row++;

		if (id == DPLL_AM335X_CORE) {
			strncpy(table[row++][0],
				"CLK_DCO_LDO Output", TABLE_MAX_ELT_LEN);
			strncpy(table[row][0], "  Status",
				TABLE_MAX_ELT_LEN);
			strncpy(table[row++][id - start_id + 1],
				(settings->dpll.MN.clkdcoldo_clkout_st == 1) ?
				"Enabled" : "Gated",TABLE_MAX_ELT_LEN);
			strncpy(table[row][0], "  Clock Speed (MHz)",
				TABLE_MAX_ELT_LEN);

			if (settings->status == DPLL_STATUS_LOCKED)
				snprintf(table[row++][id - start_id + 1],
					TABLE_MAX_ELT_LEN, "%u",
					(unsigned int)
					settings->dpll.MN.clkdcoldo_rate);
			else
				snprintf(table[row++][id - start_id + 1],
					TABLE_MAX_ELT_LEN, "%u (%u)",
					(unsigned int)
					settings->dpll.MN.clkdcoldo_rate,
					(unsigned int)
					settings_locked->dpll.MN.clkdcoldo_rate);
			row++;
		}

		for (hsdiv_id = HSDIV_AM335X_M4; hsdiv_id < HSDIV_AM335X_ID_MAX;
			hsdiv_id++) {
			row++;
			if ((settings->hsdiv)[hsdiv_id].present == 0) {
				row += 4;
			} else {
				snprintf(table[row++][0], TABLE_MAX_ELT_LEN,
					"%s Output",
					hsdiv_am335x_name_get(hsdiv_id));
				strncpy(table[row][0], "  Status",
					TABLE_MAX_ELT_LEN);
				strncpy(table[row++][id - start_id + 1],
				((settings->hsdiv)[hsdiv_id].status == 1) ?
					"Enabled" : "Gated", TABLE_MAX_ELT_LEN);
				strncpy(table[row][0], "  Clock Divider",
					TABLE_MAX_ELT_LEN);
				snprintf(table[row++][id - start_id + 1],
					TABLE_MAX_ELT_LEN,
					"%u",
					(settings->hsdiv)[hsdiv_id].div);
				strncpy(table[row][0], "  Clock Speed (MHz)",
					TABLE_MAX_ELT_LEN);
				if (settings->status == DPLL_STATUS_LOCKED)
					snprintf(table[row++][id - start_id + 1],
						TABLE_MAX_ELT_LEN, "%u",
						(unsigned int) (settings->hsdiv)[hsdiv_id].rate);
				else
					snprintf(table[row++][id - start_id + 1],
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
			table, row_max, (end_id - start_id + 1));
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_am335x_lock_freq_calc
 * @BRIEF		compute DPLL lock frequency (in MHz)
 * @RETURNS		lock frequency in case of success (in MHz)
 *			0.0 in case of error.
 * @param[in]		settings: DPLL settings with fields
 * @param[in]		ignore: do not consider DPLL STOP status.
 *			regm4xen, fref, MN.M, MN.N INITIALIZED
 * @DESCRIPTION		compute DPLL lock frequency (in MHz)
 *//*------------------------------------------------------------------------ */
double dpll_am335x_lock_freq_calc(dpll_settings *settings)
{
	CHECK_NULL_ARG(settings, 0.0);

	if (settings->type == DPLL_TYPE_A) {
		if (settings->regm4xen == 1)
			settings->fdpll =
				(settings->fref * 4.0 * (double) (settings->MN).M)
				/ ((double) (settings->MN).N + 1.0);
		else
			settings->fdpll =
				(settings->fref * (double) (settings->MN).M) /
				((double) (settings->MN).N + 1.0);
		dprintf("%s(%u): type=A regm4xen=%u fref=%lfMHz M=%u N=%u ==> "
			"fdpll=%lfMHz\n", __func__, settings->id,
			settings->regm4xen, settings->fref, (settings->MN).M,
			(settings->MN).N, settings->fdpll);
	} else {
		settings->fdpll =
			(settings->fref * (double) (settings->MN).M) /
			((double) (settings->MN).N + 1.0);
		dprintf("%s(%u): type=B fref=%lfMHz M=%u N=%u ==> "
			"fdpll=%lfMHz\n", __func__, settings->id,
			settings->fref, (settings->MN).M, (settings->MN).N,
			settings->fdpll);
	}

	return settings->fdpll;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_am335x_clk_sources_get
 * @BRIEF		retrieve DPLL input clock rates
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		settings: struct with extracted HSDIV settings
 * @param[in]		ignore: do not consider DPLL STOP status.
 *			Useful for functions that needs the DPLL output
 *			frequencies even when DPLL is stopped
 *			(e.g. autdit, clock tree, OPP detection, etc)
 * @DESCRIPTION		retrieve DPLL input clock rates
 *//*------------------------------------------------------------------------ */
int dpll_am335x_clk_sources_get(dpll_settings *settings, unsigned short ignore)
{
	CHECK_NULL_ARG(settings, OMAPCONF_ERR_ARG);

	if (dpll_am335x_sources[settings->id].ref_clk != CLK_AM335X_ID_MAX)
		settings->fref = clk_am335x_rate_get(
			(clk_am335x_id) dpll_am335x_sources[settings->id].ref_clk,
			ignore);
	else
		settings->fref = 0.0;

	/*
	 * AM335X has a bypass clock input called CLKINPULOW.
	 * If selected, CLKINPULOW is determined by a mux register read.
	 * byp_clk_m2 and byp_clk_m3 represent the two clocks that are muxed to
	 * determine CLKINPULOW, since the AM335X does not have a specified
	 * bypass clock for M2 and M3 is not supported.
	 */
	if (dpll_am335x_sources[settings->id].byp_clk_m2 != CLK_AM335X_ID_MAX)
		settings->fbyp_clk_m2 = clk_am335x_rate_get(
			(clk_am335x_id) dpll_am335x_sources[settings->id].byp_clk_m2, ignore);
	else
		settings->fbyp_clk_m2 = 0.0;

	if (dpll_am335x_sources[settings->id].byp_clk_m3 != CLK_AM335X_ID_MAX)
		settings->fbyp_clk_m3 = clk_am335x_rate_get(
			(clk_am335x_id) dpll_am335x_sources[settings->id].byp_clk_m3, ignore);
	else
		settings->fbyp_clk_m3 = 0.0;

	if (dpll_am335x_sources[settings->id].byp_clk_hsdiv != CLK_AM335X_ID_MAX)
		settings->fbyp_clk_hsdiv = clk_am335x_rate_get(
			(clk_am335x_id)
			dpll_am335x_sources[settings->id].byp_clk_hsdiv, ignore);
	else
		settings->fbyp_clk_hsdiv = 0.0;

	dprintf("%s(): %s Fref=%lf MHz\n", __func__,
		dpll_am335x_names[settings->id], settings->fref);
	dprintf("%s(): %s byp_clk_m2=%lf MHz\n", __func__,
		dpll_am335x_names[settings->id], settings->fbyp_clk_m2);
	dprintf("%s(): %s byp_clk_m3=%lf MHz\n", __func__,
		dpll_am335x_names[settings->id], settings->fbyp_clk_m3);
	dprintf("%s(): %s byp_clk_hsdiv=%lf MHz\n", __func__,
		dpll_am335x_names[settings->id], settings->fbyp_clk_hsdiv);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hsdiv_am335x_settings_extract
 * @BRIEF		extract HSDIV DPLL settings from registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		id: HSDIV valid ID
 * @param[in]		dpll_regs: dpll registers to extract from
 * @param[in,out]	settings: struct with extracted HSDIV settings
 * @DESCRIPTION		extract DPLL HSDIV settings from registers
 *//*------------------------------------------------------------------------ */
int hsdiv_am335x_settings_extract(unsigned int id, reg *hsdiv_reg,
	hsdiv_am335x_settings * settings)
{
	unsigned int val;

	CHECK_NULL_ARG(settings, OMAPCONF_ERR_ARG);

	settings->rate = 0.0;
	settings->id = (hsdiv_am335x_id) id;

	if (hsdiv_reg == NULL) {
		settings->present = 0;
		settings->status = 0;
		settings->div = 1;
		dprintf("%s(): %s does not exist.\n", __func__,
			hsdiv_am335x_name_get(id));
	} else {
		val = reg_read(hsdiv_reg);
		settings->present = 1;
		settings->div = extract_bitfield(val, 0, 5);
		settings->status = extract_bit(val, 9);
		dprintf("%s(): %s reg: %s = 0x%08X, DIV=%u, CLKST=%u\n",
			__func__, hsdiv_am335x_name_get(id), hsdiv_reg->name,
			val, settings->div, settings->status);
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hsdiv_am335x_rates_calc
 * @BRIEF		calculate DPLL HSDIV output rates
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		settings: DPLL settings struct
 * @param[in]		ignore: do not consider DPLL STOP status.
 *			Useful for functions that needs the DPLL output
 *			frequencies even when DPLL is stopped
 *			(e.g. autdit, clock tree, OPP detection, etc)
 * @DESCRIPTION		calculate DPLL HSDIV output rates
 *//*------------------------------------------------------------------------ */
int hsdiv_am335x_rates_calc(dpll_am335x_settings *settings,
	unsigned short ignore)
{
	unsigned short i;
	dpll_status st;

	CHECK_NULL_ARG(settings, OMAPCONF_ERR_ARG);

	/* Initialize all rates */
	for (i = 0; i < HSDIV_AM335X_ID_MAX; i++)
		(settings->hsdiv)[i].rate = 0.0;

	/* Determine DPLL outputs rate */
	if ((settings->status == DPLL_STATUS_STOPPED) && ignore) {
		st = DPLL_STATUS_LOCKED;
		dprintf("%s(): warning %s considered as locked\n", __func__,
			dpll_am335x_name_get((settings->dpll).id));
	} else {
		st = settings->status;
	}

	switch (st) {
	case DPLL_STATUS_BYPASSED:
		for (i = 0; i < HSDIV_AM335X_ID_MAX; i++) {
			if ((settings->hsdiv)[i].present == 0)
				continue;
			(settings->hsdiv)[i].rate =
				(settings->dpll).fbyp_clk_hsdiv;
			dprintf("%s(): %s bypassed, %s=%lfMHz\n", __func__,
				dpll_am335x_name_get((settings->dpll).id),
				hsdiv_am335x_name_get(i),
				(settings->hsdiv)[i].rate);
		}
		break;
	case DPLL_STATUS_LOCKED:
		for (i = 0; i < HSDIV_AM335X_ID_MAX; i++) {
			if ((settings->hsdiv)[i].present == 0)
				continue;
			(settings->hsdiv)[i].rate =
				(settings->dpll).MN.clkdcoldo_rate /
				(double) (settings->hsdiv)[i].div;
			dprintf("%s(): %s locked, %s=%lfMHz\n", __func__,
				dpll_am335x_name_get((settings->dpll).id),
				hsdiv_am335x_name_get(i),
				(settings->hsdiv)[i].rate);
		}
		break;
	case DPLL_STATUS_STOPPED:
		/* nothing to do, all output speeds already set to 0.0 */
		dprintf("%s(): %s stopped, all HSDIV rates=0.0MHz\n", __func__,
			dpll_am335x_name_get((settings->dpll).id));
		break;
	default:
		fprintf(stderr, "%s(): incorrect %s status! (%u)\n", __func__,
			dpll_am335x_names[(settings->dpll).id], st);
		return OMAPCONF_ERR_INTERNAL;
	}

	return 0;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_am335x_rates_calc
 * @BRIEF		calculate DPLL output rates
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		settings: DPLL settings struct
 * @param[in]		ignore: do not consider DPLL STOP status.
 *			Useful for functions that needs the DPLL output
 *			frequencies even when DPLL is stopped
 *			(e.g. autdit, clock tree, OPP detection, etc)
 * @DESCRIPTION		calculate DPLL output rates
 *//*------------------------------------------------------------------------ */
int dpll_am335x_rates_calc(dpll_am335x_settings *settings,
	unsigned short ignore)
{
	dpll_status st;

	CHECK_NULL_ARG(settings, OMAPCONF_ERR_ARG);

	/* Initialzie all rates */
	(settings->dpll).fdpll = 0.0;
	(settings->dpll).MN.M2_rate = 0.0;
	(settings->dpll).MN.clkdcoldo_rate = 0.0;

	/* Compute DPLL lock frequency */
	dpll_am335x_lock_freq_calc(&(settings->dpll));
	dprintf("%s(): %s lock freq=%lfMHz\n", __func__,
		dpll_am335x_name_get((settings->dpll).id),
		(settings->dpll).fdpll);

	/* Determine DPLL outputs rate */
	if ((settings->status == DPLL_STATUS_STOPPED) && ignore) {
		dprintf("%s(): warning %s considered as locked\n", __func__,
			dpll_am335x_name_get((settings->dpll).id));
		st = DPLL_STATUS_LOCKED;
	} else {
		st = settings->status;
	}

	switch (st) {
	case DPLL_STATUS_BYPASSED:
		(settings->dpll).fdpll = 0;
		if ((settings->dpll).MN.M2_present == 0)
			break;
		if ((settings->dpll).bypass_clk) {
			if (settings->byp_clk_sel == 0)
				(settings->dpll).MN.M2_rate =
					(settings->dpll).fbyp_clk_m2;
			else if (settings->byp_clk_sel == 1)
				(settings->dpll).MN.M2_rate =
					(settings->dpll).fbyp_clk_m3;
			else
				(settings->dpll).MN.M2_rate =
					(settings->dpll).fref;
		} else {
			(settings->dpll).MN.M2_rate = (settings->dpll).fref;
		}
		dprintf("%s(): %s bypassed, M2=%lfMHz\n", __func__,
			dpll_am335x_name_get((settings->dpll).id),
			(settings->dpll).MN.M2_rate);
		/*
		 * No bypass mode available for CLKDCOLDO output.
		 * clkdcoldo_rate already set to 0.0
		 */
		break;
	case DPLL_STATUS_LOCKED:
		if ((settings->dpll).type == DPLL_TYPE_A)
			(settings->dpll).MN.clkdcoldo_rate =
				(settings->dpll).fdpll * 2.0;
		else
			(settings->dpll).MN.clkdcoldo_rate =
				(settings->dpll).fdpll;
		dprintf("%s(): %s locked, CLKDCOLDO=%lfMHz\n", __func__,
			dpll_am335x_name_get((settings->dpll).id),
			(settings->dpll).MN.clkdcoldo_rate);

		if ((settings->dpll).MN.M2_present == 0)
			break;
		(settings->dpll).MN.M2_rate = (settings->dpll).fdpll /
			(double) (settings->dpll).MN.M2;
		dprintf("%s(): %s locked, CLKOUT=%lfMHz\n", __func__,
			dpll_am335x_name_get((settings->dpll).id),
			(settings->dpll).MN.M2_rate);
		break;
	case DPLL_STATUS_STOPPED:
		/* nothing to do, all output speeds already set to 0.0 */
		dprintf("%s(): %s stopped, all rates=0.0MHz\n", __func__,
			dpll_am335x_name_get((settings->dpll).id));
		break;
	default:
		fprintf(stderr, "%s(): incorrect %s status! (%u)\n", __func__,
			dpll_am335x_names[(settings->dpll).id], st);
		return OMAPCONF_ERR_INTERNAL;
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_am335x_settings_extract
 * @BRIEF		extract DPLL settings from registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	settings: struct with extracted DPLL settings
 * @param[in]		id: valid DPLL ID
 * @param[in]		out_id: valid DPLL OUTPUT ID
 * @param[in]		ignore: do not consider DPLL STOP status.
 *			Useful for functions that needs the DPLL output
 *			frequencies even when DPLL is stopped
 *			(e.g. autdit, clock tree, OPP detection, etc)
 * @DESCRIPTION		extract DPLL settings from registers
 *//*------------------------------------------------------------------------ */
int dpll_am335x_settings_extract(dpll_am335x_settings *settings,
	unsigned int id, unsigned short ignore)
{
	int ret;
	unsigned short i;
	unsigned int val;
	dpll_type type;
	dpll_settings_regs *dpll_regs;
	reg **hsdiv_regs;

	CHECK_NULL_ARG(settings, OMAPCONF_ERR_ARG);

	/*
	 * AM335X does not follow the exact format for OMAP5/DRA7 DPLL types
	 * However, there is enough overlap that the type structs can be used
	 * without having to change the struct itself.
	 */
	switch (id) {
	case DPLL_AM335X_PER:
		type = DPLL_TYPE_B;
		break;
	case DPLL_AM335X_CORE:
	case DPLL_AM335X_MPU:
	case DPLL_AM335X_DDR:
	case DPLL_AM335X_DISP:
		type = DPLL_TYPE_A;
		break;
	default:
		return OMAPCONF_ERR_ARG;
	}

	dprintf("\n\n### %s() EXTRACTING %s SETTINGS (IGNORE=%u) ###\n",
		__func__, dpll_am335x_name_get(id), ignore);

	dpll_regs = (dpll_settings_regs *) &(dpll_am335x_regs[id]);
	hsdiv_regs = (reg **) dpll_am335x_hsdiv_regs[id];

	ret = dpll_settings_extract(id, type, dpll_regs, &(settings->dpll));
	if (ret != 0)
		return ret;

	val = reg_read(dpll_regs->cm_clkmode_dpll);
	dprintf("%s(): %s reg: %s = 0x%08X\n", __func__,
		dpll_am335x_name_get(id),
		(dpll_regs->cm_clkmode_dpll)->name, val);

	val = extract_bitfield(val, 0, 3);
	if ((settings->dpll).lock_status == 1) {
		settings->status = DPLL_STATUS_LOCKED;
	} else {
		switch (val) {
		case DPLL_LOW_POWER_STOP:
			settings->status = DPLL_STATUS_STOPPED;
			break;
		case DPLL_MN_BYPASS:
		case DPLL_LOW_POWER_BYPASS:
		case DPLL_FAST_RELOCK_BYPASS:
			settings->status = DPLL_STATUS_BYPASSED;
			break;
		default:
			settings->status = DPLL_STATUS_MAX;
		}
	}
	dprintf("%s(): %s status: %s\n", __func__, dpll_am335x_name_get(id),
		dpll_status_name_get(settings->status));

	for (i = HSDIV_AM335X_M4; i < HSDIV_AM335X_ID_MAX; i++) {
		ret = hsdiv_am335x_settings_extract(i, hsdiv_regs[i],
			&(settings->hsdiv)[i]);
		if (ret != 0)
			return ret;
	}

	/*
	 * CLKINPULOW mux select for the bypass clocks
	 * if CLKINPULOW mux not avaliable, set to -1
	 */
	ret = mem_read(AM335X_PLL_CLKINPULOW_CTRL, &val);
	if (ret != 0)
		return ret;
	switch (id) {
	case DPLL_AM335X_PER:
	case DPLL_AM335X_CORE:
		settings->byp_clk_sel = -1;
		break;
	case DPLL_AM335X_MPU:
		settings->byp_clk_sel = extract_bit(val, 0);
		break;
	case DPLL_AM335X_DDR:
		settings->byp_clk_sel = extract_bit(val, 1);
		break;
	case DPLL_AM335X_DISP:
		settings->byp_clk_sel = extract_bit(val, 2);
		break;
	default:
		settings->byp_clk_sel = -1;
	}
	dprintf("%s(): %s byp clk sel: %d\n", __func__,
		dpll_am335x_name_get(id), settings->byp_clk_sel);

	ret = dpll_am335x_clk_sources_get(&(settings->dpll), ignore);
	if (ret != 0)
		return ret;
	ret = dpll_am335x_rates_calc(settings, ignore);
	if (ret != 0)
		return ret;
	ret = hsdiv_am335x_rates_calc(settings, ignore);
	if (ret != 0)
		return ret;

	(settings->dpll).initialized = 1;
	dprintf("### %s(): %s SETTINGS EXTRACTED (IGNORE=%u) ###\n", __func__,
		dpll_am335x_name_get(id), ignore);

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_am335x_settings_get
 * @BRIEF		return DPLL settings struct pointer
 * @RETURNS		DPLL settings struct pointer in case of success
 *			NULL otherwise
 * @param[in]		id: valid DPLL ID
 * @param[in]		ignore: do not consider DPLL STOP status.
 *			Useful for functions that needs the DPLL output
 *			frequencies even when DPLL is stopped
 *			(e.g. autdit, clock tree, OPP detection, etc)
 * @DESCRIPTION		return DPLL settings struct pointer
 *			If DPLL settings not yet extracted, do it.
 *//*------------------------------------------------------------------------ */
dpll_am335x_settings *dpll_am335x_settings_get(unsigned int id,
	unsigned short ignore)
{
	int ret;
	dpll_am335x_settings *settings;

	CHECK_ARG_LESS_THAN(id, DPLL_AM335X_ID_MAX, NULL);

	/* Get struct pointer */
	if (ignore)
		settings = dpll_am335x_locked_settings_table[id];
	else
		settings = dpll_am335x_settings_table[id];

	/* If DPLL settings not yet extracted, do it */
	if ((settings->dpll).initialized == 0) {
		ret = dpll_am335x_settings_extract(settings, id, ignore);
		if (ret < 0) {
			fprintf(stderr, "%s(): error while extracting %s "
				"parameters! (%d)", __func__,
				dpll_am335x_name_get((dpll_am335x_id) id), ret);
			settings = NULL;
		}
	}

	return settings;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_am335x_output_rate_get
 * @BRIEF		return DPLL output clock rate (in MHz)
 * @RETURNS		DPLL output clock rate (in MHz) in case of success
 *			0.0 otherwise
 * @param[in]		id: valid DPLL ID
 * @param[in]		out_id: valid DPLL OUTPUT ID
 * @param[in]		ignore: do not consider DPLL STOP status.
 *			Useful for functions that needs the DPLL output
 *			frequencies even when DPLL is stopped
 *			(e.g. autdit, clock tree, OPP detection, etc)
 * @DESCRIPTION		return DPLL output clock rate (in MHz)
 *			If DPLL settings not yet extracted, do it.
 *//*------------------------------------------------------------------------ */
double dpll_am335x_output_rate_get(dpll_am335x_id id,
	dpll_am335x_output_id out_id, unsigned short ignore)
{
	int ret;
	dpll_am335x_settings *settings;
	double rate;

	CHECK_ARG_LESS_THAN(id, DPLL_AM335X_ID_MAX, 0.0);
	CHECK_ARG_LESS_THAN(out_id, DPLL_AM335X_OUTPUT_ID_MAX, 0.0);

	/* Get struct pointer */
	if (ignore)
		settings = dpll_am335x_locked_settings_table[id];
	else
		settings = dpll_am335x_settings_table[id];

	/* If DPLL settings not yet extracted, do it */
	if ((settings->dpll).initialized == 0) {
		ret = dpll_am335x_settings_extract(settings, id, ignore);
		if (ret < 0) {
			fprintf(stderr, "%s(): error while extracting %s "
				"parameters! (%d)", __func__,
				dpll_am335x_name_get(id), ret);
			rate = 0.0;
			goto dpll_am335x_output_rate_get_end;
		}
	}

	/* Get output rate */
	switch (out_id) {
	case DPLL_AM335X_CLKOUT:
		rate = (settings->dpll).MN.M2_rate;
		break;
	case DPLL_AM335X_CLKOUTX2:
	case DPLL_AM335X_CLKDCOLDO:
		rate = (settings->dpll).MN.clkdcoldo_rate;
		break;
	case DPLL_AM335X_CLKOUTHIF:
	case DPLL_AM335X_CORE_CLKOUT_M4:
		rate = (settings->hsdiv)[HSDIV_AM335X_M4].rate;
		break;
	case DPLL_AM335X_CORE_CLKOUT_M5:
		rate = (settings->hsdiv)[HSDIV_AM335X_M5].rate;
		break;
	case DPLL_AM335X_CORE_CLKOUT_M6:
		rate = (settings->hsdiv)[HSDIV_AM335X_M6].rate;
		break;
	default:
		/* should never happen, to remove compilation warning*/
		rate = 0.0;
	}

dpll_am335x_output_rate_get_end:
	dprintf("%s(%s, %s, %u)=%lfMHz\n", __func__, dpll_am335x_name_get(id),
		dpll_am335x_output_name_get(out_id), ignore, rate);
	return rate;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_am335x_init
 * @BRIEF		allocate memory for dpll settings structs and save
 *			dpll settings in it.
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_UNEXPECTED
 * @DESCRIPTION		allocate memory for dpll settings structs and save
 *			dpll settings in it.
 *//*------------------------------------------------------------------------ */
int dpll_am335x_init(void)
{
	dpll_am335x_id id;
	unsigned int i;
	int ret;
	static const dpll_am335x_id ordered_ids[DPLL_AM335X_ID_MAX] = {
		DPLL_AM335X_PER,
		DPLL_AM335X_CORE,
		DPLL_AM335X_MPU,
		DPLL_AM335X_DDR,
		DPLL_AM335X_DISP};

	dprintf("\n%s(): retrieving all DPLL settings\n", __func__);
	/*
	 * Allocate memory for dpll settings structs
	 * And save dpll settings into it.
	 */
	for (id = DPLL_AM335X_PER; id < DPLL_AM335X_ID_MAX; id++) {
		dpll_am335x_settings_table[id] =
			malloc(sizeof(dpll_am335x_settings));
		if (dpll_am335x_settings_table[id] == NULL)
			return OMAPCONF_ERR_UNEXPECTED;
		(dpll_am335x_settings_table[id]->dpll).initialized = 0;

		dpll_am335x_locked_settings_table[id] =
			malloc(sizeof(dpll_am335x_settings));
		if (dpll_am335x_locked_settings_table[id] == NULL)
			return OMAPCONF_ERR_UNEXPECTED;
		(dpll_am335x_locked_settings_table[id]->dpll).initialized = 0;
	}

	for (i = 0; i < DPLL_AM335X_ID_MAX; i++) {
		id = ordered_ids[i];
		ret = dpll_am335x_settings_extract(
			dpll_am335x_settings_table[id], id, 0);
		if (ret < 0) {
			fprintf(stderr, "%s(): error while extracting %s "
				"parameters! (%d)", __func__,
				dpll_am335x_name_get(id), ret);
			return ret;
		}

		/*
		 * Also get DPLL params ignoring DPLL STOPPED status to also
		 * show all output speeds when DPLL is locked.
		 */
		ret = dpll_am335x_settings_extract(
			dpll_am335x_locked_settings_table[id], id, 1);
		if (ret < 0) {
			fprintf(stderr, "%s(): error while extracting %s "
				"parameters! (%d)", __func__,
				dpll_am335x_name_get(id), ret);
			return ret;
		}
	}

	dprintf("%s(): all DPLL settings retrieved\n\n", __func__);
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_am335x_free
 * @BRIEF		free memory for dpll settings structs and save
 *			dpll settings in it.
 * @RETURNS		0 on success
 * @DESCRIPTION		free memory for dpll settings structs and save
 *			dpll settings in it.
 *//*------------------------------------------------------------------------ */
int dpll_am335x_free(void)
{
	dpll_am335x_id id;

	for (id = DPLL_AM335X_PER; id < DPLL_AM335X_ID_MAX; id++) {
		if (dpll_am335x_settings_table[id] != NULL)
			free(dpll_am335x_settings_table[id]);
		if (dpll_am335x_locked_settings_table[id] != NULL)
			free(dpll_am335x_locked_settings_table[id]);
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_am335x_main
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
 *			argv[1] = DPLL ID ("mpu", "per", "core", "ddr", "disp")
 *				argv[1] may be omitted (then "all" assumed)
 *//*------------------------------------------------------------------------ */
int dpll_am335x_main(int argc, char *argv[])
{
	int ret = 0;
	dpll_am335x_id id;

	if (argc == 1) {
		id = DPLL_AM335X_ID_MAX;
	} else if (argc != 2) {
		goto dpll_am335x_main_err_arg;
	} else if (strcmp(argv[1], "all") == 0) {
		id = DPLL_AM335X_ID_MAX;
	} else {
		id = dpll_am335x_s2id(argv[1]);
		if (id == DPLL_AM335X_ID_MAX)
			goto dpll_am335x_main_err_arg;
	}

	if (strcmp(argv[0], "dump") == 0)
		ret = dpll_am335x_dump(stdout, id);
	else if (strcmp(argv[0], "cfg") == 0)
		ret = dpll_am335x_show(stdout);
	else
		goto dpll_am335x_main_err_arg;
	goto dpll_am335x_main_end;

dpll_am335x_main_err_arg:
	help(HELP_DPLL);
	ret = OMAPCONF_ERR_ARG;

dpll_am335x_main_end:
	return ret;
}
