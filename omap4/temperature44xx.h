/*
 *
 * @Component			OMAPCONF
 * @Filename			temperature44xx.h
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


#ifndef __TEMPERATURE44XX_H__
#define __TEMPERATURE44XX_H__


#include <voltdm44xx.h>


typedef enum {
	TEMP44XX_BANDGAP,
	TEMP44XX_HOTSPOT,
	TEMP44XX_DDR1_CS1,
	TEMP44XX_DDR1_CS2,
	TEMP44XX_DDR2_CS1,
	TEMP44XX_DDR2_CS2,
	TEMP44XX_PCB,
	TEMP44XX_ID_MAX
} temp44xx_sensor_id;


typedef enum {
	OMAP4_EMIF_TEMP_BELOW_85C = 0x3,
	OMAP4_EMIF_TEMP_ABOVE_85C = 0x5,
	OMAP4_EMIF_TEMP_EXCEED_105C = 0x7,
	OMAP4_EMIF_TEMP_RESERVED
} omap4_emif_temperature;


temp44xx_sensor_id temp44xx_voltdm2sensor_id(voltdm44xx_id vdd_id);
const char *temp44xx_name_get(temp44xx_sensor_id id);
int temp44xx_get(temp44xx_sensor_id id);


#endif
