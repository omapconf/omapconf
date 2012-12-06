/*
 *
 * @Component			OMAPCONF
 * @Filename			vc.h
 * @Description			VOLTAGE CONTROLLER (VC) Common Definitions &
 *				Functions
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


#ifndef __PRCM_VC_H__
#define __PRCM_VC_H__


#include <stdio.h>


short int vc_cmd_values_get(unsigned int prm_vc_val_cmd,
	unsigned char *cmd_on, unsigned char *cmd_onlp,
	unsigned char *cmd_ret, unsigned char *cmd_off);

unsigned char sri2c_is_double_filtering_enabled(
	unsigned int prm_vc_cfg_i2c_mode);
unsigned char sri2c_is_sr_mode_enabled(unsigned int prm_vc_cfg_i2c_mode);
unsigned char sri2c_is_hs_mode_enabled(unsigned int prm_vc_cfg_i2c_mode);
unsigned char sri2c_master_code_get(unsigned int prm_vc_cfg_i2c_mode);

int sri2c_low_clock_cycles_count_get(unsigned int prm_vc_cfg_i2c_mode,
	unsigned int prm_vc_cfg_i2c_clk,
	unsigned char *cycles, double *us);
int sri2c_high_clock_cycles_count_get(unsigned int prm_vc_cfg_i2c_mode,
	unsigned int prm_vc_cfg_i2c_clk,
	unsigned char *cycles, double *us);

int sri2c_config_show(FILE *stream, unsigned int prm_vc_cfg_i2c_mode,
	unsigned int prm_vc_cfg_i2c_clk);


#endif
