/*
 *
 * @Component			OMAPCONF
 * @Filename			prm_am437x.c
 * @Description			AM437x PRM Register Functions
 * @Author			Dave Gerlach <d-gerlach@ti.com>
 * @Date			2016
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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
#include <cpuinfo.h>
#include <lib.h>
#include <module.h>
#include <prcm-module.h>
#include <prm_am437x.h>

#ifdef PRM_AM437X_DEBUG
#define dprintf(format, ...)    printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/*
 * @FUNCTION        prm_am437x_mod_name_get
 * @BRIEF       return PRM module name
 * @RETURNS     PRM module name
 *          NULL in case of incorrect id
 * @param[in]       id: PRM module ID
 * @DESCRIPTION     return PRM module name
 */
const char *prm_am437x_mod_name_get(prm_am437x_mod_id id)
{
	if (id >= PRM_AM437X_MODS_COUNT) {
		fprintf(stderr, "%s(): id (%u) >= PRM_AM437X_MODS_COUNT (%u)!\n",
			__func__, id, PRM_AM437X_MODS_COUNT);
		return NULL;
	}

	return prm_am437x_mods_name[id];
}


/*
 * @FUNCTION		prm_am437x_dump
 * @BRIEF		dump selected registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output stream
 * @param[in]		id: PRM module ID
 *			If id == PRM_AM437X_MODS_COUNT, dump all PRM registers.
 * @DESCRIPTION		dump selected registers and pretty-print it in selected
 *			output stream
 */
int prm_am437x_dump(FILE *stream, prm_am437x_mod_id id)
{
	unsigned int i, mid;
	unsigned int val;
	reg **mod;
	reg *r;
	char s[TABLE_MAX_ELT_LEN];
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row = 0;

	if (!cpu_is_am437x())
		return OMAPCONF_ERR_CPU;

	CHECK_NULL_ARG(stream, OMAPCONF_ERR_ARG);

	if (id > PRM_AM437X_MODS_COUNT) {
		fprintf(stderr, "%s(): id (%u) > PRM_AM437X_MODS_COUNT!!! (%u)\n",
			__func__, id, PRM_AM437X_MODS_COUNT);
		return OMAPCONF_ERR_ARG;
	}

	autoadjust_table_init(table);

	if (id != PRM_AM437X_MODS_COUNT)
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "%s Reg. Name",
			prm_am437x_mod_name_get(id));
	else
		strncpy(table[row][0], "PRM Reg. Name", TABLE_MAX_ELT_LEN);

	strncpy(table[row][1], "Reg. Address", TABLE_MAX_ELT_LEN);
	strncpy(table[row][2], "Reg. Value", TABLE_MAX_ELT_LEN);
	row++;

	for (mid = 0; mid < PRM_AM437X_MODS_COUNT; mid++) {
		if ((id != PRM_AM437X_MODS_COUNT) && (mid != id)) {
			continue;
		} else {
			mod = prm_am437x_mods[mid];
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
