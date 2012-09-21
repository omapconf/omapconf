/*
 *
 * @Component			OMAPCONF
 * @Filename			voltdm54xx.c
 * @Description			OMAP5 Voltage Domain Definitions & APIs
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


#include <voltdm54xx.h>
#include <dpll54xx.h>
#include <cpuinfo.h>
#include <prm54xx-defs.h>
#include <sr54xx.h>
#include <pwrdm.h>
#include <clock54xx.h>
#include <module54xx.h>
#include <autoadjust_table.h>
#include <reg.h>
#include <pmic.h>


/* #define VOLTDM54XX_DEBUG */
#ifdef VOLTDM54XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static const char
	voltdm54xx_names_table[VDD54XX_ID_MAX][VOLTDM_MAX_NAME_LENGTH] = {
	"VDD_WKUP",
	"VDD_MPU",
	"VDD_MM",
	"VDD_CORE"};


static const char
	opp54xx_names_table[OPP54XX_ID_MAX + 1][OPP_MAX_NAME_LENGTH] = {
	"DPLL_CASC",
	"LOW",
	"NOM",
	"HIGH",
	"SPEEDBIN",
	"UNKNOWN"};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm54xx_name_get
 * @BRIEF		return voltage domain name
 * @RETURNS		voltage domain name on success
 *			NULL in case of error
 * @param[in]		id: valid voltage domain ID
 * @DESCRIPTION		return voltage domain name
 *//*------------------------------------------------------------------------ */
const char *voltdm54xx_name_get(voltdm54xx_id id)
{
	CHECK_ARG_LESS_THAN(id, VDD54XX_ID_MAX, NULL);

	return voltdm54xx_names_table[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp54xx_s2id
 * @BRIEF		convert string to valid OPP ID
 * @RETURNS		OPP54XX_DPLL_CASC if s == "dpll_casc"
 *			OPP54XX_LOW if s == "low"
 *			OPP54XX_NOM if s == "nom"
 *			OPP54XX_HIGH if s == "high"
 *			OPP54XX_SB if s == "speedbin"
 *			OPP54XX_ID_MAX otherwise
 * @param[in,out]	s: string
 * @DESCRIPTION		convert string to valid OPP ID
 *//*------------------------------------------------------------------------ */
opp54xx_id opp54xx_s2id(char *s)
{
	CHECK_NULL_ARG(s, OPP54XX_ID_MAX);

	if (strcmp(s, "dpll_casc") == 0)
		return OPP54XX_DPLL_CASC;
	else if (strcmp(s, "low") == 0)
		return OPP54XX_LOW;
	else if (strcmp(s, "nom") == 0)
		return OPP54XX_NOM;
	else if (strcmp(s, "high") == 0)
		return OPP54XX_HIGH;
	else if (strcmp(s, "speedbin") == 0)
		return OPP54XX_SB;
	else
		return OPP54XX_ID_MAX;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp54xx_name_get
 * @BRIEF		return OPP name
 * @RETURNS		OPP name on success
 *			NULL in case of error
 * @param[in]		id: valid OPP ID
 * @DESCRIPTION		return OPP name
 *//*------------------------------------------------------------------------ */
const char *opp54xx_name_get(opp54xx_id id)
{
	CHECK_ARG_LESS_THAN(id, OPP54XX_ID_MAX + 1, NULL);

	return opp54xx_names_table[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm54xx_opp_get
 * @BRIEF		find the current voltage domain OPP
 * @RETURNS		valid OPP ID in case of success
 *			OPP54XX_ID_MAX in case of error
 * @param[in]		id: voltage domain ID
 * @DESCRIPTION		find the current voltage domain OPP
 *//*------------------------------------------------------------------------ */
opp54xx_id voltdm54xx_opp_get(voltdm54xx_id id)
{
	opp54xx_id opp_id;
	mod54xx_id module_id;
	dpll54xx_id dpll_id;
	dpll_status status;
	double rate = 0.0, rate_por = 0.0;

	CHECK_CPU(54xx, OPP54XX_ID_MAX);
	CHECK_ARG_LESS_THAN(id, VDD54XX_ID_MAX, OPP54XX_ID_MAX);

	/*
	 * Determine current OPPs by getting MPU / IVA / L3 / SARRAM rate
	 * and comparing it to POR rate.
	 */
	switch (id) {
	case VDD54XX_WKUP:
		module_id = OMAP5_L4WKUP_INTERCONNECT;
		dpll_id = DPLL54XX_CORE;
		break;

	case VDD54XX_MPU:
		module_id = OMAP5_MPU;
		dpll_id = DPLL54XX_MPU;
		break;

	case VDD54XX_MM:
		module_id = OMAP5_IVA;
		dpll_id = DPLL54XX_IVA;
		break;

	case VDD54XX_CORE:
		module_id = OMAP5_L3_MAIN1_INTERCONNECT;
		dpll_id = DPLL54XX_CORE;
		break;

	default:
		return OPP54XX_ID_MAX;
	}

	/* if the DPLL clocking the selected module is stopped,
	 * reported speed will be 0 and OPP cannot be detected.
	 * Hence, if DPLL is stopped, ignore DPLL status to get
	 * the speed when the DPLL is running.
	 */
	status = dpll54xx_status_get(dpll_id);
	if (status == DPLL_STATUS_STOPPED)
		rate = mod54xx_clk_rate_get(module_id, 1);
	else
		rate = mod54xx_clk_rate_get(module_id, 0);

	dprintf("%s(%s): %s rate is %lfMHz\n", __func__,
		voltdm54xx_name_get(id),
		clk54xx_name_get(mod54xx_clk_get(module_id)), rate);

	for (opp_id = OPP54XX_DPLL_CASC; opp_id < OPP54XX_ID_MAX; opp_id++) {
		rate_por = mod54xx_por_clk_rate_get(module_id, opp_id);
		dprintf("%s(%s): %s POR rate for %s is %lf\n",
			__func__, voltdm54xx_name_get(id),
			mod54xx_name_get(module_id),
			opp54xx_name_get(opp_id), rate_por);
		if ((int) rate == (int) rate_por) {
			dprintf("%s(%s): OPP found: %s\n",
				__func__, voltdm54xx_name_get(id),
				opp54xx_name_get(opp_id));
			return opp_id;
		}
	}

	dprintf("%s(%s): OPP not found!\n", __func__, voltdm54xx_name_get(id));

	return OPP54XX_ID_MAX;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vr54xx_vsel2uv
 * @BRIEF		for a given rail, convert SMPS vsel command into voltage
 *			in microvolts.
 * @RETURNS		voltage in microvolts corresponding to SMPS vsel command
 * @param[in]		id: valid voltage rail
 * @param[in]		vsel: SMPS vsel command
 * @DESCRIPTION		for a given rail, convert SMPS vsel command into voltage
 *			in microvolts.
 *//*------------------------------------------------------------------------ */
unsigned long vr54xx_vsel2uv(voltdm54xx_id id, unsigned char vsel)
{
	unsigned long uv = 0;

	CHECK_ARG_LESS_THAN(id, VDD54XX_ID_MAX, 0);

	dprintf("%s(%s, 0x%X) = %luuV\n", __func__,
		voltdm54xx_name_get(id), vsel, uv);
	/* FIXME */
	/* just to remove "unused parameter" warnings ... */
	vsel = vsel;

	return uv;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vr54xx_vsel2volt
 * @BRIEF		for a given rail, convert SMPS vsel command into voltage
 *			(in VOLTS).
 * @RETURNS		voltage in VOLTS corresponding to SMPS vsel command
 * @param[in]		id: voltage rail
 * @param[in]		vsel: SMPS vsel command
 * @DESCRIPTION		for a given rail, convert SMPS vsel command into voltage
 *			(in VOLTS).
 *//*------------------------------------------------------------------------ */
double vr54xx_vsel2volt(voltdm54xx_id id, unsigned char vsel)
{
	double volt;

	CHECK_ARG_LESS_THAN(id, VDD54XX_ID_MAX, 0);

	volt = (double) vr54xx_vsel2uv(id, vsel);
	volt /= (double) 1000000.0;

	dprintf("%s(%s, 0x%X) = %lfV\n", __func__,
		voltdm54xx_name_get(id), vsel, volt);

	return volt;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm54xx_voltage_get
 * @BRIEF		find the current supply voltage of a domain
 * @RETURNS		supply voltage in case of success (>= 0.0)
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		id: valid voltage domain ID
 * @DESCRIPTION		find the current supply voltage of a domain,
 *			taking care of the voltage domain state
 *			(ON/ON_LP/RET/OFF)
 *			NB: use PRCM VP VOLTAGE register to retrieve ON voltage.
 *			Hence SR/VP/VC have to be at least initialized
 *			(SR could be disabled)
 *//*------------------------------------------------------------------------ */
double voltdm54xx_voltage_get(voltdm54xx_id id)
{
	double volt;

	CHECK_CPU(54xx, (double) OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(id, VDD54XX_ID_MAX, (double) OMAPCONF_ERR_ARG);

	/* Retrieve domain state */
	switch (id) {
	case VDD54XX_WKUP:
		return (double) OMAPCONF_ERR_NOT_AVAILABLE;

	case VDD54XX_MPU:
		volt = smps_voltage_get(PMIC_SMPS_MPU);
		break;
	case VDD54XX_MM:
		volt = smps_voltage_get(PMIC_SMPS_MM);
		break;
	case VDD54XX_CORE:
		volt = smps_voltage_get(PMIC_SMPS_CORE);
		break;

	default:
		return (double) OMAPCONF_ERR_ARG;
	}

	dprintf("%s(%s): volt=%lfV\n", __func__, voltdm54xx_name_get(id), volt);

	return volt;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm54xx_voltage_set
 * @BRIEF		set voltage of given voltage domain
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		id: valid voltage domain ID
 * @DESCRIPTION		set voltage of given voltage domain
 *//*------------------------------------------------------------------------ */
int voltdm54xx_voltage_set(voltdm54xx_id id, unsigned long uv)
{

	CHECK_CPU(54xx, (double) OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(id, VDD54XX_ID_MAX, (double) OMAPCONF_ERR_ARG);

	/* Retrieve domain state */
	switch (id) {
	case VDD54XX_WKUP:
		return OMAPCONF_ERR_NOT_AVAILABLE;

	case VDD54XX_MPU:
		return smps_voltage_set(PMIC_SMPS_MPU, uv);
		break;
	case VDD54XX_MM:
		return smps_voltage_set(PMIC_SMPS_MM, uv);
		break;
	case VDD54XX_CORE:
		return smps_voltage_set(PMIC_SMPS_CORE, uv);
		break;

	default:
		return OMAPCONF_ERR_ARG;
	}
}
