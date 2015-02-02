/*
 *
 * @Component			OMAPCONF
 * @Filename			tps659038.c
 * @Description			DRA7 TPS 659038 (SMPS Voltage Regulator) Library
 * @Author			Jin Zheng (j-zheng@ti.com)
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


#include <tps659038.h>
#include <lib.h>
#include <i2c-tools.h>
#include <mem.h>
#include <cpuinfo.h>
#include <prm_dra7xx.h>


/* #define TPS659038_DEBUG */
#ifdef TPS659038_DEBUG
#include <stdio.h>
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


typedef struct {
	int ctrl;
	int tstep;
	int force;
	int voltage;
} tps659038_smps_registers;


static const tps659038_smps_registers tps659038_smps12 = {
	.ctrl = 0x20,
	.tstep = -1,
	.force = 0x22,
	.voltage = 0x23};

static const tps659038_smps_registers tps659038_smps3 = {
	.ctrl = 0x24,
	.tstep = -1,
	.force = -1,
	.voltage = 0x27};

static const tps659038_smps_registers tps659038_smps45 = {
	.ctrl = 0x28,
	.tstep = -1,
	.force = 0x2A,
	.voltage = 0x2B};

static const tps659038_smps_registers tps659038_smps6 = {
	.ctrl = 0x2C,
	.tstep = -1,
	.force = 0x2E,
	.voltage = 0x2F};

static const tps659038_smps_registers tps659038_smps7 = {
	.ctrl = 0x30,
	.tstep = -1,
	.force = -1,
	.voltage = 0x33};

static const tps659038_smps_registers tps659038_smps8 = {
	.ctrl = 0x34,
	.tstep = -1,
	.force = 0x36,
	.voltage = 0x37};


static const tps659038_smps_registers tps659038_smps9 = {
	.ctrl = 0x38,
	.tstep = -1,
	.force = -1,
	.voltage = 0x3B};


/* TPS65917 data */
static const tps659038_smps_registers tps65917_smps1 = {
	.ctrl = 0x20,
	.tstep = -1,
	.force = 0x22,
	.voltage = 0x23};

static const tps659038_smps_registers tps65917_smps2 = {
	.ctrl = 0x24,
	.tstep = -1,
	.force = 0x26,
	.voltage = 0x27};

static const tps659038_smps_registers tps65917_smps3 = {
	.ctrl = 0x2C,
	.tstep = -1,
	.force = 0x2E,
	.voltage = 0x2F};

static const tps659038_smps_registers tps65917_smps4 = {
	.ctrl = 0x30,
	.tstep = -1,
	.force = -1,
	.voltage = 0x33};

static const tps659038_smps_registers tps65917_smps5 = {
	.ctrl = 0x38,
	.tstep = -1,
	.force = -1,
	.voltage = 0x3B};

static const tps659038_smps_registers *tps659038_smps_vdd_dra7xx_mpu = &tps659038_smps12;
static const tps659038_smps_registers *tps659038_smps_vdd_dra7xx_iva = &tps659038_smps8;
static const tps659038_smps_registers *tps659038_smps_vdd_dra7xx_core = &tps659038_smps7;
static const tps659038_smps_registers *tps659038_smps_vdd_dra7xx_gpu = &tps659038_smps6;
static const tps659038_smps_registers *tps659038_smps_vdd_dra7xx_dspeve = &tps659038_smps45;

static const tps659038_smps_registers **tps659038_smps_vdd_dra7xx[5] = {
	(const tps659038_smps_registers **) &tps659038_smps_vdd_dra7xx_mpu,
	(const tps659038_smps_registers **) &tps659038_smps_vdd_dra7xx_iva,
	(const tps659038_smps_registers **) &tps659038_smps_vdd_dra7xx_core,
	(const tps659038_smps_registers **) &tps659038_smps_vdd_dra7xx_gpu,
	(const tps659038_smps_registers **) &tps659038_smps_vdd_dra7xx_dspeve};

static float chip_revision = -1.0;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tps659038_is_present
 * @BRIEF		return 1 if TPS659038 is present on this platform,
 *			0 otherwise
 * @RETURNS		1 if TPS659038 chip is found
 *			0 otherwise
 * @DESCRIPTION		return 1 if TPS659038 is present on this platform,
 *			0 otherwise
 *//*------------------------------------------------------------------------ */
unsigned short int tps659038_is_present(void)
{
	int ret;
	unsigned int id_lsb, id_msb;
	unsigned short present = 0;

	switch (cpu_get()) {
	case DRA_75X:
	case DRA_72X:
		ret = i2cget(TPS659038_I2C_BUS, TPS659038_ID1_ADDR,
			TPS659038_PRODUCT_ID_LSB, &id_lsb);
		if (ret != 0)
			return 0;

		ret = i2cget(TPS659038_I2C_BUS, TPS659038_ID1_ADDR,
			TPS659038_PRODUCT_ID_MSB, &id_msb);
		if (ret != 0)
			return 0;

		if ((id_lsb == 0x35 && id_msb == 0xc0) ||
			   (id_lsb == 0x39 && id_msb == 0x90))
			present = 1;
		/* it is a TPS 65917 PMIC. fixup structure pointers */
		else if (id_lsb == 0x17 && id_msb == 0x09) {
			present = 1;
			tps659038_smps_vdd_dra7xx_mpu = &tps65917_smps1;
			tps659038_smps_vdd_dra7xx_iva = &tps65917_smps3;
			tps659038_smps_vdd_dra7xx_core = &tps65917_smps2;
			tps659038_smps_vdd_dra7xx_gpu = &tps65917_smps3;
			tps659038_smps_vdd_dra7xx_dspeve = &tps65917_smps3;


			tps659038_smps_vdd_dra7xx[0] = (const tps659038_smps_registers **) &tps659038_smps_vdd_dra7xx_mpu;
			tps659038_smps_vdd_dra7xx[1] = (const tps659038_smps_registers **) &tps659038_smps_vdd_dra7xx_iva;
			tps659038_smps_vdd_dra7xx[2] = (const tps659038_smps_registers **) &tps659038_smps_vdd_dra7xx_core;
			tps659038_smps_vdd_dra7xx[3] = (const tps659038_smps_registers **) &tps659038_smps_vdd_dra7xx_gpu;
			tps659038_smps_vdd_dra7xx[4] = (const tps659038_smps_registers **) &tps659038_smps_vdd_dra7xx_dspeve;

		}
		break;

	default:
		break;
	}

	dprintf("%s(): present=%u\n", __func__, present);
	return present;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tps659038_chip_revision_get
 * @BRIEF		return TPS659038 chip revision
 * @RETURNS		> 0.0 TPS659038 chip revision
 *			OMAPCONF_ERR_NOT_AVAILABLE in case of error
 * @DESCRIPTION		return TPS659038 chip revision
 *//*------------------------------------------------------------------------ */
double tps659038_chip_revision_get(void)
{
	int ret;
	unsigned int rev;

	if (chip_revision > 0)
		goto tps659038_chip_revision_get_end;

	ret = i2cget(TPS659038_I2C_BUS, TPS659038_ID2_ADDR, 0x57, &rev);
	if (ret != 0) {
		fprintf(stderr, "%s(): could not read register! (%d)\n",
			__func__, ret);
		chip_revision = (float) OMAPCONF_ERR_NOT_AVAILABLE;
		goto tps659038_chip_revision_get_end;
	}
	dprintf("%s(): rev=%u\n", __func__, rev);
	switch (rev) {
	case 0x0:
		chip_revision = 1.0;
		break;
	case 0x01:
		chip_revision = 2.0;
		break;
	case 0x02:
		chip_revision = 2.1;
		break;
	case 0x03:
		chip_revision = 2.2;
		break;
	default:
		chip_revision = (float) OMAPCONF_ERR_UNEXPECTED;
	}

tps659038_chip_revision_get_end:
	dprintf("%s(): chip_revision = %f\n", __func__,
		chip_revision);
	return chip_revision;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tps659038_eprom_revision_get
 * @BRIEF		return TPS659038 EPROM revision
 * @RETURNS		> 0.0 TPS659038 EPROM revision
 *			OMAPCONF_ERR_NOT_AVAILABLE in case of error
 * @DESCRIPTION		return TPS659038 EPROM revision
 *//*------------------------------------------------------------------------ */
double tps659038_eprom_revision_get(void)
{
	/*
	 * TBD: could not find the infomation tell where to find the register
	 * which indicates this eprom revision number
	 */
	return (double) OMAPCONF_ERR_NOT_AVAILABLE;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tps659038_vsel_get
 * @BRIEF		return vsel-encoded voltage of a given SMPS voltage rail
 * @RETURNS		VSEL-encoded voltage (8-bit, >= 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		smps_id: voltage domain ID
 * @DESCRIPTION		return vsel-encoded voltage of a given SMPS voltage rail
 *//*------------------------------------------------------------------------ */
int tps659038_vsel_get(unsigned int smps_id)
{
	int ret;
	unsigned int val, vsel_addr, vsel, range;
	const tps659038_smps_registers **vdd_smps_regs;
	const tps659038_smps_registers *smps_regs;

	CHECK_ARG_LESS_THAN(smps_id, 5, OMAPCONF_ERR_ARG);

	/* Retrive SMPS registers addresses */
	vdd_smps_regs = tps659038_smps_vdd_dra7xx[smps_id];
	if (vdd_smps_regs == NULL)
		return OMAPCONF_ERR_INTERNAL;
	smps_regs = *vdd_smps_regs;
	if (smps_regs == NULL)
		return OMAPCONF_ERR_INTERNAL;

	dprintf("%s(): smps_id=%u  ADDR: ctrl=0x%02X tstep=0x%02X force=0x%02X "
		"voltage=0x%02X\n", __func__, smps_id, smps_regs->ctrl,
		smps_regs->tstep, smps_regs->force, smps_regs->voltage);

	/* Check SMPS Status */
	if (smps_regs->ctrl == -1) {
		dprintf("%s(): SMPSxx_CTRL addr=-1!!!\n", __func__);
		return OMAPCONF_ERR_INTERNAL;
	}
	ret = i2cget(TPS659038_I2C_BUS, TPS659038_ID0_ADDR,
		smps_regs->ctrl, &val);
	if (ret != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	dprintf("%s(): SMPSxx_CTRL=0x%02X\n", __func__, val);
	if (extract_bitfield(val, 4, 2) == 0) {
		dprintf("(%s(): warning SMPS is OFF\n", __func__);
		return 0;
	}

	/* Check SMPS voltage controlled by registers, not resource pins */
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
		ret = i2cget(TPS659038_I2C_BUS, TPS659038_ID0_ADDR,
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
		ret = i2cget(TPS659038_I2C_BUS, TPS659038_ID0_ADDR,
			smps_regs->voltage, &val);
		if (ret != 0)
			return OMAPCONF_ERR_REG_ACCESS;
		dprintf("%s(): SMPSxx_VOLTAGE=0x%02X\n", __func__, val);
	}
	vsel = extract_bitfield(val, 0, TPS659038_VSEL_LEN);
	dprintf("%s(): SMPSxx_VOLTAGE=0x%02X SMPSxx_VOLTAGE.VSEL=0x%02X\n",
		__func__, val, vsel);

	/* Retrieve VSEL range from SMPSxx_VOLTAGE register (bit 7) */
	if (vsel_addr != (unsigned int) smps_regs->voltage) {
		if (smps_regs->voltage == -1) {
			dprintf("%s(): SMPSxx_VOLTAGE addr=-1!!!\n", __func__);
			return OMAPCONF_ERR_INTERNAL;
		}
		ret = i2cget(TPS659038_I2C_BUS, TPS659038_ID0_ADDR,
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
 * @FUNCTION		tps659038_vsel_to_uv
 * @BRIEF		for a given rail, convert SMPS vsel command into voltage
 *			in microvolts. Take into account SMPS voltage offset.
 * @RETURNS		voltage in microvolts corresponding to SMPS vsel command
 * @param[in]		smps_id: voltage rail
 * @param[in]		vsel: SMPS vsel command (in microvolts)
 * @DESCRIPTION		for a given rail, convert SMPS vsel command into voltage
 *			in microvolts. Take into account SMPS voltage offset.
 *//*------------------------------------------------------------------------ */
unsigned long tps659038_vsel_to_uv(unsigned char vsel)
{
	unsigned long uv;
	unsigned int range;

	/* VSEL = 7-bit + range (MSB) */
	range = extract_bit(vsel, 7);
	vsel = extract_bitfield(vsel, 0, TPS659038_VSEL_LEN);

	if (vsel == 0) {
		uv = 0;
	} else if (vsel <= 0x06) {
		uv = TPS659038_VOLT_MIN_UV;
	} else if (vsel >= 0x79) {
		uv = 1650000;
	} else {
		uv = TPS659038_VOLT_MIN_UV +
			(TPS659038_VSTEP_UV * (vsel - 6));
	}

	/* Apply range multiplier */
	uv = uv << range;

	dprintf("%s(%d (0x%02X))=%lduV\n", __func__,
		vsel, vsel, uv);
	return uv;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tps659038_smps_offset_get
 * @BRIEF		return SMPS regulator voltage offset
 * @RETURNS		voltage offset in microvolts
 * @DESCRIPTION		return SMPS regulator voltage offset
 *//*------------------------------------------------------------------------ */
long tps659038_smps_offset_get(void)
{
	dprintf("%s(): offset=%lduV\n", __func__, (long) TPS659038_VOLT_MIN_UV);

	return (long) TPS659038_VOLT_MIN_UV;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tps659038_smps_step_get
 * @BRIEF		return SMPS regulator voltage step in microvolts
 * @RETURNS		voltage step in microvolts
 * @DESCRIPTION		return SMPS regulator voltage step in microvolts
 *//*------------------------------------------------------------------------ */
long tps659038_smps_step_get(void)
{
	dprintf("%s(): step=%lduV\n", __func__, (long) TPS659038_VSTEP_UV);

	return (long) TPS659038_VSTEP_UV;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tps659038_vsel_len_get
 * @BRIEF		return the size of the vsel command
 * @RETURNS		SMPS regulator size of the vsel command
 * @DESCRIPTION		return the size of the vsel command
 *//*------------------------------------------------------------------------ */
int tps659038_vsel_len_get(void)
{
	return TPS659038_VSEL_LEN;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tps659038_uv_to_vsel
 * @BRIEF		for a given rail, convert voltage in microvolts into
 *			SMPS vsel command.
 * @RETURNS		SMPS vsel command corresponding to uv
 * @param[in]		uv: voltage to be converted (in microvolts)
 * @DESCRIPTION		for a given rail, convert voltage in microvolts into
 *			SMPS vsel command.
 *//*------------------------------------------------------------------------ */
unsigned char tps659038_uv_to_vsel(unsigned long uv)
{
	unsigned char vsel;

	vsel = (unsigned char)
		((uv - TPS659038_VOLT_MIN_UV) / TPS659038_VSTEP_UV + 6);
	dprintf("%s(%lduV)=0x%02X\n", __func__, uv, vsel);
	return vsel;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tps659038_uvoltage_set
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
 *//*------------------------------------------------------------------------ */
int tps659038_uvoltage_set(unsigned int vdd_id, unsigned long uv)
{
	int ret;
	unsigned int val;
	unsigned char vsel;
	const tps659038_smps_registers **vdd_smps_regs;
	const tps659038_smps_registers *smps_regs;

	CHECK_ARG_LESS_THAN(vdd_id, 5, OMAPCONF_ERR_ARG);

	/* Retrive SMPS registers addresses */
	vdd_smps_regs = tps659038_smps_vdd_dra7xx[vdd_id];
	if (vdd_smps_regs == NULL)
		return OMAPCONF_ERR_INTERNAL;
	smps_regs = *vdd_smps_regs;
	if (smps_regs == NULL)
		return OMAPCONF_ERR_INTERNAL;

	dprintf("%s(): vdd_id=%u  ADDR: ctrl=0x%02X tstep=0x%02X force=0x%02X "
		"voltage=0x%02X\n", __func__, vdd_id, smps_regs->ctrl,
		smps_regs->tstep, smps_regs->force, smps_regs->voltage);

	/* Check SMPS Status */
	if (smps_regs->ctrl == -1) {
		dprintf("%s(): SMPSxx_CTRL addr=-1!!!\n", __func__);
		return OMAPCONF_ERR_INTERNAL;
	}
	ret = i2cget(TPS659038_I2C_BUS, TPS659038_ID0_ADDR,
		smps_regs->ctrl, &val);
	if (ret != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	dprintf("%s(): SMPSxx_CTRL=0x%02X\n", __func__, val);
	if (extract_bitfield(val, 4, 2) == 0) {
		dprintf("(%s(): SMPS is OFF\n", __func__);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	/* Make sure SMPSxx_CTRL.ROOF_FLOOR_EN=0 */
	if (extract_bit(val, 6) == 1) {
		dprintf("%s(): SMPS voltage controlled by resource pins, "
			"clearing ROOF_FLOOR_EN bit.\n", __func__);
		/* Clear ROOF_FLOOR_EN bit (6) */
		val = val & 0xBF;
		ret = i2cset(TPS659038_I2C_BUS, TPS659038_ID0_ADDR,
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
	vsel = tps659038_uv_to_vsel(uv);
	dprintf("%s(): uv=%lu vsel=0x%02X\n", __func__, uv, vsel);

	/* Write VSEL to SMPSxx_VOLTAGE */
	ret = i2cset(TPS659038_I2C_BUS, TPS659038_ID0_ADDR,
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
		ret = i2cset(TPS659038_I2C_BUS, TPS659038_ID0_ADDR,
			smps_regs->force, (unsigned int) val);
	} else {
		dprintf("%s(): SMPSxx_FORCE does not exist.\n", __func__);
		ret = 0;
	}

	return ret;
}
