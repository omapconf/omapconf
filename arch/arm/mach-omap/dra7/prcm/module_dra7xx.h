/*
 *
 * @Component			OMAPCONF
 * @Filename			module_dra7xx.h
 * @Description			DRA7 Module Definitions & APIs
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


#ifndef __MODULE_DRA7XX_H__
#define __MODULE_DRA7XX_H__


#include <prcm-module.h>
#include <clock_dra7xx.h>
#include <voltdm_dra7xx.h>


typedef enum {
	/* Voltage dom.: CORE, Power dom.: WKUPAON, Clock domain = WKUPAON */
	DRA7_CTRL_MODULE_WKUP,
	DRA7_L4WKUP_INTERCONNECT,
	DRA7_GPIO1,
	DRA7_TIMER1,
	DRA7_TIMER12,
	DRA7_WD_TIMER2,
	DRA7_PRCM_MPU,
	DRA7_COUNTER_32K,
	DRA7_KBD,
	DRA7_DCAN1,
	DRA7_UART10,
	/* Voltage dom.: CORE, Power dom.: WKUPAON, Clock domain: N/A */
	DRA7_PRM,
	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = COREAON */
	DRA7_SMARTREFLEX_CORE,
	DRA7_SMARTREFLEX_MPU,
	DRA7_SMARTREFLEX_DSPEVE,
	DRA7_SMARTREFLEX_GPU,
	DRA7_SMARTREFLEX_IVAHD,
	DRA7_DPLL_EVE,
	DRA7_CM_CORE_AON,
	DRA7_DPLL_ABE,
	DRA7_DPLL_CORE,
	DRA7_DPLL_PER,
	DRA7_DPLL_GPU,
	DRA7_DPLL_IVA,
	DRA7_DPLL_GMAC,
	DRA7_DPLL_DSP,
	DRA7_DPLL_DDR,
	DRA7_DPLL_PCIE_REF,
	DRA7_APLL_PCIE,
	DRA7_DPLL_USB,
	DRA7_WUGEN_IPU,
	DRA7_WUGEN_SYSTEM,
	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = CD_EMU */
	DRA7_DEBUGSS,
	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = CD_L4_PER1 */
	DRA7_TIMER10,
	DRA7_TIMER11,
	DRA7_TIMER2,
	DRA7_TIMER3,
	DRA7_TIMER4,
	DRA7_TIMER9,
	DRA7_ELM,
	DRA7_GPIO2,
	DRA7_GPIO3,
	DRA7_GPIO4,
	DRA7_GPIO5,
	DRA7_GPIO6,
	DRA7_GPIO7,
	DRA7_GPIO8,
	DRA7_HDQ1W,
	DRA7_I2C1,
	DRA7_I2C2,
	DRA7_I2C3,
	DRA7_I2C4,
	DRA7_L4_PER1_INTERCONNECT,
	DRA7_MCSPI1,
	DRA7_MCSPI2,
	DRA7_MCSPI3,
	DRA7_MCSPI4,
	DRA7_MMC3,
	DRA7_MMC4,
	DRA7_UART1,
	DRA7_UART2,
	DRA7_UART3,
	DRA7_UART4,
	DRA7_UART5,
	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = CD_L4_PER2 */
	DRA7_L4_PER2_INTERCONNECT,
	DRA7_MCASP2,
	DRA7_MCASP3,
	DRA7_MCASP4,
	DRA7_MCASP5,
	DRA7_MCASP6,
	DRA7_MCASP7,
	DRA7_MCASP8,
	DRA7_DCAN2,
	DRA7_QSPI,
	DRA7_PWMSS1,
	DRA7_PWMSS2,
	DRA7_PWMSS3,
	DRA7_UART7,
	DRA7_UART8,
	DRA7_UART9,
	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = CD_L4_PER3 */
	DRA7_L4_PER3_INTERCONNECT,
	DRA7_TIMER13,
	DRA7_TIMER14,
	DRA7_TIMER15,
	DRA7_TIMER16,
	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = CD_L4_SEC */
	DRA7_AES1,
	DRA7_AES2,
	DRA7_SHA2MD5_1,
	DRA7_SHA2MD5_2,
	DRA7_RNG,
	DRA7_DMA_CRYPTO,
	DRA7_DES3DES,
	DRA7_FPKA,
	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = CD_L4_CFG */
	DRA7_CTRL_MODULE_CORE,
	DRA7_SPINLOCK,
	DRA7_L4_CFG_INTERCONNECT,
	DRA7_MAILBOX1,
	DRA7_MAILBOX2,
	DRA7_MAILBOX3,
	DRA7_MAILBOX4,
	DRA7_MAILBOX5,
	DRA7_MAILBOX6,
	DRA7_MAILBOX7,
	DRA7_MAILBOX8,
	DRA7_MAILBOX9,
	DRA7_MAILBOX10,
	DRA7_MAILBOX11,
	DRA7_MAILBOX12,
	DRA7_MAILBOX13,
	DRA7_OCP2SCP2,
	DRA7_SAR_ROM,
	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = CD_EMIF */
	DRA7_DMM,
	DRA7_EMIF1,
	DRA7_EMIF2,
	DRA7_EMIF_OCP_FW,
	DRA7_DLL,
	DRA7_EMIF_PHY1,
	DRA7_EMIF_PHY2,
	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = CD_L3_MAIN1 */
	DRA7_L3_MAIN1_INTERCONNECT,
	DRA7_GPMC,
	DRA7_OCMC_RAM1,
	DRA7_OCMC_RAM2,
	DRA7_OCMC_RAM3,
	DRA7_OCMC_MMU1,
	DRA7_OCMC_MMU2,
	DRA7_OCMC_VCP1,
	DRA7_OCMC_VCP2,
	DRA7_OCMC_EDMA,
	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = CD_ATL */
	DRA7_ATL,
	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = CD_DMA */
	DRA7_DMA_SYSTEM,
	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = CD_L3_INSTR */
	DRA7_OCP_WP_NOC,
	DRA7_L3_INSTR_INTERCONNECT,
	DRA7_MAIN_2_INTERCONNECT,
	DRA7_CTRL_MODULE_BANDGAP,
	DRA7_DLL_AGING,
	/* Voltage dom.: CORE, Power dom.: PD_CAM, Clock domain = CD_CAM */
	DRA7_VIP1,
	DRA7_VIP2,
	DRA7_VIP3,
	/* Voltage dom.: CORE, Power dom.: PD_CORE, Clock domain = CD_CORE */
	DRA7_IPU2,
	/* Voltage dom.: CORE, Power dom.: PD_IPU, Clock domain = CD_IPU */
	DRA7_MCASP1,
	DRA7_TIMER5,
	DRA7_TIMER6,
	DRA7_TIMER7,
	DRA7_TIMER8,
	DRA7_UART6,
	DRA7_I2C5,
	/* Voltage dom.: CORE, Power dom.: PD_IPU, Clock domain = CD_IPU1 */
	DRA7_IPU1,
	/* Voltage dom.: CORE, Power dom.: PD_DSS, Clock domain = CD_DSS */
	DRA7_BB2D,
	DRA7_DSS,
	DRA7_HDMI,
	DRA7_HDMI_PHY,
	/* Voltage dom.: CORE, Power dom.: PD_CUSTEFUSE, Clock domain = CD_CUSTEFUSE */
	DRA7_EFUSE_CTRL_CUST,
	/* Voltage dom.: CORE, Power dom.: PD_L3INIT, Clock domain = CD_L3INIT */
	DRA7_MMC1,
	DRA7_MMC2,
	DRA7_USB1,
	DRA7_USB2,
	DRA7_USB3,
	DRA7_USB4,
	DRA7_OCP2SCP1,
	DRA7_OCP2SCP3,
	DRA7_IEEE1500_2_OCP,
	DRA7_MLB,
	DRA7_SATA,
	/* Voltage dom.: CORE, Power dom.: PD_L3INIT, Clock domain = CD_GMAC */
	DRA7_GMAC,
	/* Voltage dom.: CORE, Power dom.: PD_L3INIT, Clock domain = CD_PCIE */
	DRA7_PCIE_SS1,
	DRA7_PCIE_SS2,
	/* Voltage dom.: CORE, Power dom.: PD_VPE, Clock domain = CD_VPE */
	DRA7_VPE,
	/* Voltage dom.: MPU, Power dom.: PD_MPU, Clock domain = CD_MPU */
	DRA7_CPU0,
	DRA7_CPU1,
	/* Voltage dom.: MPU, Power dom.: PD_MPUAON, Clock domain = CD_MPUAON */
	DRA7_DPLL_MPU,
	DRA7_MPU_L2CACHE,
	/* Voltage dom.: IVAHD, Power dom.: PD_IVA, Clock domain = CD_IVA */
	DRA7_IVAHD,
	DRA7_SL2,
	/* Voltage dom.: DSPEVE, Power dom.: PD_DSP1, Clock domain = CD_DSP1 */
	DRA7_DSP1,
	/* Voltage dom.: DSPEVE, Power dom.: PD_DSP2, Clock domain = CD_DSP2 */
	DRA7_DSP2,
	/* Voltage dom.: DSPEVE, Power dom.: PD_EVE1, Clock domain = CD_EVE1 */
	DRA7_EVE1,
	/* Voltage dom.: DSPEVE, Power dom.: PD_EVE2, Clock domain = CD_EVE2 */
	DRA7_EVE2,
	/* Voltage dom.: DSPEVE, Power dom.: PD_MMAON, Clock domain = N/A */
	DRA7_WUGEN_DSP,
	/* Voltage dom.: GPU, Power dom.: PD_GPU, Clock domain = CD_GPU */
	DRA7_GPU,
	/* Voltage dom.: RTC, Power dom.: PD_RTC, Clock domain = CD_RTC */
	DRA7_RTCSS,
	MOD_DRA7XX_ID_MAX
} mod_dra7xx_id;

void mod_dra7xx_init(void);
void mod_dra7xx_deinit(void);

const genlist *mod_dra7xx_list_get(void);
int mod_dra7xx_count_get(void);


#endif
