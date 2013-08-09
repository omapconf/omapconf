/*
 *
 * @Component			OMAPCONF
 * @Filename			dpll_dra7xx-data.c
 * @Description			DRA7 DPLL Definitions
 * @Author			Jin Zheng (j-zheng@ti.com)
 * @Date			2013
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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


#include <dpll_dra7xx-data.h>


const char dpll_dra7xx_names[DPLL_DRA7XX_ID_MAX][DPLL_MAX_NAME_LENGTH] = {
	[DPLL_DRA7XX_MPU] = "DPLL_MPU",
	[DPLL_DRA7XX_IVA] = "DPLL_IVA",
	[DPLL_DRA7XX_CORE] = "DPLL_CORE",
	[DPLL_DRA7XX_PER] = "DPLL_PER",
	[DPLL_DRA7XX_ABE] = "DPLL_ABE",
	[DPLL_DRA7XX_EVE] = "DPLL_EVE",
	[DPLL_DRA7XX_DSP] = "DPLL_DSP",
	[DPLL_DRA7XX_GMAC] = "DPLL_GMAC",
	[DPLL_DRA7XX_GPU] = "DPLL_GPU",
	[DPLL_DRA7XX_DDR] = "DPLL_DDR",
	[DPLL_DRA7XX_USB] = "DPLL_USB",
	[DPLL_DRA7XX_PCIE_REF] = "DPLL_PCIE_REF"};

const char dpll_dra7xx_strings[DPLL_DRA7XX_ID_MAX][DPLL_MAX_NAME_LENGTH] = {
	[DPLL_DRA7XX_MPU] = "mpu",
	[DPLL_DRA7XX_IVA] = "iva",
	[DPLL_DRA7XX_CORE] = "core",
	[DPLL_DRA7XX_PER] = "per",
	[DPLL_DRA7XX_ABE] = "abe",
	[DPLL_DRA7XX_EVE] = "eve",
	[DPLL_DRA7XX_DSP] = "dsp",
	[DPLL_DRA7XX_GMAC] = "gmac",
	[DPLL_DRA7XX_GPU] = "gpu",
	[DPLL_DRA7XX_DDR] = "ddr",
	[DPLL_DRA7XX_USB] = "usb",
	[DPLL_DRA7XX_PCIE_REF] = "pcieref"};

const char hsdiv_dra7xx_names[HSDIV_DRA7XX_ID_MAX][HSDIV_MAX_NAME_LENGTH] = {
	[HSDIV_DRA7XX_H11] = "H11",
	[HSDIV_DRA7XX_H12] = "H12",
	[HSDIV_DRA7XX_H13] = "H13",
	[HSDIV_DRA7XX_H14] = "H14",
	[HSDIV_DRA7XX_H21] = "H21",
	[HSDIV_DRA7XX_H22] = "H22",
	[HSDIV_DRA7XX_H23] = "H23",
	[HSDIV_DRA7XX_H24] = "H24" };
