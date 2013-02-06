/*
 *
 * @Component			OMAPCONF
 * @Filename			sysconfig44xx.h
 * @Description			OMAP4 SYSCONFIG Register Address Definitions
 * @Author			Patrick Titiano (p-titiano@ti.com)
 * @Date			2010
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
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


#ifndef __SYSCONFIG44XX_H__
#define __SYSCONFIG44XX_H__

#define	OMAP4430_M3_MMU_SYSCONFIG			(unsigned int*) 0x55082010
#define	OMAP4430_DSP_MMU_SYSCONFIG			(unsigned int*) 0x4A066010

/* Voltage domain: LDO_WKUP, Power domain: WKUP, Functional clock domain = WKUP */
#define	OMAP4430_CONTROL_GEN_WKUP_SYSCONFIG		(unsigned int*) 0x4A30C010
#define	OMAP4430_CONTROL_PADCONF_WKUP_SYSCONFIG		(unsigned int*) 0x4A31E010
#define	OMAP4430_GPIO1_SYSCONFIG			(unsigned int*) 0x4A310010 /* slave */
#define OMAP4430_GPT1_TIOCP_CFG				(unsigned int*) 0x4A318010 /* slave */
#define OMAP4430_WDT2_WDSC				(unsigned int*) 0x4A314010 /* slave */
#define OMAP4430_SYNCTIMER_SYSCONFIG			(unsigned int*) 0x4A304004 /* slave */
#define	OMAP4430_KBD_SYSCONFIG 				(unsigned int*) 0x4A31C010 /* slave */

/* Voltage domain: LDO_WKUP, Power domain: WKUP, Functional clock domain = NONE */

/* Voltage domain: LDO_WKUP, Power domain: EMU, Functional clock domain = EMU */

/* Voltage domain: VDD_MPU, Power domain: MPU, Functional clock domain = MPU */

/* Voltage domain: VDD_MPU, Power domain: ALWON_MPU, Functional clock domain = NONE */

/* Voltage domain: VDD_IVA, Power domain: ABE, Functional clock domain = ABE */
#define OMAP4430_AESS_SYSCONFIG				(unsigned int*) 0x490F1010
#define	OMAP4430_DMIC_SYSCONFIG				(unsigned int*) 0x4902E010
#define	OMAP4430_MCASP_SYSCONFIG			(unsigned int*) 0x49028004
#define	OMAP4430_MCBSP1_SYSCONFIG			(unsigned int*) 0x4902208C
#define	OMAP4430_MCBSP2_SYSCONFIG			(unsigned int*) 0x4902408C
#define	OMAP4430_MCBSP3_SYSCONFIG			(unsigned int*) 0x4902608C
#define	OMAP4430_MCPDM_SYSCONFIG			(unsigned int*) 0x49032010
#define	OMAP4430_SLIMBUS1_CMP_SYSCONFIG			(unsigned int*) 0x4902C010 /* slave */
#define OMAP4430_GPT5_TIOCP_CFG				(unsigned int*) 0x49038010
#define OMAP4430_GPT6_TIOCP_CFG				(unsigned int*) 0x4903A010
#define OMAP4430_GPT7_TIOCP_CFG				(unsigned int*) 0x4903C010
#define OMAP4430_GPT8_TIOCP_CFG				(unsigned int*) 0x4903E010
#define OMAP4430_WDT3_WDSC				(unsigned int*) 0x49030010

/* Voltage domain: VDD_IVA, Power domain: IVAHD, Functional clock domain = IVAHD */
#define	OMAP4430_IVAHD_SYSCONFIG			(unsigned int*) 0x5A05A410 /* dual */
#define	OMAP4430_ICONT1_SYSCONFIG			(unsigned int*) 0x5A070010 /* dual */
#define	OMAP4430_ICONT2_SYSCONFIG			(unsigned int*) 0x5A071010 /* dual */
#define	OMAP4430_VDMA_SYSCONFIG				(unsigned int*) 0x5A050010 /* dual */
#define	OMAP4430_IME3_SYSCONFIG				(unsigned int*) 0x5A054010 /* dual */
#define	OMAP4430_IPE3_SYSCONFIG				(unsigned int*) 0x5A058C08 /* slave */
#define	OMAP4430_ILF3_SYSCONFIG				(unsigned int*) 0x5A052010 /* dual */
#define	OMAP4430_MC3_SYSCONFIG				(unsigned int*) 0x5A059408 /* slave */
#define	OMAP4430_CALC3_SYSCONFIG			(unsigned int*) 0x5A058408 /* slave */
#define	OMAP4430_ECD3_SYSCONFIG				(unsigned int*) 0x5A059C08 /* slave */
#define	OMAP4430_ICONT1_SB_SYSCONFIG			(unsigned int*) 0x5A060010 /* slave */
#define	OMAP4430_ICONT2_SB_SYSCONFIG			(unsigned int*) 0x5A060810 /* slave */
#define	OMAP4430_ILF3_SB_SYSCONFIG			(unsigned int*) 0x5A061010 /* slave */
#define	OMAP4430_IME3_SB_SYSCONFIG			(unsigned int*) 0x5A061810 /* slave */
#define	OMAP4430_CALC3_SB_SYSCONFIG			(unsigned int*) 0x5A062010 /* slave */
#define	OMAP4430_IPE3_SB_SYSCONFIG			(unsigned int*) 0x5A062810 /* slave */
#define	OMAP4430_MC3_SB_SYSCONFIG			(unsigned int*) 0x5A063010 /* slave */
#define	OMAP4430_ECD3_SB_SYSCONFIG			(unsigned int*) 0x5A063810 /* slave */

/* Voltage domain: VDD_IVA, Power domain: DSP, Functional clock domain = DSP */
#define	OMAP4430_DSP_SYSC_SYSCONFIG 			(unsigned int*) 0x01C20008
#define	OMAP4430_MMU_DSP_SYSCONFIG			(unsigned int*) 0x4A066010
#define	OMAP4430_DSP_WUGEN_SYSCONFIG			(unsigned int*) 0x01C21008

/* Voltage domain: VDD_CORE, Power domain: ALWON_CORE, Functional clock domain = AO_L4 */
#define	OMAP4430_ERRCONFIG_CORE					(unsigned int*) 0x4A0DD038
#define	OMAP4430_ERRCONFIG_MPU					(unsigned int*) 0x4A0D9038
#define	OMAP4430_ERRCONFIG_IVA					(unsigned int*) 0x4A0DB038

/* Voltage domain: VDD_CORE, Power domain: ALWON_CORE, Functional clock domain = NONE */

/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = L4CFG */
#define	OMAP4430_CONTROL_GEN_CORE_SYSCONFIG		(unsigned int*) 0x4A002010
#define	OMAP4430_CONTROL_PADCONF_CORE_SYSCONFIG		(unsigned int*) 0x4A100010
#define	OMAP4430_SPINLOCK_SYSCONFIG			(unsigned int*) 0x4A0F6010
#define	OMAP4430_SYSTEM_MBX_SYSCONFIG			(unsigned int*) 0x4A0F4010
#define	OMAP4430_IVAHD_MBX_SYSCONFIG			(unsigned int*) 0x5A05A810

/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = C2C */
#define OMAP4430_ICR_MDM_SYS_CONFIG			(unsigned int*) 0x4A0CD010
#define OMAP4430_ICR_MPU_SYS_CONFIG			(unsigned int*) 0x4A0B6010

/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = DMA */
#define	OMAP4430_DMA4_SYSCONFIG				(unsigned int*) 0x4A05602C

/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = MPU_M3 */
#define	OMAP4430_STANDBY_CORE_SYSCONFIG			(unsigned int*) 0x55081004
#define	OMAP4430_IDLE_CORE_SYSCONFIG			(unsigned int*) 0x55081008

/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = NONE */
#define	OMAP4430_MMU_MPU_M3_SYSCONFIG			(unsigned int*) 0x55082010

/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = L3_1 */

/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = L3_2 */
#define	OMAP4430_GPMC_SYSCONFIG				(unsigned int*) 0x50000010

/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = L3_INSTR */

/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = EMIF */
#define	OMAP4430_DMM_SYSCONFIG				(unsigned int*) 0x4E000010

/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = NONE */

/* Voltage domain: VDD_CORE, Power domain: STD_EFUSE, Functional clock domain = STD_EFUSE */

/* Voltage domain: VDD_CORE, Power domain: CUST_EFUSE, Functional clock domain = CUST_EFUSE */

/* Voltage domain: VDD_CORE, Power domain: CAM, Functional clock domain = CAM */
#define	OMAP4430_ISS_HL_SYSCONFIG			(unsigned int*) 0x52000010 /* dual */

#define	OMAP4430_ISP5_SYSCONFIG				(unsigned int*) 0x52010010 /* master */
#define	OMAP4430_RSZ_SYSCONFIG				(unsigned int*) 0x52010404 /* slave */
#define	OMAP4430_SIMCOP_HL_SYSCONFIG			(unsigned int*) 0x52020010 /* master */
#define	OMAP4430_SIMCOP_DMA_SYSCONFIG			(unsigned int*) 0x52020210 /* master */
#define	OMAP4430_SIMCOP_DCT_CFG				(unsigned int*) 0x52020808 /* slave */
#define	OMAP4430_SIMCOP_VLCDJ_CTRL			(unsigned int*) 0x52020604 /* slave */
#define	OMAP4430_SIMCOP_ROT_CFG				(unsigned int*) 0x52020708 /* slave */

#define	OMAP4430_CCP2_SYSCONFIG				(unsigned int*) 0x52001C04 /* master */
#define	OMAP4430_CSI2_A_SYSCONFIG			(unsigned int*) 0x52001010 /* master */
#define	OMAP4430_CSI2_B_SYSCONFIG			(unsigned int*) 0x52001410 /* master */
#define	OMAP4430_TCTRL_SYSCONFIG			(unsigned int*) 0x52000404 /* slave */
#define	OMAP4430_BTE_HL_SYSCONFIG			(unsigned int*) 0x52002010 /* slave */
#define	OMAP4430_CBUFF_HL_SYSCONFIG			(unsigned int*) 0x52001810 /* slave */

#define	OMAP4430_FDIF_SYSCONFIG				(unsigned int*) 0x4A10A010 /* dual */

/* Voltage domain: VDD_CORE, Power domain: DSS, Functional clock domain = DSS */
#define	OMAP4430_DISPC_SYSCONFIG			(unsigned int*) 0x58001010 /* dual */
#define	OMAP4430_DSI1_SYSCONFIG				(unsigned int*) 0x58004010 /* slave */
#define	OMAP4430_DSI2_SYSCONFIG				(unsigned int*) 0x58005010 /* slave */
#define OMAP4430_HDMI_WP_SYSCONFIG			(unsigned int*) 0x58006010 /* slave */
#define	OMAP4430_RFBI_SYSCONFIG				(unsigned int*) 0x58002010 /* slave */

/* Voltage domain: VDD_CORE, Power domain: GFX, Functional clock domain = GFX */
#define	OMAP4430_GFX_SYSCONFIG				(unsigned int*) 0x5600FE10 /* dual */

/* Voltage domain: VDD_CORE, Power domain: L3_INIT, Functional clock domain = L3_INIT */
#define	OMAP4430_HSI_SYSCONFIG				(unsigned int*) 0x4A058010 /* dual */
#define	OMAP4430_HSMMC1_HL_SYSCONFIG			(unsigned int*) 0x4809C010 /* dual */
#define	OMAP4430_HSMMC1_SYSCONFIG			(unsigned int*) 0x4809C110 /* dual */
#define	OMAP4430_HSMMC2_HL_SYSCONFIG			(unsigned int*) 0x480B4010 /* dual */
#define	OMAP4430_HSMMC2_SYSCONFIG			(unsigned int*) 0x480B4110 /* dual */
#define	OMAP4430_UNIPRO1_SYSCONFIG			(unsigned int*) 0x4A068010 /* dual */
#define	OMAP4430_FSUSBHOST_HCOCPSYS			(unsigned int*) 0x4A0A9210 /* dual */
#define	OMAP4430_USBTLL_SYSCONFIG			(unsigned int*) 0x4A062010 /* slave */
#define	OMAP4430_HSUSBOTG_SYSCONFIG			(unsigned int*) 0x4A0AB404 /* dual */
#define	OMAP4430_UHH_SYSCONFIG				(unsigned int*) 0x4A064010 /* dual */

/* Voltage domain: VDD_CORE, Power domain: L3_INIT, Functional clock domain = NONE */

/* Voltage domain: VDD_CORE, Power domain: L4_PER, Functional clock domain = L4_PER */
#define OMAP4430_GPT2_TIOCP_CFG				(unsigned int*) 0x48032010 /* slave */
#define OMAP4430_GPT3_TIOCP_CFG				(unsigned int*) 0x48034010 /* slave */
#define OMAP4430_GPT4_TIOCP_CFG				(unsigned int*) 0x48036010 /* slave */
#define OMAP4430_GPT9_TIOCP_CFG				(unsigned int*) 0x4803E010 /* slave */
#define OMAP4430_GPT10_TIOCP_CFG			(unsigned int*) 0x48086010 /* slave */
#define OMAP4430_GPT11_TIOCP_CFG			(unsigned int*) 0x48088010 /* slave */
#define	OMAP4430_GPIO2_SYSCONFIG			(unsigned int*) 0x48055010 /* slave */
#define	OMAP4430_GPIO3_SYSCONFIG			(unsigned int*) 0x48057010 /* slave */
#define	OMAP4430_GPIO4_SYSCONFIG			(unsigned int*) 0x48059010 /* slave */
#define	OMAP4430_GPIO5_SYSCONFIG			(unsigned int*) 0x4805B010 /* slave */
#define	OMAP4430_GPIO6_SYSCONFIG			(unsigned int*) 0x4805D010 /* slave */
#define	OMAP4430_MCSPI1_HL_SYSCONFIG			(unsigned int*) 0x48098010 /* slave */
#define	OMAP4430_MCSPI1_SYSCONFIG			(unsigned int*) 0x48098110 /* slave */
#define	OMAP4430_MCSPI2_HL_SYSCONFIG			(unsigned int*) 0x4809A010 /* slave */
#define	OMAP4430_MCSPI2_SYSCONFIG			(unsigned int*) 0x4809A110 /* slave */
#define	OMAP4430_MCSPI3_HL_SYSCONFIG			(unsigned int*) 0x480B8010 /* slave */
#define	OMAP4430_MCSPI3_SYSCONFIG			(unsigned int*) 0x480B8110 /* slave */
#define	OMAP4430_MCSPI4_HL_SYSCONFIG			(unsigned int*) 0x480BA010 /* slave */
#define	OMAP4430_MCSPI4_SYSCONFIG			(unsigned int*) 0x480BA110 /* slave */
#define	OMAP4430_UART1_SYSC				(unsigned int*) 0x4806A054 /* slave */
#define	OMAP4430_UART2_SYSC				(unsigned int*) 0x4806C054 /* slave */
#define	OMAP4430_UART3_SYSC				(unsigned int*) 0x48020054 /* slave */
#define	OMAP4430_UART4_SYSC				(unsigned int*) 0x4806E054 /* slave */
#define	OMAP4430_I2C1_SYSC				(unsigned int*) 0x48070010 /* slave */
#define	OMAP4430_I2C2_SYSC				(unsigned int*) 0x48072010 /* slave */
#define	OMAP4430_I2C3_SYSC				(unsigned int*) 0x48060010 /* slave */
#define	OMAP4430_I2C4_SYSC				(unsigned int*) 0x48350010 /* slave */
#define	OMAP4430_MMCHS3_HL_SYSCONFIG			(unsigned int*) 0x480AD010 /* dual */
#define	OMAP4430_MMCHS3_SYSCONFIG			(unsigned int*) 0x480AD110 /* dual */
#define	OMAP4430_MMCHS4_HL_SYSCONFIG			(unsigned int*) 0x480D1010 /* dual */
#define	OMAP4430_MMCHS4_SYSCONFIG			(unsigned int*) 0x480D1110 /* dual */
#define	OMAP4430_SLIMBUS2_CMP_SYSCONFIG			(unsigned int*) 0x48076010 /* slave */
#define	OMAP4430_MMCHS5_HL_SYSCONFIG			(unsigned int*) 0x480D5010 /* dual */
#define	OMAP4430_MMCHS5_SYSCONFIG			(unsigned int*) 0x480D5110 /* dual */
#define	OMAP4430_ELM_SYSCONFIG				(unsigned int*) 0x48078010 /* slave */
#define	OMAP4430_HDQ_SYSCONFIG				(unsigned int*) 0x480B2014 /* slave */
#define	OMAP4430_MCBSP4_SYSCONFIG			(unsigned int*) 0x4809608C /* slave */

#endif /* __SYSCONFIG44XX_H__ */
