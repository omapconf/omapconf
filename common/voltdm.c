/*
 *
 * @Component			OMAPCONF
 * @Filename			voltdm.c
 * @Description			Generic Voltage Domain Definitions & APIs
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
#include <voltdm.h>
#include <voltdm44xx.h>
#include <smartreflex44xx.h>
#include <voltdm54xx.h>
#include <cpuinfo.h>
#include <opp.h>


/* #define VOLTDM_DEBUG */
#ifdef VOLTDM_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


genlist voltdm_list;
static unsigned short voltdm_init_done = 0;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void voltdm_init(void)
{
	if (!voltdm_init_done) {
		if (cpu_is_omap44xx()) {
			genlist_init(&voltdm_list);
			genlist_addtail(&voltdm_list,
				(void *) VDD_WKUP,
				(1 + strlen(VDD_WKUP)) * sizeof(char));
			genlist_addtail(&voltdm_list,
				(void *) VDD_MPU,
				(1 + strlen(VDD_MPU)) * sizeof(char));
			genlist_addtail(&voltdm_list,
				(void *) VDD_IVA,
				(1 + strlen(VDD_IVA)) * sizeof(char));
			genlist_addtail(&voltdm_list,
				(void *) VDD_CORE,
				(1 + strlen(VDD_CORE)) * sizeof(char));
		} else if (cpu_is_omap54xx()) {
			genlist_init(&voltdm_list);
			genlist_addtail(&voltdm_list,
				(void *) VDD_WKUP,
				(1 + strlen(VDD_WKUP)) * sizeof(char));
			genlist_addtail(&voltdm_list,
				(void *) VDD_MPU,
				(1 + strlen(VDD_MPU)) * sizeof(char));
			genlist_addtail(&voltdm_list,
				(void *) VDD_MM,
				(1 + strlen(VDD_MM)) * sizeof(char));
			genlist_addtail(&voltdm_list,
				(void *) VDD_CORE,
				(1 + strlen(VDD_CORE)) * sizeof(char));
		} else {
			fprintf(stderr,
				"omapconf: %s(): cpu not supported!!!\n",
				__func__);
		}

		voltdm_init_done = 1;
		dprintf("%s(): init done.\n", __func__);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm_deinit
 * @BRIEF		free dynamically allocated internal data.
 * @DESCRIPTION		free dynamically allocated internal data.
 *			MUST BE CALLED AT END OF EXECUTION.
 *//*------------------------------------------------------------------------ */
void voltdm_deinit(void)
{
	if (voltdm_init_done) {
		genlist_free(&voltdm_list);
		genlist_free(&voltdm_list);
		genlist_free(&voltdm_list);
		genlist_free(&voltdm_list);
	}
	dprintf("%s(): deinit done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm_list_get
 * @BRIEF		return the list of voltage domain(s)
 * @RETURNS		list of voltage domain(s) in case of success
 *			NULL if not available
 * @DESCRIPTION		return the number of voltage domain(s)
 *//*------------------------------------------------------------------------ */
const genlist *voltdm_list_get(void)
{
	voltdm_init();

	if (cpu_is_omap44xx() || cpu_is_omap54xx()) {
		return (const genlist *) &voltdm_list;
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		return NULL;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm_s2id
 * @BRIEF		convert voltage domain provided as a string
 *			(as defined in voltdm.h) into a plaftorm-specific
 *			voltage domain ID (integer).
 * @RETURNS		plaftorm-specific voltage domain ID (> 0) if success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		voltdm: voltage domain name (as defined in voltdm.h)
 * @DESCRIPTION		convert voltage domain provided as a string
 *			(as defined in voltdm.h) into a plaftorm-specific
 *			voltage domain ID (integer).
 *//*------------------------------------------------------------------------ */
int voltdm_s2id(const char *voltdm)
{
	CHECK_NULL_ARG(voltdm, OMAPCONF_ERR_ARG);

	if (cpu_is_omap44xx()) {
		if (strcmp(voltdm, VDD_WKUP) == 0)
			return (int) OMAP4_LDO_WKUP;
		else if (strcmp(voltdm, VDD_MPU) == 0)
			return (int) OMAP4_VDD_MPU;
		else if (strcmp(voltdm, VDD_IVA) == 0)
			return (int) OMAP4_VDD_IVA;
		else if (strcmp(voltdm, VDD_CORE) == 0)
			return (int) OMAP4_VDD_CORE;
		else
			return OMAPCONF_ERR_ARG;
	} else if (cpu_is_omap54xx()) {
		if (strcmp(voltdm, VDD_WKUP) == 0)
			return (int) VDD54XX_WKUP;
		else if (strcmp(voltdm, VDD_MPU) == 0)
			return (int) VDD54XX_MPU;
		else if (strcmp(voltdm, VDD_MM) == 0)
			return (int) VDD54XX_MM;
		else if (strcmp(voltdm, VDD_CORE) == 0)
			return (int) VDD54XX_CORE;
		else
			return OMAPCONF_ERR_ARG;
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		return OMAPCONF_ERR_CPU;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm_count_get
 * @BRIEF		return the number of voltage domain(s)
 * @RETURNS		number of voltage domain(s) (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		return the number of voltage domain(s)
 *//*------------------------------------------------------------------------ */
int voltdm_count_get(void)
{
	if (cpu_is_omap44xx()) {
		return (int) OMAP4_VD_ID_MAX;
	} else if (cpu_is_omap54xx()) {
		return (int) VDD54XX_ID_MAX;
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		return OMAPCONF_ERR_CPU;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm_voltage_get
 * @BRIEF		return the current voltage supplied to a voltage domain.
 * @RETURNS		supplied voltage in micro-volt (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		voltdm: voltage domain name (as defined in voltdm.h)
 * @DESCRIPTION		return the current voltage supplied to a voltage domain.
 *//*------------------------------------------------------------------------ */
int voltdm_voltage_get(const char *voltdm)
{
	int id, ret;
	double volt;

	CHECK_NULL_ARG(voltdm, OMAPCONF_ERR_ARG);

	voltdm_init();

	id = voltdm_s2id(voltdm);
	if (id < 0)
		return (double) OMAPCONF_ERR_ARG;

	if (cpu_is_omap44xx()) {
		ret = voltdm44xx_get_voltage((voltdm44xx_id) id, &volt);
		if (ret < 0)
			return (double) ret;
		else
			return v2uv(volt);
	} else if (cpu_is_omap54xx()) {
		return v2uv(voltdm54xx_voltage_get((voltdm54xx_id) id));
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		return (double) OMAPCONF_ERR_CPU;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm_voltage_set
 * @BRIEF		set the voltage supplied to a voltage domain.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_UNEXPECTED
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		voltdm: voltage domain name (as defined in voltdm.h)
 * @param[in]		uv: new voltage to be set (in micro-volt)
 * @DESCRIPTION		return the current voltage supplied to a voltage domain.
 *//*------------------------------------------------------------------------ */
int voltdm_voltage_set(const char *voltdm, int uv)
{
	int id;

	CHECK_NULL_ARG(voltdm, OMAPCONF_ERR_ARG);

	voltdm_init();

	id = voltdm_s2id(voltdm);
	if (id < 0)
		return (double) OMAPCONF_ERR_ARG;

	if (cpu_is_omap44xx()) {
		return sr44xx_voltage_set(
			(unsigned int) id, (unsigned long) uv);
	} else if (cpu_is_omap54xx()) {
		return voltdm54xx_voltage_set(
			(voltdm54xx_id) id, (unsigned long) uv);
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		return OMAPCONF_ERR_CPU;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm_nominal_voltage_get
 * @BRIEF		return the nominal voltage supplied to a voltage domain.
 * @RETURNS		nominal voltage in micro-volt (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		voltdm: voltage domain name (as defined in voltdm.h)
 * @DESCRIPTION		return the nominal voltage supplied to a voltage domain.
 *			In case SmartReflex AVS Class3 is enabled,
 *			it may differ from the current supplied voltage.
 *//*------------------------------------------------------------------------ */
int voltdm_nominal_voltage_get(const char *voltdm)
{
	int id;
	int uvolt;

	CHECK_NULL_ARG(voltdm, OMAPCONF_ERR_ARG);

	voltdm_init();

	id = voltdm_s2id(voltdm);
	if (id < 0) {
		uvolt = OMAPCONF_ERR_ARG;
	} else if (cpu_is_omap44xx()) {
		uvolt = v2uv(voltdm44xx_nominal_voltage_get(
			(voltdm44xx_id) id));
	} else if (cpu_is_omap54xx()) {
		uvolt = v2uv(voltdm54xx_nominal_voltage_get(
			(voltdm54xx_id) id));
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		uvolt = OMAPCONF_ERR_CPU;
	}

	dprintf("%s(%s) = %duV\n", __func__, voltdm, uvolt);
	return uvolt;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm_por_nominal_voltage_get
 * @BRIEF		return the nominal voltage to be supplied to a
 *			voltage domain, as defined in Data Manual.
 * @RETURNS		nominal voltage in micro-volt (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		voltdm: voltage domain name (as defined in voltdm.h)
 * @param[in]		opp: OPP provided as a string (as defined in opp.h)
 * @DESCRIPTION		return the nominal voltage to be supplied to a
 *			voltage domain, as defined in Data Manual.
 *			Not read from the platform, but from internal tables.
 *//*------------------------------------------------------------------------ */
int voltdm_por_nominal_voltage_get(const char *voltdm, const char *opp)
{
	int vdd_id, opp_id;

	CHECK_NULL_ARG(voltdm, OMAPCONF_ERR_ARG);

	voltdm_init();

	vdd_id = voltdm_s2id(voltdm);
	if (vdd_id < 0)
		return OMAPCONF_ERR_ARG;

	opp_id = opp_s2id(opp);
	if (opp_id < 0)
		return opp_id;

	if (cpu_is_omap44xx()) {
		return v2uv(voltdm44xx_por_nominal_voltage_get(
			(voltdm44xx_id) vdd_id, (opp44xx_id) opp_id));
	} else if (cpu_is_omap54xx()) {
		return v2uv(voltdm54xx_por_nominal_voltage_get(
			(voltdm54xx_id) vdd_id, (opp54xx_id) opp_id));
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		return OMAPCONF_ERR_CPU;
	}
}
