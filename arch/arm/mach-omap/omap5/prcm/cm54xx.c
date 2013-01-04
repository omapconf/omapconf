/*
 *
 * @Component			OMAPCONF
 * @Filename			cm54xx.h
 * @Description			OMAP5 CM Registers Functions
 * @Author			Patrick Titiano (p-titiano@ti.com)
 * @Date			2011
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
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


#include <cm54xx.h>
#include <lib.h>
#include <autoadjust_table.h>
#include <module.h>
#include <prcm-module.h>
#include <cpuinfo.h>


/* #define CM54XX_DEBUG */
#ifdef CM54XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cm54xx_mod_name_get
 * @BRIEF		return CM module name
 * @RETURNS		CM module name
 *			NULL in case of incorrect id
 * @param[in]		id: CM module ID
 * @DESCRIPTION		return CM module name
 *//*------------------------------------------------------------------------ */
const char *cm54xx_mod_name_get(cm54xx_mod_id id)
{
	if (id >= CM54XX_MODS_COUNT) {
		fprintf(stderr, "%s(): id (%u) >= CM54XX_MODS_COUNT (%u)!\n",
			__func__, id, CM54XX_MODS_COUNT);
		return NULL;
	}

	return cm54xx_mods_name[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cm54xx_is_profiling_running
 * @BRIEF		return 1 if profiling module (CMI) is running,
 *			0 otherwise
 * @RETURNS		1 if profiling module (CMI) is running, 0 otherwise
 * @param[in]		id: instrumentation ID
 *			(CM54XX_INSTR_CM_CORE or CM54XX_INSTR_CM_CORE_AON)
 * @DESCRIPTION		return 1 if profiling module (CMI) is running,
 *			0 otherwise
 *//*------------------------------------------------------------------------ */
unsigned int cm54xx_is_profiling_running(cm54xx_mod_id id)
{
	reg *cm_clkctrl_reg;
	unsigned int cm_clkctrl;

	if (cpu_revision_get() == REV_ES1_0) {
		if (id == CM54XX_INSTR_CM_CORE_AON) {
			cm_clkctrl_reg =
				&omap5430es1_cm_cm_core_aon_profiling_clkctrl;
		} else if (id == CM54XX_INSTR_CM_CORE) {
			cm_clkctrl_reg =
				&omap5430es1_cm_cm_core_profiling_clkctrl;
		} else {
			fprintf(stderr,
				"%s(): called with incorrect ID (%s)!!!\n",
				__func__, cm54xx_mod_name_get(id));
			return 0;
		}
	} else {
		if (id == CM54XX_INSTR_CM_CORE_AON) {
			cm_clkctrl_reg =
				&omap5430_cm_cm_core_aon_profiling_clkctrl;
		} else if (id == CM54XX_INSTR_CM_CORE) {
			cm_clkctrl_reg =
				&omap5430_cm_cm_core_profiling_clkctrl;
		} else {
			fprintf(stderr,
				"%s(): called with incorrect ID (%s)!!!\n",
				__func__, cm54xx_mod_name_get(id));
			return 0;
		}
	}

	if (cm_clkctrl_reg == NULL) {
		fprintf(stderr, "omapconf: %s(): cm_clkctrl_reg == NULL!!!\n",
			__func__);
		return 0;
	}

	cm_clkctrl = reg_read(cm_clkctrl_reg);
	return mod_is_accessible(cm_clkctrl);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cm54xx_dump
 * @BRIEF		dump selected registers and pretty-print it in
 *			selected output stream
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output stream
 * @param[in]		id: CM module ID - If id == CM54XX_MODS_COUNT,
 *			dump all CM registers.
 * @DESCRIPTION		dump selected registers and pretty-print it in
 *			selected output stream
 *//*------------------------------------------------------------------------ */
int cm54xx_dump(FILE *stream, cm54xx_mod_id id)
{
	unsigned int i = 0, mid;
	unsigned int val = 0;
	int err = 0;
	reg **mod;
	reg *r;
	char s[TABLE_MAX_ELT_LEN];
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row;


	if (stream == NULL) {
		fprintf(stderr, "%s(): stream == NULL!!!\n", __func__);
		err = OMAPCONF_ERR_ARG;
		goto cm54xx_dump_end;
	}

	if (id > CM54XX_MODS_COUNT) {
		fprintf(stderr, "%s(): id (%u) > CM54XX_MODS_COUNT!!! (%u)\n",
			__func__, id, CM54XX_MODS_COUNT);
		err = OMAPCONF_ERR_ARG;
		goto cm54xx_dump_end;
	}

	autoadjust_table_init(table);
	row = 0;

	if (id != CM54XX_MODS_COUNT)
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "%s Reg. Name",
			cm54xx_mod_name_get(id));
	else
		strncpy(table[row][0], "CM Reg. Name", TABLE_MAX_ELT_LEN);
	strncpy(table[row][1], "Reg. Address",
		TABLE_MAX_ELT_LEN);
	strncpy(table[row][2], "Reg. Value", TABLE_MAX_ELT_LEN);
	row++;

	for (mid = CM54XX_DSS_CM_CORE; mid < CM54XX_MODS_COUNT; mid++) {
		if ((id != CM54XX_MODS_COUNT) && (mid != id))
			continue;
		else {
			if (cpu_revision_get() == REV_ES1_0)
				mod = cm54xxes1_mods[mid];
			else
				mod = cm54xx_mods[mid];
			for (i = 0; mod[i] != NULL; i++) {
				r = mod[i];
				/* Read register */
				val = reg_read(r);
				/* Show register name, addr & content */
				snprintf(s, TABLE_MAX_ELT_LEN, "%s", r->name);
				autoadjust_table_strncpy(table, row, 0, s);

				snprintf(s, TABLE_MAX_ELT_LEN, "0x%08X",
					r->addr);
				autoadjust_table_strncpy(table, row, 1, s);

				snprintf(s, TABLE_MAX_ELT_LEN, "0x%08X", val);
				autoadjust_table_strncpy(table, row++, 2, s);
			}
		}
	}

	autoadjust_table_print(table, row, 3);

cm54xx_dump_end:
	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cm54xx_export
 * @BRIEF		export module register content to file, in XML format.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_INTERNAL
 * @param[in,out]	fp: output file stream (opened for write operations)
 * @param[in]		id: CM module ID
 * @DESCRIPTION		export module register content to file, in XML format.
 *//*------------------------------------------------------------------------ */
int cm54xx_export(FILE *fp, cm54xx_mod_id id)
{
	reg **mod;
	unsigned int i;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(fp, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(id, CM54XX_MODS_COUNT, OMAPCONF_ERR_ARG);

	if ((cpu_revision_get() != REV_ES1_0) &&
		(id == CM54XX_L4PER_CM_CORE)) {
		fprintf(stderr, "omapconf: %s(): L4_PER does not exist!!!\n",
			__func__);
		return OMAPCONF_ERR_ARG;
	}

	dprintf("%s(): exporting CM %s (%u) module ...\n", __func__,
		cm54xx_mod_name_get(id), id);

	if (cpu_revision_get() == REV_ES1_0)
		mod = cm54xxes1_mods[id];
	else
		mod = cm54xx_mods[id];
	if (mod == NULL) {
		fprintf(stderr, "omapconf: %s(): mod == NULL!!!\n", __func__);
		return OMAPCONF_ERR_INTERNAL;
	}

	if ((id == CM54XX_INSTR_CM_CORE) &&
		!cm54xx_is_profiling_running(CM54XX_INSTR_CM_CORE)) {
		dprintf(
			"%s(%s): CM module is not accessible, don't export registers\n",
			__func__, cm54xx_mod_name_get(id));
		return 0;
	} else if ((id == CM54XX_INSTR_CM_CORE_AON) &&
		!cm54xx_is_profiling_running(CM54XX_INSTR_CM_CORE_AON)) {
		dprintf(
			"%s(%s): CM module is not accessible, don't export registers\n",
			__func__, cm54xx_mod_name_get(id));
		return 0;
	}

	fprintf(fp, "          <submodule id=\"%u\" name=\"%s\">\n",
		id, cm54xx_mod_name_get(id));

	for (i = 0; mod[i] != NULL; i++)
		fprintf(fp,
			"            <register id=\"%u\" name=\"%s\" addr=\"0x%08X\" data=\"0x%08X\" />\n",
			i, reg_name_get(mod[i]), reg_addr_get(mod[i]),
			reg_read(mod[i]));

	fprintf(fp, "          </submodule>\n");
	fflush(fp);

	dprintf("%s(): CM %s (%u) module exported.\n", __func__,
		cm54xx_mod_name_get(id), id);
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cm54xx_import
 * @BRIEF		import OMAP CM registers from XML file
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in,out]	fp: XML import file descriptor
 * @param[in]		id: CM module ID
 * @DESCRIPTION		import OMAP CM registers from XML file,
 *			generated with lib54xx_export().
 *//*------------------------------------------------------------------------ */
int cm54xx_import(FILE *fp, cm54xx_mod_id id)
{
	reg **mod;
	char line[256], sline[256];
	char *xml_entry;
	int ret, i, n;

	CHECK_NULL_ARG(fp, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(id, CM54XX_MODS_COUNT, OMAPCONF_ERR_ARG);

	if (cpu_revision_get() == REV_ES1_0)
		mod = cm54xxes1_mods[id];
	else
		mod = cm54xx_mods[id];
	rewind(fp);

	/* Search for the CM module tag */
	sprintf(sline, "<submodule id=\"%u\" name=\"%s\">",
		id, cm54xx_mod_name_get(id));
	while (fgets(line, sizeof(line), fp) != NULL) {
		if (strstr(line, sline) == NULL)
			continue;
		/* Import register content */
		for (i = 0; mod[i] != NULL; i++) {
			if (fgets(line, sizeof(line), fp) == NULL)
				return OMAPCONF_ERR_UNEXPECTED;
			line[strlen(line) - 1] = '\0'; /* remove ending '\n' */
			xml_entry = strstr(line, "<"); /* remove spaces */

			dprintf("%s(%u (%s)): xml_entry=%s\n", __func__, id,
				cm54xx_mod_name_get(id), xml_entry);

			/* Check register id is correct */
			ret = sscanf(xml_entry, "<register id=\"%u\" %s",
				&n, sline);
			if (ret != 2) {
				dprintf("%s(%u (%s)): could not get id\n",
					__func__, id, cm54xx_mod_name_get(id));
				return OMAPCONF_ERR_UNEXPECTED;
			}
			if (n != i) {
				dprintf(
					"%s(%u (%s)): register id does not match! (n=%u, i=%u)\n",
					__func__, id,
					cm54xx_mod_name_get(id), n, i);
				return OMAPCONF_ERR_UNEXPECTED;
			}

			ret = reg_xml_import(mod[i], xml_entry);
			if (ret != 0)
				return ret;
		}
		dprintf("%s(%u (%s)): all registers imported.\n", __func__, id,
			cm54xx_mod_name_get(id));
		break;
	}

	return 0;
}
