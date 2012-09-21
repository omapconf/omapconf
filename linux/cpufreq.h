/*
 *
 * @Component			OMAPCONF
 * @Filename			cpufreq.h
 * @Description			Linux CPUFreq SYSFS Stats APIs
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


#ifndef __CPUFREQ_H__
#define __CPUFREQ_H__


#include <stdint.h>


#define CPUFREQ_ERR_ARG			-1 /* incorrect argument(s) */
#define CPUFREQ_ERR_INTERNAL		-3 /* internal error */
#define CPUFREQ_ERR_UNEXPECTED		-7 /* something unexpected occurred */
#define CPUFREQ_ERR_NOT_AVAILABLE	-8 /* does not exist / not available */

#define CPUFREQ_GOV_MAX_NAME_LENGTH	24

uint64_t cpufreq_time_in_state_get(unsigned int opp);
uint64_t cpufreq_total_transitions_get(void);
char *cpufreq_scaling_governor_get(char name[CPUFREQ_GOV_MAX_NAME_LENGTH]);
int cpufreq_scaling_governor_set(char new_gov[CPUFREQ_GOV_MAX_NAME_LENGTH],
	char prev_gov[CPUFREQ_GOV_MAX_NAME_LENGTH]);
unsigned int cpufreq_cur_freq_get(void);
unsigned int cpufreq_opp_nbr_get(void);
int cpufreq_set(unsigned int freq_mpu);


#endif
