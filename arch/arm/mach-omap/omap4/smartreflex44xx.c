/*
 *
 * @Component			OMAPCONF
 * @Filename			smartreflex44xx.c
 * @Description			Dump & Analyse SMARTREFLEX registers
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


#include <smartreflex44xx.h>
#include <sr44xx-data.h>
#include <sr.h>
#include <vp.h>
#include <vp44xx.h>
#include <vc.h>
#include <vc44xx.h>
#include <prm44xx.h>
#include <module44xx.h>
#include <lib44xx.h>
#include <autoadjust_table.h>
#include <help.h>
#include <lib.h>
#include <mem.h>
#include <cpuinfo.h>
#include <string.h>
#include <pmic.h>


/* #define SR44XX_DEBUG */
#ifdef SR44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


#define PMIC_SLAVE_ADDR			0x12
#define VOLT_REG_MPU_ADDR		0x55
#define VOLT_REG_IVA_ADDR		0x5B
#define VOLT_REG_CORE_ADDR		0x61

#define OMAP4460_VOLT_REG_CORE_ADDR	0x55

#define OMAP4470_VOLT_REG_IVA_ADDR	0x49
#define OMAP4470_VOLT_REG_CORE_ADDR	0x5B

#define TPS62361_SLAVE_ADDR		0x60
#define TPS62361_VOLT_REG_ADDR		0x01

#define VC_BYPASS_SLAVE_ADDR_MASK	0x0000007F
#define VC_BYPASS_SLAVE_ADDR_SHIFT	0
#define VC_BYPASS_REG_ADDR_MASK		0x0000FF00
#define VC_BYPASS_REG_ADDR_SHIFT	8
#define VC_BYPASS_DATA_MASK		0x00FF0000
#define VC_BYPASS_DATA_SHIFT		16
#define VC_BYPASS_CMD_VALID_MASK	0x01000000
#define VC_BYPASS_CMD_VALID_SHIFT	24

#define OMAP4_VOLTAGE_MAX		((double) 1500000) /* micro-volts */
#define OMAP4_VOLTAGE_MIN		((double) 600000) /* micro-volts */

#define PRCM_SR_REG_TABLE_SIZE		15
#define PRCM_SR_VC_REG_TABLE_SIZE	11
#define PRCM_SR_VP_REG_TABLE_SIZE	7


static reg_table prcm_sr_mpu_reg_table[PRCM_SR_REG_TABLE_SIZE];
static reg_table prcm_sr_iva_reg_table[PRCM_SR_REG_TABLE_SIZE];
static reg_table prcm_sr_core_reg_table[PRCM_SR_REG_TABLE_SIZE];
static reg_table prcm_sr_vp_mpu_reg_table[PRCM_SR_VP_REG_TABLE_SIZE];
static reg_table prcm_sr_vp_iva_reg_table[PRCM_SR_VP_REG_TABLE_SIZE];
static reg_table prcm_sr_vp_core_reg_table[PRCM_SR_VP_REG_TABLE_SIZE];
static reg_table prcm_sr_vc_reg_table[PRCM_SR_VC_REG_TABLE_SIZE];
static unsigned int init_done = 0;

static int sr44xx_regtable_init(void);


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr44xx_name2addr
 * @BRIEF		retrieve physical address of a register, given its name.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		name: register name
 * @param[in,out]	addr: register address
 * @DESCRIPTION		retrieve physical address of a register, given its name.
 *//*------------------------------------------------------------------------ */
int sr44xx_name2addr(char *name, unsigned int *addr)
{
	int ret;

	if (!cpu_is_omap44xx())
		return OMAPCONF_ERR_CPU;

	if (!init_done)
		sr44xx_regtable_init();

	ret = name2addr(name, addr, prcm_sr_vc_reg_table);
	if (ret == 0)
		return ret;
	ret = name2addr(name, addr, prcm_sr_vp_mpu_reg_table);
	if (ret == 0)
		return ret;
	ret = name2addr(name, addr, prcm_sr_vp_iva_reg_table);
	if (ret == 0)
		return ret;
	ret = name2addr(name, addr, prcm_sr_vp_core_reg_table);
	if (ret == 0)
		return ret;

	/*
	 * This function is called on a "omapconf read 'by name'"
	 * If name is found, then read access will be done.
	 * In the case of SR, module may be disabled so access will fail.
	 * Return OMAPCONF_ERR_REG_ACCESS if register not available.
	 */
	ret = name2addr(name, addr, prcm_sr_mpu_reg_table);
	if (ret == 0) {
		if (mod44xx_is_accessible(OMAP4_SMARTREFLEX_MPU) == 1)
			return 0;
		else
			return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	ret = name2addr(name, addr, prcm_sr_iva_reg_table);
	if (ret == 0) {
		if (mod44xx_is_accessible(OMAP4_SMARTREFLEX_IVA) == 1)
			return 0;
		else
			return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	ret = name2addr(name, addr, prcm_sr_core_reg_table);
	if (ret == 0) {
		if (mod44xx_is_accessible(OMAP4_SMARTREFLEX_CORE) == 1)
			return 0;
		else
			return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	return OMAPCONF_ERR_NOT_AVAILABLE;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr44xx_dump
 * @BRIEF		dump SR PRCM registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		dump SR PRCM registers
 *//*------------------------------------------------------------------------ */
int sr44xx_dump(void)
{
	unsigned int ret;

	if (!cpu_is_omap44xx())
		return OMAPCONF_ERR_CPU;

	if (!init_done)
		sr44xx_regtable_init();

	if (mod44xx_is_accessible(OMAP4_SMARTREFLEX_MPU) != 1) {
		printf("SR_MPU not accessible.\n");
	} else {
		ret = dumpregs(prcm_sr_mpu_reg_table);
		if (ret != 0)
			return ret;
	}
	ret = dumpregs(prcm_sr_vp_mpu_reg_table);
	if (ret != 0)
		return ret;

	if (mod44xx_is_accessible(OMAP4_SMARTREFLEX_IVA) != 1) {
		printf("SR_IVA not accessible.\n");
	} else {
		ret = dumpregs(prcm_sr_iva_reg_table);
		if (ret != 0)
			return ret;
	}
	ret = dumpregs(prcm_sr_vp_iva_reg_table);
	if (ret != 0)
		return ret;

	if (mod44xx_is_accessible(OMAP4_SMARTREFLEX_CORE) != 1) {
		printf("SR_CORE not accessible.\n");
	} else {
		ret = dumpregs(prcm_sr_core_reg_table);
		if (ret != 0)
			return ret;
	}
	ret = dumpregs(prcm_sr_vp_core_reg_table);
	if (ret != 0)
		return ret;

	return dumpregs(prcm_sr_vc_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr44xx_is_enabled
 * @BRIEF		Check if SR module is enabled
 * @RETURNS		1 if module is enabled, 0 otherwise
 * @param[in]		sr_id: SR module ID
 * @DESCRIPTION		Check if SR module is enabled
 *//*------------------------------------------------------------------------ */
unsigned int sr44xx_is_enabled(omap4_sr_module_id sr_id)
{
	unsigned int sr_config_addr, sr_config;
	mod44xx_id module_id;
	int ret;

	switch (sr_id) {
	case OMAP4_SR_MPU:
		sr_config_addr = OMAP4430_SR_MPU_SRCONFIG;
		module_id = OMAP4_SMARTREFLEX_MPU;
		break;
	case OMAP4_SR_IVA:
		sr_config_addr = OMAP4430_SR_IVA_SRCONFIG;
		module_id = OMAP4_SMARTREFLEX_IVA;
		break;
	case OMAP4_SR_CORE:
		sr_config_addr = OMAP4430_SR_CORE_SRCONFIG;
		module_id = OMAP4_SMARTREFLEX_CORE;
		break;
	default:
		return 0;
	}

	/* Read SR_CONFIG register (if accessible) */
	if (mod44xx_is_accessible(module_id) != 1)
		return 0;
	ret = mem_read(sr_config_addr, &sr_config);
	if (ret != 0)
		return 0;

	return sr_is_enabled(sr_config);

}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr44xx_name_get
 * @BRIEF		return SR module name.
 * @RETURNS		SR module name on success
 *			"FIXME" string in case of error
 * @param[in]		sr_id: SR module ID
 * @DESCRIPTION		return SR module name.
 *//*------------------------------------------------------------------------ */
const char *sr44xx_name_get(omap4_sr_module_id sr_id)
{
	if (sr_id < OMAP4_SR_ID_MAX)
		return sr44xx_mod_names[sr_id];
	else
		return sr44xx_mod_names[OMAP4_SR_ID_MAX];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr44xx_golden_settings_get
 * @BRIEF		return SR module golden settings.
 * @RETURNS		SR module name on success
 *			"FIXME" string in case of error
 * @param[in]		sr_id: SR module ID
 *			opp_id: OPP ID
 * @DESCRIPTION		return SR module golden settings, for a given chip,
 *			module and OPP.
 *//*------------------------------------------------------------------------ */
const sr_audit_settings *sr44xx_golden_settings_get(omap4_sr_module_id sr_id,
	opp44xx_id opp_id)
{
	omap_chip chip_id;

	CHECK_ARG_LESS_THAN(sr_id, OMAP4_SR_ID_MAX, NULL);
	CHECK_ARG_LESS_THAN(opp_id, OPP44XX_ID_MAX, NULL);

	chip_id = cpu_get();
	dprintf("%s(): sr_id=%d opp_id=%d chip_id=%d\n", __func__,
		sr_id, opp_id, chip_id);
	return sr44xx_golden_settings[chip_id][sr_id][opp_id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr44xx_registers_get
 * @BRIEF		save SR registers content into sr_regs structure.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		sr_id: SR module ID
 * @param[in,out]	sr_regs: SR module registers content
 * @DESCRIPTION		save SR registers content into sr_regs structure.
 *//*------------------------------------------------------------------------ */
int sr44xx_registers_get(omap4_sr_module_id sr_id, sr_registers *sr_regs)
{
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(sr_id, OMAP4_SR_ID_MAX, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(sr_regs, OMAPCONF_ERR_ARG);

	switch (sr_id) {
	case OMAP4_SR_MPU:
		if (mod44xx_is_accessible(OMAP4_SMARTREFLEX_MPU) != 1) {
			sr_regs->accessible = 0;
			ret = 0;
		} else {
			sr_regs->accessible = 1;
			ret = mem_read(OMAP4430_SR_MPU_SRCONFIG,
				&(sr_regs->srconfig));
			ret += mem_read(OMAP4430_SR_MPU_SRSTATUS,
				&(sr_regs->srstatus));
			ret += mem_read(OMAP4430_SR_MPU_SENVAL,
				&(sr_regs->senval));
			ret += mem_read(OMAP4430_SR_MPU_SENMIN,
				&(sr_regs->senmin));
			ret += mem_read(OMAP4430_SR_MPU_SENMAX,
				&(sr_regs->senmax));
			ret += mem_read(OMAP4430_SR_MPU_SENAVG,
				&(sr_regs->senavg));
			ret += mem_read(OMAP4430_SR_MPU_AVGWEIGHT,
				&(sr_regs->avgweight));
			ret += mem_read(OMAP4430_SR_MPU_NVALUERECIPROCAL,
				&(sr_regs->nvaluereciprocal));
			ret += mem_read(OMAP4430_SR_MPU_IRQSTATUS_RAW,
				&(sr_regs->irqstatus_raw));
			ret += mem_read(OMAP4430_SR_MPU_IRQSTATUS,
				&(sr_regs->irqstatus));
			ret += mem_read(OMAP4430_SR_MPU_IRQENABLE_SET,
				&(sr_regs->irqenable_set));
			ret += mem_read(OMAP4430_SR_MPU_SENERROR,
				&(sr_regs->senerror));
			ret += mem_read(OMAP4430_SR_MPU_ERRCONFIG,
				&(sr_regs->errconfig));
		}
		break;

	case OMAP4_SR_IVA:
		if (mod44xx_is_accessible(OMAP4_SMARTREFLEX_IVA) != 1) {
			sr_regs->accessible = 0;
			ret = 0;
		} else {
			sr_regs->accessible = 1;
			ret = mem_read(OMAP4430_SR_IVA_SRCONFIG,
				&(sr_regs->srconfig));
			ret += mem_read(OMAP4430_SR_IVA_SRSTATUS,
				&(sr_regs->srstatus));
			ret += mem_read(OMAP4430_SR_IVA_SENVAL,
				&(sr_regs->senval));
			ret += mem_read(OMAP4430_SR_IVA_SENMIN,
				&(sr_regs->senmin));
			ret += mem_read(OMAP4430_SR_IVA_SENMAX,
				&(sr_regs->senmax));
			ret += mem_read(OMAP4430_SR_IVA_SENAVG,
				&(sr_regs->senavg));
			ret += mem_read(OMAP4430_SR_IVA_AVGWEIGHT,
				&(sr_regs->avgweight));
			ret += mem_read(OMAP4430_SR_IVA_NVALUERECIPROCAL,
				&(sr_regs->nvaluereciprocal));
			ret += mem_read(OMAP4430_SR_IVA_IRQSTATUS_RAW,
				&(sr_regs->irqstatus_raw));
			ret += mem_read(OMAP4430_SR_IVA_IRQSTATUS,
				&(sr_regs->irqstatus));
			ret += mem_read(OMAP4430_SR_IVA_IRQENABLE_SET,
				&(sr_regs->irqenable_set));
			ret += mem_read(OMAP4430_SR_IVA_SENERROR,
				&(sr_regs->senerror));
			ret += mem_read(OMAP4430_SR_IVA_ERRCONFIG,
				&(sr_regs->errconfig));
		}
		break;

	case OMAP4_SR_CORE:
		if (mod44xx_is_accessible(
			OMAP4_SMARTREFLEX_CORE) != 1) {
			sr_regs->accessible = 0;
			ret = 0;
		} else {
			sr_regs->accessible = 1;
			ret = mem_read(OMAP4430_SR_CORE_SRCONFIG,
				&(sr_regs->srconfig));
			ret += mem_read(OMAP4430_SR_CORE_SRSTATUS,
				&(sr_regs->srstatus));
			ret += mem_read(OMAP4430_SR_CORE_SENVAL,
				&(sr_regs->senval));
			ret += mem_read(OMAP4430_SR_CORE_SENMIN,
				&(sr_regs->senmin));
			ret += mem_read(OMAP4430_SR_CORE_SENMAX,
				&(sr_regs->senmax));
			ret += mem_read(OMAP4430_SR_CORE_SENAVG,
				&(sr_regs->senavg));
			ret += mem_read(OMAP4430_SR_CORE_AVGWEIGHT,
				&(sr_regs->avgweight));
			ret += mem_read(OMAP4430_SR_CORE_NVALUERECIPROCAL,
				&(sr_regs->nvaluereciprocal));
			ret += mem_read(OMAP4430_SR_CORE_IRQSTATUS_RAW,
				&(sr_regs->irqstatus_raw));
			ret += mem_read(OMAP4430_SR_CORE_IRQSTATUS,
				&(sr_regs->irqstatus));
			ret += mem_read(OMAP4430_SR_CORE_IRQENABLE_SET,
				&(sr_regs->irqenable_set));
			ret += mem_read(OMAP4430_SR_CORE_SENERROR,
				&(sr_regs->senerror));
			ret += mem_read(OMAP4430_SR_CORE_ERRCONFIG,
				&(sr_regs->errconfig));
		}
		break;

	default:
		sr_regs->accessible = 0;
		ret = OMAPCONF_ERR_ARG;
	}

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr44xx_vp_voltage_get
 * @BRIEF		find the last voltage set by the voltage processor
 *			for a domain
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		sr_id: SR module ID
 * @param[in, out]	volt: last voltage set by voltage processor
 *			for this domain (returned)
 * @DESCRIPTION		find the last voltage set by the voltage processor
 *			for a domain
 *			NB: SR/VP/VC have to be at least initialized
 *			(SR could be disabled) otherwise this value has no
 *			sense.
 *//*------------------------------------------------------------------------ */
int sr44xx_vp_voltage_get(omap4_sr_module_id sr_id, double *volt)
{
	unsigned int vp_voltage, vp_voltage_addr, uv;
	unsigned char vsel;
	voltdm44xx_id vdd_id = OMAP4_VD_ID_MAX;
	int ret;

	if (volt == NULL)
		return OMAPCONF_ERR_ARG;
	*volt = 0.0;
	if (!cpu_is_omap44xx())
		return OMAPCONF_ERR_CPU;

	/* Retrieve corresponding register address */
	switch (sr_id) {
	case OMAP4_SR_MPU:
		vp_voltage_addr = OMAP4430_PRM_VP_MPU_VOLTAGE;
		vdd_id = OMAP4_VDD_MPU;
		break;
	case OMAP4_SR_IVA:
		vp_voltage_addr = OMAP4430_PRM_VP_IVA_VOLTAGE;
		vdd_id = OMAP4_VDD_IVA;
		break;
	case OMAP4_SR_CORE:
		vp_voltage_addr = OMAP4430_PRM_VP_CORE_VOLTAGE;
		vdd_id = OMAP4_VDD_CORE;
		break;
	default:
		return OMAPCONF_ERR_ARG;
	}

	/* Retrieve register content and extract voltage */
	if (mem_read(vp_voltage_addr, &vp_voltage) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	ret = vp_last_voltage_get(vp_voltage, (unsigned short) vdd_id,
		&vsel, &uv);
	if (ret != 0)
		return ret;

	*volt = (double) uv / 1000000.0;
	dprintf("%s(): VP voltage is %lf\n", __func__, *volt);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr44xx_vc_config
 * @BRIEF		analyse voltage controller configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		analyse voltage controller configuration
 *//*------------------------------------------------------------------------ */
int sr44xx_vc_config(void)
{
	vc44xx_registers vc_regs;
	int ret = 0;

	if (!cpu_is_omap44xx())
		return OMAPCONF_ERR_CPU;

	ret = vc44xx_registers_get(&vc_regs);
	if (ret != 0)
		return ret;

	/* Analyze VC configuration registers */
	ret = vc44xx_config_show(stdout, &vc_regs);
	if (ret != 0)
		return ret;

	return sri2c_config_show(stdout,
		vc_regs.prm_vc_cfg_i2c_mode, vc_regs.prm_vc_cfg_i2c_clk);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr44xx_module_config
 * @BRIEF		analyze configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		analyze configuration
 *//*------------------------------------------------------------------------ */
int sr44xx_module_config(void)
{
	sr_registers sr_regs[3];
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	/* Read SR_MPU registers (if accessible) */
	ret = sr44xx_registers_get(OMAP4_SR_MPU, &(sr_regs[0]));
	if (ret != 0)
		return ret;

	/* Read SR_IVA registers (if accessible) */
	ret = sr44xx_registers_get(OMAP4_SR_IVA, &(sr_regs[1]));
	if (ret != 0)
		return ret;

	/* Read SR_CORE registers (if accessible) */
	ret = sr44xx_registers_get(OMAP4_SR_CORE, &(sr_regs[2]));
	if (ret != 0)
		return ret;

	if ((sr_regs[0].accessible == 0) &&
		(sr_regs[1].accessible == 0) &&
		(sr_regs[2].accessible == 0)) {
		printf("All Smart-Reflex Modules disabled.\n");
		return 0;
	}

	return sr_config_show(stdout, sr_regs);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr44xx_status_show
 * @BRIEF		analyze OMAP4 SR convergence status
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		stream: output file (NULL: no output (silent))
 * @DESCRIPTION		analyze OMAP4 SR convergence status
 *//*------------------------------------------------------------------------ */
int sr44xx_status_show(FILE *stream)
{
	sr_status_registers sr_status_regs[3];
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	/* Read SR_MPU registers (if accessible) */
	if (mod44xx_is_accessible(OMAP4_SMARTREFLEX_MPU) != 1) {
		sr_status_regs[0].enabled = 0;
		ret = 0;
	} else {
		sr_status_regs[0].enabled = 1;
		ret = mem_read(OMAP4430_SR_MPU_SRCONFIG,
			&(sr_status_regs[0].srconfig));
		ret += mem_read(OMAP4430_SR_MPU_SENERROR,
			&(sr_status_regs[0].senerror));
		ret += mem_read(OMAP4430_SR_MPU_ERRCONFIG,
			&(sr_status_regs[0].errconfig));
		ret += mem_read(OMAP4430_PRM_VP_MPU_CONFIG,
			&(sr_status_regs[0].vp_config));
	}

	/* Read SR_IVA registers (if accessible) */
	if (mod44xx_is_accessible(OMAP4_SMARTREFLEX_IVA) != 1) {
		sr_status_regs[1].enabled = 0;
		ret = 0;
	} else {
		sr_status_regs[1].enabled = 1;
		ret = mem_read(OMAP4430_SR_IVA_SRCONFIG,
			&(sr_status_regs[1].srconfig));
		ret += mem_read(OMAP4430_SR_IVA_SENERROR,
			&(sr_status_regs[1].senerror));
		ret += mem_read(OMAP4430_SR_IVA_ERRCONFIG,
			&(sr_status_regs[1].errconfig));
		ret += mem_read(OMAP4430_PRM_VP_IVA_CONFIG,
			&(sr_status_regs[1].vp_config));
	}

	/* Read SR_CORE registers (if accessible) */
	if (mod44xx_is_accessible(OMAP4_SMARTREFLEX_CORE) != 1) {
		sr_status_regs[2].enabled = 0;
		ret = 0;
	} else {
		sr_status_regs[2].enabled = 1;
		ret = mem_read(OMAP4430_SR_CORE_SRCONFIG,
			&(sr_status_regs[2].srconfig));
		ret += mem_read(OMAP4430_SR_CORE_SENERROR,
			&(sr_status_regs[2].senerror));
		ret += mem_read(OMAP4430_SR_CORE_ERRCONFIG,
			&(sr_status_regs[2].errconfig));
		ret += mem_read(OMAP4430_PRM_VP_CORE_CONFIG,
			&(sr_status_regs[2].vp_config));
	}

	if (ret != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	if ((sr_status_regs[0].enabled == 0) &&
		(sr_status_regs[1].enabled == 0) &&
		(sr_status_regs[2].enabled == 0)) {
		printf("All Smart-Reflex Modules disabled.\n\n");
		return 0;
	}

	return sr_convergence_status_show(stream, sr_status_regs);
}


/* #define OMAP4CONF_SR_VOLTAGE_SET_DEBUG */
#ifndef SR44XX_DEBUG
#ifdef OMAP4CONF_SR_VOLTAGE_SET_DEBUG
#undef dprintf
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#endif
#endif
/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr44xx_voltage_set
 * @BRIEF		set voltage of a voltage domain using VC bypass method
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in]		vdd_id: voltage domain ID
 * @param[in]		uv: supply voltage (in uV)
 * @DESCRIPTION		set voltage of a voltage domain using VC bypass method
 *			NB: automatically disable SmartReflex (if enabled).
 *			NB: do not re-enable smartreflex afterwards or
 *			new voltage will be overriden.
 *//*------------------------------------------------------------------------ */
int sr44xx_voltage_set(unsigned int vdd_id, unsigned long uv)
{
	omap4_sr_module_id sr_id;
	FILE *fp;
	int ret;
	unsigned char vsel, vsel_len;
	unsigned int vc_bypass_value;
	unsigned int volt_reg_addr;
	char voltdm_name[VOLTDM44XX_MAX_NAME_LENGTH];
	unsigned char VR_slave_address;
	unsigned int prm_vc_val_cmd_vdd, prm_vc_val_cmd_vdd_addr;

	static const char filename[OMAP4_SR_ID_MAX][72] = {
		"/sys/kernel/debug/pm_debug/smartreflex/sr_mpu/autocomp",
		"/sys/kernel/debug/pm_debug/smartreflex/sr_iva/autocomp",
		"/sys/kernel/debug/pm_debug/smartreflex/sr_core/autocomp"};

	if (!cpu_is_omap44xx())
		return OMAPCONF_ERR_CPU;
	if ((uv < OMAP4_VOLTAGE_MIN) || (uv > OMAP4_VOLTAGE_MAX)) {
		fprintf(stderr, "Error: voltage out of range! (%1.3lfV)\n",
			(double) ((double) uv / 1000000.0));
		return OMAPCONF_ERR_ARG;
	}
	if (cpu_is_omap4470()) {
		switch (vdd_id) {
		case OMAP4_VDD_MPU:
			sr_id = OMAP4_SR_MPU;
			VR_slave_address = PMIC_SLAVE_ADDR;
			volt_reg_addr = VOLT_REG_MPU_ADDR;
			prm_vc_val_cmd_vdd_addr =
				OMAP4430_PRM_VC_VAL_CMD_VDD_MPU_L;
			break;
		case OMAP4_VDD_IVA:
			sr_id = OMAP4_SR_IVA;
			VR_slave_address = PMIC_SLAVE_ADDR;
			volt_reg_addr = OMAP4470_VOLT_REG_IVA_ADDR;
			prm_vc_val_cmd_vdd_addr =
				OMAP4430_PRM_VC_VAL_CMD_VDD_IVA_L;
			break;
		case OMAP4_VDD_CORE:
			sr_id = OMAP4_SR_CORE;
			VR_slave_address = PMIC_SLAVE_ADDR;
			volt_reg_addr = OMAP4470_VOLT_REG_CORE_ADDR;
			prm_vc_val_cmd_vdd_addr =
				OMAP4430_PRM_VC_VAL_CMD_VDD_CORE_L;
			break;
		default:
			fprintf(stderr, "Error: invalid voltage domain ID! "
					"(%d)\n", vdd_id);
			return OMAPCONF_ERR_ARG;
		}
	} else if (cpu_is_omap4460()) {
		switch (vdd_id) {
		case OMAP4_VDD_MPU:
			sr_id = OMAP4_SR_MPU;
			VR_slave_address = TPS62361_SLAVE_ADDR;
			volt_reg_addr = TPS62361_VOLT_REG_ADDR;
			prm_vc_val_cmd_vdd_addr =
				OMAP4430_PRM_VC_VAL_CMD_VDD_MPU_L;
			break;
		case OMAP4_VDD_IVA:
			sr_id = OMAP4_SR_IVA;
			VR_slave_address = PMIC_SLAVE_ADDR;
			volt_reg_addr = VOLT_REG_IVA_ADDR;
			prm_vc_val_cmd_vdd_addr =
				OMAP4430_PRM_VC_VAL_CMD_VDD_IVA_L;
			break;
		case OMAP4_VDD_CORE:
			sr_id = OMAP4_SR_CORE;
			VR_slave_address = PMIC_SLAVE_ADDR;
			volt_reg_addr = OMAP4460_VOLT_REG_CORE_ADDR;
			prm_vc_val_cmd_vdd_addr =
				OMAP4430_PRM_VC_VAL_CMD_VDD_CORE_L;
			break;
		default:
			fprintf(stderr, "Error: invalid voltage domain ID! "
					"(%d)\n", vdd_id);
			return OMAPCONF_ERR_ARG;
		}
	} else { /* 4430 */
		switch (vdd_id) {
		case OMAP4_VDD_MPU:
			sr_id = OMAP4_SR_MPU;
			VR_slave_address = PMIC_SLAVE_ADDR;
			volt_reg_addr = VOLT_REG_MPU_ADDR;
			prm_vc_val_cmd_vdd_addr =
				OMAP4430_PRM_VC_VAL_CMD_VDD_CORE_L;
			break;
		case OMAP4_VDD_IVA:
			sr_id = OMAP4_SR_IVA;
			VR_slave_address = PMIC_SLAVE_ADDR;
			volt_reg_addr = VOLT_REG_IVA_ADDR;
			prm_vc_val_cmd_vdd_addr =
				OMAP4430_PRM_VC_VAL_CMD_VDD_CORE_L;
			break;
		case OMAP4_VDD_CORE:
			sr_id = OMAP4_SR_CORE;
			VR_slave_address = PMIC_SLAVE_ADDR;
			volt_reg_addr = VOLT_REG_CORE_ADDR;
			prm_vc_val_cmd_vdd_addr =
				OMAP4430_PRM_VC_VAL_CMD_VDD_CORE_L;
			break;
		default:
			fprintf(stderr, "Error: invalid voltage domain ID! "
					"(%d)\n", vdd_id);
			return OMAPCONF_ERR_ARG;
		}
	}

	dprintf("%s(%d, %lduV): sr_id=0x%02X VR_slave_address=0x%02X "
		"volt_reg_addr=0x%02X\n", __func__, vdd_id, uv,
		sr_id, VR_slave_address, volt_reg_addr);

	/* Smartreflex must not be running, disable it */
	if (sr44xx_is_enabled(sr_id)) {
		printf("Warning: %s smartreflex is enabled. Disabling it.\n",
			voltdm44xx_get_name(vdd_id, voltdm_name));
		fp = fopen(filename[sr_id], "w");
		if (fp == NULL) {
			fprintf(stderr,
				"Could not open %s! Is debugfs mounted???\n\n",
				filename[sr_id]);
			return OMAPCONF_ERR_NOT_AVAILABLE;
		}
		ret = fwrite("0", sizeof(char), 1, fp);
		fclose(fp);
		if (ret != 1) {
			fprintf(stderr, "Could not write into %s!\n\n",
				filename[sr_id]);
			return OMAPCONF_ERR_UNEXPECTED;
		}
		printf("Smartreflex disabled.\n");
	}

	/* Get vsel corresponding to target voltage */
	vsel = smps_uvolt2vsel(vdd_id2smps_id(vdd_id), uv);
	dprintf("%s(): domain=%s, target voltage=%lfV, "
		"target vsel=0x%02X\n", __func__,
		voltdm44xx_get_name(vdd_id, voltdm_name),
		(double) ((double) uv / 1000000.0), vsel);

	/* Use VC BYPASS method to change voltage */
	vc_bypass_value = (vsel << VC_BYPASS_DATA_SHIFT) |
			(volt_reg_addr << VC_BYPASS_REG_ADDR_SHIFT) |
			(VR_slave_address << VC_BYPASS_SLAVE_ADDR_SHIFT);
	dprintf("vc_bypass_value = 0x%08X\n", vc_bypass_value);

	ret = mem_write(OMAP4430_PRM_VC_VAL_BYPASS, vc_bypass_value);
	if (ret != 0) {
		fprintf(stderr, "Error: could not write into "
			"PRM_VC_VAL_BYPASS register!!! (%d)\n\n", ret);
		return OMAPCONF_ERR_REG_ACCESS;
	}

	vc_bypass_value |= VC_BYPASS_CMD_VALID_MASK;
	dprintf("vc_bypass_value = 0x%08X\n", vc_bypass_value);

	ret = mem_write(OMAP4430_PRM_VC_VAL_BYPASS, vc_bypass_value);
	if (ret != 0) {
		fprintf(stderr, "Error: could not write into "
			"PRM_VC_VAL_BYPASS register!!! (%d)\n\n", ret);
		return OMAPCONF_ERR_REG_ACCESS;
	}

	/* Wait for VC BYPASS command to be acknowledge */
	dprintf("%s(): Wait for VC BYPASS command to be acknowledged...\n",
		__func__);
	do {
		ret = mem_read(OMAP4430_PRM_VC_VAL_BYPASS, &vc_bypass_value);
		if (ret != 0) {
			fprintf(stderr, "Error: could not read "
				"PRM_VC_VAL_BYPASS register!!! (%d)\n\n", ret);
			return OMAPCONF_ERR_REG_ACCESS;
		}
	} while ((vc_bypass_value & VC_BYPASS_CMD_VALID_MASK) != 0);

	dprintf("%s supply voltage set to %lfV.\n",
		voltdm44xx_get_name(vdd_id, voltdm_name),
		(double) ((double) uv / 1000000.0));

	/*
	 * Update VC ONVALUE voltage, so that new voltage does not get lost
	 * after a power transition on this domain
	 */
	/* Get currently programmed voltage from VC register */
	dprintf("%s(): Get currently programmed voltage "
		"(prm_vc_val_cmd_vdd_addr=0x%08X)\n", __func__,
		prm_vc_val_cmd_vdd_addr);
	if (mem_read(prm_vc_val_cmd_vdd_addr, &prm_vc_val_cmd_vdd) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (cpu_is_omap4460() && (vdd_id == OMAP4_VDD_MPU))
		/* TPS62361 vsel length is 8-bit, not 6-bit as for TWL6030 */
		vsel_len = 8;
	else
		vsel_len = 6;
	dprintf("%s(): %s: prm_vc_val_cmd_vdd=0x%08X, vsel_len=%u\n",
		__func__, voltdm44xx_get_name(vdd_id, voltdm_name),
		prm_vc_val_cmd_vdd, vsel_len);
	prm_vc_val_cmd_vdd &= ~(((1 << vsel_len) - 1) << OMAP4_ON_VOLTAGE);
	prm_vc_val_cmd_vdd |= (vsel << OMAP4_ON_VOLTAGE);
	dprintf("%s(): %s: now prm_vc_val_cmd_vdd = 0x%08X\n", __func__,
		voltdm44xx_get_name(vdd_id, voltdm_name), prm_vc_val_cmd_vdd);
	mem_write(prm_vc_val_cmd_vdd_addr, prm_vc_val_cmd_vdd);

	return 0;
}
#ifndef SR44XX_DEBUG
#ifdef OMAP4CONF_SR_VOLTAGE_SET_DEBUG
#undef dprintf
#define dprintf(format, ...)
#endif
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr44xx_config_show
 * @BRIEF		Print SR configuration
 *			(incl. SR modules (MPU, IVA, CORE), VP, VC).
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		stream: output file
 * @DESCRIPTION		Print SR configuration
 *			(incl. SR modules (MPU, IVA, CORE), VP, VC).
 *//*------------------------------------------------------------------------ */
int sr44xx_config_show(FILE *stream)
{
	int ret;

	ret = sr44xx_vc_config();
	ret |= vp44xx_config_show(stream);
	ret |= sr44xx_module_config();
	ret |= sr44xx_status_show(stream);

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr44xx_audit
 * @BRIEF		audit SR settings
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output file (NULL: no output (silent))
 * @param[in]		sr_id: SR module ID
 *				(use OMAP4_SR_ID_MAX to audit all modules)
 * @param[in,out]	err_nbr: error number
 * @param[in,out]	wng_nbr: warning number
 * @DESCRIPTION		audit SR settings, by comparing current settings with
 *			predefined "golden" settings.
 *//*------------------------------------------------------------------------ */
int sr44xx_audit(FILE *stream, omap4_sr_module_id sr_id,
	unsigned int *err_nbr, unsigned int *wng_nbr)
{
	sr_registers sr_regs;
	const sr_audit_settings *sr_golden_settings;
	omap4_sr_module_id id;
	opp44xx_id opp;
	int ret = 0;
	unsigned int err_cnt, wng_cnt;
	char opp_name[OPP44XX_MAX_NAME_LENGTH];

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(err_nbr, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(wng_nbr, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(sr_id, OMAP4_SR_ID_MAX + 1, OMAPCONF_ERR_ARG);

	*err_nbr = 0;
	*wng_nbr = 0;
	for (id = OMAP4_SR_MPU; id < OMAP4_SR_ID_MAX; id++) {
		if ((sr_id != OMAP4_SR_ID_MAX) && (sr_id != id))
			continue;

		dprintf("\n%s(): Auditing %s\n", __func__,
			sr44xx_name_get(id));
		err_cnt = 0;
		wng_cnt = 0;
		/* Get SR module registers content */
		ret = sr44xx_registers_get(id, &sr_regs);
		if (ret != 0) {
			(*err_nbr) += 1;
			return ret;
		}
		if (sr_regs.accessible == 0) {
			(*wng_nbr) += 1;
			if (stream != NULL) {
				fprintf(stream, "Warning: %s is disabled, audit"
					" cannot be run.\n",
					sr44xx_name_get(id));
			}
			continue;
		}

		/* Get OPP */
		switch (id) {
		case OMAP4_SR_MPU:
			ret = voltdm44xx_get_opp(OMAP4_VDD_MPU, &opp);
			voltdm44xx_opp2string(opp_name, opp, OMAP4_VDD_MPU);
			dprintf("  OPP is %s\n", opp_name);
			break;

		case OMAP4_SR_IVA:
			ret = voltdm44xx_get_opp(OMAP4_VDD_IVA, &opp);
			voltdm44xx_opp2string(opp_name, opp, OMAP4_VDD_IVA);
			dprintf("  OPP is %s\n", opp_name);
			break;

		case OMAP4_SR_CORE:
			ret = voltdm44xx_get_opp(OMAP4_VDD_CORE, &opp);
			voltdm44xx_opp2string(opp_name, opp, OMAP4_VDD_CORE);
			dprintf("  OPP is %s\n", opp_name);
			break;

		default:
			(*err_nbr) += 1;
			fprintf(stderr, "unexpected id! (%u)\n", id);
			return OMAPCONF_ERR_UNEXPECTED;
		}
		if (ret != 0) {
			(*wng_nbr) += 1;
			if (stream != NULL) {
				fprintf(stream, "Warning: could not find OPP,"
					" audit cannot be run.\n");
			}
			continue;
		}

		/* Get expected ("golden") settings */
		sr_golden_settings = sr44xx_golden_settings_get(id, opp);
		if (sr_golden_settings == NULL) {
			(*wng_nbr) += 1;
			if (stream != NULL) {
				fprintf(stream, "Warning: could not find golden"
					" settings, audit cannot be run.\n");
			}
			continue;
		}

		/* Audit settings */
		ret = sr_config_audit(stream, sr44xx_name_get(id), opp_name,
			&sr_regs, sr_golden_settings, &err_cnt, &wng_cnt);
		(*err_nbr) += err_cnt;
		(*wng_nbr) += wng_cnt;
		if (ret != 0)
			return ret;
	}

	if (stream != NULL) {
		if (*err_nbr == 0)
			fprintf(stream,
				"\nSUCCESS! SR Configuration Audit "
				"completed with 0 error (%u warning(s)).\n\n",
				*wng_nbr);
		else
			fprintf(stream,
				"\nFAILED! SR Configuration Audit "
				"completed with %u error(s) and %u warning(s)."
				"\n\n", *err_nbr, *wng_nbr);
	}

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr44xx_regtable_init
 * @BRIEF		initialize regtable
 * @RETURNS		0
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		initialize regtable
 *//*------------------------------------------------------------------------ */
static int sr44xx_regtable_init(void)
{
	int i = 0;

	if (!cpu_is_omap44xx())
		return OMAPCONF_ERR_CPU;

	/* Init PRCM registers table */
	/* SR_MPU */
	strcpy(prcm_sr_mpu_reg_table[i].name, "SRCONFIG_MPU");
	prcm_sr_mpu_reg_table[i++].addr = OMAP4430_SR_MPU_SRCONFIG;
	strcpy(prcm_sr_mpu_reg_table[i].name, "SRSTATUS_MPU");
	prcm_sr_mpu_reg_table[i++].addr = OMAP4430_SR_MPU_SRSTATUS;
	strcpy(prcm_sr_mpu_reg_table[i].name, "SENVAL_MPU");
	prcm_sr_mpu_reg_table[i++].addr = OMAP4430_SR_MPU_SENVAL;
	strcpy(prcm_sr_mpu_reg_table[i].name, "SENMIN_MPU");
	prcm_sr_mpu_reg_table[i++].addr = OMAP4430_SR_MPU_SENMIN;
	strcpy(prcm_sr_mpu_reg_table[i].name, "SENMAX_MPU");
	prcm_sr_mpu_reg_table[i++].addr = OMAP4430_SR_MPU_SENMAX;
	strcpy(prcm_sr_mpu_reg_table[i].name, "SENAVG_MPU");
	prcm_sr_mpu_reg_table[i++].addr = OMAP4430_SR_MPU_SENAVG;
	strcpy(prcm_sr_mpu_reg_table[i].name, "AVGWEIGHT_MPU");
	prcm_sr_mpu_reg_table[i++].addr = OMAP4430_SR_MPU_AVGWEIGHT;
	strcpy(prcm_sr_mpu_reg_table[i].name, "NVALUERECIPROCAL_MPU");
	prcm_sr_mpu_reg_table[i++].addr = OMAP4430_SR_MPU_NVALUERECIPROCAL;
	strcpy(prcm_sr_mpu_reg_table[i].name, "IRQSTATUS_RAW_MPU");
	prcm_sr_mpu_reg_table[i++].addr = OMAP4430_SR_MPU_IRQSTATUS_RAW;
	strcpy(prcm_sr_mpu_reg_table[i].name, "IRQSTATUS_MPU");
	prcm_sr_mpu_reg_table[i++].addr = OMAP4430_SR_MPU_IRQSTATUS;
	strcpy(prcm_sr_mpu_reg_table[i].name, "IRQENABLE_SET_MPU");
	prcm_sr_mpu_reg_table[i++].addr = OMAP4430_SR_MPU_IRQENABLE_SET;
	strcpy(prcm_sr_mpu_reg_table[i].name, "IRQENABLE_CLR_MPU");
	prcm_sr_mpu_reg_table[i++].addr = OMAP4430_SR_MPU_IRQENABLE_CLR;
	strcpy(prcm_sr_mpu_reg_table[i].name, "SENERROR_MPU");
	prcm_sr_mpu_reg_table[i++].addr = OMAP4430_SR_MPU_SENERROR;
	strcpy(prcm_sr_mpu_reg_table[i].name, "ERRCONFIG_MPU");
	prcm_sr_mpu_reg_table[i++].addr = OMAP4430_SR_MPU_ERRCONFIG;
	strcpy(prcm_sr_mpu_reg_table[i].name, "END");
	prcm_sr_mpu_reg_table[i].addr = 0;
	dprintf("prcm_sr_mpu_reg_table last index=%d, size=%d\n", i, i + 1);

	/* VP_MPU */
	i = 0;
	strcpy(prcm_sr_vp_mpu_reg_table[i].name, "PRM_VP_MPU_CONFIG");
	prcm_sr_vp_mpu_reg_table[i++].addr = OMAP4430_PRM_VP_MPU_CONFIG;
	strcpy(prcm_sr_vp_mpu_reg_table[i].name, "PRM_VP_MPU_STATUS");
	prcm_sr_vp_mpu_reg_table[i++].addr = OMAP4430_PRM_VP_MPU_STATUS;
	strcpy(prcm_sr_vp_mpu_reg_table[i].name, "PRM_VP_MPU_VLIMITTO");
	prcm_sr_vp_mpu_reg_table[i++].addr = OMAP4430_PRM_VP_MPU_VLIMITTO;
	strcpy(prcm_sr_vp_mpu_reg_table[i].name, "PRM_VP_MPU_VOLTAGE");
	prcm_sr_vp_mpu_reg_table[i++].addr = OMAP4430_PRM_VP_MPU_VOLTAGE;
	strcpy(prcm_sr_vp_mpu_reg_table[i].name, "PRM_VP_MPU_VSTEPMAX");
	prcm_sr_vp_mpu_reg_table[i++].addr = OMAP4430_PRM_VP_MPU_VSTEPMAX;
	strcpy(prcm_sr_vp_mpu_reg_table[i].name, "PRM_VP_MPU_VSTEPMIN");
	prcm_sr_vp_mpu_reg_table[i++].addr = OMAP4430_PRM_VP_MPU_VSTEPMIN;
	strcpy(prcm_sr_vp_mpu_reg_table[i].name, "END");
	prcm_sr_vp_mpu_reg_table[i].addr = 0;
	dprintf("prcm_sr_vp_mpu_reg_table last index=%d, size=%d\n", i, i + 1);

	/* SR_IVA */
	i = 0;
	strcpy(prcm_sr_iva_reg_table[i].name, "SRCONFIG_IVA");
	prcm_sr_iva_reg_table[i++].addr = OMAP4430_SR_IVA_SRCONFIG;
	strcpy(prcm_sr_iva_reg_table[i].name, "SRSTATUS_IVA");
	prcm_sr_iva_reg_table[i++].addr = OMAP4430_SR_IVA_SRSTATUS;
	strcpy(prcm_sr_iva_reg_table[i].name, "SENVAL_IVA");
	prcm_sr_iva_reg_table[i++].addr = OMAP4430_SR_IVA_SENVAL;
	strcpy(prcm_sr_iva_reg_table[i].name, "SENMIN_IVA");
	prcm_sr_iva_reg_table[i++].addr = OMAP4430_SR_IVA_SENMIN;
	strcpy(prcm_sr_iva_reg_table[i].name, "SENMAX_IVA");
	prcm_sr_iva_reg_table[i++].addr = OMAP4430_SR_IVA_SENMAX;
	strcpy(prcm_sr_iva_reg_table[i].name, "SENAVG_IVA");
	prcm_sr_iva_reg_table[i++].addr = OMAP4430_SR_IVA_SENAVG;
	strcpy(prcm_sr_iva_reg_table[i].name, "AVGWEIGHT_IVA");
	prcm_sr_iva_reg_table[i++].addr = OMAP4430_SR_IVA_AVGWEIGHT;
	strcpy(prcm_sr_iva_reg_table[i].name, "NVALUERECIPROCAL_IVA");
	prcm_sr_iva_reg_table[i++].addr = OMAP4430_SR_IVA_NVALUERECIPROCAL;
	strcpy(prcm_sr_iva_reg_table[i].name, "IRQSTATUS_RAW_IVA");
	prcm_sr_iva_reg_table[i++].addr = OMAP4430_SR_IVA_IRQSTATUS_RAW;
	strcpy(prcm_sr_iva_reg_table[i].name, "IRQSTATUS_IVA");
	prcm_sr_iva_reg_table[i++].addr = OMAP4430_SR_IVA_IRQSTATUS;
	strcpy(prcm_sr_iva_reg_table[i].name, "IRQENABLE_SET_IVA");
	prcm_sr_iva_reg_table[i++].addr = OMAP4430_SR_IVA_IRQENABLE_SET;
	strcpy(prcm_sr_iva_reg_table[i].name, "IRQENABLE_CLR_IVA");
	prcm_sr_iva_reg_table[i++].addr = OMAP4430_SR_IVA_IRQENABLE_CLR;
	strcpy(prcm_sr_iva_reg_table[i].name, "SENERROR_IVA");
	prcm_sr_iva_reg_table[i++].addr = OMAP4430_SR_IVA_SENERROR;
	strcpy(prcm_sr_iva_reg_table[i].name, "ERRCONFIG_IVA");
	prcm_sr_iva_reg_table[i++].addr = OMAP4430_SR_IVA_ERRCONFIG;
	strcpy(prcm_sr_iva_reg_table[i].name, "END");
	prcm_sr_iva_reg_table[i].addr = 0;
	dprintf("prcm_sr_iva_reg_table last index=%d, size=%d\n", i, i + 1);

	/* VP_IVA */
	i = 0;
	strcpy(prcm_sr_vp_iva_reg_table[i].name, "PRM_VP_IVA_CONFIG");
	prcm_sr_vp_iva_reg_table[i++].addr = OMAP4430_PRM_VP_IVA_CONFIG;
	strcpy(prcm_sr_vp_iva_reg_table[i].name, "PRM_VP_IVA_STATUS");
	prcm_sr_vp_iva_reg_table[i++].addr = OMAP4430_PRM_VP_IVA_STATUS;
	strcpy(prcm_sr_vp_iva_reg_table[i].name, "PRM_VP_IVA_VLIMITTO");
	prcm_sr_vp_iva_reg_table[i++].addr = OMAP4430_PRM_VP_IVA_VLIMITTO;
	strcpy(prcm_sr_vp_iva_reg_table[i].name, "PRM_VP_IVA_VOLTAGE");
	prcm_sr_vp_iva_reg_table[i++].addr = OMAP4430_PRM_VP_IVA_VOLTAGE;
	strcpy(prcm_sr_vp_iva_reg_table[i].name, "PRM_VP_IVA_VSTEPMAX");
	prcm_sr_vp_iva_reg_table[i++].addr = OMAP4430_PRM_VP_IVA_VSTEPMAX;
	strcpy(prcm_sr_vp_iva_reg_table[i].name, "PRM_VP_IVA_VSTEPMIN");
	prcm_sr_vp_iva_reg_table[i++].addr = OMAP4430_PRM_VP_IVA_VSTEPMIN;
	strcpy(prcm_sr_vp_iva_reg_table[i].name, "END");
	prcm_sr_vp_iva_reg_table[i].addr = 0;
	dprintf("prcm_sr_vp_iva_reg_table last index=%d, size=%d\n", i, i + 1);

	/* SR_CORE */
	i = 0;
	strcpy(prcm_sr_core_reg_table[i].name, "SRCONFIG_CORE");
	prcm_sr_core_reg_table[i++].addr = OMAP4430_SR_CORE_SRCONFIG;
	strcpy(prcm_sr_core_reg_table[i].name, "SRSTATUS_CORE");
	prcm_sr_core_reg_table[i++].addr = OMAP4430_SR_CORE_SRSTATUS;
	strcpy(prcm_sr_core_reg_table[i].name, "SENVAL_CORE");
	prcm_sr_core_reg_table[i++].addr = OMAP4430_SR_CORE_SENVAL;
	strcpy(prcm_sr_core_reg_table[i].name, "SENMIN_CORE");
	prcm_sr_core_reg_table[i++].addr = OMAP4430_SR_CORE_SENMIN;
	strcpy(prcm_sr_core_reg_table[i].name, "SENMAX_CORE");
	prcm_sr_core_reg_table[i++].addr = OMAP4430_SR_CORE_SENMAX;
	strcpy(prcm_sr_core_reg_table[i].name, "SENAVG_CORE");
	prcm_sr_core_reg_table[i++].addr = OMAP4430_SR_CORE_SENAVG;
	strcpy(prcm_sr_core_reg_table[i].name, "AVGWEIGHT_CORE");
	prcm_sr_core_reg_table[i++].addr = OMAP4430_SR_CORE_AVGWEIGHT;
	strcpy(prcm_sr_core_reg_table[i].name, "NVALUERECIPROCAL_CORE");
	prcm_sr_core_reg_table[i++].addr = OMAP4430_SR_CORE_NVALUERECIPROCAL;
	strcpy(prcm_sr_core_reg_table[i].name, "IRQSTATUS_RAW_CORE");
	prcm_sr_core_reg_table[i++].addr = OMAP4430_SR_CORE_IRQSTATUS_RAW;
	strcpy(prcm_sr_core_reg_table[i].name, "IRQSTATUS_CORE");
	prcm_sr_core_reg_table[i++].addr = OMAP4430_SR_CORE_IRQSTATUS;
	strcpy(prcm_sr_core_reg_table[i].name, "IRQENABLE_SET_CORE");
	prcm_sr_core_reg_table[i++].addr = OMAP4430_SR_CORE_IRQENABLE_SET;
	strcpy(prcm_sr_core_reg_table[i].name, "IRQENABLE_CLR_CORE");
	prcm_sr_core_reg_table[i++].addr = OMAP4430_SR_CORE_IRQENABLE_CLR;
	strcpy(prcm_sr_core_reg_table[i].name, "SENERROR_CORE");
	prcm_sr_core_reg_table[i++].addr = OMAP4430_SR_CORE_SENERROR;
	strcpy(prcm_sr_core_reg_table[i].name, "ERRCONFIG_CORE");
	prcm_sr_core_reg_table[i++].addr = OMAP4430_SR_CORE_ERRCONFIG;
	strcpy(prcm_sr_core_reg_table[i].name, "END");
	prcm_sr_core_reg_table[i].addr = 0;
	dprintf("prcm_sr_core_reg_table last index=%d, size=%d\n", i, i + 1);

	/* VP_CORE */
	i = 0;
	strcpy(prcm_sr_vp_core_reg_table[i].name, "PRM_VP_CORE_CONFIG");
	prcm_sr_vp_core_reg_table[i++].addr = OMAP4430_PRM_VP_CORE_CONFIG;
	strcpy(prcm_sr_vp_core_reg_table[i].name, "PRM_VP_CORE_STATUS");
	prcm_sr_vp_core_reg_table[i++].addr = OMAP4430_PRM_VP_CORE_STATUS;
	strcpy(prcm_sr_vp_core_reg_table[i].name, "PRM_VP_CORE_VLIMITTO");
	prcm_sr_vp_core_reg_table[i++].addr = OMAP4430_PRM_VP_CORE_VLIMITTO;
	strcpy(prcm_sr_vp_core_reg_table[i].name, "PRM_VP_CORE_VOLTAGE");
	prcm_sr_vp_core_reg_table[i++].addr = OMAP4430_PRM_VP_CORE_VOLTAGE;
	strcpy(prcm_sr_vp_core_reg_table[i].name, "PRM_VP_CORE_VSTEPMAX");
	prcm_sr_vp_core_reg_table[i++].addr = OMAP4430_PRM_VP_CORE_VSTEPMAX;
	strcpy(prcm_sr_vp_core_reg_table[i].name, "PRM_VP_CORE_VSTEPMIN");
	prcm_sr_vp_core_reg_table[i++].addr = OMAP4430_PRM_VP_CORE_VSTEPMIN;
	strcpy(prcm_sr_vp_core_reg_table[i].name, "END");
	prcm_sr_vp_core_reg_table[i].addr = 0;
	dprintf("prcm_sr_vp_core_reg_table last index=%d, size=%d\n", i, i + 1);

	/* VC */
	i = 0;
	strcpy(prcm_sr_vc_reg_table[i].name, "PRM_VC_SMPS_SA");
	prcm_sr_vc_reg_table[i++].addr = OMAP4430_PRM_VC_SMPS_SA;
	strcpy(prcm_sr_vc_reg_table[i].name, "PRM_VC_VAL_SMPS_RA_VOL");
	prcm_sr_vc_reg_table[i++].addr = OMAP4430_PRM_VC_VAL_SMPS_RA_VOL;
	strcpy(prcm_sr_vc_reg_table[i].name, "PRM_VC_VAL_SMPS_RA_CMD");
	prcm_sr_vc_reg_table[i++].addr = OMAP4430_PRM_VC_VAL_SMPS_RA_CMD;
	strcpy(prcm_sr_vc_reg_table[i].name, "PRM_VC_VAL_CMD_VDD_CORE_L");
	prcm_sr_vc_reg_table[i++].addr = OMAP4430_PRM_VC_VAL_CMD_VDD_CORE_L;
	strcpy(prcm_sr_vc_reg_table[i].name, "PRM_VC_VAL_CMD_VDD_MPU_L");
	prcm_sr_vc_reg_table[i++].addr = OMAP4430_PRM_VC_VAL_CMD_VDD_MPU_L;
	strcpy(prcm_sr_vc_reg_table[i].name, "PRM_VC_VAL_CMD_VDD_IVA_L");
	prcm_sr_vc_reg_table[i++].addr = OMAP4430_PRM_VC_VAL_CMD_VDD_IVA_L;
	strcpy(prcm_sr_vc_reg_table[i].name, "PRM_VC_VAL_BYPASS");
	prcm_sr_vc_reg_table[i++].addr = OMAP4430_PRM_VC_VAL_BYPASS;
	strcpy(prcm_sr_vc_reg_table[i].name, "PRM_VC_CFG_CHANNEL");
	prcm_sr_vc_reg_table[i++].addr = OMAP4430_PRM_VC_CFG_CHANNEL;
	strcpy(prcm_sr_vc_reg_table[i].name, "PRM_VC_CFG_I2C_MODE");
	prcm_sr_vc_reg_table[i++].addr = OMAP4430_PRM_VC_CFG_I2C_MODE;
	strcpy(prcm_sr_vc_reg_table[i].name, "PRM_VC_CFG_I2C_CLK");
	prcm_sr_vc_reg_table[i++].addr = OMAP4430_PRM_VC_CFG_I2C_CLK;
	strcpy(prcm_sr_vc_reg_table[i].name, "END");
	prcm_sr_vc_reg_table[i].addr = 0;
	dprintf("prcm_sr_vc_reg_table last index=%d, size=%d\n", i, i + 1);

	init_done = 1;
	return 0;
}
