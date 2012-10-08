/*
 *
 * @Component			OMAPCONF
 * @Filename			module54xx.c
 * @Description			OMAP5 Module Definitions & APIs
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


#include <module54xx.h>
#include <module54xx-data.h>
#include <lib.h>
#include <string.h>
#include <stdio.h>
#include <cpuinfo.h>


/* #define MODULE54XX_DEBUG */
#ifdef MODULE54XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_name_get
 * @BRIEF		return module name
 * @RETURNS		module name on success
 *			NULL in case of error
 * @param[in]		id: valid module ID
 * @DESCRIPTION		return module name
 *//*------------------------------------------------------------------------ */
const char *mod54xx_name_get(mod54xx_id id)
{
	CHECK_ARG_LESS_THAN(id, MOD54XX_ID_MAX, NULL);

	return mod54xx_names_table[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_clkdm_get
 * @BRIEF		return the ID of the clock domain a given module
 *			is part of.
 * @RETURNS		clock domain ID a given module is part of
 *			(< CLKDM54XX_ID_MAX)
 *			CLKDM54XX_ID_MAX in case of error
 * @param[in]		id: module ID
 * @DESCRIPTION		return the ID of the clock domain a given module
 *			is part of.
 *//*------------------------------------------------------------------------ */
clkdm54xx_id mod54xx_clkdm_get(mod54xx_id id)
{
	CHECK_ARG_LESS_THAN(id, MOD54XX_ID_MAX, CLKDM54XX_ID_MAX);

	return mod54xx_clkdm_table[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_pwrdm_get
 * @BRIEF		return the ID of the power domain a given module
 *			is part of.
 * @RETURNS		power domain ID a given module is part of
 *			(< PWRDM54XX_ID_MAX)
 *			PWRDM54XX_ID_MAX in case of error
 * @param[in]		id: module ID
 * @DESCRIPTION		return the ID of the power domain a given module
 *			is part of.
 *//*------------------------------------------------------------------------ */
pwrdm54xx_id mod54xx_pwrdm_get(mod54xx_id id)
{
	CHECK_ARG_LESS_THAN(id, MOD54XX_ID_MAX, PWRDM54XX_ID_MAX);

	return clkdm54xx_pwrdm_get(mod54xx_clkdm_get(id));
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_voltdm_get
 * @BRIEF		return the ID of the voltage domain a given module
 *			is part of.
 * @RETURNS		voltage domain ID a given module is part of
 *			(< VDD54XX_ID_MAX)
 *			VDD54XX_ID_MAX in case of error
 * @param[in]		id: module ID
 * @DESCRIPTION		return the ID of the voltage domain a given module
 *			is part of.
 *//*------------------------------------------------------------------------ */
voltdm54xx_id mod54xx_voltdm_get(mod54xx_id id)
{
	CHECK_ARG_LESS_THAN(id, MOD54XX_ID_MAX, VDD54XX_ID_MAX);

	return pwrdm54xx_voltdm_get(mod54xx_pwrdm_get(id));
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_mode_get
 * @BRIEF		retrieve module mode from CM register
 * @RETURNS		module mode on success
 *			MOD_MODULE_MODE_MAX in case of error or not available
 * @param[in]		id: valid module ID
 * @DESCRIPTION		retrieve module mode from CM register
 *//*------------------------------------------------------------------------ */
mod_module_mode mod54xx_mode_get(mod54xx_id id)
{
	reg *cm_clkctrl_reg;
	unsigned int cm_clkctrl;
	mod_module_mode mmode;

	if (!cpu_is_omap54xx())
		return MOD_MODULE_MODE_MAX;
	CHECK_ARG_LESS_THAN(id, MOD54XX_ID_MAX, MOD_MODULE_MODE_MAX);

	/* Retrieve CM_CLKCTRL address */
	cm_clkctrl_reg = mod54xx_cm_clkctrl_reg_get(id);
	if (cm_clkctrl_reg == NULL) {
		/* Module is not SW-Controlled via PRCM */
		dprintf("%s(#%u (%s)): CM_CLKCTRL ADDR = NULL\n",
			__func__, id, mod54xx_name_get(id));
		return MOD_MODULE_MODE_MAX;
	}

	/* Retrieve module mode */
	cm_clkctrl = reg_read(cm_clkctrl_reg);
	mmode = (mod_module_mode) extract_bitfield(cm_clkctrl, 0, 2);
	dprintf("%s(#%u (%s)): CM_CLKCTRL ADDR=0x%08X CM_CLKCTRL="
		"0x%08X MODULEMODE (bit [1-0])=%u (%s)\n", __func__, id,
		mod54xx_name_get(id), cm_clkctrl_reg->addr, cm_clkctrl, mmode,
		mod_module_mode_name_get(mmode));

	return mmode;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_idle_status_get
 * @BRIEF		retrieve module's idle status from CM_xxx_xxx_CLKCTRL
 * @RETURNS		module idle status
 *			MOD_IDLE_STATUS_MAX in case of error
 * @param[in]		id: module ID
 * @DESCRIPTION		retrieve module's idle status from CM_xxx_xxx_CLKCTRL
 *//*------------------------------------------------------------------------ */
mod_idle_status mod54xx_idle_status_get(mod54xx_id id)
{
	reg *cm_clkctrl_reg;
	unsigned int cm_clkctrl;
	mod_idle_status mstatus;

	if (!cpu_is_omap54xx())
		return MOD_IDLE_STATUS_MAX;
	CHECK_ARG_LESS_THAN(id, MOD54XX_ID_MAX, MOD_IDLE_STATUS_MAX);

	if (mod54xx_has_idle_status(id) == 0)
		return MOD_IDLE_STATUS_MAX;

	cm_clkctrl_reg = mod54xx_cm_clkctrl_reg_get(id);
	if (cm_clkctrl_reg == NULL)
		return MOD_IDLE_STATUS_MAX;

	cm_clkctrl = reg_read(cm_clkctrl_reg);
	mstatus = (mod_idle_status) extract_bitfield(cm_clkctrl, 16, 2);
	dprintf("%s(%u (%s)): CM_CLKCTRL ADDR = 0x%08X, CM_CLKCTRL = 0x%08X, "
		"IDLEST = %u (%s)\n", __func__, id, mod54xx_name_get(id),
		cm_clkctrl_reg->addr, cm_clkctrl, mstatus,
		mod_idle_status_name_get(mstatus));

	return mstatus;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_standby_status_get
 * @BRIEF		retrieve module standby status from CM_xxx_xxx_CLKCTRL
 * @RETURNS		module standby status
 *			MOD_STANDBY_STATUS_MAX in case of error
 * @param[in]		id: module ID
 * @DESCRIPTION		retrieve module standby status from CM_xxx_xxx_CLKCTRL
 *//*------------------------------------------------------------------------ */
mod_standby_status mod54xx_standby_status_get(mod54xx_id id)
{
	reg *cm_clkctrl_reg;
	unsigned int cm_clkctrl;
	mod_standby_status mstatus;

	if (!cpu_is_omap54xx())
		return MOD_STANDBY_STATUS_MAX;
	CHECK_ARG_LESS_THAN(id, MOD54XX_ID_MAX, MOD_STANDBY_STATUS_MAX);

	if (mod54xx_has_standby_status(id) == 0)
		return MOD_STANDBY_STATUS_MAX;

	cm_clkctrl_reg = mod54xx_cm_clkctrl_reg_get(id);
	if (cm_clkctrl_reg == NULL)
		return MOD_STANDBY_STATUS_MAX;
	cm_clkctrl = reg_read(cm_clkctrl_reg);
	mstatus = (mod_standby_status) extract_bit(cm_clkctrl, 18);
	dprintf("%s(%u (%s)): CM_CLKCTRL ADDR = 0x%08X, CM_CLKCTRL = 0x%08X, "
		"STANDBYST = %u (%s)\n", __func__, id, mod54xx_name_get(id),
		cm_clkctrl_reg->addr, cm_clkctrl,
		mstatus, mod_standby_status_name_get(mstatus));

	return mstatus;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_clk_get
 * @BRIEF		return module functional clock ID
 * @RETURNS		module functional clock source in case of success
 *			CLK54XX_ID_MAX in case of error
 * @param[in]		id: valid module ID
 * @DESCRIPTION		return module functional clock ID
 *//*------------------------------------------------------------------------ */
clk54xx_id mod54xx_clk_get(mod54xx_id id)
{
	clk54xx_id clk_id;

	CHECK_ARG_LESS_THAN(id, MOD54XX_ID_MAX, CLK54XX_ID_MAX);

	clk_id = mod54xx_flck_table[id];
	dprintf("%s(%s): source clk is %s\n", __func__,
		mod54xx_name_get(id), clk54xx_name_get(clk_id));

	return clk_id;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_clk_rate_get
 * @BRIEF		return module functional clock rate (in MHz)
 * @RETURNS		> 0 clock rate in MHz
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		id: valid module ID
 * @param[in]		ignore: do not consider DPLL stop status.
 *			Useful for functions that needs the DPLL output
 *			frequencies whatever its status
 *			(e.g. audit, clock tree, etc)
 * @DESCRIPTION		return module functional clock rate (in MHz)
 *//*------------------------------------------------------------------------ */
double mod54xx_clk_rate_get(mod54xx_id id, unsigned short ignore)
{
	clk54xx_id clk_id;
	double rate;

	CHECK_ARG_LESS_THAN(id, MOD54XX_ID_MAX, (double) OMAPCONF_ERR_ARG);

	clk_id = mod54xx_clk_get(id);
	rate = clk54xx_rate_get(clk_id, ignore);

	dprintf("%s(%s): source clk is %s, rate is %lfMHz\n",
		__func__, mod54xx_name_get(id),
		clk54xx_name_get(clk_id), rate);

	return rate;
}


#ifndef MODULE54XX_DEBUG
/* #define MOD54XX_GET_CLK_SPEED_DEBUG */
#ifdef MOD54XX_GET_CLK_SPEED_DEBUG
#undef dprintf
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#undef dprintf
#define dprintf(format, ...)
#endif
#endif

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_opp_clk_rate_get
 * @BRIEF		retrieve omap module's functional clock speed
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		module_id: omap module ID
 * @param[in,out]	src_clk_id: returned source clock ID
 *				(== CLK54XX_ID_MAX in case of error)
 * @param[in,out]	opp_id: returned OPP ID
 *				(== OPP54XX_ID_MAX in case of error)
 * @param[in,out]	rate: returned clock rate (in MHz)
 *				(< 0 in case of error)
 * @DESCRIPTION		retrieve omap module's functional clock speed,
 *			as well as source clock ID and current OPP
 *			Ensure that OPP is stable before returning OPP and
 *			clock speed, so that there is no misalignment between
 *			the 2 data.
 *//*------------------------------------------------------------------------ */
int mod54xx_opp_clk_rate_get(mod54xx_id module_id,
	clk54xx_id *src_clk_id, opp54xx_id *opp_id, double *rate)
{
	int ret;
	voltdm54xx_id volt_dom_id;
	opp54xx_id opp_id2;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(module_id, MOD54XX_ID_MAX, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(src_clk_id, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(opp_id, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(rate, OMAPCONF_ERR_ARG);

	*opp_id  = OPP54XX_ID_MAX;
	*rate  = (double) OMAPCONF_ERR_NOT_AVAILABLE;

	/* Get module's functional source clock */
	*src_clk_id = mod54xx_clk_get(module_id);
	if (*src_clk_id == CLK54XX_ID_MAX) {
		dprintf("%s(%s): could not get FCLK!\n", __func__,
			mod54xx_name_get(module_id));
		ret = OMAPCONF_ERR_NOT_AVAILABLE;
		goto mod54xx_opp_clk_rate_get_end;
	}

	/* Get module's functional source clock speed */
	*rate = clk54xx_rate_get(*src_clk_id, 1);
	if (*rate < 0) {
		dprintf("%s(%s): could not get rate! (ret=%lf)\n",
			__func__, mod54xx_name_get(module_id), *rate);
		ret = OMAPCONF_ERR_NOT_AVAILABLE;
		goto mod54xx_opp_clk_rate_get_end;
	}

	/* Get module's voltage domain ID */
	volt_dom_id = mod54xx_voltdm_get(module_id);
	if (volt_dom_id == VDD54XX_ID_MAX) {
		dprintf("%s(%s): could not get VDD ID!\n",
			__func__, mod54xx_name_get(module_id));
		ret = OMAPCONF_ERR_NOT_AVAILABLE;
		goto mod54xx_opp_clk_rate_get_end;
	}

	/* To ensure OPP is stable, take 2 times the
	 * OPP and use a do {} while() loop that cannot exit until the 2 OPPs
	 * retrieved are identical.
	 */
	do {
		/*
		 * Get the OPP of the voltage domain the module is part of.
		 */
		*opp_id = voltdm54xx_opp_get(volt_dom_id);
		if (*opp_id == OPP54XX_ID_MAX) {
			dprintf("%s(%s): could not get OPP!\n",
				__func__, mod54xx_name_get(module_id));
			ret = OMAPCONF_ERR_NOT_AVAILABLE;
			goto mod54xx_opp_clk_rate_get_end;
		}

		/* Get module's functional source clock speed */
		*rate = clk54xx_rate_get(*src_clk_id, 1);
		if (*rate < 0) {
			dprintf("%s(%s): could not get rate! (ret=%lf)\n",
				__func__, mod54xx_name_get(module_id), *rate);
			ret = OMAPCONF_ERR_NOT_AVAILABLE;
			goto mod54xx_opp_clk_rate_get_end;
		}

		/* Get OPP a 2nd time */
		opp_id2 = voltdm54xx_opp_get(volt_dom_id);
		if (opp_id2 == OPP54XX_ID_MAX) {
			dprintf("%s(%s): could not get OPP2!\n",
				__func__, mod54xx_name_get(module_id));
			goto mod54xx_opp_clk_rate_get_end;
		}
	} while (*opp_id != opp_id2);
	ret = 0;

mod54xx_opp_clk_rate_get_end:
	dprintf("%s(%s): src_clk_id=%s, opp_id=%s, speed=%lfMHz\n", __func__,
		mod54xx_name_get(module_id), clk54xx_name_get(*src_clk_id),
		opp54xx_name_get(*opp_id), *rate);
	return ret;
}

#ifndef MODULE54XX_DEBUG
#ifdef MOD54XX_GET_CLK_SPEED_DEBUG
#undef dprintf
#define dprintf(format, ...)
#endif
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_por_clk_rate_get
 * @BRIEF		return module functional PoR (Plan of Record) clock rate
 *			(in MHz)
 * @RETURNS		module functional PoR clock rate (in MHz) in case of
 *			success
 *			OMAPCONF_ERR_ARG
 * @param[in]		id: valid module ID
 * @param[in]		opp: valid OPP ID
 * @DESCRIPTION		return module functional PoR (Plan of Record) clock rate
 *			(in MHz)
 *//*------------------------------------------------------------------------ */
double mod54xx_por_clk_rate_get(mod54xx_id id, opp54xx_id opp)
{
	double por_clk_rate;

	CHECK_ARG_LESS_THAN(id, MOD54XX_ID_MAX, (double) OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(opp, OPP54XX_ID_MAX, (double) OMAPCONF_ERR_ARG);

	por_clk_rate = mod54xx_por_rates_table[id][opp];
	dprintf("%s(%s, %s): POR rate is %lfMHz\n", __func__,
		mod54xx_name_get(id), opp54xx_name_get(opp), por_clk_rate);

	return por_clk_rate;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_properties_get
 * @BRIEF		return module properties, as stored in
 *			mod54xx_properties_table
 * @RETURNS		module properties
 * @param[in]		id: valid module ID
 * @DESCRIPTION		return module properties, as stored in
 *			mod54xx_properties_table
 *			Return 0 if not available or in case of error.
 *			Does not make any access to any register.
 *//*------------------------------------------------------------------------ */
unsigned int mod54xx_properties_get(mod54xx_id id)
{
	if (!cpu_is_omap54xx()) {
		fprintf(stderr, "%s(): CPU != 54XX\n", __func__);
		return 0;
	}

	if (id >= MOD54XX_ID_MAX) {
		fprintf(stderr, "%s(): id=%u >= MOD54XX_ID_MAX (%u)\n",
			__func__, id, MOD54XX_ID_MAX);
		return 0;
	}

	dprintf("%s(%u (%s)): module properties=0x%04X\n", __func__, id,
			mod54xx_name_get(id), mod54xx_properties_table[id]);
	return mod54xx_properties_table[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_has_sysconfig_register
 * @BRIEF		return 1 if module has a SYSCONFIG register.
 * @RETURNS		1 if module has a SYSCONFIG register.
 *			0 if not available or in case of error.
 * @param[in]		id: valid module ID
 * @DESCRIPTION		return 1 if module has a SYSCONFIG register.
 *			(not all modules feature it).
 *			Return 0 if not available or in case of error.
 *			Does not make any access to any register.
 *//*------------------------------------------------------------------------ */
unsigned int mod54xx_has_sysconfig_register(mod54xx_id id)
{
	unsigned int mprop;

	if (!cpu_is_omap54xx()) {
		fprintf(stderr, "%s(): CPU != 54XX\n", __func__);
		return 0;
	}

	if (id >= MOD54XX_ID_MAX) {
		fprintf(stderr, "%s(): id=%u >= MOD54XX_ID_MAX (%u)\n",
			__func__, id, MOD54XX_ID_MAX);
		return 0;
	}

	mprop = mod54xx_properties_get(id);
	if ((mprop & MOD_HAS_SYSCONFIG) != 0) {
		dprintf("%s(%u): mod %s HAS SYSCONFIG register\n", __func__, id,
			mod54xx_name_get(id));
		return 1;
	} else {
		dprintf("%s(%u): mod %s does NOT have SYSCONFIG register\n",
			__func__, id, mod54xx_name_get(id));
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_has_autoidle_bit
 * @BRIEF		return 1 if module has autoidle bit in sysconfig.
 * @RETURNS		1 if module has autoidle bit in sysconfig register.
 *			0 if not available or in case of error.
 * @param[in]		id: valid module ID
 * @DESCRIPTION		return 1 if module has autoidle bit in sysconfig.
 *			(not all modules feature it).
 *			Return 0 if not available or in case of error.
 *			Does not make any access to any register.
 *//*------------------------------------------------------------------------ */
unsigned int mod54xx_has_autoidle_bit(mod54xx_id id)
{
	unsigned int mprop;

	if (!cpu_is_omap54xx()) {
		fprintf(stderr, "%s(): CPU != 54XX\n", __func__);
		return 0;
	}

	if (id >= MOD54XX_ID_MAX) {
		fprintf(stderr, "%s(): id=%u >= MOD54XX_ID_MAX (%u)\n",
			__func__, id, MOD54XX_ID_MAX);
		return 0;
	}

	mprop = mod54xx_properties_get(id);
	if ((mprop & MOD_HAS_AUTOIDLE_BIT0) != 0) {
		dprintf("%s(%u): mod %s HAS autoidle bit (0)\n", __func__, id,
			mod54xx_name_get(id));
		return 1;
	} else if ((mprop & MOD_HAS_AUTOIDLE_BIT8) != 0) {
		dprintf("%s(%u): mod %s HAS autoidle bit (8)\n", __func__, id,
			mod54xx_name_get(id));
		return 1;
	} else {
		dprintf("%s(%u): mod %s does NOT have autoidle bit\n",
			__func__, id, mod54xx_name_get(id));
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_has_idle_mode
 * @BRIEF		return 1 if module has idle mode in sysconfig register.
 * @RETURNS		1 if module has idle mode in sysconfig register.
 *			0 if not available or in case of error.
 * @param[in]		id: valid module ID
 * @DESCRIPTION		return 1 if module has idle mode in sysconfig register.
 *			(not all modules feature it).
 *			Return 0 if not available or in case of error.
 *			Does not make any access to any register.
 *//*------------------------------------------------------------------------ */
unsigned int mod54xx_has_idle_mode(mod54xx_id id)
{
	unsigned int mprop;

	if (!cpu_is_omap54xx()) {
		fprintf(stderr, "%s(): CPU != 54XX\n", __func__);
		return 0;
	}

	if (id >= MOD54XX_ID_MAX) {
		fprintf(stderr, "%s(): id=%u >= MOD54XX_ID_MAX (%u)\n",
			__func__, id, MOD54XX_ID_MAX);
		return 0;
	}

	mprop = mod54xx_properties_get(id);
	if ((mprop & MOD_HAS_IDLE_MODE1) != 0) {
		dprintf("%s(%u): mod %s HAS idle mode (1-0)\n", __func__, id,
			mod54xx_name_get(id));
		return 1;
	} else if ((mprop & MOD_HAS_IDLE_MODE3) != 0) {
		dprintf("%s(%u): mod %s HAS idle mode (3-2)\n", __func__, id,
			mod54xx_name_get(id));
		return 1;
	} else if ((mprop & MOD_HAS_IDLE_MODE4) != 0) {
		dprintf("%s(%u): mod %s HAS idle mode (4-3)\n", __func__, id,
			mod54xx_name_get(id));
		return 1;
	} else {
		dprintf("%s(%u): mod %s does NOT have idle mode\n",
			__func__, id, mod54xx_name_get(id));
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_has_idle_status
 * @BRIEF		return 1 if module has idle mode in sysconfig register.
 * @RETURNS		1 if module has idle status in CM_CLKCTRL register.
 *			0 if not available or in case of error.
 * @param[in]		id: valid module ID
 * @DESCRIPTION		return 1 if module has idle mode in sysconfig register.
 *			(not all modules feature it).
 *			Return 0 if not available or in case of error.
 *			Does not make any access to any register.
 *//*------------------------------------------------------------------------ */
unsigned int mod54xx_has_idle_status(mod54xx_id id)
{
	unsigned int mprop;

	if (!cpu_is_omap54xx()) {
		fprintf(stderr, "%s(): CPU != 54XX\n", __func__);
		return 0;
	}

	if (id >= MOD54XX_ID_MAX) {
		fprintf(stderr, "%s(): id=%u >= MOD54XX_ID_MAX (%u)\n",
			__func__, id, MOD54XX_ID_MAX);
		return 0;
	}

	mprop = mod54xx_properties_get(id);
	if ((mprop & MOD_HAS_NO_IDLE_STATUS) != 0) {
		dprintf("%s(%u): mod %s HAS NO idle status\n", __func__, id,
			mod54xx_name_get(id));
		return 0;
	} else {
		dprintf("%s(%u): mod %s HAS idle status\n",
			__func__, id, mod54xx_name_get(id));
		return 1;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_has_smart_idle_wakeup_mode
 * @BRIEF		return 1 if module implements "smart-idle wakeup" mode
 * @RETURNS		1 if module implements "smart-idle wakeup" mode.
 *			0 if not available or in case of error.
 * @param[in]		id: valid module ID
 * @DESCRIPTION		return 1 if module implements "smart-idle wakeup" mode
 *			(not all modules feature it).
 *			Return 0 if not available or in case of error.
 *			Does not make any access to any register.
 *//*------------------------------------------------------------------------ */
unsigned int mod54xx_has_smart_idle_wakeup_mode(mod54xx_id id)
{
	unsigned int mprop;

	if (!cpu_is_omap54xx()) {
		fprintf(stderr, "%s(): CPU != 54XX\n", __func__);
		return 0;
	}

	if (id >= MOD54XX_ID_MAX) {
		fprintf(stderr, "%s(): id=%u >= MOD54XX_ID_MAX (%u)\n",
			__func__, id, MOD54XX_ID_MAX);
		return 0;
	}

	mprop = mod54xx_properties_get(id);
	if ((mprop & MOD_HAS_SMART_IDLE_WAKEUP_MODE) != 0) {
		dprintf("%s(%u): mod %s HAS smart-idle wakeup mode\n",
			__func__, id, mod54xx_name_get(id));
		return 1;
	} else {
		dprintf("%s(%u): mod %s does NOT have smart-idle wakeup mode\n",
			__func__, id, mod54xx_name_get(id));
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_has_enawakeup_bit
 * @BRIEF		return 1 if module has ENAWAKEUP bit in sysconfig
 * @RETURNS		1 if module has ENAWAKEUP bit in sysconfig register.
 *			0 if not available or in case of error.
 * @param[in]		id: valid module ID
 * @DESCRIPTION		return 1 if module has ENAWAKEUP bit in sysconfig
 *			(not all modules feature it).
 *			Return 0 if not available or in case of error.
 *			Does not make any access to any register.
 *//*------------------------------------------------------------------------ */
unsigned int mod54xx_has_enawakeup_bit(mod54xx_id id)
{
	unsigned int mprop;

	if (!cpu_is_omap54xx()) {
		fprintf(stderr, "%s(): CPU != 54XX\n", __func__);
		return 0;
	}

	if (id >= MOD54XX_ID_MAX) {
		fprintf(stderr, "%s(): id=%u >= MOD54XX_ID_MAX (%u)\n",
			__func__, id, MOD54XX_ID_MAX);
		return 0;
	}

	mprop = mod54xx_properties_get(id);
	if ((mprop & MOD_HAS_ENAWAKEUP_BIT) != 0) {
		dprintf("%s(%u): mod %s HAS ENAWAKEUP bit\n", __func__, id,
			mod54xx_name_get(id));
		return 1;
	} else {
		dprintf("%s(%u): mod %s does NOT have ENAWAKEUP bit\n",
			__func__, id, mod54xx_name_get(id));
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_has_standby_mode
 * @BRIEF		return 1 if module has STANDBY mode in sysconfig
 * @RETURNS		1 if module has STANDBY mode in sysconfig register.
 *			0 if not available or in case of error.
 * @param[in]		id: valid module ID
 * @DESCRIPTION		return 1 if module has STANDBY mode in sysconfig
 *			(not all modules feature it).
 *			Return 0 if not available or in case of error.
 *			Does not make any access to any register.
 *//*------------------------------------------------------------------------ */
unsigned int mod54xx_has_standby_mode(mod54xx_id id)
{
	unsigned int mprop;

	if (!cpu_is_omap54xx()) {
		fprintf(stderr, "%s(): CPU != 54XX\n", __func__);
		return 0;
	}

	if (id >= MOD54XX_ID_MAX) {
		fprintf(stderr, "%s(): id=%u >= MOD54XX_ID_MAX (%u)\n",
			__func__, id, MOD54XX_ID_MAX);
		return 0;
	}

	mprop = mod54xx_properties_get(id);
	if ((mprop & MOD_HAS_STANDBY_MODE5) != 0) {
		dprintf("%s(%u): mod %s HAS STANDBY mode (5-4)\n", __func__, id,
			mod54xx_name_get(id));
		return 1;
	} else if ((mprop & MOD_HAS_STANDBY_MODE13) != 0) {
		dprintf("%s(%u): mod %s HAS STANDBY mode (13-12)\n",
			__func__, id, mod54xx_name_get(id));
		return 1;
	} else {
		dprintf("%s(%u): mod %s does NOT have STANDBY mode\n",
			__func__, id, mod54xx_name_get(id));
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_has_standby_status
 * @BRIEF		return 1 if module has STANDBY status field in
 *			CM_xyz_CLKCTRL register.
 * @RETURNS		1 if module has STANDBY status field in
 *			CM_xyz_CLKCTRL register.
 *			0 if not available or in case of error.
 * @param[in]		id: valid module ID
 * @DESCRIPTION		return 1 if module has STANDBY status field in
 *			CM_xyz_CLKCTRL register.
 *			(not all modules feature it).
 *			Return 0 if not available or in case of error.
 *			Does not make any access to any register.
 *//*------------------------------------------------------------------------ */
unsigned int mod54xx_has_standby_status(mod54xx_id id)
{
	unsigned int mprop;

	if (!cpu_is_omap54xx()) {
		fprintf(stderr, "%s(): CPU != 54XX\n", __func__);
		return 0;
	}

	if (id >= MOD54XX_ID_MAX) {
		fprintf(stderr, "%s(): id=%u >= MOD54XX_ID_MAX (%u)\n",
			__func__, id, MOD54XX_ID_MAX);
		return 0;
	}

	mprop = mod54xx_properties_get(id);
	if ((mprop & MOD_HAS_STANDBY_STATUS) != 0) {
		dprintf("%s(%u): mod %s HAS STANDBY status\n", __func__, id,
			mod54xx_name_get(id));
		return 1;
	} else {
		dprintf("%s(%u): mod %s does NOT have STANDBY status\n",
			__func__, id, mod54xx_name_get(id));
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_has_smart_standby_wakeup_mode
 * @BRIEF		return 1 if module implements "smart-standby wakeup"
 *			mode
 * @RETURNS		1 if module implements "smart-standby wakeup" mode.
 *			0 if not available or in case of error.
 * @param[in]		id: valid module ID
 * @DESCRIPTION		return 1 if module implements "smart-standby wakeup"
 *			mode
 *			(not all modules feature it).
 *			Return 0 if not available or in case of error.
 *			Does not make any access to any register.
 *//*------------------------------------------------------------------------ */
unsigned int mod54xx_has_smart_standby_wakeup_mode(mod54xx_id id)
{
	unsigned int mprop;

	if (!cpu_is_omap54xx()) {
		fprintf(stderr, "%s(): CPU != 54XX\n", __func__);
		return 0;
	}

	if (id >= MOD54XX_ID_MAX) {
		fprintf(stderr, "%s(): id=%u >= MOD54XX_ID_MAX (%u)\n",
			__func__, id, MOD54XX_ID_MAX);
		return 0;
	}

	mprop = mod54xx_properties_get(id);
	if ((mprop & MOD_HAS_SMART_STANDBY_WAKEUP_MODE) != 0) {
		dprintf("%s(%u): mod %s HAS smart-standby wakeup mode\n",
			__func__, id, mod54xx_name_get(id));
		return 1;
	} else {
		dprintf("%s(%u): mod %s does NOT have smart-standby wakeup "
			"mode\n", __func__, id, mod54xx_name_get(id));
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_has_clock_activity_mode
 * @BRIEF		check if omap module has clock activity mode in
 *			sysconfig register
 * @RETURNS		1 if omap module has clock activity mode in
 *			sysconfig register.
 *			0 if not available or in case of error.
 * @param[in]		id: valid module ID
 * @DESCRIPTION		check if omap module has clock activity mode in
 *			sysconfig register
 *			(not all modules feature it).
 *			Return 0 if not available or in case of error.
 *			Does not make any access to any register.
 *//*------------------------------------------------------------------------ */
unsigned int mod54xx_has_clock_activity_mode(mod54xx_id id)
{
	unsigned int mprop;

	if (!cpu_is_omap54xx()) {
		fprintf(stderr, "%s(): CPU != 54XX\n", __func__);
		return 0;
	}

	if (id >= MOD54XX_ID_MAX) {
		fprintf(stderr, "%s(): id=%u >= MOD54XX_ID_MAX (%u)\n",
			__func__, id, MOD54XX_ID_MAX);
		return 0;
	}

	mprop = mod54xx_properties_get(id);
	if ((mprop & MOD_HAS_CLOCK_ACTIVITY_MODE) != 0) {
		dprintf("%s(%u): mod %s HAS clock activity mode\n", __func__,
			id, mod54xx_name_get(id));
		return 1;
	} else {
		dprintf("%s(%u): mod %s does NOT have clock activity mode\n",
			__func__, id, mod54xx_name_get(id));
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_is_accessible
 * @BRIEF		check omap module's registers accessibility
 * @RETURNS		1 if omap module's registers accessible
 *			0 if omap module's registers NOT accessible
 *			(or in case of error)
 * @param[in]		id: valid module ID
 * @DESCRIPTION		check omap module's registers accessibility
 *//*------------------------------------------------------------------------ */
unsigned short int mod54xx_is_accessible(mod54xx_id id)
{
	reg *cm_clkctrl_reg;
	unsigned int cm_clkctrl;

	if (!cpu_is_omap54xx()) {
		fprintf(stderr, "%s(): CPU != 54XX\n", __func__);
		return 0;
	}
	if (id >= MOD54XX_ID_MAX) {
		fprintf(stderr, "%s(): id=%u >= MOD54XX_ID_MAX (%u)\n",
			__func__, id, MOD54XX_ID_MAX);
		return 0;
	}

	cm_clkctrl_reg = mod54xx_cm_clkctrl_reg_get(id);
	if (cm_clkctrl_reg == NULL) {
		dprintf("%s(): cm_clkctrl_reg == NULL!!!\n", __func__);
		return 0;
	}
	cm_clkctrl = reg_read(cm_clkctrl_reg);
	return mod_is_accessible(cm_clkctrl);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_cm_clkctrl_reg_get
 * @BRIEF		return pointer to module's CM_XYZ_CLKCTRL reg
 * @RETURNS		pointer to module's CM_XYZ_CLKCTRL reg
 *			NULL in case of error
 * @param[in]		id: valid module ID
 * @DESCRIPTION		return pointer to module's CM_XYZ_CLKCTRL reg
 *//*------------------------------------------------------------------------ */
reg *mod54xx_cm_clkctrl_reg_get(mod54xx_id id)
{
	if (!cpu_is_omap54xx())
		return NULL;
	CHECK_ARG_LESS_THAN(id, MOD54XX_ID_MAX, NULL);

	return mod54xx_cm_clkctrl_reg_table[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_rm_context_reg_get
 * @BRIEF		return pointer to module's RM_XYZ_CONTEXT reg
 * @RETURNS		pointer to module's RM_XYZ_CONTEXT reg
 *			NULL in case of error
 * @param[in]		id: valid module ID
 * @DESCRIPTION		return pointer to module's RM_XYZ_CONTEXT reg
 *//*------------------------------------------------------------------------ */
reg *mod54xx_rm_context_reg_get(mod54xx_id id)
{
	if (!cpu_is_omap54xx())
		return NULL;
	CHECK_ARG_LESS_THAN(id, MOD54XX_ID_MAX, NULL);

	return mod54xx_rm_context_reg_table[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_sysconfig_reg_get
 * @BRIEF		return pointer to module's sysconfig reg
 * @RETURNS		pointer to module's sysconfig reg
 *			NULL in case of error
 * @param[in]		id: valid module ID
 * @DESCRIPTION		return pointer to module's sysconfig reg
 *//*------------------------------------------------------------------------ */
reg *mod54xx_sysconfig_reg_get(mod54xx_id id)
{
	if (!cpu_is_omap54xx())
		return NULL;
	CHECK_ARG_LESS_THAN(id, MOD54XX_ID_MAX, NULL);

	return mod54xx_sysconfig_table[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_autoidle_mode_get
 * @BRIEF		retrieve omap module's autoidle mode
 * @RETURNS		module's autoidle mode
 *			MOD_AUTOIDLE_MODE_MAX in case of error
 * @param[in]		id: valid module ID
 * @DESCRIPTION		retrieve omap module's autoidle mode
 *//*------------------------------------------------------------------------ */
mod_autoidle_mode mod54xx_autoidle_mode_get(mod54xx_id id)
{
	reg *sysconfig;
	unsigned int val = 0;
	mod_autoidle_mode mode;
	unsigned int mprop;

	if (!cpu_is_omap54xx())
		return MOD_AUTOIDLE_MODE_MAX;
	CHECK_ARG_LESS_THAN(id, MOD54XX_ID_MAX, MOD_AUTOIDLE_MODE_MAX);
	if (!mod54xx_is_accessible(id))
		return MOD_AUTOIDLE_MODE_MAX;
	if (!mod54xx_has_autoidle_bit(id))
		return MOD_AUTOIDLE_MODE_MAX;
	sysconfig = mod54xx_sysconfig_reg_get(id);
	CHECK_NULL_ARG(sysconfig, MOD_AUTOIDLE_MODE_MAX);

	val = reg_read(sysconfig);
	mprop = mod54xx_properties_get(id);
	if ((mprop & MOD_HAS_AUTOIDLE_BIT0) != 0) {
		mode = (mod_autoidle_mode) extract_bit(val, 0);
		dprintf("%s(): SYSCONFIG ADDR = 0x%08X SYSCONFIG = 0x%08X "
			"POS=0 AUTOIDLE MODE=%u (%s)\n", __func__,
			sysconfig->addr, val, mode,
			mod_autoidle_mode_name_get(mode));
	} else if ((mprop & MOD_HAS_AUTOIDLE_BIT8) != 0) {
		/*
		 * NB: AUTOGATINGDISABLE instead of AUTOGATING,
		 * bit is inverted compared to other modules ...
		 */
		mode = (mod_autoidle_mode) !extract_bit(val, 8);
		dprintf("%s(): SYSCONFIG ADDR = 0x%08X SYSCONFIG = 0x%08X "
			"POS=8 AUTOIDLE MODE=%u (%s)\n", __func__,
			sysconfig->addr, val, mode,
			mod_autoidle_mode_name_get(mode));
	} else {
		fprintf(stderr, "%s(%u): ?!?!?!?!\n", __func__, id);
		mode = MOD_AUTOIDLE_MODE_MAX;
	}

	return mode;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_idle_mode_get
 * @BRIEF		retrieve omap module's idle mode
 * @RETURNS		module's idle mode
 *			MOD_IDLE_MODE_MAX in case of error
 * @param[in]		id: valid module ID
 * @DESCRIPTION		retrieve omap module's idle mode
 *//*------------------------------------------------------------------------ */
mod_idle_mode mod54xx_idle_mode_get(mod54xx_id id)
{
	reg *sysconfig;
	unsigned int val = 0;
	mod_idle_mode mode;
	unsigned int mprop;


	if (!cpu_is_omap54xx())
		return MOD_IDLE_MODE_MAX;
	CHECK_ARG_LESS_THAN(id, MOD54XX_ID_MAX, MOD_IDLE_MODE_MAX);
	if (!mod54xx_is_accessible(id))
		return MOD_IDLE_MODE_MAX;
	if (!mod54xx_has_idle_mode(id))
		return MOD_IDLE_MODE_MAX;
	sysconfig = mod54xx_sysconfig_reg_get(id);
	CHECK_NULL_ARG(sysconfig, MOD_IDLE_MODE_MAX);

	val = reg_read(sysconfig);
	mprop = mod54xx_properties_get(id);
	if ((mprop & MOD_HAS_IDLE_MODE1) != 0) {
		mode = (mod_idle_mode) extract_bitfield(val, 0, 2);
		dprintf("%s(): SYSCONFIG ADDR = 0x%08X SYSCONFIG = 0x%08X "
			"POS=[1-0] IDLE MODE=%u (%s)\n", __func__,
			sysconfig->addr, val, mode,
			mod_idle_mode_name_get(mode));
	} else if ((mprop & MOD_HAS_IDLE_MODE3) != 0) {
		mode = (mod_idle_mode) extract_bitfield(val, 2, 2);
		dprintf("%s(): SYSCONFIG ADDR = 0x%08X SYSCONFIG = 0x%08X "
			"POS=[3-2] IDLE MODE=%u (%s)\n", __func__,
			sysconfig->addr, val, mode,
			mod_idle_mode_name_get(mode));
	} else if ((mprop & MOD_HAS_IDLE_MODE4) != 0) {
		mode = (mod_idle_mode) extract_bitfield(val, 3, 2);
		dprintf("%s(): SYSCONFIG ADDR = 0x%08X SYSCONFIG = 0x%08X "
			"POS=[4-3] IDLE MODE=%u (%s)\n", __func__,
			sysconfig->addr, val, mode,
			mod_idle_mode_name_get(mode));
	} else {
		fprintf(stderr, "%s(%u): ?!?!?!?!\n", __func__, id);
		mode = MOD_AUTOIDLE_MODE_MAX;
	}

	return mode;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_standby_mode_get
 * @BRIEF		retrieve omap module's standby mode
 * @RETURNS		module's standby mode
 *			MOD_STANDBY_MODE_MAX in case of error
 * @param[in]		id: valid module ID
 * @DESCRIPTION		retrieve omap module's standby mode
 *//*------------------------------------------------------------------------ */
mod_standby_mode mod54xx_standby_mode_get(mod54xx_id id)
{
	reg *sysconfig;
	unsigned int val = 0;
	mod_standby_mode mode;
	unsigned int mprop;

	if (!cpu_is_omap54xx())
		return MOD_STANDBY_MODE_MAX;
	CHECK_ARG_LESS_THAN(id, MOD54XX_ID_MAX, MOD_STANDBY_MODE_MAX);
	if (!mod54xx_is_accessible(id))
		return MOD_STANDBY_MODE_MAX;
	if (!mod54xx_has_standby_mode(id))
		return MOD_STANDBY_MODE_MAX;
	sysconfig = mod54xx_sysconfig_reg_get(id);
	CHECK_NULL_ARG(sysconfig, MOD_STANDBY_MODE_MAX);

	val = reg_read(sysconfig);
	mprop = mod54xx_properties_get(id);
	if ((mprop & MOD_HAS_STANDBY_MODE5) != 0) {
		mode = (mod_standby_mode) extract_bitfield(val, 4, 2);
		dprintf("%s(): SYSCONFIG ADDR = 0x%08X SYSCONFIG = 0x%08X "
			"POS=[5-4] STANDBY MODE=%u (%s)\n", __func__,
			sysconfig->addr, val, mode,
			mod_standby_mode_name_get(mode));
	} else if ((mprop & MOD_HAS_STANDBY_MODE13) != 0) {
		mode = (mod_standby_mode) extract_bitfield(val, 12, 2);
		dprintf("%s(): SYSCONFIG ADDR = 0x%08X SYSCONFIG = 0x%08X "
			"POS=[13-12] STANDBY MODE=%u (%s)\n", __func__,
			sysconfig->addr, val, mode,
			mod_standby_mode_name_get(mode));
	} else {
		fprintf(stderr, "%s(%u): ?!?!?!?!\n", __func__, id);
		mode = MOD_AUTOIDLE_MODE_MAX;
	}

	return mode;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_clock_activity_mode_get
 * @BRIEF		retrieve omap module's clock activity mode
 * @RETURNS		module's clock activity mode
 *			MOD_CLOCK_ACTIVITY_MODE_MAX in case of error
 * @param[in]		id: valid module ID
 * @DESCRIPTION		retrieve omap module's clock activity mode
 *//*------------------------------------------------------------------------ */
mod_clock_activity_mode mod54xx_clock_activity_mode_get(mod54xx_id id)
{
	reg *sysconfig;
	unsigned int val = 0;
	mod_clock_activity_mode mode;

	if (!cpu_is_omap54xx())
		return MOD_CLOCK_ACTIVITY_MODE_MAX;
	CHECK_ARG_LESS_THAN(id, MOD54XX_ID_MAX, MOD_CLOCK_ACTIVITY_MODE_MAX);
	if (!mod54xx_is_accessible(id))
		return MOD_CLOCK_ACTIVITY_MODE_MAX;
	if (!mod54xx_has_clock_activity_mode(id))
		return MOD_CLOCK_ACTIVITY_MODE_MAX;
	sysconfig = mod54xx_sysconfig_reg_get(id);
	CHECK_NULL_ARG(sysconfig, MOD_CLOCK_ACTIVITY_MODE_MAX);

	val = reg_read(sysconfig);
	mode = (mod_clock_activity_mode) extract_bitfield(val, 8, 2);
	dprintf("%s(): SYSCONFIG ADDR = 0x%08X SYSCONFIG = 0x%08X "
		"POS=[9-8] CLOCK ACTIVITY MODE=%u (%s)\n", __func__,
		sysconfig->addr, val, mode,
		mod_clock_activity_mode_name_get(mode));

	return mode;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_context_is_lost
 * @BRIEF		check if module's context was retained or lost
 *			during last power transition
 * @RETURNS		1 if module's context was LOST during last power
 *			transition (or in case of error)
 *			0 if module's context was RETAINED during last power
 *			transition
 *			-1 in case of error or module has no context register
 * @param[in]		id: valid module ID
 * @DESCRIPTION		check if module's context was retained or lost
 *			during last power transition
 *//*------------------------------------------------------------------------ */
int mod54xx_context_is_lost(mod54xx_id id)
{
	reg *rm_context_reg;
	unsigned int rm_context;

	if (!cpu_is_omap54xx())
		return -1;
	CHECK_ARG_LESS_THAN(id, MOD54XX_ID_MAX, -1);

	/* Get module's CONTEXT register pointer */
	rm_context_reg = mod54xx_rm_context_reg_get(id);
	if (rm_context_reg == NULL) {
		dprintf("%s(%u (%s)): %s addr==NULL\n", __func__, id,
			mod54xx_name_get(id), reg_name_get(rm_context_reg));
		return -1;
	}
	/* Read register */
	rm_context = reg_read(rm_context_reg);
	if (rm_context == 0) {
		/* All memory bank(s) were retained */
		dprintf("%s(%u (%s)): %s addr=0x%08X val=0x%08X "
			"=> context is RETAINED\n", __func__, id,
			mod54xx_name_get(id), reg_name_get(rm_context_reg),
			reg_addr_get(rm_context_reg), rm_context);
		return 0;
	} else {
		/* At least 1 memory bank was lost */
		dprintf("%s(%u (%s)): %s addr=0x%08X val=0x%08X "
			"=> context is LOST\n", __func__, id,
			mod54xx_name_get(id), reg_name_get(rm_context_reg),
			reg_addr_get(rm_context_reg), rm_context);
		return 1;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_config_show
 * @BRIEF		analyze module power configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output file
 * @param[in]		id: valid module ID
 * @DESCRIPTION		analyze module power configuration
 *//*------------------------------------------------------------------------ */
int mod54xx_config_show(FILE *stream, mod54xx_id id)
{
	unsigned int cm_clkctrl;
	reg *cm_clkctrl_reg;
	char s[72];
	int ret;
	mod_idle_status idlest;
	mod_standby_status standbyst;
	clk54xx_id src_clk_id;
	double rate;
	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(id, MOD54XX_ID_MAX, OMAPCONF_ERR_ARG);

	/* Get module's CLKCTRL register pointer */
	cm_clkctrl_reg = mod54xx_cm_clkctrl_reg_get(id);
	if (cm_clkctrl_reg == NULL)
		/* Nothing to show */
		return 0;
	/* Read register */
	cm_clkctrl = reg_read(cm_clkctrl_reg);

	/* Decode and display module's power configuration */
	fprintf(stream, "|-----------------------------------------------------"
		"-------------------|\n");
	strcpy(s, mod54xx_name_get(id));
	strcat(s, " Module Configuration");
	fprintf(stream, "| %-70s |\n", s);
	fprintf(stream, "|----------------------------------|------------------"
		"-------------------|\n");

	/* F-Clock Source & Rate */
	src_clk_id = mod54xx_clk_get(id);
	if (src_clk_id != CLK54XX_ID_MAX) {
		fprintf(stream, "| %-32s | %-35s |\n", "Source Clock",
			clk54xx_name_get(src_clk_id));

		rate = mod54xx_clk_rate_get(id, 1);
		if (rate < 0.0)
			strcpy(s, "Unknown");
		else if (rate < 1.0)
			sprintf(s, "%lfMHz", rate);
		else
			sprintf(s, "%.3lfMHz", rate);
		fprintf(stream, "| %-32s | %-35s |\n", "Source Clock Rate", s);
	} else {
		fprintf(stream, "| %-32s | %-35s |\n", "Source Clock",
			"Unknown");
		fprintf(stream, "| %-32s | %-35s |\n", "Source Clock Rate",
			"Unknown");
	}

	/* Module Mode */
	fprintf(stream, "| %-32s | %-35s |\n", "Mode",
		mod_module_mode_name_get(mod54xx_mode_get(id)));


	/* Idle Status */
	idlest = mod54xx_idle_status_get(id);
	if (idlest == MOD_IDLE_STATUS_MAX)
		fprintf(stream, "| %-32s | %-35s |\n", "Idle Status",
			"Not Available (does not exist)");
	else
		fprintf(stream, "| %-32s | %-35s |\n", "Idle Status",
			mod_idle_status_name_get(idlest));

	/* Standby Status */
	standbyst = mod54xx_standby_status_get(id);
	if (standbyst == MOD_STANDBY_STATUS_MAX)
		fprintf(stream, "| %-32s | %-35s |\n", "Standby Status",
			"Not Available (does not exist)");
	else
		fprintf(stream, "| %-32s | %-35s |\n", "Standby Status",
			mod_standby_status_name_get(standbyst));

	/* FCLK Source / Optional Clocks */
	switch (id) {
	case OMAP5_DEBUGSS:
		break;

	/* Voltage dom.: WKUP: Power dom.: WKUPAON: Clock domain = WKUPAON */
	case OMAP5_CTRL_MODULE_WKUP:
	case OMAP5_L4WKUP_INTERCONNECT:
	case OMAP5_WD_TIMER2:
	case OMAP5_COUNTER_32K:
	case OMAP5_SARRAM:
	case OMAP5_KBD:
		break;

	case OMAP5_GPIO1:
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional debounce clock",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	case OMAP5_TIMER1:
		fprintf(stream, "| %-32s | %-35s |\n", "FCLK Source",
			((extract_bit(cm_clkctrl, 24) == 1) ?
				"32KHz" : "SYS_CLK"));
		break;

	case OMAP5_IO_SRCOMP_WKUP:
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional functional clock",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	/* HS/EMU ONLY */
	case OMAP5_TIMER12:
	case OMAP5_WDT1:
		break;

	/* Voltage dom.: CORE: Power dom.: COREAON: Clock domain = COREAON */
	case OMAP5_SMARTREFLEX_CORE:
	case OMAP5_SMARTREFLEX_MM:
	case OMAP5_SMARTREFLEX_MPU:
		break;

	case OMAP5_BANDGAPTS:
		rate = clk54xx_rate_get(CLK54XX_WKUPAON_GICLK, 0);
		rate /= (double)
			(1 << (3 + extract_bitfield(cm_clkctrl, 24, 2)));
		sprintf(s, "%lfMHz (WKUPAON_ICLK / %-2u)", rate,
			1 << (3 + extract_bitfield(cm_clkctrl, 24, 2)));
		fprintf(stream, "| %-32s | %-35s |\n",
			"TS F-Clock Rate (MHz)", s);
		fprintf(stream, "| %-32s | %-35s |\n", "",
			"  (1MHz < expected rate < 2MHz)");
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional functional clock",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	case OMAP5_IO_SRCOMP_CORE:
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional functional clock",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	case OMAP5_USB_PHY_CORE:
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional functional clock",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	/* Voltage dom.: CORE: Power dom.: CAM: Clock domain = CAM */
	case OMAP5_FDIF:
		fprintf(stream, "| %-32s | %-35s |\n", "FDIF_CLK Ratio",
			((extract_bit(cm_clkctrl, 24) == 1) ?
				"FDIF_CLK = FUNC_128M_CLK / 2" :
				"FDIF_CLK = FUNC_128M_CLK / 1"));
		break;

	case OMAP5_ISS:
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional functional clock",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	case OMAP5_CAL:
		break;

	/* Voltage dom.: CORE: Power dom.: CORE: Clock domain = L4CFG */
	case OMAP5_CTRL_MODULE_CORE:
	case OMAP5_SPINLOCK:
	case OMAP5_L4_CFG_INTERCONNECT:
	case OMAP5_MAILBOX:
	case OMAP5_SARROM:
	case OMAP5_OCP2SCP2:
		break;

	/* Voltage dom.: CORE: Power dom.: CORE: Clock domain = EMIF */
	case OMAP5_PHY_EMIF:
	case OMAP5_DMM:
	case OMAP5_EMIF1:
	case OMAP5_EMIF2:
	case OMAP5_EMIF_OCP_FW:
		break;

	case OMAP5_DLL_EMIF:
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional functional clock",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	/* Voltage dom.: CORE: Power dom.: CORE: Clock domain = IPU */
	case OMAP5_IPU:
		break;

	/* Voltage dom.: CORE: Power dom.: CORE: Clock domain = L3_MAIN2 */
	case OMAP5_GPMC:
	case OMAP5_L3_MAIN2_INTERCONNECT:
	case OMAP5_OCMC_RAM:
		break;

	/* Voltage dom.: CORE: Power dom.: CORE: Clock domain = L3_INSTR */
	case OMAP5_L3_MAIN3_INTERCONNECT:
	case OMAP5_L3_INSTR_INTERCONNECT:
	case OMAP5_OCP_WP_NOC:
		break;

	/* Voltage dom.: CORE: Power dom.: CORE: Clock domain = L3_MAIN1 */
	case OMAP5_L3_MAIN1_INTERCONNECT:
		break;

	/* Voltage dom.: CORE: Power dom.: CORE: Clock domain = C2C */
	case OMAP5_C2C:
	case OMAP5_C2C_OCP_FW:
	case OMAP5_MODEM_ICR:
		break;

	/* Voltage dom.: CORE: Power dom.: CORE: Clock domain = DMA */
	case OMAP5_DMA_SYSTEM:
		break;

	/* Voltage dom.: CORE: Power dom.: CORE: Clock domain = MIPIEXT */
	case OMAP5_LLI:
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional functional clocks:", "");
		fprintf(stream, "| %-32s | %-35s |\n", "  TXPHY_LS_CLK",
			((extract_bit(cm_clkctrl, 9) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  TXPHY_CLK",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	case OMAP5_LLI_OCP_FW:
	case OMAP5_MPHY:
		break;

	case OMAP5_UNIPRO1:
		fprintf(stream, "| %-32s | %-35s |\n",
			"Internal Timer Clock Ratio",
			((extract_bit(cm_clkctrl, 24) == 1) ?
				"= MIPIEXT_L3_GICLK / 2" :
				"= MIPIEXT_L3_GICLK / 1"));
		break;

	/* Voltage dom.: CORE: Power dom.: DSS: Clock domain = DSS */
	case OMAP5_DSS:
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional functional clocks:", "");
		fprintf(stream, "| %-32s | %-35s |\n", "  32KHz",
			((extract_bit(cm_clkctrl, 11) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  SYS_CLK",
			((extract_bit(cm_clkctrl, 10) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  48MHz_CLK",
			((extract_bit(cm_clkctrl, 9) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  DSSCLK",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	case OMAP5_BB2D:
		break;

	/* Voltage dom.: CORE: Power dom.: L3INIT: Clock domain = L3INIT */
	case OMAP5_HSI:
		fprintf(stream, "| %-32s | %-35s |\n", "FCLK Source",
			((extract_bit(cm_clkctrl, 24) == 1) ?
				"= HSI_FCLK (192MHz) / 2" :
				"= HSI_FCLK (192MHz) / 1"));
		break;

	case OMAP5_IEEE1500_2_OCP:
	case OMAP5_OCPSCP1:
	case OMAP5_MPHY_UNIPRO2:
	case OMAP5_OCPSCP3:
		break;

	case OMAP5_MMC1:
		fprintf(stream, "| %-32s | %-35s |\n", "Clock Ratio",
			((extract_bit(cm_clkctrl, 25) == 1) ?
				"2" : "1"));
		fprintf(stream, "| %-32s | %-35s |\n", "FCLK Source",
			((extract_bit(cm_clkctrl, 24) == 1) ?
				"DPLL_PER 192MHz" : "DPLL_PER 128MHz"));
		break;

	case OMAP5_MMC2:
		fprintf(stream, "| %-32s | %-35s |\n", "Clock Ratio",
			((extract_bit(cm_clkctrl, 25) == 1) ?
				"2" : "1"));
		fprintf(stream, "| %-32s | %-35s |\n", "FCLK Source",
			((extract_bit(cm_clkctrl, 24) == 1) ?
				"DPLL_PER 192MHz" : "DPLL_PER 128MHz"));
		break;

	case OMAP5_USB_HOST_HS:
		fprintf(stream, "| %-32s | %-35s |\n", "UTMI Port2 Source",
			((extract_bit(cm_clkctrl, 25) == 1) ?
				"External PHY" : "internal"));
		fprintf(stream, "| %-32s | %-35s |\n", "UTMI Port1 Source",
			((extract_bit(cm_clkctrl, 24) == 1) ?
				"External PHY" : "internal"));

		fprintf(stream, "| %-32s | %-35s |\n", "SAR MODE",
			((extract_bit(cm_clkctrl, 4) == 1) ?
				"Enabled" : "Disabled"));

		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional functional clocks:", "");
		fprintf(stream, "| %-32s | %-35s |\n", "  FUNC_48M_GFCLK",
			((extract_bit(cm_clkctrl, 15) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  HSIC_P2_480M_GFCLK",
			((extract_bit(cm_clkctrl, 14) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  HSIC_P1_480M_GFCLK",
			((extract_bit(cm_clkctrl, 13) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  HSIC_P2_60M_GFCLK",
			((extract_bit(cm_clkctrl, 12) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  HSIC_P1_60M_GFCLK",
			((extract_bit(cm_clkctrl, 11) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  UTMI_P3_GFCLK",
			((extract_bit(cm_clkctrl, 10) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  UTMI_P2_GFCLK",
			((extract_bit(cm_clkctrl, 9) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  UTMI_P1_GFCLK",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  HSIC_P3_480M_GFCLK",
			((extract_bit(cm_clkctrl, 7) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  HSIC_P3_60M_GFCLK",
			((extract_bit(cm_clkctrl, 6) == 1) ?
				"Enabled" : "Disabled"));
		break;

	case OMAP5_USB_OTG_SS:
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional 960MHz REF_CLK",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	case OMAP5_USB_TLL_HS:
		fprintf(stream, "| %-32s | %-35s |\n", "SAR MODE",
			((extract_bit(cm_clkctrl, 4) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional functional clocks:", "");
		fprintf(stream, "| %-32s | %-35s |\n", "  USB_CH2_CLK",
			((extract_bit(cm_clkctrl, 10) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  USB_CH1_CLK",
			((extract_bit(cm_clkctrl, 9) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  USB_CH0_CLK",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	case OMAP5_SATA:
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional functional REF_CLK",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	case OMAP5_UNIPRO2:
		fprintf(stream, "| %-32s | %-35s |\n",
			"Internal Timer Clock Ratio",
			((extract_bit(cm_clkctrl, 24) == 1) ?
				"= L3INIT_L3_GICLK / 2" :
				"= L3INIT_L3_GICLK / 1"));
		break;

	/* Voltage dom.: CORE: Power dom.: L4_PER: Clock domain = L4_PER */
	case OMAP5_TIMER10:
	case OMAP5_TIMER11:
	case OMAP5_TIMER2:
	case OMAP5_TIMER3:
	case OMAP5_TIMER4:
	case OMAP5_TIMER9:
		fprintf(stream, "| %-32s | %-35s |\n", "FCLK Source",
			((extract_bit(cm_clkctrl, 24) == 1) ?
				"32KHz" : "SYS_CLK"));
		break;

	case OMAP5_GPIO2:
	case OMAP5_GPIO3:
	case OMAP5_GPIO4:
	case OMAP5_GPIO5:
	case OMAP5_GPIO6:
	case OMAP5_GPIO7:
	case OMAP5_GPIO8:
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional debounce clock",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	case OMAP5_ELM:
	case OMAP5_HDQ1W:
	case OMAP5_I2C1:
	case OMAP5_I2C2:
	case OMAP5_I2C3:
	case OMAP5_I2C4:
	case OMAP5_I2C5:
	case OMAP5_L4_PER_INTERCONNECT:
	case OMAP5_MCSPI1:
	case OMAP5_MCSPI2:
	case OMAP5_MCSPI3:
	case OMAP5_MCSPI4:
	case OMAP5_MMC3:
	case OMAP5_MMC4:
	case OMAP5_MMC5:
	case OMAP5_UART1:
	case OMAP5_UART2:
	case OMAP5_UART3:
	case OMAP5_UART4:
	case OMAP5_UART5:
	case OMAP5_UART6:
		break;

	case OMAP5_SLIMBUS2:
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional functional clocks:", "");
		fprintf(stream, "| %-32s | %-35s |\n", "  SLIMBUS",
			((extract_bit(cm_clkctrl, 10) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  PER_ABE_24M_GFCLK",
			((extract_bit(cm_clkctrl, 9) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  PER_24M_GFCLK",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	/* Voltage dom.: CORE: Power dom.: L4_PER: Clock domain = L4_SEC */
	/* HS/EMU ONLY */
	case OMAP5_DMA_CRYPTO:
	case OMAP5_AES1:
	case OMAP5_AES2:
	case OMAP5_SHA2MD5:
	case OMAP5_RNG:
	case OMAP5_DES3DES:
	case OMAP5_PKA:
		break;

	/* Voltage dom.: CORE: Power dom.: ABE: Clock domain = ABE */
	case OMAP5_AESS:
		sprintf(s, "%u", 1 << extract_bit(cm_clkctrl, 24));
		fprintf(stream, "| %-32s | %-35s |\n",
			"AESS_FCLK to ABE_CLK Ratio", s);
		break;

	case OMAP5_DMIC:
	case OMAP5_MCASP:
	case OMAP5_MCBSP1:
	case OMAP5_MCBSP2:
	case OMAP5_MCBSP3:
		switch (extract_bitfield(cm_clkctrl, 24, 2)) {
		case 0:
			switch (extract_bitfield(cm_clkctrl, 26, 2)) {
			case 0:
				fprintf(stream, "| %-32s | %-35s |\n",
					"FCLK Source", "24MHz from DPLL_ABE");
				break;
			case 1:
				fprintf(stream, "| %-32s | %-35s |\n",
					"FCLK Source", "ABE_SYSCLK");
				break;
			case 2:
				fprintf(stream, "| %-32s | %-35s |\n",
					"FCLK Source", "24MHz from DPLL_PER");
				break;
			default:
				fprintf(stream, "| %-32s | %-35s |\n",
					"FCLK Source", "Reserved!");
				break;
			}
			break;
		case 1:
			fprintf(stream, "| %-32s | %-35s |\n",
				"FCLK Source", "CLKS pad");
			break;
		case 2:
			fprintf(stream, "| %-32s | %-35s |\n",
				"FCLK Source", "Audio SLIMBUS pad");
			break;
		default:
			fprintf(stream, "| %-32s | %-35s |\n",
				"FCLK Source", "Reserved!");
			break;
		}
		break;

	case OMAP5_L4_ABE_INTERCONNECT:
	case OMAP5_MCPDM:
	case OMAP5_WD_TIMER3:
		break;

	case OMAP5_SLIMBUS1:
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional functional clocks:", "");
		fprintf(stream, "| %-32s | %-35s |\n", "  SLIMBUS",
			((extract_bit(cm_clkctrl, 11) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  FCLK2",
			((extract_bit(cm_clkctrl, 10) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  FCLK1",
			((extract_bit(cm_clkctrl, 9) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  FCLK0",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	case OMAP5_TIMER5:
	case OMAP5_TIMER6:
	case OMAP5_TIMER7:
	case OMAP5_TIMER8:
		fprintf(stream, "| %-32s | %-35s |\n", "FCLK Source",
			((extract_bit(cm_clkctrl, 24) == 1) ?
				"ABE_32K_CLK" : "ABE_SYS_CLK"));
		break;

	/* Voltage dom.: MM: Power dom.: DSP: Clock domain = DSP */
	case OMAP5_DSP:
		break;

	/* Voltage dom.: MM: Power dom.: GPU: Clock domain = GPU */
	case OMAP5_GPU:
		fprintf(stream, "| %-32s | %-35s |\n", "GPU_HYD_GCLK Source",
			((extract_bit(cm_clkctrl, 25) == 1) ?
				"DPLL_PER HS Div." : "DPLL_CORE HS Div."));
		fprintf(stream, "| %-32s | %-35s |\n", "GPU_CORE_GCLK Source",
			((extract_bit(cm_clkctrl, 24) == 1) ?
				"DPLL_PER HS Div." : "DPLL_CORE HS Div."));
		break;

	/* Voltage dom.: MM: Power dom.: IVA: Clock domain = IVA */
	case OMAP5_IVA:
	case OMAP5_SL2:
		break;

	/* Voltage dom.: MPU: Power dom.: MPUAON Clock domain = MPU */
	case OMAP5_MPU:
		fprintf(stream, "| %-32s | %-35s |\n",
			"MPU-ABE SS Bridge Ratio",
			((extract_bit(cm_clkctrl, 26) == 1) ? "16" : "8"));
		switch (extract_bitfield(cm_clkctrl, 24, 2)) {
		case 0:
		case 1:
			fprintf(stream, "| %-32s | %-35s |\n",
				"MPU-L3MAIN Interc. Bridge Ratio", "4");
			break;
		case 2:
		case 3:
			fprintf(stream, "| %-32s | %-35s |\n",
				"MPU-L3MAIN Interc. Bridge Ratio", "8");
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}

	/* Module Context */
	ret = mod54xx_context_is_lost(id);
	if (ret == -1)
		fprintf(stream, "| %-32s | %-35s |\n", "Context",
			"Not Available (does not exist)");
	else if (ret == 0)
		fprintf(stream, "| %-32s | %-35s |\n", "Context", "Retained");
	else
		fprintf(stream, "| %-32s | %-35s |\n", "Context", "Lost");


	fprintf(stream, "|-----------------------------------------------------"
		"-------------------|\n\n");

	return 0;
}
