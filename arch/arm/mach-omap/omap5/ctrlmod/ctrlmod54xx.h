/*
 *
 * @Component			OMAPCONF
 * @Filename			ctrlmod54xx.h
 * @Description			OMAP5 CONTROL MODULE Registers Definitions
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


#ifndef __CTRLMOD54XX_H__
#define __CTRLMOD54XX_H__

#include <reg.h>
#include <stdio.h>

typedef enum {
	CTRLMOD54XX_CTRL_MODULE_CORE,
	CTRLMOD54XX_CTRL_MODULE_CORE_PAD,
	CTRLMOD54XX_CTRL_MODULE_WKUP,
	CTRLMOD54XX_CTRL_MODULE_WKUP_PAD,
	CTRLMOD54XX_MODS_COUNT = 4
} ctrlmod54xx_mod_id;

extern reg **ctrlmod54xxes1_mods[CTRLMOD54XX_MODS_COUNT];
extern reg **ctrlmod54xx_mods[CTRLMOD54XX_MODS_COUNT];

int ctrlmod54xx_dump(FILE *stream, ctrlmod54xx_mod_id id);
int ctrlmod54xx_export(FILE *fp, ctrlmod54xx_mod_id id);
int ctrlmod54xx_import(FILE *fp, ctrlmod54xx_mod_id id);
int ctrlmod54xx_io_audit(FILE *stream, unsigned int *err_nbr,
	unsigned int *wng_nbr);

/* DEPRECATED, DO NOT USE ANYMORE */
int ctrlmod54xx_main(int argc, char *argv[]);


#endif
