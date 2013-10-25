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
#include <voltdomain.h>


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
	int freq_mpu, count, i;
	unsigned int _err_nbr = 0, _wng_nbr = 0;
	const genlist *opp_list;
	opp_t opp;

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
		return OMAPCONF_ERR_UNEXPECTED;
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
			sprintf(s,
				"SUCCESS! DPLL Configuration audit completed with 0 error (%u warning(s)).\n\n",
				*wng_nbr);
		else
			sprintf(s,
				"FAILED! DPLL Configuration audit completed with %u error(s) and %u warning(s).\n\n",
				*err_nbr, *wng_nbr);

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

	/* Retrieve MPU OPPs */
	opp_list = opp_list_get(VDD_MPU);
	if (opp_list == NULL) {
		ret = OMAPCONF_ERR_NOT_AVAILABLE;
		goto audit54xx_dpll_end;
	}

	/* Retrieve number of available MPU OPPs */
	count = opp_count_get(VDD_MPU);
	if (count <= 0) {
		ret = OMAPCONF_ERR_NOT_AVAILABLE;
		goto audit54xx_dpll_end;
	}

	row = 0;
	autoadjust_table_init(table);
	snprintf(table[row][0], TABLE_MAX_ELT_LEN,
		"DPLL Configuration AUDIT Summary");
	autoadjust_table_strncpy(table, row, 1, "Audit STATUS");
	row++;

	for (i = 0; i < count; i++) {
		_err_nbr = 0;
		_wng_nbr = 0;

		/* Set MPU OPP */
		ret = genlist_get((genlist *) opp_list, i, (void *) &opp);
		if (ret != 0) {
			ret = OMAPCONF_ERR_INTERNAL;
			goto audit54xx_dpll_end;
		}

		freq_mpu = module_por_clk_rate_get(MOD_MPU, opp.name);
		if (freq_mpu < 0) {
			err_internal_msg_show();
			goto audit54xx_dpll_end;
		}
		ret = cpufreq_set((unsigned int) freq_mpu);
		if (ret != 0) {
			err_internal_msg_show();
			goto audit54xx_dpll_end;
		}

		fprintf(fp, "DPLLs Configuration Audit at MPU %s:\n\n",
			opp.name);
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "At MPU %s",
			opp.name);

		/* Run audit at this OPP */
		ret = dpll54xx_audit(dpll_id, (opp54xx_id)i, fp,
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
	sprintf(s,
		"NB: DPLL IVA may not have been audited accross all IVA OPPs (no kernel interface to control IVA OPP available).\n\n");
	fputs(s, fp);
	if (stream != NULL) {
		autoadjust_table_fprint(stream, table, row, 2);
		fputs(s, stream);
	}
	if (*err_nbr == 0)
		sprintf(s,
			"\nSUCCESS! DPLLs Configuration audit completed with 0 error (%u warning(s)).\n\n\n",
			*wng_nbr);
	else
		sprintf(s,
			"\nFAILED! DPLLs Configuration audit completed with %u error(s) and %u warning(s).\n\n\n",
			*err_nbr, *wng_nbr);
	fputs(s, fp);
	if (stream != NULL) {
		fprintf(stream,
			"DPLLs Configuration audit details saved in %s file.\n",
			logfilename);
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

	ret = module_sysconfig_audit(fp,
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
