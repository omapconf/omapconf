/*
 *
 * @Component			OMAPCONF
 * @Filename			prcm44xx.c
 * @Description			OMAPCONF PRCM OMAP4 Main file
 * @Author			Patrick Titiano (p-titiano@ti.com)
 * @Date			2010
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
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


#include <prcm44xx.h>
#include <help.h>
#include <lib.h>
#include <cpuinfo.h>
#include <string.h>
#include <mpu44xx.h>
#include <mpuss44xx.h>
#include <core44xx.h>
#include <per44xx.h>
#include <dsp44xx.h>
#include <dss44xx.h>
#include <cam44xx.h>
#include <gfx44xx.h>
#include <ivahd44xx.h>
#include <abe44xx.h>
#include <wkup44xx.h>
#include <l3init44xx.h>
#include <alwon44xx.h>
#include <emu44xx.h>
#include <dep44xx.h>
#include <wkdep44xx.h>
#include <abb44xx.h>


/* #define PRCM44XX_DEBUG */
#ifdef PRCM44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		prcm44xx_dump
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
int prcm44xx_dump(char *s)
{
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	if (s == NULL)
		return err_arg_missing_msg_show(HELP_PRCM);

	if (strcmp(s, "mpu") == 0) {
		return mpu44xx_dump();
	} else if (strcmp(s, "core") == 0) {
		return core44xx_dump();
	} else if (strcmp(s, "dsp") == 0) {
		return dsp44xx_dump();
	} else if (strcmp(s, "dss") == 0) {
		return dss44xx_dump();
	} else if (strcmp(s, "cam") == 0) {
		return cam44xx_dump();
	} else if (strcmp(s, "gfx") == 0) {
		return gfx44xx_dump();
	} else if (strcmp(s, "ivahd") == 0) {
		return ivahd44xx_dump();
	} else if (strcmp(s, "per") == 0) {
		return per44xx_dump();
	} else if (strcmp(s, "abe") == 0) {
		return abe44xx_dump();
	} else if (strcmp(s, "wkup") == 0) {
		return wkup44xx_dump();
	} else if (strcmp(s, "l3init") == 0) {
		return l3init44xx_dump();
	} else if (strcmp(s, "alwon") == 0) {
		return alwon44xx_dump();
	} else if (strcmp(s, "emu") == 0) {
		return emu44xx_dump();
	} else if (strcmp(s, "all") == 0) {
		/* Dump all PRCM registers */
		ret = wkup44xx_dump();
		ret |= l3init44xx_dump();
		ret |= alwon44xx_dump();
		ret |= emu44xx_dump();
		ret |= mpu44xx_dump();
		ret |= core44xx_dump();
		ret |= dsp44xx_dump();
		ret |= dss44xx_dump();
		ret |= cam44xx_dump();
		ret |= gfx44xx_dump();
		ret |= ivahd44xx_dump();
		ret |= per44xx_dump();
		ret |= abe44xx_dump();
		return ret;
	} else if (strcmp(s, "statdep") == 0) {
		return statdep44xx_dump();
	} else if (strcmp(s, "wkdep") == 0) {
		return wkdep44xx_dump();
	} else if (strcmp(s, "abb") == 0) {
		return abb44xx_dump();
	} else {
		return err_arg_msg_show(HELP_PRCM);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		prcm44xx_config_show
 * @BRIEF		print PRCM configuration and status of item
 *			provided in string s.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		s: PRCM item
 * @DESCRIPTION		print PRCM configuration and status of item
 *			provided in string s.
 *//*------------------------------------------------------------------------ */
int prcm44xx_config_show(char *s)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	if (s == NULL)
		return err_arg_missing_msg_show(HELP_PRCM);

	if (strcmp(s, "mpu") == 0)
		return mpu44xx_config_show(stdout);
	else if (strcmp(s, "core") == 0)
		return core44xx_config_show(stdout);
	else if (strcmp(s, "dsp") == 0)
		return dsp44xx_config_show(stdout);
	else if (strcmp(s, "dss") == 0)
		return dss44xx_config_show(stdout);
	else if (strcmp(s, "cam") == 0)
		return cam44xx_config_show(stdout);
	else if (strcmp(s, "gfx") == 0)
		return gfx44xx_config_show(stdout);
	else if (strcmp(s, "ivahd") == 0)
		return ivahd44xx_config_show(stdout);
	else if (strcmp(s, "per") == 0)
		return per44xx_config_show(stdout);
	else if (strcmp(s, "abe") == 0)
		return abe44xx_config_show(stdout);
	else if (strcmp(s, "wkup") == 0)
		return wkup44xx_config_show(stdout);
	else if (strcmp(s, "l3init") == 0)
		return l3init44xx_config_show(stdout);
	else if (strcmp(s, "alwon") == 0)
		return alwon44xx_config_show(stdout);
	else if (strcmp(s, "emu") == 0)
		return emu44xx_config_show(stdout);
	else if (strcmp(s, "irq") == 0)
		return mpu44xx_irq_show(stdout);
	else if (strcmp(s, "statdep") == 0)
		return statdep44xx_show();
	else if (strcmp(s, "wkdep") == 0)
		return wkdep44xx_config_show();
	else if (strcmp(s, "abb") == 0)
		return abb44xx_config_show();
	else
		return err_arg_msg_show(HELP_PRCM);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		prcm44xx_dep_show
 * @BRIEF		print PRCM clock domain dependency onfiguration.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		s: clock domain
 * @DESCRIPTION		print PRCM clock domain dependency onfiguration.
 *//*------------------------------------------------------------------------ */
int prcm44xx_dep_show(char *s)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	if (s == NULL)
		return err_arg_missing_msg_show(HELP_PRCM);

	if (strcmp(s, "mpu") == 0)
		return mpu44xx_dependency_show(stdout);
	else if (strcmp(s, "core") == 0)
		return core44xx_dependency_show(stdout);
	else if (strcmp(s, "dsp") == 0)
		return dsp44xx_dependency_show(stdout);
	else if (strcmp(s, "dss") == 0)
		return dss44xx_dependency_show(stdout);
	else if (strcmp(s, "cam") == 0)
		return cam44xx_dependency_show(stdout);
	else if (strcmp(s, "gfx") == 0)
		return gfx44xx_dependency_show(stdout);
	else if (strcmp(s, "ivahd") == 0)
		return ivahd44xx_dependency_show(stdout);
	else if (strcmp(s, "per") == 0)
		return per44xx_dependency_show(stdout);
	else if (strcmp(s, "l3init") == 0)
		return l3init44xx_dependency_show(stdout);
	else if (strcmp(s, "emu") == 0)
		return emu44xx_dependency_show(stdout);
	else
		return err_arg_msg_show(HELP_PRCM);
}
