/*
 *
 * @Component			OMAPCONF
 * @Filename			powerdomain.h
 * @Description			OMAP Generic Power Domain Definitions & APIs
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


#ifndef __POWERDOMAIN_H__
#define __POWERDOMAIN_H__


#include <reg.h>
#include <genlist.h>


#define PWRDM_EMU			((const char *) "EMU")
#define PWRDM_WKUPAON			((const char *) "WKUPAON")
#define PWRDM_COREAON			((const char *) "COREAON")
#define PWRDM_CAM			((const char *) "CAM")
#define PWRDM_CORE			((const char *) "CORE")
#define PWRDM_DSS			((const char *) "DSS")
#define PWRDM_CUST_EFUSE		((const char *) "CUST_EFUSE")
#define PWRDM_L3_INIT			((const char *) "L3_INIT")
#define PWRDM_L4_PER			((const char *) "L4_PER")
#define PWRDM_ABE			((const char *) "ABE")
#define PWRDM_DSP			((const char *) "DSP")
#define PWRDM_GPU			((const char *) "GPU")
#define PWRDM_MMAON			((const char *) "MMAON")
#define PWRDM_IVA			((const char *) "IVA")
#define PWRDM_MPUAON			((const char *) "MPUAON")
#define PWRDM_MPU			((const char *) "MPU")
#define PWRDM_UNKNOWN			((const char *) "UNKNOWN")


typedef struct {
	const char *name;
	int id;
	const char *voltdm;
	reg *pwrstctrl;
	reg *pwrstst;
	int properties;
} pwrdm_info;


void pwrdm_init(void);
void pwrdm_deinit(void);

int pwrdm_count_get(void);
const genlist *pwrdm_list_get(void);


#endif
