/*
 *
 * @Component			OMAPCONF
 * @Filename			emif54xx.c
 * @Description			OMAP5 EMIF Functions
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


#include <emif54xx.h>
#include <autoadjust_table.h>
#include <lib.h>
#include <cpuinfo.h>
#include <module.h>


/* #define EMIF54XX_DEBUG */
#ifdef EMIF54XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


const char *emif54xx_mods_name[EMIF54XX_MODS_COUNT] = {
	"EMIF1",
	"EMIF2"};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		emif54xx_mod_name_get
 * @BRIEF		return EMIF module name
 * @RETURNS		EMIF module name
 *			NULL in case of incorrect id
 * @param[in]		id: EMIF module ID
 * @DESCRIPTION		return EMIF module name
 *//*------------------------------------------------------------------------ */
const char *emif54xx_mod_name_get(emif54xx_mod_id id)
{
	if (id >= EMIF54XX_MODS_COUNT) {
		fprintf(stderr, "%s(): id (%u) >= EMIF54XX_MODS_COUNT (%u)!\n",
			__func__, id, EMIF54XX_MODS_COUNT);
		return NULL;
	}

	return emif54xx_mods_name[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		emif54xx_dump
 * @BRIEF		dump selected registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output stream
 * @param[in]		id: EMIF module ID
 *			If id == EMIF54XX_MODS_COUNT, dump all EMIF registers.
 * @DESCRIPTION		dump selected registers and pretty-print it in selected
 *			output stream
 *//*------------------------------------------------------------------------ */
int emif54xx_dump(FILE *stream, emif54xx_mod_id id)
{
	unsigned int i = 0, mid, accessible;
	unsigned int val = 0;
	int err = 0;
	reg **mod;
	reg *r;
	char s[TABLE_MAX_ELT_LEN];
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row;


	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(stream, OMAPCONF_ERR_ARG);

	if (id > EMIF54XX_MODS_COUNT) {
		fprintf(stderr, "%s(): id (%u) > EMIF54XX_MODS_COUNT!!! (%u)\n",
			__func__, id, EMIF54XX_MODS_COUNT);
		err = OMAPCONF_ERR_ARG;
		goto emif54xx_dump_end;
	}

	autoadjust_table_init(table);
	row = 0;

	if (id != EMIF54XX_MODS_COUNT)
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "%s Reg. Name",
			emif54xx_mod_name_get(id));
	else
		strncpy(table[row][0], "EMIF Reg. Name", TABLE_MAX_ELT_LEN);
	strncpy(table[row][1], "Reg. Address",
		TABLE_MAX_ELT_LEN);
	strncpy(table[row][2], "Reg. Value", TABLE_MAX_ELT_LEN);
	row++;

	for (mid = 0; mid < EMIF54XX_MODS_COUNT; mid++) {
		if ((id != EMIF54XX_MODS_COUNT) && (mid != id))
			continue;
		else {
			switch (mid) {
			case EMIF54XX_EMIF1:
				accessible = module_is_accessible(MOD_EMIF1);
				break;
			case EMIF54XX_EMIF2:
				accessible = module_is_accessible(MOD_EMIF2);
				break;
			default:
				accessible = 0;
			}

			if (!accessible) {
				printf("%s module is not running, registers not"
					" accessible.\n",
					emif54xx_mod_name_get(mid));
				return 0;
			}

			if (cpu_revision_get() == REV_ES1_0)
				mod = emif54xxes1_mods[mid];
			else
				mod = emif54xx_mods[mid];
			for (i = 0; mod[i] != NULL; i++) {
				r = mod[i];
				/* Read register */
				dprintf("%s(): read %s 0x%08X\n", __func__,
					r->name, r->addr);
				val = reg_read(r);
				dprintf("%s(): OK\n", __func__);
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

emif54xx_dump_end:
	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		emif54xx_export
 * @BRIEF		export module register content to file, in XML format.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in,out]	fp: output file stream (opened for write operations)
 * @param[in]		id: EMIF module ID
 * @DESCRIPTION		export module register content to file, in XML format.
 *//*------------------------------------------------------------------------ */
int emif54xx_export(FILE *fp, emif54xx_mod_id id)
{
	reg **mod;
	unsigned int i, accessible;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(fp, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(id, EMIF54XX_MODS_COUNT, OMAPCONF_ERR_ARG);

	switch (id) {
	case EMIF54XX_EMIF1:
		accessible = module_is_accessible(MOD_EMIF1);
		break;
	case EMIF54XX_EMIF2:
		accessible = module_is_accessible(MOD_EMIF2);
		break;
	default: /* should not happen as already checked just before ... */
		return OMAPCONF_ERR_INTERNAL;
	}

	if (!accessible) {
		printf("%s export: module not running, skipping "
			"registers export.\n", emif54xx_mod_name_get(id));
		return 0;
	}

	if (cpu_revision_get() == REV_ES1_0)
		mod = emif54xxes1_mods[id];
	else
		mod = emif54xx_mods[id];

	fprintf(fp, "          <submodule id=\"%u\" name=\"%s\">\n",
		id, emif54xx_mod_name_get(id));

	if (cpu_revision_get() == REV_ES1_0) {
		for (i = 0; i < OMAP5430ES1_EMIF1_MOD_REGCOUNT; i++)
			fprintf(fp, "            <register id=\"%u\" name=\"%s\" "
				"addr=\"0x%08X\" data=\"0x%08X\" />\n", i,
				(mod[i])->name, (mod[i])->addr, reg_read(mod[i]));
	} else {
		for (i = 0; i < OMAP5430_EMIF1_MOD_REGCOUNT; i++)
			fprintf(fp, "            <register id=\"%u\" name=\"%s\" "
				"addr=\"0x%08X\" data=\"0x%08X\" />\n", i,
				(mod[i])->name, (mod[i])->addr, reg_read(mod[i]));
	}

	fprintf(fp, "          </submodule>\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		emif54xx_import
 * @BRIEF		import OMAP EMIF registers from XML file
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in,out]	fp: XML import file descriptor
 * @param[in]		id: EMIF module ID
 * @DESCRIPTION		import OMAP EMIF registers from XML file,
 *			generated with lib54xx_export().
 *//*------------------------------------------------------------------------ */
int emif54xx_import(FILE *fp, emif54xx_mod_id id)
{
	reg **mod;
	char line[256], sline[256];
	char *xml_entry;
	int ret, i, n, regcount;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(fp, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(id, EMIF54XX_MODS_COUNT, OMAPCONF_ERR_ARG);

	if (cpu_revision_get() == REV_ES1_0)
		mod = emif54xxes1_mods[id];
	else
		mod = emif54xx_mods[id];
	rewind(fp);

	/* Search for the EMIF module tag */
	sprintf(sline, "<submodule id=\"%u\" name=\"%s\">",
		id, emif54xx_mod_name_get(id));
	while (fgets(line, sizeof(line), fp) != NULL) {
		if (strstr(line, sline) == NULL)
			continue;
		/* Import register content */
		if (cpu_revision_get() == REV_ES1_0) {
			regcount = OMAP5430ES1_EMIF1_MOD_REGCOUNT;
		} else { /* FIXME WITH ES2 */
			regcount = OMAP5430_EMIF1_MOD_REGCOUNT;
		}
		for (i = 0; i < regcount; i++) {
			if (fgets(line, sizeof(line), fp) == NULL)
				return OMAPCONF_ERR_UNEXPECTED;
			line[strlen(line) - 1] = '\0'; /* remove ending '\n' */
			xml_entry = strstr(line, "<"); /* remove spaces */

			dprintf("%s(%u (%s)): xml_entry=%s\n", __func__, id,
				emif54xx_mod_name_get(id), xml_entry);

			/* Check register id is correct */
			ret = sscanf(xml_entry, "<register id=\"%u\" %s",
				&n, sline);
			if (ret != 2) {
				dprintf("%s(%u (%s)): could not get id\n",
					__func__, id, emif54xx_mod_name_get(id));
				return OMAPCONF_ERR_UNEXPECTED;
			}
			if (n != i) {
				dprintf("%s(%u (%s)): register id does not "
					"match! (n=%u, i=%u)\n", __func__, id,
					emif54xx_mod_name_get(id), n, i);
				return OMAPCONF_ERR_UNEXPECTED;
			}

			ret = reg_xml_import(mod[i], xml_entry);
			if (ret != 0)
				return ret;
		}
		dprintf("%s(%u (%s)): all registers imported.\n", __func__, id,
			emif54xx_mod_name_get(id));
		break;
	}

	return 0;
}
