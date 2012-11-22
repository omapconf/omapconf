/*
 *
 * @Component			OMAPCONF
 * @Filename			vc44xx.h
 * @Description			OMAP4 VOLTAGE CONTROLLER (VC) Definitions & Functions
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


#ifndef __PRCM_VC44XX_H__
#define __PRCM_VC44XX_H__


#include <stdio.h>
#include <voltdm44xx.h>


typedef struct {
	unsigned int prm_vc_smps_sa;
	unsigned int prm_vc_smps_ra_vol;
	unsigned int prm_vc_val_smps_ra_cmd;
	unsigned int prm_vc_val_cmd_vdd_core_l;
	unsigned int prm_vc_val_cmd_vdd_mpu_l;
	unsigned int prm_vc_val_cmd_vdd_iva_l;
	unsigned int prm_vc_cfg_channel;
	unsigned int prm_vc_cfg_i2c_mode;
	unsigned int prm_vc_cfg_i2c_clk;
} vc44xx_registers;


short int vc44xx_sa_get(voltdm44xx_id id,
	unsigned int prm_vc_smps_sa, unsigned int prm_vc_cfg_channel);
short int vc44xx_volra_get(voltdm44xx_id id,
	unsigned int prm_vc_cfg_channel, unsigned int prm_vc_val_smps_ra_vol);
short int vc44xx_cmdra_get(voltdm44xx_id id,
	unsigned int prm_vc_cfg_channel, unsigned int prm_vc_val_smps_ra_cmd);
short int vc44xx_raw_cmd_values_get(voltdm44xx_id id, vc44xx_registers *vc_regs,
	unsigned char *cmd_on, unsigned char *cmd_onlp,
	unsigned char *cmd_ret, unsigned char *cmd_off);
short int vc44xx_cmd_values_get(voltdm44xx_id id, vc44xx_registers *vc_regs,
	unsigned char *cmd_on, unsigned char *cmd_onlp,
	unsigned char *cmd_ret, unsigned char *cmd_off);

int vc44xx_registers_get(vc44xx_registers *vc_regs);

int vc44xx_config_show(FILE *stream, vc44xx_registers *vc_regs);


#endif
