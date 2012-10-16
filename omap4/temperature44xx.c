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
#include <lib_android.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <autoadjust_table.h>
#include <help.h>
#include <lib.h>
#include <mem.h>
#include <cpuinfo.h>
#include <string.h>
#include <clock44xx.h>
#include <i2c-tools.h>
#include <i2c-dev.h>
#include <emif44xx.h>


#define OMAP4430_CONTROL_TEMP_SENSOR		0x4A00232C

#define OMAP4460_CM_WKUP_BANDGAP_CLKCTRL	0x4A307888
#define OMAP4460_CORE_STD_FUSE_OPP_BGAP		0x4A002260

#define OMAP4460_BANDGAP_CLKON_MASK		(1 << 8)

#define OMAP4460_BGAP_TEMPSOFF_SHIFT			13
#define OMAP4460_BGAP_TEMPSOFF_MASK			(1 << 13)
#define OMAP4460_BGAP_TEMP_SENSOR_CONTCONV_SHIFT	12
#define OMAP4460_BGAP_TEMP_SENSOR_CONTCONV_MASK		(1 << 12)
#define OMAP4460_BGAP_TEMP_SENSOR_SOC_SHIFT		11
#define OMAP4460_BGAP_TEMP_SENSOR_SOC_MASK		(1 << 11)
#define OMAP4460_BGAP_TEMP_SENSOR_EOCZ_SHIFT		10
#define OMAP4460_BGAP_TEMP_SENSOR_EOCZ_MASK		(1 << 10)
#define OMAP4460_BGAP_TEMP_SENSOR_DTEMP_SHIFT		0
#define OMAP4460_BGAP_TEMP_SENSOR_DTEMP_MASK		(0x3ff << 0)


#define OMAP_ADC_START_VALUE	530
#define OMAP_ADC_END_VALUE	923


#define	TMP102_TEMP_REG			0x00
#define	TMP102_CONF_REG			0x01
#define	TMP102_CONF_SD			0x0100
#define	TMP102_CONF_TM			0x0200
#define	TMP102_CONF_POL			0x0400
#define	TMP102_CONF_F0			0x0800
#define	TMP102_CONF_F1			0x1000
#define	TMP102_CONF_R0			0x2000
#define	TMP102_CONF_R1			0x4000
#define	TMP102_CONF_OS			0x8000
#define	TMP102_CONF_EM			0x0010
#define	TMP102_CONF_AL			0x0020
#define	TMP102_CONF_CR0			0x0040
#define	TMP102_CONF_CR1			0x0080
#define	TMP102_TLOW_REG			0x02
#define	TMP102_THIGH_REG		0x03


/* OMAP4460 PCB Sensor */
#define THERM_R0			47 /* 47 kOhms */
#define THERM_RX			10 /* 10 kOhms */
#define THERM_RY			220 /* 220 kOhms */
#define THERM_BETA			4050 /* from thermistor datasheet */
#define THERM_T0			298150 /* mKelvin (25C + 273.15) */
#define THERM_KELVIN_TO_CELSIUS		273150 /* mKelvin */
#define PCB4460_SENSOR_MAX_ADC_VAL	977


/* #define TEMP44XX_DEBUG */
#ifdef TEMP44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static const int adc_code2celcius_table[93] = {
	-38, -35, -34, -32, -30, -28, -26, -24, -22, -20, -18, -17, -15, -13,
	-12, -10, -8, -6, -5, -3, -1, 0, 2, 3, 5, 6, 8, 10, 12, 13, 15, 17, 19,
	21, 23, 25, 27, 28, 30, 32, 33, 35, 37, 38, 40, 42, 43, 45, 47, 48, 50,
	52, 53, 55, 57, 58, 60, 62, 64, 66, 68, 70, 71, 73, 75, 77, 78, 80, 82,
	83, 85, 87, 88, 90, 92, 93, 95, 97, 98, 100, 102, 103, 105, 107, 109,
	111, 113, 115, 117, 118, 120, 122, 123};

/*
 * Temperature values in milidegrees celsius. ADC code values from 530 to 923
 */
static int OMAP4460_adc_to_temp[] = {
	-40000, -40000, -40000, -40000, -39800, -39400, -39000, -38600, -38200,
	-37800, -37300, -36800, -36400, -36000, -35600, -35200, -34800,
	-34300, -33800, -33400, -33000, -32600, -32200, -31800, -31300,
	-30800, -30400, -30000, -29600, -29200, -28700, -28200, -27800,
	-27400, -27000, -26600, -26200, -25700, -25200, -24800, -24400,
	-24000, -23600, -23200, -22700, -22200, -21800, -21400, -21000,
	-20600, -20200, -19700, -19200, -18800, -18400, -18000, -17600,
	-17200, -16700, -16200, -15800, -15400, -15000, -14600, -14200,
	-13700, -13200, -12800, -12400, -12000, -11600, -11200, -10700,
	-10200, -9800, -9400, -9000, -8600, -8200, -7700, -7200, -6800,
	-6400, -6000, -5600, -5200, -4800, -4300, -3800, -3400, -3000,
	-2600, -2200, -1800, -1300, -800, -400, 0, 400, 800, 1200, 1600,
	2100, 2600, 3000, 3400, 3800, 4200, 4600, 5100, 5600, 6000, 6400,
	6800, 7200, 7600, 8000, 8500, 9000, 9400, 9800, 10200, 10600, 11000,
	11400, 11900, 12400, 12800, 13200, 13600, 14000, 14400, 14800,
	15300, 15800, 16200, 16600, 17000, 17400, 17800, 18200, 18700,
	19200, 19600, 20000, 20400, 20800, 21200, 21600, 22100, 22600,
	23000, 23400, 23800, 24200, 24600, 25000, 25400, 25900, 26400,
	26800, 27200, 27600, 28000, 28400, 28800, 29300, 29800, 30200,
	30600, 31000, 31400, 31800, 32200, 32600, 33100, 33600, 34000,
	34400, 34800, 35200, 35600, 36000, 36400, 36800, 37300, 37800,
	38200, 38600, 39000, 39400, 39800, 40200, 40600, 41100, 41600,
	42000, 42400, 42800, 43200, 43600, 44000, 44400, 44800, 45300,
	45800, 46200, 46600, 47000, 47400, 47800, 48200, 48600, 49000,
	49500, 50000, 50400, 50800, 51200, 51600, 52000, 52400, 52800,
	53200, 53700, 54200, 54600, 55000, 55400, 55800, 56200, 56600,
	57000, 57400, 57800, 58200, 58700, 59200, 59600, 60000, 60400,
	60800, 61200, 61600, 62000, 62400, 62800, 63300, 63800, 64200,
	64600, 65000, 65400, 65800, 66200, 66600, 67000, 67400, 67800,
	68200, 68700, 69200, 69600, 70000, 70400, 70800, 71200, 71600,
	72000, 72400, 72800, 73200, 73600, 74100, 74600, 75000, 75400,
	75800, 76200, 76600, 77000, 77400, 77800, 78200, 78600, 79000,
	79400, 79800, 80300, 80800, 81200, 81600, 82000, 82400, 82800,
	83200, 83600, 84000, 84400, 84800, 85200, 85600, 86000, 86400,
	86800, 87300, 87800, 88200, 88600, 89000, 89400, 89800, 90200,
	90600, 91000, 91400, 91800, 92200, 92600, 93000, 93400, 93800,
	94200, 94600, 95000, 95500, 96000, 96400, 96800, 97200, 97600,
	98000, 98400, 98800, 99200, 99600, 100000, 100400, 100800, 101200,
	101600, 102000, 102400, 102800, 103200, 103600, 104000, 104400,
	104800, 105200, 105600, 106100, 106600, 107000, 107400, 107800,
	108200, 108600, 109000, 109400, 109800, 110200, 110600, 111000,
	111400, 111800, 112200, 112600, 113000, 113400, 113800, 114200,
	114600, 115000, 115400, 115800, 116200, 116600, 117000, 117400,
	117800, 118200, 118600, 119000, 119400, 119800, 120200, 120600,
	121000, 121400, 121800, 122200, 122600, 123000
};


static const int
	omap4460_pcb_sensor_adc2celcius_table[PCB4460_SENSOR_MAX_ADC_VAL] = {
	-273, 135, 123, 117, 112, 108, 105, 103, 101, 99, 98,  96,  95,  94,
	93,  92,  91,  90,  89,  88,  88,  87,  86,  86,  85,  84,  84,
	83,  83,  82,  82,  81,  81,  81,  80,  80,  79,  79,  79,  78,
	78,  78,  77,  77,  77,  76,  76,  76,  75,  75,  75,  75,  74,
	74,  74,  73,  73,  73,  73,  73,  72,  72,  72,  72,  71,  71,
	71,  71,  71,  70,  70,  70,  70,  70,  69,  69,  69,  69,  69,
	69,  68,  68,  68,  68,  68,  68,  67,  67,  67,  67,  67,  67,
	66,  66,  66,  66,  66,  66,  66,  65,  65,  65,  65,  65,  65,
	65,  65,  64,  64,  64,  64,  64,  64,  64,  63,  63,  63,  63,
	63,  63,  63,  63,  63,  62,  62,  62,  62,  62,  62,  62,  62,
	62,  61,  61,  61,  61,  61,  61,  61,  61,  61,  61,  60,  60,
	60,  60,  60,  60,  60,  60,  60,  60,  59,  59,  59,  59,  59,
	59,  59,  59,  59,  59,  59,  59,  58,  58,  58,  58,  58,  58,
	58,  58,  58,  58,  58,  57,  57,  57,  57,  57,  57,  57,  57,
	57,  57,  57,  57,  57,  56,  56,  56,  56,  56,  56,  56,  56,
	56,  56,  56,  56,  56,  55,  55,  55,  55,  55,  55,  55,  55,
	55,  55,  55,  55,  55,  55,  54,  54,  54,  54,  54,  54,  54,
	54,  54,  54,  54,  54,  54,  54,  54,  53,  53,  53,  53,  53,
	53,  53,  53,  53,  53,  53,  53,  53,  53,  53,  53,  52,  52,
	52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,  52,
	52,  52,  51,  51,  51,  51,  51,  51,  51,  51,  51,  51,  51,
	51,  51,  51,  51,  51,  51,  50,  50,  50,  50,  50,  50,  50,
	50,  50,  50,  50,  50,  50,  50,  50,  50,  50,  50,  49,  49,
	49,  49,  49,  49,  49,  49,  49,  49,  49,  49,  49,  49,  49,
	49,  49,  49,  49,  48,  48,  48,  48,  48,  48,  48,  48,  48,
	48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  47,  47,
	47,  47,  47,  47,  47,  47,  47,  47,  47,  47,  47,  47,  47,
	47,  47,  47,  47,  47,  46,  46,  46,  46,  46,  46,  46,  46,
	46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,
	45,  45,  45,  45,  45,  45,  45,  45,  45,  45,  45,  45,  45,
	45,  45,  45,  45,  45,  45,  45,  45,  44,  44,  44,  44,  44,
	44,  44,  44,  44,  44,  44,  44,  44,  44,  44,  44,  44,  44,
	44,  44,  44,  44,  43,  43,  43,  43,  43,  43,  43,  43,  43,
	43,  43,  43,  43,  43,  43,  43,  43,  43,  43,  43,  43,  43,
	43,  42,  42,  42,  42,  42,  42,  42,  42,  42,  42,  42,  42,
	42,  42,  42,  42,  42,  42,  42,  42,  42,  42,  41,  41,  41,
	41,  41,  41,  41,  41,  41,  41,  41,  41,  41,  41,  41,  41,
	41,  41,  41,  41,  41,  41,  41,  41,  40,  40,  40,  40,  40,
	40,  40,  40,  40,  40,  40,  40,  40,  40,  40,  40,  40,  40,
	40,  40,  40,  40,  40,  39,  39,  39,  39,  39,  39,  39,  39,
	39,  39,  39,  39,  39,  39,  39,  39,  39,  39,  39,  39,  39,
	39,  39,  38,  38,  38,  38,  38,  38,  38,  38,  38,  38,  38,
	38,  38,  38,  38,  38,  38,  38,  38,  38,  38,  38,  38,  37,
	37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,
	37,  37,  37,  37,  37,  37,  37,  37,  37,  36,  36,  36,  36,
	36,  36,  36,  36,  36,  36,  36,  36,  36,  36,  36,  36,  36,
	36,  36,  36,  36,  36,  36,  35,  35,  35,  35,  35,  35,  35,
	35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,
	35,  35,  34,  34,  34,  34,  34,  34,  34,  34,  34,  34,  34,
	34,  34,  34,  34,  34,  34,  34,  34,  34,  34,  34,  33,  33,
	33,  33,  33,  33,  33,  33,  33,  33,  33,  33,  33,  33,  33,
	33,  33,  33,  33,  33,  33,  32,  32,  32,  32,  32,  32,  32,
	32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,
	32,  31,  31,  31,  31,  31,  31,  31,  31,  31,  31,  31,  31,
	31,  31,  31,  31,  31,  31,  31,  31,  30,  30,  30,  30,  30,
	30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,  30,
	30,  29,  29,  29,  29,  29,  29,  29,  29,  29,  29,  29,  29,
	29,  29,  29,  29,  29,  29,  29,  28,  28,  28,  28,  28,  28,
	28,  28,  28,  28,  28,  28,  28,  28,  28,  28,  28,  27,  27,
	27,  27,  27,  27,  27,  27,  27,  27,  27,  27,  27,  27,  27,
	27,  27,  26,  26,  26,  26,  26,  26,  26,  26,  26,  26,  26,
	26,  26,  26,  26,  26,  25,  25,  25,  25,  25,  25,  25,  25,
	25,  25,  25,  25,  25,  25,  25,  24,  24,  24,  24,  24,  24,
	24,  24,  24,  24,  24,  24,  24,  24,  23,  23,  23,  23,  23,
	23,  23,  23,  23,  23,  23,  23,  23,  22,  22,  22,  22,  22,
	22,  22,  22,  22,  22,  22,  22,  21,  21,  21,  21,  21,  21,
	21,  21,  21,  21,  21,  20,  20,  20,  20,  20,  20,  20,  20,
	20,  20,  20,  19,  19,  19,  19,  19,  19,  19,  19,  19,  18,
	18,  18,  18,  18,  18,  18,  18,  18,  17,  17,  17,  17,  17,
	17,  17,  17,  17,  16,  16,  16,  16,  16,  16,  16,  15,  15,
	15,  15,  15,  15,  15,  14,  14,  14,  14,  14,  14,  13,  13,
	13,  13,  13,  13,  12,  12,  12,  12,  12,  11,  11,  11,  11,
	11,  10,  10,  10,  10,  9,  9,  9,  9,  8,  8,  8,  8,
	7,  7,  7,  6,  6,  6,  5,  5,  4,  4,  4,  3,  3,
	2,  2,  1,  0,  0,  -1,  -2,  -3,  -4,  -5,  -6,  -8,  -10,
	-12};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		omap4460_pcb_sensor_adc2temp
 * @BRIEF		convert ADC code into temperature (celcius)
 * @RETURNS		temperature (Celcius)
 * @param[in]		code: ADC code read from PCB sensor
 * @DESCRIPTION		convert ADC code into temperature (celcius)
 *//*------------------------------------------------------------------------ */
int omap4460_pcb_sensor_adc2temp(unsigned int adc_value)
{
	/* Main formula to be used:
	 * (Beta*T0) / (Beta-T0*LN(-R0*(ADC_VALUE*(Rx+Ry)*Vref-1023*Ry*Vx) /
	 * (ADC_VALUE*Rx*Ry*Vref)))-273.15
	 * Following formula has been simplified assuming that Vref = Vx.
	 *
	 * NB: to avoid having to link with the math lib, used a pre-computed
	 * conversion table.
	 */
	CHECK_ARG_LESS_THAN(adc_value, PCB4460_SENSOR_MAX_ADC_VAL, -273);

	return omap4460_pcb_sensor_adc2celcius_table[adc_value];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tmp102_read_reg
 * @BRIEF		read tmp102 sensor
 * @RETURNS		> 0 in case of success (read data from tmp102 register)
 *			-1 in case of incorrect argument (i2c)
 *			-8 in case of i2c dev cannot be opened
 *			-4 in case of I2C read error
 * @param[in]		reg: tmp102 register address
 * @DESCRIPTION		read tmp102 sensor
 *//*------------------------------------------------------------------------ */
static inline int tmp102_read_reg(unsigned char reg)
{
	int retres;
	unsigned int tmp102_data;
	retres = i2cget_word(4, 0x48, reg, &tmp102_data);
	if (retres < 0) {
		return retres;
	} else {
		return  (int) ((tmp102_data << 8) & 0xFF00) |
			((tmp102_data >> 8) & 0xFF);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tmp102_write_reg
 * @BRIEF		write to tmp102 sensor register
 * @RETURNS		0 in case of success
 *			-1 in case of incorrect argument (i2c)
 *			-8 in case of i2c dev cannot be opened
 *			-4 in case of I2C read error
 * @param[in]		reg: tmp102 register address
 * @param[in]		val: data to write
 * @DESCRIPTION		write to tmp102 sensor register
 *//*------------------------------------------------------------------------ */
static inline int tmp102_write_reg(unsigned char reg, unsigned short val)
{
	return i2cset_word(4, 0x48, reg, ((val << 8) & 0xFF00) |
		((val >> 8) & 0xFF));
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tmp102_reg_to_mC
 * @BRIEF		convert tmp102 register value into temperature
 *			(millicelcius)
 * @RETURNS		temperatute value in celsius
 * @param[in]		val: register code read from tmp102
 * @param[in]		IsExtendedMode: mode of tmp102 sensor
 * @DESCRIPTION		convert tmp102 register value into temperature
 *			(millicelcius)
 *//*------------------------------------------------------------------------ */
static inline int tmp102_reg_to_mC(short int val, int IsExtendedMode)
{
	if (IsExtendedMode)
		return ((val & ~0x01) * 1000) / 128;
	else
		return ((val & ~0x01) * 1000) / 256;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp44xx_bandgap_adc_code2celcius
 * @BRIEF		convert ADC code into temperature (celcius)
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		code: ADC code read from bandgap register
 * @param[in,out]	temp: temperature (Celcius, min) (returned)
 * @DESCRIPTION		convert ADC code into temperature (celcius)
 *			ADC code actually gives range, so it returns the min
 *			temperature in the range indicated by ADC code.
 *//*------------------------------------------------------------------------ */
int temp44xx_bandgap_adc_code2celcius(unsigned short int code, int *temp)
{
	if (temp == NULL)
		return OMAPCONF_ERR_ARG;
	*temp = -50;
	if (code >= 128)
		return OMAPCONF_ERR_ARG;

	if (code <= 13)
		*temp = -40;
	else if (code >= 107)
		*temp = 125;
	else
		*temp = adc_code2celcius_table[code - 14];

	dprintf("%s(): adc code=%d => temp=%d C\n", __func__, code, *temp);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp44xx_bandgap_sensor_is_enabled
 * @BRIEF		return bandgap temperature sensor clock status
 * @RETURNS		0 if bandgap sensor clock is not enabled, or in case of
 *			error
 *			1 if bandgap sensor clock is enabled
 * @DESCRIPTION		return bandgap temperature sensor clock status
 *//*------------------------------------------------------------------------ */
int temp44xx_bandgap_sensor_is_enabled(void)
{
	unsigned int cm_wkup_bandgap_clkctrl;
	int ret;

	if (!cpu_is_omap44xx()) {
		fprintf(stderr, "CPU is not supported yet.\n");
		return 0;
	}

	/* Read bandgap sensor clock control register */
	ret = mem_read(OMAP4460_CM_WKUP_BANDGAP_CLKCTRL,
		&cm_wkup_bandgap_clkctrl);
	if (ret != 0) {
		fprintf(stderr, "%s(): Error reading clock register! (%d)\n",
			__func__, ret);
		return 0;
	}
	dprintf("%s(): CM_WKUP_BANDGAP_CLKCTRL = 0x%08X\n",
		__func__, cm_wkup_bandgap_clkctrl);

	/* check if bandgap sensor clock is enabled or not */
	if ((cm_wkup_bandgap_clkctrl & OMAP4460_BANDGAP_CLKON_MASK) == 0) {
		dprintf("%s(): bandgap sensor clock is disabled\n", __func__);
		ret = 0;
	} else {
		dprintf("%s(): bandgap sensor clock is enabled\n", __func__);
		ret = 1;
	}

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp44xx_bandgap_sensor_enable
 * @BRIEF		enable bandgap temperature sensor clock
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		enable bandgap temperature sensor clock
 *//*------------------------------------------------------------------------ */
int temp44xx_bandgap_sensor_enable(void)
{
	unsigned int cm_wkup_bandgap_clkctrl;
	int ret;

	if (!cpu_is_omap44xx()) {
		fprintf(stderr, "CPU is not supported yet.\n");
		return OMAPCONF_ERR_CPU;
	}

	/* Read bandgap sensor clock control register */
	ret = mem_read(OMAP4460_CM_WKUP_BANDGAP_CLKCTRL,
			&cm_wkup_bandgap_clkctrl);
	if (ret != 0) {
		fprintf(stderr, "%s(): Error reading clock register! (%d)\n",
			__func__, ret);
		return OMAPCONF_ERR_REG_ACCESS;
	}

	/* Enable optional fclk */
	ret = mem_write(OMAP4460_CM_WKUP_BANDGAP_CLKCTRL,
			cm_wkup_bandgap_clkctrl | OMAP4460_BANDGAP_CLKON_MASK);
	if (ret != 0) {
		fprintf(stderr, "%s(): Error writing control register! (%d)\n",
			__func__, ret);
		return OMAPCONF_ERR_REG_ACCESS;
	}

	dprintf("%s(): bandgap sensor clock enabled\n", __func__);
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp44xx_bandgap_sensor_disable
 * @BRIEF		disable bandgap temperature sensor clock
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		disable bandgap temperature sensor clock
 *//*------------------------------------------------------------------------ */
int temp44xx_bandgap_sensor_disable(void)
{
	unsigned int cm_wkup_bandgap_clkctrl;
	int ret;

	if (!cpu_is_omap44xx()) {
		fprintf(stderr, "CPU is not supported yet.\n");
		return OMAPCONF_ERR_CPU;
	}

	/* Read bandgap sensor clock control register */
	ret = mem_read(OMAP4460_CM_WKUP_BANDGAP_CLKCTRL,
			&cm_wkup_bandgap_clkctrl);
	if (ret != 0) {
		fprintf(stderr, "%s(): Error reading clock register! (%d)\n",
			__func__, ret);
		return OMAPCONF_ERR_REG_ACCESS;
	}

	/* Disable optional fclk */
	ret = mem_write(OMAP4460_CM_WKUP_BANDGAP_CLKCTRL,
			cm_wkup_bandgap_clkctrl & ~OMAP4460_BANDGAP_CLKON_MASK);
	if (ret != 0) {
		fprintf(stderr, "%s(): Error writing control register! (%d)\n",
			__func__, ret);
		return OMAPCONF_ERR_REG_ACCESS;
	}

	dprintf("%s(): bandgap sensor clock disabled\n", __func__);
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp4460_bandgap_sensor_clock_get
 * @BRIEF		return bandgap temperature sensor clock rate in MHz
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		return bandgap temperature sensor clock rate in MHz
 *//*------------------------------------------------------------------------ */
double temp4460_bandgap_sensor_clock_get(void)
{
	unsigned int cm_wkup_bandgap_clkctrl;
	int ret;
	unsigned char div;
	double rate;

	/* Read bandgap sensor clock control register */
	ret = mem_read(OMAP4460_CM_WKUP_BANDGAP_CLKCTRL,
			&cm_wkup_bandgap_clkctrl);
	if (ret != 0) {
		fprintf(stderr, "%s(): Error reading clock register! (%d)\n",
			__func__, ret);
		return (double) OMAPCONF_ERR_REG_ACCESS;
	}
	dprintf("%s(): CM_WKUP_BANDGAP_CLKCTRL = 0x%08X\n",
		__func__, cm_wkup_bandgap_clkctrl);

	/* Retieve L4WKUP_ICLK rate */
	rate = (unsigned int) clk44xx_get_clock_speed(OMAP4_L4WKUP_ICLK, 0);
	if (rate <= 0.0)
		return rate;

	/* Retrieve divider value */
	div = 8 << extract_bitfield(cm_wkup_bandgap_clkctrl, 24, 2);
	dprintf(
		"%s(): sensor f-clk rate = %lfMHz (L4WKUP_ICLK (%lfMHz) / %u)\n",
		__func__, rate / div, rate, div);

	return rate / (double) div;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp4460_bandgap_sensor_clock_set
 * @BRIEF		set bandgap temperature sensor clock divider to
 *			guarantee a rate between 1 and 2MHz.
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @DESCRIPTION		set bandgap temperature sensor clock divider to
 *			guarantee a rate between 1 and 2MHz.
 *//*------------------------------------------------------------------------ */
int temp4460_bandgap_sensor_clock_set(void)
{
	unsigned int cm_wkup_bandgap_clkctrl;
	int ret;
	unsigned char div;
	double rate;

	/* Read bandgap sensor clock control register */
	ret = mem_read(OMAP4460_CM_WKUP_BANDGAP_CLKCTRL,
			&cm_wkup_bandgap_clkctrl);
	if (ret != 0) {
		fprintf(stderr, "%s(): Error reading clock register! (%d)\n",
			__func__, ret);
		return (double) OMAPCONF_ERR_REG_ACCESS;
	}
	dprintf("%s(): CM_WKUP_BANDGAP_CLKCTRL = 0x%08X\n",
		__func__, cm_wkup_bandgap_clkctrl);

	/* Retieve L4WKUP_ICLK rate */
	rate = (unsigned int) clk44xx_get_clock_speed(OMAP4_L4WKUP_ICLK, 0);
	if (rate <= 0.0)
		return OMAPCONF_ERR_INTERNAL;

	/* Select divider to guarantee a rate between 1 and 2MHz. */
	div = ((unsigned int) rate >> 4) & 3;
	dprintf("%s(): div = %u\n", __func__, div);
	div = (((unsigned int) rate >> 4) & 3) << 24;

	/* Update divider in register */
	ret = mem_write(OMAP4460_CM_WKUP_BANDGAP_CLKCTRL,
			cm_wkup_bandgap_clkctrl | div);
	if (ret != 0) {
		fprintf(stderr, "%s(): Error writing control register! (%d)\n",
			__func__, ret);
		return OMAPCONF_ERR_REG_ACCESS;
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp4460_read_bandgap_sensor
 * @BRIEF		read temperature from OMAP bandgap temperature sensor
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in,out]	temp: bandgap sensor temperature (Celcius) (returned)
 * @DESCRIPTION		read temperature from OMAP bandgap temperature sensor
 *			OMAP4460 specific implementation
 *//*------------------------------------------------------------------------ */
int temp4460_read_bandgap_sensor(int *temp)
{
	unsigned int control_temp_sensor;
	unsigned int control_temp_sensor_saved;
	unsigned int res, enabled;
	int ret;
	unsigned short adc_val;
	#ifdef TEMP44XX_DEBUG
	double rate;
	#endif

	if (temp == NULL)
		return OMAPCONF_ERR_ARG;
	*temp = 0;
	if (!cpu_is_omap4460() && !cpu_is_omap4470())
		return OMAPCONF_ERR_CPU;

	ret = mem_read(OMAP4460_CORE_STD_FUSE_OPP_BGAP, &res);
	if (ret != 0) {
		dprintf("%s(): Error reading trim register! (%d)\n",
			__func__, ret);
		return OMAPCONF_ERR_REG_ACCESS;
	}
	if (res == 0)
		printf(
			"WARNING: invalid EFUSE => non-trimmed BGAP sensor, temperature is not accurate\n");


	/* Make sure sensor clock is correctly configured */
	#ifdef TEMP44XX_DEBUG
	rate = temp4460_bandgap_sensor_clock_get();
	dprintf("%s(): sensor rate is %lf\n", __func__, rate);
	#endif
	ret = temp4460_bandgap_sensor_clock_set();
	if (ret < 0) {
		fprintf(stderr, "%s(): could not set sensor rate! (%d)\n",
			__func__, ret);
		return ret;
	}
	#ifdef TEMP44XX_DEBUG
	rate = temp4460_bandgap_sensor_clock_get();
	dprintf("%s(): sensor new rate is %lf\n", __func__, rate);
	#endif

	/* Enable sensor clock, if not yet enabled */
	enabled = temp44xx_bandgap_sensor_is_enabled();
	if (!enabled) {
		ret = temp44xx_bandgap_sensor_enable();
		if (ret != 0) {
			fprintf(stderr, "%s(): could not enable clock!\n",
				__func__);
			return ret;
		}
	}

	/* Read control register */
	ret = mem_read(OMAP4430_CONTROL_TEMP_SENSOR, &control_temp_sensor);
	if (ret != 0) {
		dprintf("%s(): Error reading control register! (%d)\n",
			__func__, ret);
		ret = OMAPCONF_ERR_REG_ACCESS;
		goto temp4460_read_bandgap_sensor_end;
	}
	dprintf("%s(): 1st read control_temp_sensor = 0x%08X\n",
		__func__, control_temp_sensor);

	control_temp_sensor_saved = control_temp_sensor;
	/* check if temp_sensor wasn't enabled, if not enable it */
	if ((control_temp_sensor & OMAP4460_BGAP_TEMPSOFF_MASK)) {
		ret = mem_write(OMAP4430_CONTROL_TEMP_SENSOR,
			control_temp_sensor & ~OMAP4460_BGAP_TEMPSOFF_MASK);
		if (ret != 0) {
			dprintf(
				"%s: Error writing control register (start)! (%d)\n",
				__func__, ret);
			ret = OMAPCONF_ERR_REG_ACCESS;
			goto temp4460_read_bandgap_sensor_end;
		}
	}
	/* check if conversion is running now, if not start it*/
	if ((control_temp_sensor & (OMAP4460_BGAP_TEMP_SENSOR_EOCZ_MASK
			| OMAP4460_BGAP_TEMP_SENSOR_SOC_MASK)) == 0) {
		/* start */
		control_temp_sensor |= OMAP4460_BGAP_TEMP_SENSOR_SOC_MASK;
		ret = mem_write(OMAP4430_CONTROL_TEMP_SENSOR,
			control_temp_sensor);
		usleep(20);
		ret = mem_read(OMAP4430_CONTROL_TEMP_SENSOR,
			&control_temp_sensor);
		/* clear start */
		control_temp_sensor &= ~OMAP4460_BGAP_TEMP_SENSOR_SOC_MASK;
		ret = mem_write(OMAP4430_CONTROL_TEMP_SENSOR,
			control_temp_sensor);
	}
	/* sleep for 200 us, should be enough to finish conversion */
	usleep(200);
	/* read result */
	ret = mem_read(OMAP4430_CONTROL_TEMP_SENSOR, &control_temp_sensor);
	if (ret != 0) {
		dprintf("%s(): Error reading control register (conv)! (%d)\n",
			__func__, ret);
		ret = OMAPCONF_ERR_REG_ACCESS;
		goto temp4460_read_bandgap_sensor_end;
	}
	/* check if conversion is running now*/
	if ((control_temp_sensor & (OMAP4460_BGAP_TEMP_SENSOR_EOCZ_MASK
			| OMAP4460_BGAP_TEMP_SENSOR_SOC_MASK
			| OMAP4460_BGAP_TEMP_SENSOR_CONTCONV_MASK)) == 0) {
		/* restore off state */
		if ((control_temp_sensor_saved & OMAP4460_BGAP_TEMPSOFF_MASK))
			ret = mem_write(OMAP4430_CONTROL_TEMP_SENSOR,
				control_temp_sensor |
					OMAP4460_BGAP_TEMPSOFF_MASK);
	}
	/* calculate temperature */
	adc_val = control_temp_sensor & OMAP4460_BGAP_TEMP_SENSOR_DTEMP_MASK;
	if (adc_val < OMAP_ADC_START_VALUE || adc_val > OMAP_ADC_END_VALUE) {
		printf("%s(): invalid adc code reported by the sensor! (%d)\n",
			__func__, control_temp_sensor);
		ret = OMAPCONF_ERR_UNEXPECTED;
	} else {
		*temp = (OMAP4460_adc_to_temp[adc_val - OMAP_ADC_START_VALUE] +
			500) / 1000;
		ret = 0;
	}

temp4460_read_bandgap_sensor_end:
	/* Restore sensor clock to previous state */
	if (!enabled)
		temp44xx_bandgap_sensor_disable();

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp4430_read_bandgap_sensor
 * @BRIEF		read temperature from OMAP bandgap temperature sensor
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 * @param[in,out]	temp: bandgap sensor temperature (Celcius) (returned)
 * @DESCRIPTION		read temperature from OMAP bandgap temperature sensor
 *			OMAP4430 specific implementation
 *//*------------------------------------------------------------------------ */
int temp4430_read_bandgap_sensor(int *temp)
{
	unsigned int control_temp_sensor, enabled;
	int ret;
	unsigned short adc_val;

	if (!cpu_is_omap4430())
		return OMAPCONF_ERR_CPU;
	if (temp == NULL)
		return OMAPCONF_ERR_ARG;
	*temp = 0;

	/* Enable sensor clock, if not yet enabled */
	enabled = temp44xx_bandgap_sensor_is_enabled();
	if (!enabled) {
		ret = temp44xx_bandgap_sensor_enable();
		if (ret != 0) {
			fprintf(stderr, "%s(): could not enable clock!\n",
				__func__);
			return ret;
		}
	}

	/* Read control register */
	ret = mem_read(OMAP4430_CONTROL_TEMP_SENSOR, &control_temp_sensor);
	if (ret != 0) {
		dprintf("%s(): Error reading control register! (%d)\n",
			__func__, ret);
		ret = OMAPCONF_ERR_REG_ACCESS;
		goto temp4430_read_bandgap_sensor_end;
	}
	dprintf("%s(): 1st read control_temp_sensor = 0x%08X\n",
		__func__, control_temp_sensor);

	/*
	 * Clean previous operation.
	 * Just in case a previous operation did not complete
	 * Sensor needs a rising edge on this bit
	 */
	control_temp_sensor &= ~(1 << 9);
	dprintf("%s(): 1st write control_temp_sensor = 0x%08X\n",
		__func__, control_temp_sensor);
	ret = mem_write(OMAP4430_CONTROL_TEMP_SENSOR, control_temp_sensor);
	if (ret != 0) {
		dprintf("%s: Error writing control register (clean)! (%d)\n",
			__func__, ret);
		ret = OMAPCONF_ERR_REG_ACCESS;
		goto temp4430_read_bandgap_sensor_end;
	}
	usleep(10000); /* wait for 10ms before next operation */

	/* Start Conversion (Single Conversion Mode) */
	control_temp_sensor |= (1 << 9);
	dprintf("%s(): start write control_temp_sensor = 0x%08X\n",
		__func__, control_temp_sensor);
	ret = mem_write(OMAP4430_CONTROL_TEMP_SENSOR, control_temp_sensor);
	if (ret != 0) {
		dprintf("%s(): Error writing control register (start)! (%d)\n",
			__func__, ret);
		ret = OMAPCONF_ERR_REG_ACCESS;
		goto temp4430_read_bandgap_sensor_end;
	}

	/* Wait for end of Conversion
	 * Conversion time is about 11-14 32K cycles (~0.5us)
	 * After some testing, for some reason EOCZ bit (8) is always low
	 * even when no conversion ongoing. Don't check it then ...
	 */
	usleep(1000);

	/* Stop Conversion */
	control_temp_sensor &= ~(1 << 9);
	dprintf("%s(): stop write control_temp_sensor = 0x%08X\n",
		__func__, control_temp_sensor);
	ret = mem_write(OMAP4430_CONTROL_TEMP_SENSOR, control_temp_sensor);
	if (ret != 0) {
		dprintf("%s: Error writing control register (stop)! (%d)\n",
			__func__, ret);
		ret = OMAPCONF_ERR_REG_ACCESS;
		goto temp4430_read_bandgap_sensor_end;
	}

	/* Read value from sensor */
	ret = mem_read(OMAP4430_CONTROL_TEMP_SENSOR, &control_temp_sensor);
	if (ret != 0) {
		dprintf("%s(): Error reading control register (conv)! (%d)\n",
			__func__, ret);
		ret = OMAPCONF_ERR_REG_ACCESS;
		goto temp4430_read_bandgap_sensor_end;
	}

	/* Convert sensor value to celcius degrees */
	adc_val = extract_bitfield(control_temp_sensor, 0, 8);
	ret = temp44xx_bandgap_adc_code2celcius(adc_val, temp);
	dprintf("%s(): control_temp_sensor = 0x%08X adc_val = %d temp = %d\n",
		__func__, control_temp_sensor, adc_val, *temp);

temp4430_read_bandgap_sensor_end:
	/* Restore sensor clock to previous state */
	if (!enabled)
		temp44xx_bandgap_sensor_disable();

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp44xx_read_bandgap_sensor
 * @BRIEF		read temperature from OMAP bandgap temperature sensor
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 * @param[in,out]	temp: bandgap sensor temperature (Celcius) (returned)
 * @DESCRIPTION		read temperature from OMAP bandgap temperature sensor
 *//*------------------------------------------------------------------------ */
int temp44xx_read_bandgap_sensor(int *temp)
{
	FILE *fp = NULL;
	char line[256];
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(temp, OMAPCONF_ERR_ARG)

	*temp = 0;

	/* First try to use data from temperature sensor driver, if loaded */
	if (os_is_android()) {
		if (os_is_android() && (android_pastry_get() < PASTRY_ICS))
			fp = fopen(
				"/sys/devices/platform/omap_temp_sensor.0/temp1_input",
				"r");
		else
			fp = fopen(
				"/sys/devices/platform/omap/omap_temp_sensor.0/temp1_input",
				"r");
		if (fp == NULL) {
			dprintf("%s(): couldn't open temp sensor file!\n",
				__func__);
			goto temp44xx_read_bandgap_sensor_no_driver;
		}
		if (fgets(line, 256, fp) == NULL) {
			fclose(fp);
			goto temp44xx_read_bandgap_sensor_no_driver;
		}
		fclose(fp);

		/* Remove endind '\n' */
		line[strlen(line) - 1] = '\0';
		dprintf("%s(): line=%s len=%u\n", __func__, line, strlen(line));

		/* Retrieve temperature, in millidegrees celcius */
		ret = sscanf(line, "%d", temp);
		if (ret != 1)
			goto temp44xx_read_bandgap_sensor_no_driver;
		*temp = *temp / 1000; /* convert to degrees */

		return 0;
	}

temp44xx_read_bandgap_sensor_no_driver:
	if (cpu_is_omap4430())
		return temp4430_read_bandgap_sensor(temp);
	else /* 4460 & 4470 */
		return temp4460_read_bandgap_sensor(temp);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp4470_read_pcb_sensor
 * @BRIEF		read temperature from OMAP pcb temperature sensor
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 * @param[in,out]	temp: pcb sensor temperature (Celcius) (returned)
 * @DESCRIPTION		read temperature from OMAP pcb temperature sensor
 *			OMAP4470 specific implementation
 *//*------------------------------------------------------------------------ */
int temp4470_read_pcb_sensor(int *temp)
{
	FILE *fp = NULL;
	char line[256];
	int ret;
	int conf;
	static const char pcb_temp_file_gb[] =
		"/sys/devices/platform/i2c_omap.4/i2c-4/4-0048/temp1_input";
	static const char pcb_temp_file_ics[] =
		"/sys/devices/platform/omap/omap_i2c.4/i2c-4/4-0048/temp1_input";
	char *pcb_temp_file;

	CHECK_CPU(4470, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(temp, OMAPCONF_ERR_ARG)
	*temp = -273;

	/* First try to use data from temperature sensor driver, if loaded */
	if (os_is_android()) {
		if (android_pastry_get() < PASTRY_ICS)
			pcb_temp_file = (char *) pcb_temp_file_gb;
		else
			pcb_temp_file = (char *) pcb_temp_file_ics;
		fp = fopen(pcb_temp_file, "r");
		if (fp == NULL) {
			dprintf("%s(): couldn't open temp sensor file! (%s)\n",
				__func__, pcb_temp_file);
			goto temp4470_read_pcb_sensor_no_driver;
		}
		if (fgets(line, 256, fp) == NULL) {
			fclose(fp);
			goto temp4470_read_pcb_sensor_no_driver;
		}
		fclose(fp);

		/* Remove endind '\n' */
		line[strlen(line) - 1] = '\0';
		dprintf("%s(): line=%s len=%u\n", __func__, line, strlen(line));

		/* Retrieve temperature, in millidegrees celcius */
		ret = sscanf(line, "%d", temp);
		if (ret != 1)
			goto temp4470_read_pcb_sensor_no_driver;
		*temp = *temp / 1000; /* convert to degrees */

		return 0;
	}

temp4470_read_pcb_sensor_no_driver:
	conf = tmp102_read_reg(TMP102_CONF_REG);
	if (conf < 0) {
		fprintf(stderr, "%s(): could not read register!(%d)\n",
			__func__, conf);
		return OMAPCONF_ERR_REG_ACCESS;
	}

	/* Check if tmp102 is in shut down mode */
	if (conf & TMP102_CONF_SD) {
		conf &= ~TMP102_CONF_SD;
		ret = tmp102_write_reg(TMP102_CONF_REG, conf);
		if (ret < 0) {
			fprintf(stderr,
				"%s(): could not write register!(%d)\n",
				__func__, ret);
			return OMAPCONF_ERR_REG_ACCESS;
		}
	}

	ret = tmp102_read_reg(TMP102_TEMP_REG);
	if (ret < 0) {
		fprintf(stderr, "%s(): could not read register!(%d)\n",
			__func__, ret);
		return OMAPCONF_ERR_REG_ACCESS;
	}

	*temp = tmp102_reg_to_mC(ret, conf & TMP102_CONF_EM);
	*temp = *temp / 1000; /* convert to degrees */
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp44xx_read_pcb_sensor
 * @BRIEF		read temperature from OMAP4470 pcb temperature sensor
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 * @param[in,out]	temp: pcb sensor temperature (Celcius) (returned)
 * @DESCRIPTION		read temperature from OMAP4470 pcb temperature sensor
 *//*------------------------------------------------------------------------ */
int temp4460_read_pcb_sensor(int *temp)
{
	FILE *fp = NULL;
	char line[256];
	int ret;
	static const char pcb_temp_file_gb[] =
		"/sys/devices/platform/i2c_omap.1/i2c-1/1-0049/twl6030_gpadc/in4_input";
	static const char pcb_temp_file_ics[] =
		"/sys/devices/platform/omap/pcb_temp_sensor.0/temp1_input";
	char *pcb_temp_file;

	CHECK_CPU(4460, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(temp, OMAPCONF_ERR_ARG)
	*temp = -273;

	/* First try to use data from temperature sensor driver, if loaded */
	if (os_is_android()) {
		if (android_pastry_get() < PASTRY_ICS)
			pcb_temp_file = (char *) pcb_temp_file_gb;
		else
			pcb_temp_file = (char *) pcb_temp_file_ics;
		fp = fopen(pcb_temp_file, "r");
		if (fp == NULL) {
			fprintf(stderr,
				"Couldn't open PCB sensor file! (%s)\n\n",
				pcb_temp_file);
			return OMAPCONF_ERR_NOT_AVAILABLE;
		}
		if (fgets(line, 256, fp) == NULL) {
			fclose(fp);
			return OMAPCONF_ERR_NOT_AVAILABLE;
		}
		fclose(fp);

		/* Remove endind '\n' */
		line[strlen(line) - 1] = '\0';
		dprintf("%s(): line=%s len=%u\n", __func__, line, strlen(line));

		/* Retrieve temperature, in millidegrees celcius */
		ret = sscanf(line, "%d", temp);
		if (ret != 1)
			return OMAPCONF_ERR_NOT_AVAILABLE;
		*temp = omap4460_pcb_sensor_adc2temp(*temp);
		return 0;
	} else {
		/* FIXME */
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp44xx_read_pcb_sensor
 * @BRIEF		read temperature from pcb temperature sensor
 *			(when available)
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 * @param[in,out]	temp: pcb sensor temperature (Celcius) (returned)
 * @DESCRIPTION		read temperature from pcb temperature sensor
 *			(when available)
 *//*------------------------------------------------------------------------ */
int temp44xx_read_pcb_sensor(int *temp)
{
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(temp, OMAPCONF_ERR_ARG);
	*temp = -273;

	/* First try to use data from temperature sensor driver, if loaded */
	if (cpu_is_omap4430()) {
		printf("PCB temperature sensor is not present on OMAP4430.\n");
		*temp = TEMP_ABSOLUTE_ZERO;
		ret = OMAPCONF_ERR_NOT_AVAILABLE;
	} else if (cpu_is_omap4470()) {
		ret = temp4470_read_pcb_sensor(temp);
	} else if (cpu_is_omap4460()) {
		ret = temp4460_read_pcb_sensor(temp);
	}

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp44xx_hotspot_temp_get
 * @BRIEF		return hotspot temperature (in deg. C)
 * @RETURNS		hotspot temperature (-273 deg. C in case of error)
 * @DESCRIPTION		return hotspot temperature (in deg. C)
 *//*------------------------------------------------------------------------ */
int temp44xx_hotspot_temp_get(void)
{
	FILE *fp = NULL;
	char line[256];
	int ret, degc;
	static const char hotspot_temp_file[] =
		"/sys/devices/platform/omap/omap_temp_sensor.0/hotspot_temp";

	CHECK_CPU(44xx, TEMP_ABSOLUTE_ZERO);

	fp = fopen(hotspot_temp_file, "r");
	if (fp == NULL) {
		dprintf(
			"Hotspot temperature sensor file (%s) could not be opened.\n",
			hotspot_temp_file);
		return TEMP_ABSOLUTE_ZERO;
	}
	if (fgets(line, 256, fp) == NULL) {
		fclose(fp);
		fprintf(stderr,
			"Unexpected error reading hotspot temperature sensor file (%s).\n\n",
			hotspot_temp_file);
		return TEMP_ABSOLUTE_ZERO;
	}
	fclose(fp);

	/* Remove endind '\n' */
	line[strlen(line) - 1] = '\0';
	dprintf("%s(): line=%s len=%u\n", __func__, line, strlen(line));

	/* Retrieve temperature, in millidegrees celcius */
	ret = sscanf(line, "hot spot temp%d", &degc);
	if (ret != 1) {
		fprintf(stderr,
			"Unexpected error reading hotspot temperature sensor file (%s).\n\n",
			hotspot_temp_file);
		return TEMP_ABSOLUTE_ZERO;
	}
	degc = degc / 1000; /* convert to degrees */

	return degc;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp44xx_read_mem_sensor
 * @BRIEF		read temperature from OMAP memory temperature sensor
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in]		emif: EMIF instance (1-2)
 * @param[in]		cs: chip select (0-1)
 * @param[in, out]	temp: memory sensor temperature (Celcius) (returned)
 * @DESCRIPTION		read temperature from OMAP memory temperature sensor
 *//*------------------------------------------------------------------------ */
int temp44xx_read_mem_sensor(unsigned short emif,
	unsigned short cs, omap4_emif_temperature *temp)
{
	unsigned int emif_lpddr2_mode_reg_cfg_addr;
	unsigned int emif_lpddr2_mode_reg_cfg;
	unsigned int emif_lpddr2_mode_reg_data_addr;
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(cs, emif44xx_cs_count_get(), OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(temp, OMAPCONF_ERR_ARG);
	*temp = OMAP4_EMIF_TEMP_BELOW_85C;

	switch (emif) {
	case 1:
		emif_lpddr2_mode_reg_cfg_addr =
			OMAP44XX_EMIF1_LPDDR2_MODE_REG_CFG;
		emif_lpddr2_mode_reg_data_addr =
			OMAP44XX_EMIF1_LPDDR2_MODE_REG_DATA;
		break;
	case 2:
		emif_lpddr2_mode_reg_cfg_addr =
			OMAP44XX_EMIF2_LPDDR2_MODE_REG_CFG;
		emif_lpddr2_mode_reg_data_addr =
			OMAP44XX_EMIF2_LPDDR2_MODE_REG_DATA;
		break;
	default:
		return OMAPCONF_ERR_ARG;
	}

	switch (cs) {
	case 0:
		emif_lpddr2_mode_reg_cfg = 0x4;
		break;
	case 1:
		emif_lpddr2_mode_reg_cfg = 0x80000004;
		break;
	default:
		return OMAPCONF_ERR_ARG;
	}
	/* Write EMIF cfg register */
	ret = mem_write(emif_lpddr2_mode_reg_cfg_addr,
		emif_lpddr2_mode_reg_cfg);
	if (ret != 0) {
		dprintf("%s(): Error writing cfg register! (%d)\n",
			__func__, ret);
		return OMAPCONF_ERR_REG_ACCESS;
	}

	/* Read EMIF data register */
	ret = mem_read(emif_lpddr2_mode_reg_data_addr, (unsigned int *) temp);
	if (ret != 0) {
		dprintf("%s(): Error reading data register! (%d)\n",
			__func__, ret);
		return OMAPCONF_ERR_REG_ACCESS;
	}
	dprintf("%s(): emif_lpddr2_mode_reg_data = 0x%08X\n", __func__, *temp);

	/* Mask result with MR4_SDRAM_REF_RATE_MASK */
	*temp &= 0x7;

	/* if reported value is < OMAP4_EMIF_TEMP_BELOW_85C, treat as normal */
	if (*temp < OMAP4_EMIF_TEMP_BELOW_85C)
		*temp = OMAP4_EMIF_TEMP_BELOW_85C;

	if ((*temp == OMAP4_EMIF_TEMP_BELOW_85C) ||
		(*temp == OMAP4_EMIF_TEMP_ABOVE_85C) ||
		(*temp == OMAP4_EMIF_TEMP_EXCEED_105C)) {
		return 0;
	} else {
		*temp = OMAP4_EMIF_TEMP_RESERVED;
		return OMAPCONF_ERR_UNEXPECTED;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		temp44xx_get
 * @BRIEF		read temperature from selected temperature sensor
 * @RETURNS		temperature on success (> TEMP_ABSOLUTE_ZERO)
 *			TEMP_ABSOLUTE_ZERO in case of error
 * @param[in]		id: valid OMAP4 temperature sensor ID
 * @DESCRIPTION		read temperature from selected temperature sensor
 *//*------------------------------------------------------------------------ */
int temp44xx_get(temp44xx_sensor_id id)
{
	int ret, temp;

	switch (id) {
	case TEMP44XX_BANDGAP:
		ret = temp44xx_read_bandgap_sensor(&temp);
		if (ret != 0)
			temp = TEMP_ABSOLUTE_ZERO;
		break;

	case TEMP44XX_HOTSPOT:
		temp = temp44xx_hotspot_temp_get();
		break;

	case TEMP44XX_DDR1_CS1:
		ret = temp44xx_read_mem_sensor(1, 0,
			(omap4_emif_temperature *) &temp);
		if (ret != 0)
			temp = TEMP_ABSOLUTE_ZERO;
		break;

	case TEMP44XX_DDR2_CS1:
		ret = temp44xx_read_mem_sensor(2, 0,
			(omap4_emif_temperature *) &temp);
		if (ret != 0)
			temp = TEMP_ABSOLUTE_ZERO;
		break;

	case TEMP44XX_DDR1_CS2:
		if (emif44xx_cs_count_get() != 2)
			return TEMP_ABSOLUTE_ZERO;
		ret = temp44xx_read_mem_sensor(1, 1,
			(omap4_emif_temperature *) &temp);
		if (ret != 0)
			temp = TEMP_ABSOLUTE_ZERO;
		break;

	case TEMP44XX_DDR2_CS2:
		if (emif44xx_cs_count_get() != 2) {
			temp = TEMP_ABSOLUTE_ZERO;
			break;
		}
		ret = temp44xx_read_mem_sensor(2, 1,
			(omap4_emif_temperature *) &temp);
		if (ret != 0)
			temp = TEMP_ABSOLUTE_ZERO;
		break;

	case TEMP44XX_PCB:
		ret = temp44xx_read_pcb_sensor(&temp);
		if (ret != 0)
			temp = TEMP_ABSOLUTE_ZERO;
		break;

	default:
		fprintf(stderr,
			"omapconf: %s(): id (%u) >= TEMP44XX_ID_MAX (%u) !!!\n",
			__func__, id, TEMP44XX_ID_MAX);
		temp = TEMP_ABSOLUTE_ZERO;
	}

	dprintf("%s(%d) = %dC\n", __func__, (int) id, temp);
	return temp;
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
