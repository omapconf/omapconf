/*
 *
 * @Component			OMAPCONF
 * @Filename			clkdm54xx.h
 * @Description			OMAP5 Clock Domain Definitions & APIs
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


#ifndef __CLKDM54XX_H__
#define __CLKDM54XX_H__


#include <clockdomain.h>
#include <clkdm.h>
#include <pwrdm54xx.h>
#include <voltdm54xx.h>


#define CLKDM54XX_MAX_NAME_LENGTH		12


typedef enum {
	CLKDM54XX_EMU,
	CLKDM54XX_WKUPAON,
	CLKDM54XX_COREAON,
	CLKDM54XX_CAM,
	CLKDM54XX_L4_CFG,
	CLKDM54XX_EMIF,
	CLKDM54XX_IPU,
	CLKDM54XX_L3_MAIN2,
	CLKDM54XX_L3_INSTR,
	CLKDM54XX_L3_MAIN1,
	CLKDM54XX_C2C,
	CLKDM54XX_DMA,
	CLKDM54XX_MIPIEXT,
	CLKDM54XX_DSS,
	CLKDM54XX_CUST_EFUSE,
	CLKDM54XX_L3_INIT,
	CLKDM54XX_L4_PER,
	CLKDM54XX_L4_SEC,
	CLKDM54XX_ABE,
	CLKDM54XX_DSP,
	CLKDM54XX_GPU,
	CLKDM54XX_IVA,
	CLKDM54XX_MPU,
	CLKDM54XX_NONE, /* for PRCM own clock */
	CLKDM54XX_ID_MAX
} clkdm54xx_id;


void clkdm54xx_init(void);
void clkdm54xx_deinit(void);

int clkdm54xx_count_get(void);
const genlist *clkdm54xx_list_get(void);

const char *clkdm54xx_name_get(clkdm54xx_id id);

clkdm54xx_id clkdm54xx_s2id(char *s);
int clkdm54xx_config_show(FILE *stream, clockdm_info clkdm);


#endif
