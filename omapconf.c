/*
 *
 * @Component			OMAPCONF
 * @Filename			omapconf.c
 * @Description			omapconf main entry file
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


#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <lib.h>
#include <lib44xx.h>
#include <main44xx.h>
#include <main54xx.h>
#include <main_am335x.h>
#include <main_am437x.h>
#include <main_dra7xx.h>
#include <dpll54xx.h>
#include <lib_android.h>
#include <i2c-tools.h>
#include <help.h>
#include <autoadjust_table.h>
#include <cpuinfo.h>
#include <signal.h>
#include <mem.h>
#include <lib54xx.h>
#include <trace.h>
#include <mem.h>
#include <opp.h>
#include <voltdomain.h>
#include <temperature.h>
#include <module.h>
#include <powerdomain.h>
#include <clockdomain.h>


/* #define DEBUG */
#ifdef DEBUG
/* #define OMAPCONF_READREG_DEBUG */
/* #define OMAPCONF_WRITEREG_DEBUG */
/* #define OMAPCONF_CLEARBIT_DEBUG */
/* #define OMAPCONF_SETBIT_DEBUG */
/* #define OMAPCONF_FIND_REG_ADDR_DEBUG */
/* #define OMAPCONF_ADDRESS_IN_VALID_RANGE_DEBUG */
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static unsigned short cpu_found;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main_readreg
 * @BRIEF		read OMAP register
 * @RETURNS		0 in case of success
 *			-1 in case of incorrect register name/address
 *			-2 in case of incorrect format
 * @param[in]		reg_addr: register address
 *			can be hex value (with mandatory '0x' prefix) or name
 * @param[in]		val_format: value output format
 *			can be "hex", "bin" or "dec"
 * @DESCRIPTION		read OMAP register
 *//*------------------------------------------------------------------------ */
static int main_readreg(const char *reg_addr, const char *val_format)
{
	int ret = 0;
	unsigned int value, addr;
	char value_bin[33] = ""; /*  32 digits + '\0' */
	char name[OMAPCONF_REG_NAME_MAX_LENGTH + 1] = "";
	unsigned char by_name = 0;

	#ifdef OMAPCONF_READREG_DEBUG
	printf("%s(): reg_addr=%s\n", __func__, reg_addr);
	#endif

	/* Retrieve and check register address */
	if ((reg_addr[0] == '0') && (reg_addr[1] == 'X')) {
		/* As an integer, must start with "0x" */
		ret = sscanf(reg_addr, "0X%x", &addr);
		if (ret != 1) {
			#ifdef OMAPCONF_READREG_DEBUG
			printf("%s(): could not retrieve integer value\n",
				__func__);
			#endif
			fprintf(stderr,	"register address not recognized!\n");
			return -1;
		}
	} else {
		/* As a string, must start with alpha character */
		if (isalpha(reg_addr[0])) {
			ret = sscanf(reg_addr, "%50s", (char *) name);
			if (ret != 1) {
				#ifdef OMAPCONF_READREG_DEBUG
				printf("%s(): could not retrieve name\n",
					__func__);
				#endif
				fprintf(stderr,
					"register name not recognized!\n");
				return -1;
			} else
				by_name = 1;
		} else {
			fprintf(stderr,
			"register name/address not recognized!\n");
			return -1;
		}
	}

	#ifdef OMAPCONF_READREG_DEBUG
	if (by_name)
		printf("%s(): found reg_addr = %s\n", __func__, name);
	else
		printf("%s(): found reg_addr = 0x%08X\n", __func__, addr);
	#endif

	/*
	 * If reg. name was entered, check name is valid and retrieve reg. addr.
	 */
	if (by_name == 1) {
		ret = find_reg_addr((char *) name, &addr);
		if (ret != 0) {
			fprintf(stderr,	"not a valid register name!\n");
			return -1;
		}
		#ifdef OMAPCONF_READREG_DEBUG
		else
			printf("%s(): reg. addr. found. (0x%08X)\n",
				__func__, addr);
		#endif
	}

	/* Check data format is valid */
	if ((strcmp(val_format, "hex") != 0) &&
			(strcmp(val_format, "bin") != 0) &&
			(strcmp(val_format, "dec") != 0)) {
		fprintf(stderr, "not a valid format! (%s)\n", val_format);
		return -2;
	}

	/* Reaching this point means arguments OK */
	#ifdef OMAPCONF_READREG_DEBUG
	printf("%s(): addr=%x\n", __func__, addr);
	printf("%s(): name=%s\n", __func__, name);
	printf("%s(): format=%s\n", __func__, val_format);
	printf("%s(): ret=%d\n", __func__, ret);
	#endif

	/* Read OMAP register */
	ret = mem_read(addr, &value);
	if (ret != 0) {
		fprintf(stderr, "internal error (failed to read)!\n");
		return OMAPCONF_ERR_REG_ACCESS;
	}

	/* Display value in selected format */
	if (strcmp(val_format, "hex") == 0) {
		printf("%08X\n", value);
	} else if (strcmp(val_format, "bin") == 0) {
		/* compiler does not understand %b, so do it manually */
		/* printf("%b\n", value); */
		printf("%s\n", bin2str_32(value_bin, value));
	} else {
		/* val_format == "dec" */
		printf("%d\n", value);
	}

	return 0;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main_writereg
 * @BRIEF		write into OMAP register
 * @RETURNS		0 in case of success
 *			-1 in case of incorrect register name/address
 *			-2 in case of incorrect format
 * @param[in]		reg_addr: register address
 *			can be hex value (with mandatory'0x' prefix) or name
 * @param[in]		reg_val: value to be written into reg_addr
 * @DESCRIPTION		write into OMAP register
 *//*------------------------------------------------------------------------ */
static int main_writereg(const char *reg_addr, const char *reg_val)
{
	int ret = 0;
	unsigned int value, addr;
	char name[OMAPCONF_REG_NAME_MAX_LENGTH + 1] = "";
	unsigned char by_name = 0;

	#ifdef OMAPCONF_WRITEREG_DEBUG
	printf("%s(): reg_addr=%s\n", __func__, reg_addr);
	printf("%s(): reg_val=%s\n", __func__, reg_val);
	#endif

	/* Retrieve and check register address */
	if ((reg_addr[0] == '0') && (reg_addr[1] == 'X')) {
		/* As an integer, must start with "0x" */
		ret = sscanf(reg_addr, "0X%x", &addr);
		if (ret != 1) {
			#ifdef OMAPCONF_WRITEREG_DEBUG
			printf("%s(): could not retrieve integer value\n",
				__func__);
			#endif
			fprintf(stderr,
				"register address not recognized!\n");
			return -1;
		}
	} else {
		/* As a string, must start with alpha character */
		if (isalpha(reg_addr[0])) {
			ret = sscanf(reg_addr, "%50s", (char *) name);
			if (ret != 1) {
				#ifdef OMAPCONF_WRITEREG_DEBUG
				printf("(): could not retrieve name\n",
					__func__);
				#endif
				fprintf(stderr,
					"register name not recognized!\n");
				return -1;
			} else
				by_name = 1;
		} else {
			fprintf(stderr,
			"register name/address not recognized!\n");
			return -1;
		}
	}

	#ifdef OMAPCONF_WRITEREG_DEBUG
	if (by_name)
		printf("%s(): found reg_addr = %s\n", __func__, name);
	else
		printf("%s(): found reg_addr = 0x%08X\n", __func__, addr);
	#endif

	/*
	 * If reg. name was entered, check name is valid and retrieve reg. addr.
	 */
	if (by_name == 1) {
		ret = find_reg_addr((char *) name, &addr);
		if (ret != 0) {
			fprintf(stderr, "not a valid register name!\n");
			return -1;
		}
		#ifdef OMAPCONF_WRITEREG_DEBUG
		else
			printf("%s(): reg. addr. found. (0x%08X)\n",
				__func__, addr);
		#endif
	}

	/* Retrieve and check value to be written into register */
	if ((reg_val[0] == '0') && (reg_val[1] == 'X')) {
		/* As an integer, must start with "0x" */
		ret = sscanf(reg_val, "0X%x", &value);
		if (ret != 1) {
			#ifdef OMAPCONF_WRITEREG_DEBUG
			printf("%s(): could not retrieve integer value\n",
				__func__);
			#endif
			fprintf(stderr,
				"register address not recognized!\n");
			return -2;
		}
	} else {
		fprintf(stderr,
			"value to be written not recognized!\n");
		return -2;
	}

	#ifdef OMAPCONF_WRITEREG_DEBUG
	printf("%s(): found value = 0x%08X\n", __func__, value);
	#endif

	/* Reaching this point means arguments OK */
	#ifdef OMAPCONF_WRITEREG_DEBUG
	printf("%s(): addr=0x%x\n", __func__, addr);
	printf("%s(): name=%s\n", __func__, name);
	printf("%s(): value=0x%x\n", __func__, value);
	printf("%s(): ret=%d\n", __func__, ret);
	#endif

	/* Write OMAP register */
	ret = mem_write(addr, value);
	if (ret != 0) {
		fprintf(stderr, "internal error (failed to write)!\n");
		return OMAPCONF_ERR_REG_ACCESS;
	}

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main_clearbit
 * @BRIEF		clear given bit into OMAP register
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		clear given bit into OMAP register
 *//*------------------------------------------------------------------------ */
static int main_clearbit(int argc, char *argv[])
{
	int ret = 0;
	unsigned int pos, value, value2, addr;
	char name[OMAPCONF_REG_NAME_MAX_LENGTH + 1] = "";
	unsigned char by_name = 0;

	if (strcmp(argv[0], "clear") != 0)
		goto main_clearbit_arg_err;
	if (strcmp(argv[1], "bit") != 0)
		goto main_clearbit_arg_err;
	if (argc != 4)
		goto main_clearbit_arg_err;

	argv[2] = uppercase(argv[2]);

	#ifdef OMAPCONF_CLEARBIT_DEBUG
	printf("%s(): argv[0]=%s\n", __func__, argv[0]);
	printf("%s(): argv[1]=%s\n", __func__, argv[1]);
	printf("%s(): argv[2]=%s\n", __func__, argv[2]);
	printf("%s(): argv[3]=%s\n", __func__, argv[3]);
	#endif

	/* Retrieve and check register address */
	if ((argv[2][0] == '0') && (argv[2][1] == 'X')) {
		/* As an integer, must start with "0x" */
		ret = sscanf(argv[2], "0X%x", &addr);
		if (ret != 1) {
			#ifdef OMAPCONF_CLEARBIT_DEBUG
			printf("%s(): could not retrieve integer value\n",
				__func__);
			#endif
			goto main_clearbit_arg_err;
		}
	} else {
		/* As a string, must start with alpha character */
		if (isalpha(argv[2][0])) {
			ret = sscanf(argv[2], "%72s", (char *) name);
			if (ret != 1) {
				#ifdef OMAPCONF_CLEARBIT_DEBUG
				printf("%s(): could not retrieve name\n",
					__func__);
				#endif
				goto main_clearbit_arg_err;
			} else
				by_name = 1;
		} else {
			goto main_clearbit_arg_err;
		}
	}

	#ifdef OMAPCONF_CLEARBIT_DEBUG
	if (by_name)
		printf("%s(): found reg_addr = %s\n", __func__, name);
	else
		printf("%s(): found reg_addr = 0x%08X\n", __func__, addr);
	#endif

	/*
	 * If reg. name was entered, check name is valid and retrieve reg. addr.
	 */
	if (by_name == 1) {
		ret = find_reg_addr((char *) name, &addr);
		if (ret != 0) {
			printf("Not a valid register name! (%s)\n", name);
			return OMAPCONF_ERR_ARG;
		}
		#ifdef OMAPCONF_CLEARBIT_DEBUG
		else
			printf("%s(): reg. addr. found. (0x%08X)\n",
				__func__, addr);
		#endif
	}

	/* Retrieve and check bit position */
	ret = sscanf(argv[3], "%u", &pos);
	if (ret != 1) {
			#ifdef OMAPCONF_CLEARBIT_DEBUG
			printf("%s(): could not retrieve bit position\n",
				__func__);
			#endif
			goto main_clearbit_arg_err;
	}
	if (pos >= 32) {
		printf("Incorrect bit position! (%s)\n", argv[3]);
		return OMAPCONF_ERR_ARG;
	}

	#ifdef OMAPCONF_CLEARBIT_DEBUG
	printf("%s(): found position = %u\n", __func__, pos);
	#endif

	/* Reaching this point means arguments OK */
	#ifdef OMAPCONF_CLEARBIT_DEBUG
	printf("%s(): addr=0x%x\n", __func__, addr);
	printf("%s(): name=%s\n", __func__, name);
	printf("%s(): pos=%d\n", __func__, pos);
	printf("%s(): ret=%d\n", __func__, ret);
	#endif

	/* Clear bit in OMAP register */
	ret = mem_read(addr, &value);
	if (ret != 0) {
		fprintf(stderr, "internal error (failed to write)!\n");
		return OMAPCONF_ERR_REG_ACCESS;
	}

	#ifdef OMAPCONF_CLEARBIT_DEBUG
	printf("%s(): value=0x%x\n", __func__, value);
	printf("%s(): 1<<pos=0x%x\n", __func__, 1 << pos);
	printf("%s(): ~(1<<pos)=0x%x\n", __func__, ~(1 << pos));
	printf("%s(): value & ~(1<<pos)=0x%x\n", __func__, value & ~(1 << pos));
	#endif
	ret = mem_write(addr, value & ~(1 << pos));
	if (ret != 0) {
		fprintf(stderr, "internal error (failed to write)!\n");
		return OMAPCONF_ERR_REG_ACCESS;
	}

	ret = mem_read(addr, &value2);
	if (ret != 0) {
		fprintf(stderr, "internal error (failed to read back)!\n");
		return OMAPCONF_ERR_REG_ACCESS;
	}
	printf("@0x%08X: 0x%08X ==> 0x%08X\n\n", addr, value, value2);
	return ret;

main_clearbit_arg_err:
	help(HELP_RW);
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main_setbit
 * @BRIEF		set given bit into OMAP register
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		set given bit into OMAP register
 *//*------------------------------------------------------------------------ */
static int main_setbit(int argc, char *argv[])
{
	int ret = 0;
	unsigned int pos, value, value2, addr;
	char name[OMAPCONF_REG_NAME_MAX_LENGTH + 1] = "";
	unsigned char by_name = 0;

	if (strcmp(argv[0], "set") != 0)
		goto main_setbit_arg_err;
	if (strcmp(argv[1], "bit") != 0)
		goto main_setbit_arg_err;
	if (argc != 4)
		goto main_setbit_arg_err;

	argv[2] = uppercase(argv[2]);

	#ifdef OMAPCONF_SETBIT_DEBUG
	printf("%s(): argv[0]=%s\n", __func__, argv[0]);
	printf("%s(): argv[1]=%s\n", __func__, argv[1]);
	printf("%s(): argv[2]=%s\n", __func__, argv[2]);
	printf("%s(): argv[3]=%s\n", __func__, argv[3]);
	#endif

	/* Retrieve and check register address */
	if ((argv[2][0] == '0') && (argv[2][1] == 'X')) {
		/* As an integer, must start with "0x" */
		ret = sscanf(argv[2], "0X%x", &addr);
		if (ret != 1) {
			#ifdef OMAPCONF_SETBIT_DEBUG
			printf("%s(): could not retrieve integer value\n",
				__func__);
			#endif
			goto main_setbit_arg_err;
		}
	} else {
		/* As a string, must start with alpha character */
		if (isalpha(argv[2][0])) {
			ret = sscanf(argv[2], "%72s", (char *) name);
			if (ret != 1) {
				#ifdef OMAPCONF_SETBIT_DEBUG
				printf("%s(): could not retrieve name\n",
					__func__);
				#endif
				goto main_setbit_arg_err;
			} else
				by_name = 1;
		} else
			goto main_setbit_arg_err;
	}

	#ifdef OMAPCONF_SETBIT_DEBUG
	if (by_name)
		printf("%s(): found reg_addr = %s\n", __func__, name);
	else
		printf("%s(): found reg_addr = 0x%08X\n", __func__, addr);
	#endif

	/*
	 * If reg. name was entered, check name is valid and retrieve reg. addr.
	 */
	if (by_name == 1) {
		ret = find_reg_addr((char *) name, &addr);
		if (ret != 0) {
			printf("Not a valid register name! (%s)\n", name);
			return OMAPCONF_ERR_ARG;
		}
		#ifdef OMAPCONF_SETBIT_DEBUG
		else
			printf("%s(): reg. addr. found. (0x%08X)\n",
				__func__, addr);
		#endif
	}

	/* Retrieve and check bit position */
	ret = sscanf(argv[3], "%u", &pos);
	if (ret != 1) {
			#ifdef OMAPCONF_SETBIT_DEBUG
			printf("%s(): could not retrieve bit position\n",
				__func__);
			#endif
			goto main_setbit_arg_err;
	}
	if (pos > 31) {
		printf("Incorrect bit position! (%s)\n", argv[3]);
		return OMAPCONF_ERR_ARG;
	}

	#ifdef OMAPCONF_SETBIT_DEBUG
	printf("%s(): found position = %u\n", __func__, pos);
	#endif

	/* Reaching this point means arguments OK */
	#ifdef OMAPCONF_SETBIT_DEBUG
	printf("%s(): addr=0x%x\n", __func__, addr);
	printf("%s(): name=%s\n", __func__, name);
	printf("%s(): pos=%d\n", __func__, pos);
	printf("%s(): ret=%d\n", __func__, ret);
	#endif

	/* Set bit in OMAP register */
	ret = mem_read(addr, &value);
	if (ret != 0) {
		fprintf(stderr, "internal error (failed to read)!\n");
		return OMAPCONF_ERR_REG_ACCESS;
	}

	#ifdef OMAPCONF_SETBIT_DEBUG
	printf("%s(): value = 0x%x\n", __func__, value);
	printf("%s(): 1 << pos = 0x%x\n", __func__, 1 << pos);
	printf("%s(): value | (1 << pos) = 0x%x\n",
		__func__, value | (1 << pos));
	#endif
	ret = mem_write(addr, value | (1 << pos));
	if (ret != 0) {
		fprintf(stderr, "internal error (failed to write)!\n");
		return OMAPCONF_ERR_REG_ACCESS;
	}

	ret = mem_read(addr, &value2);
	if (ret != 0) {
		fprintf(stderr, "internal error (failed to read back)!\n");
		return OMAPCONF_ERR_REG_ACCESS;
	}
	printf("@0x%08X: 0x%08X ==> 0x%08X\n\n", addr, value, value2);
	return ret;

main_setbit_arg_err:
	help(HELP_RW);
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main_i2c_read
 * @BRIEF		read given data from given address of given device of
 *			given I2C bus
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		argc: shell input argument number
 *			argc must be 5
 * @param[in]		argv: shell input argument(s)
 *			argv[2] = i2cbus: I2C bus number
 *			argv[3] = address: I2C device address
 *			argv[4] = daddress: I2C device register address
 * @DESCRIPTION		read given data from given address of given device of
 *			given I2C bus
 *//*------------------------------------------------------------------------ */
static int main_i2c_read(int argc, char *argv[])
{
	unsigned int i2cbus, chip_address, data_address;
	unsigned int data;
	int ret;

	CHECK_NULL_ARG(argv, OMAPCONF_ERR_ARG);

	/* Retrieve arguments */
	if (argc != 5)
		goto main_i2c_read_err;
	ret = sscanf(argv[2], "%u", &i2cbus);
	if (ret != 1)
		goto main_i2c_read_err;
	ret = sscanf(argv[3], "0x%x", &chip_address);
	if (ret != 1)
		goto main_i2c_read_err;
	ret = sscanf(argv[4], "0x%x", &data_address);
	if (ret != 1)
		goto main_i2c_read_err;

	ret = i2cget(i2cbus, chip_address, data_address, &data);
	if (ret == 0)
		printf("0x%02x\n", data);
	return ret;

main_i2c_read_err:
	printf(
		"Usage: omapconf i2c read 'i2cbus' 0x'chip-address' 0x'data-address'\n");
	printf("  'i2cbus' is decimal value.\n");
	printf("  'chip-address' & 'data-address' are hexadecimal values.\n");
	printf("  Warning: prefix '0x' is mandatory.\n");
	return OMAPCONF_ERR_ARG;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main_i2c_write
 * @BRIEF		write given data at given address of given device of
 *			given I2C bus
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		argc: shell input argument number
 *			argc must be 6
 * @param[in]		argv: shell input argument(s)
 *			argv[2] = i2cbus: I2C bus number
 *			argv[3] = address: I2C device address
 *			argv[4] = daddress: I2C device register address
 *			argv[5] = data: data to be written
 * @DESCRIPTION		write given data at given address of given device of
 *			given I2C bus
 *//*------------------------------------------------------------------------ */
static int main_i2c_write(int argc, char *argv[])
{
	unsigned int i2cbus, chip_address, data_address;
	unsigned int data;
	int ret;

	if (argv == NULL) {
		printf("%s(): argv == NULL!!!\n", __func__);
		return OMAPCONF_ERR_ARG;
	}
	/* Retrieve arguments */
	if (argc != 6)
		goto main_i2c_write_err;
	ret = sscanf(argv[2], "%u", &i2cbus);
	if (ret != 1)
		goto main_i2c_write_err;
	ret = sscanf(argv[3], "0x%x", &chip_address);
	if (ret != 1)
		goto main_i2c_write_err;
	ret = sscanf(argv[4], "0x%x", &data_address);
	if (ret != 1)
		goto main_i2c_write_err;
	ret = sscanf(argv[5], "0x%x", &data);
	if (ret != 1)
		goto main_i2c_write_err;

	ret = i2cset(i2cbus, chip_address, data_address, data);
	return ret;

main_i2c_write_err:
	printf(
		"Usage: omapconf i2c write 'i2cbus' 0x'chip-address' 0x'data-address' 0x'data'\n");
	printf("  'i2cbus' is decimal value.\n");
	printf(
		"  'chip-address', 'data-address' & 'data' are hexadecimal values.\n");
	printf("  Warning: prefix '0x' is mandatory.\n");
	return OMAPCONF_ERR_ARG;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main_sigbus_handler
 * @BRIEF		catch bus error and print failing memory physical
 *			address
 * @DESCRIPTION		catch bus error and print failing memory physical
 *			address
 *//*------------------------------------------------------------------------ */
static void main_sigbus_handler(int sig, siginfo_t *siginfo, void *context)
{
	/* just to remove "unused parameter" warnings ... */
	sig = sig;
	siginfo = siginfo;
	context = context;

	dprintf("%s(): sig=%d siginfo=0x%08X, context=0x%08X\n", __func__, sig,
		(unsigned int) siginfo, (unsigned int) context);
	fprintf(stderr, "\n\n!!! OUPS... MEMORY ERROR @ 0x%08X !!!\n",
		mem_last_addr_get());
	fprintf(stderr, "Are you sure that:\n");
	fprintf(stderr, "    MEMORY ADDRESS IS VALID?\n");
	fprintf(stderr, "    TARGETED MODULE IS CLOCKED?\n\n");

	exit(-1);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main_arguments_lowercase
 * @BRIEF		make sure all user arguments are in lower case.
 * @RETURNS		none
 * @param[in, out]	argc: shell input argument number
 * @param[in, out]	argv: shell input argument(s)
 * @DESCRIPTION		make sure all user arguments are in lower case, so that
 *			case can be ignored further on.
 *//*------------------------------------------------------------------------ */
static void main_arguments_lowercase(int argc, char *argv[])
{
	int i;

	for (i = 0; i < argc; i++) {
		dprintf("%s(): Before: argv[%d] = '%s'\n",
			__func__, argc, argv[i]);
		lowercase(argv[i]);
		dprintf("%s(): After: argv[%d] = '%s'\n",
			__func__, argc, argv[i]);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main_options_scan
 * @BRIEF		search for omapconf option(s) in argv and set it.
 *			Remove found option(s) from argv (by increasing argv
 *			pointer).
 * @RETURNS		>= 0 number of options found
 *			OMAPCONF_ERR_ARG
 * @param[in, out]	argc: shell input argument number
 * @param[in, out]	argv: shell input argument(s)
 * @DESCRIPTION		search for omapconf option(s) in argv and set it.
 *			Remove found option(s) from argv (by increasing argv
 *			pointer).
 *//*------------------------------------------------------------------------ */
static int main_options_scan(int *argc, char **argv[])
{
	int ret = 0, cpt = 0;
	int i;

	if (argc == NULL) {
		fprintf(stderr, "%s(): argc == NULL!!!\n", __func__);
		goto main_options_scan_err;
	}
	if (argv == NULL) {
		fprintf(stderr, "%s(): argv == NULL!!!\n", __func__);
		goto main_options_scan_err;
	}
	for (i = 0; i < *argc; i++) {
		if (strcmp((*argv)[i], "--import") == 0) {
			dprintf("%s(): found option \"--import\" at i=%u\n",
				__func__, i);
			if (i + 1 == *argc) {
				/* missing import file name, abort */
				omapconf_revision_show(stdout);
				printf("Error: missing import file name!\n\n");
				help(HELP_ALL);
				goto main_options_scan_err;
			}
			if (!cpu_is_omap54xx()) {
				printf(
					"Sorry, only available for OMAP5...\n\n");
				goto main_options_scan_err;
			}
			/* Import register content from file */
			ret = lib54xx_import((*argv)[i + 1]);
			if (ret != 0) {
				omapconf_revision_show(stdout);
				printf(
					"Oups, error during import from \"%s\" :-(\n\n",
					(*argv)[i + 1]);
				goto main_options_scan_err;
			} else {
				printf(
					"### Registers successfully imported from \"%s\" file. ###\n\n",
					(*argv)[i + 1]);
			}
			cpt += 2;
			ret++;
		} else if (strcmp((*argv)[i], "--force") == 0) {
			dprintf("%s(): found option \"--force\" at i=%u\n",
				__func__, i);
			if (i + 1 == *argc) {
				/* missing forced cpu name, abort */
				omapconf_revision_show(stdout);
				printf("Error, missing forced CPU name!\n\n");
				help(HELP_FORCEDETECT);
				goto main_options_scan_err;
			}
			/* Force detection of selected CPU */
			ret = cpu_force((*argv)[i + 1]);
			if (ret != 0) {
				omapconf_revision_show(stdout);
				printf(
					"\"%s\" CPU is not supported, see list of supported CPU below.\n\n",
					(*argv)[i + 1]);
				help(HELP_FORCEDETECT);
				goto main_options_scan_err;
			}
			cpu_found = 1;
			cpt += 2;
			ret++;
		} else if (strcmp((*argv)[i], "--norw") == 0) {
			dprintf("%s(): found option \"--norw\" at i=%u\n",
				__func__, i);
			/* Enable fake memory access debug mode */
			mem_fake_access_set(1);
			printf(
				"\n### FAKE MEMORY ACCESS DEBUG MODE ENABLED ###\n\n");
			cpt++;
			ret++;
		} else if (strcmp((*argv)[i], "--trace_read") == 0) {
			/* Trace all memory read access */
			mem_read_trace_enable(1);
			cpt++;
			ret++;
		} else if (strcmp((*argv)[i], "--trace_write") == 0) {
			/* Trace all memory write access */
			mem_write_trace_enable(1);
			cpt++;
			ret++;
		}
	}

	/* "Remove" arguments from argv */
	(*argc) -= cpt;
	(*argv) += cpt;
	goto main_options_scan_end;
main_options_scan_err:
	ret = OMAPCONF_ERR_ARG;
main_options_scan_end:
	dprintf("%s(): ret=%d\n", __func__, ret);
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main
 * @BRIEF		main entry point
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in, out]	argc: shell input argument number
 * @param[in, out]	argv: shell input argument(s)
 * @DESCRIPTION		main entry point
 *//*------------------------------------------------------------------------ */
int main(int argc, char *argv[])
{
	int ret;
	struct sigaction act;
	unsigned int start, end, time, delay;
	double sampling_rate;
	char *prefix;
	char *cfgfile;
	int c;

	cpu_found = 0;
	ret = 0;

	/* Register signal handler in order to catch incorrect memory access. */
	act.sa_sigaction = &main_sigbus_handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGBUS, &act, NULL);

	/* Some of the omapconf functions do not support DEVICE OFF Mode,
	 * so by default acquire a wakelock if OS is Android.
	 */
	if (os_supports_wakelock())
		wakelock_acquire();

	/* To be case-insensitive, lowercase all arguments */
	main_arguments_lowercase(argc, argv);

	/* Scan user arguments for options */
	argc--;
	argv++;
	ret = main_options_scan(&argc, &argv);
	if (ret < 0)
		goto main_exit;

	if (!cpu_is_forced()) {
		/* Detect CPU if not user-enforced */
		ret = cpu_detect();
		switch (ret) {
		case 0:
			cpu_found = 1;
			break;

		case OMAPCONF_ERR_REG_ACCESS:
			omapconf_revision_show(stdout);
			printf("'/dev/mem' could not be opened.\n");
			printf(
				"Privileged access required to run omapconf.\n\n");
			ret = OMAPCONF_ERR_REG_ACCESS;
			goto main_exit;

		case OMAPCONF_ERR_CPU:
			printf(
				"Warning: chip not recognized, running in safe mode (only platform-generic functions allowed).\n\n");
			break;

		case OMAPCONF_ERR_UNEXPECTED:
		default:
			omapconf_revision_show(stdout);
			printf("Unexpected error, sorry ... (%d)\n\n", ret);
			ret = OMAPCONF_ERR_UNEXPECTED;
			goto main_exit;
		}

	}

	if (argc == 0) {
		help(HELP_USAGE);
		ret = OMAPCONF_ERR_ARG;
		goto main_exit;
	}

	/* Platform-generic functions, no need to detect cpu */
	if (strcmp(argv[0], "--help") == 0) {
		omapconf_revision_show(stdout);
		help(HELP_ALL);
		ret = 0;
		goto main_exit;
	} else if (strcmp(argv[0], "--version") == 0) {
		omapconf_revision_show(stdout);
		ret = 0;
		goto main_exit;
	} else if (strcmp(argv[0], "--cpuinfo") == 0) {
		omapconf_revision_show(stdout);
		chips_info_show(stdout, 1);
		ret = 0;
		goto main_exit;
	} else if (strcmp(argv[0], "--buildinfo") == 0) {
		omapconf_revision_show(stdout);
		release_info_show(stdout);
		ret = 0;
		goto main_exit;
	} else if (strcmp(argv[0], "read") == 0) {
		if ((argc >= 2) &&
			(strcmp(argv[1], "audioic") == 0)) {
			goto main_platform_specific;
		} else if ((argc >= 2) &&
			(strcmp(argv[1], "i2c") == 0)) {
			if (argc < 5) {
				ret = err_arg_missing_msg_show(HELP_I2C_RW);
				goto main_exit;
			} else if (argc == 5) {
				ret = main_i2c_read(argc, argv);
				goto main_exit;
			} else {
				ret = err_arg_too_many_msg_show(HELP_I2C_RW);
				goto main_exit;
			}
		}

		if (argc == 2) {
			ret = main_readreg(uppercase(argv[1]), "hex");
			goto main_exit;
		} else if (argc == 3) {
			ret = main_readreg(uppercase(argv[1]),
				lowercase(argv[2]));
			goto main_exit;
		} else {
			ret = err_arg_too_many_msg_show(HELP_RW);
			goto main_exit;
		}
	} else if (strcmp(argv[0], "write") == 0) {
		if ((argc >= 2) &&
			(strcmp(argv[1], "audioic") == 0)) {
			goto main_platform_specific;
		} else if ((argc >= 2) &&
			(strcmp(argv[1], "i2c") == 0)) {
			if (argc < 6) {
				ret = err_arg_missing_msg_show(HELP_I2C_RW);
				goto main_exit;
			} else if (argc == 6) {
				ret = main_i2c_write(argc, argv);
				goto main_exit;
			} else {
				ret = err_arg_too_many_msg_show(HELP_I2C_RW);
				goto main_exit;
			}
		}

		if (argc < 3) {
			ret = err_arg_missing_msg_show(HELP_RW);
			goto main_exit;
		} else if (argc == 3) {
			ret = main_writereg(uppercase(argv[1]),
				uppercase(argv[2]));
			goto main_exit;
		} else {
			ret = err_arg_too_many_msg_show(HELP_RW);
			goto main_exit;
		}
	} else if (strcmp(argv[0], "clear") == 0) {
		if ((argc >= 2) && (strcmp(argv[1], "bit") == 0)) {
			ret = main_clearbit(argc, argv);
			goto main_exit;
		}
	} else if (strcmp(argv[0], "set") == 0) {
		if ((argc >= 2) && (strcmp(argv[1], "bit") == 0)) {
			ret = main_setbit(argc, argv);
			goto main_exit;
		}
	} else if (strcmp(argv[0], "i2c") == 0) {
		if ((argc != 5) && (argc != 6)) {
			help(HELP_I2C_RW);
			ret = OMAPCONF_ERR_ARG;
			goto main_exit;
		}
		if (strcmp(argv[1], "read") == 0) {
			ret = main_i2c_read(argc, argv);
			goto main_exit;
		} else if (strcmp(argv[1], "write") == 0) {
			ret = main_i2c_write(argc, argv);
			goto main_exit;
		} else {
			ret = err_arg_msg_show(HELP_I2C_RW);
			goto main_exit;
		}
	} else if ((strcmp(argv[0], "dump") == 0)
		&& (argc == 3)
		&& (sscanf(argv[1], "0x%08x", &start) == 1)
		&& (sscanf(argv[2], "0x%08x", &end) == 1)) {
		ret = mem_address_range_dump(start, end);
		goto main_exit;
	} else if ((argc >= 3) &&
		(strcmp(argv[0], "trace") == 0) &&
		(strcmp(argv[1], "perf") == 0) &&
		(strcmp(argv[2], "setup") == 0)) {
		if (argc == 3)
			ret = trace_perf_setup(
				(char *) trace_perf_default_cfgfile);
		else
			ret = trace_perf_setup(argv[3]);
		goto main_exit;
	} else if ((argc >= 2) &&
		(strcmp(argv[0], "trace") == 0) &&
		(strcmp(argv[1], "perf") == 0)) {
		time = TRACE_PERF_DEFAULT_CAPTURE_TIME;
		delay = TRACE_PERF_DEFAULT_DELAY_TIME;
		sampling_rate = TRACE_PERF_DEFAULT_SAMPLING_RATE;
		prefix = NULL;
		cfgfile = (char *) trace_perf_default_cfgfile;

		omapconf_revision_show(stdout);
		chips_info_show(stdout, 0);
		release_info_show(stdout);

		if (argc == 2) {
			time = TRACE_PERF_DEFAULT_CAPTURE_TIME;
			delay = TRACE_PERF_DEFAULT_DELAY_TIME;
			sampling_rate = TRACE_PERF_DEFAULT_SAMPLING_RATE;
			prefix = NULL;
			cfgfile = (char *) trace_perf_default_cfgfile;
		} else if (argc == 3) {
			ret = sscanf(argv[2], "%u", &time);
			if (ret != 1) {
				help(HELP_TRACE);
				ret = OMAPCONF_ERR_ARG;
				goto main_exit;
			}
		} else {
			while ((c = getopt(argc, argv, "d:t:s:p:c:")) != -1) {
				switch (c) {
				case 'd': /* delay time */
					ret = sscanf(optarg, "%u", &delay);
					if (ret != 1) {
						ret = err_arg_msg_show(
							HELP_TRACE);
						goto main_exit;
					}
					break;
				case 't': /* capture time */
					ret = sscanf(optarg, "%u", &time);
					if (ret != 1) {
						ret = err_arg_msg_show(
							HELP_TRACE);
						goto main_exit;
					}
					break;
				case 's': /* sampling rate */
					ret = sscanf(optarg, "%lf",
						&sampling_rate);
					if (ret != 1) {
						ret = err_arg_msg_show(
							HELP_TRACE);
						goto main_exit;
					}
					break;
				case 'p': /* file prefix */
					prefix = optarg;
					break;
				case 'c': /* configuration file */
					cfgfile = optarg;
					break;
				default:
					ret = err_arg_msg_show(HELP_TRACE);
					goto main_exit;
				}
			}
		}
		if (cpu_is_omap44xx())
			main44xx_init();
		else if (cpu_is_omap54xx())
			dpll54xx_init();
		ret = trace_perf_capture(cfgfile, prefix,
				sampling_rate, time, delay);
		goto main_exit;
	}


	/* Platform-specific functions */
main_platform_specific:
	if (cpu_found) {
		omapconf_revision_show(stdout);
		chips_info_show(stdout, 0);
		release_info_show(stdout);
		if (cpu_is_omap44xx()) {
			ret = main44xx(argc, argv);
			goto main_exit;
		} else if (cpu_is_omap54xx()) {
			ret = main54xx(argc, argv);
			goto main_exit;
		} else if (cpu_is_dra7xx()) {
			ret = main_dra7xx(argc, argv);
			goto main_exit;
		} else if (cpu_is_am335x()) {
			ret = main_am335x(argc, argv);
			goto main_exit;
		} else if (cpu_is_am437x()) {
			ret = main_am437x(argc, argv);
			goto main_exit;
		} else {
			printf("Unsupported chip, sorry ...\n\n");
			ret = OMAPCONF_ERR_CPU;
			goto main_exit;
		}
	} else {
		printf("Function disabled in safe mode, sorry ...\n\n");
		ret = OMAPCONF_ERR_NOT_AVAILABLE;
		goto main_exit;
	}

main_exit:
	if (os_supports_wakelock())
		wakelock_release();

	/* Unmap last mapped memory page */
	mem_unmap();

	/* Deinitializations */
	if (cpu_get() != OMAP_MAX) {
		opp_deinit();
		voltdm_deinit();
		temp_sensor_deinit();
		module_deinit();
		powerdm_deinit();
		clockdm_deinit();
	}

	return ret;
}
