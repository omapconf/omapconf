/*
 *
 * @Component			OMAPCONF
 * @Filename			help.c
 * @Description			Help Library for OMAPCONF
 * @Author			Patrick Titiano (p-titiano@ti.com)
 * @Date			2006
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2006 Texas Instruments Incorporated - http://www.ti.com/
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


#include <help.h>
#include <help44xx.h>
#include <lib.h>
#include <help54xx.h>
#include <help_am335x.h>
#include <help_am437x.h>
#include <help_dra7xx.h>
#include <stdio.h>
#include <cpuinfo.h>


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		err_arg_too_many_msg_show
 * @BRIEF		print standard "too many arguments" error message.
 * @RETURNS		OMAPCONF_ERR_ARG
 * @param[in]		cat: help category to be printed
 * @DESCRIPTION		print standard "too many arguments" error message,
 *			followed by help of given category.
 *			If cat == HELP_CATEGORY_MAX, no specific help section
 *			will be printed.
 *//*------------------------------------------------------------------------ */
int err_arg_too_many_msg_show(help_category cat)
{
	if (cat != HELP_CATEGORY_MAX) {
		printf("\nomapconf: too many option(s). "
			"See supported ones below.\n\n");
		help(cat);
		printf("\n");
	} else {
		printf("\nomapconf: too many option(s). "
			"See 'omapconf --help' for more information.\n\n");
	}

	return OMAPCONF_ERR_ARG;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		err_arg_missing_msg_show
 * @BRIEF		print standard "missing argument" error message.
 * @RETURNS		OMAPCONF_ERR_ARG
 * @param[in]		cat: help category to be printed
 * @DESCRIPTION		print standard "missing argument" error message,
 *			followed by help of given category.
 *			If cat == HELP_CATEGORY_MAX, no specific help section
 *			will be printed.
 *//*------------------------------------------------------------------------ */
int err_arg_missing_msg_show(help_category cat)
{
	if (cat != HELP_CATEGORY_MAX) {
		printf("\nomapconf: missing option(s). "
			"See supported ones below.\n\n");
		help(cat);
		printf("\n");
	} else {
		printf("\nomapconf: missing option(s). "
			"See 'omapconf --help' for more information.\n\n");
	}

	return OMAPCONF_ERR_ARG;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		err_arg_msg_show
 * @BRIEF		print standard "incorrect argument" error message,
 * @RETURNS		OMAPCONF_ERR_ARG
 * @param[in]		cat: help category to be printed
 * @DESCRIPTION		print standard "incorrect argument" error message,
 *			followed by help of given category.
 *			If cat == HELP_CATEGORY_MAX, no specific help section
 *			will be printed.
 *//*------------------------------------------------------------------------ */
int err_arg_msg_show(help_category cat)
{
	if (cat != HELP_CATEGORY_MAX) {
		printf("\nomapconf: incorrect option(s). "
			"See supported ones below.\n\n");
		help(cat);
		printf("\n");
	} else {
		printf("\nomapconf: incorrect option(s). "
			"See 'omapconf --help' for more information.\n\n");
	}

	return OMAPCONF_ERR_ARG;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		err_internal_msg_show
 * @BRIEF		print standard "internal error" error message.
 * @RETURNS		OMAPCONF_ERR_INTERNAL
 * @DESCRIPTION		print standard "internal error" error message.
 *//*------------------------------------------------------------------------ */
int err_internal_msg_show(void)
{
	printf("\nomapconf: aborting due to internal error, sorry :-( ...\n\n");

	return OMAPCONF_ERR_INTERNAL;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		err_unknown_argument_msg_show
 * @BRIEF		print standard "unknown argument, see help" message.
 * @RETURNS		OMAPCONF_ERR_ARG
 * @param[in]		s: unknown argument
 * @DESCRIPTION		print standard "unknown argument, see help" message.
 *//*------------------------------------------------------------------------ */
int err_unknown_argument_msg_show(char *s)
{
	printf("\nomapconf: '%s' is not a valid omapconf argument. "
		"See 'omapconf --help'.\n\n", s);

	return OMAPCONF_ERR_ARG;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		help
 * @BRIEF		display omapconf help
 * @RETURNS		none
 * @param[in]		cat: help category to display
 * @DESCRIPTION		display omapconf help
 *//*------------------------------------------------------------------------ */
void help(help_category cat)
{
	if (cat >= HELP_CATEGORY_MAX) {
		fprintf(stderr, "help called with incorrect category!!! (%d)\n",
			cat);
		return;
	}

	if ((cat == HELP_ALL) || (cat == HELP_USAGE)) {
		printf("\nNAME\n");
		printf("\tomapconf - TI OMAP Configuration Diagnostic Tool\n");

		printf("\nSYNOPSIS\n");
		printf("\tomapconf [--version] [--help] [--cpuinfo] "
			"[--buildinfo] [--import <file>] [--force <cpu>] "
			"[--norw] <command> [<args>]\n");
		if (cat == HELP_USAGE)
			printf("\n\tSee 'omapconf --help' for more "
			"information.\n\n");
	}

	if (cat == HELP_ALL) {
		printf("\nDESCRIPTION\n");
		printf("\tomaconf is standalone application designed to provide"
			" a quick'n easy way to diagnose/monitor/debug/audit "
			"TI OMAP processors configuration at runtime, with no "
			"particular kernel dependency.\n");
		printf("\tomapconf is designed to be as much platform-agnostic "
			"as possible, being able to run on any Linux platform ("
			"Ubuntu, Android, ...) and easily ported to "
			"other OS.\n");
		printf("\tEven if omapconf today focuses mainly on "
			"power management and performances diagnostic, it is "
			"intended to be extended to any other area.\n");

		printf("\nOPTIONS\n");
		printf("\t--help\n");
		printf("\t    Print omapconf help.\n");

		printf("\n\t--version\n");
		printf("\t    Print omapconf version.\n");

		printf("\n\t--cpuinfo\n");
		printf(
			"\t    Print CPU details (revision, type, DIE ID, ...).\n");

		printf("\n\t--buildinfo\n");
		printf("\t    Print SW Build Details (kernel, release).\n");

		printf("\n\t--import <file> (### OMAP5 ONLY ###)\n");
		printf("\t    Import OMAP registers content from XML <file> "
			"(generated with command \"export <file>\").\n");
		printf("\t    Must be used in conjunction with option "
			"\"--force\".\n");

		printf("\n\t--norw\n");
		printf("\t    Fake memory access (no real R/W done): write "
			"accesses are discarded, read accesses return physical "
			"address.\n");

		printf("\n\t--trace_read\n");
		printf(
			"\t    Enable console tracing of all omapconf memory read access.\n");

		printf("\n\t--trace_write\n");
		printf(
			"\t    Enable console tracing of all omapconf memory write access.\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_FORCEDETECT)) {
		printf("\n\t--force <cpu>\n");
		printf("\t    Force CPU detection.\n");
		printf(
			"\t    Supported supported <cpu>: "
			"omap4430, omap4460, omap4470, "
			"omap5430es1, omap5432es1, omap5430, omap5432, "
			"dra75x, dra72x, am3352, am3354, am3356, am3357, "
			"am3358, am3359, am335x, am437x"
			"\n");

	}

	if ((cat != HELP_USAGE) && (cat != HELP_FORCEDETECT))
		printf("\nCOMMANDS\n");

	if ((cat == HELP_ALL) || (cat == HELP_RW)) {
		printf("\n\t### WARNING ###: use the following [read | write | "
			"set bit | clear bit | dump] commands at your own "
			"risk!\n");
		printf("\tNo address check done, may generate:\n");
		printf("\t  - bus error (invalid or not accessible "
			"<physical address>,\n");
		printf("\t  - platform crash/hang (bad <value>).\n");

		printf("\n\tomapconf read [0x<physical address> | <name>]\n");
		printf("\t    Read any OMAP memory address (register), given "
			"its <physical address> or <name> as listed in TRM.\n");
		printf("\t    e.g: omapconf read 0x4A306300, omapconf read "
			"PM_MPU_PWRSTCTRL\n");

		printf("\n\tomapconf write [0x<physical address> | <name>] "
			"0x<value>\n");
		printf("\t    Write <value> at any OMAP memory address "
			"(register), given its <physical address> or <name> as "
			"listed in TRM.\n");
		printf("\t    e.g: omapconf write 0x4A306300 0xDEADBEEF, "
			"omapconf write PM_MPU_PWRSTCTRL 0xDEADBEEF\n");

		printf("\n\tomapconf set bit [0x<physical address> | <name>] "
			"<position>"
			"\n");
		printf("\t    Set bit at <position> into any OMAP memory "
			"address (register), given its <physical address> "
			"or <name> as listed in TRM.\n");
		printf("\t    e.g: omapconf set bit 0x4A306300 1, "
			"omapconf set bit PM_MPU_PWRSTCTRL 1\n");

		printf("\n\tomapconf clear bit [0x<physical address> | <name>] "
			"<position>\n");
		printf("\t    Clear bit at <position> into any OMAP memory "
			"address (register), given its <physical address> "
			"or <name> as listed in TRM.\n");
		printf("\t    e.g: omapconf clear bit 0x4A306300 1, "
			"omapconf clear bit PM_MPU_PWRSTCTRL 1\n");

		printf("\n\tomapconf dump 0x<start address> 0x<end address>\n");
		printf("\t    Dump a range of OMAP memory addresses, from "
			"<start address> to <end address>.\n");
		printf("\t    Note all addresses within given range must be "
			"valid and accessible.\n");
		printf("\t    e.g: omapconf dump 0x48243400 0x4824340C\n");
	}


	if ((cat == HELP_ALL) || (cat == HELP_RW) || (cat == HELP_I2C_RW)) {
		printf("\n\t### WARNING ###: use the following I2C "
			"[read | write] commands at your own risk!\n");
		printf("\tNo address check done, may generate:\n");
		printf("\t  - I2C bus error (invalid or not accessible "
			"<physical address>,\n");
		printf("\t  - platform crash/hang (bad <value>).\n");


		printf("\n\tomapconf read i2c <bus> 0x<chip-addr> 0x<addr>\n");
		printf("\t    Read I2C register at address <addr> from I2C chip"
			" at <chip-addr> on I2C <bus>.\n");
		printf("\t    e.g: omapconf i2c read 1 0x49 0x02\n");

		printf("\n\tomapconf write i2c <bus> 0x<chip-addr> 0x<addr> "
			"0x<value>\n");
		printf("\t    Write <value> in I2C register at address <addr> "
			"from I2C chip at <chip-addr> on I2C <bus>.\n");
		printf("\t    e.g: omapconf i2c write 1 0x49 0x02 0xAA\n");
	}

	if ((cat == HELP_RW) || (cat == HELP_I2C_RW) ||
		(cat == HELP_FORCEDETECT))
		goto help_end;

	/* OMAP4-specific commands */
	if (cpu_is_omap44xx())
		help44xx(cat, "all");

	/* OMAP5-specific commands */
	if (cpu_is_omap54xx())
		help54xx(cat, "None");

	/* DRA7-specific commands */
	if (cpu_is_dra7xx())
		help_dra7xx(cat, "None");

	if (cpu_is_am335x())
		help_am335x(cat, "None");

	if (cpu_is_am437x())
		help_am437x(cat, "None");

	if (cat == HELP_ALL) {
		printf("\nREPORTING BUGS\n");
		printf("\tReport bugs to <omapconf_bugreport@list.ti.com> "
			"mailing-list.\n");
		printf("\tYou do not have to be subsribed to the list to send "
			"a message there.\n");

		printf("\nSUGGESTIONS\n");
		printf("\tSuggest any new idea to "
			"<omapconf_suggestions@list.ti.com> mailing-list.\n");
		printf("\tYou do not have to be subsribed to the list to send "
			"a message there.\n");

		printf("\nCONTRIBUTIONS\n");
		printf("\tSend patch to <omapconf_contribution@list.ti.com> "
			"mailing-list.\n");
		printf("\tYou do not have to be subsribed to the list to send "
			"a message there.\n");

		printf("\nNOTIFICATIONS\n");
		printf("\tSubscribe to <omapconf_updates@list.ti.com> "
			"mailing-list for automatic update notification.\n");
		printf("\tYou do not have to be subsribed to the list to send "
			"a message there.\n");

		printf("\nFURTHER DOCUMENTATION\n");
		printf("\tVisit omapconf wiki:\n");
		printf("\t\t<https://github.com/omapconf/omapconf/wiki>\n");

		printf("\n");
	}

help_end:
	return;
}
