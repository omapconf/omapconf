/*
 *
 * @Component			OMAPCONF
 * @Filename			pmi44xx.c
 * @Description			OMAP4 PMI configuration & control functions
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


#include <pmi44xx.h>
#include <lib.h>
#include <mem.h>
#include <emu44xx.h>
#include <stdio.h>
#include <dpll.h>
#include <dpll44xx.h>
#include <clock44xx.h>
#include <coresight44xx.h>
#include <emu44xx.h>
#include <stm44xx.h>
#include <unistd.h>
#include <pmic.h>
#include <cpuinfo.h>
#include <string.h>
#include <pwrdm.h>


/* #define PMI44XX_DEBUG */
#ifdef PMI44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


#ifdef PMI44XX_DEBUG
static const reg_table pmi44xx_reg_table[8] = {
	{"PMI_PIR", OMAP4430_PMI_PIR},
	{"PMI_PSCR", OMAP4430_PMI_PSCR},
	{"PMI_PSR", OMAP4430_PMI_PSR},
	{"PMI_PCR", OMAP4430_PMI_PCR},
	{"PMI_PCFR", OMAP4430_PMI_PCFR},
	{"PMI_PTCR", OMAP4430_PMI_PTCR},
	{"PMI_PSWR", OMAP4430_PMI_PSWR},
	{"END", 0} };
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pmi44xx_capture_enable
 * @BRIEF		setup PMI to capture selected event class
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_INTERNAL
 *			OMAPCONF_ERR_ARG
 * @param[in]		class: event class to capture
 * @param[in]		div: divider
 * @param[in]		window_size: window size
 * @DESCRIPTION		setup PMI to capture selected event class
 *			NB: make sure EMU domain is ON before calling this
 *			function.
 *//*------------------------------------------------------------------------ */
int pmi44xx_capture_enable(pmi_event_class_type class,
	unsigned int div, unsigned int window_size)
{
	if (!emu44xx_is_enabled()) {
		printf("pmi44xx_capture_enable(): "
			"trying to setup PMI but EMU domain OFF!!!\n");
		return OMAPCONF_ERR_INTERNAL;
	}

	if (class >= PMI_EVENT_MAX) {
		printf("pmi44xx_capture_enable(): "
			"incorrect class (0x%08X)!!!\n", class);
		return OMAPCONF_ERR_ARG;
	}
	if (div > 16) {
		printf("pmi44xx_capture_enable(): "
			"incorrect div (%d)!!!\n", div);
		return OMAPCONF_ERR_ARG;
	}
	if (div == 0) {
		printf("pmi44xx_capture_enable(): "
			"div == 0!!!\n");
		return OMAPCONF_ERR_ARG;
	}
	if (window_size > 256) {
		printf("pmi44xx_capture_enable(): "
			"incorrect window_size (%d)!!!\n", window_size);
		return OMAPCONF_ERR_ARG;
	}

	dprintf("pmi44xx_capture_enable(): setup PMI to capture events "
		"of class %x (div=%d size=%d) ...\n", class, div, window_size);
	/* Soft reset PMI module */
	mem_write(OMAP4430_PMI_PSCR, 0x9);
	mem_write(OMAP4430_PMI_PSCR, 0x8);
	/* Claim PMI module */
	mem_write(OMAP4430_PMI_PCR, 0x50000000);
	/* Enable PMI module */
	mem_write(OMAP4430_PMI_PCR, 0x90000000);
	/* Select monitored event class */
	mem_write(OMAP4430_PMI_PCFR, class);
	/* Set default PMI Clock Divider (16) & sample window size (256) */
	mem_write(OMAP4430_PMI_PSWR, ((div - 1) << 16) | window_size);
	/* Enable PMI capture */
	mem_write(OMAP4430_PMI_PCR, 0x90000080);
	#ifdef PMI44XX_DEBUG
	dumpregs((reg_table *) pmi44xx_reg_table);
	printf("pmi44xx_capture_enable(): PMI setup done.\n");
	#endif

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pmi44xx_capture_disable
 * @BRIEF		disable PMI Events capture
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_INTERNAL
 * @DESCRIPTION		disable PMI Events capture
 *			NB: make sure EMU domain is ON before calling this
 *			function.
 *//*------------------------------------------------------------------------ */
int pmi44xx_capture_disable(void)
{
	unsigned int pmi_psr;

	if (!emu44xx_is_enabled()) {
		printf("pmi44xx_capture_disable(): "
			"trying to setup PMI but EMU domain OFF!!!\n");
		return OMAPCONF_ERR_INTERNAL;
	}

	/* Stop PMI Capture */
	mem_write(OMAP4430_PMI_PCR, 0x90000000);
	dprintf("pmi44xx_capture_disable(): PMI Capture stopped.\n");

	/* Make sure FIFO buffer is empty */
	do {
		mem_read(OMAP4430_PMI_PSR, &pmi_psr);
	} while ((pmi_psr & 0x00000100) != 0x00000100);
	dprintf("pmi44xx_capture_disable(): PMI FIFO buffer is empty.\n");

	return 0;
}


/* #define PMI44XX_TRACE_CAPTURE_DEBUG */
#ifdef PMI44XX_TRACE_CAPTURE_DEBUG
#undef dprintf
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#endif
/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pmi44xx_trace_capture
 * @BRIEF		capture PMI trace and save it into file
 * @RETURNS		> 0 saved trace length (in 4-bit words)
 *			OMAPCONF_ERR_EMPTY
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		class: PMI event class to capture
 * @param[in]		time: capture duration (in seconds)
 * @param[in]		delay: delay before capture start (in seconds)
 * @param[in,out]	file: output file where captured trace is saved
 * @DESCRIPTION		capture PMI trace and save it into file
 *//*------------------------------------------------------------------------ */
int pmi44xx_trace_capture(pmi_event_class_type class,
	unsigned int time, unsigned short delay, char *file)
{
	int ret;
	unsigned int size;

	/* Check arguments */
	if (class >= PMI_EVENT_MAX)
		return OMAPCONF_ERR_ARG;
	if (time == 0)
		return OMAPCONF_ERR_ARG;
	if (file == NULL)
		return OMAPCONF_ERR_ARG;

	/* Enable EMU power domain */
	emu44xx_enable();

	/* Enable ETB capture */
	ret = coresight_etb_capture_enable();
	if (ret < 0)
		goto restore_hw_cfg1;

	/* Configure STM to collect PMI events */
	ret = stm_claim_ownership();
	if (ret < 0)
		goto restore_hw_cfg2;

	ret = stm_hw_master_enable(HW_MASTER_PMI, 0);
	if (ret < 0)
		goto restore_hw_cfg3;

	ret = stm_atb_prescaler_set(1);
	if (ret < 0)
		goto restore_hw_cfg4;

	ret = stm_atb_capture_enable();
	if (ret < 0)
		goto restore_hw_cfg4;

	if (delay != 0) {
		/* Initial delay before starting capture */
		printf("Wait for UART TX timeout (%d sec) then start PMI "
			"capture & suspend omapconf task for %d sec ...\n",
			delay, time);
		if (class == PMI_EVENT_PWRDM_TRANSITION)
			printf("NB: if UART console was ever used during this "
			"time, expected CORE/PER low-power state(s) "
			"might not be entered.\n");
		sleep(delay);
	} else {
		printf("Start PMI capture & suspend omapconf task for %d sec "
			"...\n", time);
		if (class == PMI_EVENT_PWRDM_TRANSITION)
			printf("NB: if UART console was ever used during this "
			"time, expected CORE/PER low-power state(s) "
			"might not be entered.\n");
	}

	/* Configure PMI to capture power domain transitions */
	ret = pmi44xx_capture_enable(class, 16, 256);
	if (ret < 0)
		goto restore_hw_cfg5;

	/* Suspend while collecting trace */
	sleep(time);

	/* Stop PMI Capture */
	ret = pmi44xx_capture_disable();

	/* Stop PMI capture in STM */
	ret = stm_atb_capture_disable();

	/* Stop ETB capture */
	ret = coresight_etb_capture_disable(&size);
	dprintf("PMI Capture stopped.\n");
	switch (ret) {
	case 0:
		dprintf("Captured trace length is %d 32-bit words'\n", size);
		break;
	case OMAPCONF_ERR_FULL:
		printf("Warning: ETB RAM buffer overflow detected, "
			"beginning of trace is lost...\n");
		dprintf("Captured trace length is %d 32-bit words'\n", size);
		break;
	case OMAPCONF_ERR_EMPTY:
		printf("Warning: no data received in trace buffer?!\n");
	default:
		goto restore_hw_cfg5;
	}

	/* Save trace */
	ret = coresight_etb_save_trace(file);
	if (ret <= 0) {
		printf("Could not create ETB trace file!\n\n");
		ret = OMAPCONF_ERR_NOT_AVAILABLE;
		goto restore_hw_cfg5;
	}

	/* Release/Restore HW */
	stm_hw_master_disable(0);
	stm_release_ownership();
	emu44xx_disable();

	return ret;

restore_hw_cfg5:
	stm_atb_capture_disable();
restore_hw_cfg4:
	stm_hw_master_disable(0);
restore_hw_cfg3:
	stm_release_ownership();
restore_hw_cfg2:
	coresight_etb_capture_disable(&size);
restore_hw_cfg1:
	emu44xx_disable();
	if (ret != OMAPCONF_ERR_EMPTY)
		fprintf(stderr, "%s(): internal error during capture!",
			__func__);
	return ret;
}
#ifdef PMI44XX_TRACE_CAPTURE_DEBUG
#undef dprintf
#define dprintf(format, ...)
#endif


/* #define PMI44XX_TRACE_DECODE_DEBUG */
#ifdef PMI44XX_TRACE_DECODE_DEBUG
#undef dprintf
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#endif
/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pmi44xx_trace_decode
 * @BRIEF		from ETB RAW trace, extract PMI STP messages and save it
 *			into file.
 * @RETURNS		>=0 number of event(s) in trace
 *			OMAPCONF_ERR_EMPTY
 *			OMAPCONF_ERR_TRUNCATED
 *			OMAPCONF_ERR_CORRUPTED
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_UNEXPECTED
 *			OMAPCONF_ERR_INTERNAL
 * @param[in,out]	etb_trace: name of the file where RAW ETB trace
 *				is stored.
 * @param[in]		lts_ref_clk: ATCLK reference clock speed (in MHz)
 * @param[in,out]	pmi_trace: name of the file where to store decoded
 *				PMI STP messages trace.	File contains also
 *				the RAW ETB trace for reference.
 * @param[in,out]	duration: total trace duration in microseconds.
 *				(returned)
 * @param[in]		vddcore_opp: VDD_CORE OPP when the PMI capture was
 *			started (due to OMAP4 HW bug, no initial OPP event ...)
 * @DESCRIPTION		from ETB RAW trace, extract PMI STP messages and save it
 *			into file.
 *//*------------------------------------------------------------------------ */
int pmi44xx_trace_decode(char *etb_trace, unsigned int lts_ref_clk,
	char *pmi_trace, double *duration, opp44xx_id vddcore_opp)
{
	unsigned int next_header;
	unsigned char stp_header;
	unsigned int evt_count;
	char s[9];
	unsigned int ts_gr;
	unsigned int ts_rel;
	unsigned int evt_status;
	unsigned int evt_data = 0, evt_data_prev = 0;
	unsigned int evt_class;
	unsigned int master_id;
	unsigned int length;
	double user_ts_abs, user_ts_rel, ts_rel_g;
	double atclk, atclk_dpll_unlocked, atclk_dpll_locked;
	omap4_dpll_params dpll_params;
	unsigned char in_dpll_cascading;
	pwrdm_state core_pwrdm_state = PWRDM_ON_STATE;
	unsigned char first_stp_header_found;
	FILE *fp_in;
	FILE *fp_out;
	int ret;
	static const double atclk_locked_opp50 = 200.0; /* MHz */
	static const double atclk_locked_opp100 = 266.66; /* MHz */
	double volt;

	if (etb_trace == NULL) {
		printf("pmi44xx_trace_decode() error: etb_trace == NULL!\n");
		return OMAPCONF_ERR_ARG;
	}
	if (pmi_trace == NULL) {
		printf("pmi44xx_trace_decode() error: "
			"pmi_trace == NULL!\n");
		return OMAPCONF_ERR_ARG;
	}
	if (duration == NULL) {
		printf("pmi44xx_trace_decode() error: "
			"duration == NULL!\n");
		return OMAPCONF_ERR_ARG;
	}

	fp_in = fopen(etb_trace, "r");
	if (fp_in == NULL) {
		printf("pmi44xx_trace_decode() error: "
			"could not open %s!\n", etb_trace);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}
	fp_out = fopen(pmi_trace, "w");
	if (fp_out == NULL) {
		printf("pmi44xx_trace_decode() error: "
			"could not open %s!\n", pmi_trace);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	/* Init variables */
	next_header = 0;
	ts_gr = 1;
	user_ts_abs = 0.0;
	ts_rel = 0;
	s[8] = '\0';
	*duration = 0.0;
	ret = 0;
	evt_count = 0;

	/*
	 * WORKAROUND:
	 * Last STP header does not seem to be a D8TS as specified.
	 * Need to browse trace and remove STP header(s) until a first D8TS is
	 * found.
	 */
	first_stp_header_found = 0;

	/*
	 * OMAP4 WORKAROUND:
	 * ATCLK derives from CORE_DPLL_EMU_CLK (CORE DPLL M6 output),
	 * dependent on:
	 *	- CORE domain OPP
	 *	- CORE DPLL state (locked / not locked)
	 * MUST track CORE DPLL status & OPP to accurately compute timestamp.
	 * Assumption: we are either in or not in DPLL cascading mode
	 * for the whole capture + decode time.
	 */

	/* Detect if running in DPLL cascading mode */
	ret = dpll44xx_dpll_params_get(DPLL44XX_CORE, &dpll_params, 0);
	if (ret < 0) {
		printf("pmi44xx_trace_decode(): error while getting "
			"CORE DPLL parameters! (%d)", ret);
		return OMAPCONF_ERR_INTERNAL;
	}

	atclk_dpll_unlocked = clk44xx_get_system_clock_speed();
	if (dpll_params.status != DPLL_STATUS_LOCKED) {
		dprintf("pmi44xx_trace_decode(): in DPLL cascading mode\n");
		in_dpll_cascading = 1;
	} else {
		in_dpll_cascading = 0;
	}
	dprintf("atclk_locked_opp50 = %.3lfMHz\n",
		atclk_locked_opp50);
	dprintf("atclk_locked_opp100 = %.3lfMHz\n",
		atclk_locked_opp100);
	dprintf("atclk_dpll_unlocked = %.3lfMHz\n", atclk_dpll_unlocked);
	atclk_dpll_locked = atclk_locked_opp100;
	if (vddcore_opp == OMAP4_OPP100)
		atclk_dpll_locked = atclk_locked_opp100;
	else
		atclk_dpll_locked = atclk_locked_opp50;

	/* Save ETB PMI RAW trace into file */
	fprintf(fp_out, "RAW ETB Trace:\n");
	length = 0;
	while (fread(&stp_header, sizeof(char), 1, fp_in) == 1) {
		fwrite(&stp_header, sizeof(char), 1, fp_out);
		if (stp_header != '\n')
			length++;
	};
	if (length == 0) {
		printf("pmi44xx_trace_decode(): trace file is empty!!!\n");
		fclose(fp_out);
		fclose(fp_in);
		remove(pmi_trace);
		return OMAPCONF_ERR_EMPTY;
	}
	dprintf("\n\nTrace size: %d bytes\n", length);
	fprintf(fp_out, "\n\nTrace size: %d bytes\n", length);

	dprintf("\n----- Decoded PMI Events Trace -----");
	fprintf(fp_out, "\n----- Decoded PMI Events Trace -----");
	while (ret == 0) {
		fseek(fp_in, next_header, SEEK_SET);
		ret = fread(&stp_header, sizeof(char), 1, fp_in);
		if ((ret != 1) || (stp_header == '\n')) {
			dprintf("\nEnd of trace reached.\n");
			fprintf(fp_out, "\n");
			ret = 0;
			break;
		}

		/* Decode STP header */
		switch (stp_header) {
		case '1':
			dprintf("\nMST (0x1)\n");
			/* Next expected header position */
			next_header = ftell(fp_in) + 2;
			if (first_stp_header_found == 0) {
				dprintf("\tSkipped\n");
				ret = 0;
				break;
			}
			fprintf(fp_out, "\nMST (0x1)\n");

			/* Retrieve Master ID */
			ret = fread(s, sizeof(char), 2, fp_in);
			if (ret != 2) {
				if (feof(fp_in) != 0)
					goto err_trace_truncated;
				dprintf("get Master ID from trace failed!\n");
				goto err_trace_unexpected;
			}
			ret = sscanf(s, "%2x", &master_id);
			if (ret != 1) {
				dprintf("get Master ID from string failed!\n");
				goto err_trace_unexpected;
			}
			dprintf("\tMaster ID = 0x%02X\n", master_id);
			fprintf(fp_out, "\tMaster ID = 0x%02X\n", master_id);
			ret = 0;
			break;

		case '4':
			dprintf("\nD8 (0x4)\n");
			/* Next expected header position */
			next_header = ftell(fp_in) + 2;
			if (first_stp_header_found == 0) {
				dprintf("\tSkipped\n");
				ret = 0;
				break;
			}
			fprintf(fp_out, "\nD8 (0x4)\n");

			/* Decode Event Class */
			ret = fread(s, sizeof(char), 2, fp_in);
			if (ret != 2) {
				if (feof(fp_in) != 0)
					goto err_trace_truncated;
				dprintf("get event class from trace failed!\n");
				goto err_trace_unexpected;
			}

			evt_class = 0;
			sscanf(s, "%2x", &evt_class);
			if (evt_class == PMI_VOLTDM_CLASS_LOGIC) {
				dprintf("\tEvent Class: Logic Voltage Domain "
					"(0x%02X)\n", evt_class);
				fprintf(fp_out, "\tEvent Class is Logic "
					"Voltage Domain (0x%02X)\n", evt_class);
				dprintf("\t\tevt_data = 0x%08X%08X\n",
					evt_data_prev, evt_data);
				fprintf(fp_out, "\t\tEvent Data = 0x%08X%08X\n",
					evt_data_prev, evt_data);
				/* Save VDD_CORE OPP */
				if ((evt_data_prev & 0x000000FF) == 0x8C) {
					/* Garbage ... */
					dprintf("\t\tIgnore 0x8C garbage...\n");
				} else {
					volt = (double) smps_vsel2uvolt(
						vdd_id2smps_id(OMAP4_VDD_CORE),
						evt_data_prev & 0x000000FF);
					volt = volt / 1000000.0;
					dprintf("\t\tVDD_CORE voltage = 0x%2X "
						"(%.3lfV)\n",
						evt_data_prev & 0x000000FF,
						volt);
					if (volt <= 1.0) {
						atclk_dpll_locked =
							atclk_locked_opp50;
						dprintf("\t\tVDD_CORE OPP is "
							"OPP50, "
							"atclk_dpll_locked="
							"%.3lfMHz\n",
							atclk_dpll_locked);
					} else {
						atclk_dpll_locked =
							atclk_locked_opp100;
						dprintf("\t\tVDD_CORE OPP is "
							"OPP100, "
							"atclk_dpll_locked="
							"%.3lfMHz\n",
							atclk_dpll_locked);
					}
				}
			} else if (evt_class == PMI_VOLTDM_CLASS_MEM) {
				dprintf("\tEvent Class: Memory Voltage Domain "
					"(0x%02X)\n", evt_class);
				fprintf(fp_out, "\tEvent Class is Memory "
					"Voltage Domain (0x%02X)\n", evt_class);
				dprintf("\t\tevt_data = 0x%08X\n", evt_data);
				fprintf(fp_out,
					"\t\tEvent Data = 0x%08X\n", evt_data);
			} else if (evt_class == PMI_PWRDM_CLASS_LOGIC) {
				dprintf("\tEvent Class: Logic Power Domain "
					"(0x%02X)\n", evt_class);
				fprintf(fp_out, "\tEvent Class is Logic "
					"Power Domain (0x%02X)\n", evt_class);
				dprintf("\t\tevt_data = 0x%08X\n", evt_data);
				fprintf(fp_out,
					"\t\tEvent Data = 0x%08X\n", evt_data);
				/*
				 * OMAP4 WORKAROUND:
				 * ATCLK derives from CORE_DPLL_EMU_CLK
				 * (CORE DPLL M6 output), dependent on:
				 *	- CORE domain OPP
				 *	- CORE DPLL state (locked / not locked)
				 * Need to track CORE DPLL status to
				 * correctly compute timestamp.
				 * Assumption: same EMU clock at OPP100 & OPP50
				 */
				core_pwrdm_state = (pwrdm_state)
					((evt_data & 0x00000C00) >> 10);
			} else if (evt_class == PMI_PWRDM_CLASS_MEM) {
				dprintf("\tEvent Class: Memory Power Domain "
					"(0x%02X)\n", evt_class);
				fprintf(fp_out, "\tEvent Class is Memory "
					"Power Domain (0x%02X)\n", evt_class);
				dprintf("\t\tevt_data = 0x%08X%08X\n",
					evt_data_prev, evt_data);
				fprintf(fp_out, "\t\tEvent Data = 0x%08X%08X\n",
					evt_data_prev, evt_data);
			} else {
				dprintf("ERROR: Junk Event class! (0x%02X)\n",
					evt_class);
				goto err_trace_corrupted;
			}

			/* Compute Timestamp */
			dprintf("\tts_gr = %d\n", ts_gr);
			dprintf("\tts_rel = %d\n", ts_rel);
			/* Taking into account LSTG */
			if (ts_gr < 7)
				ts_rel_g = ts_rel * (1 << ts_gr);
			else if (ts_gr >= 7)
				ts_rel_g =
					ts_rel * (1 << (6 + 2 * (ts_gr - 6)));
			dprintf("\tts_rel_g = %lf\n", ts_rel_g);
			/* Taking into account ATCLK frequency and pre-scaler */
			/*
			 * OMAP4 WORKAROUND:
			 * ATCLK derives from CORE_DPLL_EMU_CLK
			 * (CORE DPLL M6 output), dependent on:
			 *	- CORE domain OPP
			 *	- CORE DPLL state (locked / not locked)
			 * Need to track CORE DPLL status & OPP to correctly
			 * compute timestamp.
			 */
			if (in_dpll_cascading == 1) {
				atclk = atclk_dpll_unlocked;
				dprintf("\tIn DPLL cascading mode, "
					"EMU running from sysclk\n");
			} else {
				if (core_pwrdm_state == PWRDM_ON_STATE) {
					atclk = atclk_dpll_locked;
					dprintf("\tCORE domain is ON, "
						"CORE DPLL is locked\n");
				} else {
					atclk = atclk_dpll_unlocked;
					dprintf("\tCORE domain is not ON, "
						"CORE DPLL is unlocked\n");
				}
			}

			dprintf("\tatclk = %.3lfMHz\n", atclk);
			user_ts_rel = atclk / (double) lts_ref_clk;
			user_ts_rel = ts_rel_g / user_ts_rel;
			user_ts_abs += user_ts_rel;
			dprintf("\tuser_ts_rel = %lfus\n", user_ts_rel);
			dprintf("\tuser_ts_abs = %lfus\n", user_ts_abs);
			fprintf(fp_out,
				"\tTimestamp (relative) = %lfus\n",
					user_ts_rel);
			evt_count++;
			ret = 0;
			break;

		case '6':
			dprintf("\nD32 (0x6)\n");
			/* Next expected header position */
			next_header = ftell(fp_in) + 8;
			if (first_stp_header_found == 0) {
				dprintf("\tSkipped\n");
				ret = 0;
				break;
			}
			fprintf(fp_out, "\nD32 (0x6)\n");

			/* Decode Event state */
			evt_data_prev = evt_data;
			dprintf("\tevt_data_prev = 0x%08X\n", evt_data_prev);
			ret = fread(s, sizeof(char), 8, fp_in);
			if (ret != 8) {
				if (feof(fp_in) != 0)
					goto err_trace_truncated;
				dprintf("get event data from trace failed!\n");
				goto err_trace_unexpected;
			}
			ret = sscanf(s, "%8x", &evt_data);
			if (ret != 1) {
				dprintf("get event data from string failed!\n");
				goto err_trace_unexpected;
			}
			dprintf("\tevt_data = 0x%08X\n", evt_data);
			fprintf(fp_out, "\tEvent Data = 0x%08X\n", evt_data);
			ret = 0;
			break;

		case '8':
			dprintf("\nD8TS (0x8)\n");
			fprintf(fp_out, "\nD8TS (0x8)\n");
			/* Next expected header position */
			next_header = ftell(fp_in) + 4;
			if (first_stp_header_found == 0) {
				dprintf("\tFirst D8TS STP header found\n");
				first_stp_header_found = 1;
			}

			/* Decode Event status */
			ret = fread(s, sizeof(char), 2, fp_in);
			if (ret != 2) {
				if (feof(fp_in) != 0)
					goto err_trace_truncated;
				dprintf("get event status from trace failed\n");
				goto err_trace_unexpected;
			}
			ret = sscanf(s, "%2x", &evt_status);
			if (ret != 1) {
				dprintf("get event status from str failed\n");
				goto err_trace_unexpected;
			}
			dprintf("\tevt_status = 0x%02X\n", evt_status);
			fprintf(fp_out, "\tEvent Status = 0x%02X\n",
				evt_status);
			/* Decode event time stamp */
			ret = fread(s, sizeof(char), 2, fp_in);
			if (ret != 2) {
				if (feof(fp_in) != 0)
					goto err_trace_truncated;
				dprintf("get timestamp from trace failed!\n");
				goto err_trace_unexpected;
			}
			ret = sscanf(s, "%2x", &ts_rel);
			if (ret != 1) {
				dprintf("get timestamp from string failed!\n");
				goto err_trace_unexpected;
			}
			dprintf("\tRelative_Timestamp = 0x%02X (%d)\n",
				ts_rel, ts_rel);
			fprintf(fp_out, "\tRelative Timestamp = 0x%02X (%d)\n",
				ts_rel, ts_rel);
			/* TS granularity set to default (x1) */
			ts_gr = 0;
			ret = 0;
			break;

		case 'E':
			dprintf("\nLTSG (0xE)\n");
			/* Next expected header position */
			next_header = ftell(fp_in) + 1;
			if (first_stp_header_found == 0) {
				dprintf("\tSkipped\n");
				ret = 0;
				break;
			}
			fprintf(fp_out, "\nLTSG (0xE)\n");

			/* Decode TS granularity */
			ret = fread(s, sizeof(char), 1, fp_in);
			if (ret != 1) {
				if (feof(fp_in) != 0)
					goto err_trace_truncated;
				dprintf("get granularity from trace failed!\n");
				goto err_trace_unexpected;
			}
			ret = sscanf(s, "%1x", &ts_gr);
			if (ret != 1) {
				dprintf("get granularity from str failed!\n");
				goto err_trace_unexpected;
			}
			dprintf("\tts_gr = 0x%X (%d)\n",
				ts_gr, ts_gr);
			fprintf(fp_out, "\tTimestamp Granularity = 0x%X (%d)\n",
				ts_gr, ts_gr);
			ret = 0;
			break;

		default:
			dprintf("ERROR: JUNK PMI STP header found "
				"at pos %d! (%c)\n", next_header, stp_header);
			goto err_trace_corrupted;
		}
	}
	goto pmi_trace_decode_success;

err_trace_unexpected:
	dprintf("----- END OF Decoded PMI Trace -----\n");
	fprintf(fp_out,
		"----- END OF Decoded PMI Trace -----\n");
	fprintf(fp_out, "\nInternal error during trace decoding!\n");
	*duration = 0.0;
	ret = OMAPCONF_ERR_UNEXPECTED;
	goto pmi44xx_trace_decode_end;

err_trace_corrupted:
	dprintf("----- END OF Decoded PMI Trace -----\n");
	fprintf(fp_out,
		"----- END OF Decoded PMI Trace -----\n");
	fprintf(fp_out, "\nError: trace is corrupted!\n");
	*duration = 0.0;
	ret = OMAPCONF_ERR_CORRUPTED;
	goto pmi44xx_trace_decode_end;

err_trace_truncated:
	dprintf("Warning: trace truncated, ETB buffer overflow?\n");
	dprintf("----- END OF Decoded PMI Trace -----\n");
	fprintf(fp_out,
		"----- END OF Decoded PMI Trace -----\n");
	*duration = user_ts_abs;
	ret = evt_count;
	dprintf("\nNumber of events found: %d\n", evt_count);
	fprintf(fp_out, "\nNumber of events found: %d\n",
		evt_count);
	dprintf("Total Trace Duration: %lfus\n", user_ts_abs);
	fprintf(fp_out, "Total Trace Duration: %lfus\n",
		user_ts_abs);
	fprintf(fp_out, "\nWarning: trace truncated, ETB buffer overflow?\n");
	ret = OMAPCONF_ERR_TRUNCATED;
	goto pmi44xx_trace_decode_end;

pmi_trace_decode_success:
	dprintf("----- END OF Decoded PMI Trace -----\n");
	fprintf(fp_out,
		"----- END OF Decoded PMI Trace -----\n");
	*duration = user_ts_abs;
	dprintf("\nNumber of events found: %d\n", evt_count);
	fprintf(fp_out, "\nNumber of events found: %d\n",
		evt_count);
	dprintf("Total Trace Duration: %lfus\n", user_ts_abs);
	fprintf(fp_out, "Total Trace Duration: %lfus\n",
		user_ts_abs);
	dprintf("Full trace decoded with no error.\n\n");
	fprintf(fp_out, "\nFull trace decoded with no error.\n");
	ret = evt_count;

pmi44xx_trace_decode_end:
	fclose(fp_out);
	fclose(fp_in);
	return ret;
}
#ifdef PMI44XX_TRACE_DECODE_DEBUG
#undef dprintf
#define dprintf(format, ...)
#endif


/* #define PMI_EVENTS_GET_DEBUG */
#ifdef PMI_EVENTS_GET_DEBUG
#undef dprintf
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#endif
/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pmi44xx_events_get
 * @BRIEF		retrieve PM event(s) from PMI trace file.
 * @RETURNS		>=0 total number of PM events extracted from PMI trace
 *			file
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in,out]	filename: PMI trace file generated by
 *				pmi44xx_trace_decode()
 * @param[in,out]	pmi_events: list of PMI events extracted from PMI
 *				trace file
 * @DESCRIPTION		retrieve PM event(s) from PMI trace file.
 *//*------------------------------------------------------------------------ */
int pmi44xx_events_get(char *filename, genlist *pmi_events)
{
	double ts;
	unsigned int evt_class, evt_state_lsb, evt_state_msb;
	FILE *fp;
	char line[256];
	char dummy[7], dummy2[8];
	pmi_event evt;
	unsigned int evt_count;

	if (pmi_events == NULL) {
		printf("pmi44xx_events_get() error: "
			"pmi_events == NULL!\n");
		return OMAPCONF_ERR_ARG;
	}
	if (filename == NULL) {
		printf("pmi44xx_events_get() error: "
			"filename == NULL!\n");
		return OMAPCONF_ERR_ARG;
	}

	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("pmi44xx_events_get() error: "
			"could not open %s!\n", filename);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	genlist_init(pmi_events);
	evt_count = 0;

	dprintf("pmi44xx_events_get(): "
		"parsing trace file...\n");
	while (fgets(line, sizeof(line), fp) != NULL) {
		/* Looking for D8 headers */
		if (strstr(line, "D8 (0x4)") == NULL)
			continue;

		dprintf("new D8 found\n");
		/* Retrieve Event Class */
		if (fgets(line, sizeof(line), fp) == NULL) {
			printf("unexpected end of line reached!\n");
			fclose(fp);
			return OMAPCONF_ERR_UNEXPECTED;
		}
		if (sscanf(line, "\tEvent Class is %s %s Domain (0x%02X)",
			dummy, dummy2, &evt_class) != 3) {
			printf("could not get class from %s", line);
			fclose(fp);
			return OMAPCONF_ERR_UNEXPECTED;
		}
		if (evt_class >= PMI_EVENT_CLASS_MAX) {
			printf("unexpected pm class found! (%d)\n", evt_class);
			fclose(fp);
			return OMAPCONF_ERR_UNEXPECTED;
		}
		dprintf("event class is %d\n", evt_class);
		evt.class = (pmi_event_class) evt_class;

		/* Retrieve event data */
		if (fgets(line, sizeof(line), fp) == NULL) {
			printf("unexpected end of line reached!\n");
			fclose(fp);
			return OMAPCONF_ERR_UNEXPECTED;
		}
		if ((evt_class == PMI_PWRDM_CLASS_LOGIC) ||
			(evt_class == PMI_VOLTDM_CLASS_MEM)) {
			if (sscanf(line, "\t\tEvent Data = 0x%08X",
				&evt_state_lsb) != 1) {
				printf("could not get state from %s", line);
				fclose(fp);
				return OMAPCONF_ERR_UNEXPECTED;
			}
			dprintf("event data is 0x%08X\n", evt_state_lsb);
			evt_state_msb = 0;
		} else {
			if (sscanf(line, "\t\tEvent Data = 0x%08X%08X",
				&evt_state_msb, &evt_state_lsb) != 2) {
				printf("could not get state from %s", line);
				fclose(fp);
				return OMAPCONF_ERR_UNEXPECTED;
			}
			dprintf("event data is 0x%08X%08X\n",
				evt_state_msb, evt_state_lsb);
		}
		evt.data_lsb = evt_state_lsb;
		evt.data_msb = evt_state_msb;
		genlist_addtail(pmi_events, &evt, sizeof(pmi_event));
		evt_count++;

		/* Retrieve relative timestamp from next line */
		if (fgets(line, sizeof(line), fp) == NULL) {
			printf("unexpected end of line reached!\n");
			fclose(fp);
			return OMAPCONF_ERR_UNEXPECTED;
		}
		if (sscanf(line, "\tTimestamp (relative) = %lfus", &ts) != 1) {
			printf("could not get timestamp from %s", line);
			fclose(fp);
			return OMAPCONF_ERR_UNEXPECTED;
		}
		dprintf("timestamp is %lfus\n", ts);
		evt.ts = ts;
	}
	fclose(fp);
	dprintf("pmi44xx_events_get(): found %d pwrdm events.\n",
		evt_count);

	return evt_count;
}
#ifdef PMI_EVENTS_GET_DEBUG
#undef dprintf
#define dprintf(format, ...)
#endif
