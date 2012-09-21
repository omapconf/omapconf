/*
 *
 * @Component			OMAPCONF
 * @Filename			audit54xx.c
 * @Description			OMAP5 Power Audit Functions
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


#include <audit54xx.h>
#include <module54xx.h>
#include <lib.h>
#include <autoadjust_table.h>
#include <cpufreq.h>
#include <cpuinfo.h>
#include <help.h>
#include <clkdm_dependency54xx.h>
#include <ctrlmod54xx.h>
#include <dpll54xx.h>


/* #define AUDIT54XX_DEBUG */
#ifdef AUDIT54XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static const char pass[5] = "Pass";
static const char fail[5] = "FAIL";
static const char ignore[12] = "Ignored (1)";
static const char warning[8] = "Warning";


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		audit54xx_clkspeed
 * @BRIEF		OMAP5 modules functional clock speed audit.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in,out]	stream: output file - NULL: no output (silent)
 * @param[in]		clkfwk_audit: include audit of kernel clock framework
 * @param[in,out]	err_nbr: pointer to return audit error number
 * @param[in,out]	wng_nbr: pointer to return audit warning number
 * @DESCRIPTION		OMAP5 modules functional clock speed audit.
 *//*------------------------------------------------------------------------ */
int audit54xx_clkspeed(FILE *stream, unsigned short clkfwk_audit,
	unsigned int *err_nbr, unsigned int *wng_nbr)
{
	mod54xx_id module_id;
	clk54xx_id src_clk_id;
	opp54xx_id current_opp;
	double speed_curr = 0.0, speed_por = 0.0, speed_curr_fw = 0.0;
	const char pass1[10] = "pass (1)";
	const char fail2[10] = "FAIL (2)";
	const char fail3[10] = "FAIL (3)";
	const char warning4[10] = "warn (4)";
	const char warning5[10] = "warn (5)";
	const char warning6[10] = "warn (6)";
	const char warning7[10] = "warn (7)";
	const char ignore8[10] = "ign. (8)";
	const char pass9[10] = "pass (9)";
	const char fail9[10] = "FAIL (10)";
	const char warning11[10] = "warn (11)";
	const char warning12[10] = "warn (12)";
	const char warning13[10] = "warn (13)";
	const char fixme[10] = "FIXME";
	char *status;
	char s_speed_curr[16], s_speed_por[16],  s_speed_curr_fw[16];
	char *status_fw;
	char src_clk_name[CLK54XX_MAX_NAME_LENGTH];
	char src_clk_fw_name[CLK54XX_MAX_NAME_LENGTH];
	char opp_name[OPP_MAX_NAME_LENGTH];
	char prev_gov[CPUFREQ_GOV_MAX_NAME_LENGTH];
	char prev_gov2[CPUFREQ_GOV_MAX_NAME_LENGTH];
	int ret;
	mod_module_mode mmode;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(err_nbr, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(wng_nbr, OMAPCONF_ERR_ARG);

	*err_nbr = 0;
	*wng_nbr = 0;

	/* Switch to userspace governor temporarily,
	 * so that OPP cannot change during audit and does not false it.
	 */
	cpufreq_scaling_governor_set("userspace", prev_gov);

	if (stream == NULL)
		goto audit54xx_clkspeed_loop;

	if (clkfwk_audit) {
		fprintf(stream,
			"|-----------------------------------------------------"
			"------------------------------------------------------"
			"------------------------------------------------------"
			"----|\n");
		fprintf(stream,
			"| %-21s | %-51s || %-9s || %-42s || %-11s | %-11s |\n",
			"  CLOCK SPEED AUDIT",
			"                   Source Clock", "",
			"             Clock Rate (MHz)", "", "");
		fprintf(stream,
			"| %-21s | %-51s || %-9s || %-12s | %-12s | %-12s |"
			"| %-11s | %-11s |\n", "", "", "", "", "  OMAPCONF",
			"   KERNEL", "  OMAPCONF", "  KERNEL");
		fprintf(stream,
			"| %-21s | %-24s | %-24s || %-9s || %-12s | %-12s |"
			" %-12s || %-11s | %-11s |\n", "       Module",
			"     From OMAPCONF", "      From KERNEL", "   OPP",
			"  Expected", "  Current", "   Current", "  STATUS",
			"  STATUS");
		fprintf(stream,
			"|-----------------------------------------------------"
			"------------------------------------------------------"
			"------------------------------------------------------"
			"----|\n");
	} else {
		fprintf(stream,
			"|-----------------------------------------------------"
			"-----------------------------------------------------"
			"|\n");
		fprintf(stream, "| %-21s | %-24s | %-9s | %-27s | %-11s |\n",
			"  CLOCK SPEED AUDIT", "", "", "     Clock Rate (MHz)",
			"");
		fprintf(stream,
			"| %-21s | %-24s | %-9s | %-12s | %-12s | %-11s |\n",
			"Module", "Source Clock", "OPP", "Current", "Expected",
			"STATUS");
		fprintf(stream,
			"|-----------------------------------------------------"
			"-----------------------------------------------------"
			"|\n");
	}

audit54xx_clkspeed_loop:
	for (module_id = 0; module_id < MOD54XX_ID_MAX; module_id++) {
		dprintf("\n\n%s():Auditing module %s\n", __func__,
			mod54xx_name_get(module_id));
		/* Filter module ID */
		switch (module_id) {
		case OMAP5_TIMER12:
		case OMAP5_WDT1:
		case OMAP5_DMA_CRYPTO:
		case OMAP5_AES1:
		case OMAP5_AES2:
		case OMAP5_SHA2MD5:
		case OMAP5_RNG:
		case OMAP5_DES3DES:
		case OMAP5_PKA:
			if (cpu_is_gp_device()) {
				dprintf("\tGP device, skip it.\n");
				break;
			}

		default:
			/* init variables */
			status = (char *) fixme;
			status_fw = (char *) fixme;
			speed_curr = -1.0;
			snprintf(s_speed_curr, 16, "%s", "NOT FOUND");
			snprintf(src_clk_name, CLK54XX_MAX_NAME_LENGTH, "%s",
				"NOT FOUND");
			strcpy(opp_name, "NOT FOUND");
			speed_por = -2.0;
			snprintf(s_speed_por, 16, "%s", "NOT FOUND");
			speed_curr_fw = -3.0;
			snprintf(s_speed_curr_fw, 16, "%s", "NOT FOUND");
			snprintf(src_clk_fw_name, CLK54XX_MAX_NAME_LENGTH, "%s",
				"NOT FOUND");

			/* Get module's functional source clock */
			ret = mod54xx_opp_clk_rate_get(module_id,
				&src_clk_id, &current_opp, &speed_curr);
			if (src_clk_id == CLK54XX_ID_MAX) {
				dprintf("%s(): src_clk not found!\n", __func__);
				status = (char *) warning4;
				(*wng_nbr)++;
				goto audit54xx_clkspeed_opp_fill;
			}
			snprintf(src_clk_name, CLK54XX_MAX_NAME_LENGTH, "%s",
				clk54xx_name_get(src_clk_id));

			if (speed_curr < 0) {
				dprintf("%s(): speed not found!\n", __func__);
				status = (char *) warning5;
				(*wng_nbr)++;
				goto audit54xx_clkspeed_opp_fill;
			}
			dprintf("%s(): speed=%lfMHz\n", __func__, speed_curr);
			mhz2string(speed_curr, s_speed_curr);

			if (current_opp == OPP54XX_ID_MAX) {
				dprintf("%s(): opp not found!\n", __func__);
				status = (char *) fail3;
				(*err_nbr)++;
				goto audit54xx_clkspeed_opp_fill;
			}
			strncpy(opp_name, opp54xx_name_get(current_opp),
				OPP_MAX_NAME_LENGTH);

			if (ret != 0) {
				dprintf("%s(): src_clk/speed/opp not found!\n",
					__func__);
				status = (char *) fixme;
				(*wng_nbr)++;
				goto audit54xx_clkspeed_opp_fill;
			}

			if (clkfwk_audit) {
				/*
				 * Get module's functional source clock from
				 * the kernel clock framework
				 */
				snprintf(src_clk_fw_name,
					CLK54XX_MAX_NAME_LENGTH,
					"%s", clk54xx_name_get_fw(src_clk_id));
				if (strcmp(src_clk_fw_name, "FIXME") == 0) {
					status_fw = (char *) warning11;
					(*wng_nbr)++;
					goto audit54xx_clkspeed_get_por_speed;
				} else if (strcmp(src_clk_fw_name, "UNKNOWN") ==
					0) {
					status_fw = (char *) warning11;
					(*wng_nbr)++;
					goto audit54xx_clkspeed_get_por_speed;
				}

				/*
				 * Get the module's functional source clock rate
				 * from the kernel clock framework
				 */
				speed_curr_fw = clk54xx_rate_get_fw(src_clk_id);
				if (speed_curr_fw < 0.0) {
					dprintf("\tWarning: %s current rate "
						"not found!\n",
						mod54xx_name_get(module_id));
					status_fw = (char *) warning12;
					(*wng_nbr)++;
					goto audit54xx_clkspeed_get_por_speed;
				}

				if (speed_curr_fw < 1.0)
					snprintf(s_speed_curr_fw, 16, "%lf",
						speed_curr_fw);
				else
					snprintf(s_speed_curr_fw, 16, "%.3lf",
						speed_curr_fw);

				if ((int) speed_curr_fw == (int) speed_curr) {
					status_fw = (char *) pass9;
					dprintf("%s(): fw pass!\n", __func__);
				} else {
					status_fw = (char *) fail9;
					(*err_nbr)++;
					dprintf("%s(): fw FAIL!\n", __func__);
				}
				dprintf("\tsource clock (from kernel): %s\n",
					src_clk_fw_name);
				dprintf("\tsource clock rate (from kernel) is "
					"%lfMHz\n", speed_curr_fw);
			}

audit54xx_clkspeed_get_por_speed:
			/*
			 * Get Plan Of Record (POR) module's functional
			 * source clock speed
			 */
			switch (module_id) {
			case OMAP5_TIMER2:
			case OMAP5_TIMER3:
			case OMAP5_TIMER4:
			case OMAP5_TIMER5:
			case OMAP5_TIMER6:
			case OMAP5_TIMER7:
			case OMAP5_TIMER8:
			case OMAP5_TIMER9:
			case OMAP5_TIMER10:
			case OMAP5_TIMER11:
			case OMAP5_MCASP:
			case OMAP5_MCBSP1:
			case OMAP5_MCBSP2:
			case OMAP5_MCBSP3:
			case OMAP5_SLIMBUS1:
			case OMAP5_SLIMBUS2:
				/* These modules are out of interest or
				 * there is no mandatory clock speed
				 */
				snprintf(s_speed_por, 16, "%s", "Undefined");
				status = (char *) ignore8;
				break;

			default:
				mmode = mod54xx_mode_get(module_id);
				speed_por = mod54xx_por_clk_rate_get(
					module_id, current_opp);
				if (speed_por < 0.0) {
					dprintf("\tWarning: %s POR speed"
						" not yet defined!\n",
						mod54xx_name_get(module_id));
					status = (char *) warning6;
					(*wng_nbr)++;
					goto audit54xx_clkspeed_opp_fill;
				}
				dprintf("\tPOR rate is %lfMHz\n", speed_por);

				if (speed_por < 1.0)
					snprintf(s_speed_por, 16, "%lf",
						speed_por);
				else
					snprintf(s_speed_por, 16, "%.3lf",
						speed_por);
				/* Keep only 1 decimal for comparison */
				if (speed_curr > 1.0)
					speed_curr = (double) ((int)
						(speed_curr * 10.0)) / 10.0;
				dprintf("%s(): rounded current speed=%lfMHz\n",
					__func__, speed_curr);
				if (speed_por > 1.0)
					speed_por = (double) ((int)
						(speed_por * 10.0)) / 10.0;
				dprintf("%s(): rounded POR     speed=%lfMHz\n",
					__func__, speed_por);

				if (speed_curr == speed_por) {
					status = (char *) pass1;
					dprintf("%s(): pass!\n", __func__);
				} else if (mmode == MOD_DISABLED_MODE) {
					/*
					 * may not be a true failure when
					 * module is disabled (not configured).
					 * Does not impact power.
					 */
					dprintf("%s(): disabled module.\n",
						__func__);
					status = (char *) warning7;
					(*wng_nbr)++;
				} else if (speed_curr == 0.0) {
					dprintf("%s(): speed_curr == 0.0.\n",
						__func__);
					status = (char *) warning7;
					(*wng_nbr)++;
				} else if (speed_curr < speed_por) {
					dprintf("%s(): curr < por.\n",
						__func__);
					status = (char *) warning13;
					(*wng_nbr)++;
				} else {
					dprintf("%s(): FAILED!\n", __func__);
					status = (char *) fail2;
					(*err_nbr)++;
				}
			}

audit54xx_clkspeed_opp_fill:
			if (stream == NULL)
				break;

			if (clkfwk_audit) {
				fprintf(stream,
					"| %-21s | %-24s | %-24s || %-9s |"
					"| %-12s | %-12s | %-12s ||   %-9s "
					"|   %-9s |\n",
					mod54xx_name_get(module_id),
					src_clk_name, src_clk_fw_name,
					opp_name, s_speed_por, s_speed_curr,
					s_speed_curr_fw, status, status_fw);
			} else {
				fprintf(stream,
					"| %-21s | %-24s | %-9s | %-12s | %-12s"
					" | %-11s |\n",
					mod54xx_name_get(module_id),
					src_clk_name, opp_name, s_speed_curr,
					s_speed_por, status);
			}
		}
	}
	if (stream != NULL) {
		if (clkfwk_audit) {
			fprintf(stream, "|-------------------------------------"
				"----------------------------------------------"
				"----------------------------------------------"
				"------------------------------------|\n\n");
		} else {
			fprintf(stream,
				"|---------------------------------------------"
				"----------------------------------------------"
				"---------------|\n\n");
		}
		fprintf(stream, "Notes:\n");
		fprintf(stream, "  (1)  Current module rate IS the expected "
			"(PoR) one.\n");
		fprintf(stream, "  (2)  Current module rate is NOT the expected"
			" (PoR) one.\n");
		fprintf(stream, "  (3)  Current OPP could not be detected.\n");
		fprintf(stream, "  (4)  Current module source clock could not "
			"be retrieved.\n");
		fprintf(stream, "  (5)  Current module source clock rate could "
			"not be retrieved.\n");
		fprintf(stream, "  (6)  Current module source clock PoR rate "
			"could not be retrieved.\n");
		fprintf(stream, "  (7)  Clock rate does no match PoR rate, "
			"but module is disabled (no power impact).\n");
		fprintf(stream, "  (8)  Optional module, not used on reference "
			"platform.\n");
		if (clkfwk_audit) {
			fprintf(stream, "  (9)  Module rates reported by kernel"
				" clock framework & OMAPCONF are IDENTICAL.\n");
			fprintf(stream, "  (10)  Module rates reported by "
				"kernel clock framework & OMAPCONF are "
				"DIFFERENT.\n");
			fprintf(stream, "  (11) Current module source clock "
				"could not be retrieved from kernel clock "
				"framework.\n");
			fprintf(stream, "  (12) Current module source clock "
				"rate could not be retrieved from kernel clock "
				"framework.\n");
		}
		fprintf(stream, "  (13)  Current module rate is lower than "
			"the expected (PoR) one.\n");
		if (!clkfwk_audit) {
			fprintf(stream, "\nUse '-k' or '-kernel' to also audit "
			"kernel clock framework.\n\n");
		}

		if (*err_nbr == 0)
			fprintf(stream, "\nSUCCESS! Clock Speed audit "
				"completed with 0 error (%d warning(s))\n\n",
				*wng_nbr);
		else
			fprintf(stream, "\nFAILED! Clock Speed audit "
				"completed with %d error and %d warning.\n\n",
				*err_nbr, *wng_nbr);
	}

	/* Restore CPUFreq governor */
	cpufreq_scaling_governor_set(prev_gov, prev_gov2);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		audit54xx_sysconfig
 * @BRIEF		OMAP5 SYSCONFIG registers audit.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in,out]	stream: output file - NULL: no output (silent)
 * @param[in,out]	err_nbr: pointer to return audit error number
 * @param[in,out]	wng_nbr: pointer to return audit warning number
 * @DESCRIPTION		OMAP5 SYSCONFIG registers audit.
 *//*------------------------------------------------------------------------ */
int audit54xx_sysconfig(FILE *stream, unsigned int *err_nbr,
	unsigned int *wng_nbr)
{
	mod54xx_id id;
	mod_autoidle_mode autoidle_mode;
	mod_idle_mode idle_mode;
	mod_standby_mode standby_mode;
	mod_clock_activity_mode clock_activity_mode;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row;
	char element[TABLE_MAX_ELT_LEN];

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(err_nbr, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(wng_nbr, OMAPCONF_ERR_ARG);

	*err_nbr = 0;
	*wng_nbr = 0;

	autoadjust_table_init(table);

	row = 0;
	strncpy(table[row][0], "MODULES SYSCONFIG AUDIT", TABLE_MAX_ELT_LEN);
	strncpy(table[row][1], "AUTOIDLE Mode", TABLE_MAX_ELT_LEN);
	strncpy(table[row][2], "IDLE Mode", TABLE_MAX_ELT_LEN);
	strncpy(table[row][3], "STANDBY Mode", TABLE_MAX_ELT_LEN);
	strncpy(table[row][4], "CLOCK ACTIVITY Mode", TABLE_MAX_ELT_LEN);
	row++;

	for (id = OMAP5_DEBUGSS; id < MOD54XX_ID_MAX; id++) {
		dprintf("\n%s(): Module #%d name = %s\n", __func__,
			id, mod54xx_name_get(id));
		autoadjust_table_strncpy(table, row, 0,
			(char *) mod54xx_name_get(id));
		if (!mod54xx_has_sysconfig_register(id)) {
			dprintf("\t%s(): no sysconfig\n", __func__);
			continue;
		}

		if (mod54xx_is_accessible(id) != 1) {
			dprintf("\t%s(): module is not accessible\n", __func__);
			autoadjust_table_strncpy(table, row, 1,
				(char *) ignore);
			autoadjust_table_strncpy(table, row, 2,
				(char *) ignore);
			autoadjust_table_strncpy(table, row, 3,
				(char *) ignore);
			autoadjust_table_strncpy(table, row, 4,
				(char *) ignore);
			row++;
			continue;
		}

		/* Audit module's autoidle bit (if any) */
		autoidle_mode = mod54xx_autoidle_mode_get(id);
		if (autoidle_mode == MOD_AUTOIDLE_MODE_MAX) {
			dprintf("\t%s(): module does not have autoidle bit\n",
				__func__);
			goto audit54xx_sysconfig_idle_mode;
		}
		dprintf("\t%s(): autoidle=%u (%s)\n", __func__, autoidle_mode,
			mod_autoidle_mode_name_get(autoidle_mode));
		if (autoidle_mode == MOD_AUTOGATING) {
			autoadjust_table_strncpy(table, row, 1, (char *) pass);
		} else {
			snprintf(element, TABLE_MAX_ELT_LEN, "%s (%s)",
				fail, mod_autoidle_mode_name_get(
					autoidle_mode));
			autoadjust_table_strncpy(table, row, 1, element);
			(*err_nbr)++;
		}

audit54xx_sysconfig_idle_mode:
		/* Audit module's IDLE mode */
		idle_mode = mod54xx_idle_mode_get(id);
		if (idle_mode == MOD_IDLE_MODE_MAX) {
			dprintf("\t%s(): module does not have idle mode\n",
				__func__);
			goto audit54xx_sysconfig_standby_mode;
		}
		dprintf("\t%s(): idle mode=%u (%s)\n", __func__, idle_mode,
			mod_idle_mode_name_get(idle_mode));
		switch (idle_mode) {
		case MOD_SMART_IDLE_WAKEUP:
			autoadjust_table_strncpy(table, row, 2, (char *) pass);
			break;
		case MOD_SMART_IDLE:
			if (!mod54xx_has_smart_idle_wakeup_mode(id)) {
				autoadjust_table_strncpy(table, row, 2,
					(char *) pass);
			} else {
				snprintf(element, TABLE_MAX_ELT_LEN,
					"%s (%s) (3)", fail,
					mod_idle_mode_name_get(idle_mode));
				autoadjust_table_strncpy(table, row, 2,
					element);
				(*err_nbr)++;
			}
			break;
		case MOD_FORCE_IDLE:
			snprintf(element, TABLE_MAX_ELT_LEN, "%s (%s)",
				warning, mod_idle_mode_name_get(idle_mode));
			autoadjust_table_strncpy(table, row, 2,	element);
			(*wng_nbr)++;
			break;
		default:
			if ((id == OMAP5_UART1) ||
				(id == OMAP5_UART2) ||
				(id == OMAP5_UART3) ||
				(id == OMAP5_UART4) ||
				(id == OMAP5_UART5) ||
				(id == OMAP5_UART6)) {
				/*
				 * UART IP idle management is buggy
				 * (cf errata). When active,
				 * must be used in no-idle mode.
				 */
				autoadjust_table_strncpy(table, row, 2,
					(char *) pass);
			} else {
				snprintf(element, TABLE_MAX_ELT_LEN,
					"%s (%s)", fail, mod_idle_mode_name_get(
						idle_mode));
				autoadjust_table_strncpy(table, row, 2,
					element);
				(*err_nbr)++;
			}
		}

audit54xx_sysconfig_standby_mode:
		/* Audit module's STANDBY mode */
		standby_mode = mod54xx_standby_mode_get(id);
		if (standby_mode == MOD_STANDBY_MODE_MAX) {
			goto audit54xx_sysconfig_clock_activity_mode;
			dprintf("\t%s(): module does not have standby mode\n",
				__func__);
		}
		dprintf("\t%s(): standby mode=%u (%s)\n", __func__,
			standby_mode, mod_standby_mode_name_get(standby_mode));
		switch (standby_mode) {
		case MOD_STANDBY_MODE_RESERVED:
			autoadjust_table_strncpy(table, row, 3, (char *) pass);
			break;
		case MOD_SMART_STANDBY:
			if (!mod54xx_has_smart_standby_wakeup_mode(id)) {
				autoadjust_table_strncpy(table, row, 2,
					(char *) pass);
			} else {
				snprintf(element, TABLE_MAX_ELT_LEN,
					"%s (%s) (4)", fail,
					mod_standby_mode_name_get(idle_mode));
				autoadjust_table_strncpy(table, row, 2,
					element);
				(*err_nbr)++;
			}
			break;
		case MOD_FORCE_STANDBY:
			snprintf(element, TABLE_MAX_ELT_LEN, "%s (%s)",
				warning, mod_standby_mode_name_get(
					standby_mode));
			autoadjust_table_strncpy(table, row, 3, element);
			(*wng_nbr)++;
			break;
		default:
			snprintf(element, TABLE_MAX_ELT_LEN, "%s (%s)",
				fail, mod_standby_mode_name_get(standby_mode));
			autoadjust_table_strncpy(table, row, 3,	element);
			(*err_nbr)++;
		}

audit54xx_sysconfig_clock_activity_mode:
		/* Audit module's CLOCK ACTIVITY mode */
		clock_activity_mode = mod54xx_clock_activity_mode_get(id);
		if (clock_activity_mode == MOD_CLOCK_ACTIVITY_MODE_MAX) {
			dprintf("\t%s(): module does not have "
				"clock activity mode\n", __func__);
			goto audit54xx_sysconfig_next_row;
		}
		dprintf("\t%s(): clock activity mode=%u (%s)\n",
			__func__, clock_activity_mode,
			mod_clock_activity_mode_name_get(clock_activity_mode));
		switch (clock_activity_mode) {
		case MOD_FCLK_AUTO_ICLK_AUTO:
			/*
			 * Functional clock can be switched-off.
			 * L4 clock can be switched-off.
			 */
			autoadjust_table_strncpy(table, row, 4,	(char *) pass);
			break;
		case MOD_FCLK_AUTO_ICLK_ON:
			/*
			 * Functional clock can be switched-off.
			 * L4 clock is maintained during wake-up period.
			 */
		case MOD_FCLK_ON_ICLK_AUTO:
			/*
			 * Functional clock is maintained during wake-up
			 * period.
			 * L4 clock can be switched-off.
			 */
			snprintf(element, TABLE_MAX_ELT_LEN, "%s (%s)",
				warning, mod_clock_activity_mode_name_get(
					clock_activity_mode));
			autoadjust_table_strncpy(table, row, 4,	element);
			(*wng_nbr)++;
			break;
		case MOD_FCLK_ON_ICLK_ON:
			/*
			 * Functional clock is maintained during wake-up
			 * period.
			 * L4 clock is maintained during wake-up period.
			 */
		default:
			snprintf(element, TABLE_MAX_ELT_LEN, "%s (%s)",
				fail, mod_clock_activity_mode_name_get(
					clock_activity_mode));
			autoadjust_table_strncpy(table, row, 4,	element);
			(*err_nbr)++;
		}
audit54xx_sysconfig_next_row:
		row++;
	}

	if (stream != NULL) {
		autoadjust_table_fprint(stream, table, row, 5);
		fprintf(stream, "NB:\n");
		fprintf(stream, "  (1) - Show 'Ignored' when module is disabled"
			" (registers not accessible).\n");
		fprintf(stream, "  (2) - Show empty cell(s) when module does "
			"not feature this mode.\n");
		fprintf(stream, "  - AUTOIDLE MODE:\n");
		fprintf(stream, "    - Report Pass if enabled, FAIL otherwise."
			"\n");
		fprintf(stream, "  - IDLE MODE:\n");
		fprintf(stream, "    - Report Pass if set to \"Smart-Idle\" or "
			"\"Smart-Idle Wakeup\" (when available).\n");
		fprintf(stream, "      - (3) Modules featuring \"Smart-Idle "
			"Wakeup\" mode must be programmed in this mode. Audit "
			"will report FAIL even with \"Smart-Idle\" mode.\n");
		fprintf(stream, "    - Report Warning (with setting) in case of"
			" \"Force-Idle\" mode.\n");
		fprintf(stream, "    - Report FAIL (with incorrect setting) "
			"otherwise.\n");
		fprintf(stream, "  - STANDBY MODE:\n");
		fprintf(stream, "    - Report Pass if set to \"Smart-Standby\" "
			"or \"Smart-Standby Wakeup\" (when available).\n");
		fprintf(stream, "      - (4) Modules featuring \"Smart-Standby "
			"Wakeup\" mode must be programmed in this mode. Audit "
			"will report FAIL even with \"Smart-Standby\" mode.\n");
		fprintf(stream, "    - Report Warning (with setting) in case of"
			" \"Force-Standby\" mode.\n");
		fprintf(stream, "    - Report FAIL (with incorrect setting) "
			"otherwise.\n");
		fprintf(stream, "  - CLOCKACTIVITY MODE:\n");
		fprintf(stream, "    - Report Pass if both I-CLK and F-CLK are "
			"set to AUTO mode.\n");
		fprintf(stream, "    - Report Warning if one of I-CLK or F-CLK "
			"is set to ON mode.\n");
		fprintf(stream, "    - Report FAIL (with incorrect setting) "
			"otherwise.\n\n");

		if (*err_nbr == 0) {
			fprintf(stream, "SUCCESS! Modules SYSCONFIG registers "
				"audit completed with 0 error "
				"(%d warning(s))\n\n",
				*wng_nbr);
		} else {
			fprintf(stream, "FAILED! Modules SYSCONFIG registers "
				"audit completed with %d error and "
				"%d warning.\n\n",
				*err_nbr, *wng_nbr);
		}
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		audit54xx_dpll
 * @BRIEF		audit DPLL Configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		stream: output file (NULL: no output (silent))
 * @param[in]		dpll_id: DPLL ID
 *				(use DPLL54XX_ID_MAX to audit all DPLLs)
 * @param[in]		opp_id: OPP ID
 *				(use OPP54XX_ID_MAX to audit all OPPs)
 * @param[in]		curr_opp: audit current OPP only (=1) or all OPPs (=0)
 * @param[in,out]	err_nbr: audit error number
 * @param[in,out]	wng_nbr: audit warning number
 * @DESCRIPTION		audit DPLL Configuration
 *//*------------------------------------------------------------------------ */
int audit54xx_dpll(FILE *stream, dpll54xx_id dpll_id, opp54xx_id opp_id,
	unsigned short curr_opp, unsigned int *err_nbr, unsigned int *wng_nbr)
{
	int ret = 0;
	char s[256];
	char logfilename[256];
	FILE *fp;
	unsigned int row;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	char prev_gov[CPUFREQ_GOV_MAX_NAME_LENGTH] = "";
	char prev_gov2[CPUFREQ_GOV_MAX_NAME_LENGTH] = "";
	opp54xx_id opp;
	double freq_mpu;
	unsigned int _err_nbr = 0, _wng_nbr = 0;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(dpll_id, DPLL54XX_ID_MAX + 1, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(opp_id, OPP54XX_ID_MAX + 1, OMAPCONF_ERR_ARG);
	CHECK_ARG_LESS_THAN(curr_opp, 2, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(err_nbr, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(wng_nbr, OMAPCONF_ERR_ARG);

	*err_nbr = 0;
	*wng_nbr = 0;

	/* Create audit report log file */
	strcpy(logfilename, "dpll_audit_report.txt");
	fp = workdir_fopen(logfilename, "w+");
	if (fp == NULL) {
		fprintf(stderr, "Could not create %s file!\n\n", logfilename);
		return 0;
	}

	fprintf(fp,
		"OMAPCONF DPLL Configuration Audit Detailed Log:\n\n");
	omapconf_revision_show(fp);
	chips_info_show(fp, 1);
	release_info_show(fp);

	if (curr_opp == 1) {
		ret = dpll54xx_audit(dpll_id, opp_id, fp, err_nbr, wng_nbr);
		if (ret != 0)
			goto audit54xx_dpll_end;
		ret = dpll54xx_audit(dpll_id, opp_id, stream, err_nbr, wng_nbr);
		if (ret != 0)
			goto audit54xx_dpll_end;

		if (*err_nbr == 0)
			sprintf(s, "SUCCESS! DPLL Configuration audit "
				"completed with 0 error (%u warning(s))"
				".\n\n", *wng_nbr);
		else
			sprintf(s, "FAILED! DPLL Configuration audit "
				"completed with %u error(s) and %u "
				"warning(s).\n\n", *err_nbr, *wng_nbr);

		if (stream != NULL) {
			fprintf(stream, "Audit details saved in %s file.\n\n\n",
				logfilename);
			fputs(s, stream);
		}
		fputs(s, fp);
		ret = 0;
		goto audit54xx_dpll_end;
	}

	/* Save current governor (will be altered by cpufreq_set() call) */
	if (cpufreq_scaling_governor_get(prev_gov) == NULL) {
		ret = OMAPCONF_ERR_NOT_AVAILABLE;
		goto audit54xx_dpll_end;
	}

	/* Retrieve number of available MPU OPPs */
	if (cpufreq_opp_nbr_get() == 0) {
		ret = OMAPCONF_ERR_NOT_AVAILABLE;
		goto audit54xx_dpll_end;
	}

	row = 0;
	autoadjust_table_init(table);
	snprintf(table[row][0], TABLE_MAX_ELT_LEN,
		"DPLL Configuration AUDIT Summary");
	autoadjust_table_strncpy(table, row, 1, "Audit STATUS");
	row++;

	for (opp = OPP54XX_LOW; (unsigned int) opp <= cpufreq_opp_nbr_get();
		opp++) {
		_err_nbr = 0;
		_wng_nbr = 0;

		/* Set MPU OPP */
		freq_mpu = mod54xx_por_clk_rate_get(OMAP5_MPU, opp);
		if (freq_mpu < 0) {
			err_internal_msg_show();
			goto audit54xx_dpll_end;
		}
		ret = cpufreq_set((unsigned int) (freq_mpu * 1000));
		if (ret != 0) {
			err_internal_msg_show();
			goto audit54xx_dpll_end;
		}

		fprintf(fp, "DPLLs Configuration Audit at MPU %s:\n\n",
			opp54xx_name_get(opp));
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "At MPU %s",
			opp54xx_name_get(opp));

		/* Run audit at this OPP */
		ret = dpll54xx_audit(dpll_id, OPP54XX_ID_MAX, fp,
			&_err_nbr, &_wng_nbr);
		if (ret != 0) {
			err_internal_msg_show();
			goto audit54xx_dpll_end;
		}

		if (_err_nbr == 0)
			snprintf(table[row][1], TABLE_MAX_ELT_LEN,
				"PASS (0 error, %u warning(s))", _wng_nbr);
		else
			snprintf(table[row][1], TABLE_MAX_ELT_LEN,
				"FAIL (%u error, %u warning(s))",
				_err_nbr, _wng_nbr);
		(*err_nbr) += _err_nbr;
		(*wng_nbr) += _wng_nbr;
		row++;
		fprintf(fp, "\n\n\n");
	}

	/* Report final audit status */
	autoadjust_table_fprint(fp, table, row, 2);
	sprintf(s, "NB: DPLL IVA may not have been audited accross all "
		"IVA OPPs (no kernel interface to control IVA OPP "
		"available).\n\n");
	fputs(s, fp);
	if (stream != NULL) {
		autoadjust_table_fprint(stream, table, row, 2);
		fputs(s, stream);
	}
	if (*err_nbr == 0)
		sprintf(s, "\nSUCCESS! DPLLs Configuration "
			"audit completed with 0 error (%u warning(s))"
			".\n\n\n", *wng_nbr);
	else
		sprintf(s, "\nFAILED! DPLLs Configuration "
			"audit completed with %u error(s) and %u "
			"warning(s).\n\n\n", *err_nbr, *wng_nbr);
	fputs(s, fp);
	if (stream != NULL) {
		fprintf(stream, "DPLLs Configuration audit details saved "
			"in %s file.\n", logfilename);
		fputs(s, stream);
	}


audit54xx_dpll_end:
	/* Restore CPUFreq governor */
	if (strlen(prev_gov) != 0)
		cpufreq_scaling_governor_set(prev_gov, prev_gov2);
	/* Close opened file */
	if (fp != NULL)
		fclose(fp);
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		audit54xx_full
 * @BRIEF		full OMAP5 power configuration audit
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_INTERNAL
 * @param[in,out]	stream: output file - NULL: no output (silent)
 * @param[in,out]	logfile: audit report file name
 *			(revert to default "full_audit_report.txt" if NULL)
 * @param[in,out]	err_nbr: pointer to return audit error number
 * @param[in,out]	wng_nbr: pointer to return audit warning number
 * @DESCRIPTION		full OMAP5 power configuration audit
 *			(DPLL + SYSCONFIG + CLKSPEED + STATICDEP + IO).
 *//*------------------------------------------------------------------------ */
int audit54xx_full(FILE *stream, char *logfile, unsigned int *err_nbr,
	unsigned int *wng_nbr)
{
	int ret;

	unsigned int dplls_err_nbr = 0, dplls_wng_nbr = 0;
	unsigned int syscfg_err_nbr = 0, syscfg_wng_nbr = 0;
	unsigned int clkspeed_err_nbr = 0, clkspeed_wng_nbr = 0;
	unsigned int statdep_err_nbr = 0, statdep_wng_nbr = 0;
	unsigned int io_err_nbr = 0, io_wng_nbr = 0;
	unsigned int row = 0;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	char *workdir;
	char s[256];
	FILE *fp;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_NULL_ARG(err_nbr, OMAPCONF_ERR_ARG);
	CHECK_NULL_ARG(wng_nbr, OMAPCONF_ERR_ARG);

	*err_nbr = 0;
	*wng_nbr = 0;

	/* Create audit report log file */
	if (logfile != NULL) {
		strncpy(s, logfile, 255);
	} else {
		workdir = workdir_get();
		if (workdir != NULL) {
			strcpy(s, workdir);

			strcat(s, "full_audit_report.txt");
		} else {
			return OMAPCONF_ERR_INTERNAL;
		}
	}

	fp = fopen(s, "w+");
	if (fp == NULL) {
		fprintf(stderr,
			"omapconf: could not create \"%s\" full audit log file!\n\n",
			s);
		return OMAPCONF_ERR_INTERNAL;
	}
	fprintf(fp,
		"OMAPCONF Full Power Configuration Audit Detailed Log:\n\n");
	omapconf_revision_show(fp);
	chips_info_show(fp, 1);
	release_info_show(fp);

	snprintf(table[row][0], TABLE_MAX_ELT_LEN,
		"Full Power Configuration AUDIT Summary");
	snprintf(table[row][1], TABLE_MAX_ELT_LEN,
		"STATUS");
	row++;

	ret = dpll54xx_audit(DPLL54XX_ID_MAX, OPP54XX_ID_MAX, fp,
		&dplls_err_nbr, &dplls_wng_nbr);
	if (ret != 0)
		return ret;
	fputs("\n\n\n", fp);
	snprintf(table[row][0], TABLE_MAX_ELT_LEN,
		"DPLLs Configuration Audit");
	if (dplls_err_nbr == 0)
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"PASS (0 error, %u warning(s))", dplls_wng_nbr);
	else
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"FAIL (%u error, %u warning(s))",
			dplls_err_nbr, dplls_wng_nbr);
	row++;
	(*err_nbr) += dplls_err_nbr;
	(*wng_nbr) += dplls_wng_nbr;

	ret = audit54xx_sysconfig(fp,
		&syscfg_err_nbr, &syscfg_wng_nbr);
	if (ret != 0)
		return ret;
	fputs("\n\n\n", fp);
	snprintf(table[row][0], TABLE_MAX_ELT_LEN,
		"SYSCONFIG IP Registers Audit");
	if (syscfg_err_nbr == 0)
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"PASS (0 error, %u warning(s))", syscfg_wng_nbr);
	else
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"FAIL (%u error, %u warning(s))",
			syscfg_err_nbr, syscfg_wng_nbr);
	row++;
	(*err_nbr) += syscfg_err_nbr;
	(*wng_nbr) += syscfg_wng_nbr;

	ret = audit54xx_clkspeed(fp, 0,
		&clkspeed_err_nbr, &clkspeed_wng_nbr);
	if (ret != 0)
		return ret;
	fputs("\n\n\n", fp);
	snprintf(table[row][0], TABLE_MAX_ELT_LEN,
		"Clocks Speed Audit");
	if (clkspeed_err_nbr == 0)
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"PASS (0 error, %u warning(s))", clkspeed_wng_nbr);
	else
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"FAIL (%u error, %u warning(s))",
			clkspeed_err_nbr, clkspeed_wng_nbr);
	row++;
	(*err_nbr) += clkspeed_err_nbr;
	(*wng_nbr) += clkspeed_wng_nbr;

	ret = clkdmdep54xx_audit(fp,
		&statdep_err_nbr, &statdep_wng_nbr);
	if (ret != 0)
		return ret;
	fputs("\n\n\n", fp);
	snprintf(table[row][0], TABLE_MAX_ELT_LEN,
		"Static Dependencies Audit");
	if (statdep_err_nbr == 0)
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"PASS (0 error, %u warning(s))", statdep_wng_nbr);
	else
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"FAIL (%u error, %u warning(s))",
			statdep_err_nbr, statdep_wng_nbr);
	row++;
	(*err_nbr) += statdep_err_nbr;
	(*wng_nbr) += statdep_wng_nbr;

	ret = ctrlmod54xx_io_audit(fp,
		&io_err_nbr, &io_wng_nbr);
	if (ret != 0)
		return ret;
	fputs("\n\n\n", fp);
	snprintf(table[row][0], TABLE_MAX_ELT_LEN,
		"IO PADCONF Audit");
	if (io_err_nbr == 0)
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"PASS (0 error, %u warning(s))", io_wng_nbr);
	else
		snprintf(table[row][1], TABLE_MAX_ELT_LEN,
			"FAIL (%u error, %u warning(s))",
			io_err_nbr, io_wng_nbr);
	row++;
	(*err_nbr) += io_err_nbr;
	(*wng_nbr) += io_wng_nbr;

	if (stream != NULL) {
		autoadjust_table_fprint(stream, table, row, 2);
		fprintf(stream, "Audit details saved in '%s' file.\n\n\n", s);
	}
	autoadjust_table_fprint(fp, table, row, 2);

	if (err_nbr == 0) {
		sprintf(s,
			"SUCCESS! Full Power Configuration Audit completed with 0 error (%u warning(s))\n\n",
			*wng_nbr);
	} else {
		sprintf(s,
			"FAILED! Full Power Configuration Audit completed with %u error(s) and %u warning(s).\n\n",
			*err_nbr, *wng_nbr);
	}
	if (stream != NULL)
		fputs(s, stdout);
	fputs(s, fp);

	fclose(fp);
	return 0;
}
