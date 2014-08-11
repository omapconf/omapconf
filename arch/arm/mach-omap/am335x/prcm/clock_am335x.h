/*
 *
 * @Component			OMAPCONF
 * @Filename			clock_am335x.h
 * @Description			AM335X PRCM Clock Definitions & Functions
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


#ifndef __PRCM_CLOCK_AM335X_H__
#define __PRCM_CLOCK_AM335X_H__

#define CLK_AM335X_MAX_NAME_LENGTH		32

typedef enum {
	/* 32K CLKS */
	CLK_AM335X_CLK_32KHZ,	/* Output of DPLL PER*/
	CLK_AM335X_CLK_RC32K,	/* On-chip 32KHz oscillator */
	CLK_AM335X_CLK_32K_RTC,	/* External 32KHz oscillator */
	/* SYS CLKS */
	CLK_AM335X_SYS_CLK,
	CLK_AM335X_TCLKIN,
	CLK_AM335X_CLK_48,
	CLK_AM335X_CLK_24,
	CLK_AM335X_MHZ_250_CLK,
	CLK_AM335X_MHZ_125_CLK,
	CLK_AM335X_MHZ_50_CLK,
	CLK_AM335X_MHZ_5_CLK,
	/* DPLL CORE OUTPUT CLKS */
	CLK_AM335X_CORE_CLKOUTM4,
	CLK_AM335X_CORE_CLKOUTM5,
	CLK_AM335X_CORE_CLKOUTM6,
	CLK_AM335X_SGX_CORECLK,
	CLK_AM335X_L3S_CLK,
	CLK_AM335X_L4_PER_CLK,
	CLK_AM335X_L4_WKUPCLK,
	CLK_AM335X_L3F_CLK,
	CLK_AM335X_L4F_CLK,
	CLK_AM335X_PRU_ICSS_IEP_CLK,
	CLK_AM335X_DEBUGSS_CLKA,
	CLK_AM335X_PRU_ICSS_OCP_CLKL,
	CLK_AM335X_CPTS_RFT_CLK,
	/* DPLL PER OUTPUT CLKS */
	CLK_AM335X_USB_PHY_CLK,
	CLK_AM335X_PER_CLKOUTM2,
	CLK_AM335X_PRU_ICSS_UART_CLK,
	CLK_AM335X_MMC_CLK,
	CLK_AM335X_SPI_CLK,
	CLK_AM335X_UART_CLK,
	CLK_AM335X_I2C_CLK,
	/* DPLL MPU OUTPUT CLKS */
	CLK_AM335X_MPU_CLK,
	/* DPLL DISP OUTPUT CLKS */
	CLK_AM335X_DISP_CLKOUT,
	CLK_AM335X_LCD_CLK,
	/* DPLL DDR OUTPUT CLKS */
	CLK_AM335X_DDR_CLKOUTM2,
	CLK_AM335X_EMIF_M_CLK,
	/* GFX CLKS */
	CLK_AM335X_GFX_SYSCLK,
	CLK_AM335X_GFX_MEMCLK,
	CLK_AM335X_GFX_CORECLK,
	/* OTHER */
	CLK_AM335X_ID_MAX
} clk_am335x_id;


const char *clk_am335x_name_get(clk_am335x_id id);
double clk_am335x_rate_get(clk_am335x_id clk, unsigned short ignore);


#endif
