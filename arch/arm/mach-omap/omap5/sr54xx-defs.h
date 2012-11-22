/*
 *
 * @Component			OMAPCONF
 * @Filename			sr54xx-defs.h
 * @Description			OMAP5 SMARTREFLEX Registers Definitions &
 *				Functions
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


#ifndef __SR54XX_DEFS_H__
#define __SR54XX_DEFS_H__

#include <reg.h>
#include <stdio.h>

#define OMAP5430_SMARTREFLEX_MPU_SRCONFIG			0x4a0d9000
extern reg omap5430_smartreflex_mpu_srconfig;
#define OMAP5430_SMARTREFLEX_MPU_SRSTATUS			0x4a0d9004
extern reg omap5430_smartreflex_mpu_srstatus;
#define OMAP5430_SMARTREFLEX_MPU_SENVAL				0x4a0d9008
extern reg omap5430_smartreflex_mpu_senval;
#define OMAP5430_SMARTREFLEX_MPU_SENMIN				0x4a0d900c
extern reg omap5430_smartreflex_mpu_senmin;
#define OMAP5430_SMARTREFLEX_MPU_SENMAX				0x4a0d9010
extern reg omap5430_smartreflex_mpu_senmax;
#define OMAP5430_SMARTREFLEX_MPU_SENAVG				0x4a0d9014
extern reg omap5430_smartreflex_mpu_senavg;
#define OMAP5430_SMARTREFLEX_MPU_AVGWEIGHT_REG			0x4a0d9018
extern reg omap5430_smartreflex_mpu_avgweight_reg;
#define OMAP5430_SMARTREFLEX_MPU_NVALUERECIPROCAL		0x4a0d901c
extern reg omap5430_smartreflex_mpu_nvaluereciprocal;
#define OMAP5430_SMARTREFLEX_MPU_IRQSTATUS_RAW			0x4a0d9024
extern reg omap5430_smartreflex_mpu_irqstatus_raw;
#define OMAP5430_SMARTREFLEX_MPU_IRQSTATUS			0x4a0d9028
extern reg omap5430_smartreflex_mpu_irqstatus;
#define OMAP5430_SMARTREFLEX_MPU_IRQENABLE_SET			0x4a0d902c
extern reg omap5430_smartreflex_mpu_irqenable_set;
#define OMAP5430_SMARTREFLEX_MPU_IRQENABLE_CLR			0x4a0d9030
extern reg omap5430_smartreflex_mpu_irqenable_clr;
#define OMAP5430_SMARTREFLEX_MPU_SENERROR_REG			0x4a0d9034
extern reg omap5430_smartreflex_mpu_senerror_reg;
#define OMAP5430_SMARTREFLEX_MPU_ERRCONFIG			0x4a0d9038
extern reg omap5430_smartreflex_mpu_errconfig;
#define OMAP5430_SMARTREFLEX_MPU_LVTSENVAL			0x4a0d903c
extern reg omap5430_smartreflex_mpu_lvtsenval;
#define OMAP5430_SMARTREFLEX_MPU_LVTSENMIN			0x4a0d9040
extern reg omap5430_smartreflex_mpu_lvtsenmin;
#define OMAP5430_SMARTREFLEX_MPU_LVTSENMAX			0x4a0d9044
extern reg omap5430_smartreflex_mpu_lvtsenmax;
#define OMAP5430_SMARTREFLEX_MPU_LVTSENAVG			0x4a0d9048
extern reg omap5430_smartreflex_mpu_lvtsenavg;
#define OMAP5430_SMARTREFLEX_MPU_LVTNVALUERECIPROCAL		0x4a0d904c
extern reg omap5430_smartreflex_mpu_lvtnvaluereciprocal;
#define OMAP5430_SMARTREFLEX_MPU_MOD_REGCOUNT			19
extern reg *omap5430_smartreflex_mpu_mod[OMAP5430_SMARTREFLEX_MPU_MOD_REGCOUNT + 1];

#define OMAP5430_SMARTREFLEX_MM_SRCONFIG			0x4a0db000
extern reg omap5430_smartreflex_mm_srconfig;
#define OMAP5430_SMARTREFLEX_MM_SRSTATUS			0x4a0db004
extern reg omap5430_smartreflex_mm_srstatus;
#define OMAP5430_SMARTREFLEX_MM_SENVAL				0x4a0db008
extern reg omap5430_smartreflex_mm_senval;
#define OMAP5430_SMARTREFLEX_MM_SENMIN				0x4a0db00c
extern reg omap5430_smartreflex_mm_senmin;
#define OMAP5430_SMARTREFLEX_MM_SENMAX				0x4a0db010
extern reg omap5430_smartreflex_mm_senmax;
#define OMAP5430_SMARTREFLEX_MM_SENAVG				0x4a0db014
extern reg omap5430_smartreflex_mm_senavg;
#define OMAP5430_SMARTREFLEX_MM_AVGWEIGHT_REG			0x4a0db018
extern reg omap5430_smartreflex_mm_avgweight_reg;
#define OMAP5430_SMARTREFLEX_MM_NVALUERECIPROCAL		0x4a0db01c
extern reg omap5430_smartreflex_mm_nvaluereciprocal;
#define OMAP5430_SMARTREFLEX_MM_IRQSTATUS_RAW			0x4a0db024
extern reg omap5430_smartreflex_mm_irqstatus_raw;
#define OMAP5430_SMARTREFLEX_MM_IRQSTATUS			0x4a0db028
extern reg omap5430_smartreflex_mm_irqstatus;
#define OMAP5430_SMARTREFLEX_MM_IRQENABLE_SET			0x4a0db02c
extern reg omap5430_smartreflex_mm_irqenable_set;
#define OMAP5430_SMARTREFLEX_MM_IRQENABLE_CLR			0x4a0db030
extern reg omap5430_smartreflex_mm_irqenable_clr;
#define OMAP5430_SMARTREFLEX_MM_SENERROR_REG			0x4a0db034
extern reg omap5430_smartreflex_mm_senerror_reg;
#define OMAP5430_SMARTREFLEX_MM_ERRCONFIG			0x4a0db038
extern reg omap5430_smartreflex_mm_errconfig;
#define OMAP5430_SMARTREFLEX_MM_LVTSENVAL			0x4a0db03c
extern reg omap5430_smartreflex_mm_lvtsenval;
#define OMAP5430_SMARTREFLEX_MM_LVTSENMIN			0x4a0db040
extern reg omap5430_smartreflex_mm_lvtsenmin;
#define OMAP5430_SMARTREFLEX_MM_LVTSENMAX			0x4a0db044
extern reg omap5430_smartreflex_mm_lvtsenmax;
#define OMAP5430_SMARTREFLEX_MM_LVTSENAVG			0x4a0db048
extern reg omap5430_smartreflex_mm_lvtsenavg;
#define OMAP5430_SMARTREFLEX_MM_LVTNVALUERECIPROCAL		0x4a0db04c
extern reg omap5430_smartreflex_mm_lvtnvaluereciprocal;
#define OMAP5430_SMARTREFLEX_MM_MOD_REGCOUNT			19
extern reg *omap5430_smartreflex_mm_mod[OMAP5430_SMARTREFLEX_MM_MOD_REGCOUNT + 1];

#define OMAP5430_SMARTREFLEX_CORE_SRCONFIG			0x4a0dd000
extern reg omap5430_smartreflex_core_srconfig;
#define OMAP5430_SMARTREFLEX_CORE_SRSTATUS			0x4a0dd004
extern reg omap5430_smartreflex_core_srstatus;
#define OMAP5430_SMARTREFLEX_CORE_SENVAL			0x4a0dd008
extern reg omap5430_smartreflex_core_senval;
#define OMAP5430_SMARTREFLEX_CORE_SENMIN			0x4a0dd00c
extern reg omap5430_smartreflex_core_senmin;
#define OMAP5430_SMARTREFLEX_CORE_SENMAX			0x4a0dd010
extern reg omap5430_smartreflex_core_senmax;
#define OMAP5430_SMARTREFLEX_CORE_SENAVG			0x4a0dd014
extern reg omap5430_smartreflex_core_senavg;
#define OMAP5430_SMARTREFLEX_CORE_AVGWEIGHT_REG			0x4a0dd018
extern reg omap5430_smartreflex_core_avgweight_reg;
#define OMAP5430_SMARTREFLEX_CORE_NVALUERECIPROCAL		0x4a0dd01c
extern reg omap5430_smartreflex_core_nvaluereciprocal;
#define OMAP5430_SMARTREFLEX_CORE_IRQSTATUS_RAW			0x4a0dd024
extern reg omap5430_smartreflex_core_irqstatus_raw;
#define OMAP5430_SMARTREFLEX_CORE_IRQSTATUS			0x4a0dd028
extern reg omap5430_smartreflex_core_irqstatus;
#define OMAP5430_SMARTREFLEX_CORE_IRQENABLE_SET			0x4a0dd02c
extern reg omap5430_smartreflex_core_irqenable_set;
#define OMAP5430_SMARTREFLEX_CORE_IRQENABLE_CLR			0x4a0dd030
extern reg omap5430_smartreflex_core_irqenable_clr;
#define OMAP5430_SMARTREFLEX_CORE_SENERROR_REG			0x4a0dd034
extern reg omap5430_smartreflex_core_senerror_reg;
#define OMAP5430_SMARTREFLEX_CORE_ERRCONFIG			0x4a0dd038
extern reg omap5430_smartreflex_core_errconfig;
#define OMAP5430_SMARTREFLEX_CORE_LVTSENVAL			0x4a0dd03c
extern reg omap5430_smartreflex_core_lvtsenval;
#define OMAP5430_SMARTREFLEX_CORE_LVTSENMIN			0x4a0dd040
extern reg omap5430_smartreflex_core_lvtsenmin;
#define OMAP5430_SMARTREFLEX_CORE_LVTSENMAX			0x4a0dd044
extern reg omap5430_smartreflex_core_lvtsenmax;
#define OMAP5430_SMARTREFLEX_CORE_LVTSENAVG			0x4a0dd048
extern reg omap5430_smartreflex_core_lvtsenavg;
#define OMAP5430_SMARTREFLEX_CORE_LVTNVALUERECIPROCAL		0x4a0dd04c
extern reg omap5430_smartreflex_core_lvtnvaluereciprocal;
#define OMAP5430_SMARTREFLEX_CORE_MOD_REGCOUNT			19
extern reg *omap5430_smartreflex_core_mod[OMAP5430_SMARTREFLEX_CORE_MOD_REGCOUNT + 1];

typedef enum {
	SR54XX_SMARTREFLEX_MPU,
	SR54XX_SMARTREFLEX_MM,
	SR54XX_SMARTREFLEX_CORE,
	SR54XX_MODS_COUNT = 3
} sr54xx_mod_id;

extern reg **sr54xx_mods[SR54XX_MODS_COUNT + 1];

extern const char *sr54xx_mods_name[SR54XX_MODS_COUNT];


#endif
