/*
 *
 * @Component			OMAPCONF
 * @Filename			clkdm.h
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


#ifndef __CLKDM_H__
#define __CLKDM_H__


#include <reg.h>
#include <genlist.h>


#define CLKDM_EMU			((const char *) "EMU")
#define CLKDM_WKUPAON			((const char *) "WKUPAON")
#define CLKDM_COREAON			((const char *) "COREAON")
#define CLKDM_CAM			((const char *) "CAM")
#define CLKDM_L4_CFG			((const char *) "L4_CFG")
#define CLKDM_EMIF			((const char *) "EMIF")
#define CLKDM_IPU			((const char *) "IPU")
#define CLKDM_L3_MAIN2			((const char *) "L3_MAIN2")
#define CLKDM_L3_INSTR			((const char *) "L3_INSTR")
#define CLKDM_L3_MAIN1			((const char *) "L3_MAIN1")
#define CLKDM_C2C			((const char *) "C2C")
#define CLKDM_DMA			((const char *) "DMA")
#define CLKDM_MIPIEXT			((const char *) "MIPIEXT")
#define CLKDM_DSS			((const char *) "DSS")
#define CLKDM_CUST_EFUSE		((const char *) "CUST_EFUSE")
#define CLKDM_L3_INIT			((const char *) "L3_INIT")
#define CLKDM_L4_PER			((const char *) "L4_PER")
#define CLKDM_L4_SEC			((const char *) "L4_SEC")
#define CLKDM_ABE			((const char *) "ABE")
#define CLKDM_DSP			((const char *) "DSP")
#define CLKDM_GPU			((const char *) "GPU")
#define CLKDM_IVA			((const char *) "IVA")
#define CLKDM_MPU			((const char *) "MPU")
#define CLKDM_NONE			((const char *) "NONE")
#define CLKDM_UNKNOWN			((const char *) "UNKNOWN")


typedef struct {
	const char *name;
	int id;
	const char *pwrdm;
	const char *voltdm;
	reg *clkstctrl;
	int properties;
} clkdm_info;


void clkdm_init(void);
void clkdm_deinit(void);

int clkdm_count_get(void);
const genlist *clkdm_list_get(void);



#endif
