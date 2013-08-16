/*
 *
 * @Component			OMAPCONF
 * @Filename			voltdm_dra7xx.h
 * @Description			DRA7 Voltage Domain Definitions & APIs
 * @Author			Jin Zheng (j-zheng@ti.com)
 * @Date			2013
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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


#ifndef __VOLTDM_DRA7XX_H__
#define __VOLTDM_DRA7XX_H__


#include <lib.h>
#include <genlist.h>


typedef enum {
	VDD_DRA7XX_CORE,
	VDD_DRA7XX_MPU,
	VDD_DRA7XX_IVA,
	VDD_DRA7XX_DSPEVE,
	VDD_DRA7XX_GPU,
	VDD_DRA7XX_RTC,
	VDD_DRA7XX_ID_MAX
} voltdm_dra7xx_id;


typedef enum {
	OPP_DRA7XX_NOM,
	OPP_DRA7XX_OD,
	OPP_DRA7XX_HIGH,
	OPP_DRA7XX_ID_MAX
} opp_dra7xx_id;


void voltdm_dra7xx_init(void);
void voltdm_dra7xx_deinit(void);

const genlist *voltdm_dra7xx_list_get(void);
int voltdm_dra7xx_count_get(void);

const char *voltdm_dra7xx_name_get(voltdm_dra7xx_id id);
opp_dra7xx_id opp_dra7xx_s2id(char *s);
const char *voltdm_dra7xx_id2s(voltdm_dra7xx_id id);
const char *opp_dra7xx_name_get(opp_dra7xx_id id);

double voltdm_dra7xx_voltage_get(voltdm_dra7xx_id id);
int voltdm_dra7xx_voltage_set(voltdm_dra7xx_id id, unsigned long uv);

double voltdm_dra7xx_por_nominal_voltage_get(voltdm_dra7xx_id id, opp_dra7xx_id opp_id);


#endif
