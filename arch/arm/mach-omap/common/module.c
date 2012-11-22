/*
 *
 * @Component			OMAPCONF
 * @Filename			module.c
 * @Description			OMAP Generic Module Definitions & APIs
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


#include <module.h>
#include <lib.h>
#include <string.h>
#include <module44xx.h>
#include <module54xx.h>
#include <cpuinfo.h>
#include <opp.h>


/* #define MODULE_DEBUG */
#ifdef MODULE_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void mod_init(void)
{
	#ifdef MODULE_DEBUG
	int i, j, count, count_opp;
	const genlist *mod_list;
	mod_info mod;
	mod_opp opp;
	#endif

	if (cpu_is_omap44xx()) {
		mod44xx_init();
	} else if (cpu_is_omap54xx()) {
		mod54xx_init();
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
	}

	#ifdef MODULE_DEBUG
	mod_list = mod_list_get();
	count = genlist_getcount((genlist *) mod_list);
	printf("Module List:\n");
	for (i = 0; i < count; i++) {
		genlist_get((genlist *) mod_list, i, (mod_info *) &mod);
		printf(" %s:\n", mod.name);
		printf("  ID:%d\n", mod.id);
		printf("  ClkDM: %s\n", mod.clkdm);
		printf("  PwrDM: %s\n", mod.pwrdm);
		printf("  VoltDM: %s\n", mod.voltdm);
		printf("  F-Clk:%d\n", mod.clk);
		printf("  SYSCONFIG REG: %s\n", (mod.sysconfig)->name);
		printf("  CLKCTRL REG: %s\n", (mod.clkctrl)->name);
		printf("  CONTEXT REG: %s\n", (mod.context)->name);
		printf("  Properties: %d\n", mod.properties);
		printf("  OPP List: ");
		count_opp = genlist_getcount((genlist *) &(mod.mod_opp_list));
		for (j = 0; j < count_opp; j++) {
			genlist_get(&(mod.mod_opp_list), j,
				(mod_opp *) &opp);
			printf("(%s, %dKHz) ", opp.name, opp.rate);
		}
		printf("\n\n");
	}
	printf("Module count: %d\n\n", count);
	#endif
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_deinit
 * @BRIEF		free dynamically allocated internal data.
 * @DESCRIPTION		free dynamically allocated internal data.
 *			MUST BE CALLED AT END OF EXECUTION.
 *//*------------------------------------------------------------------------ */
void mod_deinit(void)
{
	if (cpu_is_omap44xx()) {
		mod44xx_deinit();
	} else if (cpu_is_omap54xx()) {
		mod54xx_deinit();
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_list_get
 * @BRIEF		return the list of modules
 * @RETURNS		list of modules in case of success
 *			NULL in case of error
 * @DESCRIPTION		return the list of modules
 *//*------------------------------------------------------------------------ */
const genlist *mod_list_get(void)
{
	if (cpu_is_omap44xx()) {
		return mod44xx_list_get();
	} else if (cpu_is_omap54xx()) {
		return mod54xx_list_get();
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		return NULL;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_count_get
 * @BRIEF		return the number of modules
 * @RETURNS		number of modules (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @DESCRIPTION		return the number of modules
 *//*------------------------------------------------------------------------ */
int mod_count_get(void)
{
	if (cpu_is_omap44xx()) {
		return mod44xx_count_get();
	} else if (cpu_is_omap54xx()) {
		return mod54xx_count_get();
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		return OMAPCONF_ERR_CPU;
	}
}
