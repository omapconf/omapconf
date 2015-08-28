/*
 *
 * @Component			OMAPCONF
 * @Filename			trace.c
 * @Description			OMAP Common Trace Definitions and Functions
 * @Author			Patrick Titiano (p-titiano@ti.com)
 * @Author			Louis Lamia (loulamia@ti.com)
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


#include <trace.h>
#include <unistd.h>
#include <stdlib.h>
#include <cpuinfo.h>
#include <cpufreq.h>
#include <module.h>
#include <lib.h>
#include <lib44xx.h>
#include <temperature.h>
#include <temp54xx.h>
#include <clock44xx.h>
#include <emif44xx.h>
#include <autoadjust_table.h>
#include "sci.h"
#include <powerdomain.h>
#include <mem.h>
#include <unistd.h>


/* #define TRACE_DEBUG */
#ifdef TRACE_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static struct sci_config_sdram my_config_emif1 = { SCI_SDRAM_THROUGHPUT, SCI_EMIF1, 1,	{ { SCI_MASTID_ALL, 0xff, SCI_WR_ONLY, SCI_ERR_DONTCARE } } };
static struct sci_config_sdram my_config_emif2 = { SCI_SDRAM_THROUGHPUT, SCI_EMIF2, 1,	{ { SCI_MASTID_ALL, 0xff, SCI_WR_ONLY, SCI_ERR_DONTCARE } } };
static struct sci_config_sdram my_config_emif3 = { SCI_SDRAM_THROUGHPUT, SCI_EMIF1, 1,	{ { SCI_MASTID_ALL, 0xff, SCI_RD_ONLY, SCI_ERR_DONTCARE } } };
static struct sci_config_sdram my_config_emif4 = { SCI_SDRAM_THROUGHPUT, SCI_EMIF2, 1,	{ { SCI_MASTID_ALL, 0xff, SCI_RD_ONLY, SCI_ERR_DONTCARE } } };
static struct sci_config_sdram my_config_emif5 = { SCI_SDRAM_THROUGHPUT, SCI_EMIF1, 1,	{ { SCI_MASTID_ALL, 0xff, SCI_WR_ONLY, SCI_ERR_DONTCARE } } };
static struct sci_config_sdram my_config_emif6 = { SCI_SDRAM_THROUGHPUT, SCI_EMIF2, 1,	{ { SCI_MASTID_ALL, 0xff, SCI_WR_ONLY, SCI_ERR_DONTCARE } } };
static struct sci_config_sdram my_config_emif7 = { SCI_SDRAM_THROUGHPUT, SCI_EMIF1, 0,	{ { SCI_MASTID_ALL, 0xff, SCI_RD_OR_WR_DONTCARE, SCI_ERR_DONTCARE } } };
static struct sci_config_sdram my_config_emif8 = { SCI_SDRAM_THROUGHPUT, SCI_EMIF2, 0,	{ { SCI_MASTID_ALL, 0xff, SCI_RD_OR_WR_DONTCARE, SCI_ERR_DONTCARE } } };

static struct sci_config_sdram *pmy_cfg[] =  {
	&my_config_emif1,
	&my_config_emif2,
	&my_config_emif3,
	&my_config_emif4,
	&my_config_emif5,
	&my_config_emif6,
	&my_config_emif7,
	&my_config_emif8};

static unsigned int num_use_cases = 4;
static unsigned int valid_usecase_cnt = 0;
static psci_handle psci_hdl = NULL;
static psci_usecase_key my_usecase_key[8] = {
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
static uint32_t *sci_cntrs_buf[8];
static double *emif_bw[2];
static double emif_bw_min[2], emif_bw_max[2], emif_bw_avg[2];
static void trace_bw_deinit(void);


/* Max number of Generic Input Files */
#define TRACE_MAX_GENINPUTS			32
#define TRACEABLES_NAME_LENGTH_MAX		24
#define TRACEABLES_UNIT_LENGTH_MAX		8

static const char
	traceables_names[NUM_ITEMS + 1][TRACEABLES_NAME_LENGTH_MAX] = {
	"CPU0 Load",
	"CPU1 Load",
	"Total CPU Load",
	"CPU1 Online Time",
	"CPU Frequency",
	"GPU Frequency",
	"L3 Frequency",
	"EMIF Bandwidth",
	"EMIF Data Bus Load",
	"Bandgap Temperature",
	"PCB Temperature",
	"Hotspot Temperature",
	"MPU Temperature",
	"GPU Temperature",
	"CORE Temperature",
	"CASE Temperature",
	"FIXME"};


static const char
	traceables_unit[NUM_ITEMS + 1][TRACEABLES_UNIT_LENGTH_MAX] = {
	"%",
	"%",
	"%",
	"%",
	"MHz",
	"MHz",
	"MHz",
	"MB/s",
	"%",
	"C",
	"C",
	"C",
	"C",
	"C",
	"C",
	"C",
	"FIXME"};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		trace_cfg_line_parse
 * @BRIEF		Parse a line from the config file
 * @RETURNS		'y' if the flag is a y
 *			'n' if the flag is an n
 *			'x' if the line is formatted incorrectly
 * @param[in, out]	line: the line to be parsed.  Replaces the character
 *			after the end of item_name with '\0' so it can be
 *			read as a string
 * @param[in]		buffer_size: the size of the line buffer
 * @DESCRIPTION		Read a line of the form "item_name | flag" and parse it
 *			for easy access to its individual components.
 *//*------------------------------------------------------------------------ */
char trace_cfg_line_parse(char line[], int buffer_size)
{
	int i = 0;
	int pipe_index;

	while (line[i] != '|') {
		i++;
		if (i < 0 || i >= buffer_size)
			return 'x';
	}

	pipe_index = i;
	i--;

	while (line[i] == ' ') {
		i--;
		if (i < 0 || i >= buffer_size)
			return 'x';
	}

	line[i+1] = '\0';
	i = pipe_index + 1;

	while (line[i] == ' ') {
		i++;
		if (i < 0 || i >= buffer_size)
			return 'x';
	}

	if (tolower(line[i]) == 'y')
		return 'y';

	else if (tolower(line[i]) == 'n')
		return 'n';

	else
		return 'x';
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		trace_default_cfg_create
 * @BRIEF		Create a default config file
 * @RETURNS		Void
 * @param[in]		fp: a file pointer opened in "write" mode
 * @DESCRIPTION		Create a default confifg file if none exists
 *//*------------------------------------------------------------------------ */
void trace_default_cfg_create(FILE *fp)
{
	int i;

	dprintf("%s(): Creating default cfg file...\n", __func__);

	fputs("# Header\n", fp);
	fputs("# Header\n", fp);
	fputs("# Header\n\n", fp);

	for (i = 0; i < NUM_ITEMS; i++) {
		fputs("## Description\n", fp);
		switch (i) {
		case EMIF_LOAD:
		case BANDGAP_TEMP:
		case PCB_TEMP:
			if (cpu_is_omap44xx())
				fprintf(fp, "%s | y\n\n", traceables_names[i]);
			else
				fprintf(fp, "%s | n\n\n", traceables_names[i]);
			break;

		case HOTSPOT_MPU_TEMP:
			if (cpu_is_omap44xx() &&
				(temp_sensor_get(TEMP_SENSOR_HOTSPOT_MPU) !=
					TEMP_ABSOLUTE_ZERO))
				fprintf(fp, "%s | y\n\n", traceables_names[i]);
			else
				fprintf(fp, "%s | n\n\n", traceables_names[i]);
			break;

		case MPU_TEMP:
		case GPU_TEMP:
		case CORE_TEMP:
		case CASE_TEMP:
			if (cpu_is_omap54xx())
				fprintf(fp, "%s | y\n\n", traceables_names[i]);
			else
				fprintf(fp, "%s | n\n\n", traceables_names[i]);
			break;

		case CPU_FREQ:
		case GPU_FREQ:
		case L3_FREQ:
			if (cpu_is_omap54xx() || cpu_is_omap44xx())
				fprintf(fp, "%s | y\n\n", traceables_names[i]);
			else
				fprintf(fp, "%s | n\n\n", traceables_names[i]);
			break;

		case EMIF_BW:
			if (cpu_is_omap54xx() || cpu_is_omap4470())
				fprintf(fp, "%s | y\n\n", traceables_names[i]);
			else
				fprintf(fp, "%s | n\n\n", traceables_names[i]);
			break;

		default:
			fprintf(fp, "%s | y\n\n", traceables_names[i]);
			break;
		}
	}

	dprintf("%s(): done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		trace_yn_swap
 * @BRIEF		Swaps the y/n flag in a line
 * @RETURNS		Void
 * @param[in, out]	line: A line of the form "other_stuff | flag"
 * @DESCRIPTION		Replaces a 'y' flag in line with 'n', or an 'n' flag
 *			with 'y', or puts 'x' if the flag is neither 'y' nor 'n'
 *//*------------------------------------------------------------------------ */
void trace_yn_swap(char line[])
{
	int i = 0;

	while (line[i] != '|')
		i++;

	i++;

	while (line[i] == ' ')
		i++;

	if (tolower(line[i]) == 'y')
		line[i] = 'n';

	else if (tolower(line[i]) == 'n')
		line[i] = 'y';

	else
		line[i] = 'x';
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		trace_yn2yesno
 * @BRIEF		Converts a y/n flag to the word "yes" or "no"
 * @RETURNS		"yes" for a 'y' flag
 *			"no" for an 'n' flag
 *			"ERROR" if the flag is incorrect
 * @param[in]		letter: the flag to convert
 * @DESCRIPTION		Converts a 'y' flag to "yes" or an 'n' flag to "no"
 *//*------------------------------------------------------------------------ */
char *trace_yn2yesno(char letter)
{
	char *word;

	if (tolower(letter) == 'y')
		word = "yes";

	else if (tolower(letter) == 'n')
		word = "no";

	else
		word = "ERROR";

	return word;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		trace_newline_strip
 * @BRIEF		Remove '\n' from the end of a line
 * @RETURNS		Void
 * @param[in, out]	line: array to strip the newline character from,
 *			first instance of '\n' will be replaced by '\0'
 * @param[in]		size: the size of the line
 * @DESCRIPTION		Replaces '\n' at the end of a line with '\0'
 *//*------------------------------------------------------------------------ */
void trace_newline_strip(char line[], int size)
{
	int i;

	for (i = 0; i < size; i++) {
		if (line[i] == '\n') {
			line[i] = '\0';
			break;
		}
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		trace_index2name
 * @BRIEF		Convert a trace index to a trace item name
 * @RETURNS		trace item name
 * @param[in]		name: string representing the traceable item's name
 * @DESCRIPTION		Takes a name and returns the array index mapped to it by
 *			the enum 'traceables'
 *//*------------------------------------------------------------------------ */
const char *trace_index2name(traceables index)
{
	if (index > NUM_ITEMS)
		index = NUM_ITEMS;

	return traceables_names[index];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		trace_name2index
 * @BRIEF		Convert a name to an array index
 * @RETURNS		An index mapped to the name
 *			-1 if no mapping can be found
 * @param[in]		name: string representing the traceable item's name
 * @DESCRIPTION		Takes a name and returns the array index mapped to it by
 *			the enum 'traceables'
 *//*------------------------------------------------------------------------ */
int trace_name2index(char *name)
{
	int i;

	/* Remove leading whitespace */
	while (*name == ' ')
		name += sizeof(char);

	for (i = 0; i < NUM_ITEMS; i++) {
		if (strcasecmp(name, traceables_names[i]) == 0) {
			dprintf("%s(): index for '%s' is %d\n", __func__,
				name, i);
			return i;
		}
	}

	dprintf("%s(): NO MATCH for '%s'!\n", __func__, name);
	return -1;
}


/* Compares 2 integers, passed as an argument to qsort */
int int_cmp(const void *v1, const void *v2)
{
	return *(int *) v1 - *(int *) v2;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		trace_geninput_config_read
 * @BRIEF		Read a config file for the generic inputs
 * @RETURNS		The number of generic input files in the config file
 *			-1 if the file couldn't be opened
 *			-2 if a buffer couldn't be allocated
 *			-3 if a line was formatted incorrectly
 * @param[in]		filename: The name of the config file to be read
 * @param [in, out]	names: An array to hold the names of the geninput files
 * @param[in, out]	paths: An array to hold the paths of the geninput files
 * @param[in, out]	units: An array to hold the units of the geninput files
 * @param[in, out]	accumulating : An array of flags that tell whether the
 *			counter is accumulating for that geninput file
 * @param[in, out]	flags: An array of flags that tell whether to trace that
 *			geninput
 * @DESCRIPTION		Read the config file for generic input files and parse
 *			them into the input buffers
 *//*------------------------------------------------------------------------ */
int trace_geninput_config_read(const char *filename,
	char *names[], char *paths[],
	char *units[], int accumulating[], int flags[])
{
	FILE *fp;
	int i = 1;
	int geninput_num = 0;
	int open_quote_index;
	int close_quote_index;
	const int BUFFER_SIZE = 256;
	char *buffer;

	fp = fopen(filename, "r");
	if (fp == NULL)
		return -1;

	while (!feof(fp)) {
		i = 1;
		buffer = malloc(BUFFER_SIZE);
		if (buffer == NULL)
			return -2;

		if (fgets(buffer, BUFFER_SIZE, fp)) {
			dprintf("unexpected read\n");
		}

		if (*buffer != '*')
			continue;

		/* Find beginning of name */
		while (*(buffer+i) == ' ') {
			if (i >= BUFFER_SIZE)
				return -3;
			i++;
		}

		names[geninput_num] = buffer + i;

		/* Find end of name */
		while (*(buffer + i) != '\"') {
			if (i >= BUFFER_SIZE)
				return -3;
			i++;
		}

		open_quote_index = i;
		i--;

		while (*(buffer+i) == ' ') {
			if (i <= 0)
				return -3;
			i--;
		}

		*(buffer + i + 1) = '\0';

		/* Find beginning of path */
		i = open_quote_index + 1;

		while (*(buffer+i) == ' ') {
			if (i >= BUFFER_SIZE)
				return -3;
			i++;
		}

		paths[geninput_num] = buffer + i;

		/* Find end of path */
		while (*(buffer + i) != '\"') {
			if (i >= BUFFER_SIZE)
				return -3;
			i++;
		}

		close_quote_index = i;
		i--;

		while (*(buffer+i) == ' ') {
			if (i <= 0)
				return -3;
			i--;
		}

		*(buffer+i+1) = '\0';

		/* Find units start */
		i = close_quote_index + 1;
		while (*(buffer + i) != '(') {
			if (i >= BUFFER_SIZE)
				return -3;
			i++;
		}
		i++;

		while (*(buffer + i) == ' ') {
			if (i >= BUFFER_SIZE)
				return -3;
			i++;
		}

		/*
		 * No units, start and end is same, set to null string and
		 * move on to accuumulating flag
		 */
		if (*(buffer + i) == ')') {
			*(buffer + i) = '\0';
			units[geninput_num] = buffer + i;
		} else {
			units[geninput_num] = buffer + i;
			/* Find end of units */
			while (*(buffer + i) != ')') {
				if (i >= BUFFER_SIZE)
					return -3;
				i++;
			}
			i--;
			while (*(buffer + i) == ' ') {
				if (i <= 0)
					return -3;
				i--;
			}
			*(buffer + i + 1) = '\0';
		}

		/* Find accumulating flag */
		while (*(buffer + i) != '[') {
			if (i >= BUFFER_SIZE)
				return -3;
			i++;
		}
		i++;

		/* Set accumulating flag */
		if (*(buffer + i) == '+')
			accumulating[geninput_num] = 1;

		else if (*(buffer + i) == '=')
			accumulating[geninput_num] = 0;

		else
			return -3;

		/* Find flag */
		while (*(buffer + i) != '|') {
			if (i >= BUFFER_SIZE)
				return -3;
			i++;
		}
		i++;
		while (*(buffer + i) == ' ') {
			if (i >= BUFFER_SIZE)
				return -3;
			i++;
		}

		/* Set flag */
		if (*(buffer + i) == 'y')
			flags[geninput_num] = 1;

		else if (*(buffer + i) == 'n')
			flags[geninput_num] = 0;

		else
			return -3;

		geninput_num++;
	}

	return geninput_num;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		trace_config_read
 * @BRIEF		Read the config file and output an array of flags.
 * @RETURNS		>= 0 the number of items to be traced
 *			-1 if the file couldn't be read
 *			-2 if one of the lines is incorrectly formatted
 *			-3 if not all items were present
 *			-4 if an item was duplicated
 *			-5 in case of incorrect argument
 * @param[in]		filename: The name of the config file to be read
 * @param[in, out]	flags: An array of flags that tell whether to trace that
 *			geninput (1s standing for traced items and
 *			0 for untraced items)
 * @DESCRIPTION		Read the config file for non-geninputs and
 *			output an array of flags telling items to be traced.
 *//*------------------------------------------------------------------------ */
int trace_config_read(const char *filename, int flags[NUM_ITEMS])
{
	static const int BUFFER_SIZE = 256;
	char buffer[BUFFER_SIZE];
	FILE *fp = NULL;
	int item_index;
	char item_tracking;
	int ret = 0, i = 0;

	CHECK_NULL_ARG(filename, -5);
	CHECK_NULL_ARG(flags, -5);

	/* Initialize Array */
	for (i = 0; i < NUM_ITEMS; i++)
		flags[i] = -10;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		dprintf("%s(): could not open %s cfg file!\n",
			__func__, filename);
		ret = -1;
		goto read_config_end;
	}

	while (!feof(fp)) {
		if (fgets(buffer, BUFFER_SIZE, fp)) {
			dprintf("unexpected read\n");
		}
		if (buffer[0] == '#' || buffer[0] == '\n' || buffer[0] == '*')
			continue;

		item_tracking = trace_cfg_line_parse(buffer, BUFFER_SIZE);
		item_index = trace_name2index(buffer);

		/* Handle Errors */
		if (item_index == -1) {
			fprintf(stderr,
				"omapconf: error: traceable item name not recognized!!!\n");
			ret = -2;
			goto read_config_end;
		}
		if (item_tracking == 'x') {
			fprintf(stderr,
				"omapconf: error: Y/N flag not recognized!!!\n");
			ret = -2;
			goto read_config_end;
		}
		if (flags[item_index] != -10) {
			fprintf(stderr,
				"omapconf: error: traceable item appears twice in list!!!\n");
			ret = -4;
			goto read_config_end;
		}

		/* Set flag */
		if (item_tracking == 'y') {
			flags[item_index] = 1;
			ret++;
		} else if (item_tracking == 'n') {
			flags[item_index] = 0;
		}
		dprintf("%s(): flag[%d] (%s) = %d\n", __func__, item_index,
			trace_index2name(item_index), flags[item_index]);
	}
	dprintf("%s(): # of items to trace: %d\n", __func__, ret);

	/* Check flags */
	for (i = 0; i < NUM_ITEMS; i++) {
		if (flags[i] == -10) {
			printf(
				"omapconf: warning: not all traceable items present in configuration (%d).\n",
				i);
			ret = -3;
		}
	}

read_config_end:
	/* Close cfg file */
	if (fp != NULL)
		fclose(fp);
	dprintf("%s(): ret=%d\n", __func__, ret);
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		trace_geninput_yn_read
 * @BRIEF		Reads a generic input line from the config
 * @RETURNS		'y' if the trace flag was 'y'
 *			'n' if the trace flag was 'n'
 *			'x' if the trace flag was incorrect
 * @param[in, out]	line: The line to be read
 * @param[in]		size: The size of the line
 * @DESCRIPTION		Reads a generic input file from the config and returns
 *			the flag
 *//*------------------------------------------------------------------------ */
char trace_geninput_yn_read(char line[], int size)
{
	int i = 0;

	while (line[i] != '\"') {
		if (i >= size)
			return 'x';
		i++;
	}

	i--;

	while (line[i] == ' ') {
		if (i < 0)
			return 'x';
		i--;
	}

	line[i+1] = '\0';
	i += 2;

	while (line[i] != '|') {
		if (i >= size)
			return 'x';
		i++;
	}

	i++;

	while (line[i] == ' ') {
		if (i >= size)
			return 'x';
		i++;
	}

	if (tolower(line[i]) == 'y')
		return 'y';

	if (tolower(line[i]) == 'n')
		return 'n';

	else
		return 'x';
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		trace_config_show
 * @BRIEF		Prints a config file to a table
 * @RETURNS		The number of elements in the table
 * @param[in, out]	buffer: a buffer to store lines being read in
 * @param[in]		buffer_size: the size of the buffer in characters
 * @param[in]		fp: a file pointer to the config file opened in
 *			"read" mode
 * @param[in, out]	p_error: pointer to an error flag that will be
 *			set if an error is found
 * @DESCRIPTION		Prints the config file pointed to by "fp" to a table
 *//*------------------------------------------------------------------------ */
int trace_config_show(char buffer[], int buffer_size, FILE *fp, int *p_error)
{
	int row = 0;
	char number_buffer[4];
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	char YorN;
	int i = 1;
	char *p_name;

	autoadjust_table_init(table);
	autoadjust_table_strncpy(table, row, 0, "#");
	autoadjust_table_strncpy(table, row, 1, "Traceable Item");
	autoadjust_table_strncpy(table, row, 2, "Currently Tracing?");
	row++;

	while (!feof(fp)) {
		if (fgets(buffer, buffer_size, fp)) {
			dprintf("unexpected read\n");
		}

		if ((buffer[0] == '#') || (buffer[0] == '\n'))
			continue;

		else if (buffer[0] == '*') {
			trace_newline_strip(buffer, buffer_size);
			sprintf(number_buffer, "%d", row);
			YorN = trace_geninput_yn_read(buffer, buffer_size);
			while (buffer[i] == ' ')
				i++;
			p_name = buffer + i;
		}

		else {
			trace_newline_strip(buffer, buffer_size);
			sprintf(number_buffer, "%d", row);
			YorN = trace_cfg_line_parse(buffer, buffer_size);
			p_name = buffer;
		}

		if (YorN == 'x') /* set the error flag */
			*p_error = 1;

		autoadjust_table_strncpy(table, row, 0, number_buffer);
		autoadjust_table_strncpy(table, row, 1, p_name);
		autoadjust_table_strncpy(table, row, 2, trace_yn2yesno(YorN));
		row++;
	}

	autoadjust_table_print(table, row, 3);
	return row-1;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		trace_geninput_file_add
 * @BRIEF		Add a generic input file to the config
 * @RETURNS		0 in case of success
 *			-1 if aborted
 * @param[in]		filename: The name of the config file
 * @DESCRIPTION		Add a generic input file to the config
 *//*------------------------------------------------------------------------ */
int trace_geninput_file_add(const char *filename)
{
	const int BUFFER_SIZE = 256;
	char input[BUFFER_SIZE];
	char name[BUFFER_SIZE];
	char path[BUFFER_SIZE];
	char units[BUFFER_SIZE];
	char accumulating;
	char flag;
	FILE *fp;
	FILE *path_test;

	printf("\nEnter X at any time to cancel without saving");

	/* Get name */
	printf("\nEnter the name of the generic input file: ");
	if (fgets(input, BUFFER_SIZE, stdin)) {
		dprintf("unexpected read\n");
	}
	if (tolower(input[0]) == 'x' &&
		(input[1] == '\n' || input[1] == '\0')) {
		printf("\nNo Generic Input File Added\n\n");
		return -1;
	}
	trace_newline_strip(input, BUFFER_SIZE);
	strcpy(name, input);


	/* Get path */
	while (1) {
		printf("\nEnter the path of the generic input file: ");
		if (fgets(input, BUFFER_SIZE, stdin)) {
			dprintf("unexpected read\n");
		}
		if (tolower(input[0]) == 'x' &&
			(input[1] == '\n' || input[1] == '\0')) {
			printf("\nNo Generic Input File Added\n\n");
			return -1;
		}
		trace_newline_strip(input, BUFFER_SIZE);
		path_test = fopen(input, "r");
		if (path_test == NULL) {
			printf("The path \"%s\" could not be found\n", input);
			continue;
		}
		fclose(path_test);
		strcpy(path, input);
		break;
	}

	/* Get Units */
	printf("\nEnter the units of the generic input file: ");
	if (fgets(input, BUFFER_SIZE, stdin)) {
		dprintf("unexpected read\n");
	}
	if (tolower(input[0]) == 'x' &&
		(input[1] == '\n' || input[1] == '\0')) {
		printf("\nNo Generic Input File Added\n\n");
		return -1;
	}
	trace_newline_strip(input, BUFFER_SIZE);
	strcpy(units, input);

	/* Get accumulating */
	while (1) {
		printf("\nIs the counter accumulating (y/n)? ");
		if (fgets(input, BUFFER_SIZE, stdin)) {
			dprintf("unexpected read\n");
		}

		if (tolower(input[0]) == 'x' &&
			(input[1] == '\n' || input[1] == '\0')) {
			printf("\nNo Generic Input File Added\n\n");
			return -1;
		}

		if (!(tolower(input[0]) == 'y' || tolower(input[0]) == 'n'))
			printf("Invalid Input: Please Enter y or n\n");
		else {
			if (tolower(input[0]) == 'y')
				accumulating = '+';
			else
				accumulating = '=';
			break;
		}
	}

	/* Get flag */
	while (1) {
		printf("\nDo you want to trace this item now (y/n)? ");
		if (fgets(input, BUFFER_SIZE, stdin)) {
			dprintf("unexpected read\n");
		}

		if (tolower(input[0]) == 'x' &&
			(input[1] == '\n' || input[1] == '\0')) {
			printf("\nNo Generic Input File Added\n\n");
			return -1;
		}

		if (!(tolower(input[0]) == 'y' || tolower(input[0]) == 'n'))
			printf("Invalid Input: Please Enter y or n\n");
		else {
			flag = tolower(input[0]);
			break;
		}
	}

	/* Write to file */
	fp = fopen(filename, "a");
	fprintf(fp, "* %s \"%s\" (%s) [%c] | %c\n\n",
		name, path, units, accumulating, flag);
	fclose(fp);
	printf("\nGeneric input file added to config\nChanges Saved\n\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		trace_geninput_file_remove
 * @BRIEF		Remove a generic input file from the config
 * @RETURNS		0 in case of success
 *			-1 if number entered was not a generic input file
 *			-2 if aborted
 * @param[in]		filename: Name of the config file
 * @param[in]		temp_filename: Name being used as a
 *			temporary config filename
 * @param[in]		num_elements: Number of elements in the table
 * @DESCRIPTION		Remove a generic input file from the config
 *//*------------------------------------------------------------------------ */
int trace_geninput_file_remove(const char *filename,
	const char *temp_filename, int num_elements)
{
	const int BUFFER_SIZE = 256;
	char buffer[BUFFER_SIZE];
	const int INPUT_SIZE = 4;
	char input_buffer[INPUT_SIZE];
	int current_num = 0;
	int remove_num;
	FILE *old_file;
	FILE *new_file;

	printf("\nEnter X at any time to cancel without saving");

	while (1) {
		printf("\nEnter the number of the file to be removed: ");
		if (fgets(input_buffer, INPUT_SIZE, stdin)) {
			dprintf("unexpected read\n");
		}

		if (tolower(input_buffer[0]) == 'x') {
			printf("\nNo Generic Input File Removed\n\n");
			return -2;
		}

		remove_num = atoi(input_buffer);

		if (remove_num <= 0 || remove_num > num_elements) {
			printf(
				"Invalid Input: Enter a number in the range 1-%d\n\n",
				num_elements);
			continue;
		}

		break;
	}

	old_file = fopen(filename, "r");
	new_file = fopen(temp_filename, "w");

	while (!feof(old_file)) {
		if (fgets(buffer, BUFFER_SIZE, old_file)) {
			dprintf("unexpected read\n");
		}

		if (buffer[0] == '#' || buffer[0] == '\n') {
			fputs(buffer, new_file);
			continue;
		}

		current_num++;

		if (current_num == remove_num && buffer[0] != '*') {
			printf("Error: Must select a generic input file\n\n");
			fclose(old_file);
			fclose(new_file);
			remove(temp_filename);
			return -1;
		}

		else if (current_num != remove_num)
			fputs(buffer, new_file);
	}

		fclose(new_file);
		fclose(old_file);
		remove(filename);
		rename(temp_filename, filename);
		printf(
			"\nGeneric input file successfully removed\nChanges Saved\n\n");

		return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		trace_geninput_file2int
 * @BRIEF		Read a file into a uint64_t
 * @RETURNS		The number in the file
 *			UINT64_MAX if there is an error reading it
 * @param[in]		file_path: path of the file to read
 * @DESCRIPTION		Read the file at file_path and return a uint64_t
 *			representing it
 *//*------------------------------------------------------------------------ */
uint64_t trace_geninput_file2int(char *file_path)
{
	uint64_t output;
	int ret;
	FILE *fp;

	fp = fopen(file_path, "r");
	if (fp == NULL)
		return UINT64_MAX;

	ret = fscanf(fp, "%llu", &output);
	if (ret != 1)
		return UINT64_MAX;

	fclose(fp);

	return output;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		trace_perf_setup
 * @BRIEF		Configure the performance trace
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		filename: name for the config file
 *			(default: trace_config.dat)
 * @DESCRIPTION		Configure the performance trace
 *//*------------------------------------------------------------------------ */
int trace_perf_setup(const char *filename)
{
	static const char TEMP_FILENAME[32] = "trace_perf_temp_config.dat";
	FILE *fp;
	FILE *new_file;
	FILE *old_file;
	const int BUFFER_SIZE = 256; /* must be able to fit all comments */
	char line[BUFFER_SIZE]; /* buffer to read lines from file */
	const int INPUT_SIZE = 16;
	char input_buffer[INPUT_SIZE];
	int input;
	int toggle[32]; /* max # of elements that can be toggled at once */
	int toggle_index = 0;
	int item_number = 0;
	int num_toggled = 0;
	int error = 0; /* flag that is set if error found in file format */
	int num_elements; /* Number of traceable items */
	int geninput_ret;


	/* TEMP_FILENAME cannot be the filename */
	if (strcmp(filename, TEMP_FILENAME) == 0) {
		printf("Error: Please choose a different filename\n");
		return OMAPCONF_ERR_ARG;
	}

	fp = fopen(filename, "r");

	/* if file doesn't exist, create a default */
	if (fp == NULL) {
		fp = fopen(filename, "w");
		if (fp == NULL) {
			fprintf(stderr,
				"omapconf: could not open %s with write permissions. Please check file permissions or move it to a R/W folder.\n\n",
				filename);
			return OMAPCONF_ERR_NOT_AVAILABLE;
		}
		trace_default_cfg_create(fp);
		fclose(fp);
		fp = fopen(filename, "r"); /* reopen the new file for reading */
	}

	num_elements = trace_config_show(line, BUFFER_SIZE, fp, &error);
	fclose(fp);

	while (1) {
		printf("Enter item number ([1-%d]) to toggle it.\n",
			num_elements);
		printf("Enter Q at any time to save and quit.\n");
		printf("Enter X at any time to quit without saving.\n");
		printf(
			"Enter A at any time to add a generic input file to the config.\n");
		printf(
			"Enter R at any time to remove a generic input file from the config.\n\n");
		printf("Command or item number: ");

		if (fgets(input_buffer, INPUT_SIZE, stdin)) {
			dprintf("unexpected read\n");
		}
		if (tolower(input_buffer[0]) == 'q' &&
			(input_buffer[1] == '\0' || input_buffer[1] == ' ' ||
				input_buffer[1] == '\n')) {
			break;
		} else if (tolower(input_buffer[0]) == 'x' &&
			(input_buffer[1] == '\0' || input_buffer[1] == ' ' ||
				input_buffer[1] == '\n')) {
			printf("\nChanges Not Saved.\n\n");
			/* If error flag was set, inform the user */
			if (error)
				printf(
					"WARNING: File Format Error!\nDo not use for trace.\n\n");
			return 0;
		} else if (tolower(input_buffer[0]) == 'a' &&
			(input_buffer[1] == '\0' || input_buffer[1] == ' ' ||
			input_buffer[1] == '\n')) {
			geninput_ret = trace_geninput_file_add(filename);
			if (geninput_ret == 0)
				num_elements++;
			fp = fopen(filename, "r");
			printf("\nNew Trace Configuration:\n");
			trace_config_show(line, BUFFER_SIZE, fp, &error);
			fclose(fp);
			continue;
		} else if (tolower(input_buffer[0]) == 'r' &&
			(input_buffer[1] == '\0' || input_buffer[1] == ' ' ||
			input_buffer[1] == '\n')) {
			geninput_ret = trace_geninput_file_remove(
				filename, TEMP_FILENAME, num_elements);
			if (geninput_ret == 0)
				num_elements--;
			fp = fopen(filename, "r");
			printf("\nNew Trace Configuration:\n");
			trace_config_show(line, BUFFER_SIZE, fp, &error);
			fclose(fp);
			continue;
		}

		/* Convert the input string to an int */
		input = atoi(input_buffer);
		/* if the input was invalid, prompt the user again */
		if (input <= 0 || input > num_elements) {
			printf(
				"Invalid Input: Enter a number in the range [1-%d] or valid command (X, Q, A, R).\n\n",
				num_elements);
			continue;
		}

		toggle[toggle_index] = input;
		toggle_index++;
	}

	qsort(toggle, toggle_index, sizeof(int), int_cmp);
	/* toggle is now a sorted array of numbers to be toggled */

	old_file = fopen(filename, "r");
	new_file = fopen(TEMP_FILENAME, "w");

	while (!feof(old_file)) {
		if (fgets(line, BUFFER_SIZE, old_file)) {
			dprintf("unexpected read\n");
		}

		if (line[0] == '#') {
			fputs(line, new_file);
			continue;
		} else if (line[0] == '\n') {
			fputs(line, new_file);
			continue;
		}

		item_number++;
		/*
		 * if this is the number of the next to be toggled,
		 * swap the y/n and write
		 */
		if (item_number == toggle[num_toggled]) {
			num_toggled++;
			trace_yn_swap(line);
		}
		fputs(line, new_file);
	}

	fclose(new_file);
	fclose(old_file);


	/* delete the old file and rename the temporary one */
	remove(filename);
	rename(TEMP_FILENAME, filename);

	fp = fopen(filename, "r");
	printf("\nNew Trace Configuration:\n");
	trace_config_show(line, BUFFER_SIZE, fp, &error);
	fclose(fp);

	/* If error flag was set, inform the user */
	if (error)
		printf("WARNING: File Format Error!\nDo not use for trace\n\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		trace_bw_errhandler
 * @BRIEF		SCI lib error handler
 * @param[in]		phandle: phandle
 * @param[in]		func: failing func
 * @param[in]		err: err number from lib
 * @DESCRIPTION		SCI lib error handler
 *//*------------------------------------------------------------------------ */
static void trace_bw_errhandler(psci_handle phandle,
	const char *func, enum sci_err err)
{
	printf("SCILib failure %d in function: %s\n", err, func);
	phandle = phandle;

	trace_bw_deinit();
	exit(-2);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		trace_bw_init
 * @BRIEF		Allocate buffers and enable EMU HW used for
 *				EMIF bandwidth monitoring.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		sample_count: number of data samples to be collected
 * @DESCRIPTION		Free allocated buffers and release EMU HW used for
 *				EMIF bandwidth monitoring.
 *//*------------------------------------------------------------------------ */
static int trace_bw_init(unsigned int sample_count)
{
	uint32_t plib_major_ver;
	uint32_t plib_minor_ver;
	uint32_t plib_func_id;
	uint32_t pmod_func_id;
	unsigned int i, j;
	struct sci_config my_sci_config;
	enum sci_err my_sci_err;

	if (cpu_is_omap4430() || cpu_is_omap4460()) {
		printf(
			"omapconf: warning: EMIF BW not available on OMAP44[30-60], skipping it.\n");
		return OMAPCONF_ERR_CPU;
	} else if (!cpu_is_omap4470() && !cpu_is_omap54xx()) {
		printf(
			"omapconf: warning: CPU not yet supported, skipping it.\n");
		return OMAPCONF_ERR_CPU;
	}

	for (i = 0; i < 2; i++) {
		emif_bw_min[i] = 1000000.0; /* MB/s */
		emif_bw_max[i] = 0.0;
		emif_bw_avg[i] = 0.0;
	}

	/* Allocated needed buffers */
	for (i = 0; i < 2; i++)
		emif_bw[i] = NULL;
	for (i = 0; i < 2; i++) {
		emif_bw[i] = malloc(sample_count * sizeof(double));
		if (emif_bw[i] == NULL) {
			fprintf(stderr,
				"omapconf: could not allocate buffer for emif_bw[%d]!\n",
				i);
			for (j = 0; j <= i; j++) {
				if (emif_bw[i] != NULL)
					free(emif_bw[i]);
			}
			return OMAPCONF_ERR_NOT_AVAILABLE;
		}
	}

	for (i = 0; i < 8; i++)
		sci_cntrs_buf[i] = NULL;
	for (i = 0; i < 8; i++) {
		sci_cntrs_buf[i] = malloc(sample_count * sizeof(uint32_t));
		if (sci_cntrs_buf[i] == NULL) {
			fprintf(stderr,
				"omapconf: could not allocate buffer for sci_cntrs_buf[%d]!\n",
				i);
			for (j = 0; j <= i; j++) {
				if (sci_cntrs_buf[i] != NULL)
					free(sci_cntrs_buf[i]);
			}
			return OMAPCONF_ERR_NOT_AVAILABLE;
		}
	}

	/* Enable needed HW (statistical collectors) */
	powerdm_emu_enable();
	my_sci_config.errhandler = trace_bw_errhandler;
	my_sci_config.data_options = 0; /* Disable options */
	my_sci_config.trigger_enable = false;
	my_sci_config.sdram_msg_rate = 1;
	my_sci_config.mstr_msg_rate = 1;
	my_sci_config.mode = SCI_MODE_DUMP;
	my_sci_err = sci_open(&psci_hdl, &my_sci_config);
	if (my_sci_err != SCI_SUCCESS) {
		fprintf(stderr,
			"omapconf: could not configure SCI (%d)!\n",
			my_sci_err);
		powerdm_emu_disable();
		return OMAPCONF_ERR_INTERNAL;
	}

	sci_get_version(psci_hdl, &plib_major_ver,
		&plib_minor_ver, &plib_func_id,
		&pmod_func_id);
	if (plib_func_id != pmod_func_id) {
		fprintf(stderr,
			"omapconf: Error - func missmatch with device %d %d\n",
			plib_func_id,
			pmod_func_id);
		sci_close(&psci_hdl);
		powerdm_emu_disable();
		return OMAPCONF_ERR_INTERNAL;
	}

	/* Program counters to collect EMIF data */
	for (i = 0; i < num_use_cases; i++) {
		my_sci_err = sci_reg_usecase_sdram(
			psci_hdl, pmy_cfg[i],
			&my_usecase_key[i]);
		if (my_sci_err != SCI_SUCCESS)
			break;
		valid_usecase_cnt++;
	}

	/* Reset Counters */
	sci_global_disable(psci_hdl);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		trace_bw_deinit
 * @BRIEF		Free allocated buffers and release EMU HW used for
 *				EMIF bandwidth monitoring.
 * @DESCRIPTION		Free allocated buffers and release EMU HW used for
 *				EMIF bandwidth monitoring.
 *//*------------------------------------------------------------------------ */
static void trace_bw_deinit(void)
{
	unsigned int i;

	/* Free allocated buffers */
	for (i = 0; i < 2; i++) {
		if (emif_bw[i] != NULL)
			free(emif_bw[i]);
	}

	for (i = 0; i < 8; i++) {
		if (sci_cntrs_buf[i] != NULL)
			free(sci_cntrs_buf[i]);
	}

	/* Release HW */
	for (i = 0; i < valid_usecase_cnt; i++)
		sci_remove_usecase(psci_hdl, &my_usecase_key[i]);

	sci_global_disable(psci_hdl);
	sci_close(&psci_hdl);
	powerdm_emu_disable();
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		trace_bw_capture
 * @BRIEF		Collect data for EMIF bandwidth monitoring from
 *				HW counters.
 * @param[in]		index: sample number
 * @DESCRIPTION		Collect data for EMIF bandwidth monitoring from
 *				HW counters.
 *//*------------------------------------------------------------------------ */
static void trace_bw_capture(unsigned int index)
{
	uint32_t sci_cntrs[8];
	unsigned short i;

	/* Dump counters */
	sci_global_enable(psci_hdl);
	sci_dump_sdram_cntrs(num_use_cases, sci_cntrs);

	/* Save counters in buffer */
	dprintf("%s():\n", __func__);
	for (i = 0; i < 8; i++) {
		sci_cntrs_buf[i][index] = sci_cntrs[i];
		dprintf("buf[%d][%d]=%u ", i, index, sci_cntrs_buf[i][index]);
	}
	dprintf("\n\n");

	/* Reset counters */
	sci_global_disable(psci_hdl);
	sci_global_enable(psci_hdl);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		trace_bw_process
 * @BRIEF		Post-process data collected for
 *				EMIF bandwidth monitoring.
 * @param[in]		sample_count: number of samples collected
 * @param[in]		sampling_rate: sampling rate at which data
 *				were collected(in second)
 * @DESCRIPTION		Post-process data collected for
 *			EMIF bandwidth monitoring (convert to MB/s, compute
 *				average, detect min/max values).
 *//*------------------------------------------------------------------------ */
static void trace_bw_process(unsigned int sample_count, double sampling_rate)
{
	unsigned int i, j;

	dprintf("%s():\n", __func__);
	for (i = 1; i < sample_count; i++) {
		for (j = 0; j < 2; j++) {
			emif_bw[j][i] = ((double) sci_cntrs_buf[2 * j][i] +
				(double) sci_cntrs_buf[(2 * j) + 1][i]) /
					(1000000.0 * sampling_rate);
			if (emif_bw[j][i] < emif_bw_min[j])
				emif_bw_min[j] = emif_bw[j][i];
			if (emif_bw[j][i] > emif_bw_max[j])
				emif_bw_max[j] = emif_bw[j][i];
			emif_bw_avg[j] = avg_recalc(
				emif_bw_avg[j], emif_bw[j][i], i - 1);
		}
		dprintf(
			"emif_bw[0][%d]=%.2lf MB/s (W), emif_bw[0][%d]=%.2lf MB/s (R)\n",
			i, emif_bw[0][i], i, emif_bw[1][i]);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		trace_perf_capture
 * @BRIEF		perform performance trace
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_UNEXPECTED
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		cfgfile: Name of the config file
 *			(default: trace_config.dat)
 * @param[in]		prefix: prefix to be added to default output file names
 *			(NULL: no prefix added)
 * @param[in]		sampling_rate: sampling rate in sec (default: 0.1s)
 * @param[in]		capture_time: capture duration in sec (default: 10s)
 * @param[in]		delay_time: initial delay before capture starts,
 *			in sec (default: 0s)
 * @DESCRIPTION		trace a custom selection of key performance indicators
 *			(CPU Load, OPPs, memory bandwidth usage & temperatures).
 *			Also trace any generic input files included in config.
 *//*------------------------------------------------------------------------ */
int trace_perf_capture(const char *cfgfile, const char *prefix,
	double sampling_rate, unsigned int capture_time,
	unsigned int delay_time)
{
	char trace_perf_file[256] =
		"perf_trace.dat";
	char trace_perf_stats_file[256] =
		"perf_trace_stats.txt";
	char trace_perf_charts_script_file[256] =
		"perf_trace_draw_charts.plt";
	char trace_perf_jpg_script_file[256] =
		"perf_trace_create_jpg.plt";
	char trace_perf_jpg_file[256] =
		"perf_trace.jpg";
	#ifdef TRACE_DEBUG
	char *cwd;
	#endif

	unsigned int sample_cnt;
	int ret;
	unsigned int sample, file;
	FILE *fp = NULL;
	const int S_SIZE = 1024;
	char s[S_SIZE];
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row = 0;
	int i = 0;
	int p_flags[NUM_ITEMS];
	char cpu_name[CPU_FULL_NAME_MAX_LENGTH];
	char version[RELEASE_VERSION_MAX_LENGTH];
	char type[RELEASE_TYPE_MAX_LENGTH];
	char date[RELEASE_DATE_MAX_LENGTH];
	double height;
	int chart_count;

	/* Variables for generic traceable items */
	unsigned int cpu;
	unsigned int *idle[2] = {NULL, NULL}, *iowait[2], *sum[2];
	double cpu_load[3], cpu_load_min[3], cpu_load_max[3], cpu_load_avg[3];
	unsigned short *cpu1_online = NULL;
	unsigned int cpu1_online_cnt;
	FILE *test_file;
	char *geninput_names[TRACE_MAX_GENINPUTS];
	char *geninput_paths[TRACE_MAX_GENINPUTS];
	char *geninput_units[TRACE_MAX_GENINPUTS];
	int geninput_accumulating[TRACE_MAX_GENINPUTS];
	int geninput_flags[TRACE_MAX_GENINPUTS];
	int geninput_num, geninput_first = 0, geninput_last = 0;
	uint64_t *geninput_data[TRACE_MAX_GENINPUTS];
	uint64_t geninput_delta;
	uint64_t geninput_min[TRACE_MAX_GENINPUTS];
	uint64_t geninput_max[TRACE_MAX_GENINPUTS];
	double geninput_avg[TRACE_MAX_GENINPUTS];

	/* Variables for OMAP-specific traceable items */
	int *cpu_freq = NULL, cpu_freq_min, cpu_freq_max;
	int *gpu_freq = NULL, gpu_freq_min, gpu_freq_max;
	unsigned int delta_idle[3], delta_iowait[3], delta_sum[3];
	int *l3_freq = NULL, l3_freq_min, l3_freq_max;

	/* Variables for OMAP4-specific traceable items */
	unsigned short emif;
	unsigned int *emif_cycles = NULL;
	unsigned int *emif_busy_cycles = NULL;
	unsigned int emif_delta_cycles, emif_delta_busy_cycles;
	double emif_load, emif_load_min, emif_load_max, emif_load_avg;
	int *bandgap_temp = NULL;
	int bandgap_temp_min, bandgap_temp_max;
	double bandgap_temp_avg;
	int *pcb_temp = NULL;
	int pcb_temp_min, pcb_temp_max;
	double pcb_temp_avg;
	int *hotspot_mpu_temp = NULL;
	int hotspot_mpu_temp_min, hotspot_mpu_temp_max;
	double hotspot_mpu_temp_avg;

	/* Variables for OMAP5 temperature items */
	int *temps[TEMP54XX_ID_MAX];
	int temps_min[TEMP54XX_ID_MAX], temps_max[TEMP54XX_ID_MAX];
	double temps_avg[TEMP54XX_ID_MAX];

	/* Check arguments */
	CHECK_NULL_ARG(cfgfile, OMAPCONF_ERR_ARG);
	if (capture_time == 0) {
		fprintf(stderr, "omapconf: capture time == 0!!!\n\n");
		return OMAPCONF_ERR_ARG;
	}
	if (sampling_rate <= 0.0) {
		fprintf(stderr, "omapconf: sampling_rate (%lf) <= 0.0!!!\n\n",
			sampling_rate);
		return OMAPCONF_ERR_ARG;
	}
	dprintf(
		"%s(): cfgfile=%s prefix=%s sampling_rate=%lfs capture_time=%d delay_time=%d\n",
		__func__, cfgfile, prefix, sampling_rate, capture_time,
		delay_time);

	/* Generate output file names, including user-selected prefix */
	if (prefix != NULL) {
		memmove((void *) (trace_perf_file + strlen(prefix)),
			(void *) trace_perf_file,
			strlen(trace_perf_file));
		memcpy((void *) trace_perf_file, prefix, strlen(prefix));

		memmove((void *) (trace_perf_stats_file + strlen(prefix)),
			(void *) trace_perf_stats_file,
			strlen(trace_perf_stats_file));
		memcpy((void *) trace_perf_stats_file, prefix, strlen(prefix));

		memmove((void *) (trace_perf_charts_script_file +
				strlen(prefix)),
			(void *) trace_perf_charts_script_file,
			strlen(trace_perf_charts_script_file));
		memcpy((void *) trace_perf_charts_script_file, prefix,
			strlen(prefix));

		memmove((void *) (trace_perf_jpg_script_file + strlen(prefix)),
			(void *) trace_perf_jpg_script_file,
			strlen(trace_perf_jpg_script_file));
		memcpy((void *) trace_perf_jpg_script_file, prefix,
			strlen(prefix));

		memmove((void *) (trace_perf_jpg_file + strlen(prefix)),
			(void *) trace_perf_jpg_file,
			strlen(trace_perf_jpg_file));
		memcpy((void *) trace_perf_jpg_file, prefix, strlen(prefix));
	}
	dprintf("%s(): output filenames:\n", __func__);
	dprintf("  trace_perf_file=%s\n", trace_perf_file);
	dprintf("  trace_perf_stats_file=%s\n", trace_perf_stats_file);
	dprintf("  trace_perf_charts_script_file=%s\n",
		trace_perf_charts_script_file);
	dprintf("  trace_perf_jpg_script_file=%s\n",
		trace_perf_jpg_script_file);
	dprintf("  trace_perf_jpg_file=%s\n\n", trace_perf_jpg_file);

	/*
	 * Change the default working directory, the current one may not be
	 * writable. Use "/data" as known to be writable (or remountable).
	 */
	if (chdir("/data")) {
		dprintf("%s: unable to chdir to /data, using curdir\n",
			__func__);
		/* ignore and continue in current directory */
	}
	#ifdef TRACE_DEBUG
	cwd = getcwd(NULL, 0);
	printf("%s(): current working directory is %s\n", __func__, cwd);
	free(cwd);
	#endif

	/* Read the config file into an array of flags */
	ret = trace_config_read(cfgfile, p_flags);
	if ((ret == -1) &&
		(strcmp(cfgfile, trace_perf_default_cfgfile) == 0)) {
		printf(
			"\nomapconf: default configuration file ('%s') not found. Creating it.\n",
			cfgfile);
		fp = fopen(cfgfile, "w");
		if (fp == NULL) {
			fprintf(stderr,
				"omapconf: %s(): could not create configuration file ('%s') with write permission!\n",
				__func__, cfgfile);
			return OMAPCONF_ERR_NOT_AVAILABLE;
		}
		trace_default_cfg_create(fp);
		fclose(fp);
		ret = trace_config_read(cfgfile, p_flags);
	} else if (ret == -1) {
		fprintf(stderr,
			"omapconf: error could not open configuration file ('%s') file!!!\n\n",
			cfgfile);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	} else if (ret < 0) {
		fprintf(stderr,
			"omapconf: error reading trace perf configuration file ('%s', %d)!!!\n\n",
			cfgfile, ret);
		return OMAPCONF_ERR_UNEXPECTED;
	}
	dprintf("%s(): # of items to trace: %d.\n", __func__, ret);

	/* Read the config file for generic input files */
	geninput_num = trace_geninput_config_read(cfgfile, geninput_names,
		geninput_paths, geninput_units, geninput_accumulating,
		geninput_flags);
	if (geninput_num < 0) {
		fprintf(stderr,
			"omapconf: error reading config file for generic inputs (%s, %d)\n\n",
			cfgfile, geninput_num);
		return OMAPCONF_ERR_UNEXPECTED;
	}
	dprintf("%s(): # of generic input to trace: %d.\n",
		__func__, geninput_num);

	/* Validate the geninput paths */
	for (i = 0; i < geninput_num; i++) {
		test_file = fopen(geninput_paths[i], "r");
		if (test_file == NULL) {
			fprintf(stderr,
				"omapconf: error generic input file '%s' at path '%s' could not be opened!!!\n\n",
				geninput_names[i], geninput_paths[i]);
			return OMAPCONF_ERR_NOT_AVAILABLE;
		}
		fclose(test_file);
	}

	/* Tracing Total CPU Load requires tracing CPU0/1 Load */
	if (p_flags[TOTAL_CPU_LOAD] &&
		!(p_flags[CPU0_LOAD] && p_flags[CPU1_LOAD])) {
		printf(
			"Warning: tracing total CPU load requires tracing individual CPU loads. All CPU loads will be traced.\n\n");
		p_flags[CPU0_LOAD] = 1;
		p_flags[CPU1_LOAD] = 1;
	}

	/* Init statistic variables */
	cpu1_online_cnt = 0; /* CPU1 Online Time */
	/* CPU Frequency, L3 Frequency, GPU Frequency Min */
	cpu_freq_min = l3_freq_min = gpu_freq_min = 100000;
	/* CPU Frequency, L3 Frequency, GPU Frequency Max */
	cpu_freq_max = l3_freq_max = gpu_freq_max = 0;
	for (cpu = 0; cpu <= 2; cpu++) {
		cpu_load_min[cpu] = (double) 200; /* CPU0/1 Load Min */
		cpu_load_max[cpu] = 0.0; /* CPU0/1 Load Max */
		cpu_load_avg[cpu] = 0.0; /* CPU0/1 Load Avg */
	}
	emif_load_min = (double) 200; /* EMIF Load Min */
	emif_load_max = 0.0; /* EMIF Load Max */
	emif_load_avg = 0.0; /* EMIF Load Avg */
	bandgap_temp_min = 200; /* Bandgap Temp Min */
	bandgap_temp_max = TEMP_ABSOLUTE_ZERO; /* Bandgap Temp Max */
	bandgap_temp_avg = 0.0; /* Bandgap Temp Avg */
	pcb_temp_min = 200; /* PCB Temp Min */
	pcb_temp_max = TEMP_ABSOLUTE_ZERO; /* PCB Temp Max */
	pcb_temp_avg = 0.0; /* PCB Temp Avg */
	hotspot_mpu_temp_min = 200;
	hotspot_mpu_temp_max = TEMP_ABSOLUTE_ZERO;
	hotspot_mpu_temp_avg = 0.0;
	for (i = 0; i < (int) TEMP54XX_ID_MAX; i++) {
		temps_min[i] = 200;
		temps_max[i] = TEMP_ABSOLUTE_ZERO ;
		temps_avg[i] = 0.0;
		temps[i] = NULL;
	}
	for (i = 0; i < TRACE_MAX_GENINPUTS; i++) {
		geninput_data[i] = NULL;
		geninput_min[i] = UINT64_MAX;
		geninput_max[i] = 0;
		geninput_avg[i] = (double) 0;
	}


	/* Allocate buffer to store sampled data */
	sample_cnt = 1 + ((capture_time * 1000) / (sampling_rate * 1000));
	dprintf("%s(): capture_time=%us, sample_cnt=%u\n", __func__,
		capture_time, sample_cnt);
	for (cpu = 0; cpu < 2; cpu++) {
		idle[cpu] = malloc(sample_cnt * sizeof(unsigned int));
		if (idle[cpu] == NULL) {
			fprintf(stderr,
				"omapconf: could not allocate buffer for CPU%d idle!\n",
				cpu);
			ret = OMAPCONF_ERR_NOT_AVAILABLE;
			goto trace_perf_capture_err;
		}
		iowait[cpu] = malloc(sample_cnt * sizeof(unsigned int));
		if (iowait[cpu] == NULL) {
			fprintf(stderr,
				"omapconf: could not allocate buffer for CPU%d iowait!\n",
				cpu);
			ret = OMAPCONF_ERR_NOT_AVAILABLE;
			goto trace_perf_capture_err;
		}
		sum[cpu] = malloc(sample_cnt * sizeof(unsigned int));
		if (sum[cpu] == NULL) {
			fprintf(stderr,
				"omapconf: could not allocate buffer for CPU%d sum!\n",
				cpu);
			ret = OMAPCONF_ERR_NOT_AVAILABLE;
			goto trace_perf_capture_err;
		}
	}

	/*
	 * Allocate this buffer no matter what because other traces
	 * depend on it
	 */
	cpu1_online = malloc(sample_cnt * sizeof(unsigned short));
	if (cpu1_online == NULL) {
		fprintf(stderr,
			"omapconf: could not allocate buffer for cpu1_online!\n");
		ret = OMAPCONF_ERR_NOT_AVAILABLE;
		goto trace_perf_capture_err;
	}

	if (p_flags[CPU_FREQ]) {
		if (cpu_is_omap44xx() || cpu_is_omap54xx()) {
			cpu_freq = malloc(sample_cnt * sizeof(int));
			if (cpu_freq == NULL) {
				fprintf(stderr,
					"omapconf: could not allocate buffer for cpu_freq!\n");
				ret = OMAPCONF_ERR_NOT_AVAILABLE;
				goto trace_perf_capture_err;
			}
		} else {
			printf(
				"omapconf: warning: CPU Frequency not available (CPU not supported), skipping it.\n");
			p_flags[CPU_FREQ] = 0;
		}
	}

	if (p_flags[GPU_FREQ]) {
		if (cpu_is_omap44xx() || cpu_is_omap54xx()) {
			gpu_freq = malloc(sample_cnt * sizeof(int));
			if (gpu_freq == NULL) {
				fprintf(stderr,
					"omapconf: could not allocate buffer for gpu_freq!\n");
				ret = OMAPCONF_ERR_NOT_AVAILABLE;
				goto trace_perf_capture_err;
			}
		} else {
			printf(
				"omapconf: warning: GPU Frequency not available (CPU not supported), skipping it.\n");
			p_flags[GPU_FREQ] = 0;
		}
	}

	if (p_flags[EMIF_LOAD]) {
		if (cpu_is_omap44xx() | cpu_is_dra7xx()) {
			/* Configure counters to count data bus busy cycles */
			ret = emif44xx_perf_cnt_configure(EMIF44XX_0,
				EMIF44XX_PERF_CNT_1,
				EMIF44XX_PERF_CNT_FILTER_DATA_TRANSFER_CYCLES,
				0, 0);
			ret |= emif44xx_perf_cnt_configure(EMIF44XX_1,
				EMIF44XX_PERF_CNT_1,
				EMIF44XX_PERF_CNT_FILTER_DATA_TRANSFER_CYCLES,
				0, 0);
			if (ret != 0) {
				fprintf(stderr,
					"omapconf: error while configuring EMIF performance counters!!! (%d)\n",
					ret);
				ret = OMAPCONF_ERR_UNEXPECTED;
				goto trace_perf_capture_err;
			}

			emif_busy_cycles = malloc(
				sample_cnt * sizeof(unsigned int));
			if (emif_busy_cycles == NULL) {
				fprintf(stderr,
					"omapconf: could not allocate buffer for emif_busy_cycles!\n");
				ret = OMAPCONF_ERR_NOT_AVAILABLE;
				goto trace_perf_capture_err;
			}
			emif_cycles = malloc(sample_cnt * sizeof(unsigned int));
			if (emif_cycles == NULL) {
				fprintf(stderr,
					"omapconf: could not allocate buffer for emif_cycles!\n");
				ret = OMAPCONF_ERR_NOT_AVAILABLE;
				goto trace_perf_capture_err;
			}
		} else {
			printf(
				"omapconf: warning: EMIF LOAD not available (CPU not supported), skipping it.\n");
			p_flags[EMIF_LOAD] = 0;
		}
	}

	if (p_flags[EMIF_BW]) {
		ret = trace_bw_init(sample_cnt);
		if (ret != 0) {
			printf(
				"omapconf: warning: EMIF BW not available (CPU not supported), skipping it.\n");
			p_flags[EMIF_BW] = 0;
		}
	}

	if (p_flags[L3_FREQ]) {
		if (cpu_is_omap44xx() || cpu_is_omap54xx()) {
			l3_freq = malloc(sample_cnt * sizeof(int));
			if (l3_freq == NULL) {
				fprintf(stderr,
					"omapconf: could not allocate buffer for l3_freq!\n");
				ret = OMAPCONF_ERR_NOT_AVAILABLE;
				goto trace_perf_capture_err;
			}
		} else {
			printf(
				"omapconf: warning: L3 Frequency not available (CPU not supported), skipping it.\n");
			p_flags[L3_FREQ] = 0;
		}
	}

	if (p_flags[BANDGAP_TEMP]) {
		if (cpu_is_omap44xx()) {
			bandgap_temp = malloc(sample_cnt * sizeof(int));
			if (bandgap_temp == NULL) {
				fprintf(stderr,
					"omapconf: could not allocate buffer for bandgap_temp!\n");
				ret = OMAPCONF_ERR_NOT_AVAILABLE;
				goto trace_perf_capture_err;
			}
		} else {
			fprintf(stderr,
				"omapconf: warning: BANDGAP temperature sensor not available, skipping it.\n");
			p_flags[BANDGAP_TEMP] = 0;
		}
	}

	if (p_flags[PCB_TEMP]) {
		if (cpu_is_omap4460() || cpu_is_omap4470() ||
			cpu_is_omap54xx()) {
			pcb_temp = malloc(sample_cnt * sizeof(int));
			if (pcb_temp == NULL) {
				fprintf(stderr,
					"omapconf: could not allocate buffer for pcb_temp!\n");
				ret = OMAPCONF_ERR_NOT_AVAILABLE;
				goto trace_perf_capture_err;
			}
		} else {
			printf(
				"omapconf: warning: PCB temperature sensor not available, skipping it.\n");
			p_flags[PCB_TEMP] = 0;
		}
	}

	if (p_flags[HOTSPOT_MPU_TEMP]) {
		if ((cpu_is_omap44xx() || cpu_is_omap54xx()) &&
			(temp_sensor_get(TEMP_SENSOR_HOTSPOT_MPU) !=
				TEMP_ABSOLUTE_ZERO)) {
			hotspot_mpu_temp = malloc(sample_cnt * sizeof(int));
			if (hotspot_mpu_temp == NULL) {
				fprintf(stderr,
					"omapconf: could not allocate buffer for hotspot_mpu_temp!\n");
				ret = OMAPCONF_ERR_NOT_AVAILABLE;
				goto trace_perf_capture_err;
			}
		} else {
			fprintf(stderr,
				"omapconf: warning: HOTSPOT temperature sensor not available, skipping it.\n");
			p_flags[HOTSPOT_MPU_TEMP] = 0;
		}
	}

	if (p_flags[MPU_TEMP]) {
		if (cpu_is_omap54xx()) {
			temps[TEMP54XX_MPU] = malloc(sample_cnt * sizeof(int));
			if (temps[TEMP54XX_MPU] == NULL) {
				fprintf(stderr,
					"omapconf: could not allocate buffer for temps[TEMP54XX_MPU]!\n");
				ret = OMAPCONF_ERR_NOT_AVAILABLE;
				goto trace_perf_capture_err;
			}
		} else {
			fprintf(stderr,
				"omapconf: warning: MPU temperature sensor not available, skipping it.\n");
			p_flags[MPU_TEMP] = 0;
		}
	}

	if (p_flags[GPU_TEMP]) {
		if (cpu_is_omap54xx()) {
			temps[TEMP54XX_GPU] = malloc(sample_cnt * sizeof(int));
			if (temps[TEMP54XX_GPU] == NULL) {
				fprintf(stderr,
					"omapconf: could not allocate buffer for temps[TEMP54XX_GPU]!\n");
				ret = OMAPCONF_ERR_NOT_AVAILABLE;
				goto trace_perf_capture_err;
			}
		} else {
			fprintf(stderr,
				"omapconf: warning: GPU temperature sensor not available, skipping it.\n");
			p_flags[GPU_TEMP] = 0;
		}
	}

	if (p_flags[CORE_TEMP]) {
		if (cpu_is_omap54xx()) {
			temps[TEMP54XX_CORE] = malloc(sample_cnt * sizeof(int));
			if (temps[TEMP54XX_CORE] == NULL) {
				fprintf(stderr,
					"omapconf: could not allocate buffer for temps[TEMP54XX_CORE]!\n");
				ret = OMAPCONF_ERR_NOT_AVAILABLE;
				goto trace_perf_capture_err;
			}
		} else {
			fprintf(stderr,
				"omapconf: warning: CORE temperature sensor not available, skipping it.\n");
			p_flags[CORE_TEMP] = 0;
		}
	}

	if (p_flags[CASE_TEMP]) {
		if (cpu_is_omap54xx()) {
			temps[TEMP54XX_CASE] = malloc(sample_cnt * sizeof(int));
			if (temps[TEMP54XX_CASE] == NULL) {
				fprintf(stderr,
					"omapconf: could not allocate buffer for temps[TEMP54XX_CASE]!\n");
				ret = OMAPCONF_ERR_NOT_AVAILABLE;
				goto trace_perf_capture_err;
			}
		} else {
			fprintf(stderr,
				"omapconf: warning: CASE temperature sensor not available, skipping it.\n");
			p_flags[CASE_TEMP] = 0;
		}
	}

	for (i = 0; i < geninput_num; i++) {
		if (geninput_flags[i]) {
			geninput_data[i] = malloc(
				sample_cnt * sizeof(uint64_t));
			if (geninput_data[i] == NULL) {
				fprintf(stderr,
					"omapconf: could not allocate buffer for geninput_data #%d!\n",
					i);
				ret = OMAPCONF_ERR_NOT_AVAILABLE;
				goto trace_perf_capture_err;
			}
		}
	}

	/* Sample performance indicators periodically */
	printf("\n");
	printf("NB:\n");
	printf("  * This is an intrusive trace (counters polling).\n");
	printf("    Idle C-States usage was altered.\n");
	printf("    Limited additional CPU & EMIFs loads generated.\n");
	printf("  * If CPU1 Load = -5.0, it means CPU1 is OFFLINE.\n");
	printf("  * CPU LOADS CANNOT be converted to Mhz.\n");
	printf("    OPP may have changed during the audit.\n");
	printf(
		"  * EMIF Data Bus Load CANNOT be converted to memory bandwidth (MB/s).\n");
	printf(
		"    DDR data busy cycles may be commands (not data) and data size is unknown.\n\n");

	/* Initial delay before starting capture */
	if (delay_time >= 1) {
		printf(
			"\nWaiting for initial delay (%u sec), then start sampling performance indicators during %us (%.3lfs sampling rate). Please wait...\n",
			delay_time, capture_time, sampling_rate);
		sleep(delay_time);
	} else {
		printf(
			"\nSampling performance indicators during %us (%.3lfs sampling rate). Please wait...\n",
			capture_time, sampling_rate);
	}

	for (sample = 0; sample < sample_cnt; sample++) {
		/* FIXME: handle generic number of CPU cores */
		/* Get CPU runtime execution stats */
		for (cpu = 0; cpu < 2; cpu++) {
			ret = cpu_proc_stats_get(cpu, &idle[cpu][sample],
				&iowait[cpu][sample], &sum[cpu][sample]);
			dprintf("%s(): CPU%u idle=%u, iowait=%u, sum=%u\n",
				__func__, cpu, idle[cpu][sample],
				iowait[cpu][sample], sum[cpu][sample]);
		}

		/* Always trace because other traces depend on this */
		/* Get CPU1 online status */
		cpu1_online[sample] = (ret == 0);
		dprintf("%s(): cpu1_online = %u\n", __func__,
			cpu1_online[sample]);

		if (p_flags[CPU_FREQ]) {
			/* Get current CPU frequency (MHz) */
			if (cpu_is_omap44xx())
				cpu_freq[sample] =
					(int) clk44xx_get_clock_speed(
						OMAP4_MPU_DPLL_CLK, 0);
			else
				cpu_freq[sample] =
					module_clk_rate_get(MOD_MPU, 0) / 1000;
			dprintf("%s(): cpu_freq = %uMHz\n", __func__,
				cpu_freq[sample]);
		}

		if (p_flags[EMIF_LOAD]) {
			/* Get EMIF total & data transfer cycles */
			emif_busy_cycles[sample] = 0;
			for (emif = 0; emif < EMIF44XX_MAX; emif++) {
				emif_busy_cycles[sample] +=
					emif44xx_perf_cnt_get_count(
						(emif44xx_ids) emif,
						EMIF44XX_PERF_CNT_1);
			}
			emif_cycles[sample] =
				emif44xx_perf_cnt_get_time(EMIF44XX_0);
			dprintf("%s(): EMIF busy cycles=%u\n", __func__,
				emif_busy_cycles[sample]);
			dprintf("%s(): EMIF cycles=%u\n", __func__,
				emif_cycles[sample]);
		}

		if (p_flags[EMIF_BW])
			trace_bw_capture(sample);

		if (p_flags[L3_FREQ]) {
			/* Get L3 frequency (MHz) */
			if (cpu_is_omap44xx())
				l3_freq[sample] =
					(int) clk44xx_get_clock_speed(
						OMAP4_L3_ICLK, 0);
			else
				l3_freq[sample] =
					module_clk_rate_get(MOD_L3_MAIN1_INTERCONNECT, 0) / 1000;
			dprintf("%s(): l3_freq = %uMHz\n",
				__func__, l3_freq[sample]);
		}

		if (p_flags[GPU_FREQ]) {
			/* Get current GPU frequency (MHz) */
			if (cpu_is_omap44xx())
				gpu_freq[sample] =
					(unsigned int) clk44xx_get_clock_speed(
						OMAP4_GFX_FCLK, 0);
			else
				gpu_freq[sample] =
					module_clk_rate_get(MOD_GPU, 0) / 1000;
			dprintf("%s(): gpu_freq = %uMHz\n",
				__func__, gpu_freq[sample]);
		}

		/* Get bandgap sensor temperature */
		if (p_flags[BANDGAP_TEMP]) {
			bandgap_temp[sample] =
				temp_sensor_get(TEMP_SENSOR_BANDGAP);
			dprintf("%s(): bandgap_temp = %dC\n", __func__,
				bandgap_temp[sample]);
		}

		/* Get PCB sensor temperature */
		if (p_flags[PCB_TEMP]) {
			pcb_temp[sample] = temp_sensor_get(TEMP_SENSOR_PCB);
			dprintf("%s(): pcb_temp = %dC\n", __func__,
				pcb_temp[sample]);
		}

		/* Get HOTSPOT temperature */
		if (p_flags[HOTSPOT_MPU_TEMP]) {
			hotspot_mpu_temp[sample] =
				temp_sensor_get(TEMP_SENSOR_HOTSPOT_MPU);
			dprintf("%s(): hotspot_mpu_temp = %dC\n", __func__,
				hotspot_mpu_temp[sample]);
		}

		/* Get CPU sensor temperature */
		if (p_flags[MPU_TEMP]) {
			temps[TEMP54XX_MPU][sample] =
				temp54xx_get(TEMP54XX_MPU);
			dprintf("%s(): cpu_temp = %dC\n", __func__,
				temps[TEMP54XX_MPU][sample]);
		}

		/* Get GPU sensor temperature */
		if (p_flags[GPU_TEMP]) {
			temps[TEMP54XX_GPU][sample] =
				temp54xx_get(TEMP54XX_GPU);
			dprintf("%s(): gpu_temp = %dC\n", __func__,
				temps[TEMP54XX_GPU][sample]);
		}

		/* Get CORE sensor temperature */
		if (p_flags[CORE_TEMP]) {
			temps[TEMP54XX_CORE][sample] =
				temp54xx_get(TEMP54XX_CORE);
			dprintf("%s(): core_temp = %dC\n", __func__,
				temps[TEMP54XX_CORE][sample]);
		}

		/* Get CASE sensor temperature */
		if (p_flags[CASE_TEMP]) {
			temps[TEMP54XX_CASE][sample] =
				temp54xx_get(TEMP54XX_CASE);
			dprintf("%s(): case_temp = %dC\n", __func__,
				temps[TEMP54XX_CASE][sample]);
		}

		/* Get Geninput Data */
		for (i = 0; i < geninput_num; i++) {
			if (geninput_flags[i]) {
				geninput_data[i][sample] =
					trace_geninput_file2int(
						geninput_paths[i]);
				dprintf("%s(): %s = %llu\n", __func__,
					geninput_names[i],
					geninput_data[i][sample]);

				if (geninput_data[i][sample] == UINT64_MAX) {
					printf(
						"\nError Reading Generic Input: %s\n",
						geninput_names[i]);
				}
			}
		}

		dprintf("\n");
		/* Sleep for some time before sampling again */
		if (sampling_rate < 1)
			usleep((unsigned int) (sampling_rate * 1000000));
		else
			sleep((unsigned int) sampling_rate);
	}

	printf("Sampling done, processing and saving data...\n");

	if (p_flags[EMIF_BW])
		trace_bw_process(sample_cnt, sampling_rate);

	/* Open trace output file */
	fp = workdir_fopen(trace_perf_file, "w");
	if (fp == NULL) {
		fprintf(stderr, "%s(): could not create %s!\n",
			__func__, trace_perf_file);
		ret = OMAPCONF_ERR_NOT_AVAILABLE;
		goto trace_perf_capture_err;
	}
	fprintf(fp, "#\n");
	fprintf(fp,
		"# -------------------- Performance Trace -----------------\n");
	fprintf(fp, "# NB:\n");
	fprintf(fp, "#   * This is an intrusive trace (counters polling).\n");
	fprintf(fp, "#     Idle C-States usage was altered.\n");
	fprintf(fp, "#     Limited additional CPU & EMIFs loads generated.\n");
	fprintf(fp, "#   * If CPU1 Load = -5.0, it means CPU1 is OFFLINE.\n");
	fprintf(fp,
		"#   * If CPU/GPU/L3 rate = -7.0, it means rate could not be retrieved.\n");
	fprintf(fp, "#\n");
	fprintf(fp, "#   * CPU LOADS CANNOT be directly converted to Mhz.\n");
	fprintf(fp, "#     OPP may have changed during the audit.\n");
	fprintf(fp,
		"#   * EMIF Data Bus Load CANNOT be converted to memory bandwidth (MB/s).\n");
	fprintf(fp,
		"#     DDR data busy cycles may be commands (not data) and data size is unknown.\n");
	fprintf(fp, "#\n");
	if (!cpu_is_omap44xx() && !cpu_is_omap54xx())
		fprintf(fp, "# CPU: UNKNOWN\n");
	else
		fprintf(fp, "# CPU: %s\n", cpu_full_name_get(cpu_name));
	if (release_details_get(version, type, date) != NULL)
		fprintf(fp, "# RELEASE: %s\n", version);
	else
		fprintf(fp, "# RELEASE: UNKNOWN\n");
	fprintf(fp, "#\n");
	fprintf(fp, "# Trace Length: %us\n", capture_time);
	fprintf(fp, "# Trace Sampling Rate: %.1lfs\n", sampling_rate);
	fprintf(fp, "# Number of samples: %u\n", sample_cnt - 1);
	fprintf(fp, "#\n");
	fprintf(fp, "# Columns:\n");
	fprintf(fp, "# 01: Timestamp (unit: s)\n");
	for (i = 0; i < NUM_ITEMS; i++) {
		if (i == CPU1_ONLINE_TIME) {
			continue;
		} else if (i < CPU1_ONLINE_TIME) {
			fprintf(fp, "# %02d: %s (unit: %s)\n", i + 2,
				traceables_names[i], traceables_unit[i]);
		} else if (i < EMIF_BW) {
			fprintf(fp, "# %02d: %s (unit: %s)\n", i + 1,
				traceables_names[i], traceables_unit[i]);
		} else if (i == EMIF_BW) {
			fprintf(fp, "# %02d: %s (WRITE) (unit: %s)\n", i + 1,
				traceables_names[i], traceables_unit[i]);
			fprintf(fp, "# %02d: %s (READ) (unit: %s)\n", i + 2,
				traceables_names[i], traceables_unit[i]);
		} else {
			fprintf(fp, "# %02d: %s (unit: %s)\n", i + 2,
				traceables_names[i], traceables_unit[i]);
		}
	}
	/* Geninput Names */
	for (i = 0; i < geninput_num; i++)
		fprintf(fp, "# %02d: %s (unit: %s)\n", NUM_ITEMS + 1 + i,
			geninput_names[i], geninput_units[i]);
	fprintf(fp, "#\n");
	fprintf(fp,
		"# ----------------------- Trace START --------------------\n");
	snprintf(s, S_SIZE,  "# Timestamp (s)");
	for (sample = 1; sample < sample_cnt; sample++) {
		/* Save timestamp */
		sprintf(s, "%.3lf", sample * sampling_rate);
		fprintf(fp, "%s", s);

		/* Compute and save CPU loads */
		for (cpu = 0; cpu < 2; cpu++) {
			if (cpu == 1 && p_flags[CPU1_ONLINE_TIME]) {
				if (cpu1_online[sample] == 0) {
					dprintf("CPU1 offline\n");
					fputs(", -5.0", fp);
					continue;
				} else {
					cpu1_online_cnt++;
				}
			}
			delta_idle[cpu] = count32_delta(idle[cpu][sample - 1],
				idle[cpu][sample]);
			delta_iowait[cpu] =
				count32_delta(iowait[cpu][sample - 1],
					iowait[cpu][sample]);
			delta_sum[cpu] = count32_delta(
				sum[cpu][sample - 1],
				sum[cpu][sample]);
			dprintf(
				"%s(): CPU%u delta_idle=%u, delta_iowait=%u, delta_sum=%u\n",
				__func__, cpu, delta_idle[cpu],
				delta_iowait[cpu], delta_sum[cpu]);

			if ((cpu == 0 && p_flags[CPU0_LOAD]) ||
				(cpu == 1 && p_flags[CPU1_LOAD])) {
				/* Compute load */
				if (delta_sum[cpu] != 0)
					cpu_load[cpu] =
						cpu_load_get(delta_idle[cpu],
							delta_iowait[cpu],
							delta_sum[cpu]);
				else
					/*
					 * Due to tickless feature, possible
					 * that no tick occured during this
					 * sampling window and so /proc/stat
					 * counters were not incremented.
					 * => cpu load = 0.
					 */
					cpu_load[cpu] = 0.0;
				dprintf("%s(): CPU%u load=%.2lf%%\n",
					__func__, cpu, cpu_load[cpu]);
				if (cpu_load[cpu] < cpu_load_min[cpu])
					cpu_load_min[cpu] = cpu_load[cpu];
				if (cpu_load[cpu] > cpu_load_max[cpu])
					cpu_load_max[cpu] = cpu_load[cpu];
				cpu_load_avg[cpu] = avg_recalc(
					cpu_load_avg[cpu],
					cpu_load[cpu], sample - 1);

				/* Save load into trace file */
				sprintf(s, "%.2lf", cpu_load[cpu]);
				fprintf(fp, ", %s", s);
			}
		}

		if (p_flags[TOTAL_CPU_LOAD]) {
			/* Compute and save total CPU loads */
			if (cpu1_online[sample])
				cpu_load[2] = (cpu_load[0] + cpu_load[1]) / 2.0;
			else
				cpu_load[2] = cpu_load[0];
			if (cpu_load[2] < cpu_load_min[2])
				cpu_load_min[2] = cpu_load[2];
			if (cpu_load[2] > cpu_load_max[2])
				cpu_load_max[2] = cpu_load[2];
			cpu_load_avg[2] = avg_recalc(
				cpu_load_avg[2], cpu_load[2], sample - 1);
			sprintf(s, "%.2lf", cpu_load[2]);
			fprintf(fp, ", %s", s);
		} else {
			fputs(", NA", fp);
		}

		if (p_flags[CPU_FREQ]) {
			/* Save CPU frequency */
			sprintf(s, "%d", cpu_freq[sample]);
			fprintf(fp, ", %s", s);
			if (cpu_freq[sample] < cpu_freq_min)
				cpu_freq_min = cpu_freq[sample];
			if (cpu_freq[sample] > cpu_freq_max)
				cpu_freq_max = cpu_freq[sample];
		} else {
			fputs(", NA", fp);
		}

		if (p_flags[GPU_FREQ]) {
			/* Save GPU frequency */
			sprintf(s, "%d", gpu_freq[sample]);
			fprintf(fp, ", %s", s);
			if (gpu_freq[sample] < gpu_freq_min)
				gpu_freq_min = gpu_freq[sample];
			if (gpu_freq[sample] > gpu_freq_max)
				gpu_freq_max = gpu_freq[sample];
		} else {
			fputs(", NA", fp);
		}

		if (p_flags[L3_FREQ]) {
			/* Save L3 frequency */
			sprintf(s, "%d", l3_freq[sample]);
			fprintf(fp, ", %s", s);
			if (l3_freq[sample] < l3_freq_min)
				l3_freq_min = l3_freq[sample];
			if (l3_freq[sample] > l3_freq_max)
				l3_freq_max = l3_freq[sample];
		} else {
			fputs(", NA", fp);
		}

		if (p_flags[EMIF_BW]) {
			sprintf(s, "%.2lf", emif_bw[0][sample]);
			fprintf(fp, ", %s", s);
			sprintf(s, "%.2lf", emif_bw[1][sample]);
			fprintf(fp, ", %s", s);
		} else {
			fputs(", NA", fp);
		}

		if (p_flags[EMIF_LOAD]) {
			/* Compute and save EMIF load (total) */
			emif_delta_busy_cycles = count32_delta(
				emif_busy_cycles[sample - 1],
				emif_busy_cycles[sample]);
			emif_delta_cycles = 2 * count32_delta(
				emif_cycles[sample - 1], emif_cycles[sample]);
			dprintf(
				"%s(): EMIF delta_busy_cycles=%u, delta_cycles=%u\n",
				__func__, emif_delta_busy_cycles,
				emif_delta_cycles);
			if (emif_delta_cycles == 0)
				emif_load = 0.0;
			else
				emif_load = 100.0 * (
					(double) emif_delta_busy_cycles /
						emif_delta_cycles);
			dprintf("%s(): EMIF load = %lf%%\n",
				__func__, emif_load);
			if (emif_load < emif_load_min)
				emif_load_min = emif_load;
			if (emif_load > emif_load_max)
				emif_load_max = emif_load;
			emif_load_avg = avg_recalc(emif_load_avg,
				emif_load, sample - 1);
			sprintf(s, "%.2lf", (double) emif_load);
			fprintf(fp, ", %s", s);
		} else {
			fputs(", NA", fp);
		}

		if (p_flags[BANDGAP_TEMP]) {
			/* Compute and save bandgap temperature */
			if (bandgap_temp[sample] > bandgap_temp_max)
				bandgap_temp_max = bandgap_temp[sample];
			if (bandgap_temp[sample] < bandgap_temp_min)
				bandgap_temp_min = bandgap_temp[sample];
			bandgap_temp_avg = avg_recalc(bandgap_temp_avg,
				bandgap_temp[sample], sample - 1);
			sprintf(s, "%d", bandgap_temp[sample]);
			fprintf(fp, ", %s", s);
		} else {
			fputs(", NA", fp);
		}

		/* Compute and save PCB temperature */
		if (p_flags[PCB_TEMP]) {
			if (pcb_temp[sample] > pcb_temp_max)
				pcb_temp_max = pcb_temp[sample];
			if (pcb_temp[sample] < pcb_temp_min)
				pcb_temp_min = pcb_temp[sample];
			pcb_temp_avg = avg_recalc(pcb_temp_avg,
				pcb_temp[sample], sample - 1);
			sprintf(s, "%d", pcb_temp[sample]);
			fprintf(fp, ", %s", s);
		} else {
			fputs(", NA", fp);
		}

		/* Compute and save HOTSPOT temperature */
		if (p_flags[HOTSPOT_MPU_TEMP]) {
			if (hotspot_mpu_temp[sample] > hotspot_mpu_temp_max)
				hotspot_mpu_temp_max = hotspot_mpu_temp[sample];
			if (hotspot_mpu_temp[sample] < hotspot_mpu_temp_min)
				hotspot_mpu_temp_min = hotspot_mpu_temp[sample];
			hotspot_mpu_temp_avg = avg_recalc(hotspot_mpu_temp_avg,
				hotspot_mpu_temp[sample], sample - 1);
			sprintf(s, "%d", hotspot_mpu_temp[sample]);
			fprintf(fp, ", %s", s);
		} else {
			fputs(", NA", fp);
		}

		/* Compute and save CPU sensor temperature */
		if (p_flags[MPU_TEMP]) {
			if (temps[TEMP54XX_MPU][sample] >
				temps_max[TEMP54XX_MPU])
				temps_max[TEMP54XX_MPU] =
					temps[TEMP54XX_MPU][sample];
			if (temps[TEMP54XX_MPU][sample] <
				temps_min[TEMP54XX_MPU])
				temps_min[TEMP54XX_MPU] =
					temps[TEMP54XX_MPU][sample];
			temps_avg[TEMP54XX_MPU] = avg_recalc(
				temps_avg[TEMP54XX_MPU],
				temps[TEMP54XX_MPU][sample], sample - 1);
			fprintf(fp, ", %d", temps[TEMP54XX_MPU][sample]);
		} else {
			fputs(", NA", fp);
		}

		/* Compute and save GPU sensor temperature */
		if (p_flags[GPU_TEMP]) {
			if (temps[TEMP54XX_GPU][sample] >
				temps_max[TEMP54XX_GPU])
				temps_max[TEMP54XX_GPU] =
					temps[TEMP54XX_GPU][sample];
			if (temps[TEMP54XX_GPU][sample] <
				temps_min[TEMP54XX_GPU])
				temps_min[TEMP54XX_GPU] =
					temps[TEMP54XX_GPU][sample];
			temps_avg[TEMP54XX_GPU] = avg_recalc(
				temps_avg[TEMP54XX_GPU],
				temps[TEMP54XX_GPU][sample], sample - 1);
			fprintf(fp, ", %d", temps[TEMP54XX_GPU][sample]);
		} else {
			fputs(", NA", fp);
		}

		/* Compute and save CORE sensor temperature */
		if (p_flags[CORE_TEMP]) {
			if (temps[TEMP54XX_CORE][sample] >
				temps_max[TEMP54XX_CORE])
				temps_max[TEMP54XX_CORE] =
					temps[TEMP54XX_CORE][sample];
			if (temps[TEMP54XX_CORE][sample] <
				temps_min[TEMP54XX_CORE])
				temps_min[TEMP54XX_CORE] =
					temps[TEMP54XX_CORE][sample];
			temps_avg[TEMP54XX_CORE] = avg_recalc(
				temps_avg[TEMP54XX_CORE],
				temps[TEMP54XX_CORE][sample], sample - 1);
			fprintf(fp, ", %d", temps[TEMP54XX_CORE][sample]);
		} else {
			fputs(", NA", fp);
		}

		/* Compute and save CASE sensor temperature */
		if (p_flags[CASE_TEMP]) {
			if (temps[TEMP54XX_CASE][sample] >
				temps_max[TEMP54XX_CASE])
				temps_max[TEMP54XX_CASE] =
					temps[TEMP54XX_CASE][sample];
			if (temps[TEMP54XX_CASE][sample] <
				temps_min[TEMP54XX_CASE])
				temps_min[TEMP54XX_CASE] =
					temps[TEMP54XX_CASE][sample];
			temps_avg[TEMP54XX_CASE] = avg_recalc(
				temps_avg[TEMP54XX_CASE],
				temps[TEMP54XX_CASE][sample], sample - 1);
			fprintf(fp, ", %d", temps[TEMP54XX_CASE][sample]);
		} else {
			fputs(", NA", fp);
		}

		/* Compute and save geninputs */
		for (i = 0; i < geninput_num; i++) {
			if (geninput_flags[i]) {
				/* Handle Accumulating Generic Inputs */
				if (geninput_accumulating[i]) {
					geninput_delta = count64_delta(
						geninput_data[i][sample-1],
						geninput_data[i][sample]);

					if (geninput_delta > geninput_max[i])
						geninput_max[i] =
							geninput_delta;
					if (geninput_delta < geninput_min[i])
						geninput_min[i] =
							geninput_delta;
					geninput_avg[i] = avg_recalc(
						geninput_avg[i],
						geninput_delta, sample - 1);
					sprintf(s, "%llu", geninput_delta);
					fprintf(fp, ", %s", s);
				}
				/* Handle Non-Accumulating Generic Inputs */
				else {
					if (geninput_data[i][sample] >
						geninput_max[i])
						geninput_max[i] =
							geninput_data[i][sample];
					if (geninput_data[i][sample] <
						geninput_min[i])
						geninput_min[i] =
							geninput_data[i][sample];
					geninput_avg[i] = avg_recalc(
						geninput_avg[i],
						geninput_data[i][sample],
						sample - 1);
					sprintf(s, "%llu",
						geninput_data[i][sample]);
					fprintf(fp, ", %s", s);
				}
			} else {
				fputs(", NA", fp);
			}
		}

		fprintf(fp, "\n");
		dprintf("\n");

	}
	fprintf(fp,
		"# ------------------------ Trace END ---------------------\n");
	fclose(fp);

	/* Save statistics */
	fp = workdir_fopen(trace_perf_stats_file, "w");
	if (fp == NULL) {
		fprintf(stderr, "%s(): could not create %s!\n",
			__func__, trace_perf_stats_file);
		ret = OMAPCONF_ERR_NOT_AVAILABLE;
		goto trace_perf_capture_err;
	}

	fprintf(fp, "Performance Statistics\n\n");
	if (!cpu_is_omap44xx() && !cpu_is_omap54xx())
		fprintf(fp, "CPU: UNKNOWN\n");
	else
		fprintf(fp, "CPU: %s\n", cpu_full_name_get(cpu_name));
	if (release_details_get(version, type, date) != NULL)
		fprintf(fp, "RELEASE: %s\n\n", version);
	else
		fprintf(fp, "RELEASE: UNKNOWN\n\n");
	fprintf(fp, "Trace Initial Delay: %ds\n", delay_time);
	fprintf(fp, "Trace Length: %us\n", capture_time);
	fprintf(fp, "Trace Sampling Rate: %lfs\n", sampling_rate);
	fprintf(fp, "Number of samples: %u\n", sample_cnt - 1);
	fprintf(fp, "\nNB:\n");
	fprintf(fp, "  * This is an intrusive trace (counters polling).\n");
	fprintf(fp, "    Idle C-States usage was altered.\n");
	fprintf(fp, "    Limited additional CPU & EMIFs loads generated.\n");
	fprintf(fp, "  * If CPU1 Load = -5.0, it means CPU1 is OFFLINE.\n");
	fprintf(fp, "  * CPU LOADS CANNOT be converted to Mhz.\n");
	fprintf(fp, "    OPP may have changed during the audit.\n");
	fprintf(fp,
		"  * EMIF Data Bus Load CANNOT be converted to memory bandwidth (MB/s).\n");
	fprintf(fp,
		"    DDR data busy cycles may be commands (not data) and data size is unknown.\n\n\n");

	autoadjust_table_init(table);
	row = 0;
	strncpy(table[row][0], "Performance Statistics", TABLE_MAX_ELT_LEN);
	strncpy(table[row][1], "Min", TABLE_MAX_ELT_LEN);
	strncpy(table[row][2], "Max", TABLE_MAX_ELT_LEN);
	strncpy(table[row][3], "Average", TABLE_MAX_ELT_LEN);
	strncpy(table[row][4], "Online Time", TABLE_MAX_ELT_LEN);
	row++;

	if (p_flags[CPU_FREQ]) {
		strncpy(table[row][0], "CPU Frequency", TABLE_MAX_ELT_LEN);
		if (cpu_freq_min < 0.0) {
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "N/A");
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "N/A");
		} else {
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%dMHz",
					cpu_freq_min);
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%dMHz",
					cpu_freq_max);
		}
		row++;
	}
	if (p_flags[MPU_TEMP]) {
		strncpy(table[row][0], "CPU Temperature", TABLE_MAX_ELT_LEN);
		if (temps_avg[TEMP54XX_MPU] != TEMP_ABSOLUTE_ZERO) {
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%dC",
				temps_min[TEMP54XX_MPU]);
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%dC",
				temps_max[TEMP54XX_MPU]);
			snprintf(table[row][3], TABLE_MAX_ELT_LEN, "%.2lfC",
				temps_avg[TEMP54XX_MPU]);
		} else {
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "NA");
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "NA");
			snprintf(table[row][3], TABLE_MAX_ELT_LEN, "NA");
		}
		row++;
	}
	for (cpu = 0; cpu <= 2; cpu++) {
		if ((cpu == 0 && p_flags[CPU0_LOAD]) ||
			(cpu == 1 && p_flags[CPU1_LOAD]) ||
			(cpu == 2 && p_flags[TOTAL_CPU_LOAD])) {
			if (cpu != 2)
				snprintf(table[row][0], TABLE_MAX_ELT_LEN,
					"CPU%u Load", cpu);
			else
				strncpy(table[row][0], "Total CPU Load",
					TABLE_MAX_ELT_LEN);
			if ((cpu == 1) && (cpu1_online_cnt == 0))
				strncpy(table[row][1], "0.00%%",
					TABLE_MAX_ELT_LEN);
			else
				snprintf(table[row][1], TABLE_MAX_ELT_LEN,
					"%.2lf%%", cpu_load_min[cpu]);
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%.2lf%%",
				cpu_load_max[cpu]);
			snprintf(table[row][3], TABLE_MAX_ELT_LEN, "%.2lf%%",
				cpu_load_avg[cpu]);
			row++;
		}

		if (cpu == 1 && p_flags[CPU1_ONLINE_TIME]) {
			strncpy(table[row][0], "CPU1 Online Time",
				TABLE_MAX_ELT_LEN);
			snprintf(table[row][4], TABLE_MAX_ELT_LEN, "%.2lf%%",
				100.0 * ((double) cpu1_online_cnt /
					((double) sample_cnt - 1)));
			row++;
		}

	}
	for (i = GPU_FREQ; i < NUM_ITEMS; i++) {
		if ((p_flags[i] == 1) && (i != MPU_TEMP)) {
			row++;
			break;
		}
	}

	if (p_flags[GPU_FREQ]) {
		strncpy(table[row][0], "GPU Frequency", TABLE_MAX_ELT_LEN);
		if (gpu_freq_min < 0) {
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "N/A");
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "N/A");
		} else {
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%dMHz",
					gpu_freq_min);
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%dMHz",
					gpu_freq_max);
		}
		row++;
	}
	if (p_flags[GPU_TEMP]) {
		strncpy(table[row][0], "GPU Temperature", TABLE_MAX_ELT_LEN);
		if (temps_avg[TEMP54XX_GPU] != TEMP_ABSOLUTE_ZERO) {
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%dC",
				temps_min[TEMP54XX_GPU]);
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%dC",
				temps_max[TEMP54XX_GPU]);
			snprintf(table[row][3], TABLE_MAX_ELT_LEN, "%.2lfC",
				temps_avg[TEMP54XX_GPU]);
		} else {
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "NA");
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "NA");
			snprintf(table[row][3], TABLE_MAX_ELT_LEN, "NA");
		}
		row++;
	}
	if ((p_flags[GPU_FREQ]) || (p_flags[GPU_TEMP]))
		row++;

	if (p_flags[L3_FREQ]) {
		strncpy(table[row][0], "L3 Frequency", TABLE_MAX_ELT_LEN);
		if (l3_freq_min < 0) {
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "N/A");
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "N/A");
		} else {
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%dMHz",
					l3_freq_min);
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%dMHz",
					l3_freq_max);
		}
		row++;
	}
	if (p_flags[CORE_TEMP]) {
		strncpy(table[row][0], "L3 Temperature", TABLE_MAX_ELT_LEN);
		if (temps_avg[TEMP54XX_CORE] != TEMP_ABSOLUTE_ZERO) {
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%dC",
				temps_min[TEMP54XX_CORE]);
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%dC",
				temps_max[TEMP54XX_CORE]);
			snprintf(table[row][3], TABLE_MAX_ELT_LEN, "%.2lfC",
				temps_avg[TEMP54XX_CORE]);
		} else {
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "NA");
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "NA");
			snprintf(table[row][3], TABLE_MAX_ELT_LEN, "NA");
		}
		row++;
	}
	if (p_flags[EMIF_LOAD]) {
		strncpy(table[row][0], "Total EMIF Data Bus Load",
			TABLE_MAX_ELT_LEN);
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%.2lf%%",
			emif_load_min);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%.2lf%%",
			emif_load_max);
		snprintf(table[row][3], TABLE_MAX_ELT_LEN, "%.2lf%%",
			emif_load_avg);
		row++;
	}
	if (p_flags[EMIF_BW]) {
		strncpy(table[row][0], "Total EMIF Bandwidth (WRITE)",
			TABLE_MAX_ELT_LEN);
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%.2lf MB/s",
			emif_bw_min[0]);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%.2lf MB/s",
			emif_bw_max[0]);
		snprintf(table[row][3], TABLE_MAX_ELT_LEN, "%.2lf MB/s",
			emif_bw_avg[0]);
		row++;
		strncpy(table[row][0], "Total EMIF Bandwidth (READ)",
			TABLE_MAX_ELT_LEN);
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%.2lf MB/s",
			emif_bw_min[1]);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%.2lf MB/s",
			emif_bw_max[1]);
		snprintf(table[row][3], TABLE_MAX_ELT_LEN, "%.2lf MB/s",
			emif_bw_avg[1]);
		row++;
	}

	if ((p_flags[L3_FREQ]) || (p_flags[CORE_TEMP]) || (p_flags[EMIF_LOAD]) ||
		(p_flags[EMIF_BW]))
		row++;

	if (p_flags[BANDGAP_TEMP]) {
		strncpy(table[row][0], "Bandgap Temperature",
			TABLE_MAX_ELT_LEN);
		if (bandgap_temp_avg != TEMP_ABSOLUTE_ZERO) {
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%dC",
				bandgap_temp_min);
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%dC",
				bandgap_temp_max);
			snprintf(table[row][3], TABLE_MAX_ELT_LEN, "%.2lfC",
				bandgap_temp_avg);
		} else {
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "NA");
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "NA");
			snprintf(table[row][3], TABLE_MAX_ELT_LEN, "NA");
		}
		row++;
	}
	if (p_flags[HOTSPOT_MPU_TEMP]) {
		strncpy(table[row][0], "MPU HOTSPOT Temperature",
			TABLE_MAX_ELT_LEN);
		if (hotspot_mpu_temp_avg != TEMP_ABSOLUTE_ZERO) {
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%dC",
				hotspot_mpu_temp_min);
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%dC",
				hotspot_mpu_temp_max);
			snprintf(table[row][3], TABLE_MAX_ELT_LEN, "%.2lfC",
				hotspot_mpu_temp_avg);
		} else {
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "NA");
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "NA");
			snprintf(table[row][3], TABLE_MAX_ELT_LEN, "NA");
		}
		row++;
	}
	if (p_flags[PCB_TEMP]) {
		strncpy(table[row][0], "PCB Temperature", TABLE_MAX_ELT_LEN);
		if (pcb_temp_avg != TEMP_ABSOLUTE_ZERO) {
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%dC",
				pcb_temp_min);
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%dC",
				pcb_temp_max);
			snprintf(table[row][3], TABLE_MAX_ELT_LEN, "%.2lfC",
				pcb_temp_avg);
		} else {
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "NA");
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "NA");
			snprintf(table[row][3], TABLE_MAX_ELT_LEN, "NA");
		}
		row++;
	}
	if (p_flags[CASE_TEMP]) {
		strncpy(table[row][0], "CASE Temperature", TABLE_MAX_ELT_LEN);
		if (temps_avg[TEMP54XX_CASE] != TEMP_ABSOLUTE_ZERO) {
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%dC",
				temps_min[TEMP54XX_CASE]);
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%dC",
				temps_max[TEMP54XX_CASE]);
			snprintf(table[row][3], TABLE_MAX_ELT_LEN, "%.2lfC",
				temps_avg[TEMP54XX_CASE]);
		} else {
			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "NA");
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "NA");
			snprintf(table[row][3], TABLE_MAX_ELT_LEN, "NA");
		}
		row++;
	}

	for (i = 0; i < geninput_num; i++) {
		if (geninput_flags[i]) {
			row++;
			strncpy(table[row][0], "*Generic Input Files*",
				TABLE_MAX_ELT_LEN);
			row++;
			break;
		}
	}

	for (i = 0; i < geninput_num; i++) {
		if (geninput_flags[i]) {
			strncpy(table[row][0], geninput_names[i],
				TABLE_MAX_ELT_LEN);

			snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%llu%s",
				geninput_min[i], geninput_units[i]);
			snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%llu%s",
				geninput_max[i], geninput_units[i]);
			snprintf(table[row][3], TABLE_MAX_ELT_LEN, "%.2f%s",
				geninput_avg[i], geninput_units[i]);

			row++;
		}
	}

	if (p_flags[CPU1_ONLINE_TIME])
		autoadjust_table_fprint(fp, table, row, 5);
	else
		autoadjust_table_fprint(fp, table, row, 4);
	fclose(fp);

	printf("Generating GNUPlot script files...\n");
	/* Compute charts height, depending on traced items */
	chart_count = 0;
	if (p_flags[CPU0_LOAD] || p_flags[CPU1_LOAD] || p_flags[TOTAL_CPU_LOAD]
		|| p_flags[EMIF_LOAD] || p_flags[EMIF_BW])
		chart_count++;
	if (p_flags[CPU_FREQ] || p_flags[GPU_FREQ] || p_flags[L3_FREQ])
		chart_count++;
	if (p_flags[BANDGAP_TEMP] || p_flags[PCB_TEMP] ||
		p_flags[HOTSPOT_MPU_TEMP] || MPU_TEMP || GPU_TEMP ||
		CORE_TEMP || CASE_TEMP)
		chart_count++;
	for (i = 0; i < geninput_num; i++) {
		if (geninput_flags[i]) {
			chart_count++;
			break;
		}
	}
	if (chart_count != 0)
		height = 1.0 / chart_count;
	else
		height = 1.0;
	dprintf("%s(): chart_count=%d height=%.2lf\n", __func__,
		chart_count, height);

	for (file = 0; file < 2; file++) {
		if (file == 0)
			fp = workdir_fopen(
				trace_perf_charts_script_file, "w");
		else
			fp = workdir_fopen(trace_perf_jpg_script_file, "w");

		if (fp == NULL) {
			fprintf(stderr, "%s(): could not create script file!\n",
				__func__);
			ret = OMAPCONF_ERR_NOT_AVAILABLE;
			goto trace_perf_capture_err;
		}

		fprintf(fp,
			"# Performance Trace GNUPlot Script File\n");
		fprintf(fp, "#\n");
		fprintf(fp, "set xlabel \"Time (s)\"\n");
		fprintf(fp, "set style line 1 lt 2 lc rgb \"red\" lw 2\n");
		fprintf(fp, "set style line 2 lt 2 lc rgb \"blue\" lw 2\n");
		fprintf(fp, "set style line 3 lt 2 lc rgb \"#228B22\" lw 2\n");
		fprintf(fp, "set style line 4 lt 2 lc rgb \"gold\" lw 2\n");
		fprintf(fp, "set style line 5 lt 2 lc rgb \"#FF1493\" lw 2\n");
		fprintf(fp,
			"set style line 6 lt 2 lc rgb \"#FF8C00\" lw 2\n");
		fprintf(fp,
			"set style line 7 lt 2 lc rgb \"#FF69B4\" lw 2\n");
		fprintf(fp, "set mxtics\n");
		fprintf(fp, "set mytics\n");
		fprintf(fp, "set grid ytics xtics mxtics\n");
		fprintf(fp, "\n");
		if (file == 0) {
			fprintf(fp, "set terminal wxt size 1133,850\n");
		} else {
			fprintf(fp, "set terminal jpeg size 1280,960\n");
			fprintf(fp, "set output \"%s\"\n",
				trace_perf_jpg_file);
		}
		fprintf(fp, "set multiplot\n");
		fprintf(fp, "\n");

		chart_count = 0;
		if (p_flags[CPU_FREQ] || p_flags[GPU_FREQ] ||
			p_flags[L3_FREQ]) {
			/* Plot CPU, GPU & L3 Speeds over Time */
			fprintf(fp, "set size 1.0,%.2lf\n", height);
			fprintf(fp, "set origin 0,%.2lf\n",
				chart_count * height);
			fprintf(fp, "set title 'Clock Speed(s) over Time'\n");
			fprintf(fp, "set ylabel \"Speed (MHz)\"\n");
			if (p_flags[CPU_FREQ]) {
				if (p_flags[GPU_FREQ] || p_flags[L3_FREQ])
					fprintf(fp,
						"plot '%s' using 1:%d ls 1 title 'CPU' with steps,\\\n",
						trace_perf_file, CPU_FREQ + 1);
				else
					fprintf(fp,
						"plot '%s' using 1:%d ls 1 title 'CPU' with steps;\n",
						trace_perf_file, CPU_FREQ + 1);
			}
			if (p_flags[GPU_FREQ]) {
				if (p_flags[CPU_FREQ])
					fprintf(fp, "     ");
				else
					fprintf(fp, "plot ");
				if (p_flags[L3_FREQ])
					fprintf(fp,
						"'%s' using 1:%d ls 2 title 'GPU' with steps,\\\n",
						trace_perf_file, GPU_FREQ + 1);
				else
					fprintf(fp,
						"'%s' using 1:%d ls 2 title 'GPU' with steps;\n",
						trace_perf_file, GPU_FREQ + 1);
			}
			if (p_flags[L3_FREQ]) {
				if ((p_flags[CPU_FREQ]) || (p_flags[GPU_FREQ]))
					fprintf(fp, "     ");
				else
					fprintf(fp, "plot ");
				fprintf(fp,
					"'%s' using 1:%d ls 7 title 'L3' with steps;\n",
					trace_perf_file, L3_FREQ + 1);
			}
			fprintf(fp, "\n");
			chart_count++;
		}

		if (p_flags[CPU0_LOAD] || p_flags[CPU1_LOAD] ||
			p_flags[TOTAL_CPU_LOAD] || p_flags[EMIF_LOAD] ||
			p_flags[EMIF_BW]) {
			/* Plot EMIF, CPU, CPU0, CPU1 Loads over Time */
			fprintf(fp, "set size 1.0,%.2lf\n", height);
			fprintf(fp, "set origin 0,%.2lf\n",
				chart_count * height);
			fprintf(fp, "set title 'EMIF/CPU Load(s) over Time'\n");
			fprintf(fp, "set ylabel \"Load (%%)\"\n");

			if (p_flags[EMIF_BW]) {
				if (p_flags[CPU0_LOAD] || p_flags[CPU1_LOAD] ||
					p_flags[TOTAL_CPU_LOAD]) {
					fprintf(fp,
						"plot '%s' using 1:%d ls 5 notitle with lines,\\\n",
						trace_perf_file, EMIF_BW  + 1);
					fprintf(fp,
						"     '%s' using 1:%d ls 7 notitle with lines,\\\n",
						trace_perf_file, EMIF_BW  + 2);
				} else {
					fprintf(fp,
						"plot '%s' using 1:%d ls 5 notitle with lines,\\\n",
						trace_perf_file, EMIF_BW + 1);
					fprintf(fp,
						"     '%s' using 1:%d ls 7 notitle with lines;\n",
						trace_perf_file, EMIF_BW + 2);
				}
			} else if (p_flags[EMIF_LOAD]) {
				if (p_flags[CPU0_LOAD] || p_flags[CPU1_LOAD] ||
					p_flags[TOTAL_CPU_LOAD])
					fprintf(fp,
						"plot '%s' using 1:%d ls 7 notitle with lines,\\\n",
						trace_perf_file, EMIF_LOAD + 3);
				else
					fprintf(fp,
						"plot '%s' using 1:%d ls 7 notitle with lines;\n",
						trace_perf_file, EMIF_LOAD + 3);
			}

			if (p_flags[TOTAL_CPU_LOAD]) {
				if (p_flags[EMIF_LOAD] || p_flags[EMIF_BW])
					fprintf(fp, "     ");
				else
					fprintf(fp, "plot ");
				if (p_flags[CPU0_LOAD] || p_flags[CPU1_LOAD])
					fprintf(fp,
						"'%s' using 1:%d ls 1 title 'Total' with lines,\\\n",
						trace_perf_file,
						TOTAL_CPU_LOAD + 2);
				else
					fprintf(fp,
						"'%s' using 1:%d ls 1 title 'Total' with lines;\n",
						trace_perf_file,
						TOTAL_CPU_LOAD + 2);
			}
			if (p_flags[CPU0_LOAD]) {
				if (p_flags[TOTAL_CPU_LOAD])
					fprintf(fp, "     ");
				else
					fprintf(fp, "plot ");
				if (p_flags[CPU1_LOAD])
					fprintf(fp,
						"'%s' using 1:%d ls 4 title 'CPU0' with lines,\\\n",
						trace_perf_file, CPU0_LOAD + 2);
				else
					fprintf(fp,
						"'%s' using 1:%d ls 4 title 'CPU0' with lines;\n",
						trace_perf_file, CPU0_LOAD + 2);
			}
			if (p_flags[CPU1_LOAD]) {
				if (p_flags[TOTAL_CPU_LOAD] ||
					p_flags[CPU0_LOAD])
					fprintf(fp, "     ");
				else
					fprintf(fp, "plot ");
				fprintf(fp,
					"'%s' using 1:%d ls 6 title 'CPU1' with lines;\n",
					trace_perf_file, CPU1_LOAD + 2);
			}
			fprintf(fp, "\n");
			chart_count++;
		}

		if (p_flags[BANDGAP_TEMP] || p_flags[PCB_TEMP] ||
			p_flags[MPU_TEMP] || p_flags[GPU_TEMP] ||
			p_flags[CORE_TEMP] || p_flags[CASE_TEMP] ||
			p_flags[HOTSPOT_MPU_TEMP]) {
			/* Plot temperatures over time */
			fprintf(fp, "set size 1.0,%.2lf\n", height);
			fprintf(fp, "set origin 0,%.2lf\n",
				chart_count * height);
			fprintf(fp, "set title 'Temperature(s) over Time'\n");
			fprintf(fp, "set ylabel \"Temperature (C)\"\n");
			if (p_flags[BANDGAP_TEMP]) {
				if (p_flags[PCB_TEMP]
					|| p_flags[MPU_TEMP] ||
					p_flags[GPU_TEMP] ||
					p_flags[CORE_TEMP] ||
					p_flags[CASE_TEMP] ||
					p_flags[HOTSPOT_MPU_TEMP])
					fprintf(fp,
						"plot '%s' using 1:%d ls 7 title 'Bandgap' with lines,\\\n",
						trace_perf_file,
						BANDGAP_TEMP + 2);
				else
					fprintf(fp,
						"plot '%s' using 1:%d ls 7 title 'Bandgap' with lines;\n",
						trace_perf_file,
						BANDGAP_TEMP + 2);
			}

			if (p_flags[PCB_TEMP]) {
				if (p_flags[BANDGAP_TEMP])
					fprintf(fp, "     ");
				else
					fprintf(fp, "plot ");
				if (p_flags[MPU_TEMP] || p_flags[GPU_TEMP] ||
					p_flags[CORE_TEMP] ||
					p_flags[CASE_TEMP] ||
					p_flags[HOTSPOT_MPU_TEMP])
					fprintf(fp,
						"     '%s' using 1:%d ls 3 title 'PCB' with lines,\\\n",
						trace_perf_file, PCB_TEMP + 2);
				else
					fprintf(fp,
						"     '%s' using 1:%d ls 3 title 'PCB' with lines;\n",
						trace_perf_file, PCB_TEMP + 2);
			}

			if (p_flags[MPU_TEMP]) {
				if (p_flags[BANDGAP_TEMP] || p_flags[PCB_TEMP])
					fprintf(fp, "     ");
				else
					fprintf(fp, "plot ");
				if (p_flags[GPU_TEMP] || p_flags[CORE_TEMP] ||
					p_flags[CASE_TEMP] ||
					p_flags[HOTSPOT_MPU_TEMP])
					fprintf(fp,
						"     '%s' using 1:%d ls 1 title 'MPU' with lines,\\\n",
						trace_perf_file, MPU_TEMP + 2);
				else
					fprintf(fp,
						"     '%s' using 1:%d ls 1 title 'MPU' with lines;\n",
						trace_perf_file, MPU_TEMP + 2);
			}

			if (p_flags[GPU_TEMP]) {
				if (p_flags[BANDGAP_TEMP] ||
					p_flags[PCB_TEMP] ||
					p_flags[MPU_TEMP])
					fprintf(fp, "     ");
				else
					fprintf(fp, "plot ");
				if (p_flags[CORE_TEMP] || p_flags[CASE_TEMP] ||
					p_flags[HOTSPOT_MPU_TEMP])
					fprintf(fp,
						"     '%s' using 1:%d ls 2 title 'GPU' with lines,\\\n",
						trace_perf_file, GPU_TEMP + 2);
				else
					fprintf(fp,
						"     '%s' using 1:%d ls 2 title 'GPU' with lines;\n",
						trace_perf_file, GPU_TEMP + 2);
			}

			if (p_flags[CORE_TEMP]) {
				if (p_flags[BANDGAP_TEMP] ||
					p_flags[PCB_TEMP] ||
					p_flags[MPU_TEMP] ||
					p_flags[GPU_TEMP])
					fprintf(fp, "     ");
				else
					fprintf(fp, "plot ");
				if (p_flags[CASE_TEMP] || p_flags[HOTSPOT_MPU_TEMP])
					fprintf(fp,
						"     '%s' using 1:%d ls 7 title 'CORE' with lines,\\\n",
						trace_perf_file, CORE_TEMP + 2);
				else
					fprintf(fp,
						"     '%s' using 1:%d ls 7 title 'CORE' with lines;\n",
						trace_perf_file, CORE_TEMP + 2);
			}

			if (p_flags[CASE_TEMP]) {
				if (p_flags[BANDGAP_TEMP] ||
					p_flags[PCB_TEMP] ||
					p_flags[MPU_TEMP] ||
					p_flags[GPU_TEMP] ||
					p_flags[CORE_TEMP])
					fprintf(fp, "     ");
				else
					fprintf(fp, "plot ");
				if (p_flags[HOTSPOT_MPU_TEMP])
					fprintf(fp,
						"     '%s' using 1:%d ls 5 title 'CASE' with lines,\\\n",
						trace_perf_file, CASE_TEMP + 2);
				else
					fprintf(fp,
						"     '%s' using 1:%d ls 5 title 'CASE' with lines;\n",
						trace_perf_file, CASE_TEMP + 2);
			}

			if (p_flags[HOTSPOT_MPU_TEMP]) {
				if (p_flags[BANDGAP_TEMP] ||
					p_flags[PCB_TEMP] ||
					p_flags[MPU_TEMP] ||
					p_flags[GPU_TEMP] ||
					p_flags[CORE_TEMP] ||
					p_flags[CASE_TEMP])
					fprintf(fp, "     ");
				else
					fprintf(fp, "plot ");
				fprintf(fp,
					"     '%s' using 1:%d ls 1 title 'MPU HotSpot' with lines;\n",
					trace_perf_file, HOTSPOT_MPU_TEMP + 2);
			}
			fprintf(fp, "\n");
			chart_count++;
		}

		if (geninput_num > 0) {
			/* Plot Generic Input File(s) over Time */
			fprintf(fp, "set size 1.0,%.2lf\n", height);
			fprintf(fp, "set origin 0,%.2lf\n",
				chart_count * height);
			fprintf(fp,
				"set title 'Generic Input File(s) over Time'\n");
			fprintf(fp, "set ylabel \"\"\n");
			/* Find first and last input traced */
			for (i = 0; i < geninput_num; i++) {
				if (geninput_flags[i] == 1) {
					geninput_first = i;
					break;
				}

			}
			for (i = geninput_num - 1; i >= 0; i--) {
				if (geninput_flags[i] == 1) {
					geninput_last = i;
					break;
				}

			}
			dprintf("%s(): geninput_first=%d, geninput_last=%d\n",
				__func__, geninput_first, geninput_last);

			for (i = 0; i < geninput_num; i++) {
				if (geninput_flags[i] == 0)
					continue;
				/*
				 * FIXME: define more line styles and
				 * select 1 per generic input.
				 */
				if (i == geninput_first)
					fprintf(fp, "plot ");
				else
					fprintf(fp, "     ");
				fprintf(fp,
					"'%s' using 1:%d ls %d title '%s' with lines",
					trace_perf_file,
					1 + NUM_ITEMS + i,
					1 + (i % 7),
					geninput_names[i]);
				if (i == geninput_last)
					fprintf(fp, ";\n");
				else
					fprintf(fp, ",\\\n");
			}
			fprintf(fp, "\n");
		}

		fprintf(fp, "unset multiplot\n");
		if (file == 0)
			fprintf(fp, "set terminal wxt size 1133,850\n");
		else
			fprintf(fp, "print \"'%s' JPEG file created.\"\n",
				trace_perf_jpg_file);
		fclose(fp);
	}

	printf("done.\n\n");

	if (p_flags[CPU1_ONLINE_TIME])
		autoadjust_table_print(table, row, 5);
	else
		autoadjust_table_print(table, row, 4);
	printf("Performance trace saved into '%s' file.\n",
		trace_perf_file);
	printf("Performance statistics saved into '%s' file.\n\n",
		trace_perf_stats_file);

	printf("Use:\n");
	printf("  gnuplot -persist '%s' to display performance charts.\n",
		trace_perf_charts_script_file);
	printf(
		"  gnuplot '%s' to save performance charts into '%s' JPEG image file.\n\n",
		trace_perf_jpg_script_file, trace_perf_jpg_file);
	ret = 0;

trace_perf_capture_err:
	/* Free allocated buffers */
	for (cpu = 0; cpu < 2; cpu++) {
		if (idle[cpu] != NULL)
			free(idle[cpu]);
		if (iowait[cpu] != NULL)
			free(iowait[cpu]);
		if (sum[cpu] != NULL)
			free(sum[cpu]);
	}
	if (cpu1_online != NULL)
		free(cpu1_online);
	if (cpu_freq != NULL)
		free(cpu_freq);
	if (gpu_freq != NULL)
		free(gpu_freq);
	if (emif_busy_cycles != NULL)
		free(emif_busy_cycles);
	if (emif_cycles != NULL)
		free(emif_cycles);
	if (p_flags[EMIF_BW])
		trace_bw_deinit();
	if (l3_freq != NULL)
		free(l3_freq);
	if (bandgap_temp != NULL)
		free(bandgap_temp);
	if (pcb_temp != NULL)
		free(pcb_temp);
	if (hotspot_mpu_temp != NULL)
		free(hotspot_mpu_temp);
	for (i = 0; i < (int) TEMP54XX_ID_MAX; i++) {
		if (temps[i] != NULL)
			free(temps[i]);
	}
	for (i = 0; i < geninput_num; i++) {
		if (geninput_data[i] != NULL)
			free(geninput_data[i]);
	}

	return ret;
}
