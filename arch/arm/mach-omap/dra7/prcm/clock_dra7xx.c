/*
 *
 * @Component			OMAPCONF
 * @Filename			clock_dra7xx.c
 * @Description			DRA7 PRCM Clocks Definitions & Functions
 * @Author			Jin Zheng (j-zheng@ti.com)
 * @Date			2013
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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


#include <clock_dra7xx.h>
#include <string.h>
#include <cpuinfo.h>
#include <lib.h>
#include <mem.h>
#include <cm_dra7xx.h>
#include <prm_dra7xx.h>
#include <dpll_dra7xx.h>
#include <stdlib.h>


/* #define CLOCK_DRA7XX_DEBUG */
#ifdef CLOCK_DRA7XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


#define DRA7XX_SYS_32K_SPEED		0.032768

/*
 * XXX: This value needs to match the exact crystal frequency used
 *      on the board. Current value is for TI DRA7 EVM.
 */
#define DRA7XX_SYS_CLKIN2_SPEED		22.5792


static const char
	clk_dra7xx_name_table[CLK_DRA7XX_ID_MAX + 1][CLK_DRA7XX_MAX_NAME_LENGTH] = {
	/* 32K CLKS */
	[CLK_DRA7XX_SYS_32K] = "SYS_32K",
	[CLK_DRA7XX_FUNC_32K_CLK] = "FUNC_32K_CLK",
	[CLK_DRA7XX_SECURE_32K_CLK] = "SECURE_32K_CLK",
	[CLK_DRA7XX_HDMI_CEC_GFCLK] = "HDMI_CEC_GFCLK",
	[CLK_DRA7XX_WKUPAON_32K_GFCLK] = "WKUPAON_32K_GFCLK",
	[CLK_DRA7XX_COREAON_32K_GFCLK] = "COREAON_32K_GFCLK",
	[CLK_DRA7XX_PER_32K_GFCLK] = "PER_32K_GFCLK",
	[CLK_DRA7XX_ABE_32K_CLK] = "ABE_32K_CLK",
	[CLK_DRA7XX_MMC1_32K_GFCLK] = "MMC1_32K_GFCLK",
	/* SYS CLKS */
	[CLK_DRA7XX_SYS_CLKIN1] = "SYS_CLKIN1",
	[CLK_DRA7XX_SYS_CLKIN2] = "SYS_CLKIN2",
	[CLK_DRA7XX_ABE_DPLL_SYS_CLK] = "ABE_DPLL_SYS_CLK",
	[CLK_DRA7XX_CUSTEFUSE_SYS_GFCLK] = "CUSTEFUSE_SYS_GFCLK",
	[CLK_DRA7XX_EMU_SYS_CLK] = "EMU_SYS_CLK",
	[CLK_DRA7XX_MPU_DPLL_CLK] = "MPU_DPLL_CLK",
	[CLK_DRA7XX_IVA_DPLL_CLK] = "IVA_DPLL_CLK",
	[CLK_DRA7XX_CORE_DPLL_CLK] = "CORE_DPLL_CLK",
	[CLK_DRA7XX_PER_DPLL_CLK] = "PER_DPLL_CLK",
	[CLK_DRA7XX_EVE_DPLL_CLK] = "EVE_DPLL_CLK",
	[CLK_DRA7XX_DSP_DPLL_CLK] = "DSP_DPLL_CLK",
	[CLK_DRA7XX_GMAC_DPLL_CLK] = "GMAC_DPLL_CLK",
	[CLK_DRA7XX_GPU_DPLL_CLK] = "GPU_DPLL_CLK",
	[CLK_DRA7XX_DDR_DPLL_CLK] = "DDR_DPLL_CLK",
	[CLK_DRA7XX_USB_DPLL_CLK] = "USB_DPLL_CLK",
	[CLK_DRA7XX_PCIE_DPLL_CLK] = "PCIE_DPLL_CLK",
	[CLK_DRA7XX_USB_OTG_SS_REF_CLK] = "USB_OTG_SS_REF_CLK",
	[CLK_DRA7XX_UNIPRO1_DPLL_CLK] = "UNIPRO1_DPLL_CLK",
	[CLK_DRA7XX_WKUPAON_IO_SRCOMP_GFCLK] = "WKUPAON_IO_SRCOMP_GFCLK",
	[CLK_DRA7XX_COREAON_IO_SRCOMP_GFCLK] = "COREAON_IO_SRCOMP_GFCLK",
	[CLK_DRA7XX_UNIPRO2_PHY_REF_GFCLK] = "UNIPRO2_PHY_REF_GFCLK",
	[CLK_DRA7XX_MIPIEXT_PHY_REF_GFCLK] = "MIPIEXT_PHY_REF_GFCLK",
	[CLK_DRA7XX_SATA_REF_GFCLK] = "SATA_REF_GFCLK",
	[CLK_DRA7XX_DSS_SYS_CLK] = "DSS_SYS_CLK",
	[CLK_DRA7XX_ABE_SYS_CLK] = "ABE_SYS_CLK",
	/* DPLL BYPASS INPUT CLKS */
	[CLK_DRA7XX_ABE_DPLL_CLK] = "ABE_DPLL_CLK",
	[CLK_DRA7XX_ABE_DPLL_BYPASS_CLK] = "ABE_DPLL_BYPASS_CLK",
	[CLK_DRA7XX_MPU_DPLL_HS_CLK] = "MPU_DPLL_HS_CLK",
	[CLK_DRA7XX_IVA_DPLL_HS_CLK] = "IVA_DPLL_HS_CLK",
	[CLK_DRA7XX_PER_DPLL_HS_CLK] = "PER_DPLL_HS_CLK",
	[CLK_DRA7XX_USB_DPLL_HS_CLK] = "USB_DPLL_HS_CLK",
	[CLK_DRA7XX_EVE_DPLL_HS_CLK] = "EVE_DPLL_HS_CLK",
	[CLK_DRA7XX_DSP_DPLL_HS_CLK] = "DSP_DPLL_HS_CLK",
	[CLK_DRA7XX_GMAC_DPLL_HS_CLK] = "GMAC_DPLL_HS_CLK",
	[CLK_DRA7XX_GPU_DPLL_HS_CLK] = "GPU_DPLL_HS_CLK",
	[CLK_DRA7XX_DDR_DPLL_HS_CLK] = "DDR_DPLL_HS_CLK",
	/* DPLL HSDIV BYPASS CLK */
	[CLK_DRA7XX_ABE_BYP_CLK_HMN] = "ABE_BYP_CLK_HMN",
	[CLK_DRA7XX_MPU_BYP_CLK_HMN] = "MPU_BYP_CLK_HMN",
	[CLK_DRA7XX_CORE_BYP_CLK_HMN] = "CORE_BYP_CLK_HMN",
	[CLK_DRA7XX_IVA_BYP_CLK_HMN] = "IVA_BYP_CLK_HMN",
	[CLK_DRA7XX_DDR_BYP_CLK_HMN] = "DDR_BYP_CLK_HMN",
	[CLK_DRA7XX_EVE_BYP_CLK_HMN] = "EVE_BYP_CLK_HMN",
	[CLK_DRA7XX_DSP_BYP_CLK_HMN] = "DSP_BYP_CLK_HMN",
	[CLK_DRA7XX_GMAC_BYP_CLK_HMN] = "GMAC_BYP_CLK_HMN",
	[CLK_DRA7XX_GPU_BYP_CLK_HMN] = "GPU_BYP_CLK_HMN",
	[CLK_DRA7XX_PER_BYP_CLK_HMN] = "PER_BYP_CLK_HMN",
	[CLK_DRA7XX_USB_BYP_CLK_HMN] = "USB_BYP_CLK_HMN",
	[CLK_DRA7XX_PCIE_BYP_CLK_HMN] = "PCIE_BYP_CLK_HMN",
	/* DPLL ABE OUTPUT CLKS */
	[CLK_DRA7XX_PER_ABE_X1_GFCLK] = "PER_ABE_X1_GFCLK",
	[CLK_DRA7XX_DPLL_ABE_X2_FCLK] = "DPLL_ABE_X2_FCLK",
	[CLK_DRA7XX_CORE_DPLL_HS_CLK] = "CORE_DPLL_HS_CLK",
	/* DPLL CORE OUTPUTS */
	[CLK_DRA7XX_CORE_DPLL_OUT_CLK] = "CORE_DPLL_OUT_CLK",
	[CLK_DRA7XX_CORE_X2_CLK] = "CORE_X2_CLK",
	[CLK_DRA7XX_CORE_USB_OTG_SS_LFPS_TX_CLK] = "CORE_USB_OTG_SS_LFPS_TX_CLK",
	[CLK_DRA7XX_CORE_GPU_CLK] = "CORE_GPU_CLK",
	[CLK_DRA7XX_CORE_IPU_ISS_BOOST_CLK] = "CORE_IPU_ISS_BOOST_CLK",
	[CLK_DRA7XX_CORE_ISS_MAIN_CLK] = "CORE_ISS_MAIN_CLK",
	[CLK_DRA7XX_BB2D_GFCLK] = "BB2D_GFCLK",
	/* DPLL PER OUTPUTS */
	[CLK_DRA7XX_FUNC_96M_AON_CLK] = "FUNC_96M_AON_CLK",
	[CLK_DRA7XX_FUNC_192M_FCLK] = "FUNC_192M_FCLK",
	[CLK_DRA7XX_FUNC_256M_CLK] = "FUNC_256M_CLK",
	[CLK_DRA7XX_DSS_GFCLK] = "DSS_GFCLK",
	[CLK_DRA7XX_PER_QSPI_CLK] = "PER_QSPI_CLK",
	[CLK_DRA7XX_PER_GPU_CLK] = "PER_GPU_CLK",
	/* DPLL MPU OUTPUTS */
	[CLK_DRA7XX_MPU_GCLK] = "MPU_GCLK",
	/* DPLL IVA OUTPUTS */
	[CLK_DRA7XX_IVA_GCLK] = "IVA_GCLK",
	/* DPLL USB OUTPUTS */
	[CLK_DRA7XX_L3INIT_480M_GFCLK] = "L3INIT_480M_GFCLK",
	[CLK_DRA7XX_L3INIT_960M_GFCLK] = "L3INIT_960M_GFCLK",
	/* DPLL EVE OUTPUTS */
	[CLK_DRA7XX_EVE_GFCLK] = "EVE_GFCLK",
	/* DPLL DSP OUTPUTS */
	[CLK_DRA7XX_DSP_GFCLK] = "DSP_GFCLK",
	[CLK_DRA7XX_EVE_GCLK] = "EVE_GCLK",
	/* DPLL GMAC OUTPUTS */
	[CLK_DRA7XX_GMAC_250M_CLK] = "GMAC_250M_CLK",
	[CLK_DRA7XX_ICSS_IEP_CLK] = "ICSS_IEP_CLK",
	[CLK_DRA7XX_GMAC_RMII_HS_CLK] = "GMAC_RMII_HS_CLK",
	[CLK_DRA7XX_GMII_250MHZ_CLK] = "GMII_250MHZ_CLK",
	[CLK_DRA7XX_ICSS_CLK] =                        "ICSS_CLK",
	/* DPLL GPU OUTPUTS */
	[CLK_DRA7XX_GPU_GCLK] = "GPU_GCLK",
	/* DPLL DDR OUTPUTS */
	[CLK_DRA7XX_EMIF_PHY_GCLK] = "EMIF_PHY_GCLK",
	[CLK_DRA7XX_EMIF_DLL_GCLK] = "EMIF_DLL_GCLK",
	/* DPLL PCIE_REF OUTPUTS */
	[CLK_DRA7XX_PCIE_M2_CLK] = "PCIE_M2_CLK",
	[CLK_DRA7XX_PCIE_REF_CLK] = "PCIE_REF_CLK",
	/* COREAON CLKDM Clocks */
	[CLK_DRA7XX_FUNC_24M_CLK] = "FUNC_24M_CLK",
	[CLK_DRA7XX_FUNC_24M_GFCLK] = "FUNC_24M_GFCLK",
	[CLK_DRA7XX_CORE_CLK] = "CORE_CLK",
	[CLK_DRA7XX_L3_ICLK] = "L3_ICLK",
	[CLK_DRA7XX_EMIF_L3_GICLK] = "EMIF_L3_GICLK",
	[CLK_DRA7XX_L4SEC_L3_GICLK] = "L4SEC_L3_GICLK",
	[CLK_DRA7XX_CAM_L3_GICLK] = "CAM_L3_GICLK",
	[CLK_DRA7XX_C2C_L3_GICLK] = "C2C_L3_GICLK",
	[CLK_DRA7XX_DMA_L3_GICLK] = "DMA_L3_GICLK",
	[CLK_DRA7XX_L3INSTR_L3_GICLK] = "L3INSTR_L3_GICLK",
	[CLK_DRA7XX_L3MAIN1_L3_GICLK] = "L3MAIN1_L3_GICLK",
	[CLK_DRA7XX_L3MAIN2_L3_GICLK] = "L3MAIN2_L3_GICLK",
	[CLK_DRA7XX_MIPIEXT_L3_GICLK] = "MIPIEXT_L3_GICLK",
	[CLK_DRA7XX_DSS_L3_GICLK] = "DSS_L3_GICLK",
	[CLK_DRA7XX_L3INIT_L3_GICLK] = "L3INIT_L3_GICLK",
	[CLK_DRA7XX_CM_CORE_AON_PROFILING_L3_GICLK] = "CM_CORE_AON_PROFILING_L3_GICLK",
	[CLK_DRA7XX_L4_ROOT_CLK] = "L4_ROOT_CLK",
	[CLK_DRA7XX_L4_ICLK] = "L4_ICLK",
	[CLK_DRA7XX_L4PER_L4_GICLK] = "L4PER_L4_GICLK",
	[CLK_DRA7XX_L4SEC_L4_GICLK] = "L4SEC_L4_GICLK",
	[CLK_DRA7XX_C2C_L4_GICLK] = "C2C_L4_GICLK",
	[CLK_DRA7XX_L4CFG_L4_GICLK] = "L4CFG_L4_GICLK",
	[CLK_DRA7XX_MIPIEXT_L4_GICLK] = "MIPIEXT_L4_GICLK",
	[CLK_DRA7XX_L3INIT_L4_GICLK] = "L3INIT_L4_GICLK",
	[CLK_DRA7XX_CM_CORE_AON_PROFILING_L4_GICLK] = "CM_CORE_AON_PROFILING_L4_GICLK",
	/* PRM CLKDM Clocks */
	[CLK_DRA7XX_ABE_LP_CLK] = "ABE_LP_CLK",
	[CLK_DRA7XX_WKUPAON_ICLK] = "WKUPAON_ICLK",
	[CLK_DRA7XX_SR_MM_SYS_GFCLK] = "SR_MM_SYS_GFCLK",
	[CLK_DRA7XX_SR_MPU_SYS_GFCLK] = "SR_MPU_SYS_GFCLK",
	[CLK_DRA7XX_SR_CORE_SYS_GFCLK] = "SR_CORE_SYS_GFCLK",
	[CLK_DRA7XX_WKUPAON_GCLK] = "WKUPAON_GCLK",
	[CLK_DRA7XX_WKUPAON_GICLK] = "WKUPAON_GICLK",
	[CLK_DRA7XX_CM_CORE_AON_SYS_CLK] = "CM_CORE_AON_SYS_CLK",
	[CLK_DRA7XX_WKUPAON_PROFILING_GCLK] = "WKUPAON_PROFILING_GCLK",
	[CLK_DRA7XX_CORE_TS_GFCLK] = "CORE_TS_GFCLK",
	[CLK_DRA7XX_COREAON_TS_GFCLK] = "COREAON_TS_GFCLK",
	[CLK_DRA7XX_L3INSTR_DLL_AGING_GCLK] = "L3INSTR_DLL_AGING_GCLK",
	[CLK_DRA7XX_L3INSTR_TS_GFCLK] = "L3INSTR_TS_GFCLK",
	/* PRM TIMER Clocks */
	[CLK_DRA7XX_TIMER1_GFCLK] = "TIMER1_GFCLK",
	[CLK_DRA7XX_TIMER2_GFCLK] = "TIMER2_GFCLK",
	[CLK_DRA7XX_TIMER3_GFCLK] = "TIMER3_GFCLK",
	[CLK_DRA7XX_TIMER4_GFCLK] = "TIMER4_GFCLK",
	[CLK_DRA7XX_TIMER9_GFCLK] = "TIMER9_GFCLK",
	[CLK_DRA7XX_TIMER10_GFCLK] = "TIMER10_GFCLK",
	[CLK_DRA7XX_TIMER11_GFCLK] = "TIMER11_GFCLK",
	/* CKGEN_USB Clocks */
	[CLK_DRA7XX_UTMI_P3_GFCLK] = "UTMI_P3_GFCLK",
	[CLK_DRA7XX_HSIC_P3_GFCLK] = "HSIC_P3_GFCLK",
	[CLK_DRA7XX_HSIC_P2_GFCLK] = "HSIC_P2_GFCLK",
	[CLK_DRA7XX_HSIC_P1_GFCLK] = "HSIC_P1_GFCLK",
	[CLK_DRA7XX_L3INIT_60M_P1_GFCLK] = "L3INIT_60M_P1_GFCLK",
	[CLK_DRA7XX_L3INIT_60M_P2_GFCLK] = "L3INIT_60M_P2_GFCLK",
	[CLK_DRA7XX_UTMI_ROOT_GFCLK] = "UTMI_ROOT_GFCLK",
	[CLK_DRA7XX_TLL_CH0_GFCLK] = "TLL_CH0_GFCLK",
	[CLK_DRA7XX_TLL_CH1_GFCLK] = "TLL_CH1_GFCLK",
	[CLK_DRA7XX_TLL_CH2_GFCLK] = "TLL_CH2_GFCLK",
	[CLK_DRA7XX_L3INIT_60M_FCLK] = "L3INIT_60M_FCLK",
	[CLK_DRA7XX_HSIC_P1_480M_GFCLK] = "HSIC_P1_480M_GFCLK",
	[CLK_DRA7XX_HSIC_P2_480M_GFCLK] = "HSIC_P2_480M_GFCLK",
	[CLK_DRA7XX_HSIC_P3_480M_GFCLK] = "HSIC_P3_480M_GFCLK",
	[CLK_DRA7XX_XCLK_60M_HSP2] = "XCLK_60M_HSP2",
	[CLK_DRA7XX_XCLK_60M_HSP1] = "XCLK_60M_HSP1",
	[CLK_DRA7XX_UTMI_P1_GFCLK] = "UTMI_P1_GFCLK",
	[CLK_DRA7XX_UTMI_P2_GFCLK] = "UTMI_P2_GFCLK",
	/* CKGEN_ABE Clocks */
	[CLK_DRA7XX_PAD_UCLKS] = "PAD_UCLKS",
	[CLK_DRA7XX_SLIMBUS_UCLKS] = "SLIMBUS_UCLKS",
	[CLK_DRA7XX_ABE_CLK] = "ABE_CLK",
	[CLK_DRA7XX_AESS_FCLK] = "AESS_FCLK",
	[CLK_DRA7XX_ABE_GICLK] = "ABE_GICLK",
	[CLK_DRA7XX_ABE_24M_FCLK] = "ABE_24M_FCLK",
	[CLK_DRA7XX_PAD_GCLKS] = "PAD_GCLKS",
	[CLK_DRA7XX_SLIMBUS_CLK] = "SLIMBUS_CLK",
	[CLK_DRA7XX_MCBSP1_INT_GFCLK] = "MCBSP1_INT_GFCLK",
	[CLK_DRA7XX_MCBSP2_INT_GFCLK] = "MCBSP2_INT_GFCLK",
	[CLK_DRA7XX_MCBSP3_INT_GFCLK] = "MCBSP3_INT_GFCLK",
	[CLK_DRA7XX_MCASP1_INT_GFCLK] = "MCASP1_INT_GFCLK",
	[CLK_DRA7XX_DMIC_INT_GFCLK] = "DMIC_INT_GFCLK",
	[CLK_DRA7XX_MCBSP1_GFCLK] = "MCBSP1_GFCLK",
	[CLK_DRA7XX_MCBSP2_GFCLK] = "MCBSP2_GFCLK",
	[CLK_DRA7XX_MCBSP3_GFCLK] = "MCBSP3_GFCLK",
	[CLK_DRA7XX_MCASP1_GFCLK] = "MCASP1_GFCLK",
	[CLK_DRA7XX_DMIC_GFCLK] = "DMIC_GFCLK",
	[CLK_DRA7XX_TIMER5_GFCLK] = "TIMER5_GFCLK",
	[CLK_DRA7XX_TIMER6_GFCLK] = "TIMER6_GFCLK",
	[CLK_DRA7XX_TIMER7_GFCLK] = "TIMER7_GFCLK",
	[CLK_DRA7XX_TIMER8_GFCLK] = "TIMER8_GFCLK",
	/* CM_CORE Clocks */
	[CLK_DRA7XX_GPU_HYD_GCLK] = "GPU_HYD_GCLK",
	[CLK_DRA7XX_GPU_CORE_GCLK] = "GPU_CORE_GCLK",
	[CLK_DRA7XX_FDIF_GFCLK] = "FDIF_GFCLK",
	[CLK_DRA7XX_PER_ABE_24M_FCLK] = "PER_ABE_24M_FCLK",
	[CLK_DRA7XX_FUNC_96M_FCLK] = "FUNC_96M_FCLK",
	[CLK_DRA7XX_FUNC_48M_FCLK] = "FUNC_48M_FCLK",
	[CLK_DRA7XX_FUNC_24M_FCLK] = "FUNC_24M_FCLK",
	[CLK_DRA7XX_HSI_FCLK] = "HSI_FCLK",
	[CLK_DRA7XX_FUNC_12M_FCLK] = "FUNC_12M_FCLK",
	[CLK_DRA7XX_MMC1_GFCLK] = "MMC1_GFCLK",
	[CLK_DRA7XX_MMC2_GFCLK] = "MMC2_GFCLK",
	[CLK_DRA7XX_PER_ABE_24M_GFCLK] = "PER_ABE_24M_GFCLK",
	[CLK_DRA7XX_PER_96M_GFCLK] = "PER_96M_GFCLK",
	[CLK_DRA7XX_PER_48M_GFCLK] = "PER_48M_GFCLK",
	[CLK_DRA7XX_PER_24M_GFCLK] = "PER_24M_GFCLK",
	[CLK_DRA7XX_HSI_GFCLK] = "HSI_GFCLK",
	[CLK_DRA7XX_PER_12M_GFCLK] = "PER_12M_GFCLK",
	[CLK_DRA7XX_C2C_GFCLK] = "C2C_GFCLK",
	[CLK_DRA7XX_C2C_ICLK] = "C2C_ICLK",
	[CLK_DRA7XX_C2C_GICLK] = "C2C_GICLK",
	[CLK_DRA7XX_EMIF_LL_GCLK] = "EMIF_LL_GCLK",
	[CLK_DRA7XX_GPU_L3_GICLK] = "GPU_L3_GICLK",
	[CLK_DRA7XX_DSS_L4_GICLK] = "DSS_L4_GICLK",
	[CLK_DRA7XX_IPU1_GFCLK] = "IPU1_GFCLK",
	[CLK_DRA7XX_IPU2_GFCLK] = "IPU2_GFCLK",
	[CLK_DRA7XX_EVE_CLK] = "EVE_CLK",
	[CLK_DRA7XX_ID_MAX] = "FIXME" };


typedef enum {
	SYSCLK_DRA7XX_RESERVED_0 = 0,
	SYSCLK_DRA7XX_RESERVED_1 = 1,
	SYSCLK_DRA7XX_20_MHZ = 2,
	SYSCLK_DRA7XX_RESERVED_3 = 3,
	SYSCLK_DRA7XX_19_2_MHZ = 4,
	SYSCLK_DRA7XX_RESERVED_5 = 5,
	SYSCLK_DRA7XX_27_MHZ = 6,
	SYSCLK_DRA7XX_RESERVED_7 = 7,
	SYSCLK_DRA7XX_ID_MAX
} sysclk_dra7xx_id;

static const double sysclk_dra7xx_rate_table[SYSCLK_DRA7XX_ID_MAX] = { /* MHz */
	0.0,
	0.0,
	20.0,
	0.0,
	19.2,
	0.0,
	27.0,
	0.0
};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clk_dra7xx_name_get
 * @BRIEF		return clock name
 * @RETURNS		clock name on success
 *			NULL in case of error
 * @param[in]		id: clock ID
 * @DESCRIPTION		return clock name
 *//*------------------------------------------------------------------------ */
const char *clk_dra7xx_name_get(clk_dra7xx_id id)
{
	CHECK_ARG_LESS_THAN(id, CLK_DRA7XX_ID_MAX + 1, NULL);

	return clk_dra7xx_name_table[id];
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clk_dra7xx_sysclk1_rate_get
 * @BRIEF		Return the mandatory system clock speed, in MHz.
 * @RETURNS		> 0 system clock speed, in MHz.
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in]		none
 * @DESCRIPTION		Return the mandatory system clock speed, in MHz.
 *//*------------------------------------------------------------------------ */
double clk_dra7xx_sysclk1_rate_get(void)
{
	unsigned int reg_val;
	static double sysclk = 0.0;
	sysclk_dra7xx_id sysclk_id;

	if (!cpu_is_dra7xx())
		return (double) OMAPCONF_ERR_CPU;

	if (sysclk > 0.0) {
		dprintf("%s(): sysclk rate=%.1lfMHz\n", __func__, sysclk);
		return sysclk;
	}

	if (!mem_fake_access_get()) {
		reg_val = reg_read(&dra7xx_ckgen_prm_cm_clksel_sys);
		sysclk_id = extract_bitfield(reg_val, 0, 3);
	} else {
		sysclk_id = SYSCLK_DRA7XX_20_MHZ; /* DRA7 EVM PoR */
	}

	sysclk = sysclk_dra7xx_rate_table[sysclk_id];
	if (sysclk == 0.0) {
		fprintf(stderr, "%s(): bad CM_CLKSEL_SYS value(%d)\n",
				__func__, sysclk_id);
		sysclk = (double) OMAPCONF_ERR_UNEXPECTED;
	} else {
		dprintf("%s(): CM_CLKSEL_SYS=0x%x, sysclk rate=%.1lfMHz\n",
				__func__, sysclk_id, sysclk);
	}

	return sysclk;
}

#ifndef CLOCK_DRA7XX_DEBUG
/* #define CLK_DRA7XX_RATE_GET_DEBUG */
#ifdef CLK_DRA7XX_RATE_GET_DEBUG
#undef dprintf
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif
#endif

#define DPRINT_CLK_SPEED1(clk_id, out_clk_speed)\
	dprintf("%s(): %s speed = %fMHz\n",\
	__func__,\
	clk_dra7xx_name_get(clk_id),\
	out_clk_speed);

#define DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed, out_clk_speed)\
	dprintf("%s(): %s src = %s, src speed = %.3fMHz, speed = %fMHz\n",\
	__func__,\
	clk_dra7xx_name_get(clk_id),\
	clk_dra7xx_name_get(src_clk_id),\
	src_clk_speed,\
	out_clk_speed);

#define DPRINT_CLK_SPEED2_DPLL(clk_id, src_clk, src_clk_speed, out_clk_speed)\
	dprintf("%s(): %s src = %s, src speed = %.3fMHz, speed = %fMHz\n",\
	__func__,\
	clk_dra7xx_name_get(clk_id),\
	src_clk,\
	src_clk_speed,\
	out_clk_speed);

#define DPRINT_CLK_SPEED3(clk_id, src_clk_id,\
	src_clk_speed, div, out_clk_speed)\
	dprintf("%s(): %s src = %s, speed = %.3fMHz / %d = %fMHz\n",\
	__func__,\
	clk_dra7xx_name_get(clk_id),\
	clk_dra7xx_name_get(src_clk_id),\
	src_clk_speed,\
	(int) div,\
	out_clk_speed);


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clk_dra7xx_rate_get
 * @BRIEF		convert bitfield value from register into string
 * @RETURNS		> 0 clock speed in MHz
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		clk_id: omap5 clock id
 * @param[in]		ignore: do not consider DPLL stop status.
 *			Useful for functions that needs the DPLL output
 *			frequencies whatever its status
 *			(e.g. audit, clock tree, etc)
 * @DESCRIPTION		convert bitfield value from register into string
 *//*------------------------------------------------------------------------ */
double clk_dra7xx_rate_get(clk_dra7xx_id clk_id,
	unsigned short ignore)
{
	unsigned int reg_val = 0;
	double src_clk_speed, out_clk_speed;
	clk_dra7xx_id src_clk_id;
	double div = 0; /* Force a crash if not properly defined */

	if (!cpu_is_dra7xx())
		return (double) OMAPCONF_ERR_CPU;

	switch (clk_id) {
	case CLK_DRA7XX_SYS_32K:
		out_clk_speed = DRA7XX_SYS_32K_SPEED;
		DPRINT_CLK_SPEED1(clk_id, out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_FUNC_32K_CLK:
		src_clk_id = CLK_DRA7XX_SYS_32K;
		src_clk_speed = clk_dra7xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_SYS_CLKIN1:
		out_clk_speed = clk_dra7xx_sysclk1_rate_get();
		DPRINT_CLK_SPEED1(clk_id, out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_SYS_CLKIN2:
		out_clk_speed = DRA7XX_SYS_CLKIN2_SPEED;
		DPRINT_CLK_SPEED1(clk_id, out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_CORE_DPLL_CLK:
	case CLK_DRA7XX_PER_DPLL_CLK:
	case CLK_DRA7XX_DSP_DPLL_CLK:
	case CLK_DRA7XX_MPU_DPLL_CLK:
	case CLK_DRA7XX_GPU_DPLL_CLK:
	case CLK_DRA7XX_IVA_DPLL_CLK:
	case CLK_DRA7XX_EVE_DPLL_CLK:
	case CLK_DRA7XX_USB_DPLL_CLK:
	case CLK_DRA7XX_DDR_DPLL_CLK:
	case CLK_DRA7XX_PCIE_DPLL_CLK:
	case CLK_DRA7XX_GMAC_DPLL_CLK:
		src_clk_id = CLK_DRA7XX_SYS_CLKIN1;
		src_clk_speed = clk_dra7xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_ABE_DPLL_CLK:
		reg_val = reg_read(&dra7xx_ckgen_prm_cm_clksel_abe_pll_ref);
		if (extract_bit(reg_val, 0) == 1)
			src_clk_id = CLK_DRA7XX_FUNC_32K_CLK;
		else
			src_clk_id = CLK_DRA7XX_ABE_DPLL_SYS_CLK;
		src_clk_speed = clk_dra7xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_ABE_DPLL_SYS_CLK:
		reg_val = reg_read(&dra7xx_ckgen_prm_cm_clksel_abe_pll_sys);
		if (extract_bit(reg_val, 0) == 1)
			src_clk_id = CLK_DRA7XX_SYS_CLKIN2;
		else
			src_clk_id = CLK_DRA7XX_SYS_CLKIN1;
		src_clk_speed = clk_dra7xx_rate_get(src_clk_id,
			ignore);
		reg_val = reg_read(&dra7xx_ckgen_prm_cm_clksel_abe_sys);
		if (extract_bit(reg_val, 0) == 1 && src_clk_speed > 26.0)
			div = 2.0;
		else
			div = 1.0;
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_ABE_DPLL_BYPASS_CLK:
		reg_val = reg_read(&dra7xx_ckgen_prm_cm_clksel_wkupaon);
		if (extract_bit(reg_val, 0) == 1)
			src_clk_id = CLK_DRA7XX_FUNC_32K_CLK;
		else
			src_clk_id = CLK_DRA7XX_ABE_DPLL_SYS_CLK;
		src_clk_speed = clk_dra7xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	/* DPLL HSDIV BYPASS CLK */
	case CLK_DRA7XX_ABE_BYP_CLK_HMN:
		src_clk_id = CLK_DRA7XX_ABE_DPLL_BYPASS_CLK;
		src_clk_speed = clk_dra7xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_MPU_BYP_CLK_HMN:
		src_clk_id = CLK_DRA7XX_MPU_DPLL_HS_CLK;
		src_clk_speed = clk_dra7xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_CORE_BYP_CLK_HMN:
		reg_val = reg_read(&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_core);
		if (extract_bit(reg_val, 23) == 1)
			src_clk_id = CLK_DRA7XX_CORE_DPLL_HS_CLK;
		else
			src_clk_id = CLK_DRA7XX_CORE_DPLL_CLK;
		src_clk_speed = clk_dra7xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_IVA_BYP_CLK_HMN:
		reg_val = reg_read(&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_iva);
		if (extract_bit(reg_val, 23) == 1)
			src_clk_id = CLK_DRA7XX_IVA_DPLL_HS_CLK;
		else
			src_clk_id = CLK_DRA7XX_IVA_DPLL_CLK;
		src_clk_speed = clk_dra7xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_DDR_BYP_CLK_HMN:
		reg_val = reg_read(&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_ddr);
		if (extract_bit(reg_val, 23) == 1)
			src_clk_id = CLK_DRA7XX_DDR_DPLL_HS_CLK;
		else
			src_clk_id = CLK_DRA7XX_DDR_DPLL_CLK;
		src_clk_speed = clk_dra7xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_EVE_BYP_CLK_HMN:
		reg_val = reg_read(&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_eve);
		if (extract_bit(reg_val, 23) == 1)
			src_clk_id = CLK_DRA7XX_EVE_DPLL_HS_CLK;
		else
			src_clk_id = CLK_DRA7XX_EVE_DPLL_CLK;
		src_clk_speed = clk_dra7xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_DSP_BYP_CLK_HMN:
		reg_val = reg_read(&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_dsp);
		if (extract_bit(reg_val, 23) == 1)
			src_clk_id = CLK_DRA7XX_DSP_DPLL_HS_CLK;
		else
			src_clk_id = CLK_DRA7XX_DSP_DPLL_CLK;
		src_clk_speed = clk_dra7xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_GMAC_BYP_CLK_HMN:
		reg_val = reg_read(&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_gmac);
		if (extract_bit(reg_val, 23) == 1)
			src_clk_id = CLK_DRA7XX_GMAC_DPLL_HS_CLK;
		else
			src_clk_id = CLK_DRA7XX_GMAC_DPLL_CLK;
		src_clk_speed = clk_dra7xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_GPU_BYP_CLK_HMN:
		reg_val = reg_read(&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_gpu);
		if (extract_bit(reg_val, 23) == 1)
			src_clk_id = CLK_DRA7XX_GPU_DPLL_HS_CLK;
		else
			src_clk_id = CLK_DRA7XX_GPU_DPLL_CLK;
		src_clk_speed = clk_dra7xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_PER_BYP_CLK_HMN:
		reg_val = reg_read(&dra7xx_ckgen_cm_core_cm_clksel_dpll_per);
		if (extract_bit(reg_val, 23) == 1)
			src_clk_id = CLK_DRA7XX_PER_DPLL_HS_CLK;
		else
			src_clk_id = CLK_DRA7XX_PER_DPLL_CLK;
		src_clk_speed = clk_dra7xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_USB_BYP_CLK_HMN:
		reg_val = reg_read(&dra7xx_ckgen_cm_core_cm_clksel_dpll_usb);
		if (extract_bit(reg_val, 23) == 1)
			src_clk_id = CLK_DRA7XX_USB_DPLL_HS_CLK;
		else
			src_clk_id = CLK_DRA7XX_USB_DPLL_CLK;
		src_clk_speed = clk_dra7xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_PCIE_BYP_CLK_HMN:
		reg_val = reg_read(&dra7xx_ckgen_cm_core_cm_clksel_dpll_pcie_ref);
		if (extract_bit(reg_val, 23) == 1)
			return 0;
		else
			src_clk_id = CLK_DRA7XX_PCIE_DPLL_CLK;
		src_clk_speed = clk_dra7xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	/* DPLL ABE OUTPUTS */
	case CLK_DRA7XX_PER_ABE_X1_GFCLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_ABE, DPLL_DRA7XX_CLKOUT_M2, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_ABE CLKOUT_M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_DPLL_ABE_X2_FCLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_ABE, DPLL_DRA7XX_CLKOUTX2_M2, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_ABE CLKOUTX2_M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_CORE_DPLL_HS_CLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_ABE, DPLL_DRA7XX_CLKOUTX2_M3, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_ABE CLKOUTX2_M3",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	/* END OF DPLL ABE OUTPUTS */

	/* DPLL CORE OUTPUTS */
	case CLK_DRA7XX_CORE_DPLL_OUT_CLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_CORE, DPLL_DRA7XX_CLKOUT_M2, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_CORE CLKOUT_M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_CORE_X2_CLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_CORE, DPLL_DRA7XX_CLKOUTX2_H12, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_CORE CLKOUTX2_H12",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_CORE_USB_OTG_SS_LFPS_TX_CLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_CORE, DPLL_DRA7XX_CLKOUTX2_H13, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_CORE CLKOUTX2_H13",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_CORE_GPU_CLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_CORE, DPLL_DRA7XX_CLKOUTX2_H14, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_CORE CLKOUTX2_H14",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_CORE_IPU_ISS_BOOST_CLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_CORE, DPLL_DRA7XX_CLKOUTX2_H22, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_CORE CLKOUTX2_H22",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_CORE_ISS_MAIN_CLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_CORE, DPLL_DRA7XX_CLKOUTX2_H23, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_CORE CLKOUTX2_H23",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_BB2D_GFCLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_CORE, DPLL_DRA7XX_CLKOUTX2_H24, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_CORE CLKOUTX2_H24",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	/* END OF DPLL CORE OUTPUTS */

	/* DPLL PER OUTPUTS */
	case CLK_DRA7XX_FUNC_96M_AON_CLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_PER, DPLL_DRA7XX_CLKOUT_M2, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_PER CLKOUT_M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_FUNC_192M_FCLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_PER, DPLL_DRA7XX_CLKOUTX2_M2, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_PER CLKOUTX2_M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_FUNC_256M_CLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_PER, DPLL_DRA7XX_CLKOUTX2_H11, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_PER CLKOUTX2_H11",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_DSS_GFCLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_PER, DPLL_DRA7XX_CLKOUTX2_H12, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_PER CLKOUTX2_H12",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_PER_QSPI_CLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_PER, DPLL_DRA7XX_CLKOUTX2_H13, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_PER CLKOUTX2_H13",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_PER_GPU_CLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_PER, DPLL_DRA7XX_CLKOUTX2_H14, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_PER CLKOUTX2_H14",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	/* END OF DPLL PER OUTPUTS */

	/* DPLL MPU OUTPUTS */
	case CLK_DRA7XX_MPU_GCLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_MPU, DPLL_DRA7XX_CLKOUT_M2, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_MPU CLKOUT_M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	/* END OF DPLL MPU OUTPUTS */

	/* DPLL IVA OUTPUTS */
	case CLK_DRA7XX_IVA_GCLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_IVA, DPLL_DRA7XX_CLKOUT_M2, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_IVA CLKOUT_M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	/* END OF DPLL IVA OUTPUTS */

	/* DPLL USB OUTPUTS */
	case CLK_DRA7XX_L3INIT_480M_GFCLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_USB, DPLL_DRA7XX_CLKOUT_M2, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_USB CLKOUT_M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_L3INIT_960M_GFCLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_USB, DPLL_DRA7XX_CLK_DCO_LDO, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_USB CLK_DCO_LDO",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	/* END OF DPLL USB OUTPUTS */

	/* DPLL EVE OUTPUTS */
	case CLK_DRA7XX_EVE_GFCLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_EVE, DPLL_DRA7XX_CLKOUT_M2, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_USB CLKOUT_M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	/* END OF DPLL EVE OUTPUTS */

	/* DPLL DSP OUTPUTS */
	case CLK_DRA7XX_DSP_GFCLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_DSP, DPLL_DRA7XX_CLKOUT_M2, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_USB CLKOUT_M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_EVE_GCLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_DSP, DPLL_DRA7XX_CLKOUTX2_M3, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_USB CLKOUT_M3",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	/* END OF DPLL DSP OUTPUTS */

	/* DPLL GMAC OUTPUTS */
	case CLK_DRA7XX_GMAC_250M_CLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_GMAC, DPLL_DRA7XX_CLKOUT_M2, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_USB CLKOUT_M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_ICSS_IEP_CLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_GMAC, DPLL_DRA7XX_CLKOUTX2_M3, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_USB CLKOUTX2_M3",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_GMAC_RMII_HS_CLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_GMAC, DPLL_DRA7XX_CLKOUTX2_H11, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_USB CLKOUTX2_H11",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_GMII_250MHZ_CLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_GMAC, DPLL_DRA7XX_CLKOUTX2_H12, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_USB CLKOUTX2_H12",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_ICSS_CLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_GMAC, DPLL_DRA7XX_CLKOUTX2_H13, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_USB CLKOUTX2_H13",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	/* END OF DPLL GMAC OUTPUTS */

	/* DPLL GPU OUTPUTS */
	case CLK_DRA7XX_GPU_GCLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_GPU, DPLL_DRA7XX_CLKOUT_M2, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_USB CLKOUT_M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	/* END OF DPLL GPU OUTPUTS */

	/* DPLL DDR OUTPUTS */
	case CLK_DRA7XX_EMIF_PHY_GCLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_DDR, DPLL_DRA7XX_CLKOUT_M2, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_USB CLKOUT_M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_EMIF_DLL_GCLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_DDR, DPLL_DRA7XX_CLKOUTX2_H11, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_USB CLKOUTX2_H11",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	/* END OF DPLL DDR OUTPUTS */

	/* DPLL PCIE_REF OUTPUTS */
	case CLK_DRA7XX_PCIE_M2_CLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_PCIE_REF, DPLL_DRA7XX_CLKOUTX2_M2, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_USB CLKOUTX2_M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_PCIE_REF_CLK:
		src_clk_speed = dpll_dra7xx_output_rate_get(
			DPLL_DRA7XX_PCIE_REF, DPLL_DRA7XX_CLKOUTX2_M2_LDO, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_USB CLKOUTX2_M2_LDO",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	/* END OF DPLL PCIE_REF OUTPUTS */

	/* DPLL BYPASS INPUT CLKS */
	case CLK_DRA7XX_MPU_DPLL_HS_CLK:
	case CLK_DRA7XX_IVA_DPLL_HS_CLK:
	case CLK_DRA7XX_EVE_DPLL_HS_CLK:
	case CLK_DRA7XX_DSP_DPLL_HS_CLK:
		src_clk_id = CLK_DRA7XX_CORE_X2_CLK;
		src_clk_speed = clk_dra7xx_rate_get(src_clk_id,
			ignore);
		if (clk_id == CLK_DRA7XX_MPU_DPLL_HS_CLK)
			reg_val = reg_read(&dra7xx_ckgen_cm_core_aon_cm_bypclk_dpll_mpu);
		else if (clk_id == CLK_DRA7XX_IVA_DPLL_HS_CLK)
			reg_val = reg_read(&dra7xx_ckgen_cm_core_aon_cm_bypclk_dpll_iva);
		else if (clk_id == CLK_DRA7XX_EVE_DPLL_HS_CLK)
			reg_val = reg_read(&dra7xx_ckgen_cm_core_aon_cm_bypclk_dpll_eve);
		else if (clk_id == CLK_DRA7XX_DSP_DPLL_HS_CLK)
			reg_val = reg_read(&dra7xx_ckgen_cm_core_aon_cm_bypclk_dpll_dsp);
		div = (double) (1 << extract_bitfield(reg_val, 0, 2));
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_PER_DPLL_HS_CLK:
	case CLK_DRA7XX_USB_DPLL_HS_CLK:
	case CLK_DRA7XX_GMAC_DPLL_HS_CLK:
	case CLK_DRA7XX_GPU_DPLL_HS_CLK:
	case CLK_DRA7XX_DDR_DPLL_HS_CLK:
		src_clk_id = CLK_DRA7XX_CORE_DPLL_HS_CLK;
		src_clk_speed = clk_dra7xx_rate_get(src_clk_id,
			ignore);
		if (clk_id == CLK_DRA7XX_PER_DPLL_HS_CLK)
			div = 2.0;
		else if (clk_id == CLK_DRA7XX_USB_DPLL_HS_CLK)
			div = 3.0;
		else if ((clk_id == CLK_DRA7XX_GMAC_DPLL_HS_CLK)
			|| (clk_id == CLK_DRA7XX_GPU_DPLL_HS_CLK)
			|| (clk_id == CLK_DRA7XX_DDR_DPLL_HS_CLK))
			div = 1.0;
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;
	/* END of DPLL BYPASS INPUT CLKS */

	/* COREAON CLKDM Clocks */
	case CLK_DRA7XX_FUNC_24M_CLK:
	case CLK_DRA7XX_FUNC_24M_GFCLK:
	case CLK_DRA7XX_CAM_L3_GICLK:
	case CLK_DRA7XX_C2C_L3_GICLK:
	case CLK_DRA7XX_DMA_L3_GICLK:
	case CLK_DRA7XX_L3MAIN2_L3_GICLK:
	case CLK_DRA7XX_MIPIEXT_L3_GICLK:
	case CLK_DRA7XX_L3INIT_L3_GICLK:
		out_clk_speed = 0;
		return out_clk_speed;

	case CLK_DRA7XX_L4_ICLK:
		src_clk_id = CLK_DRA7XX_L4_ROOT_CLK;
		src_clk_speed = clk_dra7xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_L4PER_L4_GICLK:
	case CLK_DRA7XX_L4SEC_L4_GICLK:
	case CLK_DRA7XX_C2C_L4_GICLK:
	case CLK_DRA7XX_L4CFG_L4_GICLK:
	case CLK_DRA7XX_MIPIEXT_L4_GICLK:
	case CLK_DRA7XX_L3INIT_L4_GICLK:
	case CLK_DRA7XX_CM_CORE_AON_PROFILING_L4_GICLK:
		src_clk_id = CLK_DRA7XX_L4_ICLK;
		src_clk_speed = clk_dra7xx_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_CORE_CLK:
		src_clk_id = CLK_DRA7XX_CORE_X2_CLK;
		src_clk_speed = clk_dra7xx_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_L3_ICLK:
		src_clk_id = CLK_DRA7XX_CORE_CLK;
		src_clk_speed = clk_dra7xx_rate_get(src_clk_id, ignore);
		reg_val = reg_read(&dra7xx_ckgen_cm_core_aon_cm_clksel_core);
		div = (double) (1 << extract_bit(reg_val, 4));
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_EMIF_L3_GICLK:
	case CLK_DRA7XX_L4SEC_L3_GICLK:
	case CLK_DRA7XX_L3INSTR_L3_GICLK:
	case CLK_DRA7XX_L3MAIN1_L3_GICLK:
	case CLK_DRA7XX_DSS_L3_GICLK:
	case CLK_DRA7XX_CM_CORE_AON_PROFILING_L3_GICLK:
	case CLK_DRA7XX_L4_ROOT_CLK:
		src_clk_id = CLK_DRA7XX_L3_ICLK;
		src_clk_speed = clk_dra7xx_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	/* Others */
	case CLK_DRA7XX_IPU1_GFCLK:
		reg_val = reg_read(&dra7xx_ipu_cm_core_aon_cm_ipu1_ipu1_clkctrl);
		if (extract_bit(reg_val, 24) == 0)
			src_clk_id = CLK_DRA7XX_DPLL_ABE_X2_FCLK;
		else
			src_clk_id = CLK_DRA7XX_CORE_IPU_ISS_BOOST_CLK;
		src_clk_speed = clk_dra7xx_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_IPU2_GFCLK:
		src_clk_id = CLK_DRA7XX_CORE_IPU_ISS_BOOST_CLK;
		src_clk_speed = clk_dra7xx_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_EVE_CLK:
		reg_val = reg_read(&dra7xx_ckgen_prm_cm_clksel_eve_clk);
		if (extract_bit(reg_val, 0) == 0)
			src_clk_id = CLK_DRA7XX_EVE_GFCLK;
		else
			src_clk_id = CLK_DRA7XX_EVE_GCLK;
		src_clk_speed = clk_dra7xx_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_DRA7XX_ID_MAX:
		out_clk_speed = 0;
		DPRINT_CLK_SPEED1(clk_id, out_clk_speed);
		return out_clk_speed;

	default:
		fprintf(stderr, "%s(): invalid clock id %s(%u)!\n",
			__func__, clk_dra7xx_name_table[clk_id], clk_id);
		return (double) OMAPCONF_ERR_ARG;
	}

	return 0;
}
