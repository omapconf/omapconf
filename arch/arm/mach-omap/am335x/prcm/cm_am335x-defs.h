/*
 *
 * @Component			OMAPCONF
 * @Filename			cm_am335x-defs.h
 * @Description			AM335X CM Register Definitions & Functions
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


#ifndef __CM_AM335X_DEFS_H__
#define __CM_AM335X_DEFS_H__


#include <dpll_am335x-defs.h>
#include <reg.h>

/* CM_PER Registers */
#define AM335X_CM_PER_L4LS_CLKSTCTRL				0x44E00000
extern reg am335x_cm_per_l4ls_clkstctrl;
#define AM335X_CM_PER_L3S_CLKSTCTRL				0x44E00004
extern reg am335x_cm_per_l3s_clkstctrl;
#define AM335X_CM_PER_L3_CLKSTCTRL				0x44E0000C
extern reg am335x_cm_per_l3_clkstctrl;
#define AM335X_CM_PER_CPGMAC0_CLKCTRL				0x44E00014
extern reg am335x_cm_per_cpgmac0_clkctrl;
#define AM335X_CM_PER_LCDC_CLKCTRL				0x44E00018
extern reg am335x_cm_per_lcdc_clkctrl;
#define AM335X_CM_PER_USB0_CLKCTRL				0x44E0001C
extern reg am335x_cm_per_usb0_clkctrl;
#define AM335X_CM_PER_TPTC0_CLKCTRL				0x44E00024
extern reg am335x_cm_per_tptc0_clkctrl;
#define AM335X_CM_PER_EMIF_CLKCTRL				0x44E00028
extern reg am335x_cm_per_emif_clkctrl;
#define AM335X_CM_PER_OCMCRAM_CLKCTRL				0x44E0002C
extern reg am335x_cm_per_ocmcram_clkctrl;
#define AM335X_CM_PER_GPMC_CLKCTRL				0x44E00030
extern reg am335x_cm_per_gpmc_clkctrl;
#define AM335X_CM_PER_MCASP0_CLKCTRL				0x44E00034
extern reg am335x_cm_per_mcasp0_clkctrl;
#define AM335X_CM_PER_UART5_CLKCTRL				0x44E00038
extern reg am335x_cm_per_uart5_clkctrl;
#define AM335X_CM_PER_MMC0_CLKCTRL				0x44E0003C
extern reg am335x_cm_per_mmc0_clkctrl;
#define AM335X_CM_PER_ELM_CLKCTRL				0x44E00040
extern reg am335x_cm_per_elm_clkctrl;
#define AM335X_CM_PER_I2C2_CLKCTRL				0x44E00044
extern reg am335x_cm_per_i2c2_clkctrl;
#define AM335X_CM_PER_I2C1_CLKCTRL				0x44E00048
extern reg am335x_cm_per_i2c1_clkctrl;
#define AM335X_CM_PER_SPI0_CLKCTRL				0x44E0004C
extern reg am335x_cm_per_spi0_clkctrl;
#define AM335X_CM_PER_SPI1_CLKCTRL				0x44E00050
extern reg am335x_cm_per_spi1_clkctrl;
#define AM335X_CM_PER_L4LS_CLKCTRL				0x44E00060
extern reg am335x_cm_per_l4ls_clkctrl;
#define AM335X_CM_PER_MCASP1_CLKCTRL				0x44E00068
extern reg am335x_cm_per_mcasp1_clkctrl;
#define AM335X_CM_PER_RNG_CLKCTRL				0x44E00090
extern reg am335x_cm_per_rng_clkctrl;
#define AM335X_CM_PER_AES0_CLKCTRL				0x44E00094
extern reg am335x_cm_per_aes0_clkctrl;
#define AM335X_CM_PER_SHA0_CLKCTRL				0x44E000A0
extern reg am335x_cm_per_sha0_clkctrl;
#define AM335X_CM_PER_UART1_CLKCTRL				0x44E0006C
extern reg am335x_cm_per_uart1_clkctrl;
#define AM335X_CM_PER_UART2_CLKCTRL				0x44E00070
extern reg am335x_cm_per_uart2_clkctrl;
#define AM335X_CM_PER_UART3_CLKCTRL				0x44E00074
extern reg am335x_cm_per_uart3_clkctrl;
#define AM335X_CM_PER_UART4_CLKCTRL				0x44E00078
extern reg am335x_cm_per_uart4_clkctrl;
#define AM335X_CM_PER_TIMER7_CLKCTRL				0x44E0007C
extern reg am335x_cm_per_timer7_clkctrl;
#define AM335X_CM_PER_TIMER2_CLKCTRL				0x44E00080
extern reg am335x_cm_per_timer2_clkctrl;
#define AM335X_CM_PER_TIMER3_CLKCTRL				0x44E00084
extern reg am335x_cm_per_timer3_clkctrl;
#define AM335X_CM_PER_TIMER4_CLKCTRL				0x44E00088
extern reg am335x_cm_per_timer4_clkctrl;
#define AM335X_CM_PER_GPIO1_CLKCTRL				0x44E000AC
extern reg am335x_cm_per_gpio1_clkctrl;
#define AM335X_CM_PER_GPIO2_CLKCTRL				0x44E000B0
extern reg am335x_cm_per_gpio2_clkctrl;
#define AM335X_CM_PER_GPIO3_CLKCTRL				0x44E000B4
extern reg am335x_cm_per_gpio3_clkctrl;
#define AM335X_CM_PER_TPCC_CLKCTRL				0x44E000BC
extern reg am335x_cm_per_tpcc_clkctrl;
#define AM335X_CM_PER_DCAN0_CLKCTRL				0x44E000C0
extern reg am335x_cm_per_dcan0_clkctrl;
#define AM335X_CM_PER_DCAN1_CLKCTRL				0x44E000C4
extern reg am335x_cm_per_dcan1_clkctrl;
#define AM335X_CM_PER_EPWMSS1_CLKCTRL				0x44E000CC
extern reg am335x_cm_per_epwmss1_clkctrl;
#define AM335X_CM_PER_EPWMSS0_CLKCTRL				0x44E000D4
extern reg am335x_cm_per_epwmss0_clkctrl;
#define AM335X_CM_PER_EPWMSS2_CLKCTRL				0x44E000D8
extern reg am335x_cm_per_epwmss2_clkctrl;
#define AM335X_CM_PER_L3_INSTR_CLKCTRL				0x44E000DC
extern reg am335x_cm_per_l3_instr_clkctrl;
#define AM335X_CM_PER_L3_CLKCTRL				0x44E000E0
extern reg am335x_cm_per_l3_clkctrl;
#define AM335X_CM_PER_IEEE5000_CLKCTRL				0x44E000E4
extern reg am335x_cm_per_ieee5000_clkctrl;
#define AM335X_CM_PER_PRU_ICSS_CLKCTRL				0x44E000E8
extern reg am335x_cm_per_pru_icss_clkctrl;
#define AM335X_CM_PER_TIMER5_CLKCTRL				0x44E000EC
extern reg am335x_cm_per_timer5_clkctrl;
#define AM335X_CM_PER_TIMER6_CLKCTRL				0x44E000F0
extern reg am335x_cm_per_timer6_clkctrl;
#define AM335X_CM_PER_MMC1_CLKCTRL				0x44E000F4
extern reg am335x_cm_per_mmc1_clkctrl;
#define AM335X_CM_PER_MMC2_CLKCTRL				0x44E000F8
extern reg am335x_cm_per_mmc2_clkctrl;
#define AM335X_CM_PER_TPTC1_CLKCTRL				0x44E000FC
extern reg am335x_cm_per_tptc1_clkctrl;
#define AM335X_CM_PER_TPTC2_CLKCTRL				0x44E00100
extern reg am335x_cm_per_tptc2_clkctrl;
#define AM335X_CM_PER_SPINLOCK_CLKCTRL				0x44E0010C
extern reg am335x_cm_per_spinlock_clkctrl;
#define AM335X_CM_PER_MAILBOX0_CLKCTRL				0x44E00110
extern reg am335x_cm_per_mailbox0_clkctrl;
#define AM335X_CM_PER_L4HS_CLKSTCTRL				0x44E0011C
extern reg am335x_cm_per_l4hs_clkstctrl;
#define AM335X_CM_PER_L4HS_CLKCTRL				0x44E00120
extern reg am335x_cm_per_l4hs_clkctrl;
#define AM335X_CM_PER_OCPWP_L3_CLKSTCTRL			0x44E0012C
extern reg am335x_cm_per_ocpwp_l3_clkstctrl;
#define AM335X_CM_PER_OCPWP_CLKCTRL				0x44E00130
extern reg am335x_cm_per_ocpwp_clkctrl;
#define AM335X_CM_PER_PRU_ICSS_CLKSTCTRL			0x44E00140
extern reg am335x_cm_per_pru_icss_clkstctrl;
#define AM335X_CM_PER_CPSW_CLKSTCTRL				0x44E00144
extern reg am335x_cm_per_cpsw_clkstctrl;
#define AM335X_CM_PER_LCDC_CLKSTCTRL				0x44E00148
extern reg am335x_cm_per_lcdc_clkstctrl;
#define AM335X_CM_PER_CLKDIV32K_CLKCTRL				0x44E0014C
extern reg am335x_cm_per_clkdiv32k_clkctrl;
#define AM335X_CM_PER_CLK_24MHZ_CLKSTCTRL			0x44E00150
extern reg am335x_cm_per_clk_24mhz_clkstctrl;
#define AM335X_CM_PER_MOD_REGCOUNT				61
extern reg *am335x_cm_per_mod[AM335X_CM_PER_MOD_REGCOUNT + 1];

/* CM_WKUP Registers */
#define AM335X_CM_WKUP_CLKSTCTRL				0x44E00400
extern reg am335x_cm_wkup_clkstctrl;
#define AM335X_CM_WKUP_CONTROL_CLKCTRL				0x44E00404
extern reg am335x_cm_wkup_control_clkctrl;
#define AM335X_CM_WKUP_GPIO0_CLKCTRL				0x44E00408
extern reg am335x_cm_wkup_gpio0_clkctrl;
#define AM335X_CM_WKUP_L4WKUP_CLKCTRL				0x44E0040C
extern reg am335x_cm_wkup_l4wkup_clkctrl;
#define AM335X_CM_WKUP_TIMER0_CLKCTRL				0x44E00410
extern reg am335x_cm_wkup_timer0_clkctrl;
#define AM335X_CM_WKUP_DEBUGSS_CLKCTRL				0x44E00414
extern reg am335x_cm_wkup_debugss_clkctrl;
#define AM335X_CM_L3_AON_CLKSTCTRL				0x44E00418
extern reg am335x_cm_l3_aon_clkstctrl;
#define AM335X_CM_AUTOIDLE_DPLL_MPU				0x44E0041C
extern reg am335x_cm_autoidle_dpll_mpu;
#define AM335X_CM_IDLEST_DPLL_MPU				0x44E00420
extern reg am335x_cm_idlest_dpll_mpu;
#define AM335X_CM_SSC_DELTAMSTEP_DPLL_MPU			0x44E00424
extern reg am335x_cm_ssc_deltamstep_dpll_mpu;
#define AM335X_CM_SSC_MODFREQDIV_DPLL_MPU			0x44E00428
extern reg am335x_cm_ssc_modfreqdiv_dpll_mpu;
#define AM335X_CM_CLKSEL_DPLL_MPU				0x44E0042C
extern reg am335x_cm_clksel_dpll_mpu;
#define AM335X_CM_AUTOIDLE_DPLL_DDR				0x44E00430
extern reg am335x_cm_autoidle_dpll_ddr;
#define AM335X_CM_IDLEST_DPLL_DDR				0x44E00434
extern reg am335x_cm_idlest_dpll_ddr;
#define AM335X_CM_SSC_DELTAMSTEP_DPLL_DDR			0x44E00438
extern reg am335x_cm_ssc_deltamstep_dpll_ddr;
#define AM335X_CM_SSC_MODFREQDIV_DPLL_DDR			0x44E0043C
extern reg am335x_cm_ssc_modfreqdiv_dpll_ddr;
#define AM335X_CM_CLKSEL_DPLL_DDR				0x44E00440
extern reg am335x_cm_clksel_dpll_ddr;
#define AM335X_CM_AUTOIDLE_DPLL_DISP				0x44E00444
extern reg am335x_cm_autoidle_dpll_disp;
#define AM335X_CM_IDLEST_DPLL_DISP				0x44E00448
extern reg am335x_cm_idlest_dpll_disp;
#define AM335X_CM_SSC_DELTAMSTEP_DPLL_DISP			0x44E0044C
extern reg am335x_cm_ssc_deltamstep_dpll_disp;
#define AM335X_CM_SSC_MODFREQDIV_DPLL_DISP			0x44E00450
extern reg am335x_cm_ssc_modfreqdiv_dpll_disp;
#define AM335X_CM_CLKSEL_DPLL_DISP				0x44E00454
extern reg am335x_cm_clksel_dpll_disp;
#define AM335X_CM_AUTOIDLE_DPLL_CORE				0x44E00458
extern reg am335x_cm_autoidle_dpll_core;
#define AM335X_CM_IDLEST_DPLL_CORE				0x44E0045C
extern reg am335x_cm_idlest_dpll_core;
#define AM335X_CM_SSC_DELTAMSTEP_DPLL_CORE			0x44E00460
extern reg am335x_cm_ssc_deltamstep_dpll_core;
#define AM335X_CM_SSC_MODFREQDIV_DPLL_CORE			0x44E00464
extern reg am335x_cm_ssc_modfreqdiv_dpll_core;
#define AM335X_CM_CLKSEL_DPLL_CORE				0x44E00468
extern reg am335x_cm_clksel_dpll_core;
#define AM335X_CM_AUTOIDLE_DPLL_PER				0x44E0046C
extern reg am335x_cm_autoidle_dpll_per;
#define AM335X_CM_IDLEST_DPLL_PER				0x44E00470
extern reg am335x_cm_idlest_dpll_per;
#define AM335X_CM_SSC_DELTAMSTEP_DPLL_PER			0x44E00474
extern reg am335x_cm_ssc_deltamstep_dpll_per;
#define AM335X_CM_SSC_MODFREQDIV_DPLL_PER			0x44E00478
extern reg am335x_cm_ssc_modfreqdiv_dpll_per;
#define AM335X_CM_CLKDCOLDO_DPLL_PER				0x44E0047C
extern reg am335x_cm_clkdcoldo_dpll_per;
#define AM335X_CM_DIV_M4_DPLL_CORE				0x44E00480
extern reg am335x_cm_div_m4_dpll_core;
#define AM335X_CM_DIV_M5_DPLL_CORE				0x44E00484
extern reg am335x_cm_div_m5_dpll_core;
#define AM335X_CM_CLKMODE_DPLL_MPU				0x44E00488
extern reg am335x_cm_clkmode_dpll_mpu;
#define AM335X_CM_CLKMODE_DPLL_PER				0x44E0048C
extern reg am335x_cm_clkmode_dpll_per;
#define AM335X_CM_CLKMODE_DPLL_CORE				0x44E00490
extern reg am335x_cm_clkmode_dpll_core;
#define AM335X_CM_CLKMODE_DPLL_DDR				0x44E00494
extern reg am335x_cm_clkmode_dpll_ddr;
#define AM335X_CM_CLKMODE_DPLL_DISP				0x44E00498
extern reg am335x_cm_clkmode_dpll_disp;
#define AM335X_CM_CLKSEL_DPLL_PERIPH				0x44E0049C
extern reg am335x_cm_clksel_dpll_periph;
#define AM335X_CM_DIV_M2_DPLL_DDR				0x44E004A0
extern reg am335x_cm_div_m2_dpll_ddr;
#define AM335X_CM_DIV_M2_DPLL_DISP				0x44E004A4
extern reg am335x_cm_div_m2_dpll_disp;
#define AM335X_CM_DIV_M2_DPLL_MPU				0x44E004A8
extern reg am335x_cm_div_m2_dpll_mpu;
#define AM335X_CM_DIV_M2_DPLL_PER				0x44E004AC
extern reg am335x_cm_div_m2_dpll_per;
#define AM335X_CM_WKUP_WKUP_M3_CLKCTRL				0x44E004B0
extern reg am335x_cm_wkup_wkup_m3_clkctrl;
#define AM335X_CM_WKUP_UART0_CLKCTRL				0x44E004B4
extern reg am335x_cm_wkup_uart0_clkctrl;
#define AM335X_CM_WKUP_I2C0_CLKCTRL				0x44E004B8
extern reg am335x_cm_wkup_i2c0_clkctrl;
#define AM335X_CM_WKUP_ADC_TSC_CLKCTRL				0x44E004BC
extern reg am335x_cm_wkup_adc_tsc_clkctrl;
#define AM335X_CM_WKUP_SMARTREFLEX0_CLKCTRL			0x44E004C0
extern reg am335x_cm_wkup_smartreflex0_clkctrl;
#define AM335X_CM_WKUP_TIMER1_CLKCTRL				0x44E004C4
extern reg am335x_cm_wkup_timer1_clkctrl;
#define AM335X_CM_WKUP_SMARTREFLEX1_CLKCTRL			0x44E004C8
extern reg am335x_cm_wkup_smartreflex1_clkctrl;
#define AM335X_CM_L4_WKUP_AON_CLKSTCTRL				0x44E004CC
extern reg am335x_cm_l4_wkup_aon_clkstctrl;
#define AM335X_CM_WKUP_WDT1_CLKCTRL				0x44E004D4
extern reg am335x_cm_wkup_wdt1_clkctrl;
#define AM335X_CM_DIV_M6_DPLL_CORE				0x44E004D8
extern reg am335x_cm_div_m6_dpll_core;
#define AM335X_CM_WKUP_MOD_REGCOUNT				54
extern reg *am335x_cm_wkup_mod[AM335X_CM_WKUP_MOD_REGCOUNT + 1];

/* CM_DPLL Registers */
#define AM335X_CLKSEL_TIMER7_CLK				0x44E00504
extern reg am335x_clksel_timer7_clk;
#define AM335X_CLKSEL_TIMER2_CLK				0x44E00508
extern reg am335x_clksel_timer2_clk;
#define AM335X_CLKSEL_TIMER3_CLK				0x44E0050C
extern reg am335x_clksel_timer3_clk;
#define AM335X_CLKSEL_TIMER4_CLK				0x44E00510
extern reg am335x_clksel_timer4_clk;
#define AM335X_CM_MAC_CLKSEL					0x44E00514
extern reg am335x_cm_mac_clksel;
#define AM335X_CLKSEL_TIMER5_CLK				0x44E00518
extern reg am335x_clksel_timer5_clk;
#define AM335X_CLKSEL_TIMER6_CLK				0x44E0051C
extern reg am335x_clksel_timer6_clk;
#define AM335X_CM_CPTS_RFT_CLKSEL				0x44E00520
extern reg am335x_cm_cpts_rft_clksel;
#define AM335X_CLKSEL_TIMER1MS_CLK				0x44E00528
extern reg am335x_clksel_timer1ms_clk;
#define AM335X_CLKSEL_GFX_FCLK					0x44E0052C
extern reg am335x_clksel_gfx_fclk;
#define AM335X_CLKSEL_PRU_ICSS_OCP_CLK				0x44E00530
extern reg am335x_clksel_pru_icss_ocp_clk;
#define AM335X_CLKSEL_LCDC_PIXEL_CLK				0x44E00534
extern reg am335x_clksel_lcdc_pixel_clk;
#define AM335X_CLKSEL_WDT1_CLK					0x44E00538
extern reg am335x_clksel_wdt1_clk;
#define AM335X_CLKSEL_GPIO0_DBCLK				0x44E0053C
extern reg am335x_clksel_gpio0_dbclk;
#define AM335X_CM_DPLL_MOD_REGCOUNT				14
extern reg *am335x_cm_dpll_mod[AM335X_CM_DPLL_MOD_REGCOUNT + 1];

/* CM_MPU Registers */
#define AM335X_CM_MPU_CLKSTCTRL					0x44E00600
extern reg am335x_cm_mpu_clkstctrl;
#define AM335X_CM_MPU_MPU_CLKCTRL				0x44E00604
extern reg am335x_cm_mpu_mpu_clkctrl;
#define AM335X_CM_MPU_MOD_REGCOUNT				2
extern reg *am335x_cm_mpu_mod[AM335X_CM_MPU_MOD_REGCOUNT + 1];

/* CM_DEVICE Registers */
#define AM335X_CM_CLKOUT_CTRL					0x44E00700
extern reg am335x_cm_clkout_ctrl;
#define AM335X_CM_DEVICE_MOD_REGCOUNT				1
extern reg *am335x_cm_device_mod[AM335X_CM_DEVICE_MOD_REGCOUNT + 1];

/* CM_RTC Registers */
#define AM335X_CM_RTC_RTC_CLKCTRL				0x44E00800
extern reg am335x_cm_rtc_rtc_clkctrl;
#define AM335X_CM_RTC_CLKSTCTRL					0x44E00804
extern reg am335x_cm_rtc_clkstctrl;
#define AM335X_CM_RTC_MOD_REGCOUNT				2
extern reg *am335x_cm_rtc_mod[AM335X_CM_RTC_MOD_REGCOUNT + 1];

/* CM_GFX Registers */
#define AM335X_CM_GFX_L3_CLKSTCTRL				0x44E00900
extern reg am335x_cm_gfx_l3_clkstctrl;
#define AM335X_CM_GFX_GFX_CLKCTRL				0x44E00904
extern reg am335x_cm_gfx_gfx_clkctrl;
#define AM335X_CM_GFX_L4LS_GFX_CLKSTCTRL			0x44E0090C
extern reg am335x_cm_gfx_l4ls_gfx_clkstctrl;
#define AM335X_CM_GFX_MMUCFG_CLKCTRL				0x44E00910
extern reg am335x_cm_gfx_mmucfg_clkctrl;
#define AM335X_CM_GFX_MMUDATA_CLKCTRL				0x44E00914
extern reg am335x_cm_gfx_mmudata_clkctrl;
#define AM335X_CM_GFX_MOD_REGCOUNT				5
extern reg *am335x_cm_gfx_mod[AM335X_CM_GFX_MOD_REGCOUNT + 1];

/* CM_CEFUSE Registers */
#define AM335X_CM_CEFUSE_CLKSTCTRL				0x44E00A00
extern reg am335x_cm_cefuse_clkstctrl;
#define AM335X_CM_CEFUSE_CEFUSE_CLKCTRL				0x44E00A20
extern reg am335x_cm_cefuse_cefuse_clkctrl;
#define AM335X_CM_CEFUSE_MOD_REGCOUNT				2
extern reg *am335x_cm_cefuse_mod[AM335X_CM_CEFUSE_MOD_REGCOUNT + 1];

typedef enum {
	CM_AM335X_CM_PER,
	CM_AM335X_CM_WKUP,
	CM_AM335X_CM_DPLL,
	CM_AM335X_CM_MPU,
	CM_AM335X_CM_DEVICE,
	CM_AM335X_CM_RTC,
	CM_AM335X_CM_GFX,
	CM_AM335X_CM_CEFUSE,
	CM_AM335X_MODS_COUNT
} cm_am335x_mod_id;

extern reg **cm_am335x_mods[CM_AM335X_MODS_COUNT + 1];

extern const char *cm_am335x_mods_name[CM_AM335X_MODS_COUNT];

extern const dpll_settings_regs dpll_am335x_regs[DPLL_AM335X_ID_MAX];
extern const reg *dpll_am335x_hsdiv_regs[DPLL_AM335X_ID_MAX][HSDIV_AM335X_ID_MAX];


#endif
