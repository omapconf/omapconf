/*
 *
 * @Component			OMAPCONF
 * @Filename			sr54xx.h
 * @Description			OMAP5 SMARTREFLEX Registers Functions
 * @Author			Patrick Titiano (p-titiano@ti.com)
 * @Date			2011
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
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


#ifndef __SR54XX_H__
#define __SR54XX_H__


#include <sr54xx-defs.h>
#include <stdio.h>
#include <voltdm54xx.h>


int sr54xx_main(int argc, char *argv[]);

const char *sr54xx_mod_name_get(sr54xx_mod_id id);
sr54xx_mod_id sr54xx_vddid2srid(voltdm54xx_id vdd_id);

int sr54xx_dump(FILE *stream, sr54xx_mod_id id);
int sr54xx_export(FILE *fp, sr54xx_mod_id id);
int sr54xx_import(FILE *fp, sr54xx_mod_id id);
int sr54xx_config_show(FILE *stream);
int sr54xx_module_config_show(FILE *stream);
int sr54xx_convergence_status_show(FILE *stream);

unsigned int sr54xx_is_accessible(sr54xx_mod_id id);
unsigned int sr54xx_is_enabled(sr54xx_mod_id id);
double sr54xx_last_vp_voltage_get(sr54xx_mod_id id);

int sr54xx_avs_enable(sr54xx_mod_id id, unsigned short enable);
unsigned short sr54xx_avs_is_enabled(sr54xx_mod_id id);


#endif
