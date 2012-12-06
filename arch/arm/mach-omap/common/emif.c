/*
 *
 * @Component			OMAPCONF
 * @Filename			emif.c
 * @Description			EMIF Common Definitions & Functions
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


#include <emif.h>
#include <stdio.h>


/* #define EMIF_DEBUG */
#ifdef EMIF_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static const char
	emif_mr4_code_table_c[EMIF_TEMP_RESERVED + 1][EMIF_TEMP_MAX_NAME_LENGTH] = {
	"FIXME",
	"FIXME",
	"FIXME",
	"< 85",
	"FIXME",
	">= 85 & <= 105",
	"FIXME",
	"> 105",
	"FIXME"};


static const char
	emif_mr4_code_table_f[EMIF_TEMP_RESERVED + 1][EMIF_TEMP_MAX_NAME_LENGTH] = {
	"FIXME",
	"FIXME",
	"FIXME",
	"< 185",
	"FIXME",
	">= 185 & <= 221",
	"FIXME",
	"> 221",
	"FIXME"};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		emif_mr4_convert
 * @BRIEF		convert LPDDR2 MR4 code into string
 * @RETURNS		MR4 code as a string indicating temperature range
 *			"FIXME" string in case of error
 * @param[in]		mr4: LPDDR2 MR4 code
 * @param[in]		unit: select celcius ou fahrenheit
 * @DESCRIPTION		convert LPDDR2 MR4 code into string. MR4 code is not a
 *			temperature, but a temperature range, that cannot be
 *			converted to integer. Hence return it a string.
 *//*------------------------------------------------------------------------ */
const char *emif_mr4_convert(emif_mr4_code mr4, temperature_unit unit)
{
	if (mr4 > EMIF_TEMP_RESERVED)
		mr4 = EMIF_TEMP_RESERVED;

	if (unit == TEMP_CELCIUS_DEGREES) {
		dprintf("%s(%d) = %s\n", __func__,
			mr4, emif_mr4_code_table_c[mr4]);
		return emif_mr4_code_table_c[mr4];
	} else if (unit == TEMP_FAHRENHEIT_DEGREES) {
		dprintf("%s(%d) = %s\n", __func__,
			mr4, emif_mr4_code_table_f[mr4]);
		return emif_mr4_code_table_f[mr4];
	} else {
		fprintf(stderr,
			"omapconf: %s() called with incorrect unit ""(%d), "
			"defaulting to celcius degrees.\n", __func__, unit);
		dprintf("%s(%d) = %s\n", __func__,
			mr4, emif_mr4_code_table_c[mr4]);
		return emif_mr4_code_table_c[mr4];
	}
}
