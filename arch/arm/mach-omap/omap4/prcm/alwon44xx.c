/*
 *
 * @Component			OMAPCONF
 * @Filename			alwon44xx.c
 * @Description			OMAP4 PRCM ALWON Definitions & Functions
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


#include <alwon44xx.h>
#include <cm44xx.h>
#include <prm44xx.h>
#include <module44xx.h>
#include <help.h>
#include <lib.h>
#include <mem.h>
#include <cpuinfo.h>
#include <string.h>


/* #define ALWON44XX_DEBUG */
#ifdef ALWON44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


#define PRCM_ALWON_REG_TABLE_SIZE        11


static reg_table prcm_alwon_reg_table[PRCM_ALWON_REG_TABLE_SIZE];
static unsigned int init_done = 0;

static int alwon44xx_regtable_init(void);


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		alwon44xx_name2addr
 * @BRIEF		retrieve physical address of a register, given its name.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		name: register name
 * @param[in, out]	addr: register address
 * @DESCRIPTION		retrieve physical address of a register, given its name.
 *//*------------------------------------------------------------------------ */
int alwon44xx_name2addr(char *name, unsigned int *addr)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		alwon44xx_regtable_init();

	return name2addr(name, addr, prcm_alwon_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		alwon44xx_dump
 * @BRIEF		dump PRCM ALWON registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		dump PRCM ALWON registers
 *//*------------------------------------------------------------------------ */
int alwon44xx_dump(void)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		alwon44xx_regtable_init();

	return dumpregs(prcm_alwon_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		alwon44xx_config_show
 * @BRIEF		analyze ALWON power configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		stream: output file stream
 * @DESCRIPTION		analyze ALWON power configuration
 *//*------------------------------------------------------------------------ */
int alwon44xx_config_show(FILE *stream)
{
	unsigned int cm_clkstctrl;
	unsigned int rm_context;
	unsigned int cm_clkctrl;
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		alwon44xx_regtable_init();

	if (mem_read(OMAP4430_CM_ALWON_CLKSTCTRL, &cm_clkstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	ret = clkdm44xx_config_show(stream, "ALWON",
		OMAP4430_CM_ALWON_CLKSTCTRL, cm_clkstctrl);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_ALWON_SR_MPU_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_ALWON_SR_MPU_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "SR_MPU",
		OMAP4430_CM_ALWON_SR_MPU_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_ALWON_SR_MPU_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_ALWON_SR_IVA_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_ALWON_SR_IVA_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "SR_IVA",
		OMAP4430_CM_ALWON_SR_IVA_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_ALWON_SR_IVA_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_ALWON_SR_CORE_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_ALWON_SR_CORE_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "SR_CORE",
		OMAP4430_CM_ALWON_SR_CORE_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_ALWON_SR_CORE_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		alwon44xx_main
 * @BRIEF		alwon functions main entry point
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		alwon functions main entry point
 *//*------------------------------------------------------------------------ */
int alwon44xx_main(int argc, char *argv[])
{
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (argc == 2) {
		if (!init_done)
			alwon44xx_regtable_init();
		if (strcmp(argv[1], "dump") == 0) {
			ret = alwon44xx_dump();
		} else if (strcmp(argv[1], "cfg") == 0) {
			ret = alwon44xx_config_show(stdout);
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
 * @FUNCTION		alwon44xx_regtable_init
 * @BRIEF		initialize regtable
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		initialize regtable
 *//*------------------------------------------------------------------------ */
static int alwon44xx_regtable_init(void)
{
	int i = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	/* Init PRCM registers table */
	strcpy(prcm_alwon_reg_table[i].name, "PM_ALWON_SR_MPU_WKDEP");
	prcm_alwon_reg_table[i++].addr = OMAP4430_PM_ALWON_SR_MPU_WKDEP;
	strcpy(prcm_alwon_reg_table[i].name, "RM_ALWON_SR_MPU_CONTEXT");
	prcm_alwon_reg_table[i++].addr = OMAP4430_RM_ALWON_SR_MPU_CONTEXT;
	strcpy(prcm_alwon_reg_table[i].name, "PM_ALWON_SR_IVA_WKDEP");
	prcm_alwon_reg_table[i++].addr = OMAP4430_PM_ALWON_SR_IVA_WKDEP;
	strcpy(prcm_alwon_reg_table[i].name, "RM_ALWON_SR_IVA_CONTEXT");
	prcm_alwon_reg_table[i++].addr = OMAP4430_RM_ALWON_SR_IVA_CONTEXT;
	strcpy(prcm_alwon_reg_table[i].name, "PM_ALWON_SR_CORE_WKDEP");
	prcm_alwon_reg_table[i++].addr = OMAP4430_PM_ALWON_SR_CORE_WKDEP;
	strcpy(prcm_alwon_reg_table[i].name, "RM_ALWON_SR_CORE_CONTEXT");
	prcm_alwon_reg_table[i++].addr = OMAP4430_RM_ALWON_SR_CORE_CONTEXT;
	strcpy(prcm_alwon_reg_table[i].name, "CM_ALWON_CLKSTCTRL");
	prcm_alwon_reg_table[i++].addr = OMAP4430_CM_ALWON_CLKSTCTRL;
	strcpy(prcm_alwon_reg_table[i].name, "CM_ALWON_SR_MPU_CLKCTRL");
	prcm_alwon_reg_table[i++].addr = OMAP4430_CM_ALWON_SR_MPU_CLKCTRL;
	strcpy(prcm_alwon_reg_table[i].name, "CM_ALWON_SR_IVA_CLKCTRL");
	prcm_alwon_reg_table[i++].addr = OMAP4430_CM_ALWON_SR_IVA_CLKCTRL;
	strcpy(prcm_alwon_reg_table[i].name, "CM_ALWON_SR_CORE_CLKCTRL");
	prcm_alwon_reg_table[i++].addr = OMAP4430_CM_ALWON_SR_CORE_CLKCTRL;
	strcpy(prcm_alwon_reg_table[i].name, "END");
	prcm_alwon_reg_table[i].addr = 0;

	dprintf("prcm_alwon_reg_table last index=%d, size=%d\n", i, i + 1);

	init_done = 1;
	return 0;
}
