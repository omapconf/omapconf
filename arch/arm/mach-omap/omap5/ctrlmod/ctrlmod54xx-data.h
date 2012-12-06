/*
 *
 * @Component			OMAPCONF
 * @Filename			ctrlmod54xx-data.h
 * @Description			OMAP5 CONTROL MODULE Register Golden Values
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


#ifndef __CTRLMOD54XX_DATA_H__
#define __CTRLMOD54XX_DATA_H__


#include <reg.h>
#include <ctrlmod_core54xx-defs.h>
#include <ctrlmod_core_pad54xx-defs.h>
#include <ctrlmod_wkup54xx-defs.h>
#include <ctrlmod_wkup_pad54xx-defs.h>
#include <lib.h>


typedef struct {
	data_type valid;
	unsigned int golden_value;
} ctrlmod54xx_golden_item;


extern const ctrlmod54xx_golden_item
	ctrlmod_core54xxes1_golden_values[OMAP5430ES1_CTRL_MODULE_CORE_MOD_REGCOUNT];
extern const ctrlmod54xx_golden_item
	ctrlmod_core_pad54xxes1_golden_values[OMAP5430_CTRL_MODULE_CORE_PAD_MOD_REGCOUNT];
extern const ctrlmod54xx_golden_item
	ctrlmod_wkup54xxes1_golden_values[OMAP5430ES1_CTRL_MODULE_WKUP_MOD_REGCOUNT];
extern const ctrlmod54xx_golden_item
	ctrlmod_wkup_pad54xxes1_golden_values[OMAP5430_CTRL_MODULE_WKUP_PAD_MOD_REGCOUNT];


#endif
