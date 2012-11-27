/*
 *
 * @Component			OMAPCONF
 * @Filename			emif54xxes1-defs.c
 * @Description			OMAP5 ES1 EMIF Register Address Definitions
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


#include <emif54xxes1-defs.h>
#include <stdio.h>


reg omap5430es1_emif1_emif_revision = {
	"EMIF_REVISION",
	OMAP5430ES1_EMIF1_EMIF_REVISION,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_status = {
	"EMIF_STATUS",
	OMAP5430ES1_EMIF1_EMIF_STATUS,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_sdram_config = {
	"EMIF_SDRAM_CONFIG",
	OMAP5430ES1_EMIF1_EMIF_SDRAM_CONFIG,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_sdram_config_2 = {
	"EMIF_SDRAM_CONFIG_2",
	OMAP5430ES1_EMIF1_EMIF_SDRAM_CONFIG_2,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_sdram_refresh_control = {
	"EMIF_SDRAM_REFRESH_CONTROL",
	OMAP5430ES1_EMIF1_EMIF_SDRAM_REFRESH_CONTROL,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_sdram_refresh_control_shadow = {
	"EMIF_SDRAM_REFRESH_CONTROL_SHADOW",
	OMAP5430ES1_EMIF1_EMIF_SDRAM_REFRESH_CONTROL_SHADOW,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_sdram_timing_1 = {
	"EMIF_SDRAM_TIMING_1",
	OMAP5430ES1_EMIF1_EMIF_SDRAM_TIMING_1,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_sdram_timing_1_shadow = {
	"EMIF_SDRAM_TIMING_1_SHADOW",
	OMAP5430ES1_EMIF1_EMIF_SDRAM_TIMING_1_SHADOW,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_sdram_timing_2 = {
	"EMIF_SDRAM_TIMING_2",
	OMAP5430ES1_EMIF1_EMIF_SDRAM_TIMING_2,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_sdram_timing_2_shadow = {
	"EMIF_SDRAM_TIMING_2_SHADOW",
	OMAP5430ES1_EMIF1_EMIF_SDRAM_TIMING_2_SHADOW,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_sdram_timing_3 = {
	"EMIF_SDRAM_TIMING_3",
	OMAP5430ES1_EMIF1_EMIF_SDRAM_TIMING_3,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_sdram_timing_3_shadow = {
	"EMIF_SDRAM_TIMING_3_SHADOW",
	OMAP5430ES1_EMIF1_EMIF_SDRAM_TIMING_3_SHADOW,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_lpddr2_nvm_timing = {
	"EMIF_LPDDR2_NVM_TIMING",
	OMAP5430ES1_EMIF1_EMIF_LPDDR2_NVM_TIMING,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_lpddr2_nvm_timing_shadow = {
	"EMIF_LPDDR2_NVM_TIMING_SHADOW",
	OMAP5430ES1_EMIF1_EMIF_LPDDR2_NVM_TIMING_SHADOW,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_power_management_control = {
	"EMIF_POWER_MANAGEMENT_CONTROL",
	OMAP5430ES1_EMIF1_EMIF_POWER_MANAGEMENT_CONTROL,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_power_management_control_shadow = {
	"EMIF_POWER_MANAGEMENT_CONTROL_SHADOW",
	OMAP5430ES1_EMIF1_EMIF_POWER_MANAGEMENT_CONTROL_SHADOW,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_lpddr2_mode_data = {
	"EMIF_LPDDR2_MODE_DATA",
	OMAP5430ES1_EMIF1_EMIF_LPDDR2_MODE_DATA,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_lpddr2_mode_reg_config = {
	"EMIF_LPDDR2_MODE_REG_CONFIG",
	OMAP5430ES1_EMIF1_EMIF_LPDDR2_MODE_REG_CONFIG,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_ocp_config = {
	"EMIF_OCP_CONFIG",
	OMAP5430ES1_EMIF1_EMIF_OCP_CONFIG,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_ocp_config_value_1 = {
	"EMIF_OCP_CONFIG_VALUE_1",
	OMAP5430ES1_EMIF1_EMIF_OCP_CONFIG_VALUE_1,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_ocp_config_value_2 = {
	"EMIF_OCP_CONFIG_VALUE_2",
	OMAP5430ES1_EMIF1_EMIF_OCP_CONFIG_VALUE_2,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_performance_counter_1 = {
	"EMIF_PERFORMANCE_COUNTER_1",
	OMAP5430ES1_EMIF1_EMIF_PERFORMANCE_COUNTER_1,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_performance_counter_2 = {
	"EMIF_PERFORMANCE_COUNTER_2",
	OMAP5430ES1_EMIF1_EMIF_PERFORMANCE_COUNTER_2,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_performance_counter_config = {
	"EMIF_PERFORMANCE_COUNTER_CONFIG",
	OMAP5430ES1_EMIF1_EMIF_PERFORMANCE_COUNTER_CONFIG,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_performance_counter_master_region_select = {
	"EMIF_PERFORMANCE_COUNTER_MASTER_REGION_SELECT",
	OMAP5430ES1_EMIF1_EMIF_PERFORMANCE_COUNTER_MASTER_REGION_SELECT,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_performance_counter_time = {
	"EMIF_PERFORMANCE_COUNTER_TIME",
	OMAP5430ES1_EMIF1_EMIF_PERFORMANCE_COUNTER_TIME,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_dll_calib_ctrl = {
	"EMIF_DLL_CALIB_CTRL",
	OMAP5430ES1_EMIF1_EMIF_DLL_CALIB_CTRL,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_dll_calib_ctrl_shadow = {
	"EMIF_DLL_CALIB_CTRL_SHADOW",
	OMAP5430ES1_EMIF1_EMIF_DLL_CALIB_CTRL_SHADOW,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_system_ocp_interrupt_raw_status = {
	"EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS",
	OMAP5430ES1_EMIF1_EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_low_latency_ocp_interrupt_raw_status = {
	"EMIF_LOW_LATENCY_OCP_INTERRUPT_RAW_STATUS",
	OMAP5430ES1_EMIF1_EMIF_LOW_LATENCY_OCP_INTERRUPT_RAW_STATUS,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_system_ocp_interrupt_status = {
	"EMIF_SYSTEM_OCP_INTERRUPT_STATUS",
	OMAP5430ES1_EMIF1_EMIF_SYSTEM_OCP_INTERRUPT_STATUS,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_low_latency_ocp_interrupt_status = {
	"EMIF_LOW_LATENCY_OCP_INTERRUPT_STATUS",
	OMAP5430ES1_EMIF1_EMIF_LOW_LATENCY_OCP_INTERRUPT_STATUS,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_system_ocp_interrupt_enable_set = {
	"EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET",
	OMAP5430ES1_EMIF1_EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_low_latency_ocp_interrupt_enable_set = {
	"EMIF_LOW_LATENCY_OCP_INTERRUPT_ENABLE_SET",
	OMAP5430ES1_EMIF1_EMIF_LOW_LATENCY_OCP_INTERRUPT_ENABLE_SET,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_system_ocp_interrupt_enable_clear = {
	"EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR",
	OMAP5430ES1_EMIF1_EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_low_latency_ocp_interrupt_enable_clear = {
	"EMIF_LOW_LATENCY_OCP_INTERRUPT_ENABLE_CLEAR",
	OMAP5430ES1_EMIF1_EMIF_LOW_LATENCY_OCP_INTERRUPT_ENABLE_CLEAR,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_sdram_output_impedance_calibration_config = {
	"EMIF_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG",
	OMAP5430ES1_EMIF1_EMIF_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_temperature_alert_config = {
	"EMIF_TEMPERATURE_ALERT_CONFIG",
	OMAP5430ES1_EMIF1_EMIF_TEMPERATURE_ALERT_CONFIG,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_ocp_error_log = {
	"EMIF_OCP_ERROR_LOG",
	OMAP5430ES1_EMIF1_EMIF_OCP_ERROR_LOG,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_read_write_leveling_ramp_window = {
	"EMIF_READ_WRITE_LEVELING_RAMP_WINDOW",
	OMAP5430ES1_EMIF1_EMIF_READ_WRITE_LEVELING_RAMP_WINDOW,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_read_write_leveling_ramp_control = {
	"EMIF_READ_WRITE_LEVELING_RAMP_CONTROL",
	OMAP5430ES1_EMIF1_EMIF_READ_WRITE_LEVELING_RAMP_CONTROL,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_read_write_leveling_control = {
	"EMIF_READ_WRITE_LEVELING_CONTROL",
	OMAP5430ES1_EMIF1_EMIF_READ_WRITE_LEVELING_CONTROL,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_ddr_phy_control_1 = {
	"EMIF_DDR_PHY_CONTROL_1",
	OMAP5430ES1_EMIF1_EMIF_DDR_PHY_CONTROL_1,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_ddr_phy_control_1_shadow = {
	"EMIF_DDR_PHY_CONTROL_1_SHADOW",
	OMAP5430ES1_EMIF1_EMIF_DDR_PHY_CONTROL_1_SHADOW,
	0xDEADBEEF,
	0};

reg omap5430es1_emif1_emif_ddr_phy_control_2 = {
	"EMIF_DDR_PHY_CONTROL_2",
	OMAP5430ES1_EMIF1_EMIF_DDR_PHY_CONTROL_2,
	0xDEADBEEF,
	0};

reg *omap5430es1_emif1_mod[OMAP5430ES1_EMIF1_MOD_REGCOUNT + 1] = {
	&omap5430es1_emif1_emif_revision,
	&omap5430es1_emif1_emif_status,
	&omap5430es1_emif1_emif_sdram_config,
	&omap5430es1_emif1_emif_sdram_config_2,
	&omap5430es1_emif1_emif_sdram_refresh_control,
	&omap5430es1_emif1_emif_sdram_refresh_control_shadow,
	&omap5430es1_emif1_emif_sdram_timing_1,
	&omap5430es1_emif1_emif_sdram_timing_1_shadow,
	&omap5430es1_emif1_emif_sdram_timing_2,
	&omap5430es1_emif1_emif_sdram_timing_2_shadow,
	&omap5430es1_emif1_emif_sdram_timing_3,
	&omap5430es1_emif1_emif_sdram_timing_3_shadow,
	&omap5430es1_emif1_emif_lpddr2_nvm_timing,
	&omap5430es1_emif1_emif_lpddr2_nvm_timing_shadow,
	&omap5430es1_emif1_emif_power_management_control,
	&omap5430es1_emif1_emif_power_management_control_shadow,
	&omap5430es1_emif1_emif_lpddr2_mode_data,
	&omap5430es1_emif1_emif_lpddr2_mode_reg_config,
	&omap5430es1_emif1_emif_ocp_config,
	&omap5430es1_emif1_emif_ocp_config_value_1,
	&omap5430es1_emif1_emif_ocp_config_value_2,
	&omap5430es1_emif1_emif_performance_counter_1,
	&omap5430es1_emif1_emif_performance_counter_2,
	&omap5430es1_emif1_emif_performance_counter_config,
	&omap5430es1_emif1_emif_performance_counter_master_region_select,
	&omap5430es1_emif1_emif_performance_counter_time,
	&omap5430es1_emif1_emif_dll_calib_ctrl,
	&omap5430es1_emif1_emif_dll_calib_ctrl_shadow,
	&omap5430es1_emif1_emif_system_ocp_interrupt_raw_status,
	&omap5430es1_emif1_emif_low_latency_ocp_interrupt_raw_status,
	&omap5430es1_emif1_emif_system_ocp_interrupt_status,
	&omap5430es1_emif1_emif_low_latency_ocp_interrupt_status,
	&omap5430es1_emif1_emif_system_ocp_interrupt_enable_set,
	&omap5430es1_emif1_emif_low_latency_ocp_interrupt_enable_set,
	&omap5430es1_emif1_emif_system_ocp_interrupt_enable_clear,
	&omap5430es1_emif1_emif_low_latency_ocp_interrupt_enable_clear,
	&omap5430es1_emif1_emif_sdram_output_impedance_calibration_config,
	&omap5430es1_emif1_emif_temperature_alert_config,
	&omap5430es1_emif1_emif_ocp_error_log,
	&omap5430es1_emif1_emif_read_write_leveling_ramp_window,
	&omap5430es1_emif1_emif_read_write_leveling_ramp_control,
	&omap5430es1_emif1_emif_read_write_leveling_control,
	&omap5430es1_emif1_emif_ddr_phy_control_1,
	&omap5430es1_emif1_emif_ddr_phy_control_1_shadow,
	&omap5430es1_emif1_emif_ddr_phy_control_2,
	NULL};

reg omap5430es1_emif2_emif_revision = {
	"EMIF_REVISION",
	OMAP5430ES1_EMIF2_EMIF_REVISION,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_status = {
	"EMIF_STATUS",
	OMAP5430ES1_EMIF2_EMIF_STATUS,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_sdram_config = {
	"EMIF_SDRAM_CONFIG",
	OMAP5430ES1_EMIF2_EMIF_SDRAM_CONFIG,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_sdram_config_2 = {
	"EMIF_SDRAM_CONFIG_2",
	OMAP5430ES1_EMIF2_EMIF_SDRAM_CONFIG_2,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_sdram_refresh_control = {
	"EMIF_SDRAM_REFRESH_CONTROL",
	OMAP5430ES1_EMIF2_EMIF_SDRAM_REFRESH_CONTROL,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_sdram_refresh_control_shadow = {
	"EMIF_SDRAM_REFRESH_CONTROL_SHADOW",
	OMAP5430ES1_EMIF2_EMIF_SDRAM_REFRESH_CONTROL_SHADOW,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_sdram_timing_1 = {
	"EMIF_SDRAM_TIMING_1",
	OMAP5430ES1_EMIF2_EMIF_SDRAM_TIMING_1,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_sdram_timing_1_shadow = {
	"EMIF_SDRAM_TIMING_1_SHADOW",
	OMAP5430ES1_EMIF2_EMIF_SDRAM_TIMING_1_SHADOW,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_sdram_timing_2 = {
	"EMIF_SDRAM_TIMING_2",
	OMAP5430ES1_EMIF2_EMIF_SDRAM_TIMING_2,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_sdram_timing_2_shadow = {
	"EMIF_SDRAM_TIMING_2_SHADOW",
	OMAP5430ES1_EMIF2_EMIF_SDRAM_TIMING_2_SHADOW,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_sdram_timing_3 = {
	"EMIF_SDRAM_TIMING_3",
	OMAP5430ES1_EMIF2_EMIF_SDRAM_TIMING_3,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_sdram_timing_3_shadow = {
	"EMIF_SDRAM_TIMING_3_SHADOW",
	OMAP5430ES1_EMIF2_EMIF_SDRAM_TIMING_3_SHADOW,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_lpddr2_nvm_timing = {
	"EMIF_LPDDR2_NVM_TIMING",
	OMAP5430ES1_EMIF2_EMIF_LPDDR2_NVM_TIMING,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_lpddr2_nvm_timing_shadow = {
	"EMIF_LPDDR2_NVM_TIMING_SHADOW",
	OMAP5430ES1_EMIF2_EMIF_LPDDR2_NVM_TIMING_SHADOW,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_power_management_control = {
	"EMIF_POWER_MANAGEMENT_CONTROL",
	OMAP5430ES1_EMIF2_EMIF_POWER_MANAGEMENT_CONTROL,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_power_management_control_shadow = {
	"EMIF_POWER_MANAGEMENT_CONTROL_SHADOW",
	OMAP5430ES1_EMIF2_EMIF_POWER_MANAGEMENT_CONTROL_SHADOW,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_lpddr2_mode_data = {
	"EMIF_LPDDR2_MODE_DATA",
	OMAP5430ES1_EMIF2_EMIF_LPDDR2_MODE_DATA,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_lpddr2_mode_reg_config = {
	"EMIF_LPDDR2_MODE_REG_CONFIG",
	OMAP5430ES1_EMIF2_EMIF_LPDDR2_MODE_REG_CONFIG,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_ocp_config = {
	"EMIF_OCP_CONFIG",
	OMAP5430ES1_EMIF2_EMIF_OCP_CONFIG,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_ocp_config_value_1 = {
	"EMIF_OCP_CONFIG_VALUE_1",
	OMAP5430ES1_EMIF2_EMIF_OCP_CONFIG_VALUE_1,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_ocp_config_value_2 = {
	"EMIF_OCP_CONFIG_VALUE_2",
	OMAP5430ES1_EMIF2_EMIF_OCP_CONFIG_VALUE_2,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_performance_counter_1 = {
	"EMIF_PERFORMANCE_COUNTER_1",
	OMAP5430ES1_EMIF2_EMIF_PERFORMANCE_COUNTER_1,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_performance_counter_2 = {
	"EMIF_PERFORMANCE_COUNTER_2",
	OMAP5430ES1_EMIF2_EMIF_PERFORMANCE_COUNTER_2,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_performance_counter_config = {
	"EMIF_PERFORMANCE_COUNTER_CONFIG",
	OMAP5430ES1_EMIF2_EMIF_PERFORMANCE_COUNTER_CONFIG,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_performance_counter_master_region_select = {
	"EMIF_PERFORMANCE_COUNTER_MASTER_REGION_SELECT",
	OMAP5430ES1_EMIF2_EMIF_PERFORMANCE_COUNTER_MASTER_REGION_SELECT,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_performance_counter_time = {
	"EMIF_PERFORMANCE_COUNTER_TIME",
	OMAP5430ES1_EMIF2_EMIF_PERFORMANCE_COUNTER_TIME,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_dll_calib_ctrl = {
	"EMIF_DLL_CALIB_CTRL",
	OMAP5430ES1_EMIF2_EMIF_DLL_CALIB_CTRL,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_dll_calib_ctrl_shadow = {
	"EMIF_DLL_CALIB_CTRL_SHADOW",
	OMAP5430ES1_EMIF2_EMIF_DLL_CALIB_CTRL_SHADOW,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_system_ocp_interrupt_raw_status = {
	"EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS",
	OMAP5430ES1_EMIF2_EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_low_latency_ocp_interrupt_raw_status = {
	"EMIF_LOW_LATENCY_OCP_INTERRUPT_RAW_STATUS",
	OMAP5430ES1_EMIF2_EMIF_LOW_LATENCY_OCP_INTERRUPT_RAW_STATUS,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_system_ocp_interrupt_status = {
	"EMIF_SYSTEM_OCP_INTERRUPT_STATUS",
	OMAP5430ES1_EMIF2_EMIF_SYSTEM_OCP_INTERRUPT_STATUS,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_low_latency_ocp_interrupt_status = {
	"EMIF_LOW_LATENCY_OCP_INTERRUPT_STATUS",
	OMAP5430ES1_EMIF2_EMIF_LOW_LATENCY_OCP_INTERRUPT_STATUS,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_system_ocp_interrupt_enable_set = {
	"EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET",
	OMAP5430ES1_EMIF2_EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_low_latency_ocp_interrupt_enable_set = {
	"EMIF_LOW_LATENCY_OCP_INTERRUPT_ENABLE_SET",
	OMAP5430ES1_EMIF2_EMIF_LOW_LATENCY_OCP_INTERRUPT_ENABLE_SET,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_system_ocp_interrupt_enable_clear = {
	"EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR",
	OMAP5430ES1_EMIF2_EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_low_latency_ocp_interrupt_enable_clear = {
	"EMIF_LOW_LATENCY_OCP_INTERRUPT_ENABLE_CLEAR",
	OMAP5430ES1_EMIF2_EMIF_LOW_LATENCY_OCP_INTERRUPT_ENABLE_CLEAR,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_sdram_output_impedance_calibration_config = {
	"EMIF_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG",
	OMAP5430ES1_EMIF2_EMIF_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_temperature_alert_config = {
	"EMIF_TEMPERATURE_ALERT_CONFIG",
	OMAP5430ES1_EMIF2_EMIF_TEMPERATURE_ALERT_CONFIG,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_ocp_error_log = {
	"EMIF_OCP_ERROR_LOG",
	OMAP5430ES1_EMIF2_EMIF_OCP_ERROR_LOG,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_read_write_leveling_ramp_window = {
	"EMIF_READ_WRITE_LEVELING_RAMP_WINDOW",
	OMAP5430ES1_EMIF2_EMIF_READ_WRITE_LEVELING_RAMP_WINDOW,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_read_write_leveling_ramp_control = {
	"EMIF_READ_WRITE_LEVELING_RAMP_CONTROL",
	OMAP5430ES1_EMIF2_EMIF_READ_WRITE_LEVELING_RAMP_CONTROL,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_read_write_leveling_control = {
	"EMIF_READ_WRITE_LEVELING_CONTROL",
	OMAP5430ES1_EMIF2_EMIF_READ_WRITE_LEVELING_CONTROL,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_ddr_phy_control_1 = {
	"EMIF_DDR_PHY_CONTROL_1",
	OMAP5430ES1_EMIF2_EMIF_DDR_PHY_CONTROL_1,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_ddr_phy_control_1_shadow = {
	"EMIF_DDR_PHY_CONTROL_1_SHADOW",
	OMAP5430ES1_EMIF2_EMIF_DDR_PHY_CONTROL_1_SHADOW,
	0xDEADBEEF,
	0};

reg omap5430es1_emif2_emif_ddr_phy_control_2 = {
	"EMIF_DDR_PHY_CONTROL_2",
	OMAP5430ES1_EMIF2_EMIF_DDR_PHY_CONTROL_2,
	0xDEADBEEF,
	0};

reg *omap5430es1_emif2_mod[OMAP5430ES1_EMIF2_MOD_REGCOUNT + 1] = {
	&omap5430es1_emif2_emif_revision,
	&omap5430es1_emif2_emif_status,
	&omap5430es1_emif2_emif_sdram_config,
	&omap5430es1_emif2_emif_sdram_config_2,
	&omap5430es1_emif2_emif_sdram_refresh_control,
	&omap5430es1_emif2_emif_sdram_refresh_control_shadow,
	&omap5430es1_emif2_emif_sdram_timing_1,
	&omap5430es1_emif2_emif_sdram_timing_1_shadow,
	&omap5430es1_emif2_emif_sdram_timing_2,
	&omap5430es1_emif2_emif_sdram_timing_2_shadow,
	&omap5430es1_emif2_emif_sdram_timing_3,
	&omap5430es1_emif2_emif_sdram_timing_3_shadow,
	&omap5430es1_emif2_emif_lpddr2_nvm_timing,
	&omap5430es1_emif2_emif_lpddr2_nvm_timing_shadow,
	&omap5430es1_emif2_emif_power_management_control,
	&omap5430es1_emif2_emif_power_management_control_shadow,
	&omap5430es1_emif2_emif_lpddr2_mode_data,
	&omap5430es1_emif2_emif_lpddr2_mode_reg_config,
	&omap5430es1_emif2_emif_ocp_config,
	&omap5430es1_emif2_emif_ocp_config_value_1,
	&omap5430es1_emif2_emif_ocp_config_value_2,
	&omap5430es1_emif2_emif_performance_counter_1,
	&omap5430es1_emif2_emif_performance_counter_2,
	&omap5430es1_emif2_emif_performance_counter_config,
	&omap5430es1_emif2_emif_performance_counter_master_region_select,
	&omap5430es1_emif2_emif_performance_counter_time,
	&omap5430es1_emif2_emif_dll_calib_ctrl,
	&omap5430es1_emif2_emif_dll_calib_ctrl_shadow,
	&omap5430es1_emif2_emif_system_ocp_interrupt_raw_status,
	&omap5430es1_emif2_emif_low_latency_ocp_interrupt_raw_status,
	&omap5430es1_emif2_emif_system_ocp_interrupt_status,
	&omap5430es1_emif2_emif_low_latency_ocp_interrupt_status,
	&omap5430es1_emif2_emif_system_ocp_interrupt_enable_set,
	&omap5430es1_emif2_emif_low_latency_ocp_interrupt_enable_set,
	&omap5430es1_emif2_emif_system_ocp_interrupt_enable_clear,
	&omap5430es1_emif2_emif_low_latency_ocp_interrupt_enable_clear,
	&omap5430es1_emif2_emif_sdram_output_impedance_calibration_config,
	&omap5430es1_emif2_emif_temperature_alert_config,
	&omap5430es1_emif2_emif_ocp_error_log,
	&omap5430es1_emif2_emif_read_write_leveling_ramp_window,
	&omap5430es1_emif2_emif_read_write_leveling_ramp_control,
	&omap5430es1_emif2_emif_read_write_leveling_control,
	&omap5430es1_emif2_emif_ddr_phy_control_1,
	&omap5430es1_emif2_emif_ddr_phy_control_1_shadow,
	&omap5430es1_emif2_emif_ddr_phy_control_2,
	NULL};


reg **emif54xxes1_mods[EMIF54XXES1_MODS_COUNT] = {
	(reg **) &omap5430es1_emif1_mod,
	(reg **) &omap5430es1_emif2_mod};
