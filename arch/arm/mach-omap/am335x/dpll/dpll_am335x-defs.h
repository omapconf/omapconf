/*
 *
 * @Component			OMAPCONF
 * @Filename			dpll_am335x-defs.h
 * @Description			AM335X DPLL Struct Definitions
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


#ifndef __DPLL_AM335X_DEFS_H__
#define __DPLL_AM335X_DEFS_H__


#include <dpll.h>

#define AM335X_PLL_CLKINPULOW_CTRL				0x44E10458


typedef enum {
	HSDIV_AM335X_M4,
	HSDIV_AM335X_M5,
	HSDIV_AM335X_M6,
	HSDIV_AM335X_ID_MAX
} hsdiv_am335x_id;


typedef enum {
	DPLL_AM335X_PER,
	DPLL_AM335X_CORE,
	DPLL_AM335X_MPU,
	DPLL_AM335X_DDR,
	DPLL_AM335X_DISP,
	DPLL_AM335X_ID_MAX
} dpll_am335x_id;


typedef struct {
	hsdiv_am335x_id id;
	unsigned short present;	/* 0 if no CM_DIV_M(4-6)_xyz, 1 otherwise */
	unsigned short status;	/* CM_DIV_M(4-6)_xyz.CLKST */
	unsigned int div;	/* CM_DIV_M(4-6)_xyz.DIVHS */
	double rate;		/* CLKOUT rate in MHz */
} hsdiv_am335x_settings;


typedef struct {
	dpll_settings dpll;
	dpll_status status;
	int byp_clk_sel;
	hsdiv_am335x_settings hsdiv[HSDIV_AM335X_ID_MAX];
} dpll_am335x_settings;


typedef enum {
	DPLL_AM335X_CLKOUT,
	DPLL_AM335X_CLKOUTX2,
	DPLL_AM335X_CLKDCOLDO,
	DPLL_AM335X_CLKOUTHIF,
	DPLL_AM335X_CORE_CLKOUT_M4,
	DPLL_AM335X_CORE_CLKOUT_M5,
	DPLL_AM335X_CORE_CLKOUT_M6,
	DPLL_AM335X_OUTPUT_ID_MAX
} dpll_am335x_output_id;


#endif
