/*
 *
 * @Component			OMAPCONF
 * @Filename			cpuinfo54xx.h
 * @Description			OMAP5 CPU Info Functions
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


#include <cpuinfo54xx.h>
#include <cpuinfo.h>
#include <lib.h>
#include <stdio.h>
#include <stdlib.h>
#include <cpufreq.h>


/* #define CPUID54XX_DEBUG */
#ifdef CPUID54XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu54xx_silicon_max_speed_get
 * @BRIEF		return silicon max speed (depending on cpu type and
 *			silicon type)
 * @RETURNS		Silicon max speed (in MHz)
 *			0 in case of error
 * @DESCRIPTION		return silicon max speed (depending on cpu type and
 *			silicon type)
 *//*------------------------------------------------------------------------ */
unsigned int cpu54xx_silicon_max_speed_get(void)
{
	unsigned int max_speed;

	switch (cpu_get()) {
	case OMAP_5430:
	case OMAP_5432:
		if (cpufreq_opp_nbr_get() == 4) {
			switch (cpu_revision_get()) {
			case REV_ES1_0:
				max_speed = 1200;
				break;
			case REV_ES2_0:
				max_speed = 1700;
				break;
			default:
				fprintf(stderr,
					"omapconf: %s(): warning: unknown revision!\n",
					__func__);
				max_speed = 0;
				break;
			}
		} else {
			switch (cpu_revision_get()) {
			case REV_ES1_0:
				max_speed = 1100;
				break;
			case REV_ES2_0:
				max_speed = 1500;
				break;
			default:
				fprintf(stderr,
					"omapconf: %s(): warning: unknown revision!\n",
					__func__);
				max_speed = 0;
				break;
			}
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
 * @FUNCTION		cpu54xx_cores_count_get
 * @BRIEF		return the number of CPU cores available
 * @RETURNS		>0 number of CPU cores available
 *			0 in case of error (unknown architecture)
 * @DESCRIPTION		return the number of CPU cores available
 *//*------------------------------------------------------------------------ */
unsigned int cpu54xx_cores_count_get(void)
{
	if (cpu_is_omap54xx()) {
		return 2;
	} else {
		fprintf(stderr, "%s(): unknown architecture!\n", __func__);
		return 0;
	}
}
