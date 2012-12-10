/*
 *
 * @Component			OMAPCONF
 * @Filename			mpu44xx.c
 * @Description			OMAP4 PRCM MPU Definitions & Functions
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


#include <dpll.h>
#include <dpll44xx.h>
#include <lib44xx.h>
#include <help.h>
#include <clkdm.h>
#include <cm44xx.h>
#include <prm44xx.h>
#include <pwrdm44xx.h>
#include <module44xx.h>
#include <lib.h>
#include <mem.h>
#include <cpuinfo.h>
#include <string.h>


/* #define MPU44XX_DEBUG */
#ifdef MPU44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

#define OMAP4430_SCU_CPU_POWER_STATUS 0x48240008

#define OMAPCONF_SCU_CPU_POWER_STATUS_2_STRING(s, status) \
	switch (status) { \
	case 0: \
		strcpy(s, "Normal"); \
		break; \
	case 1: \
		strcpy(s, "Reserved"); \
		break; \
	case 2: \
		strcpy(s, "Dormant"); \
		break; \
	case 3: \
		strcpy(s, "OFF"); \
		break; \
	}

reg_table prcm_mpu_reg_table[28];


static char omap44xx_prm_irq_names
	[OMAP44XX_PRM_IRQ_MAX_NBR][OMAP44XX_PRM_IRQ_NAME_LENGTH] = {
	"DPLL_CORE_RECAL",
	"DPLL_MPU_RECAL",
	"DPLL_IVA_RECAL",
	"DPLL_PER_RECAL",
	"DPLL_ABE_RECAL",
	"DPLL_USB_RECAL",
	"RESERVED",
	"DPLL_UNIPRO_RECAL",
	"TRANSITION",
	"IO",
	"RESERVED",
	"VC_SAERR",
	"VC_RAERR",
	"VC_TOERR",
	"VC_BYPASSACK",
	"RESERVED",
	"VP_CORE_OPPCHANGEDONE",
	"VP_CORE_MINVDD",
	"VP_CORE_MAXVDD",
	"VP_CORE_NOSMPSACK",
	"VP_CORE_EQVALUE",
	"VP_CORE_TRANXDONE",
	"RESERVED",
	"RESERVED",
	"VP_IVA_OPPCHANGEDONE",
	"VP_IVA_MINVDD",
	"VP_IVA_MAXVDD",
	"VP_IVA_NOSMPSACK",
	"VP_IVA_EQVALUE",
	"VP_IVA_TRANXDONE",
	"VC_IVA_VPACK",
	"ABB_IVA_DONE",
	"VP_MPU_OPPCHANGEDONE",
	"VP_MPU_MINVDD",
	"VP_MPU_MAXVDD",
	"VP_MPU_NOSMPSACK",
	"VP_MPU_EQVALUE",
	"VP_MPU_TRANXDONE",
	"VC_MPU_VPACK",
	"ABB_MPU_DONE"};

static unsigned int init_done = 0;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mpu44xx_regtable_init
 * @BRIEF		initialize reg_table fields (not possible statically)
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		initialize reg_table fields (not possible statically)
 *//*------------------------------------------------------------------------ */
int mpu44xx_regtable_init(void)
{
	int i = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	/* Init PRCM MPU registers table */
	strcpy(prcm_mpu_reg_table[i].name, "PM_PDA_CPU0_PWRSTCTRL");
	prcm_mpu_reg_table[i++].addr = OMAP4430_PM_PDA_CPU0_PWRSTCTRL;
	strcpy(prcm_mpu_reg_table[i].name, "PM_PDA_CPU0_PWRSTST");
	prcm_mpu_reg_table[i++].addr = OMAP4430_PM_PDA_CPU0_PWRSTST;
	strcpy(prcm_mpu_reg_table[i].name, "RM_PDA_CPU0_CONTEXT");
	prcm_mpu_reg_table[i++].addr = OMAP4430_RM_PDA_CPU0_CPU0_CONTEXT;
	strcpy(prcm_mpu_reg_table[i].name, "RM_PDA_CPU0_RSTCTRL");
	prcm_mpu_reg_table[i++].addr = OMAP4430_RM_PDA_CPU0_CPU0_RSTCTRL;
	strcpy(prcm_mpu_reg_table[i].name, "CM_PDA_CPU0_CLKCTRL");
	prcm_mpu_reg_table[i++].addr = OMAP4430_CM_PDA_CPU0_CPU0_CLKCTRL;
	strcpy(prcm_mpu_reg_table[i].name, "CM_PDA_CPU0_CLKSTCTRL");
	prcm_mpu_reg_table[i++].addr = OMAP4430_CM_PDA_CPU0_CLKSTCTRL;
	strcpy(prcm_mpu_reg_table[i].name, "PM_PDA_CPU1_PWRSTCTRL");
	prcm_mpu_reg_table[i++].addr = OMAP4430_PM_PDA_CPU1_PWRSTCTRL;
	strcpy(prcm_mpu_reg_table[i].name, "PM_PDA_CPU1_PWRSTST");
	prcm_mpu_reg_table[i++].addr = OMAP4430_PM_PDA_CPU1_PWRSTST;
	strcpy(prcm_mpu_reg_table[i].name, "RM_PDA_CPU1_CONTEXT");
	prcm_mpu_reg_table[i++].addr = OMAP4430_RM_PDA_CPU1_CPU1_CONTEXT;
	strcpy(prcm_mpu_reg_table[i].name, "RM_PDA_CPU1_RSTCTRL");
	prcm_mpu_reg_table[i++].addr = OMAP4430_RM_PDA_CPU1_CPU1_RSTCTRL;
	strcpy(prcm_mpu_reg_table[i].name, "CM_PDA_CPU1_CLKCTRL");
	prcm_mpu_reg_table[i++].addr = OMAP4430_CM_PDA_CPU1_CPU1_CLKCTRL;
	strcpy(prcm_mpu_reg_table[i].name, "CM_PDA_CPU1_CLKSTCTRL");
	prcm_mpu_reg_table[i++].addr = OMAP4430_CM_PDA_CPU1_CLKSTCTRL;
	strcpy(prcm_mpu_reg_table[i].name, "PM_MPU_PWRSTCTRL");
	prcm_mpu_reg_table[i++].addr = OMAP4430_PM_MPU_PWRSTCTRL;
	strcpy(prcm_mpu_reg_table[i].name, "PM_MPU_PWRSTST");
	prcm_mpu_reg_table[i++].addr = OMAP4430_PM_MPU_PWRSTST;
	strcpy(prcm_mpu_reg_table[i].name, "RM_MPU_MPU_CONTEXT");
	prcm_mpu_reg_table[i++].addr = OMAP4430_RM_MPU_MPU_CONTEXT;
	strcpy(prcm_mpu_reg_table[i].name, "CM_MPU_CLKSTCTRL");
	prcm_mpu_reg_table[i++].addr = OMAP4430_CM_MPU_CLKSTCTRL;
	strcpy(prcm_mpu_reg_table[i].name, "CM_MPU_MPU_CLKCTRL");
	prcm_mpu_reg_table[i++].addr = OMAP4430_CM_MPU_MPU_CLKCTRL;
	strcpy(prcm_mpu_reg_table[i].name, "CM_MPU_STATICDEP");
	prcm_mpu_reg_table[i++].addr = OMAP4430_CM_MPU_STATICDEP;
	strcpy(prcm_mpu_reg_table[i].name, "CM_MPU_DYNAMICDEP");
	prcm_mpu_reg_table[i++].addr = OMAP4430_CM_MPU_DYNAMICDEP;
	strcpy(prcm_mpu_reg_table[i].name, "SCU_CPU_POWER_STATUS");
	prcm_mpu_reg_table[i++].addr = OMAP4430_SCU_CPU_POWER_STATUS;
	strcpy(prcm_mpu_reg_table[i].name, "CM_CLKMODE_DPLL_MPU");
	prcm_mpu_reg_table[i++].addr = OMAP4430_CM_CLKMODE_DPLL_MPU;
	strcpy(prcm_mpu_reg_table[i].name, "CM_IDLEST_DPLL_MPU");
	prcm_mpu_reg_table[i++].addr = OMAP4430_CM_IDLEST_DPLL_MPU;
	strcpy(prcm_mpu_reg_table[i].name, "CM_AUTOIDLE_DPLL_MPU");
	prcm_mpu_reg_table[i++].addr = OMAP4430_CM_AUTOIDLE_DPLL_MPU;
	strcpy(prcm_mpu_reg_table[i].name, "PRM_IRQSTATUS_MPU_A9");
	prcm_mpu_reg_table[i++].addr = OMAP4430_PRM_IRQSTATUS_MPU;
	strcpy(prcm_mpu_reg_table[i].name, "PRM_IRQSTATUS_MPU_A9_2");
	prcm_mpu_reg_table[i++].addr = OMAP4430_PRM_IRQSTATUS_MPU_2;
	strcpy(prcm_mpu_reg_table[i].name, "PRM_IRQENABLE_MPU_A9");
	prcm_mpu_reg_table[i++].addr = OMAP4430_PRM_IRQENABLE_MPU;
	strcpy(prcm_mpu_reg_table[i].name, "PRM_IRQENABLE_MPU_A9_2");
	prcm_mpu_reg_table[i++].addr = OMAP4430_PRM_IRQENABLE_MPU_2;
	strcpy(prcm_mpu_reg_table[i].name, "END");
	prcm_mpu_reg_table[i].addr = 0;

	/* ES2.0 updates */
	if ((cpu_is_omap4430() && (cpu_revision_get() != REV_ES1_0))
		|| cpu_is_omap4460() || cpu_is_omap4470()) {
		strcpy(omap44xx_prm_irq_names[22], "VC_CORE_VPACK");
		strcpy(omap44xx_prm_irq_names[7], "RESERVED");
		strcpy(omap44xx_prm_irq_names[5], "RESERVED");
	}

	init_done = 1;
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mpu44xx_name2addr
 * @BRIEF		retrieve physical address of a register, given its name.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		name: register name
 * @param[in, out]	addr: register address
 * @DESCRIPTION		retrieve physical address of a register, given its name.
 *//*------------------------------------------------------------------------ */
int mpu44xx_name2addr(char *name, unsigned int *addr)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		mpu44xx_regtable_init();

	return name2addr(name, addr, prcm_mpu_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mpu44xx_config_show
 * @BRIEF		analyze MPU power configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		stream: output file stream
 * @DESCRIPTION		analyze MPU power configuration
 *//*------------------------------------------------------------------------ */
int mpu44xx_config_show(FILE *stream)
{
	unsigned int pm_pda_cpu0_pwrstctrl;
	unsigned int pm_pda_cpu0_pwrstst;
	unsigned int rm_pda_cpu0_context;
	unsigned int cm_pda_cpu0_clkctrl;
	unsigned int cm_pda_cpu0_clkstctrl;
	unsigned int pm_pda_cpu1_pwrstctrl;
	unsigned int pm_pda_cpu1_pwrstst;
	unsigned int rm_pda_cpu1_context;
	unsigned int cm_pda_cpu1_clkctrl;
	unsigned int cm_pda_cpu1_clkstctrl;
	unsigned int scu_cpu_power_status;
	char s0[32], s1[32];
	unsigned int cm_clkmode_dpll_mpu;
	unsigned int cm_idlest_dpll_mpu;
	unsigned int cm_autoidle_dpll_mpu;
	omap4_dpll_params dpll_mpu_params;
	unsigned int pm_pwstctrl;
	unsigned int pm_pwstst;
	unsigned int cm_clkstctrl;
	unsigned int rm_context;
	unsigned int cm_clkctrl;
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		mpu44xx_regtable_init();

	if (mem_read(OMAP4430_PM_PDA_CPU0_PWRSTCTRL,
		&pm_pda_cpu0_pwrstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_PM_PDA_CPU0_PWRSTST, &pm_pda_cpu0_pwrstst) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_PDA_CPU0_CPU0_CONTEXT,
		&rm_pda_cpu0_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_CM_PDA_CPU0_CPU0_CLKCTRL,
		&cm_pda_cpu0_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_CM_PDA_CPU0_CLKSTCTRL,
		&cm_pda_cpu0_clkstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_PM_PDA_CPU1_PWRSTCTRL,
		&pm_pda_cpu1_pwrstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_PM_PDA_CPU1_PWRSTST,
		&pm_pda_cpu1_pwrstst) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_PDA_CPU1_CPU1_CONTEXT,
		&rm_pda_cpu1_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_CM_PDA_CPU1_CPU1_CLKCTRL,
		&cm_pda_cpu1_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_CM_PDA_CPU1_CLKSTCTRL,
		&cm_pda_cpu1_clkstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_SCU_CPU_POWER_STATUS,
		&scu_cpu_power_status) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_CM_CLKMODE_DPLL_MPU,
		&cm_clkmode_dpll_mpu) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_CM_IDLEST_DPLL_MPU,
		&cm_idlest_dpll_mpu) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_CM_AUTOIDLE_DPLL_MPU,
		&cm_autoidle_dpll_mpu) != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	ret = dpll44xx_dpll_params_get(DPLL44XX_MPU,
		&dpll_mpu_params, 0);
	if (ret < 0)
		return ret;

	/* MPU LPRM config */
	fprintf(stream, "|----------------------------------------------------"
		"----|\n");
	fprintf(stream, "| %-30s | %-9s | %-9s |\n", "MPU LPRM Configuration",
		"CPU0",	"CPU1");
	fprintf(stream, "|--------------------------------|-----------|-------"
		"----|\n");
	pwrdm_state2string(s0,
		(pwrdm_state) extract_bitfield(pm_pda_cpu0_pwrstst, 0, 2));
	pwrdm_state2string(s1,
		(pwrdm_state) extract_bitfield(pm_pda_cpu1_pwrstst, 0, 2));
	fprintf(stream, "| %-30s | %-9s | %-9s |\n", "Current Power State",
		s0, s1);
	fprintf(stream, "| %-30s | %-9s | %-9s |\n", "Current Logic State",
		((extract_bit(pm_pda_cpu0_pwrstst, 2) == 1) ? "ON" : "OFF"),
		((extract_bit(pm_pda_cpu1_pwrstst, 2) == 1) ? "ON" : "OFF"));
	pwrdm_state2string(s0,
		(pwrdm_state) extract_bitfield(pm_pda_cpu0_pwrstst, 4, 2));
	pwrdm_state2string(s1,
		(pwrdm_state) extract_bitfield(pm_pda_cpu1_pwrstst, 4, 2));
	fprintf(stream, "| %-30s | %-9s | %-9s |\n",
		"Current L1$ State", s0, s1);
	pwrdm_state2string(s0,
		(pwrdm_state)extract_bitfield(pm_pda_cpu0_pwrstctrl, 0, 2));
	pwrdm_state2string(s1,
		(pwrdm_state) extract_bitfield(pm_pda_cpu1_pwrstctrl, 0, 2));
	fprintf(stream, "| %-30s | %-9s | %-9s |\n",
		"Standby Status",
		((extract_bit(cm_pda_cpu0_clkctrl, 0) == 1) ?
			"STANDBY" : "RUNNING"),
		((extract_bit(cm_pda_cpu1_clkctrl, 0) == 1) ?
			"STANDBY" : "RUNNING"));
	fprintf(stream, "| %-30s | %-9s | %-9s |\n", "", "", "");
	fprintf(stream, "| %-30s | %-9s | %-9s |\n", "Target Power State",
		s0, s1);
	fprintf(stream, "| %-30s | %-9s | %-9s |\n",
		"Logic State When Domain is RET",
		((extract_bit(pm_pda_cpu0_pwrstctrl, 2) == 1) ? "RET" : "OFF"),
		((extract_bit(pm_pda_cpu1_pwrstctrl, 2) == 1) ? "RET" : "OFF"));
	fprintf(stream, "| %-30s | %-9s | %-9s |\n", "Clock Control",
		clkdm_ctrl_mode_name_get((clkdm_ctrl_mode)
			extract_bitfield(cm_pda_cpu0_clkstctrl, 0, 2)),
		clkdm_ctrl_mode_name_get((clkdm_ctrl_mode)
			extract_bitfield(cm_pda_cpu1_clkstctrl, 0, 2)));
	fprintf(stream, "| %-30s | %-9s | %-9s |\n", "", "", "");
	if ((cpu_is_omap4430() && (cpu_revision_get() != REV_ES1_0)) ||
		cpu_is_omap4460() || cpu_is_omap4470()) {
		pwrdm_state2string(s0, (pwrdm_state)
			extract_bitfield(pm_pda_cpu0_pwrstst, 24, 2));
		pwrdm_state2string(s1, (pwrdm_state)
			extract_bitfield(pm_pda_cpu1_pwrstst, 24, 2));
		fprintf(stream, "| %-30s | %-9s | %-9s |\n", "Last Power State",
			s0, s1);
	}
	fprintf(stream, "| %-30s | %-9s | %-9s |\n", "Last L1$ Context",
		((extract_bit(rm_pda_cpu0_context, 8) == 1) ?
			"LOST" : "RETAINED"),
		((extract_bit(rm_pda_cpu1_context, 8) == 1) ?
			"LOST" : "RETAINED"));
	fprintf(stream, "| %-30s | %-9s | %-9s |\n", "Last CPU Context",
		((extract_bit(rm_pda_cpu0_context, 0) == 1) ?
			"LOST" : "RETAINED"),
		((extract_bit(rm_pda_cpu1_context, 0) == 1) ?
			"LOST" : "RETAINED"));
	fprintf(stream, "|----------------------------------------------------"
		"----|\n");
	fprintf(stream, "\n");

	/* SCU Configuration */
	fprintf(stream, "|----------------------------------------------------"
	"----|\n");
	fprintf(stream, "| %-30s | %-9s | %-9s |\n",
		"SCU Configuration", "CPU0", "CPU1");
	fprintf(stream, "|--------------------------------|-----------|-------"
		"----|\n");
	OMAPCONF_SCU_CPU_POWER_STATUS_2_STRING(s0,
		extract_bitfield(scu_cpu_power_status, 0, 2));
	OMAPCONF_SCU_CPU_POWER_STATUS_2_STRING(s1,
		extract_bitfield(scu_cpu_power_status, 8, 2));
	fprintf(stream, "| %-30s | %-9s | %-9s |\n", "CPU Power Status",
		s0, s1);
	fprintf(stream, "|---------------------------------------------------"
		"-----|\n");
	fprintf(stream, "\n");

	/* MPU Power Domain Configuration */
	if (mem_read(OMAP4430_PM_MPU_PWRSTCTRL, &pm_pwstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_PM_MPU_PWRSTST, &pm_pwstst) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = pwrdm44xx_config_show(stream, "MPU",
		OMAP4430_PM_MPU_PWRSTCTRL, pm_pwstctrl,
		OMAP4430_PM_MPU_PWRSTST, pm_pwstst);
	if (ret != 0)
		return ret;

	/* MPU Clock Domain Configuration */
	if (mem_read(OMAP4430_CM_MPU_CLKSTCTRL, &cm_clkstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = clkdm44xx_config_show(stream, "MPU",
		OMAP4430_CM_MPU_CLKSTCTRL, cm_clkstctrl);
	if (ret != 0)
		return ret;

	/* MPU Module Power Configuration */
	if (mem_read(OMAP4430_CM_MPU_MPU_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_MPU_MPU_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "MPU",
		OMAP4430_CM_MPU_MPU_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_MPU_MPU_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	/* MPU DPLL Configuration */
	fprintf(stream, "|----------------------------------------------------"
		"----|\n");
	fprintf(stream, "| MPU DPLL Configuration                             "
		"    |\n");
	fprintf(stream, "|--------------------------------|-------------------"
		"----|\n");
	fprintf(stream, "| %-30s | %-21s |\n", "Status",
		dpll_status_name_get((dpll_status) dpll_mpu_params.status));
	sprintf(s0, "%d", (unsigned int) dpll_mpu_params.M2_speed);
	fprintf(stream, "| %-30s | %-21s |\n", "Clock Speed (MHz)", s0);
	fprintf(stream, "| %-30s | %-21s |\n", "Mode",
		dpll_mode_name_get((dpll_mode) dpll_mpu_params.mode));
	fprintf(stream, "| %-30s | %-21s |\n", "Low-Power Mode",
		(dpll_mpu_params.lpmode == 1) ? "Enabled" : "Disabled");
	fprintf(stream, "| %-30s | %-21s |\n", "Autoidle Mode",
		dpll_autoidle_mode_name_get((dpll_autoidle_mode)
			dpll_mpu_params.autoidle_mode));
	fprintf(stream, "| %-30s | %-21s |\n", "M2 Output Autogating",
		(dpll_mpu_params.M2_autogating == 1) ? "Enabled" : "Disabled");
	fprintf(stream, "|----------------------------------------------------"
		"----|\n");
	fprintf(stream, "\nNB: type \"omapconf dplls cfg\" "
		"for detailed DPLL configuration.\n\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mpu44xx_dependency_show
 * @BRIEF		analyse MPU dependency configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		stream: output file stream
 * @DESCRIPTION		analyse MPU dependency configuration
 *//*------------------------------------------------------------------------ */
int mpu44xx_dependency_show(FILE *stream)
{
	unsigned int cm_mpu_staticdep;
	unsigned int cm_mpu_dynamicdep;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		mpu44xx_regtable_init();

	if (mem_read(OMAP4430_CM_MPU_STATICDEP, &cm_mpu_staticdep) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_CM_MPU_DYNAMICDEP, &cm_mpu_dynamicdep) != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	fprintf(stream,
		"|--------------------------------------------------------|\n");
	fprintf(stream,
		"| MPU Domain Dependency Configuration | Static | Dynamic |\n");
	fprintf(stream,
		"|-------------------------------------|------------------|\n");
	fprintf(stream,
		"| %-35s | %-6s | %-7s |\n", "MPU_M3",
		((extract_bit(cm_mpu_staticdep, 0) == 1) ? "En" : "Dis"),
		((extract_bit(cm_mpu_dynamicdep, 0) == 1) ? "En" : "Dis"));
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "DSP",
		((extract_bit(cm_mpu_staticdep, 1) == 1) ? "En" : "Dis"),
		((extract_bit(cm_mpu_dynamicdep, 1) == 1) ? "En" : "Dis"));
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "IVAHD",
		((extract_bit(cm_mpu_staticdep, 2) == 1) ? "En" : "Dis"),
		((extract_bit(cm_mpu_dynamicdep, 2) == 1) ? "En" : "Dis"));
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "ABE",
		((extract_bit(cm_mpu_staticdep, 3) == 1) ? "En" : "Dis"),
		"En");
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "MEM IF",
		((extract_bit(cm_mpu_staticdep, 4) == 1) ? "En" : "Dis"),
		"En");
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "L3_1",
		((extract_bit(cm_mpu_staticdep, 5) == 1) ? "En" : "Dis"),
		((extract_bit(cm_mpu_dynamicdep, 5) == 1) ? "En" : "Dis"));
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "L3_2",
		((extract_bit(cm_mpu_staticdep, 6) == 1) ? "En" : "Dis"),
		((extract_bit(cm_mpu_dynamicdep, 6) == 1) ? "En" : "Dis"));
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "L3INIT",
		((extract_bit(cm_mpu_staticdep, 7) == 1) ? "En" : "Dis"),
		((extract_bit(cm_mpu_dynamicdep, 7) == 1) ? "En" : "Dis"));
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "DSS",
		((extract_bit(cm_mpu_staticdep, 8) == 1) ? "En" : "Dis"),
		((extract_bit(cm_mpu_dynamicdep, 8) == 1) ? "En" : "Dis"));
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "ISS",
		((extract_bit(cm_mpu_staticdep, 9) == 1) ? "En" : "Dis"),
		((extract_bit(cm_mpu_dynamicdep, 9) == 1) ? "En" : "Dis"));
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "GFX",
		((extract_bit(cm_mpu_staticdep, 10) == 1) ? "En" : "Dis"),
		((extract_bit(cm_mpu_dynamicdep, 10) == 1) ? "En" : "Dis"));
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "SDMA",
		"Dis",
		((extract_bit(cm_mpu_dynamicdep, 11) == 1) ? "En" : "Dis"));
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "L4CFG",
		((extract_bit(cm_mpu_staticdep, 12) == 1) ? "En" : "Dis"),
		((extract_bit(cm_mpu_dynamicdep, 12) == 1) ? "En" : "Dis"));
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "L4PER",
		((extract_bit(cm_mpu_staticdep, 13) == 1) ? "En" : "Dis"),
		((extract_bit(cm_mpu_dynamicdep, 13) == 1) ? "En" : "Dis"));
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "L4SEC",
		((extract_bit(cm_mpu_staticdep, 14) == 1) ? "En" : "Dis"),
		((extract_bit(cm_mpu_dynamicdep, 14) == 1) ? "En" : "Dis"));
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "L4WKUP",
		((extract_bit(cm_mpu_staticdep, 15) == 1) ? "En" : "Dis"),
		((extract_bit(cm_mpu_dynamicdep, 15) == 1) ? "En" : "Dis"));
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "ALWONCORE",
		"Dis",
		((extract_bit(cm_mpu_dynamicdep, 16) == 1) ? "En" : "Dis"));
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "CEFUSE",
		"Dis",
		((extract_bit(cm_mpu_dynamicdep, 17) == 1) ? "En" : "Dis"));
	fprintf(stream, "| %-35s | %-6s | %-7s |\n", "C2C",
		"Dis",
		((extract_bit(cm_mpu_dynamicdep, 18) == 1) ? "En" : "Dis"));
	fprintf(stream,
		"|--------------------------------------------------------|\n");
	fprintf(stream,
		"| %-44s | %-7d |\n", "Window Size",
		extract_bitfield(cm_mpu_dynamicdep, 24, 4));
	fprintf(stream,
		"|--------------------------------------------------------|\n");

	fprintf(stream, "\n");
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mpu44xx_irq_show
 * @BRIEF		analyse MPU PRM IRQ configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]
 * @DESCRIPTION		analyse MPU PRM IRQ configuration
 *//*------------------------------------------------------------------------ */
int mpu44xx_irq_show(FILE *stream)
{
	unsigned int prm_irqstatus_mpu;
	unsigned int prm_irqstatus_mpu_2;
	unsigned int prm_irqenable_mpu;
	unsigned int prm_irqenable_mpu_2;
	int ret = 0;
	unsigned short i;
	char mode[8], status[8];

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		mpu44xx_regtable_init();

	ret += mem_read(OMAP4430_PRM_IRQSTATUS_MPU, &prm_irqstatus_mpu);
	ret += mem_read(OMAP4430_PRM_IRQSTATUS_MPU_2, &prm_irqstatus_mpu_2);
	ret += mem_read(OMAP4430_PRM_IRQENABLE_MPU, &prm_irqenable_mpu);
	ret += mem_read(OMAP4430_PRM_IRQENABLE_MPU_2, &prm_irqenable_mpu_2);
	if (ret != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	dprintf("OMAP4430_PRM_IRQSTATUS_MPU = 0x%x\n", prm_irqstatus_mpu);
	dprintf("OMAP4430_PRM_IRQSTATUS_MPU_2 = 0x%x\n", prm_irqstatus_mpu_2);
	dprintf("OMAP4430_PRM_IRQENABLE_MPU = 0x%x\n", prm_irqenable_mpu);
	dprintf("OMAP4430_PRM_IRQENABLE_MPU_2 = 0x%x\n", prm_irqenable_mpu_2);

	fprintf(stream, "|------------------------------------------------|\n");
	fprintf(stream, "| MPU PRM IRQ Configuration                      |\n");
	fprintf(stream, "|------------------------------------------------|\n");
	fprintf(stream, "| PRM IRQ Name               | Mode    | Status  |\n");
	fprintf(stream, "|------------------------------------------------|\n");
	for (i = 0; i < 32; i++) {
		if (strcmp("RESERVED", omap44xx_prm_irq_names[i]) != 0) {
			OMAPCONF_COND_STRCPY(extract_bit(prm_irqstatus_mpu,
				i) == 1, status, "Pending", "");
			OMAPCONF_COND_STRCPY(extract_bit(prm_irqenable_mpu,
				i) == 1, mode, "Enabled", "Masked");
			fprintf(stream, "| (%2d) %-21s | %-7s | %-7s |\n", i,
				omap44xx_prm_irq_names[i],
				mode,
				status);
		}
	}
	for (i = 32; i < OMAP44XX_PRM_IRQ_MAX_NBR; i++) {
		if (strcmp("RESERVED", omap44xx_prm_irq_names[i]) != 0) {
			OMAPCONF_COND_STRCPY(extract_bit(prm_irqstatus_mpu_2,
				i - 32) == 1, status, "Pending", "");
			OMAPCONF_COND_STRCPY(extract_bit(prm_irqenable_mpu_2,
				i - 32) == 1, mode, "Enabled", "Masked");
			fprintf(stream, "| (%2d) %-21s | %-7s | %-7s |\n", i,
				omap44xx_prm_irq_names[i],
				mode,
				status);
		}
	}
	fprintf(stream,
		"|------------------------------------------------|\n\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mpu44xx_dump
 * @BRIEF		dump PRCM MPU registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		dump PRCM MPU registers
 *//*------------------------------------------------------------------------ */
int mpu44xx_dump(void)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		mpu44xx_regtable_init();

	return dumpregs(prcm_mpu_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mpu44xx_main
 * @BRIEF		PRCM MPU main menu
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		PRCM MPU main menu
 *//*------------------------------------------------------------------------ */
int mpu44xx_main(int argc, char *argv[])
{
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (argc == 2) {
		if (!init_done)
			mpu44xx_regtable_init();
		if (strcmp(argv[1], "dump") == 0) {
			ret = dumpregs(prcm_mpu_reg_table);
		} else if (strcmp(argv[1], "cfg") == 0) {
			ret = mpu44xx_config_show(stdout);
		} else if (strcmp(argv[1], "dep") == 0) {
			ret = mpu44xx_dependency_show(stdout);
		} else if (strcmp(argv[1], "irq") == 0) {
			ret = mpu44xx_irq_show(stdout);
		} else {
			help(HELP_PRCM);
			ret = OMAPCONF_ERR_ARG;
		}
	} else {
		help(HELP_PRCM);
		ret = OMAPCONF_ERR_ARG;
	}

	return ret;
}
