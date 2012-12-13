/*
 *
 * @Component			OMAPCONF
 * @Filename			pwrdm.h
 * @Description			OMAP Power Domain Definitions & APIs
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


#ifndef __PRCM_PWRDM_H__
#define __PRCM_PWRDM_H__


#include <reg.h>


#define PWRDM_STATE_MAX_NAME_LENGTH	8


#define PWRDM_HAS_LAST_STATE			(1 << 0) /* bits [25-24] */
#define PWRDM_HAS_LOGIC_RET_STATE_CTRL_BIT	(1 << 1) /* bit 2 */


typedef enum {
	PWRDM_OFF_STATE = 0,
	PWRDM_RET_STATE = 1,
	PWRDM_INACTIVE_STATE = 2,
	PWRDM_ON_STATE = 3,
	PWRDM_STATE_MAX
} pwrdm_state;


typedef enum {
	PWRDM_STATE_PREVIOUS,
	PWRDM_STATE_CURRENT,
	PWRDM_STATE_TARGET,
	PWRDM_STATE_TYPE_MAX
} pwrdm_state_type;


pwrdm_state pwrdm_state_get(reg *pm_pwrst, pwrdm_state_type type);
pwrdm_state pwrdm_target_logic_ret_state_get(reg *pm_pwrstctrl);
pwrdm_state pwrdm_logic_state_get(reg *pm_pwrstst);
unsigned int pwrdm_in_transition(reg *pm_pwrstst);
const char *pwrdm_state_name_get(pwrdm_state st);
const char *pwrdm_state_type_name_get(pwrdm_state_type type);

/* FIXME: DEPRECATED FUNCTION. Update OMAP4 code to use new functions ... */
int pwrdm_state2string(char s[6], pwrdm_state powerstate);
int pwrdm_states_get(char *name, char pwst[6], char pwtgst[6]);


#endif
