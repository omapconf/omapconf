/*
 *
 * @Component			OMAPCONF
 * @Filename			prcm-module.c
 * @Description			OMAP PRCM Module APIs
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


#include <module.h>
#include <lib.h>
#include <string.h>
#include <module44xx.h>
#include <module54xx.h>
#include <cpuinfo.h>
#include <opp.h>


/* #define MOD_DEBUG */
#ifdef MOD_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static const char
	mod_autoidle_mode_names_table[MOD_AUTOIDLE_MODE_MAX][MODULE_MODES_MAX_NAME_LENGTH] = {
	"Free Running",
	"Autogating"};


static const char
	mod_idle_mode_names_table[MOD_IDLE_MODE_MAX][MODULE_MODES_MAX_NAME_LENGTH] = {
	"Force-Idle",
	"No Idle",
	"Smart-Idle",
	"Smart-Idle Wakeup"};


static const char
	mod_idle_status_names_table[MOD_IDLE_STATUS_MAX + 1][MODULE_MODES_MAX_NAME_LENGTH] = {
	"Full ON",
	"In Transition",
	"OCP-ONLY Idle",
	"Disabled (NO ACCESS)",
	"FIXME"};


static const char
	mod_standby_mode_names_table[MOD_STANDBY_MODE_MAX][MODULE_MODES_MAX_NAME_LENGTH] = {
	"Force-standby",
	"No standby",
	"Smart-Standby",
	"Reserved"};


static const char
	mod_standby_status_names_table[MOD_STANDBY_STATUS_MAX + 1][MODULE_MODES_MAX_NAME_LENGTH] = {
	"Functional",
	"In Standby",
	"FIXME"};


static const char
	mod_module_mode_names_table[MOD_MODULE_MODE_MAX][MODULE_MODES_MAX_NAME_LENGTH] = {
	"Disabled (NO ACCESS)",
	"HW-Auto",
	"Enabled (EXPLICITLY)",
	"Reserved"};


static const char
	mod_clock_activity_mode_names_table[MOD_CLOCK_ACTIVITY_MODE_MAX][MODULE_MODES_MAX_NAME_LENGTH] = {
	"F-CLK AUTO / I-CLK AUTO",
	"F-CLK AUTO / I-CLK ON",
	"F-CLK ON / I-CLK AUTO",
	"F-CLK ON / I-CLK ON"};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_module_mode_name_get
 * @BRIEF		return module mode name
 * @RETURNS		module mode name on success
 *			NULL otherwise
 * @param[in]		mode: valid module mode
 * @DESCRIPTION		return module mode name
 *//*------------------------------------------------------------------------ */
const char *mod_module_mode_name_get(mod_module_mode mode)
{
	CHECK_ARG_LESS_THAN(mode, MOD_MODULE_MODE_MAX, NULL);

	return mod_module_mode_names_table[mode];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_autoidle_mode_name_get
 * @BRIEF		return autoidle mode name
 * @RETURNS		autoidle mode name on success
 *			NULL otherwise
 * @param[in]		mode: valid autoidle mode
 * @DESCRIPTION		return autoidle mode name
 *//*------------------------------------------------------------------------ */
const char *mod_autoidle_mode_name_get(mod_autoidle_mode mode)
{
	CHECK_ARG_LESS_THAN(mode, MOD_AUTOIDLE_MODE_MAX, NULL);

	return mod_autoidle_mode_names_table[mode];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_idle_mode_name_get
 * @BRIEF		return idle mode name
 * @RETURNS		idle mode name on success
 *			NULL otherwise
 * @param[in]		mode: valid idle mode
 * @DESCRIPTION		return idle mode name
 *//*------------------------------------------------------------------------ */
const char *mod_idle_mode_name_get(mod_idle_mode mode)
{
	CHECK_ARG_LESS_THAN(mode, MOD_IDLE_MODE_MAX, NULL);


	return mod_idle_mode_names_table[mode];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_standby_mode_name_get
 * @BRIEF		return standby mode name
 * @RETURNS		standby mode name on success
 *			NULL otherwise
 * @param[in]		mode: valid standby mode
 * @DESCRIPTION		return standby mode name
 *//*------------------------------------------------------------------------ */
const char *mod_standby_mode_name_get(mod_standby_mode mode)
{
	CHECK_ARG_LESS_THAN(mode, MOD_STANDBY_MODE_MAX, NULL);

	return mod_standby_mode_names_table[mode];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_clock_activity_mode_name_get
 * @BRIEF		return clock activity mode name
 * @RETURNS		clock activity mode name on success
 *			NULL otherwise
 * @param[in]		mode: valid clock activity mode
 * @DESCRIPTION		return clock activity mode name
 *//*------------------------------------------------------------------------ */
const char *mod_clock_activity_mode_name_get(mod_clock_activity_mode mode)
{
	CHECK_ARG_LESS_THAN(mode, MOD_CLOCK_ACTIVITY_MODE_MAX, NULL);

	return mod_clock_activity_mode_names_table[mode];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_idle_status_name_get
 * @BRIEF		return module idle status name
 * @RETURNS		module idle status name on success
 *			NULL otherwise
 * @param[in]		status: valid module idle status
 * @DESCRIPTION		return module idle status name
 *//*------------------------------------------------------------------------ */
const char *mod_idle_status_name_get(mod_idle_status status)
{
	CHECK_ARG_LESS_THAN(status, MOD_IDLE_STATUS_MAX + 1, NULL);

	return mod_idle_status_names_table[status];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_standby_status_name_get
 * @BRIEF		return module standby status name
 * @RETURNS		module standby status name on success
 *			NULL otherwise
 * @param[in]		status: valid module standby status
 * @DESCRIPTION		return module standby status name
 *//*------------------------------------------------------------------------ */
const char *mod_standby_status_name_get(mod_standby_status status)
{
	CHECK_ARG_LESS_THAN(status, MOD_STANDBY_STATUS_MAX + 1, NULL);

	return mod_standby_status_names_table[status];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_is_accessible
 * @BRIEF		return 1 if module is running, 0 otherwise
 * @RETURNS		1 if module is running, 0 otherwise
 * @param[in]		cm_clkctrl: CM_XYZ_CLKCTRL register content
 * @DESCRIPTION		return 1 if module is running, 0 otherwise
 *//*------------------------------------------------------------------------ */
unsigned int mod_is_accessible(unsigned int cm_clkctrl)
{
	mod_module_mode mmode;
	mod_idle_status mstatus;

	/* Retrieve module mode */
	mmode = (mod_module_mode) extract_bitfield(cm_clkctrl, 0, 2);
	dprintf("%s(): CM_CLKCTRL=0x%08X MODULEMODE (bit [1-0])=%u (%s)\n",
		__func__, cm_clkctrl, mmode,
		mod_module_mode_name_get(mmode));

	if (mmode == MOD_DISABLED_MODE) {
		dprintf("%s(): module mode is disabled => NOT accessible\n",
			__func__);
		return 0;
	}

	/* Retrieve module idle status */
	mstatus = (mod_idle_status) extract_bitfield(cm_clkctrl, 16, 2);
	dprintf("%s(): IDLEST (bit [17-16]) = %u (%s)\n", __func__, mstatus,
		mod_idle_status_name_get(mstatus));
	switch (mstatus) {
	case MOD_FULL_ON:
		/* Module is fully functional, including OCP */
		dprintf("%s(): module is fully functional => accessible\n",
			__func__);
		return 1;

	case MOD_IN_TRANSITION:
		/*
		 * Module is performing transition: wakeup, or sleep,
		 * or sleep abortion.
		 * In case of sleep transition, transition may complete before
		 * the module is tentatively accessed, so it is safer to always
		 * consider module as non-accessible.
		 */
		dprintf(
			"%s(): module is performing transition: wakeup, or sleep, or sleep abortion => NOT accessible\n",
			__func__);
		return 0;

	case MOD_OCP_ONLY_IDLE:
		/*
		 * Module is in Idle mode (only OCP part). OCP clock can be
		 * re-enabled on access, so module is accessible.
		 */
		dprintf(
			"%s(): module is in Idle mode (only OCP part) => accessible\n",
			__func__);
		return 1;

	case MOD_DISABLED:
		/* Module is disabled and cannot be accessed. */
		dprintf(
			"%s(): module is disabled and cannot be accessed => NOT accessible\n",
			__func__);
		return 0;

	default:
		fprintf(stderr, "%s(): ?!?!?!?! => NOT accessible\n", __func__);
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_id_get
 * @BRIEF		return the platform-specific module ID corresponding to
 *			generic module name provided as argument.
 * @RETURNS		platform-specific module ID (>0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		mod: module name, as defined in module.h
 * @DESCRIPTION		return the platform-specific module ID corresponding to
 *			generic module name provided as argument.
 *//*------------------------------------------------------------------------ */
int mod_id_get(const char *mod)
{
	int mod_id;
	#ifdef MOD_DEBUG
	char name[MOD44XX_MAX_NAME_LENGTH];
	#endif

	/* FIXME: TACTICAL IMPLEMENTATION, NEED TO BE REWORKED/COMPLETED!!! */

	CHECK_NULL_ARG(mod, OMAPCONF_ERR_ARG);

	if (strcmp(mod, "MPU") == 0) {
		if (cpu_is_omap44xx())
			mod_id = (int) OMAP4_MPU;
		else if (cpu_is_omap54xx())
			mod_id = (int) OMAP5_MPU;
		else
			mod_id = (int) OMAPCONF_ERR_CPU;
	} else if (strcmp(mod, "IVA") == 0) {
		if (cpu_is_omap44xx())
			mod_id = (int) OMAP4_IVAHD;
		else if (cpu_is_omap54xx())
			mod_id = (int) OMAP5_IVA;
		else
			mod_id = (int) OMAPCONF_ERR_CPU;
	} else if (strcmp(mod, "DSP") == 0) {
		if (cpu_is_omap44xx())
			mod_id = (int) OMAP4_DSP;
		else if (cpu_is_omap54xx())
			mod_id = (int) OMAP5_DSP;
		else
			mod_id = (int) OMAPCONF_ERR_CPU;
	} else if (strcmp(mod, "GPU") == 0) {
		if (cpu_is_omap44xx())
			mod_id = (int) OMAP4_GFX;
		else if (cpu_is_omap54xx())
			mod_id = (int) OMAP5_GPU;
		else
			mod_id = (int) OMAPCONF_ERR_CPU;
	} else if (strcmp(mod, "AESS") == 0) {
		if (cpu_is_omap44xx())
			mod_id = (int) OMAP4_AESS;
		else if (cpu_is_omap54xx())
			mod_id = (int) OMAP5_AESS;
		else
			mod_id = (int) OMAPCONF_ERR_CPU;
	} else if (strcmp(mod, "L3") == 0) {
		if (cpu_is_omap44xx())
			mod_id = (int) OMAP4_L3_1;
		else if (cpu_is_omap54xx())
			mod_id = (int) OMAP5_L3_MAIN1_INTERCONNECT;
		else
			mod_id = (int) OMAPCONF_ERR_CPU;
	} else if (strcmp(mod, "L4") == 0) {
		if (cpu_is_omap44xx())
			mod_id = (int) OMAP4_L4_CFG;
		else if (cpu_is_omap54xx())
			mod_id = (int) OMAP5_L4_CFG_INTERCONNECT;
		else
			mod_id = (int) OMAPCONF_ERR_CPU;
	} else if (strcmp(mod, "EMIF") == 0) {
		if (cpu_is_omap44xx())
			mod_id = (int) OMAP4_EMIF1;
		else if (cpu_is_omap54xx())
			mod_id = (int) OMAP5_EMIF1;
		else
			mod_id = (int) OMAPCONF_ERR_CPU;
	} else if (strcmp(mod, "MEM") == 0) {
		if (cpu_is_omap44xx())
			mod_id = (int) OMAP4_DDRPHY;
		else if (cpu_is_omap54xx())
			mod_id = (int) OMAP5_PHY_EMIF;
		else
			mod_id = (int) OMAPCONF_ERR_CPU;
	} else if (strcmp(mod, "ISS") == 0) {
		if (cpu_is_omap44xx())
			mod_id = (int) OMAP4_ISS;
		else if (cpu_is_omap54xx())
			mod_id = (int) OMAP5_ISS;
		else
			mod_id = (int) OMAPCONF_ERR_CPU;
	} else if (strcmp(mod, "FDIF") == 0) {
		if (cpu_is_omap44xx())
			mod_id = (int) OMAP4_FDIF;
		else if (cpu_is_omap54xx())
			mod_id = (int) OMAP5_FDIF;
		else
			mod_id = (int) OMAPCONF_ERR_CPU;
	} else if (strcmp(mod, "CAL") == 0) {
		if (cpu_is_omap54xx())
			mod_id = (int) OMAP5_CAL;
		else
			mod_id = (int) OMAPCONF_ERR_CPU;
	} else if (strcmp(mod, "IPU") == 0) {
		if (cpu_is_omap44xx())
			mod_id = (int) OMAP4_MPU_M3;
		else if (cpu_is_omap54xx())
			mod_id = (int) OMAP5_IPU;
		else
			mod_id = (int) OMAPCONF_ERR_CPU;
	} else if (strcmp(mod, "DSS") == 0) {
		if (cpu_is_omap44xx())
			mod_id = (int) OMAP4_DISPC;
		else if (cpu_is_omap54xx())
			mod_id = (int) OMAP5_DSS;
		else
			mod_id = (int) OMAPCONF_ERR_CPU;
	} else if (strcmp(mod, "BB2D") == 0) {
		if (cpu_is_omap44xx())
			mod_id = (int) OMAP4_BB2D;
		else if (cpu_is_omap54xx())
			mod_id = (int) OMAP5_BB2D;
		else
			mod_id = (int) OMAPCONF_ERR_CPU;
	} else if (strcmp(mod, "HSI") == 0) {
		if (cpu_is_omap44xx())
			mod_id = (int) OMAP4_HSI;
		else if (cpu_is_omap54xx())
			mod_id = (int) OMAP5_HSI;
		else
			mod_id = (int) OMAPCONF_ERR_CPU;
	} else if (strcmp(mod, "C2C") == 0) {
		if (cpu_is_omap44xx())
			mod_id = (int) OMAP4_C2C;
		else if (cpu_is_omap54xx())
			mod_id = (int) OMAP5_C2C;
		else
			mod_id = (int) OMAPCONF_ERR_CPU;
	} else {
		mod_id = (int) OMAPCONF_ERR_NOT_AVAILABLE;
	}

	#ifdef MOD_DEBUG
	if (cpu_is_omap44xx())
		printf("%s(%s) = %d (%s)\n", __func__, mod, mod_id,
			mod44xx_get_name(mod_id, name));
	else if (cpu_is_omap54xx())
		printf("%s(%s) = %d (%s)\n", __func__, mod, mod_id,
			mod54xx_name_get(mod_id));
	#endif
	return mod_id;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_clk_rate_get
 * @BRIEF		return the module functional clock rate, in KHz.
 * @RETURNS		module functional clock rate, in KHz.
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		mod: module name, as defined in module.h
 * @DESCRIPTION		return the module functional clock rate, in KHz.
 *//*------------------------------------------------------------------------ */
int mod_clk_rate_get(const char *mod)
{
	int ret, mod_id, rate_khz;
	double rate_mhz;
	clock44xx_id clk_id;
	opp44xx_id opp_id;

	CHECK_NULL_ARG(mod, OMAPCONF_ERR_ARG);

	/* FIXME: TACTICAL IMPLEMENTATION, NEED TO BE REWORKED/COMPLETED!!! */

	mod_id = mod_id_get(mod);
	if (mod_id < 0) {
		dprintf("%s(%s): could not retrieve module ID! (%d)\n",
			__func__, mod, mod_id);
		rate_khz = mod_id;
	} else if (cpu_is_omap44xx()) {
		ret = mod44xx_get_clk_speed((mod44xx_id) mod_id,
			&clk_id, &opp_id, &rate_mhz);
		if (ret != 0) {
			dprintf(
				"%s(%s): could not retrieve module rate! (%d)\n",
				__func__, mod, ret);
			rate_khz = ret;
		} else {
			if (mod_id == OMAP4_DDRPHY)
				rate_mhz /= 2.0;
			rate_khz = mhz2khz(rate_mhz);
		}
	} else if (cpu_is_omap54xx()) {
		rate_mhz = mod54xx_clk_rate_get((mod54xx_id) mod_id, 1);
		if (rate_mhz < 0) {
			dprintf(
				"%s(%s): could not retrieve module rate! (%d)\n",
				__func__, mod, (int) rate_mhz);
			rate_khz = (int) rate_mhz;
		} else {
			rate_khz = mhz2khz(rate_mhz);
		}
	} else {
		fprintf(stderr, "omapconf: %s(): cpu not supported!!!\n",
			__func__);
		rate_khz = OMAPCONF_ERR_CPU;
	}

	dprintf("%s(%s) = %d KHz\n", __func__, mod, rate_khz);
	return rate_khz;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_mode_get
 * @BRIEF		return the module module.
 * @RETURNS		module module in case of success
 *			MOD_MODULE_MODE_MAX otherwise
 * @param[in]		mod: module name, as defined in module.h
 * @DESCRIPTION		return the module module.
 *//*------------------------------------------------------------------------ */
mod_module_mode mod_mode_get(const char *mod)
{
	mod_module_mode mmode;

	/* FIXME: TACTICAL IMPLEMENTATION, NEED TO BE REWORKED/COMPLETED!!! */

	CHECK_NULL_ARG(mod, MOD_MODULE_MODE_MAX);

	if (strcmp(mod, "MPU") == 0) {
		if (cpu_is_omap44xx())
			mod44xx_get_mode(OMAP4_MPU, &mmode);
		else if (cpu_is_omap54xx())
			mmode = mod54xx_mode_get(OMAP5_MPU);
		else
			mmode = MOD_MODULE_MODE_MAX;
	} else if (strcmp(mod, "IVA") == 0) {
		if (cpu_is_omap44xx())
			mod44xx_get_mode(OMAP4_IVAHD, &mmode);
		else if (cpu_is_omap54xx())
			mmode = mod54xx_mode_get(OMAP5_IVA);
		else
			mmode = MOD_MODULE_MODE_MAX;
	} else if (strcmp(mod, "DSP") == 0) {
		if (cpu_is_omap44xx())
			mod44xx_get_mode(OMAP4_DSP, &mmode);
		else if (cpu_is_omap54xx())
			mmode = mod54xx_mode_get(OMAP5_DSP);
		else
			mmode = MOD_MODULE_MODE_MAX;
	} else if (strcmp(mod, "GPU") == 0) {
		if (cpu_is_omap44xx())
			mod44xx_get_mode(OMAP4_GFX, &mmode);
		else if (cpu_is_omap54xx())
			mmode = mod54xx_mode_get(OMAP5_GPU);
		else
			mmode = MOD_MODULE_MODE_MAX;
	} else if (strcmp(mod, "AESS") == 0) {
		if (cpu_is_omap44xx())
			mod44xx_get_mode(OMAP4_AESS, &mmode);
		else if (cpu_is_omap54xx())
			mmode = mod54xx_mode_get(OMAP5_AESS);
		else
			mmode = MOD_MODULE_MODE_MAX;
	} else if (strcmp(mod, "L3") == 0) {
		if (cpu_is_omap44xx())
			mod44xx_get_mode(OMAP4_L3_1, &mmode);
		else if (cpu_is_omap54xx())
			mmode = mod54xx_mode_get(OMAP5_L3_MAIN1_INTERCONNECT);
		else
			mmode = MOD_MODULE_MODE_MAX;
	} else if (strcmp(mod, "L4") == 0) {
		if (cpu_is_omap44xx())
			mod44xx_get_mode(OMAP4_L4_CFG, &mmode);
		else if (cpu_is_omap54xx())
			mmode = mod54xx_mode_get(OMAP5_L4_CFG_INTERCONNECT);
		else
			mmode = MOD_MODULE_MODE_MAX;
	} else if (strcmp(mod, "EMIF") == 0) {
		if (cpu_is_omap44xx())
			mod44xx_get_mode(OMAP4_EMIF1, &mmode);
		else if (cpu_is_omap54xx())
			mmode = mod54xx_mode_get(OMAP5_EMIF1);
		else
			mmode = MOD_MODULE_MODE_MAX;
	} else if (strcmp(mod, "MEM") == 0) {
		if (cpu_is_omap44xx())
			mod44xx_get_mode(OMAP4_DDRPHY, &mmode);
		else if (cpu_is_omap54xx())
			mmode = mod54xx_mode_get(OMAP5_PHY_EMIF);
		else
			mmode = MOD_MODULE_MODE_MAX;
	} else if (strcmp(mod, "ISS") == 0) {
		if (cpu_is_omap44xx())
			mod44xx_get_mode(OMAP4_ISS, &mmode);
		else if (cpu_is_omap54xx())
			mmode = mod54xx_mode_get(OMAP5_ISS);
		else
			mmode = MOD_MODULE_MODE_MAX;
	} else if (strcmp(mod, "FDIF") == 0) {
		if (cpu_is_omap44xx())
			mod44xx_get_mode(OMAP4_FDIF, &mmode);
		else if (cpu_is_omap54xx())
			mmode = mod54xx_mode_get(OMAP5_FDIF);
		else
			mmode = MOD_MODULE_MODE_MAX;
	} else if (strcmp(mod, "CAL") == 0) {
		if (cpu_is_omap54xx())
			mmode = mod54xx_mode_get(OMAP5_CAL);
		else
			mmode = MOD_MODULE_MODE_MAX;
	} else if (strcmp(mod, "IPU") == 0) {
		if (cpu_is_omap44xx())
			mod44xx_get_mode(OMAP4_MPU_M3, &mmode);
		else if (cpu_is_omap54xx())
			mmode = mod54xx_mode_get(OMAP5_IPU);
		else
			mmode = MOD_MODULE_MODE_MAX;
	} else if (strcmp(mod, "DSS") == 0) {
		if (cpu_is_omap44xx())
			mod44xx_get_mode(OMAP4_DISPC, &mmode);
		else if (cpu_is_omap54xx())
			mmode = mod54xx_mode_get(OMAP5_DSS);
		else
			mmode = MOD_MODULE_MODE_MAX;
	} else if (strcmp(mod, "BB2D") == 0) {
		if (cpu_is_omap44xx())
			mod44xx_get_mode(OMAP4_BB2D, &mmode);
		else if (cpu_is_omap54xx())
			mmode = mod54xx_mode_get(OMAP5_BB2D);
		else
			mmode = MOD_MODULE_MODE_MAX;
	} else if (strcmp(mod, "HSI") == 0) {
		if (cpu_is_omap44xx())
			mod44xx_get_mode(OMAP4_HSI, &mmode);
		else if (cpu_is_omap54xx())
			mmode = mod54xx_mode_get(OMAP5_HSI);
		else
			mmode = MOD_MODULE_MODE_MAX;
	} else if (strcmp(mod, "C2C") == 0) {
		if (cpu_is_omap44xx())
			mod44xx_get_mode(OMAP4_C2C, &mmode);
		else if (cpu_is_omap54xx())
			mmode = mod54xx_mode_get(OMAP5_C2C);
		else
			mmode = MOD_MODULE_MODE_MAX;
	} else {
		mmode = MOD_MODULE_MODE_MAX;
	}

	dprintf("%s(%s) = %s\n", __func__, mod,
		mod_module_mode_name_get(mmode));
	return mmode;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_por_clk_rate_get
 * @BRIEF		return the recommended module functional clock rate,
 *			in KHz, for a given OPerating Point (OPP),
 *			as defined in Data Manual.
 * @RETURNS		module recommended functional clock rate, in KHz.
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		mod: module name, as defined in module.h
 * @DESCRIPTION		return the recommended module functional clock rate,
 *			in KHz, for a given OPerating Point (OPP),
 *			as defined in Data Manual.
 *//*------------------------------------------------------------------------ */
int mod_por_clk_rate_get(const char *mod, const char *opp)
{
	int ret, mod_id, opp_id, rate_khz;
	double rate_mhz;

	CHECK_NULL_ARG(mod, OMAPCONF_ERR_ARG);

	/* FIXME: TACTICAL IMPLEMENTATION, NEED TO BE REWORKED/COMPLETED!!! */

	mod_id = mod_id_get(mod);
	if (mod_id < 0) {
		dprintf("%s(%s): could not retrieve module ID! (%d)\n",
			__func__, mod, mod_id);
		rate_khz = mod_id;
		goto mod_por_clk_rate_get_end;
	}

	opp_id = opp_s2id(opp);
	if (opp_id < 0) {
		dprintf("%s(%s): could not retrieve OPP ID! (%d)\n",
			__func__, mod, opp_id);
		rate_khz = opp_id;
		goto mod_por_clk_rate_get_end;
	}

	if (cpu_is_omap44xx()) {
		ret = mod44xx_get_por_clk_speed((mod44xx_id) mod_id,
			(unsigned short) opp_id, &rate_mhz);
		if (ret < 0) {
			dprintf(
				"%s(%s): could not retrieve module POR rate! (%d)\n",
				__func__, mod, ret);
			rate_khz = ret;
		} else {
			rate_khz = mhz2khz(rate_mhz);
		}
	} else if (cpu_is_omap54xx()) {
		rate_mhz = mod54xx_por_clk_rate_get(
			(mod54xx_id) mod_id, (opp54xx_id) opp_id);
		if (rate_mhz < 0) {
			rate_khz = (int) rate_mhz;
			dprintf(
				"%s(%s): could not retrieve module POR rate! (%d)\n",
				__func__, mod, rate_khz);
		} else {
			rate_khz = mhz2khz(rate_mhz);
		}
	} else {
		fprintf(stderr, "omapconf: %s(): cpu not supported!!!\n",
			__func__);
		rate_khz = OMAPCONF_ERR_CPU;
	}

mod_por_clk_rate_get_end:
	dprintf("%s(%s) = %d KHz\n", __func__, mod, rate_khz);
	return rate_khz;
}
