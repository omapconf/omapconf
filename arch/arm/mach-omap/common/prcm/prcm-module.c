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


#include <prcm-module.h>
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
	mod_autoidle_mode_names_table[MOD_AUTOIDLE_MODE_MAX + 1][MODULE_MODES_MAX_NAME_LENGTH] = {
	"Free Running",
	"Autogating",
	"FIXME"};


static const char
	mod_idle_mode_names_table[MOD_IDLE_MODE_MAX + 1][MODULE_MODES_MAX_NAME_LENGTH] = {
	"Force-Idle",
	"No Idle",
	"Smart-Idle",
	"Smart-Idle Wakeup",
	"FIXME"};


static const char
	mod_idle_status_names_table[MOD_IDLE_STATUS_MAX + 1][MODULE_MODES_MAX_NAME_LENGTH] = {
	"Full ON",
	"In Transition",
	"OCP-ONLY Idle",
	"Disabled (NO ACCESS)",
	"FIXME"};


static const char
	mod_standby_mode_names_table[MOD_STANDBY_MODE_MAX + 1][MODULE_MODES_MAX_NAME_LENGTH] = {
	"Force-standby",
	"No standby",
	"Smart-Standby",
	"Reserved",
	"FIXME"};


static const char
	mod_standby_status_names_table[MOD_STANDBY_STATUS_MAX + 1][MODULE_MODES_MAX_NAME_LENGTH] = {
	"Functional",
	"In Standby",
	"FIXME"};


static const char
	mod_module_mode_names_table[MOD_MODULE_MODE_MAX + 1][MODULE_MODES_MAX_NAME_LENGTH] = {
	"Disabled (NO ACCESS)",
	"HW-Auto",
	"Enabled (EXPLICITLY)",
	"Reserved",
	"FIXME"};


static const char
	mod_clock_activity_mode_names_table[MOD_CLOCK_ACTIVITY_MODE_MAX + 1][MODULE_MODES_MAX_NAME_LENGTH] = {
	"F-CLK AUTO / I-CLK AUTO",
	"F-CLK AUTO / I-CLK ON",
	"F-CLK ON / I-CLK AUTO",
	"F-CLK ON / I-CLK ON",
	"FIXME"};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_module_mode_name_get
 * @BRIEF		return module mode name
 * @RETURNS		module mode name on success
 *			"FIXME" otherwise
 * @param[in]		mode: valid module mode
 * @DESCRIPTION		return module mode name
 *//*------------------------------------------------------------------------ */
const char *mod_module_mode_name_get(mod_module_mode mode)
{
	if (mode > MOD_MODULE_MODE_MAX)
		mode = MOD_MODULE_MODE_MAX;

	return mod_module_mode_names_table[mode];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_autoidle_mode_name_get
 * @BRIEF		return autoidle mode name
 * @RETURNS		autoidle mode name on success
 *			"FIXME" otherwise
 * @param[in]		mode: valid autoidle mode
 * @DESCRIPTION		return autoidle mode name
 *//*------------------------------------------------------------------------ */
const char *mod_autoidle_mode_name_get(mod_autoidle_mode mode)
{
	if (mode > MOD_AUTOIDLE_MODE_MAX)
		mode = MOD_AUTOIDLE_MODE_MAX;

	return mod_autoidle_mode_names_table[mode];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_idle_mode_name_get
 * @BRIEF		return idle mode name
 * @RETURNS		idle mode name on success
 *			"FIXME" otherwise
 * @param[in]		mode: valid idle mode
 * @DESCRIPTION		return idle mode name
 *//*------------------------------------------------------------------------ */
const char *mod_idle_mode_name_get(mod_idle_mode mode)
{
	if (mode > MOD_IDLE_MODE_MAX)
		mode = MOD_IDLE_MODE_MAX;

	return mod_idle_mode_names_table[mode];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_standby_mode_name_get
 * @BRIEF		return standby mode name
 * @RETURNS		standby mode name on success
 *			"FIXME" otherwise
 * @param[in]		mode: valid standby mode
 * @DESCRIPTION		return standby mode name
 *//*------------------------------------------------------------------------ */
const char *mod_standby_mode_name_get(mod_standby_mode mode)
{
	if (mode > MOD_STANDBY_MODE_MAX)
		mode = MOD_STANDBY_MODE_MAX;

	return mod_standby_mode_names_table[mode];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_clock_activity_mode_name_get
 * @BRIEF		return clock activity mode name
 * @RETURNS		clock activity mode name on success
 *			"FIXME" otherwise
 * @param[in]		mode: valid clock activity mode
 * @DESCRIPTION		return clock activity mode name
 *//*------------------------------------------------------------------------ */
const char *mod_clock_activity_mode_name_get(mod_clock_activity_mode mode)
{
	if (mode > MOD_CLOCK_ACTIVITY_MODE_MAX)
		mode = MOD_CLOCK_ACTIVITY_MODE_MAX;

	return mod_clock_activity_mode_names_table[mode];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_idle_status_name_get
 * @BRIEF		return module idle status name
 * @RETURNS		module idle status name on success
 *			"FIXME" otherwise
 * @param[in]		status: valid module idle status
 * @DESCRIPTION		return module idle status name
 *//*------------------------------------------------------------------------ */
const char *mod_idle_status_name_get(mod_idle_status status)
{
	if (status > MOD_IDLE_STATUS_MAX)
		status = MOD_IDLE_STATUS_MAX;

	return mod_idle_status_names_table[status];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_standby_status_name_get
 * @BRIEF		return module standby status name
 * @RETURNS		module standby status name on success
 *			"FIXME" otherwise
 * @param[in]		status: valid module standby status
 * @DESCRIPTION		return module standby status name
 *//*------------------------------------------------------------------------ */
const char *mod_standby_status_name_get(mod_standby_status status)
{
	if (status > MOD_STANDBY_STATUS_MAX)
		status = MOD_STANDBY_STATUS_MAX;

	return mod_standby_status_names_table[status];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_is_accessible
 * @BRIEF		return 1 if module is running, 0 otherwise
 * @RETURNS		1 if module is running, 0 otherwise
 * @param[in]		cm_clkctrl: CM_xxx_xxx_CLKCTRL register content
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
 * @FUNCTION		mod_module_mode_get
 * @BRIEF		return the module module mode.
 * @RETURNS		module mode in case of success
 *			MOD_MODULE_MODE_MAX otherwise
 * @param[in]		cm_clkctrl: CM_XYZ_CLKCTRL register content
 * @DESCRIPTION		return the module module mode.
 *//*------------------------------------------------------------------------ */
mod_module_mode mod_module_mode_get(unsigned int cm_clkctrl)
{
	mod_module_mode mmode;

	mmode = (mod_module_mode) extract_bitfield(cm_clkctrl, 0, 2);
	dprintf(
		"%s(): CM_CLKCTRL=0x%08X MODULEMODE (bit [1-0])=%u (%s)\n",
		__func__, cm_clkctrl, mmode,
		mod_module_mode_name_get(mmode));

	return mmode;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_idle_status_get
 * @BRIEF		retrieve module's idle status from CM_xxx_xxx_CLKCTRL
 * @RETURNS		module idle status
 *			MOD_IDLE_STATUS_MAX in case of error
 * @param[in]		cm_clkctrl: CM_xxx_xxx_CLKCTRL register content
 * @param[in]		properties: module properties
 * @DESCRIPTION		retrieve module's idle status from CM_xxx_xxx_CLKCTRL
 *//*------------------------------------------------------------------------ */
mod_idle_status mod_idle_status_get(
	unsigned int cm_clkctrl, unsigned int properties)
{
	mod_idle_status mstatus;

	if ((properties & MOD_HAS_NO_IDLE_STATUS) != 0) {
		dprintf("%s(): module HAS NO idle status (prop=%u)\n",
			__func__, properties);
		mstatus = MOD_IDLE_STATUS_MAX;
	} else {
		mstatus = (mod_idle_status) extract_bitfield(cm_clkctrl, 16, 2);
		dprintf(
			"%s(): CM_CLKCTRL=0x%08X, IDLEST (bit [17-16])=%u (%s)\n",
			__func__, cm_clkctrl, mstatus,
			mod_idle_status_name_get(mstatus));
	}

	return mstatus;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_standby_status_get
 * @BRIEF		retrieve module standby status from CM_xxx_xxx_CLKCTRL
 * @RETURNS		module standby status
 *			MOD_STANDBY_STATUS_MAX in case of error
 * @param[in]		cm_clkctrl: CM_xxx_xxx_CLKCTRL register content
 * @param[in]		properties: module properties
 * @DESCRIPTION		retrieve module standby status from CM_xxx_xxx_CLKCTRL
 *//*------------------------------------------------------------------------ */
mod_standby_status mod_standby_status_get(
	unsigned int cm_clkctrl, unsigned int properties)
{
	mod_standby_status mstatus;

	if ((properties & MOD_HAS_STANDBY_STATUS) != 0) {
		mstatus = (mod_standby_status) extract_bit(cm_clkctrl, 18);
		dprintf(
			"%s(): CM_CLKCTRL=0x%08X, STANDBYST (bit 18)=%u (%s)\n",
			__func__, cm_clkctrl, mstatus,
			mod_standby_status_name_get(mstatus));
	} else {
		dprintf("%s(): module does NOT have STANDBY status bit\n",
			__func__);
		mstatus = MOD_STANDBY_STATUS_MAX;
	}

	return mstatus;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_autoidle_mode_get
 * @BRIEF		retrieve module autoidle mode
 * @RETURNS		module autoidle mode
 *			MOD_AUTOIDLE_MODE_MAX in case of error
 * @param[in]		sysconfig: SYSCONFIG register content
 * @param[in]		properties: module properties
 * @DESCRIPTION		retrieve module autoidle mode
 *//*------------------------------------------------------------------------ */
mod_autoidle_mode mod_autoidle_mode_get(
	unsigned int sysconfig, unsigned int properties)
{
	mod_autoidle_mode mode;

	if ((properties & MOD_HAS_AUTOIDLE_BIT0) != 0) {
		mode = (mod_autoidle_mode) extract_bit(sysconfig, 0);
		dprintf(
			"%s(): SYSCONFIG=0x%08X POS=0 AUTOIDLE MODE=%u (%s)\n",
			__func__, sysconfig, mode,
			mod_autoidle_mode_name_get(mode));
	} else if ((properties & MOD_HAS_AUTOIDLE_BIT8) != 0) {
		/*
		 * NB: AUTOGATINGDISABLE instead of AUTOGATING,
		 * bit is inverted compared to other modules ...
		 */
		mode = (mod_autoidle_mode) !extract_bit(sysconfig, 8);
		dprintf("%s(): SYSCONFIG=0x%08X POS=8 AUTOIDLE MODE=%u (%s)\n",
			__func__, sysconfig, mode,
			mod_autoidle_mode_name_get(mode));
	} else {
		dprintf("%s(): MODULE DOES NOT HAVE AUTOIDLE MODE?! (%u)\n",
			__func__, properties);
		mode = MOD_AUTOIDLE_MODE_MAX;
	}

	return mode;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_idle_mode_get
 * @BRIEF		retrieve omap module's idle mode
 * @RETURNS		module's idle mode
 *			MOD_IDLE_MODE_MAX in case of error
 * @param[in]		sysconfig: SYSCONFIG register content
 * @param[in]		properties: module properties
 * @DESCRIPTION		retrieve omap module's idle mode
 *//*------------------------------------------------------------------------ */
mod_idle_mode mod_idle_mode_get(
	unsigned int sysconfig, unsigned int properties)
{
	mod_idle_mode mode;

	if ((properties & MOD_HAS_IDLE_MODE1) != 0) {
		mode = (mod_idle_mode) extract_bitfield(sysconfig, 0, 2);
		dprintf(
			"%s(): SYSCONFIG=0x%08X POS=[1-0] IDLE MODE=%u (%s)\n",
			__func__, sysconfig, mode,
			mod_idle_mode_name_get(mode));
	} else if ((properties & MOD_HAS_IDLE_MODE3) != 0) {
		mode = (mod_idle_mode) extract_bitfield(sysconfig, 2, 2);
		dprintf("%s(): SYSCONFIG=0x%08X POS=[3-2] IDLE MODE=%u (%s)\n",
			__func__, sysconfig, mode,
			mod_idle_mode_name_get(mode));
	} else if ((properties & MOD_HAS_IDLE_MODE4) != 0) {
		mode = (mod_idle_mode) extract_bitfield(sysconfig, 3, 2);
		dprintf("%s(): SYSCONFIG=0x%08X POS=[4-3] IDLE MODE=%u (%s)\n",
			__func__, sysconfig, mode,
			mod_idle_mode_name_get(mode));
	} else {
		dprintf("%s(): MODULE DOES NOT HAVE IDLE MODE?! (%u)\n",
			__func__, properties);
		mode = MOD_IDLE_MODE_MAX;
	}

	return mode;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_standby_mode_get
 * @BRIEF		retrieve omap module's standby mode
 * @RETURNS		module's standby mode
 *			MOD_STANDBY_MODE_MAX in case of error
 * @param[in]		sysconfig: SYSCONFIG register content
 * @param[in]		properties: module properties
 * @DESCRIPTION		retrieve omap module's standby mode
 *//*------------------------------------------------------------------------ */
mod_standby_mode mod_standby_mode_get(
	unsigned int sysconfig, unsigned int properties)
{
	mod_standby_mode mode;

	if ((properties & MOD_HAS_STANDBY_MODE5) != 0) {
		mode = (mod_standby_mode) extract_bitfield(sysconfig, 4, 2);
		dprintf(
			"%s(): SYSCONFIG=0x%08X POS=[5-4] STANDBY MODE=%u (%s)\n",
			__func__, sysconfig, mode,
			mod_standby_mode_name_get(mode));
	} else if ((properties & MOD_HAS_STANDBY_MODE13) != 0) {
		mode = (mod_standby_mode) extract_bitfield(sysconfig, 12, 2);
		dprintf(
			"%s(): SYSCONFIG=0x%08X POS=[13-12] STANDBY MODE=%u (%s)\n",
			__func__, sysconfig, mode,
			mod_standby_mode_name_get(mode));
	} else {
		dprintf("%s(): MODULE DOES NOT HAVE STANDBY MODE?! (%u)\n",
			__func__, properties);
		mode = MOD_STANDBY_MODE_MAX;
	}

	return mode;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_clock_activity_mode_get
 * @BRIEF		retrieve omap module's clock activity mode
 * @RETURNS		module's clock activity mode
 *			MOD_CLOCK_ACTIVITY_MODE_MAX in case of error
 * @param[in]		sysconfig: SYSCONFIG register content
 * @param[in]		properties: module properties
 * @DESCRIPTION		retrieve omap module's clock activity mode
 *//*------------------------------------------------------------------------ */
mod_clock_activity_mode mod_clock_activity_mode_get(
	unsigned int sysconfig, unsigned int properties)
{
	mod_clock_activity_mode mode;

	if ((properties & MOD_HAS_CLOCK_ACTIVITY_MODE) != 0) {
		mode = (mod_clock_activity_mode) extract_bitfield(sysconfig, 8, 2);
		dprintf(
			"%s(): SYSCONFIG=0x%08X POS=[9-8] CLOCK ACTIVITY MODE=%u (%s)\n",
			__func__, sysconfig, mode,
			mod_clock_activity_mode_name_get(mode));
	} else {
		dprintf("%s(): module does NOT have clock activity mode (%u)\n",
			__func__, properties);
		mode = MOD_CLOCK_ACTIVITY_MODE_MAX;
	}

	return mode;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod_context_is_lost
 * @BRIEF		check if module's context was retained or lost
 *			during last power transition
 * @RETURNS		1 if module's context was LOST during last power
 *			transition
 *			0 if module's context was RETAINED during last power
 *			transition
 * @param[in]		sysconfig: RM_XYZ_CONTEXT register content
 * @DESCRIPTION		check if module's context was retained or lost
 *			during last power transition
 *//*------------------------------------------------------------------------ */
int mod_context_is_lost(unsigned int rm_context)
{
	int lost;
	if (rm_context == 0) {
		/* All memory bank(s) were retained */
		dprintf(
			"%s(): RM_CONTEXT=0x%08X => context is RETAINED\n",
			__func__, rm_context);
		lost = 0;
	} else {
		/* At least 1 memory bank was lost */
		dprintf(
			"%s(): RM_CONTEXT=0x%08X => context is LOST\n",
			__func__, rm_context);
		lost = 1;
	}

	return lost;
}
