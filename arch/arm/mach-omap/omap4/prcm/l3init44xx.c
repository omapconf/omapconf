/*
 *
 * @Component			OMAPCONF
 * @Filename			l3init44xx.c
 * @Description			OMAP4 L3INIT PRCM Definitions & Functions
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


#include <l3init44xx.h>
#include <cm44xx.h>
#include <prm44xx.h>
#include <pwrdm44xx.h>
#include <module44xx.h>
#include <help.h>
#include <lib.h>
#include <mem.h>
#include <cpuinfo.h>
#include <string.h>


/* #define L3INIT44XX_DEBUG */
#ifdef L3INIT44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


#define PRCM_L3INIT_REG_TABLE_SIZE        34


static reg_table prcm_l3init_reg_table[PRCM_L3INIT_REG_TABLE_SIZE];
static unsigned int init_done = 0;

static int l3init44xx_regtable_init(void);


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		l3init44xx_name2addr
 * @BRIEF		retrieve physical address of a register, given its name.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		name: register name
 * @param[in, out]	addr: register address
 * @DESCRIPTION		retrieve physical address of a register, given its name.
 *//*------------------------------------------------------------------------ */
int l3init44xx_name2addr(char *name, unsigned int *addr)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		l3init44xx_regtable_init();

	return name2addr(name, addr, prcm_l3init_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		l3init44xx_dump
 * @BRIEF		dump L3INIT PRCM registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		dump L3INIT PRCM registers
 *//*------------------------------------------------------------------------ */
int l3init44xx_dump(void)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		l3init44xx_regtable_init();

	return dumpregs(prcm_l3init_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		l3init44xx_config_show
 * @BRIEF		analyze power configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		stream: output file stream
 * @DESCRIPTION		analyze power configuration
 *//*------------------------------------------------------------------------ */
int l3init44xx_config_show(FILE *stream)
{
	unsigned int pm_pwstctrl;
	unsigned int pm_pwstst;
	unsigned int cm_clkstctrl;
	unsigned int rm_context;
	unsigned int cm_clkctrl;
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		l3init44xx_regtable_init();

	if (mem_read(OMAP4430_PM_L3INIT_PWRSTCTRL, &pm_pwstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_PM_L3INIT_PWRSTST, &pm_pwstst) != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	if (mem_read(OMAP4430_CM_L3INIT_CLKSTCTRL, &cm_clkstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	ret = pwrdm44xx_config_show(stream, "L3INIT",
		OMAP4430_PM_L3INIT_PWRSTCTRL, pm_pwstctrl,
		OMAP4430_PM_L3INIT_PWRSTST, pm_pwstst);
	if (ret != 0)
		return ret;

	ret = clkdm44xx_config_show(stream, "L3INIT",
		OMAP4430_CM_L3INIT_CLKSTCTRL, cm_clkstctrl);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L3INIT_MMC1_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L3INIT_MMC1_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "MMC1",
		OMAP4430_CM_L3INIT_MMC1_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L3INIT_MMC1_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L3INIT_MMC2_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L3INIT_MMC2_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "MMC2",
		OMAP4430_CM_L3INIT_MMC2_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L3INIT_MMC2_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L3INIT_HSI_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L3INIT_HSI_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "HSI",
		OMAP4430_CM_L3INIT_HSI_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L3INIT_HSI_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (cpu_is_omap4430() && (cpu_revision_get() == REV_ES1_0)) {
		if (mem_read(OMAP4430_CM_L3INIT_UNIPRO1_CLKCTRL,
			&cm_clkctrl) != 0)
			return OMAPCONF_ERR_REG_ACCESS;
		if (mem_read(OMAP4430_RM_L3INIT_UNIPRO1_CONTEXT,
			&rm_context) != 0)
			return OMAPCONF_ERR_REG_ACCESS;
		ret = mod44xx_config_show(stream,
			"UNIPRO1",
			OMAP4430_CM_L3INIT_UNIPRO1_CLKCTRL, cm_clkctrl,
			OMAP4430_RM_L3INIT_UNIPRO1_CONTEXT, rm_context);
		if (ret != 0)
			return ret;
	}

	if (mem_read(OMAP4430_CM_L3INIT_USB_HOST_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L3INIT_USB_HOST_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "HSUSBHOST",
		OMAP4430_CM_L3INIT_USB_HOST_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L3INIT_USB_HOST_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L3INIT_USB_OTG_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L3INIT_USB_OTG_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "HSUSBOTG",
		OMAP4430_CM_L3INIT_USB_OTG_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L3INIT_USB_OTG_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L3INIT_USB_TLL_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L3INIT_USB_TLL_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "HSUSBTLL",
		OMAP4430_CM_L3INIT_USB_TLL_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L3INIT_USB_TLL_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L3INIT_P1500_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L3INIT_P1500_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "P1500",
		OMAP4430_CM_L3INIT_P1500_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L3INIT_P1500_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (!cpu_is_omap4470()) {
		if (mem_read(OMAP4430_CM_L3INIT_USB_HOST_FS_CLKCTRL,
			&cm_clkctrl) != 0)
			return OMAPCONF_ERR_REG_ACCESS;
		if (mem_read(OMAP4430_RM_L3INIT_USB_HOST_FS_CONTEXT,
			&rm_context) != 0)
			return OMAPCONF_ERR_REG_ACCESS;
		ret = mod44xx_config_show(stream,
			"FSUSB",
			OMAP4430_CM_L3INIT_USB_HOST_FS_CLKCTRL, cm_clkctrl,
			OMAP4430_RM_L3INIT_USB_HOST_FS_CONTEXT,
			rm_context);
		if (ret != 0)
			return ret;
	}
	if (mem_read(OMAP4430_CM_L3INIT_USBPHYOCP2SCP_CLKCTRL,
		&cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L3INIT_USBPHYOCP2SCP_CONTEXT,
		&rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "USBPHY",
		OMAP4430_CM_L3INIT_USBPHYOCP2SCP_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L3INIT_USBPHYOCP2SCP_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		l3init44xx_dependency_show
 * @BRIEF		analyse dependency configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		stream: output file stream
 * @DESCRIPTION		analyse dependency configuration
 *//*------------------------------------------------------------------------ */
int l3init44xx_dependency_show(FILE *stream)
{
	unsigned int cm_dynamicdep, cm_staticdep;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		l3init44xx_regtable_init();

	if (mem_read(OMAP4430_CM_L3INIT_STATICDEP, &cm_staticdep) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_CM_L3INIT_DYNAMICDEP, &cm_dynamicdep) != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	fprintf(stream,
		"|------------------------------------------------------------"
		"|\n");
	fprintf(stream,
		"| L3_INIT Domain Dependency Configuration | Static | Dynamic "
		"|\n");
	fprintf(stream,
		"|-----------------------------------------|------------------"
		"|\n");
	fprintf(stream, "| %-39s | %-6s | %-7s |\n", "IVAHD",
		((extract_bit(cm_staticdep, 2) == 1) ? " En" : "Dis"), "");
	fprintf(stream, "| %-39s | %-6s | %-7s |\n", "ABE",
		((extract_bit(cm_staticdep, 3) == 1) ? " En" : "Dis"), "");
	fprintf(stream, "| %-39s | %-6s | %-7s |\n", "MEMIF",
		((extract_bit(cm_staticdep, 4) == 1) ? " En" : "Dis"), "");
	fprintf(stream, "| %-39s | %-6s | %-7s |\n", "L3_1",
		((extract_bit(cm_staticdep, 5) == 1) ? " En" : "Dis"),
		((extract_bit(cm_dynamicdep, 5) == 1) ? " En" : "Dis"));
	fprintf(stream, "| %-39s | %-6s | %-7s |\n", "L3_2",
		((extract_bit(cm_staticdep, 6) == 1) ? " En" : "Dis"),
		((extract_bit(cm_dynamicdep, 6) == 1) ? " En" : "Dis"));
	fprintf(stream, "| %-39s | %-6s | %-7s |\n", "L4CFG",
		((extract_bit(cm_staticdep, 12) == 1) ? " En" : "Dis"), "");
	fprintf(stream, "| %-39s | %-6s | %-7s |\n", "L4PER",
		((extract_bit(cm_staticdep, 13) == 1) ? " En" : "Dis"), "");
	fprintf(stream, "| %-39s | %-6s | %-7s |\n", "L4WKUP",
		((extract_bit(cm_staticdep, 15) == 1) ? " En" : "Dis"), "");
	fprintf(stream,
		"|------------------------------------------------------------"
		"|\n");
	fprintf(stream, "\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		l3init44xx_main
 * @BRIEF		PRCM L3INIT main menu
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		PRCM L3INIT main menu
 *//*------------------------------------------------------------------------ */
int l3init44xx_main(int argc, char *argv[])
{
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (argc == 2) {
		if (!init_done)
			l3init44xx_regtable_init();
		if (strcmp(argv[1], "dump") == 0) {
			ret = l3init44xx_dump();
		} else if (strcmp(argv[1], "cfg") == 0) {
			ret = l3init44xx_config_show(stdout);
		} else if (strcmp(argv[1], "dep") == 0) {
			ret = l3init44xx_dependency_show(stdout);
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
 * @FUNCTION		l3init44xx_regtable_init
 * @BRIEF		initialize regtable
 * @RETURNS		0
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		initialize regtable
 *//*------------------------------------------------------------------------ */
static int l3init44xx_regtable_init(void)
{
	int i = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	/* Init PRCM registers table */
	strcpy(prcm_l3init_reg_table[i].name, "PM_L3INIT_PWRSTCTRL");
	prcm_l3init_reg_table[i++].addr = OMAP4430_PM_L3INIT_PWRSTCTRL;
	strcpy(prcm_l3init_reg_table[i].name, "PM_L3INIT_PWRSTST");
	prcm_l3init_reg_table[i++].addr = OMAP4430_PM_L3INIT_PWRSTST;
	strcpy(prcm_l3init_reg_table[i].name, "PM_L3INIT_MMC1_WKDEP");
	prcm_l3init_reg_table[i++].addr = OMAP4430_PM_L3INIT_MMC1_WKDEP;
	strcpy(prcm_l3init_reg_table[i].name, "RM_L3INIT_MMC1_CONTEXT");
	prcm_l3init_reg_table[i++].addr = OMAP4430_RM_L3INIT_MMC1_CONTEXT;
	strcpy(prcm_l3init_reg_table[i].name, "PM_L3INIT_MMC2_WKDEP");
	prcm_l3init_reg_table[i++].addr = OMAP4430_PM_L3INIT_MMC2_WKDEP;
	strcpy(prcm_l3init_reg_table[i].name, "RM_L3INIT_MMC2_CONTEXT");
	prcm_l3init_reg_table[i++].addr = OMAP4430_RM_L3INIT_MMC2_CONTEXT;
	strcpy(prcm_l3init_reg_table[i].name, "PM_L3INIT_HSI_WKDEP");
	prcm_l3init_reg_table[i++].addr = OMAP4430_PM_L3INIT_HSI_WKDEP;
	strcpy(prcm_l3init_reg_table[i].name, "RM_L3INIT_HSI_CONTEXT");
	prcm_l3init_reg_table[i++].addr = OMAP4430_RM_L3INIT_HSI_CONTEXT;
	if (cpu_is_omap4430() && (cpu_revision_get() == REV_ES1_0)) {
		strcpy(prcm_l3init_reg_table[i].name,
			"PM_L3INIT_UNIPRO1_WKDEP");
		prcm_l3init_reg_table[i++].addr =
			OMAP4430_PM_L3INIT_UNIPRO1_WKDEP;
		strcpy(prcm_l3init_reg_table[i].name,
			"RM_L3INIT_UNIPRO1_CONTEXT");
		prcm_l3init_reg_table[i++].addr =
			OMAP4430_RM_L3INIT_UNIPRO1_CONTEXT;
	}
	strcpy(prcm_l3init_reg_table[i].name, "PM_L3INIT_HSUSBHOST_WKDEP");
	prcm_l3init_reg_table[i++].addr = OMAP4430_PM_L3INIT_USB_HOST_WKDEP;
	strcpy(prcm_l3init_reg_table[i].name, "RM_L3INIT_HSUSBHOST_CONTEXT");
	prcm_l3init_reg_table[i++].addr = OMAP4430_RM_L3INIT_USB_HOST_CONTEXT;
	strcpy(prcm_l3init_reg_table[i].name, "PM_L3INIT_HSUSBOTG_WKDEP");
	prcm_l3init_reg_table[i++].addr = OMAP4430_PM_L3INIT_USB_OTG_WKDEP;
	strcpy(prcm_l3init_reg_table[i].name, "RM_L3INIT_HSUSBOTG_CONTEXT");
	prcm_l3init_reg_table[i++].addr = OMAP4430_RM_L3INIT_USB_OTG_CONTEXT;
	strcpy(prcm_l3init_reg_table[i].name, "PM_L3INIT_HSUSBTLL_WKDEP");
	prcm_l3init_reg_table[i++].addr = OMAP4430_PM_L3INIT_USB_TLL_WKDEP;
	strcpy(prcm_l3init_reg_table[i].name, "RM_L3INIT_HSUSBTLL_CONTEXT");
	prcm_l3init_reg_table[i++].addr = OMAP4430_RM_L3INIT_USB_TLL_CONTEXT;
	strcpy(prcm_l3init_reg_table[i].name, "RM_L3INIT_P1500_CONTEXT");
	prcm_l3init_reg_table[i++].addr = OMAP4430_RM_L3INIT_P1500_CONTEXT;
	if (!cpu_is_omap4470()) {
		strcpy(prcm_l3init_reg_table[i].name, "PM_L3INIT_FSUSB_WKDEP");
		prcm_l3init_reg_table[i++].addr =
			OMAP4430_PM_L3INIT_USB_HOST_FS_WKDEP;
		strcpy(prcm_l3init_reg_table[i].name,
			"RM_L3INIT_FSUSB_CONTEXT");
		prcm_l3init_reg_table[i++].addr =
			OMAP4430_RM_L3INIT_USB_HOST_FS_CONTEXT;
	}
	strcpy(prcm_l3init_reg_table[i].name, "RM_L3INIT_GPIO5_CONTEXT");
	prcm_l3init_reg_table[i++].addr =
		OMAP4430_RM_L3INIT_USBPHYOCP2SCP_CONTEXT;
	strcpy(prcm_l3init_reg_table[i].name, "CM_L3INIT_CLKSTCTRL");
	prcm_l3init_reg_table[i++].addr = OMAP4430_CM_L3INIT_CLKSTCTRL;
	strcpy(prcm_l3init_reg_table[i].name, "CM_L3INIT_STATICDEP");
	prcm_l3init_reg_table[i++].addr = OMAP4430_CM_L3INIT_STATICDEP;
	strcpy(prcm_l3init_reg_table[i].name, "CM_L3INIT_DYNAMICDEP");
	prcm_l3init_reg_table[i++].addr = OMAP4430_CM_L3INIT_DYNAMICDEP;
	strcpy(prcm_l3init_reg_table[i].name, "CM_L3INIT_MMC1_CLKCTRL");
	prcm_l3init_reg_table[i++].addr = OMAP4430_CM_L3INIT_MMC1_CLKCTRL;
	strcpy(prcm_l3init_reg_table[i].name, "CM_L3INIT_MMC2_CLKCTRL");
	prcm_l3init_reg_table[i++].addr = OMAP4430_CM_L3INIT_MMC2_CLKCTRL;
	strcpy(prcm_l3init_reg_table[i].name, "CM_L3INIT_HSI_CLKCTRL");
	prcm_l3init_reg_table[i++].addr = OMAP4430_CM_L3INIT_HSI_CLKCTRL;
	if (cpu_is_omap4430() && (cpu_revision_get() == REV_ES1_0)) {
		strcpy(prcm_l3init_reg_table[i].name,
			"CM_L3INIT_UNIPRO1_CLKCTRL");
		prcm_l3init_reg_table[i++].addr =
			OMAP4430_CM_L3INIT_UNIPRO1_CLKCTRL;
	}
	strcpy(prcm_l3init_reg_table[i].name, "CM_L3INIT_HSUSBHOST_CLKCTRL");
	prcm_l3init_reg_table[i++].addr = OMAP4430_CM_L3INIT_USB_HOST_CLKCTRL;
	strcpy(prcm_l3init_reg_table[i].name, "CM_L3INIT_HSUSBOTG_CLKCTRL");
	prcm_l3init_reg_table[i++].addr = OMAP4430_CM_L3INIT_USB_OTG_CLKCTRL;
	strcpy(prcm_l3init_reg_table[i].name, "CM_L3INIT_HSUSBTLL_CLKCTRL");
	prcm_l3init_reg_table[i++].addr = OMAP4430_CM_L3INIT_USB_TLL_CLKCTRL;
	strcpy(prcm_l3init_reg_table[i].name, "CM_L3INIT_P1500_CLKCTRL");
	prcm_l3init_reg_table[i++].addr = OMAP4430_CM_L3INIT_P1500_CLKCTRL;
	if (!cpu_is_omap4470()) {
		strcpy(prcm_l3init_reg_table[i].name,
			"CM_L3INIT_FSUSB_CLKCTRL");
		prcm_l3init_reg_table[i++].addr =
			OMAP4430_CM_L3INIT_USB_HOST_FS_CLKCTRL;
	}
	strcpy(prcm_l3init_reg_table[i].name, "CM_L3INIT_USBPHY_CLKCTRL");
	prcm_l3init_reg_table[i++].addr =
		OMAP4430_CM_L3INIT_USBPHYOCP2SCP_CLKCTRL;
	strcpy(prcm_l3init_reg_table[i].name, "END");
	prcm_l3init_reg_table[i].addr = 0;
	dprintf("prcm_l3init_reg_table last index=%d, size=%d\n", i, i + 1);

	init_done = 1;
	return 0;
}
