/*
 * @Component			OMAPCONF
 * @Filename			cpuinfo_am437x.c
 * @Description			AM437x CPU Info Functions
 * @Author			Dave Gerlach (d-gerlach@ti.com)
 * @Date			2015
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
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


#include <cpuinfo_am437x.h>
#include <cpuinfo.h>
#include <cpufreq.h>
#include <lib.h>
#include <mem.h>
#include <stdio.h>
#include <stdlib.h>


#ifdef CPUID_AM437X_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

#define OPP_50_300MHZ_BIT				(0x1 << 0)
#define OPP_100_600MHZ_BIT				(0x1 << 2)
#define OPP_120_720MHZ_BIT				(0x1 << 3)
#define OPP_TURBO_800MHZ_BIT				(0x1 << 4)
#define OPP_NITRO_1GHZ_BIT				(0x1 << 5)

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_am437x_silicon_max_speed_get
 * @BRIEF		return silicon max speed (depending on cpu type and
 *			silicon type)
 * @RETURNS		Silicon max speed (in MHz)
 *			0 in case of error
 * @DESCRIPTION		return silicon max speed (depending on cpu type and
 *			silicon type)
 *//*------------------------------------------------------------------------ */
unsigned int cpu_am437x_silicon_max_speed_get(void)
{
	unsigned int max_speed;
	unsigned int dev_attr;
	int ret;

	if (!cpu_is_am437x()) {
		fprintf(stderr, "%s(): unknown chip!\n", __func__);
		max_speed = 0;
	}

	/*
	 * Bits 5-0 of DEV_ATTRIBUTE register are OPP disable bits
	 * 1 represents OPP disabled, and 0 represents OPP enabled
	 */

	ret = mem_read(DEV_ATTRIBUTE_REG, &dev_attr);
	if (ret)
		return 0;

	dev_attr = ~dev_attr;
	if (dev_attr & OPP_NITRO_1GHZ_BIT)
		max_speed = 1000;
	else if (dev_attr & OPP_TURBO_800MHZ_BIT)
		max_speed = 800;
	else if (dev_attr & OPP_120_720MHZ_BIT)
		max_speed = 720;
	else if (dev_attr & OPP_100_600MHZ_BIT)
		max_speed = 600;
	else if (dev_attr & OPP_50_300MHZ_BIT)
		max_speed = 300;
	else {
		fprintf(stderr, "%s(): unknown efuse value!\n", __func__);
		max_speed = 300; /* Lowest supported cpu speed */
	}

	dprintf("%s(): max speed = %dMHz\n", __func__, max_speed);
	return max_speed;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_am437x_cores_count_get
 * @BRIEF		return the number of CPU cores available
 * @RETURNS		>0 number of CPU cores available
 *			0 in case of error (unknown architecture)
 * @DESCRIPTION		return the number of CPU cores available
 *//*------------------------------------------------------------------------ */
unsigned int cpu_am437x_cores_count_get(void)
{
	if (cpu_is_am437x()) {
		return 1;
	} else {
		fprintf(stderr, "%s(): unknown architecture!\n", __func__);
		return 0;
	}
}
