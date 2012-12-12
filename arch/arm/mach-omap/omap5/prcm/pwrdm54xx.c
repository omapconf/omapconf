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
	if (cpu_revision_get() == REV_ES1_0) {
		pwrdm.pwrstctrl = &omap5430es1_pm_emu_pwrstctrl;
		pwrdm.pwrstst = &omap5430es1_pm_emu_pwrstst;
	} else {
		pwrdm.pwrstctrl = &omap5430_pm_emu_pwrstctrl;
		pwrdm.pwrstst = &omap5430_pm_emu_pwrstst;
	}
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
	if (cpu_revision_get() == REV_ES1_0) {
		pwrdm.pwrstctrl = &omap5430es1_pm_cam_pwrstctrl;
		pwrdm.pwrstst = &omap5430es1_pm_cam_pwrstst;
	} else {
		pwrdm.pwrstctrl = &omap5430_pm_cam_pwrstctrl;
		pwrdm.pwrstst = &omap5430_pm_cam_pwrstst;
	}
	pwrdm.properties = PWRDM_HAS_LAST_STATE;
	genlist_addtail(&pwrdm54xx_list, (void *) &pwrdm, sizeof(powerdm_info));

	pwrdm.name = PWRDM_CORE;
	pwrdm.id = (int) PWRDM54XX_CORE;
	pwrdm.voltdm = VDD_CORE;
	if (cpu_revision_get() == REV_ES1_0) {
		pwrdm.pwrstctrl = &omap5430es1_pm_core_pwrstctrl;
		pwrdm.pwrstst = &omap5430es1_pm_core_pwrstst;
	} else {
		pwrdm.pwrstctrl = &omap5430_pm_core_pwrstctrl;
		pwrdm.pwrstst = &omap5430_pm_core_pwrstst;
	}
	pwrdm.properties = PWRDM_HAS_LAST_STATE | PWRDM_HAS_LOGIC_RET_STATE_CTRL_BIT;
	genlist_addtail(&pwrdm54xx_list, (void *) &pwrdm, sizeof(powerdm_info));

	pwrdm.name = PWRDM_DSS;
	pwrdm.id = (int) PWRDM54XX_DSS;
	pwrdm.voltdm = VDD_CORE;
	if (cpu_revision_get() == REV_ES1_0) {
		pwrdm.pwrstctrl = &omap5430es1_pm_dss_pwrstctrl;
		pwrdm.pwrstst = &omap5430es1_pm_dss_pwrstst;
	} else {
		pwrdm.pwrstctrl = &omap5430_pm_dss_pwrstctrl;
		pwrdm.pwrstst = &omap5430_pm_dss_pwrstst;
	}
	pwrdm.properties = PWRDM_HAS_LAST_STATE | PWRDM_HAS_LOGIC_RET_STATE_CTRL_BIT;
	genlist_addtail(&pwrdm54xx_list, (void *) &pwrdm, sizeof(powerdm_info));

	pwrdm.name = PWRDM_CUST_EFUSE;
	pwrdm.id = (int) PWRDM54XX_CUST_EFUSE;
	pwrdm.voltdm = VDD_CORE;
	if (cpu_revision_get() == REV_ES1_0) {
		pwrdm.pwrstctrl = &omap5430es1_pm_custefuse_pwrstctrl;
		pwrdm.pwrstst = &omap5430es1_pm_custefuse_pwrstst;
	} else {
		pwrdm.pwrstctrl = &omap5430_pm_custefuse_pwrstctrl;
		pwrdm.pwrstst = &omap5430_pm_custefuse_pwrstst;
	}
	pwrdm.properties = PWRDM_HAS_LAST_STATE;
	genlist_addtail(&pwrdm54xx_list, (void *) &pwrdm, sizeof(powerdm_info));

	pwrdm.name = PWRDM_L3_INIT;
	pwrdm.id = (int) PWRDM54XX_L3_INIT;
	pwrdm.voltdm = VDD_CORE;
	if (cpu_revision_get() == REV_ES1_0) {
		pwrdm.pwrstctrl = &omap5430es1_pm_l3init_pwrstctrl;
		pwrdm.pwrstst = &omap5430es1_pm_l3init_pwrstst;
	} else {
		pwrdm.pwrstctrl = &omap5430_pm_l3init_pwrstctrl;
		pwrdm.pwrstst = &omap5430_pm_l3init_pwrstst;
	}
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
	if (cpu_revision_get() == REV_ES1_0) {
		pwrdm.pwrstctrl = &omap5430es1_pm_abe_pwrstctrl;
		pwrdm.pwrstst = &omap5430es1_pm_abe_pwrstst;
	} else {
		pwrdm.pwrstctrl = &omap5430_pm_abe_pwrstctrl;
		pwrdm.pwrstst = &omap5430_pm_abe_pwrstst;
	}
	pwrdm.properties = PWRDM_HAS_LAST_STATE | PWRDM_HAS_LOGIC_RET_STATE_CTRL_BIT;
	genlist_addtail(&pwrdm54xx_list, (void *) &pwrdm, sizeof(powerdm_info));

	pwrdm.name = PWRDM_DSP;
	pwrdm.id = (int) PWRDM54XX_DSP;
	pwrdm.voltdm = VDD_MM;
	if (cpu_revision_get() == REV_ES1_0) {
		pwrdm.pwrstctrl = &omap5430es1_pm_dsp_pwrstctrl;
		pwrdm.pwrstst = &omap5430es1_pm_dsp_pwrstst;
	} else {
		pwrdm.pwrstctrl = &omap5430_pm_dsp_pwrstctrl;
		pwrdm.pwrstst = &omap5430_pm_dsp_pwrstst;
	}
	pwrdm.properties = PWRDM_HAS_LAST_STATE | PWRDM_HAS_LOGIC_RET_STATE_CTRL_BIT;
	genlist_addtail(&pwrdm54xx_list, (void *) &pwrdm, sizeof(powerdm_info));

	pwrdm.name = PWRDM_GPU;
	pwrdm.id = (int) PWRDM54XX_GPU;
	pwrdm.voltdm = VDD_MM;
	if (cpu_revision_get() == REV_ES1_0) {
		pwrdm.pwrstctrl = &omap5430es1_pm_gpu_pwrstctrl;
		pwrdm.pwrstst = &omap5430es1_pm_gpu_pwrstst;
	} else {
		pwrdm.pwrstctrl = &omap5430_pm_gpu_pwrstctrl;
		pwrdm.pwrstst = &omap5430_pm_gpu_pwrstst;
	}
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
	if (cpu_revision_get() == REV_ES1_0) {
		pwrdm.pwrstctrl = &omap5430es1_pm_iva_pwrstctrl;
		pwrdm.pwrstst = &omap5430es1_pm_iva_pwrstst;
	} else {
		pwrdm.pwrstctrl = &omap5430_pm_iva_pwrstctrl;
		pwrdm.pwrstst = &omap5430_pm_iva_pwrstst;
	}
	pwrdm.properties = PWRDM_HAS_LOGIC_RET_STATE_CTRL_BIT | PWRDM_HAS_LAST_STATE;
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
	if (cpu_revision_get() == REV_ES1_0) {
		pwrdm.pwrstctrl = &omap5430es1_pm_mpu_pwrstctrl;
		pwrdm.pwrstst = &omap5430es1_pm_mpu_pwrstst;
	} else {
		pwrdm.pwrstctrl = &omap5430_pm_mpu_pwrstctrl;
		pwrdm.pwrstst = &omap5430_pm_mpu_pwrstst;
	}
	pwrdm.properties = PWRDM_HAS_LAST_STATE | PWRDM_HAS_LOGIC_RET_STATE_CTRL_BIT;
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
 * @FUNCTION		pwrdm54xx_config_show
 * @BRIEF		decode and display power domain configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output file
 * @param[in]		pwrdm: power domain details
 * @DESCRIPTION		decode and display power domain configuration
 *//*------------------------------------------------------------------------ */
int pwrdm54xx_config_show(FILE *stream, powerdm_info pwrdm)
{
	pwrdm_state st_curr, st_tgt;
	unsigned int pwrstctrl;
	unsigned int pwrstst;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(stream, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(pwrdm.id, PWRDM54XX_ID_MAX, OMAPCONF_ERR_ARG);

	if (pwrdm.pwrstctrl != NULL)
		pwrstctrl = reg_read(pwrdm.pwrstctrl);
	else
		pwrstctrl = 0;
	if (pwrdm.pwrstst != NULL)
		pwrstst = reg_read(pwrdm.pwrstst);
	else
		pwrstst = 0;

	switch (pwrdm.id) {
	case PWRDM54XX_EMU:
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"Memory", "", "");
		st_curr = (pwrdm_state) extract_bitfield(pwrstst, 4, 2);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    EMU bank", pwrdm_state_name_get(st_curr), "");
		break;
	case PWRDM54XX_CAM:
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"Memory", "", "");
		st_curr = (pwrdm_state) extract_bitfield(pwrstst, 4, 2);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    MEM", pwrdm_state_name_get(st_curr), "");
		break;
	case PWRDM54XX_CORE:
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"Memory", "", "");
		st_curr = (pwrdm_state) extract_bitfield(pwrstst, 12, 2);
		st_tgt = (pwrdm_state) extract_bit(pwrstctrl, 12);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    OCP_WP/UNIPRO1/DMM bank2",
			pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));

		st_curr = (pwrdm_state) extract_bitfield(pwrstst, 10, 2);
		st_tgt = (pwrdm_state) extract_bit(pwrstctrl, 11);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    IPU UNICACHE", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));

		st_curr = (pwrdm_state) extract_bitfield(pwrstst, 8, 2);
		st_tgt = (pwrdm_state) extract_bit(pwrstctrl, 10);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    IPU L2RAM", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));

		st_curr = (pwrdm_state) extract_bitfield(pwrstst, 6, 2);
		st_tgt = (pwrdm_state) extract_bit(pwrstctrl, 9);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    OCMRAM", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));

		st_curr = (pwrdm_state) extract_bitfield(pwrstst, 4, 2);
		st_tgt = (pwrdm_state) extract_bit(pwrstctrl, 8);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    DMA/ICR/DMM bank1", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));
		break;
	case PWRDM54XX_DSS:
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"Memory", "", "");
		st_curr = (pwrdm_state) extract_bitfield(pwrstst, 4, 2);
		st_tgt = (pwrdm_state) extract_bit(pwrstctrl, 8);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    MEM", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));
		break;
	case PWRDM54XX_L3_INIT:
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"Memory", "", "");
		st_curr = (pwrdm_state) extract_bitfield(pwrstst, 6, 2);
		st_tgt = (pwrdm_state) extract_bit(pwrstctrl, 9);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    L3INIT bank2", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));

		st_curr = (pwrdm_state) extract_bitfield(pwrstst, 4, 2);
		st_tgt = (pwrdm_state) extract_bit(pwrstctrl, 8);
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
		st_curr = (pwrdm_state) extract_bitfield(pwrstst, 6, 2);
		st_tgt = (pwrdm_state) extract_bit(pwrstctrl, 9);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    NONRETAINED bank", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));

		st_curr = (pwrdm_state) extract_bitfield(pwrstst, 4, 2);
		st_tgt = (pwrdm_state) extract_bit(pwrstctrl, 8);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    RETAINED bank", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));
		break;
	case PWRDM54XX_ABE:
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"Memory", "", "");
		st_curr = (pwrdm_state) extract_bitfield(pwrstst, 4, 2);
		st_tgt = (pwrdm_state) extract_bit(pwrstctrl, 8);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    AESS", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));

		st_curr = (pwrdm_state) extract_bitfield(pwrstst, 8, 2);
		st_tgt = (pwrdm_state) extract_bit(pwrstctrl, 10);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    PERIPH", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));
		break;
	case PWRDM54XX_DSP:
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"Memory", "", "");
		st_curr = (pwrdm_state) extract_bitfield(pwrstst, 8, 2);
		st_tgt = (pwrdm_state) extract_bit(pwrstctrl, 10);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    EDMA", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));

		st_curr = (pwrdm_state) extract_bitfield(pwrstst, 6, 2);
		st_tgt = (pwrdm_state) extract_bit(pwrstctrl, 9);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    L2$", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));

		st_curr = (pwrdm_state) extract_bitfield(pwrstst, 4, 2);
		st_tgt = (pwrdm_state) extract_bit(pwrstctrl, 8);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    L1$", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));
		break;
	case PWRDM54XX_GPU:
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"Memory", "", "");
		st_curr = (pwrdm_state) extract_bitfield(pwrstst, 4, 2);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    MEM", pwrdm_state_name_get(st_curr), "");
		break;
	case PWRDM54XX_IVA:
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"Memory", "", "");
		st_curr = (pwrdm_state) extract_bitfield(pwrstst, 10, 2);
		st_tgt = (pwrdm_state) extract_bit(pwrstctrl, 11);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    TCM2", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));

		st_curr = (pwrdm_state) extract_bitfield(pwrstst, 8, 2);
		st_tgt = (pwrdm_state) extract_bit(pwrstctrl, 10);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    TCM1", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));

		st_curr = (pwrdm_state) extract_bitfield(pwrstst, 6, 2);
		st_tgt = (pwrdm_state) extract_bit(pwrstctrl, 9);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    SL2", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));

		st_curr = (pwrdm_state) extract_bitfield(pwrstst, 4, 2);
		st_tgt = (pwrdm_state) extract_bit(pwrstctrl, 8);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    HWA", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));
		break;
	case PWRDM54XX_MPU:
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"Memory", "", "");
		st_curr = (pwrdm_state) extract_bitfield(pwrstst, 6, 2);
		st_tgt = (pwrdm_state) extract_bit(pwrstctrl, 9);
		fprintf(stream, "| %-32s | %-7s | %-7s |         |\n",
			"    L2$", pwrdm_state_name_get(st_curr),
			pwrdm_state_name_get(st_tgt));
		break;

	default:
		/* Nothing to print */
		break;
	}

	return 0;
}
