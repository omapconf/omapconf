/*
 *
 * @Component			OMAPCONF
 * @Filename			module44xx-data.c
 * @Description			OMAP4 Module Definitions
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


#include <lib.h>
#include <module.h>
#include <clockdomain.h>
#include <powerdomain.h>
#include <voltdomain.h>
#include <opp.h>
#include <module44xx-data.h>
#include <sysconfig44xx.h>
#include <cm44xx.h>
#include <prm44xx.h>
#include <cpuinfo.h>


/* #define MODULE44XX_DATA_DEBUG */
#ifdef MODULE44XX_DATA_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


mod44xx_info mod44xx_info_table[OMAP4_MODULE_ID_MAX];


const char
	mod44xx_name_table[OMAP4_MODULE_ID_MAX][MODULE_MAX_NAME_LENGTH] = {
/*
 * Voltage domain: LDO_WKUP, Power domain: WKUP, Functional clock domain = WKUP
 */
	"L4WKUP",
	"CONTROL_GEN_WKUP",
	"CONTROL_PADCONF_WKUP",
	"GPIO1",
	"TIMER1",
	"TIMER12",
	"WDT1",
	"WDT2",
	"SYNCTIMER",
	"SARRAM",
	"USIM",
	"KEYBOARD",
/*
 * Voltage domain: LDO_WKUP, Power domain: WKUP, Functional clock domain = NONE
 */

/* Voltage domain: LDO_WKUP, Power domain: EMU, Functional clock domain = EMU */
	"DEBUGSS",
/* Voltage domain: VDD_MPU, Power domain: MPU, Functional clock domain = MPU */
	"MPU",
/* Voltage domain: VDD_IVA, Power domain: ABE, Functional clock domain = ABE */
	"AESS",
	"DMIC",
	"L4_ABE",
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
	"WDT3",
/*
 * Voltage domain: VDD_IVA, Power domain: IVAHD, Functional clock domain = IVAHD
 */
	"IVAHD",
	"ICONT1",
	"ICONT2",
	"VDMA",
	"IME3",
	"IPE3",
	"ILF3",
	"MC3",
	"CALC3",
	"ECD3",
	"ICONT1_SB",
	"ICONT2_SB",
	"ILF3_SB",
	"IME3_SB",
	"CALC3_SB",
	"IPE3_SB",
	"MC3_SB",
	"ECD3_SB",
	"SL2",
/*
 * Voltage domain: VDD_IVA, Power domain: DSP, Functional clock domain = DSP
 */
	"DSP",
	"MMU_DSP",
	"DSP_WUGEN",
/*
 * Voltage domain: VDD_CORE, Power domain: ALWON_CORE, Functional clock domain
 * = AO_L4
 */
	"SMARTREFLEX_CORE",
	"SMARTREFLEX_MPU",
	"SMARTREFLEX_IVA",
/*
 * Voltage domain: VDD_CORE, Power domain: ALWON_CORE, Functional clock domain
 * = NONE
 */

/* FIXME: CHECK IF REGISTER ACCESSIBLE FROM MPU	"MPU_M3_WUGEN" */

/*
 * Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = L4CFG
 */
	"L4_CFG",
	"CONTROL_GEN_CORE",
	"CONTROL_PADCONF_CORE",
	"SPINLOCK",
	"SYSTEM_MAILBOX",
/* FIXME: CHECK IF REGISTER ACCESSIBLE FROM MPU	"IVAHD_MAILBOX" */
	"SAR_ROM",
/*
 * Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = C2C
 */
	"C2C",
	"C2C_FW",
	"ICR_MDM",
	"ICR_MPU",
/*
 * Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = DMA
 */
	"SDMA",
/*
 * Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain
 * = MPU_M3
 */
	"MPU_M3",
/*
 * Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = NONE
 */
	"MMU_MPU_M3",
/*
 * Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = L3_1
 */
	"L3_1",
/*
 * Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = L3_2
 */
	"L3_2",
	"GPMC",
	"OCMC_RAM",
/*
 * Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain
 * = L3_INSTR
 */
	"L3_3",
	"L3_INSTR",
	"OCP_WP1",
/*
 * Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = EMIF
 */
	"DMM",
	"EMIF_FW",
	"EMIF1",
	"EMIF2",
	"DLL",
	"DDRPHY",
/*
 * Voltage domain: VDD_CORE, Power domain: STD_EFUSE, Functional clock domain
 * = STD_EFUSE
 */
	"STD_EFUSE",
/*
 * Voltage domain: VDD_CORE, Power domain: CUST_EFUSE, Functional clock domain
 * = CUST_EFUSE */
	"CUST_EFUSE",
/* Voltage domain: VDD_CORE, Power domain: CAM, Functional clock domain = CAM */
	"ISS",
	"CCP2",
	"CSI2_A",
	"CSI2_B",
	"TCTRL",
	"BTE",
	"CBUFF",
	"ISP5",
	"RSZ",
	"SIMCOP",
	"SIMCOP_DMA",
	"SIMCOP_DCT",
	"SIMCOP_VLCDJ",
	"SIMCOP_ROT",
	"FDIF",
/* Voltage domain: VDD_CORE, Power domain: DSS, Functional clock domain = DSS */
	"DISPC",
	"DSI1",
	"DSI2",
	"HDMI",
	"RFBI",
	"BB2D",
/* Voltage domain: VDD_CORE, Power domain: GFX, Functional clock domain = GFX */
	"GFX",
/*
 * Voltage domain: VDD_CORE, Power domain: L3_INIT, Functional clock domain
 * = L3_INIT
 */
	"HSI",
	"MMC1",
	"MMC1_HL",
	"MMC2",
	"MMC2_HL",
	"UNIPRO_1",
	"FSUSBHOST",
	"HSUSBOTG",
	"USBPHY",
	"HSUSBHOST",
	"USBTLL",
	"P1500",
/*
 * Voltage domain: VDD_CORE, Power domain: L4_PER, Functional clock domain
 * = L4_SEC
 */
	"CRYPTODMA",
	"AES1",
	"AES2",
	"SHA2MD5_1",
	"RNG",
	"DES3DES",
	"PKAEIP29",
/*
 * Voltage domain: VDD_CORE, Power domain: L4_PER, Functional clock domain
 * = L4_PER
 */
	"L4_PER",
	"TIMER2",
	"TIMER3",
	"TIMER4",
	"TIMER9",
	"TIMER10",
	"TIMER11",
	"GPIO2",
	"GPIO3",
	"GPIO4",
	"GPIO5",
	"GPIO6",
	"MCSPI1_HL",
	"MCSPI1",
	"MCSPI2_HL",
	"MCSPI2",
	"MCSPI3_HL",
	"MCSPI3",
	"MCSPI4_HL",
	"MCSPI4",
	"UART1",
	"UART2",
	"UART3",
	"UART4",
	"I2C1",
	"I2C2",
	"I2C3",
	"I2C4",
	"MMC3",
	"MMC3_HL",
	"MMC4",
	"MMC4_HL",
	"SLIMBUS2",
	"MMC5",
	"MMC5_HL",
	"ELM",
	"HDQ1W",
	"MCBSP4"};

const short int mod44xx_has_smart_idle_wakeup_table[OMAP4_MODULE_ID_MAX] = {
	0, /* OMAP4_L4_WKUP_INTERCONNECT */
	0, /* OMAP4_CONTROL_GEN_WKUP */
	0, /* OMAP4_CONTROL_PADCONF_WKUP */
	1, /* OMAP4_GPIO1 */
	1, /* OMAP4_TIMER1 */
	1, /* OMAP4_TIMER12 */
	1, /* OMAP4_WDT1 */
	1, /* OMAP4_WDT2 */
	0, /* OMAP4_SYNCTIMER */
	0, /* OMAP4_SARRAM */
	1, /* OMAP4_USIM */
	0, /* OMAP4_KEYBOARD */
	0, /* OMAP4_DEBUGSS */
	0, /* OMAP4_MPU */
	0, /* OMAP4_AESS */
	1, /* OMAP4_DMIC */
	0, /* OMAP4_L4_ABE */
	0, /* OMAP4_MCASP */
	0, /* OMAP4_MCBSP1 */
	0, /* OMAP4_MCBSP2 */
	0, /* OMAP4_MCBSP3 */
	1, /* OMAP4_MCPDM */
	1, /* OMAP4_SLIMBUS1 */
	1, /* OMAP4_TIMER5 */
	1, /* OMAP4_TIMER6 */
	1, /* OMAP4_TIMER7 */
	1, /* OMAP4_TIMER8 */
	1, /* OMAP4_WDT3 */
	0, /* OMAP4_IVAHD */
	0, /* OMAP4_ICONT1 */
	0, /* OMAP4_ICONT2 */
	0, /* OMAP4_VDMA */
	1, /* OMAP4_IME3 */
	0, /* OMAP4_IPE3 */
	1, /* OMAP4_ILF3 */
	0, /* OMAP4_MC3 */
	0, /* OMAP4_CALC3 */
	1, /* OMAP4_ECD3 */
	0, /* OMAP4_ICONT1_SB */
	0, /* OMAP4_ICONT2_SB */
	0, /* OMAP4_ILF3_SB */
	0, /* OMAP4_IME3_SB */
	0, /* OMAP4_CALC3_SB */
	0, /* OMAP4_IPE3_SB */
	0, /* OMAP4_MC3_SB */
	0, /* OMAP4_ECD3_SB */
	0, /* OMAP4_SL2 */
	0, /* OMAP4_DSP */
	0, /* OMAP4_MMU_DSP */
	0, /* OMAP4_DSP_WUGEN */
	1, /* OMAP4_SMARTREFLEX_CORE */
	1, /* OMAP4_SMARTREFLEX_MPU */
	1, /* OMAP4_SMARTREFLEX_IVA */
	0, /* OMAP4_L4_CFG */
	0, /* OMAP4_CONTROL_GEN_CORE */
	0, /* OMAP4_CONTROL_PADCONF_CORE */
	0, /* OMAP4_SPINLOCK */
	0, /* OMAP4_SYSTEM_MAILBOX */
	0, /* OMAP4_SAR_ROM */
	0, /* OMAP4_C2C */
	0, /* OMAP4_C2C_FW */
	0, /* OMAP4_ICR_MDM */
	0, /* OMAP4_ICR_MPU */
	0, /* OMAP4_SDMA */
	1, /* OMAP4_MPU_M3 */
	0, /* OMAP4_MMU_MPU_M3 */
	0, /* OMAP4_L3_1 */
	0, /* OMAP4_L3_2 */
	0, /* OMAP4_GPMC */
	0, /* OMAP4_OCMC_RAM */
	0, /* OMAP4_L3_3 */
	0, /* OMAP4_L3_INSTR */
	0, /* OMAP4_OCP_WP1 */
	0, /* OMAP4_DMM */
	0, /* OMAP4_EMIF_FW */
	0, /* OMAP4_EMIF1 */
	0, /* OMAP4_EMIF2 */
	0, /* OMAP4_DLL */
	0, /* OMAP4_DDRPHY */
	0, /* OMAP4_STD_EFUSE */
	0, /* OMAP4_CUST_EFUSE */
	1, /* OMAP4_ISS */
	0, /* OMAP4_CCP2 */
	0, /* OMAP4_CSI2_A */
	0, /* OMAP4_CSI2_B */
	0, /* OMAP4_TCTRL */
	0, /* OMAP4_BTE */
	0, /* OMAP4_CBUFF */
	0, /* OMAP4_ISP5 */
	0, /* OMAP4_RSZ */
	0, /* OMAP4_SIMCOP */
	0, /* OMAP4_SIMCOP_DMA */
	0, /* OMAP4_SIMCOP_DCT */
	0, /* OMAP4_SIMCOP_VLCDJ */
	0, /* OMAP4_SIMCOP_ROT */
	0, /* OMAP4_FDIF */
	0, /* OMAP4_DISPC */
	0, /* OMAP4_DSI1 */
	0, /* OMAP4_DSI2 */
	1, /* OMAP4_HDMI */
	0, /* OMAP4_RFBI */
	0, /* OMAP4_BB2D, */
	1, /* OMAP4_GFX */
	1, /* OMAP4_HSI */
	1, /* OMAP4_MMC1 */
	1, /* OMAP4_MMC1_HL */
	1, /* OMAP4_MMC2 */
	1, /* OMAP4_MMC2_HL */
	0, /* OMAP4_UNIPRO1 */
	1, /* OMAP4_FSUSBHOST */
	1, /* OMAP4_HSUSBOTG */
	0, /* OMAP4_USBPHY */
	0, /* OMAP4_HSUSBHOST */
	1, /* OMAP4_USBTLL */
	0, /* OMAP4_P1500 */
	0, /* OMAP4_CRYPTODMA */
	0, /* OMAP4_AES1 */
	0, /* OMAP4_AES2 */
	0, /* OMAP4_SHA2MD5_1 */
	0, /* OMAP4_RNG */
	0, /* OMAP4_DES3DES */
	0, /* OMAP4_PKAEIP29 */
	0, /* OMAP4_L4_PER */
	1, /* OMAP4_TIMER2 */
	1, /* OMAP4_TIMER3 */
	1, /* OMAP4_TIMER4 */
	1, /* OMAP4_TIMER9 */
	1, /* OMAP4_TIMER10 */
	1, /* OMAP4_TIMER11 */
	1, /* OMAP4_GPIO2 */
	1, /* OMAP4_GPIO3 */
	1, /* OMAP4_GPIO4 */
	1, /* OMAP4_GPIO5 */
	1, /* OMAP4_GPIO6 */
	1, /* OMAP4_MCSPI1_HL */
	1, /* OMAP4_MCSPI1 */
	1, /* OMAP4_MCSPI2_HL */
	1, /* OMAP4_MCSPI2 */
	1, /* OMAP4_MCSPI3_HL */
	1, /* OMAP4_MCSPI3 */
	1, /* OMAP4_MCSPI4_HL */
	1, /* OMAP4_MCSPI4 */
	1, /* OMAP4_UART1 */
	1, /* OMAP4_UART2 */
	1, /* OMAP4_UART3 */
	1, /* OMAP4_UART4 */
	1, /* OMAP4_I2C1 */
	1, /* OMAP4_I2C2 */
	1, /* OMAP4_I2C3 */
	1, /* OMAP4_I2C4 */
	1, /* OMAP4_MMC3 */
	1, /* OMAP4_MMC3_HL */
	1, /* OMAP4_MMC4 */
	1, /* OMAP4_MMC4_HL */
	1, /* OMAP4_SLIMBUS2 */
	1, /* OMAP4_MMC5 */
	1, /* OMAP4_MMC5_HL */
	0, /* OMAP4_ELM */
	0, /* OMAP4_HDQ1W */};


static unsigned short mod44xx_init_done = 0;
genlist mod44xx_list;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod44xx_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void mod44xx_init(void)
{
	mod_info mod;
	mod_opp opp;

	if (mod44xx_init_done)
		return;

	genlist_init(&mod44xx_list);

	/* Voltage domain: LDO_WKUP, Power domain: WKUP, Functional clock domain = WKUP */
	mod.id = (int) OMAP4_L4_WKUP_INTERCONNECT;
	mod.name = MOD_L4_WKUP_INTERCONNECT;
	mod.clkdm = CLKDM_WKUP;
	mod.pwrdm = PWRDM_WKUP;
	mod.voltdm = VDD_LDO_WKUP;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_WKUP_L4WKUP_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_WKUP_L4WKUP_CONTEXT */
	mod.clk = (int) OMAP4_WKUP_L4_ICLK2;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 12288;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4470()) {
		opp.name = OPP_50_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_50;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_CONTROL_GEN_WKUP;
	mod.name = MOD_CONTROL_GEN_WKUP;
	mod.clkdm = CLKDM_WKUP;
	mod.pwrdm = PWRDM_WKUP;
	mod.voltdm = VDD_LDO_WKUP;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_CONTROL_GEN_WKUP_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): NULL */
	mod.context = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clk = (int) OMAP4_WKUP_L4_ICLK2;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 12288;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4470()) {
		opp.name = OPP_50_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_50;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_CONTROL_PADCONF_WKUP;
	mod.name = MOD_CONTROL_PADCONF_WKUP;
	mod.clkdm = CLKDM_WKUP;
	mod.pwrdm = PWRDM_WKUP;
	mod.voltdm = VDD_LDO_WKUP;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_CONTROL_PADCONF_WKUP_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): NULL */
	mod.context = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clk = (int) OMAP4_WKUP_L4_ICLK2;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 12288;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4470()) {
		opp.name = OPP_50_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_50;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_WDT2;
	mod.name = MOD_WD_TIMER2;
	mod.clkdm = CLKDM_WKUP;
	mod.pwrdm = PWRDM_WKUP;
	mod.voltdm = VDD_LDO_WKUP;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_WDT2_WDSC */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_WKUP_WDT2_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_WKUP_WDT2_CONTEXT */
	mod.clk = (int) OMAP4_WKUP_32K_GFCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4470()) {
		opp.name = OPP_50_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_50;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_GPIO1;
	mod.name = MOD_GPIO1;
	mod.clkdm = CLKDM_WKUP;
	mod.pwrdm = PWRDM_WKUP;
	mod.voltdm = VDD_LDO_WKUP;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_GPIO1_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_WKUP_GPIO1_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_WKUP_GPIO1_CONTEXT */
	mod.clk = (int) OMAP4_WKUP_32K_GFCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4470()) {
		opp.name = OPP_50_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_50;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_TIMER1;
	mod.name = MOD_TIMER1;
	mod.clkdm = CLKDM_WKUP;
	mod.pwrdm = PWRDM_WKUP;
	mod.voltdm = VDD_LDO_WKUP;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_GPT1_TIOCP_CFG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_WKUP_TIMER1_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_WKUP_TIMER1_CONTEXT */
	mod.clk = (int) OMAP4_GPT1_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4470()) {
		opp.name = OPP_50_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_50;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_SYNCTIMER;
	mod.name = MOD_SYNCTIMER;
	mod.clkdm = CLKDM_WKUP;
	mod.pwrdm = PWRDM_WKUP;
	mod.voltdm = VDD_LDO_WKUP;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_SYNCTIMER_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_WKUP_SYNCTIMER_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_WKUP_SYNCTIMER_CONTEXT */
	mod.clk = (int) OMAP4_FUNC_32K_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4470()) {
		opp.name = OPP_50_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_50;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_SARRAM;
	mod.name = MOD_SARRAM;
	mod.clkdm = CLKDM_WKUP;
	mod.pwrdm = PWRDM_WKUP;
	mod.voltdm = VDD_LDO_WKUP;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_WKUP_SARRAM_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_WKUP_SARRAM_CONTEXT */
	mod.clk = (int) OMAP4_L4_ICLK2;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 49152;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4470()) {
		opp.name = OPP_50_LOW;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 58333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 58333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_50;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_KEYBOARD;
	mod.name = MOD_KEYBOARD;
	mod.clkdm = CLKDM_WKUP;
	mod.pwrdm = PWRDM_WKUP;
	mod.voltdm = VDD_LDO_WKUP;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_KBD_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_WKUP_KEYBOARD_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_WKUP_KEYBOARD_CONTEXT */
	mod.clk = (int) OMAP4_WKUP_32K_GFCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4470()) {
		opp.name = OPP_50_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_50;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	/* HS/EMU device only, not accessible for non-secure world */
	mod.id = (int) OMAP4_TIMER12;
	mod.name = MOD_TIMER12;
	mod.clkdm = CLKDM_WKUP;
	mod.pwrdm = PWRDM_WKUP;
	mod.voltdm = VDD_LDO_WKUP;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_WKUP_TIMER12_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_WKUP_TIMER12_CONTEXT */
	mod.clk = (int) OMAP4_GPT12_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4470()) {
		opp.name = OPP_50_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_50;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_WDT1;
	mod.name = MOD_WD_TIMER1;
	mod.clkdm = CLKDM_WKUP;
	mod.pwrdm = PWRDM_WKUP;
	mod.voltdm = VDD_LDO_WKUP;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_WKUP_WDT1_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_WKUP_WDT1_CONTEXT */
	mod.clk = (int) OMAP4_SECURE_32K_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4470()) {
		opp.name = OPP_50_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_50;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_USIM;
	mod.name = MOD_USIM;
	mod.clkdm = CLKDM_WKUP;
	mod.pwrdm = PWRDM_WKUP;
	mod.voltdm = VDD_LDO_WKUP;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_WKUP_USIM_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_WKUP_USIM_CONTEXT */
	mod.clk = (int) OMAP4_USIM_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 0;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4470()) {
		opp.name = OPP_50_LOW;
		opp.rate = 9142;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 9142;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 9142;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 9142;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 9142;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 9142;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_50;
		opp.rate = 9142;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 9142;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	/* end of HS/EMU device only */
	/* Voltage domain: LDO_WKUP, Power domain: WKUP, Functional clock domain = NONE */
	/* Voltage domain: LDO_WKUP, Power domain: EMU, Functional clock domain = EMU */
	mod.id = (int) OMAP4_DEBUGSS;
	mod.name = MOD_DEBUGSS;
	mod.clkdm = CLKDM_EMU;
	mod.pwrdm = PWRDM_EMU;
	mod.voltdm = VDD_LDO_WKUP;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_EMU_DEBUGSS_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_EMU_DEBUGSS_CONTEXT */
	mod.clk = (int) OMAP4_CORE_DPLL_EMU_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 196608;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4470()) {
		opp.name = OPP_50_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 207407;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 266666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 266666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 266666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 266666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 266666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage domain: VDD_MPU, Power domain: MPU, Functional clock domain = MPU */
	mod.id = (int) OMAP4_MPU;
	mod.name = MOD_MPU;
	mod.clkdm = CLKDM_MPU;
	mod.pwrdm = PWRDM_MPU;
	mod.voltdm = VDD_MPU;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_MPU_MPU_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_MPU_MPU_CONTEXT */
	mod.clk = (int) OMAP4_MPU_DPLL_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 196608;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4470()) {
		opp.name = OPP_50;
		opp.rate = 396800;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 800000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_TURBO;
		opp.rate = 1100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITRO;
		opp.rate = 1300000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITROSB;
		opp.rate = 1500000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 350000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 700000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_TURBO;
		opp.rate = 920000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITRO;
		opp.rate = 1200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITROSB;
		opp.rate = 1500000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4430 */
		opp.name = OPP_50;
		opp.rate = 300000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 600000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_TURBO;
		opp.rate = 800000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITRO;
		opp.rate = 1008000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITROSB;
		opp.rate = 1200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage domain: VDD_MPU, Power domain: ALWON_MPU, Functional clock domain = NONE */
	/* Voltage domain: VDD_IVA, Power domain: ABE, Functional clock domain = ABE */
	mod.id = (int) OMAP4_L4_ABE;
	mod.name = MOD_L4_ABE_INTERCONNECT;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_IVA;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM1_ABE_L4ABE_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clk = (int) OMAP4_ABE_ICLK2;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 49152;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_50;
	opp.rate = 49152;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (!cpu_is_omap4430()) {
		opp.name = OPP_TURBO;
		opp.rate = 98304;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITRO;
		opp.rate = 98304;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITROSB;
		opp.rate = 98304;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_AESS;
	mod.name = MOD_AESS;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_IVA;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_AESS_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM1_ABE_AESS_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_ABE_AESS_CONTEXT */
	mod.clk = (int) OMAP4_AESS_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_50;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100;
	opp.rate = 196608;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (!cpu_is_omap4430()) {
		opp.name = OPP_TURBO;
		opp.rate = 196608;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITRO;
		opp.rate = 196608;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITROSB;
		opp.rate = 196608;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_DUAL;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_MCPDM;
	mod.name = MOD_MCPDM;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_IVA;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_MCPDM_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM1_ABE_PDM_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_ABE_PDM_CONTEXT */
	mod.clk = (int) OMAP4_PAD_CLKS;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_50;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (!cpu_is_omap4430()) {
		opp.name = OPP_TURBO;
		opp.rate = 19200;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITRO;
		opp.rate = 19200;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITROSB;
		opp.rate = 19200;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_DMIC;
	mod.name = MOD_DMIC;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_IVA;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_DMIC_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM1_ABE_DMIC_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_ABE_DMIC_CONTEXT */
	mod.clk = (int) OMAP4_DMIC_ABE_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_50;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (!cpu_is_omap4430()) {
		opp.name = OPP_TURBO;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITRO;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITROSB;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_MCASP;
	mod.name = MOD_MCASP;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_IVA;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_MCASP_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM1_ABE_MCASP_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_ABE_MCASP_CONTEXT */
	mod.clk = (int) OMAP4_MCASP1_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_50;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (!cpu_is_omap4430()) {
		opp.name = OPP_TURBO;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITRO;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITROSB;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_MCBSP1;
	mod.name = MOD_MCBSP1;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_IVA;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_MCBSP1_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM1_ABE_MCBSP1_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_ABE_MCBSP1_CONTEXT */
	mod.clk = (int) OMAP4_MCBSP1_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_50;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (!cpu_is_omap4430()) {
		opp.name = OPP_TURBO;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITRO;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITROSB;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_MCBSP2;
	mod.name = MOD_MCBSP2;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_IVA;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_MCBSP2_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM1_ABE_MCBSP2_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_ABE_MCBSP2_CONTEXT */
	mod.clk = (int) OMAP4_MCBSP2_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_50;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (!cpu_is_omap4430()) {
		opp.name = OPP_TURBO;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITRO;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITROSB;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_MCBSP3;
	mod.name = MOD_MCBSP3;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_IVA;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_MCBSP3_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM1_ABE_MCBSP3_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_ABE_MCBSP3_CONTEXT */
	mod.clk = (int) OMAP4_MCBSP3_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_50;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (!cpu_is_omap4430()) {
		opp.name = OPP_TURBO;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITRO;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITROSB;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_SLIMBUS1;
	mod.name = MOD_SLIMBUS1;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_IVA;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_SLIMBUS1_CMP_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM1_ABE_SLIMBUS_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_ABE_SLIMBUS_CONTEXT */
	mod.clk = (int) OMAP4_SLIMBUS_UCLKS;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_50;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (!cpu_is_omap4430()) {
		opp.name = OPP_TURBO;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITRO;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITROSB;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_TIMER5;
	mod.name = MOD_TIMER5;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_IVA;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_GPT5_TIOCP_CFG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM1_ABE_TIMER5_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_ABE_TIMER5_CONTEXT */
	mod.clk = (int) OMAP4_ABE_GPT5_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 38400;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_50;
	opp.rate = 38400;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100;
	opp.rate = 38400;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (!cpu_is_omap4430()) {
		opp.name = OPP_TURBO;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITRO;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITROSB;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_TIMER6;
	mod.name = MOD_TIMER6;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_IVA;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_GPT6_TIOCP_CFG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM1_ABE_TIMER6_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_ABE_TIMER6_CONTEXT */
	mod.clk = (int) OMAP4_ABE_GPT6_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 38400;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_50;
	opp.rate = 38400;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100;
	opp.rate = 38400;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (!cpu_is_omap4430()) {
		opp.name = OPP_TURBO;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITRO;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITROSB;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_TIMER7;
	mod.name = MOD_TIMER7;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_IVA;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_GPT7_TIOCP_CFG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM1_ABE_TIMER7_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_ABE_TIMER7_CONTEXT */
	mod.clk = (int) OMAP4_ABE_GPT7_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 38400;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_50;
	opp.rate = 38400;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100;
	opp.rate = 38400;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (!cpu_is_omap4430()) {
		opp.name = OPP_TURBO;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITRO;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITROSB;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_TIMER8;
	mod.name = MOD_TIMER8;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_IVA;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_GPT8_TIOCP_CFG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM1_ABE_TIMER8_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_ABE_TIMER8_CONTEXT */
	mod.clk = (int) OMAP4_ABE_GPT8_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 38400;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_50;
	opp.rate = 38400;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100;
	opp.rate = 38400;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (!cpu_is_omap4430()) {
		opp.name = OPP_TURBO;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITRO;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITROSB;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_WDT3;
	mod.name = MOD_WDT3;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_IVA;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_WDT3_WDSC */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM1_ABE_WDT3_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_ABE_WDT3_CONTEXT */
	mod.clk = (int) OMAP4_ABE_ALWON_32K_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_50;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (!cpu_is_omap4430()) {
		opp.name = OPP_TURBO;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITRO;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITROSB;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage domain: VDD_IVA, Power domain: IVAHD, Functional clock domain = IVAHD */
	mod.id = (int) OMAP4_IVAHD;
	mod.name = MOD_IVAHD;
	mod.clkdm = CLKDM_IVA_HD;
	mod.pwrdm = PWRDM_IVA_HD;
	mod.voltdm = VDD_IVA;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_IVAHD_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT */
	mod.clk = (int) OMAP4_IVAHD_ROOT_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_50;
	opp.rate = 133028;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100;
	opp.rate = 266057;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (!cpu_is_omap4430()) {
		opp.name = OPP_TURBO;
		opp.rate = 330700;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITRO;
		opp.rate = 430100;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITROSB;
		opp.rate = 500000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_DUAL;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage domain: VDD_IVA, Power domain: DSP, Functional clock domain = DSP */
	mod.id = (int) OMAP4_DSP;
	mod.name = MOD_DSP;
	mod.clkdm = CLKDM_DSP;
	mod.pwrdm = PWRDM_DSP;
	mod.voltdm = VDD_IVA;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_DSP_SYSC_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_DSP_DSP_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_DSP_DSP_CONTEXT */
	mod.clk = (int) OMAP4_DSP_ROOT_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_50;
	opp.rate = 232800;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100;
	opp.rate = 465600;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (!cpu_is_omap4430()) {
		opp.name = OPP_TURBO;
		opp.rate = 496000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITRO;
		opp.rate = 430100;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITROSB;
		opp.rate = 500000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_MMU_DSP;
	mod.name = MOD_MMU_DSP;
	mod.clkdm = CLKDM_DSP;
	mod.pwrdm = PWRDM_DSP;
	mod.voltdm = VDD_IVA;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_MMU_DSP_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_DSP_DSP_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_DSP_DSP_CONTEXT */
	mod.clk = (int) OMAP4_DSP_ROOT_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_50;
	opp.rate = 232800;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100;
	opp.rate = 465600;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (!cpu_is_omap4430()) {
		opp.name = OPP_TURBO;
		opp.rate = 496000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITRO;
		opp.rate = 430100;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITROSB;
		opp.rate = 500000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_DSP_WUGEN;
	mod.name = MOD_DSP_WUGEN;
	mod.clkdm = CLKDM_DSP;
	mod.pwrdm = PWRDM_ALWON_IVA;
	mod.voltdm = VDD_IVA;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_DSP_WUGEN_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_DSP_DSP_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_DSP_DSP_CONTEXT */
	mod.clk = (int) OMAP4_DSP_ROOT_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_50;
	opp.rate = 232800;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_100;
	opp.rate = 465600;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (!cpu_is_omap4430()) {
		opp.name = OPP_TURBO;
		opp.rate = 496000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITRO;
		opp.rate = 430100;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NITROSB;
		opp.rate = 500000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage domain: VDD_CORE, Power domain: ALWON_CORE, Functional clock domain = AO_L4 */
	mod.id = (int) OMAP4_SMARTREFLEX_CORE;
	mod.name = MOD_SMARTREFLEX_CORE;
	mod.clkdm = CLKDM_L4_ALWON_CORE;
	mod.pwrdm = PWRDM_ALWON_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_ERRCONFIG_CORE */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_ALWON_SR_CORE_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_ALWON_SR_CORE_CONTEXT */
	mod.clk = (int) OMAP4_SR_CORE_SYS_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 12288;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_SMARTREFLEX_MPU;
	mod.name = MOD_SMARTREFLEX_MPU;
	mod.clkdm = CLKDM_L4_ALWON_CORE;
	mod.pwrdm = PWRDM_ALWON_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_ERRCONFIG_MPU */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_ALWON_SR_MPU_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_ALWON_SR_MPU_CONTEXT */
	mod.clk = (int) OMAP4_SR_MPU_SYS_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 12288;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_SMARTREFLEX_IVA;
	mod.name = MOD_SMARTREFLEX_IVA;
	mod.clkdm = CLKDM_L4_ALWON_CORE;
	mod.pwrdm = PWRDM_ALWON_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_ERRCONFIG_IVA */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_ALWON_SR_IVA_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_ALWON_SR_IVA_CONTEXT */
	mod.clk = (int) OMAP4_SR_IVA_SYS_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 12288;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = L4CFG */
	mod.id = (int) OMAP4_L4_CFG;
	mod.name = MOD_L4_CFG_INTERCONNECT;
	mod.clkdm = CLKDM_L4_CFG;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4CFG_L4_CFG_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4CFG_L4_CFG_CONTEXT */
	mod.clk = (int) OMAP4_CFG_L4_ICLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 49152;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 58333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 58333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_CONTROL_GEN_CORE;
	mod.name = MOD_CONTROL_GEN_CORE;
	mod.clkdm = CLKDM_L4_CFG;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_CONTROL_GEN_CORE_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): NULL */
	mod.context = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clk = (int) OMAP4_CFG_L4_ICLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 49152;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 58333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 58333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_CONTROL_PADCONF_CORE;
	mod.name = MOD_CONTROL_PADCONF_CORE;
	mod.clkdm = CLKDM_L4_CFG;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_CONTROL_PADCONF_CORE_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): NULL */
	mod.context = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clk = (int) OMAP4_CFG_L4_ICLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 49152;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 58333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 58333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_SPINLOCK;
	mod.name = MOD_SPINLOCK;
	mod.clkdm = CLKDM_L4_CFG;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_SPINLOCK_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4CFG_HW_SEM_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4CFG_HW_SEM_CONTEXT */
	mod.clk = (int) OMAP4_CFG_L4_ICLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 49152;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 58333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 58333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_SYSTEM_MAILBOX;
	mod.name = MOD_MAILBOX;
	mod.clkdm = CLKDM_L4_CFG;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_SYSTEM_MBX_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4CFG_MAILBOX_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4CFG_MAILBOX_CONTEXT */
	mod.clk = (int) OMAP4_CFG_L4_ICLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 49152;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 58333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 58333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	/* TODO: CHECK IF REGISTER ACCESSIBLE FROM MPU	mod44xx_init_info(OMAP4_IVAHD_MAILBOX, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4CFG, OMAP4_PD_CORE, OMAP4_VDD_CORE, OMAP4430_IVAHD_MBX_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4CFG_MAILBOX_CLKCTRL, (unsigned int *) OMAP4430_RM_L4CFG_MAILBOX_CONTEXT, OMAP4_UNDEF_CLK, 0.0); */
	mod.id = (int) OMAP4_SAR_ROM;
	mod.name = MOD_SARROM;
	mod.clkdm = CLKDM_L4_CFG;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4CFG_SAR_ROM_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4CFG_SAR_ROM_CONTEXT */
	mod.clk = (int) OMAP4_CFG_L4_ICLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 49152;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 58333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 58333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = C2C */
	mod.id = (int) OMAP4_C2C;
	mod.name = MOD_C2C;
	mod.clkdm = CLKDM_C2C;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_C2C_C2C_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_C2C_C2C_CONTEXT */
	mod.clk = (int) OMAP4_C2C_L3X2_ICLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_C2C_FW;
	mod.name = MOD_C2C_FW;
	mod.clkdm = CLKDM_C2C;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_C2C_C2C_FW_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_C2C_C2C_FW_CONTEXT */
	mod.clk = (int) OMAP4_C2C_L3_ICLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_ICR_MDM;
	mod.name = MOD_MODEM_ICR;
	mod.clkdm = CLKDM_C2C;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_ICR_MDM_SYS_CONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): NULL */
	mod.context = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clk = (int) OMAP4_C2C_L4_ICLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 49152;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 58333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 58333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_ICR_MPU;
	mod.name = MOD_MPU_ICR;
	mod.clkdm = CLKDM_C2C;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_ICR_MPU_SYS_CONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): NULL */
	mod.context = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clk = (int) OMAP4_C2C_L4_ICLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 49152;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 58333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 58333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = DMA */
	mod.id = (int) OMAP4_SDMA;
	mod.name = MOD_SDMA;
	mod.clkdm = CLKDM_DMA;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_DMA4_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_SDMA_SDMA_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_SDMA_SDMA_CONTEXT */
	mod.clk = (int) OMAP4_DMA_L3_ICLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_DUAL | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = MPU_M3 */
	mod.id = (int) OMAP4_MPU_M3;
	mod.name = MOD_MPU_M3;
	mod.clkdm = CLKDM_MPU_M3;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_MPU_M3_MPU_M3_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_MPU_M3_MPU_M3_CONTEXT */
	mod.clk = (int) OMAP4_MPU_M3_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 196608;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (!cpu_is_omap4470()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_50_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 466666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	/* TODO: FURTHER CHECK 	mod44xx_init_info(OMAP4_MPU_M3_WUGEN, MOD_INTERFACE_DUAL, 0, OMAP4_CD_MPU_M3, OMAP4_PD_ALWON_CORE, OMAP4_VDD_CORE, OMAP4430_MPU_M3_WUGEN_SYSCONFIG, (unsigned int *) OMAP4430_CM_MPU_M3_MPU_M3_CLKCTRL, (unsigned int *) OMAP4430_RM_MPU_M3_MPU_M3_CONTEXT, OMAP4_UNDEF_CLK, (double[OPP44XX_ID_MAX]) {0.0); */
	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = NONE */
	/* TODO: FURTHER CHECK WHEN MODULE IS ACCESSIBLE	mod44xx_init_info(OMAP4_MMU_MPU_M3, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_NONE, OMAP4_PD_CORE, OMAP4_VDD_CORE, OMAP4430_MMU_MPU_M3_SYSCONFIG, NULL, NULL, OMAP4_UNDEF_CLK, (double[OPP44XX_ID_MAX]) {0.0); */
	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = L3_1 */
	mod.id = (int) OMAP4_L3_1;
	mod.name = MOD_L3_MAIN1_INTERCONNECT;
	mod.clkdm = CLKDM_L3_MAIN1;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L3_1_L3_1_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L3_1_L3_1_CONTEXT */
	mod.clk = (int) OMAP4_L3_ICLK1;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = L3_2 */
	mod.id = (int) OMAP4_L3_2;
	mod.name = MOD_L3_MAIN2_INTERCONNECT;
	mod.clkdm = CLKDM_L3_MAIN2;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L3_2_L3_2_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L3_2_L3_2_CONTEXT */
	mod.clk = (int) OMAP4_L3_ICLK2;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_GPMC;
	mod.name = MOD_GPMC;
	mod.clkdm = CLKDM_L3_MAIN2;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_GPMC_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L3_2_GPMC_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L3_2_GPMC_CONTEXT */
	mod.clk = (int) OMAP4_L3_ICLK2;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_OCMC_RAM;
	mod.name = MOD_OCMC_RAM;
	mod.clkdm = CLKDM_L3_MAIN2;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L3_2_OCMC_RAM_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L3_2_OCMC_RAM_CONTEXT */
	mod.clk = (int) OMAP4_L3_ICLK2;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = L3_INSTR */
	mod.id = (int) OMAP4_L3_3;
	mod.name = MOD_L3_MAIN3_INTERCONNECT;
	mod.clkdm = CLKDM_L3_INSTR;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L3INSTR_L3_3_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L3INSTR_L3_3_CONTEXT */
	mod.clk = (int) OMAP4_L3_INSTR_GICLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_L3_INSTR;
	mod.name = MOD_L3_INSTR_INTERCONNECT;
	mod.clkdm = CLKDM_L3_INSTR;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L3INSTR_L3_INSTR_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L3INSTR_L3_INSTR_CONTEXT */
	mod.clk = (int) OMAP4_L3_INSTR_GICLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_OCP_WP1;
	mod.name = MOD_OCP_WP1;
	mod.clkdm = CLKDM_L3_INSTR;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L3INSTR_OCP_WP1_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L3INSTR_OCP_WP1_CONTEXT */
	mod.clk = (int) OMAP4_L3_INSTR_GICLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = EMIF */
	mod.id = (int) OMAP4_DMM;
	mod.name = MOD_DMM;
	mod.clkdm = CLKDM_EMIF;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_DMM_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_MEMIF_DMM_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_MEMIF_DMM_CONTEXT */
	mod.clk = (int) OMAP4_EMIF_L3_ICLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_EMIF_FW;
	mod.name = MOD_EMIF_FW;
	mod.clkdm = CLKDM_EMIF;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_MEMIF_EMIF_FW_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_MEMIF_EMIF_FW_CONTEXT */
	mod.clk = (int) OMAP4_EMIF_L3_ICLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_EMIF1;
	mod.name = MOD_EMIF1;
	mod.clkdm = CLKDM_EMIF;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_MEMIF_EMIF_1_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_MEMIF_EMIF_1_CONTEXT */
	mod.clk = (int) OMAP4_EMIF_L3_ICLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_EMIF2;
	mod.name = MOD_EMIF2;
	mod.clkdm = CLKDM_EMIF;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_MEMIF_EMIF_2_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_MEMIF_EMIF_2_CONTEXT */
	mod.clk = (int) OMAP4_EMIF_L3_ICLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_DDRPHY;
	mod.name = MOD_DDRPHY;
	mod.clkdm = CLKDM_EMIF;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): NULL */
	mod.context = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clk = (int) OMAP4_PHY_ROOT_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 196608;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430() && (cpu_revision_get() < REV_ES2_1)) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (!cpu_is_omap4470()) {
		opp.name = OPP_50;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 800000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 466000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 800000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 931200;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 465600;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_DLL;
	mod.name = MOD_DLL;
	mod.clkdm = CLKDM_EMIF;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_MEMIF_DLL_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_MEMIF_DLL_CONTEXT */
	mod.clk = (int) OMAP4_DLL_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage domain: VDD_CORE, Power domain: STD_EFUSE, Functional clock domain = STD_EFUSE */

	/* Voltage domain: VDD_CORE, Power domain: CUST_EFUSE, Functional clock domain = CUST_EFUSE */
	/* Voltage domain: VDD_CORE, Power domain: ALWON_CORE, Functional clock domain = NONE */
	/* Voltage domain: VDD_CORE, Power domain: ALWON_CORE, Functional clock domain = NONE */
	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = NONE */
	/* Voltage domain: VDD_CORE, Power domain: CAM, Functional clock domain = CAM */
	mod.id = (int) OMAP4_ISS;
	mod.name = MOD_ISS;
	mod.clkdm = CLKDM_CAM;
	mod.pwrdm = PWRDM_CAM;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_ISS_HL_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT */
	mod.clk = (int) OMAP4_ISS_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 196608;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 466666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_DUAL | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_CCP2;
	mod.name = MOD_CCP2;
	mod.clkdm = CLKDM_CAM;
	mod.pwrdm = PWRDM_CAM;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_CCP2_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT */
	mod.clk = (int) OMAP4_ISS_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 196608;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 466666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_MASTER;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_CSI2_A;
	mod.name = MOD_CSI2_A;
	mod.clkdm = CLKDM_CAM;
	mod.pwrdm = PWRDM_CAM;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_CSI2_A_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT */
	mod.clk = (int) OMAP4_ISS_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 196608;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 466666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_MASTER;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_CSI2_B;
	mod.name = MOD_CSI2_B;
	mod.clkdm = CLKDM_CAM;
	mod.pwrdm = PWRDM_CAM;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_CSI2_B_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT */
	mod.clk = (int) OMAP4_ISS_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 196608;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 466666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_MASTER;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_TCTRL;
	mod.name = MOD_TCTRL;
	mod.clkdm = CLKDM_CAM;
	mod.pwrdm = PWRDM_CAM;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_TCTRL_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT */
	mod.clk = (int) OMAP4_ISS_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 196608;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 466666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_BTE;
	mod.name = MOD_BTE;
	mod.clkdm = CLKDM_CAM;
	mod.pwrdm = PWRDM_CAM;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_BTE_HL_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT */
	mod.clk = (int) OMAP4_ISS_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 196608;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 466666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_CBUFF;
	mod.name = MOD_CBUFF;
	mod.clkdm = CLKDM_CAM;
	mod.pwrdm = PWRDM_CAM;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_CBUFF_HL_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT */
	mod.clk = (int) OMAP4_ISS_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 196608;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 466666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_ISP5;
	mod.name = MOD_ISP5;
	mod.clkdm = CLKDM_CAM;
	mod.pwrdm = PWRDM_CAM;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_ISP5_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT */
	mod.clk = (int) OMAP4_ISS_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 196608;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 466666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_MASTER;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_RSZ;
	mod.name = MOD_RSZ;
	mod.clkdm = CLKDM_CAM;
	mod.pwrdm = PWRDM_CAM;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_RSZ_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT */
	mod.clk = (int) OMAP4_ISS_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 196608;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 466666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_SIMCOP;
	mod.name = MOD_SIMCOP;
	mod.clkdm = CLKDM_CAM;
	mod.pwrdm = PWRDM_CAM;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_SIMCOP_HL_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT */
	mod.clk = (int) OMAP4_ISS_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 196608;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 466666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_MASTER;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_SIMCOP_DMA;
	mod.name = MOD_SIMCOP_DMA;
	mod.clkdm = CLKDM_CAM;
	mod.pwrdm = PWRDM_CAM;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_SIMCOP_DMA_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT */
	mod.clk = (int) OMAP4_ISS_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 196608;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 466666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_MASTER;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_SIMCOP_DCT;
	mod.name = MOD_SIMCOP_DCT;
	mod.clkdm = CLKDM_CAM;
	mod.pwrdm = PWRDM_CAM;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_SIMCOP_DCT_CFG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT */
	mod.clk = (int) OMAP4_ISS_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 196608;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 466666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_SIMCOP_VLCDJ;
	mod.name = MOD_SIMCOP_VLCDJ;
	mod.clkdm = CLKDM_CAM;
	mod.pwrdm = PWRDM_CAM;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_SIMCOP_VLCDJ_CTRL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT */
	mod.clk = (int) OMAP4_ISS_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 196608;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 466666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_SIMCOP_ROT;
	mod.name = MOD_SIMCOP_ROT;
	mod.clkdm = CLKDM_CAM;
	mod.pwrdm = PWRDM_CAM;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_SIMCOP_ROT_CFG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT */
	mod.clk = (int) OMAP4_ISS_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 196608;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 466666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_FDIF;
	mod.name = MOD_FDIF;
	mod.clkdm = CLKDM_CAM;
	mod.pwrdm = PWRDM_CAM;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_FDIF_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_CAM_FDIF_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_CAM_FDIF_CONTEXT */
	mod.clk = (int) OMAP4_FDIF_FCLK;
	genlist_init(&(mod.mod_opp_list));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 64000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 128000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 64000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 128000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 128000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 64000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 128000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 128000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 128000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 128000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 128000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_DUAL;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage domain: VDD_CORE, Power domain: DSS, Functional clock domain = DSS */
	mod.id = (int) OMAP4_DISPC;
	mod.name = MOD_DISPC;
	mod.clkdm = CLKDM_DSS;
	mod.pwrdm = PWRDM_DSS;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_DISPC_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_DSS_DSS_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_DSS_DSS_CONTEXT */
	mod.clk = (int) OMAP4_DSS_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 85333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_DUAL;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_DSI1;
	mod.name = MOD_DSI1;
	mod.clkdm = CLKDM_DSS;
	mod.pwrdm = PWRDM_DSS;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_DSI1_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_DSS_DSS_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_DSS_DSS_CONTEXT */
	mod.clk = (int) OMAP4_DSS_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 85333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_DSI2;
	mod.name = MOD_DSI2;
	mod.clkdm = CLKDM_DSS;
	mod.pwrdm = PWRDM_DSS;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_DSI2_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_DSS_DSS_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_DSS_DSS_CONTEXT */
	mod.clk = (int) OMAP4_DSS_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 85333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 170666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_HDMI;
	mod.name = MOD_HDMI;
	mod.clkdm = CLKDM_DSS;
	mod.pwrdm = PWRDM_DSS;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_HDMI_WP_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_DSS_DSS_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_DSS_DSS_CONTEXT */
	mod.clk = (int) OMAP4_HDMI_PHY_48M_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_RFBI;
	mod.name = MOD_RFBI;
	mod.clkdm = CLKDM_DSS;
	mod.pwrdm = PWRDM_DSS;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_RFBI_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_DSS_DSS_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_DSS_DSS_CONTEXT */
	mod.clk = (int) OMAP4_UNDEF_CLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 0;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 0;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 0;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 0;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 0;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 0;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 0;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 0;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 0;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 0;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 0;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	if (cpu_is_omap4470()) {
		mod.id = (int) OMAP4_BB2D;
		mod.name = MOD_BB2D;
		mod.clkdm = CLKDM_DSS;
		mod.pwrdm = PWRDM_DSS;
		mod.voltdm = VDD_CORE;
		mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
		mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_DSS_BB2D_CLKCTRL */
		mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_DSS_BB2D_CONTEXT */
		mod.clk = (int) OMAP4_BB2D_FCLK;
		genlist_init(&(mod.mod_opp_list));
		opp.name = OPP_DPLL_CASC;
		opp.rate = 0;
		opp.name = OPP_50_LOW;
		opp.rate = 192000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 192000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 307200;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 384000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 384000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 307200;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		mod.properties = MOD_INTERFACE_NONE;
		genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));
	}

	/* Voltage domain: VDD_CORE, Power domain: GFX, Functional clock domain = GFX */
	mod.id = (int) OMAP4_GFX;
	mod.name = MOD_SGX;
	mod.clkdm = CLKDM_SGX;
	mod.pwrdm = PWRDM_SGX;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_GFX_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_GFX_GFX_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_GFX_GFX_CONTEXT */
	mod.clk = (int) OMAP4_GFX_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 153600;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 307200;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 153600;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 307200;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 384000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 153600;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 192000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 307200;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 384000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 384000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 307200;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_DUAL | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage domain: VDD_CORE, Power domain: L3_INIT, Functional clock domain = L3_INIT */
	mod.id = (int) OMAP4_MMC1;
	mod.name = MOD_MMC1;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_HSMMC1_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L3INIT_MMC1_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L3INIT_MMC1_CONTEXT */
	mod.clk = (int) OMAP4_MMC1_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 49152;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_DUAL | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_MMC1_HL;
	mod.name = MOD_MMC1_HL;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_HSMMC1_HL_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L3INIT_MMC1_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L3INIT_MMC1_CONTEXT */
	mod.clk = (int) OMAP4_MMC1_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 49152;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_DUAL | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_MMC2;
	mod.name = MOD_MMC2;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_HSMMC2_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L3INIT_MMC2_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L3INIT_MMC2_CONTEXT */
	mod.clk = (int) OMAP4_MMC2_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 49152;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_DUAL | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_MMC2_HL;
	mod.name = MOD_MMC2_HL;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_HSMMC2_HL_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L3INIT_MMC2_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L3INIT_MMC2_CONTEXT */
	mod.clk = (int) OMAP4_MMC2_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 49152;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_DUAL | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_HSI;
	mod.name = MOD_HSI;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_HSI_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L3INIT_HSI_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L3INIT_HSI_CONTEXT */
	mod.clk = (int) OMAP4_HSI_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 49152;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_DUAL | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	if (cpu_is_omap4430() && (cpu_revision_get() == REV_ES1_0)) {
		mod.id = (int) OMAP4_UNIPRO1;
		mod.name = MOD_UNIPRO1;
		mod.clkdm = CLKDM_L3_INIT;
		mod.pwrdm = PWRDM_L3_INIT;
		mod.voltdm = VDD_CORE;
		mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_UNIPRO1_SYSCONFIG */
		mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L3INIT_UNIPRO1_CLKCTRL */
		mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L3INIT_UNIPRO1_CONTEXT */
		mod.clk = (int) OMAP4_UNIPRO1_PHY_FCLK;
		genlist_init(&(mod.mod_opp_list));
		opp.name = OPP_50;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		mod.properties = MOD_INTERFACE_DUAL;
		genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));
	}

	mod.id = (int) OMAP4_HSUSBHOST;
	mod.name = MOD_HSUSBHOST;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_UHH_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L3INIT_USB_HOST_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L3INIT_USB_HOST_CONTEXT */
	mod.clk = (int) OMAP4_INIT_48MC_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_DUAL;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_HSUSBOTG;
	mod.name = MOD_HSUSBOTG;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_HSUSBOTG_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L3INIT_USB_OTG_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L3INIT_USB_OTG_CONTEXT */
	mod.clk = (int) OMAP4_OTG_60M_FCLK;
	genlist_init(&(mod.mod_opp_list));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 60000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 60000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 60000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 60000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 60000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 60000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 60000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 60000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 60000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 60000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 60000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_DUAL | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_USBTLL;
	mod.name = MOD_USBTLL;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_USBTLL_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L3INIT_USB_TLL_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L3INIT_USB_TLL_CONTEXT */
	mod.clk = (int) OMAP4_INIT_60M_FCLK;
	genlist_init(&(mod.mod_opp_list));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 60000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 60000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 60000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 60000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 60000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 60000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 60000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 60000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 60000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 60000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 60000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_P1500;
	mod.name = MOD_P1500;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L3INIT_P1500_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L3INIT_P1500_CONTEXT */
	mod.clk = (int) OMAP4_INIT_L3_ICLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	if (!cpu_is_omap4470()) {
		mod.id = (int) OMAP4_FSUSBHOST;
		mod.name = MOD_FSUSBHOST;
		mod.clkdm = CLKDM_L3_INIT;
		mod.pwrdm = PWRDM_L3_INIT;
		mod.voltdm = VDD_CORE;
		mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_FSUSBHOST_HCOCPSYS */
		mod.clkctrl = NULL; /* FIXME (must create reg struct first): OMAP4430_CM_L3INIT_USB_HOST_FS_CLKCTRL */
		mod.context = NULL; /* FIXME (must create reg struct first): OMAP4430_RM_L3INIT_USB_HOST_FS_CONTEXT */
		mod.clk = (int) OMAP4_INIT_48MC_FCLK;
		genlist_init(&(mod.mod_opp_list));
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		if (cpu_is_omap4460()) {
			opp.name = OPP_119;
			opp.rate = 48000;
			genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		}
		mod.properties = MOD_INTERFACE_DUAL | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
		genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));
	}

	mod.id = (int) OMAP4_USBPHY;
	mod.name = MOD_USBPHY;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L3INIT_USBPHYOCP2SCP_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L3INIT_USBPHYOCP2SCP_CONTEXT */
	mod.clk = (int) OMAP4_INIT_48M_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage domain: VDD_CORE, Power domain: L3_INIT, Functional clock domain = NONE */
	/* Voltage domain: VDD_CORE, Power domain: L4_PER, Functional clock domain = L4_SEC */
	/* HS/EMU device only, not accessible for non-secure world */
	mod.id = (int) OMAP4_CRYPTODMA;
	mod.name = MOD_DMA_CRYPTO;
	mod.clkdm = CLKDM_L4_SEC;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4SEC_CRYPTODMA_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4SEC_CRYPTODMA_CONTEXT */
	mod.clk = (int) OMAP4_L3_SECURE_GICLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_AES1;
	mod.name = MOD_AES1;
	mod.clkdm = CLKDM_L4_SEC;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4SEC_AES1_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4SEC_AES1_CONTEXT */
	mod.clk = (int) OMAP4_L3_SECURE_GICLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_AES2;
	mod.name = MOD_AES2;
	mod.clkdm = CLKDM_L4_SEC;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4SEC_AES2_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4SEC_AES2_CONTEXT */
	mod.clk = (int) OMAP4_L3_SECURE_GICLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_SHA2MD5_1;
	mod.name = MOD_SHA2MD5;
	mod.clkdm = CLKDM_L4_SEC;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4SEC_SHA2MD51_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4SEC_SHA2MD51_CONTEXT */
	mod.clk = (int) OMAP4_L3_SECURE_GICLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 233333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_RNG;
	mod.name = MOD_RNG;
	mod.clkdm = CLKDM_L4_SEC;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4SEC_RNG_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4SEC_RNG_CONTEXT */
	mod.clk = (int) OMAP4_L4_SECURE_GICLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 49152;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 58333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 58333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_DES3DES;
	mod.name = MOD_DES3DES;
	mod.clkdm = CLKDM_L4_SEC;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4SEC_DES3DES_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4SEC_DES3DES_CONTEXT */
	mod.clk = (int) OMAP4_L4_SECURE_GICLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 49152;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 58333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 58333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_PKAEIP29;
	mod.name = MOD_PKA;
	mod.clkdm = CLKDM_L4_SEC;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4SEC_PKAEIP29_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4SEC_PKAEIP29_CONTEXT */
	mod.clk = (int) OMAP4_L4_SECURE_GICLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 49152;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 58333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 58333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	/* end of HS/EMU device only */
	/* Voltage domain: VDD_CORE, Power domain: L4_PER, Functional clock domain = L4_PER */
	mod.id = (int) OMAP4_TIMER10;
	mod.name = MOD_TIMER10;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_GPT10_TIOCP_CFG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_DMTIMER10_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_DMTIMER10_CONTEXT */
	mod.clk = (int) OMAP4_GPT10_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 38400;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_TIMER11;
	mod.name = MOD_TIMER11;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_GPT11_TIOCP_CFG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_DMTIMER11_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_DMTIMER11_CONTEXT */
	mod.clk = (int) OMAP4_GPT11_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 38400;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_TIMER2;
	mod.name = MOD_TIMER2;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_GPT2_TIOCP_CFG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_DMTIMER2_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_DMTIMER2_CONTEXT */
	mod.clk = (int) OMAP4_GPT2_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 38400;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_TIMER3;
	mod.name = MOD_TIMER3;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_GPT3_TIOCP_CFG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_DMTIMER3_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_DMTIMER3_CONTEXT */
	mod.clk = (int) OMAP4_GPT3_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 38400;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_TIMER4;
	mod.name = MOD_TIMER4;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_GPT4_TIOCP_CFG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_DMTIMER4_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_DMTIMER4_CONTEXT */
	mod.clk = (int) OMAP4_GPT4_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 38400;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_TIMER9;
	mod.name = MOD_TIMER9;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_GPT9_TIOCP_CFG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_DMTIMER9_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_DMTIMER9_CONTEXT */
	mod.clk = (int) OMAP4_GPT9_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 38400;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 38400;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_ELM;
	mod.name = MOD_ELM;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_ELM_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_ELM_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_ELM_CONTEXT */
	mod.clk = (int) OMAP4_PER_L4_ICLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 49152;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 58333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 58333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_GPIO2;
	mod.name = MOD_GPIO2;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_GPIO2_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_GPIO2_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_GPIO2_CONTEXT */
	mod.clk = (int) OMAP4_PER_32K_GFCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_GPIO3;
	mod.name = MOD_GPIO3;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_GPIO3_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_GPIO3_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_GPIO3_CONTEXT */
	mod.clk = (int) OMAP4_PER_32K_GFCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_GPIO4;
	mod.name = MOD_GPIO4;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_GPIO4_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_GPIO4_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_GPIO4_CONTEXT */
	mod.clk = (int) OMAP4_PER_32K_GFCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_GPIO5;
	mod.name = MOD_GPIO5;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_GPIO5_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_GPIO5_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_GPIO5_CONTEXT */
	mod.clk = (int) OMAP4_PER_32K_GFCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_GPIO6;
	mod.name = MOD_GPIO6;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_GPIO6_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_GPIO6_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_GPIO6_CONTEXT */
	mod.clk = (int) OMAP4_PER_32K_GFCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 32;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_HDQ1W;
	mod.name = MOD_HDQ1W;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_HDQ_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_HDQ1W_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_HDQ1W_CONTEXT */
	mod.clk = (int) OMAP4_12M_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 6144;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 12000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 12000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 12000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 12000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 12000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 12000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 12000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 12000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 12000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 12000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 12000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_I2C1;
	mod.name = MOD_I2C1;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_I2C1_SYSC */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_I2C1_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_I2C1_CONTEXT */
	mod.clk = (int) OMAP4_PER_96M_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 49152;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_I2C2;
	mod.name = MOD_I2C2;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_I2C2_SYSC */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_I2C2_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_I2C2_CONTEXT */
	mod.clk = (int) OMAP4_PER_96M_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 49152;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_I2C3;
	mod.name = MOD_I2C3;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_I2C3_SYSC */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_I2C3_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_I2C3_CONTEXT */
	mod.clk = (int) OMAP4_PER_96M_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 49152;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_I2C4;
	mod.name = MOD_I2C4;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_I2C4_SYSC */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_I2C4_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_I2C4_CONTEXT */
	mod.clk = (int) OMAP4_PER_96M_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 49152;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_L4_PER;
	mod.name = MOD_L4_PER_INTERCONNECT;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): NULL */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_L4PER_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_L4_PER_CONTEXT */
	mod.clk = (int) OMAP4_L4_ICLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 49152;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 50000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 58333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 116666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 58333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_NONE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_MCBSP4;
	mod.name = MOD_MCBSP4;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_MCBSP4_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_MCBSP4_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_MCBSP4_CONTEXT */
	mod.clk = (int) OMAP4_PER_MCBSP4_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 49152;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 96000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_MCSPI1_HL;
	mod.name = MOD_MCSPI1_HL;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_MCSPI1_HL_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_MCSPI1_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_MCSPI1_CONTEXT */
	mod.clk = (int) OMAP4_PER_48M_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_MCSPI1;
	mod.name = MOD_MCSPI1;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_MCSPI1_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_MCSPI1_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_MCSPI1_CONTEXT */
	mod.clk = (int) OMAP4_PER_48M_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_MCSPI2_HL;
	mod.name = MOD_MCSPI2_HL;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_MCSPI2_HL_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_MCSPI2_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_MCSPI2_CONTEXT */
	mod.clk = (int) OMAP4_PER_48M_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_MCSPI2;
	mod.name = MOD_MCSPI2;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_MCSPI2_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_MCSPI2_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_MCSPI2_CONTEXT */
	mod.clk = (int) OMAP4_PER_48M_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_MCSPI3_HL;
	mod.name = MOD_MCSPI3_HL;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_MCSPI3_HL_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_MCSPI3_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_MCSPI3_CONTEXT */
	mod.clk = (int) OMAP4_PER_48M_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_MCSPI3;
	mod.name = MOD_MCSPI3;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_MCSPI3_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_MCSPI3_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_MCSPI3_CONTEXT */
	mod.clk = (int) OMAP4_PER_48M_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_MCSPI4_HL;
	mod.name = MOD_MCSPI4_HL;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_MCSPI4_HL_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_MCSPI4_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_MCSPI4_CONTEXT */
	mod.clk = (int) OMAP4_PER_48M_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_MCSPI4;
	mod.name = MOD_MCSPI4;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_MCSPI4_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_MCSPI4_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_MCSPI4_CONTEXT */
	mod.clk = (int) OMAP4_PER_48M_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_MMC3;
	mod.name = MOD_MMC3;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_MMCHS3_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_MMCSD3_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_MMCSD3_CONTEXT */
	mod.clk = (int) OMAP4_PER_48M_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_DUAL | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_MMC3_HL;
	mod.name = MOD_MMC3_HL;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_MMCHS3_HL_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_MMCSD3_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_MMCSD3_CONTEXT */
	mod.clk = (int) OMAP4_PER_48M_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_DUAL | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_MMC4;
	mod.name = MOD_MMC4;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_MMCHS4_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_MMCSD4_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_MMCSD4_CONTEXT */
	mod.clk = (int) OMAP4_PER_48M_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_DUAL | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_MMC4_HL;
	mod.name = MOD_MMC4_HL;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_MMCHS4_HL_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_MMCSD4_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_MMCSD4_CONTEXT */
	mod.clk = (int) OMAP4_PER_48M_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_DUAL | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_SLIMBUS2;
	mod.name = MOD_SLIMBUS2;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_SLIMBUS2_CMP_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_SLIMBUS2_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_SLIMBUS2_CONTEXT */
	mod.clk = (int) OMAP4_SLIMBUS_CORE_UCLKS;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_UART1;
	mod.name = MOD_UART1;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_UART1_SYSC */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_UART1_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_UART1_CONTEXT */
	mod.clk = (int) OMAP4_PER_48M_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_UART2;
	mod.name = MOD_UART2;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_UART2_SYSC */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_UART2_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_UART2_CONTEXT */
	mod.clk = (int) OMAP4_PER_48M_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_UART3;
	mod.name = MOD_UART3;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_UART3_SYSC */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_UART3_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_UART3_CONTEXT */
	mod.clk = (int) OMAP4_PER_48M_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_UART4;
	mod.name = MOD_UART4;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_UART4_SYSC */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_UART4_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_UART4_CONTEXT */
	mod.clk = (int) OMAP4_PER_48M_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_SLAVE | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_MMC5;
	mod.name = MOD_MMC5;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_MMCHS5_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_MMCSD5_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_MMCSD5_CONTEXT */
	mod.clk = (int) OMAP4_PER_48M_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_DUAL | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod.id = (int) OMAP4_MMC5_HL;
	mod.name = MOD_MMC5_HL;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL; /* FIXME (must create reg struct first): OMAP4430_MMCHS5_HL_SYSCONFIG */
	mod.clkctrl = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_CM_L4PER_MMCSD5_CLKCTRL */
	mod.context = NULL; /* FIXME (must create reg struct first): (unsigned int *) OMAP4430_RM_L4PER_MMCSD5_CONTEXT */
	mod.clk = (int) OMAP4_PER_48M_FCLK;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_DPLL_CASC;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	if (cpu_is_omap4430()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else if (cpu_is_omap4460()) {
		opp.name = OPP_50;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else { /* 4470 */
		opp.name = OPP_50_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_50_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_LOW;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_119_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_100_HIGH;
		opp.rate = 48000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_INTERFACE_DUAL | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod44xx_list, (void *) &mod, sizeof(mod_info));

	mod44xx_init_done = 1;
	dprintf("%s(): init done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod44xx_deinit
 * @BRIEF		free dynamically allocated internal data.
 * @DESCRIPTION		free dynamically allocated internal data.
 *			MUST BE CALLED AT END OF EXECUTION.
 *//*------------------------------------------------------------------------ */
void mod44xx_deinit(void)
{
	int i, count;
	mod_info mod;

	if (mod44xx_init_done) {
		count = genlist_getcount(&mod44xx_list);
		for (i = 0; i < count; i++) {
			genlist_get(&mod44xx_list, i, (mod_info *) &mod);
			genlist_free(&(mod.mod_opp_list));
		}
		genlist_free(&mod44xx_list);
		mod44xx_init_done = 0;
	}
	dprintf("%s(): deinit done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod44xx_list_get
 * @BRIEF		return the list of modules
 * @RETURNS		list of modules in case of success
 *			NULL in case of error
 * @DESCRIPTION		return the list of modules
 *//*------------------------------------------------------------------------ */
const genlist *mod44xx_list_get(void)
{
	mod44xx_init();

	return (const genlist *) &mod44xx_list;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod44xx_count_get
 * @BRIEF		return the number of modules
 * @RETURNS		number of modules (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @DESCRIPTION		return the number of modules
 *//*------------------------------------------------------------------------ */
int mod44xx_count_get(void)
{
	int count;

	mod44xx_init();

	count = genlist_getcount(&mod44xx_list);

	dprintf("%s() = %d\n", __func__, count);
	return count;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod44xx_init_info
 * @BRIEF		initialize module info table
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 * @param[in]		id: module id
 * @param[in]		type: module interface type
 * @param[in]		has_clockactivity_bit: if clockactivity bit exists
 *			in sysconfig register
 * @param[in]		clockdm_id: clock domain id module is part of
 * @param[in]		powerdm_id: power domain id module is part of
 * @param[in]		voltagedm_id: power domain id module is part of
 * @param[in,out]	sysconfig_addr: module sysconfig physical address
 * @param[in,out]	cm_clkctrl_addr: module CM_xxx_xxx_CLKCTRL register
 *			physical address
 * @param[in,out]	rm_context_addr: module RM_xxx_xxx_CONTEXT register
 *			physical address
 * @param[in]		src_clk_id: module source clock id
 * @param[in,out]	por_speed: module clock speed POR (Plan Of Record)
 * @DESCRIPTION		initialize module info table
 *//*------------------------------------------------------------------------ */
static int mod44xx_init_info(
	mod44xx_id id,
	mod_interface_type type,
	unsigned short int has_clockactivity_bit,
	clkdm44xx_id clockdm_id,
	pwrdm44xx_id powerdm_id,
	voltdm44xx_id voltagedm_id,
	unsigned int *sysconfig_addr,
	unsigned int *cm_clkctrl_addr,
	unsigned int *rm_context_addr,
	clock44xx_id src_clk_id,
	double por_speed[OPP44XX_ID_MAX])
{
	unsigned short i;

	if (id >= OMAP4_MODULE_ID_MAX)
		return OMAPCONF_ERR_ARG;

	mod44xx_info_table[id].id = id;
	mod44xx_info_table[id].type = type;
	mod44xx_info_table[id].has_clockactivity_bit = has_clockactivity_bit;
	mod44xx_info_table[id].clockdm_id = clockdm_id;
	mod44xx_info_table[id].powerdm_id = powerdm_id;
	mod44xx_info_table[id].voltagedm_id = voltagedm_id;
	mod44xx_info_table[id].sysconfig_addr = sysconfig_addr;
	mod44xx_info_table[id].cm_clkctrl_addr = cm_clkctrl_addr;
	mod44xx_info_table[id].rm_context_addr = rm_context_addr;
	mod44xx_info_table[id].src_clk_id = src_clk_id;
	for (i = 0; i < OPP44XX_ID_MAX; i++)
		mod44xx_info_table[id].por_speed[i] = por_speed[i];

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod4430_init_info_table
 * @BRIEF		initialize OMAP44[30-60] module info table
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		initialize OMAP44[30-60] module info table
 *//*------------------------------------------------------------------------ */
int mod4430_init_info_table(void)
{
	unsigned int i = 0;

	if (!cpu_is_omap4430() && !cpu_is_omap4460())
		return OMAPCONF_ERR_CPU;

	for (i = 0; i < OMAP4_MODULE_ID_MAX; i++)
		mod44xx_init_info(i, MOD_INTERFACE_NONE, 0, OMAP4_CD_ID_MAX, OMAP4_PD_ID_MAX, OMAP4_VD_ID_MAX, NULL, NULL, NULL, OMAP4_UNDEF_CLK, (double[OPP44XX_ID_MAX]) {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0});
	dprintf("OMAP4_MODULE_ID_MAX = %d\n", OMAP4_MODULE_ID_MAX);

	/* Voltage domain: LDO_WKUP, Power domain: WKUP, Functional clock domain = WKUP */
	mod44xx_init_info(OMAP4_L4_WKUP_INTERCONNECT, MOD_INTERFACE_NONE, 0, OMAP4_CD_WKUP, OMAP4_PD_WKUP, OMAP4_LDO_WKUP, NULL, (unsigned int *) OMAP4430_CM_WKUP_L4WKUP_CLKCTRL, (unsigned int *) OMAP4430_RM_WKUP_L4WKUP_CONTEXT, OMAP4_WKUP_L4_ICLK2, (double[OPP44XX_ID_MAX]) {12.288, 38.4, 38.4, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_CONTROL_GEN_WKUP, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_WKUP, OMAP4_PD_WKUP, OMAP4_LDO_WKUP, OMAP4430_CONTROL_GEN_WKUP_SYSCONFIG, NULL, NULL, OMAP4_WKUP_L4_ICLK2, (double[OPP44XX_ID_MAX]) {12.288, 38.4, 38.4, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_CONTROL_PADCONF_WKUP, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_WKUP, OMAP4_PD_WKUP, OMAP4_LDO_WKUP, OMAP4430_CONTROL_PADCONF_WKUP_SYSCONFIG, NULL, NULL, OMAP4_WKUP_L4_ICLK2, (double[OPP44XX_ID_MAX]) {12.288, 38.4, 38.4, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_WDT2, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_WKUP, OMAP4_PD_WKUP, OMAP4_LDO_WKUP, OMAP4430_WDT2_WDSC, (unsigned int *) OMAP4430_CM_WKUP_WDT2_CLKCTRL, (unsigned int *) OMAP4430_RM_WKUP_WDT2_CONTEXT, OMAP4_WKUP_32K_GFCLK, (double[OPP44XX_ID_MAX]) {0.032768, 0.032768, 0.032768, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_GPIO1, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_WKUP, OMAP4_PD_WKUP, OMAP4_LDO_WKUP, OMAP4430_GPIO1_SYSCONFIG, (unsigned int *) OMAP4430_CM_WKUP_GPIO1_CLKCTRL, (unsigned int *) OMAP4430_RM_WKUP_GPIO1_CONTEXT, OMAP4_WKUP_32K_GFCLK, (double[OPP44XX_ID_MAX]) {0.032768, 0.032768, 0.032768, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_TIMER1, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_WKUP, OMAP4_PD_WKUP, OMAP4_LDO_WKUP, OMAP4430_GPT1_TIOCP_CFG, (unsigned int *) OMAP4430_CM_WKUP_TIMER1_CLKCTRL, (unsigned int *) OMAP4430_RM_WKUP_TIMER1_CONTEXT, OMAP4_GPT1_FCLK, (double[OPP44XX_ID_MAX]) {0.032768, 0.032768, 0.032768, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_SYNCTIMER, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_WKUP, OMAP4_PD_WKUP, OMAP4_LDO_WKUP, OMAP4430_SYNCTIMER_SYSCONFIG, (unsigned int *) OMAP4430_CM_WKUP_SYNCTIMER_CLKCTRL, (unsigned int *) OMAP4430_RM_WKUP_SYNCTIMER_CONTEXT, OMAP4_FUNC_32K_CLK, (double[OPP44XX_ID_MAX]) {0.032768, 0.032768, 0.032768, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_SARRAM, MOD_INTERFACE_NONE, 0, OMAP4_CD_WKUP, OMAP4_PD_WKUP, OMAP4_LDO_WKUP, NULL, (unsigned int *) OMAP4430_CM_WKUP_SARRAM_CLKCTRL, (unsigned int *) OMAP4430_RM_WKUP_SARRAM_CONTEXT, OMAP4_L4_ICLK2, (double[OPP44XX_ID_MAX]) {49.152, 50.0, 100.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_KEYBOARD, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_WKUP, OMAP4_PD_WKUP, OMAP4_LDO_WKUP, OMAP4430_KBD_SYSCONFIG, (unsigned int *) OMAP4430_CM_WKUP_KEYBOARD_CLKCTRL, (unsigned int *) OMAP4430_RM_WKUP_KEYBOARD_CONTEXT, OMAP4_WKUP_32K_GFCLK, (double[OPP44XX_ID_MAX]) {0.032768, 0.032768, 0.032768, -1.0, -1.0, -1.0, -1.0});
	/* HS/EMU device only, not accessible for non-secure world */
	mod44xx_init_info(OMAP4_TIMER12, MOD_INTERFACE_NONE, 0, OMAP4_CD_WKUP, OMAP4_PD_WKUP, OMAP4_LDO_WKUP, NULL, (unsigned int *) OMAP4430_CM_WKUP_TIMER12_CLKCTRL, (unsigned int *) OMAP4430_RM_WKUP_TIMER12_CONTEXT, OMAP4_GPT12_FCLK, (double[OPP44XX_ID_MAX]) {0.032768, 0.032768, 0.032768, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_WDT1, MOD_INTERFACE_NONE, 0, OMAP4_CD_WKUP, OMAP4_PD_WKUP, OMAP4_LDO_WKUP, NULL, (unsigned int *) OMAP4430_CM_WKUP_WDT1_CLKCTRL, (unsigned int *) OMAP4430_RM_WKUP_WDT1_CONTEXT, OMAP4_SECURE_32K_CLK, (double[OPP44XX_ID_MAX]) {0.032768, 0.032768, 0.032768, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_USIM, MOD_INTERFACE_NONE, 0, OMAP4_CD_WKUP, OMAP4_PD_WKUP, OMAP4_LDO_WKUP, NULL, (unsigned int *) OMAP4430_CM_WKUP_USIM_CLKCTRL, (unsigned int *) OMAP4430_RM_WKUP_USIM_CONTEXT, OMAP4_USIM_FCLK, (double[OPP44XX_ID_MAX]) {0.0, 9.142858, 9.142858, -1.0, -1.0, -1.0, -1.0});
	/* end of HS/EMU device only */

	/* Voltage domain: LDO_WKUP, Power domain: WKUP, Functional clock domain = NONE */

	/* Voltage domain: LDO_WKUP, Power domain: EMU, Functional clock domain = EMU */
	mod44xx_init_info(OMAP4_DEBUGSS, MOD_INTERFACE_NONE, 0, OMAP4_CD_EMU, OMAP4_PD_EMU, OMAP4_LDO_WKUP, NULL, (unsigned int *) OMAP4430_CM_EMU_DEBUGSS_CLKCTRL, (unsigned int *) OMAP4430_RM_EMU_DEBUGSS_CONTEXT, OMAP4_CORE_DPLL_EMU_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 266.666687, -1.0, -1.0, -1.0, -1.0});

	/* Voltage domain: VDD_MPU, Power domain: MPU, Functional clock domain = MPU */
	if (!cpu_is_omap4430())
		mod44xx_init_info(OMAP4_MPU, MOD_INTERFACE_NONE, 0, OMAP4_CD_MPU, OMAP4_PD_MPU, OMAP4_VDD_MPU, NULL, (unsigned int *) OMAP4430_CM_MPU_MPU_CLKCTRL, (unsigned int *) OMAP4430_RM_MPU_MPU_CONTEXT, OMAP4_MPU_DPLL_CLK, (double[OPP44XX_ID_MAX]) {196.608, 350.0, 700.0, 920.0, 1200.0, 1500.0, -1.0});
	else
		mod44xx_init_info(OMAP4_MPU, MOD_INTERFACE_NONE, 0, OMAP4_CD_MPU, OMAP4_PD_MPU, OMAP4_VDD_MPU, NULL, (unsigned int *) OMAP4430_CM_MPU_MPU_CLKCTRL, (unsigned int *) OMAP4430_RM_MPU_MPU_CONTEXT, OMAP4_MPU_DPLL_CLK, (double[OPP44XX_ID_MAX]) {196.608, 300.0, 600.0, 800.0, 1008.0, 1200.0, -1.0});

	/* Voltage domain: VDD_MPU, Power domain: ALWON_MPU, Functional clock domain = NONE */

	/* Voltage domain: VDD_IVA, Power domain: ABE, Functional clock domain = ABE */
	mod44xx_init_info(OMAP4_L4_ABE, MOD_INTERFACE_NONE, 0, OMAP4_CD_ABE, OMAP4_PD_ABE, OMAP4_VDD_IVA, NULL, (unsigned int *) OMAP4430_CM1_ABE_L4ABE_CLKCTRL, NULL, OMAP4_ABE_ICLK2, (double[OPP44XX_ID_MAX]) {49.152, 49.152, 98.304, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_AESS, MOD_INTERFACE_DUAL, 0, OMAP4_CD_ABE, OMAP4_PD_ABE, OMAP4_VDD_IVA, OMAP4430_AESS_SYSCONFIG, (unsigned int *) OMAP4430_CM1_ABE_AESS_CLKCTRL, (unsigned int *) OMAP4430_RM_ABE_AESS_CONTEXT, OMAP4_AESS_FCLK, (double[OPP44XX_ID_MAX]) {98.304, 98.304, 196.608, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_MCPDM, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_ABE, OMAP4_PD_ABE, OMAP4_VDD_IVA, OMAP4430_MCPDM_SYSCONFIG, (unsigned int *) OMAP4430_CM1_ABE_PDM_CLKCTRL, (unsigned int *) OMAP4430_RM_ABE_PDM_CONTEXT, OMAP4_PAD_CLKS, (double[OPP44XX_ID_MAX]) {19.2, 19.2, 19.2, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_DMIC, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_ABE, OMAP4_PD_ABE, OMAP4_VDD_IVA, OMAP4430_DMIC_SYSCONFIG, (unsigned int *) OMAP4430_CM1_ABE_DMIC_CLKCTRL, (unsigned int *) OMAP4430_RM_ABE_DMIC_CONTEXT, OMAP4_DMIC_ABE_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 24.576, 24.576, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_MCASP, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_ABE, OMAP4_PD_ABE, OMAP4_VDD_IVA, OMAP4430_MCASP_SYSCONFIG, (unsigned int *) OMAP4430_CM1_ABE_MCASP_CLKCTRL, (unsigned int *) OMAP4430_RM_ABE_MCASP_CONTEXT, OMAP4_MCASP1_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 24.576, 24.576, 24.576, 24.576, 24.576, -1.0});
	mod44xx_init_info(OMAP4_MCBSP1, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_ABE, OMAP4_PD_ABE, OMAP4_VDD_IVA, OMAP4430_MCBSP1_SYSCONFIG, (unsigned int *) OMAP4430_CM1_ABE_MCBSP1_CLKCTRL, (unsigned int *) OMAP4430_RM_ABE_MCBSP1_CONTEXT, OMAP4_MCBSP1_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 24.576, 24.576, 24.576, 24.576, 24.576, -1.0});
	mod44xx_init_info(OMAP4_MCBSP2, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_ABE, OMAP4_PD_ABE, OMAP4_VDD_IVA, OMAP4430_MCBSP2_SYSCONFIG, (unsigned int *) OMAP4430_CM1_ABE_MCBSP2_CLKCTRL, (unsigned int *) OMAP4430_RM_ABE_MCBSP2_CONTEXT, OMAP4_MCBSP2_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 24.576, 24.576, 24.576, 24.576, 24.576, -1.0});
	mod44xx_init_info(OMAP4_MCBSP3, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_ABE, OMAP4_PD_ABE, OMAP4_VDD_IVA, OMAP4430_MCBSP3_SYSCONFIG, (unsigned int *) OMAP4430_CM1_ABE_MCBSP3_CLKCTRL, (unsigned int *) OMAP4430_RM_ABE_MCBSP3_CONTEXT, OMAP4_MCBSP3_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 24.576, 24.576, 24.576, 24.576, 24.576, -1.0});
	mod44xx_init_info(OMAP4_SLIMBUS1, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_ABE, OMAP4_PD_ABE, OMAP4_VDD_IVA, OMAP4430_SLIMBUS1_CMP_SYSCONFIG, (unsigned int *) OMAP4430_CM1_ABE_SLIMBUS_CLKCTRL, (unsigned int *) OMAP4430_RM_ABE_SLIMBUS_CONTEXT, OMAP4_SLIMBUS_UCLKS, (double[OPP44XX_ID_MAX]) {24.576, 24.576, 24.576, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_TIMER5, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_ABE, OMAP4_PD_ABE, OMAP4_VDD_IVA, OMAP4430_GPT5_TIOCP_CFG, (unsigned int *) OMAP4430_CM1_ABE_TIMER5_CLKCTRL, (unsigned int *) OMAP4430_RM_ABE_TIMER5_CONTEXT, OMAP4_ABE_GPT5_FCLK, (double[OPP44XX_ID_MAX]) {38.4, 38.4, 38.4, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_TIMER6, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_ABE, OMAP4_PD_ABE, OMAP4_VDD_IVA, OMAP4430_GPT6_TIOCP_CFG, (unsigned int *) OMAP4430_CM1_ABE_TIMER6_CLKCTRL, (unsigned int *) OMAP4430_RM_ABE_TIMER6_CONTEXT, OMAP4_ABE_GPT6_FCLK, (double[OPP44XX_ID_MAX]) {38.4, 38.4, 38.4, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_TIMER7, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_ABE, OMAP4_PD_ABE, OMAP4_VDD_IVA, OMAP4430_GPT7_TIOCP_CFG, (unsigned int *) OMAP4430_CM1_ABE_TIMER7_CLKCTRL, (unsigned int *) OMAP4430_RM_ABE_TIMER7_CONTEXT, OMAP4_ABE_GPT7_FCLK, (double[OPP44XX_ID_MAX]) {38.4, 38.4, 38.4, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_TIMER8, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_ABE, OMAP4_PD_ABE, OMAP4_VDD_IVA, OMAP4430_GPT8_TIOCP_CFG, (unsigned int *) OMAP4430_CM1_ABE_TIMER8_CLKCTRL, (unsigned int *) OMAP4430_RM_ABE_TIMER8_CONTEXT, OMAP4_ABE_GPT8_FCLK, (double[OPP44XX_ID_MAX]) {38.4, 38.4, 38.4, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_WDT3, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_ABE, OMAP4_PD_ABE, OMAP4_VDD_IVA, OMAP4430_WDT3_WDSC, (unsigned int *) OMAP4430_CM1_ABE_WDT3_CLKCTRL, (unsigned int *) OMAP4430_RM_ABE_WDT3_CONTEXT, OMAP4_ABE_ALWON_32K_CLK, (double[OPP44XX_ID_MAX]) {0.032768, 0.032768, 0.032768, -1.0, -1.0, -1.0, -1.0});

	/* Voltage domain: VDD_IVA, Power domain: IVAHD, Functional clock domain = IVAHD */
	mod44xx_init_info(OMAP4_IVAHD, MOD_INTERFACE_DUAL, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_IVAHD_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.4, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_ICONT1, MOD_INTERFACE_DUAL, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_ICONT1_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.4, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_ICONT2, MOD_INTERFACE_DUAL, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_ICONT2_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.4, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_VDMA, MOD_INTERFACE_DUAL, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_ICONT1_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.4, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_IME3, MOD_INTERFACE_DUAL, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_IME3_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.4, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_IPE3, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_IPE3_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.4, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_ILF3, MOD_INTERFACE_DUAL, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_ILF3_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.4, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_MC3, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_MC3_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.4, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_CALC3, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_CALC3_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.4, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_ECD3, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_ECD3_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.4, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_ICONT1_SB, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_ICONT1_SB_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.4, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_ICONT2_SB, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_ICONT2_SB_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.4, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_ILF3_SB, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_ILF3_SB_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.4, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_IME3_SB, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_IME3_SB_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.4, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_CALC3_SB, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_CALC3_SB_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.4, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_IPE3_SB, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_IPE3_SB_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.4, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_MC3_SB, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_MC3_SB_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.4, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_ECD3_SB, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_ECD3_SB_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.4, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_SL2, MOD_INTERFACE_NONE, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, NULL, (unsigned int *) OMAP4430_CM_IVAHD_SL2_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_SL2_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.4, 500.00002, -1.0});

	/* Voltage domain: VDD_IVA, Power domain: DSP, Functional clock domain = DSP */
	mod44xx_init_info(OMAP4_DSP, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_DSP, OMAP4_PD_DSP, OMAP4_VDD_IVA, OMAP4430_DSP_SYSC_SYSCONFIG, (unsigned int *) OMAP4430_CM_DSP_DSP_CLKCTRL, (unsigned int *) OMAP4430_RM_DSP_DSP_CONTEXT, OMAP4_DSP_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 232.8, 465.6, 496.0, 430.4, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_MMU_DSP, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_DSP, OMAP4_PD_DSP, OMAP4_VDD_IVA, OMAP4430_MMU_DSP_SYSCONFIG, (unsigned int *) OMAP4430_CM_DSP_DSP_CLKCTRL, (unsigned int *) OMAP4430_RM_DSP_DSP_CONTEXT, OMAP4_DSP_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 232.8, 465.6, 496.0, 430.4, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_DSP_WUGEN, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_DSP, OMAP4_PD_ALWON_IVA, OMAP4_VDD_IVA, OMAP4430_DSP_WUGEN_SYSCONFIG, (unsigned int *) OMAP4430_CM_DSP_DSP_CLKCTRL, (unsigned int *) OMAP4430_RM_DSP_DSP_CONTEXT, OMAP4_DSP_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 232.8, 465.6, 496.0, 430.4, 500.00002, -1.0});

	/* Voltage domain: VDD_CORE, Power domain: ALWON_CORE, Functional clock domain = AO_L4 */
	mod44xx_init_info(OMAP4_SMARTREFLEX_CORE, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_AO_L4, OMAP4_PD_ALWON_CORE, OMAP4_VDD_CORE, OMAP4430_ERRCONFIG_CORE, (unsigned int *) OMAP4430_CM_ALWON_SR_CORE_CLKCTRL, (unsigned int *) OMAP4430_RM_ALWON_SR_CORE_CONTEXT, OMAP4_SR_CORE_SYS_CLK, (double[OPP44XX_ID_MAX]) {12.288, 38.4, 38.4, 38.4, 38.4, 38.4, -1.0});
	mod44xx_init_info(OMAP4_SMARTREFLEX_MPU, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_AO_L4, OMAP4_PD_ALWON_CORE, OMAP4_VDD_CORE, OMAP4430_ERRCONFIG_MPU, (unsigned int *) OMAP4430_CM_ALWON_SR_MPU_CLKCTRL, (unsigned int *) OMAP4430_RM_ALWON_SR_MPU_CONTEXT, OMAP4_SR_MPU_SYS_CLK, (double[OPP44XX_ID_MAX]) {12.288, 38.4, 38.4, 38.4, 38.4, 38.4, -1.0});
	mod44xx_init_info(OMAP4_SMARTREFLEX_IVA, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_AO_L4, OMAP4_PD_ALWON_CORE, OMAP4_VDD_CORE, OMAP4430_ERRCONFIG_IVA, (unsigned int *) OMAP4430_CM_ALWON_SR_IVA_CLKCTRL, (unsigned int *) OMAP4430_RM_ALWON_SR_IVA_CONTEXT, OMAP4_SR_IVA_SYS_CLK, (double[OPP44XX_ID_MAX]) {12.288, 38.4, 38.4, 38.4, 38.4, 38.4, -1.0});

	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = L4CFG */
	mod44xx_init_info(OMAP4_L4_CFG, MOD_INTERFACE_NONE, 0, OMAP4_CD_L4CFG, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L4CFG_L4_CFG_CLKCTRL, (unsigned int *) OMAP4430_RM_L4CFG_L4_CFG_CONTEXT, OMAP4_CFG_L4_ICLK, (double[OPP44XX_ID_MAX]) {49.152, 50.0, 100.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_CONTROL_GEN_CORE, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4CFG, OMAP4_PD_CORE, OMAP4_VDD_CORE, OMAP4430_CONTROL_GEN_CORE_SYSCONFIG, NULL, NULL, OMAP4_CFG_L4_ICLK, (double[OPP44XX_ID_MAX]) {49.152, 50.0, 100.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_CONTROL_PADCONF_CORE, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4CFG, OMAP4_PD_CORE, OMAP4_VDD_CORE, OMAP4430_CONTROL_PADCONF_CORE_SYSCONFIG, NULL, NULL, OMAP4_CFG_L4_ICLK, (double[OPP44XX_ID_MAX]) {49.152, 50.0, 100.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_SPINLOCK, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_L4CFG, OMAP4_PD_CORE, OMAP4_VDD_CORE, OMAP4430_SPINLOCK_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4CFG_HW_SEM_CLKCTRL, (unsigned int *) OMAP4430_RM_L4CFG_HW_SEM_CONTEXT, OMAP4_CFG_L4_ICLK, (double[OPP44XX_ID_MAX]) {49.152, 50.0, 100.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_SYSTEM_MAILBOX, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4CFG, OMAP4_PD_CORE, OMAP4_VDD_CORE, OMAP4430_SYSTEM_MBX_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4CFG_MAILBOX_CLKCTRL, (unsigned int *) OMAP4430_RM_L4CFG_MAILBOX_CONTEXT, OMAP4_CFG_L4_ICLK, (double[OPP44XX_ID_MAX]) {49.152, 50.0, 100.0, -1.0, -1.0, -1.0, -1.0});
	/* TODO: CHECK IF REGISTER ACCESSIBLE FROM MPU	mod44xx_init_info(OMAP4_IVAHD_MAILBOX, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4CFG, OMAP4_PD_CORE, OMAP4_VDD_CORE, OMAP4430_IVAHD_MBX_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4CFG_MAILBOX_CLKCTRL, (unsigned int *) OMAP4430_RM_L4CFG_MAILBOX_CONTEXT, OMAP4_UNDEF_CLK, 0.0); */
	mod44xx_init_info(OMAP4_SAR_ROM, MOD_INTERFACE_NONE, 0, OMAP4_CD_L4CFG, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L4CFG_SAR_ROM_CLKCTRL, (unsigned int *) OMAP4430_RM_L4CFG_SAR_ROM_CONTEXT, OMAP4_CFG_L4_ICLK, (double[OPP44XX_ID_MAX]) {49.152, 50.0, 100.0, -1.0, -1.0, -1.0, -1.0});

	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = C2C */
	mod44xx_init_info(OMAP4_C2C, MOD_INTERFACE_NONE, 0, OMAP4_CD_C2C, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_C2C_C2C_CLKCTRL, (unsigned int *) OMAP4430_RM_C2C_C2C_CONTEXT, OMAP4_C2C_L3X2_ICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 200.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_C2C_FW, MOD_INTERFACE_NONE, 0, OMAP4_CD_C2C, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_C2C_C2C_FW_CLKCTRL, (unsigned int *) OMAP4430_RM_C2C_C2C_FW_CONTEXT, OMAP4_C2C_L3_ICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 200.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_ICR_MDM, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_C2C, OMAP4_PD_CORE, OMAP4_VDD_CORE, OMAP4430_ICR_MDM_SYS_CONFIG, NULL, NULL, OMAP4_C2C_L4_ICLK, (double[OPP44XX_ID_MAX]) {49.152, 50.0, 100.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_ICR_MPU, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_C2C, OMAP4_PD_CORE, OMAP4_VDD_CORE, OMAP4430_ICR_MPU_SYS_CONFIG, NULL, NULL, OMAP4_C2C_L4_ICLK, (double[OPP44XX_ID_MAX]) {49.152, 50.0, 100.0, -1.0, -1.0, -1.0, -1.0});

	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = DMA */
	mod44xx_init_info(OMAP4_SDMA, MOD_INTERFACE_DUAL, 1, OMAP4_CD_DMA, OMAP4_PD_CORE, OMAP4_VDD_CORE, OMAP4430_DMA4_SYSCONFIG, (unsigned int *) OMAP4430_CM_SDMA_SDMA_CLKCTRL, (unsigned int *) OMAP4430_RM_SDMA_SDMA_CONTEXT, OMAP4_DMA_L3_ICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 200.0, -1.0, -1.0, -1.0, -1.0});

	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = MPU_M3 */
	mod44xx_init_info(OMAP4_MPU_M3, MOD_INTERFACE_NONE, 0, OMAP4_CD_MPU_M3, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_MPU_M3_MPU_M3_CLKCTRL, (unsigned int *) OMAP4430_RM_MPU_M3_MPU_M3_CONTEXT, OMAP4_MPU_M3_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 400.0, -1.0, -1.0, -1.0, -1.0});
	/* TODO: FURTHER CHECK 	mod44xx_init_info(OMAP4_MPU_M3_WUGEN, MOD_INTERFACE_DUAL, 0, OMAP4_CD_MPU_M3, OMAP4_PD_ALWON_CORE, OMAP4_VDD_CORE, OMAP4430_MPU_M3_WUGEN_SYSCONFIG, (unsigned int *) OMAP4430_CM_MPU_M3_MPU_M3_CLKCTRL, (unsigned int *) OMAP4430_RM_MPU_M3_MPU_M3_CONTEXT, OMAP4_UNDEF_CLK, (double[OPP44XX_ID_MAX]) {0.0); */

	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = NONE */
	/* TODO: FURTHER CHECK WHEN MODULE IS ACCESSIBLE	mod44xx_init_info(OMAP4_MMU_MPU_M3, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_NONE, OMAP4_PD_CORE, OMAP4_VDD_CORE, OMAP4430_MMU_MPU_M3_SYSCONFIG, NULL, NULL, OMAP4_UNDEF_CLK, (double[OPP44XX_ID_MAX]) {0.0); */

	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = L3_1 */
	mod44xx_init_info(OMAP4_L3_1, MOD_INTERFACE_NONE, 0, OMAP4_CD_L3_1, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L3_1_L3_1_CLKCTRL, (unsigned int *) OMAP4430_RM_L3_1_L3_1_CONTEXT, OMAP4_L3_ICLK1, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 200.0, -1.0, -1.0, -1.0, -1.0});

	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = L3_2 */
	mod44xx_init_info(OMAP4_L3_2, MOD_INTERFACE_NONE, 0, OMAP4_CD_L3_2, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L3_2_L3_2_CLKCTRL, (unsigned int *) OMAP4430_RM_L3_2_L3_2_CONTEXT, OMAP4_L3_ICLK2, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 200.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_GPMC, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L3_2, OMAP4_PD_CORE, OMAP4_VDD_CORE, OMAP4430_GPMC_SYSCONFIG, (unsigned int *) OMAP4430_CM_L3_2_GPMC_CLKCTRL, (unsigned int *) OMAP4430_RM_L3_2_GPMC_CONTEXT, OMAP4_L3_ICLK2, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 200.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_OCMC_RAM, MOD_INTERFACE_NONE, 0, OMAP4_CD_L3_2, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L3_2_OCMC_RAM_CLKCTRL, (unsigned int *) OMAP4430_RM_L3_2_OCMC_RAM_CONTEXT, OMAP4_L3_ICLK2, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 200.0, -1.0, -1.0, -1.0, -1.0});

	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = L3_INSTR */
	mod44xx_init_info(OMAP4_L3_3, MOD_INTERFACE_NONE, 0, OMAP4_CD_L3_INSTR, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L3INSTR_L3_3_CLKCTRL, (unsigned int *) OMAP4430_RM_L3INSTR_L3_3_CONTEXT, OMAP4_L3_INSTR_GICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 200.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_L3_INSTR, MOD_INTERFACE_NONE, 0, OMAP4_CD_L3_INSTR, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L3INSTR_L3_INSTR_CLKCTRL, (unsigned int *) OMAP4430_RM_L3INSTR_L3_INSTR_CONTEXT, OMAP4_L3_INSTR_GICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 200.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_OCP_WP1, MOD_INTERFACE_NONE, 0, OMAP4_CD_L3_INSTR, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L3INSTR_OCP_WP1_CLKCTRL, (unsigned int *) OMAP4430_RM_L3INSTR_OCP_WP1_CONTEXT, OMAP4_L3_INSTR_GICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 200.0, -1.0, -1.0, -1.0, -1.0});

	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = EMIF */
	mod44xx_init_info(OMAP4_DMM, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_EMIF, OMAP4_PD_CORE, OMAP4_VDD_CORE, OMAP4430_DMM_SYSCONFIG, (unsigned int *) OMAP4430_CM_MEMIF_DMM_CLKCTRL, (unsigned int *) OMAP4430_RM_MEMIF_DMM_CONTEXT, OMAP4_EMIF_L3_ICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 200.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_EMIF_FW, MOD_INTERFACE_NONE, 0, OMAP4_CD_EMIF, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_MEMIF_EMIF_FW_CLKCTRL, (unsigned int *) OMAP4430_RM_MEMIF_EMIF_FW_CONTEXT, OMAP4_EMIF_L3_ICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 200.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_EMIF1, MOD_INTERFACE_NONE, 0, OMAP4_CD_EMIF, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_MEMIF_EMIF_1_CLKCTRL, (unsigned int *) OMAP4430_RM_MEMIF_EMIF_1_CONTEXT, OMAP4_EMIF_L3_ICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 200.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_EMIF2, MOD_INTERFACE_NONE, 0, OMAP4_CD_EMIF, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_MEMIF_EMIF_2_CLKCTRL, (unsigned int *) OMAP4430_RM_MEMIF_EMIF_2_CONTEXT, OMAP4_EMIF_L3_ICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 200.0, -1.0, -1.0, -1.0, -1.0});
	if (cpu_is_omap4430() && (cpu_revision_get() < REV_ES2_1))
		mod44xx_init_info(OMAP4_DDRPHY, MOD_INTERFACE_NONE, 0, OMAP4_CD_EMIF, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, NULL, NULL, OMAP4_PHY_ROOT_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 400.0, -1.0, -1.0, -1.0, -1.0});
	else
		mod44xx_init_info(OMAP4_DDRPHY, MOD_INTERFACE_NONE, 0, OMAP4_CD_EMIF, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, NULL, NULL, OMAP4_PHY_ROOT_CLK, (double[OPP44XX_ID_MAX]) {196.608, 400.0, 800.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_DLL, MOD_INTERFACE_NONE, 0, OMAP4_CD_EMIF, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_MEMIF_DLL_CLKCTRL, (unsigned int *) OMAP4430_RM_MEMIF_DLL_CONTEXT, OMAP4_DLL_CLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 100.0, -1.0, -1.0, -1.0, -1.0});

	/* Voltage domain: VDD_CORE, Power domain: STD_EFUSE, Functional clock domain = STD_EFUSE */
	mod44xx_init_info(OMAP4_STD_EFUSE, MOD_INTERFACE_NONE, 0, OMAP4_CD_STD_EFUSE, OMAP4_PD_STD_EFUSE, OMAP4_VDD_CORE, NULL, NULL, NULL, OMAP4_STD_EFUSE_SYS_CLK, (double[OPP44XX_ID_MAX]) {38.4, 38.4, 38.4, -1.0, -1.0, -1.0, -1.0});

	/* Voltage domain: VDD_CORE, Power domain: CUST_EFUSE, Functional clock domain = CUST_EFUSE */
	/* HS/EMU device only */
	mod44xx_init_info(OMAP4_CUST_EFUSE, MOD_INTERFACE_NONE, 0, OMAP4_CD_CUST_EFUSE, OMAP4_PD_CUST_EFUSE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_CEFUSE_CEFUSE_CLKCTRL, (unsigned int *) OMAP4430_RM_CEFUSE_CEFUSE_CONTEXT, OMAP4_CUST_EFUSE_SYS_CLK, (double[OPP44XX_ID_MAX]) {-1.0, 38.4, 38.4, -1.0, -1.0, -1.0, -1.0});
	/* end of HS/EMU device only */

	/* Voltage domain: VDD_CORE, Power domain: ALWON_CORE, Functional clock domain = NONE */

	/* Voltage domain: VDD_CORE, Power domain: ALWON_CORE, Functional clock domain = NONE */

	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = NONE */

	/* Voltage domain: VDD_CORE, Power domain: CAM, Functional clock domain = CAM */
	mod44xx_init_info(OMAP4_ISS, MOD_INTERFACE_DUAL, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_ISS_HL_SYSCONFIG, (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT, OMAP4_ISS_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 400.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_CCP2, MOD_INTERFACE_MASTER, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_CCP2_SYSCONFIG, (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT, OMAP4_ISS_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 400.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_CSI2_A, MOD_INTERFACE_MASTER, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_CSI2_A_SYSCONFIG, (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT, OMAP4_ISS_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 400.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_CSI2_B, MOD_INTERFACE_MASTER, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_CSI2_B_SYSCONFIG, (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT, OMAP4_ISS_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 400.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_TCTRL, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_TCTRL_SYSCONFIG, (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT, OMAP4_ISS_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 400.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_BTE, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_BTE_HL_SYSCONFIG, (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT, OMAP4_ISS_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 400.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_CBUFF, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_CBUFF_HL_SYSCONFIG, (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT, OMAP4_ISS_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 400.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_ISP5, MOD_INTERFACE_MASTER, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_ISP5_SYSCONFIG, (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT, OMAP4_ISS_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 400.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_RSZ, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_RSZ_SYSCONFIG, (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT, OMAP4_ISS_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 400.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_SIMCOP, MOD_INTERFACE_MASTER, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_SIMCOP_HL_SYSCONFIG, (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT, OMAP4_ISS_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 400.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_SIMCOP_DMA, MOD_INTERFACE_MASTER, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_SIMCOP_DMA_SYSCONFIG, (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT, OMAP4_ISS_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 400.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_SIMCOP_DCT, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_SIMCOP_DCT_CFG, (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT, OMAP4_ISS_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 400.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_SIMCOP_VLCDJ, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_SIMCOP_VLCDJ_CTRL, (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT, OMAP4_ISS_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 400.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_SIMCOP_ROT, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_SIMCOP_ROT_CFG, (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT, OMAP4_ISS_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 400.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_FDIF, MOD_INTERFACE_DUAL, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_FDIF_SYSCONFIG, (unsigned int *) OMAP4430_CM_CAM_FDIF_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_FDIF_CONTEXT, OMAP4_FDIF_FCLK, (double[OPP44XX_ID_MAX]) {49.152, 64.0, 128.0, -1.0, -1.0, -1.0, -1.0});

	/* Voltage domain: VDD_CORE, Power domain: DSS, Functional clock domain = DSS */
	mod44xx_init_info(OMAP4_DISPC, MOD_INTERFACE_DUAL, 0, OMAP4_CD_DSS, OMAP4_PD_DSS, OMAP4_VDD_CORE, OMAP4430_DISPC_SYSCONFIG, (unsigned int *) OMAP4430_CM_DSS_DSS_CLKCTRL, (unsigned int *) OMAP4430_RM_DSS_DSS_CONTEXT, OMAP4_DSS_FCLK, (double[OPP44XX_ID_MAX]) {98.304, 170.666673, 170.666673, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_DSI1, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_DSS, OMAP4_PD_DSS, OMAP4_VDD_CORE, OMAP4430_DSI1_SYSCONFIG, (unsigned int *) OMAP4430_CM_DSS_DSS_CLKCTRL, (unsigned int *) OMAP4430_RM_DSS_DSS_CONTEXT, OMAP4_DSS_FCLK, (double[OPP44XX_ID_MAX]) {98.304, 170.666673, 170.666673, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_DSI2, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_DSS, OMAP4_PD_DSS, OMAP4_VDD_CORE, OMAP4430_DSI2_SYSCONFIG, (unsigned int *) OMAP4430_CM_DSS_DSS_CLKCTRL, (unsigned int *) OMAP4430_RM_DSS_DSS_CONTEXT, OMAP4_DSS_FCLK, (double[OPP44XX_ID_MAX]) {98.304, 170.666673, 170.666673, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_HDMI, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_DSS, OMAP4_PD_DSS, OMAP4_VDD_CORE, OMAP4430_HDMI_WP_SYSCONFIG, (unsigned int *) OMAP4430_CM_DSS_DSS_CLKCTRL, (unsigned int *) OMAP4430_RM_DSS_DSS_CONTEXT, OMAP4_HDMI_PHY_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_RFBI, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_DSS, OMAP4_PD_DSS, OMAP4_VDD_CORE, OMAP4430_RFBI_SYSCONFIG, (unsigned int *) OMAP4430_CM_DSS_DSS_CLKCTRL, (unsigned int *) OMAP4430_RM_DSS_DSS_CONTEXT, OMAP4_UNDEF_CLK, (double[OPP44XX_ID_MAX]) {0.0, 0.0, 0.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_BB2D, MOD_INTERFACE_NONE, 0, OMAP4_CD_DSS, OMAP4_PD_DSS, OMAP4_VDD_CORE, NULL, NULL, NULL, OMAP4_UNDEF_CLK, (double[OPP44XX_ID_MAX]) {0.0, 0.0, 0.0, -1.0, -1.0, -1.0});

	/* Voltage domain: VDD_CORE, Power domain: GFX, Functional clock domain = GFX */
	if (cpu_is_omap4430())
		mod44xx_init_info(OMAP4_GFX, MOD_INTERFACE_DUAL, 0, OMAP4_CD_GFX, OMAP4_PD_GFX, OMAP4_VDD_CORE, OMAP4430_GFX_SYSCONFIG, (unsigned int *) OMAP4430_CM_GFX_GFX_CLKCTRL, (unsigned int *) OMAP4430_RM_GFX_GFX_CONTEXT, OMAP4_GFX_FCLK, (double[OPP44XX_ID_MAX]) {98.304, 153.6, 307.2, -1.0, -1.0, -1.0, -1.0});
	else
		mod44xx_init_info(OMAP4_GFX, MOD_INTERFACE_DUAL, 0, OMAP4_CD_GFX, OMAP4_PD_GFX, OMAP4_VDD_CORE, OMAP4430_GFX_SYSCONFIG, (unsigned int *) OMAP4430_CM_GFX_GFX_CLKCTRL, (unsigned int *) OMAP4430_RM_GFX_GFX_CONTEXT, OMAP4_GFX_FCLK, (double[OPP44XX_ID_MAX]) {98.304, 153.6, 307.2, -1.0, -1.0, -1.0, 384.0});

	/* Voltage domain: VDD_CORE, Power domain: L3_INIT, Functional clock domain = L3_INIT */
	mod44xx_init_info(OMAP4_MMC1, MOD_INTERFACE_DUAL, 1, OMAP4_CD_L3_INIT, OMAP4_PD_L3_INIT, OMAP4_VDD_CORE, OMAP4430_HSMMC1_SYSCONFIG, (unsigned int *) OMAP4430_CM_L3INIT_MMC1_CLKCTRL, (unsigned int *) OMAP4430_RM_L3INIT_MMC1_CONTEXT, OMAP4_MMC1_FCLK, (double[OPP44XX_ID_MAX]) {49.152, 96.0, 96.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_MMC1_HL, MOD_INTERFACE_DUAL, 0, OMAP4_CD_L3_INIT, OMAP4_PD_L3_INIT, OMAP4_VDD_CORE, OMAP4430_HSMMC1_HL_SYSCONFIG, (unsigned int *) OMAP4430_CM_L3INIT_MMC1_CLKCTRL, (unsigned int *) OMAP4430_RM_L3INIT_MMC1_CONTEXT, OMAP4_MMC1_FCLK, (double[OPP44XX_ID_MAX]) {49.152, 96.0, 96.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_MMC2, MOD_INTERFACE_DUAL, 1, OMAP4_CD_L3_INIT, OMAP4_PD_L3_INIT, OMAP4_VDD_CORE, OMAP4430_HSMMC2_SYSCONFIG, (unsigned int *) OMAP4430_CM_L3INIT_MMC2_CLKCTRL, (unsigned int *) OMAP4430_RM_L3INIT_MMC2_CONTEXT, OMAP4_MMC2_FCLK, (double[OPP44XX_ID_MAX]) {49.152, 96.0, 96.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_MMC2_HL, MOD_INTERFACE_DUAL, 0, OMAP4_CD_L3_INIT, OMAP4_PD_L3_INIT, OMAP4_VDD_CORE, OMAP4430_HSMMC2_HL_SYSCONFIG, (unsigned int *) OMAP4430_CM_L3INIT_MMC2_CLKCTRL, (unsigned int *) OMAP4430_RM_L3INIT_MMC2_CONTEXT, OMAP4_MMC2_FCLK, (double[OPP44XX_ID_MAX]) {49.152, 96.0, 96.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_HSI, MOD_INTERFACE_DUAL, 0, OMAP4_CD_L3_INIT, OMAP4_PD_L3_INIT, OMAP4_VDD_CORE, OMAP4430_HSI_SYSCONFIG, (unsigned int *) OMAP4430_CM_L3INIT_HSI_CLKCTRL, (unsigned int *) OMAP4430_RM_L3INIT_HSI_CONTEXT, OMAP4_HSI_FCLK, (double[OPP44XX_ID_MAX]) {49.152, 96.0, 96.0, -1.0, -1.0, -1.0, -1.0});
	/* UNIPRO1 only in ES1.0 */
	mod44xx_init_info(OMAP4_UNIPRO1, MOD_INTERFACE_DUAL, 0, OMAP4_CD_L3_INIT, OMAP4_PD_L3_INIT, OMAP4_VDD_CORE, OMAP4430_UNIPRO1_SYSCONFIG, (unsigned int *) OMAP4430_CM_L3INIT_UNIPRO1_CLKCTRL, (unsigned int *) OMAP4430_RM_L3INIT_UNIPRO1_CONTEXT, OMAP4_UNIPRO1_PHY_FCLK, (double[OPP44XX_ID_MAX]) {-1.0, 96.0, 96.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_HSUSBHOST, MOD_INTERFACE_DUAL, 0, OMAP4_CD_L3_INIT, OMAP4_PD_L3_INIT, OMAP4_VDD_CORE, OMAP4430_UHH_SYSCONFIG, (unsigned int *) OMAP4430_CM_L3INIT_USB_HOST_CLKCTRL, (unsigned int *) OMAP4430_RM_L3INIT_USB_HOST_CONTEXT, OMAP4_INIT_48MC_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_HSUSBOTG, MOD_INTERFACE_DUAL, 0, OMAP4_CD_L3_INIT, OMAP4_PD_L3_INIT, OMAP4_VDD_CORE, OMAP4430_HSUSBOTG_SYSCONFIG, (unsigned int *) OMAP4430_CM_L3INIT_USB_OTG_CLKCTRL, (unsigned int *) OMAP4430_RM_L3INIT_USB_OTG_CONTEXT, OMAP4_OTG_60M_FCLK, (double[OPP44XX_ID_MAX]) {60.0, 60.0, 60.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_USBTLL, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L3_INIT, OMAP4_PD_L3_INIT, OMAP4_VDD_CORE, OMAP4430_USBTLL_SYSCONFIG, (unsigned int *) OMAP4430_CM_L3INIT_USB_TLL_CLKCTRL, (unsigned int *) OMAP4430_RM_L3INIT_USB_TLL_CONTEXT, OMAP4_INIT_60M_FCLK, (double[OPP44XX_ID_MAX]) {60.0, 60.0, 60.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_P1500, MOD_INTERFACE_NONE, 0, OMAP4_CD_L3_INIT, OMAP4_PD_L3_INIT, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L3INIT_P1500_CLKCTRL, (unsigned int *) OMAP4430_RM_L3INIT_P1500_CONTEXT, OMAP4_INIT_L3_ICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 200.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_FSUSBHOST, MOD_INTERFACE_DUAL, 0, OMAP4_CD_L3_INIT, OMAP4_PD_L3_INIT, OMAP4_VDD_CORE, OMAP4430_FSUSBHOST_HCOCPSYS, (unsigned int *) OMAP4430_CM_L3INIT_USB_HOST_FS_CLKCTRL, (unsigned int *) OMAP4430_RM_L3INIT_USB_HOST_FS_CONTEXT, OMAP4_INIT_48MC_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_USBPHY, MOD_INTERFACE_NONE, 0, OMAP4_CD_L3_INIT, OMAP4_PD_L3_INIT, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L3INIT_USBPHYOCP2SCP_CLKCTRL, (unsigned int *) OMAP4430_RM_L3INIT_USBPHYOCP2SCP_CONTEXT, OMAP4_INIT_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, -1.0, -1.0, -1.0, -1.0});

	/* Voltage domain: VDD_CORE, Power domain: L3_INIT, Functional clock domain = NONE */

	/* Voltage domain: VDD_CORE, Power domain: L4_PER, Functional clock domain = L4_SEC */
	/* HS/EMU device only, not accessible for non-secure world */
	mod44xx_init_info(OMAP4_CRYPTODMA, MOD_INTERFACE_NONE, 1, OMAP4_CD_L4_SEC, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L4SEC_CRYPTODMA_CLKCTRL, (unsigned int *) OMAP4430_RM_L4SEC_CRYPTODMA_CONTEXT, OMAP4_L3_SECURE_GICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 200.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_AES1, MOD_INTERFACE_NONE, 0, OMAP4_CD_L4_SEC, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L4SEC_AES1_CLKCTRL, (unsigned int *) OMAP4430_RM_L4SEC_AES1_CONTEXT, OMAP4_L3_SECURE_GICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 200.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_AES2, MOD_INTERFACE_NONE, 0, OMAP4_CD_L4_SEC, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L4SEC_AES2_CLKCTRL, (unsigned int *) OMAP4430_RM_L4SEC_AES2_CONTEXT, OMAP4_L3_SECURE_GICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 200.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_SHA2MD5_1, MOD_INTERFACE_NONE, 0, OMAP4_CD_L4_SEC, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L4SEC_SHA2MD51_CLKCTRL, (unsigned int *) OMAP4430_RM_L4SEC_SHA2MD51_CONTEXT, OMAP4_L3_SECURE_GICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 200.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_RNG, MOD_INTERFACE_NONE, 0, OMAP4_CD_L4_SEC, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L4SEC_RNG_CLKCTRL, (unsigned int *) OMAP4430_RM_L4SEC_RNG_CONTEXT, OMAP4_L4_SECURE_GICLK, (double[OPP44XX_ID_MAX]) {49.152, 50.0, 100.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_DES3DES, MOD_INTERFACE_NONE, 0, OMAP4_CD_L4_SEC, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L4SEC_DES3DES_CLKCTRL, (unsigned int *) OMAP4430_RM_L4SEC_DES3DES_CONTEXT, OMAP4_L4_SECURE_GICLK, (double[OPP44XX_ID_MAX]) {49.152, 50.0, 100.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_PKAEIP29, MOD_INTERFACE_NONE, 0, OMAP4_CD_L4_SEC, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L4SEC_PKAEIP29_CLKCTRL, (unsigned int *) OMAP4430_RM_L4SEC_PKAEIP29_CONTEXT, OMAP4_L4_SECURE_GICLK, (double[OPP44XX_ID_MAX]) {49.152, 50.0, 100.0, -1.0, -1.0, -1.0, -1.0});
	/* end of HS/EMU device only */

	/* Voltage domain: VDD_CORE, Power domain: L4_PER, Functional clock domain = L4_PER */
	mod44xx_init_info(OMAP4_TIMER10, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_GPT10_TIOCP_CFG, (unsigned int *) OMAP4430_CM_L4PER_DMTIMER10_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_DMTIMER10_CONTEXT, OMAP4_GPT10_FCLK, (double[OPP44XX_ID_MAX]) {38.4, 38.4, 38.4, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_TIMER11, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_GPT11_TIOCP_CFG, (unsigned int *) OMAP4430_CM_L4PER_DMTIMER11_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_DMTIMER11_CONTEXT, OMAP4_GPT11_FCLK, (double[OPP44XX_ID_MAX]) {38.4, 38.4, 38.4, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_TIMER2, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_GPT2_TIOCP_CFG, (unsigned int *) OMAP4430_CM_L4PER_DMTIMER2_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_DMTIMER2_CONTEXT, OMAP4_GPT2_FCLK, (double[OPP44XX_ID_MAX]) {38.4, 38.4, 38.4, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_TIMER3, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_GPT3_TIOCP_CFG, (unsigned int *) OMAP4430_CM_L4PER_DMTIMER3_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_DMTIMER3_CONTEXT, OMAP4_GPT3_FCLK, (double[OPP44XX_ID_MAX]) {38.4, 38.4, 38.4, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_TIMER4, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_GPT4_TIOCP_CFG, (unsigned int *) OMAP4430_CM_L4PER_DMTIMER4_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_DMTIMER4_CONTEXT, OMAP4_GPT4_FCLK, (double[OPP44XX_ID_MAX]) {38.4, 38.4, 38.4, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_TIMER9, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_GPT9_TIOCP_CFG, (unsigned int *) OMAP4430_CM_L4PER_DMTIMER9_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_DMTIMER9_CONTEXT, OMAP4_GPT9_FCLK, (double[OPP44XX_ID_MAX]) {38.4, 38.4, 38.4, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_ELM, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_ELM_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_ELM_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_ELM_CONTEXT, OMAP4_PER_L4_ICLK, (double[OPP44XX_ID_MAX]) {49.152, 50.0, 100.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_GPIO2, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_GPIO2_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_GPIO2_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_GPIO2_CONTEXT, OMAP4_PER_32K_GFCLK, (double[OPP44XX_ID_MAX]) {0.032768, 0.032768, 0.032768, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_GPIO3, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_GPIO3_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_GPIO3_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_GPIO3_CONTEXT, OMAP4_PER_32K_GFCLK, (double[OPP44XX_ID_MAX]) {0.032768, 0.032768, 0.032768, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_GPIO4, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_GPIO4_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_GPIO4_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_GPIO4_CONTEXT, OMAP4_PER_32K_GFCLK, (double[OPP44XX_ID_MAX]) {0.032768, 0.032768, 0.032768, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_GPIO5, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_GPIO5_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_GPIO5_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_GPIO5_CONTEXT, OMAP4_PER_32K_GFCLK, (double[OPP44XX_ID_MAX]) {0.032768, 0.032768, 0.032768, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_GPIO6, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_GPIO6_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_GPIO6_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_GPIO6_CONTEXT, OMAP4_PER_32K_GFCLK, (double[OPP44XX_ID_MAX]) {0.032768, 0.032768, 0.032768, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_HDQ1W, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_HDQ_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_HDQ1W_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_HDQ1W_CONTEXT, OMAP4_12M_FCLK, (double[OPP44XX_ID_MAX]) {6.144, 12.0, 12.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_I2C1, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_I2C1_SYSC, (unsigned int *) OMAP4430_CM_L4PER_I2C1_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_I2C1_CONTEXT, OMAP4_PER_96M_FCLK, (double[OPP44XX_ID_MAX]) {49.152, 96.0, 96.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_I2C2, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_I2C2_SYSC, (unsigned int *) OMAP4430_CM_L4PER_I2C2_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_I2C2_CONTEXT, OMAP4_PER_96M_FCLK, (double[OPP44XX_ID_MAX]) {49.152, 96.0, 96.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_I2C3, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_I2C3_SYSC, (unsigned int *) OMAP4430_CM_L4PER_I2C3_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_I2C3_CONTEXT, OMAP4_PER_96M_FCLK, (double[OPP44XX_ID_MAX]) {49.152, 96.0, 96.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_I2C4, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_I2C4_SYSC, (unsigned int *) OMAP4430_CM_L4PER_I2C4_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_I2C4_CONTEXT, OMAP4_PER_96M_FCLK, (double[OPP44XX_ID_MAX]) {49.152, 96.0, 96.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_L4_PER, MOD_INTERFACE_NONE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L4PER_L4PER_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_L4_PER_CONTEXT, OMAP4_L4_ICLK, (double[OPP44XX_ID_MAX]) {49.152, 50.0, 100.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_MCBSP4, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MCBSP4_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MCBSP4_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MCBSP4_CONTEXT, OMAP4_PER_MCBSP4_FCLK, (double[OPP44XX_ID_MAX]) {49.152, 96.0, 96.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_MCSPI1_HL, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MCSPI1_HL_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MCSPI1_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MCSPI1_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_MCSPI1, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MCSPI1_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MCSPI1_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MCSPI1_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_MCSPI2_HL, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MCSPI2_HL_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MCSPI2_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MCSPI2_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_MCSPI2, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MCSPI2_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MCSPI2_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MCSPI2_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_MCSPI3_HL, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MCSPI3_HL_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MCSPI3_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MCSPI3_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_MCSPI3, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MCSPI3_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MCSPI3_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MCSPI3_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_MCSPI4_HL, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MCSPI4_HL_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MCSPI4_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MCSPI4_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_MCSPI4, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MCSPI4_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MCSPI4_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MCSPI4_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_MMC3, MOD_INTERFACE_DUAL, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MMCHS3_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MMCSD3_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MMCSD3_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_MMC3_HL, MOD_INTERFACE_DUAL, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MMCHS3_HL_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MMCSD3_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MMCSD3_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_MMC4, MOD_INTERFACE_DUAL, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MMCHS4_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MMCSD4_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MMCSD4_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_MMC4_HL, MOD_INTERFACE_DUAL, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MMCHS4_HL_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MMCSD4_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MMCSD4_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_SLIMBUS2, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_SLIMBUS2_CMP_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_SLIMBUS2_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_SLIMBUS2_CONTEXT, OMAP4_SLIMBUS_CORE_UCLKS, (double[OPP44XX_ID_MAX]) {24.576, 24.576, 24.576, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_UART1, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_UART1_SYSC, (unsigned int *) OMAP4430_CM_L4PER_UART1_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_UART1_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_UART2, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_UART2_SYSC, (unsigned int *) OMAP4430_CM_L4PER_UART2_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_UART2_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_UART3, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_UART3_SYSC, (unsigned int *) OMAP4430_CM_L4PER_UART3_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_UART3_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_UART4, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_UART4_SYSC, (unsigned int *) OMAP4430_CM_L4PER_UART4_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_UART4_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_MMC5, MOD_INTERFACE_DUAL, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MMCHS5_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MMCSD5_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MMCSD5_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_MMC5_HL, MOD_INTERFACE_DUAL, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MMCHS5_HL_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MMCSD5_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MMCSD5_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, -1.0, -1.0, -1.0, -1.0});

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod4470_init_info_table
 * @BRIEF		initialize OMAP4470 module info table
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		initialize OMAP4470 module info table
 *//*------------------------------------------------------------------------ */
int mod4470_init_info_table(void)
{
	unsigned int i = 0;

	if (!cpu_is_omap4470())
		return OMAPCONF_ERR_CPU;

	for (i = 0; i < OMAP4_MODULE_ID_MAX; i++)
		mod44xx_init_info(i, MOD_INTERFACE_NONE, 0, OMAP4_CD_ID_MAX, OMAP4_PD_ID_MAX, OMAP4_VD_ID_MAX, NULL, NULL, NULL, OMAP4_UNDEF_CLK, (double[OPP44XX_ID_MAX]) {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0});
	dprintf("OMAP4_MODULE_ID_MAX = %d\n", OMAP4_MODULE_ID_MAX);

	/* Voltage domain: LDO_WKUP, Power domain: WKUP, Functional clock domain = WKUP */
	mod44xx_init_info(OMAP4_L4_WKUP_INTERCONNECT, MOD_INTERFACE_NONE, 0, OMAP4_CD_WKUP, OMAP4_PD_WKUP, OMAP4_LDO_WKUP, NULL, (unsigned int *) OMAP4430_CM_WKUP_L4WKUP_CLKCTRL, (unsigned int *) OMAP4430_RM_WKUP_L4WKUP_CONTEXT, OMAP4_WKUP_L4_ICLK2, (double[OPP44XX_ID_MAX]) {12.288, 38.4, 38.4, 38.4, 38.4, 38.4, 38.4});
	mod44xx_init_info(OMAP4_CONTROL_GEN_WKUP, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_WKUP, OMAP4_PD_WKUP, OMAP4_LDO_WKUP, OMAP4430_CONTROL_GEN_WKUP_SYSCONFIG, NULL, NULL, OMAP4_WKUP_L4_ICLK2, (double[OPP44XX_ID_MAX]) {12.288, 38.4, 38.4, 38.4, 38.4, 38.4, 38.4});
	mod44xx_init_info(OMAP4_CONTROL_PADCONF_WKUP, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_WKUP, OMAP4_PD_WKUP, OMAP4_LDO_WKUP, OMAP4430_CONTROL_PADCONF_WKUP_SYSCONFIG, NULL, NULL, OMAP4_WKUP_L4_ICLK2, (double[OPP44XX_ID_MAX]) {12.288, 38.4, 38.4, 38.4, 38.4, 38.4, 38.4});
	mod44xx_init_info(OMAP4_WDT2, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_WKUP, OMAP4_PD_WKUP, OMAP4_LDO_WKUP, OMAP4430_WDT2_WDSC, (unsigned int *) OMAP4430_CM_WKUP_WDT2_CLKCTRL, (unsigned int *) OMAP4430_RM_WKUP_WDT2_CONTEXT, OMAP4_WKUP_32K_GFCLK, (double[OPP44XX_ID_MAX]) {0.032768, 0.032768, 0.032768, 0.032768, 0.032768, 0.032768, 0.032768});
	mod44xx_init_info(OMAP4_GPIO1, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_WKUP, OMAP4_PD_WKUP, OMAP4_LDO_WKUP, OMAP4430_GPIO1_SYSCONFIG, (unsigned int *) OMAP4430_CM_WKUP_GPIO1_CLKCTRL, (unsigned int *) OMAP4430_RM_WKUP_GPIO1_CONTEXT, OMAP4_WKUP_32K_GFCLK, (double[OPP44XX_ID_MAX]) {0.032768, 0.032768, 0.032768, 0.032768, 0.032768, 0.032768, 0.032768});
	mod44xx_init_info(OMAP4_TIMER1, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_WKUP, OMAP4_PD_WKUP, OMAP4_LDO_WKUP, OMAP4430_GPT1_TIOCP_CFG, (unsigned int *) OMAP4430_CM_WKUP_TIMER1_CLKCTRL, (unsigned int *) OMAP4430_RM_WKUP_TIMER1_CONTEXT, OMAP4_GPT1_FCLK, (double[OPP44XX_ID_MAX]) {0.032768, 0.032768, 0.032768, 0.032768, 0.032768, 0.032768, 0.032768});
	mod44xx_init_info(OMAP4_SYNCTIMER, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_WKUP, OMAP4_PD_WKUP, OMAP4_LDO_WKUP, OMAP4430_SYNCTIMER_SYSCONFIG, (unsigned int *) OMAP4430_CM_WKUP_SYNCTIMER_CLKCTRL, (unsigned int *) OMAP4430_RM_WKUP_SYNCTIMER_CONTEXT, OMAP4_FUNC_32K_CLK, (double[OPP44XX_ID_MAX]) {0.032768, 0.032768, 0.032768, 0.032768, 0.032768, 0.032768, 0.032768});
	mod44xx_init_info(OMAP4_SARRAM, MOD_INTERFACE_NONE, 0, OMAP4_CD_WKUP, OMAP4_PD_WKUP, OMAP4_LDO_WKUP, NULL, (unsigned int *) OMAP4430_CM_WKUP_SARRAM_CLKCTRL, (unsigned int *) OMAP4430_RM_WKUP_SARRAM_CONTEXT, OMAP4_L4_ICLK2, (double[OPP44XX_ID_MAX]) {49.152, 50.0, 58.333336, 100.0, 100.0, 116.666672, 58.333336});
	mod44xx_init_info(OMAP4_KEYBOARD, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_WKUP, OMAP4_PD_WKUP, OMAP4_LDO_WKUP, OMAP4430_KBD_SYSCONFIG, (unsigned int *) OMAP4430_CM_WKUP_KEYBOARD_CLKCTRL, (unsigned int *) OMAP4430_RM_WKUP_KEYBOARD_CONTEXT, OMAP4_WKUP_32K_GFCLK, (double[OPP44XX_ID_MAX]) {0.032768, 0.032768, 0.032768, 0.032768, 0.032768, 0.032768, 0.032768});
	/* HS/EMU device only, not accessible for non-secure world */
	mod44xx_init_info(OMAP4_TIMER12, MOD_INTERFACE_NONE, 0, OMAP4_CD_WKUP, OMAP4_PD_WKUP, OMAP4_LDO_WKUP, NULL, (unsigned int *) OMAP4430_CM_WKUP_TIMER12_CLKCTRL, (unsigned int *) OMAP4430_RM_WKUP_TIMER12_CONTEXT, OMAP4_GPT12_FCLK, (double[OPP44XX_ID_MAX]) {0.032768, 0.032768, 0.032768, 0.032768, 0.032768, 0.032768, 0.032768});
	mod44xx_init_info(OMAP4_WDT1, MOD_INTERFACE_NONE, 0, OMAP4_CD_WKUP, OMAP4_PD_WKUP, OMAP4_LDO_WKUP, NULL, (unsigned int *) OMAP4430_CM_WKUP_WDT1_CLKCTRL, (unsigned int *) OMAP4430_RM_WKUP_WDT1_CONTEXT, OMAP4_SECURE_32K_CLK, (double[OPP44XX_ID_MAX]) {0.032768, 0.032768, 0.032768, 0.032768, 0.032768, 0.032768, 0.032768});
	mod44xx_init_info(OMAP4_USIM, MOD_INTERFACE_NONE, 0, OMAP4_CD_WKUP, OMAP4_PD_WKUP, OMAP4_LDO_WKUP, NULL, (unsigned int *) OMAP4430_CM_WKUP_USIM_CLKCTRL, (unsigned int *) OMAP4430_RM_WKUP_USIM_CONTEXT, OMAP4_USIM_FCLK, (double[OPP44XX_ID_MAX]) {0.0, 9.142858, 9.142858, 9.142858, 9.142858, 9.142858, 9.142858});
	/* end of HS/EMU device only */

	/* Voltage domain: LDO_WKUP, Power domain: WKUP, Functional clock domain = NONE */

	/* Voltage domain: LDO_WKUP, Power domain: EMU, Functional clock domain = EMU */
	mod44xx_init_info(OMAP4_DEBUGSS, MOD_INTERFACE_NONE, 0, OMAP4_CD_EMU, OMAP4_PD_EMU, OMAP4_LDO_WKUP, NULL, (unsigned int *) OMAP4430_CM_EMU_DEBUGSS_CLKCTRL, (unsigned int *) OMAP4430_RM_EMU_DEBUGSS_CONTEXT, OMAP4_CORE_DPLL_EMU_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 207.407, 266.666687, 266.666687, 266.666687, 266.666687});

	/* Voltage domain: VDD_MPU, Power domain: MPU, Functional clock domain = MPU */
	mod44xx_init_info(OMAP4_MPU, MOD_INTERFACE_NONE, 0, OMAP4_CD_MPU, OMAP4_PD_MPU, OMAP4_VDD_MPU, NULL, (unsigned int *) OMAP4430_CM_MPU_MPU_CLKCTRL, (unsigned int *) OMAP4430_RM_MPU_MPU_CONTEXT, OMAP4_MPU_DPLL_CLK, (double[OPP44XX_ID_MAX]) {196.608, 396.800018, 800.0, 1100.0, 1300, 1500, -1.0});

	/* Voltage domain: VDD_MPU, Power domain: ALWON_MPU, Functional clock domain = NONE */

	/* Voltage domain: VDD_IVA, Power domain: ABE, Functional clock domain = ABE */
	mod44xx_init_info(OMAP4_L4_ABE, MOD_INTERFACE_NONE, 0, OMAP4_CD_ABE, OMAP4_PD_ABE, OMAP4_VDD_IVA, NULL, (unsigned int *) OMAP4430_CM1_ABE_L4ABE_CLKCTRL, NULL, OMAP4_ABE_ICLK2, (double[OPP44XX_ID_MAX]) {49.152, 49.152, 98.304, 98.304, 98.304, 98.304, -1.0});
	mod44xx_init_info(OMAP4_AESS, MOD_INTERFACE_DUAL, 0, OMAP4_CD_ABE, OMAP4_PD_ABE, OMAP4_VDD_IVA, OMAP4430_AESS_SYSCONFIG, (unsigned int *) OMAP4430_CM1_ABE_AESS_CLKCTRL, (unsigned int *) OMAP4430_RM_ABE_AESS_CONTEXT, OMAP4_AESS_FCLK, (double[OPP44XX_ID_MAX]) {98.304, 98.304, 196.608, 196.608, 196.608, 196.608, -1.0});
	mod44xx_init_info(OMAP4_MCPDM, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_ABE, OMAP4_PD_ABE, OMAP4_VDD_IVA, OMAP4430_MCPDM_SYSCONFIG, (unsigned int *) OMAP4430_CM1_ABE_PDM_CLKCTRL, (unsigned int *) OMAP4430_RM_ABE_PDM_CONTEXT, OMAP4_PAD_CLKS, (double[OPP44XX_ID_MAX]) {19.2, 19.2, 19.2, 19.2, 19.2, 19.2, -1.0});
	mod44xx_init_info(OMAP4_DMIC, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_ABE, OMAP4_PD_ABE, OMAP4_VDD_IVA, OMAP4430_DMIC_SYSCONFIG, (unsigned int *) OMAP4430_CM1_ABE_DMIC_CLKCTRL, (unsigned int *) OMAP4430_RM_ABE_DMIC_CONTEXT, OMAP4_DMIC_ABE_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 24.576, 24.576, 24.576, 24.576, 24.576, -1.0});
	mod44xx_init_info(OMAP4_MCASP, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_ABE, OMAP4_PD_ABE, OMAP4_VDD_IVA, OMAP4430_MCASP_SYSCONFIG, (unsigned int *) OMAP4430_CM1_ABE_MCASP_CLKCTRL, (unsigned int *) OMAP4430_RM_ABE_MCASP_CONTEXT, OMAP4_MCASP1_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 24.576, 24.576, 24.576, 24.576, 24.576, -1.0});
	mod44xx_init_info(OMAP4_MCBSP1, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_ABE, OMAP4_PD_ABE, OMAP4_VDD_IVA, OMAP4430_MCBSP1_SYSCONFIG, (unsigned int *) OMAP4430_CM1_ABE_MCBSP1_CLKCTRL, (unsigned int *) OMAP4430_RM_ABE_MCBSP1_CONTEXT, OMAP4_MCBSP1_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 24.576, 24.576, 24.576, 24.576, 24.576, -1.0});
	mod44xx_init_info(OMAP4_MCBSP2, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_ABE, OMAP4_PD_ABE, OMAP4_VDD_IVA, OMAP4430_MCBSP2_SYSCONFIG, (unsigned int *) OMAP4430_CM1_ABE_MCBSP2_CLKCTRL, (unsigned int *) OMAP4430_RM_ABE_MCBSP2_CONTEXT, OMAP4_MCBSP2_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 24.576, 24.576, 24.576, 24.576, 24.576, -1.0});
	mod44xx_init_info(OMAP4_MCBSP3, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_ABE, OMAP4_PD_ABE, OMAP4_VDD_IVA, OMAP4430_MCBSP3_SYSCONFIG, (unsigned int *) OMAP4430_CM1_ABE_MCBSP3_CLKCTRL, (unsigned int *) OMAP4430_RM_ABE_MCBSP3_CONTEXT, OMAP4_MCBSP3_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 24.576, 24.576, 24.576, 24.576, 24.576, -1.0});
	mod44xx_init_info(OMAP4_SLIMBUS1, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_ABE, OMAP4_PD_ABE, OMAP4_VDD_IVA, OMAP4430_SLIMBUS1_CMP_SYSCONFIG, (unsigned int *) OMAP4430_CM1_ABE_SLIMBUS_CLKCTRL, (unsigned int *) OMAP4430_RM_ABE_SLIMBUS_CONTEXT, OMAP4_SLIMBUS_UCLKS, (double[OPP44XX_ID_MAX]) {24.576, 24.576, 24.576, 24.576, 24.576, 24.576, -1.0});
	mod44xx_init_info(OMAP4_TIMER5, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_ABE, OMAP4_PD_ABE, OMAP4_VDD_IVA, OMAP4430_GPT5_TIOCP_CFG, (unsigned int *) OMAP4430_CM1_ABE_TIMER5_CLKCTRL, (unsigned int *) OMAP4430_RM_ABE_TIMER5_CONTEXT, OMAP4_ABE_GPT5_FCLK, (double[OPP44XX_ID_MAX]) {38.4, 38.4, 38.4, 38.4, 38.4, 38.4, -1.0});
	mod44xx_init_info(OMAP4_TIMER6, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_ABE, OMAP4_PD_ABE, OMAP4_VDD_IVA, OMAP4430_GPT6_TIOCP_CFG, (unsigned int *) OMAP4430_CM1_ABE_TIMER6_CLKCTRL, (unsigned int *) OMAP4430_RM_ABE_TIMER6_CONTEXT, OMAP4_ABE_GPT6_FCLK, (double[OPP44XX_ID_MAX]) {38.4, 38.4, 38.4, 38.4, 38.4, 38.4, -1.0});
	mod44xx_init_info(OMAP4_TIMER7, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_ABE, OMAP4_PD_ABE, OMAP4_VDD_IVA, OMAP4430_GPT7_TIOCP_CFG, (unsigned int *) OMAP4430_CM1_ABE_TIMER7_CLKCTRL, (unsigned int *) OMAP4430_RM_ABE_TIMER7_CONTEXT, OMAP4_ABE_GPT7_FCLK, (double[OPP44XX_ID_MAX]) {38.4, 38.4, 38.4, 38.4, 38.4, 38.4, -1.0});
	mod44xx_init_info(OMAP4_TIMER8, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_ABE, OMAP4_PD_ABE, OMAP4_VDD_IVA, OMAP4430_GPT8_TIOCP_CFG, (unsigned int *) OMAP4430_CM1_ABE_TIMER8_CLKCTRL, (unsigned int *) OMAP4430_RM_ABE_TIMER8_CONTEXT, OMAP4_ABE_GPT8_FCLK, (double[OPP44XX_ID_MAX]) {38.4, 38.4, 38.4, 38.4, 38.4, 38.4, -1.0});
	mod44xx_init_info(OMAP4_WDT3, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_ABE, OMAP4_PD_ABE, OMAP4_VDD_IVA, OMAP4430_WDT3_WDSC, (unsigned int *) OMAP4430_CM1_ABE_WDT3_CLKCTRL, (unsigned int *) OMAP4430_RM_ABE_WDT3_CONTEXT, OMAP4_ABE_ALWON_32K_CLK, (double[OPP44XX_ID_MAX]) {0.032768, 0.032768, 0.032768, 0.032768, 0.032768, 0.032768, -1.0});

	/* Voltage domain: VDD_IVA, Power domain: IVAHD, Functional clock domain = IVAHD */
	mod44xx_init_info(OMAP4_IVAHD, MOD_INTERFACE_DUAL, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_IVAHD_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.1, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_ICONT1, MOD_INTERFACE_DUAL, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_ICONT1_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.1, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_ICONT2, MOD_INTERFACE_DUAL, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_ICONT2_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.1, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_VDMA, MOD_INTERFACE_DUAL, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_ICONT1_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.1, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_IME3, MOD_INTERFACE_DUAL, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_IME3_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.1, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_IPE3, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_IPE3_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.1, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_ILF3, MOD_INTERFACE_DUAL, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_ILF3_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.1, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_MC3, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_MC3_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.1, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_CALC3, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_CALC3_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.1, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_ECD3, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_ECD3_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.1, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_ICONT1_SB, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_ICONT1_SB_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.1, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_ICONT2_SB, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_ICONT2_SB_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.1, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_ILF3_SB, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_ILF3_SB_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.1, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_IME3_SB, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_IME3_SB_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.1, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_CALC3_SB, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_CALC3_SB_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.1, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_IPE3_SB, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_IPE3_SB_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.1, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_MC3_SB, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_MC3_SB_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.1, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_ECD3_SB, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, OMAP4430_ECD3_SB_SYSCONFIG, (unsigned int *) OMAP4430_CM_IVAHD_IVAHD_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_IVAHD_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.1, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_SL2, MOD_INTERFACE_NONE, 0, OMAP4_CD_IVA_HD, OMAP4_PD_IVA_HD, OMAP4_VDD_IVA, NULL, (unsigned int *) OMAP4430_CM_IVAHD_SL2_CLKCTRL, (unsigned int *) OMAP4430_RM_IVAHD_SL2_CONTEXT, OMAP4_IVAHD_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 133.028580, 266.057159, 330.7, 430.1, 500.00002, -1.0});

	/* Voltage domain: VDD_IVA, Power domain: DSP, Functional clock domain = DSP */
	mod44xx_init_info(OMAP4_DSP, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_DSP, OMAP4_PD_DSP, OMAP4_VDD_IVA, OMAP4430_DSP_SYSC_SYSCONFIG, (unsigned int *) OMAP4430_CM_DSP_DSP_CLKCTRL, (unsigned int *) OMAP4430_RM_DSP_DSP_CONTEXT, OMAP4_DSP_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 232.8, 465.6, 496.0, 430.1, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_MMU_DSP, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_DSP, OMAP4_PD_DSP, OMAP4_VDD_IVA, OMAP4430_MMU_DSP_SYSCONFIG, (unsigned int *) OMAP4430_CM_DSP_DSP_CLKCTRL, (unsigned int *) OMAP4430_RM_DSP_DSP_CONTEXT, OMAP4_DSP_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 232.8, 465.6, 496.0, 430.1, 500.00002, -1.0});
	mod44xx_init_info(OMAP4_DSP_WUGEN, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_DSP, OMAP4_PD_ALWON_IVA, OMAP4_VDD_IVA, OMAP4430_DSP_WUGEN_SYSCONFIG, (unsigned int *) OMAP4430_CM_DSP_DSP_CLKCTRL, (unsigned int *) OMAP4430_RM_DSP_DSP_CONTEXT, OMAP4_DSP_ROOT_CLK, (double[OPP44XX_ID_MAX]) {98.304, 232.8, 465.6, 496.0, 430.1, 500.00002, -1.0});

	/* Voltage domain: VDD_CORE, Power domain: ALWON_CORE, Functional clock domain = AO_L4 */
	mod44xx_init_info(OMAP4_SMARTREFLEX_CORE, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_AO_L4, OMAP4_PD_ALWON_CORE, OMAP4_VDD_CORE, OMAP4430_ERRCONFIG_CORE, (unsigned int *) OMAP4430_CM_ALWON_SR_CORE_CLKCTRL, (unsigned int *) OMAP4430_RM_ALWON_SR_CORE_CONTEXT, OMAP4_SR_CORE_SYS_CLK, (double[OPP44XX_ID_MAX]) {12.288, 38.4, 38.4, 38.4, 38.4, 38.4, 38.4});
	mod44xx_init_info(OMAP4_SMARTREFLEX_MPU, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_AO_L4, OMAP4_PD_ALWON_CORE, OMAP4_VDD_CORE, OMAP4430_ERRCONFIG_MPU, (unsigned int *) OMAP4430_CM_ALWON_SR_MPU_CLKCTRL, (unsigned int *) OMAP4430_RM_ALWON_SR_MPU_CONTEXT, OMAP4_SR_MPU_SYS_CLK, (double[OPP44XX_ID_MAX]) {12.288, 38.4, 38.4, 38.4, 38.4, 38.4, 38.4});
	mod44xx_init_info(OMAP4_SMARTREFLEX_IVA, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_AO_L4, OMAP4_PD_ALWON_CORE, OMAP4_VDD_CORE, OMAP4430_ERRCONFIG_IVA, (unsigned int *) OMAP4430_CM_ALWON_SR_IVA_CLKCTRL, (unsigned int *) OMAP4430_RM_ALWON_SR_IVA_CONTEXT, OMAP4_SR_IVA_SYS_CLK, (double[OPP44XX_ID_MAX]) {12.288, 38.4, 38.4, 38.4, 38.4, 38.4, 38.4});

	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = L4CFG */
	mod44xx_init_info(OMAP4_L4_CFG, MOD_INTERFACE_NONE, 0, OMAP4_CD_L4CFG, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L4CFG_L4_CFG_CLKCTRL, (unsigned int *) OMAP4430_RM_L4CFG_L4_CFG_CONTEXT, OMAP4_CFG_L4_ICLK, (double[OPP44XX_ID_MAX]) {49.152, 50.0, 58.333336, 100.0, 100.0, 116.666672, 58.333336});
	mod44xx_init_info(OMAP4_CONTROL_GEN_CORE, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4CFG, OMAP4_PD_CORE, OMAP4_VDD_CORE, OMAP4430_CONTROL_GEN_CORE_SYSCONFIG, NULL, NULL, OMAP4_CFG_L4_ICLK, (double[OPP44XX_ID_MAX]) {49.152, 50.0, 58.333336, 100.0, 100.0, 116.666672, 58.333336});
	mod44xx_init_info(OMAP4_CONTROL_PADCONF_CORE, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4CFG, OMAP4_PD_CORE, OMAP4_VDD_CORE, OMAP4430_CONTROL_PADCONF_CORE_SYSCONFIG, NULL, NULL, OMAP4_CFG_L4_ICLK, (double[OPP44XX_ID_MAX]) {49.152, 50.0, 58.333336, 100.0, 100.0, 116.666672, 58.333336});
	mod44xx_init_info(OMAP4_SPINLOCK, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_L4CFG, OMAP4_PD_CORE, OMAP4_VDD_CORE, OMAP4430_SPINLOCK_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4CFG_HW_SEM_CLKCTRL, (unsigned int *) OMAP4430_RM_L4CFG_HW_SEM_CONTEXT, OMAP4_CFG_L4_ICLK, (double[OPP44XX_ID_MAX]) {49.152, 50.0, 58.333336, 100.0, 100.0, 116.666672, 58.333336});
	mod44xx_init_info(OMAP4_SYSTEM_MAILBOX, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4CFG, OMAP4_PD_CORE, OMAP4_VDD_CORE, OMAP4430_SYSTEM_MBX_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4CFG_MAILBOX_CLKCTRL, (unsigned int *) OMAP4430_RM_L4CFG_MAILBOX_CONTEXT, OMAP4_CFG_L4_ICLK, (double[OPP44XX_ID_MAX]) {49.152, 50.0, 58.333336, 100.0, 100.0, 116.666672, 58.333336});
	/* TODO: CHECK IF REGISTER ACCESSIBLE FROM MPU	mod44xx_init_info(OMAP4_IVAHD_MAILBOX, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4CFG, OMAP4_PD_CORE, OMAP4_VDD_CORE, OMAP4430_IVAHD_MBX_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4CFG_MAILBOX_CLKCTRL, (unsigned int *) OMAP4430_RM_L4CFG_MAILBOX_CONTEXT, OMAP4_UNDEF_CLK, 0.0); */
	mod44xx_init_info(OMAP4_SAR_ROM, MOD_INTERFACE_NONE, 0, OMAP4_CD_L4CFG, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L4CFG_SAR_ROM_CLKCTRL, (unsigned int *) OMAP4430_RM_L4CFG_SAR_ROM_CONTEXT, OMAP4_CFG_L4_ICLK, (double[OPP44XX_ID_MAX]) {49.152, 50.0, 58.333336, 100.0, 100.0, 116.666672, 58.333336});

	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = C2C */
	mod44xx_init_info(OMAP4_C2C, MOD_INTERFACE_NONE, 0, OMAP4_CD_C2C, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_C2C_C2C_CLKCTRL, (unsigned int *) OMAP4430_RM_C2C_C2C_CONTEXT, OMAP4_C2C_L3X2_ICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 116.666666, 200.0, 200.0, 233.333344, 116.666666});
	mod44xx_init_info(OMAP4_C2C_FW, MOD_INTERFACE_NONE, 0, OMAP4_CD_C2C, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_C2C_C2C_FW_CLKCTRL, (unsigned int *) OMAP4430_RM_C2C_C2C_FW_CONTEXT, OMAP4_C2C_L3_ICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 116.666666, 200.0, 200.0, 233.333344, 116.666666});
	mod44xx_init_info(OMAP4_ICR_MDM, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_C2C, OMAP4_PD_CORE, OMAP4_VDD_CORE, OMAP4430_ICR_MDM_SYS_CONFIG, NULL, NULL, OMAP4_C2C_L4_ICLK, (double[OPP44XX_ID_MAX]) {49.152, 50.0, 58.333336, 100.0, 100.0, 116.666672, 58.333336});
	mod44xx_init_info(OMAP4_ICR_MPU, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_C2C, OMAP4_PD_CORE, OMAP4_VDD_CORE, OMAP4430_ICR_MPU_SYS_CONFIG, NULL, NULL, OMAP4_C2C_L4_ICLK, (double[OPP44XX_ID_MAX]) {49.152, 50.0, 58.333336, 100.0, 100.0, 116.666672, 58.333336});

	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = DMA */
	mod44xx_init_info(OMAP4_SDMA, MOD_INTERFACE_DUAL, 1, OMAP4_CD_DMA, OMAP4_PD_CORE, OMAP4_VDD_CORE, OMAP4430_DMA4_SYSCONFIG, (unsigned int *) OMAP4430_CM_SDMA_SDMA_CLKCTRL, (unsigned int *) OMAP4430_RM_SDMA_SDMA_CONTEXT, OMAP4_DMA_L3_ICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 116.666666, 200.0, 200.0, 233.333344, 116.666666});

	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = MPU_M3 */
	mod44xx_init_info(OMAP4_MPU_M3, MOD_INTERFACE_NONE, 0, OMAP4_CD_MPU_M3, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_MPU_M3_MPU_M3_CLKCTRL, (unsigned int *) OMAP4430_RM_MPU_M3_MPU_M3_CONTEXT, OMAP4_MPU_M3_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 233.33334, 400.0, 400.0, 466.666687, 233.33334});
	/* TODO: FURTHER CHECK 	mod44xx_init_info(OMAP4_MPU_M3_WUGEN, MOD_INTERFACE_DUAL, 0, OMAP4_CD_MPU_M3, OMAP4_PD_ALWON_CORE, OMAP4_VDD_CORE, OMAP4430_MPU_M3_WUGEN_SYSCONFIG, (unsigned int *) OMAP4430_CM_MPU_M3_MPU_M3_CLKCTRL, (unsigned int *) OMAP4430_RM_MPU_M3_MPU_M3_CONTEXT, OMAP4_UNDEF_CLK, (double[OPP44XX_ID_MAX]) {0.0); */

	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = NONE */
	/* TODO: FURTHER CHECK WHEN MODULE IS ACCESSIBLE	mod44xx_init_info(OMAP4_MMU_MPU_M3, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_NONE, OMAP4_PD_CORE, OMAP4_VDD_CORE, OMAP4430_MMU_MPU_M3_SYSCONFIG, NULL, NULL, OMAP4_UNDEF_CLK, (double[OPP44XX_ID_MAX]) {0.0); */

	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = L3_1 */
	mod44xx_init_info(OMAP4_L3_1, MOD_INTERFACE_NONE, 0, OMAP4_CD_L3_1, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L3_1_L3_1_CLKCTRL, (unsigned int *) OMAP4430_RM_L3_1_L3_1_CONTEXT, OMAP4_L3_ICLK1, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 116.666666, 200.0, 200.0, 233.333344, 116.666666});

	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = L3_2 */
	mod44xx_init_info(OMAP4_L3_2, MOD_INTERFACE_NONE, 0, OMAP4_CD_L3_2, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L3_2_L3_2_CLKCTRL, (unsigned int *) OMAP4430_RM_L3_2_L3_2_CONTEXT, OMAP4_L3_ICLK2, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 116.666666, 200.0, 200.0, 233.333344, 116.666666});
	mod44xx_init_info(OMAP4_GPMC, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L3_2, OMAP4_PD_CORE, OMAP4_VDD_CORE, OMAP4430_GPMC_SYSCONFIG, (unsigned int *) OMAP4430_CM_L3_2_GPMC_CLKCTRL, (unsigned int *) OMAP4430_RM_L3_2_GPMC_CONTEXT, OMAP4_L3_ICLK2, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 116.666666, 200.0, 200.0, 233.333344, 116.666666});
	mod44xx_init_info(OMAP4_OCMC_RAM, MOD_INTERFACE_NONE, 0, OMAP4_CD_L3_2, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L3_2_OCMC_RAM_CLKCTRL, (unsigned int *) OMAP4430_RM_L3_2_OCMC_RAM_CONTEXT, OMAP4_L3_ICLK2, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 116.666666, 200.0, 200.0, 233.333344, 116.666666});

	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = L3_INSTR */
	mod44xx_init_info(OMAP4_L3_3, MOD_INTERFACE_NONE, 0, OMAP4_CD_L3_INSTR, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L3INSTR_L3_3_CLKCTRL, (unsigned int *) OMAP4430_RM_L3INSTR_L3_3_CONTEXT, OMAP4_L3_INSTR_GICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 116.666666, 200.0, 200.0, 233.333344, 116.666666});
	mod44xx_init_info(OMAP4_L3_INSTR, MOD_INTERFACE_NONE, 0, OMAP4_CD_L3_INSTR, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L3INSTR_L3_INSTR_CLKCTRL, (unsigned int *) OMAP4430_RM_L3INSTR_L3_INSTR_CONTEXT, OMAP4_L3_INSTR_GICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 116.666666, 200.0, 200.0, 233.333344, 116.666666});
	mod44xx_init_info(OMAP4_OCP_WP1, MOD_INTERFACE_NONE, 0, OMAP4_CD_L3_INSTR, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L3INSTR_OCP_WP1_CLKCTRL, (unsigned int *) OMAP4430_RM_L3INSTR_OCP_WP1_CONTEXT, OMAP4_L3_INSTR_GICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 116.666666, 200.0, 200.0, 233.333344, 116.666666});

	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = EMIF */
	mod44xx_init_info(OMAP4_DMM, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_EMIF, OMAP4_PD_CORE, OMAP4_VDD_CORE, OMAP4430_DMM_SYSCONFIG, (unsigned int *) OMAP4430_CM_MEMIF_DMM_CLKCTRL, (unsigned int *) OMAP4430_RM_MEMIF_DMM_CONTEXT, OMAP4_EMIF_L3_ICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 116.666666, 200.0, 200.0, 233.333344, 116.666666});
	mod44xx_init_info(OMAP4_EMIF_FW, MOD_INTERFACE_NONE, 0, OMAP4_CD_EMIF, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_MEMIF_EMIF_FW_CLKCTRL, (unsigned int *) OMAP4430_RM_MEMIF_EMIF_FW_CONTEXT, OMAP4_EMIF_L3_ICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 116.666666, 200.0, 200.0, 233.333344, 116.666666});
	mod44xx_init_info(OMAP4_EMIF1, MOD_INTERFACE_NONE, 0, OMAP4_CD_EMIF, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_MEMIF_EMIF_1_CLKCTRL, (unsigned int *) OMAP4430_RM_MEMIF_EMIF_1_CONTEXT, OMAP4_EMIF_L3_ICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 116.666666, 200.0, 200.0, 233.333344, 116.666666});
	mod44xx_init_info(OMAP4_EMIF2, MOD_INTERFACE_NONE, 0, OMAP4_CD_EMIF, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_MEMIF_EMIF_2_CLKCTRL, (unsigned int *) OMAP4430_RM_MEMIF_EMIF_2_CONTEXT, OMAP4_EMIF_L3_ICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 116.666666, 200.0, 200.0, 233.333344, 116.666666});
	mod44xx_init_info(OMAP4_DDRPHY, MOD_INTERFACE_NONE, 0, OMAP4_CD_EMIF, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, NULL, NULL, OMAP4_PHY_ROOT_CLK, (double[OPP44XX_ID_MAX]) {196.608, 400.0, 466.0, 800.0, 400.0, 931.2, 465.6});
	mod44xx_init_info(OMAP4_DLL, MOD_INTERFACE_NONE, 0, OMAP4_CD_EMIF, OMAP4_PD_CORE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_MEMIF_DLL_CLKCTRL, (unsigned int *) OMAP4430_RM_MEMIF_DLL_CONTEXT, OMAP4_DLL_CLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 116.666672, 100.0, 100.0, 116.666672, 116.666666});

	/* Voltage domain: VDD_CORE, Power domain: STD_EFUSE, Functional clock domain = STD_EFUSE */
	mod44xx_init_info(OMAP4_STD_EFUSE, MOD_INTERFACE_NONE, 0, OMAP4_CD_STD_EFUSE, OMAP4_PD_STD_EFUSE, OMAP4_VDD_CORE, NULL, NULL, NULL, OMAP4_STD_EFUSE_SYS_CLK, (double[OPP44XX_ID_MAX]) {-1.0, 38.4, 38.4, 38.4, 38.4, 38.4, 38.4});

	/* Voltage domain: VDD_CORE, Power domain: CUST_EFUSE, Functional clock domain = CUST_EFUSE */
	/* HS/EMU device only */
	mod44xx_init_info(OMAP4_CUST_EFUSE, MOD_INTERFACE_NONE, 0, OMAP4_CD_CUST_EFUSE, OMAP4_PD_CUST_EFUSE, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_CEFUSE_CEFUSE_CLKCTRL, (unsigned int *) OMAP4430_RM_CEFUSE_CEFUSE_CONTEXT, OMAP4_CUST_EFUSE_SYS_CLK, (double[OPP44XX_ID_MAX]) {-1.0, 38.4, 38.4, 38.4, 38.4, 38.4, 38.4});
	/* end of HS/EMU device only */

	/* Voltage domain: VDD_CORE, Power domain: ALWON_CORE, Functional clock domain = NONE */

	/* Voltage domain: VDD_CORE, Power domain: ALWON_CORE, Functional clock domain = NONE */

	/* Voltage domain: VDD_CORE, Power domain: CORE, Functional clock domain = NONE */

	/* Voltage domain: VDD_CORE, Power domain: CAM, Functional clock domain = CAM */
	mod44xx_init_info(OMAP4_ISS, MOD_INTERFACE_DUAL, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_ISS_HL_SYSCONFIG, (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT, OMAP4_ISS_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 233.33334, 400.0, 400.0, 466.666687, 233.33334});
	mod44xx_init_info(OMAP4_CCP2, MOD_INTERFACE_MASTER, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_CCP2_SYSCONFIG, (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT, OMAP4_ISS_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 233.33334, 400.0, 400.0, 466.666687, 233.33334});
	mod44xx_init_info(OMAP4_CSI2_A, MOD_INTERFACE_MASTER, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_CSI2_A_SYSCONFIG, (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT, OMAP4_ISS_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 233.33334, 400.0, 400.0, 466.666687, 233.33334});
	mod44xx_init_info(OMAP4_CSI2_B, MOD_INTERFACE_MASTER, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_CSI2_B_SYSCONFIG, (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT, OMAP4_ISS_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 233.33334, 400.0, 400.0, 466.666687, 233.33334});
	mod44xx_init_info(OMAP4_TCTRL, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_TCTRL_SYSCONFIG, (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT, OMAP4_ISS_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 233.33334, 400.0, 400.0, 466.666687, 233.33334});
	mod44xx_init_info(OMAP4_BTE, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_BTE_HL_SYSCONFIG, (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT, OMAP4_ISS_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 233.33334, 400.0, 400.0, 466.666687, 233.33334});
	mod44xx_init_info(OMAP4_CBUFF, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_CBUFF_HL_SYSCONFIG, (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT, OMAP4_ISS_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 233.33334, 400.0, 400.0, 466.666687, 233.33334});
	mod44xx_init_info(OMAP4_ISP5, MOD_INTERFACE_MASTER, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_ISP5_SYSCONFIG, (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT, OMAP4_ISS_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 233.33334, 400.0, 400.0, 466.666687, 233.33334});
	mod44xx_init_info(OMAP4_RSZ, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_RSZ_SYSCONFIG, (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT, OMAP4_ISS_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 233.33334, 400.0, 400.0, 466.666687, 233.33334});
	mod44xx_init_info(OMAP4_SIMCOP, MOD_INTERFACE_MASTER, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_SIMCOP_HL_SYSCONFIG, (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT, OMAP4_ISS_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 233.33334, 400.0, 400.0, 466.666687, 233.33334});
	mod44xx_init_info(OMAP4_SIMCOP_DMA, MOD_INTERFACE_MASTER, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_SIMCOP_DMA_SYSCONFIG, (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT, OMAP4_ISS_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 233.33334, 400.0, 400.0, 466.666687, 233.33334});
	mod44xx_init_info(OMAP4_SIMCOP_DCT, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_SIMCOP_DCT_CFG, (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT, OMAP4_ISS_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 233.33334, 400.0, 400.0, 466.666687, 233.33334});
	mod44xx_init_info(OMAP4_SIMCOP_VLCDJ, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_SIMCOP_VLCDJ_CTRL, (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT, OMAP4_ISS_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 233.33334, 400.0, 400.0, 466.666687, 233.33334});
	mod44xx_init_info(OMAP4_SIMCOP_ROT, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_SIMCOP_ROT_CFG, (unsigned int *) OMAP4430_CM_CAM_ISS_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_ISS_CONTEXT, OMAP4_ISS_CLK, (double[OPP44XX_ID_MAX]) {196.608, 200.0, 233.33334, 400.0, 400.0, 466.666687, -1.0});
	mod44xx_init_info(OMAP4_FDIF, MOD_INTERFACE_DUAL, 0, OMAP4_CD_CAM, OMAP4_PD_CAM, OMAP4_VDD_CORE, OMAP4430_FDIF_SYSCONFIG, (unsigned int *) OMAP4430_CM_CAM_FDIF_CLKCTRL, (unsigned int *) OMAP4430_RM_CAM_FDIF_CONTEXT, OMAP4_FDIF_FCLK, (double[OPP44XX_ID_MAX]) {-1.0, 64.0, 128.0, 128.0, 128.0, 128.0, 128.0});

	/* Voltage domain: VDD_CORE, Power domain: DSS, Functional clock domain = DSS */
	mod44xx_init_info(OMAP4_DISPC, MOD_INTERFACE_DUAL, 0, OMAP4_CD_DSS, OMAP4_PD_DSS, OMAP4_VDD_CORE, OMAP4430_DISPC_SYSCONFIG, (unsigned int *) OMAP4430_CM_DSS_DSS_CLKCTRL, (unsigned int *) OMAP4430_RM_DSS_DSS_CONTEXT, OMAP4_DSS_FCLK, (double[OPP44XX_ID_MAX]) {98.304, 170.666673, 85.333335, 170.666673, 170.666673, 170.666673, 170.666673});
	mod44xx_init_info(OMAP4_DSI1, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_DSS, OMAP4_PD_DSS, OMAP4_VDD_CORE, OMAP4430_DSI1_SYSCONFIG, (unsigned int *) OMAP4430_CM_DSS_DSS_CLKCTRL, (unsigned int *) OMAP4430_RM_DSS_DSS_CONTEXT, OMAP4_DSS_FCLK, (double[OPP44XX_ID_MAX]) {98.304, 170.666673, 85.333335, 170.666673, 170.666673, 170.666673, 170.666673});
	mod44xx_init_info(OMAP4_DSI2, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_DSS, OMAP4_PD_DSS, OMAP4_VDD_CORE, OMAP4430_DSI2_SYSCONFIG, (unsigned int *) OMAP4430_CM_DSS_DSS_CLKCTRL, (unsigned int *) OMAP4430_RM_DSS_DSS_CONTEXT, OMAP4_DSS_FCLK, (double[OPP44XX_ID_MAX]) {98.304, 170.666673, 85.333335, 170.666673, 170.666673, 170.666673, 170.666673});
	mod44xx_init_info(OMAP4_HDMI, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_DSS, OMAP4_PD_DSS, OMAP4_VDD_CORE, OMAP4430_HDMI_WP_SYSCONFIG, (unsigned int *) OMAP4430_CM_DSS_DSS_CLKCTRL, (unsigned int *) OMAP4430_RM_DSS_DSS_CONTEXT, OMAP4_HDMI_PHY_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, 48.0, 48.0, 48.0, 48.0});
	mod44xx_init_info(OMAP4_RFBI, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_DSS, OMAP4_PD_DSS, OMAP4_VDD_CORE, OMAP4430_RFBI_SYSCONFIG, (unsigned int *) OMAP4430_CM_DSS_DSS_CLKCTRL, (unsigned int *) OMAP4430_RM_DSS_DSS_CONTEXT, OMAP4_UNDEF_CLK, (double[OPP44XX_ID_MAX]) {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0});
	mod44xx_init_info(OMAP4_BB2D, MOD_INTERFACE_NONE, 0, OMAP4_CD_DSS, OMAP4_PD_DSS, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_DSS_BB2D_CLKCTRL, (unsigned int *) OMAP4430_RM_DSS_BB2D_CONTEXT, OMAP4_BB2D_FCLK, (double[OPP44XX_ID_MAX]) {0.0, 192.000008, 192.000008, 307.2, 384.0, 384.0, 307.2});

	/* Voltage domain: VDD_CORE, Power domain: GFX, Functional clock domain = GFX */
	mod44xx_init_info(OMAP4_GFX, MOD_INTERFACE_DUAL, 0, OMAP4_CD_GFX, OMAP4_PD_GFX, OMAP4_VDD_CORE, OMAP4430_GFX_SYSCONFIG, (unsigned int *) OMAP4430_CM_GFX_GFX_CLKCTRL, (unsigned int *) OMAP4430_RM_GFX_GFX_CONTEXT, OMAP4_GFX_FCLK, (double[OPP44XX_ID_MAX]) {98.304, 153.6, 192.000008, 307.2, 384.0, 384.0, 307.2});

	/* Voltage domain: VDD_CORE, Power domain: L3_INIT, Functional clock domain = L3_INIT */
	mod44xx_init_info(OMAP4_MMC1, MOD_INTERFACE_DUAL, 1, OMAP4_CD_L3_INIT, OMAP4_PD_L3_INIT, OMAP4_VDD_CORE, OMAP4430_HSMMC1_SYSCONFIG, (unsigned int *) OMAP4430_CM_L3INIT_MMC1_CLKCTRL, (unsigned int *) OMAP4430_RM_L3INIT_MMC1_CONTEXT, OMAP4_MMC1_FCLK, (double[OPP44XX_ID_MAX]) {49.152, 96.0, 96.0, 96.0, 96.0, 96.0, 96.0});
	mod44xx_init_info(OMAP4_MMC1_HL, MOD_INTERFACE_DUAL, 0, OMAP4_CD_L3_INIT, OMAP4_PD_L3_INIT, OMAP4_VDD_CORE, OMAP4430_HSMMC1_HL_SYSCONFIG, (unsigned int *) OMAP4430_CM_L3INIT_MMC1_CLKCTRL, (unsigned int *) OMAP4430_RM_L3INIT_MMC1_CONTEXT, OMAP4_MMC1_FCLK, (double[OPP44XX_ID_MAX]) {49.152, 96.0, 96.0, 96.0, 96.0, 96.0, 96.0});
	mod44xx_init_info(OMAP4_MMC2, MOD_INTERFACE_DUAL, 1, OMAP4_CD_L3_INIT, OMAP4_PD_L3_INIT, OMAP4_VDD_CORE, OMAP4430_HSMMC2_SYSCONFIG, (unsigned int *) OMAP4430_CM_L3INIT_MMC2_CLKCTRL, (unsigned int *) OMAP4430_RM_L3INIT_MMC2_CONTEXT, OMAP4_MMC2_FCLK, (double[OPP44XX_ID_MAX]) {49.152, 96.0, 96.0, 96.0, 96.0, 96.0, 96.0});
	mod44xx_init_info(OMAP4_MMC2_HL, MOD_INTERFACE_DUAL, 0, OMAP4_CD_L3_INIT, OMAP4_PD_L3_INIT, OMAP4_VDD_CORE, OMAP4430_HSMMC2_HL_SYSCONFIG, (unsigned int *) OMAP4430_CM_L3INIT_MMC2_CLKCTRL, (unsigned int *) OMAP4430_RM_L3INIT_MMC2_CONTEXT, OMAP4_MMC2_FCLK, (double[OPP44XX_ID_MAX]) {49.152, 96.0, 96.0, 96.0, 96.0, 96.0, 96.0});
	mod44xx_init_info(OMAP4_HSI, MOD_INTERFACE_DUAL, 0, OMAP4_CD_L3_INIT, OMAP4_PD_L3_INIT, OMAP4_VDD_CORE, OMAP4430_HSI_SYSCONFIG, (unsigned int *) OMAP4430_CM_L3INIT_HSI_CLKCTRL, (unsigned int *) OMAP4430_RM_L3INIT_HSI_CONTEXT, OMAP4_HSI_FCLK, (double[OPP44XX_ID_MAX]) {-1.0, 96.0, 96.0, 96.0, 96.0, 96.0, 96.0});
	mod44xx_init_info(OMAP4_HSUSBHOST, MOD_INTERFACE_DUAL, 0, OMAP4_CD_L3_INIT, OMAP4_PD_L3_INIT, OMAP4_VDD_CORE, OMAP4430_UHH_SYSCONFIG, (unsigned int *) OMAP4430_CM_L3INIT_USB_HOST_CLKCTRL, (unsigned int *) OMAP4430_RM_L3INIT_USB_HOST_CONTEXT, OMAP4_INIT_48MC_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, 48.0, 48.0, 48.0, 48.0});
	mod44xx_init_info(OMAP4_HSUSBOTG, MOD_INTERFACE_DUAL, 0, OMAP4_CD_L3_INIT, OMAP4_PD_L3_INIT, OMAP4_VDD_CORE, OMAP4430_HSUSBOTG_SYSCONFIG, (unsigned int *) OMAP4430_CM_L3INIT_USB_OTG_CLKCTRL, (unsigned int *) OMAP4430_RM_L3INIT_USB_OTG_CONTEXT, OMAP4_OTG_60M_FCLK, (double[OPP44XX_ID_MAX]) {-1.0, 60.0, 60.0, 60.0, 60.0, 60.0, 60.0});
	mod44xx_init_info(OMAP4_USBTLL, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L3_INIT, OMAP4_PD_L3_INIT, OMAP4_VDD_CORE, OMAP4430_USBTLL_SYSCONFIG, (unsigned int *) OMAP4430_CM_L3INIT_USB_TLL_CLKCTRL, (unsigned int *) OMAP4430_RM_L3INIT_USB_TLL_CONTEXT, OMAP4_INIT_60M_FCLK, (double[OPP44XX_ID_MAX]) {60.0, 60.0, 60.0, 60.0, 60.0, 60.0, 60.0});
	mod44xx_init_info(OMAP4_P1500, MOD_INTERFACE_NONE, 0, OMAP4_CD_L3_INIT, OMAP4_PD_L3_INIT, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L3INIT_P1500_CLKCTRL, (unsigned int *) OMAP4430_RM_L3INIT_P1500_CONTEXT, OMAP4_INIT_L3_ICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 233.333344, 200.0, 233.333344, 233.333344, 233.333344});
	mod44xx_init_info(OMAP4_FSUSBHOST, MOD_INTERFACE_NONE, 0, OMAP4_CD_L3_INIT, OMAP4_PD_L3_INIT, OMAP4_VDD_CORE, NULL, NULL, NULL, OMAP4_UNDEF_CLK, (double[OPP44XX_ID_MAX]) {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0});
	mod44xx_init_info(OMAP4_USBPHY, MOD_INTERFACE_NONE, 0, OMAP4_CD_L3_INIT, OMAP4_PD_L3_INIT, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L3INIT_USBPHYOCP2SCP_CLKCTRL, (unsigned int *) OMAP4430_RM_L3INIT_USBPHYOCP2SCP_CONTEXT, OMAP4_INIT_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, 48.0, 48.0, 48.0, 48.0});

	/* Voltage domain: VDD_CORE, Power domain: L3_INIT, Functional clock domain = NONE */

	/* Voltage domain: VDD_CORE, Power domain: L4_PER, Functional clock domain = L4_SEC */
	/* HS/EMU device only, not accessible for non-secure world */
	mod44xx_init_info(OMAP4_CRYPTODMA, MOD_INTERFACE_NONE, 1, OMAP4_CD_L4_SEC, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L4SEC_CRYPTODMA_CLKCTRL, (unsigned int *) OMAP4430_RM_L4SEC_CRYPTODMA_CONTEXT, OMAP4_L3_SECURE_GICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 233.333344, 200.0, 233.333344, 233.333344, 233.333344});
	mod44xx_init_info(OMAP4_AES1, MOD_INTERFACE_NONE, 0, OMAP4_CD_L4_SEC, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L4SEC_AES1_CLKCTRL, (unsigned int *) OMAP4430_RM_L4SEC_AES1_CONTEXT, OMAP4_L3_SECURE_GICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 233.333344, 200.0, 233.333344, 233.333344, 233.333344});
	mod44xx_init_info(OMAP4_AES2, MOD_INTERFACE_NONE, 0, OMAP4_CD_L4_SEC, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L4SEC_AES2_CLKCTRL, (unsigned int *) OMAP4430_RM_L4SEC_AES2_CONTEXT, OMAP4_L3_SECURE_GICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 233.333344, 200.0, 233.333344, 233.333344, 233.333344});
	mod44xx_init_info(OMAP4_SHA2MD5_1, MOD_INTERFACE_NONE, 0, OMAP4_CD_L4_SEC, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L4SEC_SHA2MD51_CLKCTRL, (unsigned int *) OMAP4430_RM_L4SEC_SHA2MD51_CONTEXT, OMAP4_L3_SECURE_GICLK, (double[OPP44XX_ID_MAX]) {98.304, 100.0, 233.333344, 200.0, 233.333344, 233.333344, 233.333344});
	mod44xx_init_info(OMAP4_RNG, MOD_INTERFACE_NONE, 0, OMAP4_CD_L4_SEC, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L4SEC_RNG_CLKCTRL, (unsigned int *) OMAP4430_RM_L4SEC_RNG_CONTEXT, OMAP4_L4_SECURE_GICLK, (double[OPP44XX_ID_MAX]) {49.152, 50.0, 58.333336, 100.0, 100.0, 116.666672, 58.333336});
	mod44xx_init_info(OMAP4_DES3DES, MOD_INTERFACE_NONE, 0, OMAP4_CD_L4_SEC, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L4SEC_DES3DES_CLKCTRL, (unsigned int *) OMAP4430_RM_L4SEC_DES3DES_CONTEXT, OMAP4_L4_SECURE_GICLK, (double[OPP44XX_ID_MAX]) {49.152, 50.0, 58.333336, 100.0, 100.0, 116.666672, 58.333336});
	mod44xx_init_info(OMAP4_PKAEIP29, MOD_INTERFACE_NONE, 0, OMAP4_CD_L4_SEC, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L4SEC_PKAEIP29_CLKCTRL, (unsigned int *) OMAP4430_RM_L4SEC_PKAEIP29_CONTEXT, OMAP4_L4_SECURE_GICLK, (double[OPP44XX_ID_MAX]) {49.152, 50.0, 58.333336, 100.0, 100.0, 116.666672, 58.333336});
	/* end of HS/EMU device only */

	/* Voltage domain: VDD_CORE, Power domain: L4_PER, Functional clock domain = L4_PER */
	mod44xx_init_info(OMAP4_TIMER10, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_GPT10_TIOCP_CFG, (unsigned int *) OMAP4430_CM_L4PER_DMTIMER10_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_DMTIMER10_CONTEXT, OMAP4_GPT10_FCLK, (double[OPP44XX_ID_MAX]) {38.4, 38.4, 38.4, 38.4, 38.4, 38.4, 38.4});
	mod44xx_init_info(OMAP4_TIMER11, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_GPT11_TIOCP_CFG, (unsigned int *) OMAP4430_CM_L4PER_DMTIMER11_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_DMTIMER11_CONTEXT, OMAP4_GPT11_FCLK, (double[OPP44XX_ID_MAX]) {38.4, 38.4, 38.4, 38.4, 38.4, 38.4, 38.4});
	mod44xx_init_info(OMAP4_TIMER2, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_GPT2_TIOCP_CFG, (unsigned int *) OMAP4430_CM_L4PER_DMTIMER2_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_DMTIMER2_CONTEXT, OMAP4_GPT2_FCLK, (double[OPP44XX_ID_MAX]) {38.4, 38.4, 38.4, 38.4, 38.4, 38.4, 38.4});
	mod44xx_init_info(OMAP4_TIMER3, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_GPT3_TIOCP_CFG, (unsigned int *) OMAP4430_CM_L4PER_DMTIMER3_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_DMTIMER3_CONTEXT, OMAP4_GPT3_FCLK, (double[OPP44XX_ID_MAX]) {38.4, 38.4, 38.4, 38.4, 38.4, 38.4, 38.4});
	mod44xx_init_info(OMAP4_TIMER4, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_GPT4_TIOCP_CFG, (unsigned int *) OMAP4430_CM_L4PER_DMTIMER4_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_DMTIMER4_CONTEXT, OMAP4_GPT4_FCLK, (double[OPP44XX_ID_MAX]) {38.4, 38.4, 38.4, 38.4, 38.4, 38.4, 38.4});
	mod44xx_init_info(OMAP4_TIMER9, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_GPT9_TIOCP_CFG, (unsigned int *) OMAP4430_CM_L4PER_DMTIMER9_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_DMTIMER9_CONTEXT, OMAP4_GPT9_FCLK, (double[OPP44XX_ID_MAX]) {38.4, 38.4, 38.4, 38.4, 38.4, 38.4, 38.4});
	mod44xx_init_info(OMAP4_ELM, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_ELM_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_ELM_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_ELM_CONTEXT, OMAP4_PER_L4_ICLK, (double[OPP44XX_ID_MAX]) {49.152, 50.0, 58.333336, 100.0, 100.0, 116.666672, 58.333336});
	mod44xx_init_info(OMAP4_GPIO2, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_GPIO2_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_GPIO2_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_GPIO2_CONTEXT, OMAP4_PER_32K_GFCLK, (double[OPP44XX_ID_MAX]) {0.032768, 0.032768, 0.032768, 0.032768, 0.032768, 0.032768, 0.032768});
	mod44xx_init_info(OMAP4_GPIO3, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_GPIO3_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_GPIO3_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_GPIO3_CONTEXT, OMAP4_PER_32K_GFCLK, (double[OPP44XX_ID_MAX]) {0.032768, 0.032768, 0.032768, 0.032768, 0.032768, 0.032768, 0.032768});
	mod44xx_init_info(OMAP4_GPIO4, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_GPIO4_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_GPIO4_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_GPIO4_CONTEXT, OMAP4_PER_32K_GFCLK, (double[OPP44XX_ID_MAX]) {0.032768, 0.032768, 0.032768, 0.032768, 0.032768, 0.032768, 0.032768});
	mod44xx_init_info(OMAP4_GPIO5, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_GPIO5_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_GPIO5_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_GPIO5_CONTEXT, OMAP4_PER_32K_GFCLK, (double[OPP44XX_ID_MAX]) {0.032768, 0.032768, 0.032768, 0.032768, 0.032768, 0.032768, 0.032768});
	mod44xx_init_info(OMAP4_GPIO6, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_GPIO6_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_GPIO6_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_GPIO6_CONTEXT, OMAP4_PER_32K_GFCLK, (double[OPP44XX_ID_MAX]) {0.032768, 0.032768, 0.032768, 0.032768, 0.032768, 0.032768, 0.032768});
	mod44xx_init_info(OMAP4_HDQ1W, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_HDQ_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_HDQ1W_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_HDQ1W_CONTEXT, OMAP4_12M_FCLK, (double[OPP44XX_ID_MAX]) {6.144, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0});
	mod44xx_init_info(OMAP4_I2C1, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_I2C1_SYSC, (unsigned int *) OMAP4430_CM_L4PER_I2C1_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_I2C1_CONTEXT, OMAP4_PER_96M_FCLK, (double[OPP44XX_ID_MAX]) {49.152, 96.0, 96.0, 96.0, 96.0, 96.0, 96.0});
	mod44xx_init_info(OMAP4_I2C2, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_I2C2_SYSC, (unsigned int *) OMAP4430_CM_L4PER_I2C2_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_I2C2_CONTEXT, OMAP4_PER_96M_FCLK, (double[OPP44XX_ID_MAX]) {49.152, 96.0, 96.0, 96.0, 96.0, 96.0, 96.0});
	mod44xx_init_info(OMAP4_I2C3, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_I2C3_SYSC, (unsigned int *) OMAP4430_CM_L4PER_I2C3_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_I2C3_CONTEXT, OMAP4_PER_96M_FCLK, (double[OPP44XX_ID_MAX]) {49.152, 96.0, 96.0, 96.0, 96.0, 96.0, 96.0});
	mod44xx_init_info(OMAP4_I2C4, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_I2C4_SYSC, (unsigned int *) OMAP4430_CM_L4PER_I2C4_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_I2C4_CONTEXT, OMAP4_PER_96M_FCLK, (double[OPP44XX_ID_MAX]) {49.152, 96.0, 96.0, 96.0, 96.0, 96.0, 96.0});
	mod44xx_init_info(OMAP4_L4_PER, MOD_INTERFACE_NONE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, NULL, (unsigned int *) OMAP4430_CM_L4PER_L4PER_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_L4_PER_CONTEXT, OMAP4_L4_ICLK, (double[OPP44XX_ID_MAX]) {49.152, 50.0, 58.333336, 100.0, 100.0, 116.666672, 58.333336});
	mod44xx_init_info(OMAP4_MCBSP4, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MCBSP4_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MCBSP4_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MCBSP4_CONTEXT, OMAP4_PER_MCBSP4_FCLK, (double[OPP44XX_ID_MAX]) {49.152, 96.0, 96.0, 96.0, 96.0, 96.0, 96.0});
	mod44xx_init_info(OMAP4_MCSPI1_HL, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MCSPI1_HL_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MCSPI1_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MCSPI1_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, 48.0, 48.0, 48.0, 48.0});
	mod44xx_init_info(OMAP4_MCSPI1, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MCSPI1_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MCSPI1_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MCSPI1_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, 48.0, 48.0, 48.0, 48.0});
	mod44xx_init_info(OMAP4_MCSPI2_HL, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MCSPI2_HL_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MCSPI2_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MCSPI2_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, 48.0, 48.0, 48.0, 48.0});
	mod44xx_init_info(OMAP4_MCSPI2, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MCSPI2_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MCSPI2_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MCSPI2_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, 48.0, 48.0, 48.0, 48.0});
	mod44xx_init_info(OMAP4_MCSPI3_HL, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MCSPI3_HL_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MCSPI3_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MCSPI3_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, 48.0, 48.0, 48.0, 48.0});
	mod44xx_init_info(OMAP4_MCSPI3, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MCSPI3_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MCSPI3_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MCSPI3_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, 48.0, 48.0, 48.0, 48.0});
	mod44xx_init_info(OMAP4_MCSPI4_HL, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MCSPI4_HL_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MCSPI4_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MCSPI4_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, 48.0, 48.0, 48.0, 48.0});
	mod44xx_init_info(OMAP4_MCSPI4, MOD_INTERFACE_SLAVE, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MCSPI4_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MCSPI4_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MCSPI4_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, 48.0, 48.0, 48.0, 48.0});
	mod44xx_init_info(OMAP4_MMC3, MOD_INTERFACE_DUAL, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MMCHS3_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MMCSD3_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MMCSD3_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, 48.0, 48.0, 48.0, 48.0});
	mod44xx_init_info(OMAP4_MMC3_HL, MOD_INTERFACE_DUAL, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MMCHS3_HL_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MMCSD3_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MMCSD3_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, 48.0, 48.0, 48.0, 48.0});
	mod44xx_init_info(OMAP4_MMC4, MOD_INTERFACE_DUAL, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MMCHS4_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MMCSD4_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MMCSD4_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, 48.0, 48.0, 48.0, 48.0});
	mod44xx_init_info(OMAP4_MMC4_HL, MOD_INTERFACE_DUAL, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MMCHS4_HL_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MMCSD4_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MMCSD4_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, 48.0, 48.0, 48.0, 48.0});
	mod44xx_init_info(OMAP4_SLIMBUS2, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_SLIMBUS2_CMP_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_SLIMBUS2_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_SLIMBUS2_CONTEXT, OMAP4_SLIMBUS_CORE_UCLKS, (double[OPP44XX_ID_MAX]) {24.576, 24.576, 24.576, 24.576, 24.576, 24.576, 24.576});
	mod44xx_init_info(OMAP4_UART1, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_UART1_SYSC, (unsigned int *) OMAP4430_CM_L4PER_UART1_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_UART1_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, 48.0, 48.0, 48.0, 48.0});
	mod44xx_init_info(OMAP4_UART2, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_UART2_SYSC, (unsigned int *) OMAP4430_CM_L4PER_UART2_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_UART2_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, 48.0, 48.0, 48.0, 48.0});
	mod44xx_init_info(OMAP4_UART3, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_UART3_SYSC, (unsigned int *) OMAP4430_CM_L4PER_UART3_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_UART3_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, 48.0, 48.0, 48.0, 48.0});
	mod44xx_init_info(OMAP4_UART4, MOD_INTERFACE_SLAVE, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_UART4_SYSC, (unsigned int *) OMAP4430_CM_L4PER_UART4_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_UART4_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, 48.0, 48.0, 48.0, 48.0});
	mod44xx_init_info(OMAP4_MMC5, MOD_INTERFACE_DUAL, 1, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MMCHS5_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MMCSD5_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MMCSD5_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, 48.0, 48.0, 48.0, 48.0});
	mod44xx_init_info(OMAP4_MMC5_HL, MOD_INTERFACE_DUAL, 0, OMAP4_CD_L4_PER, OMAP4_PD_L4_PER, OMAP4_VDD_CORE, OMAP4430_MMCHS5_HL_SYSCONFIG, (unsigned int *) OMAP4430_CM_L4PER_MMCSD5_CLKCTRL, (unsigned int *) OMAP4430_RM_L4PER_MMCSD5_CONTEXT, OMAP4_PER_48M_FCLK, (double[OPP44XX_ID_MAX]) {24.576, 48.0, 48.0, 48.0, 48.0, 48.0, 48.0});

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod44xx_init_info_table
 * @BRIEF		initialize module info table
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		initialize module info table
 *//*------------------------------------------------------------------------ */
int mod44xx_init_info_table(void)
{
	if (!cpu_is_omap44xx())
		return OMAPCONF_ERR_CPU;
	else if (cpu_is_omap4470())
		return mod4470_init_info_table();
	else /* 4430, 4460 */
		return mod4430_init_info_table();
}
