/*
 *
 * @Component			OMAPCONF
 * @Filename			module.c
 * @Description			OMAP Module APIs
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
		dprintf("%s(): module is performing transition: "
			"wakeup, or sleep, or sleep abortion => "
			"NOT accessible\n", __func__);
		return 0;

	case MOD_OCP_ONLY_IDLE:
		/*
		 * Module is in Idle mode (only OCP part). OCP clock can be
		 * re-enabled on access, so module is accessible.
		 */
		dprintf("%s(): module is in Idle mode (only OCP part)"
			" => accessible\n", __func__);
		return 1;

	case MOD_DISABLED:
		/* Module is disabled and cannot be accessed. */
		dprintf("%s(): module is disabled and cannot be "
			"accessed => NOT accessible\n", __func__);
		return 0;

	default:
		fprintf(stderr, "%s(): ?!?!?!?! => NOT accessible\n", __func__);
		return 0;
	}
}
