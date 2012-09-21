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
#include <pthread.h>
#include <signal.h>

#include "sci.h"
#include <emu44xx.h>
#include <cm44xx.h>
#include <emu54xx.h>
#include <lib.h>
#include <common/cpuinfo.h>
#include <prm44xx.h>
#include <cm54xx-defs.h>
#include <timr44xx.h>
#include <timr54xx.h>
#include <mem.h>
#include <timestamp_32k.h>

struct sci_config_sdram my_config_emif1 = {
						SCI_SDRAM_THROUGHPUT,
						SCI_EMIF1,
						1,
						{
							{
								SCI_MASTID_ALL,
								0xff,
								SCI_WR_ONLY,
								SCI_ERR_DONTCARE
							}
						}
					};

struct sci_config_sdram my_config_emif2 = {
						SCI_SDRAM_THROUGHPUT,
						SCI_EMIF2,
						1,
						{
							{
								SCI_MASTID_ALL,
								0xff,
								SCI_WR_ONLY,
								SCI_ERR_DONTCARE
							}
						}
					};

struct sci_config_sdram my_config_emif3 = {
						SCI_SDRAM_THROUGHPUT,
						SCI_EMIF1,
						1,
						{
							{
								SCI_MASTID_ALL,
								0xff,
								SCI_RD_ONLY,
								SCI_ERR_DONTCARE
							}
						}
					};

struct sci_config_sdram my_config_emif4 = {
						SCI_SDRAM_THROUGHPUT,
						SCI_EMIF2,
						1,
						{
							{
								SCI_MASTID_ALL,
								0xff,
								SCI_RD_ONLY,
								SCI_ERR_DONTCARE
							}
						}
					};

struct sci_config_sdram my_config_emif5 = {
						SCI_SDRAM_THROUGHPUT,
						SCI_EMIF1,
						1,
						{
							{
								SCI_MSTID_IVA,
								0xff,
								SCI_WR_ONLY,
								SCI_ERR_DONTCARE
							}
						}
					};

struct sci_config_sdram my_config_emif6 = {
						SCI_SDRAM_THROUGHPUT,
						SCI_EMIF2,
						1,
						{
							{
								SCI_MSTID_IVA,
								0xff,
								SCI_WR_ONLY,
								SCI_ERR_DONTCARE
							}
						}
					};

char * msg[] = { "EMIF 0:Wr:All Initiators",
                 "EMIF 1:Wr:All Initiators",
                 "EMIF 0:Rd:All Initiators",
                 "EMIF 1:Rd:All Initiators",
                 "EMIF 0:Rd:IVA",
                 "EMIF 1:Rd:IVA",
                 "EMIF 0:Wr:IVA",
                 "EMIF 1:Rd:IVA",
		};
char * msg_overflow[] = { "EMIF 0:W:All Initiators",
                 "EMIF 1:W:All Initiators",
                 "EMIF 0:R:All Initiators",
                 "EMIF 1:R:All Initiators",
                 "EMIF 0:R:IVA",
                 "EMIF 1:R:IVA",
                 "EMIF 0:W:IVA",
                 "EMIF 1:W:IVA",
		};

struct sci_config_sdram * pmy_cfg[] =  {
					&my_config_emif1,
                                        &my_config_emif2,
                                        &my_config_emif3,
                                        &my_config_emif4,
                                        //&my_config_emif5,
                                        //&my_config_emif6,
					};

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

static volatile unsigned int *addr_32k = NULL;

#define GET_32K *(addr_32k)

#define MAX_ITERATIONS 1000000UL
uint32_t counters[(8+1)*MAX_ITERATIONS];
unsigned int num_use_cases;
unsigned int overflow_counter_index;
unsigned int tests;
unsigned int nosleep_32k_reg;
unsigned int nosleep_32k = 0;
unsigned int accumulation_type;
unsigned int valid_usecase_cnt = 0;
psci_handle psci_hdl = NULL;
psci_usecase_key my_usecase_key[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

void nosleep_32k_enable(void)
{
	unsigned int reg;
	unsigned int reg_clk;

	if (cpu_is_omap54xx())
		reg_clk = OMAP5430_CM_WKUPAON_CLKSTCTRL;
	else if (cpu_is_omap44xx())
		reg_clk = OMAP4430_CM_WKUP_CLKSTCTRL;
	mem_read(reg_clk, &reg);
	nosleep_32k_reg = reg & 0x3;
	reg = reg & (~0x3);
	mem_write(reg_clk, reg);
}

void nosleep_32k_disable(void)
{
	unsigned int reg;
	unsigned int reg_clk;

	if (cpu_is_omap54xx())
		reg_clk = OMAP5430_CM_WKUPAON_CLKSTCTRL;
	else if (cpu_is_omap44xx())
		reg_clk = OMAP4430_CM_WKUP_CLKSTCTRL;

	mem_read(reg_clk, &reg);
	reg = reg | nosleep_32k_reg;
	mem_write(reg_clk, reg);
}

void omapconf_emu_enable_domain()
{
	if (cpu_is_omap44xx())
		//omap4conf_emu_enable_domain();
		mem_write(OMAP4430_CM_L3INSTR_L3_3_CLKCTRL, 0x1);
	else if (cpu_is_omap54xx())
		//omap5conf_emu_enable_domain();
	        mem_write(OMAP5430_CM_L3INSTR_L3_MAIN_3_CLKCTRL, 0x1);
}

void omapconf_emu_disable_domain()
{
	if (cpu_is_omap44xx())
		//omap4conf_emu_disable_domain();
		mem_write(OMAP4430_CM_L3INSTR_L3_3_CLKCTRL, 0);
	else if (cpu_is_omap54xx())
		//omap5conf_emu_disable_domain();
	        mem_write(OMAP5430_CM_L3INSTR_L3_MAIN_3_CLKCTRL, 0x0);
}

void dump_buffer(void)
{
	uint32_t *counters_current = counters;
	unsigned int timestamp0;
	unsigned int i,j;

	fprintf(stderr, "%u iterations finished, dumping to file\n", tests);

	for (i = 0; i < tests - 1; i++)
	{
		unsigned int timestamp = *(counters_current + 1 + num_use_cases);
		if (i == 0) {
			timestamp0 = *counters_current;
			printf("Ref timestamp: %u\n", timestamp0);
		}
		for (j = 0; j < num_use_cases; j++) {
			if ( (*(counters_current + 1 + num_use_cases + 1 + overflow_counter_index) < *(counters_current + 1 + overflow_counter_index)) ) {
				printf("Warning: overflow\n");
				printf("0,0,0,S,,SDRAM,,%u,%s,T,V,%u,,,,0,\n", *(counters_current + 1 + num_use_cases + 1 + j) - *(counters_current + 1 + j), msg_overflow[j], timestamp - timestamp0);
		}
			else {
				printf("0,0,0,S,,SDRAM,,%u,%s,T,V,%u,,,,0,\n", *(counters_current + 1 + num_use_cases + 1 + j) - *(counters_current + 1 + j), msg[j], timestamp - timestamp0);
				}
		}
		counters_current += 1 + num_use_cases;
	}
}

void sci_killhandler(void)
{
	unsigned int i;

	if (accumulation_type == 1)
		dump_buffer();

	mem_unmap_32k(addr_32k);

	if (nosleep_32k)
		nosleep_32k_disable();

	for (i = 0; i < valid_usecase_cnt; i++) {
		sci_remove_usecase( psci_hdl, &my_usecase_key[i]);
	}

	sci_global_disable(psci_hdl);
	sci_close(&psci_hdl);
	omapconf_emu_disable_domain();
}

int statcoll_main(int argc, char **argv)
{
	struct sci_config my_sci_config;
	enum sci_err my_sci_err;
	int c;
	unsigned int delay_us;
	unsigned int iterations;
	unsigned int overflow_threshold;
	unsigned int disable = 0;
	unsigned int min_addr;
	unsigned int max_addr;

	delay_us = 1000000;
	accumulation_type = 2;
	iterations = 0;
	overflow_counter_index = 1;
	overflow_threshold = 0;

	while ((c = getopt (argc, argv, "hnm:d:a:i:o:t:r:D")) != -1) {
		switch (c)
		{
			case 'h':
				printf("\n\tomapconf trace bw [-h] [-m 0xyy or MA_MPU_1_2] [-d x] [-a 1 or 2] [-i x] [-o x -t y] [-r 0xaaaaaaaa-0xbbbbbbbb] [-n]\n");
				printf("\n\t-m 0xaa or MA_MPU_1_2\n");
				printf("\t\tMaster initiator\n");
				printf("\t\tMA_MPU_1_2 - Non DMM MPU memory traffic, see Examples\n");
				printf("\t\tSCI_MASTID_ALL 0x%x\n", SCI_MASTID_ALL);
				printf("\t\tSCI_MSTID_MPUSS 0x%x\n",SCI_MSTID_MPUSS );
				printf("\t\tSCI_MSTID_DAP 0x%x\n", SCI_MSTID_DAP);
				printf("\t\tSCI_MSTID_DSP 0x%x\n", SCI_MSTID_DSP);
				printf("\t\tSCI_MSTID_IVA 0x%x\n", SCI_MSTID_IVA);
				printf("\t\tSCI_MSTID_ISS 0x%x\n", SCI_MSTID_ISS);
				printf("\t\tSCI_MSTID_IPU 0x%x\n", SCI_MSTID_IPU);
				printf("\t\tSCI_MSTID_FDIF 0x%x\n", SCI_MSTID_FDIF);
				printf("\t\tSCI_MSTID_SDMA_RD 0x%x\n", SCI_MSTID_SDMA_RD);
				printf("\t\tSCI_MSTID_SDMA_WR 0x%x\n", SCI_MSTID_SDMA_WR);
				printf("\t\tSCI_MSTID_GPU_P1 0x%x\n", SCI_MSTID_GPU_P1);
				printf("\t\tSCI_MSTID_GPU_P2 0x%x\n", SCI_MSTID_GPU_P2);
				printf("\t\tSCI_MSTID_BB2D_P1 0x%x (GC320)\n", SCI_MSTID_BB2D_P1);
				printf("\t\tSCI_MSTID_BB2D_P2 0x%x (GC320)\n", SCI_MSTID_BB2D_P2);
				printf("\t\tSCI_MSTID_DSS 0x%x\n", SCI_MSTID_DSS);
				printf("\t\tSCI_MSTID_C2C 0x%x\n", SCI_MSTID_C2C);
				printf("\t\tSCI_MSTID_LLI 0x%x\n", SCI_MSTID_LLI);
				printf("\t\tSCI_MSTID_HSI 0x%x\n", SCI_MSTID_HSI);
				printf("\t\tSCI_MSTID_UNIPRO1 0x%x\n", SCI_MSTID_UNIPRO1);
				printf("\t\tSCI_MSTID_UNIPRO2 0x%x\n", SCI_MSTID_UNIPRO2);
				printf("\t\tSCI_MSTID_MMC1 0x%x\n", SCI_MSTID_MMC1);
				printf("\t\tSCI_MSTID_MMC2 0x%x\n", SCI_MSTID_MMC2);
				printf("\t\tSCI_MSTID_SATA 0x%x\n", SCI_MSTID_SATA);
				printf("\t\tSCI_MSTID_USB_HOST_HS 0x%x\n", SCI_MSTID_USB_HOST_HS);
				printf("\t\tSCI_MSTID_USB_OTG_HS 0x%x\n", SCI_MSTID_USB_OTG_HS);
				printf("\n\t-d xxx or 0.xx\n");
				printf("\t\tDelay in ms between 2 captures, can be float\n");
				printf("\n\t-a 1 or 2\n");
				printf("\t\taccumulation type. 2: dump at every capture. 1: dump only at end\n");
				printf("\n\t-i x\n");
				printf("\t\tnumber of iterations (for -a 1). You can Ctrl-C during test, current captures will be displayed\n");
				printf("\n\t-o x -t y \n");
				printf("\t\tindex for overflow handling (0=Wr_EMIF0,1=Wr_EMIF1,2=Rd_EMIF0,3=Rd_EMIF1) + threshold to reset HW. You must use them for -a 1\n");
				printf("\n\t-r 0xaa-0xbb\n");
				printf("\t\taddress filtering, like 0x9b000000-0x9f000000\n");
				printf("\n\t-n\n");
				printf("\t\tno sleep of 32kHz (work-around for 32kHz reading HW bug). MANDATORY for OMAP5 until fix is found\n");
				printf("\n\t-D\n");
				printf("\t\tdisable statcol (deprecated)\n");
				printf("\n\tExamples:\n");
				printf("\t-m 0x70 -d 0.3 -a 1 -i 40000 -o 2 -t 3000000000\n");
				printf("\t\taccumulation 1 is reading of registers and storing in RAM. Result is dumped at the end with CCS format to reuse\n");
				printf("\t\texisting post-processing. So you must set iterations. Overflow is taken into account. Suits small delays\n");
				printf("\n\t-m 0x70 -d 1000 -a 2 -o 2 -t 3000000000 (often used as -m 0x70 only)\n");
				printf("\t\taccumulation 2 is reading of registers and tracing them immediately\n");
				printf("\t\tFormat is time: time_start time_end delta_time -> Wr_EMIF0 Wr_EMIF1 Rd_EMIF0 Rd_EMIF1 (MB/s)\n");
				printf("\n\t-m MA_MPU_1_2 -d 1000 -a 2 -o 2 -t 3000000000\n");
				printf("\t\tMA_MPU is MPU memory adaptor, a direct path to EMIF. There are 2 MA. MA_MPU_1_2 will display:\n");
				printf("\t\tWr_MA_MPU_1 Wr_MA_MPU_2 Rd_MA_MPU_1 Rd_MA_MPU_2 (MB/s)\n");
				printf("\n\tDefault settings:\n");
				printf("\t\t-m 0xcd -d 1000 -a 2 -i 0 -o 0 -t 0\n");
				printf("\t\tall initiators, 1000ms delay, accumulation 2, infinite iterations, overflow on counter 0, threshold=0 i.e. always stop/restart HW IP after 1 capture\n");
				printf("\n\tPost-processing (for -a 1):\n");
				printf("\t\tgit clone git://gitorious.tif.ti.com/omap-video-perf/runperf.git, instrumentation/bandwidth/BWstats_ccsv5.py\n");
				printf("\t\tpython-matplotlib is needed\n");
				printf("\n\tWiki:\n");
				printf("\t\t<http://opbuwiki.dal.design.ti.com/index.php/L3_bus_monitoring_SW_tool>\n\n");

				sci_global_disable(psci_hdl);
				sci_close(&psci_hdl);

				return 0;

			case 'm':
				if (strstr(optarg, "0x")) {
					int a;
					sscanf(optarg, "%x", &a);
					my_config_emif1.filter[0].mstr_addr_match = a;
					my_config_emif2.filter[0].mstr_addr_match = a;
					my_config_emif3.filter[0].mstr_addr_match = a;
					my_config_emif4.filter[0].mstr_addr_match = a;
					printf("Master: %x\n", a);
				}
				else if (strstr(optarg, "ma_mpu_1_2")) {
					my_config_emif1.probe_id = SCI_MA_MPU_P1;
					my_config_emif2.probe_id = SCI_MA_MPU_P2;
					my_config_emif3.probe_id = SCI_MA_MPU_P1;
					my_config_emif4.probe_id = SCI_MA_MPU_P2;
					printf("Master: MA_MPU_1 and MA_MPU_2\n");
				}
			break;
			case 'd':
			{
				float a;
				sscanf(optarg, "%f", &a);
				delay_us = a * 1000;
			}
			break;
			case 'a':
				sscanf(optarg, "%u", &accumulation_type);
			break;
			case 'i':
				sscanf(optarg, "%u", &iterations);
			break;
			case 'o':
				sscanf(optarg, "%u", &overflow_counter_index);
			break;
			case 't':
				sscanf(optarg, "%u", &overflow_threshold);
			break;
			case 'n':
				nosleep_32k = 1;
			break;
			case 'r':
				sscanf(optarg, "0x%x-0x%x", &min_addr, &max_addr);

				my_config_emif1.addr_filter_min = min_addr;
				my_config_emif2.addr_filter_min = min_addr;
				my_config_emif3.addr_filter_min = min_addr;
				my_config_emif4.addr_filter_min = min_addr;

				my_config_emif1.addr_filter_max = max_addr;
				my_config_emif2.addr_filter_max = max_addr;
				my_config_emif3.addr_filter_max = max_addr;
				my_config_emif4.addr_filter_max = max_addr;

				my_config_emif1.addr_filter_enable = true;
				my_config_emif2.addr_filter_enable = true;
				my_config_emif3.addr_filter_enable = true;
				my_config_emif4.addr_filter_enable = true;
				break;
			case 'D':
				disable = 1;
			default:
				printf("Unknown option\n");
		}
	}

	printf("delay in us: %u\n", delay_us);
	printf("accumulation type: %u\n", accumulation_type);
	printf("iterations (0=infinite): %u\n", iterations);
	printf("Overflow counter index: %u\n", overflow_counter_index);
	printf("Overflow threshold: %u\n", overflow_threshold);

	if ((accumulation_type == 1) && (overflow_threshold == 0))
		printf("WARNING: it is not recommended to set -a 1 with -t 0 if -d is small. HW is reset at every capture !\n");

	if (iterations > MAX_ITERATIONS) {
		iterations = MAX_ITERATIONS;
		printf("WARNING: MAX_ITERATIONS(%d) exceeded\n", iterations);
	}

	omapconf_emu_enable_domain();

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
			exit(-1);
		}
	}

	// Test
	{
		unsigned int i, j;

		num_use_cases = sizeof(pmy_cfg)/sizeof(struct sci_config_sdram *);
		for (i = 0; i < num_use_cases; i++) {
			my_sci_err = sci_reg_usecase_sdram(psci_hdl, pmy_cfg[i], &my_usecase_key[i] );

			if ( SCI_SUCCESS != my_sci_err) break;

			valid_usecase_cnt++;
		}

		/* If you kill the process, statcoll is left running. this is an option to disable it. We should intercept and handle signal */
		if (disable == 1) {
			sci_global_disable(psci_hdl);
			sci_close(&psci_hdl);
			return 0;
		}

		/* And this is an ugly hack to disable it so that it will reset counters at enable */
		sci_global_disable(psci_hdl);

		if (nosleep_32k)
			nosleep_32k_enable();

		if (valid_usecase_cnt == num_use_cases)
		{
			uint32_t *counters_current = counters;

			if (accumulation_type == 1) {
				for (tests = 0; tests < (iterations * 9); tests++)
					counters[tests] = 0;

				my_sci_err = sci_global_enable(psci_hdl);

				for (tests = 0; tests < iterations; tests++) {
					usleep(delay_us);
					*counters_current = GET_32K;
					sci_dump_sdram_cntrs(num_use_cases, counters_current + 1);

					if (*(counters_current + 1 + overflow_counter_index) >= overflow_threshold) {
						sci_global_disable(psci_hdl);
						sci_global_enable(psci_hdl);
						counters_current += 1 + num_use_cases;
						*counters_current = GET_32K;
						sci_dump_sdram_cntrs(num_use_cases, counters_current + 1);
						tests++;
						//printf("overflow %u\n", *counters_current - counters[0]);
					}
					counters_current += 1 + num_use_cases;
				}
			}
			else {
				uint32_t *counters_prev;
				uint32_t *counters_overflow;
				unsigned int overflow_on;
				uint32_t delta_time;

				for (i = 0; i < sizeof(counters)/4; i++)
					counters[i] = 0;
				counters_prev = counters;
				counters_current = counters + 1 + num_use_cases;
				counters_overflow = counters + 2 + 2 * num_use_cases;

				sci_global_enable(psci_hdl);
				*counters_prev = GET_32K;
				sci_dump_sdram_cntrs(num_use_cases, counters_prev + 1);

				for (;;) {
					usleep(delay_us);
					*counters_current = GET_32K;
					sci_dump_sdram_cntrs(num_use_cases, counters_current + 1);

					if (*(counters_current + 1 + overflow_counter_index ) >= overflow_threshold) {
						//printf("DEBUG1 %u %u %u %u\n", *counters_prev, *(counters_prev + 1), *(counters_prev + 2), *(counters_prev + 3));
						//printf("DEBUG2 %u %u %u %u\n", *counters_current, *(counters_current + 1), *(counters_current + 2), *(counters_current + 3));
						sci_global_disable(psci_hdl);
						sci_global_enable(psci_hdl);
						*counters_overflow = GET_32K;
						sci_dump_sdram_cntrs(num_use_cases, counters_overflow + 1);
						overflow_on = 1;
					}

					/* trace current - prev */
					delta_time = *counters_current - *counters_prev;
					printf("time: %u %u %u -> ", *counters_current, *counters_prev, delta_time);
					for (j = 0; j < num_use_cases; j++) {
						printf("%.2f ", ((float)(*(counters_current + 1 + j) - *(counters_prev + 1 + j))/1000000)*32768.0/delta_time);
					}
					printf("\n");

					/* pointers increment */
					if (overflow_on == 1) {
						overflow_on = 0;
						printf("Warning: statcoll HW IP reset to avoid overflow (user defined through -o -t)\n");
						counters_current = counters_overflow;
					}

					counters_prev = counters_current;

					if ((unsigned int)(counters_current - counters) == (2 + 2 * num_use_cases))
						counters_current = counters;
					else
						counters_current += 1 + num_use_cases;

					counters_overflow = counters_current;
					if ((unsigned int)(counters_overflow - counters) == (2 + 2 * num_use_cases))
						counters_overflow = counters;
					else
						counters_overflow += 1 + num_use_cases;
				}
			}
		}
		else {
			printf(" SCI Lib Error %d\n", my_sci_err);
		}
	}

	sci_killhandler();

	exit(0);
}
