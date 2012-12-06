/*
 *
 * @Component			OMAPCONF
 * @Filename			audit54xx.c
 * @Description			OMAP5 Power Audit Functions
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


#include <audit54xx.h>
#include <module54xx.h>
#include <module.h>
#include <lib.h>
#include <autoadjust_table.h>
#include <cpufreq.h>
#include <cpuinfo.h>
#include <help.h>
#include <clkdm_dependency54xx.h>
#include <ctrlmod54xx.h>
#include <dpll54xx.h>
#include <opp.h>


/* #define AUDIT54XX_DEBUG */
#ifdef AUDIT54XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static const char pass[5] = "Pass";
static const char fail[5] = "FAIL";
static const char ignore[12] = "Ignored (1)";
static const char warning[8] = "Warning";


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		audit54xx_sysconfig
 * @BRIEF		OMAP5 SYSCONFIG registers audit.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in,out]	stream: output file - NULL: no output (silent)
 * @param[in,out]	err_nbr: pointer to return audit error number
 * @param[in,out]	wng_nbr: pointer to return audit warning number
 * @DESCRIPTION		OMAP5 SYSCONFIG registers audit.
 *//*------------------------------------------------------------------------ */
int audit54xx_sysconfig(FILE *stream, unsigned int *err_nbr,
	unsigned int *wng_nbr)
{
	mod54xx_id id;
	mod_autoidle_mode autoidle_mode;
	mod_idle_mode idle_mode;
	mod_standby_mode standby_mode;
	mod_clock_activity_mode clock_activity_mode;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row;
	char element[TABLE_MAX_ELT_LEN];

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(err_nbr, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(wng_nbr, OMAPCONF_ERR_ARG);

	*err_nbr = 0;
	*wng_nbr = 0;

	autoadjust_table_init(table);

	row = 0;
	strncpy(table[row][0], "MODULES SYSCONFIG AUDIT", TABLE_MAX_ELT_LEN);
	strncpy(table[row][1], "AUTOIDLE Mode", TABLE_MAX_ELT_LEN);
	strncpy(table[row][2], "IDLE Mode", TABLE_MAX_ELT_LEN);
	strncpy(table[row][3], "STANDBY Mode", TABLE_MAX_ELT_LEN);
	strncpy(table[row][4], "CLOCK ACTIVITY Mode", TABLE_MAX_ELT_LEN);
	row++;

	for (id = OMAP5_DEBUGSS; id < MOD54XX_ID_MAX; id++) {
		dprintf("\n%s(): Module #%d name = %s\n", __func__,
			id, mod54xx_name_get(id));
		autoadjust_table_strncpy(table, row, 0,
			(char *) mod54xx_name_get(id));
		if (!mod54xx_has_sysconfig_register(id)) {
			dprintf("\t%s(): no sysconfig\n", __func__);
			continue;
		}

		if (mod54xx_is_accessible(id) != 1) {
			dprintf("\t%s(): module is not accessible\n", __func__);
			autoadjust_table_strncpy(table, row, 1,
				(char *) ignore);
			autoadjust_table_strncpy(table, row, 2,
				(char *) ignore);
			autoadjust_table_strncpy(table, row, 3,
				(char *) ignore);
			autoadjust_table_strncpy(table, row, 4,
				(char *) ignore);
			row++;
			continue;
		}

		/* Audit module's autoidle bit (if any) */
		autoidle_mode = mod54xx_autoidle_mode_get(id);
		if (autoidle_mode == MOD_AUTOIDLE_MODE_MAX) {
			dprintf("\t%s(): module does not have autoidle bit\n",
				__func__);
			goto audit54xx_sysconfig_idle_mode;
		}
		dprintf("\t%s(): autoidle=%u (%s)\n", __func__, autoidle_mode,
			mod_autoidle_mode_name_get(autoidle_mode));
		if (autoidle_mode == MOD_AUTOGATING) {
			autoadjust_table_strncpy(table, row, 1, (char *) pass);
		} else {
			snprintf(element, TABLE_MAX_ELT_LEN, "%s (%s)",
				fail, mod_autoidle_mode_name_get(
					autoidle_mode));
			autoadjust_table_strncpy(table, row, 1, element);
			(*err_nbr)++;
		}

audit54xx_sysconfig_idle_mode:
		/* Audit module's IDLE mode */
		idle_mode = mod54xx_idle_mode_get(id);
		if (idle_mode == MOD_IDLE_MODE_MAX) {
			dprintf("\t%s(): module does not have idle mode\n",
				__func__);
			goto audit54xx_sysconfig_standby_mode;
		}
		dprintf("\t%s(): idle mode=%u (%s)\n", __func__, idle_mode,
			mod_idle_mode_name_get(idle_mode));
		switch (idle_mode) {
		case MOD_SMART_IDLE_WAKEUP:
			autoadjust_table_strncpy(table, row, 2, (char *) pass);
			break;
		case MOD_SMART_IDLE:
			if (!mod54xx_has_smart_idle_wakeup_mode(id)) {
				autoadjust_table_strncpy(table, row, 2,
					(char *) pass);
			} else {
				snprintf(element, TABLE_MAX_ELT_LEN,
					"%s (%s) (3)", fail,
					mod_idle_mode_name_get(idle_mode));
				autoadjust_table_strncpy(table, row, 2,
					element);
				(*err_nbr)++;
			}
			break;
		case MOD_FORCE_IDLE:
			snprintf(element, TABLE_MAX_ELT_LEN, "%s (%s)",
				warning, mod_idle_mode_name_get(idle_mode));
			autoadjust_table_strncpy(table, row, 2,	element);
			(*wng_nbr)++;
			break;
		default:
			if ((id == OMAP5_UART1) ||
				(id == OMAP5_UART2) ||
				(id == OMAP5_UART3) ||
				(id == OMAP5_UART4) ||
				(id == OMAP5_UART5) ||
				(id == OMAP5_UART6)) {
				/*
				 * UART IP idle management is buggy
				 * (cf errata). When active,
				 * must be used in no-idle mode.
				 */
				autoadjust_table_strncpy(table, row, 2,
					(char *) pass);
			} else {
				snprintf(element, TABLE_MAX_ELT_LEN,
					"%s (%s)", fail, mod_idle_mode_name_get(
						idle_mode));
				autoadjust_table_strncpy(table, row, 2,
					element);
				(*err_nbr)++;
			}
		}

audit54xx_sysconfig_standby_mode:
		/* Audit module's STANDBY mode */
		standby_mode = mod54xx_standby_mode_get(id);
		if (standby_mode == MOD_STANDBY_MODE_MAX) {
			goto audit54xx_sysconfig_clock_activity_mode;
			dprintf("\t%s(): module does not have standby mode\n",
				__func__);
		}
		dprintf("\t%s(): standby mode=%u (%s)\n", __func__,
			standby_mode, mod_standby_mode_name_get(standby_mode));
		switch (standby_mode) {
		case MOD_STANDBY_MODE_RESERVED:
			autoadjust_table_strncpy(table, row, 3, (char *) pass);
			break;
		case MOD_SMART_STANDBY:
			if (!mod54xx_has_smart_standby_wakeup_mode(id)) {
				autoadjust_table_strncpy(table, row, 2,
					(char *) pass);
			} else {
				snprintf(element, TABLE_MAX_ELT_LEN,
					"%s (%s) (4)", fail,
					mod_standby_mode_name_get(idle_mode));
				autoadjust_table_strncpy(table, row, 2,
					element);
				(*err_nbr)++;
			}
			break;
		case MOD_FORCE_STANDBY:
			snprintf(element, TABLE_MAX_ELT_LEN, "%s (%s)",
				warning, mod_standby_mode_name_get(
					standby_mode));
			autoadjust_table_strncpy(table, row, 3, element);
			(*wng_nbr)++;
			break;
		default:
			snprintf(element, TABLE_MAX_ELT_LEN, "%s (%s)",
				fail, mod_standby_mode_name_get(standby_mode));
			autoadjust_table_strncpy(table, row, 3,	element);
			(*err_nbr)++;
		}

audit54xx_sysconfig_clock_activity_mode:
		/* Audit module's CLOCK ACTIVITY mode */
		clock_activity_mode = mod54xx_clock_activity_mode_get(id);
		if (clock_activity_mode == MOD_CLOCK_ACTIVITY_MODE_MAX) {
			dprintf("\t%s(): module does not have "
				"clock activity mode\n", __func__);
			goto audit54xx_sysconfig_next_row;
		}
		dprintf("\t%s(): clock activity mode=%u (%s)\n",
			__func__, clock_activity_mode,
			mod_clock_activity_mode_name_get(clock_activity_mode));
		switch (clock_activity_mode) {
		case MOD_FCLK_AUTO_ICLK_AUTO:
			/*
			 * Functional clock can be switched-off.
			 * L4 clock can be switched-off.
			 */
			autoadjust_table_strncpy(table, row, 4,	(char *) pass);
			break;
		case MOD_FCLK_AUTO_ICLK_ON:
			/*
			 * Functional clock can be switched-off.
			 * L4 clock is maintained during wake-up period.
			 */
		case MOD_FCLK_ON_ICLK_AUTO:
			/*
			 * Functional clock is maintained during wake-up
			 * period.
			 * L4 clock can be switched-off.
			 */
			snprintf(element, TABLE_MAX_ELT_LEN, "%s (%s)",
				warning, mod_clock_activity_mode_name_get(
					clock_activity_mode));
			autoadjust_table_strncpy(table, row, 4,	element);
			(*wng_nbr)++;
			break;
		case MOD_FCLK_ON_ICLK_ON:
			/*
			 * Functional clock is maintained during wake-up
			 * period.
			 * L4 clock is maintained during wake-up period.
			 */
		default:
			snprintf(element, TABLE_MAX_ELT_LEN, "%s (%s)",
				fail, mod_clock_activity_mode_name_get(
					clock_activity_mode));
			autoadjust_table_strncpy(table, row, 4,	element);
			(*err_nbr)++;
		}
audit54xx_sysconfig_next_row:
		row++;
	}

	if (stream != NULL) {
		autoadjust_table_fprint(stream, table, row, 5);
		fprintf(stream, "NB:\n");
		fprintf(stream, "  (1) - Show 'Ignored' when module is disabled"
			" (registers not accessible).\n");
		fprintf(stream, "  (2) - Show empty cell(s) when module does "
			"not feature this mode.\n");
		fprintf(stream, "  - AUTOIDLE MODE:\n");
		fprintf(stream, "    - Report Pass if enabled, FAIL otherwise."
			"\n");
		fprintf(stream, "  - IDLE MODE:\n");
		fprintf(stream, "    - Report Pass if set to \"Smart-Idle\" or "
			"\"Smart-Idle Wakeup\" (when available).\n");
		fprintf(stream, "      - (3) Modules featuring \"Smart-Idle "
			"Wakeup\" mode must be programmed in this mode. Audit "
			"will report FAIL even with \"Smart-Idle\" mode.\n");
		fprintf(stream, "    - Report Warning (with setting) in case of"
			" \"Force-Idle\" mode.\n");
		fprintf(stream, "    - Report FAIL (with incorrect setting) "
			"otherwise.\n");
		fprintf(stream, "  - STANDBY MODE:\n");
		fprintf(stream, "    - Report Pass if set to \"Smart-Standby\" "
			"or \"Smart-Standby Wakeup\" (when available).\n");
		fprintf(stream, "      - (4) Modules featuring \"Smart-Standby "
			"Wakeup\" mode must be programmed in this mode. Audit "
			"will report FAIL even with \"Smart-Standby\" mode.\n");
		fprintf(stream, "    - Report Warning (with setting) in case of"
			" \"Force-Standby\" mode.\n");
		fprintf(stream, "    - Report FAIL (with incorrect setting) "
			"otherwise.\n");
		fprintf(stream, "  - CLOCKACTIVITY MODE:\n");
		fprintf(stream, "    - Report Pass if both I-CLK and F-CLK are "
			"set to AUTO mode.\n");
		fprintf(stream, "    - Report Warning if one of I-CLK or F-CLK "
			"is set to ON mode.\n");
		fprintf(stream, "    - Report FAIL (with incorrect setting) "
			"otherwise.\n\n");

		if (*err_nbr == 0) {
			fprintf(stream, "SUCCESS! Modules SYSCONFIG registers "
				"audit completed with 0 error "
				"(%d warning(s))\n\n",
				*wng_nbr);
		} else {
			fprintf(stream, "FAILED! Modules SYSCONFIG registers "
				"audit completed with %d error and "
				"%d warning.\n\n",
				*err_nbr, *wng_nbr);
		}
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		audit54xx_dpll
 * @BRIEF		audit DPLL Configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		stream: output file (NULL: no output (silent))
 * @param[in]		dpll_id: DPLL ID
 *				(use DPLL54XX_ID_MAX to audit all DPLLs)
 * @param[in]		opp_id: OPP ID
 *				(use OPP54XX_ID_MAX to audit all OPPs)
 * @param[in]		curr_opp: audit current OPP only (=1) or all OPPs (=0)
 * @param[in,out]	err_nbr: audit error number
 * @param[in,out]	wng_nbr: audit warning number
 * @DESCRIPTION		audit DPLL Configuration
 *//*------------------------------------------------------------------------ */
int audit54xx_dpll(FILE *stream, dpll54xx_id dpll_id, opp54xx_id opp_id,
	unsigned short curr_opp, unsigned int *err_nbr, unsigned int *wng_nbr)
{
	int ret = 0;
	char s[256];
	char logfilename[256];
	FILE *fp;
	unsigned int row;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	char prev_gov[CPUFREQ_GOV_MAX_NAME_LENGTH] = "";
	char prev_gov2[CPUFREQ_GOV_MAX_NAME_LENGTH] = "";
	opp54xx_id opp;
	double freq_mpu;
	unsigned int _err_nbr = 0, _wng_nbr = 0;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(dpll_id, DPLL54XX_ID_MAX + 1, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(opp_id, OPP54XX_ID_MAX + 1, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(curr_opp, 2, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(err_nbr, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(wng_nbr, OMAPCONF_ERR_ARG);

	*err_nbr = 0;
	*wng_nbr = 0;

	/* Create audit report log file */
	strcpy(logfilename, "dpll_audit_report.txt");
	fp = workdir_fopen(logfilename, "w+");
	if (fp == NULL) {
		fprintf(stderr, "Could not create %s file!\n\n", logfilename);
		return 0;
	}

	fprintf(fp,
		"OMAPCONF DPLL Configuration Audit Detailed Log:\n\n");
	omapconf_revision_show(fp);
	chips_info_show(fp, 1);
	release_info_show(fp);

	if (curr_opp == 1) {
		ret = dpll54xx_audit(dpll_id, opp_id, fp, err_nbr, wng_nbr);
		if (ret != 0)
			goto audit54xx_dpll_end;
		ret = dpll54xx_audit(dpll_id, opp_id, stream, err_nbr, wng_nbr);
		if (ret != 0)
			goto audit54xx_dpll_end;

		if (*err_nbr == 0)
			sprintf(s, "SUCCESS! DPLL Configuration audit "
				"completed with 0 error (%u warning(s))"
				".\n\n", *wng_nbr);
		else
			sprintf(s, "FAILED! DPLL Configuration audit "
				"completed with %u error(s) and %u "
				"warning(s).\n\n", *err_nbr, *wng_nbr);

		if (stream != NULL) {
			fprintf(stream, "Audit details saved in %s file.\n\n\n",
				logfilename);
			fputs(s, stream);
		}
		fputs(s, fp);
		ret = 0;
		goto audit54xx_dpll_end;
	}

	/* Save current governor (will be altered by cpufreq_set() call) */
	if (cpufreq_scaling_governor_get(prev_gov) == NULL) {
		ret = OMAPCONF_ERR_NOT_AVAILABLE;
		goto audit54xx_dpll_end;
	}

	/* Retrieve number of available MPU OPPs */
	if (cpufreq_opp_nbr_get() == 0) {
		ret = OMAPCONF_ERR_NOT_AVAILABLE;
		goto audit54xx_dpll_end;
	}

	row = 0;
	autoadjust_table_init(table);
	snprintf(table[row][0], TABLE_MAX_ELT_LEN,
		"DPLL Configuration AUDIT Summary");
	autoadjust_table_strncpy(table, row, 1, "Audit STATUS");
	row++;

	for (opp = OPP54XX_LOW; (unsigned int) opp <= cpufreq_opp_nbr_get();
		opp++) {
		_err_nbr = 0;
		_wng_nbr = 0;

		/* Set MPU OPP */
		freq_mpu = mod54xx_por_clk_rate_get(OMAP5_MPU, opp);
		if (freq_mpu < 0) {
			err_internal_msg_show();
			goto audit54xx_dpll_end;
		}
		ret = cpufreq_set((unsigned int) (freq_mpu * 1000));
		if (ret != 0) {
			err_internal_msg_show();
			goto audit54xx_dpll_end;
		}

		fprintf(fp, "DPLLs Configuration Audit at MPU %s:\n\n",
			opp54xx_name_get(opp));
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "At MPU %s",
			opp54xx_name_get(opp));

		/* Run audit at this OPP */
		ret = dpll54xx_audit(dpll_id, OPP54XX_ID_MAX, fp,
			&_err_nbr, &_wng_nbr);
		if (ret != 0) {
			err_internal_msg_show();
			goto audit54xx_dpll_end;
		}

		if (_err_nbr == 0)
			snprintf(table[row][1], TABLE_MAX_ELT_LEN,
				"PASS (0 error, %u warning(s))", _wng_nbr);
		else
			snprintf(table[row][1], TABLE_MAX_ELT_LEN,
				"FAIL (%u error, %u warning(s))",
				_err_nbr, _wng_nbr);
		(*err_nbr) += _err_nbr;
		(*wng_nbr) += _wng_nbr;
		row++;
		fprintf(fp, "\n\n\n");
	}

	/* Report final audit status */
	autoadjust_table_fprint(fp, table, row, 2);
	sprintf(s, "NB: DPLL IVA may not have been audited accross all "
		"IVA OPPs (no kernel interface to control IVA OPP "
		"available).\n\n");
	fputs(s, fp);
	if (stream != NULL) {
		autoadjust_table_fprint(stream, table, row, 2);
		fputs(s, stream);
	}
	if (*err_nbr == 0)
		sprintf(s, "\nSUCCESS! DPLLs Configuration "
			"audit completed with 0 error (%u warning(s))"
			".\n\n\n", *wng_nbr);
	else
		sprintf(s, "\nFAILED! DPLLs Configuration "
			"audit completed with %u error(s) and %u "
			"warning(s).\n\n\n", *err_nbr, *wng_nbr);
	fputs(s, fp);
	if (stream != NULL) {
		fprintf(stream, "DPLLs Configuration audit details saved "
			"in %s file.\n", logfilename);
		fputs(s, stream);
	}


audit54xx_dpll_end:
	/* Restore CPUFreq governor */
	if (strlen(prev_gov) != 0)
		cpufreq_scaling_governor_set(prev_gov, prev_gov2);
	/* Close opened file */
	if (fp != NULL)
		fclose(fp);
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		audit54xx_full
 * @BRIEF		full OMAP5 power configuration audit
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_INTERNAL
 * @param[in,out]	stream: output file - NULL: no output (silent)
 * @param[in,out]	logfile: audit report file name
 *			(revert to default "full_audit_report.txt" if NULL)
 * @param[in,out]	err_nbr: pointer to return audit error number
 * @param[in,out]	wng_nbr: pointer to return audit warning number
 * @DESCRIPTION		full OMAP5 power configuration audit
 *			(DPLL + SYSCONFIG + CLKSPEED + STATICDEP + IO).
 *//*------------------------------------------------------------------------ */
int audit54xx_full(FILE *stream, char *logfile, unsigned int *err_nbr,
	unsigned int *wng_nbr)
{
	int ret;

	unsigned int dplls_err_nbr = 0, dplls_wng_nbr = 0;
	unsigned int syscfg_err_nbr = 0, syscfg_wng_nbr = 0;
	unsigned int clkspeed_err_nbr = 0, clkspeed_wng_nbr = 0;
	unsigned int statdep_err_nbr = 0, statdep_wng_nbr = 0;
	unsigned int io_err_nbr = 0, io_wng_nbr = 0;
	unsigned int row = 0;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	char *workdir;
	char s[256];
	FILE *fp;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(err_nbr, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(wng_nbr, OMAPCONF_ERR_ARG);

	*err_nbr = 0;
	*wng_nbr = 0;

	/* Create audit report log file */
	if (logfile != NULL) {
		strncpy(s, logfile, 255);
	} else {
		workdir = workdir_get();
		if (workdir != NULL) {
			strcpy(s, workdir);

			strcat(s, "full_audit_report.txt");
		} else {
			return OMAPCONF_ERR_INTERNAL;
		}
	}

	fp = fopen(s, "w+");
	if (fp == NULL) {
		fprintf(stderr,
			"omapconf: could not create \"%s\" full audit log file!\n\n",
			s);
		return OMAPCONF_ERR_INTERNAL;
	}
	fprintf(fp,
		"OMAPCONF Full Power Configuration Audit Detailed Log:\n\n");
	omapconf_revision_show(fp);
	chips_info_show(fp, 1);
	release_info_show(fp);

	snprintf(table[row][0], TABLE_MAX_ELT_LEN,
		"Full Power Configuration AUDIT Summary");
	snprintf(table[row][1], TABLE_MAX_ELT_LEN,
		"STATUS");
	row++;

	ret = dpll54xx_audit(DPLL54XX_ID_MAX, OPP54XX_ID_MAX, fp,
		&dplls_err_nbr, &dplls_wng_nbr);
	if (ret != 0)
		return ret;
	fputs("\n\n\n", fp);
	snprintf(table[row][0], TABLE_MAX_ELT_LEN,
		"DPLLs Configuration Audit");
	if (dplls_err_nbr == 0)
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"PASS (0 error, %u warning(s))", dplls_wng_nbr);
	else
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"FAIL (%u error, %u warning(s))",
			dplls_err_nbr, dplls_wng_nbr);
	row++;
	(*err_nbr) += dplls_err_nbr;
	(*wng_nbr) += dplls_wng_nbr;

	ret = audit54xx_sysconfig(fp,
		&syscfg_err_nbr, &syscfg_wng_nbr);
	if (ret != 0)
		return ret;
	fputs("\n\n\n", fp);
	snprintf(table[row][0], TABLE_MAX_ELT_LEN,
		"SYSCONFIG IP Registers Audit");
	if (syscfg_err_nbr == 0)
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"PASS (0 error, %u warning(s))", syscfg_wng_nbr);
	else
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"FAIL (%u error, %u warning(s))",
			syscfg_err_nbr, syscfg_wng_nbr);
	row++;
	(*err_nbr) += syscfg_err_nbr;
	(*wng_nbr) += syscfg_wng_nbr;

	ret = module_clk_rate_audit(fp,
		&clkspeed_err_nbr, &clkspeed_wng_nbr);
	if (ret != 0)
		return ret;
	fputs("\n\n\n", fp);
	snprintf(table[row][0], TABLE_MAX_ELT_LEN,
		"Clocks Speed Audit");
	if (clkspeed_err_nbr == 0)
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"PASS (0 error, %u warning(s))", clkspeed_wng_nbr);
	else
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"FAIL (%u error, %u warning(s))",
			clkspeed_err_nbr, clkspeed_wng_nbr);
	row++;
	(*err_nbr) += clkspeed_err_nbr;
	(*wng_nbr) += clkspeed_wng_nbr;

	ret = clkdmdep54xx_audit(fp,
		&statdep_err_nbr, &statdep_wng_nbr);
	if (ret != 0)
		return ret;
	fputs("\n\n\n", fp);
	snprintf(table[row][0], TABLE_MAX_ELT_LEN,
		"Static Dependencies Audit");
	if (statdep_err_nbr == 0)
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"PASS (0 error, %u warning(s))", statdep_wng_nbr);
	else
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"FAIL (%u error, %u warning(s))",
			statdep_err_nbr, statdep_wng_nbr);
	row++;
	(*err_nbr) += statdep_err_nbr;
	(*wng_nbr) += statdep_wng_nbr;

	ret = ctrlmod54xx_io_audit(fp,
		&io_err_nbr, &io_wng_nbr);
	if (ret != 0)
		return ret;
	fputs("\n\n\n", fp);
	snprintf(table[row][0], TABLE_MAX_ELT_LEN,
		"IO PADCONF Audit");
	if (io_err_nbr == 0)
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"PASS (0 error, %u warning(s))", io_wng_nbr);
	else
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"FAIL (%u error, %u warning(s))",
			io_err_nbr, io_wng_nbr);
	row++;
	(*err_nbr) += io_err_nbr;
	(*wng_nbr) += io_wng_nbr;

	if (stream != NULL) {
		autoadjust_table_fprint(stream, table, row, 2);
		fprintf(stream, "Audit details saved in '%s' file.\n\n\n", s);
	}
	autoadjust_table_fprint(fp, table, row, 2);

	if (err_nbr == 0) {
		sprintf(s,
			"SUCCESS! Full Power Configuration Audit completed with 0 error (%u warning(s))\n\n",
			*wng_nbr);
	} else {
		sprintf(s,
			"FAILED! Full Power Configuration Audit completed with %u error(s) and %u warning(s).\n\n",
			*err_nbr, *wng_nbr);
	}
	if (stream != NULL)
		fputs(s, stdout);
	fputs(s, fp);

	fclose(fp);
	return 0;
}
