/*
 *
 * @Component			OMAPCONF
 * @Filename			voltdm54xx.h
 * @Description			OMAP5 Voltage Domain Definitions & APIs
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


#ifndef __VOLTDM54XX_H__
#define __VOLTDM54XX_H__


#include <lib.h>
#include <genlist.h>


typedef enum {
	VDD54XX_WKUP,
	VDD54XX_MPU,
	VDD54XX_MM,
	VDD54XX_CORE,
	VDD54XX_ID_MAX
} voltdm54xx_id;


typedef enum {
	OPP54XX_DPLL_CASC,
	OPP54XX_LOW,
	OPP54XX_NOM,
	OPP54XX_HIGH,
	OPP54XX_SB,
	OPP54XX_ID_MAX
} opp54xx_id;


void voltdm54xx_init(void);
void voltdm54xx_deinit(void);

const genlist *voltdm54xx_list_get(void);
int voltdm54xx_count_get(void);

const char *voltdm54xx_name_get(voltdm54xx_id id);
opp54xx_id opp54xx_s2id(char *s);
const char *voltdm54xx_id2s(voltdm54xx_id id);
const char *opp54xx_name_get(opp54xx_id id);

double voltdm54xx_voltage_get(voltdm54xx_id id);
int voltdm54xx_voltage_set(voltdm54xx_id id, unsigned long uv);

double voltdm54xx_nominal_voltage_get(voltdm54xx_id id);
double voltdm54xx_por_nominal_voltage_get(voltdm54xx_id id, opp54xx_id opp_id);


#endif
