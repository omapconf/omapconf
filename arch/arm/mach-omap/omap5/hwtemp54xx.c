/*
 *
 * @Component			OMAPCONF
 * @Filename			hwtemp54xx.c
 * @Description			OMAP5 Temperature Sensors Functions (from hardware)
 * @Author			José Peña <pena@ti.com>
 * @Date			2013
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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


#include <temperature.h>
#include <hwtemp.h>
#include <bgap_adc_o5_data.h>
#include <temp54xx.h>
#include <hwtemp54xx.h>
#include <ctrlmod_core54xx-defs.h>
#include <cpuinfo.h>
#include <lib.h>
#include <autoadjust_table.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


/* Expands OMAP54_DTEMP_REG(mpu, 4) to &omap5430_control_dtemp_mpu_0; */
#define OMAP54_DTEMP_REG(dom, reg_id) \
	[DTEMP_TAG_##reg_id] = &omap5430_control_dtemp_##dom##_##reg_id


/* #define HWTEMP54XX_DEBUG */
#ifdef HWTEMP54XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

static reg *mpu_temperature_FIFO_reg_address[NUM_DTEMP_TAGS] = {
	OMAP54_DTEMP_REG(mpu, 0),
	OMAP54_DTEMP_REG(mpu, 1),
	OMAP54_DTEMP_REG(mpu, 2),
	OMAP54_DTEMP_REG(mpu, 3),
	OMAP54_DTEMP_REG(mpu, 4),
};

static reg *gpu_temperature_FIFO_reg_address[NUM_DTEMP_TAGS] = {
	OMAP54_DTEMP_REG(mm, 0),
	OMAP54_DTEMP_REG(mm, 1),
	OMAP54_DTEMP_REG(mm, 2),
	OMAP54_DTEMP_REG(mm, 3),
	OMAP54_DTEMP_REG(mm, 4),
};

static reg *core_temperature_FIFO_reg_address[NUM_DTEMP_TAGS] = {
	OMAP54_DTEMP_REG(core, 0),
	OMAP54_DTEMP_REG(core, 1),
	OMAP54_DTEMP_REG(core, 2),
	OMAP54_DTEMP_REG(core, 3),
	OMAP54_DTEMP_REG(core, 4),
};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwtemp54xx_get
 * @BRIEF		return temperature measured by selected sensor's register buffer
 *			(in degrees celcius)
 * @RETURNS		measured temperature in case of success
 *			TEMP_ABSOLUTE_ZERO (-273) in case of error
 * @param[in]		id: ADC temperature sensor id
 * @DESCRIPTION		return temperature measured by selected sensor
 *			(in degrees celcius)
 *//*------------------------------------------------------------------------ */
int hwtemp54xx_get(hwtemp54xx_sensor_id id)
{
	reg *temp_reg;

	/* Use id to choose which device's register to read from */
	switch (id) {
	case HWTEMP54XX_MPU:
		temp_reg = mpu_temperature_FIFO_reg_address[DTEMP_TAG_0];
		break;
	case HWTEMP54XX_GPU:
		temp_reg = gpu_temperature_FIFO_reg_address[DTEMP_TAG_0];
		break;
	case HWTEMP54XX_CORE:
		temp_reg = core_temperature_FIFO_reg_address[DTEMP_TAG_0];
		break;
	default:
		fprintf(stderr, "%s: unsupported ID %d!\n", __func__, id);
		return TEMP_ABSOLUTE_ZERO;
	}

	return hwtemp_get(temp_reg, OMAP5_ADC_MASK, OMAP5_ADC_SHIFT,
			  OMAP5_ADC_TABLE_BEGIN, bgap_o5_conversion_table,
			  sizeof(bgap_o5_conversion_table) /
				sizeof(bgap_o5_conversion_table[0]));
}
