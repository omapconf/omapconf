/*
 *
 * @Component			OMAPCONF
 * @Filename			clockdomain.c
 * @Description			Clock Domain Generic Definitions & Functions
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


#include <clockdomain.h>
#include <clkdm44xx.h>
#include <clkdm54xx.h>
#include <clkdm.h>
#include <lib.h>
#include <stdlib.h>
#include <string.h>
#include <cpuinfo.h>


/* #define CLOCKDM_DEBUG */
#ifdef CLOCKDM_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static int _clockdm_info_get(const char *clockdm, clockdm_info *data);


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clockdm_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void clockdm_init(void)
{
	#ifdef CLOCKDM_DEBUG
	int i, count;
	const genlist *clkdm_list;
	clockdm_info clkdm;
	#endif

	if (cpu_is_omap44xx()) {
		clkdm44xx_init();
	} else if (cpu_is_omap54xx()) {
		clkdm54xx_init();
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
	}

	#ifdef CLOCKDM_DEBUG
	clkdm_list = clockdm_list_get();
	count = genlist_getcount((genlist *) clkdm_list);
	printf("Clock Domain List:\n");
	for (i = 0; i < count; i++) {
		genlist_get((genlist *) clkdm_list, i, (clockdm_info *) &clkdm);
		printf(" %s:\n", clkdm.name);
		printf("  ID:%d (%s)\n", clkdm.id,
			clkdm54xx_name_get(clkdm.id));
		printf("  PwrDM: %s\n", clkdm.powerdm);
		printf("  VoltDM: %s\n", clkdm.voltdm);
		printf("  CLKSTCTRL REG: %s\n", (clkdm.clkstctrl)->name);
		printf("  Properties: %d\n", clkdm.properties);
		printf("\n\n");
	}
	printf("Clock Domain count: %d\n\n", count);
	#endif
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clockdm_deinit
 * @BRIEF		free dynamically allocated internal data.
 * @DESCRIPTION		free dynamically allocated internal data.
 *			MUST BE CALLED AT END OF EXECUTION.
 *//*------------------------------------------------------------------------ */
void clockdm_deinit(void)
{
	if (cpu_is_omap44xx()) {
		clkdm44xx_deinit();
	} else if (cpu_is_omap54xx()) {
		clkdm54xx_deinit();
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clockdm_list_get
 * @BRIEF		return the list of clock domains
 * @RETURNS		list of clock domains in case of success
 *			NULL in case of error
 * @DESCRIPTION		return the list of clock domains
 *//*------------------------------------------------------------------------ */
const genlist *clockdm_list_get(void)
{
	if (cpu_is_omap44xx()) {
		return clkdm44xx_list_get();
	} else if (cpu_is_omap54xx()) {
		return clkdm54xx_list_get();
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		return NULL;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clockdm_count_get
 * @BRIEF		return the number of clock domains
 * @RETURNS		number of clock domains (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @DESCRIPTION		return the number of clock domains
 *//*------------------------------------------------------------------------ */
int clockdm_count_get(void)
{
	if (cpu_is_omap44xx()) {
		return clkdm44xx_count_get();
	} else if (cpu_is_omap54xx()) {
		return clkdm54xx_count_get();
	} else {
		fprintf(stderr,
			"omapconf: %s(): cpu not supported!!!\n", __func__);
		return OMAPCONF_ERR_CPU;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_clockdm_info_get
 * @BRIEF		return the saved informations of a given clock domain.
 * @RETURNS		0 in case of success
 *			-1 in case of error
 * @param[in]		clockdm: clock domain name
 * @param[in,out]	data:clock domain details
 * @DESCRIPTION		return the saved informations of a given clock domain.
 *//*------------------------------------------------------------------------ */
static int _clockdm_info_get(const char *clockdm, clockdm_info *data)
{
	const genlist *clkdm_list;
	int i, count;

	CHECK_NULL_ARG(clockdm, -1);
	CHECK_NULL_ARG(data, -1);

	clkdm_list = clockdm_list_get();
	count = genlist_getcount((genlist *) clkdm_list);
	for (i = 0; i < count; i++) {
		genlist_get((genlist *) clkdm_list, i, (void *) data);
		if (strcmp(data->name, clockdm) == 0) {
			dprintf("%s(%s): found.\n", __func__, clockdm);
			return 0;
		}
	}

	dprintf("%s(%s): not found!\n", __func__, clockdm);
	return -1;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clockdm_id_get
 * @BRIEF		return the unique ID of a given clock domain.
 * @RETURNS		>= 0 clock domain ID
 *			-1 in case of error
 * @param[in]		clockdm: clock domain name
 * @DESCRIPTION		return the unique ID of a given clock domain.
 *//*------------------------------------------------------------------------ */
int clockdm_id_get(const char *clockdm)
{
	int id;
	clockdm_info data;

	CHECK_NULL_ARG(clockdm, -1);

	id = _clockdm_info_get(clockdm, &data);
	if (id == 0)
		id = data.id;

	dprintf("%s(%s) = %d\n", __func__, clockdm, id);
	return id;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clockdm_powerdm_get
 * @BRIEF		return the power domain name a clock domain is part of
 * @RETURNS		power domain name on success.
 *			NULL in case of error
 * @param[in]		clockdm: clock domain name
 * @DESCRIPTION		return the power domain name a clock domain is part of
 *//*------------------------------------------------------------------------ */
const char *clockdm_powerdm_get(const char *clockdm)
{
	int ret;
	clockdm_info data;

	CHECK_NULL_ARG(clockdm, NULL);

	ret = _clockdm_info_get(clockdm, &data);
	if (ret != 0) {
		dprintf("%s(%s): could not retrieve clockdm_info struct!\n",
			__func__, clockdm);
		return NULL;
	}

	dprintf("%s(%s) = %s\n", __func__, clockdm, data.powerdm);
	return data.powerdm;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clockdm_voltdm_get
 * @BRIEF		return the voltage domain name a clock domain is part of
 * @RETURNS		voltage domain name on success.
 *			NULL in case of error (not found)
 * @param[in]		clockdm: clock domain name
 * @DESCRIPTION		return the voltage domain name a clock domain is part of
 *//*------------------------------------------------------------------------ */
const char *clockdm_voltdm_get(const char *clockdm)
{
	int ret;
	clockdm_info data;

	CHECK_NULL_ARG(clockdm, NULL);

	ret = _clockdm_info_get(clockdm, &data);
	if (ret != 0) {
		dprintf("%s(%s): could not retrieve clockdm_info struct!\n",
			__func__, clockdm);
		return NULL;
	}

	dprintf("%s(%s) = %s\n", __func__, clockdm, data.voltdm);
	return data.voltdm;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clockdm_clkstctrl_get
 * @BRIEF		return the CLKSTCTRL register of a given clock domain
 * @RETURNS		CLKSTCTRL register on success
 *			NULL in case of error (not found)
 * @param[in]		clockdm: clock domain name
 * @DESCRIPTION		return the CLKSTCTRL register of a given clock domain
 *//*------------------------------------------------------------------------ */
reg *clockdm_clkstctrl_get(const char *clockdm)
{
	int ret;
	clockdm_info data;

	CHECK_NULL_ARG(clockdm, NULL);

	ret = _clockdm_info_get(clockdm, &data);
	if (ret != 0) {
		dprintf("%s(%s): could not retrieve clockdm_info struct!\n",
			__func__, clockdm);
		return NULL;
	}

	if (data.clkstctrl != NULL) {
		dprintf("%s(%s): CM_CLKSTCTRL=%s\n", __func__,
			clockdm, reg_name_get(data.clkstctrl));
		return data.clkstctrl;
	} else {
		dprintf("%s(%s): CM_CLKSTCTRL==NULL\n", __func__, clockdm);
		return NULL;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clockdm_status_get
 * @BRIEF		return the status of a given clock domain
 * @RETURNS		clock domain status on success
 *			CLKDM_STATUS_MAX in case of error
 * @param[in]		clockdm: clock domain name
 * @DESCRIPTION		return the status of a given clock domain
 *//*------------------------------------------------------------------------ */
clkdm_status clockdm_status_get(const char *clockdm)
{
	reg *clkstctrl;
	clkdm_status st;

	CHECK_NULL_ARG(clockdm, CLKDM_STATUS_MAX);

	clkstctrl = clockdm_clkstctrl_get(clockdm);
	if (clkstctrl != NULL) {
		st = clkdm_status_get(clkstctrl);
		dprintf("%s(%s): CM_CLKSTCTRL=%s status=%s\n", __func__,
			clockdm, reg_name_get(clkstctrl),
			clkdm_status_name_get(st));
		return st;
	} else {
		dprintf("%s(%s): CM_CLKSTCTRL==NULL\n", __func__, clockdm);
		return CLKDM_STATUS_MAX;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clockdm_ctrl_mode_get
 * @BRIEF		return the control mode of a given clock domain
 * @RETURNS		control mode on success
 *			CLKM_CTRL_MODE_MAX in case of error
 * @param[in]		clockdm: clock domain name
 * @DESCRIPTION		return the control mode of a given clock domain
 *//*------------------------------------------------------------------------ */
clkdm_ctrl_mode clockdm_ctrl_mode_get(const char *clockdm)
{
	reg *clkstctrl;
	clkdm_ctrl_mode mode;

	CHECK_NULL_ARG(clockdm, CLKM_CTRL_MODE_MAX);

	clkstctrl = clockdm_clkstctrl_get(clockdm);
	if (clkstctrl != NULL) {
		mode = clkdm_ctrl_mode_get(clkstctrl);
		dprintf("%s(%s): CM_CLKSTCTRL=%s ctrl mode=%s\n", __func__,
			clockdm, reg_name_get(clkstctrl),
			clkdm_ctrl_mode_name_get(mode));
		return mode;
	} else {
		dprintf("%s(%s): CM_CLKSTCTRL==NULL\n", __func__, clockdm);
		return CLKM_CTRL_MODE_MAX;
	}
}
