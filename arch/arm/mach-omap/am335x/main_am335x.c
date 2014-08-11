/*
 *
 * @Component			OMAPCONF
 * @Filename			main_am335x.c
 * @Description			OMAPCONF AM335X Main file
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


#include <cm_am335x-defs.h>
#include <cpuinfo.h>
#include <ctt_am335x.h>
#include <dpll_am335x.h>
#include <emif_am335x.h>
#include <help.h>
#include <lib.h>
#include <main_am335x.h>
#include <module.h>
#include <opp.h>
#include <prcm_am335x.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <temperature.h>
#include <unistd.h>


#ifdef MAIN_AM3335X_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main_am335x_dump
 * @BRIEF		dump some AM335X registers, which category is found in
 *			argv
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 * @param[in]		argc: number of arguments
 * @param[in]		argv: argument(s)
 * @DESCRIPTION		dump some AM335X registers, which category is found in
 *			argv
 *//*------------------------------------------------------------------------ */
int main_am335x_dump(int argc, char *argv[])
{
	dpll_am335x_id dpll_id;
	if (!cpu_is_am335x())
		return OMAPCONF_ERR_CPU;

	if (argc < 1) {
		help(HELP_USAGE);
		return OMAPCONF_ERR_ARG;
	} else if (strcmp(argv[0], "emif") == 0) {
		if (argc == 1)
			return emif_am335x_dump(stdout, EMIF_AM335X_EMIF4D);
		else
			return err_arg_too_many_msg_show(HELP_EMIF);
	} else if (strcmp(argv[0], "prcm") == 0) {
		if (argc == 1)
			return prcm_am335x_dump(NULL);
		else if (argc == 2)
			return prcm_am335x_dump(argv[1]);
		else
			return err_arg_too_many_msg_show(HELP_PRCM);
	}  else if (strcmp(argv[0], "dpll") == 0) {
		if (argc == 1) {
			return dpll_am335x_dump(stdout, DPLL_AM335X_ID_MAX);
		} else if (argc == 2) {
			if (strcmp(argv[1], "all") == 0) {
				dpll_id = DPLL_AM335X_ID_MAX;
			} else {
				dpll_id = dpll_am335x_s2id(argv[1]);
				if (dpll_id == DPLL_AM335X_ID_MAX)
					return err_arg_msg_show(HELP_DPLL);
			}
			return dpll_am335x_dump(stdout, dpll_id);
		} else {
			return err_arg_too_many_msg_show(HELP_DPLL);
		}
	} else {
		return err_unknown_argument_msg_show(argv[0]);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main_am335x_export
 * @BRIEF		Export AM335X configuration into format and destination
 *			provided in argv.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		Export AM335X configuration into format and destination
 *			provided in argv.
 *//*------------------------------------------------------------------------ */
static int main_am335x_export(int argc, char *argv[])
{
	if (strcmp(argv[0], "ctt") == 0) {
		if (argc == 1)
			return ctt_am335x_dump();
		else if (argc == 2)
			return ctt_am335x_rd1_export(argv[1]);
		else
			return err_arg_too_many_msg_show(HELP_EXPORT);
	} else {
		return err_arg_msg_show(HELP_EXPORT);
	}
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main_am335x_legacy
 * @BRIEF		AM335X functions main entry point (legacy)
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		AM335X functions main entry point (legacy)
 *//*------------------------------------------------------------------------ */
static int main_am335x_legacy(int argc, char*argv[])
{
	int ret;

	if ((argc == 2) && (strcmp(argv[0], "prcm") == 0) &&
		(strcmp(argv[1], "dump") == 0)) {
		ret = prcm_am335x_dump(NULL);
	} else if ((argc == 3) && (strcmp(argv[0], "prcm") == 0) &&
		(strcmp(argv[1], "dump") == 0)) {
		ret = prcm_am335x_dump(argv[2]);
	} else if (strcmp(argv[0], "ctt") == 0) {
		ret = ctt_am335x_main(argc - 1, argv + 1);
	} else if (strcmp(argv[0], "dpll") == 0) {
		ret = dpll_am335x_main(argc - 1, argv + 1);
	} else {
		ret = err_unknown_argument_msg_show(argv[0]);
		goto main_am335x_legacy_end;
	}

	fprintf(stderr, "\n\n### WARNING ###: deprecated command/options. "
		"See 'omapconf --help'.\n\n");

main_am335x_legacy_end:
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main_am335x_show
 * @BRIEF		show some AM335X registers, which category is found in
 *			argv
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 * @param[in]		argc: number of arguments
 * @param[in]		argv: argument(s)
 * @DESCRIPTION		show some AM335X registers, which category is found in
 *			argv
 *//*------------------------------------------------------------------------ */
int main_am335x_show(int argc, char *argv[])
{
	if (argc < 1) {
		help(HELP_USAGE);
		return OMAPCONF_ERR_ARG;
	} else if (strcmp(argv[0], "dpll") == 0) {
		if (argc == 1) {
			return dpll_am335x_show(stdout);
		} else if (argc == 2) {
			if (strcmp(argv[1], "cfg") == 0)
				return dpll_am335x_show(stdout);
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
	} else if (strcmp(argv[0], "pwst") == 0) {
		if (argc == 1)
			return module_status_show(stdout);
		else
			return err_arg_too_many_msg_show(HELP_SOC_PWST);
	} else {
		return err_unknown_argument_msg_show(argv[0]);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main_am335x
 * @BRIEF		AM335X functions main entry point
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		AM335X functions main entry point.
 *//*------------------------------------------------------------------------ */
int main_am335x(int argc, char *argv[])
{
	int ret = 0;

	/* Check CPU */
	if (!cpu_is_am335x()) {
		ret = OMAPCONF_ERR_CPU;
		goto main_am335x_end;
	}

	if (argc < 1)
		goto main_am335x_err_arg;

	/* Initializations */
	dpll_am335x_init();

	if (strcmp(argv[0], "export") == 0)
		ret = main_am335x_export(argc - 1, argv + 1);
	else if (strcmp(argv[0], "dump") == 0)
		ret = main_am335x_dump(argc - 1, argv + 1);
	else if (strcmp(argv[0], "show") == 0) {
		ret = main_am335x_show(argc -1, argv + 1);
	}
	else
		ret = main_am335x_legacy(argc, argv);

	goto main_am335x_end;

main_am335x_err_arg:
	help(HELP_ALL);
	ret = OMAPCONF_ERR_ARG;

main_am335x_end:
	/* Deinitializations */
	dpll_am335x_free();

	return ret;
}
