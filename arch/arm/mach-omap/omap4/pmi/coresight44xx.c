/*
 *
 * @Component			OMAPCONF
 * @Filename			coresight44xx.c
 * @Description			OMAP4 ARM CORESIGHT configuration & control
 *				functions
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


#include <coresight44xx.h>
#include <lib.h>
#include <mem.h>
#include <stdio.h>
#include <emu44xx.h>
#include <stm44xx.h>


/* #define CORESIGHT44XX_DEBUG */
#ifdef CORESIGHT44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

/* #define CORESIGHT_ETB_SAVE_TRACE_DEBUG */
/* #define CORESIGHT_ETB_SAVE_TRACE_DEBUG_SCENARIO1A */
/* #define CORESIGHT_ETB_SAVE_TRACE_DEBUG_SCENARIO1B */
/* #define CORESIGHT_ETB_SAVE_TRACE_DEBUG_SCENARIO1C */
/* #define CORESIGHT_ETB_SAVE_TRACE_DEBUG_SCENARIO1D */
/* #define CORESIGHT_ETB_SAVE_TRACE_DEBUG_SCENARIO2 */
/* #define CORESIGHT_ETB_SAVE_TRACE_DEBUG_SCENARIO3 */
/* #define CORESIGHT_ETB_SAVE_TRACE_DEBUG_SCENARIO4 */
/* #define CORESIGHT_ETB_SAVE_TRACE_DEBUG_SCENARIO5 */

#ifdef CORESIGHT_ETB_SAVE_TRACE_DEBUG
#define OMAP44xx_ETB_RAM_SIZE		40
#else
#define OMAP44xx_ETB_RAM_SIZE		8192 /* 8KB, in bytes */
#endif


#ifdef CORESIGHT44XX_DEBUG
static const reg_table coresight_etb_reg_table[15] = {
	{"ETB_RDP", OMAP4430_ETB_RDP},
	{"ETB_STS", OMAP4430_ETB_STS},
	{"ETB_RRP", OMAP4430_ETB_RRP},
	{"ETB_RWP", OMAP4430_ETB_RWP},
	{"ETB_TRG", OMAP4430_ETB_TRG},
	{"ETB_CTL", OMAP4430_ETB_CTL},
	{"ETB_FFSR", OMAP4430_ETB_FFSR},
	{"ETB_FFCR", OMAP4430_ETB_FFCR},
	{"ETB_CTS", OMAP4430_ETB_CTS},
	{"ETB_CTC", OMAP4430_ETB_CTC},
	{"ETB_LOCK", OMAP4430_ETB_LOCK},
	{"ETB_LOCK_STS", OMAP4430_ETB_LOCK_STS},
	{"END", 0x0} };


static const reg_table coresight_cstf_reg_table[7] = {
	{"CSTF_FCR", OMAP4430_CSTF_FCR},
	{"CSTF_PCR", OMAP4430_CSTF_PCR},
	{"CSTF_CTS", OMAP4430_CSTF_CTS},
	{"CSTF_CTC", OMAP4430_CSTF_CTC},
	{"CSTF_LOCK", OMAP4430_CSTF_LOCK},
	{"CSTF_LOCK_STS", OMAP4430_CSTF_LOCK_STS},
	{"END", 0} };
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		coresight_etb_capture_enable
 * @BRIEF		enable ETB capture
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_INTERNAL
 * @DESCRIPTION		enable ETB capture
 *			NB: make sure EMU domain is ON before calling
 *			this function.
 *//*------------------------------------------------------------------------ */
int coresight_etb_capture_enable(void)
{
	#ifdef CORESIGHT44XX_DEBUG
	unsigned int i, rrp, rwp, rrd;
	#endif

	if (!emu44xx_is_enabled()) {
		printf("coresight_etb_capture_enable(): "
			"trying to enable ETB but EMU domain OFF!!!\n");
		return OMAPCONF_ERR_INTERNAL;
	}

	dprintf("coresight_etb_capture_enable(): setup ETB...\n");
	/* Unlock ETB write access */
	mem_write(OMAP4430_ETB_LOCK, OMAP4_CORESIGHT_UNLOCK_VALUE);
	/* Configure ETB trigger (no trigger) */
	mem_write(OMAP4430_ETB_TRG, 0x0);
	/* Configure ETB formatter (bypassed) */
	mem_write(OMAP4430_ETB_FFCR, 0x0);
	/* Reset read/write pointers */
	mem_write(OMAP4430_ETB_RWP, 0);
	mem_write(OMAP4430_ETB_RRP, 0);

	#ifdef CORESIGHT44XX_DEBUG
	/* Initialise ETB RAM content */
	printf("coresight_etb_capture_enable(): init RAM content...\n");
	for (i = 0; i < (OMAP44xx_ETB_RAM_SIZE / 4); i += 4) {
		if (i < 64) {
			mem_read(OMAP4430_ETB_RWP, &rwp);
			printf("write 0xDEADBEEF at RWP = 0x%08X (i = %d)\n",
				rwp, i);
		}
		mem_write(OMAP4430_ETB_RWD, 0xDEADBEEF);
	}
	printf("coresight_etb_capture_enable(): check RAM content...\n");
	for (i = 0; i < (OMAP44xx_ETB_RAM_SIZE / 4); i += 4) {
		mem_read(OMAP4430_ETB_RRP, &rrp);
		mem_read(OMAP4430_ETB_RRD, &rrd);
		if (rrd != 0xDEADBEEF)
			dprintf("error at RRP = 0x%08X, read 0x%08X "
				"instead of 0xDEADBEEF!!!\n", rrp, rrd);
	}
	/* Reset read/write pointers */
	mem_write(OMAP4430_ETB_RWP, 0);
	mem_write(OMAP4430_ETB_RRP, 0);
	dumpregs((reg_table *) coresight_etb_reg_table);
	printf("coresight_etb_capture_enable(): setup ETB done.\n");
	#endif

	/* Enable ETB Capture */
	mem_write(OMAP4430_ETB_CTL, 0x1);
	dprintf("coresight_etb_capture_enable(): ETB capture enabled.\n");

	/* Configure ETB and Coresight Trace Funnel to capture STM trace */
	dprintf("coresight_etb_capture_enable(): setup Coresight Trace "
		"Funnel to capture STM trace...\n");
	/* Unlock CSTF write access */
	mem_write(OMAP4430_CSTF_LOCK, OMAP4_CORESIGHT_UNLOCK_VALUE);
	/* Enable STM Path (port 7, hold time = 15) */
	mem_write(OMAP4430_CSTF_FCR, 0x00000E80);
	/* Give STM path highest priority */
	mem_write(OMAP4430_CSTF_PCR, 0x00053977);

	#ifdef CORESIGHT44XX_DEBUG
	dumpregs((reg_table *) coresight_cstf_reg_table);
	printf("coresight_etb_capture_enable(): Coresight Trace "
		"Funnel setup done.\n");
	#endif

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		coresight_etb_buffer_overflow
 * @BRIEF		check if ETB RAM buffer overflow occurred
 * @RETURNS		0 if no overflow occurred
 *			1 if overflow occurred
 * @DESCRIPTION		check if ETB RAM buffer overflow occurred
 *//*------------------------------------------------------------------------ */
int coresight_etb_buffer_overflow(void)
{
	unsigned int sts;

	/* Check if RAM write pointer has wrapped around */
	mem_read(OMAP4430_ETB_STS, &sts);

	return (sts & 0x00000001);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		coresight_etb_buffer_read
 * @BRIEF		read ETB RAM buffer data at given position
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG in case of error
 * @param[in]		rrp: read pointer (position in buffer from 0
 *			to OMAP44xx_ETB_RAM_SIZE/4)
 * @param[in,out]	rrd: data read from ETB buffer at position 'rrp'
 * @DESCRIPTION		read ETB RAM buffer data at given position
 *//*------------------------------------------------------------------------ */
int coresight_etb_buffer_read(unsigned int rrp, unsigned int *rrd)
{
	if (rrp >= (OMAP44xx_ETB_RAM_SIZE / 4)) {
		fprintf(stderr, "coresight_etb_buffer_read(): "
			"rrp (%d) >= OMAP44xx_ETB_RAM_SIZE / 4 (%d)!\n",
			rrp, OMAP44xx_ETB_RAM_SIZE / 4);
		return OMAPCONF_ERR_ARG;
	}
	if (rrd == NULL) {
		fprintf(stderr, "coresight_etb_buffer_read(): rrd == NULL!\n");
		return OMAPCONF_ERR_ARG;
	}

	/* Set read pointer */
	mem_write(OMAP4430_ETB_RRP, rrp);

	/* Read data in ETB at location pointed by  rrp */
	#ifdef CORESIGHT_ETB_SAVE_TRACE_DEBUG
	*rrd = rrp;
	#else
	mem_read(OMAP4430_ETB_RRD, rrd);
	#endif

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		coresight_etb_capture_disable
 * @BRIEF		disable ETB capture
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_FULL in case of buffer overflow
 *			(*size = OMAP44xx_ETB_RAM_SIZE - 4)
 *			OMAPCONF_ERR_EMPTY in case of no data received in buffer
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_INTERNAL
 * @param[in,out]	size: number of received 32-bit words in ETB (returned)
 * @DESCRIPTION		disable ETB capture
 *			NB: make sure EMU domain is ON before calling this
 *			function.
 *//*------------------------------------------------------------------------ */
int coresight_etb_capture_disable(unsigned int *size)
{
	unsigned int rwp, sts;

	if (!emu44xx_is_enabled()) {
		printf("coresight_etb_capture_disable(): "
			"trying to enable ETB but EMU domain OFF!!!\n");
		return OMAPCONF_ERR_INTERNAL;
	}
	if (size == NULL)
		return OMAPCONF_ERR_ARG;

	/* Stop ETB capture */
	mem_write(OMAP4430_ETB_CTL, 0x0);
	dprintf("coresight_etb_capture_disable(): ETB Capture stopped.\n");

	/* Retrieve number of 32-bit words received in ETB
	 * HW automatically adds the following 4 words at end of ETB capture:
	 * 0x00000001
	 * 0x00000000
	 * 0x00000000
	 * 0x00000000
	 * Hence it should be ignored.
	 */

	/* Check if RAM write pointer has wrapped around */
	mem_read(OMAP4430_ETB_STS, &sts);
	if ((sts & 0x00000001) == 0x00000001) {
		dprintf("Warning: ETB RAM buffer overflow detected, "
			"beginning of trace is lost...\n");
		*size = OMAP44xx_ETB_RAM_SIZE - 4;
		return OMAPCONF_ERR_FULL;
	}

	mem_read(OMAP4430_ETB_RWP, &rwp);
	dprintf("coresight_etb_capture_disable(): RWP now = 0x%08X\n", rwp);
	if (rwp > 4) {
		rwp -= 4;
		dprintf("coresight_etb_capture_disable(): "
			"%d 32-bit entried received in ETB\n", rwp);
		*size = rwp;
		return 0;
	} else {
		dprintf("coresight_etb_capture_disable(): "
			"no STM trace received! :(((\n");
		*size = 0;
		return OMAPCONF_ERR_EMPTY;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		coresight_etb_save_trace
 * @BRIEF		save capture ETB trace into file
 * @RETURNS		>= 0 trace length (in 4-bit words)
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in,out]	filename: name of the file where to store the ETB trace
 * @DESCRIPTION		save capture ETB trace into file
 *			NB: make sure EMU domain is ON before calling this
 *			function.
 *//*------------------------------------------------------------------------ */
int coresight_etb_save_trace(char *filename)
{
	int i, j, first, last, pos, mask, shift, size;
	unsigned int rrd, rwp;
	unsigned short overflow, trace_in_2_parts;
	FILE *fp = NULL;

	if (filename == NULL) {
		printf("coresight_etb_save_trace(): filename == NULL!\n");
		return OMAPCONF_ERR_ARG;
	}
	if (!emu44xx_is_enabled()) {
		printf("coresight_etb_save_trace(): "
			"trying to enable ETB but EMU domain OFF!!!\n");
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	/* Retrieve position in the last ETB entry of the last STP header */
	pos = stm_last_header_pos_get();
	if (pos < 0) {
		printf("coresight_etb_save_trace(): "
			"last STP header not available!!!\n");
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}
	/* Get current write pointer */
	mem_read(OMAP4430_ETB_RWP, &rwp);
	/* Get overflow status */
	overflow = coresight_etb_buffer_overflow();
	if ((!overflow) && (rwp < 5)) {
		printf("WARNING: no PMI messages in ETB RAM\n");
		return 0;
	}

	#ifdef CORESIGHT_ETB_SAVE_TRACE_DEBUG
	#ifdef CORESIGHT_ETB_SAVE_TRACE_DEBUG_SCENARIO1A
	dprintf("Case 1a: no overflow\n");
	rwp = 10;
	overflow = 0;
	pos = 2;
	#endif
	#ifdef CORESIGHT_ETB_SAVE_TRACE_DEBUG_SCENARIO1B
	dprintf("Case 1b: no overflow, ETB buffer full\n");
	rwp = 0;
	overflow = 1;
	pos = 2;
	#endif
	#ifdef CORESIGHT_ETB_SAVE_TRACE_DEBUG_SCENARIO1C
	dprintf("Case 1c: no overflow, ETB buffer empty\n");
	rwp = 0;
	overflow = 0;
	pos = 2;
	#endif
	#ifdef CORESIGHT_ETB_SAVE_TRACE_DEBUG_SCENARIO1D
	dprintf("Case 1d: no overflow, only HW footer in ETB buffer\n");
	rwp = 4;
	overflow = 0;
	pos = 2;
	#endif
	#ifdef CORESIGHT_ETB_SAVE_TRACE_DEBUG_SCENARIO2
	dprintf("Case 2: overflow, no HW footer split\n");
	rwp = 6;
	overflow = 1;
	pos = 2;
	#endif
	#ifdef CORESIGHT_ETB_SAVE_TRACE_DEBUG_SCENARIO3
	dprintf("Case 3: overflow, HW footer split\n");
	rwp = 2;
	overflow = 1;
	pos = 2;
	#endif
	#ifdef CORESIGHT_ETB_SAVE_TRACE_DEBUG_SCENARIO4
	dprintf("Case 4: overflow, only HW footer "
		"(only 4 first words overwritten by HW footer\n");
	rwp = 4;
	overflow = 1;
	pos = 2;
	#endif
	#ifdef CORESIGHT_ETB_SAVE_TRACE_DEBUG_SCENARIO5
	dprintf("Case 5: overflow, 1 word overwritten but "
		"it's not the last STP message\n");
	rwp = 5;
	overflow = 1;
	pos = 8;
	#endif
	printf("coresight_etb_save_trace(): rwp = %d, overflow = %d,\n",
		rwp, overflow);
	#endif


	/*
	 * The last 4 32-bit words are not STP elements but
	 * added automatically by HW at end of capture. Discard it.
	 */
	if (!overflow) {
		first = 0;
		last = rwp - 5;
		/*
		 * last = rwp - 5 because:
		 * 1/ The last 4 32-bit words are not STP elements but
		 * added automatically by HW at end of capture.
		 * 2/ RWP points to next location to be written,
		 * not the last written.
		 */
		 trace_in_2_parts = 0;
	} else {
		/*
		 * In case of overflow, check if HW footer is split accross
		 * beginning and end of ETB buffer.
		 */
		first = rwp;
		if (rwp > 4) {
			last = rwp - 5;
			trace_in_2_parts = 1;
		} else if (rwp == 4) {
			last = (OMAP44xx_ETB_RAM_SIZE / 4) - 1;
			trace_in_2_parts = 0;
		} else {
			last = (OMAP44xx_ETB_RAM_SIZE / 4) - (5 - rwp);
			trace_in_2_parts = 0;
		}
	}

	/*
	 * If pos > 7, it means that last STP header is not in the last
	 * ETB entry but in the previous one. So need also to decrement last.
	 */
	if (pos > 7) {
		dprintf("coresight_etb_save_trace(): "
			"STP header in last - 1 ETB entry\n");
		if (trace_in_2_parts && (last == 0)) {
			last = (OMAP44xx_ETB_RAM_SIZE / 4) - 1;
			trace_in_2_parts = 0;
		} else {
			last--;
		}
		pos -= 8;
	}

	/* Open destination file */
	fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("error: could not create %s file!\n", filename);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	/* Save ETB RAM content into file */
	dprintf("coresight_etb_save_trace(): "
				"dumping ETB RAM content...\n");
	dprintf("trace_in_2_parts = %d, last = %d, first = %d\n",
		trace_in_2_parts, last, first);
	size = 0;
	if (trace_in_2_parts) {
		for (i = last; i >= 0; i--) {
			/* Read data in ETB at location i  */
			coresight_etb_buffer_read(i, &rrd);
			if (i == last) {
				/* Ignore irrelevant bits from last ETB entry */
				for (j = pos; j >= 0; j--) {
					shift = 4 * j;
					mask = 0xF << shift;
					fprintf(fp, "%X",
						(rrd & mask) >> shift);
					dprintf("%X", (rrd & mask) >> shift);
					size++;
				}
				dprintf("\n");
			} else {
				fprintf(fp, "%08X", rrd);
				dprintf("%08X\n", rrd);
				size += 4;
			}
		}

		last = (OMAP44xx_ETB_RAM_SIZE / 4) - 1;
	}

	for (i = last; i >= first; i--) {
		/* Read data in ETB at location i  */
		coresight_etb_buffer_read(i, &rrd);
		if ((!trace_in_2_parts) && (i == last)) {
			/* Ignore irrelevant bits from last ETB entry */
			for (j = pos; j >= 0; j--) {
				shift = 4 * j;
				mask = 0xF << shift;
				fprintf(fp, "%X",
					(rrd & mask) >> shift);
				dprintf("%X", (rrd & mask) >> shift);
				size++;
			}
			dprintf("\n");
		} else {
			fprintf(fp, "%08X", rrd);
			dprintf("%08X\n", rrd);
			size += 4;
		}
	}

	dprintf("coresight_etb_save_trace(): "
			"dumping ETB RAM content done.\n");
	fclose(fp);

	/* Return the ETB trace length */
	dprintf("coresight_etb_save_trace(): trace length = %d\n", size);
	return size;
}
