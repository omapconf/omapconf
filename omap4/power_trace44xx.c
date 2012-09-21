/*
 *
 * @Component			OMAPCONF
 * @Filename			power_trace44xx.c
 * @Description			Collect OMAP4 PRCM PMI Traces in ETB
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


#include <power_trace44xx.h>
#include <pmi44xx.h>
#include <pmi44xx_pwrdm.h>
#include <pmi44xx_voltdm.h>
#include <lib.h>
#include <lib44xx.h>
#include <stdio.h>
#include <autoadjust_table.h>
#include <genlist.h>
#include <help.h>
#include <unistd.h>
#include <cpufreq.h>
#include <emif44xx.h>
#include <clock44xx.h>
#include <cpuinfo.h>
#include <temperature44xx.h>
#include <counters44xx.h>
#include <sci_swcapture.h>


static char etb_raw_trace_file[64] = "etb_trace.txt";
static char pmi_pwrdm_events_trace_file[64] = "pmi_pwrdm_events_trace.log";
static char pwrdm_transitions_file[64] = "pwrdm_transitions.csv";
static char pwrdm_transitions_stats_file[64] = "pwrdm_transitions_stats.txt";
static char pmi44xx_voltdm_trace_file[64] = "voltage_transitions_trace.log";


/* #define POWER_TRACE44XX_DEBUG */
#ifdef POWER_TRACE44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


typedef struct {
	unsigned int count;
	double total; /* in microseconds */
	double min; /* in microseconds */
	double max; /* in microseconds */
	double avg; /* in microseconds */
} time_stats;


/* #define PWRDM_TRANSITIONS_STATS_PROCESS_DEBUG */
#ifdef PWRDM_TRANSITIONS_STATS_PROCESS_DEBUG
#undef dprintf
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#endif
/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm_transitions_stats_process
 * @BRIEF		process power domain transitions statistics
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in]		transitions: power domains transitions list
 * @param[in]		duration: trace duration
 * @param[in, out]	stats: processed transitions statistics
 * @DESCRIPTION		process power domain transitions statistics
 *//*------------------------------------------------------------------------ */
int pwrdm_transitions_stats_process(pwrdm_transitions transitions,
	double duration,
	time_stats stats[OMAP4_PMI_PWRDM_MAX][PWRDM_STATE_MAX])
{
	unsigned int dom, st;
	pwrdm_transition tr;
	int count, evt;
	char *name;
	#ifdef PWRDM_TRANSITIONS_STATS_PROCESS_DEBUG
	char s[6];
	#endif

	CHECK_NULL_ARG(transitions, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(stats, OMAPCONF_ERR_ARG);
	if (duration == 0.0) {
		fprintf(stderr, "omapconf (%s): duration == 0!\n", __func__);
		return OMAPCONF_ERR_ARG;
	}

	/* Init all time statistics */
	for (dom = 0; dom < OMAP4_PMI_PWRDM_MAX; dom++) {
		for (st = 0; st < PWRDM_STATE_MAX; st++) {
			stats[dom][st].count = 0;
			stats[dom][st].total = 0.0;
			stats[dom][st].min = duration;
			stats[dom][st].max = 0.0;
			stats[dom][st].avg = 0.0;
		}
	}

	for (dom = 0; dom < OMAP4_PMI_PWRDM_MAX; dom++) {
		if (dom < OMAP4_PMI_LOGIC_PWRDM_MAX)
			name = (char *) omap4_pmi_logic_pwrdm_names_table[dom];
		else
			name = (char *) omap4_pmi_mem_pwrdm_names_table[dom -
				OMAP4_PMI_LOGIC_PWRDM_MAX];

		dprintf("\n-------- %s --------\n", name);
		if (genlist_isempty(&(transitions[dom])) == 1) {
			printf("List %d (%s) should not be empty!!!\n",
				dom , name);
			return OMAPCONF_ERR_UNEXPECTED;
		}

		/* First element in list is the initial state */
		count = genlist_getcount(&(transitions[dom]));
		for (evt = 0; evt < count; evt++) {
			genlist_get(&(transitions[dom]), evt, &tr);
			#ifdef PWRDM_TRANSITIONS_STATS_PROCESS_DEBUG
			pwrdm_state2string(s, tr.state);
			dprintf("\tState = %s (%d) during %lfus\n",
				s, tr.state, tr.ts);
			#endif

			/* Update time counters accordingly */
			stats[dom][tr.state].count++;
			stats[dom][tr.state].total += tr.ts;
			if (tr.ts < stats[dom][tr.state].min)
				stats[dom][tr.state].min = tr.ts;
			if (tr.ts > stats[dom][tr.state].max)
				stats[dom][tr.state].max = tr.ts;
			if (stats[dom][tr.state].count == 1)
				stats[dom][tr.state].avg = tr.ts;
			else
				stats[dom][tr.state].avg = avg_recalc(
				stats[dom][tr.state].avg,
				tr.ts, stats[dom][tr.state].count - 1);
		}
	}

	return 0;
}
#ifdef PWRDM_TRANSITIONS_STATS_PROCESS_DEBUG
#undef dprintf
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm_transitions_stats_format
 * @BRIEF		format transitions statistics into table
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 * @param[in, out]	stats: power domain transitions statistics
 * @param[in, out]	duration: trace duration
 * @param[in, out]	table: table with formatted statistics
 * @param[in, out]	row: table row number
 * @param[in, out]	col: table column number
 * @DESCRIPTION		format transitions statistics into table
 *//*------------------------------------------------------------------------ */
int pwrdm_transitions_stats_format(
	time_stats stats[OMAP4_PMI_PWRDM_MAX][PWRDM_STATE_MAX],
	double duration,
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN],
	unsigned int *row, unsigned int *col)
{
	unsigned int i, dom, st;
	char *name;

	CHECK_NULL_ARG(stats, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(table, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(row, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(col, OMAPCONF_ERR_ARG);
	if (duration == 0.0) {
		fprintf(stderr, "omapconf (%s): duration == 0!\n", __func__);
		return OMAPCONF_ERR_ARG;
	}

	autoadjust_table_init(table);
	*row = 0;
	snprintf(table[*row][0], TABLE_MAX_ELT_LEN,
		"Trace Duration: %.3lfus", duration);
	strncpy(table[*row][1], "Time in OFF State", TABLE_MAX_ELT_LEN);
	strncpy(table[*row][2], "Time in RET State", TABLE_MAX_ELT_LEN);
	strncpy(table[*row][3], "Time in INACT State", TABLE_MAX_ELT_LEN);
	strncpy(table[*row][4], "Time in ON State", TABLE_MAX_ELT_LEN);
	(*row)++;

	for (i = 0; i < OMAP4_USED_PMI_PWRDMS; i++) {

		dom = sorted_domain_ids[i];
		/*
		 * OMAP4 WORKAROUND:
		 * HW bug in OMAP4 makes CPU[0-1] trace irrelevant ...
		 * => Skip these domains ...
		 */
		if (((sorted_domain_class[i] == PMI_PWRDM_CLASS_LOGIC) &&
				(dom == OMAP4_PMI_LOGIC_PWRDM_A9_C1)) ||
			((sorted_domain_class[i] == PMI_PWRDM_CLASS_LOGIC) &&
				(dom == OMAP4_PMI_LOGIC_PWRDM_A9_C0)) ||
			((sorted_domain_class[i] == PMI_PWRDM_CLASS_MEM) &&
				(dom == OMAP4_PMI_MEM_PWRDM_MPU_M1)) ||
			((sorted_domain_class[i] == PMI_PWRDM_CLASS_MEM) &&
				(dom == OMAP4_PMI_MEM_PWRDM_MPU_M0)))
			continue;

		if (sorted_domain_class[i] == PMI_PWRDM_CLASS_LOGIC) {
			name = (char *) omap4_pmi_logic_pwrdm_names_table[dom];
		} else {
			name = (char *) omap4_pmi_mem_pwrdm_names_table[dom];
			dom += OMAP4_PMI_LOGIC_PWRDM_MAX;
		}

		snprintf(table[*row][0], TABLE_MAX_ELT_LEN, "  %s", name);
		(*row)++;

		for (st = 0; st < PWRDM_STATE_MAX; st++) {
			strncpy(table[*row][0],
				"    # of Time(s) Entered", TABLE_MAX_ELT_LEN);
			strncpy(table[*row + 1][0],
				"    Total Time in State", TABLE_MAX_ELT_LEN);
			strncpy(table[*row + 2][0],
				"    Min  Time in State", TABLE_MAX_ELT_LEN);
			strncpy(table[*row + 3][0],
				"    Max  Time in State", TABLE_MAX_ELT_LEN);
			strncpy(table[*row + 4][0],
				"    Average Time in State", TABLE_MAX_ELT_LEN);
			if (stats[dom][st].count == 0)
				continue;
			snprintf(table[*row][st + 1],
				TABLE_MAX_ELT_LEN, "%d", stats[dom][st].count);
			snprintf(table[*row + 1][st + 1],
				TABLE_MAX_ELT_LEN, "%.3lfus (%.2lf%%)",
				stats[dom][st].total,
				((stats[dom][st].total / duration) * 100.0));
			snprintf(table[*row + 2][st + 1],
				TABLE_MAX_ELT_LEN, "%.3lfus",
				stats[dom][st].min);
			snprintf(table[*row + 3][st + 1],
				TABLE_MAX_ELT_LEN, "%.3lfus",
				stats[dom][st].max);
			snprintf(table[*row + 4][st + 1],
				TABLE_MAX_ELT_LEN, "%.3lfus",
				stats[dom][st].avg);
		}
		(*row) += 6;
	}

	*col = 5;
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm_transitions_stats_save
 * @BRIEF		save power domain transitions stats into file
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in, out]	filename: name of the file where to save power
 *			transitions stats
 * @param[in, out]	table: table with formatted statistics
 * @param[in]		row: table row number
 * @param[in]		col: table column number
 * @DESCRIPTION		save power domain transitions stats into file
 *//*------------------------------------------------------------------------ */
int pwrdm_transitions_stats_save(char *filename,
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN],
	unsigned int row, unsigned int col)
{
	FILE *fp = NULL;
	int ret;

	CHECK_NULL_ARG(table, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(filename, OMAPCONF_ERR_ARG);

	fp = fopen(filename, "w");
	if (fp == NULL) {
		printf(
			"pwrdm_transitions_stats_save() error: could not open %s!\n",
			filename);
		return OMAPCONF_ERR_UNEXPECTED;
	}
	fprintf(fp,
		"OMAP4 Low-Power Modes Usage Statistics based on PMI Power Domains Transitions Trace:\n\n");
	fprintf(fp, "NB: CPU[0-1] stats not reported due to OMAP4 HW bugs.\n");
	fprintf(fp,
		"WARNING: State RET may report either CSWRET or OSWRET. OMAP4 PMI trace does not capture this information.\n\n");
	ret = autoadjust_table_fprint(fp, table, row, col);
	fclose(fp);

	return ret;
}


/* #define TRACE44XX_PWRDM_DEBUG */
#ifdef TRACE44XX_PWRDM_DEBUG
#undef dprintf
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#endif
/* #define SKIP_PMI_PWRDM_CAPTURE */
/* #define SKIP_PMI_PWRDM_DECODE */
/* ------------------------------------------------------------------------*//**
 * @FUNCTION		trace44xx_pwrdm
 * @BRIEF		capture and decode power domain transitions trace
 *			using PMI
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in]		duration: capture (trace) duration
 * @DESCRIPTION		capture and decode power domain transitions trace
 *			using PMI
 *//*------------------------------------------------------------------------ */
int trace44xx_pwrdm(unsigned int duration)
{
	int ret;
	pwrdm_transitions transitions;
	double trace_duration;
	time_stats stats[OMAP4_PMI_PWRDM_MAX][PWRDM_STATE_MAX];
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int dom, row, col;
	genlist pm_events;
	opp44xx_id vddcore_opp;

	ret = voltdm44xx_get_opp(OMAP4_VDD_CORE, &vddcore_opp);
	if (ret != 0)
		fprintf(stderr,
			"%s(): warning OMAP4_VDD_CORE OPP not detected!!! (%d)\n",
			__func__, ret);
#ifndef SKIP_PMI_PWRDM_CAPTURE
	ret = pmi44xx_trace_capture(PMI_EVENT_PWRDM_TRANSITION, duration,
		OMAP44XX_UART_TIMEOUT, etb_raw_trace_file);
	if (ret <= 0)
		return ret;
#endif

#ifndef SKIP_PMI_PWRDM_DECODE
	printf("Trace collected, processing it ...\n");
	/* Decode STP PMI Trace */
	ret = pmi44xx_trace_decode(etb_raw_trace_file, 1,
		pmi_pwrdm_events_trace_file, &trace_duration, vddcore_opp);
	if (ret <= 0) {
		switch (ret) {
		case 0:
			printf(
				"No power transition happened during capture, is power management really enabled?!\n\n");
			return 0;
		case OMAPCONF_ERR_TRUNCATED:
			printf(
				"Warning: ETB buffer overflow detected, trace truncated.\n");
			break;
		case OMAPCONF_ERR_CORRUPTED:
			printf("Error: trace got corrupted!\n\n");
			return OMAPCONF_ERR_UNEXPECTED;
		case OMAPCONF_ERR_EMPTY:
			printf("Error: trace file empty!\n\n");
			return OMAPCONF_ERR_UNEXPECTED;
		default:
			printf("Unexpected error during decode!\n\n");
			return OMAPCONF_ERR_UNEXPECTED;
		}
	}

	/* Extract power events from PMI trace */
	ret = pmi_pwrdm_events_get(pmi_pwrdm_events_trace_file, &pm_events);
	if (ret == 0) {
		printf("No power event found in PMI trace.\n\n");
		return 0;
	} else if (ret < 0) {
		printf("Unexpected error during extraction!\n\n");
		return OMAPCONF_ERR_UNEXPECTED;
	}
	dprintf("%d PM events extracted from trace.\n", ret);


	/* Extract individual power domain transitions from pm events */
	ret = pmi_pwrdm_transitions_find(&pm_events, trace_duration,
		transitions);
	genlist_free(&pm_events);
	if (ret == 0) {
		printf("No power domain transition found in PMI trace!\n\n");
		return 0;
	} else if (ret < 0) {
		printf(
			"Unexpected error during power domain transition extraction!\n\n");
		return OMAPCONF_ERR_UNEXPECTED;
	}
	printf("%d power domain transitions found in trace.\n", ret);


	/* Save transitions into file */
	ret = pmi_pwrdm_transitions_save(pwrdm_transitions_file,
		transitions, trace_duration);
	if (ret < 0) {
		printf("Unexpected error while saving pwrdm transitions!\n\n");
		return OMAPCONF_ERR_UNEXPECTED;
	}
	dprintf("PMI pwrdm transitions saved.\n");


	/* Compute transition statistics */
	ret = pwrdm_transitions_stats_process(transitions, trace_duration,
		stats);
	if (ret < 0) {
		printf(
			"Unexpected error while processing pwrdm transitions!\n\n");
		return OMAPCONF_ERR_UNEXPECTED;
	}
	dprintf("PMI pwrdm transitions processed.\n");


	/* Format transition statistics */
	ret = pwrdm_transitions_stats_format(stats, trace_duration,
		table, &row, &col);
	if (ret < 0) {
		printf(
			"Unexpected error while formatting power transitions stats!\n\n");
		return OMAPCONF_ERR_UNEXPECTED;
	}
	dprintf("Power transitions formatted.\n");
	printf("Trace processing done.\n");

	/* Save transition statistics into file */
	ret = pwrdm_transitions_stats_save(pwrdm_transitions_stats_file,
		table, row, col);
	if (ret < 0) {
		printf(
			"Unexpected error while saving power transitions stats!\n\n");
		return OMAPCONF_ERR_UNEXPECTED;
	}
	printf("Low-Power modes usage statistics saved into files.\n");

	for (dom = 0; dom < OMAP4_PMI_PWRDM_MAX; dom++)
		genlist_free(&(transitions[dom]));

	printf("\nPlease refer to file:\n");
	#ifdef TRACE44XX_PWRDM_DEBUG
	printf("  \"%s\" for RAW ETB trace.\n", etb_raw_trace_file);
	printf("  \"%s\" for PMI power domain events trace decoding log.\n",
		pmi_pwrdm_events_trace_file);
	#endif
	printf("  \"%s\" for power domains transitions trace in CSV format.\n",
		pwrdm_transitions_file);
	printf("  \"%s\" for power domains transitions statistics\n",
		pwrdm_transitions_stats_file);
	printf("    (i.e. min/max/avg/total/count).\n\n");
#endif
	return 0;

}
#ifdef TRACE44XX_PWRDM_DEBUG
#undef dprintf
#define dprintf(format, ...)
#endif


/* #define TRACE44XX_OPP_DEBUG */
#ifdef TRACE44XX_OPP_DEBUG
#undef dprintf
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#endif
/* #define SKIP_PMI_OPP_CAPTURE */
/* #define SKIP_PMI_OPP_DECODE */

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		trace44xx_opp
 * @BRIEF		capture and decode PMI voltage domain transitions trace
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in]		capture_time: capture (trace) duration
 * @DESCRIPTION		capture and decode PMI voltage domain transitions trace
 *//*------------------------------------------------------------------------ */
int trace44xx_opp(unsigned int capture_time)
{
	int ret;
	double trace_duration;
	genlist transitions;
	opp44xx_id vddcore_opp;

	if (capture_time == 0) {
		fprintf(stderr,
			"%s(): incorrect capture_time entered! (0 sec)!\n\n",
			__func__);
		return OMAPCONF_ERR_ARG;
	}

	ret = voltdm44xx_get_opp(OMAP4_VDD_CORE, &vddcore_opp);
	if (ret != 0)
		fprintf(stderr,
			"%s(): warning OMAP4_VDD_CORE OPP not detected!!! (%d)\n",
			__func__, ret);
#ifndef SKIP_PMI_OPP_CAPTURE
	ret = pmi44xx_trace_capture(PMI_EVENT_VOLTDM_OPP_CHANGE, capture_time,
		0, etb_raw_trace_file);
	if (ret <= 0)
		return ret;
#endif

#ifndef SKIP_PMI_OPP_DECODE
	printf("Trace collected, processing it ...\n");
	/* Decode STP PMI Trace */
	ret = pmi44xx_trace_decode(etb_raw_trace_file, 1,
		pmi44xx_voltdm_trace_file, &trace_duration, vddcore_opp);
	if (ret <= 0) {
		switch (ret) {
		case 0:
			printf(
				"Empty trace. No voltage transition happened during capture?!\n\n");
			return 0;
		case OMAPCONF_ERR_TRUNCATED:
			printf(
				"Warning: ETB buffer overflow detected, trace truncated.\n");
			break;
		case OMAPCONF_ERR_CORRUPTED:
			printf("Error: trace got corrupted!\n\n");
			return OMAPCONF_ERR_UNEXPECTED;
		case OMAPCONF_ERR_EMPTY:
			printf("Error: trace file empty!\n\n");
			return OMAPCONF_ERR_UNEXPECTED;
		default:
			printf("Unexpected error during decode!\n\n");
			return OMAPCONF_ERR_UNEXPECTED;
		}
	}

	/* Extract events from trace */
	ret = pmi44xx_voltdm_transitions_extract(pmi44xx_voltdm_trace_file,
		&transitions);
	if (ret == 0) {
		printf("No voltage transition event found.\n\n");
		return 0;
	} else if (ret < 0) {
		printf("Unexpected error during extraction!\n\n");
		return OMAPCONF_ERR_UNEXPECTED;
	}
	printf("%d voltage transition events extracted from trace.\n", ret);

	/* Save transitions into file */
	ret = pmi44xx_voltdm_transitions_save(&transitions, trace_duration);
	genlist_free(&transitions);
	if (ret < 0) {
		printf(
			"Unexpected error while saving voltage transitions!\n\n");
		return OMAPCONF_ERR_UNEXPECTED;
	}
#endif

	return 0;
}
#ifdef TRACE44XX_OPP_DEBUG
#undef dprintf
#define dprintf(format, ...)
#endif
