/*
 *
 * @Component			OMAPCONF
 * @Filename			twl6040_lib.c
 * @Description			TWL6040 Audio Companion Chip Functions
 * @Author			Patrick Titiano (p-titiano@ti.com)
 *				Misael Lopez Cruz <misael.lopez@ti.com>
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


#include <twl6040_lib.h>
#include <lib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <twl6040.h>


/* #define TWL6040_LIB_DEBUG */
#ifdef TWL6040_LIB_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_display_version_config
 * @BRIEF		analyze TWL6040 version
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output file
 * @param[in,out]	regs: register values
 * @DESCRIPTION		analyze TWL6040 version
 *//*------------------------------------------------------------------------ */
int twl6040_display_version_config(FILE *stream, unsigned char *regs)
{
	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "| VERSION                                           "
		"           |\n");
	fprintf(stream, "|--------------------------------|------------------"
		"-----------|\n");

	/* ASIC Type */
	fprintf(stream, "| %-30s | 0x%-25X |\n", "ASIC Type",
		regs[TWL6040_REG_ASICID]);

	/* ASIC Full Mask */
	fprintf(stream, "| %-30s | Version %-19d |\n", "ASIC Full Mask",
		extract_bitfield(regs[TWL6040_REG_ASICREV], 4, 4) + 1);

	/* ASIC Metal Mask */
	fprintf(stream, "| %-30s | Version %-19d |\n", "ASIC Metal Mask",
		extract_bitfield(regs[TWL6040_REG_ASICREV], 0, 4));

	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_i2cmode2string
 * @BRIEF		convert I2CMODE bitfield into string
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in]		s: destination string (pre-allocated)
 * @param[in]		i2cmode: I2CMODE bitfield
 * @DESCRIPTION		convert I2CMODE bitfield into string
 *//*------------------------------------------------------------------------ */
static int twl6040_i2cmode2string(char s[20], unsigned char i2cmode)
{
	if (s == NULL)
		return OMAPCONF_ERR_ARG;

	switch (i2cmode) {
	case 0:
		strcpy(s, "Normal Mode");
		break;
	case 1:
		strcpy(s, "Fast Mode");
		break;
	case 2:
		strcpy(s, "Fast Mode Plus");
		break;
	case 3:
		strcpy(s, "High Speed Mode");
		break;
	default:
		strcpy(s, "ERROR!!!");
		return OMAPCONF_ERR_ARG;
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_display_control_config
 * @BRIEF		analyze TWL6040 version
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output file
 * @param[in,out]	regs: register values
 * @DESCRIPTION		analyze TWL6040 version
 *//*------------------------------------------------------------------------ */
int twl6040_display_control_config(FILE *stream, unsigned char *regs)
{
	char mode[20];

	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "| CONTROL                                           "
		"           |\n");
	fprintf(stream, "|--------------------------------|------------------"
		"-----------|\n");

	/* I2C Mode */
	twl6040_i2cmode2string(mode,
		extract_bitfield(regs[TWL6040_REG_ACCCTL], 4, 2));
	fprintf(stream, "| %-30s | %-27s |\n", "I2C Mode", mode);

	/* Dual Access Registers Control */
	if (extract_bit(regs[TWL6040_REG_ACCCTL], 1) == 1) {
		fprintf(stream, "| %-30s | %-27s |\n",
			"Dual-Access Registers Control",
			"PDM and I2C interfaces");
	} else {
		fprintf(stream, "| %-30s | %-27s |\n",
			"Dual-Access Registers Control",
			((extract_bit(regs[TWL6040_REG_ACCCTL], 0) == 1) ?
			"I2C interface only" : "PDM interface only"));
	}

	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_ncpfetsize2string
 * @BRIEF		convert NCP FET size bitfield into string
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in]		s: destination string (pre-allocated)
 * @param[in]		ncpfetsize: NCPFETSIZE bitfield
 * @DESCRIPTION		convert NCP FET size bitfield into string
 *//*------------------------------------------------------------------------ */
static int twl6040_ncpfetsize2string(char s[20], unsigned char ncpfetsize)
{
	if (s == NULL)
		return OMAPCONF_ERR_ARG;

	switch (ncpfetsize) {
	case 0:
		strcpy(s, "1/8 of total FET");
		break;
	case 1:
		strcpy(s, "1/4 of total FET");
		break;
	case 2:
		strcpy(s, "3/8 of total FET");
		break;
	case 3:
		strcpy(s, "1/2 of total FET");
		break;
	case 4:
		strcpy(s, "5/8 of total FET");
		break;
	case 5:
		strcpy(s, "3/4 of total FET");
		break;
	case 6:
		strcpy(s, "7/8 of total FET");
		break;
	case 7:
		strcpy(s, "Total FET");
		break;
	default:
		strcpy(s, "ERROR!!!");
		return OMAPCONF_ERR_ARG;
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_display_power_config
 * @BRIEF		analyze TWL6040 NCP, HSLDO and LSDO configuration
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output file
 * @param[in,out]	regs: register values
 * @DESCRIPTION		analyze TWL6040 NCP, HSLDO and LSDO configuration
 *//*------------------------------------------------------------------------ */
int twl6040_display_power_config(FILE *stream, unsigned char *regs)
{
	char ncp[20];

	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "| POWER                                             "
		"           |\n");
	fprintf(stream, "|--------------------------------|------------------"
		"-----------|\n");

	/* Negative Charge Pump */
	fprintf(stream, "| %-30s | %-27s |\n", "Negative Charge Pump",
		((extract_bit(regs[TWL6040_REG_NCPCTL], 0) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Mode",
		((extract_bit(regs[TWL6040_REG_NCPCTL], 1) == 1) ?
		"PFM" : "PWM"));
	if (extract_bit(regs[TWL6040_REG_NCPCTL], 2) == 1) {
		twl6040_ncpfetsize2string(ncp,
			extract_bitfield(regs[TWL6040_REG_NCPCTL], 3, 3));
		fprintf(stream, "| %-30s | %-27s |\n", "  FET Size", ncp);
	} else {
		fprintf(stream, "| %-30s | %-27s |\n", "  FET Size",
			"Automatic");
	}
	fprintf(stream, "| %-30s | %-27s |\n", "  Loop",
		((extract_bit(regs[TWL6040_REG_NCPCTL], 6) == 1) ?
		"Open" : "Closed"));

	/* Internal Oscillator */
	fprintf(stream, "| %-30s | %-27s |\n", "Internal Oscillator",
		((extract_bit(regs[TWL6040_REG_LDOCTL], 7) == 1) ?
		"Enabled (Muxed to NCP)" : "Disabled (PLL muxed to NCP)"));

	/* Reference System */
	fprintf(stream, "| %-30s | %-27s |\n", "Reference System",
		((extract_bit(regs[TWL6040_REG_LDOCTL], 6) == 1) ?
		"Enabled" : "Disabled"));

	/* High-Side LDO */
	fprintf(stream, "| %-30s | %-27s |\n", "High Side LDO",
		((extract_bit(regs[TWL6040_REG_LDOCTL], 2) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Mode",
		((extract_bit(regs[TWL6040_REG_LDOCTL], 3) == 1) ?
		"Sleep" : "Normal"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Output When Disabled",
		((extract_bit(regs[TWL6040_REG_LDOCTL], 5) == 1) ?
		"High-Z" : "Pulled-Down to GND"));

	/* Low-Side LDO */
	fprintf(stream, "| %-30s | %-27s |\n", "Low Side LDO",
		((extract_bit(regs[TWL6040_REG_LDOCTL], 0) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Mode",
		((extract_bit(regs[TWL6040_REG_LDOCTL], 1) == 1) ?
		"Sleep" : "Normal"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Output When Disabled",
		((extract_bit(regs[TWL6040_REG_LDOCTL], 4) == 1) ?
		"High-Z" : "Pulled-Down to GND"));

	/* Split Supply Registers and State Machine */
	fprintf(stream, "| %-30s | %-27s |\n", "Split Supply Reg/State Machine",
		((extract_bit(regs[TWL6040_REG_ACCCTL], 2) == 1) ?
		"Reset" : "Running"));

	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_lpplldiv2string
 * @BRIEF		convert LPPLLDIV bitfield into string
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in]		s: destination string (pre-allocated)
 * @param[in]		lpplldiv: LPPLLDIV bitfield
 * @DESCRIPTION		convert LPPLLDIV bitfield into string
 *//*------------------------------------------------------------------------ */
static int twl6040_lpplldiv2string(char s[10], unsigned char lpplldiv)
{
	if (s == NULL)
		return OMAPCONF_ERR_ARG;

	sprintf(s, "%d", lpplldiv + 512);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_mclk2string
 * @BRIEF		convert MCLK frequency into string
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in]		s: destination string (pre-allocated)
 * @param[in]		hppllmclk: HPPLLMCLK bitfield
 * @DESCRIPTION		convert MCLK frequency into string
 *//*------------------------------------------------------------------------ */
static int twl6040_mclk2string(char s[10], unsigned char hppllmclk)
{
	if (s == NULL)
		return OMAPCONF_ERR_ARG;

	switch (hppllmclk) {
	case 0:
		strcpy(s, "12.0MHz");
		break;
	case 1:
		strcpy(s, "19.2MHz");
		break;
	case 2:
		strcpy(s, "26.0MHz");
		break;
	case 3:
		strcpy(s, "38.4MHz");
		break;
	default:
		strcpy(s, "ERROR!!!");
		return OMAPCONF_ERR_ARG;
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_display_clocking_config
 * @BRIEF		analyze TWL6040 HPPLL and LPPLL configuration
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output file
 * @param[in,out]	regs: register values
 * @DESCRIPTION		analyze TWL6040 HPPLL and LPPLL configuration
 *//*------------------------------------------------------------------------ */
int twl6040_display_clocking_config(FILE *stream, unsigned char *regs)
{
	char data[10];

	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "| CLOCKING SYSTEM                                   "
		"           |\n");
	fprintf(stream, "|--------------------------------|------------------"
		"-----------|\n");

	/* 32k Internal Oscillator */
	fprintf(stream, "| %-30s | %-27s |\n", "Clock 32kHz Source",
		((extract_bit(regs[TWL6040_REG_ACCCTL], 6) == 1) ?
		"Internal" : "External"));

	/* SYSCLK Source */
	fprintf(stream, "| %-30s | %-27s |\n", "SYSCLK source",
		((extract_bit(regs[TWL6040_REG_LPPLLCTL], 4) == 1) ?
		"High-Performance PLL" : "Low-Power PLL"));

	/* Low-Power PLL */
	fprintf(stream, "| %-30s | %-27s |\n", "Low-Power PLL",
		((extract_bit(regs[TWL6040_REG_LPPLLCTL], 0) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "  State",
		((extract_bit(regs[TWL6040_REG_LPPLLCTL], 1) == 1) ?
		"Reset" : "Normal"));
	if (extract_bit(regs[TWL6040_REG_LPPLLCTL], 2) == 1) {
		twl6040_lpplldiv2string(data, regs[TWL6040_REG_LPPLLDIV]);
		fprintf(stream, "| %-30s | %-27s |\n", "  Divider", data);
	} else {
		fprintf(stream, "| %-30s | %-27s |\n", "  Divider",
			((extract_bit(regs[TWL6040_REG_LPPLLCTL], 3) == 1) ?
			"538 (prefixed)" : "586 (prefixed)"));
	}

	/* High-Performance PLL */
	fprintf(stream, "| %-30s | %-27s |\n", "High-Performance PLL",
		((extract_bit(regs[TWL6040_REG_HPPLLCTL], 0) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "  State",
		((extract_bit(regs[TWL6040_REG_HPPLLCTL], 1) == 1) ?
		"Reset" : "Normal"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Mode",
		((extract_bit(regs[TWL6040_REG_HPPLLCTL], 2) == 1) ?
		"Bypass" : "Active"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Clock Slicer",
		((extract_bit(regs[TWL6040_REG_HPPLLCTL], 3) == 1) ?
		"Enabled" : "Disabled"));
	twl6040_mclk2string(data, extract_bitfield(regs[TWL6040_REG_HPPLLCTL],
		5, 2));
	fprintf(stream, "| %-30s | %-27s |\n", "  MCLK frequency", data);

	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_display_interrupts_config
 * @BRIEF		analyze TWL6040 interrupts and status
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output file
 * @param[in,out]	regs: register values
 * @DESCRIPTION		analyze TWL6040 interrupts and status
 *//*------------------------------------------------------------------------ */
int twl6040_display_interrupts_config(FILE *stream, unsigned char *regs)
{
	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "| INTERRUPT AND STATUS                              "
		"           |\n");
	fprintf(stream, "|--------------------------------|------------------"
		"-----------|\n");

	/* Thermal Interrupt */
	fprintf(stream, "| %-30s | %-27s |\n", "Thermal Interrupt",
		((extract_bit(regs[TWL6040_REG_INTMR], 0) == 1) ?
		"Disabled" : "Enabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Pending",
		((extract_bit(regs[TWL6040_REG_INTID], 0) == 1) ?
		"Yes" : "No"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Status",
		((extract_bit(regs[TWL6040_REG_STATUS], 6) == 1) ?
		"High" : "Low"));

	/* Plug Detection Interrupt */
	fprintf(stream, "| %-30s | %-27s |\n", "Plug Detection Interrupt",
		((extract_bit(regs[TWL6040_REG_INTMR], 1) == 1) ?
		"Disabled" : "Enabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Plug Pending",
		((extract_bit(regs[TWL6040_REG_INTID], 1) == 1) ?
		"Yes" : "No"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Unplug Pending",
		((extract_bit(regs[TWL6040_REG_INTID], 2) == 1) ?
		"Yes" : "No"));
	fprintf(stream, "| %-30s | %-27s |\n", "  PLUGDET State",
		((extract_bit(regs[TWL6040_REG_STATUS], 1) == 1) ?
		"Pulled Low" : "Not Pulled Low"));

	/* Hook Send/End Detection Interrupt */
	fprintf(stream, "| %-30s | %-27s |\n", "Hook Send/End Detection Int",
		((extract_bit(regs[TWL6040_REG_INTMR], 3) == 1) ?
		"Disabled" : "Enabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Pending",
		((extract_bit(regs[TWL6040_REG_INTID], 3) == 1) ?
		"Yes" : "No"));
	fprintf(stream, "| %-30s | %-27s |\n", "  ACONN State",
		((extract_bit(regs[TWL6040_REG_STATUS], 0) == 1) ?
		"Pulled Low" : "Not Pulled Low"));

	/* HF Short Detection Interrupt */
	fprintf(stream, "| %-30s | %-27s |\n", "HF Short Detection Interrupt",
		((extract_bit(regs[TWL6040_REG_INTMR], 4) == 1) ?
		"Disabled" : "Enabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Pending",
		((extract_bit(regs[TWL6040_REG_INTID], 4) == 1) ?
		"Yes" : "No"));
	fprintf(stream, "| %-30s | %-27s |\n", "  HF Left Overcurrent Det",
		((extract_bit(regs[TWL6040_REG_STATUS], 2) == 1) ?
		"Triggered" : "Not Triggered"));
	fprintf(stream, "| %-30s | %-27s |\n", "  HF Right Overcurrent Det",
		((extract_bit(regs[TWL6040_REG_STATUS], 3) == 1) ?
		"Triggered" : "Not Triggered"));

	/* Vibra Short Detection Interrupt */
	fprintf(stream, "| %-30s | %-27s |\n", "Vibra Short Detection Int",
		((extract_bit(regs[TWL6040_REG_INTMR], 5) == 1) ?
		"Disabled" : "Enabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Pending",
		((extract_bit(regs[TWL6040_REG_INTID], 5) == 1) ?
		"Yes" : "No"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Vibra Left Overcurrent Det",
		((extract_bit(regs[TWL6040_REG_STATUS], 4) == 1) ?
		"Triggered" : "Not Triggered"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Vibra Right Overcurrent Det",
		((extract_bit(regs[TWL6040_REG_STATUS], 5) == 1) ?
		"Triggered" : "Not Triggered"));

	/* Ready Interrupt */
	fprintf(stream, "| %-30s | %-27s |\n", "Ready Interrupt",
		((extract_bit(regs[TWL6040_REG_INTMR], 6) == 1) ?
		"Disabled" : "Enabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Pending",
		((extract_bit(regs[TWL6040_REG_INTID], 6) == 1) ?
		"Yes" : "No"));

	/* Interrupt Clear Mode */
	fprintf(stream, "| %-30s | %-27s |\n", "Interrupt Clear Mode",
		((extract_bit(regs[TWL6040_REG_ACCCTL], 3) == 1) ?
		"On Read" : "On Write"));

	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_display_biasing_config
 * @BRIEF		analyze TWL6040 biasing module configuration
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output file
 * @param[in,out]	regs: register values
 * @DESCRIPTION		analyze TWL6040 biasing module configuration
 *//*------------------------------------------------------------------------ */
int twl6040_display_biasing_config(FILE *stream, unsigned char *regs)
{
	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "| BIASING                                           "
		"           |\n");
	fprintf(stream, "|--------------------------------|------------------"
		"-----------|\n");

	/* Headset Microphone Bias */
	fprintf(stream, "| %-30s | %-27s |\n", "Headset Microphone Bias",
		((extract_bit(regs[TWL6040_REG_AMICBCTL], 0) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Mode",
		((extract_bit(regs[TWL6040_REG_AMICBCTL], 1) == 1) ?
		"Sleep" : "Normal"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Output When Disabled",
		((extract_bit(regs[TWL6040_REG_AMICBCTL], 2) == 1) ?
		"Pull-Down" : "High-Z"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Short Circuit Function",
		((extract_bit(regs[TWL6040_REG_AMICBCTL], 3) == 1) ?
		"Disabled" : "Enabled"));

	/* Main Microphone Bias */
	fprintf(stream, "| %-30s | %-27s |\n", "Main Microphone Bias",
		((extract_bit(regs[TWL6040_REG_AMICBCTL], 4) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Mode",
		((extract_bit(regs[TWL6040_REG_AMICBCTL], 5) == 1) ?
		"Sleep" : "Normal"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Output When Disabled",
		((extract_bit(regs[TWL6040_REG_AMICBCTL], 6) == 1) ?
		"Pull-Down" : "High-Z"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Short Circuit Function",
		((extract_bit(regs[TWL6040_REG_AMICBCTL], 7) == 1) ?
		"Disabled" : "Enabled"));

	/* Digital Microphone Bias 1 */
	fprintf(stream, "| %-30s | %-27s |\n", "Digital Microphone Bias 1",
		((extract_bit(regs[TWL6040_REG_DMICBCTL], 0) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Mode",
		((extract_bit(regs[TWL6040_REG_DMICBCTL], 1) == 1) ?
		"Sleep" : "Normal"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Output Voltage",
		((extract_bit(regs[TWL6040_REG_DMICBCTL], 2) == 1) ?
		"1.85V" : "1.80V"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Short Circuit Function",
		((extract_bit(regs[TWL6040_REG_DMICBCTL], 3) == 1) ?
		"Disabled" : "Enabled"));

	/* Digital Microphone Bias 2 */
	fprintf(stream, "| %-30s | %-27s |\n", "Digital Microphone Bias 2",
		((extract_bit(regs[TWL6040_REG_DMICBCTL], 4) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Mode",
		((extract_bit(regs[TWL6040_REG_DMICBCTL], 5) == 1) ?
		"Sleep" : "Normal"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Output Voltage",
		((extract_bit(regs[TWL6040_REG_DMICBCTL], 6) == 1) ?
		"1.85V" : "1.80V"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Short Circuit Function",
		((extract_bit(regs[TWL6040_REG_DMICBCTL], 7) == 1) ?
		"Disabled" : "Enabled"));

	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_miclsel2string
 * @BRIEF		convert MICLSEL to corresponding string
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in]		s: destination string (pre-allocated)
 * @param[in]		miclsel: MICLSEL bitfield
 * @DESCRIPTION		convert MICLSEL to corresponding string
 *//*------------------------------------------------------------------------ */
static int twl6040_miclsel2string(char s[30], unsigned char miclsel)
{
	if (s == NULL)
		return OMAPCONF_ERR_ARG;

	switch (miclsel) {
	case 0:
		strcpy(s, "Headset Microphone");
		break;
	case 1:
		strcpy(s, "Main Microphone");
		break;
	case 2:
		strcpy(s, "Auxiliary/FM Left");
		break;
	case 3:
		strcpy(s, "None");
		break;
	default:
		strcpy(s, "ERROR!!!");
		return OMAPCONF_ERR_ARG;
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_micrsel2string
 * @BRIEF		convert MICRSEL to corresponding string
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in]		s: destination string (pre-allocated)
 * @param[in]		micrsel: MICRSEL bitfield
 * @DESCRIPTION		convert MICRSEL to corresponding string
 *//*------------------------------------------------------------------------ */
static int twl6040_micrsel2string(char s[30], unsigned char micrsel)
{
	if (s == NULL)
		return OMAPCONF_ERR_ARG;

	switch (micrsel) {
	case 0:
		strcpy(s, "Headset Microphone");
		break;
	case 1:
		strcpy(s, "Auxiliary Microphone");
		break;
	case 2:
		strcpy(s, "Auxiliary/FM Right");
		break;
	case 3:
		strcpy(s, "None");
		break;
	default:
		strcpy(s, "ERROR!!!");
		return OMAPCONF_ERR_ARG;
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_micgain2string
 * @BRIEF		convert MICGAINL/MICGAINR to corresponding dB value
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in]		s: destination string (pre-allocated)
 * @param[in]		micgain: MICGAINL/MICGAINR bitfield
 * @DESCRIPTION		convert MICGAINL/MICGAINR to corresponding dB value
 *//*------------------------------------------------------------------------ */
static int twl6040_micgain2string(char s[10], unsigned char micgain)
{
	int db;

	if (s == NULL)
		return OMAPCONF_ERR_ARG;

	if (micgain > 0x7) {
		strcpy(s, "ERROR!!!");
		return OMAPCONF_ERR_ARG;
	}

	if (micgain <= 0x4)
		db = 6 * micgain + 6;
	else
		db = 30;

	sprintf(s, "%ddB", db);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_linegain2string
 * @BRIEF		convert LINEGAINL/LINEGAINR to corresponding dB value
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in]		s: destination string (pre-allocated)
 * @param[in]	l	inegain: LINEGAINL/LINEGAINR bitfield
 * @DESCRIPTION		convert LINEGAINL/LINEGAINR to corresponding dB value
 *//*------------------------------------------------------------------------ */
static int twl6040_linegain2string(char s[10], unsigned char linegain)
{
	int db;

	if (s == NULL)
		return OMAPCONF_ERR_ARG;

	if (linegain > 0x7) {
		strcpy(s, "ERROR!!!");
		return OMAPCONF_ERR_ARG;
	}

	db = 6 * linegain - 18;
	sprintf(s, "%ddB", db);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_display_uplink_config
 * @BRIEF		analyze TWL6040 uplink path
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output file
 * @param[in,out]	regs: register values
 * @DESCRIPTION		analyze TWL6040 uplink path
 *//*------------------------------------------------------------------------ */
int twl6040_display_uplink_config(FILE *stream, unsigned char *regs)
{
	char micsel[30];
	char gain[10];

	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "| UPLINK                                            "
		"           |\n");
	fprintf(stream, "|--------------------------------|------------------"
		"-----------|\n");

	/* Input Source */
	fprintf(stream, "| %-30s | %-27s |\n", "Input Source", "");
	twl6040_miclsel2string(micsel,
		extract_bitfield(regs[TWL6040_REG_MICLCTL], 3, 2));
	fprintf(stream, "| %-30s | %-27s |\n", "  Left", micsel);
	twl6040_micrsel2string(micsel,
		extract_bitfield(regs[TWL6040_REG_MICRCTL], 3, 2));
	fprintf(stream, "| %-30s | %-27s |\n", "  Right", micsel);

	/* ADCs */
	fprintf(stream, "| %-30s | %-27s |\n", "ADC", "");
	fprintf(stream, "| %-30s | %-27s |\n", "  Left",
		((extract_bit(regs[TWL6040_REG_MICLCTL], 2) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Right",
		((extract_bit(regs[TWL6040_REG_MICRCTL], 2) == 1) ?
		"Enabled" : "Disabled"));

	/* Microphone */
	fprintf(stream, "| %-30s | %-27s |\n", "Microphone", "");
	fprintf(stream, "| %-30s | %-27s |\n", "  Left Amplifier",
		((extract_bit(regs[TWL6040_REG_MICLCTL], 0) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "    Pre-attenuation Gain",
		((extract_bit(regs[TWL6040_REG_MICGAIN], 6) == 1) ?
		"-6dB" : "0dB"));
	twl6040_micgain2string(gain,
		extract_bitfield(regs[TWL6040_REG_MICGAIN], 0, 3));
	fprintf(stream, "| %-30s | %-27s |\n", "    Preamplifier Gain", gain);

	fprintf(stream, "| %-30s | %-27s |\n", "  Right Amplifier",
		((extract_bit(regs[TWL6040_REG_MICRCTL], 0) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "    Pre-attenuation Gain",
		((extract_bit(regs[TWL6040_REG_MICGAIN], 7) == 1) ?
		"-6dB" : "0dB"));
	twl6040_micgain2string(gain,
		extract_bitfield(regs[TWL6040_REG_MICGAIN], 3, 3));
	fprintf(stream, "| %-30s | %-27s |\n", "    Preamplifier Gain", gain);

	/* Line-In */
	fprintf(stream, "| %-30s | %-27s |\n", "Line-In", "");
	fprintf(stream, "| %-30s | %-27s |\n", "  Left Amplifier",
		((extract_bit(regs[TWL6040_REG_MICLCTL], 1) == 1) ?
		"Enabled" : "Disabled"));
	twl6040_linegain2string(gain,
		extract_bitfield(regs[TWL6040_REG_LINEGAIN], 0, 3));
	fprintf(stream, "| %-30s | %-27s |\n", "    Gain", gain);
	fprintf(stream, "| %-30s | %-27s |\n", "  Right Amplifier",
		((extract_bit(regs[TWL6040_REG_MICRCTL], 1) == 1) ?
		"Enabled" : "Disabled"));
	twl6040_linegain2string(gain,
		extract_bitfield(regs[TWL6040_REG_LINEGAIN], 3, 3));
	fprintf(stream, "| %-30s | %-27s |\n", "    Gain", gain);

	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_hsgain2string
 * @BRIEF		convert headset driver gain to corresponding dB value
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in]		s: destination string (pre-allocated)
 * @param[in]		hsgain: HSLGAIN/HSRGAIN bitfield
 * @DESCRIPTION		convert headset driver gain to corresponding dB value
 *//*------------------------------------------------------------------------ */
static int twl6040_hsgain2string(char s[10], unsigned char hsgain)
{
	int db;

	if (s == NULL)
		return OMAPCONF_ERR_ARG;

	if (hsgain > 0xF) {
		strcpy(s, "ERROR!!!");
		return OMAPCONF_ERR_ARG;
	}

	db = -2 * hsgain;
	sprintf(s, "%ddB", db);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_eargain2string
 * @BRIEF		convert ear driver gain to corresponding dB value
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in]		s: destination string (pre-allocated)
 * @param[in]		eargain: EARGAIN bitfield
 * @DESCRIPTION		convert ear driver gain to corresponding dB value
 *//*------------------------------------------------------------------------ */
static int twl6040_eargain2string(char s[10], unsigned char eargain)
{
	int db;

	if (s == NULL)
		return OMAPCONF_ERR_ARG;

	if (eargain > 0xF) {
		strcpy(s, "ERROR!!!");
		return OMAPCONF_ERR_ARG;
	}

	db = -2 * eargain + 6;
	sprintf(s, "%ddB", db);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_display_downlink1_config
 * @BRIEF		analyze TWL6040 downlink-1 path
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output file
 * @param[in,out]	regs: register values
 * @DESCRIPTION		analyze TWL6040 downlink-1 path
 *//*------------------------------------------------------------------------ */
int twl6040_display_downlink1_config(FILE *stream, unsigned char *regs)
{
	char gain[10];

	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "| DOWNLINK 1                                        "
		"           |\n");
	fprintf(stream, "|--------------------------------|------------------"
		"-----------|\n");

	/* Headset DAC */
	fprintf(stream, "| %-30s | %-27s |\n", "Headset DAC", "");
	fprintf(stream, "| %-30s | %-27s |\n", "  Left HSDAC",
		((extract_bit(regs[TWL6040_REG_HSLCTL], 0) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "    Mode",
		((extract_bit(regs[TWL6040_REG_HSLCTL], 1) == 1) ?
		"Low-Power" : "High-Performance"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Right HSDAC",
		((extract_bit(regs[TWL6040_REG_HSRCTL], 0) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "    Mode",
		((extract_bit(regs[TWL6040_REG_HSRCTL], 1) == 1) ?
		"Low-Power" : "High-Performance"));

	/* Headset Driver */
	fprintf(stream, "| %-30s | %-27s |\n", "Headset Driver", "");
	fprintf(stream, "| %-30s | %-27s |\n", "  Left HSDRV",
		((extract_bit(regs[TWL6040_REG_HSLCTL], 2) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "    Mode",
		((extract_bit(regs[TWL6040_REG_HSLCTL], 3) == 1) ?
		"Low-Power" : "High-Performance"));
	fprintf(stream, "| %-30s | %-27s |\n", "    Pull-Down",
		((extract_bit(regs[TWL6040_REG_HSLCTL], 4) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "    HSDAC -> HSDRV Path",
		((extract_bit(regs[TWL6040_REG_HSLCTL], 5) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "    Line-In -> HSDRV Path",
		((extract_bit(regs[TWL6040_REG_HSLCTL], 6) == 1) ?
		"Enabled" : "Disabled"));
	twl6040_hsgain2string(gain, extract_bitfield(regs[TWL6040_REG_HSGAIN],
		0, 4));
	fprintf(stream, "| %-30s | %-27s |\n", "    Gain", gain);

	fprintf(stream, "| %-30s | %-27s |\n", "  Right HSDRV",
		((extract_bit(regs[TWL6040_REG_HSRCTL], 2) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "    Mode",
		((extract_bit(regs[TWL6040_REG_HSRCTL], 3) == 1) ?
		"Low-Power" : "High-Performance"));
	fprintf(stream, "| %-30s | %-27s |\n", "    Pull-Down",
		((extract_bit(regs[TWL6040_REG_HSRCTL], 4) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "    HSDAC -> HSDRV Path",
		((extract_bit(regs[TWL6040_REG_HSRCTL], 5) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "    Line-In -> HSDRV Path",
		((extract_bit(regs[TWL6040_REG_HSRCTL], 6) == 1) ?
		"Enabled" : "Disabled"));
	twl6040_hsgain2string(gain, extract_bitfield(regs[TWL6040_REG_HSGAIN],
		4, 4));
	fprintf(stream, "| %-30s | %-27s |\n", "    Gain", gain);

	/* Ear Driver */
	fprintf(stream, "| %-30s | %-27s |\n", "Ear Driver", "");
	fprintf(stream, "| %-30s | %-27s |\n", "  Mono EARDRV",
		((extract_bit(regs[TWL6040_REG_EARCTL], 0) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Filter",
		((extract_bit(regs[TWL6040_REG_EARCTL], 5) == 1) ?
		"FIR" : "SINC"));
	twl6040_eargain2string(gain, extract_bitfield(regs[TWL6040_REG_EARCTL],
		1, 4));
	fprintf(stream, "| %-30s | %-27s |\n", "    Gain", gain);

	/* Mono to Stereo Mixing */
	fprintf(stream, "| %-30s | %-27s |\n", "Mono to Stereo Mixing",
		((extract_bit(regs[TWL6040_REG_HSRCTL], 7) == 1) ?
		"Enabled" : "Disabled"));

	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_hfgain2string
 * @BRIEF		convert handsfree PGA gain to corresponding dB value
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in]		s: destination string (pre-allocated)
 * @param[in]		hfpgagain: HFPGAGAINL/HFPGAGAINR bitfield
 * @DESCRIPTION		convert handsfree PGA gain to corresponding dB value
 *//*------------------------------------------------------------------------ */
static int twl6040_hfgain2string(char s[10], unsigned char hfpgagain)
{
	int db;

	if (s == NULL)
		return OMAPCONF_ERR_ARG;

	if (hfpgagain > 0x1F) {
		strcpy(s, "ERROR!!!");
		return OMAPCONF_ERR_ARG;
	}

	if (hfpgagain <= 0x1D) {
		db = -2 * hfpgagain + 6;
		sprintf(s, "%ddB", db);
	} else {
		strcpy(s, "INVALID");
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_display_downlink2_config
 * @BRIEF		analyze TWL6040 downlink-2 path
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output file
 * @param[in,out]	regs: register values
 * @DESCRIPTION		analyze TWL6040 downlink-2 path
 *//*------------------------------------------------------------------------ */
int twl6040_display_downlink2_config(FILE *stream, unsigned char *regs)
{
	char gain[10];

	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "| DOWNLINK 2                                        "
		"           |\n");
	fprintf(stream, "|--------------------------------|------------------"
		"-----------|\n");

	/* Handsfree DAC */
	fprintf(stream, "| %-30s | %-27s |\n", "Handsfree DAC", "");
	fprintf(stream, "| %-30s | %-27s |\n", "  Left HFDAC",
		((extract_bit(regs[TWL6040_REG_HFLCTL], 0) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Right HFDAC",
		((extract_bit(regs[TWL6040_REG_HFRCTL], 0) == 1) ?
		"Enabled" : "Disabled"));

	/* Handsfree PGA */
	fprintf(stream, "| %-30s | %-27s |\n", "Handsfree Prog Gain Amplifier",
		"");
	fprintf(stream, "| %-30s | %-27s |\n", "  Left HFPGA",
		((extract_bit(regs[TWL6040_REG_HFLCTL], 1) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "    HFDAC -> HFPGA Path",
		((extract_bit(regs[TWL6040_REG_HFLCTL], 2) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "    Line-In -> HFPGA Path",
		((extract_bit(regs[TWL6040_REG_HFLCTL], 3) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "    HFPGA -> AUX Path",
		((extract_bit(regs[TWL6040_REG_HFLCTL], 6) == 1) ?
		"Enabled" : "Disabled"));
	twl6040_hfgain2string(gain,
		extract_bitfield(regs[TWL6040_REG_HFLGAIN], 0, 5));
	fprintf(stream, "| %-30s | %-27s |\n", "    Gain", gain);

	fprintf(stream, "| %-30s | %-27s |\n", "  Right HFPGA",
		((extract_bit(regs[TWL6040_REG_HFRCTL], 1) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "    HFDAC -> HFPGA Path",
		((extract_bit(regs[TWL6040_REG_HFRCTL], 2) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "    Line-In -> HFPGA Path",
		((extract_bit(regs[TWL6040_REG_HFRCTL], 3) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "    HFPGA -> AUX Path",
		((extract_bit(regs[TWL6040_REG_HFRCTL], 6) == 1) ?
		"Enabled" : "Disabled"));
	twl6040_hfgain2string(gain,
		extract_bitfield(regs[TWL6040_REG_HFRGAIN], 0, 5));
	fprintf(stream, "| %-30s | %-27s |\n", "    Gain", gain);

	/* Handsfree Driver */
	fprintf(stream, "| %-30s | %-27s |\n", "Handsfree Driver", "");
	fprintf(stream, "| %-30s | %-27s |\n", "  Left HFDRV",
		((extract_bit(regs[TWL6040_REG_HFLCTL], 4) == 1) ?
		"Enabled" : "Disabled"));
	fprintf(stream, "| %-30s | %-27s |\n", "  Right HFDRV",
		((extract_bit(regs[TWL6040_REG_HFRCTL], 4) == 1) ?
		"Enabled" : "Disabled"));

	/* Mono to Stereo Mixing */
	fprintf(stream, "| %-30s | %-27s |\n", "Mono to Stereo Mixing",
		((extract_bit(regs[TWL6040_REG_HFRCTL], 5) == 1) ?
		"Enabled" : "Disabled"));

	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_vibdata2string
 * @BRIEF		convert vibrator data to corresponding differential
 *			output voltage
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in]		s: destination string (pre-allocated)
 * @param[in]		vibdat: VIBDATL/VIBDATR bitfield
 * @DESCRIPTION		convert vibrator data to corresponding differential
 *			output voltage
 *//*------------------------------------------------------------------------ */
static int twl6040_vibdata2string(char s[10], signed char vibdat)
{
	float diff;

	if (s == NULL)
		return OMAPCONF_ERR_ARG;

	if (abs(vibdat) <= 100) {
		diff = 0.05 * vibdat;
		sprintf(s, "%.2fV", diff);
	} else {
		strcpy(s, "INVALID");
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_display_vibrator_config
 * @BRIEF		analyze TWL6040 vibrator path
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output file
 * @param[in,out]	regs: register values
 * @DESCRIPTION		analyze TWL6040 vibrator path
 *//*------------------------------------------------------------------------ */
int twl6040_display_vibrator_config(FILE *stream, unsigned char *regs)
{
	char data[10];

	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "| VIBRATOR                                          "
		"           |\n");
	fprintf(stream, "|--------------------------------|------------------"
		"-----------|\n");

	/* Left Vibrator */
	fprintf(stream, "| %-30s | %-27s |\n", "Left Vibrator", "");
	fprintf(stream, "| %-30s | %-27s |\n", "  Left Vibrator Driver",
		((extract_bit(regs[TWL6040_REG_VIBCTLL], 0) == 1) ?
		"Enabled" : "Disabled"));
	if (extract_bit(regs[TWL6040_REG_VIBCTLL], 2) == 1) {
		fprintf(stream, "| %-30s | %-27s |\n", "  Control",
			"VIBCTRLLP/VIBCTRLLN");
		fprintf(stream, "| %-30s | %-27s |\n", "    VIBLP Control",
			((extract_bit(regs[TWL6040_REG_VIBCTLL], 3) == 1) ?
			"High" : "Low"));
		fprintf(stream, "| %-30s | %-27s |\n", "    VIBLN Control",
			((extract_bit(regs[TWL6040_REG_VIBCTLL], 4) == 1) ?
			"High" : "Low"));
	} else {
		if (extract_bit(regs[TWL6040_REG_VIBCTLL], 1) == 1) {
			fprintf(stream, "| %-30s | %-27s |\n", "  Control",
				"1-bit PDM");
		} else {
			fprintf(stream, "| %-30s | %-27s |\n", "  Control",
				"8-bit VIBDATL");
			twl6040_vibdata2string(data,
				extract_bitfield(regs[TWL6040_REG_VIBDATL],
					0, 8));
			fprintf(stream, "| %-30s | %-27s |\n",
				"    Differential Output",
				data);
		}
	}
	fprintf(stream, "| %-30s | %-27s |\n", "  Feedback Loop",
		((extract_bit(regs[TWL6040_REG_VIBCTLL], 5) == 1) ?
		"Disabled" : "Enabled"));

	/* Right Vibrator */
	fprintf(stream, "| %-30s | %-27s |\n", "Right Vibrator", "");
	fprintf(stream, "| %-30s | %-27s |\n", "  Right Vibrator Driver",
		((extract_bit(regs[TWL6040_REG_VIBCTLR], 0) == 1) ?
		"Enabled" : "Disabled"));
	if (extract_bit(regs[TWL6040_REG_VIBCTLR], 2) == 1) {
		fprintf(stream, "| %-30s | %-27s |\n", "  Control",
			"VIBCTRLRP/VIBCTRLRN");
		fprintf(stream, "| %-30s | %-27s |\n", "    VIBRP Control",
			((extract_bit(regs[TWL6040_REG_VIBCTLR], 3) == 1) ?
			"High" : "Low"));
		fprintf(stream, "| %-30s | %-27s |\n", "    VIBRN Control",
			((extract_bit(regs[TWL6040_REG_VIBCTLR], 4) == 1) ?
			"High" : "Low"));
	} else {
		if (extract_bit(regs[TWL6040_REG_VIBCTLR], 1) == 1) {
			fprintf(stream, "| %-30s | %-27s |\n", "  Control",
				"1-bit PDM");
		} else {
			fprintf(stream, "| %-30s | %-27s |\n", "  Control",
				"8-bit VIBDATR");
			twl6040_vibdata2string(data,
				extract_bitfield(regs[TWL6040_REG_VIBDATR],
					0, 8));
			fprintf(stream, "| %-30s | %-27s |\n",
				"    Differential Output",
				data);
		}
	}
	fprintf(stream, "| %-30s | %-27s |\n", "  Feedback Loop",
		((extract_bit(regs[TWL6040_REG_VIBCTLR], 5) == 1) ?
		"Disabled" : "Enabled"));

	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_aloopl2string
 * @BRIEF		convert left analog loopback bitfield value into string
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in]		s: destination string (pre-allocated)
 * @param[in]		aloopl: ALOOPL bitfield
 * @DESCRIPTION		convert left analog loopback bitfield value into string
 *//*------------------------------------------------------------------------ */
static int twl6040_aloopl2string(char s[30], unsigned char aloopl)
{
	if (s == NULL)
		return OMAPCONF_ERR_ARG;

	switch (aloopl) {
	case 0:
		strcpy(s, "Disabled");
		break;
	case 1:
		strcpy(s, "ADC Left -> HSDAC Left");
		break;
	case 2:
		strcpy(s, "ADC Left -> HSDAC Right");
		break;
	case 3:
		strcpy(s, "ADC Left -> HFDAC Left");
		break;
	case 4:
		strcpy(s, "ADC Left -> HFDAC Right");
		break;
	case 5:
		strcpy(s, "ADC Left -> Vibra Left");
		break;
	case 6:
		strcpy(s, "ADC Left -> Vibra Right");
		break;
	default:
		strcpy(s, "INVALID");
		return OMAPCONF_ERR_ARG;
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_aloopr2string
 * @BRIEF		convert right analog loopback bitfield value into string
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in]		s: destination string (pre-allocated)
 * @param[in]		aloopr: ALOOPR bitfield
 * @DESCRIPTION		convert right analog loopback bitfield value into string
 *//*------------------------------------------------------------------------ */
static int twl6040_aloopr2string(char s[30], unsigned char aloopr)
{
	if (s == NULL)
		return OMAPCONF_ERR_ARG;

	switch (aloopr) {
	case 0:
		strcpy(s, "Disabled");
		break;
	case 1:
		strcpy(s, "ADC Right -> HSDAC Left");
		break;
	case 2:
		strcpy(s, "ADC Right -> HSDAC Right");
		break;
	case 3:
		strcpy(s, "ADC Right -> HFDAC Left");
		break;
	case 4:
		strcpy(s, "ADC Right -> HFDAC Right");
		break;
	case 5:
		strcpy(s, "ADC Right -> Vibra Left");
		break;
	case 6:
		strcpy(s, "ADC Right -> Vibra Right");
		break;
	default:
		strcpy(s, "INVALID");
		return OMAPCONF_ERR_ARG;
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_dloopl2string
 * @BRIEF		convert digital loopback 0 bitfield value into string
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in]		s: destination string (pre-allocated)
 * @param[in]		dloop0: DLOOP0 bitfield
 * @DESCRIPTION		convert digital loopback 0 bitfield value into string
 *//*------------------------------------------------------------------------ */
static int twl6040_dloopl2string(char s[15], unsigned char dloop0)
{
	if (s == NULL)
		return OMAPCONF_ERR_ARG;

	switch (dloop0) {
	case 0:
		strcpy(s, "Disabled");
		break;
	case 1:
		strcpy(s, "DN0 -> UL0");
		break;
	case 2:
		strcpy(s, "DN1 -> UL0");
		break;
	case 3:
		strcpy(s, "DN2 -> UL0");
		break;
	case 4:
		strcpy(s, "DN3 -> UL0");
		break;
	case 5:
		strcpy(s, "DN4 -> UL0");
		break;
	default:
		strcpy(s, "INVALID");
		return OMAPCONF_ERR_ARG;
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_dloopr2string
 * @BRIEF		convert digital loopback 1 bitfield value into string
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in]		s: destination string (pre-allocated)
 * @param[in]		dloop1: DLOOP1 bitfield
 * @DESCRIPTION		convert digital loopback 1 bitfield value into string
 *//*------------------------------------------------------------------------ */
static int twl6040_dloopr2string(char s[15], unsigned char dloop1)
{
	if (s == NULL)
		return OMAPCONF_ERR_ARG;

	switch (dloop1) {
	case 0:
		strcpy(s, "Disabled");
		break;
	case 1:
		strcpy(s, "DN0 -> UL1");
		break;
	case 2:
		strcpy(s, "DN1 -> UL1");
		break;
	case 3:
		strcpy(s, "DN2 -> UL1");
		break;
	case 4:
		strcpy(s, "DN3 -> UL1");
		break;
	case 5:
		strcpy(s, "DN4 -> UL1");
		break;
	default:
		strcpy(s, "INVALID");
		return OMAPCONF_ERR_ARG;
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_display_loopback_config
 * @BRIEF		analyze TWL6040 loopback configuration
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output file
 * @param[in,out]	regs: register values
 * @DESCRIPTION		analyze TWL6040 loopback configuration
 *//*------------------------------------------------------------------------ */
int twl6040_display_loopback_config(FILE *stream, unsigned char *regs)
{
	char al[30], dl[15];

	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "| LOOPBACK                                          "
		"           |\n");
	fprintf(stream, "|--------------------------------|------------------"
		"-----------|\n");

	/* Analog Loopback */
	fprintf(stream, "| %-30s | %-27s |\n", "Analog Loopback", "");
	twl6040_aloopl2string(al,
		extract_bitfield(regs[TWL6040_REG_ALB], 3, 3));
	fprintf(stream, "| %-30s | %-27s |\n", "  Left", al);
	twl6040_aloopr2string(al,
		extract_bitfield(regs[TWL6040_REG_ALB], 0, 3));
	fprintf(stream, "| %-30s | %-27s |\n", "  Right", al);

	/* Digital Loopback */
	fprintf(stream, "| %-30s | %-27s |\n", "Digital Loopback", "");
	twl6040_dloopl2string(dl,
		extract_bitfield(regs[TWL6040_REG_DLB], 0, 3));
	fprintf(stream, "| %-30s | %-27s |\n", "  Uplink 0", dl);
	twl6040_dloopr2string(dl,
		extract_bitfield(regs[TWL6040_REG_DLB], 3, 3));
	fprintf(stream, "| %-30s | %-27s |\n", "  Uplink 1", dl);

	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_display_gpo_config
 * @BRIEF		analyze TWL6040 GPO configuration
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output file
 * @param[in,out]	regs: register values
 * @DESCRIPTION		analyze TWL6040 GPO configuration
 *//*------------------------------------------------------------------------ */
int twl6040_display_gpo_config(FILE *stream, unsigned char *regs)
{
	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "| GENERAL PURPOSE OUTPUT                            "
		"           |\n");
	fprintf(stream, "|--------------------------------|------------------"
		"-----------|\n");

	fprintf(stream, "| %-30s | %-27s |\n", "GPO1",
		((extract_bit(regs[TWL6040_REG_GPOCTL], 0) == 1) ?
		"High" : "Low"));
	fprintf(stream, "| %-30s | %-27s |\n", "GPO2",
		((extract_bit(regs[TWL6040_REG_GPOCTL], 1) == 1) ?
		"High" : "Low"));
	fprintf(stream, "| %-30s | %-27s |\n", "GPO3",
		((extract_bit(regs[TWL6040_REG_GPOCTL], 2) == 1) ?
		"High" : "Low"));

	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_display_misc_config
 * @BRIEF		analyze TWL6040 miscellaneous configuration
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output file
 * @param[in,out]	regs: register values
 * @DESCRIPTION		analyze TWL6040 miscellaneous configuration
 *//*------------------------------------------------------------------------ */
int twl6040_display_misc_config(FILE *stream, unsigned char *regs)
{
	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "| MISCELLANEOUS                                     "
		"           |\n");
	fprintf(stream, "|--------------------------------|------------------"
		"-----------|\n");

	fprintf(stream, "| %-30s | %-27s |\n", "Headset Offset Trimming", "");
	fprintf(stream, "| %-30s | 0x%-25X |\n", " Left",
		extract_bitfield(regs[TWL6040_REG_HSOTRIM], 0, 4));
	fprintf(stream, "| %-30s | 0x%-25X |\n", " Right",
		extract_bitfield(regs[TWL6040_REG_HSOTRIM], 4, 4));

	fprintf(stream, "| %-30s | %-27s |\n", "Handsfree Offset Trimming", "");
	fprintf(stream, "| %-30s | 0x%-25X |\n", " Left",
		extract_bitfield(regs[TWL6040_REG_HFOTRIM], 0, 4));
	fprintf(stream, "| %-30s | 0x%-25X |\n", " Right",
		extract_bitfield(regs[TWL6040_REG_HFOTRIM], 4, 4));

	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_display_gains
 * @BRIEF		analyze TWL6040 analog gains
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output file
 * @param[in,out]	regs: register values
 * @DESCRIPTION		analyze TWL6040 analog gains
 *//*------------------------------------------------------------------------ */
int twl6040_display_gains(FILE *stream, unsigned char *regs)
{
	char gain[20];

	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "| GAINS                                             "
		"           |\n");
	fprintf(stream, "|--------------------------------|------------------"
		"-----------|\n");

	/* Microphone */
	fprintf(stream, "| %-30s | %-27s |\n", "Microphone", "");
	fprintf(stream, "| %-30s | %-27s |\n", "  Left Pre-attenuation Gain",
		((extract_bit(regs[TWL6040_REG_MICGAIN], 6) == 1) ?
		"-6dB" : "0dB"));
	twl6040_micgain2string(gain,
		extract_bitfield(regs[TWL6040_REG_MICGAIN], 0, 3));
	fprintf(stream, "| %-30s | %-27s |\n",
		"  Left Preamplifier Gain", gain);
	fprintf(stream, "| %-30s | %-27s |\n", "  Right Pre-attenuation Gain",
		((extract_bit(regs[TWL6040_REG_MICGAIN], 7) == 1) ?
		"-6dB" : "0dB"));
	twl6040_micgain2string(gain,
		extract_bitfield(regs[TWL6040_REG_MICGAIN], 3, 3));
	fprintf(stream, "| %-30s | %-27s |\n",
		"  Right Preamplifier Gain", gain);

	/* Line-In */
	fprintf(stream, "| %-30s | %-27s |\n", "Line-In", "");
	twl6040_linegain2string(gain,
		extract_bitfield(regs[TWL6040_REG_LINEGAIN], 0, 3));
	fprintf(stream, "| %-30s | %-27s |\n", "  Left Gain", gain);
	twl6040_linegain2string(gain,
		extract_bitfield(regs[TWL6040_REG_LINEGAIN], 3, 3));
	fprintf(stream, "| %-30s | %-27s |\n", "  Right Gain", gain);

	/* Headset DAC */
	fprintf(stream, "| %-30s | %-27s |\n", "Headset", "");
	twl6040_hsgain2string(gain,
		extract_bitfield(regs[TWL6040_REG_HSGAIN], 0, 4));
	fprintf(stream, "| %-30s | %-27s |\n",
		"  Left Headset Driver Gain", gain);
	twl6040_hsgain2string(gain,
		extract_bitfield(regs[TWL6040_REG_HSGAIN], 4, 4));
	fprintf(stream, "| %-30s | %-27s |\n",
		"  Right Headset Driver Gain", gain);

	/* Ear Driver */
	fprintf(stream, "| %-30s | %-27s |\n", "Ear", "");
	twl6040_eargain2string(gain,
		extract_bitfield(regs[TWL6040_REG_EARCTL], 1, 4));
	fprintf(stream, "| %-30s | %-27s |\n",
		"  Mono Ear Driver Gain", gain);

	/* Handsfree*/
	fprintf(stream, "| %-30s | %-27s |\n", "Handsfree", "");
	twl6040_hfgain2string(gain,
		extract_bitfield(regs[TWL6040_REG_HFLGAIN], 0, 5));
	fprintf(stream, "| %-30s | %-27s |\n",
		"  Left Handsfree PGA Gain", gain);
	twl6040_hfgain2string(gain,
		extract_bitfield(regs[TWL6040_REG_HFRGAIN], 0, 5));
	fprintf(stream, "| %-30s | %-27s |\n",
		"  Right Handsfree PGA Gain", gain);

	fprintf(stream, "|---------------------------------------------------"
		"-----------|\n");
	fprintf(stream, "\n");

	return 0;
}
