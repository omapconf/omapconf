/*
 *
 * @Component			OMAPCONF
 * @Filename			vp.c
 * @Description			VOLTAGE PROCESSOR (VP) Common Definitions
 *				& Functions
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


#include <vp.h>
#include <lib.h>
#include <cpuinfo.h>
#include <clock44xx.h>
#include <clock54xx.h>
#include <autoadjust_table.h>
#include <pmic.h>


/* #define VP_DEBUG */
#ifdef VP_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* VP bitfields */
#define VP_ERROROFFSET_POS		24
#define VP_ERROROFFSET_LEN		8
#define VP_ERRORGAIN_POS		16
#define VP_ERRORGAIN_LEN		8
#define VP_INITVOLTAGE_POS		8
#define VP_INITVOLTAGE_LEN		8
#define VP_TIMEOUTEN_POS		3
#define VP_VPENABLE_POS			0

#define VP_VPINIDLE_POS			0

#define VP_VDDMAX_POS			24
#define VP_VDDMAX_LEN			8
#define VP_VDDMIN_POS			16
#define VP_VDDMIN_LEN			8
#define VP_TIMEOUT_POS			0
#define VP_TIMEOUT_LEN			16

#define VP_FORCEUPDATEWAIT_POS		8
#define VP_FORCEUPDATEWAIT_LEN		24
#define VP_VPVOLTAGE_POS		0
#define VP_VPVOLTAGE_LEN		8

#define VP_SMPSOFTWAREAITTIMEMAX_POS	8
#define VP_SMPSOFTWAREAITTIMEMAX_LEN	16
#define VP_VSTEPMAX_POS			0
#define VP_VSTEPMAX_LEN			8

#define VP_SMPSOFTWAREAITTIMEMIN_POS	8
#define VP_SMPSOFTWAREAITTIMEMIN_LEN	16
#define VP_VSTEPMIN_POS			0
#define VP_VSTEPMIN_LEN			8


#define VP_AUDIT_SHOW_STATUS(curr, golden) \
		if (curr == golden) { \
			snprintf(table[row++][3], TABLE_MAX_ELT_LEN, "Pass"); \
		} else { \
			snprintf(table[row++][3], TABLE_MAX_ELT_LEN, "FAIL"); \
			(*err_nbr)++; \
		}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vp_error_offset_get
 * @BRIEF		return VP error offset
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 * @param[in]		vp_config: VP_xyz_CONFIG register content
 * @param[in,out]	offset_raw: VP error offset RAW HEX value (RETURNED)
 * @param[in,out]	offset: VP error offset in % (signed) (RETURNED)
 * @DESCRIPTION		return VP error offset
 *//*------------------------------------------------------------------------ */
int vp_error_offset_get(unsigned int vp_config,
	signed char *offset_raw, double *offset)
{
	CHECK_NULL_ARG(offset_raw, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(offset, OMAPCONF_ERR_ARG);

	*offset_raw = (signed char) extract_bitfield(vp_config,
		VP_ERROROFFSET_POS, VP_ERROROFFSET_LEN);
	*offset = vp_error_offset_hex2percent(*offset_raw);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vp_error_offset_hex2percent
 * @BRIEF		convert VP error offset HEX signed value into %
 * @RETURNS		VP error offset in %
 * @param[in]		offset: VP error offset RAW HEX value
 * @DESCRIPTION		convert VP error offset HEX signed value into %
 *//*------------------------------------------------------------------------ */
double vp_error_offset_hex2percent(signed char offset)
{
	return (double) offset * 0.8;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vp_error_gain_get
 * @BRIEF		return VP error gain
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 * @param[in]		vp_config: VP_xyz_CONFIG register content
 * @param[in]		vdd_id: voltage domain ID
 * @param[in,out]	gain_raw: VP error gain RAW HEX value (RETURNED)
 * @param[in,out]	gain: VP error gain in mV/% (signed) (RETURNED)
 * @DESCRIPTION		return VP error gain
 *//*------------------------------------------------------------------------ */
int vp_error_gain_get(unsigned int vp_config, unsigned short vdd_id,
	signed char *gain_raw, double *gain)
{
	CHECK_NULL_ARG(gain_raw, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(gain, OMAPCONF_ERR_ARG);

	*gain_raw = (signed char) extract_bitfield(vp_config,
		VP_ERRORGAIN_POS, VP_ERRORGAIN_LEN);
	*gain = vp_error_gain_hex2percent(*gain_raw, vdd_id);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vp_error_gain_hex2percent
 * @BRIEF		convert VP error gain HEX signed value into mV/%
 * @RETURNS		VP error gain in mV/%
 * @param[in]		gain: VP error gain RAW HEX value
 * @param[in]		vdd_id: voltage domain ID
 * @DESCRIPTION		convert VP error gain HEX signed value into mV/%
 *//*------------------------------------------------------------------------ */
double vp_error_gain_hex2percent(signed char gain, unsigned short vdd_id)
{
	double step_mv;

	step_mv = (double) smps_step_get(vdd_id2smps_id(vdd_id)) / 1000.0;

	return (double) gain * step_mv / 100.0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vp_init_voltage_get
 * @BRIEF		return VP initial voltage
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 * @param[in]		vp_config: VP_xyz_CONFIG register content
 * @param[in]		vdd_id: voltage domain ID
 * @param[in,out]	init_vsel: initial voltage (vsel command) (RETURNED)
 * @param[in,out]	init_uv: initial voltage (in micro-volt) (RETURNED)
 * @DESCRIPTION		return VP initial voltage
 *//*------------------------------------------------------------------------ */
int vp_init_voltage_get(unsigned int vp_config, unsigned short vdd_id,
	unsigned char *init_vsel, unsigned int *init_uv)
{
	CHECK_NULL_ARG(init_vsel, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(init_uv, OMAPCONF_ERR_ARG);

	*init_vsel = (unsigned char) extract_bitfield(vp_config,
		VP_INITVOLTAGE_POS, VP_INITVOLTAGE_LEN);
	*init_uv = smps_vsel2uvolt(vdd_id2smps_id(vdd_id), *init_vsel);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vp_vc_timeout_is_enabled
 * @BRIEF		check if VC Timeout is enabled
 * @RETURNS		1 if VC Timeout is enabled
 *			0 if VC Timeout is disabled
 * @param[in]		vp_config: VP_xyz_CONFIG register content
 * @DESCRIPTION		check if VC Timeout is enabled
 *//*------------------------------------------------------------------------ */
unsigned char vp_vc_timeout_is_enabled(unsigned int vp_config)
{
	return extract_bit(vp_config, VP_TIMEOUTEN_POS);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vp_is_enabled
 * @BRIEF		check if VP is enabled
 * @RETURNS		1 if VP is enabled
 *			0 if VP is disabled
 * @param[in]		vp_config: VP_xyz_CONFIG register content
 * @DESCRIPTION		check if VP is enabled
 *//*------------------------------------------------------------------------ */
unsigned char vp_is_enabled(unsigned int vp_config)
{
	return extract_bit(vp_config, VP_VPENABLE_POS);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vp_is_idle
 * @BRIEF		check if VP is idle
 * @RETURNS		1 if VP is idle
 *			0 if VP is not idle (running)
 * @param[in]		vp_status: VP_xyz_STATUS register content
 * @DESCRIPTION		check if VP is idle
 *//*------------------------------------------------------------------------ */
unsigned char vp_is_idle(unsigned int vp_status)
{
	return extract_bit(vp_status, VP_VPINIDLE_POS);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vp_min_voltage_get
 * @BRIEF		return VP minimum supply voltage
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 * @param[in]		vp_vlimitto: VP_xyz_VLIMITTO register content
 * @param[in]		vdd_id: voltage domain ID
 * @param[in,out]	min_vsel: minimum supply voltage (vsel command)
 *				(RETURNED)
 * @param[in,out]	min_uv: minimum supply voltage (in micro-volt)
 *				(RETURNED)
 * @DESCRIPTION		return VP minimum supply voltage
 *//*------------------------------------------------------------------------ */
int vp_min_voltage_get(unsigned int vp_vlimitto, unsigned short vdd_id,
	unsigned char *min_vsel, unsigned int *min_uv)
{
	CHECK_NULL_ARG(min_vsel, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(min_uv, OMAPCONF_ERR_ARG);

	*min_vsel = (unsigned char) extract_bitfield(vp_vlimitto,
		VP_VDDMIN_POS, VP_VDDMIN_LEN);
	*min_uv = smps_vsel2uvolt(vdd_id2smps_id(vdd_id), *min_vsel);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vp_max_voltage_get
 * @BRIEF		return VP maximum supply voltage
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 * @param[in]		vp_vlimitto: VP_xyz_VLIMITTO register content
 * @param[in]		vdd_id: voltage domain ID
 * @param[in,out]	max_vsel: maximum supply voltage (vsel command)
 *				(RETURNED)
 * @param[in,out]	max_uv: maximum supply voltage (in micro-volt)
 *				(RETURNED)
 * @DESCRIPTION		return VP maximum supply voltage
 *//*------------------------------------------------------------------------ */
int vp_max_voltage_get(unsigned int vp_vlimitto, unsigned short vdd_id,
	unsigned char *max_vsel, unsigned int *max_uv)
{
	CHECK_NULL_ARG(max_vsel, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(max_uv, OMAPCONF_ERR_ARG);

	*max_vsel = (unsigned char) extract_bitfield(vp_vlimitto,
		VP_VDDMAX_POS, VP_VDDMAX_LEN);
	*max_uv = smps_vsel2uvolt(vdd_id2smps_id(vdd_id), *max_vsel);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vp_last_voltage_get
 * @BRIEF		return the last voltage set by the voltage processor
 *			for a domain.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 * @param[in]		vp_voltage: VP_xyz_VOLTAGE register content
 * @param[in]		vdd_id: voltage domain ID
 * @param[in,out]	vsel: last supply voltage programmed by VP
 *				(vsel command) (RETURNED)
 * @param[in,out]	uv: last supply voltage programmed by VP
 *				(in micro-volt) (RETURNED)
 * @DESCRIPTION		return the last voltage set by the voltage processor
 *			for a domain.
 *			NB: SR/VP/VC HAVE TO BE AT LEAST INITIALIZED
 *			(SR COULD BE DISABLED) OTHERWISE THIS VALUE HAS NO SENSE
 *//*------------------------------------------------------------------------ */
int vp_last_voltage_get(unsigned int vp_voltage, unsigned short vdd_id,
	unsigned char *vsel, unsigned int *uv)
{
	CHECK_NULL_ARG(vsel, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(uv, OMAPCONF_ERR_ARG);

	*vsel = (unsigned char) extract_bitfield(vp_voltage, 0,
			smps_vsel_len_get(vdd_id2smps_id(vdd_id)));

	*uv = smps_vsel2uvolt(vdd_id2smps_id(vdd_id), *vsel);
	dprintf("%s(%u): VP_VOLTAGE=0x%08X, vsel=%02X voltage=%uV\n", __func__,
		vdd_id, vp_voltage, *vsel, *uv);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vp_vc_timeout_get
 * @BRIEF		return VC maximum response wait time
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 * @param[in]		vp_vlimitto: VP_xyz_VLIMITTO register content
 * @param[in,out]	timeout_cycles: maximum response wait time
 *				(SYSCLK cycles) (RETURNED)
 * @param[in,out]	timeout_us: maximum response wait time (in micro-second)
 *				(RETURNED)
 * @DESCRIPTION		return VC maximum response wait time
 *//*------------------------------------------------------------------------ */
int vp_vc_timeout_get(unsigned int vp_vlimitto,
	unsigned int *timeout_cycles, unsigned int *timeout_us)
{
	double sysclk;

	CHECK_NULL_ARG(timeout_cycles, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(timeout_us, OMAPCONF_ERR_ARG);

	if (cpu_is_omap44xx()) {
			sysclk = clk44xx_get_system_clock_speed();
	} else if (cpu_is_omap54xx()) {
			sysclk = clk54xx_sysclk_rate_get();
	} else {
		fprintf(stderr, "%s(): cpu not supported!!!\n", __func__);
		return OMAPCONF_ERR_CPU;
	}

	*timeout_cycles = extract_bitfield(vp_vlimitto,
		VP_TIMEOUT_POS, VP_TIMEOUT_LEN);
	*timeout_us = *timeout_cycles / sysclk;

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vp_force_update_wait_time_get
 * @BRIEF		return the time voltage processor needs to wait for
 *			SMPS to be settled after receiving SMPS acknowledge.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 * @param[in]		vp_voltage: VP_xyz_VOLTAGE register content
 * @param[in,out]	time_cycles: time VP needs to wait for SMPS to be
 *				settled (in SYSCLK cycles) (returned)
 * @param[in,out]	time VP needs to wait for SMPS to be settled
 *				(in micro-second) (returned)
 * @DESCRIPTION		return the time voltage processor needs to wait for
 *			SMPS to be settled after receiving SMPS acknowledge.
 *//*------------------------------------------------------------------------ */
int vp_force_update_wait_time_get(unsigned int vp_voltage,
	unsigned int *time_cycles, unsigned int *time_us)
{
	double sysclk;

	CHECK_NULL_ARG(time_cycles, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(time_us, OMAPCONF_ERR_ARG);

	if (cpu_is_omap44xx()) {
			sysclk = clk44xx_get_system_clock_speed();
	} else if (cpu_is_omap54xx()) {
			sysclk = clk54xx_sysclk_rate_get();
	} else {
		fprintf(stderr, "%s(): cpu not supported!!!\n", __func__);
		return OMAPCONF_ERR_CPU;
	}

	*time_cycles = extract_bitfield(vp_voltage,
		VP_FORCEUPDATEWAIT_POS, VP_FORCEUPDATEWAIT_LEN);
	*time_us = *time_cycles / sysclk;

	return 0;

}



/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vp_max_step_get
 * @BRIEF		return VP maximum voltage step
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 * @param[in]		vp_vstepmax: VP_xyz_VSTEPMAX register content
 * @param[in]		vdd_id: voltage domain ID
 * @param[in,out]	max_step: maximum voltage step (vsel command) (RETURNED)
 * @param[in,out]	max_uv: maximum voltage step (in micro-volt) (RETURNED)
 * @DESCRIPTION		return VP maximum voltage step
 *//*------------------------------------------------------------------------ */
int vp_max_step_get(unsigned int vp_vstepmax, unsigned short vdd_id,
	unsigned int *max_step, unsigned int *max_uv)
{
	CHECK_NULL_ARG(max_step, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(max_uv, OMAPCONF_ERR_ARG);

	*max_step = extract_bitfield(vp_vstepmax,
		VP_VSTEPMAX_POS, VP_VSTEPMAX_LEN);
	*max_uv = *max_step * smps_step_get(vdd_id2smps_id(vdd_id));

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vp_min_step_get
 * @BRIEF		return VP minimum voltage step
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 * @param[in]		vp_vstepmin: VP_xyz_VSTEPMIN register content
 * @param[in]		vdd_id: voltage domain ID
 * @param[in,out]	min_step: minimum voltage step (vsel command) (RETURNED)
 * @param[in,out]	min_uv: minimum voltage step (in micro-volt) (RETURNED)
 * @DESCRIPTION		return VP minimum voltage step
 *//*------------------------------------------------------------------------ */
int vp_min_step_get(unsigned int vp_vstepmin, unsigned short vdd_id,
	unsigned int *min_step, unsigned int *min_uv)
{
	CHECK_NULL_ARG(min_step, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(min_uv, OMAPCONF_ERR_ARG);

	*min_step = extract_bitfield(vp_vstepmin,
		VP_VSTEPMIN_POS, VP_VSTEPMIN_LEN);
	*min_uv = *min_step * smps_step_get(vdd_id2smps_id(vdd_id));

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vp_positive_slew_rate_get
 * @BRIEF		return VP slew rate for positive voltage step
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 * @param[in]		vp_vstepmax: VP_xyz_VSTEPMAX register content
 * @param[in,out]	cycles: VP slew rate for positive voltage step
 *				in number of cycles per step (RETURNED)
 * @param[in,out]	us: VP slew rate for positive voltage step
 *				in micro-seconds per step (RETURNED)
 * @DESCRIPTION		return VP slew rate for positive voltage step
 *//*------------------------------------------------------------------------ */
int vp_positive_slew_rate_get(unsigned int vp_vstepmax,
	unsigned int *cycles, unsigned int *us)
{
	int ret;

	CHECK_NULL_ARG(cycles, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(us, OMAPCONF_ERR_ARG);

	*cycles = extract_bitfield(vp_vstepmax,
		VP_SMPSOFTWAREAITTIMEMAX_POS, VP_SMPSOFTWAREAITTIMEMAX_LEN);
	ret = vp_slew_rate_cycles2us(*cycles);
	if (ret >= 0) {
		*us = ret;
		return 0;
	} else {
		*us = 0;
		return ret;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vp_negative_slew_rate_get
 * @BRIEF		return VP slew rate for negative voltage step
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 * @param[in]		vp_vstepmin: VP_xyz_VSTEPMIN register content
 * @param[in,out]	cycles: VP slew rate for negative voltage step
 *				in number of cycles per step (RETURNED)
 * @param[in,out]	us: VP slew rate for negative voltage step
 *				in micro-seconds per step (RETURNED)
 * @DESCRIPTION		return VP slew rate for negative voltage step
 *//*------------------------------------------------------------------------ */
int vp_negative_slew_rate_get(unsigned int vp_vstepmin,
	unsigned int *cycles, unsigned int *us)
{
	int ret;

	CHECK_NULL_ARG(cycles, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(us, OMAPCONF_ERR_ARG);

	*cycles = extract_bitfield(vp_vstepmin,
		VP_SMPSOFTWAREAITTIMEMIN_POS, VP_SMPSOFTWAREAITTIMEMIN_LEN);
	ret = vp_slew_rate_cycles2us(*cycles);
	if (ret >= 0) {
		*us = ret;
		return 0;
	} else {
		*us = 0;
		return ret;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vp_slew_rate_cycles2us
 * @BRIEF		convert VP slew rate HEX value into micro-seconds
 * @RETURNS		VP slew rate in micro-seconds
 *			OMAPCONF_ERR_CPU
 * @param[in]		cycles: VP slew rate for negative voltage step in
 *				number of cycles per step
 * @DESCRIPTION		convert VP slew rate HEX value into micro-seconds
 *//*------------------------------------------------------------------------ */
int vp_slew_rate_cycles2us(unsigned int cycles)
{
	double sysclk;

	if (cpu_is_omap44xx()) {
			sysclk = clk44xx_get_system_clock_speed();
	} else if (cpu_is_omap54xx()) {
			sysclk = clk54xx_sysclk_rate_get();
	} else {
		fprintf(stderr, "%s(): cpu not supported!!!\n", __func__);
		return OMAPCONF_ERR_CPU;
	}

	return (unsigned int) ((cycles / sysclk) + 1);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vp_config_show
 * @BRIEF		decode and show VP current configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output file (NULL: no output (silent))
 * @param[in,out]	vp_regs: VP registers content for the 3 VP instances
 *				(MPU, IVA/MM, CORE)
 * @DESCRIPTION		decode and show VP current configuration
 *//*------------------------------------------------------------------------ */
int vp_config_show(FILE *stream, vp_registers vp_regs[3])
{
	unsigned int cycles, us, step, uv;
	unsigned char vsel;

	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int i, row = 0;
	signed char vp_offset_raw, vp_gain_raw;
	double vp_offset, vp_gain;

	CHECK_NULL_ARG(vp_regs, OMAPCONF_ERR_ARG);
	if (!cpu_is_omap44xx() && !cpu_is_omap54xx()) {
		fprintf(stderr, "%s(): cpu not supported!!!\n", __func__);
		return OMAPCONF_ERR_CPU;
	}


	#ifdef VP_DEBUG
	autoadjust_table_init(table);
	autoadjust_table_strncpy(table, row, 0, "VP Registers");
	autoadjust_table_strncpy(table, row, 1, "VP MPU");
	if (cpu_is_omap44xx())
		autoadjust_table_strncpy(table, row, 2, "VP MM");
	else
		autoadjust_table_strncpy(table, row, 2, "VP MM");
	autoadjust_table_strncpy(table, row, 3, "VP CORE");
	row++;
	for (i = 0; i < 3; i++) {
		row = 1;
		autoadjust_table_strncpy(table, row, 0, "VP_CONFIG");
		snprintf(table[row++][i + 1], TABLE_MAX_ELT_LEN, "0x%08X",
			vp_regs[i].vp_config);
		autoadjust_table_strncpy(table, row, 0, "VP_STATUS");
		snprintf(table[row++][i + 1], TABLE_MAX_ELT_LEN, "0x%08X",
			vp_regs[i].vp_status);
		autoadjust_table_strncpy(table, row, 0, "VP_VLIMITTO");
		snprintf(table[row++][i + 1], TABLE_MAX_ELT_LEN, "0x%08X",
			vp_regs[i].vp_vlimitto);
		autoadjust_table_strncpy(table, row, 0, "VP_VOLTAGE");
		snprintf(table[row++][i + 1], TABLE_MAX_ELT_LEN, "0x%08X",
			vp_regs[i].vp_voltage);
		autoadjust_table_strncpy(table, row, 0, "VP_VSTEPMAX");
		snprintf(table[row++][i + 1], TABLE_MAX_ELT_LEN, "0x%08X",
			vp_regs[i].vp_vstepmax);
		autoadjust_table_strncpy(table, row, 0, "VP_VSTEPMIN");
		snprintf(table[row++][i + 1], TABLE_MAX_ELT_LEN, "0x%08X",
			vp_regs[i].vp_vstepmin);
	}
	autoadjust_table_print(table, row, 4);
	#endif


	row = 0;
	autoadjust_table_init(table);
	autoadjust_table_strncpy(table, row, 0, "PRM VP Configuration");
	autoadjust_table_strncpy(table, row, 1, "VP_MPU");
	if (cpu_is_omap44xx())
		autoadjust_table_strncpy(table, row, 2, "VP_IVA");
	else
		autoadjust_table_strncpy(table, row, 2, "VP_MM");
	autoadjust_table_strncpy(table, row++, 3, "VP_CORE");

	for (i = 0; i < 3; i++) {
		row = 1;
		autoadjust_table_strncpy(table, row, 0, "Mode");
		if (vp_is_enabled(vp_regs[i].vp_config) == 1)
			autoadjust_table_strncpy(table, row, i + 1, "Enabled");
		else
			autoadjust_table_strncpy(table, row, i + 1, "Disabled");
		row++;

		autoadjust_table_strncpy(table, row, 0, "Status");
		if (vp_is_idle(vp_regs[i].vp_status) == 1)
			autoadjust_table_strncpy(table, row, i + 1, "Idle");
		else
			autoadjust_table_strncpy(table, row, i + 1,
				"Processing");
		row++;

		autoadjust_table_strncpy(table, row, 0, "VC Response Timeout");
		if (vp_vc_timeout_is_enabled(vp_regs[i].vp_config) == 1) {
			autoadjust_table_strncpy(table, row, i + 1, "Enabled");
			row++;
			autoadjust_table_strncpy(table, row, 0,
				"  Timeout (SysClk cycles, us)");
			vp_vc_timeout_get(vp_regs[i].vp_vlimitto, &cycles, &us);
			snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN,
				"%u (%uus)", cycles, us);
		} else {
			autoadjust_table_strncpy(table, row, i + 1, "Disabled");
		}
		row++;

		autoadjust_table_strncpy(table, row, 0,
			"Error Gain (hex, mV/%%)");
		vp_error_gain_get(vp_regs[i].vp_config, vp_regs[i].vdd_id,
			&vp_gain_raw, &vp_gain);
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN,
			"0x%02X (%.3lfmV/%%)", vp_gain_raw, vp_gain);
		row++;

		autoadjust_table_strncpy(table, row, 0,
			"Error Offset (hex, %%)");
		vp_error_offset_get(vp_regs[i].vp_config,
			&vp_offset_raw, &vp_offset);
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN,
			"0x%02X (%.3lf%%)", vp_offset_raw, vp_offset);
		row++;

		autoadjust_table_strncpy(table, row, 0,
			"Initial Voltage (step, V)");
		vp_init_voltage_get(vp_regs[i].vp_config, vp_regs[i].vdd_id,
			&vsel, &uv);
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN,
			"0x%02X (%.6lfV)", vsel, (double) uv / 1000000.0);
		row++;

		autoadjust_table_strncpy(table, row, 0,
			"MAX Voltage (step, V)");
		vp_max_voltage_get(vp_regs[i].vp_vlimitto, vp_regs[i].vdd_id,
			&vsel, &uv);
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN,
			"0x%02X (%.6lfV)", vsel, (double) uv / 1000000.0);
		row++;

		autoadjust_table_strncpy(table, row, 0,
			"MIN Voltage (step, V)");
		vp_min_voltage_get(vp_regs[i].vp_vlimitto, vp_regs[i].vdd_id,
			&vsel, &uv);
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN,
			"0x%02X (%.6lfV)", vsel, (double) uv / 1000000.0);
		row++;

		autoadjust_table_strncpy(table, row, 0,
			"Current Voltage (step, V)");
		vp_last_voltage_get(vp_regs[i].vp_voltage, vp_regs[i].vdd_id,
			&vsel, &uv);
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN,
			"0x%02X (%.6lfV)", vsel, (double) uv / 1000000.0);
		row++;

		autoadjust_table_strncpy(table, row, 0,
			"Force Update Wait (cycles, us)");
		vp_force_update_wait_time_get(vp_regs[i].vp_voltage,
			&cycles, &us);
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN, "%u (%uus)",
			cycles, us);
		row++;

		autoadjust_table_strncpy(table, row, 0, "MAX Voltage Step");
		vp_max_step_get(vp_regs[i].vp_vstepmax,  vp_regs[i].vdd_id,
			&step, &uv);
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN,
			"0x%02X (%.3lfmV)", step, (double) uv / 1000.0);
		row++;

		autoadjust_table_strncpy(table, row, 0,
			"SMPSWAITTIMEMAX (cycles/step, us)");
		vp_positive_slew_rate_get(vp_regs[i].vp_vstepmax, &cycles, &us);
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN, "%u (%uus)",
			cycles, us);
		row++;

		autoadjust_table_strncpy(table, row, 0, "MIN Voltage Step");
		vp_min_step_get(vp_regs[i].vp_vstepmin,  vp_regs[i].vdd_id,
			&step, &uv);
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN,
			"0x%02X (%.3lfmV)", step, (double) uv / 1000.0);
		row++;

		autoadjust_table_strncpy(table, row, 0,
			"SMPSWAITTIMEMIN (cycles/step, us)");
		vp_negative_slew_rate_get(vp_regs[i].vp_vstepmin, &cycles, &us);
		snprintf(table[row][i + 1], TABLE_MAX_ELT_LEN, "%u (%uus)",
			cycles, us);
		row++;
	}


	if (stream != NULL)
		autoadjust_table_fprint(stream, table, row, 4);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vp_config_audit
 * @BRIEF		audit Voltage Processor (VP) configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		stream: output file (NULL: no output (silent))
 * @param[in]		vp_name: voltage processor name
 * @param[in]		opp_name: OPP name
 * @param[in]		vp_regs: VP registers content
 * @param[in]		vp_golden_settings: expected ("golden") VP settings
 * @param[in,out]	err_nbr: audit error number
 * @param[in,out]	wng_nbr: audit warning number
 * @DESCRIPTION		audit Voltage Processor (VP) configuration by comparison
 *			with expected ("golden") settings
 *//*------------------------------------------------------------------------ */
int vp_config_audit(FILE *stream, const char *vp_name, const char *opp_name,
	vp_registers *vp_regs, const vp_audit_settings *vp_golden_settings,
	unsigned int *err_nbr, unsigned int *wng_nbr)
{
	signed char errgain_curr, errgain_expected;
	double errgain_curr2, errgain_expected2;
	signed char erroffset_curr, erroffset_expected;
	double erroffset_curr2, erroffset_expected2;
	unsigned int current, expected;
	unsigned int current2, expected2;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row;
	static const char mode_table[2][16] = {
		"Disabled      ",
		"Enabled       "};

	CHECK_NULL_ARG(vp_name, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(vp_regs, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(vp_golden_settings, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(err_nbr, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(wng_nbr, OMAPCONF_ERR_ARG);
	if (!cpu_is_omap44xx() && !cpu_is_omap54xx()) {
		fprintf(stderr, "%s(): cpu not supported!!!\n", __func__);
		return OMAPCONF_ERR_CPU;
	}

	*err_nbr = 0;
	*wng_nbr = 0;
	row = 0;
	autoadjust_table_init(table);
	snprintf(table[row][0], TABLE_MAX_ELT_LEN,
		"PRM %s Configuration AUDIT (@%s)", vp_name, opp_name);
	autoadjust_table_strncpy(table, row, 1, "Current");
	autoadjust_table_strncpy(table, row, 2, "Expected");
	autoadjust_table_strncpy(table, row, 3, "STATUS");
	row++;

	autoadjust_table_strncpy(table, row, 0, "Mode");
	current = vp_is_enabled(vp_regs->vp_config);
	expected = vp_golden_settings->mode;
	autoadjust_table_strncpy(table, row, 1,	(char *) mode_table[current]);
	autoadjust_table_strncpy(table, row, 2,	(char *) mode_table[expected]);
	VP_AUDIT_SHOW_STATUS(current, expected);

	autoadjust_table_strncpy(table, row, 0, "VC Response Timeout");
	current = vp_vc_timeout_is_enabled(vp_regs->vp_config);
	expected = vp_golden_settings->vc_timeout_mode;
	autoadjust_table_strncpy(table, row, 1, (char *) mode_table[current]);
	autoadjust_table_strncpy(table, row, 2, (char *) mode_table[expected]);
	VP_AUDIT_SHOW_STATUS(current, expected);

	autoadjust_table_strncpy(table, row, 0, "  Timeout (SysClk cycles)");
	vp_vc_timeout_get(vp_regs->vp_vlimitto,
		&current, &current2);
	expected = vp_golden_settings->vc_timeout_cycles;
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u", current);
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u", expected);
	VP_AUDIT_SHOW_STATUS(current, expected);

	autoadjust_table_strncpy(table, row, 0,
		"Force Update Wait (SysClk cycles)");
	vp_force_update_wait_time_get(vp_regs->vp_voltage,
		&current, &current2);
	expected = vp_golden_settings->force_update_wait_time;
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u", current);
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u", expected);
	VP_AUDIT_SHOW_STATUS(current, expected);


	autoadjust_table_strncpy(table, row, 0, "MAX Voltage Step");
	vp_max_step_get(vp_regs->vp_vstepmax,  vp_regs->vdd_id,
		&current, &current2);
	expected = vp_golden_settings->vstepmax;
	expected2 = expected * smps_step_get(vdd_id2smps_id(vp_regs->vdd_id));
	snprintf(table[row][1], TABLE_MAX_ELT_LEN,
		"0x%02X (%.3lfmV)", current, (double) current2 / 1000.0);
	snprintf(table[row][2], TABLE_MAX_ELT_LEN,
		"0x%02X (%.3lfmV)", expected, (double) expected2 / 1000.0);
	VP_AUDIT_SHOW_STATUS(current, expected);

	autoadjust_table_strncpy(table, row, 0,
		"SMPSWAITTIMEMAX (cycles/step, us)");
	vp_positive_slew_rate_get(vp_regs->vp_vstepmax, &current, &current2);
	expected = vp_golden_settings->positive_slew_rate;
	expected2 = vp_slew_rate_cycles2us(expected);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u (%uus)",
		current, current2);
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u (%uus)",
		expected, expected2);
	VP_AUDIT_SHOW_STATUS(current, expected);

	autoadjust_table_strncpy(table, row, 0, "MIN Voltage Step");
	vp_min_step_get(vp_regs->vp_vstepmin,  vp_regs->vdd_id,
		&current, &current2);
	expected = vp_golden_settings->vstepmin;
	expected2 = expected * smps_step_get(vdd_id2smps_id(vp_regs->vdd_id));
	snprintf(table[row][1], TABLE_MAX_ELT_LEN,
		"0x%02X (%.3lfmV)", current, (double) current2 / 1000.0);
	snprintf(table[row][2], TABLE_MAX_ELT_LEN,
		"0x%02X (%.3lfmV)", expected, (double) expected2 / 1000.0);
	VP_AUDIT_SHOW_STATUS(current, expected);

	autoadjust_table_strncpy(table, row, 0,
		"SMPSWAITTIMEMIN (cycles/step, us)");
	vp_negative_slew_rate_get(vp_regs->vp_vstepmin, &current, &current2);
	expected = vp_golden_settings->negative_slew_rate;
	expected2 = vp_slew_rate_cycles2us(expected);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%u (%uus)",
		current, current2);
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%u (%uus)",
		expected, expected2);
	VP_AUDIT_SHOW_STATUS(current, expected);

	autoadjust_table_strncpy(table, row, 0, "Initial Voltage (step, V)");
	vp_init_voltage_get(vp_regs->vp_config, vp_regs->vdd_id,
		(unsigned char *) &current, &current2);
	expected = vp_golden_settings->init_voltage;
	expected2 = smps_vsel2uvolt(vdd_id2smps_id(vp_regs->vdd_id), expected);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN,
		"0x%02X (%.6lfV)", current, (double) current2 / 1000000.0);
	snprintf(table[row][2], TABLE_MAX_ELT_LEN,
		"0x%02X (%.6lfV)", expected, (double) expected2 / 1000000.0);
	VP_AUDIT_SHOW_STATUS(current, expected);

	autoadjust_table_strncpy(table, row, 0, "MAX Voltage (step, V)");
	vp_max_voltage_get(vp_regs->vp_vlimitto, vp_regs->vdd_id,
		(unsigned char *) &current, &current2);
	expected = vp_golden_settings->max_voltage;
	expected2 = smps_vsel2uvolt(vdd_id2smps_id(vp_regs->vdd_id), expected);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN,
		"0x%02X (%.6lfV)", current, (double) current2 / 1000000.0);
	snprintf(table[row][2], TABLE_MAX_ELT_LEN,
		"0x%02X (%.6lfV)", expected, (double) expected2 / 1000000.0);
	VP_AUDIT_SHOW_STATUS(current, expected);

	autoadjust_table_strncpy(table, row, 0, "MIN Voltage (step, V)");
	vp_min_voltage_get(vp_regs->vp_vlimitto, vp_regs->vdd_id,
		(unsigned char *) &current, &current2);
	expected = vp_golden_settings->min_voltage;
	expected2 = smps_vsel2uvolt(vdd_id2smps_id(vp_regs->vdd_id), expected);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN,
		"0x%02X (%.6lfV)", current, (double) current2 / 1000000.0);
	snprintf(table[row][2], TABLE_MAX_ELT_LEN,
		"0x%02X (%.6lfV)", expected, (double) expected2 / 1000000.0);
	VP_AUDIT_SHOW_STATUS(current, expected);

	autoadjust_table_strncpy(table, row, 0, "Error Gain (hex, mV/%)");
	vp_error_gain_get(vp_regs->vp_config, vp_regs->vdd_id,
		&errgain_curr, &errgain_curr2);
	errgain_expected = vp_golden_settings->error_gain;
	errgain_expected2 = vp_error_gain_hex2percent(errgain_expected,
		vp_regs->vdd_id);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN,
		"0x%02X (%.3lfmV/%%)", errgain_curr, errgain_curr2);
	snprintf(table[row][2], TABLE_MAX_ELT_LEN,
		"0x%02X (%.3lfmV/%%)", errgain_expected, errgain_expected2);
	VP_AUDIT_SHOW_STATUS(errgain_curr, errgain_expected);

	autoadjust_table_strncpy(table, row, 0, "Error Offset (hex, %)");
	vp_error_offset_get(vp_regs->vp_config,
		&erroffset_curr, &erroffset_curr2);
	erroffset_expected = vp_golden_settings->error_offset;
	erroffset_expected2 = vp_error_offset_hex2percent(erroffset_expected);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN,
		"0x%02X (%.3lf%%)", erroffset_curr, erroffset_curr2);
	snprintf(table[row][2], TABLE_MAX_ELT_LEN,
		"0x%02X (%.3lf%%)", erroffset_expected, erroffset_expected2);
	VP_AUDIT_SHOW_STATUS(erroffset_curr, erroffset_expected);

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

