/*
 *
 * @Component			OMAPCONF
 * @Filename			dpll_dra7xx.c
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


#include <cm_dra7xx-defs.h>
#include <dpll_dra7xx.h>
#include <dpll_dra7xx-data.h>
#include <clock_dra7xx.h>
#include <voltdomain.h>
#include <autoadjust_table.h>
#include <stdio.h>
#include <lib.h>
#include <help.h>
#include <cpuinfo.h>
#include <string.h>
#include <opp.h>


/* #define DPLL_DRA7XX_DEBUG */
#ifdef DPLL_DRA7XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


#define DPLL_DRA7XX_AUDIT_SHOW_STATUS(curr, golden) \
		if (curr == golden) { \
			snprintf(table[row++][3], TABLE_MAX_ELT_LEN, "PASS"); \
		} else { \
			snprintf(table[row++][3], TABLE_MAX_ELT_LEN, "FAIL"); \
			(*err_nbr)++; \
		}


#define DPLL_DRA7XX_AUDIT_CHECK_GOLDEN_SETTING(setting, defval, gotolabel) \
		if (setting == defval) {\
			/* Golden setting not available */\
			snprintf(table[row][2], TABLE_MAX_ELT_LEN,\
				"Not available");\
			snprintf(table[row][3], TABLE_MAX_ELT_LEN, "WARN.");\
			(*wng_nbr)++;\
			row++;\
			goto gotolabel;\
		}


dpll_dra7xx_settings *dpll_dra7xx_settings_table[DPLL_DRA7XX_ID_MAX] = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL};


dpll_dra7xx_settings *dpll_dra7xx_locked_settings_table[DPLL_DRA7XX_ID_MAX] = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		print_reg
 * @BRIEF		Show register name, addr & content
 * @RETURNS		None
 * @param[in]		r: register. row: pointer to the row number
 * @DESCRIPTION		Show register name, addr & content
 *//*------------------------------------------------------------------------ */
void print_reg(char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN],
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
 * @FUNCTION		dpll_dra7xx_s2id
 * @BRIEF		convert string to valid DPLL ID
 * @RETURNS		DPLL_DRA7XX_MPU if s == "mpu"
 *			DPLL_DRA7XX_IVA if s == "iva"
 *			DPLL_DRA7XX_CORE if s == "core"
 *			DPLL_DRA7XX_PER if s == "per"
 *			DPLL_DRA7XX_ABE if s == "abe"
 *			DPLL_DRA7XX_EVE if s == "eve"
 *			DPLL_DRA7XX_DSP if s == "dsp"
 *			DPLL_DRA7XX_GMAC if s == "gmac"
 *			DPLL_DRA7XX_GPU if s == "gpu"
 *			DPLL_DRA7XX_DDR if s == "ddr"
 *			DPLL_DRA7XX_USB if s == "usb"
 *			DPLL_DRA7XX_PCIE_REF if s == "pcieref"
 *			DPLL_DRA7XX_ID_MAX otherwise
 * @param[in,out]	s: string
 * @DESCRIPTION		convert string to valid DPLL ID
 *//*------------------------------------------------------------------------ */
dpll_dra7xx_id dpll_dra7xx_s2id(char *s)
{
	int index;
	CHECK_NULL_ARG(s, DPLL_DRA7XX_ID_MAX);

	for (index = 0; index < DPLL_DRA7XX_ID_MAX; index++)
		if (strcmp(s, dpll_dra7xx_strings[index]) == 0)
			return (dpll_dra7xx_id) index;
	return DPLL_DRA7XX_ID_MAX;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_dra7xx_name_get
 * @BRIEF		return DPLL name
 * @RETURNS		DPLL name
 *			NULL in case of incorrect id
 * @param[in]		id: DPLL ID
 * @DESCRIPTION		return DPLL name
 *//*------------------------------------------------------------------------ */
const char *dpll_dra7xx_name_get(dpll_dra7xx_id id)
{
	CHECK_ARG_LESS_THAN(id, DPLL_DRA7XX_ID_MAX, NULL);

	return dpll_dra7xx_names[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_dra7xx_output_name_get
 * @BRIEF		return DPLL output name
 * @RETURNS		DPLL output name
 *			NULL in case of incorrect id
 * @param[in]		id: DPLL output ID
 * @DESCRIPTION		return DPLL output name
 *//*------------------------------------------------------------------------ */
const char *dpll_dra7xx_output_name_get(dpll_dra7xx_output_id id)
{
	CHECK_ARG_LESS_THAN(id, DPLL_DRA7XX_OUTPUT_ID_MAX, NULL);

	return dpll_dra7xx_output_names[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hsdiv_dra7xx_name_get
 * @BRIEF		return HS divider name
 * @RETURNS		HS divider name
 *			NULL in case of incorrect id
 * @param[in]		id: HS divider ID
 * @DESCRIPTION		return HS divider name
 *//*------------------------------------------------------------------------ */
const char *hsdiv_dra7xx_name_get(hsdiv_dra7xx_id id)
{
	CHECK_ARG_LESS_THAN(id, HSDIV_DRA7XX_ID_MAX, NULL);

	return hsdiv_dra7xx_names[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_dra7xx_dump
 * @BRIEF		dump selected DPLL registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in, out]	stream: output stream
 * @param[in]		id: DPLL ID
 *			If id == DPLL_DRA7XX_ID_MAX, dump all DPLL registers.
 * @DESCRIPTION		dump selected DPLL registers and pretty-print it to
 *			output stream.
 *//*------------------------------------------------------------------------ */
int dpll_dra7xx_dump(FILE *stream, dpll_dra7xx_id id)
{
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row, i;
	int err = 0;
	dpll_settings_regs dpll_regs;
	dpll_dra7xx_id dpll_id;
	reg *r;

	CHECK_ARG_LESS_THAN(id, DPLL_DRA7XX_ID_MAX + 1, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(stream, OMAPCONF_ERR_ARG);

	for (dpll_id = DPLL_DRA7XX_MPU; dpll_id < DPLL_DRA7XX_ID_MAX; dpll_id++) {
		if ((id != DPLL_DRA7XX_ID_MAX) && (dpll_id != id))
			continue;
		else {
			autoadjust_table_init(table);
			row = 0;
			snprintf(table[row][0], TABLE_MAX_ELT_LEN,
				"%s Reg. Name",	dpll_dra7xx_name_get(dpll_id));
			strncpy(table[row][1], "Reg. Address",
				TABLE_MAX_ELT_LEN);
			strncpy(table[row][2], "Reg. Value", TABLE_MAX_ELT_LEN);
			row++;

			dpll_regs = dpll_dra7xx_regs[dpll_id];
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
				print_reg(table, r, &row);
			}

			for (i = HSDIV_DRA7XX_H11; i < HSDIV_DRA7XX_ID_MAX; i++) {
				r = (reg *) dpll_dra7xx_hsdiv_regs[dpll_id][i];
				print_reg(table, r, &row);
			}

			autoadjust_table_print(table, row, 3);
		}
	}
	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_dra7xx_show
 * @BRIEF		analyze PLLs configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_UNEXPECTED
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		stream: output stream
 * @DESCRIPTION		analyze PLLs configuration
 *//*------------------------------------------------------------------------ */
int dpll_dra7xx_show(FILE *stream)
{
	int ret;

	ret = dpll_type_b_show(DPLL_DRA7XX_USB, DPLL_DRA7XX_ID_MAX, stream);
	if (ret != 0)
		return ret;
	ret = dpll_type_a_show(DPLL_DRA7XX_MPU, DPLL_DRA7XX_EVE, stream);
	if (ret != 0)
		return ret;
	return dpll_type_a_show(DPLL_DRA7XX_EVE, DPLL_DRA7XX_USB, stream);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_type_b_show
 * @BRIEF		show tpye B dpll module configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_UNEXPECTED
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		stream: output stream
 * @DESCRIPTION		show tpye B dpll module configuration
 *//*------------------------------------------------------------------------ */
int dpll_type_b_show(dpll_dra7xx_id start_id, dpll_dra7xx_id end_id, FILE *stream)
{
	int ret = 0;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row, row_max;
	dpll_dra7xx_id id;
	dpll_dra7xx_settings *settings, *settings_locked;

	autoadjust_table_init(table);
	row = 0;
	row_max = 0;
	strncpy(table[row][0], "DPLL Configuration", TABLE_MAX_ELT_LEN);

	for (id = start_id; id < end_id; id++) {
		row = 0;
		snprintf(table[row++][id - start_id + 1],
			TABLE_MAX_ELT_LEN, "%s",
			dpll_dra7xx_name_get(id));
		settings = dpll_dra7xx_settings_get(id, 0);
		if (settings == NULL) {
			fprintf(stderr, "%s(): error while getting %s "
				"parameters! (%d)", __func__,
				dpll_dra7xx_name_get(id), ret);
			return OMAPCONF_ERR_UNEXPECTED;
		}

		/*
		 * Also get DPLL params ignoring DPLL STOPPED status to also
		 * show all output speeds when DPLL is locked.
		 */
		settings_locked = dpll_dra7xx_settings_get(id, 1);
		if (settings_locked == NULL) {
			fprintf(stderr, "%s(): error while getting %s "
				"locked parameters! (%d)", __func__,
				dpll_dra7xx_name_get(id), ret);
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
		strncpy(table[row++][id - start_id + 1],
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
			"%-5u (x2)", settings->dpll.MN.M2);
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
		if (id == DPLL_DRA7XX_USB) {
			strncpy(table[row++][id - start_id + 1],
				(settings->dpll.MN.clkdcoldo_clkout_st == 1)
					? "Enabled" : "Gated",
					TABLE_MAX_ELT_LEN);
		} else {
			strncpy(table[row++][id - start_id + 1], "N/A", TABLE_MAX_ELT_LEN);
		}
			strncpy(table[row][0], "  Clock Speed (MHz)", TABLE_MAX_ELT_LEN);
		if (id == DPLL_DRA7XX_USB) {
			if (settings->status == DPLL_STATUS_LOCKED)
				snprintf(table[row++][id - start_id + 1],
					TABLE_MAX_ELT_LEN, "%u",
					(unsigned int) settings->dpll.MN.clkdcoldo_rate);
			else
				snprintf(table[row++][id - start_id + 1],
					TABLE_MAX_ELT_LEN, "%u (%u)",
					(unsigned int) settings->dpll.MN.clkdcoldo_rate,
					(unsigned int) settings_locked->dpll.MN.clkdcoldo_rate);
		} else {
			row++;
		}
		row++;

		strncpy(table[row++][0],
			"CLKOUTX2_M2_LDO Output", TABLE_MAX_ELT_LEN);
		strncpy(table[row][0], "  Status",
			TABLE_MAX_ELT_LEN);
		if (id == DPLL_DRA7XX_PCIE_REF) {
			strncpy(table[row++][id - start_id + 1],
				(settings->dpll.MN.clkoutldo_st == 1)
					? "Enabled" : "Gated",
					TABLE_MAX_ELT_LEN);
		} else {
			strncpy(table[row++][id - start_id + 1], "N/A", TABLE_MAX_ELT_LEN);
		}
			strncpy(table[row][0], "  Clock Speed (MHz)", TABLE_MAX_ELT_LEN);
		if (id == DPLL_DRA7XX_PCIE_REF) {
			if (settings->status == DPLL_STATUS_LOCKED)
				snprintf(table[row++][id - start_id + 1],
					TABLE_MAX_ELT_LEN, "%u",
					(unsigned int) settings->dpll.MN.clkoutldo_rate);
			else
				snprintf(table[row++][id - start_id + 1],
					TABLE_MAX_ELT_LEN, "%u (%u)",
					(unsigned int) settings->dpll.MN.clkoutldo_rate,
					(unsigned int) settings_locked->dpll.MN.clkoutldo_rate);
		} else {
			row++;
		}
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
 * @FUNCTION		dpll_type_a_show
 * @BRIEF		show tpye A dpll module configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_UNEXPECTED
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		stream: output stream
 * @DESCRIPTION		show tpye A dpll module configuration
 *//*------------------------------------------------------------------------ */
int dpll_type_a_show(dpll_dra7xx_id start_id, dpll_dra7xx_id end_id, FILE *stream)
{
	int ret = 0;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row, row_max;
	dpll_dra7xx_id id;
	hsdiv_dra7xx_id hsdiv_id;
	dpll_dra7xx_settings *settings, *settings_locked;

	autoadjust_table_init(table);
	row = 0;
	row_max = 0;
	strncpy(table[row][0], "DPLL Configuration", TABLE_MAX_ELT_LEN);

	for (id = start_id; id < end_id; id++) {
		row = 0;
		snprintf(table[row++][id - start_id + 1], TABLE_MAX_ELT_LEN, "%s",
			dpll_dra7xx_name_get(id));
		settings = dpll_dra7xx_settings_get(id, 0);
		if (settings == NULL) {
			fprintf(stderr, "%s(): error while getting %s "
				"parameters! (%d)", __func__,
				dpll_dra7xx_name_get(id), ret);
			return OMAPCONF_ERR_UNEXPECTED;
		}

		/*
		 * Also get DPLL params ignoring DPLL STOPPED status to also
		 * show all output speeds when DPLL is locked.
		 */
		settings_locked = dpll_dra7xx_settings_get(id, 1);
		if (settings_locked == NULL) {
			fprintf(stderr, "%s(): error while getting %s "
				"locked parameters! (%d)", __func__,
				dpll_dra7xx_name_get(id), ret);
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
		strncpy(table[row++][id - start_id + 1],
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
		if (dpll_dra7xx_regs[id].cm_bypclk_dpll != NULL)
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
		row++;

		strncpy(table[row][0], "Duty Cycle Correction (DCC)",
			TABLE_MAX_ELT_LEN);

		if ((id == DPLL_DRA7XX_MPU) && (settings->dpll.DCC.en == 1)) {
			snprintf(table[row][id - start_id + 1],
				TABLE_MAX_ELT_LEN,
				"Enabled");
		} else {
			snprintf(table[row][id - start_id + 1],
				TABLE_MAX_ELT_LEN,
				"Disabled");
		}
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
			snprintf(table[row++][id - start_id + 1], TABLE_MAX_ELT_LEN,
				"%-5u (x%d)", settings->dpll.MN.M2,
				(settings->dpll.DCC.en == 1)? 1:2);
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

		strncpy(table[row++][0], "X2_M2 Output", TABLE_MAX_ELT_LEN);
		if (settings->dpll.MN.X2_M2_present) {
			strncpy(table[row][0], "  Status", TABLE_MAX_ELT_LEN);
			strncpy(table[row++][id - start_id + 1],
				(settings->dpll.MN.X2_M2_clkout_st == 1) ?
					"Enabled" : "Gated",
					TABLE_MAX_ELT_LEN);
			strncpy(table[row][0], "  Clock Divider",
				TABLE_MAX_ELT_LEN);
			snprintf(table[row++][id - start_id + 1], TABLE_MAX_ELT_LEN,
				"%-5u", settings->dpll.MN.M2);
			strncpy(table[row][0], "  Clock Speed (MHz)",
				TABLE_MAX_ELT_LEN);
			if (settings->status == DPLL_STATUS_LOCKED)
				snprintf(table[row++][id - start_id + 1],
					TABLE_MAX_ELT_LEN, "%u",
					(unsigned int) settings->dpll.MN.X2_M2_rate);
			else
				snprintf(table[row++][id - start_id + 1],
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
			if (id != DPLL_DRA7XX_MPU) {
				strncpy(table[row][0], "  Status",
					TABLE_MAX_ELT_LEN);
				strncpy(table[row++][id - start_id + 1],
					(settings->dpll.MN.X2_M3_clkout_st == 1)
						? "Enabled" : "Gated",
						TABLE_MAX_ELT_LEN);
			}
			strncpy(table[row][0], "  Clock Divider",
				TABLE_MAX_ELT_LEN);
			snprintf(table[row++][id - start_id + 1], TABLE_MAX_ELT_LEN,
				"%-5u", settings->dpll.MN.M3);
			strncpy(table[row][0], "  Clock Speed (MHz)",
				TABLE_MAX_ELT_LEN);
			if (settings->status == DPLL_STATUS_LOCKED)
				snprintf(table[row++][id - start_id + 1],
					TABLE_MAX_ELT_LEN, "%u",
					(unsigned int) settings->dpll.MN.X2_M3_rate);
			else
				snprintf(table[row++][id - start_id + 1],
				TABLE_MAX_ELT_LEN, "%u (%u)",
				(unsigned int) settings->dpll.MN.X2_M3_rate,
				(unsigned int) settings_locked->dpll.MN.X2_M3_rate);
		} else {
			row += 3;
		}

		for (hsdiv_id = HSDIV_DRA7XX_H11; hsdiv_id < HSDIV_DRA7XX_ID_MAX; hsdiv_id++) {
			row++;
			if ((settings->hsdiv)[hsdiv_id].present == 0) {
				row += 4;
			} else {
				snprintf(table[row++][0], TABLE_MAX_ELT_LEN,
					"%s Output",
					hsdiv_dra7xx_name_get(hsdiv_id));
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
 * @FUNCTION		dpll_dra7xx_clk_sources_get
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
int dpll_dra7xx_clk_sources_get(dpll_settings *settings, unsigned short ignore)
{
	CHECK_NULL_ARG(settings, OMAPCONF_ERR_ARG);

	if (dpll_dra7xx_sources[settings->id].ref_clk != CLK_DRA7XX_ID_MAX)
		settings->fref = clk_dra7xx_rate_get(
			(clk_dra7xx_id) dpll_dra7xx_sources[settings->id].ref_clk,
			ignore);
	else
		settings->fref = 0.0;

	if (dpll_dra7xx_sources[settings->id].byp_clk_m2 != CLK_DRA7XX_ID_MAX)
		settings->fbyp_clk_m2 = clk_dra7xx_rate_get(
			(clk_dra7xx_id) dpll_dra7xx_sources[settings->id].byp_clk_m2, ignore);
	else
		settings->fbyp_clk_m2 = 0.0;

	if (dpll_dra7xx_sources[settings->id].byp_clk_m3 != CLK_DRA7XX_ID_MAX)
		settings->fbyp_clk_m3 = clk_dra7xx_rate_get(
			(clk_dra7xx_id) dpll_dra7xx_sources[settings->id].byp_clk_m3, ignore);
	else
		settings->fbyp_clk_m3 = 0.0;

	if (dpll_dra7xx_sources[settings->id].byp_clk_hsdiv != CLK_DRA7XX_ID_MAX)
		settings->fbyp_clk_hsdiv = clk_dra7xx_rate_get(
			(clk_dra7xx_id) dpll_dra7xx_sources[settings->id].byp_clk_hsdiv, ignore);
	else
		settings->fbyp_clk_hsdiv = 0.0;

	dprintf("%s(): %s Fref=%lf MHz\n", __func__,
		dpll_dra7xx_names[settings->id], settings->fref);
	dprintf("%s(): %s byp_clk_m2=%lf MHz\n", __func__,
		dpll_dra7xx_names[settings->id], settings->fbyp_clk_m2);
	dprintf("%s(): %s byp_clk_m3=%lf MHz\n", __func__,
		dpll_dra7xx_names[settings->id], settings->fbyp_clk_m3);
	dprintf("%s(): %s byp_clk_hsdiv=%lf MHz\n", __func__,
		dpll_dra7xx_names[settings->id], settings->fbyp_clk_hsdiv);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hsdiv_dra7xx_settings_extract
 * @BRIEF		extract DRA7 HSDIV settings from registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		id: HSDIV valid ID
 * @param[in]		dpll_regs: dpll registers to extract from
 * @param[in, out]	settings: struct with extracted HSDIV settings
 * @DESCRIPTION		extract DRA7 HSDIV settings from registers
 *//*------------------------------------------------------------------------ */
int hsdiv_dra7xx_settings_extract(unsigned int id,
	 reg *hsdiv_reg, hsdiv_dra7xx_settings *settings)
{
	unsigned int val;

	CHECK_NULL_ARG(settings, OMAPCONF_ERR_ARG);

	settings->rate = 0.0;
	settings->id = (hsdiv_dra7xx_id) id;

	if (hsdiv_reg == NULL) {
		settings->present = 0;
		settings->status = 0;
		settings->div = 1;
		dprintf("%s(): %s does not exist.\n", __func__,
			hsdiv_dra7xx_name_get(id));
	} else {
		val = reg_read(hsdiv_reg);
		settings->present = 1;
		settings->div = extract_bitfield(val, 0, 6);
		settings->status = extract_bit(val, 9);
		dprintf("%s(): %s reg: %s = 0x%08X, DIV=%u, CLKST=%u\n",
			__func__, hsdiv_dra7xx_name_get(id), hsdiv_reg->name, val,
			settings->div, settings->status);
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hsdiv_dra7xx_rates_calc
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
int hsdiv_dra7xx_rates_calc(dpll_dra7xx_settings *settings,
	unsigned short ignore)
{
	unsigned short i;
	dpll_status st;

	CHECK_NULL_ARG(settings, OMAPCONF_ERR_ARG);

	/* Initialize all rates */
	for (i = 0; i < HSDIV_DRA7XX_ID_MAX; i++)
		(settings->hsdiv)[i].rate = 0.0;


	/* Determine DPLL outputs rate */
	if ((settings->status == DPLL_STATUS_STOPPED) && ignore) {
		st = DPLL_STATUS_LOCKED;
		dprintf("%s(): warning %s considered as locked\n", __func__,
			dpll_dra7xx_name_get((settings->dpll).id));
	} else {
		st = settings->status;
	}

	switch (st) {
	case DPLL_STATUS_BYPASSED:
		for (i = 0; i < HSDIV_DRA7XX_ID_MAX; i++) {
			if ((settings->hsdiv)[i].present == 0)
				continue;
			(settings->hsdiv)[i].rate =
				(settings->dpll).fbyp_clk_hsdiv;
			dprintf("%s(): %s bypassed, %s=%lfMHz\n", __func__,
				dpll_dra7xx_name_get((settings->dpll).id),
				hsdiv_dra7xx_name_get(i),
				(settings->hsdiv)[i].rate);
		}
		break;

	case DPLL_STATUS_LOCKED:
		for (i = 0; i < HSDIV_DRA7XX_ID_MAX; i++) {
			if ((settings->hsdiv)[i].present == 0)
				continue;
			/*
			 * Some 'nice' ES2.x HW hacks to handle ...
			 * There is an additional divider by 2,
			 * and special value '63' is actually a divider by 2.5.
			 */
			if ((cpu_revision_get() != REV_ES1_0) &&
					((settings->dpll).id == DPLL_DRA7XX_CORE) &&
					(i == HSDIV_DRA7XX_H14)) {
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
				dpll_dra7xx_name_get((settings->dpll).id),
				hsdiv_dra7xx_name_get(i),
				(settings->hsdiv)[i].rate);
		}
		break;

	case DPLL_STATUS_STOPPED:
		/* nothing to do, all HSDIV output rates already set to 0.0 */
		dprintf("%s(): %s stopped, all HSDIV rates=0.0MHz\n", __func__,
			dpll_dra7xx_name_get((settings->dpll).id));
		break;

	default:
		fprintf(stderr, "%s(): incorrect %s status! (%u)\n", __func__,
			dpll_dra7xx_names[(settings->dpll).id], st);
		return OMAPCONF_ERR_INTERNAL;
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_dra7xx_rates_calc
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
int dpll_dra7xx_rates_calc(dpll_dra7xx_settings *settings,
	unsigned short ignore)
{
	dpll_status st;

	CHECK_NULL_ARG(settings, OMAPCONF_ERR_ARG);

	/* Initialize all rates */
	(settings->dpll).fdpll = 0.0;
	(settings->dpll).MN.M2_rate = 0.0;
	(settings->dpll).MN.X2_M2_rate = 0.0;
	(settings->dpll).MN.X2_M3_rate = 0.0;
	(settings->dpll).MN.clkdcoldo_rate = 0.0;
	(settings->dpll).MN.clkoutldo_rate = 0.0;

	/* Compute DPLL lock frequency */
	dpll_lock_freq_calc(&(settings->dpll));
	dprintf("%s(): %s lock freq=%lfMHz\n", __func__,
		dpll_dra7xx_name_get((settings->dpll).id), (settings->dpll).fdpll);

	/* Determine DPLL outputs rate */
	if ((settings->status == DPLL_STATUS_STOPPED) && ignore) {
		dprintf("%s(): warning %s considered as locked\n", __func__,
			dpll_dra7xx_name_get((settings->dpll).id));
		st = DPLL_STATUS_LOCKED;
	} else {
		st = settings->status;
	}

	switch (st) {
	case DPLL_STATUS_BYPASSED:
		(settings->dpll).fdpll = 0.0;
		if ((settings->dpll).MN.M2_present == 0)
			goto m3_rate_bp_calc;
		(settings->dpll).MN.X2_M2_rate = (settings->dpll).fbyp_clk_hsdiv;
		dprintf("%s(): %s bypassed, X2_M2=%lfMHz\n", __func__,
			dpll_dra7xx_name_get((settings->dpll).id),
			(settings->dpll).MN.X2_M2_rate);
		(settings->dpll).MN.M2_rate = (settings->dpll).fbyp_clk_hsdiv;
		dprintf("%s(): %s bypassed, M2=%lfMHz\n", __func__,
			dpll_dra7xx_name_get((settings->dpll).id),
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
			dpll_dra7xx_name_get((settings->dpll).id),
			(settings->dpll).MN.X2_M3_rate);
		break;

	case DPLL_STATUS_LOCKED:
		if ((settings->dpll).MN.M2_present == 0)
			goto m3_rate_locked_calc;
		if ((settings->dpll).type == DPLL_TYPE_A) {
			(settings->dpll).MN.X2_M2_rate = (settings->dpll).fdpll
				/ (double) (settings->dpll).MN.M2;
			dprintf("%s(): %s locked, X2_M2=%lfMHz\n", __func__,
				dpll_dra7xx_name_get((settings->dpll).id),
				(settings->dpll).MN.X2_M2_rate);
			if ((settings->dpll).DCC.en == 0)
				(settings->dpll).MN.M2_rate =
					(settings->dpll).MN.X2_M2_rate / 2.0;
			else
				(settings->dpll).MN.M2_rate =
					(settings->dpll).MN.X2_M2_rate;
			dprintf("%s(): %s locked, M2=%lfMHz\n", __func__,
				dpll_dra7xx_name_get((settings->dpll).id),
				(settings->dpll).MN.M2_rate);
		} else {
			(settings->dpll).MN.M2_rate = (settings->dpll).fdpll /
				(double) (settings->dpll).MN.M2;
			(settings->dpll).MN.clkdcoldo_rate =
				(settings->dpll).fdpll;
			dprintf("%s(): %s locked, CLKOUT=%lfMHz "
				"CLKDCOLDO=%lfMHz\n", __func__,
				dpll_dra7xx_name_get((settings->dpll).id),
				(settings->dpll).MN.M2_rate,
				(settings->dpll).MN.clkdcoldo_rate);
		}

m3_rate_locked_calc:
		if ((settings->dpll).MN.M3_present == 0)
			break;
		(settings->dpll).MN.X2_M3_rate = (settings->dpll).fdpll /
			(double) (settings->dpll).MN.M3;
		dprintf("%s(): %s locked, X2_M3=%lfMHz\n", __func__,
			dpll_dra7xx_name_get((settings->dpll).id),
			(settings->dpll).MN.X2_M3_rate);
		break;

	case DPLL_STATUS_STOPPED:
		/* nothing to do, all output speeds already set to 0.0 */
		dprintf("%s(): %s stopped, all rates=0.0MHz\n", __func__,
			dpll_dra7xx_name_get((settings->dpll).id));
		break;

	default:
		fprintf(stderr, "%s(): incorrect %s status! (%u)\n", __func__,
			dpll_dra7xx_names[(settings->dpll).id], st);
		return OMAPCONF_ERR_INTERNAL;
	}

	if (((settings->dpll).id == DPLL_DRA7XX_PCIE_REF) && ((settings->dpll).MN.clkoutldo_st == 1))
		(settings->dpll).MN.clkoutldo_rate = (settings->dpll).fdpll /
			(double) (settings->dpll).MN.M2;

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_dra7xx_settings_extract
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
int dpll_dra7xx_settings_extract(dpll_dra7xx_settings *settings,
	unsigned int id, unsigned short ignore)
{
	int ret;
	unsigned short i;
	unsigned int val;
	dpll_type type;
	dpll_settings_regs *dpll_regs;
	reg **hsdiv_regs;

	CHECK_NULL_ARG(settings, OMAPCONF_ERR_ARG);

	switch (id) {
	case DPLL_DRA7XX_MPU:
	case DPLL_DRA7XX_IVA:
	case DPLL_DRA7XX_CORE:
	case DPLL_DRA7XX_PER:
	case DPLL_DRA7XX_ABE:
	case DPLL_DRA7XX_DSP:
	case DPLL_DRA7XX_EVE:
	case DPLL_DRA7XX_GMAC:
	case DPLL_DRA7XX_GPU:
	case DPLL_DRA7XX_DDR:
		type = DPLL_TYPE_A;
		break;
	case DPLL_DRA7XX_USB:
	case DPLL_DRA7XX_PCIE_REF:
		type = DPLL_TYPE_B;
		break;
	default:
		return OMAPCONF_ERR_ARG;
	}

	dprintf("\n\n### %s() EXTRACTING %s SETTINGS (IGNORE=%u) ###\n",
		__func__, dpll_dra7xx_name_get(id), ignore);

	dpll_regs = (dpll_settings_regs *) &(dpll_dra7xx_regs[id]);
	hsdiv_regs = (reg **) dpll_dra7xx_hsdiv_regs[id];

	ret = dpll_settings_extract(id, type, dpll_regs, &(settings->dpll));
	if (ret != 0)
		return ret;

	/* Set X2_M2_present flag (not register bit available) */
	switch ((dpll_dra7xx_id) id) {
	case DPLL_DRA7XX_PER:
	case DPLL_DRA7XX_ABE:
		settings->dpll.MN.X2_M2_present = 1;
		break;

	case DPLL_DRA7XX_MPU:
	case DPLL_DRA7XX_IVA:
	case DPLL_DRA7XX_CORE:
	case DPLL_DRA7XX_DSP:
	case DPLL_DRA7XX_EVE:
	case DPLL_DRA7XX_GMAC:
	case DPLL_DRA7XX_GPU:
	case DPLL_DRA7XX_DDR:
	case DPLL_DRA7XX_PCIE_REF:
	case DPLL_DRA7XX_USB:
	default:
		settings->dpll.MN.X2_M2_present = 0;
	}

	/* Read CLKOUTLDO status for PCIE_REF */
	settings->dpll.MN.clkoutldo_st = 0;
	if (id == DPLL_DRA7XX_PCIE_REF) {
		val = reg_read(dpll_regs->cm_div_m2_dpll);
		dprintf("%s(): %s reg: %s = 0x%08X\n", __func__,
			dpll_dra7xx_name_get(id),
			(dpll_regs->cm_div_m2_dpll)->name, val);
		val = extract_bit(val, 10);
		if (val == 1)
			settings->dpll.MN.clkoutldo_st = 1;
	}

	val = reg_read(dpll_regs->cm_idlest_dpll);
	dprintf("%s(): %s reg: %s = 0x%08X\n", __func__,
		dpll_dra7xx_name_get(id),
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
		dpll_dra7xx_name_get(id),
		dpll_status_name_get(settings->status));

	for (i = HSDIV_DRA7XX_H11; i < HSDIV_DRA7XX_ID_MAX; i++) {
		ret = hsdiv_dra7xx_settings_extract(i,
			hsdiv_regs[i], &((settings->hsdiv)[i]));
		if (ret != 0)
			return ret;
	}

	ret = dpll_dra7xx_clk_sources_get(&(settings->dpll), ignore);
	if (ret != 0)
		return ret;
	ret = dpll_dra7xx_rates_calc(settings, ignore);
	if (ret != 0)
		return ret;
	ret = hsdiv_dra7xx_rates_calc(settings, ignore);
	if (ret != 0)
		return ret;

	(settings->dpll).initialized = 1;
	dprintf("### %s(): %s SETTINGS EXTRACTED (IGNORE=%u) ###\n",
		__func__, dpll_dra7xx_name_get(id), ignore);

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_dra7xx_settings_get
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
dpll_dra7xx_settings *dpll_dra7xx_settings_get(
	unsigned int id, unsigned short ignore)
{
	int ret;
	dpll_dra7xx_settings *settings;

	CHECK_ARG_LESS_THAN(id, DPLL_DRA7XX_ID_MAX, NULL);

	/* Get struct pointer */
	if (ignore)
		settings = dpll_dra7xx_locked_settings_table[id];
	else
		settings = dpll_dra7xx_settings_table[id];

	/* If DPLL settings not yet extracted, do it */
	if ((settings->dpll).initialized == 0) {
		ret = dpll_dra7xx_settings_extract(settings, id, ignore);
		if (ret < 0) {
			fprintf(stderr, "%s(): error while extracting %s "
				"parameters! (%d)", __func__,
				dpll_dra7xx_name_get((dpll_dra7xx_id) id), ret);
			settings = NULL;
		}
	}

	return settings;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_dra7xx_status_get
 * @BRIEF		return DPLL status.
 * @RETURNS		valid DPLL status (< DPLL_STATUS_MAX) in case of success
 *			DPLL_STATUS_MAX in case of error
 * @param[in]		id: valid DPLL ID
 * @DESCRIPTION		return DPLL status.
 *			If DPLL settings not yet extracted, do it.
 *//*------------------------------------------------------------------------ */
dpll_status dpll_dra7xx_status_get(dpll_dra7xx_id id)
{
	dpll_dra7xx_settings *settings;
	int ret;

	CHECK_ARG_LESS_THAN(id, DPLL_DRA7XX_ID_MAX, DPLL_STATUS_MAX);

	/* Get struct pointer */
	settings = dpll_dra7xx_settings_table[id];

	/* If DPLL settings not yet extracted, do it */
	if ((settings->dpll).initialized == 0) {
		ret = dpll_dra7xx_settings_extract(settings, id, 0);
		if (ret < 0) {
			fprintf(stderr, "%s(): error while extracting %s "
				"parameters! (%d)", __func__,
				dpll_dra7xx_name_get(id), ret);
			return DPLL_STATUS_MAX;
		}
	}

	return settings->status;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_dra7xx_output_rate_get
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
double dpll_dra7xx_output_rate_get(
	dpll_dra7xx_id id, dpll_dra7xx_output_id out_id, unsigned short ignore)
{
	int ret;
	dpll_dra7xx_settings *settings;
	double rate;

	CHECK_ARG_LESS_THAN(id, DPLL_DRA7XX_ID_MAX, 0.0);
	CHECK_ARG_LESS_THAN(out_id, DPLL_DRA7XX_OUTPUT_ID_MAX, 0.0);

	/* Get struct pointer */
	if (ignore)
		settings = dpll_dra7xx_locked_settings_table[id];
	else
		settings = dpll_dra7xx_settings_table[id];

	/* If DPLL settings not yet extracted, do it */
	if ((settings->dpll).initialized == 0) {
		ret = dpll_dra7xx_settings_extract(settings, id, ignore);
		if (ret < 0) {
			fprintf(stderr, "%s(): error while extracting %s "
				"parameters! (%d)", __func__,
				dpll_dra7xx_name_get(id), ret);
			rate = 0.0;
			goto dpll_dra7xx_output_rate_get_end;
		}
	}

	/* Get output rate */
	switch (out_id) {
	case DPLL_DRA7XX_CLKOUT_M2:
		rate = (settings->dpll).MN.M2_rate;
		break;
	case DPLL_DRA7XX_CLKOUTX2_M2:
		rate = (settings->dpll).MN.X2_M2_rate;
		break;
	case DPLL_DRA7XX_CLKOUTX2_M3:
		rate = (settings->dpll).MN.X2_M3_rate;
		break;
	case DPLL_DRA7XX_CLKOUTX2_H11:
		rate = (settings->hsdiv)[HSDIV_DRA7XX_H11].rate;
		break;
	case DPLL_DRA7XX_CLKOUTX2_H12:
		rate = (settings->hsdiv)[HSDIV_DRA7XX_H12].rate;
		break;
	case DPLL_DRA7XX_CLKOUTX2_H13:
		rate = (settings->hsdiv)[HSDIV_DRA7XX_H13].rate;
		break;
	case DPLL_DRA7XX_CLKOUTX2_H14:
		rate = (settings->hsdiv)[HSDIV_DRA7XX_H14].rate;
		break;
	case DPLL_DRA7XX_CLKOUTX2_H21:
		rate = (settings->hsdiv)[HSDIV_DRA7XX_H21].rate;
		break;
	case DPLL_DRA7XX_CLKOUTX2_H22:
		rate = (settings->hsdiv)[HSDIV_DRA7XX_H22].rate;
		break;
	case DPLL_DRA7XX_CLKOUTX2_H23:
		rate = (settings->hsdiv)[HSDIV_DRA7XX_H23].rate;
		break;
	case DPLL_DRA7XX_CLKOUTX2_H24:
		rate = (settings->hsdiv)[HSDIV_DRA7XX_H24].rate;
		break;
	case DPLL_DRA7XX_CLK_DCO_LDO:
		rate = (settings->dpll).MN.clkdcoldo_rate;
		break;
	case DPLL_DRA7XX_CLKOUTX2_M2_LDO:
		rate = (settings->dpll).MN.clkoutldo_rate;
		break;
	default:
		/* should never happen, to remove compilation warning */
		rate = 0.0;
	}

dpll_dra7xx_output_rate_get_end:
	dprintf("%s(%s, %s, %u)=%lfMHz\n", __func__,
		dpll_dra7xx_name_get(id),
		dpll_dra7xx_output_name_get(out_id),
		ignore, rate);
	return rate;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_dra7xx_audit
 * @BRIEF		DRA7 DPLLS settings audit.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		dpll_id: ID of the DPLL to be audited
 * @param[in]		opp_id: if != OPP_DRA7XX_ID_MAX,
 *			force audit at that given OPP
 * @param[in,out]	stream: output file - NULL: no output (silent)
 * @param[in,out]	err_nbr: pointer to return audit error number
 * @param[in,out]	wng_nbr: pointer to return audit warning number
 * @DESCRIPTION		DRA7 DPLLS settings audit.
 *//*------------------------------------------------------------------------ */
int dpll_dra7xx_audit(dpll_dra7xx_id dpll_id, opp_dra7xx_id opp_id,
	FILE *stream, unsigned int *err_nbr, unsigned int *wng_nbr)
{
	int ret = 0;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row;
	dpll_dra7xx_id id;
	hsdiv_dra7xx_id hsdiv_id;
	dpll_dra7xx_settings *settings;
	dpll_dra7xx_audited_settings *golden_settings;
	const char *opp_s;
	int opp_mpu, opp_iva, opp_core, opp_dspeve, opp_gpu, opp;
	double sysclk, abeclk;

	CHECK_ARG_LESS_THAN(dpll_id, DPLL_DRA7XX_ID_MAX + 1, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(opp_id, OPP_DRA7XX_ID_MAX + 1, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(err_nbr, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(wng_nbr, OMAPCONF_ERR_ARG);

	*err_nbr = 0;
	*wng_nbr = 0;
	sysclk = clk_dra7xx_rate_get(CLK_DRA7XX_SYS_CLKIN1, 0);
	abeclk = clk_dra7xx_rate_get(CLK_DRA7XX_ABE_DPLL_CLK, 0);

	if (opp_id != OPP_DRA7XX_ID_MAX) {
		if (stream != NULL)
			fprintf(stream, "WARNING: using forced OPP %s!\n\n",
				opp_dra7xx_name_get(opp_id));
		opp_mpu = opp_id;
		opp_iva = opp_id;
		opp_core = opp_id;
		opp_dspeve = opp_id;
		opp_gpu = opp_id;
		(*wng_nbr)++;
	} else {
		opp_s = opp_get(VDD_MPU, 1);
		opp_mpu = (opp_s == NULL) ? OPP_DRA7XX_ID_MAX : opp_s2id(opp_s);
		opp_s = opp_get(VDD_IVA, 1);
		opp_iva = (opp_s == NULL) ? OPP_DRA7XX_ID_MAX : opp_s2id(opp_s);
		opp_s = opp_get(VDD_CORE, 1);
		opp_core = (opp_s == NULL) ? OPP_DRA7XX_ID_MAX : opp_s2id(opp_s);
		opp_s = opp_get(VDD_DSPEVE, 1);
		opp_dspeve = (opp_s == NULL) ? OPP_DRA7XX_ID_MAX : opp_s2id(opp_s);
		opp_s = opp_get(VDD_GPU, 1);
		opp_gpu = (opp_s == NULL) ? OPP_DRA7XX_ID_MAX : opp_s2id(opp_s);

		if ((opp_mpu == OPP_DRA7XX_ID_MAX) ||
			(opp_iva == OPP_DRA7XX_ID_MAX) ||
			(opp_core == OPP_DRA7XX_ID_MAX) ||
			(opp_dspeve == OPP_DRA7XX_ID_MAX) ||
			(opp_gpu == OPP_DRA7XX_ID_MAX)) {
			if (stream != NULL) {
				fprintf(stream,
					"Sorry, OPP could not be detected, audit cannot be completed.\n");
				fprintf(stream,
					"Option \"-opp [nom|od|high]\" may be considered until OPP correctly setup.\n\n");
			}
			(*err_nbr)++;
			ret = 0;
			goto dpll_dra7xx_audit_end;
		}
	}

	for (id = DPLL_DRA7XX_MPU; id < DPLL_DRA7XX_ID_MAX; id++) {
		if ((dpll_id != DPLL_DRA7XX_ID_MAX) && (dpll_id != id))
			continue;

		switch (id) {
		case DPLL_DRA7XX_MPU:
			opp = opp_mpu;
			break;
		case DPLL_DRA7XX_IVA:
			opp = opp_iva;
			break;
		case DPLL_DRA7XX_DSP:
		case DPLL_DRA7XX_EVE:
			opp = opp_dspeve;
			break;
		case DPLL_DRA7XX_GPU:
			opp = opp_gpu;
			break;
		default:
			opp = opp_core;
		}

		autoadjust_table_init(table);
		row = 0;
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"%s AUDIT (@OPP %s, sysclk=%.1lfMHz)",
			dpll_dra7xx_name_get(id), opp_dra7xx_name_get(opp),
			(id == DPLL_DRA7XX_ABE) ? abeclk : sysclk);
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "Current Setting");
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "Expected");
		snprintf(table[row++][3], TABLE_MAX_ELT_LEN, "STATUS");

		settings = dpll_dra7xx_settings_get(id, 0);
		if (settings == NULL) {
			fprintf(stderr, "%s(): error while getting %s "
				"parameters! (%d)", __func__,
				dpll_dra7xx_name_get(id), ret);
			(*err_nbr)++;
			ret = OMAPCONF_ERR_INTERNAL;
			goto dpll_dra7xx_audit_end;
		}

		if ((dpll_dra7xx_audited_settings **)
			dpll_dra7xx_golden_settings_20MHz_table[id] == NULL) {
			if (stream != NULL)
				fprintf(stream,
					"WARNING: golden settings not "
					"available for %s.\n\n",
					dpll_dra7xx_name_get(id));
			(*err_nbr)++;
			ret = 0;
			goto dpll_dra7xx_audit_end;
		}
		golden_settings =
			dpll_dra7xx_golden_settings_20MHz_table[id][opp];

		if (golden_settings == NULL) {
			if (stream != NULL)
				fprintf(stream,
					"WARNING: golden settings not "
					"available for this device.\n\n");
			(*err_nbr)++;
			ret = 0;
			goto dpll_dra7xx_audit_end;
		}

		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "Status");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
			dpll_status_name_get(settings->status));
		DPLL_DRA7XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->status,
			DPLL_STATUS_MAX, dpll_dra7xx_audit_mode);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
			dpll_status_name_get(golden_settings->status));
		DPLL_DRA7XX_AUDIT_SHOW_STATUS(settings->status,
				golden_settings->status);

		if (golden_settings->status == DPLL_STATUS_STOPPED)
			/* All other DPLL settings are not relevant */
			goto dpll_dra7xx_audit_table_show;

		if (settings->status == DPLL_STATUS_STOPPED) {
			snprintf(table[row - 1][3], TABLE_MAX_ELT_LEN, "WARN.");
			(*err_nbr)--;
			(*wng_nbr)++;
			if (stream != NULL) {
				fprintf(stream, "WARNING: %s is stopped, audit "
					"cannot be completed!\n\n",
					dpll_dra7xx_name_get(id));
				autoadjust_table_fprint(stream, table, row, 4);
			}
			continue;
		}

dpll_dra7xx_audit_mode:
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "Mode");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
			dpll_mode_name_get((settings->dpll).mode));
		DPLL_DRA7XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->mode,
			DPLL_MODE_MAX, dpll_dra7xx_audit_autoidle_mode);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
			dpll_mode_name_get(golden_settings->mode));
		DPLL_DRA7XX_AUDIT_SHOW_STATUS((settings->dpll).mode,
			golden_settings->mode);

dpll_dra7xx_audit_autoidle_mode:
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "Autoidle Mode");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
			dpll_autoidle_mode_name_get(
				(settings->dpll).autoidle_mode));
		DPLL_DRA7XX_AUDIT_CHECK_GOLDEN_SETTING(
				golden_settings->autoidle_mode,
			DPLL_AUTOIDLE_MODE_MAX, dpll_dra7xx_audit_dcc_en);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
			dpll_autoidle_mode_name_get(
				golden_settings->autoidle_mode));
		DPLL_DRA7XX_AUDIT_SHOW_STATUS((settings->dpll).autoidle_mode,
			golden_settings->autoidle_mode);

dpll_dra7xx_audit_dcc_en:
		if ((settings->dpll).type == DPLL_TYPE_B)
			goto dpll_dra7xx_audit_selfreqdco;
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "DCC");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u",
			(settings->dpll).DCC.en);
		DPLL_DRA7XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->dcc_en,
			-1, dpll_dra7xx_audit_selfreqdco);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u",
			golden_settings->dcc_en);
		DPLL_DRA7XX_AUDIT_SHOW_STATUS((int) (settings->dpll).DCC.en,
			golden_settings->dcc_en);

dpll_dra7xx_audit_selfreqdco:
		if ((settings->dpll).type == DPLL_TYPE_A)
			goto dpll_dra7xx_audit_fref;
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"SELFREQDCO");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u (%s)",
			(settings->dpll).selfreqdco,
			((settings->dpll).selfreqdco) ? "100" : "010");
		DPLL_DRA7XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->selfreqdco,
			-1, dpll_dra7xx_audit_sd_div);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u (%s)",
			golden_settings->selfreqdco,
			(golden_settings->selfreqdco) ? "100" : "010");
		DPLL_DRA7XX_AUDIT_SHOW_STATUS((settings->dpll).selfreqdco,
			golden_settings->selfreqdco);

dpll_dra7xx_audit_sd_div:
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"Sigma-Delta Divider");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u",
			(settings->dpll).sd_div);
		DPLL_DRA7XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->sd_div,
			-1, dpll_dra7xx_audit_fref);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u",
			golden_settings->sd_div);
		DPLL_DRA7XX_AUDIT_SHOW_STATUS((int) (settings->dpll).sd_div,
			golden_settings->sd_div);

dpll_dra7xx_audit_fref:
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
		DPLL_DRA7XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->fref,
			-1, dpll_dra7xx_audit_regm4xen);
		DPLL_DRA7XX_AUDIT_SHOW_STATUS((settings->dpll).fref,
			golden_settings->fref);

dpll_dra7xx_audit_regm4xen:
		if ((settings->dpll).type == DPLL_TYPE_B)
			goto dpll_dra7xx_audit_M;
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"REGM4XEN");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u",
			(settings->dpll).regm4xen);
		DPLL_DRA7XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->regm4xen,
			-1, dpll_dra7xx_audit_M);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u",
			golden_settings->regm4xen);
		DPLL_DRA7XX_AUDIT_SHOW_STATUS((settings->dpll).regm4xen,
			golden_settings->regm4xen);

dpll_dra7xx_audit_M:
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"M Divider");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u",
			(settings->dpll).MN.M);
		DPLL_DRA7XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->M,
			-1, dpll_dra7xx_audit_N);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u",
			golden_settings->M);
		DPLL_DRA7XX_AUDIT_SHOW_STATUS((int) (settings->dpll).MN.M,
			golden_settings->M);


dpll_dra7xx_audit_N:
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"N Divider");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u",
			(settings->dpll).MN.N);
		DPLL_DRA7XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->N,
			-1, dpll_dra7xx_audit_fdpll);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u",
			golden_settings->N);
		DPLL_DRA7XX_AUDIT_SHOW_STATUS((int) (settings->dpll).MN.N,
			golden_settings->N);

dpll_dra7xx_audit_fdpll:
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"Lock Frequency (MHz)");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%.3lf",
			(settings->dpll).fdpll);
		DPLL_DRA7XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->fdpll,
			-1, dpll_dra7xx_audit_M2);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%.3lf",
			golden_settings->fdpll);
		DPLL_DRA7XX_AUDIT_SHOW_STATUS(
			(unsigned int) (settings->dpll).fdpll,
			(unsigned int) golden_settings->fdpll);

dpll_dra7xx_audit_M2:
		if (settings->dpll.MN.M2_present == 0)
			goto dpll_dra7xx_audit_M3;
		snprintf(table[row++][0], TABLE_MAX_ELT_LEN, "%s Output",
			dpll_dra7xx_output_name_get(DPLL_DRA7XX_CLKOUT_M2));
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
		DPLL_DRA7XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->M2,
			-1, dpll_dra7xx_audit_M2_rate);
		DPLL_DRA7XX_AUDIT_SHOW_STATUS((int) (settings->dpll).MN.M2,
			golden_settings->M2);

dpll_dra7xx_audit_M2_rate:
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"  Clock Speed (MHz)");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%.3lf",
			(settings->dpll).MN.M2_rate);
		DPLL_DRA7XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->M2_rate,
			-1, dpll_dra7xx_audit_X2_M2);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%.3lf",
			golden_settings->M2_rate);
		DPLL_DRA7XX_AUDIT_SHOW_STATUS(
			(unsigned int) (settings->dpll).MN.M2_rate,
			(unsigned int) golden_settings->M2_rate);

dpll_dra7xx_audit_X2_M2:
		if ((settings->dpll).type == DPLL_TYPE_B)
			goto dpll_dra7xx_audit_clkdcoldo_rate;
		if (settings->dpll.MN.X2_M2_present == 0)
			goto dpll_dra7xx_audit_M3;
		snprintf(table[row++][0], TABLE_MAX_ELT_LEN, "%s Output",
			dpll_dra7xx_output_name_get(DPLL_DRA7XX_CLKOUTX2_M2));
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"  Clock Divider");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u",
			(settings->dpll).MN.M2);
		DPLL_DRA7XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->M2,
			-1, dpll_dra7xx_audit_X2_M2_rate);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u",
			golden_settings->M2);
		DPLL_DRA7XX_AUDIT_SHOW_STATUS((int) (settings->dpll).MN.M2,
			golden_settings->M2);

dpll_dra7xx_audit_X2_M2_rate:
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"  Clock Speed (MHz)");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%.3lf",
			(settings->dpll).MN.X2_M2_rate);
		DPLL_DRA7XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->X2_M2_rate,
			-1, dpll_dra7xx_audit_M3);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%.3lf",
			golden_settings->X2_M2_rate);
		DPLL_DRA7XX_AUDIT_SHOW_STATUS(
			(unsigned int) (settings->dpll).MN.X2_M2_rate,
			(unsigned int) golden_settings->X2_M2_rate);

dpll_dra7xx_audit_M3:
		/*
		 * We do have M3 registers presented for most of the DPLLs,
		 * but not all of them are used at this moment. Hence ignore
		 * them when we do audit dpll.
		 */
		if (dpll_dra7xx_ignore_m3[id] || (settings->dpll.MN.M3_present == 0))
			goto dpll_dra7xx_audit_hsdiv;
		snprintf(table[row++][0], TABLE_MAX_ELT_LEN, "%s Output",
			dpll_dra7xx_output_name_get(DPLL_DRA7XX_CLKOUTX2_M3));
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"  Clock Divider");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u",
			(settings->dpll).MN.M3);
		DPLL_DRA7XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->M3,
			-1, dpll_dra7xx_audit_X2_M3_rate);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u",
			golden_settings->M3);
		DPLL_DRA7XX_AUDIT_SHOW_STATUS((int) (settings->dpll).MN.M3,
			golden_settings->M3);

dpll_dra7xx_audit_X2_M3_rate:
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"  Clock Speed (MHz)");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%.3lf",
			(settings->dpll).MN.X2_M3_rate);
		DPLL_DRA7XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->X2_M3_rate,
			-1, dpll_dra7xx_audit_hsdiv);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%.3lf",
			golden_settings->X2_M3_rate);
		DPLL_DRA7XX_AUDIT_SHOW_STATUS(
			(unsigned int) (settings->dpll).MN.X2_M3_rate,
			(unsigned int) golden_settings->X2_M3_rate);

dpll_dra7xx_audit_hsdiv:
		for (hsdiv_id = HSDIV_DRA7XX_H11; hsdiv_id < HSDIV_DRA7XX_ID_MAX;
			hsdiv_id++) {
			if ((settings->hsdiv)[hsdiv_id].present != 1)
				continue;
			snprintf(table[row++][0], TABLE_MAX_ELT_LEN,
				"%s Output",
				hsdiv_dra7xx_name_get(hsdiv_id));
			snprintf(table[row][0], TABLE_MAX_ELT_LEN,
				"  Clock Divider");
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u",
				(settings->hsdiv)[hsdiv_id].div);
			DPLL_DRA7XX_AUDIT_CHECK_GOLDEN_SETTING(
				(golden_settings->hsdiv_div)[hsdiv_id],
				-1, dpll_dra7xx_audit_hsdiv_rate);
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u",
				(golden_settings->hsdiv_div)[hsdiv_id]);
			DPLL_DRA7XX_AUDIT_SHOW_STATUS(
				(int) (settings->hsdiv)[hsdiv_id].div,
				(golden_settings->hsdiv_div)[hsdiv_id]);

dpll_dra7xx_audit_hsdiv_rate:
			snprintf(table[row][0], TABLE_MAX_ELT_LEN,
				"  Clock Speed (MHz)");
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%.3lf",
				(settings->hsdiv)[hsdiv_id].rate);
			if ((golden_settings->hsdiv_rate)[hsdiv_id] == -1) {
				/* Golden setting not available */
				snprintf(table[row][2], TABLE_MAX_ELT_LEN,
					"Not available");
				snprintf(table[row][3], TABLE_MAX_ELT_LEN,
					"WARN.");
				(*wng_nbr)++;
				row++;
				continue;
			}
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%.3lf",
				(golden_settings->hsdiv_rate)[hsdiv_id]);
			DPLL_DRA7XX_AUDIT_SHOW_STATUS(
				(unsigned int) (settings->hsdiv)[hsdiv_id].rate,
				(unsigned int)
				(golden_settings->hsdiv_rate)[hsdiv_id]);
		}
		goto dpll_dra7xx_audit_table_show;

dpll_dra7xx_audit_clkdcoldo_rate:
		if (id == DPLL_DRA7XX_PCIE_REF)
			goto dpll_dra7xx_audit_clkoutldo_rate;
		snprintf(table[row++][0], TABLE_MAX_ELT_LEN,
			"CLKDCOLDO Output");
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"  Clock Speed (MHz)");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%.3lf",
			(settings->dpll).MN.clkdcoldo_rate);
		DPLL_DRA7XX_AUDIT_CHECK_GOLDEN_SETTING(
			golden_settings->clkdcoldo_rate,
			-1, dpll_dra7xx_audit_table_show);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%.3lf",
			golden_settings->clkdcoldo_rate);
		DPLL_DRA7XX_AUDIT_SHOW_STATUS(
			(unsigned int) (settings->dpll).MN.clkdcoldo_rate,
			(unsigned int) golden_settings->clkdcoldo_rate);

dpll_dra7xx_audit_clkoutldo_rate:
		snprintf(table[row++][0], TABLE_MAX_ELT_LEN,
			"CLKOUTLDO Output");
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"  Clock Speed (MHz)");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%.3lf",
			(settings->dpll).MN.clkoutldo_rate);
		DPLL_DRA7XX_AUDIT_CHECK_GOLDEN_SETTING(
			golden_settings->clkoutldo_rate,
			-1, dpll_dra7xx_audit_table_show);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%.3lf",
			golden_settings->clkoutldo_rate);
		DPLL_DRA7XX_AUDIT_SHOW_STATUS(
			(unsigned int) (settings->dpll).MN.clkoutldo_rate,
			(unsigned int) golden_settings->clkoutldo_rate);

dpll_dra7xx_audit_table_show:
		if (stream != NULL)
			autoadjust_table_fprint(stream, table, row, 4);
	}
	ret = 0;

dpll_dra7xx_audit_end:
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_dra7xx_init
 * @BRIEF		allocate memory for dpll settings structs and save
 *			dpll settings in it.
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_UNEXPECTED
 * @DESCRIPTION		allocate memory for dpll settings structs and save
 *			dpll settings in it.
 *//*------------------------------------------------------------------------ */
int dpll_dra7xx_init(void)
{
	dpll_dra7xx_id id;
	unsigned int i;
	int ret;
	static const dpll_dra7xx_id ordered_ids[DPLL_DRA7XX_ID_MAX] = {
		DPLL_DRA7XX_ABE,
		DPLL_DRA7XX_CORE,
		DPLL_DRA7XX_PER,
		DPLL_DRA7XX_MPU,
		DPLL_DRA7XX_IVA,
		DPLL_DRA7XX_EVE,
		DPLL_DRA7XX_DSP,
		DPLL_DRA7XX_GMAC,
		DPLL_DRA7XX_GPU,
		DPLL_DRA7XX_DDR,
		DPLL_DRA7XX_USB,
		DPLL_DRA7XX_PCIE_REF};


	dprintf("\n%s(): retrieving all DPLL settings\n", __func__);
	/*
	 * Allocate memory for dpll settings structs
	 * And save dpll settings into it.
	 */
	for (id = DPLL_DRA7XX_MPU; id < DPLL_DRA7XX_ID_MAX; id++) {
		dpll_dra7xx_settings_table[id] =
			malloc(sizeof(dpll_dra7xx_settings));
		if (dpll_dra7xx_settings_table[id] == NULL)
			return OMAPCONF_ERR_UNEXPECTED;
		(dpll_dra7xx_settings_table[id]->dpll).initialized = 0;
		dpll_dra7xx_locked_settings_table[id] =
			malloc(sizeof(dpll_dra7xx_settings));
		if (dpll_dra7xx_locked_settings_table[id] == NULL)
			return OMAPCONF_ERR_UNEXPECTED;
		(dpll_dra7xx_locked_settings_table[id]->dpll).initialized = 0;
	}

	for (i = 0; i < DPLL_DRA7XX_ID_MAX; i++) {
		id = ordered_ids[i];
		ret = dpll_dra7xx_settings_extract(
			dpll_dra7xx_settings_table[id], id, 0);
		if (ret < 0) {
			fprintf(stderr, "%s(): error while extracting %s "
				"parameters! (%d)", __func__,
				dpll_dra7xx_name_get(id), ret);
			return ret;
		}

		/*
		 * Also get DPLL params ignoring DPLL STOPPED status to also
		 * show all output speeds when DPLL is locked.
		 */
		dpll_dra7xx_settings_extract(
			dpll_dra7xx_locked_settings_table[id], id, 1);
		if (ret < 0) {
			fprintf(stderr, "%s(): error while extracting %s "
				"parameters! (%d)", __func__,
				dpll_dra7xx_name_get(id), ret);
			return ret;
		}


	}

	dprintf("%s(): all DPLL settings retrieved\n\n", __func__);
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_dra7xx_free
 * @BRIEF		free memory for dpll settings structs and save
 *			dpll settings in it.
 * @RETURNS		0 on success
 * @param[in]		none
 * @DESCRIPTION		allocate memory for dpll settings structs and save
 *			dpll settings in it.
 *//*------------------------------------------------------------------------ */
int dpll_dra7xx_free(void)
{
	dpll_dra7xx_id id;

	for (id = DPLL_DRA7XX_MPU; id < DPLL_DRA7XX_ID_MAX; id++) {
		if (dpll_dra7xx_settings_table[id] != NULL)
			free(dpll_dra7xx_settings_table[id]);
		if (dpll_dra7xx_locked_settings_table[id] != NULL)
			free(dpll_dra7xx_locked_settings_table[id]);
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_dra7xx_main
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
int dpll_dra7xx_main(int argc, char *argv[])
{
	int ret = 0;
	dpll_dra7xx_id id;

	if (argc == 1) {
		id = DPLL_DRA7XX_ID_MAX;
	} else if (argc != 2) {
		goto dpll_dra7xx_main_err_arg;
	} else if (strcmp(argv[1], "all") == 0) {
		id = DPLL_DRA7XX_ID_MAX;
	} else {
		id = dpll_dra7xx_s2id(argv[1]);
		if (id == DPLL_DRA7XX_ID_MAX)
			goto dpll_dra7xx_main_err_arg;
	}

	if (strcmp(argv[0], "dump") == 0)
		ret = dpll_dra7xx_dump(stdout, id);
	else
		goto dpll_dra7xx_main_err_arg;
	goto dpll_dra7xx_main_end;

dpll_dra7xx_main_err_arg:
	help(HELP_DPLL);
	ret = OMAPCONF_ERR_ARG;

dpll_dra7xx_main_end:
	return ret;
}
