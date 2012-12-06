/*
 *
 * @Component			OMAPCONF
 * @Filename			prm54xx-defs.h
 * @Description			OMAP5 ES2 PRM Registers Definitions & Functions
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


#include <prm54xx-defs.h>
#include <prm54xxes1-defs.h>
#include <stdio.h>


reg omap5430_pm_dss_pwrstctrl = {
	"PM_DSS_PWRSTCTRL",
	OMAP5430_PM_DSS_PWRSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_pm_dss_pwrstst = {
	"PM_DSS_PWRSTST",
	OMAP5430_PM_DSS_PWRSTST,
	0xDEADBEEF,
	0};

reg omap5430_pm_dss_dss_wkdep = {
	"PM_DSS_DSS_WKDEP",
	OMAP5430_PM_DSS_DSS_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_dss_dss_context = {
	"RM_DSS_DSS_CONTEXT",
	OMAP5430_RM_DSS_DSS_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_dss_bb2d_context = {
	"RM_DSS_BB2D_CONTEXT",
	OMAP5430_RM_DSS_BB2D_CONTEXT,
	0xDEADBEEF,
	0};

reg *omap5430_dss_prm_mod[OMAP5430_DSS_PRM_MOD_REGCOUNT + 1] = {
	&omap5430_pm_dss_pwrstctrl,
	&omap5430_pm_dss_pwrstst,
	&omap5430_pm_dss_dss_wkdep,
	&omap5430_rm_dss_dss_context,
	&omap5430_rm_dss_bb2d_context,
	NULL};

reg omap5430_rm_wkupaon_l4_wkup_context = {
	"RM_WKUPAON_L4_WKUP_CONTEXT",
	OMAP5430_RM_WKUPAON_L4_WKUP_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_wkupaon_wd_timer2_wkdep = {
	"PM_WKUPAON_WD_TIMER2_WKDEP",
	OMAP5430_PM_WKUPAON_WD_TIMER2_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_wkupaon_wd_timer2_context = {
	"RM_WKUPAON_WD_TIMER2_CONTEXT",
	OMAP5430_RM_WKUPAON_WD_TIMER2_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_wkupaon_gpio1_wkdep = {
	"PM_WKUPAON_GPIO1_WKDEP",
	OMAP5430_PM_WKUPAON_GPIO1_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_wkupaon_gpio1_context = {
	"RM_WKUPAON_GPIO1_CONTEXT",
	OMAP5430_RM_WKUPAON_GPIO1_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_wkupaon_timer1_wkdep = {
	"PM_WKUPAON_TIMER1_WKDEP",
	OMAP5430_PM_WKUPAON_TIMER1_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_wkupaon_timer1_context = {
	"RM_WKUPAON_TIMER1_CONTEXT",
	OMAP5430_RM_WKUPAON_TIMER1_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_wkupaon_counter_32k_context = {
	"RM_WKUPAON_COUNTER_32K_CONTEXT",
	OMAP5430_RM_WKUPAON_COUNTER_32K_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_wkupaon_sar_ram_context = {
	"RM_WKUPAON_SAR_RAM_CONTEXT",
	OMAP5430_RM_WKUPAON_SAR_RAM_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_wkupaon_kbd_wkdep = {
	"PM_WKUPAON_KBD_WKDEP",
	OMAP5430_PM_WKUPAON_KBD_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_wkupaon_kbd_context = {
	"RM_WKUPAON_KBD_CONTEXT",
	OMAP5430_RM_WKUPAON_KBD_CONTEXT,
	0xDEADBEEF,
	0};

reg *omap5430_wkupaon_prm_mod[OMAP5430_WKUPAON_PRM_MOD_REGCOUNT + 1] = {
	&omap5430_rm_wkupaon_l4_wkup_context,
	&omap5430_pm_wkupaon_wd_timer2_wkdep,
	&omap5430_rm_wkupaon_wd_timer2_context,
	&omap5430_pm_wkupaon_gpio1_wkdep,
	&omap5430_rm_wkupaon_gpio1_context,
	&omap5430_pm_wkupaon_timer1_wkdep,
	&omap5430_rm_wkupaon_timer1_context,
	&omap5430_rm_wkupaon_counter_32k_context,
	&omap5430_rm_wkupaon_sar_ram_context,
	&omap5430_pm_wkupaon_kbd_wkdep,
	&omap5430_rm_wkupaon_kbd_context,
	NULL};

reg omap5430_revision_prm = {
	"REVISION_PRM",
	OMAP5430_REVISION_PRM,
	0xDEADBEEF,
	0};

reg omap5430_prm_irqstatus_mpu = {
	"PRM_IRQSTATUS_MPU",
	OMAP5430_PRM_IRQSTATUS_MPU,
	0xDEADBEEF,
	0};

reg omap5430_prm_irqstatus_mpu_2 = {
	"PRM_IRQSTATUS_MPU_2",
	OMAP5430_PRM_IRQSTATUS_MPU_2,
	0xDEADBEEF,
	0};

reg omap5430_prm_irqenable_mpu = {
	"PRM_IRQENABLE_MPU",
	OMAP5430_PRM_IRQENABLE_MPU,
	0xDEADBEEF,
	0};

reg omap5430_prm_irqenable_mpu_2 = {
	"PRM_IRQENABLE_MPU_2",
	OMAP5430_PRM_IRQENABLE_MPU_2,
	0xDEADBEEF,
	0};

reg omap5430_prm_irqstatus_ipu = {
	"PRM_IRQSTATUS_IPU",
	OMAP5430_PRM_IRQSTATUS_IPU,
	0xDEADBEEF,
	0};

reg omap5430_prm_irqenable_ipu = {
	"PRM_IRQENABLE_IPU",
	OMAP5430_PRM_IRQENABLE_IPU,
	0xDEADBEEF,
	0};

reg omap5430_prm_irqstatus_dsp = {
	"PRM_IRQSTATUS_DSP",
	OMAP5430_PRM_IRQSTATUS_DSP,
	0xDEADBEEF,
	0};

reg omap5430_prm_irqenable_dsp = {
	"PRM_IRQENABLE_DSP",
	OMAP5430_PRM_IRQENABLE_DSP,
	0xDEADBEEF,
	0};

reg omap5430_cm_prm_profiling_clkctrl = {
	"CM_PRM_PROFILING_CLKCTRL",
	OMAP5430_CM_PRM_PROFILING_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_prm_debug_cfg = {
	"PRM_DEBUG_CFG",
	OMAP5430_PRM_DEBUG_CFG,
	0xDEADBEEF,
	0};

reg *omap5430_ocp_socket_prm_mod[OMAP5430_OCP_SOCKET_PRM_MOD_REGCOUNT + 1] = {
	&omap5430_revision_prm,
	&omap5430_prm_irqstatus_mpu,
	&omap5430_prm_irqstatus_mpu_2,
	&omap5430_prm_irqenable_mpu,
	&omap5430_prm_irqenable_mpu_2,
	&omap5430_prm_irqstatus_ipu,
	&omap5430_prm_irqenable_ipu,
	&omap5430_prm_irqstatus_dsp,
	&omap5430_prm_irqenable_dsp,
	&omap5430_cm_prm_profiling_clkctrl,
	&omap5430_prm_debug_cfg,
	NULL};

reg omap5430_pm_cam_pwrstctrl = {
	"PM_CAM_PWRSTCTRL",
	OMAP5430_PM_CAM_PWRSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_pm_cam_pwrstst = {
	"PM_CAM_PWRSTST",
	OMAP5430_PM_CAM_PWRSTST,
	0xDEADBEEF,
	0};

reg omap5430_rm_cam_iss_context = {
	"RM_CAM_ISS_CONTEXT",
	OMAP5430_RM_CAM_ISS_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_cam_fdif_context = {
	"RM_CAM_FDIF_CONTEXT",
	OMAP5430_RM_CAM_FDIF_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_cam_cal_context = {
	"RM_CAM_CAL_CONTEXT",
	OMAP5430_RM_CAM_CAL_CONTEXT,
	0xDEADBEEF,
	0};

reg *omap5430_cam_prm_mod[OMAP5430_CAM_PRM_MOD_REGCOUNT + 1] = {
	&omap5430_pm_cam_pwrstctrl,
	&omap5430_pm_cam_pwrstst,
	&omap5430_rm_cam_iss_context,
	&omap5430_rm_cam_fdif_context,
	&omap5430_rm_cam_cal_context,
	NULL};

reg omap5430_pm_dsp_pwrstctrl = {
	"PM_DSP_PWRSTCTRL",
	OMAP5430_PM_DSP_PWRSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_pm_dsp_pwrstst = {
	"PM_DSP_PWRSTST",
	OMAP5430_PM_DSP_PWRSTST,
	0xDEADBEEF,
	0};

reg omap5430_rm_dsp_rstctrl = {
	"RM_DSP_RSTCTRL",
	OMAP5430_RM_DSP_RSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_rm_dsp_rstst = {
	"RM_DSP_RSTST",
	OMAP5430_RM_DSP_RSTST,
	0xDEADBEEF,
	0};

reg omap5430_rm_dsp_dsp_context = {
	"RM_DSP_DSP_CONTEXT",
	OMAP5430_RM_DSP_DSP_CONTEXT,
	0xDEADBEEF,
	0};

reg *omap5430_dsp_prm_mod[OMAP5430_DSP_PRM_MOD_REGCOUNT + 1] = {
	&omap5430_pm_dsp_pwrstctrl,
	&omap5430_pm_dsp_pwrstst,
	&omap5430_rm_dsp_rstctrl,
	&omap5430_rm_dsp_rstst,
	&omap5430_rm_dsp_dsp_context,
	NULL};

reg omap5430_prm_rstctrl = {
	"PRM_RSTCTRL",
	OMAP5430_PRM_RSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_prm_rstst = {
	"PRM_RSTST",
	OMAP5430_PRM_RSTST,
	0xDEADBEEF,
	0};

reg omap5430_prm_rsttime = {
	"PRM_RSTTIME",
	OMAP5430_PRM_RSTTIME,
	0xDEADBEEF,
	0};

reg omap5430_prm_clkreqctrl = {
	"PRM_CLKREQCTRL",
	OMAP5430_PRM_CLKREQCTRL,
	0xDEADBEEF,
	0};

reg omap5430_prm_voltctrl = {
	"PRM_VOLTCTRL",
	OMAP5430_PRM_VOLTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_prm_pwrreqctrl = {
	"PRM_PWRREQCTRL",
	OMAP5430_PRM_PWRREQCTRL,
	0xDEADBEEF,
	0};

reg omap5430_prm_pscon_count = {
	"PRM_PSCON_COUNT",
	OMAP5430_PRM_PSCON_COUNT,
	0xDEADBEEF,
	0};

reg omap5430_prm_io_count = {
	"PRM_IO_COUNT",
	OMAP5430_PRM_IO_COUNT,
	0xDEADBEEF,
	0};

reg omap5430_prm_io_pmctrl = {
	"PRM_IO_PMCTRL",
	OMAP5430_PRM_IO_PMCTRL,
	0xDEADBEEF,
	0};

reg omap5430_prm_voltsetup_warmreset = {
	"PRM_VOLTSETUP_WARMRESET",
	OMAP5430_PRM_VOLTSETUP_WARMRESET,
	0xDEADBEEF,
	0};

reg omap5430_prm_voltsetup_core_off = {
	"PRM_VOLTSETUP_CORE_OFF",
	OMAP5430_PRM_VOLTSETUP_CORE_OFF,
	0xDEADBEEF,
	0};

reg omap5430_prm_voltsetup_mpu_off = {
	"PRM_VOLTSETUP_MPU_OFF",
	OMAP5430_PRM_VOLTSETUP_MPU_OFF,
	0xDEADBEEF,
	0};

reg omap5430_prm_voltsetup_mm_off = {
	"PRM_VOLTSETUP_MM_OFF",
	OMAP5430_PRM_VOLTSETUP_MM_OFF,
	0xDEADBEEF,
	0};

reg omap5430_prm_voltsetup_core_ret_sleep = {
	"PRM_VOLTSETUP_CORE_RET_SLEEP",
	OMAP5430_PRM_VOLTSETUP_CORE_RET_SLEEP,
	0xDEADBEEF,
	0};

reg omap5430_prm_voltsetup_mpu_ret_sleep = {
	"PRM_VOLTSETUP_MPU_RET_SLEEP",
	OMAP5430_PRM_VOLTSETUP_MPU_RET_SLEEP,
	0xDEADBEEF,
	0};

reg omap5430_prm_voltsetup_mm_ret_sleep = {
	"PRM_VOLTSETUP_MM_RET_SLEEP",
	OMAP5430_PRM_VOLTSETUP_MM_RET_SLEEP,
	0xDEADBEEF,
	0};

reg omap5430_prm_vp_core_config = {
	"PRM_VP_CORE_CONFIG",
	OMAP5430_PRM_VP_CORE_CONFIG,
	0xDEADBEEF,
	0};

reg omap5430_prm_vp_core_status = {
	"PRM_VP_CORE_STATUS",
	OMAP5430_PRM_VP_CORE_STATUS,
	0xDEADBEEF,
	0};

reg omap5430_prm_vp_core_vlimitto = {
	"PRM_VP_CORE_VLIMITTO",
	OMAP5430_PRM_VP_CORE_VLIMITTO,
	0xDEADBEEF,
	0};

reg omap5430_prm_vp_core_voltage = {
	"PRM_VP_CORE_VOLTAGE",
	OMAP5430_PRM_VP_CORE_VOLTAGE,
	0xDEADBEEF,
	0};

reg omap5430_prm_vp_core_vstepmax = {
	"PRM_VP_CORE_VSTEPMAX",
	OMAP5430_PRM_VP_CORE_VSTEPMAX,
	0xDEADBEEF,
	0};

reg omap5430_prm_vp_core_vstepmin = {
	"PRM_VP_CORE_VSTEPMIN",
	OMAP5430_PRM_VP_CORE_VSTEPMIN,
	0xDEADBEEF,
	0};

reg omap5430_prm_vp_mpu_config = {
	"PRM_VP_MPU_CONFIG",
	OMAP5430_PRM_VP_MPU_CONFIG,
	0xDEADBEEF,
	0};

reg omap5430_prm_vp_mpu_status = {
	"PRM_VP_MPU_STATUS",
	OMAP5430_PRM_VP_MPU_STATUS,
	0xDEADBEEF,
	0};

reg omap5430_prm_vp_mpu_vlimitto = {
	"PRM_VP_MPU_VLIMITTO",
	OMAP5430_PRM_VP_MPU_VLIMITTO,
	0xDEADBEEF,
	0};

reg omap5430_prm_vp_mpu_voltage = {
	"PRM_VP_MPU_VOLTAGE",
	OMAP5430_PRM_VP_MPU_VOLTAGE,
	0xDEADBEEF,
	0};

reg omap5430_prm_vp_mpu_vstepmax = {
	"PRM_VP_MPU_VSTEPMAX",
	OMAP5430_PRM_VP_MPU_VSTEPMAX,
	0xDEADBEEF,
	0};

reg omap5430_prm_vp_mpu_vstepmin = {
	"PRM_VP_MPU_VSTEPMIN",
	OMAP5430_PRM_VP_MPU_VSTEPMIN,
	0xDEADBEEF,
	0};

reg omap5430_prm_vp_mm_config = {
	"PRM_VP_MM_CONFIG",
	OMAP5430_PRM_VP_MM_CONFIG,
	0xDEADBEEF,
	0};

reg omap5430_prm_vp_mm_status = {
	"PRM_VP_MM_STATUS",
	OMAP5430_PRM_VP_MM_STATUS,
	0xDEADBEEF,
	0};

reg omap5430_prm_vp_mm_vlimitto = {
	"PRM_VP_MM_VLIMITTO",
	OMAP5430_PRM_VP_MM_VLIMITTO,
	0xDEADBEEF,
	0};

reg omap5430_prm_vp_mm_voltage = {
	"PRM_VP_MM_VOLTAGE",
	OMAP5430_PRM_VP_MM_VOLTAGE,
	0xDEADBEEF,
	0};

reg omap5430_prm_vp_mm_vstepmax = {
	"PRM_VP_MM_VSTEPMAX",
	OMAP5430_PRM_VP_MM_VSTEPMAX,
	0xDEADBEEF,
	0};

reg omap5430_prm_vp_mm_vstepmin = {
	"PRM_VP_MM_VSTEPMIN",
	OMAP5430_PRM_VP_MM_VSTEPMIN,
	0xDEADBEEF,
	0};

reg omap5430_prm_vc_smps_core_config = {
	"PRM_VC_SMPS_CORE_CONFIG",
	OMAP5430_PRM_VC_SMPS_CORE_CONFIG,
	0xDEADBEEF,
	0};

reg omap5430_prm_vc_smps_mm_config = {
	"PRM_VC_SMPS_MM_CONFIG",
	OMAP5430_PRM_VC_SMPS_MM_CONFIG,
	0xDEADBEEF,
	0};

reg omap5430_prm_vc_smps_mpu_config = {
	"PRM_VC_SMPS_MPU_CONFIG",
	OMAP5430_PRM_VC_SMPS_MPU_CONFIG,
	0xDEADBEEF,
	0};

reg omap5430_prm_vc_val_cmd_vdd_core_l = {
	"PRM_VC_VAL_CMD_VDD_CORE_L",
	OMAP5430_PRM_VC_VAL_CMD_VDD_CORE_L,
	0xDEADBEEF,
	0};

reg omap5430_prm_vc_val_cmd_vdd_mm_l = {
	"PRM_VC_VAL_CMD_VDD_MM_L",
	OMAP5430_PRM_VC_VAL_CMD_VDD_MM_L,
	0xDEADBEEF,
	0};

reg omap5430_prm_vc_val_cmd_vdd_mpu_l = {
	"PRM_VC_VAL_CMD_VDD_MPU_L",
	OMAP5430_PRM_VC_VAL_CMD_VDD_MPU_L,
	0xDEADBEEF,
	0};

reg omap5430_prm_vc_val_bypass = {
	"PRM_VC_VAL_BYPASS",
	OMAP5430_PRM_VC_VAL_BYPASS,
	0xDEADBEEF,
	0};

reg omap5430_prm_vc_core_errst = {
	"PRM_VC_CORE_ERRST",
	OMAP5430_PRM_VC_CORE_ERRST,
	0xDEADBEEF,
	0};

reg omap5430_prm_vc_mm_errst = {
	"PRM_VC_MM_ERRST",
	OMAP5430_PRM_VC_MM_ERRST,
	0xDEADBEEF,
	0};

reg omap5430_prm_vc_mpu_errst = {
	"PRM_VC_MPU_ERRST",
	OMAP5430_PRM_VC_MPU_ERRST,
	0xDEADBEEF,
	0};

reg omap5430_prm_vc_bypass_errst = {
	"PRM_VC_BYPASS_ERRST",
	OMAP5430_PRM_VC_BYPASS_ERRST,
	0xDEADBEEF,
	0};

reg omap5430_prm_vc_cfg_i2c_mode = {
	"PRM_VC_CFG_I2C_MODE",
	OMAP5430_PRM_VC_CFG_I2C_MODE,
	0xDEADBEEF,
	0};

reg omap5430_prm_vc_cfg_i2c_clk = {
	"PRM_VC_CFG_I2C_CLK",
	OMAP5430_PRM_VC_CFG_I2C_CLK,
	0xDEADBEEF,
	0};

reg omap5430_prm_sram_count = {
	"PRM_SRAM_COUNT",
	OMAP5430_PRM_SRAM_COUNT,
	0xDEADBEEF,
	0};

reg omap5430_prm_sldo_core_setup = {
	"PRM_SLDO_CORE_SETUP",
	OMAP5430_PRM_SLDO_CORE_SETUP,
	0xDEADBEEF,
	0};

reg omap5430_prm_sldo_core_ctrl = {
	"PRM_SLDO_CORE_CTRL",
	OMAP5430_PRM_SLDO_CORE_CTRL,
	0xDEADBEEF,
	0};

reg omap5430_prm_sldo_mpu_setup = {
	"PRM_SLDO_MPU_SETUP",
	OMAP5430_PRM_SLDO_MPU_SETUP,
	0xDEADBEEF,
	0};

reg omap5430_prm_sldo_mpu_ctrl = {
	"PRM_SLDO_MPU_CTRL",
	OMAP5430_PRM_SLDO_MPU_CTRL,
	0xDEADBEEF,
	0};

reg omap5430_prm_sldo_mm_setup = {
	"PRM_SLDO_MM_SETUP",
	OMAP5430_PRM_SLDO_MM_SETUP,
	0xDEADBEEF,
	0};

reg omap5430_prm_sldo_mm_ctrl = {
	"PRM_SLDO_MM_CTRL",
	OMAP5430_PRM_SLDO_MM_CTRL,
	0xDEADBEEF,
	0};

reg omap5430_prm_abbldo_mpu_setup = {
	"PRM_ABBLDO_MPU_SETUP",
	OMAP5430_PRM_ABBLDO_MPU_SETUP,
	0xDEADBEEF,
	0};

reg omap5430_prm_abbldo_mpu_ctrl = {
	"PRM_ABBLDO_MPU_CTRL",
	OMAP5430_PRM_ABBLDO_MPU_CTRL,
	0xDEADBEEF,
	0};

reg omap5430_prm_abbldo_mm_setup = {
	"PRM_ABBLDO_MM_SETUP",
	OMAP5430_PRM_ABBLDO_MM_SETUP,
	0xDEADBEEF,
	0};

reg omap5430_prm_abbldo_mm_ctrl = {
	"PRM_ABBLDO_MM_CTRL",
	OMAP5430_PRM_ABBLDO_MM_CTRL,
	0xDEADBEEF,
	0};

reg omap5430_prm_bandgap_setup = {
	"PRM_BANDGAP_SETUP",
	OMAP5430_PRM_BANDGAP_SETUP,
	0xDEADBEEF,
	0};

reg omap5430_prm_device_off_ctrl = {
	"PRM_DEVICE_OFF_CTRL",
	OMAP5430_PRM_DEVICE_OFF_CTRL,
	0xDEADBEEF,
	0};

reg omap5430_prm_phase1_cndp = {
	"PRM_PHASE1_CNDP",
	OMAP5430_PRM_PHASE1_CNDP,
	0xDEADBEEF,
	0};

reg omap5430_prm_phase2a_cndp = {
	"PRM_PHASE2A_CNDP",
	OMAP5430_PRM_PHASE2A_CNDP,
	0xDEADBEEF,
	0};

reg omap5430_prm_phase2b_cndp = {
	"PRM_PHASE2B_CNDP",
	OMAP5430_PRM_PHASE2B_CNDP,
	0xDEADBEEF,
	0};

reg omap5430_prm_modem_if_ctrl = {
	"PRM_MODEM_IF_CTRL",
	OMAP5430_PRM_MODEM_IF_CTRL,
	0xDEADBEEF,
	0};

reg omap5430_prm_voltst_mpu = {
	"PRM_VOLTST_MPU",
	OMAP5430_PRM_VOLTST_MPU,
	0xDEADBEEF,
	0};

reg omap5430_prm_voltst_mm = {
	"PRM_VOLTST_MM",
	OMAP5430_PRM_VOLTST_MM,
	0xDEADBEEF,
	0};

reg *omap5430_device_prm_mod[OMAP5430_DEVICE_PRM_MOD_REGCOUNT + 1] = {
	&omap5430_prm_rstctrl,
	&omap5430_prm_rstst,
	&omap5430_prm_rsttime,
	&omap5430_prm_clkreqctrl,
	&omap5430_prm_voltctrl,
	&omap5430_prm_pwrreqctrl,
	&omap5430_prm_pscon_count,
	&omap5430_prm_io_count,
	&omap5430_prm_io_pmctrl,
	&omap5430_prm_voltsetup_warmreset,
	&omap5430_prm_voltsetup_core_off,
	&omap5430_prm_voltsetup_mpu_off,
	&omap5430_prm_voltsetup_mm_off,
	&omap5430_prm_voltsetup_core_ret_sleep,
	&omap5430_prm_voltsetup_mpu_ret_sleep,
	&omap5430_prm_voltsetup_mm_ret_sleep,
	&omap5430_prm_vp_core_config,
	&omap5430_prm_vp_core_status,
	&omap5430_prm_vp_core_vlimitto,
	&omap5430_prm_vp_core_voltage,
	&omap5430_prm_vp_core_vstepmax,
	&omap5430_prm_vp_core_vstepmin,
	&omap5430_prm_vp_mpu_config,
	&omap5430_prm_vp_mpu_status,
	&omap5430_prm_vp_mpu_vlimitto,
	&omap5430_prm_vp_mpu_voltage,
	&omap5430_prm_vp_mpu_vstepmax,
	&omap5430_prm_vp_mpu_vstepmin,
	&omap5430_prm_vp_mm_config,
	&omap5430_prm_vp_mm_status,
	&omap5430_prm_vp_mm_vlimitto,
	&omap5430_prm_vp_mm_voltage,
	&omap5430_prm_vp_mm_vstepmax,
	&omap5430_prm_vp_mm_vstepmin,
	&omap5430_prm_vc_smps_core_config,
	&omap5430_prm_vc_smps_mm_config,
	&omap5430_prm_vc_smps_mpu_config,
	&omap5430_prm_vc_val_cmd_vdd_core_l,
	&omap5430_prm_vc_val_cmd_vdd_mm_l,
	&omap5430_prm_vc_val_cmd_vdd_mpu_l,
	&omap5430_prm_vc_val_bypass,
	&omap5430_prm_vc_core_errst,
	&omap5430_prm_vc_mm_errst,
	&omap5430_prm_vc_mpu_errst,
	&omap5430_prm_vc_bypass_errst,
	&omap5430_prm_vc_cfg_i2c_mode,
	&omap5430_prm_vc_cfg_i2c_clk,
	&omap5430_prm_sram_count,
	&omap5430_prm_sldo_core_setup,
	&omap5430_prm_sldo_core_ctrl,
	&omap5430_prm_sldo_mpu_setup,
	&omap5430_prm_sldo_mpu_ctrl,
	&omap5430_prm_sldo_mm_setup,
	&omap5430_prm_sldo_mm_ctrl,
	&omap5430_prm_abbldo_mpu_setup,
	&omap5430_prm_abbldo_mpu_ctrl,
	&omap5430_prm_abbldo_mm_setup,
	&omap5430_prm_abbldo_mm_ctrl,
	&omap5430_prm_bandgap_setup,
	&omap5430_prm_device_off_ctrl,
	&omap5430_prm_phase1_cndp,
	&omap5430_prm_phase2a_cndp,
	&omap5430_prm_phase2b_cndp,
	&omap5430_prm_modem_if_ctrl,
	&omap5430_prm_voltst_mpu,
	&omap5430_prm_voltst_mm,
	NULL};

reg omap5430_pm_abe_pwrstctrl = {
	"PM_ABE_PWRSTCTRL",
	OMAP5430_PM_ABE_PWRSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_pm_abe_pwrstst = {
	"PM_ABE_PWRSTST",
	OMAP5430_PM_ABE_PWRSTST,
	0xDEADBEEF,
	0};

reg omap5430_rm_abe_aess_context = {
	"RM_ABE_AESS_CONTEXT",
	OMAP5430_RM_ABE_AESS_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_abe_mcpdm_wkdep = {
	"PM_ABE_MCPDM_WKDEP",
	OMAP5430_PM_ABE_MCPDM_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_abe_mcpdm_context = {
	"RM_ABE_MCPDM_CONTEXT",
	OMAP5430_RM_ABE_MCPDM_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_abe_dmic_wkdep = {
	"PM_ABE_DMIC_WKDEP",
	OMAP5430_PM_ABE_DMIC_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_abe_dmic_context = {
	"RM_ABE_DMIC_CONTEXT",
	OMAP5430_RM_ABE_DMIC_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_abe_mcasp_wkdep = {
	"PM_ABE_MCASP_WKDEP",
	OMAP5430_PM_ABE_MCASP_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_abe_mcasp_context = {
	"RM_ABE_MCASP_CONTEXT",
	OMAP5430_RM_ABE_MCASP_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_abe_mcbsp1_wkdep = {
	"PM_ABE_MCBSP1_WKDEP",
	OMAP5430_PM_ABE_MCBSP1_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_abe_mcbsp1_context = {
	"RM_ABE_MCBSP1_CONTEXT",
	OMAP5430_RM_ABE_MCBSP1_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_abe_mcbsp2_wkdep = {
	"PM_ABE_MCBSP2_WKDEP",
	OMAP5430_PM_ABE_MCBSP2_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_abe_mcbsp2_context = {
	"RM_ABE_MCBSP2_CONTEXT",
	OMAP5430_RM_ABE_MCBSP2_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_abe_mcbsp3_wkdep = {
	"PM_ABE_MCBSP3_WKDEP",
	OMAP5430_PM_ABE_MCBSP3_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_abe_mcbsp3_context = {
	"RM_ABE_MCBSP3_CONTEXT",
	OMAP5430_RM_ABE_MCBSP3_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_abe_slimbus1_wkdep = {
	"PM_ABE_SLIMBUS1_WKDEP",
	OMAP5430_PM_ABE_SLIMBUS1_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_abe_slimbus1_context = {
	"RM_ABE_SLIMBUS1_CONTEXT",
	OMAP5430_RM_ABE_SLIMBUS1_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_abe_timer5_wkdep = {
	"PM_ABE_TIMER5_WKDEP",
	OMAP5430_PM_ABE_TIMER5_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_abe_timer5_context = {
	"RM_ABE_TIMER5_CONTEXT",
	OMAP5430_RM_ABE_TIMER5_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_abe_timer6_wkdep = {
	"PM_ABE_TIMER6_WKDEP",
	OMAP5430_PM_ABE_TIMER6_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_abe_timer6_context = {
	"RM_ABE_TIMER6_CONTEXT",
	OMAP5430_RM_ABE_TIMER6_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_abe_timer7_wkdep = {
	"PM_ABE_TIMER7_WKDEP",
	OMAP5430_PM_ABE_TIMER7_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_abe_timer7_context = {
	"RM_ABE_TIMER7_CONTEXT",
	OMAP5430_RM_ABE_TIMER7_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_abe_timer8_wkdep = {
	"PM_ABE_TIMER8_WKDEP",
	OMAP5430_PM_ABE_TIMER8_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_abe_timer8_context = {
	"RM_ABE_TIMER8_CONTEXT",
	OMAP5430_RM_ABE_TIMER8_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_abe_wd_timer3_wkdep = {
	"PM_ABE_WD_TIMER3_WKDEP",
	OMAP5430_PM_ABE_WD_TIMER3_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_abe_wd_timer3_context = {
	"RM_ABE_WD_TIMER3_CONTEXT",
	OMAP5430_RM_ABE_WD_TIMER3_CONTEXT,
	0xDEADBEEF,
	0};

reg *omap5430_abe_prm_mod[OMAP5430_ABE_PRM_MOD_REGCOUNT + 1] = {
	&omap5430_pm_abe_pwrstctrl,
	&omap5430_pm_abe_pwrstst,
	&omap5430_rm_abe_aess_context,
	&omap5430_pm_abe_mcpdm_wkdep,
	&omap5430_rm_abe_mcpdm_context,
	&omap5430_pm_abe_dmic_wkdep,
	&omap5430_rm_abe_dmic_context,
	&omap5430_pm_abe_mcasp_wkdep,
	&omap5430_rm_abe_mcasp_context,
	&omap5430_pm_abe_mcbsp1_wkdep,
	&omap5430_rm_abe_mcbsp1_context,
	&omap5430_pm_abe_mcbsp2_wkdep,
	&omap5430_rm_abe_mcbsp2_context,
	&omap5430_pm_abe_mcbsp3_wkdep,
	&omap5430_rm_abe_mcbsp3_context,
	&omap5430_pm_abe_slimbus1_wkdep,
	&omap5430_rm_abe_slimbus1_context,
	&omap5430_pm_abe_timer5_wkdep,
	&omap5430_rm_abe_timer5_context,
	&omap5430_pm_abe_timer6_wkdep,
	&omap5430_rm_abe_timer6_context,
	&omap5430_pm_abe_timer7_wkdep,
	&omap5430_rm_abe_timer7_context,
	&omap5430_pm_abe_timer8_wkdep,
	&omap5430_rm_abe_timer8_context,
	&omap5430_pm_abe_wd_timer3_wkdep,
	&omap5430_rm_abe_wd_timer3_context,
	NULL};

reg omap5430_pm_gpu_pwrstctrl = {
	"PM_GPU_PWRSTCTRL",
	OMAP5430_PM_GPU_PWRSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_pm_gpu_pwrstst = {
	"PM_GPU_PWRSTST",
	OMAP5430_PM_GPU_PWRSTST,
	0xDEADBEEF,
	0};

reg omap5430_rm_gpu_gpu_context = {
	"RM_GPU_GPU_CONTEXT",
	OMAP5430_RM_GPU_GPU_CONTEXT,
	0xDEADBEEF,
	0};

reg *omap5430_gpu_prm_mod[OMAP5430_GPU_PRM_MOD_REGCOUNT + 1] = {
	&omap5430_pm_gpu_pwrstctrl,
	&omap5430_pm_gpu_pwrstst,
	&omap5430_rm_gpu_gpu_context,
	NULL};

reg omap5430_pm_coreaon_smartreflex_mpu_wkdep = {
	"PM_COREAON_SMARTREFLEX_MPU_WKDEP",
	OMAP5430_PM_COREAON_SMARTREFLEX_MPU_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_coreaon_smartreflex_mpu_context = {
	"RM_COREAON_SMARTREFLEX_MPU_CONTEXT",
	OMAP5430_RM_COREAON_SMARTREFLEX_MPU_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_coreaon_smartreflex_mm_wkdep = {
	"PM_COREAON_SMARTREFLEX_MM_WKDEP",
	OMAP5430_PM_COREAON_SMARTREFLEX_MM_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_coreaon_smartreflex_mm_context = {
	"RM_COREAON_SMARTREFLEX_MM_CONTEXT",
	OMAP5430_RM_COREAON_SMARTREFLEX_MM_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_coreaon_smartreflex_core_wkdep = {
	"PM_COREAON_SMARTREFLEX_CORE_WKDEP",
	OMAP5430_PM_COREAON_SMARTREFLEX_CORE_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_coreaon_smartreflex_core_context = {
	"RM_COREAON_SMARTREFLEX_CORE_CONTEXT",
	OMAP5430_RM_COREAON_SMARTREFLEX_CORE_CONTEXT,
	0xDEADBEEF,
	0};

reg *omap5430_coreaon_prm_mod[OMAP5430_COREAON_PRM_MOD_REGCOUNT + 1] = {
	&omap5430_pm_coreaon_smartreflex_mpu_wkdep,
	&omap5430_rm_coreaon_smartreflex_mpu_context,
	&omap5430_pm_coreaon_smartreflex_mm_wkdep,
	&omap5430_rm_coreaon_smartreflex_mm_context,
	&omap5430_pm_coreaon_smartreflex_core_wkdep,
	&omap5430_rm_coreaon_smartreflex_core_context,
	NULL};

reg omap5430_pm_custefuse_pwrstctrl = {
	"PM_CUSTEFUSE_PWRSTCTRL",
	OMAP5430_PM_CUSTEFUSE_PWRSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_pm_custefuse_pwrstst = {
	"PM_CUSTEFUSE_PWRSTST",
	OMAP5430_PM_CUSTEFUSE_PWRSTST,
	0xDEADBEEF,
	0};

reg omap5430_rm_custefuse_efuse_ctrl_cust_context = {
	"RM_CUSTEFUSE_EFUSE_CTRL_CUST_CONTEXT",
	OMAP5430_RM_CUSTEFUSE_EFUSE_CTRL_CUST_CONTEXT,
	0xDEADBEEF,
	0};

reg *omap5430_custefuse_prm_mod[OMAP5430_CUSTEFUSE_PRM_MOD_REGCOUNT + 1] = {
	&omap5430_pm_custefuse_pwrstctrl,
	&omap5430_pm_custefuse_pwrstst,
	&omap5430_rm_custefuse_efuse_ctrl_cust_context,
	NULL};

reg omap5430_cm_clksel_abe_dss_sys = {
	"CM_CLKSEL_ABE_DSS_SYS",
	OMAP5430_CM_CLKSEL_ABE_DSS_SYS,
	0xDEADBEEF,
	0};

reg omap5430_cm_clksel_wkupaon = {
	"CM_CLKSEL_WKUPAON",
	OMAP5430_CM_CLKSEL_WKUPAON,
	0xDEADBEEF,
	0};

reg omap5430_cm_clksel_abe_pll_ref = {
	"CM_CLKSEL_ABE_PLL_REF",
	OMAP5430_CM_CLKSEL_ABE_PLL_REF,
	0xDEADBEEF,
	0};

reg omap5430_cm_clksel_sys = {
	"CM_CLKSEL_SYS",
	OMAP5430_CM_CLKSEL_SYS,
	0xDEADBEEF,
	0};

reg *omap5430_ckgen_prm_mod[OMAP5430_CKGEN_PRM_MOD_REGCOUNT + 1] = {
	&omap5430_cm_clksel_abe_dss_sys,
	&omap5430_cm_clksel_wkupaon,
	&omap5430_cm_clksel_abe_pll_ref,
	&omap5430_cm_clksel_sys,
	NULL};

reg omap5430_pmi_identication = {
	"PMI_IDENTICATION",
	OMAP5430_PMI_IDENTICATION,
	0xDEADBEEF,
	0};

reg omap5430_pmi_sys_config = {
	"PMI_SYS_CONFIG",
	OMAP5430_PMI_SYS_CONFIG,
	0xDEADBEEF,
	0};

reg omap5430_pmi_status = {
	"PMI_STATUS",
	OMAP5430_PMI_STATUS,
	0xDEADBEEF,
	0};

reg omap5430_pmi_configuration = {
	"PMI_CONFIGURATION",
	OMAP5430_PMI_CONFIGURATION,
	0xDEADBEEF,
	0};

reg omap5430_pmi_class_filtering = {
	"PMI_CLASS_FILTERING",
	OMAP5430_PMI_CLASS_FILTERING,
	0xDEADBEEF,
	0};

reg omap5430_pmi_triggering = {
	"PMI_TRIGGERING",
	OMAP5430_PMI_TRIGGERING,
	0xDEADBEEF,
	0};

reg omap5430_pmi_sampling = {
	"PMI_SAMPLING",
	OMAP5430_PMI_SAMPLING,
	0xDEADBEEF,
	0};

reg *omap5430_instr_prm_mod[OMAP5430_INSTR_PRM_MOD_REGCOUNT + 1] = {
	&omap5430_pmi_identication,
	&omap5430_pmi_sys_config,
	&omap5430_pmi_status,
	&omap5430_pmi_configuration,
	&omap5430_pmi_class_filtering,
	&omap5430_pmi_triggering,
	&omap5430_pmi_sampling,
	NULL};

reg omap5430_pm_iva_pwrstctrl = {
	"PM_IVA_PWRSTCTRL",
	OMAP5430_PM_IVA_PWRSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_pm_iva_pwrstst = {
	"PM_IVA_PWRSTST",
	OMAP5430_PM_IVA_PWRSTST,
	0xDEADBEEF,
	0};

reg omap5430_rm_iva_rstctrl = {
	"RM_IVA_RSTCTRL",
	OMAP5430_RM_IVA_RSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_rm_iva_rstst = {
	"RM_IVA_RSTST",
	OMAP5430_RM_IVA_RSTST,
	0xDEADBEEF,
	0};

reg omap5430_rm_iva_iva_context = {
	"RM_IVA_IVA_CONTEXT",
	OMAP5430_RM_IVA_IVA_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_iva_sl2_context = {
	"RM_IVA_SL2_CONTEXT",
	OMAP5430_RM_IVA_SL2_CONTEXT,
	0xDEADBEEF,
	0};

reg *omap5430_iva_prm_mod[OMAP5430_IVA_PRM_MOD_REGCOUNT + 1] = {
	&omap5430_pm_iva_pwrstctrl,
	&omap5430_pm_iva_pwrstst,
	&omap5430_rm_iva_rstctrl,
	&omap5430_rm_iva_rstst,
	&omap5430_rm_iva_iva_context,
	&omap5430_rm_iva_sl2_context,
	NULL};

reg omap5430_pm_core_pwrstctrl = {
	"PM_CORE_PWRSTCTRL",
	OMAP5430_PM_CORE_PWRSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_pm_core_pwrstst = {
	"PM_CORE_PWRSTST",
	OMAP5430_PM_CORE_PWRSTST,
	0xDEADBEEF,
	0};

reg omap5430_rm_l3main1_l3_main_1_context = {
	"RM_L3MAIN1_L3_MAIN_1_CONTEXT",
	OMAP5430_RM_L3MAIN1_L3_MAIN_1_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_l3main2_l3_main_2_context = {
	"RM_L3MAIN2_L3_MAIN_2_CONTEXT",
	OMAP5430_RM_L3MAIN2_L3_MAIN_2_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_l3main2_gpmc_context = {
	"RM_L3MAIN2_GPMC_CONTEXT",
	OMAP5430_RM_L3MAIN2_GPMC_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_l3main2_ocmc_ram_context = {
	"RM_L3MAIN2_OCMC_RAM_CONTEXT",
	OMAP5430_RM_L3MAIN2_OCMC_RAM_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_ipu_rstctrl = {
	"RM_IPU_RSTCTRL",
	OMAP5430_RM_IPU_RSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_rm_ipu_rstst = {
	"RM_IPU_RSTST",
	OMAP5430_RM_IPU_RSTST,
	0xDEADBEEF,
	0};

reg omap5430_rm_ipu_ipu_context = {
	"RM_IPU_IPU_CONTEXT",
	OMAP5430_RM_IPU_IPU_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_dma_dma_system_context = {
	"RM_DMA_DMA_SYSTEM_CONTEXT",
	OMAP5430_RM_DMA_DMA_SYSTEM_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_emif_dmm_context = {
	"RM_EMIF_DMM_CONTEXT",
	OMAP5430_RM_EMIF_DMM_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_emif_emif_fw_context = {
	"RM_EMIF_EMIF_FW_CONTEXT",
	OMAP5430_RM_EMIF_EMIF_FW_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_emif_emif1_context = {
	"RM_EMIF_EMIF1_CONTEXT",
	OMAP5430_RM_EMIF_EMIF1_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_emif_emif2_context = {
	"RM_EMIF_EMIF2_CONTEXT",
	OMAP5430_RM_EMIF_EMIF2_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_emif_emif_dll_context = {
	"RM_EMIF_EMIF_DLL_CONTEXT",
	OMAP5430_RM_EMIF_EMIF_DLL_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_c2c_c2c_context = {
	"RM_C2C_C2C_CONTEXT",
	OMAP5430_RM_C2C_C2C_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_c2c_modem_icr_context = {
	"RM_C2C_MODEM_ICR_CONTEXT",
	OMAP5430_RM_C2C_MODEM_ICR_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_c2c_c2c_ocp_fw_context = {
	"RM_C2C_C2C_OCP_FW_CONTEXT",
	OMAP5430_RM_C2C_C2C_OCP_FW_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4cfg_l4_cfg_context = {
	"RM_L4CFG_L4_CFG_CONTEXT",
	OMAP5430_RM_L4CFG_L4_CFG_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4cfg_spinlock_context = {
	"RM_L4CFG_SPINLOCK_CONTEXT",
	OMAP5430_RM_L4CFG_SPINLOCK_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4cfg_mailbox_context = {
	"RM_L4CFG_MAILBOX_CONTEXT",
	OMAP5430_RM_L4CFG_MAILBOX_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4cfg_sar_rom_context = {
	"RM_L4CFG_SAR_ROM_CONTEXT",
	OMAP5430_RM_L4CFG_SAR_ROM_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4cfg_ocp2scp2_context = {
	"RM_L4CFG_OCP2SCP2_CONTEXT",
	OMAP5430_RM_L4CFG_OCP2SCP2_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_l3instr_l3_main_3_context = {
	"RM_L3INSTR_L3_MAIN_3_CONTEXT",
	OMAP5430_RM_L3INSTR_L3_MAIN_3_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_l3instr_l3_instr_context = {
	"RM_L3INSTR_L3_INSTR_CONTEXT",
	OMAP5430_RM_L3INSTR_L3_INSTR_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_l3instr_ocp_wp_noc_context = {
	"RM_L3INSTR_OCP_WP_NOC_CONTEXT",
	OMAP5430_RM_L3INSTR_OCP_WP_NOC_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_mipiext_lli_context = {
	"RM_MIPIEXT_LLI_CONTEXT",
	OMAP5430_RM_MIPIEXT_LLI_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_mipiext_lli_ocp_fw_context = {
	"RM_MIPIEXT_LLI_OCP_FW_CONTEXT",
	OMAP5430_RM_MIPIEXT_LLI_OCP_FW_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_mipiext_mphy_context = {
	"RM_MIPIEXT_MPHY_CONTEXT",
	OMAP5430_RM_MIPIEXT_MPHY_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_timer10_wkdep = {
	"PM_L4PER_TIMER10_WKDEP",
	OMAP5430_PM_L4PER_TIMER10_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_timer10_context = {
	"RM_L4PER_TIMER10_CONTEXT",
	OMAP5430_RM_L4PER_TIMER10_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_timer11_wkdep = {
	"PM_L4PER_TIMER11_WKDEP",
	OMAP5430_PM_L4PER_TIMER11_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_timer11_context = {
	"RM_L4PER_TIMER11_CONTEXT",
	OMAP5430_RM_L4PER_TIMER11_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_timer2_wkdep = {
	"PM_L4PER_TIMER2_WKDEP",
	OMAP5430_PM_L4PER_TIMER2_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_timer2_context = {
	"RM_L4PER_TIMER2_CONTEXT",
	OMAP5430_RM_L4PER_TIMER2_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_timer3_wkdep = {
	"PM_L4PER_TIMER3_WKDEP",
	OMAP5430_PM_L4PER_TIMER3_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_timer3_context = {
	"RM_L4PER_TIMER3_CONTEXT",
	OMAP5430_RM_L4PER_TIMER3_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_timer4_wkdep = {
	"PM_L4PER_TIMER4_WKDEP",
	OMAP5430_PM_L4PER_TIMER4_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_timer4_context = {
	"RM_L4PER_TIMER4_CONTEXT",
	OMAP5430_RM_L4PER_TIMER4_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_timer9_wkdep = {
	"PM_L4PER_TIMER9_WKDEP",
	OMAP5430_PM_L4PER_TIMER9_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_timer9_context = {
	"RM_L4PER_TIMER9_CONTEXT",
	OMAP5430_RM_L4PER_TIMER9_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_elm_context = {
	"RM_L4PER_ELM_CONTEXT",
	OMAP5430_RM_L4PER_ELM_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_gpio2_wkdep = {
	"PM_L4PER_GPIO2_WKDEP",
	OMAP5430_PM_L4PER_GPIO2_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_gpio2_context = {
	"RM_L4PER_GPIO2_CONTEXT",
	OMAP5430_RM_L4PER_GPIO2_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_gpio3_wkdep = {
	"PM_L4PER_GPIO3_WKDEP",
	OMAP5430_PM_L4PER_GPIO3_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_gpio3_context = {
	"RM_L4PER_GPIO3_CONTEXT",
	OMAP5430_RM_L4PER_GPIO3_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_gpio4_wkdep = {
	"PM_L4PER_GPIO4_WKDEP",
	OMAP5430_PM_L4PER_GPIO4_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_gpio4_context = {
	"RM_L4PER_GPIO4_CONTEXT",
	OMAP5430_RM_L4PER_GPIO4_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_gpio5_wkdep = {
	"PM_L4PER_GPIO5_WKDEP",
	OMAP5430_PM_L4PER_GPIO5_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_gpio5_context = {
	"RM_L4PER_GPIO5_CONTEXT",
	OMAP5430_RM_L4PER_GPIO5_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_gpio6_wkdep = {
	"PM_L4PER_GPIO6_WKDEP",
	OMAP5430_PM_L4PER_GPIO6_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_gpio6_context = {
	"RM_L4PER_GPIO6_CONTEXT",
	OMAP5430_RM_L4PER_GPIO6_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_hdq1w_context = {
	"RM_L4PER_HDQ1W_CONTEXT",
	OMAP5430_RM_L4PER_HDQ1W_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_i2c1_wkdep = {
	"PM_L4PER_I2C1_WKDEP",
	OMAP5430_PM_L4PER_I2C1_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_i2c1_context = {
	"RM_L4PER_I2C1_CONTEXT",
	OMAP5430_RM_L4PER_I2C1_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_i2c2_wkdep = {
	"PM_L4PER_I2C2_WKDEP",
	OMAP5430_PM_L4PER_I2C2_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_i2c2_context = {
	"RM_L4PER_I2C2_CONTEXT",
	OMAP5430_RM_L4PER_I2C2_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_i2c3_wkdep = {
	"PM_L4PER_I2C3_WKDEP",
	OMAP5430_PM_L4PER_I2C3_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_i2c3_context = {
	"RM_L4PER_I2C3_CONTEXT",
	OMAP5430_RM_L4PER_I2C3_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_i2c4_wkdep = {
	"PM_L4PER_I2C4_WKDEP",
	OMAP5430_PM_L4PER_I2C4_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_i2c4_context = {
	"RM_L4PER_I2C4_CONTEXT",
	OMAP5430_RM_L4PER_I2C4_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_l4_per_context = {
	"RM_L4PER_L4_PER_CONTEXT",
	OMAP5430_RM_L4PER_L4_PER_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_mcspi1_wkdep = {
	"PM_L4PER_MCSPI1_WKDEP",
	OMAP5430_PM_L4PER_MCSPI1_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_mcspi1_context = {
	"RM_L4PER_MCSPI1_CONTEXT",
	OMAP5430_RM_L4PER_MCSPI1_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_mcspi2_wkdep = {
	"PM_L4PER_MCSPI2_WKDEP",
	OMAP5430_PM_L4PER_MCSPI2_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_mcspi2_context = {
	"RM_L4PER_MCSPI2_CONTEXT",
	OMAP5430_RM_L4PER_MCSPI2_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_mcspi3_wkdep = {
	"PM_L4PER_MCSPI3_WKDEP",
	OMAP5430_PM_L4PER_MCSPI3_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_mcspi3_context = {
	"RM_L4PER_MCSPI3_CONTEXT",
	OMAP5430_RM_L4PER_MCSPI3_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_mcspi4_wkdep = {
	"PM_L4PER_MCSPI4_WKDEP",
	OMAP5430_PM_L4PER_MCSPI4_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_mcspi4_context = {
	"RM_L4PER_MCSPI4_CONTEXT",
	OMAP5430_RM_L4PER_MCSPI4_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_gpio7_wkdep = {
	"PM_L4PER_GPIO7_WKDEP",
	OMAP5430_PM_L4PER_GPIO7_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_gpio7_context = {
	"RM_L4PER_GPIO7_CONTEXT",
	OMAP5430_RM_L4PER_GPIO7_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_gpio8_wkdep = {
	"PM_L4PER_GPIO8_WKDEP",
	OMAP5430_PM_L4PER_GPIO8_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_gpio8_context = {
	"RM_L4PER_GPIO8_CONTEXT",
	OMAP5430_RM_L4PER_GPIO8_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_mmc3_wkdep = {
	"PM_L4PER_MMC3_WKDEP",
	OMAP5430_PM_L4PER_MMC3_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_mmc3_context = {
	"RM_L4PER_MMC3_CONTEXT",
	OMAP5430_RM_L4PER_MMC3_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_mmc4_wkdep = {
	"PM_L4PER_MMC4_WKDEP",
	OMAP5430_PM_L4PER_MMC4_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_mmc4_context = {
	"RM_L4PER_MMC4_CONTEXT",
	OMAP5430_RM_L4PER_MMC4_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_uart1_wkdep = {
	"PM_L4PER_UART1_WKDEP",
	OMAP5430_PM_L4PER_UART1_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_uart1_context = {
	"RM_L4PER_UART1_CONTEXT",
	OMAP5430_RM_L4PER_UART1_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_uart2_wkdep = {
	"PM_L4PER_UART2_WKDEP",
	OMAP5430_PM_L4PER_UART2_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_uart2_context = {
	"RM_L4PER_UART2_CONTEXT",
	OMAP5430_RM_L4PER_UART2_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_uart3_wkdep = {
	"PM_L4PER_UART3_WKDEP",
	OMAP5430_PM_L4PER_UART3_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_uart3_context = {
	"RM_L4PER_UART3_CONTEXT",
	OMAP5430_RM_L4PER_UART3_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_uart4_context = {
	"RM_L4PER_UART4_CONTEXT",
	OMAP5430_RM_L4PER_UART4_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_uart4_wkdep = {
	"PM_L4PER_UART4_WKDEP",
	OMAP5430_PM_L4PER_UART4_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_mmc5_wkdep = {
	"PM_L4PER_MMC5_WKDEP",
	OMAP5430_PM_L4PER_MMC5_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_mmc5_context = {
	"RM_L4PER_MMC5_CONTEXT",
	OMAP5430_RM_L4PER_MMC5_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_i2c5_wkdep = {
	"PM_L4PER_I2C5_WKDEP",
	OMAP5430_PM_L4PER_I2C5_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_i2c5_context = {
	"RM_L4PER_I2C5_CONTEXT",
	OMAP5430_RM_L4PER_I2C5_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_uart5_wkdep = {
	"PM_L4PER_UART5_WKDEP",
	OMAP5430_PM_L4PER_UART5_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_uart5_context = {
	"RM_L4PER_UART5_CONTEXT",
	OMAP5430_RM_L4PER_UART5_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l4per_uart6_wkdep = {
	"PM_L4PER_UART6_WKDEP",
	OMAP5430_PM_L4PER_UART6_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4per_uart6_context = {
	"RM_L4PER_UART6_CONTEXT",
	OMAP5430_RM_L4PER_UART6_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4sec_aes1_context = {
	"RM_L4SEC_AES1_CONTEXT",
	OMAP5430_RM_L4SEC_AES1_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4sec_aes2_context = {
	"RM_L4SEC_AES2_CONTEXT",
	OMAP5430_RM_L4SEC_AES2_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4sec_des3des_context = {
	"RM_L4SEC_DES3DES_CONTEXT",
	OMAP5430_RM_L4SEC_DES3DES_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4sec_fpka_context = {
	"RM_L4SEC_FPKA_CONTEXT",
	OMAP5430_RM_L4SEC_FPKA_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4sec_rng_context = {
	"RM_L4SEC_RNG_CONTEXT",
	OMAP5430_RM_L4SEC_RNG_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4sec_sha2md5_context = {
	"RM_L4SEC_SHA2MD5_CONTEXT",
	OMAP5430_RM_L4SEC_SHA2MD5_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_l4sec_dma_crypto_context = {
	"RM_L4SEC_DMA_CRYPTO_CONTEXT",
	OMAP5430_RM_L4SEC_DMA_CRYPTO_CONTEXT,
	0xDEADBEEF,
	0};

reg *omap5430_core_prm_mod[OMAP5430_CORE_PRM_MOD_REGCOUNT + 1] = {
	&omap5430_pm_core_pwrstctrl,
	&omap5430_pm_core_pwrstst,
	&omap5430_rm_l3main1_l3_main_1_context,
	&omap5430_rm_l3main2_l3_main_2_context,
	&omap5430_rm_l3main2_gpmc_context,
	&omap5430_rm_l3main2_ocmc_ram_context,
	&omap5430_rm_ipu_rstctrl,
	&omap5430_rm_ipu_rstst,
	&omap5430_rm_ipu_ipu_context,
	&omap5430_rm_dma_dma_system_context,
	&omap5430_rm_emif_dmm_context,
	&omap5430_rm_emif_emif_fw_context,
	&omap5430_rm_emif_emif1_context,
	&omap5430_rm_emif_emif2_context,
	&omap5430_rm_emif_emif_dll_context,
	&omap5430_rm_c2c_c2c_context,
	&omap5430_rm_c2c_modem_icr_context,
	&omap5430_rm_c2c_c2c_ocp_fw_context,
	&omap5430_rm_l4cfg_l4_cfg_context,
	&omap5430_rm_l4cfg_spinlock_context,
	&omap5430_rm_l4cfg_mailbox_context,
	&omap5430_rm_l4cfg_sar_rom_context,
	&omap5430_rm_l4cfg_ocp2scp2_context,
	&omap5430_rm_l3instr_l3_main_3_context,
	&omap5430_rm_l3instr_l3_instr_context,
	&omap5430_rm_l3instr_ocp_wp_noc_context,
	&omap5430_rm_mipiext_lli_context,
	&omap5430_rm_mipiext_lli_ocp_fw_context,
	&omap5430_rm_mipiext_mphy_context,
	&omap5430_pm_l4per_timer10_wkdep,
	&omap5430_rm_l4per_timer10_context,
	&omap5430_pm_l4per_timer11_wkdep,
	&omap5430_rm_l4per_timer11_context,
	&omap5430_pm_l4per_timer2_wkdep,
	&omap5430_rm_l4per_timer2_context,
	&omap5430_pm_l4per_timer3_wkdep,
	&omap5430_rm_l4per_timer3_context,
	&omap5430_pm_l4per_timer4_wkdep,
	&omap5430_rm_l4per_timer4_context,
	&omap5430_pm_l4per_timer9_wkdep,
	&omap5430_rm_l4per_timer9_context,
	&omap5430_rm_l4per_elm_context,
	&omap5430_pm_l4per_gpio2_wkdep,
	&omap5430_rm_l4per_gpio2_context,
	&omap5430_pm_l4per_gpio3_wkdep,
	&omap5430_rm_l4per_gpio3_context,
	&omap5430_pm_l4per_gpio4_wkdep,
	&omap5430_rm_l4per_gpio4_context,
	&omap5430_pm_l4per_gpio5_wkdep,
	&omap5430_rm_l4per_gpio5_context,
	&omap5430_pm_l4per_gpio6_wkdep,
	&omap5430_rm_l4per_gpio6_context,
	&omap5430_rm_l4per_hdq1w_context,
	&omap5430_pm_l4per_i2c1_wkdep,
	&omap5430_rm_l4per_i2c1_context,
	&omap5430_pm_l4per_i2c2_wkdep,
	&omap5430_rm_l4per_i2c2_context,
	&omap5430_pm_l4per_i2c3_wkdep,
	&omap5430_rm_l4per_i2c3_context,
	&omap5430_pm_l4per_i2c4_wkdep,
	&omap5430_rm_l4per_i2c4_context,
	&omap5430_rm_l4per_l4_per_context,
	&omap5430_pm_l4per_mcspi1_wkdep,
	&omap5430_rm_l4per_mcspi1_context,
	&omap5430_pm_l4per_mcspi2_wkdep,
	&omap5430_rm_l4per_mcspi2_context,
	&omap5430_pm_l4per_mcspi3_wkdep,
	&omap5430_rm_l4per_mcspi3_context,
	&omap5430_pm_l4per_mcspi4_wkdep,
	&omap5430_rm_l4per_mcspi4_context,
	&omap5430_pm_l4per_gpio7_wkdep,
	&omap5430_rm_l4per_gpio7_context,
	&omap5430_pm_l4per_gpio8_wkdep,
	&omap5430_rm_l4per_gpio8_context,
	&omap5430_pm_l4per_mmc3_wkdep,
	&omap5430_rm_l4per_mmc3_context,
	&omap5430_pm_l4per_mmc4_wkdep,
	&omap5430_rm_l4per_mmc4_context,
	&omap5430_pm_l4per_uart1_wkdep,
	&omap5430_rm_l4per_uart1_context,
	&omap5430_pm_l4per_uart2_wkdep,
	&omap5430_rm_l4per_uart2_context,
	&omap5430_pm_l4per_uart3_wkdep,
	&omap5430_rm_l4per_uart3_context,
	&omap5430_rm_l4per_uart4_context,
	&omap5430_pm_l4per_uart4_wkdep,
	&omap5430_pm_l4per_mmc5_wkdep,
	&omap5430_rm_l4per_mmc5_context,
	&omap5430_pm_l4per_i2c5_wkdep,
	&omap5430_rm_l4per_i2c5_context,
	&omap5430_pm_l4per_uart5_wkdep,
	&omap5430_rm_l4per_uart5_context,
	&omap5430_pm_l4per_uart6_wkdep,
	&omap5430_rm_l4per_uart6_context,
	&omap5430_rm_l4sec_aes1_context,
	&omap5430_rm_l4sec_aes2_context,
	&omap5430_rm_l4sec_des3des_context,
	&omap5430_rm_l4sec_fpka_context,
	&omap5430_rm_l4sec_rng_context,
	&omap5430_rm_l4sec_sha2md5_context,
	&omap5430_rm_l4sec_dma_crypto_context,
	NULL};

reg omap5430_pm_emu_pwrstctrl = {
	"PM_EMU_PWRSTCTRL",
	OMAP5430_PM_EMU_PWRSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_pm_emu_pwrstst = {
	"PM_EMU_PWRSTST",
	OMAP5430_PM_EMU_PWRSTST,
	0xDEADBEEF,
	0};

reg omap5430_rm_emu_debugss_context = {
	"RM_EMU_DEBUGSS_CONTEXT",
	OMAP5430_RM_EMU_DEBUGSS_CONTEXT,
	0xDEADBEEF,
	0};

reg *omap5430_emu_prm_mod[OMAP5430_EMU_PRM_MOD_REGCOUNT + 1] = {
	&omap5430_pm_emu_pwrstctrl,
	&omap5430_pm_emu_pwrstst,
	&omap5430_rm_emu_debugss_context,
	NULL};

reg omap5430_pm_mpu_pwrstctrl = {
	"PM_MPU_PWRSTCTRL",
	OMAP5430_PM_MPU_PWRSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_pm_mpu_pwrstst = {
	"PM_MPU_PWRSTST",
	OMAP5430_PM_MPU_PWRSTST,
	0xDEADBEEF,
	0};

reg omap5430_rm_mpu_mpu_context = {
	"RM_MPU_MPU_CONTEXT",
	OMAP5430_RM_MPU_MPU_CONTEXT,
	0xDEADBEEF,
	0};

reg *omap5430_mpu_prm_mod[OMAP5430_MPU_PRM_MOD_REGCOUNT + 1] = {
	&omap5430_pm_mpu_pwrstctrl,
	&omap5430_pm_mpu_pwrstst,
	&omap5430_rm_mpu_mpu_context,
	NULL};

reg omap5430_pm_l3init_pwrstctrl = {
	"PM_L3INIT_PWRSTCTRL",
	OMAP5430_PM_L3INIT_PWRSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_pm_l3init_pwrstst = {
	"PM_L3INIT_PWRSTST",
	OMAP5430_PM_L3INIT_PWRSTST,
	0xDEADBEEF,
	0};

reg omap5430_pm_l3init_mmc1_wkdep = {
	"PM_L3INIT_MMC1_WKDEP",
	OMAP5430_PM_L3INIT_MMC1_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l3init_mmc1_context = {
	"RM_L3INIT_MMC1_CONTEXT",
	OMAP5430_RM_L3INIT_MMC1_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l3init_mmc2_wkdep = {
	"PM_L3INIT_MMC2_WKDEP",
	OMAP5430_PM_L3INIT_MMC2_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l3init_mmc2_context = {
	"RM_L3INIT_MMC2_CONTEXT",
	OMAP5430_RM_L3INIT_MMC2_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l3init_hsi_wkdep = {
	"PM_L3INIT_HSI_WKDEP",
	OMAP5430_PM_L3INIT_HSI_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l3init_hsi_context = {
	"RM_L3INIT_HSI_CONTEXT",
	OMAP5430_RM_L3INIT_HSI_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l3init_unipro2_wkdep = {
	"PM_L3INIT_UNIPRO2_WKDEP",
	OMAP5430_PM_L3INIT_UNIPRO2_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l3init_unipro2_context = {
	"RM_L3INIT_UNIPRO2_CONTEXT",
	OMAP5430_RM_L3INIT_UNIPRO2_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l3init_usb_host_hs_wkdep = {
	"PM_L3INIT_USB_HOST_HS_WKDEP",
	OMAP5430_PM_L3INIT_USB_HOST_HS_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l3init_usb_host_hs_context = {
	"RM_L3INIT_USB_HOST_HS_CONTEXT",
	OMAP5430_RM_L3INIT_USB_HOST_HS_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l3init_usb_tll_hs_wkdep = {
	"PM_L3INIT_USB_TLL_HS_WKDEP",
	OMAP5430_PM_L3INIT_USB_TLL_HS_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l3init_usb_tll_hs_context = {
	"RM_L3INIT_USB_TLL_HS_CONTEXT",
	OMAP5430_RM_L3INIT_USB_TLL_HS_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_l3init_ieee1500_2_ocp_context = {
	"RM_L3INIT_IEEE1500_2_OCP_CONTEXT",
	OMAP5430_RM_L3INIT_IEEE1500_2_OCP_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l3init_sata_wkdep = {
	"PM_L3INIT_SATA_WKDEP",
	OMAP5430_PM_L3INIT_SATA_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l3init_sata_context = {
	"RM_L3INIT_SATA_CONTEXT",
	OMAP5430_RM_L3INIT_SATA_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_l3init_ocp2scp1_context = {
	"RM_L3INIT_OCP2SCP1_CONTEXT",
	OMAP5430_RM_L3INIT_OCP2SCP1_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_rm_l3init_ocp2scp3_context = {
	"RM_L3INIT_OCP2SCP3_CONTEXT",
	OMAP5430_RM_L3INIT_OCP2SCP3_CONTEXT,
	0xDEADBEEF,
	0};

reg omap5430_pm_l3init_usb_otg_ss_wkdep = {
	"PM_L3INIT_USB_OTG_SS_WKDEP",
	OMAP5430_PM_L3INIT_USB_OTG_SS_WKDEP,
	0xDEADBEEF,
	0};

reg omap5430_rm_l3init_usb_otg_ss_context = {
	"RM_L3INIT_USB_OTG_SS_CONTEXT",
	OMAP5430_RM_L3INIT_USB_OTG_SS_CONTEXT,
	0xDEADBEEF,
	0};

reg *omap5430_l3init_prm_mod[OMAP5430_L3INIT_PRM_MOD_REGCOUNT + 1] = {
	&omap5430_pm_l3init_pwrstctrl,
	&omap5430_pm_l3init_pwrstst,
	&omap5430_pm_l3init_mmc1_wkdep,
	&omap5430_rm_l3init_mmc1_context,
	&omap5430_pm_l3init_mmc2_wkdep,
	&omap5430_rm_l3init_mmc2_context,
	&omap5430_pm_l3init_hsi_wkdep,
	&omap5430_rm_l3init_hsi_context,
	&omap5430_pm_l3init_unipro2_wkdep,
	&omap5430_rm_l3init_unipro2_context,
	&omap5430_pm_l3init_usb_host_hs_wkdep,
	&omap5430_rm_l3init_usb_host_hs_context,
	&omap5430_pm_l3init_usb_tll_hs_wkdep,
	&omap5430_rm_l3init_usb_tll_hs_context,
	&omap5430_rm_l3init_ieee1500_2_ocp_context,
	&omap5430_pm_l3init_sata_wkdep,
	&omap5430_rm_l3init_sata_context,
	&omap5430_rm_l3init_ocp2scp1_context,
	&omap5430_rm_l3init_ocp2scp3_context,
	&omap5430_pm_l3init_usb_otg_ss_wkdep,
	&omap5430_rm_l3init_usb_otg_ss_context,
	NULL};

reg omap5430_pm_cpu0_pwrstctrl = {
	"PM_CPU0_PWRSTCTRL",
	OMAP5430_PM_CPU0_PWRSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_pm_cpu0_pwrstst = {
	"PM_CPU0_PWRSTST",
	OMAP5430_PM_CPU0_PWRSTST,
	0xDEADBEEF,
	0};

reg omap5430_rm_cpu0_cpu0_rstctrl = {
	"RM_CPU0_CPU0_RSTCTRL",
	OMAP5430_RM_CPU0_CPU0_RSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_rm_cpu0_cpu0_rstst = {
	"RM_CPU0_CPU0_RSTST",
	OMAP5430_RM_CPU0_CPU0_RSTST,
	0xDEADBEEF,
	0};

reg omap5430_rm_cpu0_cpu0_context = {
	"RM_CPU0_CPU0_CONTEXT",
	OMAP5430_RM_CPU0_CPU0_CONTEXT,
	0xDEADBEEF,
	0};

reg *omap5430_prcm_mpu_prm_c0_mod[OMAP5430_PRCM_MPU_PRM_C0_MOD_REGCOUNT + 1] = {
	&omap5430_pm_cpu0_pwrstctrl,
	&omap5430_pm_cpu0_pwrstst,
	&omap5430_rm_cpu0_cpu0_rstctrl,
	&omap5430_rm_cpu0_cpu0_rstst,
	&omap5430_rm_cpu0_cpu0_context,
	NULL};

reg omap5430_pm_cpu1_pwrstctrl = {
	"PM_CPU1_PWRSTCTRL",
	OMAP5430_PM_CPU1_PWRSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_pm_cpu1_pwrstst = {
	"PM_CPU1_PWRSTST",
	OMAP5430_PM_CPU1_PWRSTST,
	0xDEADBEEF,
	0};

reg omap5430_rm_cpu1_cpu1_rstctrl = {
	"RM_CPU1_CPU1_RSTCTRL",
	OMAP5430_RM_CPU1_CPU1_RSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_rm_cpu1_cpu1_rstst = {
	"RM_CPU1_CPU1_RSTST",
	OMAP5430_RM_CPU1_CPU1_RSTST,
	0xDEADBEEF,
	0};

reg omap5430_rm_cpu1_cpu1_context = {
	"RM_CPU1_CPU1_CONTEXT",
	OMAP5430_RM_CPU1_CPU1_CONTEXT,
	0xDEADBEEF,
	0};

reg *omap5430_prcm_mpu_prm_c1_mod[OMAP5430_PRCM_MPU_PRM_C1_MOD_REGCOUNT + 1] = {
	&omap5430_pm_cpu1_pwrstctrl,
	&omap5430_pm_cpu1_pwrstst,
	&omap5430_rm_cpu1_cpu1_rstctrl,
	&omap5430_rm_cpu1_cpu1_rstst,
	&omap5430_rm_cpu1_cpu1_context,
	NULL};

reg **prm54xx_mods[PRM54XX_MODS_COUNT + 1] = {
	(reg **) &omap5430_dss_prm_mod,
	(reg **) &omap5430_wkupaon_prm_mod,
	(reg **) &omap5430_ocp_socket_prm_mod,
	(reg **) &omap5430_cam_prm_mod,
	(reg **) &omap5430_dsp_prm_mod,
	(reg **) &omap5430_device_prm_mod,
	(reg **) &omap5430_abe_prm_mod,
	(reg **) &omap5430_gpu_prm_mod,
	(reg **) &omap5430_coreaon_prm_mod,
	(reg **) &omap5430_custefuse_prm_mod,
	(reg **) &omap5430_ckgen_prm_mod,
	(reg **) &omap5430_instr_prm_mod,
	(reg **) &omap5430_iva_prm_mod,
	(reg **) &omap5430_emu_prm_mod,
	(reg **) &omap5430_mpu_prm_mod,
	(reg **) &omap5430_l3init_prm_mod,
	(reg **) &omap5430_core_prm_mod,
	NULL,
	(reg **) &omap5430_prcm_mpu_prm_c0_mod,
	(reg **) &omap5430_prcm_mpu_prm_c1_mod,
	NULL};
