/*
 *
 * @Component			OMAPCONF
 * @Filename			clkdm54xx.c
 * @Description			OMAP5 Clock Domain Definitions & APIs
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


#include <lib.h>
#include <clkdm54xx.h>
#include <cm54xx.h>
#include <prm54xx.h>
#include <string.h>
#include <stdio.h>
#include <cpuinfo.h>
#include <powerdomain.h>
#include <voltdomain.h>


/* #define CLKDM54XX_DEBUG */
#ifdef CLKDM54XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static const char
	clkdm54xx_names_table[CLKDM54XX_ID_MAX][CLKDM54XX_MAX_NAME_LENGTH] = {
	"EMU",
	"WKUPAON",
	"COREAON",
	"CAM",
	"L4CFG",
	"EMIF",
	"IPU",
	"L3MAIN2",
	"L3INSTR",
	"L3MAIN1",
	"C2C",
	"DMA",
	"MIPIEXT",
	"DSS",
	"CUSTEFUSE",
	"L3INIT",
	"L4PER",
	"L4SEC",
	"ABE",
	"DSP",
	"GPU",
	"IVA",
	"MPU",
	"NONE (PRCM)"};


static unsigned short clkdm54xx_init_done = 0;
genlist clkdm54xx_list;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm54xx_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void clkdm54xx_init(void)
{
	clockdm_info clkdm;

	if (clkdm54xx_init_done)
		return;

	genlist_init(&clkdm54xx_list);

	clkdm.name = CLKDM_EMU;
	clkdm.id = (int) CLKDM54XX_EMU;
	clkdm.powerdm = PWRDM_EMU;
	clkdm.voltdm = VDD_WKUP;
	if (cpu_revision_get() == REV_ES1_0)
		clkdm.clkstctrl = &omap5430es1_cm_emu_clkstctrl;
	else
		clkdm.clkstctrl = &omap5430_cm_emu_clkstctrl;
	clkdm.properties = 0;
	genlist_addtail(&clkdm54xx_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_WKUPAON;
	clkdm.id = (int) CLKDM54XX_WKUPAON;
	clkdm.powerdm = PWRDM_WKUPAON;
	clkdm.voltdm = VDD_WKUP;
	if (cpu_revision_get() == REV_ES1_0)
		clkdm.clkstctrl = &omap5430es1_cm_wkupaon_clkstctrl;
	else
		clkdm.clkstctrl = &omap5430_cm_wkupaon_clkstctrl;
	clkdm.properties = 0;
	genlist_addtail(&clkdm54xx_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_COREAON;
	clkdm.id = (int) CLKDM54XX_COREAON;
	clkdm.powerdm = PWRDM_COREAON;
	clkdm.voltdm = VDD_CORE;
	if (cpu_revision_get() == REV_ES1_0)
		clkdm.clkstctrl = &omap5430es1_cm_coreaon_clkstctrl;
	else
		clkdm.clkstctrl = &omap5430_cm_coreaon_clkstctrl;
	clkdm.properties = 0;
	genlist_addtail(&clkdm54xx_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_CAM;
	clkdm.id = (int) CLKDM54XX_CAM;
	clkdm.powerdm = PWRDM_CAM;
	clkdm.voltdm = VDD_CORE;
	if (cpu_revision_get() == REV_ES1_0)
		clkdm.clkstctrl = &omap5430es1_cm_cam_clkstctrl;
	else
		clkdm.clkstctrl = &omap5430_cm_cam_clkstctrl;
	clkdm.properties = 0;
	genlist_addtail(&clkdm54xx_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_L4_CFG;
	clkdm.id = (int) CLKDM54XX_L4_CFG;
	clkdm.powerdm = PWRDM_CORE;
	clkdm.voltdm = VDD_CORE;
	if (cpu_revision_get() == REV_ES1_0)
		clkdm.clkstctrl = &omap5430es1_cm_l4cfg_clkstctrl;
	else
		clkdm.clkstctrl = &omap5430_cm_l4cfg_clkstctrl;
	clkdm.properties = 0;
	genlist_addtail(&clkdm54xx_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_EMIF;
	clkdm.id = (int) CLKDM54XX_EMIF;
	clkdm.powerdm = PWRDM_CORE;
	clkdm.voltdm = VDD_CORE;
	if (cpu_revision_get() == REV_ES1_0)
		clkdm.clkstctrl = &omap5430es1_cm_emif_clkstctrl;
	else
		clkdm.clkstctrl = &omap5430_cm_emif_clkstctrl;
	clkdm.properties = 0;
	genlist_addtail(&clkdm54xx_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_IPU;
	clkdm.id = (int) CLKDM54XX_IPU;
	clkdm.powerdm = PWRDM_CORE;
	clkdm.voltdm = VDD_CORE;
	if (cpu_revision_get() == REV_ES1_0)
		clkdm.clkstctrl = &omap5430es1_cm_ipu_clkstctrl;
	else
		clkdm.clkstctrl = &omap5430_cm_ipu_clkstctrl;
	clkdm.properties = 0;
	genlist_addtail(&clkdm54xx_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_L3_MAIN2;
	clkdm.id = (int) CLKDM54XX_L3_MAIN2;
	clkdm.powerdm = PWRDM_CORE;
	clkdm.voltdm = VDD_CORE;
	if (cpu_revision_get() == REV_ES1_0)
		clkdm.clkstctrl = &omap5430es1_cm_l3main2_clkstctrl;
	else
		clkdm.clkstctrl = &omap5430_cm_l3main2_clkstctrl;
	clkdm.properties = 0;
	genlist_addtail(&clkdm54xx_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_L3_INSTR;
	clkdm.id = (int) CLKDM54XX_L3_INSTR;
	clkdm.powerdm = PWRDM_CORE;
	clkdm.voltdm = VDD_CORE;
	if (cpu_revision_get() == REV_ES1_0)
		clkdm.clkstctrl = &omap5430es1_cm_l3instr_clkstctrl;
	else
		clkdm.clkstctrl = &omap5430_cm_l3instr_clkstctrl;
	clkdm.properties = 0;
	genlist_addtail(&clkdm54xx_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_L3_MAIN1;
	clkdm.id = (int) CLKDM54XX_L3_MAIN1;
	clkdm.powerdm = PWRDM_CORE;
	clkdm.voltdm = VDD_CORE;
	if (cpu_revision_get() == REV_ES1_0)
		clkdm.clkstctrl = &omap5430es1_cm_l3main1_clkstctrl;
	else
		clkdm.clkstctrl = &omap5430_cm_l3main1_clkstctrl;
	clkdm.properties = 0;
	genlist_addtail(&clkdm54xx_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_C2C;
	clkdm.id = (int) CLKDM54XX_C2C;
	clkdm.powerdm = PWRDM_CORE;
	clkdm.voltdm = VDD_CORE;
	if (cpu_revision_get() == REV_ES1_0)
		clkdm.clkstctrl = &omap5430es1_cm_c2c_clkstctrl;
	else
		clkdm.clkstctrl = &omap5430_cm_c2c_clkstctrl;
	clkdm.properties = 0;
	genlist_addtail(&clkdm54xx_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_DMA;
	clkdm.id = (int) CLKDM54XX_DMA;
	clkdm.powerdm = PWRDM_CORE;
	clkdm.voltdm = VDD_CORE;
	if (cpu_revision_get() == REV_ES1_0)
		clkdm.clkstctrl = &omap5430es1_cm_dma_clkstctrl;
	else
		clkdm.clkstctrl = &omap5430_cm_dma_clkstctrl;
	clkdm.properties = 0;
	genlist_addtail(&clkdm54xx_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_MIPIEXT;
	clkdm.id = (int) CLKDM54XX_MIPIEXT;
	clkdm.powerdm = PWRDM_CORE;
	clkdm.voltdm = VDD_CORE;
	if (cpu_revision_get() == REV_ES1_0)
		clkdm.clkstctrl = &omap5430es1_cm_mipiext_clkstctrl;
	else
		clkdm.clkstctrl = &omap5430_cm_mipiext_clkstctrl;
	clkdm.properties = 0;
	genlist_addtail(&clkdm54xx_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_DSS;
	clkdm.id = (int) CLKDM54XX_DSS;
	clkdm.powerdm = PWRDM_DSS;
	clkdm.voltdm = VDD_CORE;
	if (cpu_revision_get() == REV_ES1_0)
		clkdm.clkstctrl = &omap5430es1_cm_dss_clkstctrl;
	else
		clkdm.clkstctrl = &omap5430_cm_dss_clkstctrl;
	clkdm.properties = 0;
	genlist_addtail(&clkdm54xx_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_CUST_EFUSE;
	clkdm.id = (int) CLKDM54XX_CUST_EFUSE;
	clkdm.powerdm = PWRDM_CUST_EFUSE;
	if (cpu_revision_get() == REV_ES1_0)
		clkdm.clkstctrl = &omap5430es1_cm_custefuse_clkstctrl;
	else
		clkdm.clkstctrl = &omap5430_cm_custefuse_clkstctrl;
	clkdm.voltdm = VDD_CORE;
	clkdm.properties = 0;
	genlist_addtail(&clkdm54xx_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_L3_INIT;
	clkdm.id = (int) CLKDM54XX_L3_INIT;
	clkdm.powerdm = PWRDM_L3_INIT;
	if (cpu_revision_get() == REV_ES1_0)
		clkdm.clkstctrl = &omap5430es1_cm_l3init_clkstctrl;
	else
		clkdm.clkstctrl = &omap5430_cm_l3init_clkstctrl;
	clkdm.voltdm = VDD_CORE;
	clkdm.properties = 0;
	genlist_addtail(&clkdm54xx_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_L4_PER;
	clkdm.id = (int) CLKDM54XX_L4_PER;
	if (cpu_revision_get() == REV_ES1_0) {
		clkdm.powerdm = PWRDM_L4_PER;
		clkdm.clkstctrl = &omap5430es1_cm_l4per_clkstctrl;
	} else {
		clkdm.powerdm = PWRDM_CORE;
		clkdm.clkstctrl = &omap5430_cm_l4per_clkstctrl;
	}
	clkdm.voltdm = VDD_CORE;
	clkdm.properties = 0;
	genlist_addtail(&clkdm54xx_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_L4_SEC;
	clkdm.id = (int) CLKDM54XX_L4_SEC;
	if (cpu_revision_get() == REV_ES1_0)
		clkdm.powerdm = PWRDM_L4_PER;
	else
		clkdm.powerdm = PWRDM_CORE;
	clkdm.clkstctrl = NULL;
	clkdm.voltdm = VDD_CORE;
	clkdm.properties = 0;
	genlist_addtail(&clkdm54xx_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_ABE;
	clkdm.id = (int) CLKDM54XX_ABE;
	clkdm.powerdm = PWRDM_ABE;
	if (cpu_revision_get() == REV_ES1_0)
		clkdm.clkstctrl = &omap5430es1_cm_abe_clkstctrl;
	else
		clkdm.clkstctrl = &omap5430_cm_abe_clkstctrl;
	clkdm.voltdm = VDD_CORE;
	clkdm.properties = 0;
	genlist_addtail(&clkdm54xx_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_DSP;
	clkdm.id = (int) CLKDM54XX_DSP;
	clkdm.powerdm = PWRDM_DSP;
	if (cpu_revision_get() == REV_ES1_0)
		clkdm.clkstctrl = &omap5430es1_cm_dsp_clkstctrl;
	else
		clkdm.clkstctrl = &omap5430_cm_dsp_clkstctrl;
	clkdm.voltdm = VDD_MM;
	clkdm.properties = 0;
	genlist_addtail(&clkdm54xx_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_GPU;
	clkdm.id = (int) CLKDM54XX_GPU;
	clkdm.powerdm = PWRDM_GPU;
	if (cpu_revision_get() == REV_ES1_0)
		clkdm.clkstctrl = &omap5430es1_cm_gpu_clkstctrl;
	else
		clkdm.clkstctrl = &omap5430_cm_gpu_clkstctrl;
	clkdm.voltdm = VDD_MM;
	clkdm.properties = 0;
	genlist_addtail(&clkdm54xx_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_IVA;
	clkdm.id = (int) CLKDM54XX_IVA;
	clkdm.powerdm = PWRDM_IVA;
	if (cpu_revision_get() == REV_ES1_0)
		clkdm.clkstctrl = &omap5430es1_cm_iva_clkstctrl;
	else
		clkdm.clkstctrl = &omap5430_cm_iva_clkstctrl;
	clkdm.voltdm = VDD_MM;
	clkdm.properties = 0;
	genlist_addtail(&clkdm54xx_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_MPU;
	clkdm.id = (int) CLKDM54XX_MPU;
	clkdm.powerdm = PWRDM_MPU;
	if (cpu_revision_get() == REV_ES1_0)
		clkdm.clkstctrl = &omap5430es1_cm_mpu_clkstctrl;
	else
		clkdm.clkstctrl = &omap5430_cm_mpu_clkstctrl;
	clkdm.voltdm = VDD_MPU;
	clkdm.properties = 0;
	genlist_addtail(&clkdm54xx_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_NONE;
	clkdm.id = (int) CLKDM54XX_NONE;
	clkdm.powerdm = PWRDM_UNKNOWN;
	clkdm.clkstctrl = NULL;
	clkdm.voltdm = VDD_WKUP;
	clkdm.properties = 0;
	genlist_addtail(&clkdm54xx_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm54xx_init_done = 1;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm54xx_deinit
 * @BRIEF		free dynamically allocated internal data.
 * @DESCRIPTION		free dynamically allocated internal data.
 *			MUST BE CALLED AT END OF EXECUTION.
 *//*------------------------------------------------------------------------ */
void clkdm54xx_deinit(void)
{
	if (clkdm54xx_init_done) {
		genlist_free(&clkdm54xx_list);
		clkdm54xx_init_done = 0;

	}
	dprintf("%s(): deinit done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm54xx_list_get
 * @BRIEF		return the list of clock domains
 * @RETURNS		list of clock domains in case of success
 *			NULL in case of error
 * @DESCRIPTION		return the list of clock domains
 *//*------------------------------------------------------------------------ */
const genlist *clkdm54xx_list_get(void)
{
	clkdm54xx_init();

	return (const genlist *) &clkdm54xx_list;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm54xx_count_get
 * @BRIEF		return the number of clock domains
 * @RETURNS		number of clock domains (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @DESCRIPTION		return the number of clock domains
 *//*------------------------------------------------------------------------ */
int clkdm54xx_count_get(void)
{
	int count;

	clkdm54xx_init();

	count = genlist_getcount(&clkdm54xx_list);

	dprintf("%s() = %d\n", __func__, count);
	return count;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm54xx_name_get
 * @BRIEF		return clock domain name
 * @RETURNS		clock domain name on success
 *			NULL in case of error
 * @param[in]		id: clock domain ID
 * @DESCRIPTION		return clock domain name
 *//*------------------------------------------------------------------------ */
const char *clkdm54xx_name_get(clkdm54xx_id id)
{
	CHECK_ARG_LESS_THAN(id, CLKDM54XX_ID_MAX, NULL);

	return clkdm54xx_names_table[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm54xx_s2id
 * @BRIEF		retrieve clock domain ID matching string s
 * @RETURNS		valid clock domain ID
 *			CLKDM54XX_ID_MAX if no match found
 * @param[in]		s: string
 *			List of recognized strings: "emu", "wkupaon", "coreaon",
 *			"cam", "l4cfg", "emif", "ipu", "l3main2", "l3instr",
 *			"l3main1", "c2c", "dma", "mipiext", "dss", "custefuse",
 *			"l3init", "l4per", "l4sec", "abe", "dsp", "gpu, "iva",
 *			"mpu"
 * @DESCRIPTION		retrieve clock domain ID matching string s
 *//*------------------------------------------------------------------------ */
clkdm54xx_id clkdm54xx_s2id(char *s)
{
	clkdm54xx_id id;

	if (s == NULL)
		id = CLKDM54XX_ID_MAX;
	else if (strcmp(lowercase(s), "emu") == 0)
		id = CLKDM54XX_EMU;
	else if (strcmp(lowercase(s), "wkupaon") == 0)
		id = CLKDM54XX_WKUPAON;
	else if (strcmp(lowercase(s), "coreaon") == 0)
		id = CLKDM54XX_COREAON;
	else if (strcmp(lowercase(s), "cam") == 0)
		id = CLKDM54XX_CAM;
	else if (strcmp(lowercase(s), "l4cfg") == 0)
		id = CLKDM54XX_L4_CFG;
	else if (strcmp(lowercase(s), "emif") == 0)
		id = CLKDM54XX_EMIF;
	else if (strcmp(lowercase(s), "ipu") == 0)
		id = CLKDM54XX_IPU;
	else if (strcmp(lowercase(s), "l3main2") == 0)
		id = CLKDM54XX_L3_MAIN2;
	else if (strcmp(lowercase(s), "l3instr") == 0)
		id = CLKDM54XX_L3_INSTR;
	else if (strcmp(lowercase(s), "l3main1") == 0)
		id = CLKDM54XX_L3_MAIN1;
	else if (strcmp(lowercase(s), "c2c") == 0)
		id = CLKDM54XX_C2C ;
	else if (strcmp(lowercase(s), "dma") == 0)
		id = CLKDM54XX_DMA ;
	else if (strcmp(lowercase(s), "mipiext") == 0)
		id = CLKDM54XX_MIPIEXT ;
	else if (strcmp(lowercase(s), "dss") == 0)
		id = CLKDM54XX_DSS ;
	else if (strcmp(lowercase(s), "custefuse") == 0)
		id = CLKDM54XX_CUST_EFUSE ;
	else if (strcmp(lowercase(s), "l3init") == 0)
		id = CLKDM54XX_L3_INIT ;
	else if (strcmp(lowercase(s), "l4per") == 0)
		id = CLKDM54XX_L4_PER ;
	else if (strcmp(lowercase(s), "l4sec") == 0)
		id = CLKDM54XX_L4_SEC ;
	else if (strcmp(lowercase(s), "abe") == 0)
		id = CLKDM54XX_ABE ;
	else if (strcmp(lowercase(s), "dsp") == 0)
		id = CLKDM54XX_DSP ;
	else if (strcmp(lowercase(s), "gpu") == 0)
		id = CLKDM54XX_GPU ;
	else if (strcmp(lowercase(s), "iva") == 0)
		id = CLKDM54XX_IVA ;
	else if (strcmp(lowercase(s), "mpu") == 0)
		id = CLKDM54XX_MPU ;
	else
		id = CLKDM54XX_ID_MAX;

	dprintf("%s(%s) = %s\n", __func__, s, clkdm54xx_name_get(id));
	return id;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm54xx_config_show
 * @BRIEF		display clock domain configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output file
 * @param[in]		clkdm: clock domain details
 * @DESCRIPTION		display clock domain configuration
 *//*------------------------------------------------------------------------ */
int clkdm54xx_config_show(FILE *stream, clockdm_info clkdm)
{
	unsigned int cm_clkstctrl;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(stream, OMAPCONF_ERR_ARG);

	/* Read register */
	cm_clkstctrl = reg_read(clkdm.clkstctrl);

	/* Decode and display clock domain's configuration */
	switch (clkdm.id) {
	case CLKDM54XX_EMU:
		fprintf(stream, "| %-36s | %-23s |\n", "  EMU_SYS_CLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 8)));
		break;

	case CLKDM54XX_WKUPAON:
		if (cpu_revision_get() != REV_ES1_0) {
			fprintf(stream, "| %-36s | %-23s |\n",
				"  SYS_CLK_ALL (SCRM Level)",
				clkdm_status_name_get((clkdm_status)
					extract_bit(cm_clkstctrl, 15)));
			fprintf(stream, "| %-36s | %-23s |\n",
				"  SYS_CLK_FUNC (w/o EMU_SYS_CLK)",
				clkdm_status_name_get((clkdm_status)
					extract_bit(cm_clkstctrl, 14)));
		}
		fprintf(stream, "| %-36s | %-23s |\n",
			"  WKUPAON_IO_SRCOMP_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 13)));
		fprintf(stream, "| %-36s | %-23s |\n", "  WKUPAON_GICLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 12)));
		fprintf(stream, "| %-36s | %-23s |\n", "  WKUPAON_32K_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 11)));
		fprintf(stream, "| %-36s | %-23s |\n", "  ABE_LP_CLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 9)));
		fprintf(stream, "| %-36s | %-23s |\n",
				"  SYS_CLK (w/ EMU_SYS_CLK)",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 8)));
		break;

	case CLKDM54XX_COREAON:
		fprintf(stream, "| %-36s | %-23s |\n",
			"  COREAON_IO_SRCOMP_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 14)));
		if (cpu_revision_get() == REV_ES1_0)
			fprintf(stream, "| %-36s | %-23s |\n",
				"  COREAON_TS_GFCLK",
				clkdm_status_name_get((clkdm_status)
					extract_bit(cm_clkstctrl, 13)));
		fprintf(stream, "| %-36s | %-23s |\n", "  COREAON_32K_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 12)));
		fprintf(stream, "| %-36s | %-23s |\n", "  SR_CORE_SYS_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 11)));
		fprintf(stream, "| %-36s | %-23s |\n", "  SR_MM_SYS_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 10)));
		fprintf(stream, "| %-36s | %-23s |\n", "  SR_MPU_SYS_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 9)));
		fprintf(stream, "| %-36s | %-23s |\n", "  COREAON_L4_GICLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 8)));
		break;

	case CLKDM54XX_CAM:
		fprintf(stream, "| %-36s | %-23s |\n", "  CAM_L3_GIFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 12)));
		fprintf(stream, "| %-36s | %-23s |\n", "  CAM_BOOST_GCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 11)));
		fprintf(stream, "| %-36s | %-23s |\n", "  FDIF_GCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 10)));
		fprintf(stream, "| %-36s | %-23s |\n", "  CSI_PHY_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 9)));
		fprintf(stream, "| %-36s | %-23s |\n", "  CAM_GCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 8)));
		break;

	case CLKDM54XX_L4_CFG:
		if (cpu_revision_get() == REV_ES1_0)
			fprintf(stream, "| %-36s | %-23s |\n",
				"  CORE_TS_GFCLK",
				clkdm_status_name_get((clkdm_status)
					extract_bit(cm_clkstctrl, 9)));
		fprintf(stream, "| %-36s | %-23s |\n", "  L4CFG_L4_GICLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 8)));
		break;

	case CLKDM54XX_EMIF:
		if (cpu_revision_get() != REV_ES1_0)
			fprintf(stream, "| %-36s | %-23s |\n",
				"  EMIF_LL_GCLK",
				clkdm_status_name_get((clkdm_status)
					extract_bit(cm_clkstctrl, 11)));

		fprintf(stream, "| %-36s | %-23s |\n", "  EMIF_PHY_GCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 10)));
		fprintf(stream, "| %-36s | %-23s |\n", "  DLL_GCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 9)));
		fprintf(stream, "| %-36s | %-23s |\n", "  EMIF_L3_GICLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 8)));
		break;

	case CLKDM54XX_IPU:
		fprintf(stream, "| %-36s | %-23s |\n", "  IPU_CLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 8)));
		break;

	case CLKDM54XX_L3_MAIN2:
		fprintf(stream, "| %-36s | %-23s |\n", "  L3MAIN2_L3_GICLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 8)));
		break;

	case CLKDM54XX_L3_INSTR:
		if (cpu_revision_get() != REV_ES1_0)
			fprintf(stream, "| %-36s | %-23s |\n",
				"  L3INSTR_TS_GCLK",
				clkdm_status_name_get((clkdm_status)
					extract_bit(cm_clkstctrl, 10)));

		fprintf(stream, "| %-36s | %-23s |\n",
			"  L3INSTR_DLL_AGING_GCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 9)));
		fprintf(stream, "| %-36s | %-23s |\n", "  L3INSTR_L3_GICLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 8)));
		break;

	case CLKDM54XX_L3_MAIN1:
		fprintf(stream, "| %-36s | %-23s |\n", "  L3MAIN1_L3_GICLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 8)));
		break;

	case CLKDM54XX_C2C:
		if (cpu_revision_get() == REV_ES1_0) {
			fprintf(stream, "| %-36s | %-23s |\n", "  C2C_L4_GICLK",
				clkdm_status_name_get((clkdm_status)
					extract_bit(cm_clkstctrl, 9)));
			fprintf(stream, "| %-36s | %-23s |\n", "  C2C_L3_GICLK",
				clkdm_status_name_get((clkdm_status)
					extract_bit(cm_clkstctrl, 8)));
		} else {
			fprintf(stream, "| %-36s | %-23s |\n", "  C2C_GICLK",
				clkdm_status_name_get((clkdm_status)
					extract_bit(cm_clkstctrl, 10)));
			fprintf(stream, "| %-36s | %-23s |\n", "  C2C_GFCLK",
				clkdm_status_name_get((clkdm_status)
					extract_bit(cm_clkstctrl, 9)));
			fprintf(stream, "| %-36s | %-23s |\n", "  C2C_L4_GICLK",
				clkdm_status_name_get((clkdm_status)
					extract_bit(cm_clkstctrl, 8)));
		}
		break;

	case CLKDM54XX_DMA:
		fprintf(stream, "| %-36s | %-23s |\n", "  DMA_L3_GICLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 8)));
		break;

	case CLKDM54XX_MIPIEXT:
		fprintf(stream, "| %-36s | %-23s |\n", "  UNIPRO1_PHY_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 13)));
		fprintf(stream, "| %-36s | %-23s |\n",
			"  UNIPRO1_TXPHY_LS_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 12)));
		fprintf(stream, "| %-36s | %-23s |\n",
			"  MIPIEXT_PHY_REF_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 11)));
		fprintf(stream, "| %-36s | %-23s |\n", "  UNIPRO1_DPLL_CLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 10)));
		fprintf(stream, "| %-36s | %-23s |\n", "  MIPIEXT_L3_GICLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 8)));
		break;

	case CLKDM54XX_DSS:
		if (cpu_revision_get() != REV_ES1_0)
			fprintf(stream, "| %-36s | %-23s |\n", "  BB2D_GFCLK",
				clkdm_status_name_get((clkdm_status)
					extract_bit(cm_clkstctrl, 13)));

		fprintf(stream, "| %-36s | %-23s |\n", "  HDMI_CEC_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 12)));
		fprintf(stream, "| %-36s | %-23s |\n", "  HDMI_PHY_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 11)));
		fprintf(stream, "| %-36s | %-23s |\n", "  DSS_SYS_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 10)));
		fprintf(stream, "| %-36s | %-23s |\n", "  DSS_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 9)));
		fprintf(stream, "| %-36s | %-23s |\n", "  DSS_L[3-4]_GICLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 8)));
		break;

	case CLKDM54XX_CUST_EFUSE:
		fprintf(stream, "| %-36s | %-23s |\n", "  CUSTEFUSE_SYS_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 9)));
		fprintf(stream, "| %-36s | %-23s |\n", "  CUSTEFUSE_L4_GICLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 8)));
		break;

	case CLKDM54XX_L3_INIT:
		fprintf(stream, "| %-36s | %-23s |\n", "  USB_OTG_SS_REF_CLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 31)));
		fprintf(stream, "| %-36s | %-23s |\n", "  UTMI_P3_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 30)));
		fprintf(stream, "| %-36s | %-23s |\n", "  L3INIT_60M_P2_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 29)));
		fprintf(stream, "| %-36s | %-23s |\n", "  L3INIT_60M_P1_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 28)));
		fprintf(stream, "| %-36s | %-23s |\n", "  HSIC_P2_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 27)));
		fprintf(stream, "| %-36s | %-23s |\n", "  HSIC_P1_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 26)));
		fprintf(stream, "| %-36s | %-23s |\n", "  UTMI_ROOT_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 25)));
		fprintf(stream, "| %-36s | %-23s |\n", "  TLL_CH2_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 24)));
		fprintf(stream, "| %-36s | %-23s |\n", "  TLL_CH1_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 23)));
		fprintf(stream, "| %-36s | %-23s |\n", "  TLL_CH0_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 22)));
		fprintf(stream, "| %-36s | %-23s |\n", "  L3INIT_P2_480M_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 21)));
		fprintf(stream, "| %-36s | %-23s |\n", "  L3INIT_P1_480M_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 20)));
		fprintf(stream, "| %-36s | %-23s |\n", "  SATA_REF_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 19)));
		fprintf(stream, "| %-36s | %-23s |\n", "  MMC2_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 18)));
		fprintf(stream, "| %-36s | %-23s |\n", "  MMC1_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 17)));
		fprintf(stream, "| %-36s | %-23s |\n", "  HSI_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 16)));
		fprintf(stream, "| %-36s | %-23s |\n", "  USB_DPLL_HS_CLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 15)));
		fprintf(stream, "| %-36s | %-23s |\n", "  USB_DPLL_CLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 14)));
		fprintf(stream, "| %-36s | %-23s |\n", "  UNIPRO2_PHY_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 13)));
		fprintf(stream, "| %-36s | %-23s |\n", "  L3INIT_48M_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 12)));
		fprintf(stream, "| %-36s | %-23s |\n",
			"  L3INIT_USB_OTG_SS_LFPS_TX_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 11)));
		fprintf(stream, "| %-36s | %-23s |\n", "  UNIPRO2_DPLL_CLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 10)));
		fprintf(stream, "| %-36s | %-23s |\n", "  L3INIT_L4_GICLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 9)));
		fprintf(stream, "| %-36s | %-23s |\n", "  L3INIT_L3_GICLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 8)));
		fprintf(stream, "| %-36s | %-23s |\n", "  HSIC_P3_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 7)));
		fprintf(stream, "| %-36s | %-23s |\n", "  HSIC_P3_480M_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 6)));
		fprintf(stream, "| %-36s | %-23s |\n",
				"  UNIPRO2_PHY_REF_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 5)));
		fprintf(stream, "| %-36s | %-23s |\n", "  PAD_XCLK60MHSP2",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 4)));
		if (cpu_revision_get() == REV_ES1_0)
			fprintf(stream, "| %-36s | %-23s |\n",
				"  PAD_XCLK60MHSP1",
				clkdm_status_name_get((clkdm_status)
					extract_bit(cm_clkstctrl, 3)));
		else
			fprintf(stream, "| %-36s | %-23s |\n",
				"  MMC1_32K_GFCLK",
				clkdm_status_name_get((clkdm_status)
					extract_bit(cm_clkstctrl, 2)));
		break;

	case CLKDM54XX_L4_PER:
		if (cpu_revision_get() == REV_ES1_0) {
			fprintf(stream, "| %-36s | %-23s |\n",
				"  PAD_SLIMBUS2_CLK",
				clkdm_status_name_get((clkdm_status)
					extract_bit(cm_clkstctrl, 26)));
			fprintf(stream, "| %-36s | %-23s |\n",
				"  PER_ABE_24M_GFCLK",
				clkdm_status_name_get((clkdm_status)
					extract_bit(cm_clkstctrl, 25)));
		}
		fprintf(stream, "| %-36s | %-23s |\n", "  PER_96M_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 19)));
		fprintf(stream, "| %-36s | %-23s |\n", "  PER_48M_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 18)));
		fprintf(stream, "| %-36s | %-23s |\n", "  PER_32K_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 17)));
		if (cpu_revision_get() == REV_ES1_0)
			fprintf(stream, "| %-36s | %-23s |\n",
				"  PER_24M_GFCLK",
				clkdm_status_name_get((clkdm_status)
					extract_bit(cm_clkstctrl, 16)));
		fprintf(stream, "| %-36s | %-23s |\n", "  PER_12M_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 15)));
		fprintf(stream, "| %-36s | %-23s |\n", "  TIMER9_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 14)));
		fprintf(stream, "| %-36s | %-23s |\n", "  TIMER4_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 13)));
		fprintf(stream, "| %-36s | %-23s |\n", "  TIMER3_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 12)));
		fprintf(stream, "| %-36s | %-23s |\n", "  TIMER2_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 11)));
		fprintf(stream, "| %-36s | %-23s |\n", "  TIMER11_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 10)));
		fprintf(stream, "| %-36s | %-23s |\n", "  TIMER10_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 9)));
		fprintf(stream, "| %-36s | %-23s |\n", "  L4PER_L4_GICLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 8)));
		break;

	case CLKDM54XX_L4_SEC:
		fprintf(stream, "| %-36s | %-23s |\n", "  L4SEC_L4_GICLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 9)));
		fprintf(stream, "| %-36s | %-23s |\n", "  L4SEC_L3_GICLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 8)));
		break;

	case CLKDM54XX_ABE:
		fprintf(stream, "| %-36s | %-23s |\n", "  PAD_SLIMBUS1_CLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 15)));
		fprintf(stream, "| %-36s | %-23s |\n", "  PAD_CLKS",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 14)));
		fprintf(stream, "| %-36s | %-23s |\n", "  ABE_24M_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 13)));
		fprintf(stream, "| %-36s | %-23s |\n", "  ABE_32K_CLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 12)));
		fprintf(stream, "| %-36s | %-23s |\n", "  ABE_SYS_CLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 11)));
		fprintf(stream, "| %-36s | %-23s |\n", "  FUNC_24M_GFCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 10)));
		fprintf(stream, "| %-36s | %-23s |\n", "  ABE_GICLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 9)));
		fprintf(stream, "| %-36s | %-23s |\n", "  DPLL_ABE_X2_CLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 8)));
		break;

	case CLKDM54XX_DSP:
		fprintf(stream, "| %-36s | %-23s |\n", "  DSP_GCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 8)));
		break;

	case CLKDM54XX_GPU:
		fprintf(stream, "| %-36s | %-23s |\n", "  GPU_HYD_GCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 10)));
		fprintf(stream, "| %-36s | %-23s |\n", "  GPU_CORE_GCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 9)));
		fprintf(stream, "| %-36s | %-23s |\n", "  GPU_L3_GICLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 8)));
		break;

	case CLKDM54XX_IVA:
		fprintf(stream, "| %-36s | %-23s |\n", "  IVA_GCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 8)));
		break;

	case CLKDM54XX_MPU:
		fprintf(stream, "| %-36s | %-23s |\n", "  MPU_GCLK",
			clkdm_status_name_get(
				(clkdm_status) extract_bit(cm_clkstctrl, 8)));
		break;

	default:
		break;
	}

	return 0;
}
