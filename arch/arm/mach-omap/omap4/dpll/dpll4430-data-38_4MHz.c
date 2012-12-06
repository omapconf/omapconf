/*
 *
 * @Component			OMAPCONF
 * @Filename			dpll4430-data-38_4MHz.c
 * @Description			OMAP4430 DPLL Golden Settings
 *				(with 38.4MHz system clock)
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


const dpll44xx_audit_settings dpll4430_MPU_golden_settings_38_4MHz_dpll_casc = {
	.status = DPLL_STATUS_BYPASSED,
	.mode = DPLL_LOW_POWER_BYPASS,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.lpmode = 0,
	.regm4xen = 0,
	.dcc_en = 0,
	.dcc_count = 2.5,
	.M = -1,
	.N = -1,
	.fdpll = -1,
	.M2 = 1,
	.M2_clkout_rate = 196.608,
	.X2_M2_clkdcoldo_rate = 196.608,
	.M3 = -1,
	.X2_M3_rate = -1,
	.hsdiv_present = {-1, -1, -1, -1},
	.hsdiv = {-1, -1, -1, -1},
	.hsdiv_rate = {-1, -1, -1, -1} };

const dpll44xx_audit_settings dpll4430_MPU_golden_settings_38_4MHz_opp50 = {
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.lpmode = 0,
	.regm4xen = 0,
	.dcc_en = 0,
	.dcc_count = 2.5,
	.M = 125,
	.N = 7,
	.fdpll = 1200,
	.M2 = 2,
	.M2_clkout_rate = 300,
	.X2_M2_clkdcoldo_rate = 600,
	.M3 = -1,
	.X2_M3_rate = -1,
	.hsdiv_present = {-1, -1, -1, -1},
	.hsdiv = {-1, -1, -1, -1},
	.hsdiv_rate = {-1, -1, -1, -1} };

const dpll44xx_audit_settings dpll4430_MPU_golden_settings_38_4MHz_opp100 = {
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.lpmode = 0,
	.regm4xen = 0,
	.dcc_en = 0,
	.dcc_count = 2.5,
	.M = 125,
	.N = 7,
	.fdpll = 1200,
	.M2 = 1,
	.M2_clkout_rate = 600,
	.X2_M2_clkdcoldo_rate = 1200,
	.M3 = -1,
	.X2_M3_rate = -1,
	.hsdiv_present = {-1, -1, -1, -1},
	.hsdiv = {-1, -1, -1, -1},
	.hsdiv_rate = {-1, -1, -1, -1} };

const dpll44xx_audit_settings dpll4430_MPU_golden_settings_38_4MHz_opp_turbo = {
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.lpmode = 0,
	.regm4xen = 0,
	.dcc_en = 0,
	.dcc_count = 2.5,
	.M = 125,
	.N = 5,
	.fdpll = 1600,
	.M2 = 1,
	.M2_clkout_rate = 800,
	.X2_M2_clkdcoldo_rate = 1600,
	.M3 = -1,
	.X2_M3_rate = -1,
	.hsdiv_present = {-1, -1, -1, -1},
	.hsdiv = {-1, -1, -1, -1},
	.hsdiv_rate = {-1, -1, -1, -1} };

const dpll44xx_audit_settings dpll4430_MPU_golden_settings_38_4MHz_opp_nitro = {
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.lpmode = 0,
	.regm4xen = 0,
	.dcc_en = 0,
	.dcc_count = 2.5,
	.M = 625,
	.N = 23,
	.fdpll = 2000,
	.M2 = 1,
	.M2_clkout_rate = 1000,
	.X2_M2_clkdcoldo_rate = 2000,
	.M3 = -1,
	.X2_M3_rate = -1,
	.hsdiv_present = {-1, -1, -1, -1},
	.hsdiv = {-1, -1, -1, -1},
	.hsdiv_rate = {-1, -1, -1, -1} };

const dpll44xx_audit_settings dpll4430_MPU_golden_settings_38_4MHz_opp_nitrosb = {
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.lpmode = 0,
	.regm4xen = 0,
	.dcc_en = 0,
	.dcc_count = 2.5,
	.M = 125,
	.N = 3,
	.fdpll = 2400,
	.M2 = 1,
	.M2_clkout_rate = 1200,
	.X2_M2_clkdcoldo_rate = 2400,
	.M3 = -1,
	.X2_M3_rate = -1,
	.hsdiv_present = {-1, -1, -1, -1},
	.hsdiv = {-1, -1, -1, -1},
	.hsdiv_rate = {-1, -1, -1, -1} };

const dpll44xx_audit_settings
	*dpll4430_MPU_golden_settings_38_4MHz[OPP44XX_ID_MAX] = {
	&dpll4430_MPU_golden_settings_38_4MHz_dpll_casc,
	&dpll4430_MPU_golden_settings_38_4MHz_opp50,
	&dpll4430_MPU_golden_settings_38_4MHz_opp100,
	&dpll4430_MPU_golden_settings_38_4MHz_opp_turbo,
	&dpll4430_MPU_golden_settings_38_4MHz_opp_nitro,
	&dpll4430_MPU_golden_settings_38_4MHz_opp_nitrosb};


const dpll44xx_audit_settings dpll4430_IVA_golden_settings_38_4MHz_dpll_casc = {
	.status = DPLL_STATUS_BYPASSED,
	.mode = DPLL_LOW_POWER_BYPASS,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.lpmode = 0,
	.regm4xen = 0,
	.dcc_en = 0,
	.dcc_count = 2.5,
	.M = -1,
	.N = -1,
	.fdpll = -1,
	.M2 = -1,
	.M2_clkout_rate = -1,
	.X2_M2_clkdcoldo_rate = -1,
	.M3 = -1,
	.X2_M3_rate = -1,
	.hsdiv_present = {1, 1, -1, -1},
	.hsdiv = {-1, -1, -1, -1},
	.hsdiv_rate = {98.304, 98.304, -1, -1} };


const dpll44xx_audit_settings dpll4430_IVA_golden_settings_38_4MHz_opp50 = {
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.lpmode = 0,
	.regm4xen = 0,
	.dcc_en = 0,
	.dcc_count = 2.5,
	.M = 291,
	.N = 11,
	.fdpll = 1862.4,
	.M2 = -1,
	.M2_clkout_rate = -1,
	.X2_M2_clkdcoldo_rate = -1,
	.M3 = -1,
	.X2_M3_rate = -1,
	.hsdiv_present = {1, 1, -1, -1},
	.hsdiv = {8, 14, -1, -1},
	.hsdiv_rate = {232.8, 133, -1, -1} };

const dpll44xx_audit_settings dpll4430_IVA_golden_settings_38_4MHz_opp100 = {
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.lpmode = 0,
	.regm4xen = 0,
	.dcc_en = 0,
	.dcc_count = 2.5,
	.M = 291,
	.N = 11,
	.fdpll = 1862.4,
	.M2 = -1,
	.M2_clkout_rate = -1,
	.X2_M2_clkdcoldo_rate = -1,
	.M3 = -1,
	.X2_M3_rate = -1,
	.hsdiv_present = {1, 1, -1, -1},
	.hsdiv = {4, 7, -1, -1},
	.hsdiv_rate = {465.6, 266.1, -1, -1} };

const dpll44xx_audit_settings dpll4430_IVA_golden_settings_38_4MHz_opp_turbo = {
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.lpmode = 0,
	.regm4xen = 0,
	.dcc_en = 0,
	.dcc_count = 2.5,
	.M = 155,
	.N = 11,
	.fdpll = 992,
	.M2 = -1,
	.M2_clkout_rate = -1,
	.X2_M2_clkdcoldo_rate = -1,
	.M3 = -1,
	.X2_M3_rate = -1,
	.hsdiv_present = {1, 1, -1, -1},
	.hsdiv = {2, 3, -1, -1},
	.hsdiv_rate = {496, 330.7, -1, -1} };

const dpll44xx_audit_settings
	*dpll4430_IVA_golden_settings_38_4MHz[OPP44XX_ID_MAX] = {
	&dpll4430_IVA_golden_settings_38_4MHz_dpll_casc,
	&dpll4430_IVA_golden_settings_38_4MHz_opp50,
	&dpll4430_IVA_golden_settings_38_4MHz_opp100,
	&dpll4430_IVA_golden_settings_38_4MHz_opp_turbo,
	(dpll44xx_audit_settings *) NULL,
	(dpll44xx_audit_settings *) NULL};


const dpll44xx_audit_settings dpll4430_CORE_golden_settings_38_4MHz_dpll_casc = {
	.status = DPLL_STATUS_BYPASSED,
	.mode = DPLL_LOW_POWER_BYPASS,
	.autoidle_mode = DPLL_DISABLED,
	.lpmode = 0,
	.regm4xen = 0,
	.dcc_en = 0,
	.dcc_count = 2.5,
	.M = -1,
	.N = -1,
	.fdpll = -1,
	.M2 = -1,
	.M2_clkout_rate = 196.608,
	.X2_M2_clkdcoldo_rate = 196.608,
	.M3 = 8,
	.X2_M3_rate = 24.576,
	.hsdiv_present = {1, 1, 1, 1},
	.hsdiv = {-1, -1, -1, -1},
	.hsdiv_rate = {196.608, 196.608, 196.608, 196.608} };

const dpll44xx_audit_settings dpll4430_CORE_golden_settings_38_4MHz_opp50 = {
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.lpmode = 0,
	.regm4xen = 0,
	.dcc_en = 0,
	.dcc_count = 2.5,
	.M = 125,
	.N = 5,
	.fdpll = 1600,
	.M2 = 2,
	.M2_clkout_rate = 400,
	.X2_M2_clkdcoldo_rate = 800,
	.M3 = 8,
	.X2_M3_rate = 200,
	.hsdiv_present = {1, 1, 1, 1},
	.hsdiv = {8, 8, 8, 12},
	.hsdiv_rate = {200, 200, 200, 133.3} };

const dpll44xx_audit_settings dpll4430_CORE_golden_settings_38_4MHz_opp100 = {
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.lpmode = 0,
	.regm4xen = 0,
	.dcc_en = 0,
	.dcc_count = 2.5,
	.M = 125,
	.N = 5,
	.fdpll = 1600,
	.M2 = 1,
	.M2_clkout_rate = 800,
	.X2_M2_clkdcoldo_rate = 1600,
	.M3 = 5,
	.X2_M3_rate = 320,
	.hsdiv_present = {1, 1, 1, 1},
	.hsdiv = {8, 4, 6, 6},
	.hsdiv_rate = {200, 400, 266.7, 266.7} };

const dpll44xx_audit_settings
	*dpll4430_CORE_golden_settings_38_4MHz[OPP44XX_ID_MAX] = {
	&dpll4430_CORE_golden_settings_38_4MHz_dpll_casc,
	&dpll4430_CORE_golden_settings_38_4MHz_opp50,
	&dpll4430_CORE_golden_settings_38_4MHz_opp100,
	(dpll44xx_audit_settings *) NULL,
	(dpll44xx_audit_settings *) NULL,
	(dpll44xx_audit_settings *) NULL};


const dpll44xx_audit_settings dpll4430_PER_golden_settings_38_4MHz_dpll_casc = {
	.status = DPLL_STATUS_BYPASSED,
	.mode = DPLL_LOW_POWER_BYPASS,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.lpmode = 0,
	.regm4xen = 0,
	.dcc_en = 0,
	.dcc_count = 2.5,
	.M = -1,
	.N = -1,
	.fdpll = -1,
	.M2 = -1,
	.M2_clkout_rate = 98.304,
	.X2_M2_clkdcoldo_rate = 98.304,
	.M3 = 8,
	.X2_M3_rate = 0, /* 24.576MHz but output is gated */
	.hsdiv_present = {1, 1, 1, 1},
	.hsdiv = {-1, -1, -1, -1},
	.hsdiv_rate = {98.304, 98.304, 98.304, 98.304} };

const dpll44xx_audit_settings dpll4430_PER_golden_settings_38_4MHz_opp50 = {
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.lpmode = 0,
	.regm4xen = 0,
	.dcc_en = 0,
	.dcc_count = 2.5,
	.M = 40,
	.N = 1,
	.fdpll = 1536,
	.M2 = 8,
	.M2_clkout_rate = 96,
	.X2_M2_clkdcoldo_rate = 192,
	.M3 = 8,
	.X2_M3_rate = 192,
	.hsdiv_present = {1, 1, 1, 1},
	.hsdiv = {12, 9, 8, 10},
	.hsdiv_rate = {128, 170.7, 192, 153.6} };

const dpll44xx_audit_settings dpll4430_PER_golden_settings_38_4MHz_opp100 = {
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.lpmode = 0,
	.regm4xen = 0,
	.dcc_en = 0,
	.dcc_count = 2.5,
	.M = 40,
	.N = 1,
	.fdpll = 1536,
	.M2 = 8,
	.M2_clkout_rate = 96,
	.X2_M2_clkdcoldo_rate = 192,
	.M3 = 6,
	.X2_M3_rate = 256,
	.hsdiv_present = {1, 1, 1, 1},
	.hsdiv = {12, 9, 4, 5},
	.hsdiv_rate = {128, 170.7, 384, 307.2} };

const dpll44xx_audit_settings
	*dpll4430_PER_golden_settings_38_4MHz[OPP44XX_ID_MAX] = {
	&dpll4430_PER_golden_settings_38_4MHz_dpll_casc,
	&dpll4430_PER_golden_settings_38_4MHz_opp50,
	&dpll4430_PER_golden_settings_38_4MHz_opp100,
	(dpll44xx_audit_settings *) NULL,
	(dpll44xx_audit_settings *) NULL,
	(dpll44xx_audit_settings *) NULL};


const dpll44xx_audit_settings dpll4430_ABE_golden_settings_38_4MHz_dpll_casc = {
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_DISABLED,
	.lpmode = 1,
	.regm4xen = 1,
	.dcc_en = 0,
	.dcc_count = 2.5,
	.M = 750,
	.N = 0,
	.fdpll = 196.608,
	.M2 = 1,
	.M2_clkout_rate = 98.304,
	.X2_M2_clkdcoldo_rate = 196.608,
	.M3 = 1,
	.X2_M3_rate = 196.608,
	.hsdiv_present = {-1, -1, -1, -1},
	.hsdiv = {-1, -1, -1, -1},
	.hsdiv_rate = {-1, -1, -1, -1} };

const dpll44xx_audit_settings dpll4430_ABE_golden_settings_38_4MHz_all_opp = {
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.lpmode = 1,
	.regm4xen = 1,
	.dcc_en = 0,
	.dcc_count = 2.5,
	.M = 750,
	.N = 0,
	.fdpll = 196.608,
	.M2 = 1,
	.M2_clkout_rate = 98.304,
	.X2_M2_clkdcoldo_rate = 196.608,
	.M3 = 1,
	.X2_M3_rate = 196.608,
	.hsdiv_present = {-1, -1, -1, -1},
	.hsdiv = {-1, -1, -1, -1},
	.hsdiv_rate = {-1, -1, -1, -1} };

const dpll44xx_audit_settings
	*dpll4430_ABE_golden_settings_38_4MHz[OPP44XX_ID_MAX] = {
	&dpll4430_ABE_golden_settings_38_4MHz_dpll_casc,
	&dpll4430_ABE_golden_settings_38_4MHz_all_opp,
	&dpll4430_ABE_golden_settings_38_4MHz_all_opp,
	&dpll4430_ABE_golden_settings_38_4MHz_all_opp,
	&dpll4430_ABE_golden_settings_38_4MHz_all_opp,
	&dpll4430_ABE_golden_settings_38_4MHz_all_opp};


const dpll44xx_audit_settings dpll4430_USB_golden_settings_38_4MHz_dpll_casc = {
	.status = DPLL_STATUS_STOPPED,
	.mode = DPLL_LOW_POWER_STOP,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.lpmode = 0,
	.regm4xen = 0,
	.dcc_en = 0,
	.dcc_count = 2.5,
	.M = -1,
	.N = -1,
	.fdpll = -1,
	.M2 = -1,
	.M2_clkout_rate = -1,
	.X2_M2_clkdcoldo_rate = -1,
	.M3 = -1,
	.X2_M3_rate = -1,
	.hsdiv_present = {-1, -1, -1, -1},
	.hsdiv = {-1, -1, -1, -1},
	.hsdiv_rate = {-1, -1, -1, -1} };

const dpll44xx_audit_settings dpll4430_USB_golden_settings_38_4MHz_all_opp = {
	.status = DPLL_STATUS_LOCKED,
	.mode = DPLL_LOCK,
	.autoidle_mode = DPLL_AUTO_LOW_POWER_STOP,
	.lpmode = 0,
	.regm4xen = 0,
	.dcc_en = 0,
	.dcc_count = 2.5,
	.M = 400,
	.N = 15,
	.fdpll = 960,
	.M2 = 2,
	.M2_clkout_rate = 480,
	.X2_M2_clkdcoldo_rate = 960,
	.M3 = -1,
	.X2_M3_rate = -1,
	.hsdiv_present = {-1, -1, -1, -1},
	.hsdiv = {-1, -1, -1, -1},
	.hsdiv_rate = {-1, -1, -1, -1} };


const dpll44xx_audit_settings
	*dpll4430_USB_golden_settings_38_4MHz[OPP44XX_ID_MAX] = {
	&dpll4430_USB_golden_settings_38_4MHz_dpll_casc,
	&dpll4430_USB_golden_settings_38_4MHz_all_opp,
	&dpll4430_USB_golden_settings_38_4MHz_all_opp,
	&dpll4430_USB_golden_settings_38_4MHz_all_opp,
	&dpll4430_USB_golden_settings_38_4MHz_all_opp,
	&dpll4430_USB_golden_settings_38_4MHz_all_opp};


const dpll44xx_audit_settings **dpll4430_golden_settings_38_4MHz[DPLL44XX_ID_MAX] = {
	(const dpll44xx_audit_settings **) &dpll4430_MPU_golden_settings_38_4MHz,
	(const dpll44xx_audit_settings **) &dpll4430_IVA_golden_settings_38_4MHz,
	(const dpll44xx_audit_settings **) &dpll4430_CORE_golden_settings_38_4MHz,
	(const dpll44xx_audit_settings **) &dpll4430_PER_golden_settings_38_4MHz,
	(const dpll44xx_audit_settings **) &dpll4430_ABE_golden_settings_38_4MHz,
	(const dpll44xx_audit_settings **) &dpll4430_USB_golden_settings_38_4MHz,
	(const dpll44xx_audit_settings **) NULL,
	(const dpll44xx_audit_settings **) NULL};
