/*
 *
 * @Component			OMAPCONF
 * @Filename			module_am335x.h
 * @Description			AM335X Module Definitions & APIs
 * @Author			Gilberto Rodriguez <gilrod@ti.com>
 * @Date			2014
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
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


#ifndef __MODULE_AM335X_H__
#define __MODULE_AM335X_H__


#include <clock_am335x.h>
#include <prcm-module.h>
#include <voltdm_am335x.h>


typedef enum {
	/* Voltage dom.: CORE, Power dom.: PD_WKUP, Clock domain = WKUP */
	AM335X_GPIO0,
	AM335X_DMTIMER0_DMC,
	AM335X_DMTIMER1,
	AM335X_UART0,
	AM335X_I2C0,
	AM335X_L4_WKUP,
	AM335X_SMARTREFLEX_C2_0,
	AM335X_SMARTREFLEX_C2_1,
	AM335X_WDT1,
	/* Voltage dom.: CORE, Power dom.: PD_WKUP, Clock domain = WKUP_L3_AON */
	AM335X_DEBUGSS,
	/* Voltage dom.: CORE, Power dom.: PD_WKUP, Clock domain = UNKNOWN */
	AM335X_WKUP_M3,
	AM335X_PRCM,
	AM335X_CTRLMOD,
	AM335X_TSC,
	AM335X_WKUP_DFTSS,
	AM335X_DPLL_CORE,
	AM335X_DPLL_PER,
	AM335X_DPLL_DDR,
	AM335X_EMU_MPU,
	AM335X_RC_OSC,
	/* Voltage dom.: CORE, Power dom.: PD_PER, Clock domain = PER_L4LS */
	AM335X_L4_PER,
	AM335X_DMTIMER2,
	AM335X_DMTIMER3,
	AM335X_DMTIMER4,
	AM335X_DMTIMER5,
	AM335X_DMTIMER6,
	AM335X_DMTIMER7,
	AM335X_SPI0,
	AM335X_SPI1,
	AM335X_GPIO1,
	AM335X_GPIO2,
	AM335X_GPIO3,
	AM335X_I2C1,
	AM335X_I2C2,
	AM335X_UART1,
	AM335X_UART2,
	AM335X_UART3,
	AM335X_UART4,
	AM335X_UART5,
	AM335X_DCAN0,
	AM335X_DCAN1,
	/* Voltage dom.: CORE, Power dom.: PD_PER, Clock domain = PER_L3S */
	AM335X_L3S,
	/* Voltage dom.: CORE, Power dom.: PD_PER, Clock domain = PER_L3 */
	AM335X_L3F,
	AM335X_MCASP0,
	AM335X_MCASP1,
	AM335X_MMC0,
	AM335X_MMC1,
	AM335X_MMC2,
	AM335X_EMIF4,
	AM335X_DDR_PHY,
	/* Voltage dom.: CORE, Power dom.: PD_PER, Clock domain = PER_L4HS */
	AM335X_L4_FAST,
	/* Voltage dom.: CORE, Power dom.: PD_PER, Clock domain = PER_OCPWP_L3 */
	AM335X_OCP_WP,
	/* Voltage dom.: CORE, Power dom.: PD_PER, Clock domain = PER_PRU_ICSS */
	AM335X_PRU_ICSS,
	/* Voltage dom.: CORE, Power dom.: PD_PER, Clock domain = PER_LCDC */
	AM335X_LCD_CTRL,
	/* Voltage dom.: CORE, Power dom.: PD_PER, Clock domain = UNKNOWN */
	AM335X_EDMA,
	AM335X_GPMC,
	AM335X_OCMC_OSC,
	AM335X_USB_CTRL,
	AM335X_EPWM0,
	AM335X_EPWM1,
	AM335X_EPWM2,
	AM335X_ECAP0,
	AM335X_ECAP1,
	AM335X_ECAP2,
	AM335X_EQEP0,
	AM335X_EQEP1,
	AM335X_ELM,
	AM335X_MAILBOX0,
	AM335X_SPINLOCK,
	AM335X_USB2PHYCORE,
	AM335X_USB2PHYCM,
	/* Voltage dom.: CORE, Power dom.: PD_GFX, Clock domain = GFX_L3 */
	AM335X_SGX530,
	/* Voltage dom.: MPU, Power dom.: PD_MPU, Clock domain = MPU */
	AM335X_MPU,
	AM335X_MPU_L1,
	AM335X_MPU_L2,
	/* Voltage dom.: MPU, Power dom.: PD_WKUP, Clock domain = UNKNOWN */
	AM335X_DPLL_MPU,
	/* Voltage dom.: RTC, Power dom.: PD_RTC, Clock domain = RTC */
	AM335X_RTC,
	AM335X_32KHZ_OSC,
	MOD_AM335X_ID_MAX
} mod_am335x_id;

void mod_am335x_init();
void mod_am335x_deinit();

const genlist *mod_am335x_list_get(void);
int mod_am335x_count_get(void);


#endif
