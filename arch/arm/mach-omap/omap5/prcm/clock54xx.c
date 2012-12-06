/*
 *
 * @Component			OMAPCONF
 * @Filename			clock54xx.c
 * @Description			OMAP5 PRCM Clocks Definitions & Functions
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


#include <clock54xx.h>
#include <string.h>
#include <cpuinfo.h>
#include <lib.h>
#include <mem.h>
#include <cm54xx.h>
#include <prm54xx.h>
#include <dpll54xx.h>
#include <stdlib.h>

/* #define CLOCK54XX_DEBUG */

#ifdef CLOCK54XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static const char
	clk54xx_name_table[CLK54XX_ID_MAX + 1][CLK54XX_MAX_NAME_LENGTH] = {
	/* 32K CLKS */
	"SYS_32K",
	"FUNC_32K_CLK",
	"SECURE_32K_CLK",
	"HDMI_CEC_GFCLK",
	"WKUPAON_32K_GFCLK",
	"COREAON_32K_GFCLK",
	"PER_32K_GFCLK",
	"ABE_32K_CLK",
	"MMC1_32K_GFCLK", /* ES2.0 only */
	/* SYS CLKS */
	"SYS_CLKIN",
	"SYS_CLK",
	"CUSTEFUSE_SYS_GFCLK",
	"EMU_SYS_CLK",
	"CORE_DPLL_CLK",
	"PER_DPLL_CLK",
	"IVA_DPLL_CLK",
	"MPU_DPLL_CLK",
	"UNIPRO2_DPLL_CLK",
	"USB_DPLL_CLK",
	"USB_OTG_SS_REF_CLK",
	"UNIPRO1_DPLL_CLK",
	"WKUPAON_IO_SRCOMP_GFCLK",
	"COREAON_IO_SRCOMP_GFCLK",
	"UNIPRO2_PHY_REF_GFCLK",
	"MIPIEXT_PHY_REF_GFCLK",
	"SATA_REF_GFCLK",
	"DSS_SYS_CLK",
	"ABE_SYS_CLK",
	/* DPLL BYPASS INPUT CLKS */
	"ABE_DPLL_CLK",
	"ABE_DPLL_BYPASS_CLK",
	"MPU_DPLL_HS_CLK",
	"IVA_DPLL_HS_CLK",
	"PER_DPLL_HS_CLK",
	"USB_DPLL_HS_CLK",
	/* DPLL ABE OUTPUT CLKS */
	"PER_ABE_X1_GFCLK",
	"DPLL_ABE_X2_FCLK",
	"CORE_DPLL_HS_CLK",
	/* DPLL CORE OUTPUTS */
	"EMIF_PHY_GCLK",
	"CORE_DPLL_SCRM_CLK",
	"CORE_DLL_GCLK",
	"CORE_X2_CLK",
	"CORE_USB_OTG_SS_LFPS_TX_CLK",
	"CORE_GPU_CLK",
	"CORE_C2C_CLK", /* ES2.0 only */
	"CORE_IPU_ISS_BOOST_CLK",
	"CORE_ISS_MAIN_CLK",
	"BB2D_GFCLK", /* ES2.0 only */
	/* DPLL PER OUTPUTS */
	"FUNC_96M_AON_CLK",
	"FUNC_192M_FCLK",
	"PER_DPLL_SCRM_CLK",
	"FUNC_128M_CLK",
	"FUNC_256M_CLK", /* ES2.0 only */
	"DSS_GFCLK",
	"PER_GPU_CLK",
	/* DPLL MPU OUTPUTS */
	"MPU_GCLK",
	/* DPLL IVA OUTPUTS */
	"DSP_GCLK",
	"IVA_GCLK",
	/* DPLL USB OUTPUTS */
	"L3INIT_480M_FCLK",
	"L3INIT_960M_FCLK",
	/* DPLL UNIPRO1 OUTPUTS */
	"UNIPRO1_TXPHY_LS_GFCLK",
	"UNIPRO1_PHY_GFCLK",
	/* DPLL UNIPRO2 OUTPUTS */
	"UNIPRO2_TXPHY_LS_GFCLK",
	"UNIPRO2_PHY_GFCLK",
	/* COREAON CLKDM Clocks */
	"FUNC_24M_CLK",
	"FUNC_24M_GFCLK",
	"CORE_CLK",
	"L3_ICLK",
	"EMIF_L3_GICLK",
	"L4SEC_L3_GICLK",
	"CAM_L3_GICLK",
	"C2C_L3_GICLK",
	"DMA_L3_GICLK",
	"L3INSTR_L3_GICLK",
	"L3MAIN1_L3_GICLK",
	"L3MAIN2_L3_GICLK",
	"MIPIEXT_L3_GICLK",
	"DSS_L3_GICLK",
	"L3INIT_L3_GICLK",
	"CM_CORE_AON_PROFILING_L3_GICLK",
	"L4_ROOT_CLK",
	"L4_ICLK",
	"L4PER_L4_GICLK",
	"L4SEC_L4_GICLK",
	"C2C_L4_GICLK",
	"L4CFG_L4_GICLK",
	"MIPIEXT_L4_GICLK",
	"L3INIT_L4_GICLK",
	"CM_CORE_AON_PROFILING_L4_GICLK",
	/* PRM CLKDM Clocks */
	"ABE_LP_CLK",
	"WKUPAON_ICLK",
	"SR_MM_SYS_GFCLK",
	"SR_MPU_SYS_GFCLK",
	"SR_CORE_SYS_GFCLK",
	"WKUPAON_GCLK",
	"WKUPAON_GICLK",
	"CM_CORE_AON_SYS_CLK",
	"WKUPAON_PROFILING_GCLK",
	"CORE_TS_GFCLK",
	"COREAON_TS_GFCLK",
	"L3INSTR_DLL_AGING_GCLK",
	"L3INSTR_TS_GFCLK",
	/* PRM TIMER Clocks */
	"TIMER1_GFCLK",
	"TIMER2_GFCLK",
	"TIMER3_GFCLK",
	"TIMER4_GFCLK",
	"TIMER9_GFCLK",
	"TIMER10_GFCLK",
	"TIMER11_GFCLK",
	/* CKGEN_USB Clocks */
	"UTMI_P3_GFCLK",
	"HSIC_P3_GFCLK",
	"HSIC_P2_GFCLK",
	"HSIC_P1_GFCLK",
	"L3INIT_60M_P1_GFCLK",
	"L3INIT_60M_P2_GFCLK",
	"UTMI_ROOT_GFCLK",
	"TLL_CH0_GFCLK",
	"TLL_CH1_GFCLK",
	"TLL_CH2_GFCLK",
	"L3INIT_60M_FCLK",
	"HSIC_P1_480M_GFCLK",
	"HSIC_P2_480M_GFCLK",
	"HSIC_P3_480M_GFCLK",
	"XCLK_60M_HSP2",
	"XCLK_60M_HSP1",
	"UTMI_P1_GFCLK",
	"UTMI_P2_GFCLK",
	/* CKGEN_ABE Clocks */
	"PAD_UCLKS",
	"SLIMBUS_UCLKS",
	"ABE_CLK",
	"AESS_FCLK",
	"ABE_GICLK",
	"ABE_24M_FCLK",
	"PAD_GCLKS",
	"SLIMBUS_CLK",
	"MCBSP1_INT_GFCLK",
	"MCBSP2_INT_GFCLK",
	"MCBSP3_INT_GFCLK",
	"MCASP1_INT_GFCLK",
	"DMIC_INT_GFCLK",
	"MCBSP1_GFCLK",
	"MCBSP2_GFCLK",
	"MCBSP3_GFCLK",
	"MCASP1_GFCLK",
	"DMIC_GFCLK",
	"TIMER5_GFCLK",
	"TIMER6_GFCLK",
	"TIMER7_GFCLK",
	"TIMER8_GFCLK",
	/* CM_CORE Clocks */
	"GPU_HYD_GCLK",
	"GPU_CORE_GCLK",
	"FDIF_GFCLK",
	"PER_ABE_24M_FCLK",
	"FUNC_96M_FCLK",
	"FUNC_48M_FCLK",
	"FUNC_24M_FCLK",
	"HSI_FCLK",
	"FUNC_12M_FCLK",
	"MMC1_GFCLK",
	"MMC2_GFCLK",
	"PER_ABE_24M_GFCLK",
	"PER_96M_GFCLK",
	"PER_48M_GFCLK",
	"PER_24M_GFCLK",
	"HSI_GFCLK",
	"PER_12M_GFCLK",
	"C2C_GFCLK", /* ES2.0 only */
	"C2C_ICLK", /* ES2.0 only */
	"C2C_GICLK", /* ES2.0 only */
	"EMIF_LL_GCLK", /* ES2.0 only */
	"GPU_L3_GICLK", /* ES2.0 only */
	"DSS_L4_GICLK", /* ES2.0 only */
	"FIXME"
};


typedef enum {
	SYSCLK54XX_RESERVED_0 = 0,
	SYSCLK54XX_12_MHZ = 1,
	SYSCLK54XX_RESERVED_2 = 2,
	SYSCLK54XX_16_8_MHZ = 3,
	SYSCLK54XX_19_2_MHZ = 4,
	SYSCLK54XX_26_MHZ = 5,
	SYSCLK54XX_RESERVED_6 = 6,
	SYSCLK54XX_38_4_MHZ = 7,
	SYSCLK54XX_ID_MAX
} sysclk54xx_id;


static const double sysclk54xx_rate_table[SYSCLK54XX_ID_MAX] = { /* MHz */
	0.0,
	12.0,
	0.0,
	16.8,
	19.2,
	26.0,
	0.0,
	38.4};



/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clk54xx_name_get
 * @BRIEF		return clock name
 * @RETURNS		clock name on success
 *			NULL in case of error
 * @param[in]		id: clock ID
 * @DESCRIPTION		return clock name
 *//*------------------------------------------------------------------------ */
const char *clk54xx_name_get(clk54xx_id id)
{
	CHECK_ARG_LESS_THAN(id, CLK54XX_ID_MAX + 1, NULL);

	return clk54xx_name_table[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clk54xx_sysclk_rate_get
 * @BRIEF		Return the system clock speed, in MHz.
 * @RETURNS		> 0 system clock speed, in MHz.
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_UNEXPECTED in case of unrecognized clock
 *			speed
 * @param[in]		none
 * @DESCRIPTION		Return the system clock speed, in MHz.
 *//*------------------------------------------------------------------------ */
double clk54xx_sysclk_rate_get(void)
{
	unsigned int val;
	static double sysclk = 0.0;
	static unsigned short valid = 0;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	if (valid) {
		dprintf("%s(): sysclk rate=%.1lfMHz\n", __func__, sysclk);
		return sysclk;
	}

	if (!mem_fake_access_get()) {
		if (cpu_revision_get() == REV_ES1_0)
			val = reg_read(&omap5430es1_cm_clksel_sys);
		else
			val = reg_read(&omap5430_cm_clksel_sys);
		val &= 0x7;
	} else {
		val = SYSCLK54XX_19_2_MHZ; /* PoR */
	}
	sysclk = sysclk54xx_rate_table[val];
	valid = 1;
	dprintf("%s(): CM_CLKSEL_SYS=0x%x, sysclk rate=%.1lfMHz\n",
			__func__, val, sysclk);
	return sysclk;
}


#ifndef CLOCK54XX_DEBUG
/* #define CLK54XX_RATE_GET_DEBUG */
#ifdef CLK54XX_RATE_GET_DEBUG
#undef dprintf
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif
#endif

#define DPRINT_CLK_SPEED1(clk_id, out_clk_speed)\
	dprintf("%s(): %s speed = %fMHz\n",\
	__func__,\
	clk54xx_name_get(clk_id),\
	out_clk_speed);

#define DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed, out_clk_speed)\
	dprintf("%s(): %s src = %s, src speed = %.3fMHz, speed = %fMHz\n",\
	__func__,\
	clk54xx_name_get(clk_id),\
	clk54xx_name_get(src_clk_id),\
	src_clk_speed,\
	out_clk_speed);

#define DPRINT_CLK_SPEED2_DPLL(clk_id, src_clk, src_clk_speed, out_clk_speed)\
	dprintf("%s(): %s src = %s, src speed = %.3fMHz, speed = %fMHz\n",\
	__func__,\
	clk54xx_name_get(clk_id),\
	src_clk,\
	src_clk_speed,\
	out_clk_speed);

#define DPRINT_CLK_SPEED3(clk_id, src_clk_id,\
	src_clk_speed, div, out_clk_speed)\
	dprintf("%s(): %s src = %s, speed = %.3fMHz / %d = %fMHz\n",\
	__func__,\
	clk54xx_name_get(clk_id),\
	clk54xx_name_get(src_clk_id),\
	src_clk_speed,\
	(int) div,\
	out_clk_speed);


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clk54xx_rate_get
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
double clk54xx_rate_get(clk54xx_id clk_id,
	unsigned short ignore)
{
	unsigned int reg_val;
	double src_clk_speed, out_clk_speed;
	clk54xx_id src_clk_id;
	double div;


	if (!cpu_is_omap54xx())
		return (double) OMAPCONF_ERR_CPU;

	switch (clk_id) {
	case CLK54XX_SYS_32K:
		out_clk_speed = (double) 0.032768;
		DPRINT_CLK_SPEED1(clk_id, out_clk_speed);
		return out_clk_speed;

	case CLK54XX_FUNC_32K_CLK:
	case CLK54XX_SECURE_32K_CLK:
		src_clk_id = CLK54XX_SYS_32K;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_HDMI_CEC_GFCLK:
	case CLK54XX_WKUPAON_32K_GFCLK:
	case CLK54XX_COREAON_32K_GFCLK:
	case CLK54XX_PER_32K_GFCLK:
	case CLK54XX_ABE_32K_CLK:
	case CLK54XX_MMC1_32K_GFCLK:
		src_clk_id = CLK54XX_FUNC_32K_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_SYS_CLKIN:
		out_clk_speed = clk54xx_sysclk_rate_get();
		DPRINT_CLK_SPEED1(clk_id, out_clk_speed);
		return out_clk_speed;

	case CLK54XX_SYS_CLK:
		src_clk_id = CLK54XX_SYS_CLKIN;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;


	case CLK54XX_CUSTEFUSE_SYS_GFCLK:
	case CLK54XX_EMU_SYS_CLK:
	case CLK54XX_CORE_DPLL_CLK:
	case CLK54XX_PER_DPLL_CLK:
	case CLK54XX_IVA_DPLL_CLK:
	case CLK54XX_MPU_DPLL_CLK:
	case CLK54XX_UNIPRO2_DPLL_CLK:
	case CLK54XX_USB_DPLL_CLK:
	case CLK54XX_USB_OTG_SS_REF_CLK:
	case CLK54XX_UNIPRO1_DPLL_CLK:
	case CLK54XX_WKUPAON_IO_SRCOMP_GFCLK:
	case CLK54XX_COREAON_IO_SRCOMP_GFCLK:
	case CLK54XX_UNIPRO2_PHY_REF_GFCLK:
	case CLK54XX_MIPIEXT_PHY_REF_GFCLK:
	case CLK54XX_SATA_REF_GFCLK:
		src_clk_id = CLK54XX_SYS_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_ABE_DPLL_CLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_clksel_abe_pll_ref);
		else
			reg_val = reg_read(&omap5430_cm_clksel_abe_pll_ref);
		if (extract_bit(reg_val, 0) == 1)
			src_clk_id = CLK54XX_FUNC_32K_CLK;
		else
			src_clk_id = CLK54XX_SYS_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_ABE_DPLL_BYPASS_CLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_clksel_wkupaon);
		else
			reg_val = reg_read(&omap5430_cm_clksel_wkupaon);
		if (extract_bit(reg_val, 0) == 1)
			src_clk_id = CLK54XX_FUNC_32K_CLK;
		else
			src_clk_id = CLK54XX_SYS_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_DSS_SYS_CLK:
	case CLK54XX_ABE_SYS_CLK:
		src_clk_id = CLK54XX_SYS_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_clksel_abe_dss_sys);
		else
			reg_val = reg_read(&omap5430_cm_clksel_abe_dss_sys);
		if (extract_bit(reg_val, 0) == 1)
			div = 2.0;
		else
			div = 1.0;
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	/* DPLL ABE OUTPUTS */
	case CLK54XX_PER_ABE_X1_GFCLK: /* ES1.0 only */
		if (cpu_revision_get() != REV_ES1_0)
			fprintf(stderr,
				"%s(): WARNING: CLK54XX_PER_ABE_X1_GFCLK clock signal does not exist on ES2.x!!!\n", __func__);
		src_clk_speed = dpll54xx_output_rate_get(
			DPLL54XX_ABE, DPLL54XX_CLKOUT_M2, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_ABE CLKOUT_M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK54XX_DPLL_ABE_X2_FCLK:
		src_clk_speed = dpll54xx_output_rate_get(
			DPLL54XX_ABE, DPLL54XX_CLKOUTX2_M2, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_ABE CLKOUTX2_M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK54XX_CORE_DPLL_HS_CLK:
		src_clk_speed = dpll54xx_output_rate_get(
			DPLL54XX_ABE, DPLL54XX_CLKOUTX2_M3, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_ABE CLKOUTX2_M3",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	/* END OF DPLL ABE OUTPUTS */

	/* DPLL CORE OUTPUTS */
	case CLK54XX_EMIF_PHY_GCLK:
		src_clk_speed = dpll54xx_output_rate_get(
			DPLL54XX_CORE, DPLL54XX_CLKOUT_M2, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_CORE CLKOUT_M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK54XX_CORE_DPLL_SCRM_CLK:
		src_clk_speed = dpll54xx_output_rate_get(
			DPLL54XX_CORE, DPLL54XX_CLKOUTX2_M3, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_CORE CLKOUTX2_M3",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK54XX_CORE_DLL_GCLK:
		src_clk_speed = dpll54xx_output_rate_get(
			DPLL54XX_CORE, DPLL54XX_CLKOUTX2_H11, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_CORE CLKOUTX2_H11",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK54XX_CORE_X2_CLK:
		src_clk_speed = dpll54xx_output_rate_get(
			DPLL54XX_CORE, DPLL54XX_CLKOUTX2_H12, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_CORE CLKOUTX2_H12",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK54XX_CORE_USB_OTG_SS_LFPS_TX_CLK:
		src_clk_speed = dpll54xx_output_rate_get(
			DPLL54XX_CORE, DPLL54XX_CLKOUTX2_H13, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_CORE CLKOUTX2_H13",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK54XX_CORE_GPU_CLK:
		src_clk_speed = dpll54xx_output_rate_get(
			DPLL54XX_CORE, DPLL54XX_CLKOUTX2_H14, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_CORE CLKOUTX2_H14",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK54XX_CORE_C2C_CLK: /* ES2.0 only */
		if (cpu_revision_get() == REV_ES1_0)
			fprintf(stderr,
				"%s(): WARNING: CLK54XX_CORE_C2C_CLK clock signal does not exist on ES1.0!!!\n", __func__);
		src_clk_speed = dpll54xx_output_rate_get(
			DPLL54XX_CORE, DPLL54XX_CLKOUTX2_H21, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_CORE CLKOUTX2_H21",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK54XX_CORE_IPU_ISS_BOOST_CLK:
		src_clk_speed = dpll54xx_output_rate_get(
			DPLL54XX_CORE, DPLL54XX_CLKOUTX2_H22, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_CORE CLKOUTX2_H22",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK54XX_CORE_ISS_MAIN_CLK:
		src_clk_speed = dpll54xx_output_rate_get(
			DPLL54XX_CORE, DPLL54XX_CLKOUTX2_H23, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_CORE CLKOUTX2_H23",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK54XX_BB2D_GFCLK: /* ES2.0 only */
		if (cpu_revision_get() == REV_ES1_0)
			fprintf(stderr,
				"%s(): WARNING: CLK54XX_BB2D_GFCLK clock signal does not exist on ES1.0!!!\n", __func__);
		src_clk_speed = dpll54xx_output_rate_get(
			DPLL54XX_CORE, DPLL54XX_CLKOUTX2_H24, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_CORE CLKOUTX2_H24",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	/* END OF DPLL CORE OUTPUTS */

	/* DPLL PER OUTPUTS */
	case CLK54XX_FUNC_96M_AON_CLK:
		src_clk_speed = dpll54xx_output_rate_get(
			DPLL54XX_PER, DPLL54XX_CLKOUT_M2, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_PER CLKOUT_M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK54XX_FUNC_192M_FCLK:
		src_clk_speed = dpll54xx_output_rate_get(
			DPLL54XX_PER, DPLL54XX_CLKOUTX2_M2, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_PER CLKOUTX2_M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK54XX_PER_DPLL_SCRM_CLK:
		src_clk_speed = dpll54xx_output_rate_get(
			DPLL54XX_PER, DPLL54XX_CLKOUTX2_M3, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_PER CLKOUTX2_M3",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK54XX_FUNC_128M_CLK:
		if (cpu_revision_get() == REV_ES1_0) {
			src_clk_speed = dpll54xx_output_rate_get(
				DPLL54XX_PER, DPLL54XX_CLKOUTX2_H11, ignore);
			out_clk_speed = src_clk_speed;
			DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_PER CLKOUTX2_H11",
				src_clk_speed, out_clk_speed);
			return out_clk_speed;
		} else {
			src_clk_id = CLK54XX_FUNC_256M_CLK;
			src_clk_speed = clk54xx_rate_get(src_clk_id,
				ignore);
			div = 2.0;
			out_clk_speed = src_clk_speed / div;
			DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
				out_clk_speed);
			return out_clk_speed;
		}

	case CLK54XX_FUNC_256M_CLK: /* ES2.0 only */
		if (cpu_revision_get() == REV_ES1_0)
			fprintf(stderr,
				"%s(): WARNING: CLK54XX_FUNC_256M_CLK clock signal does not exist on ES1.0!!!\n", __func__);
		src_clk_speed = dpll54xx_output_rate_get(
			DPLL54XX_PER, DPLL54XX_CLKOUTX2_H11, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_PER CLKOUTX2_H11",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK54XX_DSS_GFCLK:
		src_clk_speed = dpll54xx_output_rate_get(
			DPLL54XX_PER, DPLL54XX_CLKOUTX2_H12, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_PER CLKOUTX2_H12",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK54XX_PER_GPU_CLK:
		src_clk_speed = dpll54xx_output_rate_get(
			DPLL54XX_PER, DPLL54XX_CLKOUTX2_H14, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_PER CLKOUTX2_H14",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	/* END OF DPLL PER OUTPUTS */

	/* DPLL MPU OUTPUTS */
	case CLK54XX_MPU_GCLK:
		src_clk_speed = dpll54xx_output_rate_get(
			DPLL54XX_MPU, DPLL54XX_CLKOUT_M2, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_MPU CLKOUT_M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	/* END OF DPLL MPU OUTPUTS */

	/* DPLL IVA OUTPUTS */
	case CLK54XX_DSP_GCLK:
		src_clk_speed = dpll54xx_output_rate_get(
			DPLL54XX_IVA, DPLL54XX_CLKOUTX2_H11, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_IVA CLKOUTX2_H11",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK54XX_IVA_GCLK:
		src_clk_speed = dpll54xx_output_rate_get(
			DPLL54XX_IVA, DPLL54XX_CLKOUTX2_H12, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_IVA CLKOUTX2_H12",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	/* END OF DPLL IVA OUTPUTS */

	/* DPLL USB OUTPUTS */
	case CLK54XX_L3INIT_480M_GFCLK:
		src_clk_speed = dpll54xx_output_rate_get(
			DPLL54XX_USB, DPLL54XX_CLKOUT_M2, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_USB CLKOUT_M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK54XX_L3INIT_960M_FCLK:
		src_clk_speed = dpll54xx_output_rate_get(
			DPLL54XX_USB, DPLL54XX_CLK_DCO_LDO, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_USB CLK_DCO_LDO",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	/* END OF DPLL USB OUTPUTS */

	/* DPLL UNIPRO1 OUTPUTS */
	case CLK54XX_UNIPRO1_TXPHY_LS_GFCLK:
		src_clk_speed = dpll54xx_output_rate_get(
			DPLL54XX_UNIPRO1, DPLL54XX_CLKOUT_M2, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_UNIPRO1 CLKOUT_M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK54XX_UNIPRO1_PHY_GFCLK:
		src_clk_speed = dpll54xx_output_rate_get(
			DPLL54XX_UNIPRO1, DPLL54XX_CLK_DCO_LDO, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_UNIPRO1 CLK_DCO_LDO",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	/* END OF DPLL UNIPRO1 OUTPUTS */

	/* DPLL UNIPRO2 OUTPUTS */
	case CLK54XX_UNIPRO2_TXPHY_LS_GFCLK:
		src_clk_speed = dpll54xx_output_rate_get(
			DPLL54XX_UNIPRO2, DPLL54XX_CLKOUT_M2, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_UNIPRO2 CLKOUT_M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case CLK54XX_UNIPRO2_PHY_GFCLK:
		src_clk_speed = dpll54xx_output_rate_get(
			DPLL54XX_UNIPRO2, DPLL54XX_CLK_DCO_LDO, ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_UNIPRO2 CLK_DCO_LDO",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	/* END OF DPLL UNIPRO2 OUTPUTS */

	case CLK54XX_MPU_DPLL_HS_CLK:
		src_clk_id = CLK54XX_CORE_X2_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_bypclk_dpll_mpu);
		else
			reg_val = reg_read(&omap5430_cm_bypclk_dpll_mpu);
		div = (double) (1 << extract_bitfield(reg_val, 0, 2));
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_IVA_DPLL_HS_CLK:
		src_clk_id = CLK54XX_CORE_X2_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_bypclk_dpll_iva);
		else
			reg_val = reg_read(&omap5430_cm_bypclk_dpll_iva);
		div = (double) (1 << extract_bitfield(reg_val, 0, 2));
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_PER_DPLL_HS_CLK:
		src_clk_id = CLK54XX_CORE_DPLL_HS_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		div = 2.0;
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_USB_DPLL_HS_CLK:
		src_clk_id = CLK54XX_CORE_DPLL_HS_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		div = 3.0;
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	/* COREAON CLKDM Clocks */
	case CLK54XX_FUNC_24M_CLK:
		src_clk_id = CLK54XX_FUNC_96M_AON_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		div = 4.0;
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_FUNC_24M_GFCLK:
		src_clk_id = CLK54XX_FUNC_24M_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_CORE_CLK:
		src_clk_id = CLK54XX_CORE_X2_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_L3_ICLK:
		src_clk_id = CLK54XX_CORE_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_clksel_core);
		else
			reg_val = reg_read(&omap5430_cm_clksel_core);
		div = (double) (1 << extract_bit(reg_val, 4));
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_C2C_L3_GICLK:  /* ES1.0 only */
		if (cpu_revision_get() != REV_ES1_0)
			fprintf(stderr,
				"%s(): WARNING: CLK54XX_C2C_L3_GICLK clock signal does not exist on ES2.x!!!\n", __func__);
	case CLK54XX_CM_CORE_AON_PROFILING_L3_GICLK:
	case CLK54XX_EMIF_L3_GICLK:
	case CLK54XX_L4SEC_L3_GICLK:
	case CLK54XX_CAM_L3_GICLK:
	case CLK54XX_DMA_L3_GICLK:
	case CLK54XX_L3INSTR_L3_GICLK:
	case CLK54XX_L3MAIN1_L3_GICLK:
	case CLK54XX_L3MAIN2_L3_GICLK:
	case CLK54XX_MIPIEXT_L3_GICLK:
	case CLK54XX_DSS_L3_GICLK:
	case CLK54XX_L3INIT_L3_GICLK:
		src_clk_id = CLK54XX_L3_ICLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_L4_ROOT_CLK:
		src_clk_id = CLK54XX_L3_ICLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_clksel_core);
		else
			reg_val = reg_read(&omap5430_cm_clksel_core);
		div = (double) (1 << extract_bit(reg_val, 8));
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_L4_ICLK:
		src_clk_id = CLK54XX_L4_ROOT_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	/* PRM CLKDM Clocks */
	case CLK54XX_ABE_LP_CLK:
		src_clk_id = CLK54XX_DPLL_ABE_X2_FCLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		div = 16.0;
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed,
			div, out_clk_speed);
		return out_clk_speed;

	case CLK54XX_WKUPAON_ICLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_clksel_wkupaon);
		else
			reg_val = reg_read(&omap5430_cm_clksel_wkupaon);
		if (extract_bit(reg_val, 0) == 1)
			src_clk_id = CLK54XX_ABE_LP_CLK;
		else
			src_clk_id = CLK54XX_SYS_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_SR_MM_SYS_GFCLK:
	case CLK54XX_SR_MPU_SYS_GFCLK:
	case CLK54XX_SR_CORE_SYS_GFCLK:
	case CLK54XX_WKUPAON_GCLK:
		src_clk_id = CLK54XX_WKUPAON_ICLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_WKUPAON_GICLK:
	case CLK54XX_CM_CORE_AON_SYS_CLK:
		src_clk_id = CLK54XX_WKUPAON_GCLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_WKUPAON_PROFILING_GCLK:
		src_clk_id = CLK54XX_WKUPAON_ICLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_CORE_TS_GFCLK: /* ES1.0 only */
	case CLK54XX_COREAON_TS_GFCLK:
		if (cpu_revision_get() != REV_ES1_0)
			fprintf(stderr,
				"%s(): WARNING: CORE[AON]_TS_GFCLK clock signal does not exist on ES2.x!!!\n", __func__);
	case CLK54XX_L3INSTR_DLL_AGING_GCLK:
		src_clk_id = CLK54XX_WKUPAON_ICLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_coreaon_bandgap_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_l3instr_ctrl_module_bandgap_clkctrl);
		div = (double) (8 << extract_bitfield(reg_val, 24, 2));
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_L3INSTR_TS_GFCLK:
		src_clk_id = CLK54XX_WKUPAON_ICLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		reg_val = reg_read(&omap5430_cm_l3instr_ctrl_module_bandgap_clkctrl);
		div = (double) (8 << extract_bitfield(reg_val, 24, 2));
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	/* PRM TIMER Clocks */
	case CLK54XX_TIMER1_GFCLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_wkupaon_timer1_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_wkupaon_timer1_clkctrl);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = CLK54XX_SYS_32K;
		else
			src_clk_id = CLK54XX_SYS_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_TIMER2_GFCLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_l4per_timer2_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_l4per_timer2_clkctrl);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = CLK54XX_SYS_32K;
		else
			src_clk_id = CLK54XX_SYS_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_TIMER3_GFCLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_l4per_timer3_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_l4per_timer3_clkctrl);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = CLK54XX_SYS_32K;
		else
			src_clk_id = CLK54XX_SYS_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_TIMER4_GFCLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_l4per_timer4_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_l4per_timer4_clkctrl);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = CLK54XX_SYS_32K;
		else
			src_clk_id = CLK54XX_SYS_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_TIMER9_GFCLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_l4per_timer9_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_l4per_timer9_clkctrl);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = CLK54XX_SYS_32K;
		else
			src_clk_id = CLK54XX_SYS_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_TIMER10_GFCLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_l4per_timer10_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_l4per_timer10_clkctrl);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = CLK54XX_SYS_32K;
		else
			src_clk_id = CLK54XX_SYS_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_TIMER11_GFCLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_l4per_timer11_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_l4per_timer11_clkctrl);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = CLK54XX_SYS_32K;
		else
			src_clk_id = CLK54XX_SYS_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	/* CKGEN_USB Clocks */
	case CLK54XX_L3INIT_60M_FCLK:
		src_clk_id = CLK54XX_L3INIT_480M_GFCLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_clksel_usb_60mhz);
		else
			reg_val = reg_read(&omap5430_cm_clksel_usb_60mhz);
		if (extract_bit(reg_val, 0) == 1)
			div = 8.0;
		else
			div = 1.0;
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_UTMI_P3_GFCLK:
	case CLK54XX_HSIC_P3_GFCLK:
	case CLK54XX_HSIC_P2_GFCLK:
	case CLK54XX_HSIC_P1_GFCLK:
	case CLK54XX_L3INIT_60M_P1_GFCLK:
	case CLK54XX_L3INIT_60M_P2_GFCLK:
	case CLK54XX_UTMI_ROOT_GFCLK:
	case CLK54XX_TLL_CH0_GFCLK:
	case CLK54XX_TLL_CH1_GFCLK:
	case CLK54XX_TLL_CH2_GFCLK:
		src_clk_id = CLK54XX_L3INIT_60M_FCLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_HSIC_P1_480M_GFCLK:
	case CLK54XX_HSIC_P2_480M_GFCLK:
	case CLK54XX_HSIC_P3_480M_GFCLK:
		src_clk_id = CLK54XX_L3INIT_480M_GFCLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_XCLK_60M_HSP2:
	case CLK54XX_XCLK_60M_HSP1:
		/* external clock, asssume 60M */
		dprintf("%s(): WARNING %s is external clock, "
			"cannot determine the frequency. Assuming 60MHz.\n",
			__func__, clk54xx_name_get(clk_id));
		return 60.0;

	case CLK54XX_UTMI_P1_GFCLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_l3init_usb_host_hs_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_l3init_usb_host_hs_clkctrl);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = CLK54XX_XCLK_60M_HSP1;
		else
			src_clk_id = CLK54XX_L3INIT_60M_P1_GFCLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_UTMI_P2_GFCLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_l3init_usb_host_hs_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_l3init_usb_host_hs_clkctrl);
		if (extract_bit(reg_val, 25) == 1)
			src_clk_id = CLK54XX_XCLK_60M_HSP2;
		else
			src_clk_id = CLK54XX_L3INIT_60M_P2_GFCLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	/* CKGEN_ABE Clocks */
	case CLK54XX_PAD_UCLKS:
		dprintf("%s(): WARNING %s is external clock, "
			"cannot determine the frequency. Assuming 19.2MHz.\n",
			__func__, clk54xx_name_get(clk_id));
		out_clk_speed = (double) 19.2;
		DPRINT_CLK_SPEED1(clk_id, out_clk_speed);
		return out_clk_speed;

	case CLK54XX_SLIMBUS_UCLKS:
		dprintf("%s(): WARNING %s is external clock, "
			"cannot determine the frequency. Assuming 24.576MHz.\n",
			__func__, clk54xx_name_get(clk_id));
		out_clk_speed = (double) 24.576;
		DPRINT_CLK_SPEED1(clk_id, out_clk_speed);
		return out_clk_speed;

	case CLK54XX_PAD_GCLKS:
		src_clk_id = CLK54XX_PAD_UCLKS;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_SLIMBUS_CLK:
		src_clk_id = CLK54XX_SLIMBUS_UCLKS;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_ABE_CLK:
		src_clk_id = CLK54XX_DPLL_ABE_X2_FCLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_clksel_abe);
		else
			reg_val = reg_read(&omap5430_cm_clksel_abe);
		div = (double) (1 << extract_bitfield(reg_val, 0, 2));
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_AESS_FCLK:
		src_clk_id = CLK54XX_ABE_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_abe_aess_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_abe_aess_clkctrl);
		div = (double) (1 << extract_bit(reg_val, 24));
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_ABE_GICLK:
		src_clk_id = CLK54XX_AESS_FCLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_abe_aess_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_abe_aess_clkctrl);
		div = (double) (1 << extract_bit(reg_val, 24));
		/* From TRM: ABE_ICLK2 depends on the divider settings of
		 * the AESS_FCLK and is always divided by 2 of the ABE_CLK.
		 * Therefore, when the AESS_FCLK divider is set to 1,
		 * the ABE_ICLK2 divider is set to 2, and vice versa. */
		div = 3.0 - div;
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_ABE_24M_FCLK:
		src_clk_id = CLK54XX_DPLL_ABE_X2_FCLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		div = 8.0;
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_TIMER5_GFCLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_abe_timer5_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_abe_timer5_clkctrl);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = CLK54XX_ABE_32K_CLK;
		else
			src_clk_id = CLK54XX_ABE_SYS_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_TIMER6_GFCLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_abe_timer6_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_abe_timer6_clkctrl);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = CLK54XX_ABE_32K_CLK;
		else
			src_clk_id = CLK54XX_ABE_SYS_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_TIMER7_GFCLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_abe_timer7_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_abe_timer7_clkctrl);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = CLK54XX_ABE_32K_CLK;
		else
			src_clk_id = CLK54XX_ABE_SYS_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_TIMER8_GFCLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_abe_timer8_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_abe_timer8_clkctrl);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = CLK54XX_ABE_32K_CLK;
		else
			src_clk_id = CLK54XX_ABE_SYS_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_MCBSP1_INT_GFCLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_abe_mcbsp1_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_abe_mcbsp1_clkctrl);
		switch (extract_bitfield(reg_val, 26, 2)) {
		case 0:
			src_clk_id = CLK54XX_ABE_24M_FCLK;
			break;
		case 1:
			src_clk_id = CLK54XX_ABE_SYS_CLK;
			break;
		case 2:
			src_clk_id = CLK54XX_FUNC_24M_GFCLK;
			break;
		default:
			fprintf(stderr, "%s(): ERROR \'Reserved\' value read "
				"from OMAP5430_CM_ABE_MCBSP1_CLKCTRL bitfield "
				"(%u) !!!\n", __func__,
				extract_bitfield(reg_val, 26, 2));
			return OMAPCONF_ERR_UNEXPECTED;
		}
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_MCBSP1_GFCLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_abe_mcbsp1_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_abe_mcbsp1_clkctrl);
		switch (extract_bitfield(reg_val, 24, 2)) {
		case 0:
			src_clk_id = CLK54XX_MCBSP1_INT_GFCLK;
			break;
		case 1:
			src_clk_id = CLK54XX_PAD_GCLKS;
			break;
		case 2:
			src_clk_id = CLK54XX_SLIMBUS_CLK;
			break;
		default:
			fprintf(stderr, "%s(): ERROR \'Reserved\' value read "
				"from OMAP5430_CM_ABE_MCBSP1_CLKCTRL bitfield "
				"(%u) !!!\n", __func__,
				extract_bitfield(reg_val, 24, 2));
			return OMAPCONF_ERR_UNEXPECTED;
		}
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_MCBSP2_INT_GFCLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_abe_mcbsp2_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_abe_mcbsp2_clkctrl);
		switch (extract_bitfield(reg_val, 26, 2)) {
		case 0:
			src_clk_id = CLK54XX_ABE_24M_FCLK;
			break;
		case 1:
			src_clk_id = CLK54XX_ABE_SYS_CLK;
			break;
		case 2:
			src_clk_id = CLK54XX_FUNC_24M_GFCLK;
			break;
		default:
			fprintf(stderr, "%s(): ERROR \'Reserved\' value read "
				"from OMAP5430_CM_ABE_MCBSP2_CLKCTRL bitfield "
				"(%u) !!!\n", __func__,
				extract_bitfield(reg_val, 26, 2));
			return OMAPCONF_ERR_UNEXPECTED;
		}
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_MCBSP2_GFCLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_abe_mcbsp2_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_abe_mcbsp2_clkctrl);
		switch (extract_bitfield(reg_val, 24, 2)) {
		case 0:
			src_clk_id = CLK54XX_MCBSP2_INT_GFCLK;
			break;
		case 1:
			src_clk_id = CLK54XX_PAD_GCLKS;
			break;
		case 2:
			src_clk_id = CLK54XX_SLIMBUS_CLK;
			break;
		default:
			fprintf(stderr, "%s(): ERROR \'Reserved\' value read "
				"from OMAP5430_CM_ABE_MCBSP2_CLKCTRL bitfield "
				"(%u) !!!\n", __func__,
				extract_bitfield(reg_val, 24, 2));
			return OMAPCONF_ERR_UNEXPECTED;
		}
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_MCBSP3_INT_GFCLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_abe_mcbsp3_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_abe_mcbsp3_clkctrl);
		switch (extract_bitfield(reg_val, 26, 2)) {
		case 0:
			src_clk_id = CLK54XX_ABE_24M_FCLK;
			break;
		case 1:
			src_clk_id = CLK54XX_ABE_SYS_CLK;
			break;
		case 2:
			src_clk_id = CLK54XX_FUNC_24M_GFCLK;
			break;
		default:
			fprintf(stderr, "%s(): ERROR \'Reserved\' value read "
				"from OMAP5430_CM_ABE_MCBSP3_CLKCTRL bitfield "
				"(%u) !!!\n", __func__,
				extract_bitfield(reg_val, 26, 2));
			return OMAPCONF_ERR_UNEXPECTED;
		}
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_MCBSP3_GFCLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_abe_mcbsp3_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_abe_mcbsp3_clkctrl);
		switch (extract_bitfield(reg_val, 24, 2)) {
		case 0:
			src_clk_id = CLK54XX_MCBSP3_INT_GFCLK;
			break;
		case 1:
			src_clk_id = CLK54XX_PAD_GCLKS;
			break;
		case 2:
			src_clk_id = CLK54XX_SLIMBUS_CLK;
			break;
		default:
			fprintf(stderr, "%s(): ERROR \'Reserved\' value read "
				"from OMAP5430_CM_ABE_MCBSP3_CLKCTRL bitfield "
				"(%u) !!!\n", __func__,
				extract_bitfield(reg_val, 24, 2));
			return OMAPCONF_ERR_UNEXPECTED;
		}
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_MCASP1_INT_GFCLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_abe_mcasp_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_abe_mcasp_clkctrl);
		switch (extract_bitfield(reg_val, 26, 2)) {
		case 0:
			src_clk_id = CLK54XX_ABE_24M_FCLK;
			break;
		case 1:
			src_clk_id = CLK54XX_ABE_SYS_CLK;
			break;
		case 2:
			src_clk_id = CLK54XX_FUNC_24M_GFCLK;
			break;
		default:
			fprintf(stderr, "%s(): ERROR \'Reserved\' value read "
				"from OMAP5430_CM_ABE_MCASP_CLKCTRL bitfield "
				"(%u) !!!\n", __func__,
				extract_bitfield(reg_val, 26, 2));
			return OMAPCONF_ERR_UNEXPECTED;
		}
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_MCASP1_GFCLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_abe_mcasp_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_abe_mcasp_clkctrl);
		switch (extract_bitfield(reg_val, 24, 2)) {
		case 0:
			src_clk_id = CLK54XX_MCASP1_INT_GFCLK;
			break;
		case 1:
			src_clk_id = CLK54XX_PAD_GCLKS;
			break;
		case 2:
			src_clk_id = CLK54XX_SLIMBUS_CLK;
			break;
		default:
			fprintf(stderr, "%s(): ERROR \'Reserved\' value read "
				"from OMAP5430_CM_ABE_MCASP_CLKCTRL bitfield "
				"(%u) !!!\n", __func__,
				extract_bitfield(reg_val, 24, 2));
			return OMAPCONF_ERR_UNEXPECTED;
		}
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_DMIC_INT_GFCLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_abe_dmic_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_abe_dmic_clkctrl);
		switch (extract_bitfield(reg_val, 26, 2)) {
		case 0:
			src_clk_id = CLK54XX_ABE_24M_FCLK;
			break;
		case 1:
			src_clk_id = CLK54XX_ABE_SYS_CLK;
			break;
		case 2:
			src_clk_id = CLK54XX_FUNC_24M_GFCLK;
			break;
		default:
			fprintf(stderr, "%s(): ERROR \'Reserved\' value read "
				"from OMAP5430_CM_ABE_DMIC_CLKCTRL bitfield "
				"(%u) !!!\n", __func__,
				extract_bitfield(reg_val, 26, 2));
			return OMAPCONF_ERR_UNEXPECTED;
		}
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_DMIC_GFCLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_abe_dmic_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_abe_dmic_clkctrl);
		switch (extract_bitfield(reg_val, 24, 2)) {
		case 0:
			src_clk_id = CLK54XX_DMIC_INT_GFCLK;
			break;
		case 1:
			src_clk_id = CLK54XX_PAD_GCLKS;
			break;
		case 2:
			src_clk_id = CLK54XX_SLIMBUS_CLK;
			break;
		default:
			fprintf(stderr, "%s(): ERROR \'Reserved\' value read "
				"from OMAP5430_CM_ABE_DMIC_CLKCTRL bitfield "
				"(%u) !!!\n", __func__,
				extract_bitfield(reg_val, 24, 2));
			return OMAPCONF_ERR_UNEXPECTED;
		}
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	/* CM_CORE Clocks */
	case CLK54XX_GPU_HYD_GCLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_gpu_gpu_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_gpu_gpu_clkctrl);
		if (extract_bit(reg_val, 25) == 1)
			src_clk_id = CLK54XX_PER_GPU_CLK;
		else
			src_clk_id = CLK54XX_CORE_GPU_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_GPU_CORE_GCLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_gpu_gpu_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_gpu_gpu_clkctrl);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = CLK54XX_PER_GPU_CLK;
		else
			src_clk_id = CLK54XX_CORE_GPU_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_FDIF_GFCLK:
		src_clk_id = CLK54XX_FUNC_128M_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_cam_fdif_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_cam_fdif_clkctrl);
		div = (double) (1 << extract_bit(reg_val, 24));
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_PER_ABE_24M_FCLK: /* ES1.0 only */
		if (cpu_revision_get() != REV_ES1_0)
			fprintf(stderr,
				"%s(): WARNING: CLK54XX_PER_ABE_24M_FCLK clock signal does not exist on ES2.x!!!\n", __func__);
		src_clk_id = CLK54XX_PER_ABE_X1_GFCLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		div = 4.0;
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_FUNC_96M_FCLK:
		src_clk_id = CLK54XX_FUNC_192M_FCLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		div = 2.0;
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_FUNC_48M_FCLK:
		src_clk_id = CLK54XX_FUNC_192M_FCLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		div = 4.0;
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_FUNC_24M_FCLK: /* ES1.0 only */
		if (cpu_revision_get() != REV_ES1_0)
			fprintf(stderr,
				"%s(): WARNING: CLK54XX_FUNC_24M_FCLK clock signal does not exist on ES2.x!!!\n", __func__);
		src_clk_id = CLK54XX_FUNC_192M_FCLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		div = 8.0;
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_HSI_FCLK:
		src_clk_id = CLK54XX_FUNC_192M_FCLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_l3init_hsi_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_l3init_hsi_clkctrl);
		div = (double) (1 << extract_bit(reg_val, 24));
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_FUNC_12M_FCLK:
		src_clk_id = CLK54XX_FUNC_192M_FCLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		div = 16.0;
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_MMC1_GFCLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_l3init_mmc1_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_l3init_mmc1_clkctrl);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = CLK54XX_FUNC_192M_FCLK;
		else
			src_clk_id = CLK54XX_FUNC_128M_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);

		div = (double) (1 << extract_bit(reg_val, 25));
		out_clk_speed = src_clk_speed / div;

		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_MMC2_GFCLK:
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_l3init_mmc2_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_l3init_mmc2_clkctrl);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = CLK54XX_FUNC_192M_FCLK;
		else
			src_clk_id = CLK54XX_FUNC_128M_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);

		div = (double) (1 << extract_bit(reg_val, 25));
		out_clk_speed = src_clk_speed / div;

		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_PER_ABE_24M_GFCLK: /* ES1.0 only */
		if (cpu_revision_get() != REV_ES1_0)
			fprintf(stderr,
				"%s(): WARNING: CLK54XX_PER_ABE_24M_GFCLK clock signal does not exist on ES2.x!!!\n", __func__);
		src_clk_id = CLK54XX_PER_ABE_24M_FCLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_PER_96M_GFCLK:
		src_clk_id = CLK54XX_FUNC_96M_FCLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_PER_48M_GFCLK:
		src_clk_id = CLK54XX_FUNC_48M_FCLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_PER_24M_GFCLK: /* ES1.0 only */
		if (cpu_revision_get() != REV_ES1_0)
			fprintf(stderr,
				"%s(): WARNING: CLK54XX_PER_24M_GFCLK clock signal does not exist on ES2.x!!!\n", __func__);
		src_clk_id = CLK54XX_FUNC_24M_FCLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_HSI_GFCLK:
		src_clk_id = CLK54XX_HSI_FCLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_PER_12M_GFCLK:
		src_clk_id = CLK54XX_FUNC_12M_FCLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_C2C_GFCLK: /* ES2.0 only */
		if (cpu_revision_get() == REV_ES1_0)
			fprintf(stderr,
				"%s(): WARNING: CLK54XX_C2C_GFCLK clock signal does not exist on ES1.0!!!\n", __func__);
		src_clk_id = CLK54XX_CORE_C2C_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_C2C_ICLK: /* ES2.0 only */
		if (cpu_revision_get() == REV_ES1_0)
			fprintf(stderr,
				"%s(): WARNING: CLK54XX_C2C_ICLK clock signal does not exist on ES1.0!!!\n", __func__);
		src_clk_id = CLK54XX_CORE_C2C_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		div = 2.0;
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_C2C_GICLK:/* ES2.0 only */
		if (cpu_revision_get() == REV_ES1_0)
			fprintf(stderr,
				"%s(): WARNING: CLK54XX_C2C_GICLK clock signal does not exist on ES1.0!!!\n", __func__);
		src_clk_id = CLK54XX_C2C_ICLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_EMIF_LL_GCLK: /* ES2.0 only */
		if (cpu_revision_get() == REV_ES1_0)
			fprintf(stderr,
				"%s(): WARNING:CLK54XX_EMIF_LL_GCLK  clock signal does not exist on ES1.0!!!\n", __func__);
		reg_val = reg_read(&omap5430_cm_emif_emif1_clkctrl);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = CLK54XX_L3_ICLK;
		else
			src_clk_id = CLK54XX_C2C_ICLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);

		div = (double) (1 << extract_bit(reg_val, 25));
		out_clk_speed = src_clk_speed / div;

		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_GPU_L3_GICLK: /* ES2.0 only */
		if (cpu_revision_get() == REV_ES1_0)
			fprintf(stderr,
				"%s(): WARNING: CLK54XX_GPU_L3_GICLK clock signal does not exist on ES1.0!!!\n", __func__);
		src_clk_id = CLK54XX_L3_ICLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		if (cpu_revision_get() == REV_ES1_0)
			reg_val = reg_read(&omap5430es1_cm_gpu_gpu_clkctrl);
		else
			reg_val = reg_read(&omap5430_cm_gpu_gpu_clkctrl);
		div = (double) (1 << extract_bit(reg_val, 26));
		out_clk_speed = src_clk_speed / div;

		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;

	/* L4 Clocks */
	case CLK54XX_CM_CORE_AON_PROFILING_L4_GICLK:
		src_clk_id = CLK54XX_L4_ROOT_CLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case CLK54XX_DSS_L4_GICLK: /* ES2.0 only */
		if (cpu_revision_get() == REV_ES1_0)
			fprintf(stderr,
				"%s(): WARNING: CLK54XX_DSS_L4_GICLK clock signal does not exist on ES1.0!!!\n", __func__);
	case CLK54XX_L4PER_L4_GICLK:
	case CLK54XX_L4SEC_L4_GICLK:
	case CLK54XX_C2C_L4_GICLK:
	case CLK54XX_L4CFG_L4_GICLK:
	case CLK54XX_MIPIEXT_L4_GICLK:
	case CLK54XX_L3INIT_L4_GICLK:
		src_clk_id = CLK54XX_L4_ICLK;
		src_clk_speed = clk54xx_rate_get(src_clk_id,
			ignore);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	default:
		fprintf(stderr, "%s(): invalid clock id (%u)!\n",
			__func__, clk_id);
		return (double) OMAPCONF_ERR_ARG;
	}

	return 0;
}
