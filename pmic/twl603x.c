/*
 *
 * @Component			OMAPCONF
 * @Filename			twl603x.c
 * @Description			OMAP4 TWL603x Power Companion Chip Library
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


#include <string.h>
#include <twl603x.h>
#include <i2c-tools.h>
#include <stdio.h>
#include <lib.h>
#include <cpuinfo.h>
#include <twl603x_lib.h>
#include <help.h>
#include <lib_android.h>


/* #define TWL603X_DEBUG */
#ifdef TWL603X_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


#define TWL6030_VSEL_LEN		6
#define TWL6030_VSTEP_UV		12660
#define TWL6030_VOFFSET_0_UV		608000
#define TWL6030_VOFFSET_1_UV		709000

#define TWL6030_SMPS_VOLTAGE0_UV	1367400
#define TWL6030_SMPS_VOLTAGE1_UV	1519300
#define TWL6030_SMPS_VOLTAGE2_UV	1823100
#define TWL6030_SMPS_VOLTAGE3_UV	1924400
#define TWL6030_SMPS_VOLTAGE4_UV	2127000


#define TWL6035_I2C_BUS			1
#define TWL6035_ID0_ADDR		0x12
#define TWL6035_ID1_ADDR		0x48
#define TWL6035_ID2_ADDR		0x49

#define TWL6035_VOFFSET_UV		500000
#define TWL6035_VSTEP_UV		10000
#define TWL6035_VSEL_LEN		8
#define TWL6035_SMPS_LOW_RANGE_UVMIN	TWL6035_VOFFSET_UV
#define TWL6035_SMPS_LOW_RANGE_UVMAX	1650000
#define TWL6035_SMPS_HIGH_RANGE_UVMIN	1650000
#define TWL6035_SMPS_HIGH_RANGE_UVMAX	3300000


static const char
	twl_603x_chip_name[TWL603X_TYPE_MAX + 1][TWL603x_NAME_MAX_LEN] = {
	"TWL6030",
	"TWL6032",
	"TWL6035",
	"FIXME"};


typedef struct {
	twl603x_type chip_type;
	float chip_revision;
	float eprom_revision;
	int vsel_len; /* width of vsel command (in bits) */
	long int vstep; /* voltage step, in microvolts */
	long int voffset[3]; /* voltage offset (per rail), in microvolts */
	unsigned long smps_voltage_uv[5];
} t_twl603x_data;


static t_twl603x_data twl603x_data = {
	.chip_type = TWL603X_TYPE_MAX,
	.chip_revision = -1.0,
	.eprom_revision = -1.0,
	.vsel_len = TWL6030_VSEL_LEN,
	.vstep = TWL6030_VSTEP_UV,
	.voffset = {-1.0, -1.0, -1.0},
	.smps_voltage_uv = {
		TWL6030_SMPS_VOLTAGE0_UV,
		TWL6030_SMPS_VOLTAGE1_UV,
		TWL6030_SMPS_VOLTAGE2_UV,
		TWL6030_SMPS_VOLTAGE3_UV,
		TWL6030_SMPS_VOLTAGE4_UV} };


typedef struct {
	int ctrl;
	int tstep;
	int force;
	int voltage;
} twl6035_smps_registers;


static const twl6035_smps_registers twl035_smps12 = {
	.ctrl = 0x20,
	.tstep = 0x21,
	.force = 0x22,
	.voltage = 0x23};

static const twl6035_smps_registers twl035_smps3 = {
	.ctrl = 0x24,
	.tstep = -1,
	.force = -1,
	.voltage = 0x27};

static const twl6035_smps_registers twl035_smps45 = {
	.ctrl = 0x28,
	.tstep = 0x29,
	.force = 0x2A,
	.voltage = 0x2B};

static const twl6035_smps_registers twl035_smps6 = {
	.ctrl = 0x2C,
	.tstep = 0x2D,
	.force = 0x2E,
	.voltage = 0x2F};

static const twl6035_smps_registers twl035_smps7 = {
	.ctrl = 0x30,
	.tstep = -1,
	.force = -1,
	.voltage = 0x33};

static const twl6035_smps_registers twl035_smps8 = {
	.ctrl = 0x34,
	.tstep = 0x35,
	.force = 0x36,
	.voltage = 0x37};


static const twl6035_smps_registers twl035_smps9 = {
	.ctrl = 0x38,
	.tstep = -1,
	.force = -1,
	.voltage = 0x3B};

static const twl6035_smps_registers twl035_smps10 = {
	.ctrl = 0x3C,
	.tstep = -1,
	.force = -1,
	.voltage = -1};

static const twl6035_smps_registers *twl6035_smps_vdd54xx_mpu = &twl035_smps12;
static const twl6035_smps_registers *twl6035_smps_vdd54xx_mm = &twl035_smps45;
static const twl6035_smps_registers *twl6035_smps_vdd54xx_core = &twl035_smps8;
static const twl6035_smps_registers **twl6035_smps_vdd54xx[3] = {
	(const twl6035_smps_registers **) &twl6035_smps_vdd54xx_mpu,
	(const twl6035_smps_registers **) &twl6035_smps_vdd54xx_mm,
	(const twl6035_smps_registers **) &twl6035_smps_vdd54xx_core};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl603x_is_twl6030
 * @BRIEF		return 1 if PMIC chip is TWL6030, 0 otherwise.
 * @RETURNS		1 PMIC chip is TWL6030
 *			0 otherwise
 * @DESCRIPTION		return 1 if PMIC chip is TWL6030, 0 otherwise.
 *//*------------------------------------------------------------------------ */
unsigned short twl603x_is_twl6030(void)
{
	int ret;
	unsigned int val1, val2;

	if (cpu_get() == DRA_75X)
		return 0;

	if (twl603x_data.chip_type != TWL603X_TYPE_MAX) {
		dprintf("%s(): flag=%d\n", __func__,
			(twl603x_data.chip_type == TWL6030));
		return twl603x_data.chip_type == TWL6030;
	}

	ret = i2cget(TWL6030_I2C_BUS, 0x49, 0x02, &val2);
	if (ret != 0)
		goto twl603x_is_twl6030_end;

	ret = i2cget(TWL6030_I2C_BUS, 0x49, 0x03, &val1);
	if (ret != 0)
		goto twl603x_is_twl6030_end;

	if ((val1 == 0xC0) && (val2 == 0x30))
		twl603x_data.chip_type = TWL6030;

twl603x_is_twl6030_end:
	dprintf("%s(): val1=0x%02X val2=0x%02X flag=%d\n",
		__func__, val1, val2, (twl603x_data.chip_type == TWL6030));
	return twl603x_data.chip_type == TWL6030;

}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl603x_is_twl6032
 * @BRIEF		return 1 if PMIC chip is TWL6032, 0 otherwise.
 * @RETURNS		1 PMIC chip is TWL6032
 *			0 otherwise
 * @DESCRIPTION		return 1 if PMIC chip is TWL6032, 0 otherwise.
 *//*------------------------------------------------------------------------ */
unsigned short twl603x_is_twl6032(void)
{
	int ret;
	unsigned int val1, val2;

	if (cpu_get() == DRA_75X)
		return 0;

	if (twl603x_data.chip_type != TWL603X_TYPE_MAX) {
		dprintf("%s(): flag=%d\n", __func__,
			(twl603x_data.chip_type == TWL6032));
		return twl603x_data.chip_type == TWL6032;
	}

	ret = i2cget(TWL6030_I2C_BUS, 0x49, 0x02, &val2);
	if (ret != 0)
		goto twl603x_is_twl6032_end;

	ret = i2cget(TWL6030_I2C_BUS, 0x49, 0x03, &val1);
	if (ret != 0)
		goto twl603x_is_twl6032_end;

	if ((val1 == 0xC0) && (val2 == 0x32))
		twl603x_data.chip_type = TWL6032;

twl603x_is_twl6032_end:
	dprintf("%s(): val1=0x%02X val2=0x%02X flag=%d\n",
		__func__, val1, val2, (twl603x_data.chip_type == TWL6032));
	return twl603x_data.chip_type == TWL6032;

}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl603x_is_twl6034
 * @BRIEF		return 1 if PMIC chip is TWL6034, 0 otherwise.
 * @RETURNS		1 PMIC chip is TWL6034
 *			0 otherwise
 * @DESCRIPTION		return 1 if PMIC chip is TWL6034, 0 otherwise.
 *//*------------------------------------------------------------------------ */
unsigned short twl603x_is_twl6034(void)
{
	int ret;
	unsigned int val1, val2;

	if (cpu_get() == DRA_75X)
		return 0;

	if (twl603x_data.chip_type != TWL603X_TYPE_MAX) {
		dprintf("%s(): flag=%d\n", __func__,
			(twl603x_data.chip_type == TWL6034));
		return twl603x_data.chip_type == TWL6034;
	}

	ret = i2cget(TWL6030_I2C_BUS, 0x49, 0x02, &val2);
	if (ret != 0)
		goto twl603x_is_twl6034_end;

	ret = i2cget(TWL6030_I2C_BUS, 0x49, 0x03, &val1);
	if (ret != 0)
		goto twl603x_is_twl6034_end;

	if ((val1 == 0x00) && (val2 == 0x00))
		twl603x_data.chip_type = TWL6034;

twl603x_is_twl6034_end:
	dprintf("%s(): val1=0x%02X val2=0x%02X flag=%d\n",
		__func__, val1, val2, (twl603x_data.chip_type == TWL6034));
	return twl603x_data.chip_type == TWL6034;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl603x_is_twl6035
 * @BRIEF		return 1 if PMIC chip is TWL6035, 0 otherwise.
 * @RETURNS		1 PMIC chip is TWL6035
 *			0 otherwise
 * @DESCRIPTION		return 1 if PMIC chip is TWL6035, 0 otherwise.
 *//*------------------------------------------------------------------------ */
unsigned short twl603x_is_twl6035(void)
{
#if 0 /* FIXME: implement true detection when ID data available */
	int ret;
	unsigned int val1, val2;

	if (twl603x_data.chip_type != TWL603X_TYPE_MAX) {
		dprintf("%s(): flag=%d\n", __func__,
			(twl603x_data.chip_type == TWL6035));
		return twl603x_data.chip_type == TWL6035;
	}

	ret = i2cget(TWL6030_I2C_BUS, 0x49, 0x02, &val2);
	if (ret != 0)
		goto twl603x_is_twl6035_end;

	ret = i2cget(TWL6030_I2C_BUS, 0x49, 0x03, &val1);
	if (ret != 0)
		goto twl603x_is_twl6035_end;
	if ((val1 == 0xC0) && (val2 == 0x35))
		twl603x_data.chip_type = TWL6035;

twl603x_is_twl6035_end:
	dprintf("%s(): val1=0x%02X val2=0x%02X flag=%d\n",
		__func__, val1, val2, (twl603x_data.chip_type == TWL6035));
	return twl603x_data.chip_type == TWL6035;
#else
	/* FIXME: implement true detection when ID data available */
	if (cpu_is_omap54xx())
		return 1;
	else
		return 0;
#endif
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl603x_chip_revision_get
 * @BRIEF		return TWL6030 chip revision
 * @RETURNS		> 0.0 valid TWL6030 chip revision
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_UNEXPECTED
 * @DESCRIPTION		return TWL6030 chip revision
 *//*------------------------------------------------------------------------ */
float twl603x_chip_revision_get(void)
{
	int ret;
	unsigned int rev;

	if (twl603x_data.chip_revision > 0)
		goto twl603x_chip_revision_get_end;

	ret = i2cget(TWL6030_I2C_BUS, 0x4A, 0x87, &rev);
	if (ret != 0) {
		fprintf(stderr, "%s(): could not read register! (%d)\n",
			__func__, ret);
		twl603x_data.chip_revision = (float) OMAPCONF_ERR_NOT_AVAILABLE;
		goto twl603x_chip_revision_get_end;
	}
	dprintf("%s(): rev=%u\n", __func__, rev);
	switch (rev) {
	case 0x0:
		twl603x_data.chip_revision = 1.0;
		break;
	case 0x01:
		if (twl603x_data.chip_type == TWL6032)
			twl603x_data.chip_revision = 1.1;
		else
			twl603x_data.chip_revision = 2.0;
		break;
	case 0x02:
		twl603x_data.chip_revision = 2.1;
		break;
	default:
		twl603x_data.chip_revision = (float) OMAPCONF_ERR_UNEXPECTED;
	}

twl603x_chip_revision_get_end:
	dprintf("%s(): chip_revision = %f\n", __func__,
		twl603x_data.chip_revision);
	return twl603x_data.chip_revision;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl603x_eprom_revision_get
 * @BRIEF		return TWL603x EPROM revision
 * @RETURNS		>0 .0 valid TWL6030 EPROM revision
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @DESCRIPTION		return TWL603x EPROM revision
 *//*------------------------------------------------------------------------ */
float twl603x_eprom_revision_get(void)
{
	int ret;
	unsigned int rev;

	if (twl603x_data.eprom_revision > 0)
		goto twl603x_eprom_revision_get_end;

	ret = i2cget(TWL6030_I2C_BUS, 0x4A, 0xDF, &rev);
	if (ret != 0) {
		fprintf(stderr, "%s(): could not read register! (%d)\n",
			__func__, ret);
		twl603x_data.eprom_revision =
			(float) OMAPCONF_ERR_NOT_AVAILABLE;
		goto twl603x_eprom_revision_get_end;
	}
	dprintf("%s(): rev=%u\n", __func__, rev);
	twl603x_data.eprom_revision = (float) (rev);

twl603x_eprom_revision_get_end:
	dprintf("%s(): eprom_revision = %f\n", __func__,
		twl603x_data.eprom_revision);
	return twl603x_data.eprom_revision;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl603x_smps_offset_get
 * @BRIEF		return SMPS regulator offset for a given rail
 * @RETURNS		>0 voltage offset in microvolts
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		vdd_id: voltage rail
 * @DESCRIPTION		return SMPS regulator offset for a given rail
 *//*------------------------------------------------------------------------ */
unsigned long twl603x_smps_offset_get(voltdm44xx_id vdd_id)
{
	int ret;
	unsigned int val;
	char product_name[256];

	if (twl603x_is_twl6035())
		return TWL6035_VOFFSET_UV;

	if (twl603x_data.voffset[vdd_id - 1] >= 0)
		goto twl603x_smps_offset_get_end;

	/*
	 * TWL6030:
	 * Starting ES2.x, Phoenix PMIC may use 709mV offset instead of 608mV
	 * depending on setting: OFFSET=1: 709mV, OFFSET=0: 608mV.
	 */
	if (twl603x_is_twl6030() && twl603x_chip_revision_get() == 1.0) {
		dprintf("%s(%u): TWL60ES1 => TWL6030_VOFFSET_0_UV\n",
			__func__, vdd_id);
		twl603x_data.voffset[vdd_id - 1] = TWL6030_VOFFSET_0_UV;
		goto twl603x_smps_offset_get_end;
	}

	ret = i2cget(TWL6030_I2C_BUS, 0x48, 0xE0, &val);
	if (ret != 0) {
		fprintf(stderr, "%s(%u): could not read register! (%d)\n",
			__func__, vdd_id, ret);
		twl603x_data.voffset[vdd_id - 1] = TWL6030_VOFFSET_1_UV;
		goto twl603x_smps_offset_get_end;
	}
	dprintf("%s(%u): val=0x%02X\n", __func__, vdd_id, val);

	switch (vdd_id) {
	case OMAP4_VDD_MPU:
		if (cpu_is_omap4460()) {
			android_product_name_get(product_name);
			if (strstr(product_name, "Kindle") == NULL)
				fprintf(stderr,
					"%s(%u): invalid vdd_id! omap4460 uses TPS62361 for VDD_MPU\n",
					__func__, vdd_id);
		}
		val &= 0x08;
		break;
	case OMAP4_VDD_IVA:
		if (cpu_is_omap4470())
			val &= 0x02;
		else
			val &= 0x10;
		break;
	case OMAP4_VDD_CORE:
		if (cpu_is_omap4460())
			val &= 0x08;
		else if (cpu_is_omap4470())
			val &= 0x10;
		else
			val &= 0x20;
		break;
	default:
		fprintf(stderr, "%s(%u): invalid vdd_id!\n", __func__, vdd_id);
		return TWL6030_VOFFSET_1_UV;
	}

	if (val != 0)
		twl603x_data.voffset[vdd_id - 1] = TWL6030_VOFFSET_1_UV;
	else
		twl603x_data.voffset[vdd_id - 1] = TWL6030_VOFFSET_0_UV;

twl603x_smps_offset_get_end:
	dprintf("%s(%u): voffset=%lduV\n", __func__,
		vdd_id, twl603x_data.voffset[vdd_id - 1]);
	return twl603x_data.voffset[vdd_id - 1];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl603x_smps_step_get
 * @BRIEF		return SMPS regulator voltage step for a given rail
 *			(in microvolts)
 * @RETURNS		voltage step in microvolts
 * @DESCRIPTION		return SMPS regulator voltage step for a given rail
 *			(in microvolts)
 *//*------------------------------------------------------------------------ */
long twl603x_smps_step_get(void)
{
	if (twl603x_is_twl6035())
		return TWL6035_VSTEP_UV;

	return twl603x_data.vstep;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl603x_vsel_len_get
 * @BRIEF		return the size of the vsel command
 * @RETURNS		SMPS regulator size of the vsel command
 * @DESCRIPTION		return the size of the vsel command
 *//*------------------------------------------------------------------------ */
int twl603x_vsel_len_get(void)
{
	if (twl603x_is_twl6035())
		return TWL6035_VSEL_LEN;

	return twl603x_data.vsel_len;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl603x_uv_to_vsel
 * @BRIEF		for a given rail, convert voltage in microvolts into
 *			vsel command. Take into account voltage offset.
 * @RETURNS		SMPS vsel command corresponding to uv
 * @param[in]		vdd_id: voltage rail
 * @param[in]		uv: voltage to be converted (in microvolts)
 * @DESCRIPTION		for a given rail, convert voltage in microvolts into
 *			vsel command. Take into account voltage offset.
 *//*------------------------------------------------------------------------ */
unsigned char twl603x_uv_to_vsel(unsigned int vdd_id, unsigned long uv)
{
	unsigned long smps_offset;
	unsigned char vsel, range;

	if (!twl603x_is_twl6035()) {
		smps_offset = twl603x_smps_offset_get(vdd_id);

		if (uv < smps_offset)
			vsel = 0;
		else if (uv == smps_offset)
			vsel = 0x01;
		else if (uv >= twl603x_data.smps_voltage_uv[4])
			vsel = 0x3E;
		else if (uv == twl603x_data.smps_voltage_uv[3])
			vsel = 0x3D;
		else if (uv == twl603x_data.smps_voltage_uv[2])
			vsel = 0x3C;
		else if (uv == twl603x_data.smps_voltage_uv[1])
			vsel = 0x3B;
		else if (uv == twl603x_data.smps_voltage_uv[0])
			vsel = 0x3A;
		else
			vsel = DIV_ROUND_UP(uv - smps_offset,
				twl603x_data.vstep) + 1;
	} else {
		if (uv == 0) {
			range = 0;
			vsel = 0;
		} else if (uv <= TWL6035_SMPS_LOW_RANGE_UVMIN) {
			range = 0;
			vsel = 0x01;
		} else if (uv <= TWL6035_SMPS_LOW_RANGE_UVMAX) {
			range = 0;
			vsel = 6 + DIV_ROUND_UP(uv - TWL6035_VOFFSET_UV,
				TWL6035_VSTEP_UV);
		} else if (uv <= 3300000) {
			range = 1;
			vsel = 6 + DIV_ROUND_UP(uv - (TWL6035_VOFFSET_UV * 2),
				2 * TWL6035_VSTEP_UV);
		} else { /* > 3.3V */
			range = 1;
			vsel = 0x79;
		}

		vsel = vsel | (range << 7);
	}

	dprintf("%s(%d, %lduV)=0x%02X\n", __func__, vdd_id, uv, vsel);
	return vsel;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl603x_vsel_to_uv
 * @BRIEF		for a given rail, convert SMPS vsel command into voltage
 *			in microvolts. Take into account SMPS voltage offset.
 * @RETURNS		voltage in microvolts corresponding to SMPS vsel command
 * @param[in]		vdd_id: voltage rail
 * @param[in]		vsel: SMPS vsel command (in microvolts)
 * @DESCRIPTION		for a given rail, convert SMPS vsel command into voltage
 *			in microvolts. Take into account SMPS voltage offset.
 *//*------------------------------------------------------------------------ */
unsigned long twl603x_vsel_to_uv(unsigned int vdd_id, unsigned char vsel)
{
	unsigned long smps_offset, uv;
	unsigned int range;

	if (!twl603x_is_twl6035()) {
		if (vsel == 0) {
			uv = 0;
		} else if (vsel > 0x3E) {
			fprintf(stderr, "%s(): warning vsel (0x%02X) "
				"is reserved value, use max (0x3E) instead!\n",
				__func__, vsel);
			vsel = 0x3E;
		}

		smps_offset = twl603x_smps_offset_get(vdd_id);

		if (vsel >= 0x3A)
			uv = twl603x_data.smps_voltage_uv[vsel - 0x3A];
		else
			uv =  smps_offset + ((vsel - 1) * twl603x_data.vstep);
	} else {
		/* VSEL = 7-bit + range (MSB) */
		range = extract_bit(vsel, 7);
		vsel = extract_bitfield(vsel, 0, 7);

		if (vsel == 0) {
			uv = 0;
		} else if (vsel <= 0x06) {
			uv = TWL6035_VOFFSET_UV;
		} else if (vsel >= 0x79) {
			uv = 1650000;
		} else {
			uv = TWL6035_VOFFSET_UV +
				(TWL6035_VSTEP_UV * (vsel - 6));
		}

		/* Apply range multiplier */
		uv = uv << range;
	}

	dprintf("%s(%d, %d (0x%02X))=%lduV\n", __func__,
		vdd_id, vsel, vsel, uv);
	return uv;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl603x_vsel_to_volt
 * @BRIEF		for a given rail, convert SMPS vsel command into voltage
 *			(in VOLTS). Take into account SMPS voltage offset.
 * @RETURNS		voltage in VOLTS corresponding to SMPS vsel command
 * @param[in]		vdd_id: voltage rail
 * @param[in]		vsel: SMPS vsel command (in microvolts)
 * @DESCRIPTION		for a given rail, convert SMPS vsel command into voltage
 *			(in VOLTS). Take into account SMPS voltage offset.
 *//*------------------------------------------------------------------------ */
double twl603x_vsel_to_volt(unsigned int vdd_id, unsigned char vsel)
{
	double volt;

	volt = (double) twl603x_vsel_to_uv(vdd_id, vsel);
	volt /= (double) 1000000.0;

	dprintf("%s(%u, 0x%X) = %lfV\n", __func__, vdd_id, vsel, volt);
	return volt;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl603x_vsel_get
 * @BRIEF		return vsel-encoded voltage of a given SMPS voltage rail
 * @RETURNS		VSEL-encoded voltage (8-bit, >= 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		vdd_id: voltage domain ID
 * @DESCRIPTION		return vsel-encoded voltage of a given SMPS voltage rail
 *			NB: not supported by TWL6030/TWL6032.
 *//*------------------------------------------------------------------------ */
int twl603x_vsel_get(unsigned int vdd_id)
{
	int ret;
	unsigned int val, vsel_addr, vsel, range;
	const twl6035_smps_registers **vdd_smps_regs;
	const twl6035_smps_registers *smps_regs;

	if (!twl603x_is_twl6035())
		return OMAPCONF_ERR_CPU;
	CHECK_ARG_LESS_THAN(vdd_id, 3, OMAPCONF_ERR_ARG);

	/* Retrive SMPS registers addresses */
	vdd_smps_regs = twl6035_smps_vdd54xx[vdd_id];
	if (vdd_smps_regs == NULL)
		return OMAPCONF_ERR_INTERNAL;
	smps_regs = *vdd_smps_regs;
	if (smps_regs == NULL)
		return OMAPCONF_ERR_INTERNAL;

	dprintf("%s(): vdd_id=%u  ADDR: ctrl=0x%02X tstep=0x%02X force=0x%02X "
		"voltage=0x%02X\n", __func__, vdd_id, smps_regs->ctrl,
		smps_regs->tstep, smps_regs->force, smps_regs->voltage);

	/* Check SMPS Status */
	/* FIXME: create dedicated API */
	if (smps_regs->ctrl == -1) {
		dprintf("%s(): SMPSxx_CTRL addr=-1!!!\n", __func__);
		return OMAPCONF_ERR_INTERNAL;
	}
	ret = i2cget(TWL6035_I2C_BUS, TWL6035_ID1_ADDR,
		smps_regs->ctrl, &val);
	if (ret != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	dprintf("%s(): SMPSxx_CTRL=0x%02X\n", __func__, val);
	if (extract_bitfield(val, 4, 2) == 0) {
		dprintf("(%s(): warning SMPS is OFF\n", __func__);
		return 0;
	}

	/* Check SMPS voltage controlled by registers, not resource pins */
	/* FIXME: create dedicated API */
	if (extract_bit(val, 6) == 1) {
		dprintf("%s(): SMPS voltage controlled by resource pins\n",
			__func__);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	/*
	 * Retrieve if voltage is controlled via
	 * SMPSxx_FORCE.VSEL or SMPSxx_VOLTAGE.VSEL
	 */
	if (smps_regs->force == -1) {
		dprintf("%s(): SMPSxx_FORCE register does not exist, "
			"use SMPSxx_VOLTAGE register.\n", __func__);
		vsel_addr = smps_regs->voltage;
	} else {
		ret = i2cget(TWL6035_I2C_BUS, TWL6035_ID1_ADDR,
			smps_regs->force, &val);
		if (ret != 0)
			return OMAPCONF_ERR_REG_ACCESS;
		dprintf("%s(): SMPSxx_FORCE=0x%02X\n", __func__, val);
		if (extract_bit(val, 7) == 1) {
			dprintf("%s(): CMD=1 => use SMPSxx_VOLTAGE register.\n",
				__func__);
			vsel_addr = smps_regs->voltage;
		} else {
			dprintf("%s(): CMD=0 => use SMPSxx_FORCE register.\n",
				__func__);
			vsel_addr = smps_regs->force;
		}
	}

	/* Retrieve VSEL (7-bit LSB) from relevant register */
	if (vsel_addr == (unsigned int) smps_regs->voltage) {
		if (smps_regs->voltage == -1) {
			dprintf("%s(): SMPSxx_VOLTAGE addr=-1!!!\n", __func__);
			return OMAPCONF_ERR_INTERNAL;
		}
		ret = i2cget(TWL6035_I2C_BUS, TWL6035_ID1_ADDR,
			smps_regs->voltage, &val);
		if (ret != 0)
			return OMAPCONF_ERR_REG_ACCESS;
		dprintf("%s(): SMPSxx_VOLTAGE=0x%02X\n", __func__, val);
	}
	vsel = extract_bitfield(val, 0, 7);
	dprintf("%s(): SMPSxx_VOLTAGE=0x%02X SMPSxx_VOLTAGE.VSEL=0x%02X\n",
		__func__, val, vsel);

	/* Retrieve VSEL range from SMPSxx_VOLTAGE register (bit 7) */
	if (vsel_addr != (unsigned int) smps_regs->voltage) {
		if (smps_regs->voltage == -1) {
			dprintf("%s(): SMPSxx_VOLTAGE addr=-1!!!\n", __func__);
			return OMAPCONF_ERR_INTERNAL;
		}
		ret = i2cget(TWL6035_I2C_BUS, TWL6035_ID1_ADDR,
			smps_regs->voltage, &val);
		if (ret != 0)
			return OMAPCONF_ERR_REG_ACCESS;
	}
	range = extract_bit(val, 7);
	dprintf("%s(): SMPSxx_VOLTAGE=0x%02X SMPSxx_VOLTAGE.RANGE=%u\n",
		__func__, val, range);

	/* Return VSEL (7-bit LSB), including range (MSB) */
	vsel = vsel | (range << 7);
	dprintf("%s(): vsel=0x%02X\n", __func__, vsel);
	return vsel;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl603x_uvoltage_get
 * @BRIEF		return voltage of a given SMPS voltage rail.
 * @RETURNS		voltage of a given SMPS voltage rail, in micro-volt.
 * @param[in]		vdd_id: voltage domain ID
 * @DESCRIPTION		return voltage of a given SMPS voltage rail,
 *			in millivolt.
 *			NB: not supported by TWL6030/TWL6032.
 *//*------------------------------------------------------------------------ */
unsigned long twl603x_uvoltage_get(unsigned int vdd_id)
{
	int vsel;

	vsel = twl603x_vsel_get(vdd_id);
	if (vsel < 0)
		return 0;

	return twl603x_vsel_to_uv(vdd_id, vsel);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl603x_voltage_get
 * @BRIEF		return voltage of a given SMPS voltage rail.
 * @RETURNS		voltage of a given SMPS voltage rail, in volt.
 * @param[in]		vdd_id: voltage domain ID
 * @DESCRIPTION		return voltage of a given SMPS voltage rail,
 *			in volt.
 *			NB: not supported by TWL6030/TWL6032.
 *//*------------------------------------------------------------------------ */
double twl603x_voltage_get(unsigned int vdd_id)
{
	int vsel;

	vsel = twl603x_vsel_get(vdd_id);
	if (vsel < 0)
		return 0;

	return (double) twl603x_vsel_to_uv(vdd_id, vsel) / 1000000.0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl603x_uvoltage_set
 * @BRIEF		set voltage of a given SMPS voltage rail.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		vdd_id: voltage domain ID
 * @param[in]		uv: voltage to be set (in micro-volt)
 * @DESCRIPTION		set voltage of a given SMPS voltage rail, in micro-volt.
 *			NB: not supported by TWL6030/TWL6032.
 *//*------------------------------------------------------------------------ */
int twl603x_uvoltage_set(unsigned int vdd_id, unsigned long uv)
{
	int ret;
	unsigned int val;
	unsigned char vsel;
	const twl6035_smps_registers **vdd_smps_regs;
	const twl6035_smps_registers *smps_regs;

	if (!twl603x_is_twl6035())
		return OMAPCONF_ERR_CPU;
	CHECK_ARG_LESS_THAN(vdd_id, 3, OMAPCONF_ERR_ARG);

	/* Retrive SMPS registers addresses */
	vdd_smps_regs = twl6035_smps_vdd54xx[vdd_id];
	if (vdd_smps_regs == NULL)
		return OMAPCONF_ERR_INTERNAL;
	smps_regs = *vdd_smps_regs;
	if (smps_regs == NULL)
		return OMAPCONF_ERR_INTERNAL;

	dprintf("%s(): vdd_id=%u  ADDR: ctrl=0x%02X tstep=0x%02X force=0x%02X "
		"voltage=0x%02X\n", __func__, vdd_id, smps_regs->ctrl,
		smps_regs->tstep, smps_regs->force, smps_regs->voltage);

	/* Check SMPS Status */
	/* FIXME: create dedicated API */
	if (smps_regs->ctrl == -1) {
		dprintf("%s(): SMPSxx_CTRL addr=-1!!!\n", __func__);
		return OMAPCONF_ERR_INTERNAL;
	}
	ret = i2cget(TWL6035_I2C_BUS, TWL6035_ID1_ADDR,
		smps_regs->ctrl, &val);
	if (ret != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	dprintf("%s(): SMPSxx_CTRL=0x%02X\n", __func__, val);
	if (extract_bitfield(val, 4, 2) == 0) {
		dprintf("(%s(): SMPS is OFF\n", __func__);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	/* Make sure SMPSxx_CTRL.ROOF_FLOOR_EN=0 */
	/* FIXME: create dedicated API */
	if (extract_bit(val, 6) == 1) {
		dprintf("%s(): SMPS voltage controlled by resource pins, "
			"clearing ROOF_FLOOR_EN bit.\n", __func__);
		/* Clear ROOF_FLOOR_EN bit (6) */
		val = val & 0xBF;
		ret = i2cset(TWL6035_I2C_BUS, TWL6035_ID1_ADDR,
			smps_regs->ctrl, (unsigned int) val);
		if (ret != 0)
			return OMAPCONF_ERR_REG_ACCESS;
		dprintf("%s(): SMPS voltage now controlled by "
			"SMPS12_FORCE.CMD bit.\n", __func__);
	} else {
		dprintf("%s(): SMPS voltage controlled by "
			"SMPS12_FORCE.CMD bit.\n", __func__);
	}

	/* Convert voltage to VSEL */
	vsel = twl603x_uv_to_vsel(vdd_id, uv);
	dprintf("%s(): uv=%lu vsel=0x%02X\n", __func__, uv, vsel);

	/* Write VSEL to SMPSxx_VOLTAGE */
	ret = i2cset(TWL6035_I2C_BUS, TWL6035_ID1_ADDR,
			smps_regs->voltage, (unsigned int) vsel);
	if (ret != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	/*
	 * Try to switch voltage control to SMPSxx_FORCE register (if exists)
	 * so that voltage will not be overriden by kernel during
	 * DVFS, AVS or power transition.
	 */
	if (smps_regs->force != -1) {
		dprintf("%s(): SMPSxx_FORCE exists, switching control.\n",
			__func__);
		/* Clear bit 7 (CMD) */
		val = vsel & 0x7F;
		ret = i2cset(TWL6035_I2C_BUS, TWL6035_ID1_ADDR,
			smps_regs->force, (unsigned int) val);
	} else {
		dprintf("%s(): SMPSxx_FORCE does not exist.\n", __func__);
		ret = 0;
	}

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl603x_main
 * @BRIEF		TWL603x menu
 *			### DEPRECATED, DO NOT USE ANYMORE ###
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		TWL603x menu
 *			### DEPRECATED, DO NOT USE ANYMORE ###
 *//*------------------------------------------------------------------------ */
int twl603x_main(int argc, char *argv[])
{
	int ret;

	if (!cpu_is_omap44xx() && !cpu_is_omap54xx())
		return OMAPCONF_ERR_CPU;

	if (argc == 2) {
		static unsigned char init_done = 0;
		if (!init_done) {
			twl603x_init_regtable();
			init_done = 1;
		}

		if (strcmp(argv[1], "dump") == 0)
			ret = twl603x_dumpregs(stdout);
		else if (cpu_is_omap54xx())
			ret = OMAPCONF_ERR_ARG;
		else if (strcmp(argv[1], "cfg") == 0)
			ret = twl603x_config(stdout);
		else if (strcmp(argv[1], "ldocfg") == 0)
			ret = twl603x_config_ldo(stdout);
		else if (strcmp(argv[1], "smpscfg") == 0)
			ret = twl603x_config_smps(stdout);
		else if (strcmp(argv[1], "rescfg") == 0)
			ret = twl603x_config_resources(stdout);
		else if (strcmp(argv[1], "devpwrgrpstat") == 0)
			ret = twl603x_config_devpwrgrp_status(stdout);
		else if (strcmp(argv[1], "reset") == 0)
			ret = twl603x_reset(stdout);
		else
			ret = OMAPCONF_ERR_ARG;

	} else if (argc == 4) {
		if (strcmp(argv[1], "setpwrgrp") == 0) {
			ret = twl603x_pwrgrp_set(stdout, argv[2], argv[3]);
		} else {
			ret = OMAPCONF_ERR_ARG;
		}
	} else {
		ret = OMAPCONF_ERR_ARG;
	}

	if (ret == OMAPCONF_ERR_ARG)
		help(HELP_PMIC);
	return ret;
}
