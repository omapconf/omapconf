/*
 *
 * @Component			OMAPCONF
 * @Filename			cpuinfo_dra7xx.h
 * @Description			DRA7xx CPU Info Functions
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

#include <cpuinfo_dra7xx.h>
#include <cpuinfo.h>
#include <lib.h>
#include <mem.h>
#include <stdio.h>
#include <stdlib.h>
#include <cpufreq.h>

/* #define CPUID7XX_DEBUG */
#ifdef CPUID_DRA7XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

/* ------------------------------------------------------------------------
 * @FUNCTION		cpu_dra7xx_silicon_max_speed_get
 * @BRIEF		return silicon max speed (depending on cpu type and
 *			silicon type)
 * @RETURNS		Silicon max speed (in MHz)
 *			0 in case of error
 * @DESCRIPTION		return silicon max speed (depending on cpu type and
 *			silicon type)
 *------------------------------------------------------------------------ */
unsigned int cpu_dra7xx_silicon_max_speed_get(void)
{
	unsigned int max_speed, efuse, speed_grade;
	int ret;

	speed_grade = 1000;

	ret = mem_read(STD_FUSE_DIE_ID_2, &efuse);
	if (ret)
		return speed_grade;

	speed_grade = (efuse & STD_FUSE_SPEED_GRADE_MASK) >>
	    STD_FUSE_SPEED_GRADE_SHIFT;
	switch (speed_grade) {
	case DRA76_EFUSE_HAS_ALL_MPU_OPP:
	case DRA76_EFUSE_HAS_PLUS_MPU_OPP:
		max_speed = 1800;
		break;
	case DRA7_EFUSE_HAS_ALL_MPU_OPP:
	case DRA7_EFUSE_HAS_HIGH_MPU_OPP:
		max_speed = 1500;
		break;
	case DRA7_EFUSE_HAS_OD_MPU_OPP:
		max_speed = 1100;
		break;
	default:
		max_speed = 1000;
		break;
	}

	dprintf("%s(): max speed = %dMHz\n", __func__, max_speed);
	return max_speed;
}
