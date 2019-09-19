/*
 *
 * @Component			OMAPCONF
 * @Filename			lp87565.c
 * @Description			OMAP4 LP87565  (SMPS Voltage Regulator) Library
 * @Author			Richard Woodruff (r-woodruff2@ti.com)
 * @Date			2019
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2019 Texas Instruments Incorporated - http://www.ti.com/
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

#include <lp87565.h>
#include <lib.h>
#include <i2c-tools.h>
#include <mem.h>
#include <cpuinfo.h>
#include <prm_dra7xx.h>

/* #define LP87565_DEBUG */
#ifdef LP87565_DEBUG
#include <stdio.h>
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

typedef struct {
	int ctrl;
	unsigned int addr;
	int force;
	int voltage;
} lp87565_smps_registers;

static const lp87565_smps_registers lp87565_smps12 = {
	.ctrl = 0x2,
	.addr = 0x60,
	.force = -1,
	.voltage = 0xa
};

static const lp87565_smps_registers lp87565_smps34 = {
	.ctrl = 0x6,
	.addr = 0x60,
	.force = -1,
	.voltage = 0xe
};

/* alternate PMIC PQ2*/
static const lp87565_smps_registers lp87565_pq1_smps1234 = {
	.ctrl = 0xa,
	.addr = 0x61,
	.force = -1,
	.voltage = 0x4
};

static const lp87565_smps_registers lp87565_pq2_smps1234 = {
	.ctrl = 0xa,
	.addr = 0x62,
	.force = -1,
	.voltage = 0x4
};

static const lp87565_smps_registers *lp87565_smps_vdd_dra7xx_mpu = &lp87565_smps12;
static const lp87565_smps_registers *lp87565_smps_vdd_dra7xx_gpu = &lp87565_smps34;

static const lp87565_smps_registers **lp87565_smps_vdd_dra7xx[5] = {
	(const lp87565_smps_registers **) &lp87565_smps_vdd_dra7xx_mpu,
	NULL,
	NULL,
	(const lp87565_smps_registers **) &lp87565_smps_vdd_dra7xx_gpu,
	NULL
};

unsigned long p_step = LP87565_VDCDC1_STEP;
unsigned int p_voff = LP87565_VDCDC1_MIN;
unsigned int p_eoff = LP87565_VDCDC1_ENC_OFF;

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		lp87565_is_present
 * @BRIEF		return 1 if LP87565  is present on this platform,
 *			0 otherwise
 * @RETURNS		1 if LP87565  chip is found
 *			0 otherwise
 * @DESCRIPTION		return 1 if LP87565  is present on this platform,
 *			0 otherwise
 *//*------------------------------------------------------------------------ */
unsigned short int lp87565_is_present(void)
{
	int ret;
	unsigned int id_lsb;
	unsigned short present = 0;

	switch (cpu_get()) {
	case DRA_76X:
		ret = i2cget(LP87565_I2C_BUS, LP87565_ID0_ADDR, LP87565_PRODUCT_ID_LSB, &id_lsb);
		if (ret != 0)
			return 0;
		if (id_lsb == 0x12){
			present = 1;
			p_step = LP87565_VDCDC1_STEP;
			p_voff = LP87565_VDCDC1_MIN;
			p_eoff = LP87565_VDCDC1_ENC_OFF;
		} else {
			present = 1;
			p_step = PQ2_VDCDC1_STEP;
			p_voff = PQ2_VDCDC1_MIN;
			p_eoff = PQ2_VDCDC1_ENC_OFF;
			lp87565_smps_vdd_dra7xx_mpu = &lp87565_pq1_smps1234;
			lp87565_smps_vdd_dra7xx_gpu = &lp87565_pq2_smps1234;
			lp87565_smps_vdd_dra7xx[0] = (const lp87565_smps_registers **) &lp87565_smps_vdd_dra7xx_mpu;
			lp87565_smps_vdd_dra7xx[3] = (const lp87565_smps_registers **) &lp87565_smps_vdd_dra7xx_gpu;
		}
		break;
	default:
		break;
	}

	dprintf("%s(): present=%u\n", __func__, present);
	return present;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		lp87565_chip_revision_get
 * @BRIEF		return LP87565  chip revision
 * @RETURNS		> 0.0 LP87565  chip revision
 *			OMAPCONF_ERR_NOT_AVAILABLE in case of error
 * @DESCRIPTION		return LP87565  chip revision
 *//*------------------------------------------------------------------------ */
double lp87565_chip_revision_get(void)
{
	/* SR-I2C link is write-only, cannot read-back any chip register ... */
	return (double) OMAPCONF_ERR_NOT_AVAILABLE;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		lp87565_eprom_revision_get
 * @BRIEF		return LP87565  EPROM revision
 * @RETURNS		> 0.0 LP87565  EPROM revision
 *			OMAPCONF_ERR_NOT_AVAILABLE in case of error
 * @DESCRIPTION		return LP87565  EPROM revision
 *//*------------------------------------------------------------------------ */
double lp87565_eprom_revision_get(void)
{
	/* SR-I2C link is write-only, cannot read-back any chip register ... */
	return (double) OMAPCONF_ERR_NOT_AVAILABLE;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		lp87565_smps_offset_get
 * @BRIEF		return SMPS regulator voltage offset
 * @RETURNS		voltage offset in microvolts
 * @DESCRIPTION		return SMPS regulator voltage offset
 *//*------------------------------------------------------------------------ */
long lp87565_smps_offset_get(void)
{
	dprintf("%s(): offset=%lduV\n", __func__, (long) p_voff);

	return (long) p_voff;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		lp87565_smps_step_get
 * @BRIEF		return SMPS regulator voltage step in microvolts
 * @RETURNS		voltage step in microvolts
 * @DESCRIPTION		return SMPS regulator voltage step in microvolts
 *//*------------------------------------------------------------------------ */
long lp87565_smps_step_get(void)
{
	dprintf("%s(): step=%lduV\n", __func__, (long) p_step);

	return (long) p_step;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		lp87565_vsel_to_uv
 * @BRIEF		for a given rail, convert SMPS vsel command into voltage
 *			in microvolts.
 * @RETURNS		voltage in microvolts corresponding to SMPS vsel command
 * @param[in]		vsel: SMPS vsel command (in microvolts)
 * @DESCRIPTION		for a given rail, convert SMPS vsel command into voltage
 *			in microvolts.
 *//*------------------------------------------------------------------------ */
unsigned long lp87565_vsel_to_uv(unsigned char vsel)
{
	unsigned long uv;

	uv = p_voff + (p_step * (vsel - p_eoff));
	dprintf("%s(%d)=%lduV\n", __func__, vsel, uv);
	return uv;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		lp87565_uv_to_vsel
 * @BRIEF		for a given rail, convert voltage in microvolts into
 *			SMPS vsel command.
 * @RETURNS		SMPS vsel command corresponding to uv
 * @param[in]		uv: voltage to be converted (in microvolts)
 * @DESCRIPTION		for a given rail, convert voltage in microvolts into
 *			SMPS vsel command.
 *//*------------------------------------------------------------------------ */
unsigned char lp87565_uv_to_vsel(unsigned long uv)
{
	unsigned char vsel;

	vsel = (unsigned char)
		DIV_ROUND_UP(uv - p_voff, p_step) + p_eoff;
	dprintf("%s(%lduV)=0x%02X\n", __func__, uv, vsel);
	return vsel;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		lp87565_vsel_get
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
int lp87565_vsel_get(unsigned int smps_id)
{
	int ret;
	unsigned int vsel;
	const lp87565_smps_registers **vdd_smps_regs;
	const lp87565_smps_registers *smps_regs;

	CHECK_ARG_LESS_THAN(smps_id, 5, OMAPCONF_ERR_ARG);

	/* Retrive SMPS registers addresses */
	vdd_smps_regs = lp87565_smps_vdd_dra7xx[smps_id];
	if (vdd_smps_regs == NULL)
		return OMAPCONF_ERR_INTERNAL;
	smps_regs = *vdd_smps_regs;
	if (smps_regs == NULL)
		return OMAPCONF_ERR_INTERNAL;

	dprintf("%s(): smps_id=%u  ADDR: ctrl=0x%02X addr=0x%02X force=0x%02X "
		"voltage=0x%02X\n", __func__, smps_id, smps_regs->ctrl,
		smps_regs->addr, smps_regs->force, smps_regs->voltage);

	if (smps_regs->voltage == -1) {
		dprintf("%s(): SMPSxx_VOLTAGE addr=-1!!!\n", __func__);
		return OMAPCONF_ERR_INTERNAL;
	}
	ret = i2cget(LP87565_I2C_BUS, smps_regs->addr,
		smps_regs->voltage, &vsel);
	if (ret != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	dprintf("%s(): vsel=0x%02X\n", __func__, vsel);
	return vsel;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		lp87565_uvoltage_set
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
int lp87565_uvoltage_set(unsigned int vdd_id, unsigned long uv)
{
	int ret;
	unsigned char vsel;
	const lp87565_smps_registers **vdd_smps_regs;
	const lp87565_smps_registers *smps_regs;

	CHECK_ARG_LESS_THAN(vdd_id, 5, OMAPCONF_ERR_ARG);

	/* Retrive SMPS registers addresses */
	vdd_smps_regs = lp87565_smps_vdd_dra7xx[vdd_id];
	if (vdd_smps_regs == NULL)
		return OMAPCONF_ERR_INTERNAL;
	smps_regs = *vdd_smps_regs;
	if (smps_regs == NULL)
		return OMAPCONF_ERR_INTERNAL;

	/* Convert voltage to VSEL */
	vsel = lp87565_uv_to_vsel(uv);
	dprintf("%s(): uv=%lu vsel=0x%02X\n", __func__, uv, vsel);

	/* Write VSEL to SMPSxx_VOLTAGE */
	ret = i2cset(LP87565_I2C_BUS, smps_regs->addr,
			smps_regs->voltage, (unsigned int) vsel);
	if (ret != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	return ret;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		lp87565_vsel_len_get
 * @BRIEF		return the size of the vsel command
 * @RETURNS		SMPS regulator size of the vsel command
 * @DESCRIPTION		return the size of the vsel command
 *//*------------------------------------------------------------------------ */
int lp87565_vsel_len_get(void)
{
	return 8;
}
