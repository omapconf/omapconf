/*
 *
 * @Component			OMAPCONF
 * @Filename			opp_am335x.h
 * @Description			AM335X OPerating Point (OPP) Common Definitions
 *				& Functions
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


#ifndef __OPP_AM335X_H__
#define __OPP_AM335X_H__


#include <voltdm_am335x.h>


typedef enum {
	OPP_AM335X_050,
	OPP_AM335X_100,
	OPP_AM335X_100_LOW,
	OPP_AM335X_100_HIGH,
	OPP_AM335X_120,
	OPP_AM335X_TURBO,
	OPP_AM335X_NITRO,
	OPP_AM335X_ID_MAX
} opp_am335x_id;


void opp_am335x_init(void);
void opp_am335x_deinit(void);

int opp_am335x_count_get(voltdm_am335x_id vdd_id);
const genlist *opp_am335x_list_get(voltdm_am335x_id vdd_id);

int opp_am335x_id_get(const char *opp);

const char *opp_am335x_name_get(opp_am335x_id id);
const char *opp_am335x_get(voltdm_am335x_id vdd_id);
const char *opp_am335x_by_rate_get(voltdm_am335x_id vdd_id);


#endif
