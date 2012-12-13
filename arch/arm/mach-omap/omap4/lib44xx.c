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
