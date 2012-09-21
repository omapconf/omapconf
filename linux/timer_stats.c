/*
 *
 * @Component			OMAPCONF
 * @Filename			timer_stats.c
 * @Description			Linux Kernel /proc/timer_stats APIs
 * @Author			Jon Hunter (jon-hunter@ti.com)
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
#include <timer_stats.h>
#include <cpuinfo.h>
#include <string.h>


/* #define TIMERSTATS_DEBUG */
#ifdef TIMERSTATS_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION	timerstats_stop
 * @BRIEF	stop timer statistics collection in the /proc/timer_stats file
 * @RETURNS	0 in case of success
 *		TIMER_ERR_NOT_AVAILABLE
 * @DESCRIPTION	stop timer statistics collection in the /proc/timer_stats file
 *//*------------------------------------------------------------------------ */
int timerstats_stop(void)
{
	FILE *fp;

	/* Open file */
	fp = fopen("/proc/timer_stats", "w");
	if (fp == NULL) {
		dprintf("%s(): cannot open /proc/timer_stats file!\n",
			__func__);
		return TIMER_ERR_NOT_AVAILABLE;
	}

	fprintf(fp, "0\n");
	fclose(fp);

	return 0;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION	timerstats_start
 * @BRIEF	start timer statistics collection in the /proc/timer_stats file
 * @RETURNS	0 in case of success
 *		TIMER_ERR_NOT_AVAILABLE
 * @DESCRIPTION	start timer statistics collection in the /proc/timer_stats file
 *//*------------------------------------------------------------------------ */
int timerstats_start(void)
{
	FILE *fp;

	/* Open file */
	fp = fopen("/proc/timer_stats", "w");
	if (fp == NULL) {
		dprintf("%s(): cannot open /proc/timer_stats file!\n",
			__func__);
		return TIMER_ERR_NOT_AVAILABLE;
	}

	fprintf(fp, "1\n");
	fclose(fp);

	return 0;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION	timerstats_save
 * @BRIEF	save timer statistics in the /proc/timer_stats file
 * @RETURNS	0 in case of success
 *		TIMER_ERR_ARG
 *		TIMER_ERR_NOT_AVAILABLE
 *		TIMER_ERR_UNEXPECTED
 * @param[in,out]	filename: file where statistics are saved
 * @DESCRIPTION	save timer statistics in the /proc/timer_stats file
 *//*------------------------------------------------------------------------ */
int timerstats_save(char *filename)
{
	FILE *from, *to;
	char ch;

	if (filename == NULL) {
		fprintf(stderr, "%s(): output file == NULL!!!\n", __func__);
		return TIMER_ERR_ARG;
	}

	/* Open file */
	from = fopen("/proc/timer_stats", "rb");
	if (from == NULL) {
		dprintf("%s(): cannot open /proc/timer_stats file!\n",
			__func__);
		return TIMER_ERR_NOT_AVAILABLE;
	}

	/* Open destination file */
	to = fopen(filename, "wb");
	if (to == NULL) {
		fprintf(stderr, "%s(): cannot open %s file!\n", __func__,
			filename);
		return TIMER_ERR_ARG;
	}

	/* Copy the file */
	while (!feof(from)) {
		ch = fgetc(from);
		if (ferror(from)) {
			fprintf(stderr, "%s(): error reading "
				"/proc/interrupts file.\n", __func__);
			return TIMER_ERR_UNEXPECTED;
		}
		if (!feof(from))
			fputc(ch, to);
		if (ferror(to)) {
			fprintf(stderr, "%s(): error writing "
				"%s file.\n", __func__, filename);
			return TIMER_ERR_UNEXPECTED;
		}
	}

	/* Close source file */
	if (fclose(from) == EOF) {
		fprintf(stderr, "%s(): error closing /proc/timer_stats file.\n",
			__func__);
		return TIMER_ERR_UNEXPECTED;
	}

	/* Close destination file */
	if (fclose(to) == EOF) {
		fprintf(stderr, "%s(): error closing %s file.\n",
			__func__, filename);
		return TIMER_ERR_UNEXPECTED;
	}

	return 0;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION	timerstats_list_get
 * @BRIEF	parse snapshot of /proc/timer_stats file and fill list
 *		with information about the timer events that occurred
 * @RETURNS	0 in case of success
 *		TIMER_ERR_ARG
 * @param[in,out]	fp: file descriptor of an opened /proc/timer_stats file
 * @param[in,out]	list: generic list where to store timers stats
 * @DESCRIPTION	parse snapshot of /proc/timer_stats file and fill list
 *		with information about the timer events that occurred
 *//*------------------------------------------------------------------------ */
int timerstats_list_get(FILE *fp, genlist *list)
{
	char line[256], count[24];
	unsigned int timer_count;
	timerstat_info inf;
	int len;

	if (fp == NULL) {
		fprintf(stderr, "%s(): fp == NULL!!!\n", __func__);
		return TIMER_ERR_ARG;
	}
	if (list == NULL) {
		fprintf(stderr, "%s(): list == NULL!!!\n", __func__);
		return TIMER_ERR_ARG;
	}

	genlist_init(list);
	timer_count = 0;

	rewind(fp);
	while (fgets(line, sizeof(line), fp) != NULL) {
		dprintf("%s(): line = %s\n", __func__, line);
		if (sscanf(line, "%s %d %s %s (%s",
				&count[0], &inf.pid, &inf.name[0],
				&inf.init_fxn[0], &inf.callback[0]) != 5)
			continue;

		len = strlen(count);
		if (count[len - 2] == 'D') {
			strcpy(&inf.deferrable[0], "YES");
			count[len - 2] = 0;
		} else {
			strcpy(&inf.deferrable[0], "no");
			count[len - 1] = 0;
		}

		inf.count = atoi(&count[0]);

		/* Remove trailing ")" from callback name */
		inf.callback[strlen(&inf.callback[0]) - 1] = 0;

		dprintf("%s(): count=%s, deferrable=%s, pid=%d, name=%s, "
			"start=%s, callback=%s\n",
			__func__, &inf.count, &inf.deferrable, &inf.pid,
			&inf.name, &inf.init_fxn, &inf.callback, len);
		genlist_addtail(list, (void *) &inf, sizeof(timerstat_info));
		timer_count++;
	}
	rewind(fp);

	return timer_count;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION	timerstats_get_summary
 * @BRIEF	parse snapshot of /proc/timer_stats file and extract
 *		summary information and store in a string
 * @RETURNS	0 in case of success
 *		TIMER_ERR_ARG
 * @param[in,out]	fp: file descriptor of an opened /proc/timer_stats file
 * @param[in,out]	summary: pointer to char array where summary is stored
 * @DESCRIPTION	parse snapshot of /proc/timer_stats file and extract
 *		summary information and store in a string
 *//*------------------------------------------------------------------------ */
int timerstats_get_summary(FILE *fp, char *summary)
{
	char line[256];
	char str1[24], str2[24], str3[24], str4[24];
	char sample_period[24], total_events[24], event_freq[24];

	if (fp == NULL) {
		fprintf(stderr, "%s(): fp == NULL!!!\n", __func__);
		return TIMER_ERR_ARG;
	}

	rewind(fp);
	while (fgets(line, sizeof(line), fp) != NULL) {
		dprintf("%s(): line = %s\n", __func__, line);
		sscanf(line, "%s %s %s %s",
			&str1[0], &str2[0], &str3[0], &str4[0]);

		if (!strcmp(&str1[0], "Sample") &&
			!(strcmp(&str2[0], "period:")))
			strcpy(&sample_period[0], &str3[0]);

		if (!strcmp(&str2[0], "total") &&
			!(strcmp(&str3[0], "events,"))) {
			strcpy(&total_events[0], &str1[0]);
			strcpy(&event_freq[0], &str4[0]);
		}
	}
	rewind(fp);

	sprintf(summary, "Timer Statistics Summary: "
		"sample period = %s, total events = %s, events/sec = %s\n",
		&sample_period[0], &total_events[0], &event_freq[0]);

	return 0;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION	timerstats_list_sort
 * @BRIEF	sort list by timer-stats occurrence decreasing order.
 * @RETURNS	0 in case of success
 *		TIMER_ERR_ARG
 *		TIMER_ERR_INTERNAL
 * @param[in,out]	list: populated list of TIMER stats.
 * @DESCRIPTION	sort list by timer-stats occurrence decreasing order.
 *		Use bubble sort algorithm.
 *//*------------------------------------------------------------------------ */
int timerstats_list_sort(genlist *list)
{
	unsigned int i, max, tmpmax;
	timerstat_info inf1, inf2;

	if (list == NULL) {
		fprintf(stderr, "%s(): list = NULL!\n", __func__);
		return TIMER_ERR_ARG;
	}
	max = genlist_getcount(list);

	while (max > 0) {
		tmpmax = 0;
		for (i = 0; i < max - 1; i++) {
			genlist_get(list, i, (timerstat_info *) &inf1);
			genlist_get(list, i + 1, (timerstat_info *) &inf2);
			if (inf1.count < inf2.count) {
				genlist_add(list, (void *) &inf2,
					sizeof(timerstat_info), i);
				genlist_remove(list, i + 2);
				tmpmax = i + 1;
			}
		}
		max = tmpmax;
	}

	return 0;
}
