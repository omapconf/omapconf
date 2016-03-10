/*
 *
 * @Component			OMAPCONF
 * @Filename			lib.c
 * @Description			Common Library for OMAPCONF
 * @Author			Patrick Titiano (p-titiano@ti.com)
 * @Date			2006
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2006 Texas Instruments Incorporated - http://www.ti.com/
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
#include <lib_android.h>
#include <lib44xx.h>
#include <lib_am335x.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <autoadjust_table.h>
#include <cpuinfo.h>
#include <stdlib.h>
#include <mem.h>
#include <cpuinfo.h>
#include <revision.h>
#include <pmic.h>
#include <twl6040.h>
#include <time.h>


/* #define OMAPCONF_BIN2STR_DEBUG */
/* #define OMAPCONF_NAME2ADDR_DEBUG */
/* #define OMAPCONF_DUMPREGS_DEBUG */
/* #define READREG_DEBUG */
/* #define WRITEREG_DEBUG */
/* #define OMAPCONF_GET_CRYSTAL_RATE_DEBUG */
/* #define OMAPCONF_GET_SYSTEM_CLOCK_SPEED_DEBUG */

/* #define LIB_DEBUG */
#ifdef LIB_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

#define PROC_VERSION_MAX_LENGTH		512

static const char workdirs[3][WORKDIR_MAX_NAME_LENGTH] = {
	"./",
	"/data/",
	"/tmp/"};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		os_supports_wakelock
 * @BRIEF		check if running OS supports wake_lock.
 * @RETURNS		1 if running OS supports wake_lock.
 *			0 if running OS does not support wake_lock.
 * @DESCRIPTION		check if running OS is Android.
 *//*------------------------------------------------------------------------ */
unsigned short os_supports_wakelock(void)
{
	FILE *fp = NULL;

	/*
	 * Try to open /sys/power/wake_lock file.
	 * If successfull, OS supports wake_lock
	 */
	fp = fopen("/sys/power/wake_lock", "r");
	if (fp == NULL) {
		return 0;
	} else {
		fclose(fp);
		return 1;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		omapconf_revision_show
 * @BRIEF		show omapconf revision
 * @RETURNS		none
 * @param[in]		stream: output file
 * @DESCRIPTION		show omapconf revision
 *//*------------------------------------------------------------------------ */
void omapconf_revision_show(FILE *stream)
{
	if (stream == NULL) {
		fprintf(stderr, "%s(): stream == NULL!!!\n", __func__);
		return;
	}

	fprintf(stream, "OMAPCONF (rev %s built %s)\n\n",
		 omapconf_version, builddate);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		linux_product_name_get
 * @BRIEF		retrieve the product name, parsing "/proc/cpuinfo".
 * @RETURNS		product name
 *			NULL if not found
 * @DESCRIPTION		retrieve the product name, parsing "/proc/cpuinfo".
 *//*------------------------------------------------------------------------ */
static char *linux_product_name_get(char product_name[256])
{
	FILE *fp = NULL;
	char line[256];
	char *pname;

	CHECK_NULL_ARG(product_name, NULL);
	if (os_is_android())
		return NULL;

	fp = fopen("/proc/cpuinfo", "r");
	if (fp == NULL) {
		fprintf(stderr,
			"omapconf: %s(): could not open '/proc/cpuinfo'?!\n",
			__func__);
		return NULL;
	}

	/* Retrieve pastry */
	while (fgets(line, 256, fp) != NULL) {
		/* Remove endind '\n' */
		line[strlen(line) - 1] = '\0';
		dprintf("%s(): line=%s len=%u\n", __func__, line, strlen(line));
		/* Looking for the "Hardware" property line */
		if (strstr(line, "Hardware") == NULL)
			continue;
		fclose(fp);
		dprintf("%s(): Hardware line found.\n", __func__);
		pname = strchr(line, ':');
		pname += 2 * sizeof(char);
		if (pname == NULL) {
			dprintf("%s(): '=' not found?!\n", __func__);
			return NULL;
		}
		strncpy(product_name, pname, 256);
		dprintf("%s(): product_name='%s'\n", __func__, product_name);
		return product_name;
	}

	fclose(fp);
	dprintf("%s(): eof reached!\n", __func__);
	return NULL;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		product_name_get
 * @BRIEF		retrieve the product name
 * @RETURNS		product name
 *			NULL if not found
 * @DESCRIPTION		retrieve the product name.
 *//*------------------------------------------------------------------------ */
char *product_name_get(char product_name[256])
{
	if (os_is_android())
		return android_product_name_get(product_name);
	else
		return linux_product_name_get(product_name);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		chips_info_show
 * @BRIEF		show chips revision (OMAP, PMIC, AUDIO IC)
 * @RETURNS		none
 * @param[in]		stream: output file
 *			die_id: select whether or not to show DIE ID
 * @DESCRIPTION		show chips revision (OMAP, PMIC, AUDIO IC)
 *//*------------------------------------------------------------------------ */
void chips_info_show(FILE *stream, unsigned short die_id)
{
	char name[CPU_NAME_MAX_LENGTH];
	char rev[CPU_REVISION_MAX_NAME_LENGTH];
	char type[CPU_DEVICE_TYPE_MAX_NAME_LENGTH];
	char si_type[CPU_SI_TYPE_MAX_NAME_LENGTH];
	char pkg_type[CPU_PKG_TYPE_MAX_NAME_LENGTH];
	float chip_rev;
	unsigned int max_speed;
	pmic_id pmic_chip[PMIC_SMPS_MAX_NUMBER];
	double pmic_chip_revision[PMIC_SMPS_MAX_NUMBER];
	double pmic_eprom_revision[PMIC_SMPS_MAX_NUMBER];
	unsigned int die_id_3, die_id_2, die_id_1, die_id_0;
	char s_die_id[CPU_DIE_ID_LENGTH];
	char product_name[256];

	if (stream == NULL) {
		fprintf(stderr, "%s(): stream == NULL!!!\n", __func__);
		return;
	}

	fprintf(stream, "HW Platform:\n");
	if (product_name_get(product_name) != NULL)
		fprintf(stream, "  %s\n", product_name);

	cpu_gets(name);
	if (strcmp(name, "UNKNOWN") != 0) {
		max_speed = cpu_silicon_max_speed_get();
		if (max_speed < 1000)
			fprintf(stream,
				"  %s ES%s %s Device (%s performance %s%s"
				"(%uMHz))\n",
				cpu_gets(name),
				cpu_revision_gets(rev),
				cpu_device_type_gets(type),
				cpu_silicon_type_gets(si_type),
				cpu_package_type_gets(pkg_type),
				(strlen(pkg_type) == 0) ? "" : " package ",
				max_speed);
		else
			fprintf(stream,
				"  %s ES%s %s Device (%s performance %s%s"
				"(%1.1lfGHz))\n",
				cpu_gets(name),
				cpu_revision_gets(rev),
				cpu_device_type_gets(type),
				cpu_silicon_type_gets(si_type),
				cpu_package_type_gets(pkg_type),
				(strlen(pkg_type) == 0) ? "" : " package ",
				(double) max_speed / 1000.0);
		if ((die_id != 0) && (cpu_die_id_get(&die_id_3, &die_id_2,
			&die_id_1, &die_id_0, s_die_id) != NULL))
			fprintf(stream, "    DIE ID: %s\n", s_die_id);
	} else {
		fprintf(stream, "  UNKNOWN CPU ARCHITECTURE\n");
	}

	pmic_chip[PMIC_SMPS_MPU] = pmic_chip_get(PMIC_SMPS_MPU);
	if (pmic_chip[PMIC_SMPS_MPU] == PMIC_ID_MAX) {
		goto pmic_detection_err;
	} else {
		pmic_chip_revision[PMIC_SMPS_MPU] =
			pmic_chip_revision_get(PMIC_SMPS_MPU);
		pmic_eprom_revision[PMIC_SMPS_MPU] =
			pmic_eprom_revision_get(PMIC_SMPS_MPU);
	}
	pmic_chip[PMIC_SMPS_MM] = pmic_chip_get(PMIC_SMPS_MM);
	if (pmic_chip[PMIC_SMPS_MM] == PMIC_ID_MAX) {
		goto pmic_detection_err;
	} else {
		pmic_chip_revision[PMIC_SMPS_MM] =
			pmic_chip_revision_get(PMIC_SMPS_MM);
		pmic_eprom_revision[PMIC_SMPS_MM] =
			pmic_eprom_revision_get(PMIC_SMPS_MM);
	}
	pmic_chip[PMIC_SMPS_CORE] = pmic_chip_get(PMIC_SMPS_CORE);
	if (pmic_chip[PMIC_SMPS_CORE] == PMIC_ID_MAX) {
		goto pmic_detection_err;
	} else {
		pmic_chip_revision[PMIC_SMPS_CORE] =
			pmic_chip_revision_get(PMIC_SMPS_CORE);
		pmic_eprom_revision[PMIC_SMPS_CORE] =
			pmic_eprom_revision_get(PMIC_SMPS_CORE);
	}

	if (pmic_chip_revision[PMIC_SMPS_MPU] >= 0.0)
		fprintf(stream, "  %s  ES%1.1f ",
			pmic_name_get(pmic_chip[PMIC_SMPS_MPU]),
			pmic_chip_revision[PMIC_SMPS_MPU]);
	else if (pmic_is_tps62361(PMIC_SMPS_MPU))
		fprintf(stream, "  %s",
			pmic_name_get(pmic_chip[PMIC_SMPS_MPU]));
	else
		fprintf(stream, "  %s  ES UNKNOWN ",
			pmic_name_get(pmic_chip[PMIC_SMPS_MPU]));

	if (pmic_eprom_revision[PMIC_SMPS_MPU] >= 0.0)
		fprintf(stream, "(EPROM rev%1.1f)\n",
			pmic_eprom_revision[PMIC_SMPS_MPU]);
	else if (pmic_is_tps62361(PMIC_SMPS_MPU) ||
		pmic_is_tps659038(PMIC_SMPS_MPU) ||
		pmic_is_tps65217x(PMIC_SMPS_MPU))
		fprintf(stream, "\n");
	else
		fprintf(stream, "(EPROM rev UNKNOWN)\n");

	if (!pmic_is_single_chip()) {
		if (pmic_chip_revision[PMIC_SMPS_CORE] >= 0.0)
			fprintf(stream, "  %s  ES%1.1f ",
				pmic_name_get(pmic_chip[PMIC_SMPS_CORE]),
				pmic_chip_revision[PMIC_SMPS_CORE]);
		else
			fprintf(stream, "  %s  ES UNKNOWN ",
				pmic_name_get(pmic_chip[PMIC_SMPS_CORE]));

		if (pmic_eprom_revision[PMIC_SMPS_CORE] >= 0.0)
			fprintf(stream, "(EPROM rev%1.1f)\n",
				pmic_eprom_revision[PMIC_SMPS_CORE]);
		else
			fprintf(stream, "(EPROM rev UNKNOWN)\n");
	}
	goto audioic_detect;

pmic_detection_err:
	fprintf(stream, "  UNKNOWN POWER IC\n");

audioic_detect:
	if (!cpu_is_dra7xx() && (strstr(product_name, "Kindle") == NULL)) {
		/* Kindle Fire products do not use Phoenix Audio.
		 * DRA7XX doesn't have McPDM so no Phoenix Audio either,
		 * tlv320aic3106 is used instead but there is no version reg
		 */
		chip_rev = twl6040_chip_revision_get();
		if (chip_rev >= 0.0)
			fprintf(stream, "  TWL6040  ES%1.1f\n\n", chip_rev);
		else
			fprintf(stream, "  UNKNOWN AUDIO IC\n\n");
	} else {
		fprintf(stream, "\n");
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		release_info_show
 * @BRIEF		show kernel and build version details
 * @RETURNS		none
 * @param[in]		stream: output file
 * @DESCRIPTION		show kernel and build version details
 *//*------------------------------------------------------------------------ */
void release_info_show(FILE *stream)
{
	char kversion[KERNEL_VERSION_MAX_LENGTH];
	char kauthor[KERNEL_AUTHOR_MAX_LENGTH];
	char ktoolchain[KERNEL_TOOLCHAIN_MAX_LENGTH];
	char ktype[KERNEL_TYPE_MAX_LENGTH];
	char kdate[KERNEL_DATE_MAX_LENGTH];
	char version[RELEASE_VERSION_MAX_LENGTH];
	char type[RELEASE_TYPE_MAX_LENGTH];
	char date[RELEASE_DATE_MAX_LENGTH];

	if (stream == NULL) {
		fprintf(stderr, "%s(): stream == NULL!!!\n", __func__);
		return;
	}

	fprintf(stream, "SW Build Details:\n");

	fprintf(stream, "  Build:\n");
	if (release_details_get(version, type, date) != NULL) {
		fprintf(stream, "    Version: %s\n", version);
		if (os_is_android()) {
			fprintf(stream, "    Pastry: %s\n",
				android_pastry_name_get(android_pastry_get()));
			fprintf(stream, "    Type: %s\n", type);
			fprintf(stream, "    Date: %s\n\n", date);
		}
	} else {
		fprintf(stream, "    Version: unknown\n");
	}

	fprintf(stream, "  Kernel:\n");
	if (kernel_details_get(kversion, kauthor, ktoolchain, ktype, kdate)
		!= NULL) {
		fprintf(stream, "    Version: %s\n", kversion);
		fprintf(stream, "    Author: %s\n", kauthor);
		fprintf(stream, "    Toolchain: %s\n", ktoolchain);
		fprintf(stream, "    Type: %s\n", ktype);
		fprintf(stream, "    Date: %s\n\n", kdate);
	} else {
		fprintf(stream, "    Version: unknown\n");
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		date_get
 * @BRIEF		format current date and time into string.
 * @RETURNS		formatted string pointer in case of success
 *			NULL otherwise
 * @param[in,out]	s: pre-allocated string where to store date and time
 * @DESCRIPTION		format current date and time into string.
 *//*------------------------------------------------------------------------ */
char *date_get(char s[17])
{
	time_t t;
	struct tm *tmp;

	CHECK_NULL_ARG(s, NULL);

	t = time(NULL);
	tmp = localtime(&t);
	if (tmp != NULL)
		strftime(s, 17, "%Y%m%d_%H%M%S_", tmp);
	else
		strncpy(s, "19700101_000000_", strlen(s));
	dprintf("%s(): current date is %s\n", __func__, s);

	return s;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		lowercase
 * @BRIEF		convert all string characters to lowercase
 * @RETURNS		the converted string
 * @param[in, out]	s: the string to be converted
 * @DESCRIPTION		convert all string characters to lowercase
 *//*------------------------------------------------------------------------ */
char *lowercase(char *s)
{
	unsigned int  i = 0;

	while (s[i]) {
		s[i] = tolower(s[i]);
		i++;
	}

	return (char *) s;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		uppercase
 * @BRIEF		convert all string characters to uppercase
 * @RETURNS		the converted string
 * @param[in, out]	s: the string to be converted
 * @DESCRIPTION		convert all string characters to uppercase
 *//*------------------------------------------------------------------------ */
char *uppercase(char *s)
{
	unsigned int  i = 0;

	while (s[i]) {
		s[i] = toupper(s[i]);
		i++;
	}

	return (char *) s;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		bin2str_32
 * @BRIEF		Convert 32-bit integer value to binary (string)
 * @RETURNS		string pointer
 * @param[in, out]	s: string where binary value is stored
 *			(must be pre-allocated)
 * @param[in]		value: 32-bit integer to be coverted
 * @DESCRIPTION		Convert 32-bit integer value to binary (string)
 *//*------------------------------------------------------------------------ */
char *bin2str_32(char s[33], unsigned int value)
{
	unsigned int i, mask;

	for (i = 0; i < 32; i++) {
		mask = 1 << i;
		value = value & mask;
		if (value == mask)
			s[31 - i] = '1';
		else
			s[31 - i] = '0';
	}
	s[32] = '\0';

	#ifdef OMAPCONF_BIN2STR_DEBUG
	printf("bin2str(%8x) = %s\n", value, s);
	#endif

	return s;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		extract_bit
 * @BRIEF		extract bit value from register, given position
 * @RETURNS		bitfield value on success (>=0)
 *			OMAPCONF_ERR_ARG
 * @param[in]		regVal: register content to extract from
 * @param[in]		pos: bit position in register
 * @DESCRIPTION		extract bit value from register, given position
 *//*------------------------------------------------------------------------ */
inline short int extract_bit(unsigned int regVal, unsigned short pos)
{
	if (pos > 31)
		return OMAPCONF_ERR_ARG;
	else
		return (regVal & (1 << pos)) >> pos;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		extract_bitfield
 * @BRIEF		extract bitfield value from register, given position and
 *			length.
 * @RETURNS		bitfield value on success (>=0)
 *			OMAPCONF_ERR_ARG
 * @param[in]		regVal: register content to extract from
 * @param[in]		start: bitfield LSB
 * @param[in]		len: bitfield length
 * @DESCRIPTION		extract bitfield value from register, given position and
 *			length.
 *//*------------------------------------------------------------------------ */
inline int extract_bitfield(unsigned int regVal, unsigned short start,
	unsigned short len)
{
	if (len == 0)
		return OMAPCONF_ERR_ARG;
	else if ((start >= 32) || (len > 32))
		return OMAPCONF_ERR_ARG;
	else if (start + len > 32)
		return OMAPCONF_ERR_ARG;
	else
		return (regVal & (((1 << len) - 1) << start)) >> start;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		count64_delta
 * @BRIEF		return the difference between 2 64-bit values,
 *			considering it's collected from timer/counter and it may
 *			have wrapped around.
 *			CAUTION: DO NOT USE WITH DATA SIZE OTHER THAN 64-BIT,
 *			OR MAY RETURN ERRONEOUS RESULT.
 * @RETURNS		difference between 2 64-bit values, considering
 *			potential wrap around
 * @param[in]		a: 1st sample from timer/counter
 * @param[in]		b: 2nd sample from timer/counter
 * @DESCRIPTION		return the difference between 2 64-bit values,
 *			considering it's collected from timer/counter and it may
 *			have wrapped around.
 *			CAUTION: DO NOT USE WITH DATA SIZE OTHER THAN 64-BIT,
 *			OR MAY RETURN ERRONEOUS RESULT.
 *//*------------------------------------------------------------------------ */
uint64_t count64_delta(uint64_t a, uint64_t b)
{
	if (b >= a) {
		return b - a;
	} else {
		dprintf("%s(%llu, %llu): b < a\n", __func__, a, b);
		return 1 + (UINT64_MAX - a) + b;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		max
 * @BRIEF		return the greatest of the 2 given 64-bit arguments
 * @RETURNS		the greatest of the 2 given arguments
 * @param[in]		a: an integer
 * @param[in]		b: a 2nd integer
 * @DESCRIPTION		return the greatest of the 2 given 64-bit arguments
 *//*------------------------------------------------------------------------ */
uint64_t max(uint64_t a, uint64_t b)
{
	if (b >= a)
		return b;
	else
		return a;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		count32_delta
 * @BRIEF		return the difference between 2 32-bit values,
 *			considering it's collected from timer/counter and it
 *			may have wrapped around.  (32-bit).
 *			CAUTION: DO NOT USE WITH DATA SIZE OTHER THAN 32-BIT, OR
 *			MAY RETURN ERRONEOUS RESULT.
 * @RETURNS		difference between 2 32-bit values, considering
 *			potential wrap around
 * @param[in]		a: 1st sample from timer/counter
 * @param[in]		b: 2nd sample from timer/counter
 * @DESCRIPTION		return the difference between 2 32-bit values,
 *			considering it's collected from timer/counter and it
 *			may have wrapped around.  (32-bit).
 *			CAUTION: DO NOT USE WITH DATA SIZE OTHER THAN 32-BIT, OR
 *			MAY RETURN ERRONEOUS RESULT.
 *//*------------------------------------------------------------------------ */
unsigned int count32_delta(unsigned int a, unsigned int b)
{
	if (b >= a) {
		return b - a;
	} else {
		dprintf("%s(%u, %u): b < a\n", __func__, a, b);
		return 1 + (0xFFFFFFFF - a) + b;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		max32
 * @BRIEF		return the greatest of the 2 given arguments
 *			(32-bit unsigned).
 * @RETURNS		the greatest of the 2 given arguments.
 * @param[in]		a: a 32-bit unsigned integer
 *			b: a 2nd 32-bit unsigned integer
 * @DESCRIPTION		return the smallest of the 2 given arguments
 *			(32-bit unsigned).
 *//*------------------------------------------------------------------------ */
unsigned int max32(unsigned int a, unsigned int b)
{
	if (b >= a)
		return b;
	else
		return a;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		max32s
 * @BRIEF		return the greatest of the 2 given arguments
 *			(32-bit signed).
 * @RETURNS		the greatest of the 2 given arguments.
 * @param[in]		a: a 32-bit signed integer
 *			b: a 2nd 32-bit signed integer
 * @DESCRIPTION		return the greatest of the 2 given arguments
 *			(32-bit signed).
 *//*------------------------------------------------------------------------ */
int max32s(int a, int b)
{
	if (b >= a)
		return b;
	else
		return a;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		min32
 * @BRIEF		return the smallest of the 2 given arguments
 *			(32-bit unsigned).
 * @RETURNS		the smallest of the 2 given arguments.
 * @param[in]		a: a 32-bit unsigned integer
 *			b: a 2nd 32-bit unsigned integer
 * @DESCRIPTION		return the smallest of the 2 given arguments
 *			(32-bit unsigned).
 *//*------------------------------------------------------------------------ */
unsigned int min32(unsigned int a, unsigned int b)
{
	if (b >= a)
		return a;
	else
		return b;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		min32s
 * @BRIEF		return the smallest of the 2 given arguments
 *			(32-bit signed).
 * @RETURNS		the smallest of the 2 given arguments.
 * @param[in]		a: a 32-bit integer
 *			b: a 2nd 32-bit integer
 * @DESCRIPTION		return the smallest of the 2 given arguments
 *			(32-bit signed).
 *//*------------------------------------------------------------------------ */
int min32s(int a, int b)
{
	if (b >= a)
		return a;
	else
		return b;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		avg_recalc
 * @BRIEF		re-compute average based on previous avg and new data.
 * @RETURNS		new average value based on previous avg and new data.
 * @param[in]		prev_avg: previous average
 * @param[in]		new_val: new data to be averaged with prev_avg
 * @param[in]		n: data count
 * @DESCRIPTION		re-compute average based on previous avg and new data.
 *//*------------------------------------------------------------------------ */
double avg_recalc(double prev_avg, double new_val, unsigned int n)
{
	double avg;
	avg = (prev_avg * (double) n) + new_val;
	avg /= (double) (n + 1);

	dprintf("%s(prev_avg=%lf, new_val=%lf, n=%u) = %lf\n", __func__,
		prev_avg, new_val, n, avg);
	return avg;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mhz2string
 * @BRIEF		format clock rate in MHz into a string.
 *			if rate < 1MHz, keep all decimals.
 *			if rate >= 1Mhz, keep only 3 decimals.
 * @RETURNS		clock rate formated as a string
 * @param[in]		rate: a clock rate
 * @param[in, out]	s: rate formatted as a string
 * @DESCRIPTION		format clock rate in MHz into a string.
 *			if rate < 1MHz, keep all decimals.
 *			if rate >= 1Mhz, keep only 3 decimals.
 *//*------------------------------------------------------------------------ */
char *mhz2string(double rate, char s[15])
{
	CHECK_NULL_ARG(s, NULL);

	if (rate <= -1.0)
		snprintf(s, 15, "%.3lf", rate);
	else if ((rate > -1.0) && (rate < 1.0))
		snprintf(s, 15, "%lf", rate);
	else
		snprintf(s, 15, "%.3lf", rate);

	return s;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		workdir_get
 * @BRIEF		find a writable directory where to store output file(s).
 * @RETURNS		writable working directory
 *			NULL if not found
 * @DESCRIPTION		find a writable directory where to store output file(s).
 *//*------------------------------------------------------------------------ */
char *workdir_get(void)
{
	FILE *fp = NULL;
	static char *found_working_dir;
	static short first_time = 1;
	char test_filename[32];
	unsigned int i;

	if (!first_time)
		return (char *) found_working_dir;
	first_time = 0;

	for (i = 0; i < 3; i++) {
		strcpy(test_filename, workdirs[i]);
		strcat(test_filename, "./test_fs_writable");
		dprintf("%s(): test_filename = %s\n", __func__, test_filename);
		fp = fopen(test_filename, "w");
		if (fp != NULL) {
			/* Current directory is writable */
			fclose(fp);
			remove(test_filename);
			found_working_dir = (char *) workdirs[i];
			dprintf("%s(): found %s is writable\n",
				__func__, found_working_dir);
			return (char *) found_working_dir;
		} else {
			dprintf("%s(): %s is not writable\n",
				__func__, found_working_dir);
		}
	}
	/* Reaching this point means no writable directory found */
	found_working_dir = NULL;
	fprintf(stderr, "No writable directory found!\n");
	return (char *) found_working_dir;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		workdir_fopen
 * @BRIEF		depending on platform (generic linux, android, eMMC
 *			boot, SD boot, etc) current directory may not be
 *			writable. If one needs to open a writable file, use this
 *			function to first look for a writable directory and then
 *			open file in this directory. In case file is open for
 *			read only, no change to regular fopen().
 * @RETURNS		FILE pointer corresponding to the opened file in
 *			working directory.
 *			NULL if no writable working directory found, or
 *			file could no be opened.
 * @param[in, out]	filename: string containing the name of the file to be
 *			opened (MUST BE WITHOUT ANY PATH)
 * @param[in, out]	mode: string containing a file access mode
 * @DESCRIPTION		depending on platform (generic linux, android, eMMC
 *			boot, SD boot, etc) current directory may not be
 *			writable. If one needs to open a writable file, use this
 *			function to first look for a writable directory and then
 *			open file in this directory. In case file is open for
 *			read only, no change to regular fopen().
 *//*------------------------------------------------------------------------ */
FILE *workdir_fopen(char filename[128], const char *mode)
{
	char *workdir;
	char fullname[128];

	if (strcmp(mode, "r") == 0)
		return fopen(filename, mode);
	else if (strcmp(mode, "r+") == 0)
		return fopen(filename, mode);

	/* Get working directory */
	workdir = workdir_get();
	if (workdir == NULL)
		return NULL;

	/* Concatenate filename to workdir */
	strcpy(fullname, workdir);
	strcat(fullname, filename);

	/* Save filename including full path */
	strcpy(filename, fullname);

	/* Open file in working directory */
	return fopen(fullname, mode);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		kernel_details_get
 * @BRIEF		retrieve kernel details (version, author, toolchain,
 *			type, date) from "/proc/version" and copy it into
 *			dedicated strings.
 * @RETURNS		requested kernel details in dedicated strings
 *			NULL in case of error
 * @param[in, out]	version: pre-allocated string of length
 *			KERNEL_VERSION_MAX_LENGTH
 * @param[in, out]	author: pre-allocated string of length
 *			KERNEL_AUTHOR_MAX_LENGTH
 * @param[in, out]	toolchain: pre-allocated string of length
 *			KERNEL_TOOLCHAIN_MAX_LENGTH
 * @param[in, out]	type: pre-allocated string of length
 *			KERNEL_TYPE_MAX_LENGTH
 * @param[in, out]	date: pre-allocated string of length
 *			KERNEL_DATE_MAX_LENGTH
 * @DESCRIPTION		retrieve kernel details (version, author, toolchain,
 *			type, date) from "/proc/version" and copy it into
 *			dedicated strings.
 *//*------------------------------------------------------------------------ */
char *kernel_details_get(char version[KERNEL_VERSION_MAX_LENGTH],
			char author[KERNEL_AUTHOR_MAX_LENGTH],
			char toolchain[KERNEL_TOOLCHAIN_MAX_LENGTH],
			char type[KERNEL_TYPE_MAX_LENGTH],
			char date[KERNEL_DATE_MAX_LENGTH])
{
	FILE *fp = NULL;
	char s[PROC_VERSION_MAX_LENGTH];
	char *str, *pch;
	unsigned short int day, num;
	static const char week[7][4] = {
		"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

	CHECK_NULL_ARG(version, NULL);
	CHECK_NULL_ARG(author, NULL);
	CHECK_NULL_ARG(toolchain, NULL);
	CHECK_NULL_ARG(type, NULL);
	CHECK_NULL_ARG(date, NULL);

	strcpy(version, "UNKNOWN");
	strcpy(author, "UNKNOWN");
	strcpy(toolchain, "UNKNOWN");
	strcpy(type, "UNKNOWN");
	strcpy(date, "UNKNOWN");

	fp = fopen("/proc/version", "r");
	if (fp == NULL) {
		fprintf(stderr, "%s(): could not open /proc/version file?!\n",
			__func__);
		goto kernel_info_get_end;
	}
	if (fgets(s, PROC_VERSION_MAX_LENGTH, fp) == NULL) {
		fprintf(stderr, "%s(): error reading /proc/version file?!\n",
			__func__);
		goto kernel_info_get_end;
	}
	/* Remove endind '\n' */
	s[strlen(s) - 1] = '\0';
	dprintf("%s(): s=%s len=%u\n", __func__, s, strlen(s));

	/* kernel version is of following format:
	 * Linux version "version" ("author") ("toolchain" ) "type" "date"
	 */
	/* Skip first 14 characters ("Linux version ") */
	str = s  + 14 * sizeof(char);
	dprintf("%s(): str=%s len=%u\n", __func__, str, strlen(str));
	/* Extract kernel version (all characters until " (") */
	num = strcspn(str, " (");
	strncpy(version, str, num);
	version[num] = '\0';
	dprintf("%s(): version=%s\n", __func__, version);
	str += (num + 2) * sizeof(char);
	dprintf("%s(): str=%s\n", __func__, str);
	/* Extract kernel author (all characters until ") (") */
	num = strcspn(str, ") (");
	strncpy(author, str, num);
	author[num] = '\0';
	dprintf("%s(): author=%s\n", __func__, author);
	str += (num + 3) * sizeof(char);
	dprintf("%s(): str=%s\n", __func__, str);
	/* Extract kernel toolchain (all characters until "#") */
	num = strcspn(str, "#");
	strncpy(toolchain, str, num - 3);
	toolchain[num - 3] = '\0';
	dprintf("%s(): toolchain=%s\n", __func__, toolchain);
	str += num * sizeof(char);
	dprintf("%s(): str=%s\n", __func__, str);
	/* Extract kernel type (all characters until day abreviation) */
	for (day = 0; day < 7; day++) {
		pch = strstr(str, week[day]);
		if (pch != NULL) {
			strncpy(type, str, (pch - str) * sizeof(char));
			type[pch - str - 1] = '\0';
			dprintf("%s(): type=%s\n", __func__, type);
			str = pch;
			break;
		}
	}
	if (day == 7) {
		fprintf(stderr, "%s(): could not find type!!!\n", __func__);
		goto kernel_info_get_end;
	}
	/* Extract kernel date (remaining part of str) */
	strcpy(date, str);
	dprintf("%s(): date=%s\n", __func__, date);

kernel_info_get_end:
	if (fp != NULL)
		fclose(fp);
	return version;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		release_version_get
 * @BRIEF		retrieve release details (version, type, date) from
 *			either "/etc/issue.net" (Linux) or
 *			"/system/build.prop" (Android) and copy it into
 *			dedicated strings.
 * @RETURNS		requested release details in dedicated strings
 *			NULL in case of error
 * @param[in, out]	version: pre-allocated string of length
 *			RELEASE_VERSION_MAX_LENGTH
 * @param[in, out]	type: pre-allocated string of length
 *			RELEASE_TYPE_MAX_LENGTH
 * @param[in, out]	date: pre-allocated string of length
 *			RELEASE_DATE_MAX_LENGTH
 * @DESCRIPTION		retrieve release details (version, type, date) from
 *			either "/etc/issue.net" (Linux) or
 *			"/system/build.prop" (Android) and copy it into
 *			dedicated strings.
 *//*------------------------------------------------------------------------ */
char *release_details_get(char version[RELEASE_VERSION_MAX_LENGTH],
			char type[RELEASE_TYPE_MAX_LENGTH],
			char date[RELEASE_DATE_MAX_LENGTH])
{
	FILE *fp = NULL;
	static const char version_file_linux[] = "/etc/issue.net";
	static const char version_file_android[] = "/system/build.prop";
	char *version_file = NULL;
	char line[256];

	CHECK_NULL_ARG(version, NULL);
	CHECK_NULL_ARG(type, NULL);
	CHECK_NULL_ARG(date, NULL);

	strcpy(version, "UNKNOWN");
	strcpy(type, "UNKNOWN");
	strcpy(date, "UNKNOWN");

	if (os_is_android())
		version_file = (char *) version_file_android;
	else
		version_file = (char *) version_file_linux;

	fp = fopen(version_file, "r");
	if (fp == NULL) {
		fprintf(stderr, "%s(): could not open %s file?!\n",
			__func__, version_file);
		goto release_details_get_end;
	}

	if (os_is_android()) {
		dprintf("%s(): parsing %s...\n", __func__, version_file);
		/* Retrieve date */
		while (fgets(line, 256, fp) != NULL) {
			/* Remove endind '\n' */
			line[strlen(line) - 1] = '\0';
			dprintf("line=%s len=%u\n", line, strlen(line));
			/* Looking for line containing date in file */
			if (strstr(line, "ro.build.date=") == NULL)
				continue;

			dprintf("ro.build.date line found\n");
			strncpy(date,
				line + strlen("ro.build.date=") * sizeof(char),
				RELEASE_DATE_MAX_LENGTH);
			dprintf("%s(): date=%s\n", __func__, date);
			break;
		}

		/* Retrieve type */
		rewind(fp);
		while (fgets(line, 256, fp) != NULL) {
			/* Remove endind '\n' */
			line[strlen(line) - 1] = '\0';
			dprintf("line=%s len=%u\n", line, strlen(line));
			/* Looking for line containing type in file */
			if (strstr(line, "ro.build.type=") == NULL)
				continue;

			dprintf("ro.build.type line found\n");
			strncpy(type,
				line + strlen("ro.build.type=") * sizeof(char),
				RELEASE_TYPE_MAX_LENGTH);
			dprintf("%s(): type=%s\n", __func__, type);
			break;
		}

		/* Retrieve version */
		rewind(fp);
		while (fgets(line, 256, fp) != NULL) {
			/* Remove endind '\n' */
			line[strlen(line) - 1] = '\0';
			dprintf("line=%s len=%u\n", line, strlen(line));
			/* Looking for line containing version in file */
			if (strstr(line, "ro.build.description=") == NULL)
				continue;

			dprintf("ro.build.description line found\n");
			strncpy(version,
				line +
				strlen("ro.build.description=") * sizeof(char),
				RELEASE_TYPE_MAX_LENGTH);
			dprintf("%s(): version=%s\n", __func__, version);
			break;
		}
	} else {
		if (fgets(version, RELEASE_VERSION_MAX_LENGTH, fp) == NULL) {
			fprintf(stderr, "%s(): error reading %s file?!\n",
				__func__, version_file);
			goto release_details_get_end;
		}
		/* Remove endind '\n' */
		version[strlen(version) - 1] = '\0';
		dprintf("%s(): version=%s len=%u\n", __func__,
			version, strlen(version));
	}

release_details_get_end:
	if (fp != NULL)
		fclose(fp);
	return version;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		name2addr
 * @BRIEF		convert register name to address.
 * @RETURNS		0 on success
 *			-1 if address not found
 * @param[in]		name: register name
 * @param[in, out]	addr: register address
 * @param[in]		table: table with list of registers name & address
 * @DESCRIPTION		convert register name to address.
 *//*------------------------------------------------------------------------ */
int name2addr(char *name, unsigned int *addr, reg_table table[])
{
	unsigned int i = 0;

	#ifdef OMAPCONF_NAME2ADDR_DEBUG
	printf("%s(): name = %s\n", __func__, name);
	#endif

	do {
		if (strcmp(table[i].name, name) == 0) {
			/* register name found */
			*addr = table[i].addr;
			#ifdef OMAPCONF_NAME2ADDR_DEBUG
			printf("%s(): Address(%s) = 0x%x\n", __func__,
				name, (*addr));
			#endif
			return 0;
		}
		i++;
	} while (strcmp(table[i].name, "END") != 0);

	/* Register name not found */
	#ifdef OMAPCONF_NAME2ADDR_DEBUG
	printf("%s(): register name not found! (%s)\n", __func__, name);
	#endif

	return -1;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		find_reg_addr
 * @BRIEF		find reg. addr corresponding to reg. name
 * @RETURNS		0 on success
 *			-1 if reg. addr. not found
 *			OMAPCONF_ERR_CPU
 * @param[in]		name: register name.
 * @param[in, out]	addr: register address corresponding to reg. name.
 * @DESCRIPTION		find reg. addr corresponding to reg. name
 *//*------------------------------------------------------------------------ */
int find_reg_addr(char *name, unsigned int *addr)
{
	int ret = 0;

	#ifdef OMAPCONF_FIND_REG_ADDR_DEBUG
	printf("%s(): looking for addr of register %s...\n", __func__, name);
	#endif

	if (cpu_is_omap44xx()) {
		ret = reg44xx_addr_find(name, addr);
	} else if (cpu_is_am335x()) {
		ret = reg_am335x_addr_find(name, addr);
	}else {
		printf("%s(): unsupported chip!\n\n", __func__);
		ret = OMAPCONF_ERR_CPU;
	}

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dumpregs
 * @BRIEF		dump registers from table given as argument.
 *			Display registers in a table with name, address and
 *			value.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		table: table with list of registers to display.
 *			Must be terminated with table field name == "END".
 * @DESCRIPTION		dump registers from table given as argument.
 *//*------------------------------------------------------------------------ */
int dumpregs(reg_table table[])
{
	unsigned int i = 0;
	unsigned int ret, val = 0;
	int err = 0;
	char autoadjust_table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row;

	autoadjust_table_init(autoadjust_table);
	row = 0;

	strncpy(autoadjust_table[row][0], "Reg. Name", TABLE_MAX_ELT_LEN);
	strncpy(autoadjust_table[row][1], "Reg. Addr",
		TABLE_MAX_ELT_LEN);
	strncpy(autoadjust_table[row][2], "Reg. Val.", TABLE_MAX_ELT_LEN);
	row++;

	while (strcmp(table[i].name, "END") != 0) {
		ret = mem_read(table[i].addr, &val);
		if (ret == 0) {
			/* Show register name, addr & content (hex) */
			snprintf(autoadjust_table[row][0], TABLE_MAX_ELT_LEN,
				"%s", table[i].name);
			snprintf(autoadjust_table[row][1], TABLE_MAX_ELT_LEN,
				"0x%08X", table[i].addr);
			snprintf(autoadjust_table[row][2], TABLE_MAX_ELT_LEN,
				"0x%08X", val);
			row++;
		} else {
			printf("%s(): read error! (addr=0x%08X, err=%d)\n",
				__func__, table[i].addr, ret);
			err = OMAPCONF_ERR_REG_ACCESS;
			break;
		}
		i++;
	}

	autoadjust_table_print(autoadjust_table, row, 3);

	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mem_address_range_dump
 * @BRIEF		dump user-selected range of contiguous physical memory.
 *			addresses
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 * @param[in]		start: physical start address (!= 0)
 * @param[in]		end: physical end address (!= 0)
 * @DESCRIPTION		dump user-selected range of contiguous physical memory.
 *//*------------------------------------------------------------------------ */
int mem_address_range_dump(unsigned int start, unsigned int end)
{
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row = 0;
	unsigned int addr, data;
	int ret;

	if (start == 0) {
		printf("ERROR: <start address> should not be 0!\n");
		return OMAPCONF_ERR_ARG;
	}
	if (end == 0) {
		printf("ERROR: <end address> should not be 0!\n");
		return OMAPCONF_ERR_ARG;
	}
	if (end <= start) {
		printf("ERROR: <end address> should be > <end address>!\n");
		return OMAPCONF_ERR_ARG;
	}

	autoadjust_table_init(table);
	row = 0;
	strncpy(table[row][0], "Address (hex)", TABLE_MAX_ELT_LEN);
	strncpy(table[row][1], "Data (hex)", TABLE_MAX_ELT_LEN);
	row++;

	for (addr = start; addr <= end; addr += 4) {
		ret = mem_read(addr, &data);
		if (ret != 0)
			printf("Read error at 0x%08X!\n", addr);
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "0x%08X", addr);
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "0x%08X", data);
		row++;
	}

	autoadjust_table_print(table, row, 2);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		name2value
 * @BRIEF		Convert a named table entry to its value. If there are
 *			multiple matches, returns the first.
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_NOT_AVAILABLE if address not found
 * @param[in]		name: Character string (max 64)
 * @param[in, out]	value: Integer value of matching string in table.
 * @param[in]		table: name_desc_val_table type of table.
 * @DESCRIPTION		Convert a named table entry to its value. If there are
 *			multiple matches, returns the first.
 *//*------------------------------------------------------------------------ */
int name2value(
	char *name, unsigned int *value, const name_desc_val_table table[])
{
	unsigned int i = 0;

	#ifdef OMAPCONF_NAME2ADDR_DEBUG
	printf("name2value(): name = %s\n", name);
	#endif

	do {
		if (strcmp(table[i].name, name) == 0) {
			/* register name found */
			*value = table[i].value;
			#ifdef OMAPCONF_NAME2ADDR_DEBUG
			printf("name2value(): Name %s indexes Value 0x%x\n",
				name, (*value));
			#endif
			return 0;
		}
		i++;
	} while (strcmp(table[i].name, "END") != 0);

	/* Register name not found */
	#ifdef OMAPCONF_NAME2ADDR_DEBUG
	printf("name2value(): name not found! (%s)\n", name);
	#endif

	return OMAPCONF_ERR_NOT_AVAILABLE;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		name2vindex
 * @BRIEF		Convert a named table entry to its index. If there are
 *			multiple matches, returns the first.
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_NOT_AVAILABLE if address not found
 * @param[in]		name: Character string (max 64)
 * @param[in, out]	index: Index of matching string in table.
 * @param[in]		table: name_desc_val_table type of table.
 * @DESCRIPTION		Convert a named table entry to its index. If there are
 *			multiple matches, returns the first.
 *//*------------------------------------------------------------------------ */
int name2index(
	char *name, unsigned int *index, const name_desc_val_table table[])
{
	unsigned int i = 0;

	#ifdef OMAPCONF_NAME2ADDR_DEBUG
	printf("name2value(): name = %s\n", name);
	#endif

	do {
		if (strcmp(table[i].name, name) == 0) {
			/* register name found */
			*index = i;
			#ifdef OMAPCONF_NAME2ADDR_DEBUG
			printf("name2value(): Name %s index is 0x%x\n",
				name, (*index));
			#endif
			return 0;
		}
		i++;
	} while (strcmp(table[i].name, "END") != 0);

	/* Register name not found */
	#ifdef OMAPCONF_NAME2ADDR_DEBUG
	printf("name2value(): name not found! (%s)\n", name);
	#endif

	return OMAPCONF_ERR_NOT_AVAILABLE;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		value2name
 * @BRIEF		Convert a value table entry to its name. If there are
 *			multiple matches, returns the first.
 * @RETURNS		0 on success
 *			-1 if address not found
 * @param[in]		value: Integer value of matching string in table.
 * @param[in, out]	name: Character string (max 64)
 * @param[in]		table: name_desc_val_table type of table.
 * @DESCRIPTION		Convert a value table entry to its name. If there are
 *			multiple matches, returns the first.
 *//*------------------------------------------------------------------------ */
int value2name(
	unsigned int value, char *name, const name_desc_val_table table[])
{
	unsigned int i = 0;

	#ifdef OMAPCONF_NAME2ADDR_DEBUG
	printf("value2name(): value = 0x%x\n", value);
	#endif

	do {
		if (table[i].value == value) {
			/* register name found */
			strcpy(name, table[i].name);
			#ifdef OMAPCONF_NAME2ADDR_DEBUG
			printf("value2name(): Value 0x%x indexes Name %s\n",
				 (value), name);
			#endif
			return 0;
		}
		i++;
	} while (strcmp(table[i].name, "END") != 0);


	/* Register name not found */
	#ifdef OMAPCONF_NAME2ADDR_DEBUG
	printf("value2name(): name not found! (%s)\n", name);
	#endif

	return -1;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		name2desc
 * @BRIEF		Convert a value of a table entry to its description
 *			text. If there are multiple matches, returns the first.
 * @RETURNS		0 on success
 *			-1 if address not found
 * @param[in]		value: unsigned int
 * @param[in, out]	desc: Character string (max 128) description of matching
 *			string.
 * @param[in]		table: name_desc_val_table type of table.
 * @DESCRIPTION		Convert a value of a table entry to its description
 *			text. If there are multiple matches, returns the first.
 *//*------------------------------------------------------------------------ */
int value2desc(
	unsigned int value, char *desc, const name_desc_val_table table[])
{
	unsigned int i = 0;

	#ifdef OMAPCONF_NAME2ADDR_DEBUG
	printf("value2desc(): value = 0x%x\n", value);
	#endif

	do {
		if (table[i].value == value) {
			/* register name found */
			strcpy(desc, table[i].desc);
			#ifdef OMAPCONF_NAME2ADDR_DEBUG
			printf("value2name(): Value 0x%x indexes Desc %s\n",
				 (value), desc);
			#endif
			return 0;
		}
		i++;
	} while (strcmp(table[i].name, "END") != 0);


	/* Register name not found */
	#ifdef OMAPCONF_NAME2ADDR_DEBUG
	printf("value2desc(): value not found! (%s)\n", desc);
	#endif

	return -1;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		name2value
 * @BRIEF		Convert a named table entry to its value. If there are
 *			multiple matches, returns the first.
 * @RETURNS		0 on success
 *			-1 if address not found
 * @param[in]		name: Character string (max 64)
 * @param[in, out]	value: Integer value of matching string in table.
 * @param[in]		index: unsigned int index
 * @param[in]		table: name_desc_val_table type of table.
 * @DESCRIPTION		Convert a named table entry to its value. If there are
 *			multiple matches, returns the first.
 *//*------------------------------------------------------------------------ */
int name2multivalue(char *name, unsigned int *value, unsigned int index,
	const name_desc_multival_table table[])
{
	unsigned int i = 0;

	#ifdef OMAPCONF_NAME2ADDR_DEBUG
	printf("name2value(): name = %s\n", name);
	#endif

	do {
		if (strcmp(table[i].name, name) == 0) {
			/* register name found */
			*value = table[i].value[index];
			#ifdef OMAPCONF_NAME2ADDR_DEBUG
			printf("name2value(): Name %s indexes Value 0x%x\n",
				name, (*value));
			#endif
			return 0;
		}
		i++;
	} while (strcmp(table[i].name, "END") != 0);

	/* Register name not found */
	#ifdef OMAPCONF_NAME2ADDR_DEBUG
	printf("name2value(): name not found! (%s)\n", name);
	#endif

	return -1;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		value2name
 * @BRIEF		Convert a value table entry to its name. If there are
 *			multiple matches, returns the first.
 * @RETURNS		0 on success
 *			-1 if address not found
 * @param[in, out]	name: Character string (max 64)
 * @param[in]		value: Integer value of matching string in table.
 * @param[in]		index: unsigned int index
 * @param[in]		table: name_desc_val_table type of table.
 * @DESCRIPTION		Convert a value table entry to its name. If there are
 *			multiple matches, returns the first.
 *//*------------------------------------------------------------------------ */
int multivalue2name(unsigned int value, char *name, unsigned int index,
	const name_desc_multival_table table[])
{
	unsigned int i = 0;

	#ifdef OMAPCONF_NAME2ADDR_DEBUG
	printf("value2name(): value = 0x%x\n", value);
	#endif

	do {
		if (table[i].value[index] == value) {
			/* register name found */
			strcpy(name, table[i].name);
			#ifdef OMAPCONF_NAME2ADDR_DEBUG
			printf("value2name(): Value 0x%x indexes Name %s\n",
				 (value), name);
			#endif
			return 0;
		}
		i++;
	} while (strcmp(table[i].name, "END") != 0);


	/* Register name not found */
	#ifdef OMAPCONF_NAME2ADDR_DEBUG
	printf("value2name(): name not found! (%s)\n", name);
	#endif

	return -1;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		name2desc
 * @BRIEF		Convert a value of a table entry to its description
 *			text. If there are multiple matches, returns the first.
 * @RETURNS		0 on success
 *			-1 if address not found
 * @param[in]		value: unsigned int
 * @param[in, out]	desc: character string (max 128) description of
 *			matching string.
 * @param[in]		index: unsigned int index
 * @param[in]		table: name_desc_val_table type of table.
 * @DESCRIPTION		Convert a value of a table entry to its description
 *			text. If there are multiple matches, returns the first.
 *//*------------------------------------------------------------------------ */
int multivalue2desc(unsigned int value, char *desc, unsigned int index,
	const name_desc_multival_table table[])
{
	unsigned int i = 0;

	#ifdef OMAPCONF_NAME2ADDR_DEBUG
	printf("value2desc(): value = 0x%x\n", value);
	#endif

	do {
		if (table[i].value[index] == value) {
			/* register name found */
			strcpy(desc, table[i].desc);
			#ifdef OMAPCONF_NAME2ADDR_DEBUG
			printf("value2name(): Value 0x%x indexes Desc %s\n",
				 (value), desc);
			#endif
			return 0;
		}
		i++;
	} while (strcmp(table[i].name, "END") != 0);


	/* Register name not found */
	#ifdef OMAPCONF_NAME2ADDR_DEBUG
	printf("value2desc(): value not found! (%s)\n", desc);
	#endif

	return -1;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		celcius2fahrenheit
 * @BRIEF		convert celcius degrees to fahrenheit degrees.
 * @RETURNS		celcius degrees converted to fahrenheit degrees.
 * @param[in]		d: celcius degree
 * @DESCRIPTION		convert celcius degrees to fahrenheit degrees.
 *//*------------------------------------------------------------------------ */
int celcius2fahrenheit(int d)
{
	return ((d * 9) / 5) + 32;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		omapconf_getdefaults
 * @BRIEF		Gets defaults from a file and returns ints or strings in
 *			the pointers allocated in the table provided.
 * @RETURNS		Pointers provided in the table will have their contents
 *			updated if entries in the defaults file are found.
 *			>= 0 if success.
 *			OMAPCONF_ERR_ARG incorrect argument(s)
 *			OMAPCONF_ERR_INTERNAL internal error
 *			OMAPCONF_ERR_NOT_AVAILABLE (i.e file not opened/found)
 *			OMAPCONF_ERR_EMPTY (no matching defaults found)
 *			OMAPCONF_ERR_OUTOFBOUNDS (value of a string longer than
 *			allocated.)
 * @param[in]		defaults_file: String of a file to be opened for
 *			reading. Will be closed before returning.
 * @param[in]		prefix: String indicating the prefix of variables for
 *			which to search.
 * @param[in, out]	tablep: Table of entries of expected default
 *			prefex and tokens
 *			that make up the name in a defaults file.
 *			For expected values, pointers must be pre-allocated
 *			in the table for the appropriate data type. Otherwise
 *			the pointers must be set to NULL.
 *			This table must have the final token[0] set to END.
 *			Is this a good convention? Should I pass instead a table
 *			size?
 * @DESCRIPTION		Gets defaults from a file and returns ints or strings in
 *			the pointers allocated in the table provided.
 *			Current implementation is a simple text file of values.
 *			This routine can be modified as necessary for a more
 *			contemporary (say XML) solution without breaking any
 *			calling code. Chose to use pointers to allow filling of
 *			existing structures if available.
 *
 *			Later could add processing of 0xNNNN, 0dNNN type strings
 *			from a file as integers... Also could add more types
 *			than ints/strings if required without breaking code.
 *//*------------------------------------------------------------------------ */
int omapconf_getdefaults(
	char *defaults_file, char *prefix, name_desc_val_table tablep[])
{
	char param[80];
	char *param_ptr;
	char str_val[128];
	int int_val;
	char line[128];
	int i;
	int ret;
	int newline_found = 0;
	int param_found = 0;
	FILE *fp = NULL;


	dprintf("OMAPCONF INFO: Processing Defaults in LIB.\n");

	fp = workdir_fopen(defaults_file, "rt");
	if (fp == NULL)
		return OMAPCONF_ERR_NOT_AVAILABLE;

	/* process defaults */
	dprintf("OMAPCONF INFO: Found and opened %s default file. "
		"Using it for defaults.\n", defaults_file);

	while (fgets(line, 128, fp) != NULL) {
		param_found = 0;
		/* Check if a \n is found. If not, issue a warning */
		for (i = 0; i < 128; i++) {
			if (line[i] == '\n') {
				newline_found = 1; break;
			}
		}
		if (!newline_found) {
			/* issue warning */
			fprintf(stderr, "%s(): WARNING: Read more than 127 "
				"chars from line %s.\nChars over 127 will be "
				"discarded.\n", __func__, defaults_file);
		}
		newline_found = 0;
		/* Process line to remove anything after a # */
		for (i = 0; i < 128; i++) {
			if (line[i] == '#') {
				line[i] = '\0'; break;
			}
		}

		/* Get the line tokens */
		*param = '\0';
		int_val = 0;
		*str_val = '\0';
		/* Get the line with an integer value */
		ret = sscanf(line, "%s %d", param, &int_val);
		/* Get the line with string value */
		ret = sscanf(line, "%s %s", param, str_val);
		if (ret != 2) {
			fprintf(stderr, "%s(): WARNING: Line did not match "
				"expected format.\nLINE: %s\n", __func__, line);
			continue;
		}

		/*
		 * At this point, check if we have a prefix match.
		 * If not, skip to next
		 */
		i = 0;
		while (prefix[i] && param[i] && (param[i] == prefix[i]))
			i++;
		if (prefix[i]) {
			/* If not NULL then no match of prefix. Continue. */
			dprintf("%s(): Prefix mismatch\n", __func__);
			continue;
		}
		/*
		 * Now have a parameter and val entries, and prefix matched.
		 * i points to the start of the param entry to compare.
		 * Reset the param pointer to skip the prefix.
		 */
		param_ptr = &(param[i]);
		/* Now check against the param entry in the table */
		i = 0;
		do {
			dprintf("%s(): OMAPCONF INFO: D.1. %s  --- %s\n",
				__func__, *tablep[i].param, param_ptr);
			if (strcmp(tablep[i].name, param_ptr) == 0) {
				/* parameter name found */
				param_found = 1;
				tablep[i].value = int_val;
				strncpy(tablep[i].desc, str_val,
					OMAPCONF_DESCRIPTION_MAX_LENGTH);
				dprintf("%s(): Found a matching param %s "
					"Copied string %s\n", __func__,
					param_ptr, tablep[i].desc);
			}
			i++;
		} while (strcmp(tablep[i].name, "END") != 0);
		if (!param_found) {
			fprintf(stderr, "%s(): WARNING: Parameter not matched."
				"\n%s(): LINE: %s\n", __func__, __func__, line);
		}

	/*
	 * Walked through the table for a particular parameter.
	 * End while loop to get next.
	 */
	}

	fclose(fp);  /* close the file prior to exiting the routine */
	return 0;

}
