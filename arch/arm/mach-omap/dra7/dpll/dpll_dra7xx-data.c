/*
 *
 * @Component			OMAPCONF
 * @Filename			dpll_dra7xx-data.c
 * @Description			DRA7 DPLL Definitions
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


#include <dpll_dra7xx-data.h>
#include <clock_dra7xx.h>


const char dpll_dra7xx_names[DPLL_DRA7XX_ID_MAX][DPLL_MAX_NAME_LENGTH] = {
	[DPLL_DRA7XX_MPU] = "DPLL_MPU",
	[DPLL_DRA7XX_IVA] = "DPLL_IVA",
	[DPLL_DRA7XX_CORE] = "DPLL_CORE",
	[DPLL_DRA7XX_PER] = "DPLL_PER",
	[DPLL_DRA7XX_ABE] = "DPLL_ABE",
	[DPLL_DRA7XX_EVE] = "DPLL_EVE",
	[DPLL_DRA7XX_DSP] = "DPLL_DSP",
	[DPLL_DRA7XX_GMAC] = "DPLL_GMAC",
	[DPLL_DRA7XX_GPU] = "DPLL_GPU",
	[DPLL_DRA7XX_DDR] = "DPLL_DDR",
	[DPLL_DRA7XX_USB] = "DPLL_USB",
	[DPLL_DRA7XX_PCIE_REF] = "DPLL_PCIE_REF"};

const char dpll_dra7xx_strings[DPLL_DRA7XX_ID_MAX][DPLL_MAX_NAME_LENGTH] = {
	[DPLL_DRA7XX_MPU] = "mpu",
	[DPLL_DRA7XX_IVA] = "iva",
	[DPLL_DRA7XX_CORE] = "core",
	[DPLL_DRA7XX_PER] = "per",
	[DPLL_DRA7XX_ABE] = "abe",
	[DPLL_DRA7XX_EVE] = "eve",
	[DPLL_DRA7XX_DSP] = "dsp",
	[DPLL_DRA7XX_GMAC] = "gmac",
	[DPLL_DRA7XX_GPU] = "gpu",
	[DPLL_DRA7XX_DDR] = "ddr",
	[DPLL_DRA7XX_USB] = "usb",
	[DPLL_DRA7XX_PCIE_REF] = "pcieref"};

const char hsdiv_dra7xx_names[HSDIV_DRA7XX_ID_MAX][HSDIV_MAX_NAME_LENGTH] = {
	[HSDIV_DRA7XX_H11] = "H11",
	[HSDIV_DRA7XX_H12] = "H12",
	[HSDIV_DRA7XX_H13] = "H13",
	[HSDIV_DRA7XX_H14] = "H14",
	[HSDIV_DRA7XX_H21] = "H21",
	[HSDIV_DRA7XX_H22] = "H22",
	[HSDIV_DRA7XX_H23] = "H23",
	[HSDIV_DRA7XX_H24] = "H24" };


const char dpll_dra7xx_output_names[DPLL_DRA7XX_OUTPUT_ID_MAX][DPLL_OUTPUT_MAX_NAME_LENGTH] = {
	[DPLL_DRA7XX_CLKOUT_M2] = "CLKOUT_M2",
	[DPLL_DRA7XX_CLKOUTX2_M2] = "CLKOUTX2_M2",
	[DPLL_DRA7XX_CLKOUTX2_M3] = "CLKOUTX2_M3",
	[DPLL_DRA7XX_CLKOUTX2_H11] = "CLKOUTX2_H11",
	[DPLL_DRA7XX_CLKOUTX2_H12] = "CLKOUTX2_H12",
	[DPLL_DRA7XX_CLKOUTX2_H13] = "CLKOUTX2_H13",
	[DPLL_DRA7XX_CLKOUTX2_H14] = "CLKOUTX2_H14",
	[DPLL_DRA7XX_CLKOUTX2_H21] = "CLKOUTX2_H21",
	[DPLL_DRA7XX_CLKOUTX2_H22] = "CLKOUTX2_H22",
	[DPLL_DRA7XX_CLKOUTX2_H23] = "CLKOUTX2_H23",
	[DPLL_DRA7XX_CLKOUTX2_H24] = "CLKOUTX2_H24",
	[DPLL_DRA7XX_CLKOUTX2_M2_LDO] = "CLKOUTX2_M2_LDO",
	[DPLL_DRA7XX_CLK_DCO_LDO] = "CLK_DCO_LDO" };


const dpll_clk_sources
	dpll_dra7xx_sources[DPLL_DRA7XX_ID_MAX] = {
	[DPLL_DRA7XX_MPU] = {CLK_DRA7XX_MPU_DPLL_CLK,
		CLK_DRA7XX_MPU_DPLL_HS_CLK,
		CLK_DRA7XX_ID_MAX,
		CLK_DRA7XX_MPU_BYP_CLK_HMN},
	[DPLL_DRA7XX_IVA] = {CLK_DRA7XX_IVA_DPLL_CLK,
		CLK_DRA7XX_IVA_DPLL_HS_CLK,
		CLK_DRA7XX_ID_MAX,
		CLK_DRA7XX_IVA_BYP_CLK_HMN},
	[DPLL_DRA7XX_CORE] = {CLK_DRA7XX_CORE_DPLL_CLK,
		CLK_DRA7XX_CORE_DPLL_HS_CLK,
		CLK_DRA7XX_CORE_DPLL_HS_CLK,
		CLK_DRA7XX_CORE_BYP_CLK_HMN},
	[DPLL_DRA7XX_PER] = {CLK_DRA7XX_PER_DPLL_CLK,
		CLK_DRA7XX_PER_DPLL_HS_CLK,
		CLK_DRA7XX_ID_MAX,
		CLK_DRA7XX_PER_BYP_CLK_HMN},
	[DPLL_DRA7XX_ABE] = {CLK_DRA7XX_ABE_DPLL_CLK,
		CLK_DRA7XX_ABE_DPLL_BYPASS_CLK,
		CLK_DRA7XX_ID_MAX,
		CLK_DRA7XX_ABE_BYP_CLK_HMN},
	[DPLL_DRA7XX_EVE] = {CLK_DRA7XX_EVE_DPLL_CLK,
		CLK_DRA7XX_EVE_DPLL_HS_CLK,
		CLK_DRA7XX_ID_MAX,
		CLK_DRA7XX_EVE_BYP_CLK_HMN},
	[DPLL_DRA7XX_DSP] = {CLK_DRA7XX_DSP_DPLL_CLK,
		CLK_DRA7XX_DSP_DPLL_HS_CLK,
		CLK_DRA7XX_ID_MAX,
		CLK_DRA7XX_DSP_BYP_CLK_HMN},
	[DPLL_DRA7XX_GMAC] = {CLK_DRA7XX_GMAC_DPLL_CLK,
		CLK_DRA7XX_GMAC_DPLL_HS_CLK,
		CLK_DRA7XX_GMAC_DPLL_HS_CLK,
		CLK_DRA7XX_GMAC_BYP_CLK_HMN},
	[DPLL_DRA7XX_GPU] = {CLK_DRA7XX_GPU_DPLL_CLK,
		CLK_DRA7XX_GPU_DPLL_HS_CLK,
		CLK_DRA7XX_ID_MAX,
		CLK_DRA7XX_GPU_BYP_CLK_HMN},
	[DPLL_DRA7XX_DDR] = {CLK_DRA7XX_DDR_DPLL_CLK,
		CLK_DRA7XX_DDR_DPLL_HS_CLK,
		CLK_DRA7XX_ID_MAX,
		CLK_DRA7XX_DDR_BYP_CLK_HMN},
	[DPLL_DRA7XX_USB] = {CLK_DRA7XX_USB_DPLL_CLK,
		CLK_DRA7XX_USB_DPLL_HS_CLK,
		CLK_DRA7XX_ID_MAX,
		CLK_DRA7XX_USB_BYP_CLK_HMN},
	[DPLL_DRA7XX_PCIE_REF] = {CLK_DRA7XX_PCIE_DPLL_CLK,
		CLK_DRA7XX_ID_MAX,
		CLK_DRA7XX_ID_MAX,
		CLK_DRA7XX_PCIE_BYP_CLK_HMN} };


short dpll_dra7xx_ignore_m3[DPLL_DRA7XX_ID_MAX] = {
	[DPLL_DRA7XX_MPU] = 1,
	[DPLL_DRA7XX_IVA] = 1,
	[DPLL_DRA7XX_CORE] = 1,
	[DPLL_DRA7XX_PER] = 1,
	[DPLL_DRA7XX_ABE] = 0,
	[DPLL_DRA7XX_EVE] = 1,
	[DPLL_DRA7XX_DSP] = 0,
	[DPLL_DRA7XX_GMAC] = 0,
	[DPLL_DRA7XX_GPU] = 1,
	[DPLL_DRA7XX_DDR] = 1,
	[DPLL_DRA7XX_USB] = 1,
	[DPLL_DRA7XX_PCIE_REF] = 1};


dpll_dra7xx_audited_settings dpll_dra7xx_MPU_golden_settings_20MHz_opp_nom = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = 20.0,
	.M = 500,
	.N = 9,
	.fdpll = 2000.0,
	.M2 = 1,
	.M2_rate = 1000.0,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = -1.0,
	.M3 = -1,
	.X2_M3_rate = -1.0,
	.hsdiv_div = {-1, -1, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0},
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	.clkoutldo_rate = -1.0 };

dpll_dra7xx_audited_settings dpll_dra7xx_MPU_golden_settings_20MHz_opp_od = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = 20.0,
	.M = 294,
	.N = 4,
	.fdpll = 2352.0,
	.M2 = 1,
	.M2_rate = 1176.0,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = -1.0,
	.M3 = -1,
	.X2_M3_rate = -1.0,
	.hsdiv_div = {-1, -1, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0},
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	.clkoutldo_rate = -1.0 };

dpll_dra7xx_audited_settings dpll_dra7xx_MPU_golden_settings_20MHz_opp_high = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = 20.0,
	.M = 600,
	.N = 7,
	.fdpll = 1500.0,
	.M2 = 1,
	.M2_rate = 1500.0,
	/* DPLL type A only */
	.dcc_en = 1,
	.regm4xen = 0,
	.X2_M2_rate = -1.0,
	.M3 = -1,
	.X2_M3_rate = -1.0,
	.hsdiv_div = {-1, -1, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0},
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	.clkoutldo_rate = -1.0 };

dpll_dra7xx_audited_settings dpll_dra7xx_IVA_golden_settings_20MHz_opp_nom = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = 20.0,
	.M = 233,
	.N = 3,
	.fdpll = 2330.0,
	.M2 = 3,
	.M2_rate = 388.333,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = -1.0,
	.M3 = -1,
	.X2_M3_rate = -1.0,
	.hsdiv_div = {-1, -1, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0},
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	.clkoutldo_rate = -1.0 };

dpll_dra7xx_audited_settings dpll_dra7xx_CORE_golden_settings_20MHz_opp_nom = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = 20.0,
	.M = 266,
	.N = 4,
	.fdpll = 2128.0,
	.M2 = 2,
	.M2_rate = 532.0,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = -1.0,
	.M3 = -1,
	.X2_M3_rate = -1.0,
	.hsdiv_div = {1, 4, 62, 5, 1, 5, 4, 6},
	.hsdiv_rate = {2128, 532, 34, 425, 2128, 425, 532, 354},
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	.clkoutldo_rate = -1.0 };

dpll_dra7xx_audited_settings dpll_dra7xx_PER_golden_settings_20MHz_opp_nom = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = 20.0,
	.M = 96,
	.N = 4,
	.fdpll = 768.0,
	.M2 = 4,
	.M2_rate = 96.0,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = 192,
	.M3 = -1,
	.X2_M3_rate = -1.0,
	.hsdiv_div = {3, 4, 10, 2, -1, -1, -1, -1},
	.hsdiv_rate = {256, 192, 76, 384, -1.0, -1.0, -1.0, -1.0},
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	.clkoutldo_rate = -1.0 };

dpll_dra7xx_audited_settings dpll_dra7xx_ABE_golden_settings_20MHz_opp_nom = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = 22.5792,
	.M = 16,
	.N = 1,
	.fdpll = 361.2672,
	.M2 = 1,
	.M2_rate = 180.6336,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = 361.2672,
	.M3 = 1,
	.X2_M3_rate = 361.2672,
	.hsdiv_div = {-1, -1, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0},
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	.clkoutldo_rate = -1.0 };

dpll_dra7xx_audited_settings dpll_dra7xx_EVE_golden_settings_20MHz_opp_nom = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = 20.0,
	.M = 214,
	.N = 3,
	.fdpll = 2140.0,
	.M2 = 2,
	.M2_rate = 535.0,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = -1.0,
	.M3 = -1,
	.X2_M3_rate = -1.0,
	.hsdiv_div = {-1, -1, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0},
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	.clkoutldo_rate = -1.0 };

dpll_dra7xx_audited_settings dpll_dra7xx_DSP_golden_settings_20MHz_opp_nom = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = 20.0,
	.M = 150,
	.N = 4,
	.fdpll = 1200.0,
	.M2 = 1,
	.M2_rate = 600.0,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = -1.0,
	.M3 = 3,
	.X2_M3_rate = 400.0,
	.hsdiv_div = {-1, -1, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0},
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	.clkoutldo_rate = -1.0 };

dpll_dra7xx_audited_settings dpll_dra7xx_GMAC_golden_settings_20MHz_opp_nom = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = 20.0,
	.M = 250,
	.N = 4,
	.fdpll = 2000.0,
	.M2 = 4,
	.M2_rate = 250.0,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = -1.0,
	.M3 = 10,
	.X2_M3_rate = 200.0,
	.hsdiv_div = {40, 8, 10, 1, -1, -1, -1, -1},
	.hsdiv_rate = {50.0, 250.0, 200.0, 2000.0, -1.0, -1.0, -1.0, -1.0},
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	.clkoutldo_rate = -1.0 };

dpll_dra7xx_audited_settings dpll_dra7xx_GPU_golden_settings_20MHz_opp_nom = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = 20.0,
	.M = 170,
	.N = 3,
	.fdpll = 1700.0,
	.M2 = 2,
	.M2_rate = 425.0,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = -1.0,
	.M3 = -1,
	.X2_M3_rate = -1.0,
	.hsdiv_div = {-1, -1, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0},
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	.clkoutldo_rate = -1.0 };

dpll_dra7xx_audited_settings dpll_dra7xx_DDR_golden_settings_20MHz_opp_nom = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = 20.0,
	.M = 266,
	.N = 4,
	.fdpll = 2128.0,
	.M2 = 2,
	.M2_rate = 532.0,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = -1.0,
	.M3 = -1,
	.X2_M3_rate = -1.0,
	.hsdiv_div = {8, -1, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {266.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0},
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	.clkoutldo_rate = -1.0 };

dpll_dra7xx_audited_settings dpll_dra7xx_USB_golden_settings_20MHz_opp_nom = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = 20.0,
	.M = 480,
	.N = 9,
	.fdpll = 960.0,
	.M2 = 2,
	.M2_rate = 480.0,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = -1.0,
	.M3 = -1,
	.X2_M3_rate = -1.0,
	.hsdiv_div = {-1, -1, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0},
	/* DPLL type B only */
	.sd_div = 4,
	.selfreqdco = 0,
	.clkdcoldo_rate = 960.0,
	.clkoutldo_rate = -1.0 };

dpll_dra7xx_audited_settings dpll_dra7xx_PCIE_REF_golden_settings_20MHz_opp_nom = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = 20.0,
	.M = 750,
	.N = 9,
	.fdpll = 1500.0,
	.M2 = 15,
	.M2_rate = 100.0,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = -1.0,
	.M3 = -1,
	.X2_M3_rate = -1.0,
	.hsdiv_div = {-1, -1, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0},
	/* DPLL type B only */
	.sd_div = 6,
	.selfreqdco = 0,
	.clkdcoldo_rate = -1.0,
	.clkoutldo_rate = 0.0 };


dpll_dra7xx_audited_settings *dpll_dra7xx_golden_settings_20MHz_table[DPLL_DRA7XX_ID_MAX][OPP_DRA7XX_ID_MAX] = {
	[DPLL_DRA7XX_MPU] = {&dpll_dra7xx_MPU_golden_settings_20MHz_opp_nom,
		&dpll_dra7xx_MPU_golden_settings_20MHz_opp_od,
		&dpll_dra7xx_MPU_golden_settings_20MHz_opp_high},
	[DPLL_DRA7XX_IVA] = {&dpll_dra7xx_IVA_golden_settings_20MHz_opp_nom,
		NULL,
		NULL},
	[DPLL_DRA7XX_CORE] = {&dpll_dra7xx_CORE_golden_settings_20MHz_opp_nom,
		NULL,
		NULL},
	[DPLL_DRA7XX_PER] = {&dpll_dra7xx_PER_golden_settings_20MHz_opp_nom,
		NULL,
		NULL},
	[DPLL_DRA7XX_ABE] = {&dpll_dra7xx_ABE_golden_settings_20MHz_opp_nom,
		NULL,
		NULL},
	[DPLL_DRA7XX_EVE] = {&dpll_dra7xx_EVE_golden_settings_20MHz_opp_nom,
		NULL,
		NULL},
	[DPLL_DRA7XX_DSP] = {&dpll_dra7xx_DSP_golden_settings_20MHz_opp_nom,
		NULL,
		NULL},
	[DPLL_DRA7XX_GMAC] = {&dpll_dra7xx_GMAC_golden_settings_20MHz_opp_nom,
		NULL,
		NULL},
	[DPLL_DRA7XX_GPU] = {&dpll_dra7xx_GPU_golden_settings_20MHz_opp_nom,
		NULL,
		NULL},
	[DPLL_DRA7XX_DDR] = {&dpll_dra7xx_DDR_golden_settings_20MHz_opp_nom,
		NULL,
		NULL},
	[DPLL_DRA7XX_USB] = {&dpll_dra7xx_USB_golden_settings_20MHz_opp_nom,
		NULL,
		NULL},
	[DPLL_DRA7XX_PCIE_REF] = {&dpll_dra7xx_PCIE_REF_golden_settings_20MHz_opp_nom,
		NULL,
		NULL} };
