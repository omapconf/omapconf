/*
 *
 * @Component			OMAPCONF
 * @Filename			clkdm44xx.h
 * @Description			OMAP4 Clock Domain Definitions & Functions
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


#ifndef __CLKDM44XX_H__
#define __CLKDM44XX_H__


#include <clkdm.h>
#include <clkdm.h>
#include <pwrdm44xx.h>
#include <voltdm44xx.h>

#define CLKDM44XX_MAX_NAME_LENGTH		16

typedef enum {
	OMAP4_CD_WKUP,
	OMAP4_CD_EMU,
	OMAP4_CD_MPU,
	OMAP4_CD_ABE,
	OMAP4_CD_IVA_HD,
	OMAP4_CD_DSP,
	OMAP4_CD_AO_L4,
	OMAP4_CD_L4CFG,
	OMAP4_CD_C2C,
	OMAP4_CD_DMA,
	OMAP4_CD_MPU_M3,
	OMAP4_CD_L3_1,
	OMAP4_CD_L3_2,
	OMAP4_CD_L3_INSTR,
	OMAP4_CD_EMIF,
	OMAP4_CD_STD_EFUSE,
	OMAP4_CD_CUST_EFUSE,
	OMAP4_CD_CAM,
	OMAP4_CD_DSS,
	OMAP4_CD_GFX,
	OMAP4_CD_L3_INIT,
	OMAP4_CD_L4_SEC,
	OMAP4_CD_L4_PER,
	OMAP4_CD_NONE, /* for PRCM own clock */
	OMAP4_CD_ID_MAX
} clkdm44xx_id;


void clkdm44xx_init(void);
void clkdm44xx_deinit(void);

int clkdm44xx_count_get(void);
const genlist *clkdm44xx_list_get(void);


char *clkdm44xx_get_name(clkdm44xx_id id, char name[CLKDM44XX_MAX_NAME_LENGTH]);
pwrdm44xx_id clkdm44xx_get_pwrdm(clkdm44xx_id id);
voltdm44xx_id clkdm44xx_get_voltdm(clkdm44xx_id id);
int clkdm44xx_get_status(clkdm44xx_id cd_id,
	clkdm_status *clkst);

int clkdm44xx_config_show(FILE *stream, const char name[11],
	unsigned int cm_clkstctrl_addr,	unsigned int cm_clkstctrl);


#endif
