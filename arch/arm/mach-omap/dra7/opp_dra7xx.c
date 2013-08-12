/*
 *
 * @Component			OMAPCONF
 * @Filename			opp_dra7xx.c
 * @Description			DRA7 OPerating Point (OPP) Common Definitions
 *				& Functions
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


#include <string.h>
#include <opp_dra7xx.h>
#include <opp.h>
#include <lib.h>
#include <cpuinfo.h>
#include <genlist.h>
#include <module.h>
#include <clock_dra7xx.h>
#include <module_dra7xx.h>
#include <voltdm_dra7xx.h>


/* #define OPP_DRA7XX_DEBUG */
#ifdef OPP_DRA7XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


genlist vdd_dra7xx_core_opp_list;
genlist vdd_dra7xx_mpu_opp_list;
genlist vdd_dra7xx_iva_opp_list;
genlist vdd_dra7xx_dspeve_opp_list;
genlist vdd_dra7xx_gpu_opp_list;
genlist vdd_dra7xx_rtc_opp_list;

genlist *opp_dra7xx_list_table[VDD_DRA7XX_ID_MAX] = {
		[VDD_DRA7XX_CORE] = &vdd_dra7xx_core_opp_list,
		[VDD_DRA7XX_MPU] = &vdd_dra7xx_mpu_opp_list,
		[VDD_DRA7XX_IVA] = &vdd_dra7xx_iva_opp_list,
		[VDD_DRA7XX_DSPEVE] = &vdd_dra7xx_dspeve_opp_list,
		[VDD_DRA7XX_GPU] = &vdd_dra7xx_gpu_opp_list,
		[VDD_DRA7XX_RTC] = &vdd_dra7xx_rtc_opp_list};

static unsigned short opp_dra7xx_init_done;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp_dra7xx_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void opp_dra7xx_init(void)
{
	static const opp_t core_opp_nom = {OPP_NOM,	1030000, 266000};

	static const opp_t mpu_opp_nom  = {OPP_NOM,	1060000, 1000000};
	static const opp_t mpu_opp_od =   {OPP_OD,	1160000, 1176000};
	static const opp_t mpu_opp_high = {OPP_HIGH,	1250000, 1500000};

	/*
	 * opp_dra7xx_list is just a reference of how many opp that a
	 * voltage manager has, so only need to add either dsp or eve,
	 * to indicating there are opp_nom, and opp_od for VDD_DSPEVE.
	 */
	static const opp_t dsp_opp_nom =  {OPP_NOM,	1060000, 600000};
	static const opp_t dsp_opp_od =   {OPP_OD,	1150000, 700000};

	static const opp_t iva_opp_nom  = {OPP_NOM,	1060000, 388300};
	static const opp_t iva_opp_od =   {OPP_OD,	1160000, 430000};
	static const opp_t iva_opp_high = {OPP_HIGH,	1250000, 532000};

	static const opp_t gpu_opp_nom  = {OPP_NOM,	1060000, 425600};
	static const opp_t gpu_opp_od =   {OPP_OD,	1160000, 500000};
	static const opp_t gpu_opp_high = {OPP_HIGH,	1250000, 532000};

	static const opp_t rtc_opp_nom = {OPP_NOM,	1030000, 34000};

	#ifdef OPP_DRA7XX_DEBUG
	int i, count;
	voltdm_dra7xx_id vdd;
	#endif

	if (!opp_dra7xx_init_done) {
		genlist_init(&vdd_dra7xx_core_opp_list);
		genlist_addtail(&vdd_dra7xx_core_opp_list,
			(void *) &core_opp_nom, sizeof(opp_t));

		genlist_init(&vdd_dra7xx_mpu_opp_list);
		genlist_addtail(&vdd_dra7xx_mpu_opp_list,
			(void *) &mpu_opp_nom, sizeof(opp_t));
		genlist_addtail(&vdd_dra7xx_mpu_opp_list,
			(void *) &mpu_opp_od, sizeof(opp_t));
		genlist_addtail(&vdd_dra7xx_mpu_opp_list,
			(void *) &mpu_opp_high, sizeof(opp_t));

		genlist_init(&vdd_dra7xx_dspeve_opp_list);
		genlist_addtail(&vdd_dra7xx_dspeve_opp_list,
			(void *) &dsp_opp_nom, sizeof(opp_t));
		genlist_addtail(&vdd_dra7xx_dspeve_opp_list,
			(void *) &dsp_opp_od, sizeof(opp_t));

		genlist_init(&vdd_dra7xx_iva_opp_list);
		genlist_addtail(&vdd_dra7xx_iva_opp_list,
			(void *) &iva_opp_nom, sizeof(opp_t));
		genlist_addtail(&vdd_dra7xx_iva_opp_list,
			(void *) &iva_opp_od, sizeof(opp_t));
		genlist_addtail(&vdd_dra7xx_iva_opp_list,
			(void *) &iva_opp_high, sizeof(opp_t));

		genlist_init(&vdd_dra7xx_gpu_opp_list);
		genlist_addtail(&vdd_dra7xx_gpu_opp_list,
			(void *) &gpu_opp_nom, sizeof(opp_t));
		genlist_addtail(&vdd_dra7xx_gpu_opp_list,
			(void *) &gpu_opp_od, sizeof(opp_t));
		genlist_addtail(&vdd_dra7xx_gpu_opp_list,
			(void *) &gpu_opp_high, sizeof(opp_t));

		genlist_init(&vdd_dra7xx_rtc_opp_list);
		genlist_addtail(&vdd_dra7xx_rtc_opp_list,
			(void *) &rtc_opp_nom, sizeof(opp_t));

		opp_dra7xx_init_done = 1;
		#ifdef OPP_DRA7XX_DEBUG
		printf("%s(): init done.\n", __func__);
		printf("OPP List:\n");
		for (vdd = VDD_DRA7XX_WKUP; vdd < VDD_DRA7XX_ID_MAX; vdd++) {
			count = genlist_getcount(
				(genlist *) opp_dra7xx_list_table[vdd]);
			printf("  %s (%d): ", voltdm_dra7xx_name_get(vdd), count);
			for (i = 0; i < count; i++) {
				genlist_get(
					(genlist *) opp_dra7xx_list_table[vdd],
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
 * @FUNCTION		opp_dra7xx_deinit
 * @BRIEF		free dynamically allocated internal data.
 * @DESCRIPTION		free dynamically allocated internal data.
 *			MUST BE CALLED AT END OF EXECUTION.
 *//*------------------------------------------------------------------------ */
void opp_dra7xx_deinit(void)
{
	if (opp_dra7xx_init_done) {
		genlist_free(&vdd_dra7xx_mpu_opp_list);
		genlist_free(&vdd_dra7xx_iva_opp_list);
		genlist_free(&vdd_dra7xx_dspeve_opp_list);
		genlist_free(&vdd_dra7xx_gpu_opp_list);
		genlist_free(&vdd_dra7xx_core_opp_list);
		genlist_free(&vdd_dra7xx_rtc_opp_list);
		opp_dra7xx_init_done = 0;

	}
	dprintf("%s(): deinit done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp_dra7xx_id_get
 * @BRIEF		convert OPP provided as a string (as defined in opp.h)
 *			into a plaftorm-specific OPP ID (integer).
 * @RETURNS		plaftorm-specific OPP ID (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 * @param[in]		opp: OPP provided as a string (as defined in opp.h)
 * @DESCRIPTION		convert OPP provided as a string (as defined in opp.h)
 *			into a plaftorm-specific OPP ID (integer).
 *//*------------------------------------------------------------------------ */
int opp_dra7xx_id_get(const char *opp)
{
	CHECK_NULL_ARG(opp, OMAPCONF_ERR_ARG);

	if (strcasecmp(opp, OPP_NOM) == 0)
		return (int) OPP_DRA7XX_NOM;
	else if (strcasecmp(opp, OPP_OD) == 0)
		return (int) OPP_DRA7XX_OD;
	else if (strcasecmp(opp, OPP_HIGH) == 0)
		return (int) OPP_DRA7XX_HIGH;
	else
		return OMAPCONF_ERR_ARG;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp_dra7xx_count_get
 * @BRIEF		return the number of OPP(s) of a given voltage domain
 * @RETURNS		number of OPP(s) (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		vdd_id: voltage domain ID
 * @DESCRIPTION		return the number of OPP(s) of a given voltage domain
 *//*------------------------------------------------------------------------ */
int opp_dra7xx_count_get(voltdm_dra7xx_id vdd_id)
{
	int count;

	CHECK_ARG_LESS_THAN(vdd_id, VDD_DRA7XX_ID_MAX, OMAPCONF_ERR_ARG);

	opp_dra7xx_init();

	count = genlist_getcount(opp_dra7xx_list_table[vdd_id]);

	dprintf("%s(%d) = %d\n", __func__, vdd_id, count);
	return count;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp_dra7xx_list_get
 * @BRIEF		return the list of OPP of a given voltage domain
 * @RETURNS		list of OPP of a given voltage domain in case of success
 *			NULL in case of error
 * @param[in]		vdd_id: voltage domain ID
 * @DESCRIPTION		return the list of OPP of a given voltage domain
 *//*------------------------------------------------------------------------ */
const genlist *opp_dra7xx_list_get(voltdm_dra7xx_id vdd_id)
{
	CHECK_ARG_LESS_THAN(vdd_id, VDD_DRA7XX_ID_MAX, NULL);

	opp_dra7xx_init();

	return opp_dra7xx_list_table[vdd_id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp_dra7xx_by_rate_get
 * @BRIEF		return the current voltage domain OPP name,
 *			searched by clock rates.
 * @RETURNS		current voltage domain OPP name (as defined in opp.h)
 *			NULL pointer in case of error or not found
 * @param[in]		vdd_id: voltage domain ID
 * @DESCRIPTION		return the current voltage domain OPP name,
 *			searched by clock rates.
 *//*------------------------------------------------------------------------ */
const char *opp_dra7xx_by_rate_get(voltdm_dra7xx_id vdd_id)
{
	const char *opp_name = NULL;
	int opp_id;
	const char *module_name;
	double rate = 0.0, rate_por = 0.0;
	double rate_eve = 0.0, rate_eve_por = 0.0;
	opp_t opp;
	const genlist *opp_list;
	int i, ret, opp_count;

	CHECK_ARG_LESS_THAN(vdd_id, VDD_DRA7XX_ID_MAX, NULL);

	/*
	 * Determine current OPPs by getting MPU / IVA / L3 / DSPEVE / GPU rate
	 * and comparing it to POR rate.
	 */
	switch (vdd_id) {
	case VDD_DRA7XX_CORE:
		module_name = MOD_L3_MAIN1_INTERCONNECT;
		break;

	case VDD_DRA7XX_MPU:
		module_name = MOD_MPU;
		break;

	case VDD_DRA7XX_IVA:
		module_name = MOD_IVAHD;
		break;

	case VDD_DRA7XX_DSPEVE:
		module_name = MOD_DSP1;
		/* special case, need to check both DSP and EVE */
		break;

	case VDD_DRA7XX_GPU:
		module_name = MOD_GPU;
		break;

	case VDD_DRA7XX_RTC:
		return OPP_NOM;
		/* module_name = TBD; */
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
		goto opp_dra7xx_by_rate_get_end;
	}
	dprintf("%s(%s): %s rate is %lfMHz\n", __func__,
		voltdm_dra7xx_name_get(vdd_id),
		clk_dra7xx_name_get(module_clk_get(module_name)), rate);
	if (vdd_id == VDD_DRA7XX_DSPEVE) {
		rate_eve = (double) module_clk_rate_get(MOD_EVE1, 1) / 1000.0;
		if (rate_eve < 0.0) {
			dprintf("%s(): could not retrieve clock speed!\n",
				__func__);
			goto opp_dra7xx_by_rate_get_end;
		}
		dprintf("%s(%s): EVE rate is %lfMHz\n", __func__,
			voltdm_dra7xx_name_get(vdd_id), rate_eve);
	}

	opp_list = opp_dra7xx_list_get(vdd_id);
	if (opp_list == NULL) {
		dprintf("%s(): could not retrieve OPP list!\n", __func__);
		goto opp_dra7xx_by_rate_get_end;
	}

	opp_count = opp_dra7xx_count_get(vdd_id);
	if (opp_count <= 0) {
		dprintf("%s(): could not retrieve OPP count!\n", __func__);
		goto opp_dra7xx_by_rate_get_end;
	}


	for (i = 0; i < opp_count; i++) {
		ret = genlist_get((genlist *) opp_list, i, (opp_t *) &opp);
		if (ret != 0) {
			dprintf("%s(): could not retrieve OPP from list!\n",
				__func__);
			goto opp_dra7xx_by_rate_get_end;
		}

		opp_id = opp_dra7xx_id_get(opp.name);
		if (opp_id < 0) {
			dprintf(
				"%s(): could not retrieve OPP ID from OPP name!\n",
				__func__);
			goto opp_dra7xx_by_rate_get_end;
		}

		rate_por = (double) module_por_clk_rate_get(module_name, opp.name) / 1000.0;
		if (rate_por < 0) {
			dprintf(
				"%s(): could not get %s %s POR speed! (%d)\n",
				__func__, module_name,
				opp.name, ret);
			goto opp_dra7xx_by_rate_get_end;
		}
		dprintf("%s(%s): %s POR rate for %s is %lf\n",
			__func__, voltdm_dra7xx_name_get(vdd_id),
			module_name, opp.name, rate_por);
		if (vdd_id == VDD_DRA7XX_DSPEVE) {
			rate_eve_por =
				(double) module_por_clk_rate_get(MOD_EVE1, opp.name) / 1000.0;
			if (rate_eve_por < 0) {
				dprintf(
					"%s(): could not get GPU %s POR speed! (%d)\n",
					__func__, opp.name, ret);
				goto opp_dra7xx_by_rate_get_end;
			}
			dprintf("%s(%s): EVE POR rate for %s is %lf\n",
				__func__, voltdm_dra7xx_name_get(vdd_id),
				opp.name, rate_eve_por);

			if (((int) rate == (int) rate_por) &&
				 ((int) rate_eve == (int) rate_eve_por)) {
				opp_name = opp.name;
				goto opp_dra7xx_by_rate_get_end;
			}
		} else {
			if ((int) rate == (int) rate_por) {
				opp_name = opp.name;
				goto opp_dra7xx_by_rate_get_end;
			}
		}
	}

	dprintf("%s(%s): OPP not found!\n",
		__func__, voltdm_dra7xx_name_get(vdd_id));

opp_dra7xx_by_rate_get_end:
	#ifdef OPP_DRA7XX_DEBUG
	if (opp_name == NULL)
		printf("%s(%s): OPP not found!\n", __func__,
			voltdm_dra7xx_name_get(vdd_id));
	else
		printf("%s(%s): OPP found: %s\n", __func__,
			voltdm_dra7xx_name_get(vdd_id), opp_name);
	#endif
	return opp_name;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp_dra7xx_get
 * @BRIEF		return the current voltage domain OPP name.
 * @RETURNS		current voltage domain OPP name (as defined in opp.h)
 *			NULL pointer in case of error or not found
 * @param[in]		vdd_id: voltage domain ID
 * @DESCRIPTION		return the current voltage domain OPP name. Search it by
 *			voltage first, then if failed search it by rates.
 *//*------------------------------------------------------------------------ */
const char *opp_dra7xx_get(voltdm_dra7xx_id vdd_id)
{
	CHECK_ARG_LESS_THAN(vdd_id, VDD_DRA7XX_ID_MAX, NULL);

	opp_dra7xx_init();

	return opp_get(voltdm_dra7xx_id2s(vdd_id), 1);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp_dra7xx_set
 * @BRIEF		change OPP of a given voltage domain.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		vdd_id: voltage domain ID
 * @param[in]		opp_id: ID of the OPP to be set
 * @DESCRIPTION		change OPP of a given voltage domain.
 *//*------------------------------------------------------------------------ */
int opp_dra7xx_set(voltdm_dra7xx_id vdd_id, opp_dra7xx_id opp_id)
{
	CHECK_ARG_LESS_THAN(vdd_id, VDD_DRA7XX_ID_MAX, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(opp_id, OPP_DRA7XX_ID_MAX, OMAPCONF_ERR_ARG);

	opp_dra7xx_init();

	printf("Sorry, not yet implemented...\n");

	return OMAPCONF_ERR_NOT_AVAILABLE;
}
