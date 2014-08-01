/*
 *
 * @Component			OMAPCONF
 * @Filename			dpll_am335x-data.c
 * @Description			AM335X DPLL Definitions
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


#include <dpll_am335x-data.h>


const char dpll_am335x_names[DPLL_AM335X_ID_MAX][DPLL_MAX_NAME_LENGTH] = {
	[DPLL_AM335X_PER] = "DPLL_PER",
	[DPLL_AM335X_CORE] = "DPLL_CORE",
	[DPLL_AM335X_MPU] = "DPLL_MPU",
	[DPLL_AM335X_DDR] = "DPLL_DDR",
	[DPLL_AM335X_DISP] = "DPLL_DISP"};

const char dpll_am335x_strings[DPLL_AM335X_ID_MAX][DPLL_MAX_NAME_LENGTH] = {
	[DPLL_AM335X_PER] = "per",
	[DPLL_AM335X_CORE] = "core",
	[DPLL_AM335X_MPU] = "mpu",
	[DPLL_AM335X_DDR] = "ddr",
	[DPLL_AM335X_DISP] = "disp"};

const char hsdiv_am335x_names[HSDIV_AM335X_ID_MAX][HSDIV_MAX_NAME_LENGTH] = {
	[HSDIV_AM335X_M4] = "M4",
	[HSDIV_AM335X_M5] = "M5",
	[HSDIV_AM335X_M6] = "M6" };
