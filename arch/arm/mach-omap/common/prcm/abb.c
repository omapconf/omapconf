/*
 *
 * @Component			OMAPCONF
 * @Filename			abb.c
 * @Description			PRCM ABB Common Definitions & Functions
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


#include <abb.h>
#include <autoadjust_table.h>
#include <lib.h>
#include <string.h>
#include <cpuinfo.h>


/* #define ABB_DEBUG */
#ifdef ABB_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		abb_status2string
 * @BRIEF		convert bitfield value from register into string
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	s: destination string (pre-allocated)
 * @param[in]		status: bitfield value
 * @DESCRIPTION		convert bitfield value from register into string
 *//*------------------------------------------------------------------------ */
int abb_status2string(char s[9], unsigned int status)
{
	if (s == NULL)
		return OMAPCONF_ERR_ARG;

	switch (status) {
	case 0:
		strcpy(s, "Bypass");
		break;
	case 1:
		strcpy(s, "RBB");
		break;
	case 2:
		strcpy(s, "FBB");
		break;
	case 3:
		strcpy(s, "Reserved");
		break;
	default:
		return OMAPCONF_ERR_ARG;
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		abb_opp_sel2string
 * @BRIEF		convert bitfield value from register into string
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	s: destination string (pre-allocated)
 * @param[in]		opp_sel: bitfield value
 * @DESCRIPTION		convert bitfield value from register into string
 *//*------------------------------------------------------------------------ */
int abb_opp_sel2string(char s[8], unsigned int opp_sel)
{
	if (s == NULL)
		return OMAPCONF_ERR_ARG;

	switch (opp_sel) {
	case 0:
	case 2:
		strcpy(s, "Nominal");
		break;
	case 1:
		strcpy(s, "Fast");
		break;
	case 3:
		strcpy(s, "Slow");
		break;
	default:
		return OMAPCONF_ERR_ARG;
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		abb_config_show
 * @BRIEF		analyze power configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output file
 * @param[in]		sysclk_rate: system_clock rate (MHz)
 * @param[in]		abb_mpu_setup: PRM_LDO_ABB_MPU_SETUP register content
 * @param[in]		abb_mpu_ctrl: PRM_LDO_ABB_MPU_CTRL register content
 * @param[in]		abb_iva_setup: PRM_LDO_ABB_IVA_SETUP register content
 * @param[in]		abb_iva_ctrl: PRM_LDO_ABB_IVA_CTRL register content
 * @DESCRIPTION		analyze power configuration
 *//*------------------------------------------------------------------------ */
int abb_config_show(FILE *stream, double sysclk_rate,
	unsigned int abb_mpu_setup, unsigned int abb_mpu_ctrl,
	unsigned int abb_iva_setup, unsigned int abb_iva_ctrl)
{
	unsigned short int abb_mpu_en, abb_iva_en;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row = 0;
	char s[9];

	CHECK_NULL_ARG(stream, OMAPCONF_ERR_ARG);
	if (sysclk_rate <= 0.0) {
		fprintf(stderr, "%s(): sysclk_rate (%lf) <= 0!!!\n", __func__,
			sysclk_rate);
		return OMAPCONF_ERR_ARG;
	}

	dprintf("%s(): sysclk_rate=%lfMHz abb_mpu_setup=0x%08X, "
		"abb_mpu_ctrl=0x%08X, abb_iva_setup=0x%08X, "
		"abb_iva_ctrl=0x%08X\n", sysclk_rate,
		abb_mpu_setup, abb_mpu_ctrl, abb_iva_setup, abb_iva_ctrl);

	abb_mpu_en = extract_bit(abb_mpu_setup, 0);
	abb_iva_en = extract_bit(abb_iva_setup, 0);

	autoadjust_table_init(table);
	row = 0;

	strncpy(table[row][0], "ABB Configuration", TABLE_MAX_ELT_LEN);
	strncpy(table[row][1], "MPU Voltage Domain", TABLE_MAX_ELT_LEN);
	if (cpu_is_omap44xx())
		strncpy(table[row][2], "IVAHD Voltage Domain",
			TABLE_MAX_ELT_LEN);
	else
		strncpy(table[row][2], "MM Voltage Domain",
			TABLE_MAX_ELT_LEN);

	row++;

	strncpy(table[row][0], "Mode", TABLE_MAX_ELT_LEN);
	strncpy(table[row][1],
		((abb_mpu_en == 1) ? "Enabled" : "Disabled"),
		TABLE_MAX_ELT_LEN);
	strncpy(table[row][2],
		((abb_iva_en == 1) ? "Enabled" : "Disabled"),
		TABLE_MAX_ELT_LEN);
	row++;

	strncpy(table[row][0], "Status", TABLE_MAX_ELT_LEN);
	if (abb_mpu_en == 1) {
		abb_status2string(s,
			extract_bitfield(abb_mpu_ctrl, 3, 2));
		strncpy(table[row][1],
			s,
			TABLE_MAX_ELT_LEN);
	}
	if (abb_iva_en == 1) {
		abb_status2string(s,
			extract_bitfield(abb_iva_ctrl, 3, 2));
		strncpy(table[row][2],
			s,
			TABLE_MAX_ELT_LEN);
	}
	row++;

	strncpy(table[row][0], "In Transition?", TABLE_MAX_ELT_LEN);
	if (abb_mpu_en == 1)
		strncpy(table[row][1],
			((extract_bit(abb_mpu_ctrl, 6) == 1) ? "YES" : "No"),
			TABLE_MAX_ELT_LEN);
	if (abb_iva_en == 1)
		strncpy(table[row][2],
			((extract_bit(abb_iva_ctrl, 6) == 1) ? "YES" : "No"),
			TABLE_MAX_ELT_LEN);
	row++;

	strncpy(table[row][0], "Selected OPP", TABLE_MAX_ELT_LEN);
	if (abb_mpu_en == 1) {
		abb_opp_sel2string(s,
			extract_bitfield(abb_mpu_ctrl, 0, 2));
		strncpy(table[row][1],
			s,
			TABLE_MAX_ELT_LEN);
	}
	if (abb_iva_en == 1) {
		abb_opp_sel2string(s,
			extract_bitfield(abb_iva_ctrl, 0, 2));
		strncpy(table[row][2],
			s,
			TABLE_MAX_ELT_LEN);
	}
	row++;

	strncpy(table[row][0], "LDO ABB Mode When Voltage is:",
		TABLE_MAX_ELT_LEN);
	row++;
	strncpy(table[row][0], "  Slow OPP (ACTIVE_RBB_SEL)",
		TABLE_MAX_ELT_LEN);
	if (abb_mpu_en == 1)
		strncpy(table[row][1],
			((extract_bit(abb_mpu_setup,
				1) == 1) ? "RBB" : "Bypass"),
			TABLE_MAX_ELT_LEN);
	if (abb_iva_en == 1)
		strncpy(table[row][2],
			((extract_bit(abb_iva_setup,
				1) == 1) ? "RBB" : "Bypass"),
			TABLE_MAX_ELT_LEN);
	row++;

	strncpy(table[row][0], "  Fast OPP (ACTIVE_FBB_SEL)",
		TABLE_MAX_ELT_LEN);
	if (abb_mpu_en == 1)
		strncpy(table[row][1],
			((extract_bit(abb_mpu_setup,
				2) == 1) ? "FBB" : "Bypass"),
			TABLE_MAX_ELT_LEN);
	if (abb_iva_en == 1)
		strncpy(table[row][2],
			((extract_bit(abb_iva_setup,
				2) == 1) ? "FBB" : "Bypass"),
			TABLE_MAX_ELT_LEN);
	row++;

	strncpy(table[row][0], "  Sleep Volt. (SLEEP_RBB_SEL)",
		TABLE_MAX_ELT_LEN);
	if (abb_mpu_en == 1)
		strncpy(table[row][1],
			((extract_bit(abb_mpu_setup,
				3) == 1) ? "RBB" : "Bypass"),
			TABLE_MAX_ELT_LEN);
	if (abb_iva_en == 1)
		strncpy(table[row][2],
			((extract_bit(abb_iva_setup,
				3) == 1) ? "RBB" : "Bypass"),
			TABLE_MAX_ELT_LEN);
	row++;
	strncpy(table[row][0], "LDO Settling Time", TABLE_MAX_ELT_LEN);
	if (abb_mpu_en == 1)
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%d (%fus)",
		extract_bitfield(abb_mpu_setup, 8, 8),
		extract_bitfield(abb_mpu_setup, 8, 8) *
		(16.0 / sysclk_rate));
	if (abb_iva_en == 1)
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%d (%fus)",
		extract_bitfield(abb_iva_setup, 8, 8),
		extract_bitfield(abb_iva_setup, 8, 8) *
		(16.0 / sysclk_rate));
	row++;
	strncpy(table[row][0], "  (Target is 50us)", TABLE_MAX_ELT_LEN);
	row++;

	strncpy(table[row][0], "Stat", TABLE_MAX_ELT_LEN);
	if (abb_mpu_en == 1)
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%d (%.3fus)",
		extract_bitfield(abb_mpu_setup, 8, 8),
		extract_bitfield(abb_mpu_setup, 8, 8) *
		(16.0 / sysclk_rate));
	if (abb_iva_en == 1)
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%d (%.3fus)",
		extract_bitfield(abb_iva_setup, 8, 8),
		extract_bitfield(abb_iva_setup, 8, 8) *
		(16.0 / sysclk_rate));

	autoadjust_table_print(table, row, 3);

	return 0;
}
