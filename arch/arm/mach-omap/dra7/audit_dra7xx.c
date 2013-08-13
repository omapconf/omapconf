/*
 *
 * @Component			OMAPCONF
 * @Filename			audit_dra7xx.c
 * @Description			DRA7 Power Audit Functions
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


#include <audit_dra7xx.h>
#include <module_dra7xx.h>
#include <module.h>
#include <lib.h>
#include <autoadjust_table.h>
#include <cpufreq.h>
#include <cpuinfo.h>
#include <help.h>
#include <dpll_dra7xx.h>
#include <opp.h>
#include <voltdomain.h>


/* #define AUDIT_DRA7XX_DEBUG */
#ifdef AUDIT_DRA7XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static const char pass[5] = "Pass";
static const char fail[5] = "FAIL";
static const char ignore[12] = "Ignored (1)";
static const char warning[8] = "Warning";


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		audit_dra7xx_dpll
 * @BRIEF		audit DPLL Configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		stream: output file (NULL: no output (silent))
 * @param[in]		dpll_id: DPLL ID
 *				(use DPLL_DRA7XX_ID_MAX to audit all DPLLs)
 * @param[in]		opp_id: OPP ID
 *				(use OPP_DRA7XX_ID_MAX to audit all OPPs)
 * @param[in]		curr_opp: audit current OPP only (=1) or all OPPs (=0)
 * @param[in,out]	err_nbr: audit error number
 * @param[in,out]	wng_nbr: audit warning number
 * @DESCRIPTION		audit DPLL Configuration
 *//*------------------------------------------------------------------------ */
int audit_dra7xx_dpll(FILE *stream, dpll_dra7xx_id dpll_id, opp_dra7xx_id opp_id,
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

	CHECK_ARG_LESS_THAN(dpll_id, DPLL_DRA7XX_ID_MAX + 1, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(opp_id, OPP_DRA7XX_ID_MAX + 1, OMAPCONF_ERR_ARG);
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
		ret = dpll_dra7xx_audit(dpll_id, opp_id, fp, err_nbr, wng_nbr);
		if (ret != 0)
			goto audit_dra7xx_dpll_end;
		ret = dpll_dra7xx_audit(dpll_id, opp_id, stream, err_nbr, wng_nbr);
		if (ret != 0)
			goto audit_dra7xx_dpll_end;

		if (*err_nbr == 0)
			sprintf(s,
				"SUCCESS! DPLL Configuration audit completed "
				"with 0 error (%u warning(s)).\n\n", *wng_nbr);
		else
			sprintf(s,
				"FAILED! DPLL Configuration audit completed with "
				"%u error(s) and %u warning(s).\n\n", *err_nbr, *wng_nbr);

		if (stream != NULL) {
			fprintf(stream, "Audit details saved in %s file.\n\n\n",
				logfilename);
			fputs(s, stream);
		}
		fputs(s, fp);
		ret = 0;
		goto audit_dra7xx_dpll_end;
	}

	/* Save current governor (will be altered by cpufreq_set() call) */
	if (cpufreq_scaling_governor_get(prev_gov) == NULL) {
		ret = OMAPCONF_ERR_NOT_AVAILABLE;
		goto audit_dra7xx_dpll_end;
	}

	/* Retrieve MPU OPPs */
	opp_list = opp_list_get(VDD_MPU);
	if (opp_list == NULL) {
		ret = OMAPCONF_ERR_NOT_AVAILABLE;
		goto audit_dra7xx_dpll_end;
	}

	/* Retrieve number of available MPU OPPs */
	count = opp_count_get(VDD_MPU);
	if (count <= 0) {
		ret = OMAPCONF_ERR_NOT_AVAILABLE;
		goto audit_dra7xx_dpll_end;
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
			goto audit_dra7xx_dpll_end;
		}

		freq_mpu = module_por_clk_rate_get(MOD_MPU, opp.name);
		if (freq_mpu < 0) {
			err_internal_msg_show();
			goto audit_dra7xx_dpll_end;
		}
		ret = cpufreq_set((unsigned int) freq_mpu);
		if (ret != 0) {
			err_internal_msg_show();
			goto audit_dra7xx_dpll_end;
		}

		fprintf(fp, "DPLLs Configuration Audit at MPU %s:\n\n",
			opp.name);
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "At MPU %s",
			opp.name);

		/* Run audit at this OPP */
		ret = dpll_dra7xx_audit(dpll_id, (opp_dra7xx_id)i, fp,
			&_err_nbr, &_wng_nbr);
		if (ret != 0) {
			err_internal_msg_show();
			goto audit_dra7xx_dpll_end;
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
	sprintf(s, "NB: DPLL IVA may not have been audited accross all IVA OPPs"
		"(no kernel interface to control IVA OPP available).\n\n");
	fputs(s, fp);
	if (stream != NULL) {
		autoadjust_table_fprint(stream, table, row, 2);
		fputs(s, stream);
	}
	if (*err_nbr == 0)
		sprintf(s, "\nSUCCESS! DPLLs Configuration audit completed with"
			"0 error (%u warning(s)).\n\n\n", *wng_nbr);
	else
		sprintf(s, "\nFAILED! DPLLs Configuration audit completed with"
			"%u error(s) and %u warning(s).\n\n\n", *err_nbr, *wng_nbr);
	fputs(s, fp);
	if (stream != NULL) {
		fprintf(stream,
			"DPLLs Configuration audit details saved in %s file.\n",
			logfilename);
		fputs(s, stream);
	}


audit_dra7xx_dpll_end:
	/* Restore CPUFreq governor */
	if (strlen(prev_gov) != 0)
		cpufreq_scaling_governor_set(prev_gov, prev_gov2);
	/* Close opened file */
	if (fp != NULL)
		fclose(fp);
	return ret;
}
