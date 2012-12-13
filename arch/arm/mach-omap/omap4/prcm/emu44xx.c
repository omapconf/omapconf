/*
 *
 * @Component			OMAPCONF
 * @Filename			emu44xx.c
 * @Description			OMAP4 EMU PRCM Definitions & Functions
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


#include <emu44xx.h>
#include <cm44xx.h>
#include <prm44xx.h>
#include <pwrdm44xx.h>
#include <module44xx.h>
#include <autoadjust_table.h>
#include <stdio.h>
#include <help.h>
#include <lib.h>
#include <mem.h>
#include <cpuinfo.h>
#include <string.h>


/* #define EMU44XX_DEBUG */
#ifdef EMU44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


#define PRCM_EMU_REG_TABLE_SIZE        7

static reg_table prcm_emu_reg_table[PRCM_EMU_REG_TABLE_SIZE];
static unsigned int init_done = 0;
static unsigned char emu_enabled = 0;

static int emu44xx_regtable_init(void);


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		emu44xx_name2addr
 * @BRIEF		retrieve physical address of a register, given its name.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		name: register name
 * @param[in, out]	addr: register address
 * @DESCRIPTION		retrieve physical address of a register, given its name.
 *//*------------------------------------------------------------------------ */
int emu44xx_name2addr(char *name, unsigned int *addr)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		emu44xx_regtable_init();

	return name2addr(name, addr, prcm_emu_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		emu44xx_dump
 * @BRIEF		dump EMU PRCM registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		dump EMU PRCM registers
 *//*------------------------------------------------------------------------ */
int emu44xx_dump(void)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		emu44xx_regtable_init();

	return dumpregs(prcm_emu_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		emu44xx_config_show
 * @BRIEF		analyze power configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		stream: output file stream
 * @DESCRIPTION		analyze power configuration
 *//*------------------------------------------------------------------------ */
int emu44xx_config_show(FILE *stream)
{
	unsigned int pm_pwstctrl;
	unsigned int pm_pwstst;
	unsigned int cm_clkstctrl;
	unsigned int rm_context;
	unsigned int cm_clkctrl;
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		emu44xx_regtable_init();

	if (mem_read(OMAP4430_PM_EMU_PWRSTCTRL, &pm_pwstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_PM_EMU_PWRSTST, &pm_pwstst) != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	if (mem_read(OMAP4430_CM_EMU_CLKSTCTRL, &cm_clkstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	ret = pwrdm44xx_config_show(stream, "EMU",
		OMAP4430_PM_EMU_PWRSTCTRL, pm_pwstctrl,
		OMAP4430_PM_EMU_PWRSTST, pm_pwstst);
	if (ret != 0)
		return ret;

	ret = clkdm44xx_config_show(stream, "EMU",
		OMAP4430_CM_EMU_CLKSTCTRL, cm_clkstctrl);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_EMU_DEBUGSS_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_EMU_DEBUGSS_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "DEBUGSS",
		OMAP4430_CM_EMU_DEBUGSS_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_EMU_DEBUGSS_CONTEXT, rm_context);

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		emu44xx_dependency_show
 * @BRIEF		analyse dependency configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		stream: output file stream
 * @DESCRIPTION		analyse dependency configuration
 *//*------------------------------------------------------------------------ */
int emu44xx_dependency_show(FILE *stream)
{
	unsigned int cm_dynamicdep;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		emu44xx_regtable_init();

	if (mem_read(OMAP4430_CM_EMU_DYNAMICDEP, &cm_dynamicdep) != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	dprintf("OMAP4430_CM_EMU_DYNAMICDEP = 0x%08X\n", cm_dynamicdep);
	fprintf(stream,
		"|--------------------------------------------------------|\n");
	fprintf(stream,
		"| EMU Domain Dependency Configuration | Static | Dynamic |\n");
	fprintf(stream,
		"|-------------------------------------|------------------|\n");
	fprintf(stream,
		"| %-35s | %-6s | %-7s |\n", "L3_2",
		"",
		((extract_bit(cm_dynamicdep, 6) == 1) ? "En" : "Dis"));
	fprintf(stream,
		"|--------------------------------------------------------|\n");
	fprintf(stream,
		"| %-44s | %-7d |\n", "Window Size",
		extract_bitfield(cm_dynamicdep, 24, 4));
	fprintf(stream,
		"|--------------------------------------------------------|\n");
	fprintf(stream,
		"\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		emu44xx_main
 * @BRIEF		PRCM EMU main menu
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		PRCM EMU main menu
 *//*------------------------------------------------------------------------ */
int emu44xx_main(int argc, char *argv[])
{
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (argc == 2) {
		if (!init_done)
			emu44xx_regtable_init();
		if (strcmp(argv[1], "dump") == 0) {
			ret = emu44xx_dump();
		} else if (strcmp(argv[1], "cfg") == 0) {
			ret = emu44xx_config_show(stdout);
		} else if (strcmp(argv[1], "dep") == 0) {
			ret = emu44xx_dependency_show(stdout);
		} else {
			help(HELP_PRCM);
			ret = OMAPCONF_ERR_ARG;
		}
	} else {
		help(HELP_PRCM);
		ret = OMAPCONF_ERR_ARG;
	}

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		emu44xx_regtable_init
 * @BRIEF		initialize regtable
 * @RETURNS		0
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		initialize regtable
 *//*------------------------------------------------------------------------ */
static int emu44xx_regtable_init(void)
{
	int i = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	/* Init PRCM registers table */
	strcpy(prcm_emu_reg_table[i].name, "PM_EMU_PWRSTCTRL");
	prcm_emu_reg_table[i++].addr = OMAP4430_PM_EMU_PWRSTCTRL;
	strcpy(prcm_emu_reg_table[i].name, "PM_EMU_PWRSTST");
	prcm_emu_reg_table[i++].addr = OMAP4430_PM_EMU_PWRSTST;
	strcpy(prcm_emu_reg_table[i].name, "RM_EMU_DEBUGSS_CONTEXT");
	prcm_emu_reg_table[i++].addr = OMAP4430_RM_EMU_DEBUGSS_CONTEXT;
	strcpy(prcm_emu_reg_table[i].name, "CM_EMU_CLKSTCTRL");
	prcm_emu_reg_table[i++].addr = OMAP4430_CM_EMU_CLKSTCTRL;
	strcpy(prcm_emu_reg_table[i].name, "CM_EMU_DYNAMICDEP");
	prcm_emu_reg_table[i++].addr = OMAP4430_CM_EMU_DYNAMICDEP;
	strcpy(prcm_emu_reg_table[i].name, "CM_EMU_DEBUGSS_CLKCTRL");
	prcm_emu_reg_table[i++].addr = OMAP4430_CM_EMU_DEBUGSS_CLKCTRL;
	strcpy(prcm_emu_reg_table[i].name, "END");
	prcm_emu_reg_table[i].addr = 0;
	dprintf("prcm_emu_reg_table last index=%d, size=%d\n", i, i + 1);

	init_done = 1;
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		emu44xx_enable
 * @BRIEF		Power ON EMU domain and instrumentation
 * @DESCRIPTION		Power ON EMU domain and instrumentation
 *			To be used when EMU/instrumentation HW is required but
 *			no debugger is attached to automatically power ON EMU
 *			domain.
 *//*------------------------------------------------------------------------ */
void emu44xx_enable(void)
{
	mem_write(OMAP4430_CM_EMU_CLKSTCTRL, 0x2);
	mem_write(OMAP4430_CM_L3INSTR_L3_3_CLKCTRL, 0x1);
	mem_write(OMAP4430_CM_L3INSTR_L3_INSTR_CLKCTRL, 0x1);
	mem_write(OMAP4430_PRM_PRM_PROFILING_CLKCTRL, 0x1);

	emu_enabled = 1;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		emu44xx_disable
 * @BRIEF		Power OFF EMU domain and instrumentation
 * @DESCRIPTION		Power OFF EMU domain and instrumentation
 *//*------------------------------------------------------------------------ */
void emu44xx_disable(void)
{
	mem_write(OMAP4430_PRM_PRM_PROFILING_CLKCTRL, 0x1);
	mem_write(OMAP4430_CM_L3INSTR_L3_3_CLKCTRL, 0);
	mem_write(OMAP4430_CM_L3INSTR_L3_INSTR_CLKCTRL, 0);
	mem_write(OMAP4430_CM_EMU_CLKSTCTRL, 0x3);

	emu_enabled = 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		emu44xx_is_enabled
 * @BRIEF		check if EMU domain is enabled
 * @RETURNS		0 if EMU domain is not enabled
 *			1 if EMU domain is enabled
 * @DESCRIPTION		check if EMU domain is enabled
 *//*------------------------------------------------------------------------ */
int emu44xx_is_enabled(void)
{
	return emu_enabled;
}
