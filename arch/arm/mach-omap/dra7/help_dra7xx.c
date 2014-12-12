/*
 *
 * @Component			OMAPCONF
 * @Filename			help_dra7xx.c
 * @Description			Help for DRA7 specific functions
 * @Author			Jin Zheng <j-zheng@ti.com>
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


#include <help_dra7xx.h>
#include <stdio.h>
#include <cpuinfo.h>
#include <tlv320aic3x.h>


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		help_dra7xx
 * @BRIEF		display help for DRA7-specific functions
 * @param[in]		cat: help category to display
 * @DESCRIPTION		display help for DRA7-specific functions
 *//*------------------------------------------------------------------------ */
void help_dra7xx(help_category cat, char *context)
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

	/* DRA7-specific commands */
	if ((cat == HELP_ALL) || (cat == HELP_EXPORT)) {
		printf("\n\tomapconf export ctt [<filename>]\n");
		printf("\t    Export PRCM registers to "
			"<filename> or stdout if omitted.\n");

		printf("\n\tomapconf ctt dump (alternative call of omapconf-export-ctt)\n");
		printf("\t    Export PRCM registers to stdout.\n");

		printf("\n\tomapconf ctt rd1\n");
		printf("\t    Export PRCM registers in rd1 format for Clock "
			"Tree Tool (CTT, <http://omappedia.org/wiki/CTT>).\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_VOLT)) {
		printf("\n\tomapconf set volt <rail> <voltage>\n");
		printf("\t    Set <rail> voltage to <voltage>.\n");
		printf("\t    Supported <rail>: mpu, iva, core, gpu, dspeve.\n");
		printf("\t    <voltage> is in volts.\n");
		printf("\t    ### WARNING ###: do it at your own risk. "
			"Unsupported voltage may crash or damage device!\n");
		printf("\t    e.g. omapconf set volt mpu 1.25\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_DPLL)) {
		printf("\n\tomapconf dump dpll [<dpll>]\n");
		printf("\t    RAW dump of <dpll> registers ('all' assumed if "
			"omitted).\n");
		printf("\t    Supported <dpll>: all, abe, core, ddr, dsp, eve, "
			"gmac, gpu, iva, mpu, pcieref, per, usb.\n");

		printf("\n\tomapconf show dpll [cfg]\n");
		printf("\t    Print the complete configuration of all DPLL "
			"([cfg] may be omitted).\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_AUDIT)) {
		printf("\n\tomapconf audit dpll [-d <dpll>] [-o <opp>]\n");
		printf("\t    Audit DPLL settings at selected OPP(s).\n");
		printf("\t    By default, audit ALL DPLLs at CURRENT OPP. "
			"Use optional '-d <dpll>' to select a given DPLL.\n");
		printf("\t    Supported <dpll> ('all' considered if omitted):"
			" abe, core, ddr, dsp, eve, gmac, gpu, iva, mpu,"
			" pcieref, per, usb.\n");
		printf("\t    Use optional '-o all' to run audit at all "
			"### MPU ### OPerating Points (OPP).\n");
		printf("\t    Use optional '-o <opp>' to force a particular "
			"### MPU ### OPerating Points (OPP). For example "
			"when MPU OPP is not correctly detected.\n");
		printf("\t    Supported <opp>: nom, od, high.\n");

		printf("\n\tomapconf audit crossbar <type> <module>\n");
		printf("\t    Dump crossbar mapping for type of module\n");
		printf("\t    'type' is irq - if omitted or 'all', show all\n");
		printf("\t    for type 'irq', 'module' is one of the following - if omitted or 'all', show all\n");
		printf("\t        mpu - chooses mpu crossbar\n");
		printf("\t        dsp - chooses dsp1 and dsp2\n");
		printf("\t        dsp1 - chooses dsp1\n");
		printf("\t        dsp2 - chooses dsp2\n");
		printf("\t        ipu - chooses ipu1 and ipu2\n");
		printf("\t        ipu1 - chooses ipu1\n");
		printf("\t        ipu2 - chooses ipu2\n");
		printf("\t        eve - chooses eve1 and eve2\n");
		printf("\t        eve1 - chooses eve1\n");
		printf("\t        eve2 - chooses eve2\n");
		printf("\t        pruss - chooses pruss1 and pruss2\n");
		printf("\t        pruss1 - chooses pruss1\n");
		printf("\t        pruss2 - chooses pruss2\n");
		printf("\t    NOTE:\n");
		printf("\t        pruss modules are supported only on AM57xx SoCs, behavior undefined on others\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_PRCM)) {
		printf("\n\tomapconf dump prcm [<pwrdm>]\n");
		printf("\t    Dump PRCM Registers related to <pwrdm> power"
			" domain ('all' assumed if omitted).\n");
		printf("\t    Supported <pwrdm>: all, cam, core, coreaon, "
			"ckgen, dev, dsp, dss, emu, eve, gpu, instr, ipu, "
			"iva, l3init, l4per, mpu, rtc, vpe, wkupaon.\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_TEMPERATURE)) {
		printf("\n\tomapconf show temp [<sensor>]\n");
		printf("\t    Print temperature reported by thermal driver, in celcius degrees.\n");
		printf("\t    Supported <sensor>: mpu, gpu, core, dspeve, iva,  all.\n");
		printf("\t    If <sensor> is omitted or <sensor> = all, all"
			"available sensors will be printed in a table, with both"
			"celcius and fahrenheit degrees.\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_HWTEMPERATURE)) {
		printf("\n\tomapconf show hwtemp [<sensor>]\n");
		printf("\t    Print temperature reported by <sensor>, in celcius degrees.\n");
		printf("\t    Supported <sensor>: mpu, gpu, core, dspeve, iva, all.\n");
		printf("\t    If <sensor> is omitted or <sensor> = all, all"
			"available sensors will be printed in a table, with both"
			"celcius and fahrenheit degrees.\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_SOC_OPP)) {
		printf("\n\tomapconf show opp\n");
		printf("\t    Print DRA7 current OPerating Points (OPP) "
			"(voltage, frequency) for MPU/IVA/GPU/DSPEVE/CORE voltage "
			"domains), including main modules frequencies.\n");
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
	}

	if ((cat == HELP_ALL) || (cat == HELP_AUDIOIC)) {
		printf("\n\tomapconf dump audioic\n");
		printf("\t    Dump tlv320aic3106 (Audio IC) registers.\n");
		printf("\t    Default audioic is in bus %u with address 0x%02x\n",
		       TLV320AIC3X_I2C_DFLT_BUS, TLV320AIC3X_I2C_VALID_ADDR1);

		printf("\n\tomapconf dump audioic 'bus' 0x'chip\n");
		printf("\t    Dump tlv320aic3106 (Audio IC) registers:\n");
		printf("\t    'i2cbus' is decimal value.\n");
		printf("\t    'chip-address' is hexadecimal value.\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_MCASP)) {
		printf("\n\tomapconf dump mcasp<n>\n");
		printf("\t    Dump McASP instance 'n' registers.\n");
		printf("\t    'n' is the instance id: 1, 2, ..., 8.\n");

		printf("\n\tomapconf show mcasp<n>\n");
		printf("\t    Show McASP instance 'n' configuration.\n");
		printf("\t    'n' is the instance id: 1, 2, ..., 8.\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_CROSSBAR)) {
		printf("\n\tomapconf dump crossbar <type> <module>\n");
		printf("\t    Dump crossbar mapping for type of module\n");
		printf("\t    'type' is irq - if omitted or 'all', show all\n");
		printf("\t    for type 'irq', 'module' is one of the following - if omitted or 'all', show all\n");
		printf("\t        mpu - chooses mpu crossbar\n");
		printf("\t        dsp - chooses dsp1 and dsp2\n");
		printf("\t        dsp1 - chooses dsp1\n");
		printf("\t        dsp2 - chooses dsp2\n");
		printf("\t        ipu - chooses ipu1 and ipu2\n");
		printf("\t        ipu1 - chooses ipu1\n");
		printf("\t        ipu2 - chooses ipu2\n");
		printf("\t        eve - chooses eve1 and eve2\n");
		printf("\t        eve1 - chooses eve1\n");
		printf("\t        eve2 - chooses eve2\n");
		printf("\t        pruss - chooses pruss1 and pruss2\n");
		printf("\t        pruss1 - chooses pruss1\n");
		printf("\t        pruss2 - chooses pruss2\n");
		printf("\t    NOTE:\n");
		printf("\t        pruss modules are supported only on AM57xx SoCs, behavior undefined on others\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_ABB)) {
		printf("\n\tomapconf dump abb\n");
		printf("\t    Dump Adaptive Body-Bias (ABB) registers.\n");

		printf("\n\tomapconf show abb\n");
		printf("\t    Print Adaptive Body-Bias (ABB) configuration\n");
	}
}
