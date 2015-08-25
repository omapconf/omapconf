/*
 *
 * @Component                   OMAPCONF
 * @Filename                    timestamp_32k.c
 * @Description                 32kHz based timestamps helper functions
 * @Author                      Frederic Turgis (f-turgis@ti.com)
 * @Date                        2012
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <common/cpuinfo.h>
#include <timr44xx.h>
#include <timr54xx.h>
#include <mem.h>


static volatile unsigned int *addr_32k = NULL;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mem_map_32k
 * @BRIEF		map given physical address
 * @RETURNS		32K virtual address
 * @DESCRIPTION		map given physical address
 *//*------------------------------------------------------------------------ */
volatile unsigned int *mem_map_32k(void)
{
	unsigned int reg_32k = 0;

	if (cpu_is_omap54xx() || cpu_is_dra7xx())
		reg_32k = OMAP5430_CR;
	else if (cpu_is_omap44xx())
		reg_32k = T32KSYNCNT_CR;

	return mem_map_address(reg_32k);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mem_unmap_32k
 * @BRIEF		unmap given physical address
 * @param[in]		addr: 32K virtual address to be unmapped
 * @DESCRIPTION		unmap given physical address
 *//*------------------------------------------------------------------------ */
void mem_unmap_32k(volatile unsigned int *addr)
{
	mem_unmap_address((unsigned int *) addr);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		timestamp_32k_main
 * @BRIEF		print delta time between 32K clock to clock_gettime(),
 *			32K clock to gettimeofday().
 * @RETURNS		1
 * @param[in]		argc: number of argument (should be 0 or 1 max)
 * @param[in]		argv: arguments (argv[0] = number of loops, default 10)
 * @DESCRIPTION		print delta time between 32K clock to clock_gettime(),
 *			32K clock to gettimeofday().
 *//*------------------------------------------------------------------------ */
int timestamp_32k_main(int argc, char **argv)
{
	struct timespec clock_get;
	struct timeval gtod;
	unsigned int counter_32k;
	unsigned int loop = 0;
	long long int value_32k;

	addr_32k = mem_map_32k();

	if (argc > 1)
		loop = atoi(argv[1]);
	if (loop == 0)
		loop = 10;

	for (; loop > 0; loop--) {
		clock_gettime(CLOCK_MONOTONIC, &clock_get);
		gettimeofday(&gtod, NULL);
		counter_32k = *addr_32k;
		value_32k = (long long int)((double)counter_32k / 32768 * 1000000);
		printf("32K to clock_gettime: %lld 32K to gettimeofday: %lld    32K: %u/%lld.%06lld clock_gettime: %u.%06u gtod: %u.%06u\n", \
			(long long int)(clock_get.tv_sec) * 1000000 + clock_get.tv_nsec / 1000 - value_32k, \
			(long long int)(gtod.tv_sec) * 1000000 + gtod.tv_usec - value_32k,
			counter_32k, value_32k / 1000000, (long long int)(value_32k - value_32k / 1000000 * 1000000), \
			(unsigned int) clock_get.tv_sec, (unsigned int)(clock_get.tv_nsec / 1000), (unsigned int)gtod.tv_sec, (unsigned int)gtod.tv_usec);
	}

	mem_unmap_32k(addr_32k);

	return 1;
}
