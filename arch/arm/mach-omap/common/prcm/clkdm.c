/*
 *
 * @Component			OMAPCONF
 * @Filename			clkdm.c
 * @Description			Clock Domain Definitions & Functions
 * @Author			Patrick Titiano (p-titiano@ti.com)
 * @Date			2006
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2006-2011 Texas Instruments Incorporated - http://www.ti.com/
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


#include <clkdm.h>
#include <lib.h>
#include <stdlib.h>
#include <string.h>


/* #define PRCM_CLKDM_DEBUG */
#ifdef PRCM_CLKDM_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static const char
	clkdm_ctrl_mode_names[CLKM_CTRL_MODE_MAX][CLKDM_CTRL_MODE_MAX_NAME_LENGTH] = {
	"NO SLEEP",
	"SW-Forced Sleep",
	"SW-Forced Wakeup",
	"HW-Auto"};


static const char
	clkdm_status_names[CLKDM_STATUS_MAX][CLKDM_STATUS_MAX_NAME_LENGTH] = {
	"Gated",
	"Running"};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm_ctrl_mode_name_get
 * @BRIEF		return clock domain transition control mode name
 * @RETURNS		clock domain transition control mode name on success
 *			"FIXME" in case of error
 * @param[in]		mode: valid clock domain transition control mode
 * @DESCRIPTION		return clock domain transition control mode name
 *//*------------------------------------------------------------------------ */
const char *clkdm_ctrl_mode_name_get(clkdm_ctrl_mode mode)
{
	CHECK_ARG_LESS_THAN(mode, CLKM_CTRL_MODE_MAX, "FIXME");

	return clkdm_ctrl_mode_names[mode];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm_ctrl_mode_get
 * @BRIEF		return clock domain transition control mode
 * @RETURNS		clock domain transition control mode on success
 *			CLKM_CTRL_MODE_MAX in case of error
 * @param[in]		cm_clkstctrl: CM_xyz_CLKSTCTRL register content
 * @DESCRIPTION		return clock domain transition control mode
 *//*------------------------------------------------------------------------ */
clkdm_ctrl_mode clkdm_ctrl_mode_get(unsigned int cm_clkstctrl)
{
	clkdm_ctrl_mode mode;

	/* Retrieve clock domain transition control mode */
	mode = (clkdm_ctrl_mode) extract_bitfield(cm_clkstctrl, 0, 2);
	dprintf("%s(): cm_clkstctrl=0x%08X => mode=%u (%s) (bit [1-0])\n",
		__func__, cm_clkstctrl,	mode, clkdm_ctrl_mode_name_get(mode));

	return mode;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm_status_name_get
 * @BRIEF		return clock domain status name
 * @RETURNS		clock domain status name on success
 *			"FIXME" in case of error
 * @param[in]		st: valid clock domain status
 * @DESCRIPTION		return clock domain status name
 *//*------------------------------------------------------------------------ */
const char *clkdm_status_name_get(clkdm_status st)
{
	CHECK_ARG_LESS_THAN(st, CLKDM_STATUS_MAX, "FIXME");

	return clkdm_status_names[st];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm_status_get
 * @BRIEF		return clock domain status
 * @RETURNS		clock domain status on success
 *			CLKDM_STATUS_MAX in case of error
 * @param[in]		cm_clkstctrl: CM_xyz_CLKSTCTRL register content
 * @DESCRIPTION		return clock domain status
 *//*------------------------------------------------------------------------ */
clkdm_status clkdm_status_get(unsigned int cm_clkstctrl)
{
	clkdm_status clkdmst;
	unsigned int val;

	/* Retrieve clock domain status */
	val = extract_bitfield(cm_clkstctrl, 8, 24);
	if (val == 0)
		clkdmst = CLKDM_GATED;
	else
		clkdmst = CLKDM_RUNNING;
	dprintf("%s(): cm_clkstctrl=0x%08X => clkst=%u (%s) (bits [31-8])\n",
		__func__, cm_clkstctrl, clkdmst,
		clkdm_status_name_get(clkdmst));

	return clkdmst;
}
