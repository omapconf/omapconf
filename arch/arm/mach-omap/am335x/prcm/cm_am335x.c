/*
 *
 * @Component			OMAPCONF
 * @Filename			cm_am335x.c
 * @Description			AM335X CM Register Functions
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
#include <cm_am335x.h>
#include <cpuinfo.h>
#include <lib.h>
#include <lib_am335x.h>
#include <module.h>
#include <prcm-module.h>

#ifdef CM_AM335X_DEBUG
#define dprintf(format, ...)    printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cm_am335x_mod_name_get
 * @BRIEF		return CM module name
 * @RETURNS		CM module name
 *			NULL in case of incorrect id
 * @param[in]		id: CM module ID
 * @DESCRIPTION		return CM module name
 *//*------------------------------------------------------------------------ */
const char *cm_am335x_mod_name_get(cm_am335x_mod_id id)
{
	if (id >= CM_AM335X_MODS_COUNT) {
		fprintf(stderr, "%s(): id (%u) >= CM_AM335X_MODS_COUNT (%u)!\n",
			__func__, id, CM_AM335X_MODS_COUNT);
		return NULL;
	}

	return cm_am335x_mods_name[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cm_am335x_dump
 * @BRIEF		dump selected registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output stream
 * @param[in]		id: CM module ID
 *			If id == CM_AM335X_MODS_COUNT, dump all CM registers.
 * @DESCRIPTION		dump selected registers and pretty-print it in selected
 *			output stream
 *//*------------------------------------------------------------------------ */
int cm_am335x_dump(FILE *stream, cm_am335x_mod_id id)
{
	unsigned int i, mid;
	unsigned int val;
	reg **mod;
	reg *r;
	char s[TABLE_MAX_ELT_LEN];
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row = 0;

	if (!cpu_is_am335x())
		return OMAPCONF_ERR_CPU;

	CHECK_NULL_ARG(stream, OMAPCONF_ERR_ARG);

	if (id > CM_AM335X_MODS_COUNT) {
		fprintf(stderr, "%s(): id (%u) > CM_AM335X_MODS_COUNT!!! (%u)\n",
			__func__, id, CM_AM335X_MODS_COUNT);
		return OMAPCONF_ERR_ARG;
	}

	autoadjust_table_init(table);

	if (id != CM_AM335X_MODS_COUNT)
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "%s Reg. Name",
			cm_am335x_mod_name_get(id));
	else
		strncpy(table[row][0], "CM Reg. Name", TABLE_MAX_ELT_LEN);

	strncpy(table[row][1], "Reg. Address", TABLE_MAX_ELT_LEN);
	strncpy(table[row][2], "Reg. Value", TABLE_MAX_ELT_LEN);
	row++;

	for (mid = 0; mid < CM_AM335X_MODS_COUNT; mid++) {
		if ((id != CM_AM335X_MODS_COUNT) && (mid != id)) {
			continue;
		} else {
			mod = cm_am335x_mods[mid];
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

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cm_am335x_name2addr
 * @BRIEF		retrieve physical address of a register, given its name.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		name: register name
 * @param[in, out]	addr: register address
 * @DESCRIPTION		retrieve physical address of a register, given its name.
 *//*------------------------------------------------------------------------ */
int cm_am335x_name2addr(char *name, unsigned int *addr)
{
	if (!cpu_is_am335x())
		return OMAPCONF_ERR_CPU;

	/* Creates pointer to register modules */
	reg ***cm_mods[1] = {
		(reg ***) &cm_am335x_mods
	};


	return am335x_name2addr(name, addr, cm_mods);
}
