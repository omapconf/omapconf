/*
 *
 * @Component			OMAPCONF
 * @Filename			ctt_dra7xx.c
 * @Description		Display PRCM registers in a format that can be
 *				imported into the clock tree tool (CTT)
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


#include <ctt_dra7xx.h>
#include <lib.h>
#include <help.h>
#include <lib.h>
#include <mem.h>
#include <cpuinfo.h>
#include <string.h>

/* #define CTT54XX_DEBUG */
#ifdef CTT_DRA7XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

#define PRCM_CTT_REG_TABLE_SIZE        220

static reg_table prcm_ctt_reg_table[PRCM_CTT_REG_TABLE_SIZE];

static int ctt_dra7xx_regtable_init(void);

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		ctt_dra7xx_dump
 * @BRIEF		dump PRCM registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		dump PRCM registers
 *//*------------------------------------------------------------------------ */
int ctt_dra7xx_dump(void)
{
	unsigned int i = 0;
	unsigned int ret, val = 0;
	int err = 0;
	char cpu_name[CPU_NAME_MAX_LENGTH], cpu_revision[CPU_REVISION_MAX_NAME_LENGTH];

	printf("The Clock Tree Tool can import register settings from a *.rd1 "
		"file.\n");
	printf("The format of the *.rd1 file is:\n\n");
	printf("DeviceName %s_SR%s\n", cpu_gets(cpu_name), cpu_revision_gets(cpu_revision));
	printf("<register address> <register value>\n");
	printf("<register address> <register value>\n");
	printf("...\n\n");
	printf("Copy the below output between the begin and end separators "
		"into a\n");
	printf("file with the extension *.rd1 and this file can be read by the"
		"\n");
	printf("Clock Tree Tool\n\n");
	printf("|--------------------------- ctt dump begin ------------------"
		"----|\n");

	if (cpu_is_dra7xx())
		printf("DeviceName %s_SR%s\n", cpu_gets(cpu_name), cpu_revision_gets(cpu_revision));
	else
		return OMAPCONF_ERR_CPU;

	ctt_dra7xx_regtable_init();

	while (prcm_ctt_reg_table[i].addr != 0) {
		/* display register addr & content (hex) */
		ret = mem_read(prcm_ctt_reg_table[i].addr, &val);
		if (ret == 0)
			printf("0x%08X 0x%08X\n", prcm_ctt_reg_table[i].addr,
				val);
		else {
			fprintf(stderr,
				"omapconf: read error! (addr=0x%08X, err=%d)\n",
				prcm_ctt_reg_table[i].addr, ret);
			err = OMAPCONF_ERR_REG_ACCESS;
		}
		i++;
	}

	printf("|---------------------------- ctt dump end --------------------"
		"---|\n\n");

	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		ctt_dra7xx_rd1_export
 * @BRIEF		export PRCM registers in CTT RD1 format
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		file: output file name
 * @DESCRIPTION		export PRCM registers in CTT RD1 format
 *//*------------------------------------------------------------------------ */
int ctt_dra7xx_rd1_export(char *file)
{
	unsigned int i = 0;
	unsigned int ret, val = 0;
	int err = 0;
	FILE *fd = NULL;
	char fullfilename[128];
	char cpu_name[CPU_NAME_MAX_LENGTH], cpu_revision[CPU_REVISION_MAX_NAME_LENGTH];

	CHECK_NULL_ARG(file, OMAPCONF_ERR_ARG);

	strcpy(fullfilename, file);
	fd = workdir_fopen(fullfilename, "w");
	if (fd == NULL) {
		printf("error: could not create %s file!\n", fullfilename);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	if (cpu_is_dra7xx())
		fprintf(fd, "DeviceName %s_SR%s\n", cpu_gets(cpu_name), cpu_revision_gets(cpu_revision));
	else
		return OMAPCONF_ERR_CPU;

	ctt_dra7xx_regtable_init();

	while (prcm_ctt_reg_table[i].addr != 0) {
		/* display register addr & content (hex) */
		ret = mem_read(prcm_ctt_reg_table[i].addr, &val);
		if (ret == 0)
			fprintf(fd, "0x%08X 0x%08X\n",
				prcm_ctt_reg_table[i].addr, val);
		else {
			fprintf(stderr,
				"omapconf: read error! (addr=0x%08X, err=%d)\n",
				prcm_ctt_reg_table[i].addr, ret);
			err = OMAPCONF_ERR_REG_ACCESS;
		}
		i++;
	}

	printf("Output written to file '%s'\n\n", fullfilename);
	fclose(fd);

	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		ctt_dra7xx_main
 * @BRIEF		CTT main menu
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		CTT main menu
 *//*------------------------------------------------------------------------ */
int ctt_dra7xx_main(int argc, char *argv[])
{
	int ret;

	if (argc == 1) {
		ctt_dra7xx_regtable_init();

		if (strcmp(argv[0], "dump") == 0)
			ret = ctt_dra7xx_dump();
		else if (strcmp(argv[0], "rd1") == 0)
			ret = ctt_dra7xx_rd1_export(
				"CTT-DRA7xx_ES1.rd1");
		else {
			help(HELP_EXPORT);
			ret = OMAPCONF_ERR_ARG;
		}
	} else {
		help(HELP_EXPORT);
		ret = OMAPCONF_ERR_ARG;
	}

	return ret;
}



/* ------------------------------------------------------------------------*//**
 * @FUNCTION		ctt_dra7xx_regtable_init
 * @BRIEF		initialize regtable
 * @RETURNS		0
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		initialize regtable
 *//*------------------------------------------------------------------------ */
static int ctt_dra7xx_regtable_init(void)
{
	int i = 0;

	/* Init PRCM registers table */
	/* Data from: CTT-v1.12.0.4 */
	/* WARNING: Make sure you update the macro PRCM_CTT_REG_TABLE_SIZE
	            before changing this */
	prcm_ctt_reg_table[i++].addr = 0x4a005100;
	prcm_ctt_reg_table[i++].addr = 0x4a005120;
	prcm_ctt_reg_table[i++].addr = 0x4a00512c;
	prcm_ctt_reg_table[i++].addr = 0x4a005130;
	prcm_ctt_reg_table[i++].addr = 0x4a00513c;
	prcm_ctt_reg_table[i++].addr = 0x4a005140;
	prcm_ctt_reg_table[i++].addr = 0x4a005144;
	prcm_ctt_reg_table[i++].addr = 0x4a005154;
	prcm_ctt_reg_table[i++].addr = 0x4a005158;
	prcm_ctt_reg_table[i++].addr = 0x4a00515c;
	prcm_ctt_reg_table[i++].addr = 0x4a005160;
	prcm_ctt_reg_table[i++].addr = 0x4a00516c;
	prcm_ctt_reg_table[i++].addr = 0x4a005170;
	prcm_ctt_reg_table[i++].addr = 0x4a00519c;
	prcm_ctt_reg_table[i++].addr = 0x4a0051a0;
	prcm_ctt_reg_table[i++].addr = 0x4a0051ac;
	prcm_ctt_reg_table[i++].addr = 0x4a0051b0;
	prcm_ctt_reg_table[i++].addr = 0x4a0051dc;
	prcm_ctt_reg_table[i++].addr = 0x4a0051e0;
	prcm_ctt_reg_table[i++].addr = 0x4a0051ec;
	prcm_ctt_reg_table[i++].addr = 0x4a0051f0;
	prcm_ctt_reg_table[i++].addr = 0x4a0051f4;
	prcm_ctt_reg_table[i++].addr = 0x4a005210;
	prcm_ctt_reg_table[i++].addr = 0x4a00521c;
	prcm_ctt_reg_table[i++].addr = 0x4a005220;
	prcm_ctt_reg_table[i++].addr = 0x4a005228;
	prcm_ctt_reg_table[i++].addr = 0x4a005234;
	prcm_ctt_reg_table[i++].addr = 0x4a005240;
	prcm_ctt_reg_table[i++].addr = 0x4a005244;
	prcm_ctt_reg_table[i++].addr = 0x4a005248;
	prcm_ctt_reg_table[i++].addr = 0x4a005254;
	prcm_ctt_reg_table[i++].addr = 0x4a005284;
	prcm_ctt_reg_table[i++].addr = 0x4a005290;
	prcm_ctt_reg_table[i++].addr = 0x4a005294;
	prcm_ctt_reg_table[i++].addr = 0x4a0052a4;
	prcm_ctt_reg_table[i++].addr = 0x4a0052a8;
	prcm_ctt_reg_table[i++].addr = 0x4a0052b4;
	prcm_ctt_reg_table[i++].addr = 0x4a0052b8;
	prcm_ctt_reg_table[i++].addr = 0x4a0052c0;
	prcm_ctt_reg_table[i++].addr = 0x4a0052c4;
	prcm_ctt_reg_table[i++].addr = 0x4a0052d8;
	prcm_ctt_reg_table[i++].addr = 0x4a0052e4;
	prcm_ctt_reg_table[i++].addr = 0x4a0052e8;
	prcm_ctt_reg_table[i++].addr = 0x4a005420;
	prcm_ctt_reg_table[i++].addr = 0x4a005520;
	prcm_ctt_reg_table[i++].addr = 0x4a005550;
	prcm_ctt_reg_table[i++].addr = 0x4a005558;
	prcm_ctt_reg_table[i++].addr = 0x4a005560;
	prcm_ctt_reg_table[i++].addr = 0x4a005568;
	prcm_ctt_reg_table[i++].addr = 0x4a005570;
	prcm_ctt_reg_table[i++].addr = 0x4a005578;
	prcm_ctt_reg_table[i++].addr = 0x4a005580;
	prcm_ctt_reg_table[i++].addr = 0x4a005620;
	prcm_ctt_reg_table[i++].addr = 0x4a005660;
	prcm_ctt_reg_table[i++].addr = 0x4a0056a0;
	prcm_ctt_reg_table[i++].addr = 0x4a005744;
	prcm_ctt_reg_table[i++].addr = 0x4a005764;
	prcm_ctt_reg_table[i++].addr = 0x4a008140;
	prcm_ctt_reg_table[i++].addr = 0x4a00814c;
	prcm_ctt_reg_table[i++].addr = 0x4a008150;
	prcm_ctt_reg_table[i++].addr = 0x4a008158;
	prcm_ctt_reg_table[i++].addr = 0x4a00815c;
	prcm_ctt_reg_table[i++].addr = 0x4a008160;
	prcm_ctt_reg_table[i++].addr = 0x4a008164;
	prcm_ctt_reg_table[i++].addr = 0x4a008180;
	prcm_ctt_reg_table[i++].addr = 0x4a00818c;
	prcm_ctt_reg_table[i++].addr = 0x4a008190;
	prcm_ctt_reg_table[i++].addr = 0x4a008200;
	prcm_ctt_reg_table[i++].addr = 0x4a00820c;
	prcm_ctt_reg_table[i++].addr = 0x4a008210;
	prcm_ctt_reg_table[i++].addr = 0x4a00821c;
	prcm_ctt_reg_table[i++].addr = 0x4a008728;
	prcm_ctt_reg_table[i++].addr = 0x4a008778;
	prcm_ctt_reg_table[i++].addr = 0x4a008780;
	prcm_ctt_reg_table[i++].addr = 0x4a008920;
	prcm_ctt_reg_table[i++].addr = 0x4a008b30;
	prcm_ctt_reg_table[i++].addr = 0x4a008b38;
	prcm_ctt_reg_table[i++].addr = 0x4a008b40;
	prcm_ctt_reg_table[i++].addr = 0x4a008c00;
	prcm_ctt_reg_table[i++].addr = 0x4a008e20;
	prcm_ctt_reg_table[i++].addr = 0x4a008e28;
	prcm_ctt_reg_table[i++].addr = 0x4a008e40;
	prcm_ctt_reg_table[i++].addr = 0x4a008e50;
	prcm_ctt_reg_table[i++].addr = 0x4a008f20;
	prcm_ctt_reg_table[i++].addr = 0x4a008f28;
	prcm_ctt_reg_table[i++].addr = 0x4a009020;
	prcm_ctt_reg_table[i++].addr = 0x4a009028;
	prcm_ctt_reg_table[i++].addr = 0x4a009030;
	prcm_ctt_reg_table[i++].addr = 0x4a009120;
	prcm_ctt_reg_table[i++].addr = 0x4a009130;
	prcm_ctt_reg_table[i++].addr = 0x4a009220;
	prcm_ctt_reg_table[i++].addr = 0x4a009328;
	prcm_ctt_reg_table[i++].addr = 0x4a009330;
	prcm_ctt_reg_table[i++].addr = 0x4a009340;
	prcm_ctt_reg_table[i++].addr = 0x4a009348;
	prcm_ctt_reg_table[i++].addr = 0x4a009350;
	prcm_ctt_reg_table[i++].addr = 0x4a009358;
	prcm_ctt_reg_table[i++].addr = 0x4a009388;
	prcm_ctt_reg_table[i++].addr = 0x4a0093b0;
	prcm_ctt_reg_table[i++].addr = 0x4a0093b8;
	prcm_ctt_reg_table[i++].addr = 0x4a0093d0;
	prcm_ctt_reg_table[i++].addr = 0x4a0093e0;
	prcm_ctt_reg_table[i++].addr = 0x4a0093e8;
	prcm_ctt_reg_table[i++].addr = 0x4a0093f0;
	prcm_ctt_reg_table[i++].addr = 0x4a009620;
	prcm_ctt_reg_table[i++].addr = 0x4a009728;
	prcm_ctt_reg_table[i++].addr = 0x4a009730;
	prcm_ctt_reg_table[i++].addr = 0x4a009738;
	prcm_ctt_reg_table[i++].addr = 0x4a009740;
	prcm_ctt_reg_table[i++].addr = 0x4a009748;
	prcm_ctt_reg_table[i++].addr = 0x4a009750;
	prcm_ctt_reg_table[i++].addr = 0x4a009760;
	prcm_ctt_reg_table[i++].addr = 0x4a009768;
	prcm_ctt_reg_table[i++].addr = 0x4a009770;
	prcm_ctt_reg_table[i++].addr = 0x4a009778;
	prcm_ctt_reg_table[i++].addr = 0x4a009780;
	prcm_ctt_reg_table[i++].addr = 0x4a009788;
	prcm_ctt_reg_table[i++].addr = 0x4a009790;
	prcm_ctt_reg_table[i++].addr = 0x4a009798;
	prcm_ctt_reg_table[i++].addr = 0x4a0097a0;
	prcm_ctt_reg_table[i++].addr = 0x4a0097a8;
	prcm_ctt_reg_table[i++].addr = 0x4a0097b0;
	prcm_ctt_reg_table[i++].addr = 0x4a0097b8;
	prcm_ctt_reg_table[i++].addr = 0x4a0097c4;
	prcm_ctt_reg_table[i++].addr = 0x4a0097c8;
	prcm_ctt_reg_table[i++].addr = 0x4a0097d0;
	prcm_ctt_reg_table[i++].addr = 0x4a0097d8;
	prcm_ctt_reg_table[i++].addr = 0x4a0097f0;
	prcm_ctt_reg_table[i++].addr = 0x4a0097f8;
	prcm_ctt_reg_table[i++].addr = 0x4a009800;
	prcm_ctt_reg_table[i++].addr = 0x4a009808;
	prcm_ctt_reg_table[i++].addr = 0x4a009810;
	prcm_ctt_reg_table[i++].addr = 0x4a009818;
	prcm_ctt_reg_table[i++].addr = 0x4a009820;
	prcm_ctt_reg_table[i++].addr = 0x4a009828;
	prcm_ctt_reg_table[i++].addr = 0x4a009830;
	prcm_ctt_reg_table[i++].addr = 0x4a009838;
	prcm_ctt_reg_table[i++].addr = 0x4a009840;
	prcm_ctt_reg_table[i++].addr = 0x4a009848;
	prcm_ctt_reg_table[i++].addr = 0x4a009850;
	prcm_ctt_reg_table[i++].addr = 0x4a009858;
	prcm_ctt_reg_table[i++].addr = 0x4a009860;
	prcm_ctt_reg_table[i++].addr = 0x4a009868;
	prcm_ctt_reg_table[i++].addr = 0x4a009870;
	prcm_ctt_reg_table[i++].addr = 0x4a009878;
	prcm_ctt_reg_table[i++].addr = 0x4a009890;
	prcm_ctt_reg_table[i++].addr = 0x4a009898;
	prcm_ctt_reg_table[i++].addr = 0x4a0098a0;
	prcm_ctt_reg_table[i++].addr = 0x4a0098a8;
	prcm_ctt_reg_table[i++].addr = 0x4a0098b0;
	prcm_ctt_reg_table[i++].addr = 0x4a0098b8;
	prcm_ctt_reg_table[i++].addr = 0x4a0098c0;
	prcm_ctt_reg_table[i++].addr = 0x4a0098c8;
	prcm_ctt_reg_table[i++].addr = 0x4a0098d0;
	prcm_ctt_reg_table[i++].addr = 0x4a0098e0;
	prcm_ctt_reg_table[i++].addr = 0x4a0098e8;
	prcm_ctt_reg_table[i++].addr = 0x4a0098f0;
	prcm_ctt_reg_table[i++].addr = 0x4a0098f8;
	prcm_ctt_reg_table[i++].addr = 0x4a009904;
	prcm_ctt_reg_table[i++].addr = 0x4a009908;
	prcm_ctt_reg_table[i++].addr = 0x4ae06108;
	prcm_ctt_reg_table[i++].addr = 0x4ae0610c;
	prcm_ctt_reg_table[i++].addr = 0x4ae06114;
	prcm_ctt_reg_table[i++].addr = 0x4ae06118;
	prcm_ctt_reg_table[i++].addr = 0x4ae06128;
	prcm_ctt_reg_table[i++].addr = 0x4ae0612c;
	prcm_ctt_reg_table[i++].addr = 0x4ae06130;
	prcm_ctt_reg_table[i++].addr = 0x4ae06134;
	prcm_ctt_reg_table[i++].addr = 0x4ae06138;
	prcm_ctt_reg_table[i++].addr = 0x4ae06144;
	prcm_ctt_reg_table[i++].addr = 0x4ae06148;
	prcm_ctt_reg_table[i++].addr = 0x4ae0614c;
	prcm_ctt_reg_table[i++].addr = 0x4ae06150;
	prcm_ctt_reg_table[i++].addr = 0x4ae06154;
	prcm_ctt_reg_table[i++].addr = 0x4ae06158;
	prcm_ctt_reg_table[i++].addr = 0x4ae06164;
	prcm_ctt_reg_table[i++].addr = 0x4ae06168;
	prcm_ctt_reg_table[i++].addr = 0x4ae0616c;
	prcm_ctt_reg_table[i++].addr = 0x4ae06170;
	prcm_ctt_reg_table[i++].addr = 0x4ae06174;
	prcm_ctt_reg_table[i++].addr = 0x4ae06178;
	prcm_ctt_reg_table[i++].addr = 0x4ae06180;
	prcm_ctt_reg_table[i++].addr = 0x4ae06184;
	prcm_ctt_reg_table[i++].addr = 0x4ae06188;
	prcm_ctt_reg_table[i++].addr = 0x4ae0618c;
	prcm_ctt_reg_table[i++].addr = 0x4ae06190;
	prcm_ctt_reg_table[i++].addr = 0x4ae06194;
	prcm_ctt_reg_table[i++].addr = 0x4ae06198;
	prcm_ctt_reg_table[i++].addr = 0x4ae0619c;
	prcm_ctt_reg_table[i++].addr = 0x4ae061a0;
	prcm_ctt_reg_table[i++].addr = 0x4ae061a4;
	prcm_ctt_reg_table[i++].addr = 0x4ae061a8;
	prcm_ctt_reg_table[i++].addr = 0x4ae061ac;
	prcm_ctt_reg_table[i++].addr = 0x4ae061b0;
	prcm_ctt_reg_table[i++].addr = 0x4ae061b4;
	prcm_ctt_reg_table[i++].addr = 0x4ae061b8;
	prcm_ctt_reg_table[i++].addr = 0x4ae061bc;
	prcm_ctt_reg_table[i++].addr = 0x4ae061c0;
	prcm_ctt_reg_table[i++].addr = 0x4ae061c8;
	prcm_ctt_reg_table[i++].addr = 0x4ae061cc;
	prcm_ctt_reg_table[i++].addr = 0x4ae061d0;
	prcm_ctt_reg_table[i++].addr = 0x4ae061d4;
	prcm_ctt_reg_table[i++].addr = 0x4ae061d8;
	prcm_ctt_reg_table[i++].addr = 0x4ae061e0;
	prcm_ctt_reg_table[i++].addr = 0x4ae07830;
	prcm_ctt_reg_table[i++].addr = 0x4ae07838;
	prcm_ctt_reg_table[i++].addr = 0x4ae07840;
	prcm_ctt_reg_table[i++].addr = 0x4ae07878;
	prcm_ctt_reg_table[i++].addr = 0x4ae07880;
	prcm_ctt_reg_table[i++].addr = 0x4ae07888;

	prcm_ctt_reg_table[i].addr = 0;

	dprintf("%s: last index=%d, size=%d\n", __func__, i, i + 1);

	return 0;
}
