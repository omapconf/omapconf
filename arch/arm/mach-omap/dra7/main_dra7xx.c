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
#include <dpll_dra7xx.h>
#include <lib.h>
#include <help.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <cpuinfo.h>
#include <prcm_dra7xx.h>


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
	} else {
		return err_unknown_argument_msg_show(argv[0]);
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
