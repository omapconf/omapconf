/*
 *
 * @Component			OMAPCONF
 * @Filename			pwrdm44xx.h
 * @Description			OMAP4 Power Domain Definitions & Functions
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


#ifndef __PWRDM44XX_H__
#define __PWRDM44XX_H__


#include <powerdomain.h>
#include <pwrdm.h>
#include <voltdm44xx.h>

#define PWRDM44XX_MAX_NAME_LENGTH		16


typedef enum {
	OMAP4_PD_WKUP,
	OMAP4_PD_EMU,
	OMAP4_PD_MPU,
	OMAP4_PD_ALWON_MPU,
	OMAP4_PD_ABE,
	OMAP4_PD_IVA_HD,
	OMAP4_PD_DSP,
	OMAP4_PD_ALWON_IVA,
	OMAP4_PD_ALWON_CORE,
	OMAP4_PD_CORE,
	OMAP4_PD_STD_EFUSE,
	OMAP4_PD_CUST_EFUSE,
	OMAP4_PD_CAM,
	OMAP4_PD_DSS,
	OMAP4_PD_GFX,
	OMAP4_PD_L3_INIT,
	OMAP4_PD_L4_PER,
	OMAP4_PD_ID_MAX
} pwrdm44xx_id;


void pwrdm44xx_init(void);
void pwrdm44xx_deinit(void);

int pwrdm44xx_count_get(void);
const genlist *pwrdm44xx_list_get(void);


char *pwrdm44xx_get_name(pwrdm44xx_id id, char name[PWRDM44XX_MAX_NAME_LENGTH]);
voltdm44xx_id pwrdm44xx_get_voltdm(pwrdm44xx_id id);
int pwrdm_states_get(char *name, char pwst[6], char pwtgst[6]);
int pwrdm44xx_get_state(pwrdm44xx_id pd_id,
	pwrdm_state *state);

int pwrdm44xx_config_show(FILE *stream, const char name[11],
	unsigned int pm_pwstctrl_addr, unsigned int pm_pwstctrl,
	unsigned int pm_pwstst_addr, unsigned int pm_pwstst);


#endif
