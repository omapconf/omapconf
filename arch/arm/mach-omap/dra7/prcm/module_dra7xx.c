/*
 *
 * @Component			OMAPCONF
 * @Filename			module_dra7xx.c
 * @Description			DRA7 Module Definitions & APIs
 * @Author			Jin Zheng (j-zheng@ti.com)
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


#include <module_dra7xx.h>
#include <lib.h>
#include <string.h>
#include <stdio.h>
#include <cpuinfo.h>
#include <cm_dra7xx-defs.h>
#include <prm_dra7xx-defs.h>
#include <voltdm_dra7xx.h>
#include <module.h>
#include <clockdomain.h>
#include <powerdomain.h>
#include <voltdomain.h>
#include <opp.h>


/* #define MODULE_DRA7XX_DEBUG */
#ifdef MODULE_DRA7XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static unsigned short mod_dra7xx_init_done;
genlist mod_dra7xx_list;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_dra7xx_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void mod_dra7xx_init(void)
{
	mod_info mod;
	mod_opp opp;

	if (mod_dra7xx_init_done)
		return;

	genlist_init(&mod_dra7xx_list);

	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = CD_L4_CFG */
	mod.name = MOD_L4_CFG_INTERCONNECT;
	mod.id = (int) DRA7_L4_CFG_INTERCONNECT;
	mod.clkdm = NULL;/* TBD */
	mod.pwrdm = NULL;/* TBD */
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK_DRA7XX_L4CFG_L4_GICLK;
	mod.sysconfig = NULL;
	mod.clkctrl = &dra7xx_core_cm_core_cm_l4cfg_l4_cfg_clkctrl;
	mod.context = &dra7xx_core_prm_rm_l4cfg_l4_cfg_context;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_NOM;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_OD;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;/* TBD */
	genlist_addtail(&mod_dra7xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = CD_EMIF */
	mod.name = MOD_DMM;
	mod.id = (int) DRA7_DMM;
	mod.clkdm = NULL;/* TBD */
	mod.pwrdm = NULL;/* TBD */
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK_DRA7XX_EMIF_L3_GICLK;
	mod.sysconfig = NULL;
	mod.clkctrl = &dra7xx_core_cm_core_cm_emif_dmm_clkctrl;
	mod.context = &dra7xx_core_prm_rm_emif_dmm_context;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_NOM;
	opp.rate = 266000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_OD;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;/* TBD */
	genlist_addtail(&mod_dra7xx_list, (void *) &mod, sizeof(mod_info));

	mod.name = MOD_EMIF1;
	mod.id = (int) DRA7_EMIF1;
	mod.clkdm = NULL;/* TBD */
	mod.pwrdm = NULL;/* TBD */
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK_DRA7XX_EMIF_L3_GICLK;
	mod.sysconfig = NULL;
	mod.clkctrl = &dra7xx_core_cm_core_cm_emif_emif1_clkctrl;
	mod.context = &dra7xx_core_prm_rm_emif_emif1_context;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_NOM;
	opp.rate = 266000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_OD;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;/* TBD */
	genlist_addtail(&mod_dra7xx_list, (void *) &mod, sizeof(mod_info));

	mod.name = MOD_EMIF2;
	mod.id = (int) DRA7_EMIF2;
	mod.clkdm = NULL;/* TBD */
	mod.pwrdm = NULL;/* TBD */
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK_DRA7XX_EMIF_L3_GICLK;
	mod.sysconfig = NULL;
	mod.clkctrl = &dra7xx_core_cm_core_cm_emif_emif2_clkctrl;
	mod.context = &dra7xx_core_prm_rm_emif_emif2_context;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_NOM;
	opp.rate = 266000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_OD;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;/* TBD */
	genlist_addtail(&mod_dra7xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = CD_L3_MAIN1 */
	mod.name = MOD_L3_MAIN1_INTERCONNECT;
	mod.id = (int) DRA7_L3_MAIN1_INTERCONNECT;
	mod.clkdm = NULL;/* TBD */
	mod.pwrdm = NULL;/* TBD */
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK_DRA7XX_L3MAIN1_L3_GICLK;
	mod.sysconfig = NULL;
	mod.clkctrl = &dra7xx_core_cm_core_cm_l3main1_l3_main_1_clkctrl;
	mod.context = &dra7xx_core_prm_rm_l3main1_l3_main_1_context;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_NOM;
	opp.rate = 266000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_OD;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;/* TBD */
	genlist_addtail(&mod_dra7xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: PD_CORE, Clock domain = CD_CORE */
	mod.name = MOD_IPU2;
	mod.id = (int) DRA7_IPU2;
	mod.clkdm = NULL;/* TBD */
	mod.pwrdm = NULL;/* TBD */
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK_DRA7XX_IPU2_GFCLK;
	mod.sysconfig = NULL;
	mod.clkctrl = &dra7xx_core_cm_core_cm_ipu2_ipu2_clkctrl;
	mod.context = &dra7xx_core_prm_rm_ipu2_ipu2_context;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_NOM;
	opp.rate = 425000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_OD;
	opp.rate = 425000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;/* TBD */
	genlist_addtail(&mod_dra7xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: PD_IPU, Clock domain = CD_IPU1 */
	mod.name = MOD_IPU1;
	mod.id = (int) DRA7_IPU1;
	mod.clkdm = NULL;/* TBD */
	mod.pwrdm = NULL;/* TBD */
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK_DRA7XX_IPU1_GFCLK;
	mod.sysconfig = NULL;
	mod.clkctrl = &dra7xx_ipu_cm_core_aon_cm_ipu1_ipu1_clkctrl;
	mod.context = &dra7xx_ipu_prm_rm_ipu1_ipu1_context;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_NOM;
	opp.rate = 425000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_OD;
	opp.rate = 425000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;/* TBD */
	genlist_addtail(&mod_dra7xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: PD_DSS, Clock domain = CD_DSS */
	mod.name = MOD_BB2D;
	mod.id = (int) DRA7_BB2D;
	mod.clkdm = NULL;/* TBD */
	mod.pwrdm = NULL;/* TBD */
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK_DRA7XX_BB2D_GFCLK;
	mod.sysconfig = NULL;
	mod.clkctrl = &dra7xx_dss_cm_core_cm_dss_bb2d_clkctrl;
	mod.context = &dra7xx_dss_prm_rm_dss_bb2d_context;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_NOM;
	opp.rate = 354600;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_OD;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;/* TBD */
	genlist_addtail(&mod_dra7xx_list, (void *) &mod, sizeof(mod_info));

	mod.name = MOD_DSS;
	mod.id = (int) DRA7_DSS;
	mod.clkdm = NULL;/* TBD */
	mod.pwrdm = NULL;/* TBD */
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK_DRA7XX_DSS_GFCLK;
	mod.sysconfig = NULL;
	mod.clkctrl = &dra7xx_dss_cm_core_cm_dss_dss_clkctrl;
	mod.context = &dra7xx_dss_prm_rm_dss_dss_context;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_NOM;
	opp.rate = 192000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_OD;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;/* TBD */
	genlist_addtail(&mod_dra7xx_list, (void *) &mod, sizeof(mod_info));



	/* Voltage dom.: IVAHD, Power dom.: PD_IVA, Clock domain = CD_IVA */
	mod.name = MOD_IVAHD;
	mod.id = (int) DRA7_IVAHD;
	mod.clkdm = NULL;/* TBD */
	mod.pwrdm = NULL;/* TBD */
	mod.voltdm = VDD_IVA;
	mod.clk = (int) CLK_DRA7XX_IVA_GCLK;
	mod.sysconfig = NULL;
	mod.clkctrl = &dra7xx_iva_cm_core_cm_iva_iva_clkctrl;
	mod.context = &dra7xx_iva_prm_rm_iva_iva_context;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_NOM;
	opp.rate = 388300;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_OD;
	opp.rate = 430000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = 532000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS;
	genlist_addtail(&mod_dra7xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: DSPEVE, Power dom.: PD_DSP1, Clock domain = CD_DSP1 */
	mod.name = MOD_DSP1;
	mod.id = (int) DRA7_DSP1;
	mod.clkdm = NULL;/* TBD */
	mod.pwrdm = NULL;/* TBD */
	mod.voltdm = VDD_DSPEVE;
	mod.clk = (int) CLK_DRA7XX_DSP_GFCLK;
	mod.sysconfig = NULL;/* TBD */
	mod.clkctrl = &dra7xx_dsp1_cm_core_aon_cm_dsp1_dsp1_clkctrl;
	mod.context = &dra7xx_dsp1_prm_rm_dsp1_dsp1_context;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_NOM;
	opp.rate = 600000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_OD;
	opp.rate = 700000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = 750000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS;
	genlist_addtail(&mod_dra7xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: DSPEVE, Power dom.: PD_DSP2, Clock domain = CD_DSP2 */
	mod.name = MOD_DSP2;
	mod.id = (int) DRA7_DSP2;
	mod.clkdm = NULL;/* TBD */
	mod.pwrdm = NULL;/* TBD */
	mod.voltdm = VDD_DSPEVE;
	mod.clk = (int) CLK_DRA7XX_DSP_GFCLK;
	mod.sysconfig = NULL;/* TBD */
	mod.clkctrl = &dra7xx_dsp2_cm_core_aon_cm_dsp2_dsp2_clkctrl;
	mod.context = &dra7xx_dsp2_prm_rm_dsp2_dsp2_context;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_NOM;
	opp.rate = 600000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_OD;
	opp.rate = 700000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = 750000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS;
	genlist_addtail(&mod_dra7xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: DSPEVE, Power dom.: PD_EVE1, Clock domain = CD_EVE1 */
	mod.name = MOD_EVE1;
	mod.id = (int) DRA7_EVE1;
	mod.clkdm = NULL;/* TBD */
	mod.pwrdm = NULL;/* TBD */
	mod.voltdm = VDD_DSPEVE;
	mod.clk = (int) CLK_DRA7XX_EVE_CLK;
	mod.sysconfig = NULL;/* TBD */
	mod.clkctrl = &dra7xx_eve1_cm_core_aon_cm_eve1_eve1_clkctrl;
	mod.context = &dra7xx_eve1_prm_rm_eve1_eve1_context;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_NOM;
	opp.rate = 535000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_OD;
	opp.rate = 650000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = 650000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS/* TBD */;
	genlist_addtail(&mod_dra7xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: DSPEVE, Power dom.: PD_EVE2, Clock domain = CD_EVE2 */
	mod.name = MOD_EVE2;
	mod.id = (int) DRA7_EVE2;
	mod.clkdm = NULL;/* TBD */
	mod.pwrdm = NULL;/* TBD */
	mod.voltdm = VDD_DSPEVE;
	mod.clk = (int) CLK_DRA7XX_EVE_CLK;
	mod.sysconfig = NULL;/* TBD */
	mod.clkctrl = &dra7xx_eve2_cm_core_aon_cm_eve2_eve2_clkctrl;
	mod.context = &dra7xx_eve2_prm_rm_eve2_eve2_context;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_NOM;
	opp.rate = 535000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_OD;
	opp.rate = 650000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = 650000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS/* TBD */;
	genlist_addtail(&mod_dra7xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: GPU, Power dom.: PD_GPU, Clock domain = CD_GPU */
	mod.name = MOD_GPU;
	mod.id = (int) DRA7_GPU;
	mod.clkdm = NULL;/* TBD */
	mod.pwrdm = NULL;/* TBD */
	mod.voltdm = VDD_GPU;
	mod.clk = (int) CLK_DRA7XX_GPU_GCLK;
	mod.sysconfig = NULL;/* TBD */
	mod.clkctrl = &dra7xx_gpu_cm_core_cm_gpu_gpu_clkctrl;
	mod.context = &dra7xx_gpu_prm_rm_gpu_gpu_context;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_NOM;
	opp.rate = 425600;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_OD;
	opp.rate = 500000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = 532000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS/* TBD */;
	genlist_addtail(&mod_dra7xx_list, (void *) &mod, sizeof(mod_info));


	/* Voltage dom.: MPU, Power dom.: PD_MPUAON, Clock domain = CD_MPUAON */
	mod.name = MOD_MPU;
	mod.id = (int) DRA7_DPLL_MPU;
	mod.clkdm = NULL;/* TBD */
	mod.pwrdm = NULL;/* TBD */
	mod.voltdm = VDD_MPU;
	mod.clk = (int) CLK_DRA7XX_MPU_GCLK;
	mod.sysconfig = NULL;
	mod.clkctrl = &dra7xx_mpu_cm_core_aon_cm_mpu_mpu_clkctrl;
	mod.context = &dra7xx_mpu_prm_rm_mpu_mpu_context;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_NOM;
	opp.rate = 1000000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_OD;
	opp.rate = 1176000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = 1500000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS;
	genlist_addtail(&mod_dra7xx_list, (void *) &mod, sizeof(mod_info));

	mod_dra7xx_init_done = 1;

	dprintf("%s(): init done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_dra7xx_deinit
 * @BRIEF		free dynamically allocated internal data.
 * @DESCRIPTION		free dynamically allocated internal data.
 *			MUST BE CALLED AT END OF EXECUTION.
 *//*------------------------------------------------------------------------ */
void mod_dra7xx_deinit(void)
{
	int i, count;
	mod_info mod;

	if (mod_dra7xx_init_done) {
		count = genlist_getcount(&mod_dra7xx_list);
		for (i = 0; i < count; i++) {
			genlist_get(&mod_dra7xx_list, i, (mod_info *) &mod);
			genlist_free(&(mod.mod_opp_list));
		}
		genlist_free(&mod_dra7xx_list);
		mod_dra7xx_init_done = 0;
	}
	dprintf("%s(): deinit done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_dra7xx_list_get
 * @BRIEF		return the list of modules
 * @RETURNS		list of modules in case of success
 *			NULL in case of error
 * @DESCRIPTION		return the list of modules
 *//*------------------------------------------------------------------------ */
const genlist *mod_dra7xx_list_get(void)
{
	mod_dra7xx_init();

	return (const genlist *) &mod_dra7xx_list;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_dra7xx_count_get
 * @BRIEF		return the number of modules
 * @RETURNS		number of modules (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @DESCRIPTION		return the number of modules
 *//*------------------------------------------------------------------------ */
int mod_dra7xx_count_get(void)
{
	int count;

	mod_dra7xx_init();

	count = genlist_getcount(&mod_dra7xx_list);

	dprintf("%s() = %d\n", __func__, count);
	return count;
}
