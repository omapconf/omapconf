/*
 *
 * @Component			OMAPCONF
 * @Filename			opp.c
 * @Description			OPerating Point (OPP) Common Definitions
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


#include <opp.h>
#include <cpuinfo.h>
#include <lib.h>
#include <string.h>
#include <voltdomain.h>
#include <autoadjust_table.h>
#include <temperature.h>
#include <cpufreq.h>
#include <opp44xx.h>
#include <clock44xx.h>
#include <prcm-module.h>
#include <module.h>
#include <module44xx.h>
#include <opp54xx.h>
#include <unistd.h>


/* #define OPP_DEBUG */
#ifdef OPP_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


#define OPP_MAX_RETRY		10


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void opp_init(void)
{
	if (cpu_is_omap44xx()) {
		opp44xx_init();
	} else if (cpu_is_omap54xx()) {
		opp54xx_init();
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp_deinit
 * @BRIEF		free dynamically allocated internal data.
 * @DESCRIPTION		free dynamically allocated internal data.
 *			MUST BE CALLED AT END OF EXECUTION.
 *//*------------------------------------------------------------------------ */
void opp_deinit(void)
{
	if (cpu_is_omap44xx()) {
		opp44xx_deinit();
	} else if (cpu_is_omap54xx()) {
		opp54xx_deinit();
	} else if (cpu_is_dra7xx()) {
		/* FIXME: Here add opp_dra7xx_deinit() */
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp_s2id
 * @BRIEF		convert OPP provided as a string (as defined in opp.h)
 *			into a plaftorm-specific OPP ID (integer).
 * @RETURNS		plaftorm-specific OPP ID (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 * @param[in]		opp: OPP provided as a string (as defined in opp.h)
 * @DESCRIPTION		convert OPP provided as a string (as defined in opp.h)
 *			into a plaftorm-specific OPP ID (integer).
 *//*------------------------------------------------------------------------ */
int opp_s2id(const char *opp)
{
	if (cpu_is_omap44xx()) {
		return opp44xx_id_get(opp);
	} else if (cpu_is_omap54xx()) {
		return opp54xx_id_get(opp);
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		return OMAPCONF_ERR_CPU;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp_list_get
 * @BRIEF		return the list of OPP of a given voltage domain
 * @RETURNS		list of OPP of a given voltage domain in case of success
 *			NULL in case of error
 * @param[in]		voltdm: voltage domain name (as defined in voltdm.h)
 * @DESCRIPTION		return the list of OPP of a given voltage domain
 *//*------------------------------------------------------------------------ */
const genlist *opp_list_get(const char *voltdm)
{
	int vdd_id;

	CHECK_NULL_ARG(voltdm, NULL);

	opp_init();

	vdd_id = voltdm_s2id(voltdm);
	if (vdd_id < 0)
		return NULL;

	if (cpu_is_omap44xx()) {
		return opp44xx_list_get((voltdm44xx_id) vdd_id);
	} else if (cpu_is_omap54xx()) {
		return opp54xx_list_get((voltdm54xx_id) vdd_id);
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		return NULL;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp_count_get
 * @BRIEF		return the number of OPP(s) of a given voltage domain
 * @RETURNS		number of OPP(s) (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		voltdm: voltage domain name (as defined in voltdm.h)
 * @DESCRIPTION		return the number of OPP(s) of a given voltage domain
 *//*------------------------------------------------------------------------ */
int opp_count_get(const char *voltdm)
{
	int vdd_id;

	CHECK_NULL_ARG(voltdm, OMAPCONF_ERR_ARG);

	opp_init();

	vdd_id = voltdm_s2id(voltdm);
	if (vdd_id < 0)
		return OMAPCONF_ERR_ARG;

	if (cpu_is_omap44xx()) {
		return opp44xx_count_get((voltdm44xx_id) vdd_id);
	} else if (cpu_is_omap54xx()) {
		return opp54xx_count_get((voltdm54xx_id) vdd_id);
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		return OMAPCONF_ERR_CPU;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp_set
 * @BRIEF		change OPP of a given voltage domain.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		voltdm: voltage domain name (as defined in voltdm.h)
 * @param[in]		opp: name of OPP to be set (as defined in opp.h)
 * @DESCRIPTION		change OPP of a given voltage domain.
 *//*------------------------------------------------------------------------ */
int opp_set(const char *voltdm, const char *opp)
{
	int vdd_id, opp_id;

	CHECK_NULL_ARG(voltdm, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(opp, OMAPCONF_ERR_ARG);

	opp_init();

	vdd_id = voltdm_s2id(voltdm);
	if (vdd_id < 0)
		return OMAPCONF_ERR_ARG;

	opp_id = opp_s2id(opp);
	if (opp_id < 0)
		return OMAPCONF_ERR_ARG;

	if (cpu_is_omap44xx()) {
		return opp44xx_set((voltdm44xx_id) vdd_id, (opp44xx_id) opp_id);
	} else if (cpu_is_omap54xx()) {
		return opp54xx_set((voltdm54xx_id) vdd_id, (opp54xx_id) opp_id);
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		return OMAPCONF_ERR_CPU;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp_by_rate_get
 * @BRIEF		return the current voltage domain OPP name,
 *			searched by clock rates.
 * @RETURNS		current voltage domain OPP name (as defined in opp.h)
 *			NULL pointer in case of error
 * @param[in]		voltdm: voltage domain name (as defined in voltdm.h)
 * @param[in]		quiet: if == 0, print warning message when OPP
 *			could not be found
 * @DESCRIPTION		return the current voltage domain OPP,
 *			searched by clock rates.
 *//*------------------------------------------------------------------------ */
const char *opp_by_rate_get(const char *voltdm, unsigned short quiet)
{
	const char *opp = NULL;
	int vdd_id;

	CHECK_NULL_ARG(voltdm, NULL);

	opp_init();

	vdd_id = voltdm_s2id(voltdm);
	if (vdd_id < 0)
		return NULL;

	if (cpu_is_omap44xx()) {
		opp = opp44xx_by_rate_get(vdd_id);
	} else if (cpu_is_omap54xx()) {
		opp = opp54xx_by_rate_get(vdd_id);
	} else {
		fprintf(stderr, "omapconf: %s(): cpu not supported!!!\n",
			__func__);
		opp = NULL;
	}

	if ((quiet == 0) && (opp == NULL))
		fprintf(stdout,
			"omapconf: warning: no matching rate for %s OPP. Please check rates against Data Manual recommendations.\n",
			voltdm);

	#ifdef OPP_DEBUG
	if (opp != NULL)
		printf("%s(%s): found %s OPP\n", __func__, voltdm, opp);
	else
		printf("%s(%s): OPP not found!\n", __func__, voltdm);
	#endif
	return opp;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp_by_voltage_get
 * @BRIEF		return the current voltage domain OPP name,
 *			searched by voltages.
 * @RETURNS		current voltage domain OPP name (as defined in opp.h)
 *			NULL pointer in case of error
 * @param[in]		voltdm: voltage domain name (as defined in voltdm.h)
 * @param[in]		quiet: if == 0, print warning message when OPP
 *			could not be found
 * @DESCRIPTION		return the current voltage domain OPP name,
 *			searched by voltages.
 *//*------------------------------------------------------------------------ */
#if 0
const char *opp_by_voltage_get(const char *voltdm, unsigned short quiet)
{
	int volt;
	opp_t opp;
	const genlist *opp_list;
	int i, opp_count;
	const char *opp_name = NULL;
	const char *opp_name2 = NULL;

	CHECK_NULL_ARG(voltdm, NULL);

	opp_init();

	volt = voltdm_nominal_voltage_get(voltdm);
	if (volt < 0) {
		dprintf("%s(%s): could not get voltage!\n", __func__, voltdm);
		return NULL;
	}
	dprintf("%s(%s): nominal voltage is %duV\n", __func__, voltdm, volt);

	opp_list = opp_list_get(voltdm);
	if (opp_list == NULL) {
		dprintf("%s(%s): could not get OPP list!\n", __func__, voltdm);
		return NULL;
	}

	opp_count = opp_count_get(voltdm);
	if (opp_count <= 0) {
		dprintf("%s(%s): could not get OPP count!\n", __func__, voltdm);
		return NULL;
	}
	dprintf("%s(%s): found %d possible OPP\n", __func__, voltdm, opp_count);

	for (i = 0; i < opp_count; i++) {
		genlist_get((genlist *) opp_list, i, (opp_t *) &opp);
		dprintf("%s(%s): POR nominal voltage for %s is %duV\n",
			__func__, voltdm, opp.name, opp.voltage);
		if (volt == opp.voltage) {
			/*
			 * OPP DPLL_CASC and OPP[50-NOM] shares the same
			 * voltage.
			 * This is also the case for OPP_NITRO and OPP_NITRO_SB.
			 * Must double-check with frequencies.
			 */
			if ((strcmp(opp.name, OPP_DPLL_CASC) != 0) &&
				(strcmp(opp.name, OPP_NITRO) != 0)) {
				opp_name = opp.name;
				dprintf("%s(%s): OPP found: %s\n", __func__,
				voltdm, opp_name);
				break;
			}
			dprintf(
				"%s(%s): %s found, double-checking using rates (same voltage apply to more than 1 OPP.\n",
				__func__, voltdm, opp.name);
			opp_name2 = opp_by_rate_get(voltdm, 1);
			if (strcmp(opp_name2, opp.name) == 0) {
				opp_name = opp.name;
				dprintf("%s(%s): OPP found: %s\n", __func__,
				voltdm, opp_name);
				break;
			}
			dprintf(
				"%s(%s): this was not %s, but probably the next one.\n",
				__func__, voltdm, opp.name);
		}
	}

	if ((quiet == 0) && (opp_name == NULL))
		fprintf(stdout,
			"omapconf: warning: no matching %s OPP for %lfV nominal voltage. Please check voltage against Data Manual recommendations.\n",
			voltdm, uv2v(volt));

	return opp_name;
}
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp_get
 * @BRIEF		return the current voltage domain OPP name
 * @RETURNS		current voltage domain OPP name (as defined in opp.h)
 *			NULL pointer in case of error
 * @param[in]		voltdm: voltage domain name (as defined in voltdm.h)
 * @param[in]		quiet: if == 0, print warning message when OPP
 *			could not be found
 * @DESCRIPTION		return the current voltage domain OPP name. Search it by
 *			voltage first, then if failed search it by rates.
 *//*------------------------------------------------------------------------ */
const char *opp_get(const char *voltdm, unsigned int quiet)
{
	const char *opp = NULL;

	CHECK_NULL_ARG(voltdm, NULL);

	opp_init();

	/*
	 *
	 * Due to Smart-Reflex AVS Class1.5 which dynamically updates nominal
	 * voltages, it is not possible to search OPP using nominal voltages.
	 * Even if SR AVS Class1.5 could be disabled before and
	 * during the search, it is considered too constraining,
	 * as it would reset the voltage and force a new calibration to happen.
	 * Also if it was ever needed to print the current voltage, it would
	 * have to be done before the search, otherwise it may not always show
	 * the converged voltage.
	 *
	 * Another reason to skip it is that we want to be really strict,
	 * then OPP is a strict combination of voltage and frequency.
	 * which means we would have to search by voltage AND by frequency,
	 * and only consider it OK if both are found and are matching.
	 *
	 */
#if 0
	dprintf("%s(%s): searching OPP by voltage first:\n", __func__, voltdm);
	opp = opp_by_voltage_get(voltdm, quiet);
	if (opp != NULL) {
		dprintf("%s(%s): OPP search by voltage succeeded.\n",
			__func__, voltdm);
		goto opp_get_end;
	}
	/*
	 * Could not detect OPP using voltage, try again
	 * using frequencies instead.
	 */
	dprintf("%s(): OPP search by voltage failed, try using rate instead.\n",
		__func__);
#endif
	opp = opp_by_rate_get(voltdm, quiet);

#if 0
opp_get_end:
#endif
	#ifdef OPP_DEBUG
	if (opp != NULL)
		printf("%s(%s): found %s OPP\n", __func__, voltdm, opp);
	else
		printf("%s(%s): OPP not found!\n", __func__, voltdm);
	#endif

	return opp;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp_show
 * @BRIEF		show current operating voltages and key clock rates.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in,out]	stream: output file stream (opened, != NULL)
 * @DESCRIPTION		show current operating voltages and key clock rates.
 *//*------------------------------------------------------------------------ */
int opp_show(FILE *stream)
{
	int volt, volt2;
	const char *opp_s, *opp_s2;
	int temp;
	int rate_mpu, rate_mpu_por;
	int rate_dsp, rate_iva, rate_gpu;
	int rate_dsp_por, rate_iva_por, rate_gpu_por, rate_aess_por;
	int rate_l3, rate_l3_por;
	int rate_l4, rate_emif, rate_lpddr2, rate_aess, rate_iss,
		rate_fdif, rate_dss, rate_bb2d, rate_hsi;
	mod_module_mode mmode;
	int rate_cal, rate_ipu, rate_c2c;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row = 0;
	unsigned int retry_cnt = 0;
	unsigned int found = 0;
	const genlist *voltdm_list;
	voltdm_info voltdm;
	int i, vdd_count;
	char prev_gov[CPUFREQ_GOV_MAX_NAME_LENGTH],
		prev_gov2[CPUFREQ_GOV_MAX_NAME_LENGTH];
	const char *temp_sensor;

	/* Switch to userspace governor temporarily,
	 * so that OPP cannot change during audit and does not false it.
	 */
	cpufreq_scaling_governor_set("userspace", prev_gov);

	autoadjust_table_init(table);
	row = 0;
	strncpy(table[row][1], "Temperature", TABLE_MAX_ELT_LEN);
	strncpy(table[row][2], "Voltage", TABLE_MAX_ELT_LEN);
	strncpy(table[row][3], "Frequency", TABLE_MAX_ELT_LEN);
	strncpy(table[row][4], "OPerating Point", TABLE_MAX_ELT_LEN);
	row++;

	/*
	 * In order to make sure all details (OPP, voltage, clock rates) are
	 * coherent (due to potential OPP change in between), must use a loop,
	 * checking that OPP and voltage did not change and that at least ONE
	 * clock rate is aligned to expected rate for the detected OPP.
	 */
	dprintf("%s():\n", __func__);

	voltdm_list = voltdm_list_get();
	if (voltdm_list == NULL)
		return OMAPCONF_ERR_INTERNAL;
	vdd_count = voltdm_count_get();
	if (vdd_count < 0)
		return OMAPCONF_ERR_INTERNAL;
	dprintf("found %d voltage domains\n", vdd_count);
	for (i = 1; i < vdd_count; i++) {
		genlist_get((genlist *) voltdm_list, i,
			(voltdm_info *) &voltdm);
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "%s / VDD_CORE%u",
				voltdm.name, i);
		dprintf("  %s:\n", voltdm.name);

		/* Retrieve OPP and clock rates */
		retry_cnt = 0;
		found = 0;
		do {
			dprintf("    TRY #%u:\n", retry_cnt);
			if (retry_cnt == 0)
				/* Print warning on first try */
				opp_s = opp_get(voltdm.name, 0);
			else
				opp_s = opp_get(voltdm.name, 1);
			if (opp_s == NULL) {
				dprintf("      OPP NOT detected!\n");
				opp_s = OPP_UNKNOWN;
			} else {
				dprintf("      OPP detected: %s\n", opp_s);
			}

			volt = voltdm_voltage_get(voltdm.name);
			dprintf("      Voltage: %duV\n", volt);

			if (strcmp(voltdm.name, VDD_MPU) == 0) {
				rate_mpu = module_clk_rate_get(MOD_MPU, 1);
				if (strcmp(opp_s, OPP_UNKNOWN) != 0)
					rate_mpu_por = module_por_clk_rate_get(
						MOD_MPU, opp_s);
				else
					rate_mpu_por = -1;
				dprintf(
					"      MPU Rate: %dKHz, POR Rate: %dKHz\n",
					rate_mpu, rate_mpu_por);
			} else if ((strcmp(voltdm.name, VDD_IVA) == 0) ||
				(strcmp(voltdm.name, VDD_MM) == 0)) {
				rate_dsp_por = -1;
				rate_iva_por = -1;
				rate_aess_por = -1;
				rate_gpu_por = -1;
				rate_dsp = module_clk_rate_get(MOD_DSP, 1);
				if (cpu_is_omap44xx()) {
					rate_iva = module_clk_rate_get(
						MOD_IVAHD, 1);
					rate_aess = module_clk_rate_get(
						MOD_AESS, 1);
				} else if (cpu_is_omap54xx()) {
					rate_iva = module_clk_rate_get(
						MOD_IVA, 1);
					rate_gpu = module_clk_rate_get(
						MOD_GPU, 1);
				}

				if (strcmp(opp_s, OPP_UNKNOWN) != 0) {
					rate_dsp_por = module_por_clk_rate_get(
						MOD_DSP, opp_s);
					if (cpu_is_omap44xx()) {
						rate_iva_por =
							module_por_clk_rate_get(
								MOD_IVAHD, opp_s);
						rate_aess_por =
							module_por_clk_rate_get(
								MOD_AESS, opp_s);
					} else if (cpu_is_omap54xx()) {
						rate_iva_por =
							module_por_clk_rate_get(
								MOD_IVA, opp_s);
						rate_gpu_por =
							module_por_clk_rate_get(
								MOD_GPU, opp_s);
					}
				}
				dprintf(
					"      DSP Rate: %dMHz, POR Rate: %dMHz\n",
					rate_dsp, rate_dsp_por);
				dprintf(
					"      IVA Rate: %dMHz, POR Rate: %dMHz\n",
					rate_iva, rate_iva_por);
				if (cpu_is_omap44xx()) {
					dprintf(
						"      AESS Rate: %dMHz, POR Rate: %dMHz\n",
						rate_aess, rate_aess_por);
				} else if (cpu_is_omap54xx()) {
					dprintf(
						"      GPU Rate: %dMHz, POR Rate: %dMHz\n",
						rate_gpu, rate_gpu_por);
				}
			} else if (strcmp(voltdm.name, VDD_CORE) == 0) {
				rate_l3 = module_clk_rate_get(
					MOD_L3_MAIN1_INTERCONNECT, 1);
				if (strcmp(opp_s, OPP_UNKNOWN) != 0)
					rate_l3_por = module_por_clk_rate_get(
						MOD_L3_MAIN1_INTERCONNECT,
						opp_s);
				else
					rate_l3_por = -1;
				dprintf(
					"      L3_1 Rate: %dMHz, POR Rate: %dMHz\n",
					rate_l3, rate_l3_por);

				rate_emif = module_clk_rate_get(MOD_EMIF1, 1);
				if (cpu_is_omap44xx())
					rate_lpddr2 = module_clk_rate_get(
						MOD_DDRPHY, 1) / 2;
				else
					rate_lpddr2 = module_clk_rate_get(
						MOD_PHY_EMIF, 1);
				rate_l4 = module_clk_rate_get(
					MOD_L4_CFG_INTERCONNECT, 1);
				if (cpu_is_omap44xx())
					rate_gpu =
						module_clk_rate_get(MOD_SGX, 1);
				else if (cpu_is_omap54xx())
					rate_aess = module_clk_rate_get(
						MOD_AESS, 1);
				rate_iss = module_clk_rate_get(MOD_ISS, 1);
				rate_fdif = module_clk_rate_get(MOD_FDIF, 1);
				if (!cpu_is_omap44xx())
					rate_cal =
						module_clk_rate_get(MOD_CAL, 1);
				else
					rate_cal = -1;
				if (cpu_is_omap44xx())
					rate_ipu = module_clk_rate_get(MOD_MPU_M3, 1);
				else
					rate_ipu = module_clk_rate_get(MOD_IPU, 1);
				if (cpu_is_omap44xx())
					rate_dss = module_clk_rate_get(MOD_DISPC, 1);
				else
					rate_dss = module_clk_rate_get(MOD_DSS, 1);
				rate_hsi = module_clk_rate_get(MOD_HSI, 1);
				if (cpu_is_omap4470() || cpu_is_omap54xx())
					rate_bb2d = module_clk_rate_get(
						MOD_BB2D, 1);
				else
					rate_bb2d = -1;
				rate_c2c = module_clk_rate_get(MOD_C2C, 1);
			}


			if (strcmp(opp_s, OPP_UNKNOWN) == 0) {
				dprintf(
					"      Could not detect OPP, aborting for this domain.\n");
				break;
			}

			opp_s2 = opp_get(voltdm.name, 1);
			if (opp_s2 == NULL) {
				dprintf("      OPP NOT detected! (2)\n");
				opp_s2 = OPP_UNKNOWN;
			} else {
				dprintf("      OPP detected: %s (2)\n", opp_s2);
			}

			volt2 = voltdm_voltage_get(voltdm.name);
			dprintf("      Voltage (2): %dV\n", volt2);

			if (strcmp(voltdm.name, VDD_MPU) == 0) {
				found = (((rate_mpu / 1000) == (rate_mpu_por / 1000)) &&
					(strcmp(opp_s, opp_s2) == 0) &&
					(volt == volt2));
			} else if (strcmp(voltdm.name, VDD_IVA) == 0) {
				found = ((strcmp(opp_s, opp_s2) == 0) &&
					(volt == volt2) &&
					(((rate_dsp / 1000) == (rate_dsp_por / 1000)) ||
						((rate_iva / 1000) == (rate_iva_por / 1000)) ||
						((rate_aess / 1000) == (rate_aess_por / 1000))));
			} else if (strcmp(voltdm.name, VDD_MM) == 0) {
				found = ((strcmp(opp_s, opp_s2) == 0) &&
					(volt == volt2) &&
					(((rate_dsp / 1000) == (rate_dsp_por / 1000)) ||
						((rate_iva / 1000) == (rate_iva_por / 1000)) ||
						((rate_gpu / 1000) == (rate_gpu_por / 1000))));
			} else if (strcmp(voltdm.name, VDD_CORE) == 0) {
				found = ((strcmp(opp_s, opp_s2) == 0) &&
					(volt == volt2) &&
					((rate_l3 / 1000) == (rate_l3_por / 1000)));
			}
			dprintf("      found=%u\n", found);

			retry_cnt++;
		} while ((retry_cnt < OPP_MAX_RETRY) && (found == 0));

		/* Print temperature */
		temp_sensor = temp_sensor_voltdm2sensor(voltdm.name);
		if (temp_sensor == NULL) {
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "NA");
		} else {
			temp = temp_sensor_get(temp_sensor);
			if (temp != TEMP_ABSOLUTE_ZERO)
				snprintf(table[row][1], TABLE_MAX_ELT_LEN,
					"%dC / %dF", temp,
					celcius2fahrenheit(temp));
			else
				snprintf(table[row][1], TABLE_MAX_ELT_LEN,
					"NA");
		}

		/* Print voltage */
		if (volt < 0)
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "NA");
		else if (!cpu_is_omap44xx())
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%.3lf V",
				uv2v(volt));
		else
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%.6lf V",
				uv2v(volt));

		/* Print OPP */
		if (retry_cnt < OPP_MAX_RETRY) {
			strncpy(table[row][4], opp_s,
				TABLE_MAX_ELT_LEN);
		} else {
			fprintf(stderr,
				"omapconf: too many %s OPP changes, could not retrieve it!!!\n",
				voltdm.name);
			strncpy(table[row][4], "ERROR", TABLE_MAX_ELT_LEN);
		}
		row++;

		/* Print clock rates */
		if (strcmp(voltdm.name, VDD_MPU) == 0) {
			if (cpu_is_online(1) == 1)
				strncpy(table[row][0], "  MPU (CPU1 ON)",
					TABLE_MAX_ELT_LEN);
			else
				strncpy(table[row][0], "  MPU (CPU1 OFF)",
					TABLE_MAX_ELT_LEN);
			snprintf(table[row][3], TABLE_MAX_ELT_LEN, " %-4d MHz",
				rate_mpu / 1000);
			row += 2;
		} else if ((strcmp(voltdm.name, VDD_IVA) == 0) ||
			(strcmp(voltdm.name, VDD_MM) == 0)) {
			strncpy(table[row][0], "  IVA", TABLE_MAX_ELT_LEN);
			if (cpu_is_omap44xx())
				mod44xx_get_mode(OMAP4_IVAHD, &mmode); /* FIXME */
			else
				mmode = module_mode_get(MOD_IVA);
			if (mmode == MOD_DISABLED_MODE)
				snprintf(table[row][3], TABLE_MAX_ELT_LEN,
					"(%-4d MHz) (1)", rate_iva / 1000);
			else
				snprintf(table[row][3], TABLE_MAX_ELT_LEN,
					" %-4d MHz", rate_iva / 1000);
			row++;

			if (cpu_is_omap44xx()) {
				strncpy(table[row][0], "  AESS",
					TABLE_MAX_ELT_LEN);
				mod44xx_get_mode(OMAP4_AESS, &mmode); /* FIXME */
				if (mmode == MOD_DISABLED_MODE)
					snprintf(table[row][3],
						TABLE_MAX_ELT_LEN,
						"(%-4d MHz) (1)",
						rate_aess / 1000);
				else
					snprintf(table[row][3],
						TABLE_MAX_ELT_LEN,
						" %-4d MHz", rate_aess / 1000);
				row++;
			} else if (cpu_is_omap54xx()) {
				strncpy(table[row][0], "  GPU",
					TABLE_MAX_ELT_LEN);
				mmode = module_mode_get(MOD_GPU);
				if (mmode == MOD_DISABLED_MODE)
					snprintf(table[row][3],
						TABLE_MAX_ELT_LEN,
						"(%-4d MHz) (1)",
						rate_gpu / 1000);
				else
					snprintf(table[row][3],
						TABLE_MAX_ELT_LEN,
						" %-4d MHz", rate_gpu / 1000);
				row++;
			}

			strncpy(table[row][0], "  DSP", TABLE_MAX_ELT_LEN);
			if (cpu_is_omap44xx())
				mod44xx_get_mode(OMAP4_DSP, &mmode); /* FIXME */
			else
				mmode = module_mode_get(MOD_DSP);
			if (mmode == MOD_DISABLED_MODE)
				snprintf(table[row][3], TABLE_MAX_ELT_LEN,
					"(%-4d MHz) (1)", rate_dsp / 1000);
			else
				snprintf(table[row][3], TABLE_MAX_ELT_LEN,
					" %-4d MHz", rate_dsp / 1000);
			row += 2;
		} else if (strcmp(voltdm.name, VDD_CORE) == 0) {
			strncpy(table[row][0], "  L3", TABLE_MAX_ELT_LEN);
			snprintf(table[row][3], TABLE_MAX_ELT_LEN, " %-4d MHz",
				rate_l3 / 1000);
			row++;

			strncpy(table[row][0], "  DMM/EMIF", TABLE_MAX_ELT_LEN);
			snprintf(table[row][3], TABLE_MAX_ELT_LEN, " %-4d MHz",
				rate_emif / 1000);
			row++;

			strncpy(table[row][0], "    LP-DDR2",
				TABLE_MAX_ELT_LEN);
			snprintf(table[row][3], TABLE_MAX_ELT_LEN, " %-4d MHz",
				rate_lpddr2 / 1000);
			row++;

			strncpy(table[row][0], "  L4", TABLE_MAX_ELT_LEN);
			snprintf(table[row][3], TABLE_MAX_ELT_LEN, " %-4d MHz",
				rate_l4 / 1000);
			row++;

			if (cpu_is_omap44xx()) {
				strncpy(table[row][0], "  GPU",
					TABLE_MAX_ELT_LEN);
				mod44xx_get_mode(OMAP4_GFX, &mmode); /* FIXME */
				if (mmode == MOD_DISABLED_MODE)
					snprintf(table[row][3],
						TABLE_MAX_ELT_LEN,
						"(%-4d MHz) (1)",
						rate_gpu / 1000);
				else
					snprintf(table[row][3],
						TABLE_MAX_ELT_LEN,
						" %-4d MHz", rate_gpu / 1000);
				row++;
			} else if (cpu_is_omap54xx()) {
				strncpy(table[row][0], "  AESS",
					TABLE_MAX_ELT_LEN);
				mmode = module_mode_get(MOD_AESS);
				if (mmode == MOD_DISABLED_MODE)
					snprintf(table[row][3],
						TABLE_MAX_ELT_LEN,
						"(%-4d MHz) (1)",
						rate_aess / 1000);
				else
					snprintf(table[row][3],
						TABLE_MAX_ELT_LEN,
						" %-4d MHz", rate_aess / 1000);
				row++;
			}

			strncpy(table[row][0], "  FDIF", TABLE_MAX_ELT_LEN);
			if (cpu_is_omap44xx())
				mod44xx_get_mode(OMAP4_FDIF, &mmode); /* FIXME */
			else
				mmode = module_mode_get(MOD_FDIF);
			if (mmode == MOD_DISABLED_MODE)
				snprintf(table[row][3], TABLE_MAX_ELT_LEN,
					"(%-4d MHz) (1)", rate_fdif / 1000);
			else
				snprintf(table[row][3], TABLE_MAX_ELT_LEN,
					" %-4d MHz", rate_fdif / 1000);
			row++;

			if (cpu_is_omap54xx()) {
				strncpy(table[row][0], "  CAL",
					TABLE_MAX_ELT_LEN);
				mmode = module_mode_get(MOD_CAL);
				if (mmode == MOD_DISABLED_MODE)
					snprintf(table[row][3],
						TABLE_MAX_ELT_LEN,
						"(%-4d MHz) (1)",
						rate_cal / 1000);
				else
					snprintf(table[row][3],
						TABLE_MAX_ELT_LEN,
						" %-4d MHz",
						rate_cal / 1000);
				row++;
			}

			strncpy(table[row][0], "  IPU", TABLE_MAX_ELT_LEN);
			if (cpu_is_omap44xx())
				mod44xx_get_mode(OMAP4_MPU_M3, &mmode); /* FIXME */
			else
				mmode = module_mode_get(MOD_IPU);
			if (mmode == MOD_DISABLED_MODE)
				snprintf(table[row][3], TABLE_MAX_ELT_LEN,
					"(%-4d MHz) (1)", rate_ipu / 1000);
			else
				snprintf(table[row][3], TABLE_MAX_ELT_LEN,
					" %-4d MHz", rate_ipu / 1000);
			row++;
			if (cpu_is_omap44xx()) {
				strncpy(table[row][0], "    Cortex-M3 Cores",
					TABLE_MAX_ELT_LEN);
				if (mmode == MOD_DISABLED_MODE)
					snprintf(table[row][3],
						TABLE_MAX_ELT_LEN,
						"(%-4d MHz) (1)",
						rate_ipu / 2000);
				else
					snprintf(table[row][3],
						TABLE_MAX_ELT_LEN,
						" %-4d MHz", rate_ipu / 2000);
				row++;
			} else if (cpu_is_omap54xx()) {
				strncpy(table[row][0], "    Cortex-M4 Cores",
					TABLE_MAX_ELT_LEN);
				if (mmode == MOD_DISABLED_MODE)
					snprintf(table[row][3],
						TABLE_MAX_ELT_LEN,
						"(%-4d MHz) (1)",
						rate_ipu / 2000);
				else
					snprintf(table[row][3],
						TABLE_MAX_ELT_LEN,
						" %-4d MHz", rate_ipu / 2000);
				row++;
			}

			strncpy(table[row][0], "  ISS", TABLE_MAX_ELT_LEN);
			if (cpu_is_omap44xx())
				mod44xx_get_mode(OMAP4_ISS, &mmode); /* FIXME */
			else
				mmode = module_mode_get(MOD_ISS);
			if (mmode == MOD_DISABLED_MODE)
				snprintf(table[row][3], TABLE_MAX_ELT_LEN,
					"(%-4d MHz) (1)", rate_iss / 1000);
			else
				snprintf(table[row][3], TABLE_MAX_ELT_LEN,
					" %-4d MHz", rate_iss / 1000);
			row++;

			strncpy(table[row][0], "  DSS", TABLE_MAX_ELT_LEN);
			if (cpu_is_omap44xx())
				mod44xx_get_mode(OMAP4_DISPC, &mmode); /* FIXME */
			else
				mmode = module_mode_get(MOD_DSS);
			if (mmode == MOD_DISABLED_MODE)
				snprintf(table[row][3], TABLE_MAX_ELT_LEN,
					"(%-4d MHz) (1)", rate_dss / 1000);
			else
				snprintf(table[row][3], TABLE_MAX_ELT_LEN,
					" %-4d MHz", rate_dss / 1000);
			row++;

			if (cpu_is_omap4470() ||
				(cpu_is_omap54xx() && (cpu_revision_get() != REV_ES1_0))) {
				strncpy(table[row][0], "  BB2D",
					TABLE_MAX_ELT_LEN);
				if (cpu_is_omap44xx())
					mod44xx_get_mode(OMAP4_BB2D, &mmode); /* FIXME */
				else
					mmode = module_mode_get(MOD_BB2D);
				if (mmode == MOD_DISABLED_MODE)
					snprintf(table[row][3],
						TABLE_MAX_ELT_LEN,
						"(%-4d MHz) (1)",
						rate_bb2d / 1000);
				else
					snprintf(table[row][3],
						TABLE_MAX_ELT_LEN, " %-4d MHz",
						rate_bb2d / 1000);
				row++;
			}

			strncpy(table[row][0], "  HSI", TABLE_MAX_ELT_LEN);
			if (cpu_is_omap44xx())
				mod44xx_get_mode(OMAP4_HSI, &mmode); /* FIXME */
			else
				mmode = module_mode_get(MOD_HSI);
			if (mmode == MOD_DISABLED_MODE)
				snprintf(table[row][3], TABLE_MAX_ELT_LEN,
					"(%-4d MHz) (1)", rate_hsi / 1000);
			else
				snprintf(table[row][3], TABLE_MAX_ELT_LEN,
					" %-4d MHz", rate_hsi / 1000);
			row++;

			strncpy(table[row][0], "  C2C", TABLE_MAX_ELT_LEN);
			if (cpu_is_omap44xx())
				mod44xx_get_mode(OMAP4_C2C, &mmode); /* FIXME */
			else
				mmode = module_mode_get(MOD_C2C);
			if (mmode == MOD_DISABLED_MODE)
				snprintf(table[row][3], TABLE_MAX_ELT_LEN,
					"(%-4d MHz) (1)", rate_c2c / 1000);
			else
				snprintf(table[row][3], TABLE_MAX_ELT_LEN,
					" %-4d MHz", rate_c2c / 1000);
			row++;
		}
	}

	/* Display table */
	autoadjust_table_fprint(stream, table, row, 5);

	fprintf(stream, "Notes:\n");
	fprintf(stream,
		"  (1) Module is disabled, rate may not be relevant.\n\n");
	fflush(stream);

	/*
	 * Avoid cpufreq_interactive_input_connect message to be printed in
	 * the middle of the OPP table...
	 */
	usleep(150000);
	/* Restore CPUFreq governor */
	cpufreq_scaling_governor_set(prev_gov, prev_gov2);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp_audit
 * @BRIEF		OPP (Operating Point) audit. Assess for each OPP that
 *			both nominal voltage and frequency are aligned with
 *			recommendations, as specified in Data Manual.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in,out]	stream: output file (opened)
 * @param[in]		voltdm: voltage domain name (as defined in voltdm.h)
 * @param[in,out]	err_nbr: pointer to return audit error number
 * @param[in,out]	wng_nbr: pointer to return audit warning number
 * @DESCRIPTION		OPP (Operating Point) audit.
 *//*------------------------------------------------------------------------ */
const char *opp_audit(FILE *stream, const char *voltdm,
	unsigned int *err_nbr, unsigned int *wng_nbr)
{
	/* Check voltage and rates against Data Manual Recommendations */

	/* FIXME */
	stream = stream;
	voltdm = voltdm;
	err_nbr = err_nbr;
	wng_nbr = wng_nbr;

	return NULL;
}
