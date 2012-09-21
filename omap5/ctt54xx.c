/*
 *
 * @Component			OMAPCONF
 * @Filename			ctt54xx.c
 * @Description			Display PRCM registers in a format that can be
 *				imported into the clock tree tool (CTT)
 * @Author			Jon Hunter (jon-hunter@ti.com)
 * @Date			2012
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
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


#include <ctt54xx.h>
#include <lib.h>
#include <help.h>
#include <lib.h>
#include <mem.h>
#include <cpuinfo.h>
#include <string.h>

/* #define CTT54XX_DEBUG */
#ifdef CTT54XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

#define PRCM_CTT_REG_TABLE_SIZE        135

static reg_table prcm_ctt_reg_table[PRCM_CTT_REG_TABLE_SIZE];

static int ctt54xx_regtable_init(void);

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		ctt54xx_dump
 * @BRIEF		dump PRCM registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		dump PRCM registers
 *//*------------------------------------------------------------------------ */
int ctt54xx_dump(void)
{
	unsigned int i = 0;
	unsigned int ret, val = 0;
	int err = 0;

	printf("The Clock Tree Tool can import register settings from a *.rd1 "
		"file.\n");
	printf("The format of the *.rd1 file is:\n\n");
	printf("DeviceName OMAPxxxx_ESx.x\n");
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

	if (cpu_is_omap54xx())
		printf("DeviceName OMAP543x_ES1.0\n");
	else
		return OMAPCONF_ERR_CPU;

	ctt54xx_regtable_init();

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
 * @FUNCTION		ctt54xx_rd1_export
 * @BRIEF		export PRCM registers in CTT RD1 format
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		file: output file name
 * @DESCRIPTION		export PRCM registers in CTT RD1 format
 *//*------------------------------------------------------------------------ */
int ctt54xx_rd1_export(char *file)
{
	unsigned int i = 0;
	unsigned int ret, val = 0;
	int err = 0;
	FILE *fd = NULL;
	char fullfilename[128];

	CHECK_CPU(54xx, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(file, OMAPCONF_ERR_ARG);

	strcpy(fullfilename, file);
	fd = workdir_fopen(fullfilename, "w");
	if (fd == NULL) {
		printf("error: could not create %s file!\n", fullfilename);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	if (cpu_is_omap54xx())
		fprintf(fd, "DeviceName OMAP543x_ES1.0\n");
	else
		return OMAPCONF_ERR_CPU;

	ctt54xx_regtable_init();

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
 * @FUNCTION		ctt54xx_main
 * @BRIEF		CTT main menu
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		CTT main menu
 *//*------------------------------------------------------------------------ */
int ctt54xx_main(int argc, char *argv[])
{
	int ret;

	CHECK_CPU(54xx, OMAPCONF_ERR_ARG);

	if (argc == 1) {
		ctt54xx_regtable_init();

		if (strcmp(argv[0], "dump") == 0)
			ret = ctt54xx_dump();
		else if (strcmp(argv[0], "rd1") == 0)
			ret = ctt54xx_rd1_export(
				"CTT-OMAP543xES1-REG_DUMP.rd1");
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
 * @FUNCTION		ctt54xx_regtable_init
 * @BRIEF		initialize regtable
 * @RETURNS		0
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		initialize regtable
 *//*------------------------------------------------------------------------ */
static int ctt54xx_regtable_init(void)
{
	int i = 0;

	CHECK_CPU(54xx, OMAPCONF_ERR_ARG);

	/* Init PRCM registers table */
	prcm_ctt_reg_table[i++].addr = 0x4a004100;
	prcm_ctt_reg_table[i++].addr = 0x4a004108;
	prcm_ctt_reg_table[i++].addr = 0x4a004120;
	prcm_ctt_reg_table[i++].addr = 0x4a00412c;
	prcm_ctt_reg_table[i++].addr = 0x4a004130;
	prcm_ctt_reg_table[i++].addr = 0x4a004134;
	prcm_ctt_reg_table[i++].addr = 0x4a004138;
	prcm_ctt_reg_table[i++].addr = 0x4a00413c;
	prcm_ctt_reg_table[i++].addr = 0x4a004140;
	prcm_ctt_reg_table[i++].addr = 0x4a004144;
	prcm_ctt_reg_table[i++].addr = 0x4a004154;
	prcm_ctt_reg_table[i++].addr = 0x4a004158;
	prcm_ctt_reg_table[i++].addr = 0x4a004160;
	prcm_ctt_reg_table[i++].addr = 0x4a00416c;
	prcm_ctt_reg_table[i++].addr = 0x4a004170;
	prcm_ctt_reg_table[i++].addr = 0x4a00419c;
	prcm_ctt_reg_table[i++].addr = 0x4a0041a0;
	prcm_ctt_reg_table[i++].addr = 0x4a0041ac;
	prcm_ctt_reg_table[i++].addr = 0x4a0041b8;
	prcm_ctt_reg_table[i++].addr = 0x4a0041bc;
	prcm_ctt_reg_table[i++].addr = 0x4a0041dc;
	prcm_ctt_reg_table[i++].addr = 0x4a0041e0;
	prcm_ctt_reg_table[i++].addr = 0x4a0041ec;
	prcm_ctt_reg_table[i++].addr = 0x4a0041f0;
	prcm_ctt_reg_table[i++].addr = 0x4a0041f4;
	prcm_ctt_reg_table[i++].addr = 0x4a004520;
	prcm_ctt_reg_table[i++].addr = 0x4a004528;
	prcm_ctt_reg_table[i++].addr = 0x4a004530;
	prcm_ctt_reg_table[i++].addr = 0x4a004538;
	prcm_ctt_reg_table[i++].addr = 0x4a004540;
	prcm_ctt_reg_table[i++].addr = 0x4a004548;
	prcm_ctt_reg_table[i++].addr = 0x4a004550;
	prcm_ctt_reg_table[i++].addr = 0x4a004558;
	prcm_ctt_reg_table[i++].addr = 0x4a004560;
	prcm_ctt_reg_table[i++].addr = 0x4a004568;
	prcm_ctt_reg_table[i++].addr = 0x4a004570;
	prcm_ctt_reg_table[i++].addr = 0x4a004578;
	prcm_ctt_reg_table[i++].addr = 0x4a004580;
	prcm_ctt_reg_table[i++].addr = 0x4a004588;
	prcm_ctt_reg_table[i++].addr = 0x4a008104;
	prcm_ctt_reg_table[i++].addr = 0x4a008140;
	prcm_ctt_reg_table[i++].addr = 0x4a00814c;
	prcm_ctt_reg_table[i++].addr = 0x4a008150;
	prcm_ctt_reg_table[i++].addr = 0x4a008154;
	prcm_ctt_reg_table[i++].addr = 0x4a008158;
	prcm_ctt_reg_table[i++].addr = 0x4a00815c;
	prcm_ctt_reg_table[i++].addr = 0x4a008164;
	prcm_ctt_reg_table[i++].addr = 0x4a008180;
	prcm_ctt_reg_table[i++].addr = 0x4a00818c;
	prcm_ctt_reg_table[i++].addr = 0x4a008190;
	prcm_ctt_reg_table[i++].addr = 0x4a0081c0;
	prcm_ctt_reg_table[i++].addr = 0x4a0081cc;
	prcm_ctt_reg_table[i++].addr = 0x4a0081d0;
	prcm_ctt_reg_table[i++].addr = 0x4a008200;
	prcm_ctt_reg_table[i++].addr = 0x4a00820c;
	prcm_ctt_reg_table[i++].addr = 0x4a008210;
	prcm_ctt_reg_table[i++].addr = 0x4a008628;
	prcm_ctt_reg_table[i++].addr = 0x4a008630;
	prcm_ctt_reg_table[i++].addr = 0x4a008638;
	prcm_ctt_reg_table[i++].addr = 0x4a008640;
	prcm_ctt_reg_table[i++].addr = 0x4a008648;
	prcm_ctt_reg_table[i++].addr = 0x4a008828;
	prcm_ctt_reg_table[i++].addr = 0x4a008920;
	prcm_ctt_reg_table[i++].addr = 0x4a008b20;
	prcm_ctt_reg_table[i++].addr = 0x4a008b30;
	prcm_ctt_reg_table[i++].addr = 0x4a008b38;
	prcm_ctt_reg_table[i++].addr = 0x4a008b40;
	prcm_ctt_reg_table[i++].addr = 0x4a008ca0;
	prcm_ctt_reg_table[i++].addr = 0x4a008ca8;
	prcm_ctt_reg_table[i++].addr = 0x4a008e20;
	prcm_ctt_reg_table[i++].addr = 0x4a008e28;
	prcm_ctt_reg_table[i++].addr = 0x4a008e40;
	prcm_ctt_reg_table[i++].addr = 0x4a008f28;
	prcm_ctt_reg_table[i++].addr = 0x4a009020;
	prcm_ctt_reg_table[i++].addr = 0x4a009028;
	prcm_ctt_reg_table[i++].addr = 0x4a009030;
	prcm_ctt_reg_table[i++].addr = 0x4a009120;
	prcm_ctt_reg_table[i++].addr = 0x4a009220;
	prcm_ctt_reg_table[i++].addr = 0x4a009328;
	prcm_ctt_reg_table[i++].addr = 0x4a009330;
	prcm_ctt_reg_table[i++].addr = 0x4a009338;
	prcm_ctt_reg_table[i++].addr = 0x4a009340;
	prcm_ctt_reg_table[i++].addr = 0x4a009348;
	prcm_ctt_reg_table[i++].addr = 0x4a009358;
	prcm_ctt_reg_table[i++].addr = 0x4a009368;
	prcm_ctt_reg_table[i++].addr = 0x4a009378;
	prcm_ctt_reg_table[i++].addr = 0x4a009388;
	prcm_ctt_reg_table[i++].addr = 0x4a0093e0;
	prcm_ctt_reg_table[i++].addr = 0x4a0093e8;
	prcm_ctt_reg_table[i++].addr = 0x4a0093f0;
	prcm_ctt_reg_table[i++].addr = 0x4a009428;
	prcm_ctt_reg_table[i++].addr = 0x4a009430;
	prcm_ctt_reg_table[i++].addr = 0x4a009438;
	prcm_ctt_reg_table[i++].addr = 0x4a009440;
	prcm_ctt_reg_table[i++].addr = 0x4a009448;
	prcm_ctt_reg_table[i++].addr = 0x4a009450;
	prcm_ctt_reg_table[i++].addr = 0x4a009458;
	prcm_ctt_reg_table[i++].addr = 0x4a009460;
	prcm_ctt_reg_table[i++].addr = 0x4a009468;
	prcm_ctt_reg_table[i++].addr = 0x4a009470;
	prcm_ctt_reg_table[i++].addr = 0x4a009478;
	prcm_ctt_reg_table[i++].addr = 0x4a009480;
	prcm_ctt_reg_table[i++].addr = 0x4a009488;
	prcm_ctt_reg_table[i++].addr = 0x4a0094a0;
	prcm_ctt_reg_table[i++].addr = 0x4a0094a8;
	prcm_ctt_reg_table[i++].addr = 0x4a0094b0;
	prcm_ctt_reg_table[i++].addr = 0x4a0094b8;
	prcm_ctt_reg_table[i++].addr = 0x4a0094c0;
	prcm_ctt_reg_table[i++].addr = 0x4a0094f0;
	prcm_ctt_reg_table[i++].addr = 0x4a0094f8;
	prcm_ctt_reg_table[i++].addr = 0x4a009500;
	prcm_ctt_reg_table[i++].addr = 0x4a009508;
	prcm_ctt_reg_table[i++].addr = 0x4a009510;
	prcm_ctt_reg_table[i++].addr = 0x4a009518;
	prcm_ctt_reg_table[i++].addr = 0x4a009520;
	prcm_ctt_reg_table[i++].addr = 0x4a009528;
	prcm_ctt_reg_table[i++].addr = 0x4a009538;
	prcm_ctt_reg_table[i++].addr = 0x4a009540;
	prcm_ctt_reg_table[i++].addr = 0x4a009548;
	prcm_ctt_reg_table[i++].addr = 0x4a009550;
	prcm_ctt_reg_table[i++].addr = 0x4a009558;
	prcm_ctt_reg_table[i++].addr = 0x4a009560;
	prcm_ctt_reg_table[i++].addr = 0x4a009568;
	prcm_ctt_reg_table[i++].addr = 0x4a009570;
	prcm_ctt_reg_table[i++].addr = 0x4a009578;
	prcm_ctt_reg_table[i++].addr = 0x4a009620;
	prcm_ctt_reg_table[i++].addr = 0x4ae06100;
	prcm_ctt_reg_table[i++].addr = 0x4ae06108;
	prcm_ctt_reg_table[i++].addr = 0x4ae0610c;
	prcm_ctt_reg_table[i++].addr = 0x4ae07830;
	prcm_ctt_reg_table[i++].addr = 0x4ae07838;
	prcm_ctt_reg_table[i++].addr = 0x4ae07840;
	prcm_ctt_reg_table[i++].addr = 0x4ae07878;
	prcm_ctt_reg_table[i++].addr = 0x4ae07890;
	prcm_ctt_reg_table[i].addr = 0;

	dprintf("%s: last index=%d, size=%d\n", __func__, i, i + 1);

	return 0;
}
