/*
 *
 * @Component			OMAPCONF
 * @Filename			voltdm_am335x.c
 * @Description			AM335X Voltage Domain Definitions & APIs
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


#include <autoadjust_table.h>
#include <clock_am335x.h>
#include <cpuinfo.h>
#include <dpll_am335x.h>
#include <opp.h>
#include <pmic.h>
#include <prm_am335x-defs.h>
#include <pwrdm.h>
#include <reg.h>
#include <voltdm_am335x.h>
#include <voltdomain.h>


#ifdef VOLTDM_AM335X_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static const char
	voltdm_am335x_names_table[VDD_AM335X_ID_MAX][VOLTDM_MAX_NAME_LENGTH] = {
	[VDD_AM335X_CORE] = "VDD_CORE",
	[VDD_AM335X_MPU] = "VDD_MPU",
	[VDD_AM335X_RTC] = "VDD_RTC"};


static unsigned short voltdm_am335x_init_done;
genlist voltdm_am335x_list;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm_am335x_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void voltdm_am335x_init(void)
{
	voltdm_info voltdm;

	if (voltdm_am335x_init_done)
		return;

	genlist_init(&voltdm_am335x_list);

	voltdm.name = VDD_CORE;
	voltdm.id = (int) VDD_AM335X_CORE;
	voltdm.voltst = NULL;
	genlist_addtail(
		&voltdm_am335x_list, (void *) &voltdm, sizeof(voltdm_info));

	voltdm.name = VDD_MPU;
	voltdm.id = (int) VDD_AM335X_MPU;
	voltdm.voltst = NULL;
	genlist_addtail(
		&voltdm_am335x_list, (void *) &voltdm, sizeof(voltdm_info));

	voltdm.name = VDD_RTC;
	voltdm.id = (int) VDD_AM335X_RTC;
	voltdm.voltst = NULL;
	genlist_addtail(
		&voltdm_am335x_list, (void *) &voltdm, sizeof(voltdm_info));

	voltdm_am335x_init_done = 1;
	dprintf("%s(): init done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm_am335x_deinit
 * @BRIEF		free dynamically allocated internal data.
 * @DESCRIPTION		free dynamically allocated internal data.
 *			MUST BE CALLED AT END OF EXECUTION.
 *//*------------------------------------------------------------------------ */
void voltdm_am335x_deinit(void)
{
	if (voltdm_am335x_init_done) {
		genlist_free(&voltdm_am335x_list);
		voltdm_am335x_init_done = 0;
	}
	dprintf("%s(): deinit done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm_am335x_list_get
 * @BRIEF		return the list of voltage domains
 * @RETURNS		list of voltage domains in case of success
 *			NULL in case of error
 * @DESCRIPTION		return the list of voltage domains
 *//*------------------------------------------------------------------------ */
const genlist *voltdm_am335x_list_get(void)
{
	voltdm_am335x_init();

	return (const genlist *) &voltdm_am335x_list;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm_am335x_count_get
 * @BRIEF		return the number of voltage domains
 * @RETURNS		number of voltage domains (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @DESCRIPTION		return the number of voltage domains
 *//*------------------------------------------------------------------------ */
int voltdm_am335x_count_get(void)
{
	int count;

	voltdm_am335x_init();

	count = genlist_getcount(&voltdm_am335x_list);

	dprintf("%s() = %d\n", __func__, count);
	return count;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm_am335x_name_get
 * @BRIEF		return voltage domain name
 * @RETURNS		voltage domain name on success
 *			NULL in case of error
 * @param[in]		id: valid voltage domain ID
 * @DESCRIPTION		return voltage domain name
 *//*------------------------------------------------------------------------ */
const char *voltdm_am335x_name_get(voltdm_am335x_id id)
{
	CHECK_ARG_LESS_THAN(id, VDD_AM335X_ID_MAX, NULL);

	return voltdm_am335x_names_table[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm_am335x_id2s
 * @BRIEF		convert voltage domain ID into voltage domain name, as
 *			defined in voltdm.h.
 * @RETURNS		Voltage Domain name, as defined in voltdm.h.
 *			NULL in case of invalid voltage domain ID
 * @param[in]		id: voltage domain ID
 * @DESCRIPTION		convert voltage domain ID to voltage domain name.
 *//*------------------------------------------------------------------------ */
const char *voltdm_am335x_id2s(voltdm_am335x_id id)
{
	const char *s;
	CHECK_ARG_LESS_THAN(id, VDD_AM335X_ID_MAX, NULL);

	switch (id) {
	case VDD_AM335X_CORE:
		s = VDD_CORE;
		break;
	case VDD_AM335X_MPU:
		s = VDD_MPU;
		break;
	case VDD_AM335X_RTC:
		s = VDD_RTC;
		break;
	default:
		s = NULL;
	}

	dprintf("%s(%d) = %s\n", __func__, id, s);
	return s;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltdm_am335x_voltage_get
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
double voltdm_am335x_voltage_get(voltdm_am335x_id id)
{
	double volt;

	CHECK_ARG_LESS_THAN(id, VDD_AM335X_ID_MAX, (double) OMAPCONF_ERR_ARG);

	switch (id) {
	case VDD_AM335X_CORE:
		volt = smps_voltage_get(PMIC_SMPS_CORE);
		break;

	case VDD_AM335X_MPU:
		volt = smps_voltage_get(PMIC_SMPS_MPU);
		break;

	case VDD_AM335X_RTC:
		volt = smps_voltage_get(PMIC_SMPS_ID_MAX);
		break;

	default:
		return (double) OMAPCONF_ERR_ARG;
	}

	dprintf("%s(%s): volt=%lfV\n", __func__, voltdm_am335x_name_get(id), volt);
	return volt;
}
