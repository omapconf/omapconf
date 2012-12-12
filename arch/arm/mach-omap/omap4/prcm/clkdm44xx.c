/*
 *
 * @Component			OMAPCONF
 * @Filename			clkdm44xx.c
 * @Description			OMAP4 Clock Domain Definitions & Functions
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


#include <lib.h>
#include <clockdomain.h>
#include <clkdm44xx.h>
#include <cm44xx.h>
#include <prm44xx.h>
#include <string.h>
#include <stdio.h>
#include <cpuinfo.h>
#include <reg.h>
#include <mem.h>


/* #define CLKDM44XX_DEBUG */
#ifdef CLKDM44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

static const char
	clkdm44xx_name_table[OMAP4_CD_ID_MAX][CLKDM44XX_MAX_NAME_LENGTH] = {
	"L4WKUP",
	"EMU",
	"MPU",
	"ABE",
	"IVAHD",
	"DSP",
	"ALWONCORE",
	"L4CFG",
	"C2C",
	"SDMA",
	"MPU_M3",
	"L3_1",
	"L3_2",
	"L3INSTR",
	"MEMIF",
	"STD_EFUSE",
	"CUST_EFUSE",
	"CAM",
	"DSS",
	"GFX",
	"L3INIT",
	"L4SEC",
	"L4PER",
	"NONE (PRCM)"};


static const pwrdm44xx_id clkdm44xx_partition_table[OMAP4_CD_ID_MAX] = {
	OMAP4_PD_WKUP,
	OMAP4_PD_EMU,
	OMAP4_PD_MPU,
	OMAP4_PD_ABE,
	OMAP4_PD_IVA_HD,
	OMAP4_PD_DSP,
	OMAP4_PD_ALWON_CORE,
	OMAP4_PD_CORE,
	OMAP4_PD_CORE,
	OMAP4_PD_CORE,
	OMAP4_PD_CORE,
	OMAP4_PD_CORE,
	OMAP4_PD_CORE,
	OMAP4_PD_CORE,
	OMAP4_PD_CORE,
	OMAP4_PD_STD_EFUSE,
	OMAP4_PD_CUST_EFUSE,
	OMAP4_PD_CAM,
	OMAP4_PD_DSS,
	OMAP4_PD_GFX,
	OMAP4_PD_L3_INIT,
	OMAP4_PD_L4_PER,
	OMAP4_PD_L4_PER};


static const unsigned int *
	clkdm44xx_cm_clkstctrl_addr_table[OMAP4_CD_ID_MAX] = {
	(unsigned int *) OMAP4430_CM_WKUP_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_EMU_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_MPU_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM1_ABE_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_IVAHD_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_DSP_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_ALWON_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_L4CFG_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_C2C_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_SDMA_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_MPU_M3_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_L3_1_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_L3_2_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_L3INSTR_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_MEMIF_CLKSTCTRL,
	NULL,
	(unsigned int *) OMAP4430_CM_CEFUSE_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_CAM_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_DSS_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_GFX_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_L3INIT_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_L4SEC_CLKSTCTRL,
	(unsigned int *) OMAP4430_CM_L4PER_CLKSTCTRL,
	NULL};


static unsigned short clkdm44xx_init_done = 0;
genlist clkdm44xx_list;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm44xx_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void clkdm44xx_init(void)
{
	clockdm_info clkdm;

	if (clkdm44xx_init_done)
		return;

	genlist_init(&clkdm44xx_list);

	/* FIXME */
	clkdm = clkdm;

	clkdm44xx_init_done = 1;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm44xx_deinit
 * @BRIEF		free dynamically allocated internal data.
 * @DESCRIPTION		free dynamically allocated internal data.
 *			MUST BE CALLED AT END OF EXECUTION.
 *//*------------------------------------------------------------------------ */
void clkdm44xx_deinit(void)
{
	if (clkdm44xx_init_done) {
		genlist_free(&clkdm44xx_list);
		clkdm44xx_init_done = 0;

	}
	dprintf("%s(): deinit done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm44xx_list_get
 * @BRIEF		return the list of clock domains
 * @RETURNS		list of clock domains in case of success
 *			NULL in case of error
 * @DESCRIPTION		return the list of clock domains
 *//*------------------------------------------------------------------------ */
const genlist *clkdm44xx_list_get(void)
{
	clkdm44xx_init();

	return (const genlist *) &clkdm44xx_list;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm44xx_count_get
 * @BRIEF		return the number of clock domains
 * @RETURNS		number of clock domains (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @DESCRIPTION		return the number of clock domains
 *//*------------------------------------------------------------------------ */
int clkdm44xx_count_get(void)
{
	int count;

	clkdm44xx_init();

	count = genlist_getcount(&clkdm44xx_list);

	dprintf("%s() = %d\n", __func__, count);
	return count;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm44xx_get_name
 * @BRIEF		return clock domain name
 * @RETURNS		clock domain name on success
 *			NULL in case of error
 * @param[in]		id: clock domain ID
 * @param[in,out]	name: clock domain name
 * @DESCRIPTION		return clock domain name
 *//*------------------------------------------------------------------------ */
char *clkdm44xx_get_name(clkdm44xx_id id, char name[CLKDM44XX_MAX_NAME_LENGTH])
{
	if ((id >= OMAP4_CD_ID_MAX) || (name == NULL))
		return NULL;
	else
		strcpy(name, clkdm44xx_name_table[id]);

	return name;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm44xx_get_pwrdm
 * @BRIEF		return the ID of the power domain a given
 *			clock domain is part of.
 * @RETURNS		power domain ID a given clock domain is part of
 *			(< OMAP4_PD_ID_MAX)
 *			OMAP4_PD_ID_MAX in case of error
 * @param[in]		id: clock domain ID
 * @DESCRIPTION		return the ID of the power domain a given
 *			clock domain is part of.
 *//*------------------------------------------------------------------------ */
pwrdm44xx_id clkdm44xx_get_pwrdm(clkdm44xx_id id)
{
	if (id >= OMAP4_CD_ID_MAX) {
		fprintf(stderr, "%s: id >= OMAP4_CD_ID_MAX!!!\n",
			__func__);
		return OMAP4_PD_ID_MAX;
	}

	return clkdm44xx_partition_table[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm44xx_get_voltdm
 * @BRIEF		return the ID of the voltage domain a given clock
 *			domain is part of.
 * @RETURNS		voltage domain ID a given clock domain is part of
 *			(< OMAP4_VD_ID_MAX)
 *			OMAP4_VD_ID_MAX in case of error
 * @param[in]		id: clock domain ID
 * @DESCRIPTION		return the ID of the voltage domain a given clock
 *			domain is part of.
 *//*------------------------------------------------------------------------ */
voltdm44xx_id clkdm44xx_get_voltdm(clkdm44xx_id id)
{
	return pwrdm44xx_get_voltdm(clkdm44xx_get_pwrdm(id));
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm44xx_get_status
 * @BRIEF		extract clock domain status from register
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 * @param[in]		cd_id: Clock Domain ID (= CLKDM_STATUS_MAX in case of
 *			error)
 * @param[in,out]	clkst: Clock Domain status (must be pre-allocated)
 * @DESCRIPTION		extract clock domain status from register
 *//*------------------------------------------------------------------------ */
int clkdm44xx_get_status(clkdm44xx_id cd_id, clkdm_status *clkst)
{
	unsigned int *cm_clkstctrl_addr;
	unsigned int cm_clkstctrl;

	#ifdef CLKDM44XX_DEBUG
	char clkdm_name[CLKDM44XX_MAX_NAME_LENGTH];
	#endif

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(clkst, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(cd_id, OMAP4_CD_ID_MAX, OMAPCONF_ERR_ARG);
	*clkst = CLKDM_STATUS_MAX;


	/* Retrieve registers address */
	cm_clkstctrl_addr = (unsigned int *)
		clkdm44xx_cm_clkstctrl_addr_table[cd_id];
	if (cm_clkstctrl_addr == NULL) {
		dprintf(
			"%s(%u (%s)): no CM_xyz_CLKSTCTRL register, return CLKDM_RUNNING\n",
			__func__, cd_id,
			clkdm44xx_get_name(cd_id, clkdm_name));
		*clkst = CLKDM_RUNNING;
		return 0;
	}
	if (mem_read((unsigned int) cm_clkstctrl_addr, &cm_clkstctrl) != 0) {
		*clkst = CLKDM_STATUS_MAX;
		return OMAPCONF_ERR_REG_ACCESS;
	}

	*clkst = clkdm_status_get(cm_clkstctrl);
	if (*clkst == CLKDM_STATUS_MAX)
		return OMAPCONF_ERR_ARG;
	else
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

	dprintf("clkdm44xx_config_show(): name=%s\n", name);
	dprintf("clkdm44xx_config_show(): cm_clkstctrl_addr=0x%08X\n",
		cm_clkstctrl_addr);
	dprintf("clkdm44xx_config_show(): cm_clkstctrl=0x%08X\n\n",
		cm_clkstctrl);


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
