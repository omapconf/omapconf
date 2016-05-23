/*
 *
 * @Component			OMAPCONF
 * @Filename			prm_am437x-defs.c
 * @Description			AM437X PRM Register Definitions & Functions
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

#include <prm_am437x-defs.h>
#include <stdio.h>

reg am437x_pm_cefuse_pwrstctrl = {
	"PM_CEFUSE_PWRSTCTRL",
	AM437X_PM_CEFUSE_PWRSTCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_pm_cefuse_pwrstst = {
	"PM_CEFUSE_PWRSTST",
	AM437X_PM_CEFUSE_PWRSTST,
	0xDEADBEEF,
	0,
};

reg am437x_rm_cefuse_context = {
	"RM_CEFUSE_CONTEXT",
	AM437X_RM_CEFUSE_CONTEXT,
	0xDEADBEEF,
	0,
};

reg *am437x_prm_cefuse_mod[AM437X_PRM_CEFUSE_MOD_REGCOUNT + 1] = {
	&am437x_pm_cefuse_pwrstctrl,
	&am437x_pm_cefuse_pwrstst,
	&am437x_rm_cefuse_context,
	NULL,
};

reg am437x_prm_rstctrl = {
	"PRM_RSTCTRL",
	AM437X_PRM_RSTCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_prm_rstst = {
	"PRM_RSTST",
	AM437X_PRM_RSTST,
	0xDEADBEEF,
	0,
};

reg am437x_prm_rsttime = {
	"PRM_RSTTIME",
	AM437X_PRM_RSTTIME,
	0xDEADBEEF,
	0,
};

reg am437x_prm_sram_count = {
	"PRM_SRAM_COUNT",
	AM437X_PRM_SRAM_COUNT,
	0xDEADBEEF,
	0,
};

reg am437x_prm_ldo_sram_core_setup = {
	"PRM_LDO_SRAM_CORE_SETUP",
	AM437X_PRM_LDO_SRAM_CORE_SETUP,
	0xDEADBEEF,
	0,
};

reg am437x_prm_ldo_sram_core_ctrl = {
	"PRM_LDO_SRAM_CORE_CTRL",
	AM437X_PRM_LDO_SRAM_CORE_CTRL,
	0xDEADBEEF,
	0,
};

reg am437x_prm_ldo_sram_mpu_setup = {
	"PRM_LDO_SRAM_MPU_SETUP",
	AM437X_PRM_LDO_SRAM_MPU_SETUP,
	0xDEADBEEF,
	0,
};

reg am437x_prm_ldo_sram_mpu_ctrl = {
	"PRM_LDO_SRAM_MPU_CTRL",
	AM437X_PRM_LDO_SRAM_MPU_CTRL,
	0xDEADBEEF,
	0,
};

reg am437x_prm_io_count = {
	"PRM_IO_COUNT",
	AM437X_PRM_IO_COUNT,
	0xDEADBEEF,
	0,
};

reg am437x_prm_io_pmctrl = {
	"PRM_IO_PMCTRL",
	AM437X_PRM_IO_PMCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_prm_vc_val_bypass = {
	"PRM_VC_VAL_BYPASS",
	AM437X_PRM_VC_VAL_BYPASS,
	0xDEADBEEF,
	0,
};

reg am437x_prm_emif_ctrl = {
	"PRM_EMIF_CTRL",
	AM437X_PRM_EMIF_CTRL,
	0xDEADBEEF,
	0,
};

reg *am437x_prm_device_mod[AM437X_PRM_DEVICE_MOD_REGCOUNT + 1] = {
	&am437x_prm_rstctrl,
	&am437x_prm_rstst,
	&am437x_prm_rsttime,
	&am437x_prm_sram_count,
	&am437x_prm_ldo_sram_core_setup,
	&am437x_prm_ldo_sram_core_ctrl,
	&am437x_prm_ldo_sram_mpu_setup,
	&am437x_prm_ldo_sram_mpu_ctrl,
	&am437x_prm_io_count,
	&am437x_prm_io_pmctrl,
	&am437x_prm_vc_val_bypass,
	&am437x_prm_emif_ctrl,
	NULL,
};

reg am437x_prm_pm_gfx_pwrstctrl = {
	"PRM_PM_GFX_PWRSTCTRL",
	AM437X_PRM_PM_GFX_PWRSTCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_prm_pm_gfx_pwrstst = {
	"PRM_PM_GFX_PWRSTST",
	AM437X_PRM_PM_GFX_PWRSTST,
	0xDEADBEEF,
	0,
};

reg am437x_prm_rm_gfx_rstctrl = {
	"PRM_RM_GFX_RSTCTRL",
	AM437X_PRM_RM_GFX_RSTCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_prm_rm_gfx_rstst = {
	"PRM_RM_GFX_RSTST",
	AM437X_PRM_RM_GFX_RSTST,
	0xDEADBEEF,
	0,
};

reg am437x_prm_rm_gfx_context = {
	"PRM_RM_GFX_CONTEXT",
	AM437X_PRM_RM_GFX_CONTEXT,
	0xDEADBEEF,
	0,
};

reg *am437x_prm_gfx_mod[AM437X_PRM_GFX_MOD_REGCOUNT + 1] = {
	&am437x_prm_pm_gfx_pwrstctrl,
	&am437x_prm_pm_gfx_pwrstst,
	&am437x_prm_rm_gfx_rstctrl,
	&am437x_prm_rm_gfx_rstst,
	&am437x_prm_rm_gfx_context,
	NULL,
};

reg am437x_pm_mpu_pwrstctrl = {
	"PM_MPU_PWRSTCTRL",
	AM437X_PM_MPU_PWRSTCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_pm_mpu_pwrstst = {
	"PM_MPU_PWRSTST",
	AM437X_PM_MPU_PWRSTST,
	0xDEADBEEF,
	0,
};

reg am437x_rm_mpu_rstst = {
	"RM_MPU_RSTST",
	AM437X_RM_MPU_RSTST,
	0xDEADBEEF,
	0,
};

reg am437x_rm_mpu_context = {
	"RM_MPU_CONTEXT",
	AM437X_RM_MPU_CONTEXT,
	0xDEADBEEF,
	0,
};

reg *am437x_prm_mpu_mod[AM437X_PRM_MPU_MOD_REGCOUNT + 1] = {
	&am437x_pm_mpu_pwrstctrl,
	&am437x_pm_mpu_pwrstst,
	&am437x_rm_mpu_rstst,
	&am437x_rm_mpu_context,
	NULL,
};

reg am437x_pm_per_pwrstctrl = {
	"PM_PER_PWRSTCTRL",
	AM437X_PM_PER_PWRSTCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_pm_per_pwrstst = {
	"PM_PER_PWRSTST",
	AM437X_PM_PER_PWRSTST,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_rstctrl = {
	"RM_PER_RSTCTRL",
	AM437X_RM_PER_RSTCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_rstst = {
	"RM_PER_RSTST",
	AM437X_RM_PER_RSTST,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_l3_context = {
	"RM_PER_L3_CONTEXT",
	AM437X_RM_PER_L3_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_aes0_context = {
	"RM_PER_AES0_CONTEXT",
	AM437X_RM_PER_AES0_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_des_context = {
	"RM_PER_DES_CONTEXT",
	AM437X_RM_PER_DES_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_l3_instr_context = {
	"RM_PER_L3_INSTR_CONTEXT",
	AM437X_RM_PER_L3_INSTR_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_ocmcram_context = {
	"RM_PER_OCMCRAM_CONTEXT",
	AM437X_RM_PER_OCMCRAM_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_sha0_context = {
	"RM_PER_SHA0_CONTEXT",
	AM437X_RM_PER_SHA0_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_vpfe0_context = {
	"RM_PER_VPFE0_CONTEXT",
	AM437X_RM_PER_VPFE0_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_vpfe1_context = {
	"RM_PER_VPFE1_CONTEXT",
	AM437X_RM_PER_VPFE1_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_tpcc_context = {
	"RM_PER_TPCC_CONTEXT",
	AM437X_RM_PER_TPCC_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_tptc0_context = {
	"RM_PER_TPTC0_CONTEXT",
	AM437X_RM_PER_TPTC0_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_tptc1_context = {
	"RM_PER_TPTC1_CONTEXT",
	AM437X_RM_PER_TPTC1_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_tptc2_context = {
	"RM_PER_TPTC2_CONTEXT",
	AM437X_RM_PER_TPTC2_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_dll_aging_context = {
	"RM_PER_DLL_AGING_CONTEXT",
	AM437X_RM_PER_DLL_AGING_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_l4hs_context = {
	"RM_PER_L4HS_CONTEXT",
	AM437X_RM_PER_L4HS_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_gpmc_context = {
	"RM_PER_GPMC_CONTEXT",
	AM437X_RM_PER_GPMC_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_adc1_context = {
	"RM_PER_ADC1_CONTEXT",
	AM437X_RM_PER_ADC1_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_mcasp0_context = {
	"RM_PER_MCASP0_CONTEXT",
	AM437X_RM_PER_MCASP0_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_mcasp1_context = {
	"RM_PER_MCASP1_CONTEXT",
	AM437X_RM_PER_MCASP1_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_mmc2_context = {
	"RM_PER_MMC2_CONTEXT",
	AM437X_RM_PER_MMC2_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_qspi_context = {
	"RM_PER_QSPI_CONTEXT",
	AM437X_RM_PER_QSPI_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_usb_otg_ss0_context = {
	"RM_PER_USB_OTG_SS0_CONTEXT",
	AM437X_RM_PER_USB_OTG_SS0_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_usb_otg_ss1_context = {
	"RM_PER_USB_OTG_SS1_CONTEXT",
	AM437X_RM_PER_USB_OTG_SS1_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_pru_icss_context = {
	"RM_PER_PRU_ICSS_CONTEXT",
	AM437X_RM_PER_PRU_ICSS_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_l4ls_context = {
	"RM_PER_L4LS_CONTEXT",
	AM437X_RM_PER_L4LS_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_dcan0_context = {
	"RM_PER_DCAN0_CONTEXT",
	AM437X_RM_PER_DCAN0_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_dcan1_context = {
	"RM_PER_DCAN1_CONTEXT",
	AM437X_RM_PER_DCAN1_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_pwmss0_context = {
	"RM_PER_PWMSS0_CONTEXT",
	AM437X_RM_PER_PWMSS0_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_pwmss1_context = {
	"RM_PER_PWMSS1_CONTEXT",
	AM437X_RM_PER_PWMSS1_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_pwmss2_context = {
	"RM_PER_PWMSS2_CONTEXT",
	AM437X_RM_PER_PWMSS2_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_pwmss3_context = {
	"RM_PER_PWMSS3_CONTEXT",
	AM437X_RM_PER_PWMSS3_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_pwmss4_context = {
	"RM_PER_PWMSS4_CONTEXT",
	AM437X_RM_PER_PWMSS4_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_pwmss5_context = {
	"RM_PER_PWMSS5_CONTEXT",
	AM437X_RM_PER_PWMSS5_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_elm_context = {
	"RM_PER_ELM_CONTEXT",
	AM437X_RM_PER_ELM_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_gpio1_context = {
	"RM_PER_GPIO1_CONTEXT",
	AM437X_RM_PER_GPIO1_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_gpio2_context = {
	"RM_PER_GPIO2_CONTEXT",
	AM437X_RM_PER_GPIO2_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_gpio3_context = {
	"RM_PER_GPIO3_CONTEXT",
	AM437X_RM_PER_GPIO3_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_gpio4_context = {
	"RM_PER_GPIO4_CONTEXT",
	AM437X_RM_PER_GPIO4_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_gpio5_context = {
	"RM_PER_GPIO5_CONTEXT",
	AM437X_RM_PER_GPIO5_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_hdq1w_context = {
	"RM_PER_HDQ1W_CONTEXT",
	AM437X_RM_PER_HDQ1W_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_i2c1_context = {
	"RM_PER_I2C1_CONTEXT",
	AM437X_RM_PER_I2C1_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_i2c2_context = {
	"RM_PER_I2C2_CONTEXT",
	AM437X_RM_PER_I2C2_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_mailbox0_context = {
	"RM_PER_MAILBOX0_CONTEXT",
	AM437X_RM_PER_MAILBOX0_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_mmc0_context = {
	"RM_PER_MMC0_CONTEXT",
	AM437X_RM_PER_MMC0_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_mmc1_context = {
	"RM_PER_MMC1_CONTEXT",
	AM437X_RM_PER_MMC1_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_rng_context = {
	"RM_PER_RNG_CONTEXT",
	AM437X_RM_PER_RNG_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_spi0_context = {
	"RM_PER_SPI0_CONTEXT",
	AM437X_RM_PER_SPI0_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_spi1_context = {
	"RM_PER_SPI1_CONTEXT",
	AM437X_RM_PER_SPI1_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_spi2_context = {
	"RM_PER_SPI2_CONTEXT",
	AM437X_RM_PER_SPI2_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_spi3_context = {
	"RM_PER_SPI3_CONTEXT",
	AM437X_RM_PER_SPI3_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_spi4_context = {
	"RM_PER_SPI4_CONTEXT",
	AM437X_RM_PER_SPI4_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_spinlock_context = {
	"RM_PER_SPINLOCK_CONTEXT",
	AM437X_RM_PER_SPINLOCK_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_timer2_context = {
	"RM_PER_TIMER2_CONTEXT",
	AM437X_RM_PER_TIMER2_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_timer3_context = {
	"RM_PER_TIMER3_CONTEXT",
	AM437X_RM_PER_TIMER3_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_timer4_context = {
	"RM_PER_TIMER4_CONTEXT",
	AM437X_RM_PER_TIMER4_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_timer5_context = {
	"RM_PER_TIMER5_CONTEXT",
	AM437X_RM_PER_TIMER5_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_timer6_context = {
	"RM_PER_TIMER6_CONTEXT",
	AM437X_RM_PER_TIMER6_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_timer7_context = {
	"RM_PER_TIMER7_CONTEXT",
	AM437X_RM_PER_TIMER7_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_timer8_context = {
	"RM_PER_TIMER8_CONTEXT",
	AM437X_RM_PER_TIMER8_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_timer9_context = {
	"RM_PER_TIMER9_CONTEXT",
	AM437X_RM_PER_TIMER9_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_timer10_context = {
	"RM_PER_TIMER10_CONTEXT",
	AM437X_RM_PER_TIMER10_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_timer11_context = {
	"RM_PER_TIMER11_CONTEXT",
	AM437X_RM_PER_TIMER11_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_uart1_context = {
	"RM_PER_UART1_CONTEXT",
	AM437X_RM_PER_UART1_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_uart2_context = {
	"RM_PER_UART2_CONTEXT",
	AM437X_RM_PER_UART2_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_uart3_context = {
	"RM_PER_UART3_CONTEXT",
	AM437X_RM_PER_UART3_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_uart4_context = {
	"RM_PER_UART4_CONTEXT",
	AM437X_RM_PER_UART4_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_uart5_context = {
	"RM_PER_UART5_CONTEXT",
	AM437X_RM_PER_UART5_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_usbphyocp2scp0_context = {
	"RM_PER_USBPHYOCP2SCP0_CONTEXT",
	AM437X_RM_PER_USBPHYOCP2SCP0_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_usbphyocp2scp1_context = {
	"RM_PER_USBPHYOCP2SCP1_CONTEXT",
	AM437X_RM_PER_USBPHYOCP2SCP1_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_emif_context = {
	"RM_PER_EMIF_CONTEXT",
	AM437X_RM_PER_EMIF_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_dll_context = {
	"RM_PER_DLL_CONTEXT",
	AM437X_RM_PER_DLL_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_dss_context = {
	"RM_PER_DSS_CONTEXT",
	AM437X_RM_PER_DSS_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_cpgmac0_context = {
	"RM_PER_CPGMAC0_CONTEXT",
	AM437X_RM_PER_CPGMAC0_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_per_ocpwp_context = {
	"RM_PER_OCPWP_CONTEXT",
	AM437X_RM_PER_OCPWP_CONTEXT,
	0xDEADBEEF,
	0,
};

reg *am437x_prm_per_mod[AM437X_PRM_PER_MOD_REGCOUNT + 1] = {
	&am437x_pm_per_pwrstctrl,
	&am437x_pm_per_pwrstst,
	&am437x_rm_per_rstctrl,
	&am437x_rm_per_rstst,
	&am437x_rm_per_l3_context,
	&am437x_rm_per_aes0_context,
	&am437x_rm_per_des_context,
	&am437x_rm_per_l3_instr_context,
	&am437x_rm_per_ocmcram_context,
	&am437x_rm_per_sha0_context,
	&am437x_rm_per_vpfe0_context,
	&am437x_rm_per_vpfe1_context,
	&am437x_rm_per_tpcc_context,
	&am437x_rm_per_tptc0_context,
	&am437x_rm_per_tptc1_context,
	&am437x_rm_per_tptc2_context,
	&am437x_rm_per_dll_aging_context,
	&am437x_rm_per_l4hs_context,
	&am437x_rm_per_gpmc_context,
	&am437x_rm_per_adc1_context,
	&am437x_rm_per_mcasp0_context,
	&am437x_rm_per_mcasp1_context,
	&am437x_rm_per_mmc2_context,
	&am437x_rm_per_qspi_context,
	&am437x_rm_per_usb_otg_ss0_context,
	&am437x_rm_per_usb_otg_ss1_context,
	&am437x_rm_per_pru_icss_context,
	&am437x_rm_per_l4ls_context,
	&am437x_rm_per_dcan0_context,
	&am437x_rm_per_dcan1_context,
	&am437x_rm_per_pwmss0_context,
	&am437x_rm_per_pwmss1_context,
	&am437x_rm_per_pwmss2_context,
	&am437x_rm_per_pwmss3_context,
	&am437x_rm_per_pwmss4_context,
	&am437x_rm_per_pwmss5_context,
	&am437x_rm_per_elm_context,
	&am437x_rm_per_gpio1_context,
	&am437x_rm_per_gpio2_context,
	&am437x_rm_per_gpio3_context,
	&am437x_rm_per_gpio4_context,
	&am437x_rm_per_gpio5_context,
	&am437x_rm_per_hdq1w_context,
	&am437x_rm_per_i2c1_context,
	&am437x_rm_per_i2c2_context,
	&am437x_rm_per_mailbox0_context,
	&am437x_rm_per_mmc0_context,
	&am437x_rm_per_mmc1_context,
	&am437x_rm_per_rng_context,
	&am437x_rm_per_spi0_context,
	&am437x_rm_per_spi1_context,
	&am437x_rm_per_spi2_context,
	&am437x_rm_per_spi3_context,
	&am437x_rm_per_spi4_context,
	&am437x_rm_per_spinlock_context,
	&am437x_rm_per_timer2_context,
	&am437x_rm_per_timer3_context,
	&am437x_rm_per_timer4_context,
	&am437x_rm_per_timer5_context,
	&am437x_rm_per_timer6_context,
	&am437x_rm_per_timer7_context,
	&am437x_rm_per_timer8_context,
	&am437x_rm_per_timer9_context,
	&am437x_rm_per_timer10_context,
	&am437x_rm_per_timer11_context,
	&am437x_rm_per_uart1_context,
	&am437x_rm_per_uart2_context,
	&am437x_rm_per_uart3_context,
	&am437x_rm_per_uart4_context,
	&am437x_rm_per_uart5_context,
	&am437x_rm_per_usbphyocp2scp0_context,
	&am437x_rm_per_usbphyocp2scp1_context,
	&am437x_rm_per_emif_context,
	&am437x_rm_per_dll_context,
	&am437x_rm_per_dss_context,
	&am437x_rm_per_cpgmac0_context,
	&am437x_rm_per_ocpwp_context,
	NULL,
};

reg am437x_rm_rtc_context = {
	"RM_RTC_CONTEXT",
	AM437X_RM_RTC_CONTEXT,
	0xDEADBEEF,
	0,
};

reg *am437x_prm_rtc_mod[AM437X_PRM_RTC_MOD_REGCOUNT + 1] = {
	&am437x_rm_rtc_context,
	NULL,
};

reg am437x_rm_wkup_rstctrl = {
	"RM_WKUP_RSTCTRL",
	AM437X_RM_WKUP_RSTCTRL,
	0xDEADBEEF,
	0,
};

reg am437x_rm_wkup_rstst = {
	"RM_WKUP_RSTST",
	AM437X_RM_WKUP_RSTST,
	0xDEADBEEF,
	0,
};

reg am437x_rm_wkup_dbgss_context = {
	"RM_WKUP_DBGSS_CONTEXT",
	AM437X_RM_WKUP_DBGSS_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_wkup_adc0_context = {
	"RM_WKUP_ADC0_CONTEXT",
	AM437X_RM_WKUP_ADC0_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_wkup_l4wkup_context = {
	"RM_WKUP_L4WKUP_CONTEXT",
	AM437X_RM_WKUP_L4WKUP_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_wkup_proc_context = {
	"RM_WKUP_PROC_CONTEXT",
	AM437X_RM_WKUP_PROC_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_wkup_synctimer_context = {
	"RM_WKUP_SYNCTIMER_CONTEXT",
	AM437X_RM_WKUP_SYNCTIMER_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_wkup_timer0_context = {
	"RM_WKUP_TIMER0_CONTEXT",
	AM437X_RM_WKUP_TIMER0_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_wkup_timer1_context = {
	"RM_WKUP_TIMER1_CONTEXT",
	AM437X_RM_WKUP_TIMER1_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_wkup_wdt1_context = {
	"RM_WKUP_WDT1_CONTEXT",
	AM437X_RM_WKUP_WDT1_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_wkup_i2c0_context = {
	"RM_WKUP_I2C0_CONTEXT",
	AM437X_RM_WKUP_I2C0_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_wkup_uart0_context = {
	"RM_WKUP_UART0_CONTEXT",
	AM437X_RM_WKUP_UART0_CONTEXT,
	0xDEADBEEF,
	0,
};

reg am437x_rm_wkup_gpio0_context = {
	"RM_WKUP_GPIO0_CONTEXT",
	AM437X_RM_WKUP_GPIO0_CONTEXT,
	0xDEADBEEF,
	0,
};

reg *am437x_prm_wkup_mod[AM437X_PRM_WKUP_MOD_REGCOUNT + 1] = {
	&am437x_rm_wkup_rstctrl,
	&am437x_rm_wkup_rstst,
	&am437x_rm_wkup_dbgss_context,
	&am437x_rm_wkup_adc0_context,
	&am437x_rm_wkup_l4wkup_context,
	&am437x_rm_wkup_proc_context,
	&am437x_rm_wkup_synctimer_context,
	&am437x_rm_wkup_timer0_context,
	&am437x_rm_wkup_timer1_context,
	&am437x_rm_wkup_wdt1_context,
	&am437x_rm_wkup_i2c0_context,
	&am437x_rm_wkup_uart0_context,
	&am437x_rm_wkup_gpio0_context,
	NULL,
};

reg am437x_prm_revision = {
	"PRM_REVISION",
	AM437X_PRM_REVISION,
	0xDEADBEEF,
	0,
};

reg am437x_prm_irqsts_mpu = {
	"PRM_IRQSTS_MPU",
	AM437X_PRM_IRQSTS_MPU,
	0xDEADBEEF,
	0,
};

reg am437x_prm_irqen_mpu = {
	"PRM_IRQEN_MPU",
	AM437X_PRM_IRQEN_MPU,
	0xDEADBEEF,
	0,
};

reg am437x_prm_irqsts_wkup_proc = {
	"PRM_IRQSTS_WKUP_PROC",
	AM437X_PRM_IRQSTS_WKUP_PROC,
	0xDEADBEEF,
	0,
};

reg am437x_prm_irqen_wkup_proc = {
	"PRM_IRQEN_WKUP_PROC",
	AM437X_PRM_IRQEN_WKUP_PROC,
	0xDEADBEEF,
	0,
};

reg *am437x_prm_irq_mod[AM437X_PRM_IRQ_MOD_REGCOUNT + 1] = {
	&am437x_prm_revision,
	&am437x_prm_irqsts_mpu,
	&am437x_prm_irqen_mpu,
	&am437x_prm_irqsts_wkup_proc,
	&am437x_prm_irqen_wkup_proc,
	NULL,
};

reg **prm_am437x_mods[PRM_AM437X_MODS_COUNT + 1] = {
	(reg **) &am437x_prm_cefuse_mod,
	(reg **) &am437x_prm_device_mod,
	(reg **) &am437x_prm_gfx_mod,
	(reg **) &am437x_prm_mpu_mod,
	(reg **) &am437x_prm_per_mod,
	(reg **) &am437x_prm_rtc_mod,
	(reg **) &am437x_prm_wkup_mod,
	(reg **) &am437x_prm_irq_mod,
	NULL,
};

const char *prm_am437x_mods_name[PRM_AM437X_MODS_COUNT] = {
	"PRM CEFUSE",
	"PRM DEVICE",
	"PRM GFX",
	"PRM MPU",
	"PRM PER",
	"PRM RTC",
	"PRM WKUP",
	"PRM IRQ",
};
