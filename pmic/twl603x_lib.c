/*
 *
 * @Component			OMAPCONF
 * @Filename			twl603x_lib.c
 * @Description			OMAP4 TWL603x Power Companion Chip Library
 * @Author			Nishanth Menon (nm@ti.com)
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


#include <twl603x_lib.h>
#include <lib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <twl603x.h>
#include <i2c-tools.h>
#include <autoadjust_table.h>


/* #define TWL603X_LIB_DEBUG */
#ifdef TWL603X_LIB_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/**
 * struct supply_reg_offs - register offsets
 * @grp:	CFG reg
 * @trans:	TRANS reg
 * @state:	STATE reg
 * @volt:	CFG_VOLTAGE
 * @step:	STEP reg
 */
struct supply_reg_offs {
	unsigned char grp;
	unsigned char trans;
	unsigned char state;
	unsigned char volt;
	unsigned char step;
};

struct supply_reg_vals {
	char *name;
	char mask;
	char val;
};

/**
 * struct twl6030_supply - describe the supply
 * @name:		name of the supply
 * @max_current:	max current in uA
 * @base_addr:		base address
 * @regs:		register offset
 *
 */
struct twl6030_supply {
	char *name;
	unsigned long max_current;
	unsigned char base_addr;
	struct supply_reg_offs *regs;
	struct supply_reg_vals *grp_vals;
	struct supply_reg_vals *trans_vals;
	struct supply_reg_vals *state_vals;
	void (*read_voltage) (unsigned char volt_reg_val,
			      unsigned long *voltage);
	void (*read_step) (unsigned char volt_reg_val, unsigned long *uv_per_us,
			   unsigned char *ramp_applied);
};

static struct supply_reg_offs default_smps_reg_off = {
	.grp = 0x0,
	.trans = 0x1,
	.state = 0x2,
	.volt = 0x4,
	.step = 0xFF,		/* No Ramps usually */
};

static struct supply_reg_offs default_vcore_reg_off = {
	.grp = 0x0,
	.trans = 0x1,
	.state = 0x2,
	.volt = 0xFF,		/* ACCESS FROM I2C_SR only */
	.step = 0x5,
};

static struct supply_reg_vals default_supply_grp_val[] = {
	{.name = "APP", .mask = 0x01, .val = 0x01},
	{.name = "CON", .mask = 0x02, .val = 0x02},
	{.name = "MOD", .mask = 0x04, .val = 0x04},
	{0},
};

static struct supply_reg_vals default_supply_state_val[] = {
	{.name = "CURR:OFF", .mask = 0x03 << 0, .val = 0x00 << 0},
	{.name = "CURR:ON", .mask = 0x03 << 0, .val = 0x01 << 0},
	{.name = "CURR:OFF", .mask = 0x03 << 0, .val = 0x02 << 0},
	{.name = "CURR:SLP", .mask = 0x03 << 0, .val = 0x03 << 0},
	{.name = "APP:OFF", .mask = 0x03 << 2, .val = 0x00 << 2},
	{.name = "APP:ON", .mask = 0x03 << 2, .val = 0x01 << 2},
	{.name = "APP:OFF", .mask = 0x03 << 2, .val = 0x02 << 2},
	{.name = "APP:SLP", .mask = 0x03 << 2, .val = 0x03 << 2},
	{.name = "CON:OFF", .mask = 0x03 << 4, .val = 0x00 << 4},
	{.name = "CON:ON", .mask = 0x03 << 4, .val = 0x01 << 4},
	{.name = "CON:OFF", .mask = 0x03 << 4, .val = 0x02 << 4},
	{.name = "CON:SLP", .mask = 0x03 << 4, .val = 0x03 << 4},
	{.name = "MOD:OFF", .mask = 0x03 << 6, .val = 0x00 << 6},
	{.name = "MOD:ON", .mask = 0x03 << 6, .val = 0x01 << 6},
	{.name = "MOD:OFF", .mask = 0x03 << 6, .val = 0x02 << 6},
	{.name = "MOD:SLP", .mask = 0x03 << 6, .val = 0x03 << 6},
	{0},
};

static struct supply_reg_vals default_smps_trans_val[] = {
	{.name = "ACT:OFF", .mask = 0x03 << 0, .val = 0x00 << 0},
	{.name = "ACT:AUTO(PWM/PFM)", .mask = 0x03 << 0, .val = 0x01 << 0},
	{.name = "ACT:RES", .mask = 0x03 << 0, .val = 0x02 << 0},
	{.name = "ACT:PWM", .mask = 0x03 << 0, .val = 0x03 << 0},
	{.name = "SLP:OFF", .mask = 0x03 << 2, .val = 0x00 << 2},
	{.name = "SLP:AUTO(PWM/PFM)", .mask = 0x03 << 2, .val = 0x01 << 2},
	{.name = "SLP:RES", .mask = 0x03 << 2, .val = 0x02 << 2},
	{.name = "SLP:PWM", .mask = 0x03 << 2, .val = 0x03 << 2},
	{.name = "OFF:OFF", .mask = 0x03 << 4, .val = 0x00 << 4},
	{.name = "OFF:AUTO(PWM/PFM)", .mask = 0x03 << 4, .val = 0x01 << 4},
	{.name = "OFF:RES", .mask = 0x03 << 4, .val = 0x02 << 4},
	{.name = "OFF:PWM", .mask = 0x03 << 4, .val = 0x03 << 4},
	{0},
};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		smps_read_voltage
 * @BRIEF
 * @RETURNS
 * @param[in]
 * @param[in, out]
 * @DESCRIPTION
 *//*------------------------------------------------------------------------ */
static void smps_read_voltage(unsigned char volt_reg_val,
			      unsigned long *voltage)
{
	*voltage = volt_reg_val & 0x1f;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vcore_read_step
 * @BRIEF
 * @RETURNS
 * @param[in]
 * @DESCRIPTION
 *//*------------------------------------------------------------------------ */
void vcore_read_step(unsigned char volt_reg_val, unsigned long *uv_per_us,
		     unsigned char *ramp_applied)
{
	*ramp_applied = (volt_reg_val & 0x80) ? 0 : 1;
	if (*ramp_applied) {
		*uv_per_us = (volt_reg_val & 0xf);
		/*
		 * if value < 0x6, clamp already applied due min delay of
		 * 6 clk cycles :(
		 */
		if (*uv_per_us < 0x6)
			*uv_per_us = 0x6;
		*uv_per_us *= 12500;	/* value * 12.5mV in uV */
	} else {
		*uv_per_us = 0;
	}
}

static struct twl6030_supply smps_supplies[] = {
	{
	 .name = "v1v29",
	 .max_current = 600000,
	 .base_addr = 0x40,
	 .regs = &default_smps_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_smps_trans_val,
	 .state_vals = default_supply_state_val,
	 .read_voltage = smps_read_voltage,
	 },
	{
	 .name = "v1v8",
	 .max_current = 1200000,
	 .base_addr = 0x46,
	 .regs = &default_smps_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_smps_trans_val,
	 .state_vals = default_supply_state_val,
	 .read_voltage = smps_read_voltage,
	 },
	{
	 .name = "v2v1",
	 .max_current = 600000,
	 .base_addr = 0x4c,
	 .regs = &default_smps_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_smps_trans_val,
	 .state_vals = default_supply_state_val,
	 .read_voltage = smps_read_voltage,
	 },
	{
	 .name = "vcore1",
	 .max_current = 1200000,
	 .base_addr = 0x52,
	 .regs = &default_vcore_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_smps_trans_val,
	 .state_vals = default_supply_state_val,
	 .read_step = vcore_read_step,
	 },
	{
	 .name = "vcore2",
	 .max_current = 600000,
	 .base_addr = 0x58,
	 .regs = &default_vcore_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_smps_trans_val,
	 .state_vals = default_supply_state_val,
	 .read_step = vcore_read_step,
	 },
	{
	 .name = "vcore3",
	 .max_current = 600000,
	 .base_addr = 0x5e,
	 .regs = &default_vcore_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_smps_trans_val,
	 .state_vals = default_supply_state_val,
	 .read_step = vcore_read_step,
	 },
	{
	 .name = "vmem",
	 .max_current = 600000,
	 .base_addr = 0x64,
	 .regs = &default_smps_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_smps_trans_val,
	 .state_vals = default_supply_state_val,
	 .read_voltage = smps_read_voltage,
	 },
	{0}
};

static struct supply_reg_offs default_ldo_reg_off = {
	.grp = 0x0,
	.trans = 0x1,
	.state = 0x2,
	.volt = 0x3,
	.step = 0xFF,		/* No Ramps usually */
};

static struct supply_reg_vals default_ldo_trans_val[] = {
	{.name = "ACT:OFF", .mask = 0x03 << 0, .val = 0x00 << 0},
	{.name = "ACT:AMS(SLP/ACT)", .mask = 0x03 << 0, .val = 0x01 << 0},
	{.name = "ACT:RES", .mask = 0x03 << 0, .val = 0x02 << 0},
	{.name = "ACT:ACT", .mask = 0x03 << 0, .val = 0x03 << 0},
	{.name = "SLP:OFF", .mask = 0x03 << 2, .val = 0x00 << 2},
	{.name = "SLP:AMS(SLP/ACT)", .mask = 0x03 << 2, .val = 0x01 << 2},
	{.name = "SLP:RES", .mask = 0x03 << 2, .val = 0x02 << 2},
	{.name = "SLP:ACT", .mask = 0x03 << 2, .val = 0x03 << 2},
	{.name = "OFF:OFF", .mask = 0x03 << 4, .val = 0x00 << 4},
	{.name = "OFF:AMS(SLP/ACT)", .mask = 0x03 << 4, .val = 0x01 << 4},
	{.name = "OFF:RES", .mask = 0x03 << 4, .val = 0x02 << 4},
	{.name = "OFF:ACT", .mask = 0x03 << 4, .val = 0x03 << 4},
	{0},
};

static struct supply_reg_offs default_vrtc_reg_off = {
	.grp = 0x0,
	.trans = 0x1,
	.state = 0x2,
	.volt = 0xFF,
	.step = 0xFF,		/* No Ramps usually */
};

static struct supply_reg_vals default_vrtc_trans_val[] = {
	{.name = "ACT:OFF", .mask = 0x03 << 0, .val = 0x00 << 0},
	{.name = "ACT:AMS(SLP/ACT)", .mask = 0x03 << 0, .val = 0x01 << 0},
	{.name = "ACT:RES", .mask = 0x03 << 0, .val = 0x02 << 0},
	{.name = "ACT:VBRTC ACT/VRTC OFF", .mask = 0x03 << 0, .val = 0x03 << 0},
	{.name = "SLP:OFF", .mask = 0x03 << 2, .val = 0x00 << 2},
	{.name = "SLP:AMS(SLP/ACT)", .mask = 0x03 << 2, .val = 0x01 << 2},
	{.name = "SLP:RES", .mask = 0x03 << 2, .val = 0x02 << 2},
	{.name = "SLP:VBRTC ACT/VRTC OFF", .mask = 0x03 << 2, .val = 0x03 << 2},
	{.name = "OFF:OFF", .mask = 0x03 << 4, .val = 0x00 << 4},
	{.name = "OFF:AMS(SLP/ACT)", .mask = 0x03 << 4, .val = 0x01 << 4},
	{.name = "OFF:RES", .mask = 0x03 << 4, .val = 0x02 << 4},
	{.name = "OFF:VBRTC ACT/VRTC OFF", .mask = 0x03 << 4, .val = 0x03 << 4},
	{0},
};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		ldo_read_voltage
 * @BRIEF
 * @RETURNS
 * @param[in]
 * @DESCRIPTION
 *//*------------------------------------------------------------------------ */
static void ldo_read_voltage(unsigned char volt_reg_val, unsigned long *voltage)
{
	*voltage = volt_reg_val & 0x1f;
}

static struct twl6030_supply ldo_supplies[] = {
	{
	 .name = "vana",
	 .max_current = 25000,
	 .base_addr = 0x80,
	 .regs = &default_ldo_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_ldo_trans_val,
	 .state_vals = default_supply_state_val,
	 .read_voltage = ldo_read_voltage,

	 },
	{
	 .name = "vaux1",
	 .max_current = 200000,
	 .base_addr = 0x84,
	 .regs = &default_ldo_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_ldo_trans_val,
	 .state_vals = default_supply_state_val,
	 .read_voltage = ldo_read_voltage,
	 },
	{
	 .name = "vaux2",
	 .max_current = 200000,
	 .base_addr = 0x88,
	 .regs = &default_ldo_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_ldo_trans_val,
	 .state_vals = default_supply_state_val,
	 .read_voltage = ldo_read_voltage,
	 },
	{
	 .name = "vaux3",
	 .max_current = 200000,
	 .base_addr = 0x8c,
	 .regs = &default_ldo_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_ldo_trans_val,
	 .state_vals = default_supply_state_val,
	 .read_voltage = ldo_read_voltage,
	 },
	/*
	   {
	   .name = "vbrtc",
	   .max_current = 1500,
	   .base_addr = 0x80,
	   .regs = &default_ldo_reg_off,
	   .grp_vals = default_supply_grp_val,
	   .trans_vals = default_ldo_trans_val,
	   .state_vals = default_supply_state_val,
	   .read_voltage = ldo_read_voltage,
	   }, */
	{
	 .name = "vcxio",
	 .max_current = 200000,
	 .base_addr = 0x90,
	 .regs = &default_ldo_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_ldo_trans_val,
	 .state_vals = default_supply_state_val,
	 .read_voltage = ldo_read_voltage,
	 },
	{
	 .name = "vdac",
	 .max_current = 50000,
	 .base_addr = 0x94,
	 .regs = &default_ldo_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_ldo_trans_val,
	 .state_vals = default_supply_state_val,
	 .read_voltage = ldo_read_voltage,
	 },
	{
	 .name = "vmmc",
	 .max_current = 200000,	/* IN1  -200mA, IN2- 50mA? */
	 .base_addr = 0x98,
	 .regs = &default_ldo_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_ldo_trans_val,
	 .state_vals = default_supply_state_val,
	 .read_voltage = ldo_read_voltage,
	 },
	{
	 .name = "vpp",
	 .max_current = 50000,
	 .base_addr = 0x9c,
	 .regs = &default_ldo_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_ldo_trans_val,
	 .state_vals = default_supply_state_val,
	 .read_voltage = ldo_read_voltage,
	 },
	{
	 .name = "vrtc",
	 .max_current = 25000,
	 .base_addr = 0xc2,
	 .regs = &default_vrtc_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_vrtc_trans_val,
	 .state_vals = default_supply_state_val,
	 .read_voltage = ldo_read_voltage,
	 },
	{
	 .name = "vusb",
	 .max_current = 35000,
	 .base_addr = 0xA0,
	 .regs = &default_ldo_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_ldo_trans_val,
	 .state_vals = default_supply_state_val,
	 .read_voltage = ldo_read_voltage,
	 },
	{
	 .name = "vusim",
	 .max_current = 50000,
	 .base_addr = 0xa4,
	 .regs = &default_ldo_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_ldo_trans_val,
	 .state_vals = default_supply_state_val,
	 .read_voltage = ldo_read_voltage,
	 },
	{0}
};

static struct supply_reg_offs default_res_reg_off = {
	.grp = 0x0,
	.trans = 0x1,
	.state = 0x2,
	.volt = 0xFF,
	.step = 0xFF,		/* No Ramps usually */
};

static struct supply_reg_vals default_res_trans_val[] = {
	{.name = "ACT:OFF", .mask = 0x03 << 0, .val = 0x00 << 0},
	{.name = "ACT:ON", .mask = 0x03 << 0, .val = 0x01 << 0},
	{.name = "ACT:RES", .mask = 0x03 << 0, .val = 0x02 << 0},
	{.name = "ACT:RES", .mask = 0x03 << 0, .val = 0x03 << 0},
	{.name = "SLP:OFF", .mask = 0x03 << 2, .val = 0x00 << 2},
	{.name = "SLP:ON", .mask = 0x03 << 2, .val = 0x01 << 2},
	{.name = "SLP:RES", .mask = 0x03 << 2, .val = 0x02 << 2},
	{.name = "SLP:RES", .mask = 0x03 << 2, .val = 0x03 << 2},
	{.name = "OFF:OFF", .mask = 0x03 << 4, .val = 0x00 << 4},
	{.name = "OFF:ON", .mask = 0x03 << 4, .val = 0x01 << 4},
	{.name = "OFF:RES", .mask = 0x03 << 4, .val = 0x02 << 4},
	{.name = "OFF:RES", .mask = 0x03 << 4, .val = 0x03 << 4},
	{0},
};

static struct twl6030_supply resource_dep[] = {
	{
	 .name = "REGEN1",
	 .base_addr = 0xad,
	 .regs = &default_res_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_res_trans_val,
	 .state_vals = default_supply_state_val,
	 },
	{
	 .name = "REGEN2",
	 .base_addr = 0xb0,
	 .regs = &default_res_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_res_trans_val,
	 .state_vals = default_supply_state_val,
	 },
	{
	 .name = "SYSEN",
	 .base_addr = 0xb3,
	 .regs = &default_res_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_res_trans_val,
	 .state_vals = default_supply_state_val,
	 },
	{
	 .name = "NRESPWRON",
	 .base_addr = 0xb6,
	 .regs = &default_res_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_res_trans_val,
	 .state_vals = default_supply_state_val,
	 },
	{
	 .name = "CLK32KAO",
	 .base_addr = 0xb9,
	 .regs = &default_res_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_res_trans_val,
	 .state_vals = default_supply_state_val,
	 },
	{
	 .name = "CLK32KG",
	 .base_addr = 0xbc,
	 .regs = &default_res_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_res_trans_val,
	 .state_vals = default_supply_state_val,
	 },
	{
	 .name = "CLK32KAUDIO",
	 .base_addr = 0xbf,
	 .regs = &default_res_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_res_trans_val,
	 .state_vals = default_supply_state_val,
	 },
	{
	 .name = "BIAS",
	 .base_addr = 0xc6,
	 .regs = &default_res_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_res_trans_val,
	 .state_vals = default_supply_state_val,
	 },
	{
	 .name = "VBATMIN_HI",
	 .base_addr = 0xc8,
	 .regs = &default_res_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_res_trans_val,
	 .state_vals = default_supply_state_val,
	 },
	{
	 .name = "RC6MHZ",
	 .base_addr = 0xcb,
	 .regs = &default_res_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_res_trans_val,
	 .state_vals = default_supply_state_val,
	 },
	{
	 .name = "TEMP",
	 .base_addr = 0xce,
	 .regs = &default_res_reg_off,
	 .grp_vals = default_supply_grp_val,
	 .trans_vals = default_res_trans_val,
	 .state_vals = default_supply_state_val,
	 },
	{0},
};

static struct supply_reg_vals device_state_val[] = {
	{.name = "APP:OFF", .mask = 0x03 << 0, .val = 0x00 << 0},
	{.name = "APP:COMP", .mask = 0x03 << 0, .val = 0x01 << 0},
	{.name = "APP:ACTIVE", .mask = 0x03 << 0, .val = 0x02 << 0},
	{.name = "APP:SLEEP", .mask = 0x03 << 0, .val = 0x03 << 0},
	{.name = "CON:OFF", .mask = 0x03 << 2, .val = 0x00 << 2},
	{.name = "CON:COMP", .mask = 0x03 << 2, .val = 0x01 << 2},
	{.name = "CON:ACTIVE", .mask = 0x03 << 2, .val = 0x02 << 2},
	{.name = "CON:SLEEP", .mask = 0x03 << 2, .val = 0x03 << 2},
	{.name = "MOD:OFF", .mask = 0x03 << 4, .val = 0x00 << 4},
	{.name = "MOD:COMP", .mask = 0x03 << 4, .val = 0x01 << 4},
	{.name = "MOD:ACTIVE", .mask = 0x03 << 4, .val = 0x02 << 4},
	{.name = "MOD:SLEEP", .mask = 0x03 << 4, .val = 0x03 << 4},
	{0},
};

static struct supply_reg_offs default_dev_reg_off = {
	.grp = 0xFF,
	.trans = 0xFF,
	.state = 0x0,
	.volt = 0xFF,
	.step = 0xFF,
};

static struct twl6030_supply device_status[] = {
	{
	 .name = "Device level PWR GROUP STATE",
	 .base_addr = 0x27,
	 .regs = &default_dev_reg_off,
	 .state_vals = device_state_val,
	 },
	{0},
};

enum print_table {
	PRINT_NAME,
	PRINT_STATE,
	PRINT_GRP,
	PRINT_TRANS,
	PRINT_MAX_CURRENT,
	PRINT_VOLTAGE,
	PRINT_STEP,
	PRINT_MAX
};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dump_reg
 * @BRIEF
 * @RETURNS
 * @param[in]
 * @DESCRIPTION
 *//*------------------------------------------------------------------------ */
void dump_reg(char *pstring, struct supply_reg_vals *reg, unsigned char reg_val)
{
	pstring[0] = 0;

	while (reg->mask) {
		if ((reg_val & reg->mask) == reg->val) {
			strncat(pstring, reg->name, TABLE_MAX_ELT_LEN);
			strncat(pstring, " ", TABLE_MAX_ELT_LEN);
		}
		reg++;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl603x_dump_supplies
 * @BRIEF
 * @RETURNS
 * @param[in]
 * @DESCRIPTION
 *//*------------------------------------------------------------------------ */
static int twl603x_dump_supplies(FILE *stream, char *name,
					  struct twl6030_supply *supply,
					  unsigned char *reg_dump,
					  unsigned char grp,
					  unsigned char trans,
					  unsigned char voltage,
					  unsigned char step)
{
	unsigned int ret = 0;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row = 0;
	unsigned int max_col = PRINT_MAX;

	autoadjust_table_init(table);

	if (stream != NULL) {
		fprintf(stream, "=====================\n");
		fprintf(stream, "%20s\n", name);
		fprintf(stream, "=====================\n");
	}

	strncpy(table[row][PRINT_NAME], "Name", TABLE_MAX_ELT_LEN);
	if (grp) {
		strncpy(table[row][PRINT_GRP], "Group Config",
			TABLE_MAX_ELT_LEN);
	} else {
		max_col--;
	}
	if (trans) {
		strncpy(table[row][PRINT_TRANS], "Transition Config",
			TABLE_MAX_ELT_LEN);
	} else {
		max_col--;
	}
	strncpy(table[row][PRINT_STATE], "State Config", TABLE_MAX_ELT_LEN);
	if (voltage) {
		strncpy(table[row][PRINT_MAX_CURRENT], "Max Current(mA)",
			TABLE_MAX_ELT_LEN);
		strncpy(table[row][PRINT_VOLTAGE], "Voltage(hex)",
			TABLE_MAX_ELT_LEN);
	} else {
		max_col -= 2;
	}
	if (step) {
		strncpy(table[row][PRINT_STEP], "Step config(mV/uSec)",
			TABLE_MAX_ELT_LEN);
	} else {
		max_col--;
	}
	row++;
	while (supply->regs) {
		snprintf(table[row][PRINT_NAME], TABLE_MAX_ELT_LEN, "%s",
			 supply->name);
		if (voltage)
			snprintf(table[row][PRINT_MAX_CURRENT],
				 TABLE_MAX_ELT_LEN, "%5ld.%1ld",
				 supply->max_current / 1000,
				 supply->max_current % 1000);
		if (grp && supply->regs->grp != 0xFF)
			dump_reg(table[row][PRINT_GRP], supply->grp_vals,
				 reg_dump[supply->regs->grp +
					  supply->base_addr]);
		if (trans && supply->regs->trans != 0xFF)
			dump_reg(table[row][PRINT_TRANS], supply->trans_vals,
				 reg_dump[supply->regs->trans +
					  supply->base_addr]);
		if (supply->regs->state != 0xFF)
			dump_reg(table[row][PRINT_STATE], supply->state_vals,
				 reg_dump[supply->regs->state +
					  supply->base_addr]);
		if (voltage && supply->regs->volt != 0xFF) {
			unsigned long x = 0;
			if (supply->read_voltage) {
				supply->read_voltage(reg_dump
						     [supply->regs->volt +
						      supply->base_addr], &x);
				snprintf(table[row][PRINT_VOLTAGE],
					 TABLE_MAX_ELT_LEN, "0x%02x",
					 (unsigned int)x);
			} else {
				strncpy(table[row][PRINT_VOLTAGE], "TBD",
					TABLE_MAX_ELT_LEN);
			}
		}
		if (step && supply->regs->step != 0xFF) {
			unsigned long x = 0;
			unsigned char y = 0;
			if (supply->read_step) {
				supply->read_step(reg_dump
						  [supply->regs->step +
						   supply->base_addr], &x, &y);
				snprintf(table[row][PRINT_STEP],
					 TABLE_MAX_ELT_LEN, "%s:%5ld.%1ld",
					 (y) ? "Ramp applied" :
					 "No ramp applied", (y) ? x / 1000 : 0,
					 (y) ? x % 1000 : 0);
			} else {
				strncpy(table[row][PRINT_STEP], "TBD",
					TABLE_MAX_ELT_LEN);
			}
		}

		supply++;
		row++;
	}
	if (stream != NULL)
		autoadjust_table_fprint(stream, table, row, max_col);

	return ret;
}


#define MAX_I2C_REGS 256
static unsigned char twl6030_reg_base_id1[MAX_I2C_REGS];
static unsigned char twl6030_reg_base_id2[MAX_I2C_REGS];
static unsigned char twl6030_reg_base_id3[MAX_I2C_REGS];


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6030_load_regs
 * @BRIEF
 * @RETURNS
 * @param[in]
 * @DESCRIPTION
 *//*------------------------------------------------------------------------ */
static int twl6030_load_regs(unsigned char bus_id,
			     unsigned char slave_addr, unsigned char *reg_dump)
{
	int ret = 0;
	int i;
	for (i = 0; i < MAX_I2C_REGS; i++) {
		unsigned int x;
		ret = i2cget(bus_id, slave_addr, i, &x);
		if (ret != 0) {
			printf
			    ("twl6030_load_regs(): read error! "
			     "(bus=%d, slave=%d, addr=0x%02X, err=%d)\n",
			     bus_id, slave_addr, i, ret);
			return ret;
		}
		reg_dump[i] = (unsigned char)x;
	}
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl603x_init_regtable
 * @BRIEF
 * @RETURNS
 * @param[in]
 * @DESCRIPTION
 *//*------------------------------------------------------------------------ */
void twl603x_init_regtable(void)
{
	/* Do nothing for now! */
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl6030_print_regs_base_addr
 * @BRIEF
 * @RETURNS
 * @param[in]
 * @DESCRIPTION
 *//*------------------------------------------------------------------------ */
static void twl6030_print_regs_base_addr(FILE *stream,
					 unsigned char bus_id,
					 unsigned char slave_addr, unsigned char
					 *reg_dump)
{
	int r;
	if (twl603x_is_twl6035())
		fprintf(stream,
			"BUS=%d SLAVE ADDR=0x%02X REGISTER BASE ADDR=0x%02X\n",
			bus_id, slave_addr, (slave_addr - 0x48 + 1) << 8);
	else
		fprintf(stream,
			"BUS=%d SLAVE ADDR=0x%02X\n", bus_id, slave_addr);
	fprintf(stream,
		"---------------------------------------------------------\n");
	fprintf(stream, "      ");
	for (r = 0; r < 0x10; r++)
		fprintf(stream, "%2x ", r);
	for (r = 0; r < MAX_I2C_REGS; r++) {
		if (!(r % 0x10))
			fprintf(stream, "\n0x%02x: ", r);
		fprintf(stream, "%02x ", reg_dump[r]);
	}
	fprintf(stream, "\n");
	fprintf(stream, "====================================================="
		"====\n\n");
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl603x_dumpregs
 * @BRIEF
 * @RETURNS
 * @param[in]
 * @DESCRIPTION
 *//*------------------------------------------------------------------------ */
int twl603x_dumpregs(FILE *stream)
{
	int r;
	r = twl6030_load_regs(TWL6030_I2C_BUS, TWL6030_I2C_ID1,
			      twl6030_reg_base_id1);
	if (r)
		return r;
	r = twl6030_load_regs(TWL6030_I2C_BUS, TWL6030_I2C_ID2,
			      twl6030_reg_base_id2);
	if (r)
		return r;
	r = twl6030_load_regs(TWL6030_I2C_BUS, TWL6030_I2C_ID3,
			      twl6030_reg_base_id3);
	if (r)
		return r;
	if (twl603x_is_twl6035())
		fprintf(stream, "REGISTER DUMP FOR TWL6035\n");
	else if (twl603x_is_twl6032())
		fprintf(stream, "REGISTER DUMP FOR TWL6032\n");
	else
		fprintf(stream, "REGISTER DUMP FOR TWL6030\n");
	fprintf(stream,
		"=========================================================\n");
	twl6030_print_regs_base_addr(stream, TWL6030_I2C_BUS,
				     TWL6030_I2C_ID1, twl6030_reg_base_id1);
	twl6030_print_regs_base_addr(stream, TWL6030_I2C_BUS,
				     TWL6030_I2C_ID2, twl6030_reg_base_id2);
	twl6030_print_regs_base_addr(stream, TWL6030_I2C_BUS,
				     TWL6030_I2C_ID3, twl6030_reg_base_id3);
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl603x_config_ldo
 * @BRIEF
 * @RETURNS
 * @param[in]
 * @DESCRIPTION
 *//*------------------------------------------------------------------------ */
int twl603x_config_ldo(FILE *stream)
{
	int r;
	r = twl6030_load_regs(TWL6030_I2C_BUS, TWL6030_I2C_ID1,
			      twl6030_reg_base_id1);
	if (r)
		return r;
	r = twl603x_dump_supplies(stream, "Device Level status",
		device_status, twl6030_reg_base_id1, 0, 0, 0, 0);
	if (r)
		return r;
	r = twl603x_dump_supplies(stream, "LDO Supplies", ldo_supplies,
		twl6030_reg_base_id1, 1, 1, 1, 0);
	return r;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl603x_config_smps
 * @BRIEF
 * @RETURNS
 * @param[in]
 * @DESCRIPTION
 *//*------------------------------------------------------------------------ */
int twl603x_config_smps(FILE *stream)
{
	int r;
	r = twl6030_load_regs(TWL6030_I2C_BUS, TWL6030_I2C_ID1,
			      twl6030_reg_base_id1);
	if (r)
		return r;
	r = twl603x_dump_supplies(stream, "Device Level status",
		device_status, twl6030_reg_base_id1, 0, 0, 0, 0);
	if (r)
		return r;
	r = twl603x_dump_supplies(stream, "SMPS Supplies",
		smps_supplies, twl6030_reg_base_id1, 1, 1, 1, 1);
	return r;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl603x_config_resources
 * @BRIEF
 * @RETURNS
 * @param[in]
 * @DESCRIPTION
 *//*------------------------------------------------------------------------ */
int twl603x_config_resources(FILE *stream)
{
	int r;
	r = twl6030_load_regs(TWL6030_I2C_BUS, TWL6030_I2C_ID1,
			      twl6030_reg_base_id1);
	if (r)
		return r;
	r = twl603x_dump_supplies(stream, "Device Level status",
		device_status, twl6030_reg_base_id1, 0, 0, 0, 0);
	if (r)
		return r;
	r = twl603x_dump_supplies(stream, "Resources", resource_dep,
		twl6030_reg_base_id1, 1, 1, 0, 0);
	return r;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl603x_config_devpwrgrp_status
 * @BRIEF
 * @RETURNS
 * @param[in]
 * @DESCRIPTION
 *//*------------------------------------------------------------------------ */
int twl603x_config_devpwrgrp_status(FILE *stream)
{
	int r;
	r = twl6030_load_regs(TWL6030_I2C_BUS, TWL6030_I2C_ID1,
			      twl6030_reg_base_id1);
	if (r)
		return r;
	r = twl603x_dump_supplies(stream, "Device Level status",
		device_status, twl6030_reg_base_id1, 0, 0, 0, 0);
	return r;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl603x_config
 * @BRIEF
 * @RETURNS
 * @param[in]
 * @DESCRIPTION
 *//*------------------------------------------------------------------------ */
int twl603x_config(FILE *stream)
{
	int r;
	r = twl6030_load_regs(TWL6030_I2C_BUS, TWL6030_I2C_ID1,
			      twl6030_reg_base_id1);
	if (r)
		return r;
	r = twl603x_dump_supplies(stream, "SMPS supplies",
		smps_supplies, twl6030_reg_base_id1, 1, 1, 1, 1);
	if (r)
		return r;
	r = twl603x_dump_supplies(stream, "LDO Supplies", ldo_supplies,
		twl6030_reg_base_id1, 1, 1, 1, 0);
	if (r)
		return r;
	r = twl603x_dump_supplies(stream, "Resources", resource_dep,
		twl6030_reg_base_id1, 1, 1, 0, 0);
	if (r)
		return r;
	r = twl603x_dump_supplies(stream, "Device Level status",
		device_status, twl6030_reg_base_id1, 0, 0, 0, 0);
	return r;
}

#define TWL6030_RESET_TIMEOUT	5


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl603x_reset
 * @BRIEF
 * @RETURNS
 * @param[in]
 * @DESCRIPTION
 *//*------------------------------------------------------------------------ */
int twl603x_reset(FILE *stream)
{
	int i = 0;

	fprintf(stream, "PHOENIX WILL BE S/w RESET in %d seconds. "
		"Press CTRL+C to abort. Counting down..\n",
		TWL6030_RESET_TIMEOUT);

	for (i = TWL6030_RESET_TIMEOUT; i > 0; i--) {
		fprintf(stream, "Time remaining: %d seconds..\n", i);
		sleep(1);
	}
	/* Write to SW_RESET bit(bit 6) in PHOENIX_DEV_ON reg(0x25) */
	i2cset(TWL6030_I2C_BUS, TWL6030_I2C_ID1, 0x25, 0x1 << 6);
	/* we are not gonna return back */
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		twl603x_pwrgrp_set
 * @BRIEF
 * @RETURNS
 * @param[in]
 * @DESCRIPTION
 *//*------------------------------------------------------------------------ */
int twl603x_pwrgrp_set(FILE *stream, char *grp, char *state)
{
	unsigned char val = 0;
	if (strcmp(grp, "app") == 0) {
		val = 0x1;
	} else if (strcmp(grp, "con") == 0) {
		val = 0x2;
	} else if (strcmp(grp, "mod") == 0) {
		val = 0x4;
	} else {
		fprintf(stream, "setpwrgrp: ERROR: group %s "
			"is not in MOD, CON or APP\n", grp);
		return OMAPCONF_ERR_ARG;
	}
	if (strcmp(state, "on") == 0) {
		val <<= 3;
	} else if (strcmp(state, "off") == 0) {
		val <<= 0;
	} else {
		fprintf(stream, "setpwrgrp: ERROR: state %s  is not "
			"ON or OFF\n", state);
		return OMAPCONF_ERR_ARG;
	}

	/* THOU SHALT NOT RESET TWL! */
	val &= ~(0x1 << 6);

	/* Write to SW_RESET bit(bit 6) in PHOENIX_DEV_ON reg(0x25) */
	i2cset(TWL6030_I2C_BUS, TWL6030_I2C_ID1, 0x25, val);
	/* ignore the readback result */
	return 0;
}
