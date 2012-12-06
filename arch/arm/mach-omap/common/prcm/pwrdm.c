/*
 *
 * @Component			OMAPCONF
 * @Filename			pwrdm.c
 * @Description			OMAP Power Domain APIs
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


#include <pwrdm.h>
#include <lib.h>
#include <mem.h>
#include <stdio.h>
#include <string.h>


/* #define PRCM_PWRDM_DEBUG */
#ifdef PRCM_PWRDM_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static const char
	pwrdm_state_names[PWRDM_STATE_MAX][PWRDM_STATE_MAX_NAME_LENGTH] = {
	"OFF",
	"RET",
	"INACT",
	"ON"};


static const char
	pwrdm_state_type_names[PWRDM_STATE_TYPE_MAX][PWRDM_STATE_MAX_NAME_LENGTH] = {
	"PREVIOUS",
	"CURRENT",
	"TARGET"};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm_state_name_get
 * @BRIEF		return power domain state name
 * @RETURNS		power domain state name on success
 *			NULL in case of error
 * @param[in]		st: valid power domain state
 * @DESCRIPTION		return power domain state name
 *//*------------------------------------------------------------------------ */
const char *pwrdm_state_name_get(pwrdm_state st)
{
	CHECK_ARG_LESS_THAN(st, PWRDM_STATE_MAX, NULL);

	return pwrdm_state_names[st];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm_state_type_name_get
 * @BRIEF		return power domain state type name
 * @RETURNS		power domain state type name on success
 *			NULL in case of error
 * @param[in]		type: valid power domain state type
 * @DESCRIPTION		return power domain state type name
 *//*------------------------------------------------------------------------ */
const char *pwrdm_state_type_name_get(pwrdm_state_type type)
{
	CHECK_ARG_LESS_THAN(type, PWRDM_STATE_TYPE_MAX, NULL);

	return pwrdm_state_type_names[type];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm_state_get
 * @BRIEF		return power domain state
 * @RETURNS		power domain state on success
 *			PWRDM_STATE_MAX in case of error
 * @param[in]		pm_pwrst: PM_xyz_PWRST[CTRL-ST] register
 * @param[in]		type: pwrdm state type
 * @DESCRIPTION		return power domain state
 *//*------------------------------------------------------------------------ */
pwrdm_state pwrdm_state_get(reg *pm_pwrst, pwrdm_state_type type)
{
	pwrdm_state st;
	unsigned int val;

	CHECK_NULL_ARG(pm_pwrst, PWRDM_STATE_MAX);

	/* Retrieve registers content */
	val = reg_read(pm_pwrst);
	dprintf("%s(%s): addr=0x%08X val=0x%08X\n", __func__,
		pm_pwrst->name, pm_pwrst->addr, val);

	/* Retrieve power domain state */
	if (type == PWRDM_STATE_PREVIOUS)
		st = (pwrdm_state) extract_bitfield(val, 24, 2);
	else
		st = (pwrdm_state) extract_bitfield(val, 0, 2);
	dprintf("%s(%s): state=%u (%s)\n", __func__,
		pm_pwrst->name, st, pwrdm_state_name_get(st));

	return st;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm_target_logic_ret_state_get
 * @BRIEF		return logic target state for this power domain
 *			when domain is RET
 * @RETURNS		power domain logic state when domain is RET:
 *			PWRDM_OFF_STATE or PWRDM_RET_STATE
 *			PWRDM_STATE_MAX in case of error
 * @param[in]		pm_pwrstctrl: PM_xyz_PWRSTCTRL register
 * @DESCRIPTION		return logic target state for this power domain when
 *			domain is RET
 *//*------------------------------------------------------------------------ */
pwrdm_state pwrdm_target_logic_ret_state_get(reg *pm_pwrstctrl)
{
	pwrdm_state st;
	unsigned int val;

	CHECK_NULL_ARG(pm_pwrstctrl, PWRDM_STATE_MAX);

	/* Retrieve registers content */
	val = reg_read(pm_pwrstctrl);
	/* Retrieve power domain state */
	if (extract_bit(val, 2) == 1)
		st = PWRDM_RET_STATE;
	else
		st = PWRDM_OFF_STATE;
	dprintf(
		"%s(%s): addr=0x%08X val=0x%08X LOGICRETSTATE (bit 2)=%u logic target RET state=%s\n",
		__func__,
		pm_pwrstctrl->name, pm_pwrstctrl->addr, val,
		extract_bit(val, 2), pwrdm_state_name_get(st));

	return st;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm_logic_state_get
 * @BRIEF		return logic state for this power domain
 * @RETURNS		power domain logic state:
 *			PWRDM_OFF_STATE or PWRDM_ON_STATE
 *			PWRDM_STATE_MAX in case of error
 * @param[in]		pm_pwrstst: PM_xyz_PWRSTST register
 * @DESCRIPTION		return logic state for this power domain
 *//*------------------------------------------------------------------------ */
pwrdm_state pwrdm_logic_state_get(reg *pm_pwrstst)
{
	pwrdm_state st;
	unsigned int val;

	CHECK_NULL_ARG(pm_pwrstst, PWRDM_STATE_MAX);

	/* Retrieve registers content */
	val = reg_read(pm_pwrstst);
	/* Retrieve power domain state */
	if (extract_bit(val, 2) == 1)
		st = PWRDM_ON_STATE;
	else
		st = PWRDM_OFF_STATE;
	dprintf(
		"%s(%s): addr=0x%08X val=0x%08X LOGICRETSTATE (bit 2)=%u logic state=%s\n",
		__func__,
		pm_pwrstst->name, pm_pwrstst->addr, val,
		extract_bit(val, 2), pwrdm_state_name_get(st));

	return st;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm_in_transition
 * @BRIEF		return 1 if power domain is in transition, 0 otherwise
 * @RETURNS		return 1 if power domain is in transition, 0 otherwise
 * @param[in]		pm_pwrstst: PM_xyz_PWRSTST register
 * @DESCRIPTION		return 1 if power domain is in transition, 0 otherwise
 *//*------------------------------------------------------------------------ */
unsigned int pwrdm_in_transition(reg *pm_pwrstst)
{
	unsigned int val;

	CHECK_NULL_ARG(pm_pwrstst, 0);

	/* Retrieve registers content */
	val = reg_read(pm_pwrstst);
	/* Retrieve power domain intransition status */
	dprintf("%s(%s): addr=0x%08X val=0x%08X INTRANSITION (bit 20)=%u\n",
		__func__, pm_pwrstst->name,
		pm_pwrstst->addr, val, extract_bit(val, 20));
	return extract_bit(val, 20);
}


/* FIXME: DEPRECATED FUNCTION. Update OMAP4 code to use new functions ... */
/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm_state2string
 * @BRIEF		convert powerstate into string
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	s: destination string (pre-allocated)
 * @param[in]		powerstate: powerstate
 * @DESCRIPTION		convert powerstate into string
 *//*------------------------------------------------------------------------ */
int pwrdm_state2string(char s[6], pwrdm_state powerstate)
{
	if (s == NULL)
		return OMAPCONF_ERR_ARG;

	switch (powerstate) {
	case PWRDM_OFF_STATE:
		strcpy(s, "OFF");
		break;
	case PWRDM_RET_STATE:
		strcpy(s, "RET");
		break;
	case PWRDM_INACTIVE_STATE:
		strcpy(s, "INACT");
		break;
	case PWRDM_ON_STATE:
		strcpy(s, "ON");
		break;
	default:
		strcpy(s, "FIXME");
		return OMAPCONF_ERR_ARG;
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm_states_get
 * @BRIEF		extract power domain states (current, target)
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in]		name: domain name (MPU, CORE, PER, ...)
 * @param[in,out]	pwst: domain current state string
 *				(must be pre-allocated)
 * @param[in,out]	pwtgst: domain target state string
 *				(must be pre-allocated)
 * @DESCRIPTION		extract power domain states (current, target)
 *			from register into strings.
 *//*------------------------------------------------------------------------ */
int pwrdm_states_get(char *name, char pwst[6], char pwtgst[6])
{
	unsigned int pwrstst, pwrstctrl;

	char pm_pwrstst_name[OMAPCONF_REG_NAME_MAX_LENGTH] = "PM_";
	char pm_pwrstctrl_name[OMAPCONF_REG_NAME_MAX_LENGTH] = "PM_";
	unsigned int pm_pwrstst_addr;
	unsigned int pm_pwrstctrl_addr;

	if ((name == NULL) ||
		(pwst == NULL) ||
		(pwtgst == NULL))
		return OMAPCONF_ERR_ARG;

	/* Retrieve register names */
	strcat(pm_pwrstst_name, name);
	strcat(pm_pwrstst_name, "_PWRSTST");
	strcat(pm_pwrstctrl_name, name);
	strcat(pm_pwrstctrl_name, "_PWRSTCTRL");
	dprintf("pm_pwrstst_name=%s pm_pwrstctrl_name=%s\n",
		pm_pwrstst_name, pm_pwrstctrl_name);

	/* Retrieve registers address */
	if (find_reg_addr(pm_pwrstst_name, &pm_pwrstst_addr) != 0) {
		printf("pm_pwrstst_name = %s not found!\n",
			pm_pwrstst_name);
		return OMAPCONF_ERR_ARG;
	}
	if (find_reg_addr(pm_pwrstctrl_name, &pm_pwrstctrl_addr) != 0) {
		printf("pm_pwrstctrl_name = %s not found!\n",
			pm_pwrstctrl_name);
		return OMAPCONF_ERR_ARG;
	}
	dprintf("pm_pwrstst_addr=0x%08X pm_pwrstctrl_addr=0x%08X\n",
		pm_pwrstst_addr, pm_pwrstctrl_addr);

	/* Retrieve registers content */
	mem_read(pm_pwrstst_addr, &pwrstst);
	mem_read(pm_pwrstctrl_addr, &pwrstctrl);

	/* Retrieve power domain current & target states */
	pwrdm_state2string(pwst,
		(pwrdm_state) extract_bitfield(pwrstst, 0, 2));
	pwrdm_state2string(pwtgst,
		(pwrdm_state) extract_bitfield(pwrstctrl, 0, 2));
	dprintf("pwst=%s pwtgst=%s\n", pwst, pwtgst);

	return 0;
}
