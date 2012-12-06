/*
 *
 * @Component			OMAPCONF
 * @Filename			prcm-module.h
 * @Description			OMAP PRCM Module Definitions & APIs
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


#ifndef __PRCM_MODULE_H__
#define __PRCM_MODULE_H__


#define MODULE_MAX_NAME_LENGTH			32
#define MODULE_MODES_MAX_NAME_LENGTH		32
#define MOD_INTERFACE_TYPE_MAX_NAME_LENGTH	8

#define OPP_MAX					6

#define MOD_HAS_SYSCONFIG			(1 << 0)
#define MOD_HAS_AUTOIDLE_BIT0			(1 << 1) /* bit 0 */
#define MOD_HAS_AUTOIDLE_BIT8			(1 << 2) /* bit 8 (for SLIMBUS) */
#define MOD_HAS_IDLE_MODE3			(1 << 3) /* bits [3-2] */
#define MOD_HAS_IDLE_MODE4			(1 << 4) /* bits [4-3] */
#define MOD_HAS_IDLE_MODE1			(1 << 5) /* bits [1-0] */
#define MOD_HAS_SMART_IDLE_WAKEUP_MODE		(1 << 6) /* mode 0x3 */
#define MOD_HAS_ENAWAKEUP_BIT			(1 << 7) /* bit 2 */
#define MOD_HAS_STANDBY_MODE5			(1 << 8) /* bits [5-4] */
#define MOD_HAS_STANDBY_MODE13			(1 << 9) /* bits [13-12] */
#define MOD_HAS_SMART_STANDBY_WAKEUP_MODE	(1 << 10) /* mode 0x3 */
#define MOD_HAS_CLOCK_ACTIVITY_MODE		(1 << 11) /* bits [9-8] */
#define MOD_HAS_STANDBY_STATUS			(1 << 12) /* CM_CLKCTRL bit 18 */
#define MOD_HAS_NO_IDLE_STATUS			(1 << 13) /* CM_CLKCTRL bit [17-16] */


typedef enum {
	MOD_FREE_RUNNING = 0,
	MOD_AUTOGATING = 1,
	MOD_AUTOIDLE_MODE_MAX
} mod_autoidle_mode;


typedef enum {
	MOD_FORCE_IDLE = 0,
	MOD_NO_IDLE = 1,
	MOD_SMART_IDLE = 2,
	MOD_SMART_IDLE_WAKEUP = 3,
	MOD_IDLE_MODE_MAX
} mod_idle_mode;


typedef enum {
	MOD_FULL_ON = 0x0,
	MOD_IN_TRANSITION = 0x1,
	MOD_OCP_ONLY_IDLE = 0x2,
	MOD_DISABLED = 0x3,
	MOD_IDLE_STATUS_MAX
} mod_idle_status;


typedef enum {
	MOD_FORCE_STANDBY = 0,
	MOD_NO_STANDBY = 1,
	MOD_SMART_STANDBY = 2,
	MOD_STANDBY_MODE_RESERVED = 3,
	MOD_STANDBY_MODE_MAX
} mod_standby_mode;


typedef enum {
	MOD_FUNCTIONAL = 0x0,
	MOD_IN_STANDBY = 0x1,
	MOD_STANDBY_STATUS_MAX
} mod_standby_status;


typedef enum {
	MOD_DISABLED_MODE = 0,
	MOD_HW_AUTO_MODE = 1,
	MOD_ENABLED_MODE = 2,
	MOD_RESERVED_MODE = 3,
	MOD_MODULE_MODE_MAX
} mod_module_mode;


typedef enum {
	MOD_FCLK_AUTO_ICLK_AUTO = 0,
	MOD_FCLK_AUTO_ICLK_ON = 1,
	MOD_FCLK_ON_ICLK_AUTO = 2,
	MOD_FCLK_ON_ICLK_ON = 3,
	MOD_CLOCK_ACTIVITY_MODE_MAX,
} mod_clock_activity_mode;


typedef enum {
	MOD_INTERFACE_MASTER,
	MOD_INTERFACE_SLAVE,
	MOD_INTERFACE_DUAL,
	MOD_INTERFACE_NONE, /* no SYSCONFIG register or only Autoidle bit */
	MOD_INTERFACE_TYPE_MAX
} mod_interface_type;


unsigned int mod_is_accessible(unsigned int cm_clkctrl);
mod_module_mode mod_module_mode_get(unsigned int cm_clkctrl);
mod_idle_status mod_idle_status_get(
	unsigned int cm_clkctrl, unsigned int properties);
mod_standby_status mod_standby_status_get(
	unsigned int cm_clkctrl, unsigned int properties);

mod_autoidle_mode mod_autoidle_mode_get(
	unsigned int sysconfig, unsigned int properties);
mod_idle_mode mod_idle_mode_get(
	unsigned int sysconfig, unsigned int properties);
mod_standby_mode mod_standby_mode_get(
	unsigned int sysconfig, unsigned int properties);
mod_clock_activity_mode mod_clock_activity_mode_get(
	unsigned int sysconfig, unsigned int properties);

int mod_context_is_lost(unsigned int rm_context);

const char *mod_module_mode_name_get(mod_module_mode mode);
const char *mod_autoidle_mode_name_get(mod_autoidle_mode mode);
const char *mod_idle_mode_name_get(mod_idle_mode mode);
const char *mod_standby_mode_name_get(mod_standby_mode mode);
const char *mod_clock_activity_mode_name_get(mod_clock_activity_mode mode);
const char *mod_idle_status_name_get(mod_idle_status status);
const char *mod_standby_status_name_get(mod_standby_status status);


#endif
