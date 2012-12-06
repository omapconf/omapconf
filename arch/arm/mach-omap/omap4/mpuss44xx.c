/*
 *
 * @Component			OMAPCONF
 * @Filename			mpuss44xx.c
 * @Description			OMAP4 MPU Subsystem Definitions & Functions
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


#include <mpuss44xx.h>
#define __USE_GNU
#define _GNU_SOURCE
#include <sched.h>
#include <help.h>
#include <lib.h>
#include <mem.h>
#include <cpuinfo.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


/* #define MPUSS44XX_DEBUG */
#ifdef MPUSS44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


reg_table mpuss44xx_scu_reg_table[9];
reg_table mpuss44xx_gic_proc_reg_table[10];
reg_table mpuss44xx_gic_dist_reg_table[132];
reg_table mpuss44xx_wkg_reg_table[15];
reg_table mpuss44xx_scm_reg_table[9];
static unsigned int init_done = 0;

static int mpuss44xx_regtable_init(void);

static unsigned int int_config_reg_addr_array[10] = {
	OMAP4430_INT_CONFIG_15_0, OMAP4430_INT_CONFIG_31_16, OMAP4430_INT_CONFIG_47_32,
	OMAP4430_INT_CONFIG_63_48, OMAP4430_INT_CONFIG_79_64, OMAP4430_INT_CONFIG_95_80,
		OMAP4430_INT_CONFIG_111_96, OMAP4430_INT_CONFIG_127_112, OMAP4430_INT_CONFIG_143_128,
	OMAP4430_INT_CONFIG_159_144};

static unsigned int active_status_reg_addr_array[5] = {
	OMAP4430_ACTIVE_STATUS_31_0, OMAP4430_ACTIVE_STATUS_63_32,
	OMAP4430_ACTIVE_STATUS_95_64, OMAP4430_ACTIVE_STATUS_127_96,
	OMAP4430_ACTIVE_STATUS_159_128};

static unsigned int enable_set_reg_addr_array[5] = {
	OMAP4430_ENABLE_SET_31_0, OMAP4430_ENABLE_SET_63_32,
	OMAP4430_ENABLE_SET_95_64, OMAP4430_ENABLE_SET_127_96,
	OMAP4430_ENABLE_SET_159_128};

static unsigned int pending_set_reg_addr_array[5] = {
	OMAP4430_PENDING_SET_31_0, OMAP4430_PENDING_SET_63_32,
	OMAP4430_PENDING_SET_95_64, OMAP4430_PENDING_SET_127_96,
	OMAP4430_PENDING_SET_159_128};

static unsigned int spi_target_reg_addr_array[40] = {
	OMAP4430_SPI_TARGET_3_0, OMAP4430_SPI_TARGET_7_4, OMAP4430_SPI_TARGET_11_8,
	OMAP4430_SPI_TARGET_15_12, 0, 0, 0,
	OMAP4430_SPI_TARGET_31_28, OMAP4430_SPI_TARGET_35_32,
	OMAP4430_SPI_TARGET_39_36, OMAP4430_SPI_TARGET_43_40, OMAP4430_SPI_TARGET_47_44,
	OMAP4430_SPI_TARGET_51_48, OMAP4430_SPI_TARGET_55_52, OMAP4430_SPI_TARGET_59_56,
	OMAP4430_SPI_TARGET_63_60, OMAP4430_SPI_TARGET_67_64, OMAP4430_SPI_TARGET_71_68,
	OMAP4430_SPI_TARGET_75_72, OMAP4430_SPI_TARGET_79_76, OMAP4430_SPI_TARGET_83_80,
	OMAP4430_SPI_TARGET_87_84, OMAP4430_SPI_TARGET_91_88, OMAP4430_SPI_TARGET_95_92,
	OMAP4430_SPI_TARGET_99_96, OMAP4430_SPI_TARGET_103_100, OMAP4430_SPI_TARGET_107_104,
	OMAP4430_SPI_TARGET_111_108, OMAP4430_SPI_TARGET_115_112, OMAP4430_SPI_TARGET_119_116,
	OMAP4430_SPI_TARGET_123_120, OMAP4430_SPI_TARGET_127_124, OMAP4430_SPI_TARGET_131_128,
	OMAP4430_SPI_TARGET_135_132, OMAP4430_SPI_TARGET_139_136, OMAP4430_SPI_TARGET_143_140,
	OMAP4430_SPI_TARGET_147_144, OMAP4430_SPI_TARGET_151_148, OMAP4430_SPI_TARGET_155_152,
	OMAP4430_SPI_TARGET_159_156};

static unsigned int priority_level_reg_addr_array[40] = {
	OMAP4430_PRIORITY_LEVEL_3_0, OMAP4430_PRIORITY_LEVEL_7_4, OMAP4430_PRIORITY_LEVEL_11_8,
	OMAP4430_PRIORITY_LEVEL_15_12, 0, 0, 0,
	OMAP4430_PRIORITY_LEVEL_31_28, OMAP4430_PRIORITY_LEVEL_35_32,
	OMAP4430_PRIORITY_LEVEL_39_36, OMAP4430_PRIORITY_LEVEL_43_40, OMAP4430_PRIORITY_LEVEL_47_44,
	OMAP4430_PRIORITY_LEVEL_51_48, OMAP4430_PRIORITY_LEVEL_55_52, OMAP4430_PRIORITY_LEVEL_59_56,
	OMAP4430_PRIORITY_LEVEL_63_60, OMAP4430_PRIORITY_LEVEL_67_64, OMAP4430_PRIORITY_LEVEL_71_68,
	OMAP4430_PRIORITY_LEVEL_75_72, OMAP4430_PRIORITY_LEVEL_79_76, OMAP4430_PRIORITY_LEVEL_83_80,
	OMAP4430_PRIORITY_LEVEL_87_84, OMAP4430_PRIORITY_LEVEL_91_88, OMAP4430_PRIORITY_LEVEL_95_92,
	OMAP4430_PRIORITY_LEVEL_99_96, OMAP4430_PRIORITY_LEVEL_103_100, OMAP4430_PRIORITY_LEVEL_107_104,
	OMAP4430_PRIORITY_LEVEL_111_108, OMAP4430_PRIORITY_LEVEL_115_112, OMAP4430_PRIORITY_LEVEL_119_116,
	OMAP4430_PRIORITY_LEVEL_123_120, OMAP4430_PRIORITY_LEVEL_127_124, OMAP4430_PRIORITY_LEVEL_131_128,
	OMAP4430_PRIORITY_LEVEL_135_132, OMAP4430_PRIORITY_LEVEL_139_136, OMAP4430_PRIORITY_LEVEL_143_140,
	OMAP4430_PRIORITY_LEVEL_147_144, OMAP4430_PRIORITY_LEVEL_151_148, OMAP4430_PRIORITY_LEVEL_155_152,
	OMAP4430_PRIORITY_LEVEL_159_156};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		scu44xx_cpu_power_status2string
 * @BRIEF		convert SCU CPU power status into string
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 * @param[in]		status: SCU CPU power status extracted from register
 * @param[in,out]	s: string where to store SCU CPU power status
 *			(must be pre-allocated)
 * @DESCRIPTION		convert SCU CPU power status into string
 *//*------------------------------------------------------------------------ */
int scu44xx_cpu_power_status2string(unsigned short status, char s[10])
{
	switch (status) {
	case 0:
		strcpy(s, "Normal");
		break;
	case 1:
		strcpy(s, "Reserved");
		break;
	case 2:
		strcpy(s, "Dormant");
		break;
	case 3:
		strcpy(s, "OFF");
		break;
	default:
		return OMAPCONF_ERR_ARG;
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		scu44xx_tag_ram_size2string
 * @BRIEF		convert tag RAM size field into string
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 * @param[in]		size: tag RAM size field extracted from register
 * @param[in]		s: string where to store tag RAM size
 *			(must be pre-allocated)
 * @DESCRIPTION		convert tag RAM size field into string
 *//*------------------------------------------------------------------------ */
int scu44xx_tag_ram_size2string(unsigned short size, char s[30])
{
	switch (size) {
	case 0:
		strcpy(s, "16KB cache, (64 indexes/tag)");
		break;
	case 1:
		strcpy(s, "32KB cache, (128 indexes/tag)");
		break;
	case 2:
		strcpy(s, "64KB cache (256 indexes/tag)");
		break;
	case 3:
		strcpy(s, "reserved");
		break;
	default:
		return OMAPCONF_ERR_ARG;
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		gic44xx_int_nbr2name
 * @BRIEF		retrieve interrupt name from interrupt line number
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 * @param[in]		int_nbr: interrupt number
 * @param[in]		name: interrupt name (must be pre-allocated)
 * @DESCRIPTION		retrieve interrupt name from interrupt line number
 *//*------------------------------------------------------------------------ */
int gic44xx_int_nbr2name(unsigned short int_nbr, char name[24])
{
	/* SPI interrupt lines go from #32 to #159 */
	if (int_nbr > 159)
		return OMAPCONF_ERR_ARG;
	if (name == NULL)
		return OMAPCONF_ERR_ARG;

	strcpy(name, omap44xx_mpu_irq_names[int_nbr]);
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		gic44xx_sensitivity_get
 * @BRIEF		retrieve interrupt sensitivity configuration
 *			from GIC registers
 * @RETURNS		bitfield raw value in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_UNEXPECTED
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		int_nbr: interrupt number
 * @param[in]		s: sensitivity (must be pre-allocated)
 * @DESCRIPTION		retrieve interrupt sensitivity configuration
 *			from GIC registers
 *//*------------------------------------------------------------------------ */
int gic44xx_sensitivity_get(unsigned int int_nbr, char s[12])
{
	unsigned int val, int_config_reg_addr, int_config_reg;

	if (int_nbr >= 160)
		return OMAPCONF_ERR_ARG;

	/* Find corresponding config register */
	int_config_reg_addr = int_config_reg_addr_array[int_nbr / 16];
	/* Read register */
	if (mem_read(int_config_reg_addr, &int_config_reg) != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	val = extract_bitfield(int_config_reg, (int_nbr % 16) << 1, 2);
	switch (val) {
	case 0:
		strcpy(s, "Not impl.");
		break;
	case 1:
	case 2:
		strcpy(s, "HIGH level");
		break;
	case 3:
		strcpy(s, "RISING-edge");
		break;
	default:
		strcpy(s, "reserved!");
		return OMAPCONF_ERR_UNEXPECTED;
	}

	return val;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		gic44xx_is_active
 * @BRIEF		check interrupt active status from GIC registers
 * @RETURNS		1 if interrupt is active
 *			0 if interrupt is inactive
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		int_nbr: interrupt number
 * @param[in]		s: interrupt status (must be pre-allocated)
 * @DESCRIPTION		check interrupt active status from GIC registers
 *//*------------------------------------------------------------------------ */
int gic44xx_is_active(unsigned int int_nbr, char s[9])
{
	unsigned int active_status_reg_addr, active_status_reg;

	if (int_nbr >= 160)
		return OMAPCONF_ERR_ARG;

	/* Find corresponding register */
	active_status_reg_addr = active_status_reg_addr_array[int_nbr / 32];
	/* Read register */
	if (mem_read(active_status_reg_addr, &active_status_reg) != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	dprintf("gic44xx_is_active(): int_nbr=%d, "
		"active_status_reg_addr=0x%08X, active_status_reg=0x%08X, "
		"bit pos=%d, active=%d\n", int_nbr, active_status_reg_addr,
		active_status_reg, int_nbr % 32,
		extract_bit(active_status_reg, (int_nbr % 32)));

	if (extract_bit(active_status_reg, (int_nbr % 32))) {
		strcpy(s, "Active");
		return 1;
	} else {
		strcpy(s, "");
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		gic44xx_is_masked
 * @BRIEF		check interrupt mask configuration from GIC registers
 * @RETURNS		1 if interrupt is masked
 *			0 if interrupt is NOT masked
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		int_nbr: interrupt number
 * @param[in]		s: interrupt mask configuration (must be pre-allocated)
 * @DESCRIPTION		check interrupt mask configuration from GIC registers
 *//*------------------------------------------------------------------------ */
int gic44xx_is_masked(unsigned int int_nbr, char s[4])
{
	unsigned int enable_set_reg_addr, enable_set_reg;

	if (int_nbr >= 160)
		return OMAPCONF_ERR_ARG;

	/* Find corresponding register */
	enable_set_reg_addr = enable_set_reg_addr_array[int_nbr / 32];
	/* Read register */
	if (mem_read(enable_set_reg_addr, &enable_set_reg) != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	dprintf("gic44xx_is_masked(): int_nbr=%d, "
		"enable_set_reg_addr=0x%08X, enable_set_reg=0x%08X, "
		"bit pos=%d, enabled (not masked)=%d\n", int_nbr,
		enable_set_reg_addr,
		enable_set_reg, int_nbr % 32,
		extract_bit(enable_set_reg, (int_nbr % 32)));

	if (extract_bit(enable_set_reg, (int_nbr % 32))) {
		strcpy(s, "");
		return 0;
	} else {
		strcpy(s, "Yes");
		return 1;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		gic44xx_is_pending
 * @BRIEF		check from GIC registers if interrupt is pending
 * @RETURNS		1 if interrupt is pending
 *			0 if interrupt is NOT pending
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		int_nbr: interrupt number
 * @param[in]		s: interrupt status (must be pre-allocated)
 * @DESCRIPTION		check from GIC registers if interrupt is pending
 *//*------------------------------------------------------------------------ */
int gic44xx_is_pending(unsigned int int_nbr, char s[4])
{
	unsigned int pending_set_reg_addr, pending_set_reg;
	char tmp[4];

	if (int_nbr >= 160)
		return OMAPCONF_ERR_ARG;

	/* Find corresponding register */
	pending_set_reg_addr = pending_set_reg_addr_array[int_nbr / 32];
	/* Read register */
	if (mem_read(pending_set_reg_addr, &pending_set_reg) != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	dprintf("gic44xx_is_pending(): int_nbr=%d, "
		"pending_set_reg_addr=0x%08X, pending_set_reg=0x%08X, "
		"bit pos=%d, enabled (not masked)=%d\n", int_nbr,
		pending_set_reg_addr, pending_set_reg, int_nbr % 32,
		extract_bit(pending_set_reg, (int_nbr % 32)));

	if (extract_bit(pending_set_reg, (int_nbr % 32))) {
		if (gic44xx_is_active(int_nbr, tmp) == 1) {
			strcpy(s, "Yes");
			return 1;
		} else {
			strcpy(s, "");
			return 0;
		}
	} else {
		strcpy(s, "");
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		gic44xx_is_cpu_target
 * @BRIEF		check from GIC registers if cpu is target
 *			of this interrupt
 * @RETURNS		1 if interrupt is targeting this cpu
 *			0 if interrupt is NOT targeting this cpu
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		int_nbr: interrupt number
 * @param[in]		cpu: cpu number
 * @param[in]		s: cpu target status (must be pre-allocated)
 * @DESCRIPTION		check from GIC registers if cpu is target
 *			of this interrupt
 *//*------------------------------------------------------------------------ */
int gic44xx_is_cpu_target(unsigned int int_nbr, unsigned short cpu,
	char s[4])
{
	unsigned int spi_target_reg_addr, spi_target_reg;

	if (int_nbr >= 160)
		return OMAPCONF_ERR_ARG;
	if ((int_nbr > 15) && (int_nbr < 28))
		/* not mapped, no register attached */
		return OMAPCONF_ERR_ARG;
	if (cpu > 1)
		return OMAPCONF_ERR_ARG;

	/* Find corresponding register */
	spi_target_reg_addr = spi_target_reg_addr_array[int_nbr / 4];
	/* Read register */
	if (mem_read(spi_target_reg_addr, &spi_target_reg) != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	dprintf("gic44xx_is_cpu_target(int %d, cpu %d): "
		"spi_target_reg_addr=0x%08X, spi_target_reg=0x%08X, "
		"bit pos=%d target=%d\n",
		int_nbr, cpu, spi_target_reg_addr,
		spi_target_reg, cpu + (8 * (int_nbr % 4)),
		extract_bit(spi_target_reg, cpu + (8 * (int_nbr % 4))));

	if (extract_bit(spi_target_reg, cpu + (8 * (int_nbr % 4)))) {
		strcpy(s, "Yes");
		return 1;
	} else {
		strcpy(s, "No");
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		gic44xx_priority_get
 * @BRIEF		retrieve interrupt priority from GIC registers
 * @RETURNS		interrupt priority level
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		int_nbr: interrupt number
 * @param[in,out]	p: interrupt priority level
 * @DESCRIPTION		retrieve interrupt priority from GIC registers
 *//*------------------------------------------------------------------------ */
int gic44xx_priority_get(unsigned int int_nbr, unsigned short *p)
{
	unsigned int priority_level_reg_addr, priority_level_reg;

	if (int_nbr >= 160)
		return OMAPCONF_ERR_ARG;
	if ((int_nbr > 15) && (int_nbr < 28))
		/* not mapped, no register attached */
		return OMAPCONF_ERR_ARG;

	/* Find corresponding register */
	priority_level_reg_addr = priority_level_reg_addr_array[int_nbr / 4];
	/* Read register */
	if (mem_read(priority_level_reg_addr, &priority_level_reg) != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	*p = extract_bitfield(priority_level_reg, 3 + (8 * (int_nbr % 4)), 5);

	dprintf("gic44xx_priority_get(int %d): "
		"priority_level_reg_addr=0x%08X priority_level_reg=0x%08X, "
		"bitfield_pos=%d p=%d\n",
		int_nbr, priority_level_reg_addr, priority_level_reg,
		3 + (8 * (int_nbr % 4)), *p);

	return *p;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		gic44xx_binary_point_mask_get
 * @BRIEF		retrieve binary point mask from GIC registers
 * @RETURNS		binary point mask
 *			OMAPCONF_ERR_ARG
 * @param[in]		bpr: ICCBPR register content
 * @param[in]		sec: select secure (1) or non-secure (0) mask
 * @param[in,out]	bpm: binary point mask
 * @DESCRIPTION		retrieve binary point mask from GIC registers
 *//*------------------------------------------------------------------------ */
int gic44xx_binary_point_mask_get(unsigned int bpr,
	unsigned short sec, unsigned short *bpm)
{
	static unsigned short bpm_array[2][8] = {
		{0xF8, 0xF8, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x00},
		{0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xE0, 0xC0, 0x80} };

	if (sec > 1)
		return OMAPCONF_ERR_ARG;

	*bpm = bpm_array[sec][extract_bitfield(bpr, 0, 3)];

	dprintf("gic44xx_binary_point_mask_get(bpr=%d, sec=%d): "
		"bp=%d, bpm=0x%02X\n", bpr, sec,
		extract_bitfield(bpr, 0, 3), *bpm);

	return *bpm;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mpuss44xx_scu_dump
 * @BRIEF		dump MPUSS SCU registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		dump MPUSS SCU registers
 *//*------------------------------------------------------------------------ */
int mpuss44xx_scu_dump(void)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_ARG);

	mpuss44xx_regtable_init();

	return dumpregs((reg_table *) mpuss44xx_scu_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mpuss44xx_pl310_dump
 * @BRIEF		dump MPUSS PL310 registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		dump MPUSS PL310 registers
 *//*------------------------------------------------------------------------ */
int mpuss44xx_pl310_dump(void)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_ARG);

	mpuss44xx_regtable_init();

	return dumpregs((reg_table *) omap4_mpuss_pl310_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mpuss44xx_gic_dump
 * @BRIEF		dump MPUSS GIC registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		dump MPUSS GIC registers
 *//*------------------------------------------------------------------------ */
int mpuss44xx_gic_dump(void)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_ARG);

	mpuss44xx_regtable_init();

	if (dumpregs((reg_table *) mpuss44xx_gic_dist_reg_table) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	return dumpregs((reg_table *) mpuss44xx_gic_proc_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mpuss44xx_wkg_dump
 * @BRIEF		dump MPUSS WKG registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		dump MPUSS WKG registers
 *//*------------------------------------------------------------------------ */
int mpuss44xx_wkg_dump(void)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_ARG);

	mpuss44xx_regtable_init();

	return dumpregs((reg_table *) mpuss44xx_wkg_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mpuss44xx_scm_dump
 * @BRIEF		dump MPUSS SCM registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		dump MPUSS SCM registers
 *//*------------------------------------------------------------------------ */
int mpuss44xx_scm_dump(void)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_ARG);

	mpuss44xx_regtable_init();

	return dumpregs((reg_table *) mpuss44xx_scm_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mpuss44xx_scu_config_show
 * @BRIEF		analyze SCU configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		analyze SCU configuration
 *//*------------------------------------------------------------------------ */
int mpuss44xx_scu_config_show(void)
{
	unsigned int scu_control_register;
	unsigned int scu_configuration_register;
	unsigned int scu_cpu_power_status;
	unsigned int scu_invalidate_all_register;
	unsigned int filtering_start_address_register;
	unsigned int filtering_end_address_register;
	unsigned int scu_access_control_register;
	unsigned int scu_secure_access_control_register;

	char s[30];

	CHECK_CPU(44xx, OMAPCONF_ERR_ARG);

	mpuss44xx_regtable_init();

	if (mem_read(OMAP4430_SCU_CONTROL_REGISTER,
		&scu_control_register) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_SCU_CONFIGURATION_REGISTER,
		&scu_configuration_register) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_SCU_CPU_POWER_STATUS,
		&scu_cpu_power_status) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_SCU_INVALIDATE_ALL_REGISTER,
		&scu_invalidate_all_register) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_FILTERING_START_ADDRESS_REGISTER,
		&filtering_start_address_register) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_FILTERING_END_ADDRESS_REGISTER,
		&filtering_end_address_register) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_SCU_ACCESS_CONTROL_REGISTER,
		&scu_access_control_register) != 0)
		return OMAPCONF_ERR_REG_ACCESS;
	if (mem_read(OMAP4430_SCU_SECURE_ACCESS_CONTROL_REGISTER,
		&scu_secure_access_control_register) != 0)
		return OMAPCONF_ERR_REG_ACCESS;

	printf("|---------------------------------"
		"--------------------------------|\n");
	printf("| %-30s | %-30s |\n", "MPUSS SCU config", "");
	printf("|---------------------------------"
		"--------------------------------|\n");
	printf("| %-30s | %-30s |\n", "Mode",
		((extract_bit(scu_control_register, 0) == 1) ?
			"Enabled" : "Disabled"));
	printf("| %-30s | %-30s |\n", "Parity",
		((extract_bit(scu_control_register, 1) == 1) ?
			"Enabled" : "Disabled"));
	printf("| %-30s | %-30s |\n", "Address Filtering",
		((extract_bit(scu_control_register, 2) == 1) ?
			"Enabled" : "Disabled"));
	if (extract_bit(scu_control_register, 2) == 1) {
		printf("| %-30s | %-30d |\n", "  Filtering Start Address",
			extract_bitfield(filtering_start_address_register,
				20, 12) << 20);
		printf("| %-30s | %-30d |\n", "  Filtering End Address",
			extract_bitfield(filtering_end_address_register,
				20, 12) << 20);
	}
	printf("| %-30s | %-30d |\n", "Number of CPUs",
		extract_bitfield(1 + scu_configuration_register, 0, 2));
	printf("| %-30s | %-30s |\n", "CPU Mode", "");
	printf("| %-30s | %-30s |\n", "  CPU0",
		((extract_bit(scu_configuration_register, 4) == 1) ?
			"SMP" : "AMP"));
	printf("| %-30s | %-30s |\n", "  CPU1",
		((extract_bit(scu_configuration_register, 5) == 1) ?
			"SMP" : "AMP"));
	printf("| %-30s | %-30s |\n", "Tag RAM Size", "");
	scu44xx_tag_ram_size2string(
		extract_bitfield(scu_configuration_register, 8, 2), s);
	printf("| %-30s | %-30s |\n", "  CPU0", s);
	scu44xx_tag_ram_size2string(
		extract_bitfield(scu_configuration_register, 10, 2), s);
	printf("| %-30s | %-30s |\n", "  CPU1", s);
	printf("| %-30s | %-30s |\n", "Power Status", "");
	scu44xx_cpu_power_status2string(
		extract_bitfield(scu_cpu_power_status, 0, 2), s);
	printf("| %-30s | %-30s |\n", "  CPU0", s);
	scu44xx_cpu_power_status2string(
		extract_bitfield(scu_cpu_power_status, 8, 2), s);
	printf("| %-30s | %-30s |\n", "  CPU1", s);
	printf("| %-30s | %-30s |\n", "SCU Access Control", "");
	printf("| %-30s | %-30s |\n", "  CPU0",
		((extract_bit(scu_access_control_register, 0) == 1) ?
		"Allowed" : "Forbidden"));
	printf("| %-30s | %-30s |\n", "  CPU1",
		((extract_bit(scu_access_control_register, 1) == 1) ?
		"Allowed" : "Forbidden"));
	printf("| %-30s | %-30s |\n", "Non-Secure Access Control", "");
	printf("| %-30s | %-30s |\n", "  Components", "");
	printf("| %-30s | %-30s |\n", "    CPU0",
		((extract_bit(scu_secure_access_control_register, 0) == 1) ?
		"Allowed" : "Forbidden"));
	printf("| %-30s | %-30s |\n", "    CPU1",
		((extract_bit(scu_secure_access_control_register, 1) == 1) ?
		"Allowed" : "Forbidden"));
	printf("| %-30s | %-30s |\n", "  Private Timer", "");
	printf("| %-30s | %-30s |\n", "    CPU0",
		((extract_bit(scu_secure_access_control_register, 4) == 1) ?
		"Allowed" : "Secure only"));
	printf("| %-30s | %-30s |\n", "    CPU1",
		((extract_bit(scu_secure_access_control_register, 5) == 1) ?
		"Allowed" : "Secure only"));
	printf("|---------------------------------"
		"--------------------------------|\n\n");

	return 0;
};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mpuss44xx_gic_config_show
 * @BRIEF		analyze GIC configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @DESCRIPTION		analyze GIC configuration
 *//*------------------------------------------------------------------------ */
int mpuss44xx_gic_config_show(void)
{
	unsigned int i = 0;
	char sensitivity[12];
	char active[9];
	char masked[4];
	char pending[4];
	char cpu0_target[4], cpu1_target[4];
	unsigned short priority;
	unsigned short int cpu;
	char s[50];
	unsigned int icpicr;
	unsigned int iccipmr;
	unsigned int iccbpr;
	unsigned int iccrpr;
	unsigned int icchpir;
	unsigned int iccabpr;
	int ret;
	unsigned short bpm;
	unsigned long mask;
	unsigned int len = sizeof(mask);
	cpu_set_t set;

	CHECK_CPU(44xx, OMAPCONF_ERR_ARG);

	mpuss44xx_regtable_init();

	for (cpu = 0; cpu < 2; cpu++) {
		/* Force process to run on selected CPU */
		CPU_ZERO(&set);
		CPU_SET(cpu, &set);
		sched_setaffinity(0, len, &set);
		#ifdef MPUSS44XX_DEBUG
		sched_getaffinity(0, len, &set);
		dprintf("mpuss44xx_gic_config_show(): CPU%d affinity: %d\n",
			cpu, set);
		#endif
		printf("|-------------------------------------------------"
			"-------------------------------------------------|\n");
		printf("| CPU%d %-91s |\n", cpu, "GIC SGI & PPI Configuration");
		printf("|-------------------------------------------------"
			"-------------------------------------------------|\n");
		printf("| %-28s | %-8s | %-6s | %-7s | %-10s | %-8s |"
			" %-11s |\n", "Int (#) Name", "Status", "Masked",
			"Pending", "Target CPU", "Priority", "Sensitivity");
		printf("|-------------------------------------------------"
			"-------------------------------------------------|\n");
		for (i = 0; i < 32; i++) {
			if (i == 16)
				/* skip interrupt lines 16 to 27, not mapped */
				i = 28;
			gic44xx_int_nbr2name(i, s);
			gic44xx_sensitivity_get(i, sensitivity);
			gic44xx_is_active(i, active);
			gic44xx_is_masked(i, masked);
			gic44xx_is_pending(i, pending);
			gic44xx_is_cpu_target(i, cpu, cpu0_target);
			gic44xx_priority_get(i, &priority);
			printf("| (%-2d) %-23s | %-8s | %-6s | %-7s | "
				"%-10s | %-8d | %-11s |\n",
				i, s,
				active,
				masked,
				pending,
				cpu0_target,
				priority,
				sensitivity);
		}
		printf("|---------------------------------------------------"
			"-----------------------------------------------|\n\n");
	}

	printf("|------------------------------------------------"
		"----------------------------------------------------|\n");
	printf("| %-98s |\n", "GIC SPI Configuration");
	printf("|------------------------------------------------"
		"----------------------------------------------------|\n");
	printf("| %-29s | %-8s | %-6s | %-7s | %-11s | %-8s | %-11s |\n",
		"Int (#) Name", "Status", "Masked", "Pending", "Target CPU",
		"Priority", "Sensitivity");
	printf("| %-29s | %-8s | %-6s | %-7s | %-4s | %-4s | %-11s |\n",
		"", "", "", "", "CPU0", "CPU1", "");
	printf("|------------------------------------------------"
		"----------------------------------------------------|\n");

	for (i = 32; i < 160; i++) {
		gic44xx_int_nbr2name(i, s);
		gic44xx_sensitivity_get(i, sensitivity);
		gic44xx_is_active(i, active);
		gic44xx_is_masked(i, masked);
		gic44xx_is_pending(i, pending);
		gic44xx_is_cpu_target(i, 0, cpu0_target);
		gic44xx_is_cpu_target(i, 1, cpu1_target);
		gic44xx_priority_get(i, &priority);

		printf("| (%-3d) %-23s | %-8s | %-6s | %-7s | %-4s | "
			"%-4s | %-8d | %-11s |\n",
			i, s,
			active,
			masked,
			pending,
			cpu0_target,
			cpu1_target,
			priority,
			sensitivity);
	}
	printf("|------------------------------------------------"
		"----------------------------------------------------|\n\n");

	/* GIC Processor Interface smart analyzis */
	for (cpu = 0; cpu < 2; cpu++) {
		/* Force process to run on selected CPU */
		CPU_ZERO(&set);
		CPU_SET(cpu, &set);
		sched_setaffinity(0, len, &set);
		#ifdef MPUSS44XX_DEBUG
		sched_getaffinity(0, len, &set);
		dprintf("mpuss44xx_gic_config_show(): CPU%d affinity: %d\n",
			cpu, set);
		#endif
		/* Read Registers */
		ret = 0;
		ret += mem_read(OMAP4430_ICPICR, &icpicr);
		ret += mem_read(OMAP4430_ICCIPMR, &iccipmr);
		ret += mem_read(OMAP4430_ICCBPR, &iccbpr);
		ret += mem_read(OMAP4430_ICCRPR, &iccrpr);
		ret += mem_read(OMAP4430_ICCHPIR, &icchpir);
		ret += mem_read(OMAP4430_ICCABPR, &iccabpr);
		if (ret != 0)
			return OMAPCONF_ERR_REG_ACCESS;
		/* Display Configuration */
		printf("|-----------------------------------------"
			"--------------------------------------------|\n");
		printf("| CPU%d %-78s |\n", cpu,
			"GIC Processor Interface Configuration");
		printf("|-----------------------------------------"
			"--------------------------------------------|\n");
		OMAPCONF_COND_STRCPY(extract_bit(icpicr, 4) == 1, s,
			"Non-Sec ignored",
			"Sec: bin_pt_s, N-Sec: bin_pt_ns");
		printf("| %-40s | %-40s |\n",
				"Used Binary Pointer Register", s);
		OMAPCONF_COND_STRCPY(extract_bit(icpicr, 3) == 1, s,
			"nFIQ",
			"nIRQ");
		printf("| %-40s | %-40s |\n",
				"Signal used for Secure Int.", s);
		OMAPCONF_COND_STRCPY(extract_bit(icpicr, 2) == 1, s,
			"Returns ID of the Non-Sec int. and ACK it.",
			"Returns 1022 and int. remains pending");
		printf("| %-40s | %-40s |\n",
				"On ICCIAR secure read when highest", "");
		printf("| %-40s | %-40s |\n",
				" priority interrupt is non-secure", s);
		OMAPCONF_COND_STRCPY(extract_bit(icpicr, 2) == 1, s,
			"int. changed to inactive or pending",
			"Write is ignored, int. status unchanged");
		printf("| %-40s | %-40s |\n",
				"On ICCEOIR secure write to signal ", "");
		printf("| %-40s | %-40s |\n",
				" the completion of non-sec int.", s);
		OMAPCONF_COND_STRCPY(extract_bit(icpicr, 1) == 1, s,
			"Enabled",
			"Disabled");
		printf("| %-40s | %-40s |\n",
				"Non-Secure Interrupts", s);
		OMAPCONF_COND_STRCPY(extract_bit(icpicr, 0) == 1, s,
			"Enabled",
			"Disabled");
		printf("| %-40s | %-40s |\n",
				"Secure Interrupts", s);
		printf("| %-40s | 0x%-38X |\n",
				"Priority Mask Level",
				extract_bitfield(iccipmr, 3, 5));
		gic44xx_binary_point_mask_get(iccbpr, 1, &bpm);
		printf("| %-40s | 0x%-38X |\n",
				"Binary Point Mask (Sec. int.)", bpm);
		gic44xx_binary_point_mask_get(iccabpr, 0, &bpm);
		printf("| %-40s | 0x%-38X |\n",
				"Binary Point Mask (Non-Sec. int.)", bpm);
		printf("| %-40s | 0x%-38X |\n",
				"Priority Level of highest active int.",
				extract_bitfield(iccrpr, 3, 5));
		printf("| %-40s | 0x%-38X |\n",
				"Priority Level of highest pending int.",
				extract_bitfield(icchpir, 0, 10));
		printf("|-----------------------------------------"
			"--------------------------------------------|\n\n");
	}

	/* Force process to come back on CPU0 */
	CPU_ZERO(&set);
	CPU_SET(0, &set);
	sched_setaffinity(0, len, &set);
	#ifdef MPUSS44XX_DEBUG
	sched_getaffinity(0, len, &set);
	dprintf("mpuss44xx_gic_config_show(): CPU%d affinity: %d\n",
		0, set);
	#endif

	return 0;
};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mpuss44xx_main
 * @BRIEF		MPUSS main menu
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		MPUSS main menu
 *//*------------------------------------------------------------------------ */
int mpuss44xx_main(int argc, char *argv[])
{
	CHECK_CPU(44xx, OMAPCONF_ERR_ARG);

	if (argc == 3) {
		if ((strcmp(argv[2], "dump") == 0) && (!init_done))
			mpuss44xx_regtable_init();

		if (strcmp(argv[1], "gic") == 0) {
			if (strcmp(argv[2], "dump") == 0) {
				if (dumpregs(
					mpuss44xx_gic_dist_reg_table) != 0)
					return OMAPCONF_ERR_REG_ACCESS;
				if (dumpregs(
					mpuss44xx_gic_proc_reg_table) != 0)
					return OMAPCONF_ERR_REG_ACCESS;
			} else if (strcmp(argv[2], "cfg") == 0) {
				return mpuss44xx_gic_config_show();
			} else {
				help(HELP_MPUSS);
				return OMAPCONF_ERR_ARG;
			}
		} else if (strcmp(argv[1], "scu") == 0) {
			if (strcmp(argv[2], "dump") == 0) {
				return dumpregs(
					mpuss44xx_scu_reg_table);
			} else if (strcmp(argv[2], "cfg") == 0) {
				return mpuss44xx_scu_config_show();
			} else {
				help(HELP_MPUSS);
				return OMAPCONF_ERR_ARG;
			}
		} else if (strcmp(argv[1], "l2c") == 0) {
			if (strcmp(argv[2], "dump") == 0) {
				return dumpregs(
				(reg_table *) omap4_mpuss_pl310_reg_table);
			} else {
				help(HELP_MPUSS);
				return OMAPCONF_ERR_ARG;
			}
		} else if (strcmp(argv[1], "wkg") == 0) {
			if (strcmp(argv[2], "dump") == 0) {
				return dumpregs(
				mpuss44xx_wkg_reg_table);
			} else {
				help(HELP_MPUSS);
				return OMAPCONF_ERR_ARG;
			}
		} else if (strcmp(argv[1], "scm") == 0) {
			if (strcmp(argv[2], "dump") == 0) {
				return dumpregs(
					mpuss44xx_scm_reg_table);
			} else {
				help(HELP_MPUSS);
				return OMAPCONF_ERR_ARG;
			}
		} else {
			help(HELP_MPUSS);
			return OMAPCONF_ERR_ARG;
		}
	} else {
		help(HELP_MPUSS);
		return OMAPCONF_ERR_ARG;
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mpuss44xx_regtable_init
 * @BRIEF		initialize reg_table fields (not possible statically)
 * @RETURNS		0
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		initialize reg_table fields (not possible statically)
 *//*------------------------------------------------------------------------ */
static int mpuss44xx_regtable_init(void)
{
	int i = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_ARG);

	/* Init MPUSS SCU registers table */
	strcpy(mpuss44xx_scu_reg_table[i].name, "SCU_CONTROL_REGISTER");
	mpuss44xx_scu_reg_table[i++].addr = OMAP4430_SCU_CONTROL_REGISTER;
	strcpy(mpuss44xx_scu_reg_table[i].name, "SCU_CONFIGURATION_REGISTER");
	mpuss44xx_scu_reg_table[i++].addr =
		OMAP4430_SCU_CONFIGURATION_REGISTER;
	strcpy(mpuss44xx_scu_reg_table[i].name, "SCU_CPU_POWER_STATUS");
	mpuss44xx_scu_reg_table[i++].addr = OMAP4430_SCU_CPU_POWER_STATUS;
	strcpy(mpuss44xx_scu_reg_table[i].name,
		"SCU_INVALIDATE_ALL_REGISTER");
	mpuss44xx_scu_reg_table[i++].addr =
		OMAP4430_SCU_INVALIDATE_ALL_REGISTER;
	strcpy(mpuss44xx_scu_reg_table[i].name,
		"FILTERING_START_ADDRESS_REGISTER");
	mpuss44xx_scu_reg_table[i++].addr =
		OMAP4430_FILTERING_START_ADDRESS_REGISTER;
	strcpy(mpuss44xx_scu_reg_table[i].name,
		"FILTERING_END_ADDRESS_REGISTER");
	mpuss44xx_scu_reg_table[i++].addr =
		OMAP4430_FILTERING_END_ADDRESS_REGISTER;
	strcpy(mpuss44xx_scu_reg_table[i].name,
		"SCU_ACCESS_CONTROL_REGISTER");
	mpuss44xx_scu_reg_table[i++].addr =
		OMAP4430_SCU_ACCESS_CONTROL_REGISTER;
	strcpy(mpuss44xx_scu_reg_table[i].name,
		"SCU_SECURE_ACCESS_CONTROL_REGISTER");
	mpuss44xx_scu_reg_table[i++].addr =
		OMAP4430_SCU_SECURE_ACCESS_CONTROL_REGISTER;
	strcpy(mpuss44xx_scu_reg_table[i].name, "END");
	mpuss44xx_scu_reg_table[i].addr = 0;
	dprintf("mpuss44xx_scu_reg_table last index=%d, size=%d\n", i, i + 1);

	/* Init MPUSS GIC PROCESSOR INTERFACE registers table */
	i = 0;
	strcpy(mpuss44xx_gic_proc_reg_table[i].name, "ICPICR");
	mpuss44xx_gic_proc_reg_table[i++].addr = OMAP4430_ICPICR;
	strcpy(mpuss44xx_gic_proc_reg_table[i].name, "ICCIPMR");
	mpuss44xx_gic_proc_reg_table[i++].addr = OMAP4430_ICCIPMR;
	strcpy(mpuss44xx_gic_proc_reg_table[i].name, "ICCBPR");
	mpuss44xx_gic_proc_reg_table[i++].addr = OMAP4430_ICCBPR;
	strcpy(mpuss44xx_gic_proc_reg_table[i].name, "ICCIAR");
	mpuss44xx_gic_proc_reg_table[i++].addr = OMAP4430_ICCIAR;
	strcpy(mpuss44xx_gic_proc_reg_table[i].name, "ICCEOIR");
	mpuss44xx_gic_proc_reg_table[i++].addr = OMAP4430_ICCEOIR;
	strcpy(mpuss44xx_gic_proc_reg_table[i].name, "ICCRPR");
	mpuss44xx_gic_proc_reg_table[i++].addr = OMAP4430_ICCRPR;
	strcpy(mpuss44xx_gic_proc_reg_table[i].name, "ICCHPIR");
	mpuss44xx_gic_proc_reg_table[i++].addr = OMAP4430_ICCHPIR;
	strcpy(mpuss44xx_gic_proc_reg_table[i].name, "ICCABPR");
	mpuss44xx_gic_proc_reg_table[i++].addr = OMAP4430_ICCABPR;
	strcpy(mpuss44xx_gic_proc_reg_table[i].name, "ICCPIIIR");
	mpuss44xx_gic_proc_reg_table[i++].addr = OMAP4430_ICCPIIIR;
	strcpy(mpuss44xx_gic_proc_reg_table[i].name, "END");
	mpuss44xx_gic_proc_reg_table[i].addr = 0;
	dprintf("mpuss44xx_gic_proc_reg_table last index=%d, size=%d\n",
		i, i + 1);

	/* Init MPUSS GIC INTERRUPT DISTRIBUTOR registers table */
	i = 0;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "IC_TYPE_REG");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_IC_TYPE_REG;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "DIST_IDENT_REG");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_DIST_IDENT_REG;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "ENABLE_SET_31_0");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_ENABLE_SET_31_0;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "ENABLE_SET_63_32");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_ENABLE_SET_63_32;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "ENABLE_SET_95_64");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_ENABLE_SET_95_64;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "ENABLE_SET_127_96");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_ENABLE_SET_127_96;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "ENABLE_SET_159_128");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_ENABLE_SET_159_128;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "ENABLE_CLR_31_0");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_ENABLE_CLR_31_0;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "ENABLE_CLR_63_32");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_ENABLE_CLR_63_32;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "ENABLE_CLR_95_64");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_ENABLE_CLR_95_64;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "ENABLE_CLR_127_96");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_ENABLE_CLR_127_96;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "ENABLE_CLR_159_128");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_ENABLE_CLR_159_128;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PENDING_SET_31_0");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_PENDING_SET_31_0;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PENDING_SET_63_32");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_PENDING_SET_63_32;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PENDING_SET_95_64");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_PENDING_SET_95_64;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PENDING_SET_127_96");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_PENDING_SET_127_96;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PENDING_SET_159_128");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_PENDING_SET_159_128;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PENDING_CLR_31_0");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_PENDING_CLR_31_0;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PENDING_CLR_63_32");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_PENDING_CLR_63_32;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PENDING_CLR_95_64");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_PENDING_CLR_95_64;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PENDING_CLR_127_96");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_PENDING_CLR_127_96;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PENDING_CLR_159_128");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_PENDING_CLR_159_128;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "ACTIVE_STATUS_31_0");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_ACTIVE_STATUS_31_0;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "ACTIVE_STATUS_63_32");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_ACTIVE_STATUS_63_32;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "ACTIVE_STATUS_95_64");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_ACTIVE_STATUS_95_64;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "ACTIVE_STATUS_127_96");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_ACTIVE_STATUS_127_96;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "ACTIVE_STATUS_159_128");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_ACTIVE_STATUS_159_128;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PRIORITY_LEVEL_3_0");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_PRIORITY_LEVEL_3_0;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PRIORITY_LEVEL_7_4");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_PRIORITY_LEVEL_7_4;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PRIORITY_LEVEL_11_8");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_PRIORITY_LEVEL_11_8;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PRIORITY_LEVEL_15_12");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_15_12;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PRIORITY_LEVEL_31_28");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_31_28;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PRIORITY_LEVEL_35_32");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_35_32;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PRIORITY_LEVEL_39_36");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_39_36;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PRIORITY_LEVEL_43_40");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_43_40;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PRIORITY_LEVEL_47_44");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_47_44;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PRIORITY_LEVEL_51_48");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_51_48;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PRIORITY_LEVEL_55_52");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_55_52;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PRIORITY_LEVEL_59_56");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_59_56;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PRIORITY_LEVEL_63_60");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_63_60;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PRIORITY_LEVEL_67_64");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_67_64;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PRIORITY_LEVEL_71_68");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_71_68;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PRIORITY_LEVEL_75_72");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_75_72;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PRIORITY_LEVEL_79_76");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_79_76;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PRIORITY_LEVEL_83_80");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_83_80;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PRIORITY_LEVEL_87_84");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_87_84;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PRIORITY_LEVEL_91_88");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_91_88;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PRIORITY_LEVEL_95_92");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_95_92;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PRIORITY_LEVEL_99_96");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_99_96;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name,
		"PRIORITY_LEVEL_103_100");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_103_100;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name,
		"PRIORITY_LEVEL_107_104");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_107_104;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name,
		"PRIORITY_LEVEL_111_108");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_111_108;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name,
		"PRIORITY_LEVEL_115_112");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_115_112;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name,
		"PRIORITY_LEVEL_119_116");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_119_116;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name,
		"PRIORITY_LEVEL_123_120");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_123_120;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name,
		"PRIORITY_LEVEL_127_124");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_127_124;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name,
		"PRIORITY_LEVEL_131_128");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_131_128;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name,
		"PRIORITY_LEVEL_135_132");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_135_132;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name,
		"PRIORITY_LEVEL_139_136");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_139_136;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name,
		"PRIORITY_LEVEL_143_140");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_143_140;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name,
		"PRIORITY_LEVEL_147_144");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_147_144;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name,
		"PRIORITY_LEVEL_151_148");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_151_148;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name,
		"PRIORITY_LEVEL_155_152");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_155_152;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name,
		"PRIORITY_LEVEL_159_156");
	mpuss44xx_gic_dist_reg_table[i++].addr =
		OMAP4430_PRIORITY_LEVEL_159_156;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_3_0");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_3_0;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_7_4");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_7_4;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_11_8");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_11_8;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_15_12");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_15_12;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_31_28");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_31_28;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_35_32");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_35_32;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_39_36");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_39_36;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_43_40");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_43_40;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_47_44");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_47_44;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_51_48");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_51_48;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_55_52");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_55_52;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_59_56");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_59_56;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_63_60");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_63_60;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_67_64");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_67_64;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_71_68");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_71_68;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_75_72");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_75_72;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_79_76");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_79_76;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_83_80");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_83_80;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_87_84");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_87_84;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_91_88");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_91_88;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_95_92");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_95_92;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_99_96");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_99_96;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_103_100");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_103_100;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_107_104");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_107_104;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_111_108");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_111_108;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_115_112");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_115_112;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_119_116");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_119_116;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_123_120");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_123_120;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_127_124");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_127_124;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_131_128");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_131_128;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_135_132");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_135_132;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_139_136");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_139_136;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_143_140");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_143_140;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_147_144");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_147_144;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_151_148");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_151_148;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_155_152");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_155_152;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_TARGET_159_156");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_TARGET_159_156;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "INT_CONFIG_15_0");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_INT_CONFIG_15_0;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "INT_CONFIG_31_16");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_INT_CONFIG_31_16;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "INT_CONFIG_47_32");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_INT_CONFIG_47_32;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "INT_CONFIG_63_48");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_INT_CONFIG_63_48;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "INT_CONFIG_79_64");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_INT_CONFIG_79_64;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "INT_CONFIG_95_80");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_INT_CONFIG_95_80;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "INT_CONFIG_111_96");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_INT_CONFIG_111_96;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "INT_CONFIG_127_112");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_INT_CONFIG_127_112;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "INT_CONFIG_143_128");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_INT_CONFIG_143_128;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "INT_CONFIG_159_144");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_INT_CONFIG_159_144;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PPI_STATUS");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_PPI_STATUS;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_STATUS_31_0");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_STATUS_31_0;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_STATUS_63_32");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_STATUS_63_32;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_STATUS_95_64");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_STATUS_95_64;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SPI_STATUS_127_96");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SPI_STATUS_127_96;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "SGI_TRIGGER");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_SGI_TRIGGER;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PERIPH_ID_4");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_PERIPH_ID_4;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PERIPH_ID_0");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_PERIPH_ID_0;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PERIPH_ID_1");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_PERIPH_ID_1;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PERIPH_ID_2");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_PERIPH_ID_2;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "PERIPH_ID_3");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_PERIPH_ID_3;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "COMPONENT_ID_0");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_COMPONENT_ID_0;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "COMPONENT_ID_1");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_COMPONENT_ID_1;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "COMPONENT_ID_2");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_COMPONENT_ID_2;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "COMPONENT_ID_3");
	mpuss44xx_gic_dist_reg_table[i++].addr = OMAP4430_COMPONENT_ID_3;
	strcpy(mpuss44xx_gic_dist_reg_table[i].name, "END");
	mpuss44xx_gic_dist_reg_table[i].addr = 0;
	dprintf("mpuss44xx_gic_dist_reg_table last index=%d, size=%d\n",
		i, i + 1);

	/* Init MPUSS WKG registers table */
	i = 0;
	strcpy(mpuss44xx_wkg_reg_table[i].name, "WKG_CONTROL_0");
	mpuss44xx_wkg_reg_table[i++].addr = OMAP4430_WKG_CONTROL_0;
	strcpy(mpuss44xx_wkg_reg_table[i].name, "WKG_ENB_A_0");
	mpuss44xx_wkg_reg_table[i++].addr = OMAP4430_WKG_ENB_A_0;
	strcpy(mpuss44xx_wkg_reg_table[i].name, "WKG_ENB_B_0");
	mpuss44xx_wkg_reg_table[i++].addr = OMAP4430_WKG_ENB_B_0;
	strcpy(mpuss44xx_wkg_reg_table[i].name, "WKG_ENB_C_0");
	mpuss44xx_wkg_reg_table[i++].addr = OMAP4430_WKG_ENB_C_0;
	strcpy(mpuss44xx_wkg_reg_table[i].name, "WKG_ENB_D_0");
	mpuss44xx_wkg_reg_table[i++].addr = OMAP4430_WKG_ENB_D_0;
	strcpy(mpuss44xx_wkg_reg_table[i].name, "WKG_ENB_E_0");
	mpuss44xx_wkg_reg_table[i++].addr = OMAP4430_WKG_ENB_E_0;
	strcpy(mpuss44xx_wkg_reg_table[i].name, "WKG_CONTROL_1");
	mpuss44xx_wkg_reg_table[i++].addr = OMAP4430_WKG_CONTROL_1;
	strcpy(mpuss44xx_wkg_reg_table[i].name, "WKG_ENB_A_1");
	mpuss44xx_wkg_reg_table[i++].addr = OMAP4430_WKG_ENB_A_1;
	strcpy(mpuss44xx_wkg_reg_table[i].name, "WKG_ENB_B_1");
	mpuss44xx_wkg_reg_table[i++].addr = OMAP4430_WKG_ENB_B_1;
	strcpy(mpuss44xx_wkg_reg_table[i].name, "WKG_ENB_C_1");
	mpuss44xx_wkg_reg_table[i++].addr = OMAP4430_WKG_ENB_C_1;
	strcpy(mpuss44xx_wkg_reg_table[i].name, "WKG_ENB_D_1");
	mpuss44xx_wkg_reg_table[i++].addr = OMAP4430_WKG_ENB_D_1;
	strcpy(mpuss44xx_wkg_reg_table[i].name, "WKG_ENB_E_1");
	mpuss44xx_wkg_reg_table[i++].addr = OMAP4430_WKG_ENB_E_1;
	strcpy(mpuss44xx_wkg_reg_table[i].name, "AUX_CORE_BOOT_0");
	mpuss44xx_wkg_reg_table[i++].addr = OMAP4430_AUX_CORE_BOOT_0;
	strcpy(mpuss44xx_wkg_reg_table[i].name, "AUX_CORE_BOOT_1");
	mpuss44xx_wkg_reg_table[i++].addr = OMAP4430_AUX_CORE_BOOT_1;
	strcpy(mpuss44xx_wkg_reg_table[i].name, "END");
	mpuss44xx_wkg_reg_table[i].addr = 0;
	dprintf("mpuss44xx_wkg_reg_table last index=%d, size=%d\n", i, i + 1);

	/* Init MPUSS SCM registers table */
	i = 0;
	strcpy(mpuss44xx_scm_reg_table[i].name, "TZ_LOCKING");
	mpuss44xx_scm_reg_table[i++].addr = OMAP4430_TZ_LOCKING;
	strcpy(mpuss44xx_scm_reg_table[i].name, "SSM_SECMEM_STATUS");
	mpuss44xx_scm_reg_table[i++].addr = OMAP4430_SSM_SECMEM_STATUS;
	strcpy(mpuss44xx_scm_reg_table[i].name, "PLATFORM_STATUS");
	mpuss44xx_scm_reg_table[i++].addr = OMAP4430_PLATFORM_STATUS;
	strcpy(mpuss44xx_scm_reg_table[i].name, "SDP_PAGE_ACT");
	mpuss44xx_scm_reg_table[i++].addr = OMAP4430_SDP_PAGE_ACT;
	strcpy(mpuss44xx_scm_reg_table[i].name, "SDP_PAGE_RD");
	mpuss44xx_scm_reg_table[i++].addr = OMAP4430_SDP_PAGE_RD;
	strcpy(mpuss44xx_scm_reg_table[i].name, "SDP_PAGE_WR");
	mpuss44xx_scm_reg_table[i++].addr = OMAP4430_SDP_PAGE_WR;
	strcpy(mpuss44xx_scm_reg_table[i].name, "SDP_LRU_LIST_HIGH");
	mpuss44xx_scm_reg_table[i++].addr = OMAP4430_SDP_LRU_LIST_HIGH;
	strcpy(mpuss44xx_scm_reg_table[i].name, "SDP_LRU_LIST_LOW");
	mpuss44xx_scm_reg_table[i++].addr = OMAP4430_SDP_LRU_LIST_LOW;
	strcpy(mpuss44xx_scm_reg_table[i].name, "END");
	mpuss44xx_scm_reg_table[i].addr = 0;
	dprintf("mpuss44xx_scm_reg_table last index=%d, size=%d\n", i, i + 1);

	init_done = 1;
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION    mpuss44xx_name2addr
 * @BRIEF       retrieve physical address of a register, given its name.
 * @RETURNS     0 in case of success
 *	        OMAPCONF_ERR_CPU
 *	        OMAPCONF_ERR_ARG
 * @param[in,out]   name: register name
 * @param[in,out]   addr: register address
 * @DESCRIPTION retrieve physical address of a register, given its name.
 *//*------------------------------------------------------------------------ */
int mpuss44xx_name2addr(char *name, unsigned int *addr)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_ARG);

	if (!init_done)
		mpuss44xx_regtable_init();

	if (name2addr(name, addr, mpuss44xx_gic_dist_reg_table) == 0)
		return 0;
	if (name2addr(name, addr, mpuss44xx_gic_proc_reg_table) == 0)
		return 0;
	if (name2addr(name, addr,
		(reg_table *) omap4_mpuss_pl310_reg_table) == 0)
		return 0;
	if (name2addr(name, addr, mpuss44xx_scu_reg_table) == 0)
		return 0;
	if (name2addr(name, addr, mpuss44xx_wkg_reg_table) == 0)
		return 0;
	if (name2addr(name, addr, mpuss44xx_scm_reg_table) == 0)
		return 0;
	else
		return OMAPCONF_ERR_ARG;
}
