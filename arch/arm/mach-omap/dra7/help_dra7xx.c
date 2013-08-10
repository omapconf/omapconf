/*
 *
 * @Component			OMAPCONF
 * @Filename			help_dra7xx.c
 * @Description			Help for DRA7 specific functions
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


#include <help_dra7xx.h>
#include <stdio.h>
#include <cpuinfo.h>
#include <tlv320aic3x.h>


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		help_dra7xx
 * @BRIEF		display help for DRA7-specific functions
 * @param[in]		cat: help category to display
 * @DESCRIPTION		display help for DRA7-specific functions
 *//*------------------------------------------------------------------------ */
void help_dra7xx(help_category cat, char *context)
{
	if (cat >= HELP_CATEGORY_MAX) {
		fprintf(stderr, "%s(): incorrect category!!! (%u)\n",
			__func__, cat);
		return;
	}
	if (context == NULL) {
		fprintf(stderr, "%s(): context == NULL!!!\n", __func__);
		return;
	}

	/* DRA7-specific commands */
	if ((cat == HELP_ALL) || (cat == HELP_EXPORT)) {
		printf("\n\tomapconf export ctt [<filename>]\n");
		printf("\t    Export PRCM registers to "
			"<filename> or stdout if omitted.\n");

		printf("\n\tomapconf ctt dump (alternative call of omapconf-export-ctt)\n");
		printf("\t    Export PRCM registers to stdout.\n");

		printf("\n\tomapconf ctt rd1\n");
		printf("\t    Export PRCM registers in rd1 format for Clock "
			"Tree Tool (CTT, <http://omappedia.org/wiki/CTT>).\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_DPLL)) {
		printf("\n\tomapconf dump dpll [<dpll>]\n");
		printf("\t    RAW dump of <dpll> registers ('all' assumed if "
			"omitted).\n");
		printf("\t    Supported <dpll>: all, abe, core, ddr, dsp, eve, "
			"gmac, gpu, iva, mpu, pcieref, per, usb.\n");

		printf("\n\tomapconf show dpll [cfg]\n");
		printf("\t    Print the complete configuration of all DPLL "
			"([cfg] may be omitted).\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_PRCM)) {
		printf("\n\tomapconf dump prcm [<pwrdm>]\n");
		printf("\t    Dump PRCM Registers related to <pwrdm> power"
			" domain ('all' assumed if omitted).\n");
		printf("\t    Supported <pwrdm>: all, cam, core, coreaon, "
			"ckgen, dev, dsp, dss, emu, eve, gpu, instr, ipu, "
			"iva, l3init, l4per, mpu, rtc, vpe, wkupaon.\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_AUDIOIC)) {
		printf("\n\tomapconf dump audioic\n");
		printf("\t    Dump tlv320aic3106 (Audio IC) registers.\n");
		printf("\t    Default audioic is in bus %u with address 0x%02x\n",
		       TLV320AIC3X_I2C_DFLT_BUS, TLV320AIC3X_I2C_VALID_ADDR1);

		printf("\n\tomapconf dump audioic 'bus' 0x'chip\n");
		printf("\t    Dump tlv320aic3106 (Audio IC) registers:\n");
		printf("\t    'i2cbus' is decimal value.\n");
		printf("\t    'chip-address' is hexadecimal value.\n");
	}
}
