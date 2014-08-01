/*
 *
 * @Component			OMAPCONF
 * @Filename			dpll_am335x.h
 * @Description			AM335X DPLL Definitions & Functions
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


#ifndef __DPLL_AM335X_H__
#define __DPLL_AM335X_H__


#include <cm_am335x-defs.h>
#include <stdio.h>


int dpll_am335x_init(void);
int dpll_am335x_free(void);

int dpll_am335x_settings_extract(dpll_am335x_settings *settings,
	unsigned int id, unsigned short ignore);

dpll_am335x_settings *dpll_am335x_settings_get(unsigned int id,
	unsigned short ignore);

dpll_status dpll_am335x_status_get(dpll_am335x_id id);

double dpll_am335x_output_rate_get(dpll_am335x_id id,
	dpll_am335x_output_id out_id, unsigned short ignore);

int dpll_am335x_type_b_show(dpll_am335x_id start_id, dpll_am335x_id end_id,
	FILE *stream);
int dpll_am335x_type_a_show(dpll_am335x_id start_id, dpll_am335x_id end_id,
	FILE *stream);
dpll_am335x_id dpll_am335x_s2id(char *s);
int dpll_am335x_dump(FILE *stream, dpll_am335x_id id);
int dpll_am335x_show(FILE *stream);
int dpll_am335x_main(int argc, char *argv[]);


#endif
