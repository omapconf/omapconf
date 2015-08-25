/*
 *
 * @Component			OMAPCONF
 * @Filename			sci_swcapture.c
 * @Description			statistiscal collectors
 * @Author			Frederic Turgis (f-turgis@ti.com)
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


#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <getopt.h>
#include <pthread.h>
#include <signal.h>

#include "sci.h"
#include <powerdomain.h>
#include <cm44xx.h>
#include <lib.h>
#include <common/cpuinfo.h>
#include <prm44xx.h>
#include <cm54xx-defs.h>
#include <timr44xx.h>
#include <timr54xx.h>
#include <mem.h>
#include <timestamp_32k.h>

struct name_value {
	char *name;
	char *name_ccs;
	unsigned int value;
};

struct name_value match_master[] = {
{ "alldmm", "All DMM", SCI_MASTID_ALL },
{ "mpuss", "MPUSS", SCI_MSTID_MPUSS },
{ "dap", "DAP", SCI_MSTID_DAP },
{ "dsp", "DSP", SCI_MSTID_DSP },
{ "iva", "IVA", SCI_MSTID_IVA },
{ "iss", "ISS", SCI_MSTID_ISS },
{ "ipu", "IPU", SCI_MSTID_IPU },
{ "fdid", "FDID", SCI_MSTID_FDIF },
{ "sdma_rd", "SDMA_RD", SCI_MSTID_SDMA_RD },
{ "sdma_wr", "SDMA_WR", SCI_MSTID_SDMA_WR },
{ "gpu_p1", "GPU_P1", SCI_MSTID_GPU_P1 },
{ "gpu_p2", "GPU_P2", SCI_MSTID_GPU_P2 },
{ "bb2d_p1", "BB2D_P1", SCI_MSTID_BB2D_P1 },
{ "bb2d_p2", "BB2D_P2", SCI_MSTID_BB2D_P2 },
{ "dss", "DSS", SCI_MSTID_DSS },
{ "c2c", "C2C", SCI_MSTID_C2C },
{ "lli", "LLI", SCI_MSTID_LLI },
{ "hsi", "HSI", SCI_MSTID_HSI },
{ "unipro1", "UNIPRO1", SCI_MSTID_UNIPRO1 },
{ "unipro2", "UNIPRO2", SCI_MSTID_UNIPRO2 },
{ "mmc1", "MMC1", SCI_MSTID_MMC1 },
{ "mmc2", "MMC2", SCI_MSTID_MMC2 },
{ "sata", "SATA", SCI_MSTID_SATA },
{ "usb_host_hs", "USB_HOST_HS", SCI_MSTID_USB_HOST_HS },
{ "usb_otg_hs", "USB_OTG_HS", SCI_MSTID_USB_OTG_HS },
{ "usb_otg_fs", "USB_OTG_FS", SCI_MSTID_USB_OTG_FS },
{ "usb3", "USB3", SCI_MSTID_USB3 },
{ NULL, NULL, 0 }
};

struct name_value match_qualifier[] = {
{ "r", "Rd", SCI_RD_ONLY },
{ "r+w", "Rd/Wr", SCI_RD_OR_WR_DONTCARE },
{ "w", "Wr", SCI_WR_ONLY },
{ NULL, NULL, 0 }
};

struct name_value match_probe[] = {
{ "emif1", "EMIF 0", SCI_EMIF1 },
{ "emif2", "EMIF 1", SCI_EMIF2 },
{ NULL, NULL, 0 }
};

struct sci_config_sdram my_config_emif1 = { SCI_SDRAM_THROUGHPUT, SCI_EMIF1, 1,	{ { SCI_MASTID_ALL, 0xff, SCI_WR_ONLY, SCI_ERR_DONTCARE } } };
struct sci_config_sdram my_config_emif2 = { SCI_SDRAM_THROUGHPUT, SCI_EMIF2, 1,	{ { SCI_MASTID_ALL, 0xff, SCI_WR_ONLY, SCI_ERR_DONTCARE } } };
struct sci_config_sdram my_config_emif3 = { SCI_SDRAM_THROUGHPUT, SCI_EMIF1, 1,	{ { SCI_MASTID_ALL, 0xff, SCI_RD_ONLY, SCI_ERR_DONTCARE } } };
struct sci_config_sdram my_config_emif4 = { SCI_SDRAM_THROUGHPUT, SCI_EMIF2, 1,	{ { SCI_MASTID_ALL, 0xff, SCI_RD_ONLY, SCI_ERR_DONTCARE } } };
struct sci_config_sdram my_config_emif5 = { SCI_SDRAM_THROUGHPUT, SCI_EMIF1, 1,	{ { SCI_MASTID_ALL, 0xff, SCI_WR_ONLY, SCI_ERR_DONTCARE } } };
struct sci_config_sdram my_config_emif6 = { SCI_SDRAM_THROUGHPUT, SCI_EMIF2, 1,	{ { SCI_MASTID_ALL, 0xff, SCI_WR_ONLY, SCI_ERR_DONTCARE } } };
struct sci_config_sdram my_config_emif7 = { SCI_SDRAM_THROUGHPUT, SCI_EMIF1, 0,	{ { SCI_MASTID_ALL, 0xff, SCI_RD_OR_WR_DONTCARE, SCI_ERR_DONTCARE } } };
struct sci_config_sdram my_config_emif8 = { SCI_SDRAM_THROUGHPUT, SCI_EMIF2, 0,	{ { SCI_MASTID_ALL, 0xff, SCI_RD_OR_WR_DONTCARE, SCI_ERR_DONTCARE } } };

struct sci_config_sdram * pmy_cfg[] =  {
					&my_config_emif1,
                                        &my_config_emif2,
                                        &my_config_emif3,
                                        &my_config_emif4,
                                        &my_config_emif5,
                                        &my_config_emif6,
                                        &my_config_emif7,
                                        &my_config_emif8,
					};

#define GET_32K *(addr_32k)
#define MAX_ITERATIONS 1000000UL

static char msg[8][100], msg_overflow[8][100]; // messages for CCS like output (-a 1 option)
static volatile unsigned int *addr_32k = NULL; // 32K timestamping
static uint32_t counters[(8+1)*MAX_ITERATIONS]; // timestamp+counters storing in "-a 1" mode
static unsigned int num_use_cases = 4;
static unsigned int option_overflow_counter_index[2], option_overflow_threshold[2];
static unsigned int option_overflow_iterations;
static unsigned int tests; // number of tests really executed in case of Ctrl-C
static unsigned int nosleep_32k_reg; // -n option
static unsigned int option_nosleep_32k = 0; // -n option
static unsigned int option_accumulation_type; // -a option
static unsigned int valid_usecase_cnt = 0;
static psci_handle psci_hdl = NULL;
static psci_usecase_key my_usecase_key[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};


void sci_errhandler(psci_handle phandle, const char * func, enum sci_err err);
void nosleep_32k_enable(void);
void nosleep_32k_disable(void);

// Generic handling of sample array
#define SAMPLE_SIZE (1 + num_use_cases) // sample contains 1 timestamp + x counters
#define TIMESTAMP_INDEX (0) // timestamp is first index in 1 sample
#define COUNTER_INDEX (1) // counters are put just after timestamp

void dump_buffer(void)
{
	uint32_t *counters_current = counters;
	unsigned int timestamp0, time;
	unsigned int i,j, tests_overflow;
	unsigned int *prev_counter, *current_counter;
	tests_overflow = 1;
	unsigned int overflow_on = 0;

	fprintf(stderr, "%u iterations finished, dumping to file\n", tests);

	// for each test, we will compute delta between prev and current and print at current timestamp
	for (i = 0; i < tests - 1; i++)
	{
		unsigned int timestamp = *(counters_current + TIMESTAMP_INDEX + SAMPLE_SIZE);
		if (i == 0) {
			timestamp0 = *(counters_current + TIMESTAMP_INDEX);
			printf("Ref timestamp: %u\n", timestamp0);
		}
		// Use relative timestamp
		time = timestamp - timestamp0;

		// Detect reset. Sample i triggers reset so sample i+1 delta to i is ignored
		if (    ( (option_overflow_iterations > 0) && (tests_overflow > option_overflow_iterations) )
		     || (   (option_overflow_iterations == 0)
		         && (   (*(counters_current + COUNTER_INDEX + option_overflow_counter_index[0]) >= option_overflow_threshold[0])
		             || (*(counters_current + COUNTER_INDEX + option_overflow_counter_index[1]) >= option_overflow_threshold[1])
		            )
		        )
		   )
			overflow_on = 1;

		for (j = 0; j < num_use_cases; j++) {
			// current counter is in fact next sample, i.e. j + sample_size. prev is j
			current_counter = counters_current + SAMPLE_SIZE + COUNTER_INDEX + j;
			prev_counter = counters_current + COUNTER_INDEX + j;

			// Overflow at 2^32. We can't fix that
			if (*current_counter == 0xFFFFFFFF) {
				fprintf(stderr, "ERROR: counter %d %s overflowed at time %u, don't trust results\n", j, msg[j], time);
				printf("ERROR: counter %d %s overflowed at time %u, don't trust results\n", j, msg[j], time);
			}

			// Dump result. In case of overflow, just print for reference, post-processing will ignore
			if (overflow_on == 1) {
				printf("Warning: overflow\n");
				printf("0,0,0,S,,SDRAM,,%u,%s,T,V,%u,,,,0,\n", *current_counter - *prev_counter, msg_overflow[j], time);
			}
			else {
				// HW bug, you read a counter that is < previous value. We fix this by forcing same value than previous sample
				if (*current_counter < *prev_counter) {
					fprintf(stderr, "WARNING: HW bug, counter %d %s  N-1=%u N=%u at time %u. omapconf fixes it\n", j, msg[j], *prev_counter, *current_counter, time);
					printf("WARNING: HW bug, counter %d %s  N-1=%u N=%u at time %u. omapconf fixes it\n", j, msg[j], *prev_counter, *current_counter, time);
					// omapconf fix, any value is OK as this is only about deltas
					*current_counter = *prev_counter;
				}

				printf("0,0,0,S,,SDRAM,,%u,%s,T,V,%u,,,,0,\n", *current_counter - *prev_counter, msg[j], time);
			}
		}
		counters_current += SAMPLE_SIZE;

		if (overflow_on == 1) {
			tests_overflow = 0;
			overflow_on = 0;
		}
		tests_overflow++;
	}
}

void sci_killhandler(void)
{
	unsigned int i;

	if (option_accumulation_type == 1)
		dump_buffer();

	mem_unmap_32k(addr_32k);

	if (option_nosleep_32k)
		nosleep_32k_disable();

	for (i = 0; i < valid_usecase_cnt; i++) {
		sci_remove_usecase( psci_hdl, &my_usecase_key[i]);
	}

	sci_global_disable(psci_hdl);
	sci_close(&psci_hdl);
	powerdm_emu_disable();
}


int statcoll_main(int argc, char **argv)
{
	struct sci_config my_sci_config;
	enum sci_err my_sci_err;
	int c, option_index = 0;
	static int longopt_flag;
	unsigned int option_delay_us;
	unsigned int option_overflow_delay_us;
	unsigned int option_iterations;
	unsigned int option_disable = 0;
	unsigned int option_min_addr;
	unsigned int option_max_addr;
	unsigned int describe_loop;

	// Default values of options
	option_delay_us = 1000000; // 1 second
	option_overflow_delay_us = 1000000; // 1 second
	option_overflow_iterations = option_overflow_delay_us / option_delay_us;
	option_accumulation_type = 2; // dump on terminal
	option_iterations = 0; // infinite iterations
	option_overflow_counter_index[0] = 0; // check counter 0 for overflow
	option_overflow_counter_index[1] = 0;
	option_overflow_threshold[0] = 0; // reset at each capture
	option_overflow_threshold[1] = 0;

	static struct option long_options[] =
	{
		/* These options set a flag. */
		{"m0",	required_argument,	&longopt_flag,	'm'},
		{"m1",	required_argument,	&longopt_flag,	'm'},
		{"m2",	required_argument,	&longopt_flag,	'm'},
		{"m3",	required_argument,	&longopt_flag,	'm'},
		{"m4",	required_argument,	&longopt_flag,	'm'},
		{"m5",	required_argument,	&longopt_flag,	'm'},
		{"m6",	required_argument,	&longopt_flag,	'm'},
		{"m7",	required_argument,	&longopt_flag,	'm'},
		{"tr0",	required_argument,	&longopt_flag,	'q'},
		{"tr1",	required_argument,	&longopt_flag,	'q'},
		{"tr2",	required_argument,	&longopt_flag,	'q'},
		{"tr3",	required_argument,	&longopt_flag,	'q'},
		{"tr4",	required_argument,	&longopt_flag,	'q'},
		{"tr5",	required_argument,	&longopt_flag,	'q'},
		{"tr",	required_argument,	&longopt_flag,	'q'},
		{"p0",	required_argument,	&longopt_flag,	'p'},
		{"p1",	required_argument,	&longopt_flag,	'p'},
		{"p2",	required_argument,	&longopt_flag,	'p'},
		{"p3",	required_argument,	&longopt_flag,	'p'},
		{"p4",	required_argument,	&longopt_flag,	'p'},
		{"p5",	required_argument,	&longopt_flag,	'p'},
		{"p6",	required_argument,	&longopt_flag,	'p'},
		{"p7",	required_argument,	&longopt_flag,	'p'},
		{"allcounters",	no_argument,	&longopt_flag,	'8'},
		{"overflow_delay",	required_argument,	&longopt_flag,	'1'},
		{0, 0, 0, 0}
	};

	while ((c = getopt_long (argc, argv, "hnm:d:a:i:o:t:r:p:q:D", long_options, &option_index)) != -1) {
		// small trick to merge long options with short options of same doaain (-m and --m0 --m1 ...)
		unsigned int long_opt = 0;

		if (c == 0)
		{
			long_opt = 1;
			c = long_options[option_index].val;
		}

		switch (c)
		{
			case 'h':
			{
				unsigned int loop = 0;

				printf("\n\tomapconf trace bw [-h] [<-m | --m<x>> <0xyy | ma_mpu | alldmm | dss | iva | ...>] [<-p | --p<x> <emif1 | emif2>] [<--tr | --tr<x>> <r|w|r+w>] [-d x] [--overflow_delay x] [-a 1 or 2] [-i x] [-o x -t y] [-r 0xaaaaaaaa-0xbbbbbbbb] [-n]\n");
				printf("\n\t-m, -p, -q sets all 8 counters while -m0, --p0, --q0 to --m7, --tr7, --p5 set 1 counter only\n");
				printf("\n\t-m <0xyy | ma_mpu | alldmm | dss | iva | ...> (MA_MPU_1_2 deprecated)\n");
				printf("\t\tMaster initiator monitored. WARNING: All DMM traffic includes DSS, IVA, GPU, ... but not MA_MPU, which requires parallel monitoring \n");
				printf("\t\tma_mpu (MA_MPU_1_2 deprecated) - Non DMM MPU memory traffic, see Examples\n");

				while (match_master[loop].name != NULL)
				{
					printf("\t\t%s 0x%x\n", match_master[loop].name, match_master[loop].value);
					loop++;
				}

				printf("\n\t-d xxx or 0.xx\n");
				printf("\t\tDelay in ms between 2 captures, can be float\n");
				printf("\n\t--overflow_delay xxx or 0.xx\n");
				printf("\t\tDelay in ms after which HW IP is reset to avoid overflow. Disables -o -t options. Can be float.\n");
				printf("\n\t-p <emif1 | emif2> or --p<x> <emif1 | emif2>\n");
				printf("\t\tProbed channel. 1 counter can monitor only EMIF1 or EMIF2\n");
				printf("\n\t--tr <r|w|r+w> or --tr<x> <r|w|r+w>\n");
				printf("\t\tTransaction qualifier. Rd or Wr or Rd+Wr monitoring. HW implementation prevents changing this on last 2 counters\n");
				printf("\n\t-a 1 or 2\n");
				printf("\t\taccumulation type. 2: dump at every capture. 1: dump only at end\n");
				printf("\n\t-i x\n");
				printf("\t\tnumber of iterations (for -a 1). You can Ctrl-C during test, current captures will be displayed\n");
				printf("\n\t-o x -t y \n");
				printf("\t\tindex for overflow handling + threshold to reset HW. Disables auto-reset of HW IP based on time (--overflow_delay). You MUST use them for -a 1\n");
				printf("\t\tUse this option twice to set 2 different thresholds on 2 different counters\n");
				printf("\n\t-r 0xaa-0xbb\n");
				printf("\t\taddress filtering, like 0x9b000000-0x9f000000\n");
				printf("\n\t-n\n");
				printf("\t\tno sleep of 32kHz (work-around for 32kHz reading HW bug). MANDATORY for OMAP5 until fix is found\n");
				printf("\n\t-D\n");
				printf("\t\tdisable statcol (deprecated)\n");
				printf("\n\tExamples:\n");
				printf("\tDefault: --p7 emif2 (this forces use of 8 counters and counter 7 is using emif2 as default probed channel)\n");
				printf("\t\tCounter: 0  Master: alldmm  Transaction: w Probe: emif1\n");
				printf("\t\tCounter: 1  Master: alldmm  Transaction: w Probe: emif2\n");
				printf("\t\tCounter: 2  Master: alldmm  Transaction: r Probe: emif1\n");
				printf("\t\tCounter: 3  Master: alldmm  Transaction: r Probe: emif2\n");
				printf("\t\tCounter: 4  Master: alldmm  Transaction: w Probe: emif1\n");
				printf("\t\tCounter: 5  Master: alldmm  Transaction: w Probe: emif2\n");
				printf("\t\tCounter: 6  Master: alldmm  Transaction: r+w Probe: emif1\n");
				printf("\t\tCounter: 7  Master: alldmm  Transaction: r+w Probe: emif2\n");
				printf("\n\t-m 0x70 -d 1000 -a 2 (often used as -m 0x70 only)\n");
				printf("\t\taccumulation 2 is reading of registers and tracing them immediately\n");
				printf("\t\tFormat is time: time_start time_end delta_time -> Wr_DMM_EMIF1 Wr_DMM_EMIF2 Rd_DMM_EMIF1 Rd_DMM_EMIF2 (MB/s)\n");
				printf("\n\t-m dss -d 0.3 -a 1 -i 40000 -o 2 -t 3000000000\n");
				printf("\t\taccumulation 1 is reading of registers and storing in RAM. Result is dumped at the end with CCS format to reuse\n");
				printf("\t\texisting post-processing. So you must set iterations. Overflow is taken into account. Suits small delays\n");
				printf("\n\t-m MA_MPU -d 1000 -a 2 --overflow_delay 500\n");
				printf("\t\tMA_MPU is MPU memory adaptor, a direct path to EMIF. MA_MPU will display:\n");
				printf("\t\tWr_MA_MPU_EMIF1 Wr_MA_MPU_EMIF2 Rd_MA_MPU_EMIF Rd_MA_MPU_EMIF2 (MB/s)\n");
				printf("\n\t--tr r+w -p emif1 --m0 ma_mpu --m1 ma_mpu --tr1 w --p1 emif2 --m2 gpu_p1 --m3 dss --m4 alldmm --m5 alldmm --p5 emif2\n");
				printf("\t\tCounter: 0  Master: ma_mpu  Transaction: r+w Probe: emif1\n");
				printf("\t\tCounter: 1  Master: ma_mpu  Transaction: w Probe: emif2\n");
				printf("\t\tCounter: 2  Master: gpu_p1  Transaction: r+w Probe: emif1\n");
				printf("\t\tCounter: 3  Master: dss  Transaction: r+w Probe: emif1\n");
				printf("\t\tCounter: 4  Master: alldmm  Transaction: r+w Probe: emif1\n");
				printf("\t\tCounter: 5  Master: alldmm  Transaction: r+w Probe: emif2\n");
				printf("\n\t2 masters + all traffic on EMIF1 and EMIF2: --tr r+w --m0 dss --m1 dss --m2 iva --m3 iva --m6 ma_mpu --m7 ma_mpu\n");
				printf("\tNote that you can monitor more masters if you have identified earlier that traffic is well balanced over EMIF1 and EMIF2, i.e. traffic for this master = 2 * EMIF1 = 2 * EMIF2\n");
				printf("\n\tDefault settings:\n");
				printf("\t\t-m 0xcd -d 1000 -a 2 -i 0 --overflow_delay 1000\n");
				printf("\t\tall initiators, 1000ms delay, accumulation 2, infinite iterations, auto-reset IP after 1 s, i.e. always stop/restart HW IP after 1 capture\n");
				printf("\n\tPost-processing (for -a 1):\n");
				printf("\t\tgit clone git://gitorious.tif.ti.com/omap-video-perf/runperf.git, instrumentation/bandwidth/BWstats_ccsv5.py\n");
				printf("\t\tpython-matplotlib is needed\n");
				printf("\n\tWiki:\n");
				printf("\t\t<http://opbuwiki.dal.design.ti.com/index.php/L3_bus_monitoring_SW_tool>\n\n");

				//sci_global_disable(psci_hdl);
				//sci_close(&psci_hdl);

				return 0;
			}

			case 'm':
			{
				unsigned int index;

				if (long_opt == 1) {
					index = long_options[option_index].name[1] - '0';

					// go up to 6 couhters
					if ((index + 1) > num_use_cases)
						num_use_cases = index + 1;
				}

				if (!strstr(optarg, "ma_mpu")) {
					unsigned int loop = 0;

					if (strstr(optarg, "0x")) {
						unsigned int a;
						sscanf(optarg, "%x", &a);
						while (match_master[loop].name != NULL)
						{
							if (match_master[loop].value == a)
								break;
							loop++;
						}
					}
					else {
						while (match_master[loop].name != NULL)
						{
							if (!strcmp(match_master[loop].name, optarg))
								break;
							loop++;
						}
					}

					if (match_master[loop].name != NULL) {
						if (long_opt == 1) {
							pmy_cfg[index]->filter[0].mstr_addr_match = match_master[loop].value;
							if (pmy_cfg[index]->probe_id == SCI_MA_MPU_P1)
								pmy_cfg[index]->probe_id = SCI_EMIF1;
							if (pmy_cfg[index]->probe_id == SCI_MA_MPU_P2)
								pmy_cfg[index]->probe_id = SCI_EMIF2;
						}
						else {
							unsigned int i;

							for (i = 0; i < sizeof(pmy_cfg)/sizeof(struct sci_config_sdram *); i++) {
								pmy_cfg[i]->filter[0].mstr_addr_match = match_master[loop].value;
								if (pmy_cfg[i]->probe_id == SCI_MA_MPU_P1)
									pmy_cfg[i]->probe_id = SCI_EMIF1;
								if (pmy_cfg[i]->probe_id == SCI_MA_MPU_P2)
									pmy_cfg[i]->probe_id = SCI_EMIF2;
							}
						}
					}
					// parsing error
					else {
						printf("ERROR: %s option of -m is not recognized\n", optarg);
						goto END;
					}
				}
				else if ( (!strcmp(optarg, "ma_mpu_1_2")) && (long_opt == 0) ) {
					my_config_emif1.probe_id = SCI_MA_MPU_P1;
					my_config_emif1.filter[0].mstr_addr_match = SCI_MASTID_ALL;
					my_config_emif2.probe_id = SCI_MA_MPU_P2;
					my_config_emif2.filter[0].mstr_addr_match = SCI_MASTID_ALL;
					my_config_emif3.probe_id = SCI_MA_MPU_P1;
					my_config_emif3.filter[0].mstr_addr_match = SCI_MASTID_ALL;
					my_config_emif4.probe_id = SCI_MA_MPU_P2;
					my_config_emif5.filter[0].mstr_addr_match = SCI_MASTID_ALL;
					my_config_emif5.probe_id = SCI_MA_MPU_P1;
					my_config_emif6.filter[0].mstr_addr_match = SCI_MASTID_ALL;
					my_config_emif6.probe_id = SCI_MA_MPU_P2;
					my_config_emif6.filter[0].mstr_addr_match = SCI_MASTID_ALL;
					my_config_emif7.probe_id = SCI_MA_MPU_P1;
					my_config_emif7.filter[0].mstr_addr_match = SCI_MASTID_ALL;
					my_config_emif8.probe_id = SCI_MA_MPU_P2;
					my_config_emif8.filter[0].mstr_addr_match = SCI_MASTID_ALL;
				}
				else if (!strcmp(optarg, "ma_mpu")) {
					if (long_opt == 1) {
						pmy_cfg[index]->filter[0].mstr_addr_match = SCI_MASTID_ALL;
						if (pmy_cfg[index]->probe_id == SCI_EMIF1)
							pmy_cfg[index]->probe_id = SCI_MA_MPU_P1;
						if (pmy_cfg[index]->probe_id == SCI_EMIF2)
							pmy_cfg[index]->probe_id = SCI_MA_MPU_P2;
						}
					else {
						unsigned int i;

						for (i = 0; i < sizeof(pmy_cfg)/sizeof(struct sci_config_sdram *); i++) {
							pmy_cfg[i]->filter[0].mstr_addr_match = SCI_MASTID_ALL;
							if (pmy_cfg[i]->probe_id == SCI_EMIF1)
								pmy_cfg[i]->probe_id = SCI_MA_MPU_P1;
							if (pmy_cfg[i]->probe_id == SCI_EMIF2)
								pmy_cfg[i]->probe_id = SCI_MA_MPU_P2;
						}
					}
				}
				else {
					printf("ERROR: %s option of -m is not recognized\n", optarg);
					goto END;
				}
			}
			break;
			case 'q':
			{
				unsigned int loop = 0;
				unsigned int index;

				if (!strcmp(long_options[option_index].name, "tr"))
					long_opt = 0;

				if (long_opt == 1) {
					index = long_options[option_index].name[2] - '0';

					// go up to 6 couhters
					if ((index + 1) > num_use_cases)
						num_use_cases = index + 1;
				}

				while (match_qualifier[loop].name != NULL)
				{
					if (!strcmp(match_qualifier[loop].name, optarg))
						break;
					loop++;
				}

				if (match_qualifier[loop].name != NULL) {
					if (long_opt == 1) {
						pmy_cfg[index]->filter[0].trans_qual = match_qualifier[loop].value;
					}
					else {
						unsigned int i;

						for (i = 0; i < sizeof(pmy_cfg)/sizeof(struct sci_config_sdram *); i++) {
							pmy_cfg[i]->filter[0].trans_qual = match_qualifier[loop].value;
						}
					}
				}
				else {
					printf("ERROR: %s option of -q/--qx not recognized\n", optarg);
					goto END;
				}
			}
			break;
			case 'p':
			{
				unsigned int loop = 0;
				unsigned int index = 0;

				if (long_opt == 1) {
					index = long_options[option_index].name[1] - '0';

					// go up to 6 couhters
					if ((index + 1) > num_use_cases)
						num_use_cases = index + 1;
				}

				while (match_probe[loop].name != NULL)
				{
					if (!strcmp(match_probe[loop].name, optarg))
						break;
					loop++;
				}

				if (match_probe[loop].name != NULL) {
					if (long_opt == 1) {
						if (pmy_cfg[index]->probe_id == SCI_MA_MPU_P1) {
							if (match_probe[loop].value == SCI_EMIF2)
								pmy_cfg[index]->probe_id = SCI_MA_MPU_P2;
						}
						else if (pmy_cfg[index]->probe_id == SCI_MA_MPU_P2) {
							if  (match_probe[loop].value == SCI_EMIF1)
								pmy_cfg[index]->probe_id = SCI_MA_MPU_P1;
						}
						else if (pmy_cfg[index]->probe_id != SCI_MA_MPU_P1 &&
								 pmy_cfg[index]->probe_id != SCI_MA_MPU_P2) {
							pmy_cfg[index]->probe_id = match_probe[loop].value;
						}
					}
					else {
						unsigned int i;

						for (i = 0; i < sizeof(pmy_cfg)/sizeof(struct sci_config_sdram *); i++) {
						if ( (pmy_cfg[i]->probe_id == SCI_MA_MPU_P1) && (match_probe[loop].value == SCI_EMIF2) )
							pmy_cfg[i]->probe_id = SCI_MA_MPU_P2;
						else if ( (pmy_cfg[i]->probe_id == SCI_MA_MPU_P2) && (match_probe[loop].value == SCI_EMIF1) )
							pmy_cfg[i]->probe_id = SCI_MA_MPU_P1;
						else if (pmy_cfg[index]->probe_id != SCI_MA_MPU_P1 &&
								 pmy_cfg[index]->probe_id != SCI_MA_MPU_P2)
							pmy_cfg[i]->probe_id = match_probe[loop].value;
						}
					}
				}
				else {
					printf("ERROR: %s option of -p/--px not recognized\n", optarg);
					goto END;
				}
			}
			break;
			case 'd':
			{
				float a;
				if ( (sscanf(optarg, "%f", &a) > 0) && (a > 0))
					option_delay_us = a * 1000;
				else {
					printf("ERROR: %s option of -d not recognized or wrong\n", optarg);
					goto END;
				}
				if (option_overflow_iterations > 0)
					option_overflow_iterations = option_overflow_delay_us / option_delay_us;
			}
			break;
			case 'a':
				sscanf(optarg, "%u", &option_accumulation_type);
				if ((option_accumulation_type != 1) && (option_accumulation_type != 2)) {
					printf("ERROR: %s option of -a not recognized or wrong\n", optarg);
					goto END;
				}
			break;
			case 'i':
				if (sscanf(optarg, "%u", &option_iterations) == 0) {
					printf("ERROR: %s option of -i not recognized\n", optarg);
					goto END;
				}
			break;
			case 'o':
			{
				static unsigned int o_count = 0;
				unsigned int result;

				if ((sscanf(optarg, "%u", &result) == 0) || (result > 7)) {
					printf("ERROR: %s option of -o not recognized or too high\n", optarg);
					goto END;
				}

				option_overflow_counter_index[1] = result;
				if (o_count++ == 0)
					option_overflow_counter_index[0] = result;
				option_overflow_delay_us = 0;
				option_overflow_iterations = 0;
			}
			break;
			case 't':
			{
				static unsigned int t_count = 0;
				unsigned int result;

				if (sscanf(optarg, "%u", &result) == 0) {
					printf("ERROR: %s option of -t not recognized\n", optarg);
					goto END;
				}

				option_overflow_threshold[1] = result;
				if (t_count++ == 0)
					option_overflow_threshold[0] = result;
				option_overflow_delay_us = 0;
				option_overflow_iterations = 0;
			}
			break;
			case 'n':
				option_nosleep_32k = 1;
			break;
			case '8':
				 num_use_cases = sizeof(pmy_cfg)/sizeof(struct sci_config_sdram *);
			break;
			case '1':
			{
				float a;
				if ( (sscanf(optarg, "%f", &a) > 0) && (a > 0)) {
					option_overflow_delay_us = a * 1000;
					option_overflow_iterations = option_overflow_delay_us / option_delay_us;
				}
				else {
					printf("ERROR: %s option of --overflow_delay not recognized or wrong\n", optarg);
					goto END;
				}
			}
			break;
			case 'r':
				sscanf(optarg, "0x%x-0x%x", &option_min_addr, &option_max_addr);

				my_config_emif1.addr_filter_min = option_min_addr;
				my_config_emif2.addr_filter_min = option_min_addr;
				my_config_emif3.addr_filter_min = option_min_addr;
				my_config_emif4.addr_filter_min = option_min_addr;
				my_config_emif5.addr_filter_min = option_min_addr;
				my_config_emif6.addr_filter_min = option_min_addr;

				my_config_emif1.addr_filter_max = option_max_addr;
				my_config_emif2.addr_filter_max = option_max_addr;
				my_config_emif3.addr_filter_max = option_max_addr;
				my_config_emif4.addr_filter_max = option_max_addr;
				my_config_emif5.addr_filter_max = option_max_addr;
				my_config_emif6.addr_filter_max = option_max_addr;

				my_config_emif1.addr_filter_enable = true;
				my_config_emif2.addr_filter_enable = true;
				my_config_emif3.addr_filter_enable = true;
				my_config_emif4.addr_filter_enable = true;
				my_config_emif5.addr_filter_enable = true;
				my_config_emif6.addr_filter_enable = true;
				break;
			case 'D':
				option_disable = 1;
			default:
				printf("ERROR: Unknown option\n");
				goto END;
		}
	}

	// Error checking, are there still elements ?
	if (optind < argc)
	{
		printf ("ERROR: non-option ARGV-elements: ");
		while (optind < argc)
			printf ("%s ", argv[optind++]);
		putchar ('\n');
		goto END;
	}

	// Even if above chhanges config of counter 7 and 8, we restore default as they can't filter
	my_config_emif7.filter[0].mstr_addr_match = SCI_MASTID_ALL;
	my_config_emif7.filter[0].trans_qual = SCI_RD_OR_WR_DONTCARE;
	my_config_emif8.filter[0].mstr_addr_match = SCI_MASTID_ALL;
	my_config_emif8.filter[0].trans_qual = SCI_RD_OR_WR_DONTCARE;

	// Describe configuration of counters in human readable format
	for (describe_loop = 0; describe_loop < num_use_cases; describe_loop++) {
		unsigned int a, b, c;
		char *a_name, *b_name, *c_name;
		unsigned int loop = 0, loop_transaction = 0;

		a = pmy_cfg[describe_loop]->filter[0].mstr_addr_match;
		b = pmy_cfg[describe_loop]->filter[0].trans_qual;
		c = pmy_cfg[describe_loop]->probe_id;

		while (match_probe[loop].name != NULL)
		{
			if (match_probe[loop].value == c)
				break;
			loop++;
		}
		if (match_probe[loop].name != NULL) {
			c_name = match_probe[loop].name;
			strcpy(msg[describe_loop], match_probe[loop].name_ccs);
			strcpy(msg_overflow[describe_loop], match_probe[loop].name_ccs);
		}
		else {
			c_name = "ERROR";
			strcpy(msg[describe_loop], "ERROR");
			strcpy(msg_overflow[describe_loop], "ERROR");
		}

		loop_transaction = 0;
		while (match_qualifier[loop_transaction].name != NULL)
		{
			if (match_qualifier[loop_transaction].value == b)
				break;
			loop_transaction++;
		}
		if (match_qualifier[loop_transaction].name != NULL) {
			char temp[20];

			b_name = match_qualifier[loop_transaction].name;
			sprintf(temp, ":%s:", match_qualifier[loop_transaction].name_ccs);
			strcat(msg[describe_loop], temp);
			sprintf(temp, ":%s:", match_qualifier[loop_transaction].name);
			strcat(msg_overflow[describe_loop], temp);
		}
		else {
			b_name = "ERROR";
			strcat(msg[describe_loop], ":ERROR:");
			strcat(msg_overflow[describe_loop], ":ERROR:");
		}

		loop = 0;
		while (match_master[loop].name != NULL)
		{
			if (match_master[loop].value == a)
				break;
			loop++;
		}
		if (match_master[loop].name != NULL) {
			a_name = match_master[loop].name;
			strcat(msg[describe_loop], match_master[loop].name_ccs);
			strcat(msg_overflow[describe_loop], match_master[loop].name_ccs);
		}
		else {
			a_name = "ERROR";
			strcat(msg[describe_loop], "ERROR");
			strcat(msg_overflow[describe_loop], "ERROR");
		}

		if ( (pmy_cfg[describe_loop]->filter[0].mstr_addr_match == SCI_MASTID_ALL) && (pmy_cfg[describe_loop]->probe_id == SCI_MA_MPU_P1)) {
			printf("Counter: %d  Master: ma_mpu  Transaction: %s Probe: emif1\n", describe_loop, b_name);
			sprintf(msg[describe_loop], "EMIF 0:%s:MA_MPU", match_qualifier[loop_transaction].name_ccs);
			sprintf(msg_overflow[describe_loop], "EMIF 0:%s:MA_MPU", match_qualifier[loop_transaction].name);
			continue;
		}
		if ( (pmy_cfg[describe_loop]->filter[0].mstr_addr_match == SCI_MASTID_ALL) && (pmy_cfg[describe_loop]->probe_id == SCI_MA_MPU_P2)) {
			printf("Counter: %d  Master: ma_mpu  Transaction: %s Probe: emif2\n", describe_loop, b_name);
			sprintf(msg[describe_loop], "EMIF 1:%s:MA_MPU", match_qualifier[loop_transaction].name_ccs);
			sprintf(msg_overflow[describe_loop], "EMIF 1:%s:MA_MPU",  match_qualifier[loop_transaction].name);
			continue;
		}

		printf("Counter: %d  Master: %s  Transaction: %s Probe: %s\n", describe_loop, a_name, b_name, c_name);
	}

	printf("delay in us: %u\n", option_delay_us);
	if (option_overflow_iterations > 0)
		printf("overflow delay in us: %u (iterations=%u)\n", option_overflow_delay_us, option_overflow_iterations);
	else
		printf("overflow delay in us: DISABLED (-o -t used)\n");
	printf("accumulation type: %u\n", option_accumulation_type);
	printf("iterations (0=infinite): %u\n", option_iterations);
	if (option_overflow_iterations == 0) {
		printf("Overflow counter index: %u %u\n", option_overflow_counter_index[0], option_overflow_counter_index[1]);
		printf("Overflow threshold: %u %u\n", option_overflow_threshold[0], option_overflow_threshold[1]);
	}
	else {
		printf("Overflow counter index: DISABLED (overflow delay used)\n");
		printf("Overflow threshold: DISABLED (overflow delay used)\n");
	}

	if (option_iterations > MAX_ITERATIONS) {
		option_iterations = MAX_ITERATIONS;
		printf("WARNING: MAX_ITERATIONS(%d) exceeded\n", option_iterations);
	}

	powerdm_emu_enable();

	/////////////////////////////////////////////////////
	//Make sure DebugSS is powered up and enabled      //
	/////////////////////////////////////////////////////
	my_sci_config.errhandler = sci_errhandler;
	my_sci_config.data_options = 0;         //Disable options
	my_sci_config.trigger_enable = false;
	my_sci_config.sdram_msg_rate = 1;
	my_sci_config.mstr_msg_rate = 1;
	my_sci_config.mode = SCI_MODE_DUMP;

	addr_32k = mem_map_32k();

	my_sci_err = sci_open(&psci_hdl, &my_sci_config);

	if (SCI_SUCCESS != my_sci_err) exit(-1);

	{
		uint32_t plib_major_ver;
		uint32_t plib_minor_ver;
		uint32_t plib_func_id;
		uint32_t pmod_func_id;

		sci_get_version(psci_hdl, &plib_major_ver, &plib_minor_ver,
			&plib_func_id, &pmod_func_id );

		if ( plib_func_id != pmod_func_id )
		{
			printf ("Error - func missmatch with device %d %d\n", plib_func_id, pmod_func_id);
			sci_close(&psci_hdl);
			powerdm_emu_disable();
			exit(-1);
		}
	}

	// Test
	{
		unsigned int i, j;

		for (i = 0; i < num_use_cases; i++) {
			my_sci_err = sci_reg_usecase_sdram(psci_hdl, pmy_cfg[i], &my_usecase_key[i] );

			if ( SCI_SUCCESS != my_sci_err) break;

			valid_usecase_cnt++;
		}

		/* If you kill the process, statcoll is left running. this is an option to disable it. We should intercept and handle signal */
		if (option_disable == 1) {
			sci_global_disable(psci_hdl);
			sci_close(&psci_hdl);
			return 0;
		}

		/* And this is an ugly hack to disable it so that it will reset counters at enable */
		sci_global_disable(psci_hdl);

		if (option_nosleep_32k)
			nosleep_32k_enable();

		if (valid_usecase_cnt == num_use_cases)
		{
			uint32_t *counters_current = counters;
			unsigned int tests_overflow = 1;

			if (option_accumulation_type == 1) {
				for (tests = 0; tests < (option_iterations * 9); tests++)
					counters[tests] = 0;

				my_sci_err = sci_global_enable(psci_hdl);

				for (tests = 0; tests < option_iterations; tests++) {
					usleep(option_delay_us);
					*(counters_current + TIMESTAMP_INDEX) = GET_32K;
					sci_dump_sdram_cntrs(num_use_cases, counters_current + COUNTER_INDEX);

					if (    ( (option_overflow_iterations > 0) && (tests_overflow > option_overflow_iterations) )
					     || (   (option_overflow_iterations == 0)
					         && (   (*(counters_current + COUNTER_INDEX + option_overflow_counter_index[0]) >= option_overflow_threshold[0])
					             || (*(counters_current + COUNTER_INDEX + option_overflow_counter_index[1]) >= option_overflow_threshold[1])
					            )
					        )
					   ) {
						sci_global_disable(psci_hdl);
						sci_global_enable(psci_hdl);
						counters_current += SAMPLE_SIZE;
						*(counters_current + TIMESTAMP_INDEX) = GET_32K;
						sci_dump_sdram_cntrs(num_use_cases, counters_current + COUNTER_INDEX);
						tests++;
						tests_overflow = 1;
						//printf("overflow %u\n", *counters_current - counters[0]);
					}
					counters_current += SAMPLE_SIZE;
					tests_overflow++;
				}
			}
			else {
				uint32_t *counters_prev;
				uint32_t *counters_overflow;
				unsigned int overflow_on;
				uint32_t delta_time;
				unsigned int tests_overflow = 1;

				for (i = 0; i < sizeof(counters)/4; i++)
					counters[i] = 0;
				counters_prev = counters;
				counters_current = counters + SAMPLE_SIZE;
				counters_overflow = counters + 2 * SAMPLE_SIZE;

				sci_global_enable(psci_hdl);
				*(counters_prev + TIMESTAMP_INDEX) = GET_32K;
				sci_dump_sdram_cntrs(num_use_cases, counters_prev + COUNTER_INDEX);

				for (;;) {
					tests_overflow++;

					usleep(option_delay_us);
					*(counters_current + TIMESTAMP_INDEX) = GET_32K;
					sci_dump_sdram_cntrs(num_use_cases, counters_current + COUNTER_INDEX);


					if (    ( (option_overflow_iterations > 0) && (tests_overflow > option_overflow_iterations) )
					     || (   (option_overflow_iterations == 0)
		        			 && (   (*(counters_current + COUNTER_INDEX + option_overflow_counter_index[0]) >= option_overflow_threshold[0])
					             || (*(counters_current + COUNTER_INDEX + option_overflow_counter_index[1]) >= option_overflow_threshold[1])
					            )
					        )
					   ) {
						sci_global_disable(psci_hdl);
						sci_global_enable(psci_hdl);
						*(counters_overflow + TIMESTAMP_INDEX) = GET_32K;
						sci_dump_sdram_cntrs(num_use_cases, counters_overflow + COUNTER_INDEX);
						overflow_on = 1;
						tests_overflow = 1;
					}

					/* trace current - prev */
					delta_time = *(counters_current + TIMESTAMP_INDEX) - *(counters_prev + TIMESTAMP_INDEX);
					printf("time: %u %u %u -> ", *(counters_current + TIMESTAMP_INDEX), *(counters_prev + TIMESTAMP_INDEX), delta_time);
					for (j = 0; j < num_use_cases; j++) {
						printf("%.2f ", ((float)(*(counters_current + COUNTER_INDEX + j) - *(counters_prev + COUNTER_INDEX + j))/1000000)*32768.0/delta_time);
					}
					printf("\n");

					for (j = 0; j < num_use_cases; j++) {
						if (*(counters_current + COUNTER_INDEX + j) == 0xFFFFFFFF) {
							fprintf(stderr, "ERROR: counter %d %s overflowed at time %u, don't trust results\n", j, msg[j], *(counters_current + TIMESTAMP_INDEX));
							printf("ERROR: counter %d %s overflowed at time %u, don't trust results\n", j, msg[j], *(counters_current + TIMESTAMP_INDEX));
						}
					}

					/* pointers increment */
					if (overflow_on == 1) {
						overflow_on = 0;
						counters_current = counters_overflow;
					}

					// offset all pointers by 1 sample
					counters_prev = counters_current;

					if ((unsigned int)(counters_current - counters) == (2 * SAMPLE_SIZE))
						counters_current = counters;
					else
						counters_current += SAMPLE_SIZE;

					counters_overflow = counters_current;
					if ((unsigned int)(counters_overflow - counters) == (2 * SAMPLE_SIZE))
						counters_overflow = counters;
					else
						counters_overflow += SAMPLE_SIZE;
				}
			}
		}
		else {
			printf(" SCI Lib Error %d\n", my_sci_err);
		}
	}

	sci_killhandler();
END:
	exit(0);
}

void sci_errhandler(psci_handle phandle, const char * func, enum sci_err err)
{
    enum sci_err my_sci_err = SCI_SUCCESS;

    printf("SCILib failure %d in function: %s \n", err, func );

    if (NULL != phandle)
          my_sci_err = sci_close(&phandle);

    if ( my_sci_err )
        exit(-2);
    else
        exit (-3);
}


void nosleep_32k_enable(void)
{
	unsigned int reg = 0;
	unsigned int reg_clk = 0;

	if (cpu_is_omap54xx()) {
		if (cpu_revision_get() == REV_ES1_0)
			reg_clk = OMAP5430ES1_CM_WKUPAON_CLKSTCTRL;
		else
			reg_clk = OMAP5430_CM_WKUPAON_CLKSTCTRL;
	} else if (cpu_is_omap44xx()) {
		reg_clk = OMAP4430_CM_WKUP_CLKSTCTRL;
	}
	mem_read(reg_clk, &reg);
	nosleep_32k_reg = reg & 0x3;
	reg = reg & (~0x3);
	mem_write(reg_clk, reg);
}

void nosleep_32k_disable(void)
{
	unsigned int reg = 0;
	unsigned int reg_clk = 0;

	if (cpu_is_omap54xx()) {
		if (cpu_revision_get() == REV_ES1_0)
			reg_clk = OMAP5430ES1_CM_WKUPAON_CLKSTCTRL;
		else
			reg_clk = OMAP5430_CM_WKUPAON_CLKSTCTRL;
	} else if (cpu_is_omap44xx()) {
		reg_clk = OMAP4430_CM_WKUP_CLKSTCTRL;
	}

	mem_read(reg_clk, &reg);
	reg = reg | nosleep_32k_reg;
	mem_write(reg_clk, reg);
}
