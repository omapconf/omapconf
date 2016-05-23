/*
 *
 * @Component			OMAPCONF
 * @Filename			prm_am437x-defs.h
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

#ifndef __PRM_AM437X_DEFS_H__
#define __PRM_AM437X_DEFS_H__

#include <reg.h>

/* PRM_CEFUSE Registers */
#define AM437X_PM_CEFUSE_PWRSTCTRL				0x44df0700
extern reg am437x_pm_cefuse_pwrstctrl;
#define AM437X_PM_CEFUSE_PWRSTST				0x44df0704
extern reg am437x_pm_cefuse_pwrstst;
#define AM437X_RM_CEFUSE_CONTEXT				0x44df0724
extern reg am437x_rm_cefuse_context;
#define AM437X_PRM_CEFUSE_MOD_REGCOUNT				3
extern reg *am437x_prm_cefuse_mod[AM437X_PRM_CEFUSE_MOD_REGCOUNT + 1];

/* PRM_DEVICE Registers */
#define AM437X_PRM_RSTCTRL					0x44df4000
extern reg am437x_prm_rstctrl;
#define AM437X_PRM_RSTST					0x44df4004
extern reg am437x_prm_rstst;
#define AM437X_PRM_RSTTIME					0x44df4008
extern reg am437x_prm_rsttime;
#define AM437X_PRM_SRAM_COUNT					0x44df400c
extern reg am437x_prm_sram_count;
#define AM437X_PRM_LDO_SRAM_CORE_SETUP				0x44df4010
extern reg am437x_prm_ldo_sram_core_setup;
#define AM437X_PRM_LDO_SRAM_CORE_CTRL				0x44df4014
extern reg am437x_prm_ldo_sram_core_ctrl;
#define AM437X_PRM_LDO_SRAM_MPU_SETUP				0x44df4018
extern reg am437x_prm_ldo_sram_mpu_setup;
#define AM437X_PRM_LDO_SRAM_MPU_CTRL				0x44df401c
extern reg am437x_prm_ldo_sram_mpu_ctrl;
#define AM437X_PRM_IO_COUNT					0x44df4020
extern reg am437x_prm_io_count;
#define AM437X_PRM_IO_PMCTRL					0x44df4024
extern reg am437x_prm_io_pmctrl;
#define AM437X_PRM_VC_VAL_BYPASS				0x44df4028
extern reg am437x_prm_vc_val_bypass;
#define AM437X_PRM_EMIF_CTRL					0x44df4030
extern reg am437x_prm_emif_ctrl;
#define AM437X_PRM_DEVICE_MOD_REGCOUNT				12
extern reg *am437x_prm_device_mod[AM437X_PRM_DEVICE_MOD_REGCOUNT + 1];

/* PRM_GFX Registers */
#define AM437X_PRM_PM_GFX_PWRSTCTRL				0x44df0400
extern reg am437x_prm_pm_gfx_pwrstctrl;
#define AM437X_PRM_PM_GFX_PWRSTST				0x44df0404
extern reg am437x_prm_pm_gfx_pwrstst;
#define AM437X_PRM_RM_GFX_RSTCTRL				0x44df0410
extern reg am437x_prm_rm_gfx_rstctrl;
#define AM437X_PRM_RM_GFX_RSTST					0x44df0414
extern reg am437x_prm_rm_gfx_rstst;
#define AM437X_PRM_RM_GFX_CONTEXT				0x44df0424
extern reg am437x_prm_rm_gfx_context;
#define AM437X_PRM_GFX_MOD_REGCOUNT				5
extern reg *am437x_prm_gfx_mod[AM437X_PRM_GFX_MOD_REGCOUNT + 1];

/* PRM_MPU Registers */
#define AM437X_PM_MPU_PWRSTCTRL					0x44df0300
extern reg am437x_pm_mpu_pwrstctrl;
#define AM437X_PM_MPU_PWRSTST					0x44df0304
extern reg am437x_pm_mpu_pwrstst;
#define AM437X_RM_MPU_RSTST					0x44df0314
extern reg am437x_rm_mpu_rstst;
#define AM437X_RM_MPU_CONTEXT					0x44df0324
extern reg am437x_rm_mpu_context;
#define AM437X_PRM_MPU_MOD_REGCOUNT				4
extern reg *am437x_prm_mpu_mod[AM437X_PRM_MPU_MOD_REGCOUNT + 1];

/* PRM_PER Registers */
#define AM437X_PM_PER_PWRSTCTRL					0x44df0800
extern reg am437x_pm_per_pwrstctrl;
#define AM437X_PM_PER_PWRSTST					0x44df0804
extern reg am437x_pm_per_pwrstst;
#define AM437X_RM_PER_RSTCTRL					0x44df0810
extern reg am437x_rm_per_rstctrl;
#define AM437X_RM_PER_RSTST					0x44df0814
extern reg am437x_rm_per_rstst;
#define AM437X_RM_PER_L3_CONTEXT				0x44df0824
extern reg am437x_rm_per_l3_context;
#define AM437X_RM_PER_AES0_CONTEXT				0x44df082c
extern reg am437x_rm_per_aes0_context;
#define AM437X_RM_PER_DES_CONTEXT				0x44df0834
extern reg am437x_rm_per_des_context;
#define AM437X_RM_PER_L3_INSTR_CONTEXT				0x44df0844
extern reg am437x_rm_per_l3_instr_context;
#define AM437X_RM_PER_OCMCRAM_CONTEXT				0x44df0854
extern reg am437x_rm_per_ocmcram_context;
#define AM437X_RM_PER_SHA0_CONTEXT				0x44df085c
extern reg am437x_rm_per_sha0_context;
#define AM437X_RM_PER_VPFE0_CONTEXT				0x44df086c
extern reg am437x_rm_per_vpfe0_context;
#define AM437X_RM_PER_VPFE1_CONTEXT				0x44df0874
extern reg am437x_rm_per_vpfe1_context;
#define AM437X_RM_PER_TPCC_CONTEXT				0x44df087c
extern reg am437x_rm_per_tpcc_context;
#define AM437X_RM_PER_TPTC0_CONTEXT				0x44df0884
extern reg am437x_rm_per_tptc0_context;
#define AM437X_RM_PER_TPTC1_CONTEXT				0x44df088c
extern reg am437x_rm_per_tptc1_context;
#define AM437X_RM_PER_TPTC2_CONTEXT				0x44df0894
extern reg am437x_rm_per_tptc2_context;
#define AM437X_RM_PER_DLL_AGING_CONTEXT				0x44df089c
extern reg am437x_rm_per_dll_aging_context;
#define AM437X_RM_PER_L4HS_CONTEXT				0x44df08a4
extern reg am437x_rm_per_l4hs_context;
#define AM437X_RM_PER_GPMC_CONTEXT				0x44df0a24
extern reg am437x_rm_per_gpmc_context;
#define AM437X_RM_PER_ADC1_CONTEXT				0x44df0a34
extern reg am437x_rm_per_adc1_context;
#define AM437X_RM_PER_MCASP0_CONTEXT				0x44df0a3c
extern reg am437x_rm_per_mcasp0_context;
#define AM437X_RM_PER_MCASP1_CONTEXT				0x44df0a44
extern reg am437x_rm_per_mcasp1_context;
#define AM437X_RM_PER_MMC2_CONTEXT				0x44df0a4c
extern reg am437x_rm_per_mmc2_context;
#define AM437X_RM_PER_QSPI_CONTEXT				0x44df0a5c
extern reg am437x_rm_per_qspi_context;
#define AM437X_RM_PER_USB_OTG_SS0_CONTEXT			0x44df0a64
extern reg am437x_rm_per_usb_otg_ss0_context;
#define AM437X_RM_PER_USB_OTG_SS1_CONTEXT			0x44df0a6c
extern reg am437x_rm_per_usb_otg_ss1_context;
#define AM437X_RM_PER_PRU_ICSS_CONTEXT				0x44df0b24
extern reg am437x_rm_per_pru_icss_context;
#define AM437X_RM_PER_L4LS_CONTEXT				0x44df0c24
extern reg am437x_rm_per_l4ls_context;
#define AM437X_RM_PER_DCAN0_CONTEXT				0x44df0c2c
extern reg am437x_rm_per_dcan0_context;
#define AM437X_RM_PER_DCAN1_CONTEXT				0x44df0c34
extern reg am437x_rm_per_dcan1_context;
#define AM437X_RM_PER_PWMSS0_CONTEXT				0x44df0c3c
extern reg am437x_rm_per_pwmss0_context;
#define AM437X_RM_PER_PWMSS1_CONTEXT				0x44df0c44
extern reg am437x_rm_per_pwmss1_context;
#define AM437X_RM_PER_PWMSS2_CONTEXT				0x44df0c4c
extern reg am437x_rm_per_pwmss2_context;
#define AM437X_RM_PER_PWMSS3_CONTEXT				0x44df0c54
extern reg am437x_rm_per_pwmss3_context;
#define AM437X_RM_PER_PWMSS4_CONTEXT				0x44df0c5c
extern reg am437x_rm_per_pwmss4_context;
#define AM437X_RM_PER_PWMSS5_CONTEXT				0x44df0c64
extern reg am437x_rm_per_pwmss5_context;
#define AM437X_RM_PER_ELM_CONTEXT				0x44df0c6c
extern reg am437x_rm_per_elm_context;
#define AM437X_RM_PER_GPIO1_CONTEXT				0x44df0c7c
extern reg am437x_rm_per_gpio1_context;
#define AM437X_RM_PER_GPIO2_CONTEXT				0x44df0c84
extern reg am437x_rm_per_gpio2_context;
#define AM437X_RM_PER_GPIO3_CONTEXT				0x44df0c8c
extern reg am437x_rm_per_gpio3_context;
#define AM437X_RM_PER_GPIO4_CONTEXT				0x44df0c94
extern reg am437x_rm_per_gpio4_context;
#define AM437X_RM_PER_GPIO5_CONTEXT				0x44df0c9c
extern reg am437x_rm_per_gpio5_context;
#define AM437X_RM_PER_HDQ1W_CONTEXT				0x44df0ca4
extern reg am437x_rm_per_hdq1w_context;
#define AM437X_RM_PER_I2C1_CONTEXT				0x44df0cac
extern reg am437x_rm_per_i2c1_context;
#define AM437X_RM_PER_I2C2_CONTEXT				0x44df0cb4
extern reg am437x_rm_per_i2c2_context;
#define AM437X_RM_PER_MAILBOX0_CONTEXT				0x44df0cbc
extern reg am437x_rm_per_mailbox0_context;
#define AM437X_RM_PER_MMC0_CONTEXT				0x44df0cc4
extern reg am437x_rm_per_mmc0_context;
#define AM437X_RM_PER_MMC1_CONTEXT				0x44df0ccc
extern reg am437x_rm_per_mmc1_context;
#define AM437X_RM_PER_RNG_CONTEXT				0x44df0ce4
extern reg am437x_rm_per_rng_context;
#define AM437X_RM_PER_SPI0_CONTEXT				0x44df0d04
extern reg am437x_rm_per_spi0_context;
#define AM437X_RM_PER_SPI1_CONTEXT				0x44df0d0c
extern reg am437x_rm_per_spi1_context;
#define AM437X_RM_PER_SPI2_CONTEXT				0x44df0d14
extern reg am437x_rm_per_spi2_context;
#define AM437X_RM_PER_SPI3_CONTEXT				0x44df0d1c
extern reg am437x_rm_per_spi3_context;
#define AM437X_RM_PER_SPI4_CONTEXT				0x44df0d24
extern reg am437x_rm_per_spi4_context;
#define AM437X_RM_PER_SPINLOCK_CONTEXT				0x44df0d2c
extern reg am437x_rm_per_spinlock_context;
#define AM437X_RM_PER_TIMER2_CONTEXT				0x44df0d34
extern reg am437x_rm_per_timer2_context;
#define AM437X_RM_PER_TIMER3_CONTEXT				0x44df0d3c
extern reg am437x_rm_per_timer3_context;
#define AM437X_RM_PER_TIMER4_CONTEXT				0x44df0d44
extern reg am437x_rm_per_timer4_context;
#define AM437X_RM_PER_TIMER5_CONTEXT				0x44df0d4c
extern reg am437x_rm_per_timer5_context;
#define AM437X_RM_PER_TIMER6_CONTEXT				0x44df0d54
extern reg am437x_rm_per_timer6_context;
#define AM437X_RM_PER_TIMER7_CONTEXT				0x44df0d5c
extern reg am437x_rm_per_timer7_context;
#define AM437X_RM_PER_TIMER8_CONTEXT				0x44df0d64
extern reg am437x_rm_per_timer8_context;
#define AM437X_RM_PER_TIMER9_CONTEXT				0x44df0d6c
extern reg am437x_rm_per_timer9_context;
#define AM437X_RM_PER_TIMER10_CONTEXT				0x44df0d74
extern reg am437x_rm_per_timer10_context;
#define AM437X_RM_PER_TIMER11_CONTEXT				0x44df0d7c
extern reg am437x_rm_per_timer11_context;
#define AM437X_RM_PER_UART1_CONTEXT				0x44df0d84
extern reg am437x_rm_per_uart1_context;
#define AM437X_RM_PER_UART2_CONTEXT				0x44df0d8c
extern reg am437x_rm_per_uart2_context;
#define AM437X_RM_PER_UART3_CONTEXT				0x44df0d94
extern reg am437x_rm_per_uart3_context;
#define AM437X_RM_PER_UART4_CONTEXT				0x44df0d9c
extern reg am437x_rm_per_uart4_context;
#define AM437X_RM_PER_UART5_CONTEXT				0x44df0da4
extern reg am437x_rm_per_uart5_context;
#define AM437X_RM_PER_USBPHYOCP2SCP0_CONTEXT			0x44df0dbc
extern reg am437x_rm_per_usbphyocp2scp0_context;
#define AM437X_RM_PER_USBPHYOCP2SCP1_CONTEXT			0x44df0dc4
extern reg am437x_rm_per_usbphyocp2scp1_context;
#define AM437X_RM_PER_EMIF_CONTEXT				0x44df0f24
extern reg am437x_rm_per_emif_context;
#define AM437X_RM_PER_DLL_CONTEXT				0x44df0f2c
extern reg am437x_rm_per_dll_context;
#define AM437X_RM_PER_DSS_CONTEXT				0x44df1224
extern reg am437x_rm_per_dss_context;
#define AM437X_RM_PER_CPGMAC0_CONTEXT				0x44df1324
extern reg am437x_rm_per_cpgmac0_context;
#define AM437X_RM_PER_OCPWP_CONTEXT				0x44df1424
extern reg am437x_rm_per_ocpwp_context;
#define AM437X_PRM_PER_MOD_REGCOUNT				77
extern reg *am437x_prm_per_mod[AM437X_PRM_PER_MOD_REGCOUNT + 1];

/* PRM_RTC Registers */
#define AM437X_RM_RTC_CONTEXT					0x44df0524
extern reg am437x_rm_rtc_context;
#define AM437X_PRM_RTC_MOD_REGCOUNT				1
extern reg *am437x_prm_rtc_mod[AM437X_PRM_RTC_MOD_REGCOUNT + 1];

/* PRM_WKUP Registers */
#define AM437X_RM_WKUP_RSTCTRL					0x44df2010
extern reg am437x_rm_wkup_rstctrl;
#define AM437X_RM_WKUP_RSTST					0x44df2014
extern reg am437x_rm_wkup_rstst;
#define AM437X_RM_WKUP_DBGSS_CONTEXT				0x44df2024
extern reg am437x_rm_wkup_dbgss_context;
#define AM437X_RM_WKUP_ADC0_CONTEXT				0x44df2124
extern reg am437x_rm_wkup_adc0_context;
#define AM437X_RM_WKUP_L4WKUP_CONTEXT				0x44df2224
extern reg am437x_rm_wkup_l4wkup_context;
#define AM437X_RM_WKUP_PROC_CONTEXT				0x44df222c
extern reg am437x_rm_wkup_proc_context;
#define AM437X_RM_WKUP_SYNCTIMER_CONTEXT			0x44df2234
extern reg am437x_rm_wkup_synctimer_context;
#define AM437X_RM_WKUP_TIMER0_CONTEXT				0x44df2324
extern reg am437x_rm_wkup_timer0_context;
#define AM437X_RM_WKUP_TIMER1_CONTEXT				0x44df232c
extern reg am437x_rm_wkup_timer1_context;
#define AM437X_RM_WKUP_WDT1_CONTEXT				0x44df233c
extern reg am437x_rm_wkup_wdt1_context;
#define AM437X_RM_WKUP_I2C0_CONTEXT				0x44df2344
extern reg am437x_rm_wkup_i2c0_context;
#define AM437X_RM_WKUP_UART0_CONTEXT				0x44df234c
extern reg am437x_rm_wkup_uart0_context;
#define AM437X_RM_WKUP_GPIO0_CONTEXT				0x44df236c
extern reg am437x_rm_wkup_gpio0_context;
#define AM437X_PRM_WKUP_MOD_REGCOUNT				13
extern reg *am437x_prm_wkup_mod[AM437X_PRM_WKUP_MOD_REGCOUNT + 1];

/* PRM_IRQ Registers */
#define AM437X_PRM_REVISION					0x44df0000
extern reg am437x_prm_revision;
#define AM437X_PRM_IRQSTS_MPU					0x44df0004
extern reg am437x_prm_irqsts_mpu;
#define AM437X_PRM_IRQEN_MPU					0x44df0008
extern reg am437x_prm_irqen_mpu;
#define AM437X_PRM_IRQSTS_WKUP_PROC				0x44df000c
extern reg am437x_prm_irqsts_wkup_proc;
#define AM437X_PRM_IRQEN_WKUP_PROC				0x44df0010
extern reg am437x_prm_irqen_wkup_proc;
#define AM437X_PRM_IRQ_MOD_REGCOUNT				5
extern reg *am437x_prm_irq_mod[AM437X_PRM_IRQ_MOD_REGCOUNT + 1];

typedef enum {
	PRM_AM437X_PRM_CEFUSE,
	PRM_AM437X_PRM_DEVICE,
	PRM_AM437X_PRM_GFX,
	PRM_AM437X_PRM_MPU,
	PRM_AM437X_PRM_PER,
	PRM_AM437X_PRM_RTC,
	PRM_AM437X_PRM_WKUP,
	PRM_AM437X_PRM_IRQ,
	PRM_AM437X_MODS_COUNT
} prm_am437x_mod_id;

extern reg **prm_am437x_mods[PRM_AM437X_MODS_COUNT + 1];

extern const char *prm_am437x_mods_name[PRM_AM437X_MODS_COUNT];


#endif
