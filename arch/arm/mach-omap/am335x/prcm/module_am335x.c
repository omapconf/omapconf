/*
 *
 * @Component			OMAPCONF
 * @Filename			module_am335x.c
 * @Description			AM335X Module Definitions & APIs
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


#include <clockdomain.h>
#include <cm_am335x-defs.h>
#include <cpuinfo.h>
#include <lib.h>
#include <module.h>
#include <module_am335x.h>
#include <opp.h>
#include <powerdomain.h>
#include <prm_am335x-defs.h>
#include <stdio.h>
#include <string.h>
#include <voltdm_am335x.h>
#include <voltdomain.h>


#ifdef MODULE_AM335X_DEBUG
#define dprintf(format, ...)	printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static unsigned short mod_am335x_init_done;
genlist mod_am335x_list;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_am335x_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void mod_am335x_init(void)
{
	mod_info mod;
	mod_opp opp;

	if (mod_am335x_init_done)
		return;

	genlist_init(&mod_am335x_list);

	/* Voltage dom.: CORE, Power dom.: PD_PER, Clock domain = PER_L3S */
	mod.name = MOD_L3_MAIN1_INTERCONNECT;
	mod.id = (int) AM335X_L3S;
	mod.clkdm = CLKDM_PER_L3S;
	mod.pwrdm = PWRDM_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK_AM335X_L3S_CLK;
	mod.sysconfig = NULL;
	mod.clkctrl = &am335x_cm_per_l3_clkctrl;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_50;
	opp.rate = 50000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100;
	opp.rate = 100000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_120;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_TURBO;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NITRO;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0; /* TBD */
	genlist_addtail(&mod_am335x_list, (void *) & mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: PD_PER, Clock domain = PER_L3 */
	mod.name = MOD_L3_MAIN2_INTERCONNECT;
	mod.id = (int) AM335X_L3F;
	mod.clkdm = CLKDM_PER_L3;
	mod.pwrdm = PWRDM_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK_AM335X_L3F_CLK;
	mod.sysconfig = NULL;
	mod.clkctrl = &am335x_cm_per_l3_clkctrl;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_50;
	opp.rate = 100000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100;
	opp.rate = 200000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_120;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_TURBO;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NITRO;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0; /* TBD */
	genlist_addtail(&mod_am335x_list, (void *) & mod, sizeof(mod_info));

	mod.name = MOD_EMIF4;
	mod.id = (int) AM335X_EMIF4;
	mod.clkdm = CLKDM_PER_L3;
	mod.pwrdm = PWRDM_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK_AM335X_EMIF_M_CLK;
	mod.sysconfig = NULL;
	mod.clkctrl = &am335x_cm_per_emif_clkctrl;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_50;
	opp.rate = 100000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100;
	opp.rate = 200000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_120;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_TURBO;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NITRO;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0; /* TBD */
	genlist_addtail(&mod_am335x_list, (void *) & mod, sizeof(mod_info));

	mod.name = MOD_PHY_EMIF;
	mod.id = (int) AM335X_DDR_PHY;
	mod.clkdm = CLKDM_PER_L3;
	mod.pwrdm = PWRDM_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK_AM335X_DDR_CLKOUTM2;
	mod.sysconfig = NULL;
	mod.clkctrl = NULL;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_50;
	opp.rate = 200000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100;
	opp.rate = 400000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_120;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_TURBO;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NITRO;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0; /* TBD */
	genlist_addtail(&mod_am335x_list, (void *) & mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: PD_PER, Clock domain = PER_L4LS */
	mod.name = MOD_L4_PER_INTERCONNECT;
	mod.id = (int) AM335X_L4_PER;
	mod.clkdm = CLKDM_PER_L4LS;
	mod.pwrdm = PWRDM_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK_AM335X_L4_PER_CLK;
	mod.sysconfig = NULL;
	mod.clkctrl = &am335x_cm_per_l4ls_clkctrl;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_50;
	opp.rate = 50000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100;
	opp.rate = 100000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_120;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_TURBO;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NITRO;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0; /* TBD */
	genlist_addtail(&mod_am335x_list, (void *) & mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: PD_PER, Clock domain = PER_L4HS */
	mod.name = MOD_L4_FAST_INTERCONNECT;
	mod.id = (int) AM335X_L4_FAST;
	mod.clkdm = CLKDM_PER_L4HS;
	mod.pwrdm = PWRDM_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK_AM335X_L4F_CLK;
	mod.sysconfig = NULL;
	mod.clkctrl = &am335x_cm_per_l4hs_clkctrl;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_50;
	opp.rate = 100000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100;
	opp.rate = 200000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_120;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_TURBO;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NITRO;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0; /* TBD */
	genlist_addtail(&mod_am335x_list, (void *) & mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: PD_WKUP, Clock domain = WKUP */
	mod.name = MOD_L4_WKUP_INTERCONNECT;
	mod.id = (int) AM335X_L4_WKUP;
	mod.clkdm = CLKDM_WKUP;
	mod.pwrdm = PWRDM_WKUP;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK_AM335X_L4_WKUPCLK;
	mod.sysconfig = NULL;
	mod.clkctrl = &am335x_cm_wkup_l4wkup_clkctrl;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_50;
	opp.rate = 50000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100;
	opp.rate = 100000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_120;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_TURBO;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NITRO;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod_am335x_list, (void *) & mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: PD_WKUP, Clock domain = WKUP_L3_AON */
	mod.name = MOD_DEBUGSS;
	mod.id = (int) AM335X_DEBUGSS;
	mod.clkdm = CLKDM_WKUP_L3_AON;
	mod.pwrdm = PWRDM_WKUP;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK_AM335X_DEBUGSS_CLKA;
	mod.sysconfig = NULL;
	mod.clkctrl = &am335x_cm_wkup_debugss_clkctrl;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_50;
	opp.rate = 100000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100;
	opp.rate = 200000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_120;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_TURBO;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NITRO;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS;
	genlist_addtail(&mod_am335x_list, (void *) & mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: PD_GFX, Clock domain = GFX_L3 */
	mod.name = MOD_GFX;
	mod.id = (int) AM335X_SGX530;
	mod.clkdm = CLKDM_GFX_L3;
	mod.pwrdm = PWRDM_GFX;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK_AM335X_GFX_SYSCLK;
	mod.sysconfig = NULL;
	mod.clkctrl = &am335x_cm_gfx_gfx_clkctrl;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_50;
	opp.rate = 100000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100;
	opp.rate = 200000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_120;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_TURBO;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NITRO;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS;
	genlist_addtail(&mod_am335x_list, (void *) & mod, sizeof(mod_info));

	/* Voltage dom.: MPU, Power dom.: PD_MPU, Clock domain = MPU */
	mod.name = MOD_MPU;
	mod.id = (int) AM335X_MPU;
	mod.clkdm = CLKDM_MPU;
	mod.pwrdm = PWRDM_MPU;
	mod.voltdm = VDD_MPU;
	mod.clk = (int) CLK_AM335X_MPU_CLK;
	mod.sysconfig = NULL;
	mod.clkctrl = &am335x_cm_mpu_mpu_clkctrl;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_50;
	opp.rate = 300000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100_LOW;
	opp.rate = 300000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100_HIGH;
	opp.rate = 600000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_120;
	opp.rate = 720000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_TURBO;
	opp.rate = 800000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NITRO;
	opp.rate = 1000000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0; /* TBD */
	genlist_addtail(&mod_am335x_list, (void *) & mod, sizeof(mod_info));

	mod_am335x_init_done = 1;

	dprintf("%s(): init done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_am335x_deinit
 * @BRIEF		free dynamically allocated internal data.
 * @DESCRIPTION		free dynamically allocated internal data.
 *			MUST BE CALLED AT END OF EXECUTION.
 *//*------------------------------------------------------------------------ */
void mod_am335x_deinit(void)
{
	int i, count;
	mod_info mod;

	if (mod_am335x_init_done) {
		count = genlist_getcount(&mod_am335x_list);
		for (i = 0; i < count; i++) {
			genlist_get(&mod_am335x_list, i, (mod_info *) &mod);
			genlist_free(&(mod.mod_opp_list));
		}
		genlist_free(&mod_am335x_list);
		mod_am335x_init_done = 0;
	}
	dprintf("%s(): deinit done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @ FUNCTION		mod_am335x_list_get
 * @ BRIEF		return the list of modules
 * @ RETURNS		list of modules in case of success
 *			NULL in case of error
 * @DESCRIPTION		return the list of modules
 *//*------------------------------------------------------------------------ */
const genlist *mod_am335x_list_get(void)
{
	mod_am335x_init();

	return (const genlist *) &mod_am335x_list;
}


/* ------------------------------------------------------------------------*//**
 * @ FUNCTION		mod_am335x_count_get
 * @ BRIEF		return the number of modules
 * @ RETURNS		number of modules (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @DESCRIPTION		return the number of modules
 *//*------------------------------------------------------------------------ */
int mod_am335x_count_get(void)
{
	int count;

	mod_am335x_init();

	count = genlist_getcount(&mod_am335x_list);

	dprintf("%s() = %d\n", __func__, count);
	return count;
}
