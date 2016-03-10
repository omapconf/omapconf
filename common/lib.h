/*
 *
 * @Component			OMAPCONF
 * @Filename			lib.h
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


#ifndef __LIB_H__
#define __LIB_H__


#include <stdio.h>
#include <reg.h>
#include <stdint.h>
#include <help.h>


/* OMAPCONF standard error numbers */
#define OMAPCONF_ERR_ARG		-1 /* incorrect argument(s) */
#define OMAPCONF_ERR_CPU		-2 /* CPU architecture not supported */
#define OMAPCONF_ERR_INTERNAL		-3 /* internal error */
#define OMAPCONF_ERR_REG_ACCESS		-4 /* register R/W access failed */
#define OMAPCONF_ERR_MEM_MAP		-5 /* memory could not be mapped */
#define OMAPCONF_ERR_MEM_DEV		-6 /* mem device couldn't be opened */
#define OMAPCONF_ERR_UNEXPECTED		-7 /* something unexpected occurred */
#define OMAPCONF_ERR_NOT_AVAILABLE	-8 /* does not exist / not available */
#define OMAPCONF_ERR_TRUNCATED		-9 /* item partially available */
#define OMAPCONF_ERR_EMPTY		-10 /* item is empty */
#define OMAPCONF_ERR_CORRUPTED		-11 /* item is corrupted */
#define OMAPCONF_ERR_FULL		-12 /* item is full */
#define OMAPCONF_ERR_OUTOFBOUNDS	-13 /* arg is too large or too small */
#define OMAPCONF_ERR_TIMEOUT		-14 /* a timer or counter expired */
#define OMAPCONF_ERR_AUDIT_FAIL		-15 /* there were errors during audit */

#define OMAPCONF_DESCRIPTION_MAX_LENGTH	128

#define WORKDIR_MAX_NAME_LENGTH		16

#define KERNEL_VERSION_MAX_LENGTH	128
#define KERNEL_AUTHOR_MAX_LENGTH	128
#define KERNEL_TOOLCHAIN_MAX_LENGTH	128
#define KERNEL_TYPE_MAX_LENGTH		128
#define KERNEL_DATE_MAX_LENGTH		128

#define RELEASE_VERSION_MAX_LENGTH	256
#define RELEASE_TYPE_MAX_LENGTH		128
#define RELEASE_DATE_MAX_LENGTH		128

typedef enum {
	OFF_VOLTAGE = 0,
	RETENTION_VOLTAGE = 8,
	ON_LOW_POWER_VOLTAGE = 16,
	ON_VOLTAGE = 24,
	VOLTAGE_TYPE_MAX
} voltage_type;


typedef enum {
	DATA_INVALID = 0,
	DATA_VALID = 1,
	DATA_TBD = 2,
	DATA_IGNORE = 3,
	DATA_TYPE_MAX = 4
} data_type;


typedef struct {
	char name[OMAPCONF_REG_NAME_MAX_LENGTH];
	unsigned int addr;
} reg_table;


typedef struct {
	char name[OMAPCONF_REG_NAME_MAX_LENGTH];
	char desc[OMAPCONF_DESCRIPTION_MAX_LENGTH];
	unsigned int value;
} name_desc_val_table;


typedef struct {
	char name[OMAPCONF_REG_NAME_MAX_LENGTH];
	char desc[OMAPCONF_DESCRIPTION_MAX_LENGTH];
	unsigned int value[6];
} name_desc_multival_table;


static const char int2char_table[11] = "0123456789";


#define inline __inline


#define OMAPCONF_COND_STRCPY(cond, string, string_cond_true, string_cond_false)\
	if (cond) \
		strcpy(string, string_cond_true);\
	else \
		strcpy(string, string_cond_false);\

#define DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))

/* OMAP_READREG() MACRO DEPRECATED STARTING OMAP5, DON'T USE IT ANYMORE */
#define OMAP_READREG(addr, var) \
	if (mem_read((unsigned int) addr, &var) != 0) { \
		fprintf(stderr, "omapconf: %s(): read error at 0x%08X!!!\n",  \
			__func__, (unsigned int) addr); \
		return OMAPCONF_ERR_REG_ACCESS; \
	}

#define CHECK_NULL_ARG(arg, ret) \
	if ((void *) arg == NULL) { \
		fprintf(stderr, "omapconf: %s(): %s == NULL!!!\n", __func__, #arg); \
		return ret; \
	}

#define CHECK_ARG_LESS_THAN(arg, max, ret) \
	if (arg >= max) { \
		fprintf(stderr, "omapconf: %s(): %s (%u) >= %s (%u) !!!\n", \
			__func__, #arg, arg, #max, max); \
		return ret; \
	}

#define CHECK_CPU(cpu, ret) \
	if (!cpu_is_omap##cpu()) { \
		fprintf(stderr, "omapconf: %s(): cpu %s not supported!!!\n", \
			__func__, #cpu); \
		return ret; \
	}


unsigned short os_supports_wakelock(void);
void omapconf_revision_show(FILE *stream);
char *product_name_get(char product_name[256]);
void chips_info_show(FILE *stream, unsigned short die_id);
void release_info_show(FILE *stream);

char *date_get(char s[17]);

char *bin2str_32(char s[33], unsigned int value);

int short extract_bit(unsigned int regVal, unsigned short pos);
int extract_bitfield(unsigned int regVal, unsigned short start,
	unsigned short len);

unsigned int count32_delta(unsigned int a, unsigned int b);
unsigned int max32(unsigned int a, unsigned int b);
unsigned int min32(unsigned int a, unsigned int b);
int max32s(int a, int b);
int min32s(int a, int b);

uint64_t count64_delta(uint64_t a, uint64_t b);
uint64_t max(uint64_t a, uint64_t b);
double avg_recalc(double prev_avg, double new_val, unsigned int n);

char *mhz2string(double rate, char s[15]);

int find_reg_addr(char *name, unsigned int *addr);
int name2addr(char *name, unsigned int *addr, reg_table table[]);
int dumpregs(reg_table table[]);
int mem_address_range_dump(unsigned int start, unsigned int end);

char *lowercase(char *s);
char *uppercase(char *s);

char *workdir_get(void);
FILE *workdir_fopen(char filename[128], const char *mode);

char *kernel_details_get(char version[KERNEL_VERSION_MAX_LENGTH],
			char author[KERNEL_AUTHOR_MAX_LENGTH],
			char toolchain[KERNEL_TOOLCHAIN_MAX_LENGTH],
			char type[KERNEL_TYPE_MAX_LENGTH],
			char date[KERNEL_DATE_MAX_LENGTH]);

char *release_details_get(char version[RELEASE_VERSION_MAX_LENGTH],
			char type[RELEASE_TYPE_MAX_LENGTH],
			char date[RELEASE_DATE_MAX_LENGTH]);

int name2value(
char *name, unsigned int *value, const name_desc_val_table table[]);
int name2index(
	char *name, unsigned int *index, const name_desc_val_table table[]);
int value2name(
	unsigned int value, char *name, const name_desc_val_table table[]);
int value2desc(
	unsigned int value, char *desc, const name_desc_val_table table[]);

int name2multivalue(char *name, unsigned int *value, unsigned int index,
	const name_desc_multival_table table[]);
int multivalue2name(unsigned int value, char *name, unsigned int index,
	const name_desc_multival_table table[]);
int multivalue2desc(unsigned int value, char *desc, unsigned int index,
	const name_desc_multival_table table[]);

double avg_recalc(double prev_avg, double new_val, unsigned int n);

int celcius2fahrenheit(int d);

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		uv2v
 * @BRIEF		convert micro-volt (integer) to volt (floating point).
 * @RETURNS		voltage in volt (V)
 * @param[in]		uv: voltage in micro-volt (uV)
 * @DESCRIPTION		convert micro-volt (integer) to volt (floating point).
 *//*------------------------------------------------------------------------ */
static inline double uv2v(int uv)
{
	double v;

	v = ((double) uv) / 1000000.0;
	return v;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		v2uv
 * @BRIEF		convert volt (floating point) to micro-volt (integer).
 * @RETURNS		voltage in micro-volt (uV)
 * @param[in]		v: voltage in volt (V)
 * @DESCRIPTION		convert volt (floating point) to micro-volt (integer).
 *//*------------------------------------------------------------------------ */
static inline int v2uv(double v)
{
	return (int) (v * 1000000.0);
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		khz2mhz
 * @BRIEF		convert KHz (integer) to MHz (floating point).
 * @RETURNS		frequency in MHz
 * @param[in]		khz: frequency in KHz
 * @DESCRIPTION		convert KHz (integer) to MHz (floating point).
 *//*------------------------------------------------------------------------ */
static inline double khz2mhz(int khz)
{
	return ((double) khz) / 1000.0;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mhz2khz
 * @BRIEF		convert MHz (floating point) to KHz (integer).
 * @RETURNS		frequency in KHz
 * @param[in]		mhz: frequency in MHz
 * @DESCRIPTION		convert MHz (floating point) to KHz (integer).
 *//*------------------------------------------------------------------------ */
static inline int mhz2khz(double mhz)
{
	return (int) (mhz * 1000.0);
}


int omapconf_getdefaults(
	char *defaults_file, char *prefix, name_desc_val_table tablep[]);


#endif
