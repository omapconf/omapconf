/*
 *
 * @Component			OMAPCONF
 * @Filename			emif44xx.c
 * @Description			OMAP4 EMIF PRCM Definitions & Functions
 * @Author			Patrick Titiano (p-titiano@ti.com)
 * @Date			2010
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
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


#include <lib44xx.h>
#include <help.h>
#include <lib.h>
#include <mem.h>
#include <cpuinfo.h>
#include <string.h>
#include <emif44xx.h>

/* #define EMIF44XX_DEBUG */
#ifdef EMIF44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

#define EMIF_REG_TABLE_SIZE 53

reg_table emif1_reg_table[EMIF_REG_TABLE_SIZE];
reg_table emif2_reg_table[EMIF_REG_TABLE_SIZE];
static unsigned int init_done = 0;

static const unsigned int
	emifs_perf_cnts[EMIF44XX_MAX][EMIF44XX_PERF_CNT_MAX] = {
		{OMAP44XX_EMIF1_PERF_CNT_1, OMAP44XX_EMIF1_PERF_CNT_2},
		{OMAP44XX_EMIF2_PERF_CNT_1, OMAP44XX_EMIF2_PERF_CNT_2} };


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		emif44xx_init_regtable
 * @BRIEF		initialize regtable
 * @RETURNS		0
 *			OMAPCONF_ERR_CPU
 * @param[in]		none
 * @DESCRIPTION		initialize regtable
 *//*------------------------------------------------------------------------ */
int emif44xx_init_regtable(void)
{
	int i = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	/* Init EMIF1 registers table */
	strcpy(emif1_reg_table[i].name, "EMIF1_MOD_ID_REV");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_MOD_ID_REV;
	strcpy(emif1_reg_table[i].name, "EMIF1_STATUS");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_STATUS;
	strcpy(emif1_reg_table[i].name, "EMIF1_SDRAM_CONFIG");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_SDRAM_CONFIG;
	strcpy(emif1_reg_table[i].name, "EMIF1_SDRAM_CONFIG_2");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_SDRAM_CONFIG_2;
	strcpy(emif1_reg_table[i].name, "EMIF1_SDRAM_REF_CTRL");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_SDRAM_REF_CTRL;
	strcpy(emif1_reg_table[i].name, "EMIF1_SDRAM_REF_CTRL_SHDW");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_SDRAM_REF_CTRL_SHDW;
	strcpy(emif1_reg_table[i].name, "EMIF1_SDRAM_TIM_1");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_SDRAM_TIM_1;
	strcpy(emif1_reg_table[i].name, "EMIF1_SDRAM_TIM_1_SHDW");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_SDRAM_TIM_1_SHDW;
	strcpy(emif1_reg_table[i].name, "EMIF1_SDRAM_TIM_2");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_SDRAM_TIM_2;
	strcpy(emif1_reg_table[i].name, "EMIF1_SDRAM_TIM_2_SHDW");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_SDRAM_TIM_2_SHDW;
	strcpy(emif1_reg_table[i].name, "EMIF1_SDRAM_TIM_3");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_SDRAM_TIM_3;
	strcpy(emif1_reg_table[i].name, "EMIF1_SDRAM_TIM_3_SHDW");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_SDRAM_TIM_3_SHDW;
	strcpy(emif1_reg_table[i].name, "EMIF1_LPDDR2_NVM_TIM");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_LPDDR2_NVM_TIM;
	strcpy(emif1_reg_table[i].name, "EMIF1_LPDDR2_NVM_TIM_SHDW");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_LPDDR2_NVM_TIM_SHDW;
	strcpy(emif1_reg_table[i].name, "EMIF1_PWR_MGMT_CTRL");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_PWR_MGMT_CTRL;
	strcpy(emif1_reg_table[i].name, "EMIF1_PWR_MGMT_CTRL_SHDW");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_PWR_MGMT_CTRL_SHDW;
	strcpy(emif1_reg_table[i].name, "EMIF1_LPDDR2_MODE_REG_DATA");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_LPDDR2_MODE_REG_DATA;
	strcpy(emif1_reg_table[i].name, "EMIF1_LPDDR2_MODE_REG_CFG");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_LPDDR2_MODE_REG_CFG;
	strcpy(emif1_reg_table[i].name, "EMIF1_OCP_CONFIG");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_OCP_CONFIG;
	strcpy(emif1_reg_table[i].name, "EMIF1_OCP_CFG_VAL_1");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_OCP_CFG_VAL_1;
	strcpy(emif1_reg_table[i].name, "EMIF1_OCP_CFG_VAL_2");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_OCP_CFG_VAL_2;
	strcpy(emif1_reg_table[i].name, "EMIF1_IODFT_TLGC");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_IODFT_TLGC;
	strcpy(emif1_reg_table[i].name, "EMIF1_IODFT_CTRL_MISR_RSLT");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_IODFT_CTRL_MISR_RSLT;
	strcpy(emif1_reg_table[i].name, "EMIF1_IODFT_ADDR_MISR_RSLT");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_IODFT_ADDR_MISR_RSLT;
	strcpy(emif1_reg_table[i].name, "EMIF1_IODFT_DATA_MISR_RSLT_1");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_IODFT_DATA_MISR_RSLT_1;
	strcpy(emif1_reg_table[i].name, "EMIF1_IODFT_DATA_MISR_RSLT_2");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_IODFT_DATA_MISR_RSLT_2;
	strcpy(emif1_reg_table[i].name, "EMIF1_IODFT_DATA_MISR_RSLT_3");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_IODFT_DATA_MISR_RSLT_3;
	strcpy(emif1_reg_table[i].name, "EMIF1_PERF_CNT_1");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_PERF_CNT_1;
	strcpy(emif1_reg_table[i].name, "EMIF1_PERF_CNT_2");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_PERF_CNT_2;
	strcpy(emif1_reg_table[i].name, "EMIF1_PERF_CNT_CFG");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_PERF_CNT_CFG;
	strcpy(emif1_reg_table[i].name, "EMIF1_PERF_CNT_SEL");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_PERF_CNT_SEL;
	strcpy(emif1_reg_table[i].name, "EMIF1_PERF_CNT_TIM");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_PERF_CNT_TIM;
	strcpy(emif1_reg_table[i].name, "EMIF1_READ_IDLE_CTRL");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_READ_IDLE_CTRL;
	strcpy(emif1_reg_table[i].name, "EMIF1_READ_IDLE_CTRL");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_READ_IDLE_CTRL;
	strcpy(emif1_reg_table[i].name, "EMIF1_READ_IDLE_CTRL_SHDW");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_READ_IDLE_CTRL_SHDW;
	strcpy(emif1_reg_table[i].name, "EMIF1_IRQ_EOI");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_IRQ_EOI;
	strcpy(emif1_reg_table[i].name, "EMIF1_IRQSTATUS_RAW_SYS");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_IRQSTATUS_RAW_SYS;
	strcpy(emif1_reg_table[i].name, "EMIF1_IRQSTATUS_RAW_LL");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_IRQSTATUS_RAW_LL;
	strcpy(emif1_reg_table[i].name, "EMIF1_IRQSTATUS_SYS");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_IRQSTATUS_SYS;
	strcpy(emif1_reg_table[i].name, "EMIF1_IRQSTATUS_LL");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_IRQSTATUS_LL;
	strcpy(emif1_reg_table[i].name, "EMIF1_IRQENABLE_SET_SYS");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_IRQENABLE_SET_SYS;
	strcpy(emif1_reg_table[i].name, "EMIF1_IRQENABLE_SET_LL");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_IRQENABLE_SET_LL;
	strcpy(emif1_reg_table[i].name, "EMIF1_IRQENABLE_SET_LL");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_IRQENABLE_SET_LL;
	strcpy(emif1_reg_table[i].name, "EMIF1_IRQENABLE_CLR_SYS");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_IRQENABLE_CLR_SYS;
	strcpy(emif1_reg_table[i].name, "EMIF1_IRQENABLE_CLR_LL");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_IRQENABLE_CLR_LL;
	strcpy(emif1_reg_table[i].name, "EMIF1_ZQ_CONFIG");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_ZQ_CONFIG;
	strcpy(emif1_reg_table[i].name, "EMIF1_TEMP_ALERT_CONFIG");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_TEMP_ALERT_CONFIG;
	strcpy(emif1_reg_table[i].name, "EMIF1_OCP_ERR_LOG");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_OCP_ERR_LOG;
	strcpy(emif1_reg_table[i].name, "EMIF1_DDR_PHY_CTRL_1");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_DDR_PHY_CTRL_1;
	strcpy(emif1_reg_table[i].name, "EMIF1_DDR_PHY_CTRL_1_SHDW");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_DDR_PHY_CTRL_1_SHDW;
	strcpy(emif1_reg_table[i].name, "EMIF1_DDR_PHY_CTRL_2");
	emif1_reg_table[i++].addr = OMAP44XX_EMIF1_DDR_PHY_CTRL_2;
	strcpy(emif1_reg_table[i].name, "END");
	emif1_reg_table[i].addr = 0;
	dprintf("emif1_reg_table last index=%d, size=%d\n", i, i + 1);

	/* Init EMIF2 registers table */
	i = 0;
	strcpy(emif2_reg_table[i].name, "EMIF2_MOD_ID_REV");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_MOD_ID_REV;
	strcpy(emif2_reg_table[i].name, "EMIF2_STATUS");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_STATUS;
	strcpy(emif2_reg_table[i].name, "EMIF2_SDRAM_CONFIG");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_SDRAM_CONFIG;
	strcpy(emif2_reg_table[i].name, "EMIF2_SDRAM_CONFIG_2");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_SDRAM_CONFIG_2;
	strcpy(emif2_reg_table[i].name, "EMIF2_SDRAM_REF_CTRL");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_SDRAM_REF_CTRL;
	strcpy(emif2_reg_table[i].name, "EMIF2_SDRAM_REF_CTRL_SHDW");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_SDRAM_REF_CTRL_SHDW;
	strcpy(emif2_reg_table[i].name, "EMIF2_SDRAM_TIM_1");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_SDRAM_TIM_1;
	strcpy(emif2_reg_table[i].name, "EMIF2_SDRAM_TIM_1_SHDW");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_SDRAM_TIM_1_SHDW;
	strcpy(emif2_reg_table[i].name, "EMIF2_SDRAM_TIM_2");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_SDRAM_TIM_2;
	strcpy(emif2_reg_table[i].name, "EMIF2_SDRAM_TIM_2_SHDW");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_SDRAM_TIM_2_SHDW;
	strcpy(emif2_reg_table[i].name, "EMIF2_SDRAM_TIM_3");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_SDRAM_TIM_3;
	strcpy(emif2_reg_table[i].name, "EMIF2_SDRAM_TIM_3_SHDW");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_SDRAM_TIM_3_SHDW;
	strcpy(emif2_reg_table[i].name, "EMIF2_LPDDR2_NVM_TIM");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_LPDDR2_NVM_TIM;
	strcpy(emif2_reg_table[i].name, "EMIF2_LPDDR2_NVM_TIM_SHDW");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_LPDDR2_NVM_TIM_SHDW;
	strcpy(emif2_reg_table[i].name, "EMIF2_PWR_MGMT_CTRL");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_PWR_MGMT_CTRL;
	strcpy(emif2_reg_table[i].name, "EMIF2_PWR_MGMT_CTRL_SHDW");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_PWR_MGMT_CTRL_SHDW;
	strcpy(emif2_reg_table[i].name, "EMIF2_LPDDR2_MODE_REG_DATA");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_LPDDR2_MODE_REG_DATA;
	strcpy(emif2_reg_table[i].name, "EMIF2_LPDDR2_MODE_REG_CFG");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_LPDDR2_MODE_REG_CFG;
	strcpy(emif2_reg_table[i].name, "EMIF2_OCP_CONFIG");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_OCP_CONFIG;
	strcpy(emif2_reg_table[i].name, "EMIF2_OCP_CFG_VAL_1");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_OCP_CFG_VAL_1;
	strcpy(emif2_reg_table[i].name, "EMIF2_OCP_CFG_VAL_2");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_OCP_CFG_VAL_2;
	strcpy(emif2_reg_table[i].name, "EMIF2_IODFT_TLGC");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_IODFT_TLGC;
	strcpy(emif2_reg_table[i].name, "EMIF2_IODFT_CTRL_MISR_RSLT");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_IODFT_CTRL_MISR_RSLT;
	strcpy(emif2_reg_table[i].name, "EMIF2_IODFT_ADDR_MISR_RSLT");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_IODFT_ADDR_MISR_RSLT;
	strcpy(emif2_reg_table[i].name, "EMIF2_IODFT_DATA_MISR_RSLT_1");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_IODFT_DATA_MISR_RSLT_1;
	strcpy(emif2_reg_table[i].name, "EMIF2_IODFT_DATA_MISR_RSLT_2");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_IODFT_DATA_MISR_RSLT_2;
	strcpy(emif2_reg_table[i].name, "EMIF2_IODFT_DATA_MISR_RSLT_3");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_IODFT_DATA_MISR_RSLT_3;
	strcpy(emif2_reg_table[i].name, "EMIF2_PERF_CNT_1");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_PERF_CNT_1;
	strcpy(emif2_reg_table[i].name, "EMIF2_PERF_CNT_2");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_PERF_CNT_2;
	strcpy(emif2_reg_table[i].name, "EMIF2_PERF_CNT_CFG");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_PERF_CNT_CFG;
	strcpy(emif2_reg_table[i].name, "EMIF2_PERF_CNT_SEL");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_PERF_CNT_SEL;
	strcpy(emif2_reg_table[i].name, "EMIF2_PERF_CNT_TIM");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_PERF_CNT_TIM;
	strcpy(emif2_reg_table[i].name, "EMIF2_READ_IDLE_CTRL");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_READ_IDLE_CTRL;
	strcpy(emif2_reg_table[i].name, "EMIF2_READ_IDLE_CTRL");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_READ_IDLE_CTRL;
	strcpy(emif2_reg_table[i].name, "EMIF2_READ_IDLE_CTRL_SHDW");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_READ_IDLE_CTRL_SHDW;
	strcpy(emif2_reg_table[i].name, "EMIF2_IRQ_EOI");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_IRQ_EOI;
	strcpy(emif2_reg_table[i].name, "EMIF2_IRQSTATUS_RAW_SYS");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_IRQSTATUS_RAW_SYS;
	strcpy(emif2_reg_table[i].name, "EMIF2_IRQSTATUS_RAW_LL");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_IRQSTATUS_RAW_LL;
	strcpy(emif2_reg_table[i].name, "EMIF2_IRQSTATUS_SYS");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_IRQSTATUS_SYS;
	strcpy(emif2_reg_table[i].name, "EMIF2_IRQSTATUS_LL");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_IRQSTATUS_LL;
	strcpy(emif2_reg_table[i].name, "EMIF2_IRQENABLE_SET_SYS");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_IRQENABLE_SET_SYS;
	strcpy(emif2_reg_table[i].name, "EMIF2_IRQENABLE_SET_LL");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_IRQENABLE_SET_LL;
	strcpy(emif2_reg_table[i].name, "EMIF2_IRQENABLE_SET_LL");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_IRQENABLE_SET_LL;
	strcpy(emif2_reg_table[i].name, "EMIF2_IRQENABLE_CLR_SYS");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_IRQENABLE_CLR_SYS;
	strcpy(emif2_reg_table[i].name, "EMIF2_IRQENABLE_CLR_LL");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_IRQENABLE_CLR_LL;
	strcpy(emif2_reg_table[i].name, "EMIF2_ZQ_CONFIG");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_ZQ_CONFIG;
	strcpy(emif2_reg_table[i].name, "EMIF2_TEMP_ALERT_CONFIG");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_TEMP_ALERT_CONFIG;
	strcpy(emif2_reg_table[i].name, "EMIF2_OCP_ERR_LOG");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_OCP_ERR_LOG;
	strcpy(emif2_reg_table[i].name, "EMIF2_DDR_PHY_CTRL_1");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_DDR_PHY_CTRL_1;
	strcpy(emif2_reg_table[i].name, "EMIF2_DDR_PHY_CTRL_1_SHDW");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_DDR_PHY_CTRL_1_SHDW;
	strcpy(emif2_reg_table[i].name, "EMIF2_DDR_PHY_CTRL_2");
	emif2_reg_table[i++].addr = OMAP44XX_EMIF2_DDR_PHY_CTRL_2;
	strcpy(emif2_reg_table[i].name, "END");
	emif2_reg_table[i].addr = 0;

	init_done = 1;
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		emif44xx_name2addr
 * @BRIEF		retrieve physical address of a register, given its name.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		name: register name
 * @param[in,out]	addr: register address
 * @DESCRIPTION		retrieve physical address of a register, given its name.
 *//*------------------------------------------------------------------------ */
int emif44xx_name2addr(char *name, unsigned int *addr)
{
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		emif44xx_init_regtable();

	ret = name2addr(name, addr, emif1_reg_table);
	if (ret == 0)
		return ret;
	else
		return name2addr(name, addr, emif2_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		emif44xx_perf_cnt_configure
 * @BRIEF		configure emif performance counter
 * @RETURNS		0 in case of success
 * @param[in]		emif_id: EMIF instance
 * @param[in]		cnt_id: performance counter ID
 * @param[in]		filter: filter value
 * @param[in]		conn_id: Also filter on connection (master) ID.
 *			-1 is disabled.
 * @param[in]		addr_sel: Address space (chip select) filtering.
 *			Refer to ENUM
 * @DESCRIPTION		configure emif performance counter
 *//*------------------------------------------------------------------------ */
int emif44xx_perf_cnt_configure(emif44xx_ids emif_id,
	emif44xx_perf_cnt_ids cnt_id, emif44xx_perf_cnt_filter_ids filter,
	int conn_id, emif44xx_memaddrspace addr_sel)
{
	unsigned int addr, data, shift;
	unsigned int enable_conn_id_filtering, enable_addr_filtering;
	unsigned int unsigned_conn_id;
	emif44xx_memaddrspace unsigned_addr_id;
	int ret;

	switch (emif_id) {
	case EMIF44XX_0:
		addr = OMAP44XX_EMIF1_PERF_CNT_CFG;
		switch (cnt_id) {
		case EMIF44XX_PERF_CNT_0:
			shift = 0;
			break;
		case EMIF44XX_PERF_CNT_1:
			shift = 16;
			break;
		default:
			fprintf(stderr, "%s(): bad CNT instance! (%u)!\n",
			__func__, cnt_id);
			return OMAPCONF_ERR_ARG;
		}
		break;
	case EMIF44XX_1:
		addr = OMAP44XX_EMIF2_PERF_CNT_CFG;
		switch (cnt_id) {
		case EMIF44XX_PERF_CNT_0:
			shift = 0;
			break;
		case EMIF44XX_PERF_CNT_1:
			shift = 16;
			break;
		default:
			fprintf(stderr, "%s(): bad CNT instance! (%u)!\n",
			__func__, cnt_id);
			return OMAPCONF_ERR_ARG;
		}
		break;
	default:
		fprintf(stderr, "%s(): bad EMIF instance! (%u)!\n",
			__func__, emif_id);
		return OMAPCONF_ERR_ARG;
	}

	ret = mem_read(addr, &data);
	if (ret != 0) {
		fprintf(stderr, "%s(): error reading EMIF_PERF_CNT_CFG reg!\n",
			__func__);
		return OMAPCONF_ERR_REG_ACCESS;
	}
	dprintf("%s(%d, %d, %d, %d, %d):\n", __func__,
		emif_id, cnt_id, filter, conn_id, addr_sel);

	enable_conn_id_filtering = 0;
	unsigned_conn_id = 0x0;
	if (conn_id >= 0 && conn_id <= 255) {
		unsigned_conn_id = conn_id << 8;
		enable_conn_id_filtering = 1;
	}
	dprintf("  Conn ID Filtering? = 0x%x, 0x%X\n",
		enable_conn_id_filtering, unsigned_conn_id);

	enable_addr_filtering = 0;
	unsigned_addr_id = EMIF44XX_MEMADDRSPACE_CS1ANDCS0;
	if (addr_sel < EMIF44XX_MEMADDRSPACE_DISABLED) {
		unsigned_addr_id = addr_sel << 0;
		enable_addr_filtering = 1;
	}
	dprintf("  Addr Filtering? = 0x%x, 0x%X\n",
		enable_addr_filtering, unsigned_addr_id);

	enable_conn_id_filtering = (enable_conn_id_filtering  << 15) << shift;
	enable_addr_filtering = (enable_addr_filtering  << 14) << shift;
	filter = filter << shift;
	dprintf("  filter = 0x%08X\n", filter);
	dprintf("  EMIF_PERF_CNT_CFG = 0x%08X\n", data);

	data = data & ~(0xFFFF << shift);
	dprintf("  EMIF_PERF_CNT_CFG cleared = 0x%08X\n", data);
	data = data | filter | enable_conn_id_filtering | enable_addr_filtering;
	dprintf(" EMIF_PERF_CNT_CFG | filter = 0x%08X\n", data);

	ret = mem_write(addr, data);
	if (ret != 0) {
		fprintf(stderr, "%s(): error writing EMIF_PERF_CNT_CFG reg!\n",
			__func__);
		return OMAPCONF_ERR_REG_ACCESS;
	}

	/*
	 * Increment addr from OMAP44XX_EMIFn_PERF_CNT_CFG to
	 * OMAP44XX_EMIFn_PERF_CNT_SEL register
	 */
	addr = addr + 0x4;
	ret = mem_read(addr, &data);
	if (ret != 0) {
		fprintf(stderr, "%s(): error reading EMIF_PERF_CNT_SEL reg!\n",
			__func__);
		return OMAPCONF_ERR_REG_ACCESS;
	}
	filter = (unsigned_conn_id | unsigned_addr_id) << shift;

	dprintf("  EMIF_PERF_CNT_SEL = 0x%08X\n", data);
	data = data & ~(0xFFFF << shift);
	dprintf("  EMIF_PERF_CNT_SEL cleared = 0x%08X\n", data);
	data = data | filter ;
	dprintf(" EMIF_PERF_CNT_SEL | filter = 0x%08X\n", data);
	ret = mem_write(addr, data);
	if (ret != 0) {
		fprintf(stderr, "%s(): error writing EMIF_PERF_CNT_SEL reg!\n",
			__func__);
		return OMAPCONF_ERR_REG_ACCESS;
	}


	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		emif44xx_perf_cnt_get_time
 * @BRIEF		return L3 clock cycles elapsed since EMIF is brought
 *			out of reset
 * @RETURNS		L3 clock cycles elapsed since EMIF was reset
 *			0 in case of error
 * @param[in]		emif_id: EMIF instance
 * @DESCRIPTION		return L3 clock cycles elapsed since EMIF is brought
 *			out of reset
 *//*------------------------------------------------------------------------ */
unsigned int emif44xx_perf_cnt_get_time(emif44xx_ids emif_id)
{
	int ret;
	unsigned int addr;
	unsigned int time;

	switch (emif_id) {
	case EMIF44XX_0:
		addr = OMAP44XX_EMIF1_PERF_CNT_TIM;
		break;
	case EMIF44XX_1:
		addr = OMAP44XX_EMIF2_PERF_CNT_TIM;
		break;
	default:
		fprintf(stderr, "%s(): bad EMIF instance! (%u)!\n",
			__func__, emif_id);
		return 0;
	}

	ret = mem_read(addr, &time);
	if (ret != 0) {
		fprintf(stderr, "%s(): error reading PERF_CNT_TIM register!\n",
			__func__);
		return 0;
	}

	return time;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		emif44xx_perf_cnt_get_count
 * @BRIEF		retrieve performance counter value as configured (filtered)
 * @RETURNS		performance counter value as configured
 *			0 in case of error
 * @param[in]		emif_id: EMIF instance
 * @param[in]		cnt_id: performance counter ID
 * @DESCRIPTION		retrieve performance counter value as configured (filtered)
 *//*------------------------------------------------------------------------ */
unsigned int emif44xx_perf_cnt_get_count(emif44xx_ids emif_id,
	emif44xx_perf_cnt_ids cnt_id)
{
	int ret;
	unsigned int count;

	#ifdef EMIF44XX_DEBUG
	if ((emif_id >= EMIF44XX_MAX) || (cnt_id >= EMIF44XX_PERF_CNT_MAX)) {
		fprintf(stderr, "%s(): (emif_id (%u) >= EMIF44XX_MAX (%u)) || "
			"(cnt_id (%u) >= EMIF44XX_PERF_CNT_MAX (%u))\n",
			__func__, emif_id, EMIF44XX_MAX,
			cnt_id, EMIF44XX_PERF_CNT_MAX);
		return 0;
	}
	#endif

	ret = mem_read(emifs_perf_cnts[emif_id][cnt_id], &count);
	if (ret != 0) {
		fprintf(stderr, "%s(): error reading EMIF_PERF_CNT register!\n",
			__func__);
		return 0;
	}

	dprintf("%s(%u, %u) = %u\n", __func__, emif_id, cnt_id, count);
	return count;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		emif44xx_cs_count_get
 * @BRIEF		return the number of Chip Select (CS) used
 * @RETURNS		number of Chip Select (CS) used (1 or 2)
 * @DESCRIPTION		return the number of Chip Select (CS) used by analyzing
 *			EMIF[1-2]_SDRAM_CONFIG configuration.
 *//*------------------------------------------------------------------------ */
unsigned char emif44xx_cs_count_get(void)
{
	unsigned int emif1_config, emif2_config;

	CHECK_CPU(44xx, 1);

	/* Read EMIF SDRAM CONFIG register */
	if ((mem_read(OMAP44XX_EMIF1_SDRAM_CONFIG, &emif1_config) != 0) ||
		(mem_read(OMAP44XX_EMIF2_SDRAM_CONFIG, &emif2_config) != 0)) {
		fprintf(stderr, "%s(): could not read EMIF[0-1]_SDRAM_CONFIG!",
			__func__);
		return 1;
	}

	if ((emif1_config & 0x8) != (emif2_config & 0x8)) {
		fprintf(stderr, "%s(): number of chip-selects used by "
			"EMIF1 and EMIF2 do not match!", __func__);
		return 1;
	}

	if (emif1_config & 0x8)
		return 2;
	else
		return 1;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		emif44xx_dump
 * @BRIEF		dump EMIF[1-2] registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		dump EMIF[1-2] registers
 *//*------------------------------------------------------------------------ */
int emif44xx_dump(void)
{
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		emif44xx_init_regtable();

	ret = dumpregs(emif1_reg_table);
	ret |= dumpregs(emif2_reg_table);
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		emif44xx_main
 * @BRIEF		EMIF main menu
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION
 *//*------------------------------------------------------------------------ */
int emif44xx_main(int argc, char *argv[])
{
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (argc == 2) {
		if (strcmp(argv[1], "dump") == 0) {
			if (!init_done)
				emif44xx_init_regtable();
			ret = dumpregs(emif1_reg_table);
			ret = dumpregs(emif2_reg_table);
		} else {
			help(HELP_EMIF);
			ret = OMAPCONF_ERR_ARG;
		}
	} else {
		help(HELP_EMIF);
		ret = OMAPCONF_ERR_ARG;
	}

	return ret;
}
