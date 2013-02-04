/*
 *
 * @Component			OMAPCONF
 * @Filename			main44xx.c
 * @Description			OMAPCONF OMAP4 Main file
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


#include <string.h>
#include <lib.h>
#include <help.h>
#include <lib44xx.h>
#include <pmic.h>
#include <cpuinfo.h>
#include <module44xx.h>
#include <voltdm44xx.h>
#include <dpll44xx.h>
#include <mpu44xx.h>
#include <prcm44xx.h>
#include <mpuss44xx.h>
#include <wkdep44xx.h>
#include <core44xx.h>
#include <per44xx.h>
#include <dsp44xx.h>
#include <dss44xx.h>
#include <cam44xx.h>
#include <gfx44xx.h>
#include <ivahd44xx.h>
#include <abe44xx.h>
#include <wkup44xx.h>
#include <l3init44xx.h>
#include <alwon44xx.h>
#include <emu44xx.h>
#include <abb44xx.h>
#include <temperature.h>
#include <emif44xx.h>
#include <power_trace44xx.h>
#include <twl603x.h>
#include <twl6040.h>
#include <display44xx.h>
#include <dep44xx.h>
#include <ctt44xx.h>
#include <pct44xx.h>
#include <audit44xx.h>
#include <hwobs44xx.h>
#include <camera44xx.h>
#include <smartreflex44xx.h>
#include <wkdep44xx.h>
#include <timestamp_32k.h>
#include <signal.h>
#include <sci_swcapture.h>
#include <stdlib.h>
#include <counters44xx.h>
#include <opp.h>


/* #define DEBUG */
#ifdef DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main44xx_init
 * @BRIEF		initialize regtables
 * @DESCRIPTION		initialize regtables
 *//*------------------------------------------------------------------------ */
void main44xx_init(void)
{
	mod44xx_init_info_table();
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main44xx_dump
 * @BRIEF		dump  of selected item provided in string argv
 *			(formated in table).
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		dump  of selected item provided in string argv
 *			(formated in table).
 *//*------------------------------------------------------------------------ */
static int main44xx_dump(int argc, char *argv[])
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	if (argc == 0)
		return err_arg_missing_msg_show(HELP_CATEGORY_MAX);

	if (strcmp(argv[0], "prcm") == 0) {
		if (argc == 1) {
			char s[] = "all";
			return prcm44xx_dump(s);
		} else if (argc == 2) {
			return prcm44xx_dump(argv[1]);
		} else {
			return err_arg_msg_show(HELP_PRCM);
		}
	} else if (strcmp(argv[0], "dpll") == 0) {
		if (argc == 1)
			return dpll44xx_dump();
		else
			return err_arg_too_many_msg_show(HELP_DPLL);
	} else if (strcmp(argv[0], "abe") == 0) {
		if (argc == 1)
			return abe44xx_dump();
		else
			return err_arg_too_many_msg_show(HELP_ABE);
	} else if (strcmp(argv[0], "emif") == 0) {
		if (argc == 1)
			return emif44xx_dump();
		else
			return err_arg_too_many_msg_show(HELP_EMIF);
	} else if (strcmp(argv[0], "camera") == 0) {
		if (argc == 1)
			return err_arg_missing_msg_show(HELP_CAMERA);
		else if (argc == 2)
			return camera44xx_dump(argv[1]);
		else
			return err_arg_too_many_msg_show(HELP_CAMERA);
	} else if (strcmp(argv[0], "display") == 0) {
		if (argc == 1)
			return err_arg_missing_msg_show(HELP_DISPLAY);
		else if (argc == 2)
			return display44xx_dump(argv[1]);
		else
			return err_arg_too_many_msg_show(HELP_DISPLAY);
	} else if (strcmp(argv[0], "sr") == 0) {
		if (argc == 1)
			return sr44xx_dump();
		else
			return err_arg_too_many_msg_show(HELP_AVS);
	} else if (strcmp(argv[0], "mpuss") == 0) {
		if (argc == 1) {
			return err_arg_missing_msg_show(HELP_MPUSS);
		} else if (argc == 2) {
			if (strcmp(argv[1], "scu") == 0)
				return mpuss44xx_scu_dump();
			else if (strcmp(argv[1], "gic") == 0)
				return mpuss44xx_gic_dump();
			else if (strcmp(argv[1], "l2c") == 0)
				return mpuss44xx_pl310_dump();
			else if (strcmp(argv[1], "wkg") == 0)
				return mpuss44xx_wkg_dump();
			else if (strcmp(argv[1], "scm") == 0)
				return mpuss44xx_scm_dump();
			else
				return err_arg_msg_show(HELP_MPUSS);
		} else {
			return err_arg_too_many_msg_show(HELP_MPUSS);
		}
	} else if (strcmp(argv[0], "audioic") == 0) {
		if (argc == 1)
			return twl6040_dumpregs();
		else
			return err_arg_too_many_msg_show(HELP_AUDIOIC);
	} else if (strcmp(argv[0], "pmic") == 0) {
		if (argc == 1)
			return twl603x_dumpregs(stdout);
		else
			return err_arg_too_many_msg_show(HELP_PMIC);
	} else {
		return err_unknown_argument_msg_show(argv[0]);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main44xx_read
 * @BRIEF		read selected item provided in string argv.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		read selected item provided in string argv.
 *//*------------------------------------------------------------------------ */
static int main44xx_read(int argc, char *argv[])
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (strcmp(argv[0], "audioic") == 0) {
		if (argc < 2)
			return err_arg_missing_msg_show(HELP_CATEGORY_MAX);
		else if (argc == 2)
			return twl6040_readreg(uppercase(argv[1]));
		else
			return err_arg_too_many_msg_show(HELP_CATEGORY_MAX);
	} else {
		return err_unknown_argument_msg_show(argv[0]);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main44xx_write
 * @BRIEF		write selected item provided in string argv.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		write selected item provided in string argv.
 *//*------------------------------------------------------------------------ */
static int main44xx_write(int argc, char *argv[])
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (strcmp(argv[0], "audioic") == 0) {
		if (argc < 3) {
			return err_arg_missing_msg_show(HELP_CATEGORY_MAX);
		} else if (argc == 3) {
			return twl6040_writereg(
				uppercase(argv[1]), uppercase(argv[2]));
		} else {
			return err_arg_too_many_msg_show(HELP_CATEGORY_MAX);
		}
	} else {
		return err_unknown_argument_msg_show(argv[0]);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main44xx_clear
 * @BRIEF		clear selected item provided in string argv.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		clear selected item provided in string argv.
 *//*------------------------------------------------------------------------ */
static int main44xx_clear(int argc, char *argv[])
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (strcmp(argv[0], "prcm") == 0) {
		if (argc < 3) {
			return err_arg_missing_msg_show(HELP_PRCM);
		} else if  (strcmp(argv[1], "statdep") == 0) {
			if (argc == 3)
				return statdep44xx_main_set(argv[2], NULL, 0);
			else if (argc == 4)
				return statdep44xx_main_set(
					argv[2], argv[3], 0);
			else
				return err_arg_too_many_msg_show(HELP_PRCM);
		} else {
			return err_arg_msg_show(HELP_PRCM);
		}
	} else {
		return err_unknown_argument_msg_show(argv[0]);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main44xx_set
 * @BRIEF		set selected item provided in string argv.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		set selected item provided in string argv.
 *//*------------------------------------------------------------------------ */
static int main44xx_set(int argc, char *argv[])
{
	voltdm44xx_id vdd_id;
	char voltdm_name[VOLTDM44XX_MAX_NAME_LENGTH];
	double v;
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);


	if (strcmp(argv[0], "prcm") == 0) {
		if (argc < 3) {
			return err_arg_missing_msg_show(HELP_PRCM);
		} else if  (strcmp(argv[1], "statdep") == 0) {
			if (argc == 3)
				return statdep44xx_main_set(argv[2], NULL, 1);
			else if (argc == 4)
				return statdep44xx_main_set(
					argv[2], argv[3], 1);
			else
				return err_arg_too_many_msg_show(HELP_PRCM);
		} else {
			return err_arg_msg_show(HELP_PRCM);
		}
	} else if (strcmp(argv[0], "volt") == 0) {
		if (argc < 3) {
			return err_arg_missing_msg_show(HELP_VOLT);
		} else if (argc == 3) {
			vdd_id = voltdm44xx_s2id(argv[1]);
			if (vdd_id == OMAP4_VD_ID_MAX)
				return err_arg_msg_show(HELP_VOLT);

			ret = sscanf(argv[2], "%lf", &v);
			if (ret != 1)
				return err_arg_msg_show(HELP_VOLT);

			ret = sr44xx_voltage_set(vdd_id,
				(unsigned long) (v * 1000000));
			if (ret != 0) {
				printf(
					"omapconf: could not set %s new voltage!!!\n\n",
					voltdm44xx_get_name(vdd_id,
					voltdm_name));
			} else {
				printf(
					"%s supply voltage set to %1.3lfV (vsel = 0x%02X).\n\n",
					voltdm44xx_get_name(vdd_id,
						voltdm_name), v,
					smps_uvolt2vsel(vdd_id2smps_id(vdd_id),
						(unsigned long) (v * 1000000)));
				printf("### WARNING ###:\n");
				printf(
					"  - Do not re-enable %s smartreflex or new voltage will be overriden.\n",
					voltdm44xx_get_name(
						vdd_id, voltdm_name));
				printf(
					"  - Do not change OPP (or use CPUFREQ) or new voltage will be overriden.\n\n");
			}
			return ret;
		} else {
			return err_arg_too_many_msg_show(HELP_VOLT);
		}
	} else if (strcmp(argv[0], "pmic") == 0) {
		if (argc < 4) {
			return err_arg_missing_msg_show(HELP_PMIC);
		} else if (argc == 4) {
			if (strcmp(argv[1], "devpwrgrp") == 0)
				return twl603x_pwrgrp_set(stdout,
					argv[2], argv[3]);
			else
				return err_arg_msg_show(HELP_PMIC);
		} else {
			return err_arg_too_many_msg_show(HELP_PMIC);
		}
	} else {
		return err_unknown_argument_msg_show(argv[0]);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main44xx_reset
 * @BRIEF		reset selected item provided in string argv.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		reset selected item provided in string argv.
 *//*------------------------------------------------------------------------ */
static int main44xx_reset(int argc, char *argv[])
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (argc < 1)
		return err_arg_missing_msg_show(HELP_CATEGORY_MAX);
	else if (strcmp(argv[0], "pmic") == 0)
		return twl603x_reset(stdout);
	else
		return err_unknown_argument_msg_show(argv[0]);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main44xx_show
 * @BRIEF		Show configuration of item provided in argv.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		Show configuration of item provided in argv.
 *//*------------------------------------------------------------------------ */
static int main44xx_show(int argc, char *argv[])
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);
	if (argc == 0)
		return err_arg_missing_msg_show(HELP_CATEGORY_MAX);

	if (strcmp(argv[0], "prcm") == 0) {
		if (argc == 2) {
			return prcm44xx_config_show(argv[1]);
		} else if (argc == 3) {
			if (strcmp(argv[2], "cfg") == 0)
				return prcm44xx_config_show(argv[1]);
			else if (strcmp(argv[2], "dep") == 0)
				return prcm44xx_dep_show(argv[1]);
			else
				return err_arg_msg_show(HELP_PRCM);
		} else {
			return err_arg_too_many_msg_show(HELP_PRCM);
		}
	} else if (strcmp(argv[0], "opp") == 0) {
		return opp_show(stdout);
	} else if (strcmp(argv[0], "pwst") == 0) {
		return power44xx_status_show();
	} else if (strcmp(argv[0], "dpll") == 0) {
		if (argc == 1)
			return dpll44xx_config_show(stdout);
		else if ((argc == 2) &&
			(strcmp(argv[1], "cfg") == 0))
			return dpll44xx_config_show(stdout);
		else
			return err_arg_msg_show(HELP_DPLL);
	} else if (strcmp(argv[0], "abe") == 0) {
		if (argc == 1)
			return abe44xx_config_show(stdout);
		else if ((argc == 2) &&
			(strcmp(argv[1], "cfg") == 0))
			return abe44xx_config_show(stdout);
		else if ((argc == 2) &&
			(strcmp(argv[1], "atc") == 0))
			return abe44xx_atc_status_show(stdout);
		else
			return err_arg_msg_show(HELP_ABE);
	} else if (strcmp(argv[0], "temp") == 0) {
		if (argc == 1) {
			return temp_sensor_show(stdout, "all");
		} else if (argc == 2) {
			if (strcmp(argv[1], "all") == 0)
				return temp_sensor_show(stdout, argv[1]);
			else if (temp_sensor_is_available(argv[1]) != 0)
				return temp_sensor_show(stdout, argv[1]);
			else
				return err_arg_msg_show(HELP_TEMPERATURE);
		} else {
			return err_arg_too_many_msg_show(HELP_TEMPERATURE);
		}
	} else if (strcmp(argv[0], "sr") == 0) {
		if (argc == 1) {
			return sr44xx_config_show(stdout);
		} else if (argc == 2) {
			if (strcmp(argv[1], "cfg") == 0)
				return sr44xx_config_show(stdout);
			else if (strcmp(argv[1], "status") == 0)
				return sr44xx_status_show(stdout);
			else
				return err_arg_msg_show(HELP_AVS);
		} else {
			return err_arg_too_many_msg_show(HELP_AVS);
		}
	} else if (strcmp(argv[0], "mpuss") == 0) {
		if (argc == 1) {
			return err_arg_missing_msg_show(HELP_MPUSS);
		} else if ((argc == 2) || ((argc == 3) &&
			(strcmp(argv[2], "cfg") == 0))) {
			if (strcmp(argv[1], "scu") == 0)
				return mpuss44xx_scu_config_show();
			else if (strcmp(argv[1], "gic") == 0)
				return mpuss44xx_gic_config_show();
			else
				return err_arg_msg_show(HELP_MPUSS);
		} else {
			return err_arg_too_many_msg_show(HELP_MPUSS);
		}
	} else if (strcmp(argv[0], "audioic") == 0) {
		if (argc == 1) {
			return twl6040_config(stdout);
		} else if (argc == 2) {
			if (strcmp(argv[1], "cfg") == 0)
				return twl6040_config(stdout);
			else if (strcmp(argv[1], "gains") == 0)
				return twl6040_gains(stdout);
			else
				return err_arg_msg_show(HELP_AUDIOIC);
		} else {
			return err_arg_too_many_msg_show(HELP_AUDIOIC);
		}
	} else if (strcmp(argv[0], "pmic") == 0) {
		if (argc == 1) {
			return err_arg_missing_msg_show(HELP_PMIC);
		} else if (argc == 2) {
			if (strcmp(argv[1], "cfg") == 0)
				return twl603x_config(stdout);
			else if (strcmp(argv[1], "ldocfg") == 0)
				return twl603x_config_ldo(stdout);
			else if (strcmp(argv[1], "smpscfg") == 0)
				return twl603x_config_smps(stdout);
			else if (strcmp(argv[1], "rescfg") == 0)
				return twl603x_config_resources(stdout);
			else if (strcmp(argv[1],
				"devpwrgrpstat") == 0)
				return twl603x_config_devpwrgrp_status(stdout);
			else
				return err_arg_msg_show(HELP_PMIC);
		} else {
			return err_arg_too_many_msg_show(HELP_PMIC);
		}
	} else if (strcmp(argv[0], "hwobs") == 0) {
		if (argc == 1) {
			return hwobs44xx_config_show();
		} else if (argc == 2) {
			if (strcmp(argv[1], "cfg") == 0)
				return hwobs44xx_config_show();
			else
				return err_arg_msg_show(HELP_HWOBS);
		} else {
			return err_arg_too_many_msg_show(HELP_HWOBS);
		}

	} else if (strcmp(argv[0], "timers_32k") == 0) {
		return timestamp_32k_main(argc, argv);
	} else if (strcmp(argv[0], "camera") == 0) {
		if (argc == 1) {
			return camera44xx_config_show();
		} else if (argc == 2) {
			if (strcmp(argv[1], "cfg") == 0)
				return camera44xx_config_show();
			else
				return err_arg_msg_show(HELP_CAMERA);
		} else {
			return err_arg_too_many_msg_show(HELP_CAMERA);
		}
	} else {
		return err_unknown_argument_msg_show(argv[0]);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main44xx_export
 * @BRIEF		Export OMAP configuration into format and destination
 *			provided in argv.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		Export OMAP configuration into format and destination
 *			provided in argv.
 *//*------------------------------------------------------------------------ */
static int main44xx_export(int argc, char *argv[])
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (argc < 1) {
		return err_arg_missing_msg_show(HELP_EXPORT);
	} else if (strcmp(argv[0], "ctt") == 0) {
		if (argc == 1)
			return ctt44xx_dump();
		else if (argc == 2)
			return ctt44xx_rd1_export(argv[1]);
		else
			return err_arg_too_many_msg_show(HELP_EXPORT);
	} else if (strcmp(argv[0], "pct") == 0) {
		if (argc == 1)
			return pct44xx_dump();
		else if (argc == 2)
			return pct44xx_rd1_export(argv[1]);
		else
			return err_arg_too_many_msg_show(HELP_EXPORT);
	} else {
		return err_unknown_argument_msg_show(argv[0]);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main44xx_enable
 * @BRIEF		enable selected item provided in string argv.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		enable selected item provided in string argv.
 *//*------------------------------------------------------------------------ */
static int main44xx_enable(int argc, char *argv[])
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (argc < 1) {
		return err_arg_missing_msg_show(HELP_CATEGORY_MAX);
	} else if (strcmp(argv[0], "hwobs") == 0) {
		if (argc == 1)
			return hwobs44xx_setup_enable();
		else
			return err_arg_too_many_msg_show(HELP_HWOBS);
	} else {
		return err_unknown_argument_msg_show(argv[0]);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main44xx_setup
 * @BRIEF		setup selected item provided in string argv.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		setup selected item provided in string argv.
 *//*------------------------------------------------------------------------ */
static int main44xx_setup(int argc, char *argv[])
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (argc == 0) {
		return err_arg_missing_msg_show(HELP_CATEGORY_MAX);
	} else if (strcmp(argv[0], "hwobs") == 0) {
		if (argc < 2) {
			return err_arg_missing_msg_show(HELP_HWOBS);
		} else if (argc == 2) {
			if (strcmp(argv[1], "pinmux") == 0)
				return hwobs44xx_pinmux_setup();
			else
				return err_arg_msg_show(HELP_HWOBS);
		} else if (argc == 3) {
			if (strcmp(argv[1], "mpuss") == 0)
				return hwobs44xx_mpuss_setup(argv[2]);
			else if (strcmp(argv[1], "abe") == 0)
				return hwobs44xx_abe_setup(argv[2]);
			else
				return err_arg_msg_show(HELP_HWOBS);
		} else if (argc == 4) {
			return err_arg_missing_msg_show(HELP_HWOBS);
		} else if (argc == 5) {
			if (strcmp(argv[1], "prcm") == 0)
				return hwobs44xx_prcm_setup(
						argv[2], argv[3], argv[4]);
			else
				return err_arg_msg_show(HELP_HWOBS);
		} else {
			return err_arg_too_many_msg_show(HELP_HWOBS);
		}
	} else {
		return err_unknown_argument_msg_show(argv[0]);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main44xx_test
 * @BRIEF		test selected item provided in string argv.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		test selected item provided in string argv.
 *//*------------------------------------------------------------------------ */
static int main44xx_test(int argc, char *argv[])
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (argc == 0) {
		return err_arg_missing_msg_show(HELP_CATEGORY_MAX);
	} else if (strcmp(argv[0], "hwobs") == 0) {
		if (argc < 2)
			return err_arg_missing_msg_show(HELP_HWOBS);
		else if (argc == 2)
			return hwobs44xx_test(argv[1]);
		else
			return err_arg_too_many_msg_show(HELP_HWOBS);
	} else {
		return err_unknown_argument_msg_show(argv[0]);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main44xx_search
 * @BRIEF		search selected item provided in string argv.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		test selected item provided in string argv.
 *//*------------------------------------------------------------------------ */
static int main44xx_search(int argc, char *argv[])
{
	voltdm44xx_id vdd_id;
	double v;
	unsigned int ms;
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (argc == 0) {
		return err_arg_missing_msg_show(HELP_CATEGORY_MAX);
	} else if (strcmp(argv[0], "vmin") == 0) {
		if (argc < 4) {
			return err_arg_missing_msg_show(HELP_VOLT);
		} else if (argc == 4) {
			vdd_id = voltdm44xx_s2id(argv[1]);
			if (vdd_id == OMAP4_VD_ID_MAX)
				return err_arg_msg_show(HELP_VOLT);
			ret = sscanf(argv[2], "%lf", &v);
			if (ret != 1)
				return err_arg_msg_show(HELP_VOLT);
			ret = sscanf(argv[3], "%d", &ms);
			if (ret != 1)
				return err_arg_msg_show(HELP_VOLT);
			return voltdm44xx_vminsearch(vdd_id, v, ms);
		} else {
			return err_arg_too_many_msg_show(HELP_VOLT);
		}
	} else {
		return err_unknown_argument_msg_show(argv[0]);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		sigkill_handler
 * @BRIEF		catch kill signal
 * @DESCRIPTION		catch kill signal
 *//*------------------------------------------------------------------------ */
static void sigkill_handler(int sigID, siginfo_t *siginfo, void *context)
{
	/* just to remove "unused parameter" warnings ... */
	sigID = sigID;
	siginfo = siginfo;
	context = context;

	dprintf("Received kill signal %d\n", sigID);
	sci_killhandler();
	exit(0);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main44xx_trace
 * @BRIEF		trace selected item provided in string argv.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		trace selected item provided in string argv.
 *//*------------------------------------------------------------------------ */
int main44xx_trace(int argc, char *argv[])
{
	int ret;
	unsigned int capture_time;
	struct sigaction act;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (argc < 2)
		return err_arg_missing_msg_show(HELP_TRACE);

	if (strcmp(argv[1], "bw") == 0) {
		/* Register kill signal handler */
		act.sa_sigaction = &sigkill_handler;
		sigaction(SIGTERM, &act, NULL);
		sigaction(SIGQUIT, &act, NULL);
		sigaction(SIGINT, &act, NULL);

		return statcoll_main(argc - 1, argv + 1);
	} else if (strcmp(argv[1], "counters") == 0) {
		return counters44xx_main(argc - 1, argv + 1);
	} else if (strcmp(argv[1], "pwrdm") == 0) {
		if (cpu_device_type_get() == DEV_HS) {
			printf(
				"omapconf: this function is not available on HS device, sorry.\n\n");
			return 0;
		}
		if (argc == 2) {
			return trace44xx_pwrdm(
				PERF_TRACE_DEFAULT_DURATION);
		} else if (argc == 3) {
			ret = sscanf(argv[2], "%u", &capture_time);
			if (ret != 1)
				return err_arg_msg_show(HELP_TRACE);
			if (capture_time == 0)
				return err_arg_msg_show(HELP_TRACE);
			return trace44xx_pwrdm(capture_time);
		} else {
			return err_arg_too_many_msg_show(HELP_TRACE);
		}
	} else if (strcmp(argv[1], "opp") == 0) {
		if (cpu_device_type_get() == DEV_HS) {
			printf(
				"omapconf: this function is not available on HS device, sorry.\n\n");
			return 0;
		}
		if (argc == 2) {
			return trace44xx_opp(
				PERF_TRACE_DEFAULT_DURATION);
		} else if (argc == 3) {
			ret = sscanf(argv[2], "%u", &capture_time);
			if (ret != 1)
				return err_arg_msg_show(HELP_TRACE);
			if (capture_time == 0)
				return err_arg_msg_show(HELP_TRACE);
			return trace44xx_opp(capture_time);
		} else {
			return err_arg_too_many_msg_show(HELP_TRACE);
		}
	} else {
		return err_arg_msg_show(HELP_TRACE);
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main44xx_legacy
 * @BRIEF		omap4 functions main entry point (legacy)
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		omap4 functions main entry point (legacy)
 *//*------------------------------------------------------------------------ */
static int main44xx_legacy(int argc, char *argv[])
{
	int ret = 0;
	voltdm44xx_id vdd_id;
	char voltdm_name[VOLTDM44XX_MAX_NAME_LENGTH];
	double v;
	unsigned int ms;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (argc == 0)
		return err_arg_missing_msg_show(HELP_CATEGORY_MAX);

	if (strcmp(argv[0], "pwst") == 0) {
		ret = power44xx_status_show();
	} else if (strcmp(argv[0], "opp") == 0) {
		ret = opp_show(stdout);
	} else if (strcmp(argv[0], "hwobs") == 0) {
		ret = hwobs44xx_main(argc, argv);
	} else if (strcmp(argv[0], "mpu") == 0) {
		ret = mpu44xx_main(argc, argv);
	} else if (strcmp(argv[0], "mpuss") == 0) {
		ret = mpuss44xx_main(argc, argv);
	} else if (strcmp(argv[0], "dplls") == 0) {
		ret = dpll44xx_main(argc, argv);
	} else if (strcmp(argv[0], "wkdep") == 0) {
		ret = wkdep44xx_main(argc, argv);
	} else if (strcmp(argv[0], "core") == 0) {
		ret = core44xx_main(argc, argv);
	} else if (strcmp(argv[0], "per") == 0) {
		ret = per44xx_main(argc, argv);
	} else if (strcmp(argv[0], "dsp") == 0) {
		ret = dsp44xx_main(argc, argv);
	} else if (strcmp(argv[0], "dss") == 0) {
		ret = dss44xx_main(argc, argv);
	} else if (strcmp(argv[0], "cam") == 0) {
		ret = cam44xx_main(argc, argv);
	} else if (strcmp(argv[0], "sgx") == 0) {
		ret = gfx44xx_main(argc, argv);
	} else if (strcmp(argv[0], "gfx") == 0) {
		ret = gfx44xx_main(argc, argv);
	} else if (strcmp(argv[0], "ivahd") == 0) {
		ret = ivahd44xx_main(argc, argv);
	} else if (strcmp(argv[0], "iva") == 0) {
		ret = ivahd44xx_main(argc, argv);
	} else if (strcmp(argv[0], "per") == 0) {
		ret = per44xx_main(argc, argv);
	} else if (strcmp(argv[0], "abe") == 0) {
		ret = abe44xx_main(argc, argv);
	} else if (strcmp(argv[0], "wkup") == 0) {
		ret = wkup44xx_main(argc, argv);
	} else if (strcmp(argv[0], "l3init") == 0) {
		ret = l3init44xx_main(argc, argv);
	} else if (strcmp(argv[0], "alwon") == 0) {
		ret = alwon44xx_main(argc, argv);
	} else if (strcmp(argv[0], "emu") == 0) {
		ret = emu44xx_main(argc, argv);
	} else if (strcmp(argv[0], "sr") == 0) {
		if (argc == 1) {
			ret = err_arg_missing_msg_show(HELP_AVS);
		} else if (argc == 2) {
			if (strcmp(argv[1], "dump") == 0)
				ret = sr44xx_dump();
			else if (strcmp(argv[1], "cfg") == 0)
				ret = sr44xx_config_show(stdout);
			else if (strcmp(argv[1], "status") == 0)
				ret = sr44xx_status_show(stdout);
			else
				ret = err_unknown_argument_msg_show(argv[1]);
		} else {
			ret = err_arg_too_many_msg_show(HELP_AVS);
		}
	} else if (strcmp(argv[0], "abb") == 0) {
		ret = abb44xx_main(argc, argv);
	} else if (strcmp(argv[0], "temp") == 0) {
		if (argc == 1) {
			ret = temp_sensor_show(stdout, "all");
		} else if (argc == 2) {
			if (strcmp(argv[1], "all") == 0)
				ret = temp_sensor_show(stdout, argv[1]);
			else if (temp_sensor_is_available(argv[1]) != 0)
				ret = temp_sensor_show(stdout, argv[1]);
			else
				ret = err_arg_msg_show(HELP_TEMPERATURE);
		} else {
			ret = err_arg_too_many_msg_show(HELP_TEMPERATURE);
		}
	} else if (strcmp(argv[0], "ctt") == 0) {
		ret = ctt44xx_main(argc, argv);
	} else if (strcmp(argv[0], "pct") == 0) {
		ret = pct44xx_main(argc, argv);
	} else if (strcmp(argv[0], "emif") == 0) {
		ret = emif44xx_main(argc, argv);
	} else if (strcmp(argv[0], "twl6040") == 0) {
		ret = twl6040_main(argc, argv);
	} else if (strcmp(argv[0], "display") == 0) {
		if (argc == 3) {
			ret = display44xx_dump(argv[2]);
		} else {
			help(HELP_DISPLAY);
			ret = OMAPCONF_ERR_ARG;
		}
	} else if (strcmp(argv[0], "statdep") == 0) {
		ret = statdep44xx_main(argc, argv);
	} else if (strcmp(argv[0], "twl6030") == 0) {
		ret = twl603x_main(argc, argv);
	} else if (strcmp(argv[0], "camera") == 0) {
		ret = camera44xx_main(argc, argv);
	} else if (strcmp(argv[0], "setvolt") == 0) {
		/* Retrieve arguments */
		if (argc != 3)
			return err_arg_msg_show(HELP_VOLT);
		vdd_id = voltdm44xx_s2id(argv[1]);
		if (vdd_id == OMAP4_VD_ID_MAX)
			return err_arg_msg_show(HELP_VOLT);
		ret = sscanf(argv[2], "%lf", &v);
		if (ret != 1)
			return err_arg_msg_show(HELP_VOLT);
		/* Call function with retrieved arguments */
		ret = sr44xx_voltage_set(vdd_id,
			(unsigned long) (v * 1000000));
		if (ret != 0) {
			fprintf(stderr,
				"Error: could not set %s new voltage!!!\n\n",
				voltdm44xx_get_name(vdd_id, voltdm_name));
		} else {
			printf(
				"%s supply voltage set to %1.3lfV (vsel = 0x%02X).\n\n",
				voltdm44xx_get_name(vdd_id, voltdm_name), v,
				smps_uvolt2vsel(vdd_id2smps_id(vdd_id),
					(unsigned long) (v * 1000000)));
			printf("### WARNING ###:\n");
			printf(
				"  - Do not re-enable %s smartreflex or new voltage will be overriden.\n",
				voltdm44xx_get_name(vdd_id, voltdm_name));
			printf(
				"  - Do not change OPP (or use CPUFREQ) or new voltage will be overriden.\n\n");
		}
	} else if (strcmp(argv[0], "vminsearch") == 0) {
		if (argc != 4)
			return err_arg_msg_show(HELP_VOLT);
		vdd_id = voltdm44xx_s2id(argv[1]);
		if (vdd_id == OMAP4_VD_ID_MAX)
			return err_arg_msg_show(HELP_VOLT);
		ret = sscanf(argv[2], "%lf", &v);
		if (ret != 1)
			return err_arg_msg_show(HELP_VOLT);
		ret = sscanf(argv[3], "%d", &ms);
		if (ret != 1)
			return err_arg_msg_show(HELP_VOLT);
		ret = voltdm44xx_vminsearch(vdd_id, v, ms);
	} else {
		ret = err_unknown_argument_msg_show(argv[0]);
		goto main44xx_legacy_end;
	}

	if (ret != 0)
		goto main44xx_legacy_end;

	fprintf(stderr,
		"\n\n### WARNING ###: deprecated command/options. See 'omapconf --help'.\n\n");

main44xx_legacy_end:
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		main44xx
 * @BRIEF		omap4 functions main entry point
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		omap4 functions main entry point (legacy)
 *//*------------------------------------------------------------------------ */
int main44xx(int argc, char *argv[])
{
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (argc == 0) {
		help(HELP_USAGE);
		return OMAPCONF_ERR_ARG;
	}

	/* Initializations */
	main44xx_init();

	if (strcmp(argv[0], "dump") == 0)
		ret = main44xx_dump(argc - 1, argv + 1);
	else if (strcmp(argv[0], "show") == 0)
		ret = main44xx_show(argc - 1, argv + 1);
	else if (strcmp(argv[0], "audit") == 0)
		ret = audit44xx_main(argc, argv);
	else if (strcmp(argv[0], "trace") == 0)
		ret = main44xx_trace(argc, argv);
	else if (strcmp(argv[0], "search") == 0)
		ret = main44xx_search(argc - 1, argv + 1);
	else if (strcmp(argv[0], "export") == 0)
		ret = main44xx_export(argc - 1, argv + 1);
	else if (strcmp(argv[0], "read") == 0)
		ret = main44xx_read(argc - 1, argv + 1);
	else if (strcmp(argv[0], "write") == 0)
		ret = main44xx_write(argc - 1, argv + 1);
	else if (strcmp(argv[0], "set") == 0)
		ret = main44xx_set(argc - 1, argv + 1);
	else if (strcmp(argv[0], "reset") == 0)
		ret = main44xx_reset(argc - 1, argv + 1);
	else if (strcmp(argv[0], "clear") == 0)
		ret = main44xx_clear(argc - 1, argv + 1);
	else if (strcmp(argv[0], "enable") == 0)
		ret = main44xx_enable(argc - 1, argv + 1);
	else if (strcmp(argv[0], "setup") == 0)
		ret = main44xx_setup(argc - 1, argv + 1);
	else if (strcmp(argv[0], "test") == 0)
		ret = main44xx_test(argc - 1, argv + 1);
	else
		ret = main44xx_legacy(argc, argv);

	return ret;
}
