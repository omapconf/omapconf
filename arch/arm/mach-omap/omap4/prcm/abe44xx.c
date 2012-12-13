/*
 *
 * @Component			OMAPCONF
 * @Filename			abe44xx.c
 * @Description			OMAP4 PRCM ABE Definitions & Functions
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


#include <abe44xx.h>
#include <clkdm44xx.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cm44xx.h>
#include <prm44xx.h>
#include <pwrdm44xx.h>
#include <module44xx.h>
#include <help.h>
#include <lib.h>
#include <mem.h>
#include <cpuinfo.h>
#include <string.h>


/* #define ABE44XX_DEBUG */
#ifdef ABE44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

#define PRCM_ABE_REG_TABLE_SIZE 32

#define OMAP_ABE_DMEM_ADDR 0x40180000
#define OMAP_ABE_ATC_LIST_SIZE 17
#define OMAP_ABE_ATC_NB_READ 6

struct atc_item {
	char name[20];
	unsigned int offset;
};

struct atc_desc {
	unsigned rdpt:7;
	unsigned reserved0:1;
	unsigned cbsize:7;
	unsigned irqdest:1;
	unsigned cberr:1;
	unsigned reserved1:5;
	unsigned cbdir:1;
	unsigned nw:1;
	unsigned wrpt:7;
	unsigned reserved2:1;
	unsigned badd:12;
	unsigned iter:7;
	unsigned srcid:6;
	unsigned destid:6;
	unsigned desen:1;
};

struct atc_item atc_list[OMAP_ABE_ATC_LIST_SIZE] = {
	{
		.name = "DMIC",
		.offset = 0x0000,
	},
	{
		.name = "McPDM DL",
		.offset = 0x0010,
	},
	{
		.name = "McPDM UL",
		.offset = 0x0018,
	},
	{
		.name = "McBSP 1 TX",
		.offset = 0x0020,
	},
	{
		.name = "McBSP 1 RX",
		.offset = 0x0028,
	},
	{
		.name = "McBSP 2 TX",
		.offset = 0x0030,
	},
	{
		.name = "McBSP 2 RX",
		.offset = 0x0038,
	},
	{
		.name = "McBSP 3 TX",
		.offset = 0x0040,
	},
	{
		.name = "McBSP 3 RX",
		.offset = 0x0048,
	},
	{
		.name = "CBPr0",
		.offset = 0x0100,
	},
	{
		.name = "CBPr1",
		.offset = 0x0108,
	},
	{
		.name = "CBPr2",
		.offset = 0x0110,
	},
	{
		.name = "CBPr3",
		.offset = 0x0118,
	},
	{
		.name = "CBPr4",
		.offset = 0x0120,
	},
	{
		.name = "CBPr5",
		.offset = 0x0128,
	},
	{
		.name = "CBPr6",
		.offset = 0x0130,
	},
	{
		.name = "CBPr7",
		.offset = 0x0138,
	}
};


reg_table prcm_abe_reg_table[PRCM_ABE_REG_TABLE_SIZE];
static unsigned int init_done = 0;

static int abe44xx_regtable_init(void);


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		abe44xx_name2addr
 * @BRIEF		retrieve physical address of a register, given its name.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		name: register name
 * @param[in, out]	addr: register address
 * @DESCRIPTION		retrieve physical address of a register, given its name.
 *//*------------------------------------------------------------------------ */
int abe44xx_name2addr(char *name, unsigned int *addr)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		abe44xx_regtable_init();

	return name2addr(name, addr, prcm_abe_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		abe44xx_config_show
 * @BRIEF		analyze ABE power configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		stream: output file stream
 * @DESCRIPTION		analyze ABE power configuration
 *//*------------------------------------------------------------------------ */
int abe44xx_config_show(FILE *stream)
{
	unsigned int pm_pwstctrl;
	unsigned int pm_pwstst;
	unsigned int cm_clkstctrl;
	unsigned int rm_context;
	unsigned int cm_clkctrl;
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		abe44xx_regtable_init();

	/* Power Domain Configuration */
	if (mem_read(OMAP4430_PM_ABE_PWRSTCTRL, &pm_pwstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_PM_ABE_PWRSTST, &pm_pwstst) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = pwrdm44xx_config_show(stream, "ABE",
		OMAP4430_PM_ABE_PWRSTCTRL, pm_pwstctrl,
		OMAP4430_PM_ABE_PWRSTST, pm_pwstst);
	if (ret != 0)
		return ret;

	/* Clock Domain Configuration */
	if (mem_read(OMAP4430_CM1_ABE_CLKSTCTRL, &cm_clkstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = clkdm44xx_config_show(stream, "ABE",
		OMAP4430_CM1_ABE_CLKSTCTRL, cm_clkstctrl);
	if (ret != 0)
		return ret;

	/* Module Power Configuration */
	if (mem_read(OMAP4430_CM1_ABE_L4ABE_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "L4ABE",
		OMAP4430_CM1_ABE_L4ABE_CLKCTRL, cm_clkctrl,
		0, 0); /* no context register */
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM1_ABE_AESS_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_ABE_AESS_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "AESS",
		OMAP4430_CM1_ABE_AESS_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_ABE_AESS_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM1_ABE_PDM_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_ABE_PDM_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "PDM",
		OMAP4430_CM1_ABE_PDM_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_ABE_PDM_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM1_ABE_DMIC_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_ABE_DMIC_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "DMIC",
		OMAP4430_CM1_ABE_DMIC_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_ABE_DMIC_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM1_ABE_MCASP_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_ABE_MCASP_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "MCASP",
		OMAP4430_CM1_ABE_MCASP_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_ABE_MCASP_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM1_ABE_MCBSP1_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_ABE_MCBSP1_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "MCBSP1",
		OMAP4430_CM1_ABE_MCBSP1_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_ABE_MCBSP1_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM1_ABE_MCBSP2_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_ABE_MCBSP2_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "MCBSP2",
		OMAP4430_CM1_ABE_MCBSP2_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_ABE_MCBSP2_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM1_ABE_MCBSP3_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_ABE_MCBSP3_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "MCBSP3",
		OMAP4430_CM1_ABE_MCBSP3_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_ABE_MCBSP3_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM1_ABE_SLIMBUS_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_ABE_SLIMBUS_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "SLIMBUS",
		OMAP4430_CM1_ABE_SLIMBUS_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_ABE_SLIMBUS_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM1_ABE_TIMER5_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_ABE_TIMER5_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "TIMER5",
		OMAP4430_CM1_ABE_TIMER5_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_ABE_TIMER5_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM1_ABE_TIMER6_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_ABE_TIMER6_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "TIMER6",
		OMAP4430_CM1_ABE_TIMER6_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_ABE_TIMER6_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM1_ABE_TIMER7_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_ABE_TIMER7_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "TIMER7",
		OMAP4430_CM1_ABE_TIMER7_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_ABE_TIMER7_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM1_ABE_TIMER8_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_ABE_TIMER8_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "TIMER8",
		OMAP4430_CM1_ABE_TIMER8_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_ABE_TIMER8_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM1_ABE_WDT3_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_ABE_WDT3_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "WDT3",
		OMAP4430_CM1_ABE_WDT3_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_ABE_WDT3_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		abe44xx_dump
 * @BRIEF		dump PRCM ABE registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		dump PRCM ABE registers
 *//*------------------------------------------------------------------------ */
int abe44xx_dump(void)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		abe44xx_regtable_init();

	return dumpregs(prcm_abe_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		abe44xx_atc_status_show
 * @BRIEF		analyze ABE ATC configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in, out]	stream: output file stream
 * @DESCRIPTION		analyze ABE ATC configuration
 *//*------------------------------------------------------------------------ */
int abe44xx_atc_status_show(FILE *stream)
{
	int i, j;
	int read_count, write_count;
	struct atc_desc atc[OMAP_ABE_ATC_NB_READ];
	int ret;
	unsigned int reg_addr;
	clkdm_status clkst;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		abe44xx_regtable_init();

	clkdm44xx_get_status(OMAP4_CD_ABE, &clkst);
	if (clkst != CLKDM_RUNNING) {
		fprintf(stream,
			"ABE clocks are not running, cannot proceed further"
			".\n\n");
		return 0;
	}

	/* Generic ABE ATC trace information */
	fprintf(stream, "Inside TI mainline the configuration is:\n");
	fprintf(stream, "\tMcBSP 1: Connected to BT device\n");
	fprintf(stream, "\tMcBSP 2: Conngeected to MODEM device\n");
	fprintf(stream, "\tMcBSP 3: Not Connected or to external Aduio IC\n");
	fprintf(stream,
		"\tCBPR0: Use for Multimedia Playback (non ping/pong mode)\n");
	fprintf(stream, "\tCBPR1: Use for Voice Playback (up to 2 channels)\n");
	fprintf(stream, "\tCBPR2: Use for Voice Record (up to 2 channels)\n");
	fprintf(stream,
		"\tCBPR3: Use for Multimedia UL Record (up to 6 channels)\n");
	fprintf(stream,
		"\tCBPR4: Use for Multimedia UL2 Record (up to 2 channels)\n");
	fprintf(stream, "\tCBPR5: Use for Tones Playback (up to 2 channels)\n");
	fprintf(stream, "\tCBPR6: Use for Vibra\n");
	fprintf(stream, "\tCBPR7: Not used\n");
	fprintf(stream, "\n");

	for (i = 0; i < OMAP_ABE_ATC_LIST_SIZE; i++) {
		/* Read ATC descriptor */
		reg_addr = OMAP_ABE_DMEM_ADDR + atc_list[i].offset;
		ret = mem_address_range_read(reg_addr,
			(unsigned int *)(&atc[0]), 2);
		if (ret)
			return ret;

		/* check if ATC descriptor is enable */
		if (atc[0].desen) {
			read_count = 0;
			write_count = 0;
			/* Make several read to check the activity */
			for (j = 0; j < OMAP_ABE_ATC_NB_READ; j++) {
				ret = mem_address_range_read(reg_addr,
					(unsigned int *)&atc[j], 2);
				if (ret)
					return ret;
				usleep(250);
			}

			/* Check Read/write pointer (moving or not) */
			for (j = 0; j < (OMAP_ABE_ATC_NB_READ-1); j++) {
				if (atc[j].rdpt != atc[j+1].rdpt)
					read_count++;
				if (atc[j].wrpt != atc[j+1].wrpt)
					write_count++;
			}

			/* Output trace */
			if (!atc[0].cbdir)
				fprintf(stream,
					"ATC for %s is running (Transfer form "
					"HW IP to DMEM):\n", atc_list[i].name);
			else
				fprintf(stream,
					"ATC for %s is running (Transfer form "
					"DMEM to HW IP):\n", atc_list[i].name);

			/* Display pointer evolution */
			if (write_count == 0) {
				if (!atc[0].cbdir)
					fprintf(stream,
						"\t!!! HW IP pointer not "
						"moving\n");
				else
					fprintf(stream,
						"\t!!! ABE pointer not "
						"moving\n");
			}
			if (read_count == 0) {
				if (!atc[0].cbdir)
					fprintf(stream,
						"\t!!! ABE pointer not "
						"moving\n");
				else
					fprintf(stream, "\t!!! HW IP pointer "
						"not moving\n");
			}
			if ((read_count != 0) && (write_count != 0))
				fprintf(stream, "\tATC pointer are moving "
					"(w:%d r:%d)\n",
					write_count, read_count);

			if ((atc[0].badd == 0) || ((atc[0].badd & 0x00F) != 0))
				fprintf(stream, "\t!!! Base Address for DMEM "
					"is not good (0x%04x)\n",
					atc[0].badd);

			fprintf(stream,
				"\tBase:0x%08x, iter: %d, FIFO size:%d\n",
				(atc[0].badd << 4) + OMAP_ABE_DMEM_ADDR,
				atc[0].iter, atc[0].cbsize);

			fprintf(stream, "\n");
		}
	}
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		abe44xx_main
 * @BRIEF		abe main entry point
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		abe menu
 *//*------------------------------------------------------------------------ */
int abe44xx_main(int argc, char *argv[])
{
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (argc == 2) {
		if (!init_done)
			abe44xx_regtable_init();
		if (strcmp(argv[1], "dump") == 0) {
			ret = dumpregs(prcm_abe_reg_table);
		} else if (strcmp(argv[1], "cfg") == 0) {
			ret = abe44xx_config_show(stdout);
		} else if (strcmp(argv[1], "atc") == 0) {
			ret = abe44xx_atc_status_show(stdout);
		} else {
			help(HELP_ABE);
			ret = OMAPCONF_ERR_ARG;
		}
	} else {
		help(HELP_ABE);
		ret = OMAPCONF_ERR_ARG;
	}

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		abe44xx_regtable_init
 * @BRIEF		initialize regtable
 * @RETURNS		0
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		initialize regtable
 *//*------------------------------------------------------------------------ */
int abe44xx_regtable_init(void)
{
	int i = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	/* Init PRCM registers table */
	strcpy(prcm_abe_reg_table[i].name, "PM_ABE_PWRSTCTRL");
	prcm_abe_reg_table[i++].addr = OMAP4430_PM_ABE_PWRSTCTRL;
	strcpy(prcm_abe_reg_table[i].name, "PM_ABE_PWRSTST");
	prcm_abe_reg_table[i++].addr = OMAP4430_PM_ABE_PWRSTST;
	strcpy(prcm_abe_reg_table[i].name, "RM_ABE_AESS_CONTEXT");
	prcm_abe_reg_table[i++].addr = OMAP4430_RM_ABE_AESS_CONTEXT;
	strcpy(prcm_abe_reg_table[i].name, "RM_ABE_PDM_CONTEXT");
	prcm_abe_reg_table[i++].addr = OMAP4430_RM_ABE_PDM_CONTEXT;
	strcpy(prcm_abe_reg_table[i].name, "RM_ABE_DMIC_CONTEXT");
	prcm_abe_reg_table[i++].addr = OMAP4430_RM_ABE_DMIC_CONTEXT;
	strcpy(prcm_abe_reg_table[i].name, "RM_ABE_MCASP_CONTEXT");
	prcm_abe_reg_table[i++].addr = OMAP4430_RM_ABE_MCASP_CONTEXT;
	strcpy(prcm_abe_reg_table[i].name, "RM_ABE_MCBSP1_CONTEXT");
	prcm_abe_reg_table[i++].addr = OMAP4430_RM_ABE_MCBSP1_CONTEXT;
	strcpy(prcm_abe_reg_table[i].name, "RM_ABE_MCBSP2_CONTEXT");
	prcm_abe_reg_table[i++].addr = OMAP4430_RM_ABE_MCBSP2_CONTEXT;
	strcpy(prcm_abe_reg_table[i].name, "RM_ABE_MCBSP3_CONTEXT");
	prcm_abe_reg_table[i++].addr = OMAP4430_RM_ABE_MCBSP3_CONTEXT;
	strcpy(prcm_abe_reg_table[i].name, "RM_ABE_SLIMBUS_CONTEXT");
	prcm_abe_reg_table[i++].addr = OMAP4430_RM_ABE_SLIMBUS_CONTEXT;
	strcpy(prcm_abe_reg_table[i].name, "RM_ABE_TIMER5_CONTEXT");
	prcm_abe_reg_table[i++].addr = OMAP4430_RM_ABE_TIMER5_CONTEXT;
	strcpy(prcm_abe_reg_table[i].name, "RM_ABE_TIMER6_CONTEXT");
	prcm_abe_reg_table[i++].addr = OMAP4430_RM_ABE_TIMER6_CONTEXT;
	strcpy(prcm_abe_reg_table[i].name, "RM_ABE_TIMER7_CONTEXT");
	prcm_abe_reg_table[i++].addr = OMAP4430_RM_ABE_TIMER7_CONTEXT;
	strcpy(prcm_abe_reg_table[i].name, "RM_ABE_TIMER8_CONTEXT");
	prcm_abe_reg_table[i++].addr = OMAP4430_RM_ABE_TIMER8_CONTEXT;
	strcpy(prcm_abe_reg_table[i].name, "RM_ABE_WDT3_CONTEXT");
	prcm_abe_reg_table[i++].addr = OMAP4430_RM_ABE_WDT3_CONTEXT;
	strcpy(prcm_abe_reg_table[i].name, "CM_CLKSEL_ABE");
	prcm_abe_reg_table[i++].addr = OMAP4430_CM_CLKSEL_ABE;
	strcpy(prcm_abe_reg_table[i].name, "CM_ABE_CLKSTCTRL");
	prcm_abe_reg_table[i++].addr = OMAP4430_CM1_ABE_CLKSTCTRL;
	strcpy(prcm_abe_reg_table[i].name, "CM1_ABE_L4ABE_CLKCTRL");
	prcm_abe_reg_table[i++].addr = OMAP4430_CM1_ABE_L4ABE_CLKCTRL;
	strcpy(prcm_abe_reg_table[i].name, "CM1_ABE_AESS_CLKCTRL");
	prcm_abe_reg_table[i++].addr = OMAP4430_CM1_ABE_AESS_CLKCTRL;
	strcpy(prcm_abe_reg_table[i].name, "CM1_ABE_PDM_CLKCTRL");
	prcm_abe_reg_table[i++].addr = OMAP4430_CM1_ABE_PDM_CLKCTRL;
	strcpy(prcm_abe_reg_table[i].name, "CM1_ABE_DMIC_CLKCTRL");
	prcm_abe_reg_table[i++].addr = OMAP4430_CM1_ABE_DMIC_CLKCTRL;
	strcpy(prcm_abe_reg_table[i].name, "CM1_ABE_MCASP_CLKCTRL");
	prcm_abe_reg_table[i++].addr = OMAP4430_CM1_ABE_MCASP_CLKCTRL;
	strcpy(prcm_abe_reg_table[i].name, "CM1_ABE_MCBSP1_CLKCTRL");
	prcm_abe_reg_table[i++].addr = OMAP4430_CM1_ABE_MCBSP1_CLKCTRL;
	strcpy(prcm_abe_reg_table[i].name, "CM1_ABE_MCBSP2_CLKCTRL");
	prcm_abe_reg_table[i++].addr = OMAP4430_CM1_ABE_MCBSP2_CLKCTRL;
	strcpy(prcm_abe_reg_table[i].name, "CM1_ABE_MCBSP3_CLKCTRL");
	prcm_abe_reg_table[i++].addr = OMAP4430_CM1_ABE_MCBSP3_CLKCTRL;
	strcpy(prcm_abe_reg_table[i].name, "CM1_ABE_SLIMBUS_CLKCTRL");
	prcm_abe_reg_table[i++].addr = OMAP4430_CM1_ABE_SLIMBUS_CLKCTRL;
	strcpy(prcm_abe_reg_table[i].name, "CM1_ABE_TIMER5_CLKCTRL");
	prcm_abe_reg_table[i++].addr = OMAP4430_CM1_ABE_TIMER5_CLKCTRL;
	strcpy(prcm_abe_reg_table[i].name, "CM1_ABE_TIMER6_CLKCTRL");
	prcm_abe_reg_table[i++].addr = OMAP4430_CM1_ABE_TIMER6_CLKCTRL;
	strcpy(prcm_abe_reg_table[i].name, "CM1_ABE_TIMER7_CLKCTRL");
	prcm_abe_reg_table[i++].addr = OMAP4430_CM1_ABE_TIMER7_CLKCTRL;
	strcpy(prcm_abe_reg_table[i].name, "CM1_ABE_TIMER8_CLKCTRL");
	prcm_abe_reg_table[i++].addr = OMAP4430_CM1_ABE_TIMER8_CLKCTRL;
	strcpy(prcm_abe_reg_table[i].name, "CM1_ABE_WDT3_CLKCTRL");
	prcm_abe_reg_table[i++].addr = OMAP4430_CM1_ABE_WDT3_CLKCTRL;
	strcpy(prcm_abe_reg_table[i].name, "END");
	prcm_abe_reg_table[i].addr = 0;
	dprintf("prcm_core_reg_table last index=%d, size=%d\n", i, i + 1);

	init_done = 1;
	return 0;
}
