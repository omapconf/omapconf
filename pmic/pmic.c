/*
 *
 * @Component			OMAPCONF
 * @Filename			pmic.c
 * @Description			OMAP Power Companion Chip Library
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


#include <pmic.h>
#include <string.h>
#include <i2c-tools.h>
#include <stdio.h>
#include <lib.h>
#include <cpuinfo.h>
#include <twl603x.h>
#include <tps62361.h>
#include <tps659038.h>
#include <tps65217x.h>
#include <help.h>
#include <voltdm44xx.h>
#include <voltdm54xx.h>
#include <voltdm_dra7xx.h>
#include <voltdm_am335x.h>


/* #define PMIC_DEBUG */
#ifdef PMIC_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static unsigned short pmic_detection_done_flag = 0;

static pmic_id pmic_chip[PMIC_SMPS_MAX_NUMBER] = {
	PMIC_ID_MAX, PMIC_ID_MAX, PMIC_ID_MAX, PMIC_ID_MAX, PMIC_ID_MAX};

static double pmic_chip_revision[PMIC_SMPS_MAX_NUMBER] = {
	(double) OMAPCONF_ERR_NOT_AVAILABLE,
	(double) OMAPCONF_ERR_NOT_AVAILABLE,
	(double) OMAPCONF_ERR_NOT_AVAILABLE,
	(double) OMAPCONF_ERR_NOT_AVAILABLE,
	(double) OMAPCONF_ERR_NOT_AVAILABLE};

static double pmic_eprom_revision[PMIC_SMPS_MAX_NUMBER] = {
	(double) OMAPCONF_ERR_NOT_AVAILABLE,
	(double) OMAPCONF_ERR_NOT_AVAILABLE,
	(double) OMAPCONF_ERR_NOT_AVAILABLE,
	(double) OMAPCONF_ERR_NOT_AVAILABLE,
	(double) OMAPCONF_ERR_NOT_AVAILABLE};

static unsigned short pmic_single_chip_flag = 1;


static const char pmic_names[PMIC_ID_MAX + 1][PMIC_NAME_MAX_LENGTH] = {
	[PMIC_TWL6030] = "TWL6030",
	[PMIC_TWL6032] = "TWL6032",
	[PMIC_TPS62361] = "TPS62361",
	[PMIC_TWL6034] = "TWL6034",
	[PMIC_TWL6035] = "TWL6035",
	[PMIC_TPS659038] = "TPS659038",
	[PMIC_TPS65217A] = "TPS65217A",
	[PMIC_TPS65217B] = "TPS65217B",
	[PMIC_TPS65217C] = "TPS65217C",
	[PMIC_TPS65217D] = "TPS65217D",
	[PMIC_TPS65917] = "TPS65917",
	[PMIC_ID_MAX] = "FIXME"};


static const char smps44xx_names[PMIC_SMPS_ID_MAX + 1][PMIC_NAME_MAX_LENGTH] = {
	[PMIC_SMPS_MPU] = "VDD_MPU",
	[PMIC_SMPS_MM] = "VDD_IVA",
	[PMIC_SMPS_CORE] = "VDD_CORE",
	[PMIC_SMPS_GPU] = "FIXME",
	[PMIC_SMPS_DSPEVE] = "FIXME",
	[PMIC_SMPS_ID_MAX] = "FIXME"};


static const char smps54xx_names[PMIC_SMPS_ID_MAX + 1][PMIC_NAME_MAX_LENGTH] = {
	[PMIC_SMPS_MPU] = "VDD_MPU",
	[PMIC_SMPS_MM] = "VDD_MM",
	[PMIC_SMPS_CORE] = "VDD_CORE",
	[PMIC_SMPS_GPU] = "FIXME",
	[PMIC_SMPS_DSPEVE] = "FIXME",
	[PMIC_SMPS_ID_MAX] = "FIXME"};


static const char smps_dra7xx_names[PMIC_SMPS_ID_MAX + 1][PMIC_NAME_MAX_LENGTH] = {
	[PMIC_SMPS_MPU] = "VDD_MPU",
	[PMIC_SMPS_MM] = "VDD_IVA",
	[PMIC_SMPS_CORE] = "VDD_CORE",
	[PMIC_SMPS_GPU] = "VDD_GPU",
	[PMIC_SMPS_DSPEVE] = "VDD_DSPEVE",
	[PMIC_SMPS_ID_MAX] = "FIXME"};


static const char smps_am335x_names[PMIC_SMPS_ID_MAX + 1][PMIC_NAME_MAX_LENGTH] = {
	[PMIC_SMPS_MPU] = "VDD_MPU",
	[PMIC_SMPS_MM] = "FIXME",
	[PMIC_SMPS_CORE] = "VDD_CORE",
	[PMIC_SMPS_GPU] = "FIXME",
	[PMIC_SMPS_DSPEVE] = "FIXME",
	[PMIC_SMPS_ID_MAX] = "FIXME"};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pmic_detection_done
 * @BRIEF		return 1 if PMIC detection already done
 *			(i.e. static data valid)
 *			0 otherwise.
 * @RETURNS		1 if PMIC detection already done
 *			0 otherwise
 * @DESCRIPTION		return 1 if PMIC detection already done
 *			(i.e. static data valid)
 *			0 otherwise.
 *//*------------------------------------------------------------------------ */
unsigned short pmic_detection_done(void)
{
	return pmic_detection_done_flag;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vdd_id2smps_id
 * @BRIEF		convert VDD ID into SMPS ID (for a given platform)
 * @RETURNS		valid SMPS ID in case of success
 *			PMIC_SMPS_ID_MAX in case of error
 * @param[in]		vdd_id: valid VDD ID
 * @DESCRIPTION		convert VDD ID into SMPS ID (for a given platform)
 *//*------------------------------------------------------------------------ */
pmic_smps_id vdd_id2smps_id(unsigned short vdd_id)
{
	pmic_smps_id smps_id;
	char smps_name[16];
	char vdd_name[16];

	switch (cpu_get()) {
	case OMAP_4430:
	case OMAP_4460:
	case OMAP_4470:
		voltdm44xx_get_name(vdd_id, vdd_name);
		if ((vdd_id == OMAP4_LDO_WKUP) || (vdd_id > OMAP4_VDD_CORE)) {
			fprintf(stderr, "%s(): incorrect vdd_id! (%u)\n",
				__func__, vdd_id);
			smps_id =  PMIC_SMPS_ID_MAX;
			strncpy(smps_name, "FIXME", 16);
		} else {
			smps_id = vdd_id - 1;
			strncpy(smps_name, smps_name_get(smps_id), 16);
		}
		break;

	case OMAP_5430:
	case OMAP_5432:
		strncpy(vdd_name, voltdm54xx_name_get(vdd_id), 16);
		if ((vdd_id == VDD54XX_WKUP) || (vdd_id > VDD54XX_CORE)) {
			fprintf(stderr, "%s(): incorrect vdd_id! (%u)\n",
				__func__, vdd_id);
			smps_id =  PMIC_SMPS_ID_MAX;
			strncpy(smps_name, "FIXME", 16);
		} else {
			smps_id = vdd_id - 1;
			strncpy(smps_name, smps_name_get(smps_id), 16);
		}
		break;
	case DRA_75X:
	case DRA_72X:
		strncpy(vdd_name, voltdm_dra7xx_name_get(vdd_id), 16);
		if (vdd_id > VDD_DRA7XX_RTC) {
			fprintf(stderr, "%s(): incorrect vdd_id! (%u)\n",
				__func__, vdd_id);
			smps_id =  PMIC_SMPS_ID_MAX;
			strncpy(smps_name, "FIXME", 16);
		} else {
			switch (vdd_id) {
			case VDD_DRA7XX_MPU:
				smps_id = PMIC_SMPS_MPU;
				break;
			case VDD_DRA7XX_CORE:
				smps_id = PMIC_SMPS_CORE;
				break;
			case VDD_DRA7XX_IVA:
				smps_id = PMIC_SMPS_MM;
				break;
			case VDD_DRA7XX_DSPEVE:
				smps_id = PMIC_SMPS_DSPEVE;
				break;
			case VDD_DRA7XX_GPU:
				smps_id = PMIC_SMPS_GPU;
				break;
			default:
				smps_id = PMIC_SMPS_ID_MAX;
			}
			strncpy(smps_name, smps_name_get(smps_id), 16);
		}
		break;

	case AM_3352:
	case AM_3354:
	case AM_3356:
	case AM_3357:
	case AM_3358:
	case AM_3359:
		strncpy(vdd_name, voltdm_am335x_name_get(vdd_id), 16);
		if (vdd_id > VDD_AM335X_RTC) {
			fprintf(stderr, "%s(): incorrect vdd_id! (%u)\n",
				__func__, vdd_id);
			smps_id =  PMIC_SMPS_ID_MAX;
			strncpy(smps_name, "FIXME", 16);
		} else {
			switch (vdd_id) {
			case VDD_AM335X_MPU:
				smps_id = PMIC_SMPS_MPU;
				break;
			case VDD_AM335X_CORE:
				smps_id = PMIC_SMPS_CORE;
				break;
			default:
				smps_id = PMIC_SMPS_ID_MAX;
			}
			strncpy(smps_name, smps_name_get(smps_id), 16);
		}
		break;

	default:
		fprintf(stderr, "%s(): unsupported CPU! (%s)\n",
			__func__, cpu_gets(smps_name));
		smps_id =  PMIC_SMPS_ID_MAX;
		strncpy(smps_name, "FIXME", 16);
	}

	dprintf("%s(): vdd_id=%s => smps_id=%s\n", __func__,
		vdd_name, smps_name);

	return smps_id;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		smps_id2vdd_id
 * @BRIEF		convert SMPS ID into VDD ID (for a given platform)
 * @RETURNS		valid VDD ID in case of success
 *			OMAP4_VD_ID_MAX in case of error (OMAP4)
 *			VDD54XX_ID_MAX in case of error (OMAP5)
 * @param[in]		smps_id: valid SMPS ID
 * @DESCRIPTION		convert SMPS ID into VDD ID (for a given platform)
 *//*------------------------------------------------------------------------ */
unsigned short smps_id2vdd_id(pmic_smps_id smps_id)
{
	unsigned short vdd_id;
	char name[16];

	switch (cpu_get()) {
	case OMAP_4430:
	case OMAP_4460:
	case OMAP_4470:
		if (smps_id > PMIC_SMPS_ID_MAX) {
			fprintf(stderr, "%s(): incorrect smps_id! (%u)\n",
				__func__, smps_id);
			vdd_id =  (unsigned short) OMAP4_VD_ID_MAX;
			strncpy(name, "FIXME", 16);
		} else {
			vdd_id = smps_id + 1;
			voltdm44xx_get_name(vdd_id, name);
		}
		break;

	case OMAP_5430:
	case OMAP_5432:
		if (smps_id > PMIC_SMPS_ID_MAX) {
			fprintf(stderr, "%s(): incorrect smps_id! (%u)\n",
				__func__, smps_id);
			vdd_id =  (unsigned short) VDD54XX_ID_MAX;
			strncpy(name, "FIXME", 16);

		} else {
			vdd_id = smps_id + 1;
			strncpy(name, voltdm54xx_name_get(vdd_id), 16);
		}
		break;
	case DRA_75X:
	case DRA_72X:
		if (smps_id > PMIC_SMPS_ID_MAX) {
			fprintf(stderr, "%s(): incorrect smps_id! (%u)\n",
				__func__, smps_id);
			vdd_id =  (unsigned short) VDD_DRA7XX_ID_MAX;
			strncpy(name, "FIXME", 16);

		} else {
			switch (smps_id) {
			case PMIC_SMPS_MPU:
				vdd_id = VDD_DRA7XX_MPU;
				break;
			case PMIC_SMPS_CORE:
				vdd_id = VDD_DRA7XX_CORE;
				break;
			case PMIC_SMPS_MM:
				vdd_id = VDD_DRA7XX_IVA;
				break;
			case PMIC_SMPS_DSPEVE:
				vdd_id = VDD_DRA7XX_DSPEVE;
				break;
			case PMIC_SMPS_GPU:
				vdd_id = VDD_DRA7XX_GPU;
				break;
			default:
				vdd_id = VDD_DRA7XX_ID_MAX;
			}
			strncpy(name, voltdm54xx_name_get(vdd_id), 16);
		}
		break;

	case AM_3352:
	case AM_3354:
	case AM_3356:
	case AM_3357:
	case AM_3358:
	case AM_3359:
		if (smps_id > PMIC_SMPS_ID_MAX) {
			fprintf(stderr, "%s(): incorrect smps_id! (%u)\n",
				__func__, smps_id);
			vdd_id =  (unsigned short) VDD_AM335X_ID_MAX;
			strncpy(name, "FIXME", 16);

		} else {
			switch (smps_id) {
			case PMIC_SMPS_MPU:
				vdd_id = VDD_AM335X_MPU;
				break;
			case PMIC_SMPS_CORE:
				vdd_id = VDD_AM335X_CORE;
				break;
			default:
				vdd_id = VDD_AM335X_ID_MAX;
			}
			strncpy(name, voltdm_am335x_name_get(vdd_id), 16);
		}
		break;

	default:
		fprintf(stderr, "%s(): unsupported CPU! (%s)\n",
			__func__, cpu_gets(name));
		vdd_id = (unsigned short) VDD54XX_ID_MAX;
		strncpy(name, "FIXME", 16);
	}

	dprintf("%s(): smps_id=%s => vdd_id=%s\n", __func__,
		smps_name_get(smps_id), name);

	return vdd_id;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pmic_name_get
 * @BRIEF		return PMIC chip name as a string
 * @RETURNS		PMIC chip name as a string in case of success
 *			"FIXME" in case of error
 * @param[in]		id: valid PMIC ID
 * @DESCRIPTION		return PMIC chip name as a string
 *//*------------------------------------------------------------------------ */
const char *pmic_name_get(pmic_id id)
{
	if (id > PMIC_ID_MAX)
		id = PMIC_ID_MAX;

	return pmic_names[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pmic_smps_init
 * @BRIEF		Initialize PMIC information related SMPS ID.
 * @RETURNS		None
 * @DESCRIPTION		Initialize PMIC information related SMPS ID.
 *//*------------------------------------------------------------------------ */
void pmic_smps_init(pmic_smps_id id, unsigned short is_twl6030,
		unsigned short is_twl6032, unsigned short is_twl6034,
		unsigned short is_twl6035, unsigned short tps62361_present,
		unsigned short tps659038_present,
		unsigned short tps65217x_present)
{
	switch (cpu_get()) {
	case OMAP_4430:
	case OMAP_4460:
	case OMAP_4470:
		if (tps62361_present) {
			pmic_chip[id] = PMIC_TPS62361;
			pmic_chip_revision[id] =
				tps62361_chip_revision_get();
			pmic_eprom_revision[id] =
				tps62361_eprom_revision_get();
		} else if (is_twl6032) {
			pmic_chip[id] = PMIC_TWL6032;
			pmic_chip_revision[id] =
				twl603x_chip_revision_get();
			pmic_eprom_revision[id] =
				twl603x_eprom_revision_get();
		} else if (is_twl6030) {
			pmic_chip[id] = PMIC_TWL6030;
			pmic_chip_revision[id] =
				twl603x_chip_revision_get();
			pmic_eprom_revision[id] =
				twl603x_eprom_revision_get();
		} else if (is_twl6034) {
			pmic_chip[id] = PMIC_TWL6034;
			pmic_chip_revision[id] =
				twl603x_chip_revision_get();
			pmic_eprom_revision[id] =
				twl603x_eprom_revision_get();
		} else {
			pmic_chip[id] = PMIC_ID_MAX;
			pmic_chip_revision[id] =
				(double) OMAPCONF_ERR_NOT_AVAILABLE;
			pmic_eprom_revision[id] =
				(double) OMAPCONF_ERR_NOT_AVAILABLE;
		}
		break;

	case OMAP_5430:
	case OMAP_5432:
		if (is_twl6035) {
			pmic_chip[id] = PMIC_TWL6035;
			pmic_chip_revision[id] =
				twl603x_chip_revision_get();
			pmic_eprom_revision[id] =
				twl603x_eprom_revision_get();
		} else {
			pmic_chip[id] = PMIC_ID_MAX;
			pmic_chip_revision[id] =
				(double) OMAPCONF_ERR_NOT_AVAILABLE;
			pmic_eprom_revision[id] =
				(double) OMAPCONF_ERR_NOT_AVAILABLE;
		}
		break;

	case DRA_75X:
		if (tps659038_present) {
			pmic_chip[id] = PMIC_TPS659038;
			pmic_chip_revision[id] =
				tps659038_chip_revision_get();
			pmic_eprom_revision[id] =
				tps659038_eprom_revision_get();
		} else {
			pmic_chip[id] = PMIC_ID_MAX;
			pmic_chip_revision[id] =
				(double) OMAPCONF_ERR_NOT_AVAILABLE;
			pmic_eprom_revision[id] =
				(double) OMAPCONF_ERR_NOT_AVAILABLE;
		}
		break;

	case DRA_72X:
		if (tps659038_present) {
			pmic_chip[id] = PMIC_TPS65917;
			pmic_chip_revision[id] =
				tps659038_chip_revision_get();
			pmic_eprom_revision[id] =
				tps659038_eprom_revision_get();
		} else {
			pmic_chip[id] = PMIC_ID_MAX;
			pmic_chip_revision[id] =
				(double) OMAPCONF_ERR_NOT_AVAILABLE;
			pmic_eprom_revision[id] =
				(double) OMAPCONF_ERR_NOT_AVAILABLE;
		}
		break;

	case AM_3352:
	case AM_3354:
	case AM_3356:
	case AM_3357:
	case AM_3358:
	case AM_3359:
		if (tps65217x_present) {
			pmic_chip[id] = (pmic_id) tps65217x_chip_get();
			pmic_chip_revision[id] =
				tps65217x_chip_revision_get();
			pmic_eprom_revision[id] =
				tps65217x_eprom_revision_get();
		} else {
			pmic_chip[id] = PMIC_ID_MAX;
			pmic_chip_revision[id] =
				(double) OMAPCONF_ERR_NOT_AVAILABLE;
			pmic_eprom_revision[id] =
				(double) OMAPCONF_ERR_NOT_AVAILABLE;
		}
		break;

	default:
		pmic_chip[id] = PMIC_ID_MAX;
			pmic_chip_revision[id] =
				(double) OMAPCONF_ERR_NOT_AVAILABLE;
			pmic_eprom_revision[id] =
				(double) OMAPCONF_ERR_NOT_AVAILABLE;
	}
	dprintf("%s(): %s PMIC is %s (chip revision=%lf, EPROM revision=%lf)\n",
		__func__, smps_name_get(id),
		pmic_name_get(pmic_chip[id]),
		pmic_chip_revision[id],
		pmic_eprom_revision[id]);

	return;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pmic_detect
 * @BRIEF		detect platform PMIC chip(s) and retrieve PMIC details.
 * @RETURNS		0
 * @DESCRIPTION		detect platform PMIC chip(s) and retrieve PMIC details.
 *//*------------------------------------------------------------------------ */
int pmic_detect(void)
{
	unsigned short is_twl6030, is_twl6032, is_twl6034, is_twl6035,
	tps62361_present, tps659038_present, tps65217x_present;

	if (pmic_detection_done())
		return 0;

	is_twl6030 = twl603x_is_twl6030();
	is_twl6032 = twl603x_is_twl6032();
	is_twl6034 = twl603x_is_twl6034();
	is_twl6035 = twl603x_is_twl6035();
	tps62361_present = tps62361_is_present();
	tps659038_present = tps659038_is_present();
	tps65217x_present = tps65217x_is_present();
	dprintf(
		"%s(): is_twl6030=%u is_twl6032=%u is_tps62361=%u "
		"is_twl6034=%u is_twl6035=%u is_tps659038=%u is_tps65217x=%u\n",
		__func__, is_twl6030,
		is_twl6032, tps62361_present, is_twl6034, is_twl6035,
		tps659038_present, tps65217x_present);

	/*
	 * Detect PMIC powering VDD_MPU rail:
	 * OMAP4: can be either TWL6030, TWL6032, TWL6034 or TPS62361.
	 * OMAP5: TWL6035
	 * DRA7: TPS659038
	 * AM335X: TPS65217X
	 */
	pmic_smps_init(PMIC_SMPS_MPU, is_twl6030, is_twl6032, is_twl6034, is_twl6035,
		tps62361_present, tps659038_present, tps65217x_present);

	/*
	 * Detect PMIC powering VDD_[IVA-MM] rail:
	 * OMAP4: can be either TWL6030 or TWL6032 or TWL6034.
	 * OMAP5: TWL6035
	 * DRA7: TPS659038
	 * AM335X: N/A.
	 */
	pmic_smps_init(PMIC_SMPS_MM, is_twl6030, is_twl6032, is_twl6034, is_twl6035,
		tps62361_present, tps659038_present, tps65217x_present);

	/*
	 * Detect PMIC powering VDD_CORE rail:
	 * OMAP4: can be either TWL6030 or TWL6032 or TWL6034.
	 * OMAP5: TWL6035
	 * DRA7: TPS659038
	 * AM335X: TPS65217X
	 */
	pmic_smps_init(PMIC_SMPS_CORE, is_twl6030, is_twl6032, is_twl6034, is_twl6035,
		tps62361_present, tps659038_present, tps65217x_present);

	/*
	 * Detect PMIC powering VDD_GPU, DSPEVE rail:
	 * OMAP4 & OMAP5: N/A.
	 * DRA7: TPS659038
	 * AM335X: N/A.
	 */
	if (cpu_get() == DRA_75X || cpu_get() == DRA_72X) {
		pmic_smps_init(PMIC_SMPS_GPU, is_twl6030, is_twl6032, is_twl6034, is_twl6035,
		tps62361_present, tps659038_present, tps65217x_present);
		pmic_smps_init(PMIC_SMPS_DSPEVE, is_twl6030, is_twl6032, is_twl6034, is_twl6035,
		tps62361_present, tps659038_present, tps65217x_present);
	}

	/* Set single-chip flag accordingly */
	if (((pmic_chip[PMIC_SMPS_MPU] == pmic_chip[PMIC_SMPS_MM]) &&
		(pmic_chip[PMIC_SMPS_MPU] == pmic_chip[PMIC_SMPS_CORE])) ||
		cpu_is_am335x()) {
		pmic_single_chip_flag = 1;
		dprintf("%s(): PMIC is single chip\n", __func__);
	} else {
		pmic_single_chip_flag = 0;
		dprintf("%s(): PMIC is multi-chip\n", __func__);
	}

	pmic_detection_done_flag = 1;
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pmic_chip_get
 * @BRIEF		return the PMIC chip ID of a given power rail.
 * @RETURNS		PMIC chip ID of a given power rail.
 *			PMIC_ID_MAX in case of error.
 * @param[in]		smps_id: valid SMPS ID
 * @DESCRIPTION		return the PMIC chip ID of a given power rail.
 *//*------------------------------------------------------------------------ */
pmic_id pmic_chip_get(pmic_smps_id smps_id)
{
	CHECK_ARG_LESS_THAN(smps_id, PMIC_SMPS_ID_MAX, PMIC_ID_MAX);

	if (!pmic_detection_done())
		pmic_detect();

	return pmic_chip[smps_id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pmic_is_twl6030
 * @BRIEF		return 1 if PMIC chip of a given rail is TWL6030
 * @RETURNS		1 if PMIC chip is TWL6030
 *			0 otherwise
 * @param[in]		smps_id: valid SMPS ID
 * @DESCRIPTION		return 1 if PMIC chip of a given rail is TWL6030
 *//*------------------------------------------------------------------------ */
unsigned short pmic_is_twl6030(pmic_smps_id smps_id)
{
	CHECK_ARG_LESS_THAN(smps_id, PMIC_SMPS_ID_MAX, 0);

	if (!pmic_detection_done())
		pmic_detect();

	return pmic_chip[smps_id] == PMIC_TWL6030;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pmic_is_twl6032
 * @BRIEF		return 1 if PMIC chip of a given rail is TWL6032
 * @RETURNS		1 if PMIC chip is TWL6032
 *			0 otherwise
 * @param[in]		smps_id: valid SMPS ID
 * @DESCRIPTION		return 1 if PMIC chip of a given rail is TWL6032
 *//*------------------------------------------------------------------------ */
unsigned short pmic_is_twl6032(pmic_smps_id smps_id)
{
	CHECK_ARG_LESS_THAN(smps_id, PMIC_SMPS_ID_MAX, 0);

	if (!pmic_detection_done())
		pmic_detect();

	return pmic_chip[smps_id] == PMIC_TWL6032;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pmic_is_twl6034
 * @BRIEF		return 1 if PMIC chip of a given rail is TWL6034
 * @RETURNS		1 if PMIC chip is TWL6034
 *			0 otherwise
 * @param[in]		smps_id: valid SMPS ID
 * @DESCRIPTION		return 1 if PMIC chip of a given rail is TWL6034
 *//*------------------------------------------------------------------------ */
unsigned short pmic_is_twl6034(pmic_smps_id smps_id)
{
	CHECK_ARG_LESS_THAN(smps_id, PMIC_SMPS_ID_MAX, 0);

	if (!pmic_detection_done())
		pmic_detect();

	return pmic_chip[smps_id] == PMIC_TWL6034;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pmic_is_twl6035
 * @BRIEF		return 1 if PMIC chip of a given rail is TWL6035
 * @RETURNS		1 if PMIC chip is TWL6035
 *			0 otherwise
 * @param[in]		smps_id: valid SMPS ID
 * @DESCRIPTION		return 1 if PMIC chip of a given rail is TWL6035
 *//*------------------------------------------------------------------------ */
unsigned short pmic_is_twl6035(pmic_smps_id smps_id)
{
	CHECK_ARG_LESS_THAN(smps_id, PMIC_SMPS_ID_MAX, 0);

	if (!pmic_detection_done())
		pmic_detect();

	return pmic_chip[smps_id] == PMIC_TWL6035;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pmic_is_tps62361
 * @BRIEF		return 1 if PMIC chip of a given rail is TPS62361
 * @RETURNS		1 if PMIC chip is TPS62361
 *			0 otherwise
 * @param[in]		smps_id: valid SMPS ID
 * @DESCRIPTION		return 1 if PMIC chip of a given rail is TPS62361
 *//*------------------------------------------------------------------------ */
unsigned short pmic_is_tps62361(pmic_smps_id smps_id)
{
	CHECK_ARG_LESS_THAN(smps_id, PMIC_SMPS_ID_MAX, 0);

	if (!pmic_detection_done())
		pmic_detect();

	return pmic_chip[smps_id] == PMIC_TPS62361;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pmic_is_tps659038
 * @BRIEF		return 1 if PMIC chip of a given rail is TPS659038
 * @RETURNS		1 if PMIC chip is TPS659038
 *			0 otherwise
 * @param[in]		smps_id: valid SMPS ID
 * @DESCRIPTION		return 1 if PMIC chip of a given rail is TPS659038
 *//*------------------------------------------------------------------------ */
unsigned short pmic_is_tps659038(pmic_smps_id smps_id)
{
	CHECK_ARG_LESS_THAN(smps_id, PMIC_SMPS_ID_MAX, 0);

	if (!pmic_detection_done())
		pmic_detect();

	if (cpu_get() == DRA_72X)
		return pmic_chip[smps_id] == PMIC_TPS65917;

	return pmic_chip[smps_id] == PMIC_TPS659038;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pmic_is_tps65217x
 * @BRIEF		return 1 if PMIC chip of a given rail is TPS65217X
 * @RETURNS		1 if PMIC chip is TPS65217X
 *			0 otherwise
 * @param[in]		smps_id: valid SMPS ID
 * @DESCRIPTION		return 1 if PMIC chip of a given rail is TPS65217X
 *//*------------------------------------------------------------------------ */
unsigned short pmic_is_tps65217x(pmic_smps_id smps_id)
{
	CHECK_ARG_LESS_THAN(smps_id, PMIC_SMPS_ID_MAX, 0);

	if (!pmic_detection_done())
		pmic_detect();

	return pmic_chip[smps_id] == PMIC_TPS65217A || pmic_chip[smps_id] ==
		PMIC_TPS65217B || pmic_chip[smps_id] == PMIC_TPS65217C ||
		pmic_chip[smps_id] == PMIC_TPS65217D;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pmic_is_single_chip
 * @BRIEF		return 1 if all SMPS rails powered by the same PMIC,
 *			0 otherwise.
 * @RETURNS		1 if all SMPS rails powered by the same PMIC chip
 *			0 otherwise
 * @DESCRIPTION		return 1 if all SMPS rails powered by the same PMIC,
 *			0 otherwise.
 *//*------------------------------------------------------------------------ */
unsigned short pmic_is_single_chip(void)
{
	if (!pmic_detection_done())
		pmic_detect();

	return pmic_single_chip_flag;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pmic_chip_revision_get
 * @BRIEF		return the PMIC chip revision of a given power rail.
 * @RETURNS		> 0.0 PMIC chip revision of a given power rail.
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		smps_id: valid SMPS ID
 * @DESCRIPTION		return the PMIC chip revision of a given power rail.
 *//*------------------------------------------------------------------------ */
double pmic_chip_revision_get(pmic_smps_id smps_id)
{
	CHECK_ARG_LESS_THAN(smps_id, PMIC_SMPS_ID_MAX,
		(double) OMAPCONF_ERR_ARG);

	if (!pmic_detection_done())
		pmic_detect();

	return pmic_chip_revision[smps_id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pmic_eprom_revision_get
 * @BRIEF		return the PMIC EPROM revision of a given power rail.
 * @RETURNS		> 0.0 PMIC EPROM revision of a given power rail.
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		smps_id: valid SMPS ID
 * @DESCRIPTION		return the PMIC EPROM revision of a given power rail.
 *//*------------------------------------------------------------------------ */
double pmic_eprom_revision_get(pmic_smps_id smps_id)
{
	CHECK_ARG_LESS_THAN(smps_id, PMIC_SMPS_ID_MAX,
		(double) OMAPCONF_ERR_ARG);

	if (!pmic_detection_done())
		pmic_detect();

	return pmic_eprom_revision[smps_id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		smps_name_get
 * @BRIEF		return PMIC SMPS name as a string
 * @RETURNS		PMIC SMPS name as a string in case of success
 *			NULL in case of error
 * @param[in]		smps_id: valid SMPS ID
 * @DESCRIPTION		return PMIC SMPS name as a string
 *//*------------------------------------------------------------------------ */
const char *smps_name_get(pmic_smps_id smps_id)
{
	CHECK_ARG_LESS_THAN(smps_id, PMIC_SMPS_ID_MAX, NULL);

	switch (cpu_get()) {
	case OMAP_4430:
	case OMAP_4460:
	case OMAP_4470:
		return smps44xx_names[smps_id];
		break;

	case OMAP_5430:
	case OMAP_5432:
		return smps54xx_names[smps_id];
		break;

	case DRA_75X:
	case DRA_72X:
		return smps_dra7xx_names[smps_id];
		break;

	case AM_3352:
	case AM_3354:
	case AM_3356:
	case AM_3357:
	case AM_3358:
	case AM_3359:
		return smps_am335x_names[smps_id];
		break;

	default:
		return smps44xx_names[smps_id];
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		smps_step_get
 * @BRIEF		return SMPS regulator voltage step (in microvolts)
 * @RETURNS		> 0 voltage step in microvolts
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		smps_id: valid SMPS ID
 * @DESCRIPTION		return SMPS regulator voltage step (in microvolts)
 *//*------------------------------------------------------------------------ */
long smps_step_get(pmic_smps_id smps_id)
{
	long step;

	CHECK_ARG_LESS_THAN(smps_id, PMIC_SMPS_ID_MAX, (long) OMAPCONF_ERR_ARG);

	if (!pmic_detection_done())
		pmic_detect();

	switch (pmic_chip[smps_id]) {
	case PMIC_TWL6030:
	case PMIC_TWL6032:
	case PMIC_TWL6034:
	case PMIC_TWL6035:
		step = twl603x_smps_step_get();
		break;
	case PMIC_TPS62361:
		step = tps62361_smps_step_get();
		break;
	case PMIC_TPS659038:
	case PMIC_TPS65917:
		step = tps659038_smps_step_get();
		break;
	case PMIC_TPS65217A:
	case PMIC_TPS65217B:
	case PMIC_TPS65217C:
	case PMIC_TPS65217D:
		step = tps65217x_smps_step_get();
	default:
		step = (long) OMAPCONF_ERR_NOT_AVAILABLE;
	}

	dprintf("%s(%s): step=%lduV\n", __func__, smps_name_get(smps_id), step);
	return step;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		smps_offset_get
 * @BRIEF		return SMPS regulator offset
 * @RETURNS		> 0 voltage offset in microvolts
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		smps_id: valid SMPS ID
 * @DESCRIPTION		return SMPS regulator offset
 *//*------------------------------------------------------------------------ */
long smps_offset_get(pmic_smps_id smps_id)
{
	long offset;

	CHECK_ARG_LESS_THAN(smps_id, PMIC_SMPS_ID_MAX, (long) OMAPCONF_ERR_ARG);

	if (!pmic_detection_done())
		pmic_detect();

	switch (pmic_chip[smps_id]) {
	case PMIC_TWL6030:
	case PMIC_TWL6032:
	case PMIC_TWL6034:
		offset = twl603x_smps_offset_get(smps_id2vdd_id(smps_id));
		break;
	case PMIC_TWL6035:
		offset = twl603x_smps_offset_get((unsigned int) smps_id);
		break;
	case PMIC_TPS62361:
		offset = tps62361_smps_offset_get();
		break;
	case PMIC_TPS659038:
	case PMIC_TPS65917:
		offset = tps659038_smps_offset_get();
		break;
	case PMIC_TPS65217A:
	case PMIC_TPS65217B:
	case PMIC_TPS65217C:
	case PMIC_TPS65217D:
		offset = tps65217x_smps_offset_get();
		break;
	default:
		offset = (long) OMAPCONF_ERR_NOT_AVAILABLE;
	}

	dprintf("%s(%s): offset=%lduV\n", __func__, smps_name_get(smps_id),
		offset);
	return offset;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		smps_vsel_len_get
 * @BRIEF		return the size of the vsel command
 * @RETURNS		> 0 SMPS regulator size of the vsel command
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		smps_id: valid SMPS ID
 * @DESCRIPTION		return the size of the vsel command
 *//*------------------------------------------------------------------------ */
int smps_vsel_len_get(pmic_smps_id smps_id)
{
	int vsel_len;

	CHECK_ARG_LESS_THAN(smps_id, PMIC_SMPS_ID_MAX, (int) OMAPCONF_ERR_ARG);

	if (!pmic_detection_done())
		pmic_detect();

	switch (pmic_chip[smps_id]) {
	case PMIC_TWL6030:
	case PMIC_TWL6032:
	case PMIC_TWL6034:
	case PMIC_TWL6035:
		vsel_len = twl603x_vsel_len_get();
		break;
	case PMIC_TPS62361:
		vsel_len = tps62361_vsel_len_get();
		break;
	case PMIC_TPS659038:
	case PMIC_TPS65917:
		vsel_len = tps659038_vsel_len_get();
		break;
	case PMIC_TPS65217A:
	case PMIC_TPS65217B:
	case PMIC_TPS65217C:
	case PMIC_TPS65217D:
		vsel_len = tps65217x_vsel_len_get();
		break;
	default:
		vsel_len = (long) OMAPCONF_ERR_NOT_AVAILABLE;
	}

	dprintf("%s(%s): vsel_len=%u\n", __func__,
		smps_name_get(smps_id), vsel_len);
	return vsel_len;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		smps_uvolt2vsel
 * @BRIEF		for a given rail, convert voltage in microvolts into
 *			SMPS vsel command.
 * @RETURNS		>= 0 SMPS vsel command corresponding to uv
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		smps_id: valid SMPS ID
 * @param[in]		uvolt: voltage to be converted (in microvolts)
 * @DESCRIPTION		for a given rail, convert voltage in microvolts into
 *			SMPS vsel command.
 *//*------------------------------------------------------------------------ */
int smps_uvolt2vsel(pmic_smps_id smps_id, unsigned long uvolt)
{
	int vsel;
	CHECK_ARG_LESS_THAN(smps_id, PMIC_SMPS_ID_MAX, (int) OMAPCONF_ERR_ARG);

	if (!pmic_detection_done())
		pmic_detect();

	switch (pmic_chip[smps_id]) {
	case PMIC_TWL6030:
	case PMIC_TWL6032:
	case PMIC_TWL6034:
		vsel = (int) twl603x_uv_to_vsel(smps_id2vdd_id(smps_id), uvolt);
		break;
	case PMIC_TWL6035:
		vsel = (int) twl603x_uv_to_vsel((unsigned int) smps_id, uvolt);
		break;
	case PMIC_TPS62361:
		vsel = (int) tps62361_uv_to_vsel(uvolt);
		break;
	case PMIC_TPS659038:
	case PMIC_TPS65917:
		vsel = (int) tps659038_uv_to_vsel(uvolt);
		break;
	case PMIC_TPS65217A:
	case PMIC_TPS65217B:
	case PMIC_TPS65217C:
	case PMIC_TPS65217D:
		vsel = (int) tps65217x_uv_to_vsel(uvolt);
		break;
	default:
		vsel = (int) OMAPCONF_ERR_NOT_AVAILABLE;
	}

	dprintf("%s(%s): uvolt=%lu vsel=%u (0x%08X)\n", __func__,
		smps_name_get(smps_id), uvolt, vsel, vsel);
	return vsel;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		smps_vsel2uvolt
 * @BRIEF		for a given rail, convert SMPS vsel command into voltage
 *			in microvolts.
 * @RETURNS		>= 0 voltage in microvolts corresponding to SMPS vsel
 *			command.
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		smps_id: valid SMPS ID
 * @param[in]		vsel: SMPS vsel command
 * @DESCRIPTION		for a given rail, convert SMPS vsel command into voltage
 *			in microvolts.
 *//*------------------------------------------------------------------------ */
long smps_vsel2uvolt(pmic_smps_id smps_id, unsigned char vsel)
{
	long uvolt;

	CHECK_ARG_LESS_THAN(smps_id, PMIC_SMPS_ID_MAX, (long) OMAPCONF_ERR_ARG);

	if (!pmic_detection_done())
		pmic_detect();

	switch (pmic_chip[smps_id]) {
	case PMIC_TWL6030:
	case PMIC_TWL6032:
	case PMIC_TWL6034:
		uvolt = twl603x_vsel_to_uv(smps_id2vdd_id(smps_id), vsel);
		break;
	case PMIC_TWL6035:
		uvolt = twl603x_vsel_to_uv((unsigned int) smps_id, vsel);
		break;
	case PMIC_TPS62361:
		uvolt = tps62361_vsel_to_uv(vsel);
		break;
	case PMIC_TPS659038:
	case PMIC_TPS65917:
		uvolt = tps659038_vsel_to_uv(vsel);
		break;
	case PMIC_TPS65217A:
	case PMIC_TPS65217B:
	case PMIC_TPS65217C:
	case PMIC_TPS65217D:
		uvolt = tps65217x_vsel_to_uv(vsel);
		break;
	default:
		uvolt = (long) OMAPCONF_ERR_NOT_AVAILABLE;
	}

	dprintf("%s(%s): =%lduV\n", __func__, smps_name_get(smps_id),
		uvolt);
	return uvolt;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		smps_vsel2volt
 * @BRIEF		for a given rail, convert SMPS vsel command into voltage
 *			(in VOLTS).
 * @RETURNS		>= 0 voltage in VOLTS corresponding to SMPS vsel command
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		smps_id: valid SMPS ID
 * @param[in]		vsel: SMPS vsel command
 * @DESCRIPTION		for a given rail, convert SMPS vsel command into voltage
 *			(in VOLTS).
 *//*------------------------------------------------------------------------ */
double smps_vsel2volt(pmic_smps_id smps_id, unsigned char vsel)
{
	double volt;

	volt = (double) smps_vsel2uvolt(smps_id, vsel);
	volt /= (double) 1000000.0;

	dprintf("%s(%s, 0x%X) = %lfV\n", __func__,
		smps_name_get(smps_id), vsel, volt);
	return volt;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		smps_voltage_round
 * @BRIEF		for a given rail, convert RAW voltage
 *			(e.g from Data Manual) into stepped SMPS voltage
 *			(in micro-volt).
 * @RETURNS		>= 0 voltage in microvolt rounded to SMPS voltage
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		smps_id: valid SMPS ID
 * @param[in]		uvolt: RAW voltage in microvolt
 * @DESCRIPTION		for a given rail, convert RAW voltage
 *			(e.g from Data Manual) into stepped SMPS voltage
 *			(in microvolt).
 *//*------------------------------------------------------------------------ */
long smps_voltage_round(pmic_smps_id smps_id, long uvolt)
{
	long rounded_uvolt;
	int vsel;

	CHECK_ARG_LESS_THAN(smps_id, PMIC_SMPS_ID_MAX, (long) OMAPCONF_ERR_ARG);
	if (uvolt < 0)
		return (long) OMAPCONF_ERR_ARG;

	vsel = smps_uvolt2vsel(smps_id, uvolt);
	rounded_uvolt = smps_vsel2uvolt(smps_id, vsel);

	dprintf("%s(%s, %lduV) = %lduV (vsel=%d)\n",
		__func__, smps_name_get(smps_id), uvolt, rounded_uvolt, vsel);
	return rounded_uvolt;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		smps_vsel_get
 * @BRIEF		return VSEL-encoded voltage of a given SMPS voltage rail
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		smps_id: SMPS ID
 * @DESCRIPTION		return VSEL-encoded voltage of a given SMPS voltage rail
 *//*------------------------------------------------------------------------ */
int smps_vsel_get(pmic_smps_id smps_id)
{
	if (pmic_is_twl6035(smps_id))
		return twl603x_vsel_get((unsigned int) smps_id);
	else if (pmic_is_tps659038(smps_id))
		return tps659038_vsel_get((unsigned int) smps_id);
	else if (pmic_is_tps65217x(smps_id))
		return tps65217x_vsel_get((unsigned int) smps_id);

	return OMAPCONF_ERR_NOT_AVAILABLE;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		smps_uvoltage_get
 * @BRIEF		return voltage of a given SMPS voltage rail.
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		smps_id: SMPS ID
 * @DESCRIPTION		return voltage of a given SMPS voltage rail.
 *//*------------------------------------------------------------------------ */
unsigned long smps_uvoltage_get(pmic_smps_id smps_id)
{
	int vsel;

	if (!pmic_is_twl6035(smps_id) && !pmic_is_tps659038(smps_id) &&
		!pmic_is_tps65217x(smps_id))
		return OMAPCONF_ERR_NOT_AVAILABLE;

	vsel = smps_vsel_get(smps_id);
	if (vsel < 0)
		return 0;

	return smps_vsel2uvolt(smps_id, vsel);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		smps_voltage_get
 * @BRIEF		return voltage of a given SMPS voltage rail in volt.
 * @RETURNS		>= 0 voltage in volt
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		smps_id: SMPS ID
 * @DESCRIPTION		return voltage of a given SMPS voltage rail in volt.
 *//*------------------------------------------------------------------------ */
double smps_voltage_get(pmic_smps_id smps_id)
{
	int vsel;

	if (!pmic_is_twl6035(smps_id) && !pmic_is_tps659038(smps_id) &&
		!pmic_is_tps65217x(smps_id))
		return OMAPCONF_ERR_NOT_AVAILABLE;

	vsel = smps_vsel_get(smps_id);
	if (vsel < 0)
		return 0;

	return (double) smps_vsel2uvolt(smps_id, vsel) / 1000000.0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		smps_voltage_set
 * @BRIEF		set voltage of a given SMPS voltage rail.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		smps_id: SMPS ID
 * @param[in]		uv: voltage to be set (in micro-volt)
 * @DESCRIPTION		set voltage of a given SMPS voltage rail, in micro-volt.
 *//*------------------------------------------------------------------------ */
int smps_voltage_set(pmic_smps_id smps_id, unsigned long uvolt)
{
	if (!pmic_is_twl6035(smps_id) && !pmic_is_tps659038(smps_id))
		return OMAPCONF_ERR_NOT_AVAILABLE;

	if (pmic_is_twl6035(smps_id))
		return twl603x_uvoltage_set((unsigned int) smps_id, uvolt);
	else
		return tps659038_uvoltage_set((unsigned int) smps_id, uvolt);
}
