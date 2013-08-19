/*
 *
 * @Component			OMAPCONF
 * @Filename			mcasp_dra7xx.c
 * @Description			Multichannel Audio Serial Port
 * @Author			Misael Lopez Cruz (misael.lopez@ti.com)
 * @Date			2013
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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

#include <stdio.h>
#include <lib.h>
#include <autoadjust_table.h>
#include <help.h>
#include <cpuinfo.h>
#include <mem.h>
#include <mcasp_dra7xx.h>
#include <cm_dra7xx-defs.h>
#include <prcm-common.h>

/* #define MCASP_DRA7XX_DEBUG */
#ifdef MCASP_DRA7XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

#define MCASP_BITFIELD(entry, mask)		((entry.value & mask) >> (ffs(mask) - 1))

#define MCASP_READREG(baseaddr, entry)		OMAP_READREG(baseaddr + entry.offset, \
							     entry.value)

#define SET_TABLE_TITLE(table, format, ...)	snprintf(table[0][0], TABLE_MAX_ELT_LEN, \
							 format, ## __VA_ARGS__)
#define SET_TABLE_PARAM(table, format, ...)	snprintf(table[row][0], TABLE_MAX_ELT_LEN, \
							 format, ## __VA_ARGS__)
#define SET_TABLE_VALUE(table, format, ...)	snprintf(table[row][1], TABLE_MAX_ELT_LEN, \
							 format, ## __VA_ARGS__)

typedef struct {
	const unsigned int offset;
	unsigned int value;
} reg_entry;

struct mcasp_regs {
	reg_entry pwridlesysconfig;
	reg_entry pfunc;
	reg_entry pdir;
	reg_entry pdout;
	reg_entry pdin;
	reg_entry gblctl;
	reg_entry rxmask;
	reg_entry rxfmt;
	reg_entry rxfmctl;
	reg_entry aclkrctl;
	reg_entry ahclkrctl;
	reg_entry rxtdm;
	reg_entry evtctlr;
	reg_entry rxstat;
	reg_entry rxtdmslot;
	reg_entry revtctl;
	reg_entry txmask;
	reg_entry txfmt;
	reg_entry txfmctl;
	reg_entry aclkxctl;
	reg_entry ahclkxctl;
	reg_entry txtdm;
	reg_entry evtctlx;
	reg_entry txstat;
	reg_entry txtdmslot;
	reg_entry xevtctl;
	reg_entry xrsrctl[16];
	reg_entry wfifoctl;
	reg_entry wfifosts;
	reg_entry rfifoctl;
	reg_entry rfifosts;
	int num_serializers;
};

static struct mcasp_regs mcasp_regs = {
	.pwridlesysconfig = { .offset = PWRIDLESYSCONFIG_OFFSET },
	.pfunc     = { .offset = MCASP_PFUNC_OFFSET },
	.pdir      = { .offset = MCASP_PDIR_OFFSET },
	.pdout     = { .offset = MCASP_PDOUT_OFFSET },
	.pdin      = { .offset = MCASP_PDIN_OFFSET },
	.gblctl    = { .offset = MCASP_GBLCTL_OFFSET },
	.rxmask    = { .offset = MCASP_RXMASK_OFFSET },
	.rxfmt     = { .offset = MCASP_RXFMT_OFFSET },
	.rxfmctl   = { .offset = MCASP_RXFMCTL_OFFSET },
	.aclkrctl  = { .offset = MCASP_ACLKRCTL_OFFSET },
	.ahclkrctl = { .offset = MCASP_AHCLKRCTL_OFFSET },
	.rxtdm     = { .offset = MCASP_RXTDM_OFFSET },
	.evtctlr   = { .offset = MCASP_EVTCTLR_OFFSET },
	.rxstat    = { .offset = MCASP_RXSTAT_OFFSET },
	.rxtdmslot = { .offset = MCASP_RXTDMSLOT_OFFSET },
	.revtctl   = { .offset = MCASP_REVTCTL_OFFSET },
	.txmask    = { .offset = MCASP_TXMASK_OFFSET },
	.txfmt     = { .offset = MCASP_TXFMT_OFFSET },
	.txfmctl   = { .offset = MCASP_TXFMCTL_OFFSET },
	.aclkxctl  = { .offset = MCASP_ACLKXCTL_OFFSET },
	.ahclkxctl = { .offset = MCASP_AHCLKXCTL_OFFSET },
	.txtdm     = { .offset = MCASP_TXTDM_OFFSET },
	.evtctlx   = { .offset = MCASP_EVTCTLX_OFFSET },
	.txstat    = { .offset = MCASP_TXSTAT_OFFSET },
	.txtdmslot = { .offset = MCASP_TXTDMSLOT_OFFSET },
	.xevtctl   = { .offset = MCASP_XEVTCTL_OFFSET },
	.xrsrctl   = {
		{ .offset = MCASP_XRSRCTL_OFFSET(0) },
		{ .offset = MCASP_XRSRCTL_OFFSET(1) },
		{ .offset = MCASP_XRSRCTL_OFFSET(2) },
		{ .offset = MCASP_XRSRCTL_OFFSET(3) },
		{ .offset = MCASP_XRSRCTL_OFFSET(4) },
		{ .offset = MCASP_XRSRCTL_OFFSET(5) },
		{ .offset = MCASP_XRSRCTL_OFFSET(6) },
		{ .offset = MCASP_XRSRCTL_OFFSET(7) },
		{ .offset = MCASP_XRSRCTL_OFFSET(8) },
		{ .offset = MCASP_XRSRCTL_OFFSET(9) },
		{ .offset = MCASP_XRSRCTL_OFFSET(10) },
		{ .offset = MCASP_XRSRCTL_OFFSET(11) },
		{ .offset = MCASP_XRSRCTL_OFFSET(12) },
		{ .offset = MCASP_XRSRCTL_OFFSET(13) },
		{ .offset = MCASP_XRSRCTL_OFFSET(14) },
		{ .offset = MCASP_XRSRCTL_OFFSET(15) },
	},
	.wfifoctl   = { .offset = MCASP_WFIFOCTL_OFFSET },
	.wfifosts   = { .offset = MCASP_WFIFOSTS_OFFSET },
	.rfifoctl   = { .offset = MCASP_RFIFOCTL_OFFSET },
	.rfifosts   = { .offset = MCASP_RFIFOSTS_OFFSET },
};

/* Common CFG registers for all McASP instances */
static const reg_table mcasp_cfg_reg_table[] = {
	{"MCASP_PID", MCASP_PID_OFFSET},
	{"PWRIDLESYSCONFIG", PWRIDLESYSCONFIG_OFFSET},
	{"MCASP_PFUNC", MCASP_PFUNC_OFFSET},
	{"MCASP_PDIR", MCASP_PDIR_OFFSET},
	{"MCASP_PDOUT", MCASP_PDOUT_OFFSET},
	{"MCASP_PDIN", MCASP_PDIN_OFFSET},
	{"MCASP_PDCLR", MCASP_PDCLR_OFFSET},
	{"MCASP_GBLCTL", MCASP_GBLCTL_OFFSET},
	{"MCASP_AMUTE", MCASP_AMUTE_OFFSET},
	{"MCASP_LBCTL", MCASP_LBCTL_OFFSET},
	{"MCASP_TXDITCTL", MCASP_TXDITCTL_OFFSET},
	{"MCASP_GBLCTLR", MCASP_GBLCTLR_OFFSET},
	{"MCASP_RXMASK", MCASP_RXMASK_OFFSET},
	{"MCASP_RXFMT", MCASP_RXFMT_OFFSET},
	{"MCASP_RXFMCTL", MCASP_RXFMCTL_OFFSET},
	{"MCASP_ACLKRCTL", MCASP_ACLKRCTL_OFFSET},
	{"MCASP_AHCLKRCTL", MCASP_AHCLKRCTL_OFFSET},
	{"MCASP_RXTDM", MCASP_RXTDM_OFFSET},
	{"MCASP_EVTCTLR", MCASP_EVTCTLR_OFFSET},
	{"MCASP_RXSTAT", MCASP_RXSTAT_OFFSET},
	{"MCASP_RXTDMSLOT", MCASP_RXTDMSLOT_OFFSET},
	{"MCASP_RXCLKCHK", MCASP_RXCLKCHK_OFFSET},
	{"MCASP_REVTCTL", MCASP_REVTCTL_OFFSET},
	{"MCASP_GBLCTLX", MCASP_GBLCTLX_OFFSET},
	{"MCASP_TXMASK", MCASP_TXMASK_OFFSET},
	{"MCASP_TXFMT", MCASP_TXFMT_OFFSET},
	{"MCASP_TXFMCTL", MCASP_TXFMCTL_OFFSET},
	{"MCASP_ACLKXCTL", MCASP_ACLKXCTL_OFFSET},
	{"MCASP_AHCLKXCTL", MCASP_AHCLKXCTL_OFFSET},
	{"MCASP_TXTDM", MCASP_TXTDM_OFFSET},
	{"MCASP_EVTCTLX", MCASP_EVTCTLX_OFFSET},
	{"MCASP_TXSTAT", MCASP_TXSTAT_OFFSET},
	{"MCASP_TXTDMSLOT", MCASP_TXTDMSLOT_OFFSET},
	{"MCASP_TXCLKCHK", MCASP_TXCLKCHK_OFFSET},
	{"MCASP_XEVTCTL", MCASP_XEVTCTL_OFFSET},
	{"MCASP_CLKADJEN", MCASP_CLKADJEN_OFFSET},
	{"END", 0},
};

/* McASP1 and McASP2 have 16 serializers */
static const reg_table mcasp_cfg_16ser_reg_table[] = {
	{"MCASP_XRSRCTL0", MCASP_XRSRCTL_OFFSET(0)},
	{"MCASP_XRSRCTL1", MCASP_XRSRCTL_OFFSET(1)},
	{"MCASP_XRSRCTL2", MCASP_XRSRCTL_OFFSET(2)},
	{"MCASP_XRSRCTL3", MCASP_XRSRCTL_OFFSET(3)},
	{"MCASP_XRSRCTL4", MCASP_XRSRCTL_OFFSET(4)},
	{"MCASP_XRSRCTL5", MCASP_XRSRCTL_OFFSET(5)},
	{"MCASP_XRSRCTL6", MCASP_XRSRCTL_OFFSET(6)},
	{"MCASP_XRSRCTL7", MCASP_XRSRCTL_OFFSET(7)},
	{"MCASP_XRSRCTL8", MCASP_XRSRCTL_OFFSET(8)},
	{"MCASP_XRSRCTL9", MCASP_XRSRCTL_OFFSET(9)},
	{"MCASP_XRSRCTL10", MCASP_XRSRCTL_OFFSET(10)},
	{"MCASP_XRSRCTL11", MCASP_XRSRCTL_OFFSET(11)},
	{"MCASP_XRSRCTL12", MCASP_XRSRCTL_OFFSET(12)},
	{"MCASP_XRSRCTL13", MCASP_XRSRCTL_OFFSET(13)},
	{"MCASP_XRSRCTL14", MCASP_XRSRCTL_OFFSET(14)},
	{"MCASP_XRSRCTL15", MCASP_XRSRCTL_OFFSET(15)},
	{"END", 0},
};

/* McASP3 through McASP8 have 4 serializers */
static const reg_table mcasp_cfg_4ser_reg_table[] = {
	{"MCASP_XRSRCTL0", MCASP_XRSRCTL_OFFSET(0)},
	{"MCASP_XRSRCTL1", MCASP_XRSRCTL_OFFSET(1)},
	{"MCASP_XRSRCTL2", MCASP_XRSRCTL_OFFSET(2)},
	{"MCASP_XRSRCTL3", MCASP_XRSRCTL_OFFSET(3)},
	{"END", 0},
};

/* McASP AFIFO registers */
static const reg_table mcasp_afifo_reg_table[] = {
	{"MCASP_WFIFOCTL", MCASP_WFIFOCTL_OFFSET},
	{"MCASP_WFIFOSTS", MCASP_WFIFOSTS_OFFSET},
	{"MCASP_RFIFOCTL", MCASP_RFIFOCTL_OFFSET},
	{"MCASP_RFIFOSTS", MCASP_RFIFOSTS_OFFSET},
	{"END", 0},
};

static unsigned int dra7xx_mcasp_get_baseaddr(unsigned int instance)
{
	switch (instance) {
	case MCASP1: return MCASP1_CFG_BASEADDR;
	case MCASP2: return MCASP2_CFG_BASEADDR;
	case MCASP3: return MCASP3_CFG_BASEADDR;
	case MCASP4: return MCASP4_CFG_BASEADDR;
	case MCASP5: return MCASP5_CFG_BASEADDR;
	case MCASP6: return MCASP6_CFG_BASEADDR;
	case MCASP7: return MCASP7_CFG_BASEADDR;
	case MCASP8: return MCASP8_CFG_BASEADDR;
	default: break;
	}

	return 0;
}

static int dra7xx_mcasp_get_serializers(unsigned int instance)
{
	switch (instance) {
	case MCASP1: return 16;
	case MCASP2: return 16;
	case MCASP3: return 4;
	case MCASP4: return 4;
	case MCASP5: return 4;
	case MCASP6: return 4;
	case MCASP7: return 4;
	case MCASP8: return 4;
	default: break;
	}

	return OMAPCONF_ERR_ARG;
}

static int dra7xx_mcasp_is_clocked(unsigned int instance)
{
	unsigned int reg, val;
	int clocked;

	switch (instance) {
	case MCASP1:
		reg = DRA7XX_IPU_CM_CORE_AON_CM_IPU_MCASP1_CLKCTRL;
		break;
	case MCASP2:
		reg = DRA7XX_L4PER_CM_CORE_CM_L4PER2_MCASP2_CLKCTRL;
		break;
	case MCASP3:
		reg = DRA7XX_L4PER_CM_CORE_CM_L4PER2_MCASP3_CLKCTRL;
		break;
	case MCASP4:
		reg = DRA7XX_L4PER_CM_CORE_CM_L4PER2_MCASP4_CLKCTRL;
		break;
	case MCASP5:
		reg = DRA7XX_L4PER_CM_CORE_CM_L4PER2_MCASP5_CLKCTRL;
		break;
	case MCASP6:
		reg = DRA7XX_L4PER_CM_CORE_CM_L4PER2_MCASP6_CLKCTRL;
		break;
	case MCASP7:
		reg = DRA7XX_L4PER_CM_CORE_CM_L4PER2_MCASP7_CLKCTRL;
		break;
	case MCASP8:
		reg = DRA7XX_L4PER_CM_CORE_CM_L4PER2_MCASP8_CLKCTRL;
		break;
	default:
		return OMAPCONF_ERR_ARG;
	}

	OMAP_READREG(reg, val);

	val = (val & BITFIELD(16, 17)) >> 16;
	switch (val) {
	case 0: /* fully functional */
	case 1: /* in-transition */
	case 2: /* only OCP part */
		clocked = 1;
		break;
	case 3: /* disabled */
	default:
		clocked = 0;
		break;
	}

	return clocked;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dra7xx_mcasp_dumpregs
 * @BRIEF		dump registers from table given as argument
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		none
 * @DESCRIPTION		dump registers from table given as argument
 *//*------------------------------------------------------------------------ */
int dra7xx_mcasp_dumpregs(FILE *stream, int argc, char *argv[])
{
	unsigned int i = 0;
	unsigned int val = 0;
	int ret, err = 0;
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row;
	unsigned int instance;
	unsigned int baseaddr;
	unsigned int address;
	int serializers;
	const char* inst_arg;
	const reg_table *reg_table;

	/* argc is 1 when called from 'dump' command, 2 for legacy */
	if (argc < 1) {
		help(HELP_MCASP);
		return OMAPCONF_ERR_ARG;
	}

	CHECK_NULL_ARG(argv, OMAPCONF_ERR_ARG);

	inst_arg = argv[0];

	ret = sscanf(inst_arg, "mcasp%u", &instance);
	if (ret != 1) {
		help(HELP_MCASP);
		return OMAPCONF_ERR_ARG;
	}

	ret = dra7xx_mcasp_is_clocked(instance);
	if (ret < 0) {
		fprintf(stderr, "omapconf: %s is not a valid instance\n",
			inst_arg);
		dprintf("omapconf: no clock information for %s\n", inst_arg);
		help(HELP_MCASP);
		return OMAPCONF_ERR_ARG;
	} else if (ret == 0) {
		fprintf(stderr, "omapconf: %s is not active, cannot proceed further\n",
			inst_arg);
		return 0;
	}

	baseaddr = dra7xx_mcasp_get_baseaddr(instance);
	if (!baseaddr) {
		fprintf(stderr, "omapconf: %s is not a valid instance\n", inst_arg);
		dprintf("%s: no base address for %s\n", __func__, inst_arg);
		help(HELP_MCASP);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	serializers = dra7xx_mcasp_get_serializers(instance);
	if (serializers < 0) {
		fprintf(stderr, "omapconf: %s is not a valid instance\n", inst_arg);
		dprintf("%s: no serializers for %s\n", __func__, inst_arg);
		help(HELP_MCASP);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	dprintf("%s(): McASP%u baseaddr=0x%08x num_ser=%u\n",
		__func__, instance, baseaddr, serializers);

	autoadjust_table_init(table);
	row = 0;

	strncpy(table[row][0], "Reg. Name", TABLE_MAX_ELT_LEN);
	strncpy(table[row][1], "Reg. Addr", TABLE_MAX_ELT_LEN);
	strncpy(table[row][2], "Reg. Val.", TABLE_MAX_ELT_LEN);
	row++;

	/* Print common McASP CFG registers */
	reg_table = mcasp_cfg_reg_table;
	while (strcmp(reg_table[i].name, "END") != 0) {
		address = baseaddr + reg_table[i].addr;

		dprintf("%s(): read register 0x%08x\n", __func__, address);
		OMAP_READREG(address, val);

		/* Show register name, addr & content (hex) */
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "%s", reg_table[i].name);
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "0x%08X", address);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "0x%08X", val);
		row++;
		i++;
	}

	if (serializers == 16)
		reg_table = mcasp_cfg_16ser_reg_table;
	else
		reg_table = mcasp_cfg_4ser_reg_table;

	/* Print McASP serializer registers */
	i = 0;
	while (strcmp(reg_table[i].name, "END") != 0) {
		address = baseaddr + reg_table[i].addr;

		dprintf("%s(): read register 0x%08x\n", __func__, address);
		OMAP_READREG(address, val);

		/* Show register name, addr & content (hex) */
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "%s", reg_table[i].name);
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "0x%08X", address);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "0x%08X", val);
		row++;
		i++;
	}

	/* Print McASP AFIFO registers */
	reg_table = mcasp_afifo_reg_table;
	i = 0;
	while (strcmp(reg_table[i].name, "END") != 0) {
		address = baseaddr + reg_table[i].addr;

		dprintf("%s(): read register 0x%08x\n", __func__, address);
		OMAP_READREG(address, val);

		/* Show register name, addr & content (hex) */
		snprintf(table[row][0], TABLE_MAX_ELT_LEN, "%s", reg_table[i].name);
		snprintf(table[row][1], TABLE_MAX_ELT_LEN, "0x%08X", address);
		snprintf(table[row][2], TABLE_MAX_ELT_LEN, "0x%08X", val);
		row++;
		i++;
	}

	autoadjust_table_fprint(stream, table, row, 3);

	return err;
}

static int dra7xx_mcasp_data(struct mcasp_regs *regs, FILE *stream)
{
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row;
	unsigned int val;
	unsigned int serializers;
	int i;

	autoadjust_table_init(table);
	row = 0;

	SET_TABLE_TITLE(table, "Data Ports and Buffers");
	row++;

	SET_TABLE_PARAM(table, "Port");
	if (MCASP_BITFIELD(regs->txfmt, 0x8))
		SET_TABLE_VALUE(table, "CFG bus");
	else
		SET_TABLE_VALUE(table, "DATA bus");
	row++;

	/* Transmit DMA */
	SET_TABLE_PARAM(table, "Transmit DMA");
	row++;

	SET_TABLE_PARAM(table, "  DMA request");
	if (MCASP_BITFIELD(regs->xevtctl, 0x1))
		SET_TABLE_VALUE(table, "Disabled");
	else
		SET_TABLE_VALUE(table, "Enabled");
	row++;

	SET_TABLE_PARAM(table, "  Status");
	if (MCASP_BITFIELD(regs->txstat, 0x80))
		SET_TABLE_VALUE(table, "Unexpected DMA/CPU data writes");
	else
		SET_TABLE_VALUE(table, "No error");
	row++;

	/* Receive DMA */
	SET_TABLE_PARAM(table, "Receive DMA");
	row++;

	SET_TABLE_PARAM(table, "  DMA request");
	if (MCASP_BITFIELD(regs->revtctl, 0x1))
		SET_TABLE_VALUE(table, "Disabled");
	else
		SET_TABLE_VALUE(table, "Enabled");
	row++;

	SET_TABLE_PARAM(table, "  Status");
	if (MCASP_BITFIELD(regs->rxstat, 0x80))
		SET_TABLE_VALUE(table, "Unexpected DMA/CPU data reads");
	else
		SET_TABLE_VALUE(table, "No error");
	row++;

	/* Transmit Buffer */
	SET_TABLE_PARAM(table, "Transmit Buffer (XBUF)");
	row++;

	SET_TABLE_PARAM(table, "  Status");
	if (MCASP_BITFIELD(regs->txstat, 0x1))
		SET_TABLE_VALUE(table, "Underrun occurred");
	else
		SET_TABLE_VALUE(table, "No error");
	row++;

	/* Receive Buffer */
	SET_TABLE_PARAM(table, "Receive Buffer (RBUF)");
	row++;

	SET_TABLE_PARAM(table, "  Status");
	if (MCASP_BITFIELD(regs->rxstat, 0x1))
		SET_TABLE_VALUE(table, "Overrun occurred");
	else
		SET_TABLE_VALUE(table, "No error");
	row++;

	/* Number of serializers used as transmitters */
	serializers = 0;
	for (i = 0; i < regs->num_serializers; i++) {
		if (MCASP_BITFIELD(regs->xrsrctl[i], 0x03) == 1)
			serializers++;
	}

	/* Write FIFO */
	SET_TABLE_PARAM(table, "Write FIFO (WFIFO)");
	row++;

	SET_TABLE_PARAM(table, "  State");
	if (MCASP_BITFIELD(regs->wfifoctl, 0x10000)) {
		val = MCASP_BITFIELD(regs->wfifoctl, 0xFF);
		if (serializers == val)
			SET_TABLE_VALUE(table, "Enabled");
		else
			SET_TABLE_VALUE(table,
				"Enabled but invalid WNUMDMA (%u), expected %u",
				val, serializers);
	} else {
		SET_TABLE_VALUE(table, "Disabled");
	}
	row++;

	SET_TABLE_PARAM(table, "  Threshold");
	SET_TABLE_VALUE(table, "%u samples", MCASP_BITFIELD(regs->wfifoctl, 0xFF00));
	row++;

	SET_TABLE_PARAM(table, "  Level");
	val = MCASP_BITFIELD(regs->wfifosts, 0xFF);
	if (val <= 64)
		SET_TABLE_VALUE(table, "%u samples in FIFO", val);
	else
		SET_TABLE_VALUE(table, "INVALID");
	row++;

	/* Number of serializers used as receivers */
	serializers = 0;
	for (i = 0; i < regs->num_serializers; i++) {
		if (MCASP_BITFIELD(regs->xrsrctl[i], 0x03) == 2)
			serializers++;
	}

	/* Read FIFO */
	SET_TABLE_PARAM(table, "Read FIFO (RFIFO)");
	row++;

	SET_TABLE_PARAM(table, "  State");
	if (MCASP_BITFIELD(regs->rfifoctl, 0x10000)) {
		val = MCASP_BITFIELD(regs->rfifoctl, 0xFF);
		if (serializers == val)
			SET_TABLE_VALUE(table, "Enabled");
		else
			SET_TABLE_VALUE(table,
				"Enabled but invalid RNUMDMA (%u), expected %u",
				val, serializers);
	} else {
		SET_TABLE_VALUE(table, "Disabled");
	}
	row++;

	SET_TABLE_PARAM(table, "  Threshold");
	SET_TABLE_VALUE(table, "%u samples", MCASP_BITFIELD(regs->rfifoctl, 0xFF00));
	row++;

	SET_TABLE_PARAM(table, "  Level");
	val = MCASP_BITFIELD(regs->rfifosts, 0xFF);
	if (val <= 64)
		SET_TABLE_VALUE(table, "%u samples in FIFO", val);
	else
		SET_TABLE_VALUE(table, "INVALID");
	row++;

	autoadjust_table_generic_fprint(stream, table, row, 2, TABLE_HAS_TITLE);

	return 0;
}

static int dra7xx_mcasp_control(struct mcasp_regs *regs, FILE *stream)
{
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row;
	unsigned int val;
	unsigned int active;

	autoadjust_table_init(table);
	row = 0;

	SET_TABLE_TITLE(table, "Control");
	row++;

	/* Transmit State-Machine */
	active = !!MCASP_BITFIELD(regs->gblctl, 0x800);

	SET_TABLE_PARAM(table, "Transmit State-Machine");
	row++;

	SET_TABLE_PARAM(table, "  State");
	if (active)
		SET_TABLE_VALUE(table, "Active");
	else
		SET_TABLE_VALUE(table, "Held in reset");
	row++;

	/* Transmit Sequencer */
	SET_TABLE_PARAM(table, "Transmit Sequencer");
	row++;

	SET_TABLE_PARAM(table, "  Enabled Slots");
	val = MCASP_BITFIELD(regs->txfmctl, 0xff80);
	if (((val >= 2) && (val <= 32)) || (val == 384))
		SET_TABLE_VALUE(table, "%u", val);
	else
		SET_TABLE_VALUE(table, "INVALID");
	row++;

	SET_TABLE_PARAM(table, "  Active Slots");
	SET_TABLE_VALUE(table, "%u", __builtin_popcount(regs->txtdm.value));
	row++;

	SET_TABLE_PARAM(table, "  Active Slots Mask");
	SET_TABLE_VALUE(table, "0x%08X", regs->txtdm.value);
	row++;

	SET_TABLE_PARAM(table, "  Current Slot");
	if (active)
		SET_TABLE_VALUE(table, "%u", MCASP_BITFIELD(regs->txtdmslot, 0x1FF));
	else
		SET_TABLE_VALUE(table, "Inactive");
	row++;


	/* Receive State-Machine */
	active = !!MCASP_BITFIELD(regs->gblctl, 0x08);

	SET_TABLE_PARAM(table, "Receive State-Machine");
	row++;

	SET_TABLE_PARAM(table, "  State");
	if (active)
		SET_TABLE_VALUE(table, "Active");
	else
		SET_TABLE_VALUE(table, "Held in reset");
	row++;

	/* Receive Sequencer */
	SET_TABLE_PARAM(table, "Receive Sequencer");
	row++;

	SET_TABLE_PARAM(table, "  Enabled Slots");
	val = MCASP_BITFIELD(regs->rxfmctl, 0xff80);
	if (((val >= 2) && (val <= 32)) || (val == 384))
		SET_TABLE_VALUE(table, "%u", val);
	else
		SET_TABLE_VALUE(table, "INVALID");
	row++;

	SET_TABLE_PARAM(table, "  Active Slots");
	SET_TABLE_VALUE(table, "%u", __builtin_popcount(regs->rxtdm.value));
	row++;

	SET_TABLE_PARAM(table, "  Active Slots Mask");
	SET_TABLE_VALUE(table, "0x%08X", regs->rxtdm.value);
	row++;

	SET_TABLE_PARAM(table, "  Current Slot");
	if (active)
		SET_TABLE_VALUE(table, "%u", MCASP_BITFIELD(regs->rxtdmslot, 0x1FF));
	else
		SET_TABLE_VALUE(table, "Inactive");
	row++;

	autoadjust_table_generic_fprint(stream, table, row, 2, TABLE_HAS_TITLE);

	return 0;
}

static int dra7xx_mcasp_clocking(struct mcasp_regs *regs, FILE *stream)
{
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row;
	unsigned int val;

	autoadjust_table_init(table);
	row = 0;

	SET_TABLE_TITLE(table, "Clocks");
	row++;

	/* Transmit Bit Clock */
	SET_TABLE_PARAM(table, "Transmit Bit Clock");
	row++;

	SET_TABLE_PARAM(table, "  State");
	if (MCASP_BITFIELD(regs->gblctl, 0x100))
		SET_TABLE_VALUE(table, "Running");
	else
		SET_TABLE_VALUE(table, "Held in reset");
	row++;

	SET_TABLE_PARAM(table, "  Divider");
	SET_TABLE_VALUE(table, "Divide-by %u",
			MCASP_BITFIELD(regs->aclkxctl, 0x1F) + 1);
	row++;

	SET_TABLE_PARAM(table, "  Source");
	if (MCASP_BITFIELD(regs->aclkxctl, 0x20))
		SET_TABLE_VALUE(table, "Internal");
	else
		SET_TABLE_VALUE(table, "External (ACLKX pin)");
	row++;

	SET_TABLE_PARAM(table, "  Polarity");
	if (MCASP_BITFIELD(regs->aclkxctl, 0x80))
		SET_TABLE_VALUE(table, "Driven on falling edge");
	else
		SET_TABLE_VALUE(table, "Driven on rising edge");
	row++;

	/* Transmit High-Speed Clock */
	SET_TABLE_PARAM(table, "Transmit High-Speed Clock");
	row++;

	SET_TABLE_PARAM(table, "  State");
	if (MCASP_BITFIELD(regs->gblctl, 0x200))
		SET_TABLE_VALUE(table, "Running");
	else
		SET_TABLE_VALUE(table, "Held in reset");
	row++;

	SET_TABLE_PARAM(table, "  Divider");
	SET_TABLE_VALUE(table, "Divide-by %u",
			MCASP_BITFIELD(regs->ahclkxctl, 0xFFF) + 1);
	row++;

	SET_TABLE_PARAM(table, "  Source");
	if (MCASP_BITFIELD(regs->ahclkxctl, 0x8000))
		SET_TABLE_VALUE(table, "Internal (AUXCLK)");
	else
		SET_TABLE_VALUE(table, "External (AHCLKX pin)");
	row++;

	SET_TABLE_PARAM(table, "  Polarity");
	if (MCASP_BITFIELD(regs->ahclkxctl, 0x4000))
		SET_TABLE_VALUE(table, "Inverted");
	else
		SET_TABLE_VALUE(table, "Non-inverted");
	row++;

	/* Receive Bit Clock */
	SET_TABLE_PARAM(table, "Receive Bit Clock");
	row++;

	SET_TABLE_PARAM(table, "  State");
	if (MCASP_BITFIELD(regs->gblctl, 0x01))
		SET_TABLE_VALUE(table, "Running");
	else
		SET_TABLE_VALUE(table, "Held in reset");
	row++;

	SET_TABLE_PARAM(table, "  Divider");
	SET_TABLE_VALUE(table, "Divide-by %u",
			MCASP_BITFIELD(regs->aclkrctl, 0x1F) + 1);
	row++;

	SET_TABLE_PARAM(table, "  Source");
	if (MCASP_BITFIELD(regs->aclkrctl, 0x20))
		SET_TABLE_VALUE(table, "Internal");
	else
		SET_TABLE_VALUE(table, "External (ACLKR pin)");
	row++;

	SET_TABLE_PARAM(table, "  Polarity");
	if (MCASP_BITFIELD(regs->aclkrctl, 0x80))
		SET_TABLE_VALUE(table, "Samples on rising edge");
	else
		SET_TABLE_VALUE(table, "Samples on falling edge");
	row++;

	/* Receive High-Speed Clock. Available only in McASP1 and McASP2 */
	if (regs->num_serializers == 16) {
		SET_TABLE_PARAM(table, "Receive High-Speed Clock");
		row++;

		SET_TABLE_PARAM(table, "  State");
		if (MCASP_BITFIELD(regs->gblctl, 0x02))
			SET_TABLE_VALUE(table, "Running");
		else
			SET_TABLE_VALUE(table, "Held in reset");
		row++;

		SET_TABLE_PARAM(table, "  Divider");
		SET_TABLE_VALUE(table, "Divide-by %u",
				MCASP_BITFIELD(regs->ahclkrctl, 0xFFF) + 1);
		row++;

		SET_TABLE_PARAM(table, "  Source");
		if (MCASP_BITFIELD(regs->ahclkrctl, 0x8000))
			SET_TABLE_VALUE(table, "Internal (AUXCLK)");
		else
			SET_TABLE_VALUE(table, "External (AHCLKR pin)");
		row++;

		SET_TABLE_PARAM(table, "  Polarity");
		if (MCASP_BITFIELD(regs->ahclkrctl, 0x4000))
			SET_TABLE_VALUE(table, "Inverted");
		else
			SET_TABLE_VALUE(table, "Non-inverted");
		row++;
	}

	SET_TABLE_PARAM(table, "Sync Mode");
	if (MCASP_BITFIELD(regs->aclkrctl, 0x40))
		SET_TABLE_VALUE(table, "Asynchronous");
	else
		SET_TABLE_VALUE(table, "Synchronous to TX");
	row++;

	SET_TABLE_PARAM(table, "Idle Mode");
	val = MCASP_BITFIELD(regs->pwridlesysconfig, 0x03);
	switch (val) {
	case 0:
		SET_TABLE_VALUE(table, "Force-idle");
		break;
	case 1:
		SET_TABLE_VALUE(table, "No-idle");
		break;
	case 2:
		SET_TABLE_VALUE(table, "Smart-idle");
		break;
	default:
		SET_TABLE_VALUE(table, "INVALID");
		break;
	}
	row++;

	autoadjust_table_generic_fprint(stream, table, row, 2, TABLE_HAS_TITLE);

	return 0;
}

static int dra7xx_mcasp_frame_sync(struct mcasp_regs *regs, FILE *stream)
{
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row;
	unsigned int val;

	autoadjust_table_init(table);
	row = 0;

	SET_TABLE_TITLE(table, "Frame Sync Generator");
	row++;

	/* Transmit frame sync generator */
	SET_TABLE_PARAM(table, "Transmit Frame Sync");
	row++;

	SET_TABLE_PARAM(table, "  Generator State");
	if (MCASP_BITFIELD(regs->gblctl, 0x1000))
		SET_TABLE_VALUE(table, "Active");
	else
		SET_TABLE_VALUE(table, "Held in reset");
	row++;

	SET_TABLE_PARAM(table, "  Source");
	if (MCASP_BITFIELD(regs->txfmctl, 0x02))
		SET_TABLE_VALUE(table, "Internal");
	else
		SET_TABLE_VALUE(table, "External");
	row++;

	SET_TABLE_PARAM(table, "  Polarity");
	if (MCASP_BITFIELD(regs->txfmctl, 0x01))
		SET_TABLE_VALUE(table, "Frame starts on falling edge");
	else
		SET_TABLE_VALUE(table, "Frame starts on rising edge");
	row++;

	SET_TABLE_PARAM(table, "  Pulse Width");
	if (MCASP_BITFIELD(regs->txfmctl, 0x10))
		SET_TABLE_VALUE(table, "Single word");
	else
		SET_TABLE_VALUE(table, "Single bit");
	row++;

	SET_TABLE_PARAM(table, "  Slot Count");
	val = MCASP_BITFIELD(regs->txfmctl, 0xff80);
	if ((val >= 2) && (val <= 32))
		SET_TABLE_VALUE(table, "%u (TDM)", val);
	else if (val == 384)
		SET_TABLE_VALUE(table, "%u (DIT)", val);
	else
		SET_TABLE_VALUE(table, "INVALID");
	row++;

	SET_TABLE_PARAM(table, "  Data Delay");
	val = MCASP_BITFIELD(regs->txfmt, 0x30000);
	switch (val) {
	case 0:
	case 1:
	case 2:
		SET_TABLE_VALUE(table, "%u-bit", val);
		break;
	default:
		SET_TABLE_VALUE(table, "INVALID");
		break;
	}
	row++;

	SET_TABLE_PARAM(table, "  Status");
	if (MCASP_BITFIELD(regs->txstat, 0x02))
		SET_TABLE_VALUE(table, "Unexpected frame sync");
	else
		SET_TABLE_VALUE(table, "No error");
	row++;

	/* Receive frame sync generator */
	SET_TABLE_PARAM(table, "Receive Frame Sync");
	row++;

	SET_TABLE_PARAM(table, "  Generator State");
	if (MCASP_BITFIELD(regs->gblctl, 0x10))
		SET_TABLE_VALUE(table, "Active");
	else
		SET_TABLE_VALUE(table, "Held in reset");
	row++;

	SET_TABLE_PARAM(table, "  Source");
	if (MCASP_BITFIELD(regs->rxfmctl, 0x02))
		SET_TABLE_VALUE(table, "Internal");
	else
		SET_TABLE_VALUE(table, "External");
	row++;

	SET_TABLE_PARAM(table, "  Polarity");
	if (MCASP_BITFIELD(regs->rxfmctl, 0x01))
		SET_TABLE_VALUE(table, "Frame starts on falling edge");
	else
		SET_TABLE_VALUE(table, "Frame starts on rising edge");
	row++;

	SET_TABLE_PARAM(table, "  Pulse Width");
	if (MCASP_BITFIELD(regs->rxfmctl, 0x10))
		SET_TABLE_VALUE(table, "Single word");
	else
		SET_TABLE_VALUE(table, "Single bit");
	row++;

	SET_TABLE_PARAM(table, "  Slot Count");
	val = MCASP_BITFIELD(regs->rxfmctl, 0xff80);
	if ((val >= 2) && (val <= 32))
		SET_TABLE_VALUE(table, "%u (TDM)", val);
	else if (val == 384)
		SET_TABLE_VALUE(table, "%u (DIT)", val);
	else
		SET_TABLE_VALUE(table, "INVALID");
	row++;

	SET_TABLE_PARAM(table, "  Data Delay");
	val = MCASP_BITFIELD(regs->rxfmt, 0x30000);
	switch (val) {
	case 0:
	case 1:
	case 2:
		SET_TABLE_VALUE(table, "%u-bit", val);
		break;
	default:
		SET_TABLE_VALUE(table, "INVALID");
		break;
	}
	row++;

	SET_TABLE_PARAM(table, "  Status");
	if (MCASP_BITFIELD(regs->rxstat, 0x02))
		SET_TABLE_VALUE(table, "Unexpected frame sync");
	else
		SET_TABLE_VALUE(table, "No error");
	row++;


	SET_TABLE_PARAM(table, "Sync Mode");
	if (MCASP_BITFIELD(regs->aclkrctl, 0x40))
		SET_TABLE_VALUE(table, "Asynchronous");
	else
		SET_TABLE_VALUE(table, "Synchronous to TX");
	row++;

	autoadjust_table_generic_fprint(stream, table, row, 2, TABLE_HAS_TITLE);

	return 0;
}

static int dra7xx_mcasp_format_units(struct mcasp_regs *regs, FILE *stream)
{
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row;
	unsigned int val;

	autoadjust_table_init(table);
	row = 0;

	SET_TABLE_TITLE(table, "Format Units");
	row++;

	/* Transmit format unit */
	SET_TABLE_PARAM(table, "Transmit Format Unit");
	row++;

	SET_TABLE_PARAM(table, "  Slot Size");
	val = MCASP_BITFIELD(regs->txfmt, 0xf0);
	switch (val) {
	case 0x3:
	case 0x5:
	case 0x7:
	case 0x9:
	case 0xb:
	case 0xd:
	case 0xf:
		SET_TABLE_VALUE(table, "%u bits", (val + 1) * 2);
		break;
	default:
		SET_TABLE_VALUE(table, "INVALID");
		break;
	}
	row++;

	SET_TABLE_PARAM(table, "  Bit Mask");
	SET_TABLE_VALUE(table, "0x%08X", regs->txmask.value);
	row++;

	SET_TABLE_PARAM(table, "  Padding");
	val = MCASP_BITFIELD(regs->txfmt, 0x600);
	switch (val) {
	case 0:
		SET_TABLE_VALUE(table, "Pad with 0");
		break;
	case 1:
		SET_TABLE_VALUE(table, "Pad with 1");
		break;
	case 2:
		SET_TABLE_VALUE(table, "Pad with XBUF bit %u value",
				MCASP_BITFIELD(regs->txfmt, 0x1f00));
		break;
	default:
		SET_TABLE_VALUE(table, "INVALID");
		break;
	}
	row++;

	SET_TABLE_PARAM(table, "  Right-Rotation");
	SET_TABLE_VALUE(table, "%u bit positions",
			MCASP_BITFIELD(regs->txfmt, 0x7) * 4);
	row++;

	SET_TABLE_PARAM(table, "  Bitstream Order");
	if (MCASP_BITFIELD(regs->txfmt, 0x8000))
		SET_TABLE_VALUE(table, "MSB first");
	else
		SET_TABLE_VALUE(table, "LSB first");
	row++;

	/* Receive format unit */
	SET_TABLE_PARAM(table, "Receive Format Unit");
	row++;

	SET_TABLE_PARAM(table, "  Slot Size");
	val = MCASP_BITFIELD(regs->rxfmt, 0xf0);
	switch (val) {
	case 0x3:
	case 0x5:
	case 0x7:
	case 0x9:
	case 0xb:
	case 0xd:
	case 0xf:
		SET_TABLE_VALUE(table, "%u bits", (val + 1) * 2);
		break;
	default:
		SET_TABLE_VALUE(table, "INVALID");
		break;
	}
	row++;

	SET_TABLE_PARAM(table, "  Bit Mask");
	SET_TABLE_VALUE(table, "0x%08X", regs->rxmask.value);
	row++;

	SET_TABLE_PARAM(table, "  Padding");
	val = MCASP_BITFIELD(regs->rxfmt, 0x600);
	switch (val) {
	case 0:
		SET_TABLE_VALUE(table, "Pad with 0");
		break;
	case 1:
		SET_TABLE_VALUE(table, "Pad with 1");
		break;
	case 2:
		SET_TABLE_VALUE(table, "Pad with RBUF bit %u value",
				MCASP_BITFIELD(regs->rxfmt, 0x1f00));
		break;
	default:
		SET_TABLE_VALUE(table, "INVALID");
		break;
	}
	row++;

	SET_TABLE_PARAM(table, "  Right-Rotation");
	SET_TABLE_VALUE(table, "%u bit positions",
			MCASP_BITFIELD(regs->rxfmt, 0x7) * 4);
	row++;

	SET_TABLE_PARAM(table, "  Bitstream Order");
	if (MCASP_BITFIELD(regs->rxfmt, 0x8000))
		SET_TABLE_VALUE(table, "MSB first");
	else
		SET_TABLE_VALUE(table, "LSB first");
	row++;

	autoadjust_table_generic_fprint(stream, table, row, 2, TABLE_HAS_TITLE);

	return 0;
}

static int dra7xx_mcasp_serializers(struct mcasp_regs *regs, FILE *stream)
{
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row;
	int i;

	autoadjust_table_init(table);
	row = 0;

	SET_TABLE_TITLE(table, "Serializers");
	row++;

	/* Transmit Serializers */
	SET_TABLE_PARAM(table, "Transmit Serializers");
	if (MCASP_BITFIELD(regs->gblctl, 0x400))
		SET_TABLE_VALUE(table, "Active");
	else
		SET_TABLE_VALUE(table, "Cleared");
	row++;

	/* Receive Serializers */
	SET_TABLE_PARAM(table, "Receive Serializers");
	if (MCASP_BITFIELD(regs->gblctl, 0x04))
		SET_TABLE_VALUE(table, "Active");
	else
		SET_TABLE_VALUE(table, "Cleared");
	row++;

	/* Serializers */
	for (i = 0; i < regs->num_serializers; i++) {
		SET_TABLE_PARAM(table, "Serializer %u", i);
		row++;

		SET_TABLE_PARAM(table, "  Mode");
		switch (MCASP_BITFIELD(regs->xrsrctl[i], 0x03)) {
		case 0:
			SET_TABLE_VALUE(table, "Inactive");
			break;
		case 1:
			SET_TABLE_VALUE(table, "Transmit");
			break;
		case 2:
			SET_TABLE_VALUE(table, "Receive");
			break;
		default:
			SET_TABLE_VALUE(table, "INVALID");
			break;
		}
		row++;

		SET_TABLE_PARAM(table, "  Inactive State");
		switch (MCASP_BITFIELD(regs->xrsrctl[i], 0x0c)) {
		case 0:
			SET_TABLE_VALUE(table, "Hi-Z");
			break;
		case 2:
			SET_TABLE_VALUE(table, "Logic Low");
			break;
		case 3:
			SET_TABLE_VALUE(table, "Logic High");
			break;
		default:
			SET_TABLE_VALUE(table, "INVALID");
			break;
		}
		row++;
	}

	autoadjust_table_generic_fprint(stream, table, row, 2, TABLE_HAS_TITLE);

	return 0;
}

static int dra7xx_mcasp_pin(const char *pin_name, const char *mcasp_name,
		struct mcasp_regs *regs, unsigned int bit,
		char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN],
		unsigned int row)
{
	unsigned int mask = 1 << bit;
	unsigned int is_gpio;
	unsigned int is_output;

	SET_TABLE_PARAM(table, "%s", pin_name);
	row++;

	is_gpio = !!MCASP_BITFIELD(regs->pfunc, mask);
	is_output = !!MCASP_BITFIELD(regs->pdir, mask);

	SET_TABLE_PARAM(table, "  Functionality");
	SET_TABLE_VALUE(table, "%s", is_gpio ?  "GPIO" : mcasp_name);
	row++;

	SET_TABLE_PARAM(table, "  Direction");
	SET_TABLE_VALUE(table, is_output ? "Output" : "Input");
	row++;

	if (is_gpio) {
		SET_TABLE_PARAM(table, "  Value");
		if (is_output) {
			if (MCASP_BITFIELD(regs->pdout, mask))
				SET_TABLE_VALUE(table, "High");
			else
				SET_TABLE_VALUE(table, "Low");
		} else {
			if (MCASP_BITFIELD(regs->pdin, mask))
				SET_TABLE_VALUE(table, "High");
			else
				SET_TABLE_VALUE(table, "Low");
		}
		row++;
	}

	return row;
}

static int dra7xx_mcasp_pinctrl(struct mcasp_regs *regs, FILE *stream)
{
	char table[TABLE_MAX_ROW][TABLE_MAX_COL][TABLE_MAX_ELT_LEN];
	unsigned int row;
	char pin_name[10];
	char mcasp_name[40];
	int i;

	autoadjust_table_init(table);
	row = 0;

	SET_TABLE_TITLE(table, "Pin Control");
	row++;

	row = dra7xx_mcasp_pin("AFSR", "Receive Frame Sync",
			       regs, 31, table, row);

	row = dra7xx_mcasp_pin("ACLKR", "Receive Bit Clock",
			       regs, 29, table, row);

	row = dra7xx_mcasp_pin("AFSX", "Transmit Frame Sync",
			       regs, 28, table, row);

	row = dra7xx_mcasp_pin("ACLKX", "Transmit Bit Clock",
			       regs, 26, table, row);

	row = dra7xx_mcasp_pin("AHCLKX", "Transmit High-Freq Clock",
			       regs, 27, table, row);

	for (i = 0; i < regs->num_serializers; i++) {
		snprintf(pin_name, sizeof(pin_name), "AXR%u", i);
		snprintf(mcasp_name, sizeof(mcasp_name),
			 "TX/RX Data Channel %u", i);

		row = dra7xx_mcasp_pin(pin_name, mcasp_name,
				       regs, i, table, row);
	}

	autoadjust_table_generic_fprint(stream, table, row, 2, TABLE_HAS_TITLE);

	return 0;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dra7xx_mcasp_show
 * @BRIEF		analyze McASP configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_UNEXPECTED
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		stream: output stream
 * @DESCRIPTION		analyze McASP configuration
 *//*------------------------------------------------------------------------ */
int dra7xx_mcasp_show(FILE *stream, int argc, char *argv[])
{
	struct mcasp_regs *regs = &mcasp_regs;
	unsigned int baseaddr = MCASP3_CFG_BASEADDR;
	unsigned int instance;
	const char* inst_arg;
	int serializers;
	int i;
	int ret;

	if (argc < 1) {
		help(HELP_MCASP);
		return OMAPCONF_ERR_ARG;
	}

	CHECK_NULL_ARG(argv, OMAPCONF_ERR_ARG);

	inst_arg = argv[0];

	ret = sscanf(inst_arg, "mcasp%u", &instance);
	if (ret != 1) {
		help(HELP_MCASP);
		return OMAPCONF_ERR_ARG;
	}

	ret = dra7xx_mcasp_is_clocked(instance);
	if (ret < 0) {
		fprintf(stderr, "omapconf: %s is not a valid instance\n",
			inst_arg);
		dprintf("omapconf: no clock information for %s\n", inst_arg);
		help(HELP_MCASP);
		return OMAPCONF_ERR_ARG;
	} else if (ret == 0) {
		fprintf(stderr, "omapconf: %s is not active, cannot proceed further\n",
			inst_arg);
		return 0;
	}

	baseaddr = dra7xx_mcasp_get_baseaddr(instance);
	if (!baseaddr) {
		fprintf(stderr, "omapconf: %s is not a valid instance\n",
			inst_arg);
		dprintf("omapconf: no base address for %s\n", inst_arg);
		help(HELP_MCASP);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	serializers = dra7xx_mcasp_get_serializers(instance);
	if (serializers < 0) {
		fprintf(stderr, "omapconf: %s is not a valid instance\n",
			inst_arg);
		dprintf("omapconf: no serializers for %s\n", inst_arg);
		help(HELP_MCASP);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	dprintf("%s(): McASP%u baseaddr=0x%08x num_ser=%u\n",
		__func__, instance, baseaddr, serializers);

	regs->num_serializers = serializers;

	MCASP_READREG(baseaddr, regs->pwridlesysconfig);
	MCASP_READREG(baseaddr, regs->pfunc);
	MCASP_READREG(baseaddr, regs->pdir);
	MCASP_READREG(baseaddr, regs->pdout);
	MCASP_READREG(baseaddr, regs->pdin);
	MCASP_READREG(baseaddr, regs->gblctl);
	MCASP_READREG(baseaddr, regs->rxmask);
	MCASP_READREG(baseaddr, regs->rxfmt);
	MCASP_READREG(baseaddr, regs->rxfmctl);
	MCASP_READREG(baseaddr, regs->aclkrctl);
	MCASP_READREG(baseaddr, regs->ahclkrctl);
	MCASP_READREG(baseaddr, regs->rxtdm);
	MCASP_READREG(baseaddr, regs->evtctlr);
	MCASP_READREG(baseaddr, regs->rxstat);
	MCASP_READREG(baseaddr, regs->rxtdmslot);
	MCASP_READREG(baseaddr, regs->revtctl);
	MCASP_READREG(baseaddr, regs->txmask);
	MCASP_READREG(baseaddr, regs->txfmt);
	MCASP_READREG(baseaddr, regs->txfmctl);
	MCASP_READREG(baseaddr, regs->aclkxctl);
	MCASP_READREG(baseaddr, regs->ahclkxctl);
	MCASP_READREG(baseaddr, regs->txtdm);
	MCASP_READREG(baseaddr, regs->evtctlx);
	MCASP_READREG(baseaddr, regs->txstat);
	MCASP_READREG(baseaddr, regs->txtdmslot);
	MCASP_READREG(baseaddr, regs->xevtctl);
	MCASP_READREG(baseaddr, regs->wfifoctl);
	MCASP_READREG(baseaddr, regs->wfifosts);
	MCASP_READREG(baseaddr, regs->rfifoctl);
	MCASP_READREG(baseaddr, regs->rfifosts);
	for (i = 0; i < regs->num_serializers; i++)
		MCASP_READREG(baseaddr, regs->xrsrctl[i]);

	dra7xx_mcasp_data(regs, stream);
	dra7xx_mcasp_control(regs, stream);
	dra7xx_mcasp_clocking(regs, stream);
	dra7xx_mcasp_frame_sync(regs, stream);
	dra7xx_mcasp_format_units(regs, stream);
	dra7xx_mcasp_serializers(regs, stream);
	dra7xx_mcasp_pinctrl(regs, stream);

	return 0;
}

/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dra7xx_mcasp_main
 * @BRIEF		main entry point
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 * @param[in]		argv: shell input argument(s)
 * @DESCRIPTION		main entry point
 *//*------------------------------------------------------------------------ */
int dra7xx_mcasp_main(int argc, char *argv[])
{
	int ret;

	if (argc == 2) {
		if (strcmp(argv[1], "dump") == 0) {
			ret = dra7xx_mcasp_dumpregs(stdout, argc, argv);
		} else if (strcmp(argv[1], "show") == 0) {
			ret = dra7xx_mcasp_show(stdout, argc, argv);
		} else {
			help(HELP_MCASP);
			ret = OMAPCONF_ERR_ARG;
		}
	} else {
		help(HELP_MCASP);
		ret = OMAPCONF_ERR_ARG;
	}

	return ret;
}
