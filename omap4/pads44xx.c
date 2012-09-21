/*
 *
 * @Component			OMAPCONF
 * @Filename			pads44xx.c
 * @Description			OMAP4 IO PAD Audit Function
 * @Author			Ivan Khoronzhuk <ivan.khoronzhuk@ti.com>
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


#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pads44xx.h>
#include <cpuinfo.h>
#include <lib.h>
#include <mem.h>


struct mux_reg_range {
	char *name;
	unsigned int start_phy_addr;	/* inclusive */
	unsigned int end_phy_addr;	/* inclusive */
};

struct mux_reg_range omap4460_4470_padconf_core = {
	.name = "core",
	.start_phy_addr = 0x4A100040,	/* CONTROL_CORE_PAD0_GPMC_AD0_PAD1_GPMC_AD1 */
	.end_phy_addr = 0x4A1001D4,	/* CONTROL_CORE_PAD0_DPM_EMU19_PAD1_CSI22_DX2 */
};

struct mux_reg_range omap4460_4470_padconf_wakeup = {
	.name = "wakeup",
	.start_phy_addr = 0x4A31E040,	/* CONTROL_WKUP_PAD0_GPIO_WK0_PAD1_GPIO_WK1 */
	.end_phy_addr = 0x4A31E074,	/* CONTROL_WKUP_PAD0_JTAG_TDI_PAD1_JTAG_TDO */
};

struct mux_reg_range *omap4460_4470_padconf[] = {
	&omap4460_4470_padconf_core,
	&omap4460_4470_padconf_wakeup,
};

#define OMAP4_NUM_MUX_RANGES	(sizeof(omap4460_4470_padconf)/\
	sizeof(struct mux_reg_range *))

#define OMAP4_MUX_MASK			 (0x7 << 0)
#define OMAP4_PULL_ENA                   (1 << 3)
#define OMAP4_PULL_UP                    (1 << 4)

#define OMAP4_INPUT_EN                   (1 << 8)
#define OMAP4_OFF_EN                     (1 << 9)
#define OMAP4_OFFOUT_EN                  (1 << 10)
#define OMAP4_OFFOUT_VAL                 (1 << 11)
#define OMAP4_OFF_PULL_EN                (1 << 12)
#define OMAP4_OFF_PULL_UP                (1 << 13)
#define OMAP4_WAKEUP_EN                  (1 << 14)

#define OMAP4_WAKEUP_EVENT               (1 << 15)


static int violation_count = 0;
static int total_count = 0;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		marker
 * @BRIEF
 * @RETURNS
 * @param[in]		stream: output stream
 * @DESCRIPTION
 *//*------------------------------------------------------------------------ */
static inline void marker(FILE *stream)
{
	fprintf(stream, "================================================\n");
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		check_mux_reg
 * @BRIEF
 * @RETURNS
 * @param[in]		stream: output stream
 * @param[in]		mux:
 * @param[in]		reg_addr:
 * @param[in]		val:
 * @DESCRIPTION
 *//*------------------------------------------------------------------------ */
static void check_mux_reg(FILE *stream, struct mux_reg_range *mux,
		      unsigned int reg_addr, unsigned short val)
{
	unsigned char mux_mode = -1;
	int pull_active = -1;
	int active_input = -1;
	int off_ovr_active = -1;
	int off_out_enable = -1;
	int off_out_val = -1;
	int off_out_pull = -1;
	int wakeup_enable = -1;

	total_count++;
	val &= 0xFFFF;
	mux_mode = val & OMAP4_MUX_MASK;

	switch (val & (OMAP4_PULL_UP | OMAP4_PULL_ENA)) {
	case OMAP4_PULL_ENA:
		pull_active = 0;
		break;
	case (OMAP4_PULL_ENA | OMAP4_PULL_UP):
		pull_active = 1;
		break;
	default:
	case 0:
		pull_active = -1;
		break;
	}
	active_input = (val & OMAP4_INPUT_EN) ? 1 : 0;
	off_ovr_active = (val & OMAP4_OFF_EN) ? 1 : 0;
	off_out_enable = (val & OMAP4_OFFOUT_EN) ? 0 : 1;
	off_out_val = (val & OMAP4_OFFOUT_VAL) ? 1 : 0;

	switch (val & (OMAP4_OFF_PULL_EN | OMAP4_OFF_PULL_UP)) {
	case OMAP4_OFF_PULL_EN:
		off_out_pull = 0;
		break;
	case (OMAP4_OFF_PULL_EN | OMAP4_OFF_PULL_UP):
		off_out_pull = 1;
		break;
	default:
	case 0:
		off_out_pull = -1;
		break;
	}

	wakeup_enable = (val & OMAP4_WAKEUP_EN) ? 1 : 0;

	/* CHECKS FOR VIOLATIONS */
	/*
	 * VIOLATION - if off mode override is used with output mode
	 * we have a risk of glitch to the extent of 5ns
	 * if active state of the PIN is HI and OFF override state is HI.
	 */
	if (off_ovr_active && off_out_enable && off_out_val) {
		fprintf(stream, "\n%d. VIOLATION:OFF_OVERRIDE OUTPUT VALUE is HI (glitch risk if active state == HIGH)",
		       violation_count);
		/* dump reg */
		violation_count++;
		fprintf(stream, ":(MUX GRP-%s) control pad address:0x%08x Value:0x%04x\n",
		       mux->name, reg_addr, val);
		fprintf(stream, "MUX_mode=%d (%s)\n", mux_mode,
		       (mux_mode == 3) ? "gpio?" : "other?");
		fprintf(stream, "Active direction=%s\n", active_input ? "input pin" :
		       "output pin");
		fprintf(stream, "Active pull=%s\n", (!pull_active) ? "Pull Down" :
		       (pull_active == 1) ? "Pull Up" : "n/a");
		fprintf(stream, "OFF Mode override_active=%s\n", off_ovr_active ? "yes" : "no");
		fprintf(stream, "OFF Mode direction=");
		if (!off_out_enable)
			fprintf(stream, "input pin\n");
		else
			fprintf(stream, "output Drive %s\n", off_out_val ? "HIGH " : "LOW");
		fprintf(stream, "OFF Mode pull=%s\n", (!off_out_pull) ? "Pull Down" :
		       (off_out_pull == 1) ? "Pull Up" : "n/a");

		fprintf(stream, "Wakeup enabled = %s\n", wakeup_enable ? "yes" : "no");
	}

	return;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pads44xx_audit
 * @BRIEF		audit IO PAD configuration for potential glitch during
 *			OFF mode transition (HW bug)
 * @RETURNS		>= 0 violation count
 *			< 0 in case of unexpected internal error
 * @param[in]		stream: output file
 * @DESCRIPTION		audit IO PAD configuration for potential glitch during
 *			OFF mode transition (HW bug)
 *//*------------------------------------------------------------------------ */
int pads44xx_audit(FILE *stream)
{
	struct mux_reg_range *mux;
	unsigned int reg;
	unsigned int i;

	if (cpu_is_omap4430()) {
		fprintf(stream, "Glitches are not present on OMAP4430\n");
		return 0;
	} else if (!(cpu_is_omap4460() || cpu_is_omap4470())) {
		fprintf(stream, "UNSUPPORTED.. sorry\n");
		return -1;
	}

	marker(stream);
	for (i = 0; i < OMAP4_NUM_MUX_RANGES; i++) {
		mux = omap4460_4470_padconf[i];
		fprintf(stream, "--<- Checking group %d/%d - \"%s\"\n",
		       i + 1, OMAP4_NUM_MUX_RANGES, mux->name);
		reg = mux->start_phy_addr;
		while (reg <= mux->end_phy_addr) {
			unsigned int reg_val = 0;
			int ret = 0;
			ret = mem_read(reg, &reg_val);
			if (ret) {
				fprintf(stream,
					"error %d at 0x%08x %s start=0x%08x to 0x%08x\n",
					ret, reg, mux->name, mux->start_phy_addr,
					mux->end_phy_addr);
				return ret;
			}
			check_mux_reg(stream, mux, reg, reg_val);
			check_mux_reg(stream, mux, reg + 2, reg_val >> 16);
			reg += 4;
		}
		fprintf(stream, "\n---> Done\n\n");
	}
	marker(stream);
	fprintf(stream, "Violations = %d out of %d pad regs checked\n",
	       violation_count, total_count);
	marker(stream);
	fprintf(stream, "Detailed description:\n"
		"If output override value is HI and "
		"active state HI, there is a potential "
		"for glitch while entering OFF mode. "
		"OMAP Erratum - TBD\n");
	marker(stream);
	fprintf(stream, "IMPORTANT NOTES and DISCLAIMERS:\n"
		"1. This is a snapshot view - does not audit padconf changes on "
		"the fly!!!\n"
		"2. This is not an 100%% authoritative audit - There are risks "
		"of false positives and negatives - detailed review of mux is "
		"highly recommended\n"
		"3. This is meant to ease the search for mux bugs-not really "
		"designed to handle firewalled registers and potential"
		" register holes\n");
	marker(stream);
	fprintf(stream, "\n");

	return violation_count;
}
