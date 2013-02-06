/*
 *
 * @Component			OMAPCONF
 * @Filename			trace.h
 * @Description			OMAP Common Trace Definitions and Functions
 * @Author			Patrick Titiano (p-titiano@ti.com)
 * @Author			Louis Lamia (loulamia@ti.com)
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


#ifndef __TRACE_H__
#define __TRACE_H__


#define TRACE_PERF_DEFAULT_CAPTURE_TIME		10 /* second */
#define TRACE_PERF_DEFAULT_DELAY_TIME		0 /* second */
#define TRACE_PERF_DEFAULT_SAMPLING_RATE	((double) 0.1) /* second */
#define TRACE_PERF_MIN_SAMPLING_RATE		((double) 0.1) /* second */
static const char trace_perf_default_cfgfile[32] = "./trace_perf_config.dat";


typedef enum {
	/* Generic */
	CPU0_LOAD = 0,
	CPU1_LOAD,
	TOTAL_CPU_LOAD,
	CPU1_ONLINE_TIME,
	/* OMAP[4-5] Specific */
	CPU_FREQ,
	GPU_FREQ,
	L3_FREQ,
	EMIF_BW,
	/* OMAP4 Specific */
	EMIF_LOAD,
	BANDGAP_TEMP,
	PCB_TEMP,
	HOTSPOT_MPU_TEMP,
	/* OMAP5 Specific */
	MPU_TEMP,
	GPU_TEMP,
	CORE_TEMP,
	CASE_TEMP,
	NUM_ITEMS
} traceables;


int trace_perf_setup(const char *filename);
int trace_perf_capture(const char *cfgfile, const char *prefix,
	double sampling_rate, unsigned int capture_time,
	unsigned int delay_time);


#endif
