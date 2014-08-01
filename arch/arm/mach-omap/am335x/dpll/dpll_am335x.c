/*
 *
 * @Component			OMAPCONF
 * @Filename			dpll_am335x.c
 * @Description			AM335X DPLL Definitions & Functions
 * @Author			Gilberto Rodriguez <gilrod@ti.com>
 * @Date			2014
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
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
#include <cm_am335x-defs.h>
#include <cpuinfo.h>
#include <dpll_am335x.h>
#include <dpll_am335x-data.h>
#include <help.h>
#include <lib.h>
#include <opp.h>
#include <stdio.h>
#include <string.h>
#include <voltdomain.h>


#ifdef DPLL_AM335X_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


dpll_am335x_settings *dpll_am335x_settings_table[DPLL_AM335X_ID_MAX] = {
	NULL, NULL, NULL, NULL, NULL};


dpll_am335x_settings *dpll_am335x_locked_settings_table[DPLL_AM335X_ID_MAX] = {
	NULL, NULL, NULL, NULL, NULL};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		am335x_print_reg
 * @BRIEF		Show register name, addr & content
 * @RETURNS		None
 * @param[in]		r: register. row: pointer to the row number
 * @DESCRIPTION		Show register name, addr & content
 *//*------------------------------------------------------------------------ */
void am335x_print_reg(char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN],
		reg *r, unsigned int *row)
{
	unsigned int val;
	if (r == NULL)
		return;
	val = reg_read(r);
	/* Show register name, addr & content */
	snprintf(table[*row][0], TABLE_MAX_ELT_LEN, "%s", r->name);
	snprintf(table[*row][1], TABLE_MAX_ELT_LEN, "0x%08X", r->addr);
	snprintf(table[*row][2], TABLE_MAX_ELT_LEN, "0x%08X", val);
	(*row)++;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_am335x_s2id
 * @BRIEF		convert string to valid DPLL ID
 * @RETURNS		DPLL_AM335X_PER if s == "per"
 *			DPLL_AM335X_CORE if s == "core"
 *			DPLL_AM335X_MPU if s == "mpu"
 *			DPLL_AM335X_DDR if s == "ddr"
 *			DPLL_AM335X_DISP if s == "disp"
 *			DPLL_AM335X_ID_MAX otherwise
 * @param[in,out]	s: string
 * @DESCRIPTION		convert string to valid DPLL ID
 *//*------------------------------------------------------------------------ */
dpll_am335x_id dpll_am335x_s2id(char *s)
{
	int index;
	CHECK_NULL_ARG(s, DPLL_AM335X_ID_MAX);

	for (index = 0; index < DPLL_AM335X_ID_MAX; index++)
		if (strcmp(s, dpll_am335x_strings[index]) == 0)
			return (dpll_am335x_id) index;
	return DPLL_AM335X_ID_MAX;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_am335x_name_get
 * @BRIEF		return DPLL name
 * @RETURNS		DPLL name
 *			NULL in case of incorrect id
 * @param[in]		id: DPLL ID
 * @DESCRIPTION		return DPLL name
 *//*------------------------------------------------------------------------ */
const char *dpll_am335x_name_get(dpll_am335x_id id)
{
	CHECK_ARG_LESS_THAN(id, DPLL_AM335X_ID_MAX, NULL);

	return dpll_am335x_names[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		hsdiv_am335x_name_get
 * @BRIEF		return HS divider name
 * @RETURNS		HS divider name
 *			NULL in case of incorrect id
 * @param[in]		id: HS divider ID
 * @DESCRIPTION		return HS divider name
 *//*------------------------------------------------------------------------ */
const char *hsdiv_am335x_name_get(hsdiv_am335x_id id)
{
	CHECK_ARG_LESS_THAN(id, HSDIV_AM335X_ID_MAX, NULL);

	return hsdiv_am335x_names[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_am335x_dump
 * @BRIEF		dump selected DPLL registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in, out]	stream: output stream
 * @param[in]		id: DPLL ID
 *			If id == DPLL_AM335X_ID_MAX, dump all DPLL registers.
 * @DESCRIPTION		dump selected DPLL registers and pretty-print it to
 *			output stream.
 *//*------------------------------------------------------------------------ */
int dpll_am335x_dump(FILE *stream, dpll_am335x_id id)
{
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row, i;
	dpll_settings_regs dpll_regs;
	dpll_am335x_id dpll_id;
	reg *r;

	CHECK_ARG_LESS_THAN(id, DPLL_AM335X_ID_MAX + 1, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(stream, OMAPCONF_ERR_ARG);

	for (dpll_id = DPLL_AM335X_PER; dpll_id < DPLL_AM335X_ID_MAX; dpll_id++) {
		if ((id != DPLL_AM335X_ID_MAX) && (dpll_id != id))
			continue;
		else {
			autoadjust_table_init(table);
			row = 0;
			snprintf(table[row][0], TABLE_MAX_ELT_LEN,
				"%s Reg. Name",	dpll_am335x_name_get(dpll_id));
			strncpy(table[row][1], "Reg. Address",
				TABLE_MAX_ELT_LEN);
			strncpy(table[row][2], "Reg. Value", TABLE_MAX_ELT_LEN);
			row++;

			dpll_regs = dpll_am335x_regs[dpll_id];
			for (i = 0; i < 10; i++) {
				switch (i) {
				case 0:
					r = dpll_regs.cm_clkmode_dpll;
					break;
				case 1:
					r = dpll_regs.cm_idlest_dpll;
					break;
				case 2:
					r = dpll_regs.cm_autoidle_dpll;
					break;
				case 3:
					r = dpll_regs.cm_clksel_dpll;
					break;
				case 4:
					r = dpll_regs.cm_bypclk_dpll;
					break;
				case 5:
					r = dpll_regs.cm_div_m2_dpll;
					break;
				case 6:
					r = dpll_regs.cm_div_m3_dpll;
					break;
				case 7:
					r = dpll_regs.cm_ssc_deltamstep_dpll;
					break;
				case 8:
					r = dpll_regs.cm_ssc_modfreqdiv_dpll;
					break;
				case 9:
					r = dpll_regs.cm_clkdcoldo_dpll;
					break;
				default:
					fprintf(stderr,
						"%s(): i=%u should not be "
						"reachable?!\n", __func__, i);
				}
				am335x_print_reg(table, r, &row);
			}

			for (i = HSDIV_AM335X_M4; i < HSDIV_AM335X_ID_MAX; i++) {
				r = (reg *) dpll_am335x_hsdiv_regs[dpll_id][i];
				am335x_print_reg(table, r, &row);
			}

			autoadjust_table_print(table, row, 3);
		}
	}
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_am335x_main
 * @BRIEF		main entry point for DPLL functions
 *
 *			### DEPRECATED, DO NOT USE ANYMORE ###
 *
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		main entry point for DPLL functions
 *			argv[0] = function ("dump", "cfg")
 *			argv[1] = DPLL ID ("mpu", "per", "core", "ddr", "disp")
 *				argv[1] may be omitted (then "all" assumed)
 *//*------------------------------------------------------------------------ */
int dpll_am335x_main(int argc, char *argv[])
{
	int ret = 0;
	dpll_am335x_id id;

	if (argc == 1) {
		id = DPLL_AM335X_ID_MAX;
	} else if (argc != 2) {
		goto dpll_am335x_main_err_arg;
	} else if (strcmp(argv[1], "all") == 0) {
		id = DPLL_AM335X_ID_MAX;
	} else {
		id = dpll_am335x_s2id(argv[1]);
		if (id == DPLL_AM335X_ID_MAX)
			goto dpll_am335x_main_err_arg;
	}

	if (strcmp(argv[0], "dump") == 0)
		ret = dpll_am335x_dump(stdout, id);
	else
		goto dpll_am335x_main_err_arg;
	goto dpll_am335x_main_end;

dpll_am335x_main_err_arg:
	help(HELP_DPLL);
	ret = OMAPCONF_ERR_ARG;

dpll_am335x_main_end:
	return ret;
}
