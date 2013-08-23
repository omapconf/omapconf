/*
 *
 * @Component			OMAPCONF
 * @Filename			crossbar.c
 * @Description			DRA7 Crossbar
 * @Author			Nishanth Menon
 * @Date			2013
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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


#include <stdlib.h>
#include <string.h>
#include <lib.h>
#include <mem.h>
#include <autoadjust_table.h>
#include "crossbar.h"


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dra7xx_crossbar_input_init
 * @BRIEF		initalizes the cross bar mapping by reading required
 *			registers
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		module_name: Module name (irq, dma etc..)
 * @param[in]		minput: array representing input crossbar module
 * @param[in]		minput_size: size of crossbar module array
 * @param[in]		mask: what mask to apply for register access
 * @DESCRIPTION		Reads register if present per entry, and updates the
 *			map for the cross bar.
 *//*------------------------------------------------------------------------ */
int dra7xx_crossbar_input_init(char *module_name,
			       struct cross_bar_module_input *minput,
			       int minput_size, unsigned int mask)
{
	struct cross_bar_module_input *curr = minput;
	unsigned int v, r = 0;
	int i;

	for (i = 0; i < minput_size; i++, curr++) {
		unsigned int addr = curr->reg;
		if (!addr)
			continue;
		v = 0;
		/* handle 16 bit */
		if (addr % 4)
			addr -= 2;
		r = mem_read(addr, &v);
		if (r) {
			fprintf(stderr,
				"%s: %s read error!idx=%d,addr=0x%08X(0x%08X),err=%d\n",
				__func__, module_name, i, curr->reg, addr, r);
			r = OMAPCONF_ERR_REG_ACCESS;
			break;
		}

		if (addr != curr->reg)
			v >>= 16;

		v &= mask;
		curr->input = v;
	}

	return r;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dra7xx_crossbar_audit
 * @BRIEF		Does an audit of crossbar configuration
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in]		stream: Output stream
 * @param[in]		type: Type of Crossbar (IRQ/DMA etc).
 * @param[in]		module_name: Module name (irq, dma etc..)
 * @param[in]		minput: array representing input crossbar module
 * @param[in]		minput_size: size of crossbar module array
 * @param[in]		cinput: array representing SoC crossbar
 * @param[in]		cinput_size: size of crossbar array
 * @param[in,out]	tot_error: total errors - updated with results of audit
 * @param[in,out]	tot_checks: total checks - updated with results of audit
 * @DESCRIPTION		Audits the cross bar to see multiple module interrupts
 *			mapping to same source.
 *//*------------------------------------------------------------------------ */
int dra7xx_crossbar_audit(FILE *stream, char *type, char *module_name,
			  struct cross_bar_module_input *minput,
			  int minput_size, struct cross_bar_input *cinput,
			  int cinput_size, int *tot_error, int *tot_checks)
{
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	int row;
	struct cross_bar_module_input *curr = minput, *s_minput;
	unsigned char *cinput_usage;
	unsigned int usage_size;
	int error = 0;
	int checks = 0;
	int i, j, r = 0;

	usage_size = cinput_size / sizeof(unsigned char) + 1;
	cinput_usage = calloc(sizeof(char), usage_size);
	if (!cinput_usage) {
		fprintf(stderr, "%s: %s unable to allocate %d usage bits\n",
			__func__, module_name, usage_size);
		return OMAPCONF_ERR_UNEXPECTED;
	}

	autoadjust_table_init(table);
	row = 0;
	snprintf(table[row][0], TABLE_MAX_ELT_LEN, "%s %s Audit", module_name,
		 type);
	row++;
	strncpy(table[row][0], "Index", TABLE_MAX_ELT_LEN);
	strncpy(table[row][1], "Addr", TABLE_MAX_ELT_LEN);
	strncpy(table[row][2], "Val", TABLE_MAX_ELT_LEN);
	strncpy(table[row][3], "Name", TABLE_MAX_ELT_LEN);
	strncpy(table[row][4], "Rationale", TABLE_MAX_ELT_LEN);
	strncpy(table[row][5], "Status", TABLE_MAX_ELT_LEN);
	row++;

	for (i = 0; i < minput_size; i++, curr++) {
		int offset = 0;
		int bit = 0;

		/* if the signal is unusable/unused, skip checks */
		if (curr->input == -1) {
			strncpy(table[row][5], "N/A", TABLE_MAX_ELT_LEN);
			goto stuff_remaining;
		}

		/* > map size?? scream */
		if (curr->input > cinput_size) {
			snprintf(table[row][4], TABLE_MAX_ELT_LEN,
				 "%d index > %d max", curr->input, cinput_size);
			strncpy(table[row][5], "FAIL", TABLE_MAX_ELT_LEN);
			error++;
			goto stuff_remaining;
		}

		/* lets now check if the input is being used */
		offset = curr->input / sizeof(cinput_usage[0]);
		bit = curr->input % sizeof(cinput_usage[0]);

		/* unused! yay.. mark and continue.. */
		if (!(cinput_usage[offset] & (1 << bit))) {
			cinput_usage[offset] |= 1 << bit;
			strncpy(table[row][5], "PASS", TABLE_MAX_ELT_LEN);
			goto stuff_remaining;
		}
		/* Marked.. hmm.. is it reserved? */
		if (!strcmp("reserved", cinput[curr->input].name)) {
			snprintf(table[row][4], TABLE_MAX_ELT_LEN,
				 "reserved %3d reuse", curr->input);
			strncpy(table[row][5], "CHECK", TABLE_MAX_ELT_LEN);
			checks++;
			goto stuff_remaining;
		}
		snprintf(table[row][4], TABLE_MAX_ELT_LEN,
			"valid %3d reuse with index: ",
			 curr->input);
		strncpy(table[row][5], "FAIL", TABLE_MAX_ELT_LEN);
		error++;

		s_minput = minput;
		for (j = 0; j < minput_size; j++, s_minput++) {
			if (s_minput == curr)
				continue;

			if (s_minput->input == curr->input) {
				char idx_str[TABLE_MAX_ELT_LEN] = { 0 };

				snprintf(idx_str, TABLE_MAX_ELT_LEN, "%d ", j);
				strncat(table[row][4],
					idx_str, TABLE_MAX_ELT_LEN);
			}
		}
stuff_remaining:
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "%d", i);
		/* If interrupt is internal, then... */
		if (curr->input == -1) {
			/* Address or value does not really matter */
			if (curr->reg)
				snprintf(table[row][1], TABLE_MAX_ELT_LEN,
					 "0x%08X?", curr->reg);
			else
				snprintf(table[row][1], TABLE_MAX_ELT_LEN,
					 "%10s", "N/A");
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "N/A");
			/* Fill up remaining from default settings */
			strncpy(table[row][3], curr->name, TABLE_MAX_ELT_LEN);
		} else {
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "0x%08X",
				 curr->reg);
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%3d",
				 curr->input);
			/* > map size?? scream */
			if (curr->input > cinput_size) {
				char *reason = "invalid";
				strncpy(table[row][3], reason,
					TABLE_MAX_ELT_LEN);
			} else {
				struct cross_bar_input *c;
				c = &cinput[curr->input];
				strncpy(table[row][3], c->name,
					TABLE_MAX_ELT_LEN);
			}
		}
		row++;
	}

	free(cinput_usage);

	r = autoadjust_table_generic_fprint(stream, table, row, 6,
				       TABLE_HAS_SUBTITLE | TABLE_HAS_TITLE);
	fprintf(stream, "'N/A' implies there is no alternate mapping possible\n");
	fprintf(stream, "Summary: CHECKS=%d FAILS = %d\n", checks, error);
	fprintf(stream,
		"Checks may be due to duplicate maps to reserved mappings\n");
	fprintf(stream,
		"FAIL implies out of range/dual mapping done - potential failure risk\n\n");

	*tot_error += error;
	*tot_checks += checks;

	return r;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dra7xx_crossbar_dump
 * @BRIEF		Does an dump of crossbar configuration
 * @RETURNS		0 on success
 * @param[in]		stream: Output stream
 * @param[in]		type: Type of Crossbar (IRQ/DMA etc).
 * @param[in]		module_name: Module name (irq, dma etc..)
 * @param[in]		minput: array representing input crossbar module
 * @param[in]		minput_size: size of crossbar module array
 * @param[in]		cinput: array representing SoC crossbar
 * @param[in]		cinput_size: size of crossbar array
 * @DESCRIPTION		Dumps the cross bar to see show the current config
 *//*------------------------------------------------------------------------ */
int dra7xx_crossbar_dump(FILE *stream, char *type, char *module_name,
			 struct cross_bar_module_input *minput,
			 int minput_size, struct cross_bar_input *cinput,
			 int cinput_size)
{
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	int row;
	struct cross_bar_module_input *curr = minput;
	int i;

	autoadjust_table_init(table);
	row = 0;
	snprintf(table[row][0], TABLE_MAX_ELT_LEN, "%s %s Dump", module_name,
		 type);
	row++;
	strncpy(table[row][0], "Index", TABLE_MAX_ELT_LEN);
	strncpy(table[row][1], "Addr", TABLE_MAX_ELT_LEN);
	strncpy(table[row][2], "Val", TABLE_MAX_ELT_LEN);
	strncpy(table[row][3], "Name", TABLE_MAX_ELT_LEN);
	strncpy(table[row][4], "Source", TABLE_MAX_ELT_LEN);
	strncpy(table[row][5], "Description", TABLE_MAX_ELT_LEN);
	row++;

	for (i = 0; i < minput_size; i++, curr++) {
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "%d", i);
		/* If interrupt is internal, then... */
		if (curr->input == -1) {
			/* Address or value does not really matter */
			if (curr->reg)
				snprintf(table[row][1], TABLE_MAX_ELT_LEN,
					 "0x%08X?", curr->reg);
			else
				snprintf(table[row][1], TABLE_MAX_ELT_LEN,
					 "%10s", "N/A");
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "N/A");
			/* Fill up remaining from default settings */
			strncpy(table[row][3], curr->name, TABLE_MAX_ELT_LEN);
			strncpy(table[row][4], curr->source, TABLE_MAX_ELT_LEN);
			strncpy(table[row][5], curr->description,
				TABLE_MAX_ELT_LEN);
		} else {
			struct cross_bar_input *c;
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "0x%08X",
				 curr->reg);
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%3d",
				 curr->input);
			/* > map size?? scream */
			if (curr->input > cinput_size) {
				char *reason = "invalid";
				strncpy(table[row][3], reason,
					TABLE_MAX_ELT_LEN);
				strncpy(table[row][4], reason,
					TABLE_MAX_ELT_LEN);
				strncpy(table[row][5], reason,
					TABLE_MAX_ELT_LEN);
			} else {
				c = &cinput[curr->input];
				strncpy(table[row][3], c->name,
					TABLE_MAX_ELT_LEN);
				strncpy(table[row][4], c->source,
					TABLE_MAX_ELT_LEN);
				strncpy(table[row][5], c->description,
					TABLE_MAX_ELT_LEN);
			}
		}
		row++;
	}

	return autoadjust_table_generic_fprint(stream, table, row, 6,
				       TABLE_HAS_SUBTITLE | TABLE_HAS_TITLE);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dra7_crossbar_dump_main
 * @BRIEF		top handler for crossbar dumps
 * @RETURNS		0 on success
 * @param[in]		argc: argument count
 * @param[in]		argv: argument array
 *//*------------------------------------------------------------------------ */
int dra7_crossbar_dump_main(int argc, char *argv[])
{
	int err = OMAPCONF_ERR_ARG;

	if (argc == 0 || !strcmp(argv[0], "all")) {
		err = dra7_dump_crossbar_irq(stdout, 0, NULL);
	} else if (!strcmp(argv[0], "irq")) {
		err = dra7_dump_crossbar_irq(stdout, argc - 1, argv + 1);
	}

	if (err)
		help(HELP_CROSSBAR);

	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dra7_crossbar_audit_main
 * @BRIEF		top handler for crossbar audits
 * @RETURNS		0 on success
 * @param[in]		argc: argument count
 * @param[in]		argv: argument array
 *//*------------------------------------------------------------------------ */
int dra7_crossbar_audit_main(int argc, char *argv[])
{
	int err = OMAPCONF_ERR_ARG;

	if (argc == 0 || !strcmp(argv[0], "all")) {
		err = dra7_audit_crossbar_irq(stdout, 0, NULL);
	} else if (!strcmp(argv[0], "irq")) {
		err = dra7_audit_crossbar_irq(stdout, argc - 1, argv + 1);
	}

	if (err)
		help(HELP_CROSSBAR);

	return err;
}
