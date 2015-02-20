/*
 *
 * @Component			OMAPCONF
 * @Filename			ctt_am437x.c
 * @Description			Display PRCM registers in a format that can be
 *				imported into the clock tree tool (CTT)
 * @Author			Dave Gerlach <d-gerlach@ti.com>
 * @Date			2015
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
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
#include <ctt_am437x.h>
#include <help.h>
#include <lib.h>
#include <mem.h>
#include <string.h>

#ifdef CTT_AM437X_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

#define PRCM_CTT_REG_TABLE_SIZE        623

#define DEVICE_NAME "AM437x_PG1.0"

static reg_table prcm_ctt_reg_table[PRCM_CTT_REG_TABLE_SIZE];

static int ctt_am437x_regtable_init(void);

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		ctt_am437x_dump
 * @BRIEF		dump PRCM registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		dump PRCM registers
 *//*------------------------------------------------------------------------ */
int ctt_am437x_dump(void)
{
	unsigned int i = 0;
	unsigned int ret, val = 0;
	int err = 0;

	printf("The Clock Tree Tool can import register settings from a *.rd1 "
		"file.\n");
	printf("The format of the *.rd1 file is:\n\n");
	printf("DeviceName %s\n", DEVICE_NAME);
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

	if (!cpu_is_am437x())
		return OMAPCONF_ERR_CPU;
	printf("DeviceName %s\n", DEVICE_NAME);

	ctt_am437x_regtable_init();

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
 * @FUNCTION		ctt_am437x_rd1_export
 * @BRIEF		export PRCM registers in CTT RD1 format
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		file: output file name
 * @DESCRIPTION		export PRCM registers in CTT RD1 format
 *//*------------------------------------------------------------------------ */
int ctt_am437x_rd1_export(char *file)
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

	if (!cpu_is_am437x())
		return OMAPCONF_ERR_CPU;
	fprintf(fd, "DeviceName %s\n", DEVICE_NAME);

	ctt_am437x_regtable_init();

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
 * @FUNCTION		ctt_am437x_main
 * @BRIEF		CTT main menu
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		CTT main menu
 *//*------------------------------------------------------------------------ */
int ctt_am437x_main(int argc, char *argv[])
{
	int ret;

	if (argc == 1) {
		ctt_am437x_regtable_init();

		if (strcmp(argv[0], "dump") == 0) {
			ret = ctt_am437x_dump();
		} else if (strcmp(argv[0], "rd1") == 0) {
			ret = ctt_am437x_rd1_export("CTT-AM437x1.rd1");
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
 * @FUNCTION		ctt_am437x_regtable_init
 * @BRIEF		initialize regtable
 * @RETURNS		0
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		initialize regtable
 *//*------------------------------------------------------------------------ */
static int ctt_am437x_regtable_init(void)
{
	int i = 0;

	/* Init PRCM register table */
	/* Data from: CTT-AM437x1.0_v1.0.0.0 */
	prcm_ctt_reg_table[i++].addr = 0x44DF2800;
	prcm_ctt_reg_table[i++].addr = 0x44DF2820;
	prcm_ctt_reg_table[i++].addr = 0x44DF2900;
	prcm_ctt_reg_table[i++].addr = 0x44DF2920;
	prcm_ctt_reg_table[i++].addr = 0x44DF2A00;
	prcm_ctt_reg_table[i++].addr = 0x44DF2A20;
	prcm_ctt_reg_table[i++].addr = 0x44DF2A28;
	prcm_ctt_reg_table[i++].addr = 0x44DF2A30;
	prcm_ctt_reg_table[i++].addr = 0x44DF2A38;
	prcm_ctt_reg_table[i++].addr = 0x44DF2A40;
	prcm_ctt_reg_table[i++].addr = 0x44DF2A48;
	prcm_ctt_reg_table[i++].addr = 0x44DF2B00;
	prcm_ctt_reg_table[i++].addr = 0x44DF2B20;
	prcm_ctt_reg_table[i++].addr = 0x44DF2B28;
	prcm_ctt_reg_table[i++].addr = 0x44DF2B30;
	prcm_ctt_reg_table[i++].addr = 0x44DF2B38;
	prcm_ctt_reg_table[i++].addr = 0x44DF2B40;
	prcm_ctt_reg_table[i++].addr = 0x44DF2B48;
	prcm_ctt_reg_table[i++].addr = 0x44DF2B50;
	prcm_ctt_reg_table[i++].addr = 0x44DF2B58;
	prcm_ctt_reg_table[i++].addr = 0x44DF2B60;
	prcm_ctt_reg_table[i++].addr = 0x44DF2B68;
	prcm_ctt_reg_table[i++].addr = 0x44DF2D20;
	prcm_ctt_reg_table[i++].addr = 0x44DF2D2C;
	prcm_ctt_reg_table[i++].addr = 0x44DF2D38;
	prcm_ctt_reg_table[i++].addr = 0x44DF2D3C;
	prcm_ctt_reg_table[i++].addr = 0x44DF2D60;
	prcm_ctt_reg_table[i++].addr = 0x44DF2D6C;
	prcm_ctt_reg_table[i++].addr = 0x44DF2D70;
	prcm_ctt_reg_table[i++].addr = 0x44DF2DA0;
	prcm_ctt_reg_table[i++].addr = 0x44DF2DAC;
	prcm_ctt_reg_table[i++].addr = 0x44DF2DB0;
	prcm_ctt_reg_table[i++].addr = 0x44DF2DB8;
	prcm_ctt_reg_table[i++].addr = 0x44DF2DE0;
	prcm_ctt_reg_table[i++].addr = 0x44DF2DEC;
	prcm_ctt_reg_table[i++].addr = 0x44DF2DF0;
	prcm_ctt_reg_table[i++].addr = 0x44DF2E20;
	prcm_ctt_reg_table[i++].addr = 0x44DF2E2C;
	prcm_ctt_reg_table[i++].addr = 0x44DF2E30;
	prcm_ctt_reg_table[i++].addr = 0x44DF2E60;
	prcm_ctt_reg_table[i++].addr = 0x44DF2E6C;
	prcm_ctt_reg_table[i++].addr = 0x44DF2E70;
	prcm_ctt_reg_table[i++].addr = 0x44DF4100;
	prcm_ctt_reg_table[i++].addr = 0x44DF4108;
	prcm_ctt_reg_table[i++].addr = 0x44DF4200;
	prcm_ctt_reg_table[i++].addr = 0x44DF4204;
	prcm_ctt_reg_table[i++].addr = 0x44DF4208;
	prcm_ctt_reg_table[i++].addr = 0x44DF420C;
	prcm_ctt_reg_table[i++].addr = 0x44DF4210;
	prcm_ctt_reg_table[i++].addr = 0x44DF4214;
	prcm_ctt_reg_table[i++].addr = 0x44DF4218;
	prcm_ctt_reg_table[i++].addr = 0x44DF421C;
	prcm_ctt_reg_table[i++].addr = 0x44DF4220;
	prcm_ctt_reg_table[i++].addr = 0x44DF4224;
	prcm_ctt_reg_table[i++].addr = 0x44DF4228;
	prcm_ctt_reg_table[i++].addr = 0x44DF422C;
	prcm_ctt_reg_table[i++].addr = 0x44DF4230;
	prcm_ctt_reg_table[i++].addr = 0x44DF4234;
	prcm_ctt_reg_table[i++].addr = 0x44DF4238;
	prcm_ctt_reg_table[i++].addr = 0x44DF423C;
	prcm_ctt_reg_table[i++].addr = 0x44DF4240;
	prcm_ctt_reg_table[i++].addr = 0x44DF4244;
	prcm_ctt_reg_table[i++].addr = 0x44DF4248;
	prcm_ctt_reg_table[i++].addr = 0x44DF424C;
	prcm_ctt_reg_table[i++].addr = 0x44DF4250;
	prcm_ctt_reg_table[i++].addr = 0x44DF4254;
	prcm_ctt_reg_table[i++].addr = 0x44DF4258;
	prcm_ctt_reg_table[i++].addr = 0x44DF425C;
	prcm_ctt_reg_table[i++].addr = 0x44DF4260;
	prcm_ctt_reg_table[i++].addr = 0x44DF8300;
	prcm_ctt_reg_table[i++].addr = 0x44DF8320;
	prcm_ctt_reg_table[i++].addr = 0x44DF8400;
	prcm_ctt_reg_table[i++].addr = 0x44DF8420;
	prcm_ctt_reg_table[i++].addr = 0x44DF8500;
	prcm_ctt_reg_table[i++].addr = 0x44DF8520;
	prcm_ctt_reg_table[i++].addr = 0x44DF8600;
	prcm_ctt_reg_table[i++].addr = 0x44DF8620;
	prcm_ctt_reg_table[i++].addr = 0x44DF8700;
	prcm_ctt_reg_table[i++].addr = 0x44DF8720;
	prcm_ctt_reg_table[i++].addr = 0x44DF8800;
	prcm_ctt_reg_table[i++].addr = 0x44DF8820;
	prcm_ctt_reg_table[i++].addr = 0x44DF8828;
	prcm_ctt_reg_table[i++].addr = 0x44DF8830;
	prcm_ctt_reg_table[i++].addr = 0x44DF8838;
	prcm_ctt_reg_table[i++].addr = 0x44DF8840;
	prcm_ctt_reg_table[i++].addr = 0x44DF8850;
	prcm_ctt_reg_table[i++].addr = 0x44DF8858;
	prcm_ctt_reg_table[i++].addr = 0x44DF8868;
	prcm_ctt_reg_table[i++].addr = 0x44DF8870;
	prcm_ctt_reg_table[i++].addr = 0x44DF8878;
	prcm_ctt_reg_table[i++].addr = 0x44DF8880;
	prcm_ctt_reg_table[i++].addr = 0x44DF8888;
	prcm_ctt_reg_table[i++].addr = 0x44DF8890;
	prcm_ctt_reg_table[i++].addr = 0x44DF8898;
	prcm_ctt_reg_table[i++].addr = 0x44DF88A0;
	prcm_ctt_reg_table[i++].addr = 0x44DF88A8;
	prcm_ctt_reg_table[i++].addr = 0x44DF8A00;
	prcm_ctt_reg_table[i++].addr = 0x44DF8A20;
	prcm_ctt_reg_table[i++].addr = 0x44DF8A28;
	prcm_ctt_reg_table[i++].addr = 0x44DF8A30;
	prcm_ctt_reg_table[i++].addr = 0x44DF8A38;
	prcm_ctt_reg_table[i++].addr = 0x44DF8A40;
	prcm_ctt_reg_table[i++].addr = 0x44DF8A48;
	prcm_ctt_reg_table[i++].addr = 0x44DF8A58;
	prcm_ctt_reg_table[i++].addr = 0x44DF8A60;
	prcm_ctt_reg_table[i++].addr = 0x44DF8A68;
	prcm_ctt_reg_table[i++].addr = 0x44DF8B00;
	prcm_ctt_reg_table[i++].addr = 0x44DF8B20;
	prcm_ctt_reg_table[i++].addr = 0x44DF8C00;
	prcm_ctt_reg_table[i++].addr = 0x44DF8C20;
	prcm_ctt_reg_table[i++].addr = 0x44DF8C28;
	prcm_ctt_reg_table[i++].addr = 0x44DF8C30;
	prcm_ctt_reg_table[i++].addr = 0x44DF8C38;
	prcm_ctt_reg_table[i++].addr = 0x44DF8C40;
	prcm_ctt_reg_table[i++].addr = 0x44DF8C48;
	prcm_ctt_reg_table[i++].addr = 0x44DF8C50;
	prcm_ctt_reg_table[i++].addr = 0x44DF8C58;
	prcm_ctt_reg_table[i++].addr = 0x44DF8C60;
	prcm_ctt_reg_table[i++].addr = 0x44DF8C68;
	prcm_ctt_reg_table[i++].addr = 0x44DF8C70;
	prcm_ctt_reg_table[i++].addr = 0x44DF8C78;
	prcm_ctt_reg_table[i++].addr = 0x44DF8C80;
	prcm_ctt_reg_table[i++].addr = 0x44DF8C88;
	prcm_ctt_reg_table[i++].addr = 0x44DF8C90;
	prcm_ctt_reg_table[i++].addr = 0x44DF8C98;
	prcm_ctt_reg_table[i++].addr = 0x44DF8CA0;
	prcm_ctt_reg_table[i++].addr = 0x44DF8CA8;
	prcm_ctt_reg_table[i++].addr = 0x44DF8CB0;
	prcm_ctt_reg_table[i++].addr = 0x44DF8CB8;
	prcm_ctt_reg_table[i++].addr = 0x44DF8CC0;
	prcm_ctt_reg_table[i++].addr = 0x44DF8CC8;
	prcm_ctt_reg_table[i++].addr = 0x44DF8CD0;
	prcm_ctt_reg_table[i++].addr = 0x44DF8CE0;
	prcm_ctt_reg_table[i++].addr = 0x44DF8D00;
	prcm_ctt_reg_table[i++].addr = 0x44DF8D08;
	prcm_ctt_reg_table[i++].addr = 0x44DF8D10;
	prcm_ctt_reg_table[i++].addr = 0x44DF8D18;
	prcm_ctt_reg_table[i++].addr = 0x44DF8D20;
	prcm_ctt_reg_table[i++].addr = 0x44DF8D28;
	prcm_ctt_reg_table[i++].addr = 0x44DF8D30;
	prcm_ctt_reg_table[i++].addr = 0x44DF8D38;
	prcm_ctt_reg_table[i++].addr = 0x44DF8D40;
	prcm_ctt_reg_table[i++].addr = 0x44DF8D48;
	prcm_ctt_reg_table[i++].addr = 0x44DF8D50;
	prcm_ctt_reg_table[i++].addr = 0x44DF8D58;
	prcm_ctt_reg_table[i++].addr = 0x44DF8D60;
	prcm_ctt_reg_table[i++].addr = 0x44DF8D68;
	prcm_ctt_reg_table[i++].addr = 0x44DF8D70;
	prcm_ctt_reg_table[i++].addr = 0x44DF8D78;
	prcm_ctt_reg_table[i++].addr = 0x44DF8D80;
	prcm_ctt_reg_table[i++].addr = 0x44DF8D88;
	prcm_ctt_reg_table[i++].addr = 0x44DF8D90;
	prcm_ctt_reg_table[i++].addr = 0x44DF8D98;
	prcm_ctt_reg_table[i++].addr = 0x44DF8DA0;
	prcm_ctt_reg_table[i++].addr = 0x44DF8DA8;
	prcm_ctt_reg_table[i++].addr = 0x44DF8DB0;
	prcm_ctt_reg_table[i++].addr = 0x44DF8DB8;
	prcm_ctt_reg_table[i++].addr = 0x44DF8DC0;
	prcm_ctt_reg_table[i++].addr = 0x44DF8F00;
	prcm_ctt_reg_table[i++].addr = 0x44DF8F20;
	prcm_ctt_reg_table[i++].addr = 0x44DF8F28;
	prcm_ctt_reg_table[i++].addr = 0x44DF8F30;
	prcm_ctt_reg_table[i++].addr = 0x44DF8F38;
	prcm_ctt_reg_table[i++].addr = 0x44DF9000;
	prcm_ctt_reg_table[i++].addr = 0x44DF9020;
	prcm_ctt_reg_table[i++].addr = 0x44DF9200;
	prcm_ctt_reg_table[i++].addr = 0x44DF9220;
	prcm_ctt_reg_table[i++].addr = 0x44DF9300;
	prcm_ctt_reg_table[i++].addr = 0x44DF9320;
	prcm_ctt_reg_table[i++].addr = 0x44E10040;
	prcm_ctt_reg_table[i++].addr = 0x44E101BC;
	prcm_ctt_reg_table[i++].addr = 0x44E10444;
	prcm_ctt_reg_table[i++].addr = 0x44E3E054;
	prcm_ctt_reg_table[i].addr = 0;

	dprintf("%s: last index=%d, size=%d", __func__, i, i + 1);

	return 0;
}
