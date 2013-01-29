/*
 *
 * @Component			OMAPCONF
 * @Filename			opp44xx.c
 * @Description			OMAP4 OPerating Point (OPP) Common Definitions
 *				& Functions
 * @Author			Patrick Titiano (p-titiano@ti.com)
 * @Date			2012
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
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


#include <stdlib.h>
#include <opp.h>
#include <lib.h>
#include <voltdm44xx.h>
#include <clock44xx.h>
#include <module44xx.h>
#include <cpuinfo.h>
#include <string.h>
#include <pmic.h>

/* #define OPP44XX_DEBUG */
#ifdef OPP44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


genlist vdd44xx_wkup_opp_list;
genlist vdd44xx_mpu_opp_list;
genlist vdd44xx_iva_opp_list;
genlist vdd44xx_core_opp_list;

genlist *opp44xx_list_table[OMAP4_VD_ID_MAX] = {
		&vdd44xx_wkup_opp_list, /* LDO_WKUP */
		&vdd44xx_mpu_opp_list, /* VDD_MPU */
		&vdd44xx_iva_opp_list, /* VDD_IVA */
		&vdd44xx_core_opp_list}; /* VDD_CORE */

static unsigned short opp44xx_init_done = 0;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp4430_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void opp4430_init(void)
{

	/*
	 * Fill nominal voltage field with Data Manual recommended voltages.
	 * Then convert it to a voltage that is achievable with SMPS
	 * (by considering SMPS voltage offset and step).
	 * This is easier to do it this way than looking at SMPS voltage table
	 * each time nominal voltage gets updated.
	 *
	 * As DPLL CASCADING OPP uses same nominal voltage as OPP50, set it at
	 * least 1 step lower than OPP50, so that it can be distinguished.
	 * OPP search by voltage will fail, but OPP search by rate should
	 * succeed.
	 */
	static opp_t opp_wkup_dpll_casc = {	OPP_DPLL_CASC,	1060000, 49152};
	static opp_t opp_wkup_opp50 = {		OPP_50,		1060000, 500000};
	static opp_t opp_wkup_opp100 = {	OPP_100,	1060000, 100000};

	static opp_t opp_mpu_dpll_casc = {	OPP_DPLL_CASC,	1025000, 196608};
	static opp_t opp_mpu_opp50 = {		OPP_50,		1025000, 300000};
	static opp_t opp_mpu_opp100 = {		OPP_100,	1200000, 600000};
	static opp_t opp_mpu_turbo = {		OPP_TURBO,	1325000, 800000};
	static opp_t opp_mpu_nitro = {		OPP_NITRO,	1388000, 100800};
	static opp_t opp_mpu_nitrosb = {	OPP_NITROSB,	1388000, 120000};

	static opp_t opp_iva_dpll_casc = {	OPP_DPLL_CASC,	950000,  98304};
	static opp_t opp_iva_opp50 = {		OPP_50,		950000,  133028};
	static opp_t opp_iva_opp100 = {		OPP_100,	1114000, 266057};
	static opp_t opp_iva_turbo = {		OPP_TURBO,	1291000, 330700};

	static opp_t opp_core_dpll_casc = {	OPP_DPLL_CASC,	962000,	 98304};
	static opp_t opp_core_opp50 = {		OPP_50,		962000,  100000};
	static opp_t opp_core_opp100 = {	OPP_100,	1127000, 200000};

	genlist_addtail(&vdd44xx_wkup_opp_list,
			(void *) &opp_wkup_dpll_casc, sizeof(opp_t));
	genlist_addtail(&vdd44xx_wkup_opp_list,
			(void *) &opp_wkup_opp50, sizeof(opp_t));
	genlist_addtail(&vdd44xx_wkup_opp_list,
			(void *) &opp_wkup_opp100, sizeof(opp_t));

	opp_mpu_dpll_casc.voltage = smps_voltage_round(
		PMIC_SMPS_MPU, opp_mpu_dpll_casc.voltage);
	genlist_addtail(&vdd44xx_mpu_opp_list,
			(void *) &opp_mpu_dpll_casc, sizeof(opp_t));
	opp_mpu_opp50.voltage = smps_voltage_round(
		PMIC_SMPS_MPU, opp_mpu_opp50.voltage);
	genlist_addtail(&vdd44xx_mpu_opp_list,
			(void *) &opp_mpu_opp50, sizeof(opp_t));
	opp_mpu_opp100.voltage = smps_voltage_round(
		PMIC_SMPS_MPU, opp_mpu_opp100.voltage);
	genlist_addtail(&vdd44xx_mpu_opp_list,
			(void *) &opp_mpu_opp100, sizeof(opp_t));
	opp_mpu_turbo.voltage = smps_voltage_round(
		PMIC_SMPS_MPU, opp_mpu_turbo.voltage);
	genlist_addtail(&vdd44xx_mpu_opp_list,
			(void *) &opp_mpu_turbo, sizeof(opp_t));
	opp_mpu_nitro.voltage = smps_voltage_round(
		PMIC_SMPS_MPU, opp_mpu_nitro.voltage);
	genlist_addtail(&vdd44xx_mpu_opp_list,
			(void *) &opp_mpu_nitro, sizeof(opp_t));
	opp_mpu_nitrosb.voltage = smps_voltage_round(
		PMIC_SMPS_MPU, opp_mpu_nitrosb.voltage);
	genlist_addtail(&vdd44xx_mpu_opp_list,
			(void *) &opp_mpu_nitrosb, sizeof(opp_t));

	opp_iva_dpll_casc.voltage = smps_voltage_round(
		PMIC_SMPS_MM, opp_iva_dpll_casc.voltage);
	genlist_addtail(&vdd44xx_iva_opp_list,
			(void *) &opp_iva_dpll_casc, sizeof(opp_t));
	opp_iva_opp50.voltage = smps_voltage_round(
		PMIC_SMPS_MM, opp_iva_opp50.voltage);
	genlist_addtail(&vdd44xx_iva_opp_list,
			(void *) &opp_iva_opp50, sizeof(opp_t));
	opp_iva_opp100.voltage = smps_voltage_round(
		PMIC_SMPS_MM, opp_iva_opp100.voltage);
	genlist_addtail(&vdd44xx_iva_opp_list,
			(void *) &opp_iva_opp100, sizeof(opp_t));
	opp_iva_turbo.voltage = smps_voltage_round(
		PMIC_SMPS_MM, opp_iva_turbo.voltage);
	genlist_addtail(&vdd44xx_iva_opp_list,
			(void *) &opp_iva_turbo, sizeof(opp_t));

	opp_core_dpll_casc.voltage = smps_voltage_round(
		PMIC_SMPS_CORE, opp_core_dpll_casc.voltage);
	genlist_addtail(&vdd44xx_core_opp_list,
			(void *) &opp_core_dpll_casc, sizeof(opp_t));
	opp_core_opp50.voltage = smps_voltage_round(
		PMIC_SMPS_CORE, opp_core_opp50.voltage);
	genlist_addtail(&vdd44xx_core_opp_list,
			(void *) &opp_core_opp50, sizeof(opp_t));
	opp_core_opp100.voltage = smps_voltage_round(
		PMIC_SMPS_CORE, opp_core_opp100.voltage);
	genlist_addtail(&vdd44xx_core_opp_list,
			(void *) &opp_core_opp100, sizeof(opp_t));
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp4460_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void opp4460_init(void)
{
	static opp_t opp_wkup_dpll_casc = {	OPP_DPLL_CASC,	1060000, 49152};
	static opp_t opp_wkup_opp50 = {		OPP_50,		1060000, 50000};
	static opp_t opp_wkup_opp100 = {	OPP_100,	1060000, 100000};

	static opp_t opp_mpu_dpll_casc = {	OPP_DPLL_CASC,	1025000, 196608};
	static opp_t opp_mpu_opp50 = {		OPP_50,		1025000, 350000};
	static opp_t opp_mpu_opp100 = {		OPP_100,	1203000, 700000};
	static opp_t opp_mpu_turbo = {		OPP_TURBO,	1317000, 920000};
	static opp_t opp_mpu_nitro = {		OPP_NITRO,	1380000, 1200000};
	static opp_t opp_mpu_nitrosb = {	OPP_NITROSB,	1380000, 1500000};

	static opp_t opp_iva_dpll_casc = {	OPP_DPLL_CASC,	950000,  98304};
	static opp_t opp_iva_opp50 = {		OPP_50,		950000,  133028};
	static opp_t opp_iva_opp100 = {		OPP_100,	1114000, 266057};
	static opp_t opp_iva_turbo = {		OPP_TURBO,	1291000, 330700};
	static opp_t opp_iva_nitro = {		OPP_NITRO,	1375000, 430400};
	static opp_t opp_iva_nitrosb = {	OPP_NITROSB,	1375000, 500000};

	static opp_t opp_core_dpll_casc = {	OPP_DPLL_CASC,	962000,  98304};
	static opp_t opp_core_opp50 = {		OPP_50,		962000,  100000};
	static opp_t opp_core_opp100 = {	OPP_100,	1127000, 200000};
	static opp_t opp_core_opp119 = {	OPP_119,	1250000, 200000};

	genlist_addtail(&vdd44xx_wkup_opp_list,
			(void *) &opp_wkup_dpll_casc, sizeof(opp_t));
	genlist_addtail(&vdd44xx_wkup_opp_list,
			(void *) &opp_wkup_opp50, sizeof(opp_t));
	genlist_addtail(&vdd44xx_wkup_opp_list,
			(void *) &opp_wkup_opp100, sizeof(opp_t));

	opp_mpu_dpll_casc.voltage = smps_voltage_round(
		PMIC_SMPS_MPU, opp_mpu_dpll_casc.voltage);
	genlist_addtail(&vdd44xx_mpu_opp_list,
			(void *) &opp_mpu_dpll_casc, sizeof(opp_t));
	opp_mpu_opp50.voltage = smps_voltage_round(
		PMIC_SMPS_MPU, opp_mpu_opp50.voltage);
	genlist_addtail(&vdd44xx_mpu_opp_list,
			(void *) &opp_mpu_opp50, sizeof(opp_t));
	opp_mpu_opp100.voltage = smps_voltage_round(
		PMIC_SMPS_MPU, opp_mpu_opp100.voltage);
	genlist_addtail(&vdd44xx_mpu_opp_list,
			(void *) &opp_mpu_opp100, sizeof(opp_t));
	opp_mpu_turbo.voltage = smps_voltage_round(
		PMIC_SMPS_MPU, opp_mpu_turbo.voltage);
	genlist_addtail(&vdd44xx_mpu_opp_list,
			(void *) &opp_mpu_turbo, sizeof(opp_t));
	opp_mpu_nitro.voltage = smps_voltage_round(
		PMIC_SMPS_MPU, opp_mpu_nitro.voltage);
	genlist_addtail(&vdd44xx_mpu_opp_list,
			(void *) &opp_mpu_nitro, sizeof(opp_t));
	opp_mpu_nitrosb.voltage = smps_voltage_round(
		PMIC_SMPS_MPU, opp_mpu_nitrosb.voltage);
	genlist_addtail(&vdd44xx_mpu_opp_list,
			(void *) &opp_mpu_nitrosb, sizeof(opp_t));

	opp_iva_dpll_casc.voltage = smps_voltage_round(
		PMIC_SMPS_MM, opp_iva_dpll_casc.voltage);
	genlist_addtail(&vdd44xx_iva_opp_list,
			(void *) &opp_iva_dpll_casc, sizeof(opp_t));
	opp_iva_opp50.voltage = smps_voltage_round(
		PMIC_SMPS_MM, opp_iva_opp50.voltage);
	genlist_addtail(&vdd44xx_iva_opp_list,
			(void *) &opp_iva_opp50, sizeof(opp_t));
	opp_iva_opp100.voltage = smps_voltage_round(
		PMIC_SMPS_MM, opp_iva_opp100.voltage);
	genlist_addtail(&vdd44xx_iva_opp_list,
			(void *) &opp_iva_opp100, sizeof(opp_t));
	opp_iva_turbo.voltage = smps_voltage_round(
		PMIC_SMPS_MM, opp_iva_turbo.voltage);
	genlist_addtail(&vdd44xx_iva_opp_list,
			(void *) &opp_iva_turbo, sizeof(opp_t));
	opp_iva_nitro.voltage = smps_voltage_round(
		PMIC_SMPS_MM, opp_iva_nitro.voltage);
	genlist_addtail(&vdd44xx_iva_opp_list,
			(void *) &opp_iva_nitro, sizeof(opp_t));
	opp_iva_nitrosb.voltage = smps_voltage_round(
		PMIC_SMPS_MM, opp_iva_nitrosb.voltage);
	genlist_addtail(&vdd44xx_iva_opp_list,
			(void *) &opp_iva_nitrosb, sizeof(opp_t));

	opp_core_dpll_casc.voltage = smps_voltage_round(
		PMIC_SMPS_CORE, opp_core_dpll_casc.voltage);
	genlist_addtail(&vdd44xx_core_opp_list,
			(void *) &opp_core_dpll_casc, sizeof(opp_t));
	opp_core_opp50.voltage = smps_voltage_round(
		PMIC_SMPS_CORE, opp_core_opp50.voltage);
	genlist_addtail(&vdd44xx_core_opp_list,
			(void *) &opp_core_opp50, sizeof(opp_t));
	opp_core_opp100.voltage = smps_voltage_round(
		PMIC_SMPS_CORE, opp_core_opp100.voltage);
	genlist_addtail(&vdd44xx_core_opp_list,
			(void *) &opp_core_opp100, sizeof(opp_t));
	opp_core_opp119.voltage = smps_voltage_round(
		PMIC_SMPS_CORE, opp_core_opp119.voltage);
	genlist_addtail(&vdd44xx_core_opp_list,
			(void *) &opp_core_opp119, sizeof(opp_t));
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp4470_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void opp4470_init(void)
{
	static opp_t opp_wkup_dpll_casc = {	OPP_DPLL_CASC,	1060000, 49152};
	static opp_t opp_wkup_opp50_low = {	OPP_50_LOW,	1060000, 50000};
	static opp_t opp_wkup_opp50_high = {	OPP_50_HIGH,	1060000, 58333};
	static opp_t opp_wkup_opp100_low = {	OPP_100_LOW,	1060000, 100000};
	static opp_t opp_wkup_opp119_low = {	OPP_119_LOW,	1060000, 100000};
	static opp_t opp_wkup_opp119_high = {	OPP_119_HIGH,	1060000, 116666};

	static opp_t opp_mpu_dpll_casc = {	OPP_DPLL_CASC,	1037000, 196608};
	static opp_t opp_mpu_opp50 = {		OPP_50,		1037000, 396800};
	static opp_t opp_mpu_opp100 = {		OPP_100,	1200000, 800000};
	static opp_t opp_mpu_turbo = {		OPP_TURBO,	1312000, 1100000};
	static opp_t opp_mpu_nitro = {		OPP_NITRO,	1375000, 1300000};
	static opp_t opp_mpu_nitrosb = {	OPP_NITROSB,	1387000, 1500000};

	static opp_t opp_iva_dpll_casc = {	OPP_DPLL_CASC,	962000,  98304};
	static opp_t opp_iva_opp50 = {		OPP_50,		962000,  133028};
	static opp_t opp_iva_opp100 = {		OPP_100,	1137000, 266057};
	static opp_t opp_iva_turbo = {		OPP_TURBO,	1287000, 330700};
	static opp_t opp_iva_nitro = {		OPP_NITRO,	1375000, 430100};
	static opp_t opp_iva_nitrosb = {	OPP_NITROSB,	1380000, 500000};

	static opp_t opp_core_dpll_casc = {	OPP_DPLL_CASC,	980000,  98304};
	static opp_t opp_core_opp50_low = {	OPP_50_LOW,	980000,  100000};
	static opp_t opp_core_opp50_high = {	OPP_50_HIGH,	980000,  116666};
	static opp_t opp_core_opp100_low = {	OPP_100_LOW,	1126000, 200000};
	static opp_t opp_core_opp100_high = {	OPP_100_HIGH,	1126000, 116666};
	static opp_t opp_core_opp119_low = {	OPP_119_LOW,	1190000, 200000};
	static opp_t opp_core_opp119_high = {	OPP_119_HIGH,	1190000, 233333};

	genlist_addtail(&vdd44xx_wkup_opp_list,
			(void *) &opp_wkup_dpll_casc, sizeof(opp_t));
	genlist_addtail(&vdd44xx_wkup_opp_list,
			(void *) &opp_wkup_opp50_low, sizeof(opp_t));
	genlist_addtail(&vdd44xx_wkup_opp_list,
			(void *) &opp_wkup_opp50_high, sizeof(opp_t));
	genlist_addtail(&vdd44xx_wkup_opp_list,
			(void *) &opp_wkup_opp100_low, sizeof(opp_t));
	genlist_addtail(&vdd44xx_wkup_opp_list,
			(void *) &opp_wkup_opp119_low, sizeof(opp_t));
	genlist_addtail(&vdd44xx_wkup_opp_list,
			(void *) &opp_wkup_opp119_high, sizeof(opp_t));

	opp_mpu_dpll_casc.voltage = smps_voltage_round(
		PMIC_SMPS_MPU, opp_mpu_dpll_casc.voltage);
	genlist_addtail(&vdd44xx_mpu_opp_list,
			(void *) &opp_mpu_dpll_casc, sizeof(opp_t));
	opp_mpu_opp50.voltage = smps_voltage_round(
		PMIC_SMPS_MPU, opp_mpu_opp50.voltage);
	genlist_addtail(&vdd44xx_mpu_opp_list,
			(void *) &opp_mpu_opp50, sizeof(opp_t));
	opp_mpu_opp100.voltage = smps_voltage_round(
		PMIC_SMPS_MPU, opp_mpu_opp100.voltage);
	genlist_addtail(&vdd44xx_mpu_opp_list,
			(void *) &opp_mpu_opp100, sizeof(opp_t));
	opp_mpu_turbo.voltage = smps_voltage_round(
		PMIC_SMPS_MPU, opp_mpu_turbo.voltage);
	genlist_addtail(&vdd44xx_mpu_opp_list,
			(void *) &opp_mpu_turbo, sizeof(opp_t));
	opp_mpu_nitro.voltage = smps_voltage_round(
		PMIC_SMPS_MPU, opp_mpu_nitro.voltage);
	genlist_addtail(&vdd44xx_mpu_opp_list,
			(void *) &opp_mpu_nitro, sizeof(opp_t));
	opp_mpu_nitrosb.voltage = smps_voltage_round(
		PMIC_SMPS_MPU, opp_mpu_nitrosb.voltage);
	genlist_addtail(&vdd44xx_mpu_opp_list,
			(void *) &opp_mpu_nitrosb, sizeof(opp_t));

	opp_iva_dpll_casc.voltage = smps_voltage_round(
		PMIC_SMPS_MM, opp_iva_dpll_casc.voltage);
	genlist_addtail(&vdd44xx_iva_opp_list,
			(void *) &opp_iva_dpll_casc, sizeof(opp_t));
	opp_iva_opp50.voltage = smps_voltage_round(
		PMIC_SMPS_MM, opp_iva_opp50.voltage);
	genlist_addtail(&vdd44xx_iva_opp_list,
			(void *) &opp_iva_opp50, sizeof(opp_t));
	opp_iva_opp100.voltage = smps_voltage_round(
		PMIC_SMPS_MM, opp_iva_opp100.voltage);
	genlist_addtail(&vdd44xx_iva_opp_list,
			(void *) &opp_iva_opp100, sizeof(opp_t));
	opp_iva_turbo.voltage = smps_voltage_round(
		PMIC_SMPS_MM, opp_iva_turbo.voltage);
	genlist_addtail(&vdd44xx_iva_opp_list,
			(void *) &opp_iva_turbo, sizeof(opp_t));
	opp_iva_nitro.voltage = smps_voltage_round(
		PMIC_SMPS_MM, opp_iva_nitro.voltage);
	genlist_addtail(&vdd44xx_iva_opp_list,
			(void *) &opp_iva_nitro, sizeof(opp_t));
	opp_iva_nitrosb.voltage = smps_voltage_round(
		PMIC_SMPS_MM, opp_iva_nitrosb.voltage);
	genlist_addtail(&vdd44xx_iva_opp_list,
			(void *) &opp_iva_nitrosb, sizeof(opp_t));

	opp_core_dpll_casc.voltage = smps_voltage_round(
		PMIC_SMPS_CORE, opp_core_dpll_casc.voltage);
	genlist_addtail(&vdd44xx_core_opp_list,
			(void *) &opp_core_dpll_casc, sizeof(opp_t));
	opp_core_opp50_low.voltage = smps_voltage_round(
		PMIC_SMPS_CORE, opp_core_opp50_low.voltage);
	genlist_addtail(&vdd44xx_core_opp_list,
			(void *) &opp_core_opp50_low, sizeof(opp_t));
	opp_core_opp50_high.voltage = smps_voltage_round(
		PMIC_SMPS_CORE, opp_core_opp50_high.voltage);
	genlist_addtail(&vdd44xx_core_opp_list,
			(void *) &opp_core_opp50_high, sizeof(opp_t));
	opp_core_opp100_low.voltage = smps_voltage_round(
		PMIC_SMPS_CORE, opp_core_opp100_low.voltage);
	genlist_addtail(&vdd44xx_core_opp_list,
			(void *) &opp_core_opp100_low, sizeof(opp_t));
	opp_core_opp100_high.voltage = smps_voltage_round(
		PMIC_SMPS_CORE, opp_core_opp100_high.voltage);
	genlist_addtail(&vdd44xx_core_opp_list,
			(void *) &opp_core_opp100_high, sizeof(opp_t));
	opp_core_opp119_low.voltage = smps_voltage_round(
		PMIC_SMPS_CORE, opp_core_opp119_low.voltage);
	genlist_addtail(&vdd44xx_core_opp_list,
			(void *) &opp_core_opp119_low, sizeof(opp_t));
	opp_core_opp119_high.voltage = smps_voltage_round(
		PMIC_SMPS_CORE, opp_core_opp119_high.voltage);
	genlist_addtail(&vdd44xx_core_opp_list,
			(void *) &opp_core_opp119_high, sizeof(opp_t));
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp44xx_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void opp44xx_init(void)
{
	#ifdef OPP44XX_DEBUG
	opp_t opp;
	int i, count;
	voltdm44xx_id vdd;
	char name[VOLTDM44XX_MAX_NAME_LENGTH];
	#endif

	if (!opp44xx_init_done) {
		genlist_init(&vdd44xx_wkup_opp_list);
		genlist_init(&vdd44xx_mpu_opp_list);
		genlist_init(&vdd44xx_iva_opp_list);
		genlist_init(&vdd44xx_core_opp_list);

		if (cpu_is_omap4430()) {
			opp4430_init();
		} else if (cpu_is_omap4460()) {
			opp4460_init();
		} else if (cpu_is_omap4470()) {
			opp4470_init();
		} else {
			fprintf(stderr,
				"omapconf: %s(): cpu not supported!!!\n",
				__func__);
		}
		opp44xx_init_done = 1;

		#ifdef OPP44XX_DEBUG
		printf("%s(): init done.\n", __func__);
		printf("OPP List:\n");
		for (vdd = OMAP4_LDO_WKUP; vdd <= OMAP4_VDD_CORE; vdd++) {
			count = genlist_getcount(
				(genlist *) opp44xx_list_table[vdd]);
			voltdm44xx_get_name(vdd, name);
			printf("  %s (%d): ", name, count);
			for (i = 0; i < count; i++) {
				genlist_get((genlist *) opp44xx_list_table[vdd],
					i, (void *) &opp);
				printf("%s (%.1lfMHz, %.3lfV)",
					opp.name, khz2mhz(opp.rate),
					uv2v(opp.voltage));
				if (i != count - 1)
					printf(", ");
			}
			printf(".\n");
		}
		#endif
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp44xx_deinit
 * @BRIEF		free dynamically allocated internal data.
 * @DESCRIPTION		free dynamically allocated internal data.
 *			MUST BE CALLED AT END OF EXECUTION.
 *//*------------------------------------------------------------------------ */
void opp44xx_deinit(void)
{
	if (opp44xx_init_done) {
		genlist_free(&vdd44xx_wkup_opp_list);
		genlist_free(&vdd44xx_mpu_opp_list);
		genlist_free(&vdd44xx_iva_opp_list);
		genlist_free(&vdd44xx_core_opp_list);
		opp44xx_init_done = 0;
	}
	dprintf("%s(): deinit done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp44xx_id_get
 * @BRIEF		convert OPP provided as a string (as defined in opp.h)
 *			into a plaftorm-specific OPP ID (integer).
 * @RETURNS		plaftorm-specific OPP ID (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 * @param[in]		opp: OPP provided as a string (as defined in opp.h)
 * @DESCRIPTION		convert OPP provided as a string (as defined in opp.h)
 *			into a plaftorm-specific OPP ID (integer).
 *//*------------------------------------------------------------------------ */
int opp44xx_id_get(const char *opp)
{
	CHECK_NULL_ARG(opp, OMAPCONF_ERR_ARG);

	if (strcasecmp(opp, OPP_DPLL_CASC) == 0)
		return (int) OMAP4_OPPDPLL_CASC;
	else if (strcasecmp(opp, OPP_50) == 0)
		return (int) OMAP4_OPP50;
	else if (strcasecmp(opp, OPP_100) == 0)
		return (int) OMAP4_OPP100;
	else if (strcasecmp(opp, OPP_TURBO) == 0)
		return (int) OMAP4_OPP_TURBO;
	else if (strcasecmp(opp, OPP_NITRO) == 0)
		return (int) OMAP4_OPP_NITRO;
	else if (strcasecmp(opp, OPP_NITROSB) == 0)
		return (int) OMAP4_OPP_NITRO_SB;
	else if (strcasecmp(opp, OPP_50_LOW) == 0)
		return (int) OMAP447X_OPP50_LOW;
	else if (strcasecmp(opp, OPP_50_HIGH) == 0)
		return (int) OMAP447X_OPP50_HIGH;
	else if (strcasecmp(opp, OPP_100_LOW) == 0)
		return (int) OMAP447X_OPP100_LOW;
	else if (strcasecmp(opp, OPP_100_HIGH) == 0)
		return (int) OMAP447X_OPP100_HIGH;
	else if (strcasecmp(opp, OPP_119_LOW) == 0)
		return (int) OMAP447X_OPP119_LOW;
	else if (strcasecmp(opp, OPP_119_HIGH) == 0)
		return (int) OMAP447X_OPP119_HIGH;
	else
		return OMAPCONF_ERR_ARG;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp44xx_count_get
 * @BRIEF		return the number of OPP(s) of a given voltage domain
 * @RETURNS		number of OPP(s) (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		vdd_id: voltage domain ID
 * @DESCRIPTION		return the number of OPP(s) of a given voltage domain
 *//*------------------------------------------------------------------------ */
int opp44xx_count_get(voltdm44xx_id vdd_id)
{
	int count;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(vdd_id, OMAP4_VD_ID_MAX, OMAPCONF_ERR_ARG);

	opp44xx_init();

	count = genlist_getcount(opp44xx_list_table[vdd_id]);

	dprintf("%s(%d) = %d\n", __func__, vdd_id, count);
	return count;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp44xx_list_get
 * @BRIEF		return the list of OPP of a given voltage domain
 * @RETURNS		list of OPP of a given voltage domain in case of success
 *			NULL in case of error
 * @param[in]		vdd_id: voltage domain ID
 * @DESCRIPTION		return the list of OPP of a given voltage domain
 *//*------------------------------------------------------------------------ */
const genlist *opp44xx_list_get(voltdm44xx_id vdd_id)
{
	CHECK_CPU(44xx, NULL);
	CHECK_ARG_LESS_THAN(vdd_id, OMAP4_VD_ID_MAX, NULL);

	opp44xx_init();

	return opp44xx_list_table[vdd_id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp44xx_by_voltage_get
 * @BRIEF		return the current voltage domain OPP name,
 *			searched by voltages.
 * @RETURNS		current voltage domain OPP name (as defined in opp.h)
 *			NULL pointer in case of error or not found
 * @param[in]		vdd_id: voltage domain ID
 * @DESCRIPTION		return the current voltage domain OPP name,
 *			searched by voltages.
 *//*------------------------------------------------------------------------ */
#if 0
const char *opp44xx_by_voltage_get(voltdm44xx_id vdd_id)
{
	CHECK_CPU(44xx, NULL);
	CHECK_ARG_LESS_THAN(vdd_id, OMAP4_VD_ID_MAX, NULL);

	opp44xx_init();

	return opp_by_voltage_get(voltdm44xx_id2s(vdd_id), 1);
}
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp44xx_by_rate_get
 * @BRIEF		return the current voltage domain OPP name,
 *			searched by clock rates.
 * @RETURNS		current voltage domain OPP name (as defined in opp.h)
 *			NULL pointer in case of error or not found
 * @param[in]		vdd_id: voltage domain ID
 * @DESCRIPTION		return the current voltage domain OPP name,
 *			searched by clock rates.
 *//*------------------------------------------------------------------------ */
const char *opp44xx_by_rate_get(voltdm44xx_id vdd_id)
{
	const char *opp_name = NULL;
	int ret;
	clock44xx_id clk_id;
	mod44xx_id module_id;
	int opp_id;
	double rate = 0.0, rate_por = 0.0;
	double gpu_rate = 0.0, gpu_rate_por = 0.0;
	double dss_rate = 0.0, dss_rate_por = 0.0;
	opp_t opp;
	const genlist *opp_list;
	int i, opp_count;

	#ifdef OPP44XX_DEBUG
	char mname[MOD44XX_MAX_NAME_LENGTH];
	char cname[CLOCK44XX_MAX_NAME_LENGTH];
	char vname[VOLTDM44XX_MAX_NAME_LENGTH];
	#endif

	CHECK_CPU(44xx, NULL);
	CHECK_ARG_LESS_THAN(vdd_id, OMAP4_VD_ID_MAX, NULL);

	opp44xx_init();

	switch (vdd_id) {
	case OMAP4_LDO_WKUP:
		clk_id = OMAP4_L4_ICLK2;
		module_id = OMAP4_SARRAM;
		break;

	case OMAP4_VDD_MPU:
		clk_id = OMAP4_MPU_DPLL_CLK;
		module_id = OMAP4_MPU;
		break;

	case OMAP4_VDD_IVA:
		clk_id = OMAP4_IVAHD_ROOT_CLK;
		module_id = OMAP4_IVAHD;
		break;

	case OMAP4_VDD_CORE:
		clk_id = OMAP4_L3_ICLK;
		module_id = OMAP4_L3_1;
		break;

	default:
		fprintf(stderr,
			"omapconf: %s(): vdd_id (%u) >= OMAP4_VD_ID_MAX (%u) !!!\n",
			__func__, vdd_id, OMAP4_VD_ID_MAX);
		opp_name = NULL;
		goto opp44xx_by_rate_get_end;
	}

	#ifdef OPP44XX_DEBUG
	voltdm44xx_get_name(vdd_id, vname);
	printf("%s(): Looking for %s OPP ...\n", __func__, vname);
	#endif

	rate = clk44xx_get_clock_speed(clk_id, 1);
	if (rate < 0.0) {
		dprintf("%s(): could not retrieve clock speed!\n", __func__);
		goto opp44xx_by_rate_get_end;
	}
	dprintf("%s(): %s speed is %lfMHz\n", __func__,
		clk44xx_get_name(clk_id, cname), rate);
	if (!cpu_is_omap4430() && (vdd_id == OMAP4_VDD_CORE)) {
		gpu_rate = clk44xx_get_clock_speed(OMAP4_GFX_FCLK, 1);
		if (gpu_rate < 0.0) {
			dprintf(
				"%s(): could not retrieve GPU clock rate!\n",
				__func__);
			goto opp44xx_by_rate_get_end;
		}
		dprintf("%s(): GPU speed is %lfMHz\n", __func__, gpu_rate);
	}

	opp_list = opp44xx_list_get(vdd_id);
	if (opp_list == NULL) {
		dprintf("%s(): could not retrieve OPP list!\n", __func__);
		goto opp44xx_by_rate_get_end;
	}

	opp_count = opp44xx_count_get(vdd_id);
	if (opp_count <= 0) {
		dprintf("%s(): could not retrieve OPP count!\n", __func__);
		goto opp44xx_by_rate_get_end;
	}

	for (i = 0; i < opp_count; i++) {
		ret = genlist_get((genlist *) opp_list, i, (opp_t *) &opp);
		if (ret != 0) {
			dprintf("%s(): could not retrieve OPP from list!\n",
				__func__);
			goto opp44xx_by_rate_get_end;
		}

		opp_id = opp44xx_id_get(opp.name);
		if (opp_id < 0) {
			dprintf(
				"%s(): could not retrieve OPP ID from OPP name!\n",
				__func__);
			goto opp44xx_by_rate_get_end;
		}

		/*
		 * Retrieve module expected speed for this OPP
		 */
		ret = mod44xx_get_por_clk_speed(
			module_id, opp_id, &rate_por);
		if (ret != 0) {
			dprintf(
				"%s(): could not get %s %s POR speed! (%d)\n",
				__func__, mod44xx_get_name(
					module_id, mname),
				opp.name, ret);
			goto opp44xx_by_rate_get_end;
		}
		dprintf("%s(): %s POR Speed for %s is %lf\n",
			__func__,
			mod44xx_get_name(module_id, mname),
			opp.name, rate_por);

		if (cpu_is_omap4460() && (vdd_id == OMAP4_VDD_IVA) &&
			((int) rate == 124)) {
			/*
			 * Hack for Galaxy Nexus, observed with pastry
			 * Jelly Bean 4.2.1 (may/may not apply to other pastry)
			 */
			opp_name = OPP_50;
			goto opp44xx_by_rate_get_end;
		}
		if ((int) rate_por != (int) rate)
			continue;

		if (cpu_is_omap4470() && (vdd_id == OMAP4_VDD_CORE) &&
			(opp_id == OMAP447X_OPP100_LOW)) {
			/* for opp_id == OMAP447X_OPP100_LOW
			 * and opp_id == OMAP447X_OPP119_LOW
			 * L3 clock frequency is identical.
			 * Use GFX clock frequency to distinguish.
			 */
			ret = mod44xx_get_por_clk_speed(OMAP4_GFX,
					OMAP447X_OPP119_LOW, &gpu_rate_por);
			if (ret != 0) {
				dprintf(
					"%s(): could not get GPU OPP119_LOW POR speed! (%d)\n",
					__func__, ret);
				goto opp44xx_by_rate_get_end;
			}
			dprintf(
				"%s(): GPU POR Speed for OPP119_LOW is %lfMHz\n",
				__func__, gpu_rate_por);

			gpu_rate = clk44xx_get_clock_speed(OMAP4_GFX_FCLK, 1);
			if (gpu_rate < 0.0) {
				dprintf(
					"%s(): could not retrieve GPU clock rate!\n",
					__func__);
					goto opp44xx_by_rate_get_end;
			}
			dprintf("%s(): GPU speed is %lfMHz\n",
				__func__, gpu_rate);
			if ((int) gpu_rate == (int) gpu_rate_por) {
				opp_name = OPP_119_LOW;
				goto opp44xx_by_rate_get_end;
			} else {
				opp_name = OPP_100_LOW;
				goto opp44xx_by_rate_get_end;
			}
		} else if (cpu_is_omap4470() && (vdd_id == OMAP4_VDD_CORE) &&
			(opp_id == OMAP447X_OPP50_HIGH)) {
			/* for opp_id == OMAP447X_OPP50_HIGH
			 * and opp_id == OMAP447X_OPP100_HIGH
			 * L3 clock frequency is identical.
			 * Use DSS clock frequency to distinguish.
			 */
			ret = mod44xx_get_por_clk_speed(OMAP4_DISPC,
					OMAP447X_OPP50_HIGH, &dss_rate_por);
			if (ret != 0) {
				dprintf(
					"%s(): could not get DSS OMAP447X_OPP50_HIGH POR speed! (%d)\n",
					__func__, ret);
				goto opp44xx_by_rate_get_end;
			}
			dprintf(
				"%s(): DSS POR Speed for OMAP447X_OPP50_HIGH is %lfMHz\n",
				__func__, dss_rate_por);

			dss_rate = clk44xx_get_clock_speed(OMAP4_DSS_FCLK, 1);
			if (dss_rate < 0.0) {
				dprintf(
					"%s(): could not retrieve DSS clock rate!\n",
					__func__);
					goto opp44xx_by_rate_get_end;
			}
			dprintf("%s(): DSS speed is %lfMHz\n",
				__func__, dss_rate);
			if ((int) dss_rate == (int) dss_rate_por) {
				opp_name = OPP_50_HIGH;
				goto opp44xx_by_rate_get_end;
			} else {
				opp_name = OPP_100_HIGH;
				goto opp44xx_by_rate_get_end;
			}
		} else if (cpu_is_omap4460() && (vdd_id == OMAP4_VDD_CORE) &&
			(opp_id == OMAP4_OPP100)) {
			/* for opp_id == OMAP4_OPP_100
			 * and opp_id == OMAP4_OPP_119
			 * L3 clock frequencies are equal.
			 * Use GPU clock frequency to distinguish.
			 */
			ret = mod44xx_get_por_clk_speed(OMAP4_GFX,
					OMAP4_OPP_119, &gpu_rate_por);
			if (ret != 0) {
				dprintf(
					"%s(): could not get GPU OMAP4_OPP_119 POR speed! (%d)\n",
					__func__, ret);
				goto opp44xx_by_rate_get_end;
			}
			dprintf(
				"%s(): GPU POR Speed for OMAP4_OPP_119 is %lfMHz\n",
				__func__, gpu_rate_por);

			gpu_rate = clk44xx_get_clock_speed(OMAP4_GFX_FCLK, 1);
			if (gpu_rate < 0.0) {
				dprintf(
					"%s(): could not retrieve GPU clock rate!\n",
					__func__);
					goto opp44xx_by_rate_get_end;
			}
			dprintf("%s(): GPU speed is %lfMHz\n",
				__func__, gpu_rate);
			if ((int) gpu_rate == (int) gpu_rate_por) {
				opp_name = OPP_119;
				goto opp44xx_by_rate_get_end;
			} else {
				opp_name = OPP_100;
				goto opp44xx_by_rate_get_end;
			}
		} else {
			opp_name = opp.name;
			goto opp44xx_by_rate_get_end;
		}
	}

opp44xx_by_rate_get_end:
	#ifdef OPP44XX_DEBUG
	if (opp_name == NULL)
		printf("%s(): OPP not found!\n", __func__);
	else
		printf("%s(): OPP found: %s\n", __func__, opp_name);
	#endif

	return opp_name;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp44xx_get
 * @BRIEF		return the current voltage domain OPP name.
 * @RETURNS		current voltage domain OPP name (as defined in opp.h)
 *			NULL pointer in case of error or not found
 * @param[in]		vdd_id: voltage domain ID
 * @DESCRIPTION		return the current voltage domain OPP name. Search it by
 *			voltage first, then if failed search it by rates.
 *//*------------------------------------------------------------------------ */
const char *opp44xx_get(voltdm44xx_id vdd_id)
{
	CHECK_CPU(44xx, NULL);
	CHECK_ARG_LESS_THAN(vdd_id, OMAP4_VD_ID_MAX, NULL);

	opp44xx_init();

	return opp_get(voltdm44xx_id2s(vdd_id), 1);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp44xx_set
 * @BRIEF		change OPP of a given voltage domain.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		vdd_id: voltage domain ID
 * @param[in]		opp_id: ID of the OPP to be set
 * @DESCRIPTION		change OPP of a given voltage domain.
 *//*------------------------------------------------------------------------ */
int opp44xx_set(voltdm44xx_id vdd_id, opp44xx_id opp_id)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(vdd_id, OMAP4_VD_ID_MAX, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(opp_id, OPP44XX_ID_MAX, OMAPCONF_ERR_ARG);

	opp44xx_init();

	printf("Sorry, not yet implemented.\n");

	return OMAPCONF_ERR_NOT_AVAILABLE;
}
