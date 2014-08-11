/*
 *
 * @Component			OMAPCONF
 * @Filename			help_am335x.c
 * @Description			Help for AM335X specific functions
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
#include <help_am335x.h>
#include <stdio.h>


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		help_am335x
 * @BRIEF		display help for AM335X-specific functions
 * @param[in]		cat: help category to display
 * @DESCRIPTION		display help for AM335X-specific functions
 *//*------------------------------------------------------------------------ */
void help_am335x(help_category cat, char *context)
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

	/* AM335X-specific commands */
	if ((cat == HELP_ALL) || (cat == HELP_EXPORT)) {
		printf("\n\tomapconf export ctt [<filename>]\n");
		printf("\t    Export PRCM registers in .rd1 format for Clock "
			"Tree Tool (CTT, <http://omappedia.org/wiki/CTT>), to "
			"<filename> or stdout if omitted.\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_EMIF)) {
		printf("\n\tomapconf dump emif\n");
		printf("\t    Dump EMIF4D registers to stdout\n");
	}

	if((cat == HELP_ALL) || (cat == HELP_PRCM)) {
		printf("\n\tomapconf dump prcm [<pwrdm>]\n");
		printf("\t    Dump PRCM Registers related to <pwrdm> power "
			"domain ('all' assumed if omitted).\n");
		printf("\t    Support <pwrdm>: all, dev, efuse, gfx, mpu, per, "
			"rtc, wkup\n");
	}

	if((cat == HELP_ALL) || (cat == HELP_DPLL)) {
		printf("\n\tomapconf dump dpll [<dpll>]\n");
		printf("\t    Dump of <dpll> registers ('all' assumed if )"
			"omitted).\n");
		printf("\t    Supported <dpll>: all, core, disp, ddr, mpu, "
			"per\n");

		printf("\n\tomapconf show dpll [cfg]\n");
		printf("\t    Print the complete configuration of all DPLL "
			"([cfg] may be omitted).\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_SOC_OPP)) {
		printf("\n\tomapconf show opp\n");
		printf("\t    Print AM335X current OPerating Points (OPP) "
			"(voltage, frequency for MPU/CORE voltage domains), "
			"including main modules frequencies.\n");
	}

	if ((cat == HELP_ALL) || (cat == HELP_SOC_PWST)) {
		printf("\n\tomapconf show pwst\n");
		printf("\t    Print AM335X power status (OPP, voltage/power/"
			"clock domains states, modules frequency and "
			"status).\n");
	}
}
