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

#include "sci_dra.h"
#include <powerdomain.h>
#include <lib.h>
#include <common/cpuinfo.h>
#include <cm_dra7xx-defs.h>
#include <mem.h>
#include <timestamp_32k.h>

struct name_value_dra {
	char *name;
	char *name_ccs;
	unsigned int value;
};

static struct name_value_dra match_master_dra[] = {
	{ "alldmm", "All DMM", SCI_MASTID_ALL_DRA },
	{ "mpu", "MPU", SCI_MSTID_MPU_DRA },
	{ "dap", "DAP", SCI_MSTID_DAP_DRA },
	{ "ieee1500_2_ocp", "IEEE1500_2_OCP", SCI_MSTID_IEEE1500_2_OCP_DRA },
	{ "dsp1_mdma", "DSP1_MDMA", SCI_MSTID_DSP1_MDMA_DRA },
	{ "dsp1_cfg", "DSP1_CFG", SCI_MSTID_DSP1_CFG_DRA },
	{ "dsp1_dma", "DSP1_DMA", SCI_MSTID_DSP1_DMA_DRA },
	{ "dsp2_dma", "DSP2_DMA", SCI_MSTID_DSP2_DMA_DRA },
	{ "dsp2_cfg", "DSP2_CFG", SCI_MSTID_DSP2_CFG_DRA },
	{ "dsp2_mdma", "DSP2_MDMA", SCI_MSTID_DSP2_MDMA_DRA },
	{ "iva_icont1", "IVA_ICONT1", SCI_MSTID_IVA_ICONT1_DRA },
	{ "eve1_p1", "EVE1_P1", SCI_MSTID_EVE1_P1_DRA },
	{ "eve2_p1", "EVE2_P1", SCI_MSTID_EVE2_P1_DRA },
	{ "ipu1", "IPU1", SCI_MSTID_IPU1_DRA },
	{ "ipu2", "IPU2", SCI_MSTID_IPU2_DRA },
	{ "sdma_rd", "SDMA_RD", SCI_MSTID_SDMA_RD_DRA },
	{ "sdma_wr", "SDMA_WR", SCI_MSTID_SDMA_WR_DRA },
	{ "edma_tc1_wr", "EDMA_TC1_WR", SCI_MSTID_EDMA_TC1_WR_DRA },
	{ "edma_tc1_rd", "EDMA_TC1_RD", SCI_MSTID_EDMA_TC1_RD_DRA },
	{ "edma_tc2_wr", "EDMA_TC2_WR", SCI_MSTID_EDMA_TC2_WR_DRA },
	{ "edma_tc2_rd", "EDMA_TC2_RD", SCI_MSTID_EDMA_TC2_RD_DRA },
	{ "dss", "DSS", SCI_MSTID_DSS_DRA},
	{ "mlb", "MLB", SCI_MSTID_MLB_DRA },
	{ "mmu1", "MMU1", SCI_MSTID_MMU1_DRA },
	{ "pcie_ss1", "PCIE_SS1", SCI_MSTID_PCIE_SS1_DRA },
	{ "pcie_ss2", "PCIE_SS2", SCI_MSTID_PCIE_SS2_DRA },
	{ "mmu2", "MMU2", SCI_MSTID_MMU2_DRA },
	{ "vip1_p1", "VIP1_P1", SCI_MSTID_VIP1_P1_DRA },
	{ "vip1_p2", "VIP1_P2", SCI_MSTID_VIP1_P2_DRA },
	{ "vip2_p1", "VIP2_P1", SCI_MSTID_VIP2_P1_DRA },
	{ "vip2_p2", "VIP2_P2", SCI_MSTID_VIP2_P2_DRA },
	{ "vip3_p1", "VIP3_P1", SCI_MSTID_VIP3_P1_DRA },
	{ "vip3_p2", "VIP3_P2", SCI_MSTID_VIP3_P2_DRA },
	{ "vpe_p1", "VPE_P1", SCI_MSTID_VPE_P1_DRA },
	{ "vpe_p2", "VPE_P2", SCI_MSTID_VPE_P2_DRA },
	{ "mmc1", "MMC1", SCI_MSTID_MMC1_DRA },
	{ "gpu_p1", "GPU_P1", SCI_MSTID_GPU_P1_DRA },
	{ "mmc2", "MMC2", SCI_MSTID_MMC2_DRA },
	{ "gpu_p2", "GPU_P2", SCI_MSTID_GPU_P2_DRA },
	{ "bb2d_p1", "BB2D_P1", SCI_MSTID_BB2D_P1_DRA },
	{ "bb2d_p2", "BB2D_P2", SCI_MSTID_BB2D_P2_DRA },
	{ "gmac_sw", "GMAC_SW", SCI_MSTID_GMAC_SW_DRA },
	{ "usb4", "USB4", SCI_MSTID_USB4_DRA },
	{ "usb1", "USB1", SCI_MSTID_USB1_DRA },
	{ "usb2", "USB2", SCI_MSTID_USB2_DRA },
	{ "usb3", "USB3", SCI_MSTID_USB3_DRA },
	{ "sata", "SATA", SCI_MSTID_SATA_DRA },
	{ "eve1_p2", "EVE1_P2", SCI_MSTID_EVE1_P2_DRA },
	{ "eve2_p2", "EVE2_P2", SCI_MSTID_EVE2_P2_DRA },
	{ NULL, NULL, 0 }
};



static struct name_value_dra match_qualifier_dra[] = {
	{ "r", "Rd", SCI_RD_ONLY },
	{ "r+w", "Rd/Wr", SCI_RD_OR_WR_DONTCARE },
	{ "w", "Wr", SCI_WR_ONLY },
	{ NULL, NULL, 0 }
};

static struct name_value_dra match_probe_dra[] = {
	{ "emif1", "EMIF 0", SCI_EMIF1_DRA },
	{ "emif2", "EMIF 1", SCI_EMIF2_DRA },
	{ NULL, NULL, 0 }
};

static struct sci_config_sdram my_config_emif_dra1 = { SCI_SDRAM_THROUGHPUT, SCI_EMIF1_DRA, 1,	{ { SCI_MASTID_ALL_DRA, 0xff, SCI_WR_ONLY, SCI_ERR_DONTCARE } } };
static struct sci_config_sdram my_config_emif_dra2 = { SCI_SDRAM_THROUGHPUT, SCI_EMIF2_DRA, 1,	{ { SCI_MASTID_ALL_DRA, 0xff, SCI_WR_ONLY, SCI_ERR_DONTCARE } } };
static struct sci_config_sdram my_config_emif_dra3 = { SCI_SDRAM_THROUGHPUT, SCI_EMIF1_DRA, 1,	{ { SCI_MASTID_ALL_DRA, 0xff, SCI_RD_ONLY, SCI_ERR_DONTCARE } } };
static struct sci_config_sdram my_config_emif_dra4 = { SCI_SDRAM_THROUGHPUT, SCI_EMIF2_DRA, 1,	{ { SCI_MASTID_ALL_DRA, 0xff, SCI_RD_ONLY, SCI_ERR_DONTCARE } } };
static struct sci_config_sdram my_config_emif_dra5 = { SCI_SDRAM_THROUGHPUT, SCI_EMIF1_DRA, 1,	{ { SCI_MASTID_ALL_DRA, 0xff, SCI_WR_ONLY, SCI_ERR_DONTCARE } } };
static struct sci_config_sdram my_config_emif_dra6 = { SCI_SDRAM_THROUGHPUT, SCI_EMIF2_DRA, 1,	{ { SCI_MASTID_ALL_DRA, 0xff, SCI_WR_ONLY, SCI_ERR_DONTCARE } } };
static struct sci_config_sdram my_config_emif_dra7 = { SCI_SDRAM_THROUGHPUT, SCI_EMIF1_DRA, 0,	{ { SCI_MASTID_ALL_DRA, 0xff, SCI_RD_OR_WR_DONTCARE, SCI_ERR_DONTCARE } } };
static struct sci_config_sdram my_config_emif_dra8 = { SCI_SDRAM_THROUGHPUT, SCI_EMIF2_DRA, 0,	{ { SCI_MASTID_ALL_DRA, 0xff, SCI_RD_OR_WR_DONTCARE, SCI_ERR_DONTCARE } } };

struct sci_config_sdram * pmy_cfg_dra[] =  {
	&my_config_emif_dra1,
	&my_config_emif_dra2,
	&my_config_emif_dra3,
	&my_config_emif_dra4,
	&my_config_emif_dra5,
	&my_config_emif_dra6,
	&my_config_emif_dra7,
	&my_config_emif_dra8
};

#define GET_32K *(addr_32k)
#define MAX_ITERATIONS 1000000UL

static char msg[8][100], msg_overflow[8][100]; /* messages for CCS like output (-a 1 option) */
static volatile unsigned int *addr_32k = NULL; /* 32K timestamping */
static uint32_t counters[(8+1)*MAX_ITERATIONS]; /* timestamp+counters storing in "-a 1" mode */
static unsigned int num_use_cases = 4;
static unsigned int option_overflow_counter_index[2], option_overflow_threshold[2];
static unsigned int option_overflow_iterations;
static unsigned int tests; /* number of tests really executed in case of Ctrl-C */
static unsigned int nosleep_32k_reg; /* -n option */
static unsigned int option_nosleep_32k = 0; /* -n option */
static unsigned int option_accumulation_type; /* -a option */
static unsigned int valid_usecase_cnt = 0;
static psci_handle psci_hdl = NULL;
static psci_usecase_key my_usecase_key[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

/* Generic handling of sample array */
#define SAMPLE_SIZE (1 + num_use_cases) /* sample contains 1 timestamp + x counters*/
#define TIMESTAMP_INDEX (0) /* timestamp is first index in 1 sample */
#define COUNTER_INDEX (1) /* counters are put just after timestamp */

static void nosleep_32k_enable_dra(void)
{
	unsigned int reg;
	unsigned int reg_clk;

	reg_clk = DRA7XX_WKUPAON_CM_CM_WKUPAON_CLKSTCTRL;
	mem_read(reg_clk, &reg);
	nosleep_32k_reg = reg & 0x3;
	reg = reg & (~0x3);
	mem_write(reg_clk, reg);
}

static void nosleep_32k_disable_dra(void)
{
	unsigned int reg;
	unsigned int reg_clk;

	reg_clk = DRA7XX_WKUPAON_CM_CM_WKUPAON_CLKSTCTRL;
	mem_read(reg_clk, &reg);
	reg = reg | nosleep_32k_reg;
	mem_write(reg_clk, reg);
}

static void sci_dump_buffer_dra(void)
{
	uint32_t *counters_current = counters;
	unsigned int timestamp0, time;
	unsigned int i,j, tests_overflow;
	unsigned int *prev_counter, *current_counter;
	tests_overflow = 1;
	unsigned int overflow_on = 0;

	fprintf(stderr, "%u iterations finished, dumping to file\n", tests);

	/* for each test, we will compute delta between prev and current and print at current timestamp */
	for (i = 0; i < tests - 1; i++)
	{
		unsigned int timestamp = *(counters_current + TIMESTAMP_INDEX + SAMPLE_SIZE);

		if (i == 0) {
			timestamp0 = *(counters_current + TIMESTAMP_INDEX);
			printf("Ref timestamp: %u\n", timestamp0);
		}
		/* Use relative timestamp */
		time = timestamp - timestamp0;

		/* Detect reset. Sample i triggers reset so sample i+1 delta to i is ignored */
		if (    ( (option_overflow_iterations > 0) && (tests_overflow > option_overflow_iterations) )
				|| (   (option_overflow_iterations == 0)
					&& (   (*(counters_current + COUNTER_INDEX + option_overflow_counter_index[0]) >= option_overflow_threshold[0])
						|| (*(counters_current + COUNTER_INDEX + option_overflow_counter_index[1]) >= option_overflow_threshold[1])
					   )
				   )
		   )
			overflow_on = 1;

		for (j = 0; j < num_use_cases; j++) {
			/* current counter is in fact next sample, i.e. j + sample_size. prev is j */
			current_counter = counters_current + SAMPLE_SIZE + COUNTER_INDEX + j;
			prev_counter = counters_current + COUNTER_INDEX + j;

			/* Overflow at 2^32. We can't fix that */
			if (*current_counter == 0xFFFFFFFF) {
				fprintf(stderr, "ERROR: counter %d %s overflowed at time %u, don't trust results\n", j, msg[j], time);
				printf("ERROR: counter %d %s overflowed at time %u, don't trust results\n", j, msg[j], time);
			}

			/* Dump result. In case of overflow, just print for reference, post-processing will ignore */
			if (overflow_on == 1) {
				printf("Warning: overflow\n");
				printf("0,0,0,S,,SDRAM,,%u,%s,T,V,%u,,,,0,\n", *current_counter - *prev_counter, msg_overflow[j], time);
			}
			else {
				/* HW bug, you read a counter that is < previous value. We fix this by forcing same value than previous sample */
				if (*current_counter < *prev_counter) {
					fprintf(stderr, "WARNING: HW bug, counter %d %s  N-1=%u N=%u at time %u. omapconf fixes it\n", j, msg[j], *prev_counter, *current_counter, time);
					printf("WARNING: HW bug, counter %d %s  N-1=%u N=%u at time %u. omapconf fixes it\n", j, msg[j], *prev_counter, *current_counter, time);
					/* omapconf fix, any value is OK as this is only about deltas */
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

static void sci_killhandler_dra(void)
{
	unsigned int i;

	if (option_accumulation_type == 1)
		sci_dump_buffer_dra();

	mem_unmap_32k(addr_32k);

	if (option_nosleep_32k)
		nosleep_32k_disable_dra();

	for (i = 0; i < valid_usecase_cnt; i++)
		sci_remove_usecase_dra( psci_hdl, &my_usecase_key[i]);

	sci_global_disable_dra(psci_hdl);
	sci_close_dra(&psci_hdl);
	powerdm_emu_disable();
}

static void sci_errhandler_dra(psci_handle phandle, const char * func, enum sci_err_dra err)
{
	enum sci_err_dra my_sci_err = SCI_SUCCESS;

	printf("SCILib failure %d in function: %s \n", err, func );

	if (NULL != phandle)
		my_sci_err = sci_close_dra(&phandle);

	if ( my_sci_err )
		exit(-2);
	else
		exit(-3);
}

static int sci_validate_version(void)
{
	uint32_t plib_major_ver;
	uint32_t plib_minor_ver;
	uint32_t plib_func_id;
	uint32_t pmod_func_id;

	sci_get_version_dra(psci_hdl, &plib_major_ver, &plib_minor_ver,
			&plib_func_id, &pmod_func_id );

	if (plib_func_id != pmod_func_id)
	{
		printf ("Error - func missmatch with device %d %d\n", plib_func_id, pmod_func_id);
		return -1;
	}

	return 0;
}

static int sci_run_test(unsigned int option_disable,
			 unsigned int option_iterations,
			 unsigned int option_delay_us)
{
	unsigned int i, j;
	enum sci_err_dra my_sci_err;

	for (i = 0; i < num_use_cases; i++) {
		my_sci_err = sci_reg_usecase_sdram_dra(psci_hdl, pmy_cfg_dra[i], &my_usecase_key[i] );

		if ( SCI_SUCCESS != my_sci_err) break;

		valid_usecase_cnt++;
	}


	/* If you kill the process, statcoll is left running. this is an option to disable it. We should intercept and handle signal */
	if (option_disable == 1) {
		sci_global_disable_dra(psci_hdl);
		sci_close_dra(&psci_hdl);
		return -1;
	}


	/* And this is an ugly hack to disable it so that it will reset counters at enable */
	sci_global_disable_dra(psci_hdl);

	if (option_nosleep_32k)
		nosleep_32k_enable_dra();

	if (valid_usecase_cnt == num_use_cases)
	{
		uint32_t *counters_current = counters;
		unsigned int tests_overflow = 1;

		if (option_accumulation_type == 1) {
			for (tests = 0; tests < (option_iterations * 9); tests++)
				counters[tests] = 0;

			my_sci_err = sci_global_enable_dra(psci_hdl);

			for (tests = 0; tests < option_iterations; tests++) {
				usleep(option_delay_us);
				*(counters_current + TIMESTAMP_INDEX) = GET_32K;
				sci_dump_sdram_cntrs_dra(num_use_cases, counters_current + COUNTER_INDEX);

				if (    ( (option_overflow_iterations > 0) && (tests_overflow > option_overflow_iterations) )
						|| (   (option_overflow_iterations == 0)
							&& (   (*(counters_current + COUNTER_INDEX + option_overflow_counter_index[0]) >= option_overflow_threshold[0])
								|| (*(counters_current + COUNTER_INDEX + option_overflow_counter_index[1]) >= option_overflow_threshold[1])
							   )
						   )
				   ) {
					sci_global_disable_dra(psci_hdl);
					sci_global_enable_dra(psci_hdl);
					counters_current += SAMPLE_SIZE;
					*(counters_current + TIMESTAMP_INDEX) = GET_32K;
					sci_dump_sdram_cntrs_dra(num_use_cases, counters_current + COUNTER_INDEX);
					tests++;
					tests_overflow = 1;
				}
				counters_current += SAMPLE_SIZE;
				tests_overflow++;
			}
		} else {
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

			sci_global_enable_dra(psci_hdl);
			*(counters_prev + TIMESTAMP_INDEX) = GET_32K;
			sci_dump_sdram_cntrs_dra(num_use_cases, counters_prev + COUNTER_INDEX);

			printf("    %33s ->   %s\n",
				"Time Stamp(32KHz ticks)",
				"Throughput(MB/s)");
			/* Print Header */
			printf("time: %11s %11s %7s -> ",
				"End", "Start", "Delta");
			for (j = 0; j < num_use_cases; j++)
				printf("%9s%d ", "Counter", j);
			printf("\n");
			for (;;) {
				tests_overflow++;

				usleep(option_delay_us);
				*(counters_current + TIMESTAMP_INDEX) = GET_32K;
				sci_dump_sdram_cntrs_dra(num_use_cases, counters_current + COUNTER_INDEX);


				if (    ( (option_overflow_iterations > 0) && (tests_overflow > option_overflow_iterations) )
						|| (   (option_overflow_iterations == 0)
							&& (   (*(counters_current + COUNTER_INDEX + option_overflow_counter_index[0]) >= option_overflow_threshold[0])
								|| (*(counters_current + COUNTER_INDEX + option_overflow_counter_index[1]) >= option_overflow_threshold[1])
							   )
						   )
				   ) {
					sci_global_disable_dra(psci_hdl);
					sci_global_enable_dra(psci_hdl);
					*(counters_overflow + TIMESTAMP_INDEX) = GET_32K;
					sci_dump_sdram_cntrs_dra(num_use_cases, counters_overflow + COUNTER_INDEX);
					overflow_on = 1;
					tests_overflow = 1;
				}

				/* trace current - prev */
				delta_time = *(counters_current + TIMESTAMP_INDEX) - *(counters_prev + TIMESTAMP_INDEX);
				printf("time: %11u %11u %7u -> ",
					*(counters_current + TIMESTAMP_INDEX),
					*(counters_prev + TIMESTAMP_INDEX),
					delta_time);
				for (j = 0; j < num_use_cases; j++) {
					printf("%10.2f ",
						((float)(*(counters_current + COUNTER_INDEX + j) - *(counters_prev + COUNTER_INDEX + j))/1000000)*32768.0/delta_time);
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

				/* offset all pointers by 1 sample */
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
	} else {
		printf(" SCI Lib Error %d\n", my_sci_err);
	}

	return 0;
}

static void sci_print_counter_config(void)
{
	unsigned int describe_loop;

	for (describe_loop = 0; describe_loop < num_use_cases; describe_loop++) {
		unsigned int a, b, c;
		char *a_name, *b_name, *c_name;
		unsigned int loop = 0, loop_transaction = 0;

		a = pmy_cfg_dra[describe_loop]->filter[0].mstr_addr_match;
		b = pmy_cfg_dra[describe_loop]->filter[0].trans_qual;
		c = pmy_cfg_dra[describe_loop]->probe_id;

		while (match_probe_dra[loop].name != NULL)
		{
			if (match_probe_dra[loop].value == c)
				break;
			loop++;
		}
		if (match_probe_dra[loop].name != NULL) {
			c_name = match_probe_dra[loop].name;
			strcpy(msg[describe_loop], match_probe_dra[loop].name_ccs);
			strcpy(msg_overflow[describe_loop], match_probe_dra[loop].name_ccs);
		}
		else {
			c_name = "ERROR";
			strcpy(msg[describe_loop], "ERROR");
			strcpy(msg_overflow[describe_loop], "ERROR");
		}

		loop_transaction = 0;
		while (match_qualifier_dra[loop_transaction].name != NULL)
		{
			if (match_qualifier_dra[loop_transaction].value == b)
				break;
			loop_transaction++;
		}
		if (match_qualifier_dra[loop_transaction].name != NULL) {
			char temp[20];

			b_name = match_qualifier_dra[loop_transaction].name;
			sprintf(temp, ":%s:", match_qualifier_dra[loop_transaction].name_ccs);
			strcat(msg[describe_loop], temp);
			sprintf(temp, ":%s:", match_qualifier_dra[loop_transaction].name);
			strcat(msg_overflow[describe_loop], temp);
		}
		else {
			b_name = "ERROR";
			strcat(msg[describe_loop], ":ERROR:");
			strcat(msg_overflow[describe_loop], ":ERROR:");
		}

		loop = 0;
		while (match_master_dra[loop].name != NULL)
		{
			if (match_master_dra[loop].value == a)
				break;
			loop++;
		}
		if (match_master_dra[loop].name != NULL) {
			a_name = match_master_dra[loop].name;
			strcat(msg[describe_loop], match_master_dra[loop].name_ccs);
			strcat(msg_overflow[describe_loop], match_master_dra[loop].name_ccs);
		}
		else {
			a_name = "ERROR";
			strcat(msg[describe_loop], "ERROR");
			strcat(msg_overflow[describe_loop], "ERROR");
		}

		if ( (pmy_cfg_dra[describe_loop]->filter[0].mstr_addr_match == SCI_MASTID_ALL_DRA) && (pmy_cfg_dra[describe_loop]->probe_id == SCI_MA_MPU_P1_DRA)) {
			sprintf(msg[describe_loop], "EMIF 0:%s:MA_MPU", match_qualifier_dra[loop_transaction].name_ccs);
			sprintf(msg_overflow[describe_loop], "EMIF 0:%s:MA_MPU", match_qualifier_dra[loop_transaction].name);
			a_name = "ma_mpu";
			c_name = "emif1";
			goto print;
		}

		if ( (pmy_cfg_dra[describe_loop]->filter[0].mstr_addr_match == SCI_MASTID_ALL_DRA) && (pmy_cfg_dra[describe_loop]->probe_id == SCI_MA_MPU_P2_DRA)) {
			sprintf(msg[describe_loop], "EMIF 1:%s:MA_MPU", match_qualifier_dra[loop_transaction].name_ccs);
			sprintf(msg_overflow[describe_loop], "EMIF 1:%s:MA_MPU",  match_qualifier_dra[loop_transaction].name);
			a_name = "ma_mpu";
			c_name = "emif2";
			goto print;
		}

print:
		printf("Counter:%2d  Master: %15s Transaction: %2s Probe: %s\n", describe_loop, a_name, b_name, c_name);
	}
	return;
}

static void statcoll_print_help(void)
{
	unsigned int loop = 0;
	char *emif_l = "emif1 | emif2";
	char *star = NULL;

	if (cpu_is_dra72x()) {
		emif_l = "emif1";
		star = "(*)";
	}

	printf("\n\tomapconf trace bw [-h] [<-m | --m<x>> <0xyy | ma_mpu | alldmm | dss | iva | ...>] [<-p | --p<x> <%s>] [<--tr | --tr<x>> <r|w|r+w>] [-d x] [--overflow_delay x] [-a 1 or 2] [-i x] [-o x -t y] [-r 0xaaaaaaaa-0xbbbbbbbb] [-n]\n", emif_l);
	printf("\n\t-m, -p, -q sets all 8 counters while -m0, --p0, --q0 to --m7, --tr7, --p5 set 1 counter only\n");
	printf("\n\t-m <0xyy | ma_mpu | alldmm | dss | iva | ...> (MA_MPU_1_2 deprecated)\n");
	printf("\t\tMaster initiator monitored. WARNING: All DMM traffic includes DSS, IVA, GPU, ... but not MA_MPU, which requires parallel monitoring \n");
	printf("\t\tma_mpu (MA_MPU_1_2 deprecated) - Non DMM MPU memory traffic, see Examples\n");

	while (match_master_dra[loop].name != NULL)
	{
		printf("\t\t%s 0x%x\n", match_master_dra[loop].name, match_master_dra[loop].value);
		loop++;
	}

	printf("\n\t-d xxx or 0.xx\n");
	printf("\t\tDelay in ms between 2 captures, can be float\n");
	printf("\n\t--overflow_delay xxx or 0.xx\n");
	printf("\t\tDelay in ms after which HW IP is reset to avoid overflow. Disables -o -t options. Can be float.\n");
	printf("\n\t-p <%s> or --p<x> <%s>\n", emif_l, emif_l);
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
	printf("\n\t-D\n");
	printf("\t\tdisable statcol (deprecated)\n");
	printf("\n\tExamples:\n");
	printf("\tDefault: --p7 emif1 (this forces use of 8 counters and counter 7 is using emif1 as default probed channel)\n");
	printf("\t\tCounter: 0  Master: alldmm  Transaction: w Probe: emif1\n");
	printf("\t\tCounter: 1  Master: alldmm  Transaction: w Probe: emif2%s\n", star);
	printf("\t\tCounter: 2  Master: alldmm  Transaction: r Probe: emif1\n");
	printf("\t\tCounter: 3  Master: alldmm  Transaction: r Probe: emif2%s\n", star);
	printf("\t\tCounter: 4  Master: alldmm  Transaction: w Probe: emif1\n");
	printf("\t\tCounter: 5  Master: alldmm  Transaction: w Probe: emif2%s\n", star);
	printf("\t\tCounter: 6  Master: alldmm  Transaction: r+w Probe: emif1\n");
	printf("\t\tCounter: 7  Master: alldmm  Transaction: r+w Probe: emif2%s\n", star);
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
	printf("\t\tCounter: 1  Master: ma_mpu  Transaction: w Probe: emif2%s\n", star);
	printf("\t\tCounter: 2  Master: gpu_p1  Transaction: r+w Probe: emif1\n");
	printf("\t\tCounter: 3  Master: dss  Transaction: r+w Probe: emif1\n");
	printf("\t\tCounter: 4  Master: alldmm  Transaction: r+w Probe: emif1\n");
	printf("\t\tCounter: 5  Master: alldmm  Transaction: r+w Probe: emif2%s\n", star);
	printf("\n\t2 masters + all traffic on EMIF1 and EMIF2%s: --tr r+w --m0 dss --m1 dss --m2 iva --m3 iva --m6 ma_mpu --m7 ma_mpu\n", star);
	printf("\tNote that you can monitor more masters if you have identified earlier that traffic is well balanced over EMIF1 and EMIF2, i.e. traffic for this master = 2 * EMIF1 = 2 * EMIF2\n");
	printf("\n\tDefault settings:\n");
	printf("\t\t-m 0xcd -d 1000 -a 2 -i 0 --overflow_delay 1000\n");
	printf("\t\tall initiators, 1000ms delay, accumulation 2, infinite iterations, auto-reset IP after 1 s, i.e. always stop/restart HW IP after 1 capture\n");
	printf("\n\tPost-processing (for -a 1):\n");
	printf("\t\tgit clone git://gitorious.design.ti.com/omap-video-perf/runperf.git [TI internal], instrumentation/bandwidth/BWstats_ccsv5.py\n");
	printf("\t\tpython-matplotlib is needed\n");
	printf("\n\tWiki:\n");
	printf("\t\t<http://www.omappedia.org/wiki/L3_bus_monitoring_SW_tool>\n\n");

	if (cpu_is_dra72x())
		printf("\t\t%sIMPORTANT NOTE: emif2 port is dummy and shows no data\n\n", star);

	return;
}

int statcoll_main_dra(int argc, char **argv)
{
	struct sci_config my_sci_config;
	enum sci_err_dra my_sci_err;
	int c, option_index = 0;
	static int longopt_flag;
	unsigned int option_delay_us;
	unsigned int option_overflow_delay_us;
	unsigned int option_iterations;
	unsigned int option_disable = 0;
	unsigned int option_min_addr;
	unsigned int option_max_addr;
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


	/* Default values of options */
	option_delay_us = 1000000; /* 1 second */
	option_overflow_delay_us = 1000000; /* 1 second */
	option_overflow_iterations = option_overflow_delay_us / option_delay_us;
	option_accumulation_type = 2; /* dump on terminal */
	option_iterations = 0; /* infinite iterations */
	option_overflow_counter_index[0] = 0; /* check counter 0 for overflow */
	option_overflow_counter_index[1] = 0;
	option_overflow_threshold[0] = 0; /* reset at each capture */
	option_overflow_threshold[1] = 0;

	/* J6Eco has no EMIF2, so we set the configs accordingly */
	if (cpu_is_dra72x()) {
		num_use_cases = 2;

		my_config_emif_dra1.probe_id = SCI_EMIF1_DRA;
		my_config_emif_dra2.probe_id = SCI_EMIF1_DRA;
		my_config_emif_dra3.probe_id = SCI_EMIF1_DRA;
		my_config_emif_dra4.probe_id = SCI_EMIF1_DRA;
		my_config_emif_dra5.probe_id = SCI_EMIF1_DRA;
		my_config_emif_dra6.probe_id = SCI_EMIF1_DRA;
		my_config_emif_dra7.probe_id = SCI_EMIF1_DRA;
		my_config_emif_dra8.probe_id = SCI_EMIF1_DRA;

		my_config_emif_dra2.filter[0].trans_qual = SCI_RD_ONLY;
		match_probe_dra[1].name = NULL;
		match_probe_dra[1].name_ccs = NULL;
		match_probe_dra[1].value = 0;
	}

	while ((c = getopt_long (argc, argv, "hnm:d:a:i:o:t:r:p:q:D", long_options, &option_index)) != -1) {
		/* small trick to merge long options with short options of same domain (-m and --m0 --m1 ...) */
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
					statcoll_print_help();
					return 0;
				}

			case 'm':
				{
					unsigned int index;

					if (long_opt == 1) {
						index = long_options[option_index].name[1] - '0';

						/* go up to 6 counters */
						if ((index + 1) > num_use_cases)
							num_use_cases = index + 1;
					}

					if (!strstr(optarg, "ma_mpu")) {
						unsigned int loop = 0;

						if (strstr(optarg, "0x")) {
							unsigned int a;
							sscanf(optarg, "%x", &a);
							while (match_master_dra[loop].name != NULL)
							{
								if (match_master_dra[loop].value == a)
									break;
								loop++;
							}
						}
						else {
							while (match_master_dra[loop].name != NULL)
							{
								if (!strcmp(match_master_dra[loop].name, optarg))
									break;
								loop++;
							}
						}

						if (match_master_dra[loop].name != NULL) {
							if (long_opt == 1) {
								pmy_cfg_dra[index]->filter[0].mstr_addr_match = match_master_dra[loop].value;
								if (pmy_cfg_dra[index]->probe_id == SCI_MA_MPU_P1_DRA)
									pmy_cfg_dra[index]->probe_id = SCI_EMIF1_DRA;
								if (pmy_cfg_dra[index]->probe_id == SCI_MA_MPU_P2_DRA)
									pmy_cfg_dra[index]->probe_id = SCI_EMIF2_DRA;
							}
							else {
								unsigned int i;

								for (i = 0; i < sizeof(pmy_cfg_dra)/sizeof(struct sci_config_sdram *); i++) {
									pmy_cfg_dra[i]->filter[0].mstr_addr_match = match_master_dra[loop].value;
									if (pmy_cfg_dra[i]->probe_id == SCI_MA_MPU_P1_DRA)
										pmy_cfg_dra[i]->probe_id = SCI_EMIF1_DRA;
									if (pmy_cfg_dra[i]->probe_id == SCI_MA_MPU_P2_DRA)
										pmy_cfg_dra[i]->probe_id = SCI_EMIF2_DRA;
								}
							}
						}
						/* parsing error */
						else {
							printf("ERROR: %s option of -m is not recognized\n", optarg);
							goto out;
						}
					}
					else if ( (!strcmp(optarg, "ma_mpu_1_2")) && (long_opt == 0) ) {
						my_config_emif_dra1.probe_id = SCI_MA_MPU_P1_DRA;
						my_config_emif_dra1.filter[0].mstr_addr_match = SCI_MASTID_ALL_DRA;
						my_config_emif_dra2.probe_id = SCI_MA_MPU_P2_DRA;
						my_config_emif_dra2.filter[0].mstr_addr_match = SCI_MASTID_ALL_DRA;
						my_config_emif_dra3.probe_id = SCI_MA_MPU_P1_DRA;
						my_config_emif_dra3.filter[0].mstr_addr_match = SCI_MASTID_ALL_DRA;
						my_config_emif_dra4.probe_id = SCI_MA_MPU_P2_DRA;
						my_config_emif_dra5.filter[0].mstr_addr_match = SCI_MASTID_ALL_DRA;
						my_config_emif_dra5.probe_id = SCI_MA_MPU_P1_DRA;
						my_config_emif_dra6.filter[0].mstr_addr_match = SCI_MASTID_ALL_DRA;
						my_config_emif_dra6.probe_id = SCI_MA_MPU_P2_DRA;
						my_config_emif_dra6.filter[0].mstr_addr_match = SCI_MASTID_ALL_DRA;
						my_config_emif_dra7.probe_id = SCI_MA_MPU_P1_DRA;
						my_config_emif_dra7.filter[0].mstr_addr_match = SCI_MASTID_ALL_DRA;
						my_config_emif_dra8.probe_id = SCI_MA_MPU_P2_DRA;
						my_config_emif_dra8.filter[0].mstr_addr_match = SCI_MASTID_ALL_DRA;
					}
					else if (!strcmp(optarg, "ma_mpu")) {
						if (long_opt == 1) {
							pmy_cfg_dra[index]->filter[0].mstr_addr_match = SCI_MASTID_ALL_DRA;
							if (pmy_cfg_dra[index]->probe_id == SCI_EMIF1_DRA)
								pmy_cfg_dra[index]->probe_id = SCI_MA_MPU_P1_DRA;
							if (pmy_cfg_dra[index]->probe_id == SCI_EMIF2_DRA)
								pmy_cfg_dra[index]->probe_id = SCI_MA_MPU_P2_DRA;
						}
						else {
							unsigned int i;

							for (i = 0; i < sizeof(pmy_cfg_dra)/sizeof(struct sci_config_sdram *); i++) {
								pmy_cfg_dra[i]->filter[0].mstr_addr_match = SCI_MASTID_ALL_DRA;
								if (pmy_cfg_dra[i]->probe_id == SCI_EMIF1_DRA)
									pmy_cfg_dra[i]->probe_id = SCI_MA_MPU_P1_DRA;
								if (pmy_cfg_dra[i]->probe_id == SCI_EMIF2_DRA)
									pmy_cfg_dra[i]->probe_id = SCI_MA_MPU_P2_DRA;
							}
						}
					}
					else {
						printf("ERROR: %s option of -m is not recognized\n", optarg);
						goto out;
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

						/* go up to 6 counters */
						if ((index + 1) > num_use_cases)
							num_use_cases = index + 1;
					}

					while (match_qualifier_dra[loop].name != NULL)
					{
						if (!strcmp(match_qualifier_dra[loop].name, optarg))
							break;
						loop++;
					}

					if (match_qualifier_dra[loop].name != NULL) {
						if (long_opt == 1) {
							pmy_cfg_dra[index]->filter[0].trans_qual = match_qualifier_dra[loop].value;
						}
						else {
							unsigned int i;

							for (i = 0; i < sizeof(pmy_cfg_dra)/sizeof(struct sci_config_sdram *); i++) {
								pmy_cfg_dra[i]->filter[0].trans_qual = match_qualifier_dra[loop].value;
							}
						}
					}
					else {
						printf("ERROR: %s option of -q/--qx not recognized\n", optarg);
						goto out;
					}
				}
				break;
			case 'p':
				{
					unsigned int loop = 0;
					unsigned int index = 0;

					if (long_opt == 1) {
						index = long_options[option_index].name[1] - '0';

						/* go up to 6 counters */
						if ((index + 1) > num_use_cases)
							num_use_cases = index + 1;
					}

					while (match_probe_dra[loop].name != NULL)
					{
						if (!strcmp(match_probe_dra[loop].name, optarg))
							break;
						loop++;
					}

					if (match_probe_dra[loop].name == NULL) {
						printf("ERROR: %s option of -p/--px not recognized\n", optarg);
						goto out;
					}

					if (long_opt == 1) {
						if (pmy_cfg_dra[index]->probe_id == SCI_MA_MPU_P1_DRA) {
							if (match_probe_dra[loop].value == SCI_EMIF2_DRA)
								pmy_cfg_dra[index]->probe_id = SCI_MA_MPU_P2_DRA;
						}
						else if (pmy_cfg_dra[index]->probe_id == SCI_MA_MPU_P2_DRA) {
							if  (match_probe_dra[loop].value == SCI_EMIF1_DRA)
								pmy_cfg_dra[index]->probe_id = SCI_MA_MPU_P1_DRA;
						}
						else if (pmy_cfg_dra[index]->probe_id != SCI_MA_MPU_P1_DRA &&
								 pmy_cfg_dra[index]->probe_id != SCI_MA_MPU_P2_DRA) {
							pmy_cfg_dra[index]->probe_id = match_probe_dra[loop].value;
						}
					} else {
						unsigned int i;

						for (i = 0; i < sizeof(pmy_cfg_dra)/sizeof(struct sci_config_sdram *); i++) {
							if ( (pmy_cfg_dra[i]->probe_id == SCI_MA_MPU_P1_DRA) && (match_probe_dra[loop].value == SCI_EMIF2_DRA) )
								pmy_cfg_dra[i]->probe_id = SCI_MA_MPU_P2_DRA;
							else if ( (pmy_cfg_dra[i]->probe_id == SCI_MA_MPU_P2_DRA) && (match_probe_dra[loop].value == SCI_EMIF1_DRA) )
								pmy_cfg_dra[i]->probe_id = SCI_MA_MPU_P1_DRA;
							else if (pmy_cfg_dra[index]->probe_id != SCI_MA_MPU_P1_DRA &&
									 pmy_cfg_dra[index]->probe_id != SCI_MA_MPU_P2_DRA)
								pmy_cfg_dra[i]->probe_id = match_probe_dra[loop].value;
						}
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
						goto out;
					}
					if (option_overflow_iterations > 0)
						option_overflow_iterations = option_overflow_delay_us / option_delay_us;
				}
				break;
			case 'a':
				sscanf(optarg, "%u", &option_accumulation_type);
				if ((option_accumulation_type != 1) && (option_accumulation_type != 2)) {
					printf("ERROR: %s option of -a not recognized or wrong\n", optarg);
					goto out;
				}
				break;
			case 'i':
				if (sscanf(optarg, "%u", &option_iterations) == 0) {
					printf("ERROR: %s option of -i not recognized\n", optarg);
					goto out;
				}
				break;
			case 'o':
				{
					static unsigned int o_count = 0;
					unsigned int result;

					if ((sscanf(optarg, "%u", &result) == 0) || (result > 7)) {
						printf("ERROR: %s option of -o not recognized or too high\n", optarg);
						goto out;
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
						goto out;
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
				num_use_cases = sizeof(pmy_cfg_dra)/sizeof(struct sci_config_sdram *);
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
						goto out;
					}
				}
				break;
			case 'r':
				sscanf(optarg, "0x%x-0x%x", &option_min_addr, &option_max_addr);

				my_config_emif_dra1.addr_filter_min = option_min_addr;
				my_config_emif_dra2.addr_filter_min = option_min_addr;
				my_config_emif_dra3.addr_filter_min = option_min_addr;
				my_config_emif_dra4.addr_filter_min = option_min_addr;
				my_config_emif_dra5.addr_filter_min = option_min_addr;
				my_config_emif_dra6.addr_filter_min = option_min_addr;

				my_config_emif_dra1.addr_filter_max = option_max_addr;
				my_config_emif_dra2.addr_filter_max = option_max_addr;
				my_config_emif_dra3.addr_filter_max = option_max_addr;
				my_config_emif_dra4.addr_filter_max = option_max_addr;
				my_config_emif_dra5.addr_filter_max = option_max_addr;
				my_config_emif_dra6.addr_filter_max = option_max_addr;

				my_config_emif_dra1.addr_filter_enable = true;
				my_config_emif_dra2.addr_filter_enable = true;
				my_config_emif_dra3.addr_filter_enable = true;
				my_config_emif_dra4.addr_filter_enable = true;
				my_config_emif_dra5.addr_filter_enable = true;
				my_config_emif_dra6.addr_filter_enable = true;
				break;
			case 'D':
				option_disable = 1;
			default:
				printf("ERROR: Unknown option\n");
				goto out;
		}
	}

	/* Error checking, are there still elements ? */
	if (optind < argc)
	{
		printf ("ERROR: non-option ARGV-elements: ");
		while (optind < argc)
			printf ("%s ", argv[optind++]);
		putchar ('\n');
		goto out;
	}

	/* Describe configuration of counters in human readable format */
	sci_print_counter_config();


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

	/* Make sure DebugSS is powered up and enabled */
	my_sci_config.errhandler = sci_errhandler_dra;
	my_sci_config.data_options = 0;         /* Disable options */
	my_sci_config.trigger_enable = false;
	my_sci_config.sdram_msg_rate = 1;
	my_sci_config.mstr_msg_rate = 1;
	my_sci_config.mode = SCI_MODE_DUMP;

	addr_32k = mem_map_32k();

	my_sci_err = sci_open_dra(&psci_hdl, &my_sci_config);

	if (SCI_SUCCESS != my_sci_err) exit(-1);

	if (sci_validate_version()) {
		sci_close_dra(&psci_hdl);
		powerdm_emu_disable();
		exit(-1);
	}

	/* Test */
	if (sci_run_test(option_disable, option_iterations, option_delay_us))
		return -1;

	sci_killhandler_dra();
out:
	exit(0);
}
