/*
 *
 * @Component			OMAPCONF
 * @Filename			clockdomain.h
 * @Description			Clock Domain Generic Definitions & Functions
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


#ifndef __CLOCKDOMAIN_H__
#define __CLOCKDOMAIN_H__


#include <reg.h>
#include <genlist.h>
#include <clkdm.h>
#include <stdio.h>


#define CLKDM_MAX_NAME_LENGTH		16


#define CLKDM_EMU			((const char *) "EMU")
#define CLKDM_WKUP			((const char *) "L4WKUP")
#define CLKDM_WKUPAON			((const char *) "WKUPAON")
#define CLKDM_COREAON			((const char *) "COREAON")
#define CLKDM_CAM			((const char *) "CAM")
#define CLKDM_L4_CFG			((const char *) "L4CFG")
#define CLKDM_EMIF			((const char *) "EMIF")
#define CLKDM_IPU			((const char *) "IPU")
#define CLKDM_MPU_M3			((const char *) "MPU_M3")
#define CLKDM_L3_MAIN2			((const char *) "L3MAIN2")
#define CLKDM_L3_INSTR			((const char *) "L3INSTR")
#define CLKDM_L3_MAIN1			((const char *) "L3MAIN1")
#define CLKDM_C2C			((const char *) "C2C")
#define CLKDM_DMA			((const char *) "DMA")
#define CLKDM_MIPIEXT			((const char *) "MIPIEXT")
#define CLKDM_DSS			((const char *) "DSS")
#define CLKDM_CUST_EFUSE		((const char *) "CUSTEFUSE")
#define CLKDM_L3_INIT			((const char *) "L3INIT")
#define CLKDM_L4_PER			((const char *) "L4PER")
#define CLKDM_L4_SEC			((const char *) "L4SEC")
#define CLKDM_L4_ALWON_CORE		((const char *) "L4_ALWON_CORE")
#define CLKDM_ABE			((const char *) "ABE")
#define CLKDM_DSP			((const char *) "DSP")
#define CLKDM_GPU			((const char *) "GPU")
#define CLKDM_SGX			((const char *) "SGX")
#define CLKDM_IVA			((const char *) "IVA")
#define CLKDM_IVA_HD			((const char *) "IVAHD")
#define CLKDM_MPU			((const char *) "MPU")
#define CLKDM_PER_L4LS			((const char *) "L4_SLOW")
#define CLKDM_PER_L3S			((const char *) "L3_SLOW")
#define CLKDM_PER_L3			((const char *) "L3_FAST")
#define CLKDM_PER_L4HS			((const char *) "L4_FAST")
#define CLKDM_PER_OCPWP_L3		((const char *) "OCPWP")
#define CLKDM_PER_PRU_ICSS		((const char *) "PRU_ICSS")
#define CLKDM_PER_CPSW			((const char *) "CPWS")
#define CLKDM_PER_LCDC			((const char *) "LCDC")
#define CLKDM_PER_CLK_24MHZ		((const char *) "CLK_24MHZ")
#define CLKDM_WKUP_L3_AON		((const char *) "WKUP_L3_AON")
#define CLKDM_WKUP_L4_WKUP_AON		((const char *) "WKUP_L4_AON")
#define CLKDM_RTC			((const char *) "RTC")
#define CLKDM_GFX_L3			((const char *) "GFX_L3")
#define CLKDM_GFX_L4LS_GFX		((const char *) "GFX_L4LS")
#define CLKDM_CEFUSE			((const char *) "CEFUSE")
#define CLKDM_NONE			((const char *) "NONE")
#define CLKDM_UNKNOWN			((const char *) "UNKNOWN")


typedef struct {
	const char *name;
	int id;
	const char *powerdm;
	const char *voltdm;
	reg *clkstctrl;
	unsigned int clkstctrl_bit; /* AM335X only */
	int properties;
} clockdm_info;


void clockdm_init(void);
void clockdm_deinit(void);

int clockdm_count_get(void);
const genlist *clockdm_list_get(void);

int clockdm_id_get(const char *clockdm);
const char *clockdm_powerdm_get(const char *clockdm);
const char *clockdm_voltdm_get(const char *clockdm);
reg *clockdm_clkstctrl_get(const char *clockdm);
unsigned int clockdm_bit_get(const char *clockdm);

clkdm_status clockdm_status_get(const char *clockdm);
clkdm_ctrl_mode clockdm_ctrl_mode_get(const char *clockdm);

int clockdm_config_show(FILE *stream, const char *clockdm);


#endif
