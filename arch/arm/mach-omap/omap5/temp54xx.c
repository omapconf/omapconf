/*
 *
 * @Component			OMAPCONF
 * @Filename			temp54xx.c
 * @Description			OMAP5 Temperature Sensors Functions
 * @Author			Patrick Titiano (p-titiano@ti.com)
 * @Date			2011
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
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


#include <temp54xx.h>
#include <hwtemp54xx.h>
#include <ctrlmod_core54xx-defs.h>
#include <cpuinfo.h>
#include <lib.h>
#include <autoadjust_table.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <emif.h>


/* #define TEMP54XX_DEBUG */
#ifdef TEMP54XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


const char *temp54xx_sensor_names[TEMP54XX_ID_MAX + 1] = {
	"MPU",
	"Hotspot MPU",
	"GPU",
	"Hotspot GPU",
	"CORE",
	"EMIF1",
	"EMIF2",
	"PCB",
	"CASE",
	"CHARGER",
	"FIXME"};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp54xx_name_get
 * @BRIEF		return temperature sensor name
 * @RETURNS		temperature sensor ID
 *			NULL in case of incorrect id
 * @param[in]		id: temperature sensor ID
 * @DESCRIPTION		return temperature sensor name
 *//*------------------------------------------------------------------------ */
const char *temp54xx_name_get(temp54xx_sensor_id id)
{
	if (id > TEMP54XX_ID_MAX)
		id = TEMP54XX_ID_MAX;

	return temp54xx_sensor_names[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm2sensor_id
 * @BRIEF		convert voltage domain ID to sensor domain ID
 * @RETURNS		valid sensor ID in case of success
 *			TEMP54XX_ID_MAX in case of voltage domain ID
 * @param[in]		vdd_id: valid voltage domain ID
 * @DESCRIPTION		convert voltage domain ID to sensor domain ID.
 *//*------------------------------------------------------------------------ */
temp54xx_sensor_id voltdm2sensor_id(voltdm54xx_id vdd_id)
{
	static const temp54xx_sensor_id voltdm2sensor_map[VDD54XX_ID_MAX] = {
		TEMP54XX_ID_MAX,
		TEMP54XX_MPU,
		TEMP54XX_GPU,
		TEMP54XX_CORE};

	CHECK_ARG_LESS_THAN(vdd_id, VDD54XX_ID_MAX, TEMP54XX_ID_MAX);

	return voltdm2sensor_map[vdd_id];
}



/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp54xx_get
 * @BRIEF		return temperature measured by selected sensor
 *			(in degrees celcius)
 * @RETURNS		measured temperature in case of success
 *			TEMP_ABSOLUTE_ZERO (-273) in case of error
 * @param[in]		id: ADC temperature sensor id
 * @param[in, out]	temp: temperature (Celcius, min) (returned)
 * @DESCRIPTION		return temperature measured by selected sensor
 *			(in degrees celcius)
 *//*------------------------------------------------------------------------ */
int temp54xx_get(temp54xx_sensor_id id)
{
	int temp, ret;
	char line[256];
	unsigned int i;
	FILE *fp = NULL;
	static const char *sensor_filenames1[TEMP54XX_ID_MAX] = {
		"/sys/kernel/debug/thermal_debug/devices/omap_cpu_sensor/temperature",
		"/sys/kernel/debug/thermal_debug/devices/omap_cpu_governor/hotspot_temp",
		"/sys/kernel/debug/thermal_debug/devices/omap_gpu_sensor/temperature",
		"/sys/kernel/debug/thermal_debug/devices/omap_gpu_governor/hotspot_temp",
		"/sys/kernel/debug/thermal_debug/devices/omap_core_sensor/temperature",
		"/sys/kernel/debug/emif.1/mr4",
		"/sys/kernel/debug/emif.2/mr4",
		"/sys/kernel/debug/thermal_debug/devices/tmp102_temp_sensor.72/temperature",
		"/sys/kernel/debug/thermal_debug/devices/tmp006_sensor/temperature",
		"/sys/kernel/debug/thermal_debug/devices/tmp102_temp_sensor.73/temperature"};
	static const char *sensor_filenames2[TEMP54XX_ID_MAX] = {
		"/sys/devices/platform/omap/omap_temp_sensor.0/temp1_input",
		"/sys/kernel/debug/thermal_debug/devices/omap_cpu_governor/hotspot_temp",
		"/sys/devices/platform/omap/omap_temp_sensor.1/temp1_input",
		"/sys/kernel/debug/thermal_debug/devices/omap_gpu_governor/hotspot_temp",
		"/sys/devices/platform/omap/omap_temp_sensor.2/temp1_input",
		"/sys/kernel/debug/emif.1/mr4",
		"/sys/kernel/debug/emif.2/mr4",
		"/sys/kernel/debug/thermal_debug/devices/tmp102_temp_sensor.72/temperature",
		"/sys/kernel/debug/thermal_debug/devices/tmp006_sensor/temperature",
		"/sys/kernel/debug/thermal_debug/devices/tmp102_temp_sensor.73/temperature"};
	static const char *sensor_filenames3[TEMP54XX_ID_MAX] = {
		"/sys/devices/platform/omap/omap4plus_scm.0/temp_sensor_hwmon.0/temp1_input",
		"/sys/kernel/debug/thermal_debug/devices/omap_cpu_governor/hotspot_temp",
		"/sys/devices/platform/omap/omap4plus_scm.0/temp_sensor_hwmon.1/temp1_input",
		"/sys/kernel/debug/thermal_debug/devices/omap_gpu_governor/hotspot_temp",
		"/sys/devices/platform/omap/omap4plus_scm.0/temp_sensor_hwmon.2/temp1_input",
		"/sys/kernel/debug/emif.1/mr4",
		"/sys/kernel/debug/emif.2/mr4",
		"/sys/kernel/debug/thermal_debug/devices/tmp102_temp_sensor.72/temperature",
		"/sys/kernel/debug/thermal_debug/devices/tmp006_sensor/temperature",
		"/sys/kernel/debug/thermal_debug/devices/tmp102_temp_sensor.73/temperature"};
	static const char **sensor_filenames_list[3] = {
		sensor_filenames1,
		sensor_filenames2,
		sensor_filenames3};

	CHECK_CPU(54xx, TEMP_ABSOLUTE_ZERO);
	CHECK_ARG_LESS_THAN(id, TEMP54XX_ID_MAX, TEMP_ABSOLUTE_ZERO);

	/* Open file exported by temp. sensor driver (if loaded) */
	for (i = 0; i < 3; i++) {
		dprintf("%s(): i=%u id=%u filename=%s\n", __func__, i, id,
			(char *) sensor_filenames_list[i][id]);
		fp = fopen((char *) sensor_filenames_list[i][id], "r");
		if (fp != NULL)
			break;
	}
	if (fp == NULL) {
		dprintf("%s(): could not open %s file!\n", __func__,
			temp54xx_name_get(id));
		temp = TEMP_ABSOLUTE_ZERO;
		goto temp54xx_get_end;
	}

	/* Read file */
	if (fgets(line, 256, fp) == NULL) {
		fclose(fp);
		dprintf("%s(): fgets() returned NULL!\n", __func__);
		temp = TEMP_ABSOLUTE_ZERO;
		goto temp54xx_get_end;
	}
	fclose(fp);

	/* Remove endind '\n' */
	line[strlen(line) - 1] = '\0';
	dprintf("%s(): line=%s len=%u\n", __func__, line, strlen(line));
	if ((id != TEMP54XX_EMIF1) && (id != TEMP54XX_EMIF2)) {
		/* Retrieve temperature, in millidegrees celcius */
		ret = sscanf(line, "%d", &temp);
		if (ret != 1) {
			dprintf("%s(): sscanf() returned %d!\n", __func__, ret);
			temp = TEMP_ABSOLUTE_ZERO;
			goto temp54xx_get_end;
		}

		temp = temp / 1000; /* convert to degrees */
	} else {
		/* Retrieve temperature as MR4 code */
		ret = sscanf(line, "MR4=%d", &temp);
		if (ret != 1) {
			dprintf("%s(): sscanf() returned %d!\n", __func__, ret);
			temp = TEMP_ABSOLUTE_ZERO;
			goto temp54xx_get_end;
		}
	}

temp54xx_get_end:
	if ((id != TEMP54XX_EMIF1) && (id != TEMP54XX_EMIF2)) {
		dprintf("%s(%s): temp is %d C\n", __func__,
			temp54xx_name_get(id), temp);
	} else {
		dprintf("%s(%s): temp is %s\n", __func__,
			temp54xx_name_get(id),
			emif_mr4_convert(temp, TEMP_CELCIUS_DEGREES));
	}
	return temp;
}
