/*
 *
 * @Component			OMAPCONF
 * @Filename			abb44xx.c
 * @Description			OMAP4 PRCM ABB Definitions & Functions
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


#include <abb44xx.h>
#include <abb.h>
#include <cm44xx.h>
#include <prm44xx.h>
#include <pwrdm44xx.h>
#include <clock44xx.h>
#include <lib44xx.h>
#include <autoadjust_table.h>
#include <help.h>
#include <lib.h>
#include <mem.h>
#include <cpuinfo.h>
#include <string.h>


/* #define ABB44XX_DEBUG */
#ifdef ABB44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

#define PRCM_ABB_REG_TABLE_SIZE        5

static reg_table prcm_abb_reg_table[PRCM_ABB_REG_TABLE_SIZE];
static unsigned int init_done = 0;

static int abb44xx_regtable_init(void);


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		abb44xx_name2addr
 * @BRIEF		retrieve physical address of a register, given its name
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		name: register name
 * @param[in,out]	addr: register address
 * @DESCRIPTION		retrieve physical address of a register, given its name
 *//*------------------------------------------------------------------------ */
int abb44xx_name2addr(char *name, unsigned int *addr)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		abb44xx_regtable_init();

	return name2addr(name, addr, prcm_abb_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		abb44xx_dump
 * @BRIEF		dump PRCM ABB registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		dump PRCM ABB registers
 *//*------------------------------------------------------------------------ */
int abb44xx_dump(void)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		abb44xx_regtable_init();

	return dumpregs(prcm_abb_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		abb44xx_config_show
 * @BRIEF		analyze power configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_INTERNAL
 * @DESCRIPTION		analyze power configuration
 *//*------------------------------------------------------------------------ */
int abb44xx_config_show(void)
{
	double sysclk_rate;
	int ret;
	struct abb_data omap4_abb_data[2];

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	omap4_abb_data[0].name = "MPU Voltage Domain";
	omap4_abb_data[1].name = "IVAHD Voltage Domain";
	ret = mem_read(OMAP4430_PRM_LDO_ABB_MPU_SETUP, &omap4_abb_data[0].setup);
	ret += mem_read(OMAP4430_PRM_LDO_ABB_MPU_CTRL, &omap4_abb_data[0].ctrl);
	ret += mem_read(OMAP4430_PRM_LDO_ABB_IVA_SETUP, &omap4_abb_data[1].setup);
	ret += mem_read(OMAP4430_PRM_LDO_ABB_IVA_CTRL, &omap4_abb_data[1].ctrl);
	if (ret != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	sysclk_rate = clk44xx_get_system_clock_speed();
	if (sysclk_rate <= 0) {
		fprintf(stderr, "%s(): could not retrieve sysclk rate! (%d)\n",
			__func__, (int) sysclk_rate);
		return OMAPCONF_ERR_INTERNAL;
	}

	return abb_config_show(stdout, sysclk_rate, omap4_abb_data, 2);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		abb44xx_main
 * @BRIEF		abb menu
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		abb menu
 *//*------------------------------------------------------------------------ */
int abb44xx_main(int argc, char *argv[])
{
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (argc == 2) {
		if (strcmp(argv[1], "dump") == 0) {
			ret = abb44xx_dump();
		} else if (strcmp(argv[1], "cfg") == 0) {
			ret = abb44xx_config_show();
		} else {
			help(HELP_ABB);
			ret = OMAPCONF_ERR_ARG;
		}
	} else {
		help(HELP_ABB);
		ret = OMAPCONF_ERR_ARG;
	}

	return ret;
}



/* ------------------------------------------------------------------------*//**
 * @FUNCTION		abb44xx_regtable_init
 * @BRIEF		initialize regtable
 * @RETURNS		0
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		initialize regtable
 *//*------------------------------------------------------------------------ */
static int abb44xx_regtable_init(void)
{
	int i = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	/* Init PRCM registers table */
	strcpy(prcm_abb_reg_table[i].name, "PRM_LDO_ABB_MPU_SETUP");
	prcm_abb_reg_table[i++].addr = OMAP4430_PRM_LDO_ABB_MPU_SETUP;
	strcpy(prcm_abb_reg_table[i].name, "PRM_LDO_ABB_MPU_CTRL");
	prcm_abb_reg_table[i++].addr = OMAP4430_PRM_LDO_ABB_MPU_CTRL;
	strcpy(prcm_abb_reg_table[i].name, "PRM_LDO_ABB_IVA_SETUP");
	prcm_abb_reg_table[i++].addr = OMAP4430_PRM_LDO_ABB_IVA_SETUP;
	strcpy(prcm_abb_reg_table[i].name, "PRM_LDO_ABB_IVA_CTRL");
	prcm_abb_reg_table[i++].addr = OMAP4430_PRM_LDO_ABB_IVA_CTRL;
	strcpy(prcm_abb_reg_table[i].name, "END");
	prcm_abb_reg_table[i].addr = 0;

	dprintf("prcm_abb_reg_table last index=%d, size=%d\n", i, i + 1);

	init_done = 1;
	return 0;
}
