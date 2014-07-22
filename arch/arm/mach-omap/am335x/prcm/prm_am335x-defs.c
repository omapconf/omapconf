/*
 *
 * @Component			OMAPCONF
 * @Filename			prm_am335x-defs.c
 * @Description			AM335X PRM Register Definitions & Functions
 * @Author			Gilberto Rodriguez <gilrod@ti.com>
 * @Date			2014
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
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


#include <prm_am335x-defs.h>
#include <stdio.h>

reg am335x_revision_prm = {
	"REVISION_PRM",
	AM335X_REVISION_PRM,
	0xDEADBEEF,
	0};

reg am335x_prm_irqstatus_mpu = {
	"PRM_IRQSTATUS_MPU",
	AM335X_PRM_IRQSTATUS_MPU,
	0xDEADBEEF,
	0};

reg am335x_prm_irqenable_mpu = {
	"PRM_IRQENABLE_MPU",
	AM335X_PRM_IRQENABLE_MPU,
	0xDEADBEEF,
	0};

reg am335x_prm_irqstatus_m3 = {
	"PRM_IRQSTATUS_M3",
	AM335X_PRM_IRQSTATUS_M3,
	0xDEADBEEF,
	0};

reg am335x_prm_irqenable_m3 = {
	"PRM_IRQENABLE_M3",
	AM335X_PRM_IRQENABLE_M3,
	0xDEADBEEF,
	0};

reg *am335x_prm_irq_mod[AM335X_PRM_IRQ_MOD_REGCOUNT + 1] = {
	&am335x_revision_prm,
	&am335x_prm_irqstatus_mpu,
	&am335x_prm_irqenable_mpu,
	&am335x_prm_irqstatus_m3,
	&am335x_prm_irqenable_m3,
	NULL};

reg am335x_rm_per_rstctrl = {
	"RM_PER_RSTCTRL",
	AM335X_RM_PER_RSTCTRL,
	0xDEADBEEF,
	0};

reg am335x_pm_per_pwrstst = {
	"PM_PER_PWRSTST",
	AM335X_PM_PER_PWRSTST,
	0xDEADBEEF,
	0};

reg am335x_pm_per_pwrstctrl = {
	"PM_PER_PWRSTCTRL",
	AM335X_PM_PER_PWRSTCTRL,
	0xDEADBEEF,
	0};

reg *am335x_prm_per_mod[AM335X_PRM_PER_MOD_REGCOUNT + 1] = {
	&am335x_rm_per_rstctrl,
	&am335x_pm_per_pwrstst,
	&am335x_pm_per_pwrstctrl,
	NULL};

reg am335x_rm_wkup_rstctrl = {
	"RM_WKUP_RSTCTRL",
	AM335X_RM_WKUP_RSTCTRL,
	0xDEADBEEF,
	0};

reg am335x_pm_wkup_pwrstctrl = {
	"PM_WKUP_PWRSTCTRL",
	AM335X_PM_WKUP_PWRSTCTRL,
	0xDEADBEEF,
	0};

reg am335x_pm_wkup_pwrstst = {
	"PM_WKUP_PWRSTST",
	AM335X_PM_WKUP_PWRSTST,
	0xDEADBEEF,
	0};

reg am335x_rm_wkup_rstst = {
	"RM_WKUP_RSTST",
	AM335X_RM_WKUP_RSTST,
	0xDEADBEEF,
	0};

reg *am335x_prm_wkup_mod[AM335X_PRM_WKUP_MOD_REGCOUNT + 1] = {
	&am335x_rm_wkup_rstctrl,
	&am335x_pm_wkup_pwrstctrl,
	&am335x_pm_wkup_pwrstst,
	&am335x_rm_wkup_rstst,
	NULL};

reg am335x_pm_mpu_pwrstctrl = {
	"PM_MPU_PWRSTCTRL",
	AM335X_PM_MPU_PWRSTCTRL,
	0xDEADBEEF,
	0};

reg am335x_pm_mpu_pwrstst = {
	"PM_MPU_PWRSTST",
	AM335X_PM_MPU_PWRSTST,
	0xDEADBEEF,
	0};

reg am335x_rm_mpu_rstst = {
	"RM_MPU_RSTST",
	AM335X_RM_MPU_RSTST,
	0xDEADBEEF,
	0};

reg *am335x_prm_mpu_mod[AM335X_PRM_MPU_MOD_REGCOUNT + 1] = {
	&am335x_pm_mpu_pwrstctrl,
	&am335x_pm_mpu_pwrstst,
	&am335x_rm_mpu_rstst,
	NULL};

reg am335x_prm_rstctrl = {
	"PRM_RSTCTRL",
	AM335X_PRM_RSTCTRL,
	0xDEADBEEF,
	0};

reg am335x_prm_rsttime = {
	"PRM_RSTTIME",
	AM335X_PRM_RSTTIME,
	0xDEADBEEF,
	0};

reg am335x_prm_rstst = {
	"PRM_RSTST",
	AM335X_PRM_RSTST,
	0xDEADBEEF,
	0};

reg am335x_prm_sram_count = {
	"PRM_SRAM_COUNT",
	AM335X_PRM_SRAM_COUNT,
	0xDEADBEEF,
	0};

reg am335x_prm_ldo_sram_core_setup = {
	"PRM_LDO_SRAM_CORE_SETUP",
	AM335X_PRM_LDO_SRAM_CORE_SETUP,
	0xDEADBEEF,
	0};

reg am335x_prm_ldo_sram_core_ctrl = {
	"PRM_LDO_SRAM_CORE_CTRL",
	AM335X_PRM_LDO_SRAM_CORE_CTRL,
	0xDEADBEEF,
	0};

reg am335x_prm_ldo_sram_mpu_setup = {
	"PRM_LDO_SRAM_MPU_SETUP",
	AM335X_PRM_LDO_SRAM_MPU_SETUP,
	0xDEADBEEF,
	0};

reg am335x_prm_ldo_sram_mpu_ctrl = {
	"PRM_LDO_SRAM_MPU_CTRL",
	AM335X_PRM_LDO_SRAM_MPU_CTRL,
	0xDEADBEEF,
	0};

reg *am335x_prm_device_mod[AM335X_PRM_DEVICE_MOD_REGCOUNT + 1] = {
	&am335x_prm_rstctrl,
	&am335x_prm_rsttime,
	&am335x_prm_rstst,
	&am335x_prm_sram_count,
	&am335x_prm_ldo_sram_core_setup,
	&am335x_prm_ldo_sram_core_ctrl,
	&am335x_prm_ldo_sram_mpu_setup,
	&am335x_prm_ldo_sram_mpu_ctrl,
	NULL};

reg am335x_pm_rtc_pwrstctrl = {
	"PM_RTC_PWRSTCTRL",
	AM335X_PM_RTC_PWRSTCTRL,
	0xDEADBEEF,
	0};

reg am335x_pm_rtc_pwrstst = {
	"PM_RTC_PWRSTST",
	AM335X_PM_RTC_PWRSTST,
	0xDEADBEEF,
	0};

reg *am335x_prm_rtc_mod[AM335X_PRM_RTC_MOD_REGCOUNT + 1] = {
	&am335x_pm_rtc_pwrstctrl,
	&am335x_pm_rtc_pwrstst,
	NULL};

reg am335x_pm_gfx_pwrstctrl = {
	"PM_GFX_PWRSTCTRL",
	AM335X_PM_GFX_PWRSTCTRL,
	0xDEADBEEF,
	0};

reg am335x_rm_gfx_rstctrl = {
	"RM_GFX_RSTCTRL",
	AM335X_RM_GFX_RSTCTRL,
	0xDEADBEEF,
	0};

reg am335x_pm_gfx_pwrstst = {
	"PM_GFX_PWRSTST",
	AM335X_PM_GFX_PWRSTST,
	0xDEADBEEF,
	0};

reg am335x_rm_gfx_rstst = {
	"RM_GFX_RSTST",
	AM335X_RM_GFX_RSTST,
	0xDEADBEEF,
	0};

reg *am335x_prm_gfx_mod[AM335X_PRM_GFX_MOD_REGCOUNT + 1] = {
	&am335x_pm_gfx_pwrstctrl,
	&am335x_rm_gfx_rstctrl,
	&am335x_pm_gfx_pwrstst,
	&am335x_rm_gfx_rstst,
	NULL};

reg am335x_pm_cefuse_pwrstctrl = {
	"PM_CEFUSE_PWRSTCTRL",
	AM335X_PM_CEFUSE_PWRSTCTRL,
	0xDEADBEEF,
	0};

reg am335x_pm_cefuse_pwrstst = {
	"PM_CEFUSE_PWRSTST",
	AM335X_PM_CEFUSE_PWRSTST,
	0xDEADBEEF,
	0};

reg *am335x_prm_cefuse_mod[AM335X_PRM_CEFUSE_MOD_REGCOUNT + 1] = {
	&am335x_pm_cefuse_pwrstctrl,
	&am335x_pm_cefuse_pwrstst,
	NULL};

reg **prm_am335x_mods[PRM_AM335X_MODS_COUNT + 1] = {
	(reg **) &am335x_prm_irq_mod,
	(reg **) &am335x_prm_per_mod,
	(reg **) &am335x_prm_wkup_mod,
	(reg **) &am335x_prm_mpu_mod,
	(reg **) &am335x_prm_device_mod,
	(reg **) &am335x_prm_rtc_mod,
	(reg **) &am335x_prm_gfx_mod,
	(reg **) &am335x_prm_cefuse_mod,
	NULL};

const char *prm_am335x_mods_name[PRM_AM335X_MODS_COUNT] = {
	"PRM IRQ",
	"PRM PER",
	"PRM WKUP",
	"PRM MPU",
	"PRM DEVICE",
	"PRM RTC",
	"PRM GFX",
	"PRM CEFUSE"};
