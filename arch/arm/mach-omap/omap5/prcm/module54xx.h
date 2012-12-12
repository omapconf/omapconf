/*
 *
 * @Component			OMAPCONF
 * @Filename			module54xx.h
 * @Description			OMAP5 Module Definitions & APIs
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


#ifndef __MODULE54XX_H__
#define __MODULE54XX_H__


#include <prcm-module.h>
#include <clock54xx.h>
#include <clkdm54xx.h>
#include <pwrdm54xx.h>
#include <voltdm54xx.h>


typedef enum {
	/* Voltage dom.: WKUP, Power dom.: EMU, Clock dom. = EMU */
	OMAP5_DEBUGSS,
	/* Voltage dom.: WKUP, Power dom.: WKUPAON, Clock domain = WKUPAON */
	OMAP5_CTRL_MODULE_WKUP,
	OMAP5_L4WKUP_INTERCONNECT,
	OMAP5_GPIO1,
	OMAP5_TIMER1,
	OMAP5_WD_TIMER2,
	OMAP5_SARRAM,
	OMAP5_COUNTER_32K,
	OMAP5_KBD,
	OMAP5_IO_SRCOMP_WKUP,
	/* HS/EMU ONLY */
	OMAP5_TIMER12,
	OMAP5_WDT1,
	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = COREAON */
	OMAP5_SMARTREFLEX_CORE,
	OMAP5_SMARTREFLEX_MM,
	OMAP5_SMARTREFLEX_MPU,
	OMAP5_BANDGAPTS,
	OMAP5_IO_SRCOMP_CORE,
	OMAP5_USB_PHY_CORE,
	/* Voltage dom.: CORE, Power dom.: CAM, Clock domain = CAM */
	OMAP5_FDIF,
	OMAP5_ISS,
	OMAP5_CAL,
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L4CFG */
	OMAP5_CTRL_MODULE_CORE,
	OMAP5_SPINLOCK,
	OMAP5_L4_CFG_INTERCONNECT,
	OMAP5_MAILBOX,
	OMAP5_SARROM,
	OMAP5_OCP2SCP2,
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = EMIF */
	OMAP5_PHY_EMIF,
	OMAP5_DLL_EMIF,
	OMAP5_DMM,
	OMAP5_EMIF1,
	OMAP5_EMIF2,
	OMAP5_EMIF_OCP_FW,
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = IPU */
	OMAP5_IPU,
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN2 */
	OMAP5_GPMC,
	OMAP5_L3_MAIN2_INTERCONNECT,
	OMAP5_OCMC_RAM,
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_INSTR */
	OMAP5_L3_MAIN3_INTERCONNECT,
	OMAP5_L3_INSTR_INTERCONNECT,
	OMAP5_OCP_WP_NOC,
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN1 */
	OMAP5_L3_MAIN1_INTERCONNECT,
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = C2C */
	OMAP5_C2C,
	OMAP5_C2C_OCP_FW,
	OMAP5_MODEM_ICR,
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = DMA */
	OMAP5_DMA_SYSTEM,
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = MIPIEXT */
	OMAP5_LLI,
	OMAP5_LLI_OCP_FW,
	OMAP5_MPHY,
	OMAP5_UNIPRO1,
	/* Voltage dom.: CORE, Power dom.: DSS, Clock domain = DSS */
	OMAP5_DSS,
	OMAP5_BB2D,
	/* Voltage dom.: CORE, Power dom.: L3INIT, Clock domain = L3INIT */
	OMAP5_HSI,
	OMAP5_IEEE1500_2_OCP,
	OMAP5_MMC1,
	OMAP5_MMC2,
	OMAP5_OCPSCP1,
	OMAP5_USB_HOST_HS,
	OMAP5_USB_OTG_SS,
	OMAP5_USB_TLL_HS,
	OMAP5_SATA,
	OMAP5_UNIPRO2,
	OMAP5_MPHY_UNIPRO2,
	OMAP5_OCPSCP3,
	/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_PER */
	OMAP5_TIMER10,
	OMAP5_TIMER11,
	OMAP5_TIMER2,
	OMAP5_TIMER3,
	OMAP5_TIMER4,
	OMAP5_TIMER9,
	OMAP5_ELM,
	OMAP5_GPIO2,
	OMAP5_GPIO3,
	OMAP5_GPIO4,
	OMAP5_GPIO5,
	OMAP5_GPIO6,
	OMAP5_GPIO7,
	OMAP5_GPIO8,
	OMAP5_HDQ1W,
	OMAP5_I2C1,
	OMAP5_I2C2,
	OMAP5_I2C3,
	OMAP5_I2C4,
	OMAP5_I2C5,
	OMAP5_L4_PER_INTERCONNECT,
	OMAP5_MCSPI1,
	OMAP5_MCSPI2,
	OMAP5_MCSPI3,
	OMAP5_MCSPI4,
	OMAP5_MMC3,
	OMAP5_MMC4,
	OMAP5_MMC5,
	OMAP5_SLIMBUS2,
	OMAP5_UART1,
	OMAP5_UART2,
	OMAP5_UART3,
	OMAP5_UART4,
	OMAP5_UART5,
	OMAP5_UART6,
	/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_SEC */
	/* HS/EMU ONLY */
	OMAP5_DMA_CRYPTO,
	OMAP5_AES1,
	OMAP5_AES2,
	OMAP5_SHA2MD5,
	OMAP5_RNG,
	OMAP5_DES3DES,
	OMAP5_PKA,
	/* Voltage dom.: CORE, Power dom.: ABE, Clock domain = ABE */
	OMAP5_AESS,
	OMAP5_DMIC,
	OMAP5_L4_ABE_INTERCONNECT,
	OMAP5_MCASP,
	OMAP5_MCBSP1,
	OMAP5_MCBSP2,
	OMAP5_MCBSP3,
	OMAP5_MCPDM,
	OMAP5_SLIMBUS1,
	OMAP5_TIMER5,
	OMAP5_TIMER6,
	OMAP5_TIMER7,
	OMAP5_TIMER8,
	OMAP5_WD_TIMER3,
	/* Voltage dom.: MM, Power dom.: DSP, Clock domain = DSP */
	OMAP5_DSP,
	/* Voltage dom.: MM, Power dom.: GPU, Clock domain = GPU */
	OMAP5_GPU,
	/* Voltage dom.: MM, Power dom.: IVA, Clock domain = IVA */
	OMAP5_IVA,
	OMAP5_SL2,
	/* Voltage dom.: MPU, Power dom.: MPUAON Clock domain = MPU */
	OMAP5_MPU,
	/* ES2.0 additions */
	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = COREAON */
	OMAP5_USB2PHY,
	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_INSTR */
	OMAP5_CTRL_MODULE_BANDGAP,
	MOD54XX_ID_MAX
} mod54xx_id;

void mod54xx_init(void);
void mod54xx_deinit(void);

const genlist *mod54xx_list_get(void);
int mod54xx_count_get(void);

int mod54xx_config_show(FILE *stream, mod54xx_id id, unsigned int cm_clkctrl);


#endif
