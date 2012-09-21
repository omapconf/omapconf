/*
 *
 * @Component			OMAPCONF
 * @Filename			dpll54xx-data.c
 * @Description			OMAP5 DPLL Definitions
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


#include <dpll54xx-data.h>
#include <clock54xx.h>


const char dpll54xx_names[DPLL54XX_ID_MAX][DPLL_MAX_NAME_LENGTH] = {
	"DPLL_MPU",
	"DPLL_IVA",
	"DPLL_CORE",
	"DPLL_PER",
	"DPLL_ABE",
	"DPLL_USB",
	"DPLL_UNIPRO1",
	"DPLL_UNIPRO2"};


const char hsdiv54xx_names[HSDIV54XX_ID_MAX][HSDIV_MAX_NAME_LENGTH] = {
	"H11",
	"H12",
	"H13",
	"H14",
	"H21",
	"H22",
	"H23",
	"H24"};


const char
	dpll54xx_output_names[DPLL54XX_OUTPUT_ID_MAX][DPLL_OUTPUT_MAX_NAME_LENGTH] = {
	"CLKOUT_M2",
	"CLKOUTX2_M2",
	"CLKOUTX2_M3",
	"CLKOUTX2_H11",
	"CLKOUTX2_H12",
	"CLKOUTX2_H13",
	"CLKOUTX2_H14",
	"CLKOUTX2_H21",
	"CLKOUTX2_H22",
	"CLKOUTX2_H23",
	"CLKOUTX2_H24",
	"CLK_DCO_LDO"};


const dpll_clk_sources
	dpll54xx_sources[DPLL54XX_ID_MAX] = {
	{CLK54XX_MPU_DPLL_CLK, CLK54XX_MPU_DPLL_HS_CLK, CLK54XX_ID_MAX, CLK54XX_ID_MAX}, /* MPU */
	{CLK54XX_IVA_DPLL_CLK, CLK54XX_IVA_DPLL_HS_CLK, CLK54XX_ID_MAX, CLK54XX_ID_MAX}, /* IVA */
	{CLK54XX_CORE_DPLL_CLK, CLK54XX_CORE_DPLL_HS_CLK, CLK54XX_CORE_DPLL_HS_CLK, CLK54XX_ID_MAX}, /* CORE */
	{CLK54XX_PER_DPLL_CLK, CLK54XX_PER_DPLL_HS_CLK, CLK54XX_ID_MAX, CLK54XX_ID_MAX}, /* PER */
	{CLK54XX_ABE_DPLL_CLK, CLK54XX_ABE_DPLL_BYPASS_CLK, CLK54XX_ID_MAX, CLK54XX_ID_MAX}, /* ABE */
	{CLK54XX_USB_DPLL_CLK, CLK54XX_USB_DPLL_HS_CLK, CLK54XX_ID_MAX, CLK54XX_ID_MAX}, /* USB */
	{CLK54XX_UNIPRO1_DPLL_CLK, CLK54XX_ID_MAX, CLK54XX_ID_MAX, CLK54XX_ID_MAX}, /* UNIPRO1 */
	{CLK54XX_UNIPRO2_DPLL_CLK, CLK54XX_ID_MAX, CLK54XX_ID_MAX, CLK54XX_ID_MAX} }; /* UNIPRO2 */
