/*
 *
 * @Component			OMAPCONF
 * @Filename			module54xx-data.c
 * @Description			OMAP5 Module Data Definitions
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


#include <module54xx-data.h>
#include <sysconfig54xx-defs.h>
#include <cm54xx.h>
#include <prm54xx.h>


const char
	mod54xx_names_table[MOD54XX_ID_MAX][MODULE_MAX_NAME_LENGTH] = {
	/* Voltage dom.: WKUP, Power dom.: EMU, Clock dom. = EMU */
	"DEBUGSS",
	/* Voltage dom.: WKUP, Power dom.: WKUPAON, Clock domain = WKUPAON */
	"CTRL_MODULE_WKUP",
	"L4WKUP_INTERCONNECT",
	"GPIO1",
	"TIMER1",
	"WD_TIMER2",
	"SARRAM",
	"COUNTER_32K",
	"KBD",
	"IO_SRCOMP_WKUP",
	/* HS/EMU ONLY */
	"TIMER12",
	"WDT1",
	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = COREAON */
	"SMARTREFLEX_CORE",
	"SMARTREFLEX_MM",
	"SMARTREFLEX_MPU",
	"BANDGAPTS",
	"IO_SRCOMP_CORE",
	"USB_PHY_CORE",
	/* Voltage dom.: CORE, Power dom.: CAM, Clock domain = CAM */
	"FDIF",
	"ISS",
	"CAL",
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L4CFG */
	"CTRL_MODULE_CORE",
	"SPINLOCK",
	"L4_CFG_INTERCONNECT",
	"MAILBOX",
	"SARROM",
	"OCP2SCP2",
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = EMIF */
	"PHY_EMIF",
	"DLL_EMIF",
	"DMM",
	"EMIF1",
	"EMIF2",
	"EMIF_OCP_FW",
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = IPU */
	"IPU",
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN2 */
	"GPMC",
	"L3_MAIN2_INTERCONNECT",
	"OCMC_RAM",
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_INSTR */
	"L3_MAIN3_INTERCONNECT",
	"L3_INSTR_INTERCONNECT",
	"OCP_WP_NOC",
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN1 */
	"L3_MAIN1_INTERCONNECT",
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = C2C */
	"C2C",
	"C2C_OCP_FW",
	"MODEM_ICR",
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = DMA */
	"DMA_SYSTEM",
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = MIPIEXT */
	"LLI",
	"LLI_OCP_FW",
	"MPHY",
	"UNIPRO1",
	/* Voltage dom.: CORE, Power dom.: DSS, Clock domain = DSS */
	"DSS",
	"BB2D",
	/* Voltage dom.: CORE, Power dom.: L3INIT, Clock domain = L3INIT */
	"HSI",
	"IEEE1500_2_OCP",
	"MMC1",
	"MMC2",
	"OCPSCP1",
	"USB_HOST_HS",
	"USB_OTG_SS",
	"USB_TLL_HS",
	"SATA",
	"UNIPRO2",
	"MPHY_UNIPRO2",
	"OCPSCP3",
	/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_PER */
	"TIMER10",
	"TIMER11",
	"TIMER2",
	"TIMER3",
	"TIMER4",
	"TIMER9",
	"ELM",
	"GPIO2",
	"GPIO3",
	"GPIO4",
	"GPIO5",
	"GPIO6",
	"GPIO7",
	"GPIO8",
	"HDQ1W",
	"I2C1",
	"I2C2",
	"I2C3",
	"I2C4",
	"I2C5",
	"L4_PER_INTERCONNECT",
	"MCSPI1",
	"MCSPI2",
	"MCSPI3",
	"MCSPI4",
	"MMC3",
	"MMC4",
	"MMC5",
	"SLIMBUS2",
	"UART1",
	"UART2",
	"UART3",
	"UART4",
	"UART5",
	"UART6",
	/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_SEC */
	/* HS/EMU ONLY */
	"DMA_CRYPTO",
	"AES1",
	"AES2",
	"SHA2MD5",
	"RNG",
	"DES3DES",
	"PKA",
	/* Voltage dom.: CORE, Power dom.: ABE, Clock domain = ABE */
	"AESS",
	"DMIC",
	"L4_ABE_INTERCONNECT",
	"MCASP",
	"MCBSP1",
	"MCBSP2",
	"MCBSP3",
	"MCPDM",
	"SLIMBUS1",
	"TIMER5",
	"TIMER6",
	"TIMER7",
	"TIMER8",
	"WD_TIMER3",
	/* Voltage dom.: MM, Power dom.: DSP, Clock domain = DSP */
	"DSP",
	/* Voltage dom.: MM, Power dom.: GPU, Clock domain = GPU */
	"GPU",
	/* Voltage dom.: MM, Power dom.: IVA, Clock domain = IVA */
	"IVA",
	"SL2",
	/* Voltage dom.: MPU, Power dom.: MPUAON Clock domain = MPU */
	"MPU",
	/* ES2.0 additions */
	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = COREAON */
	"USB2PHY",
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_INSTR */
	"CTRL_MODULE_BANDGAP"};


const clk54xx_id mod54xx_flck_table[MOD54XX_ID_MAX] = {
	/* Voltage dom.: WKUP, Power dom.: EMU, Clock dom. = EMU */
	CLK54XX_EMU_SYS_CLK, /* OMAP5_DEBUGSS */
	/* Voltage dom.: WKUP, Power dom.: WKUPAON, Clock domain = WKUPAON */
	CLK54XX_WKUPAON_GICLK, /* OMAP5_CTRL_MODULE_WKUP */
	CLK54XX_WKUPAON_GICLK, /* OMAP5_L4WKUP_INTERCONNECT */
	CLK54XX_WKUPAON_32K_GFCLK, /* OMAP5_GPIO1 */
	CLK54XX_TIMER1_GFCLK, /* OMAP5_TIMER1 */
	CLK54XX_WKUPAON_32K_GFCLK, /* OMAP5_WD_TIMER2 */
	CLK54XX_WKUPAON_GICLK, /* OMAP5_SARRAM */
	CLK54XX_FUNC_32K_CLK, /* OMAP5_COUNTER_32K */
	CLK54XX_WKUPAON_32K_GFCLK, /* OMAP5_KBD */
	CLK54XX_WKUPAON_IO_SRCOMP_GFCLK, /* IO_SRCOMP_WKUP */
	/* HS/EMU ONLY */
	CLK54XX_SECURE_32K_CLK, /* OMAP5_TIMER12 */
	CLK54XX_SECURE_32K_CLK, /* OMAP5_WDT1 */
	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = COREAON */
	CLK54XX_SR_CORE_SYS_GFCLK, /* OMAP5_SMARTREFLEX_CORE */
	CLK54XX_SR_MM_SYS_GFCLK, /* OMAP5_SMARTREFLEX_MM */
	CLK54XX_SR_MPU_SYS_GFCLK, /* OMAP5_SMARTREFLEX_MPU */
	CLK54XX_COREAON_TS_GFCLK, /* OMAP5_BANDGAPTS */
	CLK54XX_COREAON_IO_SRCOMP_GFCLK, /* OMAP5_IO_SRCOMP_CORE */
	CLK54XX_COREAON_32K_GFCLK, /* OMAP5_USB_PHY_CORE */
	/* Voltage dom.: CORE, Power dom.: CAM, Clock domain = CAM */
	CLK54XX_FDIF_GFCLK, /* OMAP5_FDIF */
	CLK54XX_CORE_ISS_MAIN_CLK, /* OMAP5_ISS */
	CLK54XX_CAM_L3_GICLK, /* OMAP5_CAL */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L4CFG */
	CLK54XX_L4CFG_L4_GICLK, /* OMAP5_CTRL_MODULE_CORE */
	CLK54XX_L4CFG_L4_GICLK, /* OMAP5_SPINLOCK */
	CLK54XX_L4CFG_L4_GICLK, /* OMAP5_L4_CFG_INTERCONNECT */
	CLK54XX_L4CFG_L4_GICLK, /* OMAP5_MAILBOX */
	CLK54XX_L4CFG_L4_GICLK, /* OMAP5_SARROM */
	CLK54XX_L4CFG_L4_GICLK, /* OMAP5_OCP2SCP2 */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = EMIF */
	CLK54XX_EMIF_PHY_GCLK, /* OMAP5_PHY_EMIF */
	CLK54XX_CORE_DLL_GCLK, /* OMAP5_DLL_EMIF */
	CLK54XX_EMIF_L3_GICLK, /* OMAP5_DMM */
	CLK54XX_EMIF_L3_GICLK, /* OMAP5_EMIF1 */
	CLK54XX_EMIF_L3_GICLK, /* OMAP5_EMIF2 */
	CLK54XX_EMIF_L3_GICLK, /* OMAP5_EMIF_OCP_FW */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = IPU */
	CLK54XX_CORE_IPU_ISS_BOOST_CLK, /* OMAP5_IPU */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN2 */
	CLK54XX_L3MAIN2_L3_GICLK, /* OMAP5_GPMC */
	CLK54XX_L3MAIN2_L3_GICLK, /* OMAP5_L3_MAIN2_INTERCONNECT */
	CLK54XX_L3MAIN2_L3_GICLK, /* OMAP5_OCMC_RAM */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_INSTR */
	CLK54XX_L3INSTR_L3_GICLK, /* OMAP5_L3_MAIN3_INTERCONNECT */
	CLK54XX_L3INSTR_L3_GICLK, /* OMAP5_L3_INSTR_INTERCONNECT */
	CLK54XX_L3INSTR_L3_GICLK, /* OMAP5_OCP_WP_NOC */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN1 */
	CLK54XX_L3MAIN1_L3_GICLK, /* OMAP5_L3_MAIN1_INTERCONNECT */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = C2C */
	CLK54XX_C2C_L3_GICLK, /* OMAP5_C2C */
	CLK54XX_C2C_L3_GICLK, /* OMAP5_C2C_OCP_FW */
	CLK54XX_C2C_L4_GICLK, /* OMAP5_MODEM_ICR */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = DMA */
	CLK54XX_DMA_L3_GICLK, /* OMAP5_DMA_SYSTEM */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = MIPIEXT */
	CLK54XX_UNIPRO1_PHY_GFCLK, /* OMAP5_LLI */
	CLK54XX_MIPIEXT_L3_GICLK, /* OMAP5_LLI_OCP_FW */
	CLK54XX_MIPIEXT_L4_GICLK, /* OMAP5_MPHY */
	CLK54XX_UNIPRO1_PHY_GFCLK, /* OMAP5_UNIPRO1 */
	/* Voltage dom.: CORE, Power dom.: DSS, Clock domain = DSS */
	CLK54XX_DSS_GFCLK, /* OMAP5_DSS */
	CLK54XX_DSS_L3_GICLK, /* OMAP5_BB2D */
	/* Voltage dom.: CORE, Power dom.: L3INIT, Clock domain = L3INIT */
	CLK54XX_HSI_GFCLK, /* OMAP5_HSI */
	CLK54XX_L3INIT_L3_GICLK, /* OMAP5_IEEE1500_2_OCP */
	CLK54XX_MMC1_GFCLK, /* OMAP5_MMC1 */
	CLK54XX_MMC2_GFCLK, /* OMAP5_MMC2 */
	CLK54XX_L3INIT_L4_GICLK, /* OMAP5_OCPSCP1 */
	CLK54XX_UTMI_P1_GFCLK, /* OMAP5_USB_HOST_HS */
	CLK54XX_L3INIT_960M_FCLK, /* OMAP5_USB_OTG_SS */
	CLK54XX_TLL_CH0_GFCLK, /* OMAP5_USB_TLL_HS */
	CLK54XX_L3INIT_L3_GICLK, /* OMAP5_SATA */
	CLK54XX_UNIPRO2_PHY_GFCLK, /* OMAP5_UNIPRO2 */
	CLK54XX_L3INIT_L4_GICLK, /* OMAP5_MPHY_UNIPRO2 */
	CLK54XX_L3INIT_L4_GICLK, /* OMAP5_OCPSCP3 */
	/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_PER */
	CLK54XX_TIMER10_GFCLK, /* OMAP5_TIMER10 */
	CLK54XX_TIMER11_GFCLK, /* OMAP5_TIMER11 */
	CLK54XX_TIMER2_GFCLK, /* OMAP5_TIMER2 */
	CLK54XX_TIMER3_GFCLK, /* OMAP5_TIMER3 */
	CLK54XX_TIMER4_GFCLK, /* OMAP5_TIMER4 */
	CLK54XX_TIMER9_GFCLK, /* OMAP5_TIMER9 */
	CLK54XX_L4PER_L4_GICLK, /* OMAP5_ELM */
	CLK54XX_PER_32K_GFCLK, /* OMAP5_GPIO2 */
	CLK54XX_PER_32K_GFCLK, /* OMAP5_GPIO3 */
	CLK54XX_PER_32K_GFCLK, /* OMAP5_GPIO4 */
	CLK54XX_PER_32K_GFCLK, /* OMAP5_GPIO5 */
	CLK54XX_PER_32K_GFCLK, /* OMAP5_GPIO6 */
	CLK54XX_PER_32K_GFCLK, /* OMAP5_GPIO7 */
	CLK54XX_PER_32K_GFCLK, /* OMAP5_GPIO8 */
	CLK54XX_PER_12M_GFCLK, /* OMAP5_HDQ1W */
	CLK54XX_PER_96M_GFCLK, /* OMAP5_I2C1 */
	CLK54XX_PER_96M_GFCLK, /* OMAP5_I2C2 */
	CLK54XX_PER_96M_GFCLK, /* OMAP5_I2C3 */
	CLK54XX_PER_96M_GFCLK, /* OMAP5_I2C4 */
	CLK54XX_PER_96M_GFCLK, /* OMAP5_I2C5 */
	CLK54XX_L4PER_L4_GICLK, /* OMAP5_L4_PER_INTERCONNECT */
	CLK54XX_PER_48M_GFCLK, /* OMAP5_MCSPI1 */
	CLK54XX_PER_48M_GFCLK, /* OMAP5_MCSPI2 */
	CLK54XX_PER_48M_GFCLK, /* OMAP5_MCSPI3 */
	CLK54XX_PER_48M_GFCLK, /* OMAP5_MCSPI4 */
	CLK54XX_PER_48M_GFCLK, /* OMAP5_MMC3 */
	CLK54XX_PER_48M_GFCLK, /* OMAP5_MMC4 */
	CLK54XX_PER_96M_GFCLK, /* OMAP5_MMC5 */
	CLK54XX_PER_24M_GFCLK, /* OMAP5_SLIMBUS2 */
	CLK54XX_PER_48M_GFCLK, /* OMAP5_UART1 */
	CLK54XX_PER_48M_GFCLK, /* OMAP5_UART2 */
	CLK54XX_PER_48M_GFCLK, /* OMAP5_UART3 */
	CLK54XX_PER_48M_GFCLK, /* OMAP5_UART4 */
	CLK54XX_PER_48M_GFCLK, /* OMAP5_UART5 */
	CLK54XX_PER_48M_GFCLK, /* OMAP5_UART6 */
	/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_SEC */
	/* HS/EMU ONLY */
	CLK54XX_L4SEC_L3_GICLK, /* OMAP5_DMA_CRYPTO */
	CLK54XX_L4SEC_L3_GICLK, /* OMAP5_AES1 */
	CLK54XX_L4SEC_L3_GICLK, /* OMAP5_AES2 */
	CLK54XX_L4SEC_L3_GICLK, /* OMAP5_SHA2MD5 */
	CLK54XX_L4SEC_L4_GICLK, /* OMAP5_RNG */
	CLK54XX_L4SEC_L4_GICLK, /* OMAP5_DES3DES */
	CLK54XX_L4SEC_L4_GICLK, /* OMAP5_PKA */
	/* Voltage dom.: CORE, Power dom.: ABE, Clock domain = ABE */
	CLK54XX_AESS_FCLK, /* OMAP5_AESS */
	CLK54XX_DMIC_GFCLK, /* OMAP5_DMIC */
	CLK54XX_ABE_GICLK, /* OMAP5_L4_ABE_INTERCONNECT */
	CLK54XX_MCASP1_GFCLK, /* OMAP5_MCASP */
	CLK54XX_MCBSP1_GFCLK, /* OMAP5_MCBSP1 */
	CLK54XX_MCBSP2_GFCLK, /* OMAP5_MCBSP2 */
	CLK54XX_MCBSP3_GFCLK, /* OMAP5_MCBSP3 */
	CLK54XX_PAD_GCLKS, /* OMAP5_MCPDM */
	CLK54XX_SLIMBUS_UCLKS, /* OMAP5_SLIMBUS1 */
	CLK54XX_TIMER5_GFCLK, /* OMAP5_TIMER5 */
	CLK54XX_TIMER6_GFCLK, /* OMAP5_TIMER6 */
	CLK54XX_TIMER7_GFCLK, /* OMAP5_TIMER7 */
	CLK54XX_TIMER8_GFCLK, /* OMAP5_TIMER8 */
	CLK54XX_ABE_32K_CLK, /* OMAP5_WD_TIMER3 */
	/* Voltage dom.: MM, Power dom.: DSP, Clock domain = DSP */
	CLK54XX_DSP_GCLK, /* OMAP5_DSP */
	/* Voltage dom.: MM, Power dom.: GPU, Clock domain = GPU */
	CLK54XX_GPU_CORE_GCLK, /* OMAP5_GPU */
	/* Voltage dom.: MM, Power dom.: IVA, Clock domain = IVA */
	CLK54XX_IVA_GCLK, /* OMAP5_IVA */
	CLK54XX_IVA_GCLK, /* OMAP5_SL2 */
	/* Voltage dom.: MPU, Power dom.: MPUAON Clock domain = MPU */
	CLK54XX_MPU_GCLK}; /* OMAP5_MPU */


const clkdm54xx_id mod54xx_clkdm_table[MOD54XX_ID_MAX] = {
	/* Voltage dom.: WKUP, Power dom.: EMU, Clock dom. = EMU */
	CLKDM54XX_EMU, /* OMAP5_DEBUGSS */
	/* Voltage dom.: WKUP, Power dom.: WKUPAON, Clock domain = WKUPAON */
	CLKDM54XX_WKUPAON, /* OMAP5_CTRL_MODULE_WKUP */
	CLKDM54XX_WKUPAON, /* OMAP5_L4WKUP_INTERCONNECT */
	CLKDM54XX_WKUPAON, /* OMAP5_GPIO1 */
	CLKDM54XX_WKUPAON, /* OMAP5_TIMER1 */
	CLKDM54XX_WKUPAON, /* OMAP5_WD_TIMER2 */
	CLKDM54XX_WKUPAON, /* OMAP5_SARRAM */
	CLKDM54XX_WKUPAON, /* OMAP5_COUNTER_32K */
	CLKDM54XX_WKUPAON, /* OMAP5_KBD */
	CLKDM54XX_WKUPAON, /* IO_SRCOMP_WKUP */
	/* HS/EMU ONLY */
	CLKDM54XX_WKUPAON, /* OMAP5_TIMER12 */
	CLKDM54XX_WKUPAON, /* OMAP5_WDT1 */
	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = COREAON */
	CLKDM54XX_COREAON, /* OMAP5_SMARTREFLEX_CORE */
	CLKDM54XX_COREAON, /* OMAP5_SMARTREFLEX_MM */
	CLKDM54XX_COREAON, /* OMAP5_SMARTREFLEX_MPU */
	CLKDM54XX_COREAON, /* OMAP5_BANDGAPTS */
	CLKDM54XX_COREAON, /* OMAP5_IO_SRCOMP_CORE */
	CLKDM54XX_COREAON, /* OMAP5_USB_PHY_CORE */
	/* Voltage dom.: CORE, Power dom.: CAM, Clock domain = CAM */
	CLKDM54XX_CAM, /* OMAP5_FDIF */
	CLKDM54XX_CAM, /* OMAP5_ISS */
	CLKDM54XX_CAM, /* OMAP5_CAL */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L4CFG */
	CLKDM54XX_L4_CFG, /* OMAP5_CTRL_MODULE_CORE */
	CLKDM54XX_L4_CFG, /* OMAP5_SPINLOCK */
	CLKDM54XX_L4_CFG, /* OMAP5_L4_CFG_INTERCONNECT */
	CLKDM54XX_L4_CFG, /* OMAP5_MAILBOX */
	CLKDM54XX_L4_CFG, /* OMAP5_SARROM */
	CLKDM54XX_L4_CFG, /* OMAP5_OCP2SCP2 */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = EMIF */
	CLKDM54XX_EMIF, /* OMAP5_PHY_EMIF */
	CLKDM54XX_EMIF, /* OMAP5_DLL_EMIF */
	CLKDM54XX_EMIF, /* OMAP5_DMM */
	CLKDM54XX_EMIF, /* OMAP5_EMIF1 */
	CLKDM54XX_EMIF, /* OMAP5_EMIF2 */
	CLKDM54XX_EMIF, /* OMAP5_EMIF_OCP_FW */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = IPU */
	CLKDM54XX_IPU, /* OMAP5_IPU */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN2 */
	CLKDM54XX_L3_MAIN2, /* OMAP5_GPMC */
	CLKDM54XX_L3_MAIN2, /* OMAP5_L3_MAIN2_INTERCONNECT */
	CLKDM54XX_L3_MAIN2, /* OMAP5_OCMC_RAM */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_INSTR */
	CLKDM54XX_L3_INSTR, /* OMAP5_L3_MAIN3_INTERCONNECT */
	CLKDM54XX_L3_INSTR, /* OMAP5_L3_INSTR_INTERCONNECT */
	CLKDM54XX_L3_INSTR, /* OMAP5_OCP_WP_NOC */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN1 */
	CLKDM54XX_L3_MAIN1, /* OMAP5_L3_MAIN1_INTERCONNECT */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = C2C */
	CLKDM54XX_C2C, /* OMAP5_C2C */
	CLKDM54XX_C2C, /* OMAP5_C2C_OCP_FW */
	CLKDM54XX_C2C, /* OMAP5_MODEM_ICR */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = DMA */
	CLKDM54XX_DMA, /* OMAP5_DMA_SYSTEM */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = MIPIEXT */
	CLKDM54XX_MIPIEXT, /* OMAP5_LLI */
	CLKDM54XX_MIPIEXT, /* OMAP5_LLI_OCP_FW */
	CLKDM54XX_MIPIEXT, /* OMAP5_MPHY */
	CLKDM54XX_MIPIEXT, /* OMAP5_UNIPRO1 */
	/* Voltage dom.: CORE, Power dom.: DSS, Clock domain = DSS */
	CLKDM54XX_DSS, /* OMAP5_DSS */
	CLKDM54XX_DSS, /* OMAP5_BB2D */
	/* Voltage dom.: CORE, Power dom.: L3INIT, Clock domain = L3INIT */
	CLKDM54XX_L3_INIT, /* OMAP5_HSI */
	CLKDM54XX_L3_INIT, /* OMAP5_IEEE1500_2_OCP */
	CLKDM54XX_L3_INIT, /* OMAP5_MMC1 */
	CLKDM54XX_L3_INIT, /* OMAP5_MMC2 */
	CLKDM54XX_L3_INIT, /* OMAP5_OCPSCP1 */
	CLKDM54XX_L3_INIT, /* OMAP5_USB_HOST_HS */
	CLKDM54XX_L3_INIT, /* OMAP5_USB_OTG_SS */
	CLKDM54XX_L3_INIT, /* OMAP5_USB_TLL_HS */
	CLKDM54XX_L3_INIT, /* OMAP5_SATA */
	CLKDM54XX_L3_INIT, /* OMAP5_UNIPRO2 */
	CLKDM54XX_L3_INIT, /* OMAP5_MPHY_UNIPRO2 */
	CLKDM54XX_L3_INIT, /* OMAP5_OCPSCP3 */
	/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_PER */
	CLKDM54XX_L4_PER, /* OMAP5_TIMER10 */
	CLKDM54XX_L4_PER, /* OMAP5_TIMER11 */
	CLKDM54XX_L4_PER, /* OMAP5_TIMER2 */
	CLKDM54XX_L4_PER, /* OMAP5_TIMER3 */
	CLKDM54XX_L4_PER, /* OMAP5_TIMER4 */
	CLKDM54XX_L4_PER, /* OMAP5_TIMER9 */
	CLKDM54XX_L4_PER, /* OMAP5_ELM */
	CLKDM54XX_L4_PER, /* OMAP5_GPIO2 */
	CLKDM54XX_L4_PER, /* OMAP5_GPIO3 */
	CLKDM54XX_L4_PER, /* OMAP5_GPIO4 */
	CLKDM54XX_L4_PER, /* OMAP5_GPIO5 */
	CLKDM54XX_L4_PER, /* OMAP5_GPIO6 */
	CLKDM54XX_L4_PER, /* OMAP5_GPIO7 */
	CLKDM54XX_L4_PER, /* OMAP5_GPIO8 */
	CLKDM54XX_L4_PER, /* OMAP5_HDQ1W */
	CLKDM54XX_L4_PER, /* OMAP5_I2C1 */
	CLKDM54XX_L4_PER, /* OMAP5_I2C2 */
	CLKDM54XX_L4_PER, /* OMAP5_I2C3 */
	CLKDM54XX_L4_PER, /* OMAP5_I2C4 */
	CLKDM54XX_L4_PER, /* OMAP5_I2C5 */
	CLKDM54XX_L4_PER, /* OMAP5_L4_PER_INTERCONNECT */
	CLKDM54XX_L4_PER, /* OMAP5_MCSPI1 */
	CLKDM54XX_L4_PER, /* OMAP5_MCSPI2 */
	CLKDM54XX_L4_PER, /* OMAP5_MCSPI3 */
	CLKDM54XX_L4_PER, /* OMAP5_MCSPI4 */
	CLKDM54XX_L4_PER, /* OMAP5_MMC3 */
	CLKDM54XX_L4_PER, /* OMAP5_MMC4 */
	CLKDM54XX_L4_PER, /* OMAP5_MMC5 */
	CLKDM54XX_L4_PER, /* OMAP5_SLIMBUS2 */
	CLKDM54XX_L4_PER, /* OMAP5_UART1 */
	CLKDM54XX_L4_PER, /* OMAP5_UART2 */
	CLKDM54XX_L4_PER, /* OMAP5_UART3 */
	CLKDM54XX_L4_PER, /* OMAP5_UART4 */
	CLKDM54XX_L4_PER, /* OMAP5_UART5 */
	CLKDM54XX_L4_PER, /* OMAP5_UART6 */
	/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_SEC */
	/* HS/EMU ONLY */
	CLKDM54XX_L4_SEC, /* OMAP5_DMA_CRYPTO */
	CLKDM54XX_L4_SEC, /* OMAP5_AES1 */
	CLKDM54XX_L4_SEC, /* OMAP5_AES2 */
	CLKDM54XX_L4_SEC, /* OMAP5_SHA2MD5 */
	CLKDM54XX_L4_SEC, /* OMAP5_RNG */
	CLKDM54XX_L4_SEC, /* OMAP5_DES3DES */
	CLKDM54XX_L4_SEC, /* OMAP5_PKA */
	/* Voltage dom.: CORE, Power dom.: ABE, Clock domain = ABE */
	CLKDM54XX_ABE, /* OMAP5_AESS */
	CLKDM54XX_ABE, /* OMAP5_DMIC */
	CLKDM54XX_ABE, /* OMAP5_L4_ABE_INTERCONNECT */
	CLKDM54XX_ABE, /* OMAP5_MCASP */
	CLKDM54XX_ABE, /* OMAP5_MCBSP1 */
	CLKDM54XX_ABE, /* OMAP5_MCBSP2 */
	CLKDM54XX_ABE, /* OMAP5_MCBSP3 */
	CLKDM54XX_ABE, /* OMAP5_MCPDM */
	CLKDM54XX_ABE, /* OMAP5_SLIMBUS1 */
	CLKDM54XX_ABE, /* OMAP5_TIMER5 */
	CLKDM54XX_ABE, /* OMAP5_TIMER6 */
	CLKDM54XX_ABE, /* OMAP5_TIMER7 */
	CLKDM54XX_ABE, /* OMAP5_TIMER8 */
	CLKDM54XX_ABE, /* OMAP5_WD_TIMER3 */
	/* Voltage dom.: MM, Power dom.: DSP, Clock domain = DSP */
	CLKDM54XX_DSP, /* OMAP5_DSP */
	/* Voltage dom.: MM, Power dom.: GPU, Clock domain = GPU */
	CLKDM54XX_GPU, /* OMAP5_GPU */
	/* Voltage dom.: MM, Power dom.: IVA, Clock domain = IVA */
	CLKDM54XX_IVA, /* OMAP5_IVA */
	CLKDM54XX_IVA, /* OMAP5_SL2 */
	/* Voltage dom.: MPU, Power dom.: MPUAON Clock domain = MPU */
	CLKDM54XX_MPU}; /* OMAP5_MPU */


reg *mod54xx_sysconfig_table[MOD54XX_ID_MAX] = {
	/* Voltage dom.: WKUP, Power dom.: EMU, Clock dom. = EMU */
	NULL, /* OMAP5_DEBUGSS */
	/* Voltage dom.: WKUP, Power dom.: WKUPAON, Clock domain = WKUPAON */
	NULL, /* OMAP5_CTRL_MODULE_WKUP */
	NULL, /* OMAP5_L4WKUP_INTERCONNECT */
	&omap5430_gpio1_sysconfig, /* OMAP5_GPIO1 */
	&omap5430_timer1_tiocp_cfg, /* OMAP5_TIMER1 */
	&omap5430_wd_timer2_l4interconnect_wdsc, /* OMAP5_WD_TIMER2 */
	NULL, /* OMAP5_SARRAM */
	&omap5430_counter_32k_sysconfig, /* OMAP5_COUNTER_32K */
	&omap5430_kbd_sysconfig, /* OMAP5_KBD */
	NULL, /* IO_SRCOMP_WKUP */
	/* HS/EMU ONLY */
	NULL, /* OMAP5_TIMER12 */
	NULL, /* OMAP5_WDT1 */
	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = COREAON */
	NULL, /* OMAP5_SMARTREFLEX_CORE */
	NULL, /* OMAP5_SMARTREFLEX_MM */
	NULL, /* OMAP5_SMARTREFLEX_MPU */
	NULL, /* OMAP5_BANDGAPTS */
	NULL, /* OMAP5_IO_SRCOMP_CORE */
	NULL, /* OMAP5_USB_PHY_CORE */
	/* Voltage dom.: CORE, Power dom.: CAM, Clock domain = CAM */
	&omap5430_fdif_sysconfig, /* OMAP5_FDIF */
	&omap5430_iss_hl_sysconfig, /* OMAP5_ISS */
	&omap5430_cal_hl_sysconfig, /* OMAP5_CAL */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L4CFG */
	NULL, /* OMAP5_CTRL_MODULE_CORE */
	&omap5430_spinlock_sysconfig, /* OMAP5_SPINLOCK */
	NULL, /* OMAP5_L4_CFG_INTERCONNECT */
	&omap5430_mailbox_l4_cfginterconnect_mailbox_sysconfig, /* OMAP5_MAILBOX */
	NULL, /* OMAP5_SARROM */
	&omap5430_ocp2scp2_sysconfig, /* OMAP5_OCP2SCP2 */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = EMIF */
	NULL, /* OMAP5_PHY_EMIF */
	NULL, /* OMAP5_DLL_EMIF */
	&omap5430_dmm_sysconfig, /* OMAP5_DMM */
	NULL, /* OMAP5_EMIF1 */
	NULL, /* OMAP5_EMIF2 */
	NULL, /* OMAP5_EMIF_OCP_FW */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = IPU */
	NULL, /* OMAP5_IPU */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN2 */
	&omap5430_gpmc_sysconfig, /* OMAP5_GPMC */
	NULL, /* OMAP5_L3_MAIN2_INTERCONNECT */
	NULL, /* OMAP5_OCMC_RAM */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_INSTR */
	NULL, /* OMAP5_L3_MAIN3_INTERCONNECT */
	NULL, /* OMAP5_L3_INSTR_INTERCONNECT */
	&omap5430_ocp_wp_sysconfig, /* OMAP5_OCP_WP_NOC */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN1 */
	NULL, /* OMAP5_L3_MAIN1_INTERCONNECT */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = C2C */
	&omap5430_c2c_sysconfig, /* OMAP5_C2C */
	NULL, /* OMAP5_C2C_OCP_FW */
	&omap5430_modem_icr_mpu_pa_sys_config, /* OMAP5_MODEM_ICR */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = DMA */
	&omap5430_dma4_ocp_sysconfig, /* OMAP5_DMA_SYSTEM */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = MIPIEXT */
	NULL, /* OMAP5_LLI */
	NULL, /* OMAP5_LLI_OCP_FW */
	NULL, /* OMAP5_MPHY */
	&omap5430_unipro1_sysconfig, /* OMAP5_UNIPRO1 */
	/* Voltage dom.: CORE, Power dom.: DSS, Clock domain = DSS */
	&omap5430_dispc_l3_main_dispc_sysconfig, /* OMAP5_DSS */
	&omap5430_bb2d_sysconfig_pm, /* OMAP5_BB2D */
	/* Voltage dom.: CORE, Power dom.: L3INIT, Clock domain = L3INIT */
	&omap5430_hsi_sysconfig, /* OMAP5_HSI */
	NULL, /* OMAP5_IEEE1500_2_OCP */
	&omap5430_mmchs1_hl_sysconfig, /* OMAP5_MMC1 */
	&omap5430_mmchs2_hl_sysconfig, /* OMAP5_MMC2 */
	&omap5430_ocp2scp1_sysconfig, /* OMAP5_OCPSCP1 */
	&omap5430_uhh_sysconfig, /* OMAP5_USB_HOST_HS */
	&omap5430_usbotgss_sysconfig, /* OMAP5_USB_OTG_SS */
	&omap5430_usbtll_sysconfig, /* OMAP5_USB_TLL_HS */
	&omap5430_sata_sysconfig, /* OMAP5_SATA */
	&omap5430_unipro2_sysconfig, /* OMAP5_UNIPRO2 */
	NULL, /* OMAP5_MPHY_UNIPRO2 */
	&omap5430_ocp2scp3_sysconfig, /* OMAP5_OCPSCP3 */
	/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_PER */
	&omap5430_timer10_l4interconnect_tiocp_cfg, /* OMAP5_TIMER10 */
	&omap5430_timer11_l4interconnect_tiocp_cfg, /* OMAP5_TIMER11 */
	&omap5430_timer2_l4interconnect_tiocp_cfg, /* OMAP5_TIMER2 */
	&omap5430_timer3_l4interconnect_tiocp_cfg, /* OMAP5_TIMER3 */
	&omap5430_timer4_l4interconnect_tiocp_cfg, /* OMAP5_TIMER4 */
	&omap5430_timer9_l4interconnect_tiocp_cfg, /* OMAP5_TIMER9 */
	&omap5430_elm_sysconfig, /* OMAP5_ELM */
	&omap5430_gpio2_sysconfig, /* OMAP5_GPIO2 */
	&omap5430_gpio3_sysconfig, /* OMAP5_GPIO3 */
	&omap5430_gpio4_sysconfig, /* OMAP5_GPIO4 */
	&omap5430_gpio5_sysconfig, /* OMAP5_GPIO5 */
	&omap5430_gpio6_sysconfig, /* OMAP5_GPIO6 */
	&omap5430_gpio7_sysconfig, /* OMAP5_GPIO7 */
	&omap5430_gpio8_sysconfig, /* OMAP5_GPIO8 */
	&omap5430_hdq_sysconfig, /* OMAP5_HDQ1W */
	&omap5430_i2c1_sysc, /* OMAP5_I2C1 */
	&omap5430_i2c2_sysc, /* OMAP5_I2C2 */
	&omap5430_i2c3_sysc, /* OMAP5_I2C3 */
	&omap5430_i2c4_sysc, /* OMAP5_I2C4 */
	&omap5430_i2c5_sysc, /* OMAP5_I2C5 */
	NULL, /* OMAP5_L4_PER_INTERCONNECT */
	&omap5430_mcspi1_hl_sysconfig, /* OMAP5_MCSPI1 */
	&omap5430_mcspi2_hl_sysconfig, /* OMAP5_MCSPI2 */
	&omap5430_mcspi3_hl_sysconfig, /* OMAP5_MCSPI3 */
	&omap5430_mcspi4_hl_sysconfig, /* OMAP5_MCSPI4 */
	&omap5430_mmchs3_hl_sysconfig, /* OMAP5_MMC3 */
	&omap5430_mmchs4_hl_sysconfig, /* OMAP5_MMC4 */
	&omap5430_mmchs5_hl_sysconfig, /* OMAP5_MMC5 */
	&omap5430_slimbus2_cmp_sysconfig, /* OMAP5_SLIMBUS2 */
	&omap5430_uart1_sysc, /* OMAP5_UART1 */
	&omap5430_uart2_sysc, /* OMAP5_UART2 */
	&omap5430_uart3_sysc, /* OMAP5_UART3 */
	&omap5430_uart4_sysc, /* OMAP5_UART4 */
	&omap5430_uart5_sysc, /* OMAP5_UART5 */
	&omap5430_uart6_sysc, /* OMAP5_UART6 */
	/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_SEC */
	/* HS/EMU ONLY */
	NULL, /* OMAP5_DMA_CRYPTO */
	NULL, /* OMAP5_AES1 */
	NULL, /* OMAP5_AES2 */
	NULL, /* OMAP5_SHA2MD5 */
	NULL, /* OMAP5_RNG */
	NULL, /* OMAP5_DES3DES */
	NULL, /* OMAP5_PKA */
	/* Voltage dom.: CORE, Power dom.: ABE, Clock domain = ABE */
	&omap5430_aess_sysconfig, /* OMAP5_AESS */
	&omap5430_dmic_cortex_a15_dmic_sysconfig, /* OMAP5_DMIC */
	NULL, /* OMAP5_L4_ABE_INTERCONNECT */
	&omap5430_mcasp_mpu_mcasp_sysconfig, /* OMAP5_MCASP */
	&omap5430_mcbsp1_cortex_a15_mcbsplp_sysconfig_reg, /* OMAP5_MCBSP1 */
	&omap5430_mcbsp2_cortex_a15_mcbsplp_sysconfig_reg, /* OMAP5_MCBSP2 */
	&omap5430_mcbsp3_cortex_a15_mcbsplp_sysconfig_reg, /* OMAP5_MCBSP3 */
	&omap5430_mcpdm_cortex_a15_mcpdm_sysconfig, /* OMAP5_MCPDM */
	&omap5430_slimbus1_mpu_slimbus_cmp_sysconfig, /* OMAP5_SLIMBUS1 */
	&omap5430_timer5_mpu_tiocp_cfg, /* OMAP5_TIMER5 */
	&omap5430_timer6_mpu_tiocp_cfg, /* OMAP5_TIMER6 */
	&omap5430_timer7_mpu_tiocp_cfg, /* OMAP5_TIMER7 */
	&omap5430_timer8_mpu_tiocp_cfg, /* OMAP5_TIMER8 */
	&omap5430_wd_timer3_l3interconnect_wdsc, /* OMAP5_WD_TIMER3 */
	/* Voltage dom.: MM, Power dom.: DSP, Clock domain = DSP */
	&omap5430_dsp_sysc_sysconfig, /* OMAP5_DSP */
	/* Voltage dom.: MM, Power dom.: GPU, Clock domain = GPU */
	&omap5430_gpu_sysconfig, /* OMAP5_GPU */
	/* Voltage dom.: MM, Power dom.: IVA, Clock domain = IVA */
	NULL, /* OMAP5_IVA */
	NULL, /* OMAP5_SL2 */
	/* Voltage dom.: MPU, Power dom.: MPUAON Clock domain = MPU */
	NULL}; /* OMAP5_MPU */


reg *mod54xxes1_cm_clkctrl_reg_table[MOD54XX_ID_MAX] = {
	/* Voltage dom.: WKUP, Power dom.: EMU, Clock dom. = EMU */
	&omap5430es1_cm_emu_debugss_clkctrl, /* OMAP5_DEBUGSS */
	/* Voltage dom.: WKUP, Power dom.: WKUPAON, Clock domain = WKUPAON */
	NULL, /* OMAP5_CTRL_MODULE_WKUP */
	&omap5430es1_cm_wkupaon_l4_wkup_clkctrl, /* OMAP5_L4WKUP_INTERCONNECT */
	&omap5430es1_cm_wkupaon_gpio1_clkctrl, /* OMAP5_GPIO1 */
	&omap5430es1_cm_wkupaon_timer1_clkctrl, /* OMAP5_TIMER1 */
	&omap5430es1_cm_wkupaon_wd_timer2_clkctrl, /* OMAP5_WD_TIMER2 */
	&omap5430es1_cm_wkupaon_sar_ram_clkctrl, /* OMAP5_SARRAM */
	&omap5430es1_cm_wkupaon_counter_32k_clkctrl, /* OMAP5_COUNTER_32K */
	&omap5430es1_cm_wkupaon_kbd_clkctrl, /* OMAP5_KBD */
	&omap5430es1_cm_wkupaon_io_srcomp_clkctrl, /* IO_SRCOMP_WKUP */
	/* HS/EMU ONLY */
	NULL, /* OMAP5_TIMER12 */
	NULL, /* OMAP5_WDT1 */
	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = COREAON */
	&omap5430es1_cm_coreaon_smartreflex_core_clkctrl, /* OMAP5_SMARTREFLEX_CORE */
	&omap5430es1_cm_coreaon_smartreflex_mm_clkctrl, /* OMAP5_SMARTREFLEX_MM */
	&omap5430es1_cm_coreaon_smartreflex_mpu_clkctrl, /* OMAP5_SMARTREFLEX_MPU */
	&omap5430es1_cm_coreaon_bandgap_clkctrl, /* OMAP5_BANDGAPTS */
	&omap5430es1_cm_coreaon_io_srcomp_clkctrl, /* OMAP5_IO_SRCOMP_CORE */
	&omap5430es1_cm_coreaon_usb_phy_core_clkctrl, /* OMAP5_USB_PHY_CORE */
	/* Voltage dom.: CORE, Power dom.: CAM, Clock domain = CAM */
	&omap5430es1_cm_cam_fdif_clkctrl, /* OMAP5_FDIF */
	&omap5430es1_cm_cam_iss_clkctrl, /* OMAP5_ISS */
	&omap5430es1_cm_cam_cal_clkctrl, /* OMAP5_CAL */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L4CFG */
	NULL, /* OMAP5_CTRL_MODULE_CORE */
	&omap5430es1_cm_l4cfg_spinlock_clkctrl, /* OMAP5_SPINLOCK */
	&omap5430es1_cm_l4cfg_l4_cfg_clkctrl, /* OMAP5_L4_CFG_INTERCONNECT */
	&omap5430es1_cm_l4cfg_mailbox_clkctrl, /* OMAP5_MAILBOX */
	&omap5430es1_cm_l4cfg_sar_rom_clkctrl, /* OMAP5_SARROM */
	&omap5430es1_cm_l4cfg_ocp2scp2_clkctrl, /* OMAP5_OCP2SCP2 */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = EMIF */
	NULL, /* OMAP5_PHY_EMIF */
	NULL, /* OMAP5_DLL_EMIF */
	&omap5430es1_cm_emif_dmm_clkctrl, /* OMAP5_DMM */
	&omap5430es1_cm_emif_emif1_clkctrl, /* OMAP5_EMIF1 */
	&omap5430es1_cm_emif_emif2_clkctrl, /* OMAP5_EMIF2 */
	&omap5430es1_cm_emif_emif_ocp_fw_clkctrl, /* OMAP5_EMIF_OCP_FW */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = IPU */
	&omap5430es1_cm_ipu_ipu_clkctrl, /* OMAP5_IPU */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN2 */
	&omap5430es1_cm_l3main2_gpmc_clkctrl, /* OMAP5_GPMC */
	&omap5430es1_cm_l3main2_l3_main_2_clkctrl, /* OMAP5_L3_MAIN2_INTERCONNECT */
	&omap5430es1_cm_l3main2_ocmc_ram_clkctrl, /* OMAP5_OCMC_RAM */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_INSTR */
	&omap5430es1_cm_l3instr_l3_main_3_clkctrl, /* OMAP5_L3_MAIN3_INTERCONNECT */
	&omap5430es1_cm_l3instr_l3_instr_clkctrl, /* OMAP5_L3_INSTR_INTERCONNECT */
	&omap5430es1_cm_l3instr_ocp_wp_noc_clkctrl, /* OMAP5_OCP_WP_NOC */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN1 */
	&omap5430es1_cm_l3main1_l3_main_1_clkctrl, /* OMAP5_L3_MAIN1_INTERCONNECT */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = C2C */
	&omap5430es1_cm_c2c_c2c_clkctrl, /* OMAP5_C2C */
	&omap5430es1_cm_c2c_c2c_ocp_fw_clkctrl, /* OMAP5_C2C_OCP_FW */
	&omap5430es1_cm_c2c_modem_icr_clkctrl, /* OMAP5_MODEM_ICR */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = DMA */
	&omap5430es1_cm_dma_dma_system_clkctrl, /* OMAP5_DMA_SYSTEM */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = MIPIEXT */
	&omap5430es1_cm_mipiext_lli_clkctrl, /* OMAP5_LLI */
	&omap5430es1_cm_mipiext_lli_ocp_fw_clkctrl, /* OMAP5_LLI_OCP_FW */
	&omap5430es1_cm_mipiext_mphy_clkctrl, /* OMAP5_MPHY */
	&omap5430es1_cm_mipiext_unipro1_clkctrl, /* OMAP5_UNIPRO1 */
	/* Voltage dom.: CORE, Power dom.: DSS, Clock domain = DSS */
	&omap5430es1_cm_dss_dss_clkctrl, /* OMAP5_DSS */
	&omap5430es1_cm_dss_bb2d_clkctrl, /* OMAP5_BB2D */
	/* Voltage dom.: CORE, Power dom.: L3INIT, Clock domain = L3INIT */
	&omap5430es1_cm_l3init_hsi_clkctrl, /* OMAP5_HSI */
	&omap5430es1_cm_l3init_ieee1500_2_ocp_clkctrl, /* OMAP5_IEEE1500_2_OCP */
	&omap5430es1_cm_l3init_mmc1_clkctrl, /* OMAP5_MMC1 */
	&omap5430es1_cm_l3init_mmc2_clkctrl, /* OMAP5_MMC2 */
	&omap5430es1_cm_l3init_ocp2scp1_clkctrl, /* OMAP5_OCPSCP1 */
	&omap5430es1_cm_l3init_usb_host_hs_clkctrl, /* OMAP5_USB_HOST_HS */
	&omap5430es1_cm_l3init_usb_otg_ss_clkctrl, /* OMAP5_USB_OTG_SS */
	&omap5430es1_cm_l3init_usb_tll_hs_clkctrl, /* OMAP5_USB_TLL_HS */
	&omap5430es1_cm_l3init_sata_clkctrl, /* OMAP5_SATA */
	&omap5430es1_cm_l3init_unipro2_clkctrl, /* OMAP5_UNIPRO2 */
	&omap5430es1_cm_l3init_mphy_unipro2_clkctrl, /* OMAP5_MPHY_UNIPRO2 */
	&omap5430es1_cm_l3init_ocp2scp3_clkctrl, /* OMAP5_OCPSCP3 */
	/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_PER */
	&omap5430es1_cm_l4per_timer10_clkctrl, /* OMAP5_TIMER10 */
	&omap5430es1_cm_l4per_timer11_clkctrl, /* OMAP5_TIMER11 */
	&omap5430es1_cm_l4per_timer2_clkctrl, /* OMAP5_TIMER2 */
	&omap5430es1_cm_l4per_timer3_clkctrl, /* OMAP5_TIMER3 */
	&omap5430es1_cm_l4per_timer4_clkctrl, /* OMAP5_TIMER4 */
	&omap5430es1_cm_l4per_timer9_clkctrl, /* OMAP5_TIMER9 */
	&omap5430es1_cm_l4per_elm_clkctrl, /* OMAP5_ELM */
	&omap5430es1_cm_l4per_gpio2_clkctrl, /* OMAP5_GPIO2 */
	&omap5430es1_cm_l4per_gpio3_clkctrl, /* OMAP5_GPIO3 */
	&omap5430es1_cm_l4per_gpio4_clkctrl, /* OMAP5_GPIO4 */
	&omap5430es1_cm_l4per_gpio5_clkctrl, /* OMAP5_GPIO5 */
	&omap5430es1_cm_l4per_gpio6_clkctrl, /* OMAP5_GPIO6 */
	&omap5430es1_cm_l4per_gpio7_clkctrl, /* OMAP5_GPIO7 */
	&omap5430es1_cm_l4per_gpio8_clkctrl, /* OMAP5_GPIO8 */
	&omap5430es1_cm_l4per_hdq1w_clkctrl, /* OMAP5_HDQ1W */
	&omap5430es1_cm_l4per_i2c1_clkctrl, /* OMAP5_I2C1 */
	&omap5430es1_cm_l4per_i2c2_clkctrl, /* OMAP5_I2C2 */
	&omap5430es1_cm_l4per_i2c3_clkctrl, /* OMAP5_I2C3 */
	&omap5430es1_cm_l4per_i2c4_clkctrl, /* OMAP5_I2C4 */
	&omap5430es1_cm_l4per_i2c5_clkctrl, /* OMAP5_I2C5 */
	&omap5430es1_cm_l4per_l4_per_clkctrl, /* OMAP5_L4_PER_INTERCONNECT */
	&omap5430es1_cm_l4per_mcspi1_clkctrl, /* OMAP5_MCSPI1 */
	&omap5430es1_cm_l4per_mcspi2_clkctrl, /* OMAP5_MCSPI2 */
	&omap5430es1_cm_l4per_mcspi3_clkctrl, /* OMAP5_MCSPI3 */
	&omap5430es1_cm_l4per_mcspi4_clkctrl, /* OMAP5_MCSPI4 */
	&omap5430es1_cm_l4per_mmc3_clkctrl, /* OMAP5_MMC3 */
	&omap5430es1_cm_l4per_mmc4_clkctrl, /* OMAP5_MMC4 */
	&omap5430es1_cm_l4per_mmc5_clkctrl, /* OMAP5_MMC5 */
	&omap5430es1_cm_l4per_slimbus2_clkctrl, /* OMAP5_SLIMBUS2 */
	&omap5430es1_cm_l4per_uart1_clkctrl, /* OMAP5_UART1 */
	&omap5430es1_cm_l4per_uart2_clkctrl, /* OMAP5_UART2 */
	&omap5430es1_cm_l4per_uart3_clkctrl, /* OMAP5_UART3 */
	&omap5430es1_cm_l4per_uart4_clkctrl, /* OMAP5_UART4 */
	&omap5430es1_cm_l4per_uart5_clkctrl, /* OMAP5_UART5 */
	&omap5430es1_cm_l4per_uart6_clkctrl, /* OMAP5_UART6 */
	/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_SEC */
	/* HS/EMU ONLY */
	NULL, /* OMAP5_DMA_CRYPTO */
	NULL, /* OMAP5_AES1 */
	NULL, /* OMAP5_AES2 */
	NULL, /* OMAP5_SHA2MD5 */
	NULL, /* OMAP5_RNG */
	NULL, /* OMAP5_DES3DES */
	NULL, /* OMAP5_PKA */
	/* Voltage dom.: CORE, Power dom.: ABE, Clock domain = ABE */
	&omap5430es1_cm_abe_aess_clkctrl, /* OMAP5_AESS */
	&omap5430es1_cm_abe_dmic_clkctrl, /* OMAP5_DMIC */
	&omap5430es1_cm_abe_l4_abe_clkctrl, /* OMAP5_L4_ABE_INTERCONNECT */
	&omap5430es1_cm_abe_mcasp_clkctrl, /* OMAP5_MCASP */
	&omap5430es1_cm_abe_mcbsp1_clkctrl, /* OMAP5_MCBSP1 */
	&omap5430es1_cm_abe_mcbsp2_clkctrl, /* OMAP5_MCBSP2 */
	&omap5430es1_cm_abe_mcbsp3_clkctrl, /* OMAP5_MCBSP3 */
	&omap5430es1_cm_abe_mcpdm_clkctrl, /* OMAP5_MCPDM */
	&omap5430es1_cm_abe_slimbus1_clkctrl, /* OMAP5_SLIMBUS1 */
	&omap5430es1_cm_abe_timer5_clkctrl, /* OMAP5_TIMER5 */
	&omap5430es1_cm_abe_timer6_clkctrl, /* OMAP5_TIMER6 */
	&omap5430es1_cm_abe_timer7_clkctrl, /* OMAP5_TIMER7 */
	&omap5430es1_cm_abe_timer8_clkctrl, /* OMAP5_TIMER8 */
	&omap5430es1_cm_abe_wd_timer3_clkctrl, /* OMAP5_WD_TIMER3 */
	/* Voltage dom.: MM, Power dom.: DSP, Clock domain = DSP */
	&omap5430es1_cm_dsp_dsp_clkctrl, /* OMAP5_DSP */
	/* Voltage dom.: MM, Power dom.: GPU, Clock domain = GPU */
	&omap5430es1_cm_gpu_gpu_clkctrl, /* OMAP5_GPU */
	/* Voltage dom.: MM, Power dom.: IVA, Clock domain = IVA */
	&omap5430es1_cm_iva_iva_clkctrl, /* OMAP5_IVA */
	&omap5430es1_cm_iva_sl2_clkctrl, /* OMAP5_SL2 */
	/* Voltage dom.: MPU, Power dom.: MPUAON Clock domain = MPU */
	&omap5430es1_cm_mpu_mpu_clkctrl}; /* OMAP5_MPU */


reg *mod54xx_cm_clkctrl_reg_table[MOD54XX_ID_MAX] = {
	/* Voltage dom.: WKUP, Power dom.: EMU, Clock dom. = EMU */
	&omap5430_cm_emu_debugss_clkctrl, /* OMAP5_DEBUGSS */
	/* Voltage dom.: WKUP, Power dom.: WKUPAON, Clock domain = WKUPAON */
	NULL, /* OMAP5_CTRL_MODULE_WKUP */
	&omap5430_cm_wkupaon_l4_wkup_clkctrl, /* OMAP5_L4WKUP_INTERCONNECT */
	&omap5430_cm_wkupaon_gpio1_clkctrl, /* OMAP5_GPIO1 */
	&omap5430_cm_wkupaon_timer1_clkctrl, /* OMAP5_TIMER1 */
	&omap5430_cm_wkupaon_wd_timer2_clkctrl, /* OMAP5_WD_TIMER2 */
	&omap5430_cm_wkupaon_sar_ram_clkctrl, /* OMAP5_SARRAM */
	&omap5430_cm_wkupaon_counter_32k_clkctrl, /* OMAP5_COUNTER_32K */
	&omap5430_cm_wkupaon_kbd_clkctrl, /* OMAP5_KBD */
	&omap5430_cm_wkupaon_io_srcomp_clkctrl, /* IO_SRCOMP_WKUP */
	/* HS/EMU ONLY */
	NULL, /* OMAP5_TIMER12 */
	NULL, /* OMAP5_WDT1 */
	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = COREAON */
	&omap5430_cm_coreaon_smartreflex_core_clkctrl, /* OMAP5_SMARTREFLEX_CORE */
	&omap5430_cm_coreaon_smartreflex_mm_clkctrl, /* OMAP5_SMARTREFLEX_MM */
	&omap5430_cm_coreaon_smartreflex_mpu_clkctrl, /* OMAP5_SMARTREFLEX_MPU */
	NULL, /* OMAP5_BANDGAPTS */
	&omap5430_cm_coreaon_io_srcomp_clkctrl, /* OMAP5_IO_SRCOMP_CORE */
	&omap5430_cm_coreaon_usb_phy_core_clkctrl, /* OMAP5_USB_PHY_CORE */
	/* Voltage dom.: CORE, Power dom.: CAM, Clock domain = CAM */
	&omap5430_cm_cam_fdif_clkctrl, /* OMAP5_FDIF */
	&omap5430_cm_cam_iss_clkctrl, /* OMAP5_ISS */
	&omap5430_cm_cam_cal_clkctrl, /* OMAP5_CAL */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L4CFG */
	NULL, /* OMAP5_CTRL_MODULE_CORE */
	&omap5430_cm_l4cfg_spinlock_clkctrl, /* OMAP5_SPINLOCK */
	&omap5430_cm_l4cfg_l4_cfg_clkctrl, /* OMAP5_L4_CFG_INTERCONNECT */
	&omap5430_cm_l4cfg_mailbox_clkctrl, /* OMAP5_MAILBOX */
	&omap5430_cm_l4cfg_sar_rom_clkctrl, /* OMAP5_SARROM */
	&omap5430_cm_l4cfg_ocp2scp2_clkctrl, /* OMAP5_OCP2SCP2 */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = EMIF */
	NULL, /* OMAP5_PHY_EMIF */
	NULL, /* OMAP5_DLL_EMIF */
	&omap5430_cm_emif_dmm_clkctrl, /* OMAP5_DMM */
	&omap5430_cm_emif_emif1_clkctrl, /* OMAP5_EMIF1 */
	&omap5430_cm_emif_emif2_clkctrl, /* OMAP5_EMIF2 */
	&omap5430_cm_emif_emif_ocp_fw_clkctrl, /* OMAP5_EMIF_OCP_FW */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = IPU */
	&omap5430_cm_ipu_ipu_clkctrl, /* OMAP5_IPU */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN2 */
	&omap5430_cm_l3main2_gpmc_clkctrl, /* OMAP5_GPMC */
	&omap5430_cm_l3main2_l3_main_2_clkctrl, /* OMAP5_L3_MAIN2_INTERCONNECT */
	&omap5430_cm_l3main2_ocmc_ram_clkctrl, /* OMAP5_OCMC_RAM */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_INSTR */
	&omap5430_cm_l3instr_l3_main_3_clkctrl, /* OMAP5_L3_MAIN3_INTERCONNECT */
	&omap5430_cm_l3instr_l3_instr_clkctrl, /* OMAP5_L3_INSTR_INTERCONNECT */
	&omap5430_cm_l3instr_ocp_wp_noc_clkctrl, /* OMAP5_OCP_WP_NOC */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN1 */
	&omap5430_cm_l3main1_l3_main_1_clkctrl, /* OMAP5_L3_MAIN1_INTERCONNECT */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = C2C */
	&omap5430_cm_c2c_c2c_clkctrl, /* OMAP5_C2C */
	&omap5430_cm_c2c_c2c_ocp_fw_clkctrl, /* OMAP5_C2C_OCP_FW */
	&omap5430_cm_c2c_modem_icr_clkctrl, /* OMAP5_MODEM_ICR */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = DMA */
	&omap5430_cm_dma_dma_system_clkctrl, /* OMAP5_DMA_SYSTEM */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = MIPIEXT */
	&omap5430_cm_mipiext_lli_clkctrl, /* OMAP5_LLI */
	&omap5430_cm_mipiext_lli_ocp_fw_clkctrl, /* OMAP5_LLI_OCP_FW */
	&omap5430_cm_mipiext_mphy_clkctrl, /* OMAP5_MPHY */
	NULL, /* OMAP5_UNIPRO1 */
	/* Voltage dom.: CORE, Power dom.: DSS, Clock domain = DSS */
	&omap5430_cm_dss_dss_clkctrl, /* OMAP5_DSS */
	&omap5430_cm_dss_bb2d_clkctrl, /* OMAP5_BB2D */
	/* Voltage dom.: CORE, Power dom.: L3INIT, Clock domain = L3INIT */
	&omap5430_cm_l3init_hsi_clkctrl, /* OMAP5_HSI */
	&omap5430_cm_l3init_ieee1500_2_ocp_clkctrl, /* OMAP5_IEEE1500_2_OCP */
	&omap5430_cm_l3init_mmc1_clkctrl, /* OMAP5_MMC1 */
	&omap5430_cm_l3init_mmc2_clkctrl, /* OMAP5_MMC2 */
	&omap5430_cm_l3init_ocp2scp1_clkctrl, /* OMAP5_OCPSCP1 */
	&omap5430_cm_l3init_usb_host_hs_clkctrl, /* OMAP5_USB_HOST_HS */
	&omap5430_cm_l3init_usb_otg_ss_clkctrl, /* OMAP5_USB_OTG_SS */
	&omap5430_cm_l3init_usb_tll_hs_clkctrl, /* OMAP5_USB_TLL_HS */
	&omap5430_cm_l3init_sata_clkctrl, /* OMAP5_SATA */
	&omap5430_cm_l3init_unipro2_clkctrl, /* OMAP5_UNIPRO2 */
	&omap5430_cm_l3init_mphy_unipro2_clkctrl, /* OMAP5_MPHY_UNIPRO2 */
	&omap5430_cm_l3init_ocp2scp3_clkctrl, /* OMAP5_OCPSCP3 */
	/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_PER */
	&omap5430_cm_l4per_timer10_clkctrl, /* OMAP5_TIMER10 */
	&omap5430_cm_l4per_timer11_clkctrl, /* OMAP5_TIMER11 */
	&omap5430_cm_l4per_timer2_clkctrl, /* OMAP5_TIMER2 */
	&omap5430_cm_l4per_timer3_clkctrl, /* OMAP5_TIMER3 */
	&omap5430_cm_l4per_timer4_clkctrl, /* OMAP5_TIMER4 */
	&omap5430_cm_l4per_timer9_clkctrl, /* OMAP5_TIMER9 */
	&omap5430_cm_l4per_elm_clkctrl, /* OMAP5_ELM */
	&omap5430_cm_l4per_gpio2_clkctrl, /* OMAP5_GPIO2 */
	&omap5430_cm_l4per_gpio3_clkctrl, /* OMAP5_GPIO3 */
	&omap5430_cm_l4per_gpio4_clkctrl, /* OMAP5_GPIO4 */
	&omap5430_cm_l4per_gpio5_clkctrl, /* OMAP5_GPIO5 */
	&omap5430_cm_l4per_gpio6_clkctrl, /* OMAP5_GPIO6 */
	&omap5430_cm_l4per_gpio7_clkctrl, /* OMAP5_GPIO7 */
	&omap5430_cm_l4per_gpio8_clkctrl, /* OMAP5_GPIO8 */
	&omap5430_cm_l4per_hdq1w_clkctrl, /* OMAP5_HDQ1W */
	&omap5430_cm_l4per_i2c1_clkctrl, /* OMAP5_I2C1 */
	&omap5430_cm_l4per_i2c2_clkctrl, /* OMAP5_I2C2 */
	&omap5430_cm_l4per_i2c3_clkctrl, /* OMAP5_I2C3 */
	&omap5430_cm_l4per_i2c4_clkctrl, /* OMAP5_I2C4 */
	&omap5430_cm_l4per_i2c5_clkctrl, /* OMAP5_I2C5 */
	&omap5430_cm_l4per_l4_per_clkctrl, /* OMAP5_L4_PER_INTERCONNECT */
	&omap5430_cm_l4per_mcspi1_clkctrl, /* OMAP5_MCSPI1 */
	&omap5430_cm_l4per_mcspi2_clkctrl, /* OMAP5_MCSPI2 */
	&omap5430_cm_l4per_mcspi3_clkctrl, /* OMAP5_MCSPI3 */
	&omap5430_cm_l4per_mcspi4_clkctrl, /* OMAP5_MCSPI4 */
	&omap5430_cm_l4per_mmc3_clkctrl, /* OMAP5_MMC3 */
	&omap5430_cm_l4per_mmc4_clkctrl, /* OMAP5_MMC4 */
	&omap5430_cm_l4per_mmc5_clkctrl, /* OMAP5_MMC5 */
	NULL, /* OMAP5_SLIMBUS2 */
	&omap5430_cm_l4per_uart1_clkctrl, /* OMAP5_UART1 */
	&omap5430_cm_l4per_uart2_clkctrl, /* OMAP5_UART2 */
	&omap5430_cm_l4per_uart3_clkctrl, /* OMAP5_UART3 */
	&omap5430_cm_l4per_uart4_clkctrl, /* OMAP5_UART4 */
	&omap5430_cm_l4per_uart5_clkctrl, /* OMAP5_UART5 */
	&omap5430_cm_l4per_uart6_clkctrl, /* OMAP5_UART6 */
	/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_SEC */
	/* HS/EMU ONLY */
	NULL, /* OMAP5_DMA_CRYPTO */
	NULL, /* OMAP5_AES1 */
	NULL, /* OMAP5_AES2 */
	NULL, /* OMAP5_SHA2MD5 */
	NULL, /* OMAP5_RNG */
	NULL, /* OMAP5_DES3DES */
	NULL, /* OMAP5_PKA */
	/* Voltage dom.: CORE, Power dom.: ABE, Clock domain = ABE */
	&omap5430_cm_abe_aess_clkctrl, /* OMAP5_AESS */
	&omap5430_cm_abe_dmic_clkctrl, /* OMAP5_DMIC */
	&omap5430_cm_abe_l4_abe_clkctrl, /* OMAP5_L4_ABE_INTERCONNECT */
	&omap5430_cm_abe_mcasp_clkctrl, /* OMAP5_MCASP */
	&omap5430_cm_abe_mcbsp1_clkctrl, /* OMAP5_MCBSP1 */
	&omap5430_cm_abe_mcbsp2_clkctrl, /* OMAP5_MCBSP2 */
	&omap5430_cm_abe_mcbsp3_clkctrl, /* OMAP5_MCBSP3 */
	&omap5430_cm_abe_mcpdm_clkctrl, /* OMAP5_MCPDM */
	&omap5430_cm_abe_slimbus1_clkctrl, /* OMAP5_SLIMBUS1 */
	&omap5430_cm_abe_timer5_clkctrl, /* OMAP5_TIMER5 */
	&omap5430_cm_abe_timer6_clkctrl, /* OMAP5_TIMER6 */
	&omap5430_cm_abe_timer7_clkctrl, /* OMAP5_TIMER7 */
	&omap5430_cm_abe_timer8_clkctrl, /* OMAP5_TIMER8 */
	&omap5430_cm_abe_wd_timer3_clkctrl, /* OMAP5_WD_TIMER3 */
	/* Voltage dom.: MM, Power dom.: DSP, Clock domain = DSP */
	&omap5430_cm_dsp_dsp_clkctrl, /* OMAP5_DSP */
	/* Voltage dom.: MM, Power dom.: GPU, Clock domain = GPU */
	&omap5430_cm_gpu_gpu_clkctrl, /* OMAP5_GPU */
	/* Voltage dom.: MM, Power dom.: IVA, Clock domain = IVA */
	&omap5430_cm_iva_iva_clkctrl, /* OMAP5_IVA */
	&omap5430_cm_iva_sl2_clkctrl, /* OMAP5_SL2 */
	/* Voltage dom.: MPU, Power dom.: MPUAON Clock domain = MPU */
	&omap5430_cm_mpu_mpu_clkctrl}; /* OMAP5_MPU */


reg *mod54xxes1_rm_context_reg_table[MOD54XX_ID_MAX] = {
	/* Voltage dom.: WKUP, Power dom.: EMU, Clock dom. = EMU */
	&omap5430es1_rm_emu_debugss_context, /* OMAP5_DEBUGSS */
	/* Voltage dom.: WKUP, Power dom.: WKUPAON, Clock domain = WKUPAON */
	NULL, /* OMAP5_CTRL_MODULE_WKUP */
	&omap5430es1_rm_wkupaon_l4_wkup_context, /* OMAP5_L4WKUP_INTERCONNECT */
	&omap5430es1_rm_wkupaon_gpio1_context, /* OMAP5_GPIO1 */
	&omap5430es1_rm_wkupaon_timer1_context, /* OMAP5_TIMER1 */
	&omap5430es1_rm_wkupaon_wd_timer2_context, /* OMAP5_WD_TIMER2 */
	&omap5430es1_rm_wkupaon_sar_ram_context, /* OMAP5_SARRAM */
	&omap5430es1_rm_wkupaon_counter_32k_context, /* OMAP5_COUNTER_32K */
	&omap5430es1_rm_wkupaon_kbd_context, /* OMAP5_KBD */
	NULL, /* IO_SRCOMP_WKUP */
	/* HS/EMU ONLY */
	NULL, /* OMAP5_TIMER12 */
	NULL, /* OMAP5_WDT1 */
	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = COREAON */
	&omap5430es1_rm_coreaon_smartreflex_core_context, /* OMAP5_SMARTREFLEX_CORE */
	&omap5430es1_rm_coreaon_smartreflex_mm_context, /* OMAP5_SMARTREFLEX_MM */
	&omap5430es1_rm_coreaon_smartreflex_mpu_context, /* OMAP5_SMARTREFLEX_MPU */
	NULL, /* OMAP5_BANDGAPTS */
	NULL, /* OMAP5_IO_SRCOMP_CORE */
	NULL, /* OMAP5_USB_PHY_CORE */
	/* Voltage dom.: CORE, Power dom.: CAM, Clock domain = CAM */
	&omap5430es1_rm_cam_fdif_context, /* OMAP5_FDIF */
	&omap5430es1_rm_cam_iss_context, /* OMAP5_ISS */
	&omap5430es1_rm_cam_cal_context, /* OMAP5_CAL */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L4CFG */
	NULL, /* OMAP5_CTRL_MODULE_CORE */
	&omap5430es1_rm_l4cfg_spinlock_context, /* OMAP5_SPINLOCK */
	&omap5430es1_rm_l4cfg_l4_cfg_context, /* OMAP5_L4_CFG_INTERCONNECT */
	&omap5430es1_rm_l4cfg_mailbox_context, /* OMAP5_MAILBOX */
	&omap5430es1_rm_l4cfg_sar_rom_context, /* OMAP5_SARROM */
	&omap5430es1_rm_l4cfg_ocp2scp2_context, /* OMAP5_OCP2SCP2 */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = EMIF */
	NULL, /* OMAP5_PHY_EMIF */
	&omap5430es1_rm_emif_emif_dll_context, /* OMAP5_DLL_EMIF */
	&omap5430es1_rm_emif_dmm_context, /* OMAP5_DMM */
	&omap5430es1_rm_emif_emif1_context, /* OMAP5_EMIF1 */
	&omap5430es1_rm_emif_emif2_context, /* OMAP5_EMIF2 */
	&omap5430es1_rm_emif_emif_fw_context, /* OMAP5_EMIF_OCP_FW */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = IPU */
	&omap5430es1_rm_ipu_ipu_context, /* OMAP5_IPU */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN2 */
	&omap5430es1_rm_l3main2_gpmc_context, /* OMAP5_GPMC */
	&omap5430es1_rm_l3main2_l3_main_2_context, /* OMAP5_L3_MAIN2_INTERCONNECT */
	&omap5430es1_rm_l3main2_ocmc_ram_context, /* OMAP5_OCMC_RAM */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_INSTR */
	&omap5430es1_rm_l3instr_l3_main_3_context, /* OMAP5_L3_MAIN3_INTERCONNECT */
	&omap5430es1_rm_l3instr_l3_instr_context, /* OMAP5_L3_INSTR_INTERCONNECT */
	&omap5430es1_rm_l3instr_ocp_wp_noc_context, /* OMAP5_OCP_WP_NOC */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN1 */
	&omap5430es1_rm_l3main1_l3_main_1_context, /* OMAP5_L3_MAIN1_INTERCONNECT */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = C2C */
	&omap5430es1_rm_c2c_c2c_context, /* OMAP5_C2C */
	&omap5430es1_rm_c2c_c2c_ocp_fw_context, /* OMAP5_C2C_OCP_FW */
	&omap5430es1_rm_c2c_modem_icr_context, /* OMAP5_MODEM_ICR */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = DMA */
	&omap5430es1_rm_dma_dma_system_context, /* OMAP5_DMA_SYSTEM */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = MIPIEXT */
	&omap5430es1_rm_mipiext_lli_context, /* OMAP5_LLI */
	&omap5430es1_rm_mipiext_lli_ocp_fw_context, /* OMAP5_LLI_OCP_FW */
	&omap5430es1_rm_mipiext_mphy_context, /* OMAP5_MPHY */
	&omap5430es1_rm_mipiext_unipro1_context, /* OMAP5_UNIPRO1 */
	/* Voltage dom.: CORE, Power dom.: DSS, Clock domain = DSS */
	&omap5430es1_rm_dss_dss_context, /* OMAP5_DSS */
	&omap5430es1_rm_dss_bb2d_context, /* OMAP5_BB2D */
	/* Voltage dom.: CORE, Power dom.: L3INIT, Clock domain = L3INIT */
	&omap5430es1_rm_l3init_hsi_context, /* OMAP5_HSI */
	&omap5430es1_rm_l3init_ieee1500_2_ocp_context, /* OMAP5_IEEE1500_2_OCP */
	&omap5430es1_rm_l3init_mmc1_context, /* OMAP5_MMC1 */
	&omap5430es1_rm_l3init_mmc2_context, /* OMAP5_MMC2 */
	&omap5430es1_rm_l3init_ocp2scp1_context, /* OMAP5_OCPSCP1 */
	&omap5430es1_rm_l3init_usb_host_hs_context, /* OMAP5_USB_HOST_HS */
	&omap5430es1_rm_l3init_usb_otg_ss_context, /* OMAP5_USB_OTG_SS */
	&omap5430es1_rm_l3init_usb_tll_hs_context, /* OMAP5_USB_TLL_HS */
	&omap5430es1_rm_l3init_sata_context, /* OMAP5_SATA */
	&omap5430es1_rm_l3init_unipro2_context, /* OMAP5_UNIPRO2 */
	NULL, /* OMAP5_MPHY_UNIPRO2 */
	&omap5430es1_rm_l3init_ocp2scp3_context, /* OMAP5_OCPSCP3 */
	/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_PER */
	&omap5430es1_rm_l4per_timer10_context, /* OMAP5_TIMER10 */
	&omap5430es1_rm_l4per_timer11_context, /* OMAP5_TIMER11 */
	&omap5430es1_rm_l4per_timer2_context, /* OMAP5_TIMER2 */
	&omap5430es1_rm_l4per_timer3_context, /* OMAP5_TIMER3 */
	&omap5430es1_rm_l4per_timer4_context, /* OMAP5_TIMER4 */
	&omap5430es1_rm_l4per_timer9_context, /* OMAP5_TIMER9 */
	&omap5430es1_rm_l4per_elm_context, /* OMAP5_ELM */
	&omap5430es1_rm_l4per_gpio2_context, /* OMAP5_GPIO2 */
	&omap5430es1_rm_l4per_gpio3_context, /* OMAP5_GPIO3 */
	&omap5430es1_rm_l4per_gpio4_context, /* OMAP5_GPIO4 */
	&omap5430es1_rm_l4per_gpio5_context, /* OMAP5_GPIO5 */
	&omap5430es1_rm_l4per_gpio6_context, /* OMAP5_GPIO6 */
	&omap5430es1_rm_l4per_gpio7_context, /* OMAP5_GPIO7 */
	&omap5430es1_rm_l4per_gpio8_context, /* OMAP5_GPIO8 */
	&omap5430es1_rm_l4per_hdq1w_context, /* OMAP5_HDQ1W */
	&omap5430es1_rm_l4per_i2c1_context, /* OMAP5_I2C1 */
	&omap5430es1_rm_l4per_i2c2_context, /* OMAP5_I2C2 */
	&omap5430es1_rm_l4per_i2c3_context, /* OMAP5_I2C3 */
	&omap5430es1_rm_l4per_i2c4_context, /* OMAP5_I2C4 */
	&omap5430es1_rm_l4per_i2c5_context, /* OMAP5_I2C5 */
	&omap5430es1_rm_l4per_l4_per_context, /* OMAP5_L4_PER_INTERCONNECT */
	&omap5430es1_rm_l4per_mcspi1_context, /* OMAP5_MCSPI1 */
	&omap5430es1_rm_l4per_mcspi2_context, /* OMAP5_MCSPI2 */
	&omap5430es1_rm_l4per_mcspi3_context, /* OMAP5_MCSPI3 */
	&omap5430es1_rm_l4per_mcspi4_context, /* OMAP5_MCSPI4 */
	&omap5430es1_rm_l4per_mmc3_context, /* OMAP5_MMC3 */
	&omap5430es1_rm_l4per_mmc4_context, /* OMAP5_MMC4 */
	&omap5430es1_rm_l4per_mmc5_context, /* OMAP5_MMC5 */
	&omap5430es1_rm_l4per_slimbus2_context, /* OMAP5_SLIMBUS2 */
	&omap5430es1_rm_l4per_uart1_context, /* OMAP5_UART1 */
	&omap5430es1_rm_l4per_uart2_context, /* OMAP5_UART2 */
	&omap5430es1_rm_l4per_uart3_context, /* OMAP5_UART3 */
	&omap5430es1_rm_l4per_uart4_context, /* OMAP5_UART4 */
	&omap5430es1_rm_l4per_uart5_context, /* OMAP5_UART5 */
	&omap5430es1_rm_l4per_uart6_context, /* OMAP5_UART6 */
	/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_SEC */
	/* HS/EMU ONLY */
	NULL, /* OMAP5_DMA_CRYPTO */
	NULL, /* OMAP5_AES1 */
	NULL, /* OMAP5_AES2 */
	NULL, /* OMAP5_SHA2MD5 */
	NULL, /* OMAP5_RNG */
	NULL, /* OMAP5_DES3DES */
	NULL, /* OMAP5_PKA */
	/* Voltage dom.: CORE, Power dom.: ABE, Clock domain = ABE */
	&omap5430es1_rm_abe_aess_context, /* OMAP5_AESS */
	&omap5430es1_rm_abe_dmic_context, /* OMAP5_DMIC */
	NULL, /* OMAP5_L4_ABE_INTERCONNECT */
	&omap5430es1_rm_abe_mcasp_context, /* OMAP5_MCASP */
	&omap5430es1_rm_abe_mcbsp1_context, /* OMAP5_MCBSP1 */
	&omap5430es1_rm_abe_mcbsp2_context, /* OMAP5_MCBSP2 */
	&omap5430es1_rm_abe_mcbsp3_context, /* OMAP5_MCBSP3 */
	&omap5430es1_rm_abe_mcpdm_context, /* OMAP5_MCPDM */
	&omap5430es1_rm_abe_slimbus1_context, /* OMAP5_SLIMBUS1 */
	&omap5430es1_rm_abe_timer5_context, /* OMAP5_TIMER5 */
	&omap5430es1_rm_abe_timer6_context, /* OMAP5_TIMER6 */
	&omap5430es1_rm_abe_timer7_context, /* OMAP5_TIMER7 */
	&omap5430es1_rm_abe_timer8_context, /* OMAP5_TIMER8 */
	&omap5430es1_rm_abe_wd_timer3_context, /* OMAP5_WD_TIMER3 */
	/* Voltage dom.: MM, Power dom.: DSP, Clock domain = DSP */
	&omap5430es1_rm_dsp_dsp_context, /* OMAP5_DSP */
	/* Voltage dom.: MM, Power dom.: GPU, Clock domain = GPU */
	&omap5430es1_rm_gpu_gpu_context, /* OMAP5_GPU */
	/* Voltage dom.: MM, Power dom.: IVA, Clock domain = IVA */
	&omap5430es1_rm_iva_iva_context, /* OMAP5_IVA */
	&omap5430es1_rm_iva_sl2_context, /* OMAP5_SL2 */
	/* Voltage dom.: MPU, Power dom.: MPUAON Clock domain = MPU */
	&omap5430es1_rm_mpu_mpu_context}; /* OMAP5_MPU */


reg *mod54xx_rm_context_reg_table[MOD54XX_ID_MAX] = {
	/* Voltage dom.: WKUP, Power dom.: EMU, Clock dom. = EMU */
	&omap5430_rm_emu_debugss_context, /* OMAP5_DEBUGSS */
	/* Voltage dom.: WKUP, Power dom.: WKUPAON, Clock domain = WKUPAON */
	NULL, /* OMAP5_CTRL_MODULE_WKUP */
	&omap5430_rm_wkupaon_l4_wkup_context, /* OMAP5_L4WKUP_INTERCONNECT */
	&omap5430_rm_wkupaon_gpio1_context, /* OMAP5_GPIO1 */
	&omap5430_rm_wkupaon_timer1_context, /* OMAP5_TIMER1 */
	&omap5430_rm_wkupaon_wd_timer2_context, /* OMAP5_WD_TIMER2 */
	&omap5430_rm_wkupaon_sar_ram_context, /* OMAP5_SARRAM */
	&omap5430_rm_wkupaon_counter_32k_context, /* OMAP5_COUNTER_32K */
	&omap5430_rm_wkupaon_kbd_context, /* OMAP5_KBD */
	NULL, /* IO_SRCOMP_WKUP */
	/* HS/EMU ONLY */
	NULL, /* OMAP5_TIMER12 */
	NULL, /* OMAP5_WDT1 */
	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = COREAON */
	&omap5430_rm_coreaon_smartreflex_core_context, /* OMAP5_SMARTREFLEX_CORE */
	&omap5430_rm_coreaon_smartreflex_mm_context, /* OMAP5_SMARTREFLEX_MM */
	&omap5430_rm_coreaon_smartreflex_mpu_context, /* OMAP5_SMARTREFLEX_MPU */
	NULL, /* OMAP5_BANDGAPTS */
	NULL, /* OMAP5_IO_SRCOMP_CORE */
	NULL, /* OMAP5_USB_PHY_CORE */
	/* Voltage dom.: CORE, Power dom.: CAM, Clock domain = CAM */
	&omap5430_rm_cam_fdif_context, /* OMAP5_FDIF */
	&omap5430_rm_cam_iss_context, /* OMAP5_ISS */
	&omap5430_rm_cam_cal_context, /* OMAP5_CAL */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L4CFG */
	NULL, /* OMAP5_CTRL_MODULE_CORE */
	&omap5430_rm_l4cfg_spinlock_context, /* OMAP5_SPINLOCK */
	&omap5430_rm_l4cfg_l4_cfg_context, /* OMAP5_L4_CFG_INTERCONNECT */
	&omap5430_rm_l4cfg_mailbox_context, /* OMAP5_MAILBOX */
	&omap5430_rm_l4cfg_sar_rom_context, /* OMAP5_SARROM */
	&omap5430_rm_l4cfg_ocp2scp2_context, /* OMAP5_OCP2SCP2 */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = EMIF */
	NULL, /* OMAP5_PHY_EMIF */
	&omap5430_rm_emif_emif_dll_context, /* OMAP5_DLL_EMIF */
	&omap5430_rm_emif_dmm_context, /* OMAP5_DMM */
	&omap5430_rm_emif_emif1_context, /* OMAP5_EMIF1 */
	&omap5430_rm_emif_emif2_context, /* OMAP5_EMIF2 */
	&omap5430_rm_emif_emif_fw_context, /* OMAP5_EMIF_OCP_FW */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = IPU */
	&omap5430_rm_ipu_ipu_context, /* OMAP5_IPU */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN2 */
	&omap5430_rm_l3main2_gpmc_context, /* OMAP5_GPMC */
	&omap5430_rm_l3main2_l3_main_2_context, /* OMAP5_L3_MAIN2_INTERCONNECT */
	&omap5430_rm_l3main2_ocmc_ram_context, /* OMAP5_OCMC_RAM */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_INSTR */
	&omap5430_rm_l3instr_l3_main_3_context, /* OMAP5_L3_MAIN3_INTERCONNECT */
	&omap5430_rm_l3instr_l3_instr_context, /* OMAP5_L3_INSTR_INTERCONNECT */
	&omap5430_rm_l3instr_ocp_wp_noc_context, /* OMAP5_OCP_WP_NOC */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN1 */
	&omap5430_rm_l3main1_l3_main_1_context, /* OMAP5_L3_MAIN1_INTERCONNECT */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = C2C */
	&omap5430_rm_c2c_c2c_context, /* OMAP5_C2C */
	&omap5430_rm_c2c_c2c_ocp_fw_context, /* OMAP5_C2C_OCP_FW */
	&omap5430_rm_c2c_modem_icr_context, /* OMAP5_MODEM_ICR */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = DMA */
	&omap5430_rm_dma_dma_system_context, /* OMAP5_DMA_SYSTEM */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = MIPIEXT */
	&omap5430_rm_mipiext_lli_context, /* OMAP5_LLI */
	&omap5430_rm_mipiext_lli_ocp_fw_context, /* OMAP5_LLI_OCP_FW */
	&omap5430_rm_mipiext_mphy_context, /* OMAP5_MPHY */
	NULL, /* OMAP5_UNIPRO1 */
	/* Voltage dom.: CORE, Power dom.: DSS, Clock domain = DSS */
	&omap5430_rm_dss_dss_context, /* OMAP5_DSS */
	&omap5430_rm_dss_bb2d_context, /* OMAP5_BB2D */
	/* Voltage dom.: CORE, Power dom.: L3INIT, Clock domain = L3INIT */
	&omap5430_rm_l3init_hsi_context, /* OMAP5_HSI */
	&omap5430_rm_l3init_ieee1500_2_ocp_context, /* OMAP5_IEEE1500_2_OCP */
	&omap5430_rm_l3init_mmc1_context, /* OMAP5_MMC1 */
	&omap5430_rm_l3init_mmc2_context, /* OMAP5_MMC2 */
	&omap5430_rm_l3init_ocp2scp1_context, /* OMAP5_OCPSCP1 */
	&omap5430_rm_l3init_usb_host_hs_context, /* OMAP5_USB_HOST_HS */
	&omap5430_rm_l3init_usb_otg_ss_context, /* OMAP5_USB_OTG_SS */
	&omap5430_rm_l3init_usb_tll_hs_context, /* OMAP5_USB_TLL_HS */
	&omap5430_rm_l3init_sata_context, /* OMAP5_SATA */
	&omap5430_rm_l3init_unipro2_context, /* OMAP5_UNIPRO2 */
	NULL, /* OMAP5_MPHY_UNIPRO2 */
	&omap5430_rm_l3init_ocp2scp3_context, /* OMAP5_OCPSCP3 */
	/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_PER */
	&omap5430_rm_l4per_timer10_context, /* OMAP5_TIMER10 */
	&omap5430_rm_l4per_timer11_context, /* OMAP5_TIMER11 */
	&omap5430_rm_l4per_timer2_context, /* OMAP5_TIMER2 */
	&omap5430_rm_l4per_timer3_context, /* OMAP5_TIMER3 */
	&omap5430_rm_l4per_timer4_context, /* OMAP5_TIMER4 */
	&omap5430_rm_l4per_timer9_context, /* OMAP5_TIMER9 */
	&omap5430_rm_l4per_elm_context, /* OMAP5_ELM */
	&omap5430_rm_l4per_gpio2_context, /* OMAP5_GPIO2 */
	&omap5430_rm_l4per_gpio3_context, /* OMAP5_GPIO3 */
	&omap5430_rm_l4per_gpio4_context, /* OMAP5_GPIO4 */
	&omap5430_rm_l4per_gpio5_context, /* OMAP5_GPIO5 */
	&omap5430_rm_l4per_gpio6_context, /* OMAP5_GPIO6 */
	&omap5430_rm_l4per_gpio7_context, /* OMAP5_GPIO7 */
	&omap5430_rm_l4per_gpio8_context, /* OMAP5_GPIO8 */
	&omap5430_rm_l4per_hdq1w_context, /* OMAP5_HDQ1W */
	&omap5430_rm_l4per_i2c1_context, /* OMAP5_I2C1 */
	&omap5430_rm_l4per_i2c2_context, /* OMAP5_I2C2 */
	&omap5430_rm_l4per_i2c3_context, /* OMAP5_I2C3 */
	&omap5430_rm_l4per_i2c4_context, /* OMAP5_I2C4 */
	&omap5430_rm_l4per_i2c5_context, /* OMAP5_I2C5 */
	&omap5430_rm_l4per_l4_per_context, /* OMAP5_L4_PER_INTERCONNECT */
	&omap5430_rm_l4per_mcspi1_context, /* OMAP5_MCSPI1 */
	&omap5430_rm_l4per_mcspi2_context, /* OMAP5_MCSPI2 */
	&omap5430_rm_l4per_mcspi3_context, /* OMAP5_MCSPI3 */
	&omap5430_rm_l4per_mcspi4_context, /* OMAP5_MCSPI4 */
	&omap5430_rm_l4per_mmc3_context, /* OMAP5_MMC3 */
	&omap5430_rm_l4per_mmc4_context, /* OMAP5_MMC4 */
	&omap5430_rm_l4per_mmc5_context, /* OMAP5_MMC5 */
	NULL, /* OMAP5_SLIMBUS2 */
	&omap5430_rm_l4per_uart1_context, /* OMAP5_UART1 */
	&omap5430_rm_l4per_uart2_context, /* OMAP5_UART2 */
	&omap5430_rm_l4per_uart3_context, /* OMAP5_UART3 */
	&omap5430_rm_l4per_uart4_context, /* OMAP5_UART4 */
	&omap5430_rm_l4per_uart5_context, /* OMAP5_UART5 */
	&omap5430_rm_l4per_uart6_context, /* OMAP5_UART6 */
	/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_SEC */
	/* HS/EMU ONLY */
	NULL, /* OMAP5_DMA_CRYPTO */
	NULL, /* OMAP5_AES1 */
	NULL, /* OMAP5_AES2 */
	NULL, /* OMAP5_SHA2MD5 */
	NULL, /* OMAP5_RNG */
	NULL, /* OMAP5_DES3DES */
	NULL, /* OMAP5_PKA */
	/* Voltage dom.: CORE, Power dom.: ABE, Clock domain = ABE */
	&omap5430_rm_abe_aess_context, /* OMAP5_AESS */
	&omap5430_rm_abe_dmic_context, /* OMAP5_DMIC */
	NULL, /* OMAP5_L4_ABE_INTERCONNECT */
	&omap5430_rm_abe_mcasp_context, /* OMAP5_MCASP */
	&omap5430_rm_abe_mcbsp1_context, /* OMAP5_MCBSP1 */
	&omap5430_rm_abe_mcbsp2_context, /* OMAP5_MCBSP2 */
	&omap5430_rm_abe_mcbsp3_context, /* OMAP5_MCBSP3 */
	&omap5430_rm_abe_mcpdm_context, /* OMAP5_MCPDM */
	&omap5430_rm_abe_slimbus1_context, /* OMAP5_SLIMBUS1 */
	&omap5430_rm_abe_timer5_context, /* OMAP5_TIMER5 */
	&omap5430_rm_abe_timer6_context, /* OMAP5_TIMER6 */
	&omap5430_rm_abe_timer7_context, /* OMAP5_TIMER7 */
	&omap5430_rm_abe_timer8_context, /* OMAP5_TIMER8 */
	&omap5430_rm_abe_wd_timer3_context, /* OMAP5_WD_TIMER3 */
	/* Voltage dom.: MM, Power dom.: DSP, Clock domain = DSP */
	&omap5430_rm_dsp_dsp_context, /* OMAP5_DSP */
	/* Voltage dom.: MM, Power dom.: GPU, Clock domain = GPU */
	&omap5430_rm_gpu_gpu_context, /* OMAP5_GPU */
	/* Voltage dom.: MM, Power dom.: IVA, Clock domain = IVA */
	&omap5430_rm_iva_iva_context, /* OMAP5_IVA */
	&omap5430_rm_iva_sl2_context, /* OMAP5_SL2 */
	/* Voltage dom.: MPU, Power dom.: MPUAON Clock domain = MPU */
	&omap5430_rm_mpu_mpu_context}; /* OMAP5_MPU */


const double mod54xx_por_rates_table[MOD54XX_ID_MAX][OPP_MAX] = {
	/* Voltage dom.: WKUP, Power dom.: EMU, Clock dom. = EMU */
	{-1.0, -1.0, 19.2, -1.0, -1.0, -1.0}, /* OMAP5_DEBUGSS */
	/* Voltage dom.: WKUP, Power dom.: WKUPAON, Clock domain = WKUPAON */
	{-1.0, -1.0, 19.2, -1.0, -1.0, -1.0}, /* OMAP5_CTRL_MODULE_WKUP */
	{-1.0, -1.0, 19.2, -1.0, -1.0, -1.0}, /* OMAP5_L4WKUP_INTERCONNECT */
	{-1.0, -1.0, 0.032768, -1.0, -1.0, -1.0}, /* OMAP5_GPIO1 */
	{-1.0, -1.0, 0.032768, -1.0, -1.0, -1.0}, /* OMAP5_TIMER1 */
	{-1.0, -1.0, 0.032768, -1.0, -1.0, -1.0}, /* OMAP5_WD_TIMER2 */
	{-1.0, -1.0, 19.2, -1.0, -1.0, -1.0}, /* OMAP5_SARRAM */
	{-1.0, -1.0, 0.032768, -1.0, -1.0, -1.0}, /* OMAP5_COUNTER_32K */
	{-1.0, -1.0, 0.032768, -1.0, -1.0, -1.0}, /* OMAP5_KBD */
	{-1.0, -1.0, 19.2, -1.0, -1.0, -1.0}, /* IO_SRCOMP_WKUP */
	/* HS/EMU ONLY */
	{-1.0, -1.0, 0.032768, -1.0, -1.0, -1.0}, /* OMAP5_TIMER12 */
	{-1.0, -1.0, 0.032768, -1.0, -1.0, -1.0}, /* OMAP5_WDT1 */
	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = COREAON */
	{-1.0, -1.0, 19.2, -1.0, -1.0, -1.0}, /* OMAP5_SMARTREFLEX_CORE */
	{-1.0, -1.0, 19.2, -1.0, -1.0, -1.0}, /* OMAP5_SMARTREFLEX_MM */
	{-1.0, -1.0, 19.2, -1.0, -1.0, -1.0}, /* OMAP5_SMARTREFLEX_MPU */
	{-1.0, -1.0, 1.2, -1.0, -1.0, -1.0}, /* OMAP5_BANDGAPTS */
	{-1.0, -1.0, 19.2, -1.0, -1.0, -1.0}, /* OMAP5_IO_SRCOMP_CORE */
	{-1.0, -1.0, 0.032768, -1.0, -1.0, -1.0}, /* OMAP5_USB_PHY_CORE */
	/* Voltage dom.: CORE, Power dom.: CAM, Clock domain = CAM */
	{-1.0, 128.0, 128.0, -1.0, -1.0, -1.0}, /* OMAP5_FDIF */
	{-1.0, 152.0, 304.0, -1.0, -1.0, -1.0}, /* OMAP5_ISS */
	{-1.0, 133.0, 266.0, -1.0, -1.0, -1.0}, /* OMAP5_CAL */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L4CFG */
	{-1.0, 66.5, 133.0, -1.0, -1.0, -1.0}, /* OMAP5_CTRL_MODULE_CORE */
	{-1.0, 66.5, 133.0, -1.0, -1.0, -1.0}, /* OMAP5_SPINLOCK */
	{-1.0, 66.5, 133.0, -1.0, -1.0, -1.0}, /* OMAP5_L4_CFG_INTERCONNECT */
	{-1.0, 66.5, 133.0, -1.0, -1.0, -1.0}, /* OMAP5_MAILBOX */
	{-1.0, 66.5, 133.0, -1.0, -1.0, -1.0}, /* OMAP5_SARROM */
	{-1.0, 66.5, 133.0, -1.0, -1.0, -1.0}, /* OMAP5_OCP2SCP2 */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = EMIF */
	{-1.0, 266.0, 532.0, -1.0, -1.0, -1.0}, /* OMAP5_PHY_EMIF */
	{-1.0, 266.0, 266.0, -1.0, -1.0, -1.0}, /* OMAP5_DLL_EMIF */
	{-1.0, 133.0, 266.0, -1.0, -1.0, -1.0}, /* OMAP5_DMM */
	{-1.0, 133.0, 266.0, -1.0, -1.0, -1.0}, /* OMAP5_EMIF1 */
	{-1.0, 133.0, 266.0, -1.0, -1.0, -1.0}, /* OMAP5_EMIF2 */
	{-1.0, 133.0, 266.0, -1.0, -1.0, -1.0}, /* OMAP5_EMIF_OCP_FW */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = IPU */
	{-1.0, 212.8, 425.6, -1.0, -1.0, -1.0}, /* OMAP5_IPU */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN2 */
	{-1.0, 133.0, 266.0, -1.0, -1.0, -1.0}, /* OMAP5_GPMC */
	{-1.0, 133.0, 266.0, -1.0, -1.0, -1.0}, /* OMAP5_L3_MAIN2_INTERCONNECT */
	{-1.0, 133.0, 266.0, -1.0, -1.0, -1.0}, /* OMAP5_OCMC_RAM */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_INSTR */
	{-1.0, 133.0, 266.0, -1.0, -1.0, -1.0}, /* OMAP5_L3_MAIN3_INTERCONNECT */
	{-1.0, 133.0, 266.0, -1.0, -1.0, -1.0}, /* OMAP5_L3_INSTR_INTERCONNECT */
	{-1.0, 133.0, 266.0, -1.0, -1.0, -1.0}, /* OMAP5_OCP_WP_NOC */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN1 */
	{98.304, 133.0, 266.0, -1.0, -1.0, -1.0}, /* OMAP5_L3_MAIN1_INTERCONNECT */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = C2C */
	{-1.0, 133.0, 266.0, -1.0, -1.0, -1.0}, /* OMAP5_C2C */
	{-1.0, 133.0, 266.0, -1.0, -1.0, -1.0}, /* OMAP5_C2C_OCP_FW */
	{-1.0, 66.5, 133.0, -1.0, -1.0, -1.0}, /* OMAP5_MODEM_ICR */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = DMA */
	{-1.0, 133.0, 266.0, -1.0, -1.0, -1.0}, /* OMAP5_DMA_SYSTEM */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = MIPIEXT */
	{-1.0, 1457.6, 1457.6, -1.0, -1.0, -1.0}, /* OMAP5_LLI */
	{-1.0, 133.0, 266.0, -1.0, -1.0, -1.0}, /* OMAP5_LLI_OCP_FW */
	{-1.0, 66.5, 133.0, -1.0, -1.0, -1.0}, /* OMAP5_MPHY */
	{-1.0, 1457.6, 1457.6, -1.0, -1.0, -1.0}, /* OMAP5_UNIPRO1 */
	/* Voltage dom.: CORE, Power dom.: DSS, Clock domain = DSS */
	{-1.0, 192.0, 192.0, -1.0, -1.0, -1.0}, /* OMAP5_DSS */
	{-1.0, 133.0, 266.0, -1.0, -1.0, -1.0}, /* OMAP5_BB2D */
	/* Voltage dom.: CORE, Power dom.: L3INIT, Clock domain = L3INIT */
	{-1.0, 192.0, 192.0, -1.0, -1.0, -1.0}, /* OMAP5_HSI */
	{-1.0, 133.0, 266.0, -1.0, -1.0, -1.0}, /* OMAP5_IEEE1500_2_OCP */
	{-1.0, 96.0, 96.0, -1.0, -1.0, -1.0}, /* OMAP5_MMC1 */
	{-1.0, 96.0, 96.0, -1.0, -1.0, -1.0}, /* OMAP5_MMC2 */
	{-1.0, 66.5, 133.0, -1.0, -1.0, -1.0}, /* OMAP5_OCPSCP1 */
	{-1.0, 60.0, 60.0, -1.0, -1.0, -1.0}, /* OMAP5_USB_HOST_HS */
	{-1.0, 960.0, 960.0, -1.0, -1.0, -1.0}, /* OMAP5_USB_OTG_SS */
	{-1.0, 60.0, 60.0, -1.0, -1.0, -1.0}, /* OMAP5_USB_TLL_HS */
	{-1.0, 133.0, 266.0, -1.0, -1.0, -1.0}, /* OMAP5_SATA */
	{-1.0, 1457.6, 1457.6, -1.0, -1.0, -1.0}, /* OMAP5_UNIPRO2 */
	{-1.0, 66.5, 133.0, -1.0, -1.0, -1.0}, /* OMAP5_MPHY_UNIPRO2 */
	{-1.0, 66.5, 133.0, -1.0, -1.0, -1.0}, /* OMAP5_OCPSCP3 */
	/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_PER */
	{-1.0, 19.2, 19.2, -1.0, -1.0, -1.0}, /* OMAP5_TIMER10 */
	{-1.0, 19.2, 19.2, -1.0, -1.0, -1.0}, /* OMAP5_TIMER11 */
	{-1.0, 19.2, 19.2, -1.0, -1.0, -1.0}, /* OMAP5_TIMER2 */
	{-1.0, 19.2, 19.2, -1.0, -1.0, -1.0}, /* OMAP5_TIMER3 */
	{-1.0, 19.2, 19.2, -1.0, -1.0, -1.0}, /* OMAP5_TIMER4 */
	{-1.0, 19.2, 19.2, -1.0, -1.0, -1.0}, /* OMAP5_TIMER9 */
	{-1.0, 66.5, 133.0, -1.0, -1.0, -1.0}, /* OMAP5_ELM */
	{-1.0, 0.032768, 0.032768, -1.0, -1.0, -1.0}, /* OMAP5_GPIO2 */
	{-1.0, 0.032768, 0.032768, -1.0, -1.0, -1.0}, /* OMAP5_GPIO3 */
	{-1.0, 0.032768, 0.032768, -1.0, -1.0, -1.0}, /* OMAP5_GPIO4 */
	{-1.0, 0.032768, 0.032768, -1.0, -1.0, -1.0}, /* OMAP5_GPIO5 */
	{-1.0, 0.032768, 0.032768, -1.0, -1.0, -1.0}, /* OMAP5_GPIO6 */
	{-1.0, 0.032768, 0.032768, -1.0, -1.0, -1.0}, /* OMAP5_GPIO7 */
	{-1.0, 0.032768, 0.032768, -1.0, -1.0, -1.0}, /* OMAP5_GPIO8 */
	{-1.0, 12.0, 12.0, -1.0, -1.0, -1.0}, /* OMAP5_HDQ1W */
	{-1.0, 96.0, 96.0, -1.0, -1.0, -1.0}, /* OMAP5_I2C1 */
	{-1.0, 96.0, 96.0, -1.0, -1.0, -1.0}, /* OMAP5_I2C2 */
	{-1.0, 96.0, 96.0, -1.0, -1.0, -1.0}, /* OMAP5_I2C3 */
	{-1.0, 96.0, 96.0, -1.0, -1.0, -1.0}, /* OMAP5_I2C4 */
	{-1.0, 96.0, 96.0, -1.0, -1.0, -1.0}, /* OMAP5_I2C5 */
	{-1.0, 66.5, 133.0, -1.0, -1.0, -1.0}, /* OMAP5_L4_PER_INTERCONNECT */
	{-1.0, 48.0, 48.0, -1.0, -1.0, -1.0}, /* OMAP5_MCSPI1 */
	{-1.0, 48.0, 48.0, -1.0, -1.0, -1.0}, /* OMAP5_MCSPI2 */
	{-1.0, 48.0, 48.0, -1.0, -1.0, -1.0}, /* OMAP5_MCSPI3 */
	{-1.0, 48.0, 48.0, -1.0, -1.0, -1.0}, /* OMAP5_MCSPI4 */
	{-1.0, 48.0, 48.0, -1.0, -1.0, -1.0}, /* OMAP5_MMC3 */
	{-1.0, 48.0, 48.0, -1.0, -1.0, -1.0}, /* OMAP5_MMC4 */
	{-1.0, 96.0, 96.0, -1.0, -1.0, -1.0}, /* OMAP5_MMC5 */
	{-1.0, 24.576, 24.576, -1.0, -1.0, -1.0}, /* OMAP5_SLIMBUS2 */
	{-1.0, 48.0, 48.0, -1.0, -1.0, -1.0}, /* OMAP5_UART1 */
	{-1.0, 48.0, 48.0, -1.0, -1.0, -1.0}, /* OMAP5_UART2 */
	{-1.0, 48.0, 48.0, -1.0, -1.0, -1.0}, /* OMAP5_UART3 */
	{-1.0, 48.0, 48.0, -1.0, -1.0, -1.0}, /* OMAP5_UART4 */
	{-1.0, 48.0, 48.0, -1.0, -1.0, -1.0}, /* OMAP5_UART5 */
	{-1.0, 48.0, 48.0, -1.0, -1.0, -1.0}, /* OMAP5_UART6 */
	/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_SEC */
	/* HS/EMU ONLY */
	{-1.0, 133.0, 266.0, -1.0, -1.0, -1.0}, /* OMAP5_DMA_CRYPTO */
	{-1.0, 133.0, 266.0, -1.0, -1.0, -1.0}, /* OMAP5_AES1 */
	{-1.0, 133.0, 266.0, -1.0, -1.0, -1.0}, /* OMAP5_AES2 */
	{-1.0, 133.0, 266.0, -1.0, -1.0, -1.0}, /* OMAP5_SHA2MD5 */
	{-1.0, 66.5, 133.0, -1.0, -1.0, -1.0}, /* OMAP5_RNG */
	{-1.0, 66.5, 133.0, -1.0, -1.0, -1.0}, /* OMAP5_DES3DES */
	{-1.0, 66.5, 133.0, -1.0, -1.0, -1.0}, /* OMAP5_PKA */
	/* Voltage dom.: CORE, Power dom.: ABE, Clock domain = ABE */
	{98.304, 98.304, 196.608, -1.0, -1.0, -1.0}, /* OMAP5_AESS */
	{24.576, 24.576, 24.576, -1.0, -1.0, -1.0}, /* OMAP5_DMIC */
	{49.152, 49.152, 98.304, -1.0, -1.0, -1.0}, /* OMAP5_L4_ABE_INTERCONNECT */
	{24.576, 98.0, 98.0, -1.0, -1.0, -1.0}, /* OMAP5_MCASP */
	{24.576, 96.0, 96.0, -1.0, -1.0, -1.0}, /* OMAP5_MCBSP1 */
	{24.576, 96.0, 96.0, -1.0, -1.0, -1.0}, /* OMAP5_MCBSP2 */
	{24.576, 96.0, 96.0, -1.0, -1.0, -1.0}, /* OMAP5_MCBSP3 */
	{19.2, 19.2, 19.2, -1.0, -1.0, -1.0}, /* OMAP5_MCPDM */
	{24.576, 24.576, 24.576, -1.0, -1.0, -1.0}, /* OMAP5_SLIMBUS1 */
	{-1.0, 19.2, 19.2, -1.0, -1.0, -1.0}, /* OMAP5_TIMER5 */
	{-1.0, 19.2, 19.2, -1.0, -1.0, -1.0}, /* OMAP5_TIMER6 */
	{-1.0, 19.2, 19.2, -1.0, -1.0, -1.0}, /* OMAP5_TIMER7 */
	{-1.0, 19.2, 19.2, -1.0, -1.0, -1.0}, /* OMAP5_TIMER8 */
	{0.032768, 0.032768, 0.032768, -1.0, -1.0, -1.0}, /* OMAP5_WD_TIMER3 */
	/* Voltage dom.: MM, Power dom.: DSP, Clock domain = DSP */
	{98.304, 232.960, 465.919, 532.0, -1.0, -1.0}, /* OMAP5_DSP */
	/* Voltage dom.: MM, Power dom.: GPU, Clock domain = GPU */
	{98.304, 177.333, 354.666, 532.0, -1.0, -1.0}, /* OMAP5_GPU */
	/* Voltage dom.: MM, Power dom.: IVA, Clock domain = IVA */
	{98.304, 194.133, 388.266, 532.0, -1.0, -1.0}, /* OMAP5_IVA */
	{98.304, 194.133, 388.266, 532.0, -1.0, -1.0}, /* OMAP5_SL2 */
	/* Voltage dom.: MPU, Power dom.: MPUAON Clock domain = MPU */
	{196.608, 400.0, 800.0, 1100.0, 1200.0, -1.0} }; /* OMAP5_MPU */


const unsigned int mod54xx_properties_table[MOD54XX_ID_MAX] = {
	/* Voltage dom.: WKUP, Power dom.: EMU, Clock dom. = EMU */
	MOD_HAS_STANDBY_STATUS, /* OMAP5_DEBUGSS */
	/* Voltage dom.: WKUP, Power dom.: WKUPAON, Clock domain = WKUPAON */
	0, /* OMAP5_CTRL_MODULE_WKUP */
	0, /* OMAP5_L4WKUP_INTERCONNECT */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_ENAWAKEUP_BIT, /* OMAP5_GPIO1 */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE, /* OMAP5_TIMER1 */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE, /* OMAP5_WD_TIMER2 */
	0, /* OMAP5_SARRAM */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE4, /* OMAP5_COUNTER_32K */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE4, /* OMAP5_KBD */
	MOD_HAS_NO_IDLE_STATUS, /* IO_SRCOMP_WKUP */
	/* HS/EMU ONLY */
	0, /* OMAP5_TIMER12 */
	0, /* OMAP5_WDT1 */
	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = COREAON */
	0, /* OMAP5_SMARTREFLEX_CORE */
	0, /* OMAP5_SMARTREFLEX_MM */
	0, /* OMAP5_SMARTREFLEX_MPU */
	MOD_HAS_NO_IDLE_STATUS, /* OMAP5_BANDGAPTS */
	MOD_HAS_NO_IDLE_STATUS, /* OMAP5_IO_SRCOMP_CORE */
	MOD_HAS_NO_IDLE_STATUS, /* OMAP5_USB_PHY_CORE */
	/* Voltage dom.: CORE, Power dom.: CAM, Clock domain = CAM */
	MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_STANDBY_MODE5, /* OMAP5_FDIF */
	MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE, /* OMAP5_ISS */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE, /* OMAP5_CAL */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L4CFG */
	0, /* OMAP5_CTRL_MODULE_CORE */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_IDLE_MODE4 | MOD_HAS_CLOCK_ACTIVITY_MODE, /* OMAP5_SPINLOCK */
	0, /* OMAP5_L4_CFG_INTERCONNECT */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3, /* OMAP5_MAILBOX */
	0, /* OMAP5_SARROM */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4, /* OMAP5_OCP2SCP2 */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = EMIF */
	0, /* OMAP5_PHY_EMIF */
	0, /* OMAP5_DLL_EMIF */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3, /* OMAP5_DMM */
	0, /* OMAP5_EMIF1 */
	0, /* OMAP5_EMIF2 */
	0, /* OMAP5_EMIF_OCP_FW */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = IPU */
	MOD_HAS_STANDBY_STATUS, /* OMAP5_IPU */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN2 */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4, /* OMAP5_GPMC */
	0, /* OMAP5_L3_MAIN2_INTERCONNECT */
	0, /* OMAP5_OCMC_RAM */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_INSTR */
	0, /* OMAP5_L3_MAIN3_INTERCONNECT */
	0, /* OMAP5_L3_INSTR_INTERCONNECT */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0, /* OMAP5_OCP_WP_NOC */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN1 */
	0, /* OMAP5_L3_MAIN1_INTERCONNECT */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = C2C */
	MOD_HAS_STANDBY_STATUS, /* OMAP5_C2C */
	0, /* OMAP5_C2C_OCP_FW */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4, /* OMAP5_MODEM_ICR */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = DMA */
	MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_STANDBY_MODE13 | MOD_HAS_CLOCK_ACTIVITY_MODE, /* OMAP5_DMA_SYSTEM */
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = MIPIEXT */
	MOD_HAS_STANDBY_STATUS, /* OMAP5_LLI */
	0, /* OMAP5_LLI_OCP_FW */
	0, /* OMAP5_MPHY */
	MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE, /* OMAP5_UNIPRO1 */
	/* Voltage dom.: CORE, Power dom.: DSS, Clock domain = DSS */
	MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_IDLE_MODE4 | MOD_HAS_CLOCK_ACTIVITY_MODE | MOD_HAS_STANDBY_MODE13, /* OMAP5_DSS */
	MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE, /* OMAP5_BB2D */
	/* Voltage dom.: CORE, Power dom.: L3INIT, Clock domain = L3INIT */
	MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE13 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE, /* OMAP5_HSI */
	MOD_HAS_STANDBY_STATUS, /* OMAP5_IEEE1500_2_OCP */
	MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE, /* OMAP5_MMC1 */
	MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE, /* OMAP5_MMC2 */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4, /* OMAP5_OCPSCP1 */
	MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE, /* OMAP5_USB_HOST_HS */
	MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE, /* OMAP5_USB_OTG_SS */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_IDLE_MODE4, /* OMAP5_USB_TLL_HS */
	MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE, /* OMAP5_SATA */
	MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE, /* OMAP5_UNIPRO2 */
	0, /* OMAP5_MPHY_UNIPRO2 */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4, /* OMAP5_OCPSCP3 */
	/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_PER */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE, /* OMAP5_TIMER10 */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE, /* OMAP5_TIMER11 */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE, /* OMAP5_TIMER2 */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE, /* OMAP5_TIMER3 */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE, /* OMAP5_TIMER4 */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE, /* OMAP5_TIMER9 */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_CLOCK_ACTIVITY_MODE, /* OMAP5_ELM */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_ENAWAKEUP_BIT, /* OMAP5_GPIO2 */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_ENAWAKEUP_BIT, /* OMAP5_GPIO3 */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_ENAWAKEUP_BIT, /* OMAP5_GPIO4 */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_ENAWAKEUP_BIT, /* OMAP5_GPIO5 */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_ENAWAKEUP_BIT, /* OMAP5_GPIO6 */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_ENAWAKEUP_BIT, /* OMAP5_GPIO7 */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_ENAWAKEUP_BIT, /* OMAP5_GPIO8 */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0, /* OMAP5_HDQ1W */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE, /* OMAP5_I2C1 */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE, /* OMAP5_I2C2 */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE, /* OMAP5_I2C3 */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE, /* OMAP5_I2C4 */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE, /* OMAP5_I2C5 */
	0, /* OMAP5_L4_PER_INTERCONNECT */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE, /* OMAP5_MCSPI1 */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE, /* OMAP5_MCSPI2 */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE, /* OMAP5_MCSPI3 */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE, /* OMAP5_MCSPI4 */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE, /* OMAP5_MMC3 */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE, /* OMAP5_MMC4 */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE, /* OMAP5_MMC5 */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT8 | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE, /* OMAP5_SLIMBUS2 */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE, /* OMAP5_UART1 */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE, /* OMAP5_UART2 */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE, /* OMAP5_UART3 */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE, /* OMAP5_UART4 */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE, /* OMAP5_UART5 */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE, /* OMAP5_UART6 */
	/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_SEC */
	/* HS/EMU ONLY */
	0, /* OMAP5_DMA_CRYPTO */
	0, /* OMAP5_AES1 */
	0, /* OMAP5_AES2 */
	0, /* OMAP5_SHA2MD5 */
	0, /* OMAP5_RNG */
	0, /* OMAP5_DES3DES */
	0, /* OMAP5_PKA */
	/* Voltage dom.: CORE, Power dom.: ABE, Clock domain = ABE */
	MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE, /* OMAP5_AESS */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE, /* OMAP5_DMIC */
	0, /* OMAP5_L4_ABE_INTERCONNECT */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE1, /* OMAP5_MCASP */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_CLOCK_ACTIVITY_MODE, /* OMAP5_MCBSP1 */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_CLOCK_ACTIVITY_MODE, /* OMAP5_MCBSP2 */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_CLOCK_ACTIVITY_MODE, /* OMAP5_MCBSP3 */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE, /* OMAP5_MCPDM */
	MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT8 | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE, /* OMAP5_SLIMBUS1 */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE, /* OMAP5_TIMER5 */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE, /* OMAP5_TIMER6 */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE, /* OMAP5_TIMER7 */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE, /* OMAP5_TIMER8 */
	MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE, /* OMAP5_WD_TIMER3 */
	/* Voltage dom.: MM, Power dom.: DSP, Clock domain = DSP */
	MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0, /* OMAP5_DSP */
	/* Voltage dom.: MM, Power dom.: GPU, Clock domain = GPU */
	MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_STANDBY_MODE5, /* OMAP5_GPU */
	/* Voltage dom.: MM, Power dom.: IVA, Clock domain = IVA */
	MOD_HAS_STANDBY_STATUS, /* OMAP5_IVA */
	0, /* OMAP5_SL2 */
	/* Voltage dom.: MPU, Power dom.: MPUAON Clock domain = MPU */
	MOD_HAS_STANDBY_STATUS}; /* OMAP5_MPU */
