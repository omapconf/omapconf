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


#include <voltdomain.h>
#include <opp.h>
#include <voltdm54xx.h>
#include <vc54xx.h>
#include <dpll54xx.h>
#include <cpuinfo.h>
#include <prm54xxes1-defs.h>
#include <sr54xx.h>
#include <pwrdm.h>
#include <clock54xx.h>
#include <module54xx.h>
#include <autoadjust_table.h>
#include <reg.h>
#include <pmic.h>
#include <prm54xx-defs.h>


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


static const double
	voltdm54xx_por_nominal_voltages_table_es1[VDD54XX_ID_MAX][OPP54XX_ID_MAX + 1] = {
	{-1.0, -1.0, -1.0, -1.0, -1.0}, /* VDD_WKUP */
	{0.94, 0.95, 1.04, 1.22, -1.0}, /* VDD_MPU */
	{0.94, 0.95, 1.04, 1.22, -1.0}, /* VDD_MM */
	{0.94, 0.95, 1.04, -1.0, -1.0} }; /* VDD_CORE */


static unsigned short voltdm54xx_init_done = 0;
genlist voltdm54xx_list;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm54xx_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void voltdm54xx_init(void)
{
	voltdm_info voltdm;

	if (voltdm54xx_init_done)
		return;

	genlist_init(&voltdm54xx_list);

	voltdm.name = VDD_WKUP;
	voltdm.id = (int) VDD54XX_WKUP;
	if (cpu_revision_get() == REV_ES1_0)
		voltdm.voltst = NULL; /* Not present on ES1.0 */
	else
		voltdm.voltst = &omap5430_prm_voltst_mpu;
	genlist_addtail(
		&voltdm54xx_list, (void *) &voltdm, sizeof(voltdm_info));

	voltdm.name = VDD_MPU;
	voltdm.id = (int) VDD54XX_MPU;
	if (cpu_revision_get() == REV_ES1_0)
		voltdm.voltst = NULL; /* Not present on ES1.0 */
	else
		voltdm.voltst = &omap5430_prm_voltst_mpu;
	genlist_addtail(
		&voltdm54xx_list, (void *) &voltdm, sizeof(voltdm_info));

	voltdm.name = VDD_MM;
	voltdm.id = (int) VDD54XX_MM;
	if (cpu_revision_get() == REV_ES1_0)
		voltdm.voltst = NULL; /* Not present on ES1.0 */
	else
		voltdm.voltst = &omap5430_prm_voltst_mpu;
	genlist_addtail(
		&voltdm54xx_list, (void *) &voltdm, sizeof(voltdm_info));

	voltdm.name = VDD_CORE;
	voltdm.id = (int) VDD54XX_CORE;
	voltdm.voltst = NULL;
	genlist_addtail(
		&voltdm54xx_list, (void *) &voltdm, sizeof(voltdm_info));

	voltdm54xx_init_done = 1;
	dprintf("%s(): init done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm54xx_deinit
 * @BRIEF		free dynamically allocated internal data.
 * @DESCRIPTION		free dynamically allocated internal data.
 *			MUST BE CALLED AT END OF EXECUTION.
 *//*------------------------------------------------------------------------ */
void voltdm54xx_deinit(void)
{
	if (voltdm54xx_init_done) {
		genlist_free(&voltdm54xx_list);
		voltdm54xx_init_done = 0;

	}
	dprintf("%s(): deinit done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm54xx_list_get
 * @BRIEF		return the list of voltage domains
 * @RETURNS		list of voltage domains in case of success
 *			NULL in case of error
 * @DESCRIPTION		return the list of voltage domains
 *//*------------------------------------------------------------------------ */
const genlist *voltdm54xx_list_get(void)
{
	voltdm54xx_init();

	return (const genlist *) &voltdm54xx_list;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm54xx_count_get
 * @BRIEF		return the number of voltage domains
 * @RETURNS		number of voltage domains (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @DESCRIPTION		return the number of voltage domains
 *//*------------------------------------------------------------------------ */
int voltdm54xx_count_get(void)
{
	int count;

	voltdm54xx_init();

	count = genlist_getcount(&voltdm54xx_list);

	dprintf("%s() = %d\n", __func__, count);
	return count;
}


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
 * @FUNCTION		voltdm54xx_id2s
 * @BRIEF		convert voltage domain ID into voltage domain name, as
 *			defined in voltdm.h.
 * @RETURNS		Voltage Domain name, as defined in voltdm.h.
 *			NULL in case of invalid voltage domain ID
 * @param[in]		id: voltage domain ID
 * @DESCRIPTION		convert voltage domain ID to voltage domain name.
 *//*------------------------------------------------------------------------ */
const char *voltdm54xx_id2s(voltdm54xx_id id)
{
	const char *s;
	CHECK_ARG_LESS_THAN(id, VDD54XX_ID_MAX, NULL);

	switch (id) {
	case VDD54XX_WKUP:
		s = VDD_WKUP;
		break;
	case VDD54XX_MPU:
		s = VDD_MPU;
		break;
	case VDD54XX_MM:
		s = VDD_MM;
		break;
	case VDD54XX_CORE:
		s = VDD_CORE;
		break;
	default:
		s = NULL;
	}

	dprintf("%s(%d) = %s\n", __func__, id, s);
	return s;
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
 * @FUNCTION		voltdm54xx_nominal_voltage_get
 * @BRIEF		return the nominal voltage of a given voltage domain
 * @RETURNS		supply voltage in case of success (>= 0.0)
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		id: valid voltage domain ID
 * @DESCRIPTION		return the nominal voltage of a given voltage domain.
 *//*------------------------------------------------------------------------ */
double voltdm54xx_nominal_voltage_get(voltdm54xx_id id)
{
	int ret;
	double volt;
	vc54xx_registers vc_regs;
	unsigned char cmd_on, cmd_onlp, cmd_ret, cmd_off;

	CHECK_CPU(54xx, (double) OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(id, VDD54XX_ID_MAX, (double) OMAPCONF_ERR_ARG);

	ret = vc54xx_registers_get(&vc_regs);
	if (ret != 0)
		return (double) ret;
	ret = vc54xx_cmd_values_get(id, &vc_regs,
			&cmd_on, &cmd_onlp, &cmd_ret, &cmd_off);
	if (ret != 0)
		return (double) ret;

	volt = smps_vsel2volt(vdd_id2smps_id(id), cmd_on);

	dprintf("%s(%s): nominal volt=%lfV\n", __func__,
		voltdm54xx_name_get(id), volt);

	return volt;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm54xx_por_nominal_voltage_get
 * @BRIEF		return the Plan of Record (POR) nominal voltage
 *			of a given voltage domain for a given OPP.
 * @RETURNS		supply voltage in case of success (>= 0.0)
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 * @param[in]		id: valid voltage domain ID
 * @DESCRIPTION		return the Plan of Record (POR) nominal voltage
 *			of a given voltage domain for a given OPP.
 *//*------------------------------------------------------------------------ */
double voltdm54xx_por_nominal_voltage_get(voltdm54xx_id id, opp54xx_id opp_id)
{
	double volt;

	CHECK_CPU(54xx, (double) OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(id, VDD54XX_ID_MAX, (double) OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(id, VDD54XX_ID_MAX, (double) OMAPCONF_ERR_ARG);

	volt = voltdm54xx_por_nominal_voltages_table_es1[id][opp_id];

	dprintf("%s(%s): %s POR nominal volt=%lfV\n", __func__,
		opp54xx_name_get(opp_id),
		voltdm54xx_name_get(id), volt);

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
