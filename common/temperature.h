/*
 *
 * @Component			OMAPCONF
 * @Filename			temperature.h
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


#ifndef __TEMPERATURE_H__
#define __TEMPERATURE_H__


#include <stdio.h>
#include <genlist.h>


typedef enum {
	TEMP_CELCIUS_DEGREES,
	TEMP_FAHRENHEIT_DEGREES,
	TEMP_UNIT_MAX
} temperature_unit;


#define TEMP_ABSOLUTE_ZERO		-273

#define TEMP_SENSOR_MAX_NAME_LENGTH	16

#define TEMP_SENSOR_BANDGAP	((const char *) "Bandgap") /* OMAP4 */
#define TEMP_SENSOR_MPU		((const char *) "MPU") /* OMAP5 & DRA7 */
#define TEMP_SENSOR_HOTSPOT_MPU	((const char *) "MPU_Hotspot") /* Common */
#define TEMP_SENSOR_GPU		((const char *) "GPU") /* OMAP5 & DRA7 */
#define TEMP_SENSOR_HOTSPOT_GPU	((const char *) "GPU_Hotspot") /* OMAP5 */
#define TEMP_SENSOR_MEM1	((const char *) "MEM1") /* Common */
#define TEMP_SENSOR_MEM2	((const char *) "MEM2") /* Common */
#define TEMP_SENSOR_CORE	((const char *) "CORE") /* OMAP5 & DRA7 */
#define TEMP_SENSOR_PCB		((const char *) "PCB") /* Common */
#define TEMP_SENSOR_CASE	((const char *) "CASE") /* OMAP5 */
#define TEMP_SENSOR_CHARGER	((const char *) "CHARGER") /* OMAP5 */
#define TEMP_SENSOR_DSPEVE	((const char *) "DSPEVE") /* DRA7 */
#define TEMP_SENSOR_IVA		((const char *) "IVA") /* DRA7 */


void temp_sensor_init(void);
void temp_sensor_deinit(void);

int temp_sensor_count_get(void);
const genlist *temp_sensor_list_get(void);

const char *temp_sensor_voltdm2sensor(const char *voltdm);
int temp_sensor_s2id(const char *sensor);
int hwtemp_sensor_s2id(const char *sensor);

int temp_sensor_is_available(const char *sensor);
int hwtemp_sensor_is_available(const char *sensor);
int temp_sensor_get(const char *sensor);
int hwtemp_sensor_get(const char *sensor);
int temp_sensor_show(FILE *stream, const char *sensor);
int hwtemp_sensor_show(FILE *stream, const char *sensor);


#endif
