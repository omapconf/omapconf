/*
 *
 * @Component			OMAPCONF
 * @Filename			gfx44xx.c
 * @Description			OMAP4 GFX PRCM Definitions & Functions
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


#include <gfx44xx.h>
#include <mem.h>
#include <cm44xx.h>
#include <prm44xx.h>
#include <pwrdm44xx.h>
#include <module44xx.h>
#include <help.h>
#include <lib.h>
#include <cpuinfo.h>
#include <string.h>


#define PRCM_GFX_REG_TABLE_SIZE 8


reg_table prcm_gfx_reg_table[PRCM_GFX_REG_TABLE_SIZE];
static unsigned int init_done = 0;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		gfx44xx_regtable_init
 * @BRIEF		initialize regtable
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		initialize regtable
 *//*------------------------------------------------------------------------ */
int gfx44xx_regtable_init(void)
{
	int i = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	/* Init PRCM registers table */
	strcpy(prcm_gfx_reg_table[i].name, "PM_GFX_PWRSTCTRL");
	prcm_gfx_reg_table[i++].addr = OMAP4430_PM_GFX_PWRSTCTRL;
	strcpy(prcm_gfx_reg_table[i].name, "PM_GFX_PWRSTST");
	prcm_gfx_reg_table[i++].addr = OMAP4430_PM_GFX_PWRSTST;
	strcpy(prcm_gfx_reg_table[i].name, "RM_GFX_GFX_CONTEXT");
	prcm_gfx_reg_table[i++].addr = OMAP4430_RM_GFX_GFX_CONTEXT;
	strcpy(prcm_gfx_reg_table[i].name, "CM_GFX_CLKSTCTRL");
	prcm_gfx_reg_table[i++].addr = OMAP4430_CM_GFX_CLKSTCTRL;
	strcpy(prcm_gfx_reg_table[i].name, "CM_GFX_GFX_CLKCTRL");
	prcm_gfx_reg_table[i++].addr = OMAP4430_CM_GFX_GFX_CLKCTRL;
	strcpy(prcm_gfx_reg_table[i].name, "CM_GFX_STATICDEP");
	prcm_gfx_reg_table[i++].addr = OMAP4430_CM_GFX_STATICDEP;
	strcpy(prcm_gfx_reg_table[i].name, "CM_GFX_DYNAMICDEP");
	prcm_gfx_reg_table[i++].addr = OMAP4430_CM_GFX_DYNAMICDEP;
	strcpy(prcm_gfx_reg_table[i].name, "END");
	prcm_gfx_reg_table[i].addr = 0;

	init_done = 1;
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		gfx44xx_name2addr
 * @BRIEF		retrieve physical address of a register, given its name.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		name: register name
 * @param[in,out]	addr: register address
 * @DESCRIPTION		retrieve physical address of a register, given its name.
 *//*------------------------------------------------------------------------ */
int gfx44xx_name2addr(char *name, unsigned int *addr)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		gfx44xx_regtable_init();

	return name2addr(name, addr, prcm_gfx_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		gfx44xx_config_show
 * @BRIEF		analyze GFX power configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output file stream
 * @DESCRIPTION		analyze GFX power configuration
 *//*------------------------------------------------------------------------ */
int gfx44xx_config_show(FILE *stream)
{
	unsigned int pm_pwstctrl;
	unsigned int pm_pwstst;
	unsigned int cm_clkstctrl;
	unsigned int rm_context;
	unsigned int cm_clkctrl;
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		gfx44xx_regtable_init();

	/* Power Domain Configuration */
	if (mem_read(OMAP4430_PM_GFX_PWRSTCTRL, &pm_pwstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_PM_GFX_PWRSTST, &pm_pwstst) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = pwrdm44xx_config_show(stream, "GFX",
		OMAP4430_PM_GFX_PWRSTCTRL, pm_pwstctrl,
		OMAP4430_PM_GFX_PWRSTST, pm_pwstst);
	if (ret != 0)
		return ret;

	/* Clock Domain Configuration */
	if (mem_read(OMAP4430_CM_GFX_CLKSTCTRL, &cm_clkstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = clkdm44xx_config_show(stream, "GFX",
		OMAP4430_CM_GFX_CLKSTCTRL, cm_clkstctrl);
	if (ret != 0)
		return ret;

	/* Module Power Configuration */
	if (mem_read(OMAP4430_CM_GFX_GFX_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_GFX_GFX_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "GFX",
		OMAP4430_CM_GFX_GFX_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_GFX_GFX_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		gfx44xx_dependency_show
 * @BRIEF		analyse GFX dependency configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		stream: output file stream
 * @DESCRIPTION		analyse GFX dependency configuration
 *//*------------------------------------------------------------------------ */
int gfx44xx_dependency_show(FILE *stream)
{
	unsigned int cm_staticdep;
	unsigned int cm_dynamicdep;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		gfx44xx_regtable_init();

	if (mem_read(OMAP4430_CM_GFX_STATICDEP, &cm_staticdep) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_CM_GFX_DYNAMICDEP, &cm_dynamicdep) != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	fprintf(stream,
		"|--------------------------------------------------------|\n");
	fprintf(stream,
		"| GFX Domain Dependency Configuration | Static | Dynamic |\n");
	fprintf(stream,
		"|-------------------------------------|------------------|\n");
	fprintf(stream,
		"| %-35s | %-6s | %-7s |\n", "IVAHD",
		((extract_bit(cm_staticdep, 2) == 1) ? "En" : "Dis"), "");
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "MEM IF",
		((extract_bit(cm_staticdep, 4) == 1) ? "En" : "Dis"), "");
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "L3_1",
		((extract_bit(cm_staticdep, 5) == 1) ? "En" : "Dis"),
		((extract_bit(cm_dynamicdep, 5) == 1) ? "En" : "Dis"));
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "L3_2",
		((extract_bit(cm_staticdep, 6) == 1) ? "En" : "Dis"), "");
	fprintf(stream,
		"|--------------------------------------------------------|\n");
	fprintf(stream, "\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		gfx44xx_dump
 * @BRIEF		dump PRCM GFX registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		dump PRCM GFX registers
 *//*------------------------------------------------------------------------ */
int gfx44xx_dump(void)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		gfx44xx_regtable_init();

	return dumpregs(prcm_gfx_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		gfx44xx_main
 * @BRIEF		main entry point for omap4 gfx
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		main entry point for omap4 gfx
 *//*------------------------------------------------------------------------ */
int gfx44xx_main(int argc, char *argv[])
{
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (argc == 2) {
		if (!init_done)
			gfx44xx_regtable_init();
		if (strcmp(argv[1], "dump") == 0) {
			ret = dumpregs(prcm_gfx_reg_table);
		} else if (strcmp(argv[1], "cfg") == 0) {
			ret = gfx44xx_config_show(stdout);
		} else if (strcmp(argv[1], "dep") == 0) {
			ret = gfx44xx_dependency_show(stdout);
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
