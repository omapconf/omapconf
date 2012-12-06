/*
 *
 * @Component			OMAPCONF
 * @Filename			ctrlmod_core54xx-defs.c
 * @Description			OMAP5 CONTROL MODULE Registers Definitions
 * @Author			Patrick Titiano (p-titiano@ti.com)
 * @Date			2011
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
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


#include <ctrlmod_core54xx-defs.h>

reg omap5430_control_core_revision = {
	"CONTROL_CORE_REVISION",
	OMAP5430_CONTROL_CORE_REVISION,
	0xDEADBEEF,
	0};

reg omap5430_control_core_hwinfo = {
	"CONTROL_CORE_HWINFO",
	OMAP5430_CONTROL_CORE_HWINFO,
	0xDEADBEEF,
	0};

reg omap5430_control_core_sysconfig = {
	"CONTROL_CORE_SYSCONFIG",
	OMAP5430_CONTROL_CORE_SYSCONFIG,
	0xDEADBEEF,
	0};

reg omap5430_control_l3_hw_fw_exported_values_conf_dbg = {
	"CONTROL_L3_HW_FW_EXPORTED_VALUES_CONF_DBG",
	OMAP5430_CONTROL_L3_HW_FW_EXPORTED_VALUES_CONF_DBG,
	0xDEADBEEF,
	0};

reg omap5430_control_l3_hw_fw_exported_values_conf_func = {
	"CONTROL_L3_HW_FW_EXPORTED_VALUES_CONF_FUNC",
	OMAP5430_CONTROL_L3_HW_FW_EXPORTED_VALUES_CONF_FUNC,
	0xDEADBEEF,
	0};

reg omap5430_control_status = {
	"CONTROL_STATUS",
	OMAP5430_CONTROL_STATUS,
	0xDEADBEEF,
	0};

reg omap5430_control_sec_err_status_func = {
	"CONTROL_SEC_ERR_STATUS_FUNC",
	OMAP5430_CONTROL_SEC_ERR_STATUS_FUNC,
	0xDEADBEEF,
	0};

reg omap5430_control_sec_err_status_debug = {
	"CONTROL_SEC_ERR_STATUS_DEBUG",
	OMAP5430_CONTROL_SEC_ERR_STATUS_DEBUG,
	0xDEADBEEF,
	0};

reg omap5430_control_forcewrnp = {
	"CONTROL_FORCEWRNP",
	OMAP5430_CONTROL_FORCEWRNP,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_mm_0 = {
	"CONTROL_STD_FUSE_OPP_VDD_MM_0",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MM_0,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_mm_1 = {
	"CONTROL_STD_FUSE_OPP_VDD_MM_1",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MM_1,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_mm_2 = {
	"CONTROL_STD_FUSE_OPP_VDD_MM_2",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MM_2,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_mm_3 = {
	"CONTROL_STD_FUSE_OPP_VDD_MM_3",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MM_3,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_mm_4 = {
	"CONTROL_STD_FUSE_OPP_VDD_MM_4",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MM_4,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_mm_5 = {
	"CONTROL_STD_FUSE_OPP_VDD_MM_5",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MM_5,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_mpu_0 = {
	"CONTROL_STD_FUSE_OPP_VDD_MPU_0",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_0,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_mpu_1 = {
	"CONTROL_STD_FUSE_OPP_VDD_MPU_1",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_1,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_mpu_2 = {
	"CONTROL_STD_FUSE_OPP_VDD_MPU_2",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_2,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_mpu_3 = {
	"CONTROL_STD_FUSE_OPP_VDD_MPU_3",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_3,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_mpu_4 = {
	"CONTROL_STD_FUSE_OPP_VDD_MPU_4",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_4,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_mpu_5 = {
	"CONTROL_STD_FUSE_OPP_VDD_MPU_5",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_5,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_mpu_6 = {
	"CONTROL_STD_FUSE_OPP_VDD_MPU_6",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_6,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_mpu_7 = {
	"CONTROL_STD_FUSE_OPP_VDD_MPU_7",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_7,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_core_0 = {
	"CONTROL_STD_FUSE_OPP_VDD_CORE_0",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_CORE_0,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_core_1 = {
	"CONTROL_STD_FUSE_OPP_VDD_CORE_1",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_CORE_1,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_core_2 = {
	"CONTROL_STD_FUSE_OPP_VDD_CORE_2",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_CORE_2,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_core_3 = {
	"CONTROL_STD_FUSE_OPP_VDD_CORE_3",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_CORE_3,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_core_4 = {
	"CONTROL_STD_FUSE_OPP_VDD_CORE_4",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_CORE_4,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_bgap_mm = {
	"CONTROL_STD_FUSE_OPP_BGAP_MM",
	OMAP5430_CONTROL_STD_FUSE_OPP_BGAP_MM,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_bgap_mpu = {
	"CONTROL_STD_FUSE_OPP_BGAP_MPU",
	OMAP5430_CONTROL_STD_FUSE_OPP_BGAP_MPU,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_bgap_core = {
	"CONTROL_STD_FUSE_OPP_BGAP_CORE",
	OMAP5430_CONTROL_STD_FUSE_OPP_BGAP_CORE,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_bgap_mpu23 = {
	"CONTROL_STD_FUSE_OPP_BGAP_MPU23",
	OMAP5430_CONTROL_STD_FUSE_OPP_BGAP_MPU23,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_die_id_0 = {
	"CONTROL_STD_FUSE_DIE_ID_0",
	OMAP5430_CONTROL_STD_FUSE_DIE_ID_0,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_die_id_1 = {
	"CONTROL_STD_FUSE_DIE_ID_1",
	OMAP5430_CONTROL_STD_FUSE_DIE_ID_1,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_die_id_2 = {
	"CONTROL_STD_FUSE_DIE_ID_2",
	OMAP5430_CONTROL_STD_FUSE_DIE_ID_2,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_die_id_3 = {
	"CONTROL_STD_FUSE_DIE_ID_3",
	OMAP5430_CONTROL_STD_FUSE_DIE_ID_3,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_prod_id = {
	"CONTROL_STD_FUSE_PROD_ID",
	OMAP5430_CONTROL_STD_FUSE_PROD_ID,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_conf_id_0 = {
	"CONTROL_STD_FUSE_CONF_ID_0",
	OMAP5430_CONTROL_STD_FUSE_CONF_ID_0,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_conf_id_1 = {
	"CONTROL_STD_FUSE_CONF_ID_1",
	OMAP5430_CONTROL_STD_FUSE_CONF_ID_1,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_mpk_0 = {
	"CONTROL_STD_FUSE_MPK_0",
	OMAP5430_CONTROL_STD_FUSE_MPK_0,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_mpk_1 = {
	"CONTROL_STD_FUSE_MPK_1",
	OMAP5430_CONTROL_STD_FUSE_MPK_1,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_mpk_2 = {
	"CONTROL_STD_FUSE_MPK_2",
	OMAP5430_CONTROL_STD_FUSE_MPK_2,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_mpk_3 = {
	"CONTROL_STD_FUSE_MPK_3",
	OMAP5430_CONTROL_STD_FUSE_MPK_3,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_mpk_4 = {
	"CONTROL_STD_FUSE_MPK_4",
	OMAP5430_CONTROL_STD_FUSE_MPK_4,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_mpk_5 = {
	"CONTROL_STD_FUSE_MPK_5",
	OMAP5430_CONTROL_STD_FUSE_MPK_5,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_mpk_6 = {
	"CONTROL_STD_FUSE_MPK_6",
	OMAP5430_CONTROL_STD_FUSE_MPK_6,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_mpk_7 = {
	"CONTROL_STD_FUSE_MPK_7",
	OMAP5430_CONTROL_STD_FUSE_MPK_7,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_mm_lvt_0 = {
	"CONTROL_STD_FUSE_OPP_VDD_MM_LVT_0",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MM_LVT_0,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_mm_lvt_1 = {
	"CONTROL_STD_FUSE_OPP_VDD_MM_LVT_1",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MM_LVT_1,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_mm_lvt_2 = {
	"CONTROL_STD_FUSE_OPP_VDD_MM_LVT_2",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MM_LVT_2,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_mm_lvt_3 = {
	"CONTROL_STD_FUSE_OPP_VDD_MM_LVT_3",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MM_LVT_3,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_mm_lvt_4 = {
	"CONTROL_STD_FUSE_OPP_VDD_MM_LVT_4",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MM_LVT_4,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_mm_lvt_5 = {
	"CONTROL_STD_FUSE_OPP_VDD_MM_LVT_5",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MM_LVT_5,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_mpu_lvt_0 = {
	"CONTROL_STD_FUSE_OPP_VDD_MPU_LVT_0",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_LVT_0,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_mpu_lvt_1 = {
	"CONTROL_STD_FUSE_OPP_VDD_MPU_LVT_1",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_LVT_1,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_mpu_lvt_2 = {
	"CONTROL_STD_FUSE_OPP_VDD_MPU_LVT_2",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_LVT_2,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_mpu_lvt_3 = {
	"CONTROL_STD_FUSE_OPP_VDD_MPU_LVT_3",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_LVT_3,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_mpu_lvt_4 = {
	"CONTROL_STD_FUSE_OPP_VDD_MPU_LVT_4",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_LVT_4,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_mpu_lvt_5 = {
	"CONTROL_STD_FUSE_OPP_VDD_MPU_LVT_5",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_LVT_5,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_mpu_lvt_6 = {
	"CONTROL_STD_FUSE_OPP_VDD_MPU_LVT_6",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_LVT_6,
	0xDEADBEEF,
	0};

reg omap5430_control_std_fuse_opp_vdd_mpu_lvt_7 = {
	"CONTROL_STD_FUSE_OPP_VDD_MPU_LVT_7",
	OMAP5430_CONTROL_STD_FUSE_OPP_VDD_MPU_LVT_7,
	0xDEADBEEF,
	0};

reg omap5430_control_cust_fuse_swrv_0 = {
	"CONTROL_CUST_FUSE_SWRV_0",
	OMAP5430_CONTROL_CUST_FUSE_SWRV_0,
	0xDEADBEEF,
	0};

reg omap5430_control_cust_fuse_swrv_1 = {
	"CONTROL_CUST_FUSE_SWRV_1",
	OMAP5430_CONTROL_CUST_FUSE_SWRV_1,
	0xDEADBEEF,
	0};

reg omap5430_control_cust_fuse_swrv_2 = {
	"CONTROL_CUST_FUSE_SWRV_2",
	OMAP5430_CONTROL_CUST_FUSE_SWRV_2,
	0xDEADBEEF,
	0};

reg omap5430_control_cust_fuse_swrv_3 = {
	"CONTROL_CUST_FUSE_SWRV_3",
	OMAP5430_CONTROL_CUST_FUSE_SWRV_3,
	0xDEADBEEF,
	0};

reg omap5430_control_cust_fuse_swrv_4 = {
	"CONTROL_CUST_FUSE_SWRV_4",
	OMAP5430_CONTROL_CUST_FUSE_SWRV_4,
	0xDEADBEEF,
	0};

reg omap5430_control_cust_fuse_swrv_5 = {
	"CONTROL_CUST_FUSE_SWRV_5",
	OMAP5430_CONTROL_CUST_FUSE_SWRV_5,
	0xDEADBEEF,
	0};

reg omap5430_control_cust_fuse_swrv_6 = {
	"CONTROL_CUST_FUSE_SWRV_6",
	OMAP5430_CONTROL_CUST_FUSE_SWRV_6,
	0xDEADBEEF,
	0};

reg omap5430_control_hwobsdivider1 = {
	"CONTROL_HWOBSDIVIDER1",
	OMAP5430_CONTROL_HWOBSDIVIDER1,
	0xDEADBEEF,
	0};

reg omap5430_control_hwobsdivider2 = {
	"CONTROL_HWOBSDIVIDER2",
	OMAP5430_CONTROL_HWOBSDIVIDER2,
	0xDEADBEEF,
	0};

reg omap5430_control_breg_selection = {
	"CONTROL_BREG_SELECTION",
	OMAP5430_CONTROL_BREG_SELECTION,
	0xDEADBEEF,
	0};

reg omap5430_control_dpll_bclk = {
	"CONTROL_DPLL_BCLK",
	OMAP5430_CONTROL_DPLL_BCLK,
	0xDEADBEEF,
	0};

reg omap5430_control_dpll_baddr_bdataw = {
	"CONTROL_DPLL_BADDR_BDATAW",
	OMAP5430_CONTROL_DPLL_BADDR_BDATAW,
	0xDEADBEEF,
	0};

reg omap5430_control_dpll_bdatar = {
	"CONTROL_DPLL_BDATAR",
	OMAP5430_CONTROL_DPLL_BDATAR,
	0xDEADBEEF,
	0};

reg omap5430_control_dev_conf = {
	"CONTROL_DEV_CONF",
	OMAP5430_CONTROL_DEV_CONF,
	0xDEADBEEF,
	0};

reg omap5430_control_dsp_bootaddr = {
	"CONTROL_DSP_BOOTADDR",
	OMAP5430_CONTROL_DSP_BOOTADDR,
	0xDEADBEEF,
	0};

reg omap5430_control_temp_sensor_mpu = {
	"CONTROL_TEMP_SENSOR_MPU",
	OMAP5430_CONTROL_TEMP_SENSOR_MPU,
	0xDEADBEEF,
	0};

reg omap5430_control_temp_sensor_mm = {
	"CONTROL_TEMP_SENSOR_MM",
	OMAP5430_CONTROL_TEMP_SENSOR_MM,
	0xDEADBEEF,
	0};

reg omap5430_control_temp_sensor_core = {
	"CONTROL_TEMP_SENSOR_CORE",
	OMAP5430_CONTROL_TEMP_SENSOR_CORE,
	0xDEADBEEF,
	0};

reg omap5430_control_ldosram_mpu_lvt_voltage_ctrl = {
	"CONTROL_LDOSRAM_MPU_LVT_VOLTAGE_CTRL",
	OMAP5430_CONTROL_LDOSRAM_MPU_LVT_VOLTAGE_CTRL,
	0xDEADBEEF,
	0};

reg omap5430_control_cortex_m4_mmuaddrtransltr = {
	"CONTROL_CORTEX_M4_MMUADDRTRANSLTR",
	OMAP5430_CONTROL_CORTEX_M4_MMUADDRTRANSLTR,
	0xDEADBEEF,
	0};

reg omap5430_control_cortex_m4_mmuaddrlogictr = {
	"CONTROL_CORTEX_M4_MMUADDRLOGICTR",
	OMAP5430_CONTROL_CORTEX_M4_MMUADDRLOGICTR,
	0xDEADBEEF,
	0};

reg omap5430_control_hwobs_control = {
	"CONTROL_HWOBS_CONTROL",
	OMAP5430_CONTROL_HWOBS_CONTROL,
	0xDEADBEEF,
	0};

reg omap5430_control_pcs1 = {
	"CONTROL_PCS1",
	OMAP5430_CONTROL_PCS1,
	0xDEADBEEF,
	0};

reg omap5430_control_pcs2 = {
	"CONTROL_PCS2",
	OMAP5430_CONTROL_PCS2,
	0xDEADBEEF,
	0};

reg omap5430_control_pcs_revision = {
	"CONTROL_PCS_REVISION",
	OMAP5430_CONTROL_PCS_REVISION,
	0xDEADBEEF,
	0};

reg omap5430_control_phy_power_usb = {
	"CONTROL_PHY_POWER_USB",
	OMAP5430_CONTROL_PHY_POWER_USB,
	0xDEADBEEF,
	0};

reg omap5430_control_phy_power_sata = {
	"CONTROL_PHY_POWER_SATA",
	OMAP5430_CONTROL_PHY_POWER_SATA,
	0xDEADBEEF,
	0};

reg omap5430_control_slimbus_keeper = {
	"CONTROL_SLIMBUS_KEEPER",
	OMAP5430_CONTROL_SLIMBUS_KEEPER,
	0xDEADBEEF,
	0};

reg omap5430_control_phy_sel = {
	"CONTROL_PHY_SEL",
	OMAP5430_CONTROL_PHY_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_bandgap_mask = {
	"CONTROL_BANDGAP_MASK",
	OMAP5430_CONTROL_BANDGAP_MASK,
	0xDEADBEEF,
	0};

reg omap5430_control_bandgap_threshold_mpu = {
	"CONTROL_BANDGAP_THRESHOLD_MPU",
	OMAP5430_CONTROL_BANDGAP_THRESHOLD_MPU,
	0xDEADBEEF,
	0};

reg omap5430_control_bandgap_threshold_mm = {
	"CONTROL_BANDGAP_THRESHOLD_MM",
	OMAP5430_CONTROL_BANDGAP_THRESHOLD_MM,
	0xDEADBEEF,
	0};

reg omap5430_control_bandgap_threshold_core = {
	"CONTROL_BANDGAP_THRESHOLD_CORE",
	OMAP5430_CONTROL_BANDGAP_THRESHOLD_CORE,
	0xDEADBEEF,
	0};

reg omap5430_control_bandgap_tshut_mpu = {
	"CONTROL_BANDGAP_TSHUT_MPU",
	OMAP5430_CONTROL_BANDGAP_TSHUT_MPU,
	0xDEADBEEF,
	0};

reg omap5430_control_bandgap_tshut_mm = {
	"CONTROL_BANDGAP_TSHUT_MM",
	OMAP5430_CONTROL_BANDGAP_TSHUT_MM,
	0xDEADBEEF,
	0};

reg omap5430_control_bandgap_tshut_core = {
	"CONTROL_BANDGAP_TSHUT_CORE",
	OMAP5430_CONTROL_BANDGAP_TSHUT_CORE,
	0xDEADBEEF,
	0};

reg omap5430_control_bandgap_counter_mpu = {
	"CONTROL_BANDGAP_COUNTER_MPU",
	OMAP5430_CONTROL_BANDGAP_COUNTER_MPU,
	0xDEADBEEF,
	0};

reg omap5430_control_bandgap_counter_mm = {
	"CONTROL_BANDGAP_COUNTER_MM",
	OMAP5430_CONTROL_BANDGAP_COUNTER_MM,
	0xDEADBEEF,
	0};

reg omap5430_control_bandgap_counter_core = {
	"CONTROL_BANDGAP_COUNTER_CORE",
	OMAP5430_CONTROL_BANDGAP_COUNTER_CORE,
	0xDEADBEEF,
	0};

reg omap5430_control_bandgap_cumul_dtemp_mpu = {
	"CONTROL_BANDGAP_CUMUL_DTEMP_MPU",
	OMAP5430_CONTROL_BANDGAP_CUMUL_DTEMP_MPU,
	0xDEADBEEF,
	0};

reg omap5430_control_bandgap_cumul_dtemp_mm = {
	"CONTROL_BANDGAP_CUMUL_DTEMP_MM",
	OMAP5430_CONTROL_BANDGAP_CUMUL_DTEMP_MM,
	0xDEADBEEF,
	0};

reg omap5430_control_bandgap_cumul_dtemp_core = {
	"CONTROL_BANDGAP_CUMUL_DTEMP_CORE",
	OMAP5430_CONTROL_BANDGAP_CUMUL_DTEMP_CORE,
	0xDEADBEEF,
	0};

reg omap5430_control_bandgap_status = {
	"CONTROL_BANDGAP_STATUS",
	OMAP5430_CONTROL_BANDGAP_STATUS,
	0xDEADBEEF,
	0};

reg omap5430_control_sata_ext_mode = {
	"CONTROL_SATA_EXT_MODE",
	OMAP5430_CONTROL_SATA_EXT_MODE,
	0xDEADBEEF,
	0};

reg omap5430_control_dtemp_mpu_0 = {
	"CONTROL_DTEMP_MPU_0",
	OMAP5430_CONTROL_DTEMP_MPU_0,
	0xDEADBEEF,
	0};

reg omap5430_control_dtemp_mpu_1 = {
	"CONTROL_DTEMP_MPU_1",
	OMAP5430_CONTROL_DTEMP_MPU_1,
	0xDEADBEEF,
	0};

reg omap5430_control_dtemp_mpu_2 = {
	"CONTROL_DTEMP_MPU_2",
	OMAP5430_CONTROL_DTEMP_MPU_2,
	0xDEADBEEF,
	0};

reg omap5430_control_dtemp_mpu_3 = {
	"CONTROL_DTEMP_MPU_3",
	OMAP5430_CONTROL_DTEMP_MPU_3,
	0xDEADBEEF,
	0};

reg omap5430_control_dtemp_mpu_4 = {
	"CONTROL_DTEMP_MPU_4",
	OMAP5430_CONTROL_DTEMP_MPU_4,
	0xDEADBEEF,
	0};

reg omap5430_control_dtemp_mm_0 = {
	"CONTROL_DTEMP_MM_0",
	OMAP5430_CONTROL_DTEMP_MM_0,
	0xDEADBEEF,
	0};

reg omap5430_control_dtemp_mm_1 = {
	"CONTROL_DTEMP_MM_1",
	OMAP5430_CONTROL_DTEMP_MM_1,
	0xDEADBEEF,
	0};

reg omap5430_control_dtemp_mm_2 = {
	"CONTROL_DTEMP_MM_2",
	OMAP5430_CONTROL_DTEMP_MM_2,
	0xDEADBEEF,
	0};

reg omap5430_control_dtemp_mm_3 = {
	"CONTROL_DTEMP_MM_3",
	OMAP5430_CONTROL_DTEMP_MM_3,
	0xDEADBEEF,
	0};

reg omap5430_control_dtemp_mm_4 = {
	"CONTROL_DTEMP_MM_4",
	OMAP5430_CONTROL_DTEMP_MM_4,
	0xDEADBEEF,
	0};

reg omap5430_control_dtemp_core_0 = {
	"CONTROL_DTEMP_CORE_0",
	OMAP5430_CONTROL_DTEMP_CORE_0,
	0xDEADBEEF,
	0};

reg omap5430_control_dtemp_core_1 = {
	"CONTROL_DTEMP_CORE_1",
	OMAP5430_CONTROL_DTEMP_CORE_1,
	0xDEADBEEF,
	0};

reg omap5430_control_dtemp_core_2 = {
	"CONTROL_DTEMP_CORE_2",
	OMAP5430_CONTROL_DTEMP_CORE_2,
	0xDEADBEEF,
	0};

reg omap5430_control_dtemp_core_3 = {
	"CONTROL_DTEMP_CORE_3",
	OMAP5430_CONTROL_DTEMP_CORE_3,
	0xDEADBEEF,
	0};

reg omap5430_control_dtemp_core_4 = {
	"CONTROL_DTEMP_CORE_4",
	OMAP5430_CONTROL_DTEMP_CORE_4,
	0xDEADBEEF,
	0};

reg omap5430_control_ocpreg_spare = {
	"CONTROL_OCPREG_SPARE",
	OMAP5430_CONTROL_OCPREG_SPARE,
	0xDEADBEEF,
	0};

reg omap5430_control_debobs_final_mux_sel = {
	"CONTROL_DEBOBS_FINAL_MUX_SEL",
	OMAP5430_CONTROL_DEBOBS_FINAL_MUX_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_debobs_ocpwp_sys_event_sel = {
	"CONTROL_DEBOBS_OCPWP_SYS_EVENT_SEL",
	OMAP5430_CONTROL_DEBOBS_OCPWP_SYS_EVENT_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_debobs_mmr_mpu = {
	"CONTROL_DEBOBS_MMR_MPU",
	OMAP5430_CONTROL_DEBOBS_MMR_MPU,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_mdma_req_sel0 = {
	"CONTROL_CONF_MDMA_REQ_SEL0",
	OMAP5430_CONTROL_CONF_MDMA_REQ_SEL0,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_mdma_req_sel1 = {
	"CONTROL_CONF_MDMA_REQ_SEL1",
	OMAP5430_CONTROL_CONF_MDMA_REQ_SEL1,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_mdma_req_sel2 = {
	"CONTROL_CONF_MDMA_REQ_SEL2",
	OMAP5430_CONTROL_CONF_MDMA_REQ_SEL2,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_mdma_req_sel3 = {
	"CONTROL_CONF_MDMA_REQ_SEL3",
	OMAP5430_CONTROL_CONF_MDMA_REQ_SEL3,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_mdma_req_sel4 = {
	"CONTROL_CONF_MDMA_REQ_SEL4",
	OMAP5430_CONTROL_CONF_MDMA_REQ_SEL4,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_mdma_req_sel5 = {
	"CONTROL_CONF_MDMA_REQ_SEL5",
	OMAP5430_CONTROL_CONF_MDMA_REQ_SEL5,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_sdma_req_sel0 = {
	"CONTROL_CONF_SDMA_REQ_SEL0",
	OMAP5430_CONTROL_CONF_SDMA_REQ_SEL0,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_sdma_req_sel1 = {
	"CONTROL_CONF_SDMA_REQ_SEL1",
	OMAP5430_CONTROL_CONF_SDMA_REQ_SEL1,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_sdma_req_sel2 = {
	"CONTROL_CONF_SDMA_REQ_SEL2",
	OMAP5430_CONTROL_CONF_SDMA_REQ_SEL2,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_sdma_req_sel3 = {
	"CONTROL_CONF_SDMA_REQ_SEL3",
	OMAP5430_CONTROL_CONF_SDMA_REQ_SEL3,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_clk_sel0 = {
	"CONTROL_CONF_CLK_SEL0",
	OMAP5430_CONTROL_CONF_CLK_SEL0,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_clk_sel1 = {
	"CONTROL_CONF_CLK_SEL1",
	OMAP5430_CONTROL_CONF_CLK_SEL1,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_clk_sel2 = {
	"CONTROL_CONF_CLK_SEL2",
	OMAP5430_CONTROL_CONF_CLK_SEL2,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_dpll_freqlock_sel = {
	"CONTROL_CONF_DPLL_FREQLOCK_SEL",
	OMAP5430_CONTROL_CONF_DPLL_FREQLOCK_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_dpll_tinitz_sel = {
	"CONTROL_CONF_DPLL_TINITZ_SEL",
	OMAP5430_CONTROL_CONF_DPLL_TINITZ_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_dpll_phaselock_sel = {
	"CONTROL_CONF_DPLL_PHASELOCK_SEL",
	OMAP5430_CONTROL_CONF_DPLL_PHASELOCK_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_dpll_tenable_sel = {
	"CONTROL_CONF_DPLL_TENABLE_SEL",
	OMAP5430_CONTROL_CONF_DPLL_TENABLE_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_dpll_tenablediv_sel = {
	"CONTROL_CONF_DPLL_TENABLEDIV_SEL",
	OMAP5430_CONTROL_CONF_DPLL_TENABLEDIV_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_dpll_bypassack_sel = {
	"CONTROL_CONF_DPLL_BYPASSACK_SEL",
	OMAP5430_CONTROL_CONF_DPLL_BYPASSACK_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_dpll_idle_sel = {
	"CONTROL_CONF_DPLL_IDLE_SEL",
	OMAP5430_CONTROL_CONF_DPLL_IDLE_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_dpllctrl_plllock_sel = {
	"CONTROL_CONF_DPLLCTRL_PLLLOCK_SEL",
	OMAP5430_CONTROL_CONF_DPLLCTRL_PLLLOCK_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_dpllctrl_pllrecal_sel = {
	"CONTROL_CONF_DPLLCTRL_PLLRECAL_SEL",
	OMAP5430_CONTROL_CONF_DPLLCTRL_PLLRECAL_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_dpllctrl_stopclock_sel = {
	"CONTROL_CONF_DPLLCTRL_STOPCLOCK_SEL",
	OMAP5430_CONTROL_CONF_DPLLCTRL_STOPCLOCK_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_dpllctrl_stopclockackz_sel = {
	"CONTROL_CONF_DPLLCTRL_STOPCLOCKACKZ_SEL",
	OMAP5430_CONTROL_CONF_DPLLCTRL_STOPCLOCKACKZ_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_dpllctrl_dispcupdatesync_sel = {
	"CONTROL_CONF_DPLLCTRL_DISPCUPDATESYNC_SEL",
	OMAP5430_CONTROL_CONF_DPLLCTRL_DISPCUPDATESYNC_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_dpllctrl_scpenpllctrl_sel = {
	"CONTROL_CONF_DPLLCTRL_SCPENPLLCTRL_SEL",
	OMAP5430_CONTROL_CONF_DPLLCTRL_SCPENPLLCTRL_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_dpllctrl_scpcmd1_sel = {
	"CONTROL_CONF_DPLLCTRL_SCPCMD1_SEL",
	OMAP5430_CONTROL_CONF_DPLLCTRL_SCPCMD1_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_dpllctrl_scpcmd0_sel = {
	"CONTROL_CONF_DPLLCTRL_SCPCMD0_SEL",
	OMAP5430_CONTROL_CONF_DPLLCTRL_SCPCMD0_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_dpllctrl_scpaddr3_sel = {
	"CONTROL_CONF_DPLLCTRL_SCPADDR3_SEL",
	OMAP5430_CONTROL_CONF_DPLLCTRL_SCPADDR3_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_dpllctrl_scpaddr2_sel = {
	"CONTROL_CONF_DPLLCTRL_SCPADDR2_SEL",
	OMAP5430_CONTROL_CONF_DPLLCTRL_SCPADDR2_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_dpllctrl_scpaddr1_sel = {
	"CONTROL_CONF_DPLLCTRL_SCPADDR1_SEL",
	OMAP5430_CONTROL_CONF_DPLLCTRL_SCPADDR1_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_dpllctrl_scpaddr0_sel = {
	"CONTROL_CONF_DPLLCTRL_SCPADDR0_SEL",
	OMAP5430_CONTROL_CONF_DPLLCTRL_SCPADDR0_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_dpllctrl_scpout_sel = {
	"CONTROL_CONF_DPLLCTRL_SCPOUT_SEL",
	OMAP5430_CONTROL_CONF_DPLLCTRL_SCPOUT_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_dpllctrl_scpinpllctrl_sel = {
	"CONTROL_CONF_DPLLCTRL_SCPINPLLCTRL_SEL",
	OMAP5430_CONTROL_CONF_DPLLCTRL_SCPINPLLCTRL_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_dpllctrl_scpbusy_sel = {
	"CONTROL_CONF_DPLLCTRL_SCPBUSY_SEL",
	OMAP5430_CONTROL_CONF_DPLLCTRL_SCPBUSY_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_mmcx_adpidle_sel = {
	"CONTROL_CONF_MMCX_ADPIDLE_SEL",
	OMAP5430_CONTROL_CONF_MMCX_ADPIDLE_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_mmcx_adpdat1paden_sel = {
	"CONTROL_CONF_MMCX_ADPDAT1PADEN_SEL",
	OMAP5430_CONTROL_CONF_MMCX_ADPDAT1PADEN_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_mmcx_ocpl4idlereq_sel = {
	"CONTROL_CONF_MMCX_OCPL4IDLEREQ_SEL",
	OMAP5430_CONTROL_CONF_MMCX_OCPL4IDLEREQ_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_mmcx_ocpl3mwait_sel = {
	"CONTROL_CONF_MMCX_OCPL3MWAIT_SEL",
	OMAP5430_CONTROL_CONF_MMCX_OCPL3MWAIT_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_mmcx_pirffret_sel = {
	"CONTROL_CONF_MMCX_PIRFFRET_SEL",
	OMAP5430_CONTROL_CONF_MMCX_PIRFFRET_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_mmcx_ocpl4sidleacko1_sel = {
	"CONTROL_CONF_MMCX_OCPL4SIDLEACKO1_SEL",
	OMAP5430_CONTROL_CONF_MMCX_OCPL4SIDLEACKO1_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_mmcx_ocpl4sidleacko0_sel = {
	"CONTROL_CONF_MMCX_OCPL4SIDLEACKO0_SEL",
	OMAP5430_CONTROL_CONF_MMCX_OCPL4SIDLEACKO0_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_mmcx_ocpl3mstandbyo_sel = {
	"CONTROL_CONF_MMCX_OCPL3MSTANDBYO_SEL",
	OMAP5430_CONTROL_CONF_MMCX_OCPL3MSTANDBYO_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_conf_mmcx_swakeup_sel = {
	"CONTROL_CONF_MMCX_SWAKEUP_SEL",
	OMAP5430_CONTROL_CONF_MMCX_SWAKEUP_SEL,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_0 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_0",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_0,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_1 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_1",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_1,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_2 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_2",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_2,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_3 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_3",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_3,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_4 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_4",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_4,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_5 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_5",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_5,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_6 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_6",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_6,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_7 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_7",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_7,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_8 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_8",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_8,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_9 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_9",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_9,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_10 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_10",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_10,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_11 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_11",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_11,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_12 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_12",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_12,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_13 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_13",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_13,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_14 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_14",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_14,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_15 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_15",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_15,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_16 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_16",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_16,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_17 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_17",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_17,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_18 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_18",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_18,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_19 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_19",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_19,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_20 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_20",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_20,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_21 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_21",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_21,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_22 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_22",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_22,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_23 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_23",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_23,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_24 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_24",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_24,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_25 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_25",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_25,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_26 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_26",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_26,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_27 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_27",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_27,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_28 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_28",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_28,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_29 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_29",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_29,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_30 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_30",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_30,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_31 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_31",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_31,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_32 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_32",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_32,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_33 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_33",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_33,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_34 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_34",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_34,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_35 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_35",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_35,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_36 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_36",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_36,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_37 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_37",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_37,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_38 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_38",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_38,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_39 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_39",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_39,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_40 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_40",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_40,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_41 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_41",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_41,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_42 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_42",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_42,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_43 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_43",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_43,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_44 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_44",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_44,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_45 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_45",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_45,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_46 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_46",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_46,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_debug_sel_tst_47 = {
	"CONTROL_CORE_CONF_DEBUG_SEL_TST_47",
	OMAP5430_CONTROL_CORE_CONF_DEBUG_SEL_TST_47,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_xbar_sel_0 = {
	"CONTROL_CORE_CONF_XBAR_SEL_0",
	OMAP5430_CONTROL_CORE_CONF_XBAR_SEL_0,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_xbar_sel_4 = {
	"CONTROL_CORE_CONF_XBAR_SEL_4",
	OMAP5430_CONTROL_CORE_CONF_XBAR_SEL_4,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_xbar_sel_8 = {
	"CONTROL_CORE_CONF_XBAR_SEL_8",
	OMAP5430_CONTROL_CORE_CONF_XBAR_SEL_8,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_xbar_sel_12 = {
	"CONTROL_CORE_CONF_XBAR_SEL_12",
	OMAP5430_CONTROL_CORE_CONF_XBAR_SEL_12,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_xbar_sel_16 = {
	"CONTROL_CORE_CONF_XBAR_SEL_16",
	OMAP5430_CONTROL_CORE_CONF_XBAR_SEL_16,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_xbar_sel_20 = {
	"CONTROL_CORE_CONF_XBAR_SEL_20",
	OMAP5430_CONTROL_CORE_CONF_XBAR_SEL_20,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_xbar_sel_24 = {
	"CONTROL_CORE_CONF_XBAR_SEL_24",
	OMAP5430_CONTROL_CORE_CONF_XBAR_SEL_24,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_xbar_sel_28 = {
	"CONTROL_CORE_CONF_XBAR_SEL_28",
	OMAP5430_CONTROL_CORE_CONF_XBAR_SEL_28,
	0xDEADBEEF,
	0};

reg omap5430_control_core_conf_xbar_bypass = {
	"CONTROL_CORE_CONF_XBAR_BYPASS",
	OMAP5430_CONTROL_CORE_CONF_XBAR_BYPASS,
	0xDEADBEEF,
	0};

reg *omap5430es1_ctrl_module_core_mod[OMAP5430ES1_CTRL_MODULE_CORE_MOD_REGCOUNT + 1] = {
	&omap5430_control_core_revision,
	&omap5430_control_core_hwinfo,
	&omap5430_control_core_sysconfig,
	&omap5430_control_l3_hw_fw_exported_values_conf_dbg,
	&omap5430_control_l3_hw_fw_exported_values_conf_func,
	&omap5430_control_status,
	&omap5430_control_forcewrnp,
	&omap5430_control_std_fuse_opp_vdd_mm_0,
	&omap5430_control_std_fuse_opp_vdd_mm_1,
	&omap5430_control_std_fuse_opp_vdd_mm_2,
	&omap5430_control_std_fuse_opp_vdd_mm_3,
	&omap5430_control_std_fuse_opp_vdd_mm_4,
	&omap5430_control_std_fuse_opp_vdd_mm_5,
	&omap5430_control_std_fuse_opp_vdd_mpu_0,
	&omap5430_control_std_fuse_opp_vdd_mpu_1,
	&omap5430_control_std_fuse_opp_vdd_mpu_2,
	&omap5430_control_std_fuse_opp_vdd_mpu_3,
	&omap5430_control_std_fuse_opp_vdd_mpu_4,
	&omap5430_control_std_fuse_opp_vdd_mpu_5,
	&omap5430_control_std_fuse_opp_vdd_mpu_6,
	&omap5430_control_std_fuse_opp_vdd_mpu_7,
	&omap5430_control_std_fuse_opp_vdd_core_0,
	&omap5430_control_std_fuse_opp_vdd_core_1,
	&omap5430_control_std_fuse_opp_vdd_core_2,
	&omap5430_control_std_fuse_opp_vdd_core_3,
	&omap5430_control_std_fuse_opp_vdd_core_4,
	&omap5430_control_std_fuse_opp_bgap_mm,
	&omap5430_control_std_fuse_opp_bgap_mpu,
	&omap5430_control_std_fuse_opp_bgap_core,
	&omap5430_control_std_fuse_die_id_0,
	&omap5430_control_std_fuse_die_id_1,
	&omap5430_control_std_fuse_die_id_2,
	&omap5430_control_std_fuse_die_id_3,
	&omap5430_control_std_fuse_prod_id,
	&omap5430_control_std_fuse_conf_id_0,
	&omap5430_control_std_fuse_conf_id_1,
	&omap5430_control_std_fuse_mpk_0,
	&omap5430_control_std_fuse_mpk_1,
	&omap5430_control_std_fuse_mpk_2,
	&omap5430_control_std_fuse_mpk_3,
	&omap5430_control_std_fuse_mpk_4,
	&omap5430_control_std_fuse_mpk_5,
	&omap5430_control_std_fuse_mpk_6,
	&omap5430_control_std_fuse_mpk_7,
	&omap5430_control_std_fuse_opp_vdd_mm_lvt_0,
	&omap5430_control_std_fuse_opp_vdd_mm_lvt_1,
	&omap5430_control_std_fuse_opp_vdd_mm_lvt_2,
	&omap5430_control_std_fuse_opp_vdd_mm_lvt_3,
	&omap5430_control_std_fuse_opp_vdd_mm_lvt_4,
	&omap5430_control_std_fuse_opp_vdd_mm_lvt_5,
	&omap5430_control_std_fuse_opp_vdd_mpu_lvt_0,
	&omap5430_control_std_fuse_opp_vdd_mpu_lvt_1,
	&omap5430_control_std_fuse_opp_vdd_mpu_lvt_2,
	&omap5430_control_std_fuse_opp_vdd_mpu_lvt_3,
	&omap5430_control_std_fuse_opp_vdd_mpu_lvt_4,
	&omap5430_control_std_fuse_opp_vdd_mpu_lvt_5,
	&omap5430_control_std_fuse_opp_vdd_mpu_lvt_6,
	&omap5430_control_std_fuse_opp_vdd_mpu_lvt_7,
	&omap5430_control_cust_fuse_swrv_0,
	&omap5430_control_cust_fuse_swrv_1,
	&omap5430_control_cust_fuse_swrv_2,
	&omap5430_control_cust_fuse_swrv_3,
	&omap5430_control_cust_fuse_swrv_4,
	&omap5430_control_cust_fuse_swrv_5,
	&omap5430_control_cust_fuse_swrv_6,
	&omap5430_control_dev_conf,
	&omap5430_control_dsp_bootaddr,
	&omap5430_control_temp_sensor_mpu,
	&omap5430_control_temp_sensor_mm,
	&omap5430_control_temp_sensor_core,
	&omap5430_control_ldosram_mpu_lvt_voltage_ctrl,
	&omap5430_control_cortex_m4_mmuaddrtransltr,
	&omap5430_control_cortex_m4_mmuaddrlogictr,
	&omap5430_control_hwobs_control,
	&omap5430_control_pcs1,
	&omap5430_control_pcs2,
	&omap5430_control_pcs_revision,
	&omap5430_control_phy_power_usb,
	&omap5430_control_phy_power_sata,
	&omap5430_control_slimbus_keeper,
	&omap5430_control_phy_sel,
	&omap5430_control_bandgap_mask,
	&omap5430_control_bandgap_threshold_mpu,
	&omap5430_control_bandgap_threshold_mm,
	&omap5430_control_bandgap_threshold_core,
	&omap5430_control_bandgap_tshut_mpu,
	&omap5430_control_bandgap_tshut_mm,
	&omap5430_control_bandgap_tshut_core,
	&omap5430_control_bandgap_counter_mpu,
	&omap5430_control_bandgap_counter_mm,
	&omap5430_control_bandgap_counter_core,
	&omap5430_control_bandgap_status,
	&omap5430_control_sata_ext_mode,
	&omap5430_control_ocpreg_spare,
	&omap5430_control_debobs_final_mux_sel,
	&omap5430_control_debobs_ocpwp_sys_event_sel,
	&omap5430_control_debobs_mmr_mpu,
	&omap5430_control_conf_mdma_req_sel0,
	&omap5430_control_conf_mdma_req_sel1,
	&omap5430_control_conf_mdma_req_sel2,
	&omap5430_control_conf_mdma_req_sel3,
	&omap5430_control_conf_mdma_req_sel4,
	&omap5430_control_conf_mdma_req_sel5,
	&omap5430_control_conf_sdma_req_sel0,
	&omap5430_control_conf_sdma_req_sel1,
	&omap5430_control_conf_sdma_req_sel2,
	&omap5430_control_conf_sdma_req_sel3,
	&omap5430_control_conf_clk_sel0,
	&omap5430_control_conf_clk_sel1,
	&omap5430_control_conf_clk_sel2,
	&omap5430_control_conf_dpll_freqlock_sel,
	&omap5430_control_conf_dpll_tinitz_sel,
	&omap5430_control_conf_dpll_phaselock_sel,
	&omap5430_control_conf_dpll_tenable_sel,
	&omap5430_control_conf_dpll_tenablediv_sel,
	&omap5430_control_conf_dpll_bypassack_sel,
	&omap5430_control_conf_dpll_idle_sel,
	&omap5430_control_conf_dpllctrl_plllock_sel,
	&omap5430_control_conf_dpllctrl_pllrecal_sel,
	&omap5430_control_conf_dpllctrl_stopclock_sel,
	&omap5430_control_conf_dpllctrl_stopclockackz_sel,
	&omap5430_control_conf_dpllctrl_dispcupdatesync_sel,
	&omap5430_control_conf_dpllctrl_scpenpllctrl_sel,
	&omap5430_control_conf_dpllctrl_scpcmd1_sel,
	&omap5430_control_conf_dpllctrl_scpcmd0_sel,
	&omap5430_control_conf_dpllctrl_scpaddr3_sel,
	&omap5430_control_conf_dpllctrl_scpaddr2_sel,
	&omap5430_control_conf_dpllctrl_scpaddr1_sel,
	&omap5430_control_conf_dpllctrl_scpaddr0_sel,
	&omap5430_control_conf_dpllctrl_scpout_sel,
	&omap5430_control_conf_dpllctrl_scpinpllctrl_sel,
	&omap5430_control_conf_dpllctrl_scpbusy_sel,
	&omap5430_control_conf_mmcx_adpidle_sel,
	&omap5430_control_conf_mmcx_adpdat1paden_sel,
	&omap5430_control_conf_mmcx_ocpl4idlereq_sel,
	&omap5430_control_conf_mmcx_ocpl3mwait_sel,
	&omap5430_control_conf_mmcx_pirffret_sel,
	&omap5430_control_conf_mmcx_ocpl4sidleacko1_sel,
	&omap5430_control_conf_mmcx_ocpl4sidleacko0_sel,
	&omap5430_control_conf_mmcx_ocpl3mstandbyo_sel,
	&omap5430_control_conf_mmcx_swakeup_sel,
	&omap5430_control_core_conf_debug_sel_tst_0,
	&omap5430_control_core_conf_debug_sel_tst_1,
	&omap5430_control_core_conf_debug_sel_tst_2,
	&omap5430_control_core_conf_debug_sel_tst_3,
	&omap5430_control_core_conf_debug_sel_tst_4,
	&omap5430_control_core_conf_debug_sel_tst_5,
	&omap5430_control_core_conf_debug_sel_tst_6,
	&omap5430_control_core_conf_debug_sel_tst_7,
	&omap5430_control_core_conf_debug_sel_tst_8,
	&omap5430_control_core_conf_debug_sel_tst_9,
	&omap5430_control_core_conf_debug_sel_tst_10,
	&omap5430_control_core_conf_debug_sel_tst_11,
	&omap5430_control_core_conf_debug_sel_tst_12,
	&omap5430_control_core_conf_debug_sel_tst_13,
	&omap5430_control_core_conf_debug_sel_tst_14,
	&omap5430_control_core_conf_debug_sel_tst_15,
	&omap5430_control_core_conf_debug_sel_tst_16,
	&omap5430_control_core_conf_debug_sel_tst_17,
	&omap5430_control_core_conf_debug_sel_tst_18,
	&omap5430_control_core_conf_debug_sel_tst_19,
	&omap5430_control_core_conf_debug_sel_tst_20,
	&omap5430_control_core_conf_debug_sel_tst_21,
	&omap5430_control_core_conf_debug_sel_tst_22,
	&omap5430_control_core_conf_debug_sel_tst_23,
	&omap5430_control_core_conf_debug_sel_tst_24,
	&omap5430_control_core_conf_debug_sel_tst_25,
	&omap5430_control_core_conf_debug_sel_tst_26,
	&omap5430_control_core_conf_debug_sel_tst_27,
	&omap5430_control_core_conf_debug_sel_tst_28,
	&omap5430_control_core_conf_debug_sel_tst_29,
	&omap5430_control_core_conf_debug_sel_tst_30,
	&omap5430_control_core_conf_debug_sel_tst_31,
	&omap5430_control_core_conf_debug_sel_tst_32,
	&omap5430_control_core_conf_debug_sel_tst_33,
	&omap5430_control_core_conf_debug_sel_tst_34,
	&omap5430_control_core_conf_debug_sel_tst_35,
	&omap5430_control_core_conf_debug_sel_tst_36,
	&omap5430_control_core_conf_debug_sel_tst_37,
	&omap5430_control_core_conf_debug_sel_tst_38,
	&omap5430_control_core_conf_debug_sel_tst_39,
	&omap5430_control_core_conf_debug_sel_tst_40,
	&omap5430_control_core_conf_debug_sel_tst_41,
	&omap5430_control_core_conf_debug_sel_tst_42,
	&omap5430_control_core_conf_debug_sel_tst_43,
	&omap5430_control_core_conf_debug_sel_tst_44,
	&omap5430_control_core_conf_debug_sel_tst_45,
	&omap5430_control_core_conf_debug_sel_tst_46,
	&omap5430_control_core_conf_debug_sel_tst_47,
	NULL};

reg *omap5430_ctrl_module_core_mod[OMAP5430_CTRL_MODULE_CORE_MOD_REGCOUNT + 1] = {
	&omap5430_control_core_revision,
	&omap5430_control_core_hwinfo,
	&omap5430_control_core_sysconfig,
	&omap5430_control_status,
	&omap5430_control_sec_err_status_func,
	&omap5430_control_sec_err_status_debug,
	&omap5430_control_forcewrnp,
	&omap5430_control_std_fuse_opp_vdd_mm_0,
	&omap5430_control_std_fuse_opp_vdd_mm_1,
	&omap5430_control_std_fuse_opp_vdd_mm_2,
	&omap5430_control_std_fuse_opp_vdd_mm_3,
	&omap5430_control_std_fuse_opp_vdd_mm_4,
	&omap5430_control_std_fuse_opp_vdd_mm_5,
	&omap5430_control_std_fuse_opp_vdd_mpu_0,
	&omap5430_control_std_fuse_opp_vdd_mpu_1,
	&omap5430_control_std_fuse_opp_vdd_mpu_2,
	&omap5430_control_std_fuse_opp_vdd_mpu_3,
	&omap5430_control_std_fuse_opp_vdd_mpu_4,
	&omap5430_control_std_fuse_opp_vdd_mpu_5,
	&omap5430_control_std_fuse_opp_vdd_mpu_6,
	&omap5430_control_std_fuse_opp_vdd_mpu_7,
	&omap5430_control_std_fuse_opp_vdd_core_0,
	&omap5430_control_std_fuse_opp_vdd_core_1,
	&omap5430_control_std_fuse_opp_vdd_core_2,
	&omap5430_control_std_fuse_opp_vdd_core_3,
	&omap5430_control_std_fuse_opp_vdd_core_4,
	&omap5430_control_std_fuse_opp_bgap_mm,
	&omap5430_control_std_fuse_opp_bgap_mpu,
	&omap5430_control_std_fuse_opp_bgap_core,
	&omap5430_control_std_fuse_opp_bgap_mpu23,
	&omap5430_control_std_fuse_die_id_0,
	&omap5430_control_std_fuse_die_id_1,
	&omap5430_control_std_fuse_die_id_2,
	&omap5430_control_std_fuse_die_id_3,
	&omap5430_control_std_fuse_prod_id,
	&omap5430_control_std_fuse_conf_id_0,
	&omap5430_control_std_fuse_conf_id_1,
	&omap5430_control_std_fuse_mpk_0,
	&omap5430_control_std_fuse_mpk_1,
	&omap5430_control_std_fuse_mpk_2,
	&omap5430_control_std_fuse_mpk_3,
	&omap5430_control_std_fuse_mpk_4,
	&omap5430_control_std_fuse_mpk_5,
	&omap5430_control_std_fuse_mpk_6,
	&omap5430_control_std_fuse_mpk_7,
	&omap5430_control_std_fuse_opp_vdd_mm_lvt_0,
	&omap5430_control_std_fuse_opp_vdd_mm_lvt_1,
	&omap5430_control_std_fuse_opp_vdd_mm_lvt_2,
	&omap5430_control_std_fuse_opp_vdd_mm_lvt_3,
	&omap5430_control_std_fuse_opp_vdd_mm_lvt_4,
	&omap5430_control_std_fuse_opp_vdd_mm_lvt_5,
	&omap5430_control_std_fuse_opp_vdd_mpu_lvt_0,
	&omap5430_control_std_fuse_opp_vdd_mpu_lvt_1,
	&omap5430_control_std_fuse_opp_vdd_mpu_lvt_2,
	&omap5430_control_std_fuse_opp_vdd_mpu_lvt_3,
	&omap5430_control_std_fuse_opp_vdd_mpu_lvt_4,
	&omap5430_control_std_fuse_opp_vdd_mpu_lvt_5,
	&omap5430_control_std_fuse_opp_vdd_mpu_lvt_6,
	&omap5430_control_std_fuse_opp_vdd_mpu_lvt_7,
	&omap5430_control_cust_fuse_swrv_0,
	&omap5430_control_cust_fuse_swrv_1,
	&omap5430_control_cust_fuse_swrv_2,
	&omap5430_control_cust_fuse_swrv_3,
	&omap5430_control_cust_fuse_swrv_4,
	&omap5430_control_cust_fuse_swrv_5,
	&omap5430_control_cust_fuse_swrv_6,
	&omap5430_control_hwobsdivider1,
	&omap5430_control_hwobsdivider2,
	&omap5430_control_breg_selection,
	&omap5430_control_dpll_bclk,
	&omap5430_control_dpll_baddr_bdataw,
	&omap5430_control_dpll_bdatar,
	&omap5430_control_dev_conf,
	&omap5430_control_dsp_bootaddr,
	&omap5430_control_temp_sensor_mpu,
	&omap5430_control_temp_sensor_mm,
	&omap5430_control_temp_sensor_core,
	&omap5430_control_ldosram_mpu_lvt_voltage_ctrl,
	&omap5430_control_cortex_m4_mmuaddrtransltr,
	&omap5430_control_cortex_m4_mmuaddrlogictr,
	&omap5430_control_hwobs_control,
	&omap5430_control_pcs1,
	&omap5430_control_pcs2,
	&omap5430_control_pcs_revision,
	&omap5430_control_phy_power_usb,
	&omap5430_control_phy_power_sata,
	&omap5430_control_slimbus_keeper,
	&omap5430_control_phy_sel,
	&omap5430_control_bandgap_mask,
	&omap5430_control_bandgap_threshold_mpu,
	&omap5430_control_bandgap_threshold_mm,
	&omap5430_control_bandgap_threshold_core,
	&omap5430_control_bandgap_tshut_mpu,
	&omap5430_control_bandgap_tshut_mm,
	&omap5430_control_bandgap_tshut_core,
	&omap5430_control_bandgap_cumul_dtemp_mpu,
	&omap5430_control_bandgap_cumul_dtemp_mm,
	&omap5430_control_bandgap_cumul_dtemp_core,
	&omap5430_control_bandgap_status,
	&omap5430_control_sata_ext_mode,
	&omap5430_control_dtemp_mpu_0,
	&omap5430_control_dtemp_mpu_1,
	&omap5430_control_dtemp_mpu_2,
	&omap5430_control_dtemp_mpu_3,
	&omap5430_control_dtemp_mpu_4,
	&omap5430_control_dtemp_mm_0,
	&omap5430_control_dtemp_mm_1,
	&omap5430_control_dtemp_mm_2,
	&omap5430_control_dtemp_mm_3,
	&omap5430_control_dtemp_mm_4,
	&omap5430_control_dtemp_core_0,
	&omap5430_control_dtemp_core_1,
	&omap5430_control_dtemp_core_2,
	&omap5430_control_dtemp_core_3,
	&omap5430_control_dtemp_core_4,
	&omap5430_control_ocpreg_spare,
	&omap5430_control_debobs_final_mux_sel,
	&omap5430_control_debobs_ocpwp_sys_event_sel,
	&omap5430_control_debobs_mmr_mpu,
	&omap5430_control_conf_sdma_req_sel0,
	&omap5430_control_conf_sdma_req_sel1,
	&omap5430_control_conf_sdma_req_sel2,
	&omap5430_control_conf_sdma_req_sel3,
	&omap5430_control_conf_clk_sel0,
	&omap5430_control_conf_clk_sel1,
	&omap5430_control_conf_clk_sel2,
	&omap5430_control_conf_dpll_freqlock_sel,
	&omap5430_control_conf_dpll_tinitz_sel,
	&omap5430_control_conf_dpll_phaselock_sel,
	&omap5430_control_conf_dpll_tenable_sel,
	&omap5430_control_conf_dpll_tenablediv_sel,
	&omap5430_control_conf_dpll_bypassack_sel,
	&omap5430_control_conf_dpll_idle_sel,
	&omap5430_control_conf_dpllctrl_plllock_sel,
	&omap5430_control_conf_dpllctrl_pllrecal_sel,
	&omap5430_control_conf_dpllctrl_stopclock_sel,
	&omap5430_control_conf_dpllctrl_stopclockackz_sel,
	&omap5430_control_conf_dpllctrl_dispcupdatesync_sel,
	&omap5430_control_conf_mmcx_adpidle_sel,
	&omap5430_control_conf_mmcx_adpdat1paden_sel,
	&omap5430_control_conf_mmcx_ocpl4idlereq_sel,
	&omap5430_control_conf_mmcx_ocpl3mwait_sel,
	&omap5430_control_conf_mmcx_pirffret_sel,
	&omap5430_control_conf_mmcx_ocpl4sidleacko1_sel,
	&omap5430_control_conf_mmcx_ocpl4sidleacko0_sel,
	&omap5430_control_conf_mmcx_ocpl3mstandbyo_sel,
	&omap5430_control_conf_mmcx_swakeup_sel,
	&omap5430_control_core_conf_debug_sel_tst_0,
	&omap5430_control_core_conf_debug_sel_tst_1,
	&omap5430_control_core_conf_debug_sel_tst_2,
	&omap5430_control_core_conf_debug_sel_tst_3,
	&omap5430_control_core_conf_debug_sel_tst_4,
	&omap5430_control_core_conf_debug_sel_tst_5,
	&omap5430_control_core_conf_debug_sel_tst_6,
	&omap5430_control_core_conf_debug_sel_tst_7,
	&omap5430_control_core_conf_debug_sel_tst_8,
	&omap5430_control_core_conf_debug_sel_tst_9,
	&omap5430_control_core_conf_debug_sel_tst_10,
	&omap5430_control_core_conf_debug_sel_tst_11,
	&omap5430_control_core_conf_debug_sel_tst_12,
	&omap5430_control_core_conf_debug_sel_tst_13,
	&omap5430_control_core_conf_debug_sel_tst_14,
	&omap5430_control_core_conf_debug_sel_tst_15,
	&omap5430_control_core_conf_debug_sel_tst_16,
	&omap5430_control_core_conf_debug_sel_tst_17,
	&omap5430_control_core_conf_debug_sel_tst_18,
	&omap5430_control_core_conf_debug_sel_tst_19,
	&omap5430_control_core_conf_debug_sel_tst_20,
	&omap5430_control_core_conf_debug_sel_tst_21,
	&omap5430_control_core_conf_debug_sel_tst_22,
	&omap5430_control_core_conf_debug_sel_tst_23,
	&omap5430_control_core_conf_debug_sel_tst_24,
	&omap5430_control_core_conf_debug_sel_tst_25,
	&omap5430_control_core_conf_debug_sel_tst_26,
	&omap5430_control_core_conf_debug_sel_tst_27,
	&omap5430_control_core_conf_debug_sel_tst_28,
	&omap5430_control_core_conf_debug_sel_tst_29,
	&omap5430_control_core_conf_debug_sel_tst_30,
	&omap5430_control_core_conf_debug_sel_tst_31,
	&omap5430_control_core_conf_debug_sel_tst_32,
	&omap5430_control_core_conf_debug_sel_tst_33,
	&omap5430_control_core_conf_debug_sel_tst_34,
	&omap5430_control_core_conf_debug_sel_tst_35,
	&omap5430_control_core_conf_debug_sel_tst_36,
	&omap5430_control_core_conf_debug_sel_tst_37,
	&omap5430_control_core_conf_debug_sel_tst_38,
	&omap5430_control_core_conf_debug_sel_tst_39,
	&omap5430_control_core_conf_debug_sel_tst_40,
	&omap5430_control_core_conf_debug_sel_tst_41,
	&omap5430_control_core_conf_debug_sel_tst_42,
	&omap5430_control_core_conf_debug_sel_tst_43,
	&omap5430_control_core_conf_debug_sel_tst_44,
	&omap5430_control_core_conf_debug_sel_tst_45,
	&omap5430_control_core_conf_debug_sel_tst_46,
	&omap5430_control_core_conf_debug_sel_tst_47,
	&omap5430_control_core_conf_xbar_sel_0,
	&omap5430_control_core_conf_xbar_sel_4,
	&omap5430_control_core_conf_xbar_sel_8,
	&omap5430_control_core_conf_xbar_sel_12,
	&omap5430_control_core_conf_xbar_sel_16,
	&omap5430_control_core_conf_xbar_sel_20,
	&omap5430_control_core_conf_xbar_sel_24,
	&omap5430_control_core_conf_xbar_sel_28,
	&omap5430_control_core_conf_xbar_bypass,
	NULL};
