/*
 *
 * @Component			OMAPCONF
 * @Filename			cm_am437x-defs.h
 * @Description			AM437X CM Register Definitions & Functions
 * @Author			Dave Gerlach <d-gerlach@ti.com>
 * @Date			2016
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef __CM_AM437X_DEFS_H__
#define __CM_AM437X_DEFS_H__

#include <reg.h>

/* CM_CEFUSE Registers */
#define AM437X_CM_CEFUSE_CLKSTCTRL				0x44df8700
extern reg am437x_cm_cefuse_clkstctrl;
#define AM437X_CM_CEFUSE_CLKCTRL				0x44df8720
extern reg am437x_cm_cefuse_clkctrl;
#define AM437X_CM_CEFUSE_MOD_REGCOUNT				2
extern reg *am437x_cm_cefuse_mod[AM437X_CM_CEFUSE_MOD_REGCOUNT + 1];

/* CM_DEVICE Registers */
#define AM437X_CM_CLKOUT1_CTRL					0x44df4100
extern reg am437x_cm_clkout1_ctrl;
#define AM437X_CM_DLL_CTRL					0x44df4104
extern reg am437x_cm_dll_ctrl;
#define AM437X_CM_CLKOUT2_CTRL					0x44df4108
extern reg am437x_cm_clkout2_ctrl;
#define AM437X_CM_DEVICE_MOD_REGCOUNT				3
extern reg *am437x_cm_device_mod[AM437X_CM_DEVICE_MOD_REGCOUNT + 1];

/* CM_DPLL Registers */
#define AM437X_CM_DPLL_DPLL_CLKSEL_TIMER1_CLK			0x44df4200
extern reg am437x_cm_dpll_dpll_clksel_timer1_clk;
#define AM437X_CM_DPLL_CLKSEL_TIMER2_CLK			0x44df4204
extern reg am437x_cm_dpll_clksel_timer2_clk;
#define AM437X_CM_DPLL_CLKSEL_TIMER3_CLK			0x44df4208
extern reg am437x_cm_dpll_clksel_timer3_clk;
#define AM437X_CM_DPLL_CLKSEL_TIMER4_CLK			0x44df420c
extern reg am437x_cm_dpll_clksel_timer4_clk;
#define AM437X_CM_DPLL_CLKSEL_TIMER5_CLK			0x44df4210
extern reg am437x_cm_dpll_clksel_timer5_clk;
#define AM437X_CM_DPLL_CLKSEL_TIMER6_CLK			0x44df4214
extern reg am437x_cm_dpll_clksel_timer6_clk;
#define AM437X_CM_DPLL_CLKSEL_TIMER7_CLK			0x44df4218
extern reg am437x_cm_dpll_clksel_timer7_clk;
#define AM437X_CM_DPLL_CLKSEL_TIMER8_CLK			0x44df421c
extern reg am437x_cm_dpll_clksel_timer8_clk;
#define AM437X_CM_DPLL_CLKSEL_TIMER9_CLK			0x44df4220
extern reg am437x_cm_dpll_clksel_timer9_clk;
#define AM437X_CM_DPLL_CLKSEL_TIMER10_CLK			0x44df4224
extern reg am437x_cm_dpll_clksel_timer10_clk;
#define AM437X_CM_DPLL_CLKSEL_TIMER11_CLK			0x44df4228
extern reg am437x_cm_dpll_clksel_timer11_clk;
#define AM437X_CM_DPLL_CLKSEL_WDT1_CLK				0x44df422c
extern reg am437x_cm_dpll_clksel_wdt1_clk;
#define AM437X_CM_DPLL_CLKSEL_SYNCTIMER_CLK			0x44df4230
extern reg am437x_cm_dpll_clksel_synctimer_clk;
#define AM437X_CM_DPLL_CLKSEL_MAC_CLK				0x44df4234
extern reg am437x_cm_dpll_clksel_mac_clk;
#define AM437X_CM_DPLL_CLKSEL_CPTS_RFT_CLK			0x44df4238
extern reg am437x_cm_dpll_clksel_cpts_rft_clk;
#define AM437X_CM_DPLL_CLKSEL_GFX_FCLK				0x44df423c
extern reg am437x_cm_dpll_clksel_gfx_fclk;
#define AM437X_CM_DPLL_CLKSEL_GPIO0_DBCLK			0x44df4240
extern reg am437x_cm_dpll_clksel_gpio0_dbclk;
#define AM437X_CM_CLKSEL_PRU_ICSS_OCP_CLK			0x44df4248
extern reg am437x_cm_clksel_pru_icss_ocp_clk;
#define AM437X_CM_CLKSEL_ADC1_CLK				0x44df424c
extern reg am437x_cm_clksel_adc1_clk;
#define AM437X_CM_DPLL_CLKSEL_DLL_AGING_CLK			0x44df4250
extern reg am437x_cm_dpll_clksel_dll_aging_clk;
#define AM437X_CM_DPLL_CLKSEL_USBPHY32KHZ_GCLK			0x44df4260
extern reg am437x_cm_dpll_clksel_usbphy32khz_gclk;
#define AM437X_CM_DPLL_MOD_REGCOUNT				21
extern reg *am437x_cm_dpll_mod[AM437X_CM_DPLL_MOD_REGCOUNT + 1];

/* CM_GFX Registers */
#define AM437X_CM_GFX_L3_CLKSTCTRL				0x44df8400
extern reg am437x_cm_gfx_l3_clkstctrl;
#define AM437X_CM_GFX_CLKCTRL					0x44df8420
extern reg am437x_cm_gfx_clkctrl;
#define AM437X_CM_GFX_MOD_REGCOUNT				2
extern reg *am437x_cm_gfx_mod[AM437X_CM_GFX_MOD_REGCOUNT + 1];

/* CM_MPU Registers */
#define AM437X_CM_MPU_CLKSTCTRL					0x44df8300
extern reg am437x_cm_mpu_clkstctrl;
#define AM437X_CM_MPU_CLKCTRL					0x44df8320
extern reg am437x_cm_mpu_clkctrl;
#define AM437X_CM_MPU_MOD_REGCOUNT				2
extern reg *am437x_cm_mpu_mod[AM437X_CM_MPU_MOD_REGCOUNT + 1];

/* CM_PER Registers */
#define AM437X_CM_PER_L3_CLKSTCTRL				0x44df8800
extern reg am437x_cm_per_l3_clkstctrl;
#define AM437X_CM_PER_L3_CLKCTRL				0x44df8820
extern reg am437x_cm_per_l3_clkctrl;
#define AM437X_CM_PER_AES0_CLKCTRL				0x44df8828
extern reg am437x_cm_per_aes0_clkctrl;
#define AM437X_CM_PER_DES_CLKCTRL				0x44df8830
extern reg am437x_cm_per_des_clkctrl;
#define AM437X_CM_PER_L3_INSTR_CLKCTRL				0x44df8840
extern reg am437x_cm_per_l3_instr_clkctrl;
#define AM437X_CM_PER_OCMCRAM_CLKCTRL				0x44df8850
extern reg am437x_cm_per_ocmcram_clkctrl;
#define AM437X_CM_PER_SHA0_CLKCTRL				0x44df8858
extern reg am437x_cm_per_sha0_clkctrl;
#define AM437X_CM_PER_VPFE0_CLKCTRL				0x44df8868
extern reg am437x_cm_per_vpfe0_clkctrl;
#define AM437X_CM_PER_VPFE1_CLKCTRL				0x44df8870
extern reg am437x_cm_per_vpfe1_clkctrl;
#define AM437X_CM_PER_TPCC_CLKCTRL				0x44df8878
extern reg am437x_cm_per_tpcc_clkctrl;
#define AM437X_CM_PER_TPTC0_CLKCTRL				0x44df8880
extern reg am437x_cm_per_tptc0_clkctrl;
#define AM437X_CM_PER_TPTC1_CLKCTRL				0x44df8888
extern reg am437x_cm_per_tptc1_clkctrl;
#define AM437X_CM_PER_TPTC2_CLKCTRL				0x44df8890
extern reg am437x_cm_per_tptc2_clkctrl;
#define AM437X_CM_PER_DLL_AGING_CLKCTRL				0x44df8898
extern reg am437x_cm_per_dll_aging_clkctrl;
#define AM437X_CM_PER_L4HS_CLKCTRL				0x44df88a0
extern reg am437x_cm_per_l4hs_clkctrl;
#define AM437X_CM_PER_L3S_CLKSTCTRL				0x44df8a00
extern reg am437x_cm_per_l3s_clkstctrl;
#define AM437X_CM_PER_GPMC_CLKCTRL				0x44df8a20
extern reg am437x_cm_per_gpmc_clkctrl;
#define AM437X_CM_PER_ADC1_CLKCTRL				0x44df8a30
extern reg am437x_cm_per_adc1_clkctrl;
#define AM437X_CM_PER_MCASP0_CLKCTRL				0x44df8a38
extern reg am437x_cm_per_mcasp0_clkctrl;
#define AM437X_CM_PER_MCASP1_CLKCTRL				0x44df8a40
extern reg am437x_cm_per_mcasp1_clkctrl;
#define AM437X_CM_PER_MMC2_CLKCTRL				0x44df8a48
extern reg am437x_cm_per_mmc2_clkctrl;
#define AM437X_CM_PER_QSPI_CLKCTRL				0x44df8a58
extern reg am437x_cm_per_qspi_clkctrl;
#define AM437X_CM_PER_USB_OTG_SS0_CLKCTRL			0x44df8a60
extern reg am437x_cm_per_usb_otg_ss0_clkctrl;
#define AM437X_CM_PER_USB_OTG_SS1_CLKCTRL			0x44df8a68
extern reg am437x_cm_per_usb_otg_ss1_clkctrl;
#define AM437X_CM_PER_PRU_ICSS_CLKSTCTRL			0x44df8b00
extern reg am437x_cm_per_pru_icss_clkstctrl;
#define AM437X_CM_PER_PRU_ICSS_CLKCTRL				0x44df8b20
extern reg am437x_cm_per_pru_icss_clkctrl;
#define AM437X_CM_PER_L4LS_CLKSTCTRL				0x44df8c00
extern reg am437x_cm_per_l4ls_clkstctrl;
#define AM437X_CM_PER_L4LS_CLKCTRL				0x44df8c20
extern reg am437x_cm_per_l4ls_clkctrl;
#define AM437X_CM_PER_DCAN0_CLKCTRL				0x44df8c28
extern reg am437x_cm_per_dcan0_clkctrl;
#define AM437X_CM_PER_DCAN1_CLKCTRL				0x44df8c30
extern reg am437x_cm_per_dcan1_clkctrl;
#define AM437X_CM_PER_PWMSS0_CLKCTRL				0x44df8c38
extern reg am437x_cm_per_pwmss0_clkctrl;
#define AM437X_CM_PER_PWMSS1_CLKCTRL				0x44df8c40
extern reg am437x_cm_per_pwmss1_clkctrl;
#define AM437X_CM_PER_PWMSS2_CLKCTRL				0x44df8c48
extern reg am437x_cm_per_pwmss2_clkctrl;
#define AM437X_CM_PER_PWMSS3_CLKCTRL				0x44df8c50
extern reg am437x_cm_per_pwmss3_clkctrl;
#define AM437X_CM_PER_PWMSS4_CLKCTRL				0x44df8c58
extern reg am437x_cm_per_pwmss4_clkctrl;
#define AM437X_CM_PER_PWMSS5_CLKCTRL				0x44df8c60
extern reg am437x_cm_per_pwmss5_clkctrl;
#define AM437X_CM_PER_ELM_CLKCTRL				0x44df8c68
extern reg am437x_cm_per_elm_clkctrl;
#define AM437X_CM_PER_GPIO1_CLKCTRL				0x44df8c78
extern reg am437x_cm_per_gpio1_clkctrl;
#define AM437X_CM_PER_GPIO2_CLKCTRL				0x44df8c80
extern reg am437x_cm_per_gpio2_clkctrl;
#define AM437X_CM_PER_GPIO3_CLKCTRL				0x44df8c88
extern reg am437x_cm_per_gpio3_clkctrl;
#define AM437X_CM_PER_GPIO4_CLKCTRL				0x44df8c90
extern reg am437x_cm_per_gpio4_clkctrl;
#define AM437X_CM_PER_GPIO5_CLKCTRL				0x44df8c98
extern reg am437x_cm_per_gpio5_clkctrl;
#define AM437X_CM_PER_HDQ1W_CLKCTRL				0x44df8ca0
extern reg am437x_cm_per_hdq1w_clkctrl;
#define AM437X_CM_PER_I2C1_CLKCTRL				0x44df8ca8
extern reg am437x_cm_per_i2c1_clkctrl;
#define AM437X_CM_PER_I2C2_CLKCTRL				0x44df8cb0
extern reg am437x_cm_per_i2c2_clkctrl;
#define AM437X_CM_PER_MAILBOX0_CLKCTRL				0x44df8cb8
extern reg am437x_cm_per_mailbox0_clkctrl;
#define AM437X_CM_PER_MMC0_CLKCTRL				0x44df8cc0
extern reg am437x_cm_per_mmc0_clkctrl;
#define AM437X_CM_PER_MMC1_CLKCTRL				0x44df8cc8
extern reg am437x_cm_per_mmc1_clkctrl;
#define AM437X_CM_PER_RNG_CLKCTRL				0x44df8ce0
extern reg am437x_cm_per_rng_clkctrl;
#define AM437X_CM_PER_SPI0_CLKCTRL				0x44df8d00
extern reg am437x_cm_per_spi0_clkctrl;
#define AM437X_CM_PER_SPI1_CLKCTRL				0x44df8d08
extern reg am437x_cm_per_spi1_clkctrl;
#define AM437X_CM_PER_SPI2_CLKCTRL				0x44df8d10
extern reg am437x_cm_per_spi2_clkctrl;
#define AM437X_CM_PER_SPI3_CLKCTRL				0x44df8d18
extern reg am437x_cm_per_spi3_clkctrl;
#define AM437X_CM_PER_SPI4_CLKCTRL				0x44df8d20
extern reg am437x_cm_per_spi4_clkctrl;
#define AM437X_CM_PER_SPINLOCK_CLKCTRL				0x44df8d28
extern reg am437x_cm_per_spinlock_clkctrl;
#define AM437X_CM_PER_TIMER2_CLKCTRL				0x44df8d30
extern reg am437x_cm_per_timer2_clkctrl;
#define AM437X_CM_PER_TIMER3_CLKCTRL				0x44df8d38
extern reg am437x_cm_per_timer3_clkctrl;
#define AM437X_CM_PER_TIMER4_CLKCTRL				0x44df8d40
extern reg am437x_cm_per_timer4_clkctrl;
#define AM437X_CM_PER_TIMER5_CLKCTRL				0x44df8d48
extern reg am437x_cm_per_timer5_clkctrl;
#define AM437X_CM_PER_TIMER6_CLKCTRL				0x44df8d50
extern reg am437x_cm_per_timer6_clkctrl;
#define AM437X_CM_PER_TIMER7_CLKCTRL				0x44df8d58
extern reg am437x_cm_per_timer7_clkctrl;
#define AM437X_CM_PER_TIMER8_CLKCTRL				0x44df8d60
extern reg am437x_cm_per_timer8_clkctrl;
#define AM437X_CM_PER_TIMER9_CLKCTRL				0x44df8d68
extern reg am437x_cm_per_timer9_clkctrl;
#define AM437X_CM_PER_TIMER10_CLKCTRL				0x44df8d70
extern reg am437x_cm_per_timer10_clkctrl;
#define AM437X_CM_PER_TIMER11_CLKCTRL				0x44df8d78
extern reg am437x_cm_per_timer11_clkctrl;
#define AM437X_CM_PER_UART1_CLKCTRL				0x44df8d80
extern reg am437x_cm_per_uart1_clkctrl;
#define AM437X_CM_PER_UART2_CLKCTRL				0x44df8d88
extern reg am437x_cm_per_uart2_clkctrl;
#define AM437X_CM_PER_UART3_CLKCTRL				0x44df8d90
extern reg am437x_cm_per_uart3_clkctrl;
#define AM437X_CM_PER_UART4_CLKCTRL				0x44df8d98
extern reg am437x_cm_per_uart4_clkctrl;
#define AM437X_CM_PER_UART5_CLKCTRL				0x44df8da0
extern reg am437x_cm_per_uart5_clkctrl;
#define AM437X_CM_PER_USBPHYOCP2SCP0_CLKCTRL			0x44df8db8
extern reg am437x_cm_per_usbphyocp2scp0_clkctrl;
#define AM437X_CM_PER_USBPHYOCP2SCP1_CLKCTRL			0x44df8dc0
extern reg am437x_cm_per_usbphyocp2scp1_clkctrl;
#define AM437X_CM_PER_EMIF_CLKSTCTRL				0x44df8f00
extern reg am437x_cm_per_emif_clkstctrl;
#define AM437X_CM_PER_EMIF_CLKCTRL				0x44df8f20
extern reg am437x_cm_per_emif_clkctrl;
#define AM437X_CM_PER_DLL_CLKCTRL				0x44df8f28
extern reg am437x_cm_per_dll_clkctrl;
#define AM437X_CM_PER_LCDC_CLKSTCTRL				0x44df9000
extern reg am437x_cm_per_lcdc_clkstctrl;
#define AM437X_CM_PER_DSS_CLKSTCTRL				0x44df9200
extern reg am437x_cm_per_dss_clkstctrl;
#define AM437X_CM_PER_DSS_CLKCTRL				0x44df9220
extern reg am437x_cm_per_dss_clkctrl;
#define AM437X_CM_PER_CPSW_CLKSTCTRL				0x44df9300
extern reg am437x_cm_per_cpsw_clkstctrl;
#define AM437X_CM_PER_CPGMAC0_CLKCTRL				0x44df9320
extern reg am437x_cm_per_cpgmac0_clkctrl;
#define AM437X_CM_PER_OCPWP_L3_CLKSTCTRL			0x44df9400
extern reg am437x_cm_per_ocpwp_l3_clkstctrl;
#define AM437X_CM_PER_OCPWP_CLKCTRL				0x44df9420
extern reg am437x_cm_per_ocpwp_clkctrl;
#define AM437X_CM_PER_MOD_REGCOUNT				82
extern reg *am437x_cm_per_mod[AM437X_CM_PER_MOD_REGCOUNT + 1];

/* CM_RTC Registers */
#define AM437X_CM_RTC_CLKSTCTRL					0x44df8500
extern reg am437x_cm_rtc_clkstctrl;
#define AM437X_CM_RTC_CLKCTRL					0x44df8520
extern reg am437x_cm_rtc_clkctrl;
#define AM437X_CM_RTC_MOD_REGCOUNT				2
extern reg *am437x_cm_rtc_mod[AM437X_CM_RTC_MOD_REGCOUNT + 1];

/* CM_WKUP Registers */
#define AM437X_CM_L3_AON_CLKSTCTRL				0x44df2800
extern reg am437x_cm_l3_aon_clkstctrl;
#define AM437X_CM_WKUP_DBGSS_CLKCTRL				0x44df2820
extern reg am437x_cm_wkup_dbgss_clkctrl;
#define AM437X_CM_L3S_ADC0_CLKSTCTRL				0x44df2900
extern reg am437x_cm_l3s_adc0_clkstctrl;
#define AM437X_CM_WKUP_ADC0_CLKCTRL				0x44df2920
extern reg am437x_cm_wkup_adc0_clkctrl;
#define AM437X_CM_L4_WKUP_AON_CLKSTCTRL				0x44df2a00
extern reg am437x_cm_l4_wkup_aon_clkstctrl;
#define AM437X_CM_WKUP_L4WKUP_CLKCTRL				0x44df2a20
extern reg am437x_cm_wkup_l4wkup_clkctrl;
#define AM437X_CM_WKUP_PROC_CLKCTRL				0x44df2a28
extern reg am437x_cm_wkup_proc_clkctrl;
#define AM437X_CM_WKUP_SYNCTIMER_CLKCTRL			0x44df2a30
extern reg am437x_cm_wkup_synctimer_clkctrl;
#define AM437X_CM_WKUP_CLKDIV32K_CLKCTRL			0x44df2a38
extern reg am437x_cm_wkup_clkdiv32k_clkctrl;
#define AM437X_CM_WKUP_USBPHY0_CLKCTRL				0x44df2a40
extern reg am437x_cm_wkup_usbphy0_clkctrl;
#define AM437X_CM_WKUP_USBPHY1_CLKCTRL				0x44df2a48
extern reg am437x_cm_wkup_usbphy1_clkctrl;
#define AM437X_CM_WKUP_CLKSTCTRL				0x44df2b00
extern reg am437x_cm_wkup_clkstctrl;
#define AM437X_CM_WKUP_TIMER0_CLKCTRL				0x44df2b20
extern reg am437x_cm_wkup_timer0_clkctrl;
#define AM437X_CM_WKUP_TIMER1_CLKCTRL				0x44df2b28
extern reg am437x_cm_wkup_timer1_clkctrl;
#define AM437X_CM_WKUP_WDT1_CLKCTRL				0x44df2b38
extern reg am437x_cm_wkup_wdt1_clkctrl;
#define AM437X_CM_WKUP_I2C0_CLKCTRL				0x44df2b40
extern reg am437x_cm_wkup_i2c0_clkctrl;
#define AM437X_CM_WKUP_UART0_CLKCTRL				0x44df2b48
extern reg am437x_cm_wkup_uart0_clkctrl;
#define AM437X_CM_WKUP_CTRL_CLKCTRL				0x44df2b60
extern reg am437x_cm_wkup_ctrl_clkctrl;
#define AM437X_CM_WKUP_GPIO0_CLKCTRL				0x44df2b68
extern reg am437x_cm_wkup_gpio0_clkctrl;
#define AM437X_CM_CLKMODE_DPLL_CORE				0x44df2d20
extern reg am437x_cm_clkmode_dpll_core;
#define AM437X_CM_IDLEST_DPLL_CORE				0x44df2d24
extern reg am437x_cm_idlest_dpll_core;
#define AM437X_CM_CLKSEL_DPLL_CORE				0x44df2d2c
extern reg am437x_cm_clksel_dpll_core;
#define AM437X_CM_DIV_M4_DPLL_CORE				0x44df2d38
extern reg am437x_cm_div_m4_dpll_core;
#define AM437X_CM_DIV_M5_DPLL_CORE				0x44df2d3c
extern reg am437x_cm_div_m5_dpll_core;
#define AM437X_CM_DIV_M6_DPLL_CORE				0x44df2d40
extern reg am437x_cm_div_m6_dpll_core;
#define AM437X_CM_SSC_DELTAMSTEP_DPLL_CORE			0x44df2d48
extern reg am437x_cm_ssc_deltamstep_dpll_core;
#define AM437X_CM_SSC_MODFREQDIV_DPLL_CORE			0x44df2d4c
extern reg am437x_cm_ssc_modfreqdiv_dpll_core;
#define AM437X_CM_CLKMODE_DPLL_MPU				0x44df2d60
extern reg am437x_cm_clkmode_dpll_mpu;
#define AM437X_CM_IDLEST_DPLL_MPU				0x44df2d64
extern reg am437x_cm_idlest_dpll_mpu;
#define AM437X_CM_CLKSEL_DPLL_MPU				0x44df2d6c
extern reg am437x_cm_clksel_dpll_mpu;
#define AM437X_CM_DIV_M2_DPLL_MPU				0x44df2d70
extern reg am437x_cm_div_m2_dpll_mpu;
#define AM437X_CM_SSC_DELTAMSTEP_DPLL_MPU			0x44df2d88
extern reg am437x_cm_ssc_deltamstep_dpll_mpu;
#define AM437X_CM_SSC_MODFREQDIV_DPLL_MPU			0x44df2d8c
extern reg am437x_cm_ssc_modfreqdiv_dpll_mpu;
#define AM437X_CM_CLKMODE_DPLL_DDR				0x44df2da0
extern reg am437x_cm_clkmode_dpll_ddr;
#define AM437X_CM_IDLEST_DPLL_DDR				0x44df2da4
extern reg am437x_cm_idlest_dpll_ddr;
#define AM437X_CM_CLKSEL_DPLL_DDR				0x44df2dac
extern reg am437x_cm_clksel_dpll_ddr;
#define AM437X_CM_DIV_M2_DPLL_DDR				0x44df2db0
extern reg am437x_cm_div_m2_dpll_ddr;
#define AM437X_CM_DIV_M4_DPLL_DDR				0x44df2db8
extern reg am437x_cm_div_m4_dpll_ddr;
#define AM437X_CM_SSC_DELTAMSTEP_DPLL_DDR			0x44df2dc8
extern reg am437x_cm_ssc_deltamstep_dpll_ddr;
#define AM437X_CM_SSC_MODFREQDIV_DPLL_DDR			0x44df2dcc
extern reg am437x_cm_ssc_modfreqdiv_dpll_ddr;
#define AM437X_CM_CLKMODE_DPLL_PER				0x44df2de0
extern reg am437x_cm_clkmode_dpll_per;
#define AM437X_CM_IDLEST_DPLL_PER				0x44df2de4
extern reg am437x_cm_idlest_dpll_per;
#define AM437X_CM_CLKSEL_DPLL_PER				0x44df2dec
extern reg am437x_cm_clksel_dpll_per;
#define AM437X_CM_DIV_M2_DPLL_PER				0x44df2df0
extern reg am437x_cm_div_m2_dpll_per;
#define AM437X_CM_CLKSEL2_DPLL_PER				0x44df2e04
extern reg am437x_cm_clksel2_dpll_per;
#define AM437X_CM_SSC_DELTAMSTEP_DPLL_PER			0x44df2e08
extern reg am437x_cm_ssc_deltamstep_dpll_per;
#define AM437X_CM_SSC_MODFREQDIV_DPLL_PER			0x44df2e0c
extern reg am437x_cm_ssc_modfreqdiv_dpll_per;
#define AM437X_CM_CLKDCOLDO_DPLL_PER				0x44df2e14
extern reg am437x_cm_clkdcoldo_dpll_per;
#define AM437X_CM_CLKMODE_DPLL_DISP				0x44df2e20
extern reg am437x_cm_clkmode_dpll_disp;
#define AM437X_CM_IDLEST_DPLL_DISP				0x44df2e24
extern reg am437x_cm_idlest_dpll_disp;
#define AM437X_CM_CLKSEL_DPLL_DISP				0x44df2e2c
extern reg am437x_cm_clksel_dpll_disp;
#define AM437X_CM_DIV_M2_DPLL_DISP				0x44df2e30
extern reg am437x_cm_div_m2_dpll_disp;
#define AM437X_CM_SSC_DELTAMSTEP_DPLL_DISP			0x44df2e48
extern reg am437x_cm_ssc_deltamstep_dpll_disp;
#define AM437X_CM_SSC_MODFREQDIV_DPLL_DISP			0x44df2e4c
extern reg am437x_cm_ssc_modfreqdiv_dpll_disp;
#define AM437X_CM_CLKMODE_DPLL_EXTDEV				0x44df2e60
extern reg am437x_cm_clkmode_dpll_extdev;
#define AM437X_CM_IDLEST_DPLL_EXTDEV				0x44df2e64
extern reg am437x_cm_idlest_dpll_extdev;
#define AM437X_CM_CLKSEL_DPLL_EXTDEV				0x44df2e6c
extern reg am437x_cm_clksel_dpll_extdev;
#define AM437X_CM_DIV_M2_DPLL_EXTDEV				0x44df2e70
extern reg am437x_cm_div_m2_dpll_extdev;
#define AM437X_CM_CLKSEL2_DPLL_EXTDEV				0x44df2e84
extern reg am437x_cm_clksel2_dpll_extdev;
#define AM437X_CM_SSC_DELTAMSTEP_DPLL_EXTDEV			0x44df2e88
extern reg am437x_cm_ssc_deltamstep_dpll_extdev;
#define AM437X_CM_SSC_MODFREQDIV_DPLL_EXTDEV			0x44df2e8c
extern reg am437x_cm_ssc_modfreqdiv_dpll_extdev;
#define AM437X_CM_SHADOW_FREQ_CONFIG1				0x44df2fa0
extern reg am437x_cm_shadow_freq_config1;
#define AM437X_CM_SHADOW_FREQ_CONFIG2				0x44df2fa4
extern reg am437x_cm_shadow_freq_config2;
#define AM437X_CM_WKUP_MOD_REGCOUNT				63

typedef enum {
	CM_AM437X_CM_CEFUSE,
	CM_AM437X_CM_DEVICE,
	CM_AM437X_CM_DPLL,
	CM_AM437X_CM_GFX,
	CM_AM437X_CM_MPU,
	CM_AM437X_CM_PER,
	CM_AM437X_CM_RTC,
	CM_AM437X_CM_WKUP,
	CM_AM437X_MODS_COUNT
} cm_am437x_mod_id;

extern reg **cm_am437x_mods[CM_AM437X_MODS_COUNT + 1];

extern const char *cm_am437x_mods_name[CM_AM437X_MODS_COUNT];

#endif
