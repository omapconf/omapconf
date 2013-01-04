/*
 *
 * @Component			OMAPCONF
 * @Filename			prm54xx.h
 * @Description			OMAP5 PRM Registers Functions
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


#include <prm54xx.h>
#include <cm54xx.h>
#include <lib.h>
#include <autoadjust_table.h>
#include <cpuinfo.h>
#include <module54xx.h>


/* #define PRM54XX_DEBUG */
#ifdef PRM54XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		prm54xx_mod_name_get
 * @BRIEF		return PRM module name
 * @RETURNS		PRM module name
 *			NULL in case of incorrect id
 * @param[in]		id: PRM module ID
 * @DESCRIPTION		return PRM module name
 *//*------------------------------------------------------------------------ */
const char *prm54xx_mod_name_get(prm54xx_mod_id id)
{
	if (id >= PRM54XX_MODS_COUNT) {
		fprintf(stderr, "%s(): id (%u) >= PRM54XX_MODS_COUNT (%u)!\n",
			__func__, id, PRM54XX_MODS_COUNT);
		return NULL;
	}

	return prm54xx_mods_name[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		prm54xx_is_profiling_running
 * @BRIEF		return 1 if profiling module (PMI) is running,
 *			0 otherwise
 * @RETURNS		1 if profiling module (PMI) is running,
 *			0 otherwise
 * @DESCRIPTION		return 1 if profiling module (PMI) is running,
 *			0 otherwise
 *//*------------------------------------------------------------------------ */
unsigned int prm54xx_is_profiling_running(void)
{
	reg *cm_clkctrl_reg;
	unsigned int cm_clkctrl;

	if (cpu_revision_get() == REV_ES1_0)
		cm_clkctrl_reg = &omap5430es1_cm_prm_profiling_clkctrl;
	else
		cm_clkctrl_reg = &omap5430_cm_prm_profiling_clkctrl;

	if (cm_clkctrl_reg == NULL) {
		dprintf("%s(): cm_clkctrl_reg == NULL!!!\n", __func__);
		return 0;
	}

	cm_clkctrl = reg_read(cm_clkctrl_reg);
	return mod_is_accessible(cm_clkctrl);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		prm54xx_dump
 * @BRIEF		dump selected registers and pretty-print it in
 *			selected output stream
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in,out]		stream: output stream
 * @param[in]		id: PRM module ID - If id == PRM54XX_MODS_COUNT,
 *			dump all PRM registers.
 * @DESCRIPTION		dump selected registers and pretty-print it in
 *			selected output stream
 *//*------------------------------------------------------------------------ */
int prm54xx_dump(FILE *stream, prm54xx_mod_id id)
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
		goto prm54xx_dump_end;
	}

	if (id > PRM54XX_MODS_COUNT) {
		fprintf(stderr, "%s(): id (%u) > PRM54XX_MODS_COUNT!!! (%u)\n",
			__func__, id, PRM54XX_MODS_COUNT);
		err = OMAPCONF_ERR_ARG;
		goto prm54xx_dump_end;
	}

	autoadjust_table_init(table);
	row = 0;

	if (id != PRM54XX_MODS_COUNT)
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "%s Reg. Name",
			prm54xx_mod_name_get(id));
	else
		strncpy(table[row][0], "PRM Reg. Name", TABLE_MAX_ELT_LEN);
	strncpy(table[row][1], "Reg. Address",
		TABLE_MAX_ELT_LEN);
	strncpy(table[row][2], "Reg. Value", TABLE_MAX_ELT_LEN);
	row++;

	for (mid = PRM54XX_DSS_PRM; mid < PRM54XX_MODS_COUNT; mid++) {
		if ((id != PRM54XX_MODS_COUNT) && (mid != id))
			continue;
		else {
			if (cpu_revision_get() == REV_ES1_0)
				mod = prm54xxes1_mods[mid];
			else
				mod = prm54xx_mods[mid];
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

prm54xx_dump_end:
	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		prm54xx_export
 * @BRIEF		export module register content to file, in XML format.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_INTERNAL
 * @param[in,out]	fp: output file stream (opened for write operations)
 * @param[in]		id: PRM module ID
 * @DESCRIPTION		export module register content to file, in XML format.
 *//*------------------------------------------------------------------------ */
int prm54xx_export(FILE *fp, prm54xx_mod_id id)
{
	reg **mod;
	unsigned int i;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(fp, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(id, PRM54XX_MODS_COUNT, OMAPCONF_ERR_ARG);
	if ((cpu_revision_get() != REV_ES1_0) &&
		(id == PRM54XX_L4PER_PRM)) {
		fprintf(stderr, "omapconf: %s(): L4_PER does not exist!!!\n",
			__func__);
		return OMAPCONF_ERR_ARG;
	}

	dprintf("%s(): exporting PRM %s (%u) module ...\n", __func__,
		prm54xx_mod_name_get(id), id);

	if (cpu_revision_get() == REV_ES1_0)
		mod = prm54xxes1_mods[id];
	else
		mod = prm54xx_mods[id];
	if (mod == NULL) {
		fprintf(stderr, "omapconf: %s(): mod == NULL!!!\n", __func__);
		return OMAPCONF_ERR_INTERNAL;
	}

	if ((id == PRM54XX_INSTR_PRM) && !prm54xx_is_profiling_running()) {
		dprintf(
			"%s(%s): PRM module is not accessible, don't export registers\n",
			__func__, prm54xx_mod_name_get(id));
		return 0;
	}

	fprintf(fp, "          <submodule id=\"%u\" name=\"%s\">\n",
		id, prm54xx_mod_name_get(id));

	for (i = 0; mod[i] != NULL; i++)
		fprintf(fp,
			"            <register id=\"%u\" name=\"%s\" addr=\"0x%08X\" data=\"0x%08X\" />\n",
			i, reg_name_get(mod[i]), reg_addr_get(mod[i]),
			reg_read(mod[i]));

	fprintf(fp, "          </submodule>\n");
	fflush(fp);

	dprintf("%s(): PRM %s (%u) module exported.\n", __func__,
		cm54xx_mod_name_get(id), id);
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		prm54xx_import
 * @BRIEF		import OMAP PRM registers from XML file
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in,out]	fp: XML import file descriptor
 * @param[in]		id: CM module ID
 * @DESCRIPTION		import OMAP PRM registers from XML file,
 *			generated with lib54xx_export().
 *//*------------------------------------------------------------------------ */
int prm54xx_import(FILE *fp, prm54xx_mod_id id)
{
	reg **mod;
	char line[256], sline[256];
	char *xml_entry;
	int ret, i, n;

	CHECK_NULL_ARG(fp, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(id, PRM54XX_MODS_COUNT, OMAPCONF_ERR_ARG);

	if (cpu_revision_get() == REV_ES1_0)
		mod = prm54xxes1_mods[id];
	else
		mod = prm54xx_mods[id];
	rewind(fp);

	/* Search for the PRM module tag */
	sprintf(sline, "<submodule id=\"%u\" name=\"%s\">",
		id, prm54xx_mod_name_get(id));
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
				prm54xx_mod_name_get(id), xml_entry);

			/* Check register id is correct */
			ret = sscanf(xml_entry, "<register id=\"%u\" %s",
				&n, sline);
			if (ret != 2) {
				dprintf("%s(%u (%s)): could not get id\n",
					__func__, id, prm54xx_mod_name_get(id));
				return OMAPCONF_ERR_UNEXPECTED;
			}
			if (n != i) {
				dprintf(
					"%s(%u (%s)): register id does not match! (n=%u, i=%u)\n",
					__func__, id,
					prm54xx_mod_name_get(id), n, i);
				return OMAPCONF_ERR_UNEXPECTED;
			}

			ret = reg_xml_import(mod[i], xml_entry);
			if (ret != 0)
				return ret;
		}
		dprintf("%s(%u (%s)): all registers imported.\n", __func__, id,
			prm54xx_mod_name_get(id));
		break;
	}

	return 0;
}
