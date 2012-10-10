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


#include <module44xx.h>
#include <module44xx-data.h>
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
