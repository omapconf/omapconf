/*
 *
 * @Component			OMAPCONF
 * @Filename			module.h
 * @Description			OMAP Generic Module Definitions & APIs
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


#ifndef __MODULE_H__
#define __MODULE_H__


#include <genlist.h>
#include <reg.h>
#include <prcm-module.h>
#include <stdio.h>


#define MOD_UNKNOWN			((const char *) "UNKNOWN")
#define MOD_DSP				((const char *) "DSP")
#define MOD_MMU_DSP			((const char *) "MMU_DSP")
#define MOD_DSP_WUGEN			((const char *) "DSP_WUGEN")
#define MOD_GPU				((const char *) "GPU")
#define MOD_SGX				((const char *) "SGX")
#define MOD_GFX				((const char *) "GFX")
#define MOD_IVA				((const char *) "IVA")
#define MOD_SL2				((const char *) "SL2")
#define MOD_MPU				((const char *) "MPU")
#define MOD_DEBUGSS			((const char *) "DEBUGSS")
#define MOD_CTRL_MODULE_WKUP		((const char *) "CTRL_MODULE_WKUP")
#define MOD_CTRL_MODULE_CORE		((const char *) "CTRL_MODULE_CORE")
#define MOD_CTRL_MODULE_BANDGAP		((const char *) "CTRL_MODULE_BANDGAP")
#define MOD_L3_MAIN1_INTERCONNECT	((const char *) "L3_MAIN1_INTERCONNECT")
#define MOD_L3_MAIN2_INTERCONNECT	((const char *) "L3_MAIN2_INTERCONNECT")
#define MOD_L3_MAIN3_INTERCONNECT	((const char *) "L3_MAIN3_INTERCONNECT")
#define MOD_L3_INSTR_INTERCONNECT	((const char *) "L3_INSTR_INTERCONNECT")
#define MOD_L4_PER_INTERCONNECT		((const char *) "L4_PER_INTERCONNECT")
#define MOD_L4_WKUP_INTERCONNECT	((const char *) "L4_WKUP_INTERCONNECT")
#define MOD_L4_CFG_INTERCONNECT		((const char *) "L4_CFG_INTERCONNECT")
#define MOD_L4_ABE_INTERCONNECT		((const char *) "L4_ABE_INTERCONNECT")
#define MOD_L4_FAST_INTERCONNECT	((const char *) "L4_FAST_INTERCONNECT")
#define MOD_GPIO1			((const char *) "GPIO1")
#define MOD_GPIO2			((const char *) "GPIO2")
#define MOD_GPIO3			((const char *) "GPIO3")
#define MOD_GPIO4			((const char *) "GPIO4")
#define MOD_GPIO5			((const char *) "GPIO5")
#define MOD_GPIO6			((const char *) "GPIO6")
#define MOD_GPIO7			((const char *) "GPIO7")
#define MOD_GPIO8			((const char *) "GPIO8")
#define MOD_TIMER1			((const char *) "TIMER1")
#define MOD_TIMER2			((const char *) "TIMER2")
#define MOD_TIMER3			((const char *) "TIMER3")
#define MOD_TIMER4			((const char *) "TIMER4")
#define MOD_TIMER5			((const char *) "TIMER5")
#define MOD_TIMER6			((const char *) "TIMER6")
#define MOD_TIMER7			((const char *) "TIMER7")
#define MOD_TIMER8			((const char *) "TIMER8")
#define MOD_TIMER9			((const char *) "TIMER9")
#define MOD_TIMER10			((const char *) "TIMER10")
#define MOD_TIMER11			((const char *) "TIMER11")
#define MOD_TIMER12			((const char *) "TIMER12")
#define MOD_WD_TIMER1			((const char *) "WD_TIMER1")
#define MOD_WD_TIMER2			((const char *) "WD_TIMER2")
#define MOD_WD_TIMER3			((const char *) "WD_TIMER3")
#define MOD_SARRAM			((const char *) "SARRAM")
#define MOD_COUNTER_32K			((const char *) "COUNTER_32K")
#define MOD_KEYBOARD			((const char *) "KEYBOARD")
#define MOD_IO_SRCOMP_WKUP		((const char *) "IO_SRCOMP_WKUP")
#define MOD_IO_SRCOMP_CORE		((const char *) "IO_SRCOMP_CORE")
#define MOD_SMARTREFLEX_MPU		((const char *) "SMARTREFLEX_MPU")
#define MOD_SMARTREFLEX_IVA		((const char *) "SMARTREFLEX_IVA")
#define MOD_SMARTREFLEX_MM		((const char *) "SMARTREFLEX_MM")
#define MOD_SMARTREFLEX_CORE		((const char *) "SMARTREFLEX_CORE")
#define MOD_BANDGAPTS			((const char *) "BANDGAPTS")
#define MOD_FDIF			((const char *) "FDIF")
#define MOD_ISS				((const char *) "ISS")
#define MOD_CAL				((const char *) "CAL")
#define MOD_CCP2			((const char *) "CCP2")
#define MOD_CSI2_A			((const char *) "CSI2_A")
#define MOD_CSI2_B			((const char *) "CSI2_B")
#define MOD_TCTRL			((const char *) "TCTRL")
#define MOD_BTE				((const char *) "BTE")
#define MOD_CBUFF			((const char *) "CBUFF")
#define MOD_ISP5			((const char *) "ISP5")
#define MOD_RSZ				((const char *) "RSZ")
#define MOD_SIMCOP			((const char *) "SIMCOP")
#define MOD_SIMCOP_DMA			((const char *) "SIMCOP_DMA")
#define MOD_SIMCOP_DCT			((const char *) "SIMCOP_DCT")
#define MOD_SIMCOP_VLCDJ		((const char *) "SIMCOP_VLCDJ")
#define MOD_SIMCOP_ROT			((const char *) "SIMCOP_ROT")
#define MOD_SPINLOCK			((const char *) "SPINLOCK")
#define MOD_MAILBOX			((const char *) "MAILBOX")
#define MOD_SARROM			((const char *) "SARROM")
#define MOD_OCP2SCP2			((const char *) "OCP2SCP2")
#define MOD_OCPSCP3			((const char *) "OCPSCP3")
#define MOD_PHY_EMIF			((const char *) "PHY_EMIF")
#define MOD_DLL_EMIF			((const char *) "DLL_EMIF")
#define MOD_DMM				((const char *) "DMM")
#define MOD_EMIF1			((const char *) "EMIF1")
#define MOD_EMIF2			((const char *) "EMIF2")
#define MOD_EMIF4			((const char *) "EMIF4")
#define MOD_EMIF_OCP_FW			((const char *) "EMIF_OCP_FW")
#define MOD_IPU				((const char *) "IPU")
#define MOD_GPMC			((const char *) "GPMC")
#define MOD_OCMC_RAM			((const char *) "OCMC_RAM")
#define MOD_OCP_WP_NOC			((const char *) "OCP_WP_NOC")
#define MOD_C2C				((const char *) "C2C")
#define MOD_C2C_OCP_FW			((const char *) "C2C_OCP_FW")
#define MOD_MODEM_ICR			((const char *) "MODEM_ICR")
#define MOD_DMA_SYSTEM			((const char *) "DMA_SYSTEM")
#define MOD_LLI				((const char *) "LLI")
#define MOD_LLI_OCP_FW			((const char *) "LLI_OCP_FW")
#define MOD_MPHY			((const char *) "MPHY")
#define MOD_DSS				((const char *) "DSS")
#define MOD_DSI1			((const char *) "DSI1")
#define MOD_DSI2			((const char *) "DSI2")
#define MOD_HDMI			((const char *) "HDMI")
#define MOD_RFBI			((const char *) "RFBI")
#define MOD_BB2D			((const char *) "BB2D")
#define MOD_HSI				((const char *) "HSI")
#define MOD_IEEE1500_2_OCP		((const char *) "IEEE1500_2_OCP")
#define MOD_MMC1			((const char *) "MMC1")
#define MOD_MMC1_HL			((const char *) "MMC1_HL")
#define MOD_MMC2			((const char *) "MMC2")
#define MOD_MMC2_HL			((const char *) "MMC2_HL")
#define MOD_MMC3			((const char *) "MMC3")
#define MOD_MMC3_HL			((const char *) "MMC3_HL")
#define MOD_MMC4			((const char *) "MMC4")
#define MOD_MMC4_HL			((const char *) "MMC4_HL")
#define MOD_MMC5			((const char *) "MMC5")
#define MOD_MMC5_HL			((const char *) "MMC5_HL")
#define MOD_OCPSCP1			((const char *) "OCPSCP1")
#define MOD_USB_HOST_HS			((const char *) "USB_HOST_HS")
#define MOD_USB_OTG_SS			((const char *) "USB_OTG_SS")
#define MOD_USB_TLL_HS			((const char *) "USB_TLL_HS")
#define MOD_USB_PHY_CORE		((const char *) "USB_PHY_CORE")
#define MOD_USB2PHY			((const char *) "USB2PHY")
#define MOD_SATA			((const char *) "SATA")
#define MOD_UNIPRO1			((const char *) "UNIPRO1")
#define MOD_UNIPRO2			((const char *) "UNIPRO2")
#define MOD_MPHY_UNIPRO2		((const char *) "MPHY_UNIPRO2")
#define MOD_ELM				((const char *) "ELM")
#define MOD_HDQ1W			((const char *) "HDQ1W")
#define MOD_I2C1			((const char *) "I2C1")
#define MOD_I2C2			((const char *) "I2C2")
#define MOD_I2C3			((const char *) "I2C3")
#define MOD_I2C4			((const char *) "I2C4")
#define MOD_I2C5			((const char *) "I2C5")
#define MOD_MCSPI1			((const char *) "MCSPI1")
#define MOD_MCSPI1_HL			((const char *) "MCSPI1_HL")
#define MOD_MCSPI2			((const char *) "MCSPI2")
#define MOD_MCSPI2_HL			((const char *) "MCSPI2_HL")
#define MOD_MCSPI3			((const char *) "MCSPI3")
#define MOD_MCSPI3_HL			((const char *) "MCSPI3_HL")
#define MOD_MCSPI4			((const char *) "MCSPI4")
#define MOD_MCSPI4_HL			((const char *) "MCSPI4_HL")
#define MOD_UART1			((const char *) "UART1")
#define MOD_UART2			((const char *) "UART2")
#define MOD_UART3			((const char *) "UART3")
#define MOD_UART4			((const char *) "UART4")
#define MOD_UART5			((const char *) "UART5")
#define MOD_UART6			((const char *) "UART6")
#define MOD_DMA_CRYPTO			((const char *) "DMA_CRYPTO")
#define MOD_AES1			((const char *) "AES1")
#define MOD_AES2			((const char *) "AES2")
#define MOD_SHA2MD5			((const char *) "SHA2MD5")
#define MOD_RNG				((const char *) "RNG")
#define MOD_DES3DES			((const char *) "DES3DES")
#define MOD_PKA				((const char *) "PKA")
#define MOD_AESS			((const char *) "AESS")
#define MOD_DMIC			((const char *) "DMIC")
#define MOD_MCASP			((const char *) "MCASP")
#define MOD_MCBSP1			((const char *) "MCBSP1")
#define MOD_MCBSP2			((const char *) "MCBSP2")
#define MOD_MCBSP3			((const char *) "MCBSP3")
#define MOD_MCPDM			((const char *) "MCPDM")
#define MOD_SLIMBUS1			((const char *) "SLIMBUS1")
#define MOD_SLIMBUS2			((const char *) "SLIMBUS2")



#define MOD_CONTROL_GEN_WKUP		((const char *) "CONTROL_GEN_WKUP")
#define MOD_CONTROL_PADCONF_WKUP	((const char *) "CONTROL_PADCONF_WKUP")
#define MOD_CONTROL_GEN_CORE		((const char *) "CONTROL_GEN_CORE")
#define MOD_CONTROL_PADCONF_CORE	((const char *) "CONTROL_PADCONF_CORE")
#define MOD_SYNCTIMER			((const char *) "SYNCTIMER")
#define MOD_USIM			((const char *) "USIM")
#define MOD_WDT3			((const char *) "WDT3")
#define MOD_IVAHD			((const char *) "IVAHD")
#define MOD_C2C_FW			((const char *) "C2C_FW")
#define MOD_MPU_ICR			((const char *) "MPU_ICR")
#define MOD_SDMA			((const char *) "SDMA")
#define MOD_MPU_M3			((const char *) "MPU_M3")
#define MOD_OCP_WP1			((const char *) "OCP_WP1")
#define MOD_EMIF_FW			((const char *) "EMIF_FW")
#define MOD_DLL				((const char *) "DLL")
#define MOD_DDRPHY			((const char *) "DDRPHY")
#define MOD_DISPC			((const char *) "DISPC")
#define MOD_FSUSBHOST			((const char *) "FSUSBHOST")
#define MOD_HSUSBHOST			((const char *) "HSUSBHOST")
#define MOD_HSUSBOTG			((const char *) "HSUSBOTG")
#define MOD_USBPHY			((const char *) "USBPHY")
#define MOD_USBTLL			((const char *) "USBTLL")
#define MOD_P1500			((const char *) "P1500")
#define MOD_MCBSP4			((const char *) "MCBSP4")


/* Additional Modules for DRA7 */
#define MOD_APLL_PCIE			((const char *) "APLL_PCIE")
#define MOD_ATL				((const char *) "ATL")
#define MOD_CM_CORE_AON			((const char *) "CM_CORE_AON")
#define MOD_CPU0			((const char *) "CPU0")
#define MOD_CPU1			((const char *) "CPU1")
#define MOD_DCAN1			((const char *) "DCAN1")
#define MOD_DCAN2			((const char *) "DCAN2")
#define MOD_DLL_AGING			((const char *) "DLL_AGING")
#define MOD_DPLL_ABE			((const char *) "DPLL_ABE")
#define MOD_DPLL_CORE			((const char *) "DPLL_CORE")
#define MOD_DPLL_DDR			((const char *) "DPLL_DDR")
#define MOD_DPLL_DSP			((const char *) "DPLL_DSP")
#define MOD_DPLL_EVE			((const char *) "DPLL_EVE")
#define MOD_DPLL_GMAC			((const char *) "DPLL_GMAC")
#define MOD_DPLL_GPU			((const char *) "DPLL_GPU")
#define MOD_DPLL_IVA			((const char *) "DPLL_IVA")
#define MOD_DPLL_MPU			((const char *) "DPLL_MPU")
#define MOD_DPLL_PCIE_REF		((const char *) "DPLL_PCIE_REF")
#define MOD_DPLL_PER			((const char *) "DPLL_PER")
#define MOD_DPLL_USB			((const char *) "DPLL_USB")
#define MOD_DSP1			((const char *) "DSP1")
#define MOD_DSP2			((const char *) "DSP2")
#define MOD_EFUSE_CTRL_CUST		((const char *) "EFUSE_CTRL_CUST")
#define MOD_EMIF_PHY1			((const char *) "EMIF_PHY1")
#define MOD_EMIF_PHY2			((const char *) "EMIF_PHY2")
#define MOD_EVE1			((const char *) "EVE1")
#define MOD_EVE2			((const char *) "EVE2")
#define MOD_FPKA			((const char *) "FPKA")
#define MOD_GMAC			((const char *) "GMAC"
#define MOD_HDMI_PHY			((const char *) "HDMI_PHY"
#define MOD_IEEE1500_2_OCP		((const char *) "IEEE1500_2_OCP")
#define MOD_IPU1			((const char *) "IPU1")
#define MOD_IPU2			((const char *) "IPU2")
#define MOD_KBD				((const char *) "KBD")
#define MOD_L4_PER1_INTERCONNECT	((const char *) "L4_PER1_INTERCONNECT")
#define MOD_L4_PER2_INTERCONNECT	((const char *) "L4_PER2_INTERCONNECT")
#define MOD_L4_PER3_INTERCONNECT	((const char *) "L4_PER3_INTERCONNECT")
#define MOD_MAILBOX1			((const char *) "MAILBOX1")
#define MOD_MAILBOX10			((const char *) "MAILBOX10")
#define MOD_MAILBOX11			((const char *) "MAILBOX11")
#define MOD_MAILBOX12			((const char *) "MAILBOX12")
#define MOD_MAILBOX13			((const char *) "MAILBOX13")
#define MOD_MAILBOX2			((const char *) "MAILBOX2")
#define MOD_MAILBOX3			((const char *) "MAILBOX3")
#define MOD_MAILBOX4			((const char *) "MAILBOX4")
#define MOD_MAILBOX5			((const char *) "MAILBOX5")
#define MOD_MAILBOX6			((const char *) "MAILBOX6")
#define MOD_MAILBOX7			((const char *) "MAILBOX7")
#define MOD_MAILBOX8			((const char *) "MAILBOX8")
#define MOD_MAILBOX9			((const char *) "MAILBOX9")
#define MOD_MAIN_2_INTERCONNECT		((const char *) "MAIN_2_INTERCONNECT")
#define MOD_MCASP1			((const char *) "MCASP1")
#define MOD_MCASP2			((const char *) "MCASP2")
#define MOD_MCASP3			((const char *) "MCASP3")
#define MOD_MCASP4			((const char *) "MCASP4")
#define MOD_MCASP5			((const char *) "MCASP5")
#define MOD_MCASP6			((const char *) "MCASP6")
#define MOD_MCASP7			((const char *) "MCASP7")
#define MOD_MCASP8			((const char *) "MCASP8")
#define MOD_MLB				((const char *) "MLB")
#define MOD_MPU_L2CACHE			((const char *) "MPU_L2CACHE")
#define MOD_OCMC_EDMA			((const char *) "OCMC_EDMA")
#define MOD_OCMC_MMU1			((const char *) "OCMC_MMU1")
#define MOD_OCMC_MMU2			((const char *) "OCMC_MMU2")
#define MOD_OCMC_RAM1			((const char *) "OCMC_RAM1")
#define MOD_OCMC_RAM2			((const char *) "OCMC_RAM2")
#define MOD_OCMC_RAM3			((const char *) "OCMC_RAM3")
#define MOD_OCMC_VCP1			((const char *) "OCMC_VCP1")
#define MOD_OCMC_VCP2			((const char *) "OCMC_VCP2")
#define MOD_OCP2SCP1			((const char *) "OCP2SCP1")
#define MOD_OCP2SCP3			((const char *) "OCP2SCP3")
#define MOD_PCIE_SS1			((const char *) "PCIE_SS1")
#define MOD_PCIE_SS2			((const char *) "PCIE_SS2")
#define MOD_PRCM_MPU			((const char *) "PRCM_MPU")
#define MOD_PRM				((const char *) "PRM")
#define MOD_PWMSS1			((const char *) "PWMSS1")
#define MOD_PWMSS2			((const char *) "PWMSS2")
#define MOD_PWMSS3			((const char *) "PWMSS3")
#define MOD_QSPI			((const char *) "QSPI")
#define MOD_RTCSS			((const char *) "RTCSS")
#define MOD_SHA2MD5_1			((const char *) "SHA2MD5_1"
#define MOD_SHA2MD5_2			((const char *) "SHA2MD5_2")
#define MOD_SMARTREFLEX_DSPEVE		((const char *) "SMARTREFLEX_DSPEVE")
#define MOD_SMARTREFLEX_GPU		((const char *) "SMARTREFLEX_GPU")
#define MOD_SMARTREFLEX_IVAHD		((const char *) "SMARTREFLEX_IVAHD")
#define MOD_TIMER13			((const char *) "TIMER13")
#define MOD_TIMER14			((const char *) "TIMER14")
#define MOD_TIMER15			((const char *) "TIMER15")
#define MOD_TIMER16			((const char *) "TIMER16")
#define MOD_UART10			((const char *) "UART10")
#define MOD_UART7			((const char *) "UART7")
#define MOD_UART8			((const char *) "UART8")
#define MOD_UART9			((const char *) "UART9")
#define MOD_USB1			((const char *) "USB1")
#define MOD_USB2			((const char *) "USB2")
#define MOD_USB3			((const char *) "USB3")
#define MOD_USB4			((const char *) "USB4")
#define MOD_VIP1			((const char *) "VIP1")
#define MOD_VIP2			((const char *) "VIP2")
#define MOD_VIP3			((const char *) "VIP3")
#define MOD_VPE				((const char *) "VPE")
#define MOD_WUGEN_DSP			((const char *) "WUGEN_DSP")
#define MOD_WUGEN_IPU			((const char *) "WUGEN_IPU")
#define MOD_WUGEN_SYSTEM		((const char *) "WUGEN_SYSTEM")


typedef struct {
	const char *name; /* Module Name */
	int id;	/* Module ID (invalid if < 0) */
	const char *clkdm; /* Name of Clock Domain module is part of */
	const char *pwrdm; /* Name of Power Domain module is part of */
	const char *voltdm; /* Name of Voltage Domain module is part of */
	int clk; /* Functional Clock of the module (invalid if < 0) */
	reg *sysconfig; /* SYSCONFIG register of the module */
	reg *clkctrl; /* CLKCTRL register of the module */
	reg *context; /* CONTEXT register of the module */
	genlist mod_opp_list; /* List of OPP (as defined in opp.h) supported by the module */
	unsigned int properties; /* Module properties flags */
} mod_info;


typedef struct {
	const char *name; /* OPP Name */
	int rate; /* in KHz */
} mod_opp;


void module_init(void);
void module_deinit(void);

int module_count_get(void);
const genlist *module_list_get(void);


unsigned int module_has_sysconfig_register(const char *mod);
unsigned int module_has_autoidle_bit(const char *mod);
unsigned int module_has_idle_mode(const char *mod);
unsigned int module_has_idle_status(const char *mod);
unsigned int module_has_smart_idle_wakeup_mode(const char *mod);
unsigned int module_has_enawakeup_bit(const char *mod);
unsigned int module_has_standby_mode(const char *mod);
unsigned int module_has_standby_status(const char *mod);
unsigned int module_has_smart_standby_wakeup_mode(const char *mod);
unsigned int module_has_clock_activity_mode(const char *mod);


int module_id_get(const char *mod);
unsigned short int module_is_accessible(const char *mod);
mod_module_mode module_mode_get(const char *mod);
mod_autoidle_mode module_autoidle_mode_get(const char *mod);
mod_idle_mode module_idle_mode_get(const char *mod);
mod_idle_status module_idle_status_get(const char *mod);
mod_standby_mode module_standby_mode_get(const char *mod);
mod_standby_status module_standby_status_get(const char *mod);
mod_clock_activity_mode module_clock_activity_mode_get(const char *mod);
int module_context_is_lost(const char *mod);
int module_clk_get(const char *mod);
int module_clk_rate_get(const char *mod, unsigned short ignore);
int module_por_clk_rate_get(const char *mod, const char *opp);

int module_status_show(FILE *stream);
int module_clk_rate_audit(FILE *stream,
	unsigned int *err_nbr, unsigned int *wng_nbr);
int module_sysconfig_audit(FILE *stream, unsigned int *err_nbr,
	unsigned int *wng_nbr);
int module_config_show(FILE *stream, const char *mod);


#endif
