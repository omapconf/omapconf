/*
 *
 * @Component			OMAPCONF
 * @Filename			twl603x.h
 * @Description			OMAP4 TWL603x Power Companion Chip Library
 * @Author			Patrick Titiano (p-titiano@ti.com)
 * @Date			2010
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
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


#ifndef __TWL603X_H__
#define __TWL603X_H__


#include <voltdm44xx.h>
#include <twl603x_lib.h>


#define TWL6030_I2C_BUS			0
#define TWL6030_I2C_ID1			0x48
#define TWL6030_I2C_ID2			0x49
#define TWL6030_I2C_ID3			0x4A


#define TWL603x_NAME_MAX_LEN		8


typedef enum {
	TWL6030,
	TWL6032,
	TWL6034,
	TWL6035,
	TWL603X_TYPE_MAX
} twl603x_type;


twl603x_type twl603x_type_get(void);
unsigned short twl603x_is_twl6030(void);
unsigned short twl603x_is_twl6032(void);
unsigned short twl603x_is_twl6034(void);
unsigned short twl603x_is_twl6035(void);

float twl603x_chip_revision_get(void);
float twl603x_eprom_revision_get(void);

unsigned char twl603x_uv_to_vsel(unsigned int vdd_id, unsigned long uv);

unsigned long twl603x_vsel_to_uv(unsigned int vdd_id, unsigned char vsel);
double twl603x_vsel_to_volt(unsigned int vdd_id, unsigned char vsel);

unsigned long twl603x_smps_offset_get(voltdm44xx_id vdd_id);
long twl603x_smps_step_get(void);
int twl603x_vsel_len_get(void);

int twl603x_vsel_get(unsigned int vdd_id);
unsigned long twl603x_uvoltage_get(unsigned int vdd_id);
double twl603x_voltage_get(unsigned int vdd_id);
int twl603x_uvoltage_set(unsigned int vdd_id, unsigned long uv);



/* DEPRECATED, DO NOT USE ANYMORE */
int twl603x_main(int argc, char *argv[]);


#endif
