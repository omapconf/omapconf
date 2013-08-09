/*
 *
 * @Component			OMAPCONF
 * @Filename			prm_dra7xx-defs.c
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


#include <prm_dra7xx-defs.h>
#include <stdio.h>


reg dra7xx_dss_prm_pm_dss_pwrstctrl = {
	"PM_DSS_PWRSTCTRL",
	DRA7XX_DSS_PRM_PM_DSS_PWRSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_dss_prm_pm_dss_pwrstst = {
	"PM_DSS_PWRSTST",
	DRA7XX_DSS_PRM_PM_DSS_PWRSTST,
	0xDEADBEEF,
	0};
reg dra7xx_dss_prm_pm_dss_dss_wkdep = {
	"PM_DSS_DSS_WKDEP",
	DRA7XX_DSS_PRM_PM_DSS_DSS_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_dss_prm_rm_dss_dss_context = {
	"RM_DSS_DSS_CONTEXT",
	DRA7XX_DSS_PRM_RM_DSS_DSS_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_dss_prm_pm_dss_dss2_wkdep = {
	"PM_DSS_DSS2_WKDEP",
	DRA7XX_DSS_PRM_PM_DSS_DSS2_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_dss_prm_rm_dss_bb2d_context = {
	"RM_DSS_BB2D_CONTEXT",
	DRA7XX_DSS_PRM_RM_DSS_BB2D_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_dss_prm_rm_dss_sdvenc_context = {
	"RM_DSS_SDVENC_CONTEXT",
	DRA7XX_DSS_PRM_RM_DSS_SDVENC_CONTEXT,
	0xDEADBEEF,
	0};
reg *dra7xx_dss_prm_mod[DRA7XX_DSS_PRM_MOD_REGCOUNT + 1] = {
	&dra7xx_dss_prm_pm_dss_pwrstctrl,
	&dra7xx_dss_prm_pm_dss_pwrstst,
	&dra7xx_dss_prm_pm_dss_dss_wkdep,
	&dra7xx_dss_prm_rm_dss_dss_context,
	&dra7xx_dss_prm_pm_dss_dss2_wkdep,
	&dra7xx_dss_prm_rm_dss_bb2d_context,
	&dra7xx_dss_prm_rm_dss_sdvenc_context,
	NULL};

reg dra7xx_wkupaon_prm_rm_wkupaon_l4_wkup_context = {
	"RM_WKUPAON_L4_WKUP_CONTEXT",
	DRA7XX_WKUPAON_PRM_RM_WKUPAON_L4_WKUP_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_prm_pm_wkupaon_wd_timer1_wkdep = {
	"PM_WKUPAON_WD_TIMER1_WKDEP",
	DRA7XX_WKUPAON_PRM_PM_WKUPAON_WD_TIMER1_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_prm_rm_wkupaon_wd_timer1_context = {
	"RM_WKUPAON_WD_TIMER1_CONTEXT",
	DRA7XX_WKUPAON_PRM_RM_WKUPAON_WD_TIMER1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_prm_pm_wkupaon_wd_timer2_wkdep = {
	"PM_WKUPAON_WD_TIMER2_WKDEP",
	DRA7XX_WKUPAON_PRM_PM_WKUPAON_WD_TIMER2_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_prm_rm_wkupaon_wd_timer2_context = {
	"RM_WKUPAON_WD_TIMER2_CONTEXT",
	DRA7XX_WKUPAON_PRM_RM_WKUPAON_WD_TIMER2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_prm_pm_wkupaon_gpio1_wkdep = {
	"PM_WKUPAON_GPIO1_WKDEP",
	DRA7XX_WKUPAON_PRM_PM_WKUPAON_GPIO1_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_prm_rm_wkupaon_gpio1_context = {
	"RM_WKUPAON_GPIO1_CONTEXT",
	DRA7XX_WKUPAON_PRM_RM_WKUPAON_GPIO1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_prm_pm_wkupaon_timer1_wkdep = {
	"PM_WKUPAON_TIMER1_WKDEP",
	DRA7XX_WKUPAON_PRM_PM_WKUPAON_TIMER1_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_prm_rm_wkupaon_timer1_context = {
	"RM_WKUPAON_TIMER1_CONTEXT",
	DRA7XX_WKUPAON_PRM_RM_WKUPAON_TIMER1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_prm_pm_wkupaon_timer12_wkdep = {
	"PM_WKUPAON_TIMER12_WKDEP",
	DRA7XX_WKUPAON_PRM_PM_WKUPAON_TIMER12_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_prm_rm_wkupaon_timer12_context = {
	"RM_WKUPAON_TIMER12_CONTEXT",
	DRA7XX_WKUPAON_PRM_RM_WKUPAON_TIMER12_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_prm_rm_wkupaon_counter_32k_context = {
	"RM_WKUPAON_COUNTER_32K_CONTEXT",
	DRA7XX_WKUPAON_PRM_RM_WKUPAON_COUNTER_32K_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_prm_rm_wkupaon_sar_ram_context = {
	"RM_WKUPAON_SAR_RAM_CONTEXT",
	DRA7XX_WKUPAON_PRM_RM_WKUPAON_SAR_RAM_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_prm_pm_wkupaon_kbd_wkdep = {
	"PM_WKUPAON_KBD_WKDEP",
	DRA7XX_WKUPAON_PRM_PM_WKUPAON_KBD_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_prm_rm_wkupaon_kbd_context = {
	"RM_WKUPAON_KBD_CONTEXT",
	DRA7XX_WKUPAON_PRM_RM_WKUPAON_KBD_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_prm_pm_wkupaon_uart10_wkdep = {
	"PM_WKUPAON_UART10_WKDEP",
	DRA7XX_WKUPAON_PRM_PM_WKUPAON_UART10_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_prm_rm_wkupaon_uart10_context = {
	"RM_WKUPAON_UART10_CONTEXT",
	DRA7XX_WKUPAON_PRM_RM_WKUPAON_UART10_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_prm_pm_wkupaon_dcan1_wkdep = {
	"PM_WKUPAON_DCAN1_WKDEP",
	DRA7XX_WKUPAON_PRM_PM_WKUPAON_DCAN1_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_prm_rm_wkupaon_dcan1_context = {
	"RM_WKUPAON_DCAN1_CONTEXT",
	DRA7XX_WKUPAON_PRM_RM_WKUPAON_DCAN1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_prm_pm_wkupaon_adc_wkdep = {
	"PM_WKUPAON_ADC_WKDEP",
	DRA7XX_WKUPAON_PRM_PM_WKUPAON_ADC_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_prm_rm_wkupaon_adc_context = {
	"RM_WKUPAON_ADC_CONTEXT",
	DRA7XX_WKUPAON_PRM_RM_WKUPAON_ADC_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_prm_rm_wkupaon_spare_safety1_context = {
	"RM_WKUPAON_SPARE_SAFETY1_CONTEXT",
	DRA7XX_WKUPAON_PRM_RM_WKUPAON_SPARE_SAFETY1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_prm_rm_wkupaon_spare_safety2_context = {
	"RM_WKUPAON_SPARE_SAFETY2_CONTEXT",
	DRA7XX_WKUPAON_PRM_RM_WKUPAON_SPARE_SAFETY2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_prm_rm_wkupaon_spare_safety3_context = {
	"RM_WKUPAON_SPARE_SAFETY3_CONTEXT",
	DRA7XX_WKUPAON_PRM_RM_WKUPAON_SPARE_SAFETY3_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_prm_rm_wkupaon_spare_safety4_context = {
	"RM_WKUPAON_SPARE_SAFETY4_CONTEXT",
	DRA7XX_WKUPAON_PRM_RM_WKUPAON_SPARE_SAFETY4_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_prm_rm_wkupaon_spare_unknown2_context = {
	"RM_WKUPAON_SPARE_UNKNOWN2_CONTEXT",
	DRA7XX_WKUPAON_PRM_RM_WKUPAON_SPARE_UNKNOWN2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_prm_rm_wkupaon_spare_unknown3_context = {
	"RM_WKUPAON_SPARE_UNKNOWN3_CONTEXT",
	DRA7XX_WKUPAON_PRM_RM_WKUPAON_SPARE_UNKNOWN3_CONTEXT,
	0xDEADBEEF,
	0};
reg *dra7xx_wkupaon_prm_mod[DRA7XX_WKUPAON_PRM_MOD_REGCOUNT + 1] = {
	&dra7xx_wkupaon_prm_rm_wkupaon_l4_wkup_context,
	&dra7xx_wkupaon_prm_pm_wkupaon_wd_timer1_wkdep,
	&dra7xx_wkupaon_prm_rm_wkupaon_wd_timer1_context,
	&dra7xx_wkupaon_prm_pm_wkupaon_wd_timer2_wkdep,
	&dra7xx_wkupaon_prm_rm_wkupaon_wd_timer2_context,
	&dra7xx_wkupaon_prm_pm_wkupaon_gpio1_wkdep,
	&dra7xx_wkupaon_prm_rm_wkupaon_gpio1_context,
	&dra7xx_wkupaon_prm_pm_wkupaon_timer1_wkdep,
	&dra7xx_wkupaon_prm_rm_wkupaon_timer1_context,
	&dra7xx_wkupaon_prm_pm_wkupaon_timer12_wkdep,
	&dra7xx_wkupaon_prm_rm_wkupaon_timer12_context,
	&dra7xx_wkupaon_prm_rm_wkupaon_counter_32k_context,
	&dra7xx_wkupaon_prm_rm_wkupaon_sar_ram_context,
	&dra7xx_wkupaon_prm_pm_wkupaon_kbd_wkdep,
	&dra7xx_wkupaon_prm_rm_wkupaon_kbd_context,
	&dra7xx_wkupaon_prm_pm_wkupaon_uart10_wkdep,
	&dra7xx_wkupaon_prm_rm_wkupaon_uart10_context,
	&dra7xx_wkupaon_prm_pm_wkupaon_dcan1_wkdep,
	&dra7xx_wkupaon_prm_rm_wkupaon_dcan1_context,
	&dra7xx_wkupaon_prm_pm_wkupaon_adc_wkdep,
	&dra7xx_wkupaon_prm_rm_wkupaon_adc_context,
	&dra7xx_wkupaon_prm_rm_wkupaon_spare_safety1_context,
	&dra7xx_wkupaon_prm_rm_wkupaon_spare_safety2_context,
	&dra7xx_wkupaon_prm_rm_wkupaon_spare_safety3_context,
	&dra7xx_wkupaon_prm_rm_wkupaon_spare_safety4_context,
	&dra7xx_wkupaon_prm_rm_wkupaon_spare_unknown2_context,
	&dra7xx_wkupaon_prm_rm_wkupaon_spare_unknown3_context,
	NULL};

reg dra7xx_ocp_socket_prm_revision_prm = {
	"REVISION_PRM",
	DRA7XX_OCP_SOCKET_PRM_REVISION_PRM,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_prm_prm_irqstatus_mpu = {
	"PRM_IRQSTATUS_MPU",
	DRA7XX_OCP_SOCKET_PRM_PRM_IRQSTATUS_MPU,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_prm_prm_irqstatus_mpu_2 = {
	"PRM_IRQSTATUS_MPU_2",
	DRA7XX_OCP_SOCKET_PRM_PRM_IRQSTATUS_MPU_2,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_prm_prm_irqenable_mpu = {
	"PRM_IRQENABLE_MPU",
	DRA7XX_OCP_SOCKET_PRM_PRM_IRQENABLE_MPU,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_prm_prm_irqenable_mpu_2 = {
	"PRM_IRQENABLE_MPU_2",
	DRA7XX_OCP_SOCKET_PRM_PRM_IRQENABLE_MPU_2,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_prm_prm_irqstatus_ipu2 = {
	"PRM_IRQSTATUS_IPU2",
	DRA7XX_OCP_SOCKET_PRM_PRM_IRQSTATUS_IPU2,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_prm_prm_irqenable_ipu2 = {
	"PRM_IRQENABLE_IPU2",
	DRA7XX_OCP_SOCKET_PRM_PRM_IRQENABLE_IPU2,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_prm_prm_irqstatus_dsp1 = {
	"PRM_IRQSTATUS_DSP1",
	DRA7XX_OCP_SOCKET_PRM_PRM_IRQSTATUS_DSP1,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_prm_prm_irqenable_dsp1 = {
	"PRM_IRQENABLE_DSP1",
	DRA7XX_OCP_SOCKET_PRM_PRM_IRQENABLE_DSP1,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_prm_cm_prm_profiling_clkctrl = {
	"CM_PRM_PROFILING_CLKCTRL",
	DRA7XX_OCP_SOCKET_PRM_CM_PRM_PROFILING_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_prm_prm_irqenable_dsp2 = {
	"PRM_IRQENABLE_DSP2",
	DRA7XX_OCP_SOCKET_PRM_PRM_IRQENABLE_DSP2,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_prm_prm_irqenable_eve1 = {
	"PRM_IRQENABLE_EVE1",
	DRA7XX_OCP_SOCKET_PRM_PRM_IRQENABLE_EVE1,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_prm_prm_irqenable_eve2 = {
	"PRM_IRQENABLE_EVE2",
	DRA7XX_OCP_SOCKET_PRM_PRM_IRQENABLE_EVE2,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_prm_prm_irqenable_eve3 = {
	"PRM_IRQENABLE_EVE3",
	DRA7XX_OCP_SOCKET_PRM_PRM_IRQENABLE_EVE3,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_prm_prm_irqenable_eve4 = {
	"PRM_IRQENABLE_EVE4",
	DRA7XX_OCP_SOCKET_PRM_PRM_IRQENABLE_EVE4,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_prm_prm_irqenable_ipu1 = {
	"PRM_IRQENABLE_IPU1",
	DRA7XX_OCP_SOCKET_PRM_PRM_IRQENABLE_IPU1,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_prm_prm_irqstatus_dsp2 = {
	"PRM_IRQSTATUS_DSP2",
	DRA7XX_OCP_SOCKET_PRM_PRM_IRQSTATUS_DSP2,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_prm_prm_irqstatus_eve1 = {
	"PRM_IRQSTATUS_EVE1",
	DRA7XX_OCP_SOCKET_PRM_PRM_IRQSTATUS_EVE1,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_prm_prm_irqstatus_eve2 = {
	"PRM_IRQSTATUS_EVE2",
	DRA7XX_OCP_SOCKET_PRM_PRM_IRQSTATUS_EVE2,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_prm_prm_irqstatus_eve3 = {
	"PRM_IRQSTATUS_EVE3",
	DRA7XX_OCP_SOCKET_PRM_PRM_IRQSTATUS_EVE3,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_prm_prm_irqstatus_eve4 = {
	"PRM_IRQSTATUS_EVE4",
	DRA7XX_OCP_SOCKET_PRM_PRM_IRQSTATUS_EVE4,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_prm_prm_irqstatus_ipu1 = {
	"PRM_IRQSTATUS_IPU1",
	DRA7XX_OCP_SOCKET_PRM_PRM_IRQSTATUS_IPU1,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_prm_prm_debug_cfg1 = {
	"PRM_DEBUG_CFG1",
	DRA7XX_OCP_SOCKET_PRM_PRM_DEBUG_CFG1,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_prm_prm_debug_cfg2 = {
	"PRM_DEBUG_CFG2",
	DRA7XX_OCP_SOCKET_PRM_PRM_DEBUG_CFG2,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_prm_prm_debug_cfg3 = {
	"PRM_DEBUG_CFG3",
	DRA7XX_OCP_SOCKET_PRM_PRM_DEBUG_CFG3,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_prm_prm_debug_cfg = {
	"PRM_DEBUG_CFG",
	DRA7XX_OCP_SOCKET_PRM_PRM_DEBUG_CFG,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_prm_prm_debug_out = {
	"PRM_DEBUG_OUT",
	DRA7XX_OCP_SOCKET_PRM_PRM_DEBUG_OUT,
	0xDEADBEEF,
	0};
reg *dra7xx_ocp_socket_prm_mod[DRA7XX_OCP_SOCKET_PRM_MOD_REGCOUNT + 1] = {
	&dra7xx_ocp_socket_prm_revision_prm,
	&dra7xx_ocp_socket_prm_prm_irqstatus_mpu,
	&dra7xx_ocp_socket_prm_prm_irqstatus_mpu_2,
	&dra7xx_ocp_socket_prm_prm_irqenable_mpu,
	&dra7xx_ocp_socket_prm_prm_irqenable_mpu_2,
	&dra7xx_ocp_socket_prm_prm_irqstatus_ipu2,
	&dra7xx_ocp_socket_prm_prm_irqenable_ipu2,
	&dra7xx_ocp_socket_prm_prm_irqstatus_dsp1,
	&dra7xx_ocp_socket_prm_prm_irqenable_dsp1,
	&dra7xx_ocp_socket_prm_cm_prm_profiling_clkctrl,
	&dra7xx_ocp_socket_prm_prm_irqenable_dsp2,
	&dra7xx_ocp_socket_prm_prm_irqenable_eve1,
	&dra7xx_ocp_socket_prm_prm_irqenable_eve2,
	&dra7xx_ocp_socket_prm_prm_irqenable_eve3,
	&dra7xx_ocp_socket_prm_prm_irqenable_eve4,
	&dra7xx_ocp_socket_prm_prm_irqenable_ipu1,
	&dra7xx_ocp_socket_prm_prm_irqstatus_dsp2,
	&dra7xx_ocp_socket_prm_prm_irqstatus_eve1,
	&dra7xx_ocp_socket_prm_prm_irqstatus_eve2,
	&dra7xx_ocp_socket_prm_prm_irqstatus_eve3,
	&dra7xx_ocp_socket_prm_prm_irqstatus_eve4,
	&dra7xx_ocp_socket_prm_prm_irqstatus_ipu1,
	&dra7xx_ocp_socket_prm_prm_debug_cfg1,
	&dra7xx_ocp_socket_prm_prm_debug_cfg2,
	&dra7xx_ocp_socket_prm_prm_debug_cfg3,
	&dra7xx_ocp_socket_prm_prm_debug_cfg,
	&dra7xx_ocp_socket_prm_prm_debug_out,
	NULL};

reg dra7xx_cam_prm_pm_cam_pwrstctrl = {
	"PM_CAM_PWRSTCTRL",
	DRA7XX_CAM_PRM_PM_CAM_PWRSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_cam_prm_pm_cam_pwrstst = {
	"PM_CAM_PWRSTST",
	DRA7XX_CAM_PRM_PM_CAM_PWRSTST,
	0xDEADBEEF,
	0};
reg dra7xx_cam_prm_pm_cam_vip1_wkdep = {
	"PM_CAM_VIP1_WKDEP",
	DRA7XX_CAM_PRM_PM_CAM_VIP1_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_cam_prm_rm_cam_vip1_context = {
	"RM_CAM_VIP1_CONTEXT",
	DRA7XX_CAM_PRM_RM_CAM_VIP1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_cam_prm_pm_cam_vip2_wkdep = {
	"PM_CAM_VIP2_WKDEP",
	DRA7XX_CAM_PRM_PM_CAM_VIP2_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_cam_prm_rm_cam_vip2_context = {
	"RM_CAM_VIP2_CONTEXT",
	DRA7XX_CAM_PRM_RM_CAM_VIP2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_cam_prm_pm_cam_vip3_wkdep = {
	"PM_CAM_VIP3_WKDEP",
	DRA7XX_CAM_PRM_PM_CAM_VIP3_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_cam_prm_rm_cam_vip3_context = {
	"RM_CAM_VIP3_CONTEXT",
	DRA7XX_CAM_PRM_RM_CAM_VIP3_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_cam_prm_rm_cam_lvdsrx_context = {
	"RM_CAM_LVDSRX_CONTEXT",
	DRA7XX_CAM_PRM_RM_CAM_LVDSRX_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_cam_prm_rm_cam_csi1_context = {
	"RM_CAM_CSI1_CONTEXT",
	DRA7XX_CAM_PRM_RM_CAM_CSI1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_cam_prm_rm_cam_csi2_context = {
	"RM_CAM_CSI2_CONTEXT",
	DRA7XX_CAM_PRM_RM_CAM_CSI2_CONTEXT,
	0xDEADBEEF,
	0};
reg *dra7xx_cam_prm_mod[DRA7XX_CAM_PRM_MOD_REGCOUNT + 1] = {
	&dra7xx_cam_prm_pm_cam_pwrstctrl,
	&dra7xx_cam_prm_pm_cam_pwrstst,
	&dra7xx_cam_prm_pm_cam_vip1_wkdep,
	&dra7xx_cam_prm_rm_cam_vip1_context,
	&dra7xx_cam_prm_pm_cam_vip2_wkdep,
	&dra7xx_cam_prm_rm_cam_vip2_context,
	&dra7xx_cam_prm_pm_cam_vip3_wkdep,
	&dra7xx_cam_prm_rm_cam_vip3_context,
	&dra7xx_cam_prm_rm_cam_lvdsrx_context,
	&dra7xx_cam_prm_rm_cam_csi1_context,
	&dra7xx_cam_prm_rm_cam_csi2_context,
	NULL};

reg dra7xx_dsp1_prm_pm_dsp1_pwrstctrl = {
	"PM_DSP1_PWRSTCTRL",
	DRA7XX_DSP1_PRM_PM_DSP1_PWRSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_dsp1_prm_pm_dsp1_pwrstst = {
	"PM_DSP1_PWRSTST",
	DRA7XX_DSP1_PRM_PM_DSP1_PWRSTST,
	0xDEADBEEF,
	0};
reg dra7xx_dsp1_prm_rm_dsp1_rstctrl = {
	"RM_DSP1_RSTCTRL",
	DRA7XX_DSP1_PRM_RM_DSP1_RSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_dsp1_prm_rm_dsp1_rstst = {
	"RM_DSP1_RSTST",
	DRA7XX_DSP1_PRM_RM_DSP1_RSTST,
	0xDEADBEEF,
	0};
reg dra7xx_dsp1_prm_rm_dsp1_dsp1_context = {
	"RM_DSP1_DSP1_CONTEXT",
	DRA7XX_DSP1_PRM_RM_DSP1_DSP1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_dsp2_prm_pm_dsp2_pwrstctrl = {
	"PM_DSP2_PWRSTCTRL",
	DRA7XX_DSP2_PRM_PM_DSP2_PWRSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_dsp2_prm_pm_dsp2_pwrstst = {
	"PM_DSP2_PWRSTST",
	DRA7XX_DSP2_PRM_PM_DSP2_PWRSTST,
	0xDEADBEEF,
	0};
reg dra7xx_dsp2_prm_rm_dsp2_rstctrl = {
	"RM_DSP2_RSTCTRL",
	DRA7XX_DSP2_PRM_RM_DSP2_RSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_dsp2_prm_rm_dsp2_rstst = {
	"RM_DSP2_RSTST",
	DRA7XX_DSP2_PRM_RM_DSP2_RSTST,
	0xDEADBEEF,
	0};
reg dra7xx_dsp2_prm_rm_dsp2_dsp2_context = {
	"RM_DSP2_DSP2_CONTEXT",
	DRA7XX_DSP2_PRM_RM_DSP2_DSP2_CONTEXT,
	0xDEADBEEF,
	0};
reg *dra7xx_dsp_prm_mod[DRA7XX_DSP_PRM_MOD_REGCOUNT + 1] = {
	&dra7xx_dsp1_prm_pm_dsp1_pwrstctrl,
	&dra7xx_dsp1_prm_pm_dsp1_pwrstst,
	&dra7xx_dsp1_prm_rm_dsp1_rstctrl,
	&dra7xx_dsp1_prm_rm_dsp1_rstst,
	&dra7xx_dsp1_prm_rm_dsp1_dsp1_context,
	&dra7xx_dsp2_prm_pm_dsp2_pwrstctrl,
	&dra7xx_dsp2_prm_pm_dsp2_pwrstst,
	&dra7xx_dsp2_prm_rm_dsp2_rstctrl,
	&dra7xx_dsp2_prm_rm_dsp2_rstst,
	&dra7xx_dsp2_prm_rm_dsp2_dsp2_context,
	NULL};

reg dra7xx_device_prm_prm_rstctrl = {
	"PRM_RSTCTRL",
	DRA7XX_DEVICE_PRM_PRM_RSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_rstst = {
	"PRM_RSTST",
	DRA7XX_DEVICE_PRM_PRM_RSTST,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_rsttime = {
	"PRM_RSTTIME",
	DRA7XX_DEVICE_PRM_PRM_RSTTIME,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_clkreqctrl = {
	"PRM_CLKREQCTRL",
	DRA7XX_DEVICE_PRM_PRM_CLKREQCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_voltctrl = {
	"PRM_VOLTCTRL",
	DRA7XX_DEVICE_PRM_PRM_VOLTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_pwrreqctrl = {
	"PRM_PWRREQCTRL",
	DRA7XX_DEVICE_PRM_PRM_PWRREQCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_pscon_count = {
	"PRM_PSCON_COUNT",
	DRA7XX_DEVICE_PRM_PRM_PSCON_COUNT,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_io_count = {
	"PRM_IO_COUNT",
	DRA7XX_DEVICE_PRM_PRM_IO_COUNT,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_io_pmctrl = {
	"PRM_IO_PMCTRL",
	DRA7XX_DEVICE_PRM_PRM_IO_PMCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_voltsetup_warmreset = {
	"PRM_VOLTSETUP_WARMRESET",
	DRA7XX_DEVICE_PRM_PRM_VOLTSETUP_WARMRESET,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_voltsetup_core_off = {
	"PRM_VOLTSETUP_CORE_OFF",
	DRA7XX_DEVICE_PRM_PRM_VOLTSETUP_CORE_OFF,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_voltsetup_mpu_off = {
	"PRM_VOLTSETUP_MPU_OFF",
	DRA7XX_DEVICE_PRM_PRM_VOLTSETUP_MPU_OFF,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_voltsetup_mm_off = {
	"PRM_VOLTSETUP_MM_OFF",
	DRA7XX_DEVICE_PRM_PRM_VOLTSETUP_MM_OFF,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_voltsetup_core_ret_sleep = {
	"PRM_VOLTSETUP_CORE_RET_SLEEP",
	DRA7XX_DEVICE_PRM_PRM_VOLTSETUP_CORE_RET_SLEEP,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_voltsetup_mpu_ret_sleep = {
	"PRM_VOLTSETUP_MPU_RET_SLEEP",
	DRA7XX_DEVICE_PRM_PRM_VOLTSETUP_MPU_RET_SLEEP,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_voltsetup_mm_ret_sleep = {
	"PRM_VOLTSETUP_MM_RET_SLEEP",
	DRA7XX_DEVICE_PRM_PRM_VOLTSETUP_MM_RET_SLEEP,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vp_core_config = {
	"PRM_VP_CORE_CONFIG",
	DRA7XX_DEVICE_PRM_PRM_VP_CORE_CONFIG,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vp_core_status = {
	"PRM_VP_CORE_STATUS",
	DRA7XX_DEVICE_PRM_PRM_VP_CORE_STATUS,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vp_core_vlimitto = {
	"PRM_VP_CORE_VLIMITTO",
	DRA7XX_DEVICE_PRM_PRM_VP_CORE_VLIMITTO,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vp_core_voltage = {
	"PRM_VP_CORE_VOLTAGE",
	DRA7XX_DEVICE_PRM_PRM_VP_CORE_VOLTAGE,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vp_core_vstepmax = {
	"PRM_VP_CORE_VSTEPMAX",
	DRA7XX_DEVICE_PRM_PRM_VP_CORE_VSTEPMAX,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vp_core_vstepmin = {
	"PRM_VP_CORE_VSTEPMIN",
	DRA7XX_DEVICE_PRM_PRM_VP_CORE_VSTEPMIN,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vp_mpu_config = {
	"PRM_VP_MPU_CONFIG",
	DRA7XX_DEVICE_PRM_PRM_VP_MPU_CONFIG,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vp_mpu_status = {
	"PRM_VP_MPU_STATUS",
	DRA7XX_DEVICE_PRM_PRM_VP_MPU_STATUS,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vp_mpu_vlimitto = {
	"PRM_VP_MPU_VLIMITTO",
	DRA7XX_DEVICE_PRM_PRM_VP_MPU_VLIMITTO,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vp_mpu_voltage = {
	"PRM_VP_MPU_VOLTAGE",
	DRA7XX_DEVICE_PRM_PRM_VP_MPU_VOLTAGE,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vp_mpu_vstepmax = {
	"PRM_VP_MPU_VSTEPMAX",
	DRA7XX_DEVICE_PRM_PRM_VP_MPU_VSTEPMAX,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vp_mpu_vstepmin = {
	"PRM_VP_MPU_VSTEPMIN",
	DRA7XX_DEVICE_PRM_PRM_VP_MPU_VSTEPMIN,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vp_mm_config = {
	"PRM_VP_MM_CONFIG",
	DRA7XX_DEVICE_PRM_PRM_VP_MM_CONFIG,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vp_mm_status = {
	"PRM_VP_MM_STATUS",
	DRA7XX_DEVICE_PRM_PRM_VP_MM_STATUS,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vp_mm_vlimitto = {
	"PRM_VP_MM_VLIMITTO",
	DRA7XX_DEVICE_PRM_PRM_VP_MM_VLIMITTO,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vp_mm_voltage = {
	"PRM_VP_MM_VOLTAGE",
	DRA7XX_DEVICE_PRM_PRM_VP_MM_VOLTAGE,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vp_mm_vstepmax = {
	"PRM_VP_MM_VSTEPMAX",
	DRA7XX_DEVICE_PRM_PRM_VP_MM_VSTEPMAX,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vp_mm_vstepmin = {
	"PRM_VP_MM_VSTEPMIN",
	DRA7XX_DEVICE_PRM_PRM_VP_MM_VSTEPMIN,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vc_smps_core_config = {
	"PRM_VC_SMPS_CORE_CONFIG",
	DRA7XX_DEVICE_PRM_PRM_VC_SMPS_CORE_CONFIG,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vc_smps_mm_config = {
	"PRM_VC_SMPS_MM_CONFIG",
	DRA7XX_DEVICE_PRM_PRM_VC_SMPS_MM_CONFIG,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vc_smps_mpu_config = {
	"PRM_VC_SMPS_MPU_CONFIG",
	DRA7XX_DEVICE_PRM_PRM_VC_SMPS_MPU_CONFIG,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vc_val_cmd_vdd_core_l = {
	"PRM_VC_VAL_CMD_VDD_CORE_L",
	DRA7XX_DEVICE_PRM_PRM_VC_VAL_CMD_VDD_CORE_L,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vc_val_cmd_vdd_mm_l = {
	"PRM_VC_VAL_CMD_VDD_MM_L",
	DRA7XX_DEVICE_PRM_PRM_VC_VAL_CMD_VDD_MM_L,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vc_val_cmd_vdd_mpu_l = {
	"PRM_VC_VAL_CMD_VDD_MPU_L",
	DRA7XX_DEVICE_PRM_PRM_VC_VAL_CMD_VDD_MPU_L,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vc_val_bypass = {
	"PRM_VC_VAL_BYPASS",
	DRA7XX_DEVICE_PRM_PRM_VC_VAL_BYPASS,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vc_core_errst = {
	"PRM_VC_CORE_ERRST",
	DRA7XX_DEVICE_PRM_PRM_VC_CORE_ERRST,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vc_mm_errst = {
	"PRM_VC_MM_ERRST",
	DRA7XX_DEVICE_PRM_PRM_VC_MM_ERRST,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vc_mpu_errst = {
	"PRM_VC_MPU_ERRST",
	DRA7XX_DEVICE_PRM_PRM_VC_MPU_ERRST,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vc_bypass_errst = {
	"PRM_VC_BYPASS_ERRST",
	DRA7XX_DEVICE_PRM_PRM_VC_BYPASS_ERRST,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vc_cfg_i2c_mode = {
	"PRM_VC_CFG_I2C_MODE",
	DRA7XX_DEVICE_PRM_PRM_VC_CFG_I2C_MODE,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_vc_cfg_i2c_clk = {
	"PRM_VC_CFG_I2C_CLK",
	DRA7XX_DEVICE_PRM_PRM_VC_CFG_I2C_CLK,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_sram_count = {
	"PRM_SRAM_COUNT",
	DRA7XX_DEVICE_PRM_PRM_SRAM_COUNT,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_sram_wkup_setup = {
	"PRM_SRAM_WKUP_SETUP",
	DRA7XX_DEVICE_PRM_PRM_SRAM_WKUP_SETUP,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_sldo_core_setup = {
	"PRM_SLDO_CORE_SETUP",
	DRA7XX_DEVICE_PRM_PRM_SLDO_CORE_SETUP,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_sldo_core_ctrl = {
	"PRM_SLDO_CORE_CTRL",
	DRA7XX_DEVICE_PRM_PRM_SLDO_CORE_CTRL,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_sldo_mpu_setup = {
	"PRM_SLDO_MPU_SETUP",
	DRA7XX_DEVICE_PRM_PRM_SLDO_MPU_SETUP,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_sldo_mpu_ctrl = {
	"PRM_SLDO_MPU_CTRL",
	DRA7XX_DEVICE_PRM_PRM_SLDO_MPU_CTRL,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_sldo_gpu_setup = {
	"PRM_SLDO_GPU_SETUP",
	DRA7XX_DEVICE_PRM_PRM_SLDO_GPU_SETUP,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_sldo_gpu_ctrl = {
	"PRM_SLDO_GPU_CTRL",
	DRA7XX_DEVICE_PRM_PRM_SLDO_GPU_CTRL,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_abbldo_mpu_setup = {
	"PRM_ABBLDO_MPU_SETUP",
	DRA7XX_DEVICE_PRM_PRM_ABBLDO_MPU_SETUP,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_abbldo_mpu_ctrl = {
	"PRM_ABBLDO_MPU_CTRL",
	DRA7XX_DEVICE_PRM_PRM_ABBLDO_MPU_CTRL,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_abbldo_gpu_setup = {
	"PRM_ABBLDO_GPU_SETUP",
	DRA7XX_DEVICE_PRM_PRM_ABBLDO_GPU_SETUP,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_abbldo_gpu_ctrl = {
	"PRM_ABBLDO_GPU_CTRL",
	DRA7XX_DEVICE_PRM_PRM_ABBLDO_GPU_CTRL,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_bandgap_setup = {
	"PRM_BANDGAP_SETUP",
	DRA7XX_DEVICE_PRM_PRM_BANDGAP_SETUP,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_device_off_ctrl = {
	"PRM_DEVICE_OFF_CTRL",
	DRA7XX_DEVICE_PRM_PRM_DEVICE_OFF_CTRL,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_phase1_cndp = {
	"PRM_PHASE1_CNDP",
	DRA7XX_DEVICE_PRM_PRM_PHASE1_CNDP,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_phase2a_cndp = {
	"PRM_PHASE2A_CNDP",
	DRA7XX_DEVICE_PRM_PRM_PHASE2A_CNDP,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_phase2b_cndp = {
	"PRM_PHASE2B_CNDP",
	DRA7XX_DEVICE_PRM_PRM_PHASE2B_CNDP,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_modem_if_ctrl = {
	"PRM_MODEM_IF_CTRL",
	DRA7XX_DEVICE_PRM_PRM_MODEM_IF_CTRL,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_voltst_mpu = {
	"PRM_VOLTST_MPU",
	DRA7XX_DEVICE_PRM_PRM_VOLTST_MPU,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_voltst_mm = {
	"PRM_VOLTST_MM",
	DRA7XX_DEVICE_PRM_PRM_VOLTST_MM,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_sldo_dspeve_setup = {
	"PRM_SLDO_DSPEVE_SETUP",
	DRA7XX_DEVICE_PRM_PRM_SLDO_DSPEVE_SETUP,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_sldo_iva_setup = {
	"PRM_SLDO_IVA_SETUP",
	DRA7XX_DEVICE_PRM_PRM_SLDO_IVA_SETUP,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_abbldo_dspeve_ctrl = {
	"PRM_ABBLDO_DSPEVE_CTRL",
	DRA7XX_DEVICE_PRM_PRM_ABBLDO_DSPEVE_CTRL,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_abbldo_iva_ctrl = {
	"PRM_ABBLDO_IVA_CTRL",
	DRA7XX_DEVICE_PRM_PRM_ABBLDO_IVA_CTRL,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_sldo_dspeve_ctrl = {
	"PRM_SLDO_DSPEVE_CTRL",
	DRA7XX_DEVICE_PRM_PRM_SLDO_DSPEVE_CTRL,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_sldo_iva_ctrl = {
	"PRM_SLDO_IVA_CTRL",
	DRA7XX_DEVICE_PRM_PRM_SLDO_IVA_CTRL,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_abbldo_dspeve_setup = {
	"PRM_ABBLDO_DSPEVE_SETUP",
	DRA7XX_DEVICE_PRM_PRM_ABBLDO_DSPEVE_SETUP,
	0xDEADBEEF,
	0};
reg dra7xx_device_prm_prm_abbldo_iva_setup = {
	"PRM_ABBLDO_IVA_SETUP",
	DRA7XX_DEVICE_PRM_PRM_ABBLDO_IVA_SETUP,
	0xDEADBEEF,
	0};
reg *dra7xx_device_prm_mod[DRA7XX_DEVICE_PRM_MOD_REGCOUNT + 1] = {
	&dra7xx_device_prm_prm_rstctrl,
	&dra7xx_device_prm_prm_rstst,
	&dra7xx_device_prm_prm_rsttime,
	&dra7xx_device_prm_prm_clkreqctrl,
	&dra7xx_device_prm_prm_voltctrl,
	&dra7xx_device_prm_prm_pwrreqctrl,
	&dra7xx_device_prm_prm_pscon_count,
	&dra7xx_device_prm_prm_io_count,
	&dra7xx_device_prm_prm_io_pmctrl,
	&dra7xx_device_prm_prm_voltsetup_warmreset,
	&dra7xx_device_prm_prm_voltsetup_core_off,
	&dra7xx_device_prm_prm_voltsetup_mpu_off,
	&dra7xx_device_prm_prm_voltsetup_mm_off,
	&dra7xx_device_prm_prm_voltsetup_core_ret_sleep,
	&dra7xx_device_prm_prm_voltsetup_mpu_ret_sleep,
	&dra7xx_device_prm_prm_voltsetup_mm_ret_sleep,
	&dra7xx_device_prm_prm_vp_core_config,
	&dra7xx_device_prm_prm_vp_core_status,
	&dra7xx_device_prm_prm_vp_core_vlimitto,
	&dra7xx_device_prm_prm_vp_core_voltage,
	&dra7xx_device_prm_prm_vp_core_vstepmax,
	&dra7xx_device_prm_prm_vp_core_vstepmin,
	&dra7xx_device_prm_prm_vp_mpu_config,
	&dra7xx_device_prm_prm_vp_mpu_status,
	&dra7xx_device_prm_prm_vp_mpu_vlimitto,
	&dra7xx_device_prm_prm_vp_mpu_voltage,
	&dra7xx_device_prm_prm_vp_mpu_vstepmax,
	&dra7xx_device_prm_prm_vp_mpu_vstepmin,
	&dra7xx_device_prm_prm_vp_mm_config,
	&dra7xx_device_prm_prm_vp_mm_status,
	&dra7xx_device_prm_prm_vp_mm_vlimitto,
	&dra7xx_device_prm_prm_vp_mm_voltage,
	&dra7xx_device_prm_prm_vp_mm_vstepmax,
	&dra7xx_device_prm_prm_vp_mm_vstepmin,
	&dra7xx_device_prm_prm_vc_smps_core_config,
	&dra7xx_device_prm_prm_vc_smps_mm_config,
	&dra7xx_device_prm_prm_vc_smps_mpu_config,
	&dra7xx_device_prm_prm_vc_val_cmd_vdd_core_l,
	&dra7xx_device_prm_prm_vc_val_cmd_vdd_mm_l,
	&dra7xx_device_prm_prm_vc_val_cmd_vdd_mpu_l,
	&dra7xx_device_prm_prm_vc_val_bypass,
	&dra7xx_device_prm_prm_vc_core_errst,
	&dra7xx_device_prm_prm_vc_mm_errst,
	&dra7xx_device_prm_prm_vc_mpu_errst,
	&dra7xx_device_prm_prm_vc_bypass_errst,
	&dra7xx_device_prm_prm_vc_cfg_i2c_mode,
	&dra7xx_device_prm_prm_vc_cfg_i2c_clk,
	&dra7xx_device_prm_prm_sram_count,
	&dra7xx_device_prm_prm_sram_wkup_setup,
	&dra7xx_device_prm_prm_sldo_core_setup,
	&dra7xx_device_prm_prm_sldo_core_ctrl,
	&dra7xx_device_prm_prm_sldo_mpu_setup,
	&dra7xx_device_prm_prm_sldo_mpu_ctrl,
	&dra7xx_device_prm_prm_sldo_gpu_setup,
	&dra7xx_device_prm_prm_sldo_gpu_ctrl,
	&dra7xx_device_prm_prm_abbldo_mpu_setup,
	&dra7xx_device_prm_prm_abbldo_mpu_ctrl,
	&dra7xx_device_prm_prm_abbldo_gpu_setup,
	&dra7xx_device_prm_prm_abbldo_gpu_ctrl,
	&dra7xx_device_prm_prm_bandgap_setup,
	&dra7xx_device_prm_prm_device_off_ctrl,
	&dra7xx_device_prm_prm_phase1_cndp,
	&dra7xx_device_prm_prm_phase2a_cndp,
	&dra7xx_device_prm_prm_phase2b_cndp,
	&dra7xx_device_prm_prm_modem_if_ctrl,
	&dra7xx_device_prm_prm_voltst_mpu,
	&dra7xx_device_prm_prm_voltst_mm,
	&dra7xx_device_prm_prm_sldo_dspeve_setup,
	&dra7xx_device_prm_prm_sldo_iva_setup,
	&dra7xx_device_prm_prm_abbldo_dspeve_ctrl,
	&dra7xx_device_prm_prm_abbldo_iva_ctrl,
	&dra7xx_device_prm_prm_sldo_dspeve_ctrl,
	&dra7xx_device_prm_prm_sldo_iva_ctrl,
	&dra7xx_device_prm_prm_abbldo_dspeve_setup,
	&dra7xx_device_prm_prm_abbldo_iva_setup,
	NULL};

reg dra7xx_gpu_prm_pm_gpu_pwrstctrl = {
	"PM_GPU_PWRSTCTRL",
	DRA7XX_GPU_PRM_PM_GPU_PWRSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_gpu_prm_pm_gpu_pwrstst = {
	"PM_GPU_PWRSTST",
	DRA7XX_GPU_PRM_PM_GPU_PWRSTST,
	0xDEADBEEF,
	0};
reg dra7xx_gpu_prm_rm_gpu_gpu_context = {
	"RM_GPU_GPU_CONTEXT",
	DRA7XX_GPU_PRM_RM_GPU_GPU_CONTEXT,
	0xDEADBEEF,
	0};
reg *dra7xx_gpu_prm_mod[DRA7XX_GPU_PRM_MOD_REGCOUNT + 1] = {
	&dra7xx_gpu_prm_pm_gpu_pwrstctrl,
	&dra7xx_gpu_prm_pm_gpu_pwrstst,
	&dra7xx_gpu_prm_rm_gpu_gpu_context,
	NULL};

reg dra7xx_coreaon_prm_pm_coreaon_smartreflex_mpu_wkdep = {
	"PM_COREAON_SMARTREFLEX_MPU_WKDEP",
	DRA7XX_COREAON_PRM_PM_COREAON_SMARTREFLEX_MPU_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_coreaon_prm_rm_coreaon_smartreflex_mpu_context = {
	"RM_COREAON_SMARTREFLEX_MPU_CONTEXT",
	DRA7XX_COREAON_PRM_RM_COREAON_SMARTREFLEX_MPU_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_coreaon_prm_pm_coreaon_smartreflex_core_wkdep = {
	"PM_COREAON_SMARTREFLEX_CORE_WKDEP",
	DRA7XX_COREAON_PRM_PM_COREAON_SMARTREFLEX_CORE_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_coreaon_prm_rm_coreaon_smartreflex_core_context = {
	"RM_COREAON_SMARTREFLEX_CORE_CONTEXT",
	DRA7XX_COREAON_PRM_RM_COREAON_SMARTREFLEX_CORE_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_coreaon_prm_pm_coreaon_smartreflex_gpu_wkdep = {
	"PM_COREAON_SMARTREFLEX_GPU_WKDEP",
	DRA7XX_COREAON_PRM_PM_COREAON_SMARTREFLEX_GPU_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_coreaon_prm_rm_coreaon_smartreflex_gpu_context = {
	"RM_COREAON_SMARTREFLEX_GPU_CONTEXT",
	DRA7XX_COREAON_PRM_RM_COREAON_SMARTREFLEX_GPU_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_coreaon_prm_pm_coreaon_smartreflex_dspeve_wkdep = {
	"PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP",
	DRA7XX_COREAON_PRM_PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_coreaon_prm_rm_coreaon_smartreflex_dspeve_context = {
	"RM_COREAON_SMARTREFLEX_DSPEVE_CONTEXT",
	DRA7XX_COREAON_PRM_RM_COREAON_SMARTREFLEX_DSPEVE_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_coreaon_prm_pm_coreaon_smartreflex_ivahd_wkdep = {
	"PM_COREAON_SMARTREFLEX_IVAHD_WKDEP",
	DRA7XX_COREAON_PRM_PM_COREAON_SMARTREFLEX_IVAHD_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_coreaon_prm_rm_coreaon_smartreflex_ivahd_context = {
	"RM_COREAON_SMARTREFLEX_IVAHD_CONTEXT",
	DRA7XX_COREAON_PRM_RM_COREAON_SMARTREFLEX_IVAHD_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_coreaon_prm_rm_coreaon_dummy_module1_context = {
	"RM_COREAON_DUMMY_MODULE1_CONTEXT",
	DRA7XX_COREAON_PRM_RM_COREAON_DUMMY_MODULE1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_coreaon_prm_rm_coreaon_dummy_module2_context = {
	"RM_COREAON_DUMMY_MODULE2_CONTEXT",
	DRA7XX_COREAON_PRM_RM_COREAON_DUMMY_MODULE2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_coreaon_prm_rm_coreaon_dummy_module3_context = {
	"RM_COREAON_DUMMY_MODULE3_CONTEXT",
	DRA7XX_COREAON_PRM_RM_COREAON_DUMMY_MODULE3_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_coreaon_prm_rm_coreaon_dummy_module4_context = {
	"RM_COREAON_DUMMY_MODULE4_CONTEXT",
	DRA7XX_COREAON_PRM_RM_COREAON_DUMMY_MODULE4_CONTEXT,
	0xDEADBEEF,
	0};
reg *dra7xx_coreaon_prm_mod[DRA7XX_COREAON_PRM_MOD_REGCOUNT + 1] = {
	&dra7xx_coreaon_prm_pm_coreaon_smartreflex_mpu_wkdep,
	&dra7xx_coreaon_prm_rm_coreaon_smartreflex_mpu_context,
	&dra7xx_coreaon_prm_pm_coreaon_smartreflex_core_wkdep,
	&dra7xx_coreaon_prm_rm_coreaon_smartreflex_core_context,
	&dra7xx_coreaon_prm_pm_coreaon_smartreflex_gpu_wkdep,
	&dra7xx_coreaon_prm_rm_coreaon_smartreflex_gpu_context,
	&dra7xx_coreaon_prm_pm_coreaon_smartreflex_dspeve_wkdep,
	&dra7xx_coreaon_prm_rm_coreaon_smartreflex_dspeve_context,
	&dra7xx_coreaon_prm_pm_coreaon_smartreflex_ivahd_wkdep,
	&dra7xx_coreaon_prm_rm_coreaon_smartreflex_ivahd_context,
	&dra7xx_coreaon_prm_rm_coreaon_dummy_module1_context,
	&dra7xx_coreaon_prm_rm_coreaon_dummy_module2_context,
	&dra7xx_coreaon_prm_rm_coreaon_dummy_module3_context,
	&dra7xx_coreaon_prm_rm_coreaon_dummy_module4_context,
	NULL};

reg dra7xx_custefuse_prm_pm_custefuse_pwrstctrl = {
	"PM_CUSTEFUSE_PWRSTCTRL",
	DRA7XX_CUSTEFUSE_PRM_PM_CUSTEFUSE_PWRSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_custefuse_prm_pm_custefuse_pwrstst = {
	"PM_CUSTEFUSE_PWRSTST",
	DRA7XX_CUSTEFUSE_PRM_PM_CUSTEFUSE_PWRSTST,
	0xDEADBEEF,
	0};
reg dra7xx_custefuse_prm_rm_custefuse_efuse_ctrl_cust_context = {
	"RM_CUSTEFUSE_EFUSE_CTRL_CUST_CONTEXT",
	DRA7XX_CUSTEFUSE_PRM_RM_CUSTEFUSE_EFUSE_CTRL_CUST_CONTEXT,
	0xDEADBEEF,
	0};
reg *dra7xx_custefuse_prm_mod[DRA7XX_CUSTEFUSE_PRM_MOD_REGCOUNT + 1] = {
	&dra7xx_custefuse_prm_pm_custefuse_pwrstctrl,
	&dra7xx_custefuse_prm_pm_custefuse_pwrstst,
	&dra7xx_custefuse_prm_rm_custefuse_efuse_ctrl_cust_context,
	NULL};

reg dra7xx_ckgen_prm_cm_clksel_sysclk1 = {
	"CM_CLKSEL_SYSCLK1",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_SYSCLK1,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_wkupaon = {
	"CM_CLKSEL_WKUPAON",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_WKUPAON,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_abe_pll_ref = {
	"CM_CLKSEL_ABE_PLL_REF",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_ABE_PLL_REF,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_sys = {
	"CM_CLKSEL_SYS",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_SYS,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_abe_pll_bypas = {
	"CM_CLKSEL_ABE_PLL_BYPAS",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_ABE_PLL_BYPAS,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_abe_pll_sys = {
	"CM_CLKSEL_ABE_PLL_SYS",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_ABE_PLL_SYS,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_abe_24m = {
	"CM_CLKSEL_ABE_24M",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_ABE_24M,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_abe_sys = {
	"CM_CLKSEL_ABE_SYS",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_ABE_SYS,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_hdmi_mcasp_aux = {
	"CM_CLKSEL_HDMI_MCASP_AUX",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_HDMI_MCASP_AUX,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_hdmi_timer = {
	"CM_CLKSEL_HDMI_TIMER",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_HDMI_TIMER,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_mcasp_sys = {
	"CM_CLKSEL_MCASP_SYS",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_MCASP_SYS,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_mlbp_mcasp = {
	"CM_CLKSEL_MLBP_MCASP",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_MLBP_MCASP,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_mlb_mcasp = {
	"CM_CLKSEL_MLB_MCASP",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_MLB_MCASP,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_per_abe_x1_gfclk_mcasp_aux = {
	"CM_CLKSEL_PER_ABE_X1_GFCLK_MCASP_AUX",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_PER_ABE_X1_GFCLK_MCASP_AUX,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_sys_clk1_32k = {
	"CM_CLKSEL_SYS_CLK1_32K",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_SYS_CLK1_32K,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_timer_sys = {
	"CM_CLKSEL_TIMER_SYS",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_TIMER_SYS,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_video1_mcasp_aux = {
	"CM_CLKSEL_VIDEO1_MCASP_AUX",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_VIDEO1_MCASP_AUX,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_video1_timer = {
	"CM_CLKSEL_VIDEO1_TIMER",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_VIDEO1_TIMER,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_video2_mcasp_aux = {
	"CM_CLKSEL_VIDEO2_MCASP_AUX",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_VIDEO2_MCASP_AUX,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_video2_timer = {
	"CM_CLKSEL_VIDEO2_TIMER",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_VIDEO2_TIMER,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_clkoutmux0 = {
	"CM_CLKSEL_CLKOUTMUX0",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_CLKOUTMUX0,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_clkoutmux1 = {
	"CM_CLKSEL_CLKOUTMUX1",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_CLKOUTMUX1,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_clkoutmux2 = {
	"CM_CLKSEL_CLKOUTMUX2",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_CLKOUTMUX2,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_hdmi_pll_sys = {
	"CM_CLKSEL_HDMI_PLL_SYS",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_HDMI_PLL_SYS,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_video1_pll_sys = {
	"CM_CLKSEL_VIDEO1_PLL_SYS",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_VIDEO1_PLL_SYS,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_video2_pll_sys = {
	"CM_CLKSEL_VIDEO2_PLL_SYS",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_VIDEO2_PLL_SYS,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_abe_clk_div = {
	"CM_CLKSEL_ABE_CLK_DIV",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_ABE_CLK_DIV,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_abe_giclk_div = {
	"CM_CLKSEL_ABE_GICLK_DIV",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_ABE_GICLK_DIV,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_aess_fclk_div = {
	"CM_CLKSEL_AESS_FCLK_DIV",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_AESS_FCLK_DIV,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_eve_clk = {
	"CM_CLKSEL_EVE_CLK",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_EVE_CLK,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_usb_otg_clk_clkoutmux = {
	"CM_CLKSEL_USB_OTG_CLK_CLKOUTMUX",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_USB_OTG_CLK_CLKOUTMUX,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_core_dpll_out_clk_clkoutmux = {
	"CM_CLKSEL_CORE_DPLL_OUT_CLK_CLKOUTMUX",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_CORE_DPLL_OUT_CLK_CLKOUTMUX,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_dsp_gfclk_clkoutmux = {
	"CM_CLKSEL_DSP_GFCLK_CLKOUTMUX",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_DSP_GFCLK_CLKOUTMUX,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_emif_phy_gclk_clkoutmux = {
	"CM_CLKSEL_EMIF_PHY_GCLK_CLKOUTMUX",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_EMIF_PHY_GCLK_CLKOUTMUX,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_emu_clk_clkoutmux = {
	"CM_CLKSEL_EMU_CLK_CLKOUTMUX",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_EMU_CLK_CLKOUTMUX,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_func_96m_aon_clk_clkoutmux = {
	"CM_CLKSEL_FUNC_96M_AON_CLK_CLKOUTMUX",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_FUNC_96M_AON_CLK_CLKOUTMUX,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_gmac_250m_clk_clkoutmux = {
	"CM_CLKSEL_GMAC_250M_CLK_CLKOUTMUX",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_GMAC_250M_CLK_CLKOUTMUX,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_gpu_gclk_clkoutmux = {
	"CM_CLKSEL_GPU_GCLK_CLKOUTMUX",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_GPU_GCLK_CLKOUTMUX,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_hdmi_clk_clkoutmux = {
	"CM_CLKSEL_HDMI_CLK_CLKOUTMUX",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_HDMI_CLK_CLKOUTMUX,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_iva_gclk_clkoutmux = {
	"CM_CLKSEL_IVA_GCLK_CLKOUTMUX",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_IVA_GCLK_CLKOUTMUX,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_l3init_480m_gfclk_clkoutmux = {
	"CM_CLKSEL_L3INIT_480M_GFCLK_CLKOUTMUX",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_L3INIT_480M_GFCLK_CLKOUTMUX,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_mpu_gclk_clkoutmux = {
	"CM_CLKSEL_MPU_GCLK_CLKOUTMUX",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_MPU_GCLK_CLKOUTMUX,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_pcie1_clk_clkoutmux = {
	"CM_CLKSEL_PCIE1_CLK_CLKOUTMUX",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_PCIE1_CLK_CLKOUTMUX,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_pcie2_clk_clkoutmux = {
	"CM_CLKSEL_PCIE2_CLK_CLKOUTMUX",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_PCIE2_CLK_CLKOUTMUX,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_per_abe_x1_clk_clkoutmux = {
	"CM_CLKSEL_PER_ABE_X1_CLK_CLKOUTMUX",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_PER_ABE_X1_CLK_CLKOUTMUX,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_sata_clk_clkoutmux = {
	"CM_CLKSEL_SATA_CLK_CLKOUTMUX",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_SATA_CLK_CLKOUTMUX,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_secure_32k_clk_clkoutmux = {
	"CM_CLKSEL_SECURE_32K_CLK_CLKOUTMUX",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_SECURE_32K_CLK_CLKOUTMUX,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_sys_clk1_clkoutmux = {
	"CM_CLKSEL_SYS_CLK1_CLKOUTMUX",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_SYS_CLK1_CLKOUTMUX,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_sys_clk2_clkoutmux = {
	"CM_CLKSEL_SYS_CLK2_CLKOUTMUX",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_SYS_CLK2_CLKOUTMUX,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_video1_clk_clkoutmux = {
	"CM_CLKSEL_VIDEO1_CLK_CLKOUTMUX",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_VIDEO1_CLK_CLKOUTMUX,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_video2_clk_clkoutmux = {
	"CM_CLKSEL_VIDEO2_CLK_CLKOUTMUX",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_VIDEO2_CLK_CLKOUTMUX,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_abe_lp_clk = {
	"CM_CLKSEL_ABE_LP_CLK",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_ABE_LP_CLK,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_adc_gfclk = {
	"CM_CLKSEL_ADC_GFCLK",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_ADC_GFCLK,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_prm_cm_clksel_eve_gfclk_clkoutmux = {
	"CM_CLKSEL_EVE_GFCLK_CLKOUTMUX",
	DRA7XX_CKGEN_PRM_CM_CLKSEL_EVE_GFCLK_CLKOUTMUX,
	0xDEADBEEF,
	0};
reg *dra7xx_ckgen_prm_mod[DRA7XX_CKGEN_PRM_MOD_REGCOUNT + 1] = {
	&dra7xx_ckgen_prm_cm_clksel_sysclk1,
	&dra7xx_ckgen_prm_cm_clksel_wkupaon,
	&dra7xx_ckgen_prm_cm_clksel_abe_pll_ref,
	&dra7xx_ckgen_prm_cm_clksel_sys,
	&dra7xx_ckgen_prm_cm_clksel_abe_pll_bypas,
	&dra7xx_ckgen_prm_cm_clksel_abe_pll_sys,
	&dra7xx_ckgen_prm_cm_clksel_abe_24m,
	&dra7xx_ckgen_prm_cm_clksel_abe_sys,
	&dra7xx_ckgen_prm_cm_clksel_hdmi_mcasp_aux,
	&dra7xx_ckgen_prm_cm_clksel_hdmi_timer,
	&dra7xx_ckgen_prm_cm_clksel_mcasp_sys,
	&dra7xx_ckgen_prm_cm_clksel_mlbp_mcasp,
	&dra7xx_ckgen_prm_cm_clksel_mlb_mcasp,
	&dra7xx_ckgen_prm_cm_clksel_per_abe_x1_gfclk_mcasp_aux,
	&dra7xx_ckgen_prm_cm_clksel_sys_clk1_32k,
	&dra7xx_ckgen_prm_cm_clksel_timer_sys,
	&dra7xx_ckgen_prm_cm_clksel_video1_mcasp_aux,
	&dra7xx_ckgen_prm_cm_clksel_video1_timer,
	&dra7xx_ckgen_prm_cm_clksel_video2_mcasp_aux,
	&dra7xx_ckgen_prm_cm_clksel_video2_timer,
	&dra7xx_ckgen_prm_cm_clksel_clkoutmux0,
	&dra7xx_ckgen_prm_cm_clksel_clkoutmux1,
	&dra7xx_ckgen_prm_cm_clksel_clkoutmux2,
	&dra7xx_ckgen_prm_cm_clksel_hdmi_pll_sys,
	&dra7xx_ckgen_prm_cm_clksel_video1_pll_sys,
	&dra7xx_ckgen_prm_cm_clksel_video2_pll_sys,
	&dra7xx_ckgen_prm_cm_clksel_abe_clk_div,
	&dra7xx_ckgen_prm_cm_clksel_abe_giclk_div,
	&dra7xx_ckgen_prm_cm_clksel_aess_fclk_div,
	&dra7xx_ckgen_prm_cm_clksel_eve_clk,
	&dra7xx_ckgen_prm_cm_clksel_usb_otg_clk_clkoutmux,
	&dra7xx_ckgen_prm_cm_clksel_core_dpll_out_clk_clkoutmux,
	&dra7xx_ckgen_prm_cm_clksel_dsp_gfclk_clkoutmux,
	&dra7xx_ckgen_prm_cm_clksel_emif_phy_gclk_clkoutmux,
	&dra7xx_ckgen_prm_cm_clksel_emu_clk_clkoutmux,
	&dra7xx_ckgen_prm_cm_clksel_func_96m_aon_clk_clkoutmux,
	&dra7xx_ckgen_prm_cm_clksel_gmac_250m_clk_clkoutmux,
	&dra7xx_ckgen_prm_cm_clksel_gpu_gclk_clkoutmux,
	&dra7xx_ckgen_prm_cm_clksel_hdmi_clk_clkoutmux,
	&dra7xx_ckgen_prm_cm_clksel_iva_gclk_clkoutmux,
	&dra7xx_ckgen_prm_cm_clksel_l3init_480m_gfclk_clkoutmux,
	&dra7xx_ckgen_prm_cm_clksel_mpu_gclk_clkoutmux,
	&dra7xx_ckgen_prm_cm_clksel_pcie1_clk_clkoutmux,
	&dra7xx_ckgen_prm_cm_clksel_pcie2_clk_clkoutmux,
	&dra7xx_ckgen_prm_cm_clksel_per_abe_x1_clk_clkoutmux,
	&dra7xx_ckgen_prm_cm_clksel_sata_clk_clkoutmux,
	&dra7xx_ckgen_prm_cm_clksel_secure_32k_clk_clkoutmux,
	&dra7xx_ckgen_prm_cm_clksel_sys_clk1_clkoutmux,
	&dra7xx_ckgen_prm_cm_clksel_sys_clk2_clkoutmux,
	&dra7xx_ckgen_prm_cm_clksel_video1_clk_clkoutmux,
	&dra7xx_ckgen_prm_cm_clksel_video2_clk_clkoutmux,
	&dra7xx_ckgen_prm_cm_clksel_abe_lp_clk,
	&dra7xx_ckgen_prm_cm_clksel_adc_gfclk,
	&dra7xx_ckgen_prm_cm_clksel_eve_gfclk_clkoutmux,
	NULL};

reg dra7xx_instr_prm_pmi_identication = {
	"PMI_IDENTICATION",
	DRA7XX_INSTR_PRM_PMI_IDENTICATION,
	0xDEADBEEF,
	0};
reg dra7xx_instr_prm_pmi_sys_config = {
	"PMI_SYS_CONFIG",
	DRA7XX_INSTR_PRM_PMI_SYS_CONFIG,
	0xDEADBEEF,
	0};
reg dra7xx_instr_prm_pmi_status = {
	"PMI_STATUS",
	DRA7XX_INSTR_PRM_PMI_STATUS,
	0xDEADBEEF,
	0};
reg dra7xx_instr_prm_pmi_configuration = {
	"PMI_CONFIGURATION",
	DRA7XX_INSTR_PRM_PMI_CONFIGURATION,
	0xDEADBEEF,
	0};
reg dra7xx_instr_prm_pmi_class_filtering = {
	"PMI_CLASS_FILTERING",
	DRA7XX_INSTR_PRM_PMI_CLASS_FILTERING,
	0xDEADBEEF,
	0};
reg dra7xx_instr_prm_pmi_triggering = {
	"PMI_TRIGGERING",
	DRA7XX_INSTR_PRM_PMI_TRIGGERING,
	0xDEADBEEF,
	0};
reg dra7xx_instr_prm_pmi_sampling = {
	"PMI_SAMPLING",
	DRA7XX_INSTR_PRM_PMI_SAMPLING,
	0xDEADBEEF,
	0};
reg *dra7xx_instr_prm_mod[DRA7XX_INSTR_PRM_MOD_REGCOUNT + 1] = {
	&dra7xx_instr_prm_pmi_identication,
	&dra7xx_instr_prm_pmi_sys_config,
	&dra7xx_instr_prm_pmi_status,
	&dra7xx_instr_prm_pmi_configuration,
	&dra7xx_instr_prm_pmi_class_filtering,
	&dra7xx_instr_prm_pmi_triggering,
	&dra7xx_instr_prm_pmi_sampling,
	NULL};

reg dra7xx_iva_prm_pm_iva_pwrstctrl = {
	"PM_IVA_PWRSTCTRL",
	DRA7XX_IVA_PRM_PM_IVA_PWRSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_iva_prm_pm_iva_pwrstst = {
	"PM_IVA_PWRSTST",
	DRA7XX_IVA_PRM_PM_IVA_PWRSTST,
	0xDEADBEEF,
	0};
reg dra7xx_iva_prm_rm_iva_rstctrl = {
	"RM_IVA_RSTCTRL",
	DRA7XX_IVA_PRM_RM_IVA_RSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_iva_prm_rm_iva_rstst = {
	"RM_IVA_RSTST",
	DRA7XX_IVA_PRM_RM_IVA_RSTST,
	0xDEADBEEF,
	0};
reg dra7xx_iva_prm_rm_iva_iva_context = {
	"RM_IVA_IVA_CONTEXT",
	DRA7XX_IVA_PRM_RM_IVA_IVA_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_iva_prm_rm_iva_sl2_context = {
	"RM_IVA_SL2_CONTEXT",
	DRA7XX_IVA_PRM_RM_IVA_SL2_CONTEXT,
	0xDEADBEEF,
	0};
reg *dra7xx_iva_prm_mod[DRA7XX_IVA_PRM_MOD_REGCOUNT + 1] = {
	&dra7xx_iva_prm_pm_iva_pwrstctrl,
	&dra7xx_iva_prm_pm_iva_pwrstst,
	&dra7xx_iva_prm_rm_iva_rstctrl,
	&dra7xx_iva_prm_rm_iva_rstst,
	&dra7xx_iva_prm_rm_iva_iva_context,
	&dra7xx_iva_prm_rm_iva_sl2_context,
	NULL};

reg dra7xx_core_prm_pm_core_pwrstctrl = {
	"PM_CORE_PWRSTCTRL",
	DRA7XX_CORE_PRM_PM_CORE_PWRSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_pm_core_pwrstst = {
	"PM_CORE_PWRSTST",
	DRA7XX_CORE_PRM_PM_CORE_PWRSTST,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l3main1_l3_main_1_context = {
	"RM_L3MAIN1_L3_MAIN_1_CONTEXT",
	DRA7XX_CORE_PRM_RM_L3MAIN1_L3_MAIN_1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l3main1_gpmc_context = {
	"RM_L3MAIN1_GPMC_CONTEXT",
	DRA7XX_CORE_PRM_RM_L3MAIN1_GPMC_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l3main1_mmu_edma_context = {
	"RM_L3MAIN1_MMU_EDMA_CONTEXT",
	DRA7XX_CORE_PRM_RM_L3MAIN1_MMU_EDMA_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l3main1_mmu_pciess_context = {
	"RM_L3MAIN1_MMU_PCIESS_CONTEXT",
	DRA7XX_CORE_PRM_RM_L3MAIN1_MMU_PCIESS_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_pm_l3main1_ocmc_ram1_wkdep = {
	"PM_L3MAIN1_OCMC_RAM1_WKDEP",
	DRA7XX_CORE_PRM_PM_L3MAIN1_OCMC_RAM1_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l3main1_ocmc_ram1_context = {
	"RM_L3MAIN1_OCMC_RAM1_CONTEXT",
	DRA7XX_CORE_PRM_RM_L3MAIN1_OCMC_RAM1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_pm_l3main1_ocmc_ram2_wkdep = {
	"PM_L3MAIN1_OCMC_RAM2_WKDEP",
	DRA7XX_CORE_PRM_PM_L3MAIN1_OCMC_RAM2_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l3main1_ocmc_ram2_context = {
	"RM_L3MAIN1_OCMC_RAM2_CONTEXT",
	DRA7XX_CORE_PRM_RM_L3MAIN1_OCMC_RAM2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_pm_l3main1_ocmc_ram3_wkdep = {
	"PM_L3MAIN1_OCMC_RAM3_WKDEP",
	DRA7XX_CORE_PRM_PM_L3MAIN1_OCMC_RAM3_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l3main1_ocmc_ram3_context = {
	"RM_L3MAIN1_OCMC_RAM3_CONTEXT",
	DRA7XX_CORE_PRM_RM_L3MAIN1_OCMC_RAM3_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l3main1_ocmc_rom_context = {
	"RM_L3MAIN1_OCMC_ROM_CONTEXT",
	DRA7XX_CORE_PRM_RM_L3MAIN1_OCMC_ROM_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_pm_l3main1_tpcc_wkdep = {
	"PM_L3MAIN1_TPCC_WKDEP",
	DRA7XX_CORE_PRM_PM_L3MAIN1_TPCC_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l3main1_tpcc_context = {
	"RM_L3MAIN1_TPCC_CONTEXT",
	DRA7XX_CORE_PRM_RM_L3MAIN1_TPCC_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_pm_l3main1_tptc1_wkdep = {
	"PM_L3MAIN1_TPTC1_WKDEP",
	DRA7XX_CORE_PRM_PM_L3MAIN1_TPTC1_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l3main1_tptc1_context = {
	"RM_L3MAIN1_TPTC1_CONTEXT",
	DRA7XX_CORE_PRM_RM_L3MAIN1_TPTC1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_pm_l3main1_tptc2_wkdep = {
	"PM_L3MAIN1_TPTC2_WKDEP",
	DRA7XX_CORE_PRM_PM_L3MAIN1_TPTC2_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l3main1_tptc2_context = {
	"RM_L3MAIN1_TPTC2_CONTEXT",
	DRA7XX_CORE_PRM_RM_L3MAIN1_TPTC2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l3main1_vcp1_context = {
	"RM_L3MAIN1_VCP1_CONTEXT",
	DRA7XX_CORE_PRM_RM_L3MAIN1_VCP1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l3main1_vcp2_context = {
	"RM_L3MAIN1_VCP2_CONTEXT",
	DRA7XX_CORE_PRM_RM_L3MAIN1_VCP2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l3main1_spare_cme_context = {
	"RM_L3MAIN1_SPARE_CME_CONTEXT",
	DRA7XX_CORE_PRM_RM_L3MAIN1_SPARE_CME_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l3main1_spare_hdmi_context = {
	"RM_L3MAIN1_SPARE_HDMI_CONTEXT",
	DRA7XX_CORE_PRM_RM_L3MAIN1_SPARE_HDMI_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l3main1_spare_icm_context = {
	"RM_L3MAIN1_SPARE_ICM_CONTEXT",
	DRA7XX_CORE_PRM_RM_L3MAIN1_SPARE_ICM_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l3main1_spare_iva2_context = {
	"RM_L3MAIN1_SPARE_IVA2_CONTEXT",
	DRA7XX_CORE_PRM_RM_L3MAIN1_SPARE_IVA2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l3main1_spare_sata2_context = {
	"RM_L3MAIN1_SPARE_SATA2_CONTEXT",
	DRA7XX_CORE_PRM_RM_L3MAIN1_SPARE_SATA2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l3main1_spare_unknown4_context = {
	"RM_L3MAIN1_SPARE_UNKNOWN4_CONTEXT",
	DRA7XX_CORE_PRM_RM_L3MAIN1_SPARE_UNKNOWN4_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l3main1_spare_unknown5_context = {
	"RM_L3MAIN1_SPARE_UNKNOWN5_CONTEXT",
	DRA7XX_CORE_PRM_RM_L3MAIN1_SPARE_UNKNOWN5_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l3main1_spare_unknown6_context = {
	"RM_L3MAIN1_SPARE_UNKNOWN6_CONTEXT",
	DRA7XX_CORE_PRM_RM_L3MAIN1_SPARE_UNKNOWN6_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l3main1_spare_videopll1_context = {
	"RM_L3MAIN1_SPARE_VIDEOPLL1_CONTEXT",
	DRA7XX_CORE_PRM_RM_L3MAIN1_SPARE_VIDEOPLL1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l3main1_spare_videopll2_context = {
	"RM_L3MAIN1_SPARE_VIDEOPLL2_CONTEXT",
	DRA7XX_CORE_PRM_RM_L3MAIN1_SPARE_VIDEOPLL2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l3main1_spare_videopll3_context = {
	"RM_L3MAIN1_SPARE_VIDEOPLL3_CONTEXT",
	DRA7XX_CORE_PRM_RM_L3MAIN1_SPARE_VIDEOPLL3_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_ipu2_rstctrl = {
	"RM_IPU2_RSTCTRL",
	DRA7XX_CORE_PRM_RM_IPU2_RSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_ipu2_rstst = {
	"RM_IPU2_RSTST",
	DRA7XX_CORE_PRM_RM_IPU2_RSTST,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_ipu2_ipu2_context = {
	"RM_IPU2_IPU2_CONTEXT",
	DRA7XX_CORE_PRM_RM_IPU2_IPU2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_dma_dma_system_context = {
	"RM_DMA_DMA_SYSTEM_CONTEXT",
	DRA7XX_CORE_PRM_RM_DMA_DMA_SYSTEM_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_emif_dmm_context = {
	"RM_EMIF_DMM_CONTEXT",
	DRA7XX_CORE_PRM_RM_EMIF_DMM_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_emif_emif_ocp_fw_context = {
	"RM_EMIF_EMIF_OCP_FW_CONTEXT",
	DRA7XX_CORE_PRM_RM_EMIF_EMIF_OCP_FW_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_emif_emif1_context = {
	"RM_EMIF_EMIF1_CONTEXT",
	DRA7XX_CORE_PRM_RM_EMIF_EMIF1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_emif_emif2_context = {
	"RM_EMIF_EMIF2_CONTEXT",
	DRA7XX_CORE_PRM_RM_EMIF_EMIF2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_emif_emif_dll_context = {
	"RM_EMIF_EMIF_DLL_CONTEXT",
	DRA7XX_CORE_PRM_RM_EMIF_EMIF_DLL_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_atl_atl_context = {
	"RM_ATL_ATL_CONTEXT",
	DRA7XX_CORE_PRM_RM_ATL_ATL_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l4cfg_l4_cfg_context = {
	"RM_L4CFG_L4_CFG_CONTEXT",
	DRA7XX_CORE_PRM_RM_L4CFG_L4_CFG_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l4cfg_spinlock_context = {
	"RM_L4CFG_SPINLOCK_CONTEXT",
	DRA7XX_CORE_PRM_RM_L4CFG_SPINLOCK_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l4cfg_mailbox1_context = {
	"RM_L4CFG_MAILBOX1_CONTEXT",
	DRA7XX_CORE_PRM_RM_L4CFG_MAILBOX1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l4cfg_sar_rom_context = {
	"RM_L4CFG_SAR_ROM_CONTEXT",
	DRA7XX_CORE_PRM_RM_L4CFG_SAR_ROM_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l4cfg_ocp2scp2_context = {
	"RM_L4CFG_OCP2SCP2_CONTEXT",
	DRA7XX_CORE_PRM_RM_L4CFG_OCP2SCP2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l4cfg_mailbox2_context = {
	"RM_L4CFG_MAILBOX2_CONTEXT",
	DRA7XX_CORE_PRM_RM_L4CFG_MAILBOX2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l4cfg_mailbox3_context = {
	"RM_L4CFG_MAILBOX3_CONTEXT",
	DRA7XX_CORE_PRM_RM_L4CFG_MAILBOX3_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l4cfg_mailbox4_context = {
	"RM_L4CFG_MAILBOX4_CONTEXT",
	DRA7XX_CORE_PRM_RM_L4CFG_MAILBOX4_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l4cfg_mailbox5_context = {
	"RM_L4CFG_MAILBOX5_CONTEXT",
	DRA7XX_CORE_PRM_RM_L4CFG_MAILBOX5_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l4cfg_mailbox6_context = {
	"RM_L4CFG_MAILBOX6_CONTEXT",
	DRA7XX_CORE_PRM_RM_L4CFG_MAILBOX6_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l4cfg_mailbox7_context = {
	"RM_L4CFG_MAILBOX7_CONTEXT",
	DRA7XX_CORE_PRM_RM_L4CFG_MAILBOX7_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l4cfg_mailbox8_context = {
	"RM_L4CFG_MAILBOX8_CONTEXT",
	DRA7XX_CORE_PRM_RM_L4CFG_MAILBOX8_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l4cfg_mailbox9_context = {
	"RM_L4CFG_MAILBOX9_CONTEXT",
	DRA7XX_CORE_PRM_RM_L4CFG_MAILBOX9_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l4cfg_mailbox10_context = {
	"RM_L4CFG_MAILBOX10_CONTEXT",
	DRA7XX_CORE_PRM_RM_L4CFG_MAILBOX10_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l4cfg_mailbox11_context = {
	"RM_L4CFG_MAILBOX11_CONTEXT",
	DRA7XX_CORE_PRM_RM_L4CFG_MAILBOX11_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l4cfg_mailbox12_context = {
	"RM_L4CFG_MAILBOX12_CONTEXT",
	DRA7XX_CORE_PRM_RM_L4CFG_MAILBOX12_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l4cfg_mailbox13_context = {
	"RM_L4CFG_MAILBOX13_CONTEXT",
	DRA7XX_CORE_PRM_RM_L4CFG_MAILBOX13_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l4cfg_spare_smartreflex_rtc_context = {
	"RM_L4CFG_SPARE_SMARTREFLEX_RTC_CONTEXT",
	DRA7XX_CORE_PRM_RM_L4CFG_SPARE_SMARTREFLEX_RTC_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l4cfg_spare_smartreflex_sdram_context = {
	"RM_L4CFG_SPARE_SMARTREFLEX_SDRAM_CONTEXT",
	DRA7XX_CORE_PRM_RM_L4CFG_SPARE_SMARTREFLEX_SDRAM_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l4cfg_spare_smartreflex_wkup_context = {
	"RM_L4CFG_SPARE_SMARTREFLEX_WKUP_CONTEXT",
	DRA7XX_CORE_PRM_RM_L4CFG_SPARE_SMARTREFLEX_WKUP_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l4cfg_io_delay_block_context = {
	"RM_L4CFG_IO_DELAY_BLOCK_CONTEXT",
	DRA7XX_CORE_PRM_RM_L4CFG_IO_DELAY_BLOCK_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l3instr_l3_main_2_context = {
	"RM_L3INSTR_L3_MAIN_2_CONTEXT",
	DRA7XX_CORE_PRM_RM_L3INSTR_L3_MAIN_2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l3instr_l3_instr_context = {
	"RM_L3INSTR_L3_INSTR_CONTEXT",
	DRA7XX_CORE_PRM_RM_L3INSTR_L3_INSTR_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_core_prm_rm_l3instr_ocp_wp_noc_context = {
	"RM_L3INSTR_OCP_WP_NOC_CONTEXT",
	DRA7XX_CORE_PRM_RM_L3INSTR_OCP_WP_NOC_CONTEXT,
	0xDEADBEEF,
	0};
reg *dra7xx_core_prm_mod[DRA7XX_CORE_PRM_MOD_REGCOUNT + 1] = {
	&dra7xx_core_prm_pm_core_pwrstctrl,
	&dra7xx_core_prm_pm_core_pwrstst,
	&dra7xx_core_prm_rm_l3main1_l3_main_1_context,
	&dra7xx_core_prm_rm_l3main1_gpmc_context,
	&dra7xx_core_prm_rm_l3main1_mmu_edma_context,
	&dra7xx_core_prm_rm_l3main1_mmu_pciess_context,
	&dra7xx_core_prm_pm_l3main1_ocmc_ram1_wkdep,
	&dra7xx_core_prm_rm_l3main1_ocmc_ram1_context,
	&dra7xx_core_prm_pm_l3main1_ocmc_ram2_wkdep,
	&dra7xx_core_prm_rm_l3main1_ocmc_ram2_context,
	&dra7xx_core_prm_pm_l3main1_ocmc_ram3_wkdep,
	&dra7xx_core_prm_rm_l3main1_ocmc_ram3_context,
	&dra7xx_core_prm_rm_l3main1_ocmc_rom_context,
	&dra7xx_core_prm_pm_l3main1_tpcc_wkdep,
	&dra7xx_core_prm_rm_l3main1_tpcc_context,
	&dra7xx_core_prm_pm_l3main1_tptc1_wkdep,
	&dra7xx_core_prm_rm_l3main1_tptc1_context,
	&dra7xx_core_prm_pm_l3main1_tptc2_wkdep,
	&dra7xx_core_prm_rm_l3main1_tptc2_context,
	&dra7xx_core_prm_rm_l3main1_vcp1_context,
	&dra7xx_core_prm_rm_l3main1_vcp2_context,
	&dra7xx_core_prm_rm_l3main1_spare_cme_context,
	&dra7xx_core_prm_rm_l3main1_spare_hdmi_context,
	&dra7xx_core_prm_rm_l3main1_spare_icm_context,
	&dra7xx_core_prm_rm_l3main1_spare_iva2_context,
	&dra7xx_core_prm_rm_l3main1_spare_sata2_context,
	&dra7xx_core_prm_rm_l3main1_spare_unknown4_context,
	&dra7xx_core_prm_rm_l3main1_spare_unknown5_context,
	&dra7xx_core_prm_rm_l3main1_spare_unknown6_context,
	&dra7xx_core_prm_rm_l3main1_spare_videopll1_context,
	&dra7xx_core_prm_rm_l3main1_spare_videopll2_context,
	&dra7xx_core_prm_rm_l3main1_spare_videopll3_context,
	&dra7xx_core_prm_rm_ipu2_rstctrl,
	&dra7xx_core_prm_rm_ipu2_rstst,
	&dra7xx_core_prm_rm_ipu2_ipu2_context,
	&dra7xx_core_prm_rm_dma_dma_system_context,
	&dra7xx_core_prm_rm_emif_dmm_context,
	&dra7xx_core_prm_rm_emif_emif_ocp_fw_context,
	&dra7xx_core_prm_rm_emif_emif1_context,
	&dra7xx_core_prm_rm_emif_emif2_context,
	&dra7xx_core_prm_rm_emif_emif_dll_context,
	&dra7xx_core_prm_rm_atl_atl_context,
	&dra7xx_core_prm_rm_l4cfg_l4_cfg_context,
	&dra7xx_core_prm_rm_l4cfg_spinlock_context,
	&dra7xx_core_prm_rm_l4cfg_mailbox1_context,
	&dra7xx_core_prm_rm_l4cfg_sar_rom_context,
	&dra7xx_core_prm_rm_l4cfg_ocp2scp2_context,
	&dra7xx_core_prm_rm_l4cfg_mailbox2_context,
	&dra7xx_core_prm_rm_l4cfg_mailbox3_context,
	&dra7xx_core_prm_rm_l4cfg_mailbox4_context,
	&dra7xx_core_prm_rm_l4cfg_mailbox5_context,
	&dra7xx_core_prm_rm_l4cfg_mailbox6_context,
	&dra7xx_core_prm_rm_l4cfg_mailbox7_context,
	&dra7xx_core_prm_rm_l4cfg_mailbox8_context,
	&dra7xx_core_prm_rm_l4cfg_mailbox9_context,
	&dra7xx_core_prm_rm_l4cfg_mailbox10_context,
	&dra7xx_core_prm_rm_l4cfg_mailbox11_context,
	&dra7xx_core_prm_rm_l4cfg_mailbox12_context,
	&dra7xx_core_prm_rm_l4cfg_mailbox13_context,
	&dra7xx_core_prm_rm_l4cfg_spare_smartreflex_rtc_context,
	&dra7xx_core_prm_rm_l4cfg_spare_smartreflex_sdram_context,
	&dra7xx_core_prm_rm_l4cfg_spare_smartreflex_wkup_context,
	&dra7xx_core_prm_rm_l4cfg_io_delay_block_context,
	&dra7xx_core_prm_rm_l3instr_l3_main_2_context,
	&dra7xx_core_prm_rm_l3instr_l3_instr_context,
	&dra7xx_core_prm_rm_l3instr_ocp_wp_noc_context,
	NULL};

reg dra7xx_emu_prm_pm_emu_pwrstctrl = {
	"PM_EMU_PWRSTCTRL",
	DRA7XX_EMU_PRM_PM_EMU_PWRSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_emu_prm_pm_emu_pwrstst = {
	"PM_EMU_PWRSTST",
	DRA7XX_EMU_PRM_PM_EMU_PWRSTST,
	0xDEADBEEF,
	0};
reg dra7xx_emu_prm_rm_emu_debugss_context = {
	"RM_EMU_DEBUGSS_CONTEXT",
	DRA7XX_EMU_PRM_RM_EMU_DEBUGSS_CONTEXT,
	0xDEADBEEF,
	0};
reg *dra7xx_emu_prm_mod[DRA7XX_EMU_PRM_MOD_REGCOUNT + 1] = {
	&dra7xx_emu_prm_pm_emu_pwrstctrl,
	&dra7xx_emu_prm_pm_emu_pwrstst,
	&dra7xx_emu_prm_rm_emu_debugss_context,
	NULL};

reg dra7xx_mpu_prm_pm_mpu_pwrstctrl = {
	"PM_MPU_PWRSTCTRL",
	DRA7XX_MPU_PRM_PM_MPU_PWRSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_mpu_prm_pm_mpu_pwrstst = {
	"PM_MPU_PWRSTST",
	DRA7XX_MPU_PRM_PM_MPU_PWRSTST,
	0xDEADBEEF,
	0};
reg dra7xx_mpu_prm_rm_mpu_mpu_context = {
	"RM_MPU_MPU_CONTEXT",
	DRA7XX_MPU_PRM_RM_MPU_MPU_CONTEXT,
	0xDEADBEEF,
	0};
reg *dra7xx_mpu_prm_mod[DRA7XX_MPU_PRM_MOD_REGCOUNT + 1] = {
	&dra7xx_mpu_prm_pm_mpu_pwrstctrl,
	&dra7xx_mpu_prm_pm_mpu_pwrstst,
	&dra7xx_mpu_prm_rm_mpu_mpu_context,
	NULL};

reg dra7xx_l3init_prm_pm_l3init_pwrstctrl = {
	"PM_L3INIT_PWRSTCTRL",
	DRA7XX_L3INIT_PRM_PM_L3INIT_PWRSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_prm_pm_l3init_pwrstst = {
	"PM_L3INIT_PWRSTST",
	DRA7XX_L3INIT_PRM_PM_L3INIT_PWRSTST,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_prm_rm_pciess_rstctrl = {
	"RM_PCIESS_RSTCTRL",
	DRA7XX_L3INIT_PRM_RM_PCIESS_RSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_prm_rm_pciess_rstst = {
	"RM_PCIESS_RSTST",
	DRA7XX_L3INIT_PRM_RM_PCIESS_RSTST,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_prm_pm_l3init_mmc1_wkdep = {
	"PM_L3INIT_MMC1_WKDEP",
	DRA7XX_L3INIT_PRM_PM_L3INIT_MMC1_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_prm_rm_l3init_mmc1_context = {
	"RM_L3INIT_MMC1_CONTEXT",
	DRA7XX_L3INIT_PRM_RM_L3INIT_MMC1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_prm_pm_l3init_mmc2_wkdep = {
	"PM_L3INIT_MMC2_WKDEP",
	DRA7XX_L3INIT_PRM_PM_L3INIT_MMC2_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_prm_rm_l3init_mmc2_context = {
	"RM_L3INIT_MMC2_CONTEXT",
	DRA7XX_L3INIT_PRM_RM_L3INIT_MMC2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_prm_pm_l3init_usb_otg_ss2_wkdep = {
	"PM_L3INIT_USB_OTG_SS2_WKDEP",
	DRA7XX_L3INIT_PRM_PM_L3INIT_USB_OTG_SS2_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_prm_rm_l3init_usb_otg_ss2_context = {
	"RM_L3INIT_USB_OTG_SS2_CONTEXT",
	DRA7XX_L3INIT_PRM_RM_L3INIT_USB_OTG_SS2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_prm_pm_l3init_usb_otg_ss3_wkdep = {
	"PM_L3INIT_USB_OTG_SS3_WKDEP",
	DRA7XX_L3INIT_PRM_PM_L3INIT_USB_OTG_SS3_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_prm_rm_l3init_usb_otg_ss3_context = {
	"RM_L3INIT_USB_OTG_SS3_CONTEXT",
	DRA7XX_L3INIT_PRM_RM_L3INIT_USB_OTG_SS3_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_prm_pm_l3init_usb_otg_ss4_wkdep = {
	"PM_L3INIT_USB_OTG_SS4_WKDEP",
	DRA7XX_L3INIT_PRM_PM_L3INIT_USB_OTG_SS4_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_prm_rm_l3init_usb_otg_ss4_context = {
	"RM_L3INIT_USB_OTG_SS4_CONTEXT",
	DRA7XX_L3INIT_PRM_RM_L3INIT_USB_OTG_SS4_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_prm_rm_l3init_mlb_ss_context = {
	"RM_L3INIT_MLB_SS_CONTEXT",
	DRA7XX_L3INIT_PRM_RM_L3INIT_MLB_SS_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_prm_rm_l3init_ieee1500_2_ocp_context = {
	"RM_L3INIT_IEEE1500_2_OCP_CONTEXT",
	DRA7XX_L3INIT_PRM_RM_L3INIT_IEEE1500_2_OCP_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_prm_pm_l3init_sata_wkdep = {
	"PM_L3INIT_SATA_WKDEP",
	DRA7XX_L3INIT_PRM_PM_L3INIT_SATA_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_prm_rm_l3init_sata_context = {
	"RM_L3INIT_SATA_CONTEXT",
	DRA7XX_L3INIT_PRM_RM_L3INIT_SATA_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_prm_pm_pcie_pciess1_wkdep = {
	"PM_PCIE_PCIESS1_WKDEP",
	DRA7XX_L3INIT_PRM_PM_PCIE_PCIESS1_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_prm_rm_pcie_pciess1_context = {
	"RM_PCIE_PCIESS1_CONTEXT",
	DRA7XX_L3INIT_PRM_RM_PCIE_PCIESS1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_prm_pm_pcie_pciess2_wkdep = {
	"PM_PCIE_PCIESS2_WKDEP",
	DRA7XX_L3INIT_PRM_PM_PCIE_PCIESS2_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_prm_rm_pcie_pciess2_context = {
	"RM_PCIE_PCIESS2_CONTEXT",
	DRA7XX_L3INIT_PRM_RM_PCIE_PCIESS2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_prm_rm_gmac_gmac_context = {
	"RM_GMAC_GMAC_CONTEXT",
	DRA7XX_L3INIT_PRM_RM_GMAC_GMAC_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_prm_rm_l3init_ocp2scp1_context = {
	"RM_L3INIT_OCP2SCP1_CONTEXT",
	DRA7XX_L3INIT_PRM_RM_L3INIT_OCP2SCP1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_prm_rm_l3init_ocp2scp3_context = {
	"RM_L3INIT_OCP2SCP3_CONTEXT",
	DRA7XX_L3INIT_PRM_RM_L3INIT_OCP2SCP3_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_prm_pm_l3init_usb_otg_ss1_wkdep = {
	"PM_L3INIT_USB_OTG_SS1_WKDEP",
	DRA7XX_L3INIT_PRM_PM_L3INIT_USB_OTG_SS1_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_prm_rm_l3init_usb_otg_ss1_context = {
	"RM_L3INIT_USB_OTG_SS1_CONTEXT",
	DRA7XX_L3INIT_PRM_RM_L3INIT_USB_OTG_SS1_CONTEXT,
	0xDEADBEEF,
	0};
reg *dra7xx_l3init_prm_mod[DRA7XX_L3INIT_PRM_MOD_REGCOUNT + 1] = {
	&dra7xx_l3init_prm_pm_l3init_pwrstctrl,
	&dra7xx_l3init_prm_pm_l3init_pwrstst,
	&dra7xx_l3init_prm_rm_pciess_rstctrl,
	&dra7xx_l3init_prm_rm_pciess_rstst,
	&dra7xx_l3init_prm_pm_l3init_mmc1_wkdep,
	&dra7xx_l3init_prm_rm_l3init_mmc1_context,
	&dra7xx_l3init_prm_pm_l3init_mmc2_wkdep,
	&dra7xx_l3init_prm_rm_l3init_mmc2_context,
	&dra7xx_l3init_prm_pm_l3init_usb_otg_ss2_wkdep,
	&dra7xx_l3init_prm_rm_l3init_usb_otg_ss2_context,
	&dra7xx_l3init_prm_pm_l3init_usb_otg_ss3_wkdep,
	&dra7xx_l3init_prm_rm_l3init_usb_otg_ss3_context,
	&dra7xx_l3init_prm_pm_l3init_usb_otg_ss4_wkdep,
	&dra7xx_l3init_prm_rm_l3init_usb_otg_ss4_context,
	&dra7xx_l3init_prm_rm_l3init_mlb_ss_context,
	&dra7xx_l3init_prm_rm_l3init_ieee1500_2_ocp_context,
	&dra7xx_l3init_prm_pm_l3init_sata_wkdep,
	&dra7xx_l3init_prm_rm_l3init_sata_context,
	&dra7xx_l3init_prm_pm_pcie_pciess1_wkdep,
	&dra7xx_l3init_prm_rm_pcie_pciess1_context,
	&dra7xx_l3init_prm_pm_pcie_pciess2_wkdep,
	&dra7xx_l3init_prm_rm_pcie_pciess2_context,
	&dra7xx_l3init_prm_rm_gmac_gmac_context,
	&dra7xx_l3init_prm_rm_l3init_ocp2scp1_context,
	&dra7xx_l3init_prm_rm_l3init_ocp2scp3_context,
	&dra7xx_l3init_prm_pm_l3init_usb_otg_ss1_wkdep,
	&dra7xx_l3init_prm_rm_l3init_usb_otg_ss1_context,
	NULL};

reg dra7xx_prcm_mpu_prm_c0_pm_cpu0_pwrstctrl = {
	"PM_CPU0_PWRSTCTRL",
	DRA7XX_PRCM_MPU_PRM_C0_PM_CPU0_PWRSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_prcm_mpu_prm_c0_pm_cpu0_pwrstst = {
	"PM_CPU0_PWRSTST",
	DRA7XX_PRCM_MPU_PRM_C0_PM_CPU0_PWRSTST,
	0xDEADBEEF,
	0};
reg dra7xx_prcm_mpu_prm_c0_rm_cpu0_cpu0_rstctrl = {
	"RM_CPU0_CPU0_RSTCTRL",
	DRA7XX_PRCM_MPU_PRM_C0_RM_CPU0_CPU0_RSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_prcm_mpu_prm_c0_rm_cpu0_cpu0_rstst = {
	"RM_CPU0_CPU0_RSTST",
	DRA7XX_PRCM_MPU_PRM_C0_RM_CPU0_CPU0_RSTST,
	0xDEADBEEF,
	0};
reg dra7xx_prcm_mpu_prm_c0_rm_cpu0_cpu0_context = {
	"RM_CPU0_CPU0_CONTEXT",
	DRA7XX_PRCM_MPU_PRM_C0_RM_CPU0_CPU0_CONTEXT,
	0xDEADBEEF,
	0};
reg *dra7xx_prcm_mpu_prm_c0_mod[DRA7XX_PRCM_MPU_PRM_C0_MOD_REGCOUNT + 1] = {
	&dra7xx_prcm_mpu_prm_c0_pm_cpu0_pwrstctrl,
	&dra7xx_prcm_mpu_prm_c0_pm_cpu0_pwrstst,
	&dra7xx_prcm_mpu_prm_c0_rm_cpu0_cpu0_rstctrl,
	&dra7xx_prcm_mpu_prm_c0_rm_cpu0_cpu0_rstst,
	&dra7xx_prcm_mpu_prm_c0_rm_cpu0_cpu0_context,
	NULL};

reg dra7xx_prcm_mpu_prm_c1_pm_cpu1_pwrstctrl = {
	"PM_CPU1_PWRSTCTRL",
	DRA7XX_PRCM_MPU_PRM_C1_PM_CPU1_PWRSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_prcm_mpu_prm_c1_pm_cpu1_pwrstst = {
	"PM_CPU1_PWRSTST",
	DRA7XX_PRCM_MPU_PRM_C1_PM_CPU1_PWRSTST,
	0xDEADBEEF,
	0};
reg dra7xx_prcm_mpu_prm_c1_rm_cpu1_cpu1_rstctrl = {
	"RM_CPU1_CPU1_RSTCTRL",
	DRA7XX_PRCM_MPU_PRM_C1_RM_CPU1_CPU1_RSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_prcm_mpu_prm_c1_rm_cpu1_cpu1_rstst = {
	"RM_CPU1_CPU1_RSTST",
	DRA7XX_PRCM_MPU_PRM_C1_RM_CPU1_CPU1_RSTST,
	0xDEADBEEF,
	0};
reg dra7xx_prcm_mpu_prm_c1_rm_cpu1_cpu1_context = {
	"RM_CPU1_CPU1_CONTEXT",
	DRA7XX_PRCM_MPU_PRM_C1_RM_CPU1_CPU1_CONTEXT,
	0xDEADBEEF,
	0};
reg *dra7xx_prcm_mpu_prm_c1_mod[DRA7XX_PRCM_MPU_PRM_C1_MOD_REGCOUNT + 1] = {
	&dra7xx_prcm_mpu_prm_c1_pm_cpu1_pwrstctrl,
	&dra7xx_prcm_mpu_prm_c1_pm_cpu1_pwrstst,
	&dra7xx_prcm_mpu_prm_c1_rm_cpu1_cpu1_rstctrl,
	&dra7xx_prcm_mpu_prm_c1_rm_cpu1_cpu1_rstst,
	&dra7xx_prcm_mpu_prm_c1_rm_cpu1_cpu1_context,
	NULL};

reg dra7xx_eve1_prm_pm_eve1_pwrstctrl = {
	"PM_EVE1_PWRSTCTRL",
	DRA7XX_EVE1_PRM_PM_EVE1_PWRSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_eve1_prm_pm_eve1_pwrstst = {
	"PM_EVE1_PWRSTST",
	DRA7XX_EVE1_PRM_PM_EVE1_PWRSTST,
	0xDEADBEEF,
	0};
reg dra7xx_eve1_prm_rm_eve1_rstctrl = {
	"RM_EVE1_RSTCTRL",
	DRA7XX_EVE1_PRM_RM_EVE1_RSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_eve1_prm_rm_eve1_rstst = {
	"RM_EVE1_RSTST",
	DRA7XX_EVE1_PRM_RM_EVE1_RSTST,
	0xDEADBEEF,
	0};
reg dra7xx_eve1_prm_pm_eve1_eve1_wkdep = {
	"PM_EVE1_EVE1_WKDEP",
	DRA7XX_EVE1_PRM_PM_EVE1_EVE1_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_eve1_prm_rm_eve1_eve1_context = {
	"RM_EVE1_EVE1_CONTEXT",
	DRA7XX_EVE1_PRM_RM_EVE1_EVE1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_eve2_prm_pm_eve2_pwrstctrl = {
	"PM_EVE2_PWRSTCTRL",
	DRA7XX_EVE2_PRM_PM_EVE2_PWRSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_eve2_prm_pm_eve2_pwrstst = {
	"PM_EVE2_PWRSTST",
	DRA7XX_EVE2_PRM_PM_EVE2_PWRSTST,
	0xDEADBEEF,
	0};
reg dra7xx_eve2_prm_rm_eve2_rstctrl = {
	"RM_EVE2_RSTCTRL",
	DRA7XX_EVE2_PRM_RM_EVE2_RSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_eve2_prm_rm_eve2_rstst = {
	"RM_EVE2_RSTST",
	DRA7XX_EVE2_PRM_RM_EVE2_RSTST,
	0xDEADBEEF,
	0};
reg dra7xx_eve2_prm_pm_eve2_eve2_wkdep = {
	"PM_EVE2_EVE2_WKDEP",
	DRA7XX_EVE2_PRM_PM_EVE2_EVE2_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_eve2_prm_rm_eve2_eve2_context = {
	"RM_EVE2_EVE2_CONTEXT",
	DRA7XX_EVE2_PRM_RM_EVE2_EVE2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_eve3_prm_pm_eve3_pwrstctrl = {
	"PM_EVE3_PWRSTCTRL",
	DRA7XX_EVE3_PRM_PM_EVE3_PWRSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_eve3_prm_pm_eve3_pwrstst = {
	"PM_EVE3_PWRSTST",
	DRA7XX_EVE3_PRM_PM_EVE3_PWRSTST,
	0xDEADBEEF,
	0};
reg dra7xx_eve3_prm_rm_eve3_rstctrl = {
	"RM_EVE3_RSTCTRL",
	DRA7XX_EVE3_PRM_RM_EVE3_RSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_eve3_prm_rm_eve3_rstst = {
	"RM_EVE3_RSTST",
	DRA7XX_EVE3_PRM_RM_EVE3_RSTST,
	0xDEADBEEF,
	0};
reg dra7xx_eve3_prm_pm_eve3_eve3_wkdep = {
	"PM_EVE3_EVE3_WKDEP",
	DRA7XX_EVE3_PRM_PM_EVE3_EVE3_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_eve3_prm_rm_eve3_eve3_context = {
	"RM_EVE3_EVE3_CONTEXT",
	DRA7XX_EVE3_PRM_RM_EVE3_EVE3_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_eve4_prm_pm_eve4_pwrstctrl = {
	"PM_EVE4_PWRSTCTRL",
	DRA7XX_EVE4_PRM_PM_EVE4_PWRSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_eve4_prm_pm_eve4_pwrstst = {
	"PM_EVE4_PWRSTST",
	DRA7XX_EVE4_PRM_PM_EVE4_PWRSTST,
	0xDEADBEEF,
	0};
reg dra7xx_eve4_prm_rm_eve4_rstctrl = {
	"RM_EVE4_RSTCTRL",
	DRA7XX_EVE4_PRM_RM_EVE4_RSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_eve4_prm_rm_eve4_rstst = {
	"RM_EVE4_RSTST",
	DRA7XX_EVE4_PRM_RM_EVE4_RSTST,
	0xDEADBEEF,
	0};
reg dra7xx_eve4_prm_pm_eve4_eve4_wkdep = {
	"PM_EVE4_EVE4_WKDEP",
	DRA7XX_EVE4_PRM_PM_EVE4_EVE4_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_eve4_prm_rm_eve4_eve4_context = {
	"RM_EVE4_EVE4_CONTEXT",
	DRA7XX_EVE4_PRM_RM_EVE4_EVE4_CONTEXT,
	0xDEADBEEF,
	0};
reg *dra7xx_eve_prm_mod[DRA7XX_EVE_PRM_MOD_REGCOUNT + 1] = {
	&dra7xx_eve1_prm_pm_eve1_pwrstctrl,
	&dra7xx_eve1_prm_pm_eve1_pwrstst,
	&dra7xx_eve1_prm_rm_eve1_rstctrl,
	&dra7xx_eve1_prm_rm_eve1_rstst,
	&dra7xx_eve1_prm_pm_eve1_eve1_wkdep,
	&dra7xx_eve1_prm_rm_eve1_eve1_context,
	&dra7xx_eve2_prm_pm_eve2_pwrstctrl,
	&dra7xx_eve2_prm_pm_eve2_pwrstst,
	&dra7xx_eve2_prm_rm_eve2_rstctrl,
	&dra7xx_eve2_prm_rm_eve2_rstst,
	&dra7xx_eve2_prm_pm_eve2_eve2_wkdep,
	&dra7xx_eve2_prm_rm_eve2_eve2_context,
	&dra7xx_eve3_prm_pm_eve3_pwrstctrl,
	&dra7xx_eve3_prm_pm_eve3_pwrstst,
	&dra7xx_eve3_prm_rm_eve3_rstctrl,
	&dra7xx_eve3_prm_rm_eve3_rstst,
	&dra7xx_eve3_prm_pm_eve3_eve3_wkdep,
	&dra7xx_eve3_prm_rm_eve3_eve3_context,
	&dra7xx_eve4_prm_pm_eve4_pwrstctrl,
	&dra7xx_eve4_prm_pm_eve4_pwrstst,
	&dra7xx_eve4_prm_rm_eve4_rstctrl,
	&dra7xx_eve4_prm_rm_eve4_rstst,
	&dra7xx_eve4_prm_pm_eve4_eve4_wkdep,
	&dra7xx_eve4_prm_rm_eve4_eve4_context,
	NULL};

reg dra7xx_ipu_prm_pm_ipu_pwrstctrl = {
	"PM_IPU_PWRSTCTRL",
	DRA7XX_IPU_PRM_PM_IPU_PWRSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_prm_pm_ipu_pwrstst = {
	"PM_IPU_PWRSTST",
	DRA7XX_IPU_PRM_PM_IPU_PWRSTST,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_prm_rm_ipu1_rstctrl = {
	"RM_IPU1_RSTCTRL",
	DRA7XX_IPU_PRM_RM_IPU1_RSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_prm_rm_ipu1_rstst = {
	"RM_IPU1_RSTST",
	DRA7XX_IPU_PRM_RM_IPU1_RSTST,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_prm_rm_ipu1_ipu1_context = {
	"RM_IPU1_IPU1_CONTEXT",
	DRA7XX_IPU_PRM_RM_IPU1_IPU1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_prm_pm_ipu_mcasp1_wkdep = {
	"PM_IPU_MCASP1_WKDEP",
	DRA7XX_IPU_PRM_PM_IPU_MCASP1_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_prm_rm_ipu_mcasp1_context = {
	"RM_IPU_MCASP1_CONTEXT",
	DRA7XX_IPU_PRM_RM_IPU_MCASP1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_prm_pm_ipu_timer5_wkdep = {
	"PM_IPU_TIMER5_WKDEP",
	DRA7XX_IPU_PRM_PM_IPU_TIMER5_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_prm_rm_ipu_timer5_context = {
	"RM_IPU_TIMER5_CONTEXT",
	DRA7XX_IPU_PRM_RM_IPU_TIMER5_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_prm_pm_ipu_timer6_wkdep = {
	"PM_IPU_TIMER6_WKDEP",
	DRA7XX_IPU_PRM_PM_IPU_TIMER6_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_prm_rm_ipu_timer6_context = {
	"RM_IPU_TIMER6_CONTEXT",
	DRA7XX_IPU_PRM_RM_IPU_TIMER6_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_prm_pm_ipu_timer7_wkdep = {
	"PM_IPU_TIMER7_WKDEP",
	DRA7XX_IPU_PRM_PM_IPU_TIMER7_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_prm_rm_ipu_timer7_context = {
	"RM_IPU_TIMER7_CONTEXT",
	DRA7XX_IPU_PRM_RM_IPU_TIMER7_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_prm_pm_ipu_timer8_wkdep = {
	"PM_IPU_TIMER8_WKDEP",
	DRA7XX_IPU_PRM_PM_IPU_TIMER8_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_prm_rm_ipu_timer8_context = {
	"RM_IPU_TIMER8_CONTEXT",
	DRA7XX_IPU_PRM_RM_IPU_TIMER8_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_prm_pm_ipu_i2c5_wkdep = {
	"PM_IPU_I2C5_WKDEP",
	DRA7XX_IPU_PRM_PM_IPU_I2C5_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_prm_rm_ipu_i2c5_context = {
	"RM_IPU_I2C5_CONTEXT",
	DRA7XX_IPU_PRM_RM_IPU_I2C5_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_prm_pm_ipu_uart6_wkdep = {
	"PM_IPU_UART6_WKDEP",
	DRA7XX_IPU_PRM_PM_IPU_UART6_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_prm_rm_ipu_uart6_context = {
	"RM_IPU_UART6_CONTEXT",
	DRA7XX_IPU_PRM_RM_IPU_UART6_CONTEXT,
	0xDEADBEEF,
	0};
reg *dra7xx_ipu_prm_mod[DRA7XX_IPU_PRM_MOD_REGCOUNT + 1] = {
	&dra7xx_ipu_prm_pm_ipu_pwrstctrl,
	&dra7xx_ipu_prm_pm_ipu_pwrstst,
	&dra7xx_ipu_prm_rm_ipu1_rstctrl,
	&dra7xx_ipu_prm_rm_ipu1_rstst,
	&dra7xx_ipu_prm_rm_ipu1_ipu1_context,
	&dra7xx_ipu_prm_pm_ipu_mcasp1_wkdep,
	&dra7xx_ipu_prm_rm_ipu_mcasp1_context,
	&dra7xx_ipu_prm_pm_ipu_timer5_wkdep,
	&dra7xx_ipu_prm_rm_ipu_timer5_context,
	&dra7xx_ipu_prm_pm_ipu_timer6_wkdep,
	&dra7xx_ipu_prm_rm_ipu_timer6_context,
	&dra7xx_ipu_prm_pm_ipu_timer7_wkdep,
	&dra7xx_ipu_prm_rm_ipu_timer7_context,
	&dra7xx_ipu_prm_pm_ipu_timer8_wkdep,
	&dra7xx_ipu_prm_rm_ipu_timer8_context,
	&dra7xx_ipu_prm_pm_ipu_i2c5_wkdep,
	&dra7xx_ipu_prm_rm_ipu_i2c5_context,
	&dra7xx_ipu_prm_pm_ipu_uart6_wkdep,
	&dra7xx_ipu_prm_rm_ipu_uart6_context,
	NULL};

reg dra7xx_l4per_prm_pm_l4per_pwrstctrl = {
	"PM_L4PER_PWRSTCTRL",
	DRA7XX_L4PER_PRM_PM_L4PER_PWRSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_pwrstst = {
	"PM_L4PER_PWRSTST",
	DRA7XX_L4PER_PRM_PM_L4PER_PWRSTST,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per2_l4per2_context = {
	"RM_L4PER2_L4PER2_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER2_L4PER2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per3_l4per3_context = {
	"RM_L4PER3_L4PER3_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER3_L4PER3_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per2_pruss1_context = {
	"RM_L4PER2_PRUSS1_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER2_PRUSS1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per2_pruss2_context = {
	"RM_L4PER2_PRUSS2_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER2_PRUSS2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_timer10_wkdep = {
	"PM_L4PER_TIMER10_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_TIMER10_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_timer10_context = {
	"RM_L4PER_TIMER10_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_TIMER10_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_timer11_wkdep = {
	"PM_L4PER_TIMER11_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_TIMER11_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_timer11_context = {
	"RM_L4PER_TIMER11_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_TIMER11_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_timer2_wkdep = {
	"PM_L4PER_TIMER2_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_TIMER2_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_timer2_context = {
	"RM_L4PER_TIMER2_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_TIMER2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_timer3_wkdep = {
	"PM_L4PER_TIMER3_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_TIMER3_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_timer3_context = {
	"RM_L4PER_TIMER3_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_TIMER3_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_timer4_wkdep = {
	"PM_L4PER_TIMER4_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_TIMER4_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_timer4_context = {
	"RM_L4PER_TIMER4_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_TIMER4_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_timer9_wkdep = {
	"PM_L4PER_TIMER9_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_TIMER9_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_timer9_context = {
	"RM_L4PER_TIMER9_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_TIMER9_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_elm_context = {
	"RM_L4PER_ELM_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_ELM_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_gpio2_wkdep = {
	"PM_L4PER_GPIO2_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_GPIO2_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_gpio2_context = {
	"RM_L4PER_GPIO2_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_GPIO2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_gpio3_wkdep = {
	"PM_L4PER_GPIO3_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_GPIO3_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_gpio3_context = {
	"RM_L4PER_GPIO3_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_GPIO3_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_gpio4_wkdep = {
	"PM_L4PER_GPIO4_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_GPIO4_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_gpio4_context = {
	"RM_L4PER_GPIO4_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_GPIO4_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_gpio5_wkdep = {
	"PM_L4PER_GPIO5_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_GPIO5_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_gpio5_context = {
	"RM_L4PER_GPIO5_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_GPIO5_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_gpio6_wkdep = {
	"PM_L4PER_GPIO6_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_GPIO6_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_gpio6_context = {
	"RM_L4PER_GPIO6_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_GPIO6_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_hdq1w_context = {
	"RM_L4PER_HDQ1W_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_HDQ1W_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per2_pwmss2_context = {
	"RM_L4PER2_PWMSS2_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER2_PWMSS2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per2_pwmss3_context = {
	"RM_L4PER2_PWMSS3_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER2_PWMSS3_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_i2c1_wkdep = {
	"PM_L4PER_I2C1_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_I2C1_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_i2c1_context = {
	"RM_L4PER_I2C1_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_I2C1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_i2c2_wkdep = {
	"PM_L4PER_I2C2_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_I2C2_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_i2c2_context = {
	"RM_L4PER_I2C2_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_I2C2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_i2c3_wkdep = {
	"PM_L4PER_I2C3_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_I2C3_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_i2c3_context = {
	"RM_L4PER_I2C3_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_I2C3_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_i2c4_wkdep = {
	"PM_L4PER_I2C4_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_I2C4_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_i2c4_context = {
	"RM_L4PER_I2C4_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_I2C4_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_l4per1_context = {
	"RM_L4PER_L4PER1_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_L4PER1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per2_pwmss1_context = {
	"RM_L4PER2_PWMSS1_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER2_PWMSS1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_timer13_wkdep = {
	"PM_L4PER_TIMER13_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_TIMER13_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per3_timer13_context = {
	"RM_L4PER3_TIMER13_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER3_TIMER13_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_timer14_wkdep = {
	"PM_L4PER_TIMER14_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_TIMER14_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per3_timer14_context = {
	"RM_L4PER3_TIMER14_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER3_TIMER14_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_timer15_wkdep = {
	"PM_L4PER_TIMER15_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_TIMER15_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per3_timer15_context = {
	"RM_L4PER3_TIMER15_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER3_TIMER15_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_mcspi1_wkdep = {
	"PM_L4PER_MCSPI1_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_MCSPI1_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_mcspi1_context = {
	"RM_L4PER_MCSPI1_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_MCSPI1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_mcspi2_wkdep = {
	"PM_L4PER_MCSPI2_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_MCSPI2_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_mcspi2_context = {
	"RM_L4PER_MCSPI2_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_MCSPI2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_mcspi3_wkdep = {
	"PM_L4PER_MCSPI3_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_MCSPI3_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_mcspi3_context = {
	"RM_L4PER_MCSPI3_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_MCSPI3_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_mcspi4_wkdep = {
	"PM_L4PER_MCSPI4_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_MCSPI4_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_mcspi4_context = {
	"RM_L4PER_MCSPI4_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_MCSPI4_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_gpio7_wkdep = {
	"PM_L4PER_GPIO7_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_GPIO7_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_gpio7_context = {
	"RM_L4PER_GPIO7_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_GPIO7_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_gpio8_wkdep = {
	"PM_L4PER_GPIO8_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_GPIO8_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_gpio8_context = {
	"RM_L4PER_GPIO8_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_GPIO8_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_mmc3_wkdep = {
	"PM_L4PER_MMC3_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_MMC3_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_mmc3_context = {
	"RM_L4PER_MMC3_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_MMC3_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_mmc4_wkdep = {
	"PM_L4PER_MMC4_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_MMC4_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_mmc4_context = {
	"RM_L4PER_MMC4_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_MMC4_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_timer16_wkdep = {
	"PM_L4PER_TIMER16_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_TIMER16_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per3_timer16_context = {
	"RM_L4PER3_TIMER16_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER3_TIMER16_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per2_qspi_wkdep = {
	"PM_L4PER2_QSPI_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER2_QSPI_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per2_qspi_context = {
	"RM_L4PER2_QSPI_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER2_QSPI_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_uart1_wkdep = {
	"PM_L4PER_UART1_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_UART1_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_uart1_context = {
	"RM_L4PER_UART1_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_UART1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_uart2_wkdep = {
	"PM_L4PER_UART2_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_UART2_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_uart2_context = {
	"RM_L4PER_UART2_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_UART2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_uart3_wkdep = {
	"PM_L4PER_UART3_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_UART3_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_uart3_context = {
	"RM_L4PER_UART3_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_UART3_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_uart4_wkdep = {
	"PM_L4PER_UART4_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_UART4_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_uart4_context = {
	"RM_L4PER_UART4_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_UART4_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per2_mcasp2_wkdep = {
	"PM_L4PER2_MCASP2_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER2_MCASP2_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per2_mcasp2_context = {
	"RM_L4PER2_MCASP2_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER2_MCASP2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per2_mcasp3_wkdep = {
	"PM_L4PER2_MCASP3_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER2_MCASP3_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per2_mcasp3_context = {
	"RM_L4PER2_MCASP3_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER2_MCASP3_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per_uart5_wkdep = {
	"PM_L4PER_UART5_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER_UART5_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per_uart5_context = {
	"RM_L4PER_UART5_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER_UART5_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per2_mcasp5_wkdep = {
	"PM_L4PER2_MCASP5_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER2_MCASP5_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per2_mcasp5_context = {
	"RM_L4PER2_MCASP5_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER2_MCASP5_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per2_mcasp6_wkdep = {
	"PM_L4PER2_MCASP6_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER2_MCASP6_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per2_mcasp6_context = {
	"RM_L4PER2_MCASP6_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER2_MCASP6_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per2_mcasp7_wkdep = {
	"PM_L4PER2_MCASP7_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER2_MCASP7_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per2_mcasp7_context = {
	"RM_L4PER2_MCASP7_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER2_MCASP7_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per2_mcasp8_wkdep = {
	"PM_L4PER2_MCASP8_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER2_MCASP8_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per2_mcasp8_context = {
	"RM_L4PER2_MCASP8_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER2_MCASP8_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per2_mcasp4_wkdep = {
	"PM_L4PER2_MCASP4_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER2_MCASP4_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per2_mcasp4_context = {
	"RM_L4PER2_MCASP4_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER2_MCASP4_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4sec_aes1_context = {
	"RM_L4SEC_AES1_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4SEC_AES1_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4sec_aes2_context = {
	"RM_L4SEC_AES2_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4SEC_AES2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4sec_des3des_context = {
	"RM_L4SEC_DES3DES_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4SEC_DES3DES_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4sec_fpka_context = {
	"RM_L4SEC_FPKA_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4SEC_FPKA_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4sec_rng_context = {
	"RM_L4SEC_RNG_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4SEC_RNG_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4sec_sha2md51_context = {
	"RM_L4SEC_SHA2MD51_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4SEC_SHA2MD51_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per2_uart7_wkdep = {
	"PM_L4PER2_UART7_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER2_UART7_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per2_uart7_context = {
	"RM_L4PER2_UART7_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER2_UART7_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4sec_dma_crypto_context = {
	"RM_L4SEC_DMA_CRYPTO_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4SEC_DMA_CRYPTO_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per2_uart8_wkdep = {
	"PM_L4PER2_UART8_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER2_UART8_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per2_uart8_context = {
	"RM_L4PER2_UART8_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER2_UART8_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per2_uart9_wkdep = {
	"PM_L4PER2_UART9_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER2_UART9_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per2_uart9_context = {
	"RM_L4PER2_UART9_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER2_UART9_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_pm_l4per2_dcan2_wkdep = {
	"PM_L4PER2_DCAN2_WKDEP",
	DRA7XX_L4PER_PRM_PM_L4PER2_DCAN2_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4per2_dcan2_context = {
	"RM_L4PER2_DCAN2_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4PER2_DCAN2_CONTEXT,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_prm_rm_l4sec_sha2md52_context = {
	"RM_L4SEC_SHA2MD52_CONTEXT",
	DRA7XX_L4PER_PRM_RM_L4SEC_SHA2MD52_CONTEXT,
	0xDEADBEEF,
	0};
reg *dra7xx_l4per_prm_mod[DRA7XX_L4PER_PRM_MOD_REGCOUNT + 1] = {
	&dra7xx_l4per_prm_pm_l4per_pwrstctrl,
	&dra7xx_l4per_prm_pm_l4per_pwrstst,
	&dra7xx_l4per_prm_rm_l4per2_l4per2_context,
	&dra7xx_l4per_prm_rm_l4per3_l4per3_context,
	&dra7xx_l4per_prm_rm_l4per2_pruss1_context,
	&dra7xx_l4per_prm_rm_l4per2_pruss2_context,
	&dra7xx_l4per_prm_pm_l4per_timer10_wkdep,
	&dra7xx_l4per_prm_rm_l4per_timer10_context,
	&dra7xx_l4per_prm_pm_l4per_timer11_wkdep,
	&dra7xx_l4per_prm_rm_l4per_timer11_context,
	&dra7xx_l4per_prm_pm_l4per_timer2_wkdep,
	&dra7xx_l4per_prm_rm_l4per_timer2_context,
	&dra7xx_l4per_prm_pm_l4per_timer3_wkdep,
	&dra7xx_l4per_prm_rm_l4per_timer3_context,
	&dra7xx_l4per_prm_pm_l4per_timer4_wkdep,
	&dra7xx_l4per_prm_rm_l4per_timer4_context,
	&dra7xx_l4per_prm_pm_l4per_timer9_wkdep,
	&dra7xx_l4per_prm_rm_l4per_timer9_context,
	&dra7xx_l4per_prm_rm_l4per_elm_context,
	&dra7xx_l4per_prm_pm_l4per_gpio2_wkdep,
	&dra7xx_l4per_prm_rm_l4per_gpio2_context,
	&dra7xx_l4per_prm_pm_l4per_gpio3_wkdep,
	&dra7xx_l4per_prm_rm_l4per_gpio3_context,
	&dra7xx_l4per_prm_pm_l4per_gpio4_wkdep,
	&dra7xx_l4per_prm_rm_l4per_gpio4_context,
	&dra7xx_l4per_prm_pm_l4per_gpio5_wkdep,
	&dra7xx_l4per_prm_rm_l4per_gpio5_context,
	&dra7xx_l4per_prm_pm_l4per_gpio6_wkdep,
	&dra7xx_l4per_prm_rm_l4per_gpio6_context,
	&dra7xx_l4per_prm_rm_l4per_hdq1w_context,
	&dra7xx_l4per_prm_rm_l4per2_pwmss2_context,
	&dra7xx_l4per_prm_rm_l4per2_pwmss3_context,
	&dra7xx_l4per_prm_pm_l4per_i2c1_wkdep,
	&dra7xx_l4per_prm_rm_l4per_i2c1_context,
	&dra7xx_l4per_prm_pm_l4per_i2c2_wkdep,
	&dra7xx_l4per_prm_rm_l4per_i2c2_context,
	&dra7xx_l4per_prm_pm_l4per_i2c3_wkdep,
	&dra7xx_l4per_prm_rm_l4per_i2c3_context,
	&dra7xx_l4per_prm_pm_l4per_i2c4_wkdep,
	&dra7xx_l4per_prm_rm_l4per_i2c4_context,
	&dra7xx_l4per_prm_rm_l4per_l4per1_context,
	&dra7xx_l4per_prm_rm_l4per2_pwmss1_context,
	&dra7xx_l4per_prm_pm_l4per_timer13_wkdep,
	&dra7xx_l4per_prm_rm_l4per3_timer13_context,
	&dra7xx_l4per_prm_pm_l4per_timer14_wkdep,
	&dra7xx_l4per_prm_rm_l4per3_timer14_context,
	&dra7xx_l4per_prm_pm_l4per_timer15_wkdep,
	&dra7xx_l4per_prm_rm_l4per3_timer15_context,
	&dra7xx_l4per_prm_pm_l4per_mcspi1_wkdep,
	&dra7xx_l4per_prm_rm_l4per_mcspi1_context,
	&dra7xx_l4per_prm_pm_l4per_mcspi2_wkdep,
	&dra7xx_l4per_prm_rm_l4per_mcspi2_context,
	&dra7xx_l4per_prm_pm_l4per_mcspi3_wkdep,
	&dra7xx_l4per_prm_rm_l4per_mcspi3_context,
	&dra7xx_l4per_prm_pm_l4per_mcspi4_wkdep,
	&dra7xx_l4per_prm_rm_l4per_mcspi4_context,
	&dra7xx_l4per_prm_pm_l4per_gpio7_wkdep,
	&dra7xx_l4per_prm_rm_l4per_gpio7_context,
	&dra7xx_l4per_prm_pm_l4per_gpio8_wkdep,
	&dra7xx_l4per_prm_rm_l4per_gpio8_context,
	&dra7xx_l4per_prm_pm_l4per_mmc3_wkdep,
	&dra7xx_l4per_prm_rm_l4per_mmc3_context,
	&dra7xx_l4per_prm_pm_l4per_mmc4_wkdep,
	&dra7xx_l4per_prm_rm_l4per_mmc4_context,
	&dra7xx_l4per_prm_pm_l4per_timer16_wkdep,
	&dra7xx_l4per_prm_rm_l4per3_timer16_context,
	&dra7xx_l4per_prm_pm_l4per2_qspi_wkdep,
	&dra7xx_l4per_prm_rm_l4per2_qspi_context,
	&dra7xx_l4per_prm_pm_l4per_uart1_wkdep,
	&dra7xx_l4per_prm_rm_l4per_uart1_context,
	&dra7xx_l4per_prm_pm_l4per_uart2_wkdep,
	&dra7xx_l4per_prm_rm_l4per_uart2_context,
	&dra7xx_l4per_prm_pm_l4per_uart3_wkdep,
	&dra7xx_l4per_prm_rm_l4per_uart3_context,
	&dra7xx_l4per_prm_pm_l4per_uart4_wkdep,
	&dra7xx_l4per_prm_rm_l4per_uart4_context,
	&dra7xx_l4per_prm_pm_l4per2_mcasp2_wkdep,
	&dra7xx_l4per_prm_rm_l4per2_mcasp2_context,
	&dra7xx_l4per_prm_pm_l4per2_mcasp3_wkdep,
	&dra7xx_l4per_prm_rm_l4per2_mcasp3_context,
	&dra7xx_l4per_prm_pm_l4per_uart5_wkdep,
	&dra7xx_l4per_prm_rm_l4per_uart5_context,
	&dra7xx_l4per_prm_pm_l4per2_mcasp5_wkdep,
	&dra7xx_l4per_prm_rm_l4per2_mcasp5_context,
	&dra7xx_l4per_prm_pm_l4per2_mcasp6_wkdep,
	&dra7xx_l4per_prm_rm_l4per2_mcasp6_context,
	&dra7xx_l4per_prm_pm_l4per2_mcasp7_wkdep,
	&dra7xx_l4per_prm_rm_l4per2_mcasp7_context,
	&dra7xx_l4per_prm_pm_l4per2_mcasp8_wkdep,
	&dra7xx_l4per_prm_rm_l4per2_mcasp8_context,
	&dra7xx_l4per_prm_pm_l4per2_mcasp4_wkdep,
	&dra7xx_l4per_prm_rm_l4per2_mcasp4_context,
	&dra7xx_l4per_prm_rm_l4sec_aes1_context,
	&dra7xx_l4per_prm_rm_l4sec_aes2_context,
	&dra7xx_l4per_prm_rm_l4sec_des3des_context,
	&dra7xx_l4per_prm_rm_l4sec_fpka_context,
	&dra7xx_l4per_prm_rm_l4sec_rng_context,
	&dra7xx_l4per_prm_rm_l4sec_sha2md51_context,
	&dra7xx_l4per_prm_pm_l4per2_uart7_wkdep,
	&dra7xx_l4per_prm_rm_l4per2_uart7_context,
	&dra7xx_l4per_prm_rm_l4sec_dma_crypto_context,
	&dra7xx_l4per_prm_pm_l4per2_uart8_wkdep,
	&dra7xx_l4per_prm_rm_l4per2_uart8_context,
	&dra7xx_l4per_prm_pm_l4per2_uart9_wkdep,
	&dra7xx_l4per_prm_rm_l4per2_uart9_context,
	&dra7xx_l4per_prm_pm_l4per2_dcan2_wkdep,
	&dra7xx_l4per_prm_rm_l4per2_dcan2_context,
	&dra7xx_l4per_prm_rm_l4sec_sha2md52_context,
	NULL};

reg dra7xx_rtc_prm_pm_rtc_rtcss_wkdep = {
	"PM_RTC_RTCSS_WKDEP",
	DRA7XX_RTC_PRM_PM_RTC_RTCSS_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_rtc_prm_rm_rtc_rtcss_context = {
	"RM_RTC_RTCSS_CONTEXT",
	DRA7XX_RTC_PRM_RM_RTC_RTCSS_CONTEXT,
	0xDEADBEEF,
	0};
reg *dra7xx_rtc_prm_mod[DRA7XX_RTC_PRM_MOD_REGCOUNT + 1] = {
	&dra7xx_rtc_prm_pm_rtc_rtcss_wkdep,
	&dra7xx_rtc_prm_rm_rtc_rtcss_context,
	NULL};

reg dra7xx_vpe_prm_pm_vpe_pwrstctrl = {
	"PM_VPE_PWRSTCTRL",
	DRA7XX_VPE_PRM_PM_VPE_PWRSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_vpe_prm_pm_vpe_pwrstst = {
	"PM_VPE_PWRSTST",
	DRA7XX_VPE_PRM_PM_VPE_PWRSTST,
	0xDEADBEEF,
	0};
reg dra7xx_vpe_prm_pm_vpe_vpe_wkdep = {
	"PM_VPE_VPE_WKDEP",
	DRA7XX_VPE_PRM_PM_VPE_VPE_WKDEP,
	0xDEADBEEF,
	0};
reg dra7xx_vpe_prm_rm_vpe_vpe_context = {
	"RM_VPE_VPE_CONTEXT",
	DRA7XX_VPE_PRM_RM_VPE_VPE_CONTEXT,
	0xDEADBEEF,
	0};
reg *dra7xx_vpe_prm_mod[DRA7XX_VPE_PRM_MOD_REGCOUNT + 1] = {
	&dra7xx_vpe_prm_pm_vpe_pwrstctrl,
	&dra7xx_vpe_prm_pm_vpe_pwrstst,
	&dra7xx_vpe_prm_pm_vpe_vpe_wkdep,
	&dra7xx_vpe_prm_rm_vpe_vpe_context,
	NULL};

reg **prm_dra7xx_mods[PRM_DRA7XX_MODS_COUNT + 1] = {
	[PRM_DRA7XX_DSS_PRM] = (reg **) &dra7xx_dss_prm_mod,
	[PRM_DRA7XX_WKUPAON_PRM] = (reg **) &dra7xx_wkupaon_prm_mod,
	[PRM_DRA7XX_OCP_SOCKET_PRM] = (reg **) &dra7xx_ocp_socket_prm_mod,
	[PRM_DRA7XX_CAM_PRM] = (reg **) &dra7xx_cam_prm_mod,
	[PRM_DRA7XX_DSP_PRM] = (reg **) &dra7xx_dsp_prm_mod,
	[PRM_DRA7XX_DEVICE_PRM] = (reg **) &dra7xx_device_prm_mod,
	[PRM_DRA7XX_GPU_PRM] = (reg **) &dra7xx_gpu_prm_mod,
	[PRM_DRA7XX_COREAON_PRM] = (reg **) &dra7xx_coreaon_prm_mod,
	[PRM_DRA7XX_CUSTEFUSE_PRM] = (reg **) &dra7xx_custefuse_prm_mod,
	[PRM_DRA7XX_CKGEN_PRM] = (reg **) &dra7xx_ckgen_prm_mod,
	[PRM_DRA7XX_INSTR_PRM] = (reg **) &dra7xx_instr_prm_mod,
	[PRM_DRA7XX_IVA_PRM] = (reg **) &dra7xx_iva_prm_mod,
	[PRM_DRA7XX_EMU_PRM] = (reg **) &dra7xx_emu_prm_mod,
	[PRM_DRA7XX_MPU_PRM] = (reg **) &dra7xx_mpu_prm_mod,
	[PRM_DRA7XX_L3INIT_PRM] = (reg **) &dra7xx_l3init_prm_mod,
	[PRM_DRA7XX_CORE_PRM] = (reg **) &dra7xx_core_prm_mod,
	[PRM_DRA7XX_L4PER_PRM] = (reg **) &dra7xx_l4per_prm_mod,
	[PRM_DRA7XX_PRCM_MPU_PRM_C0] = (reg **) &dra7xx_prcm_mpu_prm_c0_mod,
	[PRM_DRA7XX_PRCM_MPU_PRM_C1] = (reg **) &dra7xx_prcm_mpu_prm_c1_mod,
	[PRM_DRA7XX_EVE_PRM] = (reg **) &dra7xx_eve_prm_mod,
	[PRM_DRA7XX_IPU_PRM] = (reg **) &dra7xx_ipu_prm_mod,
	[PRM_DRA7XX_RTC_PRM] = (reg **) &dra7xx_rtc_prm_mod,
	[PRM_DRA7XX_VPE_PRM] = (reg **) &dra7xx_vpe_prm_mod,
	NULL};

const char *prm_dra7xx_mods_name[PRM_DRA7XX_MODS_COUNT] = {
	[PRM_DRA7XX_DSS_PRM] = "PRM DSS",
	[PRM_DRA7XX_WKUPAON_PRM] = "PRM WKUPAON",
	[PRM_DRA7XX_OCP_SOCKET_PRM] = "PRM OCP SOCKET",
	[PRM_DRA7XX_CAM_PRM] = "PRM CAM",
	[PRM_DRA7XX_DSP_PRM] = "PRM DSP",
	[PRM_DRA7XX_DEVICE_PRM] = "PRM DEVICE",
	[PRM_DRA7XX_GPU_PRM] = "PRM GPU",
	[PRM_DRA7XX_COREAON_PRM] = "PRM COREAON",
	[PRM_DRA7XX_CUSTEFUSE_PRM] = "PRM CUSTEFUSE",
	[PRM_DRA7XX_CKGEN_PRM] = "PRM CKGEN",
	[PRM_DRA7XX_INSTR_PRM] = "PRM INSTR",
	[PRM_DRA7XX_IVA_PRM] = "PRM IVA",
	[PRM_DRA7XX_EMU_PRM] = "PRM EMU",
	[PRM_DRA7XX_MPU_PRM] = "PRM MPU",
	[PRM_DRA7XX_L3INIT_PRM] = "PRM L3INIT",
	[PRM_DRA7XX_CORE_PRM] = "PRM CORE",
	[PRM_DRA7XX_L4PER_PRM] = "PRM L4PER",
	[PRM_DRA7XX_PRCM_MPU_PRM_C0] = "PRM CPU0",
	[PRM_DRA7XX_PRCM_MPU_PRM_C1] = "PRM CPU1",
	[PRM_DRA7XX_EVE_PRM] = "PRM EVE",
	[PRM_DRA7XX_IPU_PRM] = "PRM IPU",
	[PRM_DRA7XX_RTC_PRM] = "PRM RTC",
	[PRM_DRA7XX_VPE_PRM] = "PRM VPE"};
