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


#ifndef __PRM54XX_DEFS_H__
#define __PRM54XX_DEFS_H__


#include <reg.h>
#include <prm54xxes1-defs.h>


#define OMAP5430_PM_DSS_PWRSTCTRL		0x4ae07400
extern reg omap5430_pm_dss_pwrstctrl;
#define OMAP5430_PM_DSS_PWRSTST			0x4ae07404
extern reg omap5430_pm_dss_pwrstst;
#define OMAP5430_PM_DSS_DSS_WKDEP		0x4ae07420
extern reg omap5430_pm_dss_dss_wkdep;
#define OMAP5430_RM_DSS_DSS_CONTEXT		0x4ae07424
extern reg omap5430_rm_dss_dss_context;
#define OMAP5430_RM_DSS_BB2D_CONTEXT		0x4ae07434
extern reg omap5430_rm_dss_bb2d_context;
#define OMAP5430_DSS_PRM_MOD_REGCOUNT		5
extern reg *omap5430_dss_prm_mod[OMAP5430_DSS_PRM_MOD_REGCOUNT + 1];

#define OMAP5430_RM_WKUPAON_L4_WKUP_CONTEXT	0x4ae07824
extern reg omap5430_rm_wkupaon_l4_wkup_context;
#define OMAP5430_PM_WKUPAON_WD_TIMER2_WKDEP	0x4ae07830
extern reg omap5430_pm_wkupaon_wd_timer2_wkdep;
#define OMAP5430_RM_WKUPAON_WD_TIMER2_CONTEXT	0x4ae07834
extern reg omap5430_rm_wkupaon_wd_timer2_context;
#define OMAP5430_PM_WKUPAON_GPIO1_WKDEP		0x4ae07838
extern reg omap5430_pm_wkupaon_gpio1_wkdep;
#define OMAP5430_RM_WKUPAON_GPIO1_CONTEXT	0x4ae0783c
extern reg omap5430_rm_wkupaon_gpio1_context;
#define OMAP5430_PM_WKUPAON_TIMER1_WKDEP	0x4ae07840
extern reg omap5430_pm_wkupaon_timer1_wkdep;
#define OMAP5430_RM_WKUPAON_TIMER1_CONTEXT	0x4ae07844
extern reg omap5430_rm_wkupaon_timer1_context;
#define OMAP5430_RM_WKUPAON_COUNTER_32K_CONTEXT	0x4ae07854
extern reg omap5430_rm_wkupaon_counter_32k_context;
#define OMAP5430_RM_WKUPAON_SAR_RAM_CONTEXT	0x4ae07864
extern reg omap5430_rm_wkupaon_sar_ram_context;
#define OMAP5430_PM_WKUPAON_KBD_WKDEP		0x4ae07878
extern reg omap5430_pm_wkupaon_kbd_wkdep;
#define OMAP5430_RM_WKUPAON_KBD_CONTEXT		0x4ae0787c
extern reg omap5430_rm_wkupaon_kbd_context;
#define OMAP5430_WKUPAON_PRM_MOD_REGCOUNT	11
extern reg *omap5430_wkupaon_prm_mod[OMAP5430_WKUPAON_PRM_MOD_REGCOUNT + 1];

#define OMAP5430_REVISION_PRM			0x4ae06000
extern reg omap5430_revision_prm;
#define OMAP5430_PRM_IRQSTATUS_MPU		0x4ae06010
extern reg omap5430_prm_irqstatus_mpu;
#define OMAP5430_PRM_IRQSTATUS_MPU_2		0x4ae06014
extern reg omap5430_prm_irqstatus_mpu_2;
#define OMAP5430_PRM_IRQENABLE_MPU		0x4ae06018
extern reg omap5430_prm_irqenable_mpu;
#define OMAP5430_PRM_IRQENABLE_MPU_2		0x4ae0601c
extern reg omap5430_prm_irqenable_mpu_2;
#define OMAP5430_PRM_IRQSTATUS_IPU		0x4ae06020
extern reg omap5430_prm_irqstatus_ipu;
#define OMAP5430_PRM_IRQENABLE_IPU		0x4ae06028
extern reg omap5430_prm_irqenable_ipu;
#define OMAP5430_PRM_IRQSTATUS_DSP		0x4ae06030
extern reg omap5430_prm_irqstatus_dsp;
#define OMAP5430_PRM_IRQENABLE_DSP		0x4ae06038
extern reg omap5430_prm_irqenable_dsp;
#define OMAP5430_CM_PRM_PROFILING_CLKCTRL	0x4ae06040
extern reg omap5430_cm_prm_profiling_clkctrl;
#define OMAP5430_PRM_DEBUG_CFG			0x4ae06080
extern reg omap5430_prm_debug_cfg;
#define OMAP5430_OCP_SOCKET_PRM_MOD_REGCOUNT	11
extern reg *omap5430_ocp_socket_prm_mod[OMAP5430_OCP_SOCKET_PRM_MOD_REGCOUNT + 1];

#define OMAP5430_PM_CAM_PWRSTCTRL		0x4ae07300
extern reg omap5430_pm_cam_pwrstctrl;
#define OMAP5430_PM_CAM_PWRSTST			0x4ae07304
extern reg omap5430_pm_cam_pwrstst;
#define OMAP5430_RM_CAM_ISS_CONTEXT		0x4ae07324
extern reg omap5430_rm_cam_iss_context;
#define OMAP5430_RM_CAM_FDIF_CONTEXT		0x4ae0732c
extern reg omap5430_rm_cam_fdif_context;
#define OMAP5430_RM_CAM_CAL_CONTEXT		0x4ae07334
extern reg omap5430_rm_cam_cal_context;
#define OMAP5430_CAM_PRM_MOD_REGCOUNT		5
extern reg *omap5430_cam_prm_mod[OMAP5430_CAM_PRM_MOD_REGCOUNT + 1];

#define OMAP5430_PM_DSP_PWRSTCTRL		0x4ae06400
extern reg omap5430_pm_dsp_pwrstctrl;
#define OMAP5430_PM_DSP_PWRSTST			0x4ae06404
extern reg omap5430_pm_dsp_pwrstst;
#define OMAP5430_RM_DSP_RSTCTRL			0x4ae06410
extern reg omap5430_rm_dsp_rstctrl;
#define OMAP5430_RM_DSP_RSTST			0x4ae06414
extern reg omap5430_rm_dsp_rstst;
#define OMAP5430_RM_DSP_DSP_CONTEXT		0x4ae06424
extern reg omap5430_rm_dsp_dsp_context;
#define OMAP5430_DSP_PRM_MOD_REGCOUNT		5
extern reg *omap5430_dsp_prm_mod[OMAP5430_DSP_PRM_MOD_REGCOUNT + 1];

#define OMAP5430_PRM_RSTCTRL			0x4ae07c00
extern reg omap5430_prm_rstctrl;
#define OMAP5430_PRM_RSTST			0x4ae07c04
extern reg omap5430_prm_rstst;
#define OMAP5430_PRM_RSTTIME			0x4ae07c08
extern reg omap5430_prm_rsttime;
#define OMAP5430_PRM_CLKREQCTRL			0x4ae07c0c
extern reg omap5430_prm_clkreqctrl;
#define OMAP5430_PRM_VOLTCTRL			0x4ae07c10
extern reg omap5430_prm_voltctrl;
#define OMAP5430_PRM_PWRREQCTRL			0x4ae07c14
extern reg omap5430_prm_pwrreqctrl;
#define OMAP5430_PRM_PSCON_COUNT		0x4ae07c18
extern reg omap5430_prm_pscon_count;
#define OMAP5430_PRM_IO_COUNT			0x4ae07c1c
extern reg omap5430_prm_io_count;
#define OMAP5430_PRM_IO_PMCTRL			0x4ae07c20
extern reg omap5430_prm_io_pmctrl;
#define OMAP5430_PRM_VOLTSETUP_WARMRESET	0x4ae07c24
extern reg omap5430_prm_voltsetup_warmreset;
#define OMAP5430_PRM_VOLTSETUP_CORE_OFF		0x4ae07c28
extern reg omap5430_prm_voltsetup_core_off;
#define OMAP5430_PRM_VOLTSETUP_MPU_OFF		0x4ae07c2c
extern reg omap5430_prm_voltsetup_mpu_off;
#define OMAP5430_PRM_VOLTSETUP_MM_OFF		0x4ae07c30
extern reg omap5430_prm_voltsetup_mm_off;
#define OMAP5430_PRM_VOLTSETUP_CORE_RET_SLEEP	0x4ae07c34
extern reg omap5430_prm_voltsetup_core_ret_sleep;
#define OMAP5430_PRM_VOLTSETUP_MPU_RET_SLEEP	0x4ae07c38
extern reg omap5430_prm_voltsetup_mpu_ret_sleep;
#define OMAP5430_PRM_VOLTSETUP_MM_RET_SLEEP	0x4ae07c3c
extern reg omap5430_prm_voltsetup_mm_ret_sleep;
#define OMAP5430_PRM_VP_CORE_CONFIG		0x4ae07c40
extern reg omap5430_prm_vp_core_config;
#define OMAP5430_PRM_VP_CORE_STATUS		0x4ae07c44
extern reg omap5430_prm_vp_core_status;
#define OMAP5430_PRM_VP_CORE_VLIMITTO		0x4ae07c48
extern reg omap5430_prm_vp_core_vlimitto;
#define OMAP5430_PRM_VP_CORE_VOLTAGE		0x4ae07c4c
extern reg omap5430_prm_vp_core_voltage;
#define OMAP5430_PRM_VP_CORE_VSTEPMAX		0x4ae07c50
extern reg omap5430_prm_vp_core_vstepmax;
#define OMAP5430_PRM_VP_CORE_VSTEPMIN		0x4ae07c54
extern reg omap5430_prm_vp_core_vstepmin;
#define OMAP5430_PRM_VP_MPU_CONFIG		0x4ae07c58
extern reg omap5430_prm_vp_mpu_config;
#define OMAP5430_PRM_VP_MPU_STATUS		0x4ae07c5c
extern reg omap5430_prm_vp_mpu_status;
#define OMAP5430_PRM_VP_MPU_VLIMITTO		0x4ae07c60
extern reg omap5430_prm_vp_mpu_vlimitto;
#define OMAP5430_PRM_VP_MPU_VOLTAGE		0x4ae07c64
extern reg omap5430_prm_vp_mpu_voltage;
#define OMAP5430_PRM_VP_MPU_VSTEPMAX		0x4ae07c68
extern reg omap5430_prm_vp_mpu_vstepmax;
#define OMAP5430_PRM_VP_MPU_VSTEPMIN		0x4ae07c6c
extern reg omap5430_prm_vp_mpu_vstepmin;
#define OMAP5430_PRM_VP_MM_CONFIG		0x4ae07c70
extern reg omap5430_prm_vp_mm_config;
#define OMAP5430_PRM_VP_MM_STATUS		0x4ae07c74
extern reg omap5430_prm_vp_mm_status;
#define OMAP5430_PRM_VP_MM_VLIMITTO		0x4ae07c78
extern reg omap5430_prm_vp_mm_vlimitto;
#define OMAP5430_PRM_VP_MM_VOLTAGE		0x4ae07c7c
extern reg omap5430_prm_vp_mm_voltage;
#define OMAP5430_PRM_VP_MM_VSTEPMAX		0x4ae07c80
extern reg omap5430_prm_vp_mm_vstepmax;
#define OMAP5430_PRM_VP_MM_VSTEPMIN		0x4ae07c84
extern reg omap5430_prm_vp_mm_vstepmin;
#define OMAP5430_PRM_VC_SMPS_CORE_CONFIG	0x4ae07c88
extern reg omap5430_prm_vc_smps_core_config;
#define OMAP5430_PRM_VC_SMPS_MM_CONFIG		0x4ae07c8c
extern reg omap5430_prm_vc_smps_mm_config;
#define OMAP5430_PRM_VC_SMPS_MPU_CONFIG		0x4ae07c90
extern reg omap5430_prm_vc_smps_mpu_config;
#define OMAP5430_PRM_VC_VAL_CMD_VDD_CORE_L	0x4ae07c94
extern reg omap5430_prm_vc_val_cmd_vdd_core_l;
#define OMAP5430_PRM_VC_VAL_CMD_VDD_MM_L	0x4ae07c98
extern reg omap5430_prm_vc_val_cmd_vdd_mm_l;
#define OMAP5430_PRM_VC_VAL_CMD_VDD_MPU_L	0x4ae07c9c
extern reg omap5430_prm_vc_val_cmd_vdd_mpu_l;
#define OMAP5430_PRM_VC_VAL_BYPASS		0x4ae07ca0
extern reg omap5430_prm_vc_val_bypass;
#define OMAP5430_PRM_VC_CORE_ERRST		0x4ae07ca4
extern reg omap5430_prm_vc_core_errst;
#define OMAP5430_PRM_VC_MM_ERRST		0x4ae07ca8
extern reg omap5430_prm_vc_mm_errst;
#define OMAP5430_PRM_VC_MPU_ERRST		0x4ae07cac
extern reg omap5430_prm_vc_mpu_errst;
#define OMAP5430_PRM_VC_BYPASS_ERRST		0x4ae07cb0
extern reg omap5430_prm_vc_bypass_errst;
#define OMAP5430_PRM_VC_CFG_I2C_MODE		0x4ae07cb4
extern reg omap5430_prm_vc_cfg_i2c_mode;
#define OMAP5430_PRM_VC_CFG_I2C_CLK		0x4ae07cb8
extern reg omap5430_prm_vc_cfg_i2c_clk;
#define OMAP5430_PRM_SRAM_COUNT			0x4ae07cbc
extern reg omap5430_prm_sram_count;
#define OMAP5430_PRM_SLDO_CORE_SETUP		0x4ae07cc4
extern reg omap5430_prm_sldo_core_setup;
#define OMAP5430_PRM_SLDO_CORE_CTRL		0x4ae07cc8
extern reg omap5430_prm_sldo_core_ctrl;
#define OMAP5430_PRM_SLDO_MPU_SETUP		0x4ae07ccc
extern reg omap5430_prm_sldo_mpu_setup;
#define OMAP5430_PRM_SLDO_MPU_CTRL		0x4ae07cd0
extern reg omap5430_prm_sldo_mpu_ctrl;
#define OMAP5430_PRM_SLDO_MM_SETUP		0x4ae07cd4
extern reg omap5430_prm_sldo_mm_setup;
#define OMAP5430_PRM_SLDO_MM_CTRL		0x4ae07cd8
extern reg omap5430_prm_sldo_mm_ctrl;
#define OMAP5430_PRM_ABBLDO_MPU_SETUP		0x4ae07cdc
extern reg omap5430_prm_abbldo_mpu_setup;
#define OMAP5430_PRM_ABBLDO_MPU_CTRL		0x4ae07ce0
extern reg omap5430_prm_abbldo_mpu_ctrl;
#define OMAP5430_PRM_ABBLDO_MM_SETUP		0x4ae07ce4
extern reg omap5430_prm_abbldo_mm_setup;
#define OMAP5430_PRM_ABBLDO_MM_CTRL		0x4ae07ce8
extern reg omap5430_prm_abbldo_mm_ctrl;
#define OMAP5430_PRM_BANDGAP_SETUP		0x4ae07cec
extern reg omap5430_prm_bandgap_setup;
#define OMAP5430_PRM_DEVICE_OFF_CTRL		0x4ae07cf0
extern reg omap5430_prm_device_off_ctrl;
#define OMAP5430_PRM_PHASE1_CNDP		0x4ae07cf4
extern reg omap5430_prm_phase1_cndp;
#define OMAP5430_PRM_PHASE2A_CNDP		0x4ae07cf8
extern reg omap5430_prm_phase2a_cndp;
#define OMAP5430_PRM_PHASE2B_CNDP		0x4ae07cfc
extern reg omap5430_prm_phase2b_cndp;
#define OMAP5430_PRM_MODEM_IF_CTRL		0x4ae07d00
extern reg omap5430_prm_modem_if_ctrl;
#define OMAP5430_PRM_VOLTST_MPU			0x4ae07d10
extern reg omap5430_prm_voltst_mpu;
#define OMAP5430_PRM_VOLTST_MM			0x4ae07d14
extern reg omap5430_prm_voltst_mm;
#define OMAP5430_DEVICE_PRM_MOD_REGCOUNT	66
extern reg *omap5430_device_prm_mod[OMAP5430_DEVICE_PRM_MOD_REGCOUNT + 1];

#define OMAP5430_PM_ABE_PWRSTCTRL		0x4ae06500
extern reg omap5430_pm_abe_pwrstctrl;
#define OMAP5430_PM_ABE_PWRSTST			0x4ae06504
extern reg omap5430_pm_abe_pwrstst;
#define OMAP5430_RM_ABE_AESS_CONTEXT		0x4ae0652c
extern reg omap5430_rm_abe_aess_context;
#define OMAP5430_PM_ABE_MCPDM_WKDEP		0x4ae06530
extern reg omap5430_pm_abe_mcpdm_wkdep;
#define OMAP5430_RM_ABE_MCPDM_CONTEXT		0x4ae06534
extern reg omap5430_rm_abe_mcpdm_context;
#define OMAP5430_PM_ABE_DMIC_WKDEP		0x4ae06538
extern reg omap5430_pm_abe_dmic_wkdep;
#define OMAP5430_RM_ABE_DMIC_CONTEXT		0x4ae0653c
extern reg omap5430_rm_abe_dmic_context;
#define OMAP5430_PM_ABE_MCASP_WKDEP		0x4ae06540
extern reg omap5430_pm_abe_mcasp_wkdep;
#define OMAP5430_RM_ABE_MCASP_CONTEXT		0x4ae06544
extern reg omap5430_rm_abe_mcasp_context;
#define OMAP5430_PM_ABE_MCBSP1_WKDEP		0x4ae06548
extern reg omap5430_pm_abe_mcbsp1_wkdep;
#define OMAP5430_RM_ABE_MCBSP1_CONTEXT		0x4ae0654c
extern reg omap5430_rm_abe_mcbsp1_context;
#define OMAP5430_PM_ABE_MCBSP2_WKDEP		0x4ae06550
extern reg omap5430_pm_abe_mcbsp2_wkdep;
#define OMAP5430_RM_ABE_MCBSP2_CONTEXT		0x4ae06554
extern reg omap5430_rm_abe_mcbsp2_context;
#define OMAP5430_PM_ABE_MCBSP3_WKDEP		0x4ae06558
extern reg omap5430_pm_abe_mcbsp3_wkdep;
#define OMAP5430_RM_ABE_MCBSP3_CONTEXT		0x4ae0655c
extern reg omap5430_rm_abe_mcbsp3_context;
#define OMAP5430_PM_ABE_SLIMBUS1_WKDEP		0x4ae06560
extern reg omap5430_pm_abe_slimbus1_wkdep;
#define OMAP5430_RM_ABE_SLIMBUS1_CONTEXT	0x4ae06564
extern reg omap5430_rm_abe_slimbus1_context;
#define OMAP5430_PM_ABE_TIMER5_WKDEP		0x4ae06568
extern reg omap5430_pm_abe_timer5_wkdep;
#define OMAP5430_RM_ABE_TIMER5_CONTEXT		0x4ae0656c
extern reg omap5430_rm_abe_timer5_context;
#define OMAP5430_PM_ABE_TIMER6_WKDEP		0x4ae06570
extern reg omap5430_pm_abe_timer6_wkdep;
#define OMAP5430_RM_ABE_TIMER6_CONTEXT		0x4ae06574
extern reg omap5430_rm_abe_timer6_context;
#define OMAP5430_PM_ABE_TIMER7_WKDEP		0x4ae06578
extern reg omap5430_pm_abe_timer7_wkdep;
#define OMAP5430_RM_ABE_TIMER7_CONTEXT		0x4ae0657c
extern reg omap5430_rm_abe_timer7_context;
#define OMAP5430_PM_ABE_TIMER8_WKDEP		0x4ae06580
extern reg omap5430_pm_abe_timer8_wkdep;
#define OMAP5430_RM_ABE_TIMER8_CONTEXT		0x4ae06584
extern reg omap5430_rm_abe_timer8_context;
#define OMAP5430_PM_ABE_WD_TIMER3_WKDEP		0x4ae06588
extern reg omap5430_pm_abe_wd_timer3_wkdep;
#define OMAP5430_RM_ABE_WD_TIMER3_CONTEXT	0x4ae0658c
extern reg omap5430_rm_abe_wd_timer3_context;
#define OMAP5430_ABE_PRM_MOD_REGCOUNT		27
extern reg *omap5430_abe_prm_mod[OMAP5430_ABE_PRM_MOD_REGCOUNT + 1];

#define OMAP5430_PM_GPU_PWRSTCTRL		0x4ae07500
extern reg omap5430_pm_gpu_pwrstctrl;
#define OMAP5430_PM_GPU_PWRSTST			0x4ae07504
extern reg omap5430_pm_gpu_pwrstst;
#define OMAP5430_RM_GPU_GPU_CONTEXT		0x4ae07524
extern reg omap5430_rm_gpu_gpu_context;
#define OMAP5430_GPU_PRM_MOD_REGCOUNT		3
extern reg *omap5430_gpu_prm_mod[OMAP5430_GPU_PRM_MOD_REGCOUNT + 1];

#define OMAP5430_PM_COREAON_SMARTREFLEX_MPU_WKDEP	0x4ae06628
extern reg omap5430_pm_coreaon_smartreflex_mpu_wkdep;
#define OMAP5430_RM_COREAON_SMARTREFLEX_MPU_CONTEXT	0x4ae0662c
extern reg omap5430_rm_coreaon_smartreflex_mpu_context;
#define OMAP5430_PM_COREAON_SMARTREFLEX_MM_WKDEP	0x4ae06630
extern reg omap5430_pm_coreaon_smartreflex_mm_wkdep;
#define OMAP5430_RM_COREAON_SMARTREFLEX_MM_CONTEXT	0x4ae06634
extern reg omap5430_rm_coreaon_smartreflex_mm_context;
#define OMAP5430_PM_COREAON_SMARTREFLEX_CORE_WKDEP	0x4ae06638
extern reg omap5430_pm_coreaon_smartreflex_core_wkdep;
#define OMAP5430_RM_COREAON_SMARTREFLEX_CORE_CONTEXT	0x4ae0663c
extern reg omap5430_rm_coreaon_smartreflex_core_context;
#define OMAP5430_COREAON_PRM_MOD_REGCOUNT		6
extern reg *omap5430_coreaon_prm_mod[OMAP5430_COREAON_PRM_MOD_REGCOUNT + 1];

#define OMAP5430_PM_CUSTEFUSE_PWRSTCTRL			0x4ae07700
extern reg omap5430_pm_custefuse_pwrstctrl;
#define OMAP5430_PM_CUSTEFUSE_PWRSTST			0x4ae07704
extern reg omap5430_pm_custefuse_pwrstst;
#define OMAP5430_RM_CUSTEFUSE_EFUSE_CTRL_CUST_CONTEXT	0x4ae07724
extern reg omap5430_rm_custefuse_efuse_ctrl_cust_context;
#define OMAP5430_CUSTEFUSE_PRM_MOD_REGCOUNT		3
extern reg *omap5430_custefuse_prm_mod[OMAP5430_CUSTEFUSE_PRM_MOD_REGCOUNT + 1];

#define OMAP5430_CM_CLKSEL_ABE_DSS_SYS		0x4ae06100
extern reg omap5430_cm_clksel_abe_dss_sys;
#define OMAP5430_CM_CLKSEL_WKUPAON		0x4ae06108
extern reg omap5430_cm_clksel_wkupaon;
#define OMAP5430_CM_CLKSEL_ABE_PLL_REF		0x4ae0610c
extern reg omap5430_cm_clksel_abe_pll_ref;
#define OMAP5430_CM_CLKSEL_SYS			0x4ae06110
extern reg omap5430_cm_clksel_sys;
#define OMAP5430_CKGEN_PRM_MOD_REGCOUNT		4
extern reg *omap5430_ckgen_prm_mod[OMAP5430_CKGEN_PRM_MOD_REGCOUNT + 1];

#define OMAP5430_PMI_IDENTICATION		0x4ae07f00
extern reg omap5430_pmi_identication;
#define OMAP5430_PMI_SYS_CONFIG			0x4ae07f10
extern reg omap5430_pmi_sys_config;
#define OMAP5430_PMI_STATUS			0x4ae07f14
extern reg omap5430_pmi_status;
#define OMAP5430_PMI_CONFIGURATION		0x4ae07f24
extern reg omap5430_pmi_configuration;
#define OMAP5430_PMI_CLASS_FILTERING		0x4ae07f28
extern reg omap5430_pmi_class_filtering;
#define OMAP5430_PMI_TRIGGERING			0x4ae07f2c
extern reg omap5430_pmi_triggering;
#define OMAP5430_PMI_SAMPLING			0x4ae07f30
extern reg omap5430_pmi_sampling;
#define OMAP5430_INSTR_PRM_MOD_REGCOUNT		7
extern reg *omap5430_instr_prm_mod[OMAP5430_INSTR_PRM_MOD_REGCOUNT + 1];

#define OMAP5430_PM_IVA_PWRSTCTRL		0x4ae07200
extern reg omap5430_pm_iva_pwrstctrl;
#define OMAP5430_PM_IVA_PWRSTST			0x4ae07204
extern reg omap5430_pm_iva_pwrstst;
#define OMAP5430_RM_IVA_RSTCTRL			0x4ae07210
extern reg omap5430_rm_iva_rstctrl;
#define OMAP5430_RM_IVA_RSTST			0x4ae07214
extern reg omap5430_rm_iva_rstst;
#define OMAP5430_RM_IVA_IVA_CONTEXT		0x4ae07224
extern reg omap5430_rm_iva_iva_context;
#define OMAP5430_RM_IVA_SL2_CONTEXT		0x4ae0722c
extern reg omap5430_rm_iva_sl2_context;
#define OMAP5430_IVA_PRM_MOD_REGCOUNT		6
extern reg *omap5430_iva_prm_mod[OMAP5430_IVA_PRM_MOD_REGCOUNT + 1];

#define OMAP5430_PM_CORE_PWRSTCTRL		0x4ae06700
extern reg omap5430_pm_core_pwrstctrl;
#define OMAP5430_PM_CORE_PWRSTST		0x4ae06704
extern reg omap5430_pm_core_pwrstst;
#define OMAP5430_RM_L3MAIN1_L3_MAIN_1_CONTEXT	0x4ae06724
extern reg omap5430_rm_l3main1_l3_main_1_context;
#define OMAP5430_RM_L3MAIN2_L3_MAIN_2_CONTEXT	0x4ae06824
extern reg omap5430_rm_l3main2_l3_main_2_context;
#define OMAP5430_RM_L3MAIN2_GPMC_CONTEXT	0x4ae0682c
extern reg omap5430_rm_l3main2_gpmc_context;
#define OMAP5430_RM_L3MAIN2_OCMC_RAM_CONTEXT	0x4ae06834
extern reg omap5430_rm_l3main2_ocmc_ram_context;
#define OMAP5430_RM_IPU_RSTCTRL			0x4ae06910
extern reg omap5430_rm_ipu_rstctrl;
#define OMAP5430_RM_IPU_RSTST			0x4ae06914
extern reg omap5430_rm_ipu_rstst;
#define OMAP5430_RM_IPU_IPU_CONTEXT		0x4ae06924
extern reg omap5430_rm_ipu_ipu_context;
#define OMAP5430_RM_DMA_DMA_SYSTEM_CONTEXT	0x4ae06a24
extern reg omap5430_rm_dma_dma_system_context;
#define OMAP5430_RM_EMIF_DMM_CONTEXT		0x4ae06b24
extern reg omap5430_rm_emif_dmm_context;
#define OMAP5430_RM_EMIF_EMIF_FW_CONTEXT	0x4ae06b2c
extern reg omap5430_rm_emif_emif_fw_context;
#define OMAP5430_RM_EMIF_EMIF1_CONTEXT		0x4ae06b34
extern reg omap5430_rm_emif_emif1_context;
#define OMAP5430_RM_EMIF_EMIF2_CONTEXT		0x4ae06b3c
extern reg omap5430_rm_emif_emif2_context;
#define OMAP5430_RM_EMIF_EMIF_DLL_CONTEXT	0x4ae06b44
extern reg omap5430_rm_emif_emif_dll_context;
#define OMAP5430_RM_C2C_C2C_CONTEXT		0x4ae06c24
extern reg omap5430_rm_c2c_c2c_context;
#define OMAP5430_RM_C2C_MODEM_ICR_CONTEXT	0x4ae06c2c
extern reg omap5430_rm_c2c_modem_icr_context;
#define OMAP5430_RM_C2C_C2C_OCP_FW_CONTEXT	0x4ae06c34
extern reg omap5430_rm_c2c_c2c_ocp_fw_context;
#define OMAP5430_RM_L4CFG_L4_CFG_CONTEXT	0x4ae06d24
extern reg omap5430_rm_l4cfg_l4_cfg_context;
#define OMAP5430_RM_L4CFG_SPINLOCK_CONTEXT	0x4ae06d2c
extern reg omap5430_rm_l4cfg_spinlock_context;
#define OMAP5430_RM_L4CFG_MAILBOX_CONTEXT	0x4ae06d34
extern reg omap5430_rm_l4cfg_mailbox_context;
#define OMAP5430_RM_L4CFG_SAR_ROM_CONTEXT	0x4ae06d3c
extern reg omap5430_rm_l4cfg_sar_rom_context;
#define OMAP5430_RM_L4CFG_OCP2SCP2_CONTEXT	0x4ae06d44
extern reg omap5430_rm_l4cfg_ocp2scp2_context;
#define OMAP5430_RM_L3INSTR_L3_MAIN_3_CONTEXT	0x4ae06e24
extern reg omap5430_rm_l3instr_l3_main_3_context;
#define OMAP5430_RM_L3INSTR_L3_INSTR_CONTEXT	0x4ae06e2c
extern reg omap5430_rm_l3instr_l3_instr_context;
#define OMAP5430_RM_L3INSTR_OCP_WP_NOC_CONTEXT	0x4ae06e44
extern reg omap5430_rm_l3instr_ocp_wp_noc_context;
#define OMAP5430_RM_MIPIEXT_LLI_CONTEXT		0x4ae06f24
extern reg omap5430_rm_mipiext_lli_context;
#define OMAP5430_RM_MIPIEXT_LLI_OCP_FW_CONTEXT	0x4ae06f2c
extern reg omap5430_rm_mipiext_lli_ocp_fw_context;
#define OMAP5430_RM_MIPIEXT_MPHY_CONTEXT	0x4ae06f34
extern reg omap5430_rm_mipiext_mphy_context;
#define OMAP5430_PM_L4PER_TIMER10_WKDEP		0x4ae07028
extern reg omap5430_pm_l4per_timer10_wkdep;
#define OMAP5430_RM_L4PER_TIMER10_CONTEXT	0x4ae0702c
extern reg omap5430_rm_l4per_timer10_context;
#define OMAP5430_PM_L4PER_TIMER11_WKDEP		0x4ae07030
extern reg omap5430_pm_l4per_timer11_wkdep;
#define OMAP5430_RM_L4PER_TIMER11_CONTEXT	0x4ae07034
extern reg omap5430_rm_l4per_timer11_context;
#define OMAP5430_PM_L4PER_TIMER2_WKDEP		0x4ae07038
extern reg omap5430_pm_l4per_timer2_wkdep;
#define OMAP5430_RM_L4PER_TIMER2_CONTEXT	0x4ae0703c
extern reg omap5430_rm_l4per_timer2_context;
#define OMAP5430_PM_L4PER_TIMER3_WKDEP		0x4ae07040
extern reg omap5430_pm_l4per_timer3_wkdep;
#define OMAP5430_RM_L4PER_TIMER3_CONTEXT	0x4ae07044
extern reg omap5430_rm_l4per_timer3_context;
#define OMAP5430_PM_L4PER_TIMER4_WKDEP		0x4ae07048
extern reg omap5430_pm_l4per_timer4_wkdep;
#define OMAP5430_RM_L4PER_TIMER4_CONTEXT	0x4ae0704c
extern reg omap5430_rm_l4per_timer4_context;
#define OMAP5430_PM_L4PER_TIMER9_WKDEP		0x4ae07050
extern reg omap5430_pm_l4per_timer9_wkdep;
#define OMAP5430_RM_L4PER_TIMER9_CONTEXT	0x4ae07054
extern reg omap5430_rm_l4per_timer9_context;
#define OMAP5430_RM_L4PER_ELM_CONTEXT		0x4ae0705c
extern reg omap5430_rm_l4per_elm_context;
#define OMAP5430_PM_L4PER_GPIO2_WKDEP		0x4ae07060
extern reg omap5430_pm_l4per_gpio2_wkdep;
#define OMAP5430_RM_L4PER_GPIO2_CONTEXT		0x4ae07064
extern reg omap5430_rm_l4per_gpio2_context;
#define OMAP5430_PM_L4PER_GPIO3_WKDEP		0x4ae07068
extern reg omap5430_pm_l4per_gpio3_wkdep;
#define OMAP5430_RM_L4PER_GPIO3_CONTEXT		0x4ae0706c
extern reg omap5430_rm_l4per_gpio3_context;
#define OMAP5430_PM_L4PER_GPIO4_WKDEP		0x4ae07070
extern reg omap5430_pm_l4per_gpio4_wkdep;
#define OMAP5430_RM_L4PER_GPIO4_CONTEXT		0x4ae07074
extern reg omap5430_rm_l4per_gpio4_context;
#define OMAP5430_PM_L4PER_GPIO5_WKDEP		0x4ae07078
extern reg omap5430_pm_l4per_gpio5_wkdep;
#define OMAP5430_RM_L4PER_GPIO5_CONTEXT		0x4ae0707c
extern reg omap5430_rm_l4per_gpio5_context;
#define OMAP5430_PM_L4PER_GPIO6_WKDEP		0x4ae07080
extern reg omap5430_pm_l4per_gpio6_wkdep;
#define OMAP5430_RM_L4PER_GPIO6_CONTEXT		0x4ae07084
extern reg omap5430_rm_l4per_gpio6_context;
#define OMAP5430_RM_L4PER_HDQ1W_CONTEXT		0x4ae0708c
extern reg omap5430_rm_l4per_hdq1w_context;
#define OMAP5430_PM_L4PER_I2C1_WKDEP		0x4ae070a0
extern reg omap5430_pm_l4per_i2c1_wkdep;
#define OMAP5430_RM_L4PER_I2C1_CONTEXT		0x4ae070a4
extern reg omap5430_rm_l4per_i2c1_context;
#define OMAP5430_PM_L4PER_I2C2_WKDEP		0x4ae070a8
extern reg omap5430_pm_l4per_i2c2_wkdep;
#define OMAP5430_RM_L4PER_I2C2_CONTEXT		0x4ae070ac
extern reg omap5430_rm_l4per_i2c2_context;
#define OMAP5430_PM_L4PER_I2C3_WKDEP		0x4ae070b0
extern reg omap5430_pm_l4per_i2c3_wkdep;
#define OMAP5430_RM_L4PER_I2C3_CONTEXT		0x4ae070b4
extern reg omap5430_rm_l4per_i2c3_context;
#define OMAP5430_PM_L4PER_I2C4_WKDEP		0x4ae070b8
extern reg omap5430_pm_l4per_i2c4_wkdep;
#define OMAP5430_RM_L4PER_I2C4_CONTEXT		0x4ae070bc
extern reg omap5430_rm_l4per_i2c4_context;
#define OMAP5430_RM_L4PER_L4_PER_CONTEXT	0x4ae070c0
extern reg omap5430_rm_l4per_l4_per_context;
#define OMAP5430_PM_L4PER_MCSPI1_WKDEP		0x4ae070f0
extern reg omap5430_pm_l4per_mcspi1_wkdep;
#define OMAP5430_RM_L4PER_MCSPI1_CONTEXT	0x4ae070f4
extern reg omap5430_rm_l4per_mcspi1_context;
#define OMAP5430_PM_L4PER_MCSPI2_WKDEP		0x4ae070f8
extern reg omap5430_pm_l4per_mcspi2_wkdep;
#define OMAP5430_RM_L4PER_MCSPI2_CONTEXT	0x4ae070fc
extern reg omap5430_rm_l4per_mcspi2_context;
#define OMAP5430_PM_L4PER_MCSPI3_WKDEP		0x4ae07100
extern reg omap5430_pm_l4per_mcspi3_wkdep;
#define OMAP5430_RM_L4PER_MCSPI3_CONTEXT	0x4ae07104
extern reg omap5430_rm_l4per_mcspi3_context;
#define OMAP5430_PM_L4PER_MCSPI4_WKDEP		0x4ae07108
extern reg omap5430_pm_l4per_mcspi4_wkdep;
#define OMAP5430_RM_L4PER_MCSPI4_CONTEXT	0x4ae0710c
extern reg omap5430_rm_l4per_mcspi4_context;
#define OMAP5430_PM_L4PER_GPIO7_WKDEP		0x4ae07110
extern reg omap5430_pm_l4per_gpio7_wkdep;
#define OMAP5430_RM_L4PER_GPIO7_CONTEXT		0x4ae07114
extern reg omap5430_rm_l4per_gpio7_context;
#define OMAP5430_PM_L4PER_GPIO8_WKDEP		0x4ae07118
extern reg omap5430_pm_l4per_gpio8_wkdep;
#define OMAP5430_RM_L4PER_GPIO8_CONTEXT		0x4ae0711c
extern reg omap5430_rm_l4per_gpio8_context;
#define OMAP5430_PM_L4PER_MMC3_WKDEP		0x4ae07120
extern reg omap5430_pm_l4per_mmc3_wkdep;
#define OMAP5430_RM_L4PER_MMC3_CONTEXT		0x4ae07124
extern reg omap5430_rm_l4per_mmc3_context;
#define OMAP5430_PM_L4PER_MMC4_WKDEP		0x4ae07128
extern reg omap5430_pm_l4per_mmc4_wkdep;
#define OMAP5430_RM_L4PER_MMC4_CONTEXT		0x4ae0712c
extern reg omap5430_rm_l4per_mmc4_context;
#define OMAP5430_PM_L4PER_UART1_WKDEP		0x4ae07140
extern reg omap5430_pm_l4per_uart1_wkdep;
#define OMAP5430_RM_L4PER_UART1_CONTEXT		0x4ae07144
extern reg omap5430_rm_l4per_uart1_context;
#define OMAP5430_PM_L4PER_UART2_WKDEP		0x4ae07148
extern reg omap5430_pm_l4per_uart2_wkdep;
#define OMAP5430_RM_L4PER_UART2_CONTEXT		0x4ae0714c
extern reg omap5430_rm_l4per_uart2_context;
#define OMAP5430_PM_L4PER_UART3_WKDEP		0x4ae07150
extern reg omap5430_pm_l4per_uart3_wkdep;
#define OMAP5430_RM_L4PER_UART3_CONTEXT		0x4ae07154
extern reg omap5430_rm_l4per_uart3_context;
#define OMAP5430_RM_L4PER_UART4_CONTEXT		0x4ae07158
extern reg omap5430_rm_l4per_uart4_context;
#define OMAP5430_PM_L4PER_UART4_WKDEP		0x4ae0715c
extern reg omap5430_pm_l4per_uart4_wkdep;
#define OMAP5430_PM_L4PER_MMC5_WKDEP		0x4ae07160
extern reg omap5430_pm_l4per_mmc5_wkdep;
#define OMAP5430_RM_L4PER_MMC5_CONTEXT		0x4ae07164
extern reg omap5430_rm_l4per_mmc5_context;
#define OMAP5430_PM_L4PER_I2C5_WKDEP		0x4ae07168
extern reg omap5430_pm_l4per_i2c5_wkdep;
#define OMAP5430_RM_L4PER_I2C5_CONTEXT		0x4ae0716c
extern reg omap5430_rm_l4per_i2c5_context;
#define OMAP5430_PM_L4PER_UART5_WKDEP		0x4ae07170
extern reg omap5430_pm_l4per_uart5_wkdep;
#define OMAP5430_RM_L4PER_UART5_CONTEXT		0x4ae07174
extern reg omap5430_rm_l4per_uart5_context;
#define OMAP5430_PM_L4PER_UART6_WKDEP		0x4ae07178
extern reg omap5430_pm_l4per_uart6_wkdep;
#define OMAP5430_RM_L4PER_UART6_CONTEXT		0x4ae0717c
extern reg omap5430_rm_l4per_uart6_context;
#define OMAP5430_RM_L4SEC_AES1_CONTEXT		0x4ae071a4
extern reg omap5430_rm_l4sec_aes1_context;
#define OMAP5430_RM_L4SEC_AES2_CONTEXT		0x4ae071ac
extern reg omap5430_rm_l4sec_aes2_context;
#define OMAP5430_RM_L4SEC_DES3DES_CONTEXT	0x4ae071b4
extern reg omap5430_rm_l4sec_des3des_context;
#define OMAP5430_RM_L4SEC_FPKA_CONTEXT		0x4ae071bc
extern reg omap5430_rm_l4sec_fpka_context;
#define OMAP5430_RM_L4SEC_RNG_CONTEXT		0x4ae071c4
extern reg omap5430_rm_l4sec_rng_context;
#define OMAP5430_RM_L4SEC_SHA2MD5_CONTEXT	0x4ae071cc
extern reg omap5430_rm_l4sec_sha2md5_context;
#define OMAP5430_RM_L4SEC_DMA_CRYPTO_CONTEXT	0x4ae071dc
extern reg omap5430_rm_l4sec_dma_crypto_context;
#define OMAP5430_CORE_PRM_MOD_REGCOUNT		101
extern reg *omap5430_core_prm_mod[OMAP5430_CORE_PRM_MOD_REGCOUNT + 1];

#define OMAP5430_PM_EMU_PWRSTCTRL		0x4ae07a00
extern reg omap5430_pm_emu_pwrstctrl;
#define OMAP5430_PM_EMU_PWRSTST			0x4ae07a04
extern reg omap5430_pm_emu_pwrstst;
#define OMAP5430_RM_EMU_DEBUGSS_CONTEXT		0x4ae07a24
extern reg omap5430_rm_emu_debugss_context;
#define OMAP5430_EMU_PRM_MOD_REGCOUNT		3
extern reg *omap5430_emu_prm_mod[OMAP5430_EMU_PRM_MOD_REGCOUNT + 1];

#define OMAP5430_PM_MPU_PWRSTCTRL		0x4ae06300
extern reg omap5430_pm_mpu_pwrstctrl;
#define OMAP5430_PM_MPU_PWRSTST			0x4ae06304
extern reg omap5430_pm_mpu_pwrstst;
#define OMAP5430_RM_MPU_MPU_CONTEXT		0x4ae06324
extern reg omap5430_rm_mpu_mpu_context;
#define OMAP5430_MPU_PRM_MOD_REGCOUNT		3
extern reg *omap5430_mpu_prm_mod[OMAP5430_MPU_PRM_MOD_REGCOUNT + 1];

#define OMAP5430_PM_L3INIT_PWRSTCTRL			0x4ae07600
extern reg omap5430_pm_l3init_pwrstctrl;
#define OMAP5430_PM_L3INIT_PWRSTST			0x4ae07604
extern reg omap5430_pm_l3init_pwrstst;
#define OMAP5430_PM_L3INIT_MMC1_WKDEP			0x4ae07628
extern reg omap5430_pm_l3init_mmc1_wkdep;
#define OMAP5430_RM_L3INIT_MMC1_CONTEXT			0x4ae0762c
extern reg omap5430_rm_l3init_mmc1_context;
#define OMAP5430_PM_L3INIT_MMC2_WKDEP			0x4ae07630
extern reg omap5430_pm_l3init_mmc2_wkdep;
#define OMAP5430_RM_L3INIT_MMC2_CONTEXT			0x4ae07634
extern reg omap5430_rm_l3init_mmc2_context;
#define OMAP5430_PM_L3INIT_HSI_WKDEP			0x4ae07638
extern reg omap5430_pm_l3init_hsi_wkdep;
#define OMAP5430_RM_L3INIT_HSI_CONTEXT			0x4ae0763c
extern reg omap5430_rm_l3init_hsi_context;
#define OMAP5430_PM_L3INIT_UNIPRO2_WKDEP		0x4ae07640
extern reg omap5430_pm_l3init_unipro2_wkdep;
#define OMAP5430_RM_L3INIT_UNIPRO2_CONTEXT		0x4ae07644
extern reg omap5430_rm_l3init_unipro2_context;
#define OMAP5430_PM_L3INIT_USB_HOST_HS_WKDEP		0x4ae07658
extern reg omap5430_pm_l3init_usb_host_hs_wkdep;
#define OMAP5430_RM_L3INIT_USB_HOST_HS_CONTEXT		0x4ae0765c
extern reg omap5430_rm_l3init_usb_host_hs_context;
#define OMAP5430_PM_L3INIT_USB_TLL_HS_WKDEP		0x4ae07668
extern reg omap5430_pm_l3init_usb_tll_hs_wkdep;
#define OMAP5430_RM_L3INIT_USB_TLL_HS_CONTEXT		0x4ae0766c
extern reg omap5430_rm_l3init_usb_tll_hs_context;
#define OMAP5430_RM_L3INIT_IEEE1500_2_OCP_CONTEXT	0x4ae0767c
extern reg omap5430_rm_l3init_ieee1500_2_ocp_context;
#define OMAP5430_PM_L3INIT_SATA_WKDEP			0x4ae07688
extern reg omap5430_pm_l3init_sata_wkdep;
#define OMAP5430_RM_L3INIT_SATA_CONTEXT			0x4ae0768c
extern reg omap5430_rm_l3init_sata_context;
#define OMAP5430_RM_L3INIT_OCP2SCP1_CONTEXT		0x4ae076e4
extern reg omap5430_rm_l3init_ocp2scp1_context;
#define OMAP5430_RM_L3INIT_OCP2SCP3_CONTEXT		0x4ae076ec
extern reg omap5430_rm_l3init_ocp2scp3_context;
#define OMAP5430_PM_L3INIT_USB_OTG_SS_WKDEP		0x4ae076f0
extern reg omap5430_pm_l3init_usb_otg_ss_wkdep;
#define OMAP5430_RM_L3INIT_USB_OTG_SS_CONTEXT		0x4ae076f4
extern reg omap5430_rm_l3init_usb_otg_ss_context;
#define OMAP5430_L3INIT_PRM_MOD_REGCOUNT		21
extern reg *omap5430_l3init_prm_mod[OMAP5430_L3INIT_PRM_MOD_REGCOUNT + 1];

#define OMAP5430_PM_CPU0_PWRSTCTRL		0x48243400
extern reg omap5430_pm_cpu0_pwrstctrl;
#define OMAP5430_PM_CPU0_PWRSTST		0x48243404
extern reg omap5430_pm_cpu0_pwrstst;
#define OMAP5430_RM_CPU0_CPU0_RSTCTRL		0x48243410
extern reg omap5430_rm_cpu0_cpu0_rstctrl;
#define OMAP5430_RM_CPU0_CPU0_RSTST		0x48243414
extern reg omap5430_rm_cpu0_cpu0_rstst;
#define OMAP5430_RM_CPU0_CPU0_CONTEXT		0x48243424
extern reg omap5430_rm_cpu0_cpu0_context;
#define OMAP5430_PRCM_MPU_PRM_C0_MOD_REGCOUNT	5
extern reg *omap5430_prcm_mpu_prm_c0_mod[OMAP5430_PRCM_MPU_PRM_C0_MOD_REGCOUNT + 1];

#define OMAP5430_PM_CPU1_PWRSTCTRL		0x48243800
extern reg omap5430_pm_cpu1_pwrstctrl;
#define OMAP5430_PM_CPU1_PWRSTST		0x48243804
extern reg omap5430_pm_cpu1_pwrstst;
#define OMAP5430_RM_CPU1_CPU1_RSTCTRL		0x48243810
extern reg omap5430_rm_cpu1_cpu1_rstctrl;
#define OMAP5430_RM_CPU1_CPU1_RSTST		0x48243814
extern reg omap5430_rm_cpu1_cpu1_rstst;
#define OMAP5430_RM_CPU1_CPU1_CONTEXT		0x48243824
extern reg omap5430_rm_cpu1_cpu1_context;
#define OMAP5430_PRCM_MPU_PRM_C1_MOD_REGCOUNT	5
extern reg *omap5430_prcm_mpu_prm_c1_mod[OMAP5430_PRCM_MPU_PRM_C1_MOD_REGCOUNT + 1];

extern reg **prm54xx_mods[PRM54XX_MODS_COUNT + 1];


#endif
