/*
 *
 * @Component			OMAPCONF
 * @Filename			sr.h
 * @Description			SMARTREFLEX Common Definitions & Functions
 * @Author			Patrick Titiano (p-titiano@ti.com)
 * @Date			2006
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2006 Texas Instruments Incorporated - http://www.ti.com/
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


#ifndef __SR_H__
#define __SR_H__


#include <stdio.h>
#include <prcm-module.h>


#define SR_SENSOR_TYPE_MAX_LENGTH		8
#define SR_SENSOR_VAL_TYPE_MAX_LENGTH		8
#define SR_SENSOR_VAL_STATUS_MAX_LENGTH		16
#define SR_IRQ_TYPE_MAX_LENGTH			16


typedef struct {
	unsigned char accessible;
	unsigned int srconfig;
	unsigned int srstatus;
	unsigned int senval;
	unsigned int senmin;
	unsigned int senmax;
	unsigned int senavg;
	unsigned int avgweight;
	unsigned int nvaluereciprocal;
	unsigned int irqstatus_raw;
	unsigned int irqstatus;
	unsigned int irqenable_set;
	unsigned int senerror;
	unsigned int errconfig;
	/* OMAP5+ only */
	unsigned int lvtsenval;
	unsigned int lvtsenmin;
	unsigned int lvtsenmax;
	unsigned int lvtsenavg;
	unsigned int lvtnvaluereciprocal;
} sr_registers;


typedef struct {
	unsigned char enabled;
	unsigned int srconfig;
	unsigned int senerror;
	unsigned int errconfig;
	unsigned int vp_config;
} sr_status_registers;


typedef enum {
	SR_SENSOR_N,
	SR_SENSOR_P,
	SR_SENSOR_TYPE_MAX,
} sr_sensor_type;


typedef enum {
	SR_SENSOR_VAL_LATEST,
	SR_SENSOR_VAL_MIN,
	SR_SENSOR_VAL_MAX,
	SR_SENSOR_VAL_AVG,
	SR_SENSOR_VAL_TYPE_MAX,
} sr_sensor_value_type;


typedef enum {
	SR_SENSOR_VAL_INVALID,
	SR_SENSOR_VAL_VALID,
	SR_SENSOR_VAL_FINAL,
	SR_SENSOR_VAL_STATUS_MAX
} sr_sensor_value_status;


typedef enum {
	SR_IRQ_MCUDISABLEACK,
	SR_IRQ_MCUBOUNDS,
	SR_IRQ_MCUVALID,
	SR_IRQ_MCUACCUM,
	SR_IRQ_VPBOUNDS,
	SR_IRQ_TYPE_MAX
} sr_interrupt_type;


typedef struct {
	double sr_sysclk; /* in KHz */
	unsigned char irqmode[SR_IRQ_TYPE_MAX];
	unsigned char sensornmode;
	unsigned char sensorpmode;
	unsigned char minmaxavg_detector_mode;
	unsigned char errgen_mode;
	mod_idle_mode idle_mode;
	unsigned char wakeupenable;
	signed char errminlimit;
	signed char errmaxlimit;
	unsigned char errweight;
	unsigned char converged;
} sr_audit_settings;


int sr_config_show(FILE *stream, sr_registers sr_regs[3]);
int sr_convergence_status_show(FILE *stream, sr_status_registers sr_regs[3]);
int sr_config_audit(FILE *stream, const char *sr_name, const char *opp_name,
	sr_registers *sr_regs, const sr_audit_settings *sr_golden_settings,
	unsigned int *err_nbr, unsigned int *wng_nbr);

const char *sr_sensor_type_name_get(sr_sensor_type type);
const char *sr_sensor_value_type_name_get(sr_sensor_value_type type);
const char *sr_sensor_value_status_name_get(sr_sensor_value_status status);
const char *sr_interrupt_type_name_get(sr_interrupt_type type);

/* Smart-Reflex module-related functions */
unsigned char sr_is_enabled(unsigned int sr_config);
unsigned char sr_has_converged(unsigned int errconfig, unsigned int senerror);
unsigned char sr_clk_div_get(unsigned int sr_config);
double sr_clk_rate_get(unsigned int sr_config, double sr_sysclk);
unsigned char sr_is_minmaxavg_detector_enabled(unsigned int sr_config);
unsigned char sr_accumdata_count_get(unsigned int sr_config);
unsigned char sr_avg_weighting_factor_get(unsigned int avgweight,
	sr_sensor_type type);

/* Smart-Reflex Error Generator-related functions */
unsigned char sr_is_error_generator_enabled(unsigned int sr_config);
mod_idle_mode sr_error_generator_idle_mode_get(unsigned int errconfig);
unsigned char sr_is_error_generator_wakeup_enabled(unsigned int errconfig);
double sr_error_generator_limit_hex2percent(signed char limit);
unsigned char sr_error_generator_minlimit_get(unsigned int errconfig);
double sr_error_generator_minlimit_percentage_get(unsigned int errconfig);
unsigned char sr_error_generator_maxlimit_get(unsigned int errconfig);
double sr_error_generator_maxlimit_percentage_get(unsigned int errconfig);
unsigned char sr_error_generator_weight_get(unsigned int errconfig);
sr_sensor_value_status sr_sensor_error_value_status_get(
	unsigned int srstatus);
unsigned char sr_sensor_error_value_get(unsigned int senerror);
double sr_sensor_error_percentage_get(unsigned int senerror);
sr_sensor_value_status sr_avg_sensor_error_value_status_get(
	unsigned int srstatus);
unsigned char sr_avg_sensor_error_value_get(unsigned int senerror);
double sr_avg_sensor_error_percentage_get(unsigned int senerror);
double sr_delta_vdd_get(double freq_error, double vp_offset, double vp_gain);

/* Smart-Reflex Sensors-related functions */
unsigned char sr_is_sensors_disabled(unsigned int sr_config);
unsigned char sr_is_sensor_enabled(unsigned int sr_config, sr_sensor_type type);
unsigned char sr_gain_get(unsigned int nvaluereciprocal, sr_sensor_type type);
unsigned char sr_scale_value_get(unsigned int nvaluereciprocal,
	sr_sensor_type type);
unsigned int sr_ntarget_get(unsigned int nvaluereciprocal, sr_sensor_type type);
sr_sensor_value_status sr_sensor_value_status_get(unsigned int srstatus);
unsigned int sr_sensor_value_get(sr_registers *sr_regs, sr_sensor_type sen_type,
	sr_sensor_value_type val_type);
unsigned int sr_lvt_sensor_value_get(sr_registers *sr_regs,
	sr_sensor_type sen_type, sr_sensor_value_type val_type);

/* Smart-Reflex IRQ-related functions */
unsigned char sr_irq_is_enabled(unsigned int irqenable_set,
	unsigned int errconfig, sr_interrupt_type type);
unsigned char sr_irq_status_is_set(unsigned int irqstatus,
	unsigned int errconfig, sr_interrupt_type type);
unsigned char sr_irq_raw_status_is_set(unsigned int irqstatus_raw,
	sr_interrupt_type type);

/* Smart-Reflex LVT Sensors-related functions */
unsigned char sr_is_lvt_sensors_disabled(unsigned int sr_config);
unsigned char sr_is_lvt_sensor_enabled(unsigned int sr_config,
	sr_sensor_type type);


#endif
