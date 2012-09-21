/*
 *
 * @Component			OMAPCONF
 * @Filename			vc.c
 * @Description			VOLTAGE CONTROLLER (VC) Common Definitions &
 *				Functions
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


#include <vc.h>
#include <lib.h>
#include <cpuinfo.h>
#include <clock44xx.h>
#include <clock54xx.h>
#include <autoadjust_table.h>


#define VC_ON_POS			24
#define VC_ON_LEN			8
#define VC_ONLP_POS			16
#define VC_ONLP_LEN			8
#define VC_RET_POS			8
#define VC_RET_LEN			8
#define VC_OFF_POS			0
#define VC_OFF_LEN			8

#define VC_DFILTEREN_POS		6
#define VC_SRMODEEN_POS			4
#define VC_HSMODEEN_POS			3
#define VC_HSMCODE_POS			0
#define VC_HSMCODE_LEN			3

#define VC_HSSCLL_POS			24
#define VC_HSSCLL_LEN			8
#define VC_HSSCLH_POS			16
#define VC_HSSCLH_LEN			8
#define VC_SCLL_POS			8
#define VC_SCLL_LEN			8
#define VC_SCLH_POS			0
#define VC_SCLH_LEN			8


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vc_cmd_values_get
 * @BRIEF		return ON/ONLP/RET/OFF command values
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 * @param[in]		prm_vc_val_cmd: PRM_VC_VAL_CMD register content
 * @param[in,out]	cmd_on: ON command value (RETURNED)
 * @param[in,out]	cmd_onlp: ONLP command value (RETURNED)
 * @param[in,out]	cmd_ret: RET command value (RETURNED)
 * @param[in,out]	cmd_off: OFF command value (RETURNED)
 * @DESCRIPTION		return ON/ONLP/RET/OFF command values
 *//*------------------------------------------------------------------------ */
short int vc_cmd_values_get(unsigned int prm_vc_val_cmd,
	unsigned char *cmd_on, unsigned char *cmd_onlp,
	unsigned char *cmd_ret, unsigned char *cmd_off)
{
	CHECK_NULL_ARG(cmd_on, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(cmd_onlp, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(cmd_ret, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(cmd_off, OMAPCONF_ERR_ARG);

	*cmd_on = extract_bitfield(prm_vc_val_cmd, VC_ON_POS, VC_ON_LEN);
	*cmd_onlp = extract_bitfield(prm_vc_val_cmd, VC_ONLP_POS, VC_ONLP_LEN);
	*cmd_ret = extract_bitfield(prm_vc_val_cmd, VC_RET_POS, VC_RET_LEN);
	*cmd_off = extract_bitfield(prm_vc_val_cmd, VC_OFF_POS, VC_OFF_LEN);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sri2c_is_double_filtering_enabled
 * @BRIEF		check if double filtering is enabled
 * @RETURNS		1 if double filtering is enabled
 *			0 if double filtering is disabled
 * @param[in]		prm_vc_cfg_i2c_mode: PRM_VC_CFG_I2C_MODE register
 *			content
 * @DESCRIPTION		check if double filtering is enabled
 *//*------------------------------------------------------------------------ */
unsigned char sri2c_is_double_filtering_enabled(
	unsigned int prm_vc_cfg_i2c_mode)
{
	return extract_bit(prm_vc_cfg_i2c_mode, VC_DFILTEREN_POS);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sri2c_is_sr_mode_enabled
 * @BRIEF		check if I2C repeated start operation mode is enabled
 * @RETURNS		1 if I2C repeated start operation mode is enabled
 *			0 if I2C repeated start operation mode is disabled
 * @param[in]		prm_vc_cfg_i2c_mode: PRM_VC_CFG_I2C_MODE register
 *			content
 * @DESCRIPTION		check if I2C repeated start operation mode is enabled
 *//*------------------------------------------------------------------------ */
unsigned char sri2c_is_sr_mode_enabled(unsigned int prm_vc_cfg_i2c_mode)
{
	return extract_bit(prm_vc_cfg_i2c_mode, VC_SRMODEEN_POS);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sri2c_is_hs_mode_enabled
 * @BRIEF		check if I2C high speed mode is enabled
 * @RETURNS		1 if I2C high speed mode is enabled
 *			0 if I2C high speed mode is disabled
 * @param[in]		prm_vc_cfg_i2c_mode: PRM_VC_CFG_I2C_MODE register
 *			content
 * @DESCRIPTION		check if I2C high speed mode is enabled
 *//*------------------------------------------------------------------------ */
unsigned char sri2c_is_hs_mode_enabled(unsigned int prm_vc_cfg_i2c_mode)
{
	return extract_bit(prm_vc_cfg_i2c_mode, VC_HSMODEEN_POS);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sri2c_master_code_get
 * @BRIEF		return the master code value for I2C High Speed preamble
 *			transmission
 * @RETURNS		master code value for I2C High Speed preamble
 *			transmission
 * @param[in]		prm_vc_cfg_i2c_mode: PRM_VC_CFG_I2C_MODE register
 *			content
 * @DESCRIPTION		return the master code value for I2C High Speed preamble
 *			transmission
 *//*------------------------------------------------------------------------ */
unsigned char sri2c_master_code_get(unsigned int prm_vc_cfg_i2c_mode)
{
	return extract_bitfield(prm_vc_cfg_i2c_mode,
		VC_HSMCODE_POS, VC_HSMCODE_LEN);
}



/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sri2c_low_clock_cycles_count_get
 * @BRIEF		return the system clock cycles, necessary to count
 *			the low period of the I2C clock signal
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 * @param[in]		prm_vc_cfg_i2c_mode: PRM_VC_CFG_I2C_MODE register
 *				content
 * @param[in]		prm_vc_cfg_i2c_clk: PRM_VC_CFG_I2C_CLK register content
 * @param[in,out]	cycles: I2C clock signal low period (in SYSCLK cycles)
 *				(RETURNED)
 * @param[in,out]	us: I2C clock signal low period (in micro-second)
 *				(RETURNED)
 * @DESCRIPTION		return the system clock cycles, necessary to count
 *			the low period of the I2C clock signal
 *//*------------------------------------------------------------------------ */
int sri2c_low_clock_cycles_count_get(unsigned int prm_vc_cfg_i2c_mode,
	unsigned int prm_vc_cfg_i2c_clk,
	unsigned char *cycles, double *us)
{
	double sysclk;

	CHECK_NULL_ARG(cycles, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(us, OMAPCONF_ERR_ARG);

	if (cpu_is_omap44xx()) {
			sysclk = clk44xx_get_system_clock_speed();
	} else if (cpu_is_omap54xx()) {
			sysclk = clk54xx_sysclk_rate_get();
	} else {
		fprintf(stderr, "%s(): cpu not supported!!!\n", __func__);
		return OMAPCONF_ERR_CPU;
	}

	if (sri2c_is_hs_mode_enabled(prm_vc_cfg_i2c_mode))
		*cycles = extract_bitfield(prm_vc_cfg_i2c_clk,
			VC_HSSCLL_POS, VC_HSSCLL_LEN);
	else
		*cycles = extract_bitfield(prm_vc_cfg_i2c_clk,
			VC_SCLL_POS, VC_SCLL_LEN);
	*us = ((double) *cycles) / sysclk;

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sri2c_high_clock_cycles_count_get
 * @BRIEF		return the system clock cycles, necessary to count
 *			the high period of the I2C clock signal
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 * @param[in]		prm_vc_cfg_i2c_mode: PRM_VC_CFG_I2C_MODE register
 *				content
 * @param[in]		prm_vc_cfg_i2c_clk: PRM_VC_CFG_I2C_CLK register content
 * @param[in,out]	cycles: I2C clock signal high period (in SYSCLK cycles)
 *				(RETURNED)
 * @param[in,out]	us: I2C clock signal low period (in micro-second)
 *				(RETURNED)
 * @DESCRIPTION		return the system clock cycles, necessary to count
 *			the high period of the I2C clock signal
 *//*------------------------------------------------------------------------ */
int sri2c_high_clock_cycles_count_get(unsigned int prm_vc_cfg_i2c_mode,
	unsigned int prm_vc_cfg_i2c_clk,
	unsigned char *cycles, double *us)
{
	double sysclk;

	CHECK_NULL_ARG(cycles, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(us, OMAPCONF_ERR_ARG);

	if (cpu_is_omap44xx()) {
			sysclk = clk44xx_get_system_clock_speed();
	} else if (cpu_is_omap54xx()) {
			sysclk = clk54xx_sysclk_rate_get();
	} else {
		fprintf(stderr, "%s(): cpu not supported!!!\n", __func__);
		return OMAPCONF_ERR_CPU;
	}

	if (sri2c_is_hs_mode_enabled(prm_vc_cfg_i2c_mode))
		*cycles = extract_bitfield(prm_vc_cfg_i2c_clk,
			VC_HSSCLH_POS, VC_HSSCLH_LEN);
	else
		*cycles = extract_bitfield(prm_vc_cfg_i2c_clk,
			VC_SCLH_POS, VC_SCLH_LEN);
	*us = ((double) *cycles) / sysclk;

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sri2c_config_show
 * @BRIEF		decode and show VC SR I2C current configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output file (NULL: no output (silent))
 * @param[in]		prm_vc_cfg_i2c_mode: PRM_VC_CFG_I2C_MODE register
 *				content
 * @param[in]		prm_vc_cfg_i2c_clk: PRM_VC_CFG_I2C_CLK register content
 * @DESCRIPTION		decode and show VC SR I2C current configuration
 *//*------------------------------------------------------------------------ */
int sri2c_config_show(FILE *stream, unsigned int prm_vc_cfg_i2c_mode,
	unsigned int prm_vc_cfg_i2c_clk)
{
	unsigned char low_cycles, high_cycles;
	double low_us, high_us;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row = 0;

	if (!cpu_is_omap44xx() && !cpu_is_omap54xx()) {
		fprintf(stderr, "%s(): cpu not supported!!!\n", __func__);
		return OMAPCONF_ERR_CPU;
	}

	row = 0;
	autoadjust_table_init(table);
	autoadjust_table_strncpy(table, row++, 0, "SR HS-I2C Configuration");


	autoadjust_table_strncpy(table, row, 0, "Double Filtering");
	if (sri2c_is_double_filtering_enabled(prm_vc_cfg_i2c_mode))
		autoadjust_table_strncpy(table, row, 1,
			"Enabled (rejects glitches < 2 SYSCLK cycle)");
	else
		autoadjust_table_strncpy(table, row, 1,
			"Disabled (rejects glitches < 1 SYSCLK cycle)");
	row++;

	autoadjust_table_strncpy(table, row, 0,
		"Repeated Start Mode (SRMODEEN)");
	if (sri2c_is_sr_mode_enabled(prm_vc_cfg_i2c_mode))
		autoadjust_table_strncpy(table, row, 1, "Enabled");
	else
		autoadjust_table_strncpy(table, row, 1, "Disabled");
	row++;

	autoadjust_table_strncpy(table, row, 0, "High-Speed Mode (HSMODEEN)");
	if (sri2c_is_hs_mode_enabled(prm_vc_cfg_i2c_mode)) {
		autoadjust_table_strncpy(table, row, 1, "Enabled");
		row++;
		autoadjust_table_strncpy(table, row, 0,
			"  HS Master Code (HSMCODE)");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"0x%02X", sri2c_master_code_get(prm_vc_cfg_i2c_mode));
	} else {
		autoadjust_table_strncpy(table, row, 1, "Disabled");
	}
	row++;

	autoadjust_table_strncpy(table, row++, 0, "I2C Clock Configuration:");
	sri2c_low_clock_cycles_count_get(
		prm_vc_cfg_i2c_mode, prm_vc_cfg_i2c_clk, &low_cycles, &low_us);
	sri2c_high_clock_cycles_count_get(
		prm_vc_cfg_i2c_mode, prm_vc_cfg_i2c_clk,
		&high_cycles, &high_us);
	if (sri2c_is_hs_mode_enabled(prm_vc_cfg_i2c_mode)) {
		autoadjust_table_strncpy(table, row, 0,
			"  Low Period (HSSCLL)");
		snprintf(table[row++][1], TABLE_MAX_ELT_LEN, "0x%02X (%.3lfus)",
			low_cycles, low_us);
		autoadjust_table_strncpy(table, row, 0,
			"  High Period (HSSCLH)");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "0x%02X (%.3lfus)",
			high_cycles, high_us);
	} else {
		autoadjust_table_strncpy(table, row, 0, "  Low Period (SCLL)");
		snprintf(table[row++][1], TABLE_MAX_ELT_LEN, "0x%02X (%.3lfus)",
			low_cycles, low_us);
		autoadjust_table_strncpy(table, row, 0, "  High Period (SCLH)");
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "0x%02X (%.3lfus)",
			high_cycles, high_us);
	}
	row++;

	if (stream != NULL)
		autoadjust_table_fprint(stream, table, row, 2);

	return 0;
}
