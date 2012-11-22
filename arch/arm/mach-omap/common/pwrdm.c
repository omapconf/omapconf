/*
 *
 * @Component			OMAPCONF
 * @Filename			pwrdm.c
 * @Description			OMAP Generic Power Domain Definitions & APIs
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


#include <pwrdm.h>
#include <pwrdm54xx.h>
#include <pwrdm44xx.h>
#include <lib.h>
#include <mem.h>
#include <stdio.h>
#include <string.h>
#include <cpuinfo.h>


/* #define PWRDM_DEBUG */
#ifdef PWRDM_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void pwrdm_init(void)
{
	#ifdef PWRDM_DEBUG
	int i, count;
	const genlist *pwrdm_list;
	pwrdm_info pwrdm;
	#endif

	if (cpu_is_omap44xx()) {
		pwrdm44xx_init();
	} else if (cpu_is_omap54xx()) {
		pwrdm54xx_init();
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
	}

	#ifdef PWRDM_DEBUG
	pwrdm_list = pwrdm_list_get();
	count = genlist_getcount((genlist *) pwrdm_list);
	printf("Power Domain List:\n");
	for (i = 0; i < count; i++) {
		genlist_get((genlist *) pwrdm_list, i, (pwrdm_info *) &pwrdm);
		printf(" %s:\n", pwrdm.name);
		printf("  ID:%d (%s)\n", pwrdm.id,
			pwrdm54xx_name_get(pwrdm.id));
		printf("  VoltDM: %s\n", pwrdm.voltdm);
		printf("  PWRSTCTRL REG: %s\n", (pwrdm.pwrstctrl)->name);
		printf("  PWRSTST REG: %s\n", (pwrdm.pwrstst)->name);
		printf("  Properties: %d\n", pwrdm.properties);
		printf("\n\n");
	}
	printf("Power Domain count: %d\n\n", count);
	#endif
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm_deinit
 * @BRIEF		free dynamically allocated internal data.
 * @DESCRIPTION		free dynamically allocated internal data.
 *			MUST BE CALLED AT END OF EXECUTION.
 *//*------------------------------------------------------------------------ */
void pwrdm_deinit(void)
{
	if (cpu_is_omap44xx()) {
		pwrdm44xx_deinit();
	} else if (cpu_is_omap54xx()) {
		pwrdm54xx_deinit();
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm_list_get
 * @BRIEF		return the list of power domains
 * @RETURNS		list of power domains in case of success
 *			NULL in case of error
 * @DESCRIPTION		return the list of power domains
 *//*------------------------------------------------------------------------ */
const genlist *pwrdm_list_get(void)
{
	if (cpu_is_omap44xx()) {
		return pwrdm44xx_list_get();
	} else if (cpu_is_omap54xx()) {
		return pwrdm54xx_list_get();
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		return NULL;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm_count_get
 * @BRIEF		return the number of power domains
 * @RETURNS		number of power domains (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @DESCRIPTION		return the number of power domains
 *//*------------------------------------------------------------------------ */
int pwrdm_count_get(void)
{
	if (cpu_is_omap44xx()) {
		return pwrdm44xx_count_get();
	} else if (cpu_is_omap54xx()) {
		return pwrdm54xx_count_get();
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		return OMAPCONF_ERR_CPU;
	}
}



