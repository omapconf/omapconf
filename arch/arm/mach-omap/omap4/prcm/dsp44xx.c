/*
 *
 * @Component			OMAPCONF
 * @Filename			dsp44xx.c
 * @Description			OMAP4 DSP PRCM Definitions & Functions
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


#include <dpll.h>
#include <dpll44xx.h>
#include <help.h>
#include <cm44xx.h>
#include <prm44xx.h>
#include <pwrdm44xx.h>
#include <module44xx.h>
#include <lib.h>
#include <mem.h>
#include <cpuinfo.h>
#include <string.h>

/* #define DSP44XX_DEBUG */
#ifdef DSP44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

reg_table prcm_dsp_reg_table[28];
static unsigned int init_done = 0;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dsp44xx_regtable_init
 * @BRIEF		initialize reg_table fields (not possible statically)
 * @RETURNS		0
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		initialize reg_table fields (not possible statically)
 *//*------------------------------------------------------------------------ */
static int dsp44xx_regtable_init(void)
{
	int i = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	/* Init PRCM DSP registers table */
	strcpy(prcm_dsp_reg_table[i].name, "PM_DSP_PWRSTCTRL");
	prcm_dsp_reg_table[i++].addr = OMAP4430_PM_DSP_PWRSTCTRL;
	strcpy(prcm_dsp_reg_table[i].name, "PM_DSP_PWRSTST");
	prcm_dsp_reg_table[i++].addr = OMAP4430_PM_DSP_PWRSTST;
	strcpy(prcm_dsp_reg_table[i].name, "RM_DSP_DSP_CONTEXT");
	prcm_dsp_reg_table[i++].addr = OMAP4430_RM_DSP_DSP_CONTEXT;
	strcpy(prcm_dsp_reg_table[i].name, "RM_DSP_RSTCTRL");
	prcm_dsp_reg_table[i++].addr = OMAP4430_RM_DSP_RSTCTRL;
	strcpy(prcm_dsp_reg_table[i].name, "RM_DSP_RSTST");
	prcm_dsp_reg_table[i++].addr = OMAP4430_RM_DSP_RSTST;
	strcpy(prcm_dsp_reg_table[i].name, "CM_DSP_CLKSTCTRL");
	prcm_dsp_reg_table[i++].addr = OMAP4430_CM_DSP_CLKSTCTRL;
	strcpy(prcm_dsp_reg_table[i].name, "CM_DSP_DSP_CLKCTRL");
	prcm_dsp_reg_table[i++].addr = OMAP4430_CM_DSP_DSP_CLKCTRL;
	strcpy(prcm_dsp_reg_table[i].name, "CM_DSP_STATICDEP");
	prcm_dsp_reg_table[i++].addr = OMAP4430_CM_DSP_STATICDEP;
	strcpy(prcm_dsp_reg_table[i].name, "CM_DSP_DYNAMICDEP");
	prcm_dsp_reg_table[i++].addr = OMAP4430_CM_DSP_DYNAMICDEP;
	strcpy(prcm_dsp_reg_table[i].name, "END");
	prcm_dsp_reg_table[i].addr = 0;

	init_done = 1;
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dsp44xx_name2addr
 * @BRIEF		retrieve physical address of a register, given its name.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		name: register name
 * @param[in, out]	addr: register address
 * @DESCRIPTION		retrieve physical address of a register, given its name.
 *//*------------------------------------------------------------------------ */
int dsp44xx_name2addr(char *name, unsigned int *addr)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		dsp44xx_regtable_init();

	return name2addr(name, addr, prcm_dsp_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dsp44xx_config_show
 * @BRIEF		analyze DSP power configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		stream: output file stream
 * @DESCRIPTION		analyze DSP power configuration
 *//*------------------------------------------------------------------------ */
int dsp44xx_config_show(FILE *stream)
{
	unsigned int pm_pwstctrl;
	unsigned int pm_pwstst;
	unsigned int cm_clkstctrl;
	unsigned int rm_context;
	unsigned int cm_clkctrl;
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		dsp44xx_regtable_init();

	if (mem_read(OMAP4430_CM_DSP_DSP_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_DSP_DSP_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	/* Power Domain Configuration */
	if (mem_read(OMAP4430_PM_DSP_PWRSTCTRL, &pm_pwstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_PM_DSP_PWRSTST, &pm_pwstst) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = pwrdm44xx_config_show(stream, "DSP",
		OMAP4430_PM_DSP_PWRSTCTRL, pm_pwstctrl,
		OMAP4430_PM_DSP_PWRSTST, pm_pwstst);
	if (ret != 0)
		return ret;

	/* Clock Domain Configuration */
	if (mem_read(OMAP4430_CM_DSP_CLKSTCTRL, &cm_clkstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = clkdm44xx_config_show(stream, "DSP",
		OMAP4430_CM_DSP_CLKSTCTRL, cm_clkstctrl);
	if (ret != 0)
		return ret;

	/* Module Power Configuration */
	ret = mod44xx_config_show(stream, "DSP",
		OMAP4430_CM_DSP_DSP_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_DSP_DSP_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dsp44xx_dependency_show
 * @BRIEF		analyse DSP dependency configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		stream: output file stream
 * @DESCRIPTION		analyse DSP dependency configuration
 *//*------------------------------------------------------------------------ */
int dsp44xx_dependency_show(FILE *stream)
{
	unsigned int cm_dsp_staticdep;
	unsigned int cm_dsp_dynamicdep;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		dsp44xx_regtable_init();

	if (mem_read(OMAP4430_CM_DSP_STATICDEP, &cm_dsp_staticdep) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_CM_DSP_DYNAMICDEP, &cm_dsp_dynamicdep) != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	fprintf(stream,
		"|--------------------------------------------------------|\n");
	fprintf(stream,
		"| DSP Domain Dependency Configuration | Static | Dynamic |\n");
	fprintf(stream,
		"|-------------------------------------|------------------|\n");
	fprintf(stream,
		"| %-35s | %-6s | %-7s |\n", "IVAHD",
		((extract_bit(cm_dsp_staticdep, 2) == 1) ? "En" : "Dis"),
		((extract_bit(cm_dsp_dynamicdep, 2) == 1) ? "En" : "Dis"));
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "ABE",
		((extract_bit(cm_dsp_staticdep, 3) == 1) ? "En" : "Dis"),
		((extract_bit(cm_dsp_dynamicdep, 3) == 1) ? "En" : "Dis"));
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "MEM IF",
		((extract_bit(cm_dsp_staticdep, 4) == 1) ? "En" : "Dis"),
		"");
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "L3_1",
		((extract_bit(cm_dsp_staticdep, 5) == 1) ? "En" : "Dis"),
		((extract_bit(cm_dsp_dynamicdep, 5) == 1) ? "En" : "Dis"));
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "L3_2",
		((extract_bit(cm_dsp_staticdep, 6) == 1) ? "En" : "Dis"),
		"");
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "L3INIT",
		((extract_bit(cm_dsp_staticdep, 7) == 1) ? "En" : "Dis"),
		"");
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "ISS",
		((extract_bit(cm_dsp_staticdep, 9) == 1) ? "En" : "Dis"),
		"");
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "L4CFG",
		((extract_bit(cm_dsp_staticdep, 12) == 1) ? "En" : "Dis"),
		"");
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "L4PER",
		((extract_bit(cm_dsp_staticdep, 13) == 1) ? "En" : "Dis"),
		"");
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "L4WKUP",
		((extract_bit(cm_dsp_staticdep, 15) == 1) ? "En" : "Dis"),
		"");
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "ALWONCORE",
		((extract_bit(cm_dsp_staticdep, 16) == 1) ? "En" : "Dis"),
		"");
	fprintf(stream,
		"|--------------------------------------------------------|\n");
	fprintf(stream, "| %-44s | %-7d |\n", "Window Size",
		extract_bitfield(cm_dsp_dynamicdep, 24, 4));
	fprintf(stream,
		"|--------------------------------------------------------|\n");

	fprintf(stream, "\n");
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dsp44xx_dump
 * @BRIEF		dump PRCM DSP registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		dump PRCM DSP registers
 *//*------------------------------------------------------------------------ */
int dsp44xx_dump(void)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		dsp44xx_regtable_init();

	return dumpregs(prcm_dsp_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dsp44xx_main
 * @BRIEF		PRCM DSP main menu
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		PRCM DSP main menu
 *//*------------------------------------------------------------------------ */
int dsp44xx_main(int argc, char *argv[])
{
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (argc == 2) {
		if (!init_done)
			dsp44xx_regtable_init();
		if (strcmp(argv[1], "dump") == 0) {
			ret = dumpregs(prcm_dsp_reg_table);
		} else if (strcmp(argv[1], "cfg") == 0) {
			ret = dsp44xx_config_show(stdout);
		} else if (strcmp(argv[1], "dep") == 0) {
			ret = dsp44xx_dependency_show(stdout);
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
