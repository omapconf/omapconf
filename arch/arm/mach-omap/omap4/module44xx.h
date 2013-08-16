/*
 *
 * @Component			OMAPCONF
 * @Filename			module44xx.h
 * @Description			OMAP4 Module Definitions & Functions
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


#ifndef __MODULE44XX_H__
#define __MODULE44XX_H__

#include <clock44xx.h>
#include <clkdm44xx.h>
#include <pwrdm44xx.h>
#include <voltdm44xx.h>
#include <prcm-module.h>


#define MOD44XX_MAX_NAME_LENGTH			21


typedef enum {
	/*
	 * Voltage domain: LDO_WKUP, Power domain: WKUP,
	 * Functional clock domain = WKUP */
	OMAP4_L4_WKUP_INTERCONNECT,
	OMAP4_CONTROL_GEN_WKUP,
	OMAP4_CONTROL_PADCONF_WKUP,
	OMAP4_GPIO1,
	OMAP4_TIMER1,
	OMAP4_TIMER12,
	OMAP4_WDT1,
	OMAP4_WDT2,
	OMAP4_SYNCTIMER,
	OMAP4_SARRAM,
	OMAP4_USIM,
	OMAP4_KEYBOARD,
	/*
	 * Voltage domain: LDO_WKUP, Power domain: WKUP,
	 * Functional clock domain = NONE
	 */
	/*
	 * Voltage domain: LDO_WKUP, Power domain: EMU,
	 * Functional clock domain = EMU
	 */
	OMAP4_DEBUGSS,
	/*
	 * Voltage domain: VDD_MPU, Power domain: MPU,
	 * Functional clock domain = MPU
	 */
	OMAP4_MPU,
	/*
	 * Voltage domain: VDD_IVA, Power domain: ABE,
	 * Functional clock domain = ABE
	 */
	OMAP4_AESS,
	OMAP4_DMIC,
	OMAP4_L4_ABE,
	OMAP4_MCASP,
	OMAP4_MCBSP1,
	OMAP4_MCBSP2,
	OMAP4_MCBSP3,
	OMAP4_MCPDM,
	OMAP4_SLIMBUS1,
	OMAP4_TIMER5,
	OMAP4_TIMER6,
	OMAP4_TIMER7,
	OMAP4_TIMER8,
	OMAP4_WDT3,
	/*
	 * Voltage domain: VDD_IVA, Power domain: IVAHD,
	 * Functional clock domain = IVAHD
	 */
	OMAP4_IVAHD,
	OMAP4_ICONT1,
	OMAP4_ICONT2,
	OMAP4_VDMA,
	OMAP4_IME3,
	OMAP4_IPE3,
	OMAP4_ILF3,
	OMAP4_MC3,
	OMAP4_CALC3,
	OMAP4_ECD3,
	OMAP4_ICONT1_SB,
	OMAP4_ICONT2_SB,
	OMAP4_ILF3_SB,
	OMAP4_IME3_SB,
	OMAP4_CALC3_SB,
	OMAP4_IPE3_SB,
	OMAP4_MC3_SB,
	OMAP4_ECD3_SB,
	OMAP4_SL2,
	/*
	 * Voltage domain: VDD_IVA, Power domain: DSP,
	 * Functional clock domain = DSP
	 */
	OMAP4_DSP,
	OMAP4_MMU_DSP,
	OMAP4_DSP_WUGEN,
	/*
	 * Voltage domain: VDD_CORE, Power domain: ALWON_CORE,
	 * Functional clock domain = AO_L4
	 */
	OMAP4_SMARTREFLEX_CORE,
	OMAP4_SMARTREFLEX_MPU,
	OMAP4_SMARTREFLEX_IVA,
	/*
	 * Voltage domain: VDD_CORE, Power domain: ALWON_CORE,
	 * Functional clock domain = NONE
	 */
/* FIXME: CHECK IF REGISTER ACCESSIBLE FROM MPU	OMAP4_MPU_M3_WUGEN */
	/*
	 * Voltage domain: VDD_CORE, Power domain: CORE,
	 * Functional clock domain = L4CFG
	 */
	OMAP4_L4_CFG,
	OMAP4_CONTROL_GEN_CORE,
	OMAP4_CONTROL_PADCONF_CORE,
	OMAP4_SPINLOCK,
	OMAP4_SYSTEM_MAILBOX,
/* FIXME: CHECK IF REGISTER ACCESSIBLE FROM MPU	OMAP4_IVAHD_MAILBOX */
	OMAP4_SAR_ROM,
	/*
	 * Voltage domain: VDD_CORE, Power domain: CORE,
	 * Functional clock domain = C2C
	 */
	OMAP4_C2C,
	OMAP4_C2C_FW,
	OMAP4_ICR_MDM,
	OMAP4_ICR_MPU,
	/*
	 * Voltage domain: VDD_CORE, Power domain: CORE,
	 * Functional clock domain = DMA
	 */
	OMAP4_SDMA,
	/*
	 * Voltage domain: VDD_CORE, Power domain: CORE,
	 * Functional clock domain = MPU_M3
	 */
	OMAP4_MPU_M3,
	/*
	 * Voltage domain: VDD_CORE, Power domain: CORE,
	 * Functional clock domain = NONE
	 */
	OMAP4_MMU_MPU_M3,
	/*
	 * Voltage domain: VDD_CORE, Power domain: CORE,
	 * Functional clock domain = L3_1
	 */
	OMAP4_L3_1,
	/*
	 * Voltage domain: VDD_CORE, Power domain: CORE,
	 * Functional clock domain = L3_2
	 */
	OMAP4_L3_2,
	OMAP4_GPMC,
	OMAP4_OCMC_RAM,
	/*
	 * Voltage domain: VDD_CORE, Power domain: CORE,
	 * Functional clock domain = L3_INSTR
	 */
	OMAP4_L3_3,
	OMAP4_L3_INSTR,
	OMAP4_OCP_WP1,
	/*
	 * Voltage domain: VDD_CORE, Power domain: CORE,
	 * Functional clock domain = EMIF
	 */
	OMAP4_DMM,
	OMAP4_EMIF_FW,
	OMAP4_EMIF1,
	OMAP4_EMIF2,
	OMAP4_DLL,
	OMAP4_DDRPHY,
	/*
	 * Voltage domain: VDD_CORE, Power domain: STD_EFUSE,
	 * Functional clock domain = STD_EFUSE
	 */
	OMAP4_STD_EFUSE,
	/*
	 * Voltage domain: VDD_CORE, Power domain: CUST_EFUSE,
	 * Functional clock domain = CUST_EFUSE
	 */
	OMAP4_CUST_EFUSE,
	/*
	 * Voltage domain: VDD_CORE, Power domain: CAM,
	 * Functional clock domain = CAM
	 */
	OMAP4_ISS,
	OMAP4_CCP2,
	OMAP4_CSI2_A,
	OMAP4_CSI2_B,
	OMAP4_TCTRL,
	OMAP4_BTE,
	OMAP4_CBUFF,
	OMAP4_ISP5,
	OMAP4_RSZ,
	OMAP4_SIMCOP,
	OMAP4_SIMCOP_DMA,
	OMAP4_SIMCOP_DCT,
	OMAP4_SIMCOP_VLCDJ,
	OMAP4_SIMCOP_ROT,
	OMAP4_FDIF,
	/*
	 * Voltage domain: VDD_CORE, Power domain: DSS,
	 * Functional clock domain = DSS
	 */
	OMAP4_DISPC,
	OMAP4_DSI1,
	OMAP4_DSI2,
	OMAP4_HDMI,
	OMAP4_RFBI,
	OMAP4_BB2D,
	/*
	 * Voltage domain: VDD_CORE, Power domain: GFX,
	 * Functional clock domain = GFX
	 */
	OMAP4_GFX,
	/*
	 * Voltage domain: VDD_CORE, Power domain: L3_INIT,
	 * Functional clock domain = L3_INIT
	 */
	OMAP4_HSI,
	OMAP4_MMC1,
	OMAP4_MMC1_HL,
	OMAP4_MMC2,
	OMAP4_MMC2_HL,
	OMAP4_UNIPRO1,
	OMAP4_FSUSBHOST,
	OMAP4_HSUSBOTG,
	OMAP4_USBPHY,
	OMAP4_HSUSBHOST,
	OMAP4_USBTLL,
	OMAP4_P1500,
	/*
	 * Voltage domain: VDD_CORE, Power domain: L4_PER,
	 * Functional clock domain = L4_SEC
	 */
	OMAP4_CRYPTODMA,
	OMAP4_AES1,
	OMAP4_AES2,
	OMAP4_SHA2MD5_1,
	OMAP4_RNG,
	OMAP4_DES3DES,
	OMAP4_PKAEIP29,
	/*
	 * Voltage domain: VDD_CORE, Power domain: L4_PER,
	 * Functional clock domain = L4_PER
	 */
	OMAP4_L4_PER,
	OMAP4_TIMER2,
	OMAP4_TIMER3,
	OMAP4_TIMER4,
	OMAP4_TIMER9,
	OMAP4_TIMER10,
	OMAP4_TIMER11,
	OMAP4_GPIO2,
	OMAP4_GPIO3,
	OMAP4_GPIO4,
	OMAP4_GPIO5,
	OMAP4_GPIO6,
	OMAP4_MCSPI1_HL,
	OMAP4_MCSPI1,
	OMAP4_MCSPI2_HL,
	OMAP4_MCSPI2,
	OMAP4_MCSPI3_HL,
	OMAP4_MCSPI3,
	OMAP4_MCSPI4_HL,
	OMAP4_MCSPI4,
	OMAP4_UART1,
	OMAP4_UART2,
	OMAP4_UART3,
	OMAP4_UART4,
	OMAP4_I2C1,
	OMAP4_I2C2,
	OMAP4_I2C3,
	OMAP4_I2C4,
	OMAP4_MMC3,
	OMAP4_MMC3_HL,
	OMAP4_MMC4,
	OMAP4_MMC4_HL,
	OMAP4_SLIMBUS2,
	OMAP4_MMC5,
	OMAP4_MMC5_HL,
	OMAP4_ELM,
	OMAP4_HDQ1W,
	OMAP4_MCBSP4,
	OMAP4_MODULE_ID_MAX
} mod44xx_id;

void mod44xx_init(void);
void mod44xx_deinit(void);

const genlist *mod44xx_list_get(void);
int mod44xx_count_get(void);

int mod44xx_init_info_table(void);

mod44xx_id mod44xx_get_id(const char *name);
char *mod44xx_get_name(mod44xx_id id,
	char name[MOD44XX_MAX_NAME_LENGTH]);
clkdm44xx_id mod44xx_get_clkdm(mod44xx_id id);
pwrdm44xx_id mod44xx_get_pwrdm(mod44xx_id id);
voltdm44xx_id mod44xx_get_voltdm(mod44xx_id id);

int mod44xx_get_mode(mod44xx_id id, mod_module_mode *mmode);
int mod44xx_is_accessible(mod44xx_id module_id);
int mod_module_mode2string(char s[21], unsigned short mmode);
int mod_idlest2string(char s[21], unsigned short idlest);

int mod44xx_get_interface_type(mod44xx_id module_id,
	mod_interface_type *type);
int mod44xx_has_clockactivity_bit(mod44xx_id module_id);
int mod44xx_get_autoidle_mode(mod44xx_id module_id,
	mod_autoidle_mode *mode);
int mod44xx_get_idle_mode(mod44xx_id module_id,
	mod_idle_mode *mode);
int mod44xx_has_smart_idle_wakeup_mode(mod44xx_id id);
mod_idle_status mod44xx_get_idle_status(mod44xx_id id,
	char idlest[21]);
int mod44xx_get_standby_mode(mod44xx_id module_id,
	mod_standby_mode *mode);
mod_standby_status mod44xx_get_standby_status(mod44xx_id id,
	char st[11]);
int mod44xx_get_clock_activity_mode(mod44xx_id module_id,
	mod_clock_activity_mode *mode);
int mod44xx_get_src_clk(mod44xx_id module_id, int *src_clk_id);
int mod44xx_get_por_clk_speed(mod44xx_id module_id,
	unsigned short opp, double *por_clk_speed);
int mod44xx_get_clk_speed(mod44xx_id module_id,
	clock44xx_id *src_clk_id, opp44xx_id *opp_id, double *speed);

int mod44xx_config_show(FILE *stream, const char name[11],
	unsigned int cm_clkctrl_addr, unsigned int cm_clkctrl,
	unsigned int rm_context_addr, unsigned int rm_context);


#endif
