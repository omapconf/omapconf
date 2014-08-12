/*
 *
 * @Component			OMAPCONF
 * @Filename			main_dra7xx.c
 * @Description			OMAPCONF DRA7 Main file
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


#include <main_dra7xx.h>
#include <lib_dra7xx.h>
#include <voltdm_dra7xx.h>
#include <dpll_dra7xx.h>
#include <ctt_dra7xx.h>
#include <mcasp_dra7xx.h>
#include <lib.h>
#include <help.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <cpuinfo.h>
#include <prcm_dra7xx.h>
#include <temperature.h>
#include <opp.h>
#include <audit_dra7xx.h>
#include <audioic/tlv320aic3x.h>
#include <crossbar.h>
#include <abb7xx.h>
#include <statcoll/sci_swcapture_dra.h>


/* #define MAIN_DRA7XX_DEBUG */
#ifdef MAIN_DRA7XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main_dra7xx_dump
 * @BRIEF		dump some DRA7 registers, which category is found in
 *			argv
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		argc: number of arguments
 * @param[in]		argv: argument(s)
 * @DESCRIPTION		dump some DRA7 registers, which category is found in
 *			argv
 *//*------------------------------------------------------------------------ */
int main_dra7xx_dump(int argc, char *argv[])
{
	dpll_dra7xx_id dpll_id;
	CHECK_NULL_ARG(argv, OMAPCONF_ERR_ARG);

	if (argc < 1) {
		help(HELP_USAGE);
		return OMAPCONF_ERR_ARG;
	} else if (strcmp(argv[0], "prcm") == 0) {
		if (argc == 1)
			return prcm_dra7xx_dump(NULL);
		else if (argc == 2)
			return prcm_dra7xx_dump(argv[1]);
		else
			return err_arg_too_many_msg_show(HELP_PRCM);
	} else if (strcmp(argv[0], "dpll") == 0) {
		if (argc == 1)
			return dpll_dra7xx_dump(stdout, DPLL_DRA7XX_ID_MAX);
		else if (argc == 2) {
			if (strcmp(argv[1], "all") == 0)
				dpll_id = DPLL_DRA7XX_ID_MAX;
			else {
				dpll_id = dpll_dra7xx_s2id(argv[1]);
				if (dpll_id == DPLL_DRA7XX_ID_MAX)
					return err_arg_msg_show(HELP_DPLL);
			}
			return dpll_dra7xx_dump(stdout, dpll_id);
		}
		else
			return err_arg_too_many_msg_show(HELP_PRCM);
	} else if (strncmp(argv[0], "mcasp", 5) == 0) {
		if (argc == 1) {
			return dra7xx_mcasp_dumpregs(stdout, argc, argv);
		} else {
			return err_arg_too_many_msg_show(HELP_MCASP);
		}
	} else if (strcmp(argv[0], "audioic") == 0) {
		if (argc == 1 || argc == 3)
			return tlv320aic3x_dumpregs(argc, argv);
		else
			return err_arg_too_many_msg_show(HELP_AUDIOIC);
	} else if (!strcmp(argv[0], "crossbar")) {
		if (argc == 1 || argc == 2 || argc == 3) {
			return dra7_crossbar_dump_main(argc - 1, argv + 1);
		} else {
			return err_arg_too_many_msg_show(HELP_CROSSBAR);
		}
	} else if (strcmp(argv[0], "abb") == 0) {
		if (argc == 1)
			return abb7xx_dump(stdout);
		else
			return err_arg_too_many_msg_show(HELP_ABB);
	} else {
		return err_unknown_argument_msg_show(argv[0]);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main_dra7xx_legacy
 * @BRIEF		OMAP5 LEGACY functions main entry point
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		OMAP5 LEGACY functions main entry point
 *//*------------------------------------------------------------------------ */
int main_dra7xx_legacy(int argc, char *argv[])
{
	int ret;

	if ((argc == 2) && (strcmp(argv[0], "prcm") == 0) &&
		(strcmp(argv[1], "dump") == 0)) {
		ret = prcm_dra7xx_dump(NULL);
	} else if ((argc == 3) && (strcmp(argv[0], "prcm") == 0) &&
		(strcmp(argv[1], "dump") == 0)) {
		ret = prcm_dra7xx_dump(argv[2]);
	} else if (strcmp(argv[0], "dpll") == 0) {
		ret = dpll_dra7xx_main(argc - 1, argv + 1);
	} else if (strcmp(argv[0], "ctt") == 0) {
		ret = ctt_dra7xx_main(argc - 1, argv + 1);
	} else if (strncmp(argv[0], "mcasp", 5) == 0) {
		return dra7xx_mcasp_main(argc, argv);
	} else if (strcmp(argv[0], "audioic") == 0) {
		ret = tlv320aic3x_main(argc - 1, argv + 1);
	} else {
		ret = err_unknown_argument_msg_show(argv[0]);
		goto main_dra7xx_legacy_end;
	}

	fprintf(stderr, "\n\n### WARNING ###: deprecated command/options. "
		"See 'omapconf --help'.\n\n");

main_dra7xx_legacy_end:
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main_dra7xx_show
 * @BRIEF		show some DRA7 information,
 *			which category is found in argv
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG in case of incorrect format
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		show some DRA7 information,
 *			which category is found in argv
 *//*------------------------------------------------------------------------ */
int main_dra7xx_show(int argc, char *argv[])
{
	CHECK_NULL_ARG(argv, OMAPCONF_ERR_ARG);

	if (argc < 1) {
		help(HELP_USAGE);
		return OMAPCONF_ERR_ARG;
	} else if (strcmp(argv[0], "hwtemp") == 0) {
		if (argc == 1) {
			return hwtemp_sensor_show(stdout, "all");
		} else if (argc == 2) {
			if (strcmp(argv[1], "all") == 0)
				return hwtemp_sensor_show(stdout, argv[1]);
			else if (hwtemp_sensor_is_available(argv[1]) != 0)
				return hwtemp_sensor_show(stdout, argv[1]);
			else
				return err_arg_msg_show(HELP_HWTEMPERATURE);
		} else {
			return err_arg_too_many_msg_show(HELP_HWTEMPERATURE);
		}
	} else if (strcmp(argv[0], "temp") == 0) {
		if (argc == 1) {
			return temp_sensor_show(stdout, "all");
		} else if (argc == 2) {
			if (strcmp(argv[1], "all") == 0)
				return temp_sensor_show(stdout, argv[1]);
			else if (hwtemp_sensor_is_available(argv[1]) != 0)
				return temp_sensor_show(stdout, argv[1]);
			else
				return err_arg_msg_show(HELP_TEMPERATURE);
		} else {
			return err_arg_too_many_msg_show(HELP_TEMPERATURE);
		}
	} else if (strcmp(argv[0], "dpll") == 0) {
		if (argc == 1) {
			return dpll_dra7xx_show(stdout);
		} else if (argc == 2) {
			if (strcmp(argv[1], "cfg") == 0)
				return dpll_dra7xx_show(stdout);
			else
				return err_arg_msg_show(HELP_DPLL);
		} else {
			return err_arg_too_many_msg_show(HELP_DPLL);
		}
	} else if (strcmp(argv[0], "opp") == 0) {
		if (argc == 1)
			return opp_show(stdout);
		else
			return err_arg_too_many_msg_show(HELP_SOC_OPP);
	} else if (strncmp(argv[0], "mcasp", 5) == 0) {
		if (argc == 1) {
			return dra7xx_mcasp_show(stdout, argc, argv);
		} else {
			return err_arg_too_many_msg_show(HELP_MCASP);
		}
	} else if (strcmp(argv[0], "abb") == 0) {
		if (argc == 1)
			return abb7xx_config_show(stdout);
		else
			return err_arg_too_many_msg_show(HELP_ABB);
	} else {
		return err_unknown_argument_msg_show(argv[0]);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main_dra7xx_dpll_audit
 * @BRIEF		analyze command-line arguments & call DPLL audit with
 *			selected options
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_INTERNAL
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		analyze command-line arguments & call DPLL audit with
 *			selected options
 *//*------------------------------------------------------------------------ */
int main_dra7xx_dpll_audit(int argc, char *argv[])
{
	int ret = 0;
	dpll_dra7xx_id dpll_id;
	opp_dra7xx_id opp_id;
	unsigned int err_nbr, wng_nbr;
	unsigned short pos_opp_id, pos_dpll_id, curr_opp;

	CHECK_NULL_ARG(argv, OMAPCONF_ERR_ARG);

	/* Retrieve user options */
	dprintf("%s(): argc=%u\n", __func__, argc);
	#ifdef MAIN_DRA7XX_DEBUG
	for (curr_opp = 0; curr_opp < argc; curr_opp++) {
		dprintf("%s(): argv[%u]=%s\n", __func__,
			curr_opp, argv[curr_opp]);
	}
	#endif

	if (argc == 0) {
		/* Audit all DPLLs at current OPP by default */
		dpll_id = DPLL_DRA7XX_ID_MAX;
		opp_id = OPP_DRA7XX_ID_MAX;
		curr_opp = 1;
		goto main_dra7xx_dpll_audit_run;
	} else if (argc == 2) {
		if (strcmp(argv[0], "-d") == 0) {
			opp_id = OPP_DRA7XX_ID_MAX;
			curr_opp = 1;
			dpll_id = dpll_dra7xx_s2id(argv[1]);
			if (dpll_id == DPLL_DRA7XX_ID_MAX) {
				if (strcmp(argv[1], "all") == 0)
					dpll_id = DPLL_DRA7XX_ID_MAX;
				else
					goto main_dra7xx_dpll_audit_err_arg;
			}
			goto main_dra7xx_dpll_audit_run;
		} else if (strcmp(argv[0], "-o") == 0) {
			dpll_id = DPLL_DRA7XX_ID_MAX;
			curr_opp = 1;
			opp_id = opp_dra7xx_s2id(argv[1]);
			if (opp_id == OPP_DRA7XX_ID_MAX) {
				if (strcmp(argv[1], "all") == 0) {
					opp_id = OPP_DRA7XX_ID_MAX;
					curr_opp = 0;
				} else {
					goto main_dra7xx_dpll_audit_err_arg;
				}
			}
			goto main_dra7xx_dpll_audit_run;
		} else {
			goto main_dra7xx_dpll_audit_err_arg;
		}
	} else if (argc == 4) {
		curr_opp = 1;
		if (strcmp(argv[0], "-d") == 0)
			pos_dpll_id = 1;
		else if (strcmp(argv[2], "-d") == 0)
			pos_dpll_id = 3;
		else
			goto main_dra7xx_dpll_audit_err_arg;
		dpll_id = dpll_dra7xx_s2id(argv[pos_dpll_id]);
		if (dpll_id == DPLL_DRA7XX_ID_MAX) {
			if (strcmp(argv[pos_dpll_id], "all") == 0)
				dpll_id = DPLL_DRA7XX_ID_MAX;
			else
				goto main_dra7xx_dpll_audit_err_arg;
		}

		if (strcmp(argv[0], "-o") == 0)
			pos_opp_id = 1;
		else if (strcmp(argv[2], "-o") == 0)
			pos_opp_id = 3;
		else
			goto main_dra7xx_dpll_audit_err_arg;
		opp_id = opp_dra7xx_s2id(argv[pos_opp_id]);
		if (opp_id == OPP_DRA7XX_ID_MAX) {
			if (strcmp(argv[pos_opp_id], "all") == 0) {
				opp_id = OPP_DRA7XX_ID_MAX;
				curr_opp = 0;
			} else {
				goto main_dra7xx_dpll_audit_err_arg;
			}
		}
		goto main_dra7xx_dpll_audit_run;
	} else {
		goto main_dra7xx_dpll_audit_err_arg;
	}

main_dra7xx_dpll_audit_run:
	dprintf("%s(): dpll_id=%s, opp_id=%s curr_opp=%u\n", __func__,
		dpll_dra7xx_name_get(dpll_id),
		opp_dra7xx_name_get(opp_id), curr_opp);

	ret = audit_dra7xx_dpll(stdout, dpll_id, opp_id, curr_opp,
		&err_nbr, &wng_nbr);

	goto main_dra7xx_dpll_audit_end;

main_dra7xx_dpll_audit_err_arg:
	help(HELP_AUDIT);
	ret = OMAPCONF_ERR_ARG;

main_dra7xx_dpll_audit_end:
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main_dra7xx_audit
 * @BRIEF		analyze command-line arguments & select relevant
 *			audit function
 *			to call
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_INTERNAL
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		analyze command-line arguments & select relevant
 *			audit function to call
 *//*------------------------------------------------------------------------ */
int main_dra7xx_audit(int argc, char *argv[])
{
	int ret = 0;

	CHECK_NULL_ARG(argv, OMAPCONF_ERR_ARG);

	if (argc == 0) {
		goto main_dra7xx_audit_err_arg;
	} else if (strcmp(argv[0], "dpll") == 0) {
		ret = main_dra7xx_dpll_audit(argc - 1, argv + 1);
	} else if (!strcmp(argv[0], "crossbar")) {
		ret = dra7_crossbar_audit_main(argc - 1, argv + 1);
	} else {
		goto main_dra7xx_audit_err_arg;
	}
	goto main_dra7xx_audit_end;

main_dra7xx_audit_err_arg:
	help(HELP_AUDIT);
	ret = 0;

main_dra7xx_audit_end:
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main_dra7xx_export
 * @BRIEF		Export OMAP configuration into format and destination
 *			provided in argv.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		Export OMAP configuration into format and destination
 *			provided in argv.
 *//*------------------------------------------------------------------------ */
static int main_dra7xx_export(int argc, char *argv[])
{
	if (strcmp(argv[0], "ctt") == 0) {
		if (argc == 1)
			return ctt_dra7xx_dump();
		else if (argc == 2)
			return ctt_dra7xx_rd1_export(argv[1]);
		else
			return err_arg_too_many_msg_show(HELP_EXPORT);
	} else {
		return err_arg_msg_show(HELP_EXPORT);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main_dra7xx_set
 * @BRIEF		set some DRA7 item, which category is found in argv
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		argc: number of arguments
 * @param[in]		argv: argument(s)
 * @DESCRIPTION		set some DRA7 settings, which category is found in argv
 *//*------------------------------------------------------------------------ */
static int main_dra7xx_set(int argc, char *argv[])
{
	voltdm_dra7xx_id vdd_id;
	double volt;

	if (argc < 1) {
		return err_arg_missing_msg_show(HELP_CATEGORY_MAX);
	} else if (strcmp(argv[0], "volt") == 0) {
		if (argc < 3) {
			return err_arg_missing_msg_show(HELP_VOLT);
		} else if (argc == 3) {
			lowercase(argv[1]);
			if (strcmp(argv[1], "mpu") == 0)
				vdd_id = VDD_DRA7XX_MPU;
			else if (strcmp(argv[1], "iva") == 0)
				vdd_id = VDD_DRA7XX_IVA;
			else if (strcmp(argv[1], "core") == 0)
				vdd_id = VDD_DRA7XX_CORE;
			else if (strcmp(argv[1], "dspeve") == 0)
				vdd_id = VDD_DRA7XX_DSPEVE;
			else if (strcmp(argv[1], "gpu") == 0)
				vdd_id = VDD_DRA7XX_GPU;
			else
				return err_arg_msg_show(HELP_VOLT);

			if (sscanf(argv[2], "%lf", &volt) != 1)
				return err_arg_msg_show(HELP_VOLT);

			return lib_dra7xx_voltage_set(vdd_id, volt);
		} else {
			return err_arg_too_many_msg_show(HELP_VOLT);
		}
	} else {
		return err_arg_msg_show(HELP_CATEGORY_MAX);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main_dra7xx
 * @BRIEF		DRA7 functions main entry point
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		DRA7 functions main entry point.
 *//*------------------------------------------------------------------------ */
int main_dra7xx(int argc, char *argv[])
{
	int ret = 0;

	/* Check CPU */
	if (!cpu_is_dra7xx()) {
		ret = OMAPCONF_ERR_CPU;
		goto main_dra7xx_end;
	}

	if (argc < 1)
		goto main_dra7xx_err_arg;

	/* Initializations */
	dpll_dra7xx_init();

	if (strcmp(argv[0], "dump") == 0)
		ret = main_dra7xx_dump(argc - 1, argv + 1);
	else if (strcmp(argv[0], "show") == 0)
		ret = main_dra7xx_show(argc - 1, argv + 1);
	else if (strcmp(argv[0], "export") == 0)
		ret = main_dra7xx_export(argc - 1, argv + 1);
	else if (strcmp(argv[0], "audit") == 0)
		ret = main_dra7xx_audit(argc - 1, argv + 1);
	else if (strcmp(argv[0], "set") == 0)
		ret = main_dra7xx_set(argc - 1, argv + 1);
	else if (strcmp(argv[0], "trace") == 0)
        ret = statcoll_main_dra(argc - 1, argv + 1);
	else
		ret = main_dra7xx_legacy(argc, argv);

	goto main_dra7xx_end;

main_dra7xx_err_arg:
	help(HELP_ALL);
	ret = OMAPCONF_ERR_ARG;

main_dra7xx_end:
	/* Deinitializations */
	dpll_dra7xx_free();

	return ret;
}
