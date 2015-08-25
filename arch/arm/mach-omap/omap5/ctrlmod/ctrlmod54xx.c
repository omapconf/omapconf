/*
 *
 * @Component			OMAPCONF
 * @Filename			ctrlmod54xx.c
 * @Description			OMAP5 CONTROL MODULE Registers Definitions
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


#include <ctrlmod54xx.h>
#include <ctrlmod54xx-data.h>
#include <ctrlmod_core54xx-defs.h>
#include <ctrlmod_core_pad54xx-defs.h>
#include <ctrlmod_wkup54xx-defs.h>
#include <ctrlmod_wkup_pad54xx-defs.h>
#include <lib.h>
#include <cpuinfo.h>
#include <autoadjust_table.h>
#include <help.h>


/* #define CTRLMOD54XX_DEBUG */
#ifdef CTRLMOD54XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


reg **ctrlmod54xxes1_mods[CTRLMOD54XX_MODS_COUNT] = {
	(reg **) &omap5430es1_ctrl_module_core_mod,
	(reg **) &omap5430es1_ctrl_module_core_pad_mod,
	(reg **) &omap5430es1_ctrl_module_wkup_mod,
	(reg **) &omap5430_ctrl_module_wkup_pad_mod};


reg **ctrlmod54xx_mods[CTRLMOD54XX_MODS_COUNT] = {
	(reg **) &omap5430_ctrl_module_core_mod,
	(reg **) &omap5430_ctrl_module_core_pad_mod,
	(reg **) &omap5430_ctrl_module_wkup_mod,
	(reg **) &omap5430_ctrl_module_wkup_pad_mod};


const char *ctrlmod54xx_mods_name[CTRLMOD54XX_MODS_COUNT] = {
	"CONTROL MODULE CORE",
	"CONTROL MODULE CORE PAD",
	"CONTROL MODULE WKUP",
	"CONTROL MODULE WKUP PAD"};


typedef enum {
	CTRLMOD54XX_IDX_CORE,
	CTRLMOD54XX_IDX_CORE_PAD,
	CTRLMOD54XX_IDX_WKUP,
	CTRLMOD54XX_IDX_WKUP_PAD,
	CTRLMOD54XX_IDX_ALL,
	CTRLMOD54XX_IDX_MAX
} ctrlmod54xx_index;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		ctrlmod54xx_mod_name_get
 * @BRIEF		return module name
 * @RETURNS		module name
 *			NULL in case of incorrect id
 * @param[in]		id: module ID
 * @DESCRIPTION		return module name
 *//*------------------------------------------------------------------------ */
const char *ctrlmod54xx_mod_name_get(ctrlmod54xx_mod_id id)
{
	if (id >= CTRLMOD54XX_MODS_COUNT) {
		fprintf(stderr,
			"%s(): id (%u) >= CTRLMOD54XX_MODS_COUNT (%u)!\n",
			__func__, id, CTRLMOD54XX_MODS_COUNT);
		return NULL;
	}

	return ctrlmod54xx_mods_name[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		ctrlmod54xx_dump
 * @BRIEF		dump selected registers and pretty-print it in selected
 *			output stream
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output stream
 * @param[in]		id: module ID. If id == CTRLMOD54XX_MODS_COUNT,
 *			dump all registers.
 * @DESCRIPTION		dump selected registers and pretty-print it in selected
 *			output stream
 *//*------------------------------------------------------------------------ */
int ctrlmod54xx_dump(FILE *stream, ctrlmod54xx_mod_id id)
{
	unsigned int i = 0, mid;
	unsigned int val = 0;
	int err = 0;
	reg **mod;
	reg *r;
	char s[TABLE_MAX_ELT_LEN];
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	if (stream == NULL) {
		fprintf(stderr, "%s(): stream == NULL!!!\n", __func__);
		err = OMAPCONF_ERR_ARG;
		goto ctrlmod54xx_dump_end;
	}

	if (id > CTRLMOD54XX_MODS_COUNT) {
		fprintf(stderr,
			"%s(): id (%u) > CTRLMOD54XX_MODS_COUNT!!! (%u)\n",
			__func__, id, CTRLMOD54XX_MODS_COUNT);
		err = OMAPCONF_ERR_ARG;
		goto ctrlmod54xx_dump_end;
	}

	autoadjust_table_init(table);
	row = 0;

	if (id != CTRLMOD54XX_MODS_COUNT)
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "%s Reg. Name",
			ctrlmod54xx_mod_name_get(id));
	else
		strncpy(table[row][0], "CTRLMOD Reg. Name", TABLE_MAX_ELT_LEN);
	strncpy(table[row][1], "Reg. Address",
		TABLE_MAX_ELT_LEN);
	strncpy(table[row][2], "Reg. Value", TABLE_MAX_ELT_LEN);
	row++;

	for (mid = CTRLMOD54XX_CTRL_MODULE_CORE;
		mid < CTRLMOD54XX_MODS_COUNT; mid++) {
		if ((id != CTRLMOD54XX_MODS_COUNT) && (mid != id))
			continue;
		else {
			if (cpu_revision_get() == REV_ES1_0)
				mod = ctrlmod54xxes1_mods[mid];
			else
				mod = ctrlmod54xx_mods[mid];
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

ctrlmod54xx_dump_end:
	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		ctrlmod54xx_io_audit
 * @BRIEF		OMAP5 PADCONF/IO audit.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 * @param[in,out]	stream: output file - NULL: no output (silent)
 * @param[in,out]	err_nbr: pointer to return audit error number
 * @param[in,out]	wng_nbr: pointer to return audit warning number
 * @DESCRIPTION		OMAP5 PADCONF/IO audit.
 *//*------------------------------------------------------------------------ */
int ctrlmod54xx_io_audit(FILE *stream, unsigned int *err_nbr,
	unsigned int *wng_nbr)
{
	const char pass[5] = "pass";
	const char fail[5] = "FAIL";
	const char ignore[5] = "ign.";
	const char warning[5] = "warn";
	char *status = NULL;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row, i, j, curr, expected, max;
	ctrlmod54xx_golden_item *golden_values;
	reg **ctrlmod_regs;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(err_nbr, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(wng_nbr, OMAPCONF_ERR_ARG);

	*err_nbr = 0;
	*wng_nbr = 0;

	if (cpu_revision_get() != REV_ES1_0) {
		fprintf(stream,
			"No golden settings available for OMAP5430 ES2.x, sorry...\n\n");
		status = (char *) warning;
		(*wng_nbr)++;
		return OMAPCONF_ERR_CPU;
	}

	for (j = 0; j < 4; j++) {
		autoadjust_table_init(table);
		row = 0;
		switch (j) {
		case 0:
			snprintf(table[row][0], TABLE_MAX_ELT_LEN,
				"CONTROL MODULE CORE registers AUDIT");
			if (cpu_revision_get() == REV_ES1_0) {
				golden_values = (ctrlmod54xx_golden_item *)
					ctrlmod_core54xxes1_golden_values;
				ctrlmod_regs = omap5430es1_ctrl_module_core_mod;
				max = OMAP5430ES1_CTRL_MODULE_CORE_MOD_REGCOUNT;
			} else { /* FIXME WHEN ES2.0 targets available */
				golden_values = (ctrlmod54xx_golden_item *)
					ctrlmod_core54xxes1_golden_values;
				ctrlmod_regs = omap5430_ctrl_module_core_mod;
				max = OMAP5430_CTRL_MODULE_CORE_MOD_REGCOUNT;
			}
			break;
		case 1:
			snprintf(table[row][0], TABLE_MAX_ELT_LEN,
				"CONTROL MODULE CORE PADCONF Registers AUDIT");
			if (cpu_revision_get() == REV_ES1_0) {
				golden_values = (ctrlmod54xx_golden_item *)
					ctrlmod_core_pad54xxes1_golden_values;
				ctrlmod_regs =
					omap5430es1_ctrl_module_core_pad_mod;
				max = OMAP5430_CTRL_MODULE_CORE_PAD_MOD_REGCOUNT;
			} else {
				golden_values = (ctrlmod54xx_golden_item *)
					ctrlmod_core_pad54xxes1_golden_values;
				ctrlmod_regs =
					omap5430_ctrl_module_core_pad_mod;
				max = OMAP5430_CTRL_MODULE_CORE_PAD_MOD_REGCOUNT;
			}
			break;
		case 2:
			snprintf(table[row][0], TABLE_MAX_ELT_LEN,
				"CONTROL MODULE WKUP Registers AUDIT");
			if (cpu_revision_get() == REV_ES1_0) {
				golden_values = (ctrlmod54xx_golden_item *)
					ctrlmod_wkup54xxes1_golden_values;
				ctrlmod_regs = omap5430es1_ctrl_module_wkup_mod;
				max = OMAP5430ES1_CTRL_MODULE_WKUP_MOD_REGCOUNT;
			} else { /* FIXME WHEN ES2.0 targets available */
				golden_values = (ctrlmod54xx_golden_item *)
					ctrlmod_wkup54xxes1_golden_values;
				ctrlmod_regs = omap5430_ctrl_module_wkup_mod;
				max = OMAP5430ES1_CTRL_MODULE_WKUP_MOD_REGCOUNT;
			}
			break;
		case 3:
			snprintf(table[row][0], TABLE_MAX_ELT_LEN,
				"CONTROL MODULE WKUP PADCONF Registers AUDIT");
			if (cpu_revision_get() == REV_ES1_0) {
				golden_values = (ctrlmod54xx_golden_item *)
					ctrlmod_wkup_pad54xxes1_golden_values;
				ctrlmod_regs = omap5430_ctrl_module_wkup_pad_mod;
				max = OMAP5430_CTRL_MODULE_WKUP_PAD_MOD_REGCOUNT;
			} else { /* FIXME WHEN ES2.0 targets available */
				golden_values = (ctrlmod54xx_golden_item *)
					ctrlmod_wkup_pad54xxes1_golden_values;
				ctrlmod_regs = omap5430_ctrl_module_wkup_pad_mod;
				max = OMAP5430_CTRL_MODULE_WKUP_PAD_MOD_REGCOUNT;
			}
			break;

		}
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "Current");
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "Expected");
		snprintf(table[row++][3], TABLE_MAX_ELT_LEN, "STATUS");

		for (i = 0; i < max; i++) {
			/* Read register */
			curr = reg_read(ctrlmod_regs[i]);

			/* Store name & register read content in table */
			snprintf(table[row][0], TABLE_MAX_ELT_LEN, "%s",
				(ctrlmod_regs[i])->name);
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "0x%08X",
				curr);

			/* Compare to golden value */
			switch (golden_values[i].valid) {
			case DATA_INVALID:
			case DATA_TBD:
				status = (char *) warning;
				(*wng_nbr)++;
				snprintf(table[row][2], TABLE_MAX_ELT_LEN,
					"   TBD");
				break;

			case DATA_VALID:
				expected = golden_values[i].golden_value;
				snprintf(table[row][2], TABLE_MAX_ELT_LEN,
					"0x%08X", expected);
				if (curr != expected) {
					status = (char *) fail;
					(*err_nbr)++;
				} else {
					status = (char *) pass;
				}
				break;

			case DATA_IGNORE:
				status = (char *) ignore;
				break;

			default:
				fprintf(stderr,
					"%s(): something's wrong here?! (j=%u, "
					"i=%u, golden_values[i].valid=%u)\n",
					__func__, j, i,	golden_values[i].valid);
			}
			/* Store status in table */
			snprintf(table[row++][3], TABLE_MAX_ELT_LEN, "%s",
				status);
		}

		if (stream != NULL) {
			autoadjust_table_fprint(stream, table, row, 4);
			fprintf(stream, " ### WARNING: PRELIMINARY ###\n");
			fprintf(stream, " ### GOLDEN VALUES STILL TO BE "
				"VERIFIED/COMPLETED!!! ###\n\n");
		}
	}

	/* Print audit results summary */
	if (stream != NULL) {
		if (*err_nbr == 0)
			fprintf(stream, "\nSUCCESS! Clock Speed audit "
				"completed with 0 error (%d warning(s))\n\n",
				*wng_nbr);
		else
			fprintf(stream, "\nFAILED! Clock Speed audit "
				"completed with %d error and %d warning.\n\n",
				*err_nbr, *wng_nbr);
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		ctrlmod54xx_export
 * @BRIEF		export CONTROL MODULE registers content to file, in
 *			XML format.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	fp: output file stream (opened for write operations)
 * @param[in]		id: module ID
 * @DESCRIPTION		export CONTROL MODULE registers content to file, in
 *			XML format.
 *//*------------------------------------------------------------------------ */
int ctrlmod54xx_export(FILE *fp, ctrlmod54xx_mod_id id)
{
	reg **mod;
	unsigned int i;

	CHECK_NULL_ARG(fp, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(id, CTRLMOD54XX_MODS_COUNT, OMAPCONF_ERR_ARG);

	if (cpu_revision_get() == REV_ES1_0)
		mod = ctrlmod54xxes1_mods[id];
	else
		mod = ctrlmod54xx_mods[id];
	fprintf(fp, "          <submodule id=\"%u\" name=\"%s\">\n",
		id, ctrlmod54xx_mod_name_get(id));

	for (i = 0; mod[i] != NULL; i++)
		fprintf(fp, "            <register id=\"%u\" name=\"%s\" "
			"addr=\"0x%08X\" data=\"0x%08X\" />\n", i,
			(mod[i])->name, (mod[i])->addr, reg_read(mod[i]));

	fprintf(fp, "          </submodule>\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		ctrlmod54xx_import
 * @BRIEF		import CONTROL MODULE registers from XML file
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in,out]	fp: XML import file descriptor
 * @param[in]		id: module ID
 * @DESCRIPTION		import CONTROL MODULE registers from XML file,
 *			generated with lib54xx_export().
 *//*------------------------------------------------------------------------ */
int ctrlmod54xx_import(FILE *fp, ctrlmod54xx_mod_id id)
{
	reg **mod;
	char line[256], sline[256];
	char *xml_entry;
	int ret, i, n;

	CHECK_NULL_ARG(fp, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(id, CTRLMOD54XX_MODS_COUNT, OMAPCONF_ERR_ARG);

	if (cpu_revision_get() == REV_ES1_0)
		mod = ctrlmod54xxes1_mods[id];
	else
		mod = ctrlmod54xx_mods[id];
	rewind(fp);

	/* Search for the module tag */
	sprintf(sline, "<submodule id=\"%u\" name=\"%s\">",
		id, ctrlmod54xx_mod_name_get(id));
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
				ctrlmod54xx_mod_name_get(id), xml_entry);

			/* Check register id is correct */
			ret = sscanf(xml_entry, "<register id=\"%u\" %s",
				&n, sline);
			if (ret != 2) {
				dprintf("%s(%u (%s)): could not get id\n",
					__func__, id,
					ctrlmod54xx_mod_name_get(id));
				return OMAPCONF_ERR_UNEXPECTED;
			}
			if (n != i) {
				dprintf("%s(%u (%s)): register id does not "
					"match! (n=%u, i=%u)\n", __func__, id,
					ctrlmod54xx_mod_name_get(id), n, i);
				return OMAPCONF_ERR_UNEXPECTED;
			}

			ret = reg_xml_import(mod[i], xml_entry);
			if (ret != 0)
				return ret;
		}
		dprintf("%s(%u (%s)): all registers imported.\n", __func__, id,
			ctrlmod54xx_mod_name_get(id));
		break;
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		ctrlmod54xx_s2idx
 * @BRIEF		convert string to valid CTRLMOD index
 * @RETURNS		valid CTRLMOD index
 *			CTRLMOD54XX_IDX_MAX if no valid CTRLMOD index
 *			corresponding to string s
 * @param[in]		s: string
 * @DESCRIPTION		convert string to valid CTRLMOD index
 *//*------------------------------------------------------------------------ */
ctrlmod54xx_index ctrlmod54xx_s2idx(char *s)
{
	if (strcmp(s, "all") == 0)
		return CTRLMOD54XX_IDX_ALL;
	else if (strcmp(s, "core") == 0)
		return CTRLMOD54XX_IDX_CORE;
	else if (strcmp(s, "core_pad") == 0)
		return CTRLMOD54XX_IDX_CORE_PAD;
	else if (strcmp(s, "wkup") == 0)
		return CTRLMOD54XX_IDX_WKUP;
	else if (strcmp(s, "wkup_pad") == 0)
		return CTRLMOD54XX_IDX_WKUP_PAD;
	else
		return CTRLMOD54XX_IDX_MAX;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		ctrlmod54xx_main
 * @BRIEF		main entry point for CTRLMOD functions
 *
 *			### DEPRECATED, DO NOT USE ANYMORE ###
 *
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		main entry point for CTRLMOD functions
 *//*------------------------------------------------------------------------ */
int ctrlmod54xx_main(int argc, char *argv[])
{
	int ret = 0;
	unsigned int id;

	dprintf("%s(): argc=%u, argv[0]=%s, argv[1]=%s\n", __func__, argc,
		argv[0], argv[1]);

	if (argc == 0) {
		goto ctrlmod54xx_main_err_arg;
	} else if (argc == 1) {
		id = CTRLMOD54XX_MODS_COUNT;
	} else if (argc != 2) {
		goto ctrlmod54xx_main_err_arg;
	} else {
		id = ctrlmod54xx_s2idx(argv[1]);
		dprintf("%s(): ctrlmod54xx_s2idx(%s)=%u\n", argv[1], id);
		if (id == CTRLMOD54XX_IDX_MAX)
			goto ctrlmod54xx_main_err_arg;
		else if (id == CTRLMOD54XX_IDX_ALL)
			id = CTRLMOD54XX_MODS_COUNT;
		dprintf("%s(): id=%u\n", id);
	}

	if (strcmp(argv[0], "dump") == 0) {
		ret = ctrlmod54xx_dump(stdout, (ctrlmod54xx_mod_id) id);
		if (ret != 0)
			goto ctrlmod54xx_main_end;
	} else if (strcmp(argv[0], "cfg") == 0) {
		/* FIXME */
		goto ctrlmod54xx_main_err_arg;
	} else {
		goto ctrlmod54xx_main_err_arg;
	}
	goto ctrlmod54xx_main_end;

ctrlmod54xx_main_err_arg:
	help(HELP_CTRLMOD);
	ret = OMAPCONF_ERR_ARG;

ctrlmod54xx_main_end:
	return ret;
}
