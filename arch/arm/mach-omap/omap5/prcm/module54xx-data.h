/*
 *
 * @Component			OMAPCONF
 * @Filename			module54xx-data.h
 * @Description			OMAP5 Module Data Definitions
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


#ifndef __MODULE54XX_DATA_H__
#define __MODULE54XX_DATA_H__


#include <module54xx.h>
#include <voltdm54xx.h>


extern const char mod54xx_names_table[MOD54XX_ID_MAX][MODULE_MAX_NAME_LENGTH];
extern const clk54xx_id mod54xx_flck_table[MOD54XX_ID_MAX];
extern const clkdm54xx_id mod54xx_clkdm_table[MOD54XX_ID_MAX];

extern const unsigned int mod54xx_properties_table[MOD54XX_ID_MAX];
extern reg *mod54xx_sysconfig_table[MOD54XX_ID_MAX];
extern reg *mod54xxes1_cm_clkctrl_reg_table[MOD54XX_ID_MAX];
extern reg *mod54xx_cm_clkctrl_reg_table[MOD54XX_ID_MAX];
extern reg *mod54xxes1_rm_context_reg_table[MOD54XX_ID_MAX];
extern reg *mod54xx_rm_context_reg_table[MOD54XX_ID_MAX];
extern const double mod54xx_por_rates_table[MOD54XX_ID_MAX][OPP_MAX];


#endif
