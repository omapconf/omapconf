/*
 *
 * @Component			OMAPCONF
 * @Filename			vp44xx-data.c
 * @Description			OMAP4 VOLTAGE PROCESSOR Golden Settings
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


#include <vp44xx-data.h>


const char vp44xx_mod_names[VP44XX_ID_MAX + 1][12] = {
	"VP MPU",
	"VP IVA",
	"VP CORE",
	"FIXME"};


const vp_audit_settings vp4430_mpu_opp50_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = 0x1A, /* 1.025500V */
	.max_voltage = 0x37,
	.min_voltage = 0x0A,
	.error_gain = 0x0F,
	.error_offset = 0,
	.force_update_wait_time = 0x6CE,
	.vstepmax = 0x08,
	.positive_slew_rate = 0x3C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x3C};


const vp_audit_settings vp4430_mpu_opp100_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = 0x30, /* 1.200V */
	.max_voltage = 0x37,
	.min_voltage = 0x0A,
	.error_gain = 0x1B,
	.error_offset = 0,
	.force_update_wait_time = 0x6CE,
	.vstepmax = 0x08,
	.positive_slew_rate = 0x3C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x3C};


const vp_audit_settings vp4430_mpu_oppturbo_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = 0x32, /* 1.325V */
	.max_voltage = 0x37,
	.min_voltage = 0x0A,
	.error_gain = 0x20,
	.error_offset = 0,
	.force_update_wait_time = 0x6CE,
	.vstepmax = 0x08,
	.positive_slew_rate = 0x3C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x3C};


const vp_audit_settings vp4430_mpu_oppnitro_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = 0x37, /* 1.388V */
	.max_voltage = 0x37,
	.min_voltage = 0x0A,
	.error_gain = 0x2C,
	.error_offset = 0,
	.force_update_wait_time = 0x6CE,
	.vstepmax = 0x08,
	.positive_slew_rate = 0x3C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x3C};


const vp_audit_settings vp4430_mpu_oppnitrosb_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = 0x37, /* 1.388V */
	.max_voltage = 0x37,
	.min_voltage = 0x0A,
	.error_gain = 0x30,
	.error_offset = 0,
	.force_update_wait_time = 0x6CE,
	.vstepmax = 0x08,
	.positive_slew_rate = 0x3C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x3C};


const vp_audit_settings *vp4430_mpu_golden_settings[OPP44XX_ID_MAX] = {
	&vp4430_mpu_opp50_golden_settings,
	&vp4430_mpu_opp50_golden_settings,
	&vp4430_mpu_opp100_golden_settings,
	&vp4430_mpu_oppturbo_golden_settings,
	&vp4430_mpu_oppnitro_golden_settings,
	&vp4430_mpu_oppnitrosb_golden_settings};


const vp_audit_settings vp4430_iva_opp50_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = 0x15, /* 0.950V */
	.max_voltage = 0x2F,
	.min_voltage = 0x0A,
	.error_gain = 0x0F,
	.error_offset = 0,
	.force_update_wait_time = 0x6CE,
	.vstepmax = 0x08,
	.positive_slew_rate = 0x3C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x3C};


const vp_audit_settings vp4430_iva_opp100_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = 0x21, /* 1.114V */
	.max_voltage = 0x2F,
	.min_voltage = 0x0A,
	.error_gain = 0x1B,
	.error_offset = 0,
	.force_update_wait_time = 0x6CE,
	.vstepmax = 0x08,
	.positive_slew_rate = 0x3C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x3C};


const vp_audit_settings vp4430_iva_oppturbo_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = 0x2F, /* 1.291V */
	.max_voltage = 0x2F,
	.min_voltage = 0x0A,
	.error_gain = 0x20,
	.error_offset = 0,
	.force_update_wait_time = 0x6CE,
	.vstepmax = 0x08,
	.positive_slew_rate = 0x3C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x3C};


const vp_audit_settings *vp4430_iva_golden_settings[OPP44XX_ID_MAX] = {
	&vp4430_iva_opp50_golden_settings,
	&vp4430_iva_opp50_golden_settings,
	&vp4430_iva_opp100_golden_settings,
	&vp4430_iva_oppturbo_golden_settings,
	NULL,
	NULL};


const vp_audit_settings vp4430_core_opp50_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = 0x15, /* 0.962V */
	.max_voltage = 0x23,
	.min_voltage = 0x0A,
	.error_gain = 0x0F,
	.error_offset = 0,
	.force_update_wait_time = 0x6CE,
	.vstepmax = 0x08,
	.positive_slew_rate = 0x3C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x3C};


const vp_audit_settings vp4430_core_opp100_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = 0x23, /* 1.127V */
	.max_voltage = 0x23,
	.min_voltage = 0x0A,
	.error_gain = 0x1B,
	.error_offset = 0,
	.force_update_wait_time = 0x6CE,
	.vstepmax = 0x08,
	.positive_slew_rate = 0x3C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x3C};


const vp_audit_settings *vp4430_core_golden_settings[OPP44XX_ID_MAX] = {
	&vp4430_core_opp50_golden_settings,
	&vp4430_core_opp50_golden_settings,
	&vp4430_core_opp100_golden_settings,
	NULL,
	NULL,
	NULL};


const vp_audit_settings **vp4430_golden_settings[VP44XX_ID_MAX] = {
	(const vp_audit_settings **) &vp4430_mpu_golden_settings,
	(const vp_audit_settings **) &vp4430_iva_golden_settings,
	(const vp_audit_settings **) &vp4430_core_golden_settings};


const vp_audit_settings vp4460_mpu_opp50_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = 0x35, /* 1.025500V */
	.max_voltage = 0x58,
	.min_voltage = 0x19,
	.error_gain = 0x11,
	.error_offset = 0,
	.force_update_wait_time = 0x07F8,
	.vstepmax = 0x05,
	.positive_slew_rate = 0x0C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x0C};


const vp_audit_settings vp4460_mpu_opp100_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = 0x47, /* 1.203V */
	.max_voltage = 0x58,
	.min_voltage = 0x19,
	.error_gain = 0x24,
	.error_offset = 0,
	.force_update_wait_time = 0x07F8,
	.vstepmax = 0x05,
	.positive_slew_rate = 0x0C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x0C};


const vp_audit_settings vp4460_mpu_oppturbo_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = 0x52, /* 1.317V */
	.max_voltage = 0x58,
	.min_voltage = 0x19,
	.error_gain = 0x25,
	.error_offset = 0,
	.force_update_wait_time = 0x07F8,
	.vstepmax = 0x05,
	.positive_slew_rate = 0x0C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x0C};


const vp_audit_settings vp4460_mpu_oppnitro_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = 0x58, /* 1.380V */
	.max_voltage = 0x58,
	.min_voltage = 0x19,
	.error_gain = 0x2F,
	.error_offset = 0,
	.force_update_wait_time = 0x07F8,
	.vstepmax = 0x05,
	.positive_slew_rate = 0x0C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x0C};


const vp_audit_settings vp4460_mpu_oppnitrosb_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = 0x58, /* 1.380V */
	.max_voltage = 0x58,
	.min_voltage = 0x19,
	.error_gain = 0x37,
	.error_offset = 0,
	.force_update_wait_time = 0x07F8,
	.vstepmax = 0x05,
	.positive_slew_rate = 0x0C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x0C};


const vp_audit_settings *vp4460_mpu_golden_settings[OPP44XX_ID_MAX] = {
	&vp4460_mpu_opp50_golden_settings,
	&vp4460_mpu_opp50_golden_settings,
	&vp4460_mpu_opp100_golden_settings,
	&vp4460_mpu_oppturbo_golden_settings,
	&vp4460_mpu_oppnitro_golden_settings,
	&vp4460_mpu_oppnitrosb_golden_settings};


const vp_audit_settings vp4460_iva_opp50_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = 0x15, /* 0.950V */
	.max_voltage = 0x36,
	.min_voltage = 0x05,
	.error_gain = 0x0D,
	.error_offset = 0,
	.force_update_wait_time = 0x07F8,
	.vstepmax = 0x04,
	.positive_slew_rate = 0x3C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x3C};


const vp_audit_settings vp4460_iva_opp100_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = 0x21, /* 1.114V */
	.max_voltage = 0x36,
	.min_voltage = 0x05,
	.error_gain = 0x17,
	.error_offset = 0,
	.force_update_wait_time = 0x07F8,
	.vstepmax = 0x04,
	.positive_slew_rate = 0x3C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x3C};


const vp_audit_settings vp4460_iva_oppturbo_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = 0x2F, /* 1.291V */
	.max_voltage = 0x36,
	.min_voltage = 0x05,
	.error_gain = 0x1E,
	.error_offset = 0,
	.force_update_wait_time = 0x07F8,
	.vstepmax = 0x04,
	.positive_slew_rate = 0x3C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x3C};


const vp_audit_settings vp4460_iva_oppnitro_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = 0x36, /* 1.375V */
	.max_voltage = 0x36,
	.min_voltage = 0x05,
	.error_gain = 0x24,
	.error_offset = 0,
	.force_update_wait_time = 0x07F8,
	.vstepmax = 0x04,
	.positive_slew_rate = 0x3C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x3C};


const vp_audit_settings vp4460_iva_oppnitrosb_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = 0x36, /* 1.375V */
	.max_voltage = 0x36,
	.min_voltage = 0x05,
	.error_gain = 0x28,
	.error_offset = 0,
	.force_update_wait_time = 0x07F8,
	.vstepmax = 0x04,
	.positive_slew_rate = 0x3C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x3C};


const vp_audit_settings *vp4460_iva_golden_settings[OPP44XX_ID_MAX] = {
	&vp4460_iva_opp50_golden_settings,
	&vp4460_iva_opp50_golden_settings,
	&vp4460_iva_opp100_golden_settings,
	&vp4460_iva_oppturbo_golden_settings,
	&vp4460_iva_oppnitro_golden_settings,
	&vp4460_iva_oppnitrosb_golden_settings};


const vp_audit_settings vp4460_core_opp50_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = 0x15, /* 0.962V */
	.max_voltage = 0x2C,
	.min_voltage = 0x05,
	.error_gain = 0x0D,
	.error_offset = 0,
	.force_update_wait_time = 0x07F8,
	.vstepmax = 0x04,
	.positive_slew_rate = 0x3C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x3C};


const vp_audit_settings vp4460_core_opp100_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = 0x23, /* 1.127V */
	.max_voltage = 0x2C,
	.min_voltage = 0x05,
	.error_gain = 0x17,
	.error_offset = 0,
	.force_update_wait_time = 0x07F8,
	.vstepmax = 0x04,
	.positive_slew_rate = 0x3C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x3C};


const vp_audit_settings vp4460_core_oppturbo_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = 0x2C, /* 1.250V */
	.max_voltage = 0x2C,
	.min_voltage = 0x05,
	.error_gain = 0x1E,
	.error_offset = 0,
	.force_update_wait_time = 0x07F8,
	.vstepmax = 0x04,
	.positive_slew_rate = 0x3C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x3C};


const vp_audit_settings *vp4460_core_golden_settings[OPP44XX_ID_MAX] = {
	&vp4460_core_opp50_golden_settings,
	&vp4460_core_opp50_golden_settings,
	&vp4460_core_opp100_golden_settings,
	&vp4460_core_oppturbo_golden_settings,
	NULL,
	NULL};


const vp_audit_settings **vp4460_golden_settings[VP44XX_ID_MAX] = {
	(const vp_audit_settings **) &vp4460_mpu_golden_settings,
	(const vp_audit_settings **) &vp4460_iva_golden_settings,
	(const vp_audit_settings **) &vp4460_core_golden_settings};


#if 0 /* FIXME when OMAP4470 golden settings available */
const vp_audit_settings vp4470_mpu_opp50_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = , /* 1.V */
	.max_voltage = ,
	.min_voltage = ,
	.error_gain = ,
	.error_offset = 0,
	.force_update_wait_time = 0x07F8,
	.vstepmax = ,
	.positive_slew_rate = 0x3C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x3C};


const vp_audit_settings vp4470_mpu_opp100_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = , /* 1.V */
	.max_voltage = ,
	.min_voltage = ,
	.error_gain = ,
	.error_offset = 0,
	.force_update_wait_time = 0x07F8,
	.vstepmax = ,
	.positive_slew_rate = 0x3C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x3C};


const vp_audit_settings vp4470_mpu_oppturbo_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = , /* 1.V */
	.max_voltage = ,
	.min_voltage = ,
	.error_gain = ,
	.error_offset = 0,
	.force_update_wait_time = 0x07F8,
	.vstepmax = ,
	.positive_slew_rate = 0x3C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x3C};


const vp_audit_settings vp4470_mpu_oppnitro_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = , /* 1.V */
	.max_voltage = ,
	.min_voltage = ,
	.error_gain = ,
	.error_offset = 0,
	.force_update_wait_time = 0x07F8,
	.vstepmax = ,
	.positive_slew_rate = 0x3C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x3C};


const vp_audit_settings vp4470_mpu_oppnitrosb_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = , /* 1.V */
	.max_voltage = ,
	.min_voltage = ,
	.error_gain = ,
	.error_offset = 0,
	.force_update_wait_time = 0x07F8,
	.vstepmax = ,
	.positive_slew_rate = 0x3C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x3C};


const vp_audit_settings *vp4470_mpu_golden_settings[OPP44XX_ID_MAX] = {
	&vp4470_mpu_opp50_golden_settings,
	&vp4470_mpu_opp50_golden_settings,
	&vp4470_mpu_opp100_golden_settings,
	&vp4470_mpu_oppturbo_golden_settings,
	&vp4470_mpu_oppnitro_golden_settings,
	&vp4470_mpu_oppnitrosb_golden_settings};


const vp_audit_settings vp4470_iva_opp50_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = , /* 1.V */
	.max_voltage = ,
	.min_voltage = ,
	.error_gain = ,
	.error_offset = 0,
	.force_update_wait_time = 0x07F8,
	.vstepmax = ,
	.positive_slew_rate = 0x3C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x3C};


const vp_audit_settings vp4470_iva_opp100_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = , /* 1.V */
	.max_voltage = ,
	.min_voltage = ,
	.error_gain = ,
	.error_offset = 0,
	.force_update_wait_time = 0x07F8,
	.vstepmax = ,
	.positive_slew_rate = 0x3C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x3C};


const vp_audit_settings *vp4470_iva_golden_settings[OPP44XX_ID_MAX] = {
	&vp4470_iva_opp50_golden_settings,
	&vp4470_iva_opp50_golden_settings,
	&vp4470_iva_opp100_golden_settings,
	&vp4470_iva_oppturbo_golden_settings,
	&vp4470_iva_oppnitro_golden_settings,
	&vp4470_iva_oppnitrosb_golden_settings};


const vp_audit_settings vp4470_core_opp50_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = , /* 1.V */
	.max_voltage = ,
	.min_voltage = ,
	.error_gain = ,
	.error_offset = 0,
	.force_update_wait_time = 0x07F8,
	.vstepmax = ,
	.positive_slew_rate = 0x3C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x3C};


const vp_audit_settings vp4470_core_opp100_golden_settings = {
	.mode = 1,
	.vc_timeout_mode = 1,
	.vc_timeout_cycles = 0x1E00,
	.init_voltage = , /* 1.V */
	.max_voltage = ,
	.min_voltage = ,
	.error_gain = ,
	.error_offset = 0,
	.force_update_wait_time = 0x07F8,
	.vstepmax = ,
	.positive_slew_rate = 0x3C,
	.vstepmin = 0x01,
	.negative_slew_rate = 0x3C};


const vp_audit_settings *vp4470_core_golden_settings[OPP44XX_ID_MAX] = {
	&vp4470_core_opp50_golden_settings,
	&vp4470_core_opp50_golden_settings,
	&vp4470_core_opp100_golden_settings,
	&vp4470_core_oppturbo_golden_settings,
	NULL,
	NULL};
#endif


const vp_audit_settings ***vp44xx_golden_settings[OMAP_MAX] = {
	(const vp_audit_settings ***) &vp4430_golden_settings,
	(const vp_audit_settings ***) &vp4460_golden_settings,
	#if 1 /* FIXME when OMAP4470 golden settings available */
	NULL,
	#else
	(const vp_audit_settings ***) &vp4470_golden_settings,
	#endif
	NULL,
	NULL};
