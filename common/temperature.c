/*
 *
 * @Component			OMAPCONF
 * @Filename			temperature.c
 * @Description			Generic Temperature Sensors Functions
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


#include <temperature.h>
#include <temp54xx.h>
#include <hwtemp54xx.h>
#include <temp_dra7xx.h>
#include <hwtemp_dra7xx.h>
#include <temperature44xx.h>
#include <cpuinfo.h>
#include <lib.h>
#include <autoadjust_table.h>
#include <string.h>
#include <emif.h>
#include <voltdomain.h>


/* #define TEMPERATURE_DEBUG */
#ifdef TEMPERATURE_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


genlist temp_sensor_list;
static unsigned short temp_sensor_init_done = 0;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp_sensor_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void temp_sensor_init(void)
{
	if (!temp_sensor_init_done) {
		genlist_init(&temp_sensor_list);
		if (cpu_is_omap44xx()) {
			genlist_addtail(&temp_sensor_list,
				(void *) TEMP_SENSOR_BANDGAP,
				(1 + strlen(TEMP_SENSOR_BANDGAP)) * sizeof(char));
			genlist_addtail(&temp_sensor_list,
				(void *) TEMP_SENSOR_HOTSPOT_MPU,
				(1 + strlen(TEMP_SENSOR_HOTSPOT_MPU)) * sizeof(char));
			genlist_addtail(&temp_sensor_list,
				(void *) TEMP_SENSOR_MEM1,
				(1 + strlen(TEMP_SENSOR_MEM1)) * sizeof(char));
			genlist_addtail(&temp_sensor_list,
				(void *) TEMP_SENSOR_MEM2,
				(1 + strlen(TEMP_SENSOR_MEM2)) * sizeof(char));
			genlist_addtail(&temp_sensor_list,
				(void *) TEMP_SENSOR_PCB,
				(1 + strlen(TEMP_SENSOR_PCB)) * sizeof(char));
		} else if (cpu_is_omap54xx()) {
			genlist_addtail(&temp_sensor_list,
				(void *) TEMP_SENSOR_MPU,
				(1 + strlen(TEMP_SENSOR_MPU)) * sizeof(char));
			genlist_addtail(&temp_sensor_list,
				(void *) TEMP_SENSOR_HOTSPOT_MPU,
				(1 + strlen(TEMP_SENSOR_HOTSPOT_MPU)) * sizeof(char));
			genlist_addtail(&temp_sensor_list,
				(void *) TEMP_SENSOR_GPU,
				(1 + strlen(TEMP_SENSOR_GPU)) * sizeof(char));
			genlist_addtail(&temp_sensor_list,
				(void *) TEMP_SENSOR_HOTSPOT_GPU,
				(1 + strlen(TEMP_SENSOR_HOTSPOT_GPU)) * sizeof(char));
			genlist_addtail(&temp_sensor_list,
				(void *) TEMP_SENSOR_CORE,
				(1 + strlen(TEMP_SENSOR_CORE)) * sizeof(char));
			genlist_addtail(&temp_sensor_list,
				(void *) TEMP_SENSOR_MEM1,
				(1 + strlen(TEMP_SENSOR_MEM1)) * sizeof(char));
			genlist_addtail(&temp_sensor_list,
				(void *) TEMP_SENSOR_MEM2,
				(1 + strlen(TEMP_SENSOR_MEM2)) * sizeof(char));
			genlist_addtail(&temp_sensor_list,
				(void *) TEMP_SENSOR_PCB,
				(1 + strlen(TEMP_SENSOR_PCB)) * sizeof(char));
			genlist_addtail(&temp_sensor_list,
				(void *) TEMP_SENSOR_CASE,
				(1 + strlen(TEMP_SENSOR_CASE)) * sizeof(char));
			genlist_addtail(&temp_sensor_list,
				(void *) TEMP_SENSOR_CHARGER,
				(1 + strlen(TEMP_SENSOR_CHARGER)) * sizeof(char));
		} else if (cpu_is_dra7xx()) {
			genlist_addtail(&temp_sensor_list, (void *) TEMP_SENSOR_MPU,
				(1 + strlen(TEMP_SENSOR_MPU)) * sizeof(char));
			genlist_addtail(&temp_sensor_list, (void *) TEMP_SENSOR_GPU,
				(1 + strlen(TEMP_SENSOR_GPU)) * sizeof(char));
			genlist_addtail(&temp_sensor_list, (void *) TEMP_SENSOR_CORE,
				(1 + strlen(TEMP_SENSOR_CORE)) * sizeof(char));
			genlist_addtail(&temp_sensor_list, (void *) TEMP_SENSOR_IVA,
				(1 + strlen(TEMP_SENSOR_IVA)) * sizeof(char));
			genlist_addtail(&temp_sensor_list, (void *) TEMP_SENSOR_DSPEVE,
				(1 + strlen(TEMP_SENSOR_DSPEVE)) * sizeof(char));
		} else {
			fprintf(stderr,
				"omapconf: %s(): cpu not supported!!!\n",
				__func__);
		}

		temp_sensor_init_done = 1;
		dprintf("%s(): init done.\n", __func__);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp_sensor_deinit
 * @BRIEF		free dynamically allocated internal data.
 * @DESCRIPTION		free dynamically allocated internal data.
 *			MUST BE CALLED AT END OF EXECUTION.
 *//*------------------------------------------------------------------------ */
void temp_sensor_deinit(void)
{
	if (temp_sensor_init_done)
		genlist_free(&temp_sensor_list);
	dprintf("%s(): deinit done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp_sensor_voltdm2sensor
 * @BRIEF		convert generic voltage domain name
 *			into generic temperature sensor name.
 * @RETURNS		temperature sensor name
 *			NULL if not available or in case of error
 * @param[in]		voltdm: voltage domain name
 * @DESCRIPTION		convert generic voltage domain name
 *			into generic temperature sensor name.
 *			To be used to generically retrieve the temperature
 *			sensor of a given voltage domain.
 *//*------------------------------------------------------------------------ */
const char *temp_sensor_voltdm2sensor(const char *voltdm)
{
	int vdd_id;
	const char *sensor;

	CHECK_NULL_ARG(voltdm, NULL);

	vdd_id = voltdm_s2id(voltdm);
	if (vdd_id < 0) {
		sensor = NULL;
	} else if (cpu_is_omap44xx()) {
		switch (vdd_id) {
		case OMAP4_VDD_MPU:
			sensor = TEMP_SENSOR_HOTSPOT_MPU;
			break;
		case OMAP4_VDD_CORE:
			sensor = TEMP_SENSOR_BANDGAP;
			break;
		default:
			sensor = NULL;

		}
	} else if (cpu_is_omap54xx()) {
		switch (vdd_id) {
		case VDD54XX_MPU:
			sensor = TEMP_SENSOR_MPU;
			break;
		case VDD54XX_MM:
			sensor = TEMP_SENSOR_GPU;
			break;
		case VDD54XX_CORE:
			sensor = TEMP_SENSOR_CORE;
			break;
		default:
			sensor = NULL;

		}
	} else if (cpu_is_dra7xx()) {
		switch (vdd_id) {
		case VDD_DRA7XX_MPU:
			sensor = TEMP_SENSOR_MPU;
			break;
		case VDD_DRA7XX_GPU:
			sensor = TEMP_SENSOR_GPU;
			break;
		case VDD_DRA7XX_CORE:
			sensor = TEMP_SENSOR_CORE;
			break;
		case VDD_DRA7XX_IVA:
			sensor = TEMP_SENSOR_IVA;
			break;
		case VDD_DRA7XX_DSPEVE:
			sensor = TEMP_SENSOR_DSPEVE;
			break;
		default:
			sensor = NULL;

		}
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		sensor = NULL;
	}

	dprintf("%s(%s) = %s\n", __func__, voltdm, sensor);
	return sensor;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp_sensor_count_get
 * @BRIEF		return the number of temperature sensor(s)
 * @RETURNS		> 0 number of temperature sensor(s)
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		return the number of temperature sensor(s)
 *//*------------------------------------------------------------------------ */
int temp_sensor_count_get(void)
{
	int count;

	temp_sensor_init();

	if (cpu_is_omap44xx()) {
		count = genlist_getcount(&temp_sensor_list);
	} else if (cpu_is_omap54xx()) {
		count = genlist_getcount(&temp_sensor_list);
	} else if (cpu_is_dra7xx()) {
		count = genlist_getcount(&temp_sensor_list);
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		count = OMAPCONF_ERR_CPU;
	}

	dprintf("%s() = %d\n", __func__, count);
	return count;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp_sensor_list_get
 * @BRIEF		return the list of temperature sensor(s)
 * @RETURNS		list of temperature sensor(s)
 *			NULL in case of architecture is not supported
 * @DESCRIPTION		return the list of temperature sensor(s)
 *//*------------------------------------------------------------------------ */
const genlist *temp_sensor_list_get(void)
{
	temp_sensor_init();

	if (cpu_is_omap44xx()) {
		return (const genlist *) &temp_sensor_list;
	} else if (cpu_is_omap54xx()) {
		return (const genlist *) &temp_sensor_list;
	} else if (cpu_is_dra7xx()) {
		return (const genlist *) &temp_sensor_list;
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		return NULL;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp_sensor_s2id
 * @BRIEF		convert generic temperature sensor name (string)
 *			into platform-specific ID (integer).
 * @RETURNS		>= 0 platform-specific ID
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		sensor: generic temperature sensor name
 * @DESCRIPTION		convert generic temperature sensor name (string)
 *			into platform-specific ID (integer).
 *			To be used when calling architecture-specific functions.
 *//*------------------------------------------------------------------------ */
int temp_sensor_s2id(const char *sensor)
{
	int id;

	CHECK_NULL_ARG(sensor, OMAPCONF_ERR_ARG);

	if (cpu_is_omap44xx()) {
		if (strcasecmp(sensor, TEMP_SENSOR_BANDGAP) == 0)
			id = (int) TEMP44XX_BANDGAP;
		else if (strcasecmp(sensor, TEMP_SENSOR_HOTSPOT_MPU) == 0)
			id = (int) TEMP44XX_HOTSPOT;
		else if (strcasecmp(sensor, TEMP_SENSOR_MEM1) == 0)
			id = (int) TEMP44XX_DDR1_CS1;
		else if (strcasecmp(sensor, TEMP_SENSOR_MEM2) == 0)
			id = (int) TEMP44XX_DDR2_CS1;
		else if (strcasecmp(sensor, TEMP_SENSOR_PCB) == 0)
			id = (int) TEMP44XX_PCB;
		else
			id = OMAPCONF_ERR_ARG;
	} else if (cpu_is_omap54xx()) {
		if (strcasecmp(sensor, TEMP_SENSOR_MPU) == 0)
			id = (int) TEMP54XX_MPU;
		else if (strcasecmp(sensor, TEMP_SENSOR_HOTSPOT_MPU) == 0)
			id = (int) TEMP54XX_HOTSPOT_MPU;
		else if (strcasecmp(sensor, TEMP_SENSOR_GPU) == 0)
			id = (int) TEMP54XX_GPU;
		else if (strcasecmp(sensor, TEMP_SENSOR_HOTSPOT_GPU) == 0)
			id = (int) TEMP54XX_HOTSPOT_GPU;
		else if (strcasecmp(sensor, TEMP_SENSOR_MEM1) == 0)
			id = (int) TEMP54XX_EMIF1;
		else if (strcasecmp(sensor, TEMP_SENSOR_MEM2) == 0)
			id = (int) TEMP54XX_EMIF2;
		else if (strcasecmp(sensor, TEMP_SENSOR_CORE) == 0)
			id = (int) TEMP54XX_CORE;
		else if (strcasecmp(sensor, TEMP_SENSOR_PCB) == 0)
			id = (int) TEMP54XX_PCB;
		else if (strcasecmp(sensor, TEMP_SENSOR_CASE) == 0)
			id = (int) TEMP54XX_CASE;
		else if (strcasecmp(sensor, TEMP_SENSOR_CHARGER) == 0)
			id = (int) TEMP54XX_CHARGER;
		else
			id = OMAPCONF_ERR_ARG;
	} else if (cpu_is_dra7xx()) {
		if (strcasecmp(sensor, TEMP_SENSOR_MPU) == 0)
			id = (int) HWTEMP_DRA7XX_MPU;
		else if (strcasecmp(sensor, TEMP_SENSOR_GPU) == 0)
			id = (int) HWTEMP_DRA7XX_GPU;
		else if (strcasecmp(sensor, TEMP_SENSOR_CORE) == 0)
			id = (int) HWTEMP_DRA7XX_CORE;
		else if (strcasecmp(sensor, TEMP_SENSOR_IVA) == 0)
			id = (int) HWTEMP_DRA7XX_IVA;
		else if (strcasecmp(sensor, TEMP_SENSOR_DSPEVE) == 0)
			id = (int) HWTEMP_DRA7XX_DSPEVE;
		else
			id = OMAPCONF_ERR_ARG;
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		id = OMAPCONF_ERR_CPU;
	}

	dprintf("%s(%s) = %d\n", __func__, sensor, id);
	return id;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwtemp_sensor_s2id
 * @BRIEF		convert generic temperature sensor name (string)
 *			into platform-specific ID (integer).
 * @RETURNS		>= 0 platform-specific ID
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		sensor: generic temperature sensor name
 * @DESCRIPTION		convert generic temperature sensor name (string)
 *			into platform-specific ID (integer).
 *			To be used when calling architecture-specific functions.
 *//*------------------------------------------------------------------------ */
int hwtemp_sensor_s2id(const char *sensor)
{
	int id;

	CHECK_NULL_ARG(sensor, OMAPCONF_ERR_ARG);

	if (cpu_is_omap54xx()) {
		if (strcasecmp(sensor, TEMP_SENSOR_MPU) == 0)
			id = (int) HWTEMP54XX_MPU;
		else if (strcasecmp(sensor, TEMP_SENSOR_GPU) == 0)
			id = (int) HWTEMP54XX_GPU;
		else if (strcasecmp(sensor, TEMP_SENSOR_CORE) == 0)
			id = (int) HWTEMP54XX_CORE;
		else
			id = OMAPCONF_ERR_ARG;
	} else if (cpu_is_dra7xx()) {
		if (strcasecmp(sensor, TEMP_SENSOR_MPU) == 0)
			id = (int) HWTEMP_DRA7XX_MPU;
		else if (strcasecmp(sensor, TEMP_SENSOR_GPU) == 0)
			id = (int) HWTEMP_DRA7XX_GPU;
		else if (strcasecmp(sensor, TEMP_SENSOR_CORE) == 0)
			id = (int) HWTEMP_DRA7XX_CORE;
		else if (strcasecmp(sensor, TEMP_SENSOR_IVA) == 0)
			id = (int) HWTEMP_DRA7XX_IVA;
		else if (strcasecmp(sensor, TEMP_SENSOR_DSPEVE) == 0)
			id = (int) HWTEMP_DRA7XX_DSPEVE;
		else
			id = OMAPCONF_ERR_ARG;
	} else {
		fprintf(stderr, "omapconf: %s(): cpu not supported!!!\n", __func__);
		id = OMAPCONF_ERR_CPU;
	}

	dprintf("%s(%s) = %d\n", __func__, sensor, id);
	return id;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp_sensor_is_available
 * @BRIEF		check if temperature sensor is available.
 * @RETURNS		1 if temperature sensor is available
 *			0 if temperature sensor is NOT available
 * @param[in]		sensor: generic temperature sensor name
 * @DESCRIPTION		check if temperature sensor is available
 *			(platform-dependent).
 *//*------------------------------------------------------------------------ */
int temp_sensor_is_available(const char *sensor)
{
	int id;

	CHECK_NULL_ARG(sensor, 0);

	id = temp_sensor_s2id(sensor);
	if (id >= 0) {
		dprintf("%s(): %s is available.\n", __func__, sensor);
		return 1;
	} else {
		dprintf("%s(): %s is NOT available.\n", __func__, sensor);
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwtemp_sensor_is_available
 * @BRIEF		check if temperature sensor is available.
 * @RETURNS		1 if temperature sensor is available
 *			0 if temperature sensor is NOT available
 * @param[in]		sensor: generic temperature sensor name
 * @DESCRIPTION		check if temperature sensor is available
 *			(platform-dependent).
 *//*------------------------------------------------------------------------ */
int hwtemp_sensor_is_available(const char *sensor)
{
	int id;

	CHECK_NULL_ARG(sensor, 0);
	id = hwtemp_sensor_s2id(sensor);
	if (id >= 0)
	{
		dprintf("%s(): %s is available.\n", __func__, sensor);
		return 1;
	}
	else
	{
		dprintf("%s(): %s is NOT available.\n", __func__, sensor);
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp_sensor_get
 * @BRIEF		return temperature measured by temperature sensor.
 * @RETURNS		temperature measured by temperature sensor (Celcius)
 *			TEMP_ABSOLUTE_ZERO in case of error
 * @param[in]		sensor: generic temperature sensor name
 * @DESCRIPTION		return temperature measured by temperature sensor
 *			in Celcius degrees.
 *//*------------------------------------------------------------------------ */
int temp_sensor_get(const char *sensor)
{
	int id, temp;

	CHECK_NULL_ARG(sensor, TEMP_ABSOLUTE_ZERO);

	id = temp_sensor_s2id(sensor);
	if (id < 0)
		temp = TEMP_ABSOLUTE_ZERO;
	else if (cpu_is_omap44xx()) {
		temp = temp44xx_get(id);
	} else if (cpu_is_omap54xx()) {
		temp = temp54xx_get(id);
	} else if (cpu_is_dra7xx()) {
		temp = temp_dra7xx_get(id);
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		temp = TEMP_ABSOLUTE_ZERO;
	}

	dprintf("%s(%s) = %d\n", __func__, sensor, temp);
	return temp;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwtemp_sensor_get
 * @BRIEF		return temperature measured by temperature sensor hw registers.
 * @RETURNS		temperature measured by temperature sensor (Celcius)
 *			TEMP_ABSOLUTE_ZERO in case of error
 * @param[in]		sensor: generic temperature sensor name
 * @DESCRIPTION		return temperature measured by temperature sensor
 *			in Celcius degrees.
 *//*------------------------------------------------------------------------ */
int hwtemp_sensor_get(const char *sensor)
{
	int id, temp;

	CHECK_NULL_ARG(sensor, TEMP_ABSOLUTE_ZERO);

	id = hwtemp_sensor_s2id(sensor);
	if (id < 0) {
		temp = TEMP_ABSOLUTE_ZERO;
	} else if (cpu_is_omap54xx()) {
		temp = hwtemp54xx_get(id);
	} else if (cpu_is_dra7xx()) {
		temp = hwtemp_dra7xx_get(id);
	} else {
		fprintf(stderr, "omapconf: %s(): cpu not supported!!!\n", __func__);
		temp = TEMP_ABSOLUTE_ZERO;
	}

	dprintf("%s(%s) = %d\n", __func__, sensor, temp);
	return temp;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp_sensor_show
 * @BRIEF		display all available temperatures formatted in a table.
 * @RETURNS		temperatures formatted in a table
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_INTERNAL
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in,out]	stream: output file
 * @param[in,out]	sensor: generic temperature sensor name
 *				Use "all" to show all temperatures
 * @param[in]		hw: use s/w (driver based) read or hw_sensor read?
 * @DESCRIPTION		display all available temperatures formatted in a table.
 *			Display both Celcius and Fahrenheit degrees.
 *//*------------------------------------------------------------------------ */
static int _temp_sensor_show(FILE *stream, const char *sensor, const char hw)
{
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row = 0;
	int i, count, temp, temp_f;
	char temp_s[EMIF_TEMP_MAX_NAME_LENGTH];
	const char sensor2[TEMP_SENSOR_MAX_NAME_LENGTH];
	const genlist *list;

	CHECK_NULL_ARG(stream, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(sensor, OMAPCONF_ERR_ARG);

	if (strcasecmp(sensor, "all") != 0) {
		if (!temp_sensor_is_available(sensor)) {
			fprintf(stderr,
				"omapconf: '%s' temperature sensor is not available!\n",
				sensor);
			return OMAPCONF_ERR_NOT_AVAILABLE;
		}
		if (hw)
			temp = hwtemp_sensor_get(sensor);
		else
			temp = temp_sensor_get(sensor);
		if (temp == TEMP_ABSOLUTE_ZERO) {
			fprintf(stderr,
				"omapconf: could not retrieve '%s' temperature!\n",
				sensor);
			return OMAPCONF_ERR_INTERNAL;
		} else if ((strcasecmp(sensor, TEMP_SENSOR_MEM1) == 0) ||
				(strcasecmp(sensor, TEMP_SENSOR_MEM2) == 0)) {
			fprintf(stream, "%s\n",
				emif_mr4_convert((emif_mr4_code) temp,
					TEMP_CELCIUS_DEGREES));
			return 0;
		} else {
			fprintf(stream, "%d\n", temp);
			return 0;
		}
	}

	/* Retrieve temperature sensor list */
	list = temp_sensor_list_get();
	if (list == NULL) {
		fprintf(stderr, "omapconf: CPU not yet supported, sorry...\n");
		return OMAPCONF_ERR_INTERNAL;
	}

	/* Retrieve temperature sensor list count */
	count = temp_sensor_count_get();
	if (count <= 0) {
		fprintf(stderr, "omapconf: could not retrieve sensor count!\n");
		return OMAPCONF_ERR_INTERNAL;
	}
	dprintf("found %d temperature sensors\n", count);

	/* Fill table header */
	row = 0;
	autoadjust_table_init(table);
	autoadjust_table_strncpy(table, row, 0, "Sensor");
	autoadjust_table_strncpy(table, row, 1, "Temperature (C)");
	autoadjust_table_strncpy(table, row++, 2, "Temperature (F)");

	/* Fill table with temperatures */
	for (i = 0; i < count; i++) {
		genlist_get((genlist *) list, i, (char *) &sensor2);
		if (sensor2 == NULL) {
			fprintf(stderr,
				"omapconf: could not retrieve sensor!\n");
			return OMAPCONF_ERR_INTERNAL;
		}
		autoadjust_table_strncpy(table, row, 0, (char *) sensor2);
		dprintf("%s(): sensor is %s\n", __func__, sensor2);
		if (hw)
			temp = hwtemp_sensor_get(sensor2);
		else
			temp = temp_sensor_get(sensor2);
		if (temp != TEMP_ABSOLUTE_ZERO) {
			if ((strcasecmp(sensor2, TEMP_SENSOR_MEM1) == 0) ||
				(strcasecmp(sensor2, TEMP_SENSOR_MEM2) == 0)) {
				sprintf(temp_s, "%s",
					emif_mr4_convert((emif_mr4_code) temp,
						TEMP_CELCIUS_DEGREES));
				autoadjust_table_strncpy(table, row, 1, temp_s);
				sprintf(temp_s, "%s",
					emif_mr4_convert((emif_mr4_code) temp,
						TEMP_FAHRENHEIT_DEGREES));
				autoadjust_table_strncpy(table, row++, 2,
					temp_s);
			} else {
				sprintf(temp_s, "%d", temp);
				autoadjust_table_strncpy(table, row, 1, temp_s);
				temp_f = celcius2fahrenheit(temp);
				sprintf(temp_s, "%d", temp_f);
				autoadjust_table_strncpy(table, row++, 2,
					temp_s);
			}
		} else {
			autoadjust_table_strncpy(table, row, 1, "NA");
			autoadjust_table_strncpy(table, row++, 2, "NA");
		}
	}

	/* Display table */
	return autoadjust_table_fprint(stream, table, row, 3);
}


int temp_sensor_show(FILE *stream, const char *sensor)
{
	return _temp_sensor_show(stream, sensor, 0);
}


int hwtemp_sensor_show(FILE *stream, const char *sensor)
{
	return _temp_sensor_show(stream, sensor, 1);
}
