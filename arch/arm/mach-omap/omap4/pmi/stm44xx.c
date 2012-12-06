/*
 *
 * @Component			OMAPCONF
 * @Filename			stm44xx.c
 * @Description			OMAP4 STM configuration & control functions
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


#include <stm44xx.h>
#include <emu44xx.h>
#include <coresight44xx.h>
#include <lib.h>
#include <lib44xx.h>
#include <mem.h>
#include <stdio.h>


/* #define STM_OMAP4_DEBUG */
#ifdef STM_OMAP4_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

static const reg_table omap4_stm_reg_table[18] = {
	{"STM_SYSCONFIG", OMAP4430_STM_SYSCONFIG},
	{"STM_SYSSTATUS", OMAP4430_STM_SYSSTATUS},
	{"STM_SWMCTRL0", OMAP4430_STM_SWMCTRL0},
	{"STM_SWMCTRL1", OMAP4430_STM_SWMCTRL1},
	{"STM_SWMCTRL2", OMAP4430_STM_SWMCTRL2},
	{"STM_SWMCTRL3", OMAP4430_STM_SWMCTRL3},
	{"STM_SWMCTRL4", OMAP4430_STM_SWMCTRL4},
	{"STM_HWMCTRL", OMAP4430_STM_HWMCTRL},
	{"PTI_CONFIG", OMAP4430_PTI_CONFIG},
	{"PTI_COUNTD", OMAP4430_PTI_COUNTD},
	{"ATB_CONFIG", OMAP4430_ATB_CONFIG},
	{"ATB_POINTER", OMAP4430_ATB_POINTER},
	{"ATB_ID", OMAP4430_ATB_ID},
	{"STM_CTS", OMAP4430_STM_CTS},
	{"STM_CTC", OMAP4430_STM_CTC},
	{"STM_LOCK", OMAP4430_STM_LOCK},
	{"STM_LOCK_STS", OMAP4430_STM_LOCK_STS},
	{"END", 0} };


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		stm_claim_ownership
 * @BRIEF		claim STM ownership in order to be able to R/W registers.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @DESCRIPTION		claim STM ownership in order to be able to R/W registers.
 *			NB: must be called before any other access to STM
 *			registers.
 *			NB: make sure EMU domain is ON before calling this
 *			function.
 *//*------------------------------------------------------------------------ */
int stm_claim_ownership(void)
{
	if (!emu44xx_is_enabled()) {
		printf("stm_claim_ownership(): "
			"trying to enable ETB but EMU domain OFF!!!\n");
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	if (stm_is_claimed()) {
		printf("stm_claim_ownership(): STM already claimed!\n");
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	/* Unlock STM write access */
	mem_write(OMAP4430_STM_LOCK, OMAP4_CORESIGHT_UNLOCK_VALUE);
	/* Claim ownership */
	mem_write(OMAP4430_STM_SWMCTRL0, 0x40000000);
	/* Enable ownership */
	mem_write(OMAP4430_STM_SWMCTRL0, 0x80000000);

	dprintf("stm_claim_ownership(): STM claimed.\n");
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		stm_is_claimed
 * @BRIEF		check if STM is claimed, i.e. registers accessible.
 * @RETURNS		0 STM not accessible
 *			!=0 STM accessible
 * @DESCRIPTION		check if STM is claimed, i.e. registers accessible.
 *			NB: make sure EMU domain is ON before calling this
 *			function.
 *//*------------------------------------------------------------------------ */
int stm_is_claimed(void)
{
	unsigned int stm_swmctrl0;

	if (!emu44xx_is_enabled())
		return 0;

	mem_read(OMAP4430_STM_SWMCTRL0, &stm_swmctrl0);

	return ((stm_swmctrl0 & 0xC0000000) == 0x80000000);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		stm_release_ownership
 * @BRIEF		release STM ownership.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_INTERNAL
 * @DESCRIPTION		release STM ownership.
 *			NB: must be called at end of STM use.
 *			NB: make sure EMU domain is ON before calling this
 *			function.
 *//*------------------------------------------------------------------------ */
int stm_release_ownership(void)
{
	if (!emu44xx_is_enabled()) {
		printf("stm_release_ownership(): "
			"trying to enable ETB but EMU domain OFF!!!\n");
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	if (!stm_is_claimed()) {
		printf("stm_release_ownership(): STM not claimed!\n");
		return OMAPCONF_ERR_INTERNAL;
	}

	/* Release ownership */
	mem_write(OMAP4430_STM_SWMCTRL0, 0x00000000);

	dprintf("stm_release_ownership(): STM released.\n");
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		stm_dump_regs
 * @BRIEF		dump STM registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @DESCRIPTION		dump STM registers
 *//*------------------------------------------------------------------------ */
int stm_dump_regs(void)
{
	if (!emu44xx_is_enabled()) {
		printf("stm_dump_regs(): "
			"trying to enable ETB but EMU domain OFF!!!\n");
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	if (!stm_is_claimed()) {
		printf("stm_dump_regs(): STM not claimed!\n");
		return OMAPCONF_ERR_INTERNAL;
	}

	return dumpregs((reg_table *) omap4_stm_reg_table);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		stm_hw_master_enable
 * @BRIEF		enable stm hw master
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_INTERNAL
 *			OMAPCONF_ERR_ARG
 * @param[in]		hwmid: hw master ID
 * @param[in]		pos: register position
 * @DESCRIPTION		enable stm hw master
 *//*------------------------------------------------------------------------ */
int stm_hw_master_enable(stm_hw_masters hwmid, unsigned char pos)
{
	unsigned int stm_hwmctrl, mask;

	if (!emu44xx_is_enabled()) {
		printf("stm_hw_master_enable(): "
			"trying to enable ETB but EMU domain OFF!!!\n");
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}
	if (!stm_is_claimed()) {
		printf("stm_hw_master_enable(): STM not claimed!\n");
		return OMAPCONF_ERR_INTERNAL;
	}
	if (hwmid >= HW_MASTER_MAX) {
		printf("stm_hw_master_enable(): "
			"hwmid (0x%02X) >= HW_MASTER_MAX!\n", hwmid);
		return OMAPCONF_ERR_ARG;
	}
	if (pos > 3) {
		printf("stm_hw_master_enable(): "
			"pos (%d) > 3!\n", pos);
		return OMAPCONF_ERR_ARG;
	}

	mem_read(OMAP4430_STM_HWMCTRL, &stm_hwmctrl);
	pos = 2 + (8 * pos);
	mask = ~(0x1F << pos);
	stm_hwmctrl &= mask;
	stm_hwmctrl |= hwmid << pos;
	mem_write(OMAP4430_STM_HWMCTRL, stm_hwmctrl);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		stm_hw_master_disable
 * @BRIEF		disable stm hw master
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_INTERNAL
 *			OMAPCONF_ERR_ARG
 * @param[in]		pos: register position
 * @DESCRIPTION		disable stm hw master
 *//*------------------------------------------------------------------------ */
int stm_hw_master_disable(unsigned char pos)
{
	unsigned int stm_hwmctrl, mask;

	if (!emu44xx_is_enabled()) {
		printf("stm_hw_master_disable(): "
			"trying to enable ETB but EMU domain OFF!!!\n");
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}
	if (!stm_is_claimed()) {
		printf("stm_hw_master_disable(): STM not claimed!\n");
		return OMAPCONF_ERR_INTERNAL;
	}
	if (pos > 3) {
		printf("stm_hw_master_disable(): pos (%d) > 3!\n", pos);
		return OMAPCONF_ERR_ARG;
	}

	mem_read(OMAP4430_STM_HWMCTRL, &stm_hwmctrl);
	pos = 2 + (8 * pos);
	mask = ~(0x1F << pos);
	stm_hwmctrl &= mask;
	mem_write(OMAP4430_STM_HWMCTRL, stm_hwmctrl);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		stm_atb_capture_enable
 * @BRIEF		enable STM trace to be captured in ETB via ATB
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @DESCRIPTION		enable STM trace to be captured in ETB via ATB
 *			NB: make sure EMU domain is ON before calling this
 *			function.
 *//*------------------------------------------------------------------------ */
int stm_atb_capture_enable(void)
{
	if (!emu44xx_is_enabled()) {
		printf("stm_atb_capture_enable(): "
			"trying to enable ETB but EMU domain OFF!!!\n");
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}
	if (!stm_is_claimed()) {
		printf("stm_atb_capture_enable(): STM not claimed!\n");
		return OMAPCONF_ERR_INTERNAL;
	}

	mem_write(OMAP4430_ATB_CONFIG, 0x00010000);

	#ifdef STM_OMAP4_DEBUG
	printf("stm_atb_capture_enable(): ATB capture enabled.\n");
	dumpregs((reg_table *) omap4_stm_reg_table);
	#endif

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		stm_atb_capture_disable
 * @BRIEF		disable STM trace capture in ETB via ATB
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @DESCRIPTION		disable STM trace capture in ETB via ATB
 *			NB: make sure EMU domain is ON before calling this
 *			function.
 *			NB: blocking until STM FIFO is empty
 *//*------------------------------------------------------------------------ */
int stm_atb_capture_disable(void)
{
	unsigned int stm_sysstatus;

	if (!emu44xx_is_enabled()) {
		printf("stm_atb_capture_disable(): EMU domain OFF!!!\n");
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}
	if (!stm_is_claimed()) {
		printf("stm_atb_capture_disable(): STM not claimed!\n");
		return OMAPCONF_ERR_INTERNAL;
	}

	do {
		mem_read(OMAP4430_STM_SYSSTATUS, &stm_sysstatus);
	} while (stm_sysstatus != 0x00000101);
	dprintf("stm_atb_capture_disable(): STM FIFO empty.\n");

	/* Disable ATB */
	mem_write(OMAP4430_ATB_CONFIG, 0x00000000);

	dprintf("stm_atb_capture_disable(): ATB capture disabled.\n");

	#ifdef STM_OMAP4_DEBUG
	stm_last_header_pos_get();
	stm_dump_regs();
	#endif

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		stm_last_header_pos_get
 * @BRIEF		return the position of the last STP header in the last
 *			32-bit ATB word stored
 * @RETURNS		>=0 STP header position
 *			<8 STP header is in the last ETB entry
 *			>=8 STP header is in the (last -1) ETB entry
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_INTERNAL
 * @DESCRIPTION		return the position of the last STP header in the last
 *			32-bit ATB word stored
 *			NB: make sure EMU domain is ON before calling this
 *			function.
 *//*------------------------------------------------------------------------ */
int stm_last_header_pos_get(void)
{
	unsigned int atb_pointer;

	if (!emu44xx_is_enabled()) {
		printf("stm_atb_capture_disable(): "
			"trying to enable ETB but EMU domain OFF!!!\n");
		return OMAPCONF_ERR_INTERNAL;
	}
	if (!stm_is_claimed()) {
		printf("stm_atb_capture_disable(): STM not claimed!\n");
		return OMAPCONF_ERR_INTERNAL;
	}

	mem_read(OMAP4430_ATB_POINTER, &atb_pointer);
	dprintf("stm_last_header_pos_get(): atb_pointer = 0x%08X\n",
		atb_pointer);
	if ((atb_pointer & 0x00000008) == 0x00000008) {
		dprintf("stm_last_header_pos_get(): "
			"STP Header pos = %d in last ETB entry\n",
			atb_pointer & 0x00000007);
		return (atb_pointer & 0x00000007);
	} else if ((atb_pointer & 0x00000080) == 0x00000080) {
		dprintf("stm_last_header_pos_get(): "
			"STP Header pos = %d in (last -1) ETB entry\n",
			8 + ((atb_pointer & 0x00000070) >> 4));
		return (8 + ((atb_pointer & 0x00000070) >> 4));

	} else {
		dprintf("stm_last_header_pos_get(): no STP Header present!\n");
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		stm_atb_prescaler_set
 * @BRIEF		set ATB local timestamp reference clock prescaler
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @param[in]		div: prescaler (must be power of 2 and <= 128)
 * @DESCRIPTION		set ATB local timestamp reference clock prescaler
 *			NB: make sure EMU domain is ON before calling this
 *			function.
 *//*------------------------------------------------------------------------ */
int stm_atb_prescaler_set(unsigned char div)
{
	unsigned int atb_config, i;

	if (!emu44xx_is_enabled()) {
		printf("stm_atb_prescaler_set(): EMU domain OFF!!!\n");
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}
	if (!stm_is_claimed()) {
		printf("stm_atb_prescaler_set(): STM not claimed!\n");
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	for (i = 0; i < 8; i++) {
		if (div == (1 << i)) {
			dprintf("div=%d => i=%d\n", div, i);
			mem_read(OMAP4430_ATB_CONFIG, &atb_config);
			atb_config &= 0xFFFFFFF8;
			atb_config |= i;
			dprintf("atb_config=0x%08X\n", atb_config);
			mem_write(OMAP4430_ATB_CONFIG, atb_config);
			return 0;
		}
	}

	printf("stm_atb_prescaler_set(): div (%d) must be "
		"power of 2 and <= 128!\n", div);
	return OMAPCONF_ERR_ARG;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		stm_atb_prescaler_get
 * @BRIEF		return ATB local timestamp reference clock prescaler
 * @RETURNS		>0 prescaler value
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @DESCRIPTION		return ATB local timestamp reference clock prescaler
 *			NB: make sure EMU domain is ON before calling this
 *			function.
 *//*------------------------------------------------------------------------ */
int stm_atb_prescaler_get(void)
{
	unsigned int atb_config;

	if (!emu44xx_is_enabled()) {
		printf("stm_atb_prescaler_get(): "
			"trying to enable ETB but EMU domain OFF!!!\n");
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}
	if (!stm_is_claimed()) {
		printf("stm_atb_prescaler_get(): STM not claimed!\n");
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	mem_read(OMAP4430_ATB_CONFIG, &atb_config);
	atb_config &= 0x00000007;
	dprintf("stm_atb_prescaler_get(): "
		"(atb_config & 0x00000007)=0x%08X, div=%d\n",
		atb_config, 1 << atb_config);
	return (1 << atb_config);
}
