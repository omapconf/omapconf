/*
 *
 * @Component			OMAPCONF
 * @Filename			clkdm_dependency54xx.c
 * @Description			OMAP5 Clock Domain Dependencies Definitions &
 *				Functions
 * @Author			Patrick Titiano (p-titiano@ti.com)
 * @Date			2012
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
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


#include <clkdm_dependency54xx.h>
#include <lib.h>
#include <cm54xx.h>
#include <clkdm54xx.h>
#include <cpuinfo.h>
#include <autoadjust_table.h>
#include <help.h>
#include <reg.h>


/* #define CLKDMDEP54XX_DEBUG */
#ifdef CLKDMDEP54XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdmdep54xx_register_get
 * @BRIEF		return the dependency register physical address.
 * @RETURNS		NULL in case of error
 *			register physical address otherwise
 * @param[in]		id: clock domain ID
 * @param[in]		type: static or dynamic
 * @DESCRIPTION		return the dependency register physical address.
 *//*------------------------------------------------------------------------ */
const reg *clkdmdep54xx_register_get(clkdm54xx_id id, clkdmdep_type type)
{
	CHECK_ARG_LESS_THAN(id, CLKDM54XX_ID_MAX, NULL);
	CHECK_ARG_LESS_THAN(type, CLKDMDEP_TYPE_MAX, NULL);

	if (cpu_revision_get() == REV_ES1_0) {
		dprintf("%s(%u (%s), %u (%s)) = %s (0x%08X)\n", __func__,
			id, clkdm54xx_name_get(id), type, clkdmdep_type_name_get(type),
			reg_name_get((reg *) clkdmdep54xxes1_reg_table[id][type]),
			reg_addr_get((reg *) clkdmdep54xxes1_reg_table[id][type]));

		return clkdmdep54xxes1_reg_table[id][type];
	} else {
		dprintf("%s(%u (%s), %u (%s)) = %s (0x%08X)\n", __func__,
			id, clkdm54xx_name_get(id), type, clkdmdep_type_name_get(type),
			reg_name_get((reg *) clkdmdep54xx_reg_table[id][type]),
			reg_addr_get((reg *) clkdmdep54xx_reg_table[id][type]));

		return clkdmdep54xx_reg_table[id][type];
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdmdep54xx_bit_pos_get
 * @BRIEF		return the position of the dependency control bit in
 *			register
 * @RETURNS		position of the dependency control bit in register
 *			(0 <= pos <32)
 *			-1 if does not exist or in case of error
 * @param[in]		id: target clock domain ID
 * @DESCRIPTION		return the position of the dependency control bit in
 *			register
 *//*------------------------------------------------------------------------ */
short clkdmdep54xx_bit_pos_get(clkdm54xx_id id)
{
	short pos;

	CHECK_ARG_LESS_THAN(id, CLKDM54XX_ID_MAX, -1);

	if (cpu_revision_get() == REV_ES1_0)
		pos = clkdmdep54xxes1_bit_pos_table[id];
	else
		pos = clkdmdep54xx_bit_pos_table[id];
	dprintf("%s(%s)=%d\n", __func__, clkdm54xx_name_get(id), pos);

	return pos;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdmdep54xx_dump
 * @BRIEF		dump all static dependency registers content
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump all static dependency registers content
 *//*------------------------------------------------------------------------ */
int clkdmdep54xx_dump(FILE *stream)
{
	clkdm54xx_id id;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row, cm_dep;
	reg *r;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(stream, OMAPCONF_ERR_ARG);

	row = 0;
	autoadjust_table_init(table);

	strncpy(table[row][0], "Reg. Name", TABLE_MAX_ELT_LEN);
	strncpy(table[row][1], "Reg. Addr",
		TABLE_MAX_ELT_LEN);
	strncpy(table[row][2], "Reg. Val.", TABLE_MAX_ELT_LEN);
	row++;

	/* Browse all clock domains */
	for (id = 0; id < CLKDM54XX_ID_MAX; id++) {
		r = (reg *) clkdmdep54xx_register_get(id, CLKDMDEP_STATIC);
		if (r == NULL)
			goto clkdmdep54xx_dump_dynamic;

		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "%s",
			reg_name_get(r));
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "0x%08X",
			reg_addr_get(r));
		cm_dep = reg_read(r);
		snprintf(table[row++][2], TABLE_MAX_ELT_LEN, "0x%08X", cm_dep);

clkdmdep54xx_dump_dynamic:
		r = (reg *) clkdmdep54xx_register_get(id, CLKDMDEP_DYNAMIC);
		if (r == NULL)
			continue;

		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "%s",
			reg_name_get(r));
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "0x%08X",
			reg_addr_get(r));
		cm_dep = reg_read(r);
		snprintf(table[row++][2], TABLE_MAX_ELT_LEN, "0x%08X", cm_dep);
	}

	autoadjust_table_fprint(stream, table, row, 3);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdmdep54xx_has_dependency_towards_it
 * @BRIEF		indicate if clock domain can be dependent on another one
 * @RETURNS		1 if clock domain is dependent on another one
 *			0 if clock domain is NOT dependent on another one
 *			OMAPCONF_ERR_ARG
 * @param[in]		id: clock domain ID
 * @DESCRIPTION		indicate if clock domain can be dependent on another one
 *//*------------------------------------------------------------------------ */
int clkdmdep54xx_has_dependency_towards_it(clkdm54xx_id id)
{
	short int flag;
	CHECK_ARG_LESS_THAN(id, CLKDM54XX_ID_MAX, OMAPCONF_ERR_ARG);

	if (cpu_revision_get() == REV_ES1_0)
		flag = clkdmdep54xxes1_bit_pos_table[id];
	else
		flag = clkdmdep54xx_bit_pos_table[id];
	if (flag != -1)
		return 1;
	else
		return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdmdep54xx_dep_get
 * @BRIEF		return dependency from 'from' clock domain towards 'to'
 *			domain.
 * @RETURNS		dependency from 'from' clock domain towards 'to' domain.
 *			CLKDMDEP_CONTROL_TYPE_MAX in case of error
 * @param[in]		from: master clock domain ID
 * @param[in]		to: target clock domain ID
 * @param[in]		type: dependency type
 * @DESCRIPTION		return dependency from 'from' clock domain towards 'to'
 *			domain.
 *//*------------------------------------------------------------------------ */
clkdmdep_ctrl_type clkdmdep54xx_dep_get(
	clkdm54xx_id from, clkdm54xx_id to, clkdmdep_type type)
{
	CHECK_ARG_LESS_THAN(from, CLKDM54XX_ID_MAX, CLKDMDEP_CONTROL_TYPE_MAX);
	CHECK_ARG_LESS_THAN(to, CLKDM54XX_ID_MAX, CLKDMDEP_CONTROL_TYPE_MAX);
	CHECK_ARG_LESS_THAN(type, CLKDMDEP_TYPE_MAX, CLKDMDEP_CONTROL_TYPE_MAX);

	if (cpu_revision_get() == REV_ES1_0) {
		if (type == CLKDMDEP_STATIC)
			return  clkdmdep54xxes1_statdep_table[from][to];
		else
			return  clkdmdep54xxes1_dyndep_table[from][to];
	} else {
		if (type == CLKDMDEP_STATIC)
			return  clkdmdep54xx_statdep_table[from][to];
		else
			return  clkdmdep54xx_dyndep_table[from][to];
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdmdep54xx_dep_exists
 * @BRIEF		indicate if there is a dependency between the 2 given
 *			clock domains.
 * @RETURNS		1 there is a dependency between these 2 clock domains
 *			0 there is NO dependency between these 2 clock domains
 * @param[in]		from: clock domain ID
 * @param[in]		to: clock domain ID
 * @param[in]		type: dependency type
 * @DESCRIPTION		indicate if there is a dependency between the 2 given
 *			clock domains.
 *//*------------------------------------------------------------------------ */
unsigned short clkdmdep54xx_dep_exists(
	clkdm54xx_id from, clkdm54xx_id to, clkdmdep_type type)
{
	unsigned short ret;

	CHECK_ARG_LESS_THAN(from, CLKDM54XX_ID_MAX, 0);
	CHECK_ARG_LESS_THAN(to, CLKDM54XX_ID_MAX, 0);
	CHECK_ARG_LESS_THAN(type, CLKDMDEP_TYPE_MAX, 0);

	switch (clkdmdep54xx_dep_get(from, to, type)) {
	case CLKDMDEP_RW:
	case CLKDMDEP_RO:
		ret = 1;
		break;

	case CLKDMDEP_NA:
	case CLKDMDEP_CONTROL_TYPE_MAX:
	default:
		ret = 0;
	}

	dprintf("%s(%s, %s, %s)=%u (clkdmdep54xx_dep_get()=%s)\n",
		__func__, clkdm54xx_name_get(from),
		clkdm54xx_name_get(to),
		clkdmdep_type_name_get(type),
		ret, clkdmdep_ctrl_type_name_get(
			clkdmdep54xx_dep_get(from, to, type)));
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdmdep54xx_is_enabled
 * @BRIEF		check if a dependency between 2 clock domains is enabled
 *			or not.
 * @RETURNS		1 if dependency is enabled
 *			0 if dependency is disabled (or in case of error)
 * @param[in]		from: clock domain ID
 * @param[in]		to: clock domain ID
 * @param[in]		type: static or dynamic
 * @DESCRIPTION		check if a dependency between 2 clock domains is enabled
 *			or not.
 *//*------------------------------------------------------------------------ */
unsigned short clkdmdep54xx_is_enabled(
	clkdm54xx_id from, clkdm54xx_id to, clkdmdep_type type)
{
	unsigned short enabled;
	reg *cm_dep_reg;
	unsigned int cm_dep;
	short pos;

	CHECK_CPU(54xx, 0);
	CHECK_ARG_LESS_THAN(from, CLKDM54XX_ID_MAX, 0);
	CHECK_ARG_LESS_THAN(to, CLKDM54XX_ID_MAX, 0);
	CHECK_ARG_LESS_THAN(type, CLKDMDEP_TYPE_MAX, 0);


	/* Get dependency register */
	cm_dep_reg = (reg *) clkdmdep54xx_register_get(from, type);
	if (cm_dep_reg == NULL) {
		/* Dependency does not exist */
		dprintf("%s(%s, %s, %s): does not exist.\n", __func__,
			clkdm54xx_name_get(from), clkdm54xx_name_get(to),
			clkdmdep_type_name_get(type));
		return 0;
	}

	/* Read Register */
	cm_dep = reg_read(cm_dep_reg);

	/* Get Dependency control bit position from register */
	enabled = 0;
	pos = clkdmdep54xx_bit_pos_get(to);
	if (pos != -1)
		enabled = extract_bit(cm_dep, pos);

	dprintf("%s(%s, %s, %s): cm_dep=0x%08X pos=%d, enabled=%d\n",
		__func__, clkdm54xx_name_get(from), clkdm54xx_name_get(to),
		clkdmdep_type_name_get(type), cm_dep, pos, enabled);
	return enabled;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdmdep54xx_is_read_only
 * @BRIEF		indicate if a dependency between 2 given
 *			clock domains is SW-configurable or hard-coded.
 * @RETURNS		1 static dependency is read-only (hard-coded)
 *			(or in case of error)
 *			0 static dependency is SW-configurable
 * @param[in]		from: clock domain ID
 * @param[in]		to: clock domain ID
 * @param[in]		type: static or dynamic
 * @DESCRIPTION		indicate if a dependency between 2 given
 *			clock domains is SW-configurable or hard-coded.
 *//*------------------------------------------------------------------------ */
unsigned short clkdmdep54xx_is_read_only(
	clkdm54xx_id from, clkdm54xx_id to, clkdmdep_type type)
{
	unsigned short read_only;

	CHECK_ARG_LESS_THAN(from, CLKDM54XX_ID_MAX, 1);
	CHECK_ARG_LESS_THAN(to, CLKDM54XX_ID_MAX, 1);
	CHECK_ARG_LESS_THAN(type, CLKDMDEP_TYPE_MAX, 1);

	if (clkdmdep54xx_dep_get(from, to, type) == CLKDMDEP_RW)
		read_only = 0;
	else
		read_only = 1;

	dprintf("%s(%s, %s, %s)=%u\n",
		__func__, clkdm54xx_name_get(from), clkdm54xx_name_get(to),
		clkdmdep_type_name_get(type), read_only);
	return read_only;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdmdep54xx_statdep_set
 * @BRIEF		clear/set given static dependency.
 * @RETURNS		0 in case of success
 *			-1 in case of error (statdep. does not exist, read-only,
 *			bad args/cpu, etc ...)
 * @param[in]		from: clock domain ID
 * @param[in]		to: clock domain ID
 * @param[in]		enable: 0 to clear, 1 to set static dependency.
 * @DESCRIPTION		clear/set given static dependency.
 *//*------------------------------------------------------------------------ */
int clkdmdep54xx_statdep_set(clkdm54xx_id from, clkdm54xx_id to, int enable)
{
	reg *cm_dep_reg;
	unsigned int cm_dep;
	short bitpos;

	CHECK_CPU(54xx, -1);
	CHECK_ARG_LESS_THAN(from, CLKDM54XX_ID_MAX, -1);
	CHECK_ARG_LESS_THAN(to, CLKDM54XX_ID_MAX, -1);

	/* Check dependency control type / existence */
	if (clkdmdep54xx_dep_get(from, to, CLKDMDEP_STATIC) != CLKDMDEP_RW)
		return -1;

	cm_dep_reg = (reg *) clkdmdep54xx_register_get(from, CLKDMDEP_STATIC);
	if (cm_dep_reg == NULL)
		return -1;

	/* Read register content */
	cm_dep = reg_read(cm_dep_reg);

	/* Get position of the statdep control bit to update */
	bitpos = clkdmdep54xx_bit_pos_get(to);

	/* Update register content */
	if (enable)
		cm_dep |= (1 << bitpos);
	else
		cm_dep &= ~(1 << bitpos);

	/* Save updated register content */
	return reg_write(cm_dep_reg, cm_dep);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdmdep54xx_show
 * @BRIEF		show complete clock domain dependencies configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output stream
 * @param[in]		type: dependency type
 *			if type == CLKDMDEP_TYPE_MAX, show static + dynamic.
 * @DESCRIPTION		show complete clock domain dependencies configuration
 *//*------------------------------------------------------------------------ */
int clkdmdep54xx_show(FILE *stream, clkdmdep_type type)
{
	clkdm54xx_id from, to;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row, col, max_col;
	int t;
	unsigned short enabled, read_only;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(stream, OMAPCONF_ERR_ARG);
	if (type > CLKDMDEP_TYPE_MAX) {
		fprintf(stderr, "%s(): type (%u) > CLKDMDEP_TYPE_MAX (%u)!!!\n",
			__func__, type, CLKDMDEP_TYPE_MAX);
		return OMAPCONF_ERR_ARG;
	}

	for (t = (int) CLKDMDEP_DYNAMIC; t >= (int) CLKDMDEP_STATIC; t--) {
		if ((type != (int) CLKDMDEP_TYPE_MAX) && (t != (int) type))
			continue;
		row = 0;
		autoadjust_table_init(table);

		/* Fill Table Header */
		max_col = 0;
		if (t == (int) CLKDMDEP_STATIC)
			autoadjust_table_strncpy(table, row, 0,
				"Static Dependency FROM");
		else
			autoadjust_table_strncpy(table, row, 0,
				"Dynamic Dependency FROM");
		for (from = CLKDM54XX_EMU; from < CLKDM54XX_NONE; from++) {
			if (clkdmdep54xx_register_get(from, t) == NULL)
				continue;

			max_col++;
			autoadjust_table_strncpy(table, row, max_col,
				(char *) clkdm54xx_name_get(from));
		}
		row++;
		autoadjust_table_strncpy(table, row++, 0, "TOWARDS");
		/* Browse dependencies and fill table */
		col = 0;
		for (to = CLKDM54XX_EMU; to < CLKDM54XX_NONE; to++) {
			if (clkdmdep54xx_has_dependency_towards_it(to) != 1)
				continue;

			snprintf(table[row][0], TABLE_MAX_ELT_LEN, "  %s",
				clkdm54xx_name_get(to));
			col = 0;
			for (from = CLKDM54XX_EMU; from < CLKDM54XX_NONE;
				from++) {
				if (clkdmdep54xx_register_get(from, t) == NULL)
					continue;

				col++;

				if (clkdmdep54xx_dep_exists(from, to, t) != 1)
					continue;
				enabled = clkdmdep54xx_is_enabled(from, to, t);
				read_only = clkdmdep54xx_is_read_only(
					from, to, t);
#if 1
				if ((read_only == 1) &&
					(t != CLKDMDEP_DYNAMIC)) {
					if (enabled == 0)
						autoadjust_table_strncpy(table,
							row, col, "Dis (RO)");
					else
						autoadjust_table_strncpy(table,
							row, col, "EN (RO)");
				} else {
					if (enabled == 0)
						autoadjust_table_strncpy(table,
							row, col, "Dis");
					else
						autoadjust_table_strncpy(table,
							row, col, "EN");
				}
#endif
			}
			row++;
		}

		autoadjust_table_print(table, row, max_col + 1);

		if (t == CLKDMDEP_STATIC) {
			printf("NB:\n"
				"  - EN = static dependency is ENabled.\n"
				"  - Dis = static dependency is Disabled.\n"
				"  - RO = Read-Only (hard-coded, not "
				"SW-configurable).\n"
				"  - Empty cell = static dependency "
				"does not exist.\n\n");
		} else {
			printf("NB:\n"
				"  - ALL Dynamic dependencies are Read-Only "
				"(hard-coded, not SW-configurable).\n\n");
		}
	}
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdmdep54xx_audit
 * @BRIEF		audit clock domain static dependencies configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output file - NULL: no output (silent)
 * @param[in,out]	err_nbr: pointer to return audit error number
 * @param[in,out]	wng_nbr: pointer to return audit warning number
 * @DESCRIPTION		audit clock domain static dependencies configuration
 *//*------------------------------------------------------------------------ */
int clkdmdep54xx_audit(FILE *stream, unsigned int *err_nbr,
	unsigned int *wng_nbr)
{
	clkdm54xx_id from, to;
	unsigned short enabled, read_only;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row, col, max_col;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(err_nbr, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(wng_nbr, OMAPCONF_ERR_ARG);
	*err_nbr = 0;
	*wng_nbr = 0;

	/* Fill Table Header */
	autoadjust_table_init(table);
	row = 0;
	max_col = 0;
	autoadjust_table_strncpy(table, row, 0, "Static Dependency AUDIT From");
	for (from = CLKDM54XX_EMU; from < CLKDM54XX_NONE; from++) {
		if (clkdmdep54xx_register_get(from, CLKDMDEP_STATIC) == NULL)
			continue;
		max_col++;
		autoadjust_table_strncpy(table, row, max_col,
			(char *) clkdm54xx_name_get(from));
	}
	row++;
	autoadjust_table_strncpy(table, row++, 0, "TOWARDS");

	/* Browse static dependencies */
	col = 0;
	for (to = CLKDM54XX_EMU; to < CLKDM54XX_NONE; to++) {
		if (clkdmdep54xx_has_dependency_towards_it(to) != 1)
			continue;

		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "  %s",
			clkdm54xx_name_get(to));
		col = 0;
		for (from = CLKDM54XX_EMU; from < CLKDM54XX_NONE; from++) {
			if (clkdmdep54xx_register_get(
				from, CLKDMDEP_STATIC) == NULL)
				continue;

			col++;

			if (clkdmdep54xx_dep_exists(
				from, to, CLKDMDEP_STATIC) != 1)
				continue;

			read_only = clkdmdep54xx_is_read_only(
				from, to, CLKDMDEP_STATIC);
			if (read_only == 1) {
				autoadjust_table_strncpy(
					table, row, col, "Ign. (RO)");
				continue;
			}

			enabled = clkdmdep54xx_is_enabled(
				from, to, CLKDMDEP_STATIC);
			if (!enabled) {
				autoadjust_table_strncpy(
					table, row, col, "Pass");
			} else {
				autoadjust_table_strncpy(
					table, row, col, "FAIL");
				(*err_nbr)++;
			}
		}
		row++;
	}

	if (stream != NULL) {
		autoadjust_table_fprint(stream, table, row, max_col + 1);
		fprintf(stream, "NB:\n"
			"  - ALL STATIC DEPENDENCIES expected to be DISABLED "
				"in FINAL product (except HW errata).\n"
			"  - Pass = static dependency setting correct.\n"
			"  - FAIL = static dependency setting incorrect.\n"
			"  - Ign. (RO) = ignored as static dependency is "
				"Read-Only.\n"
			"  - Empty cell = static dependency does not exist."
				"\n\n");

		if (*err_nbr == 0) {
			fprintf(stream, "SUCCESS! Static Dependency "
				"configuration audit completed with 0 error "
				"(%d warning(s))\n\n",
				*wng_nbr);
		} else {
			fprintf(stream, "FAILED! Static Dependency "
				"configuration audit completed with %d error(s)"
				" and %d warning(s).\n\n",
				*err_nbr, *wng_nbr);
		}
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdmdep54xx_set
 * @BRIEF		set/clear given static dependency
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in]		clkdm_from: name of the clock domain dependency is
 *			from (mandatory)
 *			List of clock domain names: cf clkdm54xx_s2id()
 * @param[in]		clkdm_to: name of the clock domain dependency is
 *			targeting. If clkdm_to == "all" or NULL,
 *			update all dependencies from "clkdm_from".
 *			List of clock domain names: cf clkdm54xx_s2id()
 * @param[in]		enable: set dependency if == 1, clear it if == 0.
 * @DESCRIPTION		set/clear given static dependency
 *//*------------------------------------------------------------------------ */
int clkdmdep54xx_set(char *clkdm_from, char *clkdm_to, unsigned short enable)
{
	int ret;
	clkdm54xx_id from, to, first, last;
	unsigned short all;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(clkdm_from, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(enable, 2, OMAPCONF_ERR_ARG)

	dprintf("%s(): clkdm_from = %s\n", __func__, clkdm_from);
	dprintf("%s(): clkdm_to = %s\n", __func__, clkdm_to);
	dprintf("%s(): enable = %d\n", __func__, enable);

	/* Retrieve "to" clock domain ID */
	if (clkdm_to == NULL) {
		first = CLKDM54XX_EMU;
		last = CLKDM54XX_NONE;
		all = 1;
	} else if ((strcmp(lowercase(clkdm_to), "all")) == 0) {
		first = CLKDM54XX_EMU;
		last = CLKDM54XX_NONE;
		all = 1;
	} else {
		to = clkdm54xx_s2id(clkdm_to);
		if (to == CLKDM54XX_ID_MAX) {
			dprintf("%s(): could not retrieve valid \"to\" "
				"clkdm ID from %s\n", __func__, clkdm_to);
			return err_arg_msg_show(HELP_STATDEP);
		}
		first = to;
		last = to + 1;
		all = 0;
	}
	dprintf("%s(): to=%s, first=%s, last=%s\n", __func__,
		clkdm54xx_name_get(to),
		clkdm54xx_name_get(first), clkdm54xx_name_get(last));

	/* Retrieve "from" clock domain ID */
	from = clkdm54xx_s2id(clkdm_from);
	if (from == CLKDM54XX_ID_MAX) {
		dprintf("%s(): could not retrieve valid \"from\" "
			"clkdm ID from %s\n", __func__, clkdm_from);
		return err_arg_msg_show(HELP_STATDEP);
	}
	dprintf("%s(): from = %s\n", __func__, clkdm54xx_name_get(from));

	for (to = first; to < last; to++) {
		/* Check static dependency presence, skip if doesn't exist */
		if (clkdmdep54xx_is_read_only(from, to, CLKDMDEP_STATIC) != 0) {
			if (all) {
				/* just skip it */
				continue;
			} else {

				if (clkdmdep54xx_dep_exists(from, to,
					CLKDMDEP_STATIC) != 1) {
					printf("Static Dependency from %s to %s"
						" does not exist!\n\n",
						clkdm54xx_name_get(from),
						clkdm54xx_name_get(to));
					return 0;
				} else if (clkdmdep54xx_is_read_only(from, to,
					CLKDMDEP_STATIC) == 1) {
					printf("Static Dependency from %s to %s"
						" is not SW-configurable!\n\n",
						clkdm54xx_name_get(from),
						clkdm54xx_name_get(to));
					return 0;
				}
			}
		}

		/* Update Static Dependency setting */
		ret = clkdmdep54xx_statdep_set(from, to, enable);
		if (ret == 0) {
			if (enable)
				printf("Static Dependency from %s to %s "
					"enabled.\n", clkdm54xx_name_get(from),
					clkdm54xx_name_get(to));
			else
				printf("Static Dependency from %s to %s "
					"disabled.\n", clkdm54xx_name_get(from),
					clkdm54xx_name_get(to));
		} else {
			printf("Failed to update Static Dependency from %s "
				"to %s!\n", clkdm54xx_name_get(from),
					clkdm54xx_name_get(to));
			return OMAPCONF_ERR_UNEXPECTED;
		}
	}

	printf("\nWarning: new setting(s) applied but may be overridden "
		"unconditionally by kernel driver(s).\n\n");
	return 0;
}
