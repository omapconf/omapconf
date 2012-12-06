/*
 *
 * @Component			OMAPCONF
 * @Filename			clock44xx.c
 * @Description			OMAP4 PRCM Clocks Definitions & Functions
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


#include <clock44xx.h>
#include <string.h>
#include <cpuinfo.h>
#include <lib.h>
#include <mem.h>
#include <cm44xx.h>
#include <prm44xx.h>
#include <dpll44xx.h>


/* #define CLOCK44XX_DEBUG */
#ifdef CLOCK44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


const char
	clock44xx_name_table[OMAP4_CLOCK_ID_MAX][CLOCK44XX_MAX_NAME_LENGTH] = {
	"SYS_CLK",
	"FUNC_32K_CLK",
	"PER_SYS_GFCLK",
	"CUST_EFUSE_SYS_CLK",
	"STD_EFUSE_SYS_CLK",
	"EMU_SYS_CLK",
	"ABE_DPLL_BYPASS_CLK",
	"ABE_ALWON_32K_CLK",
	"PER_32K_GFCLK",
	"CORE_32K_GFCLK",
	"WKUP_32K_GFCLK",
	"ABE_LP_CLK",
	"L4WKUP_ICLK",
	"WKUP_L4_ICLK1",
	"WKUP_L4_ICLK2",
	"CM1_SYS_CLK",
	"SR_MPU_SYS_CLK",
	"SR_IVA_SYS_CLK",
	"SR_CORE_SYS_CLK",
	"ABE_DSS_SYS_CLK",
	"DSS_ALWON_SYS_CLK",
	"ABE_SYSCLK",
	"DPLL_SYS_REF_CLK",
	"CORE_DPLL_ALWON_CLK",
	"PER_DPLL_ALWON_CLK",
	"IVA_DPLL_ALWON_CLK",
	"MPU_DPLL_ALWON_CLK",
	"L3INIT_DPLL_ALWON_CLK",
	"ABE_DPLL_ALWON_CLK",
	"GPT1_FCLK",
	"GPT2_FCLK",
	"GPT3_FCLK",
	"GPT4_FCLK",
	"GPT9_FCLK",
	"GPT10_FCLK",
	"GPT11_FCLK",
	"GPT12_FCLK",
	"PHY_ROOT_CLK",
	"CORE_DPLL_SCRM_CLK",
	"DLL_X2_CLK",
	"CORE_X2_CLK",
	"CORE_DPLL_EMU_CLK",
	"CORE_GFX_FCLK",
	"96M_ALWON_FCLK",
	"192M_FCLK",
	"PER_DPLL_SCRM_CLK",
	"128M_FCLK",
	"DSS_FCLK",
	"PER_MPU_M3_CLK",
	"PER_DPLL_EMU_CLK",
	"PER_ABE_X1_FCLK",
	"DPLL_ABE_X2_FCLK",
	"CORE_DPLL_HS_CLK",
	"MPU_DPLL_CLK",
	"DSP_ROOT_CLK",
	"IVAHD_ROOT_CLK",
	"INIT_480M_FCLK",
	"INIT_960M_FCLK",
	"CLK_DCO_LDO",
	"UNIPRO1_PHY_FCLK",
	"DLL_CLK",
	"CORE_CLK",
	"CORE_MPU_M3_CLK",
	"L3_ICLK",
	"L4_ROOT_CLK",
	"L4_ICLK",
	"MPU_DPLL_HS_CLK",
	"IVA_DPLL_HS_CLK",
	"IVA_HSD_BYP_CLK",
	"CORE_PHY_HSD_BYP_CLK",
	"USB_DPLL_HS_CLK",
	"PER_DPLL_HS_CLK",
	"PER_HSD_BYP_CLK",
	"24M_FCLK",
	"HSIC_P2_480M_FCLK",
	"HSIC_P1_480M_FCLK",
	"INIT_60M_FCLK",
	"TLL_CH2_FCLK",
	"TLL_CH1_FCLK",
	"TLL_CH0_FCLK",
	"UTMI_ROOT_FCLK",
	"INIT_60M_P2_FCLK",
	"INIT_60M_P1_FCLK",
	"HSIC_P1_FCLK",
	"HSIC_P2_FCLK",
	"XCLK_60M_OTG",
	"XCLK_60M_HSP2",
	"XCLK_60M_HSP1",
	"UTMI_P1_FCLK",
	"UTMI_P2_FCLK",
	"OTG_60M_FCLK",
	"PHY_CLKOUT",
	"PAD_UCLKS",
	"SLIMBUS_UCLKS",
	"ABE_CLK",
	"AESS_FCLK",
	"ABE_ICLK2",
	"ABE_24M_FCLK",
	"PAD_CLKS",
	"SLIMBUS_CLKS",
	"MCBSP1_INT_FCLK",
	"MCBSP2_INT_FCLK",
	"MCBSP3_INT_FCLK",
	"MCASP1_INT_FCLK",
	"DMIC_ABE_INT_FCLK",
	"MCBSP1_FCLK",
	"MCBSP2_FCLK",
	"MCBSP3_FCLK",
	"MCASP1_FCLK",
	"DMIC_ABE_FCLK",
	"ABE_GPT5_FCLK",
	"ABE_GPT6_FCLK",
	"ABE_GPT7_FCLK",
	"ABE_GPT8_FCLK",
	"GFX_L3_ICLK",
	"INSTR_L3_ICLK",
	"DMA_L3_ICLK",
	"DSS_L3_ICLK",
	"EMIF_L3_ICLK",
	"INIT_L3_ICLK",
	"L3_ICLK1",
	"L3_ICLK2",
	"C2C_L3_ICLK",
	"CFG_L4_ICLK",
	"INSTR_L4_ICLK",
	"DMA_L4_ICLK",
	"DSS_L4_ICLK",
	"AO_L4_ICLK",
	"EMIF_L4_ICLK",
	"C2C_L4_ICLK",
	"INIT_L4_ICLK",
	"L4_ICLK2",
	"L4_ICLK1",
	"PER_L4_ICLK",
	"MPU_M3_ISS_CLK",
	"ISS_CLK",
	"MPU_M3_CLK",
	"64M_FCLK",
	"FDIF_FCLK",
	"PER_ABE_NC_FCLK",
	"PER_ABE_24M_FCLK",
	"96M_FCLK",
	"PER_48M_FCLK",
	"48M_FCLK",
	"INIT_48M_FCLK",
	"48MC_FCLK",
	"24MC_FCLK",
	"PER_24MC_FCLK",
	"12M_FCLK",
	"HSI_FCLK",
	"INIT_HSI_FCLK",
	"PER_GFX_FCLK",
	"HSMMC1_FCLK",
	"MMC1_FCLK",
	"HSMMC2_FCLK",
	"MMC2_FCLK",
	"PER_MCBSP4_FCLK",
	"PER_MCBSP4_INT_FCLK",
	"HDMI_PHY_48M_FCLK",
	"INIT_48MC_FCLK",
	"GFX_FCLK",
	"C2C_L3X2_ICLK",
	"PER_96M_FCLK",
	"USIM_FCLK",
	"SECURE_32K_CLK",
	"L3_SECURE_GICLK",
	"L4_SECURE_GICLK",
	"L3_INSTR_GICLK",
	"SLIMBUS_CORE_UCLKS",
	"CORE_BB2D_FCLK",
	"PER_BB2D_FCLK",
	"BB2D_FCLK",
	"UNDEF_CLK"
};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clk44xx_get_name
 * @BRIEF		return clock name
 * @RETURNS		clock name on success
 *			NULL in case of error
 * @param[in]		id: clock ID
 * @param[in,out]	name: clock name
 * @DESCRIPTION		return clock name
 *//*------------------------------------------------------------------------ */
char *clk44xx_get_name(clock44xx_id id, char name[CLOCK44XX_MAX_NAME_LENGTH])
{
	if ((id >= OMAP4_CLOCK_ID_MAX) || (name == NULL))
		return NULL;
	else
		strcpy(name, clock44xx_name_table[id]);

	return name;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clk44xx_get_system_clock_speed
 * @BRIEF		Return the system clock speed, in MHz.
 * @RETURNS		> 0 system clock speed, in MHz.
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in]		none
 * @DESCRIPTION		Return the system clock speed, in MHz.
 *//*------------------------------------------------------------------------ */
double clk44xx_get_system_clock_speed(void)
{
	unsigned int osc_clkspeed;

	if (!cpu_is_omap44xx())
		return (double) OMAPCONF_ERR_CPU;

	if (mem_read(OMAP4430_CM_SYS_CLKSEL, &osc_clkspeed) != 0)
		return (double) OMAPCONF_ERR_REG_ACCESS;
	osc_clkspeed &= 0x7;
	dprintf("%s(): osc_clkspeed = %d\n", __func__, osc_clkspeed);
	switch (osc_clkspeed) {
	case 0:
		fprintf(stderr,
			"omapconf: SYS_CLKSEL=0: System clock input selection UNINITIALIZED!\n");
		return (double) OMAPCONF_ERR_UNEXPECTED;
	case 1:
		dprintf("%s(): crystal rate = 12MHz\n", __func__);
		return 12.0; /* 12MHz */
	case 2:
		dprintf("%s(): crystal rate = 13MHz\n", __func__);
		return 13.0; /* 13MHz */
	case 3:
		dprintf("%s(): crystal rate = 16.8MHz\n", __func__);
		return 16.8; /* 16.8MHz */
	case 4:
		dprintf("%s(): crystal rate = 19.2MHz\n", __func__);
		return 19.2; /* 19.2MHz */
	case 5:
		dprintf("%s(): crystal rate = 26MHz\n", __func__);
		return 26.0; /* 26MHz */
	case 6:
		dprintf("%s(): crystal rate = 27MHz\n", __func__);
		return 27.0; /* 27MHz */
	case 7:
		dprintf("%s(): crystal rate = 38.4MHz\n", __func__);
		return 38.4f; /* 38.4MHz */
	default:
		return (double) OMAPCONF_ERR_UNEXPECTED;
	}
}


#ifndef CLOCK44XX_DEBUG
/* #define CLK44XX_GET_CLOCK_SPEED_DEBUG */
#ifdef CLK44XX_GET_CLOCK_SPEED_DEBUG
#undef dprintf
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif
#endif

#define DPRINT_CLK_SPEED1(clk_id, out_clk_speed)\
	dprintf("clk44xx_get_clock_speed(): "\
	"%s speed = %lfMHz\n",\
	clk44xx_get_name(clk_id, clk_name),\
	out_clk_speed);

#define DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed, out_clk_speed)\
	dprintf("clk44xx_get_clock_speed(): "\
	"%s src = %s, src speed = %.3lfMHz, speed = %lfMHz\n",\
	clk44xx_get_name(clk_id, clk_name),\
	clk44xx_get_name(src_clk_id, src_clk_name),\
	src_clk_speed,\
	out_clk_speed);

#define DPRINT_CLK_SPEED2_DPLL(clk_id, src_clk, src_clk_speed, out_clk_speed)\
	dprintf("clk44xx_get_clock_speed(): "\
	"%s src = %s, src speed = %.3lfMHz, speed = %lfMHz\n",\
	clk44xx_get_name(clk_id, clk_name),\
	src_clk,\
	src_clk_speed,\
	out_clk_speed);

#define DPRINT_CLK_SPEED3(clk_id, src_clk_id,\
	src_clk_speed, div, out_clk_speed)\
	dprintf("clk44xx_get_clock_speed(): "\
	"%s src = %s, speed = %.3lfMHz / %d = %lfMHz\n",\
	clk44xx_get_name(clk_id, clk_name),\
	clk44xx_get_name(src_clk_id, src_clk_name),\
	src_clk_speed,\
	(int) div,\
	out_clk_speed);


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clk44xx_get_clock_speed
 * @BRIEF		convert bitfield value from register into string
 * @RETURNS		> 0 clock speed in MHz
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		clk_id: omap4 clock id
 * @param[in]		ignore_stop_status: do not consider DPLL status.
 *			Useful for functions that needs the DPLL output speed
 *			whatever its status (e.g. audit, clock tree, etc)
 * @DESCRIPTION		convert bitfield value from register into string
 *//*------------------------------------------------------------------------ */
double clk44xx_get_clock_speed(clock44xx_id clk_id,
	unsigned short ignore_stop_status)
{
	unsigned int reg_val;
	omap4_dpll_params dpll_params;
	int ret;
	double src_clk_speed, out_clk_speed;
	clock44xx_id src_clk_id;
	double div;
	#if defined (CLK44XX_GET_CLOCK_SPEED_DEBUG) || defined (CLOCK44XX_DEBUG)
	char clk_name[CLOCK44XX_MAX_NAME_LENGTH];
	char src_clk_name[CLOCK44XX_MAX_NAME_LENGTH];
	#endif

	if (!cpu_is_omap44xx())
		return (double) OMAPCONF_ERR_CPU;

	switch (clk_id) {
	case OMAP4_SYS_CLK:
		out_clk_speed = clk44xx_get_system_clock_speed();
		DPRINT_CLK_SPEED1(clk_id, out_clk_speed);
		return out_clk_speed;
	case OMAP4_FUNC_32K_CLK:
	case OMAP4_SECURE_32K_CLK:
		out_clk_speed = (double) 0.032768;
		DPRINT_CLK_SPEED1(clk_id, out_clk_speed);
		return out_clk_speed;
	case OMAP4_PER_SYS_GFCLK:
		src_clk_id = OMAP4_SYS_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_CUST_EFUSE_SYS_CLK:
		src_clk_id = OMAP4_SYS_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_STD_EFUSE_SYS_CLK:
		src_clk_id = OMAP4_SYS_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_EMU_SYS_CLK:
		src_clk_id = OMAP4_SYS_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_ABE_DPLL_BYPASS_CLK:
		if (cpu_is_omap4430() && (cpu_revision_get() == REV_ES1_0)) {
			src_clk_id = OMAP4_SYS_CLK;
			src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
				ignore_stop_status);
			out_clk_speed = src_clk_speed;
			DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
				out_clk_speed);
			return out_clk_speed;
		} else {
			OMAP_READREG(OMAP4430_CM_L4_WKUP_CLKSEL, reg_val);
			if (extract_bit(reg_val, 0) == 1)
				src_clk_id = OMAP4_FUNC_32K_CLK;
			else
				src_clk_id = OMAP4_SYS_CLK;
			src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
				ignore_stop_status);
			out_clk_speed = src_clk_speed;
			DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
				out_clk_speed);
			return out_clk_speed;
		}

	case OMAP4_ABE_ALWON_32K_CLK:
		src_clk_id = OMAP4_FUNC_32K_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_PER_32K_GFCLK:
		src_clk_id = OMAP4_FUNC_32K_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_CORE_32K_GFCLK:
		src_clk_id = OMAP4_FUNC_32K_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_WKUP_32K_GFCLK:
		src_clk_id = OMAP4_FUNC_32K_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_ABE_LP_CLK:
		src_clk_id = OMAP4_DPLL_ABE_X2_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		div = 16.0;
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed,
			div, out_clk_speed);
		return out_clk_speed;
	case OMAP4_ABE_24M_FCLK:
		src_clk_id = OMAP4_DPLL_ABE_X2_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		div = 8.0;
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed,
			div, out_clk_speed);
		return out_clk_speed;
	case OMAP4_L4WKUP_ICLK:
		OMAP_READREG(OMAP4430_CM_L4_WKUP_CLKSEL, reg_val);
		if (extract_bit(reg_val, 0) == 1)
			src_clk_id = OMAP4_ABE_LP_CLK;
		else
			src_clk_id = OMAP4_SYS_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_WKUP_L4_ICLK1:
		src_clk_id = OMAP4_L4WKUP_ICLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_WKUP_L4_ICLK2:
		src_clk_id = OMAP4_L4WKUP_ICLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_CM1_SYS_CLK:
		src_clk_id = OMAP4_WKUP_L4_ICLK1;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_SR_MPU_SYS_CLK:
		src_clk_id = OMAP4_WKUP_L4_ICLK2;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_SR_IVA_SYS_CLK:
		src_clk_id = OMAP4_WKUP_L4_ICLK2;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_SR_CORE_SYS_CLK:
		src_clk_id = OMAP4_WKUP_L4_ICLK2;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_ABE_DSS_SYS_CLK:
		src_clk_id = OMAP4_SYS_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		OMAP_READREG(OMAP4430_CM_ABE_DSS_SYS_CLKSEL, reg_val);
		div = (double) (1 << extract_bit(reg_val, 0));
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed,
			div, out_clk_speed);
		return out_clk_speed;
	case OMAP4_DSS_ALWON_SYS_CLK:
		src_clk_id = OMAP4_ABE_DSS_SYS_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_ABE_SYSCLK:
		src_clk_id = OMAP4_ABE_DSS_SYS_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_DPLL_SYS_REF_CLK:
		if (cpu_is_omap4430() && (cpu_revision_get() == REV_ES1_0)) {
			src_clk_id = OMAP4_SYS_CLK;
			src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
				ignore_stop_status);
			OMAP_READREG(OMAP4430_CM_DPLL_SYS_REF_CLKSEL, reg_val);
			div = (double) (1 << extract_bit(reg_val, 0));
			out_clk_speed = src_clk_speed / div;
			DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed,
				div, out_clk_speed);
			return out_clk_speed;
		} else {
			src_clk_id = OMAP4_SYS_CLK;
			src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
				ignore_stop_status);
			out_clk_speed = src_clk_speed;
			DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
				out_clk_speed);
			return out_clk_speed;
		}
	case OMAP4_CORE_DPLL_ALWON_CLK:
		src_clk_id = OMAP4_DPLL_SYS_REF_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_PER_DPLL_ALWON_CLK:
		src_clk_id = OMAP4_DPLL_SYS_REF_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_IVA_DPLL_ALWON_CLK:
		src_clk_id = OMAP4_DPLL_SYS_REF_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_MPU_DPLL_ALWON_CLK:
		src_clk_id = OMAP4_DPLL_SYS_REF_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_L3INIT_DPLL_ALWON_CLK:
		src_clk_id = OMAP4_DPLL_SYS_REF_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_ABE_DPLL_ALWON_CLK:
		OMAP_READREG(OMAP4430_CM_ABE_PLL_REF_CLKSEL, reg_val);
		if (extract_bit(reg_val, 0) == 1)
			src_clk_id = OMAP4_FUNC_32K_CLK;
		else
			src_clk_id = OMAP4_DPLL_SYS_REF_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_GPT1_FCLK:
		OMAP_READREG(OMAP4430_CM_WKUP_TIMER1_CLKCTRL, reg_val);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = OMAP4_FUNC_32K_CLK;
		else
			src_clk_id = OMAP4_SYS_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_GPT2_FCLK:
		OMAP_READREG(OMAP4430_CM_L4PER_DMTIMER2_CLKCTRL, reg_val);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = OMAP4_FUNC_32K_CLK;
		else
			src_clk_id = OMAP4_SYS_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_GPT3_FCLK:
		OMAP_READREG(OMAP4430_CM_L4PER_DMTIMER3_CLKCTRL, reg_val);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = OMAP4_FUNC_32K_CLK;
		else
			src_clk_id = OMAP4_SYS_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_GPT4_FCLK:
		OMAP_READREG(OMAP4430_CM_L4PER_DMTIMER4_CLKCTRL, reg_val);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = OMAP4_FUNC_32K_CLK;
		else
			src_clk_id = OMAP4_SYS_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_GPT9_FCLK:
		OMAP_READREG(OMAP4430_CM_L4PER_DMTIMER9_CLKCTRL, reg_val);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = OMAP4_FUNC_32K_CLK;
		else
			src_clk_id = OMAP4_SYS_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_GPT10_FCLK:
		OMAP_READREG(OMAP4430_CM_L4PER_DMTIMER10_CLKCTRL, reg_val);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = OMAP4_FUNC_32K_CLK;
		else
			src_clk_id = OMAP4_SYS_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_GPT11_FCLK:
		OMAP_READREG(OMAP4430_CM_L4PER_DMTIMER11_CLKCTRL, reg_val);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = OMAP4_FUNC_32K_CLK;
		else
			src_clk_id = OMAP4_SYS_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_GPT12_FCLK:
		src_clk_id = OMAP4_SECURE_32K_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	/* DPLL CORE OUTPUTS */
	case OMAP4_PHY_ROOT_CLK:
		ret = dpll44xx_dpll_params_get(DPLL44XX_CORE,
			&dpll_params, ignore_stop_status);
		if (ret < 0)
			return ret;
		src_clk_speed = dpll_params.M2_speed;
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_CORE CLKOUT_M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	case OMAP4_CORE_DPLL_SCRM_CLK:
		ret = dpll44xx_dpll_params_get(DPLL44XX_CORE,
			&dpll_params, ignore_stop_status);
		if (ret < 0)
			return ret;
		src_clk_speed = dpll_params.X2_M3_speed;
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_CORE CLKOUT_X2M3",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	case OMAP4_DLL_X2_CLK:
		ret = dpll44xx_dpll_params_get(DPLL44XX_CORE,
			&dpll_params, ignore_stop_status);
		if (ret < 0)
			return ret;
		src_clk_speed = dpll_params.X2_M4_speed;
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_CORE CLKOUT_X2M4",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	case OMAP4_CORE_X2_CLK:
		ret = dpll44xx_dpll_params_get(DPLL44XX_CORE,
			&dpll_params, ignore_stop_status);
		if (ret < 0)
			return ret;
		src_clk_speed = dpll_params.X2_M5_speed;
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_CORE CLKOUT_X2M5",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	case OMAP4_CORE_DPLL_EMU_CLK:
		ret = dpll44xx_dpll_params_get(DPLL44XX_CORE,
			&dpll_params, ignore_stop_status);
		if (ret < 0)
			return ret;
		src_clk_speed = dpll_params.X2_M6_speed;
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_CORE CLKOUT_X2M6",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	case OMAP4_CORE_GFX_FCLK:
		ret = dpll44xx_dpll_params_get(DPLL44XX_CORE,
			&dpll_params, ignore_stop_status);
		if (ret < 0)
			return ret;
		src_clk_speed = dpll_params.X2_M7_speed;
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_CORE CLKOUT_X2M7",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	/* DPLL PER OUTPUTS */
	case OMAP4_96M_ALWON_FCLK:
		ret = dpll44xx_dpll_params_get(DPLL44XX_PER,
			&dpll_params, ignore_stop_status);
		if (ret < 0)
			return ret;
		src_clk_speed = dpll_params.M2_speed;
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_PER CLKOUT_M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	case OMAP4_192M_FCLK:
		ret = dpll44xx_dpll_params_get(DPLL44XX_PER,
			&dpll_params, ignore_stop_status);
		if (ret < 0)
			return ret;
		src_clk_speed = dpll_params.X2_M2_speed;
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_PER CLKOUT_X2M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	case OMAP4_PER_DPLL_SCRM_CLK:
		ret = dpll44xx_dpll_params_get(DPLL44XX_PER,
			&dpll_params, ignore_stop_status);
		if (ret < 0)
			return ret;
		src_clk_speed = dpll_params.X2_M3_speed;
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_PER CLKOUT_X2M3",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	case OMAP4_128M_FCLK:
		ret = dpll44xx_dpll_params_get(DPLL44XX_PER,
			&dpll_params, ignore_stop_status);
		if (ret < 0)
			return ret;
		src_clk_speed = dpll_params.X2_M4_speed;
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_PER CLKOUT_X2M4",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	case OMAP4_DSS_FCLK:
		ret = dpll44xx_dpll_params_get(DPLL44XX_PER,
			&dpll_params, ignore_stop_status);
		if (ret < 0)
			return ret;
		src_clk_speed = dpll_params.X2_M5_speed;
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_PER CLKOUT_X2M5",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	case OMAP4_PER_MPU_M3_CLK:
		ret = dpll44xx_dpll_params_get(DPLL44XX_PER,
			&dpll_params, ignore_stop_status);
		if (ret < 0)
			return ret;
		src_clk_speed = dpll_params.X2_M6_speed;
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_PER CLKOUT_X2M6",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	case OMAP4_PER_DPLL_EMU_CLK:
		ret = dpll44xx_dpll_params_get(DPLL44XX_PER,
			&dpll_params, ignore_stop_status);
		if (ret < 0)
			return ret;
		src_clk_speed = dpll_params.X2_M7_speed;
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_PER CLKOUT_X2M7",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	/* DPLL ABE OUTPUTS */
	case OMAP4_PER_ABE_X1_FCLK:
		ret = dpll44xx_dpll_params_get(DPLL44XX_ABE,
			&dpll_params, ignore_stop_status);
		if (ret < 0)
			return ret;
		src_clk_speed = dpll_params.M2_speed;
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_ABE CLKOUT_M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	case OMAP4_DPLL_ABE_X2_FCLK:
		ret = dpll44xx_dpll_params_get(DPLL44XX_ABE,
			&dpll_params, ignore_stop_status);
		if (ret < 0)
			return ret;
		src_clk_speed = dpll_params.X2_M2_speed;
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_ABE CLKOUT_X2M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	case OMAP4_CORE_DPLL_HS_CLK:
		ret = dpll44xx_dpll_params_get(DPLL44XX_ABE,
			&dpll_params, ignore_stop_status);
		if (ret < 0)
			return ret;
		src_clk_speed = dpll_params.X2_M3_speed;
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_ABE CLKOUT_X2M3",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	/* DPLL MPU OUTPUTS */
	case OMAP4_MPU_DPLL_CLK:
		ret = dpll44xx_dpll_params_get(DPLL44XX_MPU,
			&dpll_params, ignore_stop_status);
		if (ret < 0)
			return ret;
		if (dpll_params.dcc_en == 0) {
			src_clk_speed = dpll_params.M2_speed;
			out_clk_speed = src_clk_speed;
			DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_MPU CLKOUT_M2",
				src_clk_speed, out_clk_speed);
		} else {
			src_clk_speed = dpll_params.X2_M3_speed;
			out_clk_speed = src_clk_speed;
			DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_MPU CLKOUT_X2_M3",
				src_clk_speed, out_clk_speed);
		}
		return out_clk_speed;
	/* DPLL IVA OUTPUTS */
	case OMAP4_DSP_ROOT_CLK:
		ret = dpll44xx_dpll_params_get(DPLL44XX_IVA,
			&dpll_params, ignore_stop_status);
		if (ret < 0)
			return ret;
		src_clk_speed = dpll_params.X2_M4_speed;
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_IVA CLKOUT_X2M4",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	case OMAP4_IVAHD_ROOT_CLK:
		ret = dpll44xx_dpll_params_get(DPLL44XX_IVA,
			&dpll_params, ignore_stop_status);
		if (ret < 0)
			return ret;
		src_clk_speed = dpll_params.X2_M5_speed;
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_IVA CLKOUT_X2M5",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	/* DPLL USB OUTPUTS */
	case OMAP4_INIT_480M_FCLK:
		ret = dpll44xx_dpll_params_get(DPLL44XX_USB,
			&dpll_params, ignore_stop_status);
		if (ret < 0)
			return ret;
		src_clk_speed = dpll_params.M2_speed;
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_USB CLKOUT_M2",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	case OMAP4_INIT_960M_FCLK:
		ret = dpll44xx_dpll_params_get(DPLL44XX_USB,
			&dpll_params, ignore_stop_status);
		if (ret < 0)
			return ret;
		src_clk_speed = dpll_params.X2_M2_speed;
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_USB CLK_DCO_LDO",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;
	/* DPLL UNIPRO OUTPUTS */
	case OMAP4_UNIPRO1_PHY_FCLK:
		if (cpu_is_omap4430() && (cpu_revision_get() == REV_ES1_0)) {
			ret = dpll44xx_dpll_params_get(DPLL44XX_UNIPRO,
				&dpll_params, ignore_stop_status);
			if (ret < 0)
				return ret;
			src_clk_speed = dpll_params.X2_M2_speed;
			out_clk_speed = src_clk_speed;
			DPRINT_CLK_SPEED2_DPLL(clk_id,
				"DPLL_UNIPRO CLKOUT_X2M2",
				src_clk_speed, out_clk_speed);
			return out_clk_speed;
		} else {
			printf("omapconf internal error: UNIPRO module is not "
				"present in this chip revision!!!\n");
			return OMAPCONF_ERR_INTERNAL;
		}
	case OMAP4_DLL_CLK:
		src_clk_id = OMAP4_DLL_X2_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		div = 2.0;
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_CORE_CLK:
		src_clk_id = OMAP4_CORE_X2_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		OMAP_READREG(OMAP4430_CM_CLKSEL_CORE, reg_val);
		div = (double) (1 << extract_bit(reg_val, 0));
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_CORE_MPU_M3_CLK:
		src_clk_id = OMAP4_CORE_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_L3_ICLK:
	case OMAP4_C2C_L3X2_ICLK:
		src_clk_id = OMAP4_CORE_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		OMAP_READREG(OMAP4430_CM_CLKSEL_CORE, reg_val);
		div = (double) (1 << extract_bit(reg_val, 4));
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_L4_ROOT_CLK:
		src_clk_id = OMAP4_CORE_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		OMAP_READREG(OMAP4430_CM_CLKSEL_CORE, reg_val);
		div = (double) (1 << extract_bit(reg_val, 4));
		OMAP_READREG(OMAP4430_CM_CLKSEL_CORE, reg_val);
		div = div * ((double) (1 << extract_bit(reg_val, 8)));
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_L4_ICLK:
		src_clk_id = OMAP4_L4_ROOT_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_MPU_DPLL_HS_CLK:
		src_clk_id = OMAP4_CORE_X2_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		OMAP_READREG(OMAP4430_CM_BYPCLK_DPLL_MPU, reg_val);
		div = (double) (1 << extract_bitfield(reg_val, 0, 2));
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_IVA_DPLL_HS_CLK:
		src_clk_id = OMAP4_CORE_X2_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		OMAP_READREG(OMAP4430_CM_BYPCLK_DPLL_IVA, reg_val);
		div = (double) (1 << extract_bitfield(reg_val, 0, 2));
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_IVA_HSD_BYP_CLK:
		OMAP_READREG(OMAP4430_CM_CLKSEL_DPLL_IVA, reg_val);
		if (extract_bit(reg_val, 23) == 1)
			src_clk_id = OMAP4_IVA_DPLL_HS_CLK;
		else
			src_clk_id = OMAP4_IVA_DPLL_ALWON_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_CORE_PHY_HSD_BYP_CLK:
		OMAP_READREG(OMAP4430_CM_CLKSEL_DPLL_CORE, reg_val);
		if (extract_bit(reg_val, 23) == 1)
			src_clk_id = OMAP4_CORE_DPLL_HS_CLK;
		else
			src_clk_id = OMAP4_CORE_DPLL_ALWON_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_USB_DPLL_HS_CLK:
		src_clk_id = OMAP4_CORE_DPLL_HS_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		div = 2.0;
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_PER_DPLL_HS_CLK:
		src_clk_id = OMAP4_CORE_DPLL_HS_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		div = 2.0;
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_PER_HSD_BYP_CLK:
		OMAP_READREG(OMAP4430_CM_CLKSEL_DPLL_PER, reg_val);
		if (extract_bit(reg_val, 23) == 1)
			src_clk_id = OMAP4_PER_DPLL_HS_CLK;
		else
			src_clk_id = OMAP4_PER_DPLL_ALWON_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_24M_FCLK:
		src_clk_id = OMAP4_96M_ALWON_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		div = 4.0;
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_HSIC_P2_FCLK:
	case OMAP4_HSIC_P1_FCLK:
	case OMAP4_INIT_60M_P1_FCLK:
	case OMAP4_INIT_60M_P2_FCLK:
	case OMAP4_UTMI_ROOT_FCLK:
	case OMAP4_TLL_CH0_FCLK:
	case OMAP4_TLL_CH1_FCLK:
	case OMAP4_TLL_CH2_FCLK:
	case OMAP4_INIT_60M_FCLK:
		src_clk_id = OMAP4_INIT_480M_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		OMAP_READREG(OMAP4430_CM_CLKSEL_USB_60MHZ, reg_val);
		if (extract_bit(reg_val, 0) == 1)
			div = 8.0;
		else
			div = 1.0;
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_HSIC_P1_480M_FCLK:
	case OMAP4_HSIC_P2_480M_FCLK:
		src_clk_id = OMAP4_INIT_480M_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_UTMI_P1_FCLK:
		OMAP_READREG(OMAP4430_CM_L3INIT_USB_HOST_CLKCTRL, reg_val);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = OMAP4_XCLK_60M_HSP1;
		else
			src_clk_id = OMAP4_INIT_60M_P1_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_UTMI_P2_FCLK:
		OMAP_READREG(OMAP4430_CM_L3INIT_USB_HOST_CLKCTRL, reg_val);
		if (extract_bit(reg_val, 25) == 1)
			src_clk_id = OMAP4_XCLK_60M_HSP2;
		else
			src_clk_id = OMAP4_INIT_60M_P2_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_OTG_60M_FCLK:
		OMAP_READREG(OMAP4430_CM_L3INIT_USB_OTG_CLKCTRL, reg_val);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = OMAP4_XCLK_60M_OTG;
		else
			src_clk_id = OMAP4_PHY_CLKOUT;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_PHY_CLKOUT:
		out_clk_speed = (double) 60.0;
		DPRINT_CLK_SPEED1(clk_id, out_clk_speed);
		return out_clk_speed;
	case OMAP4_PAD_UCLKS:
		dprintf("clk44xx_get_clock_speed(): "
			"WARNING %s is external clock, "
			"cannot determine the frequency. Assuming 19.2MHz.\n",
			clk44xx_get_name(clk_id, clk_name));
		out_clk_speed = (double) 19.2;
		DPRINT_CLK_SPEED1(clk_id, out_clk_speed);
		return out_clk_speed;
	case OMAP4_SLIMBUS_UCLKS:
	case OMAP4_SLIMBUS_CORE_UCLKS:
		dprintf("clk44xx_get_clock_speed(): "
			"WARNING %s is external clock, "
			"cannot determine the frequency. Assuming 24.576MHz.\n",
			clk44xx_get_name(clk_id, clk_name));
		out_clk_speed = (double) 24.576;
		DPRINT_CLK_SPEED1(clk_id, out_clk_speed);
		return out_clk_speed;
	case OMAP4_PAD_CLKS:
		src_clk_id = OMAP4_PAD_UCLKS;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_SLIMBUS_CLKS:
		src_clk_id = OMAP4_SLIMBUS_UCLKS;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_ABE_CLK:
		src_clk_id = OMAP4_DPLL_ABE_X2_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		OMAP_READREG(OMAP4430_CM_CLKSEL_ABE, reg_val);
		div = (double) (1 << extract_bitfield(reg_val, 0, 2));
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_AESS_FCLK:
		src_clk_id = OMAP4_ABE_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		OMAP_READREG(OMAP4430_CM1_ABE_AESS_CLKCTRL, reg_val);
		div = (double) (1 << extract_bit(reg_val, 24));
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_ABE_ICLK2:
		src_clk_id = OMAP4_ABE_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		OMAP_READREG(OMAP4430_CM1_ABE_AESS_CLKCTRL, reg_val);
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
	case OMAP4_ABE_GPT5_FCLK:
		OMAP_READREG(OMAP4430_CM1_ABE_TIMER5_CLKCTRL, reg_val);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = OMAP4_ABE_ALWON_32K_CLK;
		else
			src_clk_id = OMAP4_ABE_SYSCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_ABE_GPT6_FCLK:
		OMAP_READREG(OMAP4430_CM1_ABE_TIMER6_CLKCTRL, reg_val);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = OMAP4_ABE_ALWON_32K_CLK;
		else
			src_clk_id = OMAP4_ABE_SYSCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_ABE_GPT7_FCLK:
		OMAP_READREG(OMAP4430_CM1_ABE_TIMER7_CLKCTRL, reg_val);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = OMAP4_ABE_ALWON_32K_CLK;
		else
			src_clk_id = OMAP4_ABE_SYSCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_ABE_GPT8_FCLK:
		OMAP_READREG(OMAP4430_CM1_ABE_TIMER8_CLKCTRL, reg_val);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = OMAP4_ABE_ALWON_32K_CLK;
		else
			src_clk_id = OMAP4_ABE_SYSCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_MCBSP1_INT_FCLK:
		OMAP_READREG(OMAP4430_CM1_ABE_MCBSP1_CLKCTRL, reg_val);
		switch (extract_bitfield(reg_val, 26, 2)) {
		case 0:
			src_clk_id = OMAP4_ABE_24M_FCLK;
			break;
		case 1:
			src_clk_id = OMAP4_ABE_SYSCLK;
			break;
		case 2:
			src_clk_id = OMAP4_24M_FCLK;
			break;
		default:
			return OMAPCONF_ERR_UNEXPECTED;
		}
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_MCBSP1_FCLK:
		OMAP_READREG(OMAP4430_CM1_ABE_MCBSP1_CLKCTRL, reg_val);
		switch (extract_bitfield(reg_val, 24, 2)) {
		case 0:
			src_clk_id = OMAP4_MCBSP1_INT_FCLK;
			break;
		case 1:
			src_clk_id = OMAP4_PAD_CLKS;
			break;
		case 2:
			src_clk_id = OMAP4_SLIMBUS_CLKS;
			break;
		default:
			return OMAPCONF_ERR_UNEXPECTED;
		}
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_MCBSP2_INT_FCLK:
		OMAP_READREG(OMAP4430_CM1_ABE_MCBSP2_CLKCTRL, reg_val);
		switch (extract_bitfield(reg_val, 26, 2)) {
		case 0:
			src_clk_id = OMAP4_ABE_24M_FCLK;
			break;
		case 1:
			src_clk_id = OMAP4_ABE_SYSCLK;
			break;
		case 2:
			src_clk_id = OMAP4_24M_FCLK;
			break;
		default:
			return OMAPCONF_ERR_UNEXPECTED;
		}
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_MCBSP2_FCLK:
		OMAP_READREG(OMAP4430_CM1_ABE_MCBSP2_CLKCTRL, reg_val);
		switch (extract_bitfield(reg_val, 24, 2)) {
		case 0:
			src_clk_id = OMAP4_MCBSP2_INT_FCLK;
			break;
		case 1:
			src_clk_id = OMAP4_PAD_CLKS;
			break;
		case 2:
			src_clk_id = OMAP4_SLIMBUS_CLKS;
			break;
		default:
			return OMAPCONF_ERR_UNEXPECTED;
		}
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_MCBSP3_INT_FCLK:
		OMAP_READREG(OMAP4430_CM1_ABE_MCBSP3_CLKCTRL, reg_val);
		switch (extract_bitfield(reg_val, 26, 2)) {
		case 0:
			src_clk_id = OMAP4_ABE_24M_FCLK;
			break;
		case 1:
			src_clk_id = OMAP4_ABE_SYSCLK;
			break;
		case 2:
			src_clk_id = OMAP4_24M_FCLK;
			break;
		default:
			return OMAPCONF_ERR_UNEXPECTED;
		}
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_MCBSP3_FCLK:
		OMAP_READREG(OMAP4430_CM1_ABE_MCBSP3_CLKCTRL, reg_val);
		switch (extract_bitfield(reg_val, 24, 2)) {
		case 0:
			src_clk_id = OMAP4_MCBSP3_INT_FCLK;
			break;
		case 1:
			src_clk_id = OMAP4_PAD_CLKS;
			break;
		case 2:
			src_clk_id = OMAP4_SLIMBUS_CLKS;
			break;
		default:
			return OMAPCONF_ERR_UNEXPECTED;
		}
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_MCASP1_INT_FCLK:
		OMAP_READREG(OMAP4430_CM1_ABE_MCASP_CLKCTRL, reg_val);
		switch (extract_bitfield(reg_val, 26, 2)) {
		case 0:
			src_clk_id = OMAP4_ABE_24M_FCLK;
			break;
		case 1:
			src_clk_id = OMAP4_ABE_SYSCLK;
			break;
		case 2:
			src_clk_id = OMAP4_24M_FCLK;
			break;
		default:
			return OMAPCONF_ERR_UNEXPECTED;
		}
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_MCASP1_FCLK:
		OMAP_READREG(OMAP4430_CM1_ABE_MCASP_CLKCTRL, reg_val);
		switch (extract_bitfield(reg_val, 24, 2)) {
		case 0:
			src_clk_id = OMAP4_MCASP1_INT_FCLK;
			break;
		case 1:
			src_clk_id = OMAP4_PAD_CLKS;
			break;
		case 2:
			src_clk_id = OMAP4_SLIMBUS_CLKS;
			break;
		default:
			return OMAPCONF_ERR_UNEXPECTED;
		}
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_DMIC_ABE_INT_FCLK:
		OMAP_READREG(OMAP4430_CM1_ABE_DMIC_CLKCTRL, reg_val);
		switch (extract_bitfield(reg_val, 26, 2)) {
		case 0:
			src_clk_id = OMAP4_ABE_24M_FCLK;
			break;
		case 1:
			src_clk_id = OMAP4_ABE_SYSCLK;
			break;
		case 2:
			src_clk_id = OMAP4_24M_FCLK;
			break;
		default:
			return OMAPCONF_ERR_UNEXPECTED;
		}
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_DMIC_ABE_FCLK:
		OMAP_READREG(OMAP4430_CM1_ABE_DMIC_CLKCTRL, reg_val);
		switch (extract_bitfield(reg_val, 24, 2)) {
		case 0:
			src_clk_id = OMAP4_DMIC_ABE_INT_FCLK;
			break;
		case 1:
			src_clk_id = OMAP4_PAD_CLKS;
			break;
		case 2:
			src_clk_id = OMAP4_SLIMBUS_CLKS;
			break;
		default:
			printf("clk44xx_get_clock_speed(): "
				"ERROR \'Reserved\' value read from "
				"OMAP4430_CM1_ABE_DMIC_CLKCTRL bitfield!!!\n");
			return OMAPCONF_ERR_UNEXPECTED;
		}
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_GFX_L3_ICLK:
	case OMAP4_INSTR_L3_ICLK:
	case OMAP4_DMA_L3_ICLK:
	case OMAP4_DSS_L3_ICLK:
	case OMAP4_EMIF_L3_ICLK:
	case OMAP4_INIT_L3_ICLK:
	case OMAP4_L3_ICLK1:
	case OMAP4_L3_ICLK2:
	case OMAP4_C2C_L3_ICLK:
		src_clk_id = OMAP4_L3_ICLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_CFG_L4_ICLK:
	case OMAP4_INSTR_L4_ICLK:
	case OMAP4_DMA_L4_ICLK:
	case OMAP4_DSS_L4_ICLK:
	case OMAP4_AO_L4_ICLK:
	case OMAP4_EMIF_L4_ICLK:
	case OMAP4_C2C_L4_ICLK:
	case OMAP4_INIT_L4_ICLK:
	case OMAP4_L4_ICLK2:
	case OMAP4_L4_ICLK1:
	case OMAP4_PER_L4_ICLK:
		src_clk_id = OMAP4_L4_ICLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case OMAP4_MPU_M3_ISS_CLK:
		if (!cpu_is_omap4470()) {
			OMAP_READREG(OMAP4430_CM_CLKSEL_MPU_M3_ISS_ROOT,
				reg_val);
			if (extract_bit(reg_val, 0) == 1)
				src_clk_id = OMAP4_PER_MPU_M3_CLK;
			else
				src_clk_id = OMAP4_CORE_MPU_M3_CLK;
			src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
				ignore_stop_status);
			out_clk_speed = src_clk_speed;
			DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
				out_clk_speed);
			return out_clk_speed;
		} else {
			src_clk_id = OMAP4_CORE_CLK;
			src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
				ignore_stop_status);
			out_clk_speed = src_clk_speed;
			DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
				out_clk_speed);
			return out_clk_speed;
		}
		break;

	case OMAP4_ISS_CLK:
	case OMAP4_MPU_M3_CLK:
		src_clk_id = OMAP4_MPU_M3_ISS_CLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case OMAP4_64M_FCLK:
		src_clk_id = OMAP4_128M_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		OMAP_READREG(OMAP4430_CM_SCALE_FCLK, reg_val);
		div = (double) (2 << extract_bit(reg_val, 0));
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_PER_ABE_NC_FCLK:
		src_clk_id = OMAP4_PER_ABE_X1_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		OMAP_READREG(OMAP4430_CM_SCALE_FCLK, reg_val);
		div = (double) (2 << extract_bit(reg_val, 0));
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_96M_FCLK:
		src_clk_id = OMAP4_192M_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		OMAP_READREG(OMAP4430_CM_SCALE_FCLK, reg_val);
		div = (double) (2 << extract_bit(reg_val, 0));
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_PER_96M_FCLK:
		src_clk_id = OMAP4_96M_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_48M_FCLK:
		src_clk_id = OMAP4_192M_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		OMAP_READREG(OMAP4430_CM_SCALE_FCLK, reg_val);
		div = (double) (4 << extract_bit(reg_val, 0));
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_FDIF_FCLK:
		src_clk_id = OMAP4_128M_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		OMAP_READREG(OMAP4430_CM_CAM_FDIF_CLKCTRL, reg_val);
		div = (double) (1 << extract_bitfield(reg_val, 24, 2));
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_PER_ABE_24M_FCLK:
		src_clk_id = OMAP4_PER_ABE_X1_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		div = 4.0;
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_PER_48M_FCLK:
		src_clk_id = OMAP4_48M_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_INIT_48M_FCLK:
		src_clk_id = OMAP4_48M_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_48MC_FCLK:
		src_clk_id = OMAP4_192M_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		div = 4.0;
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_24MC_FCLK:
		src_clk_id = OMAP4_192M_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		div = 8.0;
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_PER_24MC_FCLK:
		src_clk_id = OMAP4_24MC_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_12M_FCLK:
		src_clk_id = OMAP4_192M_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		div = 16.0;
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_HSI_FCLK:
		src_clk_id = OMAP4_192M_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		OMAP_READREG(OMAP4430_CM_L3INIT_HSI_CLKCTRL, reg_val);
		div = (double) (1 << extract_bitfield(reg_val, 24, 2));
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_INIT_HSI_FCLK:
		src_clk_id = OMAP4_HSI_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_PER_GFX_FCLK:
		if (cpu_is_omap4430() && (cpu_revision_get() == REV_ES1_0)) {
			src_clk_id = OMAP4_192M_FCLK;
			src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
				ignore_stop_status);
			OMAP_READREG(OMAP4430_CM_GFX_GFX_CLKCTRL, reg_val);
			div = (double) (1 << extract_bitfield(reg_val, 25, 2));
			out_clk_speed = src_clk_speed / div;
			DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed,
				div, out_clk_speed);
			return out_clk_speed;
		} else {
			ret = dpll44xx_dpll_params_get(DPLL44XX_PER,
				&dpll_params, ignore_stop_status);
			if (ret < 0)
				return ret;
			src_clk_speed = dpll_params.X2_M7_speed;
			out_clk_speed = src_clk_speed;
			DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_PER CLKOUT_X2M7",
				src_clk_speed, out_clk_speed);
			return out_clk_speed;
		}
		break;
	case OMAP4_HSMMC1_FCLK:
		OMAP_READREG(OMAP4430_CM_L3INIT_MMC1_CLKCTRL, reg_val);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = OMAP4_96M_FCLK;
		else
			src_clk_id = OMAP4_64M_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_MMC1_FCLK:
		src_clk_id = OMAP4_HSMMC1_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_HSMMC2_FCLK:
		OMAP_READREG(OMAP4430_CM_L3INIT_MMC2_CLKCTRL, reg_val);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = OMAP4_96M_FCLK;
		else
			src_clk_id = OMAP4_64M_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_MMC2_FCLK:
		src_clk_id = OMAP4_HSMMC2_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_PER_MCBSP4_INT_FCLK:
		OMAP_READREG(OMAP4430_CM_L4PER_MCBSP4_CLKCTRL, reg_val);
		if (extract_bit(reg_val, 25) == 1)
			src_clk_id = OMAP4_PER_ABE_NC_FCLK;
		else
			src_clk_id = OMAP4_96M_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_PER_MCBSP4_FCLK:
		OMAP_READREG(OMAP4430_CM_L4PER_MCBSP4_CLKCTRL, reg_val);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = OMAP4_PAD_UCLKS;
		else
			src_clk_id = OMAP4_PER_MCBSP4_INT_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_HDMI_PHY_48M_FCLK:
	case OMAP4_INIT_48MC_FCLK:
		src_clk_id = OMAP4_48MC_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case OMAP4_GFX_FCLK:
		if (!cpu_is_omap4470()) {
			OMAP_READREG(OMAP4430_CM_GFX_GFX_CLKCTRL, reg_val);
			if (extract_bit(reg_val, 24) == 1)
				src_clk_id = OMAP4_PER_GFX_FCLK;
			else
				src_clk_id = OMAP4_CORE_GFX_FCLK;
			src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
				ignore_stop_status);
			out_clk_speed = src_clk_speed;
			DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
				out_clk_speed);
			return out_clk_speed;
		} else {
			ret = dpll44xx_dpll_params_get(DPLL44XX_PER,
				&dpll_params, ignore_stop_status);
			if (ret < 0)
				return ret;
			src_clk_speed = dpll_params.X2_M7_speed;
			out_clk_speed = src_clk_speed;
			DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_PER CLKOUT_X2M7",
				src_clk_speed, out_clk_speed);
			return out_clk_speed;
		}

	case OMAP4_USIM_FCLK:
		src_clk_id = OMAP4_128M_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		OMAP_READREG(OMAP4430_CM_WKUP_USIM_CLKCTRL, reg_val);
		if (extract_bit(reg_val, 24) == 1)
			div = 18.0;
		else
			div = 14.0;
		out_clk_speed = src_clk_speed / div;
		DPRINT_CLK_SPEED3(clk_id, src_clk_id, src_clk_speed, div,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_L3_SECURE_GICLK:
		src_clk_id = OMAP4_L3_ICLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_L4_SECURE_GICLK:
		src_clk_id = OMAP4_L4_ICLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;
	case OMAP4_L3_INSTR_GICLK:
		src_clk_id = OMAP4_L3_ICLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	case OMAP4_CORE_BB2D_FCLK:
		ret = dpll44xx_dpll_params_get(DPLL44XX_CORE,
			&dpll_params, ignore_stop_status);
		if (ret < 0)
			return ret;
		src_clk_speed = dpll_params.X2_M7_speed;
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_CORE CLKOUT_X2M7",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case OMAP4_PER_BB2D_FCLK:
		ret = dpll44xx_dpll_params_get(DPLL44XX_PER,
			&dpll_params, ignore_stop_status);
		if (ret < 0)
			return ret;
		src_clk_speed = dpll_params.X2_M6_speed;
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2_DPLL(clk_id, "DPLL_PER CLKOUT_X2M6",
			src_clk_speed, out_clk_speed);
		return out_clk_speed;

	case OMAP4_BB2D_FCLK:
		OMAP_READREG(OMAP4430_CM_DSS_BB2D_CLKCTRL, reg_val);
		if (extract_bit(reg_val, 24) == 1)
			src_clk_id = OMAP4_PER_BB2D_FCLK;
		else
			src_clk_id = OMAP4_CORE_BB2D_FCLK;
		src_clk_speed = clk44xx_get_clock_speed(src_clk_id,
			ignore_stop_status);
		out_clk_speed = src_clk_speed;
		DPRINT_CLK_SPEED2(clk_id, src_clk_id, src_clk_speed,
			out_clk_speed);
		return out_clk_speed;

	default:
		return (double) OMAPCONF_ERR_ARG;
	}
}
