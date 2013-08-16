/*
 *
 * @Component			OMAPCONF
 * @Filename			module44xx.c
 * @Description			OMAP4 Module Definitions & Functions
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


#include <module.h>
#include <module44xx.h>
#include <module44xx-data.h>
#include <cm44xx.h>
#include <prm44xx.h>
#include <sysconfig44xx.h>
#include <lib.h>
#include <mem.h>
#include <string.h>
#include <stdio.h>
#include <cpuinfo.h>


/* #define MODULE44XX_DEBUG */
#ifdef MODULE44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod44xx_get_name
 * @BRIEF		return module name
 * @RETURNS		module name on success
 *			NULL in case of error
 * @param[in]		id: module ID
 * @param[in,out]	name: module name
 * @DESCRIPTION		return module name
 *//*------------------------------------------------------------------------ */
char *mod44xx_get_name(mod44xx_id id, char name[MOD44XX_MAX_NAME_LENGTH])
{
	if ((id >= OMAP4_MODULE_ID_MAX) || (name == NULL))
		return NULL;
	else
		strcpy(name, mod44xx_name_table[id]);

	return name;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod44xx_get_id
 * @BRIEF		return module ID
 * @RETURNS		module ID on success
 *			OMAP4_MODULE_ID_MAX in case of fail
 * @param[in,out]	name: module name
 * @DESCRIPTION		return module ID
 *//*------------------------------------------------------------------------ */
mod44xx_id mod44xx_get_id(const char *name)
{
	int i;

	for (i = 0; i < OMAP4_MODULE_ID_MAX; i++) {
		if (strcmp(name, mod44xx_name_table[i]) == 0)
			return (mod44xx_id) i;
	}

	return OMAP4_MODULE_ID_MAX;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod44xx_get_clkdm
 * @BRIEF		return the ID of the clock domain a given module
 *			is part of.
 * @RETURNS		clock domain ID a given module is part of
 *			(< OMAP4_CD_ID_MAX)
 *			OMAP4_CD_ID_MAX in case of error
 * @param[in]		id: module ID
 * @DESCRIPTION		return the ID of the clock domain a given module
 *			is part of.
 *//*------------------------------------------------------------------------ */
clkdm44xx_id mod44xx_get_clkdm(mod44xx_id id)
{
	if (id >= OMAP4_MODULE_ID_MAX)
		return OMAP4_CD_ID_MAX;

	else
		return mod44xx_info_table[id].clockdm_id;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod44xx_get_pwrdm
 * @BRIEF		return the ID of the power domain a given module
 *			is part of.
 * @RETURNS		power domain ID a given module is part of
 *			(< OMAP4_PD_ID_MAX)
 *			OMAP4_PD_ID_MAX in case of error
 * @param[in]		id: module ID
 * @DESCRIPTION		return the ID of the power domain a given module
 *			is part of.
 *//*------------------------------------------------------------------------ */
pwrdm44xx_id mod44xx_get_pwrdm(mod44xx_id id)
{
	if (id >= OMAP4_MODULE_ID_MAX)
		return OMAP4_PD_ID_MAX;

	else
		return mod44xx_info_table[id].powerdm_id;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod44xx_get_voltdm
 * @BRIEF		return the ID of the voltage domain a given module
 *			is part of.
 * @RETURNS		voltage domain ID a given module is part of
 *			(< OMAP4_VD_ID_MAX)
 *			OMAP4_VD_ID_MAX in case of error
 * @param[in]		id: module ID
 * @DESCRIPTION		return the ID of the voltage domain a given module
 *			is part of.
 *//*------------------------------------------------------------------------ */
voltdm44xx_id mod44xx_get_voltdm(mod44xx_id id)
{
	if (id >= OMAP4_MODULE_ID_MAX)
		return OMAP4_VD_ID_MAX;

	else
		return mod44xx_info_table[id].voltagedm_id;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod44xx_get_mode
 * @BRIEF		retrieve module mode from PRCM register
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 * @param[in]		id: module ID
 * @param[in,out]	mmode: module mode
 * @DESCRIPTION		retrieve module mode from PRCM register
 *//*------------------------------------------------------------------------ */
int mod44xx_get_mode(mod44xx_id id, mod_module_mode *mmode)
{
	unsigned int cm_clkctrl_addr, cm_clkctrl;
	int ret = 0;
	#ifdef MODULE44XX_DEBUG
	char name[MOD44XX_MAX_NAME_LENGTH];
	#endif

	if ((mmode == NULL) || (id >= OMAP4_MODULE_ID_MAX)) {
		fprintf(stderr,
			"%s(): (mmode == NULL) || (id >= OMAP4_MODULE_ID_MAX)!!!\n",
			__func__);
		ret = OMAPCONF_ERR_ARG;
		goto mod44xx_get_mode_exit;
	}
	*mmode = MOD_MODULE_MODE_MAX;

	if (!cpu_is_omap44xx()) {
		fprintf(stderr, "%s(): cpu is not omap44xx!!!\n", __func__);
		ret = OMAPCONF_ERR_CPU;
		goto mod44xx_get_mode_exit;
	}

	/* Retrieve CM_CLKCTRL address */
	cm_clkctrl_addr = (unsigned int) mod44xx_info_table[id].cm_clkctrl_addr;
	dprintf("%s(): module #%d name = %s CM_CLKCTRL ADDR = 0x%08X\n",
		__func__, id, mod44xx_get_name(id, name), cm_clkctrl_addr);

	/* Retrieve module mode */
	if ((void *) cm_clkctrl_addr != NULL) {
		if (mem_read(cm_clkctrl_addr, &cm_clkctrl) != 0) {
			fprintf(stderr, "%s(): could not read register!!!\n",
				__func__);
			ret = OMAPCONF_ERR_REG_ACCESS;
			goto mod44xx_get_mode_exit;
		}
		*mmode = (mod_module_mode) extract_bitfield(cm_clkctrl, 0, 2);
		dprintf(
			"%s(): CM_CLKCTRL ADDR = 0x%08X CM_CLKCTRL = 0x%08X MODULEMODE = %d\n",
			__func__, cm_clkctrl_addr, cm_clkctrl, *mmode);
		ret = 0;
	}

mod44xx_get_mode_exit:
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod44xx_is_accessible
 * @BRIEF		check omap module's registers accessibility
 * @RETURNS		1 if omap module's registers accessible
 *			0 if omap module's registers NOT accessible
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 * @param[in]		module_id: omap module ID
 * @DESCRIPTION		check omap module's registers accessibility
 *//*------------------------------------------------------------------------ */
int mod44xx_is_accessible(mod44xx_id module_id)
{
	unsigned int cm_clkctrl_addr, cm_clkctrl;
	int ret = 0;
	mod_module_mode mmode;
	#ifdef MODULE44XX_DEBUG
	char name[MOD44XX_MAX_NAME_LENGTH];
	#endif

	if (!cpu_is_omap44xx()) {
		fprintf(stderr, "%s(): cpu is not omap44xx!!!\n", __func__);
		ret = OMAPCONF_ERR_CPU;
		goto mod44xx_is_accessible_exit;
	}

	if (module_id >= OMAP4_MODULE_ID_MAX) {
		fprintf(stderr, "%s(): module_id >= OMAP4_MODULE_ID_MAX!!!\n",
			__func__);
		ret = OMAPCONF_ERR_ARG;
		goto mod44xx_is_accessible_exit;
	}

	/* Retrieve module mode */
	mod44xx_get_mode(module_id, &mmode);
	if (mmode == MOD_DISABLED_MODE) {
		dprintf(
			"%s(): module #%d name = %s mode is disabled => NOT accessible\n",
			__func__,
			module_id, mod44xx_get_name(module_id, name));
		ret = 0;
		goto mod44xx_is_accessible_exit;
	} else if (mmode == MOD_ENABLED_MODE) {
		dprintf(
			"%s(): module #%d name = %s mode is enabled => accessible\n",
			__func__,
			module_id, mod44xx_get_name(module_id, name));
		ret = 1;
		goto mod44xx_is_accessible_exit;
	}
	/* Module mode is HW Auto, need to check status */
	/* Retrieve CM_CLKCTRL address */
	cm_clkctrl_addr = (unsigned int)
		mod44xx_info_table[module_id].cm_clkctrl_addr;
	dprintf("%s(): module #%d name = %s CM_CLKCTRL ADDR = 0x%08X\n",
		__func__, module_id, mod44xx_get_name(module_id, name),
		cm_clkctrl_addr);

	/* Retrieve module state */
	if ((void *) cm_clkctrl_addr != NULL) {
		if (mem_read(cm_clkctrl_addr, &cm_clkctrl) != 0) {
			fprintf(stderr, "%s(): could not read register!!!\n",
				__func__);
			ret = OMAPCONF_ERR_REG_ACCESS;
			goto mod44xx_is_accessible_exit;
		}

		dprintf(
			"%s(): CM_CLKCTRL ADDR = 0x%08X CM_CLKCTRL = 0x%08X IDLEST = %d\n",
			__func__, (unsigned int)
				mod44xx_info_table[module_id].cm_clkctrl_addr,
			cm_clkctrl, extract_bitfield(cm_clkctrl, 16, 2));

		/* Check if module is accessible */
		switch (extract_bitfield(cm_clkctrl, 16, 2)) {
		case 0:
			/* Module is fully functional, including OCP */
			dprintf(
				"%s(): module is fully functional, including OCP\n",
				__func__);
			ret = 1;
			break;
		case 1:
			/*
			 * Module is performing transition: wakeup, or sleep,
			 * or sleep abortion
			 */
			dprintf(
				"%s(): module is performing transition: wakeup, or sleep, or sleep abortion\n",
				__func__);
			ret = 0;
			break;
		case 2:
			/* Module is in Idle mode (only OCP part) */
			dprintf(
				"%s(): module is in Idle mode (only OCP part)\n",
				__func__);
			ret = 0;
			break;
		case 3:
			/* Module is disabled and cannot be accessed */
			dprintf(
				"%s(): module is disabled and cannot be accessed\n",
				__func__);
			ret = 0;
		}
	} else {
		/* mod44xx_is_accessible():
		 * module has NO CM_CLKCTRL, it's always ON
		 */
		dprintf("%s(): module has NO CM_CLKCTRL, always ON\n",
			__func__);
		ret = 1;
	}

mod44xx_is_accessible_exit:
	dprintf("%s(%d) = %d\n", __func__, module_id, ret);
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod44xx_get_interface_type
 * @BRIEF		retrieve omap module's interface type
 * @RETURNS		0 if success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 * @param[in]		module_id: omap module ID
 * @param[in,out]	type: returned omap module's interface type
 * @DESCRIPTION		retrieve omap module's interface type
 *//*------------------------------------------------------------------------ */
int mod44xx_get_interface_type(mod44xx_id module_id,
	mod_interface_type *type)
{
	#ifdef MODULE44XX_DEBUG
	char name[MOD44XX_MAX_NAME_LENGTH];
	#endif

	if (!cpu_is_omap44xx())
		return OMAPCONF_ERR_CPU;

	if (module_id >= OMAP4_MODULE_ID_MAX)
		return OMAPCONF_ERR_ARG;

	/* Retrieve interface type */
	*type = mod44xx_info_table[module_id].type;
	dprintf("%s(): module #%d name = %s interface type = %d\n",
		__func__, module_id,
		mod44xx_get_name(module_id, name),
		*type);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod44xx_has_clockactivity_bit
 * @BRIEF		check if omap module has clockactivity bit
 *			in sysconfig register
 * @RETURNS		1 if omap module has clockactivity bit
 *			in sysconfig register
 *			0 if omap module does not have clockactivity bit
 *			in sysconfig register
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 * @param[in]		module_id: omap module ID
 * @DESCRIPTION		check if omap module has clockactivity bit
 *			in sysconfig register
 *//*------------------------------------------------------------------------ */
int mod44xx_has_clockactivity_bit(mod44xx_id module_id)
{
	#ifdef MODULE44XX_DEBUG
	char name[MOD44XX_MAX_NAME_LENGTH];
	#endif

	if (!cpu_is_omap44xx())
		return OMAPCONF_ERR_CPU;

	if (module_id >= OMAP4_MODULE_ID_MAX)
		return OMAPCONF_ERR_ARG;

	if (mod44xx_info_table[module_id].has_clockactivity_bit == 1) {
		dprintf("%s(): module %s HAS clockactivity bit\n",
		__func__, mod44xx_get_name(module_id, name));
		return 1;
	} else {
		dprintf("%s(): module %s does NOT have clockactivity bit\n",
		__func__, mod44xx_get_name(module_id, name));
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod44xx_get_autoidle_mode
 * @BRIEF		retrieve omap module's autoidle mode
 * @RETURNS		1 if success
 *			0 if omap module's registers NOT accessible
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		module_id: omap module ID
 * @param[in,out]	mode: returned omap module's autoidle mode
 * @DESCRIPTION		retrieve omap module's autoidle mode
 *//*------------------------------------------------------------------------ */
int mod44xx_get_autoidle_mode(mod44xx_id module_id,
	mod_autoidle_mode *mode)
{
	int ret_val = 0;
	unsigned int sysconfig;
	char name[MOD44XX_MAX_NAME_LENGTH];

	mod_interface_type type;

	*mode = MOD_AUTOIDLE_MODE_MAX;

	if (!cpu_is_omap44xx())
		return OMAPCONF_ERR_CPU;

	if (module_id >= OMAP4_MODULE_ID_MAX)
		return OMAPCONF_ERR_ARG;

	mod44xx_get_interface_type(module_id, &type);
	if (type == MOD_INTERFACE_NONE) {
		dprintf("%s(): module #%d name = %s has no SYSCONFIG\n",
			__func__, module_id,
			mod44xx_get_name(module_id, name));
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	ret_val = mod44xx_is_accessible(module_id);
	if (ret_val == 1) {
		/* Module is accessible */
		dprintf("%s(): module #%d name = %s is accessible\n",
			__func__, module_id,
			mod44xx_get_name(module_id, name));

		if (mod44xx_info_table[module_id].sysconfig_addr != NULL) {
			OMAP_READREG((unsigned int)
				mod44xx_info_table[module_id].sysconfig_addr,
				sysconfig);
			dprintf(
				"%s(): SYSCONFIG ADDR = 0x%08X SYSCONFIG = 0x%08X\n",
				__func__,
				(unsigned int)
				mod44xx_info_table[module_id].sysconfig_addr,
				sysconfig);

			/* Check module's autoidle bit */
			switch (module_id) {
			case OMAP4_CONTROL_GEN_WKUP:
			case OMAP4_CONTROL_PADCONF_WKUP:
			case OMAP4_SYNCTIMER:
			case OMAP4_WDT2:
			case OMAP4_WDT3:
			case OMAP4_TIMER3:
			case OMAP4_TIMER4:
			case OMAP4_TIMER5:
			case OMAP4_TIMER6:
			case OMAP4_TIMER7:
			case OMAP4_TIMER8:
			case OMAP4_TIMER9:
			case OMAP4_TIMER11:
			case OMAP4_MCASP:
			case OMAP4_IVAHD:
			case OMAP4_ICONT1:
			case OMAP4_ICONT2:
			case OMAP4_VDMA:
			case OMAP4_IME3:
			case OMAP4_ILF3:
			case OMAP4_MC3:
			case OMAP4_CALC3:
			case OMAP4_ECD3:
			case OMAP4_SMARTREFLEX_CORE:
			case OMAP4_SMARTREFLEX_MPU:
			case OMAP4_SMARTREFLEX_IVA:
			case OMAP4_CONTROL_GEN_CORE:
			case OMAP4_CONTROL_PADCONF_CORE:
			case OMAP4_SYSTEM_MAILBOX:
			case OMAP4_DMM:
			case OMAP4_AESS:
			case OMAP4_SIMCOP:
			case OMAP4_SIMCOP_DMA:
			case OMAP4_FDIF:
			case OMAP4_HDMI:
			case OMAP4_GFX:
			case OMAP4_MMC1_HL:
			case OMAP4_MMC2_HL:
			case OMAP4_MMC3_HL:
			case OMAP4_MMC4_HL:
			case OMAP4_MMC5_HL:
			case OMAP4_UNIPRO1:
			case OMAP4_FSUSBHOST:
			case OMAP4_HSUSBHOST:
			case OMAP4_MCSPI1_HL:
			case OMAP4_MCSPI2_HL:
			case OMAP4_MCSPI3_HL:
			case OMAP4_MCSPI4_HL:
			case OMAP4_DMIC:
			case OMAP4_MCBSP1:
			case OMAP4_MCBSP2:
			case OMAP4_MCBSP3:
			case OMAP4_MCPDM:
			case OMAP4_SDMA:
			case OMAP4_ISS:
			case OMAP4_BTE:
			case OMAP4_CBUFF:
				ret_val = OMAPCONF_ERR_NOT_AVAILABLE;
				dprintf("%s(): module %s has no AUTOIDLE bit\n",
					__func__,
					mod44xx_get_name(module_id, name));
				break;
			case OMAP4_SLIMBUS1:
			case OMAP4_SLIMBUS2:
				/*
				 * NB: AUTOGATINGDISABLE instead of AUTOGATING,
				 * bit is inverted compared to other modules
				 */
				*mode = (mod_autoidle_mode)
					!extract_bit(sysconfig, 8);
				ret_val = 1;
				dprintf("%s(): module %s AUTOIDLE bit 8 = %d\n",
					__func__,
					mod44xx_get_name(module_id, name),
					*mode);
				break;
			case OMAP4_SIMCOP_DCT:
				*mode = (mod_autoidle_mode)
					extract_bit(sysconfig, 5);
				ret_val = 1;
				dprintf("%s(): module %s AUTOIDLE bit 5 = %d\n",
					__func__,
					mod44xx_get_name(module_id, name),
					*mode);
				break;
			case OMAP4_SIMCOP_VLCDJ:
				*mode = (mod_autoidle_mode)
					extract_bit(sysconfig, 3);
				ret_val = 1;
				dprintf("%s(): module %s AUTOIDLE bit 3 = %d\n",
					__func__,
					mod44xx_get_name(module_id, name),
					*mode);
				break;
			case OMAP4_SIMCOP_ROT:
				*mode = (mod_autoidle_mode)
					extract_bit(sysconfig, 9);
				ret_val = 1;
				dprintf("%s(): module %s AUTOIDLE bit 9 = %d\n",
					__func__,
					mod44xx_get_name(module_id, name),
					*mode);
				break;
			default:
				*mode = (mod_autoidle_mode)
					extract_bit(sysconfig, 0);
				ret_val = 1;
				dprintf("%s(): module %s AUTOIDLE bit 0 = %d\n",
					__func__,
					mod44xx_get_name(module_id, name),
					*mode);
			}
		} else {
			fprintf(stderr,
				"omapconf (%s): error module's %s interface type is not NONE but SYSCONFIG ADDR == NULL\n",
				__func__, mod44xx_get_name(module_id, name));
			ret_val = OMAPCONF_ERR_INTERNAL;
		}
	} else if (ret_val == 0) {
		/* Module is NOT accessible */
		ret_val = 0;
		dprintf("%s(): module is NOT accessible\n", __func__);
	} else {
		/* internal error */
		dprintf("%s(): mod44xx_is_accessible() returned with %d\n",
			__func__, ret_val);
	}

	return ret_val;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod44xx_get_idle_mode
 * @BRIEF		retrieve omap module's idle mode
 * @RETURNS		1 if success
 *			0 if omap module's registers NOT accessible
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		module_id: omap module ID
 * @param[in,out]	mode: returned omap module's idle mode
 * @DESCRIPTION		retrieve omap module's idle mode
 *//*------------------------------------------------------------------------ */
int mod44xx_get_idle_mode(mod44xx_id module_id, mod_idle_mode *mode)
{
	int ret_val = 0;
	unsigned int sysconfig;
	mod_interface_type type;
	char name[MOD44XX_MAX_NAME_LENGTH];

	*mode = MOD_IDLE_MODE_MAX;

	if (!cpu_is_omap44xx()) {
		fprintf(stderr, "%s(): unsupported cpu!!!\n", __func__);
		ret_val = OMAPCONF_ERR_CPU;
		goto mod44xx_get_idle_mode_end;
	}

	if (module_id >= OMAP4_MODULE_ID_MAX) {
		fprintf(stderr, "%s(): incorrect module id!!! (%u)\n",
			__func__, module_id);
		ret_val = OMAPCONF_ERR_ARG;
		goto mod44xx_get_idle_mode_end;
	}

	mod44xx_get_interface_type(module_id, &type);
	if ((module_id != OMAP4_MPU_M3) &&
		(type != MOD_INTERFACE_SLAVE) && (type != MOD_INTERFACE_DUAL)) {
		dprintf("%s(): module #%d name = %s has no slave interface\n",
			__func__, module_id, mod44xx_get_name(module_id, name));
		ret_val = OMAPCONF_ERR_NOT_AVAILABLE;
		goto mod44xx_get_idle_mode_end;
	}

	ret_val = mod44xx_is_accessible(module_id);
	if (ret_val == 0) {
		/* Module is NOT accessible */
		ret_val = 0;
		dprintf("%s(): module #%d name = %s is NOT accessible\n",
			__func__, module_id, mod44xx_get_name(module_id, name));
		goto mod44xx_get_idle_mode_end;
	} else if (ret_val != 1) {
		/* internal error */
		dprintf("%s(): mod44xx_is_accessible() returned with %d!!!\n",
			__func__, ret_val);
		goto mod44xx_get_idle_mode_end;
	}

	/* Module is accessible */
	dprintf("%s(): module #%d name = %s is accessible\n",
		__func__, module_id, mod44xx_get_name(module_id, name));

	if ((module_id != OMAP4_MPU_M3) &&
		(mod44xx_info_table[module_id].sysconfig_addr == NULL)) {
		fprintf(stderr,
			"%s(): error module %s interface type is not NONE but SYSCONFIG ADDR == NULL\n",
			__func__, mod44xx_get_name(module_id, name));
		ret_val = OMAPCONF_ERR_INTERNAL;
		goto mod44xx_get_idle_mode_end;
	}


	if (module_id != OMAP4_MPU_M3) {
		OMAP_READREG((unsigned int)
			mod44xx_info_table[module_id].sysconfig_addr,
			sysconfig);
		dprintf("%s(): SYSCONFIG ADDR = 0x%08X, SYSCONFIG = 0x%08X\n",
			__func__, (unsigned int)
			mod44xx_info_table[module_id].sysconfig_addr,
			sysconfig);
	} else {
		OMAP_READREG((unsigned int) OMAP4430_IDLE_CORE_SYSCONFIG,
			sysconfig);
		dprintf(
			"%s(): SYSCONFIG ADDR = 0x%08X, IDLE_CORE_SYSCONFIG = 0x%08X\n",
			__func__, (unsigned int) OMAP4430_IDLE_CORE_SYSCONFIG,
			sysconfig);
	}

	/* get module's idle mode */
	switch (module_id) {
	case OMAP4_MCASP:
	case OMAP4_MPU_M3:
		*mode = (mod_idle_mode) extract_bitfield(sysconfig, 0, 2);
		ret_val = 1;
		dprintf("%s(): module %s idle mode (bits [1:0])=%d\n",
			__func__, mod44xx_get_name(module_id, name), *mode);
		break;
	case OMAP4_CONTROL_GEN_WKUP:
	case OMAP4_CONTROL_PADCONF_WKUP:
	case OMAP4_SLIMBUS1:
	case OMAP4_SLIMBUS2:
	case OMAP4_IVAHD:
	case OMAP4_ICONT1:
	case OMAP4_ICONT2:
	case OMAP4_VDMA:
	case OMAP4_IME3:
	case OMAP4_IPE3:
	case OMAP4_ILF3:
	case OMAP4_MC3:
	case OMAP4_CALC3:
	case OMAP4_ECD3:
	case OMAP4_CONTROL_GEN_CORE:
	case OMAP4_CONTROL_PADCONF_CORE:
	case OMAP4_SYSTEM_MAILBOX:
	case OMAP4_DMM:
	case OMAP4_AESS:
	case OMAP4_BTE:
	case OMAP4_CBUFF:
	case OMAP4_FDIF:
	case OMAP4_HDMI:
	case OMAP4_GFX:
	case OMAP4_MMC1_HL:
	case OMAP4_MMC2_HL:
	case OMAP4_MMC3_HL:
	case OMAP4_MMC4_HL:
	case OMAP4_MMC5_HL:
	case OMAP4_UNIPRO1:
	case OMAP4_FSUSBHOST:
	case OMAP4_HSUSBHOST:
	case OMAP4_MCSPI1_HL:
	case OMAP4_MCSPI2_HL:
	case OMAP4_MCSPI3_HL:
	case OMAP4_MCSPI4_HL:
	case OMAP4_DMIC:
	case OMAP4_MCPDM:
	case OMAP4_TIMER1:
	case OMAP4_TIMER2:
	case OMAP4_TIMER3:
	case OMAP4_TIMER4:
	case OMAP4_TIMER5:
	case OMAP4_TIMER6:
	case OMAP4_TIMER7:
	case OMAP4_TIMER8:
	case OMAP4_TIMER9:
	case OMAP4_TIMER10:
	case OMAP4_TIMER11:
	case OMAP4_ISS:
		*mode = (mod_idle_mode) extract_bitfield(sysconfig, 2, 2);
		ret_val = 1;
		dprintf("%s(): module %s idle mode (bits [3:2])=%d\n",
			__func__, mod44xx_get_name(module_id, name), *mode);
		break;
	case OMAP4_DSP:
	case OMAP4_DSP_WUGEN:
	case OMAP4_TCTRL:
	case OMAP4_RSZ:
	case OMAP4_SIMCOP_DCT:
	case OMAP4_SIMCOP_VLCDJ:
	case OMAP4_SIMCOP_ROT:
	case OMAP4_HDQ1W:
		ret_val = OMAPCONF_ERR_NOT_AVAILABLE;
		dprintf("%s(): module %s does not have IDLE mode\n",
			__func__, mod44xx_get_name(module_id, name));
		break;
	case OMAP4_SMARTREFLEX_CORE:
	case OMAP4_SMARTREFLEX_MPU:
	case OMAP4_SMARTREFLEX_IVA:
		*mode = (mod_idle_mode) extract_bitfield(sysconfig, 24, 2);
		ret_val = 1;
		dprintf("%s(): module %s idle mode (bits [25:24])=%d\n",
			__func__, mod44xx_get_name(module_id, name), *mode);
		break;
	default:
		*mode = (mod_idle_mode) extract_bitfield(sysconfig, 3, 2);
		ret_val = 1;
		dprintf("%s(): module %s idle mode (bits [4:3])=%d\n",
			__func__, mod44xx_get_name(module_id, name), *mode);
	}


mod44xx_get_idle_mode_end:
	return ret_val;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod44xx_has_smart_idle_wakeup_mode
 * @BRIEF		return 1 if module implements "smart-idle wakeup" mode
 * @RETURNS		1 if module implements "smart-idle wakeup" mode
 *			0 if mode not available.
 * @param[in]		id: module ID
 * @DESCRIPTION		return 1 if module implements "smart-idle wakeup" mode
 *			(not all modules feature this new OMAP4 mode).
 *			return 0 if mode not available or in case of error.
 *			Does not make any access to any register.
 *//*------------------------------------------------------------------------ */
int mod44xx_has_smart_idle_wakeup_mode(mod44xx_id id)
{
	if (!cpu_is_omap44xx()) {
		fprintf(stderr, "%s(): unsupported cpu!!!\n", __func__);
		return 0;
	}

	if (id >= OMAP4_MODULE_ID_MAX) {
		fprintf(stderr, "%s(): incorrect module id!!! (%u)\n",
			__func__, id);
		return 0;
	}

	dprintf("%s(%u) = %u\n",
		__func__, id, mod44xx_has_smart_idle_wakeup_table[id]);
	return mod44xx_has_smart_idle_wakeup_table[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod44xx_get_idle_status
 * @BRIEF		retrieve module's idle status from CM_xxx_xxx_CLKCTRL
 * @RETURNS		module idle status
 *			MOD_IDLE_STATUS_MAX in case of error
 * @param[in]		id: module ID
 * @param[in,out]	idlest: returned module idle status (string)
 * @DESCRIPTION		retrieve module's idle status from CM_xxx_xxx_CLKCTRL
 *//*------------------------------------------------------------------------ */
mod_idle_status mod44xx_get_idle_status(mod44xx_id id,
	char idlest[14])
{
	mod_idle_status ret = MOD_IDLE_STATUS_MAX;
	unsigned int cm_clkctrl;
	#ifdef MODULE44XX_DEBUG
	char name[MOD44XX_MAX_NAME_LENGTH];
	#endif

	if (idlest == NULL) {
		fprintf(stderr, "%s(): idlest == NULL!\n", __func__);
		goto mod44xx_get_idle_status_end;
	}

	*idlest = '\0';
	if (id >= OMAP4_MODULE_ID_MAX) {
		fprintf(stderr, "%s(): id (%u) >= OMAP4_MODULE_ID_MAX!\n",
			__func__, id);
		goto mod44xx_get_idle_status_end;
	}

	if (mod44xx_info_table[id].cm_clkctrl_addr == NULL) {
		dprintf("%s(): %s has no CLKCTRL register\n",
			__func__, mod44xx_get_name(id, name));
		goto mod44xx_get_idle_status_end;
	}

	if (mem_read((unsigned int)
			mod44xx_info_table[id].cm_clkctrl_addr,
		&cm_clkctrl) != 0) {
		fprintf(stderr, "%s(): error reading CLKCTRL reg (@0x%08X)!\n",
			__func__,
			(unsigned int) mod44xx_info_table[id].cm_clkctrl_addr);
		goto mod44xx_get_idle_status_end;
	}

	dprintf(
		"%s(): CM_CLKCTRL ADDR = 0x%08X, CM_CLKCTRL = 0x%08X, IDLEST = %u\n",
		__func__, (unsigned int) mod44xx_info_table[id].cm_clkctrl_addr,
		cm_clkctrl, extract_bitfield(cm_clkctrl, 16, 2));

	switch (extract_bitfield(cm_clkctrl, 16, 2)) {
	case 0:
		strcpy(idlest, "Full ON");
		ret = MOD_FULL_ON;
		break;
	case 1:
		strcpy(idlest, "In Transition");
		ret = MOD_IN_TRANSITION;
		break;
	case 2:
		strcpy(idlest, "OCP-ONLY Idle");
		ret = MOD_OCP_ONLY_IDLE;
		break;
	case 3:
		strcpy(idlest, "Disabled");
		ret = MOD_DISABLED;
		break;
	default:
		fprintf(stderr, "%s(): error decoding idle status!\n",
			__func__);
	}
	dprintf("%s(): %s idle status is %s (%u)\n",
		__func__, mod44xx_get_name(id, name), idlest,
		extract_bitfield(cm_clkctrl, 16, 2));

mod44xx_get_idle_status_end:
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod44xx_get_standby_mode
 * @BRIEF		retrieve omap module's standby mode
 * @RETURNS		1 if success
 *			0 if omap module's registers NOT accessible
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		module_id: omap module ID
 * @param[in,out]	mode: returned omap module's standby mode
 * @DESCRIPTION		retrieve omap module's standby mode
 *//*------------------------------------------------------------------------ */
int mod44xx_get_standby_mode(mod44xx_id module_id, mod_standby_mode *mode)
{
	int ret_val = 0;
	unsigned int sysconfig;
	mod_interface_type type;
	char name[MOD44XX_MAX_NAME_LENGTH];

	*mode = MOD_STANDBY_MODE_MAX;

	if (!cpu_is_omap44xx()) {
		fprintf(stderr, "%s(): unsupported cpu!!!\n", __func__);
		ret_val = OMAPCONF_ERR_CPU;
		goto mod44xx_get_standby_mode_end;
	}

	if (module_id >= OMAP4_MODULE_ID_MAX) {
		fprintf(stderr, "%s(): incorrect module id!!! (%u)\n",
			__func__, module_id);
		ret_val = OMAPCONF_ERR_ARG;
		goto mod44xx_get_standby_mode_end;
	}

	mod44xx_get_interface_type(module_id, &type);
	if ((module_id != OMAP4_MPU_M3) &&
		(type != MOD_INTERFACE_MASTER) &&
		(type != MOD_INTERFACE_DUAL)) {
		dprintf("%s(): module #%d name = %s has no master interface\n",
			__func__, module_id, mod44xx_get_name(module_id, name));
		ret_val = OMAPCONF_ERR_NOT_AVAILABLE;
		goto mod44xx_get_standby_mode_end;
	}

	ret_val = mod44xx_is_accessible(module_id);
	if (ret_val == 0) {
		/* Module is NOT accessible */
		ret_val = 0;
		dprintf("%s(): module #%d name = %s is NOT accessible\n",
			__func__, module_id, mod44xx_get_name(module_id, name));
		goto mod44xx_get_standby_mode_end;
	} else if (ret_val != 1) {
		/* Internal error */
		dprintf("%s(): mod44xx_is_accessible() returned with %d!!!\n",
			__func__, ret_val);
		goto mod44xx_get_standby_mode_end;
	}

	/* Module is accessible */
	dprintf("%s(): module #%d name = %s is accessible\n",
		__func__, module_id, mod44xx_get_name(module_id, name));


	if ((module_id != OMAP4_MPU_M3) &&
		(mod44xx_info_table[module_id].sysconfig_addr == NULL)) {
		fprintf(stderr,
			"%s(): error module %s interface type is not NONE but SYSCONFIG ADDR == NULL\n",
			__func__, mod44xx_get_name(module_id, name));
		ret_val = OMAPCONF_ERR_INTERNAL;
		goto mod44xx_get_standby_mode_end;
	}

	if (module_id != OMAP4_MPU_M3) {
		OMAP_READREG((unsigned int)
			mod44xx_info_table[module_id].sysconfig_addr,
			sysconfig);
		dprintf("%s(): SYSCONFIG ADDR = 0x%08X SYSCONFIG = 0x%08X\n",
			__func__, (unsigned int)
				mod44xx_info_table[module_id].sysconfig_addr,
			sysconfig);
	} else {
		OMAP_READREG((unsigned int) OMAP4430_STANDBY_CORE_SYSCONFIG,
			sysconfig);
		dprintf(
			"%s(): SYSCONFIG ADDR = 0x%08X, STANDBY_CORE_SYSCONFIG = 0x%08X\n",
			__func__, (unsigned int) OMAP4430_IDLE_CORE_SYSCONFIG,
			sysconfig);
	}

	/* Check module's standby mode */
	switch (module_id) {
	case OMAP4_IVAHD:
	case OMAP4_ICONT1:
	case OMAP4_ICONT2:
	case OMAP4_VDMA:
	case OMAP4_IME3:
	case OMAP4_ILF3:
	case OMAP4_AESS:
	case OMAP4_ISP5:
	case OMAP4_SIMCOP:
	case OMAP4_SIMCOP_DMA:
	case OMAP4_FDIF:
	case OMAP4_GFX:
	case OMAP4_MMC1_HL:
	case OMAP4_MMC2_HL:
	case OMAP4_MMC3_HL:
	case OMAP4_MMC4_HL:
	case OMAP4_MMC5_HL:
	case OMAP4_UNIPRO1:
	case OMAP4_FSUSBHOST:
	case OMAP4_HSUSBHOST:
	case OMAP4_ISS:
		*mode = (mod_standby_mode) extract_bitfield(sysconfig, 4, 2);
		ret_val = 1;
		dprintf("%s(): module %s standby mode (bits [5:4])=%d\n",
			__func__, mod44xx_get_name(module_id, name), *mode);
		break;
	case OMAP4_MPU_M3:
		*mode = (mod_standby_mode) extract_bitfield(sysconfig, 0, 2);
		ret_val = 1;
		dprintf("%s(): module %s standby mode (bits [0:12])=%d\n",
			__func__, mod44xx_get_name(module_id, name), *mode);
		break;
	default:
		*mode = (mod_standby_mode) extract_bitfield(sysconfig, 12, 2);
		ret_val = 1;
		dprintf("%s(): module %s standby mode (bits [13:12])=%d\n",
			__func__, mod44xx_get_name(module_id, name), *mode);
	}

mod44xx_get_standby_mode_end:
	return ret_val;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod44xx_get_standby_status
 * @BRIEF		retrieve module standby status from CM_xxx_xxx_CLKCTRL
 * @RETURNS		module standby status
 *			MOD_STANDBY_STATUS_MAX in case of error
 * @param[in]		id: module ID
 * @param[in,out]	st: returned module standby status (string)
 * @DESCRIPTION		retrieve module standby status from CM_xxx_xxx_CLKCTRL
 *//*------------------------------------------------------------------------ */
mod_standby_status mod44xx_get_standby_status(mod44xx_id id,
	char st[11])
{
	mod_standby_status ret = MOD_STANDBY_STATUS_MAX;
	unsigned int cm_clkctrl;
	#ifdef MODULE44XX_DEBUG
	char name[MOD44XX_MAX_NAME_LENGTH];
	#endif

	if (st == NULL) {
		fprintf(stderr, "%s(): idlest == NULL!\n", __func__);
		goto mod44xx_get_standby_status_end;
	}

	*st = '\0';
	if (id >= OMAP4_MODULE_ID_MAX) {
		fprintf(stderr, "%s(): id (%u) >= OMAP4_MODULE_ID_MAX!\n",
			__func__, id);
		goto mod44xx_get_standby_status_end;
	}

	if (mod44xx_info_table[id].cm_clkctrl_addr == NULL) {
		dprintf("%s(): %s has no CLKCTRL register\n",
			__func__, mod44xx_get_name(id, name));
		goto mod44xx_get_standby_status_end;
	}

	switch (id) {
	case OMAP4_DEBUGSS:
	case OMAP4_MPU:
	case OMAP4_DSP:
	case OMAP4_AESS:
	case OMAP4_MPU_M3:
	case OMAP4_SDMA:
	case OMAP4_C2C:
	case OMAP4_IVAHD:
	case OMAP4_ISS:
	case OMAP4_FDIF:
	case OMAP4_DISPC:
	case OMAP4_GFX:
	case OMAP4_MMC1:
	case OMAP4_MMC1_HL:
	case OMAP4_MMC2:
	case OMAP4_MMC2_HL:
	case OMAP4_HSI:
	case OMAP4_UNIPRO1:
	case OMAP4_HSUSBHOST:
	case OMAP4_HSUSBOTG:
	case OMAP4_FSUSBHOST:
		break;
	default:
		dprintf("%s(): module %s has no standby status bit\n",
			__func__, mod44xx_get_name(id, name));
		goto mod44xx_get_standby_status_end;
	}

	if (mem_read((unsigned int)
			mod44xx_info_table[id].cm_clkctrl_addr,
		&cm_clkctrl) != 0) {
		fprintf(stderr, "%s(): error reading CLKCTRL reg (@0x%08X)!\n",
			__func__,
			(unsigned int) mod44xx_info_table[id].cm_clkctrl_addr);
		goto mod44xx_get_standby_status_end;
	}

	dprintf(
		"%s(): CM_CLKCTRL ADDR = 0x%08X, CM_CLKCTRL = 0x%08X, STBYST = %u\n",
		__func__, (unsigned int) mod44xx_info_table[id].cm_clkctrl_addr,
		cm_clkctrl, extract_bit(cm_clkctrl, 18));

	switch (extract_bit(cm_clkctrl, 18)) {
	case 0:
		strcpy(st, "Functional");
		ret = MOD_FUNCTIONAL;
		break;
	case 1:
		strcpy(st, "In Standby");
		ret = MOD_IN_STANDBY;
		break;
	default:
		fprintf(stderr, "%s(): error decoding standby status!\n",
			__func__);
	}
	dprintf("%s(): %s standby status is %s (%u)\n",
		__func__, mod44xx_get_name(id, name), st,
		extract_bit(cm_clkctrl, 18));

mod44xx_get_standby_status_end:
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod44xx_get_clock_activity_mode
 * @BRIEF		retrieve omap module's clockactivity mode
 * @RETURNS		1 if success
 *			0 if omap module's registers NOT accessible
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		module_id: omap module ID
 * @param[in,out]	mode: returned omap module's clockactivity mode
 * @DESCRIPTION		retrieve omap module's clockactivity mode
 *//*------------------------------------------------------------------------ */
int mod44xx_get_clock_activity_mode(mod44xx_id module_id,
	mod_clock_activity_mode *mode)
{
	int ret_val = 0;
	unsigned int sysconfig;
	char name[MOD44XX_MAX_NAME_LENGTH];

	*mode = MOD_CLOCK_ACTIVITY_MODE_MAX;

	if (!cpu_is_omap44xx())
		return OMAPCONF_ERR_CPU;

	if (module_id >= OMAP4_MODULE_ID_MAX)
		return OMAPCONF_ERR_ARG;

	if (mod44xx_has_clockactivity_bit(module_id) != 1)
		return OMAPCONF_ERR_NOT_AVAILABLE;

	ret_val = mod44xx_is_accessible(module_id);
	if (ret_val == 1) {
		/* Module is accessible */
		dprintf("%s(): module #%d name = %s is accessible\n",
			__func__, module_id,
			mod44xx_get_name(module_id, name));

		if (mod44xx_info_table[module_id].sysconfig_addr != NULL) {
			OMAP_READREG((unsigned int)
				mod44xx_info_table[module_id].sysconfig_addr,
				sysconfig);
			dprintf(
				"%s(): SYSCONFIG ADDR = 0x%08X SYSCONFIG = 0x%08X\n",
				__func__, (unsigned int)
				mod44xx_info_table[module_id].sysconfig_addr,
				sysconfig);

			/* Check module's idle mode */
			switch (module_id) {
			case OMAP4_SPINLOCK:
			case OMAP4_ELM:
				*mode = (mod_clock_activity_mode)
					extract_bit(sysconfig, 8);
				ret_val = 1;
				dprintf(
					"%s(): module %s clockactivity bit 8 = %d\n",
					__func__,
					mod44xx_get_name(module_id, name),
					*mode);
				break;
			default:
				*mode = (mod_clock_activity_mode)
					extract_bitfield(sysconfig, 8, 2);
				ret_val = 1;
				dprintf(
					"%s(): module %s clockactivity (bits [9:8]) = %d\n",
					__func__,
					mod44xx_get_name(module_id, name),
					*mode);
			}
		} else {
			fprintf(stderr,
				"%s(): error module's %s interface type is not NONE but SYSCONFIG ADDR == NULL\n",
				__func__, mod44xx_get_name(module_id, name));
			ret_val = OMAPCONF_ERR_INTERNAL;
		}
	} else if (ret_val == 0) {
		/* Module is NOT accessible */
		ret_val = 0;
		dprintf("%s(): module is NOT accessible\n", __func__);
	} else {
		/* internal error */
		dprintf("%s(): mod44xx_is_accessible() returned with %d\n",
			__func__, ret_val);
	}

	return ret_val;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod44xx_get_src_clk
 * @BRIEF		retrieve omap module's functional clock source
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 * @param[in]		module_id: omap module ID
 * @param[in,out]	src_clk_id: returned omap functional clock source id
 *			OMAP4_UNDEF_CLK if not defined or in case of error
 * @DESCRIPTION		retrieve omap module's functional clock source
 *//*------------------------------------------------------------------------ */
int mod44xx_get_src_clk(mod44xx_id module_id, int *src_clk_id)
{
	*src_clk_id = OMAP4_UNDEF_CLK;
	#ifdef MODULE44XX_DEBUG
	char mod_name[MOD44XX_MAX_NAME_LENGTH];
	char src_clk_name[CLOCK44XX_MAX_NAME_LENGTH];
	#endif

	if (!cpu_is_omap44xx())
		return OMAPCONF_ERR_CPU;

	if (module_id >= OMAP4_MODULE_ID_MAX)
		return OMAPCONF_ERR_ARG;

	*src_clk_id = (int) mod44xx_info_table[module_id].src_clk_id;
	dprintf("%s(): module %s source is %s\n", __func__,
		mod44xx_get_name(module_id, mod_name),
		clk44xx_get_name(*src_clk_id, src_clk_name));
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod44xx_get_por_clk_speed
 * @BRIEF		retrieve omap module's functional POR clock speed
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 * @param[in]		module_id: omap module ID
 * @param[in]		opp: the OPP ID
 * @param[in,out]	por_clk_speed: returned omap functional clock speed
 *			(in MHz)
 * @DESCRIPTION		retrieve omap module's functional POR clock speed
 *//*------------------------------------------------------------------------ */
int mod44xx_get_por_clk_speed(mod44xx_id module_id,
	unsigned short opp, double *por_clk_speed)
{
	*por_clk_speed = 0.0;
	#ifdef MODULE44XX_DEBUG
	char name[MOD44XX_MAX_NAME_LENGTH];
	#endif

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(module_id, OMAP4_MODULE_ID_MAX, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(opp, OPP44XX_ID_MAX, OMAPCONF_ERR_ARG);

	*por_clk_speed = (double) mod44xx_info_table[module_id].por_speed[opp];
	dprintf("%s(): module %s POR speed is %lf\n", __func__,
		mod44xx_get_name(module_id, name),
		*por_clk_speed);
	return 0;
}


#ifndef MODULE44XX_DEBUG
/* #define MOD44XX_GET_CLK_SPEED_DEBUG */
#ifdef MOD44XX_GET_CLK_SPEED_DEBUG
#undef dprintf
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#undef dprintf
#define dprintf(format, ...)
#endif
#endif

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod44xx_get_clk_speed
 * @BRIEF		retrieve omap module's functional clock speed,
 *			as well as source clock ID and current OPP.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		module_id: omap module ID
 * @param[in, out]	src_clk_id: returned source clock ID
 *			(== OMAP4_CLOCK_ID_MAX in case of error)
 * @param[in, out]	opp_id: returned OPP ID
 *			(== OPP44XX_ID_MAX in case of error)
 * @param[in, out]	speed: returned clock speed (in MHz)
 *			(< 0 in case of error)
 * @DESCRIPTION		retrieve omap module's functional clock speed,
 *			as well as source clock ID and current OPP
 *			Ensure that OPP is stable before returning OPP and clock
 *			speed, so that there is no misalignment between the
 *			2 data.
 *//*------------------------------------------------------------------------ */
int mod44xx_get_clk_speed(mod44xx_id module_id,
	clock44xx_id *src_clk_id, opp44xx_id *opp_id, double *speed)
{
	int ret;
	voltdm44xx_id volt_dom_id;
	opp44xx_id opp_id2;
	#if (defined MOD44XX_GET_CLK_SPEED_DEBUG || defined MODULE44XX_DEBUG)
	char clk_name[CLOCK44XX_MAX_NAME_LENGTH];
	char opp_name[OPP44XX_MAX_NAME_LENGTH];
	char module_name[MOD44XX_MAX_NAME_LENGTH];
	#endif

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(module_id, OMAP4_MODULE_ID_MAX, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(src_clk_id, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(opp_id, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(speed, OMAPCONF_ERR_ARG);

	#if (defined MOD44XX_GET_CLK_SPEED_DEBUG || defined MODULE44XX_DEBUG)
	mod44xx_get_name(module_id, module_name);
	#endif

	*src_clk_id = OMAP4_CLOCK_ID_MAX;
	*opp_id  = OPP44XX_ID_MAX;
	*speed  = (double) OMAPCONF_ERR_NOT_AVAILABLE;

	/* Get module's functional source clock */
	ret = mod44xx_get_src_clk(module_id, (int *) src_clk_id);
	if (ret != 0) {
		dprintf("%s(%s): could not get FCLK! (ret=%d)\n", __func__,
			module_name, ret);
		goto mod44xx_get_clk_speed_end;
	}
	#if (defined MOD44XX_GET_CLK_SPEED_DEBUG || defined MODULE44XX_DEBUG)
	clk44xx_get_name(*src_clk_id, clk_name);
	#endif

	/* Get module's functional source clock speed */
	*speed = clk44xx_get_clock_speed(*src_clk_id, 1);
	if (*speed < 0) {
		dprintf("%s(%s): could not get speed! (ret=%lf)\n",
			__func__, module_name, *speed);
		goto mod44xx_get_clk_speed_end;
	}

	/* Get module's voltage domain ID */
	volt_dom_id = mod44xx_get_voltdm(module_id);
	if (volt_dom_id == OMAP4_VD_ID_MAX) {
		dprintf("%s(%s): could not get VDD ID!\n",
			__func__, module_name);
		ret = OMAPCONF_ERR_NOT_AVAILABLE;
		goto mod44xx_get_clk_speed_end;
	}

	/* To ensure OPP has not toggled between each calls, take 2 times the
	 * OPP and use a do {} while() loop that cannot exit until 2 OPPs
	 * retrieved are identical.
	 */
	do {
		/*
		 * Get the OPP of the voltage domain the module is part of.
		 */
		ret = voltdm44xx_get_opp(volt_dom_id, (opp44xx_id *) opp_id);
		if (ret != 0) {
			dprintf("%s(%s): could not get OPP! (ret=%d)\n",
				__func__, module_name, ret);
			goto mod44xx_get_clk_speed_end;
		}

		/* Get module's functional source clock speed */
		*speed = clk44xx_get_clock_speed(*src_clk_id, 1);
		if (*speed < 0) {
			dprintf("%s(%s): could not get speed! (ret=%lf)\n",
				__func__, module_name, *speed);
			goto mod44xx_get_clk_speed_end;
		}

		/* Get OPP a 2nd time */
		ret = voltdm44xx_get_opp(volt_dom_id, &opp_id2);
		if (ret != 0) {
			dprintf("%s(%s): could not get OPP2! (ret=%d)\n",
				__func__, module_name, ret);
			goto mod44xx_get_clk_speed_end;
		}
	} while (*opp_id != opp_id2);
	ret = 0;

mod44xx_get_clk_speed_end:
	#if (defined MOD44XX_GET_CLK_SPEED_DEBUG || defined MODULE44XX_DEBUG)
	voltdm44xx_opp2string(opp_name, *opp_id, volt_dom_id);
	printf("%s(%s): src_clk_id=%s, opp_id=%s, speed=%lfMHz\n", __func__,
		module_name, clk_name, opp_name, *speed);
	#endif
	return ret;
}

#ifndef MODULE44XX_DEBUG
#ifdef MOD44XX_GET_CLK_SPEED_DEBUG
#undef dprintf
#define dprintf(format, ...)
#endif
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod44xx_config_show
 * @BRIEF		analyze module power configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		stream: output file
 * @param[in]		name: module's name
 * @param[in]		cm_clkctrl_addr: module's CM CLKCTRL register addr
 * @param[in]		cm_clkctrl: module's CM CLKCTRL register content
 * @param[in]		rm_context_addr: module's RM CONTEXT register addr
 * @param[in]		rm_context: module's RM CONTEXT register content
 * @DESCRIPTION		analyze module power configuration
 *//*------------------------------------------------------------------------ */
int mod44xx_config_show(FILE *stream, const char name[11],
	unsigned int cm_clkctrl_addr, unsigned int cm_clkctrl,
	unsigned int rm_context_addr, unsigned int rm_context)
{
	unsigned int cm_alwon_usbphy_clkctrl;
	unsigned int tmp;

	if (!cpu_is_omap44xx()) {
		fprintf(stderr, "%s(): incorrect CPU!!!\n", __func__);
		return OMAPCONF_ERR_CPU;
	}

	dprintf("mod44xx_config_show(): name=%s\n", name);
	dprintf("mod44xx_config_show(): "
		"cm_clkctrl_addr=0x%08X\n", cm_clkctrl_addr);
	dprintf("mod44xx_config_show(): "
		"cm_clkctrl=0x%08X\n", cm_clkctrl);
	dprintf("mod44xx_config_show(): "
		"rm_context_addr=0x%08X\n", rm_context_addr);
	dprintf("mod44xx_config_show(): "
		"rm_context=0x%08X\n\n", rm_context);

	fprintf(stream, "|---------------------------------------------------"
		"-------|\n");
	fprintf(stream, "| %-10s Module Configuration                        "
		"  |\n", name);
	fprintf(stream, "|--------------------------------|------------------"
		"-------|\n");
	/* Module Mode */
	switch (cm_clkctrl_addr) {
	case OMAP4430_CM_MEMIF_DLL_CLKCTRL:
	case OMAP4430_CM_WKUP_BANDGAP_CLKCTRL:
		break;
	default:
		fprintf(stream, "| %-30s | %-23s |\n", "Mode",
			mod_module_mode_name_get((mod_module_mode)
				extract_bitfield(cm_clkctrl, 0, 2)));
		break;
	}

	/* FCLK Source / Optional Clocks */
	switch (cm_clkctrl_addr) {
	case OMAP4430_CM_MPU_MPU_CLKCTRL:
		if (!cpu_is_omap4430()) {
			tmp = (unsigned int) clk44xx_get_clock_speed(
				OMAP4_MPU_DPLL_CLK, 0);
			tmp /= 4 << extract_bit(cm_clkctrl, 25);
			fprintf(stream, "| %-30s | %dMHz (MPU CLK / %1d)    "
				"|\n", "MPU->ABE Async Bridge Speed", tmp,
				4 << extract_bit(cm_clkctrl, 25));
			tmp = (unsigned int) clk44xx_get_clock_speed(
				OMAP4_MPU_DPLL_CLK, 0);
			tmp /= 4 << extract_bit(cm_clkctrl, 24);
			fprintf(stream, "| %-30s | %dMHz (MPU CLK / %1d)    "
				"|\n", "EOCP_MA_ICLK Speed", tmp,
				4 << extract_bit(cm_clkctrl, 24));
		}
		break;
	case OMAP4430_CM1_ABE_DMIC_CLKCTRL:
	case OMAP4430_CM1_ABE_MCBSP1_CLKCTRL:
	case OMAP4430_CM1_ABE_MCBSP2_CLKCTRL:
	case OMAP4430_CM1_ABE_MCBSP3_CLKCTRL:
		switch (extract_bitfield(cm_clkctrl, 24, 2)) {
		case 0:
			switch (extract_bitfield(cm_clkctrl, 26, 2)) {
			case 0:
				fprintf(stream, "| %-30s | %-23s |\n",
					"FCLK Source", "24MHz from DPLL_ABE");
				break;
			case 1:
				fprintf(stream, "| %-30s | %-23s |\n",
					"FCLK Source", "ABE_SYSCLK");
				break;
			case 2:
				fprintf(stream, "| %-30s | %-23s |\n",
					"FCLK Source", "24MHz from DPLL_PER");
				break;
			default:
				fprintf(stream, "| %-30s | %-23s |\n",
					"FCLK Source", "Reserved!");
				break;
			}
			break;
		case 1:
			fprintf(stream, "| %-30s | %-23s |\n",
				"FCLK Source", "CLKS pad");
			break;
		case 2:
			fprintf(stream, "| %-30s | %-23s |\n",
				"FCLK Source", "Audio SLIMBUS pad");
			break;
		default:
			fprintf(stream, "| %-30s | %-23s |\n",
				"FCLK Source", "Reserved!");
			break;
		}
		break;
	case OMAP4430_CM1_ABE_SLIMBUS_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n",
			"Optional functional clock", "");
		fprintf(stream, "| %-30s | %-23s |\n", "  SLIMBUS",
			((extract_bit(cm_clkctrl, 11) == 1) ?
			"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  FCLK2",
			((extract_bit(cm_clkctrl, 10) == 1) ?
			"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  FCLK1",
			((extract_bit(cm_clkctrl, 9) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  FCLK0",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;
	case OMAP4430_CM1_ABE_AESS_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n",
			"Optional functional clock", "");
		fprintf(stream, "| %-30s | = ABE_CLK / %-4d        |\n",
			"  AESS_FCLK",
			(1 << extract_bit(cm_clkctrl, 24)));
		break;
	case OMAP4430_CM1_ABE_TIMER5_CLKCTRL:
	case OMAP4430_CM1_ABE_TIMER6_CLKCTRL:
	case OMAP4430_CM1_ABE_TIMER7_CLKCTRL:
	case OMAP4430_CM1_ABE_TIMER8_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n", "FCLK Source",
			((extract_bit(cm_clkctrl, 24) == 1) ?
			"ABE_ALWON_32K_CLK" : "ABE_SYSCLK"));
		break;
	case OMAP4430_CM_DSS_DSS_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n",
				"Optional functional clock", "");
		if (!cpu_is_omap4470())
			fprintf(stream, "| %-30s | %-23s |\n", "  TV",
				((extract_bit(cm_clkctrl, 11) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  SYS",
			((extract_bit(cm_clkctrl, 10) == 1) ?
			"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  48MHz",
			((extract_bit(cm_clkctrl, 9) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  DSS",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	case OMAP4430_CM_DSS_BB2D_CLKCTRL:
		fprintf(stream, "| %-30s | %-21s   |\n", "BB2D_FCLK Source",
			((extract_bit(cm_clkctrl, 24) == 1) ?
			"DPLL_PER" : "DPLL_CORE"));
		break;

	case OMAP4430_CM_CAM_ISS_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n",
			"Optional functional clock", "");
		fprintf(stream, "| %-30s | %-23s |\n",
			"  CAM_PHY_CTRL_GCLK 96Mhz",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;
	case OMAP4430_CM_CAM_FDIF_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n",
			"Optional functional clock", "");
		fprintf(stream, "| %-30s | = FUNC_128_CLK / %-4d   |\n",
			"  FDIF_FCLK",
			(1 << extract_bitfield(cm_clkctrl, 24, 2)));
		break;
	case OMAP4430_CM_GFX_GFX_CLKCTRL:
		if (cpu_is_omap4430() && (cpu_revision_get() == REV_ES1_0))
			fprintf(stream, "| %-30s | = 192MHz / %-10d   |\n",
			"PER_GFX_FCLK",
				(1 << extract_bitfield(cm_clkctrl, 25, 2)));
		fprintf(stream, "| %-30s | = %-19s   |\n", "GFX_FCLK",
			((extract_bit(cm_clkctrl, 24) == 1) ?
			"DPLL_PER" : "DPLL_CORE"));
		break;
	case OMAP4430_CM_L4PER_DMTIMER10_CLKCTRL:
	case OMAP4430_CM_L4PER_DMTIMER11_CLKCTRL:
	case OMAP4430_CM_WKUP_TIMER1_CLKCTRL:
	case OMAP4430_CM_L4PER_DMTIMER2_CLKCTRL:
	case OMAP4430_CM_L4PER_DMTIMER3_CLKCTRL:
	case OMAP4430_CM_L4PER_DMTIMER4_CLKCTRL:
	case OMAP4430_CM_L4PER_DMTIMER9_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n", "FCLK Source",
			((extract_bit(cm_clkctrl, 24) == 1) ?
				"32KHz" : "SYS_CLK"));
		break;
	case OMAP4430_CM_WKUP_GPIO1_CLKCTRL:
	case OMAP4430_CM_L4PER_GPIO2_CLKCTRL:
	case OMAP4430_CM_L4PER_GPIO3_CLKCTRL:
	case OMAP4430_CM_L4PER_GPIO4_CLKCTRL:
	case OMAP4430_CM_L4PER_GPIO5_CLKCTRL:
	case OMAP4430_CM_L4PER_GPIO6_CLKCTRL:
	case OMAP4430_CM_WKUP_BANDGAP_CLKCTRL:
		if (cpu_is_omap4430()) {
			fprintf(stream, "| %-30s | %-23s |\n",
				"Optional functional clock",
				((extract_bit(cm_clkctrl, 8) == 1) ?
					"Enabled" : "Disabled"));
		} else {
			fprintf(stream, "| %-30s | %-23s |\n",
				"TS F-Clock",
				((extract_bit(cm_clkctrl, 8) == 1) ?
					"Enabled" : "Disabled"));
			tmp = (unsigned int) clk44xx_get_clock_speed(
				OMAP4_L4WKUP_ICLK, 0);
			tmp /= (1 << (3 + extract_bitfield(cm_clkctrl, 24, 2)));
			fprintf(stream, "| %-30s | %dMHz (L4WKUP_ICLK / %-2d) "
				"|\n", "TS F-Clock Speed",
				tmp,
				1 << (3 + extract_bitfield(cm_clkctrl, 24, 2)));
		}
		break;
	case OMAP4430_CM_L4PER_MCBSP4_CLKCTRL:
		if (extract_bit(cm_clkctrl, 24) == 1) {
			fprintf(stream, "| %-30s | %-23s |\n",
				"FCLK Source", "CLKS Pad");
		} else {
			fprintf(stream, "| %-30s | %-23s |\n", "FCLK Source",
				((extract_bit(cm_clkctrl, 25) == 1) ?
				"DPLL_ABE 96MHz" : "DPLL_PER 96MHz"));
		}

		break;
	case OMAP4430_CM_L4PER_SLIMBUS2_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n",
			"Optional functional clock", "");
		fprintf(stream, "| %-30s | %-23s |\n", "  SLIMBUS",
			((extract_bit(cm_clkctrl, 10) == 1) ?
			"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  PER_ABE_24M_FCLK",
			((extract_bit(cm_clkctrl, 9) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  PER_24MC_FCLK",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;
	case OMAP4430_CM_MEMIF_DLL_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n", "Optional DLL_CLK FCLK",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;
	case OMAP4430_CM_WKUP_USIM_CLKCTRL:
		fprintf(stream, "| %-30s | = CM2 128MHz / %-2s       |\n",
			"USIM FCLK",
			((extract_bit(cm_clkctrl, 24) == 1) ? "18" : "14"));
		break;
	case OMAP4430_CM_L3INIT_MMC1_CLKCTRL:
	case OMAP4430_CM_L3INIT_MMC2_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n", "FCLK Source",
			((extract_bit(cm_clkctrl, 24) == 1) ?
			"96MHz from DPLL_PER" : "64MHz from DPLL_PER"));
		break;
	case OMAP4430_CM_L3INIT_HSI_CLKCTRL:
		switch (extract_bitfield(cm_clkctrl, 24, 2)) {
		case 0:
			fprintf(stream, "| %-30s | %-23s |\n",
				"FCLK Source", "192MHz / 1");
			break;
		case 1:
			fprintf(stream, "| %-30s | %-23s |\n",
				"FCLK Source", "192MHz / 2");
			break;
		case 2:
			fprintf(stream, "| %-30s | %-23s |\n",
				"FCLK Source", "192MHz / 4");
			break;
		default:
			fprintf(stream, "| %-30s | %-23s |\n",
				"FCLK Source", "Reserved!!!");
		}
		break;
	case OMAP4430_CM_L3INIT_UNIPRO1_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n",
			"Optional UNIPRO TX PHY clock",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;
	case OMAP4430_CM_L3INIT_USB_HOST_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n", "UTMI Port2 Source",
			((extract_bit(cm_clkctrl, 25) == 1) ?
			"external PHY" : "internal"));
		fprintf(stream, "| %-30s | %-23s |\n", "UTMI Port1 Source",
			((extract_bit(cm_clkctrl, 24) == 1) ?
			"external PHY" : "internal"));

		fprintf(stream, "| %-30s | %-23s |\n", "SAR MODE",
			((extract_bit(cm_clkctrl, 4) == 1) ?
				"Enabled" : "Disabled"));

		fprintf(stream, "| %-30s | %-23s |\n",
			"Optional functional clock", "");
		fprintf(stream, "| %-30s | %-23s |\n", "  FUNC48MCLK",
			((extract_bit(cm_clkctrl, 15) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  HSIC480M_P2_CLK",
			((extract_bit(cm_clkctrl, 14) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  HSIC480M_P1_CLK",
			((extract_bit(cm_clkctrl, 13) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  HSIC60M_P2_CLK",
			((extract_bit(cm_clkctrl, 12) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  HSIC60M_P1_CLK",
			((extract_bit(cm_clkctrl, 11) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  UTMI_P3_CLK",
			((extract_bit(cm_clkctrl, 10) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  UTMI_P2_CLK",
			((extract_bit(cm_clkctrl, 9) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  UTMI_P1_CLK",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;
	case OMAP4430_CM_L3INIT_USB_OTG_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n", "60MHz Source CLK",
			((extract_bit(cm_clkctrl, 24) == 1) ?
			"external ULPI PHY" : "on die UTMI PHY"));

		fprintf(stream, "| %-30s | %-23s |\n",
			"Optional XCLK (60MHz) clock",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;
	case OMAP4430_CM_L3INIT_USB_TLL_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n", "SAR MODE",
			((extract_bit(cm_clkctrl, 4) == 1) ?
				"Enabled" : "Disabled"));

		fprintf(stream, "| %-30s | %-23s |\n",
			"Optional functional clock", "");
		fprintf(stream, "| %-30s | %-23s |\n", "  USB_CH2_CLK",
			((extract_bit(cm_clkctrl, 10) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  USB_CH1_CLK",
			((extract_bit(cm_clkctrl, 9) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-30s | %-23s |\n", "  USB_CH0_CLK",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;
	case OMAP4430_CM_L3INIT_USBPHYOCP2SCP_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n",
			"Optional functional clock", "");
		if (cpu_is_omap4430() && (cpu_revision_get() == REV_ES1_0)) {
			fprintf(stream, "| %-30s | %-23s |\n", "  32KHz clock",
				((extract_bit(cm_clkctrl, 9) == 1) ?
					"Enabled" : "Disabled"));
		} else {
			if (mem_read(OMAP4430_CM_ALWON_USBPHY_CLKCTRL,
				&cm_alwon_usbphy_clkctrl) != 0)
				return OMAPCONF_ERR_REG_ACCESS;
			fprintf(stream, "| %-30s | %-23s |\n", "  32KHz clock",
				((extract_bit(cm_alwon_usbphy_clkctrl, 8)
					== 1) ? "Enabled" : "Disabled"));
		}
		fprintf(stream, "| %-30s | %-23s |\n", "  PHY_48M",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;
	case OMAP4430_CM_EMU_DEBUGSS_CLKCTRL:
		switch (extract_bitfield(cm_clkctrl, 20, 2)) {
		case 0:
			fprintf(stream, "| %-30s | %-23s |\n",
				"STM source clock", "SYS_CLK");
			break;
		case 1:
			fprintf(stream, "| %-30s | %-23s |\n",
				"STM source clock", "CORE_DPLL_EMU_CLK");
			break;
		case 2:
			fprintf(stream, "| %-30s | %-23s |\n",
				"STM source clock", "PER_DPLL_EMU_CLK");
			break;
		default:
			fprintf(stream, "| %-30s | %-23s |\n",
				"STM source clock", "Reserved!!!");
		}
		switch (extract_bitfield(cm_clkctrl, 27, 3)) {
		case 1:
			fprintf(stream, "| %-30s | %-23s |\n",
				"STM clock division", "STM source / 1");
			break;
		case 2:
			fprintf(stream, "| %-30s | %-23s |\n",
				"STM clock division", "STM source / 2");
			break;
		case 4:
			fprintf(stream, "| %-30s | %-23s |\n",
				"STM clock division", "STM source / 4");
			break;
		default:
			fprintf(stream, "| %-30s | %-23s |\n",
				"STM clock division", "Reserved!!!");
		}
		switch (extract_bitfield(cm_clkctrl, 22, 2)) {
		case 0:
			fprintf(stream, "| %-30s | %-23s |\n",
				"TRACE source clock", "SYS_CLK");
			break;
		case 1:
			fprintf(stream, "| %-30s | %-23s |\n",
				"TRACE source clock", "CORE_DPLL_EMU_CLK");
			break;
		case 2:
			if (cpu_is_omap4430() &&
				(cpu_revision_get() == REV_ES1_0))
				fprintf(stream, "| %-30s | %-23s |\n",
					"TRACE source clock",
					"PER_DPLL_EMU_CLK");
			else
				fprintf(stream, "| %-30s | %-23s |\n",
				"TRACE source clock", "Reserved!!!");
			break;
		default:
			fprintf(stream, "| %-30s | %-23s |\n",
				"TRACE source clock", "Reserved!!!");
		}
		switch (extract_bitfield(cm_clkctrl, 24, 3)) {
		case 1:
			fprintf(stream, "| %-30s | %-23s |\n",
				"TRACE clock division", "TRACE source / 1");
			break;
		case 2:
			fprintf(stream, "| %-30s | %-23s |\n",
				"TRACE clock division", "TRACE source / 2");
			break;
		case 4:
			fprintf(stream, "| %-30s | %-23s |\n",
				"TRACE clock division", "TRACE source / 4");
			break;
		default:
			fprintf(stream, "| %-30s | %-23s |\n",
				"TRACE clock division", "Reserved!!!");
		}
		break;
	default:
		break;
	}

	/* Idle Status */
	switch (cm_clkctrl_addr) {
	case OMAP4430_CM_MEMIF_DLL_CLKCTRL:
	case OMAP4430_CM_WKUP_BANDGAP_CLKCTRL:
		break;
	default:
		fprintf(stream, "| %-30s | %-23s |\n", "Idle Status",
			mod_idle_status_name_get((mod_idle_status)
				extract_bitfield(cm_clkctrl, 16, 2)));
		break;
	}

	/* Standby Status */
	switch (cm_clkctrl_addr) {
	case OMAP4430_CM_IVAHD_SL2_CLKCTRL:
	case OMAP4430_CM_MPU_M3_MPU_M3_CLKCTRL:
	case OMAP4430_CM_SDMA_SDMA_CLKCTRL:
	case OMAP4430_CM_C2C_C2C_CLKCTRL:
	case OMAP4430_CM1_ABE_AESS_CLKCTRL:
	case OMAP4430_CM_L3INIT_MMC1_CLKCTRL:
	case OMAP4430_CM_L3INIT_MMC2_CLKCTRL:
	case OMAP4430_CM_L3INIT_HSI_CLKCTRL:
	case OMAP4430_CM_L3INIT_UNIPRO1_CLKCTRL:
	case OMAP4430_CM_L3INIT_USB_HOST_CLKCTRL:
	case OMAP4430_CM_L3INIT_USB_OTG_CLKCTRL:
	case OMAP4430_CM_L3INIT_P1500_CLKCTRL:
	case OMAP4430_CM_L3INIT_USB_HOST_FS_CLKCTRL:
	case OMAP4430_CM_EMU_DEBUGSS_CLKCTRL:
		fprintf(stream, "| %-30s | %-23s |\n", "Standby Status",
			((extract_bit(cm_clkctrl, 18) == 1) ?
				"Standby" : "Not in Standby"));
		break;
	default:
		break;
	}


	switch (rm_context_addr) {
	case 0: /* no context register */
		break;
	default:
		fprintf(stream, "| %-30s | %-23s |\n", "Last Context", "");
		break;
	}

	switch (rm_context_addr) {
	case OMAP4430_RM_MPU_MPU_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  RAM",
			((extract_bit(rm_context, 10) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_DSP_DSP_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  EDMA",
			((extract_bit(rm_context, 10) == 1) ?
				"LOST" : "RETAINED"));
		break;
	default:
		break;
	}

	switch (rm_context_addr) {
	case OMAP4430_RM_IVAHD_IVAHD_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  HWA",
			((extract_bit(rm_context, 10) == 1) ?
				"LOST" : "RETAINED"));
		break;
	default:
		break;
	}

	switch (rm_context_addr) {
	case OMAP4430_RM_MPU_MPU_CONTEXT:
	case OMAP4430_RM_DSP_DSP_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  L2$",
			((extract_bit(rm_context, 9) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_IVAHD_IVAHD_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  TCM2",
			((extract_bit(rm_context, 9) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_MPU_M3_MPU_M3_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  L2RAM",
			((extract_bit(rm_context, 9) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_MEMIF_DMM_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  CORE_NRET_BANK",
			((extract_bit(rm_context, 9) == 1) ?
				"LOST" : "RETAINED"));
		break;
	default:
		break;
	}

	switch (rm_context_addr) {
	case OMAP4430_RM_WKUP_SARRAM_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  WKUP_BANK",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_MPU_MPU_CONTEXT:
		if (cpu_is_omap4430())
			fprintf(stream, "| %-30s | %-23s |\n", "  L1$",
				((extract_bit(rm_context, 8) == 1) ?
					"LOST" : "RETAINED"));
		else
			fprintf(stream, "| %-30s | %-23s |\n", "  L1$", "");
		break;
	case OMAP4430_RM_DSP_DSP_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  L1$",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_DSS_DSS_CONTEXT:
	/*
	 * case OMAP4430_RM_DSS_DEISS_CONTEXT:
	 * module not implemented in 44xx,
	 * at same address as OMAP4430_RM_DSS_BB2D_CONTEXT in 4470
	 * causing duplicate case value ...
	 */
	case OMAP4430_RM_DSS_BB2D_CONTEXT:
	case OMAP4430_RM_CAM_ISS_CONTEXT:
	case OMAP4430_RM_CAM_FDIF_CONTEXT:
	case OMAP4430_RM_GFX_GFX_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  MEM",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_IVAHD_IVAHD_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  TCM1",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_IVAHD_SL2_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  SL2",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_L4PER_MCBSP4_CONTEXT:
	case OMAP4430_RM_L4PER_MMCSD3_CONTEXT:
	case OMAP4430_RM_L4PER_MMCSD4_CONTEXT:
	case OMAP4430_RM_L4PER_SLIMBUS2_CONTEXT:
	case OMAP4430_RM_L4PER_MMCSD5_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  NONRETAINED_BANK",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_L4PER_UART1_CONTEXT:
	case OMAP4430_RM_L4PER_UART2_CONTEXT:
	case OMAP4430_RM_L4PER_UART3_CONTEXT:
	case OMAP4430_RM_L4PER_UART4_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  RETAINED_BANK",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_L3_2_OCMC_RAM_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  OCM RAM",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_MPU_M3_MPU_M3_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  Unicache",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_SDMA_SDMA_CONTEXT:
	case OMAP4430_RM_MEMIF_DMM_CONTEXT:
	case OMAP4430_RM_C2C_MODEM_ICR_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  CORE_OTHER_BANK",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_L3INSTR_OCP_WP1_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  CORE_NRET_BANK",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_ABE_AESS_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  AESSMEM",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_ABE_PDM_CONTEXT:
	case OMAP4430_RM_ABE_DMIC_CONTEXT:
	case OMAP4430_RM_ABE_MCBSP1_CONTEXT:
	case OMAP4430_RM_ABE_MCBSP2_CONTEXT:
	case OMAP4430_RM_ABE_MCBSP3_CONTEXT:
	case OMAP4430_RM_ABE_SLIMBUS_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  PERIPHMEM",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_L3INIT_MMC1_CONTEXT:
	case OMAP4430_RM_L3INIT_MMC2_CONTEXT:
	case OMAP4430_RM_L3INIT_HSI_CONTEXT:
	case OMAP4430_RM_L3INIT_UNIPRO1_CONTEXT:
	case OMAP4430_RM_L3INIT_USB_OTG_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  L3INIT_BANK1",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_EMU_DEBUGSS_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  EMU_BANK",
			((extract_bit(rm_context, 8) == 1) ?
				"LOST" : "RETAINED"));
		break;
	default:
		break;
	}

	/* RFF-based */
	switch (rm_context_addr) {
	case OMAP4430_RM_DSP_DSP_CONTEXT:
	case OMAP4430_RM_DSS_DSS_CONTEXT:
	case OMAP4430_RM_L4PER_L4_PER_CONTEXT:
	case OMAP4430_RM_L4PER_GPIO2_CONTEXT:
	case OMAP4430_RM_L4PER_GPIO3_CONTEXT:
	case OMAP4430_RM_L4PER_GPIO4_CONTEXT:
	case OMAP4430_RM_L4PER_GPIO5_CONTEXT:
	case OMAP4430_RM_L4PER_GPIO6_CONTEXT:
	case OMAP4430_RM_L4PER_I2C1_CONTEXT:
	case OMAP4430_RM_L4PER_UART1_CONTEXT:
	case OMAP4430_RM_L4PER_UART2_CONTEXT:
	case OMAP4430_RM_L4PER_UART3_CONTEXT:
	case OMAP4430_RM_L4PER_UART4_CONTEXT:
	case OMAP4430_RM_L3_1_L3_1_CONTEXT:
	case OMAP4430_RM_L3_2_L3_2_CONTEXT:
	case OMAP4430_RM_L3_2_GPMC_CONTEXT:
	case OMAP4430_RM_MPU_M3_MPU_M3_CONTEXT:
	case OMAP4430_RM_SDMA_SDMA_CONTEXT:
	case OMAP4430_RM_MEMIF_DMM_CONTEXT:
	case OMAP4430_RM_MEMIF_EMIF_FW_CONTEXT:
	case OMAP4430_RM_MEMIF_EMIF_1_CONTEXT:
	case OMAP4430_RM_MEMIF_EMIF_2_CONTEXT:
	case OMAP4430_RM_C2C_C2C_CONTEXT:
	case OMAP4430_RM_C2C_MODEM_ICR_CONTEXT:
	case OMAP4430_RM_C2C_C2C_FW_CONTEXT:
	case OMAP4430_RM_L4CFG_L4_CFG_CONTEXT:
	case OMAP4430_RM_L4CFG_HW_SEM_CONTEXT:
	case OMAP4430_RM_L4CFG_MAILBOX_CONTEXT:
	case OMAP4430_RM_L3INSTR_L3_3_CONTEXT:
	case OMAP4430_RM_L3INSTR_OCP_WP1_CONTEXT:
	case OMAP4430_RM_L3INIT_MMC1_CONTEXT:
	case OMAP4430_RM_L3INIT_MMC2_CONTEXT:
	case OMAP4430_RM_L3INIT_HSI_CONTEXT:
	case OMAP4430_RM_L3INIT_USB_HOST_CONTEXT:
	case OMAP4430_RM_L3INIT_USB_OTG_CONTEXT:
	case OMAP4430_RM_L3INIT_USB_TLL_CONTEXT:
	case OMAP4430_RM_L3INIT_USB_HOST_FS_CONTEXT:
		fprintf(stream, "| %-30s | %-23s |\n", "  RFF-Based",
			((extract_bit(rm_context, 1) == 1) ?
				"LOST" : "RETAINED"));
		break;
	case OMAP4430_RM_MPU_MPU_CONTEXT:
		if (!cpu_is_omap4430())
			fprintf(stream, "| %-30s | %-23s |\n", "  RFF-Based",
				((extract_bit(rm_context, 1) == 1) ?
					"LOST" : "RETAINED"));
		break;
	default:
		break;
	}

	/* DFF-based */
	switch (rm_context_addr) {
	case OMAP4430_RM_L4PER_GPIO2_CONTEXT:
	case OMAP4430_RM_L4PER_GPIO3_CONTEXT:
	case OMAP4430_RM_L4PER_GPIO4_CONTEXT:
	case OMAP4430_RM_L4PER_GPIO5_CONTEXT:
	case OMAP4430_RM_L4PER_GPIO6_CONTEXT:
	case OMAP4430_RM_L4PER_I2C1_CONTEXT:
	case OMAP4430_RM_L4PER_UART1_CONTEXT:
	case OMAP4430_RM_L4PER_UART2_CONTEXT:
	case OMAP4430_RM_L4PER_UART3_CONTEXT:
	case OMAP4430_RM_L4PER_UART4_CONTEXT:
	case OMAP4430_RM_L3_2_GPMC_CONTEXT:
	case OMAP4430_RM_SDMA_SDMA_CONTEXT:
	case OMAP4430_RM_C2C_MODEM_ICR_CONTEXT:
	case OMAP4430_RM_L4CFG_HW_SEM_CONTEXT:
	case OMAP4430_RM_L4CFG_MAILBOX_CONTEXT:
	case OMAP4430_RM_L3INIT_MMC1_CONTEXT:
	case OMAP4430_RM_L3INIT_MMC2_CONTEXT:
	case OMAP4430_RM_L3INIT_HSI_CONTEXT:
	case OMAP4430_RM_L3INIT_USB_HOST_CONTEXT:
	case OMAP4430_RM_L3INIT_USB_OTG_CONTEXT:
	case OMAP4430_RM_L3INIT_USB_TLL_CONTEXT:
	case OMAP4430_RM_L3INIT_USB_HOST_FS_CONTEXT:
	case 0:
		break;
	case OMAP4430_RM_MEMIF_EMIF_1_CONTEXT:
	case OMAP4430_RM_MEMIF_EMIF_2_CONTEXT:
		if ((cpu_is_omap4430() && (cpu_revision_get() != REV_ES1_0))
			|| cpu_is_omap4460() || cpu_is_omap4470()) {
			fprintf(stream, "| %-30s | %-23s |\n", "  DFF-based",
				((extract_bit(rm_context, 0) == 1) ?
					"LOST" : "RETAINED"));
		}
		break;
	default:

		fprintf(stream, "| %-30s | %-23s |\n", "  DFF-based",
			((extract_bit(rm_context, 0) == 1) ?
				"LOST" : "RETAINED"));
		break;
	}
	fprintf(stream, "|----------------------------------------------------"
		"------|\n");
	fprintf(stream, "\n");

	return 0;
}
