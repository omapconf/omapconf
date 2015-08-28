/*
 *
 * @Component			OMAPCONF
 * @Filename			uc_audit44xx.c
 * @Description			OMAP4 Use-Case Audit Functions
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


#include <uc_audit44xx.h>
#include <lib_android.h>
#include <lib44xx.h>
#include <lib.h>
#include <help.h>
#include <autoadjust_table.h>
#include <cpuinfo.h>
#include <revision.h>
#include <audit44xx.h>
#include <clock44xx.h>
#include <clkdm44xx.h>
#include <pwrdm44xx.h>
#include <voltdm44xx.h>
#include <dpll44xx.h>
#include <dep44xx.h>
#include <abe44xx.h>
#include <ivahd44xx.h>
#include <dsp44xx.h>
#include <gfx44xx.h>
#include <dss44xx.h>
#include <cam44xx.h>
#include <l3init44xx.h>
#include <mpu44xx.h>
#include <per44xx.h>
#include <core44xx.h>
#include <smartreflex44xx.h>
#include <cstate.h>
#include <unistd.h>
#include <cpufreq.h>


/* #define UC_AUDIT44XX_DEBUG */
#ifdef UC_AUDIT44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

typedef enum {
	OMAP4_UC_OS_IDLE,
	OMAP4_UC_MP3_PLAYBACK,
	OMAP4_UC_AVRECORD_1080P,
	OMAP4_UC_AVPLAYBACK_720P,
	OMAP4_UC_AVPLAYBACK_1080P,
	OMAP4_UC_HOME_SCREEN,
	OMAP4_UC_MAX
} omap4_use_case_id;

static const char omap4_use_case_name_table[OMAP4_UC_MAX][20] = {
	"OS IDLE",
	"MP3 PLAYBACK",
	"AV RECORD 1080P",
	"AV PLAYBACK 720P",
	"AV PLAYBACK 1080P",
	"HOME SCREEN"};

static char omap4_use_case_summary_filename_table[OMAP4_UC_MAX][64] = {
	"os_idle_uc_audit_summary.txt",
	"mp3_playback_uc_audit_summary.txt",
	"avrecord_1080p_uc_audit_summary.txt",
	"avplayback_720p_uc_audit_summary.txt",
	"avplayback_1080p_uc_audit_summary.txt",
	"home_screen_uc_audit_summary.txt"};

static char omap4_use_case_details_filename_table[OMAP4_UC_MAX][64] = {
	"os_idle_uc_audit_details.txt",
	"mp3_playback_uc_audit_details.txt",
	"avrecord_1080p_uc_audit_details.txt",
	"avplayback_720p_uc_audit_details.txt",
	"avplayback_1080p_uc_audit_details.txt",
	"home_screen_uc_audit_details.txt"};

static const opp44xx_id omap4_gb_por_opp_table[OMAP4_VD_ID_MAX][OMAP4_UC_MAX] = {
	{OMAP4_OPP100, OMAP4_OPP100, OMAP4_OPP100, OMAP4_OPP100, OMAP4_OPP100, OMAP4_OPP100},
	{OMAP4_OPP50, OMAP4_OPPDPLL_CASC, OMAP4_OPP50, OMAP4_OPP50, OMAP4_OPP50, OMAP4_OPP50},
	{OMAP4_OPP50, OMAP4_OPPDPLL_CASC, OMAP4_OPP100, OMAP4_OPP50, OMAP4_OPP100, OMAP4_OPP50},
	{OMAP4_OPP50, OMAP4_OPPDPLL_CASC, OMAP4_OPP100, OMAP4_OPP50, OMAP4_OPP100, OMAP4_OPP50}, };

static const opp44xx_id omap4_ics_por_opp_table[OMAP4_VD_ID_MAX][OMAP4_UC_MAX] = {
	{OMAP4_OPP100, OMAP4_OPP100, OMAP4_OPP100, OMAP4_OPP100, OMAP4_OPP100, OMAP4_OPP100},
	{OMAP4_OPP50, OMAP4_OPPDPLL_CASC, OMAP4_OPP50, OMAP4_OPP50, OMAP4_OPP50, OMAP4_OPP50},
	{OMAP4_OPP50, OMAP4_OPPDPLL_CASC, OMAP4_OPP100, OMAP4_OPP50, OMAP4_OPP100, OMAP4_OPP50},
	{OMAP4_OPP50, OMAP4_OPPDPLL_CASC, OMAP4_OPP100, OMAP4_OPP50, OMAP4_OPP100, OMAP4_OPP50} };

static const opp44xx_id omap4470_blaze_ics_por_opp_table[OMAP4_VD_ID_MAX][OMAP4_UC_MAX] = {
	{OMAP4_OPP100, OMAP4_OPP100, OMAP4_OPP100, OMAP4_OPP100, OMAP4_OPP100, OMAP4_OPP100},
	{OMAP4_OPP50, OMAP4_OPP50, OMAP4_OPP50, OMAP4_OPP50, OMAP4_OPP50, OMAP4_OPP50},
	{OMAP4_OPP50, OMAP4_OPP50, OMAP4_OPP100, OMAP4_OPP50, OMAP4_OPP100, OMAP4_OPP50},
	{OMAP447X_OPP50_LOW, OMAP447X_OPP50_LOW, OMAP447X_OPP100_LOW, OMAP447X_OPP50_LOW, OMAP447X_OPP100_LOW, OMAP447X_OPP50_LOW} };


static const opp44xx_id omap4470_tablet_ics_por_opp_table[OMAP4_VD_ID_MAX][OMAP4_UC_MAX] = {
	{OMAP4_OPP100, OMAP4_OPP100, OMAP4_OPP100, OMAP4_OPP100, OMAP4_OPP100, OMAP4_OPP100},
	{OMAP4_OPP50, OMAP4_OPP50, OMAP4_OPP50, OMAP4_OPP50, OMAP4_OPP50, OMAP4_OPP50},
	{OMAP4_OPP50, OMAP4_OPP50, OMAP4_OPP100, OMAP4_OPP50, OMAP4_OPP100, OMAP4_OPP50},
	{OMAP447X_OPP50_HIGH, OMAP447X_OPP50_HIGH, OMAP447X_OPP119_HIGH, OMAP447X_OPP50_HIGH, OMAP447X_OPP119_HIGH, OMAP447X_OPP50_HIGH} };


static const pwrdm_state
	omap4_por_power_domain_state_table[OMAP4_PD_ID_MAX][OMAP4_UC_MAX] = {
	{PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE}, /* OMAP4_PD_WKUP */
	{PWRDM_OFF_STATE, PWRDM_OFF_STATE, PWRDM_OFF_STATE, PWRDM_OFF_STATE, PWRDM_OFF_STATE, PWRDM_OFF_STATE}, /* OMAP4_PD_EMU */
	{PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE}, /* OMAP4_PD_MPU */
	{PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE}, /* OMAP4_PD_ALWON_MPU */
	{PWRDM_OFF_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_OFF_STATE}, /* OMAP4_PD_ABE */
	{PWRDM_OFF_STATE, PWRDM_OFF_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_OFF_STATE}, /* OMAP4_PD_IVA_HD */
	{PWRDM_OFF_STATE, PWRDM_OFF_STATE, PWRDM_OFF_STATE, PWRDM_OFF_STATE, PWRDM_OFF_STATE, PWRDM_OFF_STATE}, /* OMAP4_PD_DSP */
	{PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_OFF_STATE}, /* OMAP4_PD_ALWON_IVA */
	{PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE}, /* OMAP4_PD_ALWON_CORE */
	{PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE}, /* OMAP4_PD_CORE */
	{PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE}, /* OMAP4_PD_STD_EFUSE */
	{PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE}, /* OMAP4_PD_CUST_EFUSE */
	{PWRDM_OFF_STATE, PWRDM_OFF_STATE, PWRDM_ON_STATE, PWRDM_OFF_STATE, PWRDM_OFF_STATE, PWRDM_OFF_STATE}, /* OMAP4_PD_CAM */
	{PWRDM_OFF_STATE, PWRDM_OFF_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE}, /* OMAP4_PD_DSS */
	{PWRDM_OFF_STATE, PWRDM_OFF_STATE, PWRDM_OFF_STATE, PWRDM_OFF_STATE, PWRDM_OFF_STATE, PWRDM_OFF_STATE}, /* OMAP4_PD_GFX */
	{PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE, PWRDM_ON_STATE}, /* OMAP4_PD_L3_INIT */
	{PWRDM_OFF_STATE, PWRDM_OFF_STATE, PWRDM_OFF_STATE, PWRDM_OFF_STATE, PWRDM_OFF_STATE, PWRDM_OFF_STATE} }; /* OMAP4_PD_L4_PER */


static const clkdm_status
	omap4_por_clock_domain_status_table[OMAP4_CD_ID_MAX][OMAP4_UC_MAX] = {
	{CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_RUNNING}, /* OMAP4_CD_WKUP */
	{CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED}, /* OMAP4_CD_EMU */
	{CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_RUNNING}, /* OMAP4_CD_MPU */
	{CLKDM_GATED, CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_GATED}, /* OMAP4_CD_ABE */
	{CLKDM_GATED, CLKDM_GATED, CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_GATED}, /* OMAP4_CD_IVA_HD */
	{CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED}, /* OMAP4_CD_DSP */
	{CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_RUNNING}, /* OMAP4_CD_AO_L4 */
	{CLKDM_GATED, CLKDM_GATED, CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_GATED}, /* OMAP4_CD_L4CFG */
	{CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED}, /* OMAP4_CD_C2C */
	{CLKDM_GATED, CLKDM_RUNNING, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED}, /* OMAP4_CD_DMA */
	{CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED}, /* OMAP4_CD_MPU_M3 */
	{CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_RUNNING}, /* OMAP4_CD_L3_1 */
	{CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_RUNNING}, /* OMAP4_CD_L3_2 */
	{CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED}, /* OMAP4_CD_L3_INSTR */
	{CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_RUNNING}, /* OMAP4_CD_EMIF */
	{CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED}, /* OMAP4_CD_STD_EFUSE */
	{CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED}, /* OMAP4_CD_CUST_EFUSE */
	{CLKDM_GATED, CLKDM_GATED, CLKDM_RUNNING, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED}, /* OMAP4_CD_CAM */
	{CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_RUNNING}, /* OMAP4_CD_DSS */
	{CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED}, /* OMAP4_CD_GFX */
	{CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_RUNNING, CLKDM_RUNNING}, /* OMAP4_CD_L3_INIT */
	{CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED}, /* OMAP4_CD_L4_SEC */
	{CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED, CLKDM_GATED} }; /* OMAP4_CD_L4_PER */


static const pwrdm_state
	omap4_por_hotplug_cpu1_power_state_table[OMAP4_UC_MAX] = {
		PWRDM_OFF_STATE,
		PWRDM_OFF_STATE,
		PWRDM_OFF_STATE,
		PWRDM_OFF_STATE,
		PWRDM_OFF_STATE,
		PWRDM_OFF_STATE};


static const pwrdm_state
	omap4_por_interactive_cpu1_power_state_table[OMAP4_UC_MAX] = {
		PWRDM_ON_STATE,
		PWRDM_ON_STATE,
		PWRDM_ON_STATE,
		PWRDM_ON_STATE,
		PWRDM_ON_STATE,
		PWRDM_ON_STATE};


static const dpll_status
	omap4_gb_por_dpll_status_table[DPLL44XX_ID_MAX][OMAP4_UC_MAX] = {
	{DPLL_STATUS_LOCKED, DPLL_STATUS_BYPASSED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED}, /* DPLL44XX_MPU */
	{DPLL_STATUS_STOPPED, DPLL_STATUS_BYPASSED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_STOPPED}, /* DPLL44XX_IVA */
	{DPLL_STATUS_LOCKED, DPLL_STATUS_BYPASSED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED}, /* DPLL44XX_CORE */
	{DPLL_STATUS_LOCKED, DPLL_STATUS_BYPASSED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED}, /* DPLL44XX_PER */
	{DPLL_STATUS_STOPPED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_STOPPED}, /* DPLL44XX_ABE */
	{DPLL_STATUS_STOPPED, DPLL_STATUS_STOPPED, DPLL_STATUS_STOPPED, DPLL_STATUS_STOPPED, DPLL_STATUS_STOPPED, DPLL_STATUS_STOPPED}, /* DPLL44XX_USB */
	{DPLL_STATUS_STOPPED, DPLL_STATUS_STOPPED, DPLL_STATUS_STOPPED, DPLL_STATUS_STOPPED, DPLL_STATUS_STOPPED, DPLL_STATUS_STOPPED}, /* DPLL44XX_UNIPRO */
	{DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED} }; /* DPLL44XX_DDRPHY */


static const dpll_status
	omap4_ics_por_dpll_status_table[DPLL44XX_ID_MAX][OMAP4_UC_MAX] = {
	{DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED}, /* DPLL44XX_MPU */
	{DPLL_STATUS_STOPPED, DPLL_STATUS_STOPPED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_STOPPED}, /* DPLL44XX_IVA */
	{DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED}, /* DPLL44XX_CORE */
	{DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED}, /* DPLL44XX_PER */
	{DPLL_STATUS_STOPPED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_STOPPED}, /* DPLL44XX_ABE */
	{DPLL_STATUS_STOPPED, DPLL_STATUS_STOPPED, DPLL_STATUS_STOPPED, DPLL_STATUS_STOPPED, DPLL_STATUS_STOPPED, DPLL_STATUS_STOPPED}, /* DPLL44XX_USB */
	{DPLL_STATUS_STOPPED, DPLL_STATUS_STOPPED, DPLL_STATUS_STOPPED, DPLL_STATUS_STOPPED, DPLL_STATUS_STOPPED, DPLL_STATUS_STOPPED}, /* DPLL44XX_UNIPRO */
	{DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED, DPLL_STATUS_LOCKED} }; /* DPLL44XX_DDRPHY */


static const unsigned int
	omap4_gb_por_cstate_table[OMAP4_UC_MAX] = {
	4, 3, 1, 2, 2, 4};

static const unsigned int
	omap4_ics_por_cstate_table[OMAP4_UC_MAX] = {
	4, 4, 1, 1, 1, 4};



static const char pass[5] = "Pass";
static const char fail[5] = "FAIL";
static const char ignore[12] = "Ignored (1)";
static const char ignore2[12] = "Ignored (2)";
static const char ignore3[12] = "Ignored (3)";
static const char warning[8] = "Warning";


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		use_case_name_get
 * @BRIEF		return use case name
 * @RETURNS		use case name on success
 *			NULL in case of error
 * @param[in]		id: valid use case ID
 * @DESCRIPTION		return use case name
 *//*------------------------------------------------------------------------ */
const char *use_case_name_get(omap4_use_case_id id)
{
	CHECK_ARG_LESS_THAN(id, OMAP4_UC_MAX, NULL);

	return omap4_use_case_name_table[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		por44xx_opp_get
 * @BRIEF		return PoR OPP of a given voltage domain, for a given
 *			use-case
 * @RETURNS		PoR OPP for the given use-case for the given voltage
 *			domain
 *			OMAP4_OPP_MAX in case of error
 * @param[in]		id: voltage domain ID
 * @param[in]		uc_id: use-case ID
 * @DESCRIPTION		return PoR OPP of a given voltage domain, for a given
 *			use-case
 *//*------------------------------------------------------------------------ */
opp44xx_id por_opp44xx_get(voltdm44xx_id id, omap4_use_case_id uc_id)
{
	opp44xx_id opp_por;
	android_pastry_id pastry;
	#ifdef UC_AUDIT44XX_DEBUG
	char vname[VOLTDM44XX_MAX_NAME_LENGTH];
	char oname[OPP44XX_MAX_NAME_LENGTH];
	#endif

	CHECK_CPU(44xx, OPP44XX_ID_MAX);
	CHECK_ARG_LESS_THAN(id, OMAP4_VD_ID_MAX, OPP44XX_ID_MAX);
	CHECK_ARG_LESS_THAN(uc_id, OMAP4_UC_MAX, OPP44XX_ID_MAX);

	pastry = android_pastry_get();
	if ((pastry == PASTRY_UNKNOWN) || (pastry == PASTRY_ID_MAX)) {
		/* FIXME: find expected OPP for Generic Linux */
		opp_por = OPP44XX_ID_MAX;
	} else if (pastry < PASTRY_ICS) {
		opp_por = omap4_gb_por_opp_table[id][uc_id];
	} else {
		if (!cpu_is_omap4470())
			opp_por = omap4_ics_por_opp_table[id][uc_id];
		else if (((unsigned int) clk44xx_get_clock_speed(OMAP4_L3_ICLK1, 1) == 100) ||
			((unsigned int) clk44xx_get_clock_speed(OMAP4_L3_ICLK1, 1) == 200))
			opp_por = omap4470_blaze_ics_por_opp_table[id][uc_id];
		else
			opp_por = omap4470_tablet_ics_por_opp_table[id][uc_id];
	}

	#ifdef UC_AUDIT44XX_DEBUG
	voltdm44xx_opp2string(oname, opp_por, id);
	voltdm44xx_get_name(id, vname);
	#endif

	dprintf("%s(%s, %s): PoR OPP = %s\n", __func__, vname,
		use_case_name_get(uc_id), oname);

	return opp_por;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		opp_audit44xx
 * @BRIEF		OMAP4 OPP audit.
 * @RETURNS		pointer to global pass string in case of successfull
 *			audit
 *			pointer to global fail string in case of failing audit
 *			pointer to global warning string in case of internal
 *			error
 * @param[in]		vd_id: voltage domain ID
 * @param[in]		uc_id: use-case ID
 * @param[in,out]	opp: current opp (returned)
 * @param[in,out]	opp_por: expected OPP (returned)
 * @param[in,out]	err_nbr: error number (returned)
 * @param[in,out]	wng_nbr: warning number (returned)
 * @DESCRIPTION		OMAP4 OPP audit.
 *//*------------------------------------------------------------------------ */
char *opp_audit44xx(voltdm44xx_id vd_id,
	omap4_use_case_id uc_id, opp44xx_id *opp, opp44xx_id *opp_por,
	unsigned int *err_nbr, unsigned int *wng_nbr)
{
	int ret;
	#ifdef UC_AUDIT44XX_DEBUG
	char s_opp[10];
	char s_opp_por[10];
	char voltdm_name[VOLTDM44XX_MAX_NAME_LENGTH];
	#endif

	if (!cpu_is_omap44xx())
		return (char *) warning;
	if (uc_id >= OMAP4_UC_MAX)
		return (char *) warning;
	if ((opp == NULL) || (opp_por == NULL) ||
		(err_nbr == NULL) || (wng_nbr == NULL)) {
		(*wng_nbr)++;
		return (char *) warning;
	}
	*opp = OPP44XX_ID_MAX;
	*opp_por = OPP44XX_ID_MAX;
	*err_nbr = 0;
	*wng_nbr = 0;

	/* Get current OPP */
	ret = voltdm44xx_get_opp(vd_id, opp);
	if (ret == OMAPCONF_ERR_ARG) {
		(*wng_nbr)++;
		return (char *) warning;
	} else if (ret == OMAPCONF_ERR_NOT_AVAILABLE) {
		(*err_nbr)++;
		return (char *) fail;
	}

	/* Get expected OPP for this particular UC */
	*opp_por = por_opp44xx_get(vd_id, uc_id);
	if (*opp_por == OPP44XX_ID_MAX) {
		(*wng_nbr)++;
		return (char *) warning;
	}

	#ifdef UC_AUDIT44XX_DEBUG
	voltdm44xx_opp2string(s_opp, *opp, vd_id);
	voltdm44xx_opp2string(s_opp_por, *opp_por, vd_id);
	#endif
	dprintf("%s(): VD is %s, UC is %s Current OPP is %s POR OPP is %s\n",
		__func__, voltdm44xx_get_name(vd_id, voltdm_name),
		omap4_use_case_name_table[uc_id], s_opp, s_opp_por);
	if (*opp != *opp_por) {
		(*err_nbr)++;
		return (char *) fail;
	} else {
		return (char *) pass;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		voltage_audit44xx
 * @BRIEF		OMAP4 Voltage audit.
 * @RETURNS		pointer to global pass string in case of successfull
 *			audit
 *			pointer to global fail string in case of failing audit
 *			pointer to global warning string in case of internal
 *			error
 * @param[in]		vd_id: voltage domain ID
 * @param[in]		uc_id: use-case ID
 * @param[in,out]	volt: current voltage (returned)
 * @param[in,out]	volt_por: expected voltage (returned)
 * @param[in,out]	err_nbr: error number (returned)
 * @param[in,out]	wng_nbr: warning number (returned)
 * @DESCRIPTION		OMAP4 Voltage audit.
 *//*------------------------------------------------------------------------ */
char *voltage_audit44xx(voltdm44xx_id vd_id,
	omap4_use_case_id uc_id, double *volt, double *volt_por,
	unsigned int *err_nbr, unsigned int *wng_nbr)
{
	opp44xx_id opp_por;
	int ret;
	#ifdef UC_AUDIT44XX_DEBUG
	char voltdm_name[VOLTDM44XX_MAX_NAME_LENGTH];
	#endif

	if ((volt == NULL) || (volt_por == NULL) ||
		(err_nbr == NULL) || (wng_nbr == NULL)) {
		(*wng_nbr)++;
		return (char *) warning;
	}
	*volt = 0.0;
	*volt_por = 0.0;
	*err_nbr = 0;
	*wng_nbr = 0;

	if (!cpu_is_omap44xx()) {
		(*wng_nbr)++;
		return (char *) warning;
	}
	if (uc_id >= OMAP4_UC_MAX) {
		(*wng_nbr)++;
		return (char *) warning;
	}

	/* Get expected OPP for this particular UC */
	opp_por = por_opp44xx_get(vd_id, uc_id);
	if (opp_por == OPP44XX_ID_MAX) {
		(*wng_nbr)++;
		return (char *) warning;
	}
	/* Get nominal voltage for this particular UC */
	*volt_por = voltdm44xx_por_nominal_voltage_get(vd_id, opp_por);
	if (*volt_por <= 0) {
		(*wng_nbr)++;
		return (char *) warning;
	}

	/* Get current voltage */
	ret = voltdm44xx_get_voltage(vd_id, volt);
	if (ret != 0) {
		(*wng_nbr)++;
		return (char *) warning;
	}

	dprintf("%s(): VD is %s, UC is %s Current voltage is %lf "
		"MAX POR voltage is %lf\n", __func__,
		voltdm44xx_get_name(vd_id, voltdm_name),
		omap4_use_case_name_table[uc_id], *volt, *volt_por);
	if (*volt > *volt_por) {
		(*err_nbr)++;
		return (char *) fail;
	} else {
		return (char *) pass;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		ret_voltage_audit44xx
 * @BRIEF		OMAP4 RETENTION Voltage audit.
 * @RETURNS		pointer to global pass string in case of successfull
 *			audit
 *			pointer to global fail string in case of failing audit
 *			pointer to global warning string in case of internal
 *			error
 * @param[in]		vd_id: voltage domain ID
 * @param[in,out]	volt: programmed retention voltage (returned)
 * @param[in,out]	volt_por: expected retention voltage (returned)
 * @param[in,out]	err_nbr: error number (returned)
 * @param[in,out]	wng_nbr: warning number (returned)
 * @DESCRIPTION		OMAP4 RETENTION Voltage audit.
 *//*------------------------------------------------------------------------ */
char *ret_voltage_audit44xx(voltdm44xx_id vd_id,
	double *volt, double *volt_por,
	unsigned int *err_nbr, unsigned int *wng_nbr)
{
	int ret;
	#ifdef UC_AUDIT44XX_DEBUG
	char voltdm_name[VOLTDM44XX_MAX_NAME_LENGTH];
	#endif

	if ((volt == NULL) || (volt_por == NULL) ||
		(err_nbr == NULL) || (wng_nbr == NULL)) {
		(*wng_nbr)++;
		return (char *) warning;
	}
	*volt = 0.0;
	*volt_por = 0.0;
	*err_nbr = 0;
	*wng_nbr = 0;

	if (!cpu_is_omap44xx()) {
		(*wng_nbr)++;
		return (char *) warning;
	}

	/* Get expected retention voltage */
	*volt_por = voltdm44xx_por_retention_voltage_get(vd_id);
	if (*volt_por <= 0.0) {
		(*wng_nbr)++;
		return (char *) warning;
	}

	/* Get programmed retention voltage */
	ret = voltdm44xx_get_voltage_by_type(vd_id,
		OMAP4_RETENTION_VOLTAGE, volt);
	if (ret != 0) {
		(*wng_nbr)++;
		return (char *) warning;
	}

	dprintf("%s(): VD is %s, Programmed RET voltage is %lfV, "
		"POR RET voltage is %lfV.\n", __func__,
		voltdm44xx_get_name(vd_id, voltdm_name), *volt, *volt_por);
	if (*volt != *volt_por) {
		(*err_nbr)++;
		return (char *) fail;
	} else {
		return (char *) pass;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pwrdm_state_audit44xx
 * @BRIEF		Power Domain State audit.
 * @RETURNS		pointer to global pass string in case of successfull
 *			audit
 *			pointer to global fail string in case of failing audit
 *			pointer to global warning string in case of internal
 *			error
 * @param[in]		pd_id: Power Domain ID
 * @param[in]		uc_id: use-case ID
 * @param[in,out]	state: power domain state (returned)
 * @param[in,out]	state_por: expected power domain state (returned)
 * @param[in,out]	err_nbr: error number (returned)
 * @param[in,out]	wng_nbr: warning number (returned)
 * @DESCRIPTION		Power Domain State audit.
 *//*------------------------------------------------------------------------ */
char *pwrdm_state_audit44xx(pwrdm44xx_id pd_id,
	omap4_use_case_id uc_id,
	pwrdm_state *state, pwrdm_state *state_por,
	unsigned int *err_nbr, unsigned int *wng_nbr)
{
	int ret;
	#ifdef UC_AUDIT44XX_DEBUG
	char pwst[6];
	char pwst_por[6];
	char pwrdm_name[PWRDM44XX_MAX_NAME_LENGTH];
	#endif

	if ((state == NULL) || (state_por == NULL) ||
		(err_nbr == NULL) || (wng_nbr == NULL)) {
		(*wng_nbr)++;
		return (char *) warning;
	}
	*err_nbr = 0;
	*wng_nbr = 0;
	*state = PWRDM_STATE_MAX;
	*state_por = PWRDM_STATE_MAX;
	if (uc_id >= OMAP4_UC_MAX) {
		(*wng_nbr)++;
		return (char *) warning;
	}

	if (!cpu_is_omap44xx())
		return (char *) warning;

	/* Get power domain state */
	ret = pwrdm44xx_get_state(pd_id, state);
	if (ret != 0) {
		dprintf("%s(): error retrieving %s power domain state! (%d)\n",
			__func__, pwrdm44xx_get_name(pd_id, pwrdm_name), ret);
		(*wng_nbr)++;
		return (char *) warning;
	}

	/* Get expected power domain state */
	*state_por = omap4_por_power_domain_state_table[pd_id][uc_id];

	#ifdef UC_AUDIT44XX_DEBUG
	pwrdm_state2string(pwst, *state);
	pwrdm_state2string(pwst_por, *state_por);
	dprintf("%s(): PD is %s, state is %s POR state is %s\n", __func__,
		pwrdm44xx_get_name(pd_id, pwrdm_name), pwst, pwst_por);
	#endif

	if (*state != *state_por) {
		(*err_nbr)++;
		return (char *) fail;
	} else {
		return (char *) pass;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		clkdm_status_audit44xx
 * @BRIEF		Clock Domain Status audit.
 * @RETURNS		pointer to global pass string in case of successfull
 *			audit
 *			pointer to global fail string in case of failing audit
 *			pointer to global warning string in case of internal
 *			error
 * @param[in]		cd_id: Clock Domain ID
 * @param[in]		uc_id: use-case ID
 * @param[in,out]	status: clock domain status (returned)
 * @param[in,out]	status_por: expected clock domain status (returned)
 * @param[in,out]	err_nbr: error number (returned)
 * @param[in,out]	wng_nbr: warning number (returned)
 * @DESCRIPTION		Clock Domain Status audit.
 *//*------------------------------------------------------------------------ */
char *clkdm_status_audit44xx(clkdm44xx_id cd_id,
	omap4_use_case_id uc_id,
	clkdm_status *status, clkdm_status *status_por,
	unsigned int *err_nbr, unsigned int *wng_nbr)
{
	int ret;
	#ifdef UC_AUDIT44XX_DEBUG
	char clkdm_name[CLKDM44XX_MAX_NAME_LENGTH];
	#endif

	if ((status == NULL) || (status_por == NULL) ||
		(err_nbr == NULL) || (wng_nbr == NULL)) {
		(*wng_nbr)++;
		return (char *) warning;
	}
	*err_nbr = 0;
	*wng_nbr = 0;
	*status = CLKDM_STATUS_MAX;
	*status_por = CLKDM_STATUS_MAX;
	if (uc_id >= OMAP4_UC_MAX) {
		(*wng_nbr)++;
		return (char *) warning;
	}

	if (!cpu_is_omap44xx())
		return (char *) warning;

	/* Get clock domain status */
	ret = clkdm44xx_get_status(cd_id, status);
	if (ret != 0) {
		dprintf("%s(): error retrieving %s power domain state! (%d)\n",
			__func__, clkdm44xx_get_name(cd_id, clkdm_name), ret);
		(*wng_nbr)++;
		return (char *) warning;
	}

	/* Get expected clock domain status */
	*status_por = omap4_por_clock_domain_status_table[cd_id][uc_id];

	#ifdef UC_AUDIT44XX_DEBUG
	dprintf("%s(): CD is %s, status is %s POR state is %s\n", __func__,
		clkdm44xx_get_name(cd_id, clkdm_name),
			clkdm_status_name_get(*status),
			clkdm_status_name_get(*status_por));
	#endif

	if (*status != *status_por) {
		(*err_nbr)++;
		return (char *) fail;
	} else {
		return (char *) pass;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpu1_power_state_audit44xx
 * @BRIEF		CPU1 Power Status audit.
 * @RETURNS		pointer to global pass string in case of successfull
 *			audit
 *			pointer to global fail string in case of failing audit
 *			pointer to global warning string in case of internal
 *			error
 * @param[in]		uc_id: use-case ID
 * @param[in,out]	state: CPU1 power state (returned)
 * @param[in,out]	state_por: CPU1 expected power state (returned)
 * @param[in,out]	err_nbr: error number (returned)
 * @param[in,out]	wng_nbr: warning number (returned)
 * @DESCRIPTION		CPU1 Power Status audit.
 *//*------------------------------------------------------------------------ */
char *cpu1_power_state_audit44xx(omap4_use_case_id uc_id,
	pwrdm_state *state, pwrdm_state *state_por,
	unsigned int *err_nbr, unsigned int *wng_nbr)
{
	int ret;
	android_pastry_id pastry;
	#ifdef UC_AUDIT44XX_DEBUG
	char pwst[6];
	char pwst_por[6];
	#endif

	if ((state == NULL) || (state_por == NULL) ||
		(err_nbr == NULL) || (wng_nbr == NULL)) {
		(*wng_nbr)++;
		return (char *) warning;
	}
	*err_nbr = 0;
	*wng_nbr = 0;
	*state = PWRDM_STATE_MAX;
	*state_por = PWRDM_STATE_MAX;
	if (uc_id >= OMAP4_UC_MAX) {
		(*wng_nbr)++;
		return (char *) warning;
	}

	if (!cpu_is_omap44xx())
		return (char *) warning;

	/* Get power domain state */
	ret = cpu44xx_power_state_get(1, state);
	if (ret != 0) {
		dprintf(
			"%s(): error retrieving CPU1 power domain state! (%d)\n",
			__func__, ret);
		(*wng_nbr)++;
		return (char *) warning;
	}

	/* Get expected power domain state */
	pastry = android_pastry_get();
	if ((pastry == PASTRY_UNKNOWN) || (pastry == PASTRY_ID_MAX)) {
		/* FIXME: find expected OPP for Generic Linux */
		*state_por = PWRDM_STATE_MAX;
		(*wng_nbr)++;
		return (char *) warning;
	} else if (pastry < PASTRY_ICS) {
		*state_por = omap4_por_hotplug_cpu1_power_state_table[uc_id];
	} else {
		*state_por =
			omap4_por_interactive_cpu1_power_state_table[uc_id];
	}

	#ifdef UC_AUDIT44XX_DEBUG
	pwrdm_state2string(pwst, *state);
	pwrdm_state2string(pwst_por, *state_por);
	dprintf("%s(): CPU1 state=%s POR state=%s\n", __func__, pwst, pwst_por);
	#endif

	if (*state != *state_por) {
		(*err_nbr)++;
		return (char *) fail;
	} else {
		return (char *) pass;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dpll_status_audit44xx
 * @BRIEF		DPLL status audit.
 * @RETURNS		pointer to global pass string in case of successfull
 *			audit
 *			pointer to global fail string in case of failing audit
 *			pointer to global warning string in case of internal
 *			error
 * @param[in]		dpll_id: Power Domain ID
 * @param[in]		uc_id: use-case ID
 * @param[in,out]	status: DPLL mode (returned)
 * @param[in,out]	status_por: expected DPLL status (returned)
 * @param[in,out]	err_nbr: error number (returned)
 * @param[in,out]	wng_nbr: warning number (returned)
 * @DESCRIPTION		DPLL status audit.
 *//*------------------------------------------------------------------------ */
char *dpll_status_audit44xx(dpll44xx_id dpll_id,
	omap4_use_case_id uc_id,
	dpll_status *status, dpll_status *status_por,
	unsigned int *err_nbr, unsigned int *wng_nbr)
{
	int ret;
	omap4_dpll_params dpll_params;
	android_pastry_id pastry;

	if ((status == NULL) || (status_por == NULL) ||
		(err_nbr == NULL) || (wng_nbr == NULL)) {
		(*wng_nbr)++;
		return (char *) warning;
	}
	*err_nbr = 0;
	*wng_nbr = 0;
	*status = DPLL_STATUS_MAX;
	*status = DPLL_STATUS_MAX;
	if (uc_id >= OMAP4_UC_MAX) {
		(*wng_nbr)++;
		return (char *) warning;
	}

	if (!cpu_is_omap44xx())
		return (char *) warning;

	/* Get DPLL Status */
	ret = dpll44xx_dpll_params_get(dpll_id, &dpll_params, 0);
	if (ret < 0) {
		(*wng_nbr)++;
		return (char *) warning;
	}
	*status = dpll_params.status;

	/* Get expected DPLL Status */
	pastry = android_pastry_get();
	if ((pastry == PASTRY_UNKNOWN) || (pastry == PASTRY_ID_MAX)) {
		/* FIXME: find expected OPP for Generic Linux */
		(*wng_nbr)++;
		return (char *) warning;
	} else if (pastry < PASTRY_ICS) {
		*status_por = omap4_gb_por_dpll_status_table[dpll_id][uc_id];
	} else {
		if (cpu_is_omap4470())
			*status_por =
				omap4_ics_por_dpll_status_table[dpll_id][uc_id];
		else
			*status_por =
				omap4_gb_por_dpll_status_table[dpll_id][uc_id];
	}

	#ifdef UC_AUDIT44XX_DEBUG
	printf("%s(): DPLL is %d, status is %s (%d) POR status is %s (%d)\n",
		__func__, dpll_id, dpll_status_name_get(*status), *status,
		dpll_status_name_get(*status_por), *status_por);
	#endif

	if (*status != *status_por) {
		(*err_nbr)++;
		return (char *) fail;
	} else {
		return (char *) pass;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		cpufreq_governor_audit44xx
 * @BRIEF		CPUFreq Governor audit.
 * @RETURNS		pointer to global pass string in case of successfull
 *			audit
 *			pointer to global fail string in case of failing audit
 *			pointer to global warning string in case of internal
 *			error
 * @param[in,out]	gov: current scaling governor (returned)
 * @param[in,out]	gov_por: expected scaling governor (returned)
 * @param[in,out]	err_nbr: error number (returned)
 * @param[in,out]	wng_nbr: warning number (returned)
 * @DESCRIPTION		CPUFreq Governor audit.
 *//*------------------------------------------------------------------------ */
char *cpufreq_governor_audit44xx(char gov[16], char gov_por[16],
	unsigned int *err_nbr, unsigned int *wng_nbr)
{
	FILE *fp = NULL;
	android_pastry_id pastry;

	if ((gov == NULL) || (gov_por == NULL) ||
		(err_nbr == NULL) || (wng_nbr == NULL)) {
		(*wng_nbr)++;
		return (char *) warning;
	}

	strncpy(gov_por, "Not found", 16);
	/* Open /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor file */
	strncpy(gov, "Not found", 16);
	fp = fopen("/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor",
		"r");
	if (fp == NULL) {
		dprintf("error: could not open file /sys/devices/"
			"system/cpu/cpu0/cpufreq/scaling_governor!\n");
		(*err_nbr)++;
		return (char *) fail;
	}

	/* Parse it to find out current scaling governor */
	if (fgets(gov, 16, fp)) {
		dprintf("unexpected read\n");
	}
	if (strlen(gov) > 0)
		gov[strlen(gov) - 1] = '\0'; /* remove new line character */
	fclose(fp);
	dprintf("gov = %s\n", gov);

	/* Retrieve expected governor depending on Android pastry */
	pastry = android_pastry_get();
	if ((pastry == PASTRY_UNKNOWN) || (pastry == PASTRY_ID_MAX)) {
		/* FIXME: find expected OPP for Generic Linux */
		(*wng_nbr)++;
		return (char *) warning;
	} else if (pastry < PASTRY_ICS) {
		strncpy(gov_por, "hotplug", 16);
	} else {
		strncpy(gov_por, "interactive", 16);
	}

	if (strncmp(gov, gov_por, strlen(gov_por)) == 0) {
		dprintf("%s: %s governor detected\n", __func__, gov_por);
		return (char *) pass;
	} else {
		dprintf("%s: expected governor (%s) not found (%s)\n",
			__func__, gov_por, gov);
		(*err_nbr)++;
		return (char *) fail;
	}
}


/* #define DEEPEST_CSTATE_AUDIT44XX_DEBUG */
#ifdef DEEPEST_CSTATE_AUDIT44XX_DEBUG
#undef dprintf
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#endif
/* ------------------------------------------------------------------------*//**
 * @FUNCTION		deepest_cstate_audit44xx
 * @BRIEF		deepest-entered C-State audit.
 * @RETURNS		pointer to global pass string in case of successfull
 *			audit
 *			pointer to global fail string in case of failing audit
 *			pointer to global ignore string in case of unavailable
 *			stat file
 *			/sys/devices/system/cpu/cpu0/cpuidle/state[0-x]/usage
 * @param[in]		uc_id: use-case ID
 * @param[in,out]	cstate: deepest C-State entered in last 10s (returned)
 * @param[in,out]	cstate_por: expected deepest C-State entered (returned)
 * @param[in,out]	err_nbr: error number (returned)
 * @param[in,out]	wng_nbr: warning number (returned)
 * @DESCRIPTION		deepest-entered C-State audit.
 *//*------------------------------------------------------------------------ */
char *deepest_cstate_audit44xx(omap4_use_case_id uc_id,
	unsigned int *cstate, unsigned int *cstate_por,
	unsigned int *err_nbr, unsigned int *wng_nbr)
{
	unsigned int cstate_usage_sample1[MAX_CSTATE];
	unsigned int cstate_usage_sample2[MAX_CSTATE];
	unsigned int i;
	android_pastry_id pastry;

	if ((cstate == NULL) || (cstate_por == NULL) ||
		(err_nbr == NULL) || (wng_nbr == NULL)) {
		fprintf(stderr, "%s(): bad arg(s)\n", __func__);
		return (char *) ignore;
	}

	if (!cpu_is_omap44xx()) {
		fprintf(stderr, "%s(): not OMAP4!\n", __func__);
		return (char *) ignore;
	}
	*err_nbr = 0;
	*wng_nbr = 0;
	*cstate = 0;
	*cstate_por = 0;
	if (cstate_get_number() == 0) {
		/* C-State sysfs entries not found */
		fprintf(stderr, "%s(): C-State sysfs entries not found?!\n",
			__func__);
		return (char *) ignore;
	}

	/* Retrieve expected lowest C-State */
	pastry = android_pastry_get();
	if ((pastry == PASTRY_UNKNOWN) || (pastry == PASTRY_ID_MAX)) {
		/* FIXME: find expected OPP for Generic Linux */
		(*wng_nbr)++;
		return (char *) warning;
	} else if (pastry < PASTRY_ICS) {
		*cstate_por = omap4_gb_por_cstate_table[uc_id];
	} else {
		*cstate_por = omap4_ics_por_cstate_table[uc_id];
	}

	dprintf("%s(): UC is %s POR C-STATE is C%d\n", __func__,
		omap4_use_case_name_table[uc_id],
		*cstate_por);

	/* Save current usage value */
	for (i = 0; i < cstate_get_number(); i++) {
		cstate_usage_sample1[i] = cstate_get_usage(i);
		dprintf("%s(): cstate_usage_sample1[%d] = "
			"%d\n", __func__, i, cstate_usage_sample1[i]);
	}

	/* Sleep for 15s before sampling again usage value */
	printf("Monitoring C-States counters, please wait for 15s ...\n");
	sleep(15);
	printf("done.\n\n");

	/* Get new usage value */
	for (i = 0; i < cstate_get_number(); i++) {
		cstate_usage_sample2[i] = cstate_get_usage(i);
		dprintf("%s(): cstate_usage_sample2[%d] = "
			"%d\n", __func__, i, cstate_usage_sample2[i]);
	}

	/* Retrieve lowest C-State entered */
	for (i = 0; i < cstate_get_number(); i++) {
		if (cstate_usage_sample2[i] != cstate_usage_sample1[i]) {
			/*
			 * There is no sysfs file for C0.
			 * "/sys/devices/system/cpu/cpu0/cpuidle/state0/usage"
			 * is actually C1 sysfs file.
			 */
			*cstate = i + 1;
			dprintf("%s(): C%d entered\n", __func__, i + 1);
		} else {
			dprintf("%s(): C%d not entered\n", __func__, i + 1);
		}
	}

	if (*cstate >= *cstate_por) {
		dprintf("%s(): expected lowest C-State (C%d) entered\n",
			__func__, *cstate);
		return (char *) pass;
	} else {
		dprintf("%s(): expected lowest C-State NOT entered! "
			"(but C%d)\n", __func__, *cstate);
		(*err_nbr)++;
		return (char *) fail;
	}
}
#ifdef DEEPEST_CSTATE_AUDIT44XX_DEBUG
#undef dprintf
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		use_case_audit44xx
 * @BRIEF		OMAP4 Use-Case audit.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		uc_id: use-case to be audited
 * @param[in,out]	err_nbr: pointer to return audit error number
 * @param[in,out]	wng_nbr: pointer to return audit warning number
 * @param[in]		verbose: no console prints if == 0, verbose
 *			(console prints) otherwise
 * @param[in]		full_log: show full audit details
 * @DESCRIPTION		OMAP4 Use-Case audit.
 *//*------------------------------------------------------------------------ */
int use_case_audit44xx(omap4_use_case_id uc_id,
	unsigned int *err_nbr, unsigned int *wng_nbr,
	unsigned short verbose, unsigned short full_log)
{
	int ret;
	unsigned int err_nbr_tmp = 0, wng_nbr_tmp = 0, test_nbr = 0;
	char *status;
	opp44xx_id opp;
	opp44xx_id opp_por;
	char s_opp[10];
	char s_opp_por[10];
	double volt, volt_por;
	pwrdm_state state, state_por;
	char s_state[6], s_state_por[6];
	unsigned int cstate, cstate_por;
	clkdm_status clkst, clkst_por;
	dpll_status dpll_st, dpll_st_por;
	char s_gov[16], s_gov_por[16];
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	char result_table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row;
	unsigned int result_row;
	FILE *fp_summary = NULL;
	FILE *fp_details = NULL;
	char prev_gov[16], prev_gov2[16];
	unsigned int i;
	static FILE *output_streams[3];

	if (!cpu_is_omap44xx())
		return OMAPCONF_ERR_CPU;
	if (uc_id >= OMAP4_UC_MAX)
		return OMAPCONF_ERR_ARG;

	if (verbose == 1)
		output_streams[0] = stdout;
	else
		output_streams[0] = NULL;
	fp_summary = workdir_fopen(
		omap4_use_case_summary_filename_table[uc_id], "w");
	if (full_log)
		fp_details = workdir_fopen(
			omap4_use_case_details_filename_table[uc_id], "w");

	if (fp_summary == NULL) {
		printf("error: could not create summary file!\n");
	} else {
		fprintf(fp_summary, "%s Audit Summary\n\n",
			omap4_use_case_name_table[uc_id]);
		omapconf_revision_show(fp_summary);
		chips_info_show(fp_summary, 1);
		release_info_show(fp_summary);
	}

	if (full_log) {
		if (fp_details == NULL) {
			printf("error: could not create details file!\n");
		} else {
			fprintf(fp_details, "%s Audit Details\n\n",
				omap4_use_case_name_table[uc_id]);
			omapconf_revision_show(fp_details);
			chips_info_show(fp_details, 1);
			release_info_show(fp_details);
		}
	}
	output_streams[1] = fp_summary;
	output_streams[2] = fp_details;

	autoadjust_table_init(table);
	autoadjust_table_init(result_table);

	row = 0;
	snprintf(table[row][0], TABLE_MAX_ELT_LEN,
		"%s Power Settings Audit",
		omap4_use_case_name_table[uc_id]);
	strncpy(table[row][1], "Current", TABLE_MAX_ELT_LEN);
	strncpy(table[row][2], "Expected (POR)", TABLE_MAX_ELT_LEN);
	strncpy(table[row][3], "STATUS", TABLE_MAX_ELT_LEN);
	row++;

	/* Check CPUFreq Governor */
	strncpy(table[row][0], "CPUFreq Governor", TABLE_MAX_ELT_LEN);
	status = cpufreq_governor_audit44xx(s_gov, s_gov_por,
		&err_nbr_tmp, &wng_nbr_tmp);
	(*err_nbr) += err_nbr_tmp;
	(*wng_nbr) += wng_nbr_tmp;
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s", s_gov);
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s", s_gov_por);
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row += 2;
	test_nbr++;

	/* Switch to userspace governor temporarily,
	 * so that OPP cannot change during audit and does not false it.
	 */
	cpufreq_scaling_governor_set("userspace", prev_gov);

	/* Check OPPs */
	strncpy(table[row][0], "OPPs", TABLE_MAX_ELT_LEN);
	row++;
	status = opp_audit44xx(OMAP4_VDD_MPU, uc_id,
		&opp, &opp_por, &err_nbr_tmp, &wng_nbr_tmp);
	(*err_nbr) += err_nbr_tmp;
	(*wng_nbr) += wng_nbr_tmp;
	voltdm44xx_opp2string(s_opp, opp, OMAP4_VDD_MPU);
	voltdm44xx_opp2string(s_opp_por, opp_por, OMAP4_VDD_MPU);
	strncpy(table[row][0], "  VDD_MPU", TABLE_MAX_ELT_LEN);
	strncpy(table[row][1], s_opp, TABLE_MAX_ELT_LEN);
	strncpy(table[row][2], s_opp_por, TABLE_MAX_ELT_LEN);
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	status = opp_audit44xx(OMAP4_VDD_IVA, uc_id,
		&opp, &opp_por, &err_nbr_tmp, &wng_nbr_tmp);
	(*err_nbr) += err_nbr_tmp;
	(*wng_nbr) += wng_nbr_tmp;
	voltdm44xx_opp2string(s_opp, opp, OMAP4_VDD_IVA);
	voltdm44xx_opp2string(s_opp_por, opp_por, OMAP4_VDD_IVA);
	strncpy(table[row][0], "  VDD_IVA", TABLE_MAX_ELT_LEN);
	strncpy(table[row][1], s_opp, TABLE_MAX_ELT_LEN);
	strncpy(table[row][2], s_opp_por, TABLE_MAX_ELT_LEN);
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	status = opp_audit44xx(OMAP4_VDD_CORE, uc_id,
		&opp, &opp_por, &err_nbr_tmp, &wng_nbr_tmp);
	(*err_nbr) += err_nbr_tmp;
	(*wng_nbr) += wng_nbr_tmp;
	voltdm44xx_opp2string(s_opp, opp, OMAP4_VDD_CORE);
	voltdm44xx_opp2string(s_opp_por, opp_por, OMAP4_VDD_CORE);
	strncpy(table[row][0], "  VDD_CORE", TABLE_MAX_ELT_LEN);
	strncpy(table[row][1], s_opp, TABLE_MAX_ELT_LEN);
	strncpy(table[row][2], s_opp_por, TABLE_MAX_ELT_LEN);
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row += 2;
	test_nbr++;

	/* Check Smart-Reflex is enabled */
	strncpy(table[row][0], "Smart-Reflex", TABLE_MAX_ELT_LEN);
	row++;
	if (android_pastry_get() != PASTRY_GB) {
		/* ICS and next pastries use SR Class 1.5.
		 * Sensors are disabled outside of periodic recalibration.
		 * Just ignore this audit.
		 */
		strncpy(table[row][0], "  MPU", TABLE_MAX_ELT_LEN);
		strncpy(table[row][3], ignore3, TABLE_MAX_ELT_LEN);
		row++;
		test_nbr++;
		strncpy(table[row][0], "  IVA", TABLE_MAX_ELT_LEN);
		strncpy(table[row][3], ignore3, TABLE_MAX_ELT_LEN);
		row++;
		test_nbr++;
		strncpy(table[row][0], "  CORE", TABLE_MAX_ELT_LEN);
		strncpy(table[row][3], ignore3, TABLE_MAX_ELT_LEN);
		row += 2;
		test_nbr++;
		goto use_case_audit44xx_voltage_check;
	}

	if (sr44xx_is_enabled(OMAP4_SR_MPU) == 1) {
		status = (char *) pass;
		strncpy(table[row][1], "Enabled", TABLE_MAX_ELT_LEN);
	} else {
		strncpy(table[row][1], "Disabled", TABLE_MAX_ELT_LEN);
		status = (char *) fail;
		(*err_nbr)++;
	}
	strncpy(table[row][0], "  MPU", TABLE_MAX_ELT_LEN);
	strncpy(table[row][2], "Enabled", TABLE_MAX_ELT_LEN);
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	if (sr44xx_is_enabled(OMAP4_SR_IVA) == 1) {
		status = (char *) pass;
		strncpy(table[row][1], "Enabled", TABLE_MAX_ELT_LEN);
	} else {
		strncpy(table[row][1], "Disabled", TABLE_MAX_ELT_LEN);
		status = (char *) fail;
		(*err_nbr)++;
	}
	strncpy(table[row][0], "  IVA", TABLE_MAX_ELT_LEN);
	strncpy(table[row][2], "Enabled", TABLE_MAX_ELT_LEN);
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	if (sr44xx_is_enabled(OMAP4_SR_CORE) == 1) {
		status = (char *) pass;
		strncpy(table[row][1], "Enabled", TABLE_MAX_ELT_LEN);
	} else {
		strncpy(table[row][1], "Disabled", TABLE_MAX_ELT_LEN);
		status = (char *) fail;
		(*err_nbr)++;
	}
	strncpy(table[row][0], "  CORE", TABLE_MAX_ELT_LEN);
	strncpy(table[row][2], "Enabled", TABLE_MAX_ELT_LEN);
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row += 2;
	test_nbr++;

	/* Check Voltages */
use_case_audit44xx_voltage_check:
	strncpy(table[row][0], "Voltages", TABLE_MAX_ELT_LEN);
	row++;
	status = voltage_audit44xx(OMAP4_VDD_MPU, uc_id,
		&volt, &volt_por, &err_nbr_tmp, &wng_nbr_tmp);
	(*err_nbr) += err_nbr_tmp;
	(*wng_nbr) += wng_nbr_tmp;
	strncpy(table[row][0], "  VDD_MPU", TABLE_MAX_ELT_LEN);
	if (volt != 0.0)
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%lf V", volt);
	else
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "NA");
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "<= %lf V", volt_por);
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	status = voltage_audit44xx(OMAP4_VDD_IVA, uc_id,
		&volt, &volt_por, &err_nbr_tmp, &wng_nbr_tmp);
	(*err_nbr) += err_nbr_tmp;
	(*wng_nbr) += wng_nbr_tmp;
	strncpy(table[row][0], "  VDD_IVA", TABLE_MAX_ELT_LEN);
	if (volt != 0.0)
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%lf V", volt);
	else
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "NA");
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "<= %lf V", volt_por);
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	status = voltage_audit44xx(OMAP4_VDD_CORE, uc_id,
		&volt, &volt_por, &err_nbr_tmp, &wng_nbr_tmp);
	(*err_nbr) += err_nbr_tmp;
	(*wng_nbr) += wng_nbr_tmp;
	strncpy(table[row][0], "  VDD_CORE", TABLE_MAX_ELT_LEN);
	if (volt != 0.0)
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%lf V", volt);
	else
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "NA");
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "<= %lf V", volt_por);
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row += 2;
	test_nbr++;

	/* Check RETENTION Voltages */
	strncpy(table[row][0], "RETENTION Voltages", TABLE_MAX_ELT_LEN);
	row++;
	status = ret_voltage_audit44xx(OMAP4_VDD_MPU,
		&volt, &volt_por, &err_nbr_tmp, &wng_nbr_tmp);
	(*err_nbr) += err_nbr_tmp;
	(*wng_nbr) += wng_nbr_tmp;
	strncpy(table[row][0], "  VDD_MPU", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%lf V", volt);
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%lf V", volt_por);
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	status = ret_voltage_audit44xx(OMAP4_VDD_IVA,
		&volt, &volt_por, &err_nbr_tmp, &wng_nbr_tmp);
	(*err_nbr) += err_nbr_tmp;
	(*wng_nbr) += wng_nbr_tmp;
	strncpy(table[row][0], "  VDD_IVA", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%lf V", volt);
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%lf V", volt_por);
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	status = ret_voltage_audit44xx(OMAP4_VDD_CORE,
		&volt, &volt_por, &err_nbr_tmp, &wng_nbr_tmp);
	(*err_nbr) += err_nbr_tmp;
	(*wng_nbr) += wng_nbr_tmp;
	strncpy(table[row][0], "  VDD_CORE", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%lf V", volt);
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%lf V", volt_por);
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row += 2;
	test_nbr++;

	/* Check CLK Speeds */
	ret = clkspeed_audit44xx(fp_details,
		&err_nbr_tmp, &wng_nbr_tmp);
	if (ret != 0) {
		status = (char *) warning;
		(*wng_nbr)++;
		dprintf("%s(): clock speed audit returned with %d\n",
			__func__, ret);
	} else if (err_nbr_tmp != 0) {
		status = (char *) fail;
		(*err_nbr)++;
		dprintf("%s(): clock speed audit returned with %d error(s)\n",
			__func__, err_nbr_tmp);
	} else if (wng_nbr_tmp != 0) {
		status = (char *) warning;
		(*wng_nbr)++;
		dprintf("%s(): clock speed audit returned with %d warning(s)\n",
			__func__, wng_nbr_tmp);
	} else {
		status = (char *) pass;
	}
	strncpy(table[row][0], "Clock Speeds (4)", TABLE_MAX_ELT_LEN);
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row += 2;
	test_nbr++;

	/* Check static dependency settings */
	ret = statdep44xx_audit(fp_details,
		&err_nbr_tmp, &wng_nbr_tmp);
	if (ret != 0) {
		status = (char *) warning;
		(*wng_nbr)++;
		dprintf("%s(): statdep audit returned with %d\n",
			__func__, ret);
	} else if (err_nbr_tmp != 0) {
		status = (char *) fail;
		(*err_nbr)++;
		dprintf("%s(): statdep audit returned with %d error(s)\n",
			__func__, err_nbr_tmp);
	} else if (wng_nbr_tmp != 0) {
		status = (char *) warning;
		(*wng_nbr)++;
		dprintf("%s(): statdep audit returned with %d warning(s)\n",
			__func__, wng_nbr_tmp);
	} else {
		status = (char *) pass;
	}
	strncpy(table[row][0], "Static Dependencies (4)", TABLE_MAX_ELT_LEN);
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row += 2;
	test_nbr++;

	/* Check CPU1 Power State */
	strncpy(table[row][0], "CPU1 Power State", TABLE_MAX_ELT_LEN);
	status = cpu1_power_state_audit44xx(uc_id,
		&state, &state_por, &err_nbr_tmp, &wng_nbr_tmp);
	(*err_nbr) += err_nbr_tmp;
	(*wng_nbr) += wng_nbr_tmp;
	pwrdm_state2string(s_state, state);
	pwrdm_state2string(s_state_por, state_por);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s", s_state);
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s", s_state_por);
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row += 2;
	test_nbr++;

	/* Check lowest C-State entered */
	strncpy(table[row][0], "Lowest C-State entered", TABLE_MAX_ELT_LEN);
	status = deepest_cstate_audit44xx(uc_id,
		&cstate, &cstate_por, &err_nbr_tmp, &wng_nbr_tmp);
	(*err_nbr) += err_nbr_tmp;
	(*wng_nbr) += wng_nbr_tmp;
	if (status == ignore) {
		strncpy(table[row][1], "Not Available", TABLE_MAX_ELT_LEN);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "C%d", cstate_por);
		strncpy(table[row][3], "Ignored", TABLE_MAX_ELT_LEN);
	} else {
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "C%d", cstate);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "C%d", cstate_por);
		strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	}
	row += 2;
	test_nbr++;

	/* Check Power & Clock Domains State */
	strncpy(table[row][0], "Power &",
		TABLE_MAX_ELT_LEN);
	row++;
	strncpy(table[row][0], "  Clock Domains State (2)",
		TABLE_MAX_ELT_LEN);
	row++;

	status = pwrdm_state_audit44xx(OMAP4_PD_ABE, uc_id,
		&state, &state_por, &err_nbr_tmp, &wng_nbr_tmp);
	(*err_nbr) += err_nbr_tmp;
	(*wng_nbr) += wng_nbr_tmp;
	pwrdm_state2string(s_state, state);
	pwrdm_state2string(s_state_por, state_por);
	strncpy(table[row][0], "  ABE", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s", s_state);
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s", s_state_por);
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	status = clkdm_status_audit44xx(OMAP4_CD_ABE, uc_id,
		&clkst, &clkst_por, &err_nbr_tmp, &wng_nbr_tmp);
	(*err_nbr) += err_nbr_tmp;
	(*wng_nbr) += wng_nbr_tmp;
	strncpy(table[row][0], "    ABE", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst));
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst_por));
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	if (fp_details != NULL)
		abe44xx_config_show(fp_details);
	row++;
	test_nbr++;

	status = pwrdm_state_audit44xx(OMAP4_PD_IVA_HD, uc_id,
		&state, &state_por, &err_nbr_tmp, &wng_nbr_tmp);
	if ((uc_id == OMAP4_UC_OS_IDLE) || (uc_id == OMAP4_UC_MP3_PLAYBACK) ||
		(uc_id == OMAP4_UC_HOME_SCREEN)) {
		(*err_nbr) += err_nbr_tmp;
		(*wng_nbr) += wng_nbr_tmp;
	} else {
		/* Domain is auto gated, could be either gated or running */
		status = (char *) ignore2;
	}
	pwrdm_state2string(s_state, state);
	pwrdm_state2string(s_state_por, state_por);
	strncpy(table[row][0], "  IVAHD", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s", s_state);
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s", s_state_por);
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	status = clkdm_status_audit44xx(OMAP4_CD_IVA_HD, uc_id,
		&clkst, &clkst_por, &err_nbr_tmp, &wng_nbr_tmp);
	if ((uc_id == OMAP4_UC_OS_IDLE) || (uc_id == OMAP4_UC_MP3_PLAYBACK) ||
		(uc_id == OMAP4_UC_HOME_SCREEN)) {
		(*err_nbr) += err_nbr_tmp;
		(*wng_nbr) += wng_nbr_tmp;
	} else {
		/* Domain is auto gated, could be either gated or running */
		status = (char *) ignore2;
	}

	strncpy(table[row][0], "    IVAHD", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst));
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst_por));
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	if (fp_details != NULL)
		ivahd44xx_config_show(fp_details);
	row++;
	test_nbr++;

	status = pwrdm_state_audit44xx(OMAP4_PD_GFX, uc_id,
		&state, &state_por, &err_nbr_tmp, &wng_nbr_tmp);
	(*err_nbr) += err_nbr_tmp;
	(*wng_nbr) += wng_nbr_tmp;
	pwrdm_state2string(s_state, state);
	pwrdm_state2string(s_state_por, state_por);
	strncpy(table[row][0], "  GFX", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s", s_state);
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s", s_state_por);
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	status = clkdm_status_audit44xx(OMAP4_CD_GFX, uc_id,
		&clkst, &clkst_por, &err_nbr_tmp, &wng_nbr_tmp);
	(*err_nbr) += err_nbr_tmp;
	(*wng_nbr) += wng_nbr_tmp;
	strncpy(table[row][0], "    GFX", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst));
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst_por));
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	if (fp_details != NULL)
		gfx44xx_config_show(fp_details);
	row++;
	test_nbr++;

	status = pwrdm_state_audit44xx(OMAP4_PD_DSP, uc_id,
		&state, &state_por, &err_nbr_tmp, &wng_nbr_tmp);
	(*err_nbr) += err_nbr_tmp;
	(*wng_nbr) += wng_nbr_tmp;
	pwrdm_state2string(s_state, state);
	pwrdm_state2string(s_state_por, state_por);
	strncpy(table[row][0], "  DSP", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s", s_state);
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s", s_state_por);
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	status = clkdm_status_audit44xx(OMAP4_CD_DSP, uc_id,
		&clkst, &clkst_por, &err_nbr_tmp, &wng_nbr_tmp);
	(*err_nbr) += err_nbr_tmp;
	(*wng_nbr) += wng_nbr_tmp;
	strncpy(table[row][0], "    DSP", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst));
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst_por));
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	if (fp_details != NULL)
		dsp44xx_config_show(fp_details);
	row++;
	test_nbr++;

	status = pwrdm_state_audit44xx(OMAP4_PD_CAM, uc_id,
		&state, &state_por, &err_nbr_tmp, &wng_nbr_tmp);
	(*err_nbr) += err_nbr_tmp;
	(*wng_nbr) += wng_nbr_tmp;
	pwrdm_state2string(s_state, state);
	pwrdm_state2string(s_state_por, state_por);
	strncpy(table[row][0], "  CAM", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s", s_state);
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s", s_state_por);
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	status = clkdm_status_audit44xx(OMAP4_CD_CAM, uc_id,
		&clkst, &clkst_por, &err_nbr_tmp, &wng_nbr_tmp);
	(*err_nbr) += err_nbr_tmp;
	(*wng_nbr) += wng_nbr_tmp;
	strncpy(table[row][0], "    CAM", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst));
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst_por));
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	if (fp_details != NULL)
		cam44xx_config_show(fp_details);
	row++;
	test_nbr++;

	status = pwrdm_state_audit44xx(OMAP4_PD_L3_INIT, uc_id,
		&state, &state_por, &err_nbr_tmp, &wng_nbr_tmp);
	status = (char *) ignore2;
	pwrdm_state2string(s_state, state);
	pwrdm_state2string(s_state_por, state_por);
	strncpy(table[row][0], "  L3_INIT", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s", s_state);
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s", s_state_por);
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	status = clkdm_status_audit44xx(OMAP4_CD_L3_INIT, uc_id,
		&clkst, &clkst_por, &err_nbr_tmp, &wng_nbr_tmp);
	status = (char *) ignore2;
	strncpy(table[row][0], "    L3_INIT", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst));
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst_por));
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	if (fp_details != NULL)
		l3init44xx_config_show(fp_details);
	row++;
	test_nbr++;

	status = pwrdm_state_audit44xx(OMAP4_PD_MPU, uc_id,
		&state, &state_por, &err_nbr_tmp, &wng_nbr_tmp);
	status = (char *) ignore; /* MPU anyway running to execute omapconf */
	pwrdm_state2string(s_state, state);
	pwrdm_state2string(s_state_por, state_por);
	strncpy(table[row][0], "  MPU", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s", s_state);
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s", s_state_por);
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	status = clkdm_status_audit44xx(OMAP4_CD_MPU, uc_id,
		&clkst, &clkst_por, &err_nbr_tmp, &wng_nbr_tmp);
	status = (char *) ignore; /* MPU anyway running to execute omapconf */
	strncpy(table[row][0], "    MPU", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst));
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst_por));
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	if (fp_details != NULL)
		mpu44xx_config_show(fp_details);
	row++;
	test_nbr++;

	status = pwrdm_state_audit44xx(OMAP4_PD_DSS, uc_id,
		&state, &state_por, &err_nbr_tmp, &wng_nbr_tmp);
	(*err_nbr) += err_nbr_tmp;
	(*wng_nbr) += wng_nbr_tmp;
	pwrdm_state2string(s_state, state);
	pwrdm_state2string(s_state_por, state_por);
	strncpy(table[row][0], "  DSS", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s", s_state);
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s", s_state_por);
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	status = clkdm_status_audit44xx(OMAP4_CD_DSS, uc_id,
		&clkst, &clkst_por, &err_nbr_tmp, &wng_nbr_tmp);
	if ((uc_id == OMAP4_UC_OS_IDLE) || (uc_id == OMAP4_UC_MP3_PLAYBACK) ||
		(uc_id == OMAP4_UC_HOME_SCREEN)) {
		(*err_nbr) += err_nbr_tmp;
		(*wng_nbr) += wng_nbr_tmp;
	} else {
		/* Domain is auto gated, could be either gated or running */
		status = (char *) ignore2;
	}
	strncpy(table[row][0], "    DSS", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst));
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst_por));
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	if (fp_details != NULL)
		dss44xx_config_show(fp_details);
	row++;
	test_nbr++;

	status = pwrdm_state_audit44xx(OMAP4_PD_L4_PER, uc_id,
		&state, &state_por, &err_nbr_tmp, &wng_nbr_tmp);
	status = (char *) ignore; /* UARTs are running compared to POR */
	pwrdm_state2string(s_state, state);
	pwrdm_state2string(s_state_por, state_por);
	strncpy(table[row][0], "  L4_PER", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s", s_state);
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s", s_state_por);
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	status = clkdm_status_audit44xx(OMAP4_CD_L4_PER, uc_id,
		&clkst, &clkst_por, &err_nbr_tmp, &wng_nbr_tmp);
	status = (char *) ignore; /* UARTs are running compared to POR */
	strncpy(table[row][0], "    L4_PER", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst));
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst_por));
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	if (cpu_is_hs_device() || cpu_is_emu_device()) {
		status = clkdm_status_audit44xx(OMAP4_CD_L4_SEC,
			uc_id, &clkst, &clkst_por, &err_nbr_tmp, &wng_nbr_tmp);
		(*err_nbr) += err_nbr_tmp;
		(*wng_nbr) += wng_nbr_tmp;
		strncpy(table[row][0], "    L4_SEC", TABLE_MAX_ELT_LEN);
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
			clkdm_status_name_get(clkst));
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
			clkdm_status_name_get(clkst_por));
		strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
		row++;
		test_nbr++;
	}
	if (fp_details != NULL)
		per44xx_config_show(fp_details);

	status = pwrdm_state_audit44xx(OMAP4_PD_CORE, uc_id,
		&state, &state_por, &err_nbr_tmp, &wng_nbr_tmp);
	status = (char *) ignore; /* CORE anyway running to execute omapconf */
	pwrdm_state2string(s_state, state);
	pwrdm_state2string(s_state_por, state_por);
	strncpy(table[row][0], "  CORE", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s", s_state);
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s", s_state_por);
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	status = clkdm_status_audit44xx(OMAP4_CD_EMIF, uc_id,
		&clkst, &clkst_por, &err_nbr_tmp, &wng_nbr_tmp);
	status = (char *) ignore; /* EMIF anyway running to execute omapconf */
	strncpy(table[row][0], "    EMIF", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst));
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst_por));
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	status = clkdm_status_audit44xx(OMAP4_CD_L3_1, uc_id,
		&clkst, &clkst_por, &err_nbr_tmp, &wng_nbr_tmp);
	status = (char *) ignore; /* L3_1 anyway running to execute omapconf */
	strncpy(table[row][0], "    L3_1", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst));
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst_por));
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	status = clkdm_status_audit44xx(OMAP4_CD_L4CFG, uc_id,
		&clkst, &clkst_por, &err_nbr_tmp, &wng_nbr_tmp);
	status = (char *) ignore; /* always running when omapconf is running */
	strncpy(table[row][0], "    L4_CFG", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst));
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst_por));
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	status = clkdm_status_audit44xx(OMAP4_CD_MPU_M3, uc_id,
		&clkst, &clkst_por, &err_nbr_tmp, &wng_nbr_tmp);
	if ((uc_id == OMAP4_UC_OS_IDLE) || (uc_id == OMAP4_UC_MP3_PLAYBACK) ||
		(uc_id == OMAP4_UC_HOME_SCREEN)) {
		(*err_nbr) += err_nbr_tmp;
		(*wng_nbr) += wng_nbr_tmp;
	} else {
		/* Domain is auto-gated, could be either gated or running */
		status = (char *) ignore2;
	}
	strncpy(table[row][0], "    MPU_M3", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst));
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst_por));
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	status = clkdm_status_audit44xx(OMAP4_CD_DMA, uc_id,
		&clkst, &clkst_por, &err_nbr_tmp, &wng_nbr_tmp);
	if (uc_id == OMAP4_UC_MP3_PLAYBACK)
		status = (char *) ignore; /* DMA may or may not be running */
	strncpy(table[row][0], "    DMA", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst));
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst_por));
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	status = clkdm_status_audit44xx(OMAP4_CD_L3_2, uc_id,
		&clkst, &clkst_por, &err_nbr_tmp, &wng_nbr_tmp);
	status = (char *) ignore; /* always running when omapconf is running */
	strncpy(table[row][0], "    L3_2", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst));
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst_por));
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	status = clkdm_status_audit44xx(OMAP4_CD_L3_INSTR, uc_id,
		&clkst, &clkst_por, &err_nbr_tmp, &wng_nbr_tmp);
	status = (char *) ignore;
	strncpy(table[row][0], "    L3_INSTR", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst));
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst_por));
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	status = clkdm_status_audit44xx(OMAP4_CD_C2C, uc_id,
		&clkst, &clkst_por, &err_nbr_tmp, &wng_nbr_tmp);
	(*err_nbr) += err_nbr_tmp;
	(*wng_nbr) += wng_nbr_tmp;
	strncpy(table[row][0], "    C2C", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst));
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
		clkdm_status_name_get(clkst_por));
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	if (fp_details != NULL)
		core44xx_config_show(fp_details);
	row += 2;
	test_nbr++;

	/* Check SYSCONFIG settings */
	ret = sysconfig_audit44xx(fp_details,
		&err_nbr_tmp, &wng_nbr_tmp);
	if (ret != 0) {
		status = (char *) warning;
		(*wng_nbr)++;
		dprintf("%s(): sysconfig audit returned with %d\n",
			__func__, ret);
	} else if (err_nbr_tmp != 0) {
		status = (char *) fail;
		(*err_nbr)++;
		dprintf("%s(): sysconfig audit returned with %d error(s)\n",
			__func__, err_nbr_tmp);
	} else if (wng_nbr_tmp != 0) {
		status = (char *) warning;
		(*wng_nbr)++;
		dprintf("%s(): sysconfig audit returned with %d warning(s)\n",
			__func__, wng_nbr_tmp);
	} else {
		status = (char *) pass;
	}
	strncpy(table[row][0], "SYSCONFIG Settings (4)", TABLE_MAX_ELT_LEN);
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row += 2;
	test_nbr++;

	/* Check DPLLs Status */
	strncpy(table[row][0], "DPLLs Status (4)", TABLE_MAX_ELT_LEN);
	row++;
	status = dpll_status_audit44xx(DPLL44XX_ABE, uc_id,
		&dpll_st, &dpll_st_por, &err_nbr_tmp, &wng_nbr_tmp);
	(*err_nbr) += err_nbr_tmp;
	(*wng_nbr) += wng_nbr_tmp;
	strncpy(table[row][0], "  ABE", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
		dpll_status_name_get((dpll_status) dpll_st));
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
		dpll_status_name_get((dpll_status) dpll_st_por));
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	status = dpll_status_audit44xx(DPLL44XX_CORE, uc_id,
		&dpll_st, &dpll_st_por, &err_nbr_tmp, &wng_nbr_tmp);
	(*err_nbr) += err_nbr_tmp;
	(*wng_nbr) += wng_nbr_tmp;
	strncpy(table[row][0], "  CORE", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
		dpll_status_name_get((dpll_status) dpll_st));
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
		dpll_status_name_get((dpll_status) dpll_st_por));
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	status = dpll_status_audit44xx(DPLL44XX_PER, uc_id,
		&dpll_st, &dpll_st_por, &err_nbr_tmp, &wng_nbr_tmp);
	(*err_nbr) += err_nbr_tmp;
	(*wng_nbr) += wng_nbr_tmp;
	strncpy(table[row][0], "  PER", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
		dpll_status_name_get((dpll_status) dpll_st));
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
		dpll_status_name_get((dpll_status) dpll_st_por));
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	status = dpll_status_audit44xx(DPLL44XX_MPU, uc_id,
		&dpll_st, &dpll_st_por, &err_nbr_tmp, &wng_nbr_tmp);
	(*err_nbr) += err_nbr_tmp;
	(*wng_nbr) += wng_nbr_tmp;
	strncpy(table[row][0], "  MPU", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
		dpll_status_name_get((dpll_status) dpll_st));
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
		dpll_status_name_get((dpll_status) dpll_st_por));
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	status = dpll_status_audit44xx(DPLL44XX_IVA, uc_id,
		&dpll_st, &dpll_st_por, &err_nbr_tmp, &wng_nbr_tmp);
	if ((uc_id == OMAP4_UC_OS_IDLE) || (uc_id == OMAP4_UC_MP3_PLAYBACK) ||
		(uc_id == OMAP4_UC_HOME_SCREEN)) {
		(*err_nbr) += err_nbr_tmp;
		(*wng_nbr) += wng_nbr_tmp;
	} else {
		/*
		 * DPLL autoidle is enabled, could be either stopped or lock,
		 * along with IVAHD autogating
		 */
		status = (char *) ignore2;
	}
	strncpy(table[row][0], "  IVA", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
		dpll_status_name_get((dpll_status) dpll_st));
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
		dpll_status_name_get((dpll_status) dpll_st_por));
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	status = dpll_status_audit44xx(DPLL44XX_USB, uc_id,
		&dpll_st, &dpll_st_por, &err_nbr_tmp, &wng_nbr_tmp);
	(*err_nbr) += err_nbr_tmp;
	(*wng_nbr) += wng_nbr_tmp;
	strncpy(table[row][0], "  USB", TABLE_MAX_ELT_LEN);
	snprintf(table[row][1], TABLE_MAX_ELT_LEN, "%s",
		dpll_status_name_get((dpll_status) dpll_st));
	snprintf(table[row][2], TABLE_MAX_ELT_LEN, "%s",
		dpll_status_name_get((dpll_status) dpll_st_por));
	strncpy(table[row][3], status, TABLE_MAX_ELT_LEN);
	row++;
	test_nbr++;
	if (fp_details != NULL)
		dpll44xx_config_show(fp_details);

	/* Do some audit statistics */
	result_row = 0;
	snprintf(result_table[result_row][0], TABLE_MAX_ELT_LEN,
		"%s Audit Metrics", omap4_use_case_name_table[uc_id]);
	strncpy(result_table[result_row][1], "Count",
		TABLE_MAX_ELT_LEN);
	strncpy(result_table[result_row][2], "Breakout (%)",
		TABLE_MAX_ELT_LEN);
	result_row++;
	strncpy(result_table[result_row][0], "Number of tests run",
		TABLE_MAX_ELT_LEN);
	snprintf(result_table[result_row][1], TABLE_MAX_ELT_LEN, "%d",
		test_nbr);
	strncpy(result_table[result_row][2], "100%", TABLE_MAX_ELT_LEN);
	result_row++;
	strncpy(result_table[result_row][0], "Number of tests passed",
		TABLE_MAX_ELT_LEN);
	snprintf(result_table[result_row][1], TABLE_MAX_ELT_LEN, "%d",
		test_nbr - *err_nbr - *wng_nbr);
	snprintf(result_table[result_row][2], TABLE_MAX_ELT_LEN,
		"%.2lf%%", (double)
		((test_nbr - *err_nbr - *wng_nbr)  * 100) / test_nbr);
	result_row++;
	strncpy(result_table[result_row][0], "Number of tests passed "
		"with warning(s)", TABLE_MAX_ELT_LEN);
	snprintf(result_table[result_row][1], TABLE_MAX_ELT_LEN, "%d",
		*wng_nbr);
	snprintf(result_table[result_row][2], TABLE_MAX_ELT_LEN,
		"%.2lf%%", (double) (*wng_nbr * 100) / test_nbr);
	result_row++;

	strncpy(result_table[result_row][0], "Number of tests failed",
		TABLE_MAX_ELT_LEN);
	snprintf(result_table[result_row][1], TABLE_MAX_ELT_LEN, "%d",
		*err_nbr);
	snprintf(result_table[result_row][2], TABLE_MAX_ELT_LEN,
		"%.2lf%%", (double) (*err_nbr * 100) / test_nbr);
	result_row++;

	/* Save audit data into files & print results on screen */
	for (i = 0; i < 3; i++) {
		if (output_streams[i] == NULL)
			continue;

		autoadjust_table_fprint(output_streams[i], table, row, 4);

		fprintf(output_streams[i], "Notes:\n");
		fprintf(output_streams[i], " (1) Cannot be tested due to "
			"OMAPCONF execution that falses the result.\n");
		fprintf(output_streams[i], " (2) Due to auto-gating/auto-idle,"
			" item may be either gated/idle or running at the time "
			"status is read.\n");
		fprintf(output_streams[i], " (3) Cannot be tested due to "
			"disabled sensors in SR class 1.5 (outside of periodic "
			"recalibration).\n");
		fprintf(output_streams[i], " (4) For full audit details, use "
			"\"full_log\" and check \"%s\" file.\n\n",
			omap4_use_case_details_filename_table[uc_id]);

		autoadjust_table_fprint(output_streams[i],
			result_table, result_row, 3);

		fprintf(output_streams[i], "%s Use-Case Audit summary saved "
			"in \"%s\" file.\n",
			omap4_use_case_name_table[uc_id],
			omap4_use_case_summary_filename_table[uc_id]);

		if (full_log)
			fprintf(output_streams[i],
				"%s Use-Case Audit details saved in "
				"\"%s\" file.\n\n",
				omap4_use_case_name_table[uc_id],
				omap4_use_case_details_filename_table[uc_id]);
		else
			fprintf(output_streams[i], "\n");

		if (*err_nbr == 0) {
			fprintf(output_streams[i], "SUCCESS! %s Use-Case Power"
				" Settings Audit completed with 0 error "
				"(%d warning(s)).\n\n",
				omap4_use_case_name_table[uc_id], *wng_nbr);
		} else {
			fprintf(output_streams[i], "FAILED! %s Use-Case Power "
				"Settings Audit completed with "
				"%d error(s) and %d warning(s).\n\n",
				omap4_use_case_name_table[uc_id],
				*err_nbr, *wng_nbr);
		}

	}

	/* Close opened files */
	if (fp_summary != NULL)
		fclose(fp_summary);
	if (fp_details != NULL)
		fclose(fp_details);

	/* Restore CPUFreq governor */
	cpufreq_scaling_governor_set(prev_gov, prev_gov2);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		uc_audit44xx_main
 * @BRIEF		main entry point
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		main entry point
 *//*------------------------------------------------------------------------ */
int uc_audit44xx_main(int argc, char *argv[])
{
	unsigned int err_nbr = 0, wng_nbr = 0;
	int ret;

	if (!cpu_is_omap44xx())
		return OMAPCONF_ERR_CPU;

	if (argc == 2) {
		if (strcmp(argv[1], "os_idle") == 0) {
			ret = use_case_audit44xx(OMAP4_UC_OS_IDLE,
				&err_nbr, &wng_nbr, 1, 0);
		} else if (strcmp(argv[1], "mp3") == 0) {
			ret = use_case_audit44xx(OMAP4_UC_MP3_PLAYBACK,
				&err_nbr, &wng_nbr, 1, 0);
		} else if (strcmp(argv[1], "rec1080p") == 0) {
			ret = use_case_audit44xx(OMAP4_UC_AVRECORD_1080P,
				&err_nbr, &wng_nbr, 1, 0);
		} else if (strcmp(argv[1], "play720p") == 0) {
			ret = use_case_audit44xx(OMAP4_UC_AVPLAYBACK_720P,
				&err_nbr, &wng_nbr, 1, 0);
		} else if (strcmp(argv[1], "play1080p") == 0) {
			ret = use_case_audit44xx(
				OMAP4_UC_AVPLAYBACK_1080P,
				&err_nbr, &wng_nbr, 1, 0);
		} else if (strcmp(argv[1], "homescreen") == 0) {
			ret = use_case_audit44xx(OMAP4_UC_HOME_SCREEN,
				&err_nbr, &wng_nbr, 1, 0);
		} else {
			help(HELP_AUDIT);
			ret = OMAPCONF_ERR_ARG;
		}
	} else if ((argc == 3) &&
		(strcmp(argv[2], "full_log") == 0)) {
		if (strcmp(argv[1], "os_idle") == 0) {
			ret = use_case_audit44xx(OMAP4_UC_OS_IDLE,
				&err_nbr, &wng_nbr, 1, 1);
		} else if (strcmp(argv[1], "mp3") == 0) {
			ret = use_case_audit44xx(OMAP4_UC_MP3_PLAYBACK,
				&err_nbr, &wng_nbr, 1, 1);
		} else if (strcmp(argv[1], "rec1080p") == 0) {
			ret = use_case_audit44xx(OMAP4_UC_AVRECORD_1080P,
				&err_nbr, &wng_nbr, 1, 1);
		} else if (strcmp(argv[1], "play720p") == 0) {
			ret = use_case_audit44xx(OMAP4_UC_AVPLAYBACK_720P,
				&err_nbr, &wng_nbr, 1, 1);
		} else if (strcmp(argv[1], "play1080p") == 0) {
			ret = use_case_audit44xx(
				OMAP4_UC_AVPLAYBACK_1080P,
				&err_nbr, &wng_nbr, 1, 1);
		} else if (strcmp(argv[1], "homescreen") == 0) {
			ret = use_case_audit44xx(OMAP4_UC_HOME_SCREEN,
				&err_nbr, &wng_nbr, 1, 1);
		} else {
			help(HELP_AUDIT);
			ret = OMAPCONF_ERR_ARG;
		}
	} else {
		help(HELP_AUDIT);
		ret = OMAPCONF_ERR_ARG;
	}

	return ret;
}
