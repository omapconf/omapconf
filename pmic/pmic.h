/*
 *
 * @Component			OMAPCONF
 * @Filename			pmic.h
 * @Description			OMAP Power Companion Chip Library
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


#ifndef __PMIC_H__
#define __PMIC_H__


#define PMIC_NAME_MAX_LENGTH		12
#define PMIC_SMPS_MAX_NUMBER		5


typedef enum {
	PMIC_TWL6030,
	PMIC_TWL6032,
	PMIC_TPS62361,
	PMIC_TWL6034,
	PMIC_TWL6035,
	PMIC_TPS659038,
	PMIC_TPS65217A,
	PMIC_TPS65217B,
	PMIC_TPS65217C,
	PMIC_TPS65217D,
	PMIC_TPS65917,
	PMIC_ID_MAX
} pmic_id;


typedef enum {
	PMIC_SMPS_MPU,
	PMIC_SMPS_MM,
	PMIC_SMPS_CORE,
	PMIC_SMPS_GPU,
	PMIC_SMPS_DSPEVE,
	PMIC_SMPS_ID_MAX
} pmic_smps_id;


void pmic_smps_init(pmic_smps_id id, unsigned short is_twl6030,
		unsigned short is_twl6032, unsigned short is_twl6034,
		unsigned short is_twl6035, unsigned short tps62361_present,
		unsigned short tps659038_present,
		unsigned short tps65217x_present);
int pmic_detect(void);

pmic_id pmic_chip_get(pmic_smps_id smps_id);
unsigned short pmic_is_twl6030(pmic_smps_id smps_id);
unsigned short pmic_is_twl6032(pmic_smps_id smps_id);
unsigned short pmic_is_twl6034(pmic_smps_id smps_id);
unsigned short pmic_is_twl6035(pmic_smps_id smps_id);
unsigned short pmic_is_tps62361(pmic_smps_id smps_id);
unsigned short pmic_is_tps659038(pmic_smps_id smps_id);
unsigned short pmic_is_tps65217x(pmic_smps_id smps_id);
unsigned short pmic_is_single_chip(void);
double pmic_chip_revision_get(pmic_smps_id smps_id);
double pmic_eprom_revision_get(pmic_smps_id smps_id);
const char *pmic_name_get(pmic_id id);

pmic_smps_id vdd_id2smps_id(unsigned short vdd_id);
unsigned short smps_id2vdd_id(pmic_smps_id smps_id);

const char *smps_name_get(pmic_smps_id smps_id);
long smps_step_get(pmic_smps_id smps_id);
long smps_offset_get(pmic_smps_id smps_id);
int smps_vsel_len_get(pmic_smps_id smps_id);
int smps_uvolt2vsel(pmic_smps_id smps_id, unsigned long uvolt);
long smps_vsel2uvolt(pmic_smps_id smps_id, unsigned char vsel);
double smps_vsel2volt(pmic_smps_id smps_id, unsigned char vsel);
long smps_voltage_round(pmic_smps_id smps_id, long uvolt);
int smps_vsel_get(pmic_smps_id smps_id);
double smps_voltage_get(pmic_smps_id smps_id);
int smps_voltage_set(pmic_smps_id smps_id, unsigned long uvolt);


#endif
