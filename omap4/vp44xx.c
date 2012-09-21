/*
 *
 * @Component			OMAPCONF
 * @Filename			vp44xx.c
 * @Description			OMAP4 VOLTAGE PROCESSOR (VP) Definitions &
 *				Functions
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


#include <vp44xx.h>
#include <vp44xx-data.h>
#include <vp.h>
#include <lib.h>
#include <mem.h>
#include <cpuinfo.h>
#include <voltdm44xx.h>
#include <prm44xx.h>


/* #define VP44XX_DEBUG */
#ifdef VP44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vp44xx_name_get
 * @BRIEF		return VP module name.
 * @RETURNS		VP module name on success
 *			"FIXME" string in case of error
 * @param[in]		vp_id: VP module ID
 * @DESCRIPTION		return VP module name.
 *//*------------------------------------------------------------------------ */
const char *vp44xx_name_get(vp44xx_mod_id vp_id)
{
	if (vp_id < VP44XX_ID_MAX)
		return vp44xx_mod_names[vp_id];
	else
		return vp44xx_mod_names[VP44XX_ID_MAX];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vp44xx_registers_get
 * @BRIEF		save VP registers content into vp_regs structure.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		vp_id: VP module ID
 * @param[in,out]	vp_regs: VP module registers content
 * @DESCRIPTION		save VP registers content into vp_regs structure.
 *//*------------------------------------------------------------------------ */
int vp44xx_registers_get(vp44xx_mod_id vp_id, vp_registers *vp_regs)
{
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(vp_id, VP44XX_ID_MAX, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(vp_regs, OMAPCONF_ERR_ARG);

	switch (vp_id) {
	case VP44XX_MPU:
		vp_regs->vdd_id = (unsigned short) OMAP4_VDD_MPU;
		ret = mem_read(OMAP4430_PRM_VP_MPU_CONFIG,
			&(vp_regs->vp_config));
		ret += mem_read(OMAP4430_PRM_VP_MPU_VSTEPMIN,
			&(vp_regs->vp_vstepmin));
		ret += mem_read(OMAP4430_PRM_VP_MPU_VSTEPMAX,
			&(vp_regs->vp_vstepmax));
		ret += mem_read(OMAP4430_PRM_VP_MPU_VLIMITTO,
			&(vp_regs->vp_vlimitto));
		ret += mem_read(OMAP4430_PRM_VP_MPU_VOLTAGE,
			&(vp_regs->vp_voltage));
		ret += mem_read(OMAP4430_PRM_VP_MPU_STATUS,
			&(vp_regs->vp_status));
		break;

	case VP44XX_IVA:
		vp_regs->vdd_id = (unsigned short) OMAP4_VDD_IVA;
		ret = mem_read(OMAP4430_PRM_VP_IVA_CONFIG,
			&(vp_regs->vp_config));
		ret += mem_read(OMAP4430_PRM_VP_IVA_VSTEPMIN,
			&(vp_regs->vp_vstepmin));
		ret += mem_read(OMAP4430_PRM_VP_IVA_VSTEPMAX,
			&(vp_regs->vp_vstepmax));
		ret += mem_read(OMAP4430_PRM_VP_IVA_VLIMITTO,
			&(vp_regs->vp_vlimitto));
		ret += mem_read(OMAP4430_PRM_VP_IVA_VOLTAGE,
			&(vp_regs->vp_voltage));
		ret += mem_read(OMAP4430_PRM_VP_IVA_STATUS,
			&(vp_regs->vp_status));
		break;

	case VP44XX_CORE:
		vp_regs->vdd_id = (unsigned short) OMAP4_VDD_CORE;
		ret = mem_read(OMAP4430_PRM_VP_CORE_CONFIG,
			&(vp_regs->vp_config));
		ret += mem_read(OMAP4430_PRM_VP_CORE_VSTEPMIN,
			&(vp_regs->vp_vstepmin));
		ret += mem_read(OMAP4430_PRM_VP_CORE_VSTEPMAX,
			&(vp_regs->vp_vstepmax));
		ret += mem_read(OMAP4430_PRM_VP_CORE_VLIMITTO,
			&(vp_regs->vp_vlimitto));
		ret += mem_read(OMAP4430_PRM_VP_CORE_VOLTAGE,
			&(vp_regs->vp_voltage));
		ret += mem_read(OMAP4430_PRM_VP_CORE_STATUS,
			&(vp_regs->vp_status));
		break;

	default:
		ret = OMAPCONF_ERR_ARG;
	}

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vp44xx_golden_settings_get
 * @BRIEF		return VP module golden settings.
 * @RETURNS		VP module name on success
 *			"FIXME" string in case of error
 * @param[in]		vp_id: VP module ID
 * @param[in]		opp_id: OPP ID
 * @DESCRIPTION		return VP module golden settings, for a given chip,
 *			module and OPP.
 *//*------------------------------------------------------------------------ */
const vp_audit_settings *vp44xx_golden_settings_get(vp44xx_mod_id vp_id,
	opp44xx_id opp_id)
{
	omap_chip chip_id;

	CHECK_ARG_LESS_THAN(vp_id, VP44XX_ID_MAX, NULL);
	CHECK_ARG_LESS_THAN(opp_id, OPP44XX_ID_MAX, NULL);

	chip_id = cpu_get();
	dprintf("%s(): vp_id=%d opp_id=%d chip_id=%d\n", __func__,
		vp_id, opp_id, chip_id);
	return vp44xx_golden_settings[chip_id][vp_id][opp_id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vp44xx_config_show
 * @BRIEF		decode and print Voltage Processor (VP) configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		stream: output file (NULL: no output (silent))
 * @DESCRIPTION		decode and print Voltage Processor (VP) configuration
 *//*------------------------------------------------------------------------ */
int vp44xx_config_show(FILE *stream)
{
	int ret = 0;
	vp_registers vp_regs[VP44XX_ID_MAX];

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	/* Read VP_MPU registers */
	ret = vp44xx_registers_get(VP44XX_MPU, &(vp_regs[VP44XX_MPU]));
	if (ret != 0)
		return ret;

	/* Read VP_IVA registers */
	ret = vp44xx_registers_get(VP44XX_IVA, &(vp_regs[VP44XX_IVA]));
	if (ret != 0)
		return ret;

	/* Read VP_CORE registers */
	ret = vp44xx_registers_get(VP44XX_CORE, &(vp_regs[VP44XX_CORE]));
	if (ret != 0)
		return ret;

	return vp_config_show(stream, vp_regs);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vp44xx_config_audit
 * @BRIEF		audit Voltage Processor (VP) configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		stream: output file (NULL: no output (silent))
 * @param[in]		vp_id: VP module ID
 * @param[in,out]	err_nbr: audit error number
 * @param[in,out]	wng_nbr: audit warning number
 * @DESCRIPTION		audit Voltage Processor (VP) configuration by comparison
 *			with expected ("golden") settings
 *//*------------------------------------------------------------------------ */
int vp44xx_config_audit(FILE *stream, vp44xx_mod_id vp_id,
	unsigned int *err_nbr, unsigned int *wng_nbr)
{
	int ret = 0;
	vp_registers vp_regs;
	const vp_audit_settings *vp_golden_settings;
	vp44xx_mod_id vp;
	opp44xx_id opp;
	unsigned int err_cnt, wng_cnt;
	char opp_name[OPP44XX_MAX_NAME_LENGTH];

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(err_nbr, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(wng_nbr, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(vp_id, VP44XX_ID_MAX + 1, OMAPCONF_ERR_ARG);

	*err_nbr = 0;
	*wng_nbr = 0;
	for (vp = VP44XX_MPU; vp < VP44XX_ID_MAX; vp++) {
		if ((vp_id != VP44XX_ID_MAX) && (vp_id != vp))
			continue;

		dprintf("\n%s(): Auditing %s\n", __func__,
			vp44xx_name_get(vp));
		err_cnt = 0;
		wng_cnt = 0;

		/* Read VP registers */
		ret = vp44xx_registers_get(vp, &vp_regs);
		if (ret != 0) {
			(*err_nbr) += 1;
			return ret;
		}

		/* Get OPP */
		switch (vp) {
		case VP44XX_MPU:
			ret = voltdm44xx_get_opp(OMAP4_VDD_MPU, &opp);
			voltdm44xx_opp2string(opp_name, opp, OMAP4_VDD_MPU);
			dprintf("  OPP is %s\n", opp_name);
			break;

		case VP44XX_IVA:
			ret = voltdm44xx_get_opp(OMAP4_VDD_IVA, &opp);
			voltdm44xx_opp2string(opp_name, opp, OMAP4_VDD_IVA);
			dprintf("  OPP is %s\n", opp_name);
			break;

		case VP44XX_CORE:
			ret = voltdm44xx_get_opp(OMAP4_VDD_CORE, &opp);
			voltdm44xx_opp2string(opp_name, opp, OMAP4_VDD_CORE);
			dprintf("  OPP is %s\n", opp_name);
			break;

		default:
			(*err_nbr) += 1;
			fprintf(stderr, "unexpected vp! (%u)\n", vp);
			return OMAPCONF_ERR_UNEXPECTED;
		}
		if (ret != 0) {
			(*wng_nbr) += 1;
			if (stream != NULL) {
				fprintf(stream, "Warning: could not find OPP"
					", audit cannot be run.\n");
			}
			continue;
		}

		/* Get expected ("golden") settings */
		vp_golden_settings = vp44xx_golden_settings_get(vp, opp);
		if (vp_golden_settings == NULL) {
			(*wng_nbr) += 1;
			if (stream != NULL) {
				fprintf(stream, "Warning: could not find golden"
					" settings, audit cannot be run.\n");
			}
			continue;
		}

		/* Audit settings */
		ret = vp_config_audit(stream, vp44xx_name_get(vp), opp_name,
			&vp_regs, vp_golden_settings, &err_cnt, &wng_cnt);
		(*err_nbr) += err_cnt;
		(*wng_nbr) += wng_cnt;
		if (ret != 0)
			return ret;
	}

	if (stream != NULL) {
		if (*err_nbr == 0)
			fprintf(stream,
				"\nSUCCESS! VP Configuration Audit "
				"completed with 0 error (%u warning(s)).\n\n",
				*wng_nbr);
		else
			fprintf(stream,
				"\nFAILED! VP Configuration Audit "
				"completed with %u error(s) and %u warning(s)."
				"\n\n", *err_nbr, *wng_nbr);
	}

	return ret;
}
