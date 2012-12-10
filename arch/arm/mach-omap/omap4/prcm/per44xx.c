/*
 *
 * @Component			OMAPCONF
 * @Filename			per44xx.c
 * @Description			OMAP4 PRCM PER Definitions & Functions
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


#include <per44xx.h>
#include <cm44xx.h>
#include <prm44xx.h>
#include <pwrdm44xx.h>
#include <module44xx.h>
#include <lib44xx.h>
#include <help.h>
#include <lib.h>
#include <mem.h>
#include <cpuinfo.h>
#include <string.h>


/* #define PER44XX_DEBUG */
#ifdef PER44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

#define PRCM_PER_REG_TABLE_SIZE        95

reg_table prcm_per_reg_table[PRCM_PER_REG_TABLE_SIZE];
static unsigned int init_done = 0;

static int per44xx_regtable_init(void);


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		per44xx_name2addr
 * @BRIEF		retrieve physical address of a register, given its name.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		name: register name
 * @param[in,out]	addr: register address
 * @DESCRIPTION		retrieve physical address of a register, given its name.
 *//*------------------------------------------------------------------------ */
int per44xx_name2addr(char *name, unsigned int *addr)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		per44xx_regtable_init();

	return name2addr(name, addr, prcm_per_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		per44xx_config_show
 * @BRIEF		analyze power configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output file stream
 * @DESCRIPTION		analyze power configuration
 *//*------------------------------------------------------------------------ */
int per44xx_config_show(FILE *stream)
{
	unsigned int pm_pwstctrl;
	unsigned int pm_pwstst;
	unsigned int cm_clkstctrl;
	unsigned int rm_context;
	unsigned int cm_clkctrl;
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		per44xx_regtable_init();

	if (mem_read(OMAP4430_PM_L4PER_PWRSTCTRL, &pm_pwstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_PM_L4PER_PWRSTST, &pm_pwstst) != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	if (mem_read(OMAP4430_CM_L4PER_CLKSTCTRL, &cm_clkstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	ret = pwrdm44xx_config_show(stream, "L4_PER",
		OMAP4430_PM_L4PER_PWRSTCTRL, pm_pwstctrl,
		OMAP4430_PM_L4PER_PWRSTST, pm_pwstst);
	if (ret != 0)
		return ret;

	ret = clkdm44xx_config_show(stream, "L4_PER",
		OMAP4430_CM_L4PER_CLKSTCTRL, cm_clkstctrl);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_L4PER_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_L4_PER_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "L4_PER",
		OMAP4430_CM_L4PER_L4PER_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_L4_PER_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_DMTIMER2_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_DMTIMER2_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "GPTIMER2",
		OMAP4430_CM_L4PER_DMTIMER2_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_DMTIMER2_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_DMTIMER3_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_DMTIMER3_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "GPTIMER3",
		OMAP4430_CM_L4PER_DMTIMER3_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_DMTIMER3_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_DMTIMER4_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_DMTIMER4_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "GPTIMER4",
		OMAP4430_CM_L4PER_DMTIMER4_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_DMTIMER4_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_DMTIMER9_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_DMTIMER9_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "GPTIMER9",
		OMAP4430_CM_L4PER_DMTIMER9_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_DMTIMER9_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_DMTIMER10_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_DMTIMER10_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "GPTIMER10",
		OMAP4430_CM_L4PER_DMTIMER10_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_DMTIMER10_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_DMTIMER11_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_DMTIMER11_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "GPTIMER11",
		OMAP4430_CM_L4PER_DMTIMER11_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_DMTIMER11_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_ELM_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_ELM_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "ELM",
		OMAP4430_CM_L4PER_ELM_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_ELM_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_GPIO2_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_GPIO2_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "GPIO2",
		OMAP4430_CM_L4PER_GPIO2_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_GPIO2_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_GPIO3_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_GPIO3_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "GPIO3",
		OMAP4430_CM_L4PER_GPIO3_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_GPIO3_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_GPIO4_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_GPIO4_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "GPIO4",
		OMAP4430_CM_L4PER_GPIO4_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_GPIO4_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_GPIO5_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_GPIO5_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "GPIO5",
		OMAP4430_CM_L4PER_GPIO5_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_GPIO5_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_GPIO6_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_GPIO6_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "GPIO6",
		OMAP4430_CM_L4PER_GPIO6_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_GPIO6_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_HDQ1W_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_HDQ1W_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "HDQ1W",
		OMAP4430_CM_L4PER_HDQ1W_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_HDQ1W_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_I2C1_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_I2C1_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "I2C1",
		OMAP4430_CM_L4PER_I2C1_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_I2C1_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_I2C2_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_I2C2_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "I2C2",
		OMAP4430_CM_L4PER_I2C2_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_I2C2_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_I2C3_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_I2C3_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "I2C3",
		OMAP4430_CM_L4PER_I2C3_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_I2C3_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_I2C4_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_I2C4_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "I2C4",
		OMAP4430_CM_L4PER_I2C4_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_I2C4_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_MCBSP4_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_MCBSP4_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "MCBSP4",
		OMAP4430_CM_L4PER_MCBSP4_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_MCBSP4_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_MCSPI1_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_MCSPI1_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "MCSPI1",
		OMAP4430_CM_L4PER_MCSPI1_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_MCSPI1_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_MCSPI2_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_MCSPI2_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "MCSPI2",
		OMAP4430_CM_L4PER_MCSPI2_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_MCSPI2_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_MCSPI3_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_MCSPI3_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "MCSPI3",
		OMAP4430_CM_L4PER_MCSPI3_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_MCSPI3_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_MCSPI4_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_MCSPI4_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "MCSPI4",
		OMAP4430_CM_L4PER_MCSPI4_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_MCSPI4_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_MMCSD3_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_MMCSD3_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "MMCSD3",
		OMAP4430_CM_L4PER_MMCSD3_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_MMCSD3_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_MMCSD4_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_MMCSD4_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "MMCSD4",
		OMAP4430_CM_L4PER_MMCSD4_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_MMCSD4_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_MMCSD5_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_MMCSD5_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "MMCSD5",
		OMAP4430_CM_L4PER_MMCSD5_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_MMCSD5_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_SLIMBUS2_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_SLIMBUS2_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "SLIMBUS2",
		OMAP4430_CM_L4PER_SLIMBUS2_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_SLIMBUS2_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_UART1_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_UART1_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "UART1",
		OMAP4430_CM_L4PER_UART1_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_UART1_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_UART2_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_UART2_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "UART2",
		OMAP4430_CM_L4PER_UART2_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_UART2_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_UART3_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_UART3_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "UART3",
		OMAP4430_CM_L4PER_UART3_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_UART3_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4PER_UART4_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4PER_UART4_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "UART4",
		OMAP4430_CM_L4PER_UART4_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4PER_UART4_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		per44xx_dependency_show
 * @BRIEF		analyse dependency configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		analyse dependency configuration
 *//*------------------------------------------------------------------------ */
int per44xx_dependency_show(FILE *stream)
{
	unsigned int cm_dynamicdep;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		per44xx_regtable_init();

	if (mem_read(OMAP4430_CM_L4PER_DYNAMICDEP, &cm_dynamicdep) != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	fprintf(stream,
		"|--------------------------------------------------------|\n");
	fprintf(stream,
		"| PER Domain Dependency Configuration | Static | Dynamic |\n");
	fprintf(stream,
		"|-------------------------------------|------------------|\n");
	fprintf(stream,
		"| %-35s | %-6s | %-7s |\n", "L3_INIT",
		"",
		((extract_bit(cm_dynamicdep, 7) == 1) ? "En" : "Dis"));
	fprintf(stream,
		"| %-35s | %-6s | %-7s |\n", "DSS",
		"",
		((extract_bit(cm_dynamicdep, 8) == 1) ? "En" : "Dis"));
	fprintf(stream,
		"|--------------------------------------------------------|\n");
	fprintf(stream, "| %-44s | %-7d |\n", "Window Size",
		extract_bitfield(cm_dynamicdep, 24, 4));
	fprintf(stream,
		"|--------------------------------------------------------|\n");
	fprintf(stream, "\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		per44xx_dump
 * @BRIEF		dump PRCM PER registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		dump PRCM PER registers
 *//*------------------------------------------------------------------------ */
int per44xx_dump(void)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		per44xx_regtable_init();

	return dumpregs(prcm_per_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		per44xx_main
 * @BRIEF		PRCM L4PER main menu
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		PRCM L4PER main menu
 *//*------------------------------------------------------------------------ */
int per44xx_main(int argc, char *argv[])
{
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (argc == 2) {
		if (!init_done)
			per44xx_regtable_init();
		if (strcmp(argv[1], "dump") == 0) {
			ret = dumpregs(prcm_per_reg_table);
		} else if (strcmp(argv[1], "cfg") == 0) {
			ret = per44xx_config_show(stdout);
		} else if (strcmp(argv[1], "dep") == 0) {
			ret = per44xx_dependency_show(stdout);
		} else {
			help(HELP_PRCM);
			ret = OMAPCONF_ERR_ARG;
		}
	} else {
		help(HELP_PRCM);
		ret = OMAPCONF_ERR_ARG;
	}

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		per44xx_regtable_init
 * @BRIEF		initialize regtable
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		initialize regtable
 *//*------------------------------------------------------------------------ */
static int per44xx_regtable_init(void)
{
	int i = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	/* Init PRCM registers table */
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_PWRSTCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_PWRSTCTRL;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_PWRSTST");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_PWRSTST;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_DMTIMER10_WKDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_DMTIMER10_WKDEP;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_DMTIMER10_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_DMTIMER10_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_DMTIMER11_WKDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_DMTIMER11_WKDEP;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_DMTIMER11_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_DMTIMER11_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_DMTIMER2_WKDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_DMTIMER2_WKDEP;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_DMTIMER2_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_DMTIMER2_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_DMTIMER3_WKDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_DMTIMER3_WKDEP;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_DMTIMER3_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_DMTIMER3_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_DMTIMER4_WKDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_DMTIMER4_WKDEP;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_DMTIMER4_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_DMTIMER4_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_DMTIMER9_WKDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_DMTIMER9_WKDEP;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_DMTIMER9_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_DMTIMER9_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_ELM_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_ELM_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_GPIO2_WKDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_GPIO2_WKDEP;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_GPIO2_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_GPIO2_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_GPIO3_WKDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_GPIO3_WKDEP;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_GPIO3_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_GPIO3_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_GPIO4_WKDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_GPIO4_WKDEP;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_GPIO4_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_GPIO4_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_GPIO5_WKDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_GPIO5_WKDEP;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_GPIO5_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_GPIO5_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_GPIO6_WKDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_GPIO6_WKDEP;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_GPIO6_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_GPIO6_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_HDQ1W_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_HDQ1W_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_I2C1_WKDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_I2C1_WKDEP;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_I2C1_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_I2C1_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_I2C2_WKDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_I2C2_WKDEP;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_I2C2_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_I2C2_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_I2C3_WKDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_I2C3_WKDEP;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_I2C3_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_I2C3_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_I2C4_WKDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_I2C4_WKDEP;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_I2C4_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_I2C4_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_L4_PER_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_L4_PER_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_MCBSP4_WKDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_MCBSP4_WKDEP;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_MCBSP4_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_MCBSP4_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_MCSPI1_WKDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_MCSPI1_WKDEP;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_MCSPI1_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_MCSPI1_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_MCSPI2_WKDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_MCSPI2_WKDEP;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_MCSPI2_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_MCSPI2_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_MCSPI3_WKDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_MCSPI3_WKDEP;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_MCSPI3_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_MCSPI3_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_MCSPI4_WKDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_MCSPI4_WKDEP;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_MCSPI4_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_MCSPI4_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_MMCSD3_WKDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_MMCSD3_WKDEP;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_MMCSD3_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_MMCSD3_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_MMCSD4_WKDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_MMCSD4_WKDEP;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_MMCSD4_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_MMCSD4_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_SLIMBUS2_WKDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_SLIMBUS2_WKDEP;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_SLIMBUS2_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_SLIMBUS2_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_UART1_WKDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_UART1_WKDEP;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_UART1_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_UART1_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_UART2_WKDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_UART2_WKDEP;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_UART2_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_UART2_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_UART3_WKDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_UART3_WKDEP;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_UART3_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_UART3_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_UART4_WKDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_UART4_WKDEP;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_UART4_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_UART4_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "PM_L4PER_MMCSD5_WKDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_PM_L4PER_MMCSD5_WKDEP;
	strcpy(prcm_per_reg_table[i].name, "RM_L4PER_MMCSD5_CONTEXT");
	prcm_per_reg_table[i++].addr = OMAP4430_RM_L4PER_MMCSD5_CONTEXT;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_CLKSTCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_CLKSTCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_DYNAMICDEP");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_DYNAMICDEP;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_DMTIMER10_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_DMTIMER10_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_DMTIMER11_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_DMTIMER11_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_DMTIMER2_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_DMTIMER2_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_DMTIMER3_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_DMTIMER3_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_DMTIMER4_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_DMTIMER4_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_DMTIMER9_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_DMTIMER9_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_ELM_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_ELM_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_GPIO2_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_GPIO2_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_GPIO3_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_GPIO3_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_GPIO4_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_GPIO4_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_GPIO5_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_GPIO5_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_GPIO6_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_GPIO6_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_HDQ1W_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_HDQ1W_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_I2C1_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_I2C1_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_I2C2_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_I2C2_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_I2C3_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_I2C3_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_I2C4_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_I2C4_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_L4PER_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_L4PER_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_MCBSP4_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_MCBSP4_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_MCSPI1_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_MCSPI1_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_MCSPI2_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_MCSPI2_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_MCSPI3_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_MCSPI3_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_MCSPI4_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_MCSPI4_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_MMCSD3_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_MMCSD3_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_MMCSD4_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_MMCSD4_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_SLIMBUS2_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_SLIMBUS2_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_UART1_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_UART1_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_UART2_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_UART2_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_UART3_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_UART3_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_UART4_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_UART4_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "CM_L4PER_MMCSD5_CLKCTRL");
	prcm_per_reg_table[i++].addr = OMAP4430_CM_L4PER_MMCSD5_CLKCTRL;
	strcpy(prcm_per_reg_table[i].name, "END");
	prcm_per_reg_table[i].addr = 0;
	dprintf("prcm_per_reg_table last index=%d, size=%d\n", i, i + 1);

	init_done = 1;
	return 0;
}
