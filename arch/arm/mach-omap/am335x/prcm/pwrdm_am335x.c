/*
 *
 * @Component			OMAPCONF
 * @Filename			pwrdm_am335x.c
 * @Description			AM335X Power Domain Definitions & APIs
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
#include <lib.h>
#include <prm_am335x.h>
#include <pwrdm.h>
#include <pwrdm_am335x.h>
#include <stdio.h>
#include <string.h>
#include <voltdomain.h>


/* #define PWRDM_AM335X_DEBUG */
#ifdef PWRDM_AM335X_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static unsigned short pwrdm_am335x_init_done = 0;
genlist pwrdm_am335x_list;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm_am335x_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void pwrdm_am335x_init(void)
{
	powerdm_info pwrdm;

	if (pwrdm_am335x_init_done)
		return;

	genlist_init(&pwrdm_am335x_list);

	pwrdm.name = PWRDM_WKUP;
	pwrdm.id = (int) PWRDM_AM335X_WKUP;
	pwrdm.voltdm = VDD_CORE;
	pwrdm.pwrstctrl = &am335x_pm_wkup_pwrstctrl;
	pwrdm.pwrstst = &am335x_pm_wkup_pwrstst;
	pwrdm.properties = 0; /* TBD */
	genlist_addtail(&pwrdm_am335x_list, (void *) &pwrdm, sizeof(powerdm_info));

	pwrdm.name = PWRDM_MPU;
	pwrdm.id = (int) PWRDM_AM335X_MPU;
	pwrdm.voltdm = VDD_MPU;
	pwrdm.pwrstctrl = &am335x_pm_mpu_pwrstctrl;
	pwrdm.pwrstst = &am335x_pm_mpu_pwrstst;
	pwrdm.properties = 0; /* TBD */
	genlist_addtail(&pwrdm_am335x_list, (void *) &pwrdm, sizeof(powerdm_info));

	pwrdm.name = PWRDM_GFX;
	pwrdm.id = (int) PWRDM_AM335X_GFX;
	pwrdm.voltdm = VDD_CORE;
	pwrdm.pwrstctrl = &am335x_pm_gfx_pwrstctrl;
	pwrdm.pwrstst = &am335x_pm_gfx_pwrstst;
	pwrdm.properties = 0; /* TBD */
	genlist_addtail(&pwrdm_am335x_list, (void *) &pwrdm, sizeof(powerdm_info));

	pwrdm.name = PWRDM_PER;
	pwrdm.id = (int) PWRDM_AM335X_PER;
	pwrdm.voltdm = VDD_CORE;
	pwrdm.pwrstctrl = &am335x_pm_per_pwrstctrl;
	pwrdm.pwrstst = &am335x_pm_per_pwrstst;
	pwrdm.properties = 0; /* TBD */
	genlist_addtail(&pwrdm_am335x_list, (void *) &pwrdm, sizeof(powerdm_info));

	pwrdm.name = PWRDM_RTC;
	pwrdm.id = (int) PWRDM_AM335X_RTC;
	pwrdm.voltdm = VDD_RTC;
	pwrdm.pwrstctrl = &am335x_pm_rtc_pwrstctrl;
	pwrdm.pwrstst = &am335x_pm_rtc_pwrstst;
	pwrdm.properties = 0; /* TBD */
	genlist_addtail(&pwrdm_am335x_list, (void *) &pwrdm, sizeof(powerdm_info));

	pwrdm.name = PWRDM_EFUSE;
	pwrdm.id = (int) PWRDM_AM335X_EFUSE;
	pwrdm.voltdm = VDD_CORE;
	pwrdm.pwrstctrl = &am335x_pm_cefuse_pwrstctrl;
	pwrdm.pwrstst = &am335x_pm_cefuse_pwrstst;
	pwrdm.properties = 0; /* TBD */
	genlist_addtail(&pwrdm_am335x_list, (void *) &pwrdm, sizeof(powerdm_info));

	pwrdm_am335x_init_done = 1;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm_am335x_deinit
 * @BRIEF		free dynamically allocated internal data.
 * @DESCRIPTION		free dynamically allocated internal data.
 *			MUST BE CALLED AT END OF EXECUTION.
 *//*------------------------------------------------------------------------ */
void pwrdm_am335x_deinit(void)
{
	if (pwrdm_am335x_init_done) {
		genlist_free(&pwrdm_am335x_list);
		pwrdm_am335x_init_done = 0;

	}
	dprintf("%s(): deinit done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm_am335x_list_get
 * @BRIEF		return the list of power domains
 * @RETURNS		list of power domains in case of success
 *			NULL in case of error
 * @DESCRIPTION		return the list of power domains
 *//*------------------------------------------------------------------------ */
const genlist *pwrdm_am335x_list_get(void)
{
	pwrdm_am335x_init();

	return (const genlist *) &pwrdm_am335x_list;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm_am335x_count_get
 * @BRIEF		return the number of power domains
 * @RETURNS		number of power domains (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @DESCRIPTION		return the number of power domains
 *//*------------------------------------------------------------------------ */
int pwrdm_am335x_count_get(void)
{
	int count;

	pwrdm_am335x_init();

	count = genlist_getcount(&pwrdm_am335x_list);

	dprintf("%s() = %d\n", __func__, count);
	return count;
}
