/*
 *
 * @Component			OMAPCONF
 * @Filename			cpufreq.c
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


#include <cpufreq.h>
#include <stdio.h>
#include <string.h>


/* #define CPUFREQ_DEBUG */
#ifdef CPUFREQ_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static char cpufreq_time_in_state_file[60] =
	"/sys/devices/system/cpu/cpu0/cpufreq/stats/time_in_state";
static char cpufreq_total_trans_file[60] =
	"/sys/devices/system/cpu/cpu0/cpufreq/stats/total_trans";
static char cpufreq_scaling_gov_file[60] =
	"/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor";
static char cpufreq_scaling_cur_freq_file[60] =
	"/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq";
static char cpufreq_scaling_setspeed_file[60] =
	"/sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed";
static int cpufreq_opp_nbr = -1;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpufreq_total_transitions_get
 * @BRIEF		return the total number of OPP transitions that happened
 *			since start
 * @RETURNS		total number of OPP transitions that happened since start
 *			0 in case of error
 * @param[in]		none
 * @DESCRIPTION		return the total number of OPP transitions that happened
 *			since start
 *//*------------------------------------------------------------------------ */
uint64_t cpufreq_total_transitions_get(void)
{
	FILE *fp;
	int ret;
	uint64_t count;

	fp = fopen(cpufreq_total_trans_file, "r");
	if (fp == NULL) {
		fprintf(stderr, "%s not found, no CPUFREQ?\n\n",
			cpufreq_total_trans_file);
		return 0;
	}

	ret = fscanf(fp, "%llu", &count);
	if (ret != 1) {
		fprintf(stderr, "%s(): error reading %s file!\n",
			__func__, cpufreq_total_trans_file);
		fclose(fp);
		return 0;
	}

	fclose(fp);
	dprintf("%s()=%llu\n", __func__, count);
	return count;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpufreq_time_in_state_get
 * @BRIEF		return the time spent in a given OPP
 * @RETURNS		time spent in given OPP (in milliseconds)
 *			0 in case of error
 * @param[in]		opp_id: OPP
 * @DESCRIPTION		return the time spent in a given OPP
 *//*------------------------------------------------------------------------ */
uint64_t cpufreq_time_in_state_get(unsigned int opp)
{
	FILE *fp;
	int ret;
	unsigned int i;
	unsigned int freq;
	uint64_t time;

	fp = fopen(cpufreq_time_in_state_file, "r");
	if (fp == NULL) {
		fprintf(stderr, "%s not found, no CPUFREQ?\n\n",
			cpufreq_time_in_state_file);
		return 0;
	}

	for (i = 0; i <= opp; i++) {
		ret = fscanf(fp, "%u %llu", &freq, &time);
		if (ret != 2) {
			fprintf(stderr, "%s(%u): i=%u error reading %s file!\n",
				__func__, opp, i,
				cpufreq_time_in_state_file);
			fclose(fp);
			return 0;
		}
		dprintf("%s(%u): i=%u, fscanf(fp, \"%%u %%llu\")=%u %llu\n",
			__func__, opp, i, freq, time);
	}
	fclose(fp);

	return time;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpufreq_scaling_governor_get
 * @BRIEF		return the name of the current scaling governor
 * @RETURNS		name of the current scaling governor
 *			NULL in case of error
 * @param[in,out]	name: name of the current scaling governor (returned)
 * @DESCRIPTION		return the name of the current scaling governor
 *//*------------------------------------------------------------------------ */
char *cpufreq_scaling_governor_get(char name[CPUFREQ_GOV_MAX_NAME_LENGTH])
{
	FILE *fp;
	int ret;

	if (name == NULL) {
		fprintf(stderr, "%s(): name == NULL!\n", __func__);
		name = NULL;
		return NULL;
	}

	fp = fopen(cpufreq_scaling_gov_file, "r");
	if (fp == NULL) {
		fprintf(stderr, "%s not found, no CPUFREQ?\n\n",
			cpufreq_scaling_gov_file);
		name = NULL;
		return NULL;
	}

	ret = fscanf(fp, "%s", name);
	if (ret != 1) {
		fprintf(stderr, "%s(): error reading %s file!\n",
			__func__, cpufreq_scaling_gov_file);
		fclose(fp);
		name = NULL;
		return NULL;
	}
	dprintf("%s(): name = %s\n", __func__, name);
	fclose(fp);

	return name;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpufreq_scaling_governor_set
 * @BRIEF		set scaling governor and return previous governor
 * @RETURNS		0 in case of success
 *			CPUFREQ_ERR_ARG
 *			CPUFREQ_ERR_NOT_AVAILABLE
 *			CPUFREQ_ERR_UNEXPECTED
 * @param[in,out]	new_gov: name of the new scaling governor
 * @param[in,out]	prev_gov: name of the previous scaling governor
 *				(returned)
 * @DESCRIPTION		set scaling governor and return previous governor
 *//*------------------------------------------------------------------------ */
int cpufreq_scaling_governor_set(char new_gov[CPUFREQ_GOV_MAX_NAME_LENGTH],
	char prev_gov[CPUFREQ_GOV_MAX_NAME_LENGTH])
{
	FILE *fp = NULL;
	int ret;

	if ((new_gov == NULL) || (prev_gov == NULL)) {
		fprintf(stderr, "%s(): name || prev_gov == NULL!\n", __func__);
		ret = 0;
		goto cpufreq_scaling_governor_set_end;
	}

	/* Open /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor */
	fp = fopen(cpufreq_scaling_gov_file, "r+");
	if (fp == NULL) {
		fprintf(stderr, "%s not found, no CPUFREQ?\n\n",
			cpufreq_scaling_gov_file);
		ret = CPUFREQ_ERR_NOT_AVAILABLE;
		strcpy(prev_gov, "NONE");
		goto cpufreq_scaling_governor_set_end;
	}

	/* Save previous governor */
	if (fgets(prev_gov, 64, fp) == NULL) {
		fprintf(stderr, "%s(): could not read %s?!\n", __func__,
			cpufreq_scaling_gov_file);
		ret = CPUFREQ_ERR_UNEXPECTED;
		strcpy(prev_gov, "UNKNOWN");
		goto cpufreq_scaling_governor_set_end;
	}
	/* Remove endind '\n' if any */
	if (prev_gov[strlen(prev_gov) - 1] == '\n')
		prev_gov[strlen(prev_gov) - 1] = '\0';
	dprintf("%s(): prev_gov=%s len=%u\n",
		__func__, prev_gov, strlen(prev_gov));

	/* Set new governor */
	rewind(fp);
	dprintf("%s(): new_gov=%s\n", __func__, new_gov);
	if (fwrite(new_gov, sizeof(char), strlen(new_gov), fp)
		!= strlen(new_gov)) {
		fprintf(stderr, "could not update governor, "
			"does it run in privileged mode?\n");
		ret = CPUFREQ_ERR_UNEXPECTED;
		goto cpufreq_scaling_governor_set_end;
	}
	dprintf("%s(): switch from %s to %s governor ok\n",
		__func__, prev_gov, new_gov);
	ret = 0;

cpufreq_scaling_governor_set_end:
	if (fp != NULL)
		fclose(fp);
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpufreq_cur_freq_get
 * @BRIEF		return the current CPU frequency (KHz)
 * @RETURNS		current CPU frequency (KHz)
 *			0 in case of error
 * @param[in]		none
 * @DESCRIPTION		return the current CPU frequency (KHz)
 *//*------------------------------------------------------------------------ */
unsigned int cpufreq_cur_freq_get(void)
{
	FILE *fp;
	int ret;
	unsigned int cur_freq;

	fp = fopen(cpufreq_scaling_cur_freq_file, "r");
	if (fp == NULL) {
		fprintf(stderr, "%s not found, no CPUFREQ?\n\n",
			cpufreq_scaling_cur_freq_file);
		return 0;
	}

	ret = fscanf(fp, "%u", &cur_freq);
	fclose(fp);
	if (ret != 1) {
		fprintf(stderr, "%s(): error reading %s file!\n",
			__func__, cpufreq_scaling_cur_freq_file);
		return 0;
	}
	dprintf("%s(): cur_freq = %u\n", __func__, cur_freq);

	return cur_freq;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpufreq_opp_nbr_get
 * @BRIEF		return the number of OPP available
 * @RETURNS		> 0 the number of OPP available
 *			0 in case of error
 * @param[in]		none
 * @DESCRIPTION		return the number of OPP available
 *//*------------------------------------------------------------------------ */
unsigned int cpufreq_opp_nbr_get(void)
{
	FILE *fp;
	int ret;
	unsigned int freq, time;

	if (cpufreq_opp_nbr != -1)
		return (unsigned int) cpufreq_opp_nbr;

	fp = fopen(cpufreq_time_in_state_file, "r");
	if (fp == NULL) {
		fprintf(stderr, "%s not found, no CPUFREQ?\n\n",
			cpufreq_time_in_state_file);
		cpufreq_opp_nbr = 0;
		return (unsigned int) cpufreq_opp_nbr;
	}

	cpufreq_opp_nbr = 0;
	do {
		ret = fscanf(fp, "%u %u", &freq, &time);
		if (ret != 2) {
			dprintf("%s(): cpufreq_opp_nbr=%d\n",
				__func__, cpufreq_opp_nbr);
			break;
		}
		dprintf("%s(): freq=%u time=%u\n",
			__func__, freq, time);
		cpufreq_opp_nbr++;
	} while (ret == 2);

	fclose(fp);
	return (unsigned int) cpufreq_opp_nbr;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpufreq_set
 * @BRIEF		change MPU OPP using cpufreq userspace governor.
 * @RETURNS		0 in case of success
 *			CPUFREQ_ERR_NOT_AVAILABLE
 *			CPUFREQ_ERR_UNEXPECTED
 * @param[in]		freq_mpu: MPU frequency to be set (KHz)
 * @DESCRIPTION		change MPU OPP using cpufreq userspace governor.
 *//*------------------------------------------------------------------------ */
int cpufreq_set(unsigned int freq_mpu)
{
	int ret;
	char prev_gov[CPUFREQ_GOV_MAX_NAME_LENGTH];
	char freq_mpu_s[8];
	FILE *fp;

	/* Switch to userspace governor to get MPU OPP control */
	ret = cpufreq_scaling_governor_set("userspace", prev_gov);
	if (ret != 0)
		return ret;

	fp = fopen(cpufreq_scaling_setspeed_file, "r+");
	if (fp == NULL) {
		fprintf(stderr, "%s not found, no CPUFREQ?\n\n",
			cpufreq_scaling_setspeed_file);
		return CPUFREQ_ERR_NOT_AVAILABLE;
	}

	sprintf(freq_mpu_s, "%u", freq_mpu);
	if (fwrite(freq_mpu_s, sizeof(char), strlen(freq_mpu_s), fp)
		!= strlen(freq_mpu_s)) {
		fprintf(stderr, "%s(): could not update CPU frequency!\n",
			__func__);
		ret = CPUFREQ_ERR_UNEXPECTED;
	} else {
		ret = 0;
	}

	if (fp != NULL)
		fclose(fp);

	return ret;
}
