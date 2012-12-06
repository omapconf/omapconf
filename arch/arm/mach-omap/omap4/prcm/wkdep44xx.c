/*
 *
 * @Component			OMAPCONF
 * @Filename			wkdep44xx.c
 * @Description			OMAP4 WKDEP PRCM Definitions & Functions
 * @Author			Patrick Titiano (p-titiano@ti.com)
 * @Date			2010
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
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


#include <cm44xx.h>
#include <prm44xx.h>
#include <lib44xx.h>
#include <wkdep44xx.h>
#include <help.h>
#include <lib.h>
#include <mem.h>
#include <cpuinfo.h>
#include <string.h>


/* #define WKDEP44XX_DEBUG */
#ifdef WKDEP44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static reg_table omap4_prcm_wkdep_reg_table[57];
static unsigned int init_done = 0;

static int wkdep44xx_regtable_init(void);


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		wkdep44xx_name2addr
 * @BRIEF		retrieve physical address of a register, given its name.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		name: register name
 * @param[in,out]	addr: register address
 * @DESCRIPTION		retrieve physical address of a register, given its name.
 *//*------------------------------------------------------------------------ */
int wkdep44xx_name2addr(char *name, unsigned int *addr)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		wkdep44xx_regtable_init();

	return name2addr(name, addr, omap4_prcm_wkdep_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		wkdep44xx_dump
 * @BRIEF		dump PRCM WKDEP registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		dump PRCM WKDEP registers
 *//*------------------------------------------------------------------------ */
int wkdep44xx_dump(void)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		wkdep44xx_regtable_init();

	return dumpregs(omap4_prcm_wkdep_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		wkdep44xx_config_show
 * @BRIEF		analyze PRCM WKDEP configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		analyze PRCM WKDEP configuration
 *//*------------------------------------------------------------------------ */
int wkdep44xx_config_show(void)
{
	char mpu_irq_wkdep[3];
	char m3_irq_wkdep[3];
	char dsp_irq_wkdep[3];
	char sdma_irq_wkdep[3];
	char dsp_dma_wkdep[3];
	char sdma_dma_wkdep[3];
	char mpu_wake_wkdep[3];
	char dss_wkdep[4][3];
	char name[20];
	unsigned short i, j;
	unsigned int pm_wkdep;

	if (!cpu_is_omap44xx())
		return OMAPCONF_ERR_CPU;

	if (!init_done)
		wkdep44xx_regtable_init();

	printf("|-------------------------------------------------------"
		"-----------------|\n");
	printf("| PRM WKDEP Configuration                               "
		"                 |\n");
	printf("|-------------------------------------------------------"
		"-----------------|\n");
	printf("|                  |                            (Signal)"
		"                 |\n");
	printf("|                  |                            TOWARDS "
		"                 |\n");
	printf("|-------------------------------------------------------"
		"-----------------|\n");
	printf("|                  |         (SWakeup_IRQ)         |    "
		"(SWakeup_DMA)    |\n");
	printf("| FROM             | A9 | M3 | DSP | sDMA+L3_[1-2] | DSP"
		" | sDMA+L3_[1-2] |\n");
	printf("|-------------------------------------------------------"
		"-----------------|\n");
	for (i = 0; omap4_prcm_wkdep_reg_table[i].addr != 0; i++) {
		if ((strcmp(omap4_prcm_wkdep_reg_table[i].name,
				"PM_DSS_DSS_WKDEP") != 0) &&
			(strcmp(omap4_prcm_wkdep_reg_table[i].name,
				"PM_L3INIT_HSI_WKDEP") != 0) &&
			(strcmp(omap4_prcm_wkdep_reg_table[i].name,
				"PM_WKUP_GPIO1_WKDEP") != 0) &&
			(strcmp(omap4_prcm_wkdep_reg_table[i].name,
				"PM_L4PER_GPIO2_WKDEP") != 0) &&
			(strcmp(omap4_prcm_wkdep_reg_table[i].name,
				"PM_L4PER_GPIO3_WKDEP") != 0) &&
			(strcmp(omap4_prcm_wkdep_reg_table[i].name,
				"PM_L4PER_GPIO4_WKDEP") != 0) &&
			(strcmp(omap4_prcm_wkdep_reg_table[i].name,
				"PM_L4PER_GPIO5_WKDEP") != 0) &&
			(strcmp(omap4_prcm_wkdep_reg_table[i].name,
				"PM_L4PER_GPIO6_WKDEP") != 0)) {
			/* Read Register */
			if (mem_read(omap4_prcm_wkdep_reg_table[i].addr,
					&pm_wkdep) != 0)
				return OMAPCONF_ERR_REG_ACCESS;
			/* Extract WKDEP name from WKDEP register name */
			strncpy(name,
				omap4_prcm_wkdep_reg_table[i].name +
					3 * sizeof(char),
				strlen(omap4_prcm_wkdep_reg_table[i].name)
					- 9 * sizeof(char));
			name[strlen(omap4_prcm_wkdep_reg_table[i].name)
					- 9 * sizeof(char)] = '\0';
			dprintf("wkdep44xx_config_show(): "
				"pm_wkdep=%08x, name=%s\n", pm_wkdep, name);
			/* Extract WKDEP control bits from register */
			OMAPCONF_COND_STRCPY(extract_bit(pm_wkdep, 0),
				mpu_irq_wkdep, "EN", "");
			OMAPCONF_COND_STRCPY(extract_bit(pm_wkdep, 1),
				m3_irq_wkdep, "EN", "");
			OMAPCONF_COND_STRCPY(extract_bit(pm_wkdep, 2),
				dsp_irq_wkdep, "EN", "");
			OMAPCONF_COND_STRCPY(extract_bit(pm_wkdep, 3),
				sdma_irq_wkdep, "EN", "");
			OMAPCONF_COND_STRCPY(extract_bit(pm_wkdep, 6),
				dsp_dma_wkdep, "EN", "");
			OMAPCONF_COND_STRCPY(extract_bit(pm_wkdep, 7),
				sdma_dma_wkdep, "EN", "");
			printf("| %-16s | %-2s | %-2s | %-2s  |"
					" %-13s | %-2s  | %-13s |\n", name,
				mpu_irq_wkdep, m3_irq_wkdep, dsp_irq_wkdep,
				sdma_irq_wkdep, dsp_dma_wkdep, sdma_dma_wkdep);
		}
	}
	printf("|-------------------------------------------------------"
		"-----------------|\n\n");

	printf("|---------------------------------------------------------|\n");
	printf("| PRM GPIO[1-6] WKDEP Configuration                       |\n");
	printf("|---------------------------------------------------------|\n");
	printf("|                  |                (Signal)              |\n");
	printf("|                  |                TOWARDS               |\n");
	printf("|---------------------------------------------------------|\n");
	printf("|                  | (POINTRSWAKEUP1)  | (POINTRSWAKEUP2) |\n");
	printf("| FROM             |    A9   |   M3    |       DSP        |\n");
	printf("|---------------------------------------------------------|\n");
	for (i = 0; omap4_prcm_wkdep_reg_table[i].addr != 0; i++) {
		if ((strcmp(omap4_prcm_wkdep_reg_table[i].name,
				"PM_WKUP_GPIO1_WKDEP") == 0) ||
			(strcmp(omap4_prcm_wkdep_reg_table[i].name,
				"PM_L4PER_GPIO2_WKDEP") == 0) ||
			(strcmp(omap4_prcm_wkdep_reg_table[i].name,
				"PM_L4PER_GPIO3_WKDEP") == 0) ||
			(strcmp(omap4_prcm_wkdep_reg_table[i].name,
				"PM_L4PER_GPIO4_WKDEP") == 0) ||
			(strcmp(omap4_prcm_wkdep_reg_table[i].name,
				"PM_L4PER_GPIO5_WKDEP") == 0) ||
			(strcmp(omap4_prcm_wkdep_reg_table[i].name,
				"PM_L4PER_GPIO6_WKDEP") == 0)) {
			/* Read Register */
			if (mem_read(omap4_prcm_wkdep_reg_table[i].addr,
					&pm_wkdep) != 0)
				return OMAPCONF_ERR_REG_ACCESS;
			/* Extract WKDEP name from WKDEP register name */
			strncpy(name,
				omap4_prcm_wkdep_reg_table[i].name +
					3 * sizeof(char),
				strlen(omap4_prcm_wkdep_reg_table[i].name)
					- 9 * sizeof(char));
			name[strlen(omap4_prcm_wkdep_reg_table[i].name)
					- 9 * sizeof(char)] = '\0';
			dprintf("wkdep44xx_config_show(): "
				"pm_wkdep=%08x, name=%s\n",	pm_wkdep, name);
			/* Extract WKDEP control bits from register */
			OMAPCONF_COND_STRCPY(extract_bit(pm_wkdep, 0),
			mpu_irq_wkdep, "EN", "");
			OMAPCONF_COND_STRCPY(extract_bit(pm_wkdep, 1),
				m3_irq_wkdep, "EN", "");
			OMAPCONF_COND_STRCPY(extract_bit(pm_wkdep, 6),
				dsp_dma_wkdep, "EN", "");
			printf("| %-16s | %-7s | %-7s | %-16s |\n", name,
				mpu_irq_wkdep, m3_irq_wkdep, dsp_dma_wkdep);
		}
	}
	printf("|-----------------------------------------------------"
		"----|\n\n");

	/* Read Register */
	if (mem_read(OMAP4430_PM_L3INIT_HSI_WKDEP, &pm_wkdep) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	dprintf("wkdep44xx_config_show(): pm_wkdep=%08x, name=%s\n",
		pm_wkdep, "PM_L3INIT_HSI_WKDEP");
	/* Extract WKDEP control bits from register */
	OMAPCONF_COND_STRCPY(extract_bit(pm_wkdep, 0),
	mpu_irq_wkdep, "EN", "");
	OMAPCONF_COND_STRCPY(extract_bit(pm_wkdep, 1),
		m3_irq_wkdep, "EN", "");
	OMAPCONF_COND_STRCPY(extract_bit(pm_wkdep, 6),
		dsp_dma_wkdep, "EN", "");
	OMAPCONF_COND_STRCPY(extract_bit(pm_wkdep, 8),
		mpu_wake_wkdep, "EN", "");
	printf("|------------------------------------------------"
		"--------------|\n");
	printf("| PRM HSI WKDEP Configuration                    "
		"              |\n");
	printf("|------------------------------------------------"
		"--------------|\n");
	printf("|                     |                 FROM     "
		"              |\n");
	printf("|                     |                (Signal)  "
		"              |\n");
	printf("|------------------------------------------------"
		"--------------|\n");
	printf("| TOWARDS             | Modem      |            HSI"
		"            |\n");
	printf("|                     | (HSI_WAKE) | SWakeup_MPU | "
		"SWakeup_DSP |\n");
	printf("|------------------------------------------------"
		"--------------|\n");
	printf("| %-19s | %-10s | %-11s | %-11s |\n",
		"A9+L3_1+L4_CFG", mpu_wake_wkdep, mpu_irq_wkdep, "");
	printf("| %-19s | %-10s | %-11s | %-11s |\n",
		"M3+L3_2+L3_1+L4_CFG", "", m3_irq_wkdep, "");
	printf("| %-19s | %-10s | %-11s | %-11s |\n",
		"DSP+L3_1+L4_CFG", "", "", dsp_dma_wkdep);
	printf("|------------------------------------------------"
		"--------------|\n\n");

	/* Read Register */
	if (mem_read(OMAP4430_PM_DSS_DSS_WKDEP, &pm_wkdep) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	dprintf("wkdep44xx_config_show(): pm_wkdep=%08x, "
		"name=%s\n", pm_wkdep, "PM_DSS_DSS_WKDEP");
	printf("|--------------------------------------------|\n");
	printf("| PRM DSS WKDEP Configuration                |\n");
	printf("|--------------------------------------------|\n");
	printf("|               |            FROM            |\n");
	printf("|--------------------------------------------|\n");
	printf("| TOWARDS       | DISPC | DSI1 | DSI2 | HDMI |\n");
	printf("|--------------------------------------------|\n");
	/* Extract WKDEP control bits from register */
	for (j = 0; j < 4; j++) {
		for (i = 0; i < 4; i++) {
			if (((4 * i) + j) == 15) {
				OMAPCONF_COND_STRCPY(extract_bit(pm_wkdep,
					19) == 1, dss_wkdep[i], "EN", "");
			} else
				OMAPCONF_COND_STRCPY(extract_bit(pm_wkdep,
					(4 * i) + j) == 1,
					dss_wkdep[i], "EN", "");
		}
		printf("| %-13s | %-5s | %-4s | %-4s | %-4s |\n",
			omap44xx_dss_wkdep_signals[j], dss_wkdep[0],
			dss_wkdep[1], dss_wkdep[2], dss_wkdep[3]);
	}
	printf("|--------------------------------------------|\n\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		wkdep44xx_main
 * @BRIEF		main entry point
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		main entry point
 *//*------------------------------------------------------------------------ */
int wkdep44xx_main(int argc, char *argv[])
{
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (argc == 2) {
		if (strcmp(argv[1], "dump") == 0)
			ret = wkdep44xx_dump();
		else if (strcmp(argv[1], "cfg") == 0)
			ret = wkdep44xx_config_show();
		else {
			help(HELP_WKDEP);
			ret = OMAPCONF_ERR_ARG;
		}
	} else {
		help(HELP_WKDEP);
		ret = OMAPCONF_ERR_ARG;
	}

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		wkdep44xx_regtable_init
 * @BRIEF		initialize reg_table fields
 * @RETURNS		0
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		initialize reg_table fields
 *//*------------------------------------------------------------------------ */
static int wkdep44xx_regtable_init(void)
{
	int i = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	/* Init PRCM WKDEP registers table */
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_ABE_PDM_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_ABE_PDM_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_ABE_DMIC_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_ABE_DMIC_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_ABE_MCASP_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_ABE_MCASP_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_ABE_MCBSP1_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_ABE_MCBSP1_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_ABE_MCBSP2_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_ABE_MCBSP2_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_ABE_MCBSP3_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_ABE_MCBSP3_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_ABE_SLIMBUS_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_ABE_SLIMBUS_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_ABE_GPTIMER5_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_ABE_TIMER5_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_ABE_GPTIMER6_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_ABE_TIMER6_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_ABE_GPTIMER7_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_ABE_TIMER7_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_ABE_GPTIMER8_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_ABE_TIMER8_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_ABE_WDTIMER3_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_ABE_WDT3_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_ALWON_SR_MPU_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_ALWON_SR_MPU_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_ALWON_SR_IVA_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_ALWON_SR_IVA_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_ALWON_SR_CORE_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_ALWON_SR_CORE_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_DSS_DSS_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_DSS_DSS_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L3INIT_MMC1_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L3INIT_MMC1_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L3INIT_MMC2_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L3INIT_MMC2_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L3INIT_HSI_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L3INIT_HSI_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L3INIT_UNIPRO1_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L3INIT_UNIPRO1_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L3INIT_HSUSBHOST_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr =
		OMAP4430_PM_L3INIT_USB_HOST_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L3INIT_HSUSBOTG_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L3INIT_USB_OTG_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L3INIT_HSUSBTLL_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr =
		OMAP4430_PM_L3INIT_USB_TLL_WKDEP;
	if (!cpu_is_omap4470()) {
		strcpy(omap4_prcm_wkdep_reg_table[i].name,
			"PM_L3INIT_FSUSB_WKDEP");
		omap4_prcm_wkdep_reg_table[i++].addr =
			OMAP4430_PM_L3INIT_USB_HOST_FS_WKDEP;
	}
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L4PER_GPTIMER10_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr =
		OMAP4430_PM_L4PER_DMTIMER10_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L4PER_GPTIMER11_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr =
		OMAP4430_PM_L4PER_DMTIMER11_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L4PER_GPTIMER2_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L4PER_DMTIMER2_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L4PER_GPTIMER3_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L4PER_DMTIMER3_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L4PER_GPTIMER4_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L4PER_DMTIMER4_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L4PER_GPTIMER9_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L4PER_DMTIMER9_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L4PER_GPIO2_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L4PER_GPIO2_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L4PER_GPIO3_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L4PER_GPIO3_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L4PER_GPIO4_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L4PER_GPIO4_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L4PER_GPIO5_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L4PER_GPIO5_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L4PER_GPIO6_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L4PER_GPIO6_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L4PER_I2C1_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L4PER_I2C1_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L4PER_I2C2_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L4PER_I2C2_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L4PER_I2C3_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L4PER_I2C3_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L4PER_I2C4_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L4PER_I2C4_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L4PER_MCBSP4_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L4PER_MCBSP4_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L4PER_MCSPI1_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L4PER_MCSPI1_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L4PER_MCSPI2_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L4PER_MCSPI2_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L4PER_MCSPI3_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L4PER_MCSPI3_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L4PER_MCSPI4_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L4PER_MCSPI4_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L4PER_MMCSD3_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L4PER_MMCSD3_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L4PER_MMCSD4_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L4PER_MMCSD4_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L4PER_SLIMBUS2_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L4PER_SLIMBUS2_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L4PER_UART1_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L4PER_UART1_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L4PER_UART2_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L4PER_UART2_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L4PER_UART3_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L4PER_UART3_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L4PER_UART4_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L4PER_UART4_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_L4PER_MMCSD5_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_L4PER_MMCSD5_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_WKUP_WDTIMER2_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_WKUP_WDT2_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_WKUP_GPIO1_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_WKUP_GPIO1_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_WKUP_GPTIMER1_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_WKUP_TIMER1_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "PM_WKUP_KEYBOARD_WKDEP");
	omap4_prcm_wkdep_reg_table[i++].addr = OMAP4430_PM_WKUP_KEYBOARD_WKDEP;
	strcpy(omap4_prcm_wkdep_reg_table[i].name, "END");
	omap4_prcm_wkdep_reg_table[i].addr = 0;
	dprintf("omap4_prcm_wkdep_reg_table last index=%d, size=%d\n",
		i, i + 1);

	init_done = 1;
	return 0;
}
