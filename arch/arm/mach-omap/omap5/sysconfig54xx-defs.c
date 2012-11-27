/*
 *
 * @Component			OMAPCONF
 * @Filename			sysconfig54xx.c
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


#include <sysconfig54xx-defs.h>


/* Voltage dom.: WKUP, Power dom.: EMU, Clock dom. = EMU */
/* OMAP5_DEBUGSS */

/* Voltage dom.: WKUP, Power dom.: WKUPAON, Clock domain = WKUPAON */
/* OMAP5_CTRL_MODULE_WKUP */
/* OMAP5_L4WKUP_INTERCONNECT */
/* OMAP5_GPIO1 */
reg omap5430_gpio1_sysconfig = {
	"GPIO1_SYSCONFIG",
	OMAP5430_GPIO1_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_TIMER1 */
reg omap5430_timer1_tiocp_cfg = {
	"TIMER1_TIOCP_CFG",
	OMAP5430_TIMER1_TIOCP_CFG,
	0xDEADBEEF,
	0};

/* OMAP5_WD_TIMER2 */
reg omap5430_wd_timer2_l4interconnect_wdsc = {
	"WD_TIMER2_WDSC",
	OMAP5430_WD_TIMER2_L4INTERCONNECT_WDSC,
	0xDEADBEEF,
	0};

/* OMAP5_SARRAM */
/* OMAP5_COUNTER_32K */
reg omap5430_counter_32k_sysconfig = {
	"COUNTER_32K_SYSCONFIG",
	OMAP5430_COUNTER_32K_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_KBD */
reg omap5430_kbd_sysconfig = {
	"KBD_SYSCONFIG",
	OMAP5430_KBD_SYSCONFIG,
	0xDEADBEEF,
	0};

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
reg omap5430_fdif_sysconfig = {
	"FDIF_SYSCONFIG",
	OMAP5430_FDIF_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_ISS */
reg omap5430_iss_hl_sysconfig = {
	"ISS_HL_SYSCONFIG",
	OMAP5430_ISS_HL_SYSCONFIG,
	0xDEADBEEF,
	0};

reg omap5430_iss_ccp2_ccp2_sysconfig = {
	"CCP2_SYSCONFIG",
	OMAP5430_ISS_CCP2_CCP2_SYSCONFIG,
	0xDEADBEEF,
	0};

reg omap5430_iss_csi2_a_regs1_csi2_sysconfig = {
	"CSI2_A_SYSCONFIG",
	OMAP5430_ISS_CSI2_A_REGS1_CSI2_SYSCONFIG,
	0xDEADBEEF,
	0};

reg omap5430_iss_csi2_b_regs1_csi2_sysconfig = {
	"CSI2_B_SYSCONFIG",
	OMAP5430_ISS_CSI2_B_REGS1_CSI2_SYSCONFIG,
	0xDEADBEEF,
	0};

reg omap5430_iss_csi2_c_regs1_csi2_sysconfig = {
	"CSI2_C_SYSCONFIG",
	OMAP5430_ISS_CSI2_C_REGS1_CSI2_SYSCONFIG,
	0xDEADBEEF,
	0};

reg omap5430_iss_tctrl_tctrl_sysconfig = {
	"TCTRL_SYSCONFIG",
	OMAP5430_ISS_TCTRL_TCTRL_SYSCONFIG,
	0xDEADBEEF,
	0};

reg omap5430_iss_bte_bte_hl_sysconfig = {
	"BTE_HL_SYSCONFIG",
	OMAP5430_ISS_BTE_BTE_HL_SYSCONFIG,
	0xDEADBEEF,
	0};

reg omap5430_iss_cbuff_cbuff_hl_sysconfig = {
	"CBUFF_HL_SYSCONFIG",
	OMAP5430_ISS_CBUFF_CBUFF_HL_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_CAL */
reg omap5430_cal_hl_sysconfig = {
	"CAL_HL_SYSCONFIG",
	OMAP5430_CAL_HL_SYSCONFIG,
	0xDEADBEEF,
	0};

/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L4CFG */
/* OMAP5_CTRL_MODULE_CORE */
/* OMAP5_SPINLOCK */
reg omap5430_spinlock_sysconfig = {
	"SPINLOCK_SYSCONFIG",
	OMAP5430_SPINLOCK_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_L4_CFG_INTERCONNECT */
/* OMAP5_MAILBOX */
reg omap5430_mailbox_l4_cfginterconnect_mailbox_sysconfig = {
	"MAILBOX_SYSCONFIG",
	OMAP5430_MAILBOX_L4_CFGINTERCONNECT_MAILBOX_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_SARROM */
/* OMAP5_OCP2SCP2 */
reg omap5430_ocp2scp2_sysconfig = {
	"OCP2SCP2_SYSCONFIG",
	OMAP5430_OCP2SCP2_SYSCONFIG,
	0xDEADBEEF,
	0};

/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = EMIF */
/* OMAP5_PHY_EMIF */
/* OMAP5_DLL_EMIF */
/* OMAP5_DMM */
reg omap5430_dmm_sysconfig = {
	"DMM_SYSCONFIG",
	OMAP5430_DMM_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_EMIF1 */
/* OMAP5_EMIF2 */
/* OMAP5_EMIF_OCP_FW */

/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = IPU */
/* OMAP5_IPU */

/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN2 */
/* OMAP5_GPMC */
reg omap5430_gpmc_sysconfig = {
	"GPMC_SYSCONFIG",
	OMAP5430_GPMC_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_L3_MAIN2_INTERCONNECT */
/* OMAP5_OCMC_RAM */

/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_INSTR */
/* OMAP5_L3_MAIN3_INTERCONNECT */
/* OMAP5_L3_INSTR_INTERCONNECT */
/* OMAP5_OCP_WP_NOC */
reg omap5430_ocp_wp_sysconfig = {
	"OCP_WP_SYSCONFIG",
	OMAP5430_OCP_WP_SYSCONFIG,
	0xDEADBEEF,
	0};

/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN1 */
/* OMAP5_L3_MAIN1_INTERCONNECT */

/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = C2C */
/* OMAP5_C2C */
reg omap5430_c2c_sysconfig = {
	"C2C_SYSCONFIG",
	OMAP5430_C2C_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_C2C_OCP_FW */
/* OMAP5_MODEM_ICR */
reg omap5430_modem_icr_mpu_pa_sys_config = {
	"MODEM_ICR_MPU_PA_SYS_CONFIG",
	OMAP5430_MODEM_ICR_MPU_PA_SYS_CONFIG,
	0xDEADBEEF,
	0};

reg omap5430_modem_icr_mdm_pb_sys_config = {
	"MODEM_ICR_MDM_PB_SYS_CONFIG",
	OMAP5430_MODEM_ICR_MDM_PB_SYS_CONFIG,
	0xDEADBEEF,
	0};

/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = DMA */
/* OMAP5_DMA_SYSTEM */
reg omap5430_dma4_ocp_sysconfig = {
	"DMA4_OCP_SYSCONFIG",
	OMAP5430_DMA4_OCP_SYSCONFIG,
	0xDEADBEEF,
	0};

/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = MIPIEXT */
/* OMAP5_LLI */
/* OMAP5_LLI_OCP_FW */
/* OMAP5_MPHY */
/* OMAP5_UNIPRO1 */
reg omap5430_unipro1_sysconfig = {
	"UNIPRO1_SYSCONFIG",
	OMAP5430_UNIPRO1_SYSCONFIG,
	0xDEADBEEF,
	0};

/* Voltage dom.: CORE, Power dom.: DSS, Clock domain = DSS */
/* OMAP5_DSS */
reg omap5430_dispc_l3_main_dispc_sysconfig = {
	"DISPC_L3_MAIN_DISPC_SYSCONFIG",
	OMAP5430_DISPC_L3_MAIN_DISPC_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_BB2D */

/* Voltage dom.: CORE, Power dom.: L3INIT, Clock domain = L3INIT */
/* OMAP5_HSI */
reg omap5430_hsi_sysconfig = {
	"HSI_SYSCONFIG",
	OMAP5430_HSI_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_IEEE1500_2_OCP */
/* OMAP5_MMC1 */
reg omap5430_mmchs1_hl_sysconfig = {
	"MMCHS1_HL_SYSCONFIG",
	OMAP5430_MMCHS1_HL_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_MMC2 */
reg omap5430_mmchs2_hl_sysconfig = {
	"MMCHS2_HL_SYSCONFIG",
	OMAP5430_MMCHS2_HL_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_OCPSCP1 */
reg omap5430_ocp2scp1_sysconfig = {
	"OCP2SCP1_SYSCONFIG",
	OMAP5430_OCP2SCP1_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_USB_HOST_HS */
reg omap5430_uhh_sysconfig = {
	"",
	OMAP5430_UHH_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_USB_OTG_SS */
reg omap5430_usbotgss_sysconfig = {
	"USBOTGSS_SYSCONFIG",
	OMAP5430_USBOTGSS_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_USB_TLL_HS */
reg omap5430_usbtll_sysconfig = {
	"USBTLL_SYSCONFIG",
	OMAP5430_USBTLL_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_SATA */
reg omap5430_sata_sysconfig = {
	"SATA_SYSCONFIG",
	OMAP5430_SATA_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_UNIPRO2 */
reg omap5430_unipro2_sysconfig = {
	"UNIPRO2_SYSCONFIG",
	OMAP5430_UNIPRO2_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_MPHY_UNIPRO2 */
/* OMAP5_OCPSCP3 */
reg omap5430_ocp2scp3_sysconfig = {
	"OCP2SCP3_SYSCONFIG",
	OMAP5430_OCP2SCP3_SYSCONFIG,
	0xDEADBEEF,
	0};

/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_PER */
/* OMAP5_TIMER10 */
reg omap5430_timer10_l4interconnect_tiocp_cfg = {
	"TIMER10_TIOCP_CFG",
	OMAP5430_TIMER10_L4INTERCONNECT_TIOCP_CFG,
	0xDEADBEEF,
	0};

/* OMAP5_TIMER11 */
reg omap5430_timer11_l4interconnect_tiocp_cfg = {
	"TIMER11_TIOCP_CFG",
	OMAP5430_TIMER11_L4INTERCONNECT_TIOCP_CFG,
	0xDEADBEEF,
	0};

/* OMAP5_TIMER2 */
reg omap5430_timer2_l4interconnect_tiocp_cfg = {
	"TIMER2_TIOCP_CFG",
	OMAP5430_TIMER2_L4INTERCONNECT_TIOCP_CFG,
	0xDEADBEEF,
	0};

/* OMAP5_TIMER3 */
reg omap5430_timer3_l4interconnect_tiocp_cfg = {
	"TIMER3_TIOCP_CFG",
	OMAP5430_TIMER3_L4INTERCONNECT_TIOCP_CFG,
	0xDEADBEEF,
	0};

/* OMAP5_TIMER4 */
reg omap5430_timer4_l4interconnect_tiocp_cfg = {
	"TIMER4_TIOCP_CFG",
	OMAP5430_TIMER4_L4INTERCONNECT_TIOCP_CFG,
	0xDEADBEEF,
	0};

/* OMAP5_TIMER9 */
reg omap5430_timer9_l4interconnect_tiocp_cfg = {
	"TIMER9_TIOCP_CFG",
	OMAP5430_TIMER9_L4INTERCONNECT_TIOCP_CFG,
	0xDEADBEEF,
	0};

/* OMAP5_ELM */
reg omap5430_elm_sysconfig = {
	"ELM_SYSCONFIG",
	OMAP5430_ELM_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_GPIO2 */
reg omap5430_gpio2_sysconfig = {
	"GPIO2_SYSCONFIG",
	OMAP5430_GPIO2_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_GPIO3 */
reg omap5430_gpio3_sysconfig = {
	"GPIO3_SYSCONFIG",
	OMAP5430_GPIO3_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_GPIO4 */
reg omap5430_gpio4_sysconfig = {
	"GPIO4_SYSCONFIG",
	OMAP5430_GPIO4_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_GPIO5 */
reg omap5430_gpio5_sysconfig = {
	"GPIO5_SYSCONFIG",
	OMAP5430_GPIO5_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_GPIO6 */
reg omap5430_gpio6_sysconfig = {
	"GPIO6_SYSCONFIG",
	OMAP5430_GPIO6_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_GPIO7 */
reg omap5430_gpio7_sysconfig = {
	"GPIO7_SYSCONFIG",
	OMAP5430_GPIO7_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_GPIO8 */
reg omap5430_gpio8_sysconfig = {
	"GPIO8_SYSCONFIG",
	OMAP5430_GPIO8_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_HDQ1W */
reg omap5430_hdq_sysconfig = {
	"HDQ_SYSCONFIG",
	OMAP5430_HDQ_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_I2C1 */
reg omap5430_i2c1_sysc = {
	"I2C1_SYSC",
	OMAP5430_I2C1_SYSC,
	0xDEADBEEF,
	0};

/* OMAP5_I2C2 */
reg omap5430_i2c2_sysc = {
	"I2C2_SYSC",
	OMAP5430_I2C2_SYSC,
	0xDEADBEEF,
	0};

/* OMAP5_I2C3 */
reg omap5430_i2c3_sysc = {
	"I2C3_SYSC",
	OMAP5430_I2C3_SYSC,
	0xDEADBEEF,
	0};

/* OMAP5_I2C4 */
reg omap5430_i2c4_sysc = {
	"I2C4_SYSC",
	OMAP5430_I2C4_SYSC,
	0xDEADBEEF,
	0};

/* OMAP5_I2C5 */
reg omap5430_i2c5_sysc = {
	"I2C5_SYSC",
	OMAP5430_I2C5_SYSC,
	0xDEADBEEF,
	0};

/* OMAP5_L4_PER_INTERCONNECT */
/* OMAP5_MCSPI1 */
reg omap5430_mcspi1_hl_sysconfig = {
	"MCSPI1_HL_SYSCONFIG",
	OMAP5430_MCSPI1_HL_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_MCSPI2 */
reg omap5430_mcspi2_hl_sysconfig = {
	"MCSPI2_HL_SYSCONFIG",
	OMAP5430_MCSPI2_HL_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_MCSPI3 */
reg omap5430_mcspi3_hl_sysconfig = {
	"MCSPI3_HL_SYSCONFIG",
	OMAP5430_MCSPI3_HL_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_MCSPI4 */
reg omap5430_mcspi4_hl_sysconfig = {
	"MCSPI4_HL_SYSCONFIG",
	OMAP5430_MCSPI4_HL_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_MMC3 */
reg omap5430_mmchs3_hl_sysconfig = {
	"MMCHS3_HL_SYSCONFIG",
	OMAP5430_MMCHS3_HL_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_MMC4 */
reg omap5430_mmchs4_hl_sysconfig = {
	"MMCHS4_HL_SYSCONFIG",
	OMAP5430_MMCHS4_HL_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_MMC5 */
reg omap5430_mmchs5_hl_sysconfig = {
	"MMCHS5_HL_SYSCONFIG",
	OMAP5430_MMCHS5_HL_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_SLIMBUS2 */
reg omap5430_slimbus2_cmp_sysconfig = {
	"SLIMBUS2_CMP_SYSCONFIG",
	OMAP5430_SLIMBUS2_CMP_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_UART1 */
reg omap5430_uart1_sysc = {
	"UART1_SYSC",
	OMAP5430_UART1_SYSC,
	0xDEADBEEF,
	0};

/* OMAP5_UART2 */
reg omap5430_uart2_sysc = {
	"UART2_SYSC",
	OMAP5430_UART2_SYSC,
	0xDEADBEEF,
	0};

/* OMAP5_UART3 */
reg omap5430_uart3_sysc = {
	"UART3_SYSC",
	OMAP5430_UART3_SYSC,
	0xDEADBEEF,
	0};

/* OMAP5_UART4 */
reg omap5430_uart4_sysc = {
	"UART4_SYSC",
	OMAP5430_UART4_SYSC,
	0xDEADBEEF,
	0};

/* OMAP5_UART5 */
reg omap5430_uart5_sysc = {
	"UART5_SYSC",
	OMAP5430_UART5_SYSC,
	0xDEADBEEF,
	0};

/* OMAP5_UART6 */
reg omap5430_uart6_sysc = {
	"UART6_SYSC",
	OMAP5430_UART6_SYSC,
	0xDEADBEEF,
	0};

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
reg omap5430_aess_sysconfig = {
	"AESS_SYSCONFIG",
	OMAP5430_AESS_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_DMIC */
reg omap5430_dmic_cortex_a15_dmic_sysconfig = {
	"DMIC_SYSCONFIG",
	OMAP5430_DMIC_CORTEX_A15_DMIC_SYSCONFIG,
	0xDEADBEEF,
	0};

reg omap5430_dmic_l3interconnect_dmic_sysconfig = {
	"DMIC_SYSCONFIG",
	OMAP5430_DMIC_L3INTERCONNECT_DMIC_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_L4_ABE_INTERCONNECT */
/* OMAP5_MCASP */
reg omap5430_mcasp_mpu_mcasp_sysconfig = {
	"MCASP_SYSCONFIG",
	OMAP5430_MCASP_MPU_MCASP_SYSCONFIG,
	0xDEADBEEF,
	0};

reg omap5430_mcasp_l3_maininterconnect_mcasp_sysconfig = {
	"MCASP_SYSCONFIG",
	OMAP5430_MCASP_L3_MAININTERCONNECT_MCASP_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_MCBSP1 */
reg omap5430_mcbsp1_cortex_a15_mcbsplp_sysconfig_reg = {
	"MCBSPLP1_SYSCONFIG_REG",
	OMAP5430_MCBSP1_CORTEX_A15_MCBSPLP_SYSCONFIG_REG,
	0xDEADBEEF,
	0};

reg omap5430_mcbsp1_l3interconnect_mcbsplp_sysconfig_reg = {
	"MCBSPLP1_SYSCONFIG_REG",
	OMAP5430_MCBSP1_L3INTERCONNECT_MCBSPLP_SYSCONFIG_REG,
	0xDEADBEEF,
	0};

/* OMAP5_MCBSP2 */
reg omap5430_mcbsp2_cortex_a15_mcbsplp_sysconfig_reg = {
	"MCBSPLP2_SYSCONFIG_REG",
	OMAP5430_MCBSP2_CORTEX_A15_MCBSPLP_SYSCONFIG_REG,
	0xDEADBEEF,
	0};

reg omap5430_mcbsp2_l3interconnect_mcbsplp_sysconfig_reg = {
	"MCBSPLP2_SYSCONFIG_REG",
	OMAP5430_MCBSP2_L3INTERCONNECT_MCBSPLP_SYSCONFIG_REG,
	0xDEADBEEF,
	0};

/* OMAP5_MCBSP3 */
reg omap5430_mcbsp3_cortex_a15_mcbsplp_sysconfig_reg = {
	"MCBSPLP3_SYSCONFIG_REG",
	OMAP5430_MCBSP3_CORTEX_A15_MCBSPLP_SYSCONFIG_REG,
	0xDEADBEEF,
	0};

reg omap5430_mcbsp3_l3interconnect_mcbsplp_sysconfig_reg = {
	"MCBSPLP3_SYSCONFIG_REG",
	OMAP5430_MCBSP3_L3INTERCONNECT_MCBSPLP_SYSCONFIG_REG,
	0xDEADBEEF,
	0};

/* OMAP5_MCPDM */
reg omap5430_mcpdm_cortex_a15_mcpdm_sysconfig = {
	"MCPDM_SYSCONFIG",
	OMAP5430_MCPDM_CORTEX_A15_MCPDM_SYSCONFIG,
	0xDEADBEEF,
	0};

reg omap5430_mcpdm_l3interconnect_mcpdm_sysconfig = {
	"MCPDM_SYSCONFIG",
	OMAP5430_MCPDM_L3INTERCONNECT_MCPDM_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_SLIMBUS1 */
reg omap5430_slimbus1_mpu_slimbus_cmp_sysconfig = {
	"SLIMBUS1_CMP_SYSCONFIG",
	OMAP5430_SLIMBUS1_MPU_SLIMBUS_CMP_SYSCONFIG,
	0xDEADBEEF,
	0};

reg omap5430_slimbus1_l3interconnect_slimbus_cmp_sysconfig = {
	"SLIMBUS1_CMP_SYSCONFIG",
	OMAP5430_SLIMBUS1_L3INTERCONNECT_SLIMBUS_CMP_SYSCONFIG,
	0xDEADBEEF,
	0};

/* OMAP5_TIMER5 */
reg omap5430_timer5_mpu_tiocp_cfg = {
	"TIMER5_TIOCP_CFG",
	OMAP5430_TIMER5_MPU_TIOCP_CFG,
	0xDEADBEEF,
	0};

reg omap5430_timer5_l3_maininterconnect_tiocp_cfg = {
	"TIMER5_TIOCP_CFG",
	OMAP5430_TIMER5_L3_MAININTERCONNECT_TIOCP_CFG,
	0xDEADBEEF,
	0};

/* OMAP5_TIMER6 */
reg omap5430_timer6_mpu_tiocp_cfg = {
	"TIMER6_TIOCP_CFG",
	OMAP5430_TIMER6_MPU_TIOCP_CFG,
	0xDEADBEEF,
	0};

reg omap5430_timer6_l3_maininterconnect_tiocp_cfg = {
	"TIMER6_TIOCP_CFG",
	OMAP5430_TIMER6_L3_MAININTERCONNECT_TIOCP_CFG,
	0xDEADBEEF,
	0};

/* OMAP5_TIMER7 */
reg omap5430_timer7_mpu_tiocp_cfg = {
	"TIMER7_TIOCP_CFG",
	OMAP5430_TIMER7_MPU_TIOCP_CFG,
	0xDEADBEEF,
	0};

reg omap5430_timer7_l3_maininterconnect_tiocp_cfg = {
	"TIMER7_TIOCP_CFG",
	OMAP5430_TIMER7_L3_MAININTERCONNECT_TIOCP_CFG,
	0xDEADBEEF,
	0};

/* OMAP5_TIMER8 */
reg omap5430_timer8_mpu_tiocp_cfg = {
	"TIMER8_TIOCP_CFG",
	OMAP5430_TIMER8_MPU_TIOCP_CFG,
	0xDEADBEEF,
	0};

reg omap5430_timer8_l3_maininterconnect_tiocp_cfg = {
	"TIMER8_TIOCP_CFG",
	OMAP5430_TIMER8_L3_MAININTERCONNECT_TIOCP_CFG,
	0xDEADBEEF,
	0};

/* OMAP5_WD_TIMER3 */
reg omap5430_wd_timer3_l3interconnect_wdsc = {
	"WD_TIMER3_WDSC",
	OMAP5430_WD_TIMER3_L3INTERCONNECT_WDSC,
	0xDEADBEEF,
	0};

/* Voltage dom.: MM, Power dom.: DSP, Clock domain = DSP */
/* OMAP5_DSP */
reg omap5430_dsp_sysc_sysconfig = {
	"DSP_SYSC_SYSCONFIG",
	OMAP5430_DSP_SYSC_SYSCONFIG,
	0xDEADBEEF,
	0};

/* Voltage dom.: MM, Power dom.: GPU, Clock domain = GPU */
/* OMAP5_GPU */
reg omap5430_gpu_sysconfig = {
	"GPU_SYSCONFIG",
	OMAP5430_GPU_SYSCONFIG,
	0xDEADBEEF,
	0};

/* Voltage dom.: MM, Power dom.: IVA, Clock domain = IVA */
/* OMAP5_IVA */
/* OMAP5_SL2 */

/* Voltage dom.: MPU, Power dom.: MPUAON Clock domain = MPU */
/* OMAP5_MPU */
