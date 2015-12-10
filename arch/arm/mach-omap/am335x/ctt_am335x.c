/*
 *
 * @Component			OMAPCONF
 * @Filename			ctt_am335x.c
 * @Description			Display PRCM registers in a format that can be
 *				imported into the clock tree tool (CTT)
 * @Author			Gilberto Rodriguez <gilrod@ti.com>
 * @Date			2014
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
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


#include <cpuinfo.h>
#include <ctt_am335x.h>
#include <help.h>
#include <lib.h>
#include <mem.h>
#include <string.h>

#ifdef CTT_AM335X_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

#define PRCM_CTT_REG_TABLE_SIZE        623

#define DEVICE_NAME "AM335x1.0"

static reg_table prcm_ctt_reg_table[PRCM_CTT_REG_TABLE_SIZE];

static int ctt_am335x_regtable_init(void);

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		ctt_am335x_dump
 * @BRIEF		dump PRCM registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		dump PRCM registers
 *//*------------------------------------------------------------------------ */
int ctt_am335x_dump(void)
{
	unsigned int i = 0;
	unsigned int ret, val = 0;
	int err = 0;

	printf("The Clock Tree Tool can import register settings from a *.rd1 "
		"file.\n");
	printf("The format of the *.rd1 file is:\n\n");
	printf("DeviceName AM335x1.0\n");
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

	if (!cpu_is_am335x())
		return OMAPCONF_ERR_CPU;
	printf("DeviceName %s\n", DEVICE_NAME);

	ctt_am335x_regtable_init();

	while (prcm_ctt_reg_table[i].addr != 0) {
		/* display register addr & content (hex) */
		ret = mem_read(prcm_ctt_reg_table[i].addr, &val);
		if (ret == 0) {
			printf("0x%08X 0x%08X\n",
				prcm_ctt_reg_table[i].addr, val);
		} else {
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
 * @FUNCTION		ctt_am335x_rd1_export
 * @BRIEF		export PRCM registers in CTT RD1 format
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		file: output file name
 * @DESCRIPTION		export PRCM registers in CTT RD1 format
 *//*------------------------------------------------------------------------ */
int ctt_am335x_rd1_export(char *file)
{
	unsigned int i = 0;
	unsigned int ret, val = 0;
	int err = 0;
	FILE *fd = NULL;
	char fullfilename[128];

	CHECK_NULL_ARG(file, OMAPCONF_ERR_ARG);

	strncpy(fullfilename, file, 128);
	fd = workdir_fopen(fullfilename, "w");
	if (fd == NULL) {
		printf("error: could not create %s file!\n", fullfilename);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	if (!cpu_is_am335x())
		return OMAPCONF_ERR_CPU;
	fprintf(fd, "DeviceName %s\n", DEVICE_NAME);

	ctt_am335x_regtable_init();

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
 * @FUNCTION		ctt_am335x_main
 * @BRIEF		CTT main menu
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		CTT main menu
 *//*------------------------------------------------------------------------ */
int ctt_am335x_main(int argc, char *argv[])
{
	int ret;

	if (argc == 1) {
		ctt_am335x_regtable_init();

		if (strcmp(argv[0], "dump") == 0) {
			ret = ctt_am335x_dump();
		} else if (strcmp(argv[0], "rd1") == 0) {
			ret = ctt_am335x_rd1_export("CTT-AM335x1.rd1");
		} else {
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
 * @FUNCTION		ctt_am335x_regtable_init
 * @BRIEF		initialize regtable
 * @RETURNS		0
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		initialize regtable
 *//*------------------------------------------------------------------------ */
static int ctt_am335x_regtable_init(void)
{
	int i = 0;

	/* Init PRCM register table */
	/* Data from: CTT-AM335x1.0_v2.0.0.0 */
	prcm_ctt_reg_table[i++].addr = 0x44e00000;
	prcm_ctt_reg_table[i++].addr = 0x44e00004;
	prcm_ctt_reg_table[i++].addr = 0x44e00008;
	prcm_ctt_reg_table[i++].addr = 0x44e0000c;
	prcm_ctt_reg_table[i++].addr = 0x44e00010;
	prcm_ctt_reg_table[i++].addr = 0x44e00014;
	prcm_ctt_reg_table[i++].addr = 0x44e00018;
	prcm_ctt_reg_table[i++].addr = 0x44e0001c;
	prcm_ctt_reg_table[i++].addr = 0x44e00020;
	prcm_ctt_reg_table[i++].addr = 0x44e00024;
	prcm_ctt_reg_table[i++].addr = 0x44e00028;
	prcm_ctt_reg_table[i++].addr = 0x44e0002c;
	prcm_ctt_reg_table[i++].addr = 0x44e00030;
	prcm_ctt_reg_table[i++].addr = 0x44e00034;
	prcm_ctt_reg_table[i++].addr = 0x44e00038;
	prcm_ctt_reg_table[i++].addr = 0x44e0003c;
	prcm_ctt_reg_table[i++].addr = 0x44e00040;
	prcm_ctt_reg_table[i++].addr = 0x44e00044;
	prcm_ctt_reg_table[i++].addr = 0x44e00048;
	prcm_ctt_reg_table[i++].addr = 0x44e0004c;
	prcm_ctt_reg_table[i++].addr = 0x44e00050;
	prcm_ctt_reg_table[i++].addr = 0x44e00054;
	prcm_ctt_reg_table[i++].addr = 0x44e00058;
	prcm_ctt_reg_table[i++].addr = 0x44e00060;
	prcm_ctt_reg_table[i++].addr = 0x44e00064;
	prcm_ctt_reg_table[i++].addr = 0x44e00068;
	prcm_ctt_reg_table[i++].addr = 0x44e0006c;
	prcm_ctt_reg_table[i++].addr = 0x44e00070;
	prcm_ctt_reg_table[i++].addr = 0x44e00074;
	prcm_ctt_reg_table[i++].addr = 0x44e00078;
	prcm_ctt_reg_table[i++].addr = 0x44e0007c;
	prcm_ctt_reg_table[i++].addr = 0x44e00080;
	prcm_ctt_reg_table[i++].addr = 0x44e00084;
	prcm_ctt_reg_table[i++].addr = 0x44e00088;
	prcm_ctt_reg_table[i++].addr = 0x44e0008c;
	prcm_ctt_reg_table[i++].addr = 0x44e00090;
	prcm_ctt_reg_table[i++].addr = 0x44e00094;
	prcm_ctt_reg_table[i++].addr = 0x44e00098;
	prcm_ctt_reg_table[i++].addr = 0x44e0009c;
	prcm_ctt_reg_table[i++].addr = 0x44e000a0;
	prcm_ctt_reg_table[i++].addr = 0x44e000a4;
	prcm_ctt_reg_table[i++].addr = 0x44e000a8;
	prcm_ctt_reg_table[i++].addr = 0x44e000ac;
	prcm_ctt_reg_table[i++].addr = 0x44e000b0;
	prcm_ctt_reg_table[i++].addr = 0x44e000b4;
	prcm_ctt_reg_table[i++].addr = 0x44e000b8;
	prcm_ctt_reg_table[i++].addr = 0x44e000bc;
	prcm_ctt_reg_table[i++].addr = 0x44e000c0;
	prcm_ctt_reg_table[i++].addr = 0x44e000c4;
	prcm_ctt_reg_table[i++].addr = 0x44e000c8;
	prcm_ctt_reg_table[i++].addr = 0x44e000cc;
	prcm_ctt_reg_table[i++].addr = 0x44e000d0;
	prcm_ctt_reg_table[i++].addr = 0x44e000d4;
	prcm_ctt_reg_table[i++].addr = 0x44e000d8;
	prcm_ctt_reg_table[i++].addr = 0x44e000dc;
	prcm_ctt_reg_table[i++].addr = 0x44e000e0;
	prcm_ctt_reg_table[i++].addr = 0x44e000e4;
	prcm_ctt_reg_table[i++].addr = 0x44e000e8;
	prcm_ctt_reg_table[i++].addr = 0x44e000ec;
	prcm_ctt_reg_table[i++].addr = 0x44e000f0;
	prcm_ctt_reg_table[i++].addr = 0x44e000f4;
	prcm_ctt_reg_table[i++].addr = 0x44e000f8;
	prcm_ctt_reg_table[i++].addr = 0x44e000fc;
	prcm_ctt_reg_table[i++].addr = 0x44e00100;
	prcm_ctt_reg_table[i++].addr = 0x44e00104;
	prcm_ctt_reg_table[i++].addr = 0x44e0010c;
	prcm_ctt_reg_table[i++].addr = 0x44e00110;
	prcm_ctt_reg_table[i++].addr = 0x44e0011c;
	prcm_ctt_reg_table[i++].addr = 0x44e00120;
	prcm_ctt_reg_table[i++].addr = 0x44e00124;
	prcm_ctt_reg_table[i++].addr = 0x44e00128;
	prcm_ctt_reg_table[i++].addr = 0x44e0012c;
	prcm_ctt_reg_table[i++].addr = 0x44e00130;
	prcm_ctt_reg_table[i++].addr = 0x44e00134;
	prcm_ctt_reg_table[i++].addr = 0x44e00138;
	prcm_ctt_reg_table[i++].addr = 0x44e0013c;
	prcm_ctt_reg_table[i++].addr = 0x44e00140;
	prcm_ctt_reg_table[i++].addr = 0x44e00144;
	prcm_ctt_reg_table[i++].addr = 0x44e00148;
	prcm_ctt_reg_table[i++].addr = 0x44e0014c;
	prcm_ctt_reg_table[i++].addr = 0x44e00150;
	prcm_ctt_reg_table[i++].addr = 0x44e00400;
	prcm_ctt_reg_table[i++].addr = 0x44e00404;
	prcm_ctt_reg_table[i++].addr = 0x44e00408;
	prcm_ctt_reg_table[i++].addr = 0x44e0040c;
	prcm_ctt_reg_table[i++].addr = 0x44e00410;
	prcm_ctt_reg_table[i++].addr = 0x44e00414;
	prcm_ctt_reg_table[i++].addr = 0x44e00418;
	prcm_ctt_reg_table[i++].addr = 0x44e0041c;
	prcm_ctt_reg_table[i++].addr = 0x44e00420;
	prcm_ctt_reg_table[i++].addr = 0x44e00424;
	prcm_ctt_reg_table[i++].addr = 0x44e00428;
	prcm_ctt_reg_table[i++].addr = 0x44e0042c;
	prcm_ctt_reg_table[i++].addr = 0x44e00430;
	prcm_ctt_reg_table[i++].addr = 0x44e00434;
	prcm_ctt_reg_table[i++].addr = 0x44e00438;
	prcm_ctt_reg_table[i++].addr = 0x44e0043c;
	prcm_ctt_reg_table[i++].addr = 0x44e00440;
	prcm_ctt_reg_table[i++].addr = 0x44e00444;
	prcm_ctt_reg_table[i++].addr = 0x44e00448;
	prcm_ctt_reg_table[i++].addr = 0x44e0044c;
	prcm_ctt_reg_table[i++].addr = 0x44e00450;
	prcm_ctt_reg_table[i++].addr = 0x44e00454;
	prcm_ctt_reg_table[i++].addr = 0x44e00458;
	prcm_ctt_reg_table[i++].addr = 0x44e0045c;
	prcm_ctt_reg_table[i++].addr = 0x44e00460;
	prcm_ctt_reg_table[i++].addr = 0x44e00464;
	prcm_ctt_reg_table[i++].addr = 0x44e00468;
	prcm_ctt_reg_table[i++].addr = 0x44e0046c;
	prcm_ctt_reg_table[i++].addr = 0x44e00470;
	prcm_ctt_reg_table[i++].addr = 0x44e00474;
	prcm_ctt_reg_table[i++].addr = 0x44e00478;
	prcm_ctt_reg_table[i++].addr = 0x44e0047c;
	prcm_ctt_reg_table[i++].addr = 0x44e00480;
	prcm_ctt_reg_table[i++].addr = 0x44e00484;
	prcm_ctt_reg_table[i++].addr = 0x44e00488;
	prcm_ctt_reg_table[i++].addr = 0x44e0048c;
	prcm_ctt_reg_table[i++].addr = 0x44e00490;
	prcm_ctt_reg_table[i++].addr = 0x44e00494;
	prcm_ctt_reg_table[i++].addr = 0x44e00498;
	prcm_ctt_reg_table[i++].addr = 0x44e0049c;
	prcm_ctt_reg_table[i++].addr = 0x44e004a0;
	prcm_ctt_reg_table[i++].addr = 0x44e004a4;
	prcm_ctt_reg_table[i++].addr = 0x44e004a8;
	prcm_ctt_reg_table[i++].addr = 0x44e004ac;
	prcm_ctt_reg_table[i++].addr = 0x44e004b0;
	prcm_ctt_reg_table[i++].addr = 0x44e004b4;
	prcm_ctt_reg_table[i++].addr = 0x44e004b8;
	prcm_ctt_reg_table[i++].addr = 0x44e004bc;
	prcm_ctt_reg_table[i++].addr = 0x44e004c0;
	prcm_ctt_reg_table[i++].addr = 0x44e004c4;
	prcm_ctt_reg_table[i++].addr = 0x44e004c8;
	prcm_ctt_reg_table[i++].addr = 0x44e004cc;
	prcm_ctt_reg_table[i++].addr = 0x44e004d0;
	prcm_ctt_reg_table[i++].addr = 0x44e004d4;
	prcm_ctt_reg_table[i++].addr = 0x44e00504;
	prcm_ctt_reg_table[i++].addr = 0x44e00508;
	prcm_ctt_reg_table[i++].addr = 0x44e0050c;
	prcm_ctt_reg_table[i++].addr = 0x44e00510;
	prcm_ctt_reg_table[i++].addr = 0x44e00514;
	prcm_ctt_reg_table[i++].addr = 0x44e00518;
	prcm_ctt_reg_table[i++].addr = 0x44e0051c;
	prcm_ctt_reg_table[i++].addr = 0x44e00520;
	prcm_ctt_reg_table[i++].addr = 0x44e00528;
	prcm_ctt_reg_table[i++].addr = 0x44e0052c;
	prcm_ctt_reg_table[i++].addr = 0x44e00530;
	prcm_ctt_reg_table[i++].addr = 0x44e00534;
	prcm_ctt_reg_table[i++].addr = 0x44e00538;
	prcm_ctt_reg_table[i++].addr = 0x44e0053c;
	prcm_ctt_reg_table[i++].addr = 0x44e00600;
	prcm_ctt_reg_table[i++].addr = 0x44e00604;
	prcm_ctt_reg_table[i++].addr = 0x44e00700;
	prcm_ctt_reg_table[i++].addr = 0x44e00800;
	prcm_ctt_reg_table[i++].addr = 0x44e00804;
	prcm_ctt_reg_table[i++].addr = 0x44e00900;
	prcm_ctt_reg_table[i++].addr = 0x44e00904;
	prcm_ctt_reg_table[i++].addr = 0x44e00908;
	prcm_ctt_reg_table[i++].addr = 0x44e0090c;
	prcm_ctt_reg_table[i++].addr = 0x44e00910;
	prcm_ctt_reg_table[i++].addr = 0x44e00914;
	prcm_ctt_reg_table[i++].addr = 0x44e00a00;
	prcm_ctt_reg_table[i++].addr = 0x44e00a20;
	prcm_ctt_reg_table[i++].addr = 0x44e00b00;
	prcm_ctt_reg_table[i++].addr = 0x44e00b04;
	prcm_ctt_reg_table[i++].addr = 0x44e00b08;
	prcm_ctt_reg_table[i++].addr = 0x44e00b0c;
	prcm_ctt_reg_table[i++].addr = 0x44e00b10;
	prcm_ctt_reg_table[i++].addr = 0x44e00c00;
	prcm_ctt_reg_table[i++].addr = 0x44e00c04;
	prcm_ctt_reg_table[i++].addr = 0x44e00c08;
	prcm_ctt_reg_table[i++].addr = 0x44e00c0c;
	prcm_ctt_reg_table[i++].addr = 0x44e00d00;
	prcm_ctt_reg_table[i++].addr = 0x44e00d04;
	prcm_ctt_reg_table[i++].addr = 0x44e00d08;
	prcm_ctt_reg_table[i++].addr = 0x44e00d0c;
	prcm_ctt_reg_table[i++].addr = 0x44e00e00;
	prcm_ctt_reg_table[i++].addr = 0x44e00e04;
	prcm_ctt_reg_table[i++].addr = 0x44e00e08;
	prcm_ctt_reg_table[i++].addr = 0x44e00f00;
	prcm_ctt_reg_table[i++].addr = 0x44e00f04;
	prcm_ctt_reg_table[i++].addr = 0x44e00f08;
	prcm_ctt_reg_table[i++].addr = 0x44e00f0c;
	prcm_ctt_reg_table[i++].addr = 0x44e00f10;
	prcm_ctt_reg_table[i++].addr = 0x44e00f14;
	prcm_ctt_reg_table[i++].addr = 0x44e00f18;
	prcm_ctt_reg_table[i++].addr = 0x44e00f1c;
	prcm_ctt_reg_table[i++].addr = 0x44e01000;
	prcm_ctt_reg_table[i++].addr = 0x44e01004;
	prcm_ctt_reg_table[i++].addr = 0x44e01100;
	prcm_ctt_reg_table[i++].addr = 0x44e01104;
	prcm_ctt_reg_table[i++].addr = 0x44e01110;
	prcm_ctt_reg_table[i++].addr = 0x44e01114;
	prcm_ctt_reg_table[i++].addr = 0x44e01200;
	prcm_ctt_reg_table[i++].addr = 0x44e01204;
	prcm_ctt_reg_table[i++].addr = 0x44e10040;
	prcm_ctt_reg_table[i].addr = 0;

	dprintf("%s: last index=%d, size=%d", __func__, i, i + 1);

	return 0;
}
