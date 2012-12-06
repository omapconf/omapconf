/*
 *
 * @Component			OMAPCONF
 * @Filename			dpll54xx-data-38_4MHz.c
 * @Description			OMAP5 DPLL Golden Settings (with 38.4MHz system clock)
 * @Author			Patrick Titiano (p-titiano@ti.com)
 * @Date			2011
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
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


#include <dpll54xx-data.h>
#include <clock54xx.h>


dpll54xx_audited_settings dpll54xx_MPU_golden_settings_38_4MHz_dpll_casc = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_BYPASSED,
	.mode = DPLL_LOW_POWER_BYPASS,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = -1.0,
	.M = -1,
	.N = -1,
	.fdpll = -1.0,
	.M2 = -1,
	.M2_rate = 196.608,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = -1,
	.M3 = -1,
	.X2_M3_rate = -1.0,
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	/* OMAP5 ONLY */
	.hsdiv_div = {-1, -1, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0} };


dpll54xx_audited_settings dpll54xx_MPU_golden_settings_38_4MHz_opp_low = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = 38.4,
	.M = 375,
	.N = 17,
	.fdpll = 1600,
	.M2 = 2,
	.M2_rate = 400,
	/* DPLL type A only */
	.dcc_en = 1,
	.regm4xen = 0,
	.X2_M2_rate = -1,
	.M3 = -1,
	.X2_M3_rate = -1.0,
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	/* OMAP5 ONLY */
	.hsdiv_div = {-1, -1, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0} };


dpll54xx_audited_settings dpll54xx_MPU_golden_settings_38_4MHz_opp_nom = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = 38.4,
	.M = 375,
	.N = 17,
	.fdpll = 1600,
	.M2 = 1,
	.M2_rate = 800,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = -1,
	.M3 = -1,
	.X2_M3_rate = -1.0,
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	/* OMAP5 ONLY */
	.hsdiv_div = {-1, -1, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0} };


dpll54xx_audited_settings dpll54xx_MPU_golden_settings_38_4MHz_opp_high = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = 38.4,
	.M = 1375,
	.N = 47,
	.fdpll = 1100,
	.M2 = 1,
	.M2_rate = 1100,
	/* DPLL type A only */
	.dcc_en = 1,
	.regm4xen = 0,
	.X2_M2_rate = -1,
	.M3 = -1,
	.X2_M3_rate = -1.0,
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	/* OMAP5 ONLY */
	.hsdiv_div = {-1, -1, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0} };


dpll54xx_audited_settings dpll54xx_MPU_golden_settings_38_4MHz_opp_speedbin = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = 38.4,
	.M = 125,
	.N = 3,
	.fdpll = 1200,
	.M2 = 1,
	.M2_rate = 1200,
	/* DPLL type A only */
	.dcc_en = 1,
	.regm4xen = 0,
	.X2_M2_rate = -1,
	.M3 = -1,
	.X2_M3_rate = -1.0,
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	/* OMAP5 ONLY */
	.hsdiv_div = {-1, -1, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0} };


dpll54xx_audited_settings dpll54xx_IVA_golden_settings_38_4MHz_dpll_casc = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_BYPASSED,
	.mode = DPLL_LOW_POWER_BYPASS,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = -1.0,
	.M = -1,
	.N = -1,
	.fdpll = -1.0,
	.M2 = -1,
	.M2_rate = -1,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = -1,
	.M3 = -1,
	.X2_M3_rate = -1.0,
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	/* OMAP5 ONLY */
	.hsdiv_div = {-1, -1, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0} };


dpll54xx_audited_settings dpll54xx_IVA_golden_settings_38_4MHz_opp_low = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = 38.4,
	.M = 1972,
	.N = 64,
	.fdpll = 2330.0,
	.M2 = -1,
	.M2_rate = -1,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = -1,
	.M3 = -1,
	.X2_M3_rate = -1.0,
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	/* OMAP5 ONLY */
	.hsdiv_div = {10, 12, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {233.0, 194.2, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0} };


dpll54xx_audited_settings dpll54xx_IVA_golden_settings_38_4MHz_opp_nom = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = 38.4,
	.M = 1972,
	.N = 64,
	.fdpll = 2330.0,
	.M2 = -1,
	.M2_rate = -1,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = -1,
	.M3 = -1,
	.X2_M3_rate = -1.0,
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	/* OMAP5 ONLY */
	.hsdiv_div = {5, 6, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {466.0, 388.3, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0} };


dpll54xx_audited_settings dpll54xx_IVA_golden_settings_38_4MHz_opp_high = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = 38.4,
	.M = 665,
	.N = 47,
	.fdpll = 1064.0,
	.M2 = -1,
	.M2_rate = -1,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = -1,
	.M3 = -1,
	.X2_M3_rate = -1.0,
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	/* OMAP5 ONLY */
	.hsdiv_div = {2, 2, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {532.0, 532.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0} };


dpll54xx_audited_settings dpll54xx_CORE_golden_settings_38_4MHz_dpll_casc = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_BYPASSED,
	.mode = DPLL_LOW_POWER_BYPASS,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = -1.0,
	.M = -1,
	.N = -1,
	.fdpll = -1.0,
	.M2 = -1,
	.M2_rate = 196.608,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = -1,
	.M3 = -1,
	.X2_M3_rate = 196.608,
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	/* OMAP5 ONLY */
	.hsdiv_div = {-1, -1, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {196.608, 196.608, 196.608, 196.608, -1.0, 196.608, 196.608, -1.0} };


dpll54xx_audited_settings dpll54xx_CORE_golden_settings_38_4MHz_opp_low = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = 38.4,
	.M = 665,
	.N = 23,
	.fdpll = 2128.0,
	.M2 = 4,
	.M2_rate = 266.0,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = -1,
	.M3 = 8,
	.X2_M3_rate = 266.0,
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	/* OMAP5 ONLY */
	.hsdiv_div = {8, 8, 62, 10, -1, 10, 14, -1},
	.hsdiv_rate = {266.0, 266.0, 34.3, 212.8, -1.0, 212.8, 152.0, -1.0} };


dpll54xx_audited_settings dpll54xx_CORE_golden_settings_38_4MHz_opp_nom = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = 38.4,
	.M = 665,
	.N = 23,
	.fdpll = 2128.0,
	.M2 = 2,
	.M2_rate = 532.0,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = -1,
	.M3 = 5,
	.X2_M3_rate = 425.6,
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	/* OMAP5 ONLY */
	.hsdiv_div = {8, 4, 62, 5, -1, 5, 7, -1},
	.hsdiv_rate = {266.0, 532.0, 34.3, 425.6, -1.0, 425.6, 304.0, -1.0} };


dpll54xx_audited_settings dpll54xx_PER_golden_settings_38_4MHz_dpll_casc = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_BYPASSED,
	.mode = DPLL_LOW_POWER_BYPASS,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = -1.0,
	.M = -1,
	.N = -1,
	.fdpll = -1.0,
	.M2 = -1,
	.M2_rate = -1,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = -1,
	.M3 = -1,
	.X2_M3_rate = -1.0,
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	/* OMAP5 ONLY */
	.hsdiv_div = {-1, -1, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0} };


dpll54xx_audited_settings dpll54xx_PER_golden_settings_38_4MHz_opp_low = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = 38.4,
	.M = 10,
	.N = 0,
	.fdpll = 768.0,
	.M2 = 4,
	.M2_rate = 96.0,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = 192.0,
	.M3 = 4,
	.X2_M3_rate = 192.0,
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	/* OMAP5 ONLY */
	.hsdiv_div = {6, 4, -1, 4, -1, -1, -1, -1},
	.hsdiv_rate = {128.0, 196.0, -1.0, 192.0, -1.0, -1.0, -1.0, -1.0} };


dpll54xx_audited_settings dpll54xx_PER_golden_settings_38_4MHz_opp_nom = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = 38.4,
	.M = 10,
	.N = 0,
	.fdpll = 768.0,
	.M2 = 4,
	.M2_rate = 96.0,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = 192.0,
	.M3 = 3,
	.X2_M3_rate = 256.0,
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	/* OMAP5 ONLY */
	.hsdiv_div = {6, 4, -1, 2, -1, -1, -1, -1},
	.hsdiv_rate = {128.0, 196.0, -1.0, 384.0, -1.0, -1.0, -1.0, -1.0} };


dpll54xx_audited_settings dpll54xx_ABE_golden_settings_38_4MHz_dpll_casc = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_DISABLED,
	.fref = 0.032768,
	.M = 750,
	.N = 0,
	.fdpll = 196.608,
	.M2 = 1,
	.M2_rate = 98.304,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 1,
	.X2_M2_rate = 196.608,
	.M3 = 1,
	.X2_M3_rate = 196.608,
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	/* OMAP5 ONLY */
	.hsdiv_div = {-1, -1, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0} };


dpll54xx_audited_settings dpll54xx_ABE_golden_settings_38_4MHz = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = 0.032768,
	.M = 750,
	.N = 0,
	.fdpll = 196.608,
	.M2 = 1,
	.M2_rate = 98.304,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 1,
	.X2_M2_rate = 196.608,
	.M3 = 1,
	.X2_M3_rate = 196.608,
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	/* OMAP5 ONLY */
	.hsdiv_div = {-1, -1, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0} };


dpll54xx_audited_settings dpll54xx_USB_golden_settings_38_4MHz_dpll_casc = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_STOPPED,
	.mode = DPLL_LOW_POWER_STOP,
	.autoidle_mode = DPLL_DISABLED,
	.fref = -1.0,
	.M = -1,
	.N = -1,
	.fdpll = -1.0,
	.M2 = -1,
	.M2_rate = -1,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = -1,
	.M3 = -1,
	.X2_M3_rate = -1.0,
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	/* OMAP5 ONLY */
	.hsdiv_div = {-1, -1, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0} };


dpll54xx_audited_settings dpll54xx_USB_golden_settings_38_4MHz = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = 38.4,
	.M = 400,
	.N = 15,
	.fdpll = 960.0,
	.M2 = 2,
	.M2_rate = 480,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = -1,
	.M3 = -1,
	.X2_M3_rate = -1.0,
	/* DPLL type B only */
	.sd_div = 1,
	.selfreqdco = 0,
	.clkdcoldo_rate = 960.0,
	/* OMAP5 ONLY */
	.hsdiv_div = {-1, -1, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0} };


dpll54xx_audited_settings dpll54xx_UNIPRO1_golden_settings_38_4MHz_dpll_casc = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_STOPPED,
	.mode = DPLL_LOW_POWER_STOP,
	.autoidle_mode = DPLL_DISABLED,
	.fref = -1.0,
	.M = -1,
	.N = -1,
	.fdpll = -1.0,
	.M2 = -1,
	.M2_rate = -1,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = -1,
	.M3 = -1,
	.X2_M3_rate = -1.0,
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	/* OMAP5 ONLY */
	.hsdiv_div = {-1, -1, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0} };


dpll54xx_audited_settings dpll54xx_UNIPRO1_golden_settings_38_4MHz = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = 38.4,
	.M = 520,
	.N = 15,
	.fdpll = 1248.0,
	.M2 = 4,
	.M2_rate = 312.0,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = -1,
	.M3 = -1,
	.X2_M3_rate = -1.0,
	/* DPLL type B only */
	.sd_div = 1,
	.selfreqdco = 0,
	.clkdcoldo_rate = 1248.0,
	/* OMAP5 ONLY */
	.hsdiv_div = {-1, -1, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0} };


dpll54xx_audited_settings dpll54xx_UNIPRO2_golden_settings_38_4MHz_dpll_casc = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_STOPPED,
	.mode = DPLL_LOW_POWER_STOP,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.fref = -1.0,
	.M = -1,
	.N = -1,
	.fdpll = -1.0,
	.M2 = -1,
	.M2_rate = -1,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = -1,
	.M3 = -1,
	.X2_M3_rate = -1.0,
	/* DPLL type B only */
	.sd_div = -1,
	.selfreqdco = -1,
	.clkdcoldo_rate = -1.0,
	/* OMAP5 ONLY */
	.hsdiv_div = {-1, -1, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0} };


dpll54xx_audited_settings dpll54xx_UNIPRO2_golden_settings_38_4MHz = {
	/* Common DPLL type A & B */
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOW_POWER_STOP,
	.autoidle_mode = DPLL_DISABLED,
	.fref = 38.4,
	.M = 911,
	.N = 23,
	.fdpll = 1457.6,
	.M2 = 4,
	.M2_rate = 364.4,
	/* DPLL type A only */
	.dcc_en = 0,
	.regm4xen = 0,
	.X2_M2_rate = -1,
	.M3 = -1,
	.X2_M3_rate = -1.0,
	/* DPLL type B only */
	.sd_div = 1,
	.selfreqdco = 1,
	.clkdcoldo_rate = 1457.6,
	/* OMAP5 ONLY */
	.hsdiv_div = {-1, -1, -1, -1, -1, -1, -1, -1},
	.hsdiv_rate = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0} };


dpll54xx_audited_settings *dpll54xx_golden_settings_38_4MHz_table[DPLL54XX_ID_MAX][OPP54XX_ID_MAX] = {
	{&dpll54xx_MPU_golden_settings_38_4MHz_dpll_casc,
		&dpll54xx_MPU_golden_settings_38_4MHz_opp_low,
		&dpll54xx_MPU_golden_settings_38_4MHz_opp_nom,
		&dpll54xx_MPU_golden_settings_38_4MHz_opp_high,
		&dpll54xx_MPU_golden_settings_38_4MHz_opp_speedbin},
	{&dpll54xx_IVA_golden_settings_38_4MHz_dpll_casc,
		&dpll54xx_IVA_golden_settings_38_4MHz_opp_low,
		&dpll54xx_IVA_golden_settings_38_4MHz_opp_nom,
		&dpll54xx_IVA_golden_settings_38_4MHz_opp_high,
		NULL},
	{&dpll54xx_CORE_golden_settings_38_4MHz_dpll_casc,
		&dpll54xx_CORE_golden_settings_38_4MHz_opp_low,
		&dpll54xx_CORE_golden_settings_38_4MHz_opp_nom,
		NULL,
		NULL},
	{&dpll54xx_PER_golden_settings_38_4MHz_dpll_casc,
		&dpll54xx_PER_golden_settings_38_4MHz_opp_low,
		&dpll54xx_PER_golden_settings_38_4MHz_opp_nom,
		NULL,
		NULL},
	{&dpll54xx_ABE_golden_settings_38_4MHz_dpll_casc,
		&dpll54xx_ABE_golden_settings_38_4MHz,
		&dpll54xx_ABE_golden_settings_38_4MHz,
		NULL,
		NULL},
	{&dpll54xx_USB_golden_settings_38_4MHz_dpll_casc,
		&dpll54xx_USB_golden_settings_38_4MHz,
		&dpll54xx_USB_golden_settings_38_4MHz,
		NULL,
		NULL},
	{&dpll54xx_UNIPRO1_golden_settings_38_4MHz_dpll_casc,
		&dpll54xx_UNIPRO1_golden_settings_38_4MHz,
		&dpll54xx_UNIPRO1_golden_settings_38_4MHz,
		NULL,
		NULL},
	{&dpll54xx_UNIPRO2_golden_settings_38_4MHz_dpll_casc,
		&dpll54xx_UNIPRO2_golden_settings_38_4MHz,
		&dpll54xx_UNIPRO2_golden_settings_38_4MHz,
		NULL,
		NULL} };
