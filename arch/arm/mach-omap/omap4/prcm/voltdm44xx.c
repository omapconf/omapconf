/*
 *
 * @Component			OMAPCONF
 * @Filename			voltdm44xx.c
 * @Description			OMAP4 Voltage Domain Definitions & Functions
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


#include <voltdomain.h>
#include <voltdm44xx.h>
#include <vc44xx.h>
#include <prm44xx.h>
#include <string.h>
#include <unistd.h>
#include <cpuinfo.h>
#include <lib.h>
#include <mem.h>
#include <clock44xx.h>
#include <module44xx.h>
#include <pmic.h>
#include <dpll44xx.h>
#include <smartreflex44xx.h>
#include <temperature.h>
#include <temperature44xx.h>
#include <autoadjust_table.h>
#include <cpufreq.h>
#include <opp.h>


/* #define VOLTDM44XX_DEBUG */
#ifdef VOLTDM44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


#define OPP_MAX_RETRY		100


const char
	voltdm44xx_name_table[OMAP4_VD_ID_MAX][VOLTDM44XX_MAX_NAME_LENGTH] = {
	"LDO_WKUP",
	"VDD_MPU",
	"VDD_IVA",
	"VDD_CORE"};


const char
	core_opp4470_name_table[OPP44XX_ID_MAX + 1][OPP44XX_MAX_NAME_LENGTH] = {
	"DPLL_CASC",
	"OPP50_LOW",
	"OPP50_HIGH",
	"OPP100_LOW",
	"OPP119_LOW",
	"OPP119_HIGH",
	"OPP100_HIGH",
	"UNKNOWN"};


const char
	opp44xx_name_table[OPP44XX_ID_MAX + 1][OPP44XX_MAX_NAME_LENGTH] = {
	"DPLL_CASC",
	"OPP50",
	"OPP100",
	"OPP_TURBO",
	"OPP_NITRO",
	"OPP_NITRO_SB",
	"OPP119",
	"UNKNOWN"};


static const double omap4430_retention_voltage_table[OMAP4_VD_ID_MAX] = {
	0.0, 0.759640, 0.759640, 0.759640};


static const double
	omap4430_nominal_voltage_table[OMAP4_VD_ID_MAX][OPP44XX_ID_MAX] = {
	{1.06, 1.06, 1.06, 1.06, 1.06, 1.06, 1.06}, /* LDO_WKUP */
	{1.0255, 1.0255, 1.2027, 1.3293, 1.3926, 1.3926, -1.0}, /* VDD_MPU */
	{0.9622, 0.9622, 1.114, 1.291, -1.0, -1.0, -1.0}, /* VDD_IVA */
	{0.9622, 0.9622, 1.127, -1.0, -1.0, -1.0, -1.0} }; /* VDD_CORE */


static const double omap4460_retention_voltage_table[OMAP4_VD_ID_MAX] = {
	0.0, 0.75, 0.759640, 0.759640};


static const double
	omap4460_nominal_voltage_table[OMAP4_VD_ID_MAX][OPP44XX_ID_MAX] = {
	{1.06, 1.06, 1.06, 1.06, 1.06, 1.06, 1.06}, /* LDO_WKUP */
	{1.025, 1.025, 1.203, 1.317, 1.380, 1.380, -1.0}, /* VDD_MPU */
	{0.9622, 0.9622, 1.114, 1.291, 1.380, 1.380, -1.0}, /* VDD_IVA */
	{0.9622, 0.9622, 1.127, 1.2534, -1.0, -1.0} }; /* VDD_CORE */


static const double omap4470_retention_voltage_table[OMAP4_VD_ID_MAX] = {
	0.0, 0.759640, 0.759640, 0.759640};


static const double
	omap4470_nominal_voltage_table[OMAP4_VD_ID_MAX][OPP44XX_ID_MAX] = {
	{1.06, 1.06, 1.06, 1.06, 1.06, 1.06, 1.06}, /* LDO_WKUP */
	{1.0255, 1.0255, 1.2027, 1.3167, 1.380, 1.380, -1.0}, /* VDD_MPU */
	{0.9622, 0.9622, 1.1394, 1.2914, 1.380, 1.380, -1.0}, /* VDD_IVA */
	{0.9622, 0.9622, 0.9622, 1.1255, 1.2534, 1.253, 1.1274} }; /* VDD_CORE */


static unsigned short voltdm44xx_init_done = 0;
genlist voltdm44xx_list;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm44xx_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void voltdm44xx_init(void)
{
	voltdm_info voltdm;

	if (voltdm44xx_init_done)
		return;

	genlist_init(&voltdm44xx_list);

	voltdm.name = VDD_WKUP;
	voltdm.id = (int) OMAP4_LDO_WKUP;
	voltdm.voltst = NULL; /* Not present on OMAP4 */
	genlist_addtail(
		&voltdm44xx_list, (void *) &voltdm, sizeof(voltdm_info));

	voltdm.name = VDD_MPU;
	voltdm.id = (int) OMAP4_VDD_MPU;
	voltdm.voltst = NULL; /* Not present on OMAP4 */
	genlist_addtail(
		&voltdm44xx_list, (void *) &voltdm, sizeof(voltdm_info));

	voltdm.name = VDD_IVA;
	voltdm.id = (int) OMAP4_VDD_IVA;
	voltdm.voltst = NULL; /* Not present on OMAP4 */
	genlist_addtail(
		&voltdm44xx_list, (void *) &voltdm, sizeof(voltdm_info));

	voltdm.name = VDD_CORE;
	voltdm.id = (int) OMAP4_VDD_CORE;
	voltdm.voltst = NULL; /* Not present on OMAP4 */
	genlist_addtail(
		&voltdm44xx_list, (void *) &voltdm, sizeof(voltdm_info));

	voltdm44xx_init_done = 1;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm44xx_deinit
 * @BRIEF		free dynamically allocated internal data.
 * @DESCRIPTION		free dynamically allocated internal data.
 *			MUST BE CALLED AT END OF EXECUTION.
 *//*------------------------------------------------------------------------ */
void voltdm44xx_deinit(void)
{
	if (voltdm44xx_init_done) {
		genlist_free(&voltdm44xx_list);
		voltdm44xx_init_done = 0;

	}
	dprintf("%s(): deinit done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm44xx_list_get
 * @BRIEF		return the list of voltage domains
 * @RETURNS		list of voltage domains in case of success
 *			NULL in case of error
 * @DESCRIPTION		return the list of voltage domains
 *//*------------------------------------------------------------------------ */
const genlist *voltdm44xx_list_get(void)
{
	voltdm44xx_init();

	return (const genlist *) &voltdm44xx_list;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm44xx_count_get
 * @BRIEF		return the number of voltage domains
 * @RETURNS		number of voltage domains (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @DESCRIPTION		return the number of voltage domains
 *//*------------------------------------------------------------------------ */
int voltdm44xx_count_get(void)
{
	int count;

	voltdm44xx_init();

	count = genlist_getcount(&voltdm44xx_list);

	dprintf("%s() = %d\n", __func__, count);
	return count;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm44xx_get_name
 * @BRIEF		return voltage domain name
 * @RETURNS		voltage domain name on success
 *			NULL in case of error
 * @param[in]		id: voltage domain ID
 * @param[in,out]	name: voltage domain name
 * @DESCRIPTION		return voltage domain name
 *//*------------------------------------------------------------------------ */
char *voltdm44xx_get_name(voltdm44xx_id id,
	char name[VOLTDM44XX_MAX_NAME_LENGTH])
{
	if ((id >= OMAP4_VD_ID_MAX) || (name == NULL))
		return NULL;
	else
		strcpy(name, voltdm44xx_name_table[id]);

	return name;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm44xx_s2id
 * @BRIEF		convert string to valid voltage domain ID.
 * @RETURNS		valid voltage domain ID in case of success
 *			OMAP4_VD_ID_MAX otherwise
 * @param[in]		s: string
 * @DESCRIPTION		convert string to valid voltage domain ID.
 *//*------------------------------------------------------------------------ */
voltdm44xx_id voltdm44xx_s2id(char *s)
{
	voltdm44xx_id vdd_id;
	#ifdef VOLTDM44XX_DEBUG
	char voltdm_name[VOLTDM44XX_MAX_NAME_LENGTH];
	#endif

	CHECK_NULL_ARG(s, OMAP4_VD_ID_MAX);

	if (strcmp(s, "mpu") == 0)
		vdd_id = OMAP4_VDD_MPU;
	else if (strcmp(s, "iva") == 0)
		vdd_id = OMAP4_VDD_IVA;
	else if (strcmp(s, "core") == 0)
		vdd_id = OMAP4_VDD_CORE;
	else
		vdd_id = OMAP4_VD_ID_MAX;

	dprintf("%s(%s) = %d (%s)\n", __func__, s,
		vdd_id, voltdm44xx_get_name(vdd_id, voltdm_name));
	return vdd_id;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm44xx_retention_voltage_get
 * @BRIEF		return voltage domain retention voltage, in volt.
 * @RETURNS		voltage domain retention voltage on success (> 0)
 *			<= 0 in case of error
 * @param[in]		id: voltage domain ID
 * @DESCRIPTION		return voltage domain retention voltage, in volt.
 *//*------------------------------------------------------------------------ */
double voltdm44xx_retention_voltage_get(voltdm44xx_id id)
{
	int ret;
	double volt;
	vc44xx_registers vc_regs;
	unsigned char cmd_on, cmd_onlp, cmd_ret, cmd_off;
	#ifdef VOLTDM44XX_DEBUG
	char vname[VOLTDM44XX_MAX_NAME_LENGTH];
	#endif

	CHECK_CPU(44xx, (double) OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(id, OMAP4_VD_ID_MAX, (double) OMAPCONF_ERR_ARG);

	/* Retrieve VC registers */
	ret = vc44xx_registers_get(&vc_regs);
	if (ret != 0)
		return (double) ret;

	/* Retrieve RET command value */
	ret = vc44xx_cmd_values_get(id, &vc_regs,
			&cmd_on, &cmd_onlp, &cmd_ret, &cmd_off);
	if (ret != 0)
		return (double) ret;

	/* Convert RET command value to voltage */
	volt = smps_vsel2volt(vdd_id2smps_id(id), cmd_ret);

	dprintf("%s(%s): retention voltage = %lfV\n", __func__,
		voltdm44xx_get_name(id, vname), volt);

	return volt;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm44xx_por_retention_voltage_get
 * @BRIEF		return voltage domain retention voltage, as defined in
 *			Data Manual.
 * @RETURNS		domain retention voltage on success (> 0, in volt)
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		id: voltage domain ID
 * @DESCRIPTION		return voltage domain retention voltage, as defined in
 *			Data Manual.
 *//*------------------------------------------------------------------------ */
double voltdm44xx_por_retention_voltage_get(voltdm44xx_id id)
{
	double volt;
	#ifdef VOLTDM44XX_DEBUG
	char vname[VOLTDM44XX_MAX_NAME_LENGTH];
	#endif

	CHECK_CPU(44xx, (double) OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(id, OMAP4_VD_ID_MAX, (double) OMAPCONF_ERR_ARG);

	switch (cpu_get()) {
	case OMAP_4430:
		volt = omap4430_retention_voltage_table[id];
		break;
	case OMAP_4460:
		volt = omap4460_retention_voltage_table[id];
		break;
	case OMAP_4470:
		volt = omap4470_retention_voltage_table[id];
		break;
	default:
		return OMAPCONF_ERR_CPU;
	}

	dprintf("%s(%s): retention voltage = %lfV\n", __func__,
		voltdm44xx_get_name(id, vname), volt);

	return volt;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm44xx_nominal_voltage_get
 * @BRIEF		return voltage domain nominal voltage
 * @RETURNS		voltage domain nominal voltage on success (> 0)
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		id: voltage domain ID
 * @DESCRIPTION		return voltage domain nominal voltage
 *//*------------------------------------------------------------------------ */
double voltdm44xx_nominal_voltage_get(voltdm44xx_id id)
{
	int ret;
	double volt;
	vc44xx_registers vc_regs;
	unsigned char cmd_on, cmd_onlp, cmd_ret, cmd_off;
	#ifdef VOLTDM44XX_DEBUG
	char vname[VOLTDM44XX_MAX_NAME_LENGTH];
	#endif

	CHECK_CPU(44xx, (double) OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(id, OMAP4_VD_ID_MAX, (double) OMAPCONF_ERR_ARG);

	/* Retrieve VC registers */
	ret = vc44xx_registers_get(&vc_regs);
	if (ret != 0)
		return (double) ret;

	/* Retrieve ON command value */
	ret = vc44xx_cmd_values_get(id, &vc_regs,
			&cmd_on, &cmd_onlp, &cmd_ret, &cmd_off);
	if (ret != 0)
		return (double) ret;

	/* Convert ON command value to voltage */
	volt = smps_vsel2volt(vdd_id2smps_id(id), cmd_on);

	dprintf("%s(%s): ON voltage = %lfV\n", __func__,
		voltdm44xx_get_name(id, vname), volt);

	return volt;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm44xx_por_nominal_voltage_get
 * @BRIEF		return voltage domain nominal voltage, as defined in
 *			Data Manual.
 * @RETURNS		domain nominal voltage on success (> 0, in volt)
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		id: voltage domain ID
 * @param[in]		opp: opp id
 * @DESCRIPTION		return voltage domain nominal voltage, as defined in
 *			Data Manual.
 *//*------------------------------------------------------------------------ */
double voltdm44xx_por_nominal_voltage_get(voltdm44xx_id id, opp44xx_id opp)
{
	double volt;
	#ifdef VOLTDM44XX_DEBUG
	char vname[VOLTDM44XX_MAX_NAME_LENGTH];
	char oname[OPP44XX_MAX_NAME_LENGTH];
	#endif

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(id, OMAP4_VD_ID_MAX, (double) OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(opp, OPP44XX_ID_MAX, (double) OMAPCONF_ERR_ARG);

	#ifdef VOLTDM44XX_DEBUG
	voltdm44xx_opp2string(oname, opp, id);
	#endif

	switch (cpu_get()) {
	case OMAP_4430:
		volt = omap4430_nominal_voltage_table[id][opp];
		break;
	case OMAP_4460:
		volt = omap4460_nominal_voltage_table[id][opp];
		break;
	case OMAP_4470:
		volt = omap4470_nominal_voltage_table[id][opp];
		break;
	default:
		return OMAPCONF_ERR_CPU;
	}

	dprintf("%s(%s, %s): nominal voltage = %lfV\n", __func__,
		voltdm44xx_get_name(id, vname), oname, volt);

	return volt;
}


/* #define OMAP4CONF_GET_OPP_DEBUG */
#ifndef VOLTDM44XX_DEBUG
#ifdef OMAP4CONF_GET_OPP_DEBUG
#undef dprintf
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#endif
#else
#undef dprintf
#define dprintf(format, ...)
#endif
/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm44xx_get_opp
 * @BRIEF		find the current voltage domain OPP
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		id: voltage domain ID
 * @param[in,out]	opp: pointer to return OPP
 * @DESCRIPTION		find the current voltage domain OPP
 *//*------------------------------------------------------------------------ */
int voltdm44xx_get_opp(voltdm44xx_id id, opp44xx_id *opp)
{
	int ret;
	clock44xx_id clk_id;
	mod44xx_id module_id;
	unsigned int opp_id;
	double speed_curr = 0.0, speed_por = 0.0;
	double gfx_speed_curr = 0.0, gfx_speed_por = 0.0;
	double dss_speed_curr = 0.0, dss_speed_por = 0.0;
	omap4_dpll_params dpll_params;
	dpll44xx_id dpll_id;
	#ifdef OMAP4CONF_GET_OPP_DEBUG
	char mname[MOD44XX_MAX_NAME_LENGTH];
	char cname[CLOCK44XX_MAX_NAME_LENGTH];
	char vname[VOLTDM44XX_MAX_NAME_LENGTH];
	char s_opp[OPP44XX_MAX_NAME_LENGTH] = "ERR";
	#endif

	*opp = OPP44XX_ID_MAX;
	if (!cpu_is_omap44xx())
		return OMAPCONF_ERR_CPU;
	if (opp == NULL)
		return OMAPCONF_ERR_ARG;

	/*
	 * Determine current OPPs
	 * by getting MPU, IVAHD, L3 and SARRAM speeds
	 * and comparing it to POR speeds.
	 */
	switch (id) {
	case OMAP4_LDO_WKUP:
		clk_id = OMAP4_L4_ICLK2;
		module_id = OMAP4_SARRAM;
		dpll_id = DPLL44XX_CORE;
		break;
	case OMAP4_VDD_MPU:
		clk_id = OMAP4_MPU_DPLL_CLK;
		module_id = OMAP4_MPU;
		dpll_id = DPLL44XX_MPU;
		break;
	case OMAP4_VDD_IVA:
		clk_id = OMAP4_IVAHD_ROOT_CLK;
		module_id = OMAP4_IVAHD;
		dpll_id = DPLL44XX_IVA;
		break;
	case OMAP4_VDD_CORE:
		clk_id = OMAP4_L3_ICLK;
		module_id = OMAP4_L3_1;
		dpll_id = DPLL44XX_CORE;
		break;
	default:
		return OMAPCONF_ERR_ARG;
	}
	dprintf("%s(): Looking for %s OPP ...\n", __func__,
		voltdm44xx_name_table[id]);

	/* if the DPLL clocking the selected module is stopped,
	 * reported speed will be 0 and OPP cannot be detected.
	 * Hence, if DPLL is stopped, ignore DPLL status to get
	 * the speed when the DPLL is running.
	 */
	dpll44xx_dpll_params_get(dpll_id, &dpll_params, 0);
	if ((dpll_params.status == DPLL_STATUS_STOPPED) ||
		(dpll_id == DPLL44XX_IVA))
		speed_curr = clk44xx_get_clock_speed(clk_id, 1);
	else
		speed_curr = clk44xx_get_clock_speed(clk_id, 0);
	if (speed_curr < 0)
		return OMAPCONF_ERR_NOT_AVAILABLE;

	dprintf("%s(): %s speed is %lfMHz\n", __func__,
		clk44xx_get_name(clk_id, cname), speed_curr);
	for (opp_id = 0; opp_id < OPP44XX_ID_MAX; opp_id++) {
		#ifdef OMAP4CONF_GET_OPP_DEBUG
		voltdm44xx_opp2string(s_opp, opp_id, id);
		#endif

		/* Retrieve module expected speed for this tentative OPP */
		ret = mod44xx_get_por_clk_speed(module_id, opp_id, &speed_por);
		if (ret != 0) {
			dprintf("%s(): could not get %s %s POR speed! (%d)\n",
				__func__,
				mod44xx_get_name(module_id, mname), s_opp, ret);
			return ret;
		}
		dprintf("%s(): %s POR Speed for %s is %lf\n", __func__,
			mod44xx_get_name(module_id, mname), s_opp, speed_por);

		if (cpu_is_omap4460() && (id == OMAP4_VDD_IVA) &&
			((int) speed_curr == 124)) {
			/*
			 * Hack for Galaxy Nexus, observed with pastry
			 * Jelly Bean 4.2.1 (may/may not apply to other pastry)
			 */
			*opp = OMAP4_OPP50;
			dprintf("%s(): %s OPP found: %s\n", __func__,
				voltdm44xx_get_name(id, vname), s_opp);
			return 0;
		}
		if ((int) speed_por != (int) speed_curr)
			continue;

		if (cpu_is_omap4470() && (id == OMAP4_VDD_CORE) && \
			(opp_id == OMAP447X_OPP100_LOW)) {
			/* for opp_id == OMAP447X_OPP100_LOW
			 * and opp_id == OMAP447X_OPP119_LOW
			 * L3 clock frequencies are equal.
			 * Use GFX clock frequencies to distinguish.
			 */
			ret = mod44xx_get_por_clk_speed(OMAP4_GFX,
					OMAP447X_OPP119_LOW, &gfx_speed_por);
			if (ret != 0) {
				dprintf("%s(): could not get %s %s POR "
					"speed! (%d)\n", __func__,
					mod44xx_get_name(OMAP4_GFX, mname),
					"OPP119_LOW", ret);
				return ret;
			}
			dprintf("%s(): %s POR Speed for OPP119_LOW is %lfMHz\n",
				__func__, clk44xx_get_name(
					OMAP4_GFX_FCLK, cname),
				gfx_speed_por);

			gfx_speed_curr =
				clk44xx_get_clock_speed(OMAP4_GFX_FCLK, 1);
			dprintf("%s(): %s speed is %lfMHz\n", __func__,
				clk44xx_get_name(OMAP4_GFX_FCLK, cname),
				gfx_speed_curr);

			if ((int) gfx_speed_curr == (int) gfx_speed_por) {
				opp_id = OMAP447X_OPP119_LOW;
				#ifdef OMAP4CONF_GET_OPP_DEBUG
				voltdm44xx_opp2string(s_opp, opp_id, id);
				#endif
				dprintf("%s(): GFX POR Speed == OPP119_LOW "
					"POR Speed\n", __func__);
			} else {
				dprintf("%s(): GFX POR Speed != OPP119_LOW "
					"POR Speed\n", __func__);
				continue;
			}
		} else if (cpu_is_omap4470() && (id == OMAP4_VDD_CORE) && \
			(opp_id == OMAP447X_OPP50_HIGH)) {
			/* for opp_id == OMAP447X_OPP50_HIGH
			 * and opp_id == OMAP447X_OPP100_HIGH
			 * L3 clock frequencies are equal.
			 * Use DSS clock frequencies to distinguish.
			 */
			ret = mod44xx_get_por_clk_speed(OMAP4_DISPC,
					OMAP447X_OPP50_HIGH, &dss_speed_por);
			if (ret != 0) {
				dprintf("%s(): could not get %s %s POR "
					"speed! (%d)\n", __func__,
					mod44xx_get_name(OMAP4_DISPC, mname),
					"OPP50_HIGH", ret);
				return ret;
			}
			dprintf("%s(): %s POR Speed for OMAP447X_OPP50_HIGH is %lfMHz\n",
				__func__, clk44xx_get_name(
					OMAP4_DSS_FCLK, cname),
				dss_speed_por);

			dss_speed_curr =
				clk44xx_get_clock_speed(OMAP4_DSS_FCLK, 1);
			dprintf("%s(): %s speed is %lfMHz\n", __func__,
				clk44xx_get_name(OMAP4_DSS_FCLK, cname),
				dss_speed_curr);

			if ((int) dss_speed_curr == (int) dss_speed_por) {
				opp_id = OMAP447X_OPP50_HIGH;
				#ifdef OMAP4CONF_GET_OPP_DEBUG
				voltdm44xx_opp2string(s_opp, opp_id, id);
				#endif
				dprintf("%s(): DSS POR Speed == OPP50_HIGH "
					"POR Speed\n", __func__);
			} else {
				dprintf("%s(): DSS POR Speed != OPP50_HIGH "
					"POR Speed\n", __func__);
				continue;
			}
		}

		dprintf("%s(): %s OPP found: %s\n", __func__,
			voltdm44xx_get_name(id, vname), s_opp);
		*opp = (opp44xx_id) opp_id;
		return 0;
	}
	dprintf("%s(): %s OPP not found!!!\n", __func__,
		voltdm44xx_get_name(id, vname));

	return OMAPCONF_ERR_NOT_AVAILABLE;
}
#ifndef VOLTDM44XX_DEBUG
#ifdef OMAP4CONF_GET_OPP_DEBUG
#undef dprintf
#define dprintf(format, ...)
#endif
#else
#undef dprintf
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp44xx_name_get
 * @BRIEF		return OPP name.
 * @RETURNS		OPP name on success
 *			"UNKNOWN" string in case of error
 * @param[in]		opp_id: OPP ID
 * @param[in]		vdd_id: VDD ID
 * @DESCRIPTION		return DPLL name.
 *//*------------------------------------------------------------------------ */
const char *opp44xx_name_get(unsigned short opp_id, voltdm44xx_id vdd_id)
{
	if (cpu_is_omap4470() &&
		((vdd_id == OMAP4_VDD_CORE) || (vdd_id == OMAP4_LDO_WKUP))) {
		if (opp_id < OPP44XX_ID_MAX)
			return core_opp4470_name_table[opp_id];
		else
			return core_opp4470_name_table[OPP44XX_ID_MAX];
	} else {
		if (opp_id < OPP44XX_ID_MAX)
			return opp44xx_name_table[opp_id];
		else
			return opp44xx_name_table[OPP44XX_ID_MAX];
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm44xx_opp2string
 * @BRIEF		convert OPP ID into string
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in, out]	s: destination string (pre-allocated)
 * @param[in]		opp: OPP ID
 * @param[in]		vd_id: VDD ID
 * @DESCRIPTION		convert OPP ID into string
 *//*------------------------------------------------------------------------ */
int voltdm44xx_opp2string(char s[OPP44XX_MAX_NAME_LENGTH],
	unsigned short opp, voltdm44xx_id vd_id)
{
	if ((void *) s == NULL)
		return OMAPCONF_ERR_ARG;

	if (cpu_is_omap4470() &&
		((vd_id == OMAP4_VDD_CORE) || (vd_id == OMAP4_LDO_WKUP))) {
		switch (opp) {
		case OMAP447X_OPPDPLL_CASC:
			strcpy(s, "DPLL_CASC");
			break;
		case OMAP447X_OPP50_LOW:
			strcpy(s, "OPP50_LOW");
			break;
		case OMAP447X_OPP50_HIGH:
			strcpy(s, "OPP50_HIGH");
			break;
		case OMAP447X_OPP100_LOW:
			strcpy(s, "OPP100_LOW");
			break;
		case OMAP447X_OPP100_HIGH:
			strcpy(s, "OPP100_HIGH");
			break;
		case OMAP447X_OPP119_LOW:
			strcpy(s, "OPP119_LOW");
			break;
		case OMAP447X_OPP119_HIGH:
			strcpy(s, "OPP119_HIGH");
			break;
		default:
			strcpy(s, "UNKNOWN");
			return OMAPCONF_ERR_ARG;
		}
	} else {
		switch (opp) {
		case OMAP4_OPPDPLL_CASC:
			strcpy(s, "DPLL_CASC");
			break;
		case OMAP4_OPP50:
			strcpy(s, "OPP50");
			break;
		case OMAP4_OPP100:
			strcpy(s, "OPP100");
			break;
		case OMAP4_OPP_TURBO:
			strcpy(s, "OPP_TURBO");
			break;
		case OMAP4_OPP_NITRO:
			strcpy(s, "OPP_NITRO");
			break;
		case OMAP4_OPP_NITRO_SB:
			strcpy(s, "OPP_NITRO_SB");
			break;
		default:
			strcpy(s, "UNKNOWN");
			return OMAPCONF_ERR_ARG;
		}
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp44xx_s2id
 * @BRIEF		convert string to valid OPP ID.
 * @RETURNS		valid OMAP4 OPP ID in case of success
 *			OPP44XX_ID_MAX otherwise
 * @param[in]		s: string
 * @DESCRIPTION		convert string to valid OPP ID.
 *//*------------------------------------------------------------------------ */
unsigned int opp44xx_s2id(char *s)
{
	CHECK_NULL_ARG(s, OPP44XX_ID_MAX);

	if (strcmp(s, "dpll_casc") == 0)
		return (unsigned int) OMAP4_OPPDPLL_CASC;
	else if (strcmp(s, "opp50") == 0)
		return (unsigned int) OMAP4_OPP50;
	else if (strcmp(s, "opp100") == 0)
		return (unsigned int) OMAP4_OPP100;
	else if (strcmp(s, "opp_turbo") == 0)
		return (unsigned int) OMAP4_OPP_TURBO;
	else if (strcmp(s, "opp_nitro") == 0)
		return (unsigned int) OMAP4_OPP_NITRO;
	else if (strcmp(s, "opp_nitrosb") == 0)
		return (unsigned int) OMAP4_OPP_NITRO_SB;
	else if (strcmp(s, "opp50_low") == 0)
		return (unsigned int) OMAP447X_OPP50_LOW;
	else if (strcmp(s, "opp50_high") == 0)
		return (unsigned int) OMAP447X_OPP50_HIGH;
	else if (strcmp(s, "opp100_low") == 0)
		return (unsigned int) OMAP447X_OPP100_LOW;
	else if (strcmp(s, "opp100_high") == 0)
		return (unsigned int) OMAP447X_OPP100_HIGH;
	else if (strcmp(s, "opp119_low") == 0)
		return (unsigned int) OMAP447X_OPP119_LOW;
	else if (strcmp(s, "opp119_high") == 0)
		return (unsigned int) OMAP447X_OPP119_HIGH;
	else
		return (unsigned int) OPP44XX_ID_MAX;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm44xx_id2s
 * @BRIEF		convert voltage domain ID to voltage domain name, as
 *			defined in voltdm.h.
 * @RETURNS		Generic string corresponding to voltage domain ID
 *			NULL in case of invalid voltage domain ID
 * @param[in]		id: voltage domain ID
 * @DESCRIPTION		convert voltage domain ID to voltage domain name, as
 *			defined in voltdm.h.
 *//*------------------------------------------------------------------------ */
const char *voltdm44xx_id2s(voltdm44xx_id id)
{
	const char *s;
	CHECK_ARG_LESS_THAN(id, OMAP4_VD_ID_MAX, NULL);

	switch (id) {
	case OMAP4_LDO_WKUP:
		s = VDD_WKUP;
		break;
	case OMAP4_VDD_MPU:
		s = VDD_MPU;
		break;
	case OMAP4_VDD_IVA:
		s = VDD_IVA;
		break;
	case OMAP4_VDD_CORE:
		s = VDD_CORE;
		break;
	default:
		s = NULL;
	}

	dprintf("%s(%d) = %s\n", __func__, id, s);
	return s;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm44xx_get_voltage
 * @BRIEF		find the current supply voltage of a domain, taking care
 *			of the voltage domain state (ON/ON_LP/RET/OFF).
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		id: voltage domain ID
 * @param[in]		volt: supply voltage (returned)
 * @DESCRIPTION		find the current supply voltage of a domain, taking care
 *			of the voltage domain state (ON/ON_LP/RET/OFF).
 *			NB: use PRCM VP VOLTAGE register to retrieve ON voltage.
 *			Hence SR/VP/VC have to be at least initialized
 *			(SR could be disabled).
 *//*------------------------------------------------------------------------ */
int voltdm44xx_get_voltage(voltdm44xx_id id, double *volt)
{
	voltdm44xx_voltage_type type;
	pwrdm_state state1, state2, state3;
	int ret;

	if (volt == NULL)
		return OMAPCONF_ERR_ARG;
	*volt = 0.0;
	if (!cpu_is_omap44xx())
		return OMAPCONF_ERR_CPU;

	/* Retrieve domain state */
	switch (id) {
	case OMAP4_LDO_WKUP:
		return OMAPCONF_ERR_NOT_AVAILABLE;
	case OMAP4_VDD_MPU:
		/* When OMAPCONF is running, MPU domain is by essence ON ... */
		type = OMAP4_ON_VOLTAGE;
		break;
	case OMAP4_VDD_IVA:
		ret = pwrdm44xx_get_state(OMAP4_PD_ABE, &state1);
		ret += pwrdm44xx_get_state(OMAP4_PD_IVA_HD,
			&state2);
		ret += pwrdm44xx_get_state(OMAP4_PD_DSP,
			&state3);
		if (ret != 0)
			return ret;
		else if ((sr44xx_is_enabled(OMAP4_SR_IVA) == 1) ||
			(state1 == PWRDM_ON_STATE) ||
			(state2 == PWRDM_ON_STATE) ||
			(state3 == PWRDM_ON_STATE))
			type = OMAP4_ON_VOLTAGE;
		else if ((state1 == PWRDM_INACTIVE_STATE) &&
			(state2 == PWRDM_INACTIVE_STATE) &&
			(state3 == PWRDM_INACTIVE_STATE))
			type = OMAP4_ON_LOW_POWER_VOLTAGE;
		else if ((state1 == PWRDM_RET_STATE) &&
			(state2 == PWRDM_RET_STATE) &&
			(state3 == PWRDM_RET_STATE))
			type = OMAP4_RETENTION_VOLTAGE;
		else
			/* When no module is being used in VDD_IVA
			 * (ABE, IVAHD, DSP in OFF) VDD_IVA is still
			 * configured at Retention Voltage: it is not possible
			 * to switch off VDD_IVA independently from
			 * other VDD domains.
			 * Device OFF mode is the only case where VDD domains
			 * are reaching 0.0V: not observable with OMAPCONF.
			 */
			type = OMAP4_RETENTION_VOLTAGE;
		break;
	case OMAP4_VDD_CORE:
		/* When OMAPCONF is running, CORE domain is by essence ON ... */
		type = OMAP4_ON_VOLTAGE;
		break;
	default:
		return OMAPCONF_ERR_ARG;
	}

	ret = voltdm44xx_get_voltage_by_type(id, type, volt);

	dprintf("%s(): domain=%s vp_voltage type=%d volt=%lf ret=%d\n",
		__func__, voltdm44xx_name_table[id], type, *volt, ret);

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm44xx_get_voltage_by_type
 * @BRIEF		return the programmed voltage of a domain.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		id: voltage domain ID
 * @param[in]		type: voltage type (ON/SLEEP/RETENTION/OFF)
 * @param[in,out]	volt: programmed voltage (returned)
 * @DESCRIPTION		return the programmed voltage of a domain.
 *//*------------------------------------------------------------------------ */
int voltdm44xx_get_voltage_by_type(voltdm44xx_id id,
	voltdm44xx_voltage_type type, double *volt)
{
	unsigned int prm_vc_val_cmd_vdd, prm_vc_val_cmd_vdd_addr;
	unsigned short vsel_len;
	omap4_sr_module_id sr_id;
	int ret;

	CHECK_NULL_ARG(volt, OMAPCONF_ERR_ARG);
	*volt = 0.0;
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(type, OMAP4_VOLTAGE_TYPE_MAX, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(id, OMAP4_VD_ID_MAX, OMAPCONF_ERR_ARG);

	switch (id) {
	case OMAP4_LDO_WKUP:
		dprintf("%s(): not available for LDO_WKUP domain!\n", __func__);
		ret = OMAPCONF_ERR_NOT_AVAILABLE;
		goto voltdm44xx_get_voltage_by_type_end;
	case OMAP4_VDD_MPU:
		sr_id = OMAP4_SR_MPU;
		prm_vc_val_cmd_vdd_addr = OMAP4430_PRM_VC_VAL_CMD_VDD_MPU_L;
		break;
	case OMAP4_VDD_IVA:
		sr_id = OMAP4_SR_IVA;
		prm_vc_val_cmd_vdd_addr = OMAP4430_PRM_VC_VAL_CMD_VDD_IVA_L;
		break;
	case OMAP4_VDD_CORE:
		sr_id = OMAP4_SR_CORE;
		prm_vc_val_cmd_vdd_addr = OMAP4430_PRM_VC_VAL_CMD_VDD_CORE_L;
		break;
	default:
		return OMAPCONF_ERR_ARG;
	}

	vsel_len = smps_vsel_len_get(vdd_id2smps_id(id));
	dprintf("%s(%s, %u): vsel_len = %u\n", __func__,
		voltdm44xx_name_table[id], type, vsel_len);
	if (vsel_len <= 0) {
		dprintf("%s(): error getting vsel_len!\n", __func__);
		ret =  OMAPCONF_ERR_NOT_AVAILABLE;
		goto voltdm44xx_get_voltage_by_type_end;
	}

	if ((type == OMAP4_ON_VOLTAGE) && \
		(sr44xx_is_enabled(sr_id) == 1)) {
			/* SR ON, get ON voltage from VP register */
			ret = sr44xx_vp_voltage_get(sr_id, volt);
			dprintf("%s(): %s: SR ON, ON VP voltage is %lfV\n",
				__func__, voltdm44xx_name_table[id], *volt);
	} else {
		dprintf("%s(%s, %u): get programmed voltage from VC register\n",
			__func__, voltdm44xx_name_table[id], type);
		/* Get programmed voltage from VC register */
		if (mem_read(prm_vc_val_cmd_vdd_addr,
			&prm_vc_val_cmd_vdd) != 0) {
			dprintf("%s(): error reading VC register!\n", __func__);
			ret = OMAPCONF_ERR_REG_ACCESS;
			goto voltdm44xx_get_voltage_by_type_end;
		}

		*volt = smps_vsel2volt(vdd_id2smps_id(id),
			extract_bitfield(prm_vc_val_cmd_vdd, type, vsel_len));
		if (*volt < 0.0) {
			dprintf("%s(): error converting vsel to volt!\n",
				__func__);
			ret = OMAPCONF_ERR_NOT_AVAILABLE;
			goto voltdm44xx_get_voltage_by_type_end;
		}

		dprintf("%s(%s, %u): prm_vc_val_cmd_vdd = 0x%08X, voltage=%lfV"
			" (%u)\n", __func__, voltdm44xx_name_table[id],
			type, prm_vc_val_cmd_vdd, *volt,
			extract_bitfield(prm_vc_val_cmd_vdd, type, vsel_len));
		ret = 0;
	}

voltdm44xx_get_voltage_by_type_end:
	dprintf("%s(%s, %u): ret=%d\n", __func__, voltdm44xx_name_table[id],
			type, ret);
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm44xx_vminsearch
 * @BRIEF		Search minimum supply voltage of a given voltage domain
 *			by decreasing voltage step by step until it breaks.
 *			NB: PLATFORM MUST BE REBOOTED AFTER USE
 *			(CRASHED WITH NO POSSIBLE RECOVERY)
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in]		vdd_id: voltage domain ID
 * @param[in]		v: initial voltage (in Volts)
 * @param[in]		ms: waiting time between 2 steps (in ms)
 * @DESCRIPTION		Search minimum supply voltage of a given voltage domain
 *			by decreasing voltage step by step until it breaks.
 *			NB: PLATFORM MUST BE REBOOTED AFTER USE
 *			(CRASHED WITH NO POSSIBLE RECOVERY)
 *//*------------------------------------------------------------------------ */
int voltdm44xx_vminsearch(voltdm44xx_id vdd_id, double v, unsigned int ms)
{
	long uv;
	int ret, bandgap_temp;
	char voltdm_name[VOLTDM44XX_MAX_NAME_LENGTH];
	unsigned vstep;
	unsigned char vsel;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(vdd_id, OMAP4_VD_ID_MAX, OMAPCONF_ERR_ARG);
	if (v <= 0.0) {
		fprintf(stderr, "%s(): v <= 0.0 !!!\n", __func__);
		return OMAPCONF_ERR_ARG;
	}

	printf("Vmin search on %s domain scaling voltage down from %1.3lfV, "
		"waiting %dms between 2 steps.\n",
		voltdm44xx_get_name(vdd_id, voltdm_name), v, ms);
	printf("LAST voltage displayed with OK status before crash "
		"will be the Vmin for %s domain.\n\n",
		voltdm44xx_get_name(vdd_id, voltdm_name));
	printf("NB:\n  - Make sure your load generator application is "
		"running in background during the whole procedure.\n");
	printf("  - PLATFORM MUST BE REBOOTED AFTER USE "
		"(NO POSSIBLE RECOVERY).\n\n");

	/* Show current OPP for reference */
	printf("Current OPP settings for reference:\n\n");
	opp_show(stdout);

	/* decreasing step by step voltage until it breaks */
	printf("Starting Vmin search...\n");
	vstep = smps_step_get(vdd_id2smps_id(vdd_id));

	/* Translate the target voltage value into a SMPS voltage value */
	/* Change voltage value from V to uV */
	v = v * 1000000;
	/* Get vsel corresponding to target voltage */
	vsel = smps_uvolt2vsel(vdd_id2smps_id(vdd_id), v);
	/* Compute the SMPS voltage value: voltage >= target voltage */
	v = smps_offset_get(vdd_id2smps_id(vdd_id)) +
		((vsel - 1) * smps_step_get(vdd_id2smps_id(vdd_id)));

	/* change voltage value from uV to V */
	v = v / 1000000;

	for (uv = (unsigned long) (v * 1000000); uv > 0; uv = uv - vstep) {

		/* Get vsel corresponding to target voltage */
		vsel = smps_uvolt2vsel(vdd_id2smps_id(vdd_id), uv);
		bandgap_temp = temp44xx_get(TEMP44XX_BANDGAP);
		if (bandgap_temp != TEMP_ABSOLUTE_ZERO) {
			printf(
				"Trying %1.6lfV (SMPS code: %02d, temperature: %dC/%dF)...",
				(double) ((double) uv / 1000000.0), vsel,
				bandgap_temp, celcius2fahrenheit(bandgap_temp));
		} else {
			printf("Trying %1.6lfV (SMPS code: %02d, temperature: N/A)...",
				(double) ((double) uv / 1000000.0), vsel);
		}
		fflush(stdout);
		ret = sr44xx_voltage_set(vdd_id, uv);
		if (ret != 0) {
			fprintf(stderr, "Error: could not set %s voltage!\n\n",
				voltdm44xx_get_name(vdd_id, voltdm_name));
			return ret;
		}
		usleep(1000 * ms);
		printf("OK!\n");
	}
	fprintf(stderr, "Shouldn't have reached this point... "
		"please check voltage is really scaling down.\n\n");
	return OMAPCONF_ERR_UNEXPECTED;
}
