/*
 *
 * @Component			OMAPCONF
 * @Filename			audit44xx.c
 * @Description			OMAP4 Power Audit Functions
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


#include <audit.h>
#include <audit44xx.h>
#include <lib_android.h>
#include <uc_audit44xx.h>
#include <module44xx.h>
#include <lib.h>
#include <lib44xx.h>
#include <autoadjust_table.h>
#include <cpufreq.h>
#include <cpuinfo.h>
#include <help.h>
#include <interrupts.h>
#include <timer_stats.h>
#include <cstate.h>
#include <emif44xx.h>
#include <dep44xx.h>
#include <cm44xx.h>
#include <prm44xx.h>
#include <unistd.h>
#include <vp44xx.h>
#include <pads44xx.h>


/* #define AUDIT44XX_DEBUG */
#ifdef AUDIT44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

static const char pass[5] = "Pass";
static const char fail[5] = "FAIL";
static const char ignore[12] = "Ignored (1)";
static const char warning[8] = "Warning";


/* #define MODULE_AUTOIDLE_MODE_AUDIT44XX_DEBUG */
#ifdef MODULE_AUTOIDLE_MODE_AUDIT44XX_DEBUG
#undef dprintf
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#endif
/* ------------------------------------------------------------------------*//**
 * @FUNCTION		module_autoidle_mode_audit44xx
 * @BRIEF		module autoidle mode audit.
 * @RETURNS		pointer to global pass string in case of successfull
 *			audit
 *			pointer to global fail string in case of failing audit
 *			pointer to global ignore string in case of unavailable
 *			or internal error
 * @param[in]		mod_id: module ID
 * @param[in,out]	mode: module autoidle mode (returned)
 * @param[in,out]	mode_por: expected module autoidle mode (returned)
 * @param[in,out]	err_nbr: error number (returned)
 * @param[in,out]	wng_nbr: warning number (returned)
 * @DESCRIPTION		module autoidle mode audit.
 *//*------------------------------------------------------------------------ */
char *module_autoidle_mode_audit44xx(mod44xx_id mod_id,
	mod_autoidle_mode *mode, mod_autoidle_mode *mode_por,
	unsigned int *err_nbr, unsigned int *wng_nbr)
{
	int ret;
	char mod_name[MOD44XX_MAX_NAME_LENGTH];

	CHECK_CPU(44xx, (char *) ignore);
	CHECK_NULL_ARG(mode, (char *) ignore);
	CHECK_NULL_ARG(mode_por, (char *) ignore);
	CHECK_NULL_ARG(err_nbr, (char *) ignore);
	CHECK_NULL_ARG(wng_nbr, (char *) ignore);

	*err_nbr = 0;
	*wng_nbr = 0;
	*mode = MOD_AUTOIDLE_MODE_MAX;
	*mode_por = MOD_AUTOGATING;

	/* Get module autoidle mode */
	ret = mod44xx_get_autoidle_mode(mod_id, mode);
	if (ret == 1) {
		if (*mode != *mode_por) {
			dprintf("%s(): %s AUTOIDLE mode disabled.\n", __func__,
				mod44xx_get_name(mod_id, mod_name));
			(*err_nbr)++;
			return (char *) fail;
		} else {
			dprintf("%s(): %s AUTOIDLE mode enabled.\n", __func__,
				mod44xx_get_name(mod_id, mod_name));
			return (char *) pass;
		}
	} else if (ret == 0) {
		dprintf(
			"%s(): %s disabled. Module registers cannot be audited.\n",
			__func__, mod44xx_get_name(mod_id, mod_name));
		return (char *) ignore;
	} else if (ret == OMAPCONF_ERR_NOT_AVAILABLE) {
		dprintf("%s(): %s has no AUTOIDLE bit\n",
			__func__, mod44xx_get_name(mod_id, mod_name));
		return (char *) ignore;
	} else {
		fprintf(stderr,
			"omapconf: internal error while checking module %s AUTOIDLE bit! (%d)\n",
			mod44xx_get_name(mod_id, mod_name), ret);
		return (char *) ignore;
	}
}
#ifdef MODULE_AUTOIDLE_MODE_AUDIT44XX_DEBUG
#undef dprintf
#define dprintf(format, ...)
#endif


/* #define MODULE_IDLE_MODE_AUDIT44XX_DEBUG */
#ifdef MODULE_IDLE_MODE_AUDIT44XX_DEBUG
#undef dprintf
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#endif
/* ------------------------------------------------------------------------*//**
 * @FUNCTION		module_idle_mode_audit44xx
 * @BRIEF		module idle mode audit.
 * @RETURNS		pointer to global pass string in case of successfull
 *			audit
 *			pointer to global fail string in case of failing audit
 *			pointer to global warning string in case of sub-optimal
 *			configuration
 *			pointer to global ignore string in case of unavailable
 *			or internal error
 * @param[in]		mod_id: module ID
 * @param[in,out]	mode: module idle mode (returned)
 * @param[in,out]	mode_por: expected module idle mode (returned)
 * @param[in,out]	err_nbr: error number (returned)
 * @param[in,out]	wng_nbr: warning number (returned)
 * @DESCRIPTION		module idle mode audit.
 *//*------------------------------------------------------------------------ */
char *module_idle_mode_audit44xx(mod44xx_id mod_id,
	mod_idle_mode *mode, mod_idle_mode *mode_por,
	unsigned int *err_nbr, unsigned int *wng_nbr)
{
	int ret;
	char mod_name[MOD44XX_MAX_NAME_LENGTH];
	char *status;

	CHECK_CPU(44xx, (char *) ignore);
	CHECK_NULL_ARG(mode, (char *) ignore);
	CHECK_NULL_ARG(mode_por, (char *) ignore);
	CHECK_NULL_ARG(err_nbr, (char *) ignore);
	CHECK_NULL_ARG(wng_nbr, (char *) ignore);

	*err_nbr = 0;
	*wng_nbr = 0;
	*mode = MOD_IDLE_MODE_MAX;
	*mode_por = MOD_SMART_IDLE;

	/* Get module IDLE mode */
	ret = mod44xx_get_idle_mode(mod_id, mode);
	switch (ret) {
	case 1:
		break;

	case 0:
		dprintf(
			"%s(): %s disabled. Module registers cannot be audited.\n",
			__func__, mod44xx_get_name(mod_id, mod_name));
		status = (char *) ignore;
		goto module_idle_mode_audit44xx_end;

	case OMAPCONF_ERR_NOT_AVAILABLE:
		dprintf("%s(): %s has no IDLE bit\n",
			__func__, mod44xx_get_name(mod_id, mod_name));
		status = (char *) ignore;
		goto module_idle_mode_audit44xx_end;

	default:
		fprintf(stderr,
			"omapconf: internal error while checking module %s IDLE mode! (%d)\n",
			mod44xx_get_name(mod_id, mod_name), ret);
		status = (char *) ignore;
		goto module_idle_mode_audit44xx_end;
	}

	switch (*mode) {
	case MOD_SMART_IDLE_WAKEUP:
		dprintf(
			"%s(): %s IDLE  mode correctly configured to SMART-IDLE WAKEUP.\n",
			__func__, mod44xx_get_name(mod_id, mod_name));
		status = (char *) pass;
		goto module_idle_mode_audit44xx_end;

	case MOD_SMART_IDLE:
		if (mod44xx_has_smart_idle_wakeup_mode(mod_id)) {
			dprintf(
				"%s(): %s IDLE mode set to SMART-IDLE instead of SMART-IDLE WAKEUP!\n",
				__func__, mod44xx_get_name(mod_id, mod_name));
			status = (char *) fail;
			(*err_nbr)++;
		} else {
			dprintf(
				"%s(): %s IDLE mode correctly configured to SMART-IDLE.\n",
				__func__, mod44xx_get_name(mod_id, mod_name));
			status = (char *) pass;
		}
		goto module_idle_mode_audit44xx_end;

	case MOD_FORCE_IDLE:
		dprintf(
			"%s(): %s IDLE mode = FORCE-IDLE instead of SMART-IDLE.\n",
			__func__, mod44xx_get_name(mod_id, mod_name));
		if (mod_id == OMAP4_SYNCTIMER) {
			/* This module has no Smart-Idle mode */
			status = (char *) pass;
		} else {
			status = (char *) warning;
			(*wng_nbr)++;
		}
		goto module_idle_mode_audit44xx_end;

	default:
		if ((mod_id == OMAP4_UART1) ||
			(mod_id == OMAP4_UART2) ||
			(mod_id == OMAP4_UART3) ||
			(mod_id == OMAP4_UART4)) {
			/*
			 * UART IP idle management is buggy (cf errata).
			 * When active, must be used in no-idle mode.
			 */
			 status = (char *) pass;
		} else {
			dprintf(
				"%s(): %s IDLE mode not set to SMART-IDLE but %s!\n",
				__func__, mod44xx_get_name(mod_id, mod_name),
				mod_idle_mode_name_get(*mode));
			status = (char *) fail;
			(*err_nbr)++;
		}
		goto module_idle_mode_audit44xx_end;
	}

module_idle_mode_audit44xx_end:
	return status;
}
#ifdef MODULE_IDLE_MODE_AUDIT44XX_DEBUG
#undef dprintf
#define dprintf(format, ...)
#endif


/* #define MODULE_STANDBY_MODE_AUDIT44XX_DEBUG */
#ifdef MODULE_STANDBY_MODE_AUDIT44XX_DEBUG
#undef dprintf
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#endif
/* ------------------------------------------------------------------------*//**
 * @FUNCTION		module_standby_mode_audit44xx
 * @BRIEF		module standby mode audit.
 * @RETURNS		pointer to global pass string in case of successfull
 *			audit
 *			pointer to global fail string in case of failing audit
 *			pointer to global warning string in case of sub-optimal
 *			configuration
 *			pointer to global ignore string in case of unavailable
 *			or internal error
 * @param[in]		mod_id: module ID
 * @param[in,out]	mode: module standby mode (returned)
 * @param[in,out]	mode_por: expected module standby mode (returned)
 * @param[in,out]	err_nbr: error number (returned)
 * @param[in,out]	wng_nbr: warning number (returned)
 * @DESCRIPTION		module standby mode audit.
 *//*------------------------------------------------------------------------ */
char *module_standby_mode_audit44xx(mod44xx_id mod_id,
	mod_standby_mode *mode, mod_standby_mode *mode_por,
	unsigned int *err_nbr, unsigned int *wng_nbr)
{
	int ret;
	char mod_name[MOD44XX_MAX_NAME_LENGTH];

	CHECK_CPU(44xx, (char *) ignore);
	CHECK_NULL_ARG(mode, (char *) ignore);
	CHECK_NULL_ARG(mode_por, (char *) ignore);
	CHECK_NULL_ARG(err_nbr, (char *) ignore);
	CHECK_NULL_ARG(wng_nbr, (char *) ignore);

	*err_nbr = 0;
	*wng_nbr = 0;
	*mode = MOD_STANDBY_MODE_MAX;
	*mode_por = MOD_SMART_STANDBY;

	/* Get module STANDBY mode */
	ret = mod44xx_get_standby_mode(mod_id, mode);
	switch (ret) {
	case 1:
		switch (*mode) {
		case MOD_SMART_STANDBY:
			dprintf(
				"%s(): %s STANDBY mode correctly configured to MOD_SMART_STANDBY.\n",
				__func__, mod44xx_get_name(mod_id, mod_name));
			return (char *) pass;
		case MOD_FORCE_STANDBY:
			(*wng_nbr)++;
			dprintf(
				"%s(): %s STANDBY mode = FORCE-IDLE instead of SMART-STANDBY.\n",
				__func__, mod44xx_get_name(mod_id, mod_name));
			return (char *) warning;
		case MOD_STANDBY_MODE_RESERVED:
			if (mod_id == OMAP4_FSUSBHOST) {
				dprintf(
					"%s(): FSUSBHOST STANDBY mode correctly set to SMART-STANDBY WITH WAKEUP\n",
					__func__);
				return (char *) pass;
			} else {
				(*err_nbr)++;
				#ifdef MODULE_STANDBY_MODE_AUDIT44XX_DEBUG
				dprintf(
					"%s(): %s STANDBY mode not set to SMART-STANDBY but %s!\n",
					__func__,
					mod44xx_get_name(mod_id, mod_name),
					mod_standby_mode_name_get(*mode));
				#endif
				return (char *) fail;
			}
		default:
			(*err_nbr)++;
			#ifdef MODULE_STANDBY_MODE_AUDIT44XX_DEBUG
			dprintf(
				"%s(): %s STANDBY mode not set to SMART-STANDBY but %s!\n",
				__func__, mod44xx_get_name(mod_id, mod_name),
				mod_standby_mode_name_get(*mode));
			#endif
			return (char *) fail;
		}
	case 0:
		dprintf(
			"%s(): %s disabled. Module registers cannot be audited.\n",
			__func__, mod44xx_get_name(mod_id, mod_name));
		return (char *) ignore;
	case OMAPCONF_ERR_NOT_AVAILABLE:
		dprintf("%s(): %s has no STANDBY mode\n",
			__func__, mod44xx_get_name(mod_id, mod_name));
		return (char *) ignore;
	default:
		fprintf(stderr,
			"omapconf: internal error while checking module %s STANDBY mode! (%d)\n",
			mod44xx_get_name(mod_id, mod_name), ret);
		return (char *) ignore;
	}
}
#ifdef MODULE_STANDBY_MODE_AUDIT44XX_DEBUG
#undef dprintf
#define dprintf(format, ...)
#endif


/* #define MODULE_CLOCKACTIVITY_BIT_AUDIT44XX_DEBUG */
#ifdef MODULE_CLOCKACTIVITY_BIT_AUDIT44XX_DEBUG
#undef dprintf
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#endif
/* ------------------------------------------------------------------------*//**
 * @FUNCTION		module_clockactivity_bit_audit44xx
 * @BRIEF		module clock activity mode audit.
 * @RETURNS		pointer to global pass string in case of successfull
 *			audit
 *			pointer to global fail string in case of failing audit
 *			pointer to global warning string in case of sub-optimal
 *			configuration
 *			pointer to global ignore string in case of unavailable
 *			or internal error
 * @param[in]		mod_id: module ID
 * @param[in,out]	mode: module clock activity mode (returned)
 * @param[in,out]	mode_por: expected module clock activity mode (returned)
 * @param[in,out]	err_nbr: error number (returned)
 * @param[in,out]	wng_nbr: warning number (returned)
 * @DESCRIPTION		module clock activity mode audit.
 *//*------------------------------------------------------------------------ */
char *module_clockactivity_bit_audit44xx(mod44xx_id mod_id,
	mod_clock_activity_mode *mode,
	mod_clock_activity_mode *mode_por,
	unsigned int *err_nbr, unsigned int *wng_nbr)
{
	int ret;
	char mod_name[MOD44XX_MAX_NAME_LENGTH];

	CHECK_CPU(44xx, (char *) ignore);
	CHECK_NULL_ARG(mode, (char *) ignore);
	CHECK_NULL_ARG(mode_por, (char *) ignore);
	CHECK_NULL_ARG(err_nbr, (char *) ignore);
	CHECK_NULL_ARG(wng_nbr, (char *) ignore);

	*err_nbr = 0;
	*wng_nbr = 0;
	*mode = MOD_CLOCK_ACTIVITY_MODE_MAX;
	*mode_por = MOD_FCLK_AUTO_ICLK_AUTO;

	/* Get module CLOCKACTIVITY mode */
	ret = mod44xx_get_clock_activity_mode(mod_id, mode);
	switch (ret) {
	case 1:
		switch (*mode) {
		case MOD_FCLK_AUTO_ICLK_AUTO:
			/*
			 * Functional clock can be switched-off;
			 * L4 clock can be switched-off
			 */
			dprintf(
				"%s(): CLOCKACTIVITY bit correctly configured\n",
				__func__);
			return (char *) pass;
		case MOD_FCLK_AUTO_ICLK_ON:
			/*
			 * Functional clock can be switched-off;
			 * L4 clock is maintained during wake-up period
			 */
		case MOD_FCLK_ON_ICLK_AUTO:
			/*
			 * Functional clock is maintained during wake-up period;
			 * L4 clock can be switched-off
			 */
			(*wng_nbr)++;
			#ifdef MODULE_CLOCKACTIVITY_BIT_AUDIT44XX_DEBUG
			dprintf("%s(): Warning: %s CLOCKACTIVITY = %s\n",
				__func__,
				mod44xx_get_name(mod_id, mod_name),
				mod_clock_activity_mode_name_get(*mode));
			#endif
			return (char *) warning;
		case MOD_FCLK_ON_ICLK_ON:
			/*
			 * Functional clock is maintained during wake-up period;
			 * L4 clock is maintained during wake-up period
			 */
		default:
			(*err_nbr)++;
			#ifdef MODULE_CLOCKACTIVITY_BIT_AUDIT44XX_DEBUG
			dprintf("%s(): Warning: %s CLOCKACTIVITY = %s\n",
				__func__,
				mod44xx_get_name(mod_id, mod_name),
				mod_clock_activity_mode_name_get(*mode));
			#endif
			return (char *) fail;
		}
	case 0:
		dprintf(
			"%s(): %s disabled. Module registers cannot be audited.\n",
			__func__, mod44xx_get_name(mod_id, mod_name));
		return (char *) ignore;
	case OMAPCONF_ERR_NOT_AVAILABLE:
		dprintf("%s(): %s has no CLOCKACTIVITY mode\n", __func__,
			mod44xx_get_name(mod_id, mod_name));
		return (char *) ignore;
	default:
		fprintf(stderr,
			"omapconf: internal error while checking %s CLOCKACTIVITY mode! (%d)\n",
			mod44xx_get_name(mod_id, mod_name), ret);
		return (char *) ignore;
	}
}
#ifdef MODULE_CLOCKACTIVITY_BIT_AUDIT44XX_DEBUG
#undef dprintf
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		audit44xx_dpll
 * @BRIEF		audit DPLL Configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		stream: output file (NULL: no output (silent))
 * @param[in]		dpll_id: DPLL ID
 *				(use DPLL44XX_ID_MAX to audit all DPLLs)
 * @param[in]		opp_id: OPP ID
 *				(use OPP44XX_ID_MAX to audit all OPPs)
 * @param[in]		curr_opp: audit current OPP only (=1) or all OPPs (=0)
 * @param[in,out]	err_nbr: audit error number
 * @param[in,out]	wng_nbr: audit warning number
 * @DESCRIPTION		audit DPLL Configuration
 *//*------------------------------------------------------------------------ */
int audit44xx_dpll(FILE *stream, dpll44xx_id dpll_id, opp44xx_id opp_id,
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
	opp44xx_id opp;
	double freq_mpu;
	unsigned int _err_nbr = 0, _wng_nbr = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(dpll_id, DPLL44XX_ID_MAX + 1, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(opp_id, OPP44XX_ID_MAX + 1, OMAPCONF_ERR_ARG);
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
		ret = dpll44xx_audit(dpll_id, opp_id, fp, err_nbr, wng_nbr);
		if (ret != 0)
			goto audit44xx_dpll_end;
		ret = dpll44xx_audit(dpll_id, opp_id, stream, err_nbr, wng_nbr);
		if (ret != 0)
			goto audit44xx_dpll_end;

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
		goto audit44xx_dpll_end;
	}

	/* Save current governor (will be altered by cpufreq_set() call) */
	if (cpufreq_scaling_governor_get(prev_gov) == NULL) {
		ret = OMAPCONF_ERR_NOT_AVAILABLE;
		goto audit44xx_dpll_end;
	}

	/* Retrieve number of available MPU OPPs */
	if (cpufreq_opp_nbr_get() == 0) {
		ret = OMAPCONF_ERR_NOT_AVAILABLE;
		goto audit44xx_dpll_end;
	}

	row = 0;
	autoadjust_table_init(table);
	snprintf(table[row][0], TABLE_MAX_ELT_LEN,
		"DPLL Configuration AUDIT Summary");
	autoadjust_table_strncpy(table, row, 1, "Audit STATUS");
	row++;

	for (opp = OMAP4_OPP50; (unsigned int) opp <= cpufreq_opp_nbr_get();
		opp++) {
		_err_nbr = 0;
		_wng_nbr = 0;

		/* Set MPU OPP */
		ret = mod44xx_get_por_clk_speed(OMAP4_MPU, opp, &freq_mpu);
		if (ret != 0) {
			err_internal_msg_show();
			goto audit44xx_dpll_end;
		}

		ret = cpufreq_set((unsigned int) (freq_mpu * 1000));
		if (ret != 0) {
			err_internal_msg_show();
			goto audit44xx_dpll_end;
		}

		fprintf(fp, "DPLLs Configuration Audit at MPU %s:\n\n",
			opp44xx_name_get(opp, OMAP4_VDD_MPU));
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "At MPU %s",
			opp44xx_name_get(opp, OMAP4_VDD_MPU));

		/* Run audit at this OPP */
		ret = dpll44xx_audit(dpll_id, OPP44XX_ID_MAX, fp,
			&_err_nbr, &_wng_nbr);
		if (ret != 0) {
			err_internal_msg_show();
			goto audit44xx_dpll_end;
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


audit44xx_dpll_end:
	/* Restore CPUFreq governor */
	if (strlen(prev_gov) != 0)
		cpufreq_scaling_governor_set(prev_gov, prev_gov2);
	/* Close opened file */
	if (fp != NULL)
		fclose(fp);
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		audit44xx_dpll_main
 * @BRIEF		analyze command-line arguments & call DPLL audit with
 *			selected options.
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_INTERNAL
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		analyze command-line arguments & call DPLL audit with
 *			selected options.
 *//*------------------------------------------------------------------------ */
int audit44xx_dpll_main(int argc, char *argv[])
{
	int ret = 0;
	dpll44xx_id dpll_id;
	opp44xx_id opp_id;
	unsigned int err_nbr = 0, wng_nbr = 0;
	unsigned short pos_opp_id, pos_dpll_id, curr_opp;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(argv, OMAPCONF_ERR_ARG);

	/* Retrieve user options */
	dprintf("%s(): argc=%u\n", __func__, argc);
	#ifdef AUDIT44XX_DEBUG
	for (curr_opp = 0; curr_opp < argc; curr_opp++) {
		dprintf("%s(): argv[%u]=%s\n", __func__,
			curr_opp, argv[curr_opp]);
	}
	#endif

	if (argc == 0) {
		/* Audit all DPLLs at current OPP by default */
		dpll_id = DPLL44XX_ID_MAX;
		opp_id = OPP44XX_ID_MAX;
		curr_opp = 1;
		goto audit44xx_dpll_audit;
	} else if (argc == 2) {
		if (strcmp(argv[0], "-d") == 0) {
			opp_id = OPP44XX_ID_MAX;
			curr_opp = 1;
			dpll_id = dpll44xx_s2id(argv[1]);
			if (dpll_id == DPLL44XX_ID_MAX) {
				if (strcmp(argv[1], "all") == 0)
					dpll_id = DPLL44XX_ID_MAX;
				else
					goto audit44xx_dpll_err_arg;
			}
			goto audit44xx_dpll_audit;
		} else if (strcmp(argv[0], "-o") == 0) {
			dpll_id = DPLL44XX_ID_MAX;
			curr_opp = 1;
			opp_id = opp44xx_s2id(argv[1]);
			if (opp_id == OPP44XX_ID_MAX) {
				if (strcmp(argv[1], "all") == 0) {
					opp_id = OPP44XX_ID_MAX;
					curr_opp = 0;
				} else {
					goto audit44xx_dpll_err_arg;
				}
			}
			goto audit44xx_dpll_audit;
		} else {
			goto audit44xx_dpll_err_arg;
		}
	} else if (argc == 4) {
		curr_opp = 1;
		if (strcmp(argv[0], "-d") == 0)
			pos_dpll_id = 1;
		else if (strcmp(argv[2], "-d") == 0)
			pos_dpll_id = 3;
		else
			goto audit44xx_dpll_err_arg;
		dpll_id = dpll44xx_s2id(argv[pos_dpll_id]);
		if (dpll_id == DPLL44XX_ID_MAX) {
			if (strcmp(argv[pos_dpll_id], "all") == 0)
				dpll_id = DPLL44XX_ID_MAX;
			else
				goto audit44xx_dpll_err_arg;
		}

		if (strcmp(argv[0], "-o") == 0)
			pos_opp_id = 1;
		else if (strcmp(argv[2], "-o") == 0)
			pos_opp_id = 3;
		else
			goto audit44xx_dpll_err_arg;
		opp_id = opp44xx_s2id(argv[pos_opp_id]);
		if (opp_id == OPP44XX_ID_MAX) {
			if (strcmp(argv[pos_opp_id], "all") == 0) {
				opp_id = OPP44XX_ID_MAX;
				curr_opp = 0;
			} else {
				goto audit44xx_dpll_err_arg;
			}
		}
		goto audit44xx_dpll_audit;
	} else {
		goto audit44xx_dpll_err_arg;
	}

audit44xx_dpll_audit:
	dprintf("%s(): dpll_id=%s, opp_id=%s curr_opp=%u\n", __func__,
		dpll44xx_name_get(dpll_id),
		opp44xx_name_get(opp_id, OMAP4_VDD_MPU), curr_opp);

	ret = audit44xx_dpll(stdout, dpll_id, opp_id, curr_opp,
		&err_nbr, &wng_nbr);

	goto audit44xx_dpll_end;

audit44xx_dpll_err_arg:
	help(HELP_AUDIT);
	ret = OMAPCONF_ERR_ARG;

audit44xx_dpll_end:
	return ret;
}


/* #define SYSCONFIG_AUDIT44XX_DEBUG */
#ifdef SYSCONFIG_AUDIT44XX_DEBUG
#undef dprintf
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#endif
/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sysconfig_audit44xx
 * @BRIEF		OMAP4 SYSCONFIG registers audit.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in,out]	stream: output file - NULL: no output (silent)
 * @param[in,out]	err_nbr: pointer to return audit error number
 * @param[in,out]	wng_nbr: pointer to return audit warning number
 * @DESCRIPTION		OMAP4 SYSCONFIG registers audit.
 *//*------------------------------------------------------------------------ */
int sysconfig_audit44xx(FILE *stream, unsigned int *err_nbr,
	unsigned int *wng_nbr)
{
	mod44xx_id i;
	mod_autoidle_mode autoidle_mode, autoidle_mode_por;
	mod_idle_mode idle_mode, idle_mode_por;
	mod_interface_type type;
	mod_standby_mode standby_mode, standby_mode_por;
	mod_clock_activity_mode clock_activity_mode,
		clock_activity_mode_por;
	char *status;
	unsigned int err_nbr_tmp = 0, wng_nbr_tmp = 0;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row;
	char mod_name[MOD44XX_MAX_NAME_LENGTH];
	char pwst[6], pwtgst[6];

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(err_nbr, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(wng_nbr, OMAPCONF_ERR_ARG);

	*err_nbr = 0;
	*wng_nbr = 0;

	autoadjust_table_init(table);

	row = 0;
	strncpy(table[row][0], "MODULES SYSCONFIG AUDIT", TABLE_MAX_ELT_LEN);
	strncpy(table[row][1], "AUTOIDLE", TABLE_MAX_ELT_LEN);
	strncpy(table[row][2], "IDLE", TABLE_MAX_ELT_LEN);
	strncpy(table[row][3], "STANDBY", TABLE_MAX_ELT_LEN);
	strncpy(table[row][4], "CLOCKACTIVITY", TABLE_MAX_ELT_LEN);
	row++;

	for (i = 0; i < OMAP4_MODULE_ID_MAX; i++) {
		dprintf("\n%s(): Module #%d name = %s\n", __func__,
			i, mod44xx_get_name(i, mod_name));

		switch (i) {
		case OMAP4_CRYPTODMA:
		case OMAP4_AES1:
		case OMAP4_AES2:
		case OMAP4_SHA2MD5_1:
		case OMAP4_RNG:
		case OMAP4_DES3DES:
		case OMAP4_PKAEIP29:
		case OMAP4_USIM:
		case OMAP4_WDT1:
		case OMAP4_TIMER12:
		case OMAP4_CUST_EFUSE:
			/*
			 * Secure Modules, not accessible on HS,
			 * not referenced on GP
			 */
			dprintf("\tSecure Modules (not accessible (HS) / not "
				"referenced (GP)\n");
			continue;

		case OMAP4_ICONT1:
		case OMAP4_ICONT2:
		case OMAP4_VDMA:
		case OMAP4_IME3:
		case OMAP4_IPE3:
		case OMAP4_ILF3:
		case OMAP4_MC3:
		case OMAP4_CALC3:
		case OMAP4_ECD3:
		case OMAP4_ICONT1_SB:
		case OMAP4_ICONT2_SB:
		case OMAP4_ILF3_SB:
		case OMAP4_IME3_SB:
		case OMAP4_CALC3_SB:
		case OMAP4_IPE3_SB:
		case OMAP4_MC3_SB:
		case OMAP4_ECD3_SB:
		case OMAP4_SIMCOP:
		case OMAP4_SIMCOP_DMA:
		case OMAP4_SIMCOP_DCT:
		case OMAP4_SIMCOP_VLCDJ:
		case OMAP4_SIMCOP_ROT:
		case OMAP4_MPU_M3:
			/*
			 * These are HW accelerators IP. During AV record,
			 * modules are changing state quicker than omapconf
			 * code, causing from time to time incorrect access to
			 * a disabled module (i.e. bus error).
			 * Workaround: skip these internal HW IPs.
			 */
			dprintf("\tHW accelerators IP, skipped.\n");
			continue;

		case OMAP4_DISPC:
			/* With clock autogating enabled, DISPC I-CLK is getting
			 * gated at such high pace (bursts) that there is a
			 * probability of bus error */
			dprintf("\tDISPC, skipped.\n");
			continue;

		case OMAP4_DSI1:
		case OMAP4_DSI2:
		case OMAP4_HDMI:
		case OMAP4_RFBI:
			/* HACK Galaxy Nexus JOP40D: when display if OFF, power
			 * domain is put in RET but DISPC is left in
			 * "Enabled (EXPLICITLY)" mode, causing faulty attempt
			 * to access an idle module.
			 */
			if (pwrdm_states_get("DSS", pwst, pwtgst) != 0) {
				fprintf(stderr,
					"omapconf: %s(): could not retrieve DSS power domain status!!!\n",
					__func__);
				continue;
			} else if (strcmp(pwst, "ON") != 0) {
				dprintf("\t%s skipped.\n", mod44xx_get_name(i, mod_name));
				continue;
			} else {
				goto sysconfig_audit44xx_default;
			}

		case OMAP4_BB2D:
			if (!cpu_is_omap4470())
				continue;
			else
				goto sysconfig_audit44xx_default;

		case OMAP4_FSUSBHOST:
			if (cpu_is_omap4470())
				continue;
			else
				goto sysconfig_audit44xx_default;

sysconfig_audit44xx_default:
		default:
			/* Get module interface type */
			mod44xx_get_interface_type(i, &type);
			if (type == MOD_INTERFACE_NONE) {
				dprintf("\tNo SYSCONFIG register to audit.\n");
				continue;
			}

			/* Check if module is accessible */
			if (mod44xx_is_accessible(i) != 1) {
				snprintf(table[row][0], TABLE_MAX_ELT_LEN,
					"%s", mod44xx_get_name(i, mod_name));
				snprintf(table[row][1], TABLE_MAX_ELT_LEN,
					"NA");
				snprintf(table[row][2], TABLE_MAX_ELT_LEN,
					"NA");
				snprintf(table[row][3], TABLE_MAX_ELT_LEN,
					"NA");
				snprintf(table[row][4], TABLE_MAX_ELT_LEN,
					"NA");
				row++;
				dprintf("\tModule is not accessible.\n");
				continue;
			}

			snprintf(table[row][0], TABLE_MAX_ELT_LEN,
				"%s", mod44xx_get_name(i, mod_name));
			/* Audit module's autoidle bit */
			status = module_autoidle_mode_audit44xx(i,
				&autoidle_mode, &autoidle_mode_por,
				&err_nbr_tmp, &wng_nbr_tmp);
			if (status == pass) {
				strncpy(table[row][1], status,
					TABLE_MAX_ELT_LEN);

			} else if ((i == OMAP4_ICR_MDM) ||
				(i == OMAP4_ICR_MPU)) {
				/* by default no C2C driver */
				status = (char *) warning;
				(*wng_nbr)++;
				snprintf(table[row][1],	TABLE_MAX_ELT_LEN,
					"Warning (%s)",
					mod_autoidle_mode_name_get(
						autoidle_mode));
			} else if (status == fail) {
				(*err_nbr)++;
				strncpy(table[row][1], status,
					TABLE_MAX_ELT_LEN);
			} /* else do nothing in case of status == ignore */
			dprintf("\tAutoidle audit: mode=%s, status=%s\n",
				mod_autoidle_mode_name_get(autoidle_mode),
				status);
			dprintf("\t\tTotal error number=%u, total warning "
				"number=%u\n", *err_nbr, *wng_nbr);

			/* Audit module's IDLE mode */
			status = module_idle_mode_audit44xx(i,
				&idle_mode, &idle_mode_por,
				&err_nbr_tmp, &wng_nbr_tmp);
			if (status == pass) {
				strncpy(table[row][2], status,
					TABLE_MAX_ELT_LEN);
			} else if (status == warning) {
				(*wng_nbr)++;
				snprintf(table[row][2], TABLE_MAX_ELT_LEN,
					"Warning (Force-Idle)");
			} else if ((i == OMAP4_TIMER1) ||
				(i == OMAP4_DSI1) ||
				(i == OMAP4_DSI2) ||
				(i == OMAP4_HDMI)) {
				/* still configured to no-idle ... */
				status = (char *) warning;
				(*wng_nbr)++;
				snprintf(table[row][2], TABLE_MAX_ELT_LEN,
					"Warning (%s)",
					mod_idle_mode_name_get(idle_mode));
			} else if (status == fail) {
				(*err_nbr)++;
				snprintf(table[row][2], TABLE_MAX_ELT_LEN,
					"FAIL (%s)",
					mod_idle_mode_name_get(idle_mode));
			} /* else do nothing in case of status == ignore */
			dprintf("\tIdle mode audit: mode=%s, status=%s\n",
				mod_idle_mode_name_get(idle_mode), status);
			dprintf("\t\tTotal error number=%u, total warning "
				"number=%u\n", *err_nbr, *wng_nbr);

			/* Audit module's STANDBY mode */
			status = module_standby_mode_audit44xx(i,
				&standby_mode, &standby_mode_por,
				&err_nbr_tmp, &wng_nbr_tmp);
			if (status == pass) {
				strncpy(table[row][3], status,
					TABLE_MAX_ELT_LEN);
			} else if (status == fail) {
				(*err_nbr)++;
				snprintf(table[row][3], TABLE_MAX_ELT_LEN,
					"FAIL (%s)", mod_standby_mode_name_get(
						standby_mode));
			} else if (status == warning) {
				(*wng_nbr)++;
				snprintf(table[row][3], TABLE_MAX_ELT_LEN,
					"Warning (Force-standby)");
			} /* else do nothing in case of status == ignore */
			dprintf("\tStandby mode audit: mode=%s, status=%s\n",
				mod_standby_mode_name_get(standby_mode),
				status);
			dprintf("\t\tTotal error number=%u, total warning "
				"number=%u\n", *err_nbr, *wng_nbr);

			/* Audit module's CLOCKACTIVITY bit configuration */
			status = module_clockactivity_bit_audit44xx(i,
				&clock_activity_mode, &clock_activity_mode_por,
				&err_nbr_tmp, &wng_nbr_tmp);
			if (status == pass) {
				strncpy(table[row][4], status,
					TABLE_MAX_ELT_LEN);
			} else if (status == fail) {
				(*err_nbr)++;
				snprintf(table[row][4], TABLE_MAX_ELT_LEN,
					"FAIL (%s)",
					mod_clock_activity_mode_name_get(
						clock_activity_mode));
			} else if (status == warning) {
				(*wng_nbr)++;
				snprintf(table[row][4], TABLE_MAX_ELT_LEN,
					"Warning (%s)",
					mod_clock_activity_mode_name_get(
						clock_activity_mode));
			} /* else do nothing in case of status == ignore */
			dprintf("\tCLOCKACTIVITY mode audit: mode=%s, "
				"status=%s\n", mod_clock_activity_mode_name_get(
					clock_activity_mode),
				status);
			dprintf("\t\tTotal error number=%u, total warning "
				"number=%u\n", *err_nbr, *wng_nbr);
			row++;
		}
	}

	if (stream != NULL) {
		autoadjust_table_fprint(stream, table, row, 5);
		fprintf(stream, "NB:\n");
		fprintf(stream, "  - Show 'NA' when module is disabled.\n");
		fprintf(stream, "  - Show empty cell(s) when module does not "
			"feature this mode.\n");
		fprintf(stream, "  - AUTOIDLE MODE:\n");
		fprintf(stream, "    - Report Pass if enabled, FAIL otherwise."
			"\n");
		fprintf(stream, "  - IDLE MODE:\n");
		fprintf(stream, "    - Report Pass if set to \"Smart-Idle\" or "
			"\"Smart-Idle Wakeup\" (when available).\n");
		fprintf(stream, "      - Modules featuring \"Smart-Idle Wakeup"
			"\" mode must be programmed in this mode. Audit will "
			"report FAIL even with \"Smart-Idle\" mode.\n");
		fprintf(stream, "    - Report Warning (with setting) in case of"
			" \"Force-Idle\" mode.\n");
		fprintf(stream, "    - Report FAIL (with incorrect setting) "
			"otherwise.\n");
		fprintf(stream, "  - STANDBY MODE:\n");
		fprintf(stream, "    - Report Pass if set to \"Smart-Standby\" "
			"or \"Smart-Standby Wakeup\" (when available).\n");
		fprintf(stream, "      - Modules featuring \"Smart-Standby "
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
#ifdef SYSCONFIG_AUDIT44XX_DEBUG
#undef dprintf
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkspeed_audit44xx
 * @BRIEF		OMAP4 Clock Speed audit.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in,out]	stream: output file - NULL: no output (silent)
 * @param[in,out]	err_nbr: pointer to return audit error number
 * @param[in,out]	wng_nbr: pointer to return audit warning number
 * @DESCRIPTION		OMAP4 Clock Speed audit.
 *//*------------------------------------------------------------------------ */
int clkspeed_audit44xx(FILE *stream, unsigned int *err_nbr,
	unsigned int *wng_nbr)
{
	mod44xx_id module_id;
	voltdm44xx_id volt_dom_id;
	clock44xx_id src_clk_id;
	int ret;
	opp44xx_id current_opp;
	mod_module_mode mmode;
	double speed_curr = 0.0, speed_por = 0.0, speed_opp50_por = 0.0;
	const char pass[10] = "pass";
	const char fail[10] = "FAIL";
	const char warning1[10] = "warn. (1)";
	const char warning2[10] = "warn. (2)";
	const char warning3[10] = "warn. (3)";
	const char ignore4[10] = "ign. (4)";
	char *status;
	char s_curr[12], s_por[12], s_src[CLOCK44XX_MAX_NAME_LENGTH];
	char mod_name[MOD44XX_MAX_NAME_LENGTH];
	char src_clk_name[CLOCK44XX_MAX_NAME_LENGTH];
	char s_opp[OPP44XX_MAX_NAME_LENGTH] = "ERR";
	char prev_gov[16], prev_gov2[16];

	if (!cpu_is_omap44xx())
		return OMAPCONF_ERR_CPU;
	if ((err_nbr == NULL) || (wng_nbr == NULL))
		return OMAPCONF_ERR_ARG;

	*err_nbr = 0;
	*wng_nbr = 0;

	/* Switch to userspace governor temporarily,
	 * so that OPP cannot change during audit and does not false it.
	 */
	cpufreq_scaling_governor_set("userspace", prev_gov);

	if (stream != NULL) {
		fprintf(stream,
			"|-----------------------------------------------------"
			"--------------------------------------------------"
			"|\n");
		fprintf(stream, "| %-20s | %-21s | %-12s | %-27s | %-9s |\n",
			"  CLOCK SPEED AUDIT", "", "", "     Clock Rate (MHz)",
			"");
		fprintf(stream,
			"| %-20s | %-21s | %-12s | %-12s | %-12s | %-9s |\n",
			"Module", "Source Clock", "OPP", "Current", "Expected",
			"STATUS");
		fprintf(stream,
			"|-----------------------------------------------------"
			"--------------------------------------------------"
			"|\n");
	}
	for (module_id = 0; module_id < OMAP4_MODULE_ID_MAX; module_id++) {
		dprintf("%s():Auditing module %s\n", __func__,
			mod44xx_get_name(module_id, mod_name));
		/* Filter module ID */
		switch (module_id) {
		case OMAP4_RFBI:
			dprintf("%s(): RFBI FCLK not generated by PRCM.\n",
				__func__);
			/* RFBI functional clock not generated by PRCM */
			break;

		case OMAP4_MCSPI1_HL:
		case OMAP4_MCSPI2_HL:
		case OMAP4_MCSPI3_HL:
		case OMAP4_MCSPI4_HL:
		case OMAP4_MMC1_HL:
		case OMAP4_MMC2_HL:
		case OMAP4_MMC3_HL:
		case OMAP4_MMC4_HL:
		case OMAP4_MMC5_HL:
			/* Duplicates of OMAP4_xyz, skip it */
			dprintf("%s(): duplicate of OMAP4_xyz, skip it.\n",
				__func__);
			break;

		case OMAP4_MMU_DSP:
		case OMAP4_DSP_WUGEN:
		case OMAP4_ICONT1:
		case OMAP4_ICONT2:
		case OMAP4_VDMA:
		case OMAP4_IME3:
		case OMAP4_IPE3:
		case OMAP4_ILF3:
		case OMAP4_MC3:
		case OMAP4_CALC3:
		case OMAP4_ECD3:
		case OMAP4_ICONT1_SB:
		case OMAP4_ICONT2_SB:
		case OMAP4_ILF3_SB:
		case OMAP4_IME3_SB:
		case OMAP4_CALC3_SB:
		case OMAP4_IPE3_SB:
		case OMAP4_MC3_SB:
		case OMAP4_ECD3_SB:
		case OMAP4_SL2:
		case OMAP4_P1500:
		case OMAP4_MMU_MPU_M3:
			/*
			 * Part of IVA_HD subsystem
			 * all clocked by same OMAP4_IVAHD_ROOT_CLK clock
			 */
			dprintf("%s(): part of IVA_HD SS, skip it.\n",
				__func__);
			break;

		case OMAP4_CCP2:
		case OMAP4_CSI2_A:
		case OMAP4_CSI2_B:
		case OMAP4_TCTRL:
		case OMAP4_BTE:
		case OMAP4_CBUFF:
		case OMAP4_ISP5:
		case OMAP4_RSZ:
		case OMAP4_SIMCOP:
		case OMAP4_SIMCOP_DMA:
		case OMAP4_SIMCOP_DCT:
		case OMAP4_SIMCOP_VLCDJ:
		case OMAP4_SIMCOP_ROT:
			/*
			 * Part of CAM subsystem
			 * all clocked by same OMAP4_ISS_CLK clock
			 */
			dprintf("%s(): part of CAM SS, skip it.\n",
				__func__);
			break;

		case OMAP4_CRYPTODMA:
		case OMAP4_AES1:
		case OMAP4_AES2:
		case OMAP4_SHA2MD5_1:
		case OMAP4_RNG:
		case OMAP4_DES3DES:
		case OMAP4_PKAEIP29:
		case OMAP4_USIM:
		case OMAP4_WDT1:
		case OMAP4_TIMER12:
		case OMAP4_CUST_EFUSE:
			/*
			 * Secure Modules, not accessible on HS,
			 * not referenced on GP
			 */
			dprintf("%s(): secure module, skip it.\n",
				__func__);
			break;

		case OMAP4_UNIPRO1:
			/* Only present in OMAP4430ES1.0, skip it otherwise */
			if ((cpu_is_omap4430() &&
				(cpu_revision_get() != REV_ES1_0))
				|| cpu_is_omap4460() || cpu_is_omap4470())
				break;

		case OMAP4_DDRPHY:
		case OMAP4_DLL:
			/* Internal.
			 * No need to show it, tend to confuse people.
			 * Showing EMIF speed is sufficient.
			 */
			dprintf("%s(): internal, skip it.\n",
				__func__);
			 break;

		case OMAP4_FSUSBHOST:
			if (cpu_is_omap4470())
				break;
			else
				goto clkspeed_audit44xx_default;

		case OMAP4_BB2D:
			if (!cpu_is_omap4470())
				break;
			else
				goto clkspeed_audit44xx_default;

clkspeed_audit44xx_default:
		default:
			/* init variables */
			status = (char *) ignore4;
			speed_curr = -1.0;
			snprintf(s_curr, 12, "%s", "NOT FOUND");
			snprintf(s_src, 21, "%s", "NOT FOUND");
			strcpy(s_opp, "NOT FOUND");
			speed_por = -2.0;
			speed_opp50_por = -2.0;
			snprintf(s_por, 12, "%s", "NA");

			volt_dom_id = mod44xx_get_voltdm(module_id);
			ret = mod44xx_get_clk_speed(module_id,
				&src_clk_id,
				&current_opp,
				&speed_curr);

			if (src_clk_id != OMAP4_CLOCK_ID_MAX) {
				snprintf(s_src, CLOCK44XX_MAX_NAME_LENGTH, "%s",
					clk44xx_get_name(src_clk_id,
						src_clk_name));
			} else {
				dprintf("%s(): src_clk not found!\n", __func__);
				status = (char *) warning1;
				(*wng_nbr)++;
				goto clkspeed_audit44xx_show;
			}
			if (speed_curr >= 0) {
				mhz2string(speed_curr, s_curr);
			} else {
				dprintf("%s(): speed not found!\n", __func__);
				status = (char *) warning1;
				(*wng_nbr)++;
				goto clkspeed_audit44xx_show;
			}
			if (current_opp != OPP44XX_ID_MAX) {
				voltdm44xx_opp2string(s_opp,
					current_opp, volt_dom_id);
			} else {
				dprintf("%s(): opp not found!\n", __func__);
				status = (char *) warning2;
				(*wng_nbr)++;
				goto clkspeed_audit44xx_show;
			}
			if (ret != 0) {
				dprintf("%s(): src_clk/speed/opp not found!\n",
					__func__);
				status = (char *) warning1;
				(*wng_nbr)++;
				goto clkspeed_audit44xx_show;
			}
			/* Keep only 3 decimals for comparison */
			speed_curr = (int)(speed_curr * 1000.0) /
				1000.0;
			dprintf("%s(): speed=%.3lfMHz\n", __func__, speed_curr);

			/*
			 * Get Plan Of Record (POR) module's functional
			 * source clock speed
			 */
			ret = mod44xx_get_por_clk_speed(module_id,
				current_opp, &speed_por);
			mod44xx_get_mode(module_id, &mmode);
			if ((ret == 0) && (speed_por != -1.0)) {
				mhz2string(speed_por, s_por);
				/*
				 * Keep only 3 decimals for comparison
				 */
				speed_por = (int)(speed_por * 1000.0) /
					1000.0;
				dprintf("%s(): PoR speed=%.3lfMHz\n",
						__func__, speed_por);

				if (speed_curr == speed_por) {
					status = (char *) pass;
					dprintf("%s(): pass!\n",
						__func__);
				} else if (((module_id == OMAP4_AESS) ||
					(module_id == OMAP4_DMIC) ||
					(module_id == OMAP4_L4_ABE)) &&
					(current_opp == OMAP4_OPP100)) {
					/*
					 * From ICS pastry,
					 * ABE is not always following
					 * IVAHD OPP. i.e. it's possible
					 * that VDD_IVA=OPP100 but ABE
					 * stays at OPP50 clock rates.
					 */
					mod44xx_get_por_clk_speed(
						module_id, OMAP4_OPP50,
						&speed_opp50_por);
					if (speed_curr ==
						speed_opp50_por) {
						status = (char *) pass;
						mhz2string(
							speed_opp50_por,
							s_por);
						dprintf("%s(): pass!\n",
							__func__);
					} else {
						dprintf("%s(): FAILED!"
							"\n", __func__);
						status = (char *) fail;
						(*err_nbr)++;
					}
				} else if (mmode == MOD_DISABLED_MODE) {
					/*
					 * may not be a true failure
					 * when module is disabled
					 * (not configured). Does not
					 * impact power.
					 */
					dprintf("%s(): disabled "
						"module.\n",
						__func__);
					status = (char *) warning3;
					(*wng_nbr)++;
				} else {
					dprintf("%s(): FAILED!\n",
						__func__);
					status = (char *) fail;
					(*err_nbr)++;
				}
			} else {
				dprintf("%s(): warning POR speed "
					"not found!\n", __func__);
				status = (char *) warning1;
				(*wng_nbr)++;
			}

clkspeed_audit44xx_show:
			if (stream != NULL)
				fprintf(stream,
					"| %-20s | %-21s | %-12s | %-12s "
					"| %-12s | %-9s |\n",
					mod44xx_get_name(module_id, mod_name),
					s_src, s_opp, s_curr, s_por, status);
		}
	}
	if (stream != NULL) {
		fprintf(stream,
			"|-----------------------------------------------------"
			"--------------------------------------------------"
			"|\n\n");

		fprintf(stream, "NB:\n");
		fprintf(stream, "  (1) Internal error (data not found).\n");
		fprintf(stream, "  (2) OPP not found, could not audit module "
			"rate.\n");
		fprintf(stream, "  (3) Clock rate does no match target rate, "
			"but module is disabled (no power impact).\n");
		fprintf(stream, "  (4) No target clock rate available "
			"(module not used on TI reference platform).\n\n");

		if (*err_nbr == 0)
			fprintf(stream, "SUCCESS! Clock Speed audit "
				"completed with 0 error (%d warning(s))\n\n",
				*wng_nbr);
		else
			fprintf(stream, "FAILED! Clock Speed audit "
				"completed with %d error and %d warning.\n\n",
				*err_nbr, *wng_nbr);
	}

	/* Restore CPUFreq governor */
	cpufreq_scaling_governor_set(prev_gov, prev_gov2);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		audit44xx_sr_avs
 * @BRIEF		audit Smart-Reflex AVS Configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		stream: output file (NULL: no output (silent))
 * @param[in]		sr_id: SR module ID
 *				(use OMAP4_SR_ID_MAX to audit all modules)
 * @param[in]		curr_opp: audit current OPP only (=1) or all OPPs (=0)
 * @param[in,out]	err_nbr: audit error number
 * @param[in,out]	wng_nbr: audit warning number
 * @DESCRIPTION		audit Smart-Reflex AVS Configuration (SR + VP modules)
 *//*------------------------------------------------------------------------ */
int audit44xx_sr_avs(FILE *stream, omap4_sr_module_id sr_id,
	unsigned short curr_opp, unsigned int *err_nbr, unsigned int *wng_nbr)
{
	unsigned int vp_err_nbr = 0, vp_wng_nbr = 0;
	unsigned int sr_err_nbr = 0, sr_wng_nbr = 0;
	opp44xx_id opp;
	double freq_mpu;
	int ret;
	unsigned int row;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	char prev_gov[CPUFREQ_GOV_MAX_NAME_LENGTH];
	char prev_gov2[CPUFREQ_GOV_MAX_NAME_LENGTH];
	char opp_name[OPP44XX_MAX_NAME_LENGTH];
	char *workdir;
	char s[256];
	FILE *fp;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(err_nbr, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(wng_nbr, OMAPCONF_ERR_ARG);


	if (cpu_is_omap4470()) {
		(*wng_nbr) += 1;
		if (stream != NULL)
			fprintf(stream, "SR AVS Golden settings not yet "
			"available, audit cannot be run.\n\n");
		return 0;
	}

	/* Create audit report log file */
	workdir = workdir_get();
	if (workdir != NULL) {
		strcpy(s, workdir);
		strcat(s, "sr_avs_audit_report.txt");
	} else {
		return 0;
	}
	fp = fopen(s, "w+");
	if (fp == NULL) {
		fprintf(stderr, "Could not create %s file!\n\n", s);
		return 0;
	}
	fprintf(fp,
		"OMAPCONF SR AVS Configuration Audit Detailed Log:\n\n");
	omapconf_revision_show(fp);
	chips_info_show(fp, 1);
	release_info_show(fp);

	if (curr_opp == 1) {
		ret = sr44xx_audit(fp, sr_id, &sr_err_nbr, &sr_wng_nbr);
		if (ret != 0) {
			fclose(fp);
			return ret;
		}
		(*err_nbr) += sr_err_nbr;
		(*wng_nbr) += sr_wng_nbr;

		ret = vp44xx_config_audit(fp, (vp44xx_mod_id) sr_id,
			&vp_err_nbr, &vp_wng_nbr);
		if (ret != 0) {
			fclose(fp);
			return ret;
		}
		(*err_nbr) += vp_err_nbr;
		(*wng_nbr) += vp_wng_nbr;

		rewind(fp);
		while ((fgets(s, 256, fp) != NULL) && (s[0] != '|'));
		fputs(s, stream);
		if (stream != NULL) {
			while (fgets(s, 256, fp) != NULL)
				fputs(s, stream);
			fprintf(stream,
				"Audit details saved in %s file.\n",
				"sr_avs_audit_report.txt");
			if (*err_nbr == 0)
				fprintf(stream,
					"\nSUCCESS! SR AVS Configuration audit "
					"completed with 0 error (%u warning(s))"
					".\n\n", *wng_nbr);
			else
				fprintf(stream,
					"\nFAILED! SR AVS Configuration audit "
					"completed with %u error(s) and %u "
					"warning(s).\n\n", *err_nbr, *wng_nbr);
		}

		if (*err_nbr == 0)
			fprintf(fp,
				"\nSUCCESS! SR AVS Configuration audit "
				"completed with 0 error (%u warning(s))"
				".\n\n", *wng_nbr);
		else
			fprintf(fp,
				"\nFAILED! SR AVS Configuration audit "
				"completed with %u error(s) and %u warning(s)"
				".\n\n", *err_nbr, *wng_nbr);
		fclose(fp);
		ret = 0;
		goto audit44xx_sr_avs_end;
	}


	row = 0;
	autoadjust_table_init(table);
	snprintf(table[row][0], TABLE_MAX_ELT_LEN,
		"SR AVS Configuration AUDIT Summary");
	autoadjust_table_strncpy(table, row, 1, "SR Audit STATUS");
	autoadjust_table_strncpy(table, row, 2, "VP Audit STATUS");
	row++;

	/* Save current governor (will be altered by cpufreq_set() call */
	cpufreq_scaling_governor_get(prev_gov);

	for (opp = OMAP4_OPP50; (unsigned int) opp <= cpufreq_opp_nbr_get();
		opp++) {
		sr_err_nbr = 0;
		sr_wng_nbr = 0;
		vp_err_nbr = 0;
		vp_wng_nbr = 0;

		/* Set MPU OPP */
		ret = mod44xx_get_por_clk_speed(OMAP4_MPU, opp, &freq_mpu);
		if (ret != 0) {
			fclose(fp);
			goto audit44xx_sr_avs_end;
		}
		ret = cpufreq_set((unsigned int) (freq_mpu * 1000));
		if (ret != 0) {
			fclose(fp);
			goto audit44xx_sr_avs_end;
		}
		voltdm44xx_opp2string(opp_name, opp, OMAP4_VDD_MPU);
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "At MPU %s",
			opp_name);
		fprintf(fp, "SR AVS Configuration Audit at MPU %s:\n\n",
			opp_name);

		/* Run audit at this OPP */
		ret = sr44xx_audit(fp, sr_id, &sr_err_nbr,
			&sr_wng_nbr);
		if (ret != 0) {
			fclose(fp);
			goto audit44xx_sr_avs_end;
		}
		if (sr_err_nbr == 0)
			snprintf(table[row][1], TABLE_MAX_ELT_LEN,
				"PASS (0 error, %u warning(s))", sr_wng_nbr);
		else
			snprintf(table[row][1], TABLE_MAX_ELT_LEN,
				"FAIL (%u error, %u warning(s))",
				sr_err_nbr, sr_wng_nbr);
		(*err_nbr) += sr_err_nbr;
		(*wng_nbr) += sr_wng_nbr;

		ret = vp44xx_config_audit(fp, (vp44xx_mod_id) sr_id,
			&vp_err_nbr, &vp_wng_nbr);
		if (ret != 0) {
			fclose(fp);
			goto audit44xx_sr_avs_end;
		}
		if (vp_err_nbr == 0)
			snprintf(table[row][2], TABLE_MAX_ELT_LEN,
				"PASS (0 error, %u warning(s))", vp_wng_nbr);
		else
			snprintf(table[row][2], TABLE_MAX_ELT_LEN,
				"FAIL (%u error, %u warning(s))",
				vp_err_nbr, vp_wng_nbr);
		row++;
		(*err_nbr) += vp_err_nbr;
		(*wng_nbr) += vp_wng_nbr;
		fprintf(fp, "\n\n\n");
	}

	/* Report final audit status */
	autoadjust_table_fprint(fp, table, row, 3);
	fprintf(fp, "NB: SR IVA may not have been audited accross all "
		"IVA OPPs (no kernel interface to control IVA OPP "
		"available).\n\n");
	if (stream != NULL) {
		autoadjust_table_fprint(stream, table, row, 3);
		fprintf(stream, "NB: SR IVA may not have been audited accross "
			"all IVA OPPs (no kernel interface to control IVA OPP "
			"available).\n\n");
	}
	if (*err_nbr == 0)
		fprintf(fp, "\nSUCCESS! Full SR AVS Configuration "
			"audit completed with 0 error (%u warning(s))"
			".\n\n", *wng_nbr);
	else
		fprintf(fp, "\nFAILED! Full SR AVS Configuration "
			"audit completed with %u error(s) and %u "
			"warning(s).\n\n", *err_nbr, *wng_nbr);
	fclose(fp);

	if (stream != NULL) {
		fprintf(stream, "Audit details saved in %s file.\n", s);
		if (*err_nbr == 0)
			fprintf(stream, "\nSUCCESS! Full SR AVS Configuration "
				"audit completed with 0 error (%u warning(s))"
				".\n\n", *wng_nbr);
		else
			fprintf(stream, "\nFAILED! Full SR AVS Configuration "
				"audit completed with %u error(s) and %u "
				"warning(s).\n\n", *err_nbr, *wng_nbr);
	}


audit44xx_sr_avs_end:
	/* Restore CPUFreq governor */
	cpufreq_scaling_governor_set(prev_gov, prev_gov2);
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		full_audit44xx
 * @BRIEF		full OMAP4 power configuration audit
 *			(dplls, sysconfig, clkspeed, statdep, avs, pads).
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @DESCRIPTION		full OMAP4 power configuration audit
 *			(dplls, sysconfig, clkspeed, statdep, avs, pads).
 *//*------------------------------------------------------------------------ */
int full_audit44xx(void)
{
	unsigned int dplls_err_nbr = 0, dplls_wng_nbr = 0;
	unsigned int syscfg_err_nbr = 0, syscfg_wng_nbr = 0;
	unsigned int clkspeed_err_nbr = 0, clkspeed_wng_nbr = 0;
	unsigned int statdep_err_nbr = 0, statdep_wng_nbr = 0;
	unsigned int avs_err_nbr = 0, avs_wng_nbr = 0;
	int pad_violation_count;
	unsigned int err_nbr = 0, wng_nbr = 0;
	unsigned int row = 0;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	char *workdir;
	char s[256];
	FILE *fp;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	/* Create audit report log file */
	workdir = workdir_get();
	if (workdir != NULL) {
		strcpy(s, workdir);
		strcat(s, "full_audit_report.txt");
	} else {
		return 0;
	}
	fp = fopen(s, "w+");
	if (fp == NULL) {
		fprintf(stderr, "Could not create %s file!\n\n", s);
		return 0;
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

	audit44xx_dpll(fp, DPLL44XX_ID_MAX, OPP44XX_ID_MAX,
			0, &dplls_err_nbr, &dplls_wng_nbr);
	fputs("\n\n\n", fp);
	snprintf(table[row][0], TABLE_MAX_ELT_LEN,
		"DPLLs Configuration Audit");
	if (dplls_err_nbr == 0)
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"PASS (0 error, %u warning(s))", dplls_wng_nbr);
	else
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"FAIL (%u error(s), %u warning(s))",
			dplls_err_nbr, dplls_wng_nbr);
	row++;
	err_nbr += dplls_err_nbr;
	wng_nbr += dplls_wng_nbr;

	sysconfig_audit44xx(fp,
		&syscfg_err_nbr, &syscfg_wng_nbr);
	fputs("\n\n\n", fp);
	snprintf(table[row][0], TABLE_MAX_ELT_LEN,
		"SYSCONFIG IP Registers Audit");
	if (syscfg_err_nbr == 0)
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"PASS (0 error, %u warning(s))", syscfg_wng_nbr);
	else
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"FAIL (%u error(s), %u warning(s))",
			syscfg_err_nbr, syscfg_wng_nbr);
	row++;
	err_nbr += syscfg_err_nbr;
	wng_nbr += syscfg_wng_nbr;

	clkspeed_audit44xx(fp,
		&clkspeed_err_nbr, &clkspeed_wng_nbr);
	fputs("\n\n\n", fp);
	snprintf(table[row][0], TABLE_MAX_ELT_LEN,
		"Clock Speed Audit");
	if (clkspeed_err_nbr == 0)
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"PASS (0 error, %u warning(s))", clkspeed_wng_nbr);
	else
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"FAIL (%u error(s), %u warning(s))",
			clkspeed_err_nbr, clkspeed_wng_nbr);
	row++;
	err_nbr += clkspeed_err_nbr;
	wng_nbr += clkspeed_wng_nbr;

	statdep44xx_audit(fp,
		&statdep_err_nbr, &statdep_wng_nbr);
	fputs("\n\n\n", fp);
	snprintf(table[row][0], TABLE_MAX_ELT_LEN,
		"Static Dependencies Audit");
	if (statdep_err_nbr == 0)
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"PASS (0 error, %u warning(s))", statdep_wng_nbr);
	else
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"FAIL (%u error(s), %u warning(s))",
			statdep_err_nbr, statdep_wng_nbr);
	row++;
	err_nbr += statdep_err_nbr;
	wng_nbr += statdep_wng_nbr;

	audit44xx_sr_avs(fp, OMAP4_SR_ID_MAX, 0,
		&avs_err_nbr, &avs_wng_nbr);
	fputs("\n\n\n", fp);
	snprintf(table[row][0], TABLE_MAX_ELT_LEN,
		"SR AVS Audit");
	if (avs_err_nbr == 0)
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"PASS (0 error, %u warning(s))", avs_wng_nbr);
	else
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"FAIL (%u error(s), %u warning(s))",
			avs_err_nbr, avs_wng_nbr);
	row++;
	err_nbr += avs_err_nbr;
	wng_nbr += avs_wng_nbr;

	pad_violation_count = pads44xx_audit(fp);
	fputs("\n\n\n", fp);
	snprintf(table[row][0], TABLE_MAX_ELT_LEN,
		"IO PAD Audit");
	if (pad_violation_count < 0) {
		wng_nbr++;
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"ABORTED (0 error, 1 warning(s))");
	} else if (pad_violation_count == 0) {
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"PASS (0 error, 0 warning(s))");
	} else {
		err_nbr++;
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"FAIL (%u error(s), 0 warning(s))",
			pad_violation_count);
	}
	row++;

	autoadjust_table_fprint(stdout, table, row, 2);
	autoadjust_table_fprint(fp, table, row, 2);
	printf("Audit details saved in %s file.\n\n\n", s);
	if (err_nbr == 0) {
		sprintf(s, "SUCCESS! Full Power Configuration Audit "
			"completed with 0 error (%u warning(s))\n\n", wng_nbr);
	} else {
		sprintf(s, "FAILED! Full Power Configuration Audit "
			"completed with %u error(s) and %u warning(s).\n\n",
			err_nbr, wng_nbr);
	}
	fputs(s, stdout);
	fputs(s, fp);

	fclose(fp);
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		audit44xx_main
 * @BRIEF		OMAP4 audit menu
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		OMAP4 audit menu
 *//*------------------------------------------------------------------------ */
int audit44xx_main(int argc, char *argv[])
{
	unsigned int err_nbr = 0, wng_nbr = 0;
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (argc == 1) {
		help(HELP_AUDIT);
		ret = 0;
	} else if (strcmp(argv[1], "dpll") == 0) {
		ret = audit44xx_dpll_main(argc - 2, argv + 2);
	} else if (strcmp(argv[1], "perf") == 0) {
		ret = audit_performances_main(argc - 2, argv + 2);
	} else if (argc == 2) {
		if (strcmp(argv[1], "full") == 0) {
			ret = full_audit44xx();
		} else if (strcmp(argv[1], "sysconfig") == 0) {
			ret = sysconfig_audit44xx(stdout,
				&err_nbr, &wng_nbr);
		} else if (strcmp(argv[1], "clkspeed") == 0) {
			ret = clkspeed_audit44xx(stdout,
				&err_nbr, &wng_nbr);
		} else if (strcmp(argv[1], "statdep") == 0) {
			ret = statdep44xx_audit(stdout,
				&err_nbr, &wng_nbr);
		} else if (strcmp(argv[1], "avs") == 0) {
			ret = audit44xx_sr_avs(stdout, OMAP4_SR_ID_MAX, 1,
				&err_nbr, &wng_nbr);
		} else if (strcmp(argv[1], "pads") == 0) {
			ret = pads44xx_audit(stdout);
		} else {
			ret = uc_audit44xx_main(argc, argv);
		}
	} else if ((argc == 3) &&
		(strcmp(argv[1], "avs") == 0)) {
		if (strcmp(argv[2], "mpu") == 0) {
			ret = audit44xx_sr_avs(stdout, OMAP4_SR_MPU, 1,
				&err_nbr, &wng_nbr);
		} else if (strcmp(argv[2], "iva") == 0) {
			ret = audit44xx_sr_avs(stdout, OMAP4_SR_IVA, 1,
				&err_nbr, &wng_nbr);
		} else if (strcmp(argv[2], "core") == 0) {
			ret = audit44xx_sr_avs(stdout, OMAP4_SR_CORE, 1,
				&err_nbr, &wng_nbr);
		} else if (strcmp(argv[2], "full") == 0) {
			ret = audit44xx_sr_avs(stdout, OMAP4_SR_ID_MAX, 0,
				&err_nbr, &wng_nbr);
		} else {
			help(HELP_AUDIT);
			ret = 0;
		}
	} else if ((argc == 3) &&
		(strcmp(argv[2], "full_log") == 0)) {
		ret = uc_audit44xx_main(argc, argv);
	} else {
		help(HELP_AUDIT);
		ret = 0;
	}

	return ret;
}
