/*
 *
 * @Component			OMAPCONF
 * @Filename			vp.h
 * @Description			VOLTAGE PROCESSOR (VP) Common Definitions
 *				& Functions
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


#ifndef __PRCM_VP_H__
#define __PRCM_VP_H__


#include <stdio.h>


typedef struct {
	unsigned short vdd_id;
	unsigned int vp_config;
	unsigned int vp_status;
	unsigned int vp_vlimitto;
	unsigned int vp_voltage;
	unsigned int vp_vstepmax;
	unsigned int vp_vstepmin;
} vp_registers;


typedef struct {
	unsigned char mode;
	unsigned char vc_timeout_mode;
	unsigned int vc_timeout_cycles;
	unsigned char init_voltage;
	unsigned char max_voltage;
	unsigned char min_voltage;
	signed char error_gain;
	signed char error_offset;
	unsigned int force_update_wait_time;
	unsigned int vstepmax;
	unsigned int positive_slew_rate;
	unsigned int vstepmin;
	unsigned int negative_slew_rate;
} vp_audit_settings;


int vp_error_offset_get(unsigned int vp_config,
	signed char *offset_raw, double *offset);
double vp_error_offset_hex2percent(signed char offset);
int vp_error_gain_get(unsigned int vp_config, unsigned short vdd_id,
	signed char *gain_raw, double *gain);
double vp_error_gain_hex2percent(signed char gain, unsigned short vdd_id);
int vp_init_voltage_get(unsigned int vp_config,
	unsigned short vdd_id, unsigned char *init_vsel,
	unsigned int *init_uv);
unsigned char vp_vc_timeout_is_enabled(unsigned int vp_config);
unsigned char vp_is_enabled(unsigned int vp_config);
unsigned char vp_is_idle(unsigned int vp_status);
int vp_min_voltage_get(unsigned int vp_vlimitto, unsigned short vdd_id,
	unsigned char *min_vsel, unsigned int *min_uv);
int vp_max_voltage_get(unsigned int vp_vlimitto, unsigned short vdd_id,
	unsigned char *max_vsel, unsigned int *max_uv);
int vp_last_voltage_get(unsigned int vp_voltage, unsigned short vdd_id,
	unsigned char *vsel, unsigned int *uv);
int vp_vc_timeout_get(unsigned int vp_vlimitto,
	unsigned int *timeout_cycles, unsigned int *timeout_us);
int vp_force_update_wait_time_get(unsigned int vp_voltage,
	unsigned int *time_cycles, unsigned int *time_us);
int vp_max_step_get(unsigned int vp_vstepmax, unsigned short vdd_id,
	unsigned int *max_step, unsigned int *max_uv);
int vp_min_step_get(unsigned int vp_vstepmin, unsigned short vdd_id,
	unsigned int *min_step, unsigned int *min_uv);
int vp_positive_slew_rate_get(unsigned int vp_vstepmax,
	unsigned int *cycles, unsigned int *us);
int vp_negative_slew_rate_get(unsigned int vp_vstepmin,
	unsigned int *cycles, unsigned int *us);
int vp_slew_rate_cycles2us(unsigned int cycles);

int vp_config_show(FILE *stream, vp_registers vp_regs[3]);
int vp_config_audit(FILE *stream, const char *vp_name, const char *opp_name,
	vp_registers *vp_regs, const vp_audit_settings *vp_golden_settings,
	unsigned int *err_nbr, unsigned int *wng_nbr);


#endif
