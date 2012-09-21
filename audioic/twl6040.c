/*
 *
 * @Component			OMAPCONF
 * @Filename			twl6040.c
 * @Description			TWL6040 Audio Companion Chip Functions
 * @Author			Misael Lopez Cruz (misael.lopez@ti.com)
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


#include <twl6040.h>
#include <i2c-tools.h>
#include <stdio.h>
#include <lib.h>
#include <twl6040_lib.h>
#include <autoadjust_table.h>
#include <help.h>
#include <cpuinfo.h>


/* #define TWL6040_DEBUG */
#ifdef TWL6040_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

#define TWL6040_REG_TABLE_SIZE	40

static const reg_table twl6040_reg_table[TWL6040_REG_TABLE_SIZE] = {
	{"ASICID", TWL6040_REG_ASICID},
	{"ASICREV", TWL6040_REG_ASICREV},
	{"INTID", TWL6040_REG_INTID},
	{"INTMR", TWL6040_REG_INTMR},
	{"NCPCTL", TWL6040_REG_NCPCTL},
	{"LDOCTL", TWL6040_REG_LDOCTL},
	{"HPPLLCTL", TWL6040_REG_HPPLLCTL},
	{"LPPLLCTL", TWL6040_REG_LPPLLCTL},
	{"LPPLLDIV", TWL6040_REG_LPPLLDIV},
	{"AMICBCTL", TWL6040_REG_AMICBCTL},
	{"DMICBCTL", TWL6040_REG_DMICBCTL},
	{"MICLCTL", TWL6040_REG_MICLCTL},
	{"MICRCTL", TWL6040_REG_MICRCTL},
	{"MICGAIN", TWL6040_REG_MICGAIN},
	{"LINEGAIN", TWL6040_REG_LINEGAIN},
	{"HSLCTL", TWL6040_REG_HSLCTL},
	{"HSRCTL", TWL6040_REG_HSRCTL},
	{"HSGAIN", TWL6040_REG_HSGAIN},
	{"EARCTL", TWL6040_REG_EARCTL},
	{"HFLCTL", TWL6040_REG_HFLCTL},
	{"HFLGAIN", TWL6040_REG_HFLGAIN},
	{"HFRCTL", TWL6040_REG_HFRCTL},
	{"HFRGAIN", TWL6040_REG_HFRGAIN},
	{"VIBCTLL", TWL6040_REG_VIBCTLL},
	{"VIBDATL", TWL6040_REG_VIBDATL},
	{"VIBCTLR", TWL6040_REG_VIBCTLR},
	{"VIBDATR", TWL6040_REG_VIBDATR},
	{"HKCTL1", TWL6040_REG_HKCTL1},
	{"HKCTL2", TWL6040_REG_HKCTL2},
	{"GPOCTL", TWL6040_REG_GPOCTL},
	{"ALB", TWL6040_REG_ALB},
	{"DLB", TWL6040_REG_DLB},
	{"TRIM1", TWL6040_REG_TRIM1},
	{"TRIM2", TWL6040_REG_TRIM2},
	{"TRIM3", TWL6040_REG_TRIM3},
	{"HSOTRIM", TWL6040_REG_HSOTRIM},
	{"HFOTRIM", TWL6040_REG_HFOTRIM},
	{"ACCCTL", TWL6040_REG_ACCCTL},
	{"STATUS", TWL6040_REG_STATUS},
	{"END", 0} };


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_dumpregs
 * @BRIEF		dump registers from table given as argument
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		none
 * @DESCRIPTION		dump registers from table given as argument
 *//*------------------------------------------------------------------------ */
int twl6040_dumpregs(void)
{
	unsigned int i = 0;
	unsigned int val = 0;
	int ret, err = 0;
	char autoadjust_table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row;

	autoadjust_table_init(autoadjust_table);
	row = 0;

	strncpy(autoadjust_table[row][0], "Reg. Name", TABLE_MAX_ELT_LEN);
	strncpy(autoadjust_table[row][1], "Reg. Addr",
		TABLE_MAX_ELT_LEN);
	strncpy(autoadjust_table[row][2], "Reg. Val.", TABLE_MAX_ELT_LEN);
	row++;

	while (strcmp(twl6040_reg_table[i].name, "END") != 0) {
		ret = i2cget(TWL6040_I2C_BUS, TWL6040_I2C_ADDR,
			twl6040_reg_table[i].addr, &val);
		if (ret == 0) {
			/* Show register name, addr & content (hex) */
			snprintf(autoadjust_table[row][0], TABLE_MAX_ELT_LEN,
				"%s", twl6040_reg_table[i].name);
			snprintf(autoadjust_table[row][1], TABLE_MAX_ELT_LEN,
				"0x%02X", twl6040_reg_table[i].addr);
			snprintf(autoadjust_table[row][2], TABLE_MAX_ELT_LEN,
				"0x%02X", val);
			row++;
		} else if (ret == -4) {
			/*
			 * Some registers maybe unaccessible if
			 * its voltage domain is disabled
			 */
			snprintf(autoadjust_table[row][0], TABLE_MAX_ELT_LEN,
				"%s", twl6040_reg_table[i].name);
			snprintf(autoadjust_table[row][1], TABLE_MAX_ELT_LEN,
				"0x%02X", twl6040_reg_table[i].addr);
			snprintf(autoadjust_table[row][2], TABLE_MAX_ELT_LEN,
				"INACTIVE");
			row++;
		} else {
			printf("omapconf_twl6040_dumpregs(): read error! "
				"(addr=0x%02X, err=%d)\n",
				twl6040_reg_table[i].addr, ret);
			err = OMAPCONF_ERR_REG_ACCESS;
			break;
		}
		i++;
	}

	autoadjust_table_print(autoadjust_table, row, 3);

	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_name2addr
 * @BRIEF		retrieve physical address of a register, given its name.
 * @RETURNS		0 on success
 *			-1 if address not found
 * @param[in,out]	name: register name
 * @param[in,out]	addr: register address
 * @DESCRIPTION		retrieve physical address of a register, given its name.
 *//*------------------------------------------------------------------------ */
int twl6040_name2addr(char *name, unsigned int *addr)
{
	return name2addr(name, addr, (reg_table *) twl6040_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_config
 * @BRIEF		analyze TWL6040 audio configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output file stream
 * @DESCRIPTION		analyze TWL6040 audio configuration
 *//*------------------------------------------------------------------------ */
int twl6040_config(FILE *stream)
{
	unsigned char twl6040_regs[TWL6040_REG_NUM];
	unsigned int i = 0, val;
	int ret;

	while (strcmp(twl6040_reg_table[i].name, "END") != 0) {
		ret = i2cget(TWL6040_I2C_BUS, TWL6040_I2C_ADDR,
			twl6040_reg_table[i].addr, &val);
		if (ret != 0) {
			printf("twl6040_config(): read error! "
				"(addr=0x%02X, err=%d)\n",
				twl6040_reg_table[i].addr, ret);
			return OMAPCONF_ERR_REG_ACCESS;
		}
		twl6040_regs[twl6040_reg_table[i].addr] = val;
		i++;
	}

	ret = twl6040_display_version_config(stream, twl6040_regs);
	if (ret != 0)
		return ret;

	ret = twl6040_display_control_config(stream, twl6040_regs);
	if (ret != 0)
		return ret;

	ret = twl6040_display_power_config(stream, twl6040_regs);
	if (ret != 0)
		return ret;

	ret = twl6040_display_clocking_config(stream, twl6040_regs);
	if (ret != 0)
		return ret;

	ret = twl6040_display_interrupts_config(stream, twl6040_regs);
	if (ret != 0)
		return ret;

	ret = twl6040_display_biasing_config(stream, twl6040_regs);
	if (ret != 0)
		return ret;

	ret = twl6040_display_uplink_config(stream, twl6040_regs);
	if (ret != 0)
		return ret;

	ret = twl6040_display_downlink1_config(stream, twl6040_regs);
	if (ret != 0)
		return ret;

	ret = twl6040_display_downlink2_config(stream, twl6040_regs);
	if (ret != 0)
		return ret;

	ret = twl6040_display_vibrator_config(stream, twl6040_regs);
	if (ret != 0)
		return ret;

	ret = twl6040_display_loopback_config(stream, twl6040_regs);
	if (ret != 0)
		return ret;

	ret = twl6040_display_gpo_config(stream, twl6040_regs);
	if (ret != 0)
		return ret;

	ret = twl6040_display_misc_config(stream, twl6040_regs);
	if (ret != 0)
		return ret;

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_gains
 * @BRIEF		analyze TWL6040 analog gains
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output file stream
 * @DESCRIPTION		analyze TWL6040 analog gains
 *//*------------------------------------------------------------------------ */
int twl6040_gains(FILE *stream)
{
	unsigned char twl6040_regs[TWL6040_REG_NUM];
	unsigned int i = 0, val;
	int ret = 0;

	while (strcmp(twl6040_reg_table[i].name, "END") != 0) {
		ret = i2cget(TWL6040_I2C_BUS, TWL6040_I2C_ADDR,
			twl6040_reg_table[i].addr, &val);
		if (ret != 0) {
			printf("twl6040_config(): read error! "
				"(addr=0x%02X, err=%d)\n",
				twl6040_reg_table[i].addr, ret);
			return OMAPCONF_ERR_REG_ACCESS;
		}
		twl6040_regs[twl6040_reg_table[i].addr] = val;
		i++;
	}

	ret = twl6040_display_gains(stream, twl6040_regs);

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_readreg
 * @BRIEF		read data from given TWL6040 address
 * @RETURNS		0 in case of success
 *			-1 in case of incorrect register name/address
 *			-2 in case of incorrect format
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		reg_addr: Register address (name or hex address)
 * @DESCRIPTION		read data from given TWL6040 address
 *//*------------------------------------------------------------------------ */
int twl6040_readreg(const char *reg_addr)
{
	unsigned int value, addr;
	char name[OMAPCONF_REG_NAME_MAX_LENGTH + 1] = "";
	unsigned char by_name = 0;
	int ret = 0;

	if (reg_addr == NULL) {
		printf("Oups, missing register name/address!!!\n\n");
		help(HELP_AUDIOIC);
		return 0;
	}
	reg_addr = uppercase((char *) reg_addr);

	/* Retrieve and check register address */
	if ((reg_addr[0] == '0') && (reg_addr[1] == 'X')) {
		/* As an integer, must start with "0x" */
		ret = sscanf(reg_addr, "0X%x", &addr);
		if (ret != 1) {
			printf("Oups, register address not recognized!!!\n\n");
			help(HELP_AUDIOIC);
			return 0;
		}
	} else {
		/* As a string, must start with alpha character */
		if (isalpha(reg_addr[0])) {
			ret = sscanf(reg_addr, "%50s", (char *) name);
			if (ret != 1) {
				printf("Oups, register name not recognized!!!"
					"\n\n");
				help(HELP_AUDIOIC);
				return 0;
			}
			by_name = 1;
		} else {
			printf("Oups, register name/address not recognized!!!"
				"\n\n");
			help(HELP_AUDIOIC);
			return 0;
		}
	}

	/*
	 * if reg. name was entered, check name is valid and retrieve reg. addr.
	 */
	if (by_name == 1) {
		ret = twl6040_name2addr((char *)name, &addr);
		if (ret != 0) {
			printf("Oups, not a valid register name!!!\n"
				"Try \"omapconf dump audioic\" to get valid "
				"register names.\n\n");
			return 0;
		}
	}

	/* debug */
	if (by_name == 1) {
		dprintf("%s reg name=%s\n", __func__, name);
	}
	dprintf("%s addr=0x%02x\n", __func__, addr);

	/* Read i2c register (assuming TWL6040 is in bus 1) */
	ret = i2cget(1, TWL6040_I2C_ADDR, addr, &value);
	if (ret != 0) {
		printf("Oups, internal error (failed to read)!!!\n\n");
		return 0;
	}

	/* Display value in selected format */
	printf("%02X\n\n", value);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_writereg
 * @BRIEF		write given data to given TWL6040 address
 * @RETURNS		0 in case of success
 *			-1 in case of incorrect register name/address
 *			-2 in case of incorrect format
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		reg_addr: Register address (name or hex address)
 * @param[in]		reg_val: Register value
 * @DESCRIPTION		write given data to given TWL6040 address
 *//*------------------------------------------------------------------------ */
int twl6040_writereg(const char *reg_addr, const char *reg_val)
{
	unsigned int value, addr;
	char name[OMAPCONF_REG_NAME_MAX_LENGTH + 1] = "";
	unsigned char by_name = 0;
	int ret = 0;

	if (reg_addr == NULL) {
		printf("Oups, missing register name/address!!!\n\n");
		help(HELP_AUDIOIC);
		return 0;
	}
	reg_addr = uppercase((char *) reg_addr);


	if (reg_val == NULL) {
		printf("Oups, missing value to be written!!!\n\n");
		help(HELP_AUDIOIC);
		return 0;
	}
	reg_val = uppercase((char *) reg_val);


	/* Retrieve and check register address */
	if ((reg_addr[0] == '0') && (reg_addr[1] == 'X')) {
		/* As an integer, must start with "0x" */
		ret = sscanf(reg_addr, "0X%x", &addr);
		if (ret != 1) {
			printf("Oups, register address not recognized!!!\n\n");
			help(HELP_AUDIOIC);
			return 0;
		}
	} else {
		/* As a string, must start with alpha character */
		if (isalpha(reg_addr[0])) {
			ret = sscanf(reg_addr, "%50s", (char *) name);
			if (ret != 1) {
				printf("Oups, register address not recognized"
					"!!!\n\n");
			help(HELP_AUDIOIC);
				return 0;
			}
			by_name = 1;
		} else {
			printf("Oups, register address not recognized!!!\n\n");
			help(HELP_AUDIOIC);
			return 0;
		}
	}

	/*
	 * if reg. name was entered, check name is valid and retrieve reg. addr.
	 */
	if (by_name == 1) {
		ret = twl6040_name2addr((char *)name, &addr);
		if (ret != 0) {
			printf("Oups, not a valid register name!!!\n"
				"Try \"omapconf dump audioic\" to get valid "
				"register names.\n\n");
			return 0;
		}
	}

	/* Retrieve and check value to be written into register */
	if ((reg_val[0] == '0') && (reg_val[1] == 'X')) {
		/* As an integer, must start with "0x" */
		ret = sscanf(reg_val, "0X%x", &value);
		if (ret != 1) {
			printf("Oups, value to be written not recognized!\n\n");
			help(HELP_AUDIOIC);
			return 0;
		}
	} else {
		printf("Oups, value to be written not recognized!\n\n");
		help(HELP_AUDIOIC);
		return 0;
	}

	/* debug */
	if (by_name == 1) {
		dprintf("%s reg name=%s\n", __func__, name);
	}
	dprintf("%s reg addr=0x%02x\n", __func__, addr);
	dprintf("%s reg val=0x%02x\n", __func__, value);

	/* Write i2c register */
	ret = i2cset(TWL6040_I2C_BUS, TWL6040_I2C_ADDR, addr, value);
	if (ret != 0)
		printf("Oups, internal error (failed to write)!\n\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_chip_revision_get
 * @BRIEF		return TWL6040 chip revision
 * @RETURNS		>0.0 TWL6030 chip revision
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		none
 * @DESCRIPTION		return TWL6040 chip revision
 *//*------------------------------------------------------------------------ */
float twl6040_chip_revision_get(void)
{
	int ret;
	unsigned int revcode;
	float rev;

	ret = i2cget(TWL6040_I2C_BUS, TWL6040_I2C_ADDR, 0x02, &revcode);
	if (ret != 0) {
		dprintf("%s(): could not read register! (%d)\n", __func__, ret);
		return (float) OMAPCONF_ERR_NOT_AVAILABLE;
	}

	rev = 0.1 * (float) (revcode & 0x0F);
	rev += 1 * (float) (1 + ((revcode & 0xF0) >> 4));

	return rev;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6040_main
 * @BRIEF		main entry point
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		main entry point
 *//*------------------------------------------------------------------------ */
int twl6040_main(int argc, char *argv[])
{
	int ret;

	if (argc == 2) {
		if (strcmp(argv[1], "dump") == 0) {
			ret = twl6040_dumpregs();
		} else if (strcmp(argv[1], "cfg") == 0) {
			ret = twl6040_config(stdout);
		} else if (strcmp(argv[1], "gains") == 0) {
			ret = twl6040_gains(stdout);
		} else {
			help(HELP_AUDIOIC);
			ret = OMAPCONF_ERR_ARG;
		}
	} else if (argc == 3) {
		if (strcmp(argv[1], "read") == 0) {
			ret = twl6040_readreg(uppercase(argv[2]));
		} else {
			help(HELP_AUDIOIC);
			ret = OMAPCONF_ERR_ARG;
		}
	} else if (argc == 4) {
		if (strcmp(argv[1], "write") == 0) {
			ret = twl6040_writereg(uppercase(argv[2]),
				uppercase(argv[3]));
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
