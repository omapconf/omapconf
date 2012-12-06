/*
 *
 * @Component			OMAPCONF
 * @Filename			vc54xx.c
 * @Description			OMAP5 VOLTAGE CONTROLLER (VC) Definitions & Functions
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


#include <vc54xx.h>
#include <prm54xx.h>
#include <vc.h>
#include <lib.h>
#include <cpuinfo.h>
#include <autoadjust_table.h>
#include <pmic.h>


/* #define VC54XX_DEBUG */
#ifdef VC54XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static const char
	vc54xx_vfsm_error_type_names[VC54XX_VFSM_ERR_TYPE_MAX + 1][VC54XX_ERR_NAME_MAX_LENGTH] = {
	"VFSM Timeout Error",
	"VFSM RA Error",
	"VFSM SA Error",
	"FIXME"};


static const char
	vc54xx_smps_error_type_names[VC54XX_SMPS_ERR_TYPE_MAX + 1][VC54XX_ERR_NAME_MAX_LENGTH] = {
	"SMPS Timeout Error",
	"SMPS RA Error",
	"SMPS SA Error",
	"FIXME"};


static const char
	vc54xx_bypass_error_type_names[VC54XX_BYPS_ERR_TYPE_MAX + 1][VC54XX_ERR_NAME_MAX_LENGTH] = {
	"Bypass Timeout Error",
	"Bypass RA Error",
	"Bypass SA Error",
	"FIXME"};


#define VC_CMD_SET_SELECT_POS		28
#define VC_RACEN_POS			27
#define VC_RAC_POS			26
#define VC_RAV_POS			25
#define VC_SEL_SA_POS			24
#define VC_CMDRA_POS			16
#define VC_CMDRA_LEN			8
#define VC_VOLRA_POS			8
#define VC_VOLRA_LEN			8
#define VC_SA_POS			0
#define VC_SA_LEN			7

#define VC_OPP_CHANGE_EMIF_LVL_POS	25
#define VC_DATA_POS			16
#define VC_DATA_LEN			8
#define VC_REGADDR_POS			8
#define VC_REGADDR_LEN			8
#define VC_SLAVEADDR_POS		0
#define VC_SLAVEADDR_LEN		7

#define VC_VFSM_TIMEOUT_ERR_POS		5
#define VC_VFSM_RA_ERR_POS		4
#define VC_VFSM_SA_ERR_POS		3
#define VC_SMPS_TIMEOUT_ERR_POS		2
#define VC_SMPS_RA_ERR_POS		1
#define VC_SMPS_SA_ERR_POS		0

#define VC_BYPS_TIMEOUT_ERR_POS		2
#define VC_BYPS_RA_ERR_POS		1
#define VC_BYPS_SA_ERR_POS		0


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vc54xx_vfsm_error_name_get
 * @BRIEF		return VFSM error type name
 * @RETURNS		VFSM error type on success
 *			"FIXME" string in case of error
 * @param[in]		type: valid VFSM error type
 * @DESCRIPTION		return VFSM error type name
 *//*------------------------------------------------------------------------ */
const char *vc54xx_vfsm_error_name_get(vc54xx_vfsm_error_type type)
{
	if (type < VC54XX_VFSM_ERR_TYPE_MAX)
		return vc54xx_vfsm_error_type_names[type];
	else
		return vc54xx_vfsm_error_type_names[VC54XX_VFSM_ERR_TYPE_MAX];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vc54xx_smps_error_name_get
 * @BRIEF		return SMPS error type name
 * @RETURNS		SMPS error type on success
 *			"FIXME" string in case of error
 * @param[in]		type: valid SMPS error type
 * @DESCRIPTION		return SMPS error type name
 *//*------------------------------------------------------------------------ */
const char *vc54xx_smps_error_name_get(vc54xx_smps_error_type type)
{
	if (type < VC54XX_SMPS_ERR_TYPE_MAX)
		return vc54xx_smps_error_type_names[type];
	else
		return vc54xx_smps_error_type_names[VC54XX_SMPS_ERR_TYPE_MAX];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vc54xx_bypass_error_name_get
 * @BRIEF		return BYPASS error type name
 * @RETURNS		BYPASS error type on success
 *			"FIXME" string in case of error
 * @param[in]		type: valid BYPASS error type
 * @DESCRIPTION		return BYPASS error type name
 *//*------------------------------------------------------------------------ */
const char *vc54xx_bypass_error_name_get(vc54xx_bypass_error_type type)
{
	if (type < VC54XX_BYPS_ERR_TYPE_MAX)
		return vc54xx_bypass_error_type_names[type];
	else
		return vc54xx_bypass_error_type_names[VC54XX_BYPS_ERR_TYPE_MAX];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vc54xx_registers_get
 * @BRIEF		save all VC registers in structure provided as argument.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in, out]	vc_regs: structure where to store VC registers
 * @DESCRIPTION		save all VC registers in structure provided as argument.
 *//*------------------------------------------------------------------------ */
int vc54xx_registers_get(vc54xx_registers *vc_regs)
{
	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(vc_regs, OMAPCONF_ERR_ARG);

	if (cpu_revision_get() == REV_ES1_0) {
		vc_regs->vc_smps_mpu_config =
			reg_read(&omap5430es1_prm_vc_smps_mpu_config);
		vc_regs->vc_smps_mm_config =
			reg_read(&omap5430es1_prm_vc_smps_mm_config);
		vc_regs->vc_smps_core_config =
			reg_read(&omap5430es1_prm_vc_smps_core_config);
		vc_regs->vc_val_cmd_vdd_mpu_l =
			reg_read(&omap5430es1_prm_vc_val_cmd_vdd_mpu_l);
		vc_regs->vc_val_cmd_vdd_mm_l =
			reg_read(&omap5430es1_prm_vc_val_cmd_vdd_mm_l);
		vc_regs->vc_val_cmd_vdd_core_l =
			reg_read(&omap5430es1_prm_vc_val_cmd_vdd_core_l);
		vc_regs->vc_val_bypass =
			reg_read(&omap5430es1_prm_vc_val_bypass);
		vc_regs->vc_mpu_errst =
			reg_read(&omap5430es1_prm_vc_mpu_errst);
		vc_regs->vc_mm_errst =
			reg_read(&omap5430es1_prm_vc_mm_errst);
		vc_regs->vc_core_errst =
			reg_read(&omap5430es1_prm_vc_core_errst);
		vc_regs->vc_bypass_errst =
			reg_read(&omap5430es1_prm_vc_bypass_errst);
		vc_regs->vc_cfg_i2c_mode =
			reg_read(&omap5430es1_prm_vc_cfg_i2c_mode);
		vc_regs->vc_cfg_i2c_clk =
			reg_read(&omap5430es1_prm_vc_cfg_i2c_clk);
	} else {
		vc_regs->vc_smps_mpu_config =
			reg_read(&omap5430_prm_vc_smps_mpu_config);
		vc_regs->vc_smps_mm_config =
			reg_read(&omap5430_prm_vc_smps_mm_config);
		vc_regs->vc_smps_core_config =
			reg_read(&omap5430_prm_vc_smps_core_config);
		vc_regs->vc_val_cmd_vdd_mpu_l =
			reg_read(&omap5430_prm_vc_val_cmd_vdd_mpu_l);
		vc_regs->vc_val_cmd_vdd_mm_l =
			reg_read(&omap5430_prm_vc_val_cmd_vdd_mm_l);
		vc_regs->vc_val_cmd_vdd_core_l =
			reg_read(&omap5430_prm_vc_val_cmd_vdd_core_l);
		vc_regs->vc_val_bypass =
			reg_read(&omap5430_prm_vc_val_bypass);
		vc_regs->vc_mpu_errst =
			reg_read(&omap5430_prm_vc_mpu_errst);
		vc_regs->vc_mm_errst =
			reg_read(&omap5430_prm_vc_mm_errst);
		vc_regs->vc_core_errst =
			reg_read(&omap5430_prm_vc_core_errst);
		vc_regs->vc_bypass_errst =
			reg_read(&omap5430_prm_vc_bypass_errst);
		vc_regs->vc_cfg_i2c_mode =
			reg_read(&omap5430_prm_vc_cfg_i2c_mode);
		vc_regs->vc_cfg_i2c_clk =
			reg_read(&omap5430_prm_vc_cfg_i2c_clk);
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vc54xx_sa_get
 * @BRIEF		return Slave Address (SA)
 * @RETURNS		>0 Slave Address (SA)
 *			OMAPCONF_ERR_ARG
 * @param[in]		id: voltage domain ID
 * @param[in,out]	vc_regs: VC registers content
 * @DESCRIPTION		return Slave Address (SA)
 *//*------------------------------------------------------------------------ */
short int vc54xx_sa_get(voltdm54xx_id id, vc54xx_registers *vc_regs)
{
	short int sa;

	switch (id) {
	case VDD54XX_MPU:
		sa = extract_bitfield(vc_regs->vc_smps_mpu_config,
			VC_SA_POS, VC_SA_LEN);
		break;

	case VDD54XX_MM:
		if (extract_bit(vc_regs->vc_smps_mm_config,
			VC_SEL_SA_POS) == 1)
			sa = extract_bitfield(vc_regs->vc_smps_mm_config,
				VC_SA_POS, VC_SA_LEN);
		else
			sa = extract_bitfield(vc_regs->vc_smps_mpu_config,
				VC_SA_POS, VC_SA_LEN);
		break;

	case VDD54XX_CORE:
		if (extract_bit(vc_regs->vc_smps_core_config,
			VC_SEL_SA_POS) == 1)
			sa = extract_bitfield(vc_regs->vc_smps_core_config,
				VC_SA_POS, VC_SA_LEN);
		else
			sa = extract_bitfield(vc_regs->vc_smps_mpu_config,
				VC_SA_POS, VC_SA_LEN);
		break;

	default:
		sa = OMAPCONF_ERR_ARG;
	}

	return sa;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vc54xx_volra_get
 * @BRIEF		return Voltage Register Address (VOLRA)
 * @RETURNS		>0 Voltage Register Address (VOLRA)
 *			OMAPCONF_ERR_ARG
 * @param[in]		id: voltage domain ID
 * @param[in,out]	vc_regs: VC registers content
 * @DESCRIPTION		return Voltage Register Address (VOLRA)
 *//*------------------------------------------------------------------------ */
short int vc54xx_volra_get(voltdm54xx_id id, vc54xx_registers *vc_regs)
{
	short int volra;

	switch (id) {
	case VDD54XX_MPU:
		volra = extract_bitfield(vc_regs->vc_smps_mpu_config,
			VC_VOLRA_POS, VC_VOLRA_LEN);
		break;

	case VDD54XX_MM:
		if (extract_bit(vc_regs->vc_smps_mm_config,
			VC_RAV_POS) == 1)
			volra = extract_bitfield(vc_regs->vc_smps_mm_config,
				VC_VOLRA_POS, VC_VOLRA_LEN);
		else
			volra = extract_bitfield(vc_regs->vc_smps_mpu_config,
				VC_VOLRA_POS, VC_VOLRA_LEN);
		break;

	case VDD54XX_CORE:
		if (extract_bit(vc_regs->vc_smps_core_config,
			VC_RAV_POS) == 1)
			volra = extract_bitfield(vc_regs->vc_smps_core_config,
				VC_VOLRA_POS, VC_VOLRA_LEN);
		else
			volra = extract_bitfield(vc_regs->vc_smps_mpu_config,
				VC_VOLRA_POS, VC_VOLRA_LEN);
		break;

	default:
		volra = OMAPCONF_ERR_ARG;
	}

	return volra;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vc54xx_cmdra_get
 * @BRIEF		return Command Register Address (CMDRA)
 * @RETURNS		>0 Voltage Register Address (CMDRA)
 *			OMAPCONF_ERR_ARG
 * @param[in]		id: voltage domain ID
 * @param[in,out]	vc_regs: VC registers content
 * @DESCRIPTION		return Command Register Address (CMDRA)
 *//*------------------------------------------------------------------------ */
short int vc54xx_cmdra_get(voltdm54xx_id id, vc54xx_registers *vc_regs)
{
	short int cmdra;

	switch (id) {
	case VDD54XX_MPU:
		cmdra = extract_bitfield(vc_regs->vc_smps_mpu_config,
			VC_CMDRA_POS, VC_CMDRA_LEN);
		break;

	case VDD54XX_MM:
		if (extract_bit(vc_regs->vc_smps_mm_config,
			VC_RAC_POS) == 1)
			cmdra = extract_bitfield(vc_regs->vc_smps_mm_config,
				VC_CMDRA_POS, VC_CMDRA_LEN);
		else
			cmdra = extract_bitfield(vc_regs->vc_smps_mpu_config,
				VC_CMDRA_POS, VC_CMDRA_LEN);
		break;

	case VDD54XX_CORE:
		if (extract_bit(vc_regs->vc_smps_core_config,
			VC_RAC_POS) == 1)
			cmdra = extract_bitfield(vc_regs->vc_smps_core_config,
				VC_CMDRA_POS, VC_CMDRA_LEN);
		else
			cmdra = extract_bitfield(vc_regs->vc_smps_mpu_config,
				VC_CMDRA_POS, VC_CMDRA_LEN);
		break;

	default:
		cmdra = OMAPCONF_ERR_ARG;
	}

	return cmdra;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vc54xx_no_pending_error
 * @BRIEF		return 1 if there is no pending error
 * @RETURNS		1 if there is no pending error, 0 otherwise
 * @param[in]		prm_vc_errst: PRM_VC_xyz_ERRST register content
 * @param[in]		prm_vc_bypass_errst: PRM_VC_BYPASS_ERRST register
 *			content
 * @DESCRIPTION		return 1 if there is no pending error
 *//*------------------------------------------------------------------------ */
unsigned char vc54xx_no_pending_error(unsigned int prm_vc_errst,
	unsigned int prm_vc_bypass_errst)
{
	return vc54xx_no_pending_vfsm_error(prm_vc_errst) &&
		vc54xx_no_pending_smps_error(prm_vc_errst) &&
		vc54xx_no_pending_bypass_error(prm_vc_bypass_errst);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vc54xx_no_pending_vfsm_error
 * @BRIEF		return 1 if there is no pending VFSM error
 * @RETURNS		1 if there is no pending VFSM error, 0 otherwise
 * @param[in]		prm_vc_errst: PRM_VC_xyz_ERRST register content
 * @DESCRIPTION		return 1 if there is no pending VFSM error
 *//*------------------------------------------------------------------------ */
unsigned char vc54xx_no_pending_vfsm_error(unsigned int prm_vc_errst)
{
	return extract_bitfield(prm_vc_errst,
		VC_VFSM_SA_ERR_POS, VC54XX_VFSM_ERR_TYPE_MAX) == 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vc54xx_is_vfsm_error_pending
 * @BRIEF		return 1 if selected VFSM error is pending
 * @RETURNS		1 if selected VFSM error is pending, 0 otherwise
 * @param[in]		prm_vc_errst: PRM_VC_xyz_ERRST register content
 * @param[in]		type: VFSM error type
 * @DESCRIPTION		return 1 if selected VFSM error is pending
 *//*------------------------------------------------------------------------ */
unsigned char vc54xx_is_vfsm_error_pending(unsigned int prm_vc_errst,
	vc54xx_vfsm_error_type type)
{
	switch (type) {
	case VC54XX_VFSM_TIMEOUT_ERR:
		return (unsigned char) extract_bit(prm_vc_errst,
			VC_VFSM_TIMEOUT_ERR_POS);
	case VC54XX_VFSM_RA_ERR:
		return (unsigned char) extract_bit(prm_vc_errst,
			VC_VFSM_RA_ERR_POS);
	case VC54XX_VFSM_SA_ERR:
		return (unsigned char) extract_bit(prm_vc_errst,
			VC_VFSM_SA_ERR_POS);
	default:
		fprintf(stderr, "%s(): incorrect value type! (%u)\n",
			__func__, type);
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vc54xx_no_pending_smps_error
 * @BRIEF		return 1 if there is no pending SMPS error
 * @RETURNS		1 if there is no pending SMPS error, 0 otherwise
 * @param[in]		prm_vc_errst: PRM_VC_xyz_ERRST register content
 * @DESCRIPTION		return 1 if there is no pending SMPS error
 *//*------------------------------------------------------------------------ */
unsigned char vc54xx_no_pending_smps_error(unsigned int prm_vc_errst)
{
	return extract_bitfield(prm_vc_errst,
		VC_SMPS_SA_ERR_POS, VC54XX_SMPS_ERR_TYPE_MAX) == 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vc54xx_is_smps_error_pending
 * @BRIEF		return 1 if selected SMPS error is pending
 * @RETURNS		1 if selected SMPS error is pending, 0 otherwise
 * @param[in]		prm_vc_errst: PRM_VC_xyz_ERRST register content
 * @param[in]		type: SMPS error type
 * @DESCRIPTION		return 1 if selected SMPS error is pending
 *//*------------------------------------------------------------------------ */
unsigned char vc54xx_is_smps_error_pending(unsigned int prm_vc_errst,
	vc54xx_smps_error_type type)
{
	switch (type) {
	case VC54XX_SMPS_TIMEOUT_ERR:
		return extract_bit(prm_vc_errst, VC_SMPS_TIMEOUT_ERR_POS);
	case VC54XX_SMPS_RA_ERR:
		return extract_bit(prm_vc_errst, VC_SMPS_RA_ERR_POS);
	case VC54XX_SMPS_SA_ERR:
		return extract_bit(prm_vc_errst, VC_SMPS_SA_ERR_POS);
	default:
		fprintf(stderr, "%s(): incorrect value type! (%u)\n",
			__func__, type);
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vc54xx_no_pending_bypass_error
 * @BRIEF		return 1 if there is no pending BYPASS error
 * @RETURNS		1 if there is no pending BYPASS error, 0 otherwise
 * @param[in]		prm_vc_bypass_errst: PRM_VC_BYPASS_ERRST register
 *			content
 * @DESCRIPTION		return 1 if there is no pending BYPASS error
 *//*------------------------------------------------------------------------ */
unsigned char vc54xx_no_pending_bypass_error(unsigned int prm_vc_bypass_errst)
{
	return extract_bitfield(prm_vc_bypass_errst,
		VC_BYPS_SA_ERR_POS, VC54XX_BYPS_ERR_TYPE_MAX) == 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vc54xx_is_bypass_error_pending
 * @BRIEF		return 1 if selected BYPASS error is pending
 * @RETURNS		1 if selected BYPASS error is pending, 0 otherwise
 * @param[in]		prm_vc_bypass_errst: PRM_VC_BYPASS_ERRST register
 *			content
 * @param[in]		type: BYPASS error type
 * @DESCRIPTION		return 1 if selected BYPASS error is pending
 *//*------------------------------------------------------------------------ */
unsigned char vc54xx_is_bypass_error_pending(unsigned int prm_vc_bypass_errst,
	vc54xx_bypass_error_type type)
{
	switch (type) {
	case VC54XX_BYPS_TIMEOUT_ERR:
		return extract_bit(prm_vc_bypass_errst,
			VC_BYPS_TIMEOUT_ERR_POS);
	case VC54XX_BYPS_RA_ERR:
		return extract_bit(prm_vc_bypass_errst, VC_BYPS_RA_ERR_POS);
	case VC54XX_BYPS_SA_ERR:
		return extract_bit(prm_vc_bypass_errst, VC_BYPS_SA_ERR_POS);
	default:
		fprintf(stderr, "%s(): incorrect value type! (%u)\n",
			__func__, type);
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vc54xx_raw_cmd_values_get
 * @BRIEF		return ON/ONLP/RET/OFF command values
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 * @param[in]		id: voltage domain ID
 * @param[in,out]	vc_regs: Voltage Controller registers content
 * @param[in,out]	cmd_on: ON command value (RETURNED)
 * @param[in,out]	cmd_onlp: ONLP command value (RETURNED)
 * @param[in,out]	cmd_ret: RET command value (RETURNED)
 * @param[in,out]	cmd_off: OFF command value (RETURNED)
 * @DESCRIPTION		return ON/ONLP/RET/OFF command values
 *			WARNING: DO NOT CONSIDER PMIC-SPECIFIC SIZE OF COMMAND.
 *//*------------------------------------------------------------------------ */
int vc54xx_raw_cmd_values_get(voltdm54xx_id id, vc54xx_registers *vc_regs,
	unsigned char *cmd_on, unsigned char *cmd_onlp,
	unsigned char *cmd_ret, unsigned char *cmd_off)
{
	unsigned int vc_val_cmd;

	CHECK_NULL_ARG(cmd_on, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(cmd_onlp, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(cmd_ret, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(cmd_off, OMAPCONF_ERR_ARG);

	/* Command Values Set Selection */
	switch (id) {
	case VDD54XX_MPU:
		vc_val_cmd = vc_regs->vc_val_cmd_vdd_mpu_l;
		break;

	case VDD54XX_MM:
		if (extract_bit(vc_regs->vc_smps_mm_config,
			VC_CMD_SET_SELECT_POS) == 1)
			vc_val_cmd = vc_regs->vc_val_cmd_vdd_mm_l;
		else
			vc_val_cmd = vc_regs->vc_val_cmd_vdd_mpu_l;
		break;

	case VDD54XX_CORE:
		if (extract_bit(vc_regs->vc_smps_core_config,
			VC_CMD_SET_SELECT_POS) == 1)
			vc_val_cmd = vc_regs->vc_val_cmd_vdd_core_l;
		else
			vc_val_cmd = vc_regs->vc_val_cmd_vdd_mpu_l;
		break;

	default:
		return OMAPCONF_ERR_ARG;
	}

	/* Retrieve commands from registers */
	vc_cmd_values_get(vc_val_cmd,
		cmd_on, cmd_onlp, cmd_ret, cmd_off);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vc54xx_cmd_values_get
 * @BRIEF		return ON/ONLP/RET/OFF command values
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 * @param[in]		id: voltage domain ID
 * @param[in,out]	vc_regs: Voltage Controller registers content
 * @param[in,out]	cmd_on: ON command value (RETURNED)
 * @param[in,out]	cmd_onlp: ONLP command value (RETURNED)
 * @param[in,out]	cmd_ret: RET command value (RETURNED)
 * @param[in,out]	cmd_off: OFF command value (RETURNED)
 * @DESCRIPTION		return ON/ONLP/RET/OFF command values
 *			WARNING: CONSIDER PMIC-SPECIFIC SIZE OF COMMAND.
 *//*------------------------------------------------------------------------ */
int vc54xx_cmd_values_get(voltdm54xx_id id, vc54xx_registers *vc_regs,
	unsigned char *cmd_on, unsigned char *cmd_onlp,
	unsigned char *cmd_ret, unsigned char *cmd_off)
{
	int vsel_len, ret;

	ret = vc54xx_raw_cmd_values_get(id, vc_regs,
		cmd_on, cmd_onlp, cmd_ret, cmd_off);
	if (ret != 0)
		return ret;

	/*
	 * Consider size of the commands (PMIC-dependent)
	 * and mask it accordingly.
	 */
	vsel_len = smps_vsel_len_get(vdd_id2smps_id(id));

	*cmd_on = extract_bitfield(*cmd_on, 0, vsel_len);
	*cmd_onlp = extract_bitfield(*cmd_onlp, 0, vsel_len);
	*cmd_ret = extract_bitfield(*cmd_ret, 0, vsel_len);
	*cmd_off = extract_bitfield(*cmd_off, 0, vsel_len);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vc54xx_config_show
 * @BRIEF		decode and show VC current configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 * @param[in,out]	stream: output file (NULL: no output (silent))
 * @param[in,out]	vc_regs: Voltage Controller registers content
 * @DESCRIPTION		decode and show VC current configuration
 *//*------------------------------------------------------------------------ */
int vc54xx_config_show(FILE *stream, vc54xx_registers *vc_regs)
{
	voltdm54xx_id id;
	unsigned char raw_cmd_on, raw_cmd_onlp, raw_cmd_ret, raw_cmd_off;
	unsigned char cmd_on, cmd_onlp, cmd_ret, cmd_off;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row = 0;
	unsigned int errst;
	vc54xx_vfsm_error_type vfsm_type;
	vc54xx_smps_error_type smps_type;
	vc54xx_bypass_error_type bypass_type;
	unsigned char status;
	static const char error_status[2][12] = {
		"",
		"PENDING"};

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	row = 0;
	autoadjust_table_init(table);
	autoadjust_table_strncpy(table, row, 0, "PRM VC Configuration");
	autoadjust_table_strncpy(table, row, 1, "VC_MPU");
	autoadjust_table_strncpy(table, row, 2, "VC_MM");
	autoadjust_table_strncpy(table, row, 3, "VC_CORE");
	row++;

	for (id = VDD54XX_MPU; id <= VDD54XX_CORE; id++) {
		row = 1;
		autoadjust_table_strncpy(table, row, 0,
			"Power IC Slave Address (SA)");
		snprintf(table[row][id], TABLE_MAX_ELT_LEN, "0x%02X",
			vc54xx_sa_get(id, vc_regs));
		row++;

		autoadjust_table_strncpy(table, row, 0,
			"Voltage Reg. Addr (VOLRA)");
		snprintf(table[row][id], TABLE_MAX_ELT_LEN, "0x%02X",
			vc54xx_volra_get(id, vc_regs));
		row++;

		autoadjust_table_strncpy(table, row, 0,
			"Command Reg. Addr (CMDRA)");
		snprintf(table[row][id], TABLE_MAX_ELT_LEN, "0x%02X",
			vc54xx_cmdra_get(id, vc_regs));
		row++;

		autoadjust_table_strncpy(table, row++, 0,
			"Command Values:");
		vc54xx_raw_cmd_values_get(id, vc_regs,
			&raw_cmd_on, &raw_cmd_onlp, &raw_cmd_ret, &raw_cmd_off);
		vc54xx_cmd_values_get(id, vc_regs,
			&cmd_on, &cmd_onlp, &cmd_ret, &cmd_off);
		strncpy(table[row][0], "  ON", TABLE_MAX_ELT_LEN);
		snprintf(table[row][id], TABLE_MAX_ELT_LEN, "0x%02X (%.6lfV)",
			raw_cmd_on, smps_vsel2volt(vdd_id2smps_id(id), cmd_on));
		row++;

		autoadjust_table_strncpy(table, row, 0,
			"  ON-Low-Power (ONLP)");
		snprintf(table[row][id], TABLE_MAX_ELT_LEN, "0x%02X (%.6lfV)",
			raw_cmd_onlp,
			smps_vsel2volt(vdd_id2smps_id(id), cmd_onlp));
		row++;

		autoadjust_table_strncpy(table, row, 0, "  RET");
		snprintf(table[row][id], TABLE_MAX_ELT_LEN, "0x%02X (%.6lfV)",
			raw_cmd_ret,
			smps_vsel2volt(vdd_id2smps_id(id), cmd_ret));
		row++;

		autoadjust_table_strncpy(table, row, 0, "  OFF");
		snprintf(table[row][id], TABLE_MAX_ELT_LEN, "0x%02X (%.6lfV)",
			raw_cmd_off,
			smps_vsel2volt(vdd_id2smps_id(id), cmd_off));
		row += 2;

		autoadjust_table_strncpy(table, row, 0,
			"Pending Error(s)");
		switch (id) {
		case VDD54XX_MPU:
			errst = vc_regs->vc_mpu_errst;
			break;
		case VDD54XX_MM:
			errst = vc_regs->vc_mm_errst;
			break;
		case VDD54XX_CORE:
		default:
			errst = vc_regs->vc_core_errst;
		}
		if (vc54xx_no_pending_error(errst, vc_regs->vc_bypass_errst)) {
			autoadjust_table_strncpy(table, row, id, "None");
			row++;
			continue;
		}
		row++;
		autoadjust_table_strncpy(table, row++, 0,
			"  VFSM Error(s)");
		for (vfsm_type = VC54XX_VFSM_TIMEOUT_ERR;
			vfsm_type < VC54XX_VFSM_ERR_TYPE_MAX; vfsm_type++) {
			snprintf(table[row][0], TABLE_MAX_ELT_LEN, "    %s",
				vc54xx_vfsm_error_name_get(vfsm_type));
			status = vc54xx_is_vfsm_error_pending(errst, vfsm_type);
			snprintf(table[row][id], TABLE_MAX_ELT_LEN, "%s",
				error_status[status]);
			row++;
		}

		autoadjust_table_strncpy(table, row++, 0,
			"  SMPS Error(s)");
		for (smps_type = VC54XX_SMPS_TIMEOUT_ERR;
			smps_type < VC54XX_SMPS_ERR_TYPE_MAX; smps_type++) {
			snprintf(table[row][0], TABLE_MAX_ELT_LEN, "    %s",
				vc54xx_smps_error_name_get(smps_type));
			status = vc54xx_is_smps_error_pending(errst, smps_type);
			snprintf(table[row][id], TABLE_MAX_ELT_LEN, "%s",
				error_status[status]);
			row++;
		}

		autoadjust_table_strncpy(table, row++, 0,
			"  BYPASS Error(s)");
		for (bypass_type = VC54XX_BYPS_TIMEOUT_ERR;
			bypass_type < VC54XX_BYPS_ERR_TYPE_MAX; bypass_type++) {
			snprintf(table[row][0], TABLE_MAX_ELT_LEN, "    %s",
				vc54xx_bypass_error_name_get(bypass_type));
			status = vc54xx_is_bypass_error_pending(
				vc_regs->vc_bypass_errst, bypass_type);
			snprintf(table[row][id], TABLE_MAX_ELT_LEN, "%s",
				error_status[status]);
			row++;
		}
	}

	if (stream != NULL)
		autoadjust_table_fprint(stream, table, row, 4);

	return sri2c_config_show(stream,
		vc_regs->vc_cfg_i2c_mode, vc_regs->vc_cfg_i2c_clk);
}
