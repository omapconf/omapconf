/*
 *
 * @Component			OMAPCONF
 * @Filename			opp54xx.c
 * @Description			OMAP5 OPerating Point (OPP) Common Definitions
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


#include <string.h>
#include <opp.h>
#include <lib.h>
#include <cpuinfo.h>
#include <genlist.h>
#include <module.h>
#include <opp54xx.h>
#include <clock54xx.h>
#include <module54xx.h>


/* #define OPP54XX_DEBUG */
#ifdef OPP54XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


genlist vdd54xx_wkup_opp_list;
genlist vdd54xx_mpu_opp_list;
genlist vdd54xx_mm_opp_list;
genlist vdd54xx_core_opp_list;

genlist *opp54xx_list_table_es1[VDD54XX_ID_MAX] = {
		&vdd54xx_wkup_opp_list, /* VDD_WKUP */
		&vdd54xx_mpu_opp_list, /* VDD_MPU */
		&vdd54xx_mm_opp_list, /* VDD_MM */
		&vdd54xx_core_opp_list}; /* VDD_CORE */

static unsigned short opp54xx_init_done = 0;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp54xx_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void opp54xx_init(void)
{
	opp_t opp;

	/* ES1.0 */
	static const opp_t mpu_opp_low_es1  = {OPP_LOW,	 950000,  400000};
	static const opp_t mpu_opp_nom_es1  = {OPP_NOM,	 1040000, 800000};
	static const opp_t mpu_opp_high_es1 = {OPP_HIGH, 1220000, 1100000};

	static const opp_t mm_opp_low_es1 =  {OPP_LOW,	950000,  177333};
	static const opp_t mm_opp_nom_es1 =  {OPP_NOM,	1040000, 354667};
	static const opp_t mm_opp_high_es1 = {OPP_HIGH,	1220000, 532000};

	static const opp_t core_opp_low_es1 = {OPP_LOW,	950000,  133000};
	static const opp_t core_opp_nom_es1 = {OPP_NOM,	1040000, 2660000};

	/* ES2.0 */
	static const opp_t mpu_opp_low  = {OPP_LOW,	880000,  500000};
	static const opp_t mpu_opp_nom  = {OPP_NOM,	1060000, 1100000};
	static const opp_t mpu_opp_high = {OPP_HIGH,	1250000, 1500000};
	static const opp_t mpu_opp_sb =   {OPP_SB,	1290000, 1700000};

	static const opp_t mm_opp_low =  {OPP_LOW,	880000,  195000};
	static const opp_t mm_opp_nom =  {OPP_NOM,	1030000, 389000};
	static const opp_t mm_opp_high = {OPP_HIGH,	1120000, 532000};

	static const opp_t core_opp_low = {OPP_LOW,	880000,  133000};
	static const opp_t core_opp_nom = {OPP_NOM,	1040000, 2660000};

	#ifdef OPP54XX_DEBUG
	int i, count;
	voltdm54xx_id vdd;
	#endif

	if (!opp54xx_init_done) {
		genlist_init(&vdd54xx_wkup_opp_list);
		opp.name = OPP_NOM;
		opp.voltage = 1.0;
		opp.rate = clk54xx_sysclk_rate_get();
		genlist_addtail(&vdd54xx_wkup_opp_list,
			(void *) &opp, sizeof(opp_t));

		genlist_init(&vdd54xx_mpu_opp_list);
		if (cpu_revision_get() == REV_ES1_0) {
			genlist_addtail(&vdd54xx_mpu_opp_list,
				(void *) &mpu_opp_low_es1, sizeof(opp_t));
			genlist_addtail(&vdd54xx_mpu_opp_list,
				(void *) &mpu_opp_nom_es1, sizeof(opp_t));
			genlist_addtail(&vdd54xx_mpu_opp_list,
				(void *) &mpu_opp_high_es1, sizeof(opp_t));

			genlist_init(&vdd54xx_mm_opp_list);
			genlist_addtail(&vdd54xx_mm_opp_list,
				(void *) &mm_opp_low_es1, sizeof(opp_t));
			genlist_addtail(&vdd54xx_mm_opp_list,
				(void *) &mm_opp_nom_es1, sizeof(opp_t));
			genlist_addtail(&vdd54xx_mm_opp_list,
				(void *) &mm_opp_high_es1, sizeof(opp_t));

			genlist_init(&vdd54xx_core_opp_list);
			genlist_addtail(&vdd54xx_core_opp_list,
				(void *) &core_opp_low_es1, sizeof(opp_t));
			genlist_addtail(&vdd54xx_core_opp_list,
				(void *) &core_opp_nom_es1, sizeof(opp_t));
		} else {
			genlist_addtail(&vdd54xx_mpu_opp_list,
				(void *) &mpu_opp_low, sizeof(opp_t));
			genlist_addtail(&vdd54xx_mpu_opp_list,
				(void *) &mpu_opp_nom, sizeof(opp_t));
			genlist_addtail(&vdd54xx_mpu_opp_list,
				(void *) &mpu_opp_high, sizeof(opp_t));
			genlist_addtail(&vdd54xx_mpu_opp_list,
				(void *) &mpu_opp_sb, sizeof(opp_t));

			genlist_init(&vdd54xx_mm_opp_list);
			genlist_addtail(&vdd54xx_mm_opp_list,
				(void *) &mm_opp_low, sizeof(opp_t));
			genlist_addtail(&vdd54xx_mm_opp_list,
				(void *) &mm_opp_nom, sizeof(opp_t));
			genlist_addtail(&vdd54xx_mm_opp_list,
				(void *) &mm_opp_high, sizeof(opp_t));

			genlist_init(&vdd54xx_core_opp_list);
			genlist_addtail(&vdd54xx_core_opp_list,
				(void *) &core_opp_low, sizeof(opp_t));
			genlist_addtail(&vdd54xx_core_opp_list,
				(void *) &core_opp_nom, sizeof(opp_t));
		}

		opp54xx_init_done = 1;
		#ifdef OPP54XX_DEBUG
		printf("%s(): init done.\n", __func__);
		printf("OPP List:\n");
		for (vdd = VDD54XX_WKUP; vdd <= VDD54XX_CORE; vdd++) {
			count = genlist_getcount(
				(genlist *) opp54xx_list_table_es1[vdd]);
			printf("  %s (%d): ", voltdm54xx_name_get(vdd), count);
			for (i = 0; i < count; i++) {
				genlist_get(
					(genlist *) opp54xx_list_table_es1[vdd],
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
 * @FUNCTION		opp54xx_deinit
 * @BRIEF		free dynamically allocated internal data.
 * @DESCRIPTION		free dynamically allocated internal data.
 *			MUST BE CALLED AT END OF EXECUTION.
 *//*------------------------------------------------------------------------ */
void opp54xx_deinit(void)
{
	if (opp54xx_init_done) {
		genlist_free(&vdd54xx_wkup_opp_list);
		genlist_free(&vdd54xx_mpu_opp_list);
		genlist_free(&vdd54xx_mm_opp_list);
		genlist_free(&vdd54xx_core_opp_list);
		opp54xx_init_done = 0;

	}
	dprintf("%s(): deinit done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp54xx_id_get
 * @BRIEF		convert OPP provided as a string (as defined in opp.h)
 *			into a plaftorm-specific OPP ID (integer).
 * @RETURNS		plaftorm-specific OPP ID (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 * @param[in]		opp: OPP provided as a string (as defined in opp.h)
 * @DESCRIPTION		convert OPP provided as a string (as defined in opp.h)
 *			into a plaftorm-specific OPP ID (integer).
 *//*------------------------------------------------------------------------ */
int opp54xx_id_get(const char *opp)
{
	CHECK_NULL_ARG(opp, OMAPCONF_ERR_ARG);

	if (strcasecmp(opp, OPP_DPLL_CASC) == 0)
		return (int) OPP54XX_DPLL_CASC;
	else if (strcasecmp(opp, OPP_LOW) == 0)
		return (int) OPP54XX_LOW;
	else if (strcasecmp(opp, OPP_NOM) == 0)
		return (int) OPP54XX_NOM;
	else if (strcasecmp(opp, OPP_HIGH) == 0)
		return (int) OPP54XX_HIGH;
	else if (strcasecmp(opp, OPP_SB) == 0)
		return (int) OPP54XX_SB;
	else
		return OMAPCONF_ERR_ARG;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp54xx_count_get
 * @BRIEF		return the number of OPP(s) of a given voltage domain
 * @RETURNS		number of OPP(s) (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		vdd_id: voltage domain ID
 * @DESCRIPTION		return the number of OPP(s) of a given voltage domain
 *//*------------------------------------------------------------------------ */
int opp54xx_count_get(voltdm54xx_id vdd_id)
{
	int count;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(vdd_id, VDD54XX_ID_MAX, OMAPCONF_ERR_ARG);

	opp54xx_init();

	count = genlist_getcount(opp54xx_list_table_es1[vdd_id]);

	dprintf("%s(%d) = %d\n", __func__, vdd_id, count);
	return count;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp54xx_list_get
 * @BRIEF		return the list of OPP of a given voltage domain
 * @RETURNS		list of OPP of a given voltage domain in case of success
 *			NULL in case of error
 * @param[in]		vdd_id: voltage domain ID
 * @DESCRIPTION		return the list of OPP of a given voltage domain
 *//*------------------------------------------------------------------------ */
const genlist *opp54xx_list_get(voltdm54xx_id vdd_id)
{
	CHECK_CPU(54xx, NULL);
	CHECK_ARG_LESS_THAN(vdd_id, VDD54XX_ID_MAX, NULL);

	opp54xx_init();

	return opp54xx_list_table_es1[vdd_id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp54xx_by_voltage_get
 * @BRIEF		return the current voltage domain OPP name,
 *			searched by voltages.
 * @RETURNS		current voltage domain OPP name (as defined in opp.h)
 *			NULL pointer in case of error or not found
 * @param[in]		vdd_id: voltage domain ID
 * @DESCRIPTION		return the current voltage domain OPP name,
 *			searched by voltages.
 *//*------------------------------------------------------------------------ */
#if 0
const char *opp54xx_by_voltage_get(voltdm54xx_id vdd_id)
{
	CHECK_CPU(54xx, NULL);
	CHECK_ARG_LESS_THAN(vdd_id, VDD54XX_ID_MAX, NULL);

	opp54xx_init();

	return opp_by_voltage_get(voltdm54xx_id2s(vdd_id), 1);
}
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp54xx_by_rate_get
 * @BRIEF		return the current voltage domain OPP name,
 *			searched by clock rates.
 * @RETURNS		current voltage domain OPP name (as defined in opp.h)
 *			NULL pointer in case of error or not found
 * @param[in]		vdd_id: voltage domain ID
 * @DESCRIPTION		return the current voltage domain OPP name,
 *			searched by clock rates.
 *//*------------------------------------------------------------------------ */
const char *opp54xx_by_rate_get(voltdm54xx_id vdd_id)
{
	const char *opp_name = NULL;
	int opp_id;
	const char *module_name;
	double rate = 0.0, rate_por = 0.0;
	double rate_dsp = 0.0, rate_dsp_por = 0.0;
	double rate_gpu = 0.0, rate_gpu_por = 0.0;
	opp_t opp;
	const genlist *opp_list;
	int i, ret, opp_count;

	CHECK_CPU(54xx, NULL);
	CHECK_ARG_LESS_THAN(vdd_id, VDD54XX_ID_MAX, NULL);

	/*
	 * Determine current OPPs by getting MPU / IVA / L3 / SARRAM rate
	 * and comparing it to POR rate.
	 */
	switch (vdd_id) {
	case VDD54XX_WKUP:
		module_name = MOD_L4_WKUP_INTERCONNECT;
		break;

	case VDD54XX_MPU:
		module_name = MOD_MPU;
		break;

	case VDD54XX_MM:
		module_name = MOD_IVA;
		break;

	case VDD54XX_CORE:
		module_name = MOD_L3_MAIN1_INTERCONNECT;
		break;

	default:
		return NULL;
	}

	/*
	 * If the DPLL clocking the selected module is stopped,
	 * reported speed will be 0 and OPP cannot be detected.
	 * Hence, ignore DPLL status.
	 */
	rate = (double) module_clk_rate_get(module_name, 1) / 1000.0;
	if (rate < 0.0) {
		dprintf("%s(): could not retrieve clock speed!\n", __func__);
		goto opp54xx_by_rate_get_end;
	}
	dprintf("%s(%s): %s rate is %lfMHz\n", __func__,
		voltdm54xx_name_get(vdd_id),
		clk54xx_name_get(module_clk_get(module_name)), rate);
	if (vdd_id == VDD54XX_MM) {
		rate_dsp = (double) module_clk_rate_get(MOD_DSP, 1) / 1000.0;
		if (rate_dsp < 0.0) {
			dprintf("%s(): could not retrieve clock speed!\n",
				__func__);
			goto opp54xx_by_rate_get_end;
		}
		dprintf("%s(%s): DSP rate is %lfMHz\n", __func__,
			voltdm54xx_name_get(vdd_id), rate_dsp);
		rate_gpu = (double) module_clk_rate_get(MOD_GPU, 1) / 1000.0;
		if (rate_gpu < 0.0) {
			dprintf("%s(): could not retrieve clock speed!\n",
				__func__);
			goto opp54xx_by_rate_get_end;
		}
		dprintf("%s(%s): GPU rate is %lfMHz\n", __func__,
			voltdm54xx_name_get(vdd_id), rate_gpu);
	}

	opp_list = opp54xx_list_get(vdd_id);
	if (opp_list == NULL) {
		dprintf("%s(): could not retrieve OPP list!\n", __func__);
		goto opp54xx_by_rate_get_end;
	}

	opp_count = opp54xx_count_get(vdd_id);
	if (opp_count <= 0) {
		dprintf("%s(): could not retrieve OPP count!\n", __func__);
		goto opp54xx_by_rate_get_end;
	}


	for (i = 0; i < opp_count; i++) {
		ret = genlist_get((genlist *) opp_list, i, (opp_t *) &opp);
		if (ret != 0) {
			dprintf("%s(): could not retrieve OPP from list!\n",
				__func__);
			goto opp54xx_by_rate_get_end;
		}

		opp_id = opp54xx_id_get(opp.name);
		if (opp_id < 0) {
			dprintf(
				"%s(): could not retrieve OPP ID from OPP name!\n",
				__func__);
			goto opp54xx_by_rate_get_end;
		}

		rate_por = (double) module_por_clk_rate_get(module_name, opp.name) / 1000.0;
		if (rate_por < 0) {
			dprintf(
				"%s(): could not get %s %s POR speed! (%d)\n",
				__func__, module_name,
				opp.name, ret);
			goto opp54xx_by_rate_get_end;
		}
		dprintf("%s(%s): %s POR rate for %s is %lf\n",
			__func__, voltdm54xx_name_get(vdd_id),
			module_name, opp.name, rate_por);
		if (vdd_id == VDD54XX_MM) {
			rate_dsp_por =
				(double) module_por_clk_rate_get(MOD_DSP, opp.name) / 1000.0;
			if (rate_dsp_por < 0) {
				dprintf(
					"%s(): could not get DSP %s POR speed! (%d)\n",
					__func__, opp.name, ret);
				goto opp54xx_by_rate_get_end;
			}
			dprintf("%s(%s): DSP POR rate for %s is %lf\n",
				__func__, voltdm54xx_name_get(vdd_id),
				opp.name, rate_dsp_por);
			rate_gpu_por =
				(double) module_por_clk_rate_get(MOD_GPU, opp.name) / 1000.0;
			if (rate_gpu_por < 0) {
				dprintf(
					"%s(): could not get GPU %s POR speed! (%d)\n",
					__func__, opp.name, ret);
				goto opp54xx_by_rate_get_end;
			}
			dprintf("%s(%s): GPU POR rate for %s is %lf\n",
				__func__, voltdm54xx_name_get(vdd_id),
				opp.name, rate_gpu_por);

			if (((int) rate == (int) rate_por) &&
				 ((int) rate_dsp == (int) rate_dsp_por) &&
				 ((int) rate_gpu == (int) rate_gpu_por)) {
				opp_name = opp.name;
				goto opp54xx_by_rate_get_end;
			}
		} else {
			if ((int) rate == (int) rate_por) {
				opp_name = opp.name;
				goto opp54xx_by_rate_get_end;
			}
		}
	}

	dprintf("%s(%s): OPP not found!\n",
		__func__, voltdm54xx_name_get(vdd_id));

opp54xx_by_rate_get_end:
	#ifdef OPP54XX_DEBUG
	if (opp_name == NULL)
		printf("%s(%s): OPP not found!\n", __func__,
			voltdm54xx_name_get(vdd_id));
	else
		printf("%s(%s): OPP found: %s\n", __func__,
			voltdm54xx_name_get(vdd_id), opp_name);
	#endif
	return opp_name;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp54xx_get
 * @BRIEF		return the current voltage domain OPP name.
 * @RETURNS		current voltage domain OPP name (as defined in opp.h)
 *			NULL pointer in case of error or not found
 * @param[in]		vdd_id: voltage domain ID
 * @DESCRIPTION		return the current voltage domain OPP name. Search it by
 *			voltage first, then if failed search it by rates.
 *//*------------------------------------------------------------------------ */
const char *opp54xx_get(voltdm54xx_id vdd_id)
{
	CHECK_CPU(54xx, NULL);
	CHECK_ARG_LESS_THAN(vdd_id, VDD54XX_ID_MAX, NULL);

	opp54xx_init();

	return opp_get(voltdm54xx_id2s(vdd_id), 1);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp54xx_set
 * @BRIEF		change OPP of a given voltage domain.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		vdd_id: voltage domain ID
 * @param[in]		opp_id: ID of the OPP to be set
 * @DESCRIPTION		change OPP of a given voltage domain.
 *//*------------------------------------------------------------------------ */
int opp54xx_set(voltdm54xx_id vdd_id, opp54xx_id opp_id)
{
	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(vdd_id, VDD54XX_ID_MAX, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(opp_id, OPP54XX_ID_MAX, OMAPCONF_ERR_ARG);

	opp54xx_init();

	printf("Sorry, not yet implemented...\n");

	return OMAPCONF_ERR_NOT_AVAILABLE;
}
