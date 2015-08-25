/*
 *
 * @Component			OMAPCONF
 * @Filename			pct44xx.c
 * @Description			Output the CONTROL Module registers in a format
 *				that can be imported into the pad configuration
 *				tool (PCT)
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


#include <pct44xx.h>
#include <lib.h>
#include <lib44xx.h>
#include <help.h>
#include <mem.h>
#include <cpuinfo.h>
#include <string.h>

/* #define PCT44XX_DEBUG */
#ifdef PCT_OMAP4_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

#define PRCM_PCT_REG_TABLE_SIZE        143

static char pct_filename[] = "PCT-OMAP44XX-REG_DUMP.rd1";
static reg_table prcm_pct_reg_table[PRCM_PCT_REG_TABLE_SIZE + 1];

static int pct44xx_regtable_init(void);


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		ctt44xx_dump
 * @BRIEF		dump PRCM registers
 * @RETURNS		0
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		dump PRCM registers
 *//*------------------------------------------------------------------------ */
int pct44xx_dump(void)
{
	unsigned int i = 0;
	unsigned int ret, val = 0;
	int err = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_ARG);

	printf("The PAD Configuration Tool can import register settings from a "
		"*.rd1 file.\n");
	printf("The format of the *.rd1 file is:\n\n");
	printf("DeviceName OMAPxxxx_ESx.x\n");
	printf("<register address> <register value>\n");
	printf("<register address> <register value>\n");
	printf("...\n\n");
	printf("Copy the below output between the begin and end separators "
		"into a\n");
	printf("file with the extension *.rd1 and this file can be read by "
		"the\n");
	printf("PAD Configuration Tool\n\n");
	printf("|--------------------------- pct dump begin -------------------"
		"---|\n");

	if (cpu_is_omap4430())
		printf("DeviceName OMAP4430_ES2.x\n");
	else if (cpu_is_omap4460())
		printf("DeviceName OMAP4460_ES1.0\n");
	else if (cpu_is_omap4470())
		printf("DeviceName OMAP4470_ES1.0\n");
	else
		return OMAPCONF_ERR_CPU;

	pct44xx_regtable_init();

	while (prcm_pct_reg_table[i].addr != 0) {
		/* display register addr & content (hex) */
		ret = mem_read(prcm_pct_reg_table[i].addr, &val);
		if (ret == 0)
			printf("0x%08X 0x%08X\n", prcm_pct_reg_table[i].addr,
				val);
		else {
			fprintf(stderr,
				"omapconf: read error! (addr=0x%08X, err=%d)\n",
				prcm_pct_reg_table[i].addr, ret);
			err = OMAPCONF_ERR_REG_ACCESS;
		}
		i++;
	}

	printf("|---------------------------- pct dump end --------------------"
		"---|\n");

	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pct44xx_rd1_export
 * @BRIEF		export PRCM registers in PCT RD1 format
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		filename: output file name
 * @DESCRIPTION		export PRCM registers in PCT RD1 format
 *//*------------------------------------------------------------------------ */
int pct44xx_rd1_export(char *filename)
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
		fprintf(fd, "DeviceName OMAP4460_ES1.0\n");
	} else if (cpu_is_omap4470()) {
		fprintf(fd, "DeviceName OMAP4470_ES1.0\n");
	} else {
		return OMAPCONF_ERR_CPU;
		goto pct44xx_rd1_export_end;
	}

	pct44xx_regtable_init();

	while (prcm_pct_reg_table[i].addr != 0) {
		/* display register addr & content (hex) */
		ret = mem_read(prcm_pct_reg_table[i].addr, &val);
		if (ret == 0)
			fprintf(fd, "0x%08X 0x%08X\n",
				prcm_pct_reg_table[i].addr, val);
		else {
			fprintf(stderr,
				"omapconf: read error! (addr=0x%08X, err=%d)\n",
				prcm_pct_reg_table[i].addr, ret);
			err = OMAPCONF_ERR_REG_ACCESS;
		}
		i++;
	}

	printf("Output written to file '%s'.\n", filename);
	err = 0;

pct44xx_rd1_export_end:
	if (fd != NULL)
		fclose(fd);
	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pct44xx_main
 * @BRIEF		main entry point
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		main entry point
 *//*------------------------------------------------------------------------ */
int pct44xx_main(int argc, char *argv[])
{
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_ARG);

	if (argc == 2) {
		if (strcmp(argv[1], "dump") == 0)
			ret = pct44xx_dump();
		else if (strcmp(argv[1], "rd1") == 0)
			ret = pct44xx_rd1_export(pct_filename);
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
 * @FUNCTION		pct44xx_regtable_init
 * @BRIEF		initialize regtable
 * @RETURNS		0
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		initialize regtable
 *//*------------------------------------------------------------------------ */
static int pct44xx_regtable_init(void)
{
	int i = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_ARG);

	/* Init PRCM registers table */
	prcm_pct_reg_table[i++].addr = 0x4A100040;
	prcm_pct_reg_table[i++].addr = 0x4A100044;
	prcm_pct_reg_table[i++].addr = 0x4A100048;
	prcm_pct_reg_table[i++].addr = 0x4A10004C;
	prcm_pct_reg_table[i++].addr = 0x4A100050;
	prcm_pct_reg_table[i++].addr = 0x4A100054;
	prcm_pct_reg_table[i++].addr = 0x4A100058;
	prcm_pct_reg_table[i++].addr = 0x4A10005C;
	prcm_pct_reg_table[i++].addr = 0x4A100060;
	prcm_pct_reg_table[i++].addr = 0x4A100064;
	prcm_pct_reg_table[i++].addr = 0x4A100068;
	prcm_pct_reg_table[i++].addr = 0x4A10006C;
	prcm_pct_reg_table[i++].addr = 0x4A100070;
	prcm_pct_reg_table[i++].addr = 0x4A100074;
	prcm_pct_reg_table[i++].addr = 0x4A100078;
	prcm_pct_reg_table[i++].addr = 0x4A10007C;
	prcm_pct_reg_table[i++].addr = 0x4A100080;
	prcm_pct_reg_table[i++].addr = 0x4A100084;
	prcm_pct_reg_table[i++].addr = 0x4A100088;
	prcm_pct_reg_table[i++].addr = 0x4A10008C;
	prcm_pct_reg_table[i++].addr = 0x4A100090;
	prcm_pct_reg_table[i++].addr = 0x4A100094;
	prcm_pct_reg_table[i++].addr = 0x4A100098;
	prcm_pct_reg_table[i++].addr = 0x4A10009C;
	prcm_pct_reg_table[i++].addr = 0x4A1000A0;
	prcm_pct_reg_table[i++].addr = 0x4A1000A4;
	prcm_pct_reg_table[i++].addr = 0x4A1000A8;
	prcm_pct_reg_table[i++].addr = 0x4A1000AC;
	prcm_pct_reg_table[i++].addr = 0x4A1000B0;
	prcm_pct_reg_table[i++].addr = 0x4A1000B4;
	prcm_pct_reg_table[i++].addr = 0x4A1000B8;
	prcm_pct_reg_table[i++].addr = 0x4A1000BC;
	prcm_pct_reg_table[i++].addr = 0x4A1000C0;
	prcm_pct_reg_table[i++].addr = 0x4A1000C4;
	prcm_pct_reg_table[i++].addr = 0x4A1000C8;
	prcm_pct_reg_table[i++].addr = 0x4A1000CC;
	prcm_pct_reg_table[i++].addr = 0x4A1000D0;
	prcm_pct_reg_table[i++].addr = 0x4A1000D4;
	prcm_pct_reg_table[i++].addr = 0x4A1000D8;
	prcm_pct_reg_table[i++].addr = 0x4A1000DC;
	prcm_pct_reg_table[i++].addr = 0x4A1000E0;
	prcm_pct_reg_table[i++].addr = 0x4A1000E4;
	prcm_pct_reg_table[i++].addr = 0x4A1000E8;
	prcm_pct_reg_table[i++].addr = 0x4A1000EC;
	prcm_pct_reg_table[i++].addr = 0x4A1000F0;
	prcm_pct_reg_table[i++].addr = 0x4A1000F4;
	prcm_pct_reg_table[i++].addr = 0x4A1000F8;
	prcm_pct_reg_table[i++].addr = 0x4A1000FC;
	prcm_pct_reg_table[i++].addr = 0x4A100100;
	prcm_pct_reg_table[i++].addr = 0x4A100104;
	prcm_pct_reg_table[i++].addr = 0x4A100108;
	prcm_pct_reg_table[i++].addr = 0x4A10010C;
	prcm_pct_reg_table[i++].addr = 0x4A100110;
	prcm_pct_reg_table[i++].addr = 0x4A100114;
	prcm_pct_reg_table[i++].addr = 0x4A100118;
	prcm_pct_reg_table[i++].addr = 0x4A10011C;
	prcm_pct_reg_table[i++].addr = 0x4A100120;
	prcm_pct_reg_table[i++].addr = 0x4A100124;
	prcm_pct_reg_table[i++].addr = 0x4A100128;
	prcm_pct_reg_table[i++].addr = 0x4A10012C;
	prcm_pct_reg_table[i++].addr = 0x4A100130;
	prcm_pct_reg_table[i++].addr = 0x4A100134;
	prcm_pct_reg_table[i++].addr = 0x4A100138;
	prcm_pct_reg_table[i++].addr = 0x4A10013C;
	prcm_pct_reg_table[i++].addr = 0x4A100140;
	prcm_pct_reg_table[i++].addr = 0x4A100144;
	prcm_pct_reg_table[i++].addr = 0x4A100148;
	prcm_pct_reg_table[i++].addr = 0x4A10014C;
	prcm_pct_reg_table[i++].addr = 0x4A100150;
	prcm_pct_reg_table[i++].addr = 0x4A100154;
	prcm_pct_reg_table[i++].addr = 0x4A100158;
	prcm_pct_reg_table[i++].addr = 0x4A10015C;
	prcm_pct_reg_table[i++].addr = 0x4A100160;
	prcm_pct_reg_table[i++].addr = 0x4A100164;
	prcm_pct_reg_table[i++].addr = 0x4A100168;
	prcm_pct_reg_table[i++].addr = 0x4A10016C;
	prcm_pct_reg_table[i++].addr = 0x4A100170;
	prcm_pct_reg_table[i++].addr = 0x4A100174;
	prcm_pct_reg_table[i++].addr = 0x4A100178;
	prcm_pct_reg_table[i++].addr = 0x4A10017C;
	prcm_pct_reg_table[i++].addr = 0x4A100180;
	prcm_pct_reg_table[i++].addr = 0x4A100184;
	prcm_pct_reg_table[i++].addr = 0x4A100188;
	prcm_pct_reg_table[i++].addr = 0x4A10018C;
	prcm_pct_reg_table[i++].addr = 0x4A100190;
	prcm_pct_reg_table[i++].addr = 0x4A100194;
	prcm_pct_reg_table[i++].addr = 0x4A100198;
	prcm_pct_reg_table[i++].addr = 0x4A10019C;
	prcm_pct_reg_table[i++].addr = 0x4A1001A0;
	prcm_pct_reg_table[i++].addr = 0x4A1001A4;
	prcm_pct_reg_table[i++].addr = 0x4A1001A8;
	prcm_pct_reg_table[i++].addr = 0x4A1001AC;
	prcm_pct_reg_table[i++].addr = 0x4A1001B0;
	prcm_pct_reg_table[i++].addr = 0x4A1001B4;
	prcm_pct_reg_table[i++].addr = 0x4A1001B8;
	prcm_pct_reg_table[i++].addr = 0x4A1001BC;
	prcm_pct_reg_table[i++].addr = 0x4A1001C0;
	prcm_pct_reg_table[i++].addr = 0x4A1001C4;
	prcm_pct_reg_table[i++].addr = 0x4A1001C8;
	prcm_pct_reg_table[i++].addr = 0x4A1001CC;
	prcm_pct_reg_table[i++].addr = 0x4A1001D0;
	prcm_pct_reg_table[i++].addr = 0x4A1001D4;
	prcm_pct_reg_table[i++].addr = 0x4A1005A4;
	prcm_pct_reg_table[i++].addr = 0x4A1005A8;
	prcm_pct_reg_table[i++].addr = 0x4A1005AC;
	prcm_pct_reg_table[i++].addr = 0x4A1005B8;
	prcm_pct_reg_table[i++].addr = 0x4A1005BC;
	prcm_pct_reg_table[i++].addr = 0x4A1005C0;
	prcm_pct_reg_table[i++].addr = 0x4A1005C4;
	prcm_pct_reg_table[i++].addr = 0x4A1005C8;
	prcm_pct_reg_table[i++].addr = 0x4A1005CC;
	prcm_pct_reg_table[i++].addr = 0x4A1005D0;
	prcm_pct_reg_table[i++].addr = 0x4A1005D4;
	prcm_pct_reg_table[i++].addr = 0x4A1005D8;
	prcm_pct_reg_table[i++].addr = 0x4A100604;
	prcm_pct_reg_table[i++].addr = 0x4A100638;
	prcm_pct_reg_table[i++].addr = 0x4A10063C;
	prcm_pct_reg_table[i++].addr = 0x4A100640;
	prcm_pct_reg_table[i++].addr = 0x4A100644;
	prcm_pct_reg_table[i++].addr = 0x4A100648;
	prcm_pct_reg_table[i++].addr = 0x4A10064C;
	prcm_pct_reg_table[i++].addr = 0x4A100650;
	prcm_pct_reg_table[i++].addr = 0x4A100654;
	prcm_pct_reg_table[i++].addr = 0x4A31E040;
	prcm_pct_reg_table[i++].addr = 0x4A31E044;
	prcm_pct_reg_table[i++].addr = 0x4A31E048;
	prcm_pct_reg_table[i++].addr = 0x4A31E04C;
	prcm_pct_reg_table[i++].addr = 0x4A31E050;
	prcm_pct_reg_table[i++].addr = 0x4A31E054;
	prcm_pct_reg_table[i++].addr = 0x4A31E058;
	prcm_pct_reg_table[i++].addr = 0x4A31E05C;
	prcm_pct_reg_table[i++].addr = 0x4A31E060;
	prcm_pct_reg_table[i++].addr = 0x4A31E064;
	prcm_pct_reg_table[i++].addr = 0x4A31E068;
	prcm_pct_reg_table[i++].addr = 0x4A31E06C;
	prcm_pct_reg_table[i++].addr = 0x4A31E070;
	prcm_pct_reg_table[i++].addr = 0x4A31E074;
	prcm_pct_reg_table[i++].addr = 0x4A31E5A0;
	prcm_pct_reg_table[i++].addr = 0x4A31E5A4;
	prcm_pct_reg_table[i++].addr = 0x4A31E5A8;
	prcm_pct_reg_table[i++].addr = 0x4A31E5B0;
	prcm_pct_reg_table[i++].addr = 0x4A31E5B4;
	prcm_pct_reg_table[i++].addr = 0x4A31E604;
	prcm_pct_reg_table[i].addr = 0;

	dprintf("prcm_pct_reg_table last index=%d, size=%d\n", i, i + 1);

	return 0;
}
