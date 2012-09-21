/*
 *
 * @Component			OMAPCONF
 * @Filename			module44xx-data.h
 * @Description			OMAP4 Module Definitions
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


#ifndef __MODULE44XX_DATA_H__
#define __MODULE44XX_DATA_H__


#include <module44xx.h>


typedef struct {
	mod44xx_id id;
	mod_interface_type type;
	unsigned short int has_clockactivity_bit;
	clock44xx_id src_clk_id;
	clkdm44xx_id clockdm_id;
	pwrdm44xx_id powerdm_id;
	voltdm44xx_id voltagedm_id;
	unsigned int *sysconfig_addr;
	unsigned int *cm_clkctrl_addr;
	unsigned int *rm_context_addr;
	double por_speed[OPP44XX_ID_MAX]; /* in MHz */
} mod44xx_info;


extern mod44xx_info mod44xx_info_table[OMAP4_MODULE_ID_MAX];

extern const char
	mod44xx_name_table[OMAP4_MODULE_ID_MAX][MODULE_MAX_NAME_LENGTH];

extern const short int mod44xx_has_smart_idle_wakeup_table[OMAP4_MODULE_ID_MAX];

int mod44xx_init_info_table(void);


#endif
