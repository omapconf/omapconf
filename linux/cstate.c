/*
 *
 * @Component			OMAPCONF
 * @Filename			cstate.c
 * @Description			Linux C-State APIs
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


#include <lib.h>
#include <cstate.h>
#include <stdio.h>


/* #define CSTATE_DEBUG */
#ifdef CSTATE_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static char cstate_usagefile[50] =
		"/sys/devices/system/cpu/cpu0/cpuidle/state*/usage";
static char cstate_timefile[50] =
		"/sys/devices/system/cpu/cpu0/cpuidle/state*/time";
static char cstate_namefile[50] =
		"/sys/devices/system/cpu/cpu0/cpuidle/state*/name";
int cstates_nbr = -1;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cstate_get_number
 * @BRIEF		retrieve and return the number of available C-State(s)
 * @RETURNS		0 if no C-State available
 *			>0 the number of available C-State(s)
 * @DESCRIPTION		retrieve and return the number of available C-State(s)
 *//*------------------------------------------------------------------------ */
unsigned int cstate_get_number(void)
{
	unsigned int i;
	FILE *fp;

	if (cstates_nbr == -1) {
		for (i = 0; i < MAX_CSTATE; i++) {
			cstate_usagefile[42] = int2char_table[i];
			dprintf("%s(): opening %s\n",
				__func__, cstate_usagefile);
			fp = fopen(cstate_usagefile, "r");
			if (fp == NULL) {
				dprintf("%s(): %s not found\n",
					__func__, cstate_usagefile);
				if (i == 0) {
					/* CPUIdle is not enabled? */
					dprintf("%s(): cannot open C-state "
						"files. CPUIdle enabled?\n\n",
						__func__);
					cstates_nbr = 0;
				} else {
					cstates_nbr = i;
				}
				break;
			} else {
				fclose(fp);
			}
		}
	}

	dprintf("%s(): cstates_nbr = %d\n", __func__, cstates_nbr);
	return (unsigned int) cstates_nbr;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cstate_get_usage
 * @BRIEF		return the number of time(s) a C-State was entered
 * @RETURNS		the number of time(s) a C-State was entered
 *			0 in case of error
 * @param[in]		n: C-State number ([0 -- cstate_get_number() -1])
 * @DESCRIPTION		return the number of time(s) a C-State was entered
 *//*------------------------------------------------------------------------ */
uint64_t cstate_get_usage(unsigned int n)
{
	FILE *fp;
	int ret;
	uint64_t usage;

	if (cstate_get_number() == 0) {
		fprintf(stderr, "%s(): no C-State!\n", __func__);
		return 0;
	}
	if (n >= cstate_get_number()) {
		fprintf(stderr, "%s(): error n (%u) > cstates_nbr (%u)!\n",
			__func__, n, cstate_get_number());
		return 0;
	}

	cstate_usagefile[42] = int2char_table[n];
	dprintf("%s(): opening %s\n", __func__, cstate_usagefile);
	fp = fopen(cstate_usagefile, "r");
	if (fp == NULL) {
		fprintf(stderr, "%s(): error opening %s usage file!\n",
			__func__, cstate_usagefile);
		return 0;
	}
	ret = fscanf(fp, "%llu", &usage);
	if (ret != 1) {
		fprintf(stderr, "%s(): error reading %s usage file!\n",
			__func__, cstate_usagefile);
		fclose(fp);
		return 0;
	}
	dprintf("%s(%u): usage = %llu\n", __func__, n, usage);
	fclose(fp);

	return usage;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cstate_get_time
 * @BRIEF		return the time spent in a given C-State
 * @RETURNS		time spent in given C-State (in microseconds)
 *			0 in case of error
 * @param[in]		n: C-State number ([0 -- cstate_get_number() -1])
 * @DESCRIPTION		return the time spent in a given C-State
 *//*------------------------------------------------------------------------ */
uint64_t cstate_get_time(unsigned int n)
{
	FILE *fp;
	int ret;
	uint64_t time;

	if (cstate_get_number() == 0) {
		fprintf(stderr, "%s(): no C-State!\n", __func__);
		return 0;
	}
	if (n >= cstate_get_number()) {
		fprintf(stderr, "%s(): error n (%u) > cstates_nbr (%u)!\n",
			__func__, n, cstate_get_number());
		return 0;
	}

	cstate_timefile[42] = int2char_table[n];
	dprintf("%s(): opening %s\n", __func__,	cstate_timefile);
	fp = fopen(cstate_timefile, "r");
	if (fp == NULL) {
		fprintf(stderr, "%s(): error opening %s time file!\n",
			__func__, cstate_timefile);
		return 0;
	}
	ret = fscanf(fp, "%llu", &time);
	if (ret != 1) {
		fprintf(stderr, "%s(): error reading %s time file!\n",
			__func__, cstate_timefile);
		fclose(fp);
		return 0;
	}
	dprintf("%s(%u): time = %llu\n", __func__, n, time);
	fclose(fp);
	return time;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cstate_get_name
 * @BRIEF		return the name of a given C-State
 * @RETURNS		name of given C-State
 *			NULL in case of error
 * @param[in]		n: C-State number ([0 -- cstate_get_number() -1])
 * @param[in,out]	name: name of given C-State (returned)
 * @DESCRIPTION		return the name of a given C-State
 *//*------------------------------------------------------------------------ */
char *cstate_get_name(unsigned int n, char name[3])
{
	FILE *fp;
	int ret;

	if (cstate_get_number() == 0) {
		fprintf(stderr, "%s(): no C-State!\n", __func__);
		return NULL;
	}
	if (n >= cstate_get_number()) {
		fprintf(stderr, "%s(): error n (%u) > cstates_nbr (%u)!\n",
			__func__, n, cstate_get_number());
		return NULL;
	}
	if (name == NULL) {
		fprintf(stderr, "%s(): name == NULL!\n", __func__);
		return NULL;
	}

	cstate_namefile[42] = int2char_table[n];
	dprintf("%s(): opening %s\n", __func__, cstate_namefile);
	fp = fopen(cstate_namefile, "r");
	if (fp == NULL) {
		fprintf(stderr, "%s(): error opening %s time file!\n",
			__func__, cstate_namefile);
		return 0;
	}
	ret = fscanf(fp, "%s", name);
	if (ret != 1) {
		fprintf(stderr, "%s(): error reading %s time file!\n",
			__func__, cstate_namefile);
		fclose(fp);
		return 0;
	}
	dprintf("%s(%u): name = %s\n", __func__, n, name);
	fclose(fp);

	return name;
}
