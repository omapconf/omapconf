/*
 *
 * @Component			OMAPCONF
 * @Filename			sr54xx-defs.c
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


#include <sr54xx-defs.h>
#include <lib.h>
#include <autoadjust_table.h>


reg omap5430_smartreflex_mpu_srconfig = {
	"SRCONFIG",
	OMAP5430_SMARTREFLEX_MPU_SRCONFIG,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mpu_srstatus = {
	"SRSTATUS",
	OMAP5430_SMARTREFLEX_MPU_SRSTATUS,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mpu_senval = {
	"SENVAL",
	OMAP5430_SMARTREFLEX_MPU_SENVAL,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mpu_senmin = {
	"SENMIN",
	OMAP5430_SMARTREFLEX_MPU_SENMIN,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mpu_senmax = {
	"SENMAX",
	OMAP5430_SMARTREFLEX_MPU_SENMAX,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mpu_senavg = {
	"SENAVG",
	OMAP5430_SMARTREFLEX_MPU_SENAVG,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mpu_avgweight_reg = {
	"AVGWEIGHT_REG",
	OMAP5430_SMARTREFLEX_MPU_AVGWEIGHT_REG,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mpu_nvaluereciprocal = {
	"NVALUERECIPROCAL",
	OMAP5430_SMARTREFLEX_MPU_NVALUERECIPROCAL,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mpu_irqstatus_raw = {
	"IRQSTATUS_RAW",
	OMAP5430_SMARTREFLEX_MPU_IRQSTATUS_RAW,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mpu_irqstatus = {
	"IRQSTATUS",
	OMAP5430_SMARTREFLEX_MPU_IRQSTATUS,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mpu_irqenable_set = {
	"IRQENABLE_SET",
	OMAP5430_SMARTREFLEX_MPU_IRQENABLE_SET,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mpu_irqenable_clr = {
	"IRQENABLE_CLR",
	OMAP5430_SMARTREFLEX_MPU_IRQENABLE_CLR,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mpu_senerror_reg = {
	"SENERROR_REG",
	OMAP5430_SMARTREFLEX_MPU_SENERROR_REG,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mpu_errconfig = {
	"ERRCONFIG",
	OMAP5430_SMARTREFLEX_MPU_ERRCONFIG,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mpu_lvtsenval = {
	"LVTSENVAL",
	OMAP5430_SMARTREFLEX_MPU_LVTSENVAL,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mpu_lvtsenmin = {
	"LVTSENMIN",
	OMAP5430_SMARTREFLEX_MPU_LVTSENMIN,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mpu_lvtsenmax = {
	"LVTSENMAX",
	OMAP5430_SMARTREFLEX_MPU_LVTSENMAX,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mpu_lvtsenavg = {
	"LVTSENAVG",
	OMAP5430_SMARTREFLEX_MPU_LVTSENAVG,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mpu_lvtnvaluereciprocal = {
	"LVTNVALUERECIPROCAL",
	OMAP5430_SMARTREFLEX_MPU_LVTNVALUERECIPROCAL,
	0xDEADBEEF,
	0};

reg *omap5430_smartreflex_mpu_mod[OMAP5430_SMARTREFLEX_MPU_MOD_REGCOUNT + 1] = {
	&omap5430_smartreflex_mpu_srconfig,
	&omap5430_smartreflex_mpu_srstatus,
	&omap5430_smartreflex_mpu_senval,
	&omap5430_smartreflex_mpu_senmin,
	&omap5430_smartreflex_mpu_senmax,
	&omap5430_smartreflex_mpu_senavg,
	&omap5430_smartreflex_mpu_avgweight_reg,
	&omap5430_smartreflex_mpu_nvaluereciprocal,
	&omap5430_smartreflex_mpu_irqstatus_raw,
	&omap5430_smartreflex_mpu_irqstatus,
	&omap5430_smartreflex_mpu_irqenable_set,
	&omap5430_smartreflex_mpu_irqenable_clr,
	&omap5430_smartreflex_mpu_senerror_reg,
	&omap5430_smartreflex_mpu_errconfig,
	&omap5430_smartreflex_mpu_lvtsenval,
	&omap5430_smartreflex_mpu_lvtsenmin,
	&omap5430_smartreflex_mpu_lvtsenmax,
	&omap5430_smartreflex_mpu_lvtsenavg,
	&omap5430_smartreflex_mpu_lvtnvaluereciprocal,
	NULL};

reg omap5430_smartreflex_mm_srconfig = {
	"SRCONFIG",
	OMAP5430_SMARTREFLEX_MM_SRCONFIG,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mm_srstatus = {
	"SRSTATUS",
	OMAP5430_SMARTREFLEX_MM_SRSTATUS,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mm_senval = {
	"SENVAL",
	OMAP5430_SMARTREFLEX_MM_SENVAL,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mm_senmin = {
	"SENMIN",
	OMAP5430_SMARTREFLEX_MM_SENMIN,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mm_senmax = {
	"SENMAX",
	OMAP5430_SMARTREFLEX_MM_SENMAX,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mm_senavg = {
	"SENAVG",
	OMAP5430_SMARTREFLEX_MM_SENAVG,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mm_avgweight_reg = {
	"AVGWEIGHT_REG",
	OMAP5430_SMARTREFLEX_MM_AVGWEIGHT_REG,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mm_nvaluereciprocal = {
	"NVALUERECIPROCAL",
	OMAP5430_SMARTREFLEX_MM_NVALUERECIPROCAL,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mm_irqstatus_raw = {
	"IRQSTATUS_RAW",
	OMAP5430_SMARTREFLEX_MM_IRQSTATUS_RAW,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mm_irqstatus = {
	"IRQSTATUS",
	OMAP5430_SMARTREFLEX_MM_IRQSTATUS,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mm_irqenable_set = {
	"IRQENABLE_SET",
	OMAP5430_SMARTREFLEX_MM_IRQENABLE_SET,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mm_irqenable_clr = {
	"IRQENABLE_CLR",
	OMAP5430_SMARTREFLEX_MM_IRQENABLE_CLR,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mm_senerror_reg = {
	"SENERROR_REG",
	OMAP5430_SMARTREFLEX_MM_SENERROR_REG,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mm_errconfig = {
	"ERRCONFIG",
	OMAP5430_SMARTREFLEX_MM_ERRCONFIG,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mm_lvtsenval = {
	"LVTSENVAL",
	OMAP5430_SMARTREFLEX_MM_LVTSENVAL,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mm_lvtsenmin = {
	"LVTSENMIN",
	OMAP5430_SMARTREFLEX_MM_LVTSENMIN,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mm_lvtsenmax = {
	"LVTSENMAX",
	OMAP5430_SMARTREFLEX_MM_LVTSENMAX,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mm_lvtsenavg = {
	"LVTSENAVG",
	OMAP5430_SMARTREFLEX_MM_LVTSENAVG,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_mm_lvtnvaluereciprocal = {
	"LVTNVALUERECIPROCAL",
	OMAP5430_SMARTREFLEX_MM_LVTNVALUERECIPROCAL,
	0xDEADBEEF,
	0};

reg *omap5430_smartreflex_mm_mod[OMAP5430_SMARTREFLEX_MM_MOD_REGCOUNT + 1] = {
	&omap5430_smartreflex_mm_srconfig,
	&omap5430_smartreflex_mm_srstatus,
	&omap5430_smartreflex_mm_senval,
	&omap5430_smartreflex_mm_senmin,
	&omap5430_smartreflex_mm_senmax,
	&omap5430_smartreflex_mm_senavg,
	&omap5430_smartreflex_mm_avgweight_reg,
	&omap5430_smartreflex_mm_nvaluereciprocal,
	&omap5430_smartreflex_mm_irqstatus_raw,
	&omap5430_smartreflex_mm_irqstatus,
	&omap5430_smartreflex_mm_irqenable_set,
	&omap5430_smartreflex_mm_irqenable_clr,
	&omap5430_smartreflex_mm_senerror_reg,
	&omap5430_smartreflex_mm_errconfig,
	&omap5430_smartreflex_mm_lvtsenval,
	&omap5430_smartreflex_mm_lvtsenmin,
	&omap5430_smartreflex_mm_lvtsenmax,
	&omap5430_smartreflex_mm_lvtsenavg,
	&omap5430_smartreflex_mm_lvtnvaluereciprocal,
	NULL};

reg omap5430_smartreflex_core_srconfig = {
	"SRCONFIG",
	OMAP5430_SMARTREFLEX_CORE_SRCONFIG,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_core_srstatus = {
	"SRSTATUS",
	OMAP5430_SMARTREFLEX_CORE_SRSTATUS,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_core_senval = {
	"SENVAL",
	OMAP5430_SMARTREFLEX_CORE_SENVAL,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_core_senmin = {
	"SENMIN",
	OMAP5430_SMARTREFLEX_CORE_SENMIN,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_core_senmax = {
	"SENMAX",
	OMAP5430_SMARTREFLEX_CORE_SENMAX,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_core_senavg = {
	"SENAVG",
	OMAP5430_SMARTREFLEX_CORE_SENAVG,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_core_avgweight_reg = {
	"AVGWEIGHT_REG",
	OMAP5430_SMARTREFLEX_CORE_AVGWEIGHT_REG,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_core_nvaluereciprocal = {
	"NVALUERECIPROCAL",
	OMAP5430_SMARTREFLEX_CORE_NVALUERECIPROCAL,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_core_irqstatus_raw = {
	"IRQSTATUS_RAW",
	OMAP5430_SMARTREFLEX_CORE_IRQSTATUS_RAW,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_core_irqstatus = {
	"IRQSTATUS",
	OMAP5430_SMARTREFLEX_CORE_IRQSTATUS,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_core_irqenable_set = {
	"IRQENABLE_SET",
	OMAP5430_SMARTREFLEX_CORE_IRQENABLE_SET,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_core_irqenable_clr = {
	"IRQENABLE_CLR",
	OMAP5430_SMARTREFLEX_CORE_IRQENABLE_CLR,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_core_senerror_reg = {
	"SENERROR_REG",
	OMAP5430_SMARTREFLEX_CORE_SENERROR_REG,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_core_errconfig = {
	"ERRCONFIG",
	OMAP5430_SMARTREFLEX_CORE_ERRCONFIG,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_core_lvtsenval = {
	"LVTSENVAL",
	OMAP5430_SMARTREFLEX_CORE_LVTSENVAL,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_core_lvtsenmin = {
	"LVTSENMIN",
	OMAP5430_SMARTREFLEX_CORE_LVTSENMIN,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_core_lvtsenmax = {
	"LVTSENMAX",
	OMAP5430_SMARTREFLEX_CORE_LVTSENMAX,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_core_lvtsenavg = {
	"LVTSENAVG",
	OMAP5430_SMARTREFLEX_CORE_LVTSENAVG,
	0xDEADBEEF,
	0};

reg omap5430_smartreflex_core_lvtnvaluereciprocal = {
	"LVTNVALUERECIPROCAL",
	OMAP5430_SMARTREFLEX_CORE_LVTNVALUERECIPROCAL,
	0xDEADBEEF,
	0};

reg *omap5430_smartreflex_core_mod[OMAP5430_SMARTREFLEX_CORE_MOD_REGCOUNT + 1] = {
	&omap5430_smartreflex_core_srconfig,
	&omap5430_smartreflex_core_srstatus,
	&omap5430_smartreflex_core_senval,
	&omap5430_smartreflex_core_senmin,
	&omap5430_smartreflex_core_senmax,
	&omap5430_smartreflex_core_senavg,
	&omap5430_smartreflex_core_avgweight_reg,
	&omap5430_smartreflex_core_nvaluereciprocal,
	&omap5430_smartreflex_core_irqstatus_raw,
	&omap5430_smartreflex_core_irqstatus,
	&omap5430_smartreflex_core_irqenable_set,
	&omap5430_smartreflex_core_irqenable_clr,
	&omap5430_smartreflex_core_senerror_reg,
	&omap5430_smartreflex_core_errconfig,
	&omap5430_smartreflex_core_lvtsenval,
	&omap5430_smartreflex_core_lvtsenmin,
	&omap5430_smartreflex_core_lvtsenmax,
	&omap5430_smartreflex_core_lvtsenavg,
	&omap5430_smartreflex_core_lvtnvaluereciprocal,
	NULL};

reg **sr54xx_mods[SR54XX_MODS_COUNT + 1] = {
	(reg **) &omap5430_smartreflex_mpu_mod,
	(reg **) &omap5430_smartreflex_mm_mod,
	(reg **) &omap5430_smartreflex_core_mod,
	NULL};


const char *sr54xx_mods_name[SR54XX_MODS_COUNT] = {
	"SR MPU",
	"SR MM",
	"SR CORE"};
