/*
 *
 * @Component			OMAPCONF
 * @Filename			sr54xx.c
 * @Description			OMAP5 SMARTREFLEX Registers Definitions &
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


#include <sr54xx.h>
#include <sr.h>
#include <vp.h>
#include <module.h>
#include <vp54xx.h>
#include <vc54xx.h>
#include <prm54xx.h>
#include <module54xx.h>
#include <lib.h>
#include <autoadjust_table.h>
#include <help.h>
#include <reg.h>
#include <cpuinfo.h>
#include <pmic.h>


/* #define SR54XX_DEBUG */
#ifdef SR54XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr54xx_mod_name_get
 * @BRIEF		return SR module name
 * @RETURNS		SR module name
 *			NULL in case of incorrect id
 * @param[in]		id: SR module ID
 * @DESCRIPTION		return SR module name
 *//*------------------------------------------------------------------------ */
const char *sr54xx_mod_name_get(sr54xx_mod_id id)
{
	if (id >= SR54XX_MODS_COUNT) {
		fprintf(stderr, "%s(): id (%u) >= SR54XX_MODS_COUNT (%u)!\n",
			__func__, id, SR54XX_MODS_COUNT);
		return NULL;
	}

	return sr54xx_mods_name[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr54xx_is_accessible
 * @BRIEF		check if SR module is accessible
 * @RETURNS		1 if SR module is accessible, 0 otherwise
 * @param[in]		id: valid SR module ID
 * @DESCRIPTION		check if SR module is accessible
 *//*------------------------------------------------------------------------ */
unsigned int sr54xx_is_accessible(sr54xx_mod_id id)
{
	const char *mod_name;

	if (!cpu_is_omap54xx())
		return 0;

	switch (id) {
	case SR54XX_SMARTREFLEX_MPU:
		mod_name = MOD_SMARTREFLEX_MPU;
		break;
	case SR54XX_SMARTREFLEX_MM:
		mod_name = MOD_SMARTREFLEX_MM;
		break;
	case SR54XX_SMARTREFLEX_CORE:
		mod_name = MOD_SMARTREFLEX_CORE;
		break;
	default:
		return 0;
	}

	if (module_is_accessible(mod_name) == 1) {
		dprintf("%s(%s): SR module is accessible\n", __func__,
			mod_name);
		return 1;
	} else {
		dprintf("%s(%s): SR module is NOT accessible\n", __func__,
			mod_name);
		return 0;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr54xx_is_enabled
 * @BRIEF		check if SR module is enabled
 * @RETURNS		1 if SR module is enabled, 0 if not
 * @param[in]		id: valid SR module ID
 * @DESCRIPTION		check if SR module is enabled
 *//*------------------------------------------------------------------------ */
unsigned int sr54xx_is_enabled(sr54xx_mod_id id)
{
	reg **mod;
	reg *sr_config_reg;
	unsigned int sr_config;

	if (!cpu_is_omap54xx())
		return 0;

	if (!sr54xx_is_accessible(id))
		return 0;

	/* Read SR_CONFIG register */
	mod = sr54xx_mods[id];
	sr_config_reg = mod[0];
	sr_config = reg_read(sr_config_reg);

	return sr_is_enabled(sr_config);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr54xx_last_vp_voltage_get
 * @BRIEF		return the last voltage set by the voltage processor
 *			for a domain.
 * @RETURNS		>= 0 last voltage set by voltage processor for this
 *			domain (in volt)
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 * @param[in]		id: valid SR module ID
 * @DESCRIPTION		return the last voltage set by the voltage processor
 *			for a domain
 *			NB: SR/VP/VC HAVE TO BE AT LEAST INITIALIZED (SR COULD
 *			BE DISABLED) OTHERWISE THIS VALUE HAS NO SENSE.
 *//*------------------------------------------------------------------------ */
double sr54xx_last_vp_voltage_get(sr54xx_mod_id id)
{
	unsigned int vp_voltage, uv;
	unsigned char vsel;
	reg *vp_voltage_r, *vp_r_mm, *vp_r_core, *vp_r_mpu;
	voltdm54xx_id vdd_id = VDD54XX_ID_MAX;

	CHECK_CPU(54xx, (double) OMAPCONF_ERR_CPU);

	/* Retrieve corresponding register address */
	if (cpu_revision_get() == REV_ES1_0) {
		vp_r_mpu = &omap5430es1_prm_vp_mpu_voltage;
		vp_r_mm = &omap5430es1_prm_vp_mm_voltage;
		vp_r_core = &omap5430es1_prm_vp_core_voltage;
	} else {
		vp_r_mpu = &omap5430_prm_vp_mpu_voltage;
		vp_r_mm = &omap5430_prm_vp_mm_voltage;
		vp_r_core = &omap5430_prm_vp_core_voltage;
	}

	switch (id) {
	case SR54XX_SMARTREFLEX_MPU:
		vp_voltage_r = vp_r_mpu;
		vdd_id = VDD54XX_MPU;
		break;
	case SR54XX_SMARTREFLEX_MM:
		vp_voltage_r = vp_r_mm;
		vdd_id = VDD54XX_MM;
		break;
	case SR54XX_SMARTREFLEX_CORE:
		vp_voltage_r = vp_r_core;
		vdd_id = VDD54XX_CORE;
		break;
	default:
		return (double) OMAPCONF_ERR_ARG;
	}

	/* Retrieve register content and extract voltage */
	vp_voltage = reg_read(vp_voltage_r);
	vp_last_voltage_get(vp_voltage, (unsigned short) vdd_id, &vsel, &uv);
	return (double) uv / 1000000.0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr54xx_dump
 * @BRIEF		dump selected registers and pretty-print it in selected
 *			output stream
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output stream
 * @param[in]		id: SR module ID - If id == SR54XX_MODS_COUNT,
 *			dump all SR registers.
 * @DESCRIPTION		dump selected registers and pretty-print it in selected
 *			output stream
 *//*------------------------------------------------------------------------ */
int sr54xx_dump(FILE *stream, sr54xx_mod_id id)
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
		goto sr54xx_dump_end;
	}

	if (id > SR54XX_MODS_COUNT) {
		fprintf(stderr, "%s(): id (%u) > SR54XX_MODS_COUNT!!! (%u)\n",
			__func__, id, SR54XX_MODS_COUNT);
		err = OMAPCONF_ERR_ARG;
		goto sr54xx_dump_end;
	}

	autoadjust_table_init(table);
	row = 0;

	if (id != SR54XX_MODS_COUNT)
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "%s Reg. Name",
			sr54xx_mod_name_get(id));
	else
		strncpy(table[row][0], "SR Reg. Name", TABLE_MAX_ELT_LEN);
	strncpy(table[row][1], "Reg. Address",
		TABLE_MAX_ELT_LEN);
	strncpy(table[row][2], "Reg. Value", TABLE_MAX_ELT_LEN);
	row++;

	for (mid = SR54XX_SMARTREFLEX_MPU; mid < SR54XX_MODS_COUNT; mid++) {
		if ((id != SR54XX_MODS_COUNT) && (mid != id))
			continue;
		else {
			if (!sr54xx_is_enabled(mid)) {
				if (stream != NULL)
					fprintf(stream, "%s module not running"
						", registers not accessible.\n",
						sr54xx_mod_name_get(mid));
				return 0;
			}

			mod = sr54xx_mods[mid];
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

	autoadjust_table_fprint(stream, table, row, 3);

sr54xx_dump_end:
	return err;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr54xx_export
 * @BRIEF		export module register content to file, in XML format.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	fp: output file stream (opened for write operations)
 * @param[in]		id: SR module ID
 * @DESCRIPTION		export module register content to file, in XML format.
 *//*------------------------------------------------------------------------ */
int sr54xx_export(FILE *fp, sr54xx_mod_id id)
{
	reg **mod;
	unsigned int i;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(fp, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(id, SR54XX_MODS_COUNT, OMAPCONF_ERR_ARG);

	if (!sr54xx_is_enabled(id)) {
		printf("%s export: module not running, skipping "
			"registers export.\n", sr54xx_mod_name_get(id));
		return 0;
	}

	mod = sr54xx_mods[id];

	fprintf(fp, "          <submodule id=\"%u\" name=\"%s\">\n",
		id, sr54xx_mod_name_get(id));

	for (i = 0; i < OMAP5430_SMARTREFLEX_CORE_MOD_REGCOUNT; i++)
		fprintf(fp, "            <register id=\"%u\" name=\"%s\" "
			"addr=\"0x%08X\" data=\"0x%08X\" />\n", i,
			(mod[i])->name, (mod[i])->addr, reg_read(mod[i]));

	fprintf(fp, "          </submodule>\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr54xx_import
 * @BRIEF		import OMAP Smart-Reflex registers from XML file
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in,out]	fp: XML import file descriptor
 * @param[in]		id: SR module ID
 * @DESCRIPTION		import OMAP Smart-Reflex registers from XML file,
 *			generated with lib54xx_export().
 *//*------------------------------------------------------------------------ */
int sr54xx_import(FILE *fp, sr54xx_mod_id id)
{
	reg **mod;
	char line[256], sline[256];
	char *xml_entry;
	int ret, i, n;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(fp, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(id, SR54XX_MODS_COUNT, OMAPCONF_ERR_ARG);

	mod = sr54xx_mods[id];
	rewind(fp);

	/* Search for the SR module tag */
	sprintf(sline, "<submodule id=\"%u\" name=\"%s\">",
		id, sr54xx_mod_name_get(id));
	while (fgets(line, sizeof(line), fp) != NULL) {
		if (strstr(line, sline) == NULL)
			continue;
		/* Import register content */
		for (i = 0; i < OMAP5430_SMARTREFLEX_CORE_MOD_REGCOUNT; i++) {
			if (fgets(line, sizeof(line), fp) == NULL)
				return OMAPCONF_ERR_UNEXPECTED;
			line[strlen(line) - 1] = '\0'; /* remove ending '\n' */
			xml_entry = strstr(line, "<"); /* remove spaces */

			dprintf("%s(%u (%s)): xml_entry=%s\n", __func__, id,
				sr54xx_mod_name_get(id), xml_entry);

			/* Check register id is correct */
			ret = sscanf(xml_entry, "<register id=\"%u\" %s",
				&n, sline);
			if (ret != 2) {
				dprintf("%s(%u (%s)): could not get id\n",
					__func__, id, sr54xx_mod_name_get(id));
				return OMAPCONF_ERR_UNEXPECTED;
			}
			if (n != i) {
				dprintf("%s(%u (%s)): register id does not "
					"match! (n=%u, i=%u)\n", __func__, id,
					sr54xx_mod_name_get(id), n, i);
				return OMAPCONF_ERR_UNEXPECTED;
			}

			ret = reg_xml_import(mod[i], xml_entry);
			if (ret != 0)
				return ret;
		}
		dprintf("%s(%u (%s)): all registers imported.\n", __func__, id,
			sr54xx_mod_name_get(id));
		break;
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr54xx_module_config_show
 * @BRIEF		analyze Smart-Reflex module configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 * @param[in]		stream: output file (NULL: no output (silent))
 * @DESCRIPTION		analyze Smart-Reflex module configuration
 *//*------------------------------------------------------------------------ */
int sr54xx_module_config_show(FILE *stream)
{
	sr_registers sr_regs[3];
	unsigned int i;
	const char *sr_mod_names[3] = {
		MOD_SMARTREFLEX_MPU,
		MOD_SMARTREFLEX_MM,
		MOD_SMARTREFLEX_CORE};

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	for (i = 0; i < 3; i++) {
		if (module_is_accessible(sr_mod_names[i]) != 1) {
			sr_regs[i].accessible = 0;
			continue;
		}

		sr_regs[i].accessible = 1;
		sr_regs[i].srconfig = reg_read(sr54xx_mods[i][0]);
		sr_regs[i].srstatus = reg_read(sr54xx_mods[i][1]);
		sr_regs[i].senval = reg_read(sr54xx_mods[i][2]);
		sr_regs[i].senmin = reg_read(sr54xx_mods[i][3]);
		sr_regs[i].senmax = reg_read(sr54xx_mods[i][4]);
		sr_regs[i].senavg = reg_read(sr54xx_mods[i][5]);
		sr_regs[i].avgweight = reg_read(sr54xx_mods[i][6]);
		sr_regs[i].nvaluereciprocal = reg_read(sr54xx_mods[i][7]);
		sr_regs[i].irqstatus_raw = reg_read(sr54xx_mods[i][8]);
		sr_regs[i].irqstatus = reg_read(sr54xx_mods[i][9]);
		sr_regs[i].irqenable_set = reg_read(sr54xx_mods[i][10]);
		sr_regs[i].senerror = reg_read(sr54xx_mods[i][12]);
		sr_regs[i].errconfig = reg_read(sr54xx_mods[i][13]);
		sr_regs[i].lvtsenval = reg_read(sr54xx_mods[i][14]);
		sr_regs[i].lvtsenmin = reg_read(sr54xx_mods[i][15]);
		sr_regs[i].lvtsenmax = reg_read(sr54xx_mods[i][16]);
		sr_regs[i].lvtsenavg = reg_read(sr54xx_mods[i][17]);
		sr_regs[i].lvtnvaluereciprocal = reg_read(sr54xx_mods[i][18]);
	}

	if ((sr_regs[0].accessible == 0) &&
		(sr_regs[1].accessible == 0) &&
		(sr_regs[2].accessible == 0)) {
		printf("All Smart-Reflex Modules disabled.\n");
		return 0;
	}

	return sr_config_show(stream, sr_regs);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr54xx_config_show
 * @BRIEF		analyze Smart-Reflex complete configuration
 *			(SR module + VC + VP)
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 * @param[in]		stream: output file (NULL: no output (silent))
 * @DESCRIPTION		analyze Smart-Reflex complete configuration
 *			(SR module + VC + VP)
 *//*------------------------------------------------------------------------ */
int sr54xx_config_show(FILE *stream)
{
	vc54xx_registers vc_regs;
	int ret;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	if (cpu_revision_get() == REV_ES1_0) {
		vc_regs.vc_smps_mpu_config = reg_read(&omap5430es1_prm_vc_smps_mpu_config);
		vc_regs.vc_smps_mm_config = reg_read(&omap5430es1_prm_vc_smps_mm_config);
		vc_regs.vc_smps_core_config =
			reg_read(&omap5430es1_prm_vc_smps_core_config);
		vc_regs.vc_val_cmd_vdd_mpu_l =
			reg_read(&omap5430es1_prm_vc_val_cmd_vdd_mpu_l);
		vc_regs.vc_val_cmd_vdd_mm_l =
			reg_read(&omap5430es1_prm_vc_val_cmd_vdd_mm_l);
		vc_regs.vc_val_cmd_vdd_core_l =
			reg_read(&omap5430es1_prm_vc_val_cmd_vdd_core_l);
		vc_regs.vc_val_bypass = reg_read(&omap5430es1_prm_vc_val_bypass);
		vc_regs.vc_mpu_errst = reg_read(&omap5430es1_prm_vc_mpu_errst);
		vc_regs.vc_mm_errst = reg_read(&omap5430es1_prm_vc_mm_errst);
		vc_regs.vc_core_errst = reg_read(&omap5430es1_prm_vc_core_errst);
		vc_regs.vc_bypass_errst = reg_read(&omap5430es1_prm_vc_bypass_errst);
		vc_regs.vc_cfg_i2c_mode = reg_read(&omap5430es1_prm_vc_cfg_i2c_mode);
		vc_regs.vc_cfg_i2c_clk = reg_read(&omap5430es1_prm_vc_cfg_i2c_clk);
	} else {
		vc_regs.vc_smps_mpu_config = reg_read(&omap5430_prm_vc_smps_mpu_config);
		vc_regs.vc_smps_mm_config = reg_read(&omap5430_prm_vc_smps_mm_config);
		vc_regs.vc_smps_core_config =
			reg_read(&omap5430_prm_vc_smps_core_config);
		vc_regs.vc_val_cmd_vdd_mpu_l =
			reg_read(&omap5430_prm_vc_val_cmd_vdd_mpu_l);
		vc_regs.vc_val_cmd_vdd_mm_l =
			reg_read(&omap5430_prm_vc_val_cmd_vdd_mm_l);
		vc_regs.vc_val_cmd_vdd_core_l =
			reg_read(&omap5430_prm_vc_val_cmd_vdd_core_l);
		vc_regs.vc_val_bypass = reg_read(&omap5430_prm_vc_val_bypass);
		vc_regs.vc_mpu_errst = reg_read(&omap5430_prm_vc_mpu_errst);
		vc_regs.vc_mm_errst = reg_read(&omap5430_prm_vc_mm_errst);
		vc_regs.vc_core_errst = reg_read(&omap5430_prm_vc_core_errst);
		vc_regs.vc_bypass_errst = reg_read(&omap5430_prm_vc_bypass_errst);
		vc_regs.vc_cfg_i2c_mode = reg_read(&omap5430_prm_vc_cfg_i2c_mode);
		vc_regs.vc_cfg_i2c_clk = reg_read(&omap5430_prm_vc_cfg_i2c_clk);
	}

	ret = vc54xx_config_show(stream, &vc_regs);
	if (ret != 0)
		return ret;

	ret = vp54xx_config_show(stream);
	if (ret != 0)
		return ret;

	ret = sr54xx_module_config_show(stream);
	if (ret != 0)
		return ret;

	return sr54xx_convergence_status_show(stream);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr54xx_convergence_status_show
 * @BRIEF		analyze Smart-Reflex convergence status
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 * @param[in]		stream: output file (NULL: no output (silent))
 * @DESCRIPTION		analyze Smart-Reflex convergence status
 *//*------------------------------------------------------------------------ */
int sr54xx_convergence_status_show(FILE *stream)
{
	sr_status_registers sr_status_regs[3];

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	/* Read [SR-VP]_MPU registers (if accessible) */
	if (module_is_accessible(MOD_SMARTREFLEX_MPU) != 1) {
		sr_status_regs[0].enabled = 0;
	} else {
		sr_status_regs[0].enabled = 1;
		sr_status_regs[0].srconfig =
			reg_read(&omap5430_smartreflex_mpu_srconfig);
		sr_status_regs[0].senerror =
			reg_read(&omap5430_smartreflex_mpu_senerror_reg);
		sr_status_regs[0].errconfig =
			reg_read(&omap5430_smartreflex_mpu_errconfig);
		sr_status_regs[0].vp_config = (cpu_revision_get() == REV_ES1_0) ?
				reg_read(&omap5430es1_prm_vp_mpu_config):
				reg_read(&omap5430_prm_vp_mpu_config);
	}

	/* Read [SR-VP]_MM registers (if accessible) */
	if (module_is_accessible(MOD_SMARTREFLEX_MM) != 1) {
		sr_status_regs[1].enabled = 0;
	} else {
		sr_status_regs[1].enabled = 1;
		sr_status_regs[1].srconfig =
			reg_read(&omap5430_smartreflex_mm_srconfig);
		sr_status_regs[1].senerror =
			reg_read(&omap5430_smartreflex_mm_senerror_reg);
		sr_status_regs[1].errconfig =
			reg_read(&omap5430_smartreflex_mm_errconfig);
		sr_status_regs[0].vp_config = (cpu_revision_get() == REV_ES1_0) ?
				reg_read(&omap5430es1_prm_vp_mm_config):
				reg_read(&omap5430_prm_vp_mm_config);
	}

	/* Read [SR-VP]_CORE registers (if accessible) */
	if (module_is_accessible(MOD_SMARTREFLEX_CORE) != 1) {
		sr_status_regs[2].enabled = 0;
	} else {
		sr_status_regs[2].enabled = 1;
		sr_status_regs[2].srconfig =
			reg_read(&omap5430_smartreflex_core_srconfig);
		sr_status_regs[2].senerror =
			reg_read(&omap5430_smartreflex_core_senerror_reg);
		sr_status_regs[2].errconfig =
			reg_read(&omap5430_smartreflex_core_errconfig);
		sr_status_regs[0].vp_config = (cpu_revision_get() == REV_ES1_0) ?
				reg_read(&omap5430es1_prm_vp_core_config):
				reg_read(&omap5430_prm_vp_core_config);
	}

	if ((sr_status_regs[0].enabled == 0) &&
		(sr_status_regs[1].enabled == 0) &&
		(sr_status_regs[2].enabled == 0)) {
		fprintf(stream, "All Smart-Reflex Modules disabled.\n");
		return 0;
	}

	return sr_convergence_status_show(stream, sr_status_regs);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr54xx_s2id
 * @BRIEF		convert string to valid SR ID
 * @RETURNS		SR54XX_SMARTREFLEX_MPU if s == "mpu"
 *			SR54XX_SMARTREFLEX_MM if s == "mm"
 *			SR54XX_SMARTREFLEX_CORE if s == "core"
 *			SR54XX_MODS_COUNT otherwise
 * @param[in]		s: string
 * @DESCRIPTION		convert string to valid SR ID
 *//*------------------------------------------------------------------------ */
sr54xx_mod_id sr54xx_s2id(char *s)
{
	if (strcmp(s, "mpu") == 0)
		return SR54XX_SMARTREFLEX_MPU;
	else if (strcmp(s, "mm") == 0)
		return SR54XX_SMARTREFLEX_MM;
	else if (strcmp(s, "core") == 0)
		return SR54XX_SMARTREFLEX_CORE;
	else
		return SR54XX_MODS_COUNT;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr54xx_vddid2srid
 * @BRIEF		convert a VDD ID into corresponding SR ID.
 * @RETURNS		corresponding SR ID
 *			SR54XX_MODS_COUNT in case of error.
 * @param[in]		vdd_id: voltage domain ID
 * @DESCRIPTION		convert a VDD ID into corresponding SR ID.
 *//*------------------------------------------------------------------------ */
sr54xx_mod_id sr54xx_vddid2srid(voltdm54xx_id vdd_id)
{

	CHECK_ARG_LESS_THAN(vdd_id, VDD54XX_ID_MAX, SR54XX_MODS_COUNT);

	static const sr54xx_mod_id vddid2srid_table[VDD54XX_ID_MAX] = {
		SR54XX_MODS_COUNT,
		SR54XX_SMARTREFLEX_MPU,
		SR54XX_SMARTREFLEX_MM,
		SR54XX_SMARTREFLEX_CORE};

	return vddid2srid_table[vdd_id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr54xx_avs_enable
 * @BRIEF		control SR AVS via sysfs entry.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in]		id: SR ID
 * @param[in]		enable: =1 to enable, =0 to disable SR AVS
 * @DESCRIPTION		control SR AVS via sysfs entry.
 *//*------------------------------------------------------------------------ */
int sr54xx_avs_enable(sr54xx_mod_id id, unsigned short enable)
{
	int ret;
	FILE *fp;
	static const char filename[SR54XX_MODS_COUNT][72] = {
		"/sys/kernel/debug/smartreflex/smartreflex_mpu/autocomp",
		"/sys/kernel/debug/smartreflex/smartreflex_mm/autocomp",
		"/sys/kernel/debug/smartreflex/smartreflex_core/autocomp"};

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(id, SR54XX_MODS_COUNT, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(enable, 2, OMAPCONF_ERR_ARG);

	/* Open file */
	fp = fopen(filename[id], "w");
	if (fp == NULL) {
		fprintf(stderr,
			"omapconf (%s()): could not open %s! Is debugfs mounted???\n\n",
			__func__, filename[id]);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	if (enable)
		ret = fwrite("1", sizeof(char), 1, fp);
	else
		ret = fwrite("0", sizeof(char), 1, fp);
	if (ret != 1) {
		fprintf(stderr, "omapconf (%s()): could not write into %s!\n\n",
			__func__, filename[id]);
		ret = OMAPCONF_ERR_UNEXPECTED;
	} else {
		ret = 0;
	}

	/* Close file */
	if (fp != NULL)
		fclose(fp);

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr54xx_avs_is_enabled
 * @BRIEF		return SR AVS current mode (enabled/disabled).
 * @RETURNS		0 if disabled or in case of error.
 *			1 if enabled.
 * @param[in]		id: SR ID
 * @DESCRIPTION		return SR AVS current mode (enabled/disabled).
 *//*------------------------------------------------------------------------ */
unsigned short sr54xx_avs_is_enabled(sr54xx_mod_id id)
{
	int ret;
	FILE *fp;
	char s[2];
	unsigned short enable;
	static const char filename[SR54XX_MODS_COUNT][72] = {
		"/sys/kernel/debug/smartreflex/smartreflex_mpu/autocomp",
		"/sys/kernel/debug/smartreflex/smartreflex_mm/autocomp",
		"/sys/kernel/debug/smartreflex/smartreflex_core/autocomp"};

	CHECK_CPU(54xx, 0);
	CHECK_ARG_LESS_THAN(id, SR54XX_MODS_COUNT, 0);

	/* Open file */
	fp = fopen(filename[id], "r");
	if (fp == NULL) {
		fprintf(stderr, "omapconf (%s()): could not open %s! Is debugfs mounted???\n\n",
			__func__, filename[id]);
		return 0;
	}

	ret = fread(s, sizeof(char), 1, fp);
	if (ret != 1) {
		fprintf(stderr,
			"omapconf (%s()): could not read %s!\n\n",
			__func__, filename[id]);
		enable = 0;
	} else {
		enable = atoi(s);
	}

	/* Close file */
	if (fp != NULL)
		fclose(fp);

	return enable;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sr54xx_main
 * @BRIEF		main entry point for Smart-Reflex AVS functions
 *			### DEPRECATED, DO NOT USE ANYMORE ###
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		main entry point for Smart-Reflex AVS functions
 *			argv[0] = function ("dump", "cfg")
 *			argv[1] = SR ID ("mpu", "mm", "core", "all")
 *			argv[1] may be omitted (then "all" assumed)
 *//*------------------------------------------------------------------------ */
int sr54xx_main(int argc, char *argv[])
{
	int ret = 0;
	sr54xx_mod_id id;

	if (argc == 1) {
		id = SR54XX_MODS_COUNT;
	} else if (argc != 2) {
		goto sr54xx_main_err_arg;
	} else {
		id = sr54xx_s2id(argv[1]);
		if (id == SR54XX_MODS_COUNT)
			goto sr54xx_main_err_arg;
	}

	if (strcmp(argv[0], "dump") == 0) {
		if (id == SR54XX_MODS_COUNT) {
			ret = sr54xx_dump(stdout, SR54XX_SMARTREFLEX_MPU);
			if (ret != 0)
				goto sr54xx_main_end;
			ret = sr54xx_dump(stdout, SR54XX_SMARTREFLEX_MM);
			if (ret != 0)
				goto sr54xx_main_end;
			ret = sr54xx_dump(stdout, SR54XX_SMARTREFLEX_CORE);
		} else {
			ret = sr54xx_dump(stdout, id);
		}
	} else if (strcmp(argv[0], "cfg") == 0) {
		ret = sr54xx_config_show(stdout);
		goto sr54xx_main_end;
	} else if (strcmp(argv[0], "status") == 0) {
		ret = sr54xx_convergence_status_show(stdout);
		goto sr54xx_main_end;
	} else {
		goto sr54xx_main_err_arg;
	}
	goto sr54xx_main_end;

sr54xx_main_err_arg:
	help(HELP_SR);
	ret = 0;

sr54xx_main_end:
	return ret;
}
