/*
 *
 * @Component			OMAPCONF
 * @Filename			cpuinfo.h
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


#ifndef __CPUID_H__
#define __CPUID_H__


#define CPU_NAME_MAX_LENGTH			9
#define CPU_FULL_NAME_MAX_LENGTH		30
#define CPU_REVISION_MAX_NAME_LENGTH		8
#define CPU_DEVICE_TYPE_MAX_NAME_LENGTH		8
#define CPU_SI_TYPE_MAX_NAME_LENGTH		10
#define CPU_PKG_TYPE_MAX_NAME_LENGTH		8
#define CPU_FAB_CODE_MAX_NAME_LENGTH		8
#define CPU_DIE_ID_LENGTH			36


typedef enum {
	OMAP_4430,
	OMAP_4460,
	OMAP_4470,
	OMAP_5430,
	OMAP_5432,
	DRA_75X,
	DRA_72X,
	AM_3352,
	AM_3354,
	AM_3356,
	AM_3357,
	AM_3358,
	AM_3359,
	AM_335X,
	AM_437X,
	OMAP_MAX
} omap_chip;


typedef enum {
	REV_ES1_0,
	REV_ES1_1,
	REV_ES1_2,
	REV_ES1_3,
	REV_ES2_0,
	REV_ES2_1,
	REV_ES2_2,
	REV_ES2_3,
	REV_ES3_0,
	REV_ES3_1,
	REV_ES3_2,
	REV_ES3_3,
	REV_ES_MAX
} omap_chip_revision;


typedef enum {
	DEV_GP,
	DEV_EMU,
	DEV_HS,
	DEV_TEST,
	DEV_TYPE_MAX
} omap_device_type;


typedef enum {
	LOW_PERF_SI = 0,
	STANDARD_PERF_SI = 1,
	HIGH_PERF_SI = 2,
	SPEEDBIN_SI = 3,
	SILICON_TYPE_MAX = 4
} silicon_type;


typedef enum {
	ZCZ,
	ZCE,
	PACKAGE_TYPE_MAX
} package_type;

int cpu_detect(void);
int cpu_force(char *forced_cpu);
unsigned short cpu_is_forced(void);

omap_chip_revision cpu_revision_get(void);
char *cpu_revision_gets(char s[CPU_REVISION_MAX_NAME_LENGTH]);

omap_device_type cpu_device_type_get(void);
char *cpu_device_type_gets(char s[CPU_DEVICE_TYPE_MAX_NAME_LENGTH]);
unsigned int cpu_is_gp_device(void);
unsigned int cpu_is_hs_device(void);
unsigned int cpu_is_emu_device(void);
unsigned int cpu_is_test_device(void);

silicon_type cpu_silicon_type_get(void);
char *cpu_silicon_type_gets(char type[CPU_SI_TYPE_MAX_NAME_LENGTH]);
unsigned int cpu_silicon_max_speed_get(void);

package_type cpu_package_type_get(void);
char *cpu_package_type_gets(char type[CPU_PKG_TYPE_MAX_NAME_LENGTH]);


char *cpu_die_id_get(unsigned int *die_id_3, unsigned int *die_id_2,
	unsigned int *die_id_1, unsigned int *die_id_0,
	char die_id[CPU_DIE_ID_LENGTH]);

omap_chip cpu_get(void);
unsigned int cpu_is_am335x(void);
unsigned int cpu_is_am437x(void);
unsigned int cpu_is_dra7xx(void);
unsigned int cpu_is_dra72x(void);
unsigned int cpu_is_dra75x(void);
unsigned int cpu_is_omap(void);
unsigned int cpu_is_omap44xx(void);
unsigned int cpu_is_omap4430(void);
unsigned int cpu_is_omap4460(void);
unsigned int cpu_is_omap4470(void);
unsigned int cpu_is_omap5430(void);
unsigned int cpu_is_omap5432(void);
unsigned int cpu_is_omap54xx(void);

char *cpu_gets(char s[CPU_NAME_MAX_LENGTH]);
char *cpu_full_name_get(char s[CPU_FULL_NAME_MAX_LENGTH]);

unsigned int cpu_cores_count_get(void);
unsigned int cpu_online_cores_count_get(void);

unsigned int cpu_is_online(unsigned short cpu);
int cpu_proc_stats_get(unsigned int cpu,
	unsigned int *idle, unsigned int *iowait, unsigned int *sum);
double cpu_load_get(unsigned int delta_idle,
	unsigned int delta_iowait, unsigned int delta_sum);


#endif
