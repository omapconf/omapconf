/*
 *
 * @Component			OMAPCONF
 * @Filename			tps659038.h
 * @Description			DRA7 TPS 659038 (SMPS Voltage Regulator) Library
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


#ifndef __TPS659038_H__
#define __TPS659038_H__


#define TPS659038_VSEL_LEN	7

#define TPS659038_I2C_BUS	0
#define TPS659038_ID0_ADDR	0x58
#define TPS659038_ID1_ADDR	0x59
#define TPS659038_ID2_ADDR	0x5A

#define TPS659038_PRODUCT_ID_LSB	0x51
#define TPS659038_PRODUCT_ID_MSB	0x52

#define TPS659038_VOLT_MIN_UV	500000
#define TPS659038_VSTEP_UV	10000
#define TPS659038_PFM_FLAG	0x80


unsigned short int tps659038_is_present(void);
double tps659038_chip_revision_get(void);
double tps659038_eprom_revision_get(void);
long tps659038_smps_offset_get(void);
long tps659038_smps_step_get(void);
int tps659038_vsel_len_get(void);

int tps659038_vsel_get(unsigned int smps_id);
unsigned char tps659038_uv_to_vsel(unsigned long uv);
unsigned long tps659038_vsel_to_uv(unsigned char vsel);
int tps659038_uvoltage_set(unsigned int vdd_id, unsigned long uv);


#endif
