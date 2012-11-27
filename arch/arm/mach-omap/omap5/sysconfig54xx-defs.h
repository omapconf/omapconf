/*
 *
 * @Component			OMAPCONF
 * @Filename			sysconfig54xx-defs.h
 * @Description			OMAP5 SYSCONFIG Register Address Definitions
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


#ifndef __SYSCONFIG54XX_H__
#define __SYSCONFIG54XX_H__

#include <reg.h>
#include <stdio.h>


/* Voltage dom.: WKUP, Power dom.: EMU, Clock dom. = EMU */
/* OMAP5_DEBUGSS */

/* Voltage dom.: WKUP, Power dom.: WKUPAON, Clock domain = WKUPAON */
/* OMAP5_CTRL_MODULE_WKUP */
/* OMAP5_L4WKUP_INTERCONNECT */
/* OMAP5_GPIO1 */
#define OMAP5430_GPIO1_SYSCONFIG				0x4AE10010
extern reg omap5430_gpio1_sysconfig;
/* OMAP5_TIMER1 */
#define OMAP5430_TIMER1_TIOCP_CFG				0x4ae18010
extern reg omap5430_timer1_tiocp_cfg;
/* OMAP5_WD_TIMER2 */
#define OMAP5430_WD_TIMER2_L4INTERCONNECT_WDSC			0x4ae14010
extern reg omap5430_wd_timer2_l4interconnect_wdsc;
/* OMAP5_SARRAM */
/* OMAP5_COUNTER_32K */
#define OMAP5430_COUNTER_32K_SYSCONFIG				0x4ae04010
extern reg omap5430_counter_32k_sysconfig;
/* OMAP5_KBD */
#define OMAP5430_KBD_SYSCONFIG					0x4ae1c010
extern reg omap5430_kbd_sysconfig;
/* IO_SRCOMP_WKUP */
/* HS/EMU ONLY */
/* OMAP5_TIMER12 */
/* OMAP5_WDT1 */

/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = COREAON */
/* OMAP5_SMARTREFLEX_CORE */
/* OMAP5_SMARTREFLEX_MM */
/* OMAP5_SMARTREFLEX_MPU */
/* OMAP5_BANDGAPTS */
/* OMAP5_IO_SRCOMP_CORE */
/* OMAP5_USB_PHY_CORE */

/* Voltage dom.: CORE, Power dom.: CAM, Clock domain = CAM */
/* OMAP5_FDIF */
#define OMAP5430_FDIF_SYSCONFIG					0x4a10a010
extern reg omap5430_fdif_sysconfig;
/* OMAP5_ISS */
#define OMAP5430_ISS_HL_SYSCONFIG				0x52000010
extern reg omap5430_iss_hl_sysconfig;
#define OMAP5430_ISS_CCP2_CCP2_SYSCONFIG			0x52001c04
extern reg omap5430_iss_ccp2_ccp2_sysconfig;
#define OMAP5430_ISS_CSI2_A_REGS1_CSI2_SYSCONFIG		0x52001010
extern reg omap5430_iss_csi2_a_regs1_csi2_sysconfig;
#define OMAP5430_ISS_CSI2_B_REGS1_CSI2_SYSCONFIG		0x52001410
extern reg omap5430_iss_csi2_b_regs1_csi2_sysconfig;
#define OMAP5430_ISS_CSI2_C_REGS1_CSI2_SYSCONFIG		0x52002410
extern reg omap5430_iss_csi2_c_regs1_csi2_sysconfig;
#define OMAP5430_ISS_TCTRL_TCTRL_SYSCONFIG			0x52000404
extern reg omap5430_iss_tctrl_tctrl_sysconfig;
#define OMAP5430_ISS_BTE_BTE_HL_SYSCONFIG			0x52002010
extern reg omap5430_iss_bte_bte_hl_sysconfig;
#define OMAP5430_ISS_CBUFF_CBUFF_HL_SYSCONFIG			0x52001810
extern reg omap5430_iss_cbuff_cbuff_hl_sysconfig;
/* OMAP5_CAL */
#define OMAP5430_CAL_HL_SYSCONFIG				0x4a075010
extern reg omap5430_cal_hl_sysconfig;

/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L4CFG */
/* OMAP5_CTRL_MODULE_CORE */
/* OMAP5_SPINLOCK */
#define OMAP5430_SPINLOCK_SYSCONFIG				0x4a0f6010
extern reg omap5430_spinlock_sysconfig;
/* OMAP5_L4_CFG_INTERCONNECT */
/* OMAP5_MAILBOX */
#define OMAP5430_MAILBOX_L4_CFGINTERCONNECT_MAILBOX_SYSCONFIG	0x4a0f4010
extern reg omap5430_mailbox_l4_cfginterconnect_mailbox_sysconfig;
/* OMAP5_SARROM */
/* OMAP5_OCP2SCP2 */
#define OMAP5430_OCP2SCP2_SYSCONFIG				0x4A0A0010
extern reg omap5430_ocp2scp2_sysconfig;

/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = EMIF */
/* OMAP5_PHY_EMIF */
/* OMAP5_DLL_EMIF */
/* OMAP5_DMM */
#define OMAP5430_DMM_SYSCONFIG					0x4e000010
extern reg omap5430_dmm_sysconfig;
/* OMAP5_EMIF1 */
/* OMAP5_EMIF2 */
/* OMAP5_EMIF_OCP_FW */

/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = IPU */
/* OMAP5_IPU */

/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN2 */
/* OMAP5_GPMC */
#define OMAP5430_GPMC_SYSCONFIG					0x50000010
extern reg omap5430_gpmc_sysconfig;
/* OMAP5_L3_MAIN2_INTERCONNECT */
/* OMAP5_OCMC_RAM */

/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_INSTR */
/* OMAP5_L3_MAIN3_INTERCONNECT */
/* OMAP5_L3_INSTR_INTERCONNECT */
/* OMAP5_OCP_WP_NOC */
#define OMAP5430_OCP_WP_SYSCONFIG				0x4A102010
extern reg omap5430_ocp_wp_sysconfig;

/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN1 */
/* OMAP5_L3_MAIN1_INTERCONNECT */

/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = C2C */
/* OMAP5_C2C */
#define OMAP5430_C2C_SYSCONFIG					0x5c000004
extern reg omap5430_c2c_sysconfig;
/* OMAP5_C2C_OCP_FW */
/* OMAP5_MODEM_ICR */
#define OMAP5430_MODEM_ICR_MPU_PA_SYS_CONFIG			0x4a0b6010
extern reg omap5430_modem_icr_mpu_pa_sys_config;
#define OMAP5430_MODEM_ICR_MDM_PB_SYS_CONFIG			0x4a0cd010
extern reg omap5430_modem_icr_mdm_pb_sys_config;

/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = DMA */
/* OMAP5_DMA_SYSTEM */
#define OMAP5430_DMA4_OCP_SYSCONFIG				0x4a05602c
extern reg omap5430_dma4_ocp_sysconfig;

/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = MIPIEXT */
/* OMAP5_LLI */
/* OMAP5_LLI_OCP_FW */
/* OMAP5_MPHY */
/* OMAP5_UNIPRO1 */
#define OMAP5430_UNIPRO1_SYSCONFIG				0x4a068010
extern reg omap5430_unipro1_sysconfig;

/* Voltage dom.: CORE, Power dom.: DSS, Clock domain = DSS */
/* OMAP5_DSS */
#define OMAP5430_DISPC_L3_MAIN_DISPC_SYSCONFIG			0x58001010
extern reg omap5430_dispc_l3_main_dispc_sysconfig;
/* OMAP5_BB2D */

/* Voltage dom.: CORE, Power dom.: L3INIT, Clock domain = L3INIT */
/* OMAP5_HSI */
#define OMAP5430_HSI_SYSCONFIG					0x4a058010
extern reg omap5430_hsi_sysconfig;
/* OMAP5_IEEE1500_2_OCP */
/* OMAP5_MMC1 */
#define OMAP5430_MMCHS1_HL_SYSCONFIG				0x4809c010
extern reg omap5430_mmchs1_hl_sysconfig;
/* OMAP5_MMC2 */
#define OMAP5430_MMCHS2_HL_SYSCONFIG				0x480b4010
extern reg omap5430_mmchs2_hl_sysconfig;
/* OMAP5_OCPSCP1 */
#define OMAP5430_OCP2SCP1_SYSCONFIG				0x4a080010
extern reg omap5430_ocp2scp1_sysconfig;
/* OMAP5_USB_HOST_HS */
#define OMAP5430_UHH_SYSCONFIG					0x4a064010
extern reg omap5430_uhh_sysconfig;
/* OMAP5_USB_OTG_SS */
#define OMAP5430_USBOTGSS_SYSCONFIG				0x4a020010
extern reg omap5430_usbotgss_sysconfig;
/* OMAP5_USB_TLL_HS */
#define OMAP5430_USBTLL_SYSCONFIG				0x4a062010
extern reg omap5430_usbtll_sysconfig;
/* OMAP5_SATA */
#define OMAP5430_SATA_SYSCONFIG					0x4a141100
extern reg omap5430_sata_sysconfig;
/* OMAP5_UNIPRO2 */
#define OMAP5430_UNIPRO2_SYSCONFIG				0x4a070010
extern reg omap5430_unipro2_sysconfig;
/* OMAP5_MPHY_UNIPRO2 */
/* OMAP5_OCPSCP3 */
#define OMAP5430_OCP2SCP3_SYSCONFIG				0x4a090010
extern reg omap5430_ocp2scp3_sysconfig;

/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_PER */
/* OMAP5_TIMER10 */
#define OMAP5430_TIMER10_L4INTERCONNECT_TIOCP_CFG		0x48086010
extern reg omap5430_timer10_l4interconnect_tiocp_cfg;
/* OMAP5_TIMER11 */
#define OMAP5430_TIMER11_L4INTERCONNECT_TIOCP_CFG		0x48088010
extern reg omap5430_timer11_l4interconnect_tiocp_cfg;
/* OMAP5_TIMER2 */
#define OMAP5430_TIMER2_L4INTERCONNECT_TIOCP_CFG		0x48032010
extern reg omap5430_timer2_l4interconnect_tiocp_cfg;
/* OMAP5_TIMER3 */
#define OMAP5430_TIMER3_L4INTERCONNECT_TIOCP_CFG		0x48034010
extern reg omap5430_timer3_l4interconnect_tiocp_cfg;
/* OMAP5_TIMER4 */
#define OMAP5430_TIMER4_L4INTERCONNECT_TIOCP_CFG		0x48036010
extern reg omap5430_timer4_l4interconnect_tiocp_cfg;
/* OMAP5_TIMER9 */
#define OMAP5430_TIMER9_L4INTERCONNECT_TIOCP_CFG		0x4803e010
extern reg omap5430_timer9_l4interconnect_tiocp_cfg;
/* OMAP5_ELM */
#define OMAP5430_ELM_SYSCONFIG					0x48078010
extern reg omap5430_elm_sysconfig;
/* OMAP5_GPIO2 */
#define OMAP5430_GPIO2_SYSCONFIG				0x48055010
extern reg omap5430_gpio2_sysconfig;
/* OMAP5_GPIO3 */
#define OMAP5430_GPIO3_SYSCONFIG				0x48057010
extern reg omap5430_gpio3_sysconfig;
/* OMAP5_GPIO4 */
#define OMAP5430_GPIO4_SYSCONFIG				0x48059010
extern reg omap5430_gpio4_sysconfig;
/* OMAP5_GPIO5 */
#define OMAP5430_GPIO5_SYSCONFIG				0x4805b010
extern reg omap5430_gpio5_sysconfig;
/* OMAP5_GPIO6 */
#define OMAP5430_GPIO6_SYSCONFIG				0x4805d010
extern reg omap5430_gpio6_sysconfig;
/* OMAP5_GPIO7 */
#define OMAP5430_GPIO7_SYSCONFIG				0x48051010
extern reg omap5430_gpio7_sysconfig;
/* OMAP5_GPIO8 */
#define OMAP5430_GPIO8_SYSCONFIG				0x48053010
extern reg omap5430_gpio8_sysconfig;
/* OMAP5_HDQ1W */
#define OMAP5430_HDQ_SYSCONFIG					0x480B2014
extern reg omap5430_hdq_sysconfig;
/* OMAP5_I2C1 */
#define OMAP5430_I2C1_SYSC					0x48070010
extern reg omap5430_i2c1_sysc;
/* OMAP5_I2C2 */
#define OMAP5430_I2C2_SYSC					0x48072010
extern reg omap5430_i2c2_sysc;
/* OMAP5_I2C3 */
#define OMAP5430_I2C3_SYSC					0x48060010
extern reg omap5430_i2c3_sysc;
/* OMAP5_I2C4 */
#define OMAP5430_I2C4_SYSC					0x4807A010
extern reg omap5430_i2c4_sysc;
/* OMAP5_I2C5 */
#define OMAP5430_I2C5_SYSC					0x4807C010
extern reg omap5430_i2c5_sysc;
/* OMAP5_L4_PER_INTERCONNECT */
/* OMAP5_MCSPI1 */
#define OMAP5430_MCSPI1_HL_SYSCONFIG				0x48098010
extern reg omap5430_mcspi1_hl_sysconfig;
/* OMAP5_MCSPI2 */
#define OMAP5430_MCSPI2_HL_SYSCONFIG				0x4809a010
extern reg omap5430_mcspi2_hl_sysconfig;
/* OMAP5_MCSPI3 */
#define OMAP5430_MCSPI3_HL_SYSCONFIG				0x480b8010
extern reg omap5430_mcspi3_hl_sysconfig;
/* OMAP5_MCSPI4 */
#define OMAP5430_MCSPI4_HL_SYSCONFIG				0x480ba010
extern reg omap5430_mcspi4_hl_sysconfig;
/* OMAP5_MMC3 */
#define OMAP5430_MMCHS3_HL_SYSCONFIG				0x480ad010
extern reg omap5430_mmchs3_hl_sysconfig;
/* OMAP5_MMC4 */
#define OMAP5430_MMCHS4_HL_SYSCONFIG				0x480d1010
extern reg omap5430_mmchs4_hl_sysconfig;
/* OMAP5_MMC5 */
#define OMAP5430_MMCHS5_HL_SYSCONFIG				0x480d5010
extern reg omap5430_mmchs5_hl_sysconfig;
/* OMAP5_SLIMBUS2 */
#define OMAP5430_SLIMBUS2_CMP_SYSCONFIG				0x48076010
extern reg omap5430_slimbus2_cmp_sysconfig;
/* OMAP5_UART1 */
#define OMAP5430_UART1_SYSC					0x4806A054
extern reg omap5430_uart1_sysc;
/* OMAP5_UART2 */
#define OMAP5430_UART2_SYSC					0x4806C054
extern reg omap5430_uart2_sysc;
/* OMAP5_UART3 */
#define OMAP5430_UART3_SYSC					0x48020054
extern reg omap5430_uart3_sysc;
/* OMAP5_UART4 */
#define OMAP5430_UART4_SYSC					0x4806E054
extern reg omap5430_uart4_sysc;
/* OMAP5_UART5 */
#define OMAP5430_UART5_SYSC					0x48066054
extern reg omap5430_uart5_sysc;
/* OMAP5_UART6 */
#define OMAP5430_UART6_SYSC					0x48068054
extern reg omap5430_uart6_sysc;

/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_SEC */
/* HS/EMU ONLY */
/* OMAP5_DMA_CRYPTO */
/* OMAP5_AES1 */
/* OMAP5_AES2 */
/* OMAP5_SHA2MD5 */
/* OMAP5_RNG */
/* OMAP5_DES3DES */
/* OMAP5_PKA */

/* Voltage dom.: CORE, Power dom.: ABE, Clock domain = ABE */
/* OMAP5_AESS */
#define OMAP5430_AESS_SYSCONFIG					0x490F1010
extern reg omap5430_aess_sysconfig;
/* OMAP5_DMIC */
#define OMAP5430_DMIC_CORTEX_A15_DMIC_SYSCONFIG			0x4012e010
extern reg omap5430_dmic_cortex_a15_dmic_sysconfig;
#define OMAP5430_DMIC_L3INTERCONNECT_DMIC_SYSCONFIG		0x4902e010
extern reg omap5430_dmic_l3interconnect_dmic_sysconfig;
/* OMAP5_L4_ABE_INTERCONNECT */
/* OMAP5_MCASP */
#define OMAP5430_MCASP_MPU_MCASP_SYSCONFIG			0x40128004
extern reg omap5430_mcasp_mpu_mcasp_sysconfig;
#define OMAP5430_MCASP_L3_MAININTERCONNECT_MCASP_SYSCONFIG	0x49028004
extern reg omap5430_mcasp_l3_maininterconnect_mcasp_sysconfig;
/* OMAP5_MCBSP1 */
#define OMAP5430_MCBSP1_CORTEX_A15_MCBSPLP_SYSCONFIG_REG	0x4012208c
extern reg omap5430_mcbsp1_cortex_a15_mcbsplp_sysconfig_reg;
#define OMAP5430_MCBSP1_L3INTERCONNECT_MCBSPLP_SYSCONFIG_REG	0x4902208c
extern reg omap5430_mcbsp1_l3interconnect_mcbsplp_sysconfig_reg;
/* OMAP5_MCBSP2 */
#define OMAP5430_MCBSP2_CORTEX_A15_MCBSPLP_SYSCONFIG_REG	0x4012408c
extern reg omap5430_mcbsp2_cortex_a15_mcbsplp_sysconfig_reg;
#define OMAP5430_MCBSP2_L3INTERCONNECT_MCBSPLP_SYSCONFIG_REG	0x4902408c
extern reg omap5430_mcbsp2_l3interconnect_mcbsplp_sysconfig_reg;
/* OMAP5_MCBSP3 */
#define OMAP5430_MCBSP3_CORTEX_A15_MCBSPLP_SYSCONFIG_REG	0x4012608c
extern reg omap5430_mcbsp3_cortex_a15_mcbsplp_sysconfig_reg;
#define OMAP5430_MCBSP3_L3INTERCONNECT_MCBSPLP_SYSCONFIG_REG	0x4902608c
extern reg omap5430_mcbsp3_l3interconnect_mcbsplp_sysconfig_reg;
/* OMAP5_MCPDM */
#define OMAP5430_MCPDM_CORTEX_A15_MCPDM_SYSCONFIG		0x40132010
extern reg omap5430_mcpdm_cortex_a15_mcpdm_sysconfig;
#define OMAP5430_MCPDM_L3INTERCONNECT_MCPDM_SYSCONFIG		0x49032010
extern reg omap5430_mcpdm_l3interconnect_mcpdm_sysconfig;
/* OMAP5_SLIMBUS1 */
#define OMAP5430_SLIMBUS1_MPU_SLIMBUS_CMP_SYSCONFIG		0x4012c010
extern reg omap5430_slimbus1_mpu_slimbus_cmp_sysconfig;
#define OMAP5430_SLIMBUS1_L3INTERCONNECT_SLIMBUS_CMP_SYSCONFIG	0x4902c010
extern reg omap5430_slimbus1_l3interconnect_slimbus_cmp_sysconfig;
/* OMAP5_TIMER5 */
#define OMAP5430_TIMER5_MPU_TIOCP_CFG				0x40138010
extern reg omap5430_timer5_mpu_tiocp_cfg;
#define OMAP5430_TIMER5_L3_MAININTERCONNECT_TIOCP_CFG		0x49038010
extern reg omap5430_timer5_l3_maininterconnect_tiocp_cfg;
/* OMAP5_TIMER6 */
#define OMAP5430_TIMER6_MPU_TIOCP_CFG				0x4013a010
extern reg omap5430_timer6_mpu_tiocp_cfg;
#define OMAP5430_TIMER6_L3_MAININTERCONNECT_TIOCP_CFG		0x4903a010
extern reg omap5430_timer6_l3_maininterconnect_tiocp_cfg;
/* OMAP5_TIMER7 */
#define OMAP5430_TIMER7_MPU_TIOCP_CFG				0x4013c010
extern reg omap5430_timer7_mpu_tiocp_cfg;
#define OMAP5430_TIMER7_L3_MAININTERCONNECT_TIOCP_CFG		0x4903c010
extern reg omap5430_timer7_l3_maininterconnect_tiocp_cfg;
/* OMAP5_TIMER8 */
#define OMAP5430_TIMER8_MPU_TIOCP_CFG				0x4013e010
extern reg omap5430_timer8_mpu_tiocp_cfg;
#define OMAP5430_TIMER8_L3_MAININTERCONNECT_TIOCP_CFG		0x4903e010
extern reg omap5430_timer8_l3_maininterconnect_tiocp_cfg;
/* OMAP5_WD_TIMER3 */
#define OMAP5430_WD_TIMER3_L3INTERCONNECT_WDSC			0x49030010
extern reg omap5430_wd_timer3_l3interconnect_wdsc;

/* Voltage dom.: MM, Power dom.: DSP, Clock domain = DSP */
/* OMAP5_DSP */
#define OMAP5430_DSP_SYSC_SYSCONFIG				0x01c20008
extern reg omap5430_dsp_sysc_sysconfig;

/* Voltage dom.: MM, Power dom.: GPU, Clock domain = GPU */
/* OMAP5_GPU */
#define OMAP5430_GPU_SYSCONFIG					0x5600FE10
extern reg omap5430_gpu_sysconfig;

/* Voltage dom.: MM, Power dom.: IVA, Clock domain = IVA */
/* OMAP5_IVA */
/* OMAP5_SL2 */

/* Voltage dom.: MPU, Power dom.: MPUAON Clock domain = MPU */
/* OMAP5_MPU */

#endif
