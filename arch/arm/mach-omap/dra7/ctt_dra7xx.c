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

#define PRCM_CTT_REG_TABLE_SIZE        623

#define DEVICE_NAME "DRA7xx_ES1.0"

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

	printf("The Clock Tree Tool can import register settings from a *.rd1 "
		"file.\n");
	printf("The format of the *.rd1 file is:\n\n");
	printf("DeviceName DRA7xx_ES1.0\n");
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
		printf("DeviceName %s\n", DEVICE_NAME);
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

	CHECK_NULL_ARG(file, OMAPCONF_ERR_ARG);

	strcpy(fullfilename, file);
	fd = workdir_fopen(fullfilename, "w");
	if (fd == NULL) {
		printf("error: could not create %s file!\n", fullfilename);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	if (cpu_is_dra7xx())
		fprintf(fd, "DeviceName %s\n", DEVICE_NAME);
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
	/* Data from: CTT-DRA7xxES1.0-v1.12.0.0 */
	prcm_ctt_reg_table[i++].addr = 0x4AE06178;
	prcm_ctt_reg_table[i++].addr = 0x4A008C00;
	prcm_ctt_reg_table[i++].addr = 0x4A008C20;
	prcm_ctt_reg_table[i++].addr = 0x4A005128;
	prcm_ctt_reg_table[i++].addr = 0x4A005168;
	prcm_ctt_reg_table[i++].addr = 0x4A005218;
	prcm_ctt_reg_table[i++].addr = 0x4A00523C;
	prcm_ctt_reg_table[i++].addr = 0x4A00528C;
	prcm_ctt_reg_table[i++].addr = 0x4A0052B0;
	prcm_ctt_reg_table[i++].addr = 0x4A008148;
	prcm_ctt_reg_table[i++].addr = 0x4A008188;
	prcm_ctt_reg_table[i++].addr = 0x4A008208;
	prcm_ctt_reg_table[i++].addr = 0x4A0051A8;
	prcm_ctt_reg_table[i++].addr = 0x4A005254;
	prcm_ctt_reg_table[i++].addr = 0x4A0052A4;
	prcm_ctt_reg_table[i++].addr = 0x4A0051DC;
	prcm_ctt_reg_table[i++].addr = 0x4A00519C;
	prcm_ctt_reg_table[i++].addr = 0x4A00821C;
	prcm_ctt_reg_table[i++].addr = 0x4A005120;
	prcm_ctt_reg_table[i++].addr = 0x4A005160;
	prcm_ctt_reg_table[i++].addr = 0x4A005210;
	prcm_ctt_reg_table[i++].addr = 0x4A005234;
	prcm_ctt_reg_table[i++].addr = 0x4A005284;
	prcm_ctt_reg_table[i++].addr = 0x4A0052A8;
	prcm_ctt_reg_table[i++].addr = 0x4A0052D8;
	prcm_ctt_reg_table[i++].addr = 0x4A008140;
	prcm_ctt_reg_table[i++].addr = 0x4A008180;
	prcm_ctt_reg_table[i++].addr = 0x4A008200;
	prcm_ctt_reg_table[i++].addr = 0x4A0051A0;
	prcm_ctt_reg_table[i++].addr = 0x4A005108;
	prcm_ctt_reg_table[i++].addr = 0x4AE0611C;
	prcm_ctt_reg_table[i++].addr = 0x4AE06170;
	prcm_ctt_reg_table[i++].addr = 0x4AE06174;
	prcm_ctt_reg_table[i++].addr = 0x4AE061D8;
	prcm_ctt_reg_table[i++].addr = 0x4AE0610C;
	prcm_ctt_reg_table[i++].addr = 0x4AE06114;
	prcm_ctt_reg_table[i++].addr = 0x4AE06118;
	prcm_ctt_reg_table[i++].addr = 0x4AE06120;
	prcm_ctt_reg_table[i++].addr = 0x4AE06158;
	prcm_ctt_reg_table[i++].addr = 0x4AE0615C;
	prcm_ctt_reg_table[i++].addr = 0x4AE06160;
	prcm_ctt_reg_table[i++].addr = 0x4A005100;
	prcm_ctt_reg_table[i++].addr = 0x4AE06188;
	prcm_ctt_reg_table[i++].addr = 0x4A0051EC;
	prcm_ctt_reg_table[i++].addr = 0x4A00512C;
	prcm_ctt_reg_table[i++].addr = 0x4A00521C;
	prcm_ctt_reg_table[i++].addr = 0x4A005240;
	prcm_ctt_reg_table[i++].addr = 0x4A005290;
	prcm_ctt_reg_table[i++].addr = 0x4A0052B4;
	prcm_ctt_reg_table[i++].addr = 0x4A0052e4;
	prcm_ctt_reg_table[i++].addr = 0x4A0051AC;
	prcm_ctt_reg_table[i++].addr = 0x4A00516C;
	prcm_ctt_reg_table[i++].addr = 0x4A00820C;
	prcm_ctt_reg_table[i++].addr = 0x4A00814C;
	prcm_ctt_reg_table[i++].addr = 0x4A00818C;
	prcm_ctt_reg_table[i++].addr = 0x4AE0618C;
	prcm_ctt_reg_table[i++].addr = 0x4AE06190;
	prcm_ctt_reg_table[i++].addr = 0x4AE06194;
	prcm_ctt_reg_table[i++].addr = 0x4AE06180;
	prcm_ctt_reg_table[i++].addr = 0x4AE06198;
	prcm_ctt_reg_table[i++].addr = 0x4AE0619C;
	prcm_ctt_reg_table[i++].addr = 0x4AE061A0;
	prcm_ctt_reg_table[i++].addr = 0x4AE061A4;
	prcm_ctt_reg_table[i++].addr = 0x4AE06124;
	prcm_ctt_reg_table[i++].addr = 0x4AE06164;
	prcm_ctt_reg_table[i++].addr = 0x4AE06128;
	prcm_ctt_reg_table[i++].addr = 0x4AE061A8;
	prcm_ctt_reg_table[i++].addr = 0x4AE061AC;
	prcm_ctt_reg_table[i++].addr = 0x4AE0612C;
	prcm_ctt_reg_table[i++].addr = 0x4AE06134;
	prcm_ctt_reg_table[i++].addr = 0x4AE06130;
	prcm_ctt_reg_table[i++].addr = 0x4AE061B0;
	prcm_ctt_reg_table[i++].addr = 0x4AE061B4;
	prcm_ctt_reg_table[i++].addr = 0x4AE061B8;
	prcm_ctt_reg_table[i++].addr = 0x4AE06138;
	prcm_ctt_reg_table[i++].addr = 0x4AE061BC;
	prcm_ctt_reg_table[i++].addr = 0x4AE061C0;
	prcm_ctt_reg_table[i++].addr = 0x4AE06110;
	prcm_ctt_reg_table[i++].addr = 0x4AE06140;
	prcm_ctt_reg_table[i++].addr = 0x4AE061C8;
	prcm_ctt_reg_table[i++].addr = 0x4AE061CC;
	prcm_ctt_reg_table[i++].addr = 0x4AE06100;
	prcm_ctt_reg_table[i++].addr = 0x4AE06144;
	prcm_ctt_reg_table[i++].addr = 0x4A008104;
	prcm_ctt_reg_table[i++].addr = 0x4AE06184;
	prcm_ctt_reg_table[i++].addr = 0x4AE06148;
	prcm_ctt_reg_table[i++].addr = 0x4AE0614C;
	prcm_ctt_reg_table[i++].addr = 0x4AE06168;
	prcm_ctt_reg_table[i++].addr = 0x4AE061D0;
	prcm_ctt_reg_table[i++].addr = 0x4AE06150;
	prcm_ctt_reg_table[i++].addr = 0x4AE06154;
	prcm_ctt_reg_table[i++].addr = 0x4AE0616C;
	prcm_ctt_reg_table[i++].addr = 0x4AE061D4;
	prcm_ctt_reg_table[i++].addr = 0x4AE06108;
	prcm_ctt_reg_table[i++].addr = 0x4A005040;
	prcm_ctt_reg_table[i++].addr = 0x4A0050F0;
	prcm_ctt_reg_table[i++].addr = 0x4A0050F4;
	prcm_ctt_reg_table[i++].addr = 0x4A0050F8;
	prcm_ctt_reg_table[i++].addr = 0x4A0050FC;
	prcm_ctt_reg_table[i++].addr = 0x4A008600;
	prcm_ctt_reg_table[i++].addr = 0x4A008628;
	prcm_ctt_reg_table[i++].addr = 0x4A008638;
	prcm_ctt_reg_table[i++].addr = 0x4A008658;
	prcm_ctt_reg_table[i++].addr = 0x4A008668;
	prcm_ctt_reg_table[i++].addr = 0x4A008678;
	prcm_ctt_reg_table[i++].addr = 0x4A008640;
	prcm_ctt_reg_table[i++].addr = 0x4A008688;
	prcm_ctt_reg_table[i++].addr = 0x4A008698;
	prcm_ctt_reg_table[i++].addr = 0x4A005228;
	prcm_ctt_reg_table[i++].addr = 0x4A0052C0;
	prcm_ctt_reg_table[i++].addr = 0x4A008158;
	prcm_ctt_reg_table[i++].addr = 0x4A00513C;
	prcm_ctt_reg_table[i++].addr = 0x4A0052C4;
	prcm_ctt_reg_table[i++].addr = 0x4A00815C;
	prcm_ctt_reg_table[i++].addr = 0x4A005140;
	prcm_ctt_reg_table[i++].addr = 0x4A0052C8;
	prcm_ctt_reg_table[i++].addr = 0x4A008160;
	prcm_ctt_reg_table[i++].addr = 0x4A005144;
	prcm_ctt_reg_table[i++].addr = 0x4A008164;
	prcm_ctt_reg_table[i++].addr = 0x4A005154;
	prcm_ctt_reg_table[i++].addr = 0x4A005158;
	prcm_ctt_reg_table[i++].addr = 0x4A00515C;
	prcm_ctt_reg_table[i++].addr = 0x4A0051F0;
	prcm_ctt_reg_table[i++].addr = 0x4A005130;
	prcm_ctt_reg_table[i++].addr = 0x4A005220;
	prcm_ctt_reg_table[i++].addr = 0x4A005244;
	prcm_ctt_reg_table[i++].addr = 0x4A005294;
	prcm_ctt_reg_table[i++].addr = 0x4A0052B8;
	prcm_ctt_reg_table[i++].addr = 0x4A00520C;
	prcm_ctt_reg_table[i++].addr = 0x4A0051B0;
	prcm_ctt_reg_table[i++].addr = 0x4A005170;
	prcm_ctt_reg_table[i++].addr = 0x4A008210;
	prcm_ctt_reg_table[i++].addr = 0x4A008150;
	prcm_ctt_reg_table[i++].addr = 0x4A008190;
	prcm_ctt_reg_table[i++].addr = 0x4A0051F4;
	prcm_ctt_reg_table[i++].addr = 0x4A005248;
	prcm_ctt_reg_table[i++].addr = 0x4A0052BC;
	prcm_ctt_reg_table[i++].addr = 0x4A008154;
	prcm_ctt_reg_table[i++].addr = 0x4A005110;
	prcm_ctt_reg_table[i++].addr = 0x4A008A00;
	prcm_ctt_reg_table[i++].addr = 0x4A008A04;
	prcm_ctt_reg_table[i++].addr = 0x4A005270;
	prcm_ctt_reg_table[i++].addr = 0x4A008B00;
	prcm_ctt_reg_table[i++].addr = 0x4A008B40;
	prcm_ctt_reg_table[i++].addr = 0x4A008B30;
	prcm_ctt_reg_table[i++].addr = 0x4A008B38;
	prcm_ctt_reg_table[i++].addr = 0x4AE07A00;
	prcm_ctt_reg_table[i++].addr = 0x4AE07A08;
	prcm_ctt_reg_table[i++].addr = 0x4A0093C0;
	prcm_ctt_reg_table[i++].addr = 0x4A0093D0;
	prcm_ctt_reg_table[i++].addr = 0x4A0093C4;
	prcm_ctt_reg_table[i++].addr = 0x4A005540;
	prcm_ctt_reg_table[i++].addr = 0x4A005578;
	prcm_ctt_reg_table[i++].addr = 0x4A005550;
	prcm_ctt_reg_table[i++].addr = 0x4A005558;
	prcm_ctt_reg_table[i++].addr = 0x4A005560;
	prcm_ctt_reg_table[i++].addr = 0x4A005568;
	prcm_ctt_reg_table[i++].addr = 0x4A005570;
	prcm_ctt_reg_table[i++].addr = 0x4A005580;
	prcm_ctt_reg_table[i++].addr = 0x4A005500;
	prcm_ctt_reg_table[i++].addr = 0x4A005508;
	prcm_ctt_reg_table[i++].addr = 0x4A005520;
	prcm_ctt_reg_table[i++].addr = 0x4A005504;
	prcm_ctt_reg_table[i++].addr = 0x4A008900;
	prcm_ctt_reg_table[i++].addr = 0x4A008908;
	prcm_ctt_reg_table[i++].addr = 0x4A008920;
	prcm_ctt_reg_table[i++].addr = 0x4A008904;
	prcm_ctt_reg_table[i++].addr = 0x4A009358;
	prcm_ctt_reg_table[i++].addr = 0x4A009328;
	prcm_ctt_reg_table[i++].addr = 0x4A009330;
	prcm_ctt_reg_table[i++].addr = 0x4A009388;
	prcm_ctt_reg_table[i++].addr = 0x4A009304;
	prcm_ctt_reg_table[i++].addr = 0x4A009340;
	prcm_ctt_reg_table[i++].addr = 0x4A009348;
	prcm_ctt_reg_table[i++].addr = 0x4A009350;
	prcm_ctt_reg_table[i++].addr = 0x4A0093F0;
	prcm_ctt_reg_table[i++].addr = 0x4A008700;
	prcm_ctt_reg_table[i++].addr = 0x4A008708;
	prcm_ctt_reg_table[i++].addr = 0x4A008728;
	prcm_ctt_reg_table[i++].addr = 0x4A008778;
	prcm_ctt_reg_table[i++].addr = 0x4A008780;
	prcm_ctt_reg_table[i++].addr = 0x4A008D00;
	prcm_ctt_reg_table[i++].addr = 0x4A008D08;
	prcm_ctt_reg_table[i++].addr = 0x4A009700;
	prcm_ctt_reg_table[i++].addr = 0x4A009708;
	prcm_ctt_reg_table[i++].addr = 0x4A009760;
	prcm_ctt_reg_table[i++].addr = 0x4A009768;
	prcm_ctt_reg_table[i++].addr = 0x4A009770;
	prcm_ctt_reg_table[i++].addr = 0x4A009778;
	prcm_ctt_reg_table[i++].addr = 0x4A009780;
	prcm_ctt_reg_table[i++].addr = 0x4A009810;
	prcm_ctt_reg_table[i++].addr = 0x4A009810;
	prcm_ctt_reg_table[i++].addr = 0x4A009818;
	prcm_ctt_reg_table[i++].addr = 0x4A009818;
	prcm_ctt_reg_table[i++].addr = 0x4A009788;
	prcm_ctt_reg_table[i++].addr = 0x4A0097A0;
	prcm_ctt_reg_table[i++].addr = 0x4A0097A8;
	prcm_ctt_reg_table[i++].addr = 0x4A0097B0;
	prcm_ctt_reg_table[i++].addr = 0x4A0097B8;
	prcm_ctt_reg_table[i++].addr = 0x4A0097F0;
	prcm_ctt_reg_table[i++].addr = 0x4A0097F0;
	prcm_ctt_reg_table[i++].addr = 0x4A0097F8;
	prcm_ctt_reg_table[i++].addr = 0x4A0097F8;
	prcm_ctt_reg_table[i++].addr = 0x4A009800;
	prcm_ctt_reg_table[i++].addr = 0x4A009800;
	prcm_ctt_reg_table[i++].addr = 0x4A009808;
	prcm_ctt_reg_table[i++].addr = 0x4A009808;
	prcm_ctt_reg_table[i++].addr = 0x4A009820;
	prcm_ctt_reg_table[i++].addr = 0x4A009820;
	prcm_ctt_reg_table[i++].addr = 0x4A009828;
	prcm_ctt_reg_table[i++].addr = 0x4A009828;
	prcm_ctt_reg_table[i++].addr = 0x4A009728;
	prcm_ctt_reg_table[i++].addr = 0x4A009730;
	prcm_ctt_reg_table[i++].addr = 0x4A009738;
	prcm_ctt_reg_table[i++].addr = 0x4A009740;
	prcm_ctt_reg_table[i++].addr = 0x4A009748;
	prcm_ctt_reg_table[i++].addr = 0x4A009750;
	prcm_ctt_reg_table[i++].addr = 0x4A009840;
	prcm_ctt_reg_table[i++].addr = 0x4A009840;
	prcm_ctt_reg_table[i++].addr = 0x4A009848;
	prcm_ctt_reg_table[i++].addr = 0x4A009848;
	prcm_ctt_reg_table[i++].addr = 0x4A009850;
	prcm_ctt_reg_table[i++].addr = 0x4A009850;
	prcm_ctt_reg_table[i++].addr = 0x4A009858;
	prcm_ctt_reg_table[i++].addr = 0x4A009858;
	prcm_ctt_reg_table[i++].addr = 0x4A009870;
	prcm_ctt_reg_table[i++].addr = 0x4A009870;
	prcm_ctt_reg_table[i++].addr = 0x4A009860;
	prcm_ctt_reg_table[i++].addr = 0x4A009860;
	prcm_ctt_reg_table[i++].addr = 0x4A009868;
	prcm_ctt_reg_table[i++].addr = 0x4A009868;
	prcm_ctt_reg_table[i++].addr = 0x4A009898;
	prcm_ctt_reg_table[i++].addr = 0x4A009898;
	prcm_ctt_reg_table[i++].addr = 0x4A009878;
	prcm_ctt_reg_table[i++].addr = 0x4A009878;
	prcm_ctt_reg_table[i++].addr = 0x4A009890;
	prcm_ctt_reg_table[i++].addr = 0x4A009890;
	prcm_ctt_reg_table[i++].addr = 0x4A0097C4;
	prcm_ctt_reg_table[i++].addr = 0x4A0097C4;
	prcm_ctt_reg_table[i++].addr = 0x4A009790;
	prcm_ctt_reg_table[i++].addr = 0x4A009798;
	prcm_ctt_reg_table[i++].addr = 0x4A009838;
	prcm_ctt_reg_table[i++].addr = 0x4A009838;
	prcm_ctt_reg_table[i++].addr = 0x4A0097C8;
	prcm_ctt_reg_table[i++].addr = 0x4A0097C8;
	prcm_ctt_reg_table[i++].addr = 0x4A0097D0;
	prcm_ctt_reg_table[i++].addr = 0x4A0097D0;
	prcm_ctt_reg_table[i++].addr = 0x4A0097D8;
	prcm_ctt_reg_table[i++].addr = 0x4A0097D8;
	prcm_ctt_reg_table[i++].addr = 0x4A009830;
	prcm_ctt_reg_table[i++].addr = 0x4A009830;
	prcm_ctt_reg_table[i++].addr = 0x4A009880;
	prcm_ctt_reg_table[i++].addr = 0x4A009880;
	prcm_ctt_reg_table[i++].addr = 0x4A009884;
	prcm_ctt_reg_table[i++].addr = 0x4A009884;
	prcm_ctt_reg_table[i++].addr = 0x4A005300;
	prcm_ctt_reg_table[i++].addr = 0x4A005308;
	prcm_ctt_reg_table[i++].addr = 0x4A005320;
	prcm_ctt_reg_table[i++].addr = 0x4A005304;
	prcm_ctt_reg_table[i++].addr = 0x4A0093A0;
	prcm_ctt_reg_table[i++].addr = 0x4A0093B0;
	prcm_ctt_reg_table[i++].addr = 0x4A0093B8;
	prcm_ctt_reg_table[i++].addr = 0x4A0093A4;
	prcm_ctt_reg_table[i++].addr = 0x4AE06040;
	prcm_ctt_reg_table[i++].addr = 0x4A005260;
	prcm_ctt_reg_table[i++].addr = 0x4A005264;
	prcm_ctt_reg_table[i++].addr = 0x4A005148;
	prcm_ctt_reg_table[i++].addr = 0x4A005188;
	prcm_ctt_reg_table[i++].addr = 0x4A0051C8;
	prcm_ctt_reg_table[i++].addr = 0x4A005208;
	prcm_ctt_reg_table[i++].addr = 0x4A00522C;
	prcm_ctt_reg_table[i++].addr = 0x4A00524C;
	prcm_ctt_reg_table[i++].addr = 0x4A00529C;
	prcm_ctt_reg_table[i++].addr = 0x4A0052D0;
	prcm_ctt_reg_table[i++].addr = 0x4A0052F0;
	prcm_ctt_reg_table[i++].addr = 0x4A008168;
	prcm_ctt_reg_table[i++].addr = 0x4A0081A8;
	prcm_ctt_reg_table[i++].addr = 0x4A008214;
	prcm_ctt_reg_table[i++].addr = 0x4A00514C;
	prcm_ctt_reg_table[i++].addr = 0x4A00518C;
	prcm_ctt_reg_table[i++].addr = 0x4A0051CC;
	prcm_ctt_reg_table[i++].addr = 0x4A00520C;
	prcm_ctt_reg_table[i++].addr = 0x4A005230;
	prcm_ctt_reg_table[i++].addr = 0x4A005250;
	prcm_ctt_reg_table[i++].addr = 0x4A0052D4;
	prcm_ctt_reg_table[i++].addr = 0x4A0052F4;
	prcm_ctt_reg_table[i++].addr = 0x4A00816C;
	prcm_ctt_reg_table[i++].addr = 0x4A0081AC;
	prcm_ctt_reg_table[i++].addr = 0x4A008218;
	prcm_ctt_reg_table[i++].addr = 0x4AE07800;
	prcm_ctt_reg_table[i++].addr = 0x4AE07888;
	prcm_ctt_reg_table[i++].addr = 0x4AE07838;
	prcm_ctt_reg_table[i++].addr = 0x4AE07878;
	prcm_ctt_reg_table[i++].addr = 0x4AE07840;
	prcm_ctt_reg_table[i++].addr = 0x4AE07880;
	prcm_ctt_reg_table[i++].addr = 0x4AE07830;
	prcm_ctt_reg_table[i++].addr = 0x4AE07000;
	prcm_ctt_reg_table[i++].addr = 0x4AE07004;
	prcm_ctt_reg_table[i++].addr = 0x4AE07020;
	prcm_ctt_reg_table[i++].addr = 0x4AE07028;
	prcm_ctt_reg_table[i++].addr = 0x4AE07030;
	prcm_ctt_reg_table[i++].addr = 0x4AE06700;
	prcm_ctt_reg_table[i++].addr = 0x4AE06704;
	prcm_ctt_reg_table[i++].addr = 0x4AE06638;
	prcm_ctt_reg_table[i++].addr = 0x4AE06658;
	prcm_ctt_reg_table[i++].addr = 0x4AE06668;
	prcm_ctt_reg_table[i++].addr = 0x4AE06678;
	prcm_ctt_reg_table[i++].addr = 0x4AE06400;
	prcm_ctt_reg_table[i++].addr = 0x4AE06404;
	prcm_ctt_reg_table[i++].addr = 0x4AE07B00;
	prcm_ctt_reg_table[i++].addr = 0x4AE07B04;
	prcm_ctt_reg_table[i++].addr = 0x4AE07120;
	prcm_ctt_reg_table[i++].addr = 0x4AE07128;
	prcm_ctt_reg_table[i++].addr = 0x4AE07100;
	prcm_ctt_reg_table[i++].addr = 0x4AE07104;
	prcm_ctt_reg_table[i++].addr = 0x4AE07900;
	prcm_ctt_reg_table[i++].addr = 0x4AE07904;
	prcm_ctt_reg_table[i++].addr = 0x4AE07B60;
	prcm_ctt_reg_table[i++].addr = 0x4AE07B60;
	prcm_ctt_reg_table[i++].addr = 0x4AE07B40;
	prcm_ctt_reg_table[i++].addr = 0x4AE07B40;
	prcm_ctt_reg_table[i++].addr = 0x4AE07B44;
	prcm_ctt_reg_table[i++].addr = 0x4AE07B44;
	prcm_ctt_reg_table[i++].addr = 0x4AE07BA0;
	prcm_ctt_reg_table[i++].addr = 0x4AE07B80;
	prcm_ctt_reg_table[i++].addr = 0x4AE07B84;
	prcm_ctt_reg_table[i++].addr = 0x4AE06578;
	prcm_ctt_reg_table[i++].addr = 0x4AE06550;
	prcm_ctt_reg_table[i++].addr = 0x4AE06500;
	prcm_ctt_reg_table[i++].addr = 0x4AE06504;
	prcm_ctt_reg_table[i++].addr = 0x4AE06558;
	prcm_ctt_reg_table[i++].addr = 0x4AE06560;
	prcm_ctt_reg_table[i++].addr = 0x4AE06568;
	prcm_ctt_reg_table[i++].addr = 0x4AE06570;
	prcm_ctt_reg_table[i++].addr = 0x4AE06580;
	prcm_ctt_reg_table[i++].addr = 0x4AE06F00;
	prcm_ctt_reg_table[i++].addr = 0x4AE06F04;
	prcm_ctt_reg_table[i++].addr = 0x4AE07328;
	prcm_ctt_reg_table[i++].addr = 0x4AE07330;
	prcm_ctt_reg_table[i++].addr = 0x4AE07300;
	prcm_ctt_reg_table[i++].addr = 0x4AE07304;
	prcm_ctt_reg_table[i++].addr = 0x4AE07388;
	prcm_ctt_reg_table[i++].addr = 0x4AE07340;
	prcm_ctt_reg_table[i++].addr = 0x4AE07348;
	prcm_ctt_reg_table[i++].addr = 0x4AE07350;
	prcm_ctt_reg_table[i++].addr = 0x4AE073F0;
	prcm_ctt_reg_table[i++].addr = 0x4AE06750;
	prcm_ctt_reg_table[i++].addr = 0x4AE06758;
	prcm_ctt_reg_table[i++].addr = 0x4AE06760;
	prcm_ctt_reg_table[i++].addr = 0x4AE06770;
	prcm_ctt_reg_table[i++].addr = 0x4AE06778;
	prcm_ctt_reg_table[i++].addr = 0x4AE06780;
	prcm_ctt_reg_table[i++].addr = 0x4AE07460;
	prcm_ctt_reg_table[i++].addr = 0x4AE07468;
	prcm_ctt_reg_table[i++].addr = 0x4AE07470;
	prcm_ctt_reg_table[i++].addr = 0x4AE07480;
	prcm_ctt_reg_table[i++].addr = 0x4AE07510;
	prcm_ctt_reg_table[i++].addr = 0x4AE07518;
	prcm_ctt_reg_table[i++].addr = 0x4AE074A0;
	prcm_ctt_reg_table[i++].addr = 0x4AE074A8;
	prcm_ctt_reg_table[i++].addr = 0x4AE074B0;
	prcm_ctt_reg_table[i++].addr = 0x4AE074B8;
	prcm_ctt_reg_table[i++].addr = 0x4AE074F0;
	prcm_ctt_reg_table[i++].addr = 0x4AE074F8;
	prcm_ctt_reg_table[i++].addr = 0x4AE07500;
	prcm_ctt_reg_table[i++].addr = 0x4AE07508;
	prcm_ctt_reg_table[i++].addr = 0x4AE07520;
	prcm_ctt_reg_table[i++].addr = 0x4AE07528;
	prcm_ctt_reg_table[i++].addr = 0x4AE07400;
	prcm_ctt_reg_table[i++].addr = 0x4AE07404;
	prcm_ctt_reg_table[i++].addr = 0x4AE07428;
	prcm_ctt_reg_table[i++].addr = 0x4AE07430;
	prcm_ctt_reg_table[i++].addr = 0x4AE074C8;
	prcm_ctt_reg_table[i++].addr = 0x4AE074D0;
	prcm_ctt_reg_table[i++].addr = 0x4AE074D8;
	prcm_ctt_reg_table[i++].addr = 0x4AE07530;
	prcm_ctt_reg_table[i++].addr = 0x4AE07438;
	prcm_ctt_reg_table[i++].addr = 0x4AE07440;
	prcm_ctt_reg_table[i++].addr = 0x4AE07448;
	prcm_ctt_reg_table[i++].addr = 0x4AE07450;
	prcm_ctt_reg_table[i++].addr = 0x4AE07540;
	prcm_ctt_reg_table[i++].addr = 0x4AE07548;
	prcm_ctt_reg_table[i++].addr = 0x4AE07550;
	prcm_ctt_reg_table[i++].addr = 0x4AE07558;
	prcm_ctt_reg_table[i++].addr = 0x4AE07570;
	prcm_ctt_reg_table[i++].addr = 0x4ae075f0;
	prcm_ctt_reg_table[i++].addr = 0x4ae07560;
	prcm_ctt_reg_table[i++].addr = 0x4ae07568;
	prcm_ctt_reg_table[i++].addr = 0x4ae07598;
	prcm_ctt_reg_table[i++].addr = 0x4ae07578;
	prcm_ctt_reg_table[i++].addr = 0x4ae07580;
	prcm_ctt_reg_table[i++].addr = 0x4ae07588;
	prcm_ctt_reg_table[i++].addr = 0x4ae07590;
	prcm_ctt_reg_table[i++].addr = 0x4ae07538;
	prcm_ctt_reg_table[i++].addr = 0x4ae075d0;
	prcm_ctt_reg_table[i++].addr = 0x4ae06300;
	prcm_ctt_reg_table[i++].addr = 0x4ae06304;
	prcm_ctt_reg_table[i++].addr = 0x4ae073b0;
	prcm_ctt_reg_table[i++].addr = 0x4ae073b8;
	prcm_ctt_reg_table[i++].addr = 0x4ae07c80;
	prcm_ctt_reg_table[i++].addr = 0x4ae07c84;
	prcm_ctt_reg_table[i++].addr = 0x4ae07ca0;
	prcm_ctt_reg_table[i++].addr = 0x4ae060e8;
	prcm_ctt_reg_table[i++].addr = 0x4ae060ec;
	prcm_ctt_reg_table[i++].addr = 0x4ae07df0;
	prcm_ctt_reg_table[i++].addr = 0x4ae07d1c;
	prcm_ctt_reg_table[i++].addr = 0x4ae07d20;
	prcm_ctt_reg_table[i++].addr = 0x4ae06038;
	prcm_ctt_reg_table[i++].addr = 0x4ae06044;
	prcm_ctt_reg_table[i++].addr = 0x4ae06048;
	prcm_ctt_reg_table[i++].addr = 0x4ae0604c;
	prcm_ctt_reg_table[i++].addr = 0x4ae06028;
	prcm_ctt_reg_table[i++].addr = 0x4ae06058;
	prcm_ctt_reg_table[i++].addr = 0x4ae0601c;
	prcm_ctt_reg_table[i++].addr = 0x4ae06030;
	prcm_ctt_reg_table[i++].addr = 0x4ae0605c;
	prcm_ctt_reg_table[i++].addr = 0x4ae06060;
	prcm_ctt_reg_table[i++].addr = 0x4ae06064;
	prcm_ctt_reg_table[i++].addr = 0x4ae06020;
	prcm_ctt_reg_table[i++].addr = 0x4ae06070;
	prcm_ctt_reg_table[i++].addr = 0x4ae06010;
	prcm_ctt_reg_table[i++].addr = 0x4ae06014;
	prcm_ctt_reg_table[i++].addr = 0x4ae07d18;
	prcm_ctt_reg_table[i++].addr = 0x4ae07d00;
	prcm_ctt_reg_table[i++].addr = 0x4ae07d04;
	prcm_ctt_reg_table[i++].addr = 0x4ae07d08;
	prcm_ctt_reg_table[i++].addr = 0x4ae07dc4;
	prcm_ctt_reg_table[i++].addr = 0x4ae07dd8;
	prcm_ctt_reg_table[i++].addr = 0x4ae07dd4;
	prcm_ctt_reg_table[i++].addr = 0x4ae07e2c;
	prcm_ctt_reg_table[i++].addr = 0x4ae07e1c;
	prcm_ctt_reg_table[i++].addr = 0x4ae07dd0;
	prcm_ctt_reg_table[i++].addr = 0x4ae07dcc;
	prcm_ctt_reg_table[i++].addr = 0x4ae07dbc;
	prcm_ctt_reg_table[i++].addr = 0x4ae06c24;
	prcm_ctt_reg_table[i++].addr = 0x4ae07024;
	prcm_ctt_reg_table[i++].addr = 0x4ae0702c;
	prcm_ctt_reg_table[i++].addr = 0x4ae07034;
	prcm_ctt_reg_table[i++].addr = 0x4ae0663c;
	prcm_ctt_reg_table[i++].addr = 0x4ae0665c;
	prcm_ctt_reg_table[i++].addr = 0x4ae0666c;
	prcm_ctt_reg_table[i++].addr = 0x4ae0667c;
	prcm_ctt_reg_table[i++].addr = 0x4ae06a24;
	prcm_ctt_reg_table[i++].addr = 0x4ae06424;
	prcm_ctt_reg_table[i++].addr = 0x4ae06410;
	prcm_ctt_reg_table[i++].addr = 0x4ae06414;
	prcm_ctt_reg_table[i++].addr = 0x4ae07b24;
	prcm_ctt_reg_table[i++].addr = 0x4ae07b10;
	prcm_ctt_reg_table[i++].addr = 0x4ae07b14;
	prcm_ctt_reg_table[i++].addr = 0x4ae07134;
	prcm_ctt_reg_table[i++].addr = 0x4ae07124;
	prcm_ctt_reg_table[i++].addr = 0x4ae06b24;
	prcm_ctt_reg_table[i++].addr = 0x4ae06b44;
	prcm_ctt_reg_table[i++].addr = 0x4ae06b2c;
	prcm_ctt_reg_table[i++].addr = 0x4ae06b34;
	prcm_ctt_reg_table[i++].addr = 0x4ae06b3c;
	prcm_ctt_reg_table[i++].addr = 0x4ae07b64;
	prcm_ctt_reg_table[i++].addr = 0x4ae07b64;
	prcm_ctt_reg_table[i++].addr = 0x4ae07b50;
	prcm_ctt_reg_table[i++].addr = 0x4ae07b50;
	prcm_ctt_reg_table[i++].addr = 0x4ae07b54;
	prcm_ctt_reg_table[i++].addr = 0x4ae07b54;
	prcm_ctt_reg_table[i++].addr = 0x4ae07ba4;
	prcm_ctt_reg_table[i++].addr = 0x4ae07b90;
	prcm_ctt_reg_table[i++].addr = 0x4ae07b94;
	prcm_ctt_reg_table[i++].addr = 0x4ae073d4;
	prcm_ctt_reg_table[i++].addr = 0x4ae0657c;
	prcm_ctt_reg_table[i++].addr = 0x4ae06554;
	prcm_ctt_reg_table[i++].addr = 0x4ae0655c;
	prcm_ctt_reg_table[i++].addr = 0x4ae06564;
	prcm_ctt_reg_table[i++].addr = 0x4ae0656c;
	prcm_ctt_reg_table[i++].addr = 0x4ae06574;
	prcm_ctt_reg_table[i++].addr = 0x4ae06584;
	prcm_ctt_reg_table[i++].addr = 0x4AE06524;
	prcm_ctt_reg_table[i++].addr = 0x4AE06510;
	prcm_ctt_reg_table[i++].addr = 0x4AE06514;
	prcm_ctt_reg_table[i++].addr = 0x4AE06924;
	prcm_ctt_reg_table[i++].addr = 0x4AE06910;
	prcm_ctt_reg_table[i++].addr = 0x4AE06914;
	prcm_ctt_reg_table[i++].addr = 0x4AE06F24;
	prcm_ctt_reg_table[i++].addr = 0x4AE06F10;
	prcm_ctt_reg_table[i++].addr = 0x4AE06F14;
	prcm_ctt_reg_table[i++].addr = 0x4AE06F2C;
	prcm_ctt_reg_table[i++].addr = 0x4AE0737C;
	prcm_ctt_reg_table[i++].addr = 0x4AE0735C;
	prcm_ctt_reg_table[i++].addr = 0x4AE0732C;
	prcm_ctt_reg_table[i++].addr = 0x4AE07334;
	prcm_ctt_reg_table[i++].addr = 0x4AE073EC;
	prcm_ctt_reg_table[i++].addr = 0x4AE0738C;
	prcm_ctt_reg_table[i++].addr = 0x4AE07344;
	prcm_ctt_reg_table[i++].addr = 0x4AE0734C;
	prcm_ctt_reg_table[i++].addr = 0x4AE07354;
	prcm_ctt_reg_table[i++].addr = 0x4AE073F4;
	prcm_ctt_reg_table[i++].addr = 0x4AE0672C;
	prcm_ctt_reg_table[i++].addr = 0x4AE06724;
	prcm_ctt_reg_table[i++].addr = 0x4AE06734;
	prcm_ctt_reg_table[i++].addr = 0x4AE0674C;
	prcm_ctt_reg_table[i++].addr = 0x4AE06754;
	prcm_ctt_reg_table[i++].addr = 0x4AE0675C;
	prcm_ctt_reg_table[i++].addr = 0x4AE06764;
	prcm_ctt_reg_table[i++].addr = 0x4AE0676C;
	prcm_ctt_reg_table[i++].addr = 0x4AE06774;
	prcm_ctt_reg_table[i++].addr = 0x4AE0677C;
	prcm_ctt_reg_table[i++].addr = 0x4AE06784;
	prcm_ctt_reg_table[i++].addr = 0x4AE0678C;
	prcm_ctt_reg_table[i++].addr = 0x4AE06794;
	prcm_ctt_reg_table[i++].addr = 0x4AE06D24;
	prcm_ctt_reg_table[i++].addr = 0x4AE06D34;
	prcm_ctt_reg_table[i++].addr = 0x4AE06D8C;
	prcm_ctt_reg_table[i++].addr = 0x4AE06D94;
	prcm_ctt_reg_table[i++].addr = 0x4AE06D9C;
	prcm_ctt_reg_table[i++].addr = 0x4AE06DA4;
	prcm_ctt_reg_table[i++].addr = 0x4AE06D4C;
	prcm_ctt_reg_table[i++].addr = 0x4AE06D54;
	prcm_ctt_reg_table[i++].addr = 0x4AE06D5C;
	prcm_ctt_reg_table[i++].addr = 0x4AE06D64;
	prcm_ctt_reg_table[i++].addr = 0x4AE06D6C;
	prcm_ctt_reg_table[i++].addr = 0x4AE06D74;
	prcm_ctt_reg_table[i++].addr = 0x4AE06D7C;
	prcm_ctt_reg_table[i++].addr = 0x4AE06D84;
	prcm_ctt_reg_table[i++].addr = 0x4AE06D44;
	prcm_ctt_reg_table[i++].addr = 0x4AE06D3C;
	prcm_ctt_reg_table[i++].addr = 0x4AE06D2C;
	prcm_ctt_reg_table[i++].addr = 0x4AE0745C;
	prcm_ctt_reg_table[i++].addr = 0x4AE07464;
	prcm_ctt_reg_table[i++].addr = 0x4AE07474;
	prcm_ctt_reg_table[i++].addr = 0x4AE0747C;
	prcm_ctt_reg_table[i++].addr = 0x4AE07484;
	prcm_ctt_reg_table[i++].addr = 0x4AE07514;
	prcm_ctt_reg_table[i++].addr = 0x4AE0751C;
	prcm_ctt_reg_table[i++].addr = 0x4AE0748C;
	prcm_ctt_reg_table[i++].addr = 0x4AE074A4;
	prcm_ctt_reg_table[i++].addr = 0x4AE074AC;
	prcm_ctt_reg_table[i++].addr = 0x4AE074B4;
	prcm_ctt_reg_table[i++].addr = 0x4AE074BC;
	prcm_ctt_reg_table[i++].addr = 0x4AE074C0;
	prcm_ctt_reg_table[i++].addr = 0x4AE074F4;
	prcm_ctt_reg_table[i++].addr = 0x4AE074FC;
	prcm_ctt_reg_table[i++].addr = 0x4AE07504;
	prcm_ctt_reg_table[i++].addr = 0x4AE0750C;
	prcm_ctt_reg_table[i++].addr = 0x4AE0752C;
	prcm_ctt_reg_table[i++].addr = 0x4AE0742C;
	prcm_ctt_reg_table[i++].addr = 0x4AE07434;
	prcm_ctt_reg_table[i++].addr = 0x4AE0743C;
	prcm_ctt_reg_table[i++].addr = 0x4AE07444;
	prcm_ctt_reg_table[i++].addr = 0x4AE0744C;
	prcm_ctt_reg_table[i++].addr = 0x4AE07454;
	prcm_ctt_reg_table[i++].addr = 0x4AE07544;
	prcm_ctt_reg_table[i++].addr = 0x4AE0754C;
	prcm_ctt_reg_table[i++].addr = 0x4AE07554;
	prcm_ctt_reg_table[i++].addr = 0x4AE0755C;
	prcm_ctt_reg_table[i++].addr = 0x4AE07574;
	prcm_ctt_reg_table[i++].addr = 0x4AE075F4;
	prcm_ctt_reg_table[i++].addr = 0x4AE0740C;
	prcm_ctt_reg_table[i++].addr = 0x4AE07564;
	prcm_ctt_reg_table[i++].addr = 0x4AE0756C;
	prcm_ctt_reg_table[i++].addr = 0x4AE0759C;
	prcm_ctt_reg_table[i++].addr = 0x4AE0757C;
	prcm_ctt_reg_table[i++].addr = 0x4AE07584;
	prcm_ctt_reg_table[i++].addr = 0x4AE0758C;
	prcm_ctt_reg_table[i++].addr = 0x4AE07594;
	prcm_ctt_reg_table[i++].addr = 0x4AE074C4;
	prcm_ctt_reg_table[i++].addr = 0x4AE07494;
	prcm_ctt_reg_table[i++].addr = 0x4AE0749C;
	prcm_ctt_reg_table[i++].addr = 0x4AE0753C;
	prcm_ctt_reg_table[i++].addr = 0x4AE075D4;
	prcm_ctt_reg_table[i++].addr = 0x4AE075EC;
	prcm_ctt_reg_table[i++].addr = 0x4AE07414;
	prcm_ctt_reg_table[i++].addr = 0x4AE074CC;
	prcm_ctt_reg_table[i++].addr = 0x4AE074D4;
	prcm_ctt_reg_table[i++].addr = 0x4AE074DC;
	prcm_ctt_reg_table[i++].addr = 0x4AE07534;
	prcm_ctt_reg_table[i++].addr = 0x4AE075A4;
	prcm_ctt_reg_table[i++].addr = 0x4AE075AC;
	prcm_ctt_reg_table[i++].addr = 0x4AE075B4;
	prcm_ctt_reg_table[i++].addr = 0x4AE075DC;
	prcm_ctt_reg_table[i++].addr = 0x4AE075BC;
	prcm_ctt_reg_table[i++].addr = 0x4AE075C4;
	prcm_ctt_reg_table[i++].addr = 0x4AE075CC;
	prcm_ctt_reg_table[i++].addr = 0x4AE075FC;
	prcm_ctt_reg_table[i++].addr = 0x4AE06324;
	prcm_ctt_reg_table[i++].addr = 0x4AE073B4;
	prcm_ctt_reg_table[i++].addr = 0x4AE073BC;
	prcm_ctt_reg_table[i++].addr = 0x4AE07310;
	prcm_ctt_reg_table[i++].addr = 0x4AE07314;
	prcm_ctt_reg_table[i++].addr = 0x4AE07CA4;
	/* new added */
	prcm_ctt_reg_table[i++].addr = 0x4A0051E0;
	prcm_ctt_reg_table[i++].addr = 0x4A0052D8;
	prcm_ctt_reg_table[i++].addr = 0x4A0052E4;
	prcm_ctt_reg_table[i++].addr = 0x4A0052E8;
	prcm_ctt_reg_table[i++].addr = 0x4A005420;
	prcm_ctt_reg_table[i++].addr = 0x4A005620;
	prcm_ctt_reg_table[i++].addr = 0x4A005660;
	prcm_ctt_reg_table[i++].addr = 0x4A0056A0;
	prcm_ctt_reg_table[i++].addr = 0x4A005744;
	prcm_ctt_reg_table[i++].addr = 0x4A005764;
	prcm_ctt_reg_table[i++].addr = 0x4A008E20;
	prcm_ctt_reg_table[i++].addr = 0x4A008E28;
	prcm_ctt_reg_table[i++].addr = 0x4A008E40;
	prcm_ctt_reg_table[i++].addr = 0x4A008E50;
	prcm_ctt_reg_table[i++].addr = 0x4A008F20;
	prcm_ctt_reg_table[i++].addr = 0x4A008F28;
	prcm_ctt_reg_table[i++].addr = 0x4A009020;
	prcm_ctt_reg_table[i++].addr = 0x4A009028;
	prcm_ctt_reg_table[i++].addr = 0x4A009030;
	prcm_ctt_reg_table[i++].addr = 0x4A009130;
	prcm_ctt_reg_table[i++].addr = 0x4A009220;
	prcm_ctt_reg_table[i++].addr = 0x4A0093E0;
	prcm_ctt_reg_table[i++].addr = 0x4A0093E8;
	prcm_ctt_reg_table[i++].addr = 0x4A009620;
	prcm_ctt_reg_table[i++].addr = 0x4A0098A0;
	prcm_ctt_reg_table[i++].addr = 0x4A0098A8;
	prcm_ctt_reg_table[i++].addr = 0x4A0098B0;
	prcm_ctt_reg_table[i++].addr = 0x4A0098B8;
	prcm_ctt_reg_table[i++].addr = 0x4A0098C0;
	prcm_ctt_reg_table[i++].addr = 0x4A0098D0;
	prcm_ctt_reg_table[i++].addr = 0x4A0098E0;
	prcm_ctt_reg_table[i++].addr = 0x4A0098E8;
	prcm_ctt_reg_table[i++].addr = 0x4A0098F0;
	prcm_ctt_reg_table[i++].addr = 0x4A0098F8;
	prcm_ctt_reg_table[i++].addr = 0x4A009904;
	prcm_ctt_reg_table[i++].addr = 0x4A009908;
	prcm_ctt_reg_table[i].addr = 0;

	dprintf("%s: last index=%d, size=%d\n", __func__, i, i + 1);

	return 0;
}
