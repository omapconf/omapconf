/*
 *
 * @Component			OMAPCONF
 * @Filename			autoadjust_table.c
 * @Description			Table which element size automatically adapts
 *				with input strings length
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


#include <autoadjust_table.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* #define AUTOADJUST_TABLE_DEBUG */
#ifdef AUTOADJUST_TABLE_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		autoadjust_table_generic_fprint
 * @BRIEF		print elements into a table which size automatically
 *			adjusts.
 * @RETURNS		0 in case of success
 *			-1 in case of incorrect pointer
 *			-2 in case of memory allocation error
 *			-3 one element of the table is longer than
 *			TABLE_MAX_ELT_LEN
 * @param[in,out]	stream: output file
 * @param[in]		table: elements to be printed
 *			format: table[row][col][string]
 * @param[in]		row_nbr: number of rows
 * @param[in]		col_nbr: number of columns
 * @param[in]		flags: table format flags
 * @DESCRIPTION		print elements into a table which size automatically
 *			adjusts. The printed table depends on the format flags:
 *
 *	TABLE_HAS_TITLE:
 *
 *	|------------------------------------------------------------------|
 *	| elements[0][0]                                                   |
 *	|------------------------------------------------------------------|
 *	| elements[1][0]     | elements[1][1]     | elements[1][col-1]     |
 *	| elements[2][0]     | elements[2][1]     | elements[2][col-1]     |
 *	| elements[row-1][0] | elements[row-1][1] | elements[row-1][col-1] |
 *	|------------------------------------------------------------------|
 *
 *	TABLE_HAS_SUBTITLE:
 *
 *	|------------------------------------------------------------------|
 *	| elements[0][0]     | elements[0][1]     | elements[0][col-1]     |
 *	|------------------------------------------------------------------|
 *	| elements[1][0]     | elements[1][1]     | elements[1][col-1]     |
 *	| elements[2][0]     | elements[2][1]     | elements[2][col-1]     |
 *	| elements[row-1][0] | elements[row-1][1] | elements[row-1][col-1] |
 *	|------------------------------------------------------------------|
 *
 *	TABLE_HAS_TITLE | TABLE_HAS_SUBTITLE:
 *
 *	|------------------------------------------------------------------|
 *	| elements[0][0]                                                   |
 *	|------------------------------------------------------------------|
 *	| elements[1][0]     | elements[1][1]     | elements[1][col-1]     |
 *	|------------------------------------------------------------------|
 *	| elements[2][0]     | elements[2][1]     | elements[2][col-1]     |
 *	| elements[row-1][0] | elements[row-1][1] | elements[row-1][col-1] |
 *	|------------------------------------------------------------------|
 *//*------------------------------------------------------------------------ */
int autoadjust_table_generic_fprint(FILE *stream,
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN],
	unsigned int row_nbr, unsigned int col_nbr, unsigned int flags)
{
	unsigned int total_dash_nbr = 0;
	unsigned int total_width = 0;
	char *dash_line = NULL;
	char *line = NULL;
	char *title = NULL;
	unsigned int col, row;
	unsigned int tmp;
	unsigned int max_elt_size[TABLE_MAX_COL];
	unsigned int strln;
	int has_title = !!(flags & TABLE_HAS_TITLE);

	if (stream == NULL) {
		printf("autoadjust_table_fprint() error: stream == NULL!\n");
		return -1;
	}
	if (table == NULL) {
		printf("autoadjust_table_fprint() error: table == NULL!\n");
		return -1;
	}
	if (row_nbr > TABLE_MAX_ROW) {
		printf("autoadjust_table_fprint() error: row_nbr (%d) > "
			"TABLE_MAX_ROW (%d)!\n", row_nbr, TABLE_MAX_ROW);
		return -1;
	}
	if (col_nbr > TABLE_MAX_COL) {
		printf("autoadjust_table_fprint() error: col_nbr (%d) > "
			"TABLE_MAX_COL (%d)!\n", col_nbr, TABLE_MAX_COL);
		return -1;
	}

	if (has_title)
		title = table[0][0];

	#ifdef AUTOADJUST_TABLE_DEBUG
	dprintf("row_nbr = %d, col_nbr = %d\n", row_nbr, col_nbr);
	for (row = 0; row < row_nbr; row++) {
		for (col = 0; col < col_nbr; col++)
			dprintf("element[%d][%d] = %s\n",
				row, col, table[row][col]);
	}
	#endif


	/* compute width of each column of the table */
	for (col = 0; col < col_nbr; col++)
		max_elt_size[col] = 0;

	/* title length will be added to total width later */
	row = has_title ? 1 : 0;

	for (; row < row_nbr; row++) {
		tmp = 0;
		/* Get total length of strings in this line */
		for (col = 0; col < col_nbr; col++) {
			strln = strlen(table[row][col]);
			if (strln > TABLE_MAX_ELT_LEN) {
				printf("%s(): WARNING: \"%s\" size (%u) > "
					"TABLE_MAX_ELT_LEN (%u)!\n",
					__func__, table[row][col],
					strln, TABLE_MAX_ELT_LEN);
				strln = TABLE_MAX_ELT_LEN;
			}

			if (strln > max_elt_size[col]) {
				max_elt_size[col] = strln;
				dprintf("new max_elt_size[%d] = %d\n",
					col, max_elt_size[col]);
			}
		}
	}

	/* Compute the total width of the table, and allocate memory for it */
	for (col = 0; col < col_nbr; col++)
		total_width += max_elt_size[col];
	/* Add number of '|' separators per line */
	total_width += (col_nbr + 1);
	/* Add number of space character separators (2 per element) */
	total_width += col_nbr * 2;

	/* Compensate if the title is longer than table width */
	if (has_title) {
		unsigned int avail;

		strln = strlen(title);
		avail = total_width - 4; /* exclude left and right borders */
		dprintf("title_width=%d\n", strln);

		if (avail < strln) {
			/* Number of chars to compensate per column */
			tmp = (strln - avail + col_nbr - 1) / col_nbr;

			total_width = 0;
			for (col = 0; col < col_nbr; col++) {
				max_elt_size[col] += tmp;
				total_width += max_elt_size[col];
				dprintf("new max_elt_size[%d] = %d\n",
					col, max_elt_size[col]);
			}
			/* Add number of separators per line */
			total_width += (col_nbr + 1);
			total_width += col_nbr * 2;
		}
	}

	dprintf("total_width = %d\n", total_width);
	line  = malloc(sizeof(char) * (total_width + 1));
	if (line == NULL) {
		printf("autoadjust_table_fprint(): line malloc error!\n");
		return -2;
	}
	line[0] = '\0';
	line[total_width] = '\0';

	/*
	 * Compute the total number of dash characters,
	 * used to delimit the table, and allocate memory for it
	 */
	total_dash_nbr = total_width - 2;
	dash_line = malloc(sizeof(char) * (total_width + 1));
	dprintf("total_dash_nbr = %d\n", total_dash_nbr);
	if (dash_line == NULL) {
		printf("autoadjust_table_fprint(): dash_line malloc error!\n");
		return -2;
	}
	dash_line[0] = '\0';
	dash_line[total_width] = '\0';

	dprintf("total_dash_nbr=%d\n", total_dash_nbr);
	dprintf("total_width=%d\n", total_width);

	/* Print table */
	dash_line[0] = '|';
	memset(dash_line + sizeof(char), '-', total_dash_nbr);
	dash_line[total_dash_nbr + 1] = '|';
	fprintf(stream, "%s\n", dash_line);

	row = 0;
	if (has_title) {
		strcpy(line, "| ");
		strcat(line, title);
		tmp = total_width - 4 - strlen(title);
		while (tmp--)
			strcat(line, " ");

		strcat(line, " |");
		fprintf(stream, "%s\n", line);
		fprintf(stream, "%s\n", dash_line);
		row++;
	}

	for (; row < row_nbr; row++) {
		strcpy(line, "|");
		for (col = 0; col < col_nbr; col++) {
			strcat(line, " ");
			strncat(line, table[row][col], TABLE_MAX_ELT_LEN);
			if (strlen(table[row][col]) != TABLE_MAX_ELT_LEN) {
				for (tmp = strlen(table[row][col]);
					tmp < max_elt_size[col]; tmp++)
					strcat(line, " ");
			}
			strcat(line, " |");
		}
		fprintf(stream, "%s\n", line);
		if (flags & TABLE_HAS_SUBTITLE) {
			fprintf(stream, "%s\n", dash_line);
			flags &= ~TABLE_HAS_SUBTITLE;
		}
	}
	fprintf(stream, "%s\n\n", dash_line);

	free(dash_line);
	free(line);

	return 0;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		autoadjust_table_fprint
 * @BRIEF		print elements into a table which size automatically
 *			adjusts.
 * @RETURNS		0 in case of success
 *			-1 in case of incorrect pointer
 *			-2 in case of memory allocation error
 *			-3 one element of the table is longer than
 *			TABLE_MAX_ELT_LEN
 * @param[in,out]	stream: output file
 * @param[in]		table: elements to be printed
 *			format: table[row][col][string]
 * @param[in]		row_nbr: number of rows
 * @param[in]		col_nbr: number of columns
 * @DESCRIPTION		print elements into a table which size automatically
 *			adjusts. The printed table looks like this:
 *	|------------------------------------------------------------------|
 *	| elements[0][0]     | elements[0][1]     | elements[0][col-1]     |
 *	|------------------------------------------------------------------|
 *	| elements[1][0]     | elements[1][1]     | elements[1][col-1]     |
 *	| elements[2][0]     | elements[2][1]     | elements[2][col-1]     |
 *	| elements[row-1][0] | elements[row-1][1] | elements[row-1][col-1] |
 *	|------------------------------------------------------------------|
 *//*------------------------------------------------------------------------ */
int autoadjust_table_fprint(FILE *stream,
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN],
	unsigned int row_nbr, unsigned int col_nbr)
{
	return autoadjust_table_generic_fprint(stream, table, row_nbr, col_nbr,
					       TABLE_HAS_SUBTITLE);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		autoadjust_table_print
 * @BRIEF		print to console elements into a table which size
 *			automatically adjusts.
 * @RETURNS		0 in case of success
 *			-1 in case of incorrect pointer
 *			-2 in case of memory allocation error
 *			-3 one element of the table is longer than
 *			TABLE_MAX_ELT_LEN
 * @param[in]		table: elements to be printed
 *			format: table[row][col][string]
 * @param[in]		row_nbr: number of rows
 * @param[in]		col_nbr: number of columns
 * @DESCRIPTION		print to console elements into a table which size
 *			automatically adjusts. The printed table is like this:
 *	|------------------------------------------------------------------|
 *	| elements[0][0]     | elements[0][1]     | elements[0][col-1]     |
 *	|------------------------------------------------------------------|
 *	| elements[1][0]     | elements[1][1]     | elements[1][col-1]     |
 *	| elements[2][0]     | elements[2][1]     | elements[2][col-1]     |
 *	| elements[row-1][0] | elements[row-1][1] | elements[row-1][col-1] |
 *	|------------------------------------------------------------------|
 *//*------------------------------------------------------------------------ */
int autoadjust_table_print(
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN],
	unsigned int row_nbr, unsigned int col_nbr)
{
	return autoadjust_table_fprint(stdout, table, row_nbr, col_nbr);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		autoadjust_table_strncpy
 * @BRIEF		copy string into table element, making sure it can fit.
 * @RETURNS		0 in case of success
 *			-1 in case of incorrect argument(s)
 *			-3 one element of the table longer than
 *			TABLE_MAX_ELT_LEN
 * @param[in,out]	table: elements to be printed
 *			format: table[row][col][string]
 * @param[in]		row: number of rows
 * @param[in]		col: number of columns
 * @param[in]		s: string to copy
 * @DESCRIPTION		copy string into table element, making sure it can fit.
 *//*------------------------------------------------------------------------ */
int autoadjust_table_strncpy(
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN],
	unsigned int row, unsigned int col, char s[TABLE_MAX_ELT_LEN])
{
	if (table == NULL) {
		fprintf(stderr, "%s(): table == NULL!!!\n", __func__);
		return -1;
	}
	if (s == NULL) {
		fprintf(stderr, "%s(): s == NULL!!!\n", __func__);
		return -1;
	}
	if (row >= TABLE_MAX_ROW) {
		fprintf(stderr, "%s(): row (%u) >= TABLE_MAX_ROW (%u)\n",
			__func__, row, TABLE_MAX_ROW);
		return -1;
	}
	if (col >= TABLE_MAX_COL) {
		fprintf(stderr, "%s(): col (%u) >= TABLE_MAX_COL (%u)\n",
			__func__, col, TABLE_MAX_COL);
		return -1;
	}
	if (strlen(s) >= TABLE_MAX_ELT_LEN) {
		fprintf(stderr, "%s(): "
			"strlen(%s)=%u >= TABLE_MAX_ELT_LEN (%u)!\n", __func__,
			s, strlen(s), TABLE_MAX_ELT_LEN);
		return -3;
	}

	strncpy(table[row][col], s, TABLE_MAX_ELT_LEN);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		autoadjust_table_init
 * @BRIEF		fill table with empty strings
 * @RETURNS		0 in case of success
 *			-1 in case of incorrect pointer
 * @param[in,out]	table: table to fill with empty strings
 * @DESCRIPTION		fill table with empty strings, so that user does not
 *			need to fill empty cell(s).
 *//*------------------------------------------------------------------------ */
int autoadjust_table_init(
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN])
{
	unsigned int col, row;

	if (table == NULL) {
		printf("autoadjust_table_init() error: table == NULL!\n");
		return -1;
	}

	for (row = 0; row < TABLE_MAX_ROW; row++)
		for (col = 0; col < TABLE_MAX_COL; col++)
			table[row][col][0] = '\0';

	return 0;
}
