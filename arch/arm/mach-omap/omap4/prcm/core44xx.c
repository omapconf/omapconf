/*
 *
 * @Component			OMAPCONF
 * @Filename			core44xx.c
 * @Description			OMAP4 PRCM CORE Definitions & Functions
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


#include <core44xx.h>
#include <cm44xx.h>
#include <prm44xx.h>
#include <pwrdm44xx.h>
#include <module44xx.h>
#include <help.h>
#include <lib.h>
#include <mem.h>
#include <cpuinfo.h>
#include <string.h>


/* #define CORE44XX_DEBUG */
#ifdef CORE44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


#define PRCM_CORE_REG_TABLE_SIZE 70

reg_table prcm_core_reg_table[PRCM_CORE_REG_TABLE_SIZE];
static unsigned int init_done = 0;

static int core44xx_regtable_init(void);


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		core44xx_name2addr
 * @BRIEF		retrieve physical address of a register, given its name.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		name: register name
 * @param[in,out]	addr: register address
 * @DESCRIPTION		retrieve physical address of a register, given its name.
 *//*------------------------------------------------------------------------ */
int core44xx_name2addr(char *name, unsigned int *addr)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		core44xx_regtable_init();

	return name2addr(name, addr, prcm_core_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		core44xx_config_show
 * @BRIEF		analyze CORE power configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output file stream
 * @DESCRIPTION		analyze CORE power configuration
 *//*------------------------------------------------------------------------ */
int core44xx_config_show(FILE *stream)
{
	unsigned int pm_pwstctrl;
	unsigned int pm_pwstst;
	unsigned int cm_clkstctrl;
	unsigned int cm_clkctrl;
	unsigned int rm_context;
	int ret = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		core44xx_regtable_init();

	/* CORE Domain Power Configuration */
	if (mem_read(OMAP4430_PM_CORE_PWRSTCTRL, &pm_pwstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_PM_CORE_PWRSTST, &pm_pwstst) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = pwrdm44xx_config_show(stream, "CORE",
		OMAP4430_PM_CORE_PWRSTCTRL, pm_pwstctrl,
		OMAP4430_PM_CORE_PWRSTST, pm_pwstst);
	if (ret != 0)
		return ret;

	/* L3_1 Clock Domain Configuration */
	if (mem_read(OMAP4430_CM_L3_1_CLKSTCTRL, &cm_clkstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = clkdm44xx_config_show(stream, "L3_1",
		OMAP4430_CM_L3_1_CLKSTCTRL, cm_clkstctrl);
	if (ret != 0)
		return ret;
	/* L3_1 Module Power Configuration */
	if (mem_read(OMAP4430_CM_L3_1_L3_1_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L3_1_L3_1_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "L3_1",
		OMAP4430_CM_L3_1_L3_1_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L3_1_L3_1_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	/* L3_2 Clock Domain Configuration */
	if (mem_read(OMAP4430_CM_L3_2_CLKSTCTRL, &cm_clkstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = clkdm44xx_config_show(stream, "L3_2",
		OMAP4430_CM_L3_2_CLKSTCTRL, cm_clkstctrl);
	if (ret != 0)
		return ret;
	/* L3_2 Modules Power Configuration */
	if (mem_read(OMAP4430_CM_L3_2_L3_2_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L3_2_L3_2_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "L3_2",
		OMAP4430_CM_L3_2_L3_2_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L3_2_L3_2_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L3_2_GPMC_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L3_2_GPMC_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "GPMC",
		OMAP4430_CM_L3_2_GPMC_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L3_2_GPMC_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L3_2_OCMC_RAM_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L3_2_OCMC_RAM_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "OCMC_RAM",
		OMAP4430_CM_L3_2_OCMC_RAM_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L3_2_OCMC_RAM_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	/* MPU_M3 Clock Domain Configuration */
	if (mem_read(OMAP4430_CM_MPU_M3_CLKSTCTRL, &cm_clkstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = clkdm44xx_config_show(stream, "MPU_M3",
		OMAP4430_CM_MPU_M3_CLKSTCTRL, cm_clkstctrl);
	if (ret != 0)
		return ret;
	/* MPU_M3 Module Power Configuration */
	if (mem_read(OMAP4430_CM_MPU_M3_MPU_M3_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_MPU_M3_MPU_M3_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "MPU_M3",
		OMAP4430_CM_MPU_M3_MPU_M3_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_MPU_M3_MPU_M3_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	/* SDMA Clock Domain Configuration */
	if (mem_read(OMAP4430_CM_SDMA_CLKSTCTRL, &cm_clkstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = clkdm44xx_config_show(stream, "SDMA",
		OMAP4430_CM_SDMA_CLKSTCTRL, cm_clkstctrl);
	if (ret != 0)
		return ret;
	/* SDMA Module Power Configuration */
	if (mem_read(OMAP4430_CM_SDMA_SDMA_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_SDMA_SDMA_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "SDMA",
		OMAP4430_CM_SDMA_SDMA_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_SDMA_SDMA_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	/* MEMIF Clock Domain Configuration */
	if (mem_read(OMAP4430_CM_MEMIF_CLKSTCTRL, &cm_clkstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = clkdm44xx_config_show(stream, "MEMIF",
		OMAP4430_CM_MEMIF_CLKSTCTRL, cm_clkstctrl);
	if (ret != 0)
		return ret;
	/* MEMIF Modules Power Configuration */
	if (mem_read(OMAP4430_CM_MEMIF_DMM_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_MEMIF_DMM_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "DMM",
		OMAP4430_CM_MEMIF_DMM_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_MEMIF_DMM_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_MEMIF_EMIF_FW_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_MEMIF_EMIF_FW_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "EMIF_FW",
		OMAP4430_CM_MEMIF_EMIF_FW_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_MEMIF_EMIF_FW_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_MEMIF_EMIF_1_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_MEMIF_EMIF_1_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "EMIF_1",
		OMAP4430_CM_MEMIF_EMIF_1_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_MEMIF_EMIF_1_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_MEMIF_EMIF_2_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_MEMIF_EMIF_2_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "EMIF_2",
		OMAP4430_CM_MEMIF_EMIF_2_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_MEMIF_EMIF_2_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_MEMIF_DLL_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_MEMIF_DLL_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "DLL",
		OMAP4430_CM_MEMIF_DLL_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_MEMIF_DLL_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	/* C2C Clock Domain Configuration */
	if (mem_read(OMAP4430_CM_C2C_CLKSTCTRL, &cm_clkstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = clkdm44xx_config_show(stream, "C2C",
		OMAP4430_CM_C2C_CLKSTCTRL, cm_clkstctrl);
	if (ret != 0)
		return ret;
	/* C2C Modules Power Configuration */
	if (mem_read(OMAP4430_CM_C2C_C2C_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_C2C_C2C_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "C2C",
		OMAP4430_CM_C2C_C2C_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_C2C_C2C_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_C2C_MODEM_ICR_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_C2C_MODEM_ICR_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "MODEM_ICR",
		OMAP4430_CM_C2C_MODEM_ICR_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_C2C_MODEM_ICR_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_C2C_C2C_FW_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_C2C_C2C_FW_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "C2C_FW",
		OMAP4430_CM_C2C_C2C_FW_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_C2C_C2C_FW_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	/* L4CFG Clock Domain Configuration */
	if (mem_read(OMAP4430_CM_L4CFG_CLKSTCTRL, &cm_clkstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = clkdm44xx_config_show(stream, "L4CFG",
		OMAP4430_CM_L4CFG_CLKSTCTRL, cm_clkstctrl);
	if (ret != 0)
		return ret;
	/* L4CFG Modules Power Configuration */
	if (mem_read(OMAP4430_CM_L4CFG_L4_CFG_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4CFG_L4_CFG_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "L4_CFG",
		OMAP4430_CM_L4CFG_L4_CFG_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4CFG_L4_CFG_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4CFG_HW_SEM_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4CFG_HW_SEM_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "HW_SEM",
		OMAP4430_CM_L4CFG_HW_SEM_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4CFG_HW_SEM_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4CFG_MAILBOX_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4CFG_MAILBOX_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "MAILBOX",
		OMAP4430_CM_L4CFG_MAILBOX_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4CFG_MAILBOX_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L4CFG_SAR_ROM_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L4CFG_SAR_ROM_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "SAR_ROM",
		OMAP4430_CM_L4CFG_SAR_ROM_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L4CFG_SAR_ROM_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	/* L3INSTR Clock Domain Configuration */
	if (mem_read(OMAP4430_CM_L3INSTR_CLKSTCTRL, &cm_clkstctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = clkdm44xx_config_show(stream, "L3INSTR",
		OMAP4430_CM_L3INSTR_CLKSTCTRL, cm_clkstctrl);
	if (ret != 0)
		return ret;
	/* L3INSTR Modules Power Configuration */
	if (mem_read(OMAP4430_CM_L3INSTR_L3_3_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L3INSTR_L3_3_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "L3_3",
		OMAP4430_CM_L3INSTR_L3_3_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L3INSTR_L3_3_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L3INSTR_L3_INSTR_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L3INSTR_L3_INSTR_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "L3_INSTR",
		OMAP4430_CM_L3INSTR_L3_INSTR_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L3INSTR_L3_INSTR_CONTEXT, rm_context);
	if (ret != 0)
		return ret;

	if (mem_read(OMAP4430_CM_L3INSTR_OCP_WP1_CLKCTRL, &cm_clkctrl) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_RM_L3INSTR_OCP_WP1_CONTEXT, &rm_context) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = mod44xx_config_show(stream, "OCP_WP1",
		OMAP4430_CM_L3INSTR_OCP_WP1_CLKCTRL, cm_clkctrl,
		OMAP4430_RM_L3INSTR_OCP_WP1_CONTEXT, rm_context);
	if (ret != 0)
		return ret;
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		core44xx_dependency_show
 * @BRIEF		analyse CORE dependency configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in, out]	stream: output file stream
 * @DESCRIPTION		analyse CORE dependency configuration
 *//*------------------------------------------------------------------------ */
int core44xx_dependency_show(FILE *stream)
{
	unsigned int cm_l3_1_dynamicdep;
	unsigned int cm_l3_2_dynamicdep;
	unsigned int cm_mpu_m3_staticdep;
	unsigned int cm_mpu_m3_dynamicdep;
	unsigned int cm_sdma_staticdep;
	unsigned int cm_sdma_dynamicdep;
	unsigned int cm_c2c_staticdep;
	unsigned int cm_c2c_dynamicdep;
	unsigned int cm_l4cfg_dynamicdep;
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		core44xx_regtable_init();

	ret = mem_read(OMAP4430_CM_L3_1_DYNAMICDEP, &cm_l3_1_dynamicdep);
	ret += mem_read(OMAP4430_CM_L3_2_DYNAMICDEP, &cm_l3_2_dynamicdep);
	ret += mem_read(OMAP4430_CM_MPU_M3_STATICDEP, &cm_mpu_m3_staticdep);
	ret += mem_read(OMAP4430_CM_MPU_M3_DYNAMICDEP, &cm_mpu_m3_dynamicdep);
	ret += mem_read(OMAP4430_CM_SDMA_STATICDEP, &cm_sdma_staticdep);
	ret += mem_read(OMAP4430_CM_SDMA_DYNAMICDEP, &cm_sdma_dynamicdep);
	ret += mem_read(OMAP4430_CM_C2C_STATICDEP, &cm_c2c_staticdep);
	ret += mem_read(OMAP4430_CM_C2C_DYNAMICDEP, &cm_c2c_dynamicdep);
	ret += mem_read(OMAP4430_CM_L4CFG_DYNAMICDEP, &cm_l4cfg_dynamicdep);
	if (ret != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	fprintf(stream,
		"|-------------------------------------------------------------"
		"-------------|\n");
	fprintf(stream,
		"| CORE Domain Dependency Configuration (Static/Dynamic)       "
		"             |\n");
	fprintf(stream,
		"|-------------------------------------------------------------"
		"-------------|\n");
	fprintf(stream,
		"|              |                           FROM:              "
		"             |\n");
	fprintf(stream,
		"|              |  L3_1   |  L3_2   | MPU_M3  |  SDMA   |   C2C"
		"   |  L4CFG  |\n");
	fprintf(stream,
		"|              |Stat|Dyn |Stat|Dyn |Stat|Dyn |Stat|Dyn |Stat|"
		"Dyn |Stat|Dyn |\n");
	fprintf(stream,
		"|-------------------------------------------------------------"
		"-------------|\n");
	fprintf(stream,
		"|    TOWARDS:  |    |    |    |    |    |    |    |    |    | "
		"   |    |    |\n");
	fprintf(stream,
		"| %-12s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s"
		"|%-3s | %-3s|%-3s |\n",
		"MPU_M3",
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_l3_2_dynamicdep, 0) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_sdma_staticdep, 0) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"" /* not implemented */);
	fprintf(stream,
		"| %-12s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s"
		"|%-3s | %-3s|%-3s |\n",
		"DSP",
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_mpu_m3_staticdep, 1) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_l4cfg_dynamicdep, 1) == 1) ? "En" : "Dis"));
	fprintf(stream,
		"| %-12s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s"
		"|%-3s | %-3s|%-3s |\n",
		"IVAHD",
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_l3_2_dynamicdep, 2) == 1) ? "En" : "Dis"),
		((extract_bit(cm_mpu_m3_staticdep, 2) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		((extract_bit(cm_sdma_staticdep, 2) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		((extract_bit(cm_c2c_staticdep, 2) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		"", /* not implemented */
		"" /* not implemented */);
	fprintf(stream,
		"| %-12s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s"
		"|%-3s | %-3s|%-3s |\n",
		"ABE",
		"", /* not implemented */
		((extract_bit(cm_l3_1_dynamicdep, 3) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_mpu_m3_staticdep, 3) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		((extract_bit(cm_sdma_staticdep, 3) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		((extract_bit(cm_c2c_staticdep, 3) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		"", /* not implemented */
		"" /* not implemented */);
	fprintf(stream,
		"| %-12s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s"
		"|%-3s | %-3s|%-3s |\n",
		"MEM IF",
		"", /* not implemented */
		((extract_bit(cm_l3_1_dynamicdep, 4) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_mpu_m3_staticdep, 4) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		((extract_bit(cm_sdma_staticdep, 4) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		((extract_bit(cm_c2c_staticdep, 4) == 1) ? "En" : "Dis"),
		((extract_bit(cm_c2c_dynamicdep, 4) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		((extract_bit(cm_l4cfg_dynamicdep, 4) == 1) ? "En" : "Dis"));
	fprintf(stream,
		"| %-12s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s"
		"|%-3s | %-3s|%-3s |\n",
		"L3_1",
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_l3_2_dynamicdep, 5) == 1) ? "En" : "Dis"),
		((extract_bit(cm_mpu_m3_staticdep, 5) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		((extract_bit(cm_sdma_staticdep, 5) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		((extract_bit(cm_c2c_staticdep, 5) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_l4cfg_dynamicdep, 5) == 1) ? "En" : "Dis"));
	fprintf(stream,
		"| %-12s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s"
		"|%-3s | %-3s|%-3s |\n",
		"L3_2",
		"", /* not implemented */
		((extract_bit(cm_l3_1_dynamicdep, 6) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_mpu_m3_staticdep, 6) == 1) ? "En" : "Dis"),
		((extract_bit(cm_mpu_m3_dynamicdep, 6) == 1) ? "En" : "Dis"),
		((extract_bit(cm_sdma_staticdep, 6) == 1) ? "En" : "Dis"),
		((extract_bit(cm_sdma_dynamicdep, 6) == 1) ? "En" : "Dis"),
		((extract_bit(cm_c2c_staticdep, 6) == 1) ? "En" : "Dis"),
		((extract_bit(cm_c2c_dynamicdep, 6) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		((extract_bit(cm_l4cfg_dynamicdep, 6) == 1) ? "En" : "Dis"));
	fprintf(stream,
		"| %-12s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s"
		"|%-3s | %-3s|%-3s |\n",
		"L3INIT",
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_l3_2_dynamicdep, 7) == 1) ? "En" : "Dis"),
		((extract_bit(cm_mpu_m3_staticdep, 7) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		((extract_bit(cm_sdma_staticdep, 7) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		((extract_bit(cm_c2c_staticdep, 7) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_l4cfg_dynamicdep, 7) == 1) ? "En" : "Dis"));
	fprintf(stream,
		"| %-12s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s"
		"|%-3s | %-3s|%-3s |\n",
		"DSS",
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_l3_2_dynamicdep, 8) == 1) ? "En" : "Dis"),
		((extract_bit(cm_mpu_m3_staticdep, 8) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		((extract_bit(cm_sdma_staticdep, 8) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_l4cfg_dynamicdep, 8) == 1) ? "En" : "Dis"));
	fprintf(stream,
		"| %-12s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s"
		"|%-3s | %-3s|%-3s |\n",
		"ISS",
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_l3_2_dynamicdep, 9) == 1) ? "En" : "Dis"),
		((extract_bit(cm_mpu_m3_staticdep, 9) == 1) ? "En" : "Dis"),
		((extract_bit(cm_mpu_m3_dynamicdep, 9) == 1) ? "En" : "Dis"),
		((extract_bit(cm_sdma_staticdep, 9) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_l4cfg_dynamicdep, 9) == 1) ? "En" : "Dis"));
	fprintf(stream,
		"| %-12s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s"
		"|%-3s | %-3s|%-3s |\n",
		"GFX",
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_l3_2_dynamicdep, 10) == 1) ? "En" : "Dis"),
		((extract_bit(cm_mpu_m3_staticdep, 10) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"" /* not implemented */);
	fprintf(stream,
		"| %-12s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s"
		"|%-3s | %-3s|%-3s |\n",
		"SDMA",
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_mpu_m3_staticdep, 11) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_l4cfg_dynamicdep, 11) == 1) ? "En" : "Dis"));
	fprintf(stream,
		"| %-12s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s"
		"|%-3s | %-3s|%-3s |\n",
		"L4CFG",
		"", /* not implemented */
		((extract_bit(cm_l3_1_dynamicdep, 12) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_mpu_m3_staticdep, 12) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		((extract_bit(cm_sdma_staticdep, 12) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		((extract_bit(cm_c2c_staticdep, 12) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		"", /* not implemented */
		"" /* not implemented */);
	fprintf(stream,
		"| %-12s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s"
		"|%-3s | %-3s|%-3s |\n",
		"L4PER",
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_l3_2_dynamicdep, 13) == 1) ? "En" : "Dis"),
		((extract_bit(cm_mpu_m3_staticdep, 13) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		((extract_bit(cm_sdma_staticdep, 13) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		((extract_bit(cm_c2c_staticdep, 13) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		"", /* not implemented */
		"" /* not implemented */);
	fprintf(stream,
		"| %-12s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s"
		"|%-3s | %-3s|%-3s |\n",
		"L4SEC",
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_l3_2_dynamicdep, 14) == 1) ? "En" : "Dis"),
		((extract_bit(cm_mpu_m3_staticdep, 14) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		((extract_bit(cm_sdma_staticdep, 14) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"" /* not implemented */);
	fprintf(stream,
		"| %-12s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s"
		"|%-3s | %-3s|%-3s |\n",
		"L4WKUP",
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_mpu_m3_staticdep, 15) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		((extract_bit(cm_sdma_staticdep, 15) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_l4cfg_dynamicdep, 15) == 1) ? "En" : "Dis"));
	fprintf(stream,
		"| %-12s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s"
		"|%-3s | %-3s|%-3s |\n",
		"ALWONCORE",
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_mpu_m3_staticdep, 16) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_l4cfg_dynamicdep, 16) == 1) ? "En" : "Dis"));
	fprintf(stream,
		"| %-12s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s"
		"|%-3s | %-3s|%-3s |\n",
		"CEFUSE",
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_mpu_m3_staticdep, 17) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_l4cfg_dynamicdep, 17) == 1) ? "En" : "Dis"));
	fprintf(stream,
		"| %-12s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s"
		"|%-3s | %-3s|%-3s |\n",
		"C2C",
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_l3_2_dynamicdep, 18) == 1) ? "En" : "Dis"),
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		"", /* not implemented */
		((extract_bit(cm_l4cfg_dynamicdep, 18) == 1) ? "En" : "Dis"));
	if (!cpu_is_omap4430())
		fprintf(stream,
			"| %-12s | %-3s|%-3s | %-3s|%-3s | %-3s|%-3s | %-3s|"
			"%-3s | %-3s|%-3s | %-3s|%-3s |\n",
			"MPU",
			"", /* not implemented */
			"", /* not implemented */
			"", /* not implemented */
			"", /* not implemented */
			"", /* not implemented */
			"", /* not implemented */
			"", /* not implemented */
			"", /* not implemented */
			"", /* not implemented */
			"", /* not implemented */
			"", /* not implemented */
			((extract_bit(cm_l4cfg_dynamicdep, 19) == 1) ?
				"En" : "Dis"));

	fprintf(stream,
		"|-------------------------------------------------------------"
		"-------------|\n");
	fprintf(stream,
		"| Dynamic Dep  |         |         |         |         |      "
		"   |         |\n");
	fprintf(stream,
		"| %-12s |      %-2d |      %-2d |     %-2d  |         |      "
		"%-2d |      %-2d |\n",
		"Window Size",
		extract_bitfield(cm_l3_1_dynamicdep, 24, 4),
		extract_bitfield(cm_l3_2_dynamicdep, 24, 4),
		extract_bitfield(cm_mpu_m3_dynamicdep, 24, 4),
		extract_bitfield(cm_c2c_dynamicdep, 24, 4),
		extract_bitfield(cm_l4cfg_dynamicdep, 24, 4));
	fprintf(stream,
		"|------------------------------------------------------------"
		"--------------|\n\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		core44xx_dump
 * @BRIEF		dump PRCM CORE registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		dump PRCM CORE registers
 *//*------------------------------------------------------------------------ */
int core44xx_dump(void)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		core44xx_regtable_init();

	return dumpregs(prcm_core_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		core44xx_main
 * @BRIEF		PRCM CORE menu
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		PRCM CORE menu
 *//*------------------------------------------------------------------------ */
int core44xx_main(int argc, char *argv[])
{
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (argc == 2) {
		if (!init_done)
			core44xx_regtable_init();
		if (strcmp(argv[1], "dump") == 0) {
			ret = dumpregs(prcm_core_reg_table);
		} else if (strcmp(argv[1], "cfg") == 0) {
			ret = core44xx_config_show(stdout);
		} else if (strcmp(argv[1], "dep") == 0) {
			ret = core44xx_dependency_show(stdout);
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
 * @FUNCTION		core44xx_regtable_init
 * @BRIEF		initialize fields of reg_table
 * @RETURNS		0
 * @DESCRIPTION		initialize fields of reg_table
 *//*------------------------------------------------------------------------ */
static int core44xx_regtable_init(void)
{
	int i = 0;

	/* Init PRCM CORE registers table */
	strcpy(prcm_core_reg_table[i].name, "CM_L3_1_CLKSTCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_L3_1_CLKSTCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_L3_1_DYNAMICDEP");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_L3_1_DYNAMICDEP;
	strcpy(prcm_core_reg_table[i].name, "CM_L3_1_L3_1_CLKCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_L3_1_L3_1_CLKCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_L3_2_CLKSTCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_L3_2_CLKSTCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_L3_2_DYNAMICDEP");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_L3_2_DYNAMICDEP;
	strcpy(prcm_core_reg_table[i].name, "CM_L3_2_L3_2_CLKCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_L3_2_L3_2_CLKCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_L3_2_GPMC_CLKCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_L3_2_GPMC_CLKCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_L3_2_OCMC_RAM_CLKCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_L3_2_OCMC_RAM_CLKCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_MPU_M3_CLKSTCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_MPU_M3_CLKSTCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_MPU_M3_STATICDEP");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_MPU_M3_STATICDEP;
	strcpy(prcm_core_reg_table[i].name, "CM_MPU_M3_DYNAMICDEP");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_MPU_M3_DYNAMICDEP;
	strcpy(prcm_core_reg_table[i].name, "CM_MPU_M3_MPU_M3_CLKCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_MPU_M3_MPU_M3_CLKCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_SDMA_CLKSTCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_SDMA_CLKSTCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_SDMA_STATICDEP");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_SDMA_STATICDEP;
	strcpy(prcm_core_reg_table[i].name, "CM_SDMA_DYNAMICDEP");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_SDMA_DYNAMICDEP;
	strcpy(prcm_core_reg_table[i].name, "CM_SDMA_SDMA_CLKCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_SDMA_SDMA_CLKCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_MEMIF_CLKSTCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_MEMIF_CLKSTCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_MEMIF_DMM_CLKCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_MEMIF_DMM_CLKCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_MEMIF_EMIF_FW_CLKCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_MEMIF_EMIF_FW_CLKCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_MEMIF_EMIF_1_CLKCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_MEMIF_EMIF_1_CLKCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_MEMIF_EMIF_2_CLKCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_MEMIF_EMIF_2_CLKCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_MEMIF_DLL_CLKCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_MEMIF_DLL_CLKCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_MEMIF_EMIF_H1_CLKCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_MEMIF_EMIF_H1_CLKCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_MEMIF_EMIF_H2_CLKCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_MEMIF_EMIF_H2_CLKCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_MEMIF_DLL_H_CLKCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_MEMIF_DLL_H_CLKCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_C2C_CLKSTCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_C2C_CLKSTCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_C2C_STATICDEP");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_C2C_STATICDEP;
	strcpy(prcm_core_reg_table[i].name, "CM_C2C_DYNAMICDEP");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_C2C_DYNAMICDEP;
	strcpy(prcm_core_reg_table[i].name, "CM_C2C_C2C_CLKCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_C2C_C2C_CLKCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_C2C_MODEM_ICR_CLKCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_C2C_MODEM_ICR_CLKCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_C2C_C2C_FW_CLKCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_C2C_C2C_FW_CLKCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_L4CFG_CLKSTCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_L4CFG_CLKSTCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_L4CFG_DYNAMICDEP");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_L4CFG_DYNAMICDEP;
	strcpy(prcm_core_reg_table[i].name, "CM_L4CFG_L4_CFG_CLKCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_L4CFG_L4_CFG_CLKCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_L4CFG_HW_SEM_CLKCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_L4CFG_HW_SEM_CLKCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_L4CFG_MAILBOX_CLKCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_L4CFG_MAILBOX_CLKCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_L4CFG_SAR_ROM_CLKCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_L4CFG_SAR_ROM_CLKCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_L3INSTR_CLKSTCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_L3INSTR_CLKSTCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_L3INSTR_L3_3_CLKCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_L3INSTR_L3_3_CLKCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_L3INSTR_L3_INSTR_CLKCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_L3INSTR_L3_INSTR_CLKCTRL;
	strcpy(prcm_core_reg_table[i].name, "CM_L3INSTR_OCP_WP1_CLKCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_CM_L3INSTR_OCP_WP1_CLKCTRL;
	strcpy(prcm_core_reg_table[i].name, "PM_CORE_PWRSTCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_PM_CORE_PWRSTCTRL;
	strcpy(prcm_core_reg_table[i].name, "PM_CORE_PWRSTST");
	prcm_core_reg_table[i++].addr = OMAP4430_PM_CORE_PWRSTST;
	strcpy(prcm_core_reg_table[i].name, "RM_L3_1_L3_1_CONTEXT");
	prcm_core_reg_table[i++].addr = OMAP4430_RM_L3_1_L3_1_CONTEXT;
	strcpy(prcm_core_reg_table[i].name, "RM_L3_2_L3_2_CONTEXT");
	prcm_core_reg_table[i++].addr = OMAP4430_RM_L3_2_L3_2_CONTEXT;
	strcpy(prcm_core_reg_table[i].name, "RM_L3_2_GPMC_CONTEXT");
	prcm_core_reg_table[i++].addr = OMAP4430_RM_L3_2_GPMC_CONTEXT;
	strcpy(prcm_core_reg_table[i].name, "RM_L3_2_OCMC_RAM_CONTEXT");
	prcm_core_reg_table[i++].addr = OMAP4430_RM_L3_2_OCMC_RAM_CONTEXT;
	strcpy(prcm_core_reg_table[i].name, "RM_MPU_M3_RSTCTRL");
	prcm_core_reg_table[i++].addr = OMAP4430_RM_MPU_M3_RSTCTRL;
	strcpy(prcm_core_reg_table[i].name, "RM_MPU_M3_RSTST");
	prcm_core_reg_table[i++].addr = OMAP4430_RM_MPU_M3_RSTST;
	strcpy(prcm_core_reg_table[i].name, "RM_MPU_M3_MPU_M3_CONTEXT");
	prcm_core_reg_table[i++].addr = OMAP4430_RM_MPU_M3_MPU_M3_CONTEXT;
	strcpy(prcm_core_reg_table[i].name, "RM_SDMA_SDMA_CONTEXT");
	prcm_core_reg_table[i++].addr = OMAP4430_RM_SDMA_SDMA_CONTEXT;
	strcpy(prcm_core_reg_table[i].name, "RM_MEMIF_DMM_CONTEXT");
	prcm_core_reg_table[i++].addr = OMAP4430_RM_MEMIF_DMM_CONTEXT;
	strcpy(prcm_core_reg_table[i].name, "RM_MEMIF_EMIF_FW_CONTEXT");
	prcm_core_reg_table[i++].addr = OMAP4430_RM_MEMIF_EMIF_FW_CONTEXT;
	strcpy(prcm_core_reg_table[i].name, "RM_MEMIF_EMIF_1_CONTEXT");
	prcm_core_reg_table[i++].addr = OMAP4430_RM_MEMIF_EMIF_1_CONTEXT;
	strcpy(prcm_core_reg_table[i].name, "RM_MEMIF_EMIF_2_CONTEXT");
	prcm_core_reg_table[i++].addr = OMAP4430_RM_MEMIF_EMIF_2_CONTEXT;
	strcpy(prcm_core_reg_table[i].name, "RM_MEMIF_DLL_CONTEXT");
	prcm_core_reg_table[i++].addr = OMAP4430_RM_MEMIF_DLL_CONTEXT;
	strcpy(prcm_core_reg_table[i].name, "RM_MEMIF_EMIF_H1_CONTEXT");
	prcm_core_reg_table[i++].addr = OMAP4430_RM_MEMIF_EMIF_H1_CONTEXT;
	strcpy(prcm_core_reg_table[i].name, "RM_MEMIF_EMIF_H2_CONTEXT");
	prcm_core_reg_table[i++].addr = OMAP4430_RM_MEMIF_EMIF_H2_CONTEXT;
	strcpy(prcm_core_reg_table[i].name, "RM_MEMIF_DLL_H_CONTEXT");
	prcm_core_reg_table[i++].addr = OMAP4430_RM_MEMIF_DLL_H_CONTEXT;
	strcpy(prcm_core_reg_table[i].name, "RM_C2C_C2C_CONTEXT");
	prcm_core_reg_table[i++].addr = OMAP4430_RM_C2C_C2C_CONTEXT;
	strcpy(prcm_core_reg_table[i].name, "RM_C2C_MODEM_ICR_CONTEXT");
	prcm_core_reg_table[i++].addr = OMAP4430_RM_C2C_MODEM_ICR_CONTEXT;
	strcpy(prcm_core_reg_table[i].name, "RM_C2C_C2C_FW_CONTEXT");
	prcm_core_reg_table[i++].addr = OMAP4430_RM_C2C_C2C_FW_CONTEXT;
	strcpy(prcm_core_reg_table[i].name, "RM_L4CFG_L4_CFG_CONTEXT");
	prcm_core_reg_table[i++].addr = OMAP4430_RM_L4CFG_L4_CFG_CONTEXT;
	strcpy(prcm_core_reg_table[i].name, "RM_L4CFG_HW_SEM_CONTEXT");
	prcm_core_reg_table[i++].addr = OMAP4430_RM_L4CFG_HW_SEM_CONTEXT;
	strcpy(prcm_core_reg_table[i].name, "RM_L4CFG_MAILBOX_CONTEXT");
	prcm_core_reg_table[i++].addr = OMAP4430_RM_L4CFG_MAILBOX_CONTEXT;
	strcpy(prcm_core_reg_table[i].name, "RM_L4CFG_SAR_ROM_CONTEXT");
	prcm_core_reg_table[i++].addr = OMAP4430_RM_L4CFG_SAR_ROM_CONTEXT;
	strcpy(prcm_core_reg_table[i].name, "RM_L3INSTR_L3_3_CONTEXT");
	prcm_core_reg_table[i++].addr = OMAP4430_RM_L3INSTR_L3_3_CONTEXT;
	strcpy(prcm_core_reg_table[i].name, "RM_L3INSTR_L3_INSTR_CONTEXT");
	prcm_core_reg_table[i++].addr = OMAP4430_RM_L3INSTR_L3_INSTR_CONTEXT;
	strcpy(prcm_core_reg_table[i].name, "RM_L3INSTR_OCP_WP1_CONTEXT");
	prcm_core_reg_table[i++].addr = OMAP4430_RM_L3INSTR_OCP_WP1_CONTEXT;
	strcpy(prcm_core_reg_table[i].name, "END");
	prcm_core_reg_table[i].addr = 0;
	dprintf("prcm_core_reg_table last index=%d, size=%d\n", i, i + 1);

	init_done = 1;
	return 0;
}
