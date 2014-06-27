/*
 *
 * @Component			OMAPCONF
 * @Filename			cpuinfo_am335x.c
 * @Description			AM335x CPU Info Functions
 * @Author			Gilberto Rodriguez (gilrod@ti.com)
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


#include <cpuinfo_am335x.h>
#include <cpuinfo.h>
#include <cpufreq.h>
#include <lib.h>
#include <mem.h>
#include <stdio.h>
#include <stdlib.h>


/* #define CPUID_AM335X_DEBUG */
#ifdef CPUID_AM335X_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

#define OPP_50_300MHZ_BIT				(0x1 << 4)
#define OPP_100_300MHZ_BIT				(0x1 << 5)
#define OPP_100_600MHZ_BIT				(0x1 << 6)
#define OPP_120_720MHZ_BIT				(0x1 << 7)
#define OPP_TURBO_800MHZ_BIT				(0x1 << 8)
#define OPP_NITRO_1GHZ_BIT				(0x1 << 9)


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_am335x_silicon_max_speed_get
 * @BRIEF		return silicon max speed (depending on cpu type and
 *			silicon type)
 * @RETURNS		Silicon max speed (in MHz)
 *			0 in case of error
 * @DESCRIPTION		return silicon max speed (depending on cpu type and
 *			silicon type)
 *//*------------------------------------------------------------------------ */
unsigned int cpu_am335x_silicon_max_speed_get(void)
{
	unsigned int max_speed;
	unsigned int efuse_sma;
	int ret;

	/*
	 * Bits 9-0 of EFUSE_SMA register are OPP disable bits
	 * Bits 9-4 have OPP disable bits for Rev ES2.X max CPU speeds
	 * Bits 3-0 have OPP disable bits for Rev ES1.0 max CPU speeds
	 * (Reads from EFUSE_SMA register not supported in SI rev 1.0)
	 * 1 represents OPP disabled, and 0 represents OPP enabled
	 */
	if (cpu_revision_get() != REV_ES1_0) {
		ret = mem_read(EFUSE_SMA_REG, &efuse_sma);
		if (ret)
			return 0;
		efuse_sma = ~efuse_sma;
		if (efuse_sma & OPP_NITRO_1GHZ_BIT)
			max_speed = 1000;
		else if (efuse_sma & OPP_TURBO_800MHZ_BIT)
			max_speed = 800;
		else if (efuse_sma & OPP_120_720MHZ_BIT)
			max_speed = 720;
		else if (efuse_sma & OPP_100_600MHZ_BIT)
			max_speed = 600;
		else if (efuse_sma & OPP_50_300MHZ_BIT || efuse_sma & OPP_100_300MHZ_BIT)
			max_speed = 300;
		else {
			fprintf(stderr, "%s(): unknown efuse value!\n", __func__);
			max_speed = 0;
		}
	} else {
		/*
		 * Read from EFUSE SMA register not supported in Rev ES1.0
		 * (Returns all 0's)
		 */
		if (!cpu_is_am335x()) {
			fprintf(stderr, "%s(): unknown chip!\n", __func__);
			max_speed = 0;
		} else {
			fprintf(stderr, "%s(): unable to determine max "
				"freq!\n", __func__);
			max_speed = 275; /* Lowest supported cpu speed */
		}
	}

	dprintf("%s(): max speed = %dMHz\n", __func__, max_speed);
	return max_speed;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_am335x_cores_count_get
 * @BRIEF		return the number of CPU cores available
 * @RETURNS		>0 number of CPU cores available
 *			0 in case of error (unknown architecture)
 * @DESCRIPTION		return the number of CPU cores available
 *//*------------------------------------------------------------------------ */
unsigned int cpu_am335x_cores_count_get(void)
{
	if (cpu_is_am335x()) {
		return 1;
	} else {
		fprintf(stderr, "%s(): unknown architecture!\n", __func__);
		return 0;
	}
}
