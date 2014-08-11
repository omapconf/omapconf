/*
 *
 * @Component			OMAPCONF
 * @Filename			clkdm_am335x.c
 * @Description			AM335X Clock Domain Definitions & APIs
 * @Author			Gilberto Rodriguez <gilrod@ti.com>
 * @Date			2014
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
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


#include <clkdm_am335x.h>
#include <cm_am335x.h>
#include <cpuinfo.h>
#include <lib.h>
#include <powerdomain.h>
#include <prm_am335x.h>
#include <stdio.h>
#include <string.h>
#include <voltdomain.h>


/* #define CLKDM_AM335X_DEBUG */
#ifdef CLKDM_AM335X_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static const char
	clkdm_am335x_names_table[CLKDM_AM335X_ID_MAX][CLKDM_AM335X_MAX_NAME_LENGTH] = {
	"PER L4LS",
	"PER L3S",
	"PER L3",
	"PER L4HS",
	"PER OCPWP L3",
	"PER CPSW",
	"PER LCDC",
	"PER CLK 24MHZ",
	"WKUP",
	"WKUP L3 AON",
	"WKUP L4 WKUP AON",
	"MPU",
	"RTC",
	"GFX L3",
	"GFX L4LS GFX",
	"CEFUSE",
	"NONE" };


static unsigned short clkdm_am335x_init_done = 0;
genlist clkdm_am335x_list;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm_am335x_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void clkdm_am335x_init(void)
{
	clockdm_info clkdm;

	if (clkdm_am335x_init_done)
		return;

	genlist_init(&clkdm_am335x_list);

	clkdm.name = CLKDM_PER_L4LS;
	clkdm.id = (int) CLKDM_AM335X_PER_L4LS;
	clkdm.powerdm = PWRDM_PER;
	clkdm.voltdm = VDD_CORE;
	clkdm.clkstctrl = &am335x_cm_per_l4ls_clkstctrl;
	clkdm.clkstctrl_bit = 8;
	clkdm.properties = 0; /* TBD */
	genlist_addtail(&clkdm_am335x_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_PER_L3S;
	clkdm.id = (int) CLKDM_AM335X_PER_L3S;
	clkdm.powerdm = PWRDM_PER;
	clkdm.voltdm = VDD_CORE;
	clkdm.clkstctrl = &am335x_cm_per_l3s_clkstctrl;
	clkdm.clkstctrl_bit = 3;
	clkdm.properties = 0; /* TBD */
	genlist_addtail(&clkdm_am335x_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_PER_L3;
	clkdm.id = (int) CLKDM_AM335X_PER_L3;
	clkdm.powerdm = PWRDM_PER;
	clkdm.voltdm = VDD_CORE;
	clkdm.clkstctrl = &am335x_cm_per_l3_clkstctrl;
	clkdm.clkstctrl_bit = 4;
	clkdm.properties = 0; /* TBD */
	genlist_addtail(&clkdm_am335x_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_PER_L4HS;
	clkdm.id = (int) CLKDM_AM335X_PER_L4HS;
	clkdm.powerdm = PWRDM_PER;
	clkdm.voltdm = VDD_CORE;
	clkdm.clkstctrl = &am335x_cm_per_l4hs_clkstctrl;
	clkdm.clkstctrl_bit = 3;
	clkdm.properties = 0; /* TBD */
	genlist_addtail(&clkdm_am335x_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_PER_OCPWP_L3;
	clkdm.id = (int) CLKDM_AM335X_PER_OCPWP_L3;
	clkdm.powerdm = PWRDM_PER;
	clkdm.voltdm = VDD_CORE;
	clkdm.clkstctrl = &am335x_cm_per_ocpwp_l3_clkstctrl;
	clkdm.clkstctrl_bit = 4;
	clkdm.properties = 0; /* TBD */
	genlist_addtail(&clkdm_am335x_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_PER_PRU_ICSS;
	clkdm.id = (int) CLKDM_AM335X_PER_PRU_ICSS;
	clkdm.powerdm = PWRDM_PER;
	clkdm.voltdm = VDD_CORE;
	clkdm.clkstctrl = &am335x_cm_per_pru_icss_clkstctrl;
	clkdm.clkstctrl_bit = 3;
	clkdm.properties = 0; /* TBD */
	genlist_addtail(&clkdm_am335x_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_PER_CPSW;
	clkdm.id = (int) CLKDM_AM335X_PER_CPSW;
	clkdm.powerdm = PWRDM_PER;
	clkdm.voltdm = VDD_CORE;
	clkdm.clkstctrl = &am335x_cm_per_cpsw_clkstctrl;
	clkdm.clkstctrl_bit = 4;
	clkdm.properties = 0; /* TBD */
	genlist_addtail(&clkdm_am335x_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_PER_LCDC;
	clkdm.id = (int) CLKDM_AM335X_PER_LCDC;
	clkdm.powerdm = PWRDM_PER;
	clkdm.voltdm = VDD_CORE;
	clkdm.clkstctrl = &am335x_cm_per_lcdc_clkstctrl;
	clkdm.clkstctrl_bit = 4;
	clkdm.properties = 0; /* TBD */
	genlist_addtail(&clkdm_am335x_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_PER_CLK_24MHZ;
	clkdm.id = (int) CLKDM_AM335X_PER_CLK_24MHZ;
	clkdm.powerdm = PWRDM_PER;
	clkdm.voltdm = VDD_CORE;
	clkdm.clkstctrl = &am335x_cm_per_clk_24mhz_clkstctrl;
	clkdm.clkstctrl_bit = 4;
	clkdm.properties = 0; /* TBD */
	genlist_addtail(&clkdm_am335x_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_WKUP;
	clkdm.id = (int) CLKDM_AM335X_WKUP;
	clkdm.powerdm = PWRDM_WKUP;
	clkdm.voltdm = VDD_CORE;
	clkdm.clkstctrl = &am335x_cm_wkup_clkstctrl;
	clkdm.clkstctrl_bit = 2;
	clkdm.properties = 0; /* TBD */
	genlist_addtail(&clkdm_am335x_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_WKUP_L3_AON;
	clkdm.id = (int) CLKDM_AM335X_WKUP_L3_AON;
	clkdm.powerdm = PWRDM_WKUP;
	clkdm.voltdm = VDD_CORE;
	clkdm.clkstctrl = &am335x_cm_l3_aon_clkstctrl;
	clkdm.clkstctrl_bit = 3;
	clkdm.properties = 0; /* TBD */
	genlist_addtail(&clkdm_am335x_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_WKUP_L4_WKUP_AON;
	clkdm.id = (int) CLKDM_AM335X_WKUP_L4_WKUP_AON;
	clkdm.powerdm = PWRDM_WKUP;
	clkdm.voltdm = VDD_CORE;
	clkdm.clkstctrl = &am335x_cm_l4_wkup_aon_clkstctrl;
	clkdm.clkstctrl_bit = 2;
	clkdm.properties = 0; /* TBD */
	genlist_addtail(&clkdm_am335x_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_MPU;
	clkdm.id = (int) CLKDM_AM335X_MPU;
	clkdm.powerdm = PWRDM_MPU;
	clkdm.voltdm = VDD_MPU;
	clkdm.clkstctrl = &am335x_cm_mpu_clkstctrl;
	clkdm.clkstctrl_bit = 2;
	clkdm.properties = 0; /* TBD */
	genlist_addtail(&clkdm_am335x_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_RTC;
	clkdm.id = (int) CLKDM_AM335X_RTC;
	clkdm.powerdm = PWRDM_RTC;
	clkdm.voltdm = VDD_RTC;
	clkdm.clkstctrl = &am335x_cm_rtc_clkstctrl;
	clkdm.clkstctrl_bit = 8;
	clkdm.properties = 0; /* TBD */
	genlist_addtail(&clkdm_am335x_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_GFX_L3;
	clkdm.id = (int) CLKDM_AM335X_GFX_L3;
	clkdm.powerdm = PWRDM_GFX;
	clkdm.voltdm = VDD_CORE;
	clkdm.clkstctrl = &am335x_cm_gfx_l3_clkstctrl;
	clkdm.clkstctrl_bit = 8;
	clkdm.properties = 0; /* TBD */
	genlist_addtail(&clkdm_am335x_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_GFX_L4LS_GFX;
	clkdm.id = (int) CLKDM_AM335X_GFX_L4LS_GFX;
	clkdm.powerdm = PWRDM_GFX;
	clkdm.voltdm = VDD_CORE;
	clkdm.clkstctrl = &am335x_cm_gfx_l4ls_gfx_clkstctrl;
	clkdm.clkstctrl_bit = 8;
	clkdm.properties = 0; /* TBD */
	genlist_addtail(&clkdm_am335x_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_CEFUSE;
	clkdm.id = (int) CLKDM_AM335X_CEFUSE;
	clkdm.powerdm = PWRDM_EFUSE;
	clkdm.voltdm = VDD_CORE;
	clkdm.clkstctrl = &am335x_cm_cefuse_clkstctrl;
	clkdm.clkstctrl_bit = 9;
	clkdm.properties = 0; /* TBD */
	genlist_addtail(&clkdm_am335x_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm.name = CLKDM_NONE;
	clkdm.id = (int) CLKDM_AM335X_NONE;
	clkdm.powerdm = PWRDM_UNKNOWN;
	clkdm.voltdm = VDD_CORE;
	clkdm.clkstctrl = NULL;
	clkdm.properties = 0; /* TBD */
	genlist_addtail(&clkdm_am335x_list, (void *) &clkdm, sizeof(clockdm_info));

	clkdm_am335x_init_done = 1;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm_am335x_deinit
 * @BRIEF		free dynamically allocated internal data.
 * @DESCRIPTION		free dynamically allocated internal data.
 *			MUST BE CALLED AT END OF EXECUTION.
 *//*------------------------------------------------------------------------ */
void clkdm_am335x_deinit(void)
{
	if (clkdm_am335x_init_done) {
		genlist_free(&clkdm_am335x_list);
		clkdm_am335x_init_done = 0;

	}
	dprintf("%s(): deinit done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm_am335x_list_get
 * @BRIEF		return the list of clock domains
 * @RETURNS		list of clock domains in case of success
 *			NULL in case of error
 * @DESCRIPTION		return the list of clock domains
 *//*------------------------------------------------------------------------ */
const genlist *clkdm_am335x_list_get(void)
{
	clkdm_am335x_init();

	return (const genlist *) &clkdm_am335x_list;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm_am335x_count_get
 * @BRIEF		return the number of clock domains
 * @RETURNS		number of clock domains (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @DESCRIPTION		return the number of clock domains
 *//*------------------------------------------------------------------------ */
int clkdm_am335x_count_get(void)
{
	int count;

	clkdm_am335x_init();

	count = genlist_getcount(&clkdm_am335x_list);

	dprintf("%s() = %d\n", __func__, count);
	return count;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm_am335x_name_get
 * @BRIEF		return clock domain name
 * @RETURNS		clock domain name on success
 *			NULL in case of error
 * @param[in]		id: clock domain ID
 * @DESCRIPTION		return clock domain name
 *//*------------------------------------------------------------------------ */
const char *clkdm_am335x_name_get(clkdm_am335x_id id)
{
	CHECK_ARG_LESS_THAN(id, CLKDM_AM335X_ID_MAX, NULL);

	return clkdm_am335x_names_table[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm_am335x_status_get
 * @BRIEF		return clock  domain status for AM335X
 * @RETURNS		clock domain status on success
 *			CLKDM
 * @param[in]		cm_clkstctrl: CM_xyz_CLKSTCTRL register content
 * @param[in]		clkstctrl_bit: domain bit in CM_xyz_CLKSTCTRL register
 * @DESCRIPTION		return clock domain status
 *//*------------------------------------------------------------------------ */
clkdm_status clkdm_am335x_status_get(unsigned int cm_clkstctrl,
	unsigned int clkstctrl_bit)
{
	clkdm_status clkdmst;
	unsigned int val;

	/* Retrieve clock domain status */
	val = extract_bitfield(cm_clkstctrl, clkstctrl_bit, 24);
	if (val == 0)
		clkdmst = CLKDM_GATED;
	else
		clkdmst = CLKDM_RUNNING;
	dprintf("%s(): cm_clkstctrl=0x%08X => clkst=%u (%s) (bit [%u]) \n",
		__func__, cm_clkstctrl, clkdmst, clkdm_status_name_get(clkdmst),
		clkstctrl_bit);

	return clkdmst;
}
