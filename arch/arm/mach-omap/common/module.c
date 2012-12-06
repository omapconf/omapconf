/*
 *
 * @Component			OMAPCONF
 * @Filename			module.c
 * @Description			OMAP Generic Module Definitions & APIs
 * @Author			Patrick Titiano (p-titiano@ti.com)
 * @Date			2012
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
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
#include <voltdomain.h>
#include <cpufreq.h>


/* #define MODULE_DEBUG */
#ifdef MODULE_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		module_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void module_init(void)
{
	#ifdef MODULE_DEBUG
	int i, j, count, count_opp;
	const genlist *mod_list;
	mod_info mod;
	mod_opp opp;
	#endif

	if (cpu_is_omap44xx()) {
		mod44xx_init();
	} else if (cpu_is_omap54xx()) {
		mod54xx_init();
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
	}

	#ifdef MODULE_DEBUG
	mod_list = module_list_get();
	count = genlist_getcount((genlist *) mod_list);
	printf("Module List:\n");
	for (i = 0; i < count; i++) {
		genlist_get((genlist *) mod_list, i, (mod_info *) &mod);
		printf(" %s:\n", mod.name);
		printf("  ID:%d\n", mod.id);
		printf("  ClkDM: %s\n", mod.clkdm);
		printf("  PwrDM: %s\n", mod.pwrdm);
		printf("  VoltDM: %s\n", mod.voltdm);
		printf("  F-Clk:%d\n", mod.clk);
		printf("  SYSCONFIG REG: %s\n", (mod.sysconfig)->name);
		printf("  CLKCTRL REG: %s\n", (mod.clkctrl)->name);
		printf("  CONTEXT REG: %s\n", (mod.context)->name);
		printf("  Properties: %d\n", mod.properties);
		printf("  OPP List: ");
		count_opp = genlist_getcount((genlist *) &(mod.mod_opp_list));
		for (j = 0; j < count_opp; j++) {
			genlist_get(&(mod.mod_opp_list), j,
				(mod_opp *) &opp);
			printf("(%s, %dKHz) ", opp.name, opp.rate);
		}
		printf("\n\n");
	}
	printf("Module count: %d\n\n", count);
	#endif
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		module_deinit
 * @BRIEF		free dynamically allocated internal data.
 * @DESCRIPTION		free dynamically allocated internal data.
 *			MUST BE CALLED AT END OF EXECUTION.
 *//*------------------------------------------------------------------------ */
void module_deinit(void)
{
	if (cpu_is_omap44xx()) {
		mod44xx_deinit();
	} else if (cpu_is_omap54xx()) {
		mod54xx_deinit();
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		module_list_get
 * @BRIEF		return the list of modules
 * @RETURNS		list of modules in case of success
 *			NULL in case of error
 * @DESCRIPTION		return the list of modules
 *//*------------------------------------------------------------------------ */
const genlist *module_list_get(void)
{
	if (cpu_is_omap44xx()) {
		return mod44xx_list_get();
	} else if (cpu_is_omap54xx()) {
		return mod54xx_list_get();
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		return NULL;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		module_count_get
 * @BRIEF		return the number of modules
 * @RETURNS		number of modules (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @DESCRIPTION		return the number of modules
 *//*------------------------------------------------------------------------ */
int module_count_get(void)
{
	if (cpu_is_omap44xx()) {
		return mod44xx_count_get();
	} else if (cpu_is_omap54xx()) {
		return mod54xx_count_get();
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		return OMAPCONF_ERR_CPU;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_module_info_get
 * @BRIEF		return the saved informations of a given module.
 * @RETURNS		0 in case of success
 *			-1 in case of error
 * @param[in]		mod: module name
 * @param[in,out]	data: module details
 * @DESCRIPTION		return the saved informations of a given module.
 *//*------------------------------------------------------------------------ */
static int _module_info_get(const char *mod, mod_info *data)
{
	const genlist *mod_list;
	int i, count;

	CHECK_NULL_ARG(mod, -1);
	CHECK_NULL_ARG(data, -1);

	mod_list = module_list_get();
	count = genlist_getcount((genlist *) mod_list);
	for (i = 0; i < count; i++) {
		genlist_get((genlist *) mod_list, i, (void *) data);
		if (strcmp(data->name, mod) == 0) {
			dprintf("%s(%s): found.\n", __func__, mod);
			return 0;
		}
	}

	dprintf("%s(%s): not found!\n", __func__, mod);
	return -1;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		module_id_get
 * @BRIEF		return the unique ID of a given module.
 * @RETURNS		>= 0 module ID
 *			-1 in case of error
 * @param[in]		mod: module name
 * @DESCRIPTION		return the unique ID of a given module.
 *//*------------------------------------------------------------------------ */
int module_id_get(const char *mod)
{
	int id;
	mod_info data;

	CHECK_NULL_ARG(mod, -1);

	id = _module_info_get(mod, &data);
	if (id == 0)
		id = data.id;

	dprintf("%s(%s) = %d\n", __func__, mod, id);
	return id;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		module_is_accessible
 * @BRIEF		check omap module's registers accessibility
 * @RETURNS		1 if omap module's registers accessible
 *			0 if omap module's registers NOT accessible
 *			(or in case of error)
 * @param[in]		mod: module name
 * @DESCRIPTION		check omap module's registers accessibility
 *//*------------------------------------------------------------------------ */
unsigned short int module_is_accessible(const char *mod)
{
	int ret;
	mod_info data;
	unsigned int cm_clkctrl;

	CHECK_NULL_ARG(mod, 0);

	ret = _module_info_get(mod, &data);
	if (ret != 0) {
		dprintf("%s(%s): could not retrieve mod_info struct!\n",
			__func__, mod);
		return 0;
	}

	if (data.clkctrl == NULL) {
		dprintf("%s(%s): cm_clkctrl_reg == NULL!!!\n", __func__, mod);
		return 0;
	}

	cm_clkctrl = reg_read(data.clkctrl);
	dprintf("%s(%s) = %d\n", __func__, mod, mod_is_accessible(cm_clkctrl));
	return mod_is_accessible(cm_clkctrl);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		module_mode_get
 * @BRIEF		retrieve module mode from CM register
 * @RETURNS		module mode on success
 *			MOD_MODULE_MODE_MAX in case of error or not available
 * @param[in]		mod: module name
 * @DESCRIPTION		retrieve module mode from CM register
 *//*------------------------------------------------------------------------ */
mod_module_mode module_mode_get(const char *mod)
{
	int ret;
	mod_info data;
	unsigned int cm_clkctrl;
	mod_module_mode mmode;

	CHECK_NULL_ARG(mod, MOD_MODULE_MODE_MAX);

	ret = _module_info_get(mod, &data);
	if (ret != 0) {
		dprintf("%s(%s): could not retrieve mod_info struct!\n",
			__func__, mod);
		mmode = MOD_MODULE_MODE_MAX;
	} else if (data.clkctrl == NULL) {
		/* Module is not SW-Controlled via PRCM */
		dprintf("%s(%s): CM_CLKCTRL ADDR = NULL\n", __func__, mod);
		mmode = MOD_MODULE_MODE_MAX;
	} else {
		/* Retrieve module mode */
		cm_clkctrl = reg_read(data.clkctrl);
		mmode = mod_module_mode_get(cm_clkctrl);
	}

	dprintf("%s(%s) = %s\n", __func__, mod,
		mod_module_mode_name_get(mmode));
	return mmode;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		module_autoidle_mode_get
 * @BRIEF		retrieve module autoidle mode
 * @RETURNS		module autoidle mode
 *			MOD_AUTOIDLE_MODE_MAX in case of error
 * @param[in]		mod: module name
 * @DESCRIPTION		retrieve module autoidle mode
 *//*------------------------------------------------------------------------ */
mod_autoidle_mode module_autoidle_mode_get(const char *mod)
{
	int ret;
	mod_info data;
	unsigned int sysconfig;
	mod_autoidle_mode mode;

	CHECK_NULL_ARG(mod, MOD_AUTOIDLE_MODE_MAX);

	ret = _module_info_get(mod, &data);
	if (ret != 0) {
		dprintf("%s(%s): could not retrieve mod_info struct!\n",
			__func__, mod);
		mode = MOD_AUTOIDLE_MODE_MAX;
	} else if (data.sysconfig == NULL) {
		dprintf("%s(%s): sysconfig == NULL!!!\n", __func__, mod);
		mode = MOD_AUTOIDLE_MODE_MAX;
	} else if (!module_is_accessible(mod)) {
		dprintf("%s(%s): module is not accessible.\n", __func__, mod);
		mode = MOD_AUTOIDLE_MODE_MAX;
	} else {
		sysconfig = reg_read(data.sysconfig);
		mode = mod_autoidle_mode_get(sysconfig, data.properties);
		dprintf("%s(%s)=%u (%s)\n", __func__, mod, mode,
			mod_autoidle_mode_name_get(mode));
	}

	return mode;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		module_idle_mode_get
 * @BRIEF		retrieve omap module's idle mode
 * @RETURNS		module's idle mode
 *			MOD_IDLE_MODE_MAX in case of error
 * @param[in]		mod: module name
 * @DESCRIPTION		retrieve omap module's idle mode
 *//*------------------------------------------------------------------------ */
mod_idle_mode module_idle_mode_get(const char *mod)
{
	int ret;
	mod_info data;
	unsigned int sysconfig;
	mod_idle_mode mode;

	CHECK_NULL_ARG(mod, MOD_IDLE_MODE_MAX);

	ret = _module_info_get(mod, &data);
	if (ret != 0) {
		dprintf("%s(%s): could not retrieve mod_info struct!\n",
			__func__, mod);
		mode = MOD_IDLE_MODE_MAX;
	} else if (data.sysconfig == NULL) {
		dprintf("%s(%s): sysconfig == NULL!!!\n", __func__, mod);
		mode = MOD_IDLE_MODE_MAX;
	} else if (!module_is_accessible(mod)) {
		dprintf("%s(%s): module is not accessible.\n", __func__, mod);
		mode = MOD_IDLE_MODE_MAX;
	} else {
		sysconfig = reg_read(data.sysconfig);
		mode = mod_idle_mode_get(sysconfig, data.properties);
		dprintf("%s(%s)=%u (%s)\n", __func__, mod, mode,
			mod_idle_mode_name_get(mode));
	}

	return mode;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		module_idle_status_get
 * @BRIEF		retrieve module's idle status from CM_xxx_xxx_CLKCTRL
 * @RETURNS		module idle status
 *			MOD_IDLE_STATUS_MAX in case of error
 * @param[in]		mod: module name
 * @DESCRIPTION		retrieve module's idle status from CM_xxx_xxx_CLKCTRL
 *//*------------------------------------------------------------------------ */
mod_idle_status module_idle_status_get(const char *mod)
{
	int ret;
	mod_info data;
	unsigned int clkctrl;
	mod_idle_status mstatus;

	CHECK_NULL_ARG(mod, MOD_IDLE_STATUS_MAX);

	ret = _module_info_get(mod, &data);
	if (ret != 0) {
		dprintf("%s(%s): could not retrieve mod_info struct!\n",
			__func__, mod);
		mstatus = MOD_IDLE_STATUS_MAX;
	} else if (data.clkctrl == NULL) {
		dprintf("%s(%s): clkctrl == NULL!!!\n", __func__, mod);
		mstatus = MOD_IDLE_STATUS_MAX;
	} else {
		clkctrl = reg_read(data.clkctrl);
		mstatus = mod_idle_status_get(clkctrl, data.properties);
		dprintf("%s(%s)=%u (%s)\n", __func__, mod, mstatus,
			mod_idle_status_name_get(mstatus));
	}

	return mstatus;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		module_standby_mode_get
 * @BRIEF		retrieve omap module's standby mode
 * @RETURNS		module's standby mode
 *			MOD_STANDBY_MODE_MAX in case of error
 * @param[in]		mod: module name
 * @DESCRIPTION		retrieve omap module's standby mode
 *//*------------------------------------------------------------------------ */
mod_standby_mode module_standby_mode_get(const char *mod)
{
	int ret;
	mod_info data;
	unsigned int sysconfig;
	mod_standby_mode mode;

	CHECK_NULL_ARG(mod, MOD_STANDBY_MODE_MAX);

	ret = _module_info_get(mod, &data);
	if (ret != 0) {
		dprintf("%s(%s): could not retrieve mod_info struct!\n",
			__func__, mod);
		return MOD_STANDBY_MODE_MAX;
	} else if (data.sysconfig == NULL) {
		dprintf("%s(%s): sysconfig == NULL!!!\n", __func__, mod);
		mode = MOD_STANDBY_MODE_MAX;
	} else if (!module_is_accessible(mod)) {
		dprintf("%s(%s): module is not accessible.\n", __func__, mod);
		return MOD_STANDBY_MODE_MAX;
	} else {
		sysconfig = reg_read(data.sysconfig);
		mode = mod_standby_mode_get(sysconfig, data.properties);
		dprintf("%s(%s)=%u (%s)\n", __func__, mod, mode,
			mod_standby_mode_name_get(mode));
	}

	return mode;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		module_standby_status_get
 * @BRIEF		retrieve module standby status from CM_xxx_xxx_CLKCTRL
 * @RETURNS		module standby status
 *			MOD_STANDBY_STATUS_MAX in case of error
 * @param[in]		mod: module name
 * @DESCRIPTION		retrieve module standby status from CM_xxx_xxx_CLKCTRL
 *//*------------------------------------------------------------------------ */
mod_standby_status module_standby_status_get(const char *mod)
{
	int ret;
	mod_info data;
	unsigned int clkctrl;
	mod_standby_status mstatus;

	CHECK_NULL_ARG(mod, MOD_STANDBY_STATUS_MAX);

	ret = _module_info_get(mod, &data);
	if (ret != 0) {
		dprintf("%s(%s): could not retrieve mod_info struct!\n",
			__func__, mod);
		return MOD_STANDBY_STATUS_MAX;
	} else if (data.clkctrl == NULL) {
		dprintf("%s(%s): clkctrl == NULL!!!\n", __func__, mod);
		mstatus = MOD_STANDBY_STATUS_MAX;
	} else {
		clkctrl = reg_read(data.clkctrl);
		mstatus = mod_standby_status_get(clkctrl, data.properties);
		dprintf("%s(%s)=%u (%s)\n", __func__, mod, mstatus,
			mod_standby_status_name_get(mstatus));
	}

	return mstatus;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		module_context_is_lost
 * @BRIEF		check if module's context was retained or lost
 *			during last power transition
 * @RETURNS		1 if module's context was LOST during last power
 *			transition (or in case of error)
 *			0 if module's context was RETAINED during last power
 *			transition
 *			-1 in case of error or module has no context register
 * @param[in]		mod: module name
 * @DESCRIPTION		check if module's context was retained or lost
 *			during last power transition
 *//*------------------------------------------------------------------------ */
int module_context_is_lost(const char *mod)
{
	int ret;
	mod_info data;
	unsigned int rm_context;
	unsigned short lost;

	CHECK_NULL_ARG(mod, -1);

	ret = _module_info_get(mod, &data);
	if (ret != 0) {
		dprintf("%s(%s): could not retrieve mod_info struct!\n",
			__func__, mod);
		lost = -1;
	} else if (data.context == NULL) {
		dprintf("%s(%s): RM_CONTEXT addr==NULL\n", __func__, mod);
		lost = -1;
	} else {
		rm_context = reg_read(data.context);
		lost = mod_context_is_lost(rm_context);
		dprintf("%s(%s)=%d\n", __func__, mod, lost);
	}

	return lost;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		module_clock_activity_mode_get
 * @BRIEF		retrieve omap module's clock activity mode
 * @RETURNS		module's clock activity mode
 *			MOD_CLOCK_ACTIVITY_MODE_MAX in case of error
 * @param[in]		mod: module name
 * @DESCRIPTION		retrieve omap module's clock activity mode
 *//*------------------------------------------------------------------------ */
mod_clock_activity_mode module_clock_activity_mode_get(const char *mod)
{
	int ret;
	mod_info data;
	unsigned int sysconfig;
	mod_clock_activity_mode mode;

	CHECK_NULL_ARG(mod, MOD_CLOCK_ACTIVITY_MODE_MAX);

	ret = _module_info_get(mod, &data);
	if (ret != 0) {
		dprintf("%s(%s): could not retrieve mod_info struct!\n",
			__func__, mod);
		return MOD_CLOCK_ACTIVITY_MODE_MAX;
	} else if (data.sysconfig == NULL) {
		dprintf("%s(%s): sysconfig == NULL!!!\n", __func__, mod);
		mode = MOD_CLOCK_ACTIVITY_MODE_MAX;
	} else if (!module_is_accessible(mod)) {
		dprintf("%s(%s): module is not accessible.\n", __func__, mod);
		mode = MOD_CLOCK_ACTIVITY_MODE_MAX;
	} else {
		sysconfig = reg_read(data.sysconfig);
		mode = mod_clock_activity_mode_get(sysconfig, data.properties);
		dprintf("%s(%s)=%u (%s)\n", __func__, mod, mode,
			mod_clock_activity_mode_name_get(mode));


	}

	return mode;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		module_por_clk_rate_get
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
int module_por_clk_rate_get(const char *mod, const char *opp)
{
	mod_info data;
	mod_opp data_opp;
	int ret, i, opp_count, rate_khz;

	CHECK_NULL_ARG(mod, OMAPCONF_ERR_ARG);

	ret = _module_info_get(mod, &data);
	if (ret != 0) {
		dprintf("%s(%s): could not retrieve mod_info struct!\n",
			__func__, mod);
		rate_khz = OMAPCONF_ERR_NOT_AVAILABLE;
		goto module_por_clk_rate_get_end;
	}

	opp_count = genlist_getcount((genlist *) &(data.mod_opp_list));
	for (i = 0; i < opp_count; i++) {
		genlist_get(&(data.mod_opp_list), i,
			(mod_opp *) &data_opp);
		if (strcmp(data_opp.name, opp) != 0)
			continue;

		/* Module OPP details found */
		rate_khz = data_opp.rate;
		goto module_por_clk_rate_get_end;
	}

	dprintf("%s(%s): Module OPP details could not be found!\n",
		__func__, opp);
	rate_khz = OMAPCONF_ERR_NOT_AVAILABLE;




#if 0
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
#endif


module_por_clk_rate_get_end:
	dprintf("%s(%s) = %d KHz\n", __func__, mod, rate_khz);
	return rate_khz;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		module_clk_rate_get
 * @BRIEF		return the module functional clock rate, in KHz.
 * @RETURNS		module functional clock rate, in KHz.
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		mod: module name, as defined in module.h
 * @param[in]		ignore: do not consider DPLL status (if any).
 * @DESCRIPTION		return the module functional clock rate, in KHz.
 *//*------------------------------------------------------------------------ */
int module_clk_rate_get(const char *mod, unsigned short ignore)
{
	mod_info data;
	int ret, rate_khz;
	double rate_mhz;

	CHECK_NULL_ARG(mod, OMAPCONF_ERR_ARG);

	ret = _module_info_get(mod, &data);
	if (ret != 0) {
		dprintf("%s(%s): could not retrieve mod_info struct!\n",
			__func__, mod);
		rate_khz = OMAPCONF_ERR_NOT_AVAILABLE;
	} else if (data.clk < 0) {
		dprintf("%s(%s): could not retrieve module clock ID!\n",
			__func__, mod);
		rate_khz = OMAPCONF_ERR_NOT_AVAILABLE;
	} else {
		rate_mhz = clk54xx_rate_get(data.clk, ignore);
		if (rate_mhz < 0.0) {
			rate_khz = (int) rate_mhz;
			dprintf(
				"%s(%s): could not retrieve module rate! (%d)\n",
				__func__, mod, rate_khz);
		} else {
			rate_khz = mhz2khz(rate_mhz);
		}
	}

	dprintf("%s(%s)=%d KHz\n", __func__, mod, rate_khz);
	return rate_khz;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		module_status_show
 * @BRIEF		show OMAP5 power status
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in,out]	stream: output file stream (!= NULL)
 * @DESCRIPTION		show OMAP5 power status
 *//*------------------------------------------------------------------------ */
int module_status_show(FILE *stream)
{
	int voltdm_count;
	const genlist *voltdm_list;
	voltdm_info voltdm;
	const char *opp;
	char s_voltdm_name[VOLTDM_MAX_NAME_LENGTH + 10];
	int powerdm_count;
	const genlist *powerdm_list;
	powerdm_info pwrdm;
	int clockdm_count;
	const genlist *clockdm_list;
	clockdm_info clkdm;
	int mod_count;
	const genlist *mod_list;
	mod_info mod;
	int v, p, c, m;



	mod_idle_status idlest;
	mod_standby_status stbyst;
	char s_idlest[MODULE_MODES_MAX_NAME_LENGTH];
	char s_stbyst[MODULE_MODES_MAX_NAME_LENGTH];
	pwrdm_state pwst, pwtgst;
	char s_pwst[PWRDM_STATE_MAX_NAME_LENGTH];
	char s_pwtgst[PWRDM_STATE_MAX_NAME_LENGTH];
	char s_pwrdm_name[PWRDM_MAX_NAME_LENGTH];
	clkdm_status clkst;
	char s_clkst[CLKDM_STATUS_MAX_NAME_LENGTH];
	char s_clkdm_name[CLKDM_MAX_NAME_LENGTH];
	double clk_rate;
	char s_clk_rate[12];
	char s_current_opp[OPP_MAX_NAME_LENGTH];
	unsigned short first_mod, first_clkdm, first_pwrdm;
	double volt;

	/* Retrieve voltage domain list and count */
	voltdm_list = voltdm_list_get();
	if (voltdm_list == NULL) {
		fprintf(stderr,
			"omapconf: %s(): failed to retrieve VDD List!\n",
			__func__);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	voltdm_count = voltdm_count_get();
	if (voltdm_count <= 0) {
		fprintf(stderr,
			"omapconf: %s(): failed to retrieve VDD count!\n",
			__func__);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	/* Retrieve power domain list and count */
	powerdm_list = powerdm_list_get();
	if (powerdm_list == NULL) {
		fprintf(stderr,
			"omapconf: %s(): failed to retrieve PWRDM List!\n",
			__func__);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}
	powerdm_count = powerdm_count_get();
	if (powerdm_count <= 0) {
		fprintf(stderr,
			"omapconf: %s(): failed to retrieve PWRDM count!\n",
			__func__);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	/* Retrieve clock domain list and count */
	clockdm_list = clockdm_list_get();
	if (clockdm_list == NULL) {
		fprintf(stderr,
			"omapconf: %s(): failed to retrieve CLKDM List!\n",
			__func__);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}
	clockdm_count = clockdm_count_get();
	if (clockdm_count <= 0) {
		fprintf(stderr,
			"omapconf: %s(): failed to retrieve CLKDM count!\n",
			__func__);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	/* Retrieve module domain list and count */
	mod_list = module_list_get();
	if (mod_list == NULL) {
		fprintf(stderr,
			"omapconf: %s(): failed to retrieve MODULE List!\n",
			__func__);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}
	mod_count = module_count_get();
	if (mod_count <= 0) {
		fprintf(stderr,
			"omapconf: %s(): failed to retrieve MODULE count!\n",
			__func__);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}


	/* For each voltage domain, retrieve the current OPP */
	fprintf(stream,
		"|---------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	fprintf(stream,
		"| OMAP5 Power Status                                                                                                                                            |\n");
	fprintf(stream,
		"|---------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	fprintf(stream,
		"| Voltage Domain                | Power Domain                 | Clock Domain          | Module Status                                                          |\n");
	fprintf(stream,
		"| Name              | OPP       | Name       | Curr.  | Target | Name       | Status   | Name                  | Rate (MHz) | Idle                 | Standby    |\n");
	/* For each domain, retrieve the clock & power domain status */
	for (v = 0; v < voltdm_count; v++) {
		fprintf(stream,
			"|---------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
		genlist_get((genlist *) voltdm_list, v, (void *) &voltdm);

		opp = opp_get(voltdm.name, 1);
		strncpy(s_current_opp, opp, OPP_MAX_NAME_LENGTH);

		volt = (double) voltdm_voltage_get(voltdm.name) / 1000000.0;
		if (volt > 0)
			sprintf(s_voltdm_name, "%s (%.3lfV)",
				voltdm.name, volt);
		else
			strcpy(s_voltdm_name, voltdm.name);

		for (p = 0, first_pwrdm = 1; p < powerdm_count; p++) {
			genlist_get(
				(genlist *) powerdm_list, p, (void *) &pwrdm);

			if (strcmp(pwrdm.voltdm, voltdm.name) != 0)
				continue;
			/* Ignore these power domains (and modules) */
			else if (strcmp(pwrdm.name, "MMAON") == 0)
				continue;
			else if (strcmp(pwrdm.name, "MPUAON") == 0)
				continue;
			else if (strcmp(pwrdm.name, "CUSTEFUSE") == 0)
				continue;

			*s_pwst = '\0';
			pwst = powerdm_state_get(pwrdm.name,
				PWRDM_STATE_CURRENT);
			pwrdm_state2string(s_pwst, pwst);

			*s_pwtgst = '\0';
			pwtgst = powerdm_state_get(pwrdm.name,
				PWRDM_STATE_TARGET);
			pwrdm_state2string(s_pwtgst, pwtgst);
			strncpy(s_pwrdm_name, pwrdm.name,
				PWRDM_MAX_NAME_LENGTH);

			for (c = 0, first_clkdm = 1; c < clockdm_count; c++) {
				genlist_get((genlist *) clockdm_list, c,
					(void *) &clkdm);

				if (strcmp(clkdm.powerdm, pwrdm.name) != 0)
					continue;
				if ((strcmp(clkdm.name, CLKDM_L4_SEC) == 0) &&
					cpu_is_gp_device())
					continue;
				if (strcmp(clkdm.name, CLKDM_NONE) == 0)
					continue;

				if ((!first_pwrdm) && (first_clkdm))
					fprintf(stream,
						"| %-17s | %-9s |-------------------------------------------------------------------------------------------------------------------------------|\n",
						"", "");
				*s_clkst = '\0';
				clkst = clockdm_status_get(clkdm.name);
				if (clkst != CLKDM_STATUS_MAX)
					strcpy(s_clkst,
						clkdm_status_name_get(clkst));

				strncpy(s_clkdm_name, clkdm.name,
					CLKDM_MAX_NAME_LENGTH);

				/* For each module, retrieve status */
				for (m = 0, first_mod = 1; m < mod_count; m++) {
					genlist_get((genlist *) mod_list, m,
						(void *) &mod);

					if (strcmp(mod.clkdm, clkdm.name) != 0)
						continue;

					*s_idlest = '\0';
					*s_stbyst = '\0';

					idlest = module_idle_status_get(
						mod.name);
					if (idlest != MOD_IDLE_STATUS_MAX) {
						strcpy(s_idlest, mod_idle_status_name_get(idlest));
					} else if (idlest != MOD_DISABLED) {
						stbyst = module_standby_status_get(mod.name);
						if (stbyst != MOD_STANDBY_STATUS_MAX)
							strcpy(s_stbyst, mod_standby_status_name_get(stbyst));
					}
					clk_rate = (double) module_clk_rate_get(
						mod.name, 0) / 1000.0;
					if (clk_rate < 0.0)
						strcpy(s_clk_rate, "Error");
					else
						snprintf(s_clk_rate, 12,
							"%.3lf", clk_rate);
					if ((first_mod) && (!first_clkdm))
						fprintf(stream,
							"| %-17s | %-9s | %-10s | %-6s | %-6s |------------------------------------------------------------------------------------------------|\n",
							"", "", "", "", "");
					fprintf(stream,
						"| %-17s | %-9s | %-10s | %-6s | %-6s | %-10s | %-8s | %-21s | %-10s | %-20s | %-10s |\n",
						s_voltdm_name,
						s_current_opp,
						s_pwrdm_name,
						s_pwst,
						s_pwtgst,
						s_clkdm_name,
						s_clkst,
						mod.name,
						s_clk_rate,
						s_idlest,
						s_stbyst);
					if (first_mod) {
						*s_clkdm_name = '\0';
						*s_pwrdm_name = '\0';
						*s_voltdm_name = '\0';
						*s_current_opp = '\0';
						*s_pwst = '\0';
						*s_pwtgst = '\0';
						*s_clkst = '\0';
						first_mod = 0;
					}
				}
				first_clkdm = 0;
			}
			first_pwrdm = 0;
		}

	}
	fprintf(stream,
		"|---------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		module_clk_rate_audit
 * @BRIEF		Modules functional clock rate audit.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in,out]	stream: output file - NULL: no output (silent)
 * @param[in,out]	err_nbr: pointer to return audit error number
 * @param[in,out]	wng_nbr: pointer to return audit warning number
 * @DESCRIPTION		Modules functional clock rate audit.
 *//*------------------------------------------------------------------------ */
int module_clk_rate_audit(FILE *stream,
	unsigned int *err_nbr, unsigned int *wng_nbr)
{
	const char *opp;
	int mod_count, m;
	const genlist *mod_list;
	mod_info mod;

	double speed_curr = 0.0, speed_por = 0.0;
	const char pass1[10] = "pass (1)";
	const char fail2[10] = "FAIL (2)";
	const char fail3[10] = "FAIL (3)";
	const char warning4[10] = "warn (4)";
	const char warning5[10] = "warn (5)";
	const char warning6[10] = "warn (6)";
	const char warning7[10] = "warn (7)";
	const char ignore8[10] = "ign. (8)";
	const char warning9[10] = "warn (9)";
	const char fixme[10] = "FIXME";
	char *status;
	char s_speed_curr[16], s_speed_por[16];
	char src_clk_name[CLK54XX_MAX_NAME_LENGTH];
	char opp_name[OPP_MAX_NAME_LENGTH];
	char prev_gov[CPUFREQ_GOV_MAX_NAME_LENGTH];
	char prev_gov2[CPUFREQ_GOV_MAX_NAME_LENGTH];
	mod_module_mode mmode;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(err_nbr, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(wng_nbr, OMAPCONF_ERR_ARG);

	*err_nbr = 0;
	*wng_nbr = 0;

	/* Switch to userspace governor temporarily,
	 * so that OPP cannot change during audit and does not false it.
	 */
	cpufreq_scaling_governor_set("userspace", prev_gov);

	/* Retrieve module domain list and count */
	mod_list = module_list_get();
	if (mod_list == NULL) {
		fprintf(stderr,
			"omapconf: %s(): failed to retrieve MODULE List!\n",
			__func__);
		(*wng_nbr)++;
		goto module_clk_rate_audit_end;
	}
	mod_count = module_count_get();
	if (mod_count <= 0) {
		fprintf(stderr,
			"omapconf: %s(): failed to retrieve MODULE count!\n",
			__func__);
		(*wng_nbr)++;
		goto module_clk_rate_audit_end;
	}

	if (stream == NULL)
		goto module_clk_rate_audit_loop;

	fprintf(stream,
		"|----------------------------------------------------------------------------------------------------------|\n");
	fprintf(stream, "| %-21s | %-24s | %-9s | %-27s | %-11s |\n",
		"  CLOCK SPEED AUDIT", "", "", "     Clock Rate (MHz)",
		"");
	fprintf(stream,
		"| %-21s | %-24s | %-9s | %-12s | %-12s | %-11s |\n",
		"Module", "Source Clock", "OPP", "Current", "Expected",
		"STATUS");
	fprintf(stream,
		"|----------------------------------------------------------------------------------------------------------|\n");

module_clk_rate_audit_loop:
	for (m = 0; m < mod_count; m++) {
		genlist_get((genlist *) mod_list, m,
			(void *) &mod);
		dprintf("\n\n%s():Auditing module %s\n", __func__, mod.name);

		/* Filter based on module name */
		if (cpu_is_gp_device()) {
			if ((strcmp(mod.name, MOD_TIMER12) == 0) ||
				(strcmp(mod.name, MOD_WD_TIMER1) == 0) ||
				(strcmp(mod.name, MOD_DMA_CRYPTO) == 0) ||
				(strcmp(mod.name, MOD_AES1) == 0) ||
				(strcmp(mod.name, MOD_AES2) == 0) ||
				(strcmp(mod.name, MOD_SHA2MD5) == 0) ||
				(strcmp(mod.name, MOD_RNG) == 0) ||
				(strcmp(mod.name, MOD_DES3DES) == 0) ||
				(strcmp(mod.name, MOD_PKA) == 0)) {
				dprintf("\tGP device, skip it.\n");
				continue;
			}
		}

		/* init variables */
		status = (char *) fixme;
		speed_curr = -1.0;
		snprintf(s_speed_curr, 16, "%s", "NOT FOUND");
		snprintf(src_clk_name, CLK54XX_MAX_NAME_LENGTH, "%s",
			"NOT FOUND");
		strcpy(opp_name, "NOT FOUND");
		speed_por = -2.0;
		snprintf(s_speed_por, 16, "%s", "NOT FOUND");

		/* Get module's functional source clock */
		if (mod.clk < 0) {
			dprintf("%s(): src_clk not found!\n", __func__);
			status = (char *) warning4;
			(*wng_nbr)++;
			goto module_clk_rate_audit_opp_fill;
		}
		snprintf(src_clk_name, CLK54XX_MAX_NAME_LENGTH, "%s",
			clk54xx_name_get(mod.clk)); /* FIXME */

		/* Get module's functional clock rate*/
		speed_curr =
			(double) module_clk_rate_get(mod.name, 1) / 1000.0;
		if (speed_curr < 0.0) {
			dprintf("%s(): speed not found!\n", __func__);
			status = (char *) warning5;
			(*wng_nbr)++;
			goto module_clk_rate_audit_opp_fill;
		}
		dprintf("%s(): speed=%lfMHz\n", __func__, speed_curr);
		mhz2string(speed_curr, s_speed_curr);

		/* Get OPP */
		opp = opp_get(mod.voltdm, 1);
		if (opp == NULL) {
			dprintf("%s(): opp not found!\n", __func__);
			status = (char *) fail3;
			(*err_nbr)++;
			goto module_clk_rate_audit_opp_fill;
		}
		strncpy(opp_name, opp, OPP_MAX_NAME_LENGTH);

		/*
		 * Get Plan Of Record (POR) module's functional
		 * source clock rate
		 */

		if ((strcmp(mod.name, MOD_TIMER2) == 0) ||
			(strcmp(mod.name, MOD_TIMER3) == 0) ||
			(strcmp(mod.name, MOD_TIMER4) == 0) ||
			(strcmp(mod.name, MOD_TIMER5) == 0) ||
			(strcmp(mod.name, MOD_TIMER6) == 0) ||
			(strcmp(mod.name, MOD_TIMER7) == 0) ||
			(strcmp(mod.name, MOD_TIMER8) == 0) ||
			(strcmp(mod.name, MOD_TIMER9) == 0) ||
			(strcmp(mod.name, MOD_TIMER10) == 0) ||
			(strcmp(mod.name, MOD_TIMER11) == 0) ||
			(strcmp(mod.name, MOD_MCASP) == 0) ||
			(strcmp(mod.name, MOD_MCBSP1) == 0) ||
			(strcmp(mod.name, MOD_MCBSP2) == 0) ||
			(strcmp(mod.name, MOD_MCBSP3) == 0) ||
			(strcmp(mod.name, MOD_SLIMBUS1) == 0) ||
			(strcmp(mod.name, MOD_SLIMBUS2) == 0)) {
			/*
			 * These modules are out of interest or
			 * there is no mandatory clock speed
			 */
			snprintf(s_speed_por, 16, "%s", "Undefined");
			status = (char *) ignore8;
			goto module_clk_rate_audit_opp_fill;
		}

		mmode = module_mode_get(mod.name);
		speed_por = (double) module_por_clk_rate_get(
			mod.name, opp) / 1000.0;
		if (speed_por < 0.0) {
			dprintf("\tWarning: %s POR speed not yet defined!\n",
				mod.name);
			status = (char *) warning6;
			(*wng_nbr)++;
			goto module_clk_rate_audit_opp_fill;
		}
		dprintf("\tPOR rate is %lfMHz\n", speed_por);
		snprintf(s_speed_por, 16, "%.3lf", speed_por);

		/* Keep only 1 decimal for comparison */
		if (speed_curr > 1.0)
			speed_curr = (double) ((int)
				(speed_curr * 10.0)) / 10.0;
		dprintf("%s(): rounded current speed=%lfMHz\n",
			__func__, speed_curr);
		if (speed_por > 1.0)
			speed_por = (double) ((int)
				(speed_por * 10.0)) / 10.0;
		dprintf("%s(): rounded POR     speed=%lfMHz\n",
			__func__, speed_por);

		if (speed_curr == speed_por) {
			status = (char *) pass1;
			dprintf("%s(): pass!\n", __func__);
		} else if (mmode == MOD_DISABLED_MODE) {
			/*
			 * may not be a true failure when
			 * module is disabled (not configured).
			 * Does not impact power.
			 */
			dprintf("%s(): disabled module.\n",
				__func__);
			status = (char *) warning7;
			(*wng_nbr)++;
		} else if (speed_curr == 0.0) {
			dprintf("%s(): speed_curr == 0.0.\n",
				__func__);
			status = (char *) warning7;
			(*wng_nbr)++;
		} else if (speed_curr < speed_por) {
			dprintf("%s(): curr < por.\n",
				__func__);
			status = (char *) warning9;
			(*wng_nbr)++;
		} else {
			dprintf("%s(): FAILED!\n", __func__);
			status = (char *) fail2;
			(*err_nbr)++;
		}

module_clk_rate_audit_opp_fill:
		if (stream == NULL)
			break;

		fprintf(stream,
			"| %-21s | %-24s | %-9s | %-12s | %-12s | %-11s |\n",
			mod.name, src_clk_name, opp_name, s_speed_curr,
			s_speed_por, status);
	}

	if (stream == NULL)
		goto module_clk_rate_audit_end;

	fprintf(stream,
		"|----------------------------------------------------------------------------------------------------------|\n\n");

	fprintf(stream,
		"Notes:\n");
	fprintf(stream,
		"  (1)  Current module rate IS the expected (PoR) one.\n");
	fprintf(stream,
		"  (2)  Current module rate is NOT the expected (PoR) one.\n");
	fprintf(stream,
		"  (3)  Current OPP could not be detected.\n");
	fprintf(stream,
		"  (4)  Current module source clock could not be retrieved.\n");
	fprintf(stream,
		"  (5)  Current module source clock rate could not be retrieved.\n");
	fprintf(stream,
		"  (6)  Current module source clock PoR rate could not be retrieved.\n");
	fprintf(stream,
		"  (7)  Clock rate does no match PoR rate, but module is disabled (no power impact).\n");
	fprintf(stream,
		"  (8)  Optional module, not used on reference platform.\n");
	fprintf(stream,
		"  (9)  Current module rate is lower than the expected (PoR) one.\n");

	if (*err_nbr == 0)
		fprintf(stream,
			"\nSUCCESS! Clock Speed audit completed with 0 error (%d warning(s))\n\n",
			*wng_nbr);
	else
		fprintf(stream,
			"\nFAILED! Clock Speed audit completed with %d error and %d warning.\n\n",
			*err_nbr, *wng_nbr);

module_clk_rate_audit_end:
	/* Restore CPUFreq governor */
	cpufreq_scaling_governor_set(prev_gov, prev_gov2);

	return 0;
}
