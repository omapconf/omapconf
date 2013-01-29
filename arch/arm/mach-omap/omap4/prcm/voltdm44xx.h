/*
 *
 * @Component			OMAPCONF
 * @Filename			voltdm44xx.h
 * @Description			OMAP4 Voltage Domain Definitions & APIs
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


#ifndef __VOLTDM44XX_H__
#define __VOLTDM44XX_H__


#include <genlist.h>


#define VOLTDM44XX_MAX_NAME_LENGTH	12
#define OPP44XX_MAX_NAME_LENGTH	16

typedef enum {
	OMAP4_LDO_WKUP,
	OMAP4_VDD_MPU,
	OMAP4_VDD_IVA,
	OMAP4_VDD_CORE,
	OMAP4_VD_ID_MAX
} voltdm44xx_id;


typedef enum {
	OMAP4_OPPDPLL_CASC,
	OMAP4_OPP50,
	OMAP4_OPP100,
	OMAP4_OPP_TURBO,
	OMAP4_OPP_NITRO,
	OMAP4_OPP_NITRO_SB,
	OMAP4_OPP_119,
	OPP44XX_ID_MAX
} opp44xx_id;

typedef enum {
	OMAP447X_OPPDPLL_CASC,
	OMAP447X_OPP50_LOW,
	OMAP447X_OPP50_HIGH,
	OMAP447X_OPP100_LOW,
	OMAP447X_OPP119_LOW,
	OMAP447X_OPP119_HIGH,
	OMAP447X_OPP100_HIGH,
} omap447X_opp_id;

typedef enum {
	OMAP4_OFF_VOLTAGE = 0,
	OMAP4_RETENTION_VOLTAGE = 8,
	OMAP4_ON_LOW_POWER_VOLTAGE = 16,
	OMAP4_ON_VOLTAGE = 24,
	OMAP4_VOLTAGE_TYPE_MAX
} voltdm44xx_voltage_type;


char *voltdm44xx_get_name(voltdm44xx_id id,
	char name[VOLTDM44XX_MAX_NAME_LENGTH]);

voltdm44xx_id voltdm44xx_s2id(char *s);

void voltdm44xx_init(void);
void voltdm44xx_deinit(void);

const genlist *voltdm44xx_list_get(void);
int voltdm44xx_count_get(void);

double voltdm44xx_retention_voltage_get(voltdm44xx_id id);
double voltdm44xx_por_retention_voltage_get(voltdm44xx_id id);
double voltdm44xx_nominal_voltage_get(voltdm44xx_id id);
double voltdm44xx_por_nominal_voltage_get(voltdm44xx_id id, opp44xx_id opp);

const char *opp44xx_name_get(unsigned short opp_id, voltdm44xx_id vdd_id);

int voltdm44xx_get_opp(voltdm44xx_id id, opp44xx_id *opp);
int voltdm44xx_get_voltage(voltdm44xx_id id, double *volt);
int voltdm44xx_get_voltage_by_type(voltdm44xx_id id,
	voltdm44xx_voltage_type type, double *volt);


unsigned int opp44xx_s2id(char *s);

const char *voltdm44xx_id2s(voltdm44xx_id id);
int voltdm44xx_vminsearch(voltdm44xx_id vdd_id, double v, unsigned int ms);


/* WARNING: DEPRECATED (use opp44xx_name_get() instead) */
int voltdm44xx_opp2string(char s[OPP44XX_MAX_NAME_LENGTH],
	unsigned short opp, voltdm44xx_id vd_id);


#endif
