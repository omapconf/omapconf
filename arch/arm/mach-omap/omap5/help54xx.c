/*
 *
 * @Component			OMAPCONF
 * @Filename			help54xx.c
 * @Description			Help for OMAP5 specific functions
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


#include <help54xx.h>
#include <stdio.h>
#include <cpuinfo.h>


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		help54xx
 * @BRIEF		display help for OMAP5-specific functions
 * @param[in]		cat: help category to display
 * @DESCRIPTION		display help for OMAP5-specific functions
 *//*------------------------------------------------------------------------ */
void help54xx(help_category cat, char *context)
{
	if (cat >= HELP_CATEGORY_MAX) {
		fprintf(stderr, "%s(): incorrect category!!! (%u)\n",
			__func__, cat);
		return;
	}
	if (context == NULL) {
		fprintf(stderr, "%s(): context == NULL!!!\n", __func__);
		return;
	}

	/* OMAP5-specific commands */
	if ((cat == HELP_ALL) || (cat == HELP_EXPORT)) {
		printf("\n\tomapconf export [xml] [<file>]\n");
		printf("\t    Export OMAP registers in XML format into <file> "
			"([xml] may be omitted). Use date to generate default "
			"file name if <file> is omitted).\n");
		printf("\t    Exported registers configuration can be imported "
			"later on via 'omapconf --import <file>'.\n");
		printf("\t    Register values will then be read from <file>"
			" instead of registers when available.\n");

		printf("\n\tomapconf export ctt [<filename>]\n");
		printf("\t    Export PRCM registers in .rd1 format for Clock "
			"Tree Tool (CTT, <http://omappedia.org/wiki/CTT>), to "
			"<filename> or stdout if omitted.\n");

		#if 0 /* FIXME */
		printf("\n\tomapconf export pct [filename]\n");
		printf("\t    Export PRCM registers in .rd1 format for Pad "
			"Configuration Tool (PCT, "
			"<http://www.ti.com/general/docs/wtbu/wtbudocumen"
			"tcenter.tsp?templateId=6123&navigationId=12804#62>),"
			" to [filename] or stdout if omitted.\n");
		#endif
	}

	if ((cat == HELP_ALL) || (cat == HELP_SOC_OPP)) {
		printf("\n\tomapconf show opp\n");
		printf("\t    Print OMAP5 current OPerating Points (OPP) "
			"(voltage, frequency) for MPU/MM/CORE voltage "
			"domains), including main modules frequencies.\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_SOC_PWST)) {
		printf("\n\tomapconf show pwst\n");
		printf("\t    Print OMAP power status (OPP, voltage/power/clock"
			" domains states, modules frequency and status).\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_VOLT)) {
		printf("\n\tomapconf set volt <rail> <voltage>\n");
		printf("\t    Set <rail> voltage to <voltage>.\n");
		printf("\t    Supported <rail>: mpu, mm, core.\n");
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

	if ((cat == HELP_ALL) || (cat == HELP_TEMPERATURE)) {
		printf("\n\tomapconf show temp [<sensor>]\n");
		printf(
			"\t    Print temperature reported by thermal driver for <sensor>, in celcius degrees.\n");
		printf(
			"\t    Supported <sensor>: mpu, mpu_hotspot, gpu, gpu_hotspot, core, pcb, case, mem1, mem2, charger, all.\n");
		printf(
			"\t    If <sensor> is omitted or <sensor> = all, all available sensors will be printed in a table, with both celcius and fahrenheit degrees.\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_HWTEMPERATURE)) {
		printf("\n\tomapconf show hwtemp [<sensor>]\n");
		printf("\t    Print temperature reported by <sensor> by reading hwregister directly, in celcius degrees.\n");
		printf("\t    Supported <sensor>: mpu, gpu, core, all.\n");
		printf("\t    If <sensor> is omitted or <sensor> = all, all available sensors will be printed in a table, with both celcius and fahrenheit degrees.\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_DPLL)) {
		printf("\n\tomapconf dump dpll [<dpll>]\n");
		printf("\t    RAW dump of <dpll> registers ('all' assumed if "
			"omitted).\n");
		printf("\t    Supported <dpll>: mpu, iva, core, per, abe, usb, "
			"unipro1, unipro2, all.\n");

		printf("\n\tomapconf show dpll [cfg]\n");
		printf("\t    Print the complete configuration of all DPLL "
			"([cfg] may be omitted).\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_PRCM)) {
		printf("\n\tomapconf dump prcm [<pwrdm>]\n");
		printf(
			"\t    Dump PRCM Registers related to <pwrdm> power domain ('all' assumed if omitted).\n");
		if (cpu_revision_get() == REV_ES1_0)
			printf(
				"\t    Supported <pwrdm>: mpu, core, dsp, dss, cam, gpu, iva, l4per, abe, l3init, dev, emu, instr, ckgen, wkupaon, coreaon, all.\n");
		else
			printf(
				"\t    Supported <pwrdm>: mpu, core, dsp, dss, cam, gpu, iva, abe, l3init, dev, emu, instr, ckgen, wkupaon, coreaon, all.\n");


		printf("\n\tomapconf show prcm [<pwrdm>] [<clkdm>] [cfg]\n");
		printf(
			"\t    Print PRCM power configuration and status of <pwrdm> power domain ('all' assumed if omitted). [cfg] may also be omitted.\n");
		if (cpu_revision_get() == REV_ES1_0) {
			printf(
				"\t    Supported <pwrdm>: mpu, core, dsp, dss, cam, gpu, iva, l4per, abe, l3init, emu, wkupaon, coreaon, all.\n");
			printf(
				"\t    Note for CORE power domain, it is possible to select a single clock domain, providing optional <clkdm>.\n");
			printf(
				"\t    Supported <clkdm>: l4cfg, emif, ipu, l3main1, l3main2, l3instr, c2c, dma, mipiext.\n");
		} else {
			printf(
				"\t    Supported <pwrdm>: mpu, core, dsp, dss, cam, gpu, iva, abe, l3init, emu, wkupaon, coreaon, all.\n");
			printf(
				"\t    Note for CORE power domain, it is possible to select a single clock domain, providing optional <clkdm>.\n");
			printf(
				"\t    Supported <clkdm>: l4cfg, emif, ipu, l3main1, l3main2, l3instr, l4per, l4sec, c2c, dma, mipiext.\n");
		}
	}

	if ((cat == HELP_ALL) || (cat == HELP_PRCM) || (cat == HELP_STATDEP)) {
		printf("\n\tomapconf dump prcm dep\n");
		printf("\t    Dump all clock domain dependency registers.\n");

		printf("\n\tomapconf show prcm [statdep | dyndep | dep] [cfg]"
			"\n");
		printf("\t    Print all PRCM dependency configuration between "
			"clock domains ([cfg] may be omitted).\n");
		printf("\t    Use 'statdep' to print static dependency "
			"configuration only.\n");
		printf("\t    Use 'dyndep' to print dynamic dependency "
			"configuration only .\n");
		printf("\t    Use 'dep' to print both static and dynamic "
			"dependency configurations.\n");

		printf("\n\tomapconf [set | clear] prcm statdep <from> [<to>]"
			"\n");
		printf("\t    [Set (enable) | Clear (disable)] static "
			"dependency from clock domain <from> towards clock "
			"domain <to>.\n");
		printf("\t    Supported <from>/<to>: emu, wkupaon, coreaon, "
			"cam, l4cfg, emif, ipu, l3main2, l3instr, l3main1, c2c,"
			" dma, mipiext, dss, custefuse, l3init, l4per, l4sec, "
			"abe, dsp, gpu, iva, mpu, all.\n");
		printf("\t    If <to> = 'all' or <to> is omitted, then all "
			"static dependencies from clock domain <from> will be "
			"[set (enabled) | cleared (disabled)] in a row.\n");
		printf("\t    ###WARNING###: use this command at your own "
			"risk, may crash the platform!\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_PRCM) || (cat == HELP_ABB)) {
		printf("\n\tomapconf dump prcm abb\n");
		printf("\t    Dump Adaptive Body-Bias (ABB) registers.\n");

		printf("\n\tomapconf show prcm abb [cfg]\n");
		printf("\t    Print Adaptive Body-Bias (ABB) configuration "
			"([cfg] may be omitted).\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_SR)) {
		printf("\n\tomapconf dump sr [<mod>]\n");
		printf("\t    Dump Smart-Reflex Adaptive Voltage Scaling (AVS) "
			"<mod> registers ('all' assumed if omitted).\n");
		printf("\t    Supported <mod>: mpu, mm, core, all.\n");

		printf("\n\tomapconf show sr [cfg]\n");
		printf("\t    Print Smart-Reflex Adaptive Voltage Scaling (AVS)"
			" configuration, including Voltage Controller (VC) "
			"and Voltage Processor (VP) configurations "
			"([cfg] may be omitted).\n");

		printf("\n\tomapconf show sr status\n");
		printf("\t    Print Smart-Reflex Adaptive Voltage Scaling (AVS)"
			" convergence status.\n");
	}


#if 0 /* FIXME */
	if ((cat == HELP_ALL) || (cat == HELP_MPUSS)) {
		autoadjust_table_strncpy(table, row, 0,
			"MPU Sub-System Configuration");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf mpuss scu dump");
		autoadjust_table_strncpy(table, row, 2,
			"MPUSS SCU register dump.");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf mpuss scu cfg");
		autoadjust_table_strncpy(table, row, 2,
			"MPUSS SCU configuration analyzis.");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf mpuss l2c dump");
		autoadjust_table_strncpy(table, row, 2,
			"MPUSS L2 Cache Controller register dump.");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf mpuss gic dump");
		autoadjust_table_strncpy(table, row, 2,
			"MPUSS Interrupt Controller register dump.");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf mpuss gic cfg");
		autoadjust_table_strncpy(table, row, 2,
			"MPUSS Interrupt Controller configuration analyzis.");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf mpuss wkg dump");
		autoadjust_table_strncpy(table, row, 2,
			"MPUSS WakeUpGen register dump.");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf mpuss scm dump");
		autoadjust_table_strncpy(table, row, 2,
			"MPUSS SCM register dump.");
		row += 2;
	}

	if ((cat == HELP_ALL) || (cat == HELP_WKDEP)) {
		autoadjust_table_strncpy(table, row, 0,
			"Wakeup Dependencies (WKDEP)");
		row++;
		autoadjust_table_strncpy(table, row, 1, "omapconf wkdep dump");
		autoadjust_table_strncpy(table, row, 2,
			"PRCM WKDEP registers dump.");
		row++;
		autoadjust_table_strncpy(table, row, 1, "omapconf wkdep cfg");
		autoadjust_table_strncpy(table, row, 2,
			"Show PRCM WKDEP Configuration.");
		row += 2;
	}

	if ((cat == HELP_ALL) || (cat == HELP_AVS)) {
		autoadjust_table_strncpy(table, row, 0, "Smart-Reflex (AVS)");
		row++;
		autoadjust_table_strncpy(table, row, 1, "omapconf sr dump");
		autoadjust_table_strncpy(table, row, 2,
			"Smart-Reflex registers dump.");
		row++;
		autoadjust_table_strncpy(table, row, 1, "omapconf sr cfg");
		autoadjust_table_strncpy(table, row, 2,
			"Show Smart-Reflex Configuration.");
		row += 2;
	}
#endif

#if 0 /* FIXME */
	if ((cat == HELP_ALL) || (cat == HELP_DISPLAY)) {
		autoadjust_table_strncpy(table, row, 0,
			"DISPLAY");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf display dump all");
		autoadjust_table_strncpy(table, row, 2,
			"All Display Subsystem registers dump.");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf display dump all > dump.txt");
		autoadjust_table_strncpy(table, row, 2,
			"Save All Display Subsystem registers dump into "
			"dump.txt.");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf display dump dss");
		autoadjust_table_strncpy(table, row, 2,
			"DSS registers dump.");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf display dump dsi1");
		autoadjust_table_strncpy(table, row, 2,
			"DSI1 Protocol Engine registers dump.");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf display dump dsi1_pll");
		autoadjust_table_strncpy(table, row, 2,
			"DSI1 PLL registers dump.");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf display dump dsi1_phy");
		autoadjust_table_strncpy(table, row, 2,
			"DSI1 PHY registers dump.");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf display dump dsi2");
		autoadjust_table_strncpy(table, row, 2,
			"DSI2 Protocol Engine registers dump.");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf display dump dsi2_pll");
		autoadjust_table_strncpy(table, row, 2,
			"DSI2 PLL registers dump.");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf display dump dsi2_phy");
		autoadjust_table_strncpy(table, row, 2,
			"DSI2 PHY registers dump.");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf display dump rfbi");
		autoadjust_table_strncpy(table, row, 2,
			"RFBI I/F registers dump.");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf display dump venc");
		autoadjust_table_strncpy(table, row, 2,
			"Video Encoder I/F registers dump.");
		row += 2;
	}
#endif

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

	if ((cat == HELP_ALL) || (cat == HELP_CTRLMOD)) {
		printf("\n\tomapconf dump ctrlmod [<mod>]\n");
		printf("\t    Dump CONTROL MODULE <mod> registers ('all' "
			"assumed if omitted).\n");
		printf("\t    Supported <mod>: core, core_pad, wkup, wkup_pad, "
			"all.\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_HWOBS)) {
		printf("\n\tomapconf setup hwobs [pinmux | prcm | mpuss]"
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
		printf("\t    Dump TWL6035 (Power Management IC) registers.\n");

#if 0 /* FIXME */
		autoadjust_table_strncpy(table, row, 1,
			"omapconf twl6030 cfg");
		autoadjust_table_strncpy(table, row, 2,
			"Show TWL6030 supported configurations.");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf twl6030 ldocfg");
		autoadjust_table_strncpy(table, row, 2,
			"Show TWL6030 LDO configuration.");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf twl6030 smpscfg");
		autoadjust_table_strncpy(table, row, 2,
			"Show TWL6030 SMPS configuration.");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf twl6030 rescfg");
		autoadjust_table_strncpy(table, row, 2,
			"Show TWL6030 Resource dependency configuration.");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf twl6030 devpwrgrpstat");
		autoadjust_table_strncpy(table, row, 2,
			"Show TWL6030 Device level power group status.");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf twl6030 setpwrgrp [MOD|CON|APP] [ON|OFF]");
		autoadjust_table_strncpy(table, row, 2,
			"SET TWL6030 Device level power group. {CAREFUL}");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf twl6030 reset");
		autoadjust_table_strncpy(table, row, 2,
			"*RESET* TWL6030 Device(bypasses OMAP reset){CAREFUL}");
		row++;
#endif
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
		printf("\t      - read 32kHz register, clock_gettime(CLOCK_MONONOTONIC, ...), gettimeofday()\n");
		printf("\t      - print value of each + offset from 32kHz to each clock in us\n");
	}

#if 0 /* FIXME */
	if ((cat == HELP_ALL) || (cat == HELP_EXPORT)) {
		autoadjust_table_strncpy(table, row, 0,
			"PAD Configuration Tool (PCT)");
		row++;
		autoadjust_table_strncpy(table, row, 1, "omapconf pct dump");
		autoadjust_table_strncpy(table, row, 2,
			"CONTROL Module registers dump for PCT.");
		row++;
		autoadjust_table_strncpy(table, row, 1, "omapconf pct rd1");
		autoadjust_table_strncpy(table, row, 2,
			"Create *.rd1 file that can be read by PCT.");
		row += 2;
	}
#endif

	if ((cat == HELP_ALL) || (cat == HELP_AUDIT)) {
		printf("\n\tomapconf audit dpll [-d <dpll>] [-o <opp>]\n");
		printf("\t    Audit DPLL settings at selected OPP(s).\n");
		printf("\t    By default, audit ALL DPLLs at CURRENT OPP. "
			"Use optional '-d <dpll>' to select a given DPLL.\n");
		printf("\t    Supported <dpll> ('all' considered if omitted):"
			" mpu, iva, core, per, abe, usb, unipro1, unipro2, all."
			"\n");
		printf("\t    Use optional '-o all' to run audit at all "
			"### MPU ### OPerating Points (OPP).\n");
		printf("\t    Use optional '-o <opp>' to force a particular "
			"### MPU ### OPerating Points (OPP). For example "
			"when MPU OPP is not correctly detected.\n");
		printf("\t    Supported <opp>: dpll_casc, low, nom, high, "
			"speedbin.\n");

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

		printf("\n\tomapconf audit io ### PRELIMINARY ###\n");
		printf("\t    Audit IO PAD configuration.\n");

		printf("\n\tomapconf audit full [-f <filename>]\n");
		printf("\t    Execute all previously listed power audits "
			"sequencially (dplls, sysconfig, clkspeed, statdep, "
			"pads).\n");
		printf("\t    Use optional <filename> to select audit report "
			"file name (\"full_audit_report.txt\" if omitted).\n");

		printf("\n\tomapconf audit perf [<duration>] [-d <delay>]\n");
		printf("\t    Audit performance (CPU Load, C-States, OPP, "
			"temperatures & memory data bus load).\n");
		printf("\t    Use optional <duration> to select audit length "
			"in seconds (default: 10s).\n");
		printf("\t    Use optional <delay> to select initial delay "
			"before audit start in seconds (default: 10s).\n");
		printf("\t    Audit data saved in "
			"'performance_audit_report.txt' file.\n");

#if 0 /* FIXME */
		autoadjust_table_strncpy(table, row, 0,
			"Low-power Use Case Audit");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf audit os_idle [full_log]");
		autoadjust_table_strncpy(table, row, 2,
			"OS Idle UC power settings audit.");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf audit mp3 [full_log]");
		autoadjust_table_strncpy(table, row, 2,
			"MP3 Playback UC power settings audit.");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf audit play720p [full_log]");
		autoadjust_table_strncpy(table, row, 2,
			"720p AV Playback UC power settings audit.");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf audit play1080p [full_log]");
		autoadjust_table_strncpy(table, row, 2,
			"1080p AV Playback UC power settings audit.");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf audit rec1080p [full_log]");
		autoadjust_table_strncpy(table, row, 2,
			"1080p AV Record UC power settings audit.");
		row++;
		autoadjust_table_strncpy(table, row, 2,
			"Note: audit summary saved in *_uc_audit_summary.txt "
			"file.");
		row++;
		autoadjust_table_strncpy(table, row, 2,
			"  If 'full_log' option is added, audit details "
			"are also");
		row++;
		autoadjust_table_strncpy(table, row, 2,
			"saved in *_uc_audit_details.txt.");
#endif
	}

	if ((cat == HELP_ALL) || (cat == HELP_TRACE)) {
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
			"\t    Capture predefined items (CPUs Load, MPU/GPU/L3 OPP Changes, EMIF bandwidth & temperatures (bandgap, PCB, hotspot) or custom (user defined) items over time.\n");
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

#if 0 /* FIXME */
		autoadjust_table_strncpy(table, row, 0, "PMI Power Trace");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf trace pwrdm [duration]");
		autoadjust_table_strncpy(table, row, 2,
			"Collect power domain transitions trace & statistics.");
		row++;
		autoadjust_table_strncpy(table, row, 2,
			"  Use optional 'duration' to select trace length");
		row++;
		autoadjust_table_strncpy(table, row, 2,
			"    in seconds (default: 10s).");
		row++;
		autoadjust_table_strncpy(table, row, 1,
			"omapconf trace opp [duration]");
		autoadjust_table_strncpy(table, row, 2,
			"Collect OPP changes trace & statistics.");
		row++;
		autoadjust_table_strncpy(table, row, 2,
			"  Use optional 'duration' to select trace length");
		row++;
		autoadjust_table_strncpy(table, row, 2,
			"    in seconds (default: 10s).");
		row++;
#endif
	}
}
