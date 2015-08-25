/*
 *
 * @Component			OMAPCONF
 * @Filename			counters44xx.c
 * @Description			Collect data from PL310 L2 Cache Counters
 * @Author			Steve Korson (s-korson@ti.com)
 * @Date			2012
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


#include <counters44xx.h>
#include <lib.h>
#include <lib44xx.h>
#include <mem.h>
#include <stdio.h>
#include <autoadjust_table.h>
#include <help.h>
#include <help44xx.h>
#include <unistd.h>
#include <cpufreq.h>
#include <emif44xx.h>
#include <clock44xx.h>
#include <cpuinfo.h>
#include <mpuss44xx.h>
#include <timr44xx.h>
#include <l2cc44xx.h>


/* #define OMAP4CONF_COUNTERS_DEBUG */
#ifdef OMAP4CONF_COUNTERS_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


#define PERF_TRACE_SAMPLING_RATE_MS 		100 /* ms */


typedef struct {
	unsigned int count;
	double total; /* in microseconds */
	double min; /* in microseconds */
	double max; /* in microseconds */
	double avg; /* in microseconds */
} time_stats;


static char file_prefix[64] = "omap_performance_";
static char trace_perf_file[64] = "trace.dat";
static char trace_perf_stats_file[64] =	"stats.txt";

int sampling_rate = PERF_TRACE_SAMPLING_RATE_MS;

/*
// skorson
// Assigning a default like this is not preferable, but doing so
// makes it backward compatible for the trace perf option
// Leave signed, set -1 to represent disabled or unused.
// The state can contain any positive value to indicate enabled and the value.
*/
static int trace_state[TRACE_CFG_TABLE_MAX] = {
	 1, /* TRACE_CFG_TIMER_32K_SYNC - Default to enable timestamp */
	-1, /* TRACE_CFG_L2CC_CNT0_FILTER, */
	-1, /* TRACE_CFG_L2CC_CNT1_FILTER, */
	-1, /* TRACE_CFG_EMIF0_CNT0_FILTER, */
	-1, /* TRACE_CFG_EMIF1_CNT0_FILTER, */
	EMIF44XX_PERF_CNT_FILTER_DATA_TRANSFER_CYCLES, /*TRACE_CFG_EMIF0_CNT1_FILTER, */
	EMIF44XX_PERF_CNT_FILTER_DATA_TRANSFER_CYCLES, /*TRACE_CFG_EMIF1_CNT1_FILTER, */
	-1, /* TRACE_CFG_EMIF0_MCLK_CYCLES, */
	-1, /* TRACE_CFG_EMIF1_MCLK_CYCLES, */
	-1, /* TRACE_CFG_ENABLED_OPTIONS_MAX, */
/* Options that don't require data storage (i.e. options for env. or */
/* other control of a traced option.) beyond this point.  */
	-1, /* TRACE_CFG_EMIF0_CNT0_ID, */
	-1, /* TRACE_CFG_EMIF1_CNT0_ID, */
	-1, /* TRACE_CFG_EMIF0_CNT1_ID, */
	-1, /* TRACE_CFG_EMIF1_CNT1_ID, */
	-1, /* TRACE_CFG_EMIF0_CNT0_ADDRSPACE, */
	-1, /* TRACE_CFG_EMIF1_CNT0_ADDRSPACE, */
	-1, /* TRACE_CFG_EMIF0_CNT1_ADDRSPACE, */
	-1, /* TRACE_CFG_EMIF1_CNT1_ADDRSPACE, */
	-1, /* TRACE_CFG_SAMPLE_INTERVAL // State option unused */
	-1, /* TRACE_CFG_NORMALIZE // State option unused */
	-1, /* TRACE_CFG_FILE_PREFIX // State option unused */
	-1  /* TRACE_CFG_LONG_HEADER // State option used in if clause before printing */
	};


static unsigned int capture_time = 10;
char defaults_file[64] = ".omapconf_defaults";



#ifdef OMAP4CONF_COUNTERS_DEBUG
#undef dprintf
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#endif
/**
 * Function: counters44xx_perf
 * Role: trace OMAP performance (CPU Load, OPP & memory bandwidth usage).
 * Parameters:
 *	capture_time: capture (trace) duration
 * Return:
 *	0 in case of success
 *	OMAPCONF_ERR_ARG
 *	OMAPCONF_ERR_NOT_AVAILABLE
 *	OMAPCONF_ERR_UNEXPECTED
 */
int counters44xx_count(unsigned int capture_time)
{

	unsigned int i;
	unsigned int sample_cnt;
	int ret;
	unsigned int addr, data, l2_disabled_prior = 0;
	unsigned int *trace_buf[TRACE_CFG_ENABLED_OPTIONS_MAX];
	unsigned short emif;
	unsigned int sample;
	FILE *fp = NULL;
	char s[16];
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row = 0;
	char name[64];
	char tmp_name[64];
	char option[64];
	unsigned int temp, avg, min, max;


	/* Configure EMIF counters */
	ret = 0;
	if (trace_state[TRACE_CFG_EMIF0_CNT0_FILTER] >= 0)
		ret = emif44xx_perf_cnt_configure(EMIF44XX_0, 0,
			trace_state[TRACE_CFG_EMIF0_CNT0_FILTER],
			trace_state[TRACE_CFG_EMIF0_CNT0_ID],
			trace_state[TRACE_CFG_EMIF0_CNT0_ADDRSPACE]);
	if (trace_state[TRACE_CFG_EMIF1_CNT0_FILTER] >= 0)
		ret |= emif44xx_perf_cnt_configure(EMIF44XX_1, 0,
			trace_state[TRACE_CFG_EMIF1_CNT0_FILTER],
			trace_state[TRACE_CFG_EMIF1_CNT0_ID],
			trace_state[TRACE_CFG_EMIF1_CNT0_ADDRSPACE]);
	if (trace_state[TRACE_CFG_EMIF0_CNT1_FILTER] >= 0)
		ret |= emif44xx_perf_cnt_configure(EMIF44XX_0, 1,
			trace_state[TRACE_CFG_EMIF0_CNT1_FILTER],
			trace_state[TRACE_CFG_EMIF0_CNT1_ID],
			trace_state[TRACE_CFG_EMIF0_CNT1_ADDRSPACE]);
	if (trace_state[TRACE_CFG_EMIF1_CNT1_FILTER] >= 0)
		ret |= emif44xx_perf_cnt_configure(EMIF44XX_1, 1,
			trace_state[TRACE_CFG_EMIF1_CNT1_FILTER],
			trace_state[TRACE_CFG_EMIF1_CNT1_ID],
			trace_state[TRACE_CFG_EMIF1_CNT1_ADDRSPACE]);

	if (ret != 0) {
		fprintf(stderr, "%s(): error while configuring EMIF perf. "
			"counters!\n", __func__);
		ret = OMAPCONF_ERR_NOT_AVAILABLE;
		goto counters44xx_count_err;
	}

	/* Configure L2CC counters */
	/* Do this regardless whether enabled or disabled (at this point.) */
	if (trace_state[TRACE_CFG_L2CC_CNT0_FILTER] >= 0)
		ret = l2cc44xx_perf_cnt_configure(0, trace_state[TRACE_CFG_L2CC_CNT0_FILTER], 1); /* for last entry, should use boolean 'true' */
	if (trace_state[TRACE_CFG_L2CC_CNT1_FILTER] >= 0)
		ret = l2cc44xx_perf_cnt_configure(1, trace_state[TRACE_CFG_L2CC_CNT1_FILTER], 1); /* for last entry, should use boolean 'true' */

/*
//	if (ret != 0) {
//		fprintf(stderr, "%s(): error while configuring L2CC perf. "
//			"counters!\n", __func__);
//		ret = OMAPCONF_ERR_NOT_AVAILABLE;
//		goto counters44xx_count_err;
//		}
*/

	/* Allocate buffer to store sampled data, unless continuous capture is enabled */
	if (capture_time > 0) {
		if (sampling_rate > 0) {
			sample_cnt = 1 + ((capture_time * 1000) / sampling_rate);
		} else {
	/* If smaple rate of 0, trace as fast as possible for the capture time. */
			sample_cnt = 1 + ((capture_time * 1000));
		}
	} else {
		/* Hack. If capture_time == 0, capture continuous. Need room for at least 2 samples. */
		sample_cnt = 2;

		if (trace_state[TRACE_CFG_LONG_HEADER] == 1) {
			printf("#\n");
			printf("# ----------------- OMAP4430 Performance Trace+ ----------"
				"--------------------------------------------------------------"
				"-----\n");
			printf("#\n");
		/*	printf("# NB:\n"); */
			printf("#   * This is an intrusive trace (counters polling).\n");
			printf("#     Idle C-States usage was altered.\n");
			printf("#     Limted additional CPU & EMIFs loads generated.\n");
			printf("#\n");
		/*	printf("#   * If CPU1 Load = -5.0, it means CPU1 is OFFLINE.\n"); */
		/*	printf("#\n"); */
		/*	printf("#   * CPU LOADS CANNOT be directly converted to Mhz.\n"); */
		/*	printf("#     OPP may have changed during the audit.\n"); */
		/*	printf("#\n"); */
			printf("# ----------------------- Trace FORMAT -------------------"
				"--------------------------------------------------------------"
				"-----\n");
			printf("#\n");
			printf("# Trace Length: %us\n", capture_time);
			printf("#\n");
			printf("# Trace Sampling Rate: %ums\n",
				sampling_rate);
			printf("#\n");

			printf("# Number of samples: %u\n", sample_cnt - 1);
			printf("#\n");
			printf("# %10.10s ", "Timestamp(s)");
		};
		for (i = 0; i < TRACE_CFG_ENABLED_OPTIONS_MAX; i++) {
			if (trace_state[i] >= 0) {/* Traces state is enabled if non-zero state value. */
				ret = value2name(i, name, trace_config_options_table);
				printf("\t%10.10s", name);
				switch (i) {
				case TRACE_CFG_EMIF0_CNT0_FILTER:
				case TRACE_CFG_EMIF1_CNT0_FILTER:
				case TRACE_CFG_EMIF0_CNT1_FILTER:
				case TRACE_CFG_EMIF1_CNT1_FILTER:
					ret = value2name(trace_state[i], name, emif_event_counters);
					ret = snprintf(tmp_name, 64, "%s%s", ".", name);
					ret = snprintf(name, 64, "%s", tmp_name);
					break;
				case TRACE_CFG_L2CC_CNT0_FILTER:
				case TRACE_CFG_L2CC_CNT1_FILTER:
					ret = value2name(trace_state[i], name, l2cc_event_counters_table);
					ret = snprintf(tmp_name, 64, "%s%s", ".", name);
					ret = snprintf(name, 64, "%s", tmp_name);
					break;
				default:
					strcpy(name, " ");
					break;
				} /* end switch */
				printf("%s ", name);
			}
		}
		printf("\n");

		if (trace_state[TRACE_CFG_LONG_HEADER] == 1) {
			printf("#\n");
			printf("# ----------------------- Trace START --------------------"
				"--------------------------------------------------------------"
				"-----\n");
		}
	}

	dprintf("%s(): capture_time=%us, sample_cnt=%u\n", __func__,
		capture_time, sample_cnt);


	for (i = 0; i < TRACE_CFG_ENABLED_OPTIONS_MAX; i++) {
		if (trace_state[i] >= 0) {/* Traces state is enabled if non-zero state value. */
			/* Add three sample entries to hold min, avg, max */
			trace_buf[i] = malloc((sample_cnt+3) * sizeof(unsigned int));
			if (trace_buf[i] == NULL) {
				ret = value2name(i, name, trace_config_options_table);
				fprintf(stderr, "%s(): could not allocate %s!\n",
					__func__, name);
				ret = OMAPCONF_ERR_NOT_AVAILABLE;
				goto counters44xx_count_err;
			}
		}
	} /* end for i < TRACE_CFG_ENABLED_OPTIONS_MAX */

	/* Enable L2CC counters */
	ret = l2cc44xx_perf_cnt_enable();


	/* Sample performance indicators periodically */
	printf("\n");

	printf("Sampling OMAP Counters for %us, please wait...\n",
		capture_time);


	for (sample = 0; sample < sample_cnt; sample++) {

/*
		// This could be a big for loop and 'switch' statemenet...
		// Get CPU runtime execution stats
		// Get EMIF cnt0, cnt1 & total mclk cycle counts as enabled
		// skorson
		// Being lazy and doing these two one after the other. I suppose code could be written
		// to convert a for 0 to 1 loop but with only two, this is OK.
*/


		emif = 0;
		if (trace_state[TRACE_CFG_EMIF0_CNT0_FILTER] >= 0) {
			trace_buf[TRACE_CFG_EMIF0_CNT0_FILTER][sample] = emif44xx_perf_cnt_get_count(
				emif, EMIF44XX_PERF_CNT_0);
			dprintf("%s(): EMIF0 counter 0 value=%u\n", __func__,
				trace_buf[TRACE_CFG_EMIF0_CNT0_FILTER][sample]);
		}
		if (trace_state[TRACE_CFG_EMIF0_CNT1_FILTER] >= 0) {
			trace_buf[TRACE_CFG_EMIF0_CNT1_FILTER][sample] = emif44xx_perf_cnt_get_count(
				emif, EMIF44XX_PERF_CNT_1);
			dprintf("%s(): EMIF0 counter 1 value=%u\n", __func__,
				trace_buf[TRACE_CFG_EMIF0_CNT1_FILTER][sample]);
		}

		if (trace_state[TRACE_CFG_EMIF0_MCLK_CYCLES] >= 0) {
			trace_buf[TRACE_CFG_EMIF0_MCLK_CYCLES][sample] = emif44xx_perf_cnt_get_time(emif);
		}

		emif = 1;
		if (trace_state[TRACE_CFG_EMIF1_CNT0_FILTER] >= 0) {
			trace_buf[TRACE_CFG_EMIF1_CNT0_FILTER][sample] = emif44xx_perf_cnt_get_count(
				emif, EMIF44XX_PERF_CNT_0);
			dprintf("%s(): EMIF1 counter 0 value=%u\n", __func__,
				trace_buf[TRACE_CFG_EMIF1_CNT0_FILTER][sample]);
		}
		if (trace_state[TRACE_CFG_EMIF1_CNT1_FILTER] >= 0) {
			trace_buf[TRACE_CFG_EMIF1_CNT1_FILTER][sample] = emif44xx_perf_cnt_get_count(
				emif, EMIF44XX_PERF_CNT_1);
			dprintf("%s(): EMIF1 counter 1 value=%u\n", __func__,
				trace_buf[TRACE_CFG_EMIF1_CNT1_FILTER][sample]);
		}

		if (trace_state[TRACE_CFG_EMIF1_MCLK_CYCLES] >= 0) {
			trace_buf[TRACE_CFG_EMIF1_MCLK_CYCLES][sample] = emif44xx_perf_cnt_get_time(emif);
			dprintf("%s(): EMIF1 MCLK cycles=%u\n", __func__,
				trace_buf[TRACE_CFG_EMIF1_MCLK_CYCLES][sample]);
		}


/*
// FIXME: There is a bug where the L2 Counters are being disabled. Until this is known, enable the following
// block to determine if the counter has been disabled during a run. Print appropriate ERROR to screen...
*/
		if ((trace_state[TRACE_CFG_L2CC_CNT0_FILTER] >= 0) || (trace_state[TRACE_CFG_L2CC_CNT1_FILTER] >= 0))  {


			/* check if counter is still enabled.... */
			ret = name2addr("EVENT_COUNTER_CONTROL", &addr,
				(reg_table *) omap4_mpuss_pl310_reg_table);
			ret = mem_read(addr, &data);
			dprintf("EVENT COUNTER VALUE: 0x%x 0x%x\n", addr, data);
			if (ret != 0) {
				fprintf(stderr, "%s(): error reading L2CC (PL310) EVENT_COUNTER_CONTROL reg!\n",
				__func__);
				return OMAPCONF_ERR_REG_ACCESS;
			}
			if (data == 0  && l2_disabled_prior == 0) {
				l2_disabled_prior = 1;
				fprintf(stderr, "%s(): WARNING:L2CC (PL310) EVENT_COUNTER_CONTROL was DISABLED during a run!!!\n",
				__func__);
				fprintf(stderr, "%s(): WARNING:  Counter values will be invalid (zero) after this point.\n",
				__func__);
			}
		}

/* END FIXME */



		if (trace_state[TRACE_CFG_L2CC_CNT0_FILTER] >= 0) {
			trace_buf[TRACE_CFG_L2CC_CNT0_FILTER][sample] =
				(unsigned int) l2cc44xx_get_perf_cnt(0);
			dprintf("%s(): l2_event_cnt[0] sample %d = 0x%x %d\n", __func__, sample,
				trace_buf[TRACE_CFG_L2CC_CNT0_FILTER][sample], trace_buf[TRACE_CFG_L2CC_CNT0_FILTER][sample]);
		}
		if (trace_state[TRACE_CFG_L2CC_CNT1_FILTER] >= 0) {
			trace_buf[TRACE_CFG_L2CC_CNT1_FILTER][sample] =
				(unsigned int) l2cc44xx_get_perf_cnt(1);
			dprintf("%s(): l2_event_cnt[1] sample %d = 0x%x %d\n", __func__, sample,
				trace_buf[TRACE_CFG_L2CC_CNT1_FILTER][sample], trace_buf[TRACE_CFG_L2CC_CNT1_FILTER][sample]);
		}

		if (trace_state[TRACE_CFG_TIMER_32K_SYNC] >= 0) {
			addr = T32KSYNCNT_CR;
			ret = mem_read(addr, &data);
			trace_buf[TRACE_CFG_TIMER_32K_SYNC][sample] = data;
			dprintf("%s(): 32K CLK cycles=%u\n", __func__,
				trace_buf[TRACE_CFG_TIMER_32K_SYNC][sample]);
		}
		dprintf("\n");
		/* Sleep for some [minimum] time before sampling again */



		if ((capture_time == 0) && (sample > 0)) {
			/* Save timestamp */
			printf("[unix time stamp here]");
			for (i = 0; i < TRACE_CFG_ENABLED_OPTIONS_MAX; i++) {
				if (trace_state[i] >= 0) {
					sprintf(s, "%u", count32_delta(trace_buf[i][0],
					trace_buf[i][1]));
					printf("\t%10.10s", s);
				} /* if state >= 0 */
			} /* for i to TRACE_CFG_ENABLED_OPTIONS_MAX */
			printf("\n");

			/* Now move sample[1] to sample[0] */
			for (i = 0; i < TRACE_CFG_ENABLED_OPTIONS_MAX; i++) {
				if (trace_state[i] >= 0) {
					trace_buf[i][0] = trace_buf[i][1];
				} /* if state >= 0 */
			} /* for i to TRACE_CFG_ENABLED_OPTIONS_MAX */
			sample = 0;
		}

		/* SLeep onyl if a sampling rate is set. */
		/* Sampling rate of 0 is as fast as possible... */
		if (sampling_rate > 0)
			usleep(sampling_rate * 1000);
	}

	/* Disable L2CC counters */
	/* Do regardless of whether enabled for tracing or not. */
	ret = l2cc44xx_perf_cnt_disable();

	printf("Sampling done, processing and saving data...\n");

	/* Open trace output file */
	fp = workdir_fopen(trace_perf_file, "w");
	if (fp == NULL) {
		fprintf(stderr, "%s(): could not create %s!\n",
			__func__, trace_perf_file);
		ret = OMAPCONF_ERR_NOT_AVAILABLE;
		goto counters44xx_count_err;
	}

	dprintf("INFO: TRACE_CFG_LONG_HEADER %d\n", trace_state[TRACE_CFG_LONG_HEADER]);

	if (trace_state[TRACE_CFG_LONG_HEADER] == 1) {
		fprintf(fp, "#\n");
		fprintf(fp, "# ----------------- OMAP4430 Performance Trace+ ----------"
			"--------------------------------------------------------------"
			"-----\n");
		fprintf(fp, "#\n");
	/*	fprintf(fp, "# NB:\n"); */
		fprintf(fp, "#   * This is an intrusive trace (counters polling).\n");
		fprintf(fp, "#     Idle C-States usage was altered.\n");
		fprintf(fp, "#     Limted additional CPU & EMIFs loads generated.\n");
		fprintf(fp, "#\n");
	/*	fprintf(fp, "#   * If CPU1 Load = -5.0, it means CPU1 is OFFLINE.\n"); */
	/*	fprintf(fp, "#\n"); */
	/*	fprintf(fp, "#   * CPU LOADS CANNOT be directly converted to Mhz.\n"); */
	/*	fprintf(fp, "#     OPP may have changed during the audit.\n"); */
	/*	fprintf(fp, "#\n"); */
		fprintf(fp, "# ----------------------- Trace FORMAT -------------------"
			"--------------------------------------------------------------"
			"-----\n");
		fprintf(fp, "#\n");
		fprintf(fp, "# Trace Length: %us\n", capture_time);
		fprintf(fp, "#\n");
		fprintf(fp, "# Trace Sampling Rate: %ums\n",
			sampling_rate);
		fprintf(fp, "#\n");

		fprintf(fp, "# Number of samples: %u\n", sample_cnt - 1);
		fprintf(fp, "#\n");
		fprintf(fp, "# %10.10s ", "Timestamp(s)");
	};

	for (i = 0; i < TRACE_CFG_ENABLED_OPTIONS_MAX; i++) {
		if (trace_state[i] >= 0) {/* Traces state is enabled if non-zero state value. */
			ret = value2name(i, name, trace_config_options_table);
			fprintf(fp, "\t%10.10s", name);
			switch (i) {
			case TRACE_CFG_EMIF0_CNT0_FILTER:
			case TRACE_CFG_EMIF1_CNT0_FILTER:
			case TRACE_CFG_EMIF0_CNT1_FILTER:
			case TRACE_CFG_EMIF1_CNT1_FILTER:
				ret = value2name(trace_state[i], name, emif_event_counters);
				ret = snprintf(tmp_name, 64, "%s%s", ".", name);
				ret = snprintf(name, 64, "%s", tmp_name);
				break;
			case TRACE_CFG_L2CC_CNT0_FILTER:
			case TRACE_CFG_L2CC_CNT1_FILTER:
				ret = value2name(trace_state[i], name, l2cc_event_counters_table);
				ret = snprintf(tmp_name, 64, "%s%s", ".", name);
				ret = snprintf(name, 64, "%s", tmp_name);
				break;
			default:
				strcpy(name, " ");
				break;
			} /* end switch */
			fprintf(fp, "%s ", name);
		}
	}
	fprintf(fp, "\n");
	if (trace_state[TRACE_CFG_LONG_HEADER] == 1) {
		fprintf(fp, "#\n");
		fprintf(fp, "# ----------------------- Trace START --------------------"
			"--------------------------------------------------------------"
			"-----\n");
	}
	dprintf ("I'm here 0\n");

	/* Note: dropping first sample (or using it to normalize data to 0) */
	for (sample = 1; sample < sample_cnt; sample++) {
		if (sampling_rate > 0) {
		/* Save timestamp */
		sprintf(s, "%.3lf", (double)
			(sample * sampling_rate) / 1000.0);
		fprintf(fp, "%10.10s", s);
		} else {
		  sprintf(s, "%.3lf", (double)
			(sample));
		fprintf(fp, "%10.10s", s);
		}

		dprintf ("I'm here 1.%d\n", sample);

		for (i = 0; i < TRACE_CFG_ENABLED_OPTIONS_MAX; i++) {
			if (trace_state[i] >= 0) {

/*
// For now, treating this timer as a counter - its easier to perform calculations
// (std. dev, mean, error etc.)
//				if (	i == TRACE_CFG_TIMER_32K_SYNC ) {
//					// These don't need offset adjusted like counters
//					sprintf(s, "%u", count32_delta(trace_buf[i][0],
//						trace_buf[i][sample]) );
//					fprintf(fp, "\t%10.10s", s);
//					continue;
//				}
*/

				dprintf("INFO: Current Sample %d Value %d Previous %d\n",
					sample, trace_buf[i][sample], trace_buf[i][sample - 1]);

				sprintf(s, "%u",
					count32_delta(trace_buf[i][sample - 1],
					trace_buf[i][sample]));
				fprintf(fp, "\t%10.10s", s);
			} /* if state >= 0 */
		} /* for i to TRACE_CFG_ENABLED_OPTIONS_MAX */

		dprintf ("I'm here 2\n");
		fprintf(fp, "\n");
	} /* for sample < sample_cnt */

	if (trace_state[TRACE_CFG_LONG_HEADER]) {
		fprintf(fp, "# ------------------------ Trace END ---------------------"
			"--------------------------------------------------------------"
			"-----\n");
	};
	fclose(fp);
	printf("Performance trace saved into \"%s\" file.\n",
		trace_perf_file);



	/* Calculate Averages/Statistics*/
	fp = workdir_fopen(trace_perf_stats_file, "w");
	if (fp == NULL) {
		fprintf(stderr, "%s(): could not create %s!\n",
			__func__, trace_perf_stats_file);
		ret = OMAPCONF_ERR_NOT_AVAILABLE;
		goto counters44xx_count_err;
	}
	dprintf ("I'm here 2\n");
	autoadjust_table_init(table);
	row = 0;
	strncpy(table[row][0], "Performance Statistics", TABLE_MAX_ELT_LEN);
	strncpy(table[row][1], "Option", TABLE_MAX_ELT_LEN);
	strncpy(table[row][2], "Min", TABLE_MAX_ELT_LEN);
	strncpy(table[row][3], "Max", TABLE_MAX_ELT_LEN);
	strncpy(table[row][4], "Average", TABLE_MAX_ELT_LEN);
	row++;

	/* Note: sample_cnt+0 = min, +1=avg, +2 = max */
	min = sample_cnt;
	avg = sample_cnt+1;
	max = sample_cnt+2;


	dprintf ("I'm here 3\n");
	for (i = 0; i < TRACE_CFG_ENABLED_OPTIONS_MAX; i++) {
		/* Whats the 'if' below for? Will always be true... */
		if (trace_state[i] >= 0) {
			trace_buf[i][min] = ~0;
			trace_buf[i][max] =  0;
			trace_buf[i][avg] =  0;
			dprintf ("I'm here 3.%d\n", i);
			ret = value2name(i, name, trace_config_options_table);
			dprintf ("Name: %s MIN: %d MAX: %d AVG: %d\n", name, trace_buf[i][min], trace_buf[i][max], trace_buf[i][avg]);
			for (sample = 1; sample < sample_cnt; sample++) {
	dprintf ("I'm here 3.%d.%d\n", i, sample);
				temp = count32_delta(trace_buf[i][sample - 1],
					trace_buf[i][sample]);
	dprintf ("I'm here 3.%d.%d !FREQ %d\n", i, sample, temp);
				if (temp > trace_buf[i][max])
					trace_buf[i][max] = temp;
				if (temp < trace_buf[i][min])
					trace_buf[i][min] = temp;
				trace_buf[i][avg] = (unsigned int) avg_recalc((double) trace_buf[i][avg],
					(double) temp, sample - 1);
				ret = value2name(i, name, trace_config_options_table);
				dprintf ("Name: %s MIN: %d MAX: %d AVG: %d\n", name, trace_buf[i][min], trace_buf[i][max], trace_buf[i][avg]);
			} /* for sample < sample_cnt */
			dprintf ("I'm here 4.%d\n", i);
			/* Save statistics */
			ret = value2name(i, name, trace_config_options_table);
			dprintf ("Name: %s MIN: %d MAX: %d AVG: %d\n", name, trace_buf[i][min], trace_buf[i][max], trace_buf[i][avg]);
			strncpy(table[row][0], name, TABLE_MAX_ELT_LEN);


			strcpy (option, "");
			switch (i) {
			case TRACE_CFG_EMIF0_CNT0_FILTER:
			case TRACE_CFG_EMIF1_CNT0_FILTER:
			case TRACE_CFG_EMIF0_CNT1_FILTER:
			case TRACE_CFG_EMIF1_CNT1_FILTER:
				ret = value2name(trace_state[i], option, emif_event_counters);
				break;
			case TRACE_CFG_L2CC_CNT0_FILTER:
			case TRACE_CFG_L2CC_CNT1_FILTER:
				ret = value2name(trace_state[i], option, l2cc_event_counters_table);
				break;
			default:
				break;
			} /* end switch */
			strncpy(table[row][1], option, TABLE_MAX_ELT_LEN);
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%.2d", trace_buf[i][min]);
			snprintf(table[row][3], TABLE_MAX_ELT_LEN, "%.2d", trace_buf[i][max]);
			snprintf(table[row][4], TABLE_MAX_ELT_LEN, "%.2d", trace_buf[i][avg]);
			row++;
		} /* if (trace_state[i] >= 0 */

	} /* for i to TRACE_CFG_ENABLED_OPTIONS_MAX */
	dprintf ("I'm here 5\n");


	autoadjust_table_fprint(fp, table, row, 4);
	fclose(fp);
	printf("Performance statistics saved into \"%s\" file.\n\n",
		trace_perf_stats_file);
	dprintf ("I'm here 6\n");
	autoadjust_table_print(table, row, 4);
	dprintf ("I'm here 7\n");
	return ret;

counters44xx_count_err:
	/* Free allocated buffers */
	for (i = 0; i < TRACE_CFG_ENABLED_OPTIONS_MAX; i++) {
		if (trace_state[i] >= 0) {/* Traces state is enabled if non-neg state value. */
			if (trace_buf[i] != NULL) {
				free(trace_buf[i]);
			}
		}
	} /* end for i < TRACE_CFG_ENABLED_OPTIONS_MAX */

	return ret;
}


/**
 * Function: counters44xx_get_defaults
 * Role: Process defaults from a file.
 * Parameters:
 *	*fp: pointer to a a file opened for reading.
 * Return:
 *	0 in case of success
 * >1 if error processing the defaults
 * Modifies:
 * Modifies the various global perf trace values.
 */
int counters44xx_get_defaults(char *defaults_file)
{
	char param[64];
	char tmp_name[64];
	int i, j;
	int ret;
	int invalid_char = 0;
	unsigned int param_index;
	unsigned int value_index;

	unsigned int table_size;
	name_desc_val_table *default_tablep;

	dprintf("Hello!!! Calling Defaults routine.\n");

	/* Build name/val/desc array to hold defaults */


	table_size = (sizeof(trace_config_options_table));
	default_tablep = malloc(table_size);
	if (default_tablep == NULL) {
		fprintf(stderr, "%s(): ERROR: Unable to allocate memory for defaults table.Exiting.\n", __func__);
		return OMAPCONF_ERR_UNEXPECTED;
	}
		/* Must clear here. Other routines may depend on content being zeroed if not used. */
	memset(default_tablep, '\0', table_size);


	dprintf("Hello!!! Filling table with parameters.\n");

	/* Fill the table with the parameters for which we are looking */
	i = 0;
	while (strcmp(trace_config_options_table[i].name, "END") != 0) {

		ret = snprintf((default_tablep[i]).name, OMAPCONF_REG_NAME_MAX_LENGTH, "%s", trace_config_options_table[i].name);
		i++;
	};
		/* Add required END entry */
	ret = snprintf((default_tablep[i]).name, OMAPCONF_REG_NAME_MAX_LENGTH, "%s", "END");
	j = i+1; /* j now contains max entries in the default_tablep array */


	/* Call the get defaults routine */
	dprintf("Calling Defaults routine.\n");
	/* The middle paramter is an optional prefix string */
	ret = omapconf_getdefaults(defaults_file, "", default_tablep);
	dprintf("Returned.\n");

	/* Process the returned values */
	i = 0;
	while (strcmp(default_tablep[i].name, "END") != 0) {
		dprintf("Checking on item %d %s %s.\n", i, default_tablep[i].name, default_tablep[i].desc);
		/* If not an empty paramter... */
		if  (strncmp(default_tablep[i].desc, "", 1) != 0) {
			ret = name2value(default_tablep[i].name, &param_index, trace_config_options_table);
			switch (param_index) {
			/* Following are simple enabled/disabled items */
			case TRACE_CFG_TIMER_32K_SYNC:
			case TRACE_CFG_EMIF0_MCLK_CYCLES:
			case TRACE_CFG_EMIF1_MCLK_CYCLES:
			case TRACE_CFG_LONG_HEADER:
				if (strcmp(lowercase(default_tablep[i].desc), "enabled") == 0)
					trace_state[param_index] = 1;
				else
					trace_state[param_index] = -1;
				break;
			case TRACE_CFG_EMIF0_CNT0_FILTER:
			case TRACE_CFG_EMIF1_CNT0_FILTER:
			case TRACE_CFG_EMIF0_CNT1_FILTER:
			case TRACE_CFG_EMIF1_CNT1_FILTER:
				ret = name2value(default_tablep[i].desc, &value_index, emif_event_counters);
				if (value_index == EMIF44XX_PERF_CNT_FILTER_DISABLED) {
					trace_state[param_index] = -1;
				} else {
					trace_state[param_index] = value_index;
				}
				break;
			case TRACE_CFG_EMIF0_CNT0_ID:
			case TRACE_CFG_EMIF0_CNT1_ID:
			case TRACE_CFG_EMIF1_CNT0_ID:
			case TRACE_CFG_EMIF1_CNT1_ID:
				if (!(strcmp(lowercase(default_tablep[i].desc), "disabled") == 0)) {
					ret = sscanf(default_tablep[i].desc, "%u", &trace_state[param_index]);
					if (ret != 1) {
						fprintf(stderr, "%s(): Error - Integer ID did not match for %s: %s!!\n",
						__func__, param, default_tablep[i].desc);
						trace_state[param_index] = -1;
						break;
					};
				};
				if (trace_state[param_index] > 255) {
					fprintf(stderr, "%s(): Error - Param %s Integer ID > 255: %s!!\n",
						__func__, param, default_tablep[i].desc);
					trace_state[param_index] = -1;
				}
				break;
			case TRACE_CFG_EMIF0_CNT0_ADDRSPACE:
			case TRACE_CFG_EMIF0_CNT1_ADDRSPACE:
			case TRACE_CFG_EMIF1_CNT0_ADDRSPACE:
			case TRACE_CFG_EMIF1_CNT1_ADDRSPACE:
				ret = name2value(default_tablep[i].desc, &value_index, emif_event_memaddrspace);
				if (ret < 0) {
					fprintf(stderr, "%s(): Error - Unexpected Address Space for %s: %s!!\n",
					__func__, param, default_tablep[i].desc);
					trace_state[param_index] = -1;
					break;
				};
				trace_state[param_index] = value_index;
				break;


			case TRACE_CFG_L2CC_CNT0_FILTER:
			case TRACE_CFG_L2CC_CNT1_FILTER:
				dprintf("Made it to TRACE_CFG_L2CC_CNTn_FILTER.\n");
				ret = name2value(default_tablep[i].desc, &value_index, l2cc_event_counters_table);
				if (ret < 0) {
					fprintf(stderr, "%s(): Error - Unexpected L2CC Event Counter for %s: %s!!\n",
					__func__, param, default_tablep[i].desc);
					trace_state[param_index] = -1;
					break;
				};
				dprintf ("Im Here L2CC: Value Index: 0x%X\n", trace_state[param_index]);
				/* Note, for L2CC, disabled tracing is value 0x0 */
				if (!(value_index == L2CC44XX_EVT_CNT_DISABLED))
					trace_state[param_index] = value_index;
				break;

			case TRACE_CFG_SAMPLE_INTERVAL:
				ret = sscanf(default_tablep[i].desc, "%d", &sampling_rate);
				if (ret != 1) {
					help(HELP_TRACE);
					return OMAPCONF_ERR_ARG;
				}
/*
//				if (sampling_rate == 0) {
//					printf("0 sec sample time not allowed, ...\n\n");
//					sampling_rate = PERF_TRACE_SAMPLING_RATE_MS;
//					return OMAPCONF_ERR_ARG;
//						}
*/
						break;
			case TRACE_CFG_FILE_PREFIX:
				/* skorson -
				If argument includes optional file prefix
				NB: You must specify a time if specifying a prefix
				*/
				/* skorson - I'm sure there is a better way to do this... */
				for (j = 0; j < 64; j++) {
					if (default_tablep[i].desc[j] == '\0') {
						file_prefix[j] = default_tablep[i].desc[j];
						break;
					}   /* End of string  - add to file_prefix?*/
					if (j >= 20) {
						invalid_char++;
						break;
					}  /* Prefix is too long */
					if (default_tablep[i].desc[j] >= '0' && default_tablep[i].desc[j] <= '9') {
						file_prefix[j] = default_tablep[i].desc[j];
						continue;
					} /* valid number */
					if (default_tablep[i].desc[j] >= 'A' && default_tablep[i].desc[j] <= 'Z') {
						file_prefix[j] = default_tablep[i].desc[j];
						continue;
					} /* valid uprcase */
					if (default_tablep[i].desc[j] >= 'a' && default_tablep[i].desc[j] <= 'z') {
						file_prefix[j] = default_tablep[i].desc[j];
						continue;
					} /* valid lwrcase */
					if (default_tablep[i].desc[j] == '_' || default_tablep[i].desc[j] == '['
						|| default_tablep[i].desc[j] == ']' || default_tablep[i].desc[j] == '.'
						|| default_tablep[i].desc[j] == '-') {
						file_prefix[j] = default_tablep[i].desc[j];
						continue;
					} /* valid \_ \- \[ \] \. */
					invalid_char++; break;
				} /* end for */

				if (invalid_char) {
					printf("invalid prefix. Use <= 20 letters, digits, _-.[ or ] ...\n\n");
					return OMAPCONF_ERR_ARG;
				} /* end if */

				/* skorson -
				Here we have a file_prefix as the prefix. Now prepend to file names.
				built a small string prepend utility to simplify.
				This probably already exists somewhere... */

				ret = snprintf(tmp_name, 64, "%s%s", file_prefix, trace_perf_file);
				ret = snprintf(trace_perf_file, 64, "%s", tmp_name);
				ret = snprintf(tmp_name, 64, "%s%s", file_prefix, trace_perf_stats_file);
				ret = snprintf(trace_perf_stats_file, 64, "%s", tmp_name);

				break;

			case TRACE_CFG_NORMALIZE:
					printf("WARNING: Normalization not yet supported. Post-process this for now.\n");
					if (strcmp(lowercase(default_tablep[i].desc), "enabled") == 0) {
						trace_state[param_index] = 1;
						trace_state[TRACE_CFG_TIMER_32K_SYNC] = 1;
					} else
						trace_state[param_index] = -1;
					break;

			default:
				fprintf(stderr, "%s(): Error - No matching Parameter: entry %d %s!!\n",
					__func__, i, param);
				/* return OMAPCONF_ERR_ARG; */
				continue;
			} /* end switch */
			} /* end if found a value in defaults file */
		i++;
		} /* End while */

	return 0;
}


/**
 * Function: omap4conf_print_defaults
 * Role:
 * Parameters:
 *	None
 * Return:
 *	0 in case of success
 */
int counters44xx_print_defaults()
{
	int i;
	int ret;
	char name[64];
	char example_default[128];
	char desc[128];

	printf("\n\n");
	printf("# Counter Tracing Defaults Template\n");
	printf("# This can be used directly as an .omapconf_defaults file.\n");
	printf("\n");
	for (i = 0; i < TRACE_CFG_TABLE_MAX; i++) {
		ret = value2name(i, name, trace_config_options_table);
		ret = value2desc(i, desc, trace_config_options_table);
		ret = value2desc(i, example_default, trace_config_defaults_table);
		if (ret >= 0) {
			printf("%s\t%s\t# %s\n", name, example_default, desc);
		}
	}
	return 0;
}

#ifdef OMAP4CONF_COUNTERS_DEBUG
#undef dprintf
#define dprintf(format, ...)
#endif

/**
 * Function: counters44xx_main
 * Role:
 * Parameters:
 *	argc: shell input argument number
 *	argv: shell input argument(s)
 * Return:
 *	0 in case of success
 *      OMAPCONF_ERR_ARG
 *      OMAPCONF_ERR_CPU
 *	OMAPCONF_ERR_NOT_AVAILABLE
 *	OMAPCONF_ERR_UNEXPECTED
 */
int counters44xx_main(int argc, char *argv[])
{
	int ret = 0;
	int i;
	int help_skip = 0;
	int invalid_char = 0;
	char tmp_name[64];

	if (!cpu_is_omap44xx())
		return OMAPCONF_ERR_CPU;

	/* Check if a defaults file is provided */
	if ((argc < 1) || (argc > 3)) {
		help44xx(HELP_COUNTERS, "");
		return OMAPCONF_ERR_ARG;
	}

	dprintf("%s(): ARGC: %d\n", __func__, argc);
	for (i = 0; i < argc; i++) {
		dprintf("%s(): ARGV[%d]: %s\n", __func__, i, argv[i]);
		if (strcmp(argv[i], "help") == 0)
			help_skip++;
	}

/*
// skorson - Gotta be a better way to do this...
// I see other parts of the code use 'goto'...
*/
	if (help_skip == 0) {
		if ((argc >= 2) &&
		(strcmp(argv[1], "defaults") == 0)) {
			counters44xx_print_defaults();
			return 0;
		}


		/* Currently all variables are global to this file. */
		ret = counters44xx_get_defaults(defaults_file);
		if (ret) {
			fprintf(stderr, "%s(): ERROR: Error reading %s default file. Using programmed defaults.\n",
			__func__, defaults_file);
		}

		/* Retrieve capture_time */
		if (argc >= 2) {
			ret = sscanf(argv[1], "%d", &capture_time);
			if (ret != 1) {
				help44xx(HELP_COUNTERS, "");
				return OMAPCONF_ERR_ARG;
				}
			if (capture_time == 0) {
				printf("Continuous Trace Selected ...\n\n");
				}
			} /* end if argc >= 2 */

		if (argc >= 3) {
		/* skorson -
			If argument includes optional file prefix
			NB: You must specify a time if specifying a prefix
		*/
			/* skorson - checking for safe characters. I'm sure there is a better way to do this... */
			for (i = 0; i < 64; i++) {
				if (argv[2][i] == '\0') {
					file_prefix[i] = argv[2][i]; break;   }   /* End of string  - add to file_prefix?*/
				if (i >= 20) {
					invalid_char++;
					break;
				}  /* Prefix is too long */
				if (argv[2][i] >= '0' && argv[2][i] <= '9') {
					file_prefix[i] = argv[2][i];
					continue;
				} /* valid number */
				if (argv[2][i] >= 'A' && argv[2][i] <= 'Z') {
					file_prefix[i] = argv[2][i];
					continue;
				} /* valid uprcase */
				if (argv[2][i] >= 'a' && argv[2][i] <= 'z') {
					file_prefix[i] = argv[2][i];
					continue;
				} /* valid lwrcase */
				if (argv[2][i] == '_' || argv[2][i] == '['
					|| argv[2][i] == ']' || argv[2][i] == '.'
					|| argv[2][i] == '-') {
					file_prefix[i] = argv[2][i];
					continue;
				} /* valid \_ \- \[ \] \. */
				invalid_char++;
				break;
			} /* end for */

			if (invalid_char) {
				printf("invalid prefix. Use <= 20 letters, digits, _-.[ or ] ...\n\n");
				return OMAPCONF_ERR_ARG;
			} /* end if */

			/* skorson -
			Here we have a file_prefix as the prefix. Now prepend to file names.
			built a small string prepend utility to simplify.
			This probably already exists somewhere... */
/*			printf("DEBUG: Prefix == %s\n", file_prefix); */

			ret = snprintf(tmp_name, 64, "%s%s", file_prefix, trace_perf_file);
			ret = snprintf(trace_perf_file, 64, "%s", tmp_name);

			ret = snprintf(tmp_name, 64, "%s%s", file_prefix, trace_perf_stats_file);
			ret = snprintf(trace_perf_stats_file, 64, "%s", tmp_name);


		} /* End if argc = 3 */
	} /* End if help_skip == 0 */

	/* Retrieve trace type and call associated function */
	if (!help_skip) {
		ret = counters44xx_count(capture_time);
	} else if ((strcmp(argv[1], "help") == 0) && (argc >= 3)) {
		help44xx(HELP_COUNTERS, argv[2]);
	} else {
		help44xx(HELP_COUNTERS, "all");
		ret = OMAPCONF_ERR_ARG;
	}

	return ret;
}
