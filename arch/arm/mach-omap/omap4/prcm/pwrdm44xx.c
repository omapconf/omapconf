/*
 *
 * @Component			OMAPCONF
 * @Filename			pwrdm44xx.c
 * @Description			OMAP4 Power Domain Definitions & Functions
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


#include <pwrdm44xx.h>
#include <lib.h>
#include <mem.h>
#include <string.h>
#include <prm44xx.h>
#include <clock44xx.h>
#include <string.h>
#include <stdio.h>
#include <cpuinfo.h>


/* #define PWRDM44XX_DEBUG */
#ifdef PWRDM44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


const char pwrdm44xx_name_table[OMAP4_PD_ID_MAX][PWRDM44XX_MAX_NAME_LENGTH] = {
	"WKUP",
	"EMU",
	"MPU",
	"ALWON_MPU",
	"ABE",
	"IVAHD",
	"DSP",
	"ALWON_IVA",
	"ALWON_CORE",
	"CORE",
	"STD_EFUSE",
	"CUST_EFUSE",
	"CAM",
	"DSS",
	"GFX",
	"L3INIT",
	"L4PER"};

static const voltdm44xx_id pwrdm44xx_partition_table[OMAP4_PD_ID_MAX] = {
	OMAP4_LDO_WKUP,
	OMAP4_LDO_WKUP,
	OMAP4_VDD_MPU,
	OMAP4_VDD_MPU,
	OMAP4_VDD_IVA,
	OMAP4_VDD_IVA,
	OMAP4_VDD_IVA,
	OMAP4_VDD_IVA,
	OMAP4_VDD_CORE,
	OMAP4_VDD_CORE,
	OMAP4_VDD_CORE,
	OMAP4_VDD_CORE,
	OMAP4_VDD_CORE,
	OMAP4_VDD_CORE,
	OMAP4_VDD_CORE,
	OMAP4_VDD_CORE,
	OMAP4_VDD_CORE};


static unsigned short pwrdm44xx_init_done = 0;
genlist pwrdm44xx_list;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm44xx_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void pwrdm44xx_init(void)
{
	powerdm_info pwrdm;

	if (pwrdm44xx_init_done)
		return;

	genlist_init(&pwrdm44xx_list);

	/* FIXME */
	pwrdm = pwrdm;

	pwrdm44xx_init_done = 1;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm44xx_deinit
 * @BRIEF		free dynamically allocated internal data.
 * @DESCRIPTION		free dynamically allocated internal data.
 *			MUST BE CALLED AT END OF EXECUTION.
 *//*------------------------------------------------------------------------ */
void pwrdm44xx_deinit(void)
{
	if (pwrdm44xx_init_done) {
		genlist_free(&pwrdm44xx_list);
		pwrdm44xx_init_done = 0;

	}
	dprintf("%s(): deinit done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm44xx_list_get
 * @BRIEF		return the list of power domains
 * @RETURNS		list of power domains in case of success
 *			NULL in case of error
 * @DESCRIPTION		return the list of power domains
 *//*------------------------------------------------------------------------ */
const genlist *pwrdm44xx_list_get(void)
{
	pwrdm44xx_init();

	return (const genlist *) &pwrdm44xx_list;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm44xx_count_get
 * @BRIEF		return the number of power domains
 * @RETURNS		number of power domains (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @DESCRIPTION		return the number of power domains
 *//*------------------------------------------------------------------------ */
int pwrdm44xx_count_get(void)
{
	int count;

	pwrdm44xx_init();

	count = genlist_getcount(&pwrdm44xx_list);

	dprintf("%s() = %d\n", __func__, count);
	return count;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm44xx_get_name
 * @BRIEF		return power domain name
 * @RETURNS		power domain name on success
 *			NULL in case of error
 * @param[in]		id: power domain ID
 * @param[in,out]	name: power domain name
 * @DESCRIPTION		return power domain name
 *//*------------------------------------------------------------------------ */
char *pwrdm44xx_get_name(pwrdm44xx_id id, char name[PWRDM44XX_MAX_NAME_LENGTH])
{
	if ((id >= OMAP4_PD_ID_MAX) || (name == NULL))
		return NULL;
	else
		strcpy(name, pwrdm44xx_name_table[id]);

	return name;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm44xx_get_voltdm
 * @BRIEF		return the ID of the voltage domain a given power domain
 *			is part of.
 * @RETURNS		voltage domain ID a given power domain is part of
 *			(< OMAP4_VD_ID_MAX)
 *			OMAP4_VD_ID_MAX in case of error
 * @param[in]		id: power domain ID
 * @DESCRIPTION		return the ID of the voltage domain a given power domain
 *			is part of.
 *//*------------------------------------------------------------------------ */
voltdm44xx_id pwrdm44xx_get_voltdm(pwrdm44xx_id id)
{
	if (id >= OMAP4_PD_ID_MAX) {
		fprintf(stderr, "%s: id >= OMAP4_PD_ID_MAX!!!\n",
			__func__);
		return OMAP4_VD_ID_MAX;
	}

	return pwrdm44xx_partition_table[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm44xx_get_state
 * @BRIEF		extract current power domain state from register
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in]		pd_id: domain name (MPU, CORE, PER, ...)
 * @param[in,out]	state: current power domain state (returned)
 * @DESCRIPTION		extract current power domain state from register
 *//*------------------------------------------------------------------------ */
int pwrdm44xx_get_state(pwrdm44xx_id pd_id,
	pwrdm_state *state)
{
	unsigned int pm_pwrstst_addr, pwrstst;
	#ifdef PWRDM44XX_DEBUG
	char pwrdm_name[PWRDM44XX_MAX_NAME_LENGTH];
	#endif

	if (state == NULL)
		return OMAPCONF_ERR_ARG;


	/* Retrieve registers address */
	switch (pd_id) {
	case OMAP4_PD_ABE:
		pm_pwrstst_addr = OMAP4430_PM_ABE_PWRSTST;
		break;
	case OMAP4_PD_IVA_HD:
		pm_pwrstst_addr = OMAP4430_PM_IVAHD_PWRSTST;
		break;
	case OMAP4_PD_DSP:
		pm_pwrstst_addr = OMAP4430_PM_DSP_PWRSTST;
		break;
	case OMAP4_PD_CAM:
		pm_pwrstst_addr = OMAP4430_PM_CAM_PWRSTST;
		break;
	case OMAP4_PD_DSS:
		pm_pwrstst_addr = OMAP4430_PM_DSS_PWRSTST;
		break;
	case OMAP4_PD_GFX:
		pm_pwrstst_addr = OMAP4430_PM_GFX_PWRSTST;
		break;

	case OMAP4_PD_WKUP:
	case OMAP4_PD_EMU:
	case OMAP4_PD_ALWON_MPU:
	case OMAP4_PD_STD_EFUSE:
	case OMAP4_PD_CUST_EFUSE:
	case OMAP4_PD_ALWON_IVA:
	case OMAP4_PD_ALWON_CORE:
		/* ALWAYS ON domains */
		*state = PWRDM_ON_STATE;
		return 0;

	case OMAP4_PD_MPU:
		pm_pwrstst_addr = OMAP4430_PM_MPU_PWRSTST;
		break;
	case OMAP4_PD_CORE:
		pm_pwrstst_addr = OMAP4430_PM_CORE_PWRSTST;
		break;
	case OMAP4_PD_L3_INIT:
		pm_pwrstst_addr = OMAP4430_PM_L3INIT_PWRSTST;
		break;
	case OMAP4_PD_L4_PER:
		pm_pwrstst_addr = OMAP4430_PM_L4PER_PWRSTST;
		break;
	default:
		dprintf("pwrdm44xx_get_state(): "
			"called with incorrect power domain ID (%s)\n",
			pwrdm44xx_get_name(pd_id, pwrdm_name));
		return OMAPCONF_ERR_ARG;
	}

	/* Retrieve registers content */
	mem_read(pm_pwrstst_addr, &pwrstst);

	dprintf("pwrdm44xx_get_state(): "
		"Domain is %s pm_pwrstst_addr = 0x%08X pwrstst = 0x%08X\n",
		pwrdm44xx_get_name(pd_id, pwrdm_name),
		pm_pwrstst_addr, pwrstst);

	/* Retrieve power domain current state */
	*state = (pwrdm_state) extract_bitfield(pwrstst, 0, 2);

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

