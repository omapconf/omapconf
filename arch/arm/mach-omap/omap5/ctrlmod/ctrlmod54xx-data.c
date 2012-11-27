/*
 *
 * @Component			OMAPCONF
 * @Filename			ctrlmod54xx-data.c
 * @Description			OMAP5 CONTROL MODULE Register Golden Values
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


#include <ctrlmod54xx-data.h>
#include <lib.h>


const ctrlmod54xx_golden_item ctrlmod_core54xxes1_golden_values[OMAP5430ES1_CTRL_MODULE_CORE_MOD_REGCOUNT] = {
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_revision */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_hwinfo */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_sysconfig */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_l3_hw_fw_exported_values_conf_dbg */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_l3_hw_fw_exported_values_conf_func */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_status */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_forcewrnp */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_mm_0 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_mm_1 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_mm_2 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_mm_3 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_mm_4 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_mm_5 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_mpu_0 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_mpu_1 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_mpu_2 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_mpu_3 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_mpu_4 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_mpu_5 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_mpu_6 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_mpu_7 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_core_0 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_core_1 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_core_2 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_core_3 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_core_4 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_bgap_mm */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_bgap_mpu */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_bgap_core */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_die_id_0 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_die_id_1 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_die_id_2 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_die_id_3 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_prod_id */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_conf_id_0 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_conf_id_1 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_mpk_0 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_mpk_1 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_mpk_2 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_mpk_3 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_mpk_4 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_mpk_5 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_mpk_6 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_mpk_7 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_mm_lvt_0 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_mm_lvt_1 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_mm_lvt_2 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_mm_lvt_3 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_mm_lvt_4 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_mm_lvt_5 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_mpu_lvt_0 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_mpu_lvt_1 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_mpu_lvt_2 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_mpu_lvt_3 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_mpu_lvt_4 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_mpu_lvt_5 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_mpu_lvt_6 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_opp_vdd_mpu_lvt_7 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_cust_fuse_swrv_0 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_cust_fuse_swrv_1 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_cust_fuse_swrv_2 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_cust_fuse_swrv_3 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_cust_fuse_swrv_4 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_cust_fuse_swrv_5 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_cust_fuse_swrv_6 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_dev_conf */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_dsp_bootaddr */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_temp_sensor_mpu */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_temp_sensor_mm */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_temp_sensor_core */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_ldosram_mpu_lvt_voltage_ctrl */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_cortex_m4_mmuaddrtransltr */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_cortex_m4_mmuaddrlogictr */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_hwobs_control */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_pcs1 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_pcs2 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_pcs_revision */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_phy_power_usb */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_phy_power_sata */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_slimbus_keeper */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_phy_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_bandgap_mask */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_bandgap_threshold_mpu */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_bandgap_threshold_mm */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_bandgap_threshold_core */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_bandgap_tshut_mpu */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_bandgap_tshut_mm */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_bandgap_tshut_core */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_bandgap_counter_mpu */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_bandgap_counter_mm */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_bandgap_counter_core */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_bandgap_status */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_sata_ext_mode */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_ocpreg_spare */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_debobs_final_mux_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_debobs_ocpwp_sys_event_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_debobs_mmr_mpu */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_mdma_req_sel0 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_mdma_req_sel1 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_mdma_req_sel2 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_mdma_req_sel3 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_mdma_req_sel4 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_mdma_req_sel5 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_sdma_req_sel0 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_sdma_req_sel1 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_sdma_req_sel2 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_sdma_req_sel3 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_clk_sel0 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_clk_sel1 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_clk_sel2 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_dpll_freqlock_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_dpll_tinitz_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_dpll_phaselock_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_dpll_tenable_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_dpll_tenablediv_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_dpll_bypassack_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_dpll_idle_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_dpllctrl_plllock_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_dpllctrl_pllrecal_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_dpllctrl_stopclock_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_dpllctrl_stopclockackz_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_dpllctrl_dispcupdatesync_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_dpllctrl_scpenpllctrl_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_dpllctrl_scpcmd1_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_dpllctrl_scpcmd0_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_dpllctrl_scpaddr3_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_dpllctrl_scpaddr2_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_dpllctrl_scpaddr1_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_dpllctrl_scpaddr0_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_dpllctrl_scpout_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_dpllctrl_scpinpllctrl_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_dpllctrl_scpbusy_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_mmcx_adpidle_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_mmcx_adpdat1paden_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_mmcx_ocpl4idlereq_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_mmcx_ocpl3mwait_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_mmcx_pirffret_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_mmcx_ocpl4sidleacko1_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_mmcx_ocpl4sidleacko0_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_mmcx_ocpl3mstandbyo_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_conf_mmcx_swakeup_sel */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_0 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_1 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_2 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_3 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_4 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_5 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_6 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_7 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_8 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_9 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_10 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_11 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_12 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_13 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_14 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_15 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_16 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_17 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_18 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_19 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_20 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_21 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_22 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_23 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_24 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_25 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_26 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_27 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_28 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_29 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_30 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_31 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_32 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_33 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_34 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_35 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_36 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_37 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_38 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_39 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_40 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_41 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_42 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_43 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_44 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_45 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_conf_debug_sel_tst_46 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF} }; /* omap5430_control_core_conf_debug_sel_tst_47 */ /* FIXME */


const ctrlmod54xx_golden_item ctrlmod_core_pad54xxes1_golden_values[OMAP5430_CTRL_MODULE_CORE_PAD_MOD_REGCOUNT] = {
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_pad_revision */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_pad_hwinfo */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_pad_sysconfig */
	{DATA_VALID, 0x01000000}, /* omap5430_control_core_pad0_emmc_clk_pad1_emmc_cmd */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_emmc_data0_pad1_emmc_data1 */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_emmc_data2_pad1_emmc_data3 */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_emmc_data4_pad1_emmc_data5 */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_emmc_data6_pad1_emmc_data7 */
	{DATA_VALID, 0x00000000}, /* omap5430_control_core_pad0_c2c_clkout0_pad1_c2c_clkout1 */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_c2c_clkin0_pad1_c2c_clkin1 */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_c2c_datain0_pad1_c2c_datain1 */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_c2c_datain2_pad1_c2c_datain3 */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_c2c_datain4_pad1_c2c_datain5 */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_c2c_datain6_pad1_c2c_datain7 */
	{DATA_VALID, 0x00000000}, /* omap5430_control_core_pad0_c2c_dataout0_pad1_c2c_dataout1 */
	{DATA_VALID, 0x00000000}, /* omap5430_control_core_pad0_c2c_dataout2_pad1_c2c_dataout3 */
	{DATA_VALID, 0x00000000}, /* omap5430_control_core_pad0_c2c_dataout4_pad1_c2c_dataout5 */
	{DATA_VALID, 0x00000000}, /* omap5430_control_core_pad0_c2c_dataout6_pad1_c2c_dataout7 */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_c2c_data8_pad1_c2c_data9 */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_c2c_data10_pad1_c2c_data11 */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_c2c_data12_pad1_c2c_data13 */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_c2c_data14_pad1_c2c_data15 */
	{DATA_VALID, 0x011E0001}, /* omap5430_control_core_pad0_llia_wakereqout_pad1_llib_wakereqout */
	{DATA_VALID, 0x000E000E}, /* omap5430_control_core_pad0_hsi1_acready_pad1_hsi1_caready */
	{DATA_VALID, 0x011E010E}, /* omap5430_control_core_pad0_hsi1_acwake_pad1_hsi1_cawake */
	{DATA_VALID, 0x000E010E}, /* omap5430_control_core_pad0_hsi1_acflag_pad1_hsi1_acdata */
	{DATA_VALID, 0x00060006}, /* omap5430_control_core_pad0_hsi1_caflag_pad1_hsi1_cadata */
	{DATA_VALID, 0x01180000}, /* omap5430_control_core_pad0_uart1_tx_pad1_uart1_cts */
	{DATA_VALID, 0x00000118}, /* omap5430_control_core_pad0_uart1_rx_pad1_uart1_rts */
	{DATA_VALID, 0x00000100}, /* omap5430_control_core_pad0_hsi2_caready_pad1_hsi2_acready */
	{DATA_VALID, 0x00000100}, /* omap5430_control_core_pad0_hsi2_cawake_pad1_hsi2_acwake */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_hsi2_caflag_pad1_hsi2_cadata */
	{DATA_VALID, 0x00000000}, /* omap5430_control_core_pad0_hsi2_acflag_pad1_hsi2_acdata */
	{DATA_VALID, 0x01010101}, /* omap5430_control_core_pad0_uart2_rts_pad1_uart2_cts */
	{DATA_VALID, 0x01010101}, /* omap5430_control_core_pad0_uart2_rx_pad1_uart2_tx */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_usbb1_hsic_strobe_pad1_usbb1_hsic_data */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_usbb2_hsic_strobe_pad1_usbb2_hsic_data */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_timer10_pwm_evt_pad1_dsiporta_te0 */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_dsiporta_lane0x_pad1_dsiporta_lane0y */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_dsiporta_lane1x_pad1_dsiporta_lane1y */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_dsiporta_lane2x_pad1_dsiporta_lane2y */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_dsiporta_lane3x_pad1_dsiporta_lane3y */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_dsiporta_lane4x_pad1_dsiporta_lane4y */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_dsiportc_lane0x_pad1_dsiportc_lane0y */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_dsiportc_lane1x_pad1_dsiportc_lane1y */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_dsiportc_lane2x_pad1_dsiportc_lane2y */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_dsiportc_lane3x_pad1_dsiportc_lane3y */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_dsiportc_lane4x_pad1_dsiportc_lane4y */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_dsiportc_te0_pad1_timer9_pwm_evt */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_i2c4_scl_pad1_i2c4_sda */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_mcspi2_clk_pad1_mcspi2_simo */
	{DATA_VALID, 0x00000118}, /* omap5430_control_core_pad0_mcspi2_somi_pad1_mcspi2_cs0 */
	{DATA_VALID, 0x00040004}, /* omap5430_control_core_pad0_rfbi_data15_pad1_rfbi_data14 */
	{DATA_VALID, 0x000E010E}, /* omap5430_control_core_pad0_rfbi_data13_pad1_rfbi_data12 */
	{DATA_VALID, 0x000E000E}, /* omap5430_control_core_pad0_rfbi_data11_pad1_rfbi_data10 */
	{DATA_VALID, 0x0004000E}, /* omap5430_control_core_pad0_rfbi_data9_pad1_rfbi_data8 */
	{DATA_VALID, 0x000E000E}, /* omap5430_control_core_pad0_rfbi_data7_pad1_rfbi_data6 */
	{DATA_VALID, 0x01060106}, /* omap5430_control_core_pad0_rfbi_data5_pad1_rfbi_data4 */
	{DATA_VALID, 0x000E010E}, /* omap5430_control_core_pad0_rfbi_data3_pad1_rfbi_data2 */
	{DATA_VALID, 0x000E000E}, /* omap5430_control_core_pad0_rfbi_data1_pad1_rfbi_data0 */
	{DATA_VALID, 0x010E000E}, /* omap5430_control_core_pad0_rfbi_we_pad1_rfbi_cs0 */
	{DATA_VALID, 0x0004010E}, /* omap5430_control_core_pad0_rfbi_a0_pad1_rfbi_re */
	{DATA_VALID, 0x000E0004}, /* omap5430_control_core_pad0_rfbi_hsync0_pad1_rfbi_te_vsync0 */
	{DATA_VALID, 0x000E0006}, /* omap5430_control_core_pad0_gpio6_182_pad1_gpio6_183 */
	{DATA_VALID, 0x010E0004}, /* omap5430_control_core_pad0_gpio6_184_pad1_gpio6_185 */
	{DATA_VALID, 0x0104000E}, /* omap5430_control_core_pad0_gpio6_186_pad1_gpio6_187 */
	{DATA_VALID, 0x01080100}, /* omap5430_control_core_pad0_hdmi_cec_pad1_hdmi_hpd */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_hdmi_ddc_scl_pad1_hdmi_ddc_sda */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_csiportc_lane0x_pad1_csiportc_lane0y */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_csiportc_lane1x_pad1_csiportc_lane1y */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_csiportb_lane0x_pad1_csiportb_lane0y */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_csiportb_lane1x_pad1_csiportb_lane1y */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_csiportb_lane2x_pad1_csiportb_lane2y */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_csiporta_lane0x_pad1_csiporta_lane0y */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_csiporta_lane1x_pad1_csiporta_lane1y */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_csiporta_lane2x_pad1_csiporta_lane2y */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_csiporta_lane3x_pad1_csiporta_lane3y */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_csiporta_lane4x_pad1_csiporta_lane4y */
	{DATA_VALID, 0x00000000}, /* omap5430_control_core_pad0_cam_shutter_pad1_cam_strobe */
	{DATA_VALID, 0x000E0100}, /* omap5430_control_core_pad0_cam_globalreset_pad1_timer11_pwm_evt */
	{DATA_VALID, 0x000E000E}, /* omap5430_control_core_pad0_timer5_pwm_evt_pad1_timer6_pwm_evt */
	{DATA_VALID, 0x0100000E}, /* omap5430_control_core_pad0_timer8_pwm_evt_pad1_i2c3_scl */
	{DATA_VALID, 0x01020100}, /* omap5430_control_core_pad0_i2c3_sda_pad1_gpio8_233 */
	{DATA_VALID, 0x01000001}, /* omap5430_control_core_pad0_gpio8_234_pad1_abe_clks */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_abedmic_din1_pad1_abedmic_din2 */
	{DATA_VALID, 0x00000100}, /* omap5430_control_core_pad0_abedmic_din3_pad1_abedmic_clk1 */
	{DATA_VALID, 0x00010101}, /* omap5430_control_core_pad0_abedmic_clk2_pad1_abedmic_clk3 */
	{DATA_VALID, 0x01010101}, /* omap5430_control_core_pad0_abeslimbus1_clock_pad1_abeslimbus1_data */
	{DATA_VALID, 0x00000100}, /* omap5430_control_core_pad0_abemcbsp2_dr_pad1_abemcbsp2_dx */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_abemcbsp2_fsx_pad1_abemcbsp2_clkx */
	{DATA_VALID, 0x00000100}, /* omap5430_control_core_pad0_abemcpdm_ul_data_pad1_abemcpdm_dl_data */
	{DATA_VALID, 0x00000100}, /* omap5430_control_core_pad0_abemcpdm_frame_pad1_abemcpdm_lb_clk */
	{DATA_VALID, 0x01000000}, /* omap5430_control_core_pad0_wlsdio_clk_pad1_wlsdio_cmd */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_wlsdio_data0_pad1_wlsdio_data1 */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_wlsdio_data2_pad1_wlsdio_data3 */
	{DATA_VALID, 0x00000118}, /* omap5430_control_core_pad0_uart5_rx_pad1_uart5_tx */
	{DATA_VALID, 0x00000118}, /* omap5430_control_core_pad0_uart5_cts_pad1_uart5_rts */
	{DATA_VALID, 0x01000100}, /* omap5430_control_core_pad0_i2c2_scl_pad1_i2c2_sda */
	{DATA_VALID, 0x0106000E}, /* omap5430_control_core_pad0_mcspi1_clk_pad1_mcspi1_somi */
	{DATA_VALID, 0x000E000E}, /* omap5430_control_core_pad0_mcspi1_simo_pad1_mcspi1_cs0 */
	{DATA_VALID, 0x0100010E}, /* omap5430_control_core_pad0_mcspi1_cs1_pad1_i2c5_scl */
	{DATA_VALID, 0x000E0100}, /* omap5430_control_core_pad0_i2c5_sda_pad1_perslimbus2_clock */
	{DATA_VALID, 0x011E010E}, /* omap5430_control_core_pad0_perslimbus2_data_pad1_uart6_tx */
	{DATA_VALID, 0x011E011E}, /* omap5430_control_core_pad0_uart6_rx_pad1_uart6_cts */
	{DATA_VALID, 0x011E0018}, /* omap5430_control_core_pad0_uart6_rts_pad1_uart3_cts_rctx */
	{DATA_VALID, 0x00000119}, /* omap5430_control_core_pad0_uart3_rts_irsd_pad1_uart3_tx_irtx */
	{DATA_VALID, 0x01000118}, /* omap5430_control_core_pad0_uart3_rx_irrx_pad1_usbb3_hsic_strobe */
	{DATA_VALID, 0x00180100}, /* omap5430_control_core_pad0_usbb3_hsic_data_pad1_sdcard_clk */
	{DATA_VALID, 0x01180118}, /* omap5430_control_core_pad0_sdcard_cmd_pad1_sdcard_data2 */
	{DATA_VALID, 0x01180118}, /* omap5430_control_core_pad0_sdcard_data3_pad1_sdcard_data0 */
	{DATA_VALID, 0x00000118}, /* omap5430_control_core_pad0_sdcard_data1_pad1_usbd0_hs_dp */
	{DATA_VALID, 0x01180000}, /* omap5430_control_core_pad0_usbd0_hs_dm_pad1_i2c1_pmic_scl */
	{DATA_VALID, 0x00000118}, /* omap5430_control_core_pad0_i2c1_pmic_sda_pad1_usbd0_ss_rx */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_padconf_wakeupevent_0 */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_padconf_wakeupevent_1 */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_padconf_wakeupevent_2 */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_padconf_wakeupevent_3 */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_padconf_wakeupevent_4 */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_padconf_wakeupevent_5 */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_padconf_wakeupevent_6 */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_padconf_global */ /* FIXME */
	{DATA_TBD, 0x00000000}, /* omap5430_control_padconf_mode */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_smart1io_padconf_0 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_smart1io_padconf_1 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_smart1io_padconf_2 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_smart2io_padconf_0 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_smart2io_padconf_1 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_smart2io_padconf_2 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_smart3io_padconf_0 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_smart3io_padconf_1 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_pbias */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_i2c_0 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_camera_rx */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_hdmi_tx_phy */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_uniportm */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_dsiphy */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_mcbsplp */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_usb2phycore */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_hdmi_1 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_hsi */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_ddr3ch1_0 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_ddr3ch2_0 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_ddrch1_0 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_ddrch1_1 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_ddrch2_0 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_ddrch2_1 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_lpddr2ch1_0 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_lpddr2ch1_1 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_ddrio_0 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_ddrio_1 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_ddrio_2 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_hyst_1 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_usbb_hsic_control */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_c2c */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_control_spare_rw */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_control_spare_r */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_core_control_spare_r_c0 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_srcomp_north_side */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_srcomp_south_side */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_srcomp_east_side */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_srcomp_west_side */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF} }; /* omap5430_control_srcomp_code_latch */ /* FIXME */


const ctrlmod54xx_golden_item ctrlmod_wkup54xxes1_golden_values[OMAP5430ES1_CTRL_MODULE_WKUP_MOD_REGCOUNT] = {
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_revision */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_hwinfo */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_sysconfig */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_ocpreg_spare */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_prot_emif1_sdram_config */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_prot_emif1_lpddr2_nvm_config */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_prot_emif2_sdram_config */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_prot_emif2_lpddr2_nvm_config2 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_usb_conf */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_std_fuse_conf */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_dpll_clk_trimming */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_emif1_sdram_config_ext */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_emif2_sdram_config_ext */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_emif1_sdram_config_ext_1 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_emif2_sdram_config_ext_2 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_std_fuse_die_id_0 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_id_code */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_std_fuse_die_id_1 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_std_fuse_die_id_2 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_std_fuse_die_id_3 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_std_fuse_prod_id_0 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_0 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_1 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_2 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_3 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_4 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_5 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_6 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_7 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_8 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_9 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_10 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_11 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_12 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_13 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_14 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_15 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_16 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_17 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_18 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_19 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_20 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_21 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_22 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_23 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_24 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_25 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_26 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_27 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_28 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_29 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_conf_debug_sel_tst_30 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF} }; /* omap5430_control_wkup_conf_debug_sel_tst_31 */ /* FIXME */


const ctrlmod54xx_golden_item ctrlmod_wkup_pad54xxes1_golden_values[OMAP5430_CTRL_MODULE_WKUP_PAD_MOD_REGCOUNT] = {
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_pad_revision */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_pad_hwinfo */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_pad_sysconfig */ /* FIXME */
	{DATA_VALID, 0x01010101}, /* omap5430_control_wkup_pad0_llia_wakereqin_pad1_llib_wakereqin */ /* FIXME */
	{DATA_VALID, 0x01180118}, /* omap5430_control_wkup_pad0_drm_emu0_pad1_drm_emu1 */ /* FIXME */
	{DATA_VALID, 0x01000100}, /* omap5430_control_wkup_pad0_jtag_ntrst_pad1_jtag_tck */ /* FIXME */
	{DATA_VALID, 0x01000000}, /* omap5430_control_wkup_pad0_jtag_rtck_pad1_jtag_tmsc */ /* FIXME */
	{DATA_VALID, 0x00000100}, /* omap5430_control_wkup_pad0_jtag_tdi_pad1_jtag_tdo */ /* FIXME */
	{DATA_VALID, 0x01000100}, /* omap5430_control_wkup_pad0_sys_32k_pad1_fref_clk_ioreq */ /* FIXME */
	{DATA_VALID, 0x00000000}, /* omap5430_control_wkup_pad0_fref_clk0_out_pad1_fref_clk1_out */ /* FIXME */
	{DATA_VALID, 0x010E0000}, /* omap5430_control_wkup_pad0_fref_clk2_out_pad1_fref_clk2_req */ /* FIXME */
	{DATA_VALID, 0x0000010E}, /* omap5430_control_wkup_pad0_fref_clk1_req_pad1_sys_nrespwron */ /* FIXME */
	{DATA_VALID, 0x00000018}, /* omap5430_control_wkup_pad0_sys_nreswarm_pad1_sys_pwr_req */ /* FIXME */
	{DATA_VALID, 0x01180118}, /* omap5430_control_wkup_pad0_sys_nirq1_pad1_sys_nirq2 */ /* FIXME */
	{DATA_VALID, 0x01180118}, /* omap5430_control_wkup_pad0_sr_pmic_scl_pad1_sr_pmic_sda */ /* FIXME */
	{DATA_VALID, 0x01000100}, /* omap5430_control_wkup_pad0_sys_boot0_pad1_sys_boot1 */ /* FIXME */
	{DATA_VALID, 0x01000100}, /* omap5430_control_wkup_pad0_sys_boot2_pad1_sys_boot3 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_pad0_sys_boot4_pad1_sys_boot5 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_padconf_wakeupevent_0 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_smart1nopmio_padconf_0 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_smart1nopmio_padconf_1 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_wkup_padconf_mode */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_xtal_oscillator */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_i2c_2 */ /* FIXME */
	{DATA_TBD, 0xDEADBEEF}, /* omap5430_control_ckobuffer */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_control_spare_rw */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_control_spare_r */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_wkup_control_spare_r_c0 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_srcomp_east_side_wkup */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_efuse_2 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_efuse_3 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_efuse_4 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_efuse_5 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_efuse_6 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_efuse_7 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_efuse_8 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_efuse_9 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_efuse_10 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_efuse_1 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF}, /* omap5430_control_efuse_12 */ /* FIXME */
	{DATA_IGNORE, 0xDEADBEEF} }; /* omap5430_control_efuse_13 */ /* FIXME */
