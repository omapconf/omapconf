/*
 *
 * @Component			OMAPCONF
 * @Filename			prcm54xx.c
 * @Description			OMAPCONF PRCM OMAP5 Main file
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


#include <prcm54xx.h>
#include <help.h>
#include <lib.h>
#include <string.h>
#include <cpuinfo.h>
#include <prm54xx.h>
#include <cm54xx.h>
#include <dss54xx.h>
#include <emu54xx.h>
#include <wkupaon54xx.h>
#include <cam54xx.h>
#include <dsp54xx.h>
#include <prmdevice54xx.h>
#include <ckgen54xx.h>
#include <instr54xx.h>
#include <abe54xx.h>
#include <gpu54xx.h>
#include <coreaon54xx.h>
#include <iva54xx.h>
#include <mpu54xx.h>
#include <l3init54xx.h>
#include <core54xx.h>
#include <l4per54xx.h>
#include <pwrdm54xx.h>
#include <clkdm54xx.h>
#include <module54xx.h>
#include <abb54xx.h>
#include <clkdm_dependency54xx.h>
#include <powerdomain.h>
#include <clockdomain.h>
#include <module.h>


/* #define PRCM54XX_DEBUG */
#ifdef PRCM54XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


typedef enum {
	PRCM54XX_IDX_EMU,
	PRCM54XX_IDX_WKUPAON,
	PRCM54XX_IDX_COREAON,
	PRCM54XX_IDX_CAM,
	PRCM54XX_IDX_CORE,
	PRCM54XX_IDX_DEV,
	PRCM54XX_IDX_CKGEN,
	PRCM54XX_IDX_INSTR,
	PRCM54XX_IDX_DSS,
	PRCM54XX_IDX_L3INIT,
	PRCM54XX_IDX_L4PER,
	PRCM54XX_IDX_ABE,
	PRCM54XX_IDX_DSP,
	PRCM54XX_IDX_GPU,
	PRCM54XX_IDX_IVA,
	PRCM54XX_IDX_MPU,
	PRCM54XX_IDX_ALL,
	PRCM54XX_IDX_MAX
} prcm54xx_index;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm54xx_powerdm_name_get
 * @BRIEF		convert user argument string (argv[]) into power domain
 *			name.
 * @RETURNS		power domain name in case of success
 *			NULL if no match found
 * @param[in]		s: user argument string (argv[])
 * @DESCRIPTION		convert user argument string (argv[]) into power domain
 *			name.
 *//*------------------------------------------------------------------------ */
static const char *_prcm54xx_powerdm_name_get(const char *s)
{
	if (s == NULL) {
		return NULL;
	} else if (strcasecmp(s, "emu") == 0) {
		return PWRDM_EMU;
	} else if (strcasecmp(s, "wkupaon") == 0) {
		return PWRDM_WKUPAON;
	} else if (strcasecmp(s, "coreaon") == 0) {
		return PWRDM_COREAON;
	} else if (strcasecmp(s, "cam") == 0) {
		return PWRDM_CAM;
	} else if (strcasecmp(s, "core") == 0) {
		return PWRDM_CORE;
	} else if (strcasecmp(s, "dss") == 0) {
		return PWRDM_DSS;
	} else if (strcasecmp(s, "l3init") == 0) {
		return PWRDM_L3_INIT;
	} else if (strcasecmp(s, "l4per") == 0) {
		if (cpu_revision_get() == REV_ES1_0)
			return PWRDM_L4_PER;
		else
			return NULL;
	} else if (strcasecmp(s, "abe") == 0) {
		return PWRDM_ABE;
	} else if (strcasecmp(s, "dsp") == 0) {
		return PWRDM_DSP;
	} else if (strcasecmp(s, "gpu") == 0) {
		return PWRDM_GPU;
	} else if (strcasecmp(s, "iva") == 0) {
		return PWRDM_IVA;
	} else if (strcasecmp(s, "mpu") == 0) {
		return PWRDM_MPU;
	} else {
		return NULL;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm54xx_clockdm_name_get
 * @BRIEF		retrieve clock domain name matching
 *			user argument string (i.e. argv[])
 * @RETURNS		clock domain name on success
 *			NULL if no match found
 * @param[in]		s: user argument string (argv[])
 *			List of recognized strings: "emu", "wkupaon", "coreaon",
 *			"cam", "l4cfg", "emif", "ipu", "l3main2", "l3instr",
 *			"l3main1", "c2c", "dma", "mipiext", "dss", "custefuse",
 *			"l3init", "l4per", "l4sec", "abe", "dsp", "gpu, "iva",
 *			"mpu"
 * @DESCRIPTION		retrieve clock domain name matching
 *			user argument string (i.e. argv[])
 *//*------------------------------------------------------------------------ */
static const char *_prcm54xx_clockdm_name_get(const char *s)
{
	if (s == NULL)
		return NULL;
	else if (strcasecmp(s, "emu") == 0)
		return CLKDM_EMU;
	else if (strcasecmp(s, "wkupaon") == 0)
		return CLKDM_WKUPAON;
	else if (strcasecmp(s, "coreaon") == 0)
		return CLKDM_COREAON;
	else if (strcasecmp(s, "cam") == 0)
		return CLKDM_CAM;
	else if (strcasecmp(s, "l4cfg") == 0)
		return CLKDM_L4_CFG;
	else if (strcasecmp(s, "emif") == 0)
		return CLKDM_EMIF;
	else if (strcasecmp(s, "ipu") == 0)
		return CLKDM_IPU;
	else if (strcasecmp(s, "l3main2") == 0)
		return CLKDM_L3_MAIN2;
	else if (strcasecmp(s, "l3instr") == 0)
		return CLKDM_L3_INSTR;
	else if (strcasecmp(s, "l3main1") == 0)
		return CLKDM_L3_MAIN1;
	else if (strcasecmp(s, "c2c") == 0)
		return CLKDM_C2C;
	else if (strcasecmp(s, "dma") == 0)
		return CLKDM_DMA;
	else if (strcasecmp(s, "mipiext") == 0)
		return CLKDM_MIPIEXT;
	else if (strcasecmp(s, "dss") == 0)
		return CLKDM_DSS;
	else if (strcasecmp(s, "custefuse") == 0)
		return CLKDM_CUST_EFUSE;
	else if (strcasecmp(s, "l3init") == 0)
		return CLKDM_L3_INIT;
	else if (strcasecmp(s, "l4per") == 0)
		return CLKDM_L4_PER;
	else if (strcasecmp(s, "l4sec") == 0)
		return CLKDM_L4_SEC;
	else if (strcasecmp(s, "abe") == 0)
		return CLKDM_ABE;
	else if (strcasecmp(s, "dsp") == 0)
		return CLKDM_DSP;
	else if (strcasecmp(s, "gpu") == 0)
		return CLKDM_GPU;
	else if (strcasecmp(s, "iva") == 0)
		return CLKDM_IVA;
	else if (strcasecmp(s, "mpu") == 0)
		return CLKDM_MPU;
	else
		return NULL;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		prcm54xx_pwrdm_config_show
 * @BRIEF		show configuration of a given power domain and
 *			included clock domains
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_UNEXPECTED
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		stream: output file
 * @param[in]		powerdm_u: power domain name, as user argument (argv[])
 *				If powerdm_u == NULL, show all power domains
 *				configuration.
 * @param[in]		clockdm_u = clock domain name, as user argument (argv[])
 *				If clockdm_u == NULL, show inner clock domain(s)
 *				configuration.
 * @DESCRIPTION		show configuration of a given power domain and
 *			included clock domains
 *//*------------------------------------------------------------------------ */
int prcm54xx_pwrdm_config_show(FILE *stream,
	const char *powerdm_u, const char *clockdm_u)
{
	int ret, all;
	const genlist *pwrdm_list;
	powerdm_info pwrdm;
	const char *powerdm = NULL;
	int p, pwrdm_count;
	const genlist *clkdm_list;
	clockdm_info clkdm;
	const char *clockdm = NULL;
	int c, clkdm_count;
	const genlist *mod_list;
	mod_info mod;
	int m, mod_count;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(stream, OMAPCONF_ERR_ARG);

	/* Retrieve power & clock domain names from user arguments */
	dprintf("%s(): powerdm_u=%s clockdm_u=%s\n", __func__,
		powerdm_u, clockdm_u);
	all = 0;
	if ((powerdm_u == NULL) && (clockdm_u == NULL)) {
		/* no power domain provided, select all */
		all = 1;
	} else if ((powerdm_u != NULL) && (clockdm_u == NULL)) {
		/* only power domain provided, show all inner clock domains */
		if (strcmp(powerdm_u, "all") == 0) {
			all = 1;
		} else {
			powerdm = _prcm54xx_powerdm_name_get(powerdm_u);
			if (powerdm == NULL)
				return err_arg_msg_show(HELP_PRCM);
		}
	} else if ((powerdm_u != NULL) && (clockdm_u != NULL)) {
		/* power domain & clock domain provided */
		if (strcmp(powerdm_u, "all") == 0) {
			all = 1;
		} else {
			powerdm = _prcm54xx_powerdm_name_get(powerdm_u);
			if (powerdm == NULL)
				return err_arg_msg_show(HELP_PRCM);
		}

		clockdm = _prcm54xx_clockdm_name_get(clockdm_u);
		if (clockdm == NULL)
			return err_arg_msg_show(HELP_PRCM);
		if (strcmp(clockdm_powerdm_get(clockdm), powerdm) != 0) {
			printf(
				"omapconf: clock domain '%s' is not part of '%s' power domain!!!\n\n",
				clockdm, powerdm);
			return err_arg_msg_show(HELP_PRCM);
		}
	} else {
		/* power domain is missing */
		fprintf(stderr,
			"omapconf: clkdm '%s' provided without pwrdm?!\n\n",
			clockdm_u);
		return OMAPCONF_ERR_UNEXPECTED;
	}
	dprintf("%s(): powerdm=%s clockdm=%s all=%d\n", __func__,
		powerdm, clockdm, all);

	/* Retrieve power domains list and count */
	pwrdm_list = powerdm_list_get();
	if (pwrdm_list == NULL) {
		fprintf(stderr,
			"omapconf: %s(): could not retrieve power domains list?!\n",
			__func__);
		return OMAPCONF_ERR_UNEXPECTED;
	}
	pwrdm_count = genlist_getcount((genlist *) pwrdm_list);
	if (pwrdm_count == 0) {
		fprintf(stderr,
			"omapconf: %s(): empty power domains list?!\n",
			__func__);
		return OMAPCONF_ERR_UNEXPECTED;
	}
	dprintf("%s(): power domains list retrieved.\n", __func__);

	/* Retrieve clock domains list and count */
	clkdm_list = clockdm_list_get();
	if (clkdm_list == NULL) {
		fprintf(stderr,
			"omapconf: %s(): could not retrieve clock domains list?!\n",
			__func__);
		return OMAPCONF_ERR_UNEXPECTED;
	}
	clkdm_count = genlist_getcount((genlist *) clkdm_list);
	if (clkdm_count == 0) {
		fprintf(stderr,
			"omapconf: %s(): empty clock domains list?!\n",
			__func__);
		return OMAPCONF_ERR_UNEXPECTED;
	}
	dprintf("%s(): clock domains list retrieved.\n", __func__);

	/* Retrieve modules list and count */
	mod_list = module_list_get();
	if (mod_list == NULL) {
		fprintf(stderr,
			"omapconf: %s(): could not retrieve modules list?!\n",
			__func__);
		return OMAPCONF_ERR_UNEXPECTED;
	}
	mod_count = genlist_getcount((genlist *) mod_list);
	if (mod_count == 0) {
		fprintf(stderr,
			"omapconf: %s(): empty modules list?!\n",
			__func__);
		return OMAPCONF_ERR_UNEXPECTED;
	}
	dprintf("%s(): modules list retrieved.\n", __func__);

	for (p = 0; p < pwrdm_count; p++) {
		genlist_get((genlist *) pwrdm_list, p, (powerdm_info *) &pwrdm);
		if ((all == 1) || (strcmp(pwrdm.name, powerdm) == 0)) {
			dprintf("%s(): %s power domain config:\n",
				__func__, pwrdm.name);
			switch (pwrdm.id) {
			case PWRDM54XX_WKUPAON:
			case PWRDM54XX_COREAON:
			case PWRDM54XX_MMAON:
			case PWRDM54XX_MPUAON:
				dprintf("%s(): powerdm %s skipped.\n",
					__func__, pwrdm.name);
				break;
			case PWRDM54XX_L4_PER:
				if (cpu_revision_get() != REV_ES1_0) {
					fprintf(stderr,
						"omapconf: %s(): powerdm %s does not exist on ES1.0.\n",
						__func__, pwrdm.name);
					return OMAPCONF_ERR_INTERNAL;
				}
			default:
				ret = powerdm_config_show(stream, pwrdm.name);
				if (ret != 0)
					return ret;
				break;
			}

			/* Display inner clock domain(s) configuration */
			for (c = 0; c < clkdm_count; c++) {
				genlist_get((genlist *) clkdm_list, c,
					(clockdm_info *) &clkdm);
				dprintf("%s(): %s clock domain config:\n",
					__func__, clkdm.name);
				if ((clockdm != NULL) &&
					(strcmp(clkdm.name, clockdm) != 0)) {
					dprintf(
						"%s(): clockdm %s skipped (not matching)\n",
						__func__, clkdm.name);
					continue;
				} else if (strcmp(clkdm.powerdm, pwrdm.name) != 0) {
					dprintf(
						"%s(): clockdm %s skipped (not included)\n",
						__func__, clkdm.name);
					continue;
				}
				ret = clockdm_config_show(stream, clkdm.name);
				if (ret != 0)
					return ret;

				/* Display inner module(s) configuration */
				for (m = 0; m < mod_count; m++) {
					genlist_get((genlist *) mod_list, m,
						(mod_info *) &mod);
					dprintf("%s(): %s module config:\n",
						__func__, mod.name);
					if (strcmp(mod.clkdm, clkdm.name) != 0) {
						dprintf(
							"%s(): module %s skipped (not part of domain)\n",
						__func__, mod.name);
						continue;
					}
					ret = module_config_show(
						stream, mod.name);
					if (ret != 0)
						return ret;
				}
			}
		}
	}

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		prcm54xx_config_show
 * @BRIEF		show configuration of a given power domain and
 *			included clock domains
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		stream: output file
 * @param[in]		argc: number of arguments (must be == 1 or 2)
 * @param[in]		argv: argument(s)
 *			argv[0] = power domain name, as supported by
 *			prcm54xx_s2idx()
 *			argv[1] = clock domain name, as supported by
 *			clkdm54xx_s2id()
 * @DESCRIPTION		show configuration of a given power domain and
 *			included clock domains
 *//*------------------------------------------------------------------------ */
int prcm54xx_config_show(FILE *stream, int argc, char *argv[])
{
	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(stream, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(argv, OMAPCONF_ERR_ARG);

	if (argc == 0) {
		return prcm54xx_pwrdm_config_show(stream, NULL, NULL);
	} else if (strcmp(argv[0], "statdep") == 0) {
		if (argc == 1) {
			return clkdmdep54xx_show(stream, CLKDMDEP_STATIC);
		} else if (argc == 2) {
			if (strcmp(argv[1], "cfg") == 0)
				return clkdmdep54xx_show(stream,
					CLKDMDEP_STATIC);
			else
				return err_arg_msg_show(HELP_STATDEP);
		} else {
			return err_arg_too_many_msg_show(HELP_STATDEP);
		}
	} else if (strcmp(argv[0], "dyndep") == 0) {
		if (argc == 1) {
			return clkdmdep54xx_show(stream, CLKDMDEP_DYNAMIC);
		} else if (argc == 2) {
			if (strcmp(argv[1], "cfg") == 0)
				return clkdmdep54xx_show(stream,
					CLKDMDEP_DYNAMIC);
			else
				return err_arg_msg_show(HELP_STATDEP);
		} else {
			return err_arg_too_many_msg_show(HELP_STATDEP);
		}
	} else if (strcmp(argv[0], "dep") == 0) {
		if (argc == 1) {
			return clkdmdep54xx_show(stream, CLKDMDEP_TYPE_MAX);
		} else if (argc == 2) {
			if (strcmp(argv[1], "cfg") == 0)
				return clkdmdep54xx_show(stream,
					CLKDMDEP_TYPE_MAX);
			else
				return err_arg_msg_show(HELP_STATDEP);
		} else {
			return err_arg_too_many_msg_show(HELP_STATDEP);
		}
	} else if (strcmp(argv[0], "abb") == 0) {
		if (argc == 1) {
			return abb54xx_config_show(stream);
		} else if (argc == 2) {
			if (strcmp(argv[1], "cfg") == 0)
				return abb54xx_config_show(stream);
			else
				return err_arg_msg_show(HELP_ABB);
		} else {
			return err_arg_too_many_msg_show(HELP_ABB);
		}


	} else {
		if (argc == 1) {
			if (strcmp(argv[0], "cfg") == 0)
				/* no power domain provided, select all */
				return prcm54xx_pwrdm_config_show(stream,
					NULL, NULL);
			else
				/*
				 * only power domain provided,
				 * show all inner clock domains
				 */
				return prcm54xx_pwrdm_config_show(stream,
					argv[0], NULL);
		} else if (argc == 2) {
			if (strcmp(argv[1], "cfg") == 0)
				/*
				 * only power domain provided,
				 * show all inner clock domains
				 */
				return prcm54xx_pwrdm_config_show(stream,
					argv[0], NULL);
			else
				/* power domain & clock domain provided */
				return prcm54xx_pwrdm_config_show(stream,
					argv[0], argv[1]);
		} else if (argc == 3) {
			/* power domain & clock domain provided */
			if (strcmp(argv[2], "cfg") == 0)
				return prcm54xx_pwrdm_config_show(stream,
					argv[0], argv[1]);
			else
				return err_arg_msg_show(HELP_PRCM);
		} else {
			return err_arg_too_many_msg_show(HELP_PRCM);
		}
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		prcm54xx_dump
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
int prcm54xx_dump(char *s)
{
	int ret;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	if ((s == NULL) || (strcmp(s, "all") == 0)) {
		/* ALL */
		ret = emu54xx_dump(stdout);
		ret |= wkupaon54xx_dump(stdout);
		ret |= coreaon54xx_dump(stdout);
		ret |= cam54xx_dump(stdout);
		ret |= core54xx_dump(stdout);
		ret |= prmdev54xx_dump(stdout);
		ret |= ckgen54xx_dump(stdout);
		ret |= instr54xx_dump(stdout);
		ret |= dss54xx_dump(stdout);
		ret |= l3init54xx_dump(stdout);
		if (cpu_revision_get() == REV_ES1_0)
			ret |= l4per54xx_dump(stdout);
		ret |= abe54xx_dump(stdout);
		ret |= dsp54xx_dump(stdout);
		ret |= gpu54xx_dump(stdout);
		ret |= iva54xx_dump(stdout);
		ret |= mpu54xx_dump(stdout);
		return ret;
	} else if (strcmp(s, "emu") == 0) {
		return emu54xx_dump(stdout);
	} else if (strcmp(s, "wkupaon") == 0) {
		return wkupaon54xx_dump(stdout);
	} else if (strcmp(s, "coreaon") == 0) {
		return coreaon54xx_dump(stdout);
	} else if (strcmp(s, "cam") == 0) {
		return cam54xx_dump(stdout);
	} else if (strcmp(s, "core") == 0) {
		return core54xx_dump(stdout);
	} else if (strcmp(s, "dev") == 0) {
		return prmdev54xx_dump(stdout);
	} else if (strcmp(s, "ckgen") == 0) {
		return ckgen54xx_dump(stdout);
	} else if (strcmp(s, "instr") == 0) {
		return instr54xx_dump(stdout);
	} else if (strcmp(s, "dss") == 0) {
		return dss54xx_dump(stdout);
	} else if (strcmp(s, "l3init") == 0) {
		return l3init54xx_dump(stdout);
	} else if (strcmp(s, "l4per") == 0) {
		if (cpu_revision_get() == REV_ES1_0)
			return l4per54xx_dump(stdout);
		else
			return err_arg_msg_show(HELP_PRCM);
	} else if (strcmp(s, "abe") == 0) {
		return abe54xx_dump(stdout);
	} else if (strcmp(s, "dsp") == 0) {
		return dsp54xx_dump(stdout);
	} else if (strcmp(s, "gpu") == 0) {
		return gpu54xx_dump(stdout);
	} else if (strcmp(s, "iva") == 0) {
		return iva54xx_dump(stdout);
	} else if (strcmp(s, "mpu") == 0) {
		return mpu54xx_dump(stdout);
	} else if (strcmp(s, "dep") == 0) {
		return clkdmdep54xx_dump(stdout);
	} else if (strcmp(s, "abb") == 0) {
		return abb54xx_dump(stdout);
	} else {
		return err_arg_msg_show(HELP_PRCM);
	}
}
