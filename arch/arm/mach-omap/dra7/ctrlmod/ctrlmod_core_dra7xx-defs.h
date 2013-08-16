/*
 *
 * @Component			OMAPCONF
 * @Filename			ctrlmod_core_dra7xx-defs.h
 * @Description			Jacinto6 CONTROL MODULE Registers Definitions
 * @Author			José Peña <pena@ti.com>
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


#ifndef __CTRLMOD_CORE_DRA7XX_DEFS_H__
#define __CTRLMOD_CORE_DRA7XX_DEFS_H__


#include <reg.h>
#include <stdio.h>


#define DRA7XX_CTRL_CORE_DTEMP_MPU_0				0x4a0023c0
extern reg dra7xx_ctrl_core_dtemp_mpu_0;
#define DRA7XX_CTRL_CORE_DTEMP_MPU_1				0x4a0023c4
extern reg dra7xx_ctrl_core_dtemp_mpu_1;
#define DRA7XX_CTRL_CORE_DTEMP_MPU_2				0x4a0023c8
extern reg dra7xx_ctrl_core_dtemp_mpu_2;
#define DRA7XX_CTRL_CORE_DTEMP_MPU_3				0x4a0023cc
extern reg dra7xx_ctrl_core_dtemp_mpu_3;
#define DRA7XX_CTRL_CORE_DTEMP_MPU_4				0x4a0023d0
extern reg dra7xx_ctrl_core_dtemp_mpu_4;

#define DRA7XX_CTRL_CORE_DTEMP_GPU_0				0x4a0023d4
extern reg dra7xx_ctrl_core_dtemp_gpu_0;
#define DRA7XX_CTRL_CORE_DTEMP_GPU_1				0x4a0023d8
extern reg dra7xx_ctrl_core_dtemp_gpu_1;
#define DRA7XX_CTRL_CORE_DTEMP_GPU_2				0x4a0023dc
extern reg dra7xx_ctrl_core_dtemp_gpu_2;
#define DRA7XX_CTRL_CORE_DTEMP_GPU_3				0x4a0023e0
extern reg dra7xx_ctrl_core_dtemp_gpu_3;
#define DRA7XX_CTRL_CORE_DTEMP_GPU_4				0x4a0023e4
extern reg dra7xx_ctrl_core_dtemp_gpu_4;

#define DRA7XX_CTRL_CORE_DTEMP_CORE_0				0x4a0023e8
extern reg dra7xx_ctrl_core_dtemp_core_0;
#define DRA7XX_CTRL_CORE_DTEMP_CORE_1				0x4a0023ec
extern reg dra7xx_ctrl_core_dtemp_core_1;
#define DRA7XX_CTRL_CORE_DTEMP_CORE_2				0x4a0023f0
extern reg dra7xx_ctrl_core_dtemp_core_2;
#define DRA7XX_CTRL_CORE_DTEMP_CORE_3				0x4a0023f4
extern reg dra7xx_ctrl_core_dtemp_core_3;
#define DRA7XX_CTRL_CORE_DTEMP_CORE_4				0x4a0023f8
extern reg dra7xx_ctrl_core_dtemp_core_4;

#define DRA7XX_CTRL_CORE_DTEMP_IVA_0				0x4a0025b0
extern reg dra7xx_ctrl_core_dtemp_iva_0;
#define DRA7XX_CTRL_CORE_DTEMP_IVA_1				0x4a0025b4
extern reg dra7xx_ctrl_core_dtemp_iva_1;
#define DRA7XX_CTRL_CORE_DTEMP_IVA_2				0x4a0025b8
extern reg dra7xx_ctrl_core_dtemp_iva_2;
#define DRA7XX_CTRL_CORE_DTEMP_IVA_3				0x4a0025bc
extern reg dra7xx_ctrl_core_dtemp_iva_3;
#define DRA7XX_CTRL_CORE_DTEMP_IVA_4				0x4a0025c0
extern reg dra7xx_ctrl_core_dtemp_iva_4;

#define DRA7XX_CTRL_CORE_DTEMP_DSPEVE_0				0x4a00259c
extern reg dra7xx_ctrl_core_dtemp_dspeve_0;
#define DRA7XX_CTRL_CORE_DTEMP_DSPEVE_1				0x4a0025a0
extern reg dra7xx_ctrl_core_dtemp_dspeve_1;
#define DRA7XX_CTRL_CORE_DTEMP_DSPEVE_2				0x4a0025a4
extern reg dra7xx_ctrl_core_dtemp_dspeve_2;
#define DRA7XX_CTRL_CORE_DTEMP_DSPEVE_3				0x4a0025a8
extern reg dra7xx_ctrl_core_dtemp_dspeve_3;
#define DRA7XX_CTRL_CORE_DTEMP_DSPEVE_4				0x4a0025ac
extern reg dra7xx_ctrl_core_dtemp_dspeve_4;


#define DRA7XX_CTRL_MODULE_CORE_MOD_REGCOUNT			25
extern reg *dra7xx_ctrl_module_core_mod[DRA7XX_CTRL_MODULE_CORE_MOD_REGCOUNT + 1];

#endif
