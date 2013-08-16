/*
 *
 * @Component			OMAPCONF
 * @Filename			tlv320aic3x.c
 * @Description			tlv320aic3x analog codec functions
 * @Author			Misael Lopez Cruz (misael.lopez@ti.com)
 * @Date			2013
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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


#include <tlv320aic3x.h>
#include <i2c-tools.h>
#include <stdio.h>
#include <lib.h>
#include <autoadjust_table.h>
#include <help.h>
#include <cpuinfo.h>


/* #define TLV320AIC3X_DEBUG */
#ifdef TLV320AIC3X_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

/* Only registers in Page 0 */
#define TLV320AIC3X_REG_TABLE_SIZE	110

/*
 * Register names might differ in some devices of aic3x family,
 * below are taken from tlv320aic3106. Few names trimmed.
*/
static const reg_table tlv320aic3x_reg_table[TLV320AIC3X_REG_TABLE_SIZE] = {
	{"Page Select", 0},
	{"Software Reset", 1},
	{"Codec Sample Rate Select", 2},
	{"PLL Programming A", 3},
	{"PLL Programming B", 4},
	{"PLL Programming C", 5},
	{"PLL Programming D", 6},
	{"Codec Datapath Setup", 7},
	{"Audio Serial Data Interface Control A", 8},
	{"Audio Serial Data Interface Control B", 9},
	{"Audio Serial Data Interface Control B", 10},
	{"Audio Codec Overflow Flag", 11},
	{"Audio Codec Digital Filter Control", 12},
	{"Headset / Button Press Detection A", 13},
	{"Headset / Button Press Detection B", 14},
	{"Left ADC PGA Gain Control", 15},
	{"Right ADC PGA Gain Control", 16},
	{"MIC3L/R to Left ADC Control", 17},
	{"MIC3L/R to Right ADC Control", 18},
	{"LINE1L to Left ADC Control", 19},
	{"LINE2L to Left ADC Control", 20},
	{"LINE1R to Left ADC Control", 21},
	{"LINE1R to Right ADC Control", 22},
	{"LINE2R to Right ADC Control", 23},
	{"LINE1L to Right ADC Control", 24},
	{"MICBIAS Control", 25},
	{"Left AGC Control A", 26},
	{"Left AGC Control B", 27},
	{"Left AGC Control C", 28},
	{"Right AGC Control A", 29},
	{"Right AGC Control B", 30},
	{"Right AGC Control C", 31},
	{"Left AGC Gain", 32},
	{"Right AGC Gain", 33},
	{"Left AGC Noise Gate Debounce", 34},
	{"Right AGC Noise Gate Debounce", 35},
	{"ADC Flag", 36},
	{"DAC Power and Output Driver Control", 37},
	{"High-Power Output Driver Control", 38},
	/* Register 39 is reserved */
	{"High Power Output Stage Control", 40},
	{"DAC Output Switching Control", 41},
	{"Output Driver Pop Reduction", 42},
	{"Left DAC Digital Volume Control", 43},
	{"Right DAC Digital Volume Control", 44},
	{"LINE2L to HPLOUT Volume Control", 45},
	{"PGA_L to HPLOUT Volume Control", 46},
	{"DAC_L1 to HPLOUT Volume Control", 47},
	{"LINE2R to HPLOUT Volume Control", 48},
	{"PGA_R to HPLOUT Volume Control", 49},
	{"DAC_R1 to HPLOUT Volume Control", 50},
	{"HPLOUT Output Level Control", 51},
	{"LINE2L to HPLCOM Volume Control", 52},
	{"PGA_L to HPLCOM Volume Control", 53},
	{"DAC_L1 to HPLCOM Volume Control", 54},
	{"LINE2R to HPLCOM Volume Control", 55},
	{"PGA_R to HPLCOM Volume Control", 56},
	{"DAC_R1 to HPLCOM Volume Control", 57},
	{"HPLCOM Output Level Control", 58},
	{"LINE2L to HPROUT Volume Control", 59},
	{"PGA_L to HPROUT Volume Control", 60},
	{"DAC_L1 to HPROUT Volume Control", 61},
	{"LINE2R to HPROUT Volume Control", 62},
	{"PGA_R to HPROUT Volume Control", 63},
	{"DAC_R1 to HPROUT Volume Control", 64},
	{"HPROUT Output Level Control", 65},
	{"LINE2L to HPRCOM Volume Control", 66},
	{"PGA_L to HPRCOM Volume Control", 67},
	{"DAC_L1 to HPRCOM Volume Control", 68},
	{"LINE2R to HPRCOM Volume Control", 69},
	{"PGA_R to HPRCOM Volume Control", 70},
	{"DAC_R1 to HPRCOM Volume Control", 71},
	{"HPRCOM Output Level Control", 72},
	{"LINE2L to MONO_LOP/M Volume Control", 73},
	{"PGA_L to MONO_LOP/M Volume Control", 74},
	{"DAC_L1 to MONO_LOP/M Volume Control", 75},
	{"LINE2R to MONO_LOP/M Volume Control", 76},
	{"PGA_R to MONO_LOP/M Volume Control", 77},
	{"DAC_R1 to MONO_LOP/M Volume Control", 78},
	{"MONO_LOP/M Output Level Control", 79},
	{"LINE2L to LEFT_LOP/M Volume Control", 80},
	{"PGA_L to LEFT_LOP/M Volume Control", 81},
	{"DAC_L1 to LEFT_LOP/M Volume Control", 82},
	{"LINE2R to LEFT_LOP/M Volume Control", 83},
	{"PGA_R to LEFT_LOP/M Volume Control", 84},
	{"DAC_R1 to LEFT_LOP/M Volume Control", 85},
	{"LEFT_LOP/M Output Level Control", 86},
	{"LINE2L to RIGHT_LOP/M Volume Control", 87},
	{"PGA_L to RIGHT_LOP/M Volume Control", 88},
	{"DAC_L1 to RIGHT_LOP/M Volume Control", 89},
	{"LINE2R to RIGHT_LOP/M Volume Control", 90},
	{"PGA_R to RIGHT_LOP/M Volume Control", 91},
	{"DAC_R1 to RIGHT_LOP/M Volume Control", 92},
	{"RIGHT_LOP/M Output Level Control", 93},
	{"Module Power Status", 94},
	{"Output Driver Short Circuit Detection", 95},
	{"Sticky Interrupt Flags", 96},
	{"Real-Time Interrupt Flags", 97},
	{"GPIO1 Control", 98},
	{"GPIO2 Control", 99},
	{"Additional GPIO Control A", 100},
	{"Additional GPIO Control B", 101},
	{"Clock Generation Control", 102},
	{"Left AGC New Programmable Attack Time", 103},
	{"Left AGC New Programmable Decay Time", 104},
	{"Right AGC New Programmable Attack Time", 105},
	{"Right AGC New Programmable Decay Time", 106},
	{"New Programmable ADC Digital Path", 107},
	{"Passive Analog Signal Bypass Selection", 108},
	{"DAC Quiescent Current Adjustment", 109},
	{"END", 0} };


static void tlv320aic3x_dumpregs_usage(void)
{
	printf("Usage: omapconf audioic 'i2cbus' 0x'chip-address'\n");
	printf("  'i2cbus' is decimal value.\n");
	printf("  'chip-address' is hexadecimal values.\n");
	printf("  Warning: prefix '0x' is mandatory.\n");
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tlv320aic3x_dumpregs
 * @BRIEF		dump registers from table given as argument
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		none
 * @DESCRIPTION		dump registers from table given as argument
 *//*------------------------------------------------------------------------ */
int tlv320aic3x_dumpregs(int argc, char *argv[])
{
	unsigned int i = 0;
	unsigned int val = 0;
	int ret, err = 0;
	char autoadjust_table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row;
	unsigned int i2cbus, chip_address;

	if (argc == 1) {
		/* Take defaults: bus 0, address 0x18 */
		i2cbus = 0;
		chip_address = TLV320AIC3X_I2C_VALID_ADDR1;
	} else if (argc == 3) {
		if (argv == NULL) {
			printf("%s(): argv == NULL!!!\n", __func__);
			return OMAPCONF_ERR_ARG;
		}

		ret = sscanf(argv[1], "%u", &i2cbus);
		if (ret != 1) {
			tlv320aic3x_dumpregs_usage();
			return OMAPCONF_ERR_ARG;
		}

		ret = sscanf(argv[2], "0x%x", &chip_address);
		if (ret != 1) {
			tlv320aic3x_dumpregs_usage();
			return OMAPCONF_ERR_ARG;
		}
	}

	switch (chip_address) {
	case TLV320AIC3X_I2C_VALID_ADDR1:
	case TLV320AIC3X_I2C_VALID_ADDR2:
	case TLV320AIC3X_I2C_VALID_ADDR3:
	case TLV320AIC3X_I2C_VALID_ADDR4:
		break;
	default:
		printf("Invalid chip address, valid addresses are: 0x%02x - 0x%02x\n",
		       TLV320AIC3X_I2C_VALID_ADDR1, TLV320AIC3X_I2C_VALID_ADDR4);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	/* Read register 0 (Page select) to see if other i2c reads can succeed */
	ret = i2cget(i2cbus, chip_address, tlv320aic3x_reg_table[i].addr, &val);
	if (ret) {
		printf("I2C chip is not accessible\n");
		return OMAPCONF_ERR_REG_ACCESS;
	}

	autoadjust_table_init(autoadjust_table);
	row = 0;

	printf("I2C bus: %u\n", i2cbus);
	printf("Chip address: 0x%02x\n\n", chip_address);

	strncpy(autoadjust_table[row][0], "Reg. Name", TABLE_MAX_ELT_LEN);
	strncpy(autoadjust_table[row][1], "Reg. Addr",
		TABLE_MAX_ELT_LEN);
	strncpy(autoadjust_table[row][2], "Reg. Val.", TABLE_MAX_ELT_LEN);
	row++;

	while (strcmp(tlv320aic3x_reg_table[i].name, "END") != 0) {
		ret = i2cget(i2cbus, chip_address, tlv320aic3x_reg_table[i].addr, &val);
		if (ret == 0) {
			/* Show register name, addr & content (hex) */
			snprintf(autoadjust_table[row][0], TABLE_MAX_ELT_LEN,
				"%s", tlv320aic3x_reg_table[i].name);
			snprintf(autoadjust_table[row][1], TABLE_MAX_ELT_LEN,
				"%3u", tlv320aic3x_reg_table[i].addr);
			snprintf(autoadjust_table[row][2], TABLE_MAX_ELT_LEN,
				"0x%02X", val);
			row++;
		} else if (ret == -4) {
			/*
			 * Some registers maybe unaccessible if
			 * its voltage domain is disabled
			 */
			snprintf(autoadjust_table[row][0], TABLE_MAX_ELT_LEN,
				"%s", tlv320aic3x_reg_table[i].name);
			snprintf(autoadjust_table[row][1], TABLE_MAX_ELT_LEN,
				"%3u", tlv320aic3x_reg_table[i].addr);
			snprintf(autoadjust_table[row][2], TABLE_MAX_ELT_LEN,
				"INACTIVE");
			row++;
		} else {
			printf("omapconf_tlv320aic3x_dumpregs(): read error! "
				"(addr=%u, err=%d)\n",
				tlv320aic3x_reg_table[i].addr, ret);
			err = OMAPCONF_ERR_REG_ACCESS;
			break;
		}
		i++;
	}

	autoadjust_table_print(autoadjust_table, row, 3);

	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tlv320aic3x_main
 * @BRIEF		main entry point
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		main entry point
 *//*------------------------------------------------------------------------ */
int tlv320aic3x_main(int argc, char *argv[])
{
	int ret;

	if (argc == 1 || argc == 3) {
		if (strcmp(argv[0], "dump") == 0) {
			ret = tlv320aic3x_dumpregs(argc, argv);
		} else {
			help(HELP_AUDIOIC);
			ret = OMAPCONF_ERR_ARG;
		}
	} else {
		help(HELP_AUDIOIC);
		ret = OMAPCONF_ERR_ARG;
	}

	return ret;
}
