/*
 *
 * @Component			OMAPCONF
 * @Filename			help44xx.c
 * @Description			Help for OMAP4-specific functions
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


#include <help44xx.h>
#include <stdio.h>
#include <string.h>
#include <cpuinfo.h>
#include <lib.h>
#include <counters44xx.h>
#include <emif44xx.h>
#include <mpuss44xx.h>


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		help44xx
 * @BRIEF		display omap4conf help
 * @param[in]		cat: help category to display
 * @DESCRIPTION		display omap4conf help
 *//*------------------------------------------------------------------------ */
void help44xx(help_category cat, char *context)
{
	unsigned int i;
	int ret;
	char name[64];
	char desc[128];

	if (cat >= HELP_CATEGORY_MAX) {
		fprintf(stderr, "%s(): incorrect category!!! (%u)\n",
			__func__, cat);
		return;
	}

	if ((cat == HELP_ALL) || (cat == HELP_EXPORT)) {
		printf("\n\tomapconf export ctt [<filename>]\n");
		printf("\t    Export PRCM registers in .rd1 format for Clock "
			"Tree Tool (CTT, <http://omappedia.org/wiki/CTT>), to "
			"<filename> or stdout if omitted.\n");

		printf("\n\tomapconf export pct [<filename>]\n");
		printf("\t    Export PRCM registers in .rd1 format for Pad "
			"Configuration Tool (PCT, "
			"<http://www.ti.com/general/docs/wtbu/wtbudocumen"
			"tcenter.tsp?templateId=6123&navigationId=12804#62>),"
			" to <filename> or stdout if omitted.\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_SOC_PWST)) {
		printf("\n\tomapconf show pwst\n");
		printf("\t    Print OMAP power status (OPP, voltage/power/clock"
			" domains states, and modules status).\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_SOC_OPP)) {
		printf("\n\tomapconf show opp\n");
		printf("\t    Print OMAP current OPerating Points (OPP)"
			"(voltage, frequency) for MPU/IVA/CORE voltage "
			"domains), including main modules frequencies.\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_TEMPERATURE)) {
		printf("\n\tomapconf show temp [<sensor>]\n");
		printf(
			"\t    Print temperature reported by <sensor>, in celcius degrees.\n");
		printf(
			"\t    Supported <sensor>: bandgap, hotspot, mem1, mem2, pcb.\n");
		printf(
			"\t    If <sensor> is omitted, all available sensors will be printed in a table, with both celcius and fahrenheit degrees.\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_VOLT)) {
		printf("\n\tomapconf set volt <rail> <voltage>\n");
		printf("\t    Set <rail> voltage to <voltage>.\n");
		printf("\t    Supported <rail>: mpu, iva, core.\n");
		printf("\t    <voltage> is in volts.\n");
		printf("\t    ### WARNING ###: do it at your own risk. "
			"Unsupported voltage may crash or damage device!\n");
		printf("\t    e.g. omapconf set volt mpu 1.25\n");

		printf("\n\tomapconf search vmin <rail> <voltage> <time>\n");
		printf("\t    Scale <rail> voltage down step by step, starting "
			"from <voltage> & waiting <time> between 2 steps.\n");
		printf("\t    LAST voltage displayed with OK status before "
			"crash will be the minimum voltage (aka VMIN) for that "
			"<rail>.\n");
		printf("\t    Supported <rail>: mpu, iva, core.\n");
		printf("\t    <voltage> is in volts. <time> is in milliseconds."
			"\n");
		printf("\t    Make sure your load generator application is "
			"running in background during the whole procedure.\n");
		printf("\t    ### WARNING ###: no possible recovery, platform "
			"must be rebooted after use!\n");
		printf("\t    e.g. omapconf search vmin mpu 1.25 500\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_DPLL)) {
		printf("\n\tomapconf dump dpll\n");
		printf("\t    Dump all DPLL registers.\n");

		printf("\n\tomapconf show dpll [cfg]\n");
		printf("\t    Print the complete configuration of all DPLL "
			"([cfg] may be omitted).\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_PRCM)) {
		printf("\n\tomapconf dump prcm [<pwrdm>]\n");
		printf("\t    Dump PRCM Registers related to <pwrdm> power "
			"domain.\n");
		printf("\t    Supported <pwrdm> ('all' assumed if omitted): "
			"mpu, core, dsp, dss, cam, gfx, ivahd, per, abe, wkup, "
			"l3init, alwon, emu, all.\n");

		printf("\n\tomapconf show prcm <pwrdm> [cfg]\n");
		printf("\t    Print <pwrdm> PRCM power configuration and "
			"status ([cfg] may be omitted).\n");
		printf("\t    Supported <pwrdm>: mpu, core, dsp, dss, cam, gfx,"
			" ivahd, per, abe, wkup, l3init, alwon, emu.\n");

		printf("\n\tomapconf show prcm <pwrdm> dep\n");
		printf("\t    Print <pwrdm> clock domain dependencies.\n");
		printf("\t    Supported <pwrdm>: mpu, core, dsp, dss, cam, gfx,"
			" ivahd, per, l3init, emu.\n");

		printf("\n\tomapconf show prcm irq\n");
		printf("\t    Print MPU PRM IRQ configuration and status.\n");

	}

	if ((cat == HELP_ALL) || (cat == HELP_PRCM) || (cat == HELP_STATDEP)) {
		printf("\n\tomapconf dump prcm statdep\n");
		printf("\t    Dump all PRCM clock domain static dependency "
			"registers.\n");

		printf("\n\tomapconf show prcm statdep\n");
		printf("\t    Print all PRCM static dependency configuration "
			"between clock domains ([cfg] may be omitted).\n");

		printf("\n\tomapconf [set | clear] prcm statdep <from> [<to>]"
			"\n");
		printf("\t    [Set (enable) | Clear (disable)] static "
			"dependency from clock domain <from> towards clock "
			"domain <to>.\n");
		printf("\t    Supported <from>/<to>: l4wkup, emu, mpu, abe, "
			"ivahd, dsp, alwoncore, l4cfg, c2c, sdma, mpu_m3, l3_1,"
			" l3_2, l3instr, memif, std_efuse, cust_efuse, cam, "
			"dss, gfx, l3init, l4sec, l4per.\n");
		printf("\t    If <to> = all or <to> is omitted, then all "
			"static dependencies from clock domain <from> will be "
			"set (enabled) / cleared (disabled) in a row.\n");
		printf("\t    ###WARNING###: use below commands at your own "
			"risk, may crash the platform!\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_PRCM) || (cat == HELP_WKDEP)) {
		printf("\n\tomapconf dump prcm wkdep\n");
		printf("\t    Dump PRCM wakeup dependency registers.\n");

		printf("\n\tomapconf show prcm wkdep [cfg]\n");
		printf("\t    Print PRCM wakeup dependency configuration "
			"([cfg] may be omitted).\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_PRCM) || (cat == HELP_ABB)) {
		printf("\n\tomapconf dump prcm abb\n");
		printf("\t    Dump PRCM Adaptive Body-Bias (ABB) registers.\n");

		printf("\n\tomapconf show prcm abb [cfg]\n");
		printf("\t    Print PRCM Adaptive Body-Bias (ABB) configuration "
			"([cfg] may be omitted).\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_AVS)) {
		printf("\n\tomapconf dump sr\n");
		printf("\t    Dump Smart-Reflex Adaptive Voltage Scaling (AVS) "
			"registers.\n");

		printf("\n\tomapconf show sr [cfg]\n");
		printf("\t    Print Smart-Reflex Adaptive Voltage Scaling (AVS)"
			" configuration, including Voltage Controller (VC) "
			"and Voltage Processor (VP) configurations "
			"([cfg] may be omitted).\n");

		printf("\n\tomapconf show sr status\n");
		printf("\t    Print Smart-Reflex Adaptive Voltage Scaling (AVS)"
			" convergence status.\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_MPUSS)) {
		printf("\n\tomapconf dump mpuss [scu | l2c | gic | wkg | scm]"
			"\n");
		printf("\t    Dump selected MPUSS (MPU SubSystem) item "
			"registers: Snoop Control Unit (scu), Level 2 Cache "
			"Controller (l2c), Generic Interrupt Controller (gic), "
			"WaKeup Generator (wkg), Security Control Module (scm)."
			"\n");

		printf("\n\tomapconf show mpuss [scu | gic] [cfg]\n");
		printf("\t    Print selected MPUSS (MPU SubSystem) item "
			"configuration ([cfg] may be omitted): Snoop Control "
			"Unit (scu), Generic Interrupt Controller (gic).\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_DISPLAY)) {
		printf("\n\tomapconf dump display <module>\n");
		printf("\t    Dump display subsystem <module> registers.\n");
		printf("\t    Supported <module>: dss, dsi1, dsi1_pll, dsi1_phy"
			", dsi2, dsi2_pll, dsi2_phy, rfbi, venc, all.\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_CAMERA)) {
		printf("\n\tomapconf dump camera <module>\n");
		printf("\t    Dump camera subsystem <module> registers.\n");
		printf("\t    Supported <module>: iss_hl, iss_csi2a, iss_csi2b,"
			" iss_csiphy1, iss_csiphy2, iss_ccp2, all.\n");

		printf("\n\tomapconf show camera [cfg]\n");
		printf(
			"\t    Show camera subsystem configuration ([cfg] may be omitted).\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_EMIF)) {
		printf("\n\tomapconf dump emif\n");
		printf("\t    Dump EMIF[1-2] registers.\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_ABE)) {
		printf("\n\tomapconf dump abe\n");
		printf("\t    Dump Audio Back End (ABE) registers.\n");

		printf("\n\tomapconf show abe [cfg]\n");
		printf("\t    Print Audio Back End (ABE) PRCM configuration "
			"([cfg] may be omitted).\n");

		printf("\n\tomapconf show abe atc\n");
		printf("\t    Print Audio Back End (ABE) ATC descriptors "
			"status.\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_HWOBS)) {
		printf("\n\tomapconf setup hwobs [pinmux | prcm | mpuss | abe]"
			"\n");
		printf("\t    Select HWOBS signals and handles mux "
			"configuration. Type one of these commands for more "
			"details on supported options.\n");

		printf("\n\tomapconf show hwobs [cfg]\n");
		printf("\t    Print current configuration of HWOBS signals "
			"([cfg] may be omitted).\n");

		printf("\n\tomapconf test hwobs [zero | one]\n");
		printf("\t    Test external pads setup (tie-low, tie-high "
			"debug signals).\n");

		printf("\n\tomapconf enable hwobs\n");
		printf("\t    Enable debug signals. To be called after 'setup' "
			"and 'test' commands.\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_PMIC)) {
		printf("\n\tomapconf dump pmic\n");
		printf("\t    Dump TWL603x (Power Management IC) registers.\n");

		printf("\n\tomapconf show pmic <item>\n");
		printf("\t    Print TWL603x (Power Management IC) <item> "
			"configuration.\n");
		printf("\t    Supported <item>: cfg (all <item>), "
			"ldocfg (LDO), smpscfg (SMPS), rescfg (resource "
			"dependencies), devpwrgrpstat (device level power "
			"group status).\n");

		printf("\n\tomapconf set pmic devpwrgrp [MOD | CON | APP] "
			"[ON | OFF]\n");
		printf("\t    Set TWL603x (Power Management IC) device level "
			"power group [MOD | CON | APP] to [ON | OFF].\n");
		printf("\t    ### WARNING ###: do it at your own risk. "
			"May crash the platform!\n");

		printf("\n\tomapconf reset pmic\n");
		printf("\t    ### RESET ### TWL603x (Power Management IC) "
			"device (bypassing OMAP reset).\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_AUDIOIC)) {
		printf("\n\tomapconf dump audioic\n");
		printf("\t    Dump TWL6040 (Audio IC) registers.\n");

		printf("\n\tomapconf show audioic [cfg]\n");
		printf("\t    Print TWL6040 (Audio IC) audio configuration "
			"([cfg] may be omitted).\n");

		printf("\n\tomapconf show audioic gains\n");
		printf("\t    Print TWL6040 (Audio IC) audio analog gains.\n");

		printf("\n\tomapconf read audioic [0x<addr> | <name>]\n");
		printf("\t    Read TWL6040 (Audio IC) register, given its "
			"physical address <addr> or <name> as listed in TRM."
			"\n");
		printf("\t    e.g. omapconf read audioic ASICID.\n");

		printf("\n\tomapconf write audioic [0x<addr> | <name>] "
			"0x<data>\n");
		printf("\t    Write <data> into TWL6040 (Audio IC) register, "
			"given its physical address <addr> or <name> as listed "
			"in TRM.\n");
		printf("\t    e.g. omapconf write audioic HSGAIN 0x10.\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_TIMERS_32K)) {
		printf("\n\tomapconf show timers_32k [<runs>]\n");
		printf("\t    Execute <runs> executions of (10 by default):\n");
		printf("\t      - read 32kHz register, clock_gettime("
			"CLOCK_MONONOTONIC, ...), gettimeofday()\n");
		printf("\t      - print value of each + offset from 32kHz to "
			"each clock in us\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_TRACE)) {
		printf(
			"\n\tomapconf trace pwrdm [<duration>] ### EXPERIMENTAL ###\n");
		printf(
			"\t    Collect via PMI power domain transitions trace & statistics.\n");
		printf(
			"\t    Use optional <duration> to select trace length (in seconds, default: 10s).\n");
		printf(
			"\t    NB: this function is not available on HS device.\n");

		printf(
			"\n\tomapconf trace opp [<duration>] ### EXPERIMENTAL ###\n");
		printf(
			"\t    Collect via PMI OPP changes trace & statistics.\n");
		printf(
			"\t    Use optional <duration> to select trace length (in seconds, default: 10s).\n");
		printf(
			"\t    NB: this function is not available on HS device.\n");


		printf("\n\tomapconf trace perf setup [<cfgfile>]\n");
		printf(
			"\t    Interactive performance trace configurator. To be used to:\n");
		printf("\t      - Generate default trace,\n");
		printf(
			"\t      - Select which predefined item(s) to trace for,\n");
		printf(
			"\t      - Add/remove user defined items. Any file which contains a dynamic variable (integer, accumulating or not) can be traced.\n");
		printf(
			"\t    Use optional <cfgfile> to select a trace configuration file name. Default one used otherwise.\n");

		printf(
			"\n\tomapconf trace perf [-d <delay>] [-t <duration>] [-s <rate>] [-p <prefix>] [-c <cfgfile>]\n");
		printf(
			"\t    Capture predefined items (CPUs Load, MPU/GPU/L3 OPP Changes, EMIF data bus load (4430, 4460) or EMIF bandwidth (4470), & temperatures (bandgap, PCB, hotspot) or custom (user defined) items over time.\n");
		printf(
			"\t    Trace customization is done via trace configuration file, built using the trace configurator.\n");
		printf(
			"\t    If no configuration file found or selected via <cfgfile>, create a default one that will trace for all predefined items.\n");
		printf(
			"\t    Generate GNUPlot scripts to plot trace charts.\n");
		printf(
			"\t    Use optional <delay> to add initial delay before capture starts (in seconds, default: 0s).\n");
		printf(
			"\t    Use optional <duration> to change capture duration (in seconds, default: 10s).\n");
		printf(
			"\t    Use optional <rate> to change capture sampling rate (in seconds, default: 0.1s).\n");
		printf(
			"\t    Use optional <prefix> to add <prefix> to default output file names.\n");
		printf(
			"\t    Use optional <cfgfile> to select a particular trace configuration file.\n");
		printf(
			"\t    e.g. to capture a trace of 30s, with initial delay of 3s, sampling rate of 0.1s, output files prefixed with 'db175_mp3_', using default configuration file:\n");
		printf(
			"\t    # omapconf trace perf -t 30 -d 3 -s 0.1 -p db175_mp3_\n");

		printf(
			"\n\tomapconf trace bw [-h] [<-m | --m<x>> <0xyy | ma_mpu | alldmm | dss | iva | ...>] [<-p | --p<x> <emif1 | emif2>] [<--tr | --tr<x>> <r|w|r+w>] [-d x] [-a 1 or 2] [-i x] [--overflow_delay x] [-o x -t y] [-r 0xaaaaaaaa-0xbbbbbbbb] [-n]\n");
		printf(
			"\t    EMIF traffic monitoring. Type 'omapconf trace bw -h' for detailed help.\n");
		printf(
			"\t    Visit wiki: <http://opbuwiki.dal.design.ti.com/index.php/L3_bus_monitoring_SW_tool>\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_TRACE) ||
		(cat == HELP_COUNTERS)) {
		if (strcmp(context, "all") == 0) {
			printf("\n\tomapconf trace counters [<duration>]"
				" [<prefix>] ### ALPHA ###\n");
			printf("\t    Capture from a predefined list of "
				"counters which is read from .omapconf_defaults"
				" file.\n");
			printf("\t    Use optional <duration> to select trace "
				"length (in seconds, default: 10s).\n");
			printf("\t    Use optional <prefix> to set a counters "
				"dat/txt file prefix (for batch running). If "
				"using <prefix>, <duration> argument is "
				"required.\n");
			printf("\t    ### WARNING ###: L2$ counters lost "
				"accross MPU domain power transitions.\n");
			printf("\n\tomapconf trace counters defaults\n");
			printf("\t    Print an empty example defaults file "
				"which can be used as the basis for "
				".omapconf_defaults file.\n");

			printf("\n\tomapconf trace counters help [<context>]"
				"\n");
			printf("\t    Print context help for counters.\n");
			printf("\t    Supported <context>:.\n");
			printf("\t      - 'options'. Display configurable "
				"options for counters. Options are stored in "
				"'.omapconf_defaults' file.\n");
			printf("\t      - 'l2cc_events'. Display l2cc_events "
				"supported for tracing. l2cc events are read "
				"from '.omapconf_defaults' file.\n");
			printf("\t      - 'emif_events'. Display emif_events "
				"supported for counting.\n");
		}

		if (strcmp(context, "options") == 0) {
			printf("\t    Syntax is:\n");
			printf("\t      '#' indicates a comment thereafter to "
				"end of line.\n");
			printf("\t      [option] [option_value]\n");
			printf("\t      There is whitespace separating the "
				"tokens.\n");
			printf("\t      [option_value] is either DISABLED or a "
				"legal value for the option.\n");
			printf("\t      [option] values:\n");
			for (i = 0; i < TRACE_CFG_TABLE_MAX; i++) {
				ret = value2name(i, name,
					trace_config_options_table);
				ret = value2desc(i, desc,
					trace_config_options_table);
				if (ret >= 0)
					printf("\t        %s: %s\n",
						name, desc);
			}
		}

		if (strcmp(context, "l2cc_events") == 0) {
			printf("\t      The following PL310 options can be "
				"included in the .omapconf_defaults file. "
				"There are two counters in the PL310.\n");
			printf("\t      Refer to "
				"ARM PL310 documentation for more details.\n");
			printf("\t      [l2cc_event] values:\n");
			for (i = 0; i < L2CC44XX_EVT_CNT_MAX; i++) {
				ret = value2name(i, name,
					l2cc_event_counters_table);
				ret = value2desc(i, desc,
					l2cc_event_counters_table);
				if (ret >= 0)
					printf("\t        %s: %s\n",
						name, desc);
			}
		}

		if (strcmp(context, "emif_events") == 0) {
			printf("\t      When enabling the EMIF event option, "
				"one of the event (counter) types is selected. "
				"There are two counters in each of the 2 EMIFs."
				"\n");
			printf("\t      Refer to EMIF documentation for more "
				"details.\n");
			printf("\t      [emif_event] values:\n");
			for (i = 0; i < EMIF44XX_PERF_CNT_FILTER_MAX; i++) {
				ret = value2name(i, name, emif_event_counters);
				ret = value2desc(i, desc, emif_event_counters);
				if (ret >= 0)
					printf("\t        %s: %s\n",
						name, desc);
			}
		}
	}

	if ((cat == HELP_ALL) || (cat == HELP_AUDIT)) {
		printf("\n\tomapconf audit dpll [-d <dpll>] [-o <opp>]\n");
		printf("\t    Audit DPLL settings at selected OPP(s).\n");
		printf("\t    By default, audit ALL DPLLs at CURRENT OPP. "
			"Use optional \"-d <dpll>\" to select a given DPLL.\n");
		printf("\t    Supported <dpll> ('all' considered if omitted):"
			" mpu, iva, core, per, abe, usb, all.\n");
		printf("\t    Use optional '-o all' to run audit at all "
			"### MPU ### OPerating Points (OPP).\n");
		printf("\t    Use optional '-o <opp>' to force a particular "
			"### MPU ### OPerating Points (OPP). For example "
			"when MPU OPP is not correctly detected.\n");
		printf("\t    Supported <opp>: dpll_casc, opp50, opp100, "
			"opp_turbo, opp_nitro, opp_nitrosb.\n");

		printf("\n\tomapconf audit sysconfig\n");
		printf("\t    Audit OMAP modules SYSCONFIG settings "
			"(autoidle/clock activity/idle/standby modes).\n");
		printf("\t    Note only enabled (running) modules can be "
			"audited. Disabled modules will be discarded "
			"(as not accessible).\n");

		printf("\n\tomapconf audit clkspeed\n");
		printf("\t    Audit modules clock speed at the current OPerating Points (OPP).\n");

		printf("\n\tomapconf audit statdep\n");
		printf("\t    Audit clock domain static dependencies "
			"settings.\n");

		printf("\n\tomapconf audit pads\n");
		printf("\t    Audit PAD configuration against HW bug causing "
			"potential glitch during OFF mode transition "
			"(OMAP44[60-70] only).\n");

		printf("\n\tomapconf audit avs [<mod>]\n");
		printf("\t    Audit Smart-Reflex Adaptive Voltage Scaling (AVS)"
			" settings at the current OPerating Points (OPP).\n");
		printf("\t    Supported <mod> (all assumed if omitted): "
			"mpu, iva, core.\n");

		printf("\n\tomapconf audit avs full\n");
		printf("\t    Audit all (mpu + iva + core) Smart-Reflex "
			"Adaptive Voltage Scaling (AVS) settings accross all "
			"MPU OPerating Points (OPP).\n");

		printf("\n\tomapconf audit full\n");
		printf("\t    Execute all previously listed power audits "
			"sequencially (dplls, sysconfig, clkspeed, statdep, "
			"pads, avs).\n");

		printf("\n\tomapconf audit perf [<duration>] [-d <delay>]\n");
		printf("\t    Audit performance (CPU Load, C-States, OPP, "
			"temperatures & memory data bus load).\n");
		printf("\t    Use optional <duration> to select audit length "
			"in seconds (default: 10s).\n");
		printf("\t    Use optional <delay> to select initial delay "
			"before audit start in seconds (default: 10s).\n");
		printf("\t    Audit data saved in "
			"'performance_audit_report.txt' file.\n");

		printf("\n\tomapconf audit <use case> [full_log]\n");
		printf("\t    Audit power settings for a particular Use Case "
			"(UC).\n");
		printf("\t    Audit summary results saved in "
			"<use case>_uc_audit_summary.txt file.\n");
		printf("\t    If [full_log] option is used, all audit details "
			"are also saved in <use case>_uc_audit_details.txt.\n");
		printf("\t    Supported <use case>:\n");
		printf("\t      - 'homescreen' (LCD ON, no application running,"
			" no user interaction)\n");
		printf("\t      - 'os_idle' (homescreen with LCD OFF)\n");
		printf("\t      - 'mp3' (MP3 playback to headphones, "
			"with LCD OFF)\n");
		printf("\t      - 'play720p' (720P audio-video playback)\n");
		printf("\t      - 'play1080p' (1080P audio-video playback)\n");
		printf("\t      - 'rec1080p' (1080P audio-video record)\n");
	}
}
