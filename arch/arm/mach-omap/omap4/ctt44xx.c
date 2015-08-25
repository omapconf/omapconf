/*
 *
 * @Component			OMAPCONF
 * @Filename			ctt44xx.c
 * @Description			Display PRCM registers in a format that can be
 *				imported into the clock tree tool (CTT)
 * @Author			Jon Hunter (jon-hunter@ti.com)
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


#include <ctt44xx.h>
#include <lib.h>
#include <lib44xx.h>
#include <help.h>
#include <lib.h>
#include <mem.h>
#include <cpuinfo.h>
#include <string.h>


/* #define CTT44XX_DEBUG */
#ifdef CTT44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


#define PRCM_CTT_REG_TABLE_SIZE        238


static char ctt_filename[] = "CTT-OMAP44XX-REG_DUMP.rd1";
static reg_table prcm_ctt_reg_table[PRCM_CTT_REG_TABLE_SIZE + 1];


static int ctt44xx_regtable_init(void);


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		ctt44xx_dump
 * @BRIEF		dump PRCM registers
 * @RETURNS		0
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		dump PRCM registers
 *//*------------------------------------------------------------------------ */
int ctt44xx_dump(void)
{
	unsigned int i = 0;
	unsigned int ret, val = 0;
	int err = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_ARG);

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

	if (cpu_is_omap4430())
		printf("DeviceName OMAP4430_ES2.x\n");
	else if (cpu_is_omap4460())
		printf("DeviceName OMAP4460_ES1.x\n");
	else if (cpu_is_omap4470())
		printf("DeviceName OMAP4470_ES1.0\n");
	else
		return OMAPCONF_ERR_CPU;

	ctt44xx_regtable_init();

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
		"---|\n");

	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		ctt44xx_rd1_export
 * @BRIEF		export PRCM registers in CTT RD1 format
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		filename: output file name
 * @DESCRIPTION		export PRCM registers in CTT RD1 format
 *//*------------------------------------------------------------------------ */
int ctt44xx_rd1_export(char *filename)
{
	unsigned int i = 0;
	unsigned int ret, val = 0;
	int err = 0;
	FILE *fd = NULL;

	CHECK_CPU(44xx, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(filename, OMAPCONF_ERR_ARG);

	fd = fopen(filename, "w");
	if (fd == NULL) {
		printf("error: could not create %s file!\n", filename);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	if (cpu_is_omap4430()) {
		fprintf(fd, "DeviceName OMAP4430_ES2.x\n");
	} else if (cpu_is_omap4460()) {
		fprintf(fd, "DeviceName OMAP4460_ES1.x\n");
	} else if (cpu_is_omap4470()) {
		fprintf(fd, "DeviceName OMAP4470_ES1.0\n");
	} else {
		err = OMAPCONF_ERR_CPU;
		goto ctt44xx_rd1_export_end;
	}

	ctt44xx_regtable_init();

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

	printf("Output written to file '%s'.\n", filename);
	err = 0;

ctt44xx_rd1_export_end:
	if (fd != NULL)
		fclose(fd);
	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		ctt44xx_main
 * @BRIEF		main entry point for ctt
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		main entry point for ctt
 *//*------------------------------------------------------------------------ */
int ctt44xx_main(int argc, char *argv[])
{
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_ARG);

	if (argc == 2) {
		if (strcmp(argv[1], "dump") == 0)
			ret = ctt44xx_dump();
		else if (strcmp(argv[1], "rd1") == 0)
			ret = ctt44xx_rd1_export(ctt_filename);
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
 * @FUNCTION		ctt44xx_regtable_init
 * @BRIEF		initialize regtable
 * @RETURNS		0
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		initialize regtable
 *//*------------------------------------------------------------------------ */
static int ctt44xx_regtable_init(void)
{
	int i = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_ARG);

	/* Init PRCM registers table */
	prcm_ctt_reg_table[i++].addr = 0x4a004100;
	prcm_ctt_reg_table[i++].addr = 0x4a004108;
	prcm_ctt_reg_table[i++].addr = 0x4a004110;
	prcm_ctt_reg_table[i++].addr = 0x4a004120;
	prcm_ctt_reg_table[i++].addr = 0x4a004124;
	prcm_ctt_reg_table[i++].addr = 0x4a004128;
	prcm_ctt_reg_table[i++].addr = 0x4a00412c;
	prcm_ctt_reg_table[i++].addr = 0x4a004130;
	prcm_ctt_reg_table[i++].addr = 0x4a004134;
	prcm_ctt_reg_table[i++].addr = 0x4a004138;
	prcm_ctt_reg_table[i++].addr = 0x4a00413c;
	prcm_ctt_reg_table[i++].addr = 0x4a004140;
	prcm_ctt_reg_table[i++].addr = 0x4a004144;
	prcm_ctt_reg_table[i++].addr = 0x4a004148;
	prcm_ctt_reg_table[i++].addr = 0x4a00414c;
	prcm_ctt_reg_table[i++].addr = 0x4a004150;
	prcm_ctt_reg_table[i++].addr = 0x4a004160;
	prcm_ctt_reg_table[i++].addr = 0x4a004164;
	prcm_ctt_reg_table[i++].addr = 0x4a004168;
	prcm_ctt_reg_table[i++].addr = 0x4a00416c;
	prcm_ctt_reg_table[i++].addr = 0x4a004170;
	prcm_ctt_reg_table[i++].addr = 0x4a004188;
	prcm_ctt_reg_table[i++].addr = 0x4a00418c;
	prcm_ctt_reg_table[i++].addr = 0x4a00419c;
	prcm_ctt_reg_table[i++].addr = 0x4a0041a0;
	prcm_ctt_reg_table[i++].addr = 0x4a0041a4;
	prcm_ctt_reg_table[i++].addr = 0x4a0041a8;
	prcm_ctt_reg_table[i++].addr = 0x4a0041ac;
	prcm_ctt_reg_table[i++].addr = 0x4a0041b8;
	prcm_ctt_reg_table[i++].addr = 0x4a0041bc;
	prcm_ctt_reg_table[i++].addr = 0x4a0041c8;
	prcm_ctt_reg_table[i++].addr = 0x4a0041cc;
	prcm_ctt_reg_table[i++].addr = 0x4a0041dc;
	prcm_ctt_reg_table[i++].addr = 0x4a0041e0;
	prcm_ctt_reg_table[i++].addr = 0x4a0041e4;
	prcm_ctt_reg_table[i++].addr = 0x4a0041e8;
	prcm_ctt_reg_table[i++].addr = 0x4a0041ec;
	prcm_ctt_reg_table[i++].addr = 0x4a0041f0;
	prcm_ctt_reg_table[i++].addr = 0x4a0041f4;
	prcm_ctt_reg_table[i++].addr = 0x4a004208;
	prcm_ctt_reg_table[i++].addr = 0x4a00420c;
	prcm_ctt_reg_table[i++].addr = 0x4a004260;
	prcm_ctt_reg_table[i++].addr = 0x4a004264;
	prcm_ctt_reg_table[i++].addr = 0x4a004270;
	prcm_ctt_reg_table[i++].addr = 0x4a004280;
	prcm_ctt_reg_table[i++].addr = 0x4a004400;
	prcm_ctt_reg_table[i++].addr = 0x4a004404;
	prcm_ctt_reg_table[i++].addr = 0x4a004408;
	prcm_ctt_reg_table[i++].addr = 0x4a004420;
	prcm_ctt_reg_table[i++].addr = 0x4a004500;
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
	prcm_ctt_reg_table[i++].addr = 0x4a008100;
	prcm_ctt_reg_table[i++].addr = 0x4a008104;
	prcm_ctt_reg_table[i++].addr = 0x4a008108;
	prcm_ctt_reg_table[i++].addr = 0x4a008110;
	prcm_ctt_reg_table[i++].addr = 0x4a008114;
	prcm_ctt_reg_table[i++].addr = 0x4a008118;
	prcm_ctt_reg_table[i++].addr = 0x4a00811c;
	prcm_ctt_reg_table[i++].addr = 0x4a008124;
	prcm_ctt_reg_table[i++].addr = 0x4a008128;
	prcm_ctt_reg_table[i++].addr = 0x4a00812c;
	prcm_ctt_reg_table[i++].addr = 0x4a008130;
	prcm_ctt_reg_table[i++].addr = 0x4a008138;
	prcm_ctt_reg_table[i++].addr = 0x4a008140;
	prcm_ctt_reg_table[i++].addr = 0x4a008144;
	prcm_ctt_reg_table[i++].addr = 0x4a008148;
	prcm_ctt_reg_table[i++].addr = 0x4a00814c;
	prcm_ctt_reg_table[i++].addr = 0x4a008150;
	prcm_ctt_reg_table[i++].addr = 0x4a008154;
	prcm_ctt_reg_table[i++].addr = 0x4a008158;
	prcm_ctt_reg_table[i++].addr = 0x4a00815c;
	prcm_ctt_reg_table[i++].addr = 0x4a008160;
	prcm_ctt_reg_table[i++].addr = 0x4a008164;
	prcm_ctt_reg_table[i++].addr = 0x4a008180;
	prcm_ctt_reg_table[i++].addr = 0x4a008184;
	prcm_ctt_reg_table[i++].addr = 0x4a008188;
	prcm_ctt_reg_table[i++].addr = 0x4a00818c;
	prcm_ctt_reg_table[i++].addr = 0x4a008190;
	prcm_ctt_reg_table[i++].addr = 0x4a0081b4;
	prcm_ctt_reg_table[i++].addr = 0x4a008600;
	prcm_ctt_reg_table[i++].addr = 0x4a008628;
	prcm_ctt_reg_table[i++].addr = 0x4a008630;
	prcm_ctt_reg_table[i++].addr = 0x4a008638;
	prcm_ctt_reg_table[i++].addr = 0x4a008640;
	prcm_ctt_reg_table[i++].addr = 0x4a008700;
	prcm_ctt_reg_table[i++].addr = 0x4a008708;
	prcm_ctt_reg_table[i++].addr = 0x4a008720;
	prcm_ctt_reg_table[i++].addr = 0x4a008800;
	prcm_ctt_reg_table[i++].addr = 0x4a008808;
	prcm_ctt_reg_table[i++].addr = 0x4a008820;
	prcm_ctt_reg_table[i++].addr = 0x4a008828;
	prcm_ctt_reg_table[i++].addr = 0x4a008830;
	prcm_ctt_reg_table[i++].addr = 0x4a008900;
	prcm_ctt_reg_table[i++].addr = 0x4a008904;
	prcm_ctt_reg_table[i++].addr = 0x4a008908;
	prcm_ctt_reg_table[i++].addr = 0x4a008920;
	prcm_ctt_reg_table[i++].addr = 0x4a008a00;
	prcm_ctt_reg_table[i++].addr = 0x4a008a04;
	prcm_ctt_reg_table[i++].addr = 0x4a008a08;
	prcm_ctt_reg_table[i++].addr = 0x4a008a20;
	prcm_ctt_reg_table[i++].addr = 0x4a008b00;
	prcm_ctt_reg_table[i++].addr = 0x4a008b20;
	prcm_ctt_reg_table[i++].addr = 0x4a008b28;
	prcm_ctt_reg_table[i++].addr = 0x4a008b30;
	prcm_ctt_reg_table[i++].addr = 0x4a008b38;
	prcm_ctt_reg_table[i++].addr = 0x4a008b40;
	prcm_ctt_reg_table[i++].addr = 0x4a008c00;
	prcm_ctt_reg_table[i++].addr = 0x4a008c04;
	prcm_ctt_reg_table[i++].addr = 0x4a008c08;
	prcm_ctt_reg_table[i++].addr = 0x4a008c20;
	prcm_ctt_reg_table[i++].addr = 0x4a008c30;
	prcm_ctt_reg_table[i++].addr = 0x4a008d00;
	prcm_ctt_reg_table[i++].addr = 0x4a008d08;
	prcm_ctt_reg_table[i++].addr = 0x4a008d20;
	prcm_ctt_reg_table[i++].addr = 0x4a008d28;
	prcm_ctt_reg_table[i++].addr = 0x4a008d30;
	prcm_ctt_reg_table[i++].addr = 0x4a008d38;
	prcm_ctt_reg_table[i++].addr = 0x4a008e00;
	prcm_ctt_reg_table[i++].addr = 0x4a008e20;
	prcm_ctt_reg_table[i++].addr = 0x4a008e28;
	prcm_ctt_reg_table[i++].addr = 0x4a008e40;
	prcm_ctt_reg_table[i++].addr = 0x4a008f00;
	prcm_ctt_reg_table[i++].addr = 0x4a008f04;
	prcm_ctt_reg_table[i++].addr = 0x4a008f08;
	prcm_ctt_reg_table[i++].addr = 0x4a008f20;
	prcm_ctt_reg_table[i++].addr = 0x4a008f28;
	prcm_ctt_reg_table[i++].addr = 0x4a009000;
	prcm_ctt_reg_table[i++].addr = 0x4a009004;
	prcm_ctt_reg_table[i++].addr = 0x4a009008;
	prcm_ctt_reg_table[i++].addr = 0x4a009020;
	prcm_ctt_reg_table[i++].addr = 0x4a009028;
	prcm_ctt_reg_table[i++].addr = 0x4a009100;
	prcm_ctt_reg_table[i++].addr = 0x4a009104;
	prcm_ctt_reg_table[i++].addr = 0x4a009108;
	prcm_ctt_reg_table[i++].addr = 0x4a009120;
	prcm_ctt_reg_table[i++].addr = 0x4a009200;
	prcm_ctt_reg_table[i++].addr = 0x4a009204;
	prcm_ctt_reg_table[i++].addr = 0x4a009208;
	prcm_ctt_reg_table[i++].addr = 0x4a009220;
	prcm_ctt_reg_table[i++].addr = 0x4a009300;
	prcm_ctt_reg_table[i++].addr = 0x4a009304;
	prcm_ctt_reg_table[i++].addr = 0x4a009308;
	prcm_ctt_reg_table[i++].addr = 0x4a009328;
	prcm_ctt_reg_table[i++].addr = 0x4a009330;
	prcm_ctt_reg_table[i++].addr = 0x4a009338;
	prcm_ctt_reg_table[i++].addr = 0x4a009358;
	prcm_ctt_reg_table[i++].addr = 0x4a009360;
	prcm_ctt_reg_table[i++].addr = 0x4a009368;
	prcm_ctt_reg_table[i++].addr = 0x4a0093d0;
	prcm_ctt_reg_table[i++].addr = 0x4a0093e0;
	prcm_ctt_reg_table[i++].addr = 0x4a009400;
	prcm_ctt_reg_table[i++].addr = 0x4a009408;
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
	prcm_ctt_reg_table[i++].addr = 0x4a0094e0;
	prcm_ctt_reg_table[i++].addr = 0x4a0094f0;
	prcm_ctt_reg_table[i++].addr = 0x4a0094f8;
	prcm_ctt_reg_table[i++].addr = 0x4a009500;
	prcm_ctt_reg_table[i++].addr = 0x4a009508;
	prcm_ctt_reg_table[i++].addr = 0x4a009520;
	prcm_ctt_reg_table[i++].addr = 0x4a009528;
	prcm_ctt_reg_table[i++].addr = 0x4a009538;
	prcm_ctt_reg_table[i++].addr = 0x4a009540;
	prcm_ctt_reg_table[i++].addr = 0x4a009548;
	prcm_ctt_reg_table[i++].addr = 0x4a009550;
	prcm_ctt_reg_table[i++].addr = 0x4a009558;
	prcm_ctt_reg_table[i++].addr = 0x4a009560;
	prcm_ctt_reg_table[i++].addr = 0x4a306100;
	prcm_ctt_reg_table[i++].addr = 0x4a306108;
	prcm_ctt_reg_table[i++].addr = 0x4a30610c;
	prcm_ctt_reg_table[i++].addr = 0x4a306110;
	prcm_ctt_reg_table[i++].addr = 0x4a307800;
	prcm_ctt_reg_table[i++].addr = 0x4a307820;
	prcm_ctt_reg_table[i++].addr = 0x4a307830;
	prcm_ctt_reg_table[i++].addr = 0x4a307838;
	prcm_ctt_reg_table[i++].addr = 0x4a307840;
	prcm_ctt_reg_table[i++].addr = 0x4a307850;
	prcm_ctt_reg_table[i++].addr = 0x4a307860;
	prcm_ctt_reg_table[i++].addr = 0x4a307878;
	prcm_ctt_reg_table[i++].addr = 0x4a307888;
	prcm_ctt_reg_table[i++].addr = 0x4a307a00;
	prcm_ctt_reg_table[i++].addr = 0x4a307a08;
	prcm_ctt_reg_table[i++].addr = 0x4a307a20;
	prcm_ctt_reg_table[i++].addr = 0x4a30a000;
	prcm_ctt_reg_table[i++].addr = 0x4a30a100;
	prcm_ctt_reg_table[i++].addr = 0x4a30a104;
	prcm_ctt_reg_table[i++].addr = 0x4a30a110;
	prcm_ctt_reg_table[i++].addr = 0x4a30a11c;
	prcm_ctt_reg_table[i++].addr = 0x4a30a204;
	prcm_ctt_reg_table[i++].addr = 0x4a30a208;
	prcm_ctt_reg_table[i++].addr = 0x4a30a210;
	prcm_ctt_reg_table[i++].addr = 0x4a30a214;
	prcm_ctt_reg_table[i++].addr = 0x4a30a218;
	prcm_ctt_reg_table[i++].addr = 0x4a30a21c;
	prcm_ctt_reg_table[i++].addr = 0x4a30a220;
	prcm_ctt_reg_table[i++].addr = 0x4a30a224;
	prcm_ctt_reg_table[i++].addr = 0x4a30a234;
	prcm_ctt_reg_table[i++].addr = 0x4a30a310;
	prcm_ctt_reg_table[i++].addr = 0x4a30a314;
	prcm_ctt_reg_table[i++].addr = 0x4a30a318;
	prcm_ctt_reg_table[i++].addr = 0x4a30a31c;
	prcm_ctt_reg_table[i++].addr = 0x4a30a320;
	prcm_ctt_reg_table[i++].addr = 0x4a30a324;
	prcm_ctt_reg_table[i++].addr = 0x4a30a400;
	prcm_ctt_reg_table[i++].addr = 0x4a30a41c;
	prcm_ctt_reg_table[i++].addr = 0x4a30a420;
	prcm_ctt_reg_table[i++].addr = 0x4a30a510;
	prcm_ctt_reg_table[i++].addr = 0x4a30a514;
	prcm_ctt_reg_table[i++].addr = 0x4a30a51c;
	prcm_ctt_reg_table[i].addr = 0;

	dprintf("prcm_ctt_reg_table last index=%d, size=%d\n", i, i + 1);

	return 0;
}
