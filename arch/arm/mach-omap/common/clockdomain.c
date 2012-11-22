/*
 *
 * @Component			OMAPCONF
 * @Filename			clockdomain.c
 * @Description			Clock Domain Generic Definitions & Functions
 * @Author			Patrick Titiano (p-titiano@ti.com)
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


#include <clockdomain.h>
#include <clkdm44xx.h>
#include <clkdm54xx.h>
#include <lib.h>
#include <stdlib.h>
#include <string.h>
#include <cpuinfo.h>


#define CLKDM_DEBUG
#ifdef CLKDM_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void clkdm_init(void)
{
	#ifdef CLKDM_DEBUG
	int i, count;
	const genlist *clkdm_list;
	clkdm_info clkdm;
	#endif

	if (cpu_is_omap44xx()) {
		clkdm44xx_init();
	} else if (cpu_is_omap54xx()) {
		clkdm54xx_init();
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
	}

	#ifdef CLKDM_DEBUG
	clkdm_list = clkdm_list_get();
	count = genlist_getcount((genlist *) clkdm_list);
	printf("Clock Domain List:\n");
	for (i = 0; i < count; i++) {
		genlist_get((genlist *) clkdm_list, i, (clkdm_info *) &clkdm);
		printf(" %s:\n", clkdm.name);
		printf("  ID:%d (%s)\n", clkdm.id,
			clkdm54xx_name_get(clkdm.id));
		printf("  PwrDM: %s\n", clkdm.pwrdm);
		printf("  VoltDM: %s\n", clkdm.voltdm);
		printf("  CLKSTCTRL REG: %s\n", (clkdm.clkstctrl)->name);
		printf("  Properties: %d\n", clkdm.properties);
		printf("\n\n");
	}
	printf("Clock Domain count: %d\n\n", count);
	#endif
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm_deinit
 * @BRIEF		free dynamically allocated internal data.
 * @DESCRIPTION		free dynamically allocated internal data.
 *			MUST BE CALLED AT END OF EXECUTION.
 *//*------------------------------------------------------------------------ */
void clkdm_deinit(void)
{
	if (cpu_is_omap44xx()) {
		clkdm44xx_deinit();
	} else if (cpu_is_omap54xx()) {
		clkdm54xx_deinit();
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm_list_get
 * @BRIEF		return the list of clock domains
 * @RETURNS		list of clock domains in case of success
 *			NULL in case of error
 * @DESCRIPTION		return the list of clock domains
 *//*------------------------------------------------------------------------ */
const genlist *clkdm_list_get(void)
{
	if (cpu_is_omap44xx()) {
		return clkdm44xx_list_get();
	} else if (cpu_is_omap54xx()) {
		return clkdm54xx_list_get();
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		return NULL;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm_count_get
 * @BRIEF		return the number of clock domains
 * @RETURNS		number of clock domains (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @DESCRIPTION		return the number of clock domains
 *//*------------------------------------------------------------------------ */
int clkdm_count_get(void)
{
	if (cpu_is_omap44xx()) {
		return clkdm44xx_count_get();
	} else if (cpu_is_omap54xx()) {
		return clkdm54xx_count_get();
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		return OMAPCONF_ERR_CPU;
	}
}
