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
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <cpufreq.h>
#include <voltdm_dra7xx.h>
#include <cm_dra7xx-defs.h>
#include <temperature.h>
#include <voltdomain.h>
#include <opp.h>
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

/* ------------------------------------------------------------------------*//*
 * @FUNCTION		lib_dra7xx_voltage_set_walk
 * @BRIEF		change voltage of a given voltage domain in steps, switching
 *			CPUFreq governor to "userspace" & disabling smart-reflex
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		vdd_id: voltage domain ID
 * @param[in]		volt: new supply voltage (in volt)
 * @param[in]           step: step size to walk down from initial voltage
 * @param[in]           msec: time to wait inbetween steps
 * @param[in]           trans: flag to enable transient to simulate DVFS
 * @DESCRIPTION		change voltage of a given voltage domain in steps, switching
 *			CPUFreq governor to "userspace" & disabling smart-reflex
 *//*------------------------------------------------------------------------ */
int lib_dra7xx_voltage_set_walk(voltdm_dra7xx_id vdd_id, double volt,
				double step, unsigned int msec,
				unsigned int trans)
{
	int ret = -1;

	CHECK_ARG_LESS_THAN(vdd_id, VDD_DRA7XX_ID_MAX, OMAPCONF_ERR_ARG);

	if (!msec)
		msec = 300;

        /* Assume OPPs locked out at this point */
	while (volt > 0) {
		printf("Attempt to set %s supply voltage set to %1.3lfV (vsel = 0x%02X) with step down %1.3lfV waiting %dms between 2 steps.\n\n",
		       voltdm_dra7xx_name_get(vdd_id), volt,
		       smps_uvolt2vsel(vdd_id2smps_id(vdd_id),
				       (unsigned long) (volt * 1000000)),
		       step, msec);
		ret = voltdm_dra7xx_voltage_set(vdd_id,
						(unsigned long) (volt * 1000000));
		if (ret != 0) {
			fprintf(stderr, "Oups, could not change %s voltage to %.3lfV ... (%d)\n\n",
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
		volt -= step;

		if (trans)
			libdra7x_vtrans(vdd_id, msec);
		else
			usleep(1000 * msec);
	}
	return ret;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION            libdra7x_vtrans
 * @BRIEF               do vtrans operations along with vmin search
 * @RETURNS             0 in case of success
 * @param[in]           vdd_id: voltage rail on which vmin operation is performed
 *                      ms: delay between vmin steps
 * @DESCRIPTION         Generate high current transients during vmin test to AVS
 *                      managed domains.  Decent for DualCore J6, Less for J6ECO.
 *//*------------------------------------------------------------------------ */
int libdra7x_vtrans(voltdm_dra7xx_id vdd_id, unsigned int ms)
{
	unsigned int val, val1, val2;
	/* Approx. conversion of delay steps to toggle cycles */
	unsigned int i = (ms*1000)/200;

	if(vdd_id == VDD_DRA7XX_MPU) {
		/* Toggle between lock and bypass */
		while (i > 0) {
			reg_write(&dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_mpu,
				  DPLL_LOCK);
			usleep(100);
			reg_write(&dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_mpu,
				  DPLL_FAST_RELOCK_BYPASS);
			usleep(100);
			i--;
		}
	} else if (vdd_id == VDD_DRA7XX_IVA) {
		/* Set bypass source to SYSCLK */
		val = reg_read(&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_iva);
		reg_write(&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_iva,
			  val ^ (1<<23));

		/* Toggle between lock and bypass - DPLL_IVA */
		/* Toggle between slow and fast clock - DPLL_IVA */
		while (i > 0) {
			reg_write(&dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_iva, DPLL_LOCK);
			usleep(100);
			reg_write(&dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_iva, DPLL_FAST_RELOCK_BYPASS);
			usleep(100);
			i--;
		}
        } else if (vdd_id == VDD_DRA7XX_DSPEVE) {
		/* Set bypass source to SYSCLK */
		val = reg_read(&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_dsp);
		reg_write(&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_dsp,
			  val ^ (1<<23));
		val2 = reg_read(&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_eve);
		reg_write(&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_eve,
			  val2 ^ (1<<23));

		while (i > 0) {
			reg_write(&dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_dsp,
				  DPLL_LOCK);
			reg_write(&dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_eve,
				  DPLL_LOCK);
			usleep(100);
			reg_write(&dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_dsp,
				  DPLL_FAST_RELOCK_BYPASS);
                        reg_write(&dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_eve,
				  DPLL_FAST_RELOCK_BYPASS);
                        usleep(100);
			i--;
		}
        } else if (vdd_id == VDD_DRA7XX_GPU) {
		/* Set bypass source to SYSCLK */
		val = reg_read(&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_gpu);
		reg_write(&dra7xx_ckgen_cm_core_aon_cm_clksel_dpll_gpu,
			  val ^ (1<<23));

		val = reg_read(&dra7xx_ckgen_cm_core_aon_cm_div_h14_dpll_core);
		while (i > 0) {
			reg_write(&dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_gpu,
				  DPLL_LOCK);
			reg_write(&dra7xx_ckgen_cm_core_aon_cm_div_h14_dpll_core,
				  0x3e);
			usleep(100);
			reg_write(&dra7xx_ckgen_cm_core_aon_cm_clkmode_dpll_gpu,
				  DPLL_FAST_RELOCK_BYPASS);
			reg_write(&dra7xx_ckgen_cm_core_aon_cm_div_h14_dpll_core,
				  val);
			usleep(100);
			i--;
		}
	} else if (vdd_id == VDD_DRA7XX_CORE) {
		/* Toggle between slow and fast clock */
		val = reg_read(&dra7xx_ckgen_cm_core_aon_cm_div_h22_dpll_core);
		val1 = reg_read(&dra7xx_ckgen_cm_core_aon_cm_div_h23_dpll_core);
		val2 = reg_read(&dra7xx_ckgen_cm_core_aon_cm_div_h24_dpll_core);
		while (i > 0) {
			reg_write(&dra7xx_ckgen_cm_core_aon_cm_div_h22_dpll_core, 0x3f);
			reg_write(&dra7xx_ckgen_cm_core_aon_cm_div_h23_dpll_core, 0x3f);
			reg_write(&dra7xx_ckgen_cm_core_aon_cm_div_h24_dpll_core, 0x3f);
			usleep(100);
			reg_write(&dra7xx_ckgen_cm_core_aon_cm_div_h22_dpll_core, val);
			reg_write(&dra7xx_ckgen_cm_core_aon_cm_div_h23_dpll_core, val1);
			reg_write(&dra7xx_ckgen_cm_core_aon_cm_div_h24_dpll_core, val2);
			usleep(100);
			i--;
		}
	}
	return 0;
}
