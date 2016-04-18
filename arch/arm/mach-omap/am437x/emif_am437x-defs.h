/*
 *
 * @Component			OMAPCONF
 * @Filename			emif_am437x-defs.h
 * @Description			AM437X EMIF Register Address Definitions
 * @Author			Dave Gerlach <d-gerlach@ti.com>
 * @Date			2016
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef __EMIF_AM437X_DEFS_H__
#define __EMIF_AM437X_DEFS_H__

#include <reg.h>
#include <stdio.h>

#define AM437X_EMIF4D_MOD_ID_REV				0x4c000000
extern reg am437x_emif4d_mod_id_rev;
#define AM437X_EMIF4D_STS					0x4c000004
extern reg am437x_emif4d_sts;
#define AM437X_EMIF4D_SDRAM_CONFIG				0x4c000008
extern reg am437x_emif4d_sdram_config;
#define AM437X_EMIF4D_SDRAM_CONFIG_2				0x4c00000c
extern reg am437x_emif4d_sdram_config_2;
#define AM437X_EMIF4D_SDRAM_REFRESH_CTRL			0x4c000010
extern reg am437x_emif4d_sdram_refresh_ctrl;
#define AM437X_EMIF4D_SDRAM_REFRESH_CTRL_SHADOW			0x4c000014
extern reg am437x_emif4d_sdram_refresh_ctrl_shadow;
#define AM437X_EMIF4D_SDRAM_TIMING_1				0x4c000018
extern reg am437x_emif4d_sdram_timing_1;
#define AM437X_EMIF4D_SDRAM_TIMING_1_SHADOW			0x4c00001c
extern reg am437x_emif4d_sdram_timing_1_shadow;
#define AM437X_EMIF4D_SDRAM_TIMING_2				0x4c000020
extern reg am437x_emif4d_sdram_timing_2;
#define AM437X_EMIF4D_SDRAM_TIMING_2_SHADOW			0x4c000024
extern reg am437x_emif4d_sdram_timing_2_shadow;
#define AM437X_EMIF4D_SDRAM_TIMING_3				0x4c000028
extern reg am437x_emif4d_sdram_timing_3;
#define AM437X_EMIF4D_SDRAM_TIMING_3_SHADOW			0x4c00002c
extern reg am437x_emif4d_sdram_timing_3_shadow;
#define AM437X_EMIF4D_LPDDR2_NVM_TIMING				0x4c000030
extern reg am437x_emif4d_lpddr2_nvm_timing;
#define AM437X_EMIF4D_LPDDR2_NVM_TIMING_SHADOW			0x4c000034
extern reg am437x_emif4d_lpddr2_nvm_timing_shadow;
#define AM437X_EMIF4D_POWER_MANAGEMENT_CTRL			0x4c000038
extern reg am437x_emif4d_power_management_ctrl;
#define AM437X_EMIF4D_POWER_MANAGEMENT_CTRL_SHADOW		0x4c00003c
extern reg am437x_emif4d_power_management_ctrl_shadow;
#define AM437X_EMIF4D_LPDDR2_MODE_REG_DATA			0x4c000040
extern reg am437x_emif4d_lpddr2_mode_reg_data;
#define AM437X_EMIF4D_LPDDR2_MODE_REG_CONFIG			0x4c000050
extern reg am437x_emif4d_lpddr2_mode_reg_config;
#define AM437X_EMIF4D_OCP_CONFIG				0x4c000054
extern reg am437x_emif4d_ocp_config;
#define AM437X_EMIF4D_OCP_CONFIG_VALUE_1			0x4c000058
extern reg am437x_emif4d_ocp_config_value_1;
#define AM437X_EMIF4D_OCP_CONFIG_VALUE_2			0x4c00005c
extern reg am437x_emif4d_ocp_config_value_2;
#define AM437X_EMIF4D_IODFT_TEST_LOGIC_GLOBAL_CTRL		0x4c000060
extern reg am437x_emif4d_iodft_test_logic_global_ctrl;
#define AM437X_EMIF4D_IODFT_TEST_LOGIC_CTRL_MISR_RESULT		0x4c000064
extern reg am437x_emif4d_iodft_test_logic_ctrl_misr_result;
#define AM437X_EMIF4D_IODFT_TEST_LOGIC_ADDR_MISR_RESULT		0x4c000068
extern reg am437x_emif4d_iodft_test_logic_addr_misr_result;
#define AM437X_EMIF4D_IODFT_TEST_LOGIC_DATA_MISR_RESULT_1	0x4c00006c
extern reg am437x_emif4d_iodft_test_logic_data_misr_result_1;
#define AM437X_EMIF4D_IODFT_TEST_LOGIC_DATA_MISR_RESULT_2	0x4c000070
extern reg am437x_emif4d_iodft_test_logic_data_misr_result_2;
#define AM437X_EMIF4D_IODFT_TEST_LOGIC_DATA_MISR_RESULT_3	0x4c000074
extern reg am437x_emif4d_iodft_test_logic_data_misr_result_3;
#define AM437X_EMIF4D_PERFORMANCE_CTR_1				0x4c000080
extern reg am437x_emif4d_performance_ctr_1;
#define AM437X_EMIF4D_PERFORMANCE_CTR_2				0x4c000084
extern reg am437x_emif4d_performance_ctr_2;
#define AM437X_EMIF4D_PERFORMANCE_CTR_CONFIG			0x4c000088
extern reg am437x_emif4d_performance_ctr_config;
#define AM437X_EMIF4D_PERFORMANCE_CTR_MASTER_REGION_SELECT	0x4c00008c
extern reg am437x_emif4d_performance_ctr_master_region_select;
#define AM437X_EMIF4D_PERFORMANCE_CTR_TIME			0x4c000090
extern reg am437x_emif4d_performance_ctr_time;
#define AM437X_EMIF4D_MISC_REG					0x4c000094
extern reg am437x_emif4d_misc_reg;
#define AM437X_EMIF4D_DLL_CALIB_CTRL				0x4c000098
extern reg am437x_emif4d_dll_calib_ctrl;
#define AM437X_EMIF4D_DLL_CALIB_CTRL_SHADOW			0x4c00009c
extern reg am437x_emif4d_dll_calib_ctrl_shadow;
#define AM437X_EMIF4D_END_OF_INTR				0x4c0000a0
extern reg am437x_emif4d_end_of_intr;
#define AM437X_EMIF4D_SYSTEM_OCP_INTR_RAW_STS			0x4c0000a4
extern reg am437x_emif4d_system_ocp_intr_raw_sts;
#define AM437X_EMIF4D_LOW_LAT_OCP_INTR_RAW_STS			0x4c0000a8
extern reg am437x_emif4d_low_lat_ocp_intr_raw_sts;
#define AM437X_EMIF4D_SYSTEM_OCP_INTR_STS			0x4c0000ac
extern reg am437x_emif4d_system_ocp_intr_sts;
#define AM437X_EMIF4D_LOW_LAT_OCP_INTR_STS			0x4c0000b0
extern reg am437x_emif4d_low_lat_ocp_intr_sts;
#define AM437X_EMIF4D_SYSTEM_OCP_INTR_EN_SET			0x4c0000b4
extern reg am437x_emif4d_system_ocp_intr_en_set;
#define AM437X_EMIF4D_LOW_LAT_OCP_INTR_EN_SET			0x4c0000b8
extern reg am437x_emif4d_low_lat_ocp_intr_en_set;
#define AM437X_EMIF4D_SYSTEM_OCP_INTR_EN_CLR			0x4c0000bc
extern reg am437x_emif4d_system_ocp_intr_en_clr;
#define AM437X_EMIF4D_LOW_LAT_OCP_INTR_EN_CLR			0x4c0000c0
extern reg am437x_emif4d_low_lat_ocp_intr_en_clr;
#define AM437X_EMIF4D_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG	0x4c0000c8
extern reg am437x_emif4d_sdram_output_impedance_calibration_config;
#define AM437X_EMIF4D_TEMPERATURE_ALERT_CONFIG			0x4c0000cc
extern reg am437x_emif4d_temperature_alert_config;
#define AM437X_EMIF4D_OCP_ERROR_LOG				0x4c0000d0
extern reg am437x_emif4d_ocp_error_log;
#define AM437X_EMIF4D_READ_WRITE_LEVELING_RAMP_WINDOW		0x4c0000d4
extern reg am437x_emif4d_read_write_leveling_ramp_window;
#define AM437X_EMIF4D_READ_WRITE_LEVELING_RAMP_CTRL		0x4c0000d8
extern reg am437x_emif4d_read_write_leveling_ramp_ctrl;
#define AM437X_EMIF4D_READ_WRITE_LEVELING_CTRL			0x4c0000dc
extern reg am437x_emif4d_read_write_leveling_ctrl;
#define AM437X_EMIF4D_DDR_PHY_CTRL_1				0x4c0000e4
extern reg am437x_emif4d_ddr_phy_ctrl_1;
#define AM437X_EMIF4D_DDR_PHY_CTRL_1_SHADOW			0x4c0000e8
extern reg am437x_emif4d_ddr_phy_ctrl_1_shadow;
#define AM437X_EMIF4D_PRIORITY_TO_CLASS_OF_SERVICE_MAPPING	0x4c000100
extern reg am437x_emif4d_priority_to_class_of_service_mapping;
#define AM437X_EMIF4D_CONN_ID_TO_CLASS_OF_SERVICE_1_MAPPING	0x4c000104
extern reg am437x_emif4d_conn_id_to_class_of_service_1_mapping;
#define AM437X_EMIF4D_CONN_ID_TO_CLASS_OF_SERVICE_2_MAPPING	0x4c000108
extern reg am437x_emif4d_conn_id_to_class_of_service_2_mapping;
#define AM437X_EMIF4D_ECC_CTRL_REG				0x4c000110
extern reg am437x_emif4d_ecc_ctrl_reg;
#define AM437X_EMIF4D_ECC_ADDR_RANGE_1				0x4c000114
extern reg am437x_emif4d_ecc_addr_range_1;
#define AM437X_EMIF4D_ECC_ADDR_RANGE_2				0x4c000118
extern reg am437x_emif4d_ecc_addr_range_2;
#define AM437X_EMIF4D_READ_WRITE_EXECUTION_THR			0x4c000120
extern reg am437x_emif4d_read_write_execution_thr;
#define AM437X_EMIF4D_COS_CONFIG				0x4c000124
extern reg am437x_emif4d_cos_config;
#define AM437X_EMIF4D_1B_ECC_ERR_CNT				0x4c000130
extern reg am437x_emif4d_1b_ecc_err_cnt;
#define AM437X_EMIF4D_1B_ECC_ERR_THRSH				0x4c000134
extern reg am437x_emif4d_1b_ecc_err_thrsh;
#define AM437X_EMIF4D_1B_ECC_ERR_DIST_1				0x4c000138
extern reg am437x_emif4d_1b_ecc_err_dist_1;
#define AM437X_EMIF4D_1B_ECC_ERR_ADDR_LOG			0x4c00013c
extern reg am437x_emif4d_1b_ecc_err_addr_log;
#define AM437X_EMIF4D_2B_ECC_ERR_ADDR_LOG			0x4c000140
extern reg am437x_emif4d_2b_ecc_err_addr_log;
#define AM437X_EMIF4D_PHY_STS_1					0x4c000144
extern reg am437x_emif4d_phy_sts_1;
#define AM437X_EMIF4D_PHY_STS_2					0x4c000148
extern reg am437x_emif4d_phy_sts_2;
#define AM437X_EMIF4D_PHY_STS_3					0x4c00014c
extern reg am437x_emif4d_phy_sts_3;
#define AM437X_EMIF4D_PHY_STS_4					0x4c000150
extern reg am437x_emif4d_phy_sts_4;
#define AM437X_EMIF4D_PHY_STS_5					0x4c000154
extern reg am437x_emif4d_phy_sts_5;
#define AM437X_EMIF4D_PHY_STS_6					0x4c000158
extern reg am437x_emif4d_phy_sts_6;
#define AM437X_EMIF4D_PHY_STS_7					0x4c00015c
extern reg am437x_emif4d_phy_sts_7;
#define AM437X_EMIF4D_PHY_STS_8					0x4c000160
extern reg am437x_emif4d_phy_sts_8;
#define AM437X_EMIF4D_PHY_STS_9					0x4c000164
extern reg am437x_emif4d_phy_sts_9;
#define AM437X_EMIF4D_PHY_STS_10				0x4c000168
extern reg am437x_emif4d_phy_sts_10;
#define AM437X_EMIF4D_PHY_STS_11				0x4c00016c
extern reg am437x_emif4d_phy_sts_11;
#define AM437X_EMIF4D_PHY_STS_12				0x4c000170
extern reg am437x_emif4d_phy_sts_12;
#define AM437X_EMIF4D_PHY_STS_13				0x4c000174
extern reg am437x_emif4d_phy_sts_13;
#define AM437X_EMIF4D_PHY_STS_14				0x4c000178
extern reg am437x_emif4d_phy_sts_14;
#define AM437X_EMIF4D_PHY_STS_15				0x4c00017c
extern reg am437x_emif4d_phy_sts_15;
#define AM437X_EMIF4D_PHY_STS_16				0x4c000180
extern reg am437x_emif4d_phy_sts_16;
#define AM437X_EMIF4D_PHY_STS_17				0x4c000184
extern reg am437x_emif4d_phy_sts_17;
#define AM437X_EMIF4D_PHY_STS_18				0x4c000188
extern reg am437x_emif4d_phy_sts_18;
#define AM437X_EMIF4D_PHY_STS_19				0x4c00018c
extern reg am437x_emif4d_phy_sts_19;
#define AM437X_EMIF4D_PHY_STS_20				0x4c000190
extern reg am437x_emif4d_phy_sts_20;
#define AM437X_EMIF4D_PHY_STS_21				0x4c000194
extern reg am437x_emif4d_phy_sts_21;
#define AM437X_EMIF4D_PHY_STS_22				0x4c000198
extern reg am437x_emif4d_phy_sts_22;
#define AM437X_EMIF4D_PHY_STS_23				0x4c00019c
extern reg am437x_emif4d_phy_sts_23;
#define AM437X_EMIF4D_PHY_STS_24				0x4c0001a0
extern reg am437x_emif4d_phy_sts_24;
#define AM437X_EMIF4D_PHY_STS_25				0x4c0001a4
extern reg am437x_emif4d_phy_sts_25;
#define AM437X_EMIF4D_PHY_STS_26				0x4c0001a8
extern reg am437x_emif4d_phy_sts_26;
#define AM437X_EMIF4D_PHY_STS_27				0x4c0001ac
extern reg am437x_emif4d_phy_sts_27;
#define AM437X_EMIF4D_PHY_STS_28				0x4c0001b0
extern reg am437x_emif4d_phy_sts_28;
#define AM437X_EMIF4D_EXT_PHY_CTRL_1				0x4c000200
extern reg am437x_emif4d_ext_phy_ctrl_1;
#define AM437X_EMIF4D_EXT_PHY_CTRL_1_SHADOW			0x4c000204
extern reg am437x_emif4d_ext_phy_ctrl_1_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_2				0x4c000208
extern reg am437x_emif4d_ext_phy_ctrl_2;
#define AM437X_EMIF4D_EXT_PHY_CTRL_2_SHADOW			0x4c00020c
extern reg am437x_emif4d_ext_phy_ctrl_2_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_3				0x4c000210
extern reg am437x_emif4d_ext_phy_ctrl_3;
#define AM437X_EMIF4D_EXT_PHY_CTRL_3_SHADOW			0x4c000214
extern reg am437x_emif4d_ext_phy_ctrl_3_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_4				0x4c000218
extern reg am437x_emif4d_ext_phy_ctrl_4;
#define AM437X_EMIF4D_EXT_PHY_CTRL_4_SHADOW			0x4c00021c
extern reg am437x_emif4d_ext_phy_ctrl_4_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_5				0x4c000220
extern reg am437x_emif4d_ext_phy_ctrl_5;
#define AM437X_EMIF4D_EXT_PHY_CTRL_5_SHADOW			0x4c000224
extern reg am437x_emif4d_ext_phy_ctrl_5_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_6				0x4c000228
extern reg am437x_emif4d_ext_phy_ctrl_6;
#define AM437X_EMIF4D_EXT_PHY_CTRL_6_SHADOW			0x4c00022c
extern reg am437x_emif4d_ext_phy_ctrl_6_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_7				0x4c000230
extern reg am437x_emif4d_ext_phy_ctrl_7;
#define AM437X_EMIF4D_EXT_PHY_CTRL_7_SHADOW			0x4c000234
extern reg am437x_emif4d_ext_phy_ctrl_7_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_8				0x4c000238
extern reg am437x_emif4d_ext_phy_ctrl_8;
#define AM437X_EMIF4D_EXT_PHY_CTRL_8_SHADOW			0x4c00023c
extern reg am437x_emif4d_ext_phy_ctrl_8_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_9				0x4c000240
extern reg am437x_emif4d_ext_phy_ctrl_9;
#define AM437X_EMIF4D_EXT_PHY_CTRL_9_SHADOW			0x4c000244
extern reg am437x_emif4d_ext_phy_ctrl_9_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_10				0x4c000248
extern reg am437x_emif4d_ext_phy_ctrl_10;
#define AM437X_EMIF4D_EXT_PHY_CTRL_10_SHADOW			0x4c00024c
extern reg am437x_emif4d_ext_phy_ctrl_10_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_11				0x4c000250
extern reg am437x_emif4d_ext_phy_ctrl_11;
#define AM437X_EMIF4D_EXT_PHY_CTRL_11_SHADOW			0x4c000254
extern reg am437x_emif4d_ext_phy_ctrl_11_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_12				0x4c000258
extern reg am437x_emif4d_ext_phy_ctrl_12;
#define AM437X_EMIF4D_EXT_PHY_CTRL_12_SHADOW			0x4c00025c
extern reg am437x_emif4d_ext_phy_ctrl_12_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_13				0x4c000260
extern reg am437x_emif4d_ext_phy_ctrl_13;
#define AM437X_EMIF4D_EXT_PHY_CTRL_13_SHADOW			0x4c000264
extern reg am437x_emif4d_ext_phy_ctrl_13_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_14				0x4c000268
extern reg am437x_emif4d_ext_phy_ctrl_14;
#define AM437X_EMIF4D_EXT_PHY_CTRL_14_SHADOW			0x4c00026c
extern reg am437x_emif4d_ext_phy_ctrl_14_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_15				0x4c000270
extern reg am437x_emif4d_ext_phy_ctrl_15;
#define AM437X_EMIF4D_EXT_PHY_CTRL_15_SHADOW			0x4c000274
extern reg am437x_emif4d_ext_phy_ctrl_15_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_16				0x4c000278
extern reg am437x_emif4d_ext_phy_ctrl_16;
#define AM437X_EMIF4D_EXT_PHY_CTRL_16_SHADOW			0x4c00027c
extern reg am437x_emif4d_ext_phy_ctrl_16_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_17				0x4c000280
extern reg am437x_emif4d_ext_phy_ctrl_17;
#define AM437X_EMIF4D_EXT_PHY_CTRL_17_SHADOW			0x4c000284
extern reg am437x_emif4d_ext_phy_ctrl_17_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_18				0x4c000288
extern reg am437x_emif4d_ext_phy_ctrl_18;
#define AM437X_EMIF4D_EXT_PHY_CTRL_18_SHADOW			0x4c00028c
extern reg am437x_emif4d_ext_phy_ctrl_18_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_19				0x4c000290
extern reg am437x_emif4d_ext_phy_ctrl_19;
#define AM437X_EMIF4D_EXT_PHY_CTRL_19_SHADOW			0x4c000294
extern reg am437x_emif4d_ext_phy_ctrl_19_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_20				0x4c000298
extern reg am437x_emif4d_ext_phy_ctrl_20;
#define AM437X_EMIF4D_EXT_PHY_CTRL_20_SHADOW			0x4c00029c
extern reg am437x_emif4d_ext_phy_ctrl_20_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_21				0x4c0002a0
extern reg am437x_emif4d_ext_phy_ctrl_21;
#define AM437X_EMIF4D_EXT_PHY_CTRL_21_SHADOW			0x4c0002a4
extern reg am437x_emif4d_ext_phy_ctrl_21_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_22				0x4c0002a8
extern reg am437x_emif4d_ext_phy_ctrl_22;
#define AM437X_EMIF4D_EXT_PHY_CTRL_22_SHADOW			0x4c0002ac
extern reg am437x_emif4d_ext_phy_ctrl_22_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_23				0x4c0002b0
extern reg am437x_emif4d_ext_phy_ctrl_23;
#define AM437X_EMIF4D_EXT_PHY_CTRL_23_SHADOW			0x4c0002b4
extern reg am437x_emif4d_ext_phy_ctrl_23_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_24				0x4c0002b8
extern reg am437x_emif4d_ext_phy_ctrl_24;
#define AM437X_EMIF4D_EXT_PHY_CTRL_24_SHADOW			0x4c0002bc
extern reg am437x_emif4d_ext_phy_ctrl_24_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_25				0x4c0002c0
extern reg am437x_emif4d_ext_phy_ctrl_25;
#define AM437X_EMIF4D_EXT_PHY_CTRL_25_SHADOW			0x4c0002c4
extern reg am437x_emif4d_ext_phy_ctrl_25_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_26				0x4c0002c8
extern reg am437x_emif4d_ext_phy_ctrl_26;
#define AM437X_EMIF4D_EXT_PHY_CTRL_26_SHADOW			0x4c0002cc
extern reg am437x_emif4d_ext_phy_ctrl_26_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_27				0x4c0002d0
extern reg am437x_emif4d_ext_phy_ctrl_27;
#define AM437X_EMIF4D_EXT_PHY_CTRL_27_SHADOW			0x4c0002d4
extern reg am437x_emif4d_ext_phy_ctrl_27_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_28				0x4c0002d8
extern reg am437x_emif4d_ext_phy_ctrl_28;
#define AM437X_EMIF4D_EXT_PHY_CTRL_28_SHADOW			0x4c0002dc
extern reg am437x_emif4d_ext_phy_ctrl_28_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_29				0x4c0002e0
extern reg am437x_emif4d_ext_phy_ctrl_29;
#define AM437X_EMIF4D_EXT_PHY_CTRL_29_SHADOW			0x4c0002e4
extern reg am437x_emif4d_ext_phy_ctrl_29_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_30				0x4c0002e8
extern reg am437x_emif4d_ext_phy_ctrl_30;
#define AM437X_EMIF4D_EXT_PHY_CTRL_30_SHADOW			0x4c0002ec
extern reg am437x_emif4d_ext_phy_ctrl_30_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_31				0x4c0002f0
extern reg am437x_emif4d_ext_phy_ctrl_31;
#define AM437X_EMIF4D_EXT_PHY_CTRL_31_SHADOW			0x4c0002f4
extern reg am437x_emif4d_ext_phy_ctrl_31_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_32				0x4c0002f8
extern reg am437x_emif4d_ext_phy_ctrl_32;
#define AM437X_EMIF4D_EXT_PHY_CTRL_32_SHADOW			0x4c0002fc
extern reg am437x_emif4d_ext_phy_ctrl_32_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_33				0x4c000300
extern reg am437x_emif4d_ext_phy_ctrl_33;
#define AM437X_EMIF4D_EXT_PHY_CTRL_33_SHADOW			0x4c000304
extern reg am437x_emif4d_ext_phy_ctrl_33_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_34				0x4c000308
extern reg am437x_emif4d_ext_phy_ctrl_34;
#define AM437X_EMIF4D_EXT_PHY_CTRL_34_SHADOW			0x4c00030c
extern reg am437x_emif4d_ext_phy_ctrl_34_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_35				0x4c000310
extern reg am437x_emif4d_ext_phy_ctrl_35;
#define AM437X_EMIF4D_EXT_PHY_CTRL_35_SHADOW			0x4c000314
extern reg am437x_emif4d_ext_phy_ctrl_35_shadow;
#define AM437X_EMIF4D_EXT_PHY_CTRL_36				0x4c000318
extern reg am437x_emif4d_ext_phy_ctrl_36;
#define AM437X_EMIF4D_EXT_PHY_CTRL_36_SHADOW			0x4c00031c
extern reg am437x_emif4d_ext_phy_ctrl_36_shadow;
#define AM437X_EMIF4D_MOD_REGCOUNT				165
extern reg *am437x_emif4d_mod[AM437X_EMIF4D_MOD_REGCOUNT + 1];

typedef enum {
	EMIF_AM437X_EMIF4D,
	EMIF_AM437X_MODS_COUNT = 1
} emif_am437x_mod_id;

extern reg **emif_am437x_mods[EMIF_AM437X_MODS_COUNT];

extern const char *emif_am437x_mods_name[EMIF_AM437X_MODS_COUNT];

#endif
