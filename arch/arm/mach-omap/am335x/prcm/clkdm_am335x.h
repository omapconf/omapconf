/*
 *
 * @Component			OMAPCONF
 * @Filename			clkdm_am335x.h
 * @Description			AM335X Clock Domain Definitions & APIs
 * @Author			Gilberto Rodriguez <gilrod@ti.com>
 * @Date			2014
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
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


#ifndef __CLKDM_AM335X_H__
#define __CLKDM_AM335X_H__


#include <clkdm.h>
#include <clockdomain.h>
#include <pwrdm_am335x.h>
#include <voltdm_am335x.h>


#define CLKDM_AM335X_MAX_NAME_LENGTH		16


typedef enum {
	CLKDM_AM335X_PER_L4LS,
	CLKDM_AM335X_PER_L3S,
	CLKDM_AM335X_PER_L3,
	CLKDM_AM335X_PER_L4HS,
	CLKDM_AM335X_PER_OCPWP_L3,
	CLKDM_AM335X_PER_PRU_ICSS,
	CLKDM_AM335X_PER_CPSW,
	CLKDM_AM335X_PER_LCDC,
	CLKDM_AM335X_PER_CLK_24MHZ,
	CLKDM_AM335X_WKUP,
	CLKDM_AM335X_WKUP_L3_AON,
	CLKDM_AM335X_WKUP_L4_WKUP_AON,
	CLKDM_AM335X_MPU,
	CLKDM_AM335X_RTC,
	CLKDM_AM335X_GFX_L3,
	CLKDM_AM335X_GFX_L4LS_GFX,
	CLKDM_AM335X_CEFUSE,
	CLKDM_AM335X_NONE,
	CLKDM_AM335X_ID_MAX
} clkdm_am335x_id;


void clkdm_am335x_init(void);
void clkdm_am335x_deinit(void);

int clkdm_am335x_count_get(void);
const genlist *clkdm_am335x_list_get(void);

const char *clkdm_am335x_name_get(clkdm_am335x_id id);
clkdm_status clkdm_am335x_status_get(unsigned int cm_clkstctrl,
	unsigned int clkstctrl_bit);

#endif
