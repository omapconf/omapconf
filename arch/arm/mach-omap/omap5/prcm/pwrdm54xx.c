/*
 *
 * @Component			OMAPCONF
 * @Filename			pwrdm54xx.c
 * @Description			OMAP5 Power Domain Definitions & APIs
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


#include <pwrdm.h>
#include <powerdomain.h>
#include <voltdomain.h>
#include <pwrdm54xx.h>
#include <lib.h>
#include <string.h>
#include <prm54xx.h>
#include <clock54xx.h>
#include <string.h>
#include <stdio.h>
#include <cpuinfo.h>


/* #define PWRDM54XX_DEBUG */
#ifdef PWRDM54XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


const char
	pwrdm54xx_names_table[PWRDM54XX_ID_MAX][PWRDM54XX_MAX_NAME_LENGTH] = {
	"EMU",
	"WKUPAON",
	"COREAON",
	"CAM",
	"CORE",
	"DSS",
	"CUST_EFUSE",
	"L3INIT",
	"L4PER",
	"ABE",
	"DSP",
	"GPU",
	"MMAON",
	"IVA",
	"MPUAON",
	"MPU"};


static const voltdm54xx_id pwrdm54xx_partition_table[PWRDM54XX_ID_MAX] = {
	VDD54XX_WKUP,
	VDD54XX_WKUP,
	VDD54XX_CORE,
	VDD54XX_CORE,
	VDD54XX_CORE,
	VDD54XX_CORE,
	VDD54XX_CORE,
	VDD54XX_CORE,
	VDD54XX_CORE,
	VDD54XX_CORE,
	VDD54XX_MM,
	VDD54XX_MM,
	VDD54XX_MM,
	VDD54XX_MM,
	VDD54XX_MPU,
	VDD54XX_MPU};


static reg *pwrdm54xx_pwrstctrl_table[PWRDM54XX_ID_MAX] = {
	&omap5430es1_pm_emu_pwrstctrl,	/* PWRDM54XX_EMU */
	NULL,				/* PWRDM54XX_WKUPAON */
	NULL,				/* PWRDM54XX_COREAON */
	&omap5430es1_pm_cam_pwrstctrl,	/* PWRDM54XX_CAM */
	&omap5430es1_pm_core_pwrstctrl,	/* PWRDM54XX_CORE */
	&omap5430es1_pm_dss_pwrstctrl,	/* PWRDM54XX_DSS */
	&omap5430es1_pm_custefuse_pwrstctrl, /* PWRDM54XX_CUST_EFUSE */
	&omap5430es1_pm_l3init_pwrstctrl,	/* PWRDM54XX_L3_INIT */
	&omap5430es1_pm_l4per_pwrstctrl,	/* PWRDM54XX_L4_PER */
	&omap5430es1_pm_abe_pwrstctrl,	/* PWRDM54XX_ABE */
	&omap5430es1_pm_dsp_pwrstctrl,	/* PWRDM54XX_DSP */
	&omap5430es1_pm_gpu_pwrstctrl,	/* PWRDM54XX_GPU */
	NULL,				/* PWRDM54XX_MMAON */
	&omap5430es1_pm_iva_pwrstctrl,	/* PWRDM54XX_IVA */
	NULL,				/* PWRDM54XX_MPUAON */
	&omap5430es1_pm_mpu_pwrstctrl,	/* PWRDM54XX_MPU */};


static reg *pwrdm54xx_pwrstst_table[PWRDM54XX_ID_MAX] = {
	&omap5430es1_pm_emu_pwrstst,	/* PWRDM54XX_EMU */
	NULL,				/* PWRDM54XX_WKUPAON */
	NULL,				/* PWRDM54XX_COREAON */
	&omap5430es1_pm_cam_pwrstst,	/* PWRDM54XX_CAM */
	&omap5430es1_pm_core_pwrstst,	/* PWRDM54XX_CORE */
	&omap5430es1_pm_dss_pwrstst,	/* PWRDM54XX_DSS */
	&omap5430es1_pm_custefuse_pwrstst,	/* PWRDM54XX_CUST_EFUSE */
	&omap5430es1_pm_l3init_pwrstst,	/* PWRDM54XX_L3_INIT */
	&omap5430es1_pm_l4per_pwrstst,	/* PWRDM54XX_L4_PER */
	&omap5430es1_pm_abe_pwrstst,	/* PWRDM54XX_ABE */
	&omap5430es1_pm_dsp_pwrstst,	/* PWRDM54XX_DSP */
	&omap5430es1_pm_gpu_pwrstst,	/* PWRDM54XX_GPU */
	NULL,				/* PWRDM54XX_MMAON */
	&omap5430es1_pm_iva_pwrstst,	/* PWRDM54XX_IVA */
	NULL,				/* PWRDM54XX_MPUAON */
	&omap5430es1_pm_mpu_pwrstst,	/* PWRDM54XX_MPU */};



static const unsigned int pwrdm54xx_properties_table[PWRDM54XX_ID_MAX] = {
	PWRDM_HAS_LAST_STATE, /* PWRDM54XX_EMU */
	0, /* PWRDM54XX_WKUPAON */
	0, /* PWRDM54XX_COREAON */
	PWRDM_HAS_LAST_STATE,	/* PWRDM54XX_CAM */
	PWRDM_HAS_LAST_STATE | PWRDM_HAS_LOGIC_RET_STATE_CTRL_BIT, /* PWRDM54XX_CORE */
	PWRDM_HAS_LAST_STATE | PWRDM_HAS_LOGIC_RET_STATE_CTRL_BIT, /* PWRDM54XX_DSS */
	PWRDM_HAS_LAST_STATE,	/* PWRDM54XX_CUST_EFUSE */
	PWRDM_HAS_LAST_STATE | PWRDM_HAS_LOGIC_RET_STATE_CTRL_BIT, /* PWRDM54XX_L3_INIT */
	PWRDM_HAS_LAST_STATE | PWRDM_HAS_LOGIC_RET_STATE_CTRL_BIT, /* PWRDM54XX_L4_PER */
	PWRDM_HAS_LAST_STATE | PWRDM_HAS_LOGIC_RET_STATE_CTRL_BIT, /* PWRDM54XX_ABE */
	PWRDM_HAS_LAST_STATE | PWRDM_HAS_LOGIC_RET_STATE_CTRL_BIT, /* PWRDM54XX_DSP */
	PWRDM_HAS_LAST_STATE, /* PWRDM54XX_GPU */
	0, /* PWRDM54XX_MMAON */
	PWRDM_HAS_LAST_STATE | PWRDM_HAS_LOGIC_RET_STATE_CTRL_BIT, /* PWRDM54XX_IVA */
	0, /* PWRDM54XX_MPUAON */
	PWRDM_HAS_LAST_STATE | PWRDM_HAS_LOGIC_RET_STATE_CTRL_BIT, /* PWRDM54XX_MPU */};


static unsigned short pwrdm54xx_init_done = 0;
genlist pwrdm54xx_list;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm54xx_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void pwrdm54xx_init(void)
{
	powerdm_info pwrdm;

	if (pwrdm54xx_init_done)
		return;

	genlist_init(&pwrdm54xx_list);

	pwrdm.name = PWRDM_EMU;
	pwrdm.id = (int) PWRDM54XX_EMU;
	pwrdm.voltdm = VDD_WKUP;
	pwrdm.pwrstctrl = &omap5430es1_pm_emu_pwrstctrl;
	pwrdm.pwrstst = &omap5430es1_pm_emu_pwrstst;
	pwrdm.properties = PWRDM_HAS_LAST_STATE;
	genlist_addtail(&pwrdm54xx_list, (void *) &pwrdm, sizeof(powerdm_info));

	pwrdm.name = PWRDM_WKUPAON;
	pwrdm.id = (int) PWRDM54XX_WKUPAON;
	pwrdm.voltdm = VDD_WKUP;
	pwrdm.pwrstctrl = NULL;
	pwrdm.pwrstst = NULL;
	pwrdm.properties = 0;
	genlist_addtail(&pwrdm54xx_list, (void *) &pwrdm, sizeof(powerdm_info));

	pwrdm.name = PWRDM_COREAON;
	pwrdm.id = (int) PWRDM54XX_COREAON;
	pwrdm.voltdm = VDD_CORE;
	pwrdm.pwrstctrl = NULL;
	pwrdm.pwrstst = NULL;
	pwrdm.properties = 0;
	genlist_addtail(&pwrdm54xx_list, (void *) &pwrdm, sizeof(powerdm_info));

	pwrdm.name = PWRDM_CAM;
	pwrdm.id = (int) PWRDM54XX_CAM;
	pwrdm.voltdm = VDD_CORE;
	pwrdm.pwrstctrl = &omap5430es1_pm_cam_pwrstctrl;
	pwrdm.pwrstst = &omap5430es1_pm_cam_pwrstst;
	pwrdm.properties = PWRDM_HAS_LAST_STATE;
	genlist_addtail(&pwrdm54xx_list, (void *) &pwrdm, sizeof(powerdm_info));

	pwrdm.name = PWRDM_CORE;
	pwrdm.id = (int) PWRDM54XX_CORE;
	pwrdm.voltdm = VDD_CORE;
	pwrdm.pwrstctrl = &omap5430es1_pm_core_pwrstctrl;
	pwrdm.pwrstst = &omap5430es1_pm_core_pwrstst;
	pwrdm.properties = PWRDM_HAS_LAST_STATE | PWRDM_HAS_LOGIC_RET_STATE_CTRL_BIT;
	genlist_addtail(&pwrdm54xx_list, (void *) &pwrdm, sizeof(powerdm_info));

	pwrdm.name = PWRDM_DSS;
	pwrdm.id = (int) PWRDM54XX_DSS;
	pwrdm.voltdm = VDD_CORE;
	pwrdm.pwrstctrl = &omap5430es1_pm_dss_pwrstctrl;
	pwrdm.pwrstst = &omap5430es1_pm_dss_pwrstst;
	pwrdm.properties = PWRDM_HAS_LAST_STATE | PWRDM_HAS_LOGIC_RET_STATE_CTRL_BIT;
	genlist_addtail(&pwrdm54xx_list, (void *) &pwrdm, sizeof(powerdm_info));

	pwrdm.name = PWRDM_CUST_EFUSE;
	pwrdm.id = (int) PWRDM54XX_CUST_EFUSE;
	pwrdm.voltdm = VDD_CORE;
	pwrdm.pwrstctrl = &omap5430es1_pm_custefuse_pwrstctrl;
	pwrdm.pwrstst = &omap5430es1_pm_custefuse_pwrstst;
	pwrdm.properties = PWRDM_HAS_LAST_STATE;
	genlist_addtail(&pwrdm54xx_list, (void *) &pwrdm, sizeof(powerdm_info));

	pwrdm.name = PWRDM_L3_INIT;
	pwrdm.id = (int) PWRDM54XX_L3_INIT;
	pwrdm.voltdm = VDD_CORE;
	pwrdm.pwrstctrl = &omap5430es1_pm_l3init_pwrstctrl;
	pwrdm.pwrstst = &omap5430es1_pm_l3init_pwrstst;
	pwrdm.properties = PWRDM_HAS_LAST_STATE | PWRDM_HAS_LOGIC_RET_STATE_CTRL_BIT;
	genlist_addtail(&pwrdm54xx_list, (void *) &pwrdm, sizeof(powerdm_info));

	if (cpu_revision_get() == REV_ES1_0) {
		pwrdm.name = PWRDM_L4_PER;
		pwrdm.id = (int) PWRDM54XX_L4_PER;
		pwrdm.voltdm = VDD_CORE;
		pwrdm.pwrstctrl = &omap5430es1_pm_l4per_pwrstctrl;
		pwrdm.pwrstst = &omap5430es1_pm_l4per_pwrstst;
		pwrdm.properties = PWRDM_HAS_LAST_STATE | PWRDM_HAS_LOGIC_RET_STATE_CTRL_BIT;
		genlist_addtail(&pwrdm54xx_list, (void *) &pwrdm, sizeof(powerdm_info));
	}

	pwrdm.name = PWRDM_ABE;
	pwrdm.id = (int) PWRDM54XX_ABE;
	pwrdm.voltdm = VDD_CORE;
	pwrdm.pwrstctrl = &omap5430es1_pm_abe_pwrstctrl;
	pwrdm.pwrstst = &omap5430es1_pm_abe_pwrstst;
	pwrdm.properties = PWRDM_HAS_LAST_STATE | PWRDM_HAS_LOGIC_RET_STATE_CTRL_BIT;
	genlist_addtail(&pwrdm54xx_list, (void *) &pwrdm, sizeof(powerdm_info));

	pwrdm.name = PWRDM_DSP;
	pwrdm.id = (int) PWRDM54XX_DSP;
	pwrdm.voltdm = VDD_MM;
	pwrdm.pwrstctrl = &omap5430es1_pm_dsp_pwrstctrl;
	pwrdm.pwrstst = &omap5430es1_pm_dsp_pwrstst;
	pwrdm.properties = PWRDM_HAS_LAST_STATE | PWRDM_HAS_LOGIC_RET_STATE_CTRL_BIT;
	genlist_addtail(&pwrdm54xx_list, (void *) &pwrdm, sizeof(powerdm_info));

	pwrdm.name = PWRDM_GPU;
	pwrdm.id = (int) PWRDM54XX_GPU;
	pwrdm.voltdm = VDD_MM;
	pwrdm.pwrstctrl = &omap5430es1_pm_gpu_pwrstctrl;
	pwrdm.pwrstst = &omap5430es1_pm_gpu_pwrstst;
	pwrdm.properties = PWRDM_HAS_LAST_STATE;
	genlist_addtail(&pwrdm54xx_list, (void *) &pwrdm, sizeof(powerdm_info));

	pwrdm.name = PWRDM_MMAON;
	pwrdm.id = (int) PWRDM54XX_MMAON;
	pwrdm.voltdm = VDD_MM;
	pwrdm.pwrstctrl = NULL;
	pwrdm.pwrstst = NULL;
	pwrdm.properties = 0;
	genlist_addtail(&pwrdm54xx_list, (void *) &pwrdm, sizeof(powerdm_info));

	pwrdm.name = PWRDM_IVA;
	pwrdm.id = (int) PWRDM54XX_IVA;
	pwrdm.voltdm = VDD_MM;
	pwrdm.pwrstctrl = &omap5430es1_pm_iva_pwrstctrl;
	pwrdm.pwrstst = &omap5430es1_pm_iva_pwrstst;
	pwrdm.properties = PWRDM_HAS_LAST_STATE;
	genlist_addtail(&pwrdm54xx_list, (void *) &pwrdm, sizeof(powerdm_info));

	pwrdm.name = PWRDM_MPUAON;
	pwrdm.id = (int) PWRDM54XX_MPUAON;
	pwrdm.voltdm = VDD_MPU;
	pwrdm.pwrstctrl = NULL;
	pwrdm.pwrstst = NULL;
	pwrdm.properties = 0;
	genlist_addtail(&pwrdm54xx_list, (void *) &pwrdm, sizeof(powerdm_info));

	pwrdm.name = PWRDM_MPU;
	pwrdm.id = (int) PWRDM54XX_MPU;
	pwrdm.voltdm = VDD_MPU;
	pwrdm.pwrstctrl = &omap5430es1_pm_mpu_pwrstctrl;
	pwrdm.pwrstst = &omap5430es1_pm_mpu_pwrstst;
	pwrdm.properties = PWRDM_HAS_LAST_STATE;
	genlist_addtail(&pwrdm54xx_list, (void *) &pwrdm, sizeof(powerdm_info));

	pwrdm54xx_init_done = 1;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm54xx_deinit
 * @BRIEF		free dynamically allocated internal data.
 * @DESCRIPTION		free dynamically allocated internal data.
 *			MUST BE CALLED AT END OF EXECUTION.
 *//*------------------------------------------------------------------------ */
void pwrdm54xx_deinit(void)
{
	if (pwrdm54xx_init_done) {
		genlist_free(&pwrdm54xx_list);
		pwrdm54xx_init_done = 0;

	}
	dprintf("%s(): deinit done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm54xx_list_get
 * @BRIEF		return the list of power domains
 * @RETURNS		list of power domains in case of success
 *			NULL in case of error
 * @DESCRIPTION		return the list of power domains
 *//*------------------------------------------------------------------------ */
const genlist *pwrdm54xx_list_get(void)
{
	pwrdm54xx_init();

	return (const genlist *) &pwrdm54xx_list;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm54xx_count_get
 * @BRIEF		return the number of power domains
 * @RETURNS		number of power domains (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @DESCRIPTION		return the number of power domains
 *//*------------------------------------------------------------------------ */
int pwrdm54xx_count_get(void)
{
	int count;

	pwrdm54xx_init();

	count = genlist_getcount(&pwrdm54xx_list);

	dprintf("%s() = %d\n", __func__, count);
	return count;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm54xx_name_get
 * @BRIEF		return power domain name
 * @RETURNS		power domain name on success
 *			NULL in case of error
 * @param[in]		id: valid power domain ID
 * @DESCRIPTION		return power domain name
 *//*------------------------------------------------------------------------ */
const char *pwrdm54xx_name_get(pwrdm54xx_id id)
{
	CHECK_ARG_LESS_THAN(id, PWRDM54XX_ID_MAX, NULL);

	return pwrdm54xx_names_table[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm54xx_voltdm_get
 * @BRIEF		return the ID of the voltage domain a given
 *			power domain is part of.
 * @RETURNS		voltage domain ID a given power domain is part of
 *			(< OMAP5_VD_ID_MAX)
 *			VDD54XX_ID_MAX in case of error
 * @param[in]		id: valid power domain ID
 * @DESCRIPTION		return the ID of the voltage domain a given
 *			power domain is part of.
 *//*------------------------------------------------------------------------ */
voltdm54xx_id pwrdm54xx_voltdm_get(pwrdm54xx_id id)
{
	CHECK_ARG_LESS_THAN(id, PWRDM54XX_ID_MAX, VDD54XX_ID_MAX);

	return pwrdm54xx_partition_table[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm54xx_state_get
 * @BRIEF		extract power domain state from register
 * @RETURNS		power domain state on success
 *			PWRDM_STATE_MAX in case of error
 * @param[in]		id: valid power domain ID
 * @param[in]		type: valid power domain state type
 * @DESCRIPTION		extract power domain state from register
 *//*------------------------------------------------------------------------ */
pwrdm_state pwrdm54xx_state_get(pwrdm54xx_id id, pwrdm_state_type type)
{
	reg *pm_pwrst;

	CHECK_CPU(54xx, PWRDM_STATE_MAX);
	CHECK_ARG_LESS_THAN(id, PWRDM54XX_ID_MAX, PWRDM_STATE_MAX);

	/* Retrieve registers address */
	if (type == PWRDM_STATE_TARGET)
		pm_pwrst = pwrdm54xx_pwrstctrl_table[id];
	else
		pm_pwrst = pwrdm54xx_pwrstst_table[id];
	if (pm_pwrst == NULL) {
		/* Always ON domain */
		dprintf("%s(%s): Always ON domain\n", __func__,
			pwrdm54xx_name_get(id));
		return PWRDM_ON_STATE;
	}

	/* Retrieve power domain state */
	return pwrdm_state_get(pm_pwrst, type);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm54xx_properties_get
 * @BRIEF		return power domain properties, stored in
 *			pwrdm54xx_properties_table.
 * @RETURNS		power domain properties
 * @param[in]		id: valid power domain ID
 * @DESCRIPTION		return power domain properties, stored in
 *			pwrdm54xx_properties_table.
 *			Return 0 if not available or in case of error.
 *			Does not make any access to any register.
 *//*------------------------------------------------------------------------ */
unsigned int pwrdm54xx_properties_get(pwrdm54xx_id id)
{
	if (!cpu_is_omap54xx()) {
		fprintf(stderr, "%s(): CPU != 54XX\n", __func__);
		return 0;
	}

	if (id >= PWRDM54XX_ID_MAX) {
		fprintf(stderr, "%s(): id=%u >= PWRDM54XX_ID_MAX (%u)\n",
			__func__, id, PWRDM54XX_ID_MAX);
		return 0;
	}

	dprintf("%s(%u (%s)): power domain properties=0x%04X\n", __func__, id,
			pwrdm54xx_name_get(id), pwrdm54xx_properties_table[id]);
	return pwrdm54xx_properties_table[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm54xx_has_pwrstctrl_reg
 * @BRIEF		return 1 if power domain features PM_xyz_PWRSTCTRL,
 *			0 otherwise.
 * @RETURNS		1 if power domain features PM_xyz_PWRSTCTRL register
 *			0 otherwise
 * @param[in]		id: valid power domain ID
 * @DESCRIPTION		return 1 if power domain features PM_xyz_PWRSTCTRL,
 *			0 otherwise.
 *//*------------------------------------------------------------------------ */
unsigned int pwrdm54xx_has_pwrstctrl_reg(pwrdm54xx_id id)
{
	if (!cpu_is_omap54xx())
		return 0;
	CHECK_ARG_LESS_THAN(id, PWRDM54XX_ID_MAX, 0);

	return (pwrdm54xx_pwrstctrl_table[id] != NULL);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm54xx_has_pwrstst_reg
 * @BRIEF		return 1 if power domain features PM_xyz_PWRSTST,
 *			0 otherwise.
 * @RETURNS		1 if power domain features PM_xyz_PWRSTST register
 *			0 otherwise
 * @param[in]		id: valid power domain ID
 * @DESCRIPTION		return 1 if power domain features PM_xyz_PWRSTST,
 *			0 otherwise.
 *//*------------------------------------------------------------------------ */
unsigned int pwrdm54xx_has_pwrstst_reg(pwrdm54xx_id id)
{
	if (!cpu_is_omap54xx())
		return 0;
	CHECK_ARG_LESS_THAN(id, PWRDM54XX_ID_MAX, 0);

	return (pwrdm54xx_pwrstst_table[id] != NULL);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm54xx_pwrstctrl_reg_get
 * @BRIEF		return pointer to power domain PM_xyz_PWRSTCTRL register
 * @RETURNS		pointer to power domain PM_xyz_PWRSTCTRL register
 *			NULL in case of error
 * @param[in]		id: valid power domain ID
 * @DESCRIPTION		return pointer to power domain PM_xyz_PWRSTCTRL register
 *//*------------------------------------------------------------------------ */
reg *pwrdm54xx_pwrstctrl_reg_get(pwrdm54xx_id id)
{
	if (!cpu_is_omap54xx())
		return NULL;
	CHECK_ARG_LESS_THAN(id, PWRDM54XX_ID_MAX, NULL);

	return pwrdm54xx_pwrstctrl_table[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm54xx_pwrstst_reg_get
 * @BRIEF		return pointer to power domain PM_xyz_PWRSTST register.
 * @RETURNS		pointer to power domain PM_xyz_PWRSTST register
 *			NULL in case of error
 * @param[in]		id: valid power domain ID
 * @DESCRIPTION		return pointer to power domain PM_xyz_PWRSTST register.
 *//*------------------------------------------------------------------------ */
reg *pwrdm54xx_pwrstst_reg_get(pwrdm54xx_id id)
{
	if (!cpu_is_omap54xx())
		return NULL;
	CHECK_ARG_LESS_THAN(id, PWRDM54XX_ID_MAX, NULL);

	return pwrdm54xx_pwrstst_table[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm54xx_has_last_power_state
 * @BRIEF		return 1 if power domain has LASTPOWERSTATEENTERED
 * @RETURNS		1 if power domain has a LASTPOWERSTATEENTERED bitfield.
 *			0 if not available or in case of error.
 * @param[in]		id: valid power domain ID
 * @DESCRIPTION		return 1 if power domain has LASTPOWERSTATEENTERED
 *			in PM_xyz_PWRSTST register (not all power domains
 *			feature it).
 *			Return 0 if not available or in case of error.
 *			Does not make any access to any register.
 *//*------------------------------------------------------------------------ */
unsigned int pwrdm54xx_has_last_power_state(pwrdm54xx_id id)
{
	unsigned int prop;

	if (!cpu_is_omap54xx()) {
		fprintf(stderr, "%s(): CPU != 54XX\n", __func__);
		return 0;
	}

	if (id >= PWRDM54XX_ID_MAX) {
		fprintf(stderr, "%s(): id=%u >= PWRDM54XX_ID_MAX (%u)\n",
			__func__, id, PWRDM54XX_ID_MAX);
		return 0;
	}

	prop = pwrdm54xx_properties_get(id);
	if ((prop & PWRDM_HAS_LAST_STATE) != 0) {
		dprintf("%s(%u): mod %s HAS LASTPOWERSTATEENTERED bitfield\n",
			__func__, id, pwrdm54xx_name_get(id));
		return 1;
	} else {
		dprintf("%s(%u): mod %s does NOT have LASTPOWERSTATEENTERED"
			" bitfield\n", __func__, id, pwrdm54xx_name_get(id));
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm54xx_has_logic_ret_state_ctrl_bit
 * @BRIEF		return 1 if power domain has LOGICRETSTATE bitfield
 * @RETURNS		1 if power domain has a LOGICRETSTATE bitfield.
 *			0 if not available or in case of error.
 * @param[in]		id: valid power domain ID
 * @DESCRIPTION		return 1 if power domain has LOGICRETSTATE bitfield
 *			in PM_xyz_PWRSTCTRL register (not all power domains
 *			feature it).
 *			Return 0 if not available or in case of error.
 *			Does not make any access to any register.
 *//*------------------------------------------------------------------------ */
unsigned int pwrdm54xx_has_logic_ret_state_ctrl_bit(pwrdm54xx_id id)
{
	unsigned int prop;

	if (!cpu_is_omap54xx()) {
		fprintf(stderr, "%s(): CPU != 54XX\n", __func__);
		return 0;
	}

	if (id >= PWRDM54XX_ID_MAX) {
		fprintf(stderr, "%s(): id=%u >= PWRDM54XX_ID_MAX (%u)\n",
			__func__, id, PWRDM54XX_ID_MAX);
		return 0;
	}

	prop = pwrdm54xx_properties_get(id);
	if ((prop & PWRDM_HAS_LOGIC_RET_STATE_CTRL_BIT) != 0) {
		dprintf("%s(%u): mod %s HAS LOGICRETSTATE bitfield\n",
			__func__, id, pwrdm54xx_name_get(id));
		return 1;
	} else {
		dprintf("%s(%u): mod %s does NOT have LOGICRETSTATE"
			" bitfield\n", __func__, id, pwrdm54xx_name_get(id));
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm54xx_target_logic_ret_state_get
 * @BRIEF		return logic target state for this power domain when
 *			domain is RET
 * @RETURNS		power domain logic state when domain is RET:
 *			PWRDM_OFF_STATE or PWRDM_RET_STATE
 *			PWRDM_STATE_MAX in case of error
 * @param[in]		id: valid power domain ID
 * @DESCRIPTION		return logic target state for this power domain when
 *			domain is RET
 *//*------------------------------------------------------------------------ */
pwrdm_state pwrdm54xx_target_logic_ret_state_get(pwrdm54xx_id id)
{
	reg *pm_pwrstctrl;

	if (!cpu_is_omap54xx()) {
		fprintf(stderr, "%s(): CPU != 54XX\n", __func__);
		return PWRDM_STATE_MAX;
	}
	CHECK_ARG_LESS_THAN(id, PWRDM54XX_ID_MAX, PWRDM_STATE_MAX);

	if (!pwrdm54xx_has_logic_ret_state_ctrl_bit(id))
		return PWRDM_STATE_MAX;

	/* Retrieve PM_xyz_PWRSTCTRL pointer */
	pm_pwrstctrl = pwrdm54xx_pwrstctrl_reg_get(id);
	if (pm_pwrstctrl == NULL)
		return PWRDM_STATE_MAX;
	else
		/* Retrieve logic target state */
		return pwrdm_target_logic_ret_state_get(pm_pwrstctrl);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm54xx_logic_state_get
 * @BRIEF		return logic current state for this power domain
 * @RETURNS		power domain logic current state:
 *			PWRDM_OFF_STATE or PWRDM_ON_STATE
 *			PWRDM_STATE_MAX in case of error
 * @param[in]		id: valid power domain ID
 * @DESCRIPTION		return logic current state for this power domain
 *//*------------------------------------------------------------------------ */
pwrdm_state pwrdm54xx_logic_state_get(pwrdm54xx_id id)
{
	reg *pm_pwrstst;

	if (!cpu_is_omap54xx()) {
		fprintf(stderr, "%s(): CPU != 54XX\n", __func__);
		return PWRDM_STATE_MAX;
	}
	CHECK_ARG_LESS_THAN(id, PWRDM54XX_ID_MAX, PWRDM_STATE_MAX);

	/* Retrieve PM_xyz_PWRSTST pointer */
	pm_pwrstst = pwrdm54xx_pwrstst_reg_get(id);
	if (pm_pwrstst == NULL)
		return PWRDM_STATE_MAX;
	else
		/* Retrieve logic target state */
		return pwrdm_logic_state_get(pm_pwrstst);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm54xx_in_transition
 * @BRIEF		return 1 if power domain is in transition, 0 otherwise
 * @RETURNS		1 if power domain is in transition, 0 otherwise
 * @param[in]		id: valid power domain ID
 * @DESCRIPTION		return 1 if power domain is in transition, 0 otherwise
 *//*------------------------------------------------------------------------ */
unsigned int pwrdm54xx_in_transition(pwrdm54xx_id id)
{
	reg *pm_pwrstst;

	if (!cpu_is_omap54xx()) {
		fprintf(stderr, "%s(): CPU != 54XX\n", __func__);
		return 0;
	}
	CHECK_ARG_LESS_THAN(id, PWRDM54XX_ID_MAX, 0);

	/* Retrieve PM_xyz_PWRSTST pointer */
	pm_pwrstst = pwrdm54xx_pwrstst_reg_get(id);
	/* Retrieve power domain intransition status */
	return pwrdm_in_transition(pm_pwrstst);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm54xx_config_show
 * @BRIEF		decode and display power domain configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output file
 * @param[in]		id: valid power domain ID
 * @DESCRIPTION		decode and display power domain configuration
 *//*------------------------------------------------------------------------ */
int pwrdm54xx_config_show(FILE *stream, pwrdm54xx_id id)
{
	pwrdm_state st_last, st_curr, st_tgt;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(stream, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(id, PWRDM54XX_ID_MAX, OMAPCONF_ERR_ARG);
	char s1[32], s2[32];
	reg *pm_pwrstctrl_reg;
	reg *pm_pwrstst_reg;
	unsigned int pm_pwrstctrl;
	unsigned int pm_pwrstst;
	char s[64];

	fprintf(stream, "|---------------------------------------------------"
		"-------------|\n");
	strcpy(s, pwrdm54xx_name_get(id));
	strcat(s, " Power Domain Configuration");
	fprintf(stream, "| %-62s |\n", s);
	fprintf(stream, "|---------------------------------------------------"
		"-------------|\n");
	fprintf(stream, "| %-32s | %-7s | %-7s | %-7s |\n", "Power State",
		"Current", "Target", "Last");
	fprintf(stream, "|----------------------------------|---------|------"
		"---|---------|\n");

	st_last = pwrdm54xx_state_get(id, PWRDM_STATE_PREVIOUS);
	st_curr = pwrdm54xx_state_get(id, PWRDM_STATE_CURRENT);
	st_tgt = pwrdm54xx_state_get(id, PWRDM_STATE_TARGET);
	fprintf(stream, "| %-32s | %-7s | %-7s | %-7s |\n",
		"Domain", pwrdm_state_name_get(st_curr),
		pwrdm_state_name_get(st_tgt), pwrdm_state_name_get(st_last));

	if ((!pwrdm54xx_has_logic_ret_state_ctrl_bit(id)) &&
		(!pwrdm54xx_has_pwrstst_reg(id)))
		goto pwrdm54xx_config_show_mem;

	st_tgt = pwrdm54xx_target_logic_ret_state_get(id);
	if (st_tgt != PWRDM_STATE_MAX)
		strcpy(s1, pwrdm_state_name_get(st_tgt));
	else
		strcpy(s1, "");
	st_curr = pwrdm54xx_logic_state_get(id);
	if (st_curr != PWRDM_STATE_MAX)
		strcpy(s2, pwrdm_state_name_get(st_curr));
	else
		strcpy(s2, "");
	fprintf(stream, "| %-32s | %-7s | %-7s |         |\n", "Logic", s2, s1);

pwrdm54xx_config_show_mem:
	if (pwrdm54xx_has_pwrstctrl_reg(id)) {
		pm_pwrstctrl_reg = pwrdm54xx_pwrstctrl_reg_get(id);
		pm_pwrstctrl = reg_read(pm_pwrstctrl_reg);
	}
	if (pwrdm54xx_has_pwrstst_reg(id)) {
		pm_pwrstst_reg = pwrdm54xx_pwrstst_reg_get(id);
		pm_pwrstst = reg_read(pm_pwrstst_reg);
	}

	switch (id) {
	case PWRDM54XX_EMU:
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"Memory", "", "");
		st_curr = (pwrdm_state) extract_bitfield(pm_pwrstst, 4, 2);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    EMU bank", pwrdm_state_name_get(st_curr), "");
		break;
	case PWRDM54XX_CAM:
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"Memory", "", "");
		st_curr = (pwrdm_state) extract_bitfield(pm_pwrstst, 4, 2);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    MEM", pwrdm_state_name_get(st_curr), "");
		break;
	case PWRDM54XX_CORE:
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"Memory", "", "");
		st_curr = (pwrdm_state) extract_bitfield(pm_pwrstst, 12, 2);
		st_tgt = (pwrdm_state) extract_bit(pm_pwrstctrl, 12);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    OCP_WP/UNIPRO1/DMM bank2",
			pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));

		st_curr = (pwrdm_state) extract_bitfield(pm_pwrstst, 10, 2);
		st_tgt = (pwrdm_state) extract_bit(pm_pwrstctrl, 11);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    IPU UNICACHE", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));

		st_curr = (pwrdm_state) extract_bitfield(pm_pwrstst, 8, 2);
		st_tgt = (pwrdm_state) extract_bit(pm_pwrstctrl, 10);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    IPU L2RAM", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));

		st_curr = (pwrdm_state) extract_bitfield(pm_pwrstst, 6, 2);
		st_tgt = (pwrdm_state) extract_bit(pm_pwrstctrl, 9);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    OCMRAM", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));

		st_curr = (pwrdm_state) extract_bitfield(pm_pwrstst, 4, 2);
		st_tgt = (pwrdm_state) extract_bit(pm_pwrstctrl, 8);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    DMA/ICR/DMM bank1", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));
		break;
	case PWRDM54XX_DSS:
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"Memory", "", "");
		st_curr = (pwrdm_state) extract_bitfield(pm_pwrstst, 8, 2);
		st_curr = (pwrdm_state) extract_bitfield(pm_pwrstst, 4, 2);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    MEM", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));
		break;
	case PWRDM54XX_L3_INIT:
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"Memory", "", "");
		st_curr = (pwrdm_state) extract_bitfield(pm_pwrstst, 6, 2);
		st_tgt = (pwrdm_state) extract_bit(pm_pwrstctrl, 9);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    L3INIT bank2", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));

		st_curr = (pwrdm_state) extract_bitfield(pm_pwrstst, 4, 2);
		st_tgt = (pwrdm_state) extract_bit(pm_pwrstctrl, 8);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    L3INIT bank1", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));
		break;
	case PWRDM54XX_L4_PER:
		if (cpu_revision_get() != REV_ES1_0) {
			fprintf(stderr,
				"omapconf: %s(): L4_PER removed from ES2.x!\n",
				__func__);
			break;
		}
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"Memory", "", "");
		st_curr = (pwrdm_state) extract_bitfield(pm_pwrstst, 6, 2);
		st_tgt = (pwrdm_state) extract_bit(pm_pwrstctrl, 9);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    NONRETAINED bank", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));

		st_curr = (pwrdm_state) extract_bitfield(pm_pwrstst, 4, 2);
		st_tgt = (pwrdm_state) extract_bit(pm_pwrstctrl, 8);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    RETAINED bank", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));
		break;
	case PWRDM54XX_ABE:
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"Memory", "", "");
		st_curr = (pwrdm_state) extract_bitfield(pm_pwrstst, 4, 2);
		st_tgt = (pwrdm_state) extract_bit(pm_pwrstctrl, 8);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    AESS", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));

		st_curr = (pwrdm_state) extract_bitfield(pm_pwrstst, 8, 2);
		st_tgt = (pwrdm_state) extract_bit(pm_pwrstctrl, 10);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    PERIPH", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));
		break;
	case PWRDM54XX_DSP:
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"Memory", "", "");
		st_curr = (pwrdm_state) extract_bitfield(pm_pwrstst, 8, 2);
		st_tgt = (pwrdm_state) extract_bit(pm_pwrstctrl, 10);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    EDMA", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));

		st_curr = (pwrdm_state) extract_bitfield(pm_pwrstst, 6, 2);
		st_tgt = (pwrdm_state) extract_bit(pm_pwrstctrl, 9);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    L2$", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));

		st_curr = (pwrdm_state) extract_bitfield(pm_pwrstst, 4, 2);
		st_tgt = (pwrdm_state) extract_bit(pm_pwrstctrl, 8);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    L1$", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));
		break;
	case PWRDM54XX_GPU:
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"Memory", "", "");
		st_curr = (pwrdm_state) extract_bitfield(pm_pwrstst, 4, 2);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    MEM", pwrdm_state_name_get(st_curr), "");
		break;
	case PWRDM54XX_IVA:
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"Memory", "", "");
		st_curr = (pwrdm_state) extract_bitfield(pm_pwrstst, 10, 2);
		st_tgt = (pwrdm_state) extract_bit(pm_pwrstctrl, 11);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    TCM2", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));

		st_curr = (pwrdm_state) extract_bitfield(pm_pwrstst, 8, 2);
		st_tgt = (pwrdm_state) extract_bit(pm_pwrstctrl, 10);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    TCM1", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));

		st_curr = (pwrdm_state) extract_bitfield(pm_pwrstst, 6, 2);
		st_tgt = (pwrdm_state) extract_bit(pm_pwrstctrl, 9);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    SL2", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));

		st_curr = (pwrdm_state) extract_bitfield(pm_pwrstst, 4, 2);
		st_tgt = (pwrdm_state) extract_bit(pm_pwrstctrl, 8);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    HWA", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));
		break;
	case PWRDM54XX_MPU:
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"Memory", "", "");
		st_curr = (pwrdm_state) extract_bitfield(pm_pwrstst, 6, 2);
		st_tgt = (pwrdm_state) extract_bit(pm_pwrstctrl, 9);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    L2$", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));
		break;

	default:
		/* Nothing to print */
		break;
	}

	if (pwrdm54xx_has_pwrstst_reg(id)) {
		fprintf(stream, "|---------------------------------------------"
			"-------------------|\n");

		fprintf(stream, "| %-32s | %-27s |\n",
			"Ongoing Power Transition?",
			((pwrdm54xx_in_transition(id) == 1) ? "YES" : "NO"));
	}
	fprintf(stream, "|---------------------------------------------------"
		"-------------|\n\n");
	return 0;
}
