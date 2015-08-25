/*
 *
 * @Component			OMAPCONF
 * @Filename			audit.c
 * @Description			Generic Power Audit Functions
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


#include <audit.h>
#include <lib.h>
#include <autoadjust_table.h>
#include <cpufreq.h>
#include <cpuinfo.h>
#include <help.h>
#include <interrupts.h>
#include <timer_stats.h>
#include <cstate.h>
#include <unistd.h>
#include <voltdm44xx.h>
#include <voltdm54xx.h>
#include <emif44xx.h>


#define AUDIT_PERF_DEFAULT_DURATION	10
#define AUDIT_PERF_DEFAULT_DELAY	10


/* #define AUDIT_DEBUG */
#ifdef AUDIT_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		audit_performances
 * @BRIEF		audit performances (CPU Load, C-States, OPP,
 *			memory bandwidth, timers, interrrupts, ...).
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		stream: output file (NULL: no output (silent))
 * @param[in]		duration: audit duration, in seconds (>= 1).
 * @param[in]		delay: initial wait delay before starting audit (in sec)
 * @DESCRIPTION		audit performance (CPU Load, C-States, OPP,
 *			memory bandwidth, timers, interrrupts, ...).
 *//*------------------------------------------------------------------------ */
int audit_performances(FILE *stream, unsigned int duration, unsigned int delay)
{
	int ret = 0;
	unsigned short skip_proc_stats_audit = 0;
	unsigned int cpu_cores_cnt = 0, cpu_online_cores_cnt = 0;
	unsigned short *cpu_online = NULL;
	unsigned int *idle_t0 = NULL, *iowait_t0 = NULL, *sum_t0 = NULL;
	unsigned int *idle_t1 = NULL, *iowait_t1 = NULL, *sum_t1 = NULL;
	unsigned int *idle_cnt = NULL, *iowait_cnt = NULL, *sum_cnt = NULL;
	double *load = NULL, load_total = 0;
	unsigned int cstates_nbr = 0;
	uint64_t cstates_usage[MAX_CSTATE][3] = { {0} };
	uint64_t cstates_time[MAX_CSTATE][3] = { {0} };
	unsigned short emif = 0;
	unsigned int emif_busy_cycles[2] = { 0 };
	unsigned int emif_cycles[2] = { 0 };
	unsigned int emif_delta_cycles = 0,
		emif_delta_busy_cycles = 0;
	double emif_load = 0;
	uint64_t *time_in_opp_t0 = NULL;
	uint64_t *time_in_opp_t1 = NULL;
	uint64_t *time_in_opp_cnt = NULL;
	uint64_t total_trans_t0 = 0, total_trans_t1 = 0, total_trans_cnt = 0;
	unsigned int i = 0;
	uint64_t sec = 0, msec = 0, usec = 0, active_c0_time = 0;
	double pct = 0;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row = 0;
	char name[16] = { 0 };
	FILE *fp = NULL;
	char perf_summary_file[64];
	FILE *fp_irq_1 = NULL, *fp_irq_2 = NULL, *fp_timerstats = NULL;
	unsigned int irq_total_count = 0, occurred_irq_count = 0, timer_count = 0;
	genlist occurred_irq_list, timerstats_list;
	irq_info irq_inf = { 0 };
	timerstat_info timer_inf = { 0 };
	char irq_snap_file1[32] = { 0 };
	char irq_snap_file2[32] = { 0 };
	char timerstats_file[32] = { 0 };
	char timerstats_summary[256] = { 0 };
	unsigned int skip_irq_audit = 0, skip_cstate_audit = 0;
	int skip_timerstats_audit = 0;
	char *workdir = NULL;
	unsigned short skip_cpufreq_audit = 0;
	unsigned int opp_cnt = 0;


	if (duration == 0) {
		fprintf(stream, "Duration should be at least 1 second ...\n\n");
		ret = OMAPCONF_ERR_ARG;
		goto audit_performances_exit;
	}

	if (!cpu_is_omap44xx() && !cpu_is_omap54xx()) {
		fprintf(stream, "Unsupported platform, sorry...\n\n");
		ret = OMAPCONF_ERR_CPU;
		goto audit_performances_exit;
	}

	/* Retrieve a writable directory */
	workdir = workdir_get();
	if (workdir != NULL) {
		strcpy(irq_snap_file1, workdir);
		strcpy(irq_snap_file2, workdir);
		strcpy(timerstats_file, workdir);
		strcpy(perf_summary_file, workdir);
		strcat(irq_snap_file1, "proc_interrupts_1");
		strcat(irq_snap_file2, "proc_interrupts_2");
		strcat(timerstats_file, "proc_timerstats");
		strcat(perf_summary_file, "performance_audit_report.txt");
		skip_irq_audit = 0;
		skip_timerstats_audit = 0;
	} else {
		skip_irq_audit = 1;
		skip_timerstats_audit = 1;
	}

	/* Open trace output file */
	fp = fopen(perf_summary_file, "w");
	if (fp == NULL) {
		fprintf(stderr, "%s(): could not create %s!\n",
			__func__, perf_summary_file);
	} else {
		fprintf(fp, "OMAP Performance Audit Summary\n\n");
		omapconf_revision_show(fp);
		chips_info_show(fp, 1);
		release_info_show(fp);
	}

	/* Retrieve number of CPU cores and allocate buffers */
	cpu_cores_cnt = cpu_cores_count_get();
	if (cpu_cores_cnt < 1) {
		skip_proc_stats_audit = 1;
	} else {
		dprintf("%s(): found %u cores\n", __func__, cpu_cores_cnt);
		cpu_online = malloc(cpu_cores_cnt * sizeof(unsigned int));
		idle_t0 = malloc(cpu_cores_cnt * sizeof(unsigned int));
		iowait_t0 = malloc(cpu_cores_cnt * sizeof(unsigned int));
		sum_t0 = malloc(cpu_cores_cnt * sizeof(unsigned int));
		idle_t1 = malloc(cpu_cores_cnt * sizeof(unsigned int));
		iowait_t1 = malloc(cpu_cores_cnt * sizeof(unsigned int));
		sum_t1 = malloc(cpu_cores_cnt * sizeof(unsigned int));
		idle_cnt = malloc(cpu_cores_cnt * sizeof(unsigned int));
		iowait_cnt = malloc(cpu_cores_cnt * sizeof(unsigned int));
		sum_cnt = malloc(cpu_cores_cnt * sizeof(unsigned int));
		load = malloc(cpu_cores_cnt * sizeof(double));
		if ((cpu_online == NULL) || (idle_t0 == NULL) ||
			(iowait_t0 == NULL) || (sum_t0 == NULL) ||
			(idle_t1 == NULL) || (iowait_t1 == NULL) ||
			(sum_t1 == NULL) || (iowait_cnt == NULL) ||
			(iowait_cnt == NULL) || (sum_cnt == NULL) ||
			(load == NULL)) {
			fprintf(stderr, "%s(): could not allocate buffers for "
				"CPU stats!\n", __func__);
			skip_proc_stats_audit = 1;
		}
		dprintf("%s(): CPU stats buffers allocated.\n", __func__);
		skip_proc_stats_audit = 0;
	}

	/* Retrieve number of MPU OPPs and allocate buffers */
	opp_cnt = cpufreq_opp_nbr_get();
	if (opp_cnt == 0) {
		skip_cpufreq_audit = 1;
	} else {
		dprintf("%s(): found %u MPU OPPs\n", __func__, opp_cnt);
		time_in_opp_t0 = malloc(opp_cnt * sizeof(uint64_t));
		time_in_opp_t1 = malloc(opp_cnt * sizeof(uint64_t));
		time_in_opp_cnt = malloc(opp_cnt * sizeof(uint64_t));
		if ((time_in_opp_t0 == NULL) || (time_in_opp_t1 == NULL) ||
			(time_in_opp_cnt == NULL)) {
			fprintf(stderr, "%s(): could not allocate buffers for "
				"CPUFREQ stats!\n", __func__);
			skip_cpufreq_audit = 1;
		}
		dprintf("%s(): CPUFREQ stats buffers allocated.\n", __func__);
		skip_cpufreq_audit = 0;
	}

	/* Configure EMIF counters to count data bus busy cycles (OMAP4) */
	if (cpu_is_omap44xx()) {
		ret = emif44xx_perf_cnt_configure(EMIF44XX_0,
			EMIF44XX_PERF_CNT_1,
			EMIF44XX_PERF_CNT_FILTER_DATA_TRANSFER_CYCLES,
			-1, EMIF44XX_MEMADDRSPACE_DISABLED);
		ret |= emif44xx_perf_cnt_configure(EMIF44XX_1,
			EMIF44XX_PERF_CNT_1,
			EMIF44XX_PERF_CNT_FILTER_DATA_TRANSFER_CYCLES,
			-1, EMIF44XX_MEMADDRSPACE_DISABLED);
		if (ret != 0) {
			strncpy(timerstats_summary,
				"Unexpected error occurred while configuring "
				"EMIF performance counters!!!\n\n", 256);
			if (stream != NULL)
				fputs(timerstats_summary, stream);
			if (fp != NULL)
				fputs(timerstats_summary, fp);
			ret = OMAPCONF_ERR_NOT_AVAILABLE;
			goto audit_performances_exit;
		}
		dprintf("%s(): EMIF counters configured.\n", __func__);
	}

	/* Retrieve number of active C-State(s) */
	cstates_nbr = cstate_get_number();
	if (cstates_nbr == 0) {
		cstates_nbr = 0;
		skip_cstate_audit = 1;
	} else {
		skip_cstate_audit = 0;
		dprintf("%s(): found %u C-State(s)\n", __func__, cstates_nbr);
	}

	if (fp != NULL) {
		fprintf(fp, "Audit duration: %us\n", duration);
		fprintf(fp, "Audit initial delay: %us\n\n", delay);
	}
	/* Initial delay before starting capture */
	if (delay >= 1) {
		if (stream != NULL)
			fprintf(stream, "Wait for initial delay (%u sec), then"
				" sample various Key Performance Indicators "
				"over %u second(s) ...\n\n", delay, duration);
		sleep(delay);
	} else {
		if (stream != NULL)
			fprintf(stream,
			"Sampling various Key Performance Indicators "
			"over %u second(s) ...\n\n", duration);
	}

	/* Save current C-State usage & time counters */
	if (skip_cstate_audit == 0) {
		for (i = 0; i < cstates_nbr; i++) {
			cstates_usage[i][0] = cstate_get_usage(i);
			cstates_time[i][0] = cstate_get_time(i);
		}
	}

	/* Save current cpufreq stats */
	if (skip_cpufreq_audit == 0) {
		for (i = 0; i < opp_cnt; i++) {
			time_in_opp_t0[i] = cpufreq_time_in_state_get(i);
			dprintf("%s(): time_in_opp_t0[%u] = %llu\n",
				__func__, i, time_in_opp_t0[i]);
		}
		total_trans_t0 = cpufreq_total_transitions_get();
	}

	/* Save current cpu usage stats */
	if (skip_proc_stats_audit == 0) {
		for (i = 0; i < cpu_cores_cnt; i++) {
			ret = cpu_proc_stats_get(i,
				&idle_t0[i], &iowait_t0[i], &sum_t0[i]);
			if (ret != 0) {
				cpu_online[i] = 0;
				dprintf("%s(): CPU%u offline\n", __func__, i);
			} else {
				cpu_online[i] = 1;
			}

		}
	}

	/* Get current EMIFs total & data transfer cycles */
	if (cpu_is_omap44xx()) {
		emif_busy_cycles[0] = 0;
		for (emif = 0; emif < EMIF44XX_MAX; emif++) {
			emif_busy_cycles[0] += emif44xx_perf_cnt_get_count(
				(emif44xx_ids) emif, EMIF44XX_PERF_CNT_1);
		}
		emif_cycles[0] = emif44xx_perf_cnt_get_time(EMIF44XX_0);
	}

	/* Save current interrupt stats */
	if (skip_irq_audit != 1) {
		ret = irq_snapshot_save(irq_snap_file1);
		if (ret != 0)
			skip_irq_audit = 1;
	}

	/* Save current timer stats */
	/* Stop timer statistic collector, if enabled */
	skip_timerstats_audit = timerstats_stop();
	if (skip_timerstats_audit == 0)
		skip_timerstats_audit = timerstats_start();

	/* Sleep for some time before sampling again usage counters */
	sleep(duration);

	/* Get new EMIFs total & data transfer cycles */
	if (cpu_is_omap44xx()) {
		emif_busy_cycles[1] = 0;
		for (emif = 0; emif < EMIF44XX_MAX; emif++) {
			emif_busy_cycles[1] += emif44xx_perf_cnt_get_count(
				(emif44xx_ids) emif, EMIF44XX_PERF_CNT_1);
		}
		emif_cycles[1] = emif44xx_perf_cnt_get_time(EMIF44XX_0);
	}

	if (skip_timerstats_audit == 0)
		skip_timerstats_audit = timerstats_stop();

	/* Get new interrupts stats */
	if (skip_irq_audit == 0) {
		ret = irq_snapshot_save(irq_snap_file2);
		if (ret != 0) {
			skip_irq_audit = 1;
			remove(irq_snap_file1);
		}
	}

	if (skip_timerstats_audit == 0)
		timerstats_save(timerstats_file);

	/* Get new cpu usage stats*/
	if (skip_proc_stats_audit == 0) {
		for (i = 0; i < cpu_cores_cnt; i++) {
			ret = cpu_proc_stats_get(i,
				&idle_t1[i], &iowait_t1[i], &sum_t1[i]);
			if (ret != 0) {
				cpu_online[i] = 0;
				dprintf("%s(): CPU%u offline\n", __func__, i);
			} else {
				cpu_online[i] = 1;
			}

		}
	}

	/* Get new cpufreq stats */
	if (skip_cpufreq_audit == 0) {
		for (i = 0; i < opp_cnt; i++) {
			time_in_opp_t1[i] = cpufreq_time_in_state_get(i);
			dprintf("%s(): time_in_opp_t1[%u] = %llu\n",
				__func__, i, time_in_opp_t1[i]);
		}
		total_trans_t1 = cpufreq_total_transitions_get();
	}

	/* Get new C-State usage counters */
	if (skip_cstate_audit == 0) {
		for (i = 0; i < cstates_nbr; i++) {
			cstates_usage[i][1] = cstate_get_usage(i);
			cstates_time[i][1] = cstate_get_time(i);
			dprintf("%s(): cstates_usage[%u][0] = "
				"%llu\n", __func__, i, cstates_usage[i][0]);
			dprintf("%s(): cstates_usage[%u][1] = "
				"%llu\n", __func__, i, cstates_usage[i][1]);
			dprintf("%s(): cstates_time[%u][0] = "
				"%llu\n", __func__, i, cstates_time[i][0]);
			dprintf("%s(): cstates_time[%u][1] = "
				"%llu\n", __func__, i, cstates_time[i][1]);
		}
	}

	/* Process data */
	if (cpu_is_omap44xx()) {
		emif_delta_busy_cycles = count32_delta(
			emif_busy_cycles[0], emif_busy_cycles[1]);
		emif_delta_cycles = 2 * count32_delta(
			emif_cycles[0], emif_cycles[1]);
		dprintf("%s(): EMIF delta_busy_cycles=%u, delta_cycles=%u\n",
			__func__, emif_delta_busy_cycles, emif_delta_cycles);
		emif_load = 100.0 * (
			(double) emif_delta_busy_cycles /
				emif_delta_cycles);
		dprintf("%s(): EMIF load = %lf%%\n", __func__, emif_load);
	}

	if (skip_cpufreq_audit == 0) {
		total_trans_cnt = count64_delta(total_trans_t0, total_trans_t1);
		dprintf("CPUFREQ:\n");
		dprintf("  total transitions = %llu\n", total_trans_cnt);
		for (i = 0; i < opp_cnt; i++) {
			time_in_opp_cnt[i] =
				count64_delta(time_in_opp_t0[i],
					time_in_opp_t1[i]);
			#ifdef AUDIT_DEBUG
			/* FIXME: retrieve cpufreq sampling rate (variable) */
			if (cpu_is_omap44xx())
				printf("  time in OPP %s = %llums\n",
					opp44xx_name_get(i + 1, OMAP4_VDD_MPU),
					time_in_opp_cnt[i] * 10);
			else
				printf("  time in OPP %s = %llums\n",
					opp54xx_name_get(i + 1),
					time_in_opp_cnt[i] * 10);
			#endif
		}
	}

	if (skip_cstate_audit == 0) {
		for (i = 0; i < cstates_nbr; i++) {
			cstates_usage[i][2] = count64_delta(
				cstates_usage[i][0], cstates_usage[i][1]);

			cstates_time[i][2] = count64_delta(
				cstates_time[i][0], cstates_time[i][1]);
		}
	}

	/* Compute & Show C-State Statistics */
	if (skip_cstate_audit == 1) {
		strncpy(timerstats_summary,
			"WARNING: could not retrieve C-State number. "
			"Skipping C-States audit.\n\n", 256);
		if (stream != NULL)
			fputs(timerstats_summary, stream);
		if (fp != NULL)
			fputs(timerstats_summary, fp);
	} else {
		autoadjust_table_init(table);
		row = 0;
		strncpy(table[row][0], "C-State", TABLE_MAX_ELT_LEN);
		strncpy(table[row][1], "Entered?", TABLE_MAX_ELT_LEN);
		strncpy(table[row][2], "Hit Number", TABLE_MAX_ELT_LEN);
		strncpy(table[row][3], "Time Spent (s)", TABLE_MAX_ELT_LEN);
		strncpy(table[row][4], "Time Spent (%)", TABLE_MAX_ELT_LEN);
		row++;

		strncpy(table[row][0], "Active + \"C0\"", TABLE_MAX_ELT_LEN);
		strncpy(table[row][1], "Yes", TABLE_MAX_ELT_LEN);
		active_c0_time = duration * 1000000;
		for (i = 0; i < cstates_nbr; i++) {
			if (active_c0_time > cstates_time[i][2])
				active_c0_time -= cstates_time[i][2];
			else
				/*
				 * It may be possible that
				 * active_c0_time is < cstates_time[i][2]
				 * (duration may fluctuate a little depending on
				 * system load). Make sure it doesn't cross 0 as
				 * it's an unsigned interger.
				 */
				active_c0_time = 0;

		}
		sec = active_c0_time / 1000000;
		msec = (active_c0_time % 1000000) / 1000;
		usec = active_c0_time % 1000;
		snprintf(table[row][3], TABLE_MAX_ELT_LEN,
			"%llus %llums %lluus", sec, msec, usec);
		pct = ((double) active_c0_time / (double)
					(duration * 1000000)) * 100.0;
		snprintf(table[row][4], TABLE_MAX_ELT_LEN, "%3.1f%%", pct);
		row++;

		for (i = 0; i < cstates_nbr; i++) {
			snprintf(table[row][0], TABLE_MAX_ELT_LEN, "%s",
				cstate_get_name(i, name));
			if (cstates_usage[i][2] != 0) {
				dprintf("%s(): C%u entered\n", __func__, i + 1);
				strncpy(table[row][1], "Yes",
					TABLE_MAX_ELT_LEN);

				snprintf(table[row][2], TABLE_MAX_ELT_LEN,
					"%llu", cstates_usage[i][2]);

				sec = cstates_time[i][2] / 1000000;
				msec = (cstates_time[i][2] % 1000000) / 1000;
				usec = cstates_time[i][2] % 1000;
				snprintf(table[row][3], TABLE_MAX_ELT_LEN,
					"%llus %llums %lluus", sec, msec, usec);

				pct = ((double) cstates_time[i][2] / (double)
					(duration * 1000000)) * 100.0;
				snprintf(table[row][4], TABLE_MAX_ELT_LEN,
					"%3.1f%%", pct);
			} else {
				dprintf("%s(): C%u not entered\n",
					__func__, i + 1);
				strncpy(table[row][1], "No", TABLE_MAX_ELT_LEN);
			}
			row++;
		}

		/* Print results */
		strncpy(timerstats_summary,
			"NB: this table shows statistics about "
			"the ATTEMPTED C-States, not the effectively "
			"entered C-States (not supported by kernel "
			"idle framework yet).\nAs a consequence, these "
			"C-States MAY or MAY NOT have been entered, "
			"depending on HW conditions.\n\n\n", 256);
		if (stream != NULL) {
			autoadjust_table_fprint(stream, table, row, 5);
			fputs(timerstats_summary, stream);
		}
		if (fp != NULL) {
			autoadjust_table_fprint(fp, table, row, 5);
			fputs(timerstats_summary, fp);
		}
	}

	/* Show CPUFreq stats */
	if (skip_cpufreq_audit == 1) {
		strncpy(timerstats_summary, "WARNING: could not retrieve MPU "
			"OPP number. CPUFreq audit skipped.\n\n", 256);
		if (stream != NULL)
			fputs(timerstats_summary, stream);
		if (fp != NULL)
			fputs(timerstats_summary, fp);
	} else {
		autoadjust_table_init(table);
		row = 0;
		strncpy(table[row][0], "MPU OPP", TABLE_MAX_ELT_LEN);
		strncpy(table[row][1], "Time Spent in OPP", TABLE_MAX_ELT_LEN);
		row++;

		for (i = 0; i < opp_cnt; i++) {
			if (cpu_is_omap44xx())
				snprintf(table[row][0], TABLE_MAX_ELT_LEN, "%s",
					opp44xx_name_get(i + 1, OMAP4_VDD_MPU));
			else
				snprintf(table[row][0], TABLE_MAX_ELT_LEN, "%s",
					opp54xx_name_get(i + 1));
			snprintf(table[row][1], TABLE_MAX_ELT_LEN,
				"%llus%llums",
				time_in_opp_cnt[i] / 100,
				(time_in_opp_cnt[i] % 100) * 10);
			row++;
		}

		cpufreq_scaling_governor_get(name);
		if (name != NULL)
			sprintf(timerstats_summary,
				"CPUFreq Governor: %s\n", name);
		else
			sprintf(timerstats_summary,
				"CPUFreq Governor: not found!\n");
		if (stream != NULL)
			fputs(timerstats_summary, stream);
		if (fp != NULL)
			fputs(timerstats_summary, fp);

		sprintf(timerstats_summary,
			"Total number of OPP transitions: %llu\n\n",
			total_trans_cnt);
		if (stream != NULL) {
			fputs(timerstats_summary, stream);
			autoadjust_table_fprint(stream, table, row, 2);
			fprintf(stream, "\n");
		}
		if (fp != NULL) {
			fputs(timerstats_summary, fp);
			autoadjust_table_fprint(fp, table, row, 2);
			fprintf(fp, "\n");
		}
	}

	/* Show CPU Load stats */
	if (skip_proc_stats_audit == 1) {
		strncpy(timerstats_summary, "WARNING: could not retrieve CPU "
			"cores number. CPU Load audit skipped.\n\n", 256);
		if (stream != NULL)
			fputs(timerstats_summary, stream);
		if (fp != NULL)
			fputs(timerstats_summary, fp);
	} else {
		autoadjust_table_init(table);
		row = 0;
		strncpy(table[row][0], "CPU", TABLE_MAX_ELT_LEN);
		strncpy(table[row][1], "Average Load (*)", TABLE_MAX_ELT_LEN);
		row++;

		cpu_online_cores_cnt = 0;
		load_total = 0.0;
		for (i = 0; i < cpu_cores_cnt; i++) {
			snprintf(table[row][0], TABLE_MAX_ELT_LEN, "CPU%u", i);
			if ((i >= 1) && (cpu_online[i] == 0)) {
				snprintf(table[row][1], TABLE_MAX_ELT_LEN,
					"Offline");
				row++;
				continue;
			}

			idle_cnt[i] =
				count32_delta(idle_t0[i], idle_t1[i]);
			iowait_cnt[i] =
				count32_delta(iowait_t0[i], iowait_t1[i]);
			sum_cnt[i] =
				count32_delta(sum_t0[i], sum_t1[i]);
			dprintf("%s(): idle_cnt[%u] = %u, iowait_cnt[%u] = %u, "
				"sum_cnt[%u] = %u\n", __func__, i, idle_cnt[i],
				i, iowait_cnt[i], i, sum_cnt[i]);
			if (sum_cnt[i] != 0) {
				load[i] = cpu_load_get(idle_cnt[i],
					iowait_cnt[i], sum_cnt[i]);
				cpu_online_cores_cnt++;
			} else {
				/*
				 * Due to tickless feature, it is possible that
				 * that no tick occured during this sampling
				 * window and so /proc/stat counters were not
				 * incremented. => cpu load = 0.
				 */
				load[i] = 0.0;
			}
			load_total += load[i];
			dprintf("%s(): CPU%u load=%.2lf%%\n",
					__func__, i, load[i]);
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%.2lf%%",
				load[i]);
			row++;
		}
		dprintf("%s(): cpu_online_cores_cnt=%u\n",
			__func__, cpu_online_cores_cnt);
		load_total = load_total / cpu_online_cores_cnt;
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "Total");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%.2lf%%",
			load_total);
		row++;

		strncpy(timerstats_summary, "(*) CANNOT be converted to Mhz. "
			"OPP may have changed during the audit.\n\n\n", 256);
		if (stream != NULL) {
			autoadjust_table_fprint(stream, table, row, 2);
			fputs(timerstats_summary, stream);
		}
		if (fp != NULL) {
			autoadjust_table_fprint(fp, table, row, 2);
			fputs(timerstats_summary, fp);
		}
	}

	/* Show EMIF stats */
	if (cpu_is_omap44xx()) {
		autoadjust_table_init(table);
		row = 0;
		strncpy(table[row][0], "EMIF", TABLE_MAX_ELT_LEN);
		strncpy(table[row][1], "Average Load (*)", TABLE_MAX_ELT_LEN);
		row++;
		strncpy(table[row][0], "Total EMIF Data Bus Load",
			TABLE_MAX_ELT_LEN);
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%.2lf%%",
				(double) emif_load);
		row++;
		strncpy(timerstats_summary, "(*) CANNOT be converted to memory "
			"bandwidth (MB/s).\n    DDR data busy cycles may be "
			"commands (not data) and data size is unknown.\n\n\n",
			256);
		if (stream != NULL) {
			autoadjust_table_fprint(stream, table, row, 2);
			fputs(timerstats_summary, stream);
		}

		if (fp != NULL) {
			autoadjust_table_fprint(fp, table, row, 2);
			fputs(timerstats_summary, fp);
		}
	}


	/* Show interrupts stats */
	if (skip_irq_audit == 1) {
		strncpy(timerstats_summary,
			"WARNING: could not save a snapshot of "
			"/proc/interrupts file. "
			"IRQ audit skipped.\n\n", 256);
		if (stream != NULL)
			fputs(timerstats_summary, stream);
		if (fp != NULL)
			fputs(timerstats_summary, fp);
	} else {
		fp_irq_1 = fopen(irq_snap_file1, "r");
		fp_irq_2 = fopen(irq_snap_file2, "r");
		if ((fp_irq_1 == NULL) || (fp_irq_2 == NULL)) {
			fprintf(stderr, "%s(): could not open interrupts "
				"snapshot files!\n\n", __func__);
			ret = OMAPCONF_ERR_NOT_AVAILABLE;
			goto audit_performances_exit;
		}

		autoadjust_table_init(table);
		row = 0;
		strncpy(table[row][0], "IRQ #", TABLE_MAX_ELT_LEN);
		strncpy(table[row][1], "Device Name", TABLE_MAX_ELT_LEN);
		strncpy(table[row][2], "Occurrence", TABLE_MAX_ELT_LEN);
		strncpy(table[row][3], "Proportion", TABLE_MAX_ELT_LEN);
		strncpy(table[row][4], "Rate", TABLE_MAX_ELT_LEN);
		row++;

		irq_total_count = irq_total_count_get(fp_irq_2)
			- irq_total_count_get(fp_irq_1);
		dprintf("%s(): irq_total_count=%d\n", __func__,
			irq_total_count);
		occurred_irq_count = irq_occurred_list_get(fp_irq_1, fp_irq_2,
			&occurred_irq_list);
		dprintf("%s(): # of irq lines that occurred = %d\n", __func__,
			occurred_irq_count);
		irq_occurred_list_sort(&occurred_irq_list);
		for (i = 0; i < occurred_irq_count; i++) {
			genlist_get(&occurred_irq_list, i, &irq_inf);
			snprintf(table[row][0], TABLE_MAX_ELT_LEN, "%d",
				irq_inf.nbr);
			strncpy(table[row][1], irq_inf.dev_name,
				TABLE_MAX_ELT_LEN);
			pct = (double) irq_inf.count / (double) irq_total_count;
			pct *= 100.0;
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u",
				irq_inf.count);
			snprintf(table[row][3], TABLE_MAX_ELT_LEN, "%.1lf%%",
				pct);
			pct = (double) irq_inf.count / (double) duration;
			snprintf(table[row][4], TABLE_MAX_ELT_LEN, "%.1lf/sec",
				pct);
			row++;
		}

		genlist_free(&occurred_irq_list);
		fclose(fp_irq_1);
		remove(irq_snap_file1);
		fclose(fp_irq_2);
		remove(irq_snap_file2);

		sprintf(timerstats_summary,
			"CPU was interrupted %d times by the following %d "
			"sources:\n", irq_total_count, occurred_irq_count);
		if (stream != NULL) {
			fputs(timerstats_summary, stream);
			autoadjust_table_fprint(stream, table, row, 5);
		}
		if (fp != NULL) {
			fputs(timerstats_summary, fp);
			autoadjust_table_fprint(fp, table, row, 5);
		}
	}

	/* Show timer stats */
	if (skip_timerstats_audit != 0) {
		strncpy(timerstats_summary,
			"Timer Statistics: unable to capture kernel timer "
			"statistics.\nMake sure that CONFIG_TIMER_STATS "
			"are enabled in the kernel configuration.\n\n", 256);
		if (stream != NULL)
			fputs(timerstats_summary, stream);
		if (fp != NULL)
			fputs(timerstats_summary, fp);
	} else {
		fp_timerstats = fopen(timerstats_file, "r");
		if (fp_timerstats == NULL) {
			fprintf(stderr, "%s(): could not open timer stats "
				"snapshot file!\n\n", __func__);
			ret = OMAPCONF_ERR_NOT_AVAILABLE;
			goto audit_performances_exit;
		}

		autoadjust_table_init(table);
		row = 0;
		strncpy(table[row][0], "# Timer Events", TABLE_MAX_ELT_LEN);
		strncpy(table[row][1], "Deferrable", TABLE_MAX_ELT_LEN);
		strncpy(table[row][2], "Process ID", TABLE_MAX_ELT_LEN);
		strncpy(table[row][3], "Process Name", TABLE_MAX_ELT_LEN);
		strncpy(table[row][4], "Init Function", TABLE_MAX_ELT_LEN);
		strncpy(table[row][5], "Callback Function", TABLE_MAX_ELT_LEN);
		row++;

		timer_count = timerstats_list_get(fp_timerstats,
			&timerstats_list);
		dprintf("%s(): # of timers that occurred = %d\n", __func__,
			timer_count);
		timerstats_list_sort(&timerstats_list);

		for (i = 0; i < timer_count; i++) {
			genlist_get(&timerstats_list, i, &timer_inf);
			snprintf(table[row][0], TABLE_MAX_ELT_LEN, "%d",
				timer_inf.count);
			strncpy(table[row][1], timer_inf.deferrable,
				TABLE_MAX_ELT_LEN);
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%d",
				timer_inf.pid);
			strncpy(table[row][3], timer_inf.name,
				TABLE_MAX_ELT_LEN);
			strncpy(table[row][4], timer_inf.init_fxn,
				TABLE_MAX_ELT_LEN);
			strncpy(table[row][5], timer_inf.callback,
				TABLE_MAX_ELT_LEN);
			row++;
		}

		timerstats_get_summary(fp_timerstats, &timerstats_summary[0]);
		genlist_free(&timerstats_list);
		fclose(fp_timerstats);
		remove(timerstats_file);

		if (stream != NULL) {
			fputs(timerstats_summary, stream);
			autoadjust_table_fprint(stream, table, row, 6);
		}
		if (fp != NULL) {
			fputs(timerstats_summary, fp);
			autoadjust_table_fprint(fp, table, row, 6);
		}
	}
	if ((fp != NULL) && (stream != NULL))
		fprintf(stream, "Performance Audit data saved into "
			"\"%s\" file.\n\n", perf_summary_file);

	ret = 0;

audit_performances_exit:
	if (cpu_online != NULL)
		free(cpu_online);
	if (idle_t0 != NULL)
		free(idle_t0);
	if (iowait_t0 != NULL)
		free(iowait_t0);
	if (sum_t0 != NULL)
		free(sum_t0);
	if (idle_t1 != NULL)
		free(idle_t1);
	if (iowait_t1 != NULL)
		free(iowait_t1);
	if (sum_t1 != NULL)
		free(sum_t1);
	if (idle_cnt != NULL)
		free(idle_cnt);
	if (iowait_cnt != NULL)
		free(iowait_cnt);
	if (sum_cnt != NULL)
		free(sum_cnt);
	if (load != NULL)
		free(load);

	if (time_in_opp_t0 != NULL)
		free(time_in_opp_t0);
	if (time_in_opp_t1 != NULL)
		free(time_in_opp_t1);
	if (time_in_opp_cnt != NULL)
		free(time_in_opp_cnt);

	if (fp != NULL)
		fclose(fp);

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		audit_performances_main
 * @BRIEF		analyze command-line arguments & call performance audit
 *			with selected options.
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 *				argc=0: default duration, default delay
 *				argc=1: argv[0]=duration
 *				argc=2: argv[0]="-d" argv[1]=delay
 *				argc=3: argv[0]=duration argv[1]="-d"
 *					argv[2]=delay
 * @DESCRIPTION		analyze command-line arguments & call performance audit
 *			with selected options.
 *//*------------------------------------------------------------------------ */
int audit_performances_main(int argc, char *argv[])
{
	int ret;
	int duration = 0, delay = 0;

	if (argc == 0) {
		ret = audit_performances(stdout,
			AUDIT_PERF_DEFAULT_DURATION, AUDIT_PERF_DEFAULT_DELAY);
	} else if (argc == 1) {
		ret = sscanf(argv[0], "%d", &duration);
		if (ret != 1) {
			help(HELP_AUDIT);
			ret = 0;
		}
		ret = audit_performances(stdout,
			(unsigned int) duration, AUDIT_PERF_DEFAULT_DELAY);
	} else if ((argc == 2) && (strcmp(argv[0], "-d") == 0)) {
		ret = sscanf(argv[1], "%d", &delay);
		if (ret != 1) {
			help(HELP_AUDIT);
			ret = 0;
		}
		ret = audit_performances(stdout,
			AUDIT_PERF_DEFAULT_DURATION, (unsigned int) delay);
	} else if ((argc == 3) && (strcmp(argv[1], "-d") == 0)) {
		ret = sscanf(argv[0], "%d", &duration);
		if (ret != 1) {
			help(HELP_AUDIT);
			ret = 0;
		}
		ret = sscanf(argv[2], "%d", &delay);
		if (ret != 1) {
			help(HELP_AUDIT);
			ret = 0;
		}
		ret = audit_performances(stdout,
			(unsigned int) duration, (unsigned int) delay);
	} else {
		help(HELP_AUDIT);
		ret = 0;
	}

	return ret;
}
