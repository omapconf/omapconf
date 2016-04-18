/*
 *
 * @Component			OMAPCONF
 * @Filename			emif_am437x.c
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

#include <emif_am437x-defs.h>

reg am437x_emif4d_mod_id_rev = {
	"EMIF4D_MOD_ID_REV",
	AM437X_EMIF4D_MOD_ID_REV,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_sts = {
	"EMIF4D_STS",
	AM437X_EMIF4D_STS,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_sdram_config = {
	"EMIF4D_SDRAM_CONFIG",
	AM437X_EMIF4D_SDRAM_CONFIG,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_sdram_config_2 = {
	"EMIF4D_SDRAM_CONFIG_2",
	AM437X_EMIF4D_SDRAM_CONFIG_2,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_sdram_refresh_ctrl = {
	"EMIF4D_SDRAM_REFRESH_CTRL",
	AM437X_EMIF4D_SDRAM_REFRESH_CTRL,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_sdram_refresh_ctrl_shadow = {
	"EMIF4D_SDRAM_REFRESH_CTRL_SHADOW",
	AM437X_EMIF4D_SDRAM_REFRESH_CTRL_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_sdram_timing_1 = {
	"EMIF4D_SDRAM_TIMING_1",
	AM437X_EMIF4D_SDRAM_TIMING_1,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_sdram_timing_1_shadow = {
	"EMIF4D_SDRAM_TIMING_1_SHADOW",
	AM437X_EMIF4D_SDRAM_TIMING_1_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_sdram_timing_2 = {
	"EMIF4D_SDRAM_TIMING_2",
	AM437X_EMIF4D_SDRAM_TIMING_2,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_sdram_timing_2_shadow = {
	"EMIF4D_SDRAM_TIMING_2_SHADOW",
	AM437X_EMIF4D_SDRAM_TIMING_2_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_sdram_timing_3 = {
	"EMIF4D_SDRAM_TIMING_3",
	AM437X_EMIF4D_SDRAM_TIMING_3,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_sdram_timing_3_shadow = {
	"EMIF4D_SDRAM_TIMING_3_SHADOW",
	AM437X_EMIF4D_SDRAM_TIMING_3_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_lpddr2_nvm_timing = {
	"EMIF4D_LPDDR2_NVM_TIMING",
	AM437X_EMIF4D_LPDDR2_NVM_TIMING,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_lpddr2_nvm_timing_shadow = {
	"EMIF4D_LPDDR2_NVM_TIMING_SHADOW",
	AM437X_EMIF4D_LPDDR2_NVM_TIMING_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_power_management_ctrl = {
	"EMIF4D_POWER_MANAGEMENT_CTRL",
	AM437X_EMIF4D_POWER_MANAGEMENT_CTRL,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_power_management_ctrl_shadow = {
	"EMIF4D_POWER_MANAGEMENT_CTRL_SHADOW",
	AM437X_EMIF4D_POWER_MANAGEMENT_CTRL_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_lpddr2_mode_reg_data = {
	"EMIF4D_LPDDR2_MODE_REG_DATA",
	AM437X_EMIF4D_LPDDR2_MODE_REG_DATA,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_lpddr2_mode_reg_config = {
	"EMIF4D_LPDDR2_MODE_REG_CONFIG",
	AM437X_EMIF4D_LPDDR2_MODE_REG_CONFIG,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ocp_config = {
	"EMIF4D_OCP_CONFIG",
	AM437X_EMIF4D_OCP_CONFIG,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ocp_config_value_1 = {
	"EMIF4D_OCP_CONFIG_VALUE_1",
	AM437X_EMIF4D_OCP_CONFIG_VALUE_1,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ocp_config_value_2 = {
	"EMIF4D_OCP_CONFIG_VALUE_2",
	AM437X_EMIF4D_OCP_CONFIG_VALUE_2,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_iodft_test_logic_global_ctrl = {
	"EMIF4D_IODFT_TEST_LOGIC_GLOBAL_CTRL",
	AM437X_EMIF4D_IODFT_TEST_LOGIC_GLOBAL_CTRL,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_iodft_test_logic_ctrl_misr_result = {
	"EMIF4D_IODFT_TEST_LOGIC_CTRL_MISR_RESULT",
	AM437X_EMIF4D_IODFT_TEST_LOGIC_CTRL_MISR_RESULT,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_iodft_test_logic_addr_misr_result = {
	"EMIF4D_IODFT_TEST_LOGIC_ADDR_MISR_RESULT",
	AM437X_EMIF4D_IODFT_TEST_LOGIC_ADDR_MISR_RESULT,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_iodft_test_logic_data_misr_result_1 = {
	"EMIF4D_IODFT_TEST_LOGIC_DATA_MISR_RESULT_1",
	AM437X_EMIF4D_IODFT_TEST_LOGIC_DATA_MISR_RESULT_1,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_iodft_test_logic_data_misr_result_2 = {
	"EMIF4D_IODFT_TEST_LOGIC_DATA_MISR_RESULT_2",
	AM437X_EMIF4D_IODFT_TEST_LOGIC_DATA_MISR_RESULT_2,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_iodft_test_logic_data_misr_result_3 = {
	"EMIF4D_IODFT_TEST_LOGIC_DATA_MISR_RESULT_3",
	AM437X_EMIF4D_IODFT_TEST_LOGIC_DATA_MISR_RESULT_3,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_performance_ctr_1 = {
	"EMIF4D_PERFORMANCE_CTR_1",
	AM437X_EMIF4D_PERFORMANCE_CTR_1,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_performance_ctr_2 = {
	"EMIF4D_PERFORMANCE_CTR_2",
	AM437X_EMIF4D_PERFORMANCE_CTR_2,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_performance_ctr_config = {
	"EMIF4D_PERFORMANCE_CTR_CONFIG",
	AM437X_EMIF4D_PERFORMANCE_CTR_CONFIG,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_performance_ctr_master_region_select = {
	"EMIF4D_PERFORMANCE_CTR_MASTER_REGION_SELECT",
	AM437X_EMIF4D_PERFORMANCE_CTR_MASTER_REGION_SELECT,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_performance_ctr_time = {
	"EMIF4D_PERFORMANCE_CTR_TIME",
	AM437X_EMIF4D_PERFORMANCE_CTR_TIME,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_misc_reg = {
	"EMIF4D_MISC_REG",
	AM437X_EMIF4D_MISC_REG,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_dll_calib_ctrl = {
	"EMIF4D_DLL_CALIB_CTRL",
	AM437X_EMIF4D_DLL_CALIB_CTRL,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_dll_calib_ctrl_shadow = {
	"EMIF4D_DLL_CALIB_CTRL_SHADOW",
	AM437X_EMIF4D_DLL_CALIB_CTRL_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_end_of_intr = {
	"EMIF4D_END_OF_INTR",
	AM437X_EMIF4D_END_OF_INTR,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_system_ocp_intr_raw_sts = {
	"EMIF4D_SYSTEM_OCP_INTR_RAW_STS",
	AM437X_EMIF4D_SYSTEM_OCP_INTR_RAW_STS,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_low_lat_ocp_intr_raw_sts = {
	"EMIF4D_LOW_LAT_OCP_INTR_RAW_STS",
	AM437X_EMIF4D_LOW_LAT_OCP_INTR_RAW_STS,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_system_ocp_intr_sts = {
	"EMIF4D_SYSTEM_OCP_INTR_STS",
	AM437X_EMIF4D_SYSTEM_OCP_INTR_STS,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_low_lat_ocp_intr_sts = {
	"EMIF4D_LOW_LAT_OCP_INTR_STS",
	AM437X_EMIF4D_LOW_LAT_OCP_INTR_STS,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_system_ocp_intr_en_set = {
	"EMIF4D_SYSTEM_OCP_INTR_EN_SET",
	AM437X_EMIF4D_SYSTEM_OCP_INTR_EN_SET,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_low_lat_ocp_intr_en_set = {
	"EMIF4D_LOW_LAT_OCP_INTR_EN_SET",
	AM437X_EMIF4D_LOW_LAT_OCP_INTR_EN_SET,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_system_ocp_intr_en_clr = {
	"EMIF4D_SYSTEM_OCP_INTR_EN_CLR",
	AM437X_EMIF4D_SYSTEM_OCP_INTR_EN_CLR,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_low_lat_ocp_intr_en_clr = {
	"EMIF4D_LOW_LAT_OCP_INTR_EN_CLR",
	AM437X_EMIF4D_LOW_LAT_OCP_INTR_EN_CLR,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_sdram_output_impedance_calibration_config = {
	"EMIF4D_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG",
	AM437X_EMIF4D_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_temperature_alert_config = {
	"EMIF4D_TEMPERATURE_ALERT_CONFIG",
	AM437X_EMIF4D_TEMPERATURE_ALERT_CONFIG,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ocp_error_log = {
	"EMIF4D_OCP_ERROR_LOG",
	AM437X_EMIF4D_OCP_ERROR_LOG,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_read_write_leveling_ramp_window = {
	"EMIF4D_READ_WRITE_LEVELING_RAMP_WINDOW",
	AM437X_EMIF4D_READ_WRITE_LEVELING_RAMP_WINDOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_read_write_leveling_ramp_ctrl = {
	"EMIF4D_READ_WRITE_LEVELING_RAMP_CTRL",
	AM437X_EMIF4D_READ_WRITE_LEVELING_RAMP_CTRL,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_read_write_leveling_ctrl = {
	"EMIF4D_READ_WRITE_LEVELING_CTRL",
	AM437X_EMIF4D_READ_WRITE_LEVELING_CTRL,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ddr_phy_ctrl_1 = {
	"EMIF4D_DDR_PHY_CTRL_1",
	AM437X_EMIF4D_DDR_PHY_CTRL_1,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ddr_phy_ctrl_1_shadow = {
	"EMIF4D_DDR_PHY_CTRL_1_SHADOW",
	AM437X_EMIF4D_DDR_PHY_CTRL_1_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_priority_to_class_of_service_mapping = {
	"EMIF4D_PRIORITY_TO_CLASS_OF_SERVICE_MAPPING",
	AM437X_EMIF4D_PRIORITY_TO_CLASS_OF_SERVICE_MAPPING,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_conn_id_to_class_of_service_1_mapping = {
	"EMIF4D_CONN_ID_TO_CLASS_OF_SERVICE_1_MAPPING",
	AM437X_EMIF4D_CONN_ID_TO_CLASS_OF_SERVICE_1_MAPPING,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_conn_id_to_class_of_service_2_mapping = {
	"EMIF4D_CONN_ID_TO_CLASS_OF_SERVICE_2_MAPPING",
	AM437X_EMIF4D_CONN_ID_TO_CLASS_OF_SERVICE_2_MAPPING,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ecc_ctrl_reg = {
	"EMIF4D_ECC_CTRL_REG",
	AM437X_EMIF4D_ECC_CTRL_REG,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ecc_addr_range_1 = {
	"EMIF4D_ECC_ADDR_RANGE_1",
	AM437X_EMIF4D_ECC_ADDR_RANGE_1,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ecc_addr_range_2 = {
	"EMIF4D_ECC_ADDR_RANGE_2",
	AM437X_EMIF4D_ECC_ADDR_RANGE_2,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_read_write_execution_thr = {
	"EMIF4D_READ_WRITE_EXECUTION_THR",
	AM437X_EMIF4D_READ_WRITE_EXECUTION_THR,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_cos_config = {
	"EMIF4D_COS_CONFIG",
	AM437X_EMIF4D_COS_CONFIG,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_1b_ecc_err_cnt = {
	"EMIF4D_1B_ECC_ERR_CNT",
	AM437X_EMIF4D_1B_ECC_ERR_CNT,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_1b_ecc_err_thrsh = {
	"EMIF4D_1B_ECC_ERR_THRSH",
	AM437X_EMIF4D_1B_ECC_ERR_THRSH,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_1b_ecc_err_dist_1 = {
	"EMIF4D_1B_ECC_ERR_DIST_1",
	AM437X_EMIF4D_1B_ECC_ERR_DIST_1,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_1b_ecc_err_addr_log = {
	"EMIF4D_1B_ECC_ERR_ADDR_LOG",
	AM437X_EMIF4D_1B_ECC_ERR_ADDR_LOG,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_2b_ecc_err_addr_log = {
	"EMIF4D_2B_ECC_ERR_ADDR_LOG",
	AM437X_EMIF4D_2B_ECC_ERR_ADDR_LOG,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_phy_sts_1 = {
	"EMIF4D_PHY_STS_1",
	AM437X_EMIF4D_PHY_STS_1,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_phy_sts_2 = {
	"EMIF4D_PHY_STS_2",
	AM437X_EMIF4D_PHY_STS_2,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_phy_sts_3 = {
	"EMIF4D_PHY_STS_3",
	AM437X_EMIF4D_PHY_STS_3,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_phy_sts_4 = {
	"EMIF4D_PHY_STS_4",
	AM437X_EMIF4D_PHY_STS_4,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_phy_sts_5 = {
	"EMIF4D_PHY_STS_5",
	AM437X_EMIF4D_PHY_STS_5,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_phy_sts_6 = {
	"EMIF4D_PHY_STS_6",
	AM437X_EMIF4D_PHY_STS_6,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_phy_sts_7 = {
	"EMIF4D_PHY_STS_7",
	AM437X_EMIF4D_PHY_STS_7,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_phy_sts_8 = {
	"EMIF4D_PHY_STS_8",
	AM437X_EMIF4D_PHY_STS_8,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_phy_sts_9 = {
	"EMIF4D_PHY_STS_9",
	AM437X_EMIF4D_PHY_STS_9,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_phy_sts_10 = {
	"EMIF4D_PHY_STS_10",
	AM437X_EMIF4D_PHY_STS_10,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_phy_sts_11 = {
	"EMIF4D_PHY_STS_11",
	AM437X_EMIF4D_PHY_STS_11,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_phy_sts_12 = {
	"EMIF4D_PHY_STS_12",
	AM437X_EMIF4D_PHY_STS_12,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_phy_sts_13 = {
	"EMIF4D_PHY_STS_13",
	AM437X_EMIF4D_PHY_STS_13,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_phy_sts_14 = {
	"EMIF4D_PHY_STS_14",
	AM437X_EMIF4D_PHY_STS_14,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_phy_sts_15 = {
	"EMIF4D_PHY_STS_15",
	AM437X_EMIF4D_PHY_STS_15,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_phy_sts_16 = {
	"EMIF4D_PHY_STS_16",
	AM437X_EMIF4D_PHY_STS_16,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_phy_sts_17 = {
	"EMIF4D_PHY_STS_17",
	AM437X_EMIF4D_PHY_STS_17,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_phy_sts_18 = {
	"EMIF4D_PHY_STS_18",
	AM437X_EMIF4D_PHY_STS_18,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_phy_sts_19 = {
	"EMIF4D_PHY_STS_19",
	AM437X_EMIF4D_PHY_STS_19,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_phy_sts_20 = {
	"EMIF4D_PHY_STS_20",
	AM437X_EMIF4D_PHY_STS_20,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_phy_sts_21 = {
	"EMIF4D_PHY_STS_21",
	AM437X_EMIF4D_PHY_STS_21,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_phy_sts_22 = {
	"EMIF4D_PHY_STS_22",
	AM437X_EMIF4D_PHY_STS_22,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_phy_sts_23 = {
	"EMIF4D_PHY_STS_23",
	AM437X_EMIF4D_PHY_STS_23,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_phy_sts_24 = {
	"EMIF4D_PHY_STS_24",
	AM437X_EMIF4D_PHY_STS_24,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_phy_sts_25 = {
	"EMIF4D_PHY_STS_25",
	AM437X_EMIF4D_PHY_STS_25,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_phy_sts_26 = {
	"EMIF4D_PHY_STS_26",
	AM437X_EMIF4D_PHY_STS_26,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_phy_sts_27 = {
	"EMIF4D_PHY_STS_27",
	AM437X_EMIF4D_PHY_STS_27,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_phy_sts_28 = {
	"EMIF4D_PHY_STS_28",
	AM437X_EMIF4D_PHY_STS_28,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_1 = {
	"EMIF4D_EXT_PHY_CTRL_1",
	AM437X_EMIF4D_EXT_PHY_CTRL_1,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_1_shadow = {
	"EMIF4D_EXT_PHY_CTRL_1_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_1_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_2 = {
	"EMIF4D_EXT_PHY_CTRL_2",
	AM437X_EMIF4D_EXT_PHY_CTRL_2,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_2_shadow = {
	"EMIF4D_EXT_PHY_CTRL_2_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_2_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_3 = {
	"EMIF4D_EXT_PHY_CTRL_3",
	AM437X_EMIF4D_EXT_PHY_CTRL_3,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_3_shadow = {
	"EMIF4D_EXT_PHY_CTRL_3_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_3_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_4 = {
	"EMIF4D_EXT_PHY_CTRL_4",
	AM437X_EMIF4D_EXT_PHY_CTRL_4,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_4_shadow = {
	"EMIF4D_EXT_PHY_CTRL_4_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_4_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_5 = {
	"EMIF4D_EXT_PHY_CTRL_5",
	AM437X_EMIF4D_EXT_PHY_CTRL_5,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_5_shadow = {
	"EMIF4D_EXT_PHY_CTRL_5_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_5_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_6 = {
	"EMIF4D_EXT_PHY_CTRL_6",
	AM437X_EMIF4D_EXT_PHY_CTRL_6,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_6_shadow = {
	"EMIF4D_EXT_PHY_CTRL_6_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_6_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_7 = {
	"EMIF4D_EXT_PHY_CTRL_7",
	AM437X_EMIF4D_EXT_PHY_CTRL_7,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_7_shadow = {
	"EMIF4D_EXT_PHY_CTRL_7_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_7_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_8 = {
	"EMIF4D_EXT_PHY_CTRL_8",
	AM437X_EMIF4D_EXT_PHY_CTRL_8,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_8_shadow = {
	"EMIF4D_EXT_PHY_CTRL_8_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_8_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_9 = {
	"EMIF4D_EXT_PHY_CTRL_9",
	AM437X_EMIF4D_EXT_PHY_CTRL_9,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_9_shadow = {
	"EMIF4D_EXT_PHY_CTRL_9_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_9_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_10 = {
	"EMIF4D_EXT_PHY_CTRL_10",
	AM437X_EMIF4D_EXT_PHY_CTRL_10,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_10_shadow = {
	"EMIF4D_EXT_PHY_CTRL_10_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_10_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_11 = {
	"EMIF4D_EXT_PHY_CTRL_11",
	AM437X_EMIF4D_EXT_PHY_CTRL_11,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_11_shadow = {
	"EMIF4D_EXT_PHY_CTRL_11_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_11_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_12 = {
	"EMIF4D_EXT_PHY_CTRL_12",
	AM437X_EMIF4D_EXT_PHY_CTRL_12,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_12_shadow = {
	"EMIF4D_EXT_PHY_CTRL_12_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_12_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_13 = {
	"EMIF4D_EXT_PHY_CTRL_13",
	AM437X_EMIF4D_EXT_PHY_CTRL_13,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_13_shadow = {
	"EMIF4D_EXT_PHY_CTRL_13_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_13_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_14 = {
	"EMIF4D_EXT_PHY_CTRL_14",
	AM437X_EMIF4D_EXT_PHY_CTRL_14,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_14_shadow = {
	"EMIF4D_EXT_PHY_CTRL_14_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_14_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_15 = {
	"EMIF4D_EXT_PHY_CTRL_15",
	AM437X_EMIF4D_EXT_PHY_CTRL_15,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_15_shadow = {
	"EMIF4D_EXT_PHY_CTRL_15_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_15_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_16 = {
	"EMIF4D_EXT_PHY_CTRL_16",
	AM437X_EMIF4D_EXT_PHY_CTRL_16,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_16_shadow = {
	"EMIF4D_EXT_PHY_CTRL_16_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_16_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_17 = {
	"EMIF4D_EXT_PHY_CTRL_17",
	AM437X_EMIF4D_EXT_PHY_CTRL_17,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_17_shadow = {
	"EMIF4D_EXT_PHY_CTRL_17_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_17_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_18 = {
	"EMIF4D_EXT_PHY_CTRL_18",
	AM437X_EMIF4D_EXT_PHY_CTRL_18,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_18_shadow = {
	"EMIF4D_EXT_PHY_CTRL_18_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_18_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_19 = {
	"EMIF4D_EXT_PHY_CTRL_19",
	AM437X_EMIF4D_EXT_PHY_CTRL_19,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_19_shadow = {
	"EMIF4D_EXT_PHY_CTRL_19_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_19_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_20 = {
	"EMIF4D_EXT_PHY_CTRL_20",
	AM437X_EMIF4D_EXT_PHY_CTRL_20,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_20_shadow = {
	"EMIF4D_EXT_PHY_CTRL_20_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_20_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_21 = {
	"EMIF4D_EXT_PHY_CTRL_21",
	AM437X_EMIF4D_EXT_PHY_CTRL_21,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_21_shadow = {
	"EMIF4D_EXT_PHY_CTRL_21_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_21_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_22 = {
	"EMIF4D_EXT_PHY_CTRL_22",
	AM437X_EMIF4D_EXT_PHY_CTRL_22,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_22_shadow = {
	"EMIF4D_EXT_PHY_CTRL_22_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_22_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_23 = {
	"EMIF4D_EXT_PHY_CTRL_23",
	AM437X_EMIF4D_EXT_PHY_CTRL_23,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_23_shadow = {
	"EMIF4D_EXT_PHY_CTRL_23_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_23_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_24 = {
	"EMIF4D_EXT_PHY_CTRL_24",
	AM437X_EMIF4D_EXT_PHY_CTRL_24,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_24_shadow = {
	"EMIF4D_EXT_PHY_CTRL_24_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_24_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_25 = {
	"EMIF4D_EXT_PHY_CTRL_25",
	AM437X_EMIF4D_EXT_PHY_CTRL_25,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_25_shadow = {
	"EMIF4D_EXT_PHY_CTRL_25_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_25_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_26 = {
	"EMIF4D_EXT_PHY_CTRL_26",
	AM437X_EMIF4D_EXT_PHY_CTRL_26,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_26_shadow = {
	"EMIF4D_EXT_PHY_CTRL_26_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_26_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_27 = {
	"EMIF4D_EXT_PHY_CTRL_27",
	AM437X_EMIF4D_EXT_PHY_CTRL_27,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_27_shadow = {
	"EMIF4D_EXT_PHY_CTRL_27_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_27_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_28 = {
	"EMIF4D_EXT_PHY_CTRL_28",
	AM437X_EMIF4D_EXT_PHY_CTRL_28,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_28_shadow = {
	"EMIF4D_EXT_PHY_CTRL_28_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_28_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_29 = {
	"EMIF4D_EXT_PHY_CTRL_29",
	AM437X_EMIF4D_EXT_PHY_CTRL_29,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_29_shadow = {
	"EMIF4D_EXT_PHY_CTRL_29_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_29_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_30 = {
	"EMIF4D_EXT_PHY_CTRL_30",
	AM437X_EMIF4D_EXT_PHY_CTRL_30,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_30_shadow = {
	"EMIF4D_EXT_PHY_CTRL_30_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_30_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_31 = {
	"EMIF4D_EXT_PHY_CTRL_31",
	AM437X_EMIF4D_EXT_PHY_CTRL_31,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_31_shadow = {
	"EMIF4D_EXT_PHY_CTRL_31_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_31_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_32 = {
	"EMIF4D_EXT_PHY_CTRL_32",
	AM437X_EMIF4D_EXT_PHY_CTRL_32,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_32_shadow = {
	"EMIF4D_EXT_PHY_CTRL_32_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_32_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_33 = {
	"EMIF4D_EXT_PHY_CTRL_33",
	AM437X_EMIF4D_EXT_PHY_CTRL_33,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_33_shadow = {
	"EMIF4D_EXT_PHY_CTRL_33_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_33_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_34 = {
	"EMIF4D_EXT_PHY_CTRL_34",
	AM437X_EMIF4D_EXT_PHY_CTRL_34,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_34_shadow = {
	"EMIF4D_EXT_PHY_CTRL_34_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_34_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_35 = {
	"EMIF4D_EXT_PHY_CTRL_35",
	AM437X_EMIF4D_EXT_PHY_CTRL_35,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_35_shadow = {
	"EMIF4D_EXT_PHY_CTRL_35_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_35_SHADOW,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_36 = {
	"EMIF4D_EXT_PHY_CTRL_36",
	AM437X_EMIF4D_EXT_PHY_CTRL_36,
	0xDEADBEEF,
	0,
};

reg am437x_emif4d_ext_phy_ctrl_36_shadow = {
	"EMIF4D_EXT_PHY_CTRL_36_SHADOW",
	AM437X_EMIF4D_EXT_PHY_CTRL_36_SHADOW,
	0xDEADBEEF,
	0,
};

reg *am437x_emif4d_mod[AM437X_EMIF4D_MOD_REGCOUNT + 1] = {
	&am437x_emif4d_mod_id_rev,
	&am437x_emif4d_sts,
	&am437x_emif4d_sdram_config,
	&am437x_emif4d_sdram_config_2,
	&am437x_emif4d_sdram_refresh_ctrl,
	&am437x_emif4d_sdram_refresh_ctrl_shadow,
	&am437x_emif4d_sdram_timing_1,
	&am437x_emif4d_sdram_timing_1_shadow,
	&am437x_emif4d_sdram_timing_2,
	&am437x_emif4d_sdram_timing_2_shadow,
	&am437x_emif4d_sdram_timing_3,
	&am437x_emif4d_sdram_timing_3_shadow,
	&am437x_emif4d_lpddr2_nvm_timing,
	&am437x_emif4d_lpddr2_nvm_timing_shadow,
	&am437x_emif4d_power_management_ctrl,
	&am437x_emif4d_power_management_ctrl_shadow,
	&am437x_emif4d_lpddr2_mode_reg_data,
	&am437x_emif4d_lpddr2_mode_reg_config,
	&am437x_emif4d_ocp_config,
	&am437x_emif4d_ocp_config_value_1,
	&am437x_emif4d_ocp_config_value_2,
	&am437x_emif4d_iodft_test_logic_global_ctrl,
	&am437x_emif4d_iodft_test_logic_ctrl_misr_result,
	&am437x_emif4d_iodft_test_logic_addr_misr_result,
	&am437x_emif4d_iodft_test_logic_data_misr_result_1,
	&am437x_emif4d_iodft_test_logic_data_misr_result_2,
	&am437x_emif4d_iodft_test_logic_data_misr_result_3,
	&am437x_emif4d_performance_ctr_1,
	&am437x_emif4d_performance_ctr_2,
	&am437x_emif4d_performance_ctr_config,
	&am437x_emif4d_performance_ctr_master_region_select,
	&am437x_emif4d_performance_ctr_time,
	&am437x_emif4d_misc_reg,
	&am437x_emif4d_dll_calib_ctrl,
	&am437x_emif4d_dll_calib_ctrl_shadow,
	&am437x_emif4d_end_of_intr,
	&am437x_emif4d_system_ocp_intr_raw_sts,
	&am437x_emif4d_low_lat_ocp_intr_raw_sts,
	&am437x_emif4d_system_ocp_intr_sts,
	&am437x_emif4d_low_lat_ocp_intr_sts,
	&am437x_emif4d_system_ocp_intr_en_set,
	&am437x_emif4d_low_lat_ocp_intr_en_set,
	&am437x_emif4d_system_ocp_intr_en_clr,
	&am437x_emif4d_low_lat_ocp_intr_en_clr,
	&am437x_emif4d_sdram_output_impedance_calibration_config,
	&am437x_emif4d_temperature_alert_config,
	&am437x_emif4d_ocp_error_log,
	&am437x_emif4d_read_write_leveling_ramp_window,
	&am437x_emif4d_read_write_leveling_ramp_ctrl,
	&am437x_emif4d_read_write_leveling_ctrl,
	&am437x_emif4d_ddr_phy_ctrl_1,
	&am437x_emif4d_ddr_phy_ctrl_1_shadow,
	&am437x_emif4d_priority_to_class_of_service_mapping,
	&am437x_emif4d_conn_id_to_class_of_service_1_mapping,
	&am437x_emif4d_conn_id_to_class_of_service_2_mapping,
	&am437x_emif4d_ecc_ctrl_reg,
	&am437x_emif4d_ecc_addr_range_1,
	&am437x_emif4d_ecc_addr_range_2,
	&am437x_emif4d_read_write_execution_thr,
	&am437x_emif4d_cos_config,
	&am437x_emif4d_1b_ecc_err_cnt,
	&am437x_emif4d_1b_ecc_err_thrsh,
	&am437x_emif4d_1b_ecc_err_dist_1,
	&am437x_emif4d_1b_ecc_err_addr_log,
	&am437x_emif4d_2b_ecc_err_addr_log,
	&am437x_emif4d_phy_sts_1,
	&am437x_emif4d_phy_sts_2,
	&am437x_emif4d_phy_sts_3,
	&am437x_emif4d_phy_sts_4,
	&am437x_emif4d_phy_sts_5,
	&am437x_emif4d_phy_sts_6,
	&am437x_emif4d_phy_sts_7,
	&am437x_emif4d_phy_sts_8,
	&am437x_emif4d_phy_sts_9,
	&am437x_emif4d_phy_sts_10,
	&am437x_emif4d_phy_sts_11,
	&am437x_emif4d_phy_sts_12,
	&am437x_emif4d_phy_sts_13,
	&am437x_emif4d_phy_sts_14,
	&am437x_emif4d_phy_sts_15,
	&am437x_emif4d_phy_sts_16,
	&am437x_emif4d_phy_sts_17,
	&am437x_emif4d_phy_sts_18,
	&am437x_emif4d_phy_sts_19,
	&am437x_emif4d_phy_sts_20,
	&am437x_emif4d_phy_sts_21,
	&am437x_emif4d_phy_sts_22,
	&am437x_emif4d_phy_sts_23,
	&am437x_emif4d_phy_sts_24,
	&am437x_emif4d_phy_sts_25,
	&am437x_emif4d_phy_sts_26,
	&am437x_emif4d_phy_sts_27,
	&am437x_emif4d_phy_sts_28,
	&am437x_emif4d_ext_phy_ctrl_1,
	&am437x_emif4d_ext_phy_ctrl_1_shadow,
	&am437x_emif4d_ext_phy_ctrl_2,
	&am437x_emif4d_ext_phy_ctrl_2_shadow,
	&am437x_emif4d_ext_phy_ctrl_3,
	&am437x_emif4d_ext_phy_ctrl_3_shadow,
	&am437x_emif4d_ext_phy_ctrl_4,
	&am437x_emif4d_ext_phy_ctrl_4_shadow,
	&am437x_emif4d_ext_phy_ctrl_5,
	&am437x_emif4d_ext_phy_ctrl_5_shadow,
	&am437x_emif4d_ext_phy_ctrl_6,
	&am437x_emif4d_ext_phy_ctrl_6_shadow,
	&am437x_emif4d_ext_phy_ctrl_7,
	&am437x_emif4d_ext_phy_ctrl_7_shadow,
	&am437x_emif4d_ext_phy_ctrl_8,
	&am437x_emif4d_ext_phy_ctrl_8_shadow,
	&am437x_emif4d_ext_phy_ctrl_9,
	&am437x_emif4d_ext_phy_ctrl_9_shadow,
	&am437x_emif4d_ext_phy_ctrl_10,
	&am437x_emif4d_ext_phy_ctrl_10_shadow,
	&am437x_emif4d_ext_phy_ctrl_11,
	&am437x_emif4d_ext_phy_ctrl_11_shadow,
	&am437x_emif4d_ext_phy_ctrl_12,
	&am437x_emif4d_ext_phy_ctrl_12_shadow,
	&am437x_emif4d_ext_phy_ctrl_13,
	&am437x_emif4d_ext_phy_ctrl_13_shadow,
	&am437x_emif4d_ext_phy_ctrl_14,
	&am437x_emif4d_ext_phy_ctrl_14_shadow,
	&am437x_emif4d_ext_phy_ctrl_15,
	&am437x_emif4d_ext_phy_ctrl_15_shadow,
	&am437x_emif4d_ext_phy_ctrl_16,
	&am437x_emif4d_ext_phy_ctrl_16_shadow,
	&am437x_emif4d_ext_phy_ctrl_17,
	&am437x_emif4d_ext_phy_ctrl_17_shadow,
	&am437x_emif4d_ext_phy_ctrl_18,
	&am437x_emif4d_ext_phy_ctrl_18_shadow,
	&am437x_emif4d_ext_phy_ctrl_19,
	&am437x_emif4d_ext_phy_ctrl_19_shadow,
	&am437x_emif4d_ext_phy_ctrl_20,
	&am437x_emif4d_ext_phy_ctrl_20_shadow,
	&am437x_emif4d_ext_phy_ctrl_21,
	&am437x_emif4d_ext_phy_ctrl_21_shadow,
	&am437x_emif4d_ext_phy_ctrl_22,
	&am437x_emif4d_ext_phy_ctrl_22_shadow,
	&am437x_emif4d_ext_phy_ctrl_23,
	&am437x_emif4d_ext_phy_ctrl_23_shadow,
	&am437x_emif4d_ext_phy_ctrl_24,
	&am437x_emif4d_ext_phy_ctrl_24_shadow,
	&am437x_emif4d_ext_phy_ctrl_25,
	&am437x_emif4d_ext_phy_ctrl_25_shadow,
	&am437x_emif4d_ext_phy_ctrl_26,
	&am437x_emif4d_ext_phy_ctrl_26_shadow,
	&am437x_emif4d_ext_phy_ctrl_27,
	&am437x_emif4d_ext_phy_ctrl_27_shadow,
	&am437x_emif4d_ext_phy_ctrl_28,
	&am437x_emif4d_ext_phy_ctrl_28_shadow,
	&am437x_emif4d_ext_phy_ctrl_29,
	&am437x_emif4d_ext_phy_ctrl_29_shadow,
	&am437x_emif4d_ext_phy_ctrl_30,
	&am437x_emif4d_ext_phy_ctrl_30_shadow,
	&am437x_emif4d_ext_phy_ctrl_31,
	&am437x_emif4d_ext_phy_ctrl_31_shadow,
	&am437x_emif4d_ext_phy_ctrl_32,
	&am437x_emif4d_ext_phy_ctrl_32_shadow,
	&am437x_emif4d_ext_phy_ctrl_33,
	&am437x_emif4d_ext_phy_ctrl_33_shadow,
	&am437x_emif4d_ext_phy_ctrl_34,
	&am437x_emif4d_ext_phy_ctrl_34_shadow,
	&am437x_emif4d_ext_phy_ctrl_35,
	&am437x_emif4d_ext_phy_ctrl_35_shadow,
	&am437x_emif4d_ext_phy_ctrl_36,
	&am437x_emif4d_ext_phy_ctrl_36_shadow,
	NULL,
};

reg **emif_am437x_mods[EMIF_AM437X_MODS_COUNT] = {
	(reg **) &am437x_emif4d_mod
};

const char *emif_am437x_mods_name[EMIF_AM437X_MODS_COUNT] = {
	"EMIF4D"
};
