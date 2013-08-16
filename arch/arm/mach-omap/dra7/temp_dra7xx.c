/*
 *
 * @Component			OMAPCONF
 * @Filename			temp_dra7xx.c
 * @Description			Jacinto6 Temperature Sensors Functions
 * @Author			José Peña (pena@ti.com)
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
#include <temp_dra7xx.h>
#include <hwtemp_dra7xx.h>
#include <ctrlmod_core_dra7xx-defs.h>
#include <cpuinfo.h>
#include <lib.h>
#include <autoadjust_table.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


/* increase this num for each back up fn list*/
#define NUM_SENSOR_FILENAMES_LIST  1


/* #define TEMP_DRA7XX_DEBUG */
#ifdef TEMP_DRA7XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


const char *temp_dra7xx_sensor_names[TEMP_DRA7XX_ID_MAX + 1] = {
	"MPU",
	"GPU",
	"CORE",
	"IVA",
	"DSPEVE",
	"FIXME"};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp_dra7xx_name_get
 * @BRIEF		return temperature sensor name
 * @RETURNS		temperature sensor ID
 *			NULL in case of incorrect id
 * @param[in]		id: temperature sensor ID
 * @DESCRIPTION		return temperature sensor name
 *//*------------------------------------------------------------------------ */
const char *temp_dra7xx_name_get(temp_dra7xx_sensor_id id)
{
	if (id > TEMP_DRA7XX_ID_MAX)
		id = TEMP_DRA7XX_ID_MAX;

	return temp_dra7xx_sensor_names[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION           temp_dra7xx_get
 * @BRIEF              return temperature measured by selected sensor
 *                     (in degrees celcius)
 * @RETURNS            measured temperature in case of success
 *                     TEMP_ABSOLUTE_ZERO (-273) in case of error
 * @param[in]          id: ADC temperature sensor id
 * @param[in, out]     temp: temperature (Celcius, min) (returned)
 * @DESCRIPTION                return temperature measured by selected sensor
 *                     (in degrees celcius)
 *//*------------------------------------------------------------------------ */
int temp_dra7xx_get(temp_dra7xx_sensor_id id)
{
	int temp, ret;
	char line[256];
	unsigned int i;
	FILE *fp = NULL;
	static const char *sensor_filenames1[TEMP_DRA7XX_ID_MAX] = {
			"/sys/class/thermal/thermal_zone0/temp",
			"/sys/class/thermal/thermal_zone1/temp",
			"/sys/class/thermal/thermal_zone2/temp",
			"/sys/class/thermal/thermal_zone4/temp",
			"/sys/class/thermal/thermal_zone3/temp"};

	static const char **sensor_filenames_list[NUM_SENSOR_FILENAMES_LIST] = {
		sensor_filenames1,
	};

	CHECK_ARG_LESS_THAN(id, TEMP_DRA7XX_ID_MAX, TEMP_ABSOLUTE_ZERO);

	/* Open file exported by temp. sensor driver (if loaded) */
	for (i = 0; i <  NUM_SENSOR_FILENAMES_LIST; i++) {
		dprintf("%s(): i=%u id=%u filename=%s\n", __func__, i, id,
			(char *) sensor_filenames_list[i][id]);
		fp = fopen((char *) sensor_filenames_list[i][id], "r");
		if (fp != NULL)
			break;
	}
	if (fp == NULL) {
		dprintf("%s(): could not open %s file!\n", __func__,
			temp_dra7xx_name_get(id));
		temp = TEMP_ABSOLUTE_ZERO;
		goto temp_dra7xx_get_end;
	}

	/* Read file */
	if (fgets(line, 256, fp) == NULL) {
		fclose(fp);
		dprintf("%s(): fgets() returned NULL!\n", __func__);
		temp = TEMP_ABSOLUTE_ZERO;
		goto temp_dra7xx_get_end;
	}
	fclose(fp);

	/* Remove endind '\n' */
	line[strlen(line) - 1] = '\0';
	dprintf("%s(): line=%s len=%u\n", __func__, line, strlen(line));


	/* Retrieve temperature, in millidegrees celcius */
	ret = sscanf(line, "%d", &temp);
	if (ret != 1) {
		dprintf("%s(): sscanf() returned %d!\n", __func__, ret);
		temp = TEMP_ABSOLUTE_ZERO;
		goto temp_dra7xx_get_end;
	}

	temp = temp / 1000; /* convert to degrees */

temp_dra7xx_get_end:
	dprintf("%s(%s): temp is %d C\n", __func__, temp_dra7xx_name_get(id),
		temp);

	return temp;
}
