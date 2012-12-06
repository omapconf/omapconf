/*
 *
 * @Component			OMAPCONF
 * @Filename			emif54xxes1-defs.h
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


#ifndef __EMIF54XXES1_DEFS_H__
#define __EMIF54XXES1_DEFS_H__


#include <reg.h>


#define OMAP5430ES1_EMIF1_EMIF_REVISION					0x4c000000
extern reg omap5430es1_emif1_emif_revision;
#define OMAP5430ES1_EMIF1_EMIF_STATUS					0x4c000004
extern reg omap5430es1_emif1_emif_status;
#define OMAP5430ES1_EMIF1_EMIF_SDRAM_CONFIG				0x4c000008
extern reg omap5430es1_emif1_emif_sdram_config;
#define OMAP5430ES1_EMIF1_EMIF_SDRAM_CONFIG_2				0x4c00000c
extern reg omap5430es1_emif1_emif_sdram_config_2;
#define OMAP5430ES1_EMIF1_EMIF_SDRAM_REFRESH_CONTROL			0x4c000010
extern reg omap5430es1_emif1_emif_sdram_refresh_control;
#define OMAP5430ES1_EMIF1_EMIF_SDRAM_REFRESH_CONTROL_SHADOW		0x4c000014
extern reg omap5430es1_emif1_emif_sdram_refresh_control_shadow;
#define OMAP5430ES1_EMIF1_EMIF_SDRAM_TIMING_1				0x4c000018
extern reg omap5430es1_emif1_emif_sdram_timing_1;
#define OMAP5430ES1_EMIF1_EMIF_SDRAM_TIMING_1_SHADOW			0x4c00001c
extern reg omap5430es1_emif1_emif_sdram_timing_1_shadow;
#define OMAP5430ES1_EMIF1_EMIF_SDRAM_TIMING_2				0x4c000020
extern reg omap5430es1_emif1_emif_sdram_timing_2;
#define OMAP5430ES1_EMIF1_EMIF_SDRAM_TIMING_2_SHADOW			0x4c000024
extern reg omap5430es1_emif1_emif_sdram_timing_2_shadow;
#define OMAP5430ES1_EMIF1_EMIF_SDRAM_TIMING_3				0x4c000028
extern reg omap5430es1_emif1_emif_sdram_timing_3;
#define OMAP5430ES1_EMIF1_EMIF_SDRAM_TIMING_3_SHADOW			0x4c00002c
extern reg omap5430es1_emif1_emif_sdram_timing_3_shadow;
#define OMAP5430ES1_EMIF1_EMIF_LPDDR2_NVM_TIMING			0x4c000030
extern reg omap5430es1_emif1_emif_lpddr2_nvm_timing;
#define OMAP5430ES1_EMIF1_EMIF_LPDDR2_NVM_TIMING_SHADOW			0x4c000034
extern reg omap5430es1_emif1_emif_lpddr2_nvm_timing_shadow;
#define OMAP5430ES1_EMIF1_EMIF_POWER_MANAGEMENT_CONTROL			0x4c000038
extern reg omap5430es1_emif1_emif_power_management_control;
#define OMAP5430ES1_EMIF1_EMIF_POWER_MANAGEMENT_CONTROL_SHADOW		0x4c00003c
extern reg omap5430es1_emif1_emif_power_management_control_shadow;
#define OMAP5430ES1_EMIF1_EMIF_LPDDR2_MODE_DATA				0x4c000040
extern reg omap5430es1_emif1_emif_lpddr2_mode_data;
#define OMAP5430ES1_EMIF1_EMIF_LPDDR2_MODE_REG_CONFIG			0x4c000050
extern reg omap5430es1_emif1_emif_lpddr2_mode_reg_config;
#define OMAP5430ES1_EMIF1_EMIF_OCP_CONFIG				0x4c000054
extern reg omap5430es1_emif1_emif_ocp_config;
#define OMAP5430ES1_EMIF1_EMIF_OCP_CONFIG_VALUE_1			0x4c000058
extern reg omap5430es1_emif1_emif_ocp_config_value_1;
#define OMAP5430ES1_EMIF1_EMIF_OCP_CONFIG_VALUE_2			0x4c00005c
extern reg omap5430es1_emif1_emif_ocp_config_value_2;
#define OMAP5430ES1_EMIF1_EMIF_PERFORMANCE_COUNTER_1			0x4c000080
extern reg omap5430es1_emif1_emif_performance_counter_1;
#define OMAP5430ES1_EMIF1_EMIF_PERFORMANCE_COUNTER_2			0x4c000084
extern reg omap5430es1_emif1_emif_performance_counter_2;
#define OMAP5430ES1_EMIF1_EMIF_PERFORMANCE_COUNTER_CONFIG		0x4c000088
extern reg omap5430es1_emif1_emif_performance_counter_config;
#define OMAP5430ES1_EMIF1_EMIF_PERFORMANCE_COUNTER_MASTER_REGION_SELECT	0x4c00008c
extern reg omap5430es1_emif1_emif_performance_counter_master_region_select;
#define OMAP5430ES1_EMIF1_EMIF_PERFORMANCE_COUNTER_TIME			0x4c000090
extern reg omap5430es1_emif1_emif_performance_counter_time;
#define OMAP5430ES1_EMIF1_EMIF_DLL_CALIB_CTRL				0x4c000098
extern reg omap5430es1_emif1_emif_dll_calib_ctrl;
#define OMAP5430ES1_EMIF1_EMIF_DLL_CALIB_CTRL_SHADOW			0x4c00009c
extern reg omap5430es1_emif1_emif_dll_calib_ctrl_shadow;
#define OMAP5430ES1_EMIF1_EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS		0x4c0000a4
extern reg omap5430es1_emif1_emif_system_ocp_interrupt_raw_status;
#define OMAP5430ES1_EMIF1_EMIF_LOW_LATENCY_OCP_INTERRUPT_RAW_STATUS	0x4c0000a8
extern reg omap5430es1_emif1_emif_low_latency_ocp_interrupt_raw_status;
#define OMAP5430ES1_EMIF1_EMIF_SYSTEM_OCP_INTERRUPT_STATUS		0x4c0000ac
extern reg omap5430es1_emif1_emif_system_ocp_interrupt_status;
#define OMAP5430ES1_EMIF1_EMIF_LOW_LATENCY_OCP_INTERRUPT_STATUS		0x4c0000b0
extern reg omap5430es1_emif1_emif_low_latency_ocp_interrupt_status;
#define OMAP5430ES1_EMIF1_EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET		0x4c0000b4
extern reg omap5430es1_emif1_emif_system_ocp_interrupt_enable_set;
#define OMAP5430ES1_EMIF1_EMIF_LOW_LATENCY_OCP_INTERRUPT_ENABLE_SET	0x4c0000b8
extern reg omap5430es1_emif1_emif_low_latency_ocp_interrupt_enable_set;
#define OMAP5430ES1_EMIF1_EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR	0x4c0000bc
extern reg omap5430es1_emif1_emif_system_ocp_interrupt_enable_clear;
#define OMAP5430ES1_EMIF1_EMIF_LOW_LATENCY_OCP_INTERRUPT_ENABLE_CLEAR	0x4c0000c0
extern reg omap5430es1_emif1_emif_low_latency_ocp_interrupt_enable_clear;
#define OMAP5430ES1_EMIF1_EMIF_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG	0x4c0000c8
extern reg omap5430es1_emif1_emif_sdram_output_impedance_calibration_config;
#define OMAP5430ES1_EMIF1_EMIF_TEMPERATURE_ALERT_CONFIG			0x4c0000cc
extern reg omap5430es1_emif1_emif_temperature_alert_config;
#define OMAP5430ES1_EMIF1_EMIF_OCP_ERROR_LOG				0x4c0000d0
extern reg omap5430es1_emif1_emif_ocp_error_log;
#define OMAP5430ES1_EMIF1_EMIF_READ_WRITE_LEVELING_RAMP_WINDOW		0x4c0000d4
extern reg omap5430es1_emif1_emif_read_write_leveling_ramp_window;
#define OMAP5430ES1_EMIF1_EMIF_READ_WRITE_LEVELING_RAMP_CONTROL		0x4c0000d8
extern reg omap5430es1_emif1_emif_read_write_leveling_ramp_control;
#define OMAP5430ES1_EMIF1_EMIF_READ_WRITE_LEVELING_CONTROL		0x4c0000dc
extern reg omap5430es1_emif1_emif_read_write_leveling_control;
#define OMAP5430ES1_EMIF1_EMIF_DDR_PHY_CONTROL_1			0x4c0000e4
extern reg omap5430es1_emif1_emif_ddr_phy_control_1;
#define OMAP5430ES1_EMIF1_EMIF_DDR_PHY_CONTROL_1_SHADOW			0x4c0000e8
extern reg omap5430es1_emif1_emif_ddr_phy_control_1_shadow;
#define OMAP5430ES1_EMIF1_EMIF_DDR_PHY_CONTROL_2			0x4c0000ec
extern reg omap5430es1_emif1_emif_ddr_phy_control_2;
#define OMAP5430ES1_EMIF1_MOD_REGCOUNT					45
extern reg *omap5430es1_emif1_mod[OMAP5430ES1_EMIF1_MOD_REGCOUNT + 1];

#define OMAP5430ES1_EMIF2_EMIF_REVISION					0x4d000000
extern reg omap5430es1_emif2_emif_revision;
#define OMAP5430ES1_EMIF2_EMIF_STATUS					0x4d000004
extern reg omap5430es1_emif2_emif_status;
#define OMAP5430ES1_EMIF2_EMIF_SDRAM_CONFIG				0x4d000008
extern reg omap5430es1_emif2_emif_sdram_config;
#define OMAP5430ES1_EMIF2_EMIF_SDRAM_CONFIG_2				0x4d00000c
extern reg omap5430es1_emif2_emif_sdram_config_2;
#define OMAP5430ES1_EMIF2_EMIF_SDRAM_REFRESH_CONTROL			0x4d000010
extern reg omap5430es1_emif2_emif_sdram_refresh_control;
#define OMAP5430ES1_EMIF2_EMIF_SDRAM_REFRESH_CONTROL_SHADOW		0x4d000014
extern reg omap5430es1_emif2_emif_sdram_refresh_control_shadow;
#define OMAP5430ES1_EMIF2_EMIF_SDRAM_TIMING_1				0x4d000018
extern reg omap5430es1_emif2_emif_sdram_timing_1;
#define OMAP5430ES1_EMIF2_EMIF_SDRAM_TIMING_1_SHADOW			0x4d00001c
extern reg omap5430es1_emif2_emif_sdram_timing_1_shadow;
#define OMAP5430ES1_EMIF2_EMIF_SDRAM_TIMING_2				0x4d000020
extern reg omap5430es1_emif2_emif_sdram_timing_2;
#define OMAP5430ES1_EMIF2_EMIF_SDRAM_TIMING_2_SHADOW			0x4d000024
extern reg omap5430es1_emif2_emif_sdram_timing_2_shadow;
#define OMAP5430ES1_EMIF2_EMIF_SDRAM_TIMING_3				0x4d000028
extern reg omap5430es1_emif2_emif_sdram_timing_3;
#define OMAP5430ES1_EMIF2_EMIF_SDRAM_TIMING_3_SHADOW			0x4d00002c
extern reg omap5430es1_emif2_emif_sdram_timing_3_shadow;
#define OMAP5430ES1_EMIF2_EMIF_LPDDR2_NVM_TIMING			0x4d000030
extern reg omap5430es1_emif2_emif_lpddr2_nvm_timing;
#define OMAP5430ES1_EMIF2_EMIF_LPDDR2_NVM_TIMING_SHADOW			0x4d000034
extern reg omap5430es1_emif2_emif_lpddr2_nvm_timing_shadow;
#define OMAP5430ES1_EMIF2_EMIF_POWER_MANAGEMENT_CONTROL			0x4d000038
extern reg omap5430es1_emif2_emif_power_management_control;
#define OMAP5430ES1_EMIF2_EMIF_POWER_MANAGEMENT_CONTROL_SHADOW		0x4d00003c
extern reg omap5430es1_emif2_emif_power_management_control_shadow;
#define OMAP5430ES1_EMIF2_EMIF_LPDDR2_MODE_DATA				0x4d000040
extern reg omap5430es1_emif2_emif_lpddr2_mode_data;
#define OMAP5430ES1_EMIF2_EMIF_LPDDR2_MODE_REG_CONFIG			0x4d000050
extern reg omap5430es1_emif2_emif_lpddr2_mode_reg_config;
#define OMAP5430ES1_EMIF2_EMIF_OCP_CONFIG				0x4d000054
extern reg omap5430es1_emif2_emif_ocp_config;
#define OMAP5430ES1_EMIF2_EMIF_OCP_CONFIG_VALUE_1			0x4d000058
extern reg omap5430es1_emif2_emif_ocp_config_value_1;
#define OMAP5430ES1_EMIF2_EMIF_OCP_CONFIG_VALUE_2			0x4d00005c
extern reg omap5430es1_emif2_emif_ocp_config_value_2;
#define OMAP5430ES1_EMIF2_EMIF_PERFORMANCE_COUNTER_1			0x4d000080
extern reg omap5430es1_emif2_emif_performance_counter_1;
#define OMAP5430ES1_EMIF2_EMIF_PERFORMANCE_COUNTER_2			0x4d000084
extern reg omap5430es1_emif2_emif_performance_counter_2;
#define OMAP5430ES1_EMIF2_EMIF_PERFORMANCE_COUNTER_CONFIG		0x4d000088
extern reg omap5430es1_emif2_emif_performance_counter_config;
#define OMAP5430ES1_EMIF2_EMIF_PERFORMANCE_COUNTER_MASTER_REGION_SELECT	0x4d00008c
extern reg omap5430es1_emif2_emif_performance_counter_master_region_select;
#define OMAP5430ES1_EMIF2_EMIF_PERFORMANCE_COUNTER_TIME			0x4d000090
extern reg omap5430es1_emif2_emif_performance_counter_time;
#define OMAP5430ES1_EMIF2_EMIF_DLL_CALIB_CTRL				0x4d000098
extern reg omap5430es1_emif2_emif_dll_calib_ctrl;
#define OMAP5430ES1_EMIF2_EMIF_DLL_CALIB_CTRL_SHADOW			0x4d00009c
extern reg omap5430es1_emif2_emif_dll_calib_ctrl_shadow;
#define OMAP5430ES1_EMIF2_EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS		0x4d0000a4
extern reg omap5430es1_emif2_emif_system_ocp_interrupt_raw_status;
#define OMAP5430ES1_EMIF2_EMIF_LOW_LATENCY_OCP_INTERRUPT_RAW_STATUS	0x4d0000a8
extern reg omap5430es1_emif2_emif_low_latency_ocp_interrupt_raw_status;
#define OMAP5430ES1_EMIF2_EMIF_SYSTEM_OCP_INTERRUPT_STATUS		0x4d0000ac
extern reg omap5430es1_emif2_emif_system_ocp_interrupt_status;
#define OMAP5430ES1_EMIF2_EMIF_LOW_LATENCY_OCP_INTERRUPT_STATUS		0x4d0000b0
extern reg omap5430es1_emif2_emif_low_latency_ocp_interrupt_status;
#define OMAP5430ES1_EMIF2_EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET		0x4d0000b4
extern reg omap5430es1_emif2_emif_system_ocp_interrupt_enable_set;
#define OMAP5430ES1_EMIF2_EMIF_LOW_LATENCY_OCP_INTERRUPT_ENABLE_SET	0x4d0000b8
extern reg omap5430es1_emif2_emif_low_latency_ocp_interrupt_enable_set;
#define OMAP5430ES1_EMIF2_EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR	0x4d0000bc
extern reg omap5430es1_emif2_emif_system_ocp_interrupt_enable_clear;
#define OMAP5430ES1_EMIF2_EMIF_LOW_LATENCY_OCP_INTERRUPT_ENABLE_CLEAR	0x4d0000c0
extern reg omap5430es1_emif2_emif_low_latency_ocp_interrupt_enable_clear;
#define OMAP5430ES1_EMIF2_EMIF_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG	0x4d0000c8
extern reg omap5430es1_emif2_emif_sdram_output_impedance_calibration_config;
#define OMAP5430ES1_EMIF2_EMIF_TEMPERATURE_ALERT_CONFIG			0x4d0000cc
extern reg omap5430es1_emif2_emif_temperature_alert_config;
#define OMAP5430ES1_EMIF2_EMIF_OCP_ERROR_LOG				0x4d0000d0
extern reg omap5430es1_emif2_emif_ocp_error_log;
#define OMAP5430ES1_EMIF2_EMIF_READ_WRITE_LEVELING_RAMP_WINDOW		0x4d0000d4
extern reg omap5430es1_emif2_emif_read_write_leveling_ramp_window;
#define OMAP5430ES1_EMIF2_EMIF_READ_WRITE_LEVELING_RAMP_CONTROL		0x4d0000d8
extern reg omap5430es1_emif2_emif_read_write_leveling_ramp_control;
#define OMAP5430ES1_EMIF2_EMIF_READ_WRITE_LEVELING_CONTROL		0x4d0000dc
extern reg omap5430es1_emif2_emif_read_write_leveling_control;
#define OMAP5430ES1_EMIF2_EMIF_DDR_PHY_CONTROL_1			0x4d0000e4
extern reg omap5430es1_emif2_emif_ddr_phy_control_1;
#define OMAP5430ES1_EMIF2_EMIF_DDR_PHY_CONTROL_1_SHADOW			0x4d0000e8
extern reg omap5430es1_emif2_emif_ddr_phy_control_1_shadow;
#define OMAP5430ES1_EMIF2_EMIF_DDR_PHY_CONTROL_2			0x4d0000ec
extern reg omap5430es1_emif2_emif_ddr_phy_control_2;
#define OMAP5430ES1_EMIF2_MOD_REGCOUNT					45
extern reg *omap5430es1_emif2_mod[OMAP5430ES1_EMIF2_MOD_REGCOUNT + 1];


#define EMIF54XXES1_MODS_COUNT		2
extern reg **emif54xxes1_mods[EMIF54XXES1_MODS_COUNT];


#endif
