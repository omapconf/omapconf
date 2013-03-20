/*
 *
 * @Component			OMAPCONF
 * @Filename			module54xx.c
 * @Description			OMAP5 Module Definitions & APIs
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


#include <module54xx.h>
#include <lib.h>
#include <string.h>
#include <stdio.h>
#include <cpuinfo.h>
#include <cm54xx-defs.h>
#include <prm54xx-defs.h>
#include <sysconfig54xx-defs.h>
#include <module.h>
#include <clockdomain.h>
#include <powerdomain.h>
#include <voltdomain.h>
#include <opp.h>


/* #define MODULE54XX_DEBUG */
#ifdef MODULE54XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static unsigned short mod54xx_init_done = 0;
genlist mod54xx_list;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod5430_init
 * @BRIEF		initialize internal data for OMAP5430
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void mod5430_init(void)
{
	mod_info mod;
	mod_opp opp;

	if (mod54xx_init_done)
		return;

	genlist_init(&mod54xx_list);

	/* Voltage dom.: WKUP, Power dom.: EMU, Clock dom. = EMU */
	mod.name = MOD_DEBUGSS;
	mod.id = (int) OMAP5_DEBUGSS;
	mod.clkdm = CLKDM_EMU;
	mod.pwrdm = PWRDM_EMU;
	mod.voltdm = VDD_WKUP;
	mod.clk = (int) CLK54XX_EMU_SYS_CLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_emu_debugss_clkctrl;
		mod.context = &omap5430es1_rm_emu_debugss_context;
	} else {
		mod.clkctrl = &omap5430_cm_emu_debugss_clkctrl;
		mod.context = &omap5430_rm_emu_debugss_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: WKUP, Power dom.: WKUPAON, Clock domain = WKUPAON */
	mod.name = MOD_CTRL_MODULE_WKUP;
	mod.id = (int) OMAP5_CTRL_MODULE_WKUP;
	mod.clkdm = CLKDM_WKUPAON;
	mod.pwrdm = PWRDM_WKUPAON;
	mod.voltdm = VDD_WKUP;
	mod.clk = (int) CLK54XX_WKUPAON_GICLK;
	mod.sysconfig = NULL;
	mod.clkctrl = NULL;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_L4_WKUP_INTERCONNECT;
	mod.id = (int) OMAP5_L4WKUP_INTERCONNECT;
	mod.clkdm = CLKDM_WKUPAON;
	mod.pwrdm = PWRDM_WKUPAON;
	mod.voltdm = VDD_WKUP;
	mod.clk = (int) CLK54XX_WKUPAON_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_wkupaon_l4_wkup_clkctrl;
		mod.context = &omap5430es1_rm_wkupaon_l4_wkup_context;
	} else {
		mod.clkctrl = &omap5430_cm_wkupaon_l4_wkup_clkctrl;
		mod.context = &omap5430_rm_wkupaon_l4_wkup_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_GPIO1;
	mod.id = (int) OMAP5_GPIO1;
	mod.clkdm = CLKDM_WKUPAON;
	mod.pwrdm = PWRDM_WKUPAON;
	mod.voltdm = VDD_WKUP;
	mod.clk = (int) CLK54XX_WKUPAON_32K_GFCLK;
	mod.sysconfig = &omap5430_gpio1_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_wkupaon_gpio1_clkctrl;
		mod.context = &omap5430es1_rm_wkupaon_gpio1_context;
	} else {
		mod.clkctrl = &omap5430_cm_wkupaon_gpio1_clkctrl;
		mod.context = &omap5430_rm_wkupaon_gpio1_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_ENAWAKEUP_BIT;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_TIMER1;
	mod.id = (int) OMAP5_TIMER1;
	mod.clkdm = CLKDM_WKUPAON;
	mod.pwrdm = PWRDM_WKUPAON;
	mod.voltdm = VDD_WKUP;
	mod.clk = (int) CLK54XX_TIMER1_GFCLK;
	mod.sysconfig = &omap5430_timer1_tiocp_cfg;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_wkupaon_timer1_clkctrl;
		mod.context = &omap5430es1_rm_wkupaon_timer1_context;
	} else {
		mod.clkctrl = &omap5430_cm_wkupaon_timer1_clkctrl;
		mod.context = &omap5430_rm_wkupaon_timer1_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_WD_TIMER2;
	mod.id = (int) OMAP5_WD_TIMER2;
	mod.clkdm = CLKDM_WKUPAON;
	mod.pwrdm = PWRDM_WKUPAON;
	mod.voltdm = VDD_WKUP;
	mod.clk = (int) CLK54XX_WKUPAON_32K_GFCLK;
	mod.sysconfig = &omap5430_wd_timer2_l4interconnect_wdsc;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_wkupaon_wd_timer2_clkctrl;
		mod.context = &omap5430es1_rm_wkupaon_wd_timer2_context;
	} else {
		mod.clkctrl = &omap5430_cm_wkupaon_wd_timer2_clkctrl;
		mod.context = &omap5430_rm_wkupaon_wd_timer2_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_SARRAM;
	mod.id = (int) OMAP5_SARRAM;
	mod.clkdm = CLKDM_WKUPAON;
	mod.pwrdm = PWRDM_WKUPAON;
	mod.voltdm = VDD_WKUP;
	mod.clk = (int) CLK54XX_WKUPAON_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_wkupaon_sar_ram_clkctrl;
		mod.context = &omap5430es1_rm_wkupaon_sar_ram_context;
	} else {
		mod.clkctrl = &omap5430_cm_wkupaon_sar_ram_clkctrl;
		mod.context = &omap5430_rm_wkupaon_sar_ram_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_COUNTER_32K;
	mod.id = (int) OMAP5_COUNTER_32K;
	mod.clkdm = CLKDM_WKUPAON;
	mod.pwrdm = PWRDM_WKUPAON;
	mod.voltdm = VDD_WKUP;
	mod.clk = (int) CLK54XX_FUNC_32K_CLK;
	mod.sysconfig = &omap5430_counter_32k_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_wkupaon_counter_32k_clkctrl;
		mod.context = &omap5430es1_rm_wkupaon_counter_32k_context;
	} else {
		mod.clkctrl = &omap5430_cm_wkupaon_counter_32k_clkctrl;
		mod.context = &omap5430_rm_wkupaon_counter_32k_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE4;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_KEYBOARD;
	mod.id = (int) OMAP5_KBD;
	mod.clkdm = CLKDM_WKUPAON;
	mod.pwrdm = PWRDM_WKUPAON;
	mod.voltdm = VDD_WKUP;
	mod.clk = (int) CLK54XX_WKUPAON_32K_GFCLK;
	mod.sysconfig = &omap5430_kbd_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_wkupaon_kbd_clkctrl;
		mod.context = &omap5430es1_rm_wkupaon_kbd_context;
	} else {
		mod.clkctrl = &omap5430_cm_wkupaon_kbd_clkctrl;
		mod.context = &omap5430_rm_wkupaon_kbd_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE4;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	if (cpu_revision_get() != REV_ES1_0) {
		mod.name = MOD_IO_SRCOMP_WKUP;
		mod.id = (int) OMAP5_IO_SRCOMP_WKUP;
		mod.clkdm = CLKDM_WKUPAON;
		mod.pwrdm = PWRDM_WKUPAON;
		mod.voltdm = VDD_WKUP;
		mod.clk = (int) CLK54XX_WKUPAON_IO_SRCOMP_GFCLK;
		mod.sysconfig = NULL;
		mod.clkctrl = &omap5430es1_cm_wkupaon_io_srcomp_clkctrl;
		mod.context = NULL;
		genlist_init(&(mod.mod_opp_list));
		opp.name = OPP_LOW;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 19200;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_HIGH;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_SB;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		mod.properties = MOD_HAS_NO_IDLE_STATUS;
		genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));
	}


	/* HS/EMU ONLY */
	mod.name = MOD_TIMER12;
	mod.id = (int) OMAP5_TIMER12;
	mod.clkdm = CLKDM_WKUPAON;
	mod.pwrdm = PWRDM_WKUPAON;
	mod.voltdm = VDD_WKUP;
	mod.clk = (int) CLK54XX_SECURE_32K_CLK;
	mod.sysconfig = NULL;
	mod.clkctrl = NULL;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_WD_TIMER1;
	mod.id = (int) OMAP5_WDT1;
	mod.clkdm = CLKDM_WKUPAON;
	mod.pwrdm = PWRDM_WKUPAON;
	mod.voltdm = VDD_WKUP;
	mod.clk = (int) CLK54XX_SECURE_32K_CLK;
	mod.sysconfig = NULL;
	mod.clkctrl = NULL;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = COREAON */
	mod.name = MOD_SMARTREFLEX_CORE;
	mod.id = (int) OMAP5_SMARTREFLEX_CORE;
	mod.clkdm = CLKDM_COREAON;
	mod.pwrdm = PWRDM_COREAON;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_SR_CORE_SYS_GFCLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_coreaon_smartreflex_core_clkctrl;
		mod.context = &omap5430es1_rm_coreaon_smartreflex_core_context;
	} else {
		mod.clkctrl = &omap5430_cm_coreaon_smartreflex_core_clkctrl;
		mod.context = &omap5430_rm_coreaon_smartreflex_core_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_SMARTREFLEX_MM;
	mod.id = (int) OMAP5_SMARTREFLEX_MM;
	mod.clkdm = CLKDM_COREAON;
	mod.pwrdm = PWRDM_COREAON;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_SR_MM_SYS_GFCLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_coreaon_smartreflex_mm_clkctrl;
		mod.context = &omap5430es1_rm_coreaon_smartreflex_mm_context;
	} else {
		mod.clkctrl = &omap5430_cm_coreaon_smartreflex_mm_clkctrl;
		mod.context = &omap5430_rm_coreaon_smartreflex_mm_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_SMARTREFLEX_MPU;
	mod.id = (int) OMAP5_SMARTREFLEX_MPU;
	mod.clkdm = CLKDM_COREAON;
	mod.pwrdm = PWRDM_COREAON;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_SR_MPU_SYS_GFCLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_coreaon_smartreflex_mpu_clkctrl;
		mod.context = &omap5430es1_rm_coreaon_smartreflex_mpu_context;
	} else {
		mod.clkctrl = &omap5430_cm_coreaon_smartreflex_mpu_clkctrl;
		mod.context = &omap5430_rm_coreaon_smartreflex_mpu_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	if (cpu_revision_get() == REV_ES1_0) {
		mod.name = MOD_BANDGAPTS;
		mod.id = (int) OMAP5_BANDGAPTS;
		mod.clkdm = CLKDM_COREAON;
		mod.pwrdm = PWRDM_COREAON;
		mod.voltdm = VDD_CORE;
		mod.clk = (int) CLK54XX_COREAON_TS_GFCLK;
		mod.sysconfig = NULL;
		mod.clkctrl = &omap5430es1_cm_coreaon_bandgap_clkctrl;
		mod.context = NULL;
		genlist_init(&(mod.mod_opp_list));
		opp.name = OPP_LOW;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 1200;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_HIGH;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_SB;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		mod.properties = MOD_HAS_NO_IDLE_STATUS;
		genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));
	}


	if (cpu_revision_get() != REV_ES1_0) {
		mod.name = MOD_IO_SRCOMP_CORE;
		mod.id = (int) OMAP5_IO_SRCOMP_CORE;
		mod.clkdm = CLKDM_COREAON;
		mod.pwrdm = PWRDM_COREAON;
		mod.voltdm = VDD_CORE;
		mod.clk = (int) CLK54XX_COREAON_IO_SRCOMP_GFCLK;
		mod.sysconfig = NULL;
		mod.clkctrl = &omap5430_cm_coreaon_io_srcomp_clkctrl;
		mod.context = NULL;
		genlist_init(&(mod.mod_opp_list));
		opp.name = OPP_LOW;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 19200;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_HIGH;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_SB;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		mod.properties = MOD_HAS_NO_IDLE_STATUS;
		genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));
	}

	if (cpu_revision_get() == REV_ES1_0) {
		mod.name = MOD_USB_PHY_CORE;
		mod.id = (int) OMAP5_USB_PHY_CORE;
		mod.clkctrl = &omap5430es1_cm_coreaon_usb_phy_core_clkctrl;
	} else {
		mod.name = MOD_USB2PHY;
		mod.id = (int) OMAP5_USB2PHY;
		mod.clkctrl = &omap5430_cm_coreaon_usb_phy_core_clkctrl;
	}
	mod.clkdm = CLKDM_COREAON;
	mod.pwrdm = PWRDM_COREAON;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_COREAON_32K_GFCLK;
	mod.sysconfig = NULL;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_NO_IDLE_STATUS;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: CAM, Clock domain = CAM */
	mod.name = MOD_FDIF;
	mod.id = (int) OMAP5_FDIF;
	mod.clkdm = CLKDM_CAM;
	mod.pwrdm = PWRDM_CAM;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_FDIF_GFCLK;
	mod.sysconfig = &omap5430_fdif_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_cam_fdif_clkctrl;
		mod.context = &omap5430es1_rm_cam_fdif_context;
	} else {
		mod.clkctrl = &omap5430_cm_cam_fdif_clkctrl;
		mod.context = &omap5430_rm_cam_fdif_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 128000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 128000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_STANDBY_MODE5;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_ISS;
	mod.id = (int) OMAP5_ISS;
	mod.clkdm = CLKDM_CAM;
	mod.pwrdm = PWRDM_CAM;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_CORE_ISS_MAIN_CLK;
	mod.sysconfig = &omap5430_iss_hl_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_cam_iss_clkctrl;
		mod.context = &omap5430es1_rm_cam_iss_context;
	} else {
		mod.clkctrl = &omap5430_cm_cam_iss_clkctrl;
		mod.context = &omap5430_rm_cam_iss_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 152000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 304000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 151954;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 303908;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_CAL;
	mod.id = (int) OMAP5_CAL;
	mod.clkdm = CLKDM_CAM;
	mod.pwrdm = PWRDM_CAM;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_CAM_L3_GICLK;
	mod.sysconfig = &omap5430_cal_hl_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_cam_cal_clkctrl;
		mod.context = &omap5430es1_rm_cam_cal_context;
	} else {
		mod.clkctrl = &omap5430_cm_cam_cal_clkctrl;
		mod.context = &omap5430_rm_cam_cal_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 266000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 265919;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L4CFG */
	mod.name = MOD_CTRL_MODULE_CORE;
	mod.id = (int) OMAP5_CTRL_MODULE_CORE;
	mod.clkdm = CLKDM_L4_CFG;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4CFG_L4_GICLK;
	mod.sysconfig = NULL;
	mod.clkctrl = NULL;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 66500;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 66479;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_SPINLOCK;
	mod.id = (int) OMAP5_SPINLOCK;
	mod.clkdm = CLKDM_L4_CFG;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4CFG_L4_GICLK;
	mod.sysconfig = &omap5430_spinlock_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4cfg_spinlock_clkctrl;
		mod.context = &omap5430es1_rm_l4cfg_spinlock_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4cfg_spinlock_clkctrl;
		mod.context = &omap5430_rm_l4cfg_spinlock_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 66500;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 66479;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_IDLE_MODE4 | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_L4_CFG_INTERCONNECT;
	mod.id = (int) OMAP5_L4_CFG_INTERCONNECT;
	mod.clkdm = CLKDM_L4_CFG;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4CFG_L4_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4cfg_l4_cfg_clkctrl;
		mod.context = &omap5430es1_rm_l4cfg_l4_cfg_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4cfg_l4_cfg_clkctrl;
		mod.context = &omap5430_rm_l4cfg_l4_cfg_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 66500;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 66479;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MAILBOX;
	mod.id = (int) OMAP5_MAILBOX;
	mod.clkdm = CLKDM_L4_CFG;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4CFG_L4_GICLK;
	mod.sysconfig = &omap5430_mailbox_l4_cfginterconnect_mailbox_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4cfg_mailbox_clkctrl;
		mod.context = &omap5430es1_rm_l4cfg_mailbox_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4cfg_mailbox_clkctrl;
		mod.context = &omap5430_rm_l4cfg_mailbox_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 66500;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 66479;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_SARROM;
	mod.id = (int) OMAP5_SARROM;
	mod.clkdm = CLKDM_L4_CFG;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4CFG_L4_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4cfg_sar_rom_clkctrl;
		mod.context = &omap5430es1_rm_l4cfg_sar_rom_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4cfg_sar_rom_clkctrl;
		mod.context = &omap5430_rm_l4cfg_sar_rom_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 66500;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 66479;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_OCP2SCP2;
	mod.id = (int) OMAP5_OCP2SCP2;
	mod.clkdm = CLKDM_L4_CFG;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4CFG_L4_GICLK;
	mod.sysconfig = &omap5430_ocp2scp2_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4cfg_ocp2scp2_clkctrl;
		mod.context = &omap5430es1_rm_l4cfg_ocp2scp2_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4cfg_ocp2scp2_clkctrl;
		mod.context = &omap5430_rm_l4cfg_ocp2scp2_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 66500;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 66479;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = EMIF */
	mod.name = MOD_PHY_EMIF;
	mod.id = (int) OMAP5_PHY_EMIF;
	mod.clkdm = CLKDM_EMIF;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_EMIF_PHY_GCLK;
	mod.sysconfig = NULL;
	mod.clkctrl = NULL;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 266000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 532000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 265919;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 531838;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_DLL_EMIF;
	mod.id = (int) OMAP5_DLL_EMIF;
	mod.clkdm = CLKDM_EMIF;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_CORE_DLL_GCLK;
	mod.sysconfig = NULL;
	mod.clkctrl = NULL;
	if (cpu_revision_get() == REV_ES1_0)
		mod.context = &omap5430es1_rm_emif_emif_dll_context;
	else
		mod.context = &omap5430_rm_emif_emif_dll_context;
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 266000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 266000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 265919;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 265919;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_DMM;
	mod.id = (int) OMAP5_DMM;
	mod.clkdm = CLKDM_EMIF;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_EMIF_L3_GICLK;
	mod.sysconfig = &omap5430_dmm_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_emif_dmm_clkctrl;
		mod.context = &omap5430es1_rm_emif_dmm_context;
	} else {
		mod.clkctrl = &omap5430_cm_emif_dmm_clkctrl;
		mod.context = &omap5430_rm_emif_dmm_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 266000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 265919;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_EMIF1;
	mod.id = (int) OMAP5_EMIF1;
	mod.clkdm = CLKDM_EMIF;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_EMIF_L3_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_emif_emif1_clkctrl;
		mod.context = &omap5430es1_rm_emif_emif1_context;
	} else {
		mod.clkctrl = &omap5430_cm_emif_emif1_clkctrl;
		mod.context = &omap5430_rm_emif_emif1_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 266000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 265919;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_EMIF2;
	mod.id = (int) OMAP5_EMIF2;
	mod.clkdm = CLKDM_EMIF;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_EMIF_L3_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_emif_emif2_clkctrl;
		mod.context = &omap5430es1_rm_emif_emif2_context;
	} else {
		mod.clkctrl = &omap5430_cm_emif_emif2_clkctrl;
		mod.context = &omap5430_rm_emif_emif2_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 266000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 265919;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_EMIF_OCP_FW;
	mod.id = (int) OMAP5_EMIF_OCP_FW;
	mod.clkdm = CLKDM_EMIF;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_EMIF_L3_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_emif_emif_ocp_fw_clkctrl;
		mod.context = &omap5430es1_rm_emif_emif_fw_context;
	} else {
		mod.clkctrl = &omap5430_cm_emif_emif_ocp_fw_clkctrl;
		mod.context = &omap5430_rm_emif_emif_fw_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 266000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 265919;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = IPU */
	mod.name = MOD_IPU;
	mod.id = (int) OMAP5_IPU;
	mod.clkdm = CLKDM_IPU;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_CORE_IPU_ISS_BOOST_CLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_ipu_ipu_clkctrl;
		mod.context = &omap5430es1_rm_ipu_ipu_context;
	} else {
		mod.clkctrl = &omap5430_cm_ipu_ipu_clkctrl;
		mod.context = &omap5430_rm_ipu_ipu_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 212800;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 425600;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 212735;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 425471;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN2 */
	mod.name = MOD_GPMC;
	mod.id = (int) OMAP5_GPMC;
	mod.clkdm = CLKDM_L3_MAIN2;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L3MAIN2_L3_GICLK;
	mod.sysconfig = &omap5430_gpmc_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3main2_gpmc_clkctrl;
		mod.context = &omap5430es1_rm_l3main2_gpmc_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3main2_gpmc_clkctrl;
		mod.context = &omap5430_rm_l3main2_gpmc_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 266000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 265919;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_L3_MAIN2_INTERCONNECT;
	mod.id = (int) OMAP5_L3_MAIN2_INTERCONNECT;
	mod.clkdm = CLKDM_L3_MAIN2;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L3MAIN2_L3_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3main2_l3_main_2_clkctrl;
		mod.context = &omap5430es1_rm_l3main2_l3_main_2_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3main2_l3_main_2_clkctrl;
		mod.context = &omap5430_rm_l3main2_l3_main_2_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 266000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 265919;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_OCMC_RAM;
	mod.id = (int) OMAP5_OCMC_RAM;
	mod.clkdm = CLKDM_L3_MAIN2;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L3MAIN2_L3_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3main2_ocmc_ram_clkctrl;
		mod.context = &omap5430es1_rm_l3main2_ocmc_ram_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3main2_ocmc_ram_clkctrl;
		mod.context = &omap5430_rm_l3main2_ocmc_ram_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 266000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 265919;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_INSTR */
	mod.name = MOD_L3_MAIN3_INTERCONNECT;
	mod.id = (int) OMAP5_L3_MAIN3_INTERCONNECT;
	mod.clkdm = CLKDM_L3_INSTR;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L3INSTR_L3_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3instr_l3_main_3_clkctrl;
		mod.context = &omap5430es1_rm_l3instr_l3_main_3_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3instr_l3_main_3_clkctrl;
		mod.context = &omap5430_rm_l3instr_l3_main_3_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 266000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 265919;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_L3_INSTR_INTERCONNECT;
	mod.id = (int) OMAP5_L3_INSTR_INTERCONNECT;
	mod.clkdm = CLKDM_L3_INSTR;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L3INSTR_L3_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3instr_l3_instr_clkctrl;
		mod.context = &omap5430es1_rm_l3instr_l3_instr_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3instr_l3_instr_clkctrl;
		mod.context = &omap5430_rm_l3instr_l3_instr_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 266000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 265919;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_OCP_WP_NOC;
	mod.id = (int) OMAP5_OCP_WP_NOC;
	mod.clkdm = CLKDM_L3_INSTR;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L3INSTR_L3_GICLK;
	mod.sysconfig = &omap5430_ocp_wp_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3instr_ocp_wp_noc_clkctrl;
		mod.context = &omap5430es1_rm_l3instr_ocp_wp_noc_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3instr_ocp_wp_noc_clkctrl;
		mod.context = &omap5430_rm_l3instr_ocp_wp_noc_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 266000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 265919;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	if (cpu_revision_get() != REV_ES1_0) {
		mod.name = MOD_CTRL_MODULE_BANDGAP;
		mod.id = (int) OMAP5_CTRL_MODULE_BANDGAP;
		mod.clkdm = CLKDM_L3_INSTR;
		mod.pwrdm = PWRDM_CORE;
		mod.voltdm = VDD_CORE;
		mod.clk = (int) CLK54XX_L3INSTR_TS_GFCLK;
		mod.sysconfig = NULL;
		mod.clkctrl = NULL;
		mod.context = NULL;
		genlist_init(&(mod.mod_opp_list));
		opp.name = OPP_LOW;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 1200;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_HIGH;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_SB;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		mod.properties = 0;
		genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));
	}

	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN1 */
	mod.name = MOD_L3_MAIN1_INTERCONNECT;
	mod.id = (int) OMAP5_L3_MAIN1_INTERCONNECT;
	mod.clkdm = CLKDM_L3_MAIN1;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L3MAIN1_L3_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3main1_l3_main_1_clkctrl;
		mod.context = &omap5430es1_rm_l3main1_l3_main_1_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3main1_l3_main_1_clkctrl;
		mod.context = &omap5430_rm_l3main1_l3_main_1_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp,
			sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 266000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp,
			sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp,
			sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 265919;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp,
			sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = C2C */
	mod.name = MOD_C2C;
	mod.id = (int) OMAP5_C2C;
	mod.clkdm = CLKDM_C2C;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clk = (int) CLK54XX_C2C_L3_GICLK;
		mod.sysconfig = &omap5430_c2c_sysconfig;
		mod.clkctrl = &omap5430es1_cm_c2c_c2c_clkctrl;
		mod.context = &omap5430es1_rm_c2c_c2c_context;
	} else {
		mod.clk = (int) CLK54XX_C2C_GFCLK;
		mod.sysconfig = &omap5430_c2c_sysconfig;
		mod.clkctrl = &omap5430_cm_c2c_c2c_clkctrl;
		mod.context = &omap5430_rm_c2c_c2c_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 266000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 177279;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 354559;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_C2C_OCP_FW;
	mod.id = (int) OMAP5_C2C_OCP_FW;
	mod.clkdm = CLKDM_C2C;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clk = (int) CLK54XX_C2C_L3_GICLK;
		mod.clkctrl = &omap5430es1_cm_c2c_c2c_ocp_fw_clkctrl;
		mod.context = &omap5430es1_rm_c2c_c2c_ocp_fw_context;
	} else {
		mod.clk = (int) CLK54XX_C2C_GICLK;
		mod.clkctrl = &omap5430_cm_c2c_c2c_ocp_fw_clkctrl;
		mod.context = &omap5430_rm_c2c_c2c_ocp_fw_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 266000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 88639;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 177279;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MODEM_ICR;
	mod.id = (int) OMAP5_MODEM_ICR;
	mod.clkdm = CLKDM_C2C;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_C2C_L4_GICLK;
	mod.sysconfig = &omap5430_modem_icr_mpu_pa_sys_config;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_c2c_modem_icr_clkctrl;
		mod.context = &omap5430es1_rm_c2c_modem_icr_context;
	} else {
		mod.clkctrl = &omap5430_cm_c2c_modem_icr_clkctrl;
		mod.context = &omap5430_rm_c2c_modem_icr_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 66500;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 66479;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = DMA */
	mod.name = MOD_DMA_SYSTEM;
	mod.id = (int) OMAP5_DMA_SYSTEM;
	mod.clkdm = CLKDM_DMA;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_DMA_L3_GICLK;
	mod.sysconfig = &omap5430_dma4_ocp_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_dma_dma_system_clkctrl;
		mod.context = &omap5430es1_rm_dma_dma_system_context;
	} else {
		mod.clkctrl = &omap5430_cm_dma_dma_system_clkctrl;
		mod.context = &omap5430_rm_dma_dma_system_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 266000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 265919;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_STANDBY_MODE13 | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = MIPIEXT */
	mod.name = MOD_LLI;
	mod.id = (int) OMAP5_LLI;
	mod.clkdm = CLKDM_MIPIEXT;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_UNIPRO1_PHY_GFCLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_mipiext_lli_clkctrl;
		mod.context = &omap5430es1_rm_mipiext_lli_context;
	} else {
		mod.clkctrl = &omap5430_cm_mipiext_lli_clkctrl;
		mod.context = &omap5430_rm_mipiext_lli_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 1457600;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 1457600;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_LLI_OCP_FW;
	mod.id = (int) OMAP5_LLI_OCP_FW;
	mod.clkdm = CLKDM_MIPIEXT;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_MIPIEXT_L3_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_mipiext_lli_ocp_fw_clkctrl;
		mod.context = &omap5430es1_rm_mipiext_lli_ocp_fw_context;
	} else {
		mod.clkctrl = &omap5430_cm_mipiext_lli_ocp_fw_clkctrl;
		mod.context = &omap5430_rm_mipiext_lli_ocp_fw_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 266000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 265919;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MPHY;
	mod.id = (int) OMAP5_MPHY;
	mod.clkdm = CLKDM_MIPIEXT;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_MIPIEXT_L4_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_mipiext_mphy_clkctrl;
		mod.context = &omap5430es1_rm_mipiext_mphy_context;
	} else {
		mod.clkctrl = &omap5430_cm_mipiext_mphy_clkctrl;
		mod.context = &omap5430_rm_mipiext_mphy_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 66500;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 66479;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	if (cpu_revision_get() == REV_ES1_0) {
		mod.name = MOD_UNIPRO1;
		mod.id = (int) OMAP5_UNIPRO1;
		mod.clkdm = CLKDM_MIPIEXT;
		mod.pwrdm = PWRDM_CORE;
		mod.voltdm = VDD_CORE;
		mod.clk = (int) CLK54XX_UNIPRO1_PHY_GFCLK;
		mod.sysconfig = &omap5430_unipro1_sysconfig;
		mod.clkctrl = &omap5430es1_cm_mipiext_unipro1_clkctrl;
		mod.context = &omap5430es1_rm_mipiext_unipro1_context;
		genlist_init(&(mod.mod_opp_list));
		opp.name = OPP_LOW;
		opp.rate = 1457600;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 1457600;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_HIGH;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_SB;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE;
		genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));
	}

	/* Voltage dom.: CORE, Power dom.: DSS, Clock domain = DSS */
	mod.name = MOD_DSS;
	mod.id = (int) OMAP5_DSS;
	mod.clkdm = CLKDM_DSS;
	mod.pwrdm = PWRDM_DSS;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_DSS_GFCLK;
	mod.sysconfig = &omap5430_dispc_l3_main_dispc_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_dss_dss_clkctrl;
		mod.context = &omap5430es1_rm_dss_dss_context;
	} else {
		mod.clkctrl = &omap5430_cm_dss_dss_clkctrl;
		mod.context = &omap5430_rm_dss_dss_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 192000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 192000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_IDLE_MODE4 | MOD_HAS_CLOCK_ACTIVITY_MODE | MOD_HAS_STANDBY_MODE13;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	if (cpu_revision_get() != REV_ES1_0) {
		mod.name = MOD_BB2D;
		mod.id = (int) OMAP5_BB2D;
		mod.clkdm = CLKDM_DSS;
		mod.pwrdm = PWRDM_DSS;
		mod.voltdm = VDD_CORE;
		mod.clk = (int) CLK54XX_BB2D_GFCLK;
		mod.sysconfig = NULL;
		mod.clkctrl = &omap5430es1_cm_dss_bb2d_clkctrl;
		mod.context = &omap5430es1_rm_dss_bb2d_context;
		genlist_init(&(mod.mod_opp_list));
		opp.name = OPP_LOW;
		opp.rate = 177279;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 354559;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_HIGH;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_SB;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		mod.properties = MOD_HAS_STANDBY_STATUS;
		genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));
	}

	/* Voltage dom.: CORE, Power dom.: L3INIT, Clock domain = L3INIT */
	mod.name = MOD_HSI;
	mod.id = (int) OMAP5_HSI;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_HSI_GFCLK;
	mod.sysconfig = &omap5430_hsi_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3init_hsi_clkctrl;
		mod.context = &omap5430es1_rm_l3init_hsi_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3init_hsi_clkctrl;
		mod.context = &omap5430_rm_l3init_hsi_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 192000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 192000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE13 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_IEEE1500_2_OCP;
	mod.id = (int) OMAP5_IEEE1500_2_OCP;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L3INIT_L3_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3init_ieee1500_2_ocp_clkctrl;
		mod.context = &omap5430es1_rm_l3init_ieee1500_2_ocp_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3init_ieee1500_2_ocp_clkctrl;
		mod.context = &omap5430_rm_l3init_ieee1500_2_ocp_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 266000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 265919;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MMC1;
	mod.id = (int) OMAP5_MMC1;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_MMC1_GFCLK;
	mod.sysconfig = &omap5430_mmchs1_hl_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3init_mmc1_clkctrl;
		mod.context = &omap5430es1_rm_l3init_mmc1_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3init_mmc1_clkctrl;
		mod.context = &omap5430_rm_l3init_mmc1_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MMC2;
	mod.id = (int) OMAP5_MMC2;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_MMC2_GFCLK;
	mod.sysconfig = &omap5430_mmchs2_hl_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3init_mmc2_clkctrl;
		mod.context = &omap5430es1_rm_l3init_mmc2_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3init_mmc2_clkctrl;
		mod.context = &omap5430_rm_l3init_mmc2_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_OCPSCP1;
	mod.id = (int) OMAP5_OCPSCP1;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L3INIT_L4_GICLK;
	mod.sysconfig = &omap5430_ocp2scp1_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3init_ocp2scp1_clkctrl;
		mod.context = &omap5430es1_rm_l3init_ocp2scp1_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3init_ocp2scp1_clkctrl;
		mod.context = &omap5430_rm_l3init_ocp2scp1_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 66500;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 66479;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_USB_HOST_HS;
	mod.id = (int) OMAP5_USB_HOST_HS;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_UTMI_P1_GFCLK;
	mod.sysconfig = &omap5430_uhh_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3init_usb_host_hs_clkctrl;
		mod.context = &omap5430es1_rm_l3init_usb_host_hs_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3init_usb_host_hs_clkctrl;
		mod.context = &omap5430_rm_l3init_usb_host_hs_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 60000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 60000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_USB_OTG_SS;
	mod.id = (int) OMAP5_USB_OTG_SS;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L3INIT_960M_FCLK;
	mod.sysconfig = &omap5430_usbotgss_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3init_usb_otg_ss_clkctrl;
		mod.context = &omap5430es1_rm_l3init_usb_otg_ss_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3init_usb_otg_ss_clkctrl;
		mod.context = &omap5430_rm_l3init_usb_otg_ss_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 960000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 960000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_USB_TLL_HS;
	mod.id = (int) OMAP5_USB_TLL_HS;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_TLL_CH0_GFCLK;
	mod.sysconfig = &omap5430_usbtll_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3init_usb_tll_hs_clkctrl;
		mod.context = &omap5430es1_rm_l3init_usb_tll_hs_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3init_usb_tll_hs_clkctrl;
		mod.context = &omap5430_rm_l3init_usb_tll_hs_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 60000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 60000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_IDLE_MODE4;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_SATA;
	mod.id = (int) OMAP5_SATA;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L3INIT_L3_GICLK;
	mod.sysconfig = &omap5430_sata_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3init_sata_clkctrl;
		mod.context = &omap5430es1_rm_l3init_sata_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3init_sata_clkctrl;
		mod.context = &omap5430_rm_l3init_sata_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 266000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 265919;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_UNIPRO2;
	mod.id = (int) OMAP5_UNIPRO2;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_UNIPRO2_PHY_GFCLK;
	mod.sysconfig = &omap5430_unipro2_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3init_unipro2_clkctrl;
		mod.context = &omap5430es1_rm_l3init_unipro2_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3init_unipro2_clkctrl;
		mod.context = &omap5430_rm_l3init_unipro2_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 1457600;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 1457600;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MPHY_UNIPRO2;
	mod.id = (int) OMAP5_MPHY_UNIPRO2;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L3INIT_L4_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0)
		mod.clkctrl = &omap5430es1_cm_l3init_mphy_unipro2_clkctrl;
	else
		mod.clkctrl = &omap5430_cm_l3init_mphy_unipro2_clkctrl;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 66500;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 66479;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_OCPSCP3;
	mod.id = (int) OMAP5_OCPSCP3;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L3INIT_L4_GICLK;
	mod.sysconfig = &omap5430_ocp2scp3_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3init_ocp2scp3_clkctrl;
		mod.context = &omap5430es1_rm_l3init_ocp2scp3_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3init_ocp2scp3_clkctrl;
		mod.context = &omap5430_rm_l3init_ocp2scp3_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 66500;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 66479;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_PER */
	mod.name = MOD_TIMER10;
	mod.id = (int) OMAP5_TIMER10;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_TIMER10_GFCLK;
	mod.sysconfig = &omap5430_timer10_l4interconnect_tiocp_cfg;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_timer10_clkctrl;
		mod.context = &omap5430es1_rm_l4per_timer10_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_timer10_clkctrl;
		mod.context = &omap5430_rm_l4per_timer10_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_TIMER11;
	mod.id = (int) OMAP5_TIMER11;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_TIMER11_GFCLK;
	mod.sysconfig = &omap5430_timer11_l4interconnect_tiocp_cfg;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_timer11_clkctrl;
		mod.context = &omap5430es1_rm_l4per_timer11_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_timer11_clkctrl;
		mod.context = &omap5430_rm_l4per_timer11_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_TIMER2;
	mod.id = (int) OMAP5_TIMER2;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_TIMER2_GFCLK;
	mod.sysconfig = &omap5430_timer2_l4interconnect_tiocp_cfg;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_timer2_clkctrl;
		mod.context = &omap5430es1_rm_l4per_timer2_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_timer2_clkctrl;
		mod.context = &omap5430_rm_l4per_timer2_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_TIMER3;
	mod.id = (int) OMAP5_TIMER3;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_TIMER3_GFCLK;
	mod.sysconfig = &omap5430_timer3_l4interconnect_tiocp_cfg;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_timer3_clkctrl;
		mod.context = &omap5430es1_rm_l4per_timer3_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_timer3_clkctrl;
		mod.context = &omap5430_rm_l4per_timer3_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_TIMER4;
	mod.id = (int) OMAP5_TIMER4;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_TIMER4_GFCLK;
	mod.sysconfig = &omap5430_timer4_l4interconnect_tiocp_cfg;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_timer4_clkctrl;
		mod.context = &omap5430es1_rm_l4per_timer4_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_timer4_clkctrl;
		mod.context = &omap5430_rm_l4per_timer4_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_TIMER9;
	mod.id = (int) OMAP5_TIMER9;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_TIMER9_GFCLK;
	mod.sysconfig = &omap5430_timer9_l4interconnect_tiocp_cfg;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_timer9_clkctrl;
		mod.context = &omap5430es1_rm_l4per_timer9_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_timer9_clkctrl;
		mod.context = &omap5430_rm_l4per_timer9_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_ELM;
	mod.id = (int) OMAP5_ELM;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4PER_L4_GICLK;
	mod.sysconfig = &omap5430_elm_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_elm_clkctrl;
		mod.context = &omap5430es1_rm_l4per_elm_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_elm_clkctrl;
		mod.context = &omap5430_rm_l4per_elm_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 66500;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 66479;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_GPIO2;
	mod.id = (int) OMAP5_GPIO2;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_32K_GFCLK;
	mod.sysconfig = &omap5430_gpio2_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_gpio2_clkctrl;
		mod.context = &omap5430es1_rm_l4per_gpio2_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_gpio2_clkctrl;
		mod.context = &omap5430_rm_l4per_gpio2_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_ENAWAKEUP_BIT;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_GPIO3;
	mod.id = (int) OMAP5_GPIO3;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_32K_GFCLK;
	mod.sysconfig = &omap5430_gpio3_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_gpio3_clkctrl;
		mod.context = &omap5430es1_rm_l4per_gpio3_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_gpio3_clkctrl;
		mod.context = &omap5430_rm_l4per_gpio3_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_ENAWAKEUP_BIT;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_GPIO4;
	mod.id = (int) OMAP5_GPIO4;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_32K_GFCLK;
	mod.sysconfig = &omap5430_gpio4_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_gpio4_clkctrl;
		mod.context = &omap5430es1_rm_l4per_gpio4_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_gpio4_clkctrl;
		mod.context = &omap5430_rm_l4per_gpio4_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_ENAWAKEUP_BIT;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_GPIO5;
	mod.id = (int) OMAP5_GPIO5;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_32K_GFCLK;
	mod.sysconfig = &omap5430_gpio5_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_gpio5_clkctrl;
		mod.context = &omap5430es1_rm_l4per_gpio5_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_gpio5_clkctrl;
		mod.context = &omap5430_rm_l4per_gpio5_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_ENAWAKEUP_BIT;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_GPIO6;
	mod.id = (int) OMAP5_GPIO6;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_32K_GFCLK;
	mod.sysconfig = &omap5430_gpio6_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_gpio6_clkctrl;
		mod.context = &omap5430es1_rm_l4per_gpio6_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_gpio6_clkctrl;
		mod.context = &omap5430_rm_l4per_gpio6_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_ENAWAKEUP_BIT;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_GPIO7;
	mod.id = (int) OMAP5_GPIO7;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_32K_GFCLK;
	mod.sysconfig = &omap5430_gpio7_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_gpio7_clkctrl;
		mod.context = &omap5430es1_rm_l4per_gpio7_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_gpio7_clkctrl;
		mod.context = &omap5430_rm_l4per_gpio7_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_ENAWAKEUP_BIT;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_GPIO8;
	mod.id = (int) OMAP5_GPIO8;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_32K_GFCLK;
	mod.sysconfig = &omap5430_gpio8_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_gpio8_clkctrl;
		mod.context = &omap5430es1_rm_l4per_gpio8_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_gpio8_clkctrl;
		mod.context = &omap5430_rm_l4per_gpio8_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_ENAWAKEUP_BIT;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_HDQ1W;
	mod.id = (int) OMAP5_HDQ1W;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_12M_GFCLK;
	mod.sysconfig = &omap5430_hdq_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_hdq1w_clkctrl;
		mod.context = &omap5430es1_rm_l4per_hdq1w_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_hdq1w_clkctrl;
		mod.context = &omap5430_rm_l4per_hdq1w_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 12000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 12000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_I2C1;
	mod.id = (int) OMAP5_I2C1;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_96M_GFCLK;
	mod.sysconfig = &omap5430_i2c1_sysc;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_i2c1_clkctrl;
		mod.context = &omap5430es1_rm_l4per_i2c1_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_i2c1_clkctrl;
		mod.context = &omap5430_rm_l4per_i2c1_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_I2C2;
	mod.id = (int) OMAP5_I2C2;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_96M_GFCLK;
	mod.sysconfig = &omap5430_i2c2_sysc;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_i2c2_clkctrl;
		mod.context = &omap5430es1_rm_l4per_i2c2_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_i2c2_clkctrl;
		mod.context = &omap5430_rm_l4per_i2c2_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_I2C3;
	mod.id = (int) OMAP5_I2C3;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_96M_GFCLK;
	mod.sysconfig = &omap5430_i2c3_sysc;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_i2c3_clkctrl;
		mod.context = &omap5430es1_rm_l4per_i2c3_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_i2c3_clkctrl;
		mod.context = &omap5430_rm_l4per_i2c3_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_I2C4;
	mod.id = (int) OMAP5_I2C4;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_96M_GFCLK;
	mod.sysconfig = &omap5430_i2c4_sysc;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_i2c4_clkctrl;
		mod.context = &omap5430es1_rm_l4per_i2c4_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_i2c4_clkctrl;
		mod.context = &omap5430_rm_l4per_i2c4_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_I2C5;
	mod.id = (int) OMAP5_I2C5;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_96M_GFCLK;
	mod.sysconfig = &omap5430_i2c5_sysc;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_i2c5_clkctrl;
		mod.context = &omap5430es1_rm_l4per_i2c5_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_i2c5_clkctrl;
		mod.context = &omap5430_rm_l4per_i2c5_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_L4_PER_INTERCONNECT;
	mod.id = (int) OMAP5_L4_PER_INTERCONNECT;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4PER_L4_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_l4_per_clkctrl;
		mod.context = &omap5430es1_rm_l4per_l4_per_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_l4_per_clkctrl;
		mod.context = &omap5430_rm_l4per_l4_per_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 66500;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 66479;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MCSPI1;
	mod.id = (int) OMAP5_MCSPI1;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_48M_GFCLK;
	mod.sysconfig = &omap5430_mcspi1_hl_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_mcspi1_clkctrl;
		mod.context = &omap5430es1_rm_l4per_mcspi1_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_mcspi1_clkctrl;
		mod.context = &omap5430_rm_l4per_mcspi1_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MCSPI2;
	mod.id = (int) OMAP5_MCSPI2;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_48M_GFCLK;
	mod.sysconfig = &omap5430_mcspi2_hl_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_mcspi2_clkctrl;
		mod.context = &omap5430es1_rm_l4per_mcspi2_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_mcspi2_clkctrl;
		mod.context = &omap5430_rm_l4per_mcspi2_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MCSPI3;
	mod.id = (int) OMAP5_MCSPI3;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_48M_GFCLK;
	mod.sysconfig = &omap5430_mcspi3_hl_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_mcspi3_clkctrl;
		mod.context = &omap5430es1_rm_l4per_mcspi3_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_mcspi3_clkctrl;
		mod.context = &omap5430_rm_l4per_mcspi3_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MCSPI4;
	mod.id = (int) OMAP5_MCSPI4;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_48M_GFCLK;
	mod.sysconfig = &omap5430_mcspi4_hl_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_mcspi4_clkctrl;
		mod.context = &omap5430es1_rm_l4per_mcspi4_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_mcspi4_clkctrl;
		mod.context = &omap5430_rm_l4per_mcspi4_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MMC3;
	mod.id = (int) OMAP5_MMC3;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_48M_GFCLK;
	mod.sysconfig = &omap5430_mmchs3_hl_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_mmc3_clkctrl;
		mod.context = &omap5430es1_rm_l4per_mmc3_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_mmc3_clkctrl;
		mod.context = &omap5430_rm_l4per_mmc3_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MMC4;
	mod.id = (int) OMAP5_MMC4;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_48M_GFCLK;
	mod.sysconfig = &omap5430_mmchs4_hl_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_mmc4_clkctrl;
		mod.context = &omap5430es1_rm_l4per_mmc4_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_mmc4_clkctrl;
		mod.context = &omap5430_rm_l4per_mmc4_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MMC5;
	mod.id = (int) OMAP5_MMC5;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_96M_GFCLK;
	mod.sysconfig = &omap5430_mmchs5_hl_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_mmc5_clkctrl;
		mod.context = &omap5430es1_rm_l4per_mmc5_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_mmc5_clkctrl;
		mod.context = &omap5430_rm_l4per_mmc5_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	if (cpu_revision_get() == REV_ES1_0) {
		mod.name = MOD_SLIMBUS2;
		mod.id = (int) OMAP5_SLIMBUS2;
		mod.clkdm = CLKDM_L4_PER;
		mod.pwrdm = PWRDM_L4_PER;
		mod.voltdm = VDD_CORE;
		mod.clk = (int) CLK54XX_PER_24M_GFCLK;
		mod.sysconfig = &omap5430_slimbus2_cmp_sysconfig;
		mod.clkctrl = &omap5430es1_cm_l4per_slimbus2_clkctrl;
		mod.context = &omap5430es1_rm_l4per_slimbus2_context;
		genlist_init(&(mod.mod_opp_list));
		opp.name = OPP_LOW;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_HIGH;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_SB;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT8 | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
		genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));
	}


	mod.name = MOD_UART1;
	mod.id = (int) OMAP5_UART1;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_48M_GFCLK;
	mod.sysconfig = &omap5430_uart1_sysc;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_uart1_clkctrl;
		mod.context = &omap5430es1_rm_l4per_uart1_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_uart1_clkctrl;
		mod.context = &omap5430_rm_l4per_uart1_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_UART2;
	mod.id = (int) OMAP5_UART2;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_48M_GFCLK;
	mod.sysconfig = &omap5430_uart2_sysc;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_uart2_clkctrl;
		mod.context = &omap5430es1_rm_l4per_uart2_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_uart2_clkctrl;
		mod.context = &omap5430_rm_l4per_uart2_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_UART3;
	mod.id = (int) OMAP5_UART3;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_48M_GFCLK;
	mod.sysconfig = &omap5430_uart3_sysc;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_uart3_clkctrl;
		mod.context = &omap5430es1_rm_l4per_uart3_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_uart3_clkctrl;
		mod.context = &omap5430_rm_l4per_uart3_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_UART4;
	mod.id = (int) OMAP5_UART4;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_48M_GFCLK;
	mod.sysconfig = &omap5430_uart4_sysc;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_uart4_clkctrl;
		mod.context = &omap5430es1_rm_l4per_uart4_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_uart4_clkctrl;
		mod.context = &omap5430_rm_l4per_uart4_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_UART5;
	mod.id = (int) OMAP5_UART5;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_48M_GFCLK;
	mod.sysconfig = &omap5430_uart5_sysc;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_uart5_clkctrl;
		mod.context = &omap5430es1_rm_l4per_uart5_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_uart5_clkctrl;
		mod.context = &omap5430_rm_l4per_uart5_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_UART6;
	mod.id = (int) OMAP5_UART6;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_48M_GFCLK;
	mod.sysconfig = &omap5430_uart6_sysc;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_uart6_clkctrl;
		mod.context = &omap5430es1_rm_l4per_uart6_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_uart6_clkctrl;
		mod.context = &omap5430_rm_l4per_uart6_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_SEC */
	/* HS/EMU ONLY */
	mod.name = MOD_DMA_CRYPTO;
	mod.id = (int) OMAP5_DMA_CRYPTO;
	mod.clkdm = CLKDM_L4_SEC;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4SEC_L3_GICLK;
	mod.sysconfig = NULL;
	mod.clkctrl = NULL;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 266000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 265919;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_AES1;
	mod.id = (int) OMAP5_AES1;
	mod.clkdm = CLKDM_L4_SEC;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4SEC_L3_GICLK;
	mod.sysconfig = NULL;
	mod.clkctrl = NULL;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 266000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 265919;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_AES2;
	mod.id = (int) OMAP5_AES2;
	mod.clkdm = CLKDM_L4_SEC;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4SEC_L3_GICLK;
	mod.sysconfig = NULL;
	mod.clkctrl = NULL;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 266000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 265919;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_SHA2MD5;
	mod.id = (int) OMAP5_SHA2MD5;
	mod.clkdm = CLKDM_L4_SEC;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4SEC_L3_GICLK;
	mod.sysconfig = NULL;
	mod.clkctrl = NULL;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 266000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 265919;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_RNG;
	mod.id = (int) OMAP5_RNG;
	mod.clkdm = CLKDM_L4_SEC;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4SEC_L4_GICLK;
	mod.sysconfig = NULL;
	mod.clkctrl = NULL;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 66500;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 66479;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_DES3DES;
	mod.id = (int) OMAP5_DES3DES;
	mod.clkdm = CLKDM_L4_SEC;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4SEC_L4_GICLK;
	mod.sysconfig = NULL;
	mod.clkctrl = NULL;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 66500;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 66479;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_PKA;
	mod.id = (int) OMAP5_PKA;
	mod.clkdm = CLKDM_L4_SEC;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4SEC_L4_GICLK;
	mod.sysconfig = NULL;
	mod.clkctrl = NULL;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 66500;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 66479;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 132959;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: ABE, Clock domain = ABE */
	mod.name = MOD_AESS;
	mod.id = (int) OMAP5_AESS;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_AESS_FCLK;
	mod.sysconfig = &omap5430_aess_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_abe_aess_clkctrl;
		mod.context = &omap5430es1_rm_abe_aess_context;
	} else {
		mod.clkctrl = &omap5430_cm_abe_aess_clkctrl;
		mod.context = &omap5430_rm_abe_aess_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 196608;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_DMIC;
	mod.id = (int) OMAP5_DMIC;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_DMIC_GFCLK;
	mod.sysconfig = &omap5430_dmic_cortex_a15_dmic_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_abe_dmic_clkctrl;
		mod.context = &omap5430es1_rm_abe_dmic_context;
	} else {
		mod.clkctrl = &omap5430_cm_abe_dmic_clkctrl;
		mod.context = &omap5430_rm_abe_dmic_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_L4_ABE_INTERCONNECT;
	mod.id = (int) OMAP5_L4_ABE_INTERCONNECT;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_ABE_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0)
		mod.clkctrl = &omap5430es1_cm_abe_l4_abe_clkctrl;
	else
		mod.clkctrl = &omap5430_cm_abe_l4_abe_clkctrl;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 49152;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 98304;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MCASP;
	mod.id = (int) OMAP5_MCASP;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_MCASP1_GFCLK;
	mod.sysconfig = &omap5430_mcasp_mpu_mcasp_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_abe_mcasp_clkctrl;
		mod.context = &omap5430es1_rm_abe_mcasp_context;
	} else {
		mod.clkctrl = &omap5430_cm_abe_mcasp_clkctrl;
		mod.context = &omap5430_rm_abe_mcasp_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 98000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 98000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE1;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MCBSP1;
	mod.id = (int) OMAP5_MCBSP1;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_MCBSP1_GFCLK;
	mod.sysconfig = &omap5430_mcbsp1_cortex_a15_mcbsplp_sysconfig_reg;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_abe_mcbsp1_clkctrl;
		mod.context = &omap5430es1_rm_abe_mcbsp1_context;
	} else {
		mod.clkctrl = &omap5430_cm_abe_mcbsp1_clkctrl;
		mod.context = &omap5430_rm_abe_mcbsp1_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MCBSP2;
	mod.id = (int) OMAP5_MCBSP2;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_MCBSP2_GFCLK;
	mod.sysconfig = &omap5430_mcbsp2_cortex_a15_mcbsplp_sysconfig_reg;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_abe_mcbsp2_clkctrl;
		mod.context = &omap5430es1_rm_abe_mcbsp2_context;
	} else {
		mod.clkctrl = &omap5430_cm_abe_mcbsp2_clkctrl;
		mod.context = &omap5430_rm_abe_mcbsp2_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MCBSP3;
	mod.id = (int) OMAP5_MCBSP3;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_MCBSP3_GFCLK;
	mod.sysconfig = &omap5430_mcbsp3_cortex_a15_mcbsplp_sysconfig_reg;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_abe_mcbsp3_clkctrl;
		mod.context = &omap5430es1_rm_abe_mcbsp3_context;
	} else {
		mod.clkctrl = &omap5430_cm_abe_mcbsp3_clkctrl;
		mod.context = &omap5430_rm_abe_mcbsp3_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MCPDM;
	mod.id = (int) OMAP5_MCPDM;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PAD_GCLKS;
	mod.sysconfig = &omap5430_mcpdm_cortex_a15_mcpdm_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_abe_mcpdm_clkctrl;
		mod.context = &omap5430es1_rm_abe_mcpdm_context;
	} else {
		mod.clkctrl = &omap5430_cm_abe_mcpdm_clkctrl;
		mod.context = &omap5430_rm_abe_mcpdm_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_SLIMBUS1;
	mod.id = (int) OMAP5_SLIMBUS1;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_SLIMBUS_UCLKS;
	mod.sysconfig = &omap5430_slimbus1_mpu_slimbus_cmp_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_abe_slimbus1_clkctrl;
		mod.context = &omap5430es1_rm_abe_slimbus1_context;
	} else {
		mod.clkctrl = &omap5430_cm_abe_slimbus1_clkctrl;
		mod.context = &omap5430_rm_abe_slimbus1_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT8 | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_TIMER5;
	mod.id = (int) OMAP5_TIMER5;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_TIMER5_GFCLK;
	mod.sysconfig = &omap5430_timer5_mpu_tiocp_cfg;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_abe_timer5_clkctrl;
		mod.context = &omap5430es1_rm_abe_timer5_context;
	} else {
		mod.clkctrl = &omap5430_cm_abe_timer5_clkctrl;
		mod.context = &omap5430_rm_abe_timer5_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_TIMER6;
	mod.id = (int) OMAP5_TIMER6;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_TIMER6_GFCLK;
	mod.sysconfig = &omap5430_timer6_mpu_tiocp_cfg;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_abe_timer6_clkctrl;
		mod.context = &omap5430es1_rm_abe_timer6_context;
	} else {
		mod.clkctrl = &omap5430_cm_abe_timer6_clkctrl;
		mod.context = &omap5430_rm_abe_timer6_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_TIMER7;
	mod.id = (int) OMAP5_TIMER7;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_TIMER7_GFCLK;
	mod.sysconfig = &omap5430_timer7_mpu_tiocp_cfg;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_abe_timer7_clkctrl;
		mod.context = &omap5430es1_rm_abe_timer7_context;
	} else {
		mod.clkctrl = &omap5430_cm_abe_timer7_clkctrl;
		mod.context = &omap5430_rm_abe_timer7_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_TIMER8;
	mod.id = (int) OMAP5_TIMER8;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_TIMER8_GFCLK;
	mod.sysconfig = &omap5430_timer8_mpu_tiocp_cfg;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_abe_timer8_clkctrl;
		mod.context = &omap5430es1_rm_abe_timer8_context;
	} else {
		mod.clkctrl = &omap5430_cm_abe_timer8_clkctrl;
		mod.context = &omap5430_rm_abe_timer8_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_WD_TIMER3;
	mod.id = (int) OMAP5_WD_TIMER3;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_ABE_32K_CLK;
	mod.sysconfig = &omap5430_wd_timer3_l3interconnect_wdsc;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_abe_wd_timer3_clkctrl;
		mod.context = &omap5430es1_rm_abe_wd_timer3_context;
	} else {
		mod.clkctrl = &omap5430_cm_abe_wd_timer3_clkctrl;
		mod.context = &omap5430_rm_abe_wd_timer3_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: MM, Power dom.: DSP, Clock domain = DSP */
	mod.name = MOD_DSP;
	mod.id = (int) OMAP5_DSP;
	mod.clkdm = CLKDM_DSP;
	mod.pwrdm = PWRDM_DSP;
	mod.voltdm = VDD_MM;
	mod.clk = (int) CLK54XX_DSP_GCLK;
	mod.sysconfig = &omap5430_dsp_sysc_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_dsp_dsp_clkctrl;
		mod.context = &omap5430es1_rm_dsp_dsp_context;
	} else {
		mod.clkctrl = &omap5430_cm_dsp_dsp_clkctrl;
		mod.context = &omap5430_rm_dsp_dsp_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 232960;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 465919;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = 531199;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: MM, Power dom.: GPU, Clock domain = GPU */
	mod.name = MOD_GPU;
	mod.id = (int) OMAP5_GPU;
	mod.clkdm = CLKDM_GPU;
	mod.pwrdm = PWRDM_GPU;
	mod.voltdm = VDD_MM;
	mod.clk = (int) CLK54XX_GPU_CORE_GCLK;
	mod.sysconfig = &omap5430_gpu_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_gpu_gpu_clkctrl;
		mod.context = &omap5430es1_rm_gpu_gpu_context;
	} else {
		mod.clkctrl = &omap5430_cm_gpu_gpu_clkctrl;
		mod.context = &omap5430_rm_gpu_gpu_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 177333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp,
			sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 354666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp,
			sizeof(mod_opp));
		opp.name = OPP_HIGH;
		opp.rate = 532000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp,
			sizeof(mod_opp));
		opp.name = OPP_SB;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp,
			sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 212735;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp,
			sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 425471;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp,
			sizeof(mod_opp));
		opp.name = OPP_HIGH;
		opp.rate = 531839;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp,
			sizeof(mod_opp));
		opp.name = OPP_SB;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp,
			sizeof(mod_opp));
	}
	mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_STANDBY_MODE5;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: MM, Power dom.: IVA, Clock domain = IVA */
	mod.name = MOD_IVA;
	mod.id = (int) OMAP5_IVA;
	mod.clkdm = CLKDM_IVA;
	mod.pwrdm = PWRDM_IVA;
	mod.voltdm = VDD_MM;
	mod.clk = (int) CLK54XX_IVA_GCLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_iva_iva_clkctrl;
		mod.context = &omap5430es1_rm_iva_iva_context;
	} else {
		mod.clkctrl = &omap5430_cm_iva_iva_clkctrl;
		mod.context = &omap5430_rm_iva_iva_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 194133;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 388266;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = 531199;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_SL2;
	mod.id = (int) OMAP5_SL2;
	mod.clkdm = CLKDM_IVA;
	mod.pwrdm = PWRDM_IVA;
	mod.voltdm = VDD_MM;
	mod.clk = (int) CLK54XX_IVA_GCLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_iva_sl2_clkctrl;
		mod.context = &omap5430es1_rm_iva_sl2_context;
	} else {
		mod.clkctrl = &omap5430_cm_iva_sl2_clkctrl;
		mod.context = &omap5430_rm_iva_sl2_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 194133;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 388266;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = 531199;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: MPU, Power dom.: MPUAON Clock domain = MPU */
	mod.name = MOD_MPU;
	mod.id = (int) OMAP5_MPU;
	mod.clkdm = CLKDM_MPU;
	mod.pwrdm = PWRDM_MPU;
	mod.voltdm = VDD_MPU;
	mod.clk = (int) CLK54XX_MPU_GCLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_mpu_mpu_clkctrl;
		mod.context = &omap5430es1_rm_mpu_mpu_context;
	} else {
		mod.clkctrl = &omap5430_cm_mpu_mpu_clkctrl;
		mod.context = &omap5430_rm_mpu_mpu_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 800000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_HIGH;
		opp.rate = 1100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_SB;
		opp.rate = 1200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 499200;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 1099885;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_HIGH;
		opp.rate = 1500000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_SB;
		opp.rate = 1699200;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_HAS_STANDBY_STATUS;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	mod54xx_init_done = 1;

	dprintf("%s(): init done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod5432_init
 * @BRIEF		initialize internal data for OMAP5432
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void mod5432_init(void)
{
	mod_info mod;
	mod_opp opp;

	if (mod54xx_init_done)
		return;

	genlist_init(&mod54xx_list);

	/* Voltage dom.: WKUP, Power dom.: EMU, Clock dom. = EMU */
	mod.name = MOD_DEBUGSS;
	mod.id = (int) OMAP5_DEBUGSS;
	mod.clkdm = CLKDM_EMU;
	mod.pwrdm = PWRDM_EMU;
	mod.voltdm = VDD_WKUP;
	mod.clk = (int) CLK54XX_EMU_SYS_CLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_emu_debugss_clkctrl;
		mod.context = &omap5430es1_rm_emu_debugss_context;
	} else {
		mod.clkctrl = &omap5430_cm_emu_debugss_clkctrl;
		mod.context = &omap5430_rm_emu_debugss_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: WKUP, Power dom.: WKUPAON, Clock domain = WKUPAON */
	mod.name = MOD_CTRL_MODULE_WKUP;
	mod.id = (int) OMAP5_CTRL_MODULE_WKUP;
	mod.clkdm = CLKDM_WKUPAON;
	mod.pwrdm = PWRDM_WKUPAON;
	mod.voltdm = VDD_WKUP;
	mod.clk = (int) CLK54XX_WKUPAON_GICLK;
	mod.sysconfig = NULL;
	mod.clkctrl = NULL;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_L4_WKUP_INTERCONNECT;
	mod.id = (int) OMAP5_L4WKUP_INTERCONNECT;
	mod.clkdm = CLKDM_WKUPAON;
	mod.pwrdm = PWRDM_WKUPAON;
	mod.voltdm = VDD_WKUP;
	mod.clk = (int) CLK54XX_WKUPAON_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_wkupaon_l4_wkup_clkctrl;
		mod.context = &omap5430es1_rm_wkupaon_l4_wkup_context;
	} else {
		mod.clkctrl = &omap5430_cm_wkupaon_l4_wkup_clkctrl;
		mod.context = &omap5430_rm_wkupaon_l4_wkup_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_GPIO1;
	mod.id = (int) OMAP5_GPIO1;
	mod.clkdm = CLKDM_WKUPAON;
	mod.pwrdm = PWRDM_WKUPAON;
	mod.voltdm = VDD_WKUP;
	mod.clk = (int) CLK54XX_WKUPAON_32K_GFCLK;
	mod.sysconfig = &omap5430_gpio1_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_wkupaon_gpio1_clkctrl;
		mod.context = &omap5430es1_rm_wkupaon_gpio1_context;
	} else {
		mod.clkctrl = &omap5430_cm_wkupaon_gpio1_clkctrl;
		mod.context = &omap5430_rm_wkupaon_gpio1_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_ENAWAKEUP_BIT;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_TIMER1;
	mod.id = (int) OMAP5_TIMER1;
	mod.clkdm = CLKDM_WKUPAON;
	mod.pwrdm = PWRDM_WKUPAON;
	mod.voltdm = VDD_WKUP;
	mod.clk = (int) CLK54XX_TIMER1_GFCLK;
	mod.sysconfig = &omap5430_timer1_tiocp_cfg;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_wkupaon_timer1_clkctrl;
		mod.context = &omap5430es1_rm_wkupaon_timer1_context;
	} else {
		mod.clkctrl = &omap5430_cm_wkupaon_timer1_clkctrl;
		mod.context = &omap5430_rm_wkupaon_timer1_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_WD_TIMER2;
	mod.id = (int) OMAP5_WD_TIMER2;
	mod.clkdm = CLKDM_WKUPAON;
	mod.pwrdm = PWRDM_WKUPAON;
	mod.voltdm = VDD_WKUP;
	mod.clk = (int) CLK54XX_WKUPAON_32K_GFCLK;
	mod.sysconfig = &omap5430_wd_timer2_l4interconnect_wdsc;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_wkupaon_wd_timer2_clkctrl;
		mod.context = &omap5430es1_rm_wkupaon_wd_timer2_context;
	} else {
		mod.clkctrl = &omap5430_cm_wkupaon_wd_timer2_clkctrl;
		mod.context = &omap5430_rm_wkupaon_wd_timer2_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_SARRAM;
	mod.id = (int) OMAP5_SARRAM;
	mod.clkdm = CLKDM_WKUPAON;
	mod.pwrdm = PWRDM_WKUPAON;
	mod.voltdm = VDD_WKUP;
	mod.clk = (int) CLK54XX_WKUPAON_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_wkupaon_sar_ram_clkctrl;
		mod.context = &omap5430es1_rm_wkupaon_sar_ram_context;
	} else {
		mod.clkctrl = &omap5430_cm_wkupaon_sar_ram_clkctrl;
		mod.context = &omap5430_rm_wkupaon_sar_ram_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_COUNTER_32K;
	mod.id = (int) OMAP5_COUNTER_32K;
	mod.clkdm = CLKDM_WKUPAON;
	mod.pwrdm = PWRDM_WKUPAON;
	mod.voltdm = VDD_WKUP;
	mod.clk = (int) CLK54XX_FUNC_32K_CLK;
	mod.sysconfig = &omap5430_counter_32k_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_wkupaon_counter_32k_clkctrl;
		mod.context = &omap5430es1_rm_wkupaon_counter_32k_context;
	} else {
		mod.clkctrl = &omap5430_cm_wkupaon_counter_32k_clkctrl;
		mod.context = &omap5430_rm_wkupaon_counter_32k_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE4;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_KEYBOARD;
	mod.id = (int) OMAP5_KBD;
	mod.clkdm = CLKDM_WKUPAON;
	mod.pwrdm = PWRDM_WKUPAON;
	mod.voltdm = VDD_WKUP;
	mod.clk = (int) CLK54XX_WKUPAON_32K_GFCLK;
	mod.sysconfig = &omap5430_kbd_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_wkupaon_kbd_clkctrl;
		mod.context = &omap5430es1_rm_wkupaon_kbd_context;
	} else {
		mod.clkctrl = &omap5430_cm_wkupaon_kbd_clkctrl;
		mod.context = &omap5430_rm_wkupaon_kbd_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE4;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	if (cpu_revision_get() != REV_ES1_0) {
		mod.name = MOD_IO_SRCOMP_WKUP;
		mod.id = (int) OMAP5_IO_SRCOMP_WKUP;
		mod.clkdm = CLKDM_WKUPAON;
		mod.pwrdm = PWRDM_WKUPAON;
		mod.voltdm = VDD_WKUP;
		mod.clk = (int) CLK54XX_WKUPAON_IO_SRCOMP_GFCLK;
		mod.sysconfig = NULL;
		mod.clkctrl = &omap5430es1_cm_wkupaon_io_srcomp_clkctrl;
		mod.context = NULL;
		genlist_init(&(mod.mod_opp_list));
		opp.name = OPP_LOW;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 19200;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_HIGH;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_SB;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		mod.properties = MOD_HAS_NO_IDLE_STATUS;
		genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));
	}


	/* HS/EMU ONLY */
	mod.name = MOD_TIMER12;
	mod.id = (int) OMAP5_TIMER12;
	mod.clkdm = CLKDM_WKUPAON;
	mod.pwrdm = PWRDM_WKUPAON;
	mod.voltdm = VDD_WKUP;
	mod.clk = (int) CLK54XX_SECURE_32K_CLK;
	mod.sysconfig = NULL;
	mod.clkctrl = NULL;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_WD_TIMER1;
	mod.id = (int) OMAP5_WDT1;
	mod.clkdm = CLKDM_WKUPAON;
	mod.pwrdm = PWRDM_WKUPAON;
	mod.voltdm = VDD_WKUP;
	mod.clk = (int) CLK54XX_SECURE_32K_CLK;
	mod.sysconfig = NULL;
	mod.clkctrl = NULL;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: COREAON, Clock domain = COREAON */
	mod.name = MOD_SMARTREFLEX_CORE;
	mod.id = (int) OMAP5_SMARTREFLEX_CORE;
	mod.clkdm = CLKDM_COREAON;
	mod.pwrdm = PWRDM_COREAON;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_SR_CORE_SYS_GFCLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_coreaon_smartreflex_core_clkctrl;
		mod.context = &omap5430es1_rm_coreaon_smartreflex_core_context;
	} else {
		mod.clkctrl = &omap5430_cm_coreaon_smartreflex_core_clkctrl;
		mod.context = &omap5430_rm_coreaon_smartreflex_core_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_SMARTREFLEX_MM;
	mod.id = (int) OMAP5_SMARTREFLEX_MM;
	mod.clkdm = CLKDM_COREAON;
	mod.pwrdm = PWRDM_COREAON;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_SR_MM_SYS_GFCLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_coreaon_smartreflex_mm_clkctrl;
		mod.context = &omap5430es1_rm_coreaon_smartreflex_mm_context;
	} else {
		mod.clkctrl = &omap5430_cm_coreaon_smartreflex_mm_clkctrl;
		mod.context = &omap5430_rm_coreaon_smartreflex_mm_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_SMARTREFLEX_MPU;
	mod.id = (int) OMAP5_SMARTREFLEX_MPU;
	mod.clkdm = CLKDM_COREAON;
	mod.pwrdm = PWRDM_COREAON;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_SR_MPU_SYS_GFCLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_coreaon_smartreflex_mpu_clkctrl;
		mod.context = &omap5430es1_rm_coreaon_smartreflex_mpu_context;
	} else {
		mod.clkctrl = &omap5430_cm_coreaon_smartreflex_mpu_clkctrl;
		mod.context = &omap5430_rm_coreaon_smartreflex_mpu_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	if (cpu_revision_get() == REV_ES1_0) {
		mod.name = MOD_BANDGAPTS;
		mod.id = (int) OMAP5_BANDGAPTS;
		mod.clkdm = CLKDM_COREAON;
		mod.pwrdm = PWRDM_COREAON;
		mod.voltdm = VDD_CORE;
		mod.clk = (int) CLK54XX_COREAON_TS_GFCLK;
		mod.sysconfig = NULL;
		mod.clkctrl = &omap5430es1_cm_coreaon_bandgap_clkctrl;
		mod.context = NULL;
		genlist_init(&(mod.mod_opp_list));
		opp.name = OPP_LOW;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 1200;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_HIGH;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_SB;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		mod.properties = MOD_HAS_NO_IDLE_STATUS;
		genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));
	}


	if (cpu_revision_get() != REV_ES1_0) {
		mod.name = MOD_IO_SRCOMP_CORE;
		mod.id = (int) OMAP5_IO_SRCOMP_CORE;
		mod.clkdm = CLKDM_COREAON;
		mod.pwrdm = PWRDM_COREAON;
		mod.voltdm = VDD_CORE;
		mod.clk = (int) CLK54XX_COREAON_IO_SRCOMP_GFCLK;
		mod.sysconfig = NULL;
		mod.clkctrl = &omap5430_cm_coreaon_io_srcomp_clkctrl;
		mod.context = NULL;
		genlist_init(&(mod.mod_opp_list));
		opp.name = OPP_LOW;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 19200;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_HIGH;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_SB;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		mod.properties = MOD_HAS_NO_IDLE_STATUS;
		genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));
	}

	if (cpu_revision_get() == REV_ES1_0) {
		mod.name = MOD_USB_PHY_CORE;
		mod.id = (int) OMAP5_USB_PHY_CORE;
		mod.clkctrl = &omap5430es1_cm_coreaon_usb_phy_core_clkctrl;
	} else {
		mod.name = MOD_USB2PHY;
		mod.id = (int) OMAP5_USB2PHY;
		mod.clkctrl = &omap5430_cm_coreaon_usb_phy_core_clkctrl;
	}
	mod.clkdm = CLKDM_COREAON;
	mod.pwrdm = PWRDM_COREAON;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_COREAON_32K_GFCLK;
	mod.sysconfig = NULL;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_NO_IDLE_STATUS;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: CAM, Clock domain = CAM */
	mod.name = MOD_FDIF;
	mod.id = (int) OMAP5_FDIF;
	mod.clkdm = CLKDM_CAM;
	mod.pwrdm = PWRDM_CAM;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_FDIF_GFCLK;
	mod.sysconfig = &omap5430_fdif_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_cam_fdif_clkctrl;
		mod.context = &omap5430es1_rm_cam_fdif_context;
	} else {
		mod.clkctrl = &omap5430_cm_cam_fdif_clkctrl;
		mod.context = &omap5430_rm_cam_fdif_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 128000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 128000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_STANDBY_MODE5;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_ISS;
	mod.id = (int) OMAP5_ISS;
	mod.clkdm = CLKDM_CAM;
	mod.pwrdm = PWRDM_CAM;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_CORE_ISS_MAIN_CLK;
	mod.sysconfig = &omap5430_iss_hl_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_cam_iss_clkctrl;
		mod.context = &omap5430es1_rm_cam_iss_context;
	} else {
		mod.clkctrl = &omap5430_cm_cam_iss_clkctrl;
		mod.context = &omap5430_rm_cam_iss_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 152000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 304000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_CAL;
	mod.id = (int) OMAP5_CAL;
	mod.clkdm = CLKDM_CAM;
	mod.pwrdm = PWRDM_CAM;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_CAM_L3_GICLK;
	mod.sysconfig = &omap5430_cal_hl_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_cam_cal_clkctrl;
		mod.context = &omap5430es1_rm_cam_cal_context;
	} else {
		mod.clkctrl = &omap5430_cm_cam_cal_clkctrl;
		mod.context = &omap5430_rm_cam_cal_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 266000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L4CFG */
	mod.name = MOD_CTRL_MODULE_CORE;
	mod.id = (int) OMAP5_CTRL_MODULE_CORE;
	mod.clkdm = CLKDM_L4_CFG;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4CFG_L4_GICLK;
	mod.sysconfig = NULL;
	mod.clkctrl = NULL;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 66500;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_SPINLOCK;
	mod.id = (int) OMAP5_SPINLOCK;
	mod.clkdm = CLKDM_L4_CFG;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4CFG_L4_GICLK;
	mod.sysconfig = &omap5430_spinlock_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4cfg_spinlock_clkctrl;
		mod.context = &omap5430es1_rm_l4cfg_spinlock_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4cfg_spinlock_clkctrl;
		mod.context = &omap5430_rm_l4cfg_spinlock_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 66500;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_IDLE_MODE4 | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_L4_CFG_INTERCONNECT;
	mod.id = (int) OMAP5_L4_CFG_INTERCONNECT;
	mod.clkdm = CLKDM_L4_CFG;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4CFG_L4_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4cfg_l4_cfg_clkctrl;
		mod.context = &omap5430es1_rm_l4cfg_l4_cfg_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4cfg_l4_cfg_clkctrl;
		mod.context = &omap5430_rm_l4cfg_l4_cfg_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 66500;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MAILBOX;
	mod.id = (int) OMAP5_MAILBOX;
	mod.clkdm = CLKDM_L4_CFG;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4CFG_L4_GICLK;
	mod.sysconfig = &omap5430_mailbox_l4_cfginterconnect_mailbox_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4cfg_mailbox_clkctrl;
		mod.context = &omap5430es1_rm_l4cfg_mailbox_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4cfg_mailbox_clkctrl;
		mod.context = &omap5430_rm_l4cfg_mailbox_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 66500;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_SARROM;
	mod.id = (int) OMAP5_SARROM;
	mod.clkdm = CLKDM_L4_CFG;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4CFG_L4_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4cfg_sar_rom_clkctrl;
		mod.context = &omap5430es1_rm_l4cfg_sar_rom_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4cfg_sar_rom_clkctrl;
		mod.context = &omap5430_rm_l4cfg_sar_rom_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 66500;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_OCP2SCP2;
	mod.id = (int) OMAP5_OCP2SCP2;
	mod.clkdm = CLKDM_L4_CFG;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4CFG_L4_GICLK;
	mod.sysconfig = &omap5430_ocp2scp2_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4cfg_ocp2scp2_clkctrl;
		mod.context = &omap5430es1_rm_l4cfg_ocp2scp2_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4cfg_ocp2scp2_clkctrl;
		mod.context = &omap5430_rm_l4cfg_ocp2scp2_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 66500;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = EMIF */
	mod.name = MOD_PHY_EMIF;
	mod.id = (int) OMAP5_PHY_EMIF;
	mod.clkdm = CLKDM_EMIF;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_EMIF_PHY_GCLK;
	mod.sysconfig = NULL;
	mod.clkctrl = NULL;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 266000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 532000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_DLL_EMIF;
	mod.id = (int) OMAP5_DLL_EMIF;
	mod.clkdm = CLKDM_EMIF;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_CORE_DLL_GCLK;
	mod.sysconfig = NULL;
	mod.clkctrl = NULL;
	if (cpu_revision_get() == REV_ES1_0)
		mod.context = &omap5430es1_rm_emif_emif_dll_context;
	else
		mod.context = &omap5430_rm_emif_emif_dll_context;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 266000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 266000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_DMM;
	mod.id = (int) OMAP5_DMM;
	mod.clkdm = CLKDM_EMIF;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_EMIF_L3_GICLK;
	mod.sysconfig = &omap5430_dmm_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_emif_dmm_clkctrl;
		mod.context = &omap5430es1_rm_emif_dmm_context;
	} else {
		mod.clkctrl = &omap5430_cm_emif_dmm_clkctrl;
		mod.context = &omap5430_rm_emif_dmm_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 266000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_EMIF1;
	mod.id = (int) OMAP5_EMIF1;
	mod.clkdm = CLKDM_EMIF;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_EMIF_L3_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_emif_emif1_clkctrl;
		mod.context = &omap5430es1_rm_emif_emif1_context;
	} else {
		mod.clkctrl = &omap5430_cm_emif_emif1_clkctrl;
		mod.context = &omap5430_rm_emif_emif1_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 266000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_EMIF2;
	mod.id = (int) OMAP5_EMIF2;
	mod.clkdm = CLKDM_EMIF;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_EMIF_L3_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_emif_emif2_clkctrl;
		mod.context = &omap5430es1_rm_emif_emif2_context;
	} else {
		mod.clkctrl = &omap5430_cm_emif_emif2_clkctrl;
		mod.context = &omap5430_rm_emif_emif2_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 266000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_EMIF_OCP_FW;
	mod.id = (int) OMAP5_EMIF_OCP_FW;
	mod.clkdm = CLKDM_EMIF;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_EMIF_L3_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_emif_emif_ocp_fw_clkctrl;
		mod.context = &omap5430es1_rm_emif_emif_fw_context;
	} else {
		mod.clkctrl = &omap5430_cm_emif_emif_ocp_fw_clkctrl;
		mod.context = &omap5430_rm_emif_emif_fw_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 266000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = IPU */
	mod.name = MOD_IPU;
	mod.id = (int) OMAP5_IPU;
	mod.clkdm = CLKDM_IPU;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_CORE_IPU_ISS_BOOST_CLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_ipu_ipu_clkctrl;
		mod.context = &omap5430es1_rm_ipu_ipu_context;
	} else {
		mod.clkctrl = &omap5430_cm_ipu_ipu_clkctrl;
		mod.context = &omap5430_rm_ipu_ipu_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 212800;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 425600;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN2 */
	mod.name = MOD_GPMC;
	mod.id = (int) OMAP5_GPMC;
	mod.clkdm = CLKDM_L3_MAIN2;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L3MAIN2_L3_GICLK;
	mod.sysconfig = &omap5430_gpmc_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3main2_gpmc_clkctrl;
		mod.context = &omap5430es1_rm_l3main2_gpmc_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3main2_gpmc_clkctrl;
		mod.context = &omap5430_rm_l3main2_gpmc_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 266000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_L3_MAIN2_INTERCONNECT;
	mod.id = (int) OMAP5_L3_MAIN2_INTERCONNECT;
	mod.clkdm = CLKDM_L3_MAIN2;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L3MAIN2_L3_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3main2_l3_main_2_clkctrl;
		mod.context = &omap5430es1_rm_l3main2_l3_main_2_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3main2_l3_main_2_clkctrl;
		mod.context = &omap5430_rm_l3main2_l3_main_2_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 266000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_OCMC_RAM;
	mod.id = (int) OMAP5_OCMC_RAM;
	mod.clkdm = CLKDM_L3_MAIN2;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L3MAIN2_L3_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3main2_ocmc_ram_clkctrl;
		mod.context = &omap5430es1_rm_l3main2_ocmc_ram_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3main2_ocmc_ram_clkctrl;
		mod.context = &omap5430_rm_l3main2_ocmc_ram_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 266000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_INSTR */
	mod.name = MOD_L3_MAIN3_INTERCONNECT;
	mod.id = (int) OMAP5_L3_MAIN3_INTERCONNECT;
	mod.clkdm = CLKDM_L3_INSTR;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L3INSTR_L3_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3instr_l3_main_3_clkctrl;
		mod.context = &omap5430es1_rm_l3instr_l3_main_3_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3instr_l3_main_3_clkctrl;
		mod.context = &omap5430_rm_l3instr_l3_main_3_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 266000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_L3_INSTR_INTERCONNECT;
	mod.id = (int) OMAP5_L3_INSTR_INTERCONNECT;
	mod.clkdm = CLKDM_L3_INSTR;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L3INSTR_L3_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3instr_l3_instr_clkctrl;
		mod.context = &omap5430es1_rm_l3instr_l3_instr_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3instr_l3_instr_clkctrl;
		mod.context = &omap5430_rm_l3instr_l3_instr_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 266000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_OCP_WP_NOC;
	mod.id = (int) OMAP5_OCP_WP_NOC;
	mod.clkdm = CLKDM_L3_INSTR;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L3INSTR_L3_GICLK;
	mod.sysconfig = &omap5430_ocp_wp_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3instr_ocp_wp_noc_clkctrl;
		mod.context = &omap5430es1_rm_l3instr_ocp_wp_noc_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3instr_ocp_wp_noc_clkctrl;
		mod.context = &omap5430_rm_l3instr_ocp_wp_noc_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 266000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	if (cpu_revision_get() != REV_ES1_0) {
		mod.name = MOD_CTRL_MODULE_BANDGAP;
		mod.id = (int) OMAP5_CTRL_MODULE_BANDGAP;
		mod.clkdm = CLKDM_L3_INSTR;
		mod.pwrdm = PWRDM_CORE;
		mod.voltdm = VDD_CORE;
		mod.clk = (int) CLK54XX_L3INSTR_TS_GFCLK;
		mod.sysconfig = NULL;
		mod.clkctrl = NULL;
		mod.context = NULL;
		genlist_init(&(mod.mod_opp_list));
		opp.name = OPP_LOW;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 1200;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_HIGH;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_SB;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		mod.properties = 0;
		genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));
	}

	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = L3_MAIN1 */
	mod.name = MOD_L3_MAIN1_INTERCONNECT;
	mod.id = (int) OMAP5_L3_MAIN1_INTERCONNECT;
	mod.clkdm = CLKDM_L3_MAIN1;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L3MAIN1_L3_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3main1_l3_main_1_clkctrl;
		mod.context = &omap5430es1_rm_l3main1_l3_main_1_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3main1_l3_main_1_clkctrl;
		mod.context = &omap5430_rm_l3main1_l3_main_1_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 266000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = C2C */
	mod.name = MOD_C2C;
	mod.id = (int) OMAP5_C2C;
	mod.clkdm = CLKDM_C2C;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clk = (int) CLK54XX_C2C_L3_GICLK;
		mod.sysconfig = &omap5430_c2c_sysconfig;
		mod.clkctrl = &omap5430es1_cm_c2c_c2c_clkctrl;
		mod.context = &omap5430es1_rm_c2c_c2c_context;
	} else {
		mod.clk = (int) CLK54XX_C2C_GFCLK;
		mod.sysconfig = &omap5430_c2c_sysconfig;
		mod.clkctrl = &omap5430_cm_c2c_c2c_clkctrl;
		mod.context = &omap5430_rm_c2c_c2c_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 266000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 177333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 354666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_C2C_OCP_FW;
	mod.id = (int) OMAP5_C2C_OCP_FW;
	mod.clkdm = CLKDM_C2C;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clk = (int) CLK54XX_C2C_L3_GICLK;
		mod.clkctrl = &omap5430es1_cm_c2c_c2c_ocp_fw_clkctrl;
		mod.context = &omap5430es1_rm_c2c_c2c_ocp_fw_context;
	} else {
		mod.clk = (int) CLK54XX_C2C_GICLK;
		mod.clkctrl = &omap5430_cm_c2c_c2c_ocp_fw_clkctrl;
		mod.context = &omap5430_rm_c2c_c2c_ocp_fw_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 133000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 266000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 88666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 177333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MODEM_ICR;
	mod.id = (int) OMAP5_MODEM_ICR;
	mod.clkdm = CLKDM_C2C;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_C2C_L4_GICLK;
	mod.sysconfig = &omap5430_modem_icr_mpu_pa_sys_config;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_c2c_modem_icr_clkctrl;
		mod.context = &omap5430es1_rm_c2c_modem_icr_context;
	} else {
		mod.clkctrl = &omap5430_cm_c2c_modem_icr_clkctrl;
		mod.context = &omap5430_rm_c2c_modem_icr_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 66500;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = DMA */
	mod.name = MOD_DMA_SYSTEM;
	mod.id = (int) OMAP5_DMA_SYSTEM;
	mod.clkdm = CLKDM_DMA;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_DMA_L3_GICLK;
	mod.sysconfig = &omap5430_dma4_ocp_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_dma_dma_system_clkctrl;
		mod.context = &omap5430es1_rm_dma_dma_system_context;
	} else {
		mod.clkctrl = &omap5430_cm_dma_dma_system_clkctrl;
		mod.context = &omap5430_rm_dma_dma_system_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 266000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_STANDBY_MODE13 | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: CORE, Clock domain = MIPIEXT */
	mod.name = MOD_LLI;
	mod.id = (int) OMAP5_LLI;
	mod.clkdm = CLKDM_MIPIEXT;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_UNIPRO1_PHY_GFCLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_mipiext_lli_clkctrl;
		mod.context = &omap5430es1_rm_mipiext_lli_context;
	} else {
		mod.clkctrl = &omap5430_cm_mipiext_lli_clkctrl;
		mod.context = &omap5430_rm_mipiext_lli_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 1457600;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 1457600;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_LLI_OCP_FW;
	mod.id = (int) OMAP5_LLI_OCP_FW;
	mod.clkdm = CLKDM_MIPIEXT;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_MIPIEXT_L3_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_mipiext_lli_ocp_fw_clkctrl;
		mod.context = &omap5430es1_rm_mipiext_lli_ocp_fw_context;
	} else {
		mod.clkctrl = &omap5430_cm_mipiext_lli_ocp_fw_clkctrl;
		mod.context = &omap5430_rm_mipiext_lli_ocp_fw_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 266000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MPHY;
	mod.id = (int) OMAP5_MPHY;
	mod.clkdm = CLKDM_MIPIEXT;
	mod.pwrdm = PWRDM_CORE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_MIPIEXT_L4_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_mipiext_mphy_clkctrl;
		mod.context = &omap5430es1_rm_mipiext_mphy_context;
	} else {
		mod.clkctrl = &omap5430_cm_mipiext_mphy_clkctrl;
		mod.context = &omap5430_rm_mipiext_mphy_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 66500;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	if (cpu_revision_get() == REV_ES1_0) {
		mod.name = MOD_UNIPRO1;
		mod.id = (int) OMAP5_UNIPRO1;
		mod.clkdm = CLKDM_MIPIEXT;
		mod.pwrdm = PWRDM_CORE;
		mod.voltdm = VDD_CORE;
		mod.clk = (int) CLK54XX_UNIPRO1_PHY_GFCLK;
		mod.sysconfig = &omap5430_unipro1_sysconfig;
		mod.clkctrl = &omap5430es1_cm_mipiext_unipro1_clkctrl;
		mod.context = &omap5430es1_rm_mipiext_unipro1_context;
		genlist_init(&(mod.mod_opp_list));
		opp.name = OPP_LOW;
		opp.rate = 1457600;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 1457600;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_HIGH;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_SB;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE;
		genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));
	}

	/* Voltage dom.: CORE, Power dom.: DSS, Clock domain = DSS */
	mod.name = MOD_DSS;
	mod.id = (int) OMAP5_DSS;
	mod.clkdm = CLKDM_DSS;
	mod.pwrdm = PWRDM_DSS;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_DSS_GFCLK;
	mod.sysconfig = &omap5430_dispc_l3_main_dispc_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_dss_dss_clkctrl;
		mod.context = &omap5430es1_rm_dss_dss_context;
	} else {
		mod.clkctrl = &omap5430_cm_dss_dss_clkctrl;
		mod.context = &omap5430_rm_dss_dss_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 192000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 192000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_IDLE_MODE4 | MOD_HAS_CLOCK_ACTIVITY_MODE | MOD_HAS_STANDBY_MODE13;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	if (cpu_revision_get() != REV_ES1_0) {
		mod.name = MOD_BB2D;
		mod.id = (int) OMAP5_BB2D;
		mod.clkdm = CLKDM_DSS;
		mod.pwrdm = PWRDM_DSS;
		mod.voltdm = VDD_CORE;
		mod.clk = (int) CLK54XX_BB2D_GFCLK;
		mod.sysconfig = NULL;
		mod.clkctrl = &omap5430es1_cm_dss_bb2d_clkctrl;
		mod.context = &omap5430es1_rm_dss_bb2d_context;
		genlist_init(&(mod.mod_opp_list));
		opp.name = OPP_LOW;
		opp.rate = 177333;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 354666;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_HIGH;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_SB;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		mod.properties = MOD_HAS_STANDBY_STATUS;
		genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));
	}

	/* Voltage dom.: CORE, Power dom.: L3INIT, Clock domain = L3INIT */
	mod.name = MOD_HSI;
	mod.id = (int) OMAP5_HSI;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_HSI_GFCLK;
	mod.sysconfig = &omap5430_hsi_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3init_hsi_clkctrl;
		mod.context = &omap5430es1_rm_l3init_hsi_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3init_hsi_clkctrl;
		mod.context = &omap5430_rm_l3init_hsi_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 192000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 192000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE13 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_IEEE1500_2_OCP;
	mod.id = (int) OMAP5_IEEE1500_2_OCP;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L3INIT_L3_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3init_ieee1500_2_ocp_clkctrl;
		mod.context = &omap5430es1_rm_l3init_ieee1500_2_ocp_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3init_ieee1500_2_ocp_clkctrl;
		mod.context = &omap5430_rm_l3init_ieee1500_2_ocp_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 266000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MMC1;
	mod.id = (int) OMAP5_MMC1;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_MMC1_GFCLK;
	mod.sysconfig = &omap5430_mmchs1_hl_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3init_mmc1_clkctrl;
		mod.context = &omap5430es1_rm_l3init_mmc1_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3init_mmc1_clkctrl;
		mod.context = &omap5430_rm_l3init_mmc1_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MMC2;
	mod.id = (int) OMAP5_MMC2;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_MMC2_GFCLK;
	mod.sysconfig = &omap5430_mmchs2_hl_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3init_mmc2_clkctrl;
		mod.context = &omap5430es1_rm_l3init_mmc2_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3init_mmc2_clkctrl;
		mod.context = &omap5430_rm_l3init_mmc2_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_OCPSCP1;
	mod.id = (int) OMAP5_OCPSCP1;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L3INIT_L4_GICLK;
	mod.sysconfig = &omap5430_ocp2scp1_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3init_ocp2scp1_clkctrl;
		mod.context = &omap5430es1_rm_l3init_ocp2scp1_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3init_ocp2scp1_clkctrl;
		mod.context = &omap5430_rm_l3init_ocp2scp1_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 66500;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_USB_HOST_HS;
	mod.id = (int) OMAP5_USB_HOST_HS;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_UTMI_P1_GFCLK;
	mod.sysconfig = &omap5430_uhh_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3init_usb_host_hs_clkctrl;
		mod.context = &omap5430es1_rm_l3init_usb_host_hs_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3init_usb_host_hs_clkctrl;
		mod.context = &omap5430_rm_l3init_usb_host_hs_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 60000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 60000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_USB_OTG_SS;
	mod.id = (int) OMAP5_USB_OTG_SS;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L3INIT_960M_FCLK;
	mod.sysconfig = &omap5430_usbotgss_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3init_usb_otg_ss_clkctrl;
		mod.context = &omap5430es1_rm_l3init_usb_otg_ss_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3init_usb_otg_ss_clkctrl;
		mod.context = &omap5430_rm_l3init_usb_otg_ss_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 960000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 960000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_USB_TLL_HS;
	mod.id = (int) OMAP5_USB_TLL_HS;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_TLL_CH0_GFCLK;
	mod.sysconfig = &omap5430_usbtll_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3init_usb_tll_hs_clkctrl;
		mod.context = &omap5430es1_rm_l3init_usb_tll_hs_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3init_usb_tll_hs_clkctrl;
		mod.context = &omap5430_rm_l3init_usb_tll_hs_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 60000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 60000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_IDLE_MODE4;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_SATA;
	mod.id = (int) OMAP5_SATA;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L3INIT_L3_GICLK;
	mod.sysconfig = &omap5430_sata_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3init_sata_clkctrl;
		mod.context = &omap5430es1_rm_l3init_sata_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3init_sata_clkctrl;
		mod.context = &omap5430_rm_l3init_sata_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 266000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_UNIPRO2;
	mod.id = (int) OMAP5_UNIPRO2;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_UNIPRO2_PHY_GFCLK;
	mod.sysconfig = &omap5430_unipro2_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3init_unipro2_clkctrl;
		mod.context = &omap5430es1_rm_l3init_unipro2_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3init_unipro2_clkctrl;
		mod.context = &omap5430_rm_l3init_unipro2_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 1457600;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 1457600;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MPHY_UNIPRO2;
	mod.id = (int) OMAP5_MPHY_UNIPRO2;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L3INIT_L4_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0)
		mod.clkctrl = &omap5430es1_cm_l3init_mphy_unipro2_clkctrl;
	else
		mod.clkctrl = &omap5430_cm_l3init_mphy_unipro2_clkctrl;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 66500;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_OCPSCP3;
	mod.id = (int) OMAP5_OCPSCP3;
	mod.clkdm = CLKDM_L3_INIT;
	mod.pwrdm = PWRDM_L3_INIT;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L3INIT_L4_GICLK;
	mod.sysconfig = &omap5430_ocp2scp3_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l3init_ocp2scp3_clkctrl;
		mod.context = &omap5430es1_rm_l3init_ocp2scp3_context;
	} else {
		mod.clkctrl = &omap5430_cm_l3init_ocp2scp3_clkctrl;
		mod.context = &omap5430_rm_l3init_ocp2scp3_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 66500;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_PER */
	mod.name = MOD_TIMER10;
	mod.id = (int) OMAP5_TIMER10;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_TIMER10_GFCLK;
	mod.sysconfig = &omap5430_timer10_l4interconnect_tiocp_cfg;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_timer10_clkctrl;
		mod.context = &omap5430es1_rm_l4per_timer10_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_timer10_clkctrl;
		mod.context = &omap5430_rm_l4per_timer10_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_TIMER11;
	mod.id = (int) OMAP5_TIMER11;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_TIMER11_GFCLK;
	mod.sysconfig = &omap5430_timer11_l4interconnect_tiocp_cfg;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_timer11_clkctrl;
		mod.context = &omap5430es1_rm_l4per_timer11_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_timer11_clkctrl;
		mod.context = &omap5430_rm_l4per_timer11_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_TIMER2;
	mod.id = (int) OMAP5_TIMER2;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_TIMER2_GFCLK;
	mod.sysconfig = &omap5430_timer2_l4interconnect_tiocp_cfg;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_timer2_clkctrl;
		mod.context = &omap5430es1_rm_l4per_timer2_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_timer2_clkctrl;
		mod.context = &omap5430_rm_l4per_timer2_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_TIMER3;
	mod.id = (int) OMAP5_TIMER3;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_TIMER3_GFCLK;
	mod.sysconfig = &omap5430_timer3_l4interconnect_tiocp_cfg;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_timer3_clkctrl;
		mod.context = &omap5430es1_rm_l4per_timer3_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_timer3_clkctrl;
		mod.context = &omap5430_rm_l4per_timer3_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_TIMER4;
	mod.id = (int) OMAP5_TIMER4;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_TIMER4_GFCLK;
	mod.sysconfig = &omap5430_timer4_l4interconnect_tiocp_cfg;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_timer4_clkctrl;
		mod.context = &omap5430es1_rm_l4per_timer4_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_timer4_clkctrl;
		mod.context = &omap5430_rm_l4per_timer4_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_TIMER9;
	mod.id = (int) OMAP5_TIMER9;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_TIMER9_GFCLK;
	mod.sysconfig = &omap5430_timer9_l4interconnect_tiocp_cfg;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_timer9_clkctrl;
		mod.context = &omap5430es1_rm_l4per_timer9_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_timer9_clkctrl;
		mod.context = &omap5430_rm_l4per_timer9_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_ELM;
	mod.id = (int) OMAP5_ELM;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4PER_L4_GICLK;
	mod.sysconfig = &omap5430_elm_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_elm_clkctrl;
		mod.context = &omap5430es1_rm_l4per_elm_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_elm_clkctrl;
		mod.context = &omap5430_rm_l4per_elm_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 66500;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_GPIO2;
	mod.id = (int) OMAP5_GPIO2;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_32K_GFCLK;
	mod.sysconfig = &omap5430_gpio2_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_gpio2_clkctrl;
		mod.context = &omap5430es1_rm_l4per_gpio2_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_gpio2_clkctrl;
		mod.context = &omap5430_rm_l4per_gpio2_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_ENAWAKEUP_BIT;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_GPIO3;
	mod.id = (int) OMAP5_GPIO3;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_32K_GFCLK;
	mod.sysconfig = &omap5430_gpio3_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_gpio3_clkctrl;
		mod.context = &omap5430es1_rm_l4per_gpio3_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_gpio3_clkctrl;
		mod.context = &omap5430_rm_l4per_gpio3_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_ENAWAKEUP_BIT;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_GPIO4;
	mod.id = (int) OMAP5_GPIO4;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_32K_GFCLK;
	mod.sysconfig = &omap5430_gpio4_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_gpio4_clkctrl;
		mod.context = &omap5430es1_rm_l4per_gpio4_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_gpio4_clkctrl;
		mod.context = &omap5430_rm_l4per_gpio4_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_ENAWAKEUP_BIT;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_GPIO5;
	mod.id = (int) OMAP5_GPIO5;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_32K_GFCLK;
	mod.sysconfig = &omap5430_gpio5_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_gpio5_clkctrl;
		mod.context = &omap5430es1_rm_l4per_gpio5_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_gpio5_clkctrl;
		mod.context = &omap5430_rm_l4per_gpio5_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_ENAWAKEUP_BIT;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_GPIO6;
	mod.id = (int) OMAP5_GPIO6;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_32K_GFCLK;
	mod.sysconfig = &omap5430_gpio6_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_gpio6_clkctrl;
		mod.context = &omap5430es1_rm_l4per_gpio6_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_gpio6_clkctrl;
		mod.context = &omap5430_rm_l4per_gpio6_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_ENAWAKEUP_BIT;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_GPIO7;
	mod.id = (int) OMAP5_GPIO7;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_32K_GFCLK;
	mod.sysconfig = &omap5430_gpio7_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_gpio7_clkctrl;
		mod.context = &omap5430es1_rm_l4per_gpio7_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_gpio7_clkctrl;
		mod.context = &omap5430_rm_l4per_gpio7_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_ENAWAKEUP_BIT;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_GPIO8;
	mod.id = (int) OMAP5_GPIO8;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_32K_GFCLK;
	mod.sysconfig = &omap5430_gpio8_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_gpio8_clkctrl;
		mod.context = &omap5430es1_rm_l4per_gpio8_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_gpio8_clkctrl;
		mod.context = &omap5430_rm_l4per_gpio8_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_ENAWAKEUP_BIT;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_HDQ1W;
	mod.id = (int) OMAP5_HDQ1W;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_12M_GFCLK;
	mod.sysconfig = &omap5430_hdq_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_hdq1w_clkctrl;
		mod.context = &omap5430es1_rm_l4per_hdq1w_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_hdq1w_clkctrl;
		mod.context = &omap5430_rm_l4per_hdq1w_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 12000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 12000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_I2C1;
	mod.id = (int) OMAP5_I2C1;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_96M_GFCLK;
	mod.sysconfig = &omap5430_i2c1_sysc;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_i2c1_clkctrl;
		mod.context = &omap5430es1_rm_l4per_i2c1_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_i2c1_clkctrl;
		mod.context = &omap5430_rm_l4per_i2c1_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_I2C2;
	mod.id = (int) OMAP5_I2C2;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_96M_GFCLK;
	mod.sysconfig = &omap5430_i2c2_sysc;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_i2c2_clkctrl;
		mod.context = &omap5430es1_rm_l4per_i2c2_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_i2c2_clkctrl;
		mod.context = &omap5430_rm_l4per_i2c2_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_I2C3;
	mod.id = (int) OMAP5_I2C3;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_96M_GFCLK;
	mod.sysconfig = &omap5430_i2c3_sysc;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_i2c3_clkctrl;
		mod.context = &omap5430es1_rm_l4per_i2c3_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_i2c3_clkctrl;
		mod.context = &omap5430_rm_l4per_i2c3_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_I2C4;
	mod.id = (int) OMAP5_I2C4;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_96M_GFCLK;
	mod.sysconfig = &omap5430_i2c4_sysc;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_i2c4_clkctrl;
		mod.context = &omap5430es1_rm_l4per_i2c4_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_i2c4_clkctrl;
		mod.context = &omap5430_rm_l4per_i2c4_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_I2C5;
	mod.id = (int) OMAP5_I2C5;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_96M_GFCLK;
	mod.sysconfig = &omap5430_i2c5_sysc;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_i2c5_clkctrl;
		mod.context = &omap5430es1_rm_l4per_i2c5_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_i2c5_clkctrl;
		mod.context = &omap5430_rm_l4per_i2c5_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_L4_PER_INTERCONNECT;
	mod.id = (int) OMAP5_L4_PER_INTERCONNECT;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4PER_L4_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_l4_per_clkctrl;
		mod.context = &omap5430es1_rm_l4per_l4_per_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_l4_per_clkctrl;
		mod.context = &omap5430_rm_l4per_l4_per_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 66500;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MCSPI1;
	mod.id = (int) OMAP5_MCSPI1;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_48M_GFCLK;
	mod.sysconfig = &omap5430_mcspi1_hl_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_mcspi1_clkctrl;
		mod.context = &omap5430es1_rm_l4per_mcspi1_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_mcspi1_clkctrl;
		mod.context = &omap5430_rm_l4per_mcspi1_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MCSPI2;
	mod.id = (int) OMAP5_MCSPI2;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_48M_GFCLK;
	mod.sysconfig = &omap5430_mcspi2_hl_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_mcspi2_clkctrl;
		mod.context = &omap5430es1_rm_l4per_mcspi2_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_mcspi2_clkctrl;
		mod.context = &omap5430_rm_l4per_mcspi2_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MCSPI3;
	mod.id = (int) OMAP5_MCSPI3;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_48M_GFCLK;
	mod.sysconfig = &omap5430_mcspi3_hl_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_mcspi3_clkctrl;
		mod.context = &omap5430es1_rm_l4per_mcspi3_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_mcspi3_clkctrl;
		mod.context = &omap5430_rm_l4per_mcspi3_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MCSPI4;
	mod.id = (int) OMAP5_MCSPI4;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_48M_GFCLK;
	mod.sysconfig = &omap5430_mcspi4_hl_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_mcspi4_clkctrl;
		mod.context = &omap5430es1_rm_l4per_mcspi4_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_mcspi4_clkctrl;
		mod.context = &omap5430_rm_l4per_mcspi4_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MMC3;
	mod.id = (int) OMAP5_MMC3;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_48M_GFCLK;
	mod.sysconfig = &omap5430_mmchs3_hl_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_mmc3_clkctrl;
		mod.context = &omap5430es1_rm_l4per_mmc3_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_mmc3_clkctrl;
		mod.context = &omap5430_rm_l4per_mmc3_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MMC4;
	mod.id = (int) OMAP5_MMC4;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_48M_GFCLK;
	mod.sysconfig = &omap5430_mmchs4_hl_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_mmc4_clkctrl;
		mod.context = &omap5430es1_rm_l4per_mmc4_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_mmc4_clkctrl;
		mod.context = &omap5430_rm_l4per_mmc4_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MMC5;
	mod.id = (int) OMAP5_MMC5;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_96M_GFCLK;
	mod.sysconfig = &omap5430_mmchs5_hl_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_mmc5_clkctrl;
		mod.context = &omap5430es1_rm_l4per_mmc5_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_mmc5_clkctrl;
		mod.context = &omap5430_rm_l4per_mmc5_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	if (cpu_revision_get() == REV_ES1_0) {
		mod.name = MOD_SLIMBUS2;
		mod.id = (int) OMAP5_SLIMBUS2;
		mod.clkdm = CLKDM_L4_PER;
		mod.pwrdm = PWRDM_L4_PER;
		mod.voltdm = VDD_CORE;
		mod.clk = (int) CLK54XX_PER_24M_GFCLK;
		mod.sysconfig = &omap5430_slimbus2_cmp_sysconfig;
		mod.clkctrl = &omap5430es1_cm_l4per_slimbus2_clkctrl;
		mod.context = &omap5430es1_rm_l4per_slimbus2_context;
		genlist_init(&(mod.mod_opp_list));
		opp.name = OPP_LOW;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 24576;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_HIGH;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_SB;
		opp.rate = -1;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT8 | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
		genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));
	}


	mod.name = MOD_UART1;
	mod.id = (int) OMAP5_UART1;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_48M_GFCLK;
	mod.sysconfig = &omap5430_uart1_sysc;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_uart1_clkctrl;
		mod.context = &omap5430es1_rm_l4per_uart1_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_uart1_clkctrl;
		mod.context = &omap5430_rm_l4per_uart1_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_UART2;
	mod.id = (int) OMAP5_UART2;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_48M_GFCLK;
	mod.sysconfig = &omap5430_uart2_sysc;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_uart2_clkctrl;
		mod.context = &omap5430es1_rm_l4per_uart2_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_uart2_clkctrl;
		mod.context = &omap5430_rm_l4per_uart2_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_UART3;
	mod.id = (int) OMAP5_UART3;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_48M_GFCLK;
	mod.sysconfig = &omap5430_uart3_sysc;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_uart3_clkctrl;
		mod.context = &omap5430es1_rm_l4per_uart3_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_uart3_clkctrl;
		mod.context = &omap5430_rm_l4per_uart3_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_UART4;
	mod.id = (int) OMAP5_UART4;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_48M_GFCLK;
	mod.sysconfig = &omap5430_uart4_sysc;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_uart4_clkctrl;
		mod.context = &omap5430es1_rm_l4per_uart4_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_uart4_clkctrl;
		mod.context = &omap5430_rm_l4per_uart4_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_UART5;
	mod.id = (int) OMAP5_UART5;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_48M_GFCLK;
	mod.sysconfig = &omap5430_uart5_sysc;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_uart5_clkctrl;
		mod.context = &omap5430es1_rm_l4per_uart5_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_uart5_clkctrl;
		mod.context = &omap5430_rm_l4per_uart5_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_UART6;
	mod.id = (int) OMAP5_UART6;
	mod.clkdm = CLKDM_L4_PER;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PER_48M_GFCLK;
	mod.sysconfig = &omap5430_uart6_sysc;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_l4per_uart6_clkctrl;
		mod.context = &omap5430es1_rm_l4per_uart6_context;
	} else {
		mod.clkctrl = &omap5430_cm_l4per_uart6_clkctrl;
		mod.context = &omap5430_rm_l4per_uart6_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 48000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0 | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: L4_PER, Clock domain = L4_SEC */
	/* HS/EMU ONLY */
	mod.name = MOD_DMA_CRYPTO;
	mod.id = (int) OMAP5_DMA_CRYPTO;
	mod.clkdm = CLKDM_L4_SEC;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4SEC_L3_GICLK;
	mod.sysconfig = NULL;
	mod.clkctrl = NULL;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 266000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_AES1;
	mod.id = (int) OMAP5_AES1;
	mod.clkdm = CLKDM_L4_SEC;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4SEC_L3_GICLK;
	mod.sysconfig = NULL;
	mod.clkctrl = NULL;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 266000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_AES2;
	mod.id = (int) OMAP5_AES2;
	mod.clkdm = CLKDM_L4_SEC;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4SEC_L3_GICLK;
	mod.sysconfig = NULL;
	mod.clkctrl = NULL;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 266000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_SHA2MD5;
	mod.id = (int) OMAP5_SHA2MD5;
	mod.clkdm = CLKDM_L4_SEC;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4SEC_L3_GICLK;
	mod.sysconfig = NULL;
	mod.clkctrl = NULL;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 266000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_RNG;
	mod.id = (int) OMAP5_RNG;
	mod.clkdm = CLKDM_L4_SEC;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4SEC_L4_GICLK;
	mod.sysconfig = NULL;
	mod.clkctrl = NULL;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 66500;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_DES3DES;
	mod.id = (int) OMAP5_DES3DES;
	mod.clkdm = CLKDM_L4_SEC;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4SEC_L4_GICLK;
	mod.sysconfig = NULL;
	mod.clkctrl = NULL;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 66500;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_PKA;
	mod.id = (int) OMAP5_PKA;
	mod.clkdm = CLKDM_L4_SEC;
	mod.pwrdm = PWRDM_L4_PER;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_L4SEC_L4_GICLK;
	mod.sysconfig = NULL;
	mod.clkctrl = NULL;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 66500;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 133000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: CORE, Power dom.: ABE, Clock domain = ABE */
	mod.name = MOD_AESS;
	mod.id = (int) OMAP5_AESS;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_AESS_FCLK;
	mod.sysconfig = &omap5430_aess_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_abe_aess_clkctrl;
		mod.context = &omap5430es1_rm_abe_aess_context;
	} else {
		mod.clkctrl = &omap5430_cm_abe_aess_clkctrl;
		mod.context = &omap5430_rm_abe_aess_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 98133;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 196266;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_STANDBY_MODE5 | MOD_HAS_SMART_STANDBY_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_DMIC;
	mod.id = (int) OMAP5_DMIC;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_DMIC_GFCLK;
	mod.sysconfig = &omap5430_dmic_cortex_a15_dmic_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_abe_dmic_clkctrl;
		mod.context = &omap5430es1_rm_abe_dmic_context;
	} else {
		mod.clkctrl = &omap5430_cm_abe_dmic_clkctrl;
		mod.context = &omap5430_rm_abe_dmic_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_L4_ABE_INTERCONNECT;
	mod.id = (int) OMAP5_L4_ABE_INTERCONNECT;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_ABE_GICLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0)
		mod.clkctrl = &omap5430es1_cm_abe_l4_abe_clkctrl;
	else
		mod.clkctrl = &omap5430_cm_abe_l4_abe_clkctrl;
	mod.context = NULL;
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 49066;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 98133;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MCASP;
	mod.id = (int) OMAP5_MCASP;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_MCASP1_GFCLK;
	mod.sysconfig = &omap5430_mcasp_mpu_mcasp_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_abe_mcasp_clkctrl;
		mod.context = &omap5430es1_rm_abe_mcasp_context;
	} else {
		mod.clkctrl = &omap5430_cm_abe_mcasp_clkctrl;
		mod.context = &omap5430_rm_abe_mcasp_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 98000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 98000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE1;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MCBSP1;
	mod.id = (int) OMAP5_MCBSP1;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_MCBSP1_GFCLK;
	mod.sysconfig = &omap5430_mcbsp1_cortex_a15_mcbsplp_sysconfig_reg;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_abe_mcbsp1_clkctrl;
		mod.context = &omap5430es1_rm_abe_mcbsp1_context;
	} else {
		mod.clkctrl = &omap5430_cm_abe_mcbsp1_clkctrl;
		mod.context = &omap5430_rm_abe_mcbsp1_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MCBSP2;
	mod.id = (int) OMAP5_MCBSP2;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_MCBSP2_GFCLK;
	mod.sysconfig = &omap5430_mcbsp2_cortex_a15_mcbsplp_sysconfig_reg;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_abe_mcbsp2_clkctrl;
		mod.context = &omap5430es1_rm_abe_mcbsp2_context;
	} else {
		mod.clkctrl = &omap5430_cm_abe_mcbsp2_clkctrl;
		mod.context = &omap5430_rm_abe_mcbsp2_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MCBSP3;
	mod.id = (int) OMAP5_MCBSP3;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_MCBSP3_GFCLK;
	mod.sysconfig = &omap5430_mcbsp3_cortex_a15_mcbsplp_sysconfig_reg;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_abe_mcbsp3_clkctrl;
		mod.context = &omap5430es1_rm_abe_mcbsp3_context;
	} else {
		mod.clkctrl = &omap5430_cm_abe_mcbsp3_clkctrl;
		mod.context = &omap5430_rm_abe_mcbsp3_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 96000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE4 | MOD_HAS_ENAWAKEUP_BIT | MOD_HAS_CLOCK_ACTIVITY_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_MCPDM;
	mod.id = (int) OMAP5_MCPDM;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_PAD_GCLKS;
	mod.sysconfig = &omap5430_mcpdm_cortex_a15_mcpdm_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_abe_mcpdm_clkctrl;
		mod.context = &omap5430es1_rm_abe_mcpdm_context;
	} else {
		mod.clkctrl = &omap5430_cm_abe_mcpdm_clkctrl;
		mod.context = &omap5430_rm_abe_mcpdm_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_SLIMBUS1;
	mod.id = (int) OMAP5_SLIMBUS1;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_SLIMBUS_UCLKS;
	mod.sysconfig = &omap5430_slimbus1_mpu_slimbus_cmp_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_abe_slimbus1_clkctrl;
		mod.context = &omap5430es1_rm_abe_slimbus1_context;
	} else {
		mod.clkctrl = &omap5430_cm_abe_slimbus1_clkctrl;
		mod.context = &omap5430_rm_abe_slimbus1_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 24576;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT8 | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_TIMER5;
	mod.id = (int) OMAP5_TIMER5;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_TIMER5_GFCLK;
	mod.sysconfig = &omap5430_timer5_mpu_tiocp_cfg;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_abe_timer5_clkctrl;
		mod.context = &omap5430es1_rm_abe_timer5_context;
	} else {
		mod.clkctrl = &omap5430_cm_abe_timer5_clkctrl;
		mod.context = &omap5430_rm_abe_timer5_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_TIMER6;
	mod.id = (int) OMAP5_TIMER6;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_TIMER6_GFCLK;
	mod.sysconfig = &omap5430_timer6_mpu_tiocp_cfg;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_abe_timer6_clkctrl;
		mod.context = &omap5430es1_rm_abe_timer6_context;
	} else {
		mod.clkctrl = &omap5430_cm_abe_timer6_clkctrl;
		mod.context = &omap5430_rm_abe_timer6_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_TIMER7;
	mod.id = (int) OMAP5_TIMER7;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_TIMER7_GFCLK;
	mod.sysconfig = &omap5430_timer7_mpu_tiocp_cfg;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_abe_timer7_clkctrl;
		mod.context = &omap5430es1_rm_abe_timer7_context;
	} else {
		mod.clkctrl = &omap5430_cm_abe_timer7_clkctrl;
		mod.context = &omap5430_rm_abe_timer7_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_TIMER8;
	mod.id = (int) OMAP5_TIMER8;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_TIMER8_GFCLK;
	mod.sysconfig = &omap5430_timer8_mpu_tiocp_cfg;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_abe_timer8_clkctrl;
		mod.context = &omap5430es1_rm_abe_timer8_context;
	} else {
		mod.clkctrl = &omap5430_cm_abe_timer8_clkctrl;
		mod.context = &omap5430_rm_abe_timer8_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 19200;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_WD_TIMER3;
	mod.id = (int) OMAP5_WD_TIMER3;
	mod.clkdm = CLKDM_ABE;
	mod.pwrdm = PWRDM_ABE;
	mod.voltdm = VDD_CORE;
	mod.clk = (int) CLK54XX_ABE_32K_CLK;
	mod.sysconfig = &omap5430_wd_timer3_l3interconnect_wdsc;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_abe_wd_timer3_clkctrl;
		mod.context = &omap5430es1_rm_abe_wd_timer3_context;
	} else {
		mod.clkctrl = &omap5430_cm_abe_wd_timer3_clkctrl;
		mod.context = &omap5430_rm_abe_wd_timer3_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 32;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE4 | MOD_HAS_SMART_IDLE_WAKEUP_MODE;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: MM, Power dom.: DSP, Clock domain = DSP */
	mod.name = MOD_DSP;
	mod.id = (int) OMAP5_DSP;
	mod.clkdm = CLKDM_DSP;
	mod.pwrdm = PWRDM_DSP;
	mod.voltdm = VDD_MM;
	mod.clk = (int) CLK54XX_DSP_GCLK;
	mod.sysconfig = &omap5430_dsp_sysc_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_dsp_dsp_clkctrl;
		mod.context = &omap5430es1_rm_dsp_dsp_context;
	} else {
		mod.clkctrl = &omap5430_cm_dsp_dsp_clkctrl;
		mod.context = &omap5430_rm_dsp_dsp_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 232960;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 465919;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = 531199;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_AUTOIDLE_BIT0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: MM, Power dom.: GPU, Clock domain = GPU */
	mod.name = MOD_GPU;
	mod.id = (int) OMAP5_GPU;
	mod.clkdm = CLKDM_GPU;
	mod.pwrdm = PWRDM_GPU;
	mod.voltdm = VDD_MM;
	mod.clk = (int) CLK54XX_GPU_CORE_GCLK;
	mod.sysconfig = &omap5430_gpu_sysconfig;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_gpu_gpu_clkctrl;
		mod.context = &omap5430es1_rm_gpu_gpu_context;
	} else {
		mod.clkctrl = &omap5430_cm_gpu_gpu_clkctrl;
		mod.context = &omap5430_rm_gpu_gpu_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 212800;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 425471;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = 532000;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS | MOD_HAS_SYSCONFIG | MOD_HAS_IDLE_MODE3 | MOD_HAS_STANDBY_MODE5;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: MM, Power dom.: IVA, Clock domain = IVA */
	mod.name = MOD_IVA;
	mod.id = (int) OMAP5_IVA;
	mod.clkdm = CLKDM_IVA;
	mod.pwrdm = PWRDM_IVA;
	mod.voltdm = VDD_MM;
	mod.clk = (int) CLK54XX_IVA_GCLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_iva_iva_clkctrl;
		mod.context = &omap5430es1_rm_iva_iva_context;
	} else {
		mod.clkctrl = &omap5430_cm_iva_iva_clkctrl;
		mod.context = &omap5430_rm_iva_iva_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 194133;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 388266;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = 531199;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = MOD_HAS_STANDBY_STATUS;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));


	mod.name = MOD_SL2;
	mod.id = (int) OMAP5_SL2;
	mod.clkdm = CLKDM_IVA;
	mod.pwrdm = PWRDM_IVA;
	mod.voltdm = VDD_MM;
	mod.clk = (int) CLK54XX_IVA_GCLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_iva_sl2_clkctrl;
		mod.context = &omap5430es1_rm_iva_sl2_context;
	} else {
		mod.clkctrl = &omap5430_cm_iva_sl2_clkctrl;
		mod.context = &omap5430_rm_iva_sl2_context;
	}
	genlist_init(&(mod.mod_opp_list));
	opp.name = OPP_LOW;
	opp.rate = 194133;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_NOM;
	opp.rate = 388266;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_HIGH;
	opp.rate = 531199;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	opp.name = OPP_SB;
	opp.rate = -1;
	genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	mod.properties = 0;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	/* Voltage dom.: MPU, Power dom.: MPUAON Clock domain = MPU */
	mod.name = MOD_MPU;
	mod.id = (int) OMAP5_MPU;
	mod.clkdm = CLKDM_MPU;
	mod.pwrdm = PWRDM_MPU;
	mod.voltdm = VDD_MPU;
	mod.clk = (int) CLK54XX_MPU_GCLK;
	mod.sysconfig = NULL;
	if (cpu_revision_get() == REV_ES1_0) {
		mod.clkctrl = &omap5430es1_cm_mpu_mpu_clkctrl;
		mod.context = &omap5430es1_rm_mpu_mpu_context;
	} else {
		mod.clkctrl = &omap5430_cm_mpu_mpu_clkctrl;
		mod.context = &omap5430_rm_mpu_mpu_context;
	}
	genlist_init(&(mod.mod_opp_list));
	if (cpu_revision_get() == REV_ES1_0) {
		opp.name = OPP_LOW;
		opp.rate = 400000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 800000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_HIGH;
		opp.rate = 1100000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_SB;
		opp.rate = 1200000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	} else {
		opp.name = OPP_LOW;
		opp.rate = 499200;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_NOM;
		opp.rate = 1099885;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_HIGH;
		opp.rate = 1500000;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
		opp.name = OPP_SB;
		opp.rate = 1699200;
		genlist_addtail(&(mod.mod_opp_list), (void *) &opp, sizeof(mod_opp));
	}
	mod.properties = MOD_HAS_STANDBY_STATUS;
	genlist_addtail(&mod54xx_list, (void *) &mod, sizeof(mod_info));

	mod54xx_init_done = 1;

	dprintf("%s(): init done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_init
 * @BRIEF		initialize internal data
 * @DESCRIPTION		initialize internal data (architecture dependent)
 *//*------------------------------------------------------------------------ */
void mod54xx_init(void)
{
	if (cpu_get() == OMAP_5430)
		mod5430_init();
	else
		mod5432_init();
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_deinit
 * @BRIEF		free dynamically allocated internal data.
 * @DESCRIPTION		free dynamically allocated internal data.
 *			MUST BE CALLED AT END OF EXECUTION.
 *//*------------------------------------------------------------------------ */
void mod54xx_deinit(void)
{
	int i, count;
	mod_info mod;

	if (mod54xx_init_done) {
		count = genlist_getcount(&mod54xx_list);
		for (i = 0; i < count; i++) {
			genlist_get(&mod54xx_list, i, (mod_info *) &mod);
			genlist_free(&(mod.mod_opp_list));
		}
		genlist_free(&mod54xx_list);
		mod54xx_init_done = 0;
	}
	dprintf("%s(): deinit done.\n", __func__);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_list_get
 * @BRIEF		return the list of modules
 * @RETURNS		list of modules in case of success
 *			NULL in case of error
 * @DESCRIPTION		return the list of modules
 *//*------------------------------------------------------------------------ */
const genlist *mod54xx_list_get(void)
{
	mod54xx_init();

	return (const genlist *) &mod54xx_list;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_count_get
 * @BRIEF		return the number of modules
 * @RETURNS		number of modules (> 0) in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @DESCRIPTION		return the number of modules
 *//*------------------------------------------------------------------------ */
int mod54xx_count_get(void)
{
	int count;

	mod54xx_init();

	count = genlist_getcount(&mod54xx_list);

	dprintf("%s() = %d\n", __func__, count);
	return count;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mod54xx_config_show
 * @BRIEF		analyze module power configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 * @param[in,out]	stream: output file
 * @param[in]		id: valid module ID
 * @DESCRIPTION		analyze module power configuration
 *//*------------------------------------------------------------------------ */
int mod54xx_config_show(FILE *stream, mod54xx_id id, unsigned int cm_clkctrl)
{
	char s[72];
	double rate;

	CHECK_CPU(54xx, OMAPCONF_ERR_CPU);
	CHECK_ARG_LESS_THAN(id, MOD54XX_ID_MAX, OMAPCONF_ERR_ARG);

	/* FCLK Source / Optional Clocks */
	switch (id) {
	case OMAP5_DEBUGSS:
		break;

	/* Voltage dom.: WKUP: Power dom.: WKUPAON: Clock domain = WKUPAON */
	case OMAP5_CTRL_MODULE_WKUP:
	case OMAP5_L4WKUP_INTERCONNECT:
	case OMAP5_WD_TIMER2:
	case OMAP5_COUNTER_32K:
	case OMAP5_SARRAM:
	case OMAP5_KBD:
		break;

	case OMAP5_GPIO1:
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional debounce clock",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	case OMAP5_TIMER1:
		fprintf(stream, "| %-32s | %-35s |\n", "FCLK Source",
			((extract_bit(cm_clkctrl, 24) == 1) ?
				"32KHz" : "SYS_CLK"));
		break;

	case OMAP5_IO_SRCOMP_WKUP:
		if (cpu_revision_get() == REV_ES1_0)
			fprintf(stream, "| %-32s | %-35s |\n",
				"Optional functional clock",
				((extract_bit(cm_clkctrl, 8) == 1) ?
					"Enabled" : "Disabled"));
		else
			fprintf(stream, "| %-32s | %-35s |\n",
				"Functional clock",
				((extract_bit(cm_clkctrl, 8) == 1) ?
					"Enabled" : "Disabled"));

		break;

	/* HS/EMU ONLY */
	case OMAP5_TIMER12:
	case OMAP5_WDT1:
		break;

	/* Voltage dom.: CORE: Power dom.: COREAON: Clock domain = COREAON */
	case OMAP5_SMARTREFLEX_CORE:
	case OMAP5_SMARTREFLEX_MM:
	case OMAP5_SMARTREFLEX_MPU:
		break;

	case OMAP5_BANDGAPTS:
		if (cpu_revision_get() != REV_ES1_0) {
			fprintf(stderr,
				"omapconf: %s(): BANDGAPTS does not exist anymore on ES2.x!\n",
				__func__);
			break;
		}
		rate = clk54xx_rate_get(CLK54XX_WKUPAON_GICLK, 0);
		rate /= (double)
			(1 << (3 + extract_bitfield(cm_clkctrl, 24, 2)));
		sprintf(s, "%lfMHz (WKUPAON_ICLK / %-2u)", rate,
			1 << (3 + extract_bitfield(cm_clkctrl, 24, 2)));
		fprintf(stream, "| %-32s | %-35s |\n",
			"TS F-Clock Rate (MHz)", s);
		fprintf(stream, "| %-32s | %-35s |\n", "",
			"  (1MHz < expected rate < 2MHz)");
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional functional clock",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	case OMAP5_IO_SRCOMP_CORE:
		if (cpu_revision_get() == REV_ES1_0)
			fprintf(stream, "| %-32s | %-35s |\n",
				"Optional functional clock",
				((extract_bit(cm_clkctrl, 8) == 1) ?
					"Enabled" : "Disabled"));
		else
			fprintf(stream, "| %-32s | %-35s |\n",
				"Functional clock",
				((extract_bit(cm_clkctrl, 8) == 1) ?
					"Enabled" : "Disabled"));

		break;

	case OMAP5_USB_PHY_CORE:
		if (cpu_revision_get() != REV_ES1_0) {
			fprintf(stderr,
				"omapconf: %s(): USB_PHY_CORE does not exist anymore on ES2.x!\n",
				__func__);
			break;
		}
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional functional clock",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	case OMAP5_USB2PHY:
		if (cpu_revision_get() == REV_ES1_0) {
			fprintf(stderr,
				"omapconf: %s(): USB2PHY does not exist on ES1.0!\n",
				__func__);
			break;
		}
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional functional clock",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	/* Voltage dom.: CORE: Power dom.: CAM: Clock domain = CAM */
	case OMAP5_FDIF:
		fprintf(stream, "| %-32s | %-35s |\n", "FDIF_CLK Ratio",
			((extract_bit(cm_clkctrl, 24) == 1) ?
				"FDIF_CLK = FUNC_128M_CLK / 2" :
				"FDIF_CLK = FUNC_128M_CLK / 1"));
		break;

	case OMAP5_ISS:
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional functional clock",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	case OMAP5_CAL:
		break;

	/* Voltage dom.: CORE: Power dom.: CORE: Clock domain = L4CFG */
	case OMAP5_CTRL_MODULE_CORE:
	case OMAP5_SPINLOCK:
	case OMAP5_L4_CFG_INTERCONNECT:
	case OMAP5_MAILBOX:
	case OMAP5_SARROM:
	case OMAP5_OCP2SCP2:
		break;

	/* Voltage dom.: CORE: Power dom.: CORE: Clock domain = EMIF */
	case OMAP5_PHY_EMIF:
	case OMAP5_DMM:
	case OMAP5_EMIF2:
	case OMAP5_EMIF_OCP_FW:
		break;

	case OMAP5_EMIF1:
		if (cpu_revision_get() == REV_ES1_0)
			break;
		fprintf(stream, "| %-32s | %-35s |\n",
			"EMIF_LL_GCLK Clock Source",
			((extract_bit(cm_clkctrl, 24) == 1) ?
				"Same as LLI" : "Same as C2C"));


	case OMAP5_DLL_EMIF:
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional functional clock",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	/* Voltage dom.: CORE: Power dom.: CORE: Clock domain = IPU */
	case OMAP5_IPU:
		break;

	/* Voltage dom.: CORE: Power dom.: CORE: Clock domain = L3_MAIN2 */
	case OMAP5_GPMC:
	case OMAP5_L3_MAIN2_INTERCONNECT:
	case OMAP5_OCMC_RAM:
		break;

	/* Voltage dom.: CORE: Power dom.: CORE: Clock domain = L3_INSTR */
	case OMAP5_L3_MAIN3_INTERCONNECT:
	case OMAP5_L3_INSTR_INTERCONNECT:
	case OMAP5_OCP_WP_NOC:
		break;

	case OMAP5_CTRL_MODULE_BANDGAP:
		rate = clk54xx_rate_get(CLK54XX_WKUPAON_ICLK, 0);
		rate /= (double)
			(1 << (3 + extract_bitfield(cm_clkctrl, 24, 2)));
		sprintf(s, "%lfMHz (WKUPAON_ICLK / %-2u)", rate,
			1 << (3 + extract_bitfield(cm_clkctrl, 24, 2)));
		fprintf(stream, "| %-32s | %-35s |\n",
			"TS F-Clock Rate (MHz)", s);
		break;

	/* Voltage dom.: CORE: Power dom.: CORE: Clock domain = L3_MAIN1 */
	case OMAP5_L3_MAIN1_INTERCONNECT:
		break;

	/* Voltage dom.: CORE: Power dom.: CORE: Clock domain = C2C */
	case OMAP5_C2C:
	case OMAP5_C2C_OCP_FW:
	case OMAP5_MODEM_ICR:
		break;

	/* Voltage dom.: CORE: Power dom.: CORE: Clock domain = DMA */
	case OMAP5_DMA_SYSTEM:
		break;

	/* Voltage dom.: CORE: Power dom.: CORE: Clock domain = MIPIEXT */
	case OMAP5_LLI:
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional functional clocks:", "");
		fprintf(stream, "| %-32s | %-35s |\n", "  TXPHY_LS_CLK",
			((extract_bit(cm_clkctrl, 9) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  TXPHY_CLK",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	case OMAP5_LLI_OCP_FW:
	case OMAP5_MPHY:
		break;

	case OMAP5_UNIPRO1:
		if (cpu_revision_get() != REV_ES1_0) {
			fprintf(stderr,
				"omapconf: %s(): UNIPRO1 does not exist anymore on ES2.x!\n",
				__func__);
			break;
		}
		fprintf(stream, "| %-32s | %-35s |\n",
			"Internal Timer Clock Ratio",
			((extract_bit(cm_clkctrl, 24) == 1) ?
				"= MIPIEXT_L3_GICLK / 2" :
				"= MIPIEXT_L3_GICLK / 1"));
		break;

	/* Voltage dom.: CORE: Power dom.: DSS: Clock domain = DSS */
	case OMAP5_DSS:
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional functional clocks:", "");
		fprintf(stream, "| %-32s | %-35s |\n", "  32KHz",
			((extract_bit(cm_clkctrl, 11) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  SYS_CLK",
			((extract_bit(cm_clkctrl, 10) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  48MHz_CLK",
			((extract_bit(cm_clkctrl, 9) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  DSSCLK",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	case OMAP5_BB2D:
		break;

	/* Voltage dom.: CORE: Power dom.: L3INIT: Clock domain = L3INIT */
	case OMAP5_HSI:
		fprintf(stream, "| %-32s | %-35s |\n", "FCLK Source",
			((extract_bit(cm_clkctrl, 24) == 1) ?
				"= HSI_FCLK (192MHz) / 2" :
				"= HSI_FCLK (192MHz) / 1"));
		break;

	case OMAP5_IEEE1500_2_OCP:
	case OMAP5_OCPSCP1:
	case OMAP5_MPHY_UNIPRO2:
	case OMAP5_OCPSCP3:
		break;

	case OMAP5_MMC1:
		fprintf(stream, "| %-32s | %-35s |\n", "Clock Ratio",
			((extract_bit(cm_clkctrl, 25) == 1) ?
				"2" : "1"));
		fprintf(stream, "| %-32s | %-35s |\n", "FCLK Source",
			((extract_bit(cm_clkctrl, 24) == 1) ?
				"DPLL_PER 192MHz" : "DPLL_PER 128MHz"));

		if (cpu_revision_get() != REV_ES1_0) {
			fprintf(stream, "| %-32s | %-35s |\n",
				"Optional 32K Functional clocks:",
				((extract_bit(cm_clkctrl, 8) == 1) ?
					"Enabled" : "Disabled"));
		}
		break;

	case OMAP5_MMC2:
		fprintf(stream, "| %-32s | %-35s |\n", "Clock Ratio",
			((extract_bit(cm_clkctrl, 25) == 1) ?
				"2" : "1"));
		fprintf(stream, "| %-32s | %-35s |\n", "FCLK Source",
			((extract_bit(cm_clkctrl, 24) == 1) ?
				"DPLL_PER 192MHz" : "DPLL_PER 128MHz"));
		break;

	case OMAP5_USB_HOST_HS:
		fprintf(stream, "| %-32s | %-35s |\n", "UTMI Port2 Source",
			((extract_bit(cm_clkctrl, 25) == 1) ?
				"External PHY" : "internal"));
		fprintf(stream, "| %-32s | %-35s |\n", "UTMI Port1 Source",
			((extract_bit(cm_clkctrl, 24) == 1) ?
				"External PHY" : "internal"));

		fprintf(stream, "| %-32s | %-35s |\n", "SAR MODE",
			((extract_bit(cm_clkctrl, 4) == 1) ?
				"Enabled" : "Disabled"));

		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional functional clocks:", "");
		fprintf(stream, "| %-32s | %-35s |\n", "  FUNC_48M_GFCLK",
			((extract_bit(cm_clkctrl, 15) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  HSIC_P2_480M_GFCLK",
			((extract_bit(cm_clkctrl, 14) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  HSIC_P1_480M_GFCLK",
			((extract_bit(cm_clkctrl, 13) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  HSIC_P2_60M_GFCLK",
			((extract_bit(cm_clkctrl, 12) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  HSIC_P1_60M_GFCLK",
			((extract_bit(cm_clkctrl, 11) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  UTMI_P3_GFCLK",
			((extract_bit(cm_clkctrl, 10) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  UTMI_P2_GFCLK",
			((extract_bit(cm_clkctrl, 9) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  UTMI_P1_GFCLK",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  HSIC_P3_480M_GFCLK",
			((extract_bit(cm_clkctrl, 7) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  HSIC_P3_60M_GFCLK",
			((extract_bit(cm_clkctrl, 6) == 1) ?
				"Enabled" : "Disabled"));
		break;

	case OMAP5_USB_OTG_SS:
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional 960MHz REF_CLK",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	case OMAP5_USB_TLL_HS:
		fprintf(stream, "| %-32s | %-35s |\n", "SAR MODE",
			((extract_bit(cm_clkctrl, 4) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional functional clocks:", "");
		fprintf(stream, "| %-32s | %-35s |\n", "  USB_CH2_CLK",
			((extract_bit(cm_clkctrl, 10) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  USB_CH1_CLK",
			((extract_bit(cm_clkctrl, 9) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  USB_CH0_CLK",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	case OMAP5_SATA:
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional functional REF_CLK",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	case OMAP5_UNIPRO2:
		fprintf(stream, "| %-32s | %-35s |\n",
			"Internal Timer Clock Ratio",
			((extract_bit(cm_clkctrl, 24) == 1) ?
				"= L3INIT_L3_GICLK / 2" :
				"= L3INIT_L3_GICLK / 1"));
		break;

	/* ES1.0:
	 *   Voltage dom.: CORE: Power dom.: L4_PER: Clock domain = L4_PER
	 * ES2.0:
	 *   Voltage dom.: CORE: Power dom.: CORE: Clock domain = L4_PER
	 */
	case OMAP5_TIMER10:
	case OMAP5_TIMER11:
	case OMAP5_TIMER2:
	case OMAP5_TIMER3:
	case OMAP5_TIMER4:
	case OMAP5_TIMER9:
		fprintf(stream, "| %-32s | %-35s |\n", "FCLK Source",
			((extract_bit(cm_clkctrl, 24) == 1) ?
				"32KHz" : "SYS_CLK"));
		break;

	case OMAP5_GPIO2:
	case OMAP5_GPIO3:
	case OMAP5_GPIO4:
	case OMAP5_GPIO5:
	case OMAP5_GPIO6:
	case OMAP5_GPIO7:
	case OMAP5_GPIO8:
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional debounce clock",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	case OMAP5_ELM:
	case OMAP5_HDQ1W:
	case OMAP5_I2C1:
	case OMAP5_I2C2:
	case OMAP5_I2C3:
	case OMAP5_I2C4:
	case OMAP5_I2C5:
	case OMAP5_L4_PER_INTERCONNECT:
	case OMAP5_MCSPI1:
	case OMAP5_MCSPI2:
	case OMAP5_MCSPI3:
	case OMAP5_MCSPI4:
	case OMAP5_MMC3:
	case OMAP5_MMC4:
	case OMAP5_MMC5:
	case OMAP5_UART1:
	case OMAP5_UART2:
	case OMAP5_UART3:
	case OMAP5_UART4:
	case OMAP5_UART5:
	case OMAP5_UART6:
		break;

	case OMAP5_SLIMBUS2:
		if (cpu_revision_get() != REV_ES1_0) {
			fprintf(stderr,
				"omapconf: %s(): SLIMBUS2 does not exist anymore on ES2.x!\n",
				__func__);
			break;
		}
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional functional clocks:", "");
		fprintf(stream, "| %-32s | %-35s |\n", "  SLIMBUS",
			((extract_bit(cm_clkctrl, 10) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  PER_ABE_24M_GFCLK",
			((extract_bit(cm_clkctrl, 9) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  PER_24M_GFCLK",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	/* Voltage dom.: CORE: Power dom.: L4_PER: Clock domain = L4_SEC */
	/* HS/EMU ONLY */
	case OMAP5_DMA_CRYPTO:
	case OMAP5_AES1:
	case OMAP5_AES2:
	case OMAP5_SHA2MD5:
	case OMAP5_RNG:
	case OMAP5_DES3DES:
	case OMAP5_PKA:
		break;

	/* Voltage dom.: CORE: Power dom.: ABE: Clock domain = ABE */
	case OMAP5_AESS:
		sprintf(s, "%u", 1 << extract_bit(cm_clkctrl, 24));
		fprintf(stream, "| %-32s | %-35s |\n",
			"AESS_FCLK to ABE_CLK Ratio", s);
		break;

	case OMAP5_DMIC:
	case OMAP5_MCASP:
	case OMAP5_MCBSP1:
	case OMAP5_MCBSP2:
	case OMAP5_MCBSP3:
		switch (extract_bitfield(cm_clkctrl, 24, 2)) {
		case 0:
			switch (extract_bitfield(cm_clkctrl, 26, 2)) {
			case 0:
				fprintf(stream, "| %-32s | %-35s |\n",
					"FCLK Source", "24MHz from DPLL_ABE");
				break;
			case 1:
				fprintf(stream, "| %-32s | %-35s |\n",
					"FCLK Source", "ABE_SYSCLK");
				break;
			case 2:
				fprintf(stream, "| %-32s | %-35s |\n",
					"FCLK Source", "24MHz from DPLL_PER");
				break;
			default:
				fprintf(stream, "| %-32s | %-35s |\n",
					"FCLK Source", "Reserved!");
				break;
			}
			break;
		case 1:
			fprintf(stream, "| %-32s | %-35s |\n",
				"FCLK Source", "CLKS pad");
			break;
		case 2:
			fprintf(stream, "| %-32s | %-35s |\n",
				"FCLK Source", "Audio SLIMBUS pad");
			break;
		default:
			fprintf(stream, "| %-32s | %-35s |\n",
				"FCLK Source", "Reserved!");
			break;
		}
		break;

	case OMAP5_L4_ABE_INTERCONNECT:
	case OMAP5_MCPDM:
	case OMAP5_WD_TIMER3:
		break;

	case OMAP5_SLIMBUS1:
		fprintf(stream, "| %-32s | %-35s |\n",
			"Optional functional clocks:", "");
		fprintf(stream, "| %-32s | %-35s |\n", "  SLIMBUS",
			((extract_bit(cm_clkctrl, 11) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  FCLK2",
			((extract_bit(cm_clkctrl, 10) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  FCLK1",
			((extract_bit(cm_clkctrl, 9) == 1) ?
				"Enabled" : "Disabled"));
		fprintf(stream, "| %-32s | %-35s |\n", "  FCLK0",
			((extract_bit(cm_clkctrl, 8) == 1) ?
				"Enabled" : "Disabled"));
		break;

	case OMAP5_TIMER5:
	case OMAP5_TIMER6:
	case OMAP5_TIMER7:
	case OMAP5_TIMER8:
		fprintf(stream, "| %-32s | %-35s |\n", "FCLK Source",
			((extract_bit(cm_clkctrl, 24) == 1) ?
				"ABE_32K_CLK" : "ABE_SYS_CLK"));
		break;

	/* Voltage dom.: MM: Power dom.: DSP: Clock domain = DSP */
	case OMAP5_DSP:
		break;

	/* Voltage dom.: MM: Power dom.: GPU: Clock domain = GPU */
	case OMAP5_GPU:
		if (cpu_revision_get() != REV_ES1_0)
			fprintf(stream, "| %-32s | %-35s |\n",
				"GPU_SYS_CLK Ratio",
				((extract_bit(cm_clkctrl, 26) == 1) ?
					"L3_ICLK / 2" : "L3_ICLK / 1"));
		fprintf(stream, "| %-32s | %-35s |\n", "GPU_HYD_GCLK Source",
			((extract_bit(cm_clkctrl, 25) == 1) ?
				"DPLL_PER HS Div." : "DPLL_CORE HS Div."));
		fprintf(stream, "| %-32s | %-35s |\n", "GPU_CORE_GCLK Source",
			((extract_bit(cm_clkctrl, 24) == 1) ?
				"DPLL_PER HS Div." : "DPLL_CORE HS Div."));
		break;

	/* Voltage dom.: MM: Power dom.: IVA: Clock domain = IVA */
	case OMAP5_IVA:
	case OMAP5_SL2:
		break;

	/* Voltage dom.: MPU: Power dom.: MPU Clock domain = MPU */
	case OMAP5_MPU:
		fprintf(stream, "| %-32s | %-35s |\n",
			"MPU-ABE SS Bridge Ratio",
			((extract_bit(cm_clkctrl, 26) == 1) ? "16" : "8"));
		switch (extract_bitfield(cm_clkctrl, 24, 2)) {
		case 0:
		case 1:
			fprintf(stream, "| %-32s | %-35s |\n",
				"MPU-L3MAIN Interc. Bridge Ratio", "4");
			break;
		case 2:
		case 3:
			fprintf(stream, "| %-32s | %-35s |\n",
				"MPU-L3MAIN Interc. Bridge Ratio", "8");
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}

	return 0;
}
