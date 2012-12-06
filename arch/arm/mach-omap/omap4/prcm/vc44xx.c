/*
 *
 * @Component			OMAPCONF
 * @Filename			vc44xx.c
 * @Description			OMAP4 VOLTAGE CONTROLLER (VC) Definitions &
 *				Functions
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


#include <vc44xx.h>
#include <prm44xx.h>
#include <mem.h>
#include <vc.h>
#include <pmic.h>
#include <lib.h>
#include <autoadjust_table.h>
#include <cpuinfo.h>


/* #define VC44XX_DEBUG */
#ifdef VC44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


#define VC_SA_VDD_MPU_L_POS				16
#define VC_SA_VDD_MPU_L_LEN				7
#define VC_SA_VDD_IVA_L_POS				8
#define VC_SA_VDD_IVA_L_LEN				7
#define VC_SA_VDD_CORE_L_POS				0
#define VC_SA_VDD_CORE_L_LEN				7

#define VC_VOLRA_VDD_MPU_L_POS				16
#define VC_VOLRA_VDD_MPU_L_LEN				8
#define VC_VOLRA_VDD_IVA_L_POS				8
#define VC_VOLRA_VDD_IVA_L_LEN				8
#define VC_VOLRA_VDD_CORE_L_POS				0
#define VC_VOLRA_VDD_CORE_L_LEN				8

#define VC_CMDRA_VDD_MPU_L_POS				16
#define VC_CMDRA_VDD_MPU_L_LEN				8
#define VC_CMDRA_VDD_IVA_L_POS				8
#define VC_CMDRA_VDD_IVA_L_LEN				8
#define VC_CMDRA_VDD_CORE_L_POS				0
#define VC_CMDRA_VDD_CORE_L_LEN				8

#define VC_CFG_CHANNEL_RACEN_VDD_MPU_L_POS		20
#define VC_CFG_CHANNEL_RAC_VDD_MPU_L_POS		19
#define VC_CFG_CHANNEL_RAV_VDD_MPU_L_POS		18
#define VC_CFG_CHANNEL_CMD_VDD_MPU_L_POS		17
#define VC_CFG_CHANNEL_SA_VDD_MPU_L_POS			16

#define VC_CFG_CHANNEL_CMD_VDD_IVA_L_POS		12
#define VC_CFG_CHANNEL_RACEN_VDD_IVA_L_POS		11
#define VC_CFG_CHANNEL_RAC_VDD_IVA_L_POS		10
#define VC_CFG_CHANNEL_RAV_VDD_IVA_L_POS		9
#define VC_CFG_CHANNEL_SA_VDD_IVA_L_POS			8

#define VC_CFG_CHANNEL_CMD_VDD_CORE_L_POS		4
#define VC_CFG_CHANNEL_RACEN_VDD_CORE_L_POS		3
#define VC_CFG_CHANNEL_RAC_VDD_CORE_L_POS		2
#define VC_CFG_CHANNEL_RAV_VDD_CORE_L_POS		1
#define VC_CFG_CHANNEL_SA_VDD_CORE_L_POS		0


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vc44xx_sa_get
 * @BRIEF		return Slave Address (SA)
 * @RETURNS		>0 Slave Address (SA)
 *			OMAPCONF_ERR_ARG
 * @param[in]		id: voltage domain ID
 * @param[in]		prm_vc_smps_sa: PRM_VC_SMPS_SA register content
 * @param[in]		prm_vc_cfg_channel: PRM_VC_CFG_CHANNEL register content
 * @DESCRIPTION		return Slave Address (SA)
 *//*------------------------------------------------------------------------ */
short int vc44xx_sa_get(voltdm44xx_id id,
	unsigned int prm_vc_smps_sa, unsigned int prm_vc_cfg_channel)
{
	short int sa;

	switch (id) {
	case OMAP4_VDD_MPU:
		sa = extract_bitfield(prm_vc_smps_sa,
			VC_SA_VDD_MPU_L_POS, VC_SA_VDD_MPU_L_LEN);
		break;

	case OMAP4_VDD_IVA:
		if (extract_bit(prm_vc_cfg_channel,
			VC_CFG_CHANNEL_SA_VDD_IVA_L_POS) == 1)
			sa = extract_bitfield(prm_vc_smps_sa,
				VC_SA_VDD_IVA_L_POS, VC_SA_VDD_IVA_L_LEN);
		else
			sa = extract_bitfield(prm_vc_smps_sa,
				VC_SA_VDD_CORE_L_POS, VC_SA_VDD_CORE_L_LEN);
		break;

	case OMAP4_VDD_CORE:
		if (extract_bit(prm_vc_cfg_channel,
			VC_CFG_CHANNEL_SA_VDD_CORE_L_POS) == 1)
			sa = extract_bitfield(prm_vc_smps_sa,
				VC_SA_VDD_CORE_L_POS, VC_SA_VDD_CORE_L_LEN);
		else
			sa = extract_bitfield(prm_vc_smps_sa,
				VC_SA_VDD_MPU_L_POS, VC_SA_VDD_MPU_L_LEN);
		break;

	default:
		sa = OMAPCONF_ERR_ARG;
	}

	return sa;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vc44xx_volra_get
 * @BRIEF		return Voltage Register Address (VOLRA)
 * @RETURNS		>0 Voltage Register Address (VOLRA)
 *			OMAPCONF_ERR_ARG
 * @param[in]		id: voltage domain ID
 * @param[in]		prm_vc_cfg_channel: PRM_VC_CFG_CHANNEL register content
 * @param[in]		prm_vc_val_smps_ra_vol: PRM_VC_VAL_SMPS_RA_VOL register
 *			content
 * @DESCRIPTION		return Voltage Register Address (VOLRA)
 *//*------------------------------------------------------------------------ */
short int vc44xx_volra_get(voltdm44xx_id id,
	unsigned int prm_vc_cfg_channel, unsigned int prm_vc_val_smps_ra_vol)
{
	short int volra;

	switch (id) {
	case OMAP4_VDD_MPU:
		volra =	extract_bitfield(prm_vc_val_smps_ra_vol,
			VC_VOLRA_VDD_MPU_L_POS, VC_VOLRA_VDD_MPU_L_LEN);
		break;

	case OMAP4_VDD_IVA:
		if (extract_bit(prm_vc_cfg_channel,
			VC_CFG_CHANNEL_RAV_VDD_IVA_L_POS) == 1)
			volra = extract_bitfield(prm_vc_val_smps_ra_vol,
				VC_VOLRA_VDD_IVA_L_POS, VC_VOLRA_VDD_IVA_L_LEN);
		else
			volra = extract_bitfield(prm_vc_val_smps_ra_vol,
				VC_VOLRA_VDD_CORE_L_POS,
				VC_VOLRA_VDD_CORE_L_LEN);
		break;

	case OMAP4_VDD_CORE:
		if (extract_bit(prm_vc_cfg_channel,
			VC_CFG_CHANNEL_RAV_VDD_CORE_L_POS) == 1)
			volra = extract_bitfield(prm_vc_val_smps_ra_vol,
				VC_VOLRA_VDD_CORE_L_POS,
				VC_VOLRA_VDD_CORE_L_LEN);
		else
			volra = extract_bitfield(prm_vc_val_smps_ra_vol,
				VC_VOLRA_VDD_MPU_L_POS,
				VC_VOLRA_VDD_MPU_L_LEN);
		break;

	default:
		volra = OMAPCONF_ERR_ARG;
	}

	return volra;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vc44xx_cmdra_get
 * @BRIEF		return Command Register Address (CMDRA)
 * @RETURNS		>0 Command Register Address (CMDRA)
 *			OMAPCONF_ERR_ARG
 * @param[in]		id: voltage domain ID
 * @param[in]		prm_vc_cfg_channel: PRM_VC_CFG_CHANNEL register content
 * @param[in]		prm_vc_val_smps_ra_cmd: PRM_VC_VAL_SMPS_RA_CMD register
 *			content
 * @DESCRIPTION		return Command Register Address (CMDRA)
 *//*------------------------------------------------------------------------ */
short int vc44xx_cmdra_get(voltdm44xx_id id,
	unsigned int prm_vc_cfg_channel, unsigned int prm_vc_val_smps_ra_cmd)
{
	short int cmdra;

	switch (id) {
	case OMAP4_VDD_MPU:
		cmdra = extract_bitfield(prm_vc_val_smps_ra_cmd,
			VC_CMDRA_VDD_MPU_L_POS, VC_CMDRA_VDD_MPU_L_LEN);
		break;

	case OMAP4_VDD_IVA:
		if (extract_bit(prm_vc_cfg_channel,
			VC_CFG_CHANNEL_RAC_VDD_IVA_L_POS) == 1)
			cmdra = extract_bitfield(prm_vc_val_smps_ra_cmd,
				VC_CMDRA_VDD_IVA_L_POS, VC_CMDRA_VDD_IVA_L_LEN);
		else
			cmdra = extract_bitfield(prm_vc_val_smps_ra_cmd,
				VC_CMDRA_VDD_CORE_L_POS,
				VC_CMDRA_VDD_CORE_L_LEN);
		break;

	case OMAP4_VDD_CORE:
		if (extract_bit(prm_vc_cfg_channel,
			VC_CFG_CHANNEL_RAC_VDD_CORE_L_POS) == 1)
			cmdra = extract_bitfield(prm_vc_val_smps_ra_cmd,
				VC_CMDRA_VDD_CORE_L_POS,
				VC_CMDRA_VDD_CORE_L_LEN);
		else
			cmdra = extract_bitfield(prm_vc_val_smps_ra_cmd,
				VC_CMDRA_VDD_MPU_L_POS,
				VC_CMDRA_VDD_MPU_L_LEN);
		break;

	default:
		cmdra = OMAPCONF_ERR_ARG;
	}

	return cmdra;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vc44xx_raw_cmd_values_get
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
short int vc44xx_raw_cmd_values_get(voltdm44xx_id id, vc44xx_registers *vc_regs,
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
	case OMAP4_VDD_MPU:
		vc_val_cmd = vc_regs->prm_vc_val_cmd_vdd_mpu_l;
		break;

	case OMAP4_VDD_IVA:
		if (extract_bit(vc_regs->prm_vc_cfg_channel,
			VC_CFG_CHANNEL_CMD_VDD_IVA_L_POS) == 1)
			vc_val_cmd = vc_regs->prm_vc_val_cmd_vdd_iva_l;
		else
			vc_val_cmd = vc_regs->prm_vc_val_cmd_vdd_core_l;
		break;

	case OMAP4_VDD_CORE:
		vc_val_cmd = vc_regs->prm_vc_val_cmd_vdd_core_l;
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
 * @FUNCTION		vc44xx_cmd_values_get
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
short int vc44xx_cmd_values_get(voltdm44xx_id id, vc44xx_registers *vc_regs,
	unsigned char *cmd_on, unsigned char *cmd_onlp,
	unsigned char *cmd_ret, unsigned char *cmd_off)
{
	int vsel_len, ret;

	ret = vc44xx_raw_cmd_values_get(id, vc_regs,
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
 * @FUNCTION		vc44xx_registers_get
 * @BRIEF		save all VC registers in structure provided as argument.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in, out]	vc_regs: structure where to store VC registers
 * @DESCRIPTION		save all VC registers in structure provided as argument.
 *//*------------------------------------------------------------------------ */
int vc44xx_registers_get(vc44xx_registers *vc_regs)
{
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(vc_regs, OMAPCONF_ERR_ARG);

	ret = mem_read(OMAP4430_PRM_VC_SMPS_SA,
		&(vc_regs->prm_vc_smps_sa));
	ret += mem_read(OMAP4430_PRM_VC_VAL_SMPS_RA_VOL,
		&(vc_regs->prm_vc_smps_ra_vol));
	ret += mem_read(OMAP4430_PRM_VC_VAL_SMPS_RA_CMD,
		&(vc_regs->prm_vc_val_smps_ra_cmd));
	ret += mem_read(OMAP4430_PRM_VC_VAL_CMD_VDD_CORE_L,
		&(vc_regs->prm_vc_val_cmd_vdd_core_l));
	ret += mem_read(OMAP4430_PRM_VC_VAL_CMD_VDD_MPU_L,
		&(vc_regs->prm_vc_val_cmd_vdd_mpu_l));
	ret += mem_read(OMAP4430_PRM_VC_VAL_CMD_VDD_IVA_L,
		&(vc_regs->prm_vc_val_cmd_vdd_iva_l));
	ret += mem_read(OMAP4430_PRM_VC_CFG_CHANNEL,
		&(vc_regs->prm_vc_cfg_channel));
	ret += mem_read(OMAP4430_PRM_VC_CFG_I2C_MODE,
		&(vc_regs->prm_vc_cfg_i2c_mode));
	ret += mem_read(OMAP4430_PRM_VC_CFG_I2C_CLK,
		&(vc_regs->prm_vc_cfg_i2c_clk));

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vc44xx_config_show
 * @BRIEF		decode and show VC current configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output file (NULL: no output (silent))
 * @param[in,out]	vc_regs: Voltage Controller registers content
 * @DESCRIPTION		decode and show VC current configuration
 *//*------------------------------------------------------------------------ */
int vc44xx_config_show(FILE *stream, vc44xx_registers *vc_regs)
{
	voltdm44xx_id id;
	unsigned char raw_cmd_on, raw_cmd_onlp, raw_cmd_ret, raw_cmd_off;
	unsigned char cmd_on, cmd_onlp, cmd_ret, cmd_off;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	row = 0;
	autoadjust_table_init(table);
	autoadjust_table_strncpy(table, row, 0, "PRM VC Configuration");
	autoadjust_table_strncpy(table, row, 1, "VC_MPU");
	autoadjust_table_strncpy(table, row, 2, "VC_IVA");
	autoadjust_table_strncpy(table, row, 3, "VC_CORE");
	row++;

	for (id = OMAP4_VDD_MPU; id <= OMAP4_VDD_CORE; id++) {
		row = 1;
		autoadjust_table_strncpy(table, row, 0,
			"Power IC Slave Address (SA)");
		snprintf(table[row][id], TABLE_MAX_ELT_LEN, "0x%02X",
			vc44xx_sa_get(id, vc_regs->prm_vc_smps_sa,
				vc_regs->prm_vc_cfg_channel));
		row++;

		autoadjust_table_strncpy(table, row, 0,
			"Voltage Reg. Addr (VOLRA)");
		snprintf(table[row][id], TABLE_MAX_ELT_LEN, "0x%02X",
			vc44xx_volra_get(id, vc_regs->prm_vc_cfg_channel,
				vc_regs->prm_vc_smps_ra_vol));
		row++;

		autoadjust_table_strncpy(table, row, 0,
			"Command Reg. Addr (CMDRA)");
		snprintf(table[row][id], TABLE_MAX_ELT_LEN, "0x%02X",
			vc44xx_cmdra_get(id, vc_regs->prm_vc_cfg_channel,
				vc_regs->prm_vc_val_smps_ra_cmd));
		row++;

		autoadjust_table_strncpy(table, row++, 0,
			"Command Values:");
		vc44xx_raw_cmd_values_get(id, vc_regs,
			&raw_cmd_on, &raw_cmd_onlp, &raw_cmd_ret, &raw_cmd_off);
		vc44xx_cmd_values_get(id, vc_regs,
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
		row++;

	}

	if (stream != NULL)
		autoadjust_table_fprint(stream, table, row, 4);

	return 0;
}
