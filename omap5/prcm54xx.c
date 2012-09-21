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


static prcm54xx_index prcm54xx_s2idx(char *s);
static pwrdm54xx_id prcm54xx_idx2pwrdmid(prcm54xx_index idx);


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		prcm54xx_pwrdm_config_show
 * @BRIEF		show configuration of a given power domain and
 *			included clock domains
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in]		stream: output file
 * @param[in]		pwrdm_s: power domain name, as supported by
 *			prcm54xx_s2idx()
 *			If pwrdm_s == NULL, show all power domains
 *			configuration.
 * @param[in]		clkdm_s = clock domain name, as supported
 *			by clkdm54xx_s2id()
 *			If clkdm_s == NULL, show all inner clock domains
 *			configuration.
 * @DESCRIPTION		show configuration of a given power domain and
 *			included clock domains
 *//*------------------------------------------------------------------------ */
int prcm54xx_pwrdm_config_show(FILE *stream, char *pwrdm_s, char *clkdm_s)
{
	int ret;
	pwrdm54xx_id pwrdm_id, pwrdm_id_start, pwrdm_id_end;
	clkdm54xx_id clkdm_id, clkdm_id_start, clkdm_id_end;
	mod54xx_id mod_id;
	prcm54xx_index idx;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(stream, OMAPCONF_ERR_ARG);

	if ((pwrdm_s == NULL) && (clkdm_s == NULL)) {
		/* no power domain provided, select all */
		pwrdm_id_start = PWRDM54XX_EMU;
		pwrdm_id_end = PWRDM54XX_ID_MAX;
		clkdm_id_start = CLKDM54XX_EMU;
		clkdm_id_end = CLKDM54XX_ID_MAX;
	} else if ((pwrdm_s != NULL) && (clkdm_s == NULL)) {
		/* only power domain provided, show all inner clock domains */
		idx = prcm54xx_s2idx(pwrdm_s);
		if (idx == PRCM54XX_IDX_MAX)
			return err_arg_msg_show(HELP_PRCM);

		if (idx == PRCM54XX_IDX_ALL) {
			pwrdm_id_start = PWRDM54XX_EMU;
			pwrdm_id_end = PWRDM54XX_ID_MAX;
			clkdm_id_start = CLKDM54XX_EMU;
			clkdm_id_end = CLKDM54XX_ID_MAX;
		} else {
			pwrdm_id_start = prcm54xx_idx2pwrdmid(idx);
			if (pwrdm_id_start == PWRDM54XX_ID_MAX)
				return err_arg_msg_show(HELP_PRCM);

			pwrdm_id_end = (pwrdm54xx_id) (pwrdm_id_start + 1);
			clkdm_id_start = CLKDM54XX_EMU;
			clkdm_id_end = CLKDM54XX_ID_MAX;
		}
	} else if ((pwrdm_s != NULL) && (clkdm_s != NULL)) {
		/* power domain & clock domain provided */
		idx = prcm54xx_s2idx(pwrdm_s);
		if (idx == PRCM54XX_IDX_MAX)
			return err_arg_msg_show(HELP_PRCM);

		pwrdm_id_start = prcm54xx_idx2pwrdmid(idx);
		if (pwrdm_id_start == PWRDM54XX_ID_MAX)
			return err_arg_msg_show(HELP_PRCM);

		pwrdm_id_end = (pwrdm54xx_id) (pwrdm_id_start + 1);

		clkdm_id_start = clkdm54xx_s2id(clkdm_s);
		if (clkdm_id_start == CLKDM54XX_ID_MAX)
			return err_arg_msg_show(HELP_PRCM);

		if (clkdm54xx_pwrdm_get(clkdm_id_start) != pwrdm_id_start) {
			printf("omapconf: clock domain '\"%s\"' is not part "
				"of '\"%s\"' power domain!!!\n\n",
				clkdm_s, pwrdm_s);
			return err_arg_msg_show(HELP_PRCM);
		}
		clkdm_id_end = (clkdm54xx_id) (clkdm_id_start + 1);
	} else {
		/* pwrdm is missing */
		fprintf(stderr,
			"omapconf: clkdm '%s' provided without pwrdm?!\n\n",
			clkdm_s);
		return OMAPCONF_ERR_UNEXPECTED;
	}

	/* Display power domain(s) configuration */
	for (pwrdm_id = pwrdm_id_start; pwrdm_id < pwrdm_id_end; pwrdm_id++) {
		switch (pwrdm_id) {
		case PWRDM54XX_WKUPAON:
		case PWRDM54XX_COREAON:
		case PWRDM54XX_MMAON:
		case PWRDM54XX_MPUAON:
			break;
		default:
			ret = pwrdm54xx_config_show(stream,
				(pwrdm54xx_id) pwrdm_id);
			if (ret != 0)
				return ret;
			break;
		}

		/* Display inner clock domain(s) configuration */
		for (clkdm_id = clkdm_id_start; clkdm_id < clkdm_id_end;
			clkdm_id++) {
			if (clkdm54xx_pwrdm_get(clkdm_id) != pwrdm_id)
				continue;
			ret = clkdm54xx_config_show(stream, clkdm_id);
			if (ret != 0)
				return ret;

			/* Display inner module(s) configuration */
			for (mod_id = OMAP5_DEBUGSS; mod_id < MOD54XX_ID_MAX;
				mod_id++) {
				if (mod54xx_clkdm_get(mod_id) != clkdm_id)
					continue;
				ret = mod54xx_config_show(stream, mod_id);
				if (ret != 0)
					return ret;
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
 * @FUNCTION		prcm54xx_s2idx
 * @BRIEF		convert string to valid PRCM index
 * @RETURNS		valid PRCM index
 *			PRCM54XX_IDX_MAX if no valid PRCM index corresponding
 *			to string s
 * @param[in]		s: string
 * @DESCRIPTION		convert string to valid PRCM index
 *//*------------------------------------------------------------------------ */
prcm54xx_index prcm54xx_s2idx(char *s)
{
	if (strcmp(s, "all") == 0)
		return PRCM54XX_IDX_ALL;
	else if (strcmp(s, "emu") == 0)
		return PRCM54XX_IDX_EMU;
	else if (strcmp(s, "wkupaon") == 0)
		return PRCM54XX_IDX_WKUPAON;
	else if (strcmp(s, "coreaon") == 0)
		return PRCM54XX_IDX_COREAON;
	else if (strcmp(s, "cam") == 0)
		return PRCM54XX_IDX_CAM;
	else if (strcmp(s, "core") == 0)
		return PRCM54XX_IDX_CORE;
	else if (strcmp(s, "dev") == 0)
		return PRCM54XX_IDX_DEV;
	else if (strcmp(s, "core") == 0)
		return PRCM54XX_IDX_CORE;
	else if (strcmp(s, "ckgen") == 0)
		return PRCM54XX_IDX_CKGEN;
	else if (strcmp(s, "instr") == 0)
		return PRCM54XX_IDX_INSTR;
	else if (strcmp(s, "dss") == 0)
		return PRCM54XX_IDX_DSS;
	else if (strcmp(s, "l3init") == 0)
		return PRCM54XX_IDX_L3INIT;
	else if (strcmp(s, "l4per") == 0)
		return PRCM54XX_IDX_L4PER;
	else if (strcmp(s, "abe") == 0)
		return PRCM54XX_IDX_ABE;
	else if (strcmp(s, "dsp") == 0)
		return PRCM54XX_IDX_DSP;
	else if (strcmp(s, "gpu") == 0)
		return PRCM54XX_IDX_GPU;
	else if (strcmp(s, "iva") == 0)
		return PRCM54XX_IDX_IVA;
	else if (strcmp(s, "mpu") == 0)
		return PRCM54XX_IDX_MPU;
	else
		return PRCM54XX_IDX_MAX;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		prcm54xx_idx2pwrdmid
 * @BRIEF		convert PRCM index into valid power domain ID
 * @RETURNS		valid power domain ID
 *			PWRDM54XX_ID_MAX if no match found
 * @param[in]		idx: PRCM index
 * @DESCRIPTION		convert PRCM index into valid power domain ID
 *//*------------------------------------------------------------------------ */
pwrdm54xx_id prcm54xx_idx2pwrdmid(prcm54xx_index idx)
{
	pwrdm54xx_id id;

	switch (idx) {
	case PRCM54XX_IDX_EMU:
		id = PWRDM54XX_EMU;
		break;
	case PRCM54XX_IDX_WKUPAON:
		id = PWRDM54XX_WKUPAON;
		break;
	case PRCM54XX_IDX_COREAON:
		id = PWRDM54XX_COREAON;
		break;
	case PRCM54XX_IDX_CAM:
		id = PWRDM54XX_CAM;
		break;
	case PRCM54XX_IDX_CORE:
		id = PWRDM54XX_CORE;
		break;
	case PRCM54XX_IDX_DSS:
		id = PWRDM54XX_DSS;
		break;
	case PRCM54XX_IDX_L3INIT:
		id = PWRDM54XX_L3_INIT;
		break;
	case PRCM54XX_IDX_L4PER:
		id = PWRDM54XX_L4_PER;
		break;
	case PRCM54XX_IDX_ABE:
		id = PWRDM54XX_ABE;
		break;
	case PRCM54XX_IDX_DSP:
		id = PWRDM54XX_DSP;
		break;
	case PRCM54XX_IDX_GPU:
		id = PWRDM54XX_GPU;
		break;
	case PRCM54XX_IDX_IVA:
		id = PWRDM54XX_IVA;
		break;
	case PRCM54XX_IDX_MPU:
		id = PWRDM54XX_MPU;
		break;

	case PRCM54XX_IDX_DEV:
	case PRCM54XX_IDX_CKGEN:
	case PRCM54XX_IDX_INSTR:
	default:
		/*
		 * does not exist (not a power domain, but PRCM module).
		 */
		id = PWRDM54XX_ID_MAX;
	}

	dprintf("%s(%u)=%s\n", __func__, idx, pwrdm54xx_name_get(id));
	return id;
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
		return l4per54xx_dump(stdout);
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
