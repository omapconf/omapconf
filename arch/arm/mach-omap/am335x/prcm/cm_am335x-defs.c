/*
 *
 * @Component			OMAPCONF
 * @Filename			cm_am335x-defs.c
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


#include <cm_am335x-defs.h>
#include <stdio.h>

reg am335x_cm_per_l4ls_clkstctrl = {
	"CM_PER_L4LS_CLKSTCTRL",
	AM335X_CM_PER_L4LS_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_l3s_clkstctrl = {
	"CM_PER_L3S_CLKSTCTRL",
	AM335X_CM_PER_L3S_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_l3_clkstctrl = {
	"CM_PER_L3_CLKSTCTRL",
	AM335X_CM_PER_L3_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_cpgmac0_clkctrl = {
	"CM_PER_CPGMAC0_CLKCTRL",
	AM335X_CM_PER_CPGMAC0_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_lcdc_clkctrl = {
	"CM_PER_LCDC_CLKCTRL",
	AM335X_CM_PER_LCDC_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_usb0_clkctrl = {
	"CM_PER_USB0_CLKCTRL",
	AM335X_CM_PER_USB0_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_tptc0_clkctrl = {
	"CM_PER_TPTC0_CLKCTRL",
	AM335X_CM_PER_TPTC0_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_emif_clkctrl = {
	"CM_PER_EMIF_CLKCTRL",
	AM335X_CM_PER_EMIF_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_ocmcram_clkctrl = {
	"CM_PER_OCMCRAM_CLKCTRL",
	AM335X_CM_PER_OCMCRAM_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_gpmc_clkctrl = {
	"CM_PER_GPMC_CLKCTRL",
	AM335X_CM_PER_GPMC_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_mcasp0_clkctrl = {
	"CM_PER_MCASP0_CLKCTRL",
	AM335X_CM_PER_MCASP0_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_uart5_clkctrl = {
	"CM_PER_UART5_CLKCTRL",
	AM335X_CM_PER_UART5_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_mmc0_clkctrl = {
	"CM_PER_MMC0_CLKCTRL",
	AM335X_CM_PER_MMC0_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_elm_clkctrl = {
	"CM_PER_ELM_CLKCTRL",
	AM335X_CM_PER_ELM_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_i2c2_clkctrl = {
	"CM_PER_I2C2_CLKCTRL",
	AM335X_CM_PER_I2C2_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_i2c1_clkctrl = {
	"CM_PER_I2C1_CLKCTRL",
	AM335X_CM_PER_I2C1_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_spi0_clkctrl = {
	"CM_PER_SPI0_CLKCTRL",
	AM335X_CM_PER_SPI0_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_spi1_clkctrl = {
	"CM_PER_SPI1_CLKCTRL",
	AM335X_CM_PER_SPI1_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_l4ls_clkctrl = {
	"CM_PER_L4LS_CLKCTRL",
	AM335X_CM_PER_L4LS_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_mcasp1_clkctrl = {
	"CM_PER_MCASP1_CLKCTRL",
	AM335X_CM_PER_MCASP1_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_uart1_clkctrl = {
	"CM_PER_UART1_CLKCTRL",
	AM335X_CM_PER_UART1_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_uart2_clkctrl = {
	"CM_PER_UART2_CLKCTRL",
	AM335X_CM_PER_UART2_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_uart3_clkctrl = {
	"CM_PER_UART3_CLKCTRL",
	AM335X_CM_PER_UART3_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_uart4_clkctrl = {
	"CM_PER_UART4_CLKCTRL",
	AM335X_CM_PER_UART4_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_timer7_clkctrl = {
	"CM_PER_TIMER7_CLKCTRL",
	AM335X_CM_PER_TIMER7_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_timer2_clkctrl = {
	"CM_PER_TIMER2_CLKCTRL",
	AM335X_CM_PER_TIMER2_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_timer3_clkctrl = {
	"CM_PER_TIMER3_CLKCTRL",
	AM335X_CM_PER_TIMER3_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_timer4_clkctrl = {
	"CM_PER_TIMER4_CLKCTRL",
	AM335X_CM_PER_TIMER4_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_rng_clkctrl = {
	"CM_PER_RNG_CLKCTRL",
	AM335X_CM_PER_RNG_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_aes0_clkctrl = {
	"CM_PER_AES0_CLKCTRL",
	AM335X_CM_PER_AES0_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_sha0_clkctrl = {
	"CM_PER_SHA0_CLKCTRL",
	AM335X_CM_PER_SHA0_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_gpio1_clkctrl = {
	"CM_PER_GPIO1_CLKCTRL",
	AM335X_CM_PER_GPIO1_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_gpio2_clkctrl = {
	"CM_PER_GPIO2_CLKCTRL",
	AM335X_CM_PER_GPIO2_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_gpio3_clkctrl = {
	"CM_PER_GPIO3_CLKCTRL",
	AM335X_CM_PER_GPIO3_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_tpcc_clkctrl = {
	"CM_PER_TPCC_CLKCTRL",
	AM335X_CM_PER_TPCC_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_dcan0_clkctrl = {
	"CM_PER_DCAN0_CLKCTRL",
	AM335X_CM_PER_DCAN0_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_dcan1_clkctrl = {
	"CM_PER_DCAN1_CLKCTRL",
	AM335X_CM_PER_DCAN1_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_epwmss1_clkctrl = {
	"CM_PER_EPWMSS1_CLKCTRL",
	AM335X_CM_PER_EPWMSS1_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_epwmss0_clkctrl = {
	"CM_PER_EPWMSS0_CLKCTRL",
	AM335X_CM_PER_EPWMSS0_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_epwmss2_clkctrl = {
	"CM_PER_EPWMSS2_CLKCTRL",
	AM335X_CM_PER_EPWMSS2_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_l3_instr_clkctrl = {
	"CM_PER_L3_INSTR_CLKCTRL",
	AM335X_CM_PER_L3_INSTR_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_l3_clkctrl = {
	"CM_PER_L3_CLKCTRL",
	AM335X_CM_PER_L3_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_ieee5000_clkctrl = {
	"CM_PER_IEEE5000_CLKCTRL",
	AM335X_CM_PER_IEEE5000_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_pru_icss_clkctrl = {
	"CM_PER_PRU_ICSS_CLKCTRL",
	AM335X_CM_PER_PRU_ICSS_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_timer5_clkctrl = {
	"CM_PER_TIMER5_CLKCTRL",
	AM335X_CM_PER_TIMER5_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_timer6_clkctrl = {
	"CM_PER_TIMER6_CLKCTRL",
	AM335X_CM_PER_TIMER6_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_mmc1_clkctrl = {
	"CM_PER_MMC1_CLKCTRL",
	AM335X_CM_PER_MMC1_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_mmc2_clkctrl = {
	"CM_PER_MMC2_CLKCTRL",
	AM335X_CM_PER_MMC2_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_tptc1_clkctrl = {
	"CM_PER_TPTC1_CLKCTRL",
	AM335X_CM_PER_TPTC1_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_tptc2_clkctrl = {
	"CM_PER_TPTC2_CLKCTRL",
	AM335X_CM_PER_TPTC2_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_spinlock_clkctrl = {
	"CM_PER_SPINLOCK_CLKCTRL",
	AM335X_CM_PER_SPINLOCK_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_mailbox0_clkctrl = {
	"CM_PER_MAILBOX0_CLKCTRL",
	AM335X_CM_PER_MAILBOX0_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_l4hs_clkstctrl = {
	"CM_PER_L4HS_CLKSTCTRL",
	AM335X_CM_PER_L4HS_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_l4hs_clkctrl = {
	"CM_PER_L4HS_CLKCTRL",
	AM335X_CM_PER_L4HS_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_ocpwp_l3_clkstctrl = {
	"CM_PER_OCPWP_L3_CLKSTCTRL",
	AM335X_CM_PER_OCPWP_L3_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_ocpwp_clkctrl = {
	"CM_PER_OCPWP_CLKCTRL",
	AM335X_CM_PER_OCPWP_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_pru_icss_clkstctrl = {
	"CM_PER_PRU_ICSS_CLKSTCTRL",
	AM335X_CM_PER_PRU_ICSS_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_cpsw_clkstctrl = {
	"CM_PER_CPSW_CLKSTCTRL",
	AM335X_CM_PER_CPSW_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_lcdc_clkstctrl = {
	"CM_PER_LCDC_CLKSTCTRL",
	AM335X_CM_PER_LCDC_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_clkdiv32k_clkctrl = {
	"CM_PER_CLKDIV32K_CLKCTRL",
	AM335X_CM_PER_CLKDIV32K_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_per_clk_24mhz_clkstctrl = {
	"CM_PER_CLK_24MHZ_CLKSTCTRL",
	AM335X_CM_PER_CLK_24MHZ_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg *am335x_cm_per_mod[AM335X_CM_PER_MOD_REGCOUNT + 1] = {
	&am335x_cm_per_l4ls_clkstctrl,
	&am335x_cm_per_l3s_clkstctrl,
	&am335x_cm_per_l3_clkstctrl,
	&am335x_cm_per_cpgmac0_clkctrl,
	&am335x_cm_per_lcdc_clkctrl,
	&am335x_cm_per_usb0_clkctrl,
	&am335x_cm_per_tptc0_clkctrl,
	&am335x_cm_per_emif_clkctrl,
	&am335x_cm_per_ocmcram_clkctrl,
	&am335x_cm_per_gpmc_clkctrl,
	&am335x_cm_per_mcasp0_clkctrl,
	&am335x_cm_per_uart5_clkctrl,
	&am335x_cm_per_mmc0_clkctrl,
	&am335x_cm_per_elm_clkctrl,
	&am335x_cm_per_i2c2_clkctrl,
	&am335x_cm_per_i2c1_clkctrl,
	&am335x_cm_per_spi0_clkctrl,
	&am335x_cm_per_spi1_clkctrl,
	&am335x_cm_per_l4ls_clkctrl,
	&am335x_cm_per_mcasp1_clkctrl,
	&am335x_cm_per_uart1_clkctrl,
	&am335x_cm_per_uart2_clkctrl,
	&am335x_cm_per_uart3_clkctrl,
	&am335x_cm_per_uart4_clkctrl,
	&am335x_cm_per_timer7_clkctrl,
	&am335x_cm_per_timer2_clkctrl,
	&am335x_cm_per_timer3_clkctrl,
	&am335x_cm_per_timer4_clkctrl,
	&am335x_cm_per_rng_clkctrl,
	&am335x_cm_per_aes0_clkctrl,
	&am335x_cm_per_sha0_clkctrl,
	&am335x_cm_per_gpio1_clkctrl,
	&am335x_cm_per_gpio2_clkctrl,
	&am335x_cm_per_gpio3_clkctrl,
	&am335x_cm_per_tpcc_clkctrl,
	&am335x_cm_per_dcan0_clkctrl,
	&am335x_cm_per_dcan1_clkctrl,
	&am335x_cm_per_epwmss1_clkctrl,
	&am335x_cm_per_epwmss0_clkctrl,
	&am335x_cm_per_epwmss2_clkctrl,
	&am335x_cm_per_l3_instr_clkctrl,
	&am335x_cm_per_l3_clkctrl,
	&am335x_cm_per_ieee5000_clkctrl,
	&am335x_cm_per_pru_icss_clkctrl,
	&am335x_cm_per_timer5_clkctrl,
	&am335x_cm_per_timer6_clkctrl,
	&am335x_cm_per_mmc1_clkctrl,
	&am335x_cm_per_mmc2_clkctrl,
	&am335x_cm_per_tptc1_clkctrl,
	&am335x_cm_per_tptc2_clkctrl,
	&am335x_cm_per_spinlock_clkctrl,
	&am335x_cm_per_mailbox0_clkctrl,
	&am335x_cm_per_l4hs_clkstctrl,
	&am335x_cm_per_l4hs_clkctrl,
	&am335x_cm_per_ocpwp_l3_clkstctrl,
	&am335x_cm_per_ocpwp_clkctrl,
	&am335x_cm_per_pru_icss_clkstctrl,
	&am335x_cm_per_cpsw_clkstctrl,
	&am335x_cm_per_lcdc_clkstctrl,
	&am335x_cm_per_clkdiv32k_clkctrl,
	&am335x_cm_per_clk_24mhz_clkstctrl,
	NULL};

reg am335x_cm_wkup_clkstctrl = {
	"CM_WKUP_CLKSTCTRL",
	AM335X_CM_WKUP_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_wkup_control_clkctrl = {
	"CM_WKUP_CONTROL_CLKCTRL",
	AM335X_CM_WKUP_CONTROL_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_wkup_gpio0_clkctrl = {
	"CM_WKUP_GPIO0_CLKCTRL",
	AM335X_CM_WKUP_GPIO0_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_wkup_l4wkup_clkctrl = {
	"CM_WKUP_L4WKUP_CLKCTRL",
	AM335X_CM_WKUP_L4WKUP_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_wkup_timer0_clkctrl = {
	"CM_WKUP_TIMER0_CLKCTRL",
	AM335X_CM_WKUP_TIMER0_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_wkup_debugss_clkctrl = {
	"CM_WKUP_DEBUGSS_CLKCTRL",
	AM335X_CM_WKUP_DEBUGSS_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_l3_aon_clkstctrl = {
	"CM_L3_AON_CLKSTCTRL",
	AM335X_CM_L3_AON_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_autoidle_dpll_mpu = {
	"CM_AUTOIDLE_DPLL_MPU",
	AM335X_CM_AUTOIDLE_DPLL_MPU,
	0xDEADBEEF,
	0};

reg am335x_cm_idlest_dpll_mpu = {
	"CM_IDLEST_DPLL_MPU",
	AM335X_CM_IDLEST_DPLL_MPU,
	0xDEADBEEF,
	0};

reg am335x_cm_ssc_deltamstep_dpll_mpu = {
	"CM_SSC_DELTAMSTEP_DPLL_MPU",
	AM335X_CM_SSC_DELTAMSTEP_DPLL_MPU,
	0xDEADBEEF,
	0};

reg am335x_cm_ssc_modfreqdiv_dpll_mpu = {
	"CM_SSC_MODFREQDIV_DPLL_MPU",
	AM335X_CM_SSC_MODFREQDIV_DPLL_MPU,
	0xDEADBEEF,
	0};

reg am335x_cm_clksel_dpll_mpu = {
	"CM_CLKSEL_DPLL_MPU",
	AM335X_CM_CLKSEL_DPLL_MPU,
	0xDEADBEEF,
	0};

reg am335x_cm_autoidle_dpll_ddr = {
	"CM_AUTOIDLE_DPLL_DDR",
	AM335X_CM_AUTOIDLE_DPLL_DDR,
	0xDEADBEEF,
	0};

reg am335x_cm_idlest_dpll_ddr = {
	"CM_IDLEST_DPLL_DDR",
	AM335X_CM_IDLEST_DPLL_DDR,
	0xDEADBEEF,
	0};

reg am335x_cm_ssc_deltamstep_dpll_ddr = {
	"CM_SSC_DELTAMSTEP_DPLL_DDR",
	AM335X_CM_SSC_DELTAMSTEP_DPLL_DDR,
	0xDEADBEEF,
	0};

reg am335x_cm_ssc_modfreqdiv_dpll_ddr = {
	"CM_SSC_MODFREQDIV_DPLL_DDR",
	AM335X_CM_SSC_MODFREQDIV_DPLL_DDR,
	0xDEADBEEF,
	0};

reg am335x_cm_clksel_dpll_ddr = {
	"CM_CLKSEL_DPLL_DDR",
	AM335X_CM_CLKSEL_DPLL_DDR,
	0xDEADBEEF,
	0};

reg am335x_cm_autoidle_dpll_disp = {
	"CM_AUTOIDLE_DPLL_DISP",
	AM335X_CM_AUTOIDLE_DPLL_DISP,
	0xDEADBEEF,
	0};

reg am335x_cm_idlest_dpll_disp = {
	"CM_IDLEST_DPLL_DISP",
	AM335X_CM_IDLEST_DPLL_DISP,
	0xDEADBEEF,
	0};

reg am335x_cm_ssc_deltamstep_dpll_disp = {
	"CM_SSC_DELTAMSTEP_DPLL_DISP",
	AM335X_CM_SSC_DELTAMSTEP_DPLL_DISP,
	0xDEADBEEF,
	0};

reg am335x_cm_ssc_modfreqdiv_dpll_disp = {
	"CM_SSC_MODFREQDIV_DPLL_DISP",
	AM335X_CM_SSC_MODFREQDIV_DPLL_DISP,
	0xDEADBEEF,
	0};

reg am335x_cm_clksel_dpll_disp = {
	"CM_CLKSEL_DPLL_DISP",
	AM335X_CM_CLKSEL_DPLL_DISP,
	0xDEADBEEF,
	0};

reg am335x_cm_autoidle_dpll_core = {
	"CM_AUTOIDLE_DPLL_CORE",
	AM335X_CM_AUTOIDLE_DPLL_CORE,
	0xDEADBEEF,
	0};

reg am335x_cm_idlest_dpll_core = {
	"CM_IDLEST_DPLL_CORE",
	AM335X_CM_IDLEST_DPLL_CORE,
	0xDEADBEEF,
	0};

reg am335x_cm_ssc_deltamstep_dpll_core = {
	"CM_SSC_DELTAMSTEP_DPLL_CORE",
	AM335X_CM_SSC_DELTAMSTEP_DPLL_CORE,
	0xDEADBEEF,
	0};

reg am335x_cm_ssc_modfreqdiv_dpll_core = {
	"CM_SSC_MODFREQDIV_DPLL_CORE",
	AM335X_CM_SSC_MODFREQDIV_DPLL_CORE,
	0xDEADBEEF,
	0};

reg am335x_cm_clksel_dpll_core = {
	"CM_CLKSEL_DPLL_CORE",
	AM335X_CM_CLKSEL_DPLL_CORE,
	0xDEADBEEF,
	0};

reg am335x_cm_autoidle_dpll_per = {
	"CM_AUTOIDLE_DPLL_PER",
	AM335X_CM_AUTOIDLE_DPLL_PER,
	0xDEADBEEF,
	0};

reg am335x_cm_idlest_dpll_per = {
	"CM_IDLEST_DPLL_PER",
	AM335X_CM_IDLEST_DPLL_PER,
	0xDEADBEEF,
	0};

reg am335x_cm_ssc_deltamstep_dpll_per = {
	"CM_SSC_DELTAMSTEP_DPLL_PER",
	AM335X_CM_SSC_DELTAMSTEP_DPLL_PER,
	0xDEADBEEF,
	0};

reg am335x_cm_ssc_modfreqdiv_dpll_per = {
	"CM_SSC_MODFREQDIV_DPLL_PER",
	AM335X_CM_SSC_MODFREQDIV_DPLL_PER,
	0xDEADBEEF,
	0};

reg am335x_cm_clkdcoldo_dpll_per = {
	"CM_CLKDCOLDO_DPLL_PER",
	AM335X_CM_CLKDCOLDO_DPLL_PER,
	0xDEADBEEF,
	0};

reg am335x_cm_div_m4_dpll_core = {
	"CM_DIV_M4_DPLL_CORE",
	AM335X_CM_DIV_M4_DPLL_CORE,
	0xDEADBEEF,
	0};

reg am335x_cm_div_m5_dpll_core = {
	"CM_DIV_M5_DPLL_CORE",
	AM335X_CM_DIV_M5_DPLL_CORE,
	0xDEADBEEF,
	0};

reg am335x_cm_clkmode_dpll_mpu = {
	"CM_CLKMODE_DPLL_MPU",
	AM335X_CM_CLKMODE_DPLL_MPU,
	0xDEADBEEF,
	0};

reg am335x_cm_clkmode_dpll_per = {
	"CM_CLKMODE_DPLL_PER",
	AM335X_CM_CLKMODE_DPLL_PER,
	0xDEADBEEF,
	0};

reg am335x_cm_clkmode_dpll_core = {
	"CM_CLKMODE_DPLL_CORE",
	AM335X_CM_CLKMODE_DPLL_CORE,
	0xDEADBEEF,
	0};

reg am335x_cm_clkmode_dpll_ddr = {
	"CM_CLKMODE_DPLL_DDR",
	AM335X_CM_CLKMODE_DPLL_DDR,
	0xDEADBEEF,
	0};

reg am335x_cm_clkmode_dpll_disp = {
	"CM_CLKMODE_DPLL_DISP",
	AM335X_CM_CLKMODE_DPLL_DISP,
	0xDEADBEEF,
	0};

reg am335x_cm_clksel_dpll_periph = {
	"CM_CLKSEL_DPLL_PERIPH",
	AM335X_CM_CLKSEL_DPLL_PERIPH,
	0xDEADBEEF,
	0};

reg am335x_cm_div_m2_dpll_ddr = {
	"CM_DIV_M2_DPLL_DDR",
	AM335X_CM_DIV_M2_DPLL_DDR,
	0xDEADBEEF,
	0};

reg am335x_cm_div_m2_dpll_disp = {
	"CM_DIV_M2_DPLL_DISP",
	AM335X_CM_DIV_M2_DPLL_DISP,
	0xDEADBEEF,
	0};

reg am335x_cm_div_m2_dpll_mpu = {
	"CM_DIV_M2_DPLL_MPU",
	AM335X_CM_DIV_M2_DPLL_MPU,
	0xDEADBEEF,
	0};

reg am335x_cm_div_m2_dpll_per = {
	"CM_DIV_M2_DPLL_PER",
	AM335X_CM_DIV_M2_DPLL_PER,
	0xDEADBEEF,
	0};

reg am335x_cm_wkup_wkup_m3_clkctrl = {
	"CM_WKUP_WKUP_M3_CLKCTRL",
	AM335X_CM_WKUP_WKUP_M3_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_wkup_uart0_clkctrl = {
	"CM_WKUP_UART0_CLKCTRL",
	AM335X_CM_WKUP_UART0_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_wkup_i2c0_clkctrl = {
	"CM_WKUP_I2C0_CLKCTRL",
	AM335X_CM_WKUP_I2C0_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_wkup_adc_tsc_clkctrl = {
	"CM_WKUP_ADC_TSC_CLKCTRL",
	AM335X_CM_WKUP_ADC_TSC_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_wkup_smartreflex0_clkctrl = {
	"CM_WKUP_SMARTREFLEX0_CLKCTRL",
	AM335X_CM_WKUP_SMARTREFLEX0_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_wkup_timer1_clkctrl = {
	"CM_WKUP_TIMER1_CLKCTRL",
	AM335X_CM_WKUP_TIMER1_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_wkup_smartreflex1_clkctrl = {
	"CM_WKUP_SMARTREFLEX1_CLKCTRL",
	AM335X_CM_WKUP_SMARTREFLEX1_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_l4_wkup_aon_clkstctrl = {
	"CM_L4_WKUP_AON_CLKSTCTRL",
	AM335X_CM_L4_WKUP_AON_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_wkup_wdt1_clkctrl = {
	"CM_WKUP_WDT1_CLKCTRL",
	AM335X_CM_WKUP_WDT1_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_div_m6_dpll_core = {
	"CM_DIV_M6_DPLL_CORE",
	AM335X_CM_DIV_M6_DPLL_CORE,
	0xDEADBEEF,
	0};

reg *am335x_cm_wkup_mod[AM335X_CM_WKUP_MOD_REGCOUNT + 1] = {
	&am335x_cm_wkup_clkstctrl,
	&am335x_cm_wkup_control_clkctrl,
	&am335x_cm_wkup_gpio0_clkctrl,
	&am335x_cm_wkup_l4wkup_clkctrl,
	&am335x_cm_wkup_timer0_clkctrl,
	&am335x_cm_wkup_debugss_clkctrl,
	&am335x_cm_l3_aon_clkstctrl,
	&am335x_cm_autoidle_dpll_mpu,
	&am335x_cm_idlest_dpll_mpu,
	&am335x_cm_ssc_deltamstep_dpll_mpu,
	&am335x_cm_ssc_modfreqdiv_dpll_mpu,
	&am335x_cm_clksel_dpll_mpu,
	&am335x_cm_autoidle_dpll_ddr,
	&am335x_cm_idlest_dpll_ddr,
	&am335x_cm_ssc_deltamstep_dpll_ddr,
	&am335x_cm_ssc_modfreqdiv_dpll_ddr,
	&am335x_cm_clksel_dpll_ddr,
	&am335x_cm_autoidle_dpll_disp,
	&am335x_cm_idlest_dpll_disp,
	&am335x_cm_ssc_deltamstep_dpll_disp,
	&am335x_cm_ssc_modfreqdiv_dpll_disp,
	&am335x_cm_clksel_dpll_disp,
	&am335x_cm_autoidle_dpll_core,
	&am335x_cm_idlest_dpll_core,
	&am335x_cm_ssc_deltamstep_dpll_core,
	&am335x_cm_ssc_modfreqdiv_dpll_core,
	&am335x_cm_clksel_dpll_core,
	&am335x_cm_autoidle_dpll_per,
	&am335x_cm_idlest_dpll_per,
	&am335x_cm_ssc_deltamstep_dpll_per,
	&am335x_cm_ssc_modfreqdiv_dpll_per,
	&am335x_cm_clkdcoldo_dpll_per,
	&am335x_cm_div_m4_dpll_core,
	&am335x_cm_div_m5_dpll_core,
	&am335x_cm_clkmode_dpll_mpu,
	&am335x_cm_clkmode_dpll_per,
	&am335x_cm_clkmode_dpll_core,
	&am335x_cm_clkmode_dpll_ddr,
	&am335x_cm_clkmode_dpll_disp,
	&am335x_cm_clksel_dpll_periph,
	&am335x_cm_div_m2_dpll_ddr,
	&am335x_cm_div_m2_dpll_disp,
	&am335x_cm_div_m2_dpll_mpu,
	&am335x_cm_div_m2_dpll_per,
	&am335x_cm_wkup_wkup_m3_clkctrl,
	&am335x_cm_wkup_uart0_clkctrl,
	&am335x_cm_wkup_i2c0_clkctrl,
	&am335x_cm_wkup_adc_tsc_clkctrl,
	&am335x_cm_wkup_smartreflex0_clkctrl,
	&am335x_cm_wkup_timer1_clkctrl,
	&am335x_cm_wkup_smartreflex1_clkctrl,
	&am335x_cm_l4_wkup_aon_clkstctrl,
	&am335x_cm_wkup_wdt1_clkctrl,
	&am335x_cm_div_m6_dpll_core,
	NULL};

reg am335x_clksel_timer7_clk = {
	"CLKSEL_TIMER7_CLK",
	AM335X_CLKSEL_TIMER7_CLK,
	0xDEADBEEF,
	0};

reg am335x_clksel_timer2_clk = {
	"CLKSEL_TIMER2_CLK",
	AM335X_CLKSEL_TIMER2_CLK,
	0xDEADBEEF,
	0};

reg am335x_clksel_timer3_clk = {
	"CLKSEL_TIMER3_CLK",
	AM335X_CLKSEL_TIMER3_CLK,
	0xDEADBEEF,
	0};

reg am335x_clksel_timer4_clk = {
	"CLKSEL_TIMER4_CLK",
	AM335X_CLKSEL_TIMER4_CLK,
	0xDEADBEEF,
	0};

reg am335x_cm_mac_clksel = {
	"CM_MAC_CLKSEL",
	AM335X_CM_MAC_CLKSEL,
	0xDEADBEEF,
	0};

reg am335x_clksel_timer5_clk = {
	"CLKSEL_TIMER5_CLK",
	AM335X_CLKSEL_TIMER5_CLK,
	0xDEADBEEF,
	0};

reg am335x_clksel_timer6_clk = {
	"CLKSEL_TIMER6_CLK",
	AM335X_CLKSEL_TIMER6_CLK,
	0xDEADBEEF,
	0};

reg am335x_cm_cpts_rft_clksel = {
	"CM_CPTS_RFT_CLKSEL",
	AM335X_CM_CPTS_RFT_CLKSEL,
	0xDEADBEEF,
	0};

reg am335x_clksel_timer1ms_clk = {
	"CLKSEL_TIMER1MS_CLK",
	AM335X_CLKSEL_TIMER1MS_CLK,
	0xDEADBEEF,
	0};

reg am335x_clksel_gfx_fclk = {
	"CLKSEL_GFX_FCLK",
	AM335X_CLKSEL_GFX_FCLK,
	0xDEADBEEF,
	0};

reg am335x_clksel_pru_icss_ocp_clk = {
	"CLKSEL_PRU_ICSS_OCP_CLK",
	AM335X_CLKSEL_PRU_ICSS_OCP_CLK,
	0xDEADBEEF,
	0};

reg am335x_clksel_lcdc_pixel_clk = {
	"CLKSEL_LCDC_PIXEL_CLK",
	AM335X_CLKSEL_LCDC_PIXEL_CLK,
	0xDEADBEEF,
	0};

reg am335x_clksel_wdt1_clk = {
	"CLKSEL_WDT1_CLK",
	AM335X_CLKSEL_WDT1_CLK,
	0xDEADBEEF,
	0};

reg am335x_clksel_gpio0_dbclk = {
	"CLKSEL_GPIO0_DBCLK",
	AM335X_CLKSEL_GPIO0_DBCLK,
	0xDEADBEEF,
	0};

reg *am335x_cm_dpll_mod[AM335X_CM_DPLL_MOD_REGCOUNT + 1] = {
	&am335x_clksel_timer7_clk,
	&am335x_clksel_timer2_clk,
	&am335x_clksel_timer3_clk,
	&am335x_clksel_timer4_clk,
	&am335x_cm_mac_clksel,
	&am335x_clksel_timer5_clk,
	&am335x_clksel_timer6_clk,
	&am335x_cm_cpts_rft_clksel,
	&am335x_clksel_timer1ms_clk,
	&am335x_clksel_gfx_fclk,
	&am335x_clksel_pru_icss_ocp_clk,
	&am335x_clksel_lcdc_pixel_clk,
	&am335x_clksel_wdt1_clk,
	&am335x_clksel_gpio0_dbclk,
	NULL};

reg am335x_cm_mpu_clkstctrl = {
	"CM_MPU_CLKSTCTRL",
	AM335X_CM_MPU_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_mpu_mpu_clkctrl = {
	"CM_MPU_MPU_CLKCTRL",
	AM335X_CM_MPU_MPU_CLKCTRL,
	0xDEADBEEF,
	0};

reg *am335x_cm_mpu_mod[AM335X_CM_MPU_MOD_REGCOUNT + 1] = {
	&am335x_cm_mpu_clkstctrl,
	&am335x_cm_mpu_mpu_clkctrl,
	NULL};

reg am335x_cm_clkout_ctrl = {
	"CM_CLKOUT_CTRL",
	AM335X_CM_CLKOUT_CTRL,
	0xDEADBEEF,
	0};

reg *am335x_cm_device_mod[AM335X_CM_DEVICE_MOD_REGCOUNT + 1] = {
	&am335x_cm_clkout_ctrl,
	NULL};

reg am335x_cm_rtc_rtc_clkctrl = {
	"CM_RTC_RTC_CLKCTRL",
	AM335X_CM_RTC_RTC_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_rtc_clkstctrl = {
	"CM_RTC_CLKSTCTRL",
	AM335X_CM_RTC_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg *am335x_cm_rtc_mod[AM335X_CM_RTC_MOD_REGCOUNT + 1] = {
	&am335x_cm_rtc_rtc_clkctrl,
	&am335x_cm_rtc_clkstctrl,
	NULL};

reg am335x_cm_gfx_l3_clkstctrl = {
	"CM_GFX_L3_CLKSTCTRL",
	AM335X_CM_GFX_L3_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_gfx_gfx_clkctrl = {
	"CM_GFX_GFX_CLKCTRL",
	AM335X_CM_GFX_GFX_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_gfx_l4ls_gfx_clkstctrl = {
	"CM_GFX_L4LS_GFX_CLKSTCTRL",
	AM335X_CM_GFX_L4LS_GFX_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_gfx_mmucfg_clkctrl = {
	"CM_GFX_MMUCFG_CLKCTRL",
	AM335X_CM_GFX_MMUCFG_CLKCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_gfx_mmudata_clkctrl = {
	"CM_GFX_MMUDATA_CLKCTRL",
	AM335X_CM_GFX_MMUDATA_CLKCTRL,
	0xDEADBEEF,
	0};

reg *am335x_cm_gfx_mod[AM335X_CM_GFX_MOD_REGCOUNT + 1] = {
	&am335x_cm_gfx_l3_clkstctrl,
	&am335x_cm_gfx_gfx_clkctrl,
	&am335x_cm_gfx_l4ls_gfx_clkstctrl,
	&am335x_cm_gfx_mmucfg_clkctrl,
	&am335x_cm_gfx_mmudata_clkctrl,
	NULL};

reg am335x_cm_cefuse_clkstctrl = {
	"CM_CEFUSE_CLKSTCTRL",
	AM335X_CM_CEFUSE_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg am335x_cm_cefuse_cefuse_clkctrl = {
	"CM_CEFUSE_CEFUSE_CLKCTRL",
	AM335X_CM_CEFUSE_CEFUSE_CLKCTRL,
	0xDEADBEEF,
	0};

reg *am335x_cm_cefuse_mod[AM335X_CM_CEFUSE_MOD_REGCOUNT + 1] = {
	&am335x_cm_cefuse_clkstctrl,
	&am335x_cm_cefuse_cefuse_clkctrl,
	NULL};

reg **cm_am335x_mods[CM_AM335X_MODS_COUNT + 1] = {
	(reg **) &am335x_cm_per_mod,
	(reg **) &am335x_cm_wkup_mod,
	(reg **) &am335x_cm_dpll_mod,
	(reg **) &am335x_cm_mpu_mod,
	(reg **) &am335x_cm_device_mod,
	(reg **) &am335x_cm_rtc_mod,
	(reg **) &am335x_cm_gfx_mod,
	(reg **) &am335x_cm_cefuse_mod,
	NULL};

const char *cm_am335x_mods_name[CM_AM335X_MODS_COUNT] = {
	"CM PER",
	"CM WKUP",
	"CM DPLL",
	"CM MPU",
	"CM DEVICE",
	"CM RTC",
	"CM GFX",
	"CM CEFUSE"};


const dpll_settings_regs dpll_am335x_regs[DPLL_AM335X_ID_MAX] = {
	{&am335x_cm_clkmode_dpll_per,
		&am335x_cm_idlest_dpll_per,
		&am335x_cm_autoidle_dpll_per,
		&am335x_cm_clksel_dpll_periph,
		NULL,
		&am335x_cm_div_m2_dpll_per,
		NULL,
		&am335x_cm_ssc_deltamstep_dpll_per,
		&am335x_cm_ssc_modfreqdiv_dpll_per,
		&am335x_cm_clkdcoldo_dpll_per},
	{&am335x_cm_clkmode_dpll_core,
		&am335x_cm_idlest_dpll_core,
		&am335x_cm_autoidle_dpll_core,
		&am335x_cm_clksel_dpll_core,
		NULL, NULL, NULL,
		&am335x_cm_ssc_deltamstep_dpll_core,
		&am335x_cm_ssc_modfreqdiv_dpll_core,
		NULL},
	{&am335x_cm_clkmode_dpll_mpu,
		&am335x_cm_idlest_dpll_mpu,
		&am335x_cm_autoidle_dpll_mpu,
		&am335x_cm_clksel_dpll_mpu,
		NULL,
		&am335x_cm_div_m2_dpll_mpu,
		NULL,
		&am335x_cm_ssc_deltamstep_dpll_mpu,
		&am335x_cm_ssc_modfreqdiv_dpll_mpu,
		NULL},
	{&am335x_cm_clkmode_dpll_ddr,
		&am335x_cm_idlest_dpll_ddr,
		&am335x_cm_autoidle_dpll_ddr,
		&am335x_cm_clksel_dpll_ddr,
		NULL,
		&am335x_cm_div_m2_dpll_ddr,
		NULL,
		&am335x_cm_ssc_deltamstep_dpll_ddr,
		&am335x_cm_ssc_modfreqdiv_dpll_ddr,
		NULL},
	{&am335x_cm_clkmode_dpll_disp,
		&am335x_cm_idlest_dpll_disp,
		&am335x_cm_autoidle_dpll_disp,
		&am335x_cm_clksel_dpll_disp,
		NULL,
		&am335x_cm_div_m2_dpll_disp,
		NULL,
		&am335x_cm_ssc_deltamstep_dpll_disp,
		&am335x_cm_ssc_modfreqdiv_dpll_disp,
		NULL} };

const reg *dpll_am335x_hsdiv_regs[DPLL_AM335X_ID_MAX][HSDIV_AM335X_ID_MAX] = {
	{NULL, NULL, NULL},
	{&am335x_cm_div_m4_dpll_core,
		&am335x_cm_div_m5_dpll_core,
		&am335x_cm_div_m6_dpll_core},
	{NULL, NULL, NULL},
	{NULL, NULL, NULL},
	{NULL, NULL, NULL} };
