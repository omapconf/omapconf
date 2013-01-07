/*
 *
 * @Component			OMAPCONF
 * @Filename			abe54xx.c
 * @Description			OMAP5 ABE Definitions & Functions
 * @Author			Patrick Titiano (p-titiano@ti.com)
 * @Date			2011
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
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


#include <abe54xx.h>
#include <clockdomain.h>
#include <lib54xx.h>
#include <cpuinfo.h>
#include <help.h>
#include <mem.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


/* #define ABE54XX_DEBUG */
#ifdef ABE54XX_DEBUG
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

struct atc_item atc54xx_list[OMAP_ABE_ATC_LIST_SIZE] = {
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


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		abe54xx_atc_status_show
 * @BRIEF		analyze ABE ATC configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output file stream
 * @DESCRIPTION		analyze ABE ATC configuration
 *//*------------------------------------------------------------------------ */
int abe54xx_atc_status_show(FILE *stream)
{
	int i, j;
	int read_count, write_count;
	struct atc_desc atc[OMAP_ABE_ATC_NB_READ];
	int ret;
	unsigned int reg_addr;
	clkdm_status clkst;

	clkst = clockdm_status_get("CLKDM_ABE");
	if (clkst != CLKDM_RUNNING) {
		fprintf(stream,
			"ABE clocks are not running, cannot proceed further.\n\n");
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
		reg_addr = OMAP_ABE_DMEM_ADDR + atc54xx_list[i].offset;
		ret = mem_address_range_read(
			reg_addr, (unsigned int *)(&atc[0]), 2);
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
					"HW IP to DMEM):\n",
					atc54xx_list[i].name);
			else
				fprintf(stream,
					"ATC for %s is running (Transfer form "
					"DMEM to HW IP):\n",
					atc54xx_list[i].name);

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
