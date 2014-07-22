/*
 *
 * @Component			OMAPCONF
 * @Filename			prm_am335x-defs.h
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


#ifndef __PRM_AM335X_DEFS_H__
#define __PRM_AM335X_DEFS_H__


#include <reg.h>

/* PRM_IRQ Registers */
#define AM335X_REVISION_PRM					0x44E00B00
extern reg am335x_revision_prm;
#define AM335X_PRM_IRQSTATUS_MPU				0x44E00B04
extern reg am335x_prm_irqstatus_mpu;
#define AM335X_PRM_IRQENABLE_MPU				0x44E00B08
extern reg am335x_prm_irqenable_mpu;
#define AM335X_PRM_IRQSTATUS_M3					0x44E00B0C
extern reg am335x_prm_irqstatus_m3;
#define AM335X_PRM_IRQENABLE_M3					0x44E00B10
extern reg am335x_prm_irqenable_m3;
#define AM335X_PRM_IRQ_MOD_REGCOUNT				5
extern reg *am335x_prm_irq_mod[AM335X_PRM_IRQ_MOD_REGCOUNT + 1];

/* PRM_PER Registers */
#define AM335X_RM_PER_RSTCTRL					0x44E00C00
extern reg am335x_rm_per_rstctrl;
#define AM335X_PM_PER_PWRSTST					0x44E00C08
extern reg am335x_pm_per_pwrstst;
#define AM335X_PM_PER_PWRSTCTRL					0x44E00C0C
extern reg am335x_pm_per_pwrstctrl;
#define AM335X_PRM_PER_MOD_REGCOUNT				3
extern reg *am335x_prm_per_mod[AM335X_PRM_PER_MOD_REGCOUNT + 1];

/* PRM_WKUP Registers */
#define AM335X_RM_WKUP_RSTCTRL					0x44E00D00
extern reg am335x_rm_wkup_rstctrl;
#define AM335X_PM_WKUP_PWRSTCTRL				0x44E00D04
extern reg am335x_pm_wkup_pwrstctrl;
#define AM335X_PM_WKUP_PWRSTST					0x44E00D08
extern reg am335x_pm_wkup_pwrstst;
#define AM335X_RM_WKUP_RSTST					0x44E00D0C
extern reg am335x_rm_wkup_rstst;
#define AM335X_PRM_WKUP_MOD_REGCOUNT				4
extern reg *am335x_prm_wkup_mod[AM335X_PRM_WKUP_MOD_REGCOUNT + 1];

/* PRM_MPU Registers */
#define AM335X_PM_MPU_PWRSTCTRL					0x44E00E00
extern reg am335x_pm_mpu_pwrstctrl;
#define AM335X_PM_MPU_PWRSTST					0x44E00E04
extern reg am335x_pm_mpu_pwrstst;
#define AM335X_RM_MPU_RSTST					0x44E00E08
extern reg am335x_rm_mpu_rstst;
#define AM335X_PRM_MPU_MOD_REGCOUNT				3
extern reg *am335x_prm_mpu_mod[AM335X_PRM_MPU_MOD_REGCOUNT + 1];

/* PRM_DEVICE Registers */
#define AM335X_PRM_RSTCTRL					0x44E00F00
extern reg am335x_prm_rstctrl;
#define AM335X_PRM_RSTTIME					0x44E00F04
extern reg am335x_prm_rsttime;
#define AM335X_PRM_RSTST					0x44E00F08
extern reg am335x_prm_rstst;
#define AM335X_PRM_SRAM_COUNT					0x44E00F0C
extern reg am335x_prm_sram_count;
#define AM335X_PRM_LDO_SRAM_CORE_SETUP				0x44E00F10
extern reg am335x_prm_ldo_sram_core_setup;
#define AM335X_PRM_LDO_SRAM_CORE_CTRL				0x44E00F14
extern reg am335x_prm_ldo_sram_core_ctrl;
#define AM335X_PRM_LDO_SRAM_MPU_SETUP				0x44E00F18
extern reg am335x_prm_ldo_sram_mpu_setup;
#define AM335X_PRM_LDO_SRAM_MPU_CTRL				0x44E00F1C
extern reg am335x_prm_ldo_sram_mpu_ctrl;
#define AM335X_PRM_DEVICE_MOD_REGCOUNT				8
extern reg *am335x_prm_device_mod[AM335X_PRM_DEVICE_MOD_REGCOUNT + 1];

/* PRM_RTC Registers */
#define AM335X_PM_RTC_PWRSTCTRL					0x44E01000
extern reg am335x_pm_rtc_pwrstctrl;
#define AM335X_PM_RTC_PWRSTST					0x44E01004
extern reg am335x_pm_rtc_pwrstst;
#define AM335X_PRM_RTC_MOD_REGCOUNT				2
extern reg *am335x_prm_rtc_mod[AM335X_PRM_RTC_MOD_REGCOUNT + 1];

/* PRM_GFX Registers */
#define AM335X_PM_GFX_PWRSTCTRL					0x44E01100
extern reg am335x_pm_gfx_pwrstctrl;
#define AM335X_RM_GFX_RSTCTRL					0x44E01104
extern reg am335x_rm_gfx_rstctrl;
#define AM335X_PM_GFX_PWRSTST					0x44E01110
extern reg am335x_pm_gfx_pwrstst;
#define AM335X_RM_GFX_RSTST					0x44E01114
extern reg am335x_rm_gfx_rstst;
#define AM335X_PRM_GFX_MOD_REGCOUNT				4
extern reg *am335x_prm_gfx_mod[AM335X_PRM_GFX_MOD_REGCOUNT + 1];

/* PRM_CEFUSE Registers */
#define AM335X_PM_CEFUSE_PWRSTCTRL				0x44E01200
extern reg am335x_pm_cefuse_pwrstctrl;
#define AM335X_PM_CEFUSE_PWRSTST				0x44E01204
extern reg am335x_pm_cefuse_pwrstst;
#define AM335X_PRM_CEFUSE_MOD_REGCOUNT				2
extern reg *am335x_prm_cefuse_mod[AM335X_PRM_CEFUSE_MOD_REGCOUNT + 1];

typedef enum {
	PRM_AM335X_PRM_IRQ,
	PRM_AM335X_PRM_PER,
	PRM_AM335X_PRM_WKUP,
	PRM_AM335X_PRM_MPU,
	PRM_AM335X_PRM_DEVICE,
	PRM_AM335X_PRM_RTC,
	PRM_AM335X_PRM_GFX,
	PRM_AM335X_PRM_CEFUSE,
	PRM_AM335X_MODS_COUNT
} prm_am335x_mod_id;

extern reg **prm_am335x_mods[PRM_AM335X_MODS_COUNT + 1];

extern const char *prm_am335x_mods_name[PRM_AM335X_MODS_COUNT];


#endif
