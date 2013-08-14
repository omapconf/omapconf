/*
 *
 * @Component			OMAPCONF
 * @Filename			lib_dra7xx.c
 * @Description			OMAPCONF DRA7 General Purpose Library
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


#include <lib_dra7xx.h>
#include <lib.h>
#include <stdlib.h>
#include <cpufreq.h>
#include <voltdm_dra7xx.h>
#include <pmic.h>


/* #define LIB_DRA7XX_DEBUG */
#ifdef LIB_DRA7XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		lib_dra7xx_voltage_set
 * @BRIEF		change voltage of a given voltage domain, switching
 *			CPUFreq governor to "userspace" & disabling smart-reflex
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		vdd_id: voltage domain ID
 * @param[in]		volt: new supply voltage (in volt)
 * @DESCRIPTION		change voltage of a given voltage domain, switching
 *			CPUFreq governor to "userspace" & disabling smart-reflex
 *//*------------------------------------------------------------------------ */
int lib_dra7xx_voltage_set(voltdm_dra7xx_id vdd_id, double volt)
{
	int ret, ret_cpufreq;
	char prev_gov[CPUFREQ_GOV_MAX_NAME_LENGTH];
	char prev_gov2[CPUFREQ_GOV_MAX_NAME_LENGTH];

	CHECK_ARG_LESS_THAN(vdd_id, VDD_DRA7XX_ID_MAX, OMAPCONF_ERR_ARG);

	/*
	 * Switch governor to 'userspace' otherwise voltage change will be
	 * overriden in case of OPP change.
	 */
	printf("Warning: switching CPUFreq governor to 'userspace', otherwise "
		"voltage change will be overriden...\n");
	ret_cpufreq = cpufreq_scaling_governor_set("userspace", prev_gov);
	if (ret_cpufreq < 0)
		printf("Warning: failed to switch governor. Voltage will be "
			"overriden in case of OPP change.\n");
	else
		printf("CPUFreq governor switched to 'userspace'.\n");

	ret = voltdm_dra7xx_voltage_set(vdd_id,
		(unsigned long) (volt * 1000000));
	if (ret != 0) {
		fprintf(stderr, "Oups, could not change %s voltage to "
			"%.3lfV ... (%d)\n\n",
			voltdm_dra7xx_name_get(vdd_id), volt, ret);
	} else {
		printf("%s supply voltage set to %1.3lfV (vsel = 0x%02X).\n\n",
			voltdm_dra7xx_name_get(vdd_id), volt,
			smps_uvolt2vsel(vdd_id2smps_id(vdd_id),
			(unsigned long) (volt * 1000000)));
		printf("Warning:\n"
			"  - Do not re-enable %s smartreflex or new voltage "
			"will be overriden.\n"
			"  - Do not change OPP (or use CPUFREQ) or new voltage"
			" will be overriden.\n\n", voltdm_dra7xx_name_get(vdd_id));
	}

	/* Restore CPUFreq governor */
	cpufreq_scaling_governor_set(prev_gov, prev_gov2);

	return ret;
}
