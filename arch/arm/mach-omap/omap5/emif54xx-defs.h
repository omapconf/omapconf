/*
 *
 * @Component			OMAPCONF
 * @Filename			emif54xx-defs.h
 * @Description			OMAP5 ES2 EMIF Register Address Definitions
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


#ifndef __EMIF54XX_DEFS_H__
#define __EMIF54XX_DEFS_H__


#include <emif54xxes1-defs.h>
#include <reg.h>
#include <stdio.h>


#define OMAP5430_EMIF1_EMIF_REVISION					0x4c000000
extern reg omap5430_emif1_emif_revision;
#define OMAP5430_EMIF1_EMIF_STATUS					0x4c000004
extern reg omap5430_emif1_emif_status;
#define OMAP5430_EMIF1_EMIF_SDRAM_CONFIG				0x4c000008
extern reg omap5430_emif1_emif_sdram_config;
#define OMAP5430_EMIF1_EMIF_SDRAM_CONFIG_2				0x4c00000c
extern reg omap5430_emif1_emif_sdram_config_2;
#define OMAP5430_EMIF1_EMIF_SDRAM_REFRESH_CONTROL			0x4c000010
extern reg omap5430_emif1_emif_sdram_refresh_control;
#define OMAP5430_EMIF1_EMIF_SDRAM_REFRESH_CONTROL_SHADOW		0x4c000014
extern reg omap5430_emif1_emif_sdram_refresh_control_shadow;
#define OMAP5430_EMIF1_EMIF_SDRAM_TIMING_1				0x4c000018
extern reg omap5430_emif1_emif_sdram_timing_1;
#define OMAP5430_EMIF1_EMIF_SDRAM_TIMING_1_SHADOW			0x4c00001c
extern reg omap5430_emif1_emif_sdram_timing_1_shadow;
#define OMAP5430_EMIF1_EMIF_SDRAM_TIMING_2				0x4c000020
extern reg omap5430_emif1_emif_sdram_timing_2;
#define OMAP5430_EMIF1_EMIF_SDRAM_TIMING_2_SHADOW			0x4c000024
extern reg omap5430_emif1_emif_sdram_timing_2_shadow;
#define OMAP5430_EMIF1_EMIF_SDRAM_TIMING_3				0x4c000028
extern reg omap5430_emif1_emif_sdram_timing_3;
#define OMAP5430_EMIF1_EMIF_SDRAM_TIMING_3_SHADOW			0x4c00002c
extern reg omap5430_emif1_emif_sdram_timing_3_shadow;
#define OMAP5430_EMIF1_EMIF_POWER_MANAGEMENT_CONTROL			0x4c000038
extern reg omap5430_emif1_emif_power_management_control;
#define OMAP5430_EMIF1_EMIF_POWER_MANAGEMENT_CONTROL_SHADOW		0x4c00003c
extern reg omap5430_emif1_emif_power_management_control_shadow;
#define OMAP5430_EMIF1_EMIF_LPDDR2_MODE_REG_DATA			0x4c000040
extern reg omap5430_emif1_emif_lpddr2_mode_reg_data;
#define OMAP5430_EMIF1_EMIF_LPDDR2_MODE_REG_CONFIG			0x4c000050
extern reg omap5430_emif1_emif_lpddr2_mode_reg_config;
#define OMAP5430_EMIF1_EMIF_OCP_CONFIG					0x4c000054
extern reg omap5430_emif1_emif_ocp_config;
#define OMAP5430_EMIF1_EMIF_OCP_CONFIG_VALUE_1				0x4c000058
extern reg omap5430_emif1_emif_ocp_config_value_1;
#define OMAP5430_EMIF1_EMIF_OCP_CONFIG_VALUE_2				0x4c00005c
extern reg omap5430_emif1_emif_ocp_config_value_2;
#define OMAP5430_EMIF1_EMIF_PERFORMANCE_COUNTER_1			0x4c000080
extern reg omap5430_emif1_emif_performance_counter_1;
#define OMAP5430_EMIF1_EMIF_PERFORMANCE_COUNTER_2			0x4c000084
extern reg omap5430_emif1_emif_performance_counter_2;
#define OMAP5430_EMIF1_EMIF_PERFORMANCE_COUNTER_CONFIG			0x4c000088
extern reg omap5430_emif1_emif_performance_counter_config;
#define OMAP5430_EMIF1_EMIF_PERFORMANCE_COUNTER_MASTER_REGION_SELECT	0x4c00008c
extern reg omap5430_emif1_emif_performance_counter_master_region_select;
#define OMAP5430_EMIF1_EMIF_PERFORMANCE_COUNTER_TIME			0x4c000090
extern reg omap5430_emif1_emif_performance_counter_time;
#define OMAP5430_EMIF1_EMIF_MISC_REG					0x4c000094
extern reg omap5430_emif1_emif_misc_reg;
#define OMAP5430_EMIF1_EMIF_DLL_CALIB_CTRL				0x4c000098
extern reg omap5430_emif1_emif_dll_calib_ctrl;
#define OMAP5430_EMIF1_EMIF_DLL_CALIB_CTRL_SHADOW			0x4c00009c
extern reg omap5430_emif1_emif_dll_calib_ctrl_shadow;
#define OMAP5430_EMIF1_EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS		0x4c0000a4
extern reg omap5430_emif1_emif_system_ocp_interrupt_raw_status;
#define OMAP5430_EMIF1_EMIF_LOW_LATENCY_OCP_INTERRUPT_RAW_STATUS	0x4c0000a8
extern reg omap5430_emif1_emif_low_latency_ocp_interrupt_raw_status;
#define OMAP5430_EMIF1_EMIF_SYSTEM_OCP_INTERRUPT_STATUS			0x4c0000ac
extern reg omap5430_emif1_emif_system_ocp_interrupt_status;
#define OMAP5430_EMIF1_EMIF_LOW_LATENCY_OCP_INTERRUPT_STATUS		0x4c0000b0
extern reg omap5430_emif1_emif_low_latency_ocp_interrupt_status;
#define OMAP5430_EMIF1_EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET		0x4c0000b4
extern reg omap5430_emif1_emif_system_ocp_interrupt_enable_set;
#define OMAP5430_EMIF1_EMIF_LOW_LATENCY_OCP_INTERRUPT_ENABLE_SET	0x4c0000b8
extern reg omap5430_emif1_emif_low_latency_ocp_interrupt_enable_set;
#define OMAP5430_EMIF1_EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR		0x4c0000bc
extern reg omap5430_emif1_emif_system_ocp_interrupt_enable_clear;
#define OMAP5430_EMIF1_EMIF_LOW_LATENCY_OCP_INTERRUPT_ENABLE_CLEAR	0x4c0000c0
extern reg omap5430_emif1_emif_low_latency_ocp_interrupt_enable_clear;
#define OMAP5430_EMIF1_EMIF_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG	0x4c0000c8
extern reg omap5430_emif1_emif_sdram_output_impedance_calibration_config;
#define OMAP5430_EMIF1_EMIF_TEMPERATURE_ALERT_CONFIG			0x4c0000cc
extern reg omap5430_emif1_emif_temperature_alert_config;
#define OMAP5430_EMIF1_EMIF_OCP_ERROR_LOG				0x4c0000d0
extern reg omap5430_emif1_emif_ocp_error_log;
#define OMAP5430_EMIF1_EMIF_READ_WRITE_LEVELING_RAMP_WINDOW		0x4c0000d4
extern reg omap5430_emif1_emif_read_write_leveling_ramp_window;
#define OMAP5430_EMIF1_EMIF_READ_WRITE_LEVELING_RAMP_CONTROL		0x4c0000d8
extern reg omap5430_emif1_emif_read_write_leveling_ramp_control;
#define OMAP5430_EMIF1_EMIF_READ_WRITE_LEVELING_CONTROL			0x4c0000dc
extern reg omap5430_emif1_emif_read_write_leveling_control;
#define OMAP5430_EMIF1_EMIF_DDR_PHY_CONTROL_1				0x4c0000e4
extern reg omap5430_emif1_emif_ddr_phy_control_1;
#define OMAP5430_EMIF1_EMIF_DDR_PHY_CONTROL_1_SHADOW			0x4c0000e8
extern reg omap5430_emif1_emif_ddr_phy_control_1_shadow;
#define OMAP5430_EMIF1_EMIF_READ_WRITE_EXECUTION_THRESHOLD		0x4c000120
extern reg omap5430_emif1_emif_read_write_execution_threshold;
#define OMAP5430_EMIF1_EMIF_PHY_STATUS_1				0x4c000140
extern reg omap5430_emif1_emif_phy_status_1;
#define OMAP5430_EMIF1_EMIF_PHY_STATUS_20				0x4c00018c
extern reg omap5430_emif1_emif_phy_status_20;
#define OMAP5430_EMIF1_EMIF_PHY_STATUS_21				0x4c000190
extern reg omap5430_emif1_emif_phy_status_21;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_1				0x4c000200
extern reg omap5430_emif1_emif_ext_phy_control_1;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_1_SHADOW			0x4c000204
extern reg omap5430_emif1_emif_ext_phy_control_1_shadow;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_2				0x4c000208
extern reg omap5430_emif1_emif_ext_phy_control_2;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_2_SHADOW			0x4c00020c
extern reg omap5430_emif1_emif_ext_phy_control_2_shadow;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_3				0x4c000210
extern reg omap5430_emif1_emif_ext_phy_control_3;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_3_SHADOW			0x4c000214
extern reg omap5430_emif1_emif_ext_phy_control_3_shadow;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_4				0x4c000218
extern reg omap5430_emif1_emif_ext_phy_control_4;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_4_SHADOW			0x4c00021c
extern reg omap5430_emif1_emif_ext_phy_control_4_shadow;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_5				0x4c000220
extern reg omap5430_emif1_emif_ext_phy_control_5;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_5_SHADOW			0x4c000224
extern reg omap5430_emif1_emif_ext_phy_control_5_shadow;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_6				0x4c000228
extern reg omap5430_emif1_emif_ext_phy_control_6;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_6_SHADOW			0x4c00022c
extern reg omap5430_emif1_emif_ext_phy_control_6_shadow;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_7				0x4c000230
extern reg omap5430_emif1_emif_ext_phy_control_7;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_7_SHADOW			0x4c000234
extern reg omap5430_emif1_emif_ext_phy_control_7_shadow;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_8				0x4c000238
extern reg omap5430_emif1_emif_ext_phy_control_8;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_8_SHADOW			0x4c00023c
extern reg omap5430_emif1_emif_ext_phy_control_8_shadow;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_9				0x4c000240
extern reg omap5430_emif1_emif_ext_phy_control_9;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_9_SHADOW			0x4c000244
extern reg omap5430_emif1_emif_ext_phy_control_9_shadow;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_10				0x4c000248
extern reg omap5430_emif1_emif_ext_phy_control_10;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_10_SHADOW			0x4c00024c
extern reg omap5430_emif1_emif_ext_phy_control_10_shadow;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_11				0x4c000250
extern reg omap5430_emif1_emif_ext_phy_control_11;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_11_SHADOW			0x4c000254
extern reg omap5430_emif1_emif_ext_phy_control_11_shadow;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_12				0x4c000258
extern reg omap5430_emif1_emif_ext_phy_control_12;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_12_SHADOW			0x4c00025c
extern reg omap5430_emif1_emif_ext_phy_control_12_shadow;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_13				0x4c000260
extern reg omap5430_emif1_emif_ext_phy_control_13;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_13_SHADOW			0x4c000264
extern reg omap5430_emif1_emif_ext_phy_control_13_shadow;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_14				0x4c000268
extern reg omap5430_emif1_emif_ext_phy_control_14;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_14_SHADOW			0x4c00026c
extern reg omap5430_emif1_emif_ext_phy_control_14_shadow;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_15				0x4c000270
extern reg omap5430_emif1_emif_ext_phy_control_15;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_15_SHADOW			0x4c000274
extern reg omap5430_emif1_emif_ext_phy_control_15_shadow;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_16				0x4c000278
extern reg omap5430_emif1_emif_ext_phy_control_16;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_16_SHADOW			0x4c00027c
extern reg omap5430_emif1_emif_ext_phy_control_16_shadow;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_17				0x4c000280
extern reg omap5430_emif1_emif_ext_phy_control_17;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_17_SHADOW			0x4c000284
extern reg omap5430_emif1_emif_ext_phy_control_17_shadow;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_18				0x4c000288
extern reg omap5430_emif1_emif_ext_phy_control_18;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_18_SHADOW			0x4c00028c
extern reg omap5430_emif1_emif_ext_phy_control_18_shadow;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_19				0x4c000290
extern reg omap5430_emif1_emif_ext_phy_control_19;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_19_SHADOW			0x4c000294
extern reg omap5430_emif1_emif_ext_phy_control_19_shadow;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_20				0x4c000298
extern reg omap5430_emif1_emif_ext_phy_control_20;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_20_SHADOW			0x4c00029c
extern reg omap5430_emif1_emif_ext_phy_control_20_shadow;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_21				0x4c0002a0
extern reg omap5430_emif1_emif_ext_phy_control_21;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_21_SHADOW			0x4c0002a4
extern reg omap5430_emif1_emif_ext_phy_control_21_shadow;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_22				0x4c0002a8
extern reg omap5430_emif1_emif_ext_phy_control_22;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_22_SHADOW			0x4c0002ac
extern reg omap5430_emif1_emif_ext_phy_control_22_shadow;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_23				0x4c0002b0
extern reg omap5430_emif1_emif_ext_phy_control_23;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_23_SHADOW			0x4c0002b4
extern reg omap5430_emif1_emif_ext_phy_control_23_shadow;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_24				0x4c0002b8
extern reg omap5430_emif1_emif_ext_phy_control_24;
#define OMAP5430_EMIF1_EMIF_EXT_PHY_CONTROL_24_SHADOW			0x4c0002bc
extern reg omap5430_emif1_emif_ext_phy_control_24_shadow;
#define OMAP5430_EMIF1_MOD_REGCOUNT					95
extern reg *omap5430_emif1_mod[OMAP5430_EMIF1_MOD_REGCOUNT + 1];

#define OMAP5430_EMIF2_EMIF_REVISION					0x4d000000
extern reg omap5430_emif2_emif_revision;
#define OMAP5430_EMIF2_EMIF_STATUS					0x4d000004
extern reg omap5430_emif2_emif_status;
#define OMAP5430_EMIF2_EMIF_SDRAM_CONFIG				0x4d000008
extern reg omap5430_emif2_emif_sdram_config;
#define OMAP5430_EMIF2_EMIF_SDRAM_CONFIG_2				0x4d00000c
extern reg omap5430_emif2_emif_sdram_config_2;
#define OMAP5430_EMIF2_EMIF_SDRAM_REFRESH_CONTROL			0x4d000010
extern reg omap5430_emif2_emif_sdram_refresh_control;
#define OMAP5430_EMIF2_EMIF_SDRAM_REFRESH_CONTROL_SHADOW		0x4d000014
extern reg omap5430_emif2_emif_sdram_refresh_control_shadow;
#define OMAP5430_EMIF2_EMIF_SDRAM_TIMING_1				0x4d000018
extern reg omap5430_emif2_emif_sdram_timing_1;
#define OMAP5430_EMIF2_EMIF_SDRAM_TIMING_1_SHADOW			0x4d00001c
extern reg omap5430_emif2_emif_sdram_timing_1_shadow;
#define OMAP5430_EMIF2_EMIF_SDRAM_TIMING_2				0x4d000020
extern reg omap5430_emif2_emif_sdram_timing_2;
#define OMAP5430_EMIF2_EMIF_SDRAM_TIMING_2_SHADOW			0x4d000024
extern reg omap5430_emif2_emif_sdram_timing_2_shadow;
#define OMAP5430_EMIF2_EMIF_SDRAM_TIMING_3				0x4d000028
extern reg omap5430_emif2_emif_sdram_timing_3;
#define OMAP5430_EMIF2_EMIF_SDRAM_TIMING_3_SHADOW			0x4d00002c
extern reg omap5430_emif2_emif_sdram_timing_3_shadow;
#define OMAP5430_EMIF2_EMIF_POWER_MANAGEMENT_CONTROL			0x4d000038
extern reg omap5430_emif2_emif_power_management_control;
#define OMAP5430_EMIF2_EMIF_POWER_MANAGEMENT_CONTROL_SHADOW		0x4d00003c
extern reg omap5430_emif2_emif_power_management_control_shadow;
#define OMAP5430_EMIF2_EMIF_LPDDR2_MODE_REG_DATA			0x4d000040
extern reg omap5430_emif2_emif_lpddr2_mode_reg_data;
#define OMAP5430_EMIF2_EMIF_LPDDR2_MODE_REG_CONFIG			0x4d000050
extern reg omap5430_emif2_emif_lpddr2_mode_reg_config;
#define OMAP5430_EMIF2_EMIF_OCP_CONFIG					0x4d000054
extern reg omap5430_emif2_emif_ocp_config;
#define OMAP5430_EMIF2_EMIF_OCP_CONFIG_VALUE_1				0x4d000058
extern reg omap5430_emif2_emif_ocp_config_value_1;
#define OMAP5430_EMIF2_EMIF_OCP_CONFIG_VALUE_2				0x4d00005c
extern reg omap5430_emif2_emif_ocp_config_value_2;
#define OMAP5430_EMIF2_EMIF_PERFORMANCE_COUNTER_1			0x4d000080
extern reg omap5430_emif2_emif_performance_counter_1;
#define OMAP5430_EMIF2_EMIF_PERFORMANCE_COUNTER_2			0x4d000084
extern reg omap5430_emif2_emif_performance_counter_2;
#define OMAP5430_EMIF2_EMIF_PERFORMANCE_COUNTER_CONFIG			0x4d000088
extern reg omap5430_emif2_emif_performance_counter_config;
#define OMAP5430_EMIF2_EMIF_PERFORMANCE_COUNTER_MASTER_REGION_SELECT	0x4d00008c
extern reg omap5430_emif2_emif_performance_counter_master_region_select;
#define OMAP5430_EMIF2_EMIF_PERFORMANCE_COUNTER_TIME			0x4d000090
extern reg omap5430_emif2_emif_performance_counter_time;
#define OMAP5430_EMIF2_EMIF_MISC_REG					0x4d000094
extern reg omap5430_emif2_emif_misc_reg;
#define OMAP5430_EMIF2_EMIF_DLL_CALIB_CTRL				0x4d000098
extern reg omap5430_emif2_emif_dll_calib_ctrl;
#define OMAP5430_EMIF2_EMIF_DLL_CALIB_CTRL_SHADOW			0x4d00009c
extern reg omap5430_emif2_emif_dll_calib_ctrl_shadow;
#define OMAP5430_EMIF2_EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS		0x4d0000a4
extern reg omap5430_emif2_emif_system_ocp_interrupt_raw_status;
#define OMAP5430_EMIF2_EMIF_LOW_LATENCY_OCP_INTERRUPT_RAW_STATUS	0x4d0000a8
extern reg omap5430_emif2_emif_low_latency_ocp_interrupt_raw_status;
#define OMAP5430_EMIF2_EMIF_SYSTEM_OCP_INTERRUPT_STATUS			0x4d0000ac
extern reg omap5430_emif2_emif_system_ocp_interrupt_status;
#define OMAP5430_EMIF2_EMIF_LOW_LATENCY_OCP_INTERRUPT_STATUS		0x4d0000b0
extern reg omap5430_emif2_emif_low_latency_ocp_interrupt_status;
#define OMAP5430_EMIF2_EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET		0x4d0000b4
extern reg omap5430_emif2_emif_system_ocp_interrupt_enable_set;
#define OMAP5430_EMIF2_EMIF_LOW_LATENCY_OCP_INTERRUPT_ENABLE_SET	0x4d0000b8
extern reg omap5430_emif2_emif_low_latency_ocp_interrupt_enable_set;
#define OMAP5430_EMIF2_EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR		0x4d0000bc
extern reg omap5430_emif2_emif_system_ocp_interrupt_enable_clear;
#define OMAP5430_EMIF2_EMIF_LOW_LATENCY_OCP_INTERRUPT_ENABLE_CLEAR	0x4d0000c0
extern reg omap5430_emif2_emif_low_latency_ocp_interrupt_enable_clear;
#define OMAP5430_EMIF2_EMIF_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG	0x4d0000c8
extern reg omap5430_emif2_emif_sdram_output_impedance_calibration_config;
#define OMAP5430_EMIF2_EMIF_TEMPERATURE_ALERT_CONFIG			0x4d0000cc
extern reg omap5430_emif2_emif_temperature_alert_config;
#define OMAP5430_EMIF2_EMIF_OCP_ERROR_LOG				0x4d0000d0
extern reg omap5430_emif2_emif_ocp_error_log;
#define OMAP5430_EMIF2_EMIF_READ_WRITE_LEVELING_RAMP_WINDOW		0x4d0000d4
extern reg omap5430_emif2_emif_read_write_leveling_ramp_window;
#define OMAP5430_EMIF2_EMIF_READ_WRITE_LEVELING_RAMP_CONTROL		0x4d0000d8
extern reg omap5430_emif2_emif_read_write_leveling_ramp_control;
#define OMAP5430_EMIF2_EMIF_READ_WRITE_LEVELING_CONTROL			0x4d0000dc
extern reg omap5430_emif2_emif_read_write_leveling_control;
#define OMAP5430_EMIF2_EMIF_DDR_PHY_CONTROL_1				0x4d0000e4
extern reg omap5430_emif2_emif_ddr_phy_control_1;
#define OMAP5430_EMIF2_EMIF_DDR_PHY_CONTROL_1_SHADOW			0x4d0000e8
extern reg omap5430_emif2_emif_ddr_phy_control_1_shadow;
#define OMAP5430_EMIF2_EMIF_READ_WRITE_EXECUTION_THRESHOLD		0x4d000120
extern reg omap5430_emif2_emif_read_write_execution_threshold;
#define OMAP5430_EMIF2_EMIF_PHY_STATUS_1				0x4d000140
extern reg omap5430_emif2_emif_phy_status_1;
#define OMAP5430_EMIF2_EMIF_PHY_STATUS_20				0x4d00018c
extern reg omap5430_emif2_emif_phy_status_20;
#define OMAP5430_EMIF2_EMIF_PHY_STATUS_21				0x4d000190
extern reg omap5430_emif2_emif_phy_status_21;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_1				0x4d000200
extern reg omap5430_emif2_emif_ext_phy_control_1;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_1_SHADOW			0x4d000204
extern reg omap5430_emif2_emif_ext_phy_control_1_shadow;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_2				0x4d000208
extern reg omap5430_emif2_emif_ext_phy_control_2;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_2_SHADOW			0x4d00020c
extern reg omap5430_emif2_emif_ext_phy_control_2_shadow;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_3				0x4d000210
extern reg omap5430_emif2_emif_ext_phy_control_3;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_3_SHADOW			0x4d000214
extern reg omap5430_emif2_emif_ext_phy_control_3_shadow;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_4				0x4d000218
extern reg omap5430_emif2_emif_ext_phy_control_4;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_4_SHADOW			0x4d00021c
extern reg omap5430_emif2_emif_ext_phy_control_4_shadow;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_5				0x4d000220
extern reg omap5430_emif2_emif_ext_phy_control_5;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_5_SHADOW			0x4d000224
extern reg omap5430_emif2_emif_ext_phy_control_5_shadow;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_6				0x4d000228
extern reg omap5430_emif2_emif_ext_phy_control_6;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_6_SHADOW			0x4d00022c
extern reg omap5430_emif2_emif_ext_phy_control_6_shadow;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_7				0x4d000230
extern reg omap5430_emif2_emif_ext_phy_control_7;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_7_SHADOW			0x4d000234
extern reg omap5430_emif2_emif_ext_phy_control_7_shadow;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_8				0x4d000238
extern reg omap5430_emif2_emif_ext_phy_control_8;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_8_SHADOW			0x4d00023c
extern reg omap5430_emif2_emif_ext_phy_control_8_shadow;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_9				0x4d000240
extern reg omap5430_emif2_emif_ext_phy_control_9;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_9_SHADOW			0x4d000244
extern reg omap5430_emif2_emif_ext_phy_control_9_shadow;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_10				0x4d000248
extern reg omap5430_emif2_emif_ext_phy_control_10;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_10_SHADOW			0x4d00024c
extern reg omap5430_emif2_emif_ext_phy_control_10_shadow;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_11				0x4d000250
extern reg omap5430_emif2_emif_ext_phy_control_11;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_11_SHADOW			0x4d000254
extern reg omap5430_emif2_emif_ext_phy_control_11_shadow;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_12				0x4d000258
extern reg omap5430_emif2_emif_ext_phy_control_12;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_12_SHADOW			0x4d00025c
extern reg omap5430_emif2_emif_ext_phy_control_12_shadow;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_13				0x4d000260
extern reg omap5430_emif2_emif_ext_phy_control_13;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_13_SHADOW			0x4d000264
extern reg omap5430_emif2_emif_ext_phy_control_13_shadow;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_14				0x4d000268
extern reg omap5430_emif2_emif_ext_phy_control_14;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_14_SHADOW			0x4d00026c
extern reg omap5430_emif2_emif_ext_phy_control_14_shadow;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_15				0x4d000270
extern reg omap5430_emif2_emif_ext_phy_control_15;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_15_SHADOW			0x4d000274
extern reg omap5430_emif2_emif_ext_phy_control_15_shadow;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_16				0x4d000278
extern reg omap5430_emif2_emif_ext_phy_control_16;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_16_SHADOW			0x4d00027c
extern reg omap5430_emif2_emif_ext_phy_control_16_shadow;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_17				0x4d000280
extern reg omap5430_emif2_emif_ext_phy_control_17;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_17_SHADOW			0x4d000284
extern reg omap5430_emif2_emif_ext_phy_control_17_shadow;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_18				0x4d000288
extern reg omap5430_emif2_emif_ext_phy_control_18;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_18_SHADOW			0x4d00028c
extern reg omap5430_emif2_emif_ext_phy_control_18_shadow;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_19				0x4d000290
extern reg omap5430_emif2_emif_ext_phy_control_19;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_19_SHADOW			0x4d000294
extern reg omap5430_emif2_emif_ext_phy_control_19_shadow;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_20				0x4d000298
extern reg omap5430_emif2_emif_ext_phy_control_20;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_20_SHADOW			0x4d00029c
extern reg omap5430_emif2_emif_ext_phy_control_20_shadow;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_21				0x4d0002a0
extern reg omap5430_emif2_emif_ext_phy_control_21;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_21_SHADOW			0x4d0002a4
extern reg omap5430_emif2_emif_ext_phy_control_21_shadow;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_22				0x4d0002a8
extern reg omap5430_emif2_emif_ext_phy_control_22;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_22_SHADOW			0x4d0002ac
extern reg omap5430_emif2_emif_ext_phy_control_22_shadow;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_23				0x4d0002b0
extern reg omap5430_emif2_emif_ext_phy_control_23;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_23_SHADOW			0x4d0002b4
extern reg omap5430_emif2_emif_ext_phy_control_23_shadow;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_24				0x4d0002b8
extern reg omap5430_emif2_emif_ext_phy_control_24;
#define OMAP5430_EMIF2_EMIF_EXT_PHY_CONTROL_24_SHADOW			0x4d0002bc
extern reg omap5430_emif2_emif_ext_phy_control_24_shadow;
#define OMAP5430_EMIF2_MOD_REGCOUNT					95
extern reg *omap5430_emif2_mod[OMAP5430_EMIF2_MOD_REGCOUNT + 1];


typedef enum {
	EMIF54XX_EMIF1,
	EMIF54XX_EMIF2,
	EMIF54XX_MODS_COUNT = 2
} emif54xx_mod_id;


extern reg **emif54xx_mods[EMIF54XX_MODS_COUNT];


#endif
