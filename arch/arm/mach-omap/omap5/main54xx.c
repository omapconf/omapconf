/*
 *
 * @Component			OMAPCONF
 * @Filename			main54xx.c
 * @Description			OMAPCONF OMAP5 Main file
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


#include <main54xx.h>
#include <lib54xx.h>
#include <lib.h>
#include <help.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <cpuinfo.h>
#include <prcm54xx.h>
#include <sr54xx.h>
#include <dpll54xx.h>
#include <voltdm54xx.h>
#include <module.h>
#include <audit54xx.h>
#include <ctrlmod54xx.h>
#include <temp54xx.h>
#include <hwtemp54xx.h>
#include <hwobs54xx.h>
#include <abb54xx.h>
#include <emif54xx.h>
#include <clkdm_dependency54xx.h>
#include <abe54xx.h>
#include <twl6040.h>
#include <twl603x.h>
#include <ctt54xx.h>
#include <audit.h>
#include <timestamp_32k.h>
#include <sci_swcapture.h>
#include <temperature.h>
#include <opp.h>


/* #define MAIN54XX_DEBUG */
#ifdef MAIN54XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


#define PERF_TRACE54XX_DEFAULT_CAPTURE_TIME	10 /* second */
#define PERF_TRACE54XX_DEFAULT_DELAY_TIME	0 /* second */
#define PERF_TRACE54XX_DEFAULT_SAMPLING_RATE	(double) 0.1 /* second */
#define PERF_TRACE54XX_MIN_SAMPLING_RATE	(double) 0.1 /* second */


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sigkill_handler
 * @BRIEF		catch kill signal
 * @DESCRIPTION		catch kill signal
 *//*------------------------------------------------------------------------ */
void sigkill_handler(int sigID, siginfo_t *siginfo, void *context)
{
	/* just to remove "unused parameter" warnings ... */
	sigID = sigID;
	siginfo = siginfo;
	context = context;

	dprintf("Received kill signal %d\n", sigID);
	sci_killhandler();
	exit(0);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main54xx_dpll_audit
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
int main54xx_dpll_audit(int argc, char *argv[])
{
	int ret = 0;
	dpll54xx_id dpll_id;
	opp54xx_id opp_id;
	unsigned int err_nbr, wng_nbr;
	unsigned short pos_opp_id, pos_dpll_id, curr_opp;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(argv, OMAPCONF_ERR_ARG);


	/* Retrieve user options */
	dprintf("%s(): argc=%u\n", __func__, argc);
	#ifdef MAIN54XX_DEBUG
	for (curr_opp = 0; curr_opp < argc; curr_opp++) {
		dprintf("%s(): argv[%u]=%s\n", __func__,
			curr_opp, argv[curr_opp]);
	}
	#endif

	if (argc == 0) {
		/* Audit all DPLLs at current OPP by default */
		dpll_id = DPLL54XX_ID_MAX;
		opp_id = OPP54XX_ID_MAX;
		curr_opp = 1;
		goto main54xx_dpll_audit_run;
	} else if (argc == 2) {
		if (strcmp(argv[0], "-d") == 0) {
			opp_id = OPP54XX_ID_MAX;
			curr_opp = 1;
			dpll_id = dpll54xx_s2id(argv[1]);
			if (dpll_id == DPLL54XX_ID_MAX) {
				if (strcmp(argv[1], "all") == 0)
					dpll_id = DPLL54XX_ID_MAX;
				else
					goto main54xx_dpll_audit_err_arg;
			}
			goto main54xx_dpll_audit_run;
		} else if (strcmp(argv[0], "-o") == 0) {
			dpll_id = DPLL54XX_ID_MAX;
			curr_opp = 1;
			opp_id = opp54xx_s2id(argv[1]);
			if (opp_id == OPP54XX_ID_MAX) {
				if (strcmp(argv[1], "all") == 0) {
					opp_id = OPP54XX_ID_MAX;
					curr_opp = 0;
				} else {
					goto main54xx_dpll_audit_err_arg;
				}
			}
			goto main54xx_dpll_audit_run;
		} else {
			goto main54xx_dpll_audit_err_arg;
		}
	} else if (argc == 4) {
		curr_opp = 1;
		if (strcmp(argv[0], "-d") == 0)
			pos_dpll_id = 1;
		else if (strcmp(argv[2], "-d") == 0)
			pos_dpll_id = 3;
		else
			goto main54xx_dpll_audit_err_arg;
		dpll_id = dpll54xx_s2id(argv[pos_dpll_id]);
		if (dpll_id == DPLL54XX_ID_MAX) {
			if (strcmp(argv[pos_dpll_id], "all") == 0)
				dpll_id = DPLL54XX_ID_MAX;
			else
				goto main54xx_dpll_audit_err_arg;
		}

		if (strcmp(argv[0], "-o") == 0)
			pos_opp_id = 1;
		else if (strcmp(argv[2], "-o") == 0)
			pos_opp_id = 3;
		else
			goto main54xx_dpll_audit_err_arg;
		opp_id = opp54xx_s2id(argv[pos_opp_id]);
		if (opp_id == OPP54XX_ID_MAX) {
			if (strcmp(argv[pos_opp_id], "all") == 0) {
				opp_id = OPP54XX_ID_MAX;
				curr_opp = 0;
			} else {
				goto main54xx_dpll_audit_err_arg;
			}
		}
		goto main54xx_dpll_audit_run;
	} else {
		goto main54xx_dpll_audit_err_arg;
	}

main54xx_dpll_audit_run:
	dprintf("%s(): dpll_id=%s, opp_id=%s curr_opp=%u\n", __func__,
		dpll54xx_name_get(dpll_id),
		opp54xx_name_get(opp_id), curr_opp);

	ret = audit54xx_dpll(stdout, dpll_id, opp_id, curr_opp,
		&err_nbr, &wng_nbr);

	goto main54xx_dpll_audit_end;

main54xx_dpll_audit_err_arg:
	help(HELP_AUDIT);
	ret = OMAPCONF_ERR_ARG;

main54xx_dpll_audit_end:
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main54xx_audit
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
int main54xx_audit(int argc, char *argv[])
{
	int ret = 0;
	unsigned int err_nbr, wng_nbr;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(argv, OMAPCONF_ERR_ARG);

	if (argc == 0) {
		goto main54xx_audit_err_arg;
	} else if (strcmp(argv[0], "dpll") == 0) {
		ret = main54xx_dpll_audit(argc - 1, argv + 1);
	} else if (strcmp(argv[0], "clkspeed") == 0) {
		if (argc == 1)
			ret = module_clk_rate_audit(
				stdout, &err_nbr, &wng_nbr);
		else
			goto main54xx_audit_err_arg;
	} else if (strcmp(argv[0], "io") == 0) {
		ret = ctrlmod54xx_io_audit(stdout, &err_nbr, &wng_nbr);
	} else if (strcmp(argv[0], "sysconfig") == 0) {
		ret = module_sysconfig_audit(stdout, &err_nbr, &wng_nbr);
	} else if (strcmp(argv[0], "statdep") == 0) {
		ret = clkdmdep54xx_audit(stdout, &err_nbr, &wng_nbr);
	} else if (strcmp(argv[0], "perf") == 0) {
		ret = audit_performances_main(argc - 1, argv + 1);
	} else if (strcmp(argv[0], "full") == 0) {
		if (argc == 1) {
			ret = audit54xx_full(stdout, NULL, &err_nbr, &wng_nbr);
		} else if (argc == 2) {
			ret = err_arg_missing_msg_show(HELP_AUDIT);
		} else if (argc == 3) {
			if (strcmp(argv[1], "-f") == 0)
				ret = audit54xx_full(
					stdout, argv[2], &err_nbr, &wng_nbr);
			else
				ret = err_arg_msg_show(HELP_AUDIT);
		} else {
			ret = err_arg_too_many_msg_show(HELP_AUDIT);
		}
	} else {
		goto main54xx_audit_err_arg;
	}
	goto main54xx_audit_end;

main54xx_audit_err_arg:
	help(HELP_AUDIT);
	ret = 0;

main54xx_audit_end:
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main54xx_dump
 * @BRIEF		dump some OMAP5 registers, which category is found in
 *			argv
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		argc: number of arguments
 * @param[in]		argv: argument(s)
 * @DESCRIPTION		dump some OMAP5 registers, which category is found in
 *			argv
 *//*------------------------------------------------------------------------ */
int main54xx_dump(int argc, char *argv[])
{
	dpll54xx_id dpll_id;
	int ret;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(argv, OMAPCONF_ERR_ARG);

	if (argc < 1) {
		help(HELP_USAGE);
		return OMAPCONF_ERR_ARG;
	} else if (strcmp(argv[0], "prcm") == 0) {
		if (argc == 1)
			return prcm54xx_dump(NULL);
		else if (argc == 2)
			return prcm54xx_dump(argv[1]);
		else
			return err_arg_too_many_msg_show(HELP_PRCM);
	} else if (strcmp(argv[0], "emif") == 0) {
		if (argc == 1) {
			ret = emif54xx_dump(stdout, EMIF54XX_EMIF1);
			ret |= emif54xx_dump(stdout, EMIF54XX_EMIF2);
			return ret;
		} else {
			return err_arg_too_many_msg_show(HELP_EMIF);
		}
	} else if (strcmp(argv[0], "abe") == 0) {
		if (argc == 1) {
			return prcm54xx_dump("abe");
		} else {
			return err_arg_too_many_msg_show(HELP_ABE);
		}
	} else if (strcmp(argv[0], "audioic") == 0) {
		if (argc == 1) {
			return twl6040_dumpregs();
		} else {
			return err_arg_too_many_msg_show(HELP_AUDIOIC);
		}
	} else if (strcmp(argv[0], "pmic") == 0) {
		if (argc == 1) {
			return twl603x_dumpregs(stdout);
		} else {
			return err_arg_too_many_msg_show(HELP_PMIC);
		}
	} else if (strcmp(argv[0], "dpll") == 0) {
		if (argc == 1) {
			return dpll54xx_dump(stdout, DPLL54XX_ID_MAX);
		} else if (argc == 2) {
			if (strcmp(argv[1], "all") == 0) {
				dpll_id = DPLL54XX_ID_MAX;
			} else {
				dpll_id = dpll54xx_s2id(argv[1]);
				if (dpll_id == DPLL54XX_ID_MAX)
					return err_arg_msg_show(HELP_DPLL);
			}
			return dpll54xx_dump(stdout, dpll_id);
		} else {
			return err_arg_too_many_msg_show(HELP_DPLL);
		}
	} else if (strcmp(argv[0], "ctrlmod") == 0) {
		if (argc == 1) {
			return ctrlmod54xx_dump(stdout, CTRLMOD54XX_MODS_COUNT);
		} else if (argc == 2) {
			if (strcmp(argv[1], "all") == 0)
				return ctrlmod54xx_dump(stdout,
					CTRLMOD54XX_MODS_COUNT);
			else if (strcmp(argv[1], "core") == 0)
				return ctrlmod54xx_dump(stdout,
					CTRLMOD54XX_CTRL_MODULE_CORE);
			else if (strcmp(argv[1], "core_pad") == 0)
				return ctrlmod54xx_dump(stdout,
					CTRLMOD54XX_CTRL_MODULE_CORE_PAD);
			else if (strcmp(argv[1], "wkup") == 0)
				return ctrlmod54xx_dump(stdout,
					CTRLMOD54XX_CTRL_MODULE_WKUP);
			else if (strcmp(argv[1], "wkup_pad") == 0)
				return ctrlmod54xx_dump(stdout,
					CTRLMOD54XX_CTRL_MODULE_WKUP_PAD);
			else
				return err_arg_msg_show(HELP_CTRLMOD);
		} else {
			return err_arg_too_many_msg_show(HELP_CTRLMOD);
		}
	} else if (strcmp(argv[0], "sr") == 0) {
		if (argc == 1) {
			ret = sr54xx_dump(stdout, SR54XX_SMARTREFLEX_MPU);
			ret |= sr54xx_dump(stdout, SR54XX_SMARTREFLEX_MM);
			ret |= sr54xx_dump(stdout, SR54XX_SMARTREFLEX_CORE);
			return ret;
		} else if (argc == 2) {
			if (strcmp(argv[1], "all") == 0)
				return sr54xx_dump(stdout, SR54XX_MODS_COUNT);
			else if (strcmp(argv[1], "mpu") == 0)
				return sr54xx_dump(stdout,
					SR54XX_SMARTREFLEX_MPU);
			else if (strcmp(argv[1], "mm") == 0)
				return sr54xx_dump(stdout,
					SR54XX_SMARTREFLEX_MM);
			else if (strcmp(argv[1], "core") == 0)
				return sr54xx_dump(stdout,
					SR54XX_SMARTREFLEX_CORE);
			else
				return err_arg_msg_show(HELP_SR);
		} else {
			return err_arg_too_many_msg_show(HELP_SR);
		}
	} else if (strcmp(argv[0], "abb") == 0) {
		ret = abb54xx_dump(stdout);
		fprintf(stderr,
			"\n\n### WARNING ###: deprecated command/options. "
			"See 'omapconf --help'.\n\n");
		return ret;
	} else if (strcmp(argv[0], "dep") == 0) {
		ret = clkdmdep54xx_dump(stdout);
		fprintf(stderr,
			"\n\n### WARNING ###: deprecated command/options. "
			"See 'omapconf --help'.\n\n");
		return ret;
	} else {
		return err_unknown_argument_msg_show(argv[0]);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main54xx_set
 * @BRIEF		set some OMAP5 item, which category is found in argv
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		argc: number of arguments
 * @param[in]		argv: argument(s)
 * @DESCRIPTION		set some OMAP5 item, which category is found in argv
 *//*------------------------------------------------------------------------ */
static int main54xx_set(int argc, char *argv[])
{
	voltdm54xx_id vdd_id;
	double volt;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	if (argc < 1) {
		return err_arg_missing_msg_show(HELP_CATEGORY_MAX);
	} else if (strcmp(argv[0], "prcm") == 0) {
		if (argc < 2) {
			return err_arg_missing_msg_show(HELP_PRCM);
		} else if (strcmp(argv[1], "statdep") == 0) {
			if (argc < 3)
				return err_arg_missing_msg_show(HELP_STATDEP);
			if (argc == 3)
				return clkdmdep54xx_set(argv[2], NULL, 1);
			else if (argc == 4)
				return clkdmdep54xx_set(argv[2], argv[3], 1);
			else
				return err_arg_too_many_msg_show(HELP_STATDEP);
		} else {
			return err_arg_msg_show(HELP_PRCM);
		}
	} else if (strcmp(argv[0], "volt") == 0) {
		if (argc < 3) {
			return err_arg_missing_msg_show(HELP_VOLT);
		} else if (argc == 3) {
			lowercase(argv[1]);
			if (strcmp(argv[1], "mpu") == 0)
				vdd_id = VDD54XX_MPU;
			else if (strcmp(argv[1], "mm") == 0)
				vdd_id = VDD54XX_MM;
			else if (strcmp(argv[1], "core") == 0)
				vdd_id = VDD54XX_CORE;
			else
				return err_arg_msg_show(HELP_VOLT);

			if (sscanf(argv[2], "%lf", &volt) != 1)
				return err_arg_msg_show(HELP_VOLT);

			return lib54xx_voltage_set(vdd_id, volt);
		} else {
			return err_arg_too_many_msg_show(HELP_VOLT);
		}
	} else {
		return err_arg_msg_show(HELP_CATEGORY_MAX);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main54xx_clear
 * @BRIEF		clear some OMAP5 item, which category is found in argv
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		argc: number of arguments
 * @param[in]		argv: argument(s)
 * @DESCRIPTION		clear some OMAP5 item, which category is found in argv
 *//*------------------------------------------------------------------------ */
static int main54xx_clear(int argc, char *argv[])
{
	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	if (argc < 1) {
		return err_arg_missing_msg_show(HELP_CATEGORY_MAX);
	} else if (strcmp(argv[0], "prcm") == 0) {
		if (argc < 2) {
			return err_arg_missing_msg_show(HELP_PRCM);
		} else if (strcmp(argv[1], "statdep") == 0) {
			if (argc < 3)
				return err_arg_missing_msg_show(HELP_STATDEP);
			if (argc == 3)
				return clkdmdep54xx_set(argv[2], NULL, 0);
			else if (argc == 4)
				return clkdmdep54xx_set(argv[2], argv[3], 0);
			else
				return err_arg_too_many_msg_show(HELP_STATDEP);
		} else {
			return err_arg_msg_show(HELP_PRCM);
		}
	} else {
		return err_arg_msg_show(HELP_CATEGORY_MAX);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main54xx_read
 * @BRIEF		read some item, which category is found in argv
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		argc: number of arguments
 * @param[in]		argv: argument(s)
 *			argv[0] = category
 *			argv[1...n] = arguments of that category
 * @DESCRIPTION		read some item, which category is found in argv
 *//*------------------------------------------------------------------------ */
int main54xx_read(int argc, char *argv[])
{
	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(argv, OMAPCONF_ERR_ARG);

	if (argc < 1) {
		return OMAPCONF_ERR_ARG;
	} else if (strcmp(argv[0], "audioic") == 0) {
		return twl6040_readreg(argv[1]);
	} else {
		return OMAPCONF_ERR_ARG;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main54xx_write
 * @BRIEF		udpate some item, which category is found in argv
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		argc: number of arguments
 * @param[in]		argv: argument(s)
 *			argv[0] = category
 *			argv[1...n] = arguments of that category
 * @DESCRIPTION		udpate some item, which category is found in argv
 *//*------------------------------------------------------------------------ */
int main54xx_write(int argc, char *argv[])
{
	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(argv, OMAPCONF_ERR_ARG);

	if (argc < 1) {
		return OMAPCONF_ERR_ARG;
	} else if (strcmp(argv[0], "audioic") == 0) {
		return twl6040_writereg(argv[1], argv[2]);
	} else {
		return OMAPCONF_ERR_ARG;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main54xx_trace
 * @BRIEF		find which trace to run (found in argv), and execute it
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		argc: number of arguments
 * @param[in]		argv: argument(s)
 *			argv[0] = category
 *			argv[1...n] = arguments of that category
 * @DESCRIPTION		find which trace to run (found in argv), and execute it
 *//*------------------------------------------------------------------------ */
int main54xx_trace(int argc, char *argv[])
{
	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(argv, OMAPCONF_ERR_ARG);

	if (argc < 1) {
		return err_arg_missing_msg_show(HELP_TRACE);
	} else if (strcmp(argv[0], "bw") == 0) {
		struct sigaction act;

		/* Register kill signal handler */
		act.sa_sigaction = &sigkill_handler;
		sigaction(SIGTERM, &act, NULL);
		sigaction(SIGQUIT, &act, NULL);
		sigaction(SIGINT, &act, NULL);

		return statcoll_main(argc, argv);
	} else {
		return err_unknown_argument_msg_show(argv[0]);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main54xx_show
 * @BRIEF		show some OMAP5 information,
 *			which category is found in argv
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG in case of incorrect format
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		show some OMAP5 information,
 *			which category is found in argv
 *//*------------------------------------------------------------------------ */
int main54xx_show(int argc, char *argv[])
{
	int ret;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(argv, OMAPCONF_ERR_ARG);

	if (argc < 1) {
		help(HELP_USAGE);
		return OMAPCONF_ERR_ARG;
	} else if (strcmp(argv[0], "prcm") == 0) {
		return prcm54xx_config_show(stdout, argc - 1, argv + 1);
	} else if (strcmp(argv[0], "opp") == 0) {
		if (argc == 1)
			return opp_show(stdout);
		else
			return err_arg_too_many_msg_show(HELP_SOC_OPP);
	} else if (strcmp(argv[0], "pwst") == 0) {
		if (argc == 1)
			return module_status_show(stdout);
		else
			return err_arg_too_many_msg_show(HELP_SOC_PWST);
	} else if (strcmp(argv[0], "temp") == 0) {
		if (argc == 1) {
			return temp_sensor_show(stdout, "all");
		} else if (argc == 2) {
			if (strcmp(argv[1], "all") == 0)
				return temp_sensor_show(stdout, argv[1]);
			else if (temp_sensor_is_available(argv[1]) != 0)
				return temp_sensor_show(stdout, argv[1]);
			else
				return err_arg_msg_show(HELP_TEMPERATURE);
		} else {
			return err_arg_too_many_msg_show(HELP_TEMPERATURE);
		}
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
	} else if (strcmp(argv[0], "dpll") == 0) {
		if (argc == 1) {
			return dpll54xx_show(stdout);
		} else if (argc == 2) {
			if (strcmp(argv[1], "cfg") == 0)
				return dpll54xx_show(stdout);
			else
				return err_arg_msg_show(HELP_DPLL);
		} else {
			return err_arg_too_many_msg_show(HELP_DPLL);
		}
	} else if (strcmp(argv[0], "hwobs") == 0) {
		if (argc == 1) {
			return hwobs54xx_display_cfg();
		} else if (argc == 2) {
			if (strcmp(argv[1], "cfg") == 0)
				return hwobs54xx_display_cfg();
			else
				return err_arg_msg_show(HELP_HWOBS);
		} else {
			return err_arg_too_many_msg_show(HELP_HWOBS);
		}
	} else if (strcmp(argv[0], "abe") == 0) {
		if (argc == 1) {
			return prcm54xx_config_show(stdout, 1, argv);
		} else if (argc == 2) {
			if (strcmp(argv[1], "cfg") == 0)
				return prcm54xx_config_show(
					stdout, 1, argv);
			else if (strcmp(argv[1], "atc") == 0)
				return abe54xx_atc_status_show(stdout);
			else
				return err_arg_msg_show(HELP_ABE);
		} else {
			return err_arg_too_many_msg_show(HELP_ABE);
		}
	} else if (strcmp(argv[0], "audioic") == 0) {
		if (argc == 1) {
			return twl6040_config(stdout);
		} else if (argc == 2) {
			if (strcmp(argv[1], "cfg") == 0)
				return twl6040_config(stdout);
			else if (strcmp(argv[1], "gains") == 0)
				return twl6040_gains(stdout);
			else
				return err_arg_msg_show(HELP_AUDIOIC);
		} else {
			return err_arg_too_many_msg_show(HELP_AUDIOIC);
		}
	} else if (strcmp(argv[0], "sr") == 0) {
		if (argc == 1) {
			return sr54xx_config_show(stdout);
		} else if (argc == 2) {
			if (strcmp(argv[1], "cfg") == 0)
				return sr54xx_config_show(stdout);
			else if (strcmp(argv[1], "status") == 0)
				return sr54xx_convergence_status_show(stdout);
			else
				return err_arg_msg_show(HELP_SR);
		} else {
			return err_arg_too_many_msg_show(HELP_SR);
		}
	} else if (strcmp(argv[0], "timers_32k") == 0) {
		return timestamp_32k_main(argc, argv);
	/* Legacy */
	} else if (strcmp(argv[0], "abb") == 0) {
		ret = abb54xx_config_show(stdout);
		fprintf(stderr,
			"\n\n### WARNING ###: deprecated command/options. "
			"See 'omapconf --help'.\n\n");
		return ret;
	} else if (strcmp(argv[0], "statdep") == 0) {
		ret = clkdmdep54xx_show(stdout, CLKDMDEP_STATIC);
		fprintf(stderr,
			"\n\n### WARNING ###: deprecated command/options. "
			"See 'omapconf --help'.\n\n");
		return ret;
	} else if (strcmp(argv[0], "dyndep") == 0) {
		ret = clkdmdep54xx_show(stdout, CLKDMDEP_DYNAMIC);
		fprintf(stderr,
			"\n\n### WARNING ###: deprecated command/options. "
			"See 'omapconf --help'.\n\n");
		return ret;
	} else if (strcmp(argv[0], "dep") == 0) {
		ret = clkdmdep54xx_show(stdout, CLKDMDEP_TYPE_MAX);
		fprintf(stderr,
			"\n\n### WARNING ###: deprecated command/options. "
			"See 'omapconf --help'.\n\n");
		return ret;
	} else {
		return err_unknown_argument_msg_show(argv[0]);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main54xx_enable
 * @BRIEF		enable selected item provided in string argv.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		enable selected item provided in string argv.
 *//*------------------------------------------------------------------------ */
static int main54xx_enable(int argc, char *argv[])
{
	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	if (argc == 0) {
		return err_arg_missing_msg_show(HELP_CATEGORY_MAX);
	} else if (strcmp(argv[0], "hwobs") == 0) {
		if (argc == 1)
			return hwobs54xx_enable();
		else
			return err_arg_too_many_msg_show(HELP_HWOBS);
	} else {
		return err_unknown_argument_msg_show(argv[0]);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main54xx_setup
 * @BRIEF		setup selected item provided in string argv.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		setup selected item provided in string argv.
 *//*------------------------------------------------------------------------ */
static int main54xx_setup(int argc, char *argv[])
{
	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	if (argc == 0) {
		return err_arg_missing_msg_show(HELP_CATEGORY_MAX);
	} else if (strcmp(argv[0], "hwobs") == 0) {
		if (argc < 2) {
			return err_arg_missing_msg_show(HELP_HWOBS);
		} else if (strcmp(argv[1], "pinmux") == 0) {
			if (argc != 3)
				return hwobs54xx_pinmux_setup(NULL);
			else
				return hwobs54xx_pinmux_setup(argv[2]);
		} else if (strcmp(argv[1], "mpuss") == 0) {
			if (argc != 3)
				return hwobs54xx_mpuss_setup(NULL);
			else
				return hwobs54xx_mpuss_setup(argv[2]);
		} else if (strcmp(argv[1], "prcm") == 0) {
			if (argc != 5)
				return hwobs54xx_prcm_setup(NULL, NULL, NULL);
			else
				return hwobs54xx_prcm_setup(
					argv[2], argv[3], argv[4]);
		} else {
			return err_arg_msg_show(HELP_HWOBS);
		}
	} else {
		return err_unknown_argument_msg_show(argv[0]);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main54xx_test
 * @BRIEF		test selected item provided in string argv.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		test selected item provided in string argv.
 *//*------------------------------------------------------------------------ */
static int main54xx_test(int argc, char *argv[])
{
	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	if (argc == 0) {
		return err_arg_missing_msg_show(HELP_CATEGORY_MAX);
	} else if (strcmp(argv[0], "hwobs") == 0) {
		if (argc != 2)
			return hwobs54xx_test(NULL);
		else
			return hwobs54xx_test(argv[1]);
	} else {
		return err_unknown_argument_msg_show(argv[0]);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main54xx_search
 * @BRIEF		search selected item provided in string argv.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		test selected item provided in string argv.
 *//*------------------------------------------------------------------------ */
static int main54xx_search(int argc, char *argv[])
{
	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	if (argc == 0) {
		return err_arg_missing_msg_show(HELP_CATEGORY_MAX);
	} else if (strcmp(argv[0], "vmin") == 0) {
		if (argc < 4)
			return err_arg_missing_msg_show(HELP_VOLT);
		else if (argc == 4)
			return lib54xx_vminsearch(argc - 1, argv + 1);
		else
			return err_arg_too_many_msg_show(HELP_VOLT);
	} else {
		return err_unknown_argument_msg_show(argv[0]);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main54xx_export
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
static int main54xx_export(int argc, char *argv[])
{
	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	if (argc == 0) {
		return lib54xx_export(NULL);
	} else if (strcmp(argv[0], "xml") == 0) {
		if (argc == 1)
			return lib54xx_export(NULL);
		else if (argc == 2)
			return lib54xx_export(argv[1]);
		else
			return err_arg_too_many_msg_show(HELP_EXPORT);
	} else if (strcmp(argv[0], "ctt") == 0) {
		if (argc == 1)
			return ctt54xx_dump();
		else if (argc == 2)
			return ctt54xx_rd1_export(argv[1]);
		else
			return err_arg_too_many_msg_show(HELP_EXPORT);
	#if 0 /* FIXME */
	} else if (strcmp(argv[0], "pct") == 0) {
		if (argc == 1)
			return pct54xx_dump();
		else if (argc == 2)
			return pct54xx_rd1_export(argv[1]);
		else
			return err_arg_too_many_msg_show(HELP_EXPORT);
	#endif
	} else {
		return err_arg_msg_show(HELP_EXPORT);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main54xx_legacy
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
int main54xx_legacy(int argc, char *argv[])
{
	int ret;

	if ((argc == 2) && (strcmp(argv[0], "prcm") == 0) &&
		(strcmp(argv[1], "dump") == 0)) {
		ret = prcm54xx_dump(NULL);
	} else if ((argc == 3) && (strcmp(argv[0], "prcm") == 0) &&
		(strcmp(argv[1], "dump") == 0)) {
		ret = prcm54xx_dump(argv[2]);
	} else if (strcmp(argv[0], "sr") == 0) {
		ret = sr54xx_main(argc - 1, argv + 1);
	} else if (strcmp(argv[0], "dpll") == 0) {
		ret = dpll54xx_main(argc - 1, argv + 1);
	} else if (strcmp(argv[0], "ctrlmod") == 0) {
		ret = ctrlmod54xx_main(argc - 1, argv + 1);
	} else if (strcmp(argv[0], "twl6035") == 0) {
		ret = twl603x_main(argc, argv);
	} else if (strcmp(argv[0], "hwobs") == 0) {
		ret = hwobs54xx_main(argc - 1, argv + 1);
	} else if (strcmp(argv[0], "ctt") == 0) {
		ret = ctt54xx_main(argc - 1, argv + 1);
	} else if (strcmp(argv[0], "vminsearch") == 0) {
		ret = lib54xx_vminsearch(argc - 1, argv + 1);
	} else {
		ret = err_unknown_argument_msg_show(argv[0]);
		goto main54xx_legacy_end;
	}

	fprintf(stderr, "\n\n### WARNING ###: deprecated command/options. "
		"See 'omapconf --help'.\n\n");

main54xx_legacy_end:
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main54xx
 * @BRIEF		OMAP5 functions main entry point
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		OMAP5 functions main entry point.
 *//*------------------------------------------------------------------------ */
int main54xx(int argc, char *argv[])
{
	int ret = 0;

	/* Check CPU */
	if (!cpu_is_omap54xx()) {
		ret = OMAPCONF_ERR_CPU;
		goto main54xx_end;
	}

	if (argc < 1)
		goto main54xx_err_arg;

	/* Initializations */
	dpll54xx_init();

	if (strcmp(argv[0], "audit") == 0) {
		ret = main54xx_audit(argc - 1, argv + 1);
	} else if (strcmp(argv[0], "dump") == 0) {
		ret = main54xx_dump(argc - 1, argv + 1);
	} else if (strcmp(argv[0], "show") == 0) {
		ret = main54xx_show(argc - 1, argv + 1);
	} else if (strcmp(argv[0], "export") == 0) {
		ret = main54xx_export(argc - 1, argv + 1);
	} else if (strcmp(argv[0], "set") == 0) {
		ret = main54xx_set(argc - 1, argv + 1);
	} else if (strcmp(argv[0], "clear") == 0) {
		ret = main54xx_clear(argc - 1, argv + 1);
	} else if (strcmp(argv[0], "read") == 0) {
		ret = main54xx_read(argc - 1, argv + 1);
	} else if (strcmp(argv[0], "write") == 0) {
		ret = main54xx_write(argc - 1, argv + 1);
	} else if (strcmp(argv[0], "trace") == 0) {
		ret = main54xx_trace(argc - 1, argv + 1);
	} else if (strcmp(argv[0], "vminsearch") == 0) {
		ret = lib54xx_vminsearch(argc - 1, argv + 1);
	} else if (strcmp(argv[0], "enable") == 0) {
		return main54xx_enable(argc - 1, argv + 1);
	} else if (strcmp(argv[0], "setup") == 0) {
		return main54xx_setup(argc - 1, argv + 1);
	} else if (strcmp(argv[0], "test") == 0) {
		return main54xx_test(argc - 1, argv + 1);
	} else if (strcmp(argv[0], "search") == 0) {
		ret = main54xx_search(argc - 1, argv + 1);
	} else {
		ret = main54xx_legacy(argc, argv);
	}

	goto main54xx_end;

main54xx_err_arg:
	help(HELP_ALL);
	ret = OMAPCONF_ERR_ARG;

main54xx_end:
	/* Deinitializations */
	dpll54xx_free();

	return ret;
}
