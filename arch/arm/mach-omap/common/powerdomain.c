/*
 *
 * @Component			OMAPCONF
 * @Filename			powerdomain.c
 * @Description			OMAP Generic Power Domain Definitions & APIs
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


#include <powerdomain.h>
#include <pwrdm54xx.h>
#include <pwrdm44xx.h>
#include <pwrdm_am335x.h>
#include <lib.h>
#include <mem.h>
#include <stdio.h>
#include <string.h>
#include <cpuinfo.h>
#include <cm44xx.h>
#include <emu44xx.h>
#include <cm54xx-defs.h>
#include <cm_dra7xx-defs.h>

/* #define PWRDM_DEBUG */
#ifdef PWRDM_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static int _powerdm_info_get(const char *powerdm, powerdm_info *data);


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		powerdm_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void powerdm_init(void)
{
	#ifdef PWRDM_DEBUG
	int i, count;
	const genlist *pwrdm_list;
	powerdm_info pwrdm;
	#endif

	if (cpu_is_omap44xx()) {
		pwrdm44xx_init();
	} else if (cpu_is_omap54xx()) {
		pwrdm54xx_init();
	} else if (cpu_is_am335x()) {
		pwrdm_am335x_init();
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
	}

	#ifdef PWRDM_DEBUG
	pwrdm_list = powerdm_list_get();
	count = genlist_getcount((genlist *) pwrdm_list);
	printf("Power Domain List:\n");
	for (i = 0; i < count; i++) {
		genlist_get((genlist *) pwrdm_list, i, (powerdm_info *) &pwrdm);
		printf(" %s:\n", pwrdm.name);
		printf("  ID:%d\n", pwrdm.id);
		printf("  VoltDM: %s\n", pwrdm.voltdm);
		printf("  PWRSTCTRL REG: %s\n", (pwrdm.pwrstctrl)->name);
		printf("  PWRSTST REG: %s\n", (pwrdm.pwrstst)->name);
		printf("  Properties: %d\n", pwrdm.properties);
		printf("\n\n");
	}
	printf("Power Domain count: %d\n\n", count);
	#endif
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		powerdm_deinit
 * @BRIEF		free dynamically allocated internal data.
 * @DESCRIPTION		free dynamically allocated internal data.
 *			MUST BE CALLED AT END OF EXECUTION.
 *//*------------------------------------------------------------------------ */
void powerdm_deinit(void)
{
	if (cpu_is_omap44xx()) {
		pwrdm44xx_deinit();
	} else if (cpu_is_omap54xx()) {
		pwrdm54xx_deinit();
	} else if (cpu_is_am335x()) {
		pwrdm_am335x_deinit();
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		powerdm_list_get
 * @BRIEF		return the list of power domains
 * @RETURNS		list of power domains in case of success
 *			NULL in case of error
 * @DESCRIPTION		return the list of power domains
 *//*------------------------------------------------------------------------ */
const genlist *powerdm_list_get(void)
{
	if (cpu_is_omap44xx()) {
		return pwrdm44xx_list_get();
	} else if (cpu_is_omap54xx()) {
		return pwrdm54xx_list_get();
	} else if (cpu_is_am335x()) {
		return pwrdm_am335x_list_get();
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		return NULL;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		powerdm_count_get
 * @BRIEF		return the number of power domains
 * @RETURNS		number of power domains (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @DESCRIPTION		return the number of power domains
 *//*------------------------------------------------------------------------ */
int powerdm_count_get(void)
{
	if (cpu_is_omap44xx()) {
		return pwrdm44xx_count_get();
	} else if (cpu_is_omap54xx()) {
		return pwrdm54xx_count_get();
	} else if (cpu_is_am335x()) {
		return pwrdm_am335x_count_get();
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		return OMAPCONF_ERR_CPU;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_powerdm_info_get
 * @BRIEF		return the saved informations of a given power domain.
 * @RETURNS		0 in case of success
 *			-1 in case of error
 * @param[in]		powerdm: power domain name
 * @param[in,out]	data: power domain details
 * @DESCRIPTION		return the saved informations of a given power domain.
 *//*------------------------------------------------------------------------ */
static int _powerdm_info_get(const char *powerdm, powerdm_info *data)
{
	const genlist *pwrdm_list;
	int i, count;

	CHECK_NULL_ARG(powerdm, -1);
	CHECK_NULL_ARG(data, -1);

	pwrdm_list = powerdm_list_get();
	count = genlist_getcount((genlist *) pwrdm_list);
	for (i = 0; i < count; i++) {
		genlist_get((genlist *) pwrdm_list, i, (void *) data);
		if (strcmp(data->name, powerdm) == 0) {
			dprintf("%s(%s): found.\n", __func__, powerdm);
			return 0;
		}
	}

	dprintf("%s(%s): not found!\n", __func__, powerdm);
	return -1;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		powerdm_has_last_power_state
 * @BRIEF		return 1 if power domain has LASTPOWERSTATEENTERED
 * @RETURNS		1 if power domain has a LASTPOWERSTATEENTERED bitfield.
 *			0 if not available or in case of error.
 * @param[in]		powerdm: power domain name
 * @DESCRIPTION		return 1 if power domain has LASTPOWERSTATEENTERED
 *			in PM_xyz_PWRSTST register (not all power domains
 *			feature it).
 *			Return 0 if not available or in case of error.
 *			Does not make any access to any register.
 *//*------------------------------------------------------------------------ */
unsigned int powerdm_has_last_power_state(const char *powerdm)
{
	int ret;
	powerdm_info data;

	CHECK_NULL_ARG(powerdm, 0);

	ret = _powerdm_info_get(powerdm, &data);
	if (ret != 0) {
		dprintf("%s(%s): could not retrieve powerdm_info struct!\n",
			__func__, powerdm);
		return 0;
	}

	if ((data.properties & PWRDM_HAS_LAST_STATE) != 0) {
		dprintf("%s(%s): HAS LASTPOWERSTATEENTERED bitfield\n",
			__func__, powerdm);
		return 1;
	} else {
		dprintf(
			"%s(%s): does NOT have LASTPOWERSTATEENTERED bitfield\n",
			__func__, powerdm);
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		powerdm_has_logic_ret_state_ctrl_bit
 * @BRIEF		return 1 if power domain has LOGICRETSTATE bitfield
 * @RETURNS		1 if power domain has a LOGICRETSTATE bitfield.
 *			0 if not available or in case of error.
 * @param[in]		powerdm: power domain name
 * @DESCRIPTION		return 1 if power domain has LOGICRETSTATE bitfield
 *			in PM_xyz_PWRSTCTRL register (not all power domains
 *			feature it).
 *			Return 0 if not available or in case of error.
 *			Does not make any access to any register.
 *//*------------------------------------------------------------------------ */
unsigned int powerdm_has_logic_ret_state_ctrl_bit(const char *powerdm)
{
	int ret;
	powerdm_info data;

	CHECK_NULL_ARG(powerdm, 0);

	ret = _powerdm_info_get(powerdm, &data);
	if (ret != 0) {
		dprintf("%s(%s): could not retrieve powerdm_info struct!\n",
			__func__, powerdm);
		return 0;
	}

	if ((data.properties & PWRDM_HAS_LOGIC_RET_STATE_CTRL_BIT) != 0) {
		dprintf("%s(%s): HAS LOGICRETSTATE bitfield\n",
			__func__, powerdm);
		return 1;
	} else {
		dprintf("%s(%s): does NOT have LOGICRETSTATE bitfield\n",
			__func__, powerdm);
		return 0;
	}
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		powerdm_id_get
 * @BRIEF		return the unique ID of a given power domain.
 * @RETURNS		>= 0 power domain ID
 *			-1 in case of error
 * @param[in]		powerdm: power domain name
 * @DESCRIPTION		return the unique ID of a given power domain.
 *//*------------------------------------------------------------------------ */
int powerdm_id_get(const char *powerdm)
{
	int id;
	powerdm_info data;

	CHECK_NULL_ARG(powerdm, -1);

	id = _powerdm_info_get(powerdm, &data);
	if (id == 0)
		id = data.id;

	dprintf("%s(%s) = %d\n", __func__, powerdm, id);
	return id;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		powerdm_voltdm_get
 * @BRIEF		return the voltage domain name a power domain is part of
 * @RETURNS		voltage domain name on success.
 *			NULL in case of error
 * @param[in]		powerdm: power domain name
 * @DESCRIPTION		return the voltage domain name a power domain is part of
 *//*------------------------------------------------------------------------ */
const char *powerdm_voltdm_get(const char *powerdm)
{
	int ret;
	powerdm_info data;

	CHECK_NULL_ARG(powerdm, NULL);

	ret = _powerdm_info_get(powerdm, &data);
	if (ret != 0) {
		dprintf("%s(%s): could not retrieve powerdm_info struct!\n",
			__func__, powerdm);
		return NULL;
	}

	dprintf("%s(%s) = %s\n", __func__, powerdm, data.voltdm);
	return data.voltdm;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		powerdm_pwrstctrl_reg_get
 * @BRIEF		return the PWRSTCTRL register of a given power domain
 * @RETURNS		PWRSTCTRL register on success
 *			NULL in case of error
 * @param[in]		powerdm: power domain name
 * @DESCRIPTION		return the PWRSTCTRL register of a given power domain
 *//*------------------------------------------------------------------------ */
reg *powerdm_pwrstctrl_reg_get(const char *powerdm)
{
	int ret;
	powerdm_info data;

	CHECK_NULL_ARG(powerdm, NULL);

	ret = _powerdm_info_get(powerdm, &data);
	if (ret != 0) {
		dprintf("%s(%s): could not retrieve powerdm_info struct!\n",
			__func__, powerdm);
		return NULL;
	}

	if (data.pwrstctrl != NULL) {
		dprintf("%s(%s): PM_PWRSTCTRL=%s\n", __func__,
			powerdm, reg_name_get(data.pwrstctrl));
		return data.pwrstctrl;
	} else {
		dprintf("%s(%s): PM_PWRSTCTRL==NULL\n", __func__, powerdm);
		return NULL;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		powerdm_pwrstst_reg_get
 * @BRIEF		return the PWRSTST register of a given power domain
 * @RETURNS		PWRSTST register on success
 *			NULL in case of error
 * @param[in]		powerdm: power domain name
 * @DESCRIPTION		return the PWRSTST register of a given power domain
 *//*------------------------------------------------------------------------ */
reg *powerdm_pwrstst_reg_get(const char *powerdm)
{
	int ret;
	powerdm_info data;

	CHECK_NULL_ARG(powerdm, NULL);

	ret = _powerdm_info_get(powerdm, &data);
	if (ret != 0) {
		dprintf("%s(%s): could not retrieve powerdm_info struct!\n",
			__func__, powerdm);
		return NULL;
	}

	if (data.pwrstst != NULL) {
		dprintf("%s(%s): PM_PWRSTST=%s\n", __func__,
			powerdm, reg_name_get(data.pwrstst));
		return data.pwrstst;
	} else {
		dprintf("%s(%s): PM_PWRSTST==NULL\n", __func__, powerdm);
		return NULL;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		powerdm_target_logic_ret_state_get
 * @BRIEF		return the programmed target logic retention state
 *			of a given power domain
 * @RETURNS		programmed target logic retention state on success
 *			PWRDM_STATE_MAX in case of error
 * @param[in]		powerdm: power domain name
 * @DESCRIPTION		return the programmed target logic retention state
 *			of a given power domain
 *//*------------------------------------------------------------------------ */
pwrdm_state powerdm_target_logic_ret_state_get(const char *powerdm)
{
	reg *pm_pwrstctrl;
	pwrdm_state state;

	CHECK_NULL_ARG(powerdm, PWRDM_STATE_MAX);

	if (!powerdm_has_logic_ret_state_ctrl_bit(powerdm)) {
		dprintf("%s(%s): domain doesn't have RET state control bit.\n",
			__func__, powerdm);
		return PWRDM_STATE_MAX;
	}

	pm_pwrstctrl = powerdm_pwrstctrl_reg_get(powerdm);
	if (pm_pwrstctrl == NULL) {
		dprintf("%s(%s): PM_PWRSTCTRL==NULL!\n", __func__, powerdm);
		return PWRDM_STATE_MAX;
	}

	state = pwrdm_target_logic_ret_state_get(pm_pwrstctrl);
	dprintf("%s(%s) = %s\n", __func__, powerdm,
		pwrdm_state_name_get(state));
	return state;
}



/* ------------------------------------------------------------------------*//**
 * @FUNCTION		powerdm_logic_state_get
 * @BRIEF		return the current logic state of a given power domain
 * @RETURNS		current logic state on success
 *			PWRDM_STATE_MAX in case of error
 * @param[in]		powerdm: power domain name
 * @DESCRIPTION		return the current logic state of a given power domain
 *//*------------------------------------------------------------------------ */
pwrdm_state powerdm_logic_state_get(const char *powerdm)
{
	reg *pm_pwrstst;
	pwrdm_state state;

	CHECK_NULL_ARG(powerdm, PWRDM_STATE_MAX);

	pm_pwrstst = powerdm_pwrstst_reg_get(powerdm);
	if (pm_pwrstst == NULL) {
		dprintf("%s(%s): PM_PWRSTST==NULL!\n", __func__, powerdm);
		return PWRDM_STATE_MAX;
	}

	state = pwrdm_logic_state_get(pm_pwrstst);
	dprintf("%s(%s) = %s\n", __func__, powerdm,
		pwrdm_state_name_get(state));
	return state;
}



/* ------------------------------------------------------------------------*//**
 * @FUNCTION		powerdm_state_get
 * @BRIEF		return the previous/current/target state of
 *			a given power domain
 * @RETURNS		domain previous/current/target state on success
 *			PWRDM_STATE_MAX in case of error
 * @param[in]		powerdm: power domain name
 * @param[in]		type: power domain state type
 * @DESCRIPTION		return the previous/current/target state of
 *			a given power domain
 *//*------------------------------------------------------------------------ */
pwrdm_state powerdm_state_get(const char *powerdm, pwrdm_state_type type)
{
	reg *pm_reg;
	pwrdm_state state;

	CHECK_NULL_ARG(powerdm, PWRDM_STATE_MAX);
	CHECK_ARG_LESS_THAN(type, PWRDM_STATE_TYPE_MAX, PWRDM_STATE_MAX);

	/* Retrieve registers address */
	switch (type) {
	case PWRDM_STATE_TARGET:
		pm_reg = powerdm_pwrstctrl_reg_get(powerdm);
		break;
	case PWRDM_STATE_CURRENT:
	case PWRDM_STATE_PREVIOUS:
		pm_reg = powerdm_pwrstst_reg_get(powerdm);
		break;
	default:
		fprintf(stderr,
			"omapconf: %s(%s): invalid type (%d)!\n",
			__func__, powerdm, type);
		return PWRDM_STATE_MAX;
	}

	if (pm_reg == NULL) {
		/* Always ON domain */
		dprintf("%s(%s): Always ON domain\n", __func__, powerdm);
		return PWRDM_ON_STATE;
	}

	/* Retrieve power domain state */
	state = pwrdm_state_get(pm_reg, type);
	dprintf("%s(%s, %s) = %s\n", __func__, powerdm,
		pwrdm_state_type_name_get(type),
		pwrdm_state_name_get(state));
	return state;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		powerdm_in_transition
 * @BRIEF		return 1 if a power transition is ongoing
 *			on a given power domain
 * @RETURNS		1 if a power transition is ongoing
 *			0 if NO power transition is ongoing (or error)
 * @param[in]		powerdm: power domain name
 * @DESCRIPTION		return 1 if a power transition is ongoing
 *			on a given power domain
 *//*------------------------------------------------------------------------ */
unsigned int powerdm_in_transition(const char *powerdm)
{
	int in_transition;
	reg *pm_pwrstst;

	CHECK_NULL_ARG(powerdm, 0);

	pm_pwrstst = powerdm_pwrstst_reg_get(powerdm);
	if (pm_pwrstst == NULL) {
		dprintf("%s(%s): PM_PWRSTST==NULL!\n", __func__, powerdm);
		return 0;
	}

	in_transition = pwrdm_in_transition(pm_pwrstst);
	#ifdef PWRDM_DEBUG
	if (in_transition)
		printf("%s(%s): power transition ONGOING.\n",
			__func__, powerdm);
	else
		printf("%s(%s): NO power transition ongoing.\n",
			__func__, powerdm);
	#endif

	return in_transition;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		powerdm_config_show
 * @BRIEF		decode and display power domain configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in,out]	stream: output file
 * @param[in]		powerdm: power domain name
 * @DESCRIPTION		decode and display power domain configuration
 *//*------------------------------------------------------------------------ */
int powerdm_config_show(FILE *stream, const char *powerdm)
{
	int ret;
	powerdm_info data;
	pwrdm_state st_last, st_curr, st_tgt;
	reg *pm_pwrstctrl;
	reg *pm_pwrstst;
	char s[64];
	char s1[32], s2[32];

	CHECK_NULL_ARG(stream, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(powerdm, OMAPCONF_ERR_ARG);

	ret = _powerdm_info_get(powerdm, &data);
	if (ret != 0) {
		dprintf("%s(%s): could not retrieve powerdm_info struct!\n",
			__func__, powerdm);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	fprintf(stream,
		"|----------------------------------------------------------------|\n");
	strcpy(s, powerdm);
	strcat(s, " Power Domain Configuration");
	fprintf(stream, "| %-62s |\n", s);
	fprintf(stream,
		"|----------------------------------------------------------------|\n");
	fprintf(stream, "| %-32s | %-7s | %-7s | %-7s |\n", "Power State",
		"Current", "Target", "Last");
	fprintf(stream,
		"|----------------------------------|---------|---------|---------|\n");

	st_last = powerdm_state_get(powerdm, PWRDM_STATE_PREVIOUS);
	st_curr = powerdm_state_get(powerdm, PWRDM_STATE_CURRENT);
	st_tgt = powerdm_state_get(powerdm, PWRDM_STATE_TARGET);
	fprintf(stream, "| %-32s | %-7s | %-7s | %-7s |\n",
		"Domain", pwrdm_state_name_get(st_curr),
		pwrdm_state_name_get(st_tgt), pwrdm_state_name_get(st_last));

	if ((!powerdm_has_logic_ret_state_ctrl_bit(powerdm)) &&
		(data.pwrstst == NULL))
		goto powerdm_config_show_mem;

	st_tgt = powerdm_target_logic_ret_state_get(powerdm);
	if (st_tgt != PWRDM_STATE_MAX)
		strcpy(s1, pwrdm_state_name_get(st_tgt));
	else
		strcpy(s1, "");
	st_curr = powerdm_logic_state_get(powerdm);
	if (st_curr != PWRDM_STATE_MAX)
		strcpy(s2, pwrdm_state_name_get(st_curr));
	else
		strcpy(s2, "");
	fprintf(stream, "| %-32s | %-7s | %-7s |         |\n", "Logic", s2, s1);

powerdm_config_show_mem:
	if (cpu_is_omap44xx()) {
		pm_pwrstctrl = powerdm_pwrstctrl_reg_get(powerdm);
		pm_pwrstst = powerdm_pwrstst_reg_get(powerdm);
		ret = pwrdm44xx_config_show(stream, powerdm,
			reg_addr_get(pm_pwrstctrl),
			reg_read(pm_pwrstctrl),
			reg_addr_get(pm_pwrstst),
			reg_read(pm_pwrstst));
	} else if (cpu_is_omap54xx()) {
		ret = pwrdm54xx_config_show(stream, data);
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		ret = OMAPCONF_ERR_CPU;
	}

	if (data.pwrstst != NULL) {
		fprintf(stream,
			"|----------------------------------------------------------------|\n");

		fprintf(stream, "| %-32s | %-27s |\n",
			"Ongoing Power Transition?",
			((powerdm_in_transition(powerdm) == 1) ? "YES" : "NO"));
	}
	fprintf(stream,
		"|----------------------------------------------------------------|\n\n");

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		powerdm_emu_enable
 * @BRIEF		Power ON EMU domain and clocks.
 * @DESCRIPTION		Power ON EMU domain and clocks.
 *//*------------------------------------------------------------------------ */
void powerdm_emu_enable(void)
{
	if (cpu_is_omap44xx()) {
		mem_write(OMAP4430_CM_L3INSTR_L3_3_CLKCTRL, 0x1);
	} else if (cpu_is_omap54xx()) {
		if (cpu_revision_get() == REV_ES1_0)
			mem_write(OMAP5430ES1_CM_L3INSTR_L3_MAIN_3_CLKCTRL,
				0x1);
		else
			mem_write(OMAP5430_CM_L3INSTR_L3_MAIN_3_CLKCTRL, 0x1);
	} else if (cpu_is_dra7xx()) {
		mem_write(DRA7XX_CORE_CM_CORE_CM_L3MAIN1_CLKSTCTRL, 0x1);
		mem_write(DRA7XX_CORE_CM_CORE_CM_L3INSTR_L3_MAIN_2_CLKCTRL, 0x1);
		mem_write(DRA7XX_CORE_CM_CORE_CM_L3INSTR_L3_INSTR_CLKCTRL, 0x1);
	} else {
		fprintf(stderr,
			"omapconf: %s(): warning: cpu not supported, skipping it.\n",
			__func__);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		powerdm_emu_disable
 * @BRIEF		Power OFF EMU domain and clocks.
 * @DESCRIPTION		Power OFF EMU domain and clocks.
 *//*------------------------------------------------------------------------ */
void powerdm_emu_disable(void)
{
	if (cpu_is_omap44xx()) {
		mem_write(OMAP4430_CM_L3INSTR_L3_3_CLKCTRL, 0);
	} else if (cpu_is_omap54xx()) {
		if (cpu_revision_get() == REV_ES1_0)
			mem_write(OMAP5430ES1_CM_L3INSTR_L3_MAIN_3_CLKCTRL,
				0x0);
		else
			mem_write(OMAP5430_CM_L3INSTR_L3_MAIN_3_CLKCTRL, 0x0);
	} else if (cpu_is_dra7xx()) {
		mem_write(DRA7XX_CORE_CM_CORE_CM_L3MAIN1_CLKSTCTRL, 0x0);
		mem_write(DRA7XX_CORE_CM_CORE_CM_L3INSTR_L3_MAIN_2_CLKCTRL, 0x0);
		mem_write(DRA7XX_CORE_CM_CORE_CM_L3INSTR_L3_INSTR_CLKCTRL, 0x0);
	} else {
		fprintf(stderr,
			"omapconf: %s(): warning: cpu not supported, skipping it.\n",
			__func__);
	}
}
