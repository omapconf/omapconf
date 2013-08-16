/*
 *
 * @Component			OMAPCONF
 * @Filename			cm_dra7xx.c
 * @Description			DRA7 CM Registers Functions
 * @Author			Jin Zheng (j-zheng@ti.com)
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


#include <cm_dra7xx.h>
#include <lib.h>
#include <autoadjust_table.h>
#include <module.h>
#include <prcm-module.h>
#include <cpuinfo.h>


/* #define CM_DRA7XX_DEBUG */
#ifdef CM_DRA7XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cm_dra7xx_mod_name_get
 * @BRIEF		return CM module name
 * @RETURNS		CM module name
 *			NULL in case of incorrect id
 * @param[in]		id: CM module ID
 * @DESCRIPTION		return CM module name
 *//*------------------------------------------------------------------------ */
const char *cm_dra7xx_mod_name_get(cm_dra7xx_mod_id id)
{
	if (id >= CM_DRA7XX_MODS_COUNT) {
		fprintf(stderr, "%s(): id (%u) >= CM_DRA7XX_MODS_COUNT (%u)!\n",
			__func__, id, CM_DRA7XX_MODS_COUNT);
		return NULL;
	}

	return cm_dra7xx_mods_name[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cm_dra7xx_is_profiling_running
 * @BRIEF		return 1 if profiling module (CMI) is running,
 *			0 otherwise
 * @RETURNS		1 if profiling module (CMI) is running, 0 otherwise
 * @param[in]		id: instrumentation ID
 *			(CM_DRA7XX_INSTR_CM_CORE or CM_DRA7XX_INSTR_CM_CORE_AON)
 * @DESCRIPTION		return 1 if profiling module (CMI) is running,
 *			0 otherwise
 *//*------------------------------------------------------------------------ */
unsigned int cm_dra7xx_is_profiling_running(cm_dra7xx_mod_id id)
{
	reg *cm_clkctrl_reg;
	unsigned int cm_clkctrl;

	if (id == CM_DRA7XX_INSTR_CM_CORE_AON) {
		cm_clkctrl_reg =
			&dra7xx_ocp_socket_cm_core_aon_cm_cm_core_aon_profiling_clkctrl;
	} else {
		fprintf(stderr,
			"%s(): called with incorrect ID (%s)!!!\n",
			__func__, cm_dra7xx_mod_name_get(id));
		return 0;
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
 * @FUNCTION		cm_dra7xx_dump
 * @BRIEF		dump selected registers and pretty-print it in
 *			selected output stream
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output stream
 * @param[in]		id: CM module ID - If id == CM_DRA7XX_MODS_COUNT,
 *			dump all CM registers.
 * @DESCRIPTION		dump selected registers and pretty-print it in
 *			selected output stream
 *//*------------------------------------------------------------------------ */
int cm_dra7xx_dump(FILE *stream, cm_dra7xx_mod_id id)
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
		goto cm_dra7xx_dump_end;
	}

	if (id > CM_DRA7XX_MODS_COUNT) {
		fprintf(stderr, "%s(): id (%u) > CM_DRA7XX_MODS_COUNT!!! (%u)\n",
			__func__, id, CM_DRA7XX_MODS_COUNT);
		err = OMAPCONF_ERR_ARG;
		goto cm_dra7xx_dump_end;
	}

	autoadjust_table_init(table);
	row = 0;

	if (id != CM_DRA7XX_MODS_COUNT)
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "%s Reg. Name",
			cm_dra7xx_mod_name_get(id));
	else
		strncpy(table[row][0], "CM Reg. Name", TABLE_MAX_ELT_LEN);
	strncpy(table[row][1], "Reg. Address",
		TABLE_MAX_ELT_LEN);
	strncpy(table[row][2], "Reg. Value", TABLE_MAX_ELT_LEN);
	row++;

	for (mid = 0; mid < CM_DRA7XX_MODS_COUNT; mid++) {
		if ((id != CM_DRA7XX_MODS_COUNT) && (mid != id))
			continue;
		else {
			mod = cm_dra7xx_mods[mid];
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

cm_dra7xx_dump_end:
	return err;
}
