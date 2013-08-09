/*
 *
 * @Component			OMAPCONF
 * @Filename			prm_dra7xx-defs.h
 * @Description			DRA7 PRM Registers Definitions & Functions
 * @Author			Jin Zheng (j-zheng@ti.com)
 * @Date			2013
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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


#ifndef __PRM_DRA7XX_DEFS_H__
#define __PRM_DRA7XX_DEFS_H__


#include <reg.h>

#define DRA7XX_DSS_PRM_PM_DSS_PWRSTCTRL		0x4ae07100
extern  reg  dra7xx_dss_prm_pm_dss_pwrstctrl;
#define DRA7XX_DSS_PRM_PM_DSS_PWRSTST		0x4ae07104
extern  reg  dra7xx_dss_prm_pm_dss_pwrstst;
#define DRA7XX_DSS_PRM_PM_DSS_DSS_WKDEP		0x4ae07120
extern  reg  dra7xx_dss_prm_pm_dss_dss_wkdep;
#define DRA7XX_DSS_PRM_RM_DSS_DSS_CONTEXT	0x4ae07124
extern  reg  dra7xx_dss_prm_rm_dss_dss_context;
#define DRA7XX_DSS_PRM_PM_DSS_DSS2_WKDEP	0x4ae07128
extern  reg  dra7xx_dss_prm_pm_dss_dss2_wkdep;
#define DRA7XX_DSS_PRM_RM_DSS_BB2D_CONTEXT	0x4ae07134
extern  reg  dra7xx_dss_prm_rm_dss_bb2d_context;
#define DRA7XX_DSS_PRM_RM_DSS_SDVENC_CONTEXT	0x4ae0713c
extern  reg  dra7xx_dss_prm_rm_dss_sdvenc_context;
#define DRA7XX_DSS_PRM_MOD_REGCOUNT		7
extern reg *dra7xx_dss_prm_mod[DRA7XX_DSS_PRM_MOD_REGCOUNT + 1];

#define DRA7XX_WKUPAON_PRM_RM_WKUPAON_L4_WKUP_CONTEXT		0x4ae07724
extern  reg  dra7xx_wkupaon_prm_rm_wkupaon_l4_wkup_context;
#define DRA7XX_WKUPAON_PRM_PM_WKUPAON_WD_TIMER1_WKDEP		0x4ae07728
extern  reg  dra7xx_wkupaon_prm_pm_wkupaon_wd_timer1_wkdep;
#define DRA7XX_WKUPAON_PRM_RM_WKUPAON_WD_TIMER1_CONTEXT		0x4ae0772c
extern  reg  dra7xx_wkupaon_prm_rm_wkupaon_wd_timer1_context;
#define DRA7XX_WKUPAON_PRM_PM_WKUPAON_WD_TIMER2_WKDEP		0x4ae07730
extern  reg  dra7xx_wkupaon_prm_pm_wkupaon_wd_timer2_wkdep;
#define DRA7XX_WKUPAON_PRM_RM_WKUPAON_WD_TIMER2_CONTEXT		0x4ae07734
extern  reg  dra7xx_wkupaon_prm_rm_wkupaon_wd_timer2_context;
#define DRA7XX_WKUPAON_PRM_PM_WKUPAON_GPIO1_WKDEP		0x4ae07738
extern  reg  dra7xx_wkupaon_prm_pm_wkupaon_gpio1_wkdep;
#define DRA7XX_WKUPAON_PRM_RM_WKUPAON_GPIO1_CONTEXT		0x4ae0773c
extern  reg  dra7xx_wkupaon_prm_rm_wkupaon_gpio1_context;
#define DRA7XX_WKUPAON_PRM_PM_WKUPAON_TIMER1_WKDEP		0x4ae07740
extern  reg  dra7xx_wkupaon_prm_pm_wkupaon_timer1_wkdep;
#define DRA7XX_WKUPAON_PRM_RM_WKUPAON_TIMER1_CONTEXT		0x4ae07744
extern  reg  dra7xx_wkupaon_prm_rm_wkupaon_timer1_context;
#define DRA7XX_WKUPAON_PRM_PM_WKUPAON_TIMER12_WKDEP		0x4ae07748
extern  reg  dra7xx_wkupaon_prm_pm_wkupaon_timer12_wkdep;
#define DRA7XX_WKUPAON_PRM_RM_WKUPAON_TIMER12_CONTEXT		0x4ae0774c
extern  reg  dra7xx_wkupaon_prm_rm_wkupaon_timer12_context;
#define DRA7XX_WKUPAON_PRM_RM_WKUPAON_COUNTER_32K_CONTEXT	0x4ae07754
extern  reg  dra7xx_wkupaon_prm_rm_wkupaon_counter_32k_context;
#define DRA7XX_WKUPAON_PRM_RM_WKUPAON_SAR_RAM_CONTEXT		0x4ae07764
extern  reg  dra7xx_wkupaon_prm_rm_wkupaon_sar_ram_context;
#define DRA7XX_WKUPAON_PRM_PM_WKUPAON_KBD_WKDEP			0x4ae07778
extern  reg  dra7xx_wkupaon_prm_pm_wkupaon_kbd_wkdep;
#define DRA7XX_WKUPAON_PRM_RM_WKUPAON_KBD_CONTEXT		0x4ae0777c
extern  reg  dra7xx_wkupaon_prm_rm_wkupaon_kbd_context;
#define DRA7XX_WKUPAON_PRM_PM_WKUPAON_UART10_WKDEP		0x4ae07780
extern  reg  dra7xx_wkupaon_prm_pm_wkupaon_uart10_wkdep;
#define DRA7XX_WKUPAON_PRM_RM_WKUPAON_UART10_CONTEXT		0x4ae07784
extern  reg  dra7xx_wkupaon_prm_rm_wkupaon_uart10_context;
#define DRA7XX_WKUPAON_PRM_PM_WKUPAON_DCAN1_WKDEP		0x4ae07788
extern  reg  dra7xx_wkupaon_prm_pm_wkupaon_dcan1_wkdep;
#define DRA7XX_WKUPAON_PRM_RM_WKUPAON_DCAN1_CONTEXT		0x4ae0778c
extern  reg  dra7xx_wkupaon_prm_rm_wkupaon_dcan1_context;
#define DRA7XX_WKUPAON_PRM_PM_WKUPAON_ADC_WKDEP			0x4ae077a0
extern  reg  dra7xx_wkupaon_prm_pm_wkupaon_adc_wkdep;
#define DRA7XX_WKUPAON_PRM_RM_WKUPAON_ADC_CONTEXT		0x4ae077a4
extern  reg  dra7xx_wkupaon_prm_rm_wkupaon_adc_context;
#define DRA7XX_WKUPAON_PRM_RM_WKUPAON_SPARE_SAFETY1_CONTEXT	0x4ae077b4
extern  reg  dra7xx_wkupaon_prm_rm_wkupaon_spare_safety1_context;
#define DRA7XX_WKUPAON_PRM_RM_WKUPAON_SPARE_SAFETY2_CONTEXT	0x4ae077bc
extern  reg  dra7xx_wkupaon_prm_rm_wkupaon_spare_safety2_context;
#define DRA7XX_WKUPAON_PRM_RM_WKUPAON_SPARE_SAFETY3_CONTEXT	0x4ae077c4
extern  reg  dra7xx_wkupaon_prm_rm_wkupaon_spare_safety3_context;
#define DRA7XX_WKUPAON_PRM_RM_WKUPAON_SPARE_SAFETY4_CONTEXT	0x4ae077cc
extern  reg  dra7xx_wkupaon_prm_rm_wkupaon_spare_safety4_context;
#define DRA7XX_WKUPAON_PRM_RM_WKUPAON_SPARE_UNKNOWN2_CONTEXT	0x4ae077d4
extern  reg  dra7xx_wkupaon_prm_rm_wkupaon_spare_unknown2_context;
#define DRA7XX_WKUPAON_PRM_RM_WKUPAON_SPARE_UNKNOWN3_CONTEXT	0x4ae077dc
extern  reg  dra7xx_wkupaon_prm_rm_wkupaon_spare_unknown3_context;
#define DRA7XX_WKUPAON_PRM_MOD_REGCOUNT				27
extern reg *dra7xx_wkupaon_prm_mod[DRA7XX_WKUPAON_PRM_MOD_REGCOUNT + 1];

#define DRA7XX_OCP_SOCKET_PRM_REVISION_PRM		0x4ae06000
extern  reg  dra7xx_ocp_socket_prm_revision_prm;
#define DRA7XX_OCP_SOCKET_PRM_PRM_IRQSTATUS_MPU		0x4ae06010
extern  reg  dra7xx_ocp_socket_prm_prm_irqstatus_mpu;
#define DRA7XX_OCP_SOCKET_PRM_PRM_IRQSTATUS_MPU_2	0x4ae06014
extern  reg  dra7xx_ocp_socket_prm_prm_irqstatus_mpu_2;
#define DRA7XX_OCP_SOCKET_PRM_PRM_IRQENABLE_MPU		0x4ae06018
extern  reg  dra7xx_ocp_socket_prm_prm_irqenable_mpu;
#define DRA7XX_OCP_SOCKET_PRM_PRM_IRQENABLE_MPU_2	0x4ae0601c
extern  reg  dra7xx_ocp_socket_prm_prm_irqenable_mpu_2;
#define DRA7XX_OCP_SOCKET_PRM_PRM_IRQSTATUS_IPU2	0x4ae06020
extern  reg  dra7xx_ocp_socket_prm_prm_irqstatus_ipu2;
#define DRA7XX_OCP_SOCKET_PRM_PRM_IRQENABLE_IPU2	0x4ae06028
extern  reg  dra7xx_ocp_socket_prm_prm_irqenable_ipu2;
#define DRA7XX_OCP_SOCKET_PRM_PRM_IRQSTATUS_DSP1	0x4ae06030
extern  reg  dra7xx_ocp_socket_prm_prm_irqstatus_dsp1;
#define DRA7XX_OCP_SOCKET_PRM_PRM_IRQENABLE_DSP1	0x4ae06038
extern  reg  dra7xx_ocp_socket_prm_prm_irqenable_dsp1;
#define DRA7XX_OCP_SOCKET_PRM_CM_PRM_PROFILING_CLKCTRL	0x4ae06040
extern  reg  dra7xx_ocp_socket_prm_cm_prm_profiling_clkctrl;
#define DRA7XX_OCP_SOCKET_PRM_PRM_IRQENABLE_DSP2	0x4ae06044
extern  reg  dra7xx_ocp_socket_prm_prm_irqenable_dsp2;
#define DRA7XX_OCP_SOCKET_PRM_PRM_IRQENABLE_EVE1	0x4ae06048
extern  reg  dra7xx_ocp_socket_prm_prm_irqenable_eve1;
#define DRA7XX_OCP_SOCKET_PRM_PRM_IRQENABLE_EVE2	0x4ae0604c
extern  reg  dra7xx_ocp_socket_prm_prm_irqenable_eve2;
#define DRA7XX_OCP_SOCKET_PRM_PRM_IRQENABLE_EVE3	0x4ae06050
extern  reg  dra7xx_ocp_socket_prm_prm_irqenable_eve3;
#define DRA7XX_OCP_SOCKET_PRM_PRM_IRQENABLE_EVE4	0x4ae06054
extern  reg  dra7xx_ocp_socket_prm_prm_irqenable_eve4;
#define DRA7XX_OCP_SOCKET_PRM_PRM_IRQENABLE_IPU1	0x4ae06058
extern  reg  dra7xx_ocp_socket_prm_prm_irqenable_ipu1;
#define DRA7XX_OCP_SOCKET_PRM_PRM_IRQSTATUS_DSP2	0x4ae0605c
extern  reg  dra7xx_ocp_socket_prm_prm_irqstatus_dsp2;
#define DRA7XX_OCP_SOCKET_PRM_PRM_IRQSTATUS_EVE1	0x4ae06060
extern  reg  dra7xx_ocp_socket_prm_prm_irqstatus_eve1;
#define DRA7XX_OCP_SOCKET_PRM_PRM_IRQSTATUS_EVE2	0x4ae06064
extern  reg  dra7xx_ocp_socket_prm_prm_irqstatus_eve2;
#define DRA7XX_OCP_SOCKET_PRM_PRM_IRQSTATUS_EVE3	0x4ae06068
extern  reg  dra7xx_ocp_socket_prm_prm_irqstatus_eve3;
#define DRA7XX_OCP_SOCKET_PRM_PRM_IRQSTATUS_EVE4	0x4ae0606c
extern  reg  dra7xx_ocp_socket_prm_prm_irqstatus_eve4;
#define DRA7XX_OCP_SOCKET_PRM_PRM_IRQSTATUS_IPU1	0x4ae06070
extern  reg  dra7xx_ocp_socket_prm_prm_irqstatus_ipu1;
#define DRA7XX_OCP_SOCKET_PRM_PRM_DEBUG_CFG1		0x4ae060e4
extern  reg  dra7xx_ocp_socket_prm_prm_debug_cfg1;
#define DRA7XX_OCP_SOCKET_PRM_PRM_DEBUG_CFG2		0x4ae060e8
extern  reg  dra7xx_ocp_socket_prm_prm_debug_cfg2;
#define DRA7XX_OCP_SOCKET_PRM_PRM_DEBUG_CFG3		0x4ae060ec
extern  reg  dra7xx_ocp_socket_prm_prm_debug_cfg3;
#define DRA7XX_OCP_SOCKET_PRM_PRM_DEBUG_CFG		0x4ae060f0
extern  reg  dra7xx_ocp_socket_prm_prm_debug_cfg;
#define DRA7XX_OCP_SOCKET_PRM_PRM_DEBUG_OUT		0x4ae060f4
extern  reg  dra7xx_ocp_socket_prm_prm_debug_out;
#define DRA7XX_OCP_SOCKET_PRM_MOD_REGCOUNT		27
extern reg *dra7xx_ocp_socket_prm_mod[DRA7XX_OCP_SOCKET_PRM_MOD_REGCOUNT + 1];

#define DRA7XX_CAM_PRM_PM_CAM_PWRSTCTRL		0x4ae07000
extern  reg  dra7xx_cam_prm_pm_cam_pwrstctrl;
#define DRA7XX_CAM_PRM_PM_CAM_PWRSTST		0x4ae07004
extern  reg  dra7xx_cam_prm_pm_cam_pwrstst;
#define DRA7XX_CAM_PRM_PM_CAM_VIP1_WKDEP	0x4ae07020
extern  reg  dra7xx_cam_prm_pm_cam_vip1_wkdep;
#define DRA7XX_CAM_PRM_RM_CAM_VIP1_CONTEXT	0x4ae07024
extern  reg  dra7xx_cam_prm_rm_cam_vip1_context;
#define DRA7XX_CAM_PRM_PM_CAM_VIP2_WKDEP	0x4ae07028
extern  reg  dra7xx_cam_prm_pm_cam_vip2_wkdep;
#define DRA7XX_CAM_PRM_RM_CAM_VIP2_CONTEXT	0x4ae0702c
extern  reg  dra7xx_cam_prm_rm_cam_vip2_context;
#define DRA7XX_CAM_PRM_PM_CAM_VIP3_WKDEP	0x4ae07030
extern  reg  dra7xx_cam_prm_pm_cam_vip3_wkdep;
#define DRA7XX_CAM_PRM_RM_CAM_VIP3_CONTEXT	0x4ae07034
extern  reg  dra7xx_cam_prm_rm_cam_vip3_context;
#define DRA7XX_CAM_PRM_RM_CAM_LVDSRX_CONTEXT	0x4ae0703c
extern  reg  dra7xx_cam_prm_rm_cam_lvdsrx_context;
#define DRA7XX_CAM_PRM_RM_CAM_CSI1_CONTEXT	0x4ae07044
extern  reg  dra7xx_cam_prm_rm_cam_csi1_context;
#define DRA7XX_CAM_PRM_RM_CAM_CSI2_CONTEXT	0x4ae0704c
extern  reg  dra7xx_cam_prm_rm_cam_csi2_context;
#define DRA7XX_CAM_PRM_MOD_REGCOUNT		11
extern reg *dra7xx_cam_prm_mod[DRA7XX_CAM_PRM_MOD_REGCOUNT + 1];

#define DRA7XX_DSP1_PRM_PM_DSP1_PWRSTCTRL	0x4ae06400
extern  reg  dra7xx_dsp1_prm_pm_dsp1_pwrstctrl;
#define DRA7XX_DSP1_PRM_PM_DSP1_PWRSTST		0x4ae06404
extern  reg  dra7xx_dsp1_prm_pm_dsp1_pwrstst;
#define DRA7XX_DSP1_PRM_RM_DSP1_RSTCTRL		0x4ae06410
extern  reg  dra7xx_dsp1_prm_rm_dsp1_rstctrl;
#define DRA7XX_DSP1_PRM_RM_DSP1_RSTST		0x4ae06414
extern  reg  dra7xx_dsp1_prm_rm_dsp1_rstst;
#define DRA7XX_DSP1_PRM_RM_DSP1_DSP1_CONTEXT	0x4ae06424
extern  reg  dra7xx_dsp1_prm_rm_dsp1_dsp1_context;
#define DRA7XX_DSP2_PRM_PM_DSP2_PWRSTCTRL	0x4ae07b00
extern  reg  dra7xx_dsp2_prm_pm_dsp2_pwrstctrl;
#define DRA7XX_DSP2_PRM_PM_DSP2_PWRSTST		0x4ae07b04
extern  reg  dra7xx_dsp2_prm_pm_dsp2_pwrstst;
#define DRA7XX_DSP2_PRM_RM_DSP2_RSTCTRL		0x4ae07b10
extern  reg  dra7xx_dsp2_prm_rm_dsp2_rstctrl;
#define DRA7XX_DSP2_PRM_RM_DSP2_RSTST		0x4ae07b14
extern  reg  dra7xx_dsp2_prm_rm_dsp2_rstst;
#define DRA7XX_DSP2_PRM_RM_DSP2_DSP2_CONTEXT	0x4ae07b24
extern  reg  dra7xx_dsp2_prm_rm_dsp2_dsp2_context;
#define DRA7XX_DSP_PRM_MOD_REGCOUNT		10
extern reg *dra7xx_dsp_prm_mod[DRA7XX_DSP_PRM_MOD_REGCOUNT + 1];

#define DRA7XX_DEVICE_PRM_PRM_RSTCTRL			0x4ae07d00
extern  reg  dra7xx_device_prm_prm_rstctrl;
#define DRA7XX_DEVICE_PRM_PRM_RSTST			0x4ae07d04
extern  reg  dra7xx_device_prm_prm_rstst;
#define DRA7XX_DEVICE_PRM_PRM_RSTTIME			0x4ae07d08
extern  reg  dra7xx_device_prm_prm_rsttime;
#define DRA7XX_DEVICE_PRM_PRM_CLKREQCTRL		0x4ae07d0c
extern  reg  dra7xx_device_prm_prm_clkreqctrl;
#define DRA7XX_DEVICE_PRM_PRM_VOLTCTRL			0x4ae07d10
extern  reg  dra7xx_device_prm_prm_voltctrl;
#define DRA7XX_DEVICE_PRM_PRM_PWRREQCTRL		0x4ae07d14
extern  reg  dra7xx_device_prm_prm_pwrreqctrl;
#define DRA7XX_DEVICE_PRM_PRM_PSCON_COUNT		0x4ae07d18
extern  reg  dra7xx_device_prm_prm_pscon_count;
#define DRA7XX_DEVICE_PRM_PRM_IO_COUNT			0x4ae07d1c
extern  reg  dra7xx_device_prm_prm_io_count;
#define DRA7XX_DEVICE_PRM_PRM_IO_PMCTRL			0x4ae07d20
extern  reg  dra7xx_device_prm_prm_io_pmctrl;
#define DRA7XX_DEVICE_PRM_PRM_VOLTSETUP_WARMRESET	0x4ae07d24
extern  reg  dra7xx_device_prm_prm_voltsetup_warmreset;
#define DRA7XX_DEVICE_PRM_PRM_VOLTSETUP_CORE_OFF	0x4ae07d28
extern  reg  dra7xx_device_prm_prm_voltsetup_core_off;
#define DRA7XX_DEVICE_PRM_PRM_VOLTSETUP_MPU_OFF		0x4ae07d2c
extern  reg  dra7xx_device_prm_prm_voltsetup_mpu_off;
#define DRA7XX_DEVICE_PRM_PRM_VOLTSETUP_MM_OFF		0x4ae07d30
extern  reg  dra7xx_device_prm_prm_voltsetup_mm_off;
#define DRA7XX_DEVICE_PRM_PRM_VOLTSETUP_CORE_RET_SLEEP	0x4ae07d34
extern  reg  dra7xx_device_prm_prm_voltsetup_core_ret_sleep;
#define DRA7XX_DEVICE_PRM_PRM_VOLTSETUP_MPU_RET_SLEEP	0x4ae07d38
extern  reg  dra7xx_device_prm_prm_voltsetup_mpu_ret_sleep;
#define DRA7XX_DEVICE_PRM_PRM_VOLTSETUP_MM_RET_SLEEP	0x4ae07d3c
extern  reg  dra7xx_device_prm_prm_voltsetup_mm_ret_sleep;
#define DRA7XX_DEVICE_PRM_PRM_VP_CORE_CONFIG		0x4ae07d40
extern  reg  dra7xx_device_prm_prm_vp_core_config;
#define DRA7XX_DEVICE_PRM_PRM_VP_CORE_STATUS		0x4ae07d44
extern  reg  dra7xx_device_prm_prm_vp_core_status;
#define DRA7XX_DEVICE_PRM_PRM_VP_CORE_VLIMITTO		0x4ae07d48
extern  reg  dra7xx_device_prm_prm_vp_core_vlimitto;
#define DRA7XX_DEVICE_PRM_PRM_VP_CORE_VOLTAGE		0x4ae07d4c
extern  reg  dra7xx_device_prm_prm_vp_core_voltage;
#define DRA7XX_DEVICE_PRM_PRM_VP_CORE_VSTEPMAX		0x4ae07d50
extern  reg  dra7xx_device_prm_prm_vp_core_vstepmax;
#define DRA7XX_DEVICE_PRM_PRM_VP_CORE_VSTEPMIN		0x4ae07d54
extern  reg  dra7xx_device_prm_prm_vp_core_vstepmin;
#define DRA7XX_DEVICE_PRM_PRM_VP_MPU_CONFIG		0x4ae07d58
extern  reg  dra7xx_device_prm_prm_vp_mpu_config;
#define DRA7XX_DEVICE_PRM_PRM_VP_MPU_STATUS		0x4ae07d5c
extern  reg  dra7xx_device_prm_prm_vp_mpu_status;
#define DRA7XX_DEVICE_PRM_PRM_VP_MPU_VLIMITTO		0x4ae07d60
extern  reg  dra7xx_device_prm_prm_vp_mpu_vlimitto;
#define DRA7XX_DEVICE_PRM_PRM_VP_MPU_VOLTAGE		0x4ae07d64
extern  reg  dra7xx_device_prm_prm_vp_mpu_voltage;
#define DRA7XX_DEVICE_PRM_PRM_VP_MPU_VSTEPMAX		0x4ae07d68
extern  reg  dra7xx_device_prm_prm_vp_mpu_vstepmax;
#define DRA7XX_DEVICE_PRM_PRM_VP_MPU_VSTEPMIN		0x4ae07d6c
extern  reg  dra7xx_device_prm_prm_vp_mpu_vstepmin;
#define DRA7XX_DEVICE_PRM_PRM_VP_MM_CONFIG		0x4ae07d70
extern  reg  dra7xx_device_prm_prm_vp_mm_config;
#define DRA7XX_DEVICE_PRM_PRM_VP_MM_STATUS		0x4ae07d74
extern  reg  dra7xx_device_prm_prm_vp_mm_status;
#define DRA7XX_DEVICE_PRM_PRM_VP_MM_VLIMITTO		0x4ae07d78
extern  reg  dra7xx_device_prm_prm_vp_mm_vlimitto;
#define DRA7XX_DEVICE_PRM_PRM_VP_MM_VOLTAGE		0x4ae07d7c
extern  reg  dra7xx_device_prm_prm_vp_mm_voltage;
#define DRA7XX_DEVICE_PRM_PRM_VP_MM_VSTEPMAX		0x4ae07d80
extern  reg  dra7xx_device_prm_prm_vp_mm_vstepmax;
#define DRA7XX_DEVICE_PRM_PRM_VP_MM_VSTEPMIN		0x4ae07d84
extern  reg  dra7xx_device_prm_prm_vp_mm_vstepmin;
#define DRA7XX_DEVICE_PRM_PRM_VC_SMPS_CORE_CONFIG	0x4ae07d88
extern  reg  dra7xx_device_prm_prm_vc_smps_core_config;
#define DRA7XX_DEVICE_PRM_PRM_VC_SMPS_MM_CONFIG		0x4ae07d8c
extern  reg  dra7xx_device_prm_prm_vc_smps_mm_config;
#define DRA7XX_DEVICE_PRM_PRM_VC_SMPS_MPU_CONFIG	0x4ae07d90
extern  reg  dra7xx_device_prm_prm_vc_smps_mpu_config;
#define DRA7XX_DEVICE_PRM_PRM_VC_VAL_CMD_VDD_CORE_L	0x4ae07d94
extern  reg  dra7xx_device_prm_prm_vc_val_cmd_vdd_core_l;
#define DRA7XX_DEVICE_PRM_PRM_VC_VAL_CMD_VDD_MM_L	0x4ae07d98
extern  reg  dra7xx_device_prm_prm_vc_val_cmd_vdd_mm_l;
#define DRA7XX_DEVICE_PRM_PRM_VC_VAL_CMD_VDD_MPU_L	0x4ae07d9c
extern  reg  dra7xx_device_prm_prm_vc_val_cmd_vdd_mpu_l;
#define DRA7XX_DEVICE_PRM_PRM_VC_VAL_BYPASS		0x4ae07da0
extern  reg  dra7xx_device_prm_prm_vc_val_bypass;
#define DRA7XX_DEVICE_PRM_PRM_VC_CORE_ERRST		0x4ae07da4
extern  reg  dra7xx_device_prm_prm_vc_core_errst;
#define DRA7XX_DEVICE_PRM_PRM_VC_MM_ERRST		0x4ae07da8
extern  reg  dra7xx_device_prm_prm_vc_mm_errst;
#define DRA7XX_DEVICE_PRM_PRM_VC_MPU_ERRST		0x4ae07dac
extern  reg  dra7xx_device_prm_prm_vc_mpu_errst;
#define DRA7XX_DEVICE_PRM_PRM_VC_BYPASS_ERRST		0x4ae07db0
extern  reg  dra7xx_device_prm_prm_vc_bypass_errst;
#define DRA7XX_DEVICE_PRM_PRM_VC_CFG_I2C_MODE		0x4ae07db4
extern  reg  dra7xx_device_prm_prm_vc_cfg_i2c_mode;
#define DRA7XX_DEVICE_PRM_PRM_VC_CFG_I2C_CLK		0x4ae07db8
extern  reg  dra7xx_device_prm_prm_vc_cfg_i2c_clk;
#define DRA7XX_DEVICE_PRM_PRM_SRAM_COUNT		0x4ae07dbc
extern  reg  dra7xx_device_prm_prm_sram_count;
#define DRA7XX_DEVICE_PRM_PRM_SRAM_WKUP_SETUP		0x4ae07dc0
extern  reg  dra7xx_device_prm_prm_sram_wkup_setup;
#define DRA7XX_DEVICE_PRM_PRM_SLDO_CORE_SETUP		0x4ae07dc4
extern  reg  dra7xx_device_prm_prm_sldo_core_setup;
#define DRA7XX_DEVICE_PRM_PRM_SLDO_CORE_CTRL		0x4ae07dc8
extern  reg  dra7xx_device_prm_prm_sldo_core_ctrl;
#define DRA7XX_DEVICE_PRM_PRM_SLDO_MPU_SETUP		0x4ae07dcc
extern  reg  dra7xx_device_prm_prm_sldo_mpu_setup;
#define DRA7XX_DEVICE_PRM_PRM_SLDO_MPU_CTRL		0x4ae07dd0
extern  reg  dra7xx_device_prm_prm_sldo_mpu_ctrl;
#define DRA7XX_DEVICE_PRM_PRM_SLDO_GPU_SETUP		0x4ae07dd4
extern  reg  dra7xx_device_prm_prm_sldo_gpu_setup;
#define DRA7XX_DEVICE_PRM_PRM_SLDO_GPU_CTRL		0x4ae07dd8
extern  reg  dra7xx_device_prm_prm_sldo_gpu_ctrl;
#define DRA7XX_DEVICE_PRM_PRM_ABBLDO_MPU_SETUP		0x4ae07ddc
extern  reg  dra7xx_device_prm_prm_abbldo_mpu_setup;
#define DRA7XX_DEVICE_PRM_PRM_ABBLDO_MPU_CTRL		0x4ae07de0
extern  reg  dra7xx_device_prm_prm_abbldo_mpu_ctrl;
#define DRA7XX_DEVICE_PRM_PRM_ABBLDO_GPU_SETUP		0x4ae07de4
extern  reg  dra7xx_device_prm_prm_abbldo_gpu_setup;
#define DRA7XX_DEVICE_PRM_PRM_ABBLDO_GPU_CTRL		0x4ae07de8
extern  reg  dra7xx_device_prm_prm_abbldo_gpu_ctrl;
#define DRA7XX_DEVICE_PRM_PRM_BANDGAP_SETUP		0x4ae07dec
extern  reg  dra7xx_device_prm_prm_bandgap_setup;
#define DRA7XX_DEVICE_PRM_PRM_DEVICE_OFF_CTRL		0x4ae07df0
extern  reg  dra7xx_device_prm_prm_device_off_ctrl;
#define DRA7XX_DEVICE_PRM_PRM_PHASE1_CNDP		0x4ae07df4
extern  reg  dra7xx_device_prm_prm_phase1_cndp;
#define DRA7XX_DEVICE_PRM_PRM_PHASE2A_CNDP		0x4ae07df8
extern  reg  dra7xx_device_prm_prm_phase2a_cndp;
#define DRA7XX_DEVICE_PRM_PRM_PHASE2B_CNDP		0x4ae07dfc
extern  reg  dra7xx_device_prm_prm_phase2b_cndp;
#define DRA7XX_DEVICE_PRM_PRM_MODEM_IF_CTRL		0x4ae07e00
extern  reg  dra7xx_device_prm_prm_modem_if_ctrl;
#define DRA7XX_DEVICE_PRM_PRM_VOLTST_MPU		0x4ae07e10
extern  reg  dra7xx_device_prm_prm_voltst_mpu;
#define DRA7XX_DEVICE_PRM_PRM_VOLTST_MM			0x4ae07e14
extern  reg  dra7xx_device_prm_prm_voltst_mm;
#define DRA7XX_DEVICE_PRM_PRM_SLDO_DSPEVE_SETUP		0x4ae07e18
extern  reg  dra7xx_device_prm_prm_sldo_dspeve_setup;
#define DRA7XX_DEVICE_PRM_PRM_SLDO_IVA_SETUP		0x4ae07e1c
extern  reg  dra7xx_device_prm_prm_sldo_iva_setup;
#define DRA7XX_DEVICE_PRM_PRM_ABBLDO_DSPEVE_CTRL	0x4ae07e20
extern  reg  dra7xx_device_prm_prm_abbldo_dspeve_ctrl;
#define DRA7XX_DEVICE_PRM_PRM_ABBLDO_IVA_CTRL		0x4ae07e24
extern  reg  dra7xx_device_prm_prm_abbldo_iva_ctrl;
#define DRA7XX_DEVICE_PRM_PRM_SLDO_DSPEVE_CTRL		0x4ae07e28
extern  reg  dra7xx_device_prm_prm_sldo_dspeve_ctrl;
#define DRA7XX_DEVICE_PRM_PRM_SLDO_IVA_CTRL		0x4ae07e2c
extern  reg  dra7xx_device_prm_prm_sldo_iva_ctrl;
#define DRA7XX_DEVICE_PRM_PRM_ABBLDO_DSPEVE_SETUP	0x4ae07e30
extern  reg  dra7xx_device_prm_prm_abbldo_dspeve_setup;
#define DRA7XX_DEVICE_PRM_PRM_ABBLDO_IVA_SETUP		0x4ae07e34
extern  reg  dra7xx_device_prm_prm_abbldo_iva_setup;
#define DRA7XX_DEVICE_PRM_MOD_REGCOUNT			75
extern reg *dra7xx_device_prm_mod[DRA7XX_DEVICE_PRM_MOD_REGCOUNT + 1];

#define DRA7XX_GPU_PRM_PM_GPU_PWRSTCTRL		0x4ae07200
extern  reg  dra7xx_gpu_prm_pm_gpu_pwrstctrl;
#define DRA7XX_GPU_PRM_PM_GPU_PWRSTST		0x4ae07204
extern  reg  dra7xx_gpu_prm_pm_gpu_pwrstst;
#define DRA7XX_GPU_PRM_RM_GPU_GPU_CONTEXT	0x4ae07224
extern  reg  dra7xx_gpu_prm_rm_gpu_gpu_context;
#define DRA7XX_GPU_PRM_MOD_REGCOUNT		3
extern reg *dra7xx_gpu_prm_mod[DRA7XX_GPU_PRM_MOD_REGCOUNT + 1];

#define DRA7XX_COREAON_PRM_PM_COREAON_SMARTREFLEX_MPU_WKDEP		0x4ae06628
extern  reg  dra7xx_coreaon_prm_pm_coreaon_smartreflex_mpu_wkdep;
#define DRA7XX_COREAON_PRM_RM_COREAON_SMARTREFLEX_MPU_CONTEXT		0x4ae0662c
extern  reg  dra7xx_coreaon_prm_rm_coreaon_smartreflex_mpu_context;
#define DRA7XX_COREAON_PRM_PM_COREAON_SMARTREFLEX_CORE_WKDEP		0x4ae06638
extern  reg  dra7xx_coreaon_prm_pm_coreaon_smartreflex_core_wkdep;
#define DRA7XX_COREAON_PRM_RM_COREAON_SMARTREFLEX_CORE_CONTEXT		0x4ae0663c
extern  reg  dra7xx_coreaon_prm_rm_coreaon_smartreflex_core_context;
#define DRA7XX_COREAON_PRM_PM_COREAON_SMARTREFLEX_GPU_WKDEP		0x4ae06658
extern  reg  dra7xx_coreaon_prm_pm_coreaon_smartreflex_gpu_wkdep;
#define DRA7XX_COREAON_PRM_RM_COREAON_SMARTREFLEX_GPU_CONTEXT		0x4ae0665c
extern  reg  dra7xx_coreaon_prm_rm_coreaon_smartreflex_gpu_context;
#define DRA7XX_COREAON_PRM_PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP		0x4ae06668
extern  reg  dra7xx_coreaon_prm_pm_coreaon_smartreflex_dspeve_wkdep;
#define DRA7XX_COREAON_PRM_RM_COREAON_SMARTREFLEX_DSPEVE_CONTEXT	0x4ae0666c
extern  reg  dra7xx_coreaon_prm_rm_coreaon_smartreflex_dspeve_context;
#define DRA7XX_COREAON_PRM_PM_COREAON_SMARTREFLEX_IVAHD_WKDEP		0x4ae06678
extern  reg  dra7xx_coreaon_prm_pm_coreaon_smartreflex_ivahd_wkdep;
#define DRA7XX_COREAON_PRM_RM_COREAON_SMARTREFLEX_IVAHD_CONTEXT		0x4ae0667c
extern  reg  dra7xx_coreaon_prm_rm_coreaon_smartreflex_ivahd_context;
#define DRA7XX_COREAON_PRM_RM_COREAON_DUMMY_MODULE1_CONTEXT		0x4ae066ac
extern  reg  dra7xx_coreaon_prm_rm_coreaon_dummy_module1_context;
#define DRA7XX_COREAON_PRM_RM_COREAON_DUMMY_MODULE2_CONTEXT		0x4ae066bc
extern  reg  dra7xx_coreaon_prm_rm_coreaon_dummy_module2_context;
#define DRA7XX_COREAON_PRM_RM_COREAON_DUMMY_MODULE3_CONTEXT		0x4ae066cc
extern  reg  dra7xx_coreaon_prm_rm_coreaon_dummy_module3_context;
#define DRA7XX_COREAON_PRM_RM_COREAON_DUMMY_MODULE4_CONTEXT		0x4ae066dc
extern  reg  dra7xx_coreaon_prm_rm_coreaon_dummy_module4_context;
#define DRA7XX_COREAON_PRM_MOD_REGCOUNT					14
extern reg *dra7xx_coreaon_prm_mod[DRA7XX_COREAON_PRM_MOD_REGCOUNT + 1];

#define DRA7XX_CUSTEFUSE_PRM_PM_CUSTEFUSE_PWRSTCTRL			0x4ae07600
extern  reg  dra7xx_custefuse_prm_pm_custefuse_pwrstctrl;
#define DRA7XX_CUSTEFUSE_PRM_PM_CUSTEFUSE_PWRSTST			0x4ae07604
extern  reg  dra7xx_custefuse_prm_pm_custefuse_pwrstst;
#define DRA7XX_CUSTEFUSE_PRM_RM_CUSTEFUSE_EFUSE_CTRL_CUST_CONTEXT	0x4ae07624
extern  reg  dra7xx_custefuse_prm_rm_custefuse_efuse_ctrl_cust_context;
#define DRA7XX_CUSTEFUSE_PRM_MOD_REGCOUNT				3
extern reg *dra7xx_custefuse_prm_mod[DRA7XX_CUSTEFUSE_PRM_MOD_REGCOUNT + 1];

#define DRA7XX_CKGEN_PRM_CM_CLKSEL_SYSCLK1			0x4ae06100
extern  reg  dra7xx_ckgen_prm_cm_clksel_sysclk1;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_WKUPAON			0x4ae06108
extern  reg  dra7xx_ckgen_prm_cm_clksel_wkupaon;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_ABE_PLL_REF			0x4ae0610c
extern  reg  dra7xx_ckgen_prm_cm_clksel_abe_pll_ref;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_SYS				0x4ae06110
extern  reg  dra7xx_ckgen_prm_cm_clksel_sys;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_ABE_PLL_BYPAS		0x4ae06114
extern  reg  dra7xx_ckgen_prm_cm_clksel_abe_pll_bypas;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_ABE_PLL_SYS			0x4ae06118
extern  reg  dra7xx_ckgen_prm_cm_clksel_abe_pll_sys;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_ABE_24M			0x4ae0611c
extern  reg  dra7xx_ckgen_prm_cm_clksel_abe_24m;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_ABE_SYS			0x4ae06120
extern  reg  dra7xx_ckgen_prm_cm_clksel_abe_sys;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_HDMI_MCASP_AUX		0x4ae06124
extern  reg  dra7xx_ckgen_prm_cm_clksel_hdmi_mcasp_aux;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_HDMI_TIMER			0x4ae06128
extern  reg  dra7xx_ckgen_prm_cm_clksel_hdmi_timer;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_MCASP_SYS			0x4ae0612c
extern  reg  dra7xx_ckgen_prm_cm_clksel_mcasp_sys;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_MLBP_MCASP			0x4ae06130
extern  reg  dra7xx_ckgen_prm_cm_clksel_mlbp_mcasp;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_MLB_MCASP			0x4ae06134
extern  reg  dra7xx_ckgen_prm_cm_clksel_mlb_mcasp;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_PER_ABE_X1_GFCLK_MCASP_AUX	0x4ae06138
extern  reg  dra7xx_ckgen_prm_cm_clksel_per_abe_x1_gfclk_mcasp_aux;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_SYS_CLK1_32K			0x4ae06140
extern  reg  dra7xx_ckgen_prm_cm_clksel_sys_clk1_32k;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_TIMER_SYS			0x4ae06144
extern  reg  dra7xx_ckgen_prm_cm_clksel_timer_sys;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_VIDEO1_MCASP_AUX		0x4ae06148
extern  reg  dra7xx_ckgen_prm_cm_clksel_video1_mcasp_aux;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_VIDEO1_TIMER			0x4ae0614c
extern  reg  dra7xx_ckgen_prm_cm_clksel_video1_timer;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_VIDEO2_MCASP_AUX		0x4ae06150
extern  reg  dra7xx_ckgen_prm_cm_clksel_video2_mcasp_aux;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_VIDEO2_TIMER			0x4ae06154
extern  reg  dra7xx_ckgen_prm_cm_clksel_video2_timer;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_CLKOUTMUX0			0x4ae06158
extern  reg  dra7xx_ckgen_prm_cm_clksel_clkoutmux0;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_CLKOUTMUX1			0x4ae0615c
extern  reg  dra7xx_ckgen_prm_cm_clksel_clkoutmux1;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_CLKOUTMUX2			0x4ae06160
extern  reg  dra7xx_ckgen_prm_cm_clksel_clkoutmux2;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_HDMI_PLL_SYS			0x4ae06164
extern  reg  dra7xx_ckgen_prm_cm_clksel_hdmi_pll_sys;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_VIDEO1_PLL_SYS		0x4ae06168
extern  reg  dra7xx_ckgen_prm_cm_clksel_video1_pll_sys;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_VIDEO2_PLL_SYS		0x4ae0616c
extern  reg  dra7xx_ckgen_prm_cm_clksel_video2_pll_sys;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_ABE_CLK_DIV			0x4ae06170
extern  reg  dra7xx_ckgen_prm_cm_clksel_abe_clk_div;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_ABE_GICLK_DIV		0x4ae06174
extern  reg  dra7xx_ckgen_prm_cm_clksel_abe_giclk_div;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_AESS_FCLK_DIV		0x4ae06178
extern  reg  dra7xx_ckgen_prm_cm_clksel_aess_fclk_div;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_EVE_CLK			0x4ae06180
extern  reg  dra7xx_ckgen_prm_cm_clksel_eve_clk;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_USB_OTG_CLK_CLKOUTMUX	0x4ae06184
extern  reg  dra7xx_ckgen_prm_cm_clksel_usb_otg_clk_clkoutmux;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_CORE_DPLL_OUT_CLK_CLKOUTMUX	0x4ae06188
extern  reg  dra7xx_ckgen_prm_cm_clksel_core_dpll_out_clk_clkoutmux;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_DSP_GFCLK_CLKOUTMUX		0x4ae0618c
extern  reg  dra7xx_ckgen_prm_cm_clksel_dsp_gfclk_clkoutmux;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_EMIF_PHY_GCLK_CLKOUTMUX	0x4ae06190
extern  reg  dra7xx_ckgen_prm_cm_clksel_emif_phy_gclk_clkoutmux;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_EMU_CLK_CLKOUTMUX		0x4ae06194
extern  reg  dra7xx_ckgen_prm_cm_clksel_emu_clk_clkoutmux;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_FUNC_96M_AON_CLK_CLKOUTMUX	0x4ae06198
extern  reg  dra7xx_ckgen_prm_cm_clksel_func_96m_aon_clk_clkoutmux;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_GMAC_250M_CLK_CLKOUTMUX	0x4ae0619c
extern  reg  dra7xx_ckgen_prm_cm_clksel_gmac_250m_clk_clkoutmux;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_GPU_GCLK_CLKOUTMUX		0x4ae061a0
extern  reg  dra7xx_ckgen_prm_cm_clksel_gpu_gclk_clkoutmux;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_HDMI_CLK_CLKOUTMUX		0x4ae061a4
extern  reg  dra7xx_ckgen_prm_cm_clksel_hdmi_clk_clkoutmux;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_IVA_GCLK_CLKOUTMUX		0x4ae061a8
extern  reg  dra7xx_ckgen_prm_cm_clksel_iva_gclk_clkoutmux;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_L3INIT_480M_GFCLK_CLKOUTMUX	0x4ae061ac
extern  reg  dra7xx_ckgen_prm_cm_clksel_l3init_480m_gfclk_clkoutmux;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_MPU_GCLK_CLKOUTMUX		0x4ae061b0
extern  reg  dra7xx_ckgen_prm_cm_clksel_mpu_gclk_clkoutmux;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_PCIE1_CLK_CLKOUTMUX		0x4ae061b4
extern  reg  dra7xx_ckgen_prm_cm_clksel_pcie1_clk_clkoutmux;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_PCIE2_CLK_CLKOUTMUX		0x4ae061b8
extern  reg  dra7xx_ckgen_prm_cm_clksel_pcie2_clk_clkoutmux;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_PER_ABE_X1_CLK_CLKOUTMUX	0x4ae061bc
extern  reg  dra7xx_ckgen_prm_cm_clksel_per_abe_x1_clk_clkoutmux;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_SATA_CLK_CLKOUTMUX		0x4ae061c0
extern  reg  dra7xx_ckgen_prm_cm_clksel_sata_clk_clkoutmux;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_SECURE_32K_CLK_CLKOUTMUX	0x4ae061c4
extern  reg  dra7xx_ckgen_prm_cm_clksel_secure_32k_clk_clkoutmux;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_SYS_CLK1_CLKOUTMUX		0x4ae061c8
extern  reg  dra7xx_ckgen_prm_cm_clksel_sys_clk1_clkoutmux;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_SYS_CLK2_CLKOUTMUX		0x4ae061cc
extern  reg  dra7xx_ckgen_prm_cm_clksel_sys_clk2_clkoutmux;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_VIDEO1_CLK_CLKOUTMUX		0x4ae061d0
extern  reg  dra7xx_ckgen_prm_cm_clksel_video1_clk_clkoutmux;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_VIDEO2_CLK_CLKOUTMUX		0x4ae061d4
extern  reg  dra7xx_ckgen_prm_cm_clksel_video2_clk_clkoutmux;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_ABE_LP_CLK			0x4ae061d8
extern  reg  dra7xx_ckgen_prm_cm_clksel_abe_lp_clk;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_ADC_GFCLK			0x4ae061dc
extern  reg  dra7xx_ckgen_prm_cm_clksel_adc_gfclk;
#define DRA7XX_CKGEN_PRM_CM_CLKSEL_EVE_GFCLK_CLKOUTMUX		0x4ae061e0
extern  reg  dra7xx_ckgen_prm_cm_clksel_eve_gfclk_clkoutmux;
#define DRA7XX_CKGEN_PRM_MOD_REGCOUNT				54
extern reg *dra7xx_ckgen_prm_mod[DRA7XX_CKGEN_PRM_MOD_REGCOUNT + 1];

#define DRA7XX_INSTR_PRM_PMI_IDENTICATION	0x4ae07f00
extern  reg  dra7xx_instr_prm_pmi_identication;
#define DRA7XX_INSTR_PRM_PMI_SYS_CONFIG		0x4ae07f10
extern  reg  dra7xx_instr_prm_pmi_sys_config;
#define DRA7XX_INSTR_PRM_PMI_STATUS		0x4ae07f14
extern  reg  dra7xx_instr_prm_pmi_status;
#define DRA7XX_INSTR_PRM_PMI_CONFIGURATION	0x4ae07f24
extern  reg  dra7xx_instr_prm_pmi_configuration;
#define DRA7XX_INSTR_PRM_PMI_CLASS_FILTERING	0x4ae07f28
extern  reg  dra7xx_instr_prm_pmi_class_filtering;
#define DRA7XX_INSTR_PRM_PMI_TRIGGERING		0x4ae07f2c
extern  reg  dra7xx_instr_prm_pmi_triggering;
#define DRA7XX_INSTR_PRM_PMI_SAMPLING		0x4ae07f30
extern  reg  dra7xx_instr_prm_pmi_sampling;
#define DRA7XX_INSTR_PRM_MOD_REGCOUNT		7
extern reg *dra7xx_instr_prm_mod[DRA7XX_INSTR_PRM_MOD_REGCOUNT + 1];

#define DRA7XX_IVA_PRM_PM_IVA_PWRSTCTRL		0x4ae06f00
extern  reg  dra7xx_iva_prm_pm_iva_pwrstctrl;
#define DRA7XX_IVA_PRM_PM_IVA_PWRSTST		0x4ae06f04
extern  reg  dra7xx_iva_prm_pm_iva_pwrstst;
#define DRA7XX_IVA_PRM_RM_IVA_RSTCTRL		0x4ae06f10
extern  reg  dra7xx_iva_prm_rm_iva_rstctrl;
#define DRA7XX_IVA_PRM_RM_IVA_RSTST		0x4ae06f14
extern  reg  dra7xx_iva_prm_rm_iva_rstst;
#define DRA7XX_IVA_PRM_RM_IVA_IVA_CONTEXT	0x4ae06f24
extern  reg  dra7xx_iva_prm_rm_iva_iva_context;
#define DRA7XX_IVA_PRM_RM_IVA_SL2_CONTEXT	0x4ae06f2c
extern  reg  dra7xx_iva_prm_rm_iva_sl2_context;
#define DRA7XX_IVA_PRM_MOD_REGCOUNT		6
extern reg *dra7xx_iva_prm_mod[DRA7XX_IVA_PRM_MOD_REGCOUNT + 1];

#define DRA7XX_CORE_PRM_PM_CORE_PWRSTCTRL		0x4ae06700
extern  reg  dra7xx_core_prm_pm_core_pwrstctrl;
#define DRA7XX_CORE_PRM_PM_CORE_PWRSTST			0x4ae06704
extern  reg  dra7xx_core_prm_pm_core_pwrstst;
#define DRA7XX_CORE_PRM_RM_L3MAIN1_L3_MAIN_1_CONTEXT	0x4ae06724
extern  reg  dra7xx_core_prm_rm_l3main1_l3_main_1_context;
#define DRA7XX_CORE_PRM_RM_L3MAIN1_GPMC_CONTEXT		0x4ae0672c
extern  reg  dra7xx_core_prm_rm_l3main1_gpmc_context;
#define DRA7XX_CORE_PRM_RM_L3MAIN1_MMU_EDMA_CONTEXT	0x4ae06734
extern  reg  dra7xx_core_prm_rm_l3main1_mmu_edma_context;
#define DRA7XX_CORE_PRM_RM_L3MAIN1_MMU_PCIESS_CONTEXT	0x4ae0674c
extern  reg  dra7xx_core_prm_rm_l3main1_mmu_pciess_context;
#define DRA7XX_CORE_PRM_PM_L3MAIN1_OCMC_RAM1_WKDEP	0x4ae06750
extern  reg  dra7xx_core_prm_pm_l3main1_ocmc_ram1_wkdep;
#define DRA7XX_CORE_PRM_RM_L3MAIN1_OCMC_RAM1_CONTEXT	0x4ae06754
extern  reg  dra7xx_core_prm_rm_l3main1_ocmc_ram1_context;
#define DRA7XX_CORE_PRM_PM_L3MAIN1_OCMC_RAM2_WKDEP	0x4ae06758
extern  reg  dra7xx_core_prm_pm_l3main1_ocmc_ram2_wkdep;
#define DRA7XX_CORE_PRM_RM_L3MAIN1_OCMC_RAM2_CONTEXT	0x4ae0675c
extern  reg  dra7xx_core_prm_rm_l3main1_ocmc_ram2_context;
#define DRA7XX_CORE_PRM_PM_L3MAIN1_OCMC_RAM3_WKDEP	0x4ae06760
extern  reg  dra7xx_core_prm_pm_l3main1_ocmc_ram3_wkdep;
#define DRA7XX_CORE_PRM_RM_L3MAIN1_OCMC_RAM3_CONTEXT	0x4ae06764
extern  reg  dra7xx_core_prm_rm_l3main1_ocmc_ram3_context;
#define DRA7XX_CORE_PRM_RM_L3MAIN1_OCMC_ROM_CONTEXT	0x4ae0676c
extern  reg  dra7xx_core_prm_rm_l3main1_ocmc_rom_context;
#define DRA7XX_CORE_PRM_PM_L3MAIN1_TPCC_WKDEP		0x4ae06770
extern  reg  dra7xx_core_prm_pm_l3main1_tpcc_wkdep;
#define DRA7XX_CORE_PRM_RM_L3MAIN1_TPCC_CONTEXT		0x4ae06774
extern  reg  dra7xx_core_prm_rm_l3main1_tpcc_context;
#define DRA7XX_CORE_PRM_PM_L3MAIN1_TPTC1_WKDEP		0x4ae06778
extern  reg  dra7xx_core_prm_pm_l3main1_tptc1_wkdep;
#define DRA7XX_CORE_PRM_RM_L3MAIN1_TPTC1_CONTEXT	0x4ae0677c
extern  reg  dra7xx_core_prm_rm_l3main1_tptc1_context;
#define DRA7XX_CORE_PRM_PM_L3MAIN1_TPTC2_WKDEP		0x4ae06780
extern  reg  dra7xx_core_prm_pm_l3main1_tptc2_wkdep;
#define DRA7XX_CORE_PRM_RM_L3MAIN1_TPTC2_CONTEXT	0x4ae06784
extern  reg  dra7xx_core_prm_rm_l3main1_tptc2_context;
#define DRA7XX_CORE_PRM_RM_L3MAIN1_VCP1_CONTEXT		0x4ae0678c
extern  reg  dra7xx_core_prm_rm_l3main1_vcp1_context;
#define DRA7XX_CORE_PRM_RM_L3MAIN1_VCP2_CONTEXT		0x4ae06794
extern  reg  dra7xx_core_prm_rm_l3main1_vcp2_context;
#define DRA7XX_CORE_PRM_RM_L3MAIN1_SPARE_CME_CONTEXT	0x4ae0679c
extern  reg  dra7xx_core_prm_rm_l3main1_spare_cme_context;
#define DRA7XX_CORE_PRM_RM_L3MAIN1_SPARE_HDMI_CONTEXT	0x4ae067a4
extern  reg  dra7xx_core_prm_rm_l3main1_spare_hdmi_context;
#define DRA7XX_CORE_PRM_RM_L3MAIN1_SPARE_ICM_CONTEXT	0x4ae067ac
extern  reg  dra7xx_core_prm_rm_l3main1_spare_icm_context;
#define DRA7XX_CORE_PRM_RM_L3MAIN1_SPARE_IVA2_CONTEXT	0x4ae067b4
extern  reg  dra7xx_core_prm_rm_l3main1_spare_iva2_context;
#define DRA7XX_CORE_PRM_RM_L3MAIN1_SPARE_SATA2_CONTEXT	0x4ae067bc
extern  reg  dra7xx_core_prm_rm_l3main1_spare_sata2_context;
#define DRA7XX_CORE_PRM_RM_L3MAIN1_SPARE_UNKNOWN4_CONTEXT	0x4ae067c4
extern  reg  dra7xx_core_prm_rm_l3main1_spare_unknown4_context;
#define DRA7XX_CORE_PRM_RM_L3MAIN1_SPARE_UNKNOWN5_CONTEXT	0x4ae067cc
extern  reg  dra7xx_core_prm_rm_l3main1_spare_unknown5_context;
#define DRA7XX_CORE_PRM_RM_L3MAIN1_SPARE_UNKNOWN6_CONTEXT	0x4ae067d4
extern  reg  dra7xx_core_prm_rm_l3main1_spare_unknown6_context;
#define DRA7XX_CORE_PRM_RM_L3MAIN1_SPARE_VIDEOPLL1_CONTEXT	0x4ae067dc
extern  reg  dra7xx_core_prm_rm_l3main1_spare_videopll1_context;
#define DRA7XX_CORE_PRM_RM_L3MAIN1_SPARE_VIDEOPLL2_CONTEXT	0x4ae067f4
extern  reg  dra7xx_core_prm_rm_l3main1_spare_videopll2_context;
#define DRA7XX_CORE_PRM_RM_L3MAIN1_SPARE_VIDEOPLL3_CONTEXT	0x4ae067fc
extern  reg  dra7xx_core_prm_rm_l3main1_spare_videopll3_context;
#define DRA7XX_CORE_PRM_RM_IPU2_RSTCTRL			0x4ae06910
extern  reg  dra7xx_core_prm_rm_ipu2_rstctrl;
#define DRA7XX_CORE_PRM_RM_IPU2_RSTST			0x4ae06914
extern  reg  dra7xx_core_prm_rm_ipu2_rstst;
#define DRA7XX_CORE_PRM_RM_IPU2_IPU2_CONTEXT		0x4ae06924
extern  reg  dra7xx_core_prm_rm_ipu2_ipu2_context;
#define DRA7XX_CORE_PRM_RM_DMA_DMA_SYSTEM_CONTEXT	0x4ae06a24
extern  reg  dra7xx_core_prm_rm_dma_dma_system_context;
#define DRA7XX_CORE_PRM_RM_EMIF_DMM_CONTEXT		0x4ae06b24
extern  reg  dra7xx_core_prm_rm_emif_dmm_context;
#define DRA7XX_CORE_PRM_RM_EMIF_EMIF_OCP_FW_CONTEXT	0x4ae06b2c
extern  reg  dra7xx_core_prm_rm_emif_emif_ocp_fw_context;
#define DRA7XX_CORE_PRM_RM_EMIF_EMIF1_CONTEXT		0x4ae06b34
extern  reg  dra7xx_core_prm_rm_emif_emif1_context;
#define DRA7XX_CORE_PRM_RM_EMIF_EMIF2_CONTEXT		0x4ae06b3c
extern  reg  dra7xx_core_prm_rm_emif_emif2_context;
#define DRA7XX_CORE_PRM_RM_EMIF_EMIF_DLL_CONTEXT	0x4ae06b44
extern  reg  dra7xx_core_prm_rm_emif_emif_dll_context;
#define DRA7XX_CORE_PRM_RM_ATL_ATL_CONTEXT		0x4ae06c24
extern  reg  dra7xx_core_prm_rm_atl_atl_context;
#define DRA7XX_CORE_PRM_RM_L4CFG_L4_CFG_CONTEXT		0x4ae06d24
extern  reg  dra7xx_core_prm_rm_l4cfg_l4_cfg_context;
#define DRA7XX_CORE_PRM_RM_L4CFG_SPINLOCK_CONTEXT	0x4ae06d2c
extern  reg  dra7xx_core_prm_rm_l4cfg_spinlock_context;
#define DRA7XX_CORE_PRM_RM_L4CFG_MAILBOX1_CONTEXT	0x4ae06d34
extern  reg  dra7xx_core_prm_rm_l4cfg_mailbox1_context;
#define DRA7XX_CORE_PRM_RM_L4CFG_SAR_ROM_CONTEXT	0x4ae06d3c
extern  reg  dra7xx_core_prm_rm_l4cfg_sar_rom_context;
#define DRA7XX_CORE_PRM_RM_L4CFG_OCP2SCP2_CONTEXT	0x4ae06d44
extern  reg  dra7xx_core_prm_rm_l4cfg_ocp2scp2_context;
#define DRA7XX_CORE_PRM_RM_L4CFG_MAILBOX2_CONTEXT	0x4ae06d4c
extern  reg  dra7xx_core_prm_rm_l4cfg_mailbox2_context;
#define DRA7XX_CORE_PRM_RM_L4CFG_MAILBOX3_CONTEXT	0x4ae06d54
extern  reg  dra7xx_core_prm_rm_l4cfg_mailbox3_context;
#define DRA7XX_CORE_PRM_RM_L4CFG_MAILBOX4_CONTEXT	0x4ae06d5c
extern  reg  dra7xx_core_prm_rm_l4cfg_mailbox4_context;
#define DRA7XX_CORE_PRM_RM_L4CFG_MAILBOX5_CONTEXT	0x4ae06d64
extern  reg  dra7xx_core_prm_rm_l4cfg_mailbox5_context;
#define DRA7XX_CORE_PRM_RM_L4CFG_MAILBOX6_CONTEXT	0x4ae06d6c
extern  reg  dra7xx_core_prm_rm_l4cfg_mailbox6_context;
#define DRA7XX_CORE_PRM_RM_L4CFG_MAILBOX7_CONTEXT	0x4ae06d74
extern  reg  dra7xx_core_prm_rm_l4cfg_mailbox7_context;
#define DRA7XX_CORE_PRM_RM_L4CFG_MAILBOX8_CONTEXT	0x4ae06d7c
extern  reg  dra7xx_core_prm_rm_l4cfg_mailbox8_context;
#define DRA7XX_CORE_PRM_RM_L4CFG_MAILBOX9_CONTEXT	0x4ae06d84
extern  reg  dra7xx_core_prm_rm_l4cfg_mailbox9_context;
#define DRA7XX_CORE_PRM_RM_L4CFG_MAILBOX10_CONTEXT	0x4ae06d8c
extern  reg  dra7xx_core_prm_rm_l4cfg_mailbox10_context;
#define DRA7XX_CORE_PRM_RM_L4CFG_MAILBOX11_CONTEXT	0x4ae06d94
extern  reg  dra7xx_core_prm_rm_l4cfg_mailbox11_context;
#define DRA7XX_CORE_PRM_RM_L4CFG_MAILBOX12_CONTEXT	0x4ae06d9c
extern  reg  dra7xx_core_prm_rm_l4cfg_mailbox12_context;
#define DRA7XX_CORE_PRM_RM_L4CFG_MAILBOX13_CONTEXT	0x4ae06da4
extern  reg  dra7xx_core_prm_rm_l4cfg_mailbox13_context;
#define DRA7XX_CORE_PRM_RM_L4CFG_SPARE_SMARTREFLEX_RTC_CONTEXT		0x4ae06dac
extern  reg  dra7xx_core_prm_rm_l4cfg_spare_smartreflex_rtc_context;
#define DRA7XX_CORE_PRM_RM_L4CFG_SPARE_SMARTREFLEX_SDRAM_CONTEXT	0x4ae06db4
extern  reg  dra7xx_core_prm_rm_l4cfg_spare_smartreflex_sdram_context;
#define DRA7XX_CORE_PRM_RM_L4CFG_SPARE_SMARTREFLEX_WKUP_CONTEXT		0x4ae06dbc
extern  reg  dra7xx_core_prm_rm_l4cfg_spare_smartreflex_wkup_context;
#define DRA7XX_CORE_PRM_RM_L4CFG_IO_DELAY_BLOCK_CONTEXT			0x4ae06dc4
extern  reg  dra7xx_core_prm_rm_l4cfg_io_delay_block_context;
#define DRA7XX_CORE_PRM_RM_L3INSTR_L3_MAIN_2_CONTEXT	0x4ae06e24
extern  reg  dra7xx_core_prm_rm_l3instr_l3_main_2_context;
#define DRA7XX_CORE_PRM_RM_L3INSTR_L3_INSTR_CONTEXT	0x4ae06e2c
extern  reg  dra7xx_core_prm_rm_l3instr_l3_instr_context;
#define DRA7XX_CORE_PRM_RM_L3INSTR_OCP_WP_NOC_CONTEXT	0x4ae06e44
extern  reg  dra7xx_core_prm_rm_l3instr_ocp_wp_noc_context;
#define DRA7XX_CORE_PRM_MOD_REGCOUNT			66
extern reg *dra7xx_core_prm_mod[DRA7XX_CORE_PRM_MOD_REGCOUNT + 1];

#define DRA7XX_EMU_PRM_PM_EMU_PWRSTCTRL		0x4ae07900
extern  reg  dra7xx_emu_prm_pm_emu_pwrstctrl;
#define DRA7XX_EMU_PRM_PM_EMU_PWRSTST		0x4ae07904
extern  reg  dra7xx_emu_prm_pm_emu_pwrstst;
#define DRA7XX_EMU_PRM_RM_EMU_DEBUGSS_CONTEXT	0x4ae07924
extern  reg  dra7xx_emu_prm_rm_emu_debugss_context;
#define DRA7XX_EMU_PRM_MOD_REGCOUNT		3
extern reg *dra7xx_emu_prm_mod[DRA7XX_EMU_PRM_MOD_REGCOUNT + 1];

#define DRA7XX_MPU_PRM_PM_MPU_PWRSTCTRL		0x4ae06300
extern  reg  dra7xx_mpu_prm_pm_mpu_pwrstctrl;
#define DRA7XX_MPU_PRM_PM_MPU_PWRSTST		0x4ae06304
extern  reg  dra7xx_mpu_prm_pm_mpu_pwrstst;
#define DRA7XX_MPU_PRM_RM_MPU_MPU_CONTEXT	0x4ae06324
extern  reg  dra7xx_mpu_prm_rm_mpu_mpu_context;
#define DRA7XX_MPU_PRM_MOD_REGCOUNT		3
extern reg *dra7xx_mpu_prm_mod[DRA7XX_MPU_PRM_MOD_REGCOUNT + 1];

#define DRA7XX_L3INIT_PRM_PM_L3INIT_PWRSTCTRL		0x4ae07300
extern  reg  dra7xx_l3init_prm_pm_l3init_pwrstctrl;
#define DRA7XX_L3INIT_PRM_PM_L3INIT_PWRSTST		0x4ae07304
extern  reg  dra7xx_l3init_prm_pm_l3init_pwrstst;
#define DRA7XX_L3INIT_PRM_RM_PCIESS_RSTCTRL		0x4ae07310
extern  reg  dra7xx_l3init_prm_rm_pciess_rstctrl;
#define DRA7XX_L3INIT_PRM_RM_PCIESS_RSTST		0x4ae07314
extern  reg  dra7xx_l3init_prm_rm_pciess_rstst;
#define DRA7XX_L3INIT_PRM_PM_L3INIT_MMC1_WKDEP		0x4ae07328
extern  reg  dra7xx_l3init_prm_pm_l3init_mmc1_wkdep;
#define DRA7XX_L3INIT_PRM_RM_L3INIT_MMC1_CONTEXT	0x4ae0732c
extern  reg  dra7xx_l3init_prm_rm_l3init_mmc1_context;
#define DRA7XX_L3INIT_PRM_PM_L3INIT_MMC2_WKDEP		0x4ae07330
extern  reg  dra7xx_l3init_prm_pm_l3init_mmc2_wkdep;
#define DRA7XX_L3INIT_PRM_RM_L3INIT_MMC2_CONTEXT	0x4ae07334
extern  reg  dra7xx_l3init_prm_rm_l3init_mmc2_context;
#define DRA7XX_L3INIT_PRM_PM_L3INIT_USB_OTG_SS2_WKDEP	0x4ae07340
extern  reg  dra7xx_l3init_prm_pm_l3init_usb_otg_ss2_wkdep;
#define DRA7XX_L3INIT_PRM_RM_L3INIT_USB_OTG_SS2_CONTEXT	0x4ae07344
extern  reg  dra7xx_l3init_prm_rm_l3init_usb_otg_ss2_context;
#define DRA7XX_L3INIT_PRM_PM_L3INIT_USB_OTG_SS3_WKDEP	0x4ae07348
extern  reg  dra7xx_l3init_prm_pm_l3init_usb_otg_ss3_wkdep;
#define DRA7XX_L3INIT_PRM_RM_L3INIT_USB_OTG_SS3_CONTEXT	0x4ae0734c
extern  reg  dra7xx_l3init_prm_rm_l3init_usb_otg_ss3_context;
#define DRA7XX_L3INIT_PRM_PM_L3INIT_USB_OTG_SS4_WKDEP	0x4ae07350
extern  reg  dra7xx_l3init_prm_pm_l3init_usb_otg_ss4_wkdep;
#define DRA7XX_L3INIT_PRM_RM_L3INIT_USB_OTG_SS4_CONTEXT	0x4ae07354
extern  reg  dra7xx_l3init_prm_rm_l3init_usb_otg_ss4_context;
#define DRA7XX_L3INIT_PRM_RM_L3INIT_MLB_SS_CONTEXT	0x4ae0735c
extern  reg  dra7xx_l3init_prm_rm_l3init_mlb_ss_context;
#define DRA7XX_L3INIT_PRM_RM_L3INIT_IEEE1500_2_OCP_CONTEXT	0x4ae0737c
extern  reg  dra7xx_l3init_prm_rm_l3init_ieee1500_2_ocp_context;
#define DRA7XX_L3INIT_PRM_PM_L3INIT_SATA_WKDEP		0x4ae07388
extern  reg  dra7xx_l3init_prm_pm_l3init_sata_wkdep;
#define DRA7XX_L3INIT_PRM_RM_L3INIT_SATA_CONTEXT	0x4ae0738c
extern  reg  dra7xx_l3init_prm_rm_l3init_sata_context;
#define DRA7XX_L3INIT_PRM_PM_PCIE_PCIESS1_WKDEP		0x4ae073b0
extern  reg  dra7xx_l3init_prm_pm_pcie_pciess1_wkdep;
#define DRA7XX_L3INIT_PRM_RM_PCIE_PCIESS1_CONTEXT	0x4ae073b4
extern  reg  dra7xx_l3init_prm_rm_pcie_pciess1_context;
#define DRA7XX_L3INIT_PRM_PM_PCIE_PCIESS2_WKDEP		0x4ae073b8
extern  reg  dra7xx_l3init_prm_pm_pcie_pciess2_wkdep;
#define DRA7XX_L3INIT_PRM_RM_PCIE_PCIESS2_CONTEXT	0x4ae073bc
extern  reg  dra7xx_l3init_prm_rm_pcie_pciess2_context;
#define DRA7XX_L3INIT_PRM_RM_GMAC_GMAC_CONTEXT		0x4ae073d4
extern  reg  dra7xx_l3init_prm_rm_gmac_gmac_context;
#define DRA7XX_L3INIT_PRM_RM_L3INIT_OCP2SCP1_CONTEXT	0x4ae073e4
extern  reg  dra7xx_l3init_prm_rm_l3init_ocp2scp1_context;
#define DRA7XX_L3INIT_PRM_RM_L3INIT_OCP2SCP3_CONTEXT	0x4ae073ec
extern  reg  dra7xx_l3init_prm_rm_l3init_ocp2scp3_context;
#define DRA7XX_L3INIT_PRM_PM_L3INIT_USB_OTG_SS1_WKDEP	0x4ae073f0
extern  reg  dra7xx_l3init_prm_pm_l3init_usb_otg_ss1_wkdep;
#define DRA7XX_L3INIT_PRM_RM_L3INIT_USB_OTG_SS1_CONTEXT	0x4ae073f4
extern  reg  dra7xx_l3init_prm_rm_l3init_usb_otg_ss1_context;
#define DRA7XX_L3INIT_PRM_MOD_REGCOUNT			27
extern reg *dra7xx_l3init_prm_mod[DRA7XX_L3INIT_PRM_MOD_REGCOUNT + 1];

#define DRA7XX_PRCM_MPU_PRM_C0_PM_CPU0_PWRSTCTRL	0x48243400
extern  reg  dra7xx_prcm_mpu_prm_c0_pm_cpu0_pwrstctrl;
#define DRA7XX_PRCM_MPU_PRM_C0_PM_CPU0_PWRSTST		0x48243404
extern  reg  dra7xx_prcm_mpu_prm_c0_pm_cpu0_pwrstst;
#define DRA7XX_PRCM_MPU_PRM_C0_RM_CPU0_CPU0_RSTCTRL	0x48243410
extern  reg  dra7xx_prcm_mpu_prm_c0_rm_cpu0_cpu0_rstctrl;
#define DRA7XX_PRCM_MPU_PRM_C0_RM_CPU0_CPU0_RSTST	0x48243414
extern  reg  dra7xx_prcm_mpu_prm_c0_rm_cpu0_cpu0_rstst;
#define DRA7XX_PRCM_MPU_PRM_C0_RM_CPU0_CPU0_CONTEXT	0x48243424
extern  reg  dra7xx_prcm_mpu_prm_c0_rm_cpu0_cpu0_context;
#define DRA7XX_PRCM_MPU_PRM_C0_MOD_REGCOUNT		5
extern reg *dra7xx_prcm_mpu_prm_c0_mod[DRA7XX_PRCM_MPU_PRM_C0_MOD_REGCOUNT + 1];

#define DRA7XX_PRCM_MPU_PRM_C1_PM_CPU1_PWRSTCTRL	0x48243800
extern  reg  dra7xx_prcm_mpu_prm_c1_pm_cpu1_pwrstctrl;
#define DRA7XX_PRCM_MPU_PRM_C1_PM_CPU1_PWRSTST		0x48243804
extern  reg  dra7xx_prcm_mpu_prm_c1_pm_cpu1_pwrstst;
#define DRA7XX_PRCM_MPU_PRM_C1_RM_CPU1_CPU1_RSTCTRL	0x48243810
extern  reg  dra7xx_prcm_mpu_prm_c1_rm_cpu1_cpu1_rstctrl;
#define DRA7XX_PRCM_MPU_PRM_C1_RM_CPU1_CPU1_RSTST	0x48243814
extern  reg  dra7xx_prcm_mpu_prm_c1_rm_cpu1_cpu1_rstst;
#define DRA7XX_PRCM_MPU_PRM_C1_RM_CPU1_CPU1_CONTEXT	0x48243824
extern  reg  dra7xx_prcm_mpu_prm_c1_rm_cpu1_cpu1_context;
#define DRA7XX_PRCM_MPU_PRM_C1_MOD_REGCOUNT		5
extern reg *dra7xx_prcm_mpu_prm_c1_mod[DRA7XX_PRCM_MPU_PRM_C1_MOD_REGCOUNT + 1];

#define DRA7XX_EVE1_PRM_PM_EVE1_PWRSTCTRL	0x4ae07b40
extern  reg  dra7xx_eve1_prm_pm_eve1_pwrstctrl;
#define DRA7XX_EVE1_PRM_PM_EVE1_PWRSTST		0x4ae07b44
extern  reg  dra7xx_eve1_prm_pm_eve1_pwrstst;
#define DRA7XX_EVE1_PRM_RM_EVE1_RSTCTRL		0x4ae07b50
extern  reg  dra7xx_eve1_prm_rm_eve1_rstctrl;
#define DRA7XX_EVE1_PRM_RM_EVE1_RSTST		0x4ae07b54
extern  reg  dra7xx_eve1_prm_rm_eve1_rstst;
#define DRA7XX_EVE1_PRM_PM_EVE1_EVE1_WKDEP	0x4ae07b60
extern  reg  dra7xx_eve1_prm_pm_eve1_eve1_wkdep;
#define DRA7XX_EVE1_PRM_RM_EVE1_EVE1_CONTEXT	0x4ae07b64
extern  reg  dra7xx_eve1_prm_rm_eve1_eve1_context;
#define DRA7XX_EVE2_PRM_PM_EVE2_PWRSTCTRL	0x4ae07b80
extern  reg  dra7xx_eve2_prm_pm_eve2_pwrstctrl;
#define DRA7XX_EVE2_PRM_PM_EVE2_PWRSTST		0x4ae07b84
extern  reg  dra7xx_eve2_prm_pm_eve2_pwrstst;
#define DRA7XX_EVE2_PRM_RM_EVE2_RSTCTRL		0x4ae07b90
extern  reg  dra7xx_eve2_prm_rm_eve2_rstctrl;
#define DRA7XX_EVE2_PRM_RM_EVE2_RSTST		0x4ae07b94
extern  reg  dra7xx_eve2_prm_rm_eve2_rstst;
#define DRA7XX_EVE2_PRM_PM_EVE2_EVE2_WKDEP	0x4ae07ba0
extern  reg  dra7xx_eve2_prm_pm_eve2_eve2_wkdep;
#define DRA7XX_EVE2_PRM_RM_EVE2_EVE2_CONTEXT	0x4ae07ba4
extern  reg  dra7xx_eve2_prm_rm_eve2_eve2_context;
#define DRA7XX_EVE3_PRM_PM_EVE3_PWRSTCTRL	0x4ae07bc0
extern  reg  dra7xx_eve3_prm_pm_eve3_pwrstctrl;
#define DRA7XX_EVE3_PRM_PM_EVE3_PWRSTST		0x4ae07bc4
extern  reg  dra7xx_eve3_prm_pm_eve3_pwrstst;
#define DRA7XX_EVE3_PRM_RM_EVE3_RSTCTRL		0x4ae07bd0
extern  reg  dra7xx_eve3_prm_rm_eve3_rstctrl;
#define DRA7XX_EVE3_PRM_RM_EVE3_RSTST		0x4ae07bd4
extern  reg  dra7xx_eve3_prm_rm_eve3_rstst;
#define DRA7XX_EVE3_PRM_PM_EVE3_EVE3_WKDEP	0x4ae07be0
extern  reg  dra7xx_eve3_prm_pm_eve3_eve3_wkdep;
#define DRA7XX_EVE3_PRM_RM_EVE3_EVE3_CONTEXT	0x4ae07be4
extern  reg  dra7xx_eve3_prm_rm_eve3_eve3_context;
#define DRA7XX_EVE4_PRM_PM_EVE4_PWRSTCTRL	0x4ae07c00
extern  reg  dra7xx_eve4_prm_pm_eve4_pwrstctrl;
#define DRA7XX_EVE4_PRM_PM_EVE4_PWRSTST		0x4ae07c04
extern  reg  dra7xx_eve4_prm_pm_eve4_pwrstst;
#define DRA7XX_EVE4_PRM_RM_EVE4_RSTCTRL		0x4ae07c10
extern  reg  dra7xx_eve4_prm_rm_eve4_rstctrl;
#define DRA7XX_EVE4_PRM_RM_EVE4_RSTST		0x4ae07c14
extern  reg  dra7xx_eve4_prm_rm_eve4_rstst;
#define DRA7XX_EVE4_PRM_PM_EVE4_EVE4_WKDEP	0x4ae07c20
extern  reg  dra7xx_eve4_prm_pm_eve4_eve4_wkdep;
#define DRA7XX_EVE4_PRM_RM_EVE4_EVE4_CONTEXT	0x4ae07c24
extern  reg  dra7xx_eve4_prm_rm_eve4_eve4_context;
#define DRA7XX_EVE_PRM_MOD_REGCOUNT		24
extern reg *dra7xx_eve_prm_mod[DRA7XX_EVE_PRM_MOD_REGCOUNT + 1];

#define DRA7XX_IPU_PRM_PM_IPU_PWRSTCTRL		0x4ae06500
extern  reg  dra7xx_ipu_prm_pm_ipu_pwrstctrl;
#define DRA7XX_IPU_PRM_PM_IPU_PWRSTST		0x4ae06504
extern  reg  dra7xx_ipu_prm_pm_ipu_pwrstst;
#define DRA7XX_IPU_PRM_RM_IPU1_RSTCTRL		0x4ae06510
extern  reg  dra7xx_ipu_prm_rm_ipu1_rstctrl;
#define DRA7XX_IPU_PRM_RM_IPU1_RSTST		0x4ae06514
extern  reg  dra7xx_ipu_prm_rm_ipu1_rstst;
#define DRA7XX_IPU_PRM_RM_IPU1_IPU1_CONTEXT	0x4ae06524
extern  reg  dra7xx_ipu_prm_rm_ipu1_ipu1_context;
#define DRA7XX_IPU_PRM_PM_IPU_MCASP1_WKDEP	0x4ae06550
extern  reg  dra7xx_ipu_prm_pm_ipu_mcasp1_wkdep;
#define DRA7XX_IPU_PRM_RM_IPU_MCASP1_CONTEXT	0x4ae06554
extern  reg  dra7xx_ipu_prm_rm_ipu_mcasp1_context;
#define DRA7XX_IPU_PRM_PM_IPU_TIMER5_WKDEP	0x4ae06558
extern  reg  dra7xx_ipu_prm_pm_ipu_timer5_wkdep;
#define DRA7XX_IPU_PRM_RM_IPU_TIMER5_CONTEXT	0x4ae0655c
extern  reg  dra7xx_ipu_prm_rm_ipu_timer5_context;
#define DRA7XX_IPU_PRM_PM_IPU_TIMER6_WKDEP	0x4ae06560
extern  reg  dra7xx_ipu_prm_pm_ipu_timer6_wkdep;
#define DRA7XX_IPU_PRM_RM_IPU_TIMER6_CONTEXT	0x4ae06564
extern  reg  dra7xx_ipu_prm_rm_ipu_timer6_context;
#define DRA7XX_IPU_PRM_PM_IPU_TIMER7_WKDEP	0x4ae06568
extern  reg  dra7xx_ipu_prm_pm_ipu_timer7_wkdep;
#define DRA7XX_IPU_PRM_RM_IPU_TIMER7_CONTEXT	0x4ae0656c
extern  reg  dra7xx_ipu_prm_rm_ipu_timer7_context;
#define DRA7XX_IPU_PRM_PM_IPU_TIMER8_WKDEP	0x4ae06570
extern  reg  dra7xx_ipu_prm_pm_ipu_timer8_wkdep;
#define DRA7XX_IPU_PRM_RM_IPU_TIMER8_CONTEXT	0x4ae06574
extern  reg  dra7xx_ipu_prm_rm_ipu_timer8_context;
#define DRA7XX_IPU_PRM_PM_IPU_I2C5_WKDEP	0x4ae06578
extern  reg  dra7xx_ipu_prm_pm_ipu_i2c5_wkdep;
#define DRA7XX_IPU_PRM_RM_IPU_I2C5_CONTEXT	0x4ae0657c
extern  reg  dra7xx_ipu_prm_rm_ipu_i2c5_context;
#define DRA7XX_IPU_PRM_PM_IPU_UART6_WKDEP	0x4ae06580
extern  reg  dra7xx_ipu_prm_pm_ipu_uart6_wkdep;
#define DRA7XX_IPU_PRM_RM_IPU_UART6_CONTEXT	0x4ae06584
extern  reg  dra7xx_ipu_prm_rm_ipu_uart6_context;
#define DRA7XX_IPU_PRM_MOD_REGCOUNT		19
extern reg *dra7xx_ipu_prm_mod[DRA7XX_IPU_PRM_MOD_REGCOUNT + 1];

#define DRA7XX_L4PER_PRM_PM_L4PER_PWRSTCTRL		0x4ae07400
extern  reg  dra7xx_l4per_prm_pm_l4per_pwrstctrl;
#define DRA7XX_L4PER_PRM_PM_L4PER_PWRSTST		0x4ae07404
extern  reg  dra7xx_l4per_prm_pm_l4per_pwrstst;
#define DRA7XX_L4PER_PRM_RM_L4PER2_L4PER2_CONTEXT	0x4ae0740c
extern  reg  dra7xx_l4per_prm_rm_l4per2_l4per2_context;
#define DRA7XX_L4PER_PRM_RM_L4PER3_L4PER3_CONTEXT	0x4ae07414
extern  reg  dra7xx_l4per_prm_rm_l4per3_l4per3_context;
#define DRA7XX_L4PER_PRM_RM_L4PER2_PRUSS1_CONTEXT	0x4ae0741c
extern  reg  dra7xx_l4per_prm_rm_l4per2_pruss1_context;
#define DRA7XX_L4PER_PRM_RM_L4PER2_PRUSS2_CONTEXT	0x4ae07424
extern  reg  dra7xx_l4per_prm_rm_l4per2_pruss2_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_TIMER10_WKDEP		0x4ae07428
extern  reg  dra7xx_l4per_prm_pm_l4per_timer10_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER_TIMER10_CONTEXT	0x4ae0742c
extern  reg  dra7xx_l4per_prm_rm_l4per_timer10_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_TIMER11_WKDEP		0x4ae07430
extern  reg  dra7xx_l4per_prm_pm_l4per_timer11_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER_TIMER11_CONTEXT	0x4ae07434
extern  reg  dra7xx_l4per_prm_rm_l4per_timer11_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_TIMER2_WKDEP		0x4ae07438
extern  reg  dra7xx_l4per_prm_pm_l4per_timer2_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER_TIMER2_CONTEXT	0x4ae0743c
extern  reg  dra7xx_l4per_prm_rm_l4per_timer2_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_TIMER3_WKDEP		0x4ae07440
extern  reg  dra7xx_l4per_prm_pm_l4per_timer3_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER_TIMER3_CONTEXT	0x4ae07444
extern  reg  dra7xx_l4per_prm_rm_l4per_timer3_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_TIMER4_WKDEP		0x4ae07448
extern  reg  dra7xx_l4per_prm_pm_l4per_timer4_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER_TIMER4_CONTEXT	0x4ae0744c
extern  reg  dra7xx_l4per_prm_rm_l4per_timer4_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_TIMER9_WKDEP		0x4ae07450
extern  reg  dra7xx_l4per_prm_pm_l4per_timer9_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER_TIMER9_CONTEXT	0x4ae07454
extern  reg  dra7xx_l4per_prm_rm_l4per_timer9_context;
#define DRA7XX_L4PER_PRM_RM_L4PER_ELM_CONTEXT		0x4ae0745c
extern  reg  dra7xx_l4per_prm_rm_l4per_elm_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_GPIO2_WKDEP		0x4ae07460
extern  reg  dra7xx_l4per_prm_pm_l4per_gpio2_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER_GPIO2_CONTEXT		0x4ae07464
extern  reg  dra7xx_l4per_prm_rm_l4per_gpio2_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_GPIO3_WKDEP		0x4ae07468
extern  reg  dra7xx_l4per_prm_pm_l4per_gpio3_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER_GPIO3_CONTEXT		0x4ae0746c
extern  reg  dra7xx_l4per_prm_rm_l4per_gpio3_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_GPIO4_WKDEP		0x4ae07470
extern  reg  dra7xx_l4per_prm_pm_l4per_gpio4_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER_GPIO4_CONTEXT		0x4ae07474
extern  reg  dra7xx_l4per_prm_rm_l4per_gpio4_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_GPIO5_WKDEP		0x4ae07478
extern  reg  dra7xx_l4per_prm_pm_l4per_gpio5_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER_GPIO5_CONTEXT		0x4ae0747c
extern  reg  dra7xx_l4per_prm_rm_l4per_gpio5_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_GPIO6_WKDEP		0x4ae07480
extern  reg  dra7xx_l4per_prm_pm_l4per_gpio6_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER_GPIO6_CONTEXT		0x4ae07484
extern  reg  dra7xx_l4per_prm_rm_l4per_gpio6_context;
#define DRA7XX_L4PER_PRM_RM_L4PER_HDQ1W_CONTEXT		0x4ae0748c
extern  reg  dra7xx_l4per_prm_rm_l4per_hdq1w_context;
#define DRA7XX_L4PER_PRM_RM_L4PER2_PWMSS2_CONTEXT	0x4ae07494
extern  reg  dra7xx_l4per_prm_rm_l4per2_pwmss2_context;
#define DRA7XX_L4PER_PRM_RM_L4PER2_PWMSS3_CONTEXT	0x4ae0749c
extern  reg  dra7xx_l4per_prm_rm_l4per2_pwmss3_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_I2C1_WKDEP		0x4ae074a0
extern  reg  dra7xx_l4per_prm_pm_l4per_i2c1_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER_I2C1_CONTEXT		0x4ae074a4
extern  reg  dra7xx_l4per_prm_rm_l4per_i2c1_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_I2C2_WKDEP		0x4ae074a8
extern  reg  dra7xx_l4per_prm_pm_l4per_i2c2_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER_I2C2_CONTEXT		0x4ae074ac
extern  reg  dra7xx_l4per_prm_rm_l4per_i2c2_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_I2C3_WKDEP		0x4ae074b0
extern  reg  dra7xx_l4per_prm_pm_l4per_i2c3_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER_I2C3_CONTEXT		0x4ae074b4
extern  reg  dra7xx_l4per_prm_rm_l4per_i2c3_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_I2C4_WKDEP		0x4ae074b8
extern  reg  dra7xx_l4per_prm_pm_l4per_i2c4_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER_I2C4_CONTEXT		0x4ae074bc
extern  reg  dra7xx_l4per_prm_rm_l4per_i2c4_context;
#define DRA7XX_L4PER_PRM_RM_L4PER_L4PER1_CONTEXT	0x4ae074c0
extern  reg  dra7xx_l4per_prm_rm_l4per_l4per1_context;
#define DRA7XX_L4PER_PRM_RM_L4PER2_PWMSS1_CONTEXT	0x4ae074c4
extern  reg  dra7xx_l4per_prm_rm_l4per2_pwmss1_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_TIMER13_WKDEP		0x4ae074c8
extern  reg  dra7xx_l4per_prm_pm_l4per_timer13_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER3_TIMER13_CONTEXT	0x4ae074cc
extern  reg  dra7xx_l4per_prm_rm_l4per3_timer13_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_TIMER14_WKDEP		0x4ae074d0
extern  reg  dra7xx_l4per_prm_pm_l4per_timer14_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER3_TIMER14_CONTEXT	0x4ae074d4
extern  reg  dra7xx_l4per_prm_rm_l4per3_timer14_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_TIMER15_WKDEP		0x4ae074d8
extern  reg  dra7xx_l4per_prm_pm_l4per_timer15_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER3_TIMER15_CONTEXT	0x4ae074dc
extern  reg  dra7xx_l4per_prm_rm_l4per3_timer15_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_MCSPI1_WKDEP		0x4ae074f0
extern  reg  dra7xx_l4per_prm_pm_l4per_mcspi1_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER_MCSPI1_CONTEXT	0x4ae074f4
extern  reg  dra7xx_l4per_prm_rm_l4per_mcspi1_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_MCSPI2_WKDEP		0x4ae074f8
extern  reg  dra7xx_l4per_prm_pm_l4per_mcspi2_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER_MCSPI2_CONTEXT	0x4ae074fc
extern  reg  dra7xx_l4per_prm_rm_l4per_mcspi2_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_MCSPI3_WKDEP		0x4ae07500
extern  reg  dra7xx_l4per_prm_pm_l4per_mcspi3_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER_MCSPI3_CONTEXT	0x4ae07504
extern  reg  dra7xx_l4per_prm_rm_l4per_mcspi3_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_MCSPI4_WKDEP		0x4ae07508
extern  reg  dra7xx_l4per_prm_pm_l4per_mcspi4_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER_MCSPI4_CONTEXT	0x4ae0750c
extern  reg  dra7xx_l4per_prm_rm_l4per_mcspi4_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_GPIO7_WKDEP		0x4ae07510
extern  reg  dra7xx_l4per_prm_pm_l4per_gpio7_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER_GPIO7_CONTEXT		0x4ae07514
extern  reg  dra7xx_l4per_prm_rm_l4per_gpio7_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_GPIO8_WKDEP		0x4ae07518
extern  reg  dra7xx_l4per_prm_pm_l4per_gpio8_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER_GPIO8_CONTEXT		0x4ae0751c
extern  reg  dra7xx_l4per_prm_rm_l4per_gpio8_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_MMC3_WKDEP		0x4ae07520
extern  reg  dra7xx_l4per_prm_pm_l4per_mmc3_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER_MMC3_CONTEXT		0x4ae07524
extern  reg  dra7xx_l4per_prm_rm_l4per_mmc3_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_MMC4_WKDEP		0x4ae07528
extern  reg  dra7xx_l4per_prm_pm_l4per_mmc4_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER_MMC4_CONTEXT		0x4ae0752c
extern  reg  dra7xx_l4per_prm_rm_l4per_mmc4_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_TIMER16_WKDEP		0x4ae07530
extern  reg  dra7xx_l4per_prm_pm_l4per_timer16_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER3_TIMER16_CONTEXT	0x4ae07534
extern  reg  dra7xx_l4per_prm_rm_l4per3_timer16_context;
#define DRA7XX_L4PER_PRM_PM_L4PER2_QSPI_WKDEP		0x4ae07538
extern  reg  dra7xx_l4per_prm_pm_l4per2_qspi_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER2_QSPI_CONTEXT		0x4ae0753c
extern  reg  dra7xx_l4per_prm_rm_l4per2_qspi_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_UART1_WKDEP		0x4ae07540
extern  reg  dra7xx_l4per_prm_pm_l4per_uart1_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER_UART1_CONTEXT		0x4ae07544
extern  reg  dra7xx_l4per_prm_rm_l4per_uart1_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_UART2_WKDEP		0x4ae07548
extern  reg  dra7xx_l4per_prm_pm_l4per_uart2_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER_UART2_CONTEXT		0x4ae0754c
extern  reg  dra7xx_l4per_prm_rm_l4per_uart2_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_UART3_WKDEP		0x4ae07550
extern  reg  dra7xx_l4per_prm_pm_l4per_uart3_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER_UART3_CONTEXT		0x4ae07554
extern  reg  dra7xx_l4per_prm_rm_l4per_uart3_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_UART4_WKDEP		0x4ae07558
extern  reg  dra7xx_l4per_prm_pm_l4per_uart4_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER_UART4_CONTEXT		0x4ae0755c
extern  reg  dra7xx_l4per_prm_rm_l4per_uart4_context;
#define DRA7XX_L4PER_PRM_PM_L4PER2_MCASP2_WKDEP		0x4ae07560
extern  reg  dra7xx_l4per_prm_pm_l4per2_mcasp2_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER2_MCASP2_CONTEXT	0x4ae07564
extern  reg  dra7xx_l4per_prm_rm_l4per2_mcasp2_context;
#define DRA7XX_L4PER_PRM_PM_L4PER2_MCASP3_WKDEP		0x4ae07568
extern  reg  dra7xx_l4per_prm_pm_l4per2_mcasp3_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER2_MCASP3_CONTEXT	0x4ae0756c
extern  reg  dra7xx_l4per_prm_rm_l4per2_mcasp3_context;
#define DRA7XX_L4PER_PRM_PM_L4PER_UART5_WKDEP		0x4ae07570
extern  reg  dra7xx_l4per_prm_pm_l4per_uart5_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER_UART5_CONTEXT		0x4ae07574
extern  reg  dra7xx_l4per_prm_rm_l4per_uart5_context;
#define DRA7XX_L4PER_PRM_PM_L4PER2_MCASP5_WKDEP		0x4ae07578
extern  reg  dra7xx_l4per_prm_pm_l4per2_mcasp5_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER2_MCASP5_CONTEXT	0x4ae0757c
extern  reg  dra7xx_l4per_prm_rm_l4per2_mcasp5_context;
#define DRA7XX_L4PER_PRM_PM_L4PER2_MCASP6_WKDEP		0x4ae07580
extern  reg  dra7xx_l4per_prm_pm_l4per2_mcasp6_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER2_MCASP6_CONTEXT	0x4ae07584
extern  reg  dra7xx_l4per_prm_rm_l4per2_mcasp6_context;
#define DRA7XX_L4PER_PRM_PM_L4PER2_MCASP7_WKDEP		0x4ae07588
extern  reg  dra7xx_l4per_prm_pm_l4per2_mcasp7_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER2_MCASP7_CONTEXT	0x4ae0758c
extern  reg  dra7xx_l4per_prm_rm_l4per2_mcasp7_context;
#define DRA7XX_L4PER_PRM_PM_L4PER2_MCASP8_WKDEP		0x4ae07590
extern  reg  dra7xx_l4per_prm_pm_l4per2_mcasp8_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER2_MCASP8_CONTEXT	0x4ae07594
extern  reg  dra7xx_l4per_prm_rm_l4per2_mcasp8_context;
#define DRA7XX_L4PER_PRM_PM_L4PER2_MCASP4_WKDEP		0x4ae07598
extern  reg  dra7xx_l4per_prm_pm_l4per2_mcasp4_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER2_MCASP4_CONTEXT	0x4ae0759c
extern  reg  dra7xx_l4per_prm_rm_l4per2_mcasp4_context;
#define DRA7XX_L4PER_PRM_RM_L4SEC_AES1_CONTEXT		0x4ae075a4
extern  reg  dra7xx_l4per_prm_rm_l4sec_aes1_context;
#define DRA7XX_L4PER_PRM_RM_L4SEC_AES2_CONTEXT		0x4ae075ac
extern  reg  dra7xx_l4per_prm_rm_l4sec_aes2_context;
#define DRA7XX_L4PER_PRM_RM_L4SEC_DES3DES_CONTEXT	0x4ae075b4
extern  reg  dra7xx_l4per_prm_rm_l4sec_des3des_context;
#define DRA7XX_L4PER_PRM_RM_L4SEC_FPKA_CONTEXT		0x4ae075bc
extern  reg  dra7xx_l4per_prm_rm_l4sec_fpka_context;
#define DRA7XX_L4PER_PRM_RM_L4SEC_RNG_CONTEXT		0x4ae075c4
extern  reg  dra7xx_l4per_prm_rm_l4sec_rng_context;
#define DRA7XX_L4PER_PRM_RM_L4SEC_SHA2MD51_CONTEXT	0x4ae075cc
extern  reg  dra7xx_l4per_prm_rm_l4sec_sha2md51_context;
#define DRA7XX_L4PER_PRM_PM_L4PER2_UART7_WKDEP		0x4ae075d0
extern  reg  dra7xx_l4per_prm_pm_l4per2_uart7_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER2_UART7_CONTEXT	0x4ae075d4
extern  reg  dra7xx_l4per_prm_rm_l4per2_uart7_context;
#define DRA7XX_L4PER_PRM_RM_L4SEC_DMA_CRYPTO_CONTEXT	0x4ae075dc
extern  reg  dra7xx_l4per_prm_rm_l4sec_dma_crypto_context;
#define DRA7XX_L4PER_PRM_PM_L4PER2_UART8_WKDEP		0x4ae075e0
extern  reg  dra7xx_l4per_prm_pm_l4per2_uart8_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER2_UART8_CONTEXT	0x4ae075e4
extern  reg  dra7xx_l4per_prm_rm_l4per2_uart8_context;
#define DRA7XX_L4PER_PRM_PM_L4PER2_UART9_WKDEP		0x4ae075e8
extern  reg  dra7xx_l4per_prm_pm_l4per2_uart9_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER2_UART9_CONTEXT	0x4ae075ec
extern  reg  dra7xx_l4per_prm_rm_l4per2_uart9_context;
#define DRA7XX_L4PER_PRM_PM_L4PER2_DCAN2_WKDEP		0x4ae075f0
extern  reg  dra7xx_l4per_prm_pm_l4per2_dcan2_wkdep;
#define DRA7XX_L4PER_PRM_RM_L4PER2_DCAN2_CONTEXT	0x4ae075f4
extern  reg  dra7xx_l4per_prm_rm_l4per2_dcan2_context;
#define DRA7XX_L4PER_PRM_RM_L4SEC_SHA2MD52_CONTEXT	0x4ae075fc
extern  reg  dra7xx_l4per_prm_rm_l4sec_sha2md52_context;
#define DRA7XX_L4PER_PRM_MOD_REGCOUNT			108
extern reg *dra7xx_l4per_prm_mod[DRA7XX_L4PER_PRM_MOD_REGCOUNT + 1];

#define DRA7XX_RTC_PRM_PM_RTC_RTCSS_WKDEP	0x4ae07c60
extern  reg  dra7xx_rtc_prm_pm_rtc_rtcss_wkdep;
#define DRA7XX_RTC_PRM_RM_RTC_RTCSS_CONTEXT	0x4ae07c64
extern  reg  dra7xx_rtc_prm_rm_rtc_rtcss_context;
#define DRA7XX_RTC_PRM_MOD_REGCOUNT		2
extern reg *dra7xx_rtc_prm_mod[DRA7XX_RTC_PRM_MOD_REGCOUNT + 1];

#define DRA7XX_VPE_PRM_PM_VPE_PWRSTCTRL		0x4ae07c80
extern  reg  dra7xx_vpe_prm_pm_vpe_pwrstctrl;
#define DRA7XX_VPE_PRM_PM_VPE_PWRSTST		0x4ae07c84
extern  reg  dra7xx_vpe_prm_pm_vpe_pwrstst;
#define DRA7XX_VPE_PRM_PM_VPE_VPE_WKDEP		0x4ae07ca0
extern  reg  dra7xx_vpe_prm_pm_vpe_vpe_wkdep;
#define DRA7XX_VPE_PRM_RM_VPE_VPE_CONTEXT	0x4ae07ca4
extern  reg  dra7xx_vpe_prm_rm_vpe_vpe_context;
#define DRA7XX_VPE_PRM_MOD_REGCOUNT		4
extern reg *dra7xx_vpe_prm_mod[DRA7XX_VPE_PRM_MOD_REGCOUNT + 1];

typedef enum {
	PRM_DRA7XX_DSS_PRM,
	PRM_DRA7XX_WKUPAON_PRM,
	PRM_DRA7XX_OCP_SOCKET_PRM,
	PRM_DRA7XX_CAM_PRM,
	PRM_DRA7XX_DSP_PRM,
	PRM_DRA7XX_DEVICE_PRM,
	PRM_DRA7XX_GPU_PRM,
	PRM_DRA7XX_COREAON_PRM,
	PRM_DRA7XX_CUSTEFUSE_PRM,
	PRM_DRA7XX_CKGEN_PRM,
	PRM_DRA7XX_INSTR_PRM,
	PRM_DRA7XX_IVA_PRM,
	PRM_DRA7XX_EMU_PRM,
	PRM_DRA7XX_MPU_PRM,
	PRM_DRA7XX_L3INIT_PRM,
	PRM_DRA7XX_CORE_PRM,
	PRM_DRA7XX_L4PER_PRM,
	PRM_DRA7XX_PRCM_MPU_PRM_C0,
	PRM_DRA7XX_PRCM_MPU_PRM_C1,
	PRM_DRA7XX_EVE_PRM,
	PRM_DRA7XX_IPU_PRM,
	PRM_DRA7XX_RTC_PRM,
	PRM_DRA7XX_VPE_PRM,
	PRM_DRA7XX_MODS_COUNT = 23
} prm_dra7xx_mod_id;

extern reg **prm_dra7xx_mods[PRM_DRA7XX_MODS_COUNT + 1];

extern const char *prm_dra7xx_mods_name[PRM_DRA7XX_MODS_COUNT];

#endif
