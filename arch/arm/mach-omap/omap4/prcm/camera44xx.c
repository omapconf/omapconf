/* ======================================================================= *//**
 * @Component			OMAPCONF
 * @Filename			camera44xx.c
 * @Description			OMAP4 Camera Configuration
 * @Author			Sergio Aguirre (saaguirre@ti.com)
 * @Author			Edward Lee (edward.lee@ti.com)
 * @Date			2012
 * @Copyright			TEXAS INSTRUMENTS Incorporated
 *//*======================================================================== */
/*
 * camera44xx.c
 *
 * OMAP Power Configuration Tool ("omapconf")
 *  OMAP4 Camera Configuration
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 *
 * Written by Sergio Aguirre (saaguirre@ti.com)
 *	      Edward Lee     (edward.lee@ti.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA.
 */


#include <camera44xx.h>
#include <camera-regbits-44xx.h>
#include <lib44xx.h>
#include <help.h>
#include <lib.h>
#include <mem.h>
#include <cpuinfo.h>
#include <string.h>
#include <cm44xx.h>

/* +1 is for the END element */
#define ISS_HL_REG_TABLE_SIZE		(24 + 1)
#define ISS_CSI2_REG_TABLE_SIZE		(73 + 1)
#define ISS_CSIPHY_REG_TABLE_SIZE	(3 + 1)
#define ISS_CCP2_REG_TABLE_SIZE		(64 + 1)

typedef enum {
	FDIF_FCLK,
	CAM_PHY_CTRL_CLK,
	ISS_CLK,
	OPTFCLKEN_CTRLCLK,
	ISS_SUBCLK_SIMCOP,
	ISS_SUBCLK_ISP,
	ISS_SUBCLK_CSI2A,
	ISS_SUBCLK_CSI2B,
	ISS_SUBCLK_CCP2,
	ISS_SUBCLK_VPORT0,
	ISS_SUBCLK_VPORT1,
	ISS_SUBCLK_VPORT2,
	CAMERA44XX_CLOCK_ID_MAX
} camera44xx_clock_id;

reg_table iss_hl_reg_table[ISS_HL_REG_TABLE_SIZE];
reg_table iss_csi2_reg_table[2][ISS_CSI2_REG_TABLE_SIZE];
reg_table iss_csiphy_reg_table[2][ISS_CSIPHY_REG_TABLE_SIZE];
reg_table iss_ccp2_reg_table[ISS_CCP2_REG_TABLE_SIZE];

static unsigned int init_done = 0;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		camera44xx_init_regtable
 * @BRIEF		initialize regtable
 * @DESCRIPTION		initialize regtable
 *//*------------------------------------------------------------------------ */
void camera44xx_init_regtable(void)
{
	int i = 0, j = 0, k = 0;

	/* Init ISS HL registers table */
	strcpy(iss_hl_reg_table[i].name, "ISS_HL_REVISION");
	iss_hl_reg_table[i++].addr = ISS_HL_REVISION;
	strcpy(iss_hl_reg_table[i].name, "ISS_HL_SYSCONFIG");
	iss_hl_reg_table[i++].addr = ISS_HL_SYSCONFIG;

	for (j = 0; j < 6; j++) {
		sprintf(iss_hl_reg_table[i].name, "ISS_HL_IRQSTATUS_RAW_%d", j);
		iss_hl_reg_table[i++].addr = ISS_HL_IRQSTATUS_RAW(j);
		sprintf(iss_hl_reg_table[i].name, "ISS_HL_IRQSTATUS_%d", j);
		iss_hl_reg_table[i++].addr = ISS_HL_IRQSTATUS(j);
		sprintf(iss_hl_reg_table[i].name, "ISS_HL_IRQENABLE_SET_%d", j);
		iss_hl_reg_table[i++].addr = ISS_HL_IRQENABLE_SET(j);
	}

	strcpy(iss_hl_reg_table[i].name, "ISS_CTRL");
	iss_hl_reg_table[i++].addr = ISS_CTRL;
	strcpy(iss_hl_reg_table[i].name, "ISS_CLKCTRL");
	iss_hl_reg_table[i++].addr = ISS_CLKCTRL;
	strcpy(iss_hl_reg_table[i].name, "ISS_CLKSTAT");
	iss_hl_reg_table[i++].addr = ISS_CLKSTAT;
	strcpy(iss_hl_reg_table[i].name, "ISS_PM_STATUS");
	iss_hl_reg_table[i++].addr = ISS_PM_STATUS;
	strcpy(iss_hl_reg_table[i].name, "END");
	iss_hl_reg_table[i].addr = 0;

	for (k = 0; k < 2; k++) {
		/* Init ISS CSI2A/B registers table */
		i = 0;
		strcpy(iss_csi2_reg_table[k][i].name, "CSI2_REVISION");
		iss_csi2_reg_table[k][i++].addr = CSI2_REVISION + (k * 0x400);
		strcpy(iss_csi2_reg_table[k][i].name, "CSI2_SYSCONFIG");
		iss_csi2_reg_table[k][i++].addr = CSI2_SYSCONFIG + (k * 0x400);
		strcpy(iss_csi2_reg_table[k][i].name, "CSI2_SYSSTATUS");
		iss_csi2_reg_table[k][i++].addr = CSI2_SYSSTATUS + (k * 0x400);
		strcpy(iss_csi2_reg_table[k][i].name, "CSI2_IRQENABLE");
		iss_csi2_reg_table[k][i++].addr = CSI2_IRQENABLE + (k * 0x400);
		strcpy(iss_csi2_reg_table[k][i].name, "CSI2_CTRL");
		iss_csi2_reg_table[k][i++].addr = CSI2_CTRL + (k * 0x400);
		strcpy(iss_csi2_reg_table[k][i].name, "CSI2_COMPLEXIO_CFG");
		iss_csi2_reg_table[k][i++].addr =
			CSI2_COMPLEXIO_CFG + (k * 0x400);
		strcpy(iss_csi2_reg_table[k][i].name,
			"CSI2_COMPLEXIO_IRQSTATUS");
		iss_csi2_reg_table[k][i++].addr =
			CSI2_COMPLEXIO_IRQSTATUS + (k * 0x400);
		strcpy(iss_csi2_reg_table[k][i].name,
			"CSI2_COMPLEXIO_IRQENABLE");
		iss_csi2_reg_table[k][i++].addr =
			CSI2_COMPLEXIO_IRQENABLE + (k * 0x400);
		strcpy(iss_csi2_reg_table[k][i].name, "CSI2_TIMING");
		iss_csi2_reg_table[k][i++].addr = CSI2_TIMING + (k * 0x400);

		for (j = 0; j < 8; j++) {
			sprintf(iss_csi2_reg_table[k][i].name,
				"CSI2_CTX_CTRL1_%d", j);
			iss_csi2_reg_table[k][i++].addr =
				CSI2_CTX_CTRL1(j) + (k * 0x400);
			sprintf(iss_csi2_reg_table[k][i].name,
				"CSI2_CTX_CTRL2_%d", j);
			iss_csi2_reg_table[k][i++].addr =
				CSI2_CTX_CTRL2(j) + (k * 0x400);
			sprintf(iss_csi2_reg_table[k][i].name,
				"CSI2_CTX_DAT_OFST_%d", j);
			iss_csi2_reg_table[k][i++].addr =
				CSI2_CTX_DAT_OFST(j) + (k * 0x400);
			sprintf(iss_csi2_reg_table[k][i].name,
				"CSI2_CTX_DAT_PING_ADDR_%d", j);
			iss_csi2_reg_table[k][i++].addr =
				CSI2_CTX_DAT_PING_ADDR(j) + (k * 0x400);
			sprintf(iss_csi2_reg_table[k][i].name,
				"CSI2_CTX_DAT_PONG_ADDR_%d", j);
			iss_csi2_reg_table[k][i++].addr =
				CSI2_CTX_DAT_PONG_ADDR(j) + (k * 0x400);
			sprintf(iss_csi2_reg_table[k][i].name,
				"CSI2_CTX_IRQENABLE_%d", j);
			iss_csi2_reg_table[k][i++].addr =
				CSI2_CTX_IRQENABLE(j) + (k * 0x400);
			sprintf(iss_csi2_reg_table[k][i].name,
				"CSI2_CTX_IRQSTATUS_%d", j);
			iss_csi2_reg_table[k][i++].addr =
				CSI2_CTX_IRQSTATUS(j) + (k * 0x400);
			sprintf(iss_csi2_reg_table[k][i].name,
				"CSI2_CTX_CTRL3_%d", j);
			iss_csi2_reg_table[k][i++].addr =
				CSI2_CTX_CTRL3(j) + (k * 0x400);
		}

		strcpy(iss_csi2_reg_table[k][i].name, "END");
		iss_csi2_reg_table[k][i].addr = 0;

		/* Init ISS CSIPHY1 registers table */
		i = 0;
		strcpy(iss_csiphy_reg_table[k][i].name, "REGISTER0");
		iss_csiphy_reg_table[k][i++].addr = REGISTER0 + (k * 0x400);
		strcpy(iss_csiphy_reg_table[k][i].name, "REGISTER1");
		iss_csiphy_reg_table[k][i++].addr = REGISTER1 + (k * 0x400);
		strcpy(iss_csiphy_reg_table[k][i].name, "REGISTER2");
		iss_csiphy_reg_table[k][i++].addr = REGISTER2 + (k * 0x400);
		strcpy(iss_csiphy_reg_table[k][i].name, "END");
		iss_csiphy_reg_table[k][i].addr = 0;
	}

	/* Init ISS CCP2 registers table */
	i = 0;
	strcpy(iss_ccp2_reg_table[i].name, "CCP2_REVISION");
	iss_ccp2_reg_table[i++].addr = CCP2_REVISION;
	strcpy(iss_ccp2_reg_table[i].name, "CCP2_SYSCONFIG");
	iss_ccp2_reg_table[i++].addr = CCP2_SYSCONFIG;
	strcpy(iss_ccp2_reg_table[i].name, "CCP2_SYSSTATUS");
	iss_ccp2_reg_table[i++].addr = CCP2_SYSSTATUS;
	strcpy(iss_ccp2_reg_table[i].name, "CCP2_LC01_IRQENABLE");
	iss_ccp2_reg_table[i++].addr = CCP2_LC01_IRQENABLE;
	strcpy(iss_ccp2_reg_table[i].name, "CCP2_LC01_IRQSTATUS");
	iss_ccp2_reg_table[i++].addr = CCP2_LC01_IRQSTATUS;
	strcpy(iss_ccp2_reg_table[i].name, "CCP2_LC23_IRQENABLE");
	iss_ccp2_reg_table[i++].addr = CCP2_LC23_IRQENABLE;
	strcpy(iss_ccp2_reg_table[i].name, "CCP2_LC23_IRQSTATUS");
	iss_ccp2_reg_table[i++].addr = CCP2_LC23_IRQSTATUS;
	strcpy(iss_ccp2_reg_table[i].name, "CCP2_LCM_IRQENABLE");
	iss_ccp2_reg_table[i++].addr = CCP2_LCM_IRQENABLE;
	strcpy(iss_ccp2_reg_table[i].name, "CCP2_LCM_IRQSTATUS");
	iss_ccp2_reg_table[i++].addr = CCP2_LCM_IRQSTATUS;
	strcpy(iss_ccp2_reg_table[i].name, "CCP2_CTRL");
	iss_ccp2_reg_table[i++].addr = CCP2_CTRL;
	strcpy(iss_ccp2_reg_table[i].name, "CCP2_CTRL1");
	iss_ccp2_reg_table[i++].addr = CCP2_CTRL1;

	for (j = 0; j < 4; j++) {
		sprintf(iss_ccp2_reg_table[i].name, "CCP2_LC%d_CTRL", j);
		iss_ccp2_reg_table[i++].addr = CCP2_LCx_CTRL(j);
		sprintf(iss_ccp2_reg_table[i].name, "CCP2_LC%d_CODE", j);
		iss_ccp2_reg_table[i++].addr = CCP2_LCx_CODE(j);
		sprintf(iss_ccp2_reg_table[i].name, "CCP2_LC%d_STAT_START", j);
		iss_ccp2_reg_table[i++].addr = CCP2_LCx_STAT_START(j);
		sprintf(iss_ccp2_reg_table[i].name, "CCP2_LC%d_STAT_SIZE", j);
		iss_ccp2_reg_table[i++].addr = CCP2_LCx_STAT_SIZE(j);
		sprintf(iss_ccp2_reg_table[i].name, "CCP2_LC%d_SOF_ADDR", j);
		iss_ccp2_reg_table[i++].addr = CCP2_LCx_SOF_ADDR(j);
		sprintf(iss_ccp2_reg_table[i].name, "CCP2_LC%d_EOF_ADDR", j);
		iss_ccp2_reg_table[i++].addr = CCP2_LCx_EOF_ADDR(j);
		sprintf(iss_ccp2_reg_table[i].name, "CCP2_LC%d_DAT_START", j);
		iss_ccp2_reg_table[i++].addr = CCP2_LCx_DAT_START(j);
		sprintf(iss_ccp2_reg_table[i].name, "CCP2_LC%d_DAT_SIZE", j);
		iss_ccp2_reg_table[i++].addr = CCP2_LCx_DAT_SIZE(j);
		sprintf(iss_ccp2_reg_table[i].name,
			"CCP2_LC%d_DAT_PING_ADDR", j);
		iss_ccp2_reg_table[i++].addr = CCP2_LCx_DAT_PING_ADDR(j);
		sprintf(iss_ccp2_reg_table[i].name,
			"CCP2_LC%d_DAT_PONG_ADDR", j);
		iss_ccp2_reg_table[i++].addr = CCP2_LCx_DAT_PONG_ADDR(j);
		sprintf(iss_ccp2_reg_table[i].name, "CCP2_LC%d_DAT_OFST", j);
		iss_ccp2_reg_table[i++].addr = CCP2_LCx_DAT_OFST(j);
	}

	strcpy(iss_ccp2_reg_table[i].name, "CCP2_LCM_CTRL");
	iss_ccp2_reg_table[i++].addr = CCP2_LCM_CTRL;
	strcpy(iss_ccp2_reg_table[i].name, "CCP2_LCM_VSIZE");
	iss_ccp2_reg_table[i++].addr = CCP2_LCM_VSIZE;
	strcpy(iss_ccp2_reg_table[i].name, "CCP2_LCM_HSIZE");
	iss_ccp2_reg_table[i++].addr = CCP2_LCM_HSIZE;
	strcpy(iss_ccp2_reg_table[i].name, "CCP2_LCM_PREFETCH");
	iss_ccp2_reg_table[i++].addr = CCP2_LCM_PREFETCH;
	strcpy(iss_ccp2_reg_table[i].name, "CCP2_LCM_SRC_ADDR");
	iss_ccp2_reg_table[i++].addr = CCP2_LCM_SRC_ADDR;
	strcpy(iss_ccp2_reg_table[i].name, "CCP2_LCM_SRC_OFST");
	iss_ccp2_reg_table[i++].addr = CCP2_LCM_SRC_OFST;
	strcpy(iss_ccp2_reg_table[i].name, "CCP2_LCM_DST_ADDR");
	iss_ccp2_reg_table[i++].addr = CCP2_LCM_DST_ADDR;
	strcpy(iss_ccp2_reg_table[i].name, "CCP2_LCM_DST_OFST");
	iss_ccp2_reg_table[i++].addr = CCP2_LCM_DST_OFST;
	strcpy(iss_ccp2_reg_table[i].name, "CCP2_LCM_HISTORY");
	iss_ccp2_reg_table[i++].addr = CCP2_LCM_HISTORY;
	strcpy(iss_ccp2_reg_table[i].name, "END");
	iss_ccp2_reg_table[i].addr = 0;

	init_done = 1;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		camera44xx_name2addr
 * @BRIEF		retrieve physical address of a register, given its name.
 * @RETURNS		0 if found, -1 otherwise.
 * @param[in]		name: register name
 * @param[in, out]	addr: register address
 * @DESCRIPTION		retrieve physical address of a register, given its name.
 *//*------------------------------------------------------------------------ */
int camera44xx_name2addr(char *name, unsigned int *addr)
{
	int ret, k;

	if (!cpu_is_omap44xx())
		return -1;

	if (!init_done)
		camera44xx_init_regtable();

	ret = name2addr(name, addr, iss_hl_reg_table);
	if (ret == 0)
		return 0;

	for (k = 0; k < 2; k++) {
		ret = name2addr(name, addr, iss_csi2_reg_table[k]);
		if (ret == 0)
			return 0;

		ret = name2addr(name, addr, iss_csiphy_reg_table[k]);
		if (ret == 0)
			return 0;
	}

	ret = name2addr(name, addr, iss_ccp2_reg_table);
	if (ret == 0)
		return 0;

	/* Not found above */
	return -1;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		camera44xx_clock_is_running
 * @BRIEF		check if selected camera clock is running or not.
 * @RETURNS		1 if selected clock is running,
 *			0 if clock is gated or erroneous id.
 * @param[in]		id: module to be dump (i.e. user-entered argv[3])
 * @DESCRIPTION		check if selected camera clock is running or not.
 *//*------------------------------------------------------------------------ */
unsigned char camera44xx_clock_is_running(camera44xx_clock_id id)
{
	unsigned char running;
	unsigned int cm_cam_clkstctrl, cm_cam_iss_clkctrl;
	unsigned int iss_clkstat;
	int ret;

	ret = mem_read(OMAP4430_CM_CAM_CLKSTCTRL, &cm_cam_clkstctrl);
	ret |= mem_read(OMAP4430_CM_CAM_ISS_CLKCTRL, &cm_cam_iss_clkctrl);
	if (ret != 0) {
		running = 0;
		goto camera44xx_clock_is_running_end;
	}

	/* Special ISS subgroup common treatment: */
	if ((id == ISS_SUBCLK_SIMCOP) ||
	    (id == ISS_SUBCLK_ISP) ||
	    (id == ISS_SUBCLK_CSI2A) ||
	    (id == ISS_SUBCLK_CSI2B) ||
	    (id == ISS_SUBCLK_CCP2) ||
	    (id == ISS_SUBCLK_VPORT0) ||
	    (id == ISS_SUBCLK_VPORT1) ||
	    (id == ISS_SUBCLK_VPORT2)) {
		/* First check if ISS_CLK is enabled, to avoid access fault. */
		running = extract_bit(cm_cam_clkstctrl, 8);
		if (running) {
			ret = mem_read(ISS_CLKSTAT, &iss_clkstat);
			if (ret != 0) {
				running = 0;
				goto camera44xx_clock_is_running_end;
			}
		}
	}

	switch (id) {
	case FDIF_FCLK:
		running = extract_bit(cm_cam_clkstctrl, 10);
		break;
	case CAM_PHY_CTRL_CLK:
		running = extract_bit(cm_cam_clkstctrl, 9);
		break;
	case ISS_CLK:
		running = extract_bit(cm_cam_clkstctrl, 8);
		break;
	case OPTFCLKEN_CTRLCLK:
		running = extract_bit(cm_cam_iss_clkctrl, 8);
		break;
	case ISS_SUBCLK_SIMCOP:
		running = extract_bit(iss_clkstat, 0);
		break;
	case ISS_SUBCLK_ISP:
		running = extract_bit(iss_clkstat, 1);
		break;
	case ISS_SUBCLK_CSI2A:
		running = extract_bit(iss_clkstat, 2);
		break;
	case ISS_SUBCLK_CSI2B:
		running = extract_bit(iss_clkstat, 3);
		break;
	case ISS_SUBCLK_CCP2:
		running = extract_bit(iss_clkstat, 4);
		break;
	case ISS_SUBCLK_VPORT0:
		running = extract_bit(iss_clkstat, 28);
		break;
	case ISS_SUBCLK_VPORT1:
		running = extract_bit(iss_clkstat, 29);
		break;
	case ISS_SUBCLK_VPORT2:
		running = extract_bit(iss_clkstat, 30);
		break;
	default:
		fprintf(stderr, "%s(): erroneous id (%d)!!!\n", __func__, id);
		running = 0;
	}

camera44xx_clock_is_running_end:
	return running;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		get_frame_name
 * @BRIEF		Transfer to format string from format value.
 * @RETURNS		format string
 * @param[in]		format integer
 * @DESCRIPTION		Transfer to format string from format value.
 *//*------------------------------------------------------------------------ */
static char *get_frame_name(unsigned int format)
{
	switch (format) {
	case 0x12:
		return "Embedded 8-bit nonimage data (that is, JPEG)";
	case 0x18:
		return "YUV4:2:0 8 bit";
	case 0x19:
		return "YUV4:2:0 10 bit";
	case 0x1e:
		return "YUV4:2:2 8 bit";
	case 0x1f:
		return "YUV4:2:2 10 bit";
	case 0x22:
		return "RGB565";
	case 0x24:
		return "RGB888";
	case 0x2A:
		return "RAW8";
	case 0x2B:
		return "RAW10";
	case 0x2C:
		return "RAW12";
	default:
		return "(Unknown)";
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		iss_csi2_check
 * @BRIEF		Dump CSI2 information.
 * @param[in]		CSI2 register
 * @DESCRIPTION		Dump CSI2 information.
 *//*------------------------------------------------------------------------ */
void iss_csi2_check(struct iss_csi2_regs *csi2)
{
	int mem_out = 0;
	unsigned int used_lanes = 0;

	printf("\tCSI2 Revision: %x.%x\n",
		csi2->revision.major, csi2->revision.minor);

	/* CSI2_SYSCONFIG checks */
	printf("\tMstandby mode is ");
	switch (csi2->sysconfig.mstandby_mode) {
	case 0:
		printf("Force-standby.\n");
		/* Aborting analysis */
		return;
	case 1:
		printf("No-standby.\n");
		break;
	case 2:
		printf("Smart-standby.\n");
		break;
	}
	printf("\tAuto-idle is %s.\n",
		csi2->sysconfig.auto_idle ? "enabled" : "disabled");

	/* CSI2_SYSSTATUS checks */
	if (!csi2->sysstatus.reset_done)
		printf("\tERROR: Reset is not done yet!\t ");

	/* CSI2_CTRL checks */
	printf("\tVideoPort clock is ");
	if (csi2->ctrl.vp_clk_en) {
		printf("enabled.\n");
		printf("\t\tVP_PCLK = OCPCLK");
		switch (csi2->ctrl.vp_out_ctrl) {
		case CSI2_CTRL_VP_OUT_CTRL_DIV1:
			printf(".\n");
			break;
		case CSI2_CTRL_VP_OUT_CTRL_DIV2:
			printf(" / 2.\n");
			break;
		case CSI2_CTRL_VP_OUT_CTRL_DIV3:
			printf(" / 3.\n");
			break;
		case CSI2_CTRL_VP_OUT_CTRL_DIV4:
			printf(" / 4.\n");
			break;
		}
		printf("\tOCP output is ");
		if (csi2->ctrl.vp_only_en) {
			mem_out = 0;
			printf("disabled.\n");
		} else {
			mem_out = 1;
			printf("enabled.\n");
		}
	} else {
		printf("disabled.\n");
		if (csi2->ctrl.vp_only_en) {
			printf("\tERROR: VP disabled, but VP ONLY is set?\n");
			mem_out = 0;
		}
	}

	if (mem_out) {
		printf("\tDMA burst size to the L3 bus is: ");
		if (csi2->ctrl.burst_size_expand)
			printf("16x64-bit burst.\n");
		else
			printf("%ux64 OCP writes.\n",
				1 << csi2->ctrl.burst_size);
	}

	if (!csi2->ctrl.non_posted_write)
		printf(
			"\tWARNING: Non-posted writes disabled. Not recommended.\n");

	if (csi2->ctrl.dbg_en)
		printf(
			"\tIMPORTANT: Debug mode enabled. Data input will be ignored.\n");

	printf("\tECC check is %s.\n",
		csi2->ctrl.ecc_en ? "enabled" : "disabled");
	printf("\tInterface is %s.\n",
		csi2->ctrl.if_en ? "enabled" : "disabled");

	printf("\tLane information:\n");
	/* COMPLEXIO_CFG checks */
	if (csi2->complexio_cfg.clock_position != 0)
		used_lanes |= (1 << csi2->complexio_cfg.clock_position);
	printf("\t\tClock: position #%u, %s polarity.%s\n",
		csi2->complexio_cfg.clock_position,
		csi2->complexio_cfg.clock_pol ? "X:-, Y:+" : "X:+, Y:-",
		csi2->complexio_cfg.clock_position == 0 ?
			" (WARNING: Disabled)" : "");

	printf("\t\tData lanes used:\n");

	if (used_lanes & (1 << csi2->complexio_cfg.data1_position)) {
		printf("\t\t\tERROR: Position #%u is already used!\n",
			csi2->complexio_cfg.data1_position);
	} else if (csi2->complexio_cfg.data1_position != 0) {
		used_lanes |= (1 << csi2->complexio_cfg.data1_position);

		printf("\t\t\tData1: position #%u, %s polarity.\n",
			csi2->complexio_cfg.data1_position,
			csi2->complexio_cfg.data1_pol ?
				"X:-, Y:+" : "X:+, Y:-");
	}

	if (used_lanes & (1 << csi2->complexio_cfg.data2_position)) {
		printf("\t\t\tERROR: Position #%u is already used!\n",
			csi2->complexio_cfg.data2_position);
	} else if (csi2->complexio_cfg.data2_position != 0) {
		used_lanes |= (1 << csi2->complexio_cfg.data2_position);

		printf("\t\t\tData2: position #%u, %s polarity.\n",
			csi2->complexio_cfg.data2_position,
			csi2->complexio_cfg.data2_pol ?
				"X:-, Y:+" : "X:+, Y:-");
	}

	if (used_lanes & (1 << csi2->complexio_cfg.data3_position)) {
		printf("\t\t\tERROR: Position #%u is already used!\n",
			csi2->complexio_cfg.data3_position);
	} else if (csi2->complexio_cfg.data3_position != 0) {
		used_lanes |= (1 << csi2->complexio_cfg.data3_position);

		printf("\t\t\tData3: position #%u, %s polarity.\n",
			csi2->complexio_cfg.data3_position,
			csi2->complexio_cfg.data3_pol ?
				"X:-, Y:+" : "X:+, Y:-");
	}

	if (used_lanes & (1 << csi2->complexio_cfg.data4_position)) {
		printf("\t\t\tERROR: Position #%u is already used!\n",
			csi2->complexio_cfg.data4_position);
	} else if (csi2->complexio_cfg.data4_position != 0) {
		used_lanes |= (1 << csi2->complexio_cfg.data4_position);

		printf("\t\t\tData4: position #%u, %s polarity.\n",
			csi2->complexio_cfg.data4_position,
			csi2->complexio_cfg.data4_pol ?
				"X:-, Y:+" : "X:+, Y:-");
	}

	if ((used_lanes &= ~(1 << csi2->complexio_cfg.clock_position)) == 0)
		printf("\t\t\tWARNING: No data lanes enabled.\n");

	printf("\tAutomatic switch between ULP and ON is %s\n",
		csi2->complexio_cfg.pwr_auto ? "disabled" : "enabled");

	printf("\tComplexIO power state is: ");
	switch (csi2->complexio_cfg.pwr_status) {
	case 0:
		printf("OFF\n");
		break;
	case 1:
		printf("ON\n");
		break;
	case 2:
		printf("Ultralow-Power\n");
		break;
	}

	if (csi2->complexio_cfg.reset_done == 0)
		printf("\tWARNING: ComplexIO Reset ongoing.\n");

	printf("\tStop state timeout in ISS_FCLK cycles: %u\n",
		csi2->timing.stop_state_counter_io1 *
		(1 + (csi2->timing.stop_state_x16_io1 * 15)) *
		(1 + (csi2->timing.stop_state_x4_io1 * 3)));

	printf("\tContext information:\n");
	{
		int i;

		for (i = 0; i < 8; i++) {
			/* NOTE: Comment out below to print all contexts */
			if (!csi2->ctx[i].ctrl1.ctx_en)
				continue;

			printf("\t\tContext#%u:\n", i);

			printf("\t\t\tContext is %s.\n",
				csi2->ctx[i].ctrl1.ctx_en ?
					"enabled" : "disabled");

			if (csi2->ctx[i].ctrl1.vp_force) {
				printf("\t\t\tEnforcing VP + OCP output.\n");
				if (!csi2->ctrl.vp_clk_en)
					printf(
						"\t\t\t\tWARNING: VideoPort is disabled!");
				if (csi2->ctrl.vp_only_en)
					printf(
						"\t\t\t\tWARNING: VP_ONLY selected.");
			}

			printf("\t\t\tChecksum is %s\n",
				csi2->ctx[i].ctrl1.cs_en ?
					"enabled" : "disabled");

			printf("\t\t\tFrames to capture: ");
			if (csi2->ctx[i].ctrl1.count)
				printf("%u\n", csi2->ctx[i].ctrl1.count);
			else
				printf("(infinite)\n");

			printf("\t\t\tFrame counter: %u\n",
				csi2->ctx[i].ctrl2.frame);

			printf("\t\t\tBuffers:\n");
			printf("\t\t\t\tPing: 0x%08x\n",
				csi2->ctx[i].dat_ping_addr);
			if (csi2->ctx[i].dat_ping_addr !=
				csi2->ctx[i].dat_pong_addr)
				printf("\t\t\t\tPong: 0x%08x\n",
					csi2->ctx[i].dat_pong_addr);
			printf("\t\t\t\tOffset: 0x%08x\n",
				csi2->ctx[i].dat_ofst);

			printf("\t\t\tFormat: 0x%x - %s%s.\n",
				csi2->ctx[i].ctrl2.format,
				get_frame_name(csi2->ctx[i].ctrl2.format),
				csi2->ctx[i].ctrl1.generic ?
					" (enforced)" : "");
		}
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		iss_isp5_sys1_check
 * @BRIEF		Dump ISP2 information.
 * @param[in]		ISP register
 * @DESCRIPTION		Dump ISP2 information.
 *//*------------------------------------------------------------------------ */
unsigned int iss_isp5_sys1_check(struct iss_top_regs *iss_top,
	struct iss_isp5_sys1_regs *iss_isp5_sys1)
{
	unsigned int 	ret = 0;
	struct iss_ipipeif_regs *iss_ipipeif = NULL;
	struct iss_isif_regs *iss_isif = NULL;
	struct iss_ipipe_regs *iss_ipipe = NULL;
	struct iss_resizer_regs *iss_resizer = NULL;
	struct iss_h3a_regs *iss_h3a = NULL;

	printf("\tISS ISP5 Revision: %x.%x.%x\n",
		iss_isp5_sys1->revision.x_major,
		iss_isp5_sys1->revision.y_minor,
		iss_isp5_sys1->revision.r_rtl);

	/* ISP5_SYSCONFIG checks */
	printf("\tMstandby mode is ");
	switch (iss_isp5_sys1->sysconfig.standbymode) {
	case 0:
		printf("Force-standby.\n");
		/* Aborting analysis */
		goto next5;
		break;
	case 1:
		printf("No-standby.\n");
		break;
	case 2:
		printf("Smart-standby.\n");
		break;
	}
	printf("\tAuto-idle is %s.\n",
		iss_isp5_sys1->sysconfig.auto_idle ? "enabled" : "disabled");
	printf("\tIPIPEIF Input: ");

	switch (iss_top->ctrl.input_sel) {
	case ISS_CTRL_INPUT_SEL_CSI2A:
		printf("CSI2A.\n");
		break;
	case ISS_CTRL_INPUT_SEL_CSI2B:
		printf("CSI2B.\n");
		break;
	case ISS_CTRL_INPUT_SEL_CCP2:
		printf("CCP2.\n");
		break;
	default:
		printf("Parallel.\n");
		break;
	}

	if (iss_isp5_sys1->ctrl.ipipeif_clk_enable) {
		printf("\tIPIPEIF subclock is enabled.\n");
		iss_ipipeif = mem_map_address(ISS_IPIPEIF_PBASE);
		if (iss_ipipeif == 0) {
			ret = OMAPCONF_ERR_REG_ACCESS;
			goto next1;
		}

		printf("\t\tSelected datapath:\n");
		if ((iss_ipipeif->cfg1.inpsrc1 == 0) &&
			(iss_ipipeif->cfg1.inpsrc2 == 0)) {
			printf("\t\t\tVideoPort -> ISIF -> IPIPE/RSZ/H3A\n");
		} else if ((iss_ipipeif->cfg1.inpsrc1 == 0) &&
			(iss_ipipeif->cfg1.inpsrc2 == 1)) {
			printf(
				"\t\t\tBuffer Logic (RAW) -> [A-Law/DPCM] -> IPIPE/RSZ\n");
		} else if ((iss_ipipeif->cfg1.inpsrc1 == 0) &&
			(iss_ipipeif->cfg1.inpsrc2 == 2)) {
			printf(
				"\t\t\tVideoPort -> ISIF -> Dark frame subtraction/H3A\n");
			printf(
				"\t\t\tBuffer Logic (RAW) -> Dark frame subtraction\n");
			printf("\t\t\tDark frame subtraction -> IPIPE/RSZ\n");
		} else if ((iss_ipipeif->cfg1.inpsrc1 == 0) &&
			(iss_ipipeif->cfg1.inpsrc2 == 3)) {
			printf("\t\t\tVideoPort -> ISIF -> H3A\n");
			printf("\t\t\tBuffer Logic (RAW/YUV) -> IPIPE/RSZ\n");
		} else {
			printf("\t\t\t(Unknown, INPSRC1=%u, INPSRC2=%u)\n",
				iss_ipipeif->cfg1.inpsrc1,
				iss_ipipeif->cfg1.inpsrc2);
		}
	}

next1:
	if (iss_isp5_sys1->ctrl.isif_clk_enable) {
		printf("\tISIF subclock is enabled.\n");
		iss_isif = mem_map_address(ISS_ISIF_PBASE);
		if (iss_isif == 0) {
			ret = OMAPCONF_ERR_REG_ACCESS;
			goto next2;
		}

		printf("\t\tModule is %s.\n",
			iss_isif->syncen.syen ? "enabled" : "disabled");
		if (!iss_isif->syncen.syen)
			goto next2;
		printf("\t\tData input type: ");
		switch (iss_isif->modeset.inpmod) {
		case 0:
			printf("RAW.\n");
			break;
		case 1:
			printf("YCbCr 16bit.\n");
			break;
		case 2:
			printf("YCbCr 8bit.\n");
			printf("\t\t\tY signal position in %s pixel.\n",
				iss_isif->ccdcfg.y8pos ? "odd" : "even");
			break;
		case 3:
			printf("Reserved(?).\n");
			break;
		}
		printf("\t\tHD/VD signal direction is %s.\n",
			iss_isif->modeset.hdvdd ? "output" : "input");
		printf("\t\tHD polarity is %s.\n",
			iss_isif->modeset.hdpol ? "Negative" : "Pastive");
		printf("\t\tVD polarity is %s.\n",
			iss_isif->modeset.vdpol ? "Negative" : "Pastive");
		printf("\t\tFLD signal direction is %s.\n",
			iss_isif->modeset.fidd ? "output" : "input");
		printf("\t\t%s sensor.\n", iss_isif->modeset.ccdmd ?
			"Interlaced" : "Progressive");
		if (!cpu_is_omap4430()) {
			printf("\t\tFLD polarity is %s.\n",
				iss_isif->modeset.fdpol ?
					"Negative" : "Pastive");
			printf("\t\tLow pass filter is %s.\n",
				iss_isif->modeset.vdpol ?
					"enabled" : "disabled");
		}
		printf("\t\tSDRAM output is %s.\n",
			iss_isif->syncen.dwen ? "enabled" : "disabled");
	}
next2:
	if (iss_isp5_sys1->ctrl.ipipe_clk_enable) {
		printf("\tIPIPE subclock is enabled.\n");
		iss_ipipe = mem_map_address(ISS_IPIPE_PBASE);
		if (iss_ipipe == 0) {
			ret = OMAPCONF_ERR_REG_ACCESS;
			goto next3;
		}

		printf("\t\tGlobal clock is %s.\n",
			iss_ipipe->gck_mmr ? "enabled" : "disabled. Exiting..");
		/* Exiting analysis if global clock is disabled */
		if (!iss_ipipe->gck_mmr)
			goto next3;

		printf("\t\tSource is %s.\n", iss_ipipe->src_en.en ?
			"enabled" : "disabled");

		printf("\t\tSelected datapath: ");
		switch (iss_ipipe->src_fmt.fmt) {
		case 0:
			printf("IN: RAW BAYER, OUT: YUV4:2:2\n");
			break;
		case 1:
			printf("IN: RAW BAYER, OUT: RAW BAYER\n");
			break;
		case 2:
			printf("IN: RAW BAYER, OUT: DISABLED\n");
			break;
		case 3:
			printf("IN: YUV4:2:2, OUT: YUV4:2:2\n");
			break;
		}

		printf("\t\tInput start/size: X=%d/%d;Y=%d/%d\n",
			iss_ipipe->src_hps, iss_ipipe->src_hsz,
			iss_ipipe->src_vps, iss_ipipe->src_vsz + 1);
	}

next3:
	if (iss_isp5_sys1->ctrl.rsz_clk_enable) {
		printf("\tRESIZER subclock is enabled.\n");
		iss_resizer = mem_map_address(ISS_RESIZER_PBASE);
		if (iss_resizer == 0) {
			ret = OMAPCONF_ERR_REG_ACCESS;
			goto next4;
		}

		printf("\t\tGlobal clock is %s.\n",
			iss_resizer->gck_mmr ? "enabled" : "disabled.");
		#if 0
		printf("\t\tRESIZER Revision: %x.%x\n",
			iss_resizer->revision.major,
			iss_resizer->revision.minor);
		#endif
		printf("\t\tRESIZER core clock is %s.\n",
			(iss_resizer->gck_sdr & 0x1) ? "enabled" : "disabled");
		printf("\t\tSource is %s.\n",
			iss_resizer->src_en.en ? "enabled" : "disabled");
		printf("\t\tSelected datapath:%s.\n",
			iss_resizer->src_fmt0.sel ? "IPIPEIF" : "IPIPE");

		printf("\t\tInput data is %s.\n",
			iss_resizer->src_fmt1.in420 ?
				"YUV4:2:0" : "YUV4:2:2");
		printf("\t\tInput start/size: X=%d/%d;Y=%d/%d\n",
			iss_resizer->src_hps, iss_resizer->src_hsz + 1,
			iss_resizer->src_vps, iss_resizer->src_vsz + 1);

		printf("\t\tRESIZER A clock is %s.\n",
			iss_resizer->sysconfig.rsza_clk_en ?
				"enabled" : "disabled");
		printf("\t\tRESIZER B clock is %s.\n",
			iss_resizer->sysconfig.rszb_clk_en ?
				"enabled" : "disabled");

		printf("\t\tRESIZER A output format is %s.\n",
			(iss_resizer->rza.n420 & 0x3) ?
				"YUV4:2:0" : "YUV4:2:2");
		printf("\t\tRESIZER B output format is %s.\n",
			(iss_resizer->rzb.n420 & 0x3) ?
				"YUV4:2:0" : "YUV4:2:2");

		/* Exiting analysis if global clock is disabled */
		if (!iss_resizer->gck_mmr)
			goto next4;
	}

next4:
	if (iss_isp5_sys1->ctrl.h3a_clk_enable) {
		printf("\tH3A subclock is enabled.\n");
		iss_h3a = mem_map_address(ISS_H3A_PBASE);
		if (iss_h3a == 0) {
			ret = OMAPCONF_ERR_REG_ACCESS;
			goto next5;
		}
		printf("\t\tH3A Revision: %x.%x.%x\n",
			iss_h3a->pid.x_major, iss_h3a->pid.y_minor,
			iss_h3a->pid.r_rtl);
	}
next5:

	if (iss_h3a)
		mem_unmap_address(iss_h3a);
	if (iss_resizer)
		mem_unmap_address(iss_resizer);
	if (iss_ipipe)
		mem_unmap_address(iss_ipipe);
	if (iss_isif)
		mem_unmap_address(iss_isif);
	if (iss_ipipeif)
		mem_unmap_address(iss_ipipeif);

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		camera44xx_dump
 * @BRIEF		dump CAMERA registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		camera_mod: module to be dump
 *			(i.e. user-entered argv[3])
 * @DESCRIPTION		dump CAMERA registers
 *//*------------------------------------------------------------------------ */
int camera44xx_dump(char *camera_mod)
{
	int ret;

	if (!cpu_is_omap44xx()) {
		ret = OMAPCONF_ERR_CPU;
		goto camera44xx_dump_end;
	}

	if (!camera44xx_clock_is_running(ISS_CLK)) {
		printf("ISS CLK stopped, registers not accessible.\n\n");
		ret = OMAPCONF_ERR_REG_ACCESS;
		goto camera44xx_dump_end;
	}

	if (!init_done)
		camera44xx_init_regtable();

	ret = OMAPCONF_ERR_ARG;
	if ((strcmp(camera_mod, "all") == 0) ||
		(strcmp(camera_mod, "iss_hl") == 0))
		ret = dumpregs(iss_hl_reg_table);

	if ((strcmp(camera_mod, "all") == 0) ||
		(strcmp(camera_mod, "iss_csi2a") == 0)) {
		if (!camera44xx_clock_is_running(ISS_SUBCLK_CSI2A)) {
			printf(
				"ISS CSI2A clock stopped, registers not accessible.\n\n");
			ret = OMAPCONF_ERR_REG_ACCESS;
		} else {
			ret = dumpregs(iss_csi2_reg_table[0]);
		}
	}

	if ((strcmp(camera_mod, "all") == 0) ||
		(strcmp(camera_mod, "iss_csiphy1") == 0)) {
		if (!camera44xx_clock_is_running(ISS_SUBCLK_CSI2A)) {
			printf(
				"ISS CSI2A clock stopped, registers not accessible.\n\n");
			ret = OMAPCONF_ERR_REG_ACCESS;
		} else {
			ret = dumpregs(iss_csiphy_reg_table[0]);
		}
	}

	if ((strcmp(camera_mod, "all") == 0) ||
		(strcmp(camera_mod, "iss_csi2b") == 0)) {
		if (!camera44xx_clock_is_running(ISS_SUBCLK_CSI2B)) {
			printf(
				"ISS CSI2B clock stopped, registers not accessible.\n\n");
			ret = OMAPCONF_ERR_REG_ACCESS;
		} else {
			ret = dumpregs(iss_csi2_reg_table[1]);
		}
	}

	if ((strcmp(camera_mod, "all") == 0) ||
		(strcmp(camera_mod, "iss_csiphy2") == 0)) {
		if (!camera44xx_clock_is_running(ISS_SUBCLK_CSI2B)) {
			printf(
				"ISS CSI2B clock stopped, registers not accessible.\n\n");
			ret = OMAPCONF_ERR_REG_ACCESS;
		} else {
			ret = dumpregs(iss_csiphy_reg_table[1]);
		}
	}

	if ((strcmp(camera_mod, "all") == 0) ||
		(strcmp(camera_mod, "iss_ccp2") == 0)) {
		if (!camera44xx_clock_is_running(ISS_SUBCLK_CCP2)) {
			printf(
				"ISS CCP2 clock stopped, registers not accessible.\n\n");
			ret = OMAPCONF_ERR_REG_ACCESS;
		} else {
			ret = dumpregs(iss_ccp2_reg_table);
		}
	}

	if (ret == OMAPCONF_ERR_ARG)
		help(HELP_CAMERA);

camera44xx_dump_end:
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		camera44xx_config_show
 * @BRIEF		Show camera configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_INTERNAL
 * @DESCRIPTION		Show camera configuration
 *//*------------------------------------------------------------------------ */
int camera44xx_config_show(void)
{
	struct iss_top_regs *iss_top = NULL;
	struct iss_csi2_regs *iss_csi2a = NULL;
	struct iss_csi2_regs *iss_csi2b = NULL;
	struct iss_ccp2_regs *iss_ccp2 = NULL;
	struct iss_isp5_sys1_regs *iss_isp5_sys1 = NULL;
	unsigned int camera_rx;
	int i, ret;

	ret = OMAPCONF_ERR_ARG;

	if (!cpu_is_omap44xx()) {
		ret = OMAPCONF_ERR_CPU;
		goto camera44xx_show_end;
	}

	if (!camera44xx_clock_is_running(ISS_CLK)) {
		printf("ISS CLK stopped, registers not accessible.\n\n");
		ret = OMAPCONF_ERR_REG_ACCESS;
		goto camera44xx_show_end;
	}

	ret = mem_read(CONTROL_CAMERA_RX, &camera_rx);
	if (ret != 0) {
		ret = OMAPCONF_ERR_REG_ACCESS;
		goto camera44xx_show_end;
	}
	printf("CONTROL_CAMERA_RX\n");
	printf("\tCSI21:\n");
	printf("\t\tMode: ");
	switch ((camera_rx & (0x3 << 16)) >> 16) {
	case 0:
		printf("D-PHY.\n");
		break;
	case 1:
		printf("Data/strobe (CCP2).\n");
		break;
	case 2:
		printf("Data/clock (CCP2/CSI1).\n");
		break;
	case 3:
		printf("GPI (Parallel).\n");
		break;
	}
	printf("\t\tCTRLCLK: %s.\n",
		(camera_rx & (1 << 18)) ? "enabled" : "disabled");
	printf("\t\tLanes enabled (0->4): ");
	for (i = 0; i < 5; i++) {
		if (i != 0)
			printf(", ");
		printf("%s", (camera_rx & (1 << (i + 24))) ? "1" : "0");
	}
	printf("\n");


	printf("\tCSI22:\n");
	printf("\t\tMode: ");
	switch ((camera_rx & (0x3 << 19)) >> 19) {
	case 0:
		printf("D-PHY.\n");
		break;
	case 1:
		printf("Data/strobe (CCP2).\n");
		break;
	case 2:
		printf("Data/clock (CCP2/CSI1).\n");
		break;
	case 3:
		printf("GPI (Parallel).\n");
		break;
	}
	printf("\t\tCTRLCLK: %s.\n",
		(camera_rx & (1 << 21)) ? "enabled" : "disabled");

	if (cpu_is_omap4470()) {
		printf("\t\tLanes enabled (0->2): ");
		for (i = 0; i < 3; i++) {
			if (i != 0)
				printf(", ");
			printf("%s", (camera_rx & (1 << (i + 29))) ? "1" : "0");
		}
	} else {
		printf("\t\tLanes enabled (0->1): ");
		for (i = 0; i < 2; i++) {
			if (i != 0)
				printf(", ");
			printf("%s", (camera_rx & (1 << (i + 29))) ? "1" : "0");
		}
	}
	printf("\n");

	iss_top = mem_map_address(ISS_TOP_PBASE);
	if (iss_top == 0) {
		ret = OMAPCONF_ERR_REG_ACCESS;
		goto camera44xx_show_end;
	}

	printf("ISS Revision: %x.%x.%x\n", iss_top->hl_revision.x_major,
		iss_top->hl_revision.y_minor, iss_top->hl_revision.r_rtl);

	if (!camera44xx_clock_is_running(ISS_SUBCLK_CSI2A)) {
		printf("ISS CSI2A CLK stopped, registers not accessible.\n\n");
		ret = OMAPCONF_ERR_REG_ACCESS;
		goto next1;
	}

	printf("CSI2A CLK is enabled.\n");
	iss_csi2a = mem_map_address(ISS_CSI2_A_REGS1_PBASE);
	if (iss_csi2a == 0) {
		ret = OMAPCONF_ERR_REG_ACCESS;
		goto next1;
	}

	iss_csi2_check(iss_csi2a);

next1:
	if (!camera44xx_clock_is_running(ISS_SUBCLK_CSI2B)) {
		printf("ISS CSI2B CLK stopped, registers not accessible.\n\n");
		ret = OMAPCONF_ERR_REG_ACCESS;
		goto next2;
	}

	printf("CSI2B CLK is enabled.\n");
	iss_csi2b = mem_map_address(ISS_CSI2_B_REGS1_PBASE);
	if (iss_csi2b == 0) {
		ret = OMAPCONF_ERR_REG_ACCESS;
		goto next2;
	}

	iss_csi2_check(iss_csi2b);

next2:
	if (!camera44xx_clock_is_running(ISS_SUBCLK_CCP2)) {
		printf("ISS CCP2 CLK stopped, registers not accessible.\n\n");
		ret = OMAPCONF_ERR_REG_ACCESS;
		goto next3;
	}

	printf("CCP2 CLK is enabled.\n");
	iss_ccp2 = mem_map_address(ISS_CCP2_PBASE);
	if (iss_ccp2 == 0) {
		ret = OMAPCONF_ERR_REG_ACCESS;
		goto next3;
	}
	printf("\tCCP2 Revision: 0x%x\n", iss_ccp2->revision);
	printf("\tLCM_SRC_ADDR:0x%x\n", iss_ccp2->lcm_src_addr);
	printf("\tLCM_SRC_OFST:%d\n", iss_ccp2->lcm_src_ofst);
	printf("\tLCM_HSIZE_SKIP:%d\n", (iss_ccp2->lcm_hsize) & 0xFFF);
	printf("\tRead data from memory size: X=%d;Y=%d\n",
		(iss_ccp2->lcm_hsize) >> 16, (iss_ccp2->lcm_vsize) >> 16);
	printf("\tCCP2 write data to %s.\n",
		((iss_ccp2->lcm_ctrl & 0x40) >> 2) ? "Memory" : "VideoPort");


next3:
	if (!camera44xx_clock_is_running(ISS_SUBCLK_ISP)) {
		printf("ISS ISP CLK stopped, registers not accessible.\n\n");
		ret = OMAPCONF_ERR_REG_ACCESS;
		goto next4;
	}

	printf("ISP CLK is enabled.\n");
	iss_isp5_sys1 = mem_map_address(ISS_ISP5_SYS1_PBASE);
	if (iss_isp5_sys1 == 0) {
		ret = OMAPCONF_ERR_REG_ACCESS;
		goto next4;
	}

	ret = iss_isp5_sys1_check(iss_top, iss_isp5_sys1);
	if (ret != 0) {
		ret = OMAPCONF_ERR_REG_ACCESS;
		goto next4;
	}

next4:
	if (!camera44xx_clock_is_running(ISS_SUBCLK_SIMCOP)) {
		printf("ISS SIMCOP CLK stopped, registers not accessible.\n\n");
		ret = OMAPCONF_ERR_REG_ACCESS;
		goto camera44xx_show_end;
	}
	printf("SIMCOP CLK is enabled.\n");

	if (ret == OMAPCONF_ERR_ARG)
		help(HELP_CAMERA);

camera44xx_show_end:

	if (iss_isp5_sys1)
		mem_unmap_address(iss_isp5_sys1);
	if (iss_csi2a)
		mem_unmap_address(iss_csi2a);
	if (iss_csi2b)
		mem_unmap_address(iss_csi2b);
	if (iss_ccp2)
		mem_unmap_address(iss_ccp2);
	if (iss_top)
		mem_unmap_address(iss_ccp2);

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		camera44xx_main
 * @BRIEF		CAMERA main menu
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_INTERNAL
 * @param[in]		argc: shell input argument number
 *			argv: shell input argument(s)
 * @DESCRIPTION		CAMERA main menu
 *//*------------------------------------------------------------------------ */
int camera44xx_main(int argc, char *argv[])
{
	int ret;

	if (!cpu_is_omap44xx())
		return OMAPCONF_ERR_CPU;

	if (argc != 3) {
		help(HELP_CAMERA);
		return OMAPCONF_ERR_ARG;
	}

	if (strcmp(argv[1], "dump") == 0) {
		ret = camera44xx_dump(argv[2]);
	} else {
		help(HELP_CAMERA);
		ret = OMAPCONF_ERR_ARG;
	}

	return ret;
}
