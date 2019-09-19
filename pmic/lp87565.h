/*
 *
 * @Component			OMAPCONF
 * @Filename			lp87565 .h
 * @Description			J6Plus LP 87565 (SMPS Voltage Regulator) Library
 * @Author			Richard Woodruff (r-woodruff2@ti.com)
 * @Date			2019
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2019 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef __LP87565_H__
#define __LP87565_H__

#define LP87565_VSEL_LEN	8

#define LP87565_I2C_BUS	0
#define LP87565_ID0_ADDR	0x60	/* LP-MPU & GPU */
#define LP87565_PRODUCT_ID_LSB	0
#define LP87565_VDCDC1_MIN	730000	/* start of 5mV step range is 730mV */
#define LP87565_VDCDC1_STEP	5000	/* 5mV opeartion range .7 to 1.4v */
#define LP87565_VDCDC1_ENC_OFF 0x17	/* encode offset to VSEL base */

#define PQ2_ID1_ADDR    0x61	/* PQ2-MPU */
#define PQ2_ID0_ADDR    0x62	/* PQ2-GPU */
#define PQ2_VDCDC1_MIN	530000	/* start at 530mV */
#define PQ2_VDCDC1_STEP	6250	/* 6.25mV opeartion range .7 to 1.4v */
#define PQ2_VDCDC1_ENC_OFF 0x0

unsigned short int lp87565_is_present(void);
double lp87565_chip_revision_get(void);
double lp87565_eprom_revision_get(void);
long lp87565_smps_offset_get(void);
long lp87565_smps_step_get(void);
int lp87565_vsel_len_get(void);

unsigned char lp87565_uv_to_vsel(unsigned long uv);
unsigned long lp87565_vsel_to_uv(unsigned char vsel);
int lp87565_uvoltage_set(unsigned int vdd_id, unsigned long uv);
int lp87565_vsel_get(unsigned int smps_id);

#endif
