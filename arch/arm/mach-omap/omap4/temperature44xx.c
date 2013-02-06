/*
 *
 * @Component			OMAPCONF
 * @Filename			temperature44xx.c
 * @Description			OMAP4 Temperature Sensors Functions
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


#include <temperature.h>
#include <temperature44xx.h>
#include <lib.h>
#include <emif.h>
#include <cpuinfo.h>
#include <string.h>


const char *temp44xx_sensor_names[TEMP44XX_ID_MAX + 1] = {
	"BANDGAP",
	"HOTSPOT",
	"DDR1_CS1",
	"DDR1_CS2",
	"DDR2_CS1",
	"DDR2_CS2",
	"PCB",
	"FIXME"};


/* #define TEMP44XX_DEBUG */
#ifdef TEMP44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp44xx_name_get
 * @BRIEF		return temperature sensor name
 * @RETURNS		temperature sensor ID
 *			NULL in case of incorrect id
 * @param[in]		id: temperature sensor ID
 * @DESCRIPTION		return temperature sensor name
 *//*------------------------------------------------------------------------ */
const char *temp44xx_name_get(temp44xx_sensor_id id)
{
	if (id > TEMP44XX_ID_MAX)
		id = TEMP44XX_ID_MAX;

	return temp44xx_sensor_names[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp44xx_voltdm2sensor_id
 * @BRIEF		convert voltage domain ID to sensor domain ID
 * @RETURNS		valid sensor ID in case of success
 *			TEMP44XX_ID_MAX in case of voltage domain ID
 * @param[in]		vdd_id: valid voltage domain ID
 * @DESCRIPTION		convert voltage domain ID to sensor domain ID.
 *//*------------------------------------------------------------------------ */
temp44xx_sensor_id temp44xx_voltdm2sensor_id(voltdm44xx_id vdd_id)
{
	static const temp44xx_sensor_id voltdm2sensor_map[OMAP4_VD_ID_MAX] = {
		TEMP44XX_ID_MAX, /* OMAP4_LDO_WKUP */
		TEMP44XX_HOTSPOT, /* OMAP4_VDD_MPU */
		TEMP44XX_ID_MAX, /* OMAP4_VDD_IVA */
		TEMP44XX_BANDGAP}; /* OMAP4_VDD_CORE */

	CHECK_ARG_LESS_THAN(vdd_id, OMAP4_VD_ID_MAX, TEMP44XX_ID_MAX);

	dprintf("%s(%d) = %d\n", __func__, vdd_id, voltdm2sensor_map[vdd_id]);
	return voltdm2sensor_map[vdd_id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp44xx_get
 * @BRIEF		return temperature measured by selected sensor
 *			(in degrees celcius)
 * @RETURNS		measured temperature in case of success
 *			TEMP_ABSOLUTE_ZERO (-273) in case of error
 * @param[in]		id: temperature sensor id
 * @DESCRIPTION		return temperature measured by selected sensor
 *			(in degrees celcius)
 *//*------------------------------------------------------------------------ */
int temp44xx_get(temp44xx_sensor_id id)
{
	int temp, ret;
	char line[256];
	unsigned int i;
	FILE *fp = NULL;
	static const char *sensor_filenames1[TEMP44XX_ID_MAX] = {
		"/sys/devices/platform/omap4plus_scm.0/temp_sensor_hwmon.0/temp1_input", /* GLP */
		"/sys/devices/platform/omap/omap_temp_sensor.0/hotspot_temp",
		"/sys/kernel/debug/emif.1/mr4", /* GLP */
		"/sys/kernel/debug/emif.1/mr4", /* GLP */
		"/sys/kernel/debug/emif.2/mr4", /* GLP */
		"/sys/kernel/debug/emif.2/mr4", /* GLP */
		"/sys/devices/platform/i2c_omap.1/i2c-1/1-0049/twl6030_gpadc/in4_input"}; /* 4460 */

	static const char *sensor_filenames2[TEMP44XX_ID_MAX] = {
		"/sys/devices/platform/omap/omap_temp_sensor.0/temp1_input", /* Android */
		"/sys/devices/platform/omap/omap_temp_sensor.0/hotspot_temp",
		"/sys/devices/platform/omap/omap_emif.0/temperature", /* Android */
		"/sys/devices/platform/omap/omap_emif.0/temperature", /* Android */
		"/sys/devices/platform/omap/omap_emif.1/temperature", /* Android */
		"/sys/devices/platform/omap/omap_emif.1/temperature", /* Android */
		"/sys/devices/platform/omap/pcb_temp_sensor.0/temp1_input"}; /* 4460 */

	static const char *sensor_filenames3[TEMP44XX_ID_MAX] = {
		"/sys/devices/platform/omap4plus_scm.0/temp_sensor_hwmon.0/temp1_input",
		"/sys/devices/platform/omap/omap_temp_sensor.0/hotspot_temp",
		"/sys/kernel/debug/emif.1/mr4",
		"/sys/kernel/debug/emif.1/mr4",
		"/sys/kernel/debug/emif.2/mr4",
		"/sys/kernel/debug/emif.2/mr4",
		"/sys/devices/platform/i2c_omap.4/i2c-4/4-0048/temp1_input"}; /* 4470 */

	static const char *sensor_filenames4[TEMP44XX_ID_MAX] = {
		"/sys/devices/platform/omap4plus_scm.0/temp_sensor_hwmon.0/temp1_input",
		"/sys/devices/platform/omap/omap_temp_sensor.0/hotspot_temp",
		"/sys/kernel/debug/emif.1/mr4",
		"/sys/kernel/debug/emif.1/mr4",
		"/sys/kernel/debug/emif.2/mr4",
		"/sys/kernel/debug/emif.2/mr4",
		"/sys/devices/platform/omap/omap_i2c.4/i2c-4/4-0048/temp1_input"}; /* 4470 */

	static const char *sensor_filenames5[TEMP44XX_ID_MAX] = {
		"/sys/devices/platform/omap/omap_temp_sensor.0/temperature", /* Android Galaxy Nexus JOP40D */
		"/sys/devices/platform/omap/omap_temp_sensor.0/hotspot_temp",
		"/sys/devices/platform/omap/omap_emif.0/temperature", /* Android */
		"/sys/devices/platform/omap/omap_emif.0/temperature", /* Android */
		"/sys/devices/platform/omap/omap_emif.1/temperature", /* Android */
		"/sys/devices/platform/omap/omap_emif.1/temperature", /* Android */
		"/sys/devices/platform/omap/pcb_temp_sensor.0/temp1_input"}; /* 4460 */

	static const char **sensor_filenames_list[5] = {
		sensor_filenames1,
		sensor_filenames2,
		sensor_filenames3,
		sensor_filenames4,
		sensor_filenames5};

	CHECK_CPU(44xx, TEMP_ABSOLUTE_ZERO);
	CHECK_ARG_LESS_THAN(id, TEMP44XX_ID_MAX, TEMP_ABSOLUTE_ZERO);

	/* Open file exported by temp. sensor driver (if loaded) */
	for (i = 0; i < 5; i++) {
		dprintf("%s(): i=%u id=%u filename=%s\n", __func__, i, id,
			(char *) sensor_filenames_list[i][id]);
		fp = fopen((char *) sensor_filenames_list[i][id], "r");
		if (fp != NULL)
			break;
	}
	if (fp == NULL) {
		dprintf("%s(): could not open %s file!\n", __func__,
			temp44xx_name_get(id));
		temp = TEMP_ABSOLUTE_ZERO;
		goto temp44xx_get_end;
	}

	/* Read file */
	if (fgets(line, 256, fp) == NULL) {
		fclose(fp);
		dprintf("%s(): fgets() returned NULL!\n", __func__);
		temp = TEMP_ABSOLUTE_ZERO;
		goto temp44xx_get_end;
	}
	fclose(fp);

	/* Remove endind '\n' */
	line[strlen(line) - 1] = '\0';
	dprintf("%s(): line=%s len=%u\n", __func__, line, strlen(line));
	if ((id != TEMP44XX_DDR1_CS1) && (id != TEMP44XX_DDR1_CS2) &&
		(id != TEMP44XX_DDR2_CS1) && (id != TEMP44XX_DDR2_CS1)) {
		/* Retrieve temperature, in millidegrees celcius */
		ret = sscanf(line, "%d", &temp);
		if (ret != 1) {
			dprintf("%s(): sscanf() returned %d!\n", __func__, ret);
			temp = TEMP_ABSOLUTE_ZERO;
			goto temp44xx_get_end;
		}

		temp = temp / 1000; /* convert to degrees */
	} else {
		/* Retrieve temperature as MR4 code */
		ret = sscanf(line, "MR4=%d", &temp);
		if (ret != 1) {
			dprintf("%s(): sscanf(\"MR4=%%d\") returned %d!\n",
				__func__, ret);
			ret = sscanf(line, "%d", &temp);
			if (ret != 1) {
				dprintf("%s(): sscanf(\"%%d\") returned %d!\n",
					__func__, ret);
				temp = TEMP_ABSOLUTE_ZERO;
				goto temp44xx_get_end;
			}
		}
	}

temp44xx_get_end:
	if ((id != TEMP44XX_DDR1_CS1) && (id != TEMP44XX_DDR1_CS2) &&
		(id != TEMP44XX_DDR2_CS1) && (id != TEMP44XX_DDR2_CS1)) {
		dprintf("%s(%s): temp is %d C\n", __func__,
			temp44xx_name_get(id), temp);
	} else {
		dprintf("%s(%s): temp is %s\n", __func__,
			temp44xx_name_get(id),
			emif_mr4_convert(temp, TEMP_CELCIUS_DEGREES));
	}
	return temp;
}
