/*
 *
 * @Component			OMAPCONF
 * @Filename			clock_am335x.c
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


#include <clock_am335x.h>
#include <cm_am335x.h>
#include <cpuinfo.h>
#include <dpll_am335x.h>
#include <lib.h>
#include <mem.h>
#include <prm_am335x.h>
#include <stdlib.h>
#include <string.h>


#ifdef CLOCK_AM335X_DEBUG
#define dprintf(format, ...)	printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


#define AM335X_SYS_32K_SPEED			0.032768
/* Control Mod registers with clock settings */
#define AM335X_STATUS				0x44E10040
#define AM335X_CLK32K_DIVRATIO_CTRL		0x4EE10444

/* External clock inputs (MHz) */
#define AM335X_TCLKIN_SPEED			0.0
#define AM335X_EXT_32K_SPEED			0.0

static const char
	clk_am335x_name_table[CLK_AM335X_ID_MAX + 1][CLK_AM335X_MAX_NAME_LENGTH] = {
	/* 32K CLKS */
	[CLK_AM335X_CLK_32KHZ] = "CLK_32KHZ",
	[CLK_AM335X_CLK_RC32K] = "CLK_RC32K",
	[CLK_AM335X_CLK_32K_RTC] = "CLK_32K_RTC",
	/* SYS CLKS */
	[CLK_AM335X_SYS_CLK] = "SYS_CLK",
	[CLK_AM335X_TCLKIN] = "TCLKIN",
	[CLK_AM335X_CLK_48] = "CLK_48",
	[CLK_AM335X_CLK_24] = "CLK_24",
	[CLK_AM335X_MHZ_250_CLK] = "MHZ_250_CLK",
	[CLK_AM335X_MHZ_125_CLK] = "MHZ_125_CLK",
	[CLK_AM335X_MHZ_50_CLK] = "MHZ_50_CLK",
	[CLK_AM335X_MHZ_5_CLK] = "MHZ_5_CLK",
	/* DPLL CORE OUTPUT CLKS */
	[CLK_AM335X_CORE_CLKOUTM4] = "CORE_CLKOUTM4",
	[CLK_AM335X_CORE_CLKOUTM5] = "CORE_CLKOUTM5",
	[CLK_AM335X_CORE_CLKOUTM6] = "CORE_CLKOUTM6",
	[CLK_AM335X_SGX_CORECLK] = "SGX_CORECLK",
	[CLK_AM335X_L3S_CLK] = "L3S_CLK",
	[CLK_AM335X_L4_PER_CLK] = "L4_PER_CLK",
	[CLK_AM335X_L4_WKUPCLK] = "L4_WKUPCLK",
	[CLK_AM335X_L3F_CLK] = "L3F_CLK",
	[CLK_AM335X_L4F_CLK] = "L4F_CLK",
	[CLK_AM335X_PRU_ICSS_IEP_CLK] = "PRU_ICSS_IEP_CLK",
	[CLK_AM335X_DEBUGSS_CLKA] = "DEBUGSS_CLKA",
	[CLK_AM335X_PRU_ICSS_OCP_CLKL] = "PRU_ICSS_OCP_CLKL",
	[CLK_AM335X_CPTS_RFT_CLK] = "CPTS_RFT_CLK",
	/* DPLL PER OUTPUT CLKS */
	[CLK_AM335X_USB_PHY_CLK] = "USB_PHY_CLK",
	[CLK_AM335X_PER_CLKOUTM2] = "PER_CLKOUTM2",
	[CLK_AM335X_PRU_ICSS_UART_CLK] = "PRU_ICSS_UART_CLK",
	[CLK_AM335X_MMC_CLK] = "MMC_CLK",
	[CLK_AM335X_SPI_CLK] = "SPI_CLK",
	[CLK_AM335X_UART_CLK] = "UART_CLK",
	[CLK_AM335X_I2C_CLK] = "I2C_CLK",
	/* DPLL MPU OUTPUT CLKS */
	[CLK_AM335X_MPU_CLK] = "MPU_CLK",
	/* DPLL DISP OUTPUT CLKS */
	[CLK_AM335X_DISP_CLKOUT] = "DISP_CLKOUT",
	[CLK_AM335X_LCD_CLK] = "LCD_CLK",
	/* DPLL DDR OUTPUT CLKS */
	[CLK_AM335X_DDR_CLKOUTM2] = "DDR_CLKOUTM2",
	[CLK_AM335X_EMIF_M_CLK] = "EMIF_M_CLK",
	/* GFX CLKS */
	[CLK_AM335X_GFX_SYSCLK] = "GFX_SYSCLK",
	[CLK_AM335X_GFX_MEMCLK] = "GFX_MEMCLK",
	[CLK_AM335X_GFX_CORECLK] = "GFX_CORECLK",
	[CLK_AM335X_ID_MAX] = "FIXME" };

typedef enum {
	SYSCLK_AM335X_19_2_MHZ = 0,
	SYSCLK_AM335X_24_MHZ = 1,
	SYSCLK_AM335X_25_MHZ = 2,
	SYSCLK_AM335X_26_MHZ = 3,
	SYSCLK_AM335X_ID_MAX
} sysclk_am335x_id;

static const double sysclk_am335x_rate_table[SYSCLK_AM335X_ID_MAX] = {
	/* MHz */
	19.2,
	24.0,
	25.0,
	26.0
};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clk_am335x_name_get
 * @BRIEF		return clock name
 * @RETURNS		clock name on success
 *			NULL in case of error
 * @param[in]		id: clock ID
 * @DESCRIPTION		return clock name
 *//*------------------------------------------------------------------------ */
const char *clk_am335x_name_get(clk_am335x_id id)
{
	CHECK_ARG_LESS_THAN(id, CLK_AM335X_ID_MAX + 1, NULL);

	return clk_am335x_name_table[id];
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clk_am335x_sysclk_rate_get
 * @BRIEF		Return the mandatory system clock speed, in MHz.
 * @RETURNS		> 0 system clock speed, in MHz.
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in]		none
 * @DESCRIPTION		Return the mandatory system clock speed, in MHz.
 *//*------------------------------------------------------------------------ */
double clk_am335x_sysclk_rate_get(void)
{
	unsigned int reg_val;
	static double sysclk = 0.0;
	sysclk_am335x_id sysclk_id;

	if (!cpu_is_am335x())
		return (double) OMAPCONF_ERR_CPU;

	if (sysclk > 0.0) {
		dprintf("%s(): sysclk rate=%.1lfMHz\n", __func__, sysclk);
		return sysclk;
	}

	if (!mem_fake_access_get()) {
		mem_read(AM335X_STATUS, &reg_val);
		sysclk_id = extract_bitfield(reg_val, 22, 2);
	} else {
		sysclk_id = SYSCLK_AM335X_19_2_MHZ; /* AM335X EVM PoR */
	}

	sysclk = sysclk_am335x_rate_table[sysclk_id];
	if (sysclk == 0.0) {
		fprintf(stderr, "%s(): bad CONTROL_STATUS value(%d)\n",
				__func__, sysclk_id);
		sysclk = (double) OMAPCONF_ERR_UNEXPECTED;
	} else {
		dprintf("%s(): CONTROL_STATUS=0x%x, sysclk rate=%.1lfMHz\n",
				__func__, sysclk_id, sysclk);
	}

	return sysclk;
}

#ifndef CLOCK_AM335X_DEBUG
#ifdef CLK_AM335X_RATE_GET_DEBUG
#undef dprintf
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif
#endif

#define DPRINT_CLK_SPEED1(clk_id, out_clk_speed)\
	dprintf("%s(): %s speed = %fMHz\n",\
	__func__,\
	clk_am335x_name_get(clk_id),\
	out_clk_speed);

#define DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed, out_clk_speed)\
	dprintf("%s(): %s src = %s, src speed = %.3fMHz, speed = %fMHz\n",\
	__func__,\
	clk_am335x_name_get(clk_id),\
	clk_am335x_name_get(src_clk_id),\
	src_clk_speed,\
	out_clk_speed);

#define DPRINT_CLK_SPEED2_DPLL(clk_id, src_clk, src_clk_speed, out_clk_speed)\
	dprintf("%s(): %s src = %s, src speed = %.3fMHz, speed = %fMHz\n",\
	__func__,\
	clk_am335x_name_get(clk_id),\
	src_clk,\
	src_clk_speed,\
	out_clk_speed);

#define DPRINT_CLK_SPEED3(clk_id, src_clk_id,\
	src_clk_speed, div, out_clk_speed)\
	dprintf("%s(): %s src = %s, speed = %.3fMHz / %d = %fMHz\n",\
	__func__,\
	clk_am335x_name_get(clk_id),\
	clk_am335x_name_get(src_clk_id),\
	src_clk_speed,\
	(int) div,\
	out_clk_speed);


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clk_am335x_rate_get
 * @BRIEF		convert bitfield value from register into string
 * @RETURNS		> 0 clock speed in MHz
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		clk_id: am335x clock id
 * @param[in]		ignore: do not consider DPLL stop status.
 *			Useful for functions that needs the DPLL output
 *			frequencies whatever its status
 *			(e.g. audit, clock tree, etc)
 * @DESCRIPTION		convert bitfield value from register into string
 *//*------------------------------------------------------------------------ */
double clk_am335x_rate_get(clk_am335x_id clk_id,
	unsigned short ignore)
{
	unsigned int reg_val;
	double src_clk_speed, out_clk_speed;
	clk_am335x_id src_clk_id;
	double div;

	if (!cpu_is_am335x())
		return (double) OMAPCONF_ERR_CPU;

	switch (clk_id) {
	/* 32K CLKS */
	case CLK_AM335X_CLK_32KHZ:
		mem_read(AM335X_CLK32K_DIVRATIO_CTRL, &reg_val);
		if (extract_bit(reg_val, 0) == 0)
			div = 732.4219;
		else
			div = 366.2109;

		src_clk_id = CLK_AM335X_CLK_24;
		src_clk_speed = clk_am335x_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
				out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_CLK_RC32K:
		out_clk_speed = AM335X_SYS_32K_SPEED;
		DPRINT_CLK_SPEED1(clk_id, out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_CLK_32K_RTC:
		out_clk_speed = AM335X_EXT_32K_SPEED;
		DPRINT_CLK_SPEED1(clk_id, out_clk_speed);
		return out_clk_speed;
	/* SYS CLKS */
	case CLK_AM335X_SYS_CLK:
		/* Listed as M_OSC (Master Oscillator) in TRM */
		out_clk_speed = clk_am335x_sysclk_rate_get();
		DPRINT_CLK_SPEED1(clk_id, out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_TCLKIN:
		out_clk_speed = AM335X_TCLKIN_SPEED;
		DPRINT_CLK_SPEED1(clk_id, out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_CLK_48:
		src_clk_id = CLK_AM335X_PER_CLKOUTM2;
		src_clk_speed = clk_am335x_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed / 4;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_CLK_24:
		src_clk_id = CLK_AM335X_CLK_48;
		src_clk_speed = clk_am335x_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed / 2;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_MHZ_250_CLK:
		src_clk_id = CLK_AM335X_CORE_CLKOUTM5;
		src_clk_speed = clk_am335x_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_MHZ_125_CLK:
		src_clk_id = CLK_AM335X_CORE_CLKOUTM5;
		src_clk_speed = clk_am335x_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed / 2;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_MHZ_50_CLK:
		src_clk_id = CLK_AM335X_CORE_CLKOUTM5;
		src_clk_speed = clk_am335x_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed / 5;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_MHZ_5_CLK:
		src_clk_id = CLK_AM335X_MHZ_50_CLK;
		src_clk_speed = clk_am335x_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed / 10;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	/* DPLL CORE OUTPUT CLKS */
	case CLK_AM335X_CORE_CLKOUTM4:
		src_clk_speed = dpll_am335x_output_rate_get(
			DPLL_AM335X_CORE, DPLL_AM335X_CORE_CLKOUT_M4, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_CORE CORE_CLKOUT_M4",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_CORE_CLKOUTM5:
		src_clk_speed = dpll_am335x_output_rate_get(
			DPLL_AM335X_CORE, DPLL_AM335X_CORE_CLKOUT_M5, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_CORE CORE_CLKOUT_M5",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_CORE_CLKOUTM6:
		src_clk_speed = dpll_am335x_output_rate_get(
			DPLL_AM335X_CORE, DPLL_AM335X_CORE_CLKOUT_M6, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_CORE CORE_CLKOUT_M6",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_SGX_CORECLK:
		reg_val = reg_read(&am335x_clksel_gfx_fclk);
		if (extract_bit(reg_val, 1) == 0)
			src_clk_id = CLK_AM335X_CORE_CLKOUTM4;
		else
			src_clk_id = CLK_AM335X_PER_CLKOUTM2;

		src_clk_speed = clk_am335x_rate_get(src_clk_id, ignore);
		div = (double) (1 << extract_bit(reg_val, 0));
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_L3S_CLK:
		src_clk_id = CLK_AM335X_CORE_CLKOUTM4;
		src_clk_speed = clk_am335x_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed / 2;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_L4_PER_CLK:
		src_clk_id = CLK_AM335X_CORE_CLKOUTM4;
		src_clk_speed = clk_am335x_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed / 2;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_L4_WKUPCLK:
		src_clk_id = CLK_AM335X_CORE_CLKOUTM4;
		src_clk_speed = clk_am335x_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed / 2;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_L3F_CLK:
		src_clk_id = CLK_AM335X_CORE_CLKOUTM4;
		src_clk_speed = clk_am335x_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_L4F_CLK:
		src_clk_id = CLK_AM335X_CORE_CLKOUTM4;
		src_clk_speed = clk_am335x_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_PRU_ICSS_IEP_CLK:
		src_clk_id = CLK_AM335X_CORE_CLKOUTM4;
		src_clk_speed = clk_am335x_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_DEBUGSS_CLKA:
		src_clk_id = CLK_AM335X_CORE_CLKOUTM4;
		src_clk_speed = clk_am335x_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_PRU_ICSS_OCP_CLKL:
		reg_val = reg_read(&am335x_clksel_pru_icss_ocp_clk);
		if (extract_bit(reg_val, 0) == 0)
			src_clk_id = CLK_AM335X_CORE_CLKOUTM4;
		else
			src_clk_id = CLK_AM335X_DISP_CLKOUT;

		src_clk_speed = clk_am335x_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_CPTS_RFT_CLK:
		reg_val = reg_read(&am335x_cm_cpts_rft_clksel);
		if (extract_bit(reg_val, 0) == 0)
			src_clk_id = CLK_AM335X_CORE_CLKOUTM4;
		else
			src_clk_id = CLK_AM335X_CORE_CLKOUTM5;

		src_clk_speed = clk_am335x_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	/* DPLL PER OUTPUT CLKS */
	case CLK_AM335X_USB_PHY_CLK:
		src_clk_speed = dpll_am335x_output_rate_get(
			DPLL_AM335X_PER, DPLL_AM335X_CLKDCOLDO, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_PER CLKOUT", src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_PER_CLKOUTM2:
		src_clk_speed = dpll_am335x_output_rate_get(
			DPLL_AM335X_PER, DPLL_AM335X_CLKOUT, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_PER CLKOUT", src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_PRU_ICSS_UART_CLK:
		src_clk_id = CLK_AM335X_PER_CLKOUTM2;
		src_clk_speed = clk_am335x_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_MMC_CLK:
		src_clk_id = CLK_AM335X_PER_CLKOUTM2;
		src_clk_speed = clk_am335x_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed / 2;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_SPI_CLK:
		src_clk_id = CLK_AM335X_CLK_48;
		src_clk_speed = clk_am335x_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_UART_CLK:
		src_clk_id = CLK_AM335X_CLK_48;
		src_clk_speed = clk_am335x_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_I2C_CLK:
		src_clk_id = CLK_AM335X_CLK_48;
		src_clk_speed = clk_am335x_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	/* DPLL MPU OUTPUT CLKS */
	case CLK_AM335X_MPU_CLK:
		src_clk_speed = dpll_am335x_output_rate_get(
			DPLL_AM335X_MPU, DPLL_AM335X_CLKOUT, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_MPU CLKOUT", src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	/* DPLL DISP OUTPUT CLKS */
	case CLK_AM335X_DISP_CLKOUT:
		src_clk_speed = dpll_am335x_output_rate_get(
			DPLL_AM335X_DISP, DPLL_AM335X_CLKOUT, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_DISP CLKOUT", src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_LCD_CLK:
		reg_val = reg_read(&am335x_clksel_lcdc_pixel_clk);
		if (extract_bitfield(reg_val, 0, 2) == 2)
			src_clk_id = CLK_AM335X_PER_CLKOUTM2;
		else if (extract_bitfield(reg_val, 0, 2) == 1)
			src_clk_id = CLK_AM335X_CORE_CLKOUTM5;
		else
			src_clk_id = CLK_AM335X_DISP_CLKOUT;

		src_clk_speed = clk_am335x_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	/* DPLL DDR OUTPUT CLKS */
	case CLK_AM335X_DDR_CLKOUTM2:
		src_clk_speed = dpll_am335x_output_rate_get(
			DPLL_AM335X_DDR, DPLL_AM335X_CLKOUT, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_DDR CLKOUT", src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_EMIF_M_CLK:
		src_clk_id = CLK_AM335X_DDR_CLKOUTM2;
		src_clk_speed = clk_am335x_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed / 2;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_GFX_SYSCLK:
		src_clk_id = CLK_AM335X_CORE_CLKOUTM4;
		src_clk_speed = clk_am335x_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed / 2;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_GFX_MEMCLK:
		src_clk_id = CLK_AM335X_CORE_CLKOUTM4;
		src_clk_speed = clk_am335x_rate_get(src_clk_id, ignore);
		out_clk_speed = src_clk_speed / 2;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_GFX_CORECLK:
		reg_val = reg_read(&am335x_clksel_gfx_fclk);
		if (extract_bit(reg_val, 1))
			src_clk_id = CLK_AM335X_PER_CLKOUTM2;
		else
			src_clk_id = CLK_AM335X_CORE_CLKOUTM4;

		src_clk_speed = clk_am335x_rate_get(src_clk_id, ignore);
		if (extract_bit(reg_val, 0))
			div = 2;
		else
			div = 1;

		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	case CLK_AM335X_ID_MAX:
		out_clk_speed = 0;
		DPRINT_CLK_SPEED1(clk_id, out_clk_speed);
		return out_clk_speed;

	default:
		fprintf(stderr, "%s(): invalid clock id %s(%u)!\n",
			__func__, clk_am335x_name_table[clk_id], clk_id);
		return (double) OMAPCONF_ERR_ARG;
	}

	return 0;
}
