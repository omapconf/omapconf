/*
 *
 * @Component			OMAPCONF
 * @Filename			counters44xx.h
 * @Description			Collect OMAP4 PRCM PMI Traces in ETB
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


#ifndef __COUNTERS44XX_H__
#define __COUNTERS44XX_H__

#include <lib.h>


typedef enum {
	/*
	 * The options thta can be traced (i.e. enabled/disabled or appear in a
	 * file). Must be first.
	 */
	TRACE_CFG_TIMER_32K_SYNC,
	TRACE_CFG_L2CC_CNT0_FILTER,
	TRACE_CFG_L2CC_CNT1_FILTER,
	TRACE_CFG_EMIF0_CNT0_FILTER,
	TRACE_CFG_EMIF1_CNT0_FILTER,
	TRACE_CFG_EMIF0_CNT1_FILTER,
	TRACE_CFG_EMIF1_CNT1_FILTER,
	TRACE_CFG_EMIF0_MCLK_CYCLES,
	TRACE_CFG_EMIF1_MCLK_CYCLES,
	/* Index Marker */
	TRACE_CFG_ENABLED_OPTIONS_MAX,
	/*
	 * Options that don't require data storage (i.e. options for env. or
	 * other control of a traced option.) beyond this point.
	 */
	TRACE_CFG_EMIF0_CNT0_ID,
	TRACE_CFG_EMIF1_CNT0_ID,
	TRACE_CFG_EMIF0_CNT1_ID,
	TRACE_CFG_EMIF1_CNT1_ID,
	TRACE_CFG_EMIF0_CNT0_ADDRSPACE,
	TRACE_CFG_EMIF1_CNT0_ADDRSPACE,
	TRACE_CFG_EMIF0_CNT1_ADDRSPACE,
	TRACE_CFG_EMIF1_CNT1_ADDRSPACE,
	TRACE_CFG_SAMPLE_INTERVAL,
	TRACE_CFG_NORMALIZE,	/*
				 * When enabled, normalize results based on the
				 * TRACE_CFG_TIMER_32K_SYNC count.
				 * Setting enabled auto-enables
				 * TRACE_CFG_TIMER_32K_SYNC counting.
				 * Not configured (does not do anything)
				 * at this time.
				 */
	TRACE_CFG_FILE_PREFIX,
	TRACE_CFG_LONG_HEADER,
	/* Index marker */
	TRACE_CFG_TABLE_MAX
	} trace_cfg_options_type;


static const name_desc_val_table trace_config_options_table[] =  {
	{"TIMER_32K_SYNC",	"(ENABLED | DISABLED) free-running 32K timer timestamp.",	TRACE_CFG_TIMER_32K_SYNC},
	{"L2CC_CNT0_FILTER",	"Value of L2CC Event 0 event to trace (or DISABLED).",		TRACE_CFG_L2CC_CNT0_FILTER},
	{"L2CC_CNT1_FILTER",	"Value of L2CC Event 1 event to trace (or DISABLED).",		TRACE_CFG_L2CC_CNT1_FILTER},
	{"EMIF0_CNT0_FILTER",	"Value of EMIF0 CNT0 event to trace (or DISABLED).",            TRACE_CFG_EMIF0_CNT0_FILTER},
	{"EMIF1_CNT0_FILTER",	"Value of EMIF1 CNT0 event to trace (or DISABLED).",		TRACE_CFG_EMIF1_CNT0_FILTER},
	{"EMIF0_CNT1_FILTER",	"Value of EMIF0 CNT1 event to trace (or DISABLED).",		TRACE_CFG_EMIF0_CNT1_FILTER},
	{"EMIF1_CNT1_FILTER",	"Value of EMIF1 CNT1 event to trace (or DISABLED).",		TRACE_CFG_EMIF1_CNT1_FILTER},
	{"EMIF0_CNT0_ID",	"0 to 255 ID value (or DISABLED).",				TRACE_CFG_EMIF0_CNT0_ID},
	{"EMIF1_CNT0_ID",	"0 to 255 ID value (or DISABLED).",				TRACE_CFG_EMIF1_CNT0_ID},
	{"EMIF0_CNT1_ID",	"0 to 255 ID value (or DISABLED).",				TRACE_CFG_EMIF0_CNT1_ID},
	{"EMIF1_CNT1_ID",	"0 to 255 ID value (or DISABLED).",				TRACE_CFG_EMIF1_CNT1_ID},
	{"EMIF0_CNT0_ADDRSP",	"Addr-Space Filter (or DISABLED).",				TRACE_CFG_EMIF0_CNT0_ADDRSPACE},
	{"EMIF1_CNT0_ADDRSP",	"Addr-Space Filter (or DISABLED).",				TRACE_CFG_EMIF1_CNT0_ADDRSPACE},
	{"EMIF0_CNT1_ADDRSP",	"Addr-Space Filter (or DISABLED).",				TRACE_CFG_EMIF0_CNT1_ADDRSPACE},
	{"EMIF1_CNT1_ADDRSP",	"Addr-Space Filter (or DISABLED).",				TRACE_CFG_EMIF1_CNT1_ADDRSPACE},
	{"EMIF0_MCLK_CYCLES",	"EMIF0 MCLK cycles since EMIF0 reset (ENABLED | DISABLED).",	TRACE_CFG_EMIF0_MCLK_CYCLES},
	{"EMIF1_MCLK_CYCLES",	"EMIF1 MCLK cycles since EMIF1 reset (ENABLED | DISABLED).",	TRACE_CFG_EMIF1_MCLK_CYCLES},
	{"SAMPLE_INTERVAL",	"Integer sample interval, in ms.",				TRACE_CFG_SAMPLE_INTERVAL},
	{"FILE_PREFIX",		"20 character file prefix [a-zA-Z0-9\\[\\]\\._-].", 		TRACE_CFG_FILE_PREFIX},
	{"LONG_HEADER",		"(ENABLED | DISABLED) a long header in the dat file.", 		TRACE_CFG_LONG_HEADER},
	/* END OF TABLE IS REQUIRED! */
	{"END",			"END of Table.",						0} };

static const name_desc_val_table trace_config_defaults_table[] =  {
	{"TIMER_32K_SYNC",	"ENABLED",	TRACE_CFG_TIMER_32K_SYNC},
	{"L2CC_CNT0_FILTER",	"CO",		TRACE_CFG_L2CC_CNT0_FILTER},
	{"L2CC_CNT1_FILTER",	"DRHIT",	TRACE_CFG_L2CC_CNT1_FILTER},
	{"EMIF0_CNT0_FILTER",	"TOTAL_READ",	TRACE_CFG_EMIF0_CNT0_FILTER},
	{"EMIF1_CNT0_FILTER",	"DISABLED",	TRACE_CFG_EMIF1_CNT0_FILTER},
	{"EMIF0_CNT1_FILTER",	"TOTAL_READ",	TRACE_CFG_EMIF0_CNT1_FILTER},
	{"EMIF1_CNT1_FILTER",	"DISABLED",	TRACE_CFG_EMIF1_CNT1_FILTER},
	{"EMIF0_CNT0_ID",	"DISABLED",	TRACE_CFG_EMIF0_CNT0_ID},
	{"EMIF1_CNT0_ID",	"DISABLED",	TRACE_CFG_EMIF1_CNT0_ID},
	{"EMIF0_CNT1_ID",	"DISABLED",	TRACE_CFG_EMIF0_CNT1_ID},
	{"EMIF1_CNT1_ID",	"DISABLED",	TRACE_CFG_EMIF1_CNT1_ID},
	{"EMIF0_CNT0_ADDRSP",	"DISABLED",	TRACE_CFG_EMIF0_CNT0_ADDRSPACE},
	{"EMIF1_CNT0_ADDRSP",	"DISABLED",	TRACE_CFG_EMIF1_CNT0_ADDRSPACE},
	{"EMIF0_CNT1_ADDRSP",	"DISABLED",	TRACE_CFG_EMIF0_CNT1_ADDRSPACE},
	{"EMIF1_CNT1_ADDRSP",	"DISABLED",	TRACE_CFG_EMIF1_CNT1_ADDRSPACE},
	{"EMIF0_MCLK_CYCLES",	"ENABLED",	TRACE_CFG_EMIF0_MCLK_CYCLES},
	{"EMIF1_MCLK_CYCLES",	"ENABLED",	TRACE_CFG_EMIF1_MCLK_CYCLES},
	{"SAMPLE_INTERVAL",	"10",		TRACE_CFG_SAMPLE_INTERVAL},
	{"FILE_PREFIX",		"results_01_",	TRACE_CFG_FILE_PREFIX},
	{"LONG_HEADER",		"DISABLED",	TRACE_CFG_LONG_HEADER},
	/* END OF TABLE IS REQUIRED! */
	{"END",			"END of Table." , 0} };



/* ------------------------------------------------------------------------*//**
 * @FUNCTION		counters44xx_main
 * @BRIEF		main entry point
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		Counters functions main entry point
 *//*------------------------------------------------------------------------ */
int counters44xx_main(int argc, char *argv[]);


#endif
