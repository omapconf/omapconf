/*
 *
 * @Component			OMAPCONF
 * @Filename			dpll44xx.c
 * @Description			OMAP4 DPLL PRCM Definitions & Functions
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
#include <dpll44xx-data.h>
#include <dpll.h>
#include <autoadjust_table.h>
#include <lib.h>
#include <mem.h>
#include <help.h>
#include <cpuinfo.h>


/*
#define DPLL44XX_DPLL_PARAMS_GET_DEBUG
#define DPLL44XX_PARAMS_GET_DEBUG
#define DPLL44XX_HS_DIVIDER_PARAMS_GET_DEBUG
#define DPLL44XX_MN_PARAMS_GET_DEBUG
#define DPLL44XX_SPEEDS_GET_DEBUG
#define DPLL44XX_CONFIG_SHOW_DEBUG
*/
#ifdef DPLL44XX_CONFIG_SHOW_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


#define DPLL44XX_AUDIT_SHOW_STATUS(curr, golden) \
		if (curr == golden) { \
			snprintf(table[row++][3], TABLE_MAX_ELT_LEN, "Pass"); \
		} else { \
			snprintf(table[row++][3], TABLE_MAX_ELT_LEN, "FAIL"); \
			(*err_nbr)++; \
		}

#define DPLL44XX_AUDIT_CHECK_GOLDEN_SETTING(setting, defval, gotolabel) \
		if (setting == defval) {\
			/* Golden setting not available */\
			snprintf(table[row][2], TABLE_MAX_ELT_LEN,\
				"Not available");\
			snprintf(table[row][3], TABLE_MAX_ELT_LEN, "warn.");\
			(*wng_nbr)++;\
			row++;\
			goto gotolabel;\
		}


static int dpll44xx_MN_params_get(dpll44xx_id dpll_id,
	omap4_dpll_MN_params *dpll_MN_params);
static int dpll44xx_SSC_params_get(dpll44xx_id dpll_id,
	omap4_dpll_SSC_params *dpll_SSC_params);
static int dpll44xx_hs_divider_params_get(dpll44xx_id dpll_id,
	omap4_dpll_hs_divider_params dpll_hs_divider_params[4]);
static int dpll44xx_speeds_get(omap4_dpll_params *dpll_params,
	unsigned short ignore_stop_status);


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll44xx_name2addr
 * @BRIEF		retrieve physical address of a register, given its name.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		name: register name
 * @param[in]		addr: register address
 * @DESCRIPTION		retrieve physical address of a register, given its name.
 *//*------------------------------------------------------------------------ */
int dpll44xx_name2addr(char *name, unsigned int *addr)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	dpll44xx_init_regtable();

	return name2addr(name, addr, dpll44xx_prcm_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll44xx_dump
 * @BRIEF		dump PLLs PRCM registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		dump PLLs PRCM registers
 *//*------------------------------------------------------------------------ */
int dpll44xx_dump(void)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	dpll44xx_init_regtable();

	return dumpregs(dpll44xx_prcm_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll44xx_name_get
 * @BRIEF		return DPLL name.
 * @RETURNS		DPLL name on success
 *			"FIXME" string in case of error
 * @param[in]		id: DPLL ID
 * @DESCRIPTION		return DPLL name.
 *//*------------------------------------------------------------------------ */
const char *dpll44xx_name_get(dpll44xx_id id)
{
	if (id < DPLL44XX_ID_MAX)
		return dpll44xx_names[id];
	else
		return dpll44xx_names[DPLL44XX_ID_MAX];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll44xx_output_name_get
 * @BRIEF		return DPLL output name.
 * @RETURNS		DPLL name on success
 *			"FIXME" string in case of error
 * @param[in]		id: DPLL output ID
 * @DESCRIPTION		return DPLL output name.
 *//*------------------------------------------------------------------------ */
const char *dpll44xx_output_name_get(dpll44xx_output_id id)
{
	if (id < DPLL44XX_OUTPUT_ID_MAX)
		return dpll44xx_output_names[id];
	else
		return dpll44xx_output_names[DPLL44XX_OUTPUT_ID_MAX];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll44xx_dcc_count2us
 * @BRIEF		convert DCC COUNT MAX RAW value into micro-seconds
 * @RETURNS		DCC COUNT value into micro-seconds
 *			-1 in case of error.
 * @param[in]		dcc_count: DCC COUNT MAX RAW value
 * @DESCRIPTION		convert DCC COUNT MAX RAW value into micro-seconds
 *//*------------------------------------------------------------------------ */
double dpll44xx_dcc_count2us(unsigned int dcc_count)
{
	return 32 * dcc_count / clk44xx_get_clock_speed(OMAP4_L4_ICLK1, 0);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll44xx_MN_params_get
 * @BRIEF		get M/N parameters and compute the output speed
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		dpll_id: DPLL ID
 * @param[in,out]	dpll_MN_params: pre-allocated structure where to store
 *			DPLL parameters
 * @DESCRIPTION		get M/N parameters and compute the output speed
 *//*------------------------------------------------------------------------ */
static int dpll44xx_MN_params_get(dpll44xx_id dpll_id,
	omap4_dpll_MN_params *dpll_MN_params)
{
	unsigned int cm_clksel_dpll, cm_div_m2_dpll, cm_div_m3_dpll;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (dpll_id >= DPLL44XX_ID_MAX)
		return OMAPCONF_ERR_ARG;

	if (dpll_MN_params == NULL) {
		fprintf(stderr, "omapconf internal error: "
			"dpll44xx_MN_params_get() called with "
			"NULL pointer!\n");
		return OMAPCONF_ERR_ARG;
	}

	#ifdef DPLL44XX_MN_PARAMS_GET_DEBUG
	printf("dpll44xx_MN_params_get(): dpll_id = %d\n", dpll_id);
	#endif

	if (mem_read(omap4_dpll_MN_regs[dpll_id].cm_clksel_dpll,
		&cm_clksel_dpll) < 0)
		return OMAPCONF_ERR_REG_ACCESS;
	dpll_MN_params->M = extract_bitfield(cm_clksel_dpll, 8, 11);
	dpll_MN_params->N = extract_bitfield(cm_clksel_dpll, 0, 7);


	if (omap4_dpll_MN_regs[dpll_id].cm_div_m2_dpll != 0) {
		if (mem_read(omap4_dpll_MN_regs[dpll_id].cm_div_m2_dpll,
			&cm_div_m2_dpll) < 0)
			return OMAPCONF_ERR_REG_ACCESS;
		dpll_MN_params->M2 = extract_bitfield(cm_div_m2_dpll, 0, 5);
	} else {
		dpll_MN_params->M2 = 1;
	}

	if (omap4_dpll_MN_regs[dpll_id].cm_div_m3_dpll != 0) {
		if (mem_read(omap4_dpll_MN_regs[dpll_id].cm_div_m3_dpll,
			&cm_div_m3_dpll) < 0)
			return OMAPCONF_ERR_REG_ACCESS;
		dpll_MN_params->M3 = extract_bitfield(cm_div_m3_dpll, 0, 5);
	} else {
		dpll_MN_params->M3 = 1;
	}

	#ifdef DPLL44XX_MN_PARAMS_GET_DEBUG
	printf("dpll44xx_MN_params_get(): DPLL%d\n", dpll_id);
	printf("dpll44xx_MN_params_get(): "
		"cm_clksel_dpll addr = 0x%08X, cm_clksel_dpll = 0x%08X\n",
		omap4_dpll_MN_regs[dpll_id].cm_clksel_dpll, cm_clksel_dpll);
	printf("dpll44xx_MN_params_get(): "
		"cm_div_m2_dpll addr = 0x%08X, cm_div_m2_dpll = 0x%08X\n",
		omap4_dpll_MN_regs[dpll_id].cm_div_m2_dpll, cm_div_m2_dpll);
	printf("dpll44xx_MN_params_get(): "
		"cm_div_m3_dpll addr = 0x%08X, cm_div_m3_dpll = 0x%08X\n",
		omap4_dpll_MN_regs[dpll_id].cm_div_m3_dpll, cm_div_m3_dpll);
	printf("dpll44xx_MN_params_get(): M = %d\n", dpll_MN_params->M);
	printf("dpll44xx_MN_params_get(): N = %d\n", dpll_MN_params->N);
	printf("dpll44xx_MN_params_get(): M2 = %d\n", dpll_MN_params->M2);
	printf("dpll44xx_MN_params_get(): M3 = %d\n", dpll_MN_params->M3);
	#endif

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll44xx_SSC_params_get
 * @BRIEF		extract SSC parameters from DPLL registers
 * @RETURNS		0
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		dpll_id: ID of the DPLL to get parameters
 * @param[in,out]	dpll_SSC_params: pre-allocated structure where to store
 *			parameters
 * @DESCRIPTION		extract SSC parameters from DPLL registers
 *			and store it into structure.
 *//*------------------------------------------------------------------------ */
static int dpll44xx_SSC_params_get(dpll44xx_id dpll_id,
	omap4_dpll_SSC_params *dpll_SSC_params)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(dpll_id, DPLL44XX_ID_MAX, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(dpll_SSC_params, OMAPCONF_ERR_ARG);

	/* FIXME: implement function */
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll44xx_hs_divider_params_get
 * @BRIEF		extract HS divider parameters from DPLL registers
 * @RETURNS		0
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		dpll_id: ID of the DPLL to get parameters
 * @param[in]		dpll_hs_divider_params: pre-allocated structure to store
 *			parameters
 * @DESCRIPTION		extract HS divider parameters from DPLL registers
 *			and store it into structure.
 *//*------------------------------------------------------------------------ */
static int dpll44xx_hs_divider_params_get(dpll44xx_id dpll_id,
	omap4_dpll_hs_divider_params dpll_hs_divider_params[4])
{
	int ret = 0;
	unsigned int cm_div_m_dpll = 0;
	unsigned short i = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(dpll_id, DPLL44XX_ID_MAX, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(dpll_hs_divider_params, ret);

	#ifdef DPLL44XX_HS_DIVIDER_PARAMS_GET_DEBUG
	printf("%s(): dpll_id = %d\n", __func__, dpll_id);
	#endif

	for (i = 0; i < 4; i++) {
		#ifdef DPLL44XX_HS_DIVIDER_PARAMS_GET_DEBUG
		printf("%s(): omap4_dpll_hs_divider_regs[%d][0] = 0x%X\n",
			__func__, dpll_id,
			omap4_dpll_hs_divider_regs[dpll_id][i]);
		#endif

		if (omap4_dpll_hs_divider_regs[dpll_id][i] != 0) {
			ret = mem_read(omap4_dpll_hs_divider_regs[dpll_id][i],
				&cm_div_m_dpll);
			if (ret < 0)
				return OMAPCONF_ERR_REG_ACCESS;
			dpll_hs_divider_params[i].present = 1;
			dpll_hs_divider_params[i].pwdn =
				extract_bit(cm_div_m_dpll, 12);
			dpll_hs_divider_params[i].status =
				extract_bit(cm_div_m_dpll, 9);
			dpll_hs_divider_params[i].autogating =
				!extract_bit(cm_div_m_dpll, 8);
			dpll_hs_divider_params[i].div =
				extract_bitfield(cm_div_m_dpll, 0, 5);
		} else {
			dpll_hs_divider_params[i].present = 0;
		}

		#ifdef DPLL44XX_HS_DIVIDER_PARAMS_GET_DEBUG
		if (dpll_hs_divider_params[i].present) {
			printf("CM_DIV_M%d_DPLL = 0x%08X\n",
				4 + i, cm_div_m_dpll);
			printf("DPLL%d_M%d.pwdn = %d\n",
				dpll_id, 4 + i,
				dpll_hs_divider_params[i].pwdn);
			printf("DPLL%d_M%d.status = %d\n",
				dpll_id, 4 + i,
				dpll_hs_divider_params[i].status);
			printf("DPLL%d_M%d.autogating = %d\n",
				dpll_id, 4 + i,
				dpll_hs_divider_params[i].autogating);
			printf("DPLL%d_M%d.div = %d\n",
				dpll_id, 4 + i, dpll_hs_divider_params[i].div);
		} else
			printf("DPLL%d_M%d not present\n", dpll_id, 4 + i);
		#endif
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll44xx_dpll_params_get
 * @BRIEF		extract parameters from DPLL registers
 * @RETURNS		0
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		dpll_id: ID of the DPLL to get parameters
 * @param[in,out]	dpll_params: pre-allocated structure where to store
 *			parameters
 * @param[in]		ignore_stop_status: do not consider DPLL STOP status.
 *			Useful for functions that needs the DPLL output
 *			frequencies even when DPLL is stopped
 *			(e.g. audit, clock tree, OPP detection, etc)
 * @DESCRIPTION		extract parameters from DPLL registers
 *			and store it into structure.
 *//*------------------------------------------------------------------------ */
int dpll44xx_dpll_params_get(dpll44xx_id dpll_id,
	omap4_dpll_params *dpll_params, unsigned short ignore_stop_status)
{
	int ret = 0;
	unsigned int cm_clkmode_dpll = 0;
	unsigned int cm_autoidle_dpll = 0;
	unsigned int cm_clksel_dpll = 0;
	unsigned int cm_div_m2_dpll = 0;
	unsigned int cm_div_m3_dpll = 0;
	unsigned int cm_idlest_dpll = 0;
	unsigned int cm_bypclk_dpll = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(dpll_id, DPLL44XX_ID_MAX, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(dpll_params, OMAPCONF_ERR_ARG);

	dpll_params->id = dpll_id;
	#ifdef DPLL44XX_DPLL_PARAMS_GET_DEBUG
	printf("%s(): DPLL is %s\n", __func__,
		dpll44xx_names[dpll_params->id]);
	printf("%s(): omap4_dpll_regs[%s].cm_clkmode_dpll = 0x%X\n", __func__,
		dpll44xx_names[dpll_id],
		omap4_dpll_regs[dpll_id].cm_clkmode_dpll);
	printf("%s(): omap4_dpll_regs[%s].cm_autoidle_dpll = 0x%X\n", __func__,
		dpll44xx_names[dpll_id],
		omap4_dpll_regs[dpll_id].cm_autoidle_dpll);
	printf("%s(): omap4_dpll_regs[%s].cm_clksel_dpll = 0x%X\n", __func__,
		dpll44xx_names[dpll_id],
		omap4_dpll_regs[dpll_id].cm_clksel_dpll);
	printf("%s(): omap4_dpll_regs[%s].cm_bypclk_dpll = 0x%X\n", __func__,
		dpll44xx_names[dpll_id],
		omap4_dpll_regs[dpll_id].cm_bypclk_dpll);
	printf("%s(): omap4_dpll_regs[%s].cm_div_m2_dpll = 0x%X\n", __func__,
		dpll44xx_names[dpll_id],
		omap4_dpll_regs[dpll_id].cm_div_m2_dpll);
	printf("%s(): omap4_dpll_regs[%s].cm_div_m3_dpll = 0x%X\n", __func__,
		dpll44xx_names[dpll_id],
		omap4_dpll_regs[dpll_id].cm_div_m3_dpll);
	printf("%s(): omap4_dpll_regs[%s].cm_idlest_dpll = 0x%X\n", __func__,
		dpll44xx_names[dpll_id],
		omap4_dpll_regs[dpll_id].cm_idlest_dpll);
	#endif

	if (omap4_dpll_regs[dpll_id].cm_clkmode_dpll != 0) {
		ret = mem_read(omap4_dpll_regs[dpll_id].cm_clkmode_dpll,
			&cm_clkmode_dpll);
		if (ret < 0)
			return OMAPCONF_ERR_REG_ACCESS;
	}
	if (omap4_dpll_regs[dpll_id].cm_autoidle_dpll != 0) {
		ret = mem_read(omap4_dpll_regs[dpll_id].cm_autoidle_dpll,
			&cm_autoidle_dpll);
		if (ret < 0)
			return OMAPCONF_ERR_REG_ACCESS;
	}
	if (omap4_dpll_regs[dpll_id].cm_clksel_dpll != 0) {
		ret = mem_read(omap4_dpll_regs[dpll_id].cm_clksel_dpll,
			&cm_clksel_dpll);
		if (ret < 0)
			return OMAPCONF_ERR_REG_ACCESS;
	}
	if (omap4_dpll_regs[dpll_id].cm_bypclk_dpll != 0) {
		ret = mem_read(omap4_dpll_regs[dpll_id].cm_bypclk_dpll,
			&cm_bypclk_dpll);
		if (ret < 0)
			return OMAPCONF_ERR_REG_ACCESS;
	}
	if (omap4_dpll_regs[dpll_id].cm_div_m2_dpll != 0) {
		ret = mem_read(omap4_dpll_regs[dpll_id].cm_div_m2_dpll,
			&cm_div_m2_dpll);
		if (ret < 0)
			return OMAPCONF_ERR_REG_ACCESS;
		dpll_params->M2_present = 1;
	} else
		dpll_params->M2_present = 0;

	switch (dpll_id) {
	case DPLL44XX_MPU:
		if (!cpu_is_omap4430()) {
			/*
			 * In case of OMAP4460 and beyond,
			 * X2_M3 output is used for frequencies > 1GHz.
			 * But there is no CM_DIV_M3_DPLL_MPU register,
			 * divider is hard-coded to 1.
			 * Need to emulate register.
			 */
			dpll_params->M3_present = 1;
			cm_div_m3_dpll = 0x00000201;
		} else {
			dpll_params->M3_present = 0;
		}
		break;
	default:
		if (omap4_dpll_regs[dpll_id].cm_div_m3_dpll != 0) {
			ret = mem_read(omap4_dpll_regs[dpll_id].cm_div_m3_dpll,
				&cm_div_m3_dpll);
			if (ret < 0)
				return OMAPCONF_ERR_REG_ACCESS;
			dpll_params->M3_present = 1;
		} else {
			dpll_params->M3_present = 0;
		}
	}

	if (omap4_dpll_regs[dpll_id].cm_idlest_dpll != 0) {
		ret = mem_read(omap4_dpll_regs[dpll_id].cm_idlest_dpll,
			&cm_idlest_dpll);
		if (ret < 0)
			return OMAPCONF_ERR_REG_ACCESS;
	}

	dpll_params->lpmode = extract_bit(cm_clkmode_dpll, 10);
	dpll_params->relock_ramp_en = extract_bit(cm_clkmode_dpll, 9);
	dpll_params->driftguard_en = extract_bit(cm_clkmode_dpll, 8);
	dpll_params->ramp_time = 1 << (extract_bitfield(cm_clkmode_dpll,
		5, 3) + 1);
	dpll_params->ramp_level = extract_bitfield(cm_clkmode_dpll, 3, 2);
	dpll_params->mode = extract_bitfield(cm_clkmode_dpll, 0, 3);
	dpll_params->regm4xen = extract_bit(cm_clkmode_dpll, 11);
	dpll_params->autoidle_mode = extract_bitfield(cm_autoidle_dpll, 0, 3);

	switch (cm_idlest_dpll) {
	case 0x000:
		/*
		 * DPLL is either in bypass or in stop mode
		 * Must also read DPLL mode and autoidle mode
		 * to determine status.
		 */
		switch (dpll_params->mode) {
		case DPLL_LOW_POWER_STOP:
		case DPLL_FAST_RELOCK_STOP:
			dpll_params->status = DPLL_STATUS_STOPPED;
			break;
		case DPLL_LOW_POWER_BYPASS:
		case DPLL_FAST_RELOCK_BYPASS:
		case DPLL_MN_BYPASS:
			dpll_params->status = DPLL_STATUS_BYPASSED;
			break;
		case DPLL_LOCK:
			/* need to check autoidle mode */
			switch (dpll_params->autoidle_mode) {
			case DPLL_AUTO_LOW_POWER_STOP:
			case DPLL_AUTO_FAST_RELOCK_STOP:
				dpll_params->status = DPLL_STATUS_STOPPED;
				break;
			case DPLL_AUTO_BYPASS_LOW_POWER:
			case DPLL_AUTO_BYPASS_FAST_RELOCK:
				dpll_params->status = DPLL_STATUS_BYPASSED;
				break;
			case DPLL_DISABLED:
			default:
				/* can't happen ... */
				return OMAPCONF_ERR_INTERNAL;
			}
			break;
		default:
			/* can't happen ... */
			return OMAPCONF_ERR_INTERNAL;
		}
		break;
	case 0x001:
		/* DPLL is LOCKED */
		dpll_params->status = DPLL_STATUS_LOCKED;
		break;
	case 0x100:
		/* DPLL is MN BYPASSED */
		dpll_params->status = DPLL_STATUS_BYPASSED;
		break;
	case 0x101:
		/* impossible for DPLL to be LOCKED and MN BYPASSED */
		return OMAPCONF_ERR_INTERNAL;
	default:
		/* unexpected value */
		return OMAPCONF_ERR_UNEXPECTED;
	}

	if (!cpu_is_omap4430() && (dpll_id == DPLL44XX_MPU)) {
		dpll_params->dcc_en = extract_bit(cm_clksel_dpll, 22);
		dpll_params->dcc_count =
			extract_bitfield(cm_clksel_dpll, 24, 8);
	} else {
		dpll_params->dcc_en = 0;
		dpll_params->dcc_count = 0;
	}
	dpll_params->bypass_clk = extract_bit(cm_clksel_dpll, 23);
	dpll_params->clkouthif_src = extract_bit(cm_clksel_dpll, 20);

	if (dpll_params->M2_present) {
		dpll_params->M2_clkout_st = extract_bit(cm_div_m2_dpll, 9);
		dpll_params->M2_autogating = !extract_bit(cm_div_m2_dpll, 8);
		dpll_params->X2_M2_clkout_st = extract_bit(cm_div_m2_dpll, 11);
		dpll_params->X2_M2_autogating =
			!extract_bit(cm_div_m2_dpll, 10);
	}

	if (dpll_params->M3_present) {
		dpll_params->X2_M3_clkout_st = extract_bit(cm_div_m3_dpll, 9);
		dpll_params->X2_M3_autogating = !extract_bit(cm_div_m3_dpll, 8);
	}

	if (omap4_dpll_regs[dpll_id].cm_bypclk_dpll != 0)
		dpll_params->bypass_clk_div = 1 <<
				extract_bitfield(cm_bypclk_dpll, 0, 2);
	else
		dpll_params->bypass_clk_div = 1;

	#ifdef DPLL44XX_PARAMS_GET_DEBUG
	printf("%s(): %s cm_clkmode_dpll = 0x%08X\n", __func__,
		dpll44xx_names[dpll_id], cm_clkmode_dpll);
	printf("%s(): %s dpll_params->lpmode = %d\n", __func__,
		dpll44xx_names[dpll_id], dpll_params->lpmode);
	printf("%s(): %s dpll_params->relock_ramp_en = %d\n", __func__,
		dpll44xx_names[dpll_id], dpll_params->relock_ramp_en);
	printf("%s(): %s dpll_params->driftguard_en = %d\n", __func__,
		dpll44xx_names[dpll_id], dpll_params->driftguard_en);
	printf("%s(): %s dpll_params->ramp_time = %d\n", __func__,
		dpll44xx_names[dpll_id], dpll_params->ramp_time);
	printf("%s(): %s dpll_params->ramp_level = %d\n", __func__,
		dpll44xx_names[dpll_id], dpll_params->ramp_level);
	printf("%s(): %s dpll_params->mode = %d\n", __func__,
		dpll44xx_names[dpll_id], dpll_params->mode);
	printf("%s(): %s dpll_params->regm4xen = %d\n", __func__,
		dpll44xx_names[dpll_id], dpll_params->regm4xen);

	printf("%s(): %s cm_autoidle_dpll = 0x%08X\n", __func__,
		dpll44xx_names[dpll_id], cm_autoidle_dpll);
	printf("%s(): %s dpll_params->autoidle_mode = %d\n", __func__,
		dpll44xx_names[dpll_id], dpll_params->autoidle_mode);

	printf("%s(): %s cm_clksel_dpll = 0x%08X\n", __func__,
		dpll44xx_names[dpll_id], cm_clksel_dpll);
	printf("%s(): %s dpll_params->bypass_clk = %d\n", __func__,
		dpll44xx_names[dpll_id], dpll_params->bypass_clk);
	printf("%s(): %s dpll_params->clkouthif_src = %d\n", __func__,
		dpll44xx_names[dpll_id], dpll_params->clkouthif_src);
	printf("%s(): %s dpll_params->dcc_en = %d\n", __func__,
		dpll44xx_names[dpll_id], dpll_params->dcc_en);
	printf("%s(): %s dpll_params->dcc_count = %d\n", __func__,
		dpll44xx_names[dpll_id], dpll_params->dcc_count);

	if (dpll_params->M2_present) {
		printf("%s(): %s cm_div_m2_dpll = 0x%08X\n", __func__,
			dpll44xx_names[dpll_id], cm_div_m2_dpll);
		printf("%s(): %s dpll_params->M2_clkout_st = %d\n", __func__,
			dpll44xx_names[dpll_id], dpll_params->M2_clkout_st);
		printf("%s(): %s dpll_params->M2_autogating = %d\n", __func__,
			dpll44xx_names[dpll_id], dpll_params->M2_autogating);
		printf("%s(): %s dpll_params->X2_M2_clkout_st = %d\n", __func__,
			dpll44xx_names[dpll_id],
			dpll_params->X2_M2_clkout_st);
		printf("%s(): %s dpll_params->X2_M2_autogating = %d\n",
			__func__, dpll44xx_names[dpll_id],
			dpll_params->X2_M2_autogating);
	} else {
		printf("%s(): %s cm_div_m2_dpll does not exist\n",
			__func__, dpll44xx_names[dpll_id]);
	}

	if (dpll_params->M3_present) {
		printf("%s(): %s cm_div_m3_dpll = 0x%08X\n", __func__,
			dpll44xx_names[dpll_id], cm_div_m3_dpll);
		printf("%s(): %s dpll_params->X2_M3_clkout_st = %d\n", __func__,
			dpll44xx_names[dpll_id],
			dpll_params->X2_M3_clkout_st);
		printf("%s(): %s dpll_params->X2_M3_autogating = %d\n",
			__func__, dpll44xx_names[dpll_id],
			dpll_params->X2_M3_autogating);
	} else {
		printf("%s(): %s cm_div_m3_dpll does not exist\n",
			__func__, dpll44xx_names[dpll_id]);
	}

	printf("%s(): %s cm_idlest_dpll = 0x%08X\n", __func__,
		dpll44xx_names[dpll_id], cm_idlest_dpll);
	printf("%s(): %s dpll_params->status = %d\n", __func__,
		dpll44xx_names[dpll_id], dpll_params->status);

	printf("%s(): %s cm_bypclk_dpll = 0x%08X\n", __func__,
		dpll44xx_names[dpll_id], cm_bypclk_dpll);
	printf("%s(): %s dpll_params->bypass_clk_div = %d\n", __func__,
		dpll44xx_names[dpll_id], dpll_params->bypass_clk_div);
	#endif

	ret = dpll44xx_MN_params_get(dpll_id, &(dpll_params->MN_params));
	ret = dpll44xx_SSC_params_get(dpll_id,
		&(dpll_params->SSC_params));
	ret = dpll44xx_hs_divider_params_get(dpll_id, dpll_params->HS_M);
	ret = dpll44xx_speeds_get(dpll_params, ignore_stop_status);

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll44xx_speeds_get
 * @BRIEF		compute DPLL output speeds in MHz
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_INTERNAL
 * @param[in,out]	dpll_params: pre-allocated structure where to store DPLL
 *			parameters
 * @param[in]		ignore_stop_status: do not consider DPLL STOP status.
 *			Useful for functions that needs the DPLL output
 *			frequencies even when DPLL is stopped
 *			(e.g. audit, clock tree, OPP detection, etc)
 * @DESCRIPTION		compute DPLL output speeds in MHz
 *//*------------------------------------------------------------------------ */
static int dpll44xx_speeds_get(omap4_dpll_params *dpll_params,
	unsigned short ignore_stop_status)
{
	dpll_status dpll_status;
	#ifdef DPLL44XX_SPEEDS_GET_DEBUG
	char name[CLOCK44XX_MAX_NAME_LENGTH];
	#endif

	CHECK_NULL_ARG(dpll_params, OMAPCONF_ERR_ARG);

	dpll_params->M2_speed = 0.0;
	dpll_params->X2_M2_speed = 0.0;
	dpll_params->X2_M3_speed = 0.0;
	dpll_params->X2_M4_speed = 0.0;
	dpll_params->X2_M5_speed = 0.0;
	dpll_params->X2_M6_speed = 0.0;
	dpll_params->X2_M7_speed = 0.0;

	/* Retrieve DPLL input clocks speed */
	if (omap4_dpll_sources[dpll_params->id].ref_clk != OMAP4_CLOCK_ID_MAX)
		dpll_params->fref = clk44xx_get_clock_speed(
			omap4_dpll_sources[dpll_params->id].ref_clk,
			ignore_stop_status);
	if (omap4_dpll_sources[dpll_params->id].byp_clk_m2 !=
		OMAP4_CLOCK_ID_MAX)
		dpll_params->fbyp_clk_m2 = clk44xx_get_clock_speed(
			omap4_dpll_sources[dpll_params->id].byp_clk_m2,
			ignore_stop_status);
	if (omap4_dpll_sources[dpll_params->id].byp_clk_m3 !=
		OMAP4_CLOCK_ID_MAX)
		dpll_params->fbyp_clk_m3 = clk44xx_get_clock_speed(
			omap4_dpll_sources[dpll_params->id].byp_clk_m3,
			ignore_stop_status);
	if (omap4_dpll_sources[dpll_params->id].byp_clk_mx !=
		OMAP4_CLOCK_ID_MAX)
		dpll_params->fbyp_clk_mx = clk44xx_get_clock_speed(
			omap4_dpll_sources[dpll_params->id].byp_clk_mx,
			ignore_stop_status);

	#ifdef DPLL44XX_SPEEDS_GET_DEBUG
	printf("%s(): %s REF_CLK = %lf (source is %s)\n", __func__,
		dpll44xx_names[dpll_params->id],
		dpll_params->fref, clk44xx_get_name(omap4_dpll_sources[
			dpll_params->id].ref_clk, name));
	if (omap4_dpll_sources[dpll_params->id].byp_clk_m2 !=
		OMAP4_CLOCK_ID_MAX)
		printf("%s(): %s BP Clk M2 = %lf (source is %s)\n", __func__,
			dpll44xx_names[dpll_params->id],
			dpll_params->fbyp_clk_m2,
			clk44xx_get_name(omap4_dpll_sources[
				dpll_params->id].byp_clk_m2, name));
	if (omap4_dpll_sources[dpll_params->id].byp_clk_m3 !=
		OMAP4_CLOCK_ID_MAX)
		printf("%s(): %s BP Clk M3 = %lf (source is %s)\n", __func__,
			dpll44xx_names[dpll_params->id],
			dpll_params->fbyp_clk_m3,
			clk44xx_get_name(omap4_dpll_sources[
				dpll_params->id].byp_clk_m3, name));
	if (omap4_dpll_sources[dpll_params->id].byp_clk_mx !=
		OMAP4_CLOCK_ID_MAX)
		printf("%s(): %s BP Clk Mx = %lf (source is %s)\n", __func__,
			dpll44xx_names[dpll_params->id],
			dpll_params->fbyp_clk_mx,
			clk44xx_get_name(omap4_dpll_sources[
				dpll_params->id].byp_clk_mx, name));
	#endif

	/* Determine DPLL output frequency */
	if ((dpll_params->status == DPLL_STATUS_STOPPED) &&
		(ignore_stop_status))
		dpll_status = DPLL_STATUS_LOCKED;
	else
		dpll_status = dpll_params->status;

	switch (dpll_status) {
	case DPLL_STATUS_BYPASSED:
		dpll_params->fdpll = 0.0;

		if (dpll_params->M2_present) {
			dpll_params->X2_M2_speed = dpll_params->fbyp_clk_m2;
			dpll_params->M2_speed = dpll_params->fbyp_clk_m2;
		}

		if (dpll_params->M3_present)
			dpll_params->X2_M3_speed = dpll_params->fbyp_clk_m3 /
			(double) dpll_params->MN_params.M3;

		if (dpll_params->HS_M[0].present)
			dpll_params->X2_M4_speed = dpll_params->fbyp_clk_mx;

		if (dpll_params->HS_M[1].present)
			dpll_params->X2_M5_speed = dpll_params->fbyp_clk_mx;

		if (dpll_params->HS_M[2].present)
			dpll_params->X2_M6_speed = dpll_params->fbyp_clk_mx;

		if (dpll_params->HS_M[3].present)
			dpll_params->X2_M7_speed = dpll_params->fbyp_clk_mx;
		break;

	case DPLL_STATUS_LOCKED:
		if (dpll_params->id <= DPLL44XX_ABE) {
			if (dpll_params->regm4xen == 0)
				dpll_params->fdpll = (dpll_params->fref * 2.0 *
					(dpll_params->MN_params.M)) /
					((dpll_params->MN_params.N) + 1);
			else
				dpll_params->fdpll = (dpll_params->fref * 8.0 *
					(dpll_params->MN_params.M)) /
					((dpll_params->MN_params.N) + 1);
			if (dpll_params->M2_present) {
				dpll_params->X2_M2_speed = dpll_params->fdpll /
					(double) dpll_params->MN_params.M2;
				dpll_params->M2_speed =
					dpll_params->X2_M2_speed / 2.0;
			}
		} else {
			dpll_params->fdpll = (dpll_params->fref *
				(dpll_params->MN_params.M)) /
				((dpll_params->MN_params.N) + 1);
			/* clkdcoldo */
			dpll_params->X2_M2_speed = dpll_params->fdpll;
			/* clkout */
			dpll_params->M2_speed = dpll_params->fdpll /
				(double) dpll_params->MN_params.M2;
		}


		if (dpll_params->M3_present)
			dpll_params->X2_M3_speed = dpll_params->fdpll /
			(double) dpll_params->MN_params.M3;

		if (dpll_params->HS_M[0].present)
			dpll_params->X2_M4_speed = dpll_params->fdpll /
			(double) dpll_params->HS_M[0].div;

		if (dpll_params->HS_M[1].present)
			dpll_params->X2_M5_speed = dpll_params->fdpll /
			(double) dpll_params->HS_M[1].div;

		if (dpll_params->HS_M[2].present)
			dpll_params->X2_M6_speed = dpll_params->fdpll /
			(double) dpll_params->HS_M[2].div;

		if (dpll_params->HS_M[3].present)
			dpll_params->X2_M7_speed = dpll_params->fdpll /
			(double) dpll_params->HS_M[3].div;
		break;

	case DPLL_STATUS_STOPPED:
		dpll_params->fdpll = 0.0;
		/* all output speeds already set to 0.0 */
		break;

	default:
		return OMAPCONF_ERR_INTERNAL;
	}


	#ifdef DPLL44XX_SPEEDS_GET_DEBUG
	printf("%s(): %s Fref = %lf KHz\n", __func__,
		dpll44xx_names[dpll_params->id], dpll_params->fref);
	printf("%s(): %s Fdpll = %lf MHz\n", __func__,
		dpll44xx_names[dpll_params->id], dpll_params->fdpll);
	printf("%s(): %s M2_speed = %lf MHz\n", __func__,
		dpll44xx_names[dpll_params->id], dpll_params->M2_speed);
	printf("%s(): %s X2_M2_speed = %lf MHz\n", __func__,
		dpll44xx_names[dpll_params->id], dpll_params->X2_M2_speed);
	printf("%s(): %s X2_M3_speed = %lf MHz\n", __func__,
		dpll44xx_names[dpll_params->id], dpll_params->X2_M3_speed);
	printf("%s(): %s X2_M4_speed = %lf MHz\n", __func__,
		dpll44xx_names[dpll_params->id], dpll_params->X2_M4_speed);
	printf("%s(): %s X2_M5_speed = %lf MHz\n", __func__,
		dpll44xx_names[dpll_params->id], dpll_params->X2_M5_speed);
	printf("%s(): %s X2_M6_speed = %lf MHz\n", __func__,
		dpll44xx_names[dpll_params->id], dpll_params->X2_M6_speed);
	printf("%s(): %s X2_M7_speed = %lf MHz\n", __func__,
		dpll44xx_names[dpll_params->id], dpll_params->X2_M7_speed);
	#endif

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll44xx_config_show
 * @BRIEF		analyze PLLs configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in, out]	stream: output file
 * @DESCRIPTION		analyze PLLs configuration
 *//*------------------------------------------------------------------------ */
int dpll44xx_config_show(FILE *stream)
{
	int ret = 0;
	double val, val2;
	omap4_dpll_params dpll_params, dpll_params_locked;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row, row_max;
	dpll44xx_id dpll_id;
	unsigned int hsdiv_count;

	autoadjust_table_init(table);
	row = 0;
	row_max = 0;
	strncpy(table[row][0], "DPLL Configuration", TABLE_MAX_ELT_LEN);

	for (dpll_id = DPLL44XX_MPU; dpll_id <= DPLL44XX_USB; dpll_id++) {
		row = 0;
		snprintf(table[row++][dpll_id + 1], TABLE_MAX_ELT_LEN, "%s",
			dpll44xx_name_get(dpll_id));
		ret = dpll44xx_dpll_params_get(dpll_id, &dpll_params, 0);
		if (ret < 0) {
			dprintf("%s(): error while getting DPLL %d "
				"parameters! (%d)", __func__, dpll_id, ret);
			break;
		}

		/*
		 * Also get DPLL params ignoring DPLL STOPPED status to also
		 * show all output speeds when DPLL is locked.
		 * No need to check return value as it just already returned ok.
		 */
		dpll44xx_dpll_params_get(dpll_id, &dpll_params_locked, 1);

		strncpy(table[row][0], "Status", TABLE_MAX_ELT_LEN);
		strncpy(table[row][dpll_id + 1],
			dpll_status_name_get((dpll_status) dpll_params.status),
			TABLE_MAX_ELT_LEN);
		row += 2;

		strncpy(table[row][0], "Mode", TABLE_MAX_ELT_LEN);
		strncpy(table[row++][dpll_id + 1],
			dpll_mode_name_get((dpll_mode) dpll_params.mode),
			TABLE_MAX_ELT_LEN);

		strncpy(table[row][0], "Automatic Control", TABLE_MAX_ELT_LEN);
		strncpy(table[row++][dpll_id + 1],
			dpll_autoidle_mode_name_get(
				(dpll_autoidle_mode) dpll_params.autoidle_mode),
			TABLE_MAX_ELT_LEN);

		strncpy(table[row++][0], " LPST = Low-Power STop",
			TABLE_MAX_ELT_LEN);
		strncpy(table[row++][0], " FRST = Fast-Relock STop",
			TABLE_MAX_ELT_LEN);
		strncpy(table[row++][0], " LPBP = Low-Power ByPass",
			TABLE_MAX_ELT_LEN);
		strncpy(table[row++][0], " FRBP = Fast-Relock ByPass",
			TABLE_MAX_ELT_LEN);
		strncpy(table[row++][0], " MNBP = MN ByPass",
			TABLE_MAX_ELT_LEN);

		strncpy(table[row][0], "Low-Power Mode", TABLE_MAX_ELT_LEN);
		strncpy(table[row][dpll_id + 1],
			(dpll_params.lpmode == 1) ? "Enabled" : "Disabled",
			TABLE_MAX_ELT_LEN);
		row += 2;

		strncpy(table[row][0], "Automatic Recalibration",
			TABLE_MAX_ELT_LEN);
		strncpy(table[row++][dpll_id + 1],
			(dpll_params.driftguard_en == 1) ?
			"Enabled" : "Disabled",	TABLE_MAX_ELT_LEN);

		strncpy(table[row][0], "Clock Ramping during Relock",
				TABLE_MAX_ELT_LEN);
		strncpy(table[row++][dpll_id + 1],
			(dpll_params.relock_ramp_en == 1) ?
			"Enabled" : "Disabled", TABLE_MAX_ELT_LEN);

		strncpy(table[row][0], "Ramping Rate (x REFCLK(s))",
			TABLE_MAX_ELT_LEN);
		snprintf(table[row++][dpll_id + 1], TABLE_MAX_ELT_LEN, "%d",
			dpll_params.ramp_time);

		strncpy(table[row][0], "Ramping Levels", TABLE_MAX_ELT_LEN);
		strncpy(table[row][dpll_id + 1],
			dpll_ramp_level_name_get(
				(dpll_ramp_level) dpll_params.ramp_level),
			TABLE_MAX_ELT_LEN);
		row += 2;

		strncpy(table[row][0], "Bypass Clock", TABLE_MAX_ELT_LEN);
		strncpy(table[row++][dpll_id + 1],
			(dpll_params.bypass_clk == 1) ? "CLKINPULOW" : "CLKINP",
			TABLE_MAX_ELT_LEN);

		strncpy(table[row][0], "Bypass Clock Divider",
			TABLE_MAX_ELT_LEN);
		if (omap4_dpll_regs[dpll_id].cm_bypclk_dpll != 0)
			snprintf(table[row][dpll_id + 1], TABLE_MAX_ELT_LEN,
			"%d", dpll_params.bypass_clk_div);
		row++;

		strncpy(table[row][0], "REGM4XEN Mode",
			TABLE_MAX_ELT_LEN);
		if (dpll_params.regm4xen == 0)
			snprintf(table[row][dpll_id + 1], TABLE_MAX_ELT_LEN,
				"Disabled");
		else
			snprintf(table[row][dpll_id + 1], TABLE_MAX_ELT_LEN,
				"Enabled");
		row++;

		if (!cpu_is_omap4430()) {
			strncpy(table[row][0], "Duty Cycle Correction (DCC)",
				TABLE_MAX_ELT_LEN);
			if (dpll_id == DPLL44XX_MPU) {
				if (dpll_params.dcc_en == 1) {
					val = dpll44xx_dcc_count2us(
						dpll_params.dcc_count);
					snprintf(table[row][dpll_id + 1],
						TABLE_MAX_ELT_LEN,
						"%d (%.1lfus)",
						dpll_params.dcc_count, val);
				} else {
					snprintf(table[row][dpll_id + 1],
						TABLE_MAX_ELT_LEN,
						"Disabled");
				}
			}
			row += 2;
		} else {
			row++;
		}

		strncpy(table[row][0], "M Multiplier Factor",
			TABLE_MAX_ELT_LEN);
		snprintf(table[row++][dpll_id + 1], TABLE_MAX_ELT_LEN, "%d",
			dpll_params.MN_params.M);

		strncpy(table[row][0], "N Divider Factor", TABLE_MAX_ELT_LEN);
		snprintf(table[row++][dpll_id + 1], TABLE_MAX_ELT_LEN, "%d",
			dpll_params.MN_params.N);

		strncpy(table[row][0], "Lock Frequency (MHz)",
			TABLE_MAX_ELT_LEN);
		if (dpll_params.status == DPLL_STATUS_LOCKED)
			snprintf(table[row][dpll_id + 1], TABLE_MAX_ELT_LEN,
			"%d", (unsigned int) dpll_params.fdpll);
		else
			snprintf(table[row][dpll_id + 1], TABLE_MAX_ELT_LEN,
				"%d (%d)",
				(unsigned int) dpll_params.fdpll,
				(unsigned int) dpll_params_locked.fdpll);
		row += 2;

		strncpy(table[row][0], "M2 Output", TABLE_MAX_ELT_LEN);
		row++;
		if ((dpll_params.M2_present) && (dpll_params.dcc_en == 0)) {
			strncpy(table[row][0], "  Status", TABLE_MAX_ELT_LEN);
			strncpy(table[row++][dpll_id + 1],
				(dpll_params.M2_clkout_st == 1) ?
					"Enabled" : "Gated",
					TABLE_MAX_ELT_LEN);
			strncpy(table[row][0], "  Clock Divider",
				TABLE_MAX_ELT_LEN);
			snprintf(table[row++][dpll_id + 1], TABLE_MAX_ELT_LEN,
				"%-5d (x2)", dpll_params.MN_params.M2);
			strncpy(table[row][0], "  Clock Speed (MHz)",
				TABLE_MAX_ELT_LEN);
			if (dpll_params.status == DPLL_STATUS_LOCKED)
				snprintf(table[row++][dpll_id + 1],
					TABLE_MAX_ELT_LEN, "%d",
					(unsigned int) dpll_params.M2_speed);
			else
				snprintf(table[row++][dpll_id + 1],
				TABLE_MAX_ELT_LEN, "%d (%d)",
				(unsigned int) dpll_params.M2_speed,
				(unsigned int) dpll_params_locked.M2_speed);
			strncpy(table[row][0], "  Autogating",
				TABLE_MAX_ELT_LEN);
			strncpy(table[row++][dpll_id + 1],
			(dpll_params.M2_autogating == 1) ?
				"Enabled" : "Disabled",	TABLE_MAX_ELT_LEN);
		} else {
			row += 4;
		}
		row++;

		strncpy(table[row++][0], "X2_M2 Output", TABLE_MAX_ELT_LEN);
		if ((dpll_id != DPLL44XX_MPU) && (dpll_params.M2_present)) {
			strncpy(table[row][0], "  Status", TABLE_MAX_ELT_LEN);
			strncpy(table[row++][dpll_id + 1],
				(dpll_params.X2_M2_clkout_st == 1) ?
					"Enabled" : "Gated",
					TABLE_MAX_ELT_LEN);
			strncpy(table[row][0], "  Clock Divider",
				TABLE_MAX_ELT_LEN);
			snprintf(table[row++][dpll_id + 1], TABLE_MAX_ELT_LEN,
				"%-5d", dpll_params.MN_params.M2);
			strncpy(table[row][0], "  Clock Speed (MHz)",
				TABLE_MAX_ELT_LEN);
			if (dpll_params.status == DPLL_STATUS_LOCKED)
				snprintf(table[row++][dpll_id + 1],
					TABLE_MAX_ELT_LEN, "%d",
					(unsigned int) dpll_params.X2_M2_speed);
			else
				snprintf(table[row++][dpll_id + 1],
					TABLE_MAX_ELT_LEN, "%d (%d)",
					(unsigned int) dpll_params.X2_M2_speed,
					(unsigned int)
						dpll_params_locked.X2_M2_speed);
			strncpy(table[row][0], "  Autogating",
				TABLE_MAX_ELT_LEN);
			strncpy(table[row++][dpll_id + 1],
			(dpll_params.X2_M2_autogating == 1) ?
				"Enabled" : "Disabled",	TABLE_MAX_ELT_LEN);
		} else {
			row += 4;
		}
		row++;

		strncpy(table[row++][0], "X2_M3 Output", TABLE_MAX_ELT_LEN);
		if (((dpll_id != DPLL44XX_MPU) && (dpll_params.M3_present)) ||
			((dpll_id == DPLL44XX_MPU) && (dpll_params.dcc_en == 1))) {
			strncpy(table[row][0], "  Status",
				TABLE_MAX_ELT_LEN);
			strncpy(table[row++][dpll_id + 1],
				(dpll_params.X2_M3_clkout_st == 1) ?
					"Enabled" : "Gated",
					TABLE_MAX_ELT_LEN);
			strncpy(table[row][0], "  Clock Divider",
				TABLE_MAX_ELT_LEN);
			snprintf(table[row++][dpll_id + 1], TABLE_MAX_ELT_LEN,
				"%-5d", dpll_params.MN_params.M3);
			strncpy(table[row][0], "  Clock Speed (MHz)",
				TABLE_MAX_ELT_LEN);
			if (dpll_params.status == DPLL_STATUS_LOCKED)
				snprintf(table[row++][dpll_id + 1],
					TABLE_MAX_ELT_LEN, "%d",
					(unsigned int) dpll_params.X2_M3_speed);
			else
				snprintf(table[row++][dpll_id + 1],
				TABLE_MAX_ELT_LEN, "%d (%d)",
				(unsigned int) dpll_params.X2_M3_speed,
				(unsigned int) dpll_params_locked.X2_M3_speed);
			strncpy(table[row][0], "  Autogating",
				TABLE_MAX_ELT_LEN);
			strncpy(table[row++][dpll_id + 1],
			(dpll_params.X2_M3_autogating == 1) ?
				"Enabled" : "Disabled",
				TABLE_MAX_ELT_LEN);
		} else {
			row += 4;
		}
		row++;


		for (hsdiv_count = 0; hsdiv_count < 4; hsdiv_count++) {
			snprintf(table[row++][0], TABLE_MAX_ELT_LEN,
				"X2_M%d Output", hsdiv_count + 4);

			if (dpll_params.HS_M[hsdiv_count].present) {
				strncpy(table[row][0], "  Status",
					TABLE_MAX_ELT_LEN);
				strncpy(table[row++][dpll_id + 1],
				(dpll_params.HS_M[hsdiv_count].status == 1) ?
					"Enabled" : "Gated", TABLE_MAX_ELT_LEN);
				strncpy(table[row][0], "  Clock Divider",
					TABLE_MAX_ELT_LEN);
				snprintf(table[row++][dpll_id + 1],
					TABLE_MAX_ELT_LEN,
					"%d",
					dpll_params.HS_M[hsdiv_count].div);
				strncpy(table[row][0], "  Clock Speed (MHz)",
					TABLE_MAX_ELT_LEN);
				switch (hsdiv_count) {
				case 0:
					val = dpll_params.X2_M4_speed;
					val2 = dpll_params_locked.X2_M4_speed;
					break;
				case 1:
					val = dpll_params.X2_M5_speed;
					val2 = dpll_params_locked.X2_M5_speed;
					break;
				case 2:
					val = dpll_params.X2_M6_speed;
					val2 = dpll_params_locked.X2_M6_speed;
					break;
				case 3:
					val = dpll_params.X2_M7_speed;
					val2 = dpll_params_locked.X2_M7_speed;
					break;
				default:
					fprintf(stderr,
						"%s(): cannot happen!\n",
						__func__);
				}
				if (dpll_params.status == DPLL_STATUS_LOCKED)
					snprintf(table[row++][dpll_id + 1],
						TABLE_MAX_ELT_LEN, "%d",
						(unsigned int) val);
				else
					snprintf(table[row++][dpll_id + 1],
					TABLE_MAX_ELT_LEN, "%d (%d)",
					(unsigned int) val,
					(unsigned int) val2);
				strncpy(table[row][0], "  Autogating",
					TABLE_MAX_ELT_LEN);
				strncpy(table[row++][dpll_id + 1],
				(dpll_params.HS_M[hsdiv_count].autogating == 1)
					? "Enabled" : "Disabled",
					TABLE_MAX_ELT_LEN);
				if (cpu_is_omap4430()) {
					strncpy(table[row][0],
						"  Auto Power Down",
						TABLE_MAX_ELT_LEN);
					strncpy(table[row++][dpll_id + 1],
						(dpll_params.HS_M[hsdiv_count].pwdn == 1) ?
							"Enabled" : "Disabled",
							TABLE_MAX_ELT_LEN);
				} else {
					strncpy(table[row][0], "  Power Status",
						TABLE_MAX_ELT_LEN);
					strncpy(table[row++][dpll_id + 1],
						(dpll_params.HS_M[hsdiv_count].pwdn == 1) ?
							"Up" : "Down",
							TABLE_MAX_ELT_LEN);
				}
			} else {
				row += 5;
			}
			if (hsdiv_count != 3)
				row++;
		}
		if (row > row_max)
			row_max = row;
	}

	if (stream != NULL)
		autoadjust_table_fprint(stream, table, row_max, 7);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll44xx_ssc_config_show
 * @BRIEF		analyze PLLs Spread Spectrum Clocking configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		none
 * @DESCRIPTION		analyze PLLs Spread Spectrum Clocking configuration
 *//*------------------------------------------------------------------------ */
int dpll44xx_ssc_config_show(void)
{
	/* FIXME: implement function */
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll44xx_audit
 * @BRIEF		OMAP4 DPLLS settings audit.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		dpll_id: ID of the DPLL to be audited
 * @param[in]		opp_id: if != DPLL44XX_ID_MAX, force audit at that OPP
 * @param[in]		stream: output file (NULL: no output (silent))
 * @param[in,out]	err_nbr: audit error number
 * @param[in,out]	wng_nbr: audit warning number
 * @DESCRIPTION		OMAP4 DPLLS settings audit.
 *//*------------------------------------------------------------------------ */
int dpll44xx_audit(dpll44xx_id dpll_id, opp44xx_id opp_id,
	FILE *stream, unsigned int *err_nbr, unsigned int *wng_nbr)
{
	int ret;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row, i;
	dpll44xx_id id;
	double sysclk, rate;
	opp44xx_id opp_mpu, opp_iva, opp_core, opp;
	voltdm44xx_id vdd_id;
	omap4_dpll_params settings;
	dpll44xx_audit_settings *golden_settings;
	static const char s_mode[2][12] = {
		"Disabled",
		"Enabled"};

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(dpll_id, DPLL44XX_ID_MAX + 1, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(opp_id, OPP44XX_ID_MAX + 1, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(err_nbr, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(wng_nbr, OMAPCONF_ERR_ARG);

	dprintf("dpll_id=%s, opp_id=%s\n", dpll44xx_name_get(dpll_id),
		opp44xx_name_get(opp_id, OMAP4_VDD_MPU));

	*err_nbr = 0;
	*wng_nbr = 0;
	sysclk = clk44xx_get_system_clock_speed();
	if ((int) sysclk != (int) 38.4) {
		if (stream != NULL)
			fprintf(stream,
				"Sorry, %.1lfMHz sysclk is not supported.\n\n",
				sysclk);
		(*err_nbr)++;
		ret = 0;
		goto dpll44xx_audit_end;
	}

	if (opp_id != OPP44XX_ID_MAX) {
		if (stream != NULL)
			fprintf(stream, "WARNING: using forced OPP %s!\n\n",
				opp44xx_name_get(opp_id, OMAP4_VDD_MPU));
		opp_mpu = opp_id;
		opp_iva = opp_id;
		opp_core = opp_id;
		(*wng_nbr)++;
	} else {
		ret = voltdm44xx_get_opp(OMAP4_VDD_MPU, &opp_mpu);
		ret |= voltdm44xx_get_opp(OMAP4_VDD_IVA, &opp_iva);
		ret |= voltdm44xx_get_opp(OMAP4_VDD_CORE, &opp_core);

		if (ret != 0) {
			if (stream != NULL) {
				fprintf(stream,
					"Sorry, OPP could not be detected, "
					"audit cannot be completed.\n");
				fprintf(stream, "Option \"-opp "
					"[dpll_casc|opp50|opp100|opp_turbo|"
					"opp_nitro|opp_nitrosb]\" may be "
					"considered until OPP is properly setup"
					".\n\n");
			}
			(*err_nbr)++;
			ret = 0;
			goto dpll44xx_audit_end;
		}
	}

	for (id = DPLL44XX_MPU; id <= DPLL44XX_USB; id++) {
		if ((dpll_id != DPLL44XX_ID_MAX) && (id != dpll_id))
			continue;

		switch (id) {
		case DPLL44XX_MPU:
			opp = opp_mpu;
			vdd_id = OMAP4_VDD_MPU;
			break;
		case DPLL44XX_IVA:
			opp = opp_iva;
			vdd_id = OMAP4_VDD_IVA;
			break;
		default:
			opp = opp_core;
			vdd_id = OMAP4_VDD_CORE;
		}

		autoadjust_table_init(table);
		row = 0;
		snprintf(table[row][0], TABLE_MAX_ELT_LEN,
			"%s AUDIT (@OPP %s, sysclk=%.1lfMHz)",
			dpll44xx_name_get(id), opp44xx_name_get(opp, vdd_id),
			sysclk);
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "Current Setting");
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "Expected");
		snprintf(table[row++][3], TABLE_MAX_ELT_LEN, "STATUS");

		ret = dpll44xx_dpll_params_get(id, &settings, 1);
		if (ret != 0) {
			fprintf(stderr, "Sorry, error (%d) occured while "
				"getting %s parameters!", ret,
				dpll44xx_name_get(id));
			(*err_nbr)++;
			ret = OMAPCONF_ERR_INTERNAL;
			goto dpll44xx_audit_end;
		}

		golden_settings = NULL;
		if (cpu_is_omap4430()) {
			if ((dpll44xx_audit_settings **)
				dpll4430_golden_settings_38_4MHz[id] == NULL) {
				if (stream != NULL)
					fprintf(stream,
						"WARNING: golden settings not "
						"available for %s.\n\n",
						dpll44xx_name_get(id));
				(*err_nbr)++;
				ret = 0;
				goto dpll44xx_audit_end;
			}
			golden_settings = (dpll44xx_audit_settings *)
				dpll4430_golden_settings_38_4MHz[id][opp];
		} else if (cpu_is_omap4460()) {
			if ((dpll44xx_audit_settings **)
				dpll4460_golden_settings_38_4MHz[id] == NULL) {
				if (stream != NULL)
					fprintf(stream,
						"WARNING: golden settings not "
						"available for %s.\n\n",
						dpll44xx_name_get(id));
				(*err_nbr)++;
				ret = 0;
				goto dpll44xx_audit_end;
			}
			golden_settings = (dpll44xx_audit_settings *)
				dpll4460_golden_settings_38_4MHz[id][opp];
		} else if (cpu_is_omap4470()) {
			if ((dpll44xx_audit_settings **)
				dpll4470_golden_settings_38_4MHz[id] == NULL) {
				if (stream != NULL)
					fprintf(stream,
						"WARNING: golden settings not "
						"available for %s.\n\n",
						dpll44xx_name_get(id));
				(*wng_nbr)++;
				continue;
			}
			golden_settings = (dpll44xx_audit_settings *)
				dpll4470_golden_settings_38_4MHz[id][opp];
		}
		if (golden_settings == NULL) {
			if (stream != NULL)
				fprintf(stream,
					"WARNING: golden settings not "
					"available for this device.\n\n");
			(*err_nbr)++;
			ret = 0;
			goto dpll44xx_audit_end;
		}

		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "Status");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
			dpll_status_name_get(settings.status));
		DPLL44XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->status,
			DPLL_STATUS_MAX, dpll44xx_audit_mode);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
			dpll_status_name_get(golden_settings->status));
		DPLL44XX_AUDIT_SHOW_STATUS(settings.status,
				golden_settings->status);

		if (golden_settings->status == DPLL_STATUS_STOPPED)
			/* All other DPLL settings are not relevant */
			goto dpll44xx_audit_table_show;

		if (settings.status == DPLL_STATUS_STOPPED) {
			snprintf(table[row - 1][3], TABLE_MAX_ELT_LEN, "warn.");
			(*err_nbr)--;
			if (stream != NULL) {
				fprintf(stream, "WARNING: %s is stopped, audit "
					"cannot be completed!\n\n",
					dpll44xx_name_get(id));
				autoadjust_table_fprint(stream, table, row, 4);
			}
			(*wng_nbr)++;
			continue;
		}

dpll44xx_audit_mode:
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "Mode");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
			dpll_mode_name_get(settings.mode));
		DPLL44XX_AUDIT_CHECK_GOLDEN_SETTING(golden_settings->mode,
			DPLL_MODE_MAX, dpll44xx_audit_autoidle_mode);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
			dpll_mode_name_get(golden_settings->mode));
		DPLL44XX_AUDIT_SHOW_STATUS(settings.mode,
			golden_settings->mode);

dpll44xx_audit_autoidle_mode:
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "Autoidle Mode");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
			dpll_autoidle_mode_name_get(settings.autoidle_mode));
		DPLL44XX_AUDIT_CHECK_GOLDEN_SETTING(
			golden_settings->autoidle_mode,
			DPLL_AUTOIDLE_MODE_MAX, dpll44xx_audit_lpmode);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
			dpll_autoidle_mode_name_get(
				golden_settings->autoidle_mode));
		DPLL44XX_AUDIT_SHOW_STATUS(settings.autoidle_mode,
			golden_settings->autoidle_mode);

dpll44xx_audit_lpmode:
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "Low-Power Mode");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
			s_mode[settings.lpmode]);
		DPLL44XX_AUDIT_CHECK_GOLDEN_SETTING(
			golden_settings->lpmode, -1, dpll44xx_audit_regm4xen);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
			s_mode[golden_settings->lpmode]);
		DPLL44XX_AUDIT_SHOW_STATUS((int) settings.lpmode,
			golden_settings->lpmode);

dpll44xx_audit_regm4xen:
		if ((id != DPLL44XX_ABE) && (opp == OMAP4_OPPDPLL_CASC))
			goto dpll44xx_audit_dcc_en;
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "REGM4XEN Mode");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
			s_mode[settings.regm4xen]);
		DPLL44XX_AUDIT_CHECK_GOLDEN_SETTING(
			golden_settings->regm4xen, -1, dpll44xx_audit_dcc_en);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
			s_mode[golden_settings->regm4xen]);
		DPLL44XX_AUDIT_SHOW_STATUS((int) settings.regm4xen,
			golden_settings->regm4xen);

dpll44xx_audit_dcc_en:
		if ((id != DPLL44XX_ABE) && (opp == OMAP4_OPPDPLL_CASC))
			goto dpll44xx_audit_M;
		if (cpu_is_omap4430())
			/* No DCC with OMAP4430 */
			goto dpll44xx_audit_M;
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "DCC Mode");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
			s_mode[settings.dcc_en]);
		DPLL44XX_AUDIT_CHECK_GOLDEN_SETTING(
			golden_settings->dcc_en, -1, dpll44xx_audit_dcc_count);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
			s_mode[golden_settings->dcc_en]);
		DPLL44XX_AUDIT_SHOW_STATUS((int) settings.dcc_en,
			golden_settings->dcc_en);

dpll44xx_audit_dcc_count:
		if (golden_settings->dcc_en != 1)
			goto dpll44xx_audit_M;
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "DCC Count");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%.3lfus",
			dpll44xx_dcc_count2us(settings.dcc_count));
		DPLL44XX_AUDIT_CHECK_GOLDEN_SETTING(
			golden_settings->dcc_count, -1, dpll44xx_audit_M);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%.3lfus",
			golden_settings->dcc_count);
		if (dpll44xx_dcc_count2us(settings.dcc_count) >=
			golden_settings->dcc_count) {
			snprintf(table[row++][3], TABLE_MAX_ELT_LEN, "PASS");
		} else {
			snprintf(table[row++][3], TABLE_MAX_ELT_LEN, "FAIL");
			(*err_nbr)++;
		}

dpll44xx_audit_M:
		if ((id != DPLL44XX_ABE) && (opp == OMAP4_OPPDPLL_CASC))
			goto dpll44xx_audit_N;
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "M Divider");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u",
			settings.MN_params.M);
		DPLL44XX_AUDIT_CHECK_GOLDEN_SETTING(
			golden_settings->M, -1, dpll44xx_audit_N);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u",
			golden_settings->M);
		DPLL44XX_AUDIT_SHOW_STATUS((int) settings.MN_params.M,
			golden_settings->M);

dpll44xx_audit_N:
		if ((id != DPLL44XX_ABE) && (opp == OMAP4_OPPDPLL_CASC))
			goto dpll44xx_audit_fdpll;
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "N Divider");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u",
			settings.MN_params.N);
		DPLL44XX_AUDIT_CHECK_GOLDEN_SETTING(
			golden_settings->N, -1, dpll44xx_audit_fdpll);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u",
			golden_settings->N);
		DPLL44XX_AUDIT_SHOW_STATUS((int) settings.MN_params.N,
			golden_settings->N);

dpll44xx_audit_fdpll:
		if ((id != DPLL44XX_ABE) && (opp == OMAP4_OPPDPLL_CASC))
			goto dpll44xx_audit_M2;
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "Lock Frequency");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%.1lfMHz",
			settings.fdpll);
		DPLL44XX_AUDIT_CHECK_GOLDEN_SETTING(
			golden_settings->fdpll, -1, dpll44xx_audit_M2);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%.1lfMHz",
			golden_settings->fdpll);
		DPLL44XX_AUDIT_SHOW_STATUS((int) settings.fdpll,
			(int) golden_settings->fdpll);

dpll44xx_audit_M2:
		if ((id != DPLL44XX_ABE) && (opp == OMAP4_OPPDPLL_CASC))
			goto dpll44xx_audit_M2_rate;
		if (golden_settings->dcc_en == 1)
			goto dpll44xx_audit_M3;
		if (settings.M2_present == 0)
			goto dpll44xx_audit_M3;
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "M2 Divider");
		if (id <= DPLL44XX_ABE)
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u (x2)",
				settings.MN_params.M2);
		else
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u",
				settings.MN_params.M2);

		DPLL44XX_AUDIT_CHECK_GOLDEN_SETTING(
			golden_settings->M2, -1, dpll44xx_audit_M2_rate);
		if (golden_settings->dcc_en == 1)
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u (x2)",
				golden_settings->M2);
		else
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u",
				golden_settings->M2);

		DPLL44XX_AUDIT_SHOW_STATUS((int) settings.MN_params.M2,
			golden_settings->M2);

dpll44xx_audit_M2_rate:
		if (id == DPLL44XX_IVA)
			goto dpll44xx_audit_switch_A_B;
		if (id <= DPLL44XX_ABE)
			snprintf(table[row][0], TABLE_MAX_ELT_LEN,
				"M2 Output Rate");
		else
			snprintf(table[row][0], TABLE_MAX_ELT_LEN,
				"CLKOUT Output Rate");

		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%.1lfMHz",
			settings.M2_speed);
		DPLL44XX_AUDIT_CHECK_GOLDEN_SETTING(
			golden_settings->M2_clkout_rate, -1,
			dpll44xx_audit_X2_M2_rate);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%.1lfMHz",
			golden_settings->M2_clkout_rate);
		DPLL44XX_AUDIT_SHOW_STATUS((int) settings.M2_speed,
			(int) golden_settings->M2_clkout_rate);

dpll44xx_audit_X2_M2_rate:
		if (id <= DPLL44XX_ABE)
			snprintf(table[row][0], TABLE_MAX_ELT_LEN,
				"X2_M2 Output Rate");
		else
			snprintf(table[row][0], TABLE_MAX_ELT_LEN,
				"CLKDCOLDO Output Rate");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%.1lfMHz",
			settings.X2_M2_speed);
		DPLL44XX_AUDIT_CHECK_GOLDEN_SETTING(
			golden_settings->X2_M2_clkdcoldo_rate, -1,
			dpll44xx_audit_M3);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%.1lfMHz",
			golden_settings->X2_M2_clkdcoldo_rate);
		DPLL44XX_AUDIT_SHOW_STATUS((int) settings.X2_M2_speed,
			(int) golden_settings->X2_M2_clkdcoldo_rate);


dpll44xx_audit_M3:
		if ((settings.M3_present == 0) &&
			(golden_settings->dcc_en != 1))
			goto dpll44xx_audit_switch_A_B;
		if ((id == DPLL44XX_MPU) && (golden_settings->dcc_en != 1))
			goto dpll44xx_audit_switch_A_B;
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "M3 Divider");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u",
			settings.MN_params.M3);
		DPLL44XX_AUDIT_CHECK_GOLDEN_SETTING(
			golden_settings->M3, -1, dpll44xx_audit_X2_M3_rate);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u",
			golden_settings->M3);
		DPLL44XX_AUDIT_SHOW_STATUS((int) settings.MN_params.M3,
			golden_settings->M3);

dpll44xx_audit_X2_M3_rate:
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "X2_M3 Output Rate");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%.1lfMHz",
			settings.X2_M3_speed);
		DPLL44XX_AUDIT_CHECK_GOLDEN_SETTING(
			golden_settings->X2_M3_rate, -1,
			dpll44xx_audit_switch_A_B);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%.1lfMHz",
			golden_settings->X2_M3_rate);
		DPLL44XX_AUDIT_SHOW_STATUS((int) settings.X2_M3_speed,
			(int) golden_settings->X2_M3_rate);

dpll44xx_audit_switch_A_B:
		if (id <= DPLL44XX_ABE)
			goto dpll44xx_audit_hsdiv;
		else
			goto dpll44xx_audit_table_show;


dpll44xx_audit_hsdiv:
		for (i = 0; i < 4; i++) {
			if (settings.HS_M[i].present != 1)
				continue;
			if ((id != DPLL44XX_ABE) && (opp == OMAP4_OPPDPLL_CASC))
				goto dpll44xx_audit_hsdiv_rate;
			snprintf(table[row][0], TABLE_MAX_ELT_LEN,
				"M%u Divider", i + 4);
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u",
				settings.HS_M[i].div);
			if (golden_settings->hsdiv[i] == -1) {
				/* Golden setting not available */
				snprintf(table[row][2], TABLE_MAX_ELT_LEN,
					"Not available");
				snprintf(table[row][3], TABLE_MAX_ELT_LEN,
					"warn.");
				(*wng_nbr)++;
				row++;
				goto dpll44xx_audit_hsdiv_rate;
			}
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u",
				golden_settings->hsdiv[i]);
			DPLL44XX_AUDIT_SHOW_STATUS((int) settings.HS_M[i].div,
				golden_settings->hsdiv[i]);

dpll44xx_audit_hsdiv_rate:
			snprintf(table[row][0], TABLE_MAX_ELT_LEN,
				"X2_M%u Output Rate", i + 4);
			switch (i) {
			case 0:
				rate = settings.X2_M4_speed;
				break;
			case 1:
				rate = settings.X2_M5_speed;
				break;
			case 2:
				rate = settings.X2_M6_speed;
				break;
			case 3:
				rate = settings.X2_M7_speed;
				break;
			default:
				rate = 0;
				fprintf(stderr,	"%s(): i=%u cannot happen!\n",
					__func__, i);
				return OMAPCONF_ERR_INTERNAL;
			}
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%.1lfMHz",
				rate);

			if (golden_settings->hsdiv_rate[i] == -1) {
				/* Golden setting not available */
				snprintf(table[row][2], TABLE_MAX_ELT_LEN,
					"Not available");
				snprintf(table[row][3], TABLE_MAX_ELT_LEN,
					"warn.");
				(*wng_nbr)++;
				row++;
				continue;
			}
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%.1lfMHz",
				golden_settings->hsdiv_rate[i]);
			DPLL44XX_AUDIT_SHOW_STATUS((int) rate,
				(int) golden_settings->hsdiv_rate[i]);
		}

dpll44xx_audit_table_show:
		if (stream != NULL)
			autoadjust_table_fprint(stream, table, row, 4);
	}
	ret = 0;


dpll44xx_audit_end:
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll44xx_s2id
 * @BRIEF		convert string to valid DPLL ID.
 * @RETURNS		DPLL44XX_MPU if s == "mpu"
 *			DPLL44XX_IVA if s == "iva"
 *			DPLL44XX_CORE if s == "core"
 *			DPLL44XX_PER if s == "per"
 *			DPLL44XX_ABE if s == "abe"
 *			DPLL44XX_USB if s == "usb"
 *			DPLL44XX_UNIPRO if s == "unipro1"
 *			DPLL44XX_DDRPHY if s == "ddrphy"
 *			DPLL44XX_ID_MAX otherwise
 * @param[in]		s: string
 * @DESCRIPTION		convert string to valid DPLL ID.
 *//*------------------------------------------------------------------------ */
dpll44xx_id dpll44xx_s2id(char *s)
{
	CHECK_NULL_ARG(s, DPLL44XX_ID_MAX);

	if (strcmp(s, "mpu") == 0)
		return  DPLL44XX_MPU;
	else if (strcmp(s, "iva") == 0)
		return  DPLL44XX_IVA;
	else if (strcmp(s, "core") == 0)
		return  DPLL44XX_CORE;
	else if (strcmp(s, "per") == 0)
		return  DPLL44XX_PER;
	else if (strcmp(s, "abe") == 0)
		return  DPLL44XX_ABE;
	else if (strcmp(s, "usb") == 0)
		return  DPLL44XX_USB;
	else if (strcmp(s, "unipro") == 0)
		return  DPLL44XX_UNIPRO;
	else if (strcmp(s, "ddrphy") == 0)
		return  DPLL44XX_DDRPHY;
	else
		return DPLL44XX_ID_MAX;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll44xx_main
 * @BRIEF		call function corresponding to shell arguments
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		call function corresponding to shell arguments
 *//*------------------------------------------------------------------------ */
int dpll44xx_main(int argc, char *argv[])
{
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (argc == 2) {
		if (strcmp(argv[1], "dump") == 0) {
			ret = dpll44xx_dump();
		} else if (strcmp(argv[1], "cfg") == 0) {
			ret = dpll44xx_config_show(stdout);
		} else {
			help(HELP_DPLL);
		ret = 0;
		}
	} else {
		help(HELP_DPLL);
		ret = 0;
	}

	return ret;
}
