/*
 *
 * @Component			OMAPCONF
 * @Filename			tps65217x.c
 * @Description			AM335X TPS 65217X (SMPS Voltage Regulator)
 *				Library
 * @Author			Gilberto Rodriguez <gilrod@ti.com>
 * @Date			2014
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
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


#include <cpuinfo.h>
#include <i2c-tools.h>
#include <lib.h>
#include <mem.h>
#include <prm_am335x.h>
#include <tps65217x.h>


#ifdef TPS65217X_DEBUG
#include <stdio.h>
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


typedef struct {
	int ctrl;
	int tstep;
	int voltage;
} tps65217x_smps_registers;


static const tps65217x_smps_registers tps65217x_smps2 = {
	.ctrl = 0x16,
	.tstep = -1,
	.voltage = 0x0F};

static const tps65217x_smps_registers tps65217x_smps3 = {
	.ctrl = 0x16,
	.tstep = -1,
	.voltage = 0x10};


static const tps65217x_smps_registers *tps65217x_smps_vdd_am335x_mpu = &tps65217x_smps2;
static const tps65217x_smps_registers *tps65217x_smps_vdd_am335x_core = &tps65217x_smps3;

static const tps65217x_smps_registers **tps65217x_smps_vdd_am335x[5] = {
	(const tps65217x_smps_registers **) &tps65217x_smps_vdd_am335x_mpu,
	NULL,
	(const tps65217x_smps_registers **) &tps65217x_smps_vdd_am335x_core,
	NULL, NULL };

static float chip_revision = -1.0;
static int chip_type = 0;

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tps65217x_is_present
 * @BRIEF		return 1 if TPS65217X is present on this platform,
 *			0 otherwise
 * @RETURNS		1 if TPS65217X chip is found
 *			0 otherwise
 * @DESCRIPTION		return 1 if TPS65217X is present on this platform,
 *			0 otherwise
 *//*------------------------------------------------------------------------ */
unsigned short int tps65217x_is_present(void)
{
	int ret;
	unsigned int id_lsb;
	unsigned short present;

	switch (cpu_get()) {
	case AM_3352:
	case AM_3354:
	case AM_3356:
	case AM_3357:
	case AM_3358:
	case AM_3359:
		/* Check to see if address is readable */
		ret = i2cget(TPS65217X_I2C_BUS, TPS65217X_ID0_ADDR,
			0x00, &id_lsb);
		if (ret != 0)
			return 0;

		/* Check to see if chip and revision is valid */
		present = ((tps65217x_chip_get() >= 6) ||
			tps65217x_chip_revision_get() > 0) ? 1 : 0;
		break;

	default:
		present = 0;
	}

	dprintf("%s(): present=%u\n", __func__, present);
	return present;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tps65217x_chip_get
 * @BRIEF		return TPS65217X chip
 * @RETURNS		> 0.0 TPS65217X chip
 *			OMAPCONF_ERR_UNEXPECTED in case of error
 * @DESCRIPTION		return TPS65217X chip (A, B, C, D, UNKNOWN)
 *//*------------------------------------------------------------------------ */
int tps65217x_chip_get(void)
{
	int ret;
	unsigned int rev;
	unsigned short int pmic_chip;

	ret = i2cget(TPS65217X_I2C_BUS, TPS65217X_ID0_ADDR, 0x00, &rev);
	if (ret != 0) {
		fprintf(stderr, "%s(): could not read register! (%d)\n",
			__func__, ret);
		pmic_chip = OMAPCONF_ERR_NOT_AVAILABLE;
		goto tps65217x_chip_get_end;
	}
	dprintf("%s(): rev=%02x\n", __func__, rev);
	switch (rev & 0xF0) {
	case 0x60:
		pmic_chip = 9; /* TPS65217D */
		break;
	case 0x70:
		pmic_chip = 6; /* TPS65217A */
		break;
	case 0xE0:
		pmic_chip = 8; /* TPS65217C */
		break;
	case 0xF0:
		pmic_chip = 7; /* TPS65217B */
		break;
	default:
		pmic_chip = OMAPCONF_ERR_UNEXPECTED;
	}

tps65217x_chip_get_end:
	dprintf("%s(): pmic_chip = %d %d\n", __func__, pmic_chip, chip_type);
	chip_type = pmic_chip;
	return pmic_chip;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tps65217x_chip_revision_get
 * @BRIEF		return TPS65217X chip revision
 * @RETURNS		> 0.0 TPS65217X chip revision
 *			OMAPCONF_ERR_UNEXPECTED in case of error
 * @DESCRIPTION		return TPS65217X chip revision
 *//*------------------------------------------------------------------------ */
double tps65217x_chip_revision_get(void)
{
	int ret;
	unsigned int rev;

	if (chip_revision > 0)
		goto tps65217x_chip_revision_get_end;

	ret = i2cget(TPS65217X_I2C_BUS, TPS65217X_ID0_ADDR, 0x00, &rev);
	if (ret != 0) {
		fprintf(stderr, "%s(): could not read register! (%d)\n",
			__func__, ret);
		chip_revision = (float) OMAPCONF_ERR_NOT_AVAILABLE;
		goto tps65217x_chip_revision_get_end;
	}
	dprintf("%s(): rev=%02X\n", __func__, rev);
	switch (rev & 0xF) {
	case 0x0:
		chip_revision = 1.0;
		break;
	case 0x01:
		chip_revision = 1.1;
		break;
	case 0x02:
		chip_revision = 1.2;
		break;
	default:
		chip_revision = (float) OMAPCONF_ERR_UNEXPECTED;
	}

tps65217x_chip_revision_get_end:
	dprintf("%s(): chip_revision = %f\n", __func__,
		chip_revision);
	return chip_revision;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tps65217x_eprom_revision_get
 * @BRIEF		return TPS65217X EPROM revision
 * @RETURNS		> 0.0 TPS65217X EPROM revision
 *			OMAPCONF_ERR_NOT_AVAILABLE in case of error
 * @DESCRIPTION		return TPS65217X EPROM revision
 *//*------------------------------------------------------------------------ */
double tps65217x_eprom_revision_get(void)
{
	/*
	 * TBD: could not find the infomation tell where to find the register
	 * which indicates this eprom revision number
	 */
	return (double) OMAPCONF_ERR_NOT_AVAILABLE;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tps65217x_vsel_get
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
int tps65217x_vsel_get(unsigned int smps_id)
{
	int ret;
	unsigned int val, vsel, stat_bit;
	const tps65217x_smps_registers **vdd_smps_regs;
	const tps65217x_smps_registers *smps_regs;

	CHECK_ARG_LESS_THAN(smps_id, 5, OMAPCONF_ERR_ARG);

	/* Retrive SMPS registers addresses */
	vdd_smps_regs = tps65217x_smps_vdd_am335x[smps_id];
	if (vdd_smps_regs == NULL)
		return OMAPCONF_ERR_INTERNAL;
	smps_regs = *vdd_smps_regs;
	if (smps_regs == NULL)
		return OMAPCONF_ERR_INTERNAL;

	dprintf("%s(): smps_id=%u  ADDR: ctrl=0x%02X tstep=0x%02X "
		"voltage=0x%02X\n", __func__, smps_id, smps_regs->ctrl,
		smps_regs->tstep, smps_regs->voltage);

	/* Check SMPS Status */
	if (smps_regs->ctrl == -1) {
		dprintf("%s(): SMPSxx_CTRL addr=-1!!!\n", __func__);
		return OMAPCONF_ERR_INTERNAL;
	}
	ret = i2cget(TPS65217X_I2C_BUS, TPS65217X_ID0_ADDR,
		smps_regs->ctrl, &val);
	if (ret != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	/* MPU and CORE share same enable register */
	switch (chip_type) {
	case 6:
		/*
		 * TPS65217A is for AM335X ZCE package
		 * MPU and CORE are combined for this package
		 */
		stat_bit = 3;
		break;
	case 7:
		if (smps_id == 0)
			stat_bit = 4;
		else
			stat_bit = 3;
		break;
	case 8:
	case 9:
		if (smps_id == 0)
			stat_bit = 3;
		else
			stat_bit = 4;
		break;
	default:
		fprintf(stderr, "%s(): should not reach here?!\n", __func__);
		return OMAPCONF_ERR_INTERNAL;
	}
	dprintf("%s(): SMPSxx_CTRL=0x%02X\n", __func__, val);
	if (extract_bit(val, stat_bit) == 0) {
		dprintf("(%s(): warning SMPS is OFF\n", __func__);
		return 0;
	}

	/* Check SMPS voltage controlled by registers, not resource pins */
	ret = i2cget(TPS65217X_I2C_BUS, TPS65217X_ID0_ADDR,
		smps_regs->voltage, &val);
	if (ret != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (extract_bit(val, 7) == 1) {
		dprintf("%s(): SMPS voltage controlled by resource pins\n",
			__func__);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	/* Retrieve VSEL (6-bits) from relevant register */
	if (smps_regs->voltage != -1) {
		ret = i2cget(TPS65217X_I2C_BUS, TPS65217X_ID0_ADDR,
			smps_regs->voltage, &val);
		if (ret != 0)
			return OMAPCONF_ERR_REG_ACCESS;
		dprintf("%s(): SMPSxx_VOLTAGE=0x%02X\n", __func__, val);
	} else {
		dprintf("%s(): SMPSxx_VOLTAGE addr=-1!!!\n", __func__);
		return OMAPCONF_ERR_INTERNAL;
	}
	vsel = extract_bitfield(val, 0, TPS65217X_VSEL_LEN);
	dprintf("%s(): SMPSxx_VOLTAGE=0x%02X SMPSxx_VOLTAGE.VSEL=0x%02X\n",
		__func__, val, vsel);

	return vsel;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tps65217x_vsel_to_uv
 * @BRIEF		for a given rail, convert SMPS vsel command into voltage
 *			in microvolts. Take into account SMPS voltage offset.
 * @RETURNS		voltage in microvolts corresponding to SMPS vsel command
 * @param[in]		smps_id: voltage rail
 * @param[in]		vsel: SMPS vsel command (in microvolts)
 * @DESCRIPTION		for a given rail, convert SMPS vsel command into voltage
 *			in microvolts. Take into account SMPS voltage offset.
 *//*------------------------------------------------------------------------ */
unsigned long tps65217x_vsel_to_uv(unsigned char vsel)
{
	unsigned long uv;

	vsel = extract_bitfield(vsel, 0, TPS65217X_VSEL_LEN);

	if (vsel == 0) {
		uv = TPS65217X_VOLT_MIN_UV;
	} else if (vsel >= 0x38) {
		uv = 3300000;
	} else if (vsel >= 0x18) {
		uv = TPS65217X_VOLT_MIN_UV + 600000 +
			(TPS65217X_VSTEP_UV * 2 * (vsel - 12));
	} else {
		uv = TPS65217X_VOLT_MIN_UV +
			(TPS65217X_VSTEP_UV * vsel);
	}

	dprintf("%s(%d (0x%02X))=%lduV\n", __func__, vsel, vsel, uv);
	return uv;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tps65217x_smps_offset_get
 * @BRIEF		return SMPS regulator voltage offset
 * @RETURNS		voltage offset in microvolts
 * @DESCRIPTION		return SMPS regulator voltage offset
 *//*------------------------------------------------------------------------ */
long tps65217x_smps_offset_get(void)
{
	dprintf("%s(): offset=%lduV\n", __func__, (long) TPS65217X_VOLT_MIN_UV);

	return (long) TPS65217X_VOLT_MIN_UV;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tps65217x_smps_step_get
 * @BRIEF		return SMPS regulator voltage step in microvolts
 * @RETURNS		voltage step in microvolts
 * @DESCRIPTION		return SMPS regulator voltage step in microvolts
 *//*------------------------------------------------------------------------ */
long tps65217x_smps_step_get(void)
{
	dprintf("%s(): step=%lduV\n", __func__, (long) TPS65217X_VSTEP_UV);

	return (long) TPS65217X_VSTEP_UV;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tps65217x_vsel_len_get
 * @BRIEF		return the size of the vsel command
 * @RETURNS		SMPS regulator size of the vsel command
 * @DESCRIPTION		return the size of the vsel command
 *//*------------------------------------------------------------------------ */
int tps65217x_vsel_len_get(void)
{
	return TPS65217X_VSEL_LEN;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tps65217x_uv_to_vsel
 * @BRIEF		for a given rail, convert voltage in microvolts into
 *			SMPS vsel command.
 * @RETURNS		SMPS vsel command corresponding to uv
 * @param[in]		uv: voltage to be converted (in microvolts)
 * @DESCRIPTION		for a given rail, convert voltage in microvolts into
 *			SMPS vsel command.
 *//*------------------------------------------------------------------------ */
unsigned char tps65217x_uv_to_vsel(unsigned long uv)
{
	unsigned char vsel;

	vsel = (unsigned char)
		((uv - TPS65217X_VOLT_MIN_UV) / TPS65217X_VSTEP_UV + 6);
	dprintf("%s(%lduV)=0x%02X\n", __func__, uv, vsel);
	return vsel;
}
