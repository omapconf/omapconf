/*
 * @Component			OMAPCONF
 * @Filename			prcm_am437x.c
 * @Description			OMAPCONF PRCM AM437X Main file
 * @Author			Dave Gerlach <d-gerlach@ti.com>
 * @Date			2016
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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
#include <cm_am437x.h>
#include <cpuinfo.h>
#include <help.h>
#include <lib.h>
#include <module.h>
#include <powerdomain.h>
#include <prcm_am437x.h>
#include <prm_am437x.h>
#include <string.h>

#ifdef PRCM_AM437X_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm_am437x_wkup_dump
 * @BRIEF		dump WKUP PRCM registers and pretty-print it
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump WKUP PRCM registers and pretty-print it
 */
static inline int _prcm_am437x_wkup_dump(FILE *stream)
{
	int ret;

	ret = prm_am437x_dump(stream, PRM_AM437X_PRM_WKUP);
	if (ret != 0)
		return ret;
	return cm_am437x_dump(stream, CM_AM437X_CM_WKUP);
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm_am437x_mpu_dump
 * @BRIEF		dump MPU PRCM registers and pretty-print it
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump MPU PRCM registers and pretty-print it
 */
static inline int _prcm_am437x_mpu_dump(FILE *stream)
{
	int ret;

	ret = prm_am437x_dump(stream, PRM_AM437X_PRM_MPU);
	if (ret != 0)
		return ret;
	return cm_am437x_dump(stream, CM_AM437X_CM_MPU);
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm_am437x_gfx_dump
 * @BRIEF		dump GFX PRCM registers and pretty-print it
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump GFX PRCM registers and pretty-print it
 */
static inline int _prcm_am437x_gfx_dump(FILE *stream)
{
	int ret;

	ret = prm_am437x_dump(stream, PRM_AM437X_PRM_GFX);
	if (ret != 0)
		return ret;
	return cm_am437x_dump(stream, CM_AM437X_CM_GFX);
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm_am437x_per_dump
 * @BRIEF		dump PER PRCM registers and pretty-print it
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump PER PRCM registers and pretty-print it
 */
static inline int _prcm_am437x_per_dump(FILE *stream)
{
	int ret;

	ret = prm_am437x_dump(stream, PRM_AM437X_PRM_PER);
	if (ret != 0)
		return ret;
	return cm_am437x_dump(stream, CM_AM437X_CM_PER);
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm_am437x_rtc_dump
 * @BRIEF		dump RTC PRCM registers and pretty-print it
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump RTC PRCM registers and pretty-print it
 */
static inline int _prcm_am437x_rtc_dump(FILE *stream)
{
	int ret;

	ret = prm_am437x_dump(stream, PRM_AM437X_PRM_RTC);
	if (ret != 0)
		return ret;
	return cm_am437x_dump(stream, CM_AM437X_CM_RTC);
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm_am437x_efuse_dump
 * @BRIEF		dump efuse PRCM registers and pretty-print it
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump MPU PRCM registers and pretty-print it
 *//*------------------------------------------------------------------------ */
static inline int _prcm_am437x_efuse_dump(FILE *stream)
{
	int ret;

	ret = prm_am437x_dump(stream, PRM_AM437X_PRM_CEFUSE);
	if (ret != 0)
		return ret;
	return cm_am437x_dump(stream, CM_AM437X_CM_CEFUSE);
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm_am437x_dev_dump
 * @BRIEF		dump DEVICE PRCM registers and pretty-print it
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump DEVICE PRCM registers and pretty-print it
 *//*------------------------------------------------------------------------ */
static inline int _prcm_am437x_dev_dump(FILE *stream)
{
	int ret;

	ret = prm_am437x_dump(stream, PRM_AM437X_PRM_DEVICE);
	if (ret != 0)
		return ret;
	return cm_am437x_dump(stream, CM_AM437X_CM_DEVICE);
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm_am437x_irq_dump
 * @BRIEF		dump PRCM IRQ PRCM registers and pretty-print it
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump PRM IRQ PRCM registers and pretty-print it.
 *			NOTE: No corresponding CM module
 */
static inline int _prcm_am437x_irq_dump(FILE *stream)
{
	return prm_am437x_dump(stream, PRM_AM437X_PRM_IRQ);
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm_am437x_dpll_dump
 * @BRIEF		dump PRCM IRQ PRCM registers and pretty-print it
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump CM DPLL PRCM registers and pretty-print it.
 *			NOTE: No corresponding PRM module
 */
static inline int _prcm_am437x_dpll_dump(FILE *stream)
{
	return cm_am437x_dump(stream, CM_AM437X_CM_DPLL);
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		prcm_am437x_dump
 * @BRIEF		dump (formated in table) PRCM registers related to power
 *			domain provided in string s.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		s: power domain
 * @DESCRIPTION		dump (formated in table) PRCM registers related to power
 *			domain provided in string s.
 *//*------------------------------------------------------------------------ */
int prcm_am437x_dump(char *s)
{
	int ret = 0;

	if ((s == NULL) || (strcmp(s, "all") == 0)) {
		/* ALL */
		ret = _prcm_am437x_per_dump(stdout);
		ret |= _prcm_am437x_wkup_dump(stdout);
		ret |= _prcm_am437x_mpu_dump(stdout);
		ret |= _prcm_am437x_dev_dump(stdout);
		ret |= _prcm_am437x_rtc_dump(stdout);
		ret |= _prcm_am437x_gfx_dump(stdout);
		ret |= _prcm_am437x_efuse_dump(stdout);
		ret |= _prcm_am437x_irq_dump(stdout);
		ret |= _prcm_am437x_dpll_dump(stdout);
		return ret;
	} else if (strcmp(s, "wkup") == 0) {
		return _prcm_am437x_wkup_dump(stdout);
	} else if (strcmp(s, "mpu") == 0) {
		return _prcm_am437x_mpu_dump(stdout);
	} else if (strcmp(s, "gfx") == 0) {
		return _prcm_am437x_gfx_dump(stdout);
	} else if (strcmp(s, "per") == 0) {
		return _prcm_am437x_per_dump(stdout);
	} else if (strcmp(s, "rtc") == 0) {
		return _prcm_am437x_rtc_dump(stdout);
	} else if (strcmp(s, "efuse") == 0) {
		return _prcm_am437x_efuse_dump(stdout);
	} else if (strcmp(s, "dev") == 0) {
		return _prcm_am437x_dev_dump(stdout);
	} else if (strcmp(s, "irq") == 0) {
		return _prcm_am437x_irq_dump(stdout);
	} else if (strcmp(s, "dpll") == 0) {
		return _prcm_am437x_dpll_dump(stdout);
	} else {
		return err_arg_msg_show(HELP_PRCM);
	}
}
