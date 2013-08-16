/*
 *
 * @Component			OMAPCONF
 * @Filename			voltdm_dra7xx.c
 * @Description			DRA7 Voltage Domain Definitions & APIs
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


#include <voltdomain.h>
#include <opp.h>
#include <voltdm_dra7xx.h>
#include <dpll_dra7xx.h>
#include <cpuinfo.h>
#include <prm_dra7xx-defs.h>
#include <pwrdm.h>
#include <clock_dra7xx.h>
#include <autoadjust_table.h>
#include <reg.h>
#include <pmic.h>


/* #define VOLTDM_DRA7XX_DEBUG */
#ifdef VOLTDM_DRA7XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static const char
	voltdm_dra7xx_names_table[VDD_DRA7XX_ID_MAX][VOLTDM_MAX_NAME_LENGTH] = {
	[VDD_DRA7XX_CORE] = "VDD_CORE",
	[VDD_DRA7XX_MPU] = "VDD_MPU",
	[VDD_DRA7XX_IVA] = "VDD_IVA",
	[VDD_DRA7XX_DSPEVE] = "VDD_DSPEVE",
	[VDD_DRA7XX_GPU] = "VDD_GPU",
	[VDD_DRA7XX_RTC] = "VDD_RTC"};


static const char
	opp_dra7xx_names_table[OPP_DRA7XX_ID_MAX + 1][OPP_MAX_NAME_LENGTH] = {
	[OPP_DRA7XX_NOM] = "NOM",
	[OPP_DRA7XX_OD] = "OD",
	[OPP_DRA7XX_HIGH] = "HIGH",
	[OPP_DRA7XX_ID_MAX] = "UNKNOWN"};


static const double
	voltdm_dra7xx_por_nominal_voltages_table[VDD_DRA7XX_ID_MAX][OPP_DRA7XX_ID_MAX + 1] = {
	[VDD_DRA7XX_CORE] = {1.03, -1.0, -1.0, -1.0},
	[VDD_DRA7XX_MPU] = {1.06, 1.16, 1.25, -1.0},
	[VDD_DRA7XX_IVA] = {1.06, 1.15, 1.25, -1.0},
	[VDD_DRA7XX_DSPEVE] = {1.06, 1.15, -1.0, -1.0},
	[VDD_DRA7XX_GPU] = {1.06, 1.15, 1.25, -1.0},
	[VDD_DRA7XX_RTC] = {1.03, -1.0, -1.0, -1.0}
};


static unsigned short voltdm_dra7xx_init_done;
genlist voltdm_dra7xx_list;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm_dra7xx_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void voltdm_dra7xx_init(void)
{
	voltdm_info voltdm;

	if (voltdm_dra7xx_init_done)
		return;

	genlist_init(&voltdm_dra7xx_list);

	voltdm.name = VDD_CORE;
	voltdm.id = (int) VDD_DRA7XX_CORE;
	voltdm.voltst = NULL;
	genlist_addtail(
		&voltdm_dra7xx_list, (void *) &voltdm, sizeof(voltdm_info));

	voltdm.name = VDD_MPU;
	voltdm.id = (int) VDD_DRA7XX_MPU;
	voltdm.voltst = &dra7xx_device_prm_prm_voltst_mpu;
	genlist_addtail(
		&voltdm_dra7xx_list, (void *) &voltdm, sizeof(voltdm_info));

	voltdm.name = VDD_GPU;
	voltdm.id = (int) VDD_DRA7XX_GPU;
	voltdm.voltst = NULL;
	genlist_addtail(
		&voltdm_dra7xx_list, (void *) &voltdm, sizeof(voltdm_info));

	voltdm.name = VDD_DSPEVE;
	voltdm.id = (int) VDD_DRA7XX_DSPEVE;
	voltdm.voltst = NULL;
	genlist_addtail(
		&voltdm_dra7xx_list, (void *) &voltdm, sizeof(voltdm_info));

	voltdm.name = VDD_IVA;
	voltdm.id = (int) VDD_DRA7XX_IVA;
	voltdm.voltst = NULL;
	genlist_addtail(
		&voltdm_dra7xx_list, (void *) &voltdm, sizeof(voltdm_info));

	voltdm.name = VDD_RTC;
	voltdm.id = (int) VDD_DRA7XX_RTC;
	voltdm.voltst = NULL;
	genlist_addtail(
		&voltdm_dra7xx_list, (void *) &voltdm, sizeof(voltdm_info));

	voltdm_dra7xx_init_done = 1;
	dprintf("%s(): init done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm_dra7xx_deinit
 * @BRIEF		free dynamically allocated internal data.
 * @DESCRIPTION		free dynamically allocated internal data.
 *			MUST BE CALLED AT END OF EXECUTION.
 *//*------------------------------------------------------------------------ */
void voltdm_dra7xx_deinit(void)
{
	if (voltdm_dra7xx_init_done) {
		genlist_free(&voltdm_dra7xx_list);
		voltdm_dra7xx_init_done = 0;
	}
	dprintf("%s(): deinit done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm_dra7xx_list_get
 * @BRIEF		return the list of voltage domains
 * @RETURNS		list of voltage domains in case of success
 *			NULL in case of error
 * @DESCRIPTION		return the list of voltage domains
 *//*------------------------------------------------------------------------ */
const genlist *voltdm_dra7xx_list_get(void)
{
	voltdm_dra7xx_init();

	return (const genlist *) &voltdm_dra7xx_list;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm_dra7xx_count_get
 * @BRIEF		return the number of voltage domains
 * @RETURNS		number of voltage domains (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @DESCRIPTION		return the number of voltage domains
 *//*------------------------------------------------------------------------ */
int voltdm_dra7xx_count_get(void)
{
	int count;

	voltdm_dra7xx_init();

	count = genlist_getcount(&voltdm_dra7xx_list);

	dprintf("%s() = %d\n", __func__, count);
	return count;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm_dra7xx_name_get
 * @BRIEF		return voltage domain name
 * @RETURNS		voltage domain name on success
 *			NULL in case of error
 * @param[in]		id: valid voltage domain ID
 * @DESCRIPTION		return voltage domain name
 *//*------------------------------------------------------------------------ */
const char *voltdm_dra7xx_name_get(voltdm_dra7xx_id id)
{
	CHECK_ARG_LESS_THAN(id, VDD_DRA7XX_ID_MAX, NULL);

	return voltdm_dra7xx_names_table[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp_dra7xx_s2id
 * @BRIEF		convert string to valid OPP ID
 * @RETURNS		OPP_DRA7XX_NOM if s == "nom"
 *			OPP_DRA7XX_OD if s == "od"
 *			OPP_DRA7XX_HIGH if s == "high"
 *			OPP_DRA7XX_ID_MAX otherwise
 * @param[in,out]	s: string
 * @DESCRIPTION		convert string to valid OPP ID
 *//*------------------------------------------------------------------------ */
opp_dra7xx_id opp_dra7xx_s2id(char *s)
{
	CHECK_NULL_ARG(s, OPP_DRA7XX_ID_MAX);

	if (strcmp(s, "nom") == 0)
		return OPP_DRA7XX_NOM;
	else if (strcmp(s, "od") == 0)
		return OPP_DRA7XX_OD;
	else if (strcmp(s, "high") == 0)
		return OPP_DRA7XX_HIGH;
	else
		return OPP_DRA7XX_ID_MAX;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm_dra7xx_id2s
 * @BRIEF		convert voltage domain ID into voltage domain name, as
 *			defined in voltdm.h.
 * @RETURNS		Voltage Domain name, as defined in voltdm.h.
 *			NULL in case of invalid voltage domain ID
 * @param[in]		id: voltage domain ID
 * @DESCRIPTION		convert voltage domain ID to voltage domain name.
 *//*------------------------------------------------------------------------ */
const char *voltdm_dra7xx_id2s(voltdm_dra7xx_id id)
{
	const char *s;
	CHECK_ARG_LESS_THAN(id, VDD_DRA7XX_ID_MAX, NULL);

	switch (id) {
	case VDD_DRA7XX_CORE:
		s = VDD_CORE;
		break;
	case VDD_DRA7XX_MPU:
		s = VDD_MPU;
		break;
	case VDD_DRA7XX_IVA:
		s = VDD_IVA;
		break;
	case VDD_DRA7XX_DSPEVE:
		s = VDD_DSPEVE;
		break;
	case VDD_DRA7XX_GPU:
		s = VDD_GPU;
		break;
	case VDD_DRA7XX_RTC:
		s = VDD_RTC;
		break;
	default:
		s = NULL;
	}

	dprintf("%s(%d) = %s\n", __func__, id, s);
	return s;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp_dra7xx_name_get
 * @BRIEF		return OPP name
 * @RETURNS		OPP name on success
 *			NULL in case of error
 * @param[in]		id: valid OPP ID
 * @DESCRIPTION		return OPP name
 *//*------------------------------------------------------------------------ */
const char *opp_dra7xx_name_get(opp_dra7xx_id id)
{
	CHECK_ARG_LESS_THAN(id, OPP_DRA7XX_ID_MAX + 1, NULL);

	return opp_dra7xx_names_table[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vr_dra7xx_vsel2uv
 * @BRIEF		for a given rail, convert SMPS vsel command into voltage
 *			in microvolts.
 * @RETURNS		voltage in microvolts corresponding to SMPS vsel command
 * @param[in]		id: valid voltage rail
 * @param[in]		vsel: SMPS vsel command
 * @DESCRIPTION		for a given rail, convert SMPS vsel command into voltage
 *			in microvolts.
 *//*------------------------------------------------------------------------ */
unsigned long vr_dra7xx_vsel2uv(voltdm_dra7xx_id id, unsigned char vsel)
{
	unsigned long uv = 0;

	CHECK_ARG_LESS_THAN(id, VDD_DRA7XX_ID_MAX, 0);

	dprintf("%s(%s, 0x%X) = %luuV\n", __func__,
		voltdm_dra7xx_name_get(id), vsel, uv);
	/* FIXME */
	/* just to remove "unused parameter" warnings ... */
	vsel = vsel;

	return uv;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vr_dra7xx_vsel2volt
 * @BRIEF		for a given rail, convert SMPS vsel command into voltage
 *			(in VOLTS).
 * @RETURNS		voltage in VOLTS corresponding to SMPS vsel command
 * @param[in]		id: voltage rail
 * @param[in]		vsel: SMPS vsel command
 * @DESCRIPTION		for a given rail, convert SMPS vsel command into voltage
 *			(in VOLTS).
 *//*------------------------------------------------------------------------ */
double vr_dra7xx_vsel2volt(voltdm_dra7xx_id id, unsigned char vsel)
{
	double volt;

	CHECK_ARG_LESS_THAN(id, VDD_DRA7XX_ID_MAX, 0);

	volt = (double) vr_dra7xx_vsel2uv(id, vsel);
	volt /= (double) 1000000.0;

	dprintf("%s(%s, 0x%X) = %lfV\n", __func__,
		voltdm_dra7xx_name_get(id), vsel, volt);

	return volt;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm_dra7xx_por_nominal_voltage_get
 * @BRIEF		return the Plan of Record (POR) nominal voltage
 *			of a given voltage domain for a given OPP.
 * @RETURNS		supply voltage in case of success (>= 0.0)
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 * @param[in]		id: valid voltage domain ID
 * @DESCRIPTION		return the Plan of Record (POR) nominal voltage
 *			of a given voltage domain for a given OPP.
 *//*------------------------------------------------------------------------ */
double voltdm_dra7xx_por_nominal_voltage_get(voltdm_dra7xx_id id, opp_dra7xx_id opp_id)
{
	double volt;

	CHECK_ARG_LESS_THAN(id, VDD_DRA7XX_ID_MAX, (double) OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(id, VDD_DRA7XX_ID_MAX, (double) OMAPCONF_ERR_ARG);

	volt = voltdm_dra7xx_por_nominal_voltages_table[id][opp_id];

	dprintf("%s(%s): %s POR nominal volt=%lfV\n", __func__,
		opp_dra7xx_name_get(opp_id),
		voltdm_dra7xx_name_get(id), volt);

	return volt;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm_dra7xx_voltage_get
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
double voltdm_dra7xx_voltage_get(voltdm_dra7xx_id id)
{
	double volt;

	CHECK_ARG_LESS_THAN(id, VDD_DRA7XX_ID_MAX, (double) OMAPCONF_ERR_ARG);

	switch (id) {
	case VDD_DRA7XX_CORE:
		volt = smps_voltage_get(PMIC_SMPS_CORE);
		break;

	case VDD_DRA7XX_MPU:
		volt = smps_voltage_get(PMIC_SMPS_MPU);
		break;

	case VDD_DRA7XX_IVA:
		/* MM is IVA for DRA7 */
		volt = smps_voltage_get(PMIC_SMPS_MM);
		break;

	case VDD_DRA7XX_DSPEVE:
		volt = smps_voltage_get(PMIC_SMPS_DSPEVE);
		break;

	case VDD_DRA7XX_GPU:
		volt = smps_voltage_get(PMIC_SMPS_GPU);
		break;

	case VDD_DRA7XX_RTC:
		/* VDD_RTC is fixed to be 1.0 and controlled by LDO9 */
		volt = 1.0;
		break;

	default:
		return (double) OMAPCONF_ERR_ARG;
	}

	dprintf("%s(%s): volt=%lfV\n", __func__, voltdm_dra7xx_name_get(id), volt);
	return volt;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm_dra7xx_voltage_set
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
int voltdm_dra7xx_voltage_set(voltdm_dra7xx_id id, unsigned long uv)
{
	CHECK_ARG_LESS_THAN(id, VDD_DRA7XX_ID_MAX, (double) OMAPCONF_ERR_ARG);

	/* Retrieve domain state */
	switch (id) {
	case VDD_DRA7XX_CORE:
		return smps_voltage_set(PMIC_SMPS_CORE, uv);
		break;
	case VDD_DRA7XX_MPU:
		return smps_voltage_set(PMIC_SMPS_MPU, uv);
		break;
	case VDD_DRA7XX_IVA:
		return smps_voltage_set(PMIC_SMPS_MM, uv);
		break;
	case VDD_DRA7XX_DSPEVE:
		return smps_voltage_set(PMIC_SMPS_DSPEVE, uv);
		break;
	case VDD_DRA7XX_GPU:
		return smps_voltage_set(PMIC_SMPS_GPU, uv);
		break;
	case VDD_DRA7XX_RTC:
		return OMAPCONF_ERR_NOT_AVAILABLE;
		break;

	default:
		return OMAPCONF_ERR_ARG;
	}
}
