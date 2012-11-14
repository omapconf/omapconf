/*
 *
 * @Component			OMAPCONF
 * @Filename			lib54xx.c
 * @Description			OMAPCONF OMAP5 General Purpose Library
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


#include <lib54xx.h>
#include <lib.h>
#include <string.h>
#include <stdlib.h>
#include <module54xx.h>
#include <cpuinfo.h>
#include <cpufreq.h>
#include <autoadjust_table.h>
#include <prm54xx.h>
#include <cm54xx.h>
#include <sr54xx.h>
#include <ctrlmod54xx.h>
#include <emif54xx.h>
#include <revision.h>
#include <time.h>
#include <temp54xx.h>
#include <temperature.h>
#include <unistd.h>
#include <pmic.h>
#include <lib_android.h>
#include <opp.h>
#include <voltdm.h>
#include <genlist.h>
#include <temperature.h>


/* #define LIB54XX_DEBUG */
#ifdef LIB54XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		lib54xx_pwst_show
 * @BRIEF		show OMAP5 power status
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in,out]	stream: output file stream (!= NULL)
 * @DESCRIPTION		show OMAP5 power status
 *//*------------------------------------------------------------------------ */
int lib54xx_pwst_show(FILE *stream)
{
	mod_idle_status idlest;
	mod_standby_status stbyst;
	char s_idlest[MODULE_MODES_MAX_NAME_LENGTH];
	char s_stbyst[MODULE_MODES_MAX_NAME_LENGTH];
	char s_mod_name[MODULE_MAX_NAME_LENGTH];
	pwrdm_state pwst, pwtgst;
	char s_pwst[PWRDM_STATE_MAX_NAME_LENGTH];
	char s_pwtgst[PWRDM_STATE_MAX_NAME_LENGTH];
	char s_pwrdm_name[PWRDM54XX_MAX_NAME_LENGTH];
	clkdm_status clkst;
	char s_clkst[CLKDM_STATUS_MAX_NAME_LENGTH];
	char s_clkdm_name[CLKDM54XX_MAX_NAME_LENGTH];
	double clk_rate;
	char s_clk_rate[12];
	opp54xx_id current_opp[VDD54XX_ID_MAX] = {
		OPP54XX_ID_MAX, OPP54XX_ID_MAX, OPP54XX_ID_MAX, OPP54XX_ID_MAX};
	char s_current_opp[VDD54XX_ID_MAX][OPP_MAX_NAME_LENGTH] = {
		"UNKNOWN",
		"UNKNOWN",
		"UNKNOWN",
		"UNKNOWN"};
	char s_voltdm_name[VOLTDM_MAX_NAME_LENGTH + 10];
	unsigned short first_mod, first_clkdm, first_pwrdm;
	mod54xx_id mod_id;
	clkdm54xx_id clkdm_id;
	pwrdm54xx_id pwrdm_id;
	voltdm54xx_id voltdm_id;
	double volt;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(stream, OMAPCONF_ERR_ARG);

	/* For each voltage domain, retrieve the current OPP */
	current_opp[VDD54XX_WKUP] = voltdm54xx_opp_get(VDD54XX_WKUP);
	if (current_opp[VDD54XX_WKUP] == OPP54XX_ID_MAX)
		fprintf(stderr, "Warning: %s OPP not detected!\n",
			voltdm54xx_name_get(VDD54XX_WKUP));
	current_opp[VDD54XX_MPU] = voltdm54xx_opp_get(VDD54XX_MPU);
	if (current_opp[VDD54XX_MPU] == OPP54XX_ID_MAX)
		fprintf(stderr, "Warning: %s OPP not detected!\n",
			voltdm54xx_name_get(VDD54XX_MPU));
	current_opp[VDD54XX_MM] = voltdm54xx_opp_get(VDD54XX_MM);
	if (current_opp[VDD54XX_MM] == OPP54XX_ID_MAX)
		fprintf(stderr, "Warning: %s OPP not detected!\n",
			voltdm54xx_name_get(VDD54XX_MM));
	current_opp[VDD54XX_CORE] = voltdm54xx_opp_get(VDD54XX_CORE);
	if (current_opp[VDD54XX_CORE] == OPP54XX_ID_MAX)
		fprintf(stderr, "Warning: %s OPP not detected!\n",
			voltdm54xx_name_get(VDD54XX_CORE));
	strcpy(s_current_opp[VDD54XX_WKUP],
		opp54xx_name_get(current_opp[VDD54XX_WKUP]));
	strcpy(s_current_opp[VDD54XX_MPU],
		opp54xx_name_get(current_opp[VDD54XX_MPU]));
	strcpy(s_current_opp[VDD54XX_MM],
		opp54xx_name_get(current_opp[VDD54XX_MM]));
	strcpy(s_current_opp[VDD54XX_CORE],
		opp54xx_name_get(current_opp[VDD54XX_CORE]));

	dprintf("%s():\n"
		" current_opp[WKUP] = %s\n"
		" current_opp[MPU] = %s\n"
		" current_opp[MM] = %s\n"
		" current_opp[CORE] = %s\n", __func__,
		s_current_opp[VDD54XX_WKUP],
		s_current_opp[VDD54XX_MPU],
		s_current_opp[VDD54XX_MM],
		s_current_opp[VDD54XX_CORE]);


	fprintf(stream, "|-----------------------------------------------------"
		"--------------------------------------------------------------"
		"--------------------------------------------|\n");
	fprintf(stream, "| OMAP5 Power Status                                  "
		"                                                              "
		"                                            |\n");
	fprintf(stream, "|-----------------------------------------------------"
		"--------------------------------------------------------------"
		"--------------------------------------------|\n");
	fprintf(stream, "| Voltage Domain                | Power Domain        "
		"         | Clock Domain          | Module Status              "
		"                                            |\n");
	fprintf(stream, "| Name              | OPP       | Name       | Curr.  "
		"| Target | Name       | Status   | Name                  "
		"| Rate (MHz) | Idle                 | Standby    |\n");
	/* For each domain, retrieve the clock & power domain status */
	for (voltdm_id = 0; voltdm_id < VDD54XX_ID_MAX; voltdm_id++) {
		fprintf(stream, "|---------------------------------------------"
			"------------------------------------------------------"
			"------------------------------------------------------"
			"------|\n");
		volt = voltdm54xx_voltage_get(voltdm_id);
		if (volt > 0)
			sprintf(s_voltdm_name, "%s (%.3lfV)",
				voltdm54xx_name_get(voltdm_id), volt);
		else
			strcpy(s_voltdm_name, voltdm54xx_name_get(voltdm_id));
		for (pwrdm_id = 0, first_pwrdm = 1; pwrdm_id < PWRDM54XX_ID_MAX;
			pwrdm_id++) {
			if (pwrdm54xx_voltdm_get(pwrdm_id) != voltdm_id)
				continue;

			switch (pwrdm_id) {
			case PWRDM54XX_MPUAON:
			case PWRDM54XX_MMAON:
			case PWRDM54XX_CUST_EFUSE:
				/* Ignore these power domains (and modules) */
				continue;

			default:
				*s_pwst = '\0';
				pwst = pwrdm54xx_state_get(pwrdm_id,
					PWRDM_STATE_CURRENT);
				if (pwst != PWRDM_STATE_MAX)
					pwrdm_state2string(s_pwst, pwst);
				*s_pwtgst = '\0';
				pwtgst = pwrdm54xx_state_get(pwrdm_id,
					PWRDM_STATE_TARGET);
				if (pwtgst != PWRDM_STATE_MAX)
					pwrdm_state2string(s_pwtgst, pwtgst);

				pwrdm_state2string(s_pwtgst, pwtgst);
				strcpy(s_pwrdm_name,
					pwrdm54xx_name_get(pwrdm_id));
			}

			for (clkdm_id = 0, first_clkdm = 1;
				clkdm_id < CLKDM54XX_NONE; clkdm_id++) {
				if ((clkdm_id == CLKDM54XX_L4_SEC) &&
					cpu_is_gp_device())
					continue;
				if (clkdm_id == CLKDM54XX_NONE)
					continue;
				if (clkdm54xx_pwrdm_get(clkdm_id) != pwrdm_id)
					continue;

				if ((!first_pwrdm) && (first_clkdm))
					fprintf(stream, "| %-17s | %-9s |------"
						"------------------------------"
						"------------------------------"
						"------------------------------"
						"------------------------------"
						"-|\n", "", "");
				*s_clkst = '\0';
				clkst = clkdm54xx_status_get(clkdm_id);
				if (clkst != CLKDM_STATUS_MAX)
					strcpy(s_clkst,
						clkdm_status_name_get(clkst));

				strcpy(s_clkdm_name,
					clkdm54xx_name_get(clkdm_id));

				/* For each module, retrieve status */
				for (mod_id = 0, first_mod = 1;
					mod_id < MOD54XX_ID_MAX; mod_id++) {
					if (mod54xx_clkdm_get(mod_id) !=
						clkdm_id)
						continue;

					*s_idlest = '\0';
					*s_stbyst = '\0';

					idlest = mod54xx_idle_status_get(
						mod_id);
					if (idlest != MOD_IDLE_STATUS_MAX)
						strcpy(s_idlest,
							mod_idle_status_name_get(
								idlest));
					else if (idlest != MOD_DISABLED) {
						stbyst = mod54xx_standby_status_get(
							mod_id);
						if (stbyst != MOD_STANDBY_STATUS_MAX)
							strcpy(s_stbyst,
								mod_standby_status_name_get(
								stbyst));
					}
					strcpy(s_mod_name,
						mod54xx_name_get(mod_id));
					clk_rate =
						mod54xx_clk_rate_get(mod_id, 0);
					if (clk_rate < 0.0)
						strcpy(s_clk_rate, "Error");
					else if (clk_rate < 1.0)
						snprintf(s_clk_rate, 12,
							"%lf", clk_rate);
					else
						snprintf(s_clk_rate, 12,
							"%.3lf", clk_rate);
					if ((first_mod) && (!first_clkdm))
						fprintf(stream, "| %-17s | %-9s"
							" | %-10s | %-6s | %-6s"
							" |--------------------"
							"----------------------"
							"----------------------"
							"----------------------"
							"----------|\n",
							"", "", "", "", "");
					fprintf(stream, "| %-17s | %-9s | %-10s"
						" | %-6s | %-6s | %-10s | %-8s "
						"| %-21s | %-10s | %-20s |"
						" %-10s |\n",
						s_voltdm_name,
						s_current_opp[voltdm_id],
						s_pwrdm_name,
						s_pwst,
						s_pwtgst,
						s_clkdm_name,
						s_clkst,
						s_mod_name,
						s_clk_rate,
						s_idlest,
						s_stbyst);
					if (first_mod) {
						*s_clkdm_name = '\0';
						*s_pwrdm_name = '\0';
						*s_voltdm_name = '\0';
						*s_current_opp[voltdm_id] =
							'\0';
						*s_pwst = '\0';
						*s_pwtgst = '\0';
						*s_clkst = '\0';
						first_mod = 0;
					}
				}
				first_clkdm = 0;
			}
			first_pwrdm = 0;
		}

	}
	fprintf(stream, "|-----------------------------------------------------"
		"--------------------------------------------------------------"
		"--------------------------------------------|\n\n");

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		lib54xx_voltage_set
 * @BRIEF		change voltage of a given voltage domain, switching
 *			CPUFreq governor to "userspace" & disabling smart-reflex
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		vdd_id: voltage domain ID
 * @param[in]		volt: new supply voltage (in volt)
 * @DESCRIPTION		change voltage of a given voltage domain, switching
 *			CPUFreq governor to "userspace" & disabling smart-reflex
 *//*------------------------------------------------------------------------ */
int lib54xx_voltage_set(voltdm54xx_id vdd_id, double volt)
{
	int ret, ret_cpufreq;
	char prev_gov[CPUFREQ_GOV_MAX_NAME_LENGTH];
	sr54xx_mod_id sr_id;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(vdd_id, VDD54XX_ID_MAX, OMAPCONF_ERR_ARG);

	/*
	 * Switch governor to 'userspace' otherwise voltage change will be
	 * overriden in case of OPP change.
	 */
	printf("Warning: switching CPUFreq governor to 'userspace', otherwise "
		"voltage change will be overriden...\n");
	ret_cpufreq = cpufreq_scaling_governor_set("userspace", prev_gov);
	if (ret_cpufreq < 0)
		printf("Warning: failed to switch governor. Voltage will be "
			"overriden in case of OPP change.\n");
	else
		printf("CPUFreq governor switched to 'userspace'.\n");
	/*
	 * Disable Smart-Reflex (if running) otherwise voltage change will be
	 * overriden.
	 */
	sr_id = sr54xx_vddid2srid(vdd_id);
	if (sr54xx_avs_is_enabled(sr_id)) {
		printf("Warning: %s Smart-Reflex AVS is enabled. "
			"Disabling it...\n", voltdm54xx_name_get(vdd_id));
		ret = sr54xx_avs_enable(sr_id, 0);
		if (ret == 0)
			printf("Smartreflex disabled.\n\n");
		else
			printf("Warning: Could not disable Smart-Reflex AVS. "
				"Voltage may be overriden.\n\n");
	} else {
		printf("Smartreflex disabled.\n\n");
	}

	ret = voltdm54xx_voltage_set(vdd_id,
		(unsigned long) (volt * 1000000));
	if (ret != 0) {
		fprintf(stderr, "Oups, could not change %s voltage to "
			"%.3lfV ... (%d)\n\n",
			voltdm54xx_name_get(vdd_id), volt, ret);
	} else {
		printf("%s supply voltage set to %1.3lfV (vsel = 0x%02X).\n\n",
			voltdm54xx_name_get(vdd_id), volt,
			smps_uvolt2vsel(vdd_id2smps_id(vdd_id),
				(unsigned long) (volt * 1000000)));
		printf("Warning:\n"
			"  - Do not re-enable %s smartreflex or new voltage "
			"will be overriden.\n"
			"  - Do not change OPP (or use CPUFREQ) or new voltage"
			" will be overriden.\n\n", voltdm54xx_name_get(vdd_id));
	}

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		lib54xx_vminsearch
 * @BRIEF		search minimum supply voltage by decreasing voltage
 *			step by step  until it breaks.
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number (must be == 3)
 * @param[in]		argv: shell input argument(s)
 *				argv[0]="voltage domain" ("mpu", "mm", "core")
 *				argv[1]="initial voltage" (in volts)
 *				argv[2]="delay" between steps (in milliseconds)
 * @DESCRIPTION		search minimum supply voltage by decreasing voltage
 *			step by step  until it breaks.
 *			NB: switch CPUFreq governor to "userspace" &
 *			disable smart-reflex
 *//*------------------------------------------------------------------------ */
int lib54xx_vminsearch(int argc, char *argv[])
{
	long uv;
	double v, prev_v;
	int ret, temp;
	unsigned long vstep;
	unsigned char vsel;
	voltdm54xx_id vdd_id;
	sr54xx_mod_id sr_id;
	unsigned int ms;
	char prev_gov[CPUFREQ_GOV_MAX_NAME_LENGTH];

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	/* Retrieve arguments */
	if (argc != 3)
		goto lib54xx_vminsearch_arg_err;
	if (strcmp(argv[0], "mpu") == 0)
		vdd_id = VDD54XX_MPU;
	else if (strcmp(argv[0], "mm") == 0)
		vdd_id = VDD54XX_MM;
	else if (strcmp(argv[0], "core") == 0)
		vdd_id = VDD54XX_CORE;
	else
		goto lib54xx_vminsearch_arg_err;
	ret = sscanf(argv[1], "%lf", &v);
	if (ret != 1)
		goto lib54xx_vminsearch_arg_err;
	ret = sscanf(argv[2], "%d", &ms);
	if (ret != 1)
		goto lib54xx_vminsearch_arg_err;
	if (ms <= 0)
		goto lib54xx_vminsearch_arg_err;

	/*
	 * Switch governor to 'userspace' otherwise voltage change will be
	 * overriden in case of OPP change.
	 */
	printf("Warning: switching CPUFreq governor to 'userspace', otherwise "
		"voltage change will be overriden...\n");
	ret = cpufreq_scaling_governor_set("userspace", prev_gov);
	if (ret < 0)
		printf("Warning: failed to switch governor. Voltage will be "
			"overriden in case of OPP change.\n");
	else
		printf("CPUFreq governor switched to 'userspace'.\n");

	/*
	 * Disable Smart-Reflex (if running) otherwise voltage change will be
	 * overriden.
	 */
	sr_id = sr54xx_vddid2srid(vdd_id);
	if (sr54xx_avs_is_enabled(sr_id)) {
		printf("Warning: %s Smart-Reflex AVS is enabled. "
			"Disabling it...\n", voltdm54xx_name_get(vdd_id));
		ret = sr54xx_avs_enable(sr_id, 0);
		if (ret == 0)
			printf("Smartreflex disabled.\n\n");
		else
			printf("Warning: Could not disable Smart-Reflex AVS. "
				"Voltage may be overriden.\n\n");
	} else {
		printf("Smartreflex disabled.\n\n");
	}

	/* Show current OPP for reference */
	printf("Current OPP configuration for reference:\n\n");
	opp_show(stdout);

	/* Retrieving SMPS voltage step */
	vstep = smps_step_get(vdd_id2smps_id(vdd_id));
	dprintf("%s(): vstep=%luuV\n", __func__, vstep);

	printf("Vmin SEARCH on %s domain scaling voltage down from %1.3lfV in "
		"steps of %lumV, waiting %dms between each step.\n",
		voltdm54xx_name_get(vdd_id), v, vstep / 1000, ms);
	printf("LAST voltage displayed with OK status before crash "
		"will be the Vmin for %s domain.\n\n",
		voltdm54xx_name_get(vdd_id));
	printf("NB:\n  - Make sure your load generator application is "
		"running in background during the whole procedure.\n");
	printf("  - PLATFORM MUST BE REBOOTED AFTER USE "
		"(NO POSSIBLE RECOVERY).\n\n");

	/* Rounding requested initial voltage */
	vsel = smps_uvolt2vsel(vdd_id2smps_id(vdd_id),
		(unsigned long) (v * 1000000));
	prev_v = v;
	v = (double) smps_vsel2uvolt(vdd_id2smps_id(vdd_id), vsel);
	v = v / 1000000;
	if (v != prev_v)
		printf("Note: rounded up initial voltage to %.3lfV.\n\n", v);

	/* Decreasing voltage step by step until it breaks */
	printf("Starting Vmin SEARCH...\n");

	for (uv = (unsigned long) (v * 1000000); uv >= 0; uv = uv - vstep) {
		/* Get vsel corresponding to target voltage */
		vsel = smps_uvolt2vsel(vdd_id2smps_id(vdd_id), uv);
		temp = temp54xx_get(voltdm2sensor_id(vdd_id));
		if (temp != TEMP_ABSOLUTE_ZERO)
			printf("Trying %1.3lfV (SMPS code: 0x%02X, temperature: %dC/%dF)...",
				smps_vsel2volt(vdd_id2smps_id(vdd_id), vsel),
				vsel, temp, celcius2fahrenheit(temp));
		else
			printf("Trying %1.3lfV (SMPS code: 0x%02X, temperature: N/A)...",
				smps_vsel2volt(vdd_id2smps_id(vdd_id), vsel),
				vsel);
		fflush(stdout);
		ret = smps_voltage_set(vdd_id2smps_id(vdd_id), uv);
		if (ret != 0) {
			fprintf(stderr, "Error: could not set %s voltage!\n\n",
				voltdm54xx_name_get(vdd_id));
			return ret;
		}
		usleep(1000 * ms);
		printf("OK!\n");
	}
	fprintf(stderr, "Shouldn't have reached this point... "
		"please check voltage is really scaling down.\n\n");
	return 0;

lib54xx_vminsearch_arg_err:
	return err_arg_msg_show(HELP_VOLT);
	return OMAPCONF_ERR_ARG;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		lib54xx_export
 * @BRIEF		export OMAP registers in XML format into file
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG otherwise
 * @param[in]		file: export file name (default if == NULL)
 * @DESCRIPTION		export OMAP registers in XML format into file. If no
 *			file name provided, generate one using current date.
 *//*------------------------------------------------------------------------ */
int lib54xx_export(char *file)
{
	FILE *fp = NULL;
	char default_file[64];
	char export_date[32];
	char version[RELEASE_VERSION_MAX_LENGTH];
	char type[RELEASE_TYPE_MAX_LENGTH];
	char date[RELEASE_DATE_MAX_LENGTH];
	char kversion[KERNEL_VERSION_MAX_LENGTH];
	char kauthor[KERNEL_AUTHOR_MAX_LENGTH];
	char ktoolchain[KERNEL_TOOLCHAIN_MAX_LENGTH];
	char ktype[KERNEL_TYPE_MAX_LENGTH];
	char kdate[KERNEL_DATE_MAX_LENGTH];
	char dev_name[CPU_NAME_MAX_LENGTH];
	char dev_rev[CPU_REVISION_MAX_NAME_LENGTH];
	char dev_type[CPU_DEVICE_TYPE_MAX_NAME_LENGTH];
	char dev_si_type[CPU_SI_TYPE_MAX_NAME_LENGTH];
	unsigned int dev_max_speed;
	unsigned int i;
	time_t t;
	struct tm *tmp;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);

	/* Get date */
	t = time(NULL);
	tmp = localtime(&t);

	/* Open export file */
	if (file == NULL) {
		/* No file name given, generate default one */
		strcpy(default_file,
			"omapconf_export_Mon_Jan_01_00_00_00_CET_1970.xml");
		if (tmp != NULL)
			strftime(default_file, 64,
				"omapconf_export_%a_%b_%d_%H_%M_%S_%Z_%Y.xml",
				tmp);
		fp = fopen(default_file, "w");
	} else {
		fp = fopen(file, "w");
	}
	if (fp == NULL) {
		printf("Oups... could not create %s!!!\n\n", file);
		return 0;
	}

	/* XML header */
	fprintf(fp, "<?xml version=\"1.0\"?>\n\n");

	strcpy(export_date, "Mon Jan 01 00:00:00 CET 1970");
	if (tmp != NULL)
		strftime(export_date, sizeof(export_date),
			"%a %b %d %H:%M:%S %Z %Y", tmp);

	fprintf(fp,
		"<omapconf_export export_date=\"%s\" omapconf_version=\"%u.%u\" omapconf_builddate=\"%s\">\n",
		export_date, OMAPCONF_REV_MAJOR, OMAPCONF_REV_MINOR, builddate);

	release_details_get(version, type, date);
	if (os_is_android())
		fprintf(fp,
			"  <buildinfo os=\"android\" version=\"%s\" type=\"%s\" date=\"%s\">\n",
			version, type, date);
	else
		fprintf(fp, "  <buildinfo os=\"linux\" version=\"%s\">\n",
			version);

	kernel_details_get(kversion, kauthor, ktoolchain, ktype, kdate);
	fprintf(fp,
		"    <kernel version=\"%s\" author=\"%s\" toolchain=\"%s\" type=\"%s\" date=\"%s\">\n",
		kversion, kauthor, ktoolchain, ktype, kdate);

	cpu_gets(dev_name);
	cpu_revision_gets(dev_rev);
	cpu_device_type_gets(dev_type);
	cpu_silicon_type_gets(dev_si_type);
	dev_max_speed = cpu_silicon_max_speed_get();
	fprintf(fp,
		"      <device name=\"%s\" revision=\"%s\" type=\"%s\" silicon_type=\"%s\" max_speed_mhz=\"%u\">\n",
		dev_name, dev_rev, dev_type, dev_si_type, dev_max_speed);

	/* Export PRM registers */
	fprintf(fp, "        <module name=\"PRM\">\n");
	for (i = 0; i < PRM54XX_MODS_COUNT; i++)
		prm54xx_export(fp, (prm54xx_mod_id) i);
	fprintf(fp, "        </module>\n");

	/* Export CM registers */
	fprintf(fp, "        <module name=\"CM\">\n");
	for (i = 0; i < CM54XX_MODS_COUNT; i++)
		cm54xx_export(fp, (cm54xx_mod_id) i);
	fprintf(fp, "        </module>\n");

	/* Export Smart-Reflex registers */
	fprintf(fp, "        <module name=\"SR\">\n");
	sr54xx_export(fp, SR54XX_SMARTREFLEX_MPU);
	sr54xx_export(fp, SR54XX_SMARTREFLEX_MM);
	sr54xx_export(fp, SR54XX_SMARTREFLEX_CORE);
	fprintf(fp, "        </module>\n");

	/* Export CONTROL MODULE registers */
	fprintf(fp, "        <module name=\"CONTROL MODULE\">\n");
	ctrlmod54xx_export(fp, CTRLMOD54XX_CTRL_MODULE_CORE);
	ctrlmod54xx_export(fp, CTRLMOD54XX_CTRL_MODULE_CORE_PAD);
	ctrlmod54xx_export(fp, CTRLMOD54XX_CTRL_MODULE_WKUP);
	ctrlmod54xx_export(fp, CTRLMOD54XX_CTRL_MODULE_WKUP_PAD);
	fprintf(fp, "        </module>\n");

	/* Export EMIF registers */
	fprintf(fp, "        <module name=\"EMIF\">\n");
	emif54xx_export(fp, EMIF54XX_EMIF1);
	emif54xx_export(fp, EMIF54XX_EMIF2);
	fprintf(fp, "        </module>\n");

	fprintf(fp, "      </device>\n");
	fprintf(fp, "    </kernel>\n");
	fprintf(fp, "  </build>\n");
	fprintf(fp, "</omapconf_export>");

	/* Close file */
	if (fp != NULL)
		fclose(fp);

	if (file == NULL)
		printf("Registers successfully exported in \"%s\" file.\n\n",
			default_file);
	else
		printf("Registers successfully exported in \"%s\" file.\n\n",
			file);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		lib54xx_import
 * @BRIEF		import OMAP registers from XML file, generated with
 *			lib54xx_export().
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in,out]	file: XML file name
 * @DESCRIPTION		import OMAP registers from XML file, generated with
 *			lib54xx_export().
 *//*------------------------------------------------------------------------ */
int lib54xx_import(char *file)
{
	unsigned int i;
	FILE *fp = NULL;
	char line[256];
	char dummy[256];
	int ret;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(file, OMAPCONF_ERR_ARG);

	/* Open export file */
	fp = fopen(file, "r");
	if (fp == NULL) {
		printf("Oups... could not open \"%s\" file!?\n\n", file);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	/* Verify it's a XML file */
	if (fgets(line, sizeof(line), fp) == NULL) {
		printf("Oups, empty \"%s\" file?! :-(\n\n",
			file);
		ret = OMAPCONF_ERR_UNEXPECTED;
		goto lib54xx_import_end;
	}
	if (strstr(line, "<?xml version=\"1.0\"?>") == NULL) {
		printf("Oups, XML header not found in \"%s\" file?! :-(\n\n",
			file);
		ret = OMAPCONF_ERR_UNEXPECTED;
		goto lib54xx_import_end;
	}

	/* Verify it was generated from OMAPCONF */
	fgets(line, sizeof(line), fp); /* Jump empty line */
	fgets(line, sizeof(line), fp);
	if (sscanf(line, "<omapconf_export %s>", dummy) != 1) {
		printf("Oups, OMAPCONF header not found in \"%s\" file?! "
			":-(\n\n", file);
		ret = OMAPCONF_ERR_UNEXPECTED;
		goto lib54xx_import_end;
	}


	/* Import PRM registers */
	for (i = 0; i < PRM54XX_MODS_COUNT; i++) {
		ret = prm54xx_import(fp, (prm54xx_mod_id) i);
		if (ret != 0) {
			ret = OMAPCONF_ERR_UNEXPECTED;
			goto lib54xx_import_end;
		}
	}

	/* Import CM registers */
	for (i = 0; i < CM54XX_MODS_COUNT; i++) {
		ret = cm54xx_import(fp, (cm54xx_mod_id) i);
		if (ret != 0) {
			ret = OMAPCONF_ERR_UNEXPECTED;
			goto lib54xx_import_end;
		}
	}

	/* Import Smart-Reflex registers */
	for (i = 0; i < SR54XX_MODS_COUNT; i++) {
		ret = sr54xx_import(fp, (sr54xx_mod_id) i);
		if (ret != 0) {
			ret = OMAPCONF_ERR_UNEXPECTED;
			goto lib54xx_import_end;
		}
	}

	/* Import CONTROL MODULE registers */
	for (i = 0; i < CTRLMOD54XX_MODS_COUNT; i++) {
		ret = ctrlmod54xx_import(fp, (ctrlmod54xx_mod_id) i);
		if (ret != 0) {
			ret = OMAPCONF_ERR_UNEXPECTED;
			goto lib54xx_import_end;
		}
	}


lib54xx_import_end:
	/* Close file */
	if (fp != NULL)
		fclose(fp);
	return ret;
}
