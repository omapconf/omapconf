/*
 *
 * @Component			OMAPCONF
 * @Filename			vc54xx.h
 * @Description			OMAP5 VOLTAGE CONTROLLER (VC) Definitions & Functions
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


#ifndef __PRCM_VC54XX_H__
#define __PRCM_VC54XX_H__


#include <voltdm54xx.h>
#include <reg.h>


#define VC54XX_ERR_NAME_MAX_LENGTH		24


typedef struct {
	unsigned int vc_smps_mpu_config;
	unsigned int vc_smps_mm_config;
	unsigned int vc_smps_core_config;
	unsigned int vc_val_cmd_vdd_mpu_l;
	unsigned int vc_val_cmd_vdd_mm_l;
	unsigned int vc_val_cmd_vdd_core_l;
	unsigned int vc_val_bypass;
	unsigned int vc_mpu_errst;
	unsigned int vc_mm_errst;
	unsigned int vc_core_errst;
	unsigned int vc_bypass_errst;
	unsigned int vc_cfg_i2c_mode;
	unsigned int vc_cfg_i2c_clk;
} vc54xx_registers;


typedef enum {
	VC54XX_VFSM_TIMEOUT_ERR,
	VC54XX_VFSM_RA_ERR,
	VC54XX_VFSM_SA_ERR,
	VC54XX_VFSM_ERR_TYPE_MAX
} vc54xx_vfsm_error_type;


typedef enum {
	VC54XX_SMPS_TIMEOUT_ERR,
	VC54XX_SMPS_RA_ERR,
	VC54XX_SMPS_SA_ERR,
	VC54XX_SMPS_ERR_TYPE_MAX
} vc54xx_smps_error_type;


typedef enum {
	VC54XX_BYPS_TIMEOUT_ERR,
	VC54XX_BYPS_RA_ERR,
	VC54XX_BYPS_SA_ERR,
	VC54XX_BYPS_ERR_TYPE_MAX
} vc54xx_bypass_error_type;


int vc54xx_config_show(FILE *stream, vc54xx_registers *vc_regs);

int vc54xx_registers_get(vc54xx_registers *vc_regs);

short int vc54xx_sa_get(voltdm54xx_id id, vc54xx_registers *vc_regs);
short int vc54xx_volra_get(voltdm54xx_id id, vc54xx_registers *vc_regs);
short int vc54xx_cmdra_get(voltdm54xx_id id, vc54xx_registers *vc_regs);

int vc54xx_raw_cmd_values_get(voltdm54xx_id id, vc54xx_registers *vc_regs,
	unsigned char *cmd_on, unsigned char *cmd_onlp,
	unsigned char *cmd_ret, unsigned char *cmd_off);
int vc54xx_cmd_values_get(voltdm54xx_id id, vc54xx_registers *vc_regs,
	unsigned char *cmd_on, unsigned char *cmd_onlp,
	unsigned char *cmd_ret, unsigned char *cmd_off);

unsigned char vc54xx_no_pending_error(unsigned int prm_vc_errst,
	unsigned int prm_vc_bypass_errst);

unsigned char vc54xx_no_pending_vfsm_error(unsigned int prm_vc_errst);
unsigned char vc54xx_is_vfsm_error_pending(unsigned int prm_vc_errst,
	vc54xx_vfsm_error_type type);
const char *vc54xx_vfsm_error_name_get(vc54xx_vfsm_error_type type);

unsigned char vc54xx_no_pending_smps_error(unsigned int prm_vc_errst);
unsigned char vc54xx_is_smps_error_pending(unsigned int prm_vc_errst,
	vc54xx_smps_error_type type);
const char *vc54xx_smps_error_name_get(vc54xx_smps_error_type type);

unsigned char vc54xx_no_pending_bypass_error(unsigned int prm_vc_bypass_errst);
unsigned char vc54xx_is_bypass_error_pending(unsigned int prm_vc_bypass_errst,
	vc54xx_bypass_error_type type);
const char *vc54xx_bypass_error_name_get(vc54xx_bypass_error_type type);


#endif
