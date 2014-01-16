/*
 *
 * @Component			OMAPCONF
 * @Filename			abb7xx.c
 * @Description			DRA7 PRCM ABB Definitions & Functions
 * @Author			Nishanth Menon
 * @Date			2014
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
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


#include <abb7xx.h>
#include <abb.h>
#include <autoadjust_table.h>
#include <lib.h>
#include <mem.h>
#include <cpuinfo.h>
#include <prm_dra7xx-defs.h>
#include <clock_dra7xx.h>


/* #define ABB7XX_DEBUG */
#ifdef ABB7XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		abb7xx_dump
 * @BRIEF		dump PRCM ABB registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump PRCM ABB registers
 *//*------------------------------------------------------------------------ */
int abb7xx_dump(FILE *stream)
{
	reg *abb_registers[] = {
		&dra7xx_device_prm_prm_abbldo_mpu_setup,
		&dra7xx_device_prm_prm_abbldo_mpu_ctrl,
		&dra7xx_device_prm_prm_abbldo_iva_setup,
		&dra7xx_device_prm_prm_abbldo_iva_ctrl,
		&dra7xx_device_prm_prm_abbldo_dspeve_setup,
		&dra7xx_device_prm_prm_abbldo_dspeve_ctrl,
		&dra7xx_device_prm_prm_abbldo_gpu_setup,
		&dra7xx_device_prm_prm_abbldo_gpu_ctrl,
		0,
	};
	char autoadjust_table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row, idx;

	CHECK_NULL_ARG(stream, OMAPCONF_ERR_ARG);

	autoadjust_table_init(autoadjust_table);
	row = 0;

	strncpy(autoadjust_table[row][0], "Reg. Name", TABLE_MAX_ELT_LEN);
	strncpy(autoadjust_table[row][1], "Reg. Addr",
		TABLE_MAX_ELT_LEN);
	strncpy(autoadjust_table[row][2], "Reg. Val.", TABLE_MAX_ELT_LEN);
	row++;

	for (idx = 0; abb_registers[idx] != 0; idx++) {
		snprintf(autoadjust_table[row][0], TABLE_MAX_ELT_LEN,
			"%s", reg_name_get(abb_registers[idx]));
		snprintf(autoadjust_table[row][1], TABLE_MAX_ELT_LEN,
			"0x%08X", reg_addr_get(abb_registers[idx]));
		snprintf(autoadjust_table[row++][2], TABLE_MAX_ELT_LEN,
			"0x%08X", reg_read(abb_registers[idx]));
		row++;
	}

	autoadjust_table_print(autoadjust_table, row, 3);

	return 0;
}

static void read_all_abb_regs(struct abb_data *data)
{
	data[0].name = "MPU Voltage Domain";
	data[0].setup = reg_read(&dra7xx_device_prm_prm_abbldo_mpu_setup);
	data[0].ctrl = reg_read(&dra7xx_device_prm_prm_abbldo_mpu_ctrl);

	data[1].name = "IVA Voltage Domain";
	data[1].setup = reg_read(&dra7xx_device_prm_prm_abbldo_iva_setup);
	data[1].ctrl = reg_read(&dra7xx_device_prm_prm_abbldo_iva_ctrl);

	data[2].name = "DSPEVE Voltage Domain";
	data[2].setup = reg_read(&dra7xx_device_prm_prm_abbldo_dspeve_setup);
	data[2].ctrl = reg_read(&dra7xx_device_prm_prm_abbldo_dspeve_ctrl);

	data[3].name = "GPU Voltage Domain";
	data[3].setup = reg_read(&dra7xx_device_prm_prm_abbldo_gpu_setup);
	data[3].ctrl = reg_read(&dra7xx_device_prm_prm_abbldo_gpu_ctrl);
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		abb7xx_config_show
 * @BRIEF		analyze power configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_INTERNAL
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		analyze power configuration
 *//*------------------------------------------------------------------------ */
int abb7xx_config_show(FILE *stream)
{
	double sysclk_rate;
	struct abb_data dra7_abb_data[4];

	CHECK_NULL_ARG(stream, OMAPCONF_ERR_ARG);

	read_all_abb_regs(dra7_abb_data);

	sysclk_rate = clk_dra7xx_rate_get(CLK_DRA7XX_SYS_CLKIN1, 0);
	if (sysclk_rate <= 0) {
		fprintf(stderr, "%s(): could not retrieve sysclk rate! (%d)\n",
			__func__, (int) sysclk_rate);
		return OMAPCONF_ERR_INTERNAL;
	}

	return abb_config_show(stream, sysclk_rate, dra7_abb_data, 4);
}
