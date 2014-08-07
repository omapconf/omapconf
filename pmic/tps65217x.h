/*
 *
 * @Component			OMAPCONF
 * @Filename			tps65217x.h
 * @Description			AM335X TPS 65217X (SMPS Voltage Regulator)
 *				Library
 * @Author			Gilberto Rodriguez <gilrod@ti.com>
 * @Date			2014
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
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


#ifndef __TPS65217X_H__
#define __TPS65217X_H__


#define TPS65217X_VSEL_LEN	6

#define TPS65217X_I2C_BUS	0
#define TPS65217X_ID0_ADDR	0x24

#define TPS65217X_VOLT_MIN_UV	900000
#define TPS65217X_VSTEP_UV	25000


unsigned short int tps65217x_is_present(void);
int tps65217x_chip_get(void);
double tps65217x_chip_revision_get(void);
double tps65217x_eprom_revision_get(void);
long tps65217x_smps_offset_get(void);
long tps65217x_smps_step_get(void);
int tps65217x_vsel_len_get(void);

int tps65217x_vsel_get(unsigned int smps_id);
unsigned char tps65217x_uv_to_vsel(unsigned long uv);
unsigned long tps65217x_vsel_to_uv(unsigned char vsel);
int tps65217x_uvoltage_set(unsigned int vdd_id, unsigned long uv);


#endif
