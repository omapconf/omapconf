/*
 *
 * @Component			OMAPCONF
 * @Filename			cm_dra7xx-defs.c
 * @Description			DRA7 CM Registers Definitions & Function
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


#include <cm_dra7xx-defs.h>
#include <lib.h>


reg dra7xx_dsp1_cm_core_aon_cm_dsp1_clkstctrl = {
	"CM_DSP1_CLKSTCTRL",
	DRA7XX_DSP1_CM_CORE_AON_CM_DSP1_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_dsp1_cm_core_aon_cm_dsp1_staticdep = {
	"CM_DSP1_STATICDEP",
	DRA7XX_DSP1_CM_CORE_AON_CM_DSP1_STATICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_dsp1_cm_core_aon_cm_dsp1_dynamicdep = {
	"CM_DSP1_DYNAMICDEP",
	DRA7XX_DSP1_CM_CORE_AON_CM_DSP1_DYNAMICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_dsp1_cm_core_aon_cm_dsp1_dsp1_clkctrl = {
	"CM_DSP1_DSP1_CLKCTRL",
	DRA7XX_DSP1_CM_CORE_AON_CM_DSP1_DSP1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_dsp2_cm_core_aon_cm_dsp2_clkstctrl = {
	"CM_DSP2_CLKSTCTRL",
	DRA7XX_DSP2_CM_CORE_AON_CM_DSP2_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_dsp2_cm_core_aon_cm_dsp2_staticdep = {
	"CM_DSP2_STATICDEP",
	DRA7XX_DSP2_CM_CORE_AON_CM_DSP2_STATICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_dsp2_cm_core_aon_cm_dsp2_dynamicdep = {
	"CM_DSP2_DYNAMICDEP",
	DRA7XX_DSP2_CM_CORE_AON_CM_DSP2_DYNAMICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_dsp2_cm_core_aon_cm_dsp2_dsp2_clkctrl = {
	"CM_DSP2_DSP2_CLKCTRL",
	DRA7XX_DSP2_CM_CORE_AON_CM_DSP2_DSP2_CLKCTRL,
	0xDEADBEEF,
	0};
reg *dra7xx_dsp_cm_core_aon_mod[DRA7XX_DSP_CM_CORE_AON_MOD_REGCOUNT + 1] = {
	&dra7xx_dsp1_cm_core_aon_cm_dsp1_clkstctrl,
	&dra7xx_dsp1_cm_core_aon_cm_dsp1_staticdep,
	&dra7xx_dsp1_cm_core_aon_cm_dsp1_dynamicdep,
	&dra7xx_dsp1_cm_core_aon_cm_dsp1_dsp1_clkctrl,
	&dra7xx_dsp2_cm_core_aon_cm_dsp2_clkstctrl,
	&dra7xx_dsp2_cm_core_aon_cm_dsp2_staticdep,
	&dra7xx_dsp2_cm_core_aon_cm_dsp2_dynamicdep,
	&dra7xx_dsp2_cm_core_aon_cm_dsp2_dsp2_clkctrl,
	NULL};

reg dra7xx_eve1_cm_core_aon_cm_eve1_clkstctrl = {
	"CM_EVE1_CLKSTCTRL",
	DRA7XX_EVE1_CM_CORE_AON_CM_EVE1_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_eve1_cm_core_aon_cm_eve1_staticdep = {
	"CM_EVE1_STATICDEP",
	DRA7XX_EVE1_CM_CORE_AON_CM_EVE1_STATICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_eve1_cm_core_aon_cm_eve1_eve1_clkctrl = {
	"CM_EVE1_EVE1_CLKCTRL",
	DRA7XX_EVE1_CM_CORE_AON_CM_EVE1_EVE1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_eve2_cm_core_aon_cm_eve2_clkstctrl = {
	"CM_EVE2_CLKSTCTRL",
	DRA7XX_EVE2_CM_CORE_AON_CM_EVE2_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_eve2_cm_core_aon_cm_eve2_staticdep = {
	"CM_EVE2_STATICDEP",
	DRA7XX_EVE2_CM_CORE_AON_CM_EVE2_STATICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_eve2_cm_core_aon_cm_eve2_eve2_clkctrl = {
	"CM_EVE2_EVE2_CLKCTRL",
	DRA7XX_EVE2_CM_CORE_AON_CM_EVE2_EVE2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_eve3_cm_core_aon_cm_eve3_clkstctrl = {
	"CM_EVE3_CLKSTCTRL",
	DRA7XX_EVE3_CM_CORE_AON_CM_EVE3_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_eve3_cm_core_aon_cm_eve3_staticdep = {
	"CM_EVE3_STATICDEP",
	DRA7XX_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_eve3_cm_core_aon_cm_eve3_eve3_clkctrl = {
	"CM_EVE3_EVE3_CLKCTRL",
	DRA7XX_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_eve4_cm_core_aon_cm_eve4_clkstctrl = {
	"CM_EVE4_CLKSTCTRL",
	DRA7XX_EVE4_CM_CORE_AON_CM_EVE4_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_eve4_cm_core_aon_cm_eve4_staticdep = {
	"CM_EVE4_STATICDEP",
	DRA7XX_EVE4_CM_CORE_AON_CM_EVE4_STATICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_eve4_cm_core_aon_cm_eve4_eve4_clkctrl = {
	"CM_EVE4_EVE4_CLKCTRL",
	DRA7XX_EVE4_CM_CORE_AON_CM_EVE4_EVE4_CLKCTRL,
	0xDEADBEEF,
	0};
reg *dra7xx_eve_cm_core_aon_mod[DRA7XX_EVE_CM_CORE_AON_MOD_REGCOUNT + 1] = {
	&dra7xx_eve1_cm_core_aon_cm_eve1_clkstctrl,
	&dra7xx_eve1_cm_core_aon_cm_eve1_staticdep,
	&dra7xx_eve1_cm_core_aon_cm_eve1_eve1_clkctrl,
	&dra7xx_eve2_cm_core_aon_cm_eve2_clkstctrl,
	&dra7xx_eve2_cm_core_aon_cm_eve2_staticdep,
	&dra7xx_eve2_cm_core_aon_cm_eve2_eve2_clkctrl,
	&dra7xx_eve3_cm_core_aon_cm_eve3_clkstctrl,
	&dra7xx_eve3_cm_core_aon_cm_eve3_staticdep,
	&dra7xx_eve3_cm_core_aon_cm_eve3_eve3_clkctrl,
	&dra7xx_eve4_cm_core_aon_cm_eve4_clkstctrl,
	&dra7xx_eve4_cm_core_aon_cm_eve4_staticdep,
	&dra7xx_eve4_cm_core_aon_cm_eve4_eve4_clkctrl,
	NULL};

reg dra7xx_instr_cm_core_aon_cmi_identication = {
	"CMI_IDENTICATION",
	DRA7XX_INSTR_CM_CORE_AON_CMI_IDENTICATION,
	0xDEADBEEF,
	0};
reg dra7xx_instr_cm_core_aon_cmi_sys_config = {
	"CMI_SYS_CONFIG",
	DRA7XX_INSTR_CM_CORE_AON_CMI_SYS_CONFIG,
	0xDEADBEEF,
	0};
reg dra7xx_instr_cm_core_aon_cmi_status = {
	"CMI_STATUS",
	DRA7XX_INSTR_CM_CORE_AON_CMI_STATUS,
	0xDEADBEEF,
	0};
reg dra7xx_instr_cm_core_aon_cmi_configuration = {
	"CMI_CONFIGURATION",
	DRA7XX_INSTR_CM_CORE_AON_CMI_CONFIGURATION,
	0xDEADBEEF,
	0};
reg dra7xx_instr_cm_core_aon_cmi_class_filtering = {
	"CMI_CLASS_FILTERING",
	DRA7XX_INSTR_CM_CORE_AON_CMI_CLASS_FILTERING,
	0xDEADBEEF,
	0};
reg dra7xx_instr_cm_core_aon_cmi_triggering = {
	"CMI_TRIGGERING",
	DRA7XX_INSTR_CM_CORE_AON_CMI_TRIGGERING,
	0xDEADBEEF,
	0};
reg dra7xx_instr_cm_core_aon_cmi_sampling = {
	"CMI_SAMPLING",
	DRA7XX_INSTR_CM_CORE_AON_CMI_SAMPLING,
	0xDEADBEEF,
	0};
reg *dra7xx_instr_cm_core_aon_mod[DRA7XX_INSTR_CM_CORE_AON_MOD_REGCOUNT + 1] = {
	&dra7xx_instr_cm_core_aon_cmi_identication,
	&dra7xx_instr_cm_core_aon_cmi_sys_config,
	&dra7xx_instr_cm_core_aon_cmi_status,
	&dra7xx_instr_cm_core_aon_cmi_configuration,
	&dra7xx_instr_cm_core_aon_cmi_class_filtering,
	&dra7xx_instr_cm_core_aon_cmi_triggering,
	&dra7xx_instr_cm_core_aon_cmi_sampling,
	NULL};

reg dra7xx_ipu_cm_core_aon_cm_ipu1_clkstctrl = {
	"CM_IPU1_CLKSTCTRL",
	DRA7XX_IPU_CM_CORE_AON_CM_IPU1_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_cm_core_aon_cm_ipu1_staticdep = {
	"CM_IPU1_STATICDEP",
	DRA7XX_IPU_CM_CORE_AON_CM_IPU1_STATICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_cm_core_aon_cm_ipu1_dynamicdep = {
	"CM_IPU1_DYNAMICDEP",
	DRA7XX_IPU_CM_CORE_AON_CM_IPU1_DYNAMICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_cm_core_aon_cm_ipu1_ipu1_clkctrl = {
	"CM_IPU1_IPU1_CLKCTRL",
	DRA7XX_IPU_CM_CORE_AON_CM_IPU1_IPU1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_cm_core_aon_cm_ipu_clkstctrl = {
	"CM_IPU_CLKSTCTRL",
	DRA7XX_IPU_CM_CORE_AON_CM_IPU_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_cm_core_aon_cm_ipu_mcasp1_clkctrl = {
	"CM_IPU_MCASP1_CLKCTRL",
	DRA7XX_IPU_CM_CORE_AON_CM_IPU_MCASP1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_cm_core_aon_cm_ipu_timer5_clkctrl = {
	"CM_IPU_TIMER5_CLKCTRL",
	DRA7XX_IPU_CM_CORE_AON_CM_IPU_TIMER5_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_cm_core_aon_cm_ipu_timer6_clkctrl = {
	"CM_IPU_TIMER6_CLKCTRL",
	DRA7XX_IPU_CM_CORE_AON_CM_IPU_TIMER6_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_cm_core_aon_cm_ipu_timer7_clkctrl = {
	"CM_IPU_TIMER7_CLKCTRL",
	DRA7XX_IPU_CM_CORE_AON_CM_IPU_TIMER7_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_cm_core_aon_cm_ipu_timer8_clkctrl = {
	"CM_IPU_TIMER8_CLKCTRL",
	DRA7XX_IPU_CM_CORE_AON_CM_IPU_TIMER8_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_cm_core_aon_cm_ipu_i2c5_clkctrl = {
	"CM_IPU_I2C5_CLKCTRL",
	DRA7XX_IPU_CM_CORE_AON_CM_IPU_I2C5_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_ipu_cm_core_aon_cm_ipu_uart6_clkctrl = {
	"CM_IPU_UART6_CLKCTRL",
	DRA7XX_IPU_CM_CORE_AON_CM_IPU_UART6_CLKCTRL,
	0xDEADBEEF,
	0};
reg *dra7xx_ipu_cm_core_aon_mod[DRA7XX_IPU_CM_CORE_AON_MOD_REGCOUNT + 1] = {
	&dra7xx_ipu_cm_core_aon_cm_ipu1_clkstctrl,
	&dra7xx_ipu_cm_core_aon_cm_ipu1_staticdep,
	&dra7xx_ipu_cm_core_aon_cm_ipu1_dynamicdep,
	&dra7xx_ipu_cm_core_aon_cm_ipu1_ipu1_clkctrl,
	&dra7xx_ipu_cm_core_aon_cm_ipu_clkstctrl,
	&dra7xx_ipu_cm_core_aon_cm_ipu_mcasp1_clkctrl,
	&dra7xx_ipu_cm_core_aon_cm_ipu_timer5_clkctrl,
	&dra7xx_ipu_cm_core_aon_cm_ipu_timer6_clkctrl,
	&dra7xx_ipu_cm_core_aon_cm_ipu_timer7_clkctrl,
	&dra7xx_ipu_cm_core_aon_cm_ipu_timer8_clkctrl,
	&dra7xx_ipu_cm_core_aon_cm_ipu_i2c5_clkctrl,
	&dra7xx_ipu_cm_core_aon_cm_ipu_uart6_clkctrl,
	NULL};

reg dra7xx_mpu_cm_core_aon_cm_mpu_clkstctrl = {
	"CM_MPU_CLKSTCTRL",
	DRA7XX_MPU_CM_CORE_AON_CM_MPU_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_mpu_cm_core_aon_cm_mpu_staticdep = {
	"CM_MPU_STATICDEP",
	DRA7XX_MPU_CM_CORE_AON_CM_MPU_STATICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_mpu_cm_core_aon_cm_mpu_dynamicdep = {
	"CM_MPU_DYNAMICDEP",
	DRA7XX_MPU_CM_CORE_AON_CM_MPU_DYNAMICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_mpu_cm_core_aon_cm_mpu_mpu_clkctrl = {
	"CM_MPU_MPU_CLKCTRL",
	DRA7XX_MPU_CM_CORE_AON_CM_MPU_MPU_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_mpu_cm_core_aon_cm_mpu_mpu_mpu_dbg_clkctrl = {
	"CM_MPU_MPU_MPU_DBG_CLKCTRL",
	DRA7XX_MPU_CM_CORE_AON_CM_MPU_MPU_MPU_DBG_CLKCTRL,
	0xDEADBEEF,
	0};
reg *dra7xx_mpu_cm_core_aon_mod[DRA7XX_MPU_CM_CORE_AON_MOD_REGCOUNT + 1] = {
	&dra7xx_mpu_cm_core_aon_cm_mpu_clkstctrl,
	&dra7xx_mpu_cm_core_aon_cm_mpu_staticdep,
	&dra7xx_mpu_cm_core_aon_cm_mpu_dynamicdep,
	&dra7xx_mpu_cm_core_aon_cm_mpu_mpu_clkctrl,
	&dra7xx_mpu_cm_core_aon_cm_mpu_mpu_mpu_dbg_clkctrl,
	NULL};

reg dra7xx_ocp_socket_cm_core_aon_revision_cm_core_aon = {
	"REVISION_CM_CORE_AON",
	DRA7XX_OCP_SOCKET_CM_CORE_AON_REVISION_CM_CORE_AON,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_cm_core_aon_cm_cm_core_aon_profiling_clkctrl = {
	"CM_CM_CORE_AON_PROFILING_CLKCTRL",
	DRA7XX_OCP_SOCKET_CM_CORE_AON_CM_CM_CORE_AON_PROFILING_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_cm_core_aon_cm_core_aon_debug_out = {
	"CM_CORE_AON_DEBUG_OUT",
	DRA7XX_OCP_SOCKET_CM_CORE_AON_CM_CORE_AON_DEBUG_OUT,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_cm_core_aon_cm_core_aon_debug_cfg0 = {
	"CM_CORE_AON_DEBUG_CFG0",
	DRA7XX_OCP_SOCKET_CM_CORE_AON_CM_CORE_AON_DEBUG_CFG0,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_cm_core_aon_cm_core_aon_debug_cfg1 = {
	"CM_CORE_AON_DEBUG_CFG1",
	DRA7XX_OCP_SOCKET_CM_CORE_AON_CM_CORE_AON_DEBUG_CFG1,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_cm_core_aon_cm_core_aon_debug_cfg2 = {
	"CM_CORE_AON_DEBUG_CFG2",
	DRA7XX_OCP_SOCKET_CM_CORE_AON_CM_CORE_AON_DEBUG_CFG2,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_cm_core_aon_cm_core_aon_debug_cfg3 = {
	"CM_CORE_AON_DEBUG_CFG3",
	DRA7XX_OCP_SOCKET_CM_CORE_AON_CM_CORE_AON_DEBUG_CFG3,
	0xDEADBEEF,
	0};
reg *dra7xx_ocp_socket_cm_core_aon_mod[DRA7XX_OCP_SOCKET_CM_CORE_AON_MOD_REGCOUNT + 1] = {
	&dra7xx_ocp_socket_cm_core_aon_revision_cm_core_aon,
	&dra7xx_ocp_socket_cm_core_aon_cm_cm_core_aon_profiling_clkctrl,
	&dra7xx_ocp_socket_cm_core_aon_cm_core_aon_debug_out,
	&dra7xx_ocp_socket_cm_core_aon_cm_core_aon_debug_cfg0,
	&dra7xx_ocp_socket_cm_core_aon_cm_core_aon_debug_cfg1,
	&dra7xx_ocp_socket_cm_core_aon_cm_core_aon_debug_cfg2,
	&dra7xx_ocp_socket_cm_core_aon_cm_core_aon_debug_cfg3,
	NULL};

reg dra7xx_restore_cm_core_aon_cm_clksel_core_restore = {
	"CM_CLKSEL_CORE_RESTORE",
	DRA7XX_RESTORE_CM_CORE_AON_CM_CLKSEL_CORE_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_aon_cm_div_m2_dpll_core_restore = {
	"CM_DIV_M2_DPLL_CORE_RESTORE",
	DRA7XX_RESTORE_CM_CORE_AON_CM_DIV_M2_DPLL_CORE_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_aon_cm_div_m3_dpll_core_restore = {
	"CM_DIV_M3_DPLL_CORE_RESTORE",
	DRA7XX_RESTORE_CM_CORE_AON_CM_DIV_M3_DPLL_CORE_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_aon_cm_div_h11_dpll_core_restore = {
	"CM_DIV_H11_DPLL_CORE_RESTORE",
	DRA7XX_RESTORE_CM_CORE_AON_CM_DIV_H11_DPLL_CORE_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_aon_cm_div_h12_dpll_core_restore = {
	"CM_DIV_H12_DPLL_CORE_RESTORE",
	DRA7XX_RESTORE_CM_CORE_AON_CM_DIV_H12_DPLL_CORE_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_aon_cm_div_h13_dpll_core_restore = {
	"CM_DIV_H13_DPLL_CORE_RESTORE",
	DRA7XX_RESTORE_CM_CORE_AON_CM_DIV_H13_DPLL_CORE_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_aon_cm_div_h14_dpll_core_restore = {
	"CM_DIV_H14_DPLL_CORE_RESTORE",
	DRA7XX_RESTORE_CM_CORE_AON_CM_DIV_H14_DPLL_CORE_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_aon_cm_div_h21_dpll_core_restore = {
	"CM_DIV_H21_DPLL_CORE_RESTORE",
	DRA7XX_RESTORE_CM_CORE_AON_CM_DIV_H21_DPLL_CORE_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_aon_cm_div_h22_dpll_core_restore = {
	"CM_DIV_H22_DPLL_CORE_RESTORE",
	DRA7XX_RESTORE_CM_CORE_AON_CM_DIV_H22_DPLL_CORE_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_aon_cm_div_h23_dpll_core_restore = {
	"CM_DIV_H23_DPLL_CORE_RESTORE",
	DRA7XX_RESTORE_CM_CORE_AON_CM_DIV_H23_DPLL_CORE_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_aon_cm_div_h24_dpll_core_restore = {
	"CM_DIV_H24_DPLL_CORE_RESTORE",
	DRA7XX_RESTORE_CM_CORE_AON_CM_DIV_H24_DPLL_CORE_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_aon_cm_clksel_dpll_core_restore = {
	"CM_CLKSEL_DPLL_CORE_RESTORE",
	DRA7XX_RESTORE_CM_CORE_AON_CM_CLKSEL_DPLL_CORE_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_aon_cm_ssc_deltamstep_dpll_core_restore = {
	"CM_SSC_DELTAMSTEP_DPLL_CORE_RESTORE",
	DRA7XX_RESTORE_CM_CORE_AON_CM_SSC_DELTAMSTEP_DPLL_CORE_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_aon_cm_ssc_modfreqdiv_dpll_core_restore = {
	"CM_SSC_MODFREQDIV_DPLL_CORE_RESTORE",
	DRA7XX_RESTORE_CM_CORE_AON_CM_SSC_MODFREQDIV_DPLL_CORE_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_aon_cm_clkmode_dpll_core_restore = {
	"CM_CLKMODE_DPLL_CORE_RESTORE",
	DRA7XX_RESTORE_CM_CORE_AON_CM_CLKMODE_DPLL_CORE_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_aon_cm_shadow_freq_config2_restore = {
	"CM_SHADOW_FREQ_CONFIG2_RESTORE",
	DRA7XX_RESTORE_CM_CORE_AON_CM_SHADOW_FREQ_CONFIG2_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_aon_cm_shadow_freq_config1_restore = {
	"CM_SHADOW_FREQ_CONFIG1_RESTORE",
	DRA7XX_RESTORE_CM_CORE_AON_CM_SHADOW_FREQ_CONFIG1_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_aon_cm_autoidle_dpll_core_restore = {
	"CM_AUTOIDLE_DPLL_CORE_RESTORE",
	DRA7XX_RESTORE_CM_CORE_AON_CM_AUTOIDLE_DPLL_CORE_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_aon_cm_mpu_clkstctrl_restore = {
	"CM_MPU_CLKSTCTRL_RESTORE",
	DRA7XX_RESTORE_CM_CORE_AON_CM_MPU_CLKSTCTRL_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_aon_cm_cm_core_aon_profiling_clkctrl_restore = {
	"CM_CM_CORE_AON_PROFILING_CLKCTRL_RESTORE",
	DRA7XX_RESTORE_CM_CORE_AON_CM_CM_CORE_AON_PROFILING_CLKCTRL_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_aon_cm_dyn_dep_prescal_restore = {
	"CM_DYN_DEP_PRESCAL_RESTORE",
	DRA7XX_RESTORE_CM_CORE_AON_CM_DYN_DEP_PRESCAL_RESTORE,
	0xDEADBEEF,
	0};
reg *dra7xx_restore_cm_core_aon_mod[DRA7XX_RESTORE_CM_CORE_AON_MOD_REGCOUNT + 1] = {
	&dra7xx_restore_cm_core_aon_cm_clksel_core_restore,
	&dra7xx_restore_cm_core_aon_cm_div_m2_dpll_core_restore,
	&dra7xx_restore_cm_core_aon_cm_div_m3_dpll_core_restore,
	&dra7xx_restore_cm_core_aon_cm_div_h11_dpll_core_restore,
	&dra7xx_restore_cm_core_aon_cm_div_h12_dpll_core_restore,
	&dra7xx_restore_cm_core_aon_cm_div_h13_dpll_core_restore,
	&dra7xx_restore_cm_core_aon_cm_div_h14_dpll_core_restore,
	&dra7xx_restore_cm_core_aon_cm_div_h21_dpll_core_restore,
	&dra7xx_restore_cm_core_aon_cm_div_h22_dpll_core_restore,
	&dra7xx_restore_cm_core_aon_cm_div_h23_dpll_core_restore,
	&dra7xx_restore_cm_core_aon_cm_div_h24_dpll_core_restore,
	&dra7xx_restore_cm_core_aon_cm_clksel_dpll_core_restore,
	&dra7xx_restore_cm_core_aon_cm_ssc_deltamstep_dpll_core_restore,
	&dra7xx_restore_cm_core_aon_cm_ssc_modfreqdiv_dpll_core_restore,
	&dra7xx_restore_cm_core_aon_cm_clkmode_dpll_core_restore,
	&dra7xx_restore_cm_core_aon_cm_shadow_freq_config2_restore,
	&dra7xx_restore_cm_core_aon_cm_shadow_freq_config1_restore,
	&dra7xx_restore_cm_core_aon_cm_autoidle_dpll_core_restore,
	&dra7xx_restore_cm_core_aon_cm_mpu_clkstctrl_restore,
	&dra7xx_restore_cm_core_aon_cm_cm_core_aon_profiling_clkctrl_restore,
	&dra7xx_restore_cm_core_aon_cm_dyn_dep_prescal_restore,
	NULL};

reg dra7xx_rtc_cm_core_aon_cm_rtc_clkstctrl = {
	"CM_RTC_CLKSTCTRL",
	DRA7XX_RTC_CM_CORE_AON_CM_RTC_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_rtc_cm_core_aon_cm_rtc_rtcss_clkctrl = {
	"CM_RTC_RTCSS_CLKCTRL",
	DRA7XX_RTC_CM_CORE_AON_CM_RTC_RTCSS_CLKCTRL,
	0xDEADBEEF,
	0};
reg *dra7xx_rtc_cm_core_aon_mod[DRA7XX_RTC_CM_CORE_AON_MOD_REGCOUNT + 1] = {
	&dra7xx_rtc_cm_core_aon_cm_rtc_clkstctrl,
	&dra7xx_rtc_cm_core_aon_cm_rtc_rtcss_clkctrl,
	NULL};

reg dra7xx_vpe_cm_core_aon_cm_vpe_clkstctrl = {
	"CM_VPE_CLKSTCTRL",
	DRA7XX_VPE_CM_CORE_AON_CM_VPE_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_vpe_cm_core_aon_cm_vpe_vpe_clkctrl = {
	"CM_VPE_VPE_CLKCTRL",
	DRA7XX_VPE_CM_CORE_AON_CM_VPE_VPE_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_vpe_cm_core_aon_cm_vpe_staticdep = {
	"CM_VPE_STATICDEP",
	DRA7XX_VPE_CM_CORE_AON_CM_VPE_STATICDEP,
	0xDEADBEEF,
	0};
reg *dra7xx_vpe_cm_core_aon_mod[DRA7XX_VPE_CM_CORE_AON_MOD_REGCOUNT + 1] = {
	&dra7xx_vpe_cm_core_aon_cm_vpe_clkstctrl,
	&dra7xx_vpe_cm_core_aon_cm_vpe_vpe_clkctrl,
	&dra7xx_vpe_cm_core_aon_cm_vpe_staticdep,
	NULL};

reg dra7xx_cam_cm_core_cm_cam_clkstctrl = {
	"CM_CAM_CLKSTCTRL",
	DRA7XX_CAM_CM_CORE_CM_CAM_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_cam_cm_core_cm_cam_staticdep = {
	"CM_CAM_STATICDEP",
	DRA7XX_CAM_CM_CORE_CM_CAM_STATICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_cam_cm_core_cm_cam_vip1_clkctrl = {
	"CM_CAM_VIP1_CLKCTRL",
	DRA7XX_CAM_CM_CORE_CM_CAM_VIP1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_cam_cm_core_cm_cam_vip2_clkctrl = {
	"CM_CAM_VIP2_CLKCTRL",
	DRA7XX_CAM_CM_CORE_CM_CAM_VIP2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_cam_cm_core_cm_cam_vip3_clkctrl = {
	"CM_CAM_VIP3_CLKCTRL",
	DRA7XX_CAM_CM_CORE_CM_CAM_VIP3_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_cam_cm_core_cm_cam_lvdsrx_clkctrl = {
	"CM_CAM_LVDSRX_CLKCTRL",
	DRA7XX_CAM_CM_CORE_CM_CAM_LVDSRX_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_cam_cm_core_cm_cam_csi1_clkctrl = {
	"CM_CAM_CSI1_CLKCTRL",
	DRA7XX_CAM_CM_CORE_CM_CAM_CSI1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_cam_cm_core_cm_cam_csi2_clkctrl = {
	"CM_CAM_CSI2_CLKCTRL",
	DRA7XX_CAM_CM_CORE_CM_CAM_CSI2_CLKCTRL,
	0xDEADBEEF,
	0};
reg *dra7xx_cam_cm_core_mod[DRA7XX_CAM_CM_CORE_MOD_REGCOUNT + 1] = {
	&dra7xx_cam_cm_core_cm_cam_clkstctrl,
	&dra7xx_cam_cm_core_cm_cam_staticdep,
	&dra7xx_cam_cm_core_cm_cam_vip1_clkctrl,
	&dra7xx_cam_cm_core_cm_cam_vip2_clkctrl,
	&dra7xx_cam_cm_core_cm_cam_vip3_clkctrl,
	&dra7xx_cam_cm_core_cm_cam_lvdsrx_clkctrl,
	&dra7xx_cam_cm_core_cm_cam_csi1_clkctrl,
	&dra7xx_cam_cm_core_cm_cam_csi2_clkctrl,
	NULL};

reg dra7xx_coreaon_cm_core_cm_coreaon_clkstctrl = {
	"CM_COREAON_CLKSTCTRL",
	DRA7XX_COREAON_CM_CORE_CM_COREAON_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_coreaon_cm_core_cm_coreaon_smartreflex_mpu_clkctrl = {
	"CM_COREAON_SMARTREFLEX_MPU_CLKCTRL",
	DRA7XX_COREAON_CM_CORE_CM_COREAON_SMARTREFLEX_MPU_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_coreaon_cm_core_cm_coreaon_smartreflex_core_clkctrl = {
	"CM_COREAON_SMARTREFLEX_CORE_CLKCTRL",
	DRA7XX_COREAON_CM_CORE_CM_COREAON_SMARTREFLEX_CORE_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_coreaon_cm_core_cm_coreaon_usb_phy1_core_clkctrl = {
	"CM_COREAON_USB_PHY1_CORE_CLKCTRL",
	DRA7XX_COREAON_CM_CORE_CM_COREAON_USB_PHY1_CORE_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_coreaon_cm_core_cm_coreaon_io_srcomp_clkctrl = {
	"CM_COREAON_IO_SRCOMP_CLKCTRL",
	DRA7XX_COREAON_CM_CORE_CM_COREAON_IO_SRCOMP_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_coreaon_cm_core_cm_coreaon_smartreflex_gpu_clkctrl = {
	"CM_COREAON_SMARTREFLEX_GPU_CLKCTRL",
	DRA7XX_COREAON_CM_CORE_CM_COREAON_SMARTREFLEX_GPU_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_coreaon_cm_core_cm_coreaon_smartreflex_dspeve_clkctrl = {
	"CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL",
	DRA7XX_COREAON_CM_CORE_CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_coreaon_cm_core_cm_coreaon_smartreflex_ivahd_clkctrl = {
	"CM_COREAON_SMARTREFLEX_IVAHD_CLKCTRL",
	DRA7XX_COREAON_CM_CORE_CM_COREAON_SMARTREFLEX_IVAHD_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_coreaon_cm_core_cm_coreaon_usb_phy2_core_clkctrl = {
	"CM_COREAON_USB_PHY2_CORE_CLKCTRL",
	DRA7XX_COREAON_CM_CORE_CM_COREAON_USB_PHY2_CORE_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_coreaon_cm_core_cm_coreaon_usb_phy3_core_clkctrl = {
	"CM_COREAON_USB_PHY3_CORE_CLKCTRL",
	DRA7XX_COREAON_CM_CORE_CM_COREAON_USB_PHY3_CORE_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_coreaon_cm_core_cm_coreaon_dummy_module1_clkctrl = {
	"CM_COREAON_DUMMY_MODULE1_CLKCTRL",
	DRA7XX_COREAON_CM_CORE_CM_COREAON_DUMMY_MODULE1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_coreaon_cm_core_cm_coreaon_dummy_module2_clkctrl = {
	"CM_COREAON_DUMMY_MODULE2_CLKCTRL",
	DRA7XX_COREAON_CM_CORE_CM_COREAON_DUMMY_MODULE2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_coreaon_cm_core_cm_coreaon_dummy_module3_clkctrl = {
	"CM_COREAON_DUMMY_MODULE3_CLKCTRL",
	DRA7XX_COREAON_CM_CORE_CM_COREAON_DUMMY_MODULE3_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_coreaon_cm_core_cm_coreaon_dummy_module4_clkctrl = {
	"CM_COREAON_DUMMY_MODULE4_CLKCTRL",
	DRA7XX_COREAON_CM_CORE_CM_COREAON_DUMMY_MODULE4_CLKCTRL,
	0xDEADBEEF,
	0};
reg *dra7xx_coreaon_cm_core_mod[DRA7XX_COREAON_CM_CORE_MOD_REGCOUNT + 1] = {
	&dra7xx_coreaon_cm_core_cm_coreaon_clkstctrl,
	&dra7xx_coreaon_cm_core_cm_coreaon_smartreflex_mpu_clkctrl,
	&dra7xx_coreaon_cm_core_cm_coreaon_smartreflex_core_clkctrl,
	&dra7xx_coreaon_cm_core_cm_coreaon_usb_phy1_core_clkctrl,
	&dra7xx_coreaon_cm_core_cm_coreaon_io_srcomp_clkctrl,
	&dra7xx_coreaon_cm_core_cm_coreaon_smartreflex_gpu_clkctrl,
	&dra7xx_coreaon_cm_core_cm_coreaon_smartreflex_dspeve_clkctrl,
	&dra7xx_coreaon_cm_core_cm_coreaon_smartreflex_ivahd_clkctrl,
	&dra7xx_coreaon_cm_core_cm_coreaon_usb_phy2_core_clkctrl,
	&dra7xx_coreaon_cm_core_cm_coreaon_usb_phy3_core_clkctrl,
	&dra7xx_coreaon_cm_core_cm_coreaon_dummy_module1_clkctrl,
	&dra7xx_coreaon_cm_core_cm_coreaon_dummy_module2_clkctrl,
	&dra7xx_coreaon_cm_core_cm_coreaon_dummy_module3_clkctrl,
	&dra7xx_coreaon_cm_core_cm_coreaon_dummy_module4_clkctrl,
	NULL};

reg dra7xx_core_cm_core_cm_l3main1_clkstctrl = {
	"CM_L3MAIN1_CLKSTCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3MAIN1_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3main1_dynamicdep = {
	"CM_L3MAIN1_DYNAMICDEP",
	DRA7XX_CORE_CM_CORE_CM_L3MAIN1_DYNAMICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3main1_l3_main_1_clkctrl = {
	"CM_L3MAIN1_L3_MAIN_1_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3MAIN1_L3_MAIN_1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3main1_gpmc_clkctrl = {
	"CM_L3MAIN1_GPMC_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3MAIN1_GPMC_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3main1_mmu_edma_clkctrl = {
	"CM_L3MAIN1_MMU_EDMA_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3MAIN1_MMU_EDMA_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3main1_mmu_pciess_clkctrl = {
	"CM_L3MAIN1_MMU_PCIESS_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3MAIN1_MMU_PCIESS_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3main1_ocmc_ram1_clkctrl = {
	"CM_L3MAIN1_OCMC_RAM1_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3MAIN1_OCMC_RAM1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3main1_ocmc_ram2_clkctrl = {
	"CM_L3MAIN1_OCMC_RAM2_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3MAIN1_OCMC_RAM2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3main1_ocmc_ram3_clkctrl = {
	"CM_L3MAIN1_OCMC_RAM3_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3MAIN1_OCMC_RAM3_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3main1_ocmc_rom_clkctrl = {
	"CM_L3MAIN1_OCMC_ROM_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3MAIN1_OCMC_ROM_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3main1_tpcc_clkctrl = {
	"CM_L3MAIN1_TPCC_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3MAIN1_TPCC_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3main1_tptc1_clkctrl = {
	"CM_L3MAIN1_TPTC1_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3MAIN1_TPTC1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3main1_tptc2_clkctrl = {
	"CM_L3MAIN1_TPTC2_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3MAIN1_TPTC2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3main1_vcp1_clkctrl = {
	"CM_L3MAIN1_VCP1_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3MAIN1_VCP1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3main1_vcp2_clkctrl = {
	"CM_L3MAIN1_VCP2_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3MAIN1_VCP2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3main1_spare_cme_clkctrl = {
	"CM_L3MAIN1_SPARE_CME_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3MAIN1_SPARE_CME_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3main1_spare_hdmi_clkctrl = {
	"CM_L3MAIN1_SPARE_HDMI_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3MAIN1_SPARE_HDMI_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3main1_spare_icm_clkctrl = {
	"CM_L3MAIN1_SPARE_ICM_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3MAIN1_SPARE_ICM_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3main1_spare_iva2_clkctrl = {
	"CM_L3MAIN1_SPARE_IVA2_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3MAIN1_SPARE_IVA2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3main1_spare_sata2_clkctrl = {
	"CM_L3MAIN1_SPARE_SATA2_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3MAIN1_SPARE_SATA2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3main1_spare_unknown4_clkctrl = {
	"CM_L3MAIN1_SPARE_UNKNOWN4_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3MAIN1_SPARE_UNKNOWN4_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3main1_spare_unknown5_clkctrl = {
	"CM_L3MAIN1_SPARE_UNKNOWN5_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3MAIN1_SPARE_UNKNOWN5_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3main1_spare_unknown6_clkctrl = {
	"CM_L3MAIN1_SPARE_UNKNOWN6_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3MAIN1_SPARE_UNKNOWN6_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3main1_spare_videopll1_clkctrl = {
	"CM_L3MAIN1_SPARE_VIDEOPLL1_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3MAIN1_SPARE_VIDEOPLL1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3main1_spare_videopll2_clkctrl = {
	"CM_L3MAIN1_SPARE_VIDEOPLL2_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3MAIN1_SPARE_VIDEOPLL2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3main1_spare_videopll3_clkctrl = {
	"CM_L3MAIN1_SPARE_VIDEOPLL3_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3MAIN1_SPARE_VIDEOPLL3_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_ipu2_clkstctrl = {
	"CM_IPU2_CLKSTCTRL",
	DRA7XX_CORE_CM_CORE_CM_IPU2_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_ipu2_staticdep = {
	"CM_IPU2_STATICDEP",
	DRA7XX_CORE_CM_CORE_CM_IPU2_STATICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_ipu2_dynamicdep = {
	"CM_IPU2_DYNAMICDEP",
	DRA7XX_CORE_CM_CORE_CM_IPU2_DYNAMICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_ipu2_ipu2_clkctrl = {
	"CM_IPU2_IPU2_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_IPU2_IPU2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_dma_clkstctrl = {
	"CM_DMA_CLKSTCTRL",
	DRA7XX_CORE_CM_CORE_CM_DMA_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_dma_staticdep = {
	"CM_DMA_STATICDEP",
	DRA7XX_CORE_CM_CORE_CM_DMA_STATICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_dma_dynamicdep = {
	"CM_DMA_DYNAMICDEP",
	DRA7XX_CORE_CM_CORE_CM_DMA_DYNAMICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_dma_dma_system_clkctrl = {
	"CM_DMA_DMA_SYSTEM_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_DMA_DMA_SYSTEM_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_emif_clkstctrl = {
	"CM_EMIF_CLKSTCTRL",
	DRA7XX_CORE_CM_CORE_CM_EMIF_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_emif_dmm_clkctrl = {
	"CM_EMIF_DMM_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_EMIF_DMM_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_emif_emif_ocp_fw_clkctrl = {
	"CM_EMIF_EMIF_OCP_FW_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_EMIF_EMIF_OCP_FW_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_emif_emif1_clkctrl = {
	"CM_EMIF_EMIF1_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_EMIF_EMIF1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_emif_emif2_clkctrl = {
	"CM_EMIF_EMIF2_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_EMIF_EMIF2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_emif_emif_dll_clkctrl = {
	"CM_EMIF_EMIF_DLL_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_EMIF_EMIF_DLL_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_atl_atl_clkctrl = {
	"CM_ATL_ATL_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_ATL_ATL_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_atl_clkstctrl = {
	"CM_ATL_CLKSTCTRL",
	DRA7XX_CORE_CM_CORE_CM_ATL_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l4cfg_clkstctrl = {
	"CM_L4CFG_CLKSTCTRL",
	DRA7XX_CORE_CM_CORE_CM_L4CFG_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l4cfg_dynamicdep = {
	"CM_L4CFG_DYNAMICDEP",
	DRA7XX_CORE_CM_CORE_CM_L4CFG_DYNAMICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l4cfg_l4_cfg_clkctrl = {
	"CM_L4CFG_L4_CFG_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L4CFG_L4_CFG_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l4cfg_spinlock_clkctrl = {
	"CM_L4CFG_SPINLOCK_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L4CFG_SPINLOCK_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l4cfg_mailbox1_clkctrl = {
	"CM_L4CFG_MAILBOX1_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L4CFG_MAILBOX1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l4cfg_sar_rom_clkctrl = {
	"CM_L4CFG_SAR_ROM_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L4CFG_SAR_ROM_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l4cfg_ocp2scp2_clkctrl = {
	"CM_L4CFG_OCP2SCP2_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L4CFG_OCP2SCP2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l4cfg_mailbox2_clkctrl = {
	"CM_L4CFG_MAILBOX2_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L4CFG_MAILBOX2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l4cfg_mailbox3_clkctrl = {
	"CM_L4CFG_MAILBOX3_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L4CFG_MAILBOX3_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l4cfg_mailbox4_clkctrl = {
	"CM_L4CFG_MAILBOX4_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L4CFG_MAILBOX4_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l4cfg_mailbox5_clkctrl = {
	"CM_L4CFG_MAILBOX5_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L4CFG_MAILBOX5_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l4cfg_mailbox6_clkctrl = {
	"CM_L4CFG_MAILBOX6_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L4CFG_MAILBOX6_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l4cfg_mailbox7_clkctrl = {
	"CM_L4CFG_MAILBOX7_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L4CFG_MAILBOX7_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l4cfg_mailbox8_clkctrl = {
	"CM_L4CFG_MAILBOX8_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L4CFG_MAILBOX8_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l4cfg_mailbox9_clkctrl = {
	"CM_L4CFG_MAILBOX9_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L4CFG_MAILBOX9_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l4cfg_mailbox10_clkctrl = {
	"CM_L4CFG_MAILBOX10_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L4CFG_MAILBOX10_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l4cfg_mailbox11_clkctrl = {
	"CM_L4CFG_MAILBOX11_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L4CFG_MAILBOX11_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l4cfg_mailbox12_clkctrl = {
	"CM_L4CFG_MAILBOX12_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L4CFG_MAILBOX12_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l4cfg_mailbox13_clkctrl = {
	"CM_L4CFG_MAILBOX13_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L4CFG_MAILBOX13_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l4cfg_spare_smartreflex_rtc_clkctrl = {
	"CM_L4CFG_SPARE_SMARTREFLEX_RTC_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L4CFG_SPARE_SMARTREFLEX_RTC_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l4cfg_spare_smartreflex_sdram_clkctrl = {
	"CM_L4CFG_SPARE_SMARTREFLEX_SDRAM_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L4CFG_SPARE_SMARTREFLEX_SDRAM_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l4cfg_spare_smartreflex_wkup_clkctrl = {
	"CM_L4CFG_SPARE_SMARTREFLEX_WKUP_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L4CFG_SPARE_SMARTREFLEX_WKUP_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l4cfg_io_delay_block_clkctrl = {
	"CM_L4CFG_IO_DELAY_BLOCK_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L4CFG_IO_DELAY_BLOCK_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3instr_clkstctrl = {
	"CM_L3INSTR_CLKSTCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3INSTR_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3instr_l3_main_2_clkctrl = {
	"CM_L3INSTR_L3_MAIN_2_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3INSTR_L3_MAIN_2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3instr_l3_instr_clkctrl = {
	"CM_L3INSTR_L3_INSTR_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3INSTR_L3_INSTR_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3instr_ocp_wp_noc_clkctrl = {
	"CM_L3INSTR_OCP_WP_NOC_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3INSTR_OCP_WP_NOC_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3instr_dll_aging_clkctrl = {
	"CM_L3INSTR_DLL_AGING_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3INSTR_DLL_AGING_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_core_cm_core_cm_l3instr_ctrl_module_bandgap_clkctrl = {
	"CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL",
	DRA7XX_CORE_CM_CORE_CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL,
	0xDEADBEEF,
	0};
reg *dra7xx_core_cm_core_mod[DRA7XX_CORE_CM_CORE_MOD_REGCOUNT + 1] = {
	&dra7xx_core_cm_core_cm_l3main1_clkstctrl,
	&dra7xx_core_cm_core_cm_l3main1_dynamicdep,
	&dra7xx_core_cm_core_cm_l3main1_l3_main_1_clkctrl,
	&dra7xx_core_cm_core_cm_l3main1_gpmc_clkctrl,
	&dra7xx_core_cm_core_cm_l3main1_mmu_edma_clkctrl,
	&dra7xx_core_cm_core_cm_l3main1_mmu_pciess_clkctrl,
	&dra7xx_core_cm_core_cm_l3main1_ocmc_ram1_clkctrl,
	&dra7xx_core_cm_core_cm_l3main1_ocmc_ram2_clkctrl,
	&dra7xx_core_cm_core_cm_l3main1_ocmc_ram3_clkctrl,
	&dra7xx_core_cm_core_cm_l3main1_ocmc_rom_clkctrl,
	&dra7xx_core_cm_core_cm_l3main1_tpcc_clkctrl,
	&dra7xx_core_cm_core_cm_l3main1_tptc1_clkctrl,
	&dra7xx_core_cm_core_cm_l3main1_tptc2_clkctrl,
	&dra7xx_core_cm_core_cm_l3main1_vcp1_clkctrl,
	&dra7xx_core_cm_core_cm_l3main1_vcp2_clkctrl,
	&dra7xx_core_cm_core_cm_l3main1_spare_cme_clkctrl,
	&dra7xx_core_cm_core_cm_l3main1_spare_hdmi_clkctrl,
	&dra7xx_core_cm_core_cm_l3main1_spare_icm_clkctrl,
	&dra7xx_core_cm_core_cm_l3main1_spare_iva2_clkctrl,
	&dra7xx_core_cm_core_cm_l3main1_spare_sata2_clkctrl,
	&dra7xx_core_cm_core_cm_l3main1_spare_unknown4_clkctrl,
	&dra7xx_core_cm_core_cm_l3main1_spare_unknown5_clkctrl,
	&dra7xx_core_cm_core_cm_l3main1_spare_unknown6_clkctrl,
	&dra7xx_core_cm_core_cm_l3main1_spare_videopll1_clkctrl,
	&dra7xx_core_cm_core_cm_l3main1_spare_videopll2_clkctrl,
	&dra7xx_core_cm_core_cm_l3main1_spare_videopll3_clkctrl,
	&dra7xx_core_cm_core_cm_ipu2_clkstctrl,
	&dra7xx_core_cm_core_cm_ipu2_staticdep,
	&dra7xx_core_cm_core_cm_ipu2_dynamicdep,
	&dra7xx_core_cm_core_cm_ipu2_ipu2_clkctrl,
	&dra7xx_core_cm_core_cm_dma_clkstctrl,
	&dra7xx_core_cm_core_cm_dma_staticdep,
	&dra7xx_core_cm_core_cm_dma_dynamicdep,
	&dra7xx_core_cm_core_cm_dma_dma_system_clkctrl,
	&dra7xx_core_cm_core_cm_emif_clkstctrl,
	&dra7xx_core_cm_core_cm_emif_dmm_clkctrl,
	&dra7xx_core_cm_core_cm_emif_emif_ocp_fw_clkctrl,
	&dra7xx_core_cm_core_cm_emif_emif1_clkctrl,
	&dra7xx_core_cm_core_cm_emif_emif2_clkctrl,
	&dra7xx_core_cm_core_cm_emif_emif_dll_clkctrl,
	&dra7xx_core_cm_core_cm_atl_atl_clkctrl,
	&dra7xx_core_cm_core_cm_atl_clkstctrl,
	&dra7xx_core_cm_core_cm_l4cfg_clkstctrl,
	&dra7xx_core_cm_core_cm_l4cfg_dynamicdep,
	&dra7xx_core_cm_core_cm_l4cfg_l4_cfg_clkctrl,
	&dra7xx_core_cm_core_cm_l4cfg_spinlock_clkctrl,
	&dra7xx_core_cm_core_cm_l4cfg_mailbox1_clkctrl,
	&dra7xx_core_cm_core_cm_l4cfg_sar_rom_clkctrl,
	&dra7xx_core_cm_core_cm_l4cfg_ocp2scp2_clkctrl,
	&dra7xx_core_cm_core_cm_l4cfg_mailbox2_clkctrl,
	&dra7xx_core_cm_core_cm_l4cfg_mailbox3_clkctrl,
	&dra7xx_core_cm_core_cm_l4cfg_mailbox4_clkctrl,
	&dra7xx_core_cm_core_cm_l4cfg_mailbox5_clkctrl,
	&dra7xx_core_cm_core_cm_l4cfg_mailbox6_clkctrl,
	&dra7xx_core_cm_core_cm_l4cfg_mailbox7_clkctrl,
	&dra7xx_core_cm_core_cm_l4cfg_mailbox8_clkctrl,
	&dra7xx_core_cm_core_cm_l4cfg_mailbox9_clkctrl,
	&dra7xx_core_cm_core_cm_l4cfg_mailbox10_clkctrl,
	&dra7xx_core_cm_core_cm_l4cfg_mailbox11_clkctrl,
	&dra7xx_core_cm_core_cm_l4cfg_mailbox12_clkctrl,
	&dra7xx_core_cm_core_cm_l4cfg_mailbox13_clkctrl,
	&dra7xx_core_cm_core_cm_l4cfg_spare_smartreflex_rtc_clkctrl,
	&dra7xx_core_cm_core_cm_l4cfg_spare_smartreflex_sdram_clkctrl,
	&dra7xx_core_cm_core_cm_l4cfg_spare_smartreflex_wkup_clkctrl,
	&dra7xx_core_cm_core_cm_l4cfg_io_delay_block_clkctrl,
	&dra7xx_core_cm_core_cm_l3instr_clkstctrl,
	&dra7xx_core_cm_core_cm_l3instr_l3_main_2_clkctrl,
	&dra7xx_core_cm_core_cm_l3instr_l3_instr_clkctrl,
	&dra7xx_core_cm_core_cm_l3instr_ocp_wp_noc_clkctrl,
	&dra7xx_core_cm_core_cm_l3instr_dll_aging_clkctrl,
	&dra7xx_core_cm_core_cm_l3instr_ctrl_module_bandgap_clkctrl,
	NULL};

reg dra7xx_custefuse_cm_core_cm_custefuse_clkstctrl = {
	"CM_CUSTEFUSE_CLKSTCTRL",
	DRA7XX_CUSTEFUSE_CM_CORE_CM_CUSTEFUSE_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_custefuse_cm_core_cm_custefuse_efuse_ctrl_cust_clkctrl = {
	"CM_CUSTEFUSE_EFUSE_CTRL_CUST_CLKCTRL",
	DRA7XX_CUSTEFUSE_CM_CORE_CM_CUSTEFUSE_EFUSE_CTRL_CUST_CLKCTRL,
	0xDEADBEEF,
	0};
reg *dra7xx_custefuse_cm_core_mod[DRA7XX_CUSTEFUSE_CM_CORE_MOD_REGCOUNT + 1] = {
	&dra7xx_custefuse_cm_core_cm_custefuse_clkstctrl,
	&dra7xx_custefuse_cm_core_cm_custefuse_efuse_ctrl_cust_clkctrl,
	NULL};

reg dra7xx_dss_cm_core_cm_dss_clkstctrl = {
	"CM_DSS_CLKSTCTRL",
	DRA7XX_DSS_CM_CORE_CM_DSS_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_dss_cm_core_cm_dss_staticdep = {
	"CM_DSS_STATICDEP",
	DRA7XX_DSS_CM_CORE_CM_DSS_STATICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_dss_cm_core_cm_dss_dynamicdep = {
	"CM_DSS_DYNAMICDEP",
	DRA7XX_DSS_CM_CORE_CM_DSS_DYNAMICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_dss_cm_core_cm_dss_dss_clkctrl = {
	"CM_DSS_DSS_CLKCTRL",
	DRA7XX_DSS_CM_CORE_CM_DSS_DSS_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_dss_cm_core_cm_dss_bb2d_clkctrl = {
	"CM_DSS_BB2D_CLKCTRL",
	DRA7XX_DSS_CM_CORE_CM_DSS_BB2D_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_dss_cm_core_cm_dss_sdvenc_clkctrl = {
	"CM_DSS_SDVENC_CLKCTRL",
	DRA7XX_DSS_CM_CORE_CM_DSS_SDVENC_CLKCTRL,
	0xDEADBEEF,
	0};
reg *dra7xx_dss_cm_core_mod[DRA7XX_DSS_CM_CORE_MOD_REGCOUNT + 1] = {
	&dra7xx_dss_cm_core_cm_dss_clkstctrl,
	&dra7xx_dss_cm_core_cm_dss_staticdep,
	&dra7xx_dss_cm_core_cm_dss_dynamicdep,
	&dra7xx_dss_cm_core_cm_dss_dss_clkctrl,
	&dra7xx_dss_cm_core_cm_dss_bb2d_clkctrl,
	&dra7xx_dss_cm_core_cm_dss_sdvenc_clkctrl,
	NULL};

reg dra7xx_gpu_cm_core_cm_gpu_clkstctrl = {
	"CM_GPU_CLKSTCTRL",
	DRA7XX_GPU_CM_CORE_CM_GPU_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_gpu_cm_core_cm_gpu_staticdep = {
	"CM_GPU_STATICDEP",
	DRA7XX_GPU_CM_CORE_CM_GPU_STATICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_gpu_cm_core_cm_gpu_dynamicdep = {
	"CM_GPU_DYNAMICDEP",
	DRA7XX_GPU_CM_CORE_CM_GPU_DYNAMICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_gpu_cm_core_cm_gpu_gpu_clkctrl = {
	"CM_GPU_GPU_CLKCTRL",
	DRA7XX_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL,
	0xDEADBEEF,
	0};
reg *dra7xx_gpu_cm_core_mod[DRA7XX_GPU_CM_CORE_MOD_REGCOUNT + 1] = {
	&dra7xx_gpu_cm_core_cm_gpu_clkstctrl,
	&dra7xx_gpu_cm_core_cm_gpu_staticdep,
	&dra7xx_gpu_cm_core_cm_gpu_dynamicdep,
	&dra7xx_gpu_cm_core_cm_gpu_gpu_clkctrl,
	NULL};

reg dra7xx_iva_cm_core_cm_iva_clkstctrl = {
	"CM_IVA_CLKSTCTRL",
	DRA7XX_IVA_CM_CORE_CM_IVA_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_iva_cm_core_cm_iva_staticdep = {
	"CM_IVA_STATICDEP",
	DRA7XX_IVA_CM_CORE_CM_IVA_STATICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_iva_cm_core_cm_iva_dynamicdep = {
	"CM_IVA_DYNAMICDEP",
	DRA7XX_IVA_CM_CORE_CM_IVA_DYNAMICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_iva_cm_core_cm_iva_iva_clkctrl = {
	"CM_IVA_IVA_CLKCTRL",
	DRA7XX_IVA_CM_CORE_CM_IVA_IVA_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_iva_cm_core_cm_iva_sl2_clkctrl = {
	"CM_IVA_SL2_CLKCTRL",
	DRA7XX_IVA_CM_CORE_CM_IVA_SL2_CLKCTRL,
	0xDEADBEEF,
	0};
reg *dra7xx_iva_cm_core_mod[DRA7XX_IVA_CM_CORE_MOD_REGCOUNT + 1] = {
	&dra7xx_iva_cm_core_cm_iva_clkstctrl,
	&dra7xx_iva_cm_core_cm_iva_staticdep,
	&dra7xx_iva_cm_core_cm_iva_dynamicdep,
	&dra7xx_iva_cm_core_cm_iva_iva_clkctrl,
	&dra7xx_iva_cm_core_cm_iva_sl2_clkctrl,
	NULL};

reg dra7xx_l3init_cm_core_cm_l3init_clkstctrl = {
	"CM_L3INIT_CLKSTCTRL",
	DRA7XX_L3INIT_CM_CORE_CM_L3INIT_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_cm_core_cm_l3init_staticdep = {
	"CM_L3INIT_STATICDEP",
	DRA7XX_L3INIT_CM_CORE_CM_L3INIT_STATICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_cm_core_cm_l3init_dynamicdep = {
	"CM_L3INIT_DYNAMICDEP",
	DRA7XX_L3INIT_CM_CORE_CM_L3INIT_DYNAMICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_cm_core_cm_l3init_mmc1_clkctrl = {
	"CM_L3INIT_MMC1_CLKCTRL",
	DRA7XX_L3INIT_CM_CORE_CM_L3INIT_MMC1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_cm_core_cm_l3init_mmc2_clkctrl = {
	"CM_L3INIT_MMC2_CLKCTRL",
	DRA7XX_L3INIT_CM_CORE_CM_L3INIT_MMC2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_cm_core_cm_l3init_usb_otg_ss2_clkctrl = {
	"CM_L3INIT_USB_OTG_SS2_CLKCTRL",
	DRA7XX_L3INIT_CM_CORE_CM_L3INIT_USB_OTG_SS2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_cm_core_cm_l3init_usb_otg_ss3_clkctrl = {
	"CM_L3INIT_USB_OTG_SS3_CLKCTRL",
	DRA7XX_L3INIT_CM_CORE_CM_L3INIT_USB_OTG_SS3_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_cm_core_cm_l3init_usb_otg_ss4_clkctrl = {
	"CM_L3INIT_USB_OTG_SS4_CLKCTRL",
	DRA7XX_L3INIT_CM_CORE_CM_L3INIT_USB_OTG_SS4_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_cm_core_cm_l3init_mlb_ss_clkctrl = {
	"CM_L3INIT_MLB_SS_CLKCTRL",
	DRA7XX_L3INIT_CM_CORE_CM_L3INIT_MLB_SS_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_cm_core_cm_l3init_ieee1500_2_ocp_clkctrl = {
	"CM_L3INIT_IEEE1500_2_OCP_CLKCTRL",
	DRA7XX_L3INIT_CM_CORE_CM_L3INIT_IEEE1500_2_OCP_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_cm_core_cm_l3init_sata_clkctrl = {
	"CM_L3INIT_SATA_CLKCTRL",
	DRA7XX_L3INIT_CM_CORE_CM_L3INIT_SATA_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_cm_core_cm_pcie_clkstctrl = {
	"CM_PCIE_CLKSTCTRL",
	DRA7XX_L3INIT_CM_CORE_CM_PCIE_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_cm_core_cm_pcie_staticdep = {
	"CM_PCIE_STATICDEP",
	DRA7XX_L3INIT_CM_CORE_CM_PCIE_STATICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_cm_core_cm_pcie_pciess1_clkctrl = {
	"CM_PCIE_PCIESS1_CLKCTRL",
	DRA7XX_L3INIT_CM_CORE_CM_PCIE_PCIESS1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_cm_core_cm_pcie_pciess2_clkctrl = {
	"CM_PCIE_PCIESS2_CLKCTRL",
	DRA7XX_L3INIT_CM_CORE_CM_PCIE_PCIESS2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_cm_core_cm_gmac_clkstctrl = {
	"CM_GMAC_CLKSTCTRL",
	DRA7XX_L3INIT_CM_CORE_CM_GMAC_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_cm_core_cm_gmac_staticdep = {
	"CM_GMAC_STATICDEP",
	DRA7XX_L3INIT_CM_CORE_CM_GMAC_STATICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_cm_core_cm_gmac_dynamicdep = {
	"CM_GMAC_DYNAMICDEP",
	DRA7XX_L3INIT_CM_CORE_CM_GMAC_DYNAMICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_cm_core_cm_gmac_gmac_clkctrl = {
	"CM_GMAC_GMAC_CLKCTRL",
	DRA7XX_L3INIT_CM_CORE_CM_GMAC_GMAC_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_cm_core_cm_l3init_ocp2scp1_clkctrl = {
	"CM_L3INIT_OCP2SCP1_CLKCTRL",
	DRA7XX_L3INIT_CM_CORE_CM_L3INIT_OCP2SCP1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_cm_core_cm_l3init_ocp2scp3_clkctrl = {
	"CM_L3INIT_OCP2SCP3_CLKCTRL",
	DRA7XX_L3INIT_CM_CORE_CM_L3INIT_OCP2SCP3_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l3init_cm_core_cm_l3init_usb_otg_ss1_clkctrl = {
	"CM_L3INIT_USB_OTG_SS1_CLKCTRL",
	DRA7XX_L3INIT_CM_CORE_CM_L3INIT_USB_OTG_SS1_CLKCTRL,
	0xDEADBEEF,
	0};
reg *dra7xx_l3init_cm_core_mod[DRA7XX_L3INIT_CM_CORE_MOD_REGCOUNT + 1] = {
	&dra7xx_l3init_cm_core_cm_l3init_clkstctrl,
	&dra7xx_l3init_cm_core_cm_l3init_staticdep,
	&dra7xx_l3init_cm_core_cm_l3init_dynamicdep,
	&dra7xx_l3init_cm_core_cm_l3init_mmc1_clkctrl,
	&dra7xx_l3init_cm_core_cm_l3init_mmc2_clkctrl,
	&dra7xx_l3init_cm_core_cm_l3init_usb_otg_ss2_clkctrl,
	&dra7xx_l3init_cm_core_cm_l3init_usb_otg_ss3_clkctrl,
	&dra7xx_l3init_cm_core_cm_l3init_usb_otg_ss4_clkctrl,
	&dra7xx_l3init_cm_core_cm_l3init_mlb_ss_clkctrl,
	&dra7xx_l3init_cm_core_cm_l3init_ieee1500_2_ocp_clkctrl,
	&dra7xx_l3init_cm_core_cm_l3init_sata_clkctrl,
	&dra7xx_l3init_cm_core_cm_pcie_clkstctrl,
	&dra7xx_l3init_cm_core_cm_pcie_staticdep,
	&dra7xx_l3init_cm_core_cm_pcie_pciess1_clkctrl,
	&dra7xx_l3init_cm_core_cm_pcie_pciess2_clkctrl,
	&dra7xx_l3init_cm_core_cm_gmac_clkstctrl,
	&dra7xx_l3init_cm_core_cm_gmac_staticdep,
	&dra7xx_l3init_cm_core_cm_gmac_dynamicdep,
	&dra7xx_l3init_cm_core_cm_gmac_gmac_clkctrl,
	&dra7xx_l3init_cm_core_cm_l3init_ocp2scp1_clkctrl,
	&dra7xx_l3init_cm_core_cm_l3init_ocp2scp3_clkctrl,
	&dra7xx_l3init_cm_core_cm_l3init_usb_otg_ss1_clkctrl,
	NULL};

reg dra7xx_l4per_cm_core_cm_l4per_clkstctrl = {
	"CM_L4PER_CLKSTCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_dynamicdep = {
	"CM_L4PER_DYNAMICDEP",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_DYNAMICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per2_l4_per2_clkctrl = {
	"CM_L4PER2_L4_PER2_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER2_L4_PER2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per3_l4_per3_clkctrl = {
	"CM_L4PER3_L4_PER3_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER3_L4_PER3_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per2_pruss1_clkctrl = {
	"CM_L4PER2_PRUSS1_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER2_PRUSS1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per2_pruss2_clkctrl = {
	"CM_L4PER2_PRUSS2_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER2_PRUSS2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_timer10_clkctrl = {
	"CM_L4PER_TIMER10_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_TIMER10_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_timer11_clkctrl = {
	"CM_L4PER_TIMER11_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_TIMER11_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_timer2_clkctrl = {
	"CM_L4PER_TIMER2_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_TIMER2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_timer3_clkctrl = {
	"CM_L4PER_TIMER3_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_TIMER3_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_timer4_clkctrl = {
	"CM_L4PER_TIMER4_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_TIMER4_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_timer9_clkctrl = {
	"CM_L4PER_TIMER9_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_TIMER9_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_elm_clkctrl = {
	"CM_L4PER_ELM_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_ELM_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_gpio2_clkctrl = {
	"CM_L4PER_GPIO2_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_GPIO2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_gpio3_clkctrl = {
	"CM_L4PER_GPIO3_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_GPIO3_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_gpio4_clkctrl = {
	"CM_L4PER_GPIO4_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_GPIO4_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_gpio5_clkctrl = {
	"CM_L4PER_GPIO5_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_GPIO5_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_gpio6_clkctrl = {
	"CM_L4PER_GPIO6_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_GPIO6_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_hdq1w_clkctrl = {
	"CM_L4PER_HDQ1W_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_HDQ1W_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per2_pwmss2_clkctrl = {
	"CM_L4PER2_PWMSS2_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER2_PWMSS2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per2_pwmss3_clkctrl = {
	"CM_L4PER2_PWMSS3_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER2_PWMSS3_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_i2c1_clkctrl = {
	"CM_L4PER_I2C1_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_I2C1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_i2c2_clkctrl = {
	"CM_L4PER_I2C2_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_I2C2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_i2c3_clkctrl = {
	"CM_L4PER_I2C3_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_I2C3_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_i2c4_clkctrl = {
	"CM_L4PER_I2C4_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_I2C4_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_l4_per1_clkctrl = {
	"CM_L4PER_L4_PER1_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_L4_PER1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per2_pwmss1_clkctrl = {
	"CM_L4PER2_PWMSS1_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER2_PWMSS1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per3_timer13_clkctrl = {
	"CM_L4PER3_TIMER13_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER3_TIMER13_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per3_timer14_clkctrl = {
	"CM_L4PER3_TIMER14_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER3_TIMER14_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per3_timer15_clkctrl = {
	"CM_L4PER3_TIMER15_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER3_TIMER15_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_mcspi1_clkctrl = {
	"CM_L4PER_MCSPI1_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_MCSPI1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_mcspi2_clkctrl = {
	"CM_L4PER_MCSPI2_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_MCSPI2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_mcspi3_clkctrl = {
	"CM_L4PER_MCSPI3_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_MCSPI3_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_mcspi4_clkctrl = {
	"CM_L4PER_MCSPI4_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_MCSPI4_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_gpio7_clkctrl = {
	"CM_L4PER_GPIO7_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_GPIO7_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_gpio8_clkctrl = {
	"CM_L4PER_GPIO8_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_GPIO8_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_mmc3_clkctrl = {
	"CM_L4PER_MMC3_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_MMC3_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_mmc4_clkctrl = {
	"CM_L4PER_MMC4_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_MMC4_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per3_timer16_clkctrl = {
	"CM_L4PER3_TIMER16_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER3_TIMER16_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per2_qspi_clkctrl = {
	"CM_L4PER2_QSPI_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER2_QSPI_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_uart1_clkctrl = {
	"CM_L4PER_UART1_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_UART1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_uart2_clkctrl = {
	"CM_L4PER_UART2_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_UART2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_uart3_clkctrl = {
	"CM_L4PER_UART3_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_UART3_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_uart4_clkctrl = {
	"CM_L4PER_UART4_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_UART4_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per2_mcasp2_clkctrl = {
	"CM_L4PER2_MCASP2_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER2_MCASP2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per2_mcasp3_clkctrl = {
	"CM_L4PER2_MCASP3_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER2_MCASP3_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per_uart5_clkctrl = {
	"CM_L4PER_UART5_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER_UART5_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per2_mcasp5_clkctrl = {
	"CM_L4PER2_MCASP5_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER2_MCASP5_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4sec_clkstctrl = {
	"CM_L4SEC_CLKSTCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4SEC_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4sec_staticdep = {
	"CM_L4SEC_STATICDEP",
	DRA7XX_L4PER_CM_CORE_CM_L4SEC_STATICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4sec_dynamicdep = {
	"CM_L4SEC_DYNAMICDEP",
	DRA7XX_L4PER_CM_CORE_CM_L4SEC_DYNAMICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per2_mcasp8_clkctrl = {
	"CM_L4PER2_MCASP8_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER2_MCASP8_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per2_mcasp4_clkctrl = {
	"CM_L4PER2_MCASP4_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER2_MCASP4_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4sec_aes1_clkctrl = {
	"CM_L4SEC_AES1_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4SEC_AES1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4sec_aes2_clkctrl = {
	"CM_L4SEC_AES2_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4SEC_AES2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4sec_des3des_clkctrl = {
	"CM_L4SEC_DES3DES_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4SEC_DES3DES_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4sec_fpka_clkctrl = {
	"CM_L4SEC_FPKA_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4SEC_FPKA_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4sec_rng_clkctrl = {
	"CM_L4SEC_RNG_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4SEC_RNG_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4sec_sha2md51_clkctrl = {
	"CM_L4SEC_SHA2MD51_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4SEC_SHA2MD51_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per2_uart7_clkctrl = {
	"CM_L4PER2_UART7_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER2_UART7_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4sec_dma_crypto_clkctrl = {
	"CM_L4SEC_DMA_CRYPTO_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4SEC_DMA_CRYPTO_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per2_uart8_clkctrl = {
	"CM_L4PER2_UART8_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER2_UART8_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per2_uart9_clkctrl = {
	"CM_L4PER2_UART9_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER2_UART9_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per2_dcan2_clkctrl = {
	"CM_L4PER2_DCAN2_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER2_DCAN2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4sec_sha2md52_clkctrl = {
	"CM_L4SEC_SHA2MD52_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4SEC_SHA2MD52_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per2_clkstctrl = {
	"CM_L4PER2_CLKSTCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER2_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per2_dynamicdep = {
	"CM_L4PER2_DYNAMICDEP",
	DRA7XX_L4PER_CM_CORE_CM_L4PER2_DYNAMICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per2_mcasp6_clkctrl = {
	"CM_L4PER2_MCASP6_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER2_MCASP6_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per2_mcasp7_clkctrl = {
	"CM_L4PER2_MCASP7_CLKCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER2_MCASP7_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per2_staticdep = {
	"CM_L4PER2_STATICDEP",
	DRA7XX_L4PER_CM_CORE_CM_L4PER2_STATICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per3_clkstctrl = {
	"CM_L4PER3_CLKSTCTRL",
	DRA7XX_L4PER_CM_CORE_CM_L4PER3_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_l4per_cm_core_cm_l4per3_dynamicdep = {
	"CM_L4PER3_DYNAMICDEP",
	DRA7XX_L4PER_CM_CORE_CM_L4PER3_DYNAMICDEP,
	0xDEADBEEF,
	0};
reg *dra7xx_l4per_cm_core_mod[DRA7XX_L4PER_CM_CORE_MOD_REGCOUNT + 1] = {
	&dra7xx_l4per_cm_core_cm_l4per_clkstctrl,
	&dra7xx_l4per_cm_core_cm_l4per_dynamicdep,
	&dra7xx_l4per_cm_core_cm_l4per2_l4_per2_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per3_l4_per3_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per2_pruss1_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per2_pruss2_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_timer10_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_timer11_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_timer2_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_timer3_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_timer4_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_timer9_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_elm_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_gpio2_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_gpio3_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_gpio4_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_gpio5_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_gpio6_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_hdq1w_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per2_pwmss2_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per2_pwmss3_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_i2c1_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_i2c2_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_i2c3_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_i2c4_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_l4_per1_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per2_pwmss1_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per3_timer13_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per3_timer14_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per3_timer15_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_mcspi1_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_mcspi2_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_mcspi3_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_mcspi4_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_gpio7_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_gpio8_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_mmc3_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_mmc4_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per3_timer16_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per2_qspi_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_uart1_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_uart2_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_uart3_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_uart4_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per2_mcasp2_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per2_mcasp3_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per_uart5_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per2_mcasp5_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4sec_clkstctrl,
	&dra7xx_l4per_cm_core_cm_l4sec_staticdep,
	&dra7xx_l4per_cm_core_cm_l4sec_dynamicdep,
	&dra7xx_l4per_cm_core_cm_l4per2_mcasp8_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per2_mcasp4_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4sec_aes1_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4sec_aes2_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4sec_des3des_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4sec_fpka_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4sec_rng_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4sec_sha2md51_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per2_uart7_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4sec_dma_crypto_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per2_uart8_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per2_uart9_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per2_dcan2_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4sec_sha2md52_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per2_clkstctrl,
	&dra7xx_l4per_cm_core_cm_l4per2_dynamicdep,
	&dra7xx_l4per_cm_core_cm_l4per2_mcasp6_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per2_mcasp7_clkctrl,
	&dra7xx_l4per_cm_core_cm_l4per2_staticdep,
	&dra7xx_l4per_cm_core_cm_l4per3_clkstctrl,
	&dra7xx_l4per_cm_core_cm_l4per3_dynamicdep,
	NULL};

reg dra7xx_ocp_socket_cm_core_revision_cm_core = {
	"REVISION_CM_CORE",
	DRA7XX_OCP_SOCKET_CM_CORE_REVISION_CM_CORE,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_cm_core_cm_cm_core_profiling_clkctrl = {
	"CM_CM_CORE_PROFILING_CLKCTRL",
	DRA7XX_OCP_SOCKET_CM_CORE_CM_CM_CORE_PROFILING_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_ocp_socket_cm_core_cm_core_debug_cfg = {
	"CM_CORE_DEBUG_CFG",
	DRA7XX_OCP_SOCKET_CM_CORE_CM_CORE_DEBUG_CFG,
	0xDEADBEEF,
	0};
reg *dra7xx_ocp_socket_cm_core_mod[DRA7XX_OCP_SOCKET_CM_CORE_MOD_REGCOUNT + 1] = {
	&dra7xx_ocp_socket_cm_core_revision_cm_core,
	&dra7xx_ocp_socket_cm_core_cm_cm_core_profiling_clkctrl,
	&dra7xx_ocp_socket_cm_core_cm_core_debug_cfg,
	NULL};

reg dra7xx_restore_cm_core_cm_l3main1_clkstctrl_restore = {
	"CM_L3MAIN1_CLKSTCTRL_RESTORE",
	DRA7XX_RESTORE_CM_CORE_CM_L3MAIN1_CLKSTCTRL_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_cm_l4cfg_clkstctrl_restore = {
	"CM_L4CFG_CLKSTCTRL_RESTORE",
	DRA7XX_RESTORE_CM_CORE_CM_L4CFG_CLKSTCTRL_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_cm_l4per_clkstctrl_restore = {
	"CM_L4PER_CLKSTCTRL_RESTORE",
	DRA7XX_RESTORE_CM_CORE_CM_L4PER_CLKSTCTRL_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_cm_l3init_clkstctrl_restore = {
	"CM_L3INIT_CLKSTCTRL_RESTORE",
	DRA7XX_RESTORE_CM_CORE_CM_L3INIT_CLKSTCTRL_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_cm_l3instr_l3_main_2_clkctrl_restore = {
	"CM_L3INSTR_L3_MAIN_2_CLKCTRL_RESTORE",
	DRA7XX_RESTORE_CM_CORE_CM_L3INSTR_L3_MAIN_2_CLKCTRL_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_cm_l3instr_l3_instr_clkctrl_restore = {
	"CM_L3INSTR_L3_INSTR_CLKCTRL_RESTORE",
	DRA7XX_RESTORE_CM_CORE_CM_L3INSTR_L3_INSTR_CLKCTRL_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_cm_l3instr_ocp_wp_noc_clkctrl_restore = {
	"CM_L3INSTR_OCP_WP_NOC_CLKCTRL_RESTORE",
	DRA7XX_RESTORE_CM_CORE_CM_L3INSTR_OCP_WP_NOC_CLKCTRL_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_cm_cm_core_profiling_clkctrl_restore = {
	"CM_CM_CORE_PROFILING_CLKCTRL_RESTORE",
	DRA7XX_RESTORE_CM_CORE_CM_CM_CORE_PROFILING_CLKCTRL_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_cm_l3main1_dynamicdep_restore = {
	"CM_L3MAIN1_DYNAMICDEP_RESTORE",
	DRA7XX_RESTORE_CM_CORE_CM_L3MAIN1_DYNAMICDEP_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_cm_l4cfg_dynamicdep_restore = {
	"CM_L4CFG_DYNAMICDEP_RESTORE",
	DRA7XX_RESTORE_CM_CORE_CM_L4CFG_DYNAMICDEP_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_cm_l4per_dynamicdep_restore = {
	"CM_L4PER_DYNAMICDEP_RESTORE",
	DRA7XX_RESTORE_CM_CORE_CM_L4PER_DYNAMICDEP_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_cm_coreaon_io_srcomp_clkctrl_restore = {
	"CM_COREAON_IO_SRCOMP_CLKCTRL_RESTORE",
	DRA7XX_RESTORE_CM_CORE_CM_COREAON_IO_SRCOMP_CLKCTRL_RESTORE,
	0xDEADBEEF,
	0};
reg dra7xx_restore_cm_core_cm_dma_staticdep_restore = {
	"CM_DMA_STATICDEP_RESTORE",
	DRA7XX_RESTORE_CM_CORE_CM_DMA_STATICDEP_RESTORE,
	0xDEADBEEF,
	0};
reg *dra7xx_restore_cm_core_mod[DRA7XX_RESTORE_CM_CORE_MOD_REGCOUNT + 1] = {
	&dra7xx_restore_cm_core_cm_l3main1_clkstctrl_restore,
	&dra7xx_restore_cm_core_cm_l4cfg_clkstctrl_restore,
	&dra7xx_restore_cm_core_cm_l4per_clkstctrl_restore,
	&dra7xx_restore_cm_core_cm_l3init_clkstctrl_restore,
	&dra7xx_restore_cm_core_cm_l3instr_l3_main_2_clkctrl_restore,
	&dra7xx_restore_cm_core_cm_l3instr_l3_instr_clkctrl_restore,
	&dra7xx_restore_cm_core_cm_l3instr_ocp_wp_noc_clkctrl_restore,
	&dra7xx_restore_cm_core_cm_cm_core_profiling_clkctrl_restore,
	&dra7xx_restore_cm_core_cm_l3main1_dynamicdep_restore,
	&dra7xx_restore_cm_core_cm_l4cfg_dynamicdep_restore,
	&dra7xx_restore_cm_core_cm_l4per_dynamicdep_restore,
	&dra7xx_restore_cm_core_cm_coreaon_io_srcomp_clkctrl_restore,
	&dra7xx_restore_cm_core_cm_dma_staticdep_restore,
	NULL};

reg dra7xx_ckgen_cm_core_aon_cm_clksel_core = {
	"CM_CLKSEL_CORE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_CLKSEL_CORE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_clksel_abe = {
	"CM_CLKSEL_ABE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_CLKSEL_ABE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_dll_ctrl = {
	"CM_DLL_CTRL",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DLL_CTRL,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_core = {
	"CM_CLKMODE_DPLL_CORE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_CLKMODE_DPLL_CORE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_idlest_dpll_core = {
	"CM_IDLEST_DPLL_CORE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_IDLEST_DPLL_CORE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_autoidle_dpll_core = {
	"CM_AUTOIDLE_DPLL_CORE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_AUTOIDLE_DPLL_CORE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_core = {
	"CM_CLKSEL_DPLL_CORE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_CLKSEL_DPLL_CORE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_m2_dpll_core = {
	"CM_DIV_M2_DPLL_CORE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_M2_DPLL_CORE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_m3_dpll_core = {
	"CM_DIV_M3_DPLL_CORE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_M3_DPLL_CORE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_h11_dpll_core = {
	"CM_DIV_H11_DPLL_CORE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_H11_DPLL_CORE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_h12_dpll_core = {
	"CM_DIV_H12_DPLL_CORE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_H12_DPLL_CORE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_h13_dpll_core = {
	"CM_DIV_H13_DPLL_CORE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_H13_DPLL_CORE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_h14_dpll_core = {
	"CM_DIV_H14_DPLL_CORE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_H14_DPLL_CORE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_ssc_deltamstep_dpll_core = {
	"CM_SSC_DELTAMSTEP_DPLL_CORE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_SSC_DELTAMSTEP_DPLL_CORE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_ssc_modfreqdiv_dpll_core = {
	"CM_SSC_MODFREQDIV_DPLL_CORE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_SSC_MODFREQDIV_DPLL_CORE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_h21_dpll_core = {
	"CM_DIV_H21_DPLL_CORE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_H21_DPLL_CORE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_h22_dpll_core = {
	"CM_DIV_H22_DPLL_CORE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_H22_DPLL_CORE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_h23_dpll_core = {
	"CM_DIV_H23_DPLL_CORE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_H23_DPLL_CORE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_h24_dpll_core = {
	"CM_DIV_H24_DPLL_CORE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_H24_DPLL_CORE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_mpu = {
	"CM_CLKMODE_DPLL_MPU",
	DRA7XX_CKGEN_CM_CORE_AON_CM_CLKMODE_DPLL_MPU,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_idlest_dpll_mpu = {
	"CM_IDLEST_DPLL_MPU",
	DRA7XX_CKGEN_CM_CORE_AON_CM_IDLEST_DPLL_MPU,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_autoidle_dpll_mpu = {
	"CM_AUTOIDLE_DPLL_MPU",
	DRA7XX_CKGEN_CM_CORE_AON_CM_AUTOIDLE_DPLL_MPU,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_mpu = {
	"CM_CLKSEL_DPLL_MPU",
	DRA7XX_CKGEN_CM_CORE_AON_CM_CLKSEL_DPLL_MPU,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_m2_dpll_mpu = {
	"CM_DIV_M2_DPLL_MPU",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_M2_DPLL_MPU,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_ssc_deltamstep_dpll_mpu = {
	"CM_SSC_DELTAMSTEP_DPLL_MPU",
	DRA7XX_CKGEN_CM_CORE_AON_CM_SSC_DELTAMSTEP_DPLL_MPU,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_ssc_modfreqdiv_dpll_mpu = {
	"CM_SSC_MODFREQDIV_DPLL_MPU",
	DRA7XX_CKGEN_CM_CORE_AON_CM_SSC_MODFREQDIV_DPLL_MPU,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_bypclk_dpll_mpu = {
	"CM_BYPCLK_DPLL_MPU",
	DRA7XX_CKGEN_CM_CORE_AON_CM_BYPCLK_DPLL_MPU,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_iva = {
	"CM_CLKMODE_DPLL_IVA",
	DRA7XX_CKGEN_CM_CORE_AON_CM_CLKMODE_DPLL_IVA,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_idlest_dpll_iva = {
	"CM_IDLEST_DPLL_IVA",
	DRA7XX_CKGEN_CM_CORE_AON_CM_IDLEST_DPLL_IVA,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_autoidle_dpll_iva = {
	"CM_AUTOIDLE_DPLL_IVA",
	DRA7XX_CKGEN_CM_CORE_AON_CM_AUTOIDLE_DPLL_IVA,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_iva = {
	"CM_CLKSEL_DPLL_IVA",
	DRA7XX_CKGEN_CM_CORE_AON_CM_CLKSEL_DPLL_IVA,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_m2_dpll_iva = {
	"CM_DIV_M2_DPLL_IVA",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_M2_DPLL_IVA,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_m3_dpll_iva = {
	"CM_DIV_M3_DPLL_IVA",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_M3_DPLL_IVA,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_ssc_deltamstep_dpll_iva = {
	"CM_SSC_DELTAMSTEP_DPLL_IVA",
	DRA7XX_CKGEN_CM_CORE_AON_CM_SSC_DELTAMSTEP_DPLL_IVA,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_ssc_modfreqdiv_dpll_iva = {
	"CM_SSC_MODFREQDIV_DPLL_IVA",
	DRA7XX_CKGEN_CM_CORE_AON_CM_SSC_MODFREQDIV_DPLL_IVA,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_bypclk_dpll_iva = {
	"CM_BYPCLK_DPLL_IVA",
	DRA7XX_CKGEN_CM_CORE_AON_CM_BYPCLK_DPLL_IVA,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_abe = {
	"CM_CLKMODE_DPLL_ABE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_CLKMODE_DPLL_ABE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_idlest_dpll_abe = {
	"CM_IDLEST_DPLL_ABE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_IDLEST_DPLL_ABE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_autoidle_dpll_abe = {
	"CM_AUTOIDLE_DPLL_ABE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_AUTOIDLE_DPLL_ABE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_abe = {
	"CM_CLKSEL_DPLL_ABE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_CLKSEL_DPLL_ABE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_m2_dpll_abe = {
	"CM_DIV_M2_DPLL_ABE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_M2_DPLL_ABE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_m3_dpll_abe = {
	"CM_DIV_M3_DPLL_ABE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_M3_DPLL_ABE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_ssc_deltamstep_dpll_abe = {
	"CM_SSC_DELTAMSTEP_DPLL_ABE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_SSC_DELTAMSTEP_DPLL_ABE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_ssc_modfreqdiv_dpll_abe = {
	"CM_SSC_MODFREQDIV_DPLL_ABE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_SSC_MODFREQDIV_DPLL_ABE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_ddr = {
	"CM_CLKMODE_DPLL_DDR",
	DRA7XX_CKGEN_CM_CORE_AON_CM_CLKMODE_DPLL_DDR,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_idlest_dpll_ddr = {
	"CM_IDLEST_DPLL_DDR",
	DRA7XX_CKGEN_CM_CORE_AON_CM_IDLEST_DPLL_DDR,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_autoidle_dpll_ddr = {
	"CM_AUTOIDLE_DPLL_DDR",
	DRA7XX_CKGEN_CM_CORE_AON_CM_AUTOIDLE_DPLL_DDR,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_ddr = {
	"CM_CLKSEL_DPLL_DDR",
	DRA7XX_CKGEN_CM_CORE_AON_CM_CLKSEL_DPLL_DDR,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_m2_dpll_ddr = {
	"CM_DIV_M2_DPLL_DDR",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_M2_DPLL_DDR,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_m3_dpll_ddr = {
	"CM_DIV_M3_DPLL_DDR",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_M3_DPLL_DDR,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_h11_dpll_ddr = {
	"CM_DIV_H11_DPLL_DDR",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_H11_DPLL_DDR,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_ssc_deltamstep_dpll_ddr = {
	"CM_SSC_DELTAMSTEP_DPLL_DDR",
	DRA7XX_CKGEN_CM_CORE_AON_CM_SSC_DELTAMSTEP_DPLL_DDR,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_ssc_modfreqdiv_dpll_ddr = {
	"CM_SSC_MODFREQDIV_DPLL_DDR",
	DRA7XX_CKGEN_CM_CORE_AON_CM_SSC_MODFREQDIV_DPLL_DDR,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_dsp = {
	"CM_CLKMODE_DPLL_DSP",
	DRA7XX_CKGEN_CM_CORE_AON_CM_CLKMODE_DPLL_DSP,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_idlest_dpll_dsp = {
	"CM_IDLEST_DPLL_DSP",
	DRA7XX_CKGEN_CM_CORE_AON_CM_IDLEST_DPLL_DSP,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_autoidle_dpll_dsp = {
	"CM_AUTOIDLE_DPLL_DSP",
	DRA7XX_CKGEN_CM_CORE_AON_CM_AUTOIDLE_DPLL_DSP,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_dsp = {
	"CM_CLKSEL_DPLL_DSP",
	DRA7XX_CKGEN_CM_CORE_AON_CM_CLKSEL_DPLL_DSP,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_m2_dpll_dsp = {
	"CM_DIV_M2_DPLL_DSP",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_M2_DPLL_DSP,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_m3_dpll_dsp = {
	"CM_DIV_M3_DPLL_DSP",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_M3_DPLL_DSP,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_ssc_deltamstep_dpll_dsp = {
	"CM_SSC_DELTAMSTEP_DPLL_DSP",
	DRA7XX_CKGEN_CM_CORE_AON_CM_SSC_DELTAMSTEP_DPLL_DSP,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_ssc_modfreqdiv_dpll_dsp = {
	"CM_SSC_MODFREQDIV_DPLL_DSP",
	DRA7XX_CKGEN_CM_CORE_AON_CM_SSC_MODFREQDIV_DPLL_DSP,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_bypclk_dpll_dsp = {
	"CM_BYPCLK_DPLL_DSP",
	DRA7XX_CKGEN_CM_CORE_AON_CM_BYPCLK_DPLL_DSP,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_shadow_freq_config1 = {
	"CM_SHADOW_FREQ_CONFIG1",
	DRA7XX_CKGEN_CM_CORE_AON_CM_SHADOW_FREQ_CONFIG1,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_shadow_freq_config2 = {
	"CM_SHADOW_FREQ_CONFIG2",
	DRA7XX_CKGEN_CM_CORE_AON_CM_SHADOW_FREQ_CONFIG2,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_dyn_dep_prescal = {
	"CM_DYN_DEP_PRESCAL",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DYN_DEP_PRESCAL,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_restore_st = {
	"CM_RESTORE_ST",
	DRA7XX_CKGEN_CM_CORE_AON_CM_RESTORE_ST,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_eve = {
	"CM_CLKMODE_DPLL_EVE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_CLKMODE_DPLL_EVE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_idlest_dpll_eve = {
	"CM_IDLEST_DPLL_EVE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_IDLEST_DPLL_EVE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_autoidle_dpll_eve = {
	"CM_AUTOIDLE_DPLL_EVE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_AUTOIDLE_DPLL_EVE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_eve = {
	"CM_CLKSEL_DPLL_EVE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_CLKSEL_DPLL_EVE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_m2_dpll_eve = {
	"CM_DIV_M2_DPLL_EVE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_M2_DPLL_EVE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_m3_dpll_eve = {
	"CM_DIV_M3_DPLL_EVE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_M3_DPLL_EVE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_ssc_deltamstep_dpll_eve = {
	"CM_SSC_DELTAMSTEP_DPLL_EVE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_SSC_DELTAMSTEP_DPLL_EVE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_ssc_modfreqdiv_dpll_eve = {
	"CM_SSC_MODFREQDIV_DPLL_EVE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_SSC_MODFREQDIV_DPLL_EVE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_bypclk_dpll_eve = {
	"CM_BYPCLK_DPLL_EVE",
	DRA7XX_CKGEN_CM_CORE_AON_CM_BYPCLK_DPLL_EVE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_gmac = {
	"CM_CLKMODE_DPLL_GMAC",
	DRA7XX_CKGEN_CM_CORE_AON_CM_CLKMODE_DPLL_GMAC,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_idlest_dpll_gmac = {
	"CM_IDLEST_DPLL_GMAC",
	DRA7XX_CKGEN_CM_CORE_AON_CM_IDLEST_DPLL_GMAC,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_autoidle_dpll_gmac = {
	"CM_AUTOIDLE_DPLL_GMAC",
	DRA7XX_CKGEN_CM_CORE_AON_CM_AUTOIDLE_DPLL_GMAC,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_gmac = {
	"CM_CLKSEL_DPLL_GMAC",
	DRA7XX_CKGEN_CM_CORE_AON_CM_CLKSEL_DPLL_GMAC,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_m2_dpll_gmac = {
	"CM_DIV_M2_DPLL_GMAC",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_M2_DPLL_GMAC,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_m3_dpll_gmac = {
	"CM_DIV_M3_DPLL_GMAC",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_M3_DPLL_GMAC,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_h11_dpll_gmac = {
	"CM_DIV_H11_DPLL_GMAC",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_H11_DPLL_GMAC,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_h12_dpll_gmac = {
	"CM_DIV_H12_DPLL_GMAC",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_H12_DPLL_GMAC,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_h13_dpll_gmac = {
	"CM_DIV_H13_DPLL_GMAC",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_H13_DPLL_GMAC,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_h14_dpll_gmac = {
	"CM_DIV_H14_DPLL_GMAC",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_H14_DPLL_GMAC,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_ssc_deltamstep_dpll_gmac = {
	"CM_SSC_DELTAMSTEP_DPLL_GMAC",
	DRA7XX_CKGEN_CM_CORE_AON_CM_SSC_DELTAMSTEP_DPLL_GMAC,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_ssc_modfreqdiv_dpll_gmac = {
	"CM_SSC_MODFREQDIV_DPLL_GMAC",
	DRA7XX_CKGEN_CM_CORE_AON_CM_SSC_MODFREQDIV_DPLL_GMAC,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_gpu = {
	"CM_CLKMODE_DPLL_GPU",
	DRA7XX_CKGEN_CM_CORE_AON_CM_CLKMODE_DPLL_GPU,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_idlest_dpll_gpu = {
	"CM_IDLEST_DPLL_GPU",
	DRA7XX_CKGEN_CM_CORE_AON_CM_IDLEST_DPLL_GPU,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_autoidle_dpll_gpu = {
	"CM_AUTOIDLE_DPLL_GPU",
	DRA7XX_CKGEN_CM_CORE_AON_CM_AUTOIDLE_DPLL_GPU,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_gpu = {
	"CM_CLKSEL_DPLL_GPU",
	DRA7XX_CKGEN_CM_CORE_AON_CM_CLKSEL_DPLL_GPU,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_m2_dpll_gpu = {
	"CM_DIV_M2_DPLL_GPU",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_M2_DPLL_GPU,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_div_m3_dpll_gpu = {
	"CM_DIV_M3_DPLL_GPU",
	DRA7XX_CKGEN_CM_CORE_AON_CM_DIV_M3_DPLL_GPU,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_ssc_deltamstep_dpll_gpu = {
	"CM_SSC_DELTAMSTEP_DPLL_GPU",
	DRA7XX_CKGEN_CM_CORE_AON_CM_SSC_DELTAMSTEP_DPLL_GPU,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_aon_cm_ssc_modfreqdiv_dpll_gpu = {
	"CM_SSC_MODFREQDIV_DPLL_GPU",
	DRA7XX_CKGEN_CM_CORE_AON_CM_SSC_MODFREQDIV_DPLL_GPU,
	0xDEADBEEF,
	0};
reg *dra7xx_ckgen_cm_core_aon_mod[DRA7XX_CKGEN_CM_CORE_AON_MOD_REGCOUNT + 1] = {
	&dra7xx_ckgen_cm_core_aon_cm_clksel_core,
	&dra7xx_ckgen_cm_core_aon_cm_clksel_abe,
	&dra7xx_ckgen_cm_core_aon_cm_dll_ctrl,
	&dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_core,
	&dra7xx_ckgen_cm_core_aon_cm_idlest_dpll_core,
	&dra7xx_ckgen_cm_core_aon_cm_autoidle_dpll_core,
	&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_core,
	&dra7xx_ckgen_cm_core_aon_cm_div_m2_dpll_core,
	&dra7xx_ckgen_cm_core_aon_cm_div_m3_dpll_core,
	&dra7xx_ckgen_cm_core_aon_cm_div_h11_dpll_core,
	&dra7xx_ckgen_cm_core_aon_cm_div_h12_dpll_core,
	&dra7xx_ckgen_cm_core_aon_cm_div_h13_dpll_core,
	&dra7xx_ckgen_cm_core_aon_cm_div_h14_dpll_core,
	&dra7xx_ckgen_cm_core_aon_cm_ssc_deltamstep_dpll_core,
	&dra7xx_ckgen_cm_core_aon_cm_ssc_modfreqdiv_dpll_core,
	&dra7xx_ckgen_cm_core_aon_cm_div_h21_dpll_core,
	&dra7xx_ckgen_cm_core_aon_cm_div_h22_dpll_core,
	&dra7xx_ckgen_cm_core_aon_cm_div_h23_dpll_core,
	&dra7xx_ckgen_cm_core_aon_cm_div_h24_dpll_core,
	&dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_mpu,
	&dra7xx_ckgen_cm_core_aon_cm_idlest_dpll_mpu,
	&dra7xx_ckgen_cm_core_aon_cm_autoidle_dpll_mpu,
	&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_mpu,
	&dra7xx_ckgen_cm_core_aon_cm_div_m2_dpll_mpu,
	&dra7xx_ckgen_cm_core_aon_cm_ssc_deltamstep_dpll_mpu,
	&dra7xx_ckgen_cm_core_aon_cm_ssc_modfreqdiv_dpll_mpu,
	&dra7xx_ckgen_cm_core_aon_cm_bypclk_dpll_mpu,
	&dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_iva,
	&dra7xx_ckgen_cm_core_aon_cm_idlest_dpll_iva,
	&dra7xx_ckgen_cm_core_aon_cm_autoidle_dpll_iva,
	&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_iva,
	&dra7xx_ckgen_cm_core_aon_cm_div_m2_dpll_iva,
	&dra7xx_ckgen_cm_core_aon_cm_div_m3_dpll_iva,
	&dra7xx_ckgen_cm_core_aon_cm_ssc_deltamstep_dpll_iva,
	&dra7xx_ckgen_cm_core_aon_cm_ssc_modfreqdiv_dpll_iva,
	&dra7xx_ckgen_cm_core_aon_cm_bypclk_dpll_iva,
	&dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_abe,
	&dra7xx_ckgen_cm_core_aon_cm_idlest_dpll_abe,
	&dra7xx_ckgen_cm_core_aon_cm_autoidle_dpll_abe,
	&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_abe,
	&dra7xx_ckgen_cm_core_aon_cm_div_m2_dpll_abe,
	&dra7xx_ckgen_cm_core_aon_cm_div_m3_dpll_abe,
	&dra7xx_ckgen_cm_core_aon_cm_ssc_deltamstep_dpll_abe,
	&dra7xx_ckgen_cm_core_aon_cm_ssc_modfreqdiv_dpll_abe,
	&dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_ddr,
	&dra7xx_ckgen_cm_core_aon_cm_idlest_dpll_ddr,
	&dra7xx_ckgen_cm_core_aon_cm_autoidle_dpll_ddr,
	&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_ddr,
	&dra7xx_ckgen_cm_core_aon_cm_div_m2_dpll_ddr,
	&dra7xx_ckgen_cm_core_aon_cm_div_m3_dpll_ddr,
	&dra7xx_ckgen_cm_core_aon_cm_div_h11_dpll_ddr,
	&dra7xx_ckgen_cm_core_aon_cm_ssc_deltamstep_dpll_ddr,
	&dra7xx_ckgen_cm_core_aon_cm_ssc_modfreqdiv_dpll_ddr,
	&dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_dsp,
	&dra7xx_ckgen_cm_core_aon_cm_idlest_dpll_dsp,
	&dra7xx_ckgen_cm_core_aon_cm_autoidle_dpll_dsp,
	&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_dsp,
	&dra7xx_ckgen_cm_core_aon_cm_div_m2_dpll_dsp,
	&dra7xx_ckgen_cm_core_aon_cm_div_m3_dpll_dsp,
	&dra7xx_ckgen_cm_core_aon_cm_ssc_deltamstep_dpll_dsp,
	&dra7xx_ckgen_cm_core_aon_cm_ssc_modfreqdiv_dpll_dsp,
	&dra7xx_ckgen_cm_core_aon_cm_bypclk_dpll_dsp,
	&dra7xx_ckgen_cm_core_aon_cm_shadow_freq_config1,
	&dra7xx_ckgen_cm_core_aon_cm_shadow_freq_config2,
	&dra7xx_ckgen_cm_core_aon_cm_dyn_dep_prescal,
	&dra7xx_ckgen_cm_core_aon_cm_restore_st,
	&dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_eve,
	&dra7xx_ckgen_cm_core_aon_cm_idlest_dpll_eve,
	&dra7xx_ckgen_cm_core_aon_cm_autoidle_dpll_eve,
	&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_eve,
	&dra7xx_ckgen_cm_core_aon_cm_div_m2_dpll_eve,
	&dra7xx_ckgen_cm_core_aon_cm_div_m3_dpll_eve,
	&dra7xx_ckgen_cm_core_aon_cm_ssc_deltamstep_dpll_eve,
	&dra7xx_ckgen_cm_core_aon_cm_ssc_modfreqdiv_dpll_eve,
	&dra7xx_ckgen_cm_core_aon_cm_bypclk_dpll_eve,
	&dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_gmac,
	&dra7xx_ckgen_cm_core_aon_cm_idlest_dpll_gmac,
	&dra7xx_ckgen_cm_core_aon_cm_autoidle_dpll_gmac,
	&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_gmac,
	&dra7xx_ckgen_cm_core_aon_cm_div_m2_dpll_gmac,
	&dra7xx_ckgen_cm_core_aon_cm_div_m3_dpll_gmac,
	&dra7xx_ckgen_cm_core_aon_cm_div_h11_dpll_gmac,
	&dra7xx_ckgen_cm_core_aon_cm_div_h12_dpll_gmac,
	&dra7xx_ckgen_cm_core_aon_cm_div_h13_dpll_gmac,
	&dra7xx_ckgen_cm_core_aon_cm_div_h14_dpll_gmac,
	&dra7xx_ckgen_cm_core_aon_cm_ssc_deltamstep_dpll_gmac,
	&dra7xx_ckgen_cm_core_aon_cm_ssc_modfreqdiv_dpll_gmac,
	&dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_gpu,
	&dra7xx_ckgen_cm_core_aon_cm_idlest_dpll_gpu,
	&dra7xx_ckgen_cm_core_aon_cm_autoidle_dpll_gpu,
	&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_gpu,
	&dra7xx_ckgen_cm_core_aon_cm_div_m2_dpll_gpu,
	&dra7xx_ckgen_cm_core_aon_cm_div_m3_dpll_gpu,
	&dra7xx_ckgen_cm_core_aon_cm_ssc_deltamstep_dpll_gpu,
	&dra7xx_ckgen_cm_core_aon_cm_ssc_modfreqdiv_dpll_gpu,
	NULL};

reg dra7xx_ckgen_cm_core_cm_clksel_usb_60mhz = {
	"CM_CLKSEL_USB_60MHZ",
	DRA7XX_CKGEN_CM_CORE_CM_CLKSEL_USB_60MHZ,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_clkmode_dpll_per = {
	"CM_CLKMODE_DPLL_PER",
	DRA7XX_CKGEN_CM_CORE_CM_CLKMODE_DPLL_PER,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_idlest_dpll_per = {
	"CM_IDLEST_DPLL_PER",
	DRA7XX_CKGEN_CM_CORE_CM_IDLEST_DPLL_PER,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_autoidle_dpll_per = {
	"CM_AUTOIDLE_DPLL_PER",
	DRA7XX_CKGEN_CM_CORE_CM_AUTOIDLE_DPLL_PER,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_clksel_dpll_per = {
	"CM_CLKSEL_DPLL_PER",
	DRA7XX_CKGEN_CM_CORE_CM_CLKSEL_DPLL_PER,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_div_m2_dpll_per = {
	"CM_DIV_M2_DPLL_PER",
	DRA7XX_CKGEN_CM_CORE_CM_DIV_M2_DPLL_PER,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_div_m3_dpll_per = {
	"CM_DIV_M3_DPLL_PER",
	DRA7XX_CKGEN_CM_CORE_CM_DIV_M3_DPLL_PER,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_div_h11_dpll_per = {
	"CM_DIV_H11_DPLL_PER",
	DRA7XX_CKGEN_CM_CORE_CM_DIV_H11_DPLL_PER,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_div_h12_dpll_per = {
	"CM_DIV_H12_DPLL_PER",
	DRA7XX_CKGEN_CM_CORE_CM_DIV_H12_DPLL_PER,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_div_h13_dpll_per = {
	"CM_DIV_H13_DPLL_PER",
	DRA7XX_CKGEN_CM_CORE_CM_DIV_H13_DPLL_PER,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_div_h14_dpll_per = {
	"CM_DIV_H14_DPLL_PER",
	DRA7XX_CKGEN_CM_CORE_CM_DIV_H14_DPLL_PER,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_ssc_deltamstep_dpll_per = {
	"CM_SSC_DELTAMSTEP_DPLL_PER",
	DRA7XX_CKGEN_CM_CORE_CM_SSC_DELTAMSTEP_DPLL_PER,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_ssc_modfreqdiv_dpll_per = {
	"CM_SSC_MODFREQDIV_DPLL_PER",
	DRA7XX_CKGEN_CM_CORE_CM_SSC_MODFREQDIV_DPLL_PER,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_clkmode_dpll_usb = {
	"CM_CLKMODE_DPLL_USB",
	DRA7XX_CKGEN_CM_CORE_CM_CLKMODE_DPLL_USB,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_idlest_dpll_usb = {
	"CM_IDLEST_DPLL_USB",
	DRA7XX_CKGEN_CM_CORE_CM_IDLEST_DPLL_USB,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_autoidle_dpll_usb = {
	"CM_AUTOIDLE_DPLL_USB",
	DRA7XX_CKGEN_CM_CORE_CM_AUTOIDLE_DPLL_USB,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_clksel_dpll_usb = {
	"CM_CLKSEL_DPLL_USB",
	DRA7XX_CKGEN_CM_CORE_CM_CLKSEL_DPLL_USB,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_div_m2_dpll_usb = {
	"CM_DIV_M2_DPLL_USB",
	DRA7XX_CKGEN_CM_CORE_CM_DIV_M2_DPLL_USB,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_ssc_deltamstep_dpll_usb = {
	"CM_SSC_DELTAMSTEP_DPLL_USB",
	DRA7XX_CKGEN_CM_CORE_CM_SSC_DELTAMSTEP_DPLL_USB,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_ssc_modfreqdiv_dpll_usb = {
	"CM_SSC_MODFREQDIV_DPLL_USB",
	DRA7XX_CKGEN_CM_CORE_CM_SSC_MODFREQDIV_DPLL_USB,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_clkdcoldo_dpll_usb = {
	"CM_CLKDCOLDO_DPLL_USB",
	DRA7XX_CKGEN_CM_CORE_CM_CLKDCOLDO_DPLL_USB,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_clkmode_dpll_pcie_ref = {
	"CM_CLKMODE_DPLL_PCIE_REF",
	DRA7XX_CKGEN_CM_CORE_CM_CLKMODE_DPLL_PCIE_REF,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_idlest_dpll_pcie_ref = {
	"CM_IDLEST_DPLL_PCIE_REF",
	DRA7XX_CKGEN_CM_CORE_CM_IDLEST_DPLL_PCIE_REF,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_autoidle_dpll_pcie_ref = {
	"CM_AUTOIDLE_DPLL_PCIE_REF",
	DRA7XX_CKGEN_CM_CORE_CM_AUTOIDLE_DPLL_PCIE_REF,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_clksel_dpll_pcie_ref = {
	"CM_CLKSEL_DPLL_PCIE_REF",
	DRA7XX_CKGEN_CM_CORE_CM_CLKSEL_DPLL_PCIE_REF,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_div_m2_dpll_pcie_ref = {
	"CM_DIV_M2_DPLL_PCIE_REF",
	DRA7XX_CKGEN_CM_CORE_CM_DIV_M2_DPLL_PCIE_REF,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_ssc_deltamstep_dpll_pcie_ref = {
	"CM_SSC_DELTAMSTEP_DPLL_PCIE_REF",
	DRA7XX_CKGEN_CM_CORE_CM_SSC_DELTAMSTEP_DPLL_PCIE_REF,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_ssc_modfreqdiv_dpll_pcie_ref = {
	"CM_SSC_MODFREQDIV_DPLL_PCIE_REF",
	DRA7XX_CKGEN_CM_CORE_CM_SSC_MODFREQDIV_DPLL_PCIE_REF,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_clkmode_apll_pcie = {
	"CM_CLKMODE_APLL_PCIE",
	DRA7XX_CKGEN_CM_CORE_CM_CLKMODE_APLL_PCIE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_idlest_apll_pcie = {
	"CM_IDLEST_APLL_PCIE",
	DRA7XX_CKGEN_CM_CORE_CM_IDLEST_APLL_PCIE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_div_m2_apll_pcie = {
	"CM_DIV_M2_APLL_PCIE",
	DRA7XX_CKGEN_CM_CORE_CM_DIV_M2_APLL_PCIE,
	0xDEADBEEF,
	0};
reg dra7xx_ckgen_cm_core_cm_clkvcoldo_apll_pcie = {
	"CM_CLKVCOLDO_APLL_PCIE",
	DRA7XX_CKGEN_CM_CORE_CM_CLKVCOLDO_APLL_PCIE,
	0xDEADBEEF,
	0};
reg *dra7xx_ckgen_cm_core_mod[DRA7XX_CKGEN_CM_CORE_MOD_REGCOUNT + 1] = {
	&dra7xx_ckgen_cm_core_cm_clksel_usb_60mhz,
	&dra7xx_ckgen_cm_core_cm_clkmode_dpll_per,
	&dra7xx_ckgen_cm_core_cm_idlest_dpll_per,
	&dra7xx_ckgen_cm_core_cm_autoidle_dpll_per,
	&dra7xx_ckgen_cm_core_cm_clksel_dpll_per,
	&dra7xx_ckgen_cm_core_cm_div_m2_dpll_per,
	&dra7xx_ckgen_cm_core_cm_div_m3_dpll_per,
	&dra7xx_ckgen_cm_core_cm_div_h11_dpll_per,
	&dra7xx_ckgen_cm_core_cm_div_h12_dpll_per,
	&dra7xx_ckgen_cm_core_cm_div_h13_dpll_per,
	&dra7xx_ckgen_cm_core_cm_div_h14_dpll_per,
	&dra7xx_ckgen_cm_core_cm_ssc_deltamstep_dpll_per,
	&dra7xx_ckgen_cm_core_cm_ssc_modfreqdiv_dpll_per,
	&dra7xx_ckgen_cm_core_cm_clkmode_dpll_usb,
	&dra7xx_ckgen_cm_core_cm_idlest_dpll_usb,
	&dra7xx_ckgen_cm_core_cm_autoidle_dpll_usb,
	&dra7xx_ckgen_cm_core_cm_clksel_dpll_usb,
	&dra7xx_ckgen_cm_core_cm_div_m2_dpll_usb,
	&dra7xx_ckgen_cm_core_cm_ssc_deltamstep_dpll_usb,
	&dra7xx_ckgen_cm_core_cm_ssc_modfreqdiv_dpll_usb,
	&dra7xx_ckgen_cm_core_cm_clkdcoldo_dpll_usb,
	&dra7xx_ckgen_cm_core_cm_clkmode_dpll_pcie_ref,
	&dra7xx_ckgen_cm_core_cm_idlest_dpll_pcie_ref,
	&dra7xx_ckgen_cm_core_cm_autoidle_dpll_pcie_ref,
	&dra7xx_ckgen_cm_core_cm_clksel_dpll_pcie_ref,
	&dra7xx_ckgen_cm_core_cm_div_m2_dpll_pcie_ref,
	&dra7xx_ckgen_cm_core_cm_ssc_deltamstep_dpll_pcie_ref,
	&dra7xx_ckgen_cm_core_cm_ssc_modfreqdiv_dpll_pcie_ref,
	&dra7xx_ckgen_cm_core_cm_clkmode_apll_pcie,
	&dra7xx_ckgen_cm_core_cm_idlest_apll_pcie,
	&dra7xx_ckgen_cm_core_cm_div_m2_apll_pcie,
	&dra7xx_ckgen_cm_core_cm_clkvcoldo_apll_pcie,
	NULL};

reg dra7xx_emu_cm_cm_emu_clkstctrl = {
	"CM_EMU_CLKSTCTRL",
	DRA7XX_EMU_CM_CM_EMU_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_emu_cm_cm_emu_debugss_clkctrl = {
	"CM_EMU_DEBUGSS_CLKCTRL",
	DRA7XX_EMU_CM_CM_EMU_DEBUGSS_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_emu_cm_cm_emu_dynamicdep = {
	"CM_EMU_DYNAMICDEP",
	DRA7XX_EMU_CM_CM_EMU_DYNAMICDEP,
	0xDEADBEEF,
	0};
reg dra7xx_emu_cm_cm_emu_mpu_emu_dbg_clkctrl = {
	"CM_EMU_MPU_EMU_DBG_CLKCTRL",
	DRA7XX_EMU_CM_CM_EMU_MPU_EMU_DBG_CLKCTRL,
	0xDEADBEEF,
	0};
reg *dra7xx_emu_cm_mod[DRA7XX_EMU_CM_MOD_REGCOUNT + 1] = {
	&dra7xx_emu_cm_cm_emu_clkstctrl,
	&dra7xx_emu_cm_cm_emu_debugss_clkctrl,
	&dra7xx_emu_cm_cm_emu_dynamicdep,
	&dra7xx_emu_cm_cm_emu_mpu_emu_dbg_clkctrl,
	NULL};

reg dra7xx_wkupaon_cm_cm_wkupaon_clkstctrl = {
	"CM_WKUPAON_CLKSTCTRL",
	DRA7XX_WKUPAON_CM_CM_WKUPAON_CLKSTCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_cm_cm_wkupaon_l4_wkup_clkctrl = {
	"CM_WKUPAON_L4_WKUP_CLKCTRL",
	DRA7XX_WKUPAON_CM_CM_WKUPAON_L4_WKUP_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_cm_cm_wkupaon_wd_timer1_clkctrl = {
	"CM_WKUPAON_WD_TIMER1_CLKCTRL",
	DRA7XX_WKUPAON_CM_CM_WKUPAON_WD_TIMER1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_cm_cm_wkupaon_wd_timer2_clkctrl = {
	"CM_WKUPAON_WD_TIMER2_CLKCTRL",
	DRA7XX_WKUPAON_CM_CM_WKUPAON_WD_TIMER2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_cm_cm_wkupaon_gpio1_clkctrl = {
	"CM_WKUPAON_GPIO1_CLKCTRL",
	DRA7XX_WKUPAON_CM_CM_WKUPAON_GPIO1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_cm_cm_wkupaon_timer1_clkctrl = {
	"CM_WKUPAON_TIMER1_CLKCTRL",
	DRA7XX_WKUPAON_CM_CM_WKUPAON_TIMER1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_cm_cm_wkupaon_timer12_clkctrl = {
	"CM_WKUPAON_TIMER12_CLKCTRL",
	DRA7XX_WKUPAON_CM_CM_WKUPAON_TIMER12_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_cm_cm_wkupaon_counter_32k_clkctrl = {
	"CM_WKUPAON_COUNTER_32K_CLKCTRL",
	DRA7XX_WKUPAON_CM_CM_WKUPAON_COUNTER_32K_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_cm_cm_wkupaon_sar_ram_clkctrl = {
	"CM_WKUPAON_SAR_RAM_CLKCTRL",
	DRA7XX_WKUPAON_CM_CM_WKUPAON_SAR_RAM_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_cm_cm_wkupaon_kbd_clkctrl = {
	"CM_WKUPAON_KBD_CLKCTRL",
	DRA7XX_WKUPAON_CM_CM_WKUPAON_KBD_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_cm_cm_wkupaon_uart10_clkctrl = {
	"CM_WKUPAON_UART10_CLKCTRL",
	DRA7XX_WKUPAON_CM_CM_WKUPAON_UART10_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_cm_cm_wkupaon_dcan1_clkctrl = {
	"CM_WKUPAON_DCAN1_CLKCTRL",
	DRA7XX_WKUPAON_CM_CM_WKUPAON_DCAN1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_cm_cm_wkupaon_scrm_clkctrl = {
	"CM_WKUPAON_SCRM_CLKCTRL",
	DRA7XX_WKUPAON_CM_CM_WKUPAON_SCRM_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_cm_cm_wkupaon_io_srcomp_clkctrl = {
	"CM_WKUPAON_IO_SRCOMP_CLKCTRL",
	DRA7XX_WKUPAON_CM_CM_WKUPAON_IO_SRCOMP_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_cm_cm_wkupaon_adc_clkctrl = {
	"CM_WKUPAON_ADC_CLKCTRL",
	DRA7XX_WKUPAON_CM_CM_WKUPAON_ADC_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_cm_cm_wkupaon_spare_safety1_clkctrl = {
	"CM_WKUPAON_SPARE_SAFETY1_CLKCTRL",
	DRA7XX_WKUPAON_CM_CM_WKUPAON_SPARE_SAFETY1_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_cm_cm_wkupaon_spare_safety2_clkctrl = {
	"CM_WKUPAON_SPARE_SAFETY2_CLKCTRL",
	DRA7XX_WKUPAON_CM_CM_WKUPAON_SPARE_SAFETY2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_cm_cm_wkupaon_spare_safety3_clkctrl = {
	"CM_WKUPAON_SPARE_SAFETY3_CLKCTRL",
	DRA7XX_WKUPAON_CM_CM_WKUPAON_SPARE_SAFETY3_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_cm_cm_wkupaon_spare_safety4_clkctrl = {
	"CM_WKUPAON_SPARE_SAFETY4_CLKCTRL",
	DRA7XX_WKUPAON_CM_CM_WKUPAON_SPARE_SAFETY4_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_cm_cm_wkupaon_spare_unknown2_clkctrl = {
	"CM_WKUPAON_SPARE_UNKNOWN2_CLKCTRL",
	DRA7XX_WKUPAON_CM_CM_WKUPAON_SPARE_UNKNOWN2_CLKCTRL,
	0xDEADBEEF,
	0};
reg dra7xx_wkupaon_cm_cm_wkupaon_spare_unknown3_clkctrl = {
	"CM_WKUPAON_SPARE_UNKNOWN3_CLKCTRL",
	DRA7XX_WKUPAON_CM_CM_WKUPAON_SPARE_UNKNOWN3_CLKCTRL,
	0xDEADBEEF,
	0};
reg *dra7xx_wkupaon_cm_mod[DRA7XX_WKUPAON_CM_MOD_REGCOUNT + 1] = {
	&dra7xx_wkupaon_cm_cm_wkupaon_clkstctrl,
	&dra7xx_wkupaon_cm_cm_wkupaon_l4_wkup_clkctrl,
	&dra7xx_wkupaon_cm_cm_wkupaon_wd_timer1_clkctrl,
	&dra7xx_wkupaon_cm_cm_wkupaon_wd_timer2_clkctrl,
	&dra7xx_wkupaon_cm_cm_wkupaon_gpio1_clkctrl,
	&dra7xx_wkupaon_cm_cm_wkupaon_timer1_clkctrl,
	&dra7xx_wkupaon_cm_cm_wkupaon_timer12_clkctrl,
	&dra7xx_wkupaon_cm_cm_wkupaon_counter_32k_clkctrl,
	&dra7xx_wkupaon_cm_cm_wkupaon_sar_ram_clkctrl,
	&dra7xx_wkupaon_cm_cm_wkupaon_kbd_clkctrl,
	&dra7xx_wkupaon_cm_cm_wkupaon_uart10_clkctrl,
	&dra7xx_wkupaon_cm_cm_wkupaon_dcan1_clkctrl,
	&dra7xx_wkupaon_cm_cm_wkupaon_scrm_clkctrl,
	&dra7xx_wkupaon_cm_cm_wkupaon_io_srcomp_clkctrl,
	&dra7xx_wkupaon_cm_cm_wkupaon_adc_clkctrl,
	&dra7xx_wkupaon_cm_cm_wkupaon_spare_safety1_clkctrl,
	&dra7xx_wkupaon_cm_cm_wkupaon_spare_safety2_clkctrl,
	&dra7xx_wkupaon_cm_cm_wkupaon_spare_safety3_clkctrl,
	&dra7xx_wkupaon_cm_cm_wkupaon_spare_safety4_clkctrl,
	&dra7xx_wkupaon_cm_cm_wkupaon_spare_unknown2_clkctrl,
	&dra7xx_wkupaon_cm_cm_wkupaon_spare_unknown3_clkctrl,
	NULL};

reg **cm_dra7xx_mods[CM_DRA7XX_MODS_COUNT + 1] = {
	[CM_DRA7XX_DSP_CM_CORE_AON] = (reg **) &dra7xx_dsp_cm_core_aon_mod,
	[CM_DRA7XX_EVE_CM_CORE_AON] = (reg **) &dra7xx_eve_cm_core_aon_mod,
	[CM_DRA7XX_INSTR_CM_CORE_AON] = (reg **) &dra7xx_instr_cm_core_aon_mod,
	[CM_DRA7XX_IPU_CM_CORE_AON] = (reg **) &dra7xx_ipu_cm_core_aon_mod,
	[CM_DRA7XX_MPU_CM_CORE_AON] = (reg **) &dra7xx_mpu_cm_core_aon_mod,
	[CM_DRA7XX_OCP_SOCKET_CM_CORE_AON] = (reg **) &dra7xx_ocp_socket_cm_core_aon_mod,
	[CM_DRA7XX_RESTORE_CM_CORE_AON] = (reg **) &dra7xx_restore_cm_core_aon_mod,
	[CM_DRA7XX_RTC_CM_CORE_AON] = (reg **) &dra7xx_rtc_cm_core_aon_mod,
	[CM_DRA7XX_VPE_CM_CORE_AON] = (reg **) &dra7xx_vpe_cm_core_aon_mod,
	[CM_DRA7XX_CAM_CM_CORE] = (reg **) &dra7xx_cam_cm_core_mod,
	[CM_DRA7XX_COREAON_CM_CORE] = (reg **) &dra7xx_coreaon_cm_core_mod,
	[CM_DRA7XX_CORE_CM_CORE] = (reg **) &dra7xx_core_cm_core_mod,
	[CM_DRA7XX_CUSTEFUSE_CM_CORE] = (reg **) &dra7xx_custefuse_cm_core_mod,
	[CM_DRA7XX_DSS_CM_CORE] = (reg **) &dra7xx_dss_cm_core_mod,
	[CM_DRA7XX_GPU_CM_CORE] = (reg **) &dra7xx_gpu_cm_core_mod,
	[CM_DRA7XX_IVA_CM_CORE] = (reg **) &dra7xx_iva_cm_core_mod,
	[CM_DRA7XX_L3INIT_CM_CORE] = (reg **) &dra7xx_l3init_cm_core_mod,
	[CM_DRA7XX_L4PER_CM_CORE] = (reg **) &dra7xx_l4per_cm_core_mod,
	[CM_DRA7XX_OCP_SOCKET_CM_CORE] = (reg **) &dra7xx_ocp_socket_cm_core_mod,
	[CM_DRA7XX_RESTORE_CM_CORE] = (reg **) &dra7xx_restore_cm_core_mod,
	[CM_DRA7XX_CKGEN_CM_CORE_AON] = (reg **) &dra7xx_ckgen_cm_core_aon_mod,
	[CM_DRA7XX_CKGEN_CM_CORE] = (reg **) &dra7xx_ckgen_cm_core_mod,
	[CM_DRA7XX_EMU_CM] = (reg **) &dra7xx_emu_cm_mod,
	[CM_DRA7XX_WKUPAON_CM] = (reg **) &dra7xx_wkupaon_cm_mod,
	NULL};

const char *cm_dra7xx_mods_name[CM_DRA7XX_MODS_COUNT] = {
	[CM_DRA7XX_DSP_CM_CORE_AON] = "CM CORE AON DSP",
	[CM_DRA7XX_EVE_CM_CORE_AON] = "CM CORE AON EVE",
	[CM_DRA7XX_INSTR_CM_CORE_AON] = "CM CORE AON INSTR",
	[CM_DRA7XX_IPU_CM_CORE_AON] = "CM CORE AON IPU",
	[CM_DRA7XX_MPU_CM_CORE_AON] = "CM CORE AON MPU",
	[CM_DRA7XX_OCP_SOCKET_CM_CORE_AON] = "CM CORE AON OCP SOCKET",
	[CM_DRA7XX_RESTORE_CM_CORE_AON] = "CM CORE AON RESTORE",
	[CM_DRA7XX_RTC_CM_CORE_AON] = "CM CORE AON RTC",
	[CM_DRA7XX_VPE_CM_CORE_AON] = "CM CORE AON VPE",
	[CM_DRA7XX_CAM_CM_CORE] = "CM CORE CAM",
	[CM_DRA7XX_COREAON_CM_CORE] = "CM CORE COREAON",
	[CM_DRA7XX_CORE_CM_CORE] = "CM CORE CORE",
	[CM_DRA7XX_CUSTEFUSE_CM_CORE] = "CM CORE CUSTEFUSE",
	[CM_DRA7XX_DSS_CM_CORE] = "CM CORE DSS",
	[CM_DRA7XX_GPU_CM_CORE] = "CM CORE GPU",
	[CM_DRA7XX_IVA_CM_CORE] = "CM CORE IVA",
	[CM_DRA7XX_L3INIT_CM_CORE] = "CM CORE L3INIT",
	[CM_DRA7XX_L4PER_CM_CORE] = "CM CORE L4PER",
	[CM_DRA7XX_OCP_SOCKET_CM_CORE] = "CM CORE OCP SOCKET",
	[CM_DRA7XX_RESTORE_CM_CORE] = "CM CORE RESTORE",
	[CM_DRA7XX_CKGEN_CM_CORE_AON] = "CM CORE AON CKGEN",
	[CM_DRA7XX_CKGEN_CM_CORE] = "CM CORE CKGEN",
	[CM_DRA7XX_EMU_CM] = "CM EMU",
	[CM_DRA7XX_WKUPAON_CM] = "CM WKUPAON"};


const dpll_settings_regs dpll_dra7xx_regs[DPLL_DRA7XX_ID_MAX] = {
	{&dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_mpu,
		&dra7xx_ckgen_cm_core_aon_cm_idlest_dpll_mpu,
		&dra7xx_ckgen_cm_core_aon_cm_autoidle_dpll_mpu,
		&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_mpu,
		&dra7xx_ckgen_cm_core_aon_cm_bypclk_dpll_mpu,
		&dra7xx_ckgen_cm_core_aon_cm_div_m2_dpll_mpu,
		NULL,
		&dra7xx_ckgen_cm_core_aon_cm_ssc_deltamstep_dpll_mpu,
		&dra7xx_ckgen_cm_core_aon_cm_ssc_modfreqdiv_dpll_mpu,
		NULL},
	{&dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_iva,
		&dra7xx_ckgen_cm_core_aon_cm_idlest_dpll_iva,
		&dra7xx_ckgen_cm_core_aon_cm_autoidle_dpll_iva,
		&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_iva,
		&dra7xx_ckgen_cm_core_aon_cm_bypclk_dpll_iva,
		&dra7xx_ckgen_cm_core_aon_cm_div_m2_dpll_iva,
		&dra7xx_ckgen_cm_core_aon_cm_div_m3_dpll_iva,
		&dra7xx_ckgen_cm_core_aon_cm_ssc_deltamstep_dpll_iva,
		&dra7xx_ckgen_cm_core_aon_cm_ssc_modfreqdiv_dpll_iva,
		NULL},
	{&dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_core,
		&dra7xx_ckgen_cm_core_aon_cm_idlest_dpll_core,
		&dra7xx_ckgen_cm_core_aon_cm_autoidle_dpll_core,
		&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_core,
		NULL,
		&dra7xx_ckgen_cm_core_aon_cm_div_m2_dpll_core,
		&dra7xx_ckgen_cm_core_aon_cm_div_m3_dpll_core,
		&dra7xx_ckgen_cm_core_aon_cm_ssc_deltamstep_dpll_core,
		&dra7xx_ckgen_cm_core_aon_cm_ssc_modfreqdiv_dpll_core,
		NULL},
	{&dra7xx_ckgen_cm_core_cm_clkmode_dpll_per,
		&dra7xx_ckgen_cm_core_cm_idlest_dpll_per,
		&dra7xx_ckgen_cm_core_cm_autoidle_dpll_per,
		&dra7xx_ckgen_cm_core_cm_clksel_dpll_per,
		NULL,
		&dra7xx_ckgen_cm_core_cm_div_m2_dpll_per,
		&dra7xx_ckgen_cm_core_cm_div_m3_dpll_per,
		&dra7xx_ckgen_cm_core_cm_ssc_deltamstep_dpll_per,
		&dra7xx_ckgen_cm_core_cm_ssc_modfreqdiv_dpll_per,
		NULL},
	{&dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_abe,
		&dra7xx_ckgen_cm_core_aon_cm_idlest_dpll_abe,
		&dra7xx_ckgen_cm_core_aon_cm_autoidle_dpll_abe,
		&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_abe,
		NULL,
		&dra7xx_ckgen_cm_core_aon_cm_div_m2_dpll_abe,
		&dra7xx_ckgen_cm_core_aon_cm_div_m3_dpll_abe,
		&dra7xx_ckgen_cm_core_aon_cm_ssc_deltamstep_dpll_abe,
		&dra7xx_ckgen_cm_core_aon_cm_ssc_modfreqdiv_dpll_abe,
		NULL},
	{&dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_eve,
		&dra7xx_ckgen_cm_core_aon_cm_idlest_dpll_eve,
		&dra7xx_ckgen_cm_core_aon_cm_autoidle_dpll_eve,
		&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_eve,
		&dra7xx_ckgen_cm_core_aon_cm_bypclk_dpll_eve,
		&dra7xx_ckgen_cm_core_aon_cm_div_m2_dpll_eve,
		&dra7xx_ckgen_cm_core_aon_cm_div_m3_dpll_eve,
		&dra7xx_ckgen_cm_core_aon_cm_ssc_deltamstep_dpll_eve,
		&dra7xx_ckgen_cm_core_aon_cm_ssc_modfreqdiv_dpll_eve,
		NULL},
	{&dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_dsp,
		&dra7xx_ckgen_cm_core_aon_cm_idlest_dpll_dsp,
		&dra7xx_ckgen_cm_core_aon_cm_autoidle_dpll_dsp,
		&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_dsp,
		&dra7xx_ckgen_cm_core_aon_cm_bypclk_dpll_dsp,
		&dra7xx_ckgen_cm_core_aon_cm_div_m2_dpll_dsp,
		&dra7xx_ckgen_cm_core_aon_cm_div_m3_dpll_dsp,
		&dra7xx_ckgen_cm_core_aon_cm_ssc_deltamstep_dpll_dsp,
		&dra7xx_ckgen_cm_core_aon_cm_ssc_modfreqdiv_dpll_dsp,
		NULL},
	{&dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_gmac,
		&dra7xx_ckgen_cm_core_aon_cm_idlest_dpll_gmac,
		&dra7xx_ckgen_cm_core_aon_cm_autoidle_dpll_gmac,
		&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_gmac,
		NULL,
		&dra7xx_ckgen_cm_core_aon_cm_div_m2_dpll_gmac,
		&dra7xx_ckgen_cm_core_aon_cm_div_m3_dpll_gmac,
		&dra7xx_ckgen_cm_core_aon_cm_ssc_deltamstep_dpll_gmac,
		&dra7xx_ckgen_cm_core_aon_cm_ssc_modfreqdiv_dpll_gmac,
		NULL},
	{&dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_gpu,
		&dra7xx_ckgen_cm_core_aon_cm_idlest_dpll_gpu,
		&dra7xx_ckgen_cm_core_aon_cm_autoidle_dpll_gpu,
		&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_gpu,
		NULL,
		&dra7xx_ckgen_cm_core_aon_cm_div_m2_dpll_gpu,
		&dra7xx_ckgen_cm_core_aon_cm_div_m3_dpll_gpu,
		&dra7xx_ckgen_cm_core_aon_cm_ssc_deltamstep_dpll_gpu,
		&dra7xx_ckgen_cm_core_aon_cm_ssc_modfreqdiv_dpll_gpu,
		NULL},
	{&dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_ddr,
		&dra7xx_ckgen_cm_core_aon_cm_idlest_dpll_ddr,
		&dra7xx_ckgen_cm_core_aon_cm_autoidle_dpll_ddr,
		&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_ddr,
		NULL,
		&dra7xx_ckgen_cm_core_aon_cm_div_m2_dpll_ddr,
		&dra7xx_ckgen_cm_core_aon_cm_div_m3_dpll_ddr,
		&dra7xx_ckgen_cm_core_aon_cm_ssc_deltamstep_dpll_ddr,
		&dra7xx_ckgen_cm_core_aon_cm_ssc_modfreqdiv_dpll_ddr,
		NULL},
	{&dra7xx_ckgen_cm_core_cm_clkmode_dpll_usb,
		&dra7xx_ckgen_cm_core_cm_idlest_dpll_usb,
		&dra7xx_ckgen_cm_core_cm_autoidle_dpll_usb,
		&dra7xx_ckgen_cm_core_cm_clksel_dpll_usb,
		NULL,
		&dra7xx_ckgen_cm_core_cm_div_m2_dpll_usb,
		NULL,
		&dra7xx_ckgen_cm_core_cm_ssc_deltamstep_dpll_usb,
		&dra7xx_ckgen_cm_core_cm_ssc_modfreqdiv_dpll_usb,
		&dra7xx_ckgen_cm_core_cm_clkdcoldo_dpll_usb},
	{&dra7xx_ckgen_cm_core_cm_clkmode_dpll_pcie_ref,
		&dra7xx_ckgen_cm_core_cm_idlest_dpll_pcie_ref,
		&dra7xx_ckgen_cm_core_cm_autoidle_dpll_pcie_ref,
		&dra7xx_ckgen_cm_core_cm_clksel_dpll_pcie_ref,
		NULL,
		&dra7xx_ckgen_cm_core_cm_div_m2_dpll_pcie_ref,
		NULL,
		&dra7xx_ckgen_cm_core_cm_ssc_deltamstep_dpll_pcie_ref,
		&dra7xx_ckgen_cm_core_cm_ssc_modfreqdiv_dpll_pcie_ref,
		NULL} };


const reg *dpll_dra7xx_hsdiv_regs[DPLL_DRA7XX_ID_MAX][HSDIV_DRA7XX_ID_MAX] = {
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{&dra7xx_ckgen_cm_core_aon_cm_div_h11_dpll_core,
		&dra7xx_ckgen_cm_core_aon_cm_div_h12_dpll_core,
		&dra7xx_ckgen_cm_core_aon_cm_div_h13_dpll_core,
		&dra7xx_ckgen_cm_core_aon_cm_div_h14_dpll_core,
		&dra7xx_ckgen_cm_core_aon_cm_div_h21_dpll_core,
		&dra7xx_ckgen_cm_core_aon_cm_div_h22_dpll_core,
		&dra7xx_ckgen_cm_core_aon_cm_div_h23_dpll_core,
		&dra7xx_ckgen_cm_core_aon_cm_div_h24_dpll_core},
	{&dra7xx_ckgen_cm_core_cm_div_h11_dpll_per,
		&dra7xx_ckgen_cm_core_cm_div_h12_dpll_per,
		&dra7xx_ckgen_cm_core_cm_div_h13_dpll_per,
		&dra7xx_ckgen_cm_core_cm_div_h14_dpll_per,
		NULL, NULL, NULL, NULL},
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{&dra7xx_ckgen_cm_core_aon_cm_div_h11_dpll_gmac,
		&dra7xx_ckgen_cm_core_aon_cm_div_h12_dpll_gmac,
		&dra7xx_ckgen_cm_core_aon_cm_div_h13_dpll_gmac,
		&dra7xx_ckgen_cm_core_aon_cm_div_h14_dpll_gmac,
		NULL, NULL, NULL, NULL},
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{&dra7xx_ckgen_cm_core_aon_cm_div_h11_dpll_ddr,
		NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL} };
