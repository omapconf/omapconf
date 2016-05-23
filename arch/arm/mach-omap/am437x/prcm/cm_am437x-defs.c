/*
 *
 * @Component			OMAPCONF
 * @Filename			cm_am437x-defs.c
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


#include <cm_am437x-defs.h>
#include <stdio.h>

reg am437x_cm_cefuse_clkstctrl = {
	"CM_CEFUSE_CLKSTCTRL",
	AM437X_CM_CEFUSE_CLKSTCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_cefuse_clkctrl = {
	"CM_CEFUSE_CLKCTRL",
	AM437X_CM_CEFUSE_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg *am437x_cm_cefuse_mod[AM437X_CM_CEFUSE_MOD_REGCOUNT + 1] = {
	&am437x_cm_cefuse_clkstctrl,
	&am437x_cm_cefuse_clkctrl,
	NULL,
};

reg am437x_cm_clkout1_ctrl = {
	"CM_CLKOUT1_CTRL",
	AM437X_CM_CLKOUT1_CTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_dll_ctrl = {
	"CM_DLL_CTRL",
	AM437X_CM_DLL_CTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_clkout2_ctrl = {
	"CM_CLKOUT2_CTRL",
	AM437X_CM_CLKOUT2_CTRL,
	0xDEADBEEF,
	0,
};

reg *am437x_cm_device_mod[AM437X_CM_DEVICE_MOD_REGCOUNT + 1] = {
	&am437x_cm_clkout1_ctrl,
	&am437x_cm_dll_ctrl,
	&am437x_cm_clkout2_ctrl,
	NULL,
};

reg am437x_cm_dpll_dpll_clksel_timer1_clk = {
	"CM_DPLL_DPLL_CLKSEL_TIMER1_CLK",
	AM437X_CM_DPLL_DPLL_CLKSEL_TIMER1_CLK,
	0xDEADBEEF,
	0,
};

reg am437x_cm_dpll_clksel_timer2_clk = {
	"CM_DPLL_CLKSEL_TIMER2_CLK",
	AM437X_CM_DPLL_CLKSEL_TIMER2_CLK,
	0xDEADBEEF,
	0,
};

reg am437x_cm_dpll_clksel_timer3_clk = {
	"CM_DPLL_CLKSEL_TIMER3_CLK",
	AM437X_CM_DPLL_CLKSEL_TIMER3_CLK,
	0xDEADBEEF,
	0,
};

reg am437x_cm_dpll_clksel_timer4_clk = {
	"CM_DPLL_CLKSEL_TIMER4_CLK",
	AM437X_CM_DPLL_CLKSEL_TIMER4_CLK,
	0xDEADBEEF,
	0,
};

reg am437x_cm_dpll_clksel_timer5_clk = {
	"CM_DPLL_CLKSEL_TIMER5_CLK",
	AM437X_CM_DPLL_CLKSEL_TIMER5_CLK,
	0xDEADBEEF,
	0,
};

reg am437x_cm_dpll_clksel_timer6_clk = {
	"CM_DPLL_CLKSEL_TIMER6_CLK",
	AM437X_CM_DPLL_CLKSEL_TIMER6_CLK,
	0xDEADBEEF,
	0,
};

reg am437x_cm_dpll_clksel_timer7_clk = {
	"CM_DPLL_CLKSEL_TIMER7_CLK",
	AM437X_CM_DPLL_CLKSEL_TIMER7_CLK,
	0xDEADBEEF,
	0,
};

reg am437x_cm_dpll_clksel_timer8_clk = {
	"CM_DPLL_CLKSEL_TIMER8_CLK",
	AM437X_CM_DPLL_CLKSEL_TIMER8_CLK,
	0xDEADBEEF,
	0,
};

reg am437x_cm_dpll_clksel_timer9_clk = {
	"CM_DPLL_CLKSEL_TIMER9_CLK",
	AM437X_CM_DPLL_CLKSEL_TIMER9_CLK,
	0xDEADBEEF,
	0,
};

reg am437x_cm_dpll_clksel_timer10_clk = {
	"CM_DPLL_CLKSEL_TIMER10_CLK",
	AM437X_CM_DPLL_CLKSEL_TIMER10_CLK,
	0xDEADBEEF,
	0,
};

reg am437x_cm_dpll_clksel_timer11_clk = {
	"CM_DPLL_CLKSEL_TIMER11_CLK",
	AM437X_CM_DPLL_CLKSEL_TIMER11_CLK,
	0xDEADBEEF,
	0,
};

reg am437x_cm_dpll_clksel_wdt1_clk = {
	"CM_DPLL_CLKSEL_WDT1_CLK",
	AM437X_CM_DPLL_CLKSEL_WDT1_CLK,
	0xDEADBEEF,
	0,
};

reg am437x_cm_dpll_clksel_synctimer_clk = {
	"CM_DPLL_CLKSEL_SYNCTIMER_CLK",
	AM437X_CM_DPLL_CLKSEL_SYNCTIMER_CLK,
	0xDEADBEEF,
	0,
};

reg am437x_cm_dpll_clksel_mac_clk = {
	"CM_DPLL_CLKSEL_MAC_CLK",
	AM437X_CM_DPLL_CLKSEL_MAC_CLK,
	0xDEADBEEF,
	0,
};

reg am437x_cm_dpll_clksel_cpts_rft_clk = {
	"CM_DPLL_CLKSEL_CPTS_RFT_CLK",
	AM437X_CM_DPLL_CLKSEL_CPTS_RFT_CLK,
	0xDEADBEEF,
	0,
};

reg am437x_cm_dpll_clksel_gfx_fclk = {
	"CM_DPLL_CLKSEL_GFX_FCLK",
	AM437X_CM_DPLL_CLKSEL_GFX_FCLK,
	0xDEADBEEF,
	0,
};

reg am437x_cm_dpll_clksel_gpio0_dbclk = {
	"CM_DPLL_CLKSEL_GPIO0_DBCLK",
	AM437X_CM_DPLL_CLKSEL_GPIO0_DBCLK,
	0xDEADBEEF,
	0,
};

reg am437x_cm_clksel_pru_icss_ocp_clk = {
	"CM_CLKSEL_PRU_ICSS_OCP_CLK",
	AM437X_CM_CLKSEL_PRU_ICSS_OCP_CLK,
	0xDEADBEEF,
	0,
};

reg am437x_cm_clksel_adc1_clk = {
	"CM_CLKSEL_ADC1_CLK",
	AM437X_CM_CLKSEL_ADC1_CLK,
	0xDEADBEEF,
	0,
};

reg am437x_cm_dpll_clksel_dll_aging_clk = {
	"CM_DPLL_CLKSEL_DLL_AGING_CLK",
	AM437X_CM_DPLL_CLKSEL_DLL_AGING_CLK,
	0xDEADBEEF,
	0,
};

reg am437x_cm_dpll_clksel_usbphy32khz_gclk = {
	"CM_DPLL_CLKSEL_USBPHY32KHZ_GCLK",
	AM437X_CM_DPLL_CLKSEL_USBPHY32KHZ_GCLK,
	0xDEADBEEF,
	0,
};

reg *am437x_cm_dpll_mod[AM437X_CM_DPLL_MOD_REGCOUNT + 1] = {
	&am437x_cm_dpll_dpll_clksel_timer1_clk,
	&am437x_cm_dpll_clksel_timer2_clk,
	&am437x_cm_dpll_clksel_timer3_clk,
	&am437x_cm_dpll_clksel_timer4_clk,
	&am437x_cm_dpll_clksel_timer5_clk,
	&am437x_cm_dpll_clksel_timer6_clk,
	&am437x_cm_dpll_clksel_timer7_clk,
	&am437x_cm_dpll_clksel_timer8_clk,
	&am437x_cm_dpll_clksel_timer9_clk,
	&am437x_cm_dpll_clksel_timer10_clk,
	&am437x_cm_dpll_clksel_timer11_clk,
	&am437x_cm_dpll_clksel_wdt1_clk,
	&am437x_cm_dpll_clksel_synctimer_clk,
	&am437x_cm_dpll_clksel_mac_clk,
	&am437x_cm_dpll_clksel_cpts_rft_clk,
	&am437x_cm_dpll_clksel_gfx_fclk,
	&am437x_cm_dpll_clksel_gpio0_dbclk,
	&am437x_cm_clksel_pru_icss_ocp_clk,
	&am437x_cm_clksel_adc1_clk,
	&am437x_cm_dpll_clksel_dll_aging_clk,
	&am437x_cm_dpll_clksel_usbphy32khz_gclk,
	NULL,
};

reg am437x_cm_gfx_l3_clkstctrl = {
	"CM_GFX_L3_CLKSTCTRL",
	AM437X_CM_GFX_L3_CLKSTCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_gfx_clkctrl = {
	"CM_GFX_CLKCTRL",
	AM437X_CM_GFX_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg *am437x_cm_gfx_mod[AM437X_CM_GFX_MOD_REGCOUNT + 1] = {
	&am437x_cm_gfx_l3_clkstctrl,
	&am437x_cm_gfx_clkctrl,
	NULL,
};

reg am437x_cm_mpu_clkstctrl = {
	"CM_MPU_CLKSTCTRL",
	AM437X_CM_MPU_CLKSTCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_mpu_clkctrl = {
	"CM_MPU_CLKCTRL",
	AM437X_CM_MPU_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg *am437x_cm_mpu_mod[AM437X_CM_MPU_MOD_REGCOUNT + 1] = {
	&am437x_cm_mpu_clkstctrl,
	&am437x_cm_mpu_clkctrl,
	NULL,
};

reg am437x_cm_per_l3_clkstctrl = {
	"CM_PER_L3_CLKSTCTRL",
	AM437X_CM_PER_L3_CLKSTCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_l3_clkctrl = {
	"CM_PER_L3_CLKCTRL",
	AM437X_CM_PER_L3_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_aes0_clkctrl = {
	"CM_PER_AES0_CLKCTRL",
	AM437X_CM_PER_AES0_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_des_clkctrl = {
	"CM_PER_DES_CLKCTRL",
	AM437X_CM_PER_DES_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_l3_instr_clkctrl = {
	"CM_PER_L3_INSTR_CLKCTRL",
	AM437X_CM_PER_L3_INSTR_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_ocmcram_clkctrl = {
	"CM_PER_OCMCRAM_CLKCTRL",
	AM437X_CM_PER_OCMCRAM_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_sha0_clkctrl = {
	"CM_PER_SHA0_CLKCTRL",
	AM437X_CM_PER_SHA0_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_vpfe0_clkctrl = {
	"CM_PER_VPFE0_CLKCTRL",
	AM437X_CM_PER_VPFE0_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_vpfe1_clkctrl = {
	"CM_PER_VPFE1_CLKCTRL",
	AM437X_CM_PER_VPFE1_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_tpcc_clkctrl = {
	"CM_PER_TPCC_CLKCTRL",
	AM437X_CM_PER_TPCC_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_tptc0_clkctrl = {
	"CM_PER_TPTC0_CLKCTRL",
	AM437X_CM_PER_TPTC0_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_tptc1_clkctrl = {
	"CM_PER_TPTC1_CLKCTRL",
	AM437X_CM_PER_TPTC1_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_tptc2_clkctrl = {
	"CM_PER_TPTC2_CLKCTRL",
	AM437X_CM_PER_TPTC2_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_dll_aging_clkctrl = {
	"CM_PER_DLL_AGING_CLKCTRL",
	AM437X_CM_PER_DLL_AGING_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_l4hs_clkctrl = {
	"CM_PER_L4HS_CLKCTRL",
	AM437X_CM_PER_L4HS_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_l3s_clkstctrl = {
	"CM_PER_L3S_CLKSTCTRL",
	AM437X_CM_PER_L3S_CLKSTCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_gpmc_clkctrl = {
	"CM_PER_GPMC_CLKCTRL",
	AM437X_CM_PER_GPMC_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_adc1_clkctrl = {
	"CM_PER_ADC1_CLKCTRL",
	AM437X_CM_PER_ADC1_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_mcasp0_clkctrl = {
	"CM_PER_MCASP0_CLKCTRL",
	AM437X_CM_PER_MCASP0_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_mcasp1_clkctrl = {
	"CM_PER_MCASP1_CLKCTRL",
	AM437X_CM_PER_MCASP1_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_mmc2_clkctrl = {
	"CM_PER_MMC2_CLKCTRL",
	AM437X_CM_PER_MMC2_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_qspi_clkctrl = {
	"CM_PER_QSPI_CLKCTRL",
	AM437X_CM_PER_QSPI_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_usb_otg_ss0_clkctrl = {
	"CM_PER_USB_OTG_SS0_CLKCTRL",
	AM437X_CM_PER_USB_OTG_SS0_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_usb_otg_ss1_clkctrl = {
	"CM_PER_USB_OTG_SS1_CLKCTRL",
	AM437X_CM_PER_USB_OTG_SS1_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_pru_icss_clkstctrl = {
	"CM_PER_PRU_ICSS_CLKSTCTRL",
	AM437X_CM_PER_PRU_ICSS_CLKSTCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_pru_icss_clkctrl = {
	"CM_PER_PRU_ICSS_CLKCTRL",
	AM437X_CM_PER_PRU_ICSS_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_l4ls_clkstctrl = {
	"CM_PER_L4LS_CLKSTCTRL",
	AM437X_CM_PER_L4LS_CLKSTCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_l4ls_clkctrl = {
	"CM_PER_L4LS_CLKCTRL",
	AM437X_CM_PER_L4LS_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_dcan0_clkctrl = {
	"CM_PER_DCAN0_CLKCTRL",
	AM437X_CM_PER_DCAN0_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_dcan1_clkctrl = {
	"CM_PER_DCAN1_CLKCTRL",
	AM437X_CM_PER_DCAN1_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_pwmss0_clkctrl = {
	"CM_PER_PWMSS0_CLKCTRL",
	AM437X_CM_PER_PWMSS0_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_pwmss1_clkctrl = {
	"CM_PER_PWMSS1_CLKCTRL",
	AM437X_CM_PER_PWMSS1_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_pwmss2_clkctrl = {
	"CM_PER_PWMSS2_CLKCTRL",
	AM437X_CM_PER_PWMSS2_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_pwmss3_clkctrl = {
	"CM_PER_PWMSS3_CLKCTRL",
	AM437X_CM_PER_PWMSS3_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_pwmss4_clkctrl = {
	"CM_PER_PWMSS4_CLKCTRL",
	AM437X_CM_PER_PWMSS4_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_pwmss5_clkctrl = {
	"CM_PER_PWMSS5_CLKCTRL",
	AM437X_CM_PER_PWMSS5_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_elm_clkctrl = {
	"CM_PER_ELM_CLKCTRL",
	AM437X_CM_PER_ELM_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_gpio1_clkctrl = {
	"CM_PER_GPIO1_CLKCTRL",
	AM437X_CM_PER_GPIO1_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_gpio2_clkctrl = {
	"CM_PER_GPIO2_CLKCTRL",
	AM437X_CM_PER_GPIO2_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_gpio3_clkctrl = {
	"CM_PER_GPIO3_CLKCTRL",
	AM437X_CM_PER_GPIO3_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_gpio4_clkctrl = {
	"CM_PER_GPIO4_CLKCTRL",
	AM437X_CM_PER_GPIO4_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_gpio5_clkctrl = {
	"CM_PER_GPIO5_CLKCTRL",
	AM437X_CM_PER_GPIO5_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_hdq1w_clkctrl = {
	"CM_PER_HDQ1W_CLKCTRL",
	AM437X_CM_PER_HDQ1W_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_i2c1_clkctrl = {
	"CM_PER_I2C1_CLKCTRL",
	AM437X_CM_PER_I2C1_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_i2c2_clkctrl = {
	"CM_PER_I2C2_CLKCTRL",
	AM437X_CM_PER_I2C2_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_mailbox0_clkctrl = {
	"CM_PER_MAILBOX0_CLKCTRL",
	AM437X_CM_PER_MAILBOX0_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_mmc0_clkctrl = {
	"CM_PER_MMC0_CLKCTRL",
	AM437X_CM_PER_MMC0_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_mmc1_clkctrl = {
	"CM_PER_MMC1_CLKCTRL",
	AM437X_CM_PER_MMC1_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_rng_clkctrl = {
	"CM_PER_RNG_CLKCTRL",
	AM437X_CM_PER_RNG_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_spi0_clkctrl = {
	"CM_PER_SPI0_CLKCTRL",
	AM437X_CM_PER_SPI0_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_spi1_clkctrl = {
	"CM_PER_SPI1_CLKCTRL",
	AM437X_CM_PER_SPI1_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_spi2_clkctrl = {
	"CM_PER_SPI2_CLKCTRL",
	AM437X_CM_PER_SPI2_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_spi3_clkctrl = {
	"CM_PER_SPI3_CLKCTRL",
	AM437X_CM_PER_SPI3_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_spi4_clkctrl = {
	"CM_PER_SPI4_CLKCTRL",
	AM437X_CM_PER_SPI4_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_spinlock_clkctrl = {
	"CM_PER_SPINLOCK_CLKCTRL",
	AM437X_CM_PER_SPINLOCK_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_timer2_clkctrl = {
	"CM_PER_TIMER2_CLKCTRL",
	AM437X_CM_PER_TIMER2_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_timer3_clkctrl = {
	"CM_PER_TIMER3_CLKCTRL",
	AM437X_CM_PER_TIMER3_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_timer4_clkctrl = {
	"CM_PER_TIMER4_CLKCTRL",
	AM437X_CM_PER_TIMER4_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_timer5_clkctrl = {
	"CM_PER_TIMER5_CLKCTRL",
	AM437X_CM_PER_TIMER5_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_timer6_clkctrl = {
	"CM_PER_TIMER6_CLKCTRL",
	AM437X_CM_PER_TIMER6_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_timer7_clkctrl = {
	"CM_PER_TIMER7_CLKCTRL",
	AM437X_CM_PER_TIMER7_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_timer8_clkctrl = {
	"CM_PER_TIMER8_CLKCTRL",
	AM437X_CM_PER_TIMER8_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_timer9_clkctrl = {
	"CM_PER_TIMER9_CLKCTRL",
	AM437X_CM_PER_TIMER9_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_timer10_clkctrl = {
	"CM_PER_TIMER10_CLKCTRL",
	AM437X_CM_PER_TIMER10_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_timer11_clkctrl = {
	"CM_PER_TIMER11_CLKCTRL",
	AM437X_CM_PER_TIMER11_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_uart1_clkctrl = {
	"CM_PER_UART1_CLKCTRL",
	AM437X_CM_PER_UART1_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_uart2_clkctrl = {
	"CM_PER_UART2_CLKCTRL",
	AM437X_CM_PER_UART2_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_uart3_clkctrl = {
	"CM_PER_UART3_CLKCTRL",
	AM437X_CM_PER_UART3_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_uart4_clkctrl = {
	"CM_PER_UART4_CLKCTRL",
	AM437X_CM_PER_UART4_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_uart5_clkctrl = {
	"CM_PER_UART5_CLKCTRL",
	AM437X_CM_PER_UART5_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_usbphyocp2scp0_clkctrl = {
	"CM_PER_USBPHYOCP2SCP0_CLKCTRL",
	AM437X_CM_PER_USBPHYOCP2SCP0_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_usbphyocp2scp1_clkctrl = {
	"CM_PER_USBPHYOCP2SCP1_CLKCTRL",
	AM437X_CM_PER_USBPHYOCP2SCP1_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_emif_clkstctrl = {
	"CM_PER_EMIF_CLKSTCTRL",
	AM437X_CM_PER_EMIF_CLKSTCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_emif_clkctrl = {
	"CM_PER_EMIF_CLKCTRL",
	AM437X_CM_PER_EMIF_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_dll_clkctrl = {
	"CM_PER_DLL_CLKCTRL",
	AM437X_CM_PER_DLL_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_lcdc_clkstctrl = {
	"CM_PER_LCDC_CLKSTCTRL",
	AM437X_CM_PER_LCDC_CLKSTCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_dss_clkstctrl = {
	"CM_PER_DSS_CLKSTCTRL",
	AM437X_CM_PER_DSS_CLKSTCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_dss_clkctrl = {
	"CM_PER_DSS_CLKCTRL",
	AM437X_CM_PER_DSS_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_cpsw_clkstctrl = {
	"CM_PER_CPSW_CLKSTCTRL",
	AM437X_CM_PER_CPSW_CLKSTCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_cpgmac0_clkctrl = {
	"CM_PER_CPGMAC0_CLKCTRL",
	AM437X_CM_PER_CPGMAC0_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_ocpwp_l3_clkstctrl = {
	"CM_PER_OCPWP_L3_CLKSTCTRL",
	AM437X_CM_PER_OCPWP_L3_CLKSTCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_per_ocpwp_clkctrl = {
	"CM_PER_OCPWP_CLKCTRL",
	AM437X_CM_PER_OCPWP_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg *am437x_cm_per_mod[AM437X_CM_PER_MOD_REGCOUNT + 1] = {
	&am437x_cm_per_l3_clkstctrl,
	&am437x_cm_per_l3_clkctrl,
	&am437x_cm_per_aes0_clkctrl,
	&am437x_cm_per_des_clkctrl,
	&am437x_cm_per_l3_instr_clkctrl,
	&am437x_cm_per_ocmcram_clkctrl,
	&am437x_cm_per_sha0_clkctrl,
	&am437x_cm_per_vpfe0_clkctrl,
	&am437x_cm_per_vpfe1_clkctrl,
	&am437x_cm_per_tpcc_clkctrl,
	&am437x_cm_per_tptc0_clkctrl,
	&am437x_cm_per_tptc1_clkctrl,
	&am437x_cm_per_tptc2_clkctrl,
	&am437x_cm_per_dll_aging_clkctrl,
	&am437x_cm_per_l4hs_clkctrl,
	&am437x_cm_per_l3s_clkstctrl,
	&am437x_cm_per_gpmc_clkctrl,
	&am437x_cm_per_adc1_clkctrl,
	&am437x_cm_per_mcasp0_clkctrl,
	&am437x_cm_per_mcasp1_clkctrl,
	&am437x_cm_per_mmc2_clkctrl,
	&am437x_cm_per_qspi_clkctrl,
	&am437x_cm_per_usb_otg_ss0_clkctrl,
	&am437x_cm_per_usb_otg_ss1_clkctrl,
	&am437x_cm_per_pru_icss_clkstctrl,
	&am437x_cm_per_pru_icss_clkctrl,
	&am437x_cm_per_l4ls_clkstctrl,
	&am437x_cm_per_l4ls_clkctrl,
	&am437x_cm_per_dcan0_clkctrl,
	&am437x_cm_per_dcan1_clkctrl,
	&am437x_cm_per_pwmss0_clkctrl,
	&am437x_cm_per_pwmss1_clkctrl,
	&am437x_cm_per_pwmss2_clkctrl,
	&am437x_cm_per_pwmss3_clkctrl,
	&am437x_cm_per_pwmss4_clkctrl,
	&am437x_cm_per_pwmss5_clkctrl,
	&am437x_cm_per_elm_clkctrl,
	&am437x_cm_per_gpio1_clkctrl,
	&am437x_cm_per_gpio2_clkctrl,
	&am437x_cm_per_gpio3_clkctrl,
	&am437x_cm_per_gpio4_clkctrl,
	&am437x_cm_per_gpio5_clkctrl,
	&am437x_cm_per_hdq1w_clkctrl,
	&am437x_cm_per_i2c1_clkctrl,
	&am437x_cm_per_i2c2_clkctrl,
	&am437x_cm_per_mailbox0_clkctrl,
	&am437x_cm_per_mmc0_clkctrl,
	&am437x_cm_per_mmc1_clkctrl,
	&am437x_cm_per_rng_clkctrl,
	&am437x_cm_per_spi0_clkctrl,
	&am437x_cm_per_spi1_clkctrl,
	&am437x_cm_per_spi2_clkctrl,
	&am437x_cm_per_spi3_clkctrl,
	&am437x_cm_per_spi4_clkctrl,
	&am437x_cm_per_spinlock_clkctrl,
	&am437x_cm_per_timer2_clkctrl,
	&am437x_cm_per_timer3_clkctrl,
	&am437x_cm_per_timer4_clkctrl,
	&am437x_cm_per_timer5_clkctrl,
	&am437x_cm_per_timer6_clkctrl,
	&am437x_cm_per_timer7_clkctrl,
	&am437x_cm_per_timer8_clkctrl,
	&am437x_cm_per_timer9_clkctrl,
	&am437x_cm_per_timer10_clkctrl,
	&am437x_cm_per_timer11_clkctrl,
	&am437x_cm_per_uart1_clkctrl,
	&am437x_cm_per_uart2_clkctrl,
	&am437x_cm_per_uart3_clkctrl,
	&am437x_cm_per_uart4_clkctrl,
	&am437x_cm_per_uart5_clkctrl,
	&am437x_cm_per_usbphyocp2scp0_clkctrl,
	&am437x_cm_per_usbphyocp2scp1_clkctrl,
	&am437x_cm_per_emif_clkstctrl,
	&am437x_cm_per_emif_clkctrl,
	&am437x_cm_per_dll_clkctrl,
	&am437x_cm_per_lcdc_clkstctrl,
	&am437x_cm_per_dss_clkstctrl,
	&am437x_cm_per_dss_clkctrl,
	&am437x_cm_per_cpsw_clkstctrl,
	&am437x_cm_per_cpgmac0_clkctrl,
	&am437x_cm_per_ocpwp_l3_clkstctrl,
	&am437x_cm_per_ocpwp_clkctrl,
	NULL,
};

reg am437x_cm_rtc_clkstctrl = {
	"CM_RTC_CLKSTCTRL",
	AM437X_CM_RTC_CLKSTCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_rtc_clkctrl = {
	"CM_RTC_CLKCTRL",
	AM437X_CM_RTC_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg *am437x_cm_rtc_mod[AM437X_CM_RTC_MOD_REGCOUNT + 1] = {
	&am437x_cm_rtc_clkstctrl,
	&am437x_cm_rtc_clkctrl,
	NULL,
};

reg am437x_cm_l3_aon_clkstctrl = {
	"CM_L3_AON_CLKSTCTRL",
	AM437X_CM_L3_AON_CLKSTCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_wkup_dbgss_clkctrl = {
	"CM_WKUP_DBGSS_CLKCTRL",
	AM437X_CM_WKUP_DBGSS_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_l3s_adc0_clkstctrl = {
	"CM_L3S_ADC0_CLKSTCTRL",
	AM437X_CM_L3S_ADC0_CLKSTCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_wkup_adc0_clkctrl = {
	"CM_WKUP_ADC0_CLKCTRL",
	AM437X_CM_WKUP_ADC0_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_l4_wkup_aon_clkstctrl = {
	"CM_L4_WKUP_AON_CLKSTCTRL",
	AM437X_CM_L4_WKUP_AON_CLKSTCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_wkup_l4wkup_clkctrl = {
	"CM_WKUP_L4WKUP_CLKCTRL",
	AM437X_CM_WKUP_L4WKUP_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_wkup_proc_clkctrl = {
	"CM_WKUP_PROC_CLKCTRL",
	AM437X_CM_WKUP_PROC_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_wkup_synctimer_clkctrl = {
	"CM_WKUP_SYNCTIMER_CLKCTRL",
	AM437X_CM_WKUP_SYNCTIMER_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_wkup_clkdiv32k_clkctrl = {
	"CM_WKUP_CLKDIV32K_CLKCTRL",
	AM437X_CM_WKUP_CLKDIV32K_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_wkup_usbphy0_clkctrl = {
	"CM_WKUP_USBPHY0_CLKCTRL",
	AM437X_CM_WKUP_USBPHY0_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_wkup_usbphy1_clkctrl = {
	"CM_WKUP_USBPHY1_CLKCTRL",
	AM437X_CM_WKUP_USBPHY1_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_wkup_clkstctrl = {
	"CM_WKUP_CLKSTCTRL",
	AM437X_CM_WKUP_CLKSTCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_wkup_timer0_clkctrl = {
	"CM_WKUP_TIMER0_CLKCTRL",
	AM437X_CM_WKUP_TIMER0_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_wkup_timer1_clkctrl = {
	"CM_WKUP_TIMER1_CLKCTRL",
	AM437X_CM_WKUP_TIMER1_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_wkup_wdt1_clkctrl = {
	"CM_WKUP_WDT1_CLKCTRL",
	AM437X_CM_WKUP_WDT1_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_wkup_i2c0_clkctrl = {
	"CM_WKUP_I2C0_CLKCTRL",
	AM437X_CM_WKUP_I2C0_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_wkup_uart0_clkctrl = {
	"CM_WKUP_UART0_CLKCTRL",
	AM437X_CM_WKUP_UART0_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_wkup_ctrl_clkctrl = {
	"CM_WKUP_CTRL_CLKCTRL",
	AM437X_CM_WKUP_CTRL_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_wkup_gpio0_clkctrl = {
	"CM_WKUP_GPIO0_CLKCTRL",
	AM437X_CM_WKUP_GPIO0_CLKCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_cm_clkmode_dpll_core = {
	"CM_CLKMODE_DPLL_CORE",
	AM437X_CM_CLKMODE_DPLL_CORE,
	0xDEADBEEF,
	0,
};

reg am437x_cm_idlest_dpll_core = {
	"CM_IDLEST_DPLL_CORE",
	AM437X_CM_IDLEST_DPLL_CORE,
	0xDEADBEEF,
	0,
};

reg am437x_cm_clksel_dpll_core = {
	"CM_CLKSEL_DPLL_CORE",
	AM437X_CM_CLKSEL_DPLL_CORE,
	0xDEADBEEF,
	0,
};

reg am437x_cm_div_m4_dpll_core = {
	"CM_DIV_M4_DPLL_CORE",
	AM437X_CM_DIV_M4_DPLL_CORE,
	0xDEADBEEF,
	0,
};

reg am437x_cm_div_m5_dpll_core = {
	"CM_DIV_M5_DPLL_CORE",
	AM437X_CM_DIV_M5_DPLL_CORE,
	0xDEADBEEF,
	0,
};

reg am437x_cm_div_m6_dpll_core = {
	"CM_DIV_M6_DPLL_CORE",
	AM437X_CM_DIV_M6_DPLL_CORE,
	0xDEADBEEF,
	0,
};

reg am437x_cm_ssc_deltamstep_dpll_core = {
	"CM_SSC_DELTAMSTEP_DPLL_CORE",
	AM437X_CM_SSC_DELTAMSTEP_DPLL_CORE,
	0xDEADBEEF,
	0,
};

reg am437x_cm_ssc_modfreqdiv_dpll_core = {
	"CM_SSC_MODFREQDIV_DPLL_CORE",
	AM437X_CM_SSC_MODFREQDIV_DPLL_CORE,
	0xDEADBEEF,
	0,
};

reg am437x_cm_clkmode_dpll_mpu = {
	"CM_CLKMODE_DPLL_MPU",
	AM437X_CM_CLKMODE_DPLL_MPU,
	0xDEADBEEF,
	0,
};

reg am437x_cm_idlest_dpll_mpu = {
	"CM_IDLEST_DPLL_MPU",
	AM437X_CM_IDLEST_DPLL_MPU,
	0xDEADBEEF,
	0,
};

reg am437x_cm_clksel_dpll_mpu = {
	"CM_CLKSEL_DPLL_MPU",
	AM437X_CM_CLKSEL_DPLL_MPU,
	0xDEADBEEF,
	0,
};

reg am437x_cm_div_m2_dpll_mpu = {
	"CM_DIV_M2_DPLL_MPU",
	AM437X_CM_DIV_M2_DPLL_MPU,
	0xDEADBEEF,
	0,
};

reg am437x_cm_ssc_deltamstep_dpll_mpu = {
	"CM_SSC_DELTAMSTEP_DPLL_MPU",
	AM437X_CM_SSC_DELTAMSTEP_DPLL_MPU,
	0xDEADBEEF,
	0,
};

reg am437x_cm_ssc_modfreqdiv_dpll_mpu = {
	"CM_SSC_MODFREQDIV_DPLL_MPU",
	AM437X_CM_SSC_MODFREQDIV_DPLL_MPU,
	0xDEADBEEF,
	0,
};

reg am437x_cm_clkmode_dpll_ddr = {
	"CM_CLKMODE_DPLL_DDR",
	AM437X_CM_CLKMODE_DPLL_DDR,
	0xDEADBEEF,
	0,
};

reg am437x_cm_idlest_dpll_ddr = {
	"CM_IDLEST_DPLL_DDR",
	AM437X_CM_IDLEST_DPLL_DDR,
	0xDEADBEEF,
	0,
};

reg am437x_cm_clksel_dpll_ddr = {
	"CM_CLKSEL_DPLL_DDR",
	AM437X_CM_CLKSEL_DPLL_DDR,
	0xDEADBEEF,
	0,
};

reg am437x_cm_div_m2_dpll_ddr = {
	"CM_DIV_M2_DPLL_DDR",
	AM437X_CM_DIV_M2_DPLL_DDR,
	0xDEADBEEF,
	0,
};

reg am437x_cm_div_m4_dpll_ddr = {
	"CM_DIV_M4_DPLL_DDR",
	AM437X_CM_DIV_M4_DPLL_DDR,
	0xDEADBEEF,
	0,
};

reg am437x_cm_ssc_deltamstep_dpll_ddr = {
	"CM_SSC_DELTAMSTEP_DPLL_DDR",
	AM437X_CM_SSC_DELTAMSTEP_DPLL_DDR,
	0xDEADBEEF,
	0,
};

reg am437x_cm_ssc_modfreqdiv_dpll_ddr = {
	"CM_SSC_MODFREQDIV_DPLL_DDR",
	AM437X_CM_SSC_MODFREQDIV_DPLL_DDR,
	0xDEADBEEF,
	0,
};

reg am437x_cm_clkmode_dpll_per = {
	"CM_CLKMODE_DPLL_PER",
	AM437X_CM_CLKMODE_DPLL_PER,
	0xDEADBEEF,
	0,
};

reg am437x_cm_idlest_dpll_per = {
	"CM_IDLEST_DPLL_PER",
	AM437X_CM_IDLEST_DPLL_PER,
	0xDEADBEEF,
	0,
};

reg am437x_cm_clksel_dpll_per = {
	"CM_CLKSEL_DPLL_PER",
	AM437X_CM_CLKSEL_DPLL_PER,
	0xDEADBEEF,
	0,
};

reg am437x_cm_div_m2_dpll_per = {
	"CM_DIV_M2_DPLL_PER",
	AM437X_CM_DIV_M2_DPLL_PER,
	0xDEADBEEF,
	0,
};

reg am437x_cm_clksel2_dpll_per = {
	"CM_CLKSEL2_DPLL_PER",
	AM437X_CM_CLKSEL2_DPLL_PER,
	0xDEADBEEF,
	0,
};

reg am437x_cm_ssc_deltamstep_dpll_per = {
	"CM_SSC_DELTAMSTEP_DPLL_PER",
	AM437X_CM_SSC_DELTAMSTEP_DPLL_PER,
	0xDEADBEEF,
	0,
};

reg am437x_cm_ssc_modfreqdiv_dpll_per = {
	"CM_SSC_MODFREQDIV_DPLL_PER",
	AM437X_CM_SSC_MODFREQDIV_DPLL_PER,
	0xDEADBEEF,
	0,
};

reg am437x_cm_clkdcoldo_dpll_per = {
	"CM_CLKDCOLDO_DPLL_PER",
	AM437X_CM_CLKDCOLDO_DPLL_PER,
	0xDEADBEEF,
	0,
};

reg am437x_cm_clkmode_dpll_disp = {
	"CM_CLKMODE_DPLL_DISP",
	AM437X_CM_CLKMODE_DPLL_DISP,
	0xDEADBEEF,
	0,
};

reg am437x_cm_idlest_dpll_disp = {
	"CM_IDLEST_DPLL_DISP",
	AM437X_CM_IDLEST_DPLL_DISP,
	0xDEADBEEF,
	0,
};

reg am437x_cm_clksel_dpll_disp = {
	"CM_CLKSEL_DPLL_DISP",
	AM437X_CM_CLKSEL_DPLL_DISP,
	0xDEADBEEF,
	0,
};

reg am437x_cm_div_m2_dpll_disp = {
	"CM_DIV_M2_DPLL_DISP",
	AM437X_CM_DIV_M2_DPLL_DISP,
	0xDEADBEEF,
	0,
};

reg am437x_cm_ssc_deltamstep_dpll_disp = {
	"CM_SSC_DELTAMSTEP_DPLL_DISP",
	AM437X_CM_SSC_DELTAMSTEP_DPLL_DISP,
	0xDEADBEEF,
	0,
};

reg am437x_cm_ssc_modfreqdiv_dpll_disp = {
	"CM_SSC_MODFREQDIV_DPLL_DISP",
	AM437X_CM_SSC_MODFREQDIV_DPLL_DISP,
	0xDEADBEEF,
	0,
};

reg am437x_cm_clkmode_dpll_extdev = {
	"CM_CLKMODE_DPLL_EXTDEV",
	AM437X_CM_CLKMODE_DPLL_EXTDEV,
	0xDEADBEEF,
	0,
};

reg am437x_cm_idlest_dpll_extdev = {
	"CM_IDLEST_DPLL_EXTDEV",
	AM437X_CM_IDLEST_DPLL_EXTDEV,
	0xDEADBEEF,
	0,
};

reg am437x_cm_clksel_dpll_extdev = {
	"CM_CLKSEL_DPLL_EXTDEV",
	AM437X_CM_CLKSEL_DPLL_EXTDEV,
	0xDEADBEEF,
	0,
};

reg am437x_cm_div_m2_dpll_extdev = {
	"CM_DIV_M2_DPLL_EXTDEV",
	AM437X_CM_DIV_M2_DPLL_EXTDEV,
	0xDEADBEEF,
	0,
};

reg am437x_cm_clksel2_dpll_extdev = {
	"CM_CLKSEL2_DPLL_EXTDEV",
	AM437X_CM_CLKSEL2_DPLL_EXTDEV,
	0xDEADBEEF,
	0,
};

reg am437x_cm_ssc_deltamstep_dpll_extdev = {
	"CM_SSC_DELTAMSTEP_DPLL_EXTDEV",
	AM437X_CM_SSC_DELTAMSTEP_DPLL_EXTDEV,
	0xDEADBEEF,
	0,
};

reg am437x_cm_ssc_modfreqdiv_dpll_extdev = {
	"CM_SSC_MODFREQDIV_DPLL_EXTDEV",
	AM437X_CM_SSC_MODFREQDIV_DPLL_EXTDEV,
	0xDEADBEEF,
	0,
};

reg am437x_cm_shadow_freq_config1 = {
	"CM_SHADOW_FREQ_CONFIG1",
	AM437X_CM_SHADOW_FREQ_CONFIG1,
	0xDEADBEEF,
	0,
};

reg am437x_cm_shadow_freq_config2 = {
	"CM_SHADOW_FREQ_CONFIG2",
	AM437X_CM_SHADOW_FREQ_CONFIG2,
	0xDEADBEEF,
	0,
};

reg *am437x_cm_wkup_mod[AM437X_CM_WKUP_MOD_REGCOUNT + 1] = {
	&am437x_cm_l3_aon_clkstctrl,
	&am437x_cm_wkup_dbgss_clkctrl,
	&am437x_cm_l3s_adc0_clkstctrl,
	&am437x_cm_wkup_adc0_clkctrl,
	&am437x_cm_l4_wkup_aon_clkstctrl,
	&am437x_cm_wkup_l4wkup_clkctrl,
	&am437x_cm_wkup_proc_clkctrl,
	&am437x_cm_wkup_synctimer_clkctrl,
	&am437x_cm_wkup_clkdiv32k_clkctrl,
	&am437x_cm_wkup_usbphy0_clkctrl,
	&am437x_cm_wkup_usbphy1_clkctrl,
	&am437x_cm_wkup_clkstctrl,
	&am437x_cm_wkup_timer0_clkctrl,
	&am437x_cm_wkup_timer1_clkctrl,
	&am437x_cm_wkup_wdt1_clkctrl,
	&am437x_cm_wkup_i2c0_clkctrl,
	&am437x_cm_wkup_uart0_clkctrl,
	&am437x_cm_wkup_ctrl_clkctrl,
	&am437x_cm_wkup_gpio0_clkctrl,
	&am437x_cm_clkmode_dpll_core,
	&am437x_cm_idlest_dpll_core,
	&am437x_cm_clksel_dpll_core,
	&am437x_cm_div_m4_dpll_core,
	&am437x_cm_div_m5_dpll_core,
	&am437x_cm_div_m6_dpll_core,
	&am437x_cm_ssc_deltamstep_dpll_core,
	&am437x_cm_ssc_modfreqdiv_dpll_core,
	&am437x_cm_clkmode_dpll_mpu,
	&am437x_cm_idlest_dpll_mpu,
	&am437x_cm_clksel_dpll_mpu,
	&am437x_cm_div_m2_dpll_mpu,
	&am437x_cm_ssc_deltamstep_dpll_mpu,
	&am437x_cm_ssc_modfreqdiv_dpll_mpu,
	&am437x_cm_clkmode_dpll_ddr,
	&am437x_cm_idlest_dpll_ddr,
	&am437x_cm_clksel_dpll_ddr,
	&am437x_cm_div_m2_dpll_ddr,
	&am437x_cm_div_m4_dpll_ddr,
	&am437x_cm_ssc_deltamstep_dpll_ddr,
	&am437x_cm_ssc_modfreqdiv_dpll_ddr,
	&am437x_cm_clkmode_dpll_per,
	&am437x_cm_idlest_dpll_per,
	&am437x_cm_clksel_dpll_per,
	&am437x_cm_div_m2_dpll_per,
	&am437x_cm_clksel2_dpll_per,
	&am437x_cm_ssc_deltamstep_dpll_per,
	&am437x_cm_ssc_modfreqdiv_dpll_per,
	&am437x_cm_clkdcoldo_dpll_per,
	&am437x_cm_clkmode_dpll_disp,
	&am437x_cm_idlest_dpll_disp,
	&am437x_cm_clksel_dpll_disp,
	&am437x_cm_div_m2_dpll_disp,
	&am437x_cm_ssc_deltamstep_dpll_disp,
	&am437x_cm_ssc_modfreqdiv_dpll_disp,
	&am437x_cm_clkmode_dpll_extdev,
	&am437x_cm_idlest_dpll_extdev,
	&am437x_cm_clksel_dpll_extdev,
	&am437x_cm_div_m2_dpll_extdev,
	&am437x_cm_clksel2_dpll_extdev,
	&am437x_cm_ssc_deltamstep_dpll_extdev,
	&am437x_cm_ssc_modfreqdiv_dpll_extdev,
	&am437x_cm_shadow_freq_config1,
	&am437x_cm_shadow_freq_config2,
	NULL,
};

reg **cm_am437x_mods[CM_AM437X_MODS_COUNT + 1] = {
	(reg **) &am437x_cm_cefuse_mod,
	(reg **) &am437x_cm_device_mod,
	(reg **) &am437x_cm_dpll_mod,
	(reg **) &am437x_cm_gfx_mod,
	(reg **) &am437x_cm_mpu_mod,
	(reg **) &am437x_cm_per_mod,
	(reg **) &am437x_cm_rtc_mod,
	(reg **) &am437x_cm_wkup_mod,
	NULL,
};

const char *cm_am437x_mods_name[CM_AM437X_MODS_COUNT] = {
	"CM CEFUSE",
	"CM DEVICE",
	"CM DPLL",
	"CM GFX",
	"CM MPU",
	"CM PER",
	"CM RTC",
	"CM WKUP",
};
