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
#include <stdio.h>
#include <stdlib.h>
#include <cpufreq.h>


/* #define CPUID7XX_DEBUG */
#ifdef CPUID_DRA7XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_dra7xx_silicon_max_speed_get
 * @BRIEF		return silicon max speed (depending on cpu type and
 *			silicon type)
 * @RETURNS		Silicon max speed (in MHz)
 *			0 in case of error
 * @DESCRIPTION		return silicon max speed (depending on cpu type and
 *			silicon type)
 *//*------------------------------------------------------------------------ */
unsigned int cpu_dra7xx_silicon_max_speed_get(void)
{
	unsigned int max_speed;

	switch (cpu_get()) {
	/*
	 * TBD: to use DIE ID to detect maximum speed capable. For the moment,
	 * we use cpufreq entries if any to detect max speed.
	 */
	case DRA_72X:
	case DRA_75X:
		switch (cpu_silicon_type_get()) {
		case STANDARD_PERF_SI:
			max_speed = 1000;
			break;
		case HIGH_PERF_SI:
			max_speed = 1500;
			break;
		default:
			max_speed = 0;
			break;
		}
		break;

	default:
		fprintf(stderr, "%s(): unknown chip!\n", __func__);
		max_speed = 0;
	}

	dprintf("%s(): max speed = %dMHz\n", __func__, max_speed);
	return max_speed;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_dra7xx_cores_count_get
 * @BRIEF		return the number of CPU cores available
 * @RETURNS		>0 number of CPU cores available
 *			0 in case of error (unknown architecture)
 * @DESCRIPTION		return the number of CPU cores available
 *//*------------------------------------------------------------------------ */
unsigned int cpu_dra7xx_cores_count_get(void)
{
	if (cpu_is_dra7xx()) {
		/* This may need to be detected using efuse in the future. */
		return 2;
	} else {
		fprintf(stderr, "%s(): unknown architecture!\n", __func__);
		return 0;
	}
}
