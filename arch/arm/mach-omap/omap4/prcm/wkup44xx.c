/*
 *
 * @Component			OMAPCONF
 * @Filename			wkup44xx.c
 * @Description			OMAP4 WKUP PRCM Definitions & Functions
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


#include <wkup44xx.h>
#include <cm44xx.h>
#include <prm44xx.h>
#include <pwrdm44xx.h>
#include <module44xx.h>
#include <lib44xx.h>
#include <help.h>
#include <cm44xx.h>
#include <prm44xx.h>
#include <lib.h>
#include <mem.h>
#include <cpuinfo.h>
#include <string.h>


/* #define WKUP44XX_DEBUG */
#ifdef WKUP44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

#define PRCM_WKUP_REG_TABLE_SIZE 25

reg_table prcm_wkup_reg_table[PRCM_WKUP_REG_TABLE_SIZE];
static unsigned int init_done = 0;

static int wkup44xx_regtable_init(void);


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		wkup44xx_name2addr
 * @BRIEF		retrieve physical address of a register, given its name.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		name: register name
 * @param[in,out]	addr: register address
 * @DESCRIPTION		retrieve physical address of a register, given its name.
 *//*------------------------------------------------------------------------ */
int wkup44xx_name2addr(char *name, unsigned int *addr)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		wkup44xx_regtable_init();

	return name2addr(name, addr, prcm_wkup_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		wkup44xx_config_show
 * @BRIEF		analyze WKUP power configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		analyze WKUP power configuration
 *//*------------------------------------------------------------------------ */
int wkup44xx_config_show(FILE *stream)
{
	unsigned int cm_clkstctrl;
	unsigned int rm_context;
	unsigned int cm_clkctrl;
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_ARG);

	if (!init_done)
		wkup44xx_regtable_init();

	/* Clock Domain Configuration */
	if (mem_read(OMAP4430_CM_WKUP_CLKSTCTRL, &cm_clkstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = clkdm44xx_config_show(stream, "WKUP",
		OMAP4430_CM_WKUP_CLKSTCTRL, cm_clkstctrl);
	if (ret != 0)
		return ret;

	/* Module Power Configuration */
	if (mem_read(OMAP4430_CM_WKUP_L4WKUP_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_WKUP_L4WKUP_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "L4WKUP",
		OMAP4430_CM_WKUP_L4WKUP_CLKCTRL, cm_clkctrl,
		OMAP4430_CM_WKUP_L4WKUP_CLKCTRL, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_WKUP_WDT1_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_WKUP_WDT1_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "WDT1",
		OMAP4430_CM_WKUP_WDT1_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_WKUP_WDT1_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_WKUP_WDT2_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_WKUP_WDT2_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "WDT2",
		OMAP4430_CM_WKUP_WDT2_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_WKUP_WDT2_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_WKUP_GPIO1_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_WKUP_GPIO1_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "GPIO1",
		OMAP4430_CM_WKUP_GPIO1_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_WKUP_GPIO1_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_WKUP_TIMER1_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_WKUP_TIMER1_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "TIMER1",
		OMAP4430_CM_WKUP_TIMER1_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_WKUP_TIMER1_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_WKUP_TIMER12_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_WKUP_TIMER12_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "TIMER12",
		OMAP4430_CM_WKUP_TIMER12_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_WKUP_TIMER12_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_WKUP_SYNCTIMER_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_WKUP_SYNCTIMER_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "SYNCTIMER",
		OMAP4430_CM_WKUP_SYNCTIMER_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_WKUP_SYNCTIMER_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_WKUP_USIM_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_WKUP_USIM_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "USIM",
		OMAP4430_CM_WKUP_USIM_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_WKUP_USIM_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_WKUP_SARRAM_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_WKUP_SARRAM_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "SARRAM",
		OMAP4430_CM_WKUP_SARRAM_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_WKUP_SARRAM_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_WKUP_KEYBOARD_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_WKUP_KEYBOARD_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "KEYBOARD",
		OMAP4430_CM_WKUP_KEYBOARD_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_WKUP_KEYBOARD_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_WKUP_RTC_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_WKUP_RTC_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "RTC",
		OMAP4430_CM_WKUP_RTC_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_WKUP_RTC_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_WKUP_BANDGAP_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "BANDGAP",
		OMAP4430_CM_WKUP_BANDGAP_CLKCTRL, cm_clkctrl,
		0, 0); /* no context register */
	if (ret != 0)
		return ret;

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		wkup44xx_dump
 * @BRIEF		dump PRCM WKUP registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		dump PRCM WKUP registers
 *//*------------------------------------------------------------------------ */
int wkup44xx_dump(void)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_ARG);

	if (!init_done)
		wkup44xx_regtable_init();

	return dumpregs(prcm_wkup_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		wkup44xx_main
 * @BRIEF		PRCM WKUP main menu
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		PRCM WKUP main menu
 *//*------------------------------------------------------------------------ */
int wkup44xx_main(int argc, char *argv[])
{
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (argc == 2) {
		if (!init_done)
			wkup44xx_regtable_init();
		if (strcmp(argv[1], "dump") == 0) {
			ret = dumpregs(prcm_wkup_reg_table);
		} else if (strcmp(argv[1], "cfg") == 0) {
			ret = wkup44xx_config_show(stdout);
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
 * @FUNCTION		wkup44xx_regtable_init
 * @BRIEF		initialize regtable
 * @RETURNS		0
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		initialize regtable
 *//*------------------------------------------------------------------------ */
static int wkup44xx_regtable_init(void)
{
	int i = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	/* Init PRCM registers table */
	strcpy(prcm_wkup_reg_table[i].name, "RM_WKUP_L4WKUP_CONTEXT");
	prcm_wkup_reg_table[i++].addr = OMAP4430_RM_WKUP_L4WKUP_CONTEXT;
	strcpy(prcm_wkup_reg_table[i].name, "RM_WKUP_WDT1_CONTEXT");
	prcm_wkup_reg_table[i++].addr = OMAP4430_RM_WKUP_WDT1_CONTEXT;
	strcpy(prcm_wkup_reg_table[i].name, "RM_WKUP_WDT2_CONTEXT");
	prcm_wkup_reg_table[i++].addr = OMAP4430_RM_WKUP_WDT2_CONTEXT;
	strcpy(prcm_wkup_reg_table[i].name, "RM_WKUP_GPIO1_CONTEXT");
	prcm_wkup_reg_table[i++].addr = OMAP4430_RM_WKUP_GPIO1_CONTEXT;
	strcpy(prcm_wkup_reg_table[i].name, "RM_WKUP_TIMER1_CONTEXT");
	prcm_wkup_reg_table[i++].addr = OMAP4430_RM_WKUP_TIMER1_CONTEXT;
	strcpy(prcm_wkup_reg_table[i].name, "RM_WKUP_TIMER12_CONTEXT");
	prcm_wkup_reg_table[i++].addr = OMAP4430_RM_WKUP_TIMER12_CONTEXT;
	strcpy(prcm_wkup_reg_table[i].name, "RM_WKUP_SYNCTIMER_CONTEXT");
	prcm_wkup_reg_table[i++].addr = OMAP4430_RM_WKUP_SYNCTIMER_CONTEXT;
	strcpy(prcm_wkup_reg_table[i].name, "RM_WKUP_USIM_CONTEXT");
	prcm_wkup_reg_table[i++].addr = OMAP4430_RM_WKUP_USIM_CONTEXT;
	strcpy(prcm_wkup_reg_table[i].name, "RM_WKUP_SARRAM_CONTEXT");
	prcm_wkup_reg_table[i++].addr = OMAP4430_RM_WKUP_SARRAM_CONTEXT;
	strcpy(prcm_wkup_reg_table[i].name, "RM_WKUP_KEYBOARD_CONTEXT");
	prcm_wkup_reg_table[i++].addr = OMAP4430_RM_WKUP_KEYBOARD_CONTEXT;
	strcpy(prcm_wkup_reg_table[i].name, "RM_WKUP_RTC_CONTEXT");
	prcm_wkup_reg_table[i++].addr = OMAP4430_RM_WKUP_RTC_CONTEXT;
	strcpy(prcm_wkup_reg_table[i].name, "CM_WKUP_CLKSTCTRL");
	prcm_wkup_reg_table[i++].addr = OMAP4430_CM_WKUP_CLKSTCTRL;
	strcpy(prcm_wkup_reg_table[i].name, "CM_WKUP_L4WKUP_CLKCTRL");
	prcm_wkup_reg_table[i++].addr = OMAP4430_CM_WKUP_L4WKUP_CLKCTRL;
	strcpy(prcm_wkup_reg_table[i].name, "CM_WKUP_WDT1_CLKCTRL");
	prcm_wkup_reg_table[i++].addr = OMAP4430_CM_WKUP_WDT1_CLKCTRL;
	strcpy(prcm_wkup_reg_table[i].name, "CM_WKUP_WDT2_CLKCTRL");
	prcm_wkup_reg_table[i++].addr = OMAP4430_CM_WKUP_WDT2_CLKCTRL;
	strcpy(prcm_wkup_reg_table[i].name, "CM_WKUP_GPIO1_CLKCTRL");
	prcm_wkup_reg_table[i++].addr = OMAP4430_CM_WKUP_GPIO1_CLKCTRL;
	strcpy(prcm_wkup_reg_table[i].name, "CM_WKUP_TIMER1_CLKCTRL");
	prcm_wkup_reg_table[i++].addr = OMAP4430_CM_WKUP_TIMER1_CLKCTRL;
	strcpy(prcm_wkup_reg_table[i].name, "CM_WKUP_TIMER12_CLKCTRL");
	prcm_wkup_reg_table[i++].addr = OMAP4430_CM_WKUP_TIMER12_CLKCTRL;
	strcpy(prcm_wkup_reg_table[i].name, "CM_WKUP_SYNCTIMER_CLKCTRL");
	prcm_wkup_reg_table[i++].addr = OMAP4430_CM_WKUP_SYNCTIMER_CLKCTRL;
	strcpy(prcm_wkup_reg_table[i].name, "CM_WKUP_USIM_CLKCTRL");
	prcm_wkup_reg_table[i++].addr = OMAP4430_CM_WKUP_USIM_CLKCTRL;
	strcpy(prcm_wkup_reg_table[i].name, "CM_WKUP_SARRAM_CLKCTRL");
	prcm_wkup_reg_table[i++].addr = OMAP4430_CM_WKUP_SARRAM_CLKCTRL;
	strcpy(prcm_wkup_reg_table[i].name, "CM_WKUP_KEYBOARD_CLKCTRL");
	prcm_wkup_reg_table[i++].addr = OMAP4430_CM_WKUP_KEYBOARD_CLKCTRL;
	strcpy(prcm_wkup_reg_table[i].name, "CM_WKUP_RTC_CLKCTRL");
	prcm_wkup_reg_table[i++].addr = OMAP4430_CM_WKUP_RTC_CLKCTRL;
	strcpy(prcm_wkup_reg_table[i].name, "CM_WKUP_BANDGAP_CLKCTRL");
	prcm_wkup_reg_table[i++].addr = OMAP4430_CM_WKUP_BANDGAP_CLKCTRL;
	strcpy(prcm_wkup_reg_table[i].name, "END");
	prcm_wkup_reg_table[i].addr = 0;
	dprintf("prcm_wkup_reg_table last index=%d, size=%d\n", i, i + 1);

	init_done = 1;
	return 0;
}
