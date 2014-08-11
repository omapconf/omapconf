/*
 *
 * @Component			OMAPCONF
 * @Filename			pwrdm_am335x.h
 * @Description			AM335X Power Domain Definitions & APIs
 * @Author			Gilberto Rodriguez
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


#ifndef __PWRDM_AM335X_H__
#define __PWRDM_AM335X_H__


#include <genlist.h>
#include <powerdomain.h>
#include <pwrdm.h>
#include <voltdm_am335x.h>


#define PWRDM_AM335X_MAX_NAME_LENGTH		16


typedef enum {
	PWRDM_AM335X_WKUP,
	PWRDM_AM335X_MPU,
	PWRDM_AM335X_GFX,
	PWRDM_AM335X_PER,
	PWRDM_AM335X_RTC,
	PWRDM_AM335X_EFUSE,
	PWRDM_AM335X_ID_MAX
} pwrdm_am335x_id;


void pwrdm_am335x_init(void);
void pwrdm_am335x_deinit(void);

int pwrdm_am335x_count_get(void);
const genlist *pwrdm_am335x_list_get(void);


#endif
