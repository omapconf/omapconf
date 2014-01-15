/*
 *
 * @Component			OMAPCONF
 * @Filename			abb54xx.c
 * @Description			OMAP5 PRCM ABB Definitions & Functions
 * @Author			Patrick Titiano (p-titiano@ti.com)
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


#include <abb54xx.h>
#include <abb.h>
#include <autoadjust_table.h>
#include <lib.h>
#include <mem.h>
#include <cpuinfo.h>
#include <prm54xx-defs.h>
#include <clock54xx.h>


/* #define ABB54XX_DEBUG */
#ifdef ABB54XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		abb54xx_dump
 * @BRIEF		dump PRCM ABB registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump PRCM ABB registers
 *//*------------------------------------------------------------------------ */
int abb54xx_dump(FILE *stream)
{
	reg *abb_mpu_setup_reg;
	reg *abb_mpu_ctrl_reg;
	reg *abb_mm_setup_reg;
	reg *abb_mm_ctrl_reg;
	char autoadjust_table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(stream, OMAPCONF_ERR_ARG);

	autoadjust_table_init(autoadjust_table);
	row = 0;

	strncpy(autoadjust_table[row][0], "Reg. Name", TABLE_MAX_ELT_LEN);
	strncpy(autoadjust_table[row][1], "Reg. Addr",
		TABLE_MAX_ELT_LEN);
	strncpy(autoadjust_table[row][2], "Reg. Val.", TABLE_MAX_ELT_LEN);
	row++;

	/* Read ABB registers content */
	if (cpu_revision_get() == REV_ES1_0) {
		abb_mpu_setup_reg = &omap5430es1_prm_abbldo_mpu_setup;
		abb_mpu_ctrl_reg = &omap5430es1_prm_abbldo_mpu_ctrl;
		abb_mm_setup_reg = &omap5430es1_prm_abbldo_mm_setup;
		abb_mm_ctrl_reg = &omap5430es1_prm_abbldo_mm_ctrl;
	} else {
		abb_mpu_setup_reg = &omap5430_prm_abbldo_mpu_setup;
		abb_mpu_ctrl_reg = &omap5430_prm_abbldo_mpu_ctrl;
		abb_mm_setup_reg = &omap5430_prm_abbldo_mm_setup;
		abb_mm_ctrl_reg = &omap5430_prm_abbldo_mm_ctrl;
	}

	/* Show register name, addr & content (hex) */
	snprintf(autoadjust_table[row][0], TABLE_MAX_ELT_LEN,
		"%s", reg_name_get(abb_mpu_setup_reg));
	snprintf(autoadjust_table[row][1], TABLE_MAX_ELT_LEN,
		"0x%08X", reg_addr_get(abb_mpu_setup_reg));
	snprintf(autoadjust_table[row++][2], TABLE_MAX_ELT_LEN,
		"0x%08X", reg_read(abb_mpu_setup_reg));
	snprintf(autoadjust_table[row][0], TABLE_MAX_ELT_LEN,
		"%s", reg_name_get(abb_mpu_ctrl_reg));
	snprintf(autoadjust_table[row][1], TABLE_MAX_ELT_LEN,
		"0x%08X", reg_addr_get(abb_mpu_ctrl_reg));
	snprintf(autoadjust_table[row++][2], TABLE_MAX_ELT_LEN,
		"0x%08X", reg_read(abb_mpu_ctrl_reg));
	snprintf(autoadjust_table[row][0], TABLE_MAX_ELT_LEN,
		"%s", reg_name_get(abb_mm_setup_reg));
	snprintf(autoadjust_table[row][1], TABLE_MAX_ELT_LEN,
		"0x%08X", reg_addr_get(abb_mm_setup_reg));
	snprintf(autoadjust_table[row++][2], TABLE_MAX_ELT_LEN,
		"0x%08X", reg_read(abb_mm_setup_reg));
	snprintf(autoadjust_table[row][0], TABLE_MAX_ELT_LEN,
		"%s", reg_name_get(abb_mm_ctrl_reg));
	snprintf(autoadjust_table[row][1], TABLE_MAX_ELT_LEN,
		"0x%08X", reg_addr_get(abb_mm_ctrl_reg));
	snprintf(autoadjust_table[row++][2], TABLE_MAX_ELT_LEN,
		"0x%08X", reg_read(abb_mm_ctrl_reg));

	autoadjust_table_print(autoadjust_table, row, 3);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		abb54xx_config_show
 * @BRIEF		analyze power configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_INTERNAL
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		analyze power configuration
 *//*------------------------------------------------------------------------ */
int abb54xx_config_show(FILE *stream)
{
	double sysclk_rate;
	struct abb_data omap5_abb_data[2];

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(stream, OMAPCONF_ERR_ARG);

	omap5_abb_data[0].name = "MPU Voltage Domain";
	omap5_abb_data[1].name = "MM Voltage Domain";
	if (cpu_revision_get() == REV_ES1_0) {
		omap5_abb_data[0].setup = reg_read(&omap5430es1_prm_abbldo_mpu_setup);
		omap5_abb_data[0].ctrl = reg_read(&omap5430es1_prm_abbldo_mpu_ctrl);
		omap5_abb_data[1].setup = reg_read(&omap5430es1_prm_abbldo_mm_setup);
		omap5_abb_data[1].ctrl = reg_read(&omap5430es1_prm_abbldo_mm_ctrl);
	} else {
		omap5_abb_data[0].setup = reg_read(&omap5430_prm_abbldo_mpu_setup);
		omap5_abb_data[0].ctrl = reg_read(&omap5430_prm_abbldo_mpu_ctrl);
		omap5_abb_data[1].setup = reg_read(&omap5430_prm_abbldo_mm_setup);
		omap5_abb_data[1].ctrl = reg_read(&omap5430_prm_abbldo_mm_ctrl);
	}

	sysclk_rate = clk54xx_sysclk_rate_get();
	if (sysclk_rate <= 0) {
		fprintf(stderr, "%s(): could not retrieve sysclk rate! (%d)\n",
			__func__, (int) sysclk_rate);
		return OMAPCONF_ERR_INTERNAL;
	}

	return abb_config_show(stream, sysclk_rate, omap5_abb_data, 2);
}
