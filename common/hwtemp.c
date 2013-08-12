/*
 *
 * @Component			OMAPCONF
 * @Filename			hwtemp.c
 * @Description			Reads Temperature Sensors Registers
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


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hwtemp_get
 * @BRIEF		return temperature measured by selected sensor's
 *			register buffer	(in degrees celcius)
 * @RETURNS		measured temperature in case of success
 *			TEMP_ABSOLUTE_ZERO (-273) in case of error
 * @param[in]		temp_register: temperature register to read
 * @param[in]		mask: mask to use (applied before shift)
 * @param[in]		shift: how many bits to shift
 * @param[in]		conv_table: mask to use
 * @DESCRIPTION		return temperature measured by selected sensor
 *			(in degrees celcius)
 *//*------------------------------------------------------------------------ */
int hwtemp_get(reg *temp_register, unsigned int mask, unsigned int shift,
	       unsigned int start_val, const short int *conv_table,
	       unsigned int sizeof_conv_table)
{
	unsigned int val;

	/*
	 * read the register and return the register
	 * only the lower 10 bits then take that ADC code and convert to celcius
	 */
	val = reg_read(temp_register);
	val &= mask;
	val >>= shift;

	if (val < start_val) {
		fprintf(stderr, "%s: read value=%d < start_value = %d\n",
			__func__, val, start_val);
		return TEMP_ABSOLUTE_ZERO;
	}
	val -= start_val;

	if (val >= sizeof_conv_table) {
		fprintf(stderr, "%s: read value=%d > max_value = %d\n",
			__func__, val + start_val, sizeof_conv_table + start_val - 1);
		return TEMP_ABSOLUTE_ZERO;
	}

	return conv_table[val];
}
