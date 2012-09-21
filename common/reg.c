/*
 *
 * @Component			OMAPCONF
 * @Filename			reg.c
 * @Description			Register Structure Functions
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


#include <reg.h>
#include <lib.h>
#include <mem.h>
#include <string.h>


/* #define REG_DEBUG */
#ifdef REG_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		reg_init
 * @BRIEF		initialize reg structure.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	r: reg structure pointer
 * @param[in]		name: name field value
 * @param[in]		addr: addr field value
 * @param[in]		data: data field value
 * @DESCRIPTION		initialize reg structure.
 *//*------------------------------------------------------------------------ */
int reg_init(reg *r,
	char name[OMAPCONF_REG_NAME_MAX_LENGTH],
	unsigned int addr,
	unsigned int data)
{
	CHECK_NULL_ARG(r, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(name, OMAPCONF_ERR_ARG);

	strncpy(r->name, name, OMAPCONF_REG_NAME_MAX_LENGTH);
	r->addr = addr;
	r->data = data;
	r->data_valid = 1;

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		reg_xml_import
 * @BRIEF		import reg details from XML entry
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in,out]	r: reg structure pointer
 * @param[in]		xml_entry: XML entry (i.e. "<register id=..."),
 *				as generated with reg_xml_export()
 * @DESCRIPTION		import reg details from XML entry
 *//*------------------------------------------------------------------------ */
int reg_xml_import(reg *r, char *xml_entry)
{
	char name[OMAPCONF_REG_NAME_MAX_LENGTH];
	unsigned int addr;
	unsigned int data;
	char *token;
	int ret;

	CHECK_NULL_ARG(r, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(xml_entry, OMAPCONF_ERR_ARG);

	dprintf("%s(): xml_entry=%s\n", __func__, xml_entry);

	token = strtok(xml_entry, "= "); /* == "<register" */
	token = strtok(NULL, "= "); /* == "id" */
	if (strcmp(token, "id") != 0) {
		dprintf("%s(): could not get id token\n", __func__);
		return OMAPCONF_ERR_UNEXPECTED;
	}
	token = strtok(NULL, "= ");

	/* Retrieve register name */
	token = strtok(NULL, "= "); /* == "name" */
	if (strcmp(token, "name") != 0) {
		dprintf("%s(): could not get name token\n", __func__);
		return OMAPCONF_ERR_UNEXPECTED;
	}
	token = strtok(NULL, "\"");
	if (token == NULL) {
		dprintf("%s(): could not get name\n", __func__);
		return OMAPCONF_ERR_UNEXPECTED;
	}
	strncpy(name, token, OMAPCONF_REG_NAME_MAX_LENGTH);

	/* Retrieve register address */
	token = strtok(NULL, "= "); /* == "addr" */
	if (strcmp(token, "addr") != 0) {
		dprintf("%s(): could not get addr token\n", __func__);
		return OMAPCONF_ERR_UNEXPECTED;
	}
	token = strtok(NULL, "\"");
	if (token == NULL) {
		dprintf("%s(): could not get addr\n", __func__);
		return OMAPCONF_ERR_UNEXPECTED;
	}
	ret = sscanf(token, "0x%08X", &addr);
	if (ret != 1) {
		dprintf("%s(): could not get addr\n", __func__);
		return OMAPCONF_ERR_UNEXPECTED;
	}

	/* Retrieve register data */
	token = strtok(NULL, "= "); /* == "data" */
	if (strcmp(token, "data") != 0) {
		dprintf("%s(): could not get data token\n", __func__);
		return OMAPCONF_ERR_UNEXPECTED;
	}
	token = strtok(NULL, "\"");
	if (token == NULL) {
		dprintf("%s(): could not get data\n", __func__);
		return OMAPCONF_ERR_UNEXPECTED;
	}
	ret = sscanf(token, "0x%08X", &data);
	if (ret != 1) {
		dprintf("%s(): could not get data\n", __func__);
		return OMAPCONF_ERR_UNEXPECTED;
	}

	dprintf("%s(): name=%s addr=0x%08X data=0x%08X\n",
		__func__, name, addr, data);

	ret = reg_init(r, name, addr, data);

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		reg_xml_export
 * @BRIEF		export reg details to XML entry
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in]		r: reg structure pointer
 * @param[in,out]	xml_entry: XML entry (i.e. "<register id=..."),
 * @DESCRIPTION		export reg details to XML entry
 *//*------------------------------------------------------------------------ */
int reg_xml_export(reg r, char *xml_entry)
{
	/* FIXME */
	r = r;
	xml_entry = xml_entry;
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		reg_read
 * @BRIEF		return register content
 * @RETURNS		register content
 * @param[in]		r: a reg struct
 * @DESCRIPTION		return register content, either
 *			from the pre-loaded (via import) value, or
 *			from a true register access if there is no pre-loaded
 *			value.
 *//*------------------------------------------------------------------------ */
unsigned int reg_read(reg *r)
{
	unsigned int val;
	int ret;

	CHECK_NULL_ARG(r, 0xABBADEAD);

	if (r->data_valid == 1) {
		val = r->data;
	} else {
		ret = mem_read(r->addr, &val);
		if (ret != 0)
			fprintf(stderr, "%s(): read error at 0x%08X!!!\n",
				__func__, r->addr);
	}

	return val;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		reg_write
 * @BRIEF		update register content of, either:
 *				the pre-loaded (via import) value, or
 *				the real register if there is no pre-loaded
 *				value.
 * @RETURNS		0 in case of success
 *			-1 if content couldn't be updated (for any reason)
 * @param[in,out]	r: a reg struct
 * @param[in]		val: updated register content
 * @DESCRIPTION		update register content of, either:
 *				the pre-loaded (via import) value, or
 *				the real register if there is no pre-loaded
 *				value.
 *//*------------------------------------------------------------------------ */
int reg_write(reg *r, unsigned int val)
{
	int ret;

	CHECK_NULL_ARG(r, -1);
	CHECK_NULL_ARG(reg_addr_get(r), -1);

	if (r->data_valid == 1) {
		r->data = val;
		return 0;
	} else {
		ret = mem_write(reg_addr_get(r), val);
		if (ret != 0)
			return -1;
		else
			return 0;
	}

	return val;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		reg_name_get
 * @BRIEF		return register name
 * @RETURNS		register name pointer
 * @param[in]		r: a reg struct pointer
 * @DESCRIPTION		return register name
 *//*------------------------------------------------------------------------ */
char *reg_name_get(reg *r)
{
	CHECK_NULL_ARG(r, NULL);

	return r->name;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		reg_addr_get
 * @BRIEF		return register physical address
 * @RETURNS		register physical address
 * @param[in]		r: a reg struct pointer
 * @DESCRIPTION		return register physical address
 *//*------------------------------------------------------------------------ */
unsigned int reg_addr_get(reg *r)
{
	CHECK_NULL_ARG(r, 0);

	return r->addr;
}
