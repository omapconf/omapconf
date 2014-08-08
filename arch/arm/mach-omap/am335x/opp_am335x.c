/*
 *
 * @Component			OMAPCONF
 * @Filename			opp_am335x.c
 * @Description			AM335X OPerating Point (OPP) Common Definitions
 *				& Functions
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


#include <clock_am335x.h>
#include <cpuinfo.h>
#include <genlist.h>
#include <lib.h>
#include <module.h>
#include <module_am335x.h>
#include <opp.h>
#include <opp_am335x.h>
#include <string.h>
#include <voltdm_am335x.h>


#ifdef OPP_AM335X_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


genlist vdd_am335x_core_opp_list;
genlist vdd_am335x_mpu_opp_list;
genlist vdd_am335x_rtc_opp_list;

genlist *opp_am335x_list_table[VDD_AM335X_ID_MAX] = {
		[VDD_AM335X_CORE] = &vdd_am335x_core_opp_list,
		[VDD_AM335X_MPU] = &vdd_am335x_mpu_opp_list,
		[VDD_AM335X_RTC] = &vdd_am335x_rtc_opp_list};


static const char
	opp_am335x_names_table[OPP_AM335X_ID_MAX + 1][OPP_MAX_NAME_LENGTH] = {
	[OPP_AM335X_050] = "50",
	[OPP_AM335X_100] = "100",
	[OPP_AM335X_100_LOW] = "100_LOW",
	[OPP_AM335X_100_HIGH] = "100_HIGH",
	[OPP_AM335X_120] = "120",
	[OPP_AM335X_TURBO] = "TURBO",
	[OPP_AM335X_NITRO] = "NITRO",
	[OPP_AM335X_ID_MAX] = "UNKNOWN"};


static unsigned short opp_am335x_init_done;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp_am335x_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void opp_am335x_init(void)
{
	static const opp_t core_opp_50       = {OPP_50,		950000,  50000};
	static const opp_t core_opp_100	     = {OPP_100,	1100000, 100000};

	/* For AM335X REV_ES1_0 */
	static const opp_t mpu_opp_100_l_es1 = {OPP_100_LOW,	1100000, 275000};
	static const opp_t mpu_opp_100_h_es1 = {OPP_100_HIGH,	1100000, 500000};
	static const opp_t mpu_opp_120_es1   = {OPP_120,	1200000, 600000};
	static const opp_t mpu_opp_turbo_es1 = {OPP_TURBO,	1260000, 720000};

	/* For AM335X REV_ES2_X */
	static const opp_t mpu_opp_50	     = {OPP_50,		950000,  300000};
	static const opp_t mpu_opp_100_l     = {OPP_100_LOW,	1100000, 300000};
	static const opp_t mpu_opp_100_h     = {OPP_100_HIGH,	1100000, 600000};
	static const opp_t mpu_opp_120       = {OPP_120,	1200000, 720000};
	static const opp_t mpu_opp_turbo     = {OPP_TURBO,	1260000, 800000};
	static const opp_t mpu_opp_nitro     = {OPP_NITRO,	1325000, 1000000};

#ifdef OPP_AM335X_DEBUG
	int i, count;
	voltdm_am335x_id vdd;
	opp_t opp;
#endif

	if (!opp_am335x_init_done) {
		genlist_init(&vdd_am335x_core_opp_list);
		genlist_addtail(&vdd_am335x_core_opp_list,
			(void *) &core_opp_50, sizeof(opp_t));
		genlist_addtail(&vdd_am335x_core_opp_list,
			(void *) &core_opp_100, sizeof(opp_t));

		genlist_init(&vdd_am335x_mpu_opp_list);
		if (cpu_revision_get() >= REV_ES2_0) {
			genlist_addtail(&vdd_am335x_mpu_opp_list,
				(void *) &mpu_opp_50, sizeof(opp_t));
			genlist_addtail(&vdd_am335x_mpu_opp_list,
				(void *) &mpu_opp_100_l, sizeof(opp_t));
			genlist_addtail(&vdd_am335x_mpu_opp_list,
				(void *) &mpu_opp_100_h, sizeof(opp_t));
			genlist_addtail(&vdd_am335x_mpu_opp_list,
				(void *) &mpu_opp_120, sizeof(opp_t));
			genlist_addtail(&vdd_am335x_mpu_opp_list,
				(void *) &mpu_opp_turbo, sizeof(opp_t));
			genlist_addtail(&vdd_am335x_mpu_opp_list,
				(void *) &mpu_opp_nitro, sizeof(opp_t));
		}
		else {
			genlist_addtail(&vdd_am335x_mpu_opp_list,
				(void *) &mpu_opp_100_l_es1, sizeof(opp_t));
			genlist_addtail(&vdd_am335x_mpu_opp_list,
				(void *) &mpu_opp_100_h_es1, sizeof(opp_t));
			genlist_addtail(&vdd_am335x_mpu_opp_list,
				(void *) &mpu_opp_120_es1, sizeof(opp_t));
			genlist_addtail(&vdd_am335x_mpu_opp_list,
				(void *) &mpu_opp_turbo_es1, sizeof(opp_t));
		}

		genlist_init(&vdd_am335x_rtc_opp_list);

		opp_am335x_init_done = 1;
#ifdef OPP_AM335X_DEBUG
		printf("%s(): init done.\n", __func__);
		printf("OPP List:\n");
		for (vdd = 0; vdd < VDD_AM335X_ID_MAX; vdd++) {
			count = genlist_getcount(
				(genlist *) opp_am335x_list_table[vdd]);
			printf("  %s (%d): ", voltdm_am335x_name_get(vdd), count);
			for (i = 0; i < count; i++) {
				genlist_get(
					(genlist *) opp_am335x_list_table[vdd],
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
 * @FUNCTION		opp_am335x_deinit
 * @BRIEF		free dynamically allocated internal data.
 * @DESCRIPTION		free dynamically allocated internal data.
 *			MUST BE CALLED AT END OF EXECUTION.
 *//*------------------------------------------------------------------------ */
void opp_am335x_deinit(void)
{
	if (opp_am335x_init_done) {
		genlist_free(&vdd_am335x_mpu_opp_list);
		genlist_free(&vdd_am335x_core_opp_list);
		genlist_free(&vdd_am335x_rtc_opp_list);
		opp_am335x_init_done = 0;

	}
	dprintf("%s(): deinit done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp_am335x_id_get
 * @BRIEF		convert OPP provided as a string (as defined in opp.h)
 *			into a plaftorm-specific OPP ID (integer).
 * @RETURNS		plaftorm-specific OPP ID (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 * @param[in]		opp: OPP provided as a string (as defined in opp.h)
 * @DESCRIPTION		convert OPP provided as a string (as defined in opp.h)
 *			into a plaftorm-specific OPP ID (integer).
 *//*------------------------------------------------------------------------ */
int opp_am335x_id_get(const char *opp)
{
	CHECK_NULL_ARG(opp, OMAPCONF_ERR_ARG);

	if (strcasecmp(opp, OPP_50) == 0)
		return (int) OPP_AM335X_050;
	else if (strcasecmp(opp, OPP_100) == 0)
		return (int) OPP_AM335X_100;
	else if (strcasecmp(opp, OPP_100_LOW) == 0)
		return (int) OPP_AM335X_100_LOW;
	else if (strcasecmp(opp, OPP_100_HIGH) == 0)
		return (int) OPP_AM335X_100_HIGH;
	else if (strcasecmp(opp, OPP_120) == 0)
		return (int) OPP_AM335X_120;
	else if (strcasecmp(opp, OPP_TURBO) == 0)
		return (int) OPP_AM335X_TURBO;
	else if (strcasecmp(opp, OPP_NITRO) == 0)
		return (int) OPP_AM335X_NITRO;
	else
		return OMAPCONF_ERR_ARG;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp_am335x_count_get
 * @BRIEF		return the number of OPP(s) of a given voltage domain
 * @RETURNS		number of OPP(s) (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		vdd_id: voltage domain ID
 * @DESCRIPTION		return the number of OPP(s) of a given voltage domain
 *//*------------------------------------------------------------------------ */
int opp_am335x_count_get(voltdm_am335x_id vdd_id)
{
	int count;

	CHECK_ARG_LESS_THAN(vdd_id, VDD_AM335X_ID_MAX, OMAPCONF_ERR_ARG);

	opp_am335x_init();

	count = genlist_getcount(opp_am335x_list_table[vdd_id]);

	dprintf("%s(%d) = %d\n", __func__, vdd_id, count);
	return count;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp_am335x_list_get
 * @BRIEF		return the list of OPP of a given voltage domain
 * @RETURNS		list of OPP of a given voltage domain in case of success
 *			NULL in case of error
 * @param[in]		vdd_id: voltage domain ID
 * @DESCRIPTION		return the list of OPP of a given voltage domain
 *//*------------------------------------------------------------------------ */
const genlist *opp_am335x_list_get(voltdm_am335x_id vdd_id)
{
	CHECK_ARG_LESS_THAN(vdd_id, VDD_AM335X_ID_MAX, NULL);

	opp_am335x_init();

	return opp_am335x_list_table[vdd_id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp_am335x_by_rate_get
 * @BRIEF		return the current voltage domain OPP name,
 *			searched by clock rates.
 * @RETURNS		current voltage domain OPP name (as defined in opp.h)
 *			NULL pointer in case of error or not found
 * @param[in]		vdd_id: voltage domain ID
 * @DESCRIPTION		return the current voltage domain OPP name,
 *			searched by clock rates.
 *//*------------------------------------------------------------------------ */
const char *opp_am335x_by_rate_get(voltdm_am335x_id vdd_id)
{
	const char *opp_name = NULL;
	int opp_id;
	const char *module_name;
	double sys_clk, mult;
	double rate = 0.0, rate_por = 0.0;
	opp_t opp;
	const genlist *opp_list;
	int i, ret, opp_count;

	CHECK_ARG_LESS_THAN(vdd_id, VDD_AM335X_ID_MAX, NULL);

	/*
	 * Determine current OPPs by getting MPU / CORE rate
	 * and comparing it to POR rate.
	 */
	switch (vdd_id) {
	case VDD_AM335X_CORE:
		module_name = MOD_L3_MAIN1_INTERCONNECT;
		break;

	case VDD_AM335X_MPU:
		module_name = MOD_MPU;
		break;

	case VDD_AM335X_RTC:
		return NULL;
		/* module_name = TBD; */
		break;

	default:
		return NULL;
	}

	/* Normalize clock rate to 24MHz standard system clock */
	sys_clk = clk_am335x_rate_get(CLK_AM335X_SYS_CLK, 1);
	switch ((int) sys_clk) {
	case 19:
		mult = 1.25;
		break;
	case 24:
		mult = 1.0;
		break;
	case 25:
		mult = 0.96;
		break;
	case 26:
		mult = 0.923077;
		break;
	default:
		mult = 0.0;
	}


	/*
	 * If the DPLL clocking the selected module is stopped,
	 * reported speed will be 0 and OPP cannot be detected.
	 * Hence, ignore DPLL status.
	 */
	rate = (double) module_clk_rate_get(module_name, 1) / 1000.0 * mult;
	if (rate < 0.0) {
		dprintf("%s(): could not retrieve clock speed!\n", __func__);
		goto opp_am335x_by_rate_get_end;
	}
	dprintf("%s(%s): %s rate is %lfMHz\n", __func__,
		voltdm_am335x_name_get(vdd_id),
		clk_am335x_name_get(module_clk_get(module_name)), rate);

	opp_list = opp_am335x_list_get(vdd_id);
	if (opp_list == NULL) {
		dprintf("%s(): could not retrieve OPP list!\n", __func__);
		goto opp_am335x_by_rate_get_end;
	}

	opp_count = opp_am335x_count_get(vdd_id);
	if (opp_count <= 0) {
		dprintf("%s(): could not retrieve OPP count!\n", __func__);
		goto opp_am335x_by_rate_get_end;
	}


	for (i = 0; i < opp_count; i++) {
		ret = genlist_get((genlist *) opp_list, i, (opp_t *) &opp);
		if (ret != 0) {
			dprintf("%s(): could not retrieve OPP from list!\n",
				__func__);
			goto opp_am335x_by_rate_get_end;
		}

		opp_id = opp_am335x_id_get(opp.name);
		if (opp_id < 0) {
			dprintf(
				"%s(): could not retrieve OPP ID from OPP name!\n",
				__func__);
			goto opp_am335x_by_rate_get_end;
		}

		rate_por = (double) module_por_clk_rate_get(module_name, opp.name)
				/ 1000.0;
		if (rate_por < 0) {
			dprintf(
				"%s(): could not get %s %s POR speed! (%d)\n",
				__func__, module_name,
				opp.name, ret);
			goto opp_am335x_by_rate_get_end;
		}
		dprintf("%s(%s): %s POR rate for %s is %lf\n",
			__func__, voltdm_am335x_name_get(vdd_id),
		module_name, opp.name, rate_por);
		if ((int) rate == (int) rate_por) {
			/*
			 * The only way to distinguish between OPP50 and
			 * OPP100 (300MHz) is to look at the voltage range
			 * (OPP50 is between .912V and .988V)
			 */
			if (opp_am335x_id_get(opp.name) == OPP_AM335X_050)
				if ((int) voltdm_am335x_voltage_get(vdd_id) == 1)
					continue;
			opp_name = opp.name;
			goto opp_am335x_by_rate_get_end;
		}
	}

	dprintf("%s(%s): OPP not found!\n",
		__func__, voltdm_am335x_name_get(vdd_id));

opp_am335x_by_rate_get_end:
#ifdef OPP_AM335X_DEBUG
	if (opp_name == NULL)
		printf("%s(%s): OPP not found!\n", __func__,
			voltdm_am335x_name_get(vdd_id));
	else
		printf("%s(%s): OPP found: %s\n", __func__,
			voltdm_am335x_name_get(vdd_id), opp_name);
#endif
	return opp_name;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp_am335x_get
 * @BRIEF		return the current voltage domain OPP name.
 * @RETURNS		current voltage domain OPP name (as defined in opp.h)
 *			NULL pointer in case of error or not found
 * @param[in]		vdd_id: voltage domain ID
 * @DESCRIPTION		return the current voltage domain OPP name. Search it by
 *			voltage first, then if failed search it by rates.
 *//*------------------------------------------------------------------------ */
const char *opp_am335x_get(voltdm_am335x_id vdd_id)
{
	CHECK_ARG_LESS_THAN(vdd_id, VDD_AM335X_ID_MAX, NULL);

	opp_am335x_init();

	return opp_get(voltdm_am335x_id2s(vdd_id), 1);
}
