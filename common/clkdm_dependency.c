/*
 *
 * @Component			OMAPCONF
 * @Filename			clkdm_dependency.c
 * @Description			Clock Domain Dependencies Common Definitions &
 *				Functions
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


#include <clkdm_dependency.h>
#include <lib.h>


static const char
	clkdmdep_type_names_table[CLKDMDEP_TYPE_MAX][CLKDMDEP_TYPE_MAX_NAME_LENGTH] = {
	"Static",
	"Dynamic"};


static const char
	clkdmdep_ctrl_type_names_table[CLKDMDEP_CONTROL_TYPE_MAX][CLKDMDEP_CTRL_TYPE_MAX_NAME_LENGTH] = {
	"NA",
	"R/W",
	"RO"};


static const char
	clkdmdep_status_names_table[CLKDMDEP_STATUS_MAX][CLKDMDEP_STATUS_MAX_NAME_LENGTH] = {
	"Disabled",
	"Enabled"};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdmdep_type_name_get
 * @BRIEF		return type name
 * @RETURNS		name on success
 *			NULL in case of error
 * @param[in]		type: dependency type (static/dynamic)
 * @DESCRIPTION		return type name
 *//*------------------------------------------------------------------------ */
const char *clkdmdep_type_name_get(clkdmdep_type type)
{
	CHECK_ARG_LESS_THAN(type, CLKDMDEP_TYPE_MAX, NULL);

	return clkdmdep_type_names_table[type];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdmdep_ctrl_type_name_get
 * @BRIEF		return control type name
 * @RETURNS		name on success
 *			NULL in case of error
 * @param[in]		type: dependency control type (RW/RO/...)
 * @DESCRIPTION		return control type name
 *//*------------------------------------------------------------------------ */
const char *clkdmdep_ctrl_type_name_get(clkdmdep_ctrl_type type)
{
	CHECK_ARG_LESS_THAN(type, CLKDMDEP_CONTROL_TYPE_MAX, NULL);

	return clkdmdep_ctrl_type_names_table[type];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdmdep_status_name_get
 * @BRIEF		return status name
 * @RETURNS		name on success
 *			NULL in case of error
 * @param[in]		st: status (en/dis)
 * @DESCRIPTION		return status name
 *//*------------------------------------------------------------------------ */
const char *clkdmdep_status_name_get(clkdmdep_status st)
{
	CHECK_ARG_LESS_THAN(st, CLKDMDEP_STATUS_MAX, NULL);

	return clkdmdep_status_names_table[st];
}
