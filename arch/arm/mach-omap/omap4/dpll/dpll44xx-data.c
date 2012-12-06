/*
 *
 * @Component			OMAPCONF
 * @Filename			dpll44xx-data.c
 * @Description			OMAP4 DPLL Definitions
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


#include <dpll44xx-data.h>
#include <cm44xx.h>
#include <cpuinfo.h>
#include <string.h>


reg_table dpll44xx_prcm_reg_table[80];
static unsigned int dpll44xx_prcm_reg_table_init_done = 0;


const char dpll44xx_names[DPLL44XX_ID_MAX + 1][DPLL_MAX_NAME_LENGTH] = {
	"DPLL_MPU",
	"DPLL_IVA",
	"DPLL_CORE",
	"DPLL_PER",
	"DPLL_ABE",
	"DPLL_USB",
	"DPLL_UNIPRO",
	"DPLL_DDRPHY",
	"FIXME"};


const char dpll44xx_output_names[DPLL44XX_OUTPUT_ID_MAX + 1][DPLL_OUTPUT_MAX_NAME_LENGTH] = {
	"CLKOUT_M2",
	"CLKOUTX2_M2",
	"CLKOUTX2_M3",
	"CLKOUTX2_M4",
	"CLKOUTX2_M5",
	"CLKOUTX2_M6",
	"CLKOUTX2_M7",
	"CLK_DCO_LDO",
	"FIXME"};


const omap4_dpll_MN_params_regs omap4_dpll_MN_regs[DPLL44XX_ID_MAX] = {
	{OMAP4430_CM_CLKSEL_DPLL_MPU, OMAP4430_CM_DIV_M2_DPLL_MPU, 0},
	{OMAP4430_CM_CLKSEL_DPLL_IVA, 0, 0},
	{OMAP4430_CM_CLKSEL_DPLL_CORE, OMAP4430_CM_DIV_M2_DPLL_CORE, OMAP4430_CM_DIV_M3_DPLL_CORE},
	{OMAP4430_CM_CLKSEL_DPLL_PER, OMAP4430_CM_DIV_M2_DPLL_PER, OMAP4430_CM_DIV_M3_DPLL_PER},
	{OMAP4430_CM_CLKSEL_DPLL_ABE, OMAP4430_CM_DIV_M2_DPLL_ABE, OMAP4430_CM_DIV_M3_DPLL_ABE},
	{OMAP4430_CM_CLKSEL_DPLL_USB, OMAP4430_CM_DIV_M2_DPLL_USB, 0},
	{OMAP4430_CM_CLKSEL_DPLL_UNIPRO, OMAP4430_CM_DIV_M2_DPLL_UNIPRO, 0},
	{OMAP4430_CM_CLKSEL_DPLL_DDRPHY, OMAP4430_CM_DIV_M2_DPLL_DDRPHY, 0}
};


const unsigned int omap4_dpll_hs_divider_regs[DPLL44XX_ID_MAX][4] = {
	{0, 0, 0, 0},
	{OMAP4430_CM_DIV_M4_DPLL_IVA, OMAP4430_CM_DIV_M5_DPLL_IVA, 0, 0},
	{OMAP4430_CM_DIV_M4_DPLL_CORE, OMAP4430_CM_DIV_M5_DPLL_CORE, OMAP4430_CM_DIV_M6_DPLL_CORE, OMAP4430_CM_DIV_M7_DPLL_CORE},
	{OMAP4430_CM_DIV_M4_DPLL_PER, OMAP4430_CM_DIV_M5_DPLL_PER, OMAP4430_CM_DIV_M6_DPLL_PER, OMAP4430_CM_DIV_M7_DPLL_PER},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{OMAP4430_CM_DIV_M4_DPLL_DDRPHY, OMAP4430_CM_DIV_M5_DPLL_DDRPHY, OMAP4430_CM_DIV_M6_DPLL_DDRPHY, 0}
};


const omap4_dpll_params_regs omap4_dpll_regs[DPLL44XX_ID_MAX] = {
	{OMAP4430_CM_CLKMODE_DPLL_MPU, OMAP4430_CM_IDLEST_DPLL_MPU, OMAP4430_CM_AUTOIDLE_DPLL_MPU, OMAP4430_CM_CLKSEL_DPLL_MPU, OMAP4430_CM_BYPCLK_DPLL_MPU, OMAP4430_CM_DIV_M2_DPLL_MPU, 0},
	{OMAP4430_CM_CLKMODE_DPLL_IVA, OMAP4430_CM_IDLEST_DPLL_IVA, OMAP4430_CM_AUTOIDLE_DPLL_IVA, OMAP4430_CM_CLKSEL_DPLL_IVA, OMAP4430_CM_BYPCLK_DPLL_IVA, 0, 0},
	{OMAP4430_CM_CLKMODE_DPLL_CORE, OMAP4430_CM_IDLEST_DPLL_CORE, OMAP4430_CM_AUTOIDLE_DPLL_CORE, OMAP4430_CM_CLKSEL_DPLL_CORE, 0, OMAP4430_CM_DIV_M2_DPLL_CORE, OMAP4430_CM_DIV_M3_DPLL_CORE},
	{OMAP4430_CM_CLKMODE_DPLL_PER, OMAP4430_CM_IDLEST_DPLL_PER, OMAP4430_CM_AUTOIDLE_DPLL_PER, OMAP4430_CM_CLKSEL_DPLL_PER, 0, OMAP4430_CM_DIV_M2_DPLL_PER, OMAP4430_CM_DIV_M3_DPLL_PER},
	{OMAP4430_CM_CLKMODE_DPLL_ABE, OMAP4430_CM_IDLEST_DPLL_ABE, OMAP4430_CM_AUTOIDLE_DPLL_ABE, OMAP4430_CM_CLKSEL_DPLL_ABE, 0, OMAP4430_CM_DIV_M2_DPLL_ABE, OMAP4430_CM_DIV_M3_DPLL_ABE},
	{OMAP4430_CM_CLKMODE_DPLL_USB, OMAP4430_CM_IDLEST_DPLL_USB, OMAP4430_CM_AUTOIDLE_DPLL_USB, OMAP4430_CM_CLKSEL_DPLL_USB, 0, OMAP4430_CM_DIV_M2_DPLL_USB, 0},
	{OMAP4430_CM_CLKMODE_DPLL_UNIPRO, OMAP4430_CM_IDLEST_DPLL_UNIPRO, OMAP4430_CM_AUTOIDLE_DPLL_UNIPRO, OMAP4430_CM_CLKSEL_DPLL_UNIPRO, 0, OMAP4430_CM_DIV_M2_DPLL_UNIPRO, 0},
	{OMAP4430_CM_CLKMODE_DPLL_DDRPHY, OMAP4430_CM_IDLEST_DPLL_DDRPHY, OMAP4430_CM_AUTOIDLE_DPLL_DDRPHY, OMAP4430_CM_CLKSEL_DPLL_DDRPHY, 0, OMAP4430_CM_DIV_M2_DPLL_DDRPHY, 0},
};


const omap4_dpll_clock_sources omap4_dpll_sources[DPLL44XX_ID_MAX] = {
	{OMAP4_MPU_DPLL_ALWON_CLK, OMAP4_MPU_DPLL_HS_CLK, OMAP4_CLOCK_ID_MAX, OMAP4_CLOCK_ID_MAX},
	{OMAP4_IVA_DPLL_ALWON_CLK, OMAP4_IVA_DPLL_HS_CLK, OMAP4_CLOCK_ID_MAX, OMAP4_IVA_HSD_BYP_CLK},
	{OMAP4_CORE_DPLL_ALWON_CLK, OMAP4_CORE_DPLL_HS_CLK, OMAP4_CORE_DPLL_HS_CLK, OMAP4_CORE_PHY_HSD_BYP_CLK},
	{OMAP4_PER_DPLL_ALWON_CLK, OMAP4_PER_DPLL_HS_CLK, OMAP4_CLOCK_ID_MAX, OMAP4_PER_HSD_BYP_CLK},
	{OMAP4_ABE_DPLL_ALWON_CLK, OMAP4_ABE_DPLL_BYPASS_CLK, OMAP4_CLOCK_ID_MAX, OMAP4_CLOCK_ID_MAX},
	{OMAP4_L3INIT_DPLL_ALWON_CLK, OMAP4_USB_DPLL_HS_CLK, OMAP4_CLOCK_ID_MAX, OMAP4_CLOCK_ID_MAX},
	{OMAP4_L3INIT_DPLL_ALWON_CLK, OMAP4_CLOCK_ID_MAX, OMAP4_CLOCK_ID_MAX, OMAP4_CLOCK_ID_MAX},
	{OMAP4_CLOCK_ID_MAX, OMAP4_CLOCK_ID_MAX, OMAP4_CLOCK_ID_MAX, OMAP4_CLOCK_ID_MAX} };



/**
 * Function: dpll44xx_init_regtable
 * Role: initialize .addr field of reg_table (not possible statically)
 * Parameters:
 *	none
 * Return:
 *	0
 *	OMAPCONF_ERR_CPU
 */
int dpll44xx_init_regtable(void)
{
	unsigned int i = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (dpll44xx_prcm_reg_table_init_done == 1)
		return 0;

	/* Init DPLLs registers table */
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_CLKMODE_DPLL_CORE;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_CLKMODE_DPLL_CORE");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_IDLEST_DPLL_CORE;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_IDLEST_DPLL_CORE");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_AUTOIDLE_DPLL_CORE;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_AUTOIDLE_DPLL_CORE");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_CLKSEL_DPLL_CORE;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_CLKSEL_DPLL_CORE");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_DIV_M2_DPLL_CORE;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_DIV_M2_DPLL_CORE");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_DIV_M3_DPLL_CORE;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_DIV_M3_DPLL_CORE");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_DIV_M4_DPLL_CORE;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_DIV_M4_DPLL_CORE");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_DIV_M5_DPLL_CORE;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_DIV_M5_DPLL_CORE");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_DIV_M6_DPLL_CORE;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_DIV_M6_DPLL_CORE");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_DIV_M7_DPLL_CORE;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_DIV_M7_DPLL_CORE");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_SSC_DELTAMSTEP_DPLL_CORE;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_SSC_DELTAMSTEP_DPLL_CORE");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_SSC_MODFREQDIV_DPLL_CORE;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_SSC_MODFREQDIV_DPLL_CORE");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_EMU_OVERRIDE_DPLL_CORE;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_EMU_OVERRIDE_DPLL_CORE");

	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_CLKMODE_DPLL_PER;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_CLKMODE_DPLL_PER");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_IDLEST_DPLL_PER;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_IDLEST_DPLL_PER");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_AUTOIDLE_DPLL_PER;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_AUTOIDLE_DPLL_PER");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_CLKSEL_DPLL_PER;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_CLKSEL_DPLL_PER");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_DIV_M2_DPLL_PER;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_DIV_M2_DPLL_PER");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_DIV_M3_DPLL_PER;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_DIV_M3_DPLL_PER");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_DIV_M4_DPLL_PER;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_DIV_M4_DPLL_PER");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_DIV_M5_DPLL_PER;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_DIV_M5_DPLL_PER");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_DIV_M6_DPLL_PER;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_DIV_M6_DPLL_PER");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_DIV_M7_DPLL_PER;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_DIV_M7_DPLL_PER");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_SSC_DELTAMSTEP_DPLL_PER;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_SSC_DELTAMSTEP_DPLL_PER");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_SSC_MODFREQDIV_DPLL_PER;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_SSC_MODFREQDIV_DPLL_PER");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_EMU_OVERRIDE_DPLL_PER;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_EMU_OVERRIDE_DPLL_PER");

	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_CLKMODE_DPLL_MPU;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_CLKMODE_DPLL_MPU");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_IDLEST_DPLL_MPU;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_IDLEST_DPLL_MPU");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_AUTOIDLE_DPLL_MPU;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_AUTOIDLE_DPLL_MPU");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_CLKSEL_DPLL_MPU;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_CLKSEL_DPLL_MPU");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_DIV_M2_DPLL_MPU;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_DIV_M2_DPLL_MPU");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_SSC_DELTAMSTEP_DPLL_MPU;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_SSC_DELTAMSTEP_DPLL_MPU");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_SSC_MODFREQDIV_DPLL_MPU;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_SSC_MODFREQDIV_DPLL_MPU");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_BYPCLK_DPLL_MPU;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_BYPCLK_DPLL_MPU");

	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_CLKMODE_DPLL_IVA;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_CLKMODE_DPLL_IVA");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_IDLEST_DPLL_IVA;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_IDLEST_DPLL_IVA");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_AUTOIDLE_DPLL_IVA;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_AUTOIDLE_DPLL_IVA");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_CLKSEL_DPLL_IVA;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_CLKSEL_DPLL_IVA");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_DIV_M4_DPLL_IVA;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_DIV_M4_DPLL_IVA");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_DIV_M5_DPLL_IVA;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_DIV_M5_DPLL_IVA");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_SSC_DELTAMSTEP_DPLL_IVA;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_SSC_DELTAMSTEP_DPLL_IVA");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_SSC_MODFREQDIV_DPLL_IVA;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_SSC_MODFREQDIV_DPLL_IVA");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_BYPCLK_DPLL_IVA;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_BYPCLK_DPLL_IVA");

	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_CLKMODE_DPLL_ABE;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_CLKMODE_DPLL_ABE");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_IDLEST_DPLL_ABE;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_IDLEST_DPLL_ABE");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_AUTOIDLE_DPLL_ABE;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_AUTOIDLE_DPLL_ABE");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_CLKSEL_DPLL_ABE;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_CLKSEL_DPLL_ABE");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_DIV_M2_DPLL_ABE;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_DIV_M2_DPLL_ABE");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_DIV_M3_DPLL_ABE;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_DIV_M3_DPLL_ABE");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_SSC_DELTAMSTEP_DPLL_ABE;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_SSC_DELTAMSTEP_DPLL_ABE");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_SSC_MODFREQDIV_DPLL_ABE;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_SSC_MODFREQDIV_DPLL_ABE");

	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_CLKMODE_DPLL_USB;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_CLKMODE_DPLL_USB");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_IDLEST_DPLL_USB;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_IDLEST_DPLL_USB");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_AUTOIDLE_DPLL_USB;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_AUTOIDLE_DPLL_USB");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_CLKSEL_DPLL_USB;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_CLKSEL_DPLL_USB");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_DIV_M2_DPLL_USB;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_DIV_M2_DPLL_USB");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_SSC_DELTAMSTEP_DPLL_USB;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_SSC_DELTAMSTEP_DPLL_USB");
	dpll44xx_prcm_reg_table[i].addr = OMAP4430_CM_SSC_MODFREQDIV_DPLL_USB;
	strcpy(dpll44xx_prcm_reg_table[i++].name, "CM_SSC_MODFREQDIV_DPLL_USB");

	if (cpu_is_omap4430() && (cpu_revision_get() == REV_ES1_0)) {
		dpll44xx_prcm_reg_table[i].addr =
			OMAP4430_CM_CLKMODE_DPLL_UNIPRO;
		strcpy(dpll44xx_prcm_reg_table[i++].name,
			"CM_CLKMODE_DPLL_UNIPRO");
		dpll44xx_prcm_reg_table[i].addr =
			OMAP4430_CM_IDLEST_DPLL_UNIPRO;
		strcpy(dpll44xx_prcm_reg_table[i++].name,
			"CM_IDLEST_DPLL_UNIPRO");
		dpll44xx_prcm_reg_table[i].addr =
			OMAP4430_CM_AUTOIDLE_DPLL_UNIPRO;
		strcpy(dpll44xx_prcm_reg_table[i++].name,
			"CM_AUTOIDLE_DPLL_UNIPRO");
		dpll44xx_prcm_reg_table[i].addr =
			OMAP4430_CM_CLKSEL_DPLL_UNIPRO;
		strcpy(dpll44xx_prcm_reg_table[i++].name,
			"CM_CLKSEL_DPLL_UNIPRO");
		dpll44xx_prcm_reg_table[i].addr =
			OMAP4430_CM_DIV_M2_DPLL_UNIPRO;
		strcpy(dpll44xx_prcm_reg_table[i++].name,
			"CM_DIV_M2_DPLL_UNIPRO");
		dpll44xx_prcm_reg_table[i].addr =
			OMAP4430_CM_SSC_DELTAMSTEP_DPLL_UNIPRO;
		strcpy(dpll44xx_prcm_reg_table[i++].name,
			"CM_SSC_DELTAMSTEP_DPLL_UNIPRO");
		dpll44xx_prcm_reg_table[i].addr =
			OMAP4430_CM_SSC_MODFREQDIV_DPLL_UNIPRO;
		strcpy(dpll44xx_prcm_reg_table[i++].name,
			"CM_SSC_MODFREQDIV_DPLL_UNIPRO");

		dpll44xx_prcm_reg_table[i].addr =
			OMAP4430_CM_CLKMODE_DPLL_DDRPHY;
		strcpy(dpll44xx_prcm_reg_table[i++].name,
			"CM_CLKMODE_DPLL_DDRPHY");
		dpll44xx_prcm_reg_table[i].addr =
			OMAP4430_CM_IDLEST_DPLL_DDRPHY;
		strcpy(dpll44xx_prcm_reg_table[i++].name,
			"CM_IDLEST_DPLL_DDRPHY");
		dpll44xx_prcm_reg_table[i].addr =
			OMAP4430_CM_AUTOIDLE_DPLL_DDRPHY;
		strcpy(dpll44xx_prcm_reg_table[i++].name,
			"CM_AUTOIDLE_DPLL_DDRPHY");
		dpll44xx_prcm_reg_table[i].addr =
			OMAP4430_CM_CLKSEL_DPLL_DDRPHY;
		strcpy(dpll44xx_prcm_reg_table[i++].name,
			"CM_CLKSEL_DPLL_DDRPHY");
		dpll44xx_prcm_reg_table[i].addr =
			OMAP4430_CM_DIV_M2_DPLL_DDRPHY;
		strcpy(dpll44xx_prcm_reg_table[i++].name,
			"CM_DIV_M2_DPLL_DDRPHY");
		dpll44xx_prcm_reg_table[i].addr =
			OMAP4430_CM_DIV_M4_DPLL_DDRPHY;
		strcpy(dpll44xx_prcm_reg_table[i++].name,
			"CM_DIV_M4_DPLL_DDRPHY");
		dpll44xx_prcm_reg_table[i].addr =
			OMAP4430_CM_DIV_M5_DPLL_DDRPHY;
		strcpy(dpll44xx_prcm_reg_table[i++].name,
			"CM_DIV_M5_DPLL_DDRPHY");
		dpll44xx_prcm_reg_table[i].addr =
			OMAP4430_CM_DIV_M6_DPLL_DDRPHY;
		strcpy(dpll44xx_prcm_reg_table[i++].name,
			"CM_DIV_M6_DPLL_DDRPHY");
		dpll44xx_prcm_reg_table[i].addr =
			OMAP4430_CM_SSC_DELTAMSTEP_DPLL_DDRPHY;
		strcpy(dpll44xx_prcm_reg_table[i++].name,
			"CM_SSC_DELTAMSTEP_DPLL_DDRPHY");
		dpll44xx_prcm_reg_table[i].addr =
			OMAP4430_CM_SSC_MODFREQDIV_DPLL_DDRPHY;
		strcpy(dpll44xx_prcm_reg_table[i++].name,
			"CM_SSC_MODFREQDIV_DPLL_DDRPHY");
	}
	dpll44xx_prcm_reg_table[i].addr = 0;
	strcpy(dpll44xx_prcm_reg_table[i].name, "END");

	dpll44xx_prcm_reg_table_init_done = 1;
	return 0;
}
