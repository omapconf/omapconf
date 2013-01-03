/*
 *
 * @Component			OMAPCONF
 * @Filename			sr.c
 * @Description			SMARTREFLEX Common Definitions & Functions
 * @Author			Patrick Titiano (p-titiano@ti.com)
 * @Date			2006
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2006 Texas Instruments Incorporated - http://www.ti.com/
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


#include <sr.h>
#include <lib.h>
#include <cpuinfo.h>
#include <autoadjust_table.h>
#include <help.h>
#include <string.h>
#include <pmic.h>
#include <voltdm44xx.h>
#include <clock44xx.h>
#include <module.h>
#include <voltdomain.h>
#include <vp.h>
#include <opp.h>


/* #define SR_DEBUG */
#ifdef SR_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


#define SR_ACCUMDATA_POS		22
#define SR_ACCUMDATA_LEN		10
#define SR_SRCLKLENGTH_POS		12
#define SR_SRCLKLENGTH_LEN		10
#define SR_SRENABLE_POS			11
#define SR_SENENABLE_POS		10
#define SR_ERRORGENERATORENABLE_POS	9
#define SR_MINMAXAVGENABLE_POS		8
#define SR_LVTSENENABLE_POS		4
#define SR_LVTSENNENABLE_POS		3
#define SR_LVTSENPENABLE_POS		2
#define SR_SENNENABLE_POS		1
#define SR_SENPENABLE_POS		0

#define SR_AVGERRVALID_POS		3
#define SR_MINMAXAVGVALID_POS		2
#define SR_ERRORGENERATORVALID_POS	1
#define SR_MINMAXAVGACCUMVALID_POS	0

#define SR_SENPVAL_POS			16
#define SR_SENPVAL_LEN			16
#define SR_SENNVAL_POS			0
#define SR_SENNVAL_LEN			16

#define SR_SENPMIN_POS			16
#define SR_SENPMIN_LEN			16
#define SR_SENNMIN_POS			0
#define SR_SENNMIN_LEN			16

#define SR_SENPMAX_POS			16
#define SR_SENPMAX_LEN			16
#define SR_SENNMAX_POS			0
#define SR_SENNMAX_LEN			16

#define SR_SENPAVG_POS			16
#define SR_SENPAVG_LEN			16
#define SR_SENNAVG_POS			0
#define SR_SENNAVG_LEN			16

#define SR_SENPAVGWEIGHT_POS		2
#define SR_SENPAVGWEIGHT_LEN		2
#define SR_SENNAVGWEIGHT_POS		0
#define SR_SENNAVGWEIGHT_LEN		2

#define SR_SENPGAIN_POS			20
#define SR_SENPGAIN_LEN			4
#define SR_SENNGAIN_POS			16
#define SR_SENNGAIN_LEN			4
#define SR_SENPRN_POS			8
#define SR_SENPRN_LEN			8
#define SR_SENNRN_POS			0
#define SR_SENNRN_LEN			8

#define SR_MCUACCUMINTSTATRAW_POS	3
#define SR_MCUVALIDINTSTATRAW_POS	2
#define SR_MCUBOUNDSINTSTATRAW_POS	1
#define SR_MCUDISABLEACKINTSTATRAW_POS	0

#define SR_MCUACCUMINTSTATENA_POS	3
#define SR_MCUVALIDINTSTATENA_POS	2
#define SR_MCUBOUNDSINTSTATENA_POS	1
#define SR_MCUDISABLEACKINTSTATENA_POS	0

#define SR_MCUACCUMINTENASET_POS	3
#define SR_MCUVALIDINTENASET_POS	2
#define SR_MCUBOUNDSINTENASET_POS	1
#define SR_MCUDISABLEACKINTENASET_POS	0

#define SR_MCUACCUMINTENACLR_POS	3
#define SR_MCUVALIDINTENACLR_POS	2
#define SR_MCUBOUNDSINTENACLR_POS	1
#define SR_MCUDISABLEACKINTENACLR_POS	0

#define SR_AVGERROR_LEN			8
#define SR_AVGERROR_POS			8
#define SR_SENERROR_LEN			8
#define SR_SENERROR_POS			0

#define SR_WAKEUPENABLE_POS		26
#define SR_IDLEMODE_POS			24
#define SR_IDLEMODE_LEN			2
#define SR_VPBOUNDSINTSTATENA_POS	23
#define SR_VPBOUNDSINTENABLE_POS	22
#define SR_ERRWEIGHT_POS		16
#define SR_ERRWEIGHT_LEN		3
#define SR_ERRMAXLIMIT_POS		8
#define SR_ERRMAXLIMIT_LEN		8
#define SR_ERRMINLIMIT_POS		0
#define SR_ERRMINLIMIT_LEN		8


#define SR_AUDIT_SHOW_STATUS(curr, golden) \
		if (curr == golden) { \
			snprintf(table[row++][3], TABLE_MAX_ELT_LEN, "Pass"); \
		} else { \
			snprintf(table[row++][3], TABLE_MAX_ELT_LEN, "FAIL"); \
			(*err_nbr)++; \
		}


static const char
	sr_sensor_type_names[SR_SENSOR_TYPE_MAX + 1][SR_SENSOR_TYPE_MAX_LENGTH] = {
	"N",
	"P",
	"FIXME"
};


static const char
	sr_sensor_value_type_names[SR_SENSOR_VAL_TYPE_MAX + 1][SR_SENSOR_VAL_TYPE_MAX_LENGTH] = {
	"Latest",
	"MIN",
	"MAX",
	"AVG",
	"FIXME"
};


static const char
	sr_sensor_value_status_names[SR_SENSOR_VAL_STATUS_MAX + 1][SR_SENSOR_VAL_STATUS_MAX_LENGTH] = {
	"Invalid",
	"Valid",
	"Valid & Final",
	"FIXME"
};


static const char
	sr_interrupt_type_names[SR_IRQ_TYPE_MAX + 1][SR_IRQ_TYPE_MAX_LENGTH] = {
	"MCU DisableAck",
	"MCU Bounds",
	"MCU Valid",
	"MCU Accum",
	"VP bounds",
	"FIXME"
};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_sensor_type_name_get
 * @BRIEF		return sensor type name
 * @RETURNS		sensor type name on success
 *			"FIXME" string in case of error
 * @param[in]		type: valid sensor type ID
 * @DESCRIPTION		return sensor type name
 *//*------------------------------------------------------------------------ */
const char *sr_sensor_type_name_get(sr_sensor_type type)
{
	if (type < SR_SENSOR_TYPE_MAX)
		return sr_sensor_type_names[type];
	else
		return sr_sensor_type_names[SR_SENSOR_TYPE_MAX];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_sensor_value_type_name_get
 * @BRIEF		return sensor value type name
 * @RETURNS		sensor value type name on success
 *			"FIXME" string in case of error
 * @param[in]		type: valid sensor value type ID
 * @DESCRIPTION		return sensor value type name
 *//*------------------------------------------------------------------------ */
const char *sr_sensor_value_type_name_get(sr_sensor_value_type type)
{
	if (type < SR_SENSOR_VAL_TYPE_MAX)
		return sr_sensor_value_type_names[type];
	else
		return sr_sensor_value_type_names[SR_SENSOR_VAL_TYPE_MAX];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_sensor_value_status_name_get
 * @BRIEF		return sensor value status name
 * @RETURNS		sensor value status name on success
 *			"FIXME" string in case of error
 * @param[in]		status: valid sensor value status ID
 * @DESCRIPTION		return sensor value status name
 *//*------------------------------------------------------------------------ */
const char *sr_sensor_value_status_name_get(sr_sensor_value_status status)
{
	if (status < SR_SENSOR_VAL_STATUS_MAX)
		return sr_sensor_value_status_names[status];
	else
		return sr_sensor_value_status_names[SR_SENSOR_VAL_STATUS_MAX];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_interrupt_type_name_get
 * @BRIEF		return SR interrupt type name
 * @RETURNS		interrupt type name on success
 *			"FIXME" string in case of error
 * @param[in]		type: valid interrupt type ID
 * @DESCRIPTION		return SR interrupt type name
 *//*------------------------------------------------------------------------ */
const char *sr_interrupt_type_name_get(sr_interrupt_type type)
{
	if (type < SR_IRQ_TYPE_MAX)
		return sr_interrupt_type_names[type];
	else
		return sr_interrupt_type_names[SR_IRQ_TYPE_MAX];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_is_enabled
 * @BRIEF		check if SR module is enabled by analyzing SRCONFIG
 *			register content
 * @RETURNS		1 if module is enabled, 0 otherwise.
 * @param[in]		sr_config: SRCONFIG register content
 * @DESCRIPTION		check if SR module is enabled by analyzing SRCONFIG
 *			register content
 *//*------------------------------------------------------------------------ */
unsigned char sr_is_enabled(unsigned int sr_config)
{
	return extract_bit(sr_config, SR_SRENABLE_POS);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_has_converged
 * @BRIEF		check if SR module has converged
 * @RETURNS		1 if module is enabled, 0 otherwise
 * @param[in]		errconfig: ERRCONFIG register content
 * @param[in]		senerror: SENERROR register content
 * @DESCRIPTION		check if SR module has converged
 *//*------------------------------------------------------------------------ */
unsigned char sr_has_converged(unsigned int errconfig, unsigned int senerror)
{
	signed char minlimit, maxlimit, avgerr;

	minlimit = (signed char) sr_error_generator_minlimit_get(errconfig);
	maxlimit = (signed char) sr_error_generator_maxlimit_get(errconfig);
	avgerr = (signed char) sr_avg_sensor_error_value_get(senerror);

	if ((avgerr <= maxlimit) && (avgerr >= minlimit)) {
		dprintf("%s(): minlimit=%d maxlimit=%d avgerr=%d => "
			"converged\n", __func__, minlimit, maxlimit, avgerr);
		return 1;
	} else {
		dprintf("%s(): minlimit=%d maxlimit=%d avgerr=%d => "
			"NOT converged\n", __func__, minlimit, maxlimit,
			avgerr);
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_is_sensors_disabled
 * @BRIEF		check if SR sensors (N+P) are disabled
 * @RETURNS		1 if SR sensors (N+P) are disabled, 0 otherwise
 * @param[in]		sr_config: SRCONFIG register content
 * @DESCRIPTION		check if SR sensors (N+P) are disabled
 *//*------------------------------------------------------------------------ */
unsigned char sr_is_sensors_disabled(unsigned int sr_config)
{
	return !extract_bit(sr_config, SR_SENENABLE_POS);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_is_lvt_sensors_disabled
 * @BRIEF		check if SR LVT sensors (N+P) are disabled
 * @RETURNS		1 if SR LVT sensors (N+P) are disabled, 0 otherwise
 * @param[in]		sr_config: SRCONFIG register content
 * @DESCRIPTION		check if SR LVT sensors (N+P) are disabled
 *//*------------------------------------------------------------------------ */
unsigned char sr_is_lvt_sensors_disabled(unsigned int sr_config)
{
	return !extract_bit(sr_config, SR_LVTSENENABLE_POS);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_is_sensor_enabled
 * @BRIEF		check if SR sensor is enabled
 * @RETURNS		1 if SR sensor is enabled, 0 otherwise
 * @param[in]		sr_config: SRCONFIG register content
 * @param[in]		type: sensor type
 * @DESCRIPTION		check if SR sensor is enabled
 *//*------------------------------------------------------------------------ */
unsigned char sr_is_sensor_enabled(unsigned int sr_config, sr_sensor_type type)
{
	switch (type) {
	case SR_SENSOR_N:
		return extract_bit(sr_config, SR_SENNENABLE_POS);
	case SR_SENSOR_P:
		return extract_bit(sr_config, SR_SENPENABLE_POS);
	default:
		fprintf(stderr, "%s(): incorrect sensor type! (%u)\n", __func__,
			type);
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_is_lvt_sensor_enabled
 * @BRIEF		check if SR LVT sensor is enabled
 * @RETURNS		1 if SR LVT sensor is enabled, 0 otherwise
 * @param[in]		sr_config: SRCONFIG register content
 * @param[in]		type: sensor type
 * @DESCRIPTION		check if SR LVT sensor is enabled
 *//*------------------------------------------------------------------------ */
unsigned char sr_is_lvt_sensor_enabled(unsigned int sr_config,
	sr_sensor_type type)
{
	switch (type) {
	case SR_SENSOR_N:
		return extract_bit(sr_config, SR_LVTSENNENABLE_POS);
	case SR_SENSOR_P:
		return extract_bit(sr_config, SR_LVTSENPENABLE_POS);
	default:
		fprintf(stderr, "%s(): incorrect sensor type! (%u)\n", __func__,
			type);
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_is_error_generator_enabled
 * @BRIEF		check if SR error generator is enabled
 * @RETURNS		1 if SR error generator is enabled, 0 otherwise
 * @param[in]		sr_config: SRCONFIG register content
 * @DESCRIPTION		check if SR error generator is enabled
 *//*------------------------------------------------------------------------ */
unsigned char sr_is_error_generator_enabled(unsigned int sr_config)
{
	return extract_bit(sr_config, SR_ERRORGENERATORENABLE_POS);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_is_minmaxavg_detector_enabled
 * @BRIEF		check if SR min/max/avg detector is enabled
 * @RETURNS		1 if SR min/max/avg detector is enabled, 0 otherwise
 * @param[in]		sr_config: SRCONFIG register content
 * @DESCRIPTION		check if SR min/max/avg detector is enabled
 *//*------------------------------------------------------------------------ */
unsigned char sr_is_minmaxavg_detector_enabled(unsigned int sr_config)
{
	return extract_bit(sr_config, SR_MINMAXAVGENABLE_POS);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_accumdata_count_get
 * @BRIEF		return the number of values to accumulate
 * @RETURNS		number of values to accumulate (ACCUMDATA)
 * @param[in]		sr_config: SRCONFIG register content
 * @DESCRIPTION		return the number of values to accumulate
 *//*------------------------------------------------------------------------ */
unsigned char sr_accumdata_count_get(unsigned int sr_config)
{
	return extract_bitfield(sr_config,
		SR_ACCUMDATA_POS, SR_ACCUMDATA_LEN);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_clk_div_get
 * @BRIEF		return the value of the internal source clock divider
 * @RETURNS		value of the internal source clock divider (SRCLKLENGTH)
 * @param[in]		sr_config: SRCONFIG register content
 * @DESCRIPTION		return the value of the internal source clock divider
 *//*------------------------------------------------------------------------ */
unsigned char sr_clk_div_get(unsigned int sr_config)
{
	return extract_bitfield(sr_config,
		SR_SRCLKLENGTH_POS, SR_SRCLKLENGTH_LEN);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_clk_rate_get
 * @BRIEF		return the rate of the SR clock, considering internal
 *			divider
 * @RETURNS		rate of the SR clock, considering internal divider (KHz)
 * @param[in]		sr_config: SRCONFIG register content
 * @param[in]		sr_sysclk: smartreflex sysclk rate (MHz)
 * @DESCRIPTION		return the rate of the SR clock, considering internal
 *			divider
 *//*------------------------------------------------------------------------ */
double sr_clk_rate_get(unsigned int sr_config, double sr_sysclk)
{
	return (sr_sysclk * 1000.0) /
		(2.0 * (double) sr_clk_div_get(sr_config));
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_avg_weighting_factor_get
 * @BRIEF		return the sensor averaging weighting factor (P & N)
 * @RETURNS		sensor averaging weighting factor (P & N)
 * @param[in]		avgweight: AVGWEIGHT register content
 * @param[in]		type: valid sensor type ID
 * @DESCRIPTION		return the sensor averaging weighting factor (P & N)
 *//*------------------------------------------------------------------------ */
unsigned char sr_avg_weighting_factor_get(unsigned int avgweight,
	sr_sensor_type type)
{
	switch (type) {
	case SR_SENSOR_N:
		return (unsigned char) extract_bitfield(avgweight,
			SR_SENNAVGWEIGHT_POS, SR_SENNAVGWEIGHT_LEN);
	case SR_SENSOR_P:
		return (unsigned char) extract_bitfield(avgweight,
			SR_SENPAVGWEIGHT_POS, SR_SENPAVGWEIGHT_LEN);
	default:
		fprintf(stderr, "%s(): incorrect sensor type! (%u)\n", __func__,
			type);
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_gain_get
 * @BRIEF		return the reciprocal gain (P & N)
 * @RETURNS		reciprocal gain (P & N)
 * @param[in]		nvaluereciprocal: NVALUERECIPROCAL register content
 * @param[in]		type: valid sensor type ID
 * @DESCRIPTION		return the reciprocal gain (P & N)
 *//*------------------------------------------------------------------------ */
unsigned char sr_gain_get(unsigned int nvaluereciprocal, sr_sensor_type type)
{
	switch (type) {
	case SR_SENSOR_N:
		return extract_bitfield(nvaluereciprocal,
			SR_SENNGAIN_POS, SR_SENNGAIN_LEN);
	case SR_SENSOR_P:
		return extract_bitfield(nvaluereciprocal,
			SR_SENPGAIN_POS, SR_SENPGAIN_LEN);
	default:
		fprintf(stderr, "%s(): incorrect sensor type! (%u)\n", __func__,
			type);
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_scale_value_get
 * @BRIEF		return the reciprocal scale value (P & N)
 * @RETURNS		reciprocal scale value (P & N)
 * @param[in]		nvaluereciprocal: NVALUERECIPROCAL register content
 * @param[in]		type: valid sensor type ID
 * @DESCRIPTION		return the reciprocal scale value (P & N)
 *//*------------------------------------------------------------------------ */
unsigned char sr_scale_value_get(unsigned int nvaluereciprocal,
	sr_sensor_type type)
{
	switch (type) {
	case SR_SENSOR_N:
		return extract_bitfield(nvaluereciprocal,
			SR_SENNRN_POS, SR_SENNRN_LEN);
	case SR_SENSOR_P:
		return extract_bitfield(nvaluereciprocal,
			SR_SENPRN_POS, SR_SENPRN_LEN);
	default:
		fprintf(stderr, "%s(): incorrect sensor type! (%u)\n", __func__,
			type);
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_ntarget_get
 * @BRIEF		return the sensor NTarget (P & N)
 * @RETURNS		sensor NTarget
 * @param[in]		nvaluereciprocal: NVALUERECIPROCAL register content
 * @param[in]		type: valid sensor type ID
 * @DESCRIPTION		return the sensor NTarget (P & N)
 *//*------------------------------------------------------------------------ */
unsigned int sr_ntarget_get(unsigned int nvaluereciprocal, sr_sensor_type type)
{
	unsigned char gain, scale;
	double ntarget;

	gain = sr_gain_get(nvaluereciprocal, type);
	scale = sr_scale_value_get(nvaluereciprocal, type);
	ntarget = 1.0 / ((double) scale / (double) (1 << (gain + 8)));
	dprintf("%s(): NVALUERECIPROCAL=0x%08X gain=%u scale=%u ntarget=%u\n",
		__func__, nvaluereciprocal, gain, scale,
		1 + (unsigned int) ntarget);
	return 1 + (unsigned int) ntarget;

}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_error_generator_limit_hex2percent
 * @BRIEF		convert error limit HEX signed value into %
 * @RETURNS		error limit value in %
 * @param[in]		limit: error limit HEX signed value
 * @DESCRIPTION		convert error limit HEX signed value into %
 *//*------------------------------------------------------------------------ */
double sr_error_generator_limit_hex2percent(signed char limit)
{
	return 0.8 * (double) limit;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_error_generator_minlimit_get
 * @BRIEF		return the RAW lower limit of SenError for interrupt
 *			generation
 * @RETURNS		RAW lower limit ("ERRMINLIMIT")
 * @param[in]		errconfig: ERRCONFIG register content
 * @DESCRIPTION		return the RAW lower limit of SenError for interrupt
 *			generation
 *//*------------------------------------------------------------------------ */
unsigned char sr_error_generator_minlimit_get(unsigned int errconfig)
{
	return (unsigned char) extract_bitfield(errconfig,
		SR_ERRMINLIMIT_POS, SR_ERRMINLIMIT_LEN);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_error_generator_minlimit_percentage_get
 * @BRIEF		return the percentage of lower limit of SenError
 *			for interrupt generation
 * @RETURNS		lower limit ("ERRMINLIMIT") percentage
 * @param[in]		errconfig: ERRCONFIG register content
 * @DESCRIPTION		return the percentage of lower limit of SenError
 *			for interrupt generation
 *//*------------------------------------------------------------------------ */
double sr_error_generator_minlimit_percentage_get(unsigned int errconfig)
{
	return sr_error_generator_limit_hex2percent(
		(signed char) sr_error_generator_minlimit_get(errconfig));
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_error_generator_maxlimit_get
 * @BRIEF		return the RAW upper limit of SenError for interrupt
 *			generation
 * @RETURNS		RAW upper limit ("ERRMAXLIMIT")
 * @param[in]		errconfig: ERRCONFIG register content
 * @DESCRIPTION		return the RAW upper limit of SenError for interrupt
 *			generation
 *//*------------------------------------------------------------------------ */
unsigned char sr_error_generator_maxlimit_get(unsigned int errconfig)
{
	return (unsigned char) extract_bitfield(errconfig,
		SR_ERRMAXLIMIT_POS, SR_ERRMAXLIMIT_LEN);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_error_generator_maxlimit_percentage_get
 * @BRIEF		return the percentage of upper limit of SenError
 *			for interrupt generation
 * @RETURNS		upper limit ("ERRMAXLIMIT") percentage
 * @param[in]		errconfig: ERRCONFIG register content
 * @DESCRIPTION		return the percentage of upper limit of SenError
 *			for interrupt generation
 *//*------------------------------------------------------------------------ */
double sr_error_generator_maxlimit_percentage_get(unsigned int errconfig)
{
	return sr_error_generator_limit_hex2percent(
		(signed char) sr_error_generator_maxlimit_get(errconfig));
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_error_generator_weight_get
 * @BRIEF		return the sensor error weighting factor (ERRWEIGHT)
 * @RETURNS		AvgSenError weight (ERRWEIGHT)
 * @param[in]		errconfig: ERRCONFIG register content
 * @DESCRIPTION		return the sensor error weighting factor (ERRWEIGHT)
 *//*------------------------------------------------------------------------ */
unsigned char sr_error_generator_weight_get(unsigned int errconfig)
{
	return (unsigned char) extract_bitfield(errconfig,
		SR_ERRWEIGHT_POS, SR_ERRWEIGHT_LEN);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_error_generator_idle_mode_get
 * @BRIEF		return sensor error generator idle mode
 * @RETURNS		sensor error generator idle mode
 * @param[in]		errconfig: ERRCONFIG register content
 * @DESCRIPTION		return sensor error generator idle mode
 *//*------------------------------------------------------------------------ */
mod_idle_mode sr_error_generator_idle_mode_get(unsigned int errconfig)
{
	return extract_bitfield(errconfig,
		SR_IDLEMODE_POS, SR_IDLEMODE_LEN);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_is_error_generator_wakeup_enabled
 * @BRIEF		check if SR error generator module WAKEUP generation
 *			is enabled
 * @RETURNS		1 if module WAKEUP generation is enabled, 0 otherwise
 * @param[in]		errconfig: ERRCONFIG register content
 * @DESCRIPTION		check if SR error generator module WAKEUP generation
 *			is enabled
 *//*------------------------------------------------------------------------ */
unsigned char sr_is_error_generator_wakeup_enabled(unsigned int errconfig)
{
	return extract_bit(errconfig, SR_WAKEUPENABLE_POS);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_irq_is_enabled
 * @BRIEF		check if SR interrupt of type 'irq' is enabled
 * @RETURNS		1 if interrupt is enabled, 0 otherwise
 * @param[in]		irqenable_set: IRQENABLE_SET register content
 * @param[in]		errconfig: ERRCONFIG register content
 * @param[in]		irq: interrupt type
 * @DESCRIPTION		check if SR interrupt of type 'irq' is enabled
 *//*------------------------------------------------------------------------ */
unsigned char sr_irq_is_enabled(unsigned int irqenable_set,
	unsigned int errconfig, sr_interrupt_type type)
{
	switch (type) {
	case SR_IRQ_MCUDISABLEACK:
		return extract_bit(irqenable_set,
			SR_MCUDISABLEACKINTENASET_POS);
	case SR_IRQ_MCUBOUNDS:
		return extract_bit(irqenable_set, SR_MCUBOUNDSINTENASET_POS);
	case SR_IRQ_MCUVALID:
		return extract_bit(irqenable_set, SR_MCUVALIDINTENASET_POS);
	case SR_IRQ_MCUACCUM:
		return extract_bit(irqenable_set, SR_MCUACCUMINTENASET_POS);
	case SR_IRQ_VPBOUNDS:
		return extract_bit(errconfig, SR_VPBOUNDSINTENABLE_POS);
	default:
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_irq_status_is_set
 * @BRIEF		check if SR interrupt of type 'irq' status is set
 *			(pending)
 * @RETURNS		1 if interrupt status is set, 0 otherwise
 * @param[in]		irqstatus: IRQSTATUS register content
 * @param[in]		errconfig: ERRCONFIG register content
 * @param[in]		type: interrupt type
 * @DESCRIPTION		check if SR interrupt of type 'irq' status is set
 *			(pending)
 *//*------------------------------------------------------------------------ */
unsigned char sr_irq_status_is_set(unsigned int irqstatus,
	unsigned int errconfig, sr_interrupt_type type)
{
	switch (type) {
	case SR_IRQ_MCUDISABLEACK:
		return extract_bit(irqstatus,
			SR_MCUDISABLEACKINTSTATENA_POS);
	case SR_IRQ_MCUBOUNDS:
		return extract_bit(irqstatus, SR_MCUBOUNDSINTSTATENA_POS);
	case SR_IRQ_MCUVALID:
		return extract_bit(irqstatus, SR_MCUVALIDINTSTATENA_POS);
	case SR_IRQ_MCUACCUM:
		return extract_bit(irqstatus, SR_MCUACCUMINTSTATENA_POS);
	case SR_IRQ_VPBOUNDS:
		return extract_bit(errconfig, SR_VPBOUNDSINTSTATENA_POS);
	default:
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_irq_raw_status_is_set
 * @BRIEF		check if SR interrupt of type 'irq' status is set
 *			(pending).
 *			NB: VPBOUNDS interrupt has no raw interrupt status flag
 * @RETURNS		1 if interrupt raw status is set, 0 otherwise
 * @param[in]		irqstatus_raw: IRQSTATUS_RAW register content
 * @param[in]		type: interrupt type
 * @DESCRIPTION		check if SR interrupt of type 'irq' status is set
 *			(pending).
 *			NB: VPBOUNDS interrupt has no raw interrupt status flag
 *//*------------------------------------------------------------------------ */
unsigned char sr_irq_raw_status_is_set(unsigned int irqstatus_raw,
	sr_interrupt_type type)
{
	switch (type) {
	case SR_IRQ_MCUDISABLEACK:
		return extract_bit(irqstatus_raw,
			SR_MCUDISABLEACKINTSTATRAW_POS);
	case SR_IRQ_MCUBOUNDS:
		return extract_bit(irqstatus_raw, SR_MCUBOUNDSINTSTATRAW_POS);
	case SR_IRQ_MCUVALID:
		return extract_bit(irqstatus_raw, SR_MCUVALIDINTSTATRAW_POS);
	case SR_IRQ_MCUACCUM:
		return extract_bit(irqstatus_raw, SR_MCUACCUMINTSTATRAW_POS);
	case SR_IRQ_VPBOUNDS:
		fprintf(stderr, "%s(): error: VPBOUNDS has no raw interrupt "
			"status flag.\n", __func__);
	default:
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_sensor_error_value_status_get
 * @BRIEF		return the current status of sensor error value
 * @RETURNS		sensor error value (SenError) status
 * @param[in]		srstatus: SRSTATUS register content
 * @DESCRIPTION		return the current status of sensor error value
 *//*------------------------------------------------------------------------ */
sr_sensor_value_status sr_sensor_error_value_status_get(
	unsigned int srstatus)
{
	if (extract_bit(srstatus, SR_ERRORGENERATORVALID_POS) == 1)
		return SR_SENSOR_VAL_VALID;
	else
		return SR_SENSOR_VAL_INVALID;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_sensor_error_value_get
 * @BRIEF		return RAW sensor error value from SENERROR register
 * @RETURNS		RAW sensor error value from SENERROR register
 * @param[in]		senerror: SENERROR register content
 * @DESCRIPTION		return RAW sensor error value from SENERROR register
 *//*------------------------------------------------------------------------ */
unsigned char sr_sensor_error_value_get(unsigned int senerror)
{
	return (unsigned char) extract_bitfield(senerror,
		SR_SENERROR_POS, SR_SENERROR_LEN);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_sensor_error_percentage_get
 * @BRIEF		return sensor error percentage
 * @RETURNS		percentage of sensor error value
 * @param[in]		senerror: SENERROR register content
 * @DESCRIPTION		return sensor error percentage
 *//*------------------------------------------------------------------------ */
double sr_sensor_error_percentage_get(unsigned int senerror)
{
	return 0.8 * (signed char) sr_sensor_error_value_get(senerror);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_avg_sensor_error_value_status_get
 * @BRIEF		return the current status of avg error value
 * @RETURNS		avg error value (AvgError) status
 * @param[in]		srstatus: SRSTATUS register content
 * @DESCRIPTION		return the current status of avg error value
 *//*------------------------------------------------------------------------ */
sr_sensor_value_status sr_avg_sensor_error_value_status_get(
	unsigned int srstatus)
{
	if (extract_bit(srstatus, SR_AVGERRVALID_POS) == 1)
		return SR_SENSOR_VAL_VALID;
	else
		return SR_SENSOR_VAL_INVALID;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_avg_sensor_error_value_get
 * @BRIEF		return RAW sensor error value from SENERROR register
 * @RETURNS		RAW sensor error value from SENERROR register
 * @param[in]		senerror: SENERROR register content
 * @DESCRIPTION		return RAW sensor error value from SENERROR register
 *//*------------------------------------------------------------------------ */
unsigned char sr_avg_sensor_error_value_get(unsigned int senerror)
{
	return (unsigned char) extract_bitfield(senerror,
		SR_AVGERROR_POS, SR_AVGERROR_LEN);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_avg_sensor_error_percentage_get
 * @BRIEF		return avg sensor error percentage
 * @RETURNS		avg sensor error value
 * @param[in]		senerror: SENERROR register content
 * @DESCRIPTION		return avg sensor error percentage
 *//*------------------------------------------------------------------------ */
double sr_avg_sensor_error_percentage_get(unsigned int senerror)
{
	return 0.8 * (signed char) sr_avg_sensor_error_value_get(senerror);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_sensor_value_status_get
 * @BRIEF		return the current status of selected value type
 *			(invalid/valid/final)
 * @RETURNS		sensor values (min/max/avg/latest) status
 * @param[in]		srstatus: SRSTATUS register content
 * @DESCRIPTION		return the current status of selected value type
 *			(invalid/valid/final)
 *//*------------------------------------------------------------------------ */
sr_sensor_value_status sr_sensor_value_status_get(unsigned int srstatus)
{
	if (extract_bit(srstatus, SR_MINMAXAVGACCUMVALID_POS) == 1)
		return SR_SENSOR_VAL_FINAL;
	else if (extract_bit(srstatus, SR_MINMAXAVGVALID_POS) == 1)
		return SR_SENSOR_VAL_VALID;
	else
		return SR_SENSOR_VAL_INVALID;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_sensor_value_get
 * @BRIEF		return selected SR sensor value
 *			NB: use sr_sensor_value_status_get() first to make sure
 *			value is valid
 * @RETURNS		SR sensor current (latest) value
 * @param[in]		sr_regs: SR registers content
 * @param[in]		sen_type: sensor type
 * @param[in]		val_type: value type
 * @DESCRIPTION		return selected SR sensor value
 *			NB: use sr_sensor_value_status_get() first to make sure
 *			value is valid
 *//*------------------------------------------------------------------------ */
unsigned int sr_sensor_value_get(sr_registers *sr_regs, sr_sensor_type sen_type,
	sr_sensor_value_type val_type)
{
	switch (sen_type) {
	case SR_SENSOR_N:
		switch (val_type) {
		case SR_SENSOR_VAL_LATEST:
			return (unsigned int) extract_bitfield(sr_regs->senval,
				SR_SENNVAL_POS, SR_SENNVAL_LEN);
		case SR_SENSOR_VAL_MIN:
			return (unsigned int) extract_bitfield(sr_regs->senmin,
				SR_SENNMIN_POS, SR_SENNMIN_LEN);
		case SR_SENSOR_VAL_MAX:
			return (unsigned int) extract_bitfield(sr_regs->senmax,
				SR_SENNMAX_POS, SR_SENNMAX_LEN);
		case SR_SENSOR_VAL_AVG:
			return (unsigned int) extract_bitfield(sr_regs->senavg,
				SR_SENNAVG_POS, SR_SENNAVG_LEN);
		default:
			fprintf(stderr, "%s(): incorrect value type! (%u)\n",
				__func__, val_type);
			return 0;
		}

	case SR_SENSOR_P:
		switch (val_type) {
		case SR_SENSOR_VAL_LATEST:
			return (unsigned int) extract_bitfield(sr_regs->senval,
				SR_SENPVAL_POS, SR_SENPVAL_LEN);
		case SR_SENSOR_VAL_MIN:
			return (unsigned int) extract_bitfield(sr_regs->senmin,
				SR_SENPMIN_POS, SR_SENPMIN_LEN);
		case SR_SENSOR_VAL_MAX:
			return (unsigned int) extract_bitfield(sr_regs->senmax,
				SR_SENPMAX_POS, SR_SENPMAX_LEN);
		case SR_SENSOR_VAL_AVG:
			return (unsigned int) extract_bitfield(sr_regs->senavg,
				SR_SENPAVG_POS, SR_SENPAVG_LEN);
		default:
			fprintf(stderr, "%s(): incorrect value type! (%u)\n",
				__func__, val_type);
			return 0;
		}

	default:
		fprintf(stderr, "%s(): incorrect sensor type! (%u)\n", __func__,
			sen_type);
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_delta_vdd_get
 * @BRIEF		return the delta Vdd error in mV
 * @RETURNS		SR delta Vdd error in mV
 * @param[in]		freq_error: avegare sensor error (%)
 * @param[in]		vp_offset: programmed VP error offset (%)
 * @param[in]		vp_gain: programmed VP error gain (mV/%)
 * @DESCRIPTION		return the delta Vdd error in mV
 *//*------------------------------------------------------------------------ */
double sr_delta_vdd_get(double freq_error, double vp_offset, double vp_gain)
{
	return (freq_error + vp_offset) * vp_gain;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_lvt_sensor_value_get
 * @BRIEF		return selected SR sensor value
 *			NB: use sr_sensor_value_status_get() first to make sure
 *			value is valid
 * @RETURNS		SR sensor current (latest) value
 * @param[in]		sr_regs: SR registers content
 * @param[in]		sen_type: sensor type
 * @param[in]		val_type: value type
 * @DESCRIPTION		return selected SR sensor value
 *			NB: use sr_sensor_value_status_get() first to make sure
 *			value is valid
 *//*------------------------------------------------------------------------ */
unsigned int sr_lvt_sensor_value_get(sr_registers *sr_regs,
	sr_sensor_type sen_type, sr_sensor_value_type val_type)
{
	switch (sen_type) {
	case SR_SENSOR_N:
		switch (val_type) {
		case SR_SENSOR_VAL_LATEST:
			return (unsigned int) extract_bitfield(
					sr_regs->lvtsenval,
				SR_SENNVAL_POS, SR_SENNVAL_LEN);
		case SR_SENSOR_VAL_MIN:
			return (unsigned int) extract_bitfield(
					sr_regs->lvtsenmin,
				SR_SENNMIN_POS, SR_SENNMIN_LEN);
		case SR_SENSOR_VAL_MAX:
			return (unsigned int) extract_bitfield(
					sr_regs->lvtsenmax,
				SR_SENNMAX_POS, SR_SENNMAX_LEN);
		case SR_SENSOR_VAL_AVG:
			return (unsigned int) extract_bitfield(
					sr_regs->lvtsenavg,
				SR_SENNAVG_POS, SR_SENNAVG_LEN);
		default:
			fprintf(stderr, "%s(): incorrect value type! (%u)\n",
				__func__, val_type);
			return 0;
		}

	case SR_SENSOR_P:
		switch (val_type) {
		case SR_SENSOR_VAL_LATEST:
			return (unsigned int) extract_bitfield(
					sr_regs->lvtsenval,
				SR_SENPVAL_POS, SR_SENPVAL_LEN);
		case SR_SENSOR_VAL_MIN:
			return (unsigned int) extract_bitfield(
					sr_regs->lvtsenmin,
				SR_SENPMIN_POS, SR_SENPMIN_LEN);
		case SR_SENSOR_VAL_MAX:
			return (unsigned int) extract_bitfield(
					sr_regs->lvtsenmax,
				SR_SENPMAX_POS, SR_SENPMAX_LEN);
		case SR_SENSOR_VAL_AVG:
			return (unsigned int) extract_bitfield(
					sr_regs->lvtsenavg,
				SR_SENPAVG_POS, SR_SENPAVG_LEN);
		default:
			fprintf(stderr, "%s(): incorrect value type! (%u)\n",
				__func__, val_type);
			return 0;
		}

	default:
		fprintf(stderr, "%s(): incorrect sensor type! (%u)\n", __func__,
			sen_type);
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_config_show
 * @BRIEF		analyze Smart-Reflex sensor configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		stream: output file (NULL: no output (silent))
 * @param[in]		sr_regs: SR registers content for the 3 SR instances
 *			(MPU, IVA/MM, CORE)
 * @DESCRIPTION		analyze Smart-Reflex sensor configuration
 *//*------------------------------------------------------------------------ */
int sr_config_show(FILE *stream, sr_registers sr_regs[3])
{
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int i, val, val2, row, maxrow;
	sr_sensor_value_status status;
	sr_sensor_value_type val_type;
	sr_interrupt_type irq_type;
	opp44xx_id vdd_core_opp;
	double sys_clk, sr_sysclk;
	static const char irq_status_table[2][10] = {
		"Unchanged",
		"Set"};
	static const char mode_table[2][16] = {
		"Disabled      ",
		"Enabled       "};
	char *s1, *s2;
	unsigned char mode, mode2;

	if (!cpu_is_omap44xx() & !cpu_is_omap54xx()) {
		fprintf(stderr, "%s(): cpu not supported!!!\n", __func__);
		return OMAPCONF_ERR_CPU;
	}

	#ifdef SR_DEBUG
	row = 0;
	maxrow = 0;
	autoadjust_table_init(table);
	autoadjust_table_strncpy(table, row, 0, "SR Registers");
	autoadjust_table_strncpy(table, row, 1, "SR MPU");
	if (cpu_is_omap44xx())
		autoadjust_table_strncpy(table, row, 2, "SR IVA");
	else
		autoadjust_table_strncpy(table, row, 2, "SR MM");
	autoadjust_table_strncpy(table, row, 3, "SR CORE");
	row++;
	for (i = 0; i < 3; i++) {
		if (row > maxrow)
			maxrow = row;
		row = 1;
		autoadjust_table_strncpy(table, row, 0, "ACCESSIBLE");
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN, "0x%08X",
				sr_regs[i].accessible);
		if (sr_regs[i].accessible == 0)
			continue;
		row++;
		autoadjust_table_strncpy(table, row, 0, "SRCONFIG");
		snprintf(table[row++][i + 1], TABLE_MAX_ELT_LEN, "0x%08X",
			sr_regs[i].srconfig);
		autoadjust_table_strncpy(table, row, 0, "SRSTATUS");
		snprintf(table[row++][i + 1], TABLE_MAX_ELT_LEN, "0x%08X",
			sr_regs[i].srstatus);
		autoadjust_table_strncpy(table, row, 0, "SENVAL");
		snprintf(table[row++][i + 1], TABLE_MAX_ELT_LEN, "0x%08X",
			sr_regs[i].senval);
		autoadjust_table_strncpy(table, row, 0, "SENMIN");
		snprintf(table[row++][i + 1], TABLE_MAX_ELT_LEN, "0x%08X",
			sr_regs[i].senmin);
		autoadjust_table_strncpy(table, row, 0, "SENMAX");
		snprintf(table[row++][i + 1], TABLE_MAX_ELT_LEN, "0x%08X",
			sr_regs[i].senmax);
		autoadjust_table_strncpy(table, row, 0, "SENAVG");
		snprintf(table[row++][i + 1], TABLE_MAX_ELT_LEN, "0x%08X",
			sr_regs[i].senavg);
		autoadjust_table_strncpy(table, row, 0, "AVGWEIGHT");
		snprintf(table[row++][i + 1], TABLE_MAX_ELT_LEN, "0x%08X",
			sr_regs[i].avgweight);
		autoadjust_table_strncpy(table, row, 0, "NVALUERECIPROCAL");
		snprintf(table[row++][i + 1], TABLE_MAX_ELT_LEN, "0x%08X",
			sr_regs[i].nvaluereciprocal);
		autoadjust_table_strncpy(table, row, 0, "IRQSTATUS_RAW");
		snprintf(table[row++][i + 1], TABLE_MAX_ELT_LEN, "0x%08X",
			sr_regs[i].irqstatus_raw);
		autoadjust_table_strncpy(table, row, 0, "IRQSTATUS");
		snprintf(table[row++][i + 1], TABLE_MAX_ELT_LEN, "0x%08X",
			sr_regs[i].irqstatus);
		autoadjust_table_strncpy(table, row, 0, "IRQENABLE_SET");
		snprintf(table[row++][i + 1], TABLE_MAX_ELT_LEN, "0x%08X",
			sr_regs[i].irqenable_set);
		autoadjust_table_strncpy(table, row, 0, "SENERROR");
		snprintf(table[row++][i + 1], TABLE_MAX_ELT_LEN, "0x%08X",
			sr_regs[i].senerror);
		autoadjust_table_strncpy(table, row, 0, "ERRCONFIG");
		snprintf(table[row++][i + 1], TABLE_MAX_ELT_LEN, "0x%08X",
			sr_regs[i].errconfig);

		if (cpu_is_omap44xx())
			continue;
		autoadjust_table_strncpy(table, row, 0, "LVTSENVAL");
		snprintf(table[row++][i + 1], TABLE_MAX_ELT_LEN, "0x%08X",
			sr_regs[i].lvtsenval);
		autoadjust_table_strncpy(table, row, 0, "LVTSENMIN");
		snprintf(table[row++][i + 1], TABLE_MAX_ELT_LEN, "0x%08X",
			sr_regs[i].lvtsenmin);
		autoadjust_table_strncpy(table, row, 0, "LVTSENMAX");
		snprintf(table[row++][i + 1], TABLE_MAX_ELT_LEN, "0x%08X",
			sr_regs[i].lvtsenmax);
		autoadjust_table_strncpy(table, row, 0, "LVTSENAVG");
		snprintf(table[row++][i + 1], TABLE_MAX_ELT_LEN, "0x%08X",
			sr_regs[i].lvtsenavg);
		autoadjust_table_strncpy(table, row, 0, "LVTNVALUERECIPROCAL");
		snprintf(table[row++][i + 1], TABLE_MAX_ELT_LEN, "0x%08X",
			sr_regs[i].lvtnvaluereciprocal);
	}
	autoadjust_table_print(table, maxrow, 4);
	#endif

	if (cpu_is_omap44xx()) {
		sys_clk = clk44xx_get_system_clock_speed();
		/* Get VDD_CORE OPP to detect DPLL cascading mode */
		voltdm44xx_get_opp(OMAP4_VDD_CORE, &vdd_core_opp);
		if (vdd_core_opp == OMAP4_OPPDPLL_CASC)
			sr_sysclk = 12.288; /* MHz */
		else
			sr_sysclk = sys_clk;
	} else {
		sr_sysclk =
			(double) module_clk_rate_get(MOD_SMARTREFLEX_MPU, 0) / 1000.0;
	}
	dprintf("%s(): sr_sysclk = %lfMHz\n", __func__, sr_sysclk);

	row = 0;
	maxrow = 0;
	autoadjust_table_init(table);
	autoadjust_table_strncpy(table, row, 0, "SR Configuration");
	autoadjust_table_strncpy(table, row, 1, "SR_MPU");
	if (cpu_is_omap44xx())
		autoadjust_table_strncpy(table, row, 2, "SR_MM");
	else
		autoadjust_table_strncpy(table, row, 2, "SR_MM");
	autoadjust_table_strncpy(table, row, 3, "SR_CORE");
	row++;

	for (i = 0; i < 3; i++) {
		if (row > maxrow)
			maxrow = row;
		row = 1;
		autoadjust_table_strncpy(table, row, 0, "SR Module");
		if (sr_regs[i].accessible == 0) {
			autoadjust_table_strncpy(table, row, i + 1, "Disabled");
			row++;
			continue;
		}
		mode = sr_is_enabled(sr_regs[i].srconfig);
		autoadjust_table_strncpy(table, row, i + 1,
			(char *) mode_table[mode]);
		row++;
		autoadjust_table_strncpy(table, row, 0,
			"SR_CLK Divider (SRCLKLENGTH)");
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN, "0x%03X (%u)",
			sr_clk_div_get(sr_regs[i].srconfig),
			sr_clk_div_get(sr_regs[i].srconfig));
		row++;
		autoadjust_table_strncpy(table, row, 0,
			"SR_CLK Frequency");
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN, "%.3lfKHz",
			sr_clk_rate_get(sr_regs[i].srconfig, sr_sysclk));
		row += 2;

		autoadjust_table_strncpy(table, row++, 0,
			"Interrupt configuration");
		for (irq_type = SR_IRQ_MCUDISABLEACK;
			irq_type < SR_IRQ_TYPE_MAX; irq_type++) {
			snprintf(table[row][0], TABLE_MAX_ELT_LEN, "  %s",
				sr_interrupt_type_name_get(irq_type));
			mode = sr_irq_is_enabled(sr_regs[i].irqenable_set,
				sr_regs[i].errconfig, irq_type);
			autoadjust_table_strncpy(table, row++, i + 1,
					(char *) mode_table[mode]);
			if (mode == 0)
				continue;
			snprintf(table[row][0], TABLE_MAX_ELT_LEN,
				"    Status (Masked | Raw)");
			val = sr_irq_status_is_set(sr_regs[i].irqstatus,
				sr_regs[i].errconfig, irq_type);
			s1 = (char *) irq_status_table[val];
			if (irq_type != SR_IRQ_VPBOUNDS) {
				val2 = sr_irq_raw_status_is_set(
					sr_regs[i].irqstatus_raw, irq_type);
				s2 = (char *) irq_status_table[val2];
				snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN,
					"%s | %s", s1, s2);
			} else {
				snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN,
					"%s", s1);
			}
			row++;
		}
		row++;

		autoadjust_table_strncpy(table, row, 0,
			"SR Sensors (N | P)");
		if (sr_is_sensors_disabled(sr_regs[i].srconfig) == 1) {
			autoadjust_table_strncpy(table, row, i + 1, "Disabled");
			row += 2;
			goto sr_config_show_minmaxavg;
		}
		mode = sr_is_sensor_enabled(sr_regs[i].srconfig, SR_SENSOR_N);
		mode2 = sr_is_sensor_enabled(sr_regs[i].srconfig, SR_SENSOR_P);
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN, "%s | %s",
			mode_table[mode], mode_table[mode2]);
		row++;

		autoadjust_table_strncpy(table, row, 0,
			"  Reciprocal Gain (SEN[N-P]GAIN)");
		val = sr_gain_get(sr_regs[i].nvaluereciprocal, SR_SENSOR_N);
		val2 = sr_gain_get(sr_regs[i].nvaluereciprocal, SR_SENSOR_P);
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN,
			"0x%04X (%05u) | 0x%04X (%05u)", val, val, val2, val2);
		row++;

		autoadjust_table_strncpy(table, row, 0,
			"  Reciprocal Scale Value (SEN[N-P]RN)");
		val = sr_scale_value_get(sr_regs[i].nvaluereciprocal,
			SR_SENSOR_N);
		val2 = sr_scale_value_get(sr_regs[i].nvaluereciprocal,
			SR_SENSOR_P);
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN,
			"0x%04X (%05u) | 0x%04X (%05u)", val, val, val2, val2);
		row++;

		autoadjust_table_strncpy(table, row, 0, "  NTarget");
		val = sr_ntarget_get(sr_regs[i].nvaluereciprocal, SR_SENSOR_N);
		val2 = sr_ntarget_get(sr_regs[i].nvaluereciprocal, SR_SENSOR_P);
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN,
			"0x%04X (%05u) | 0x%04X (%05u)", val, val, val2, val2);
		row++;
		if (cpu_is_omap44xx()) {
			row++;
			goto sr_config_show_minmaxavg;
		}

		autoadjust_table_strncpy(table, row, 0,
			"SR LVT Sensors (N | P)");
		if (sr_is_lvt_sensors_disabled(sr_regs[i].srconfig) == 1) {
			autoadjust_table_strncpy(table, row, i + 1, "Disabled");
			row += 5;
			goto sr_config_show_minmaxavg;
		}
		mode = sr_is_lvt_sensor_enabled(sr_regs[i].srconfig,
			SR_SENSOR_N);
		mode2 = sr_is_lvt_sensor_enabled(sr_regs[i].srconfig,
			SR_SENSOR_P);
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN, "%s | %s",
			mode_table[mode], mode_table[mode2]);
		row++;

		autoadjust_table_strncpy(table, row, 0,
			"  Reciprocal Gain (SEN[N-P]GAIN)");
		val = sr_gain_get(sr_regs[i].lvtnvaluereciprocal, SR_SENSOR_N);
		val2 = sr_gain_get(sr_regs[i].lvtnvaluereciprocal, SR_SENSOR_P);
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN,
			"0x%04X (%05u) | 0x%04X (%05u)", val, val, val2, val2);
		row++;

		autoadjust_table_strncpy(table, row, 0,
			"  Reciprocal Scale Value (SEN[N-P]RN)");
		val = sr_scale_value_get(sr_regs[i].lvtnvaluereciprocal,
			SR_SENSOR_N);
		val2 = sr_scale_value_get(sr_regs[i].lvtnvaluereciprocal,
			SR_SENSOR_P);
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN,
			"0x%04X (%05u) | 0x%04X (%05u)", val, val, val2, val2);
		row++;

		autoadjust_table_strncpy(table, row, 0, "  NTarget");
		val = sr_ntarget_get(sr_regs[i].lvtnvaluereciprocal,
			SR_SENSOR_N);
		val2 = sr_ntarget_get(sr_regs[i].lvtnvaluereciprocal,
			SR_SENSOR_P);
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN,
			"0x%04X (%05u) | 0x%04X (%05u)", val, val, val2, val2);
		row += 2;

sr_config_show_minmaxavg:
		autoadjust_table_strncpy(table, row, 0,
			"Min/Max/Avg Detector Module");
		mode = sr_is_minmaxavg_detector_enabled(sr_regs[i].srconfig);
		autoadjust_table_strncpy(table, row, i + 1,
			(char *) mode_table[mode]);
		row++;
		if (mode == 0) {
			row++;
			goto sr_config_show_errgen;
		}
		autoadjust_table_strncpy(table, row, 0,
			"  Nbr of Accumulated Values (ACCUMDATA)");
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN, "0x%04X (%05u)",
			sr_accumdata_count_get(sr_regs[i].srconfig),
			sr_accumdata_count_get(sr_regs[i].srconfig));
		row++;

		autoadjust_table_strncpy(table, row, 0,
			"  Averager Weighting Factor (N | P)");
		val = sr_avg_weighting_factor_get(sr_regs[i].avgweight,
			SR_SENSOR_N);
		val2 = sr_avg_weighting_factor_get(sr_regs[i].avgweight,
			SR_SENSOR_P);
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN,
			"0x%04X (%05u) | 0x%04X (%05u)",
			val, val, val2, val2);
		row++;
		autoadjust_table_strncpy(table, row++, 0,
			"  Sensor Values (N | P)");
		for (val_type = SR_SENSOR_VAL_LATEST;
			val_type < SR_SENSOR_VAL_TYPE_MAX; val_type++) {
			snprintf(table[row][0], TABLE_MAX_ELT_LEN, "    %s",
				sr_sensor_value_type_name_get(val_type));
			status = sr_sensor_value_status_get(
				sr_regs[i].srstatus);
			if (status == SR_SENSOR_VAL_INVALID) {
				snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN,
					"%s", sr_sensor_value_status_name_get(
						status));
			} else {
				val = sr_sensor_value_get(&(sr_regs[i]),
					SR_SENSOR_N, val_type);
				val2 = sr_sensor_value_get(&(sr_regs[i]),
					SR_SENSOR_P, val_type);
				snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN,
					"0x%04X (%05u) | 0x%04X (%05u)",
					val, val, val2, val2);
			}
			row++;
		}

		if (cpu_is_omap44xx()) {
			row++;
			goto sr_config_show_errgen;
		}
		autoadjust_table_strncpy(table, row++, 0,
			"  LVT Sensor Values (N | P)");
		for (val_type = SR_SENSOR_VAL_LATEST;
			val_type < SR_SENSOR_VAL_TYPE_MAX; val_type++) {
			snprintf(table[row][0], TABLE_MAX_ELT_LEN, "    %s",
				sr_sensor_value_type_name_get(val_type));
			status = sr_sensor_value_status_get(
				sr_regs[i].srstatus);
			if (status == SR_SENSOR_VAL_INVALID) {
				snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN,
					"%s", sr_sensor_value_status_name_get(
						status));
			} else {
				val = sr_lvt_sensor_value_get(&(sr_regs[i]),
					SR_SENSOR_N, val_type);
				val2 = sr_lvt_sensor_value_get(&(sr_regs[i]),
					SR_SENSOR_P, val_type);
				snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN,
					"0x%04X (%05u) | 0x%04X (%05u)",
					val, val, val2, val2);
			}
			row++;
		}
		row++;

sr_config_show_errgen:
		autoadjust_table_strncpy(table, row, 0,
			"Error Generator Module");
		mode = sr_is_error_generator_enabled(sr_regs[i].srconfig);
		autoadjust_table_strncpy(table, row, i + 1,
			(char *) mode_table[mode]);
		row++;
		autoadjust_table_strncpy(table, row, 0,
			"  Idle Mode");
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN, "%s",
			mod_idle_mode_name_get(sr_error_generator_idle_mode_get(
				sr_regs[i].errconfig)));
		row++;
		autoadjust_table_strncpy(table, row, 0,
			"  WAKEUPENABLE");
		val = sr_is_error_generator_wakeup_enabled(
			sr_regs[i].errconfig);
		autoadjust_table_strncpy(table, row, i + 1,
			(char *) mode_table[mode]);
		row++;

		autoadjust_table_strncpy(table, row, 0,
			"  ERRMINLIMIT");
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN,
			"%.1lf%% (0x%02X)",
			sr_error_generator_minlimit_percentage_get(
				sr_regs[i].errconfig),
			sr_error_generator_minlimit_get(sr_regs[i].errconfig));
		row++;
		autoadjust_table_strncpy(table, row, 0,
			"  ERRMAXLIMIT");
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN,
			"%.1lf%% (0x%02X)",
			sr_error_generator_maxlimit_percentage_get(
				sr_regs[i].errconfig),
			sr_error_generator_maxlimit_get(sr_regs[i].errconfig));
		row++;
		autoadjust_table_strncpy(table, row, 0,
			"  ERRWEIGHT");
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN, "0x%1X (%u)",
			sr_error_generator_weight_get(sr_regs[i].errconfig),
			sr_error_generator_weight_get(sr_regs[i].errconfig));
		row += 2;

		autoadjust_table_strncpy(table, row++, 0,
			"Sensor Error");
		autoadjust_table_strncpy(table, row, 0,
			"  Latest");
		status = sr_sensor_error_value_status_get(sr_regs[i].srstatus);
		snprintf(table[row++][i + 1], TABLE_MAX_ELT_LEN,
			"%.1lf%% (0x%02X) (%s)",
			sr_sensor_error_percentage_get(sr_regs[i].senerror),
			sr_sensor_error_value_get(sr_regs[i].senerror),
			sr_sensor_value_status_name_get(status));
		autoadjust_table_strncpy(table, row, 0,
			"  Average");
		status = sr_avg_sensor_error_value_status_get(
			sr_regs[i].srstatus);
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN,
			"%.1lf%% (0x%02X) (%s)",
			sr_avg_sensor_error_percentage_get(sr_regs[i].senerror),
			sr_avg_sensor_error_value_get(sr_regs[i].senerror),
			sr_sensor_value_status_name_get(status));
		row++;
	}

	if (stream != NULL)
		autoadjust_table_fprint(stream, table, maxrow, 4);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_convergence_status_show
 * @BRIEF		analyze Smart-Reflex convergence status
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		stream: output file (NULL: no output (silent))
 * @param[in]		sr_regs: SR registers content for the 3 SR instances
 *			(MPU, IVA/MM, CORE)
 * @DESCRIPTION		analyze Smart-Reflex convergence status
 *//*------------------------------------------------------------------------ */
int sr_convergence_status_show(FILE *stream, sr_status_registers sr_regs[3])
{
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	int v, row, maxrow;
	double volt, freq_error, delta_vdd, vp_offset, vp_gain;
	signed char vp_offset_raw, vp_gain_raw;
	static const char mode_table[2][16] = {
		"Disabled      ",
		"Enabled       "};
	unsigned char mode;
	const char *opp;
	char s_opp[16];
	int voltdm_count;
	const genlist *voltdm_list;
	voltdm_info voltdm;

	if (!cpu_is_omap44xx() & !cpu_is_omap54xx()) {
		fprintf(stderr, "%s(): cpu not supported!!!\n", __func__);
		return OMAPCONF_ERR_CPU;
	}

	row = 0;
	maxrow = 0;
	autoadjust_table_init(table);
	autoadjust_table_strncpy(table, row, 0, "SR Convergence Status");
	autoadjust_table_strncpy(table, row, 1, "SR MPU");
	if (cpu_is_omap44xx())
		autoadjust_table_strncpy(table, row, 2, "SR IVA");
	else
		autoadjust_table_strncpy(table, row, 2, "SR MM");
	autoadjust_table_strncpy(table, row, 3, "SR CORE");
	row++;


	/* Retrieve voltage domain list and count */
	voltdm_list = voltdm_list_get();
	if (voltdm_list == NULL) {
		fprintf(stderr,
			"omapconf: %s(): failed to retrieve VDD List!\n",
			__func__);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	voltdm_count = voltdm_count_get();
	if (voltdm_count <= 0) {
		fprintf(stderr,
			"omapconf: %s(): failed to retrieve VDD count!\n",
			__func__);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	/* Browse voltage domains, skipping WKUP */
	for (v = 0; v < voltdm_count - 1; v++) {
		/* Get voltage domain details */
		genlist_get((genlist *) voltdm_list, v + 1, (void *) &voltdm);

		/* Save max number of row */
		if (row > maxrow)
			maxrow = row;
		row = 1;

		/* Show module status */
		autoadjust_table_strncpy(table, row, 0, "SR Module");
		if (sr_regs[v].enabled == 0) {
			autoadjust_table_strncpy(table, row, v + 1, "Disabled");
			row++;
			continue;
		}
		mode = sr_is_enabled(sr_regs[v].srconfig);
		autoadjust_table_strncpy(table, row, v + 1,
			(char *) mode_table[mode]);
		row++;

		/* Show OPP */
		autoadjust_table_strncpy(table, row, 0, "OPP");
		opp = opp_get(voltdm.name, 1);
		if (opp != NULL)
			strncpy(s_opp, opp, OPP_MAX_NAME_LENGTH);
		else
			strncpy(s_opp, "NOT FOUND", OPP_MAX_NAME_LENGTH);
		autoadjust_table_strncpy(table, row, v + 1, s_opp);
		row++;

		/* Show convergence status */
		autoadjust_table_strncpy(table, row, 0, "Converged?");
		if (sr_has_converged(
			sr_regs[v].errconfig, sr_regs[v].senerror) == 1)
			autoadjust_table_strncpy(table, row, v + 1, "YES");
		else
			autoadjust_table_strncpy(table, row, v + 1, "NO");
		row++;

		/* Show voltage error */
		autoadjust_table_strncpy(table, row, 0,
			"Voltage Error (%, mV)");
		freq_error = sr_avg_sensor_error_percentage_get(
			sr_regs[v].senerror);
		vp_error_offset_get(sr_regs[v].vp_config,
			&vp_offset_raw, &vp_offset);
		vp_error_gain_get(sr_regs[v].vp_config, v + 1,
			&vp_gain_raw, &vp_gain);
		delta_vdd = sr_delta_vdd_get(freq_error, vp_offset, vp_gain);
		snprintf(table[row][v + 1], TABLE_MAX_ELT_LEN,
			"%.1lf%% (%.3lfmV)", freq_error, delta_vdd);
		row++;

		/* Show converged voltage */
		autoadjust_table_strncpy(table, row, 0,
			"Converged Voltage (V)");
		volt = (double) voltdm_voltage_get(voltdm.name) / 1000000.0;
		if (volt >= 0)
			snprintf(table[row][v + 1], TABLE_MAX_ELT_LEN,
				"%.6lfV", volt);
		else
			snprintf(table[row][v + 1], TABLE_MAX_ELT_LEN,
				"NA");
		row++;
	}

	if (stream != NULL)
		autoadjust_table_fprint(stream, table, maxrow, 4);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr_config_audit
 * @BRIEF		audit SR settings
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output file (NULL: no output (silent))
 * @param[in]		sr_name: SR module name
 * @param[in]		opp_name: OPP name
 * @param[in]		sr_regs: SR registers content
 * @param[in]		sr_golden_settings: expected ("golden") SR settings
 * @param[in,out]	err_nbr: error number
 * @param[in,out]	wng_nbr: warning number
 * @DESCRIPTION		audit SR settings, by comparing current settings with
 *			predefined "golden" settings.
 *//*------------------------------------------------------------------------ */
int sr_config_audit(FILE *stream, const char *sr_name, const char *opp_name,
	sr_registers *sr_regs, const sr_audit_settings *sr_golden_settings,
	unsigned int *err_nbr, unsigned int *wng_nbr)
{
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row;
	double sys_clk, sr_sysclk;
	opp44xx_id vdd_core_opp;
	sr_interrupt_type irqtype;
	mod_idle_mode idle_mode_curr, idle_mode_expected;
	static const char mode_table[2][16] = {
		"Disabled      ",
		"Enabled       "};
	unsigned char curr, expected;

	if (!cpu_is_omap44xx() /* & !cpu_is_omap54xx() FIXME */) {
		fprintf(stderr, "%s(): cpu not supported!!!\n", __func__);
		return OMAPCONF_ERR_CPU;
	}
	CHECK_NULL_ARG(sr_name, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(sr_regs, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(sr_golden_settings, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(err_nbr, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(wng_nbr, OMAPCONF_ERR_ARG);

	*err_nbr = 0;
	*wng_nbr = 0;

	if (cpu_is_omap44xx()) {
		sys_clk = clk44xx_get_system_clock_speed();
		/* Get VDD_CORE OPP to detect DPLL cascading mode */
		voltdm44xx_get_opp(OMAP4_VDD_CORE, &vdd_core_opp);
		if (vdd_core_opp == OMAP4_OPPDPLL_CASC)
			sr_sysclk = 12.288; /* MHz */
		else
			sr_sysclk = sys_clk;
	} else {
		sr_sysclk =
			(double) module_clk_rate_get(MOD_SMARTREFLEX_MPU, 0) / 1000.0;
	}
	dprintf("%s(): sr_sysclk = %lfMHz\n", __func__, sr_sysclk);

	if (sr_regs->accessible == 0) {
		if (stream != NULL)
			fprintf(stream, "%s is disabled, audit cannot be "
			"completed.\n\n", sr_name);
		return 0;
	}
	row = 0;
	autoadjust_table_init(table);
	snprintf(table[row][0], TABLE_MAX_ELT_LEN,
		"%s AVS Configuration AUDIT (@%s)", sr_name, opp_name);

	autoadjust_table_strncpy(table, row, 1, "Current");
	autoadjust_table_strncpy(table, row, 2, "Expected");
	autoadjust_table_strncpy(table, row, 3, "STATUS");
	row++;

	autoadjust_table_strncpy(table, row, 0,
		"SR_CLK Frequency");
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%.3lfKHz",
		sr_clk_rate_get(sr_regs->srconfig, sr_sysclk));
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%.3lfKHz",
		sr_golden_settings->sr_sysclk);
	SR_AUDIT_SHOW_STATUS(
		(unsigned int) sr_clk_rate_get(sr_regs->srconfig, sr_sysclk),
		(unsigned int) sr_golden_settings->sr_sysclk);

	autoadjust_table_strncpy(table, row++, 0,
		"Interrupt configuration");
	for (irqtype = SR_IRQ_MCUDISABLEACK; irqtype < SR_IRQ_TYPE_MAX;
		irqtype++) {
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "  %s",
			sr_interrupt_type_name_get(irqtype));
		curr = sr_irq_is_enabled(
			sr_regs->irqenable_set,
			sr_regs->errconfig, irqtype);
		autoadjust_table_strncpy(table, row, 1,
				(char *) mode_table[curr]);
		expected = sr_golden_settings->irqmode[irqtype];
		autoadjust_table_strncpy(table, row, 2,
				(char *) mode_table[expected]);
		SR_AUDIT_SHOW_STATUS(curr, expected);
	}

	autoadjust_table_strncpy(table, row, 0,
		"SR Sensor N");
	curr = sr_is_sensor_enabled(sr_regs->srconfig, SR_SENSOR_N);
	expected = sr_golden_settings->sensornmode;
	autoadjust_table_strncpy(table, row, 1,
		(char *) mode_table[curr]);
	autoadjust_table_strncpy(table, row, 2,
		(char *) mode_table[expected]);
	SR_AUDIT_SHOW_STATUS(curr, expected);


	autoadjust_table_strncpy(table, row, 0,
		"SR Sensor P");
	curr = sr_is_sensor_enabled(sr_regs->srconfig, SR_SENSOR_P);
	expected = sr_golden_settings->sensorpmode;
	autoadjust_table_strncpy(table, row, 1,
		(char *) mode_table[curr]);
	autoadjust_table_strncpy(table, row, 2,
		(char *) mode_table[expected]);
	SR_AUDIT_SHOW_STATUS(curr, expected);

	autoadjust_table_strncpy(table, row, 0,
		"Min/Max/Avg Detector Module");
	curr = sr_is_minmaxavg_detector_enabled(sr_regs->srconfig);
	expected = sr_golden_settings->minmaxavg_detector_mode;
	autoadjust_table_strncpy(table, row, 1,
		(char *) mode_table[curr]);
	autoadjust_table_strncpy(table, row, 2,
		(char *) mode_table[expected]);
	SR_AUDIT_SHOW_STATUS(curr, expected);

	autoadjust_table_strncpy(table, row, 0,
		"Error Generator Module");
	curr = sr_is_error_generator_enabled(sr_regs->srconfig);
	expected = sr_golden_settings->errgen_mode;
	autoadjust_table_strncpy(table, row, 1,
		(char *) mode_table[curr]);
	autoadjust_table_strncpy(table, row, 2,
		(char *) mode_table[expected]);
	SR_AUDIT_SHOW_STATUS(curr, expected);

	autoadjust_table_strncpy(table, row, 0, "  Idle Mode");
	idle_mode_curr =
		sr_error_generator_idle_mode_get(sr_regs->errconfig);
	idle_mode_expected = sr_golden_settings->idle_mode;
	autoadjust_table_strncpy(table, row, 1,
		(char *) mod_idle_mode_name_get(idle_mode_curr));
	autoadjust_table_strncpy(table, row, 2,
		(char *) mod_idle_mode_name_get(idle_mode_expected));
	SR_AUDIT_SHOW_STATUS(idle_mode_curr, idle_mode_expected);

	autoadjust_table_strncpy(table, row, 0, "  WAKEUPENABLE");
	curr = sr_is_error_generator_wakeup_enabled(
		sr_regs->errconfig);
	expected = sr_golden_settings->wakeupenable;
	autoadjust_table_strncpy(table, row, 1,
		(char *) mode_table[curr]);
	autoadjust_table_strncpy(table, row, 2,
		(char *) mode_table[expected]);
	SR_AUDIT_SHOW_STATUS(curr, expected);

	autoadjust_table_strncpy(table, row, 0, "  ERRMINLIMIT");
	curr = sr_error_generator_minlimit_get(sr_regs->errconfig);
	expected = sr_golden_settings->errminlimit;
	snprintf(table[row][1], TABLE_MAX_ELT_LEN,
		"0x%02X (%.1lf%%)", curr,
		sr_error_generator_limit_hex2percent((signed char) curr));
	snprintf(table[row][2], TABLE_MAX_ELT_LEN,
		"0x%02X (%.1lf%%)", expected,
		sr_error_generator_limit_hex2percent((signed char) expected));
	SR_AUDIT_SHOW_STATUS(curr, expected);

	autoadjust_table_strncpy(table, row, 0, "  ERRMAXLIMIT");
	curr = sr_error_generator_maxlimit_get(sr_regs->errconfig);
	expected = sr_golden_settings->errmaxlimit;
	snprintf(table[row][1], TABLE_MAX_ELT_LEN,
		"0x%02X (%.1lf%%)", curr,
		sr_error_generator_limit_hex2percent((signed char) curr));
	snprintf(table[row][2], TABLE_MAX_ELT_LEN,
		"0x%02X (%.1lf%%)", expected,
		sr_error_generator_limit_hex2percent((signed char) expected));
	SR_AUDIT_SHOW_STATUS(curr, expected);

	autoadjust_table_strncpy(table, row, 0,
		"  ERRWEIGHT");
	curr = sr_error_generator_weight_get(sr_regs->errconfig);
	expected = sr_golden_settings->errweight;
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "0x%1X (%u)",
		curr, curr);
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "0x%1X (%u)",
		expected, expected);
	SR_AUDIT_SHOW_STATUS(curr, expected);

	autoadjust_table_strncpy(table, row, 0, "Convergence Status");
	curr = sr_has_converged(
		sr_regs->errconfig, sr_regs->senerror);
	expected = sr_golden_settings->converged;
	if (curr == 1)
		autoadjust_table_strncpy(table, row, 1, "Converged");
	else
		autoadjust_table_strncpy(table, row, 1,
			"Not Converged");
	if (expected == 1)
		autoadjust_table_strncpy(table, row, 2, "Converged");
	else
		autoadjust_table_strncpy(table, row, 2,
			"Not Converged");
	SR_AUDIT_SHOW_STATUS(curr, expected);

	if (stream != NULL) {
		autoadjust_table_fprint(stream, table, row, 4);
		fprintf(stream, "NB:\n");
		fprintf(stream, "  - Report 'FAIL' when current setting is "
			"different than golden setting.\n");
		fprintf(stream, "  - Report 'Pass' when current setting "
			"matches golden setting.\n\n");
	}

	return 0;
}
