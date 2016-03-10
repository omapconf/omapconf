/*
 *
 * @Component			OMAPCONF
 * @Filename			cpuid.c
 * @Description			OMAP CPU Detection & infos
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


#include <cpuinfo.h>
#include <cpuinfo44xx.h>
#include <cpuinfo54xx.h>
#include <cpuinfo_am335x.h>
#include <cpuinfo_am437x.h>
#include <cpuinfo_dra7xx.h>
#include <lib.h>
#include <mem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* #define CPUID_DEBUG */
#ifdef CPUID_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* Identification Registers for OMAP4 & OMAP5 */
#define CONTROL_STD_FUSE_DIE_ID_0			0x4A002200
#define ID_CODE						0x4A002204
#define CONTROL_STD_FUSE_DIE_ID_1			0x4A002208
#define CONTROL_STD_FUSE_DIE_ID_2			0x4A00220C
#define CONTROL_STD_FUSE_DIE_ID_3			0x4A002210
#define CONTROL_STD_FUSE_PROD_ID_0			0x4A002214

/* FOR OMAP4 ONLY */
#define CONTROL_STD_FUSE_PROD_ID_1			0x4A002218

/* Identification Registers for DRA7xx */
#define DRA7_CONTROL_STD_FUSE_DIE_ID_0			0x4AE0C200
#define DRA7_ID_CODE					0x4AE0C204
#define DRA7_CONTROL_STD_FUSE_DIE_ID_1			0x4AE0C208
#define DRA7_CONTROL_STD_FUSE_DIE_ID_2			0x4AE0C20C
#define DRA7_CONTROL_STD_FUSE_DIE_ID_3			0x4AE0C210
#define DRA7_CONTROL_STD_FUSE_PROD_ID_0			0x4AE0C214

/* Identification Registers for AM335x */
#define AM335X_DEVICE_ID				0x44E10600
#define AM335X_DEV_FEAT_REG				0x44E10604
#define AM335X_SI_REV_1_0				0x0B94402E
#define AM335X_SI_REV_2_0				0x1B94402E
#define AM335X_SI_REV_2_1				0x2B94402E

/* Identification Registers for AM437x */
#define AM437X_DEVICE_ID				0x44E10600
#define AM437X_DEV_FEAT_REG				0x44E10604

#define AM335X_STATUS					0x44E10040
#define OMAP44XX_STATUS					0x4A0022C4
#define OMAP54XX_STATUS					0x4A002134

/* AM335X Device Features  */
#define AM3352_DEV_FEAT					0x00FC0382
#define AM3354_DEV_FEAT					0x20FC0382
#define AM3356_DEV_FEAT					0x00FD0383
#define AM3357_DEV_FEAT					0x00FF0383
#define AM3358_DEV_FEAT					0x20FD0383
#define AM3359_DEV_FEAT					0x20FF0383

/* ID Codes */
#define DRA74X_ES_1_0_ID_CODE				0x0B99002F
#define DRA74X_ES_1_1_ID_CODE				0x1B99002F
#define DRA74X_ES_2_0_ID_CODE				0x2B99002F
#define DRA72X_ES_1_0_ID_CODE				0x0B9BC02F
#define DRA72X_ES_2_0_ID_CODE				0x1B9BC02F

#define OMAP5432_ES_2_0_ID_CODE				0x1B99802F
#define OMAP5432_ES_1_0_ID_CODE				0x0B99802F
#define OMAP5430_ES_2_0_ID_CODE				0x1B94202F
#define OMAP5430_ES_1_0_ID_CODE				0x0B94202F

#define OMAP4470_ES_1_0_ID_CODE				0x0B97502F

#define OMAP4460_ES_1_1_ID_CODE				0x2B94E02F
#define OMAP4460_ES_1_0_ID_CODE				0x0B94E02F

#define OMAP4430_ES_2_3_ID_CODE				0x6B95C02F
#define OMAP4430_ES_2_2_ID_CODE				0x4B95C02F
#define OMAP4430_ES_2_1_ID_CODE				0x3B95C02F
#define OMAP4430_ES_2_0_ID_CODE				0x1B85202F
#define OMAP4430_ES_1_0_ID_CODE				0x0B85202F

#define AM437X_SI_REV_1_0				0x0B98C02F
#define AM437X_SI_REV_1_1				0x1B98C02F
#define AM437X_SI_REV_1_2				0x2B98C02F

static unsigned short cpu_forced;


static omap_chip cpu;
static const char cpu_name[OMAP_MAX + 1][CPU_NAME_MAX_LENGTH] = {
	[OMAP_4430] = "OMAP4430",
	[OMAP_4460] = "OMAP4460",
	[OMAP_4470] = "OMAP4470",
	[OMAP_5430] = "OMAP5430",
	[OMAP_5432] = "OMAP5432",
	[DRA_75X]  = "DRA75X",
	[DRA_72X]  = "DRA72X",
	[AM_3352] = "AM3352",
	[AM_3354] = "AM3354",
	[AM_3356] = "AM3356",
	[AM_3357] = "AM3357",
	[AM_3358] = "AM3358",
	[AM_3359] = "AM3359",
	[AM_335X] = "AM335X",
	[AM_437X] = "AM437X",
	[OMAP_MAX] = "UNKNOWN"};
static char cpu_full_name[CPU_FULL_NAME_MAX_LENGTH];


static omap_device_type cpu_type;
static const char
	cpu_device_type[DEV_TYPE_MAX + 1][CPU_DEVICE_TYPE_MAX_NAME_LENGTH] = {
	[DEV_GP] = "GP",
	[DEV_EMU] = "EMU",
	[DEV_HS] = "HS",
	[DEV_TEST] = "TEST",
	[DEV_TYPE_MAX] = "UNKNOWN"};


static omap_chip_revision cpu_rev;
static const char cpu_revision[REV_ES_MAX + 1][CPU_REVISION_MAX_NAME_LENGTH] = {
	[REV_ES1_0] = "1.0",
	[REV_ES1_1] = "1.1",
	[REV_ES1_2] = "1.2",
	[REV_ES1_3] = "1.3",
	[REV_ES2_0] = "2.0",
	[REV_ES2_1] = "2.1",
	[REV_ES2_2] = "2.2",
	[REV_ES2_3] = "2.3",
	[REV_ES3_0] = "3.0",
	[REV_ES3_1] = "3.1",
	[REV_ES3_2] = "3.2",
	[REV_ES3_3] = "3.3",
	[REV_ES_MAX] = "UNKNOWN"};


static silicon_type si_type;
static const char
	silicon_type_table[SILICON_TYPE_MAX + 1]
	[CPU_SI_TYPE_MAX_NAME_LENGTH] = {
	[LOW_PERF_SI] = "LOW",
	[STANDARD_PERF_SI] = "STANDARD",
	[HIGH_PERF_SI] = "HIGH",
	[SPEEDBIN_SI] = "SPEEDBIN",
	[SILICON_TYPE_MAX] = "UNKNOWN"};


static package_type pkg_type;
static const char package_type_table[PACKAGE_TYPE_MAX + 1]
	[CPU_PKG_TYPE_MAX_NAME_LENGTH] = {
	[ZCZ] = "ZCZ",
	[ZCE] = "ZCE",
	[PACKAGE_TYPE_MAX] = ""};


static char cpu_online_file[36] =
	"/sys/devices/system/cpu/cpu*/online";
static int cpu_cores_count = -1;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_forced_set
 * @BRIEF		set CPU forced flag
 * @RETURNS		none
 * @param[in]		forced: CPU forced flag
 * @DESCRIPTION		set CPU forced flag
 *//*------------------------------------------------------------------------ */
static inline void cpu_forced_set(unsigned short forced)
{
	cpu_forced = forced;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_is_forced
 * @BRIEF		return CPU forced flag
 * @RETURNS		0 if CPU not forced (true detection)
 *			1 if CPU forced (user selected CPU)
 * @param[in]		none
 * @DESCRIPTION		return CPU forced flag
 *//*------------------------------------------------------------------------ */
unsigned short cpu_is_forced(void)
{
	return cpu_forced;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_set
 * @BRIEF		set CPU
 * @RETURNS		none
 * @param[in]		omap: detected CPU
 * @DESCRIPTION		set CPU
 *//*------------------------------------------------------------------------ */
static inline void cpu_set(omap_chip omap)
{
	cpu = omap;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_get
 * @BRIEF		return CPU
 * @RETURNS		CPU
 * @param[in]		none
 * @DESCRIPTION		return CPU
 *//*------------------------------------------------------------------------ */
omap_chip cpu_get(void)
{
	return cpu;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_gets
 * @BRIEF		return CPU name as a string
 * @RETURNS		CPU name as a string
 * @param[in,out]	s: pre-allocated string where to store CPU name
 * @DESCRIPTION		return CPU name as a string
 *//*------------------------------------------------------------------------ */
char *cpu_gets(char s[CPU_NAME_MAX_LENGTH])
{
	omap_chip omap;

	omap = cpu_get();
	if (omap > OMAP_MAX)
		omap = OMAP_MAX;
	return strncpy(s, cpu_name[omap], CPU_NAME_MAX_LENGTH);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_is_omap
 * @BRIEF		check if cpu is an omap chip by trying to read
 *			/sys/devices/soc0/machine
 * @RETURNS		1 if cpu is an omap chip
 *			0 if cpu is NOT an omap chip
 * @param[in]		none
 * @DESCRIPTION		check if cpu is an omap chip by trying to read
 *			/sys/devices/soc0/machine
*//*------------------------------------------------------------------------ */
unsigned int cpu_is_omap(void)
{
	FILE *fp;
	char line[256] = {0};
	char *machine_name;
	int ret = 1;

	fp = fopen("/sys/devices/soc0/machine", "r");
	if (fp == NULL) {
		fprintf(stderr, "%s(): CONFIG_SOC_BUS not enabled in kernel!\n"
			"Assuming cpu is OMAP(legacy kernel)\n",
			__func__);
		return 1;
	}
	if (fgets(line, 256, fp)) {
		dprintf("unexpected read\n");
	}

	/* Truncate line at whitespace */
	machine_name = strtok(line, " \n\t\v\f\r");

	if (!strcasecmp(machine_name, "AM335X") || !strcasecmp(machine_name, "AM437X"))
		ret = 0;

	fclose(fp);
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_is_am335x
 * @BRIEF		check if cpu is AM335x
 * @RETURNS		1 if cpu is AM335x
 *			0 if cpu is NOT AM335x
 * @param[in]		none
 * @DESCRIPTION		check if cpu is AM335x
 *//*------------------------------------------------------------------------ */
unsigned int cpu_is_am335x(void)
{
	return ((cpu == AM_3352) || (cpu == AM_3354) || (cpu == AM_3356) ||
		(cpu == AM_3357) || (cpu == AM_3358) || (cpu == AM_3359) ||
		(cpu == AM_335X));
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_is_am437x
 * @BRIEF		check if cpu is AM437x
 * @RETURNS		1 if cpu is AM437x
 *			0 if cpu is NOT AM437x
 * @param[in]		none
 * @DESCRIPTION		check if cpu is AM437x
 *//*------------------------------------------------------------------------ */
unsigned int cpu_is_am437x(void)
{
	return cpu == AM_437X;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_is_dra7xx
 * @BRIEF		check if cpu is DRA7xx
 * @RETURNS		1 if cpu is DRA7xx
 *			0 if cpu is NOT DRA7xx
 * @param[in]		none
 * @DESCRIPTION		check if cpu is DRA7xx
 *//*------------------------------------------------------------------------ */
unsigned int cpu_is_dra7xx(void)
{
	return cpu == DRA_75X || cpu == DRA_72X;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_is_dra72x
 * @BRIEF		check if cpu is DRA72x
 * @RETURNS		1 if cpu is DRA72x
 *			0 if cpu is NOT DRA72x
 * @param[in]		none
 * @DESCRIPTION		check if cpu is DRA72x
 *//*------------------------------------------------------------------------ */
unsigned int cpu_is_dra72x(void)
{
	return cpu == DRA_72X;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_is_dra75x
 * @BRIEF		check if cpu is DRA75x
 * @RETURNS		1 if cpu is DRA75x
 *			0 if cpu is NOT DRA75x
 * @param[in]		none
 * @DESCRIPTION		check if cpu is DRA75x
 *//*------------------------------------------------------------------------ */
unsigned int cpu_is_dra75x(void)
{
	return cpu == DRA_75X;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_is_omap44xx
 * @BRIEF		check if cpu is OMAP44xx
 * @RETURNS		1 if cpu is OMAP44xx
 *			0 if cpu is NOT OMAP44xx
 * @param[in]		none
 * @DESCRIPTION		check if cpu is OMAP44xx
 *//*------------------------------------------------------------------------ */
unsigned int cpu_is_omap44xx(void)
{
	return ((cpu == OMAP_4430) || (cpu == OMAP_4460) || (cpu == OMAP_4470));
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_is_omap4430
 * @BRIEF		check if cpu is OMAP4430
 * @RETURNS		1 if cpu is OMAP4430
 *			0 if cpu is NOT OMAP4430
 * @param[in]		none
 * @DESCRIPTION		check if cpu is OMAP4430
 *//*------------------------------------------------------------------------ */
unsigned int cpu_is_omap4430(void)
{
	return cpu == OMAP_4430;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_is_omap4460
 * @BRIEF		check if cpu is OMAP4460
 * @RETURNS		1 if cpu is OMAP4460
 *			0 if cpu is NOT OMAP4460
 * @param[in]		none
 * @DESCRIPTION		check if cpu is OMAP4460
 *//*------------------------------------------------------------------------ */
unsigned int cpu_is_omap4460(void)
{
	return cpu == OMAP_4460;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_is_omap4470
 * @BRIEF		check if cpu is OMAP4470
 * @RETURNS		1 if cpu is OMAP4470
 *			0 if cpu is NOT OMAP4470
 * @param[in]		none
 * @DESCRIPTION		check if cpu is OMAP4470
 *//*------------------------------------------------------------------------ */
unsigned int cpu_is_omap4470(void)
{
	return cpu == OMAP_4470;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_is_omap5430
 * @BRIEF		check if cpu is OMAP5430
 * @RETURNS		1 if cpu is OMAP5430
 *			0 if cpu is NOT OMAP5430
 * @param[in]		none
 * @DESCRIPTION		check if cpu is OMAP5430
 *//*------------------------------------------------------------------------ */
unsigned int cpu_is_omap5430(void)
{
	return cpu == OMAP_5430;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_is_omap5432
 * @BRIEF		check if cpu is OMAP5432
 * @RETURNS		1 if cpu is OMAP5432
 *			0 if cpu is NOT OMAP5432
 * @param[in]		none
 * @DESCRIPTION		check if cpu is OMAP5432
 *//*------------------------------------------------------------------------ */
unsigned int cpu_is_omap5432(void)
{
	return cpu == OMAP_5432;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_is_omap54xx
 * @BRIEF		check if cpu is OMAP54xx
 * @RETURNS		1 if cpu is OMAP54xx
 *			0 if cpu is NOT OMAP54xx
 * @param[in]		none
 * @DESCRIPTION		check if cpu is OMAP54xx
 *//*------------------------------------------------------------------------ */
unsigned int cpu_is_omap54xx(void)
{
	return ((cpu == OMAP_5430) || (cpu == OMAP_5432));
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_revision_set
 * @BRIEF		set CPU revision
 * @RETURNS		none
 * @param[in]		rev: CPU revision
 * @DESCRIPTION		set CPU revision
 *//*------------------------------------------------------------------------ */
static inline void cpu_revision_set(omap_chip_revision rev)
{
	cpu_rev = rev;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_revision_get
 * @BRIEF		return CPU revision
 * @RETURNS		CPU revision
 * @param[in]		none
 * @DESCRIPTION		return CPU revision
 *//*------------------------------------------------------------------------ */
omap_chip_revision cpu_revision_get(void)
{
	return cpu_rev;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_revision_gets
 * @BRIEF		return CPU revision as a string
 * @RETURNS		CPU revision as a string
 * @param[in,out]	s: pre-allocated string where to store CPU revision
 * @DESCRIPTION		return CPU revision as a string
 *//*------------------------------------------------------------------------ */
char *cpu_revision_gets(char s[CPU_REVISION_MAX_NAME_LENGTH])
{
	if (s == NULL) {
		fprintf(stderr, "%s(): s == NULL!\n", __func__);
		return NULL;
	}

	if (cpu_rev > REV_ES_MAX) {
		fprintf(stderr, "%s(): cpu_rev (%u) > REV_ES_MAX!\n",
			__func__, cpu_rev);
		return NULL;
	}

	return strncpy(s, cpu_revision[cpu_rev], CPU_REVISION_MAX_NAME_LENGTH);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_device_type_set
 * @BRIEF		set CPU device type
 * @RETURNS		none
 * @param[in]		type: device type
 * @DESCRIPTION		set CPU device type
 *//*------------------------------------------------------------------------ */
static inline void cpu_device_type_set(omap_device_type type)
{
	cpu_type = type;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_device_type_get
 * @BRIEF		return CPU device type
 * @RETURNS		CPU device type
 * @param[in]		none
 * @DESCRIPTION		return CPU device type
 *//*------------------------------------------------------------------------ */
omap_device_type cpu_device_type_get(void)
{
	return cpu_type;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_device_type_gets
 * @BRIEF		return CPU device type as a string
 * @RETURNS		CPU device type as a string
 * @param[in,out]	s: pre-allocated string where to store CPU device type
 * @DESCRIPTION		return CPU device type as a string
 *//*------------------------------------------------------------------------ */
char *cpu_device_type_gets(char s[CPU_DEVICE_TYPE_MAX_NAME_LENGTH])
{
	omap_device_type t;

	if (s == NULL) {
		fprintf(stderr, "%s(): s == NULL!\n", __func__);
		return NULL;
	}

	t = cpu_device_type_get();
	if (t > DEV_TYPE_MAX) {
		fprintf(stderr, "%s(): t (%u) > DEV_TYPE_MAX!\n",
			__func__, t);
		return NULL;
	}

	return strncpy(s, cpu_device_type[t], CPU_DEVICE_TYPE_MAX_NAME_LENGTH);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_is_gp_device
 * @BRIEF		check if cpu device type is GP
 * @RETURNS		1 if cpu device type is GP
 *			0 if cpu device type is GP
 * @param[in]		none
 * @DESCRIPTION		check if cpu device type is GP
 *//*------------------------------------------------------------------------ */
unsigned int cpu_is_gp_device(void)
{
	return cpu_type == DEV_GP;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_is_hs_device
 * @BRIEF		check if cpu device type is HS
 * @RETURNS		1 if cpu device type is HS
 *			0 if cpu device type is HS
 * @param[in]		none
 * @DESCRIPTION		check if cpu device type is HS
 *//*------------------------------------------------------------------------ */
unsigned int cpu_is_hs_device(void)
{
	return cpu_type == DEV_HS;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_is_emu_device
 * @BRIEF		check if cpu device type is EMU
 * @RETURNS		1 if cpu device type is EMU
 *			0 if cpu device type is EMU
 * @param[in]		none
 * @DESCRIPTION		check if cpu device type is EMU
 *//*------------------------------------------------------------------------ */
unsigned int cpu_is_emu_device(void)
{
	return cpu_type == DEV_EMU;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_is_test_device
 * @BRIEF		check if cpu device type is TEST
 * @RETURNS		1 if cpu device type is TEST
 *			0 if cpu device type is TEST
 * @param[in]		none
 * @DESCRIPTION		check if cpu device type is TEST
 *//*------------------------------------------------------------------------ */
unsigned int cpu_is_test_device(void)
{
	return cpu_type == DEV_TEST;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_full_name_set
 * @BRIEF		set CPU full name (name + rev + type)
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		none
 * @DESCRIPTION		set CPU full name (name + rev + type)
 *//*------------------------------------------------------------------------ */
static int cpu_full_name_set(void)
{
	char name[CPU_NAME_MAX_LENGTH];
	char rev[CPU_REVISION_MAX_NAME_LENGTH];
	char type[CPU_DEVICE_TYPE_MAX_NAME_LENGTH];

	strncpy(cpu_full_name, "", sizeof(cpu_full_name));

	cpu_gets(name);
	if (name == NULL) {
		fprintf(stderr, "%s(): name == NULL!\n", __func__);
		return OMAPCONF_ERR_INTERNAL;
	}
	cpu_revision_gets(rev);
	if (rev == NULL) {
		fprintf(stderr, "%s(): rev == NULL!\n", __func__);
		return OMAPCONF_ERR_INTERNAL;
	}
	cpu_device_type_gets(type);
	if (type == NULL) {
		fprintf(stderr, "%s(): type == NULL!\n", __func__);
		return OMAPCONF_ERR_INTERNAL;
	}

	if (cpu_is_forced() == 1)
		strcat(cpu_full_name, "FORCED ");
	strcat(cpu_full_name, name);
	strcat(cpu_full_name, " ES");
	strcat(cpu_full_name, rev);
	strcat(cpu_full_name, " (");
	strcat(cpu_full_name, type);
	strcat(cpu_full_name, ")");

	dprintf("%s(): cpu_full_name=%s\n", __func__, cpu_full_name);
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_full_name_get
 * @BRIEF		return CPU full name (name + rev + type) as a string
 * @RETURNS		CPU full name as a string
 * @param[in,out]	s: pre-allocated string where to store CPU full name
 * @DESCRIPTION		return CPU full name (name + rev + type) as a string
 *//*------------------------------------------------------------------------ */
char *cpu_full_name_get(char s[CPU_FULL_NAME_MAX_LENGTH])
{
	return strncpy(s, cpu_full_name, CPU_FULL_NAME_MAX_LENGTH);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_silicon_type_set
 * @BRIEF		set silicon type
 * @RETURNS		none
 * @param[in]		t: silicon type
 * @DESCRIPTION		set silicon type
 *//*------------------------------------------------------------------------ */
static inline void cpu_silicon_type_set(silicon_type t)
{
	si_type = t;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_silicon_type_get
 * @BRIEF		return silicon type
 * @RETURNS		Silicon (process) type
 *			SILICON_TYPE_MAX if unknown
 * @param[in]		none
 * @DESCRIPTION		return silicon type
 *//*------------------------------------------------------------------------ */
silicon_type cpu_silicon_type_get(void)
{
	return si_type;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_silicon_type_gets
 * @BRIEF		return silicon type as a string
 * @RETURNS		silicon type as a string
 * @param[in,out]	type: pre-allocated string where to store silicon type
 * @DESCRIPTION		return silicon type as a string
 *//*------------------------------------------------------------------------ */
char *cpu_silicon_type_gets(char type[CPU_SI_TYPE_MAX_NAME_LENGTH])
{
	silicon_type t;

	if (type == NULL) {
		fprintf(stderr, "%s(): type == NULL!\n", __func__);
		return NULL;
	}

	t = cpu_silicon_type_get();
	if (t > SILICON_TYPE_MAX) {
		fprintf(stderr, "%s(): t (%u) > SILICON_TYPE_MAX!\n",
			__func__, t);
		return NULL;
	}

	return strncpy(type, silicon_type_table[t], CPU_SI_TYPE_MAX_NAME_LENGTH);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_silicon_max_speed_get
 * @BRIEF		return silicon max speed
 * @RETURNS		Silicon max speed (in MHz)
 *			0 in case of error
 * @param[in]		none
 * @DESCRIPTION		return silicon max speed
 *			(depending on cpu type and silicon type)
 *//*------------------------------------------------------------------------ */
unsigned int cpu_silicon_max_speed_get(void)
{
	unsigned int max_speed;

	if (cpu_is_omap44xx()) {
		max_speed = cpu44xx_silicon_max_speed_get();
	} else if (cpu_is_omap54xx()) {
		max_speed = cpu54xx_silicon_max_speed_get();
	} else if (cpu_is_dra7xx()) {
		max_speed = cpu_dra7xx_silicon_max_speed_get();
	} else if(cpu_is_am335x()) {
		max_speed = cpu_am335x_silicon_max_speed_get();
	} else if(cpu_is_am437x()) {
		max_speed = cpu_am437x_silicon_max_speed_get();
	} else {
		dprintf("%s(): unknown architecture!\n", __func__);
		max_speed = 0;
	}

	dprintf("%s(): max speed = %dMHz\n", __func__, max_speed);
	return max_speed;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_package_type_set
 * @BRIEF		set package type
 * @RETURNS		none
 * @param[in]		t: package type
 * @DESCRIPTION		set package type
 *//*------------------------------------------------------------------------ */
static inline void cpu_package_type_set(package_type t)
{
	pkg_type = t;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_package_type_get
 * @BRIEF		return package type
 * @RETURNS		Package type
 *			PACKAGE_TYPE_MAX if unknown
 * @param[in]		none
 * @DESCRIPTION		return package type
 *//*------------------------------------------------------------------------ */
package_type cpu_package_type_get(void)
{
	return pkg_type;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_package_type_gets
 * @BRIEF		return package type as a string
 * @RETURNS		package type as a string
 * @param[in,out]	type: pre-allocated string where to store package type
 * @DESCRIPTION		return package type as a string
 *//*------------------------------------------------------------------------ */
char *cpu_package_type_gets(char type[CPU_PKG_TYPE_MAX_NAME_LENGTH])
{
	package_type t;

	if (type == NULL) {
		fprintf(stderr, "%s(): type == NULL!\n", __func__);
		return NULL;
	}

	t = cpu_package_type_get();
	if (t > PACKAGE_TYPE_MAX) {
		fprintf(stderr, "%s(): t (%u) > PACKAGE_TYPE_MAX!\n",
			__func__, t);
		return NULL;
	}

	return strncpy(type, package_type_table[t], CPU_PKG_TYPE_MAX_NAME_LENGTH);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_die_id_get
 * @BRIEF		return SoC DIE ID (4x 32-bit integers, string).
 * @RETURNS		OMAP DIE ID string (as "DIEID3-DIEID2-DIEID1-DIEID0")
 *			NULL in case of error
 * @param[in,out]	die_id_3: DIE ID (part 3, MSB)
 * @param[in,out]	die_id_2: DIE ID (part 2)
 * @param[in,out]	die_id_1: DIE ID (part 1)
 * @param[in,out]	die_id_0: DIE ID (part 0, LSB)
 * @param[in,out]	die_id: DIE ID string ("DIEID3-DIEID2-DIEID1-DIEID0")
 * @DESCRIPTION		return SoC DIE ID (4x 32-bit integers, string).
 *//*------------------------------------------------------------------------ */
char *cpu_die_id_get(unsigned int *die_id_3, unsigned int *die_id_2,
	unsigned int *die_id_1, unsigned int *die_id_0,
	char die_id[CPU_DIE_ID_LENGTH])
{	unsigned int die_id_add_3;
	unsigned int die_id_add_2;
	unsigned int die_id_add_1;
	unsigned int die_id_add_0;

	CHECK_NULL_ARG(die_id, NULL);

	/*
	 * The DIE ID for the AM335X is TI proprietary information
	 * NULL is returned since it cannot be shown
	 */
	if (cpu_is_am335x() || cpu_is_am437x())
		return NULL;

	if (cpu_get() == DRA_75X || cpu_get() == DRA_72X) {
		die_id_add_3 = DRA7_CONTROL_STD_FUSE_DIE_ID_3;
		die_id_add_2 = DRA7_CONTROL_STD_FUSE_DIE_ID_2;
		die_id_add_1 = DRA7_CONTROL_STD_FUSE_DIE_ID_1;
		die_id_add_0 = DRA7_CONTROL_STD_FUSE_DIE_ID_0;
	} else {
		die_id_add_3 = CONTROL_STD_FUSE_DIE_ID_3;
		die_id_add_2 = CONTROL_STD_FUSE_DIE_ID_2;
		die_id_add_1 = CONTROL_STD_FUSE_DIE_ID_1;
		die_id_add_0 = CONTROL_STD_FUSE_DIE_ID_0;
	}

	if (mem_read(die_id_add_3, die_id_3) != 0)
		return NULL;
	dprintf("%s(): die_id_3 = 0x%08X\n", __func__, *die_id_3);
	if (mem_read(die_id_add_2, die_id_2) != 0)
		return NULL;
	dprintf("%s(): die_id_2 = 0x%08X\n", __func__, *die_id_2);
	if (mem_read(die_id_add_1, die_id_1) != 0)
		return NULL;
	dprintf("%s(): die_id_1 = 0x%08X\n", __func__, *die_id_1);
	if (mem_read(die_id_add_0, die_id_0) != 0)
		return NULL;
	dprintf("%s(): die_id_0 = 0x%08X\n", __func__, *die_id_0);

	sprintf(die_id, "%08X-%08X-%08X-%08X",
		*die_id_3, *die_id_2, *die_id_1, *die_id_0);
	dprintf("%s(): die_id = %s\n", __func__, die_id);

	return die_id;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_init
 * @BRIEF		init local cpuinfo variables
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in]		none
 * @DESCRIPTION		init local cpuinfo variables
 *//*------------------------------------------------------------------------ */
void cpu_init(void)
{
	cpu_forced_set(0);
	cpu_set(OMAP_MAX);
	cpu_revision_set(REV_ES_MAX);
	cpu_device_type_set(DEV_TYPE_MAX);
	cpu_silicon_type_set(SILICON_TYPE_MAX);
	cpu_package_type_set(PACKAGE_TYPE_MAX);
	cpu_full_name_set();
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_rev_get_from_cpuinfo
 * @BRIEF		Parse /proc/cpuinfo to get ARM Cortex-A9 revision
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_UNEXPECTED
 *			OMAPCONF_ERR_CPU if cpu not recognized
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	cpu_rev: returned cpu revision
 *			= REV_ES1_0 if CHIRON
 *			= REV_ES2_0 if VEYRON
 *			= REV_ES_MAX if not found
 * @DESCRIPTION		Parse /proc/cpuinfo to get ARM Cortex-A9 revision
 *//*------------------------------------------------------------------------ */
int cpu_rev_get_from_cpuinfo(omap_chip_revision *cpu_rev)
{
	char line[256];
	FILE *fp;
	unsigned short found = 0;

	/* Open /proc/cpuinfo file */
	fp = fopen("/proc/cpuinfo", "r");
	if (!fp) {
		printf("%s(): /proc/cpuinfo not found?!\n", __func__);
		return OMAPCONF_ERR_UNEXPECTED;
	}

	/* Parse it to find out OMAP CPU revision*/
	*cpu_rev = REV_ES_MAX;
	found = 0;
	while (fgets(line, sizeof(line), fp) != NULL) {
		/* Strip trailing '\n' if it exists */
		dprintf("%s\n", line);
		dprintf("strstr(%s, \"CPU revision\") = %s\n",
			line, strstr(line, "CPU revision"));
		if (strstr(line, "CPU revision") != NULL) {
			dprintf(
				"cpu_rev_get_from_cpuinfo: CPU revision line found\n");
			if (strstr(line, "1") != NULL) {
				*cpu_rev = REV_ES1_0;
				found = 1;
				dprintf("%s(): found CHIRON\n", __func__);
				break;
			} else if (strstr(line, "2") != NULL) {
				*cpu_rev = REV_ES2_0;
				found = 1;
				dprintf("%s(): found VEYRON\n", __func__);
				break;
			} else {
				*cpu_rev = REV_ES_MAX;
				found = 0;
				dprintf("%s(): ES unknown (%s)!\n",
					__func__, line);
				break;
			}
		}
	}
	fclose(fp);
	if (!found) {
		dprintf("%s(): ES not recognized!\n", __func__);
		return OMAPCONF_ERR_CPU;
	}

	return 0;
}

static int identify_omap(void)
{
	unsigned int id_code;

	if (mem_read(ID_CODE, &id_code) != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	dprintf("%s(): ID_CODE = 0x%08X\n", __func__, id_code);

	switch (id_code) {
	case OMAP5432_ES_2_0_ID_CODE:
		cpu_set(OMAP_5432);
		cpu_revision_set(REV_ES2_0);
		break;

	case OMAP5432_ES_1_0_ID_CODE:
		cpu_set(OMAP_5432);
		cpu_revision_set(REV_ES1_0);
		break;

	case OMAP5430_ES_2_0_ID_CODE:
		cpu_set(OMAP_5430);
		cpu_revision_set(REV_ES2_0);
		break;

	case OMAP5430_ES_1_0_ID_CODE:
	case 0x0000002F: /* Zebu */
		cpu_set(OMAP_5430);
		cpu_revision_set(REV_ES1_0);
		break;

	case OMAP4470_ES_1_0_ID_CODE:
		cpu_set(OMAP_4470);
		cpu_revision_set(REV_ES1_0);
		break;

	case OMAP4460_ES_1_1_ID_CODE:
		cpu_set(OMAP_4460);
		cpu_revision_set(REV_ES1_1);
		break;

	case OMAP4460_ES_1_0_ID_CODE:
		cpu_set(OMAP_4460);
		cpu_revision_set(REV_ES1_0);
		break;

	case OMAP4430_ES_2_3_ID_CODE:
		cpu_set(OMAP_4430);
		cpu_revision_set(REV_ES2_3);
		break;

	case OMAP4430_ES_2_2_ID_CODE:
		cpu_set(OMAP_4430);
		cpu_revision_set(REV_ES2_2);
		break;

	case OMAP4430_ES_2_1_ID_CODE:
		cpu_set(OMAP_4430);
		cpu_revision_set(REV_ES2_1);
		break;

	case OMAP4430_ES_2_0_ID_CODE:
	case OMAP4430_ES_1_0_ID_CODE:
		/*
		 * Due to fusing issue between ES1.0 and ES2.0 (same code...),
		 * revision cannot be correctly detected.
		 * Workaround is to use Cortex-A9 own revision code, which did
		 * changed, but it is not accessible from user space...
		 * Only way is to use /proc/cpuinfo.
		 */
		cpu_set(OMAP_4430);
		cpu_rev_get_from_cpuinfo(&cpu_rev);
		switch (cpu_rev) {
		case REV_ES2_0:
			cpu_revision_set(REV_ES2_0);
			break;
		case REV_ES1_0:
			cpu_revision_set(REV_ES1_0);
			break;
		default:
			dprintf("%s(): unknown ARM Cortex-A9!\n", __func__);
			return OMAPCONF_ERR_UNEXPECTED;
		}
		break;
	default:
		/* Retrieve DRA7 chip & ES in default case */
		if (mem_read(DRA7_ID_CODE, &id_code) != 0)
			return OMAPCONF_ERR_REG_ACCESS;
		dprintf("%s(): ID_CODE = 0x%08X\n", __func__, id_code);

		switch (id_code) {
		case DRA72X_ES_1_0_ID_CODE:
			cpu_set(DRA_72X);
			cpu_revision_set(REV_ES1_0);
			break;
		case DRA72X_ES_2_0_ID_CODE:
			cpu_set(DRA_72X);
			cpu_revision_set(REV_ES2_0);
			break;
		case DRA74X_ES_1_1_ID_CODE:
			cpu_set(DRA_75X);
			cpu_revision_set(REV_ES1_1);
			break;
		case DRA74X_ES_1_0_ID_CODE:
			cpu_set(DRA_75X);
			cpu_revision_set(REV_ES1_0);
			break;
		case DRA74X_ES_2_0_ID_CODE:
			cpu_set(DRA_75X);
			cpu_revision_set(REV_ES2_0);
			break;
		default:
			dprintf("%s(): OMAP ID CODE not recognized! (0x%08X)\n",
				__func__, id_code);
			return OMAPCONF_ERR_CPU;
		}
	}

	return 0;
}

static int identify_am335x_features(void)
{
	unsigned int dev_feat;

	if (mem_read(AM335X_DEV_FEAT_REG, &dev_feat) != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	switch (dev_feat) {
	case AM3352_DEV_FEAT:
		cpu_set(AM_3352);
		break;
	case AM3354_DEV_FEAT:
		cpu_set(AM_3354);
		break;
	case AM3356_DEV_FEAT:
		cpu_set(AM_3356);
		break;
	case AM3357_DEV_FEAT:
		cpu_set(AM_3357);
		break;
	case AM3358_DEV_FEAT:
		cpu_set(AM_3358);
		break;
	case AM3359_DEV_FEAT:
		cpu_set(AM_3359);
		break;
	default:
		cpu_set(AM_335X);
		break;
	}

	return 0;
}

static int identify_sitara(void)
{
	unsigned int dev_id;
	int ret = 0;

	/* Setting cpu revision here since different register must be read */
	if (mem_read(AM335X_DEVICE_ID, &dev_id) != 0) {
		fprintf(stderr,
			"omapconf (%s()): could not read DEVICE_ID "
			"register!\n", __func__);
		return OMAPCONF_ERR_REG_ACCESS;
	}
	switch (dev_id) {
	case AM335X_SI_REV_1_0:
		ret = identify_am335x_features();
		cpu_revision_set(REV_ES1_0);
		break;
	case AM335X_SI_REV_2_0:
		ret = identify_am335x_features();
		cpu_revision_set(REV_ES2_0);
		break;
	case AM335X_SI_REV_2_1:
		ret = identify_am335x_features();
		cpu_revision_set(REV_ES2_1);
		break;
	case AM437X_SI_REV_1_0:
		cpu_set(AM_437X);
		cpu_revision_set(REV_ES1_0);
		break;
	case AM437X_SI_REV_1_1:
		cpu_set(AM_437X);
		cpu_revision_set(REV_ES1_1);
		break;
	case AM437X_SI_REV_1_2:
		cpu_set(AM_437X);
		cpu_revision_set(REV_ES1_2);
		break;
	default:
		fprintf(stderr,
			"omapconf (%s()): Unknown silicon revision!\n",
			__func__);
		return OMAPCONF_ERR_CPU;
	}

	return ret;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_detect
 * @BRIEF		Detect cpu and set internal global variables accordingly
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_UNEXPECTED
 *			OMAPCONF_ERR_CPU if cpu not recognized
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		none
 * @DESCRIPTION		Detect cpu and set internal global variables accordingly
 *//*------------------------------------------------------------------------ */
int cpu_detect(void)
{
	unsigned int status;
	unsigned int efuse;
	unsigned int prod_id_1;
	int ret;
	unsigned char status_bit_start;

	#ifdef CPUID_DEBUG
	char s[CPU_FULL_NAME_MAX_LENGTH];
	char rev_s[CPU_REVISION_MAX_NAME_LENGTH];
	char dev_type_s[CPU_DEVICE_TYPE_MAX_NAME_LENGTH];
	#endif

	/* Init variables */
	cpu_init();

	/* Retrieve OMAP chip & ES */
	/* Determine if device is of the AM or OMAP family */
	if (cpu_is_omap())
		ret = identify_omap();
	else
		ret = identify_sitara();

	if (ret)
		return ret;

	dprintf("%s(): Chip is %s ES%s\n", __func__,
		cpu_gets(s), cpu_revision_gets(rev_s));


	/* Retrieve device type */
	if (cpu_is_omap44xx()) {
		ret = mem_read(OMAP44XX_STATUS, &status);
		status_bit_start = 8;
	} else if (cpu_is_omap54xx() || cpu_is_dra7xx()) {
		ret = mem_read(OMAP54XX_STATUS, &status);
		status_bit_start = 6;
	} else if (cpu_is_am335x() || cpu_is_am437x()) {
		ret = mem_read(AM335X_STATUS, &status);
		status_bit_start = 8;
	} else {
		ret = -1;
	}

	if (ret)
		return OMAPCONF_ERR_REG_ACCESS;
	dprintf("%s(): OMAP44XX_STATUS = 0x%08X\n", __func__, status);
	switch (extract_bitfield(status, status_bit_start, 2)) {
	case 3:
		cpu_device_type_set(DEV_GP);
		break;
	case 2:
		cpu_device_type_set(DEV_HS);
		break;
	case 1:
		cpu_device_type_set(DEV_EMU);
		break;
	default:
		cpu_device_type_set(DEV_TEST);
	}
	dprintf("%s(): Device Type is %s\n", __func__,
		cpu_device_type_gets(dev_type_s));

	/* Retrieve silicon performance type from EFuse */
	if (cpu_is_omap44xx()) {
		if (mem_read(CONTROL_STD_FUSE_PROD_ID_1, &prod_id_1) != 0) {
			fprintf(stderr,
				"omapconf (%s()): could not read CONTROL_STD_FUSE_PROD_ID_1 register!\n",
				__func__);
			return OMAPCONF_ERR_REG_ACCESS;
		}
		dprintf("%s(): CONTROL_STD_FUSE_PROD_ID_1 = 0x%08X\n",
			__func__, prod_id_1);
		si_type = (silicon_type) extract_bitfield(prod_id_1, 16, 2);
	} else if (cpu_is_omap54xx()) {
		if (cpu_revision_get() == REV_ES1_0) {
			if (cpu_silicon_max_speed_get() != 1200)
				cpu_silicon_type_set(STANDARD_PERF_SI);
			else
				cpu_silicon_type_set(SPEEDBIN_SI);
		} else {
			if (cpu_silicon_max_speed_get() != 1700)
				cpu_silicon_type_set(STANDARD_PERF_SI);
			else
				cpu_silicon_type_set(SPEEDBIN_SI);
		}
	} else if (cpu_is_dra7xx()) {
		/* TBD: implement true detection when ID data is available */
		cpu_silicon_type_set(STANDARD_PERF_SI);

	} else if (cpu_is_am335x()){
		if (mem_read(EFUSE_SMA_REG, &efuse) != 0) {
			fprintf(stderr,
				"omapconf: (%s()): could not read EFUSE_SMA register!\n",
				__func__);
			return OMAPCONF_ERR_REG_ACCESS;
		}
		switch (extract_bitfield(efuse, 16, 2)) {
		case 0:
			/*
			 * Silicon revision 1.0 does not support EFUSE SMA REG
			 * (returns all 0's if read)
			 * Setting as unknown until there is an alternate method
			 */
			cpu_package_type_set(PACKAGE_TYPE_MAX);
			break;
		case 1:
			cpu_package_type_set(ZCZ);
			break;
		case 2:
			cpu_package_type_set(ZCE);
			break;
		default:
			fprintf(stderr,
				"omapconf: (%s()): could not identify package type!\n",
				__func__);
			return OMAPCONF_ERR_UNEXPECTED;
		}
	}
	dprintf("%s(): Silicon performance type is %s (%uMHz)\n",
		__func__, cpu_silicon_type_gets(s),
		cpu_silicon_max_speed_get());

	/* Set CPU full name */
	cpu_full_name_set();
	dprintf("%s(): CPU full name is %s\n", __func__, cpu_full_name);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_force
 * @BRIEF		Force cpu detection.
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in]		forced_cpu: name of the force cpu
 * @DESCRIPTION		Force cpu detection.
 *//*------------------------------------------------------------------------ */
int cpu_force(char *forced_cpu)
{
	if (forced_cpu == NULL) {
		fprintf(stderr,
			"%s(): forced_cpu == NULL!\n", __func__);
		return OMAPCONF_ERR_ARG;
	}

	cpu_init();

	if (strcmp(forced_cpu, "dra72x") == 0) {
		cpu_forced_set(1);
		cpu_set(DRA_72X);
		cpu_device_type_set(DEV_GP);
		cpu_revision_set(REV_ES1_1);
		cpu_silicon_type_set(STANDARD_PERF_SI);
		cpu_full_name_set();
	} else if (strcmp(forced_cpu, "dra75x") == 0) {
		cpu_forced_set(1);
		cpu_set(DRA_75X);
		cpu_device_type_set(DEV_GP);
		cpu_revision_set(REV_ES1_1);
		cpu_silicon_type_set(STANDARD_PERF_SI);
		cpu_full_name_set();
	} else if (strcmp (forced_cpu, "am3352") == 0) {
		cpu_forced_set(1);
		cpu_set(AM_3352);
		cpu_device_type_set(DEV_GP);
		cpu_revision_set(REV_ES2_1);
		cpu_package_type_set(ZCZ);
		cpu_full_name_set();
	} else if (strcmp (forced_cpu, "am3354") == 0) {
		cpu_forced_set(1);
		cpu_set(AM_3354);
		cpu_device_type_set(DEV_GP);
		cpu_revision_set(REV_ES2_1);
		cpu_package_type_set(ZCZ);
		cpu_full_name_set();
	} else if (strcmp (forced_cpu, "am3356") == 0) {
		cpu_forced_set(1);
		cpu_set(AM_3356);
		cpu_device_type_set(DEV_GP);
		cpu_revision_set(REV_ES2_1);
		cpu_package_type_set(ZCZ);
		cpu_full_name_set();
	} else if (strcmp (forced_cpu, "am3357") == 0) {
		cpu_forced_set(1);
		cpu_set(AM_3357);
		cpu_device_type_set(DEV_GP);
		cpu_revision_set(REV_ES2_1);
		cpu_package_type_set(ZCZ);
		cpu_full_name_set();
	} else if (strcmp (forced_cpu, "am3358") == 0) {
		cpu_forced_set(1);
		cpu_set(AM_3358);
		cpu_device_type_set(DEV_GP);
		cpu_revision_set(REV_ES2_1);
		cpu_package_type_set(ZCZ);
		cpu_full_name_set();
	} else if (strcmp (forced_cpu, "am3359") == 0) {
		cpu_forced_set(1);
		cpu_set(AM_3359);
		cpu_device_type_set(DEV_GP);
		cpu_revision_set(REV_ES2_1);
		cpu_package_type_set(ZCZ);
		cpu_full_name_set();
	} else if (strcmp (forced_cpu, "am335x") == 0) {
		cpu_forced_set(1);
		cpu_set(AM_335X);
		cpu_device_type_set(DEV_GP);
		cpu_revision_set(REV_ES2_1);
		cpu_package_type_set(ZCZ);
		cpu_full_name_set();
	} else if (strcmp (forced_cpu, "am437x") == 0) {
		cpu_forced_set(1);
		cpu_set(AM_437X);
		cpu_device_type_set(DEV_GP);
		cpu_revision_set(REV_ES1_2);
		cpu_full_name_set();
	} else if (strcmp(forced_cpu, "omap5430") == 0) {
		cpu_forced_set(1);
		cpu_set(OMAP_5430);
		cpu_device_type_set(DEV_GP);
		cpu_revision_set(REV_ES2_0);
		cpu_silicon_type_set(STANDARD_PERF_SI);
		cpu_full_name_set();
	} else if (strcmp(forced_cpu, "omap5430es1") == 0) {
		cpu_forced_set(1);
		cpu_set(OMAP_5430);
		cpu_device_type_set(DEV_GP);
		cpu_revision_set(REV_ES1_0);
		cpu_silicon_type_set(STANDARD_PERF_SI);
		cpu_full_name_set();
	} else if (strcmp(forced_cpu, "omap5432") == 0) {
		cpu_forced_set(1);
		cpu_set(OMAP_5432);
		cpu_device_type_set(DEV_GP);
		cpu_revision_set(REV_ES2_0);
		cpu_silicon_type_set(STANDARD_PERF_SI);
		cpu_full_name_set();
	} else if (strcmp(forced_cpu, "omap5432es1") == 0) {
		cpu_forced_set(1);
		cpu_set(OMAP_5432);
		cpu_device_type_set(DEV_GP);
		cpu_revision_set(REV_ES1_0);
		cpu_silicon_type_set(STANDARD_PERF_SI);
		cpu_full_name_set();
	} else if (strcmp(forced_cpu, "omap4430") == 0) {
		cpu_forced_set(1);
		cpu_set(OMAP_4430);
		cpu_device_type_set(DEV_GP);
		cpu_revision_set(REV_ES2_2);
		cpu_silicon_type_set(STANDARD_PERF_SI);
		cpu_full_name_set();
	} else if (strcmp(forced_cpu, "omap4460") == 0) {
		cpu_forced_set(1);
		cpu_set(OMAP_4460);
		cpu_device_type_set(DEV_GP);
		cpu_revision_set(REV_ES1_1);
		cpu_silicon_type_set(STANDARD_PERF_SI);
		cpu_full_name_set();
	} else if (strcmp(forced_cpu, "omap4470") == 0) {
		cpu_forced_set(1);
		cpu_set(OMAP_4470);
		cpu_device_type_set(DEV_GP);
		cpu_revision_set(REV_ES1_0);
		cpu_silicon_type_set(STANDARD_PERF_SI);
		cpu_full_name_set();
	} else {
		return OMAPCONF_ERR_ARG;
	}

	cpu_forced_set(1);
	return 0;
}


/* #define CPU_IS_ONLINE_DEBUG */
#ifdef CPU_IS_ONLINE_DEBUG
#undef dprintf
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#endif
/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_is_online
 * @BRIEF		check if cpu core is online
 * @RETURNS		0 cpu is OFFLINE
 *			1 cpu is ONLINE
 * @param[in]		cpu: cpu core number
 * @DESCRIPTION		check if cpu core is online
 *//*------------------------------------------------------------------------ */
unsigned int cpu_is_online(unsigned short cpu)
{
	FILE *fp;
	int ret;
	unsigned int online;

	#ifdef CPU_IS_ONLINE_DEBUG
	if (cpu >= 9) {
		fprintf(stderr, "%s(%u): cpu > 9!\n", __func__, cpu);
		return 0;
	}
	#endif

	cpu_online_file[27] = int2char_table[cpu];
	dprintf("%s(%u): opening %s\n", __func__, cpu, cpu_online_file);
	/* Open "/sys/devices/system/cpu/cpuX/online" file */
	fp = fopen(cpu_online_file, "r");
	if (fp == NULL) {
		fprintf(stderr, "%s(%u): error opening %s file!\n",
			__func__, cpu, cpu_online_file);
		return 0;
	}

	ret = fscanf(fp, "%u", &online);
	if (ret != 1) {
		fprintf(stderr, "%s(%u): error reading %s file!\n",
			__func__, cpu, cpu_online_file);
		fclose(fp);
		return 0;
	}
	dprintf("%s(%u) = %u\n", __func__, cpu, online);
	fclose(fp);
	return online;

}
#ifdef CPU_IS_ONLINE_DEBUG
#undef dprintf
#define dprintf(format, ...)
#endif


/* #define CPU_PROC_STATS_GET_DEBUG */
#ifdef CPU_PROC_STATS_GET_DEBUG
#undef dprintf
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#endif
/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_proc_stats_get
 * @BRIEF		extract CPU runtime execution statistics from /proc/stat
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in]		cpu: cpu core number
 * @param[in,out]	idle: amount of time the CPU has spent IDLE, since boot
 *			(RETURNED)
 * @param[in,out]	iowait: amount of time the CPU has spent waiting for I/O
 *			to complete, since boot (RETURNED)
 * @param[in,out]	sum: total amount of time, since boot (RETURNED)
 * @DESCRIPTION		extract CPU runtime execution statistics from /proc/stat
 *			Time units are in USER_HZ.
 *//*------------------------------------------------------------------------ */
int cpu_proc_stats_get(unsigned int cpu,
	unsigned int *idle, unsigned int *iowait, unsigned int *sum)
{
	FILE *fp;
	int ret;
	unsigned short i;
	char line[256];
	char cpu_name[16];
	unsigned int user;
	unsigned int nice;
	unsigned int system;
	unsigned int irq;
	unsigned int softirq;
	unsigned int steal;

	CHECK_NULL_ARG(idle, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(iowait, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(sum, OMAPCONF_ERR_ARG);

	*idle = 0;
	*iowait = 0;
	*sum = 0;

	/* Open "/proc/stat" file */
	fp = fopen("/proc/stat", "r");
	if (fp == NULL) {
		dprintf("%s(%u): error opening %s file!\n",
			__func__, cpu, "/proc/stat");
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	/* Get idle, iowait & sum stats from file */
	for (i = 0; i <= cpu + 1; i++) {
		if (fgets(line, sizeof(line), fp)) {
			dprintf("unexpected read\n");
		}
		if (i != cpu + 1)
			continue;

		dprintf("%s(%u): line=%s", __func__, cpu, line);
		ret = sscanf(line, "%s %u %u %u %u %u %u %u %u\n",
			cpu_name, &user, &nice, &system, idle, iowait,
			&irq, &softirq, &steal);
		if ((ret != 9) || (strstr(cpu_name, "cpu") == NULL)) {
			dprintf("%s(%u): error reading file! CPU%u offline?\n",
				__func__, cpu, cpu);
			dprintf("%s(%u):  line=%s",
				__func__, cpu, line);
			dprintf("%s(%u):  ret=%d\n",
				__func__, cpu, ret);
			fclose(fp);
			return OMAPCONF_ERR_UNEXPECTED;
		}
	}

	/* Close file */
	fclose(fp);

	/* Return stats */
	*sum = user + nice + system + *idle + *iowait + irq + softirq + steal;
	dprintf("%s(%u): idle=%u, iowait=%u, sum=%u\n", __func__, cpu,
		*idle, *iowait, *sum);
	return 0;
}
#ifdef CPU_PROC_STATS_GET_DEBUG
#undef dprintf
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_load_get
 * @BRIEF		compute CPU load (0 - 100%)
 * @RETURNS		CPU load (0 - 100%)
 * @param[in]		delta_idle: delta amount of CPU IDLE time, between two
 *			samples
 * @param[in]		delta_iowait: delta amount of CPU IOWAIT time,
 *			between two samples
 * @param[in]		delta_sum: delta amount of time, between two samples
 * @DESCRIPTION		compute CPU load (0 - 100%)
 *//*------------------------------------------------------------------------ */
double cpu_load_get(unsigned int delta_idle,
	unsigned int delta_iowait, unsigned int delta_sum)
{
	double load;

	if (delta_sum == 0) {
		fprintf(stderr, "%s(): divide by zero!!!\n", __func__);
		return 0.0;
	}

	load = (double) (delta_idle + delta_iowait);
	load = load / (double) delta_sum;
	load = (1 - load) * 100;

	return load;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_online_cores_count_get
 * @BRIEF		return the number of CPU cores online
 * @RETURNS		number of CPU cores online
 * @param[in]		none
 * @DESCRIPTION		return the number of CPU cores online
 *//*------------------------------------------------------------------------ */
unsigned int cpu_online_cores_count_get(void)
{
	unsigned int i, cpu_total_count, cpu_online_count;

	cpu_total_count = cpu_cores_count_get();
	cpu_online_count = 0;
	for (i = 0; i < cpu_total_count; i++) {
		if (cpu_is_online(i) == 1)
			cpu_online_count++;
	}

	return cpu_online_count;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu_cores_count_get
 * @BRIEF		return the number of CPU cores available
 * @RETURNS		>0 number of CPU cores available
 *			0 in case of error (unknown architecture)
 * @param[in]		none
 * @DESCRIPTION		return the number of CPU cores available
 *//*------------------------------------------------------------------------ */
unsigned int cpu_cores_count_get(void)
{
	FILE *fp;
	char line[256];

	if (cpu_cores_count != -1)
		return cpu_cores_count;

	if (cpu_is_omap44xx()) {
		cpu_cores_count = cpu44xx_cores_count_get();
	} else if (cpu_is_omap54xx()) {
		cpu_cores_count = cpu54xx_cores_count_get();
	} else {
		/* Open "/proc/stat" file */
		fp = fopen("/proc/stat", "r");
		if (fp == NULL) {
			dprintf("%s(%u): error opening %s file!\n",
				__func__, cpu, "/proc/stat");
			fprintf(stderr,
				"omapconf (%s()): could not retrieve the number of CPU cores !\n",
				__func__);
			cpu_cores_count = 0;
			return (unsigned int) cpu_cores_count;
		}

		/* /proc/stat is formatted like this:
		 * cpu  6982 2624 19577 7242532 12176 0 868 0 0 0
		 * cpu0 3960 1682 9120 1796241 9116 0 837 0 0 0
		 * cpu1 1616 837 6133 1810747 1614 0 16 0 0 0
		 * cpu2 1068 88 2574 1816656 949 0 14 0 0 0
		 * cpu3 337 15 1748 1818886 496 0 0 0 0 0
		 * ...
		 * intr 1676733 49 1773 0 0 0 0 0 0 0 0 0 0 1032 0 0 45427 0 0
		 * ...
		 */
		cpu_cores_count = -1;
		if (fgets(line, sizeof(line), fp)) {
			dprintf("unexpected read\n");
		}
		while ((line != NULL) && (strstr(line, "cpu") != NULL)) {
			cpu_cores_count++;
			if (fgets(line, sizeof(line), fp)) {
				dprintf("unexpected read\n");
			}
		};
		dprintf("%s(): cpu_cores_count=%u\n", __func__,
			cpu_cores_count);

		/* Close file */
		fclose(fp);
	}

	return (unsigned int) cpu_cores_count;
}
