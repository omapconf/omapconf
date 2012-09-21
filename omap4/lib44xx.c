/*
 *
 * @Component			OMAPCONF
 * @Filename			lib44xx.c
 * @Description			OMAPCONF OMAP4 General Purpose Library
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


#include <lib44xx.h>
#include <mem.h>
#include <cm44xx.h>
#include <prm44xx.h>
#include <lib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dpll44xx.h>
#include <smartreflex44xx.h>
#include <module44xx.h>
#include <cpuinfo.h>
#include <autoadjust_table.h>
#include <mpu44xx.h>
#include <mpuss44xx.h>
#include <wkdep44xx.h>
#include <core44xx.h>
#include <per44xx.h>
#include <dsp44xx.h>
#include <dss44xx.h>
#include <cam44xx.h>
#include <camera44xx.h>
#include <gfx44xx.h>
#include <ivahd44xx.h>
#include <abe44xx.h>
#include <wkup44xx.h>
#include <wkdep44xx.h>
#include <l3init44xx.h>
#include <alwon44xx.h>
#include <emu44xx.h>
#include <display44xx.h>
#include <abb44xx.h>


/* #define LIB44XX_FIND_REG_ADDR_DEBUG */
/* #define LIB44XX_DEBUG */
#ifdef LIB44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		reg44xx_addr_find
 * @BRIEF		find reg. addr corresponding to reg. name given as
 *			argument
 * @RETURNS		0 on success
 *			-1 if reg. addr. not found
 * @param[in]		name: reg. name.
 * @param[in,out]	addr: reg. addr corresponding to reg. name
 * @DESCRIPTION		find reg. addr corresponding to reg. name given as
 *			argument
 *//*------------------------------------------------------------------------ */
int reg44xx_addr_find(char *name, unsigned int* addr)
{
	#ifdef LIB44XX_FIND_REG_ADDR_DEBUG
	printf("%s(): looking for addr of register %s...\n", __func__, name);
	#endif

	if (mpu44xx_name2addr(name, addr) == 0)
		goto reg_addr_found;
	if (mpuss44xx_name2addr(name, addr) == 0)
		goto reg_addr_found;
	if (dpll44xx_name2addr(name, addr) == 0)
		goto reg_addr_found;
	if (wkdep44xx_name2addr(name, addr) == 0)
		goto reg_addr_found;
	if (core44xx_name2addr(name, addr) == 0)
		goto reg_addr_found;
	if (dsp44xx_name2addr(name, addr) == 0)
		goto reg_addr_found;
	if (dss44xx_name2addr(name, addr) == 0)
		goto reg_addr_found;
	if (cam44xx_name2addr(name, addr) == 0)
		goto reg_addr_found;
	if (camera44xx_name2addr(name, addr) == 0)
		goto reg_addr_found;
	if (gfx44xx_name2addr(name, addr) == 0)
		goto reg_addr_found;
	if (ivahd44xx_name2addr(name, addr) == 0)
		goto reg_addr_found;
	if (per44xx_name2addr(name, addr) == 0)
		goto reg_addr_found;
	if (abe44xx_name2addr(name, addr) == 0)
		goto reg_addr_found;
	if (wkup44xx_name2addr(name, addr) == 0)
		goto reg_addr_found;
	if (l3init44xx_name2addr(name, addr) == 0)
		goto reg_addr_found;
	if (alwon44xx_name2addr(name, addr) == 0)
		goto reg_addr_found;
	if (emu44xx_name2addr(name, addr) == 0)
		goto reg_addr_found;
	if (sr44xx_name2addr(name, addr) == 0)
		goto reg_addr_found;
	if (abb44xx_name2addr(name, addr) == 0)
		goto reg_addr_found;
	if (display44xx_name2addr(name, addr) == 0)
		goto reg_addr_found;
	#ifdef LIB44XX_FIND_REG_ADDR_DEBUG
	printf("%s(): register addr not found!\n", __func__);
	#endif
	return -1;

reg_addr_found:
	#ifdef LIB44XX_FIND_REG_ADDR_DEBUG
	printf("%s(): register addr found: 0x%x\n", __func__, *addr);
	#endif

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu44xx_power_state_get
 * @BRIEF		extract current CPU[0-1] power state from register
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in]		cpu: CPU core number (0, 1)
 * @param[in, out]	state: current CPU[0-1] power state (returned)
 * @DESCRIPTION		extract current CPU[0-1] power state from register
 *//*------------------------------------------------------------------------ */
int cpu44xx_power_state_get(unsigned int cpu,
	pwrdm_state *state)
{
	unsigned int pm_pda_cpu_pwrstst_addr, pm_pda_cpu_pwrstst;

	if (state == NULL)
		return OMAPCONF_ERR_ARG;
	*state = PWRDM_STATE_MAX;


	/* Retrieve registers address */
	switch (cpu) {
	case 0:
		pm_pda_cpu_pwrstst_addr = OMAP4430_PM_PDA_CPU0_PWRSTST;
		break;
	case 1:
		pm_pda_cpu_pwrstst_addr = OMAP4430_PM_PDA_CPU1_PWRSTST;
		break;
	default:
		dprintf("%s(): called with incorrect CPU # (%d)\n",
			__func__, cpu);
		return OMAPCONF_ERR_ARG;
	}

	/* Retrieve register content */
	mem_read(pm_pda_cpu_pwrstst_addr, &pm_pda_cpu_pwrstst);

	dprintf("%s(): CPU is %d pm_pda_cpu_pwrstst_addr = 0x%08X "
		"pm_pda_cpu_pwrstst = 0x%08X\n", __func__,
		cpu, pm_pda_cpu_pwrstst_addr, pm_pda_cpu_pwrstst);

	/* Retrieve power state */
	*state = (pwrdm_state) extract_bitfield(pm_pda_cpu_pwrstst, 0, 2);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm44xx_config_show
 * @BRIEF		analyze power domain configuration
 * @RETURNS		0 in case of error
 * @param[in,out]	stream: output file
 * @param[in,out]	name: domain name
 * @param[in]		pm_pwstctrl_addr: PM_xyz_PWSTCTRL register address
 * @param[in]		pm_pwstctrl: PM_xyz_PWSTCTRL register content
 * @param[in]		pm_pwstst_addr: PM_xyz_PWSTST register address
 * @param[in]		pm_pwstst: PM_xyz_PWSTST register content
 * @DESCRIPTION		analyze power domain configuration
 *//*------------------------------------------------------------------------ */
int pwrdm44xx_config_show(FILE *stream, const char name[11],
	unsigned int pm_pwstctrl_addr, unsigned int pm_pwstctrl,
	unsigned int pm_pwstst_addr, unsigned int pm_pwstst)
{
	char curr[32], tgt[32], last[32];

	dprintf("%s(): name=%s\n", __func__, name);
	dprintf("%s(): pm_pwstctrl addr=0x%08X\n", __func__, pm_pwstctrl_addr);
	dprintf("%s(): pm_pwstctrl=0x%08X\n", __func__, pm_pwstctrl);
	dprintf("%s(): pm_pwstst addr=0x%08X\n", __func__, pm_pwstst_addr);
	dprintf("%s(): pm_pwstst=0x%08X\n", __func__, pm_pwstst);
	dprintf("\n");

	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "| %-10s Power Domain Configuration                  "
		"      |\n", name);
	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "| %-30s | %-7s | %-7s | %-7s |\n", "Power State",
		"Current", "Target", "Last");
	fprintf(stream, "|--------------------------------|---------|--------"
		"-|---------|\n");
	pwrdm_state2string(curr,
		(pwrdm_state) extract_bitfield(pm_pwstst, 0, 2));
	pwrdm_state2string(tgt,
		(pwrdm_state) extract_bitfield(pm_pwstctrl, 0, 2));
	if ((cpu_is_omap4430() && (cpu_revision_get() != REV_ES1_0)) ||
		cpu_is_omap4460() || cpu_is_omap4470()) {
		switch (pm_pwstst_addr) {
		case OMAP4430_PM_MPU_PWRSTST:
		case OMAP4430_PM_DSP_PWRSTST:
		case OMAP4430_PM_ABE_PWRSTST:
		case OMAP4430_PM_CORE_PWRSTST:
		case OMAP4430_PM_IVAHD_PWRSTST:
		case OMAP4430_PM_L3INIT_PWRSTST:
		case OMAP4430_PM_L4PER_PWRSTST:
			pwrdm_state2string(last, (pwrdm_state)
				extract_bitfield(pm_pwstst, 24, 2));
			break;
		case OMAP4430_PM_CAM_PWRSTST:
		case OMAP4430_PM_DSS_PWRSTST:
		case OMAP4430_PM_GFX_PWRSTST:
		case OMAP4430_PM_EMU_PWRSTST:
			if (!cpu_is_omap4430())
				pwrdm_state2string(last, (pwrdm_state)
					extract_bitfield(pm_pwstst, 24, 2));
			else
				strcpy(last, "");
			break;
		default:
			strcpy(last, "");
		}
	} else {
		strcpy(last, "");
	}
	fprintf(stream, "| %-30s | %-7s | %-7s | %-7s |\n",
		"Domain", curr, tgt, last);

	if ((pm_pwstctrl_addr == OMAP4430_PM_CAM_PWRSTCTRL) ||
			(pm_pwstctrl_addr == OMAP4430_PM_EMU_PWRSTCTRL) ||
			(pm_pwstctrl_addr == OMAP4430_PM_GFX_PWRSTCTRL)) {
		fprintf(stream, "| %-30s | %-7s | %-7s |         |\n", "Logic",
			((extract_bit(pm_pwstst, 2) == 1) ? "ON" : "OFF"),
			"");
	} else {
		fprintf(stream, "| %-30s | %-7s | %-7s |         |\n", "Logic",
			((extract_bit(pm_pwstst, 2) == 1) ? "ON" : "OFF"),
			((extract_bit(pm_pwstctrl, 2) == 1) ? "RET" : "OFF"));
	}
	fprintf(stream, "| %-30s | %-7s | %-7s |         |\n",
		"Memory", "", "");
	switch (pm_pwstctrl_addr) {
	case OMAP4430_PM_CORE_PWRSTCTRL:
		pwrdm_state2string(curr, (pwrdm_state)
			extract_bitfield(pm_pwstst, 12, 2));
		pwrdm_state2string(tgt, (pwrdm_state)
			extract_bit(pm_pwstctrl, 12));
		fprintf(stream, "| %-30s | %-7s | %-7s |         |\n",
			"    OCP_WP Bank & DMM Bank2", curr, tgt);
		break;
	default:
		break;
	}

	switch (pm_pwstctrl_addr) {
	case OMAP4430_PM_IVAHD_PWRSTCTRL:
		pwrdm_state2string(curr, (pwrdm_state)
			extract_bitfield(pm_pwstst, 10, 2));
		pwrdm_state2string(tgt, (pwrdm_state)
			extract_bit(pm_pwstctrl, 11));
		fprintf(stream, "| %-30s | %-7s | %-7s |         |\n",
			"    TCM2", curr, tgt);
		break;
	case OMAP4430_PM_CORE_PWRSTCTRL:
		pwrdm_state2string(curr, (pwrdm_state)
			extract_bitfield(pm_pwstst, 10, 2));
		pwrdm_state2string(tgt, (pwrdm_state)
			extract_bit(pm_pwstctrl, 11));
		fprintf(stream, "| %-30s | %-7s | %-7s |         |\n",
			"    MPU_M3 Unicache", curr, tgt);
	default:
		break;
	}

	switch (pm_pwstctrl_addr) {
	case OMAP4430_PM_MPU_PWRSTCTRL:
		pwrdm_state2string(curr, (pwrdm_state)
			extract_bitfield(pm_pwstst, 8, 2));
		pwrdm_state2string(tgt, (pwrdm_state)
			extract_bit(pm_pwstctrl, 10));
		fprintf(stream, "| %-30s | %-7s | %-7s |         |\n",
			"    RAM", curr, tgt);
		break;
	case OMAP4430_PM_DSP_PWRSTCTRL:
		pwrdm_state2string(curr, (pwrdm_state)
			extract_bitfield(pm_pwstst, 8, 2));
		pwrdm_state2string(tgt, (pwrdm_state)
			extract_bit(pm_pwstctrl, 10));
		fprintf(stream, "| %-30s | %-7s | %-7s |         |\n",
			"    EDMA", curr, tgt);
		break;
	case OMAP4430_PM_DSS_PWRSTCTRL:
	case OMAP4430_PM_CAM_PWRSTCTRL:
	case OMAP4430_PM_GFX_PWRSTCTRL:
		pwrdm_state2string(curr, (pwrdm_state)
			extract_bitfield(pm_pwstst, 4, 2));
		pwrdm_state2string(tgt, (pwrdm_state)
			extract_bit(pm_pwstctrl, 8));
		fprintf(stream, "| %-30s | %-7s | %-7s |         |\n",
			"    MEM", curr, tgt);
		break;
	case OMAP4430_PM_IVAHD_PWRSTCTRL:
		pwrdm_state2string(curr, (pwrdm_state)
			extract_bitfield(pm_pwstst, 8, 2));
		pwrdm_state2string(tgt, (pwrdm_state)
			extract_bit(pm_pwstctrl, 10));
		fprintf(stream, "| %-30s | %-7s | %-7s |         |\n",
			"    TCM1", curr, tgt);
	case OMAP4430_PM_CORE_PWRSTCTRL:
		pwrdm_state2string(curr, (pwrdm_state)
			extract_bitfield(pm_pwstst, 8, 2));
		pwrdm_state2string(tgt, (pwrdm_state)
			extract_bit(pm_pwstctrl, 10));
		fprintf(stream, "| %-30s | %-7s | %-7s |         |\n",
			"    MPU_M3 L2 RAM", curr, tgt);
	default:
		break;
	}

	switch (pm_pwstctrl_addr) {
	case OMAP4430_PM_ABE_PWRSTCTRL:
		pwrdm_state2string(curr, (pwrdm_state)
			extract_bitfield(pm_pwstst, 8, 2));
		pwrdm_state2string(tgt, (pwrdm_state)
			extract_bit(pm_pwstctrl, 10));
		fprintf(stream, "| %-30s | %-7s | %-7s |         |\n",
			"    PERIPHMEM", curr, tgt);
		pwrdm_state2string(curr, (pwrdm_state)
			extract_bitfield(pm_pwstst, 4, 2));
		pwrdm_state2string(tgt, (pwrdm_state)
			extract_bit(pm_pwstctrl, 8));
		fprintf(stream, "| %-30s | %-7s | %-7s |         |\n",
			"    AESSMEM", curr, tgt);
		break;
	case OMAP4430_PM_MPU_PWRSTCTRL:
		pwrdm_state2string(curr, (pwrdm_state)
			extract_bitfield(pm_pwstst, 6, 2));
		pwrdm_state2string(tgt, (pwrdm_state)
			extract_bit(pm_pwstctrl, 9));
		fprintf(stream, "| %-30s | %-7s | %-7s |         |\n",
			"    L2$", curr, tgt);
		if (cpu_is_omap4430())
			pwrdm_state2string(curr,
				extract_bitfield(pm_pwstst, 4, 2));
		else
			strcpy(curr, ""); /* not available on OMAP44[60-70] */
		pwrdm_state2string(tgt,
			extract_bit(pm_pwstctrl, 8));
		fprintf(stream, "| %-30s | %-7s | %-7s |         |\n",
			"    L1$", curr, tgt);
		break;
	case OMAP4430_PM_DSP_PWRSTCTRL:
		pwrdm_state2string(curr, (pwrdm_state)
			extract_bitfield(pm_pwstst, 6, 2));
		pwrdm_state2string(tgt, (pwrdm_state)
			extract_bit(pm_pwstctrl, 9));
		fprintf(stream, "| %-30s | %-7s | %-7s |         |\n",
			"    L2$", curr, tgt);
		pwrdm_state2string(curr,
			extract_bitfield(pm_pwstst, 4, 2));
		pwrdm_state2string(tgt,
			extract_bit(pm_pwstctrl, 8));
		fprintf(stream, "| %-30s | %-7s | %-7s |         |\n",
			"    L1$", curr, tgt);
		break;
	case OMAP4430_PM_IVAHD_PWRSTCTRL:
		pwrdm_state2string(curr, (pwrdm_state)
			extract_bitfield(pm_pwstst, 6, 2));
		pwrdm_state2string(tgt, (pwrdm_state)
			extract_bit(pm_pwstctrl, 9));
		fprintf(stream, "| %-30s | %-7s | %-7s |         |\n",
			"    SL2", curr, tgt);
		pwrdm_state2string(curr, (pwrdm_state)
			extract_bitfield(pm_pwstst, 4, 2));
		pwrdm_state2string(tgt, (pwrdm_state)
			extract_bit(pm_pwstctrl, 8));
		fprintf(stream, "| %-30s | %-7s | %-7s |         |\n",
			"    HWA", curr, tgt);
		break;
	case OMAP4430_PM_L4PER_PWRSTCTRL:
		pwrdm_state2string(curr, (pwrdm_state)
			extract_bitfield(pm_pwstst, 6, 2));
		pwrdm_state2string(tgt, (pwrdm_state)
			extract_bit(pm_pwstctrl, 9));
		fprintf(stream, "| %-30s | %-7s | %-7s |         |\n",
			"    NONRETAINED", curr, tgt);
		pwrdm_state2string(curr, (pwrdm_state)
			extract_bitfield(pm_pwstst, 4, 2));
		pwrdm_state2string(tgt, (pwrdm_state)
			extract_bit(pm_pwstctrl, 8));
		fprintf(stream, "| %-30s | %-7s | %-7s |         |\n",
			"    RETAINED", curr, tgt);
		break;
	case OMAP4430_PM_CORE_PWRSTCTRL:
		pwrdm_state2string(curr, (pwrdm_state)
			extract_bitfield(pm_pwstst, 6, 2));
		pwrdm_state2string(tgt, (pwrdm_state)
			extract_bit(pm_pwstctrl, 9));
		fprintf(stream, "| %-30s | %-7s | %-7s |         |\n",
			"    OCM RAM", curr, tgt);
		pwrdm_state2string(curr, (pwrdm_state)
			extract_bitfield(pm_pwstst, 4, 2));
		pwrdm_state2string(tgt, (pwrdm_state)
			extract_bit(pm_pwstctrl, 8));
		fprintf(stream, "| %-30s | %-7s | %-7s |         |\n",
			"    DMA/ICR Bank & DMM Bank1", curr, tgt);
		break;
	case OMAP4430_PM_L3INIT_PWRSTCTRL:
		pwrdm_state2string(curr, (pwrdm_state)
			extract_bitfield(pm_pwstst, 4, 2));
		pwrdm_state2string(tgt, (pwrdm_state)
			extract_bit(pm_pwstctrl, 8));
		fprintf(stream, "| %-30s | %-7s | %-7s |         |\n",
			"    L3INIT Bank1", curr, tgt);
		break;
	case OMAP4430_PM_EMU_PWRSTCTRL:
		pwrdm_state2string(curr, (pwrdm_state)
			extract_bitfield(pm_pwstst, 4, 2));
		pwrdm_state2string(tgt, (pwrdm_state)
			extract_bitfield(pm_pwstctrl, 16, 2));
		fprintf(stream, "| %-30s | %-7s | %-7s |         |\n",
			"    EMU Bank", curr, tgt);
		break;
	default:
		break;
	}
	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "| %-30s | %-27s |\n", "Ongoing Power Transition?",
		((extract_bit(pm_pwstst, 20) == 1) ? "YES" : "NO"));
	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm44xx_config_show
 * @BRIEF		analyze clock domain configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output file
 * @param[in,out]	name: domain name
 * @param[in]		cm_clkstctrl_addr: CM_xyz_CLKSTCTRL register address
 * @param[in]		cm_clkstctrl: CM_xyz_CLKSTCTRL register content
 * @DESCRIPTION		analyze clock domain configuration
 *//*------------------------------------------------------------------------ */
int clkdm44xx_config_show(FILE *stream, const char name[11],
	unsigned int cm_clkstctrl_addr,	unsigned int cm_clkstctrl)
{
	unsigned int cm_clksel_abe;

	dprintf("clkdm44xx_config_show(): "
		"name=%s\n", name);
	dprintf("clkdm44xx_config_show(): "
		"cm_clkstctrl_addr=0x%08X\n", cm_clkstctrl_addr);
	dprintf("clkdm44xx_config_show(): "
		"cm_clkstctrl=0x%08X\n", cm_clkstctrl);
	dprintf("\n");


	if (!cpu_is_omap44xx()) {
		fprintf(stderr, "%s(): cpu is not OMAP44xx!!!\n", __func__);
		return OMAPCONF_ERR_CPU;
	}

	if (cm_clkstctrl_addr == OMAP4430_CM1_ABE_CLKSTCTRL) {
		if (mem_read(OMAP4430_CM_CLKSEL_ABE, &cm_clksel_abe) != 0)
			return OMAPCONF_ERR_REG_ACCESS;
	}

	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "| %-10s Clock Domain Configuration                  "
		"      |\n", name);
	fprintf(stream, "|--------------------------------|------------------"
		"-----------|\n");
	fprintf(stream, "| %-30s | %-27s |\n",
		"Clock State Transition control",
		clkdm_ctrl_mode_name_get((clkdm_ctrl_mode)
			extract_bitfield(cm_clkstctrl, 0, 2)));

	switch (cm_clkstctrl_addr) {
	case OMAP4430_CM_WKUP_CLKSTCTRL:
		fprintf(stream, "| %-30s | %-27s |\n", "Clock State", "");
		if (!cpu_is_omap4430())
			fprintf(stream, "| %-30s | %-27s |\n", "  WKUP_TS_FCLK",
				((extract_bit(cm_clkstctrl, 13) == 1) ?
					"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  L4_WKUP_GICLK",
			((extract_bit(cm_clkstctrl, 12) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  WKUP_32K_GFCLK",
			((extract_bit(cm_clkstctrl, 11) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  USIM_GFCLK",
			((extract_bit(cm_clkstctrl, 10) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  ABE_LP_CLK",
			((extract_bit(cm_clkstctrl, 9) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  SYS_CLK",
			((extract_bit(cm_clkstctrl, 8) == 1) ?
				"RUNNING" : "GATED"));
		break;
	case OMAP4430_CM1_ABE_CLKSTCTRL:
		fprintf(stream, "| %-30s | %-27s |\n", "Clock State", "");
		fprintf(stream, "| %-30s | %-27s |\n", "  ABE_24M_FCLK",
			((extract_bit(cm_clkstctrl, 13) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  ABE_ALWON_32K_CLK",
			((extract_bit(cm_clkstctrl, 12) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  ABE_SYSCLK",
			((extract_bit(cm_clkstctrl, 11) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  24M_FCLK",
			((extract_bit(cm_clkstctrl, 10) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  ABE_ICLK2",
			((extract_bit(cm_clkstctrl, 9) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  DPLL_ABE_X2_CLK",
			((extract_bit(cm_clkstctrl, 8) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  PAD_CLKS",
			((extract_bit(cm_clksel_abe, 8) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  SLIMBUS_CLK",
			((extract_bit(cm_clksel_abe, 10) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | ABE_CLK = DPLL_ABE_X2_CLK/%-1d |\n",
			"OPP Divider",
			1 << extract_bitfield(cm_clksel_abe, 0, 2));
		break;
	case OMAP4430_CM_L4PER_CLKSTCTRL:
		fprintf(stream, "| %-30s | %-27s |\n", "Clock State", "");
		fprintf(stream, "| %-30s | %-27s |\n", "  PER_ABE_24M_FCLK",
			((extract_bit(cm_clkstctrl, 25) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  PER_SYS_FCLK",
			((extract_bit(cm_clkstctrl, 24) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  PER_MCBSP4_FCLK",
			((extract_bit(cm_clkstctrl, 22) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  PER_96M_FCLK",
			((extract_bit(cm_clkstctrl, 19) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  PER_48M_FCLK",
			((extract_bit(cm_clkstctrl, 18) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  PER_32K_FCLK",
			((extract_bit(cm_clkstctrl, 17) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  PER_24MC_FCLK",
			((extract_bit(cm_clkstctrl, 16) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  FUNC_12M_FCLK",
			((extract_bit(cm_clkstctrl, 15) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  DMT9_FCLK",
			((extract_bit(cm_clkstctrl, 14) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  DMT4_FCLK",
			((extract_bit(cm_clkstctrl, 13) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  DMT3_FCLK",
			((extract_bit(cm_clkstctrl, 12) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  DMT2_FCLK",
			((extract_bit(cm_clkstctrl, 11) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  DMT11_FCLK",
			((extract_bit(cm_clkstctrl, 10) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  DMT10_FCLK",
			((extract_bit(cm_clkstctrl, 9) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  L4_PER_GICLK",
			((extract_bit(cm_clkstctrl, 8) == 1) ?
				"RUNNING" : "GATED"));
		break;
	case OMAP4430_CM_DSS_CLKSTCTRL:
		fprintf(stream, "| %-30s | %-27s |\n", "Clock State", "");
		if (cpu_is_omap4470())
			fprintf(stream, "| %-30s | %-27s |\n", "  BB2D FCLK",
				((extract_bit(cm_clkstctrl, 12) == 1) ?
					"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  HDMI PHY 48MHz FCLK",
			((extract_bit(cm_clkstctrl, 11) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  DSS ALWON SYSCLK",
			((extract_bit(cm_clkstctrl, 10) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  DSS_FCLK",
			((extract_bit(cm_clkstctrl, 9) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  DSS_L3_ICLK",
			((extract_bit(cm_clkstctrl, 8) == 1) ?
				"RUNNING" : "GATED"));
		break;
	case OMAP4430_CM_CAM_CLKSTCTRL:
		fprintf(stream, "| %-30s | %-27s |\n", "Clock State", "");
		fprintf(stream, "| %-30s | %-27s |\n", "  FDIF FCLK",
			((extract_bit(cm_clkstctrl, 10) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  CAM PHY CTRL CLK",
			((extract_bit(cm_clkstctrl, 9) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  ISS_ICLK",
			((extract_bit(cm_clkstctrl, 8) == 1) ?
				"RUNNING" : "GATED"));
		break;
	case OMAP4430_CM_GFX_CLKSTCTRL:
		fprintf(stream, "| %-30s | %-27s |\n", "Clock State", "");
		fprintf(stream, "| %-30s | %-27s |\n", "  GFX_FCLK",
			((extract_bit(cm_clkstctrl, 9) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  GFX_L3_ICLK",
			((extract_bit(cm_clkstctrl, 8) == 1) ?
				"RUNNING" : "GATED"));
		break;
	case OMAP4430_CM_MEMIF_CLKSTCTRL:
		fprintf(stream, "| %-30s | %-27s |\n", "Clock State", "");
		fprintf(stream, "| %-30s | %-27s |\n", "  PHY_ROOT_CLK",
			((extract_bit(cm_clkstctrl, 10) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  DLL_CLK",
			((extract_bit(cm_clkstctrl, 9) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  L3_EMIF_ICLK",
			((extract_bit(cm_clkstctrl, 8) == 1) ?
				"RUNNING" : "GATED"));
		break;
	case OMAP4430_CM_C2C_CLKSTCTRL:
		fprintf(stream, "| %-30s | %-27s |\n", "Clock State", "");
		if ((cpu_is_omap4430() && (cpu_revision_get() != REV_ES1_0))
			|| cpu_is_omap4460() || cpu_is_omap4470())
			fprintf(stream, "| %-30s | %-27s |\n",
				"  C2C_L3X2_ICLK",
				((extract_bit(cm_clkstctrl, 10) == 1) ?
					"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  L4_C2C_ICLK",
			((extract_bit(cm_clkstctrl, 9) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  L3_C2C_ICLK",
			((extract_bit(cm_clkstctrl, 8) == 1) ?
				"RUNNING" : "GATED"));
		break;
	case OMAP4430_CM_L3INIT_CLKSTCTRL:
		fprintf(stream, "| %-30s | %-27s |\n", "Clock State", "");
		fprintf(stream, "| %-30s | %-27s |\n", "  INIT_32K_FCLK",
			((extract_bit(cm_clkstctrl, 31) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  INIT_60M_P2_FCLK",
			((extract_bit(cm_clkstctrl, 29) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  INIT_60M_P1_FCLK",
			((extract_bit(cm_clkstctrl, 28) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  HSIC_P2_FCLK",
			((extract_bit(cm_clkstctrl, 27) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  HSIC_P1_FCLK",
			((extract_bit(cm_clkstctrl, 26) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  UTMI_ROOT_24M_FCLK",
			((extract_bit(cm_clkstctrl, 25) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  TLL_CH2_FCLK",
			((extract_bit(cm_clkstctrl, 24) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  TLL_CH1_FCLK",
			((extract_bit(cm_clkstctrl, 23) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  TLL_CH0_FCLK",
			((extract_bit(cm_clkstctrl, 22) == 1) ?
				"RUNNING" : "GATED"));

		fprintf(stream, "| %-30s | %-27s |\n", "  HSIC_P2_480M_FCLK",
			((extract_bit(cm_clkstctrl, 21) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  HSIC_P1_480M_FCLK",
			((extract_bit(cm_clkstctrl, 20) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  INIT_HSMMC2_FCLK",
			((extract_bit(cm_clkstctrl, 18) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  INIT_HSMMC1_FCLK",
			((extract_bit(cm_clkstctrl, 17) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  INIT_HSI_FCLK",
			((extract_bit(cm_clkstctrl, 16) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  USB_DPLL_HS_CLK",
			((extract_bit(cm_clkstctrl, 15) == 1) ?
				"RUNNING" : "GATED"));
		if (cpu_is_omap4430() && (cpu_revision_get() == REV_ES1_0))
			fprintf(stream, "| %-30s | %-27s |\n",
				"  L3INIT_DPLL_ALWON_CLK",
				((extract_bit(cm_clkstctrl, 14) == 1) ?
					"RUNNING" : "GATED"));
		else
			fprintf(stream, "| %-30s | %-27s |\n", "  USB_DPLL_CLK",
				((extract_bit(cm_clkstctrl, 14) == 1) ?
					"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  INIT_48MC_FCLK",
			((extract_bit(cm_clkstctrl, 13) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  INIT_48M_FCLK",
			((extract_bit(cm_clkstctrl, 12) == 1) ?
				"RUNNING" : "GATED"));
		if (cpu_is_omap4430() && (cpu_revision_get() == REV_ES1_0)) {
			fprintf(stream, "| %-30s | %-27s |\n",
				"  INIT_96M_FCLK",
				((extract_bit(cm_clkstctrl, 11) == 1) ?
					"RUNNING" : "GATED"));
			fprintf(stream, "| %-30s | %-27s |\n",
				"  UNIPRO_DPLL_FCLK",
				((extract_bit(cm_clkstctrl, 10) == 1) ?
					"RUNNING" : "GATED"));
		}
		fprintf(stream, "| %-30s | %-27s |\n", "  L4_INIT_ICLK",
			((extract_bit(cm_clkstctrl, 9) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  L3_INIT_ICLK",
			((extract_bit(cm_clkstctrl, 8) == 1) ?
				"RUNNING" : "GATED"));
		break;
	case OMAP4430_CM_ALWON_CLKSTCTRL:
		fprintf(stream, "| %-30s | %-27s |\n", "Clock State", "");
		fprintf(stream, "| %-30s | %-27s |\n", "  SR_CORE_SYSCLK",
			((extract_bit(cm_clkstctrl, 11) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  SR_IVA_SYSCLK",
			((extract_bit(cm_clkstctrl, 10) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  SR_MPU_SYSCLK",
			((extract_bit(cm_clkstctrl, 9) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  L4_AO_ICLK",
			((extract_bit(cm_clkstctrl, 8) == 1) ?
				"RUNNING" : "GATED"));
		break;
	case OMAP4430_CM_EMU_CLKSTCTRL:
		fprintf(stream, "| %-30s | %-27s |\n", "Clock State", "");
		if (cpu_is_omap4430() && (cpu_revision_get() == REV_ES1_0))
			fprintf(stream, "| %-30s | %-27s |\n",
				"  PER_DPLL_EMU_CLK",
				((extract_bit(cm_clkstctrl, 10) == 1) ?
					"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  CORE_DPLL_EMU_CLK",
			((extract_bit(cm_clkstctrl, 9) == 1) ?
				"RUNNING" : "GATED"));
		fprintf(stream, "| %-30s | %-27s |\n", "  EMU_SYS_CLK",
			((extract_bit(cm_clkstctrl, 8) == 1) ?
				"RUNNING" : "GATED"));
		break;
	default:
		fprintf(stream, "| %-30s | %-27s |\n", "Clock State",
			((extract_bit(cm_clkstctrl, 8) == 1) ?
				"RUNNING" : "GATED"));
		break;
	}
	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod44xx_config_show
 * @BRIEF		analyze module power configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		stream: output file
 * @param[in]		name: module's name
 * @param[in]		cm_clkctrl_addr: module's CM CLKCTRL register addr
 * @param[in]		cm_clkctrl: module's CM CLKCTRL register content
 * @param[in]		rm_context_addr: module's RM CONTEXT register addr
 * @param[in]		rm_context: module's RM CONTEXT register content
 * @DESCRIPTION		analyze module power configuration
 *//*------------------------------------------------------------------------ */
int mod44xx_config_show(FILE *stream, const char name[11],
	unsigned int cm_clkctrl_addr, unsigned int cm_clkctrl,
	unsigned int rm_context_addr, unsigned int rm_context)
{
	unsigned int cm_alwon_usbphy_clkctrl;
	unsigned int tmp;

	if (!cpu_is_omap44xx()) {
		fprintf(stderr, "%s(): incorrect CPU!!!\n", __func__);
		return OMAPCONF_ERR_CPU;
	}

	dprintf("mod44xx_config_show(): name=%s\n", name);
	dprintf("mod44xx_config_show(): "
		"cm_clkctrl_addr=0x%08X\n", cm_clkctrl_addr);
	dprintf("mod44xx_config_show(): "
		"cm_clkctrl=0x%08X\n", cm_clkctrl);
	dprintf("mod44xx_config_show(): "
		"rm_context_addr=0x%08X\n", rm_context_addr);
	dprintf("mod44xx_config_show(): "
		"rm_context=0x%08X\n\n", rm_context);

	fprintf(stream, "|---------------------------------------------------"
		"-------|\n");
	fprintf(stream, "| %-10s Module Configuration                        "
		"  |\n", name);
	fprintf(stream, "|--------------------------------|------------------"
		"-------|\n");
	/* Module Mode */
	switch (cm_clkctrl_addr) {
	case OMAP4430_CM_MEMIF_DLL_CLKCTRL:
	case OMAP4430_CM_WKUP_BANDGAP_CLKCTRL:
		break;
	default:
		fprintf(stream, "| %-30s | %-23s |\n", "Mode",
			mod_module_mode_name_get((mod_module_mode)
				extract_bitfield(cm_clkctrl, 0, 2)));
		break;
	}

	/* FCLK Source / Optional Clocks */
	switch (cm_clkctrl_addr) {
	case OMAP4430_CM_MPU_MPU_CLKCTRL:
		if (!cpu_is_omap4430()) {
			tmp = (unsigned int) clk44xx_get_clock_speed(
				OMAP4_MPU_DPLL_CLK, 0);
			tmp /= 4 << extract_bit(cm_clkctrl, 25);
			fprintf(stream, "| %-30s | %dMHz (MPU CLK / %1d)    "
				"|\n", "MPU->ABE Async Bridge Speed", tmp,
				4 << extract_bit(cm_clkctrl, 25));
			tmp = (unsigned int) clk44xx_get_clock_speed(
				OMAP4_MPU_DPLL_CLK, 0);
			tmp /= 4 << extract_bit(cm_clkctrl, 24);
			fprintf(stream, "| %-30s | %dMHz (MPU CLK / %1d)    "
				"|\n", "EOCP_MA_ICLK Speed", tmp,
				4 << extract_bit(cm_clkctrl, 24));
		}
		break;
	case OMAP4430_CM1_ABE_DMIC_CLKCTRL:
	case OMAP4430_CM1_ABE_MCBSP1_CLKCTRL:
	case OMAP4430_CM1_ABE_MCBSP2_CLKCTRL:
	case OMAP4430_CM1_ABE_MCBSP3_CLKCTRL:
		switch (extract_bitfield(cm_clkctrl, 24, 2)) {
		case 0:
			switch (extract_bitfield(cm_clkctrl, 26, 2)) {
			case 0:
				fprintf(stream, "| %-30s | %-23s |\n",
					"FCLK Source", "24MHz from DPLL_ABE");
				break;
			case 1:
				fprintf(stream, "| %-30s | %-23s |\n",
					"FCLK Source", "ABE_SYSCLK");
				break;
			case 2:
				fprintf(stream, "| %-30s | %-23s |\n",
					"FCLK Source", "24MHz from DPLL_PER");
				break;
			default:
				fprintf(stream, "| %-30s | %-23s |\n",
					"FCLK Source", "Reserved!");
				break;
			}
			break;
		case 1:
			fprintf(stream, "| %-30s | %-23s |\n",
				"FCLK Source", "CLKS pad");
			break;
		case 2:
			fprintf(stream, "| %-30s | %-23s |\n",
				"FCLK Source", "Audio SLIMBUS pad");
			break;
		default:
			fprintf(stream, "| %-30s | %-23s |\n",
				"FCLK Source", "Reserved!");
			break;
		}
		break;
	case OMAP4430_CM1_ABE_SLIMBUS_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n",
			"Optional functional clock", "");
		fprintf(stream, "| %-30s | %-23s |\n", "  SLIMBUS",
			((extract_bit(cm_clkctrl, 11) == 1) ?
			"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  FCLK2",
			((extract_bit(cm_clkctrl, 10) == 1) ?
			"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  FCLK1",
			((extract_bit(cm_clkctrl, 9) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  FCLK0",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;
	case OMAP4430_CM1_ABE_AESS_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n",
			"Optional functional clock", "");
		fprintf(stream, "| %-30s | = ABE_CLK / %-4d        |\n",
			"  AESS_FCLK",
			(1 << extract_bit(cm_clkctrl, 24)));
		break;
	case OMAP4430_CM1_ABE_TIMER5_CLKCTRL:
	case OMAP4430_CM1_ABE_TIMER6_CLKCTRL:
	case OMAP4430_CM1_ABE_TIMER7_CLKCTRL:
	case OMAP4430_CM1_ABE_TIMER8_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n", "FCLK Source",
			((extract_bit(cm_clkctrl, 24) == 1) ?
			"ABE_ALWON_32K_CLK" : "ABE_SYSCLK"));
		break;
	case OMAP4430_CM_DSS_DSS_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n",
				"Optional functional clock", "");
		if (!cpu_is_omap4470())
			fprintf(stream, "| %-30s | %-23s |\n", "  TV",
				((extract_bit(cm_clkctrl, 11) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  SYS",
			((extract_bit(cm_clkctrl, 10) == 1) ?
			"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  48MHz",
			((extract_bit(cm_clkctrl, 9) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  DSS",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	case OMAP4430_CM_DSS_BB2D_CLKCTRL:
		fprintf(stream, "| %-30s | %-21s   |\n", "BB2D_FCLK Source",
			((extract_bit(cm_clkctrl, 24) == 1) ?
			"DPLL_PER" : "DPLL_CORE"));
		break;

	case OMAP4430_CM_CAM_ISS_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n",
			"Optional functional clock", "");
		fprintf(stream, "| %-30s | %-23s |\n",
			"  CAM_PHY_CTRL_GCLK 96Mhz",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;
	case OMAP4430_CM_CAM_FDIF_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n",
			"Optional functional clock", "");
		fprintf(stream, "| %-30s | = FUNC_128_CLK / %-4d   |\n",
			"  FDIF_FCLK",
			(1 << extract_bitfield(cm_clkctrl, 24, 2)));
		break;
	case OMAP4430_CM_GFX_GFX_CLKCTRL:
		if (cpu_is_omap4430() && (cpu_revision_get() == REV_ES1_0))
			fprintf(stream, "| %-30s | = 192MHz / %-10d   |\n",
			"PER_GFX_FCLK",
				(1 << extract_bitfield(cm_clkctrl, 25, 2)));
		fprintf(stream, "| %-30s | = %-19s   |\n", "GFX_FCLK",
			((extract_bit(cm_clkctrl, 24) == 1) ?
			"DPLL_PER" : "DPLL_CORE"));
		break;
	case OMAP4430_CM_L4PER_DMTIMER10_CLKCTRL:
	case OMAP4430_CM_L4PER_DMTIMER11_CLKCTRL:
	case OMAP4430_CM_WKUP_TIMER1_CLKCTRL:
	case OMAP4430_CM_L4PER_DMTIMER2_CLKCTRL:
	case OMAP4430_CM_L4PER_DMTIMER3_CLKCTRL:
	case OMAP4430_CM_L4PER_DMTIMER4_CLKCTRL:
	case OMAP4430_CM_L4PER_DMTIMER9_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n", "FCLK Source",
			((extract_bit(cm_clkctrl, 24) == 1) ?
				"32KHz" : "SYS_CLK"));
		break;
	case OMAP4430_CM_WKUP_GPIO1_CLKCTRL:
	case OMAP4430_CM_L4PER_GPIO2_CLKCTRL:
	case OMAP4430_CM_L4PER_GPIO3_CLKCTRL:
	case OMAP4430_CM_L4PER_GPIO4_CLKCTRL:
	case OMAP4430_CM_L4PER_GPIO5_CLKCTRL:
	case OMAP4430_CM_L4PER_GPIO6_CLKCTRL:
	case OMAP4430_CM_WKUP_BANDGAP_CLKCTRL:
		if (cpu_is_omap4430()) {
			fprintf(stream, "| %-30s | %-23s |\n",
				"Optional functional clock",
				((extract_bit(cm_clkctrl, 8) == 1) ?
					"Enabled" : "Disabled"));
		} else {
			fprintf(stream, "| %-30s | %-23s |\n",
				"TS F-Clock",
				((extract_bit(cm_clkctrl, 8) == 1) ?
					"Enabled" : "Disabled"));
			tmp = (unsigned int) clk44xx_get_clock_speed(
				OMAP4_L4WKUP_ICLK, 0);
			tmp /= (1 << (3 + extract_bitfield(cm_clkctrl, 24, 2)));
			fprintf(stream, "| %-30s | %dMHz (L4WKUP_ICLK / %-2d) "
				"|\n", "TS F-Clock Speed",
				tmp,
				1 << (3 + extract_bitfield(cm_clkctrl, 24, 2)));
		}
		break;
	case OMAP4430_CM_L4PER_MCBSP4_CLKCTRL:
		if (extract_bit(cm_clkctrl, 24) == 1) {
			fprintf(stream, "| %-30s | %-23s |\n",
				"FCLK Source", "CLKS Pad");
		} else {
			fprintf(stream, "| %-30s | %-23s |\n", "FCLK Source",
				((extract_bit(cm_clkctrl, 25) == 1) ?
				"DPLL_ABE 96MHz" : "DPLL_PER 96MHz"));
		}

		break;
	case OMAP4430_CM_L4PER_SLIMBUS2_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n",
			"Optional functional clock", "");
		fprintf(stream, "| %-30s | %-23s |\n", "  SLIMBUS",
			((extract_bit(cm_clkctrl, 10) == 1) ?
			"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  PER_ABE_24M_FCLK",
			((extract_bit(cm_clkctrl, 9) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  PER_24MC_FCLK",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;
	case OMAP4430_CM_MEMIF_DLL_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n", "Optional DLL_CLK FCLK",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;
	case OMAP4430_CM_WKUP_USIM_CLKCTRL:
		fprintf(stream, "| %-30s | = CM2 128MHz / %-2s       |\n",
			"USIM FCLK",
			((extract_bit(cm_clkctrl, 24) == 1) ? "18" : "14"));
		break;
	case OMAP4430_CM_L3INIT_MMC1_CLKCTRL:
	case OMAP4430_CM_L3INIT_MMC2_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n", "FCLK Source",
			((extract_bit(cm_clkctrl, 24) == 1) ?
			"96MHz from DPLL_PER" : "64MHz from DPLL_PER"));
		break;
	case OMAP4430_CM_L3INIT_HSI_CLKCTRL:
		switch (extract_bitfield(cm_clkctrl, 24, 2)) {
		case 0:
			fprintf(stream, "| %-30s | %-23s |\n",
				"FCLK Source", "192MHz / 1");
			break;
		case 1:
			fprintf(stream, "| %-30s | %-23s |\n",
				"FCLK Source", "192MHz / 2");
			break;
		case 2:
			fprintf(stream, "| %-30s | %-23s |\n",
				"FCLK Source", "192MHz / 4");
			break;
		default:
			fprintf(stream, "| %-30s | %-23s |\n",
				"FCLK Source", "Reserved!!!");
		}
		break;
	case OMAP4430_CM_L3INIT_UNIPRO1_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n",
			"Optional UNIPRO TX PHY clock",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;
	case OMAP4430_CM_L3INIT_USB_HOST_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n", "UTMI Port2 Source",
			((extract_bit(cm_clkctrl, 25) == 1) ?
			"external PHY" : "internal"));
		fprintf(stream, "| %-30s | %-23s |\n", "UTMI Port1 Source",
			((extract_bit(cm_clkctrl, 24) == 1) ?
			"external PHY" : "internal"));

		fprintf(stream, "| %-30s | %-23s |\n", "SAR MODE",
			((extract_bit(cm_clkctrl, 4) == 1) ?
				"Enabled" : "Disabled"));

		fprintf(stream, "| %-30s | %-23s |\n",
			"Optional functional clock", "");
		fprintf(stream, "| %-30s | %-23s |\n", "  FUNC48MCLK",
			((extract_bit(cm_clkctrl, 15) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  HSIC480M_P2_CLK",
			((extract_bit(cm_clkctrl, 14) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  HSIC480M_P1_CLK",
			((extract_bit(cm_clkctrl, 13) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  HSIC60M_P2_CLK",
			((extract_bit(cm_clkctrl, 12) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  HSIC60M_P1_CLK",
			((extract_bit(cm_clkctrl, 11) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  UTMI_P3_CLK",
			((extract_bit(cm_clkctrl, 10) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  UTMI_P2_CLK",
			((extract_bit(cm_clkctrl, 9) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  UTMI_P1_CLK",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;
	case OMAP4430_CM_L3INIT_USB_OTG_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n", "60MHz Source CLK",
			((extract_bit(cm_clkctrl, 24) == 1) ?
			"external ULPI PHY" : "on die UTMI PHY"));

		fprintf(stream, "| %-30s | %-23s |\n",
			"Optional XCLK (60MHz) clock",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;
	case OMAP4430_CM_L3INIT_USB_TLL_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n", "SAR MODE",
			((extract_bit(cm_clkctrl, 4) == 1) ?
				"Enabled" : "Disabled"));

		fprintf(stream, "| %-30s | %-23s |\n",
			"Optional functional clock", "");
		fprintf(stream, "| %-30s | %-23s |\n", "  USB_CH2_CLK",
			((extract_bit(cm_clkctrl, 10) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  USB_CH1_CLK",
			((extract_bit(cm_clkctrl, 9) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  USB_CH0_CLK",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;
	case OMAP4430_CM_L3INIT_USBPHYOCP2SCP_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n",
			"Optional functional clock", "");
		if (cpu_is_omap4430() && (cpu_revision_get() == REV_ES1_0)) {
			fprintf(stream, "| %-30s | %-23s |\n", "  32KHz clock",
				((extract_bit(cm_clkctrl, 9) == 1) ?
					"Enabled" : "Disabled"));
		} else {
			if (mem_read(OMAP4430_CM_ALWON_USBPHY_CLKCTRL,
				&cm_alwon_usbphy_clkctrl) != 0)
				return OMAPCONF_ERR_REG_ACCESS;
			fprintf(stream, "| %-30s | %-23s |\n", "  32KHz clock",
				((extract_bit(cm_alwon_usbphy_clkctrl, 8)
					== 1) ? "Enabled" : "Disabled"));
		}
		fprintf(stream, "| %-30s | %-23s |\n", "  PHY_48M",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;
	case OMAP4430_CM_EMU_DEBUGSS_CLKCTRL:
		switch (extract_bitfield(cm_clkctrl, 20, 2)) {
		case 0:
			fprintf(stream, "| %-30s | %-23s |\n",
				"STM source clock", "SYS_CLK");
			break;
		case 1:
			fprintf(stream, "| %-30s | %-23s |\n",
				"STM source clock", "CORE_DPLL_EMU_CLK");
			break;
		case 2:
			fprintf(stream, "| %-30s | %-23s |\n",
				"STM source clock", "PER_DPLL_EMU_CLK");
			break;
		default:
			fprintf(stream, "| %-30s | %-23s |\n",
				"STM source clock", "Reserved!!!");
		}
		switch (extract_bitfield(cm_clkctrl, 27, 3)) {
		case 1:
			fprintf(stream, "| %-30s | %-23s |\n",
				"STM clock division", "STM source / 1");
			break;
		case 2:
			fprintf(stream, "| %-30s | %-23s |\n",
				"STM clock division", "STM source / 2");
			break;
		case 4:
			fprintf(stream, "| %-30s | %-23s |\n",
				"STM clock division", "STM source / 4");
			break;
		default:
			fprintf(stream, "| %-30s | %-23s |\n",
				"STM clock division", "Reserved!!!");
		}
		switch (extract_bitfield(cm_clkctrl, 22, 2)) {
		case 0:
			fprintf(stream, "| %-30s | %-23s |\n",
				"TRACE source clock", "SYS_CLK");
			break;
		case 1:
			fprintf(stream, "| %-30s | %-23s |\n",
				"TRACE source clock", "CORE_DPLL_EMU_CLK");
			break;
		case 2:
			if (cpu_is_omap4430() &&
				(cpu_revision_get() == REV_ES1_0))
				fprintf(stream, "| %-30s | %-23s |\n",
					"TRACE source clock",
					"PER_DPLL_EMU_CLK");
			else
				fprintf(stream, "| %-30s | %-23s |\n",
				"TRACE source clock", "Reserved!!!");
			break;
		default:
			fprintf(stream, "| %-30s | %-23s |\n",
				"TRACE source clock", "Reserved!!!");
		}
		switch (extract_bitfield(cm_clkctrl, 24, 3)) {
		case 1:
			fprintf(stream, "| %-30s | %-23s |\n",
				"TRACE clock division", "TRACE source / 1");
			break;
		case 2:
			fprintf(stream, "| %-30s | %-23s |\n",
				"TRACE clock division", "TRACE source / 2");
			break;
		case 4:
			fprintf(stream, "| %-30s | %-23s |\n",
				"TRACE clock division", "TRACE source / 4");
			break;
		default:
			fprintf(stream, "| %-30s | %-23s |\n",
				"TRACE clock division", "Reserved!!!");
		}
		break;
	default:
		break;
	}

	/* Idle Status */
	switch (cm_clkctrl_addr) {
	case OMAP4430_CM_MEMIF_DLL_CLKCTRL:
	case OMAP4430_CM_WKUP_BANDGAP_CLKCTRL:
		break;
	default:
		fprintf(stream, "| %-30s | %-23s |\n", "Idle Status",
			mod_idle_status_name_get((mod_idle_status)
				extract_bitfield(cm_clkctrl, 16, 2)));
		break;
	}

	/* Standby Status */
	switch (cm_clkctrl_addr) {
	case OMAP4430_CM_IVAHD_SL2_CLKCTRL:
	case OMAP4430_CM_MPU_M3_MPU_M3_CLKCTRL:
	case OMAP4430_CM_SDMA_SDMA_CLKCTRL:
	case OMAP4430_CM_C2C_C2C_CLKCTRL:
	case OMAP4430_CM1_ABE_AESS_CLKCTRL:
	case OMAP4430_CM_L3INIT_MMC1_CLKCTRL:
	case OMAP4430_CM_L3INIT_MMC2_CLKCTRL:
	case OMAP4430_CM_L3INIT_HSI_CLKCTRL:
	case OMAP4430_CM_L3INIT_UNIPRO1_CLKCTRL:
	case OMAP4430_CM_L3INIT_USB_HOST_CLKCTRL:
	case OMAP4430_CM_L3INIT_USB_OTG_CLKCTRL:
	case OMAP4430_CM_L3INIT_P1500_CLKCTRL:
	case OMAP4430_CM_L3INIT_USB_HOST_FS_CLKCTRL:
	case OMAP4430_CM_EMU_DEBUGSS_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n", "Standby Status",
			((extract_bit(cm_clkctrl, 18) == 1) ?
				"Standby" : "Not in Standby"));
		break;
	default:
		break;
	}


	switch (rm_context_addr) {
	case 0: /* no context register */
		break;
	default:
		fprintf(stream, "| %-30s | %-23s |\n", "Last Context", "");
		break;
	}

	switch (rm_context_addr) {
	case OMAP4430_RM_MPU_MPU_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  RAM",
			((extract_bit(rm_context, 10) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_DSP_DSP_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  EDMA",
			((extract_bit(rm_context, 10) == 1) ?
				"LOST" : "RETAINED"));
		break;
	default:
		break;
	}

	switch (rm_context_addr) {
	case OMAP4430_RM_IVAHD_IVAHD_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  HWA",
			((extract_bit(rm_context, 10) == 1) ?
				"LOST" : "RETAINED"));
		break;
	default:
		break;
	}

	switch (rm_context_addr) {
	case OMAP4430_RM_MPU_MPU_CONTEXT:
	case OMAP4430_RM_DSP_DSP_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  L2$",
			((extract_bit(rm_context, 9) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_IVAHD_IVAHD_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  TCM2",
			((extract_bit(rm_context, 9) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_MPU_M3_MPU_M3_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  L2RAM",
			((extract_bit(rm_context, 9) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_MEMIF_DMM_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  CORE_NRET_BANK",
			((extract_bit(rm_context, 9) == 1) ?
				"LOST" : "RETAINED"));
		break;
	default:
		break;
	}

	switch (rm_context_addr) {
	case OMAP4430_RM_WKUP_SARRAM_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  WKUP_BANK",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_MPU_MPU_CONTEXT:
		if (cpu_is_omap4430())
			fprintf(stream, "| %-30s | %-23s |\n", "  L1$",
				((extract_bit(rm_context, 8) == 1) ?
					"LOST" : "RETAINED"));
		else
			fprintf(stream, "| %-30s | %-23s |\n", "  L1$", "");
		break;
	case OMAP4430_RM_DSP_DSP_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  L1$",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_DSS_DSS_CONTEXT:
	/*
	 * case OMAP4430_RM_DSS_DEISS_CONTEXT:
	 * module not implemented in 44xx,
	 * at same address as OMAP4430_RM_DSS_BB2D_CONTEXT in 4470
	 * causing duplicate case value ...
	 */
	case OMAP4430_RM_DSS_BB2D_CONTEXT:
	case OMAP4430_RM_CAM_ISS_CONTEXT:
	case OMAP4430_RM_CAM_FDIF_CONTEXT:
	case OMAP4430_RM_GFX_GFX_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  MEM",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_IVAHD_IVAHD_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  TCM1",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_IVAHD_SL2_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  SL2",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_L4PER_MCBSP4_CONTEXT:
	case OMAP4430_RM_L4PER_MMCSD3_CONTEXT:
	case OMAP4430_RM_L4PER_MMCSD4_CONTEXT:
	case OMAP4430_RM_L4PER_SLIMBUS2_CONTEXT:
	case OMAP4430_RM_L4PER_MMCSD5_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  NONRETAINED_BANK",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_L4PER_UART1_CONTEXT:
	case OMAP4430_RM_L4PER_UART2_CONTEXT:
	case OMAP4430_RM_L4PER_UART3_CONTEXT:
	case OMAP4430_RM_L4PER_UART4_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  RETAINED_BANK",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_L3_2_OCMC_RAM_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  OCM RAM",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_MPU_M3_MPU_M3_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  Unicache",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_SDMA_SDMA_CONTEXT:
	case OMAP4430_RM_MEMIF_DMM_CONTEXT:
	case OMAP4430_RM_C2C_MODEM_ICR_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  CORE_OTHER_BANK",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_L3INSTR_OCP_WP1_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  CORE_NRET_BANK",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_ABE_AESS_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  AESSMEM",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_ABE_PDM_CONTEXT:
	case OMAP4430_RM_ABE_DMIC_CONTEXT:
	case OMAP4430_RM_ABE_MCBSP1_CONTEXT:
	case OMAP4430_RM_ABE_MCBSP2_CONTEXT:
	case OMAP4430_RM_ABE_MCBSP3_CONTEXT:
	case OMAP4430_RM_ABE_SLIMBUS_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  PERIPHMEM",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_L3INIT_MMC1_CONTEXT:
	case OMAP4430_RM_L3INIT_MMC2_CONTEXT:
	case OMAP4430_RM_L3INIT_HSI_CONTEXT:
	case OMAP4430_RM_L3INIT_UNIPRO1_CONTEXT:
	case OMAP4430_RM_L3INIT_USB_OTG_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  L3INIT_BANK1",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_EMU_DEBUGSS_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  EMU_BANK",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	default:
		break;
	}

	/* RFF-based */
	switch (rm_context_addr) {
	case OMAP4430_RM_DSP_DSP_CONTEXT:
	case OMAP4430_RM_DSS_DSS_CONTEXT:
	case OMAP4430_RM_L4PER_L4_PER_CONTEXT:
	case OMAP4430_RM_L4PER_GPIO2_CONTEXT:
	case OMAP4430_RM_L4PER_GPIO3_CONTEXT:
	case OMAP4430_RM_L4PER_GPIO4_CONTEXT:
	case OMAP4430_RM_L4PER_GPIO5_CONTEXT:
	case OMAP4430_RM_L4PER_GPIO6_CONTEXT:
	case OMAP4430_RM_L4PER_I2C1_CONTEXT:
	case OMAP4430_RM_L4PER_UART1_CONTEXT:
	case OMAP4430_RM_L4PER_UART2_CONTEXT:
	case OMAP4430_RM_L4PER_UART3_CONTEXT:
	case OMAP4430_RM_L4PER_UART4_CONTEXT:
	case OMAP4430_RM_L3_1_L3_1_CONTEXT:
	case OMAP4430_RM_L3_2_L3_2_CONTEXT:
	case OMAP4430_RM_L3_2_GPMC_CONTEXT:
	case OMAP4430_RM_MPU_M3_MPU_M3_CONTEXT:
	case OMAP4430_RM_SDMA_SDMA_CONTEXT:
	case OMAP4430_RM_MEMIF_DMM_CONTEXT:
	case OMAP4430_RM_MEMIF_EMIF_FW_CONTEXT:
	case OMAP4430_RM_MEMIF_EMIF_1_CONTEXT:
	case OMAP4430_RM_MEMIF_EMIF_2_CONTEXT:
	case OMAP4430_RM_C2C_C2C_CONTEXT:
	case OMAP4430_RM_C2C_MODEM_ICR_CONTEXT:
	case OMAP4430_RM_C2C_C2C_FW_CONTEXT:
	case OMAP4430_RM_L4CFG_L4_CFG_CONTEXT:
	case OMAP4430_RM_L4CFG_HW_SEM_CONTEXT:
	case OMAP4430_RM_L4CFG_MAILBOX_CONTEXT:
	case OMAP4430_RM_L3INSTR_L3_3_CONTEXT:
	case OMAP4430_RM_L3INSTR_OCP_WP1_CONTEXT:
	case OMAP4430_RM_L3INIT_MMC1_CONTEXT:
	case OMAP4430_RM_L3INIT_MMC2_CONTEXT:
	case OMAP4430_RM_L3INIT_HSI_CONTEXT:
	case OMAP4430_RM_L3INIT_USB_HOST_CONTEXT:
	case OMAP4430_RM_L3INIT_USB_OTG_CONTEXT:
	case OMAP4430_RM_L3INIT_USB_TLL_CONTEXT:
	case OMAP4430_RM_L3INIT_USB_HOST_FS_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  RFF-Based",
			((extract_bit(rm_context, 1) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_MPU_MPU_CONTEXT:
		if (!cpu_is_omap4430())
			fprintf(stream, "| %-30s | %-23s |\n", "  RFF-Based",
				((extract_bit(rm_context, 1) == 1) ?
					"LOST" : "RETAINED"));
		break;
	default:
		break;
	}

	/* DFF-based */
	switch (rm_context_addr) {
	case OMAP4430_RM_L4PER_GPIO2_CONTEXT:
	case OMAP4430_RM_L4PER_GPIO3_CONTEXT:
	case OMAP4430_RM_L4PER_GPIO4_CONTEXT:
	case OMAP4430_RM_L4PER_GPIO5_CONTEXT:
	case OMAP4430_RM_L4PER_GPIO6_CONTEXT:
	case OMAP4430_RM_L4PER_I2C1_CONTEXT:
	case OMAP4430_RM_L4PER_UART1_CONTEXT:
	case OMAP4430_RM_L4PER_UART2_CONTEXT:
	case OMAP4430_RM_L4PER_UART3_CONTEXT:
	case OMAP4430_RM_L4PER_UART4_CONTEXT:
	case OMAP4430_RM_L3_2_GPMC_CONTEXT:
	case OMAP4430_RM_SDMA_SDMA_CONTEXT:
	case OMAP4430_RM_C2C_MODEM_ICR_CONTEXT:
	case OMAP4430_RM_L4CFG_HW_SEM_CONTEXT:
	case OMAP4430_RM_L4CFG_MAILBOX_CONTEXT:
	case OMAP4430_RM_L3INIT_MMC1_CONTEXT:
	case OMAP4430_RM_L3INIT_MMC2_CONTEXT:
	case OMAP4430_RM_L3INIT_HSI_CONTEXT:
	case OMAP4430_RM_L3INIT_USB_HOST_CONTEXT:
	case OMAP4430_RM_L3INIT_USB_OTG_CONTEXT:
	case OMAP4430_RM_L3INIT_USB_TLL_CONTEXT:
	case OMAP4430_RM_L3INIT_USB_HOST_FS_CONTEXT:
	case 0:
		break;
	case OMAP4430_RM_MEMIF_EMIF_1_CONTEXT:
	case OMAP4430_RM_MEMIF_EMIF_2_CONTEXT:
		if ((cpu_is_omap4430() && (cpu_revision_get() != REV_ES1_0))
			|| cpu_is_omap4460() || cpu_is_omap4470()) {
			fprintf(stream, "| %-30s | %-23s |\n", "  DFF-based",
				((extract_bit(rm_context, 0) == 1) ?
					"LOST" : "RETAINED"));
		}
		break;
	default:

		fprintf(stream, "| %-30s | %-23s |\n", "  DFF-based",
			((extract_bit(rm_context, 0) == 1) ?
				"LOST" : "RETAINED"));
		break;
	}
	fprintf(stream, "|----------------------------------------------------"
		"------|\n");
	fprintf(stream, "\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		power44xx_status_show
 * @BRIEF		analyze & display OMAP4 power status
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @DESCRIPTION		analyze & display OMAP4 power status
 *//*------------------------------------------------------------------------ */
int power44xx_status_show(void)
{
	char s_idlest[14];
	char s_stbyst[11];
	char pwst[6];
	char pwtgst[6];
	char s_clkst[CLKDM_STATUS_MAX_NAME_LENGTH];
	clkdm_status clkst;
	opp44xx_id current_opp;
	char s_current_opp[OMAP4_VD_ID_MAX][OPP44XX_MAX_NAME_LENGTH] = {
		"",
		"UNKNOWN",
		"UNKNOWN",
		"UNKNOWN"};
	int ret = 0;
	unsigned short first_mod, first_clkdm, first_pwrdm;
	mod44xx_id mod_id;
	clkdm44xx_id clkdm_id;
	pwrdm44xx_id pwrdm_id;
	voltdm44xx_id voltdm_id;
	char mod_name[MODULE_MAX_NAME_LENGTH];
	char clkdm_name[CLKDM44XX_MAX_NAME_LENGTH];
	char pwrdm_name[PWRDM44XX_MAX_NAME_LENGTH];
	char voltdm_name[VOLTDM44XX_MAX_NAME_LENGTH];

	if (!cpu_is_omap44xx())
		return OMAPCONF_ERR_CPU;

	/* For each voltage domain, retrieve the current OPP */
	ret = voltdm44xx_get_opp(OMAP4_VDD_MPU, &current_opp);
	if (ret != 0)
		dprintf("%s(): warning OMAP4_VDD_MPU OPP not detected!!!\n",
			__func__);
	else
		voltdm44xx_opp2string(s_current_opp[OMAP4_VDD_MPU],
			current_opp, OMAP4_VDD_MPU);
	ret = voltdm44xx_get_opp(OMAP4_VDD_IVA, &current_opp);
	if (ret != 0)
		dprintf("%s(): warning OMAP4_VDD_IVA OPP not detected!!!\n",
			__func__);
	else
		voltdm44xx_opp2string(s_current_opp[OMAP4_VDD_IVA],
			current_opp, OMAP4_VDD_IVA);
	ret = voltdm44xx_get_opp(OMAP4_VDD_CORE, &current_opp);
	if (ret != 0)
		dprintf("%s(): warning OMAP4_VDD_CORE OPP not detected!!!\n",
			__func__);
	else
		voltdm44xx_opp2string(s_current_opp[OMAP4_VDD_CORE],
			current_opp, OMAP4_VDD_CORE);

	printf("|--------------------------------------------------------------"
		"--------------------------------------------------------------"
		"----|\n");
	printf("| OMAP Power Status                                            "
		"                                                              "
		"    |\n");
	printf("|--------------------------------------------------------------"
		"--------------------------------------------------------------"
		"----|\n");
	printf("| Voltage Domain          | Power Domain                 | "
		"Clock Domain          | Module Status                         "
		"        |\n");
	printf("| Name     | OPP          | Name       | Curr.  | Target | "
		"Name       | Status   | Name             | Idle          |"
		" Standby    |\n");
	/* For each domain, retrieve the clock & power domain status */
	for (voltdm_id = 0; voltdm_id < OMAP4_VD_ID_MAX; voltdm_id++) {
		printf("|------------------------------------------------------"
			"------------------------------------------------------"
			"--------------------|\n");
		voltdm44xx_get_name(voltdm_id, voltdm_name);
		for (pwrdm_id = 0, first_pwrdm = 1; pwrdm_id < OMAP4_PD_ID_MAX;
			pwrdm_id++) {
			if (pwrdm44xx_get_voltdm(pwrdm_id) != voltdm_id)
				continue;

			pwrdm44xx_get_name(pwrdm_id, pwrdm_name);
			switch (pwrdm_id) {
			case OMAP4_PD_WKUP:
			case OMAP4_PD_ALWON_MPU:
			case OMAP4_PD_ALWON_IVA:
			case OMAP4_PD_ALWON_CORE:
				strcpy(pwst, "ON");
				strcpy(pwtgst, "");
				break;
			case OMAP4_PD_STD_EFUSE:
			case OMAP4_PD_CUST_EFUSE:
				continue;
			default:
				pwrdm_states_get(pwrdm_name, pwst, pwtgst);
			}

			for (clkdm_id = 0, first_clkdm = 1;
				clkdm_id < OMAP4_CD_NONE; clkdm_id++) {
				if ((clkdm_id == OMAP4_CD_L4_SEC) &&
					cpu_is_gp_device())
					continue;
				if (clkdm44xx_get_pwrdm(clkdm_id) != pwrdm_id)
					continue;

				if ((!first_pwrdm) && (first_clkdm))
					printf("| %-8s | %-12s |---------------"
						"------------------------------"
						"------------------------------"
						"---------------------------"
						"|\n", "", "");
				clkdm44xx_get_name(clkdm_id, clkdm_name);
				clkdm44xx_get_status(clkdm_id, &clkst);
				strcpy(s_clkst, clkdm_status_name_get(clkst));

				/* For each module, retrieve status */
				for (mod_id = 0, first_mod = 1; mod_id <
						OMAP4_MODULE_ID_MAX; mod_id++) {
					if (mod44xx_get_clkdm(mod_id) !=
						clkdm_id)
						continue;

					switch (mod_id) {
					case OMAP4_TIMER12:
					case OMAP4_WDT1:
					case OMAP4_USIM:
						if (cpu_is_gp_device())
							continue;
					case OMAP4_MCSPI1_HL:
					case OMAP4_MCSPI2_HL:
					case OMAP4_MCSPI3_HL:
					case OMAP4_MCSPI4_HL:
					case OMAP4_MMC1_HL:
					case OMAP4_MMC2_HL:
					case OMAP4_MMC3_HL:
					case OMAP4_MMC4_HL:
					case OMAP4_MMC5_HL:
						/* "Duplicates", just skip it */
						continue;
					case OMAP4_CONTROL_GEN_WKUP:
					case OMAP4_CONTROL_PADCONF_WKUP:
					case OMAP4_CONTROL_GEN_CORE:
					case OMAP4_CONTROL_PADCONF_CORE:
					case OMAP4_ICR_MDM:
					case OMAP4_ICR_MPU:
					case OMAP4_DDRPHY:
					case OMAP4_ICONT1:
					case OMAP4_ICONT2:
					case OMAP4_VDMA:
					case OMAP4_IME3:
					case OMAP4_IPE3:
					case OMAP4_ILF3:
					case OMAP4_MC3:
					case OMAP4_CALC3:
					case OMAP4_ECD3:
					case OMAP4_ICONT1_SB:
					case OMAP4_ICONT2_SB:
					case OMAP4_ILF3_SB:
					case OMAP4_IME3_SB:
					case OMAP4_CALC3_SB:
					case OMAP4_IPE3_SB:
					case OMAP4_MC3_SB:
					case OMAP4_ECD3_SB:
					case OMAP4_SL2:
					case OMAP4_MMU_DSP:
					case OMAP4_DSP_WUGEN:
					case OMAP4_CCP2:
					case OMAP4_CSI2_A:
					case OMAP4_CSI2_B:
					case OMAP4_TCTRL:
					case OMAP4_BTE:
					case OMAP4_CBUFF:
					case OMAP4_ISP5:
					case OMAP4_RSZ:
					case OMAP4_SIMCOP:
					case OMAP4_SIMCOP_DMA:
					case OMAP4_SIMCOP_DCT:
					case OMAP4_SIMCOP_VLCDJ:
					case OMAP4_SIMCOP_ROT:
					case OMAP4_DSI1:
					case OMAP4_DSI2:
					case OMAP4_HDMI:
					case OMAP4_RFBI:
						/* no status available */
						 continue;
					case OMAP4_P1500:
					case OMAP4_ELM:
						/*
						 * ignored
						 */
						 continue;
					case OMAP4_DLL:
						/* Internal. No need to show. */
						continue;

					case OMAP4_FSUSBHOST:
						if (cpu_is_omap4470())
							continue;
						break;

					case OMAP4_BB2D:
						if (!cpu_is_omap4470())
							continue;
						mod44xx_get_name(
							mod_id, mod_name);
						mod44xx_get_idle_status(mod_id,
							s_idlest);
						mod44xx_get_standby_status(
							mod_id, s_stbyst);
						break;
					default:
						mod44xx_get_name(
							mod_id, mod_name);
						mod44xx_get_idle_status(mod_id,
							s_idlest);
						mod44xx_get_standby_status(
							mod_id, s_stbyst);
					}
					mod44xx_get_name(
						mod_id, mod_name);
					mod44xx_get_idle_status(mod_id,
						s_idlest);
					mod44xx_get_standby_status(
						mod_id, s_stbyst);

					if ((first_mod) && (!first_clkdm))
						printf("| %-8s | %-12s | %-10s "
							"| %-6s | %-6s |-------"
							"----------------------"
							"----------------------"
							"--------------------|"
							"\n",
							"", "", "", "", "");
					printf("| %-8s | %-12s | %-10s | %-6s |"
						" %-6s | %-10s | %-8s | %-16s |"
						" %-13s | %-10s |\n",
						voltdm_name,
						s_current_opp[voltdm_id],
						pwrdm_name, pwst, pwtgst,
						clkdm_name, s_clkst, mod_name,
						s_idlest, s_stbyst);
					if (first_mod) {
						*clkdm_name = '\0';
						*pwrdm_name = '\0';
						*voltdm_name = '\0';
						*s_current_opp[voltdm_id] =
							'\0';
						*pwst = '\0';
						*pwtgst = '\0';
						*s_clkst = '\0';
						first_mod = 0;
					}
				}
				first_clkdm = 0;
			}
			first_pwrdm = 0;
		}

	}
	printf("|--------------------------------------------------------------"
		"--------------------------------------------------------------"
		"----|\n\n");

	return 0;
}
