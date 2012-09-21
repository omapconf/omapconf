/*
 *
 * @Component			OMAPCONF
 * @Filename			display44xx.c
 * @Description			OMAP4 Display Configuration
 * @Author			Erwan Petillon (e-petillon@ti.com)
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


#include <display44xx.h>
#include <lib44xx.h>
#include <help.h>
#include <lib.h>
#include <mem.h>
#include <cpuinfo.h>
#include <string.h>
#include <cm44xx.h>


/* #define DISPLAY44XX_DEBUG */
#ifdef DISPLAY44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif

#define DSS_REG_TABLE_SIZE		5
#define DSI1_REG_TABLE_SIZE		64
#define DSI1_PHY_REG_TABLE_SIZE		7
#define DSI1_PLL_REG_TABLE_SIZE		10
#define DSI2_REG_TABLE_SIZE		64
#define DSI2_PHY_REG_TABLE_SIZE		7
#define DSI2_PLL_REG_TABLE_SIZE		10
#define RFBI_REG_TABLE_SIZE		25
#define VENC_REG_TABLE_SIZE		44
#define DISPC_REG_TABLE_SIZE		351


typedef enum {
	HDMI_PHY_48MHz_FCLK,
	DSS_ALWON_SYS_CLK,
	DSS_FCLK,
	DSS_L3_ICLK,
	OPTFCLK_TV_FCLK,
	OPTFCLK_SYS_CLK,
	OPTFCLK_48MHZ_CLK,
	OPTFCLK_DSSCLK,
	DISPLAY44XX_CLOCK_ID_MAX
} display44xx_clock_id;


reg_table dss_reg_table[DSS_REG_TABLE_SIZE];
reg_table dispc_reg_table[DISPC_REG_TABLE_SIZE];
reg_table dsi1_reg_table[DSI1_REG_TABLE_SIZE];
reg_table dsi1_phy_reg_table[DSI1_PHY_REG_TABLE_SIZE];
reg_table dsi1_pll_reg_table[DSI1_PLL_REG_TABLE_SIZE];
reg_table dsi2_reg_table[DSI2_REG_TABLE_SIZE];
reg_table dsi2_phy_reg_table[DSI2_PHY_REG_TABLE_SIZE];
reg_table dsi2_pll_reg_table[DSI2_PLL_REG_TABLE_SIZE];
reg_table rfbi_reg_table[RFBI_REG_TABLE_SIZE];
reg_table venc_reg_table[VENC_REG_TABLE_SIZE];

static unsigned int init_done = 0;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		display44xx_init_regtable
 * @BRIEF		initialize regtable
 * @RETURNS		0
 *			OMAPCONF_ERR_CPU
 * @DESCRIPTION		initialize regtable
 *//*------------------------------------------------------------------------ */
int display44xx_init_regtable(void)
{
	int i = 0;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	/* Init DSS registers table */
	strcpy(dss_reg_table[i].name , "DSS_REVISION");
	dss_reg_table[i++].addr = DSS_REVISION;
	strcpy(dss_reg_table[i].name , "DSS_SYSSTATUS");
	dss_reg_table[i++].addr = DSS_SYSSTATUS;
	strcpy(dss_reg_table[i].name , "DSS_CTRL");
	dss_reg_table[i++].addr = DSS_CTRL;
	strcpy(dss_reg_table[i].name , "DSS_STATUS");
	dss_reg_table[i++].addr = DSS_STATUS;
	strcpy(dss_reg_table[i].name, "END");
	dss_reg_table[i].addr = 0;

	/* Init DSI1 PHY registers table */
	i = 0;
	strcpy(dsi1_phy_reg_table[i].name , "DSI1_PHY_REGISTER0");
	dsi1_phy_reg_table[i++].addr = DSI1_PHY_REGISTER0;
	strcpy(dsi1_phy_reg_table[i].name , "DSI1_PHY_REGISTER1");
	dsi1_phy_reg_table[i++].addr = DSI1_PHY_REGISTER1;
	strcpy(dsi1_phy_reg_table[i].name , "DSI1_PHY_REGISTER2");
	dsi1_phy_reg_table[i++].addr = DSI1_PHY_REGISTER2;
	strcpy(dsi1_phy_reg_table[i].name , "DSI1_PHY_REGISTER3");
	dsi1_phy_reg_table[i++].addr = DSI1_PHY_REGISTER3;
	strcpy(dsi1_phy_reg_table[i].name , "DSI1_PHY_REGISTER4");
	dsi1_phy_reg_table[i++].addr = DSI1_PHY_REGISTER4;
	strcpy(dsi1_phy_reg_table[i].name , "DSI1_PHY_REGISTER5");
	dsi1_phy_reg_table[i++].addr = DSI1_PHY_REGISTER5;
	strcpy(dsi1_phy_reg_table[i].name, "END");
	dsi1_phy_reg_table[i].addr = 0;

	/* Init DSI1 PHY registers table */
	i = 0;
	strcpy(dsi1_reg_table[i].name , "DSI1_REVISION");
	dsi1_reg_table[i++].addr = DSI1_REVISION;
	strcpy(dsi1_reg_table[i].name , "DSI1_SYSCONFIG");
	dsi1_reg_table[i++].addr = DSI1_SYSCONFIG;
	strcpy(dsi1_reg_table[i].name , "DSI1_SYSSTATUS");
	dsi1_reg_table[i++].addr = DSI1_SYSSTATUS;
	strcpy(dsi1_reg_table[i].name , "DSI1_IRQSTATUS");
	dsi1_reg_table[i++].addr = DSI1_IRQSTATUS;
	strcpy(dsi1_reg_table[i].name , "DSI1_IRQENABLE");
	dsi1_reg_table[i++].addr = DSI1_IRQENABLE;
	strcpy(dsi1_reg_table[i].name , "DSI1_CTRL");
	dsi1_reg_table[i++].addr = DSI1_CTRL;
	strcpy(dsi1_reg_table[i].name , "DSI1_GNQ");
	dsi1_reg_table[i++].addr = DSI1_GNQ;
	strcpy(dsi1_reg_table[i].name , "DSI1_COMPLEXIO_CFG1");
	dsi1_reg_table[i++].addr = DSI1_COMPLEXIO_CFG1;
	strcpy(dsi1_reg_table[i].name , "DSI1_COMPLEXIO_IRQSTATUS");
	dsi1_reg_table[i++].addr = DSI1_COMPLEXIO_IRQSTATUS;
	strcpy(dsi1_reg_table[i].name , "DSI1_COMPLEXIO_IRQENABLE");
	dsi1_reg_table[i++].addr = DSI1_COMPLEXIO_IRQENABLE;
	strcpy(dsi1_reg_table[i].name , "DSI1_CLK_CTRL");
	dsi1_reg_table[i++].addr = DSI1_CLK_CTRL;
	strcpy(dsi1_reg_table[i].name , "DSI1_TIMING1");
	dsi1_reg_table[i++].addr = DSI1_TIMING1;
	strcpy(dsi1_reg_table[i].name , "DSI1_TIMING2");
	dsi1_reg_table[i++].addr = DSI1_TIMING2;
	strcpy(dsi1_reg_table[i].name , "DSI1_VM_TIMING1");
	dsi1_reg_table[i++].addr = DSI1_VM_TIMING1;
	strcpy(dsi1_reg_table[i].name , "DSI1_VM_TIMING2");
	dsi1_reg_table[i++].addr = DSI1_VM_TIMING2;
	strcpy(dsi1_reg_table[i].name , "DSI1_VM_TIMING3");
	dsi1_reg_table[i++].addr = DSI1_VM_TIMING3;
	strcpy(dsi1_reg_table[i].name , "DSI1_CLK_TIMING");
	dsi1_reg_table[i++].addr = DSI1_CLK_TIMING;
	strcpy(dsi1_reg_table[i].name , "DSI1_TX_FIFO_VC_SIZE");
	dsi1_reg_table[i++].addr = DSI1_TX_FIFO_VC_SIZE;
	strcpy(dsi1_reg_table[i].name , "DSI1_RX_FIFO_VC_SIZE");
	dsi1_reg_table[i++].addr = DSI1_RX_FIFO_VC_SIZE;
	strcpy(dsi1_reg_table[i].name , "DSI1_COMPLEXIO_CFG2");
	dsi1_reg_table[i++].addr = DSI1_COMPLEXIO_CFG2;
	strcpy(dsi1_reg_table[i].name , "DSI1_RX_FIFO_VC_FULLNESS");
	dsi1_reg_table[i++].addr = DSI1_RX_FIFO_VC_FULLNESS;
	strcpy(dsi1_reg_table[i].name , "DSI1_VM_TIMING4");
	dsi1_reg_table[i++].addr = DSI1_VM_TIMING4;
	strcpy(dsi1_reg_table[i].name , "DSI1_TX_FIFO_VC_EMPTINESS");
	dsi1_reg_table[i++].addr = DSI1_TX_FIFO_VC_EMPTINESS;
	strcpy(dsi1_reg_table[i].name , "DSI1_VM_TIMING5");
	dsi1_reg_table[i++].addr = DSI1_VM_TIMING5;
	strcpy(dsi1_reg_table[i].name , "DSI1_VM_TIMING6");
	dsi1_reg_table[i++].addr = DSI1_VM_TIMING6;
	strcpy(dsi1_reg_table[i].name , "DSI1_VM_TIMING7");
	dsi1_reg_table[i++].addr = DSI1_VM_TIMING7;
	strcpy(dsi1_reg_table[i].name , "DSI1_STOPCLK_TIMING");
	dsi1_reg_table[i++].addr = DSI1_STOPCLK_TIMING;
	strcpy(dsi1_reg_table[i].name , "DSI1_CTRL2");
	dsi1_reg_table[i++].addr = DSI1_CTRL2;
	strcpy(dsi1_reg_table[i].name , "DSI1_VM_TIMING8");
	dsi1_reg_table[i++].addr = DSI1_VM_TIMING8;
	strcpy(dsi1_reg_table[i].name , "DSI1_TE_HSYNC_WIDTH_0");
	dsi1_reg_table[i++].addr = DSI1_TE_HSYNC_WIDTH_0;
	strcpy(dsi1_reg_table[i].name , "DSI1_TE_VSYNC_WIDTH_0");
	dsi1_reg_table[i++].addr = DSI1_TE_VSYNC_WIDTH_0;
	strcpy(dsi1_reg_table[i].name , "DSI1_TE_HSYNC_NUMBER_0");
	dsi1_reg_table[i++].addr = DSI1_TE_HSYNC_NUMBER_0;
	strcpy(dsi1_reg_table[i].name , "DSI1_TE_HSYNC_WIDTH_1");
	dsi1_reg_table[i++].addr = DSI1_TE_HSYNC_WIDTH_1;
	strcpy(dsi1_reg_table[i].name , "DSI1_TE_VSYNC_WIDTH_1");
	dsi1_reg_table[i++].addr = DSI1_TE_VSYNC_WIDTH_1;
	strcpy(dsi1_reg_table[i].name , "DSI1_TE_HSYNC_NUMBER_1");
	dsi1_reg_table[i++].addr = DSI1_TE_HSYNC_NUMBER_1;
	strcpy(dsi1_reg_table[i].name , "DSI1_VC_CTRL_1");
	dsi1_reg_table[i++].addr = DSI1_VC_CTRL_1;
	strcpy(dsi1_reg_table[i].name , "DSI1_VC_TE_1");
	dsi1_reg_table[i++].addr = DSI1_VC_TE_1;
	strcpy(dsi1_reg_table[i].name , "DSI1_VC_LONG_PACKET_HEADER_1");
	dsi1_reg_table[i++].addr = DSI1_VC_LONG_PACKET_HEADER_1;
	strcpy(dsi1_reg_table[i].name , "DSI1_VC_LONG_PACKET_PAYLOAD_1");
	dsi1_reg_table[i++].addr = DSI1_VC_LONG_PACKET_PAYLOAD_1;
	strcpy(dsi1_reg_table[i].name , "DSI1_VC_SHORT_PACKET_HEADER_1");
	dsi1_reg_table[i++].addr = DSI1_VC_SHORT_PACKET_HEADER_1;
	strcpy(dsi1_reg_table[i].name , "DSI1_VC_IRQSTATUS_1");
	dsi1_reg_table[i++].addr = DSI1_VC_IRQSTATUS_1;
	strcpy(dsi1_reg_table[i].name , "DSI1_VC_IRQENABLE_1");
	dsi1_reg_table[i++].addr = DSI1_VC_IRQENABLE_1;
	strcpy(dsi1_reg_table[i].name , "DSI1_VC_CTRL_2");
	dsi1_reg_table[i++].addr = DSI1_VC_CTRL_2;
	strcpy(dsi1_reg_table[i].name , "DSI1_VC_TE_2");
	dsi1_reg_table[i++].addr = DSI1_VC_TE_2;
	strcpy(dsi1_reg_table[i].name , "DSI1_VC_LONG_PACKET_HEADER_2");
	dsi1_reg_table[i++].addr = DSI1_VC_LONG_PACKET_HEADER_2;
	strcpy(dsi1_reg_table[i].name , "DSI1_VC_LONG_PACKET_PAYLOAD_2");
	dsi1_reg_table[i++].addr = DSI1_VC_LONG_PACKET_PAYLOAD_2;
	strcpy(dsi1_reg_table[i].name , "DSI1_VC_SHORT_PACKET_HEADER_2");
	dsi1_reg_table[i++].addr = DSI1_VC_SHORT_PACKET_HEADER_2;
	strcpy(dsi1_reg_table[i].name , "DSI1_VC_IRQSTATUS_2");
	dsi1_reg_table[i++].addr = DSI1_VC_IRQSTATUS_2;
	strcpy(dsi1_reg_table[i].name , "DSI1_VC_IRQENABLE_2");
	dsi1_reg_table[i++].addr = DSI1_VC_IRQENABLE_2;
	strcpy(dsi1_reg_table[i].name , "DSI1_VC_CTRL_3");
	dsi1_reg_table[i++].addr = DSI1_VC_CTRL_3;
	strcpy(dsi1_reg_table[i].name , "DSI1_VC_TE_3");
	dsi1_reg_table[i++].addr = DSI1_VC_TE_3;
	strcpy(dsi1_reg_table[i].name , "DSI1_VC_LONG_PACKET_HEADER_3");
	dsi1_reg_table[i++].addr = DSI1_VC_LONG_PACKET_HEADER_3;
	strcpy(dsi1_reg_table[i].name , "DSI1_VC_LONG_PACKET_PAYLOAD_3");
	dsi1_reg_table[i++].addr = DSI1_VC_LONG_PACKET_PAYLOAD_3;
	strcpy(dsi1_reg_table[i].name , "DSI1_VC_SHORT_PACKET_HEADER_3");
	dsi1_reg_table[i++].addr = DSI1_VC_SHORT_PACKET_HEADER_3;
	strcpy(dsi1_reg_table[i].name , "DSI1_VC_IRQSTATUS_3");
	dsi1_reg_table[i++].addr = DSI1_VC_IRQSTATUS_3;
	strcpy(dsi1_reg_table[i].name , "DSI1_VC_IRQENABLE_3");
	dsi1_reg_table[i++].addr = DSI1_VC_IRQENABLE_3;
	strcpy(dsi1_reg_table[i].name , "DSI1_VC_CTRL_4");
	dsi1_reg_table[i++].addr = DSI1_VC_CTRL_4;
	strcpy(dsi1_reg_table[i].name , "DSI1_VC_TE_4");
	dsi1_reg_table[i++].addr = DSI1_VC_TE_4;
	strcpy(dsi1_reg_table[i].name , "DSI1_VC_LONG_PACKET_HEADER_4");
	dsi1_reg_table[i++].addr = DSI1_VC_LONG_PACKET_HEADER_4;
	strcpy(dsi1_reg_table[i].name , "DSI1_VC_LONG_PACKET_PAYLOAD_4");
	dsi1_reg_table[i++].addr = DSI1_VC_LONG_PACKET_PAYLOAD_4;
	strcpy(dsi1_reg_table[i].name , "DSI1_VC_SHORT_PACKET_HEADER_4");
	dsi1_reg_table[i++].addr = DSI1_VC_SHORT_PACKET_HEADER_4;
	strcpy(dsi1_reg_table[i].name , "DSI1_VC_IRQSTATUS_4");
	dsi1_reg_table[i++].addr = DSI1_VC_IRQSTATUS_4;
	strcpy(dsi1_reg_table[i].name , "DSI1_VC_IRQENABLE_4");
	dsi1_reg_table[i++].addr = DSI1_VC_IRQENABLE_4;
	strcpy(dsi1_reg_table[i].name, "END");
	dsi1_reg_table[i].addr = 0;


	/* Init DSI1 PLL registers table */
	i = 0;
	strcpy(dsi1_pll_reg_table[i].name , "DSI1_PLL_CONTROL");
	dsi1_pll_reg_table[i++].addr = DSI1_PLL_CONTROL;
	strcpy(dsi1_pll_reg_table[i].name , "DSI1_PLL_STATUS");
	dsi1_pll_reg_table[i++].addr = DSI1_PLL_STATUS;
	strcpy(dsi1_pll_reg_table[i].name , "DSI1_PLL_GO");
	dsi1_pll_reg_table[i++].addr = DSI1_PLL_GO;
	strcpy(dsi1_pll_reg_table[i].name , "DSI1_PLL_CONFIGURATION1");
	dsi1_pll_reg_table[i++].addr = DSI1_PLL_CONFIGURATION1;
	strcpy(dsi1_pll_reg_table[i].name , "DSI1_PLL_CONFIGURATION2");
	dsi1_pll_reg_table[i++].addr = DSI1_PLL_CONFIGURATION2;
	strcpy(dsi1_pll_reg_table[i].name , "DSI1_PLL_CONFIGURATION3");
	dsi1_pll_reg_table[i++].addr = DSI1_PLL_CONFIGURATION3;
	strcpy(dsi1_pll_reg_table[i].name , "DSI1_PLL_SSC_CONFIGURATION1");
	dsi1_pll_reg_table[i++].addr = DSI1_PLL_SSC_CONFIGURATION1;
	strcpy(dsi1_pll_reg_table[i].name , "DSI1_PLL_SSC_CONFIGURATION2");
	dsi1_pll_reg_table[i++].addr = DSI1_PLL_SSC_CONFIGURATION2;
	strcpy(dsi1_pll_reg_table[i].name , "DSI1_PLL_CONFIG");
	dsi1_pll_reg_table[i++].addr = DSI1_PLL_CONFIG;
	strcpy(dsi1_pll_reg_table[i].name, "END");
	dsi1_pll_reg_table[i].addr = 0;

	/* Init DSI2 PE registers table */
	i = 0;
	strcpy(dsi2_reg_table[i].name , "DSI2_REVISION");
	dsi2_reg_table[i++].addr = DSI2_REVISION;
	strcpy(dsi2_reg_table[i].name , "DSI2_SYSCONFIG");
	dsi2_reg_table[i++].addr = DSI2_SYSCONFIG;
	strcpy(dsi2_reg_table[i].name , "DSI2_SYSSTATUS");
	dsi2_reg_table[i++].addr = DSI2_SYSSTATUS;
	strcpy(dsi2_reg_table[i].name , "DSI2_IRQSTATUS");
	dsi2_reg_table[i++].addr = DSI2_IRQSTATUS;
	strcpy(dsi2_reg_table[i].name , "DSI2_IRQENABLE");
	dsi2_reg_table[i++].addr = DSI2_IRQENABLE;
	strcpy(dsi2_reg_table[i].name , "DSI2_CTRL");
	dsi2_reg_table[i++].addr = DSI2_CTRL;
	strcpy(dsi2_reg_table[i].name , "DSI2_GNQ");
	dsi2_reg_table[i++].addr = DSI2_GNQ;
	strcpy(dsi2_reg_table[i].name , "DSI2_COMPLEXIO_CFG1");
	dsi2_reg_table[i++].addr = DSI2_COMPLEXIO_CFG1;
	strcpy(dsi2_reg_table[i].name , "DSI2_COMPLEXIO_IRQSTATUS");
	dsi2_reg_table[i++].addr = DSI2_COMPLEXIO_IRQSTATUS;
	strcpy(dsi2_reg_table[i].name , "DSI2_COMPLEXIO_IRQENABLE");
	dsi2_reg_table[i++].addr = DSI2_COMPLEXIO_IRQENABLE;
	strcpy(dsi2_reg_table[i].name , "DSI2_CLK_CTRL");
	dsi2_reg_table[i++].addr = DSI2_CLK_CTRL;
	strcpy(dsi2_reg_table[i].name , "DSI2_TIMING1");
	dsi2_reg_table[i++].addr = DSI2_TIMING1;
	strcpy(dsi2_reg_table[i].name , "DSI2_TIMING2");
	dsi2_reg_table[i++].addr = DSI2_TIMING2;
	strcpy(dsi2_reg_table[i].name , "DSI2_VM_TIMING1");
	dsi2_reg_table[i++].addr = DSI2_VM_TIMING1;
	strcpy(dsi2_reg_table[i].name , "DSI2_VM_TIMING2");
	dsi2_reg_table[i++].addr = DSI2_VM_TIMING2;
	strcpy(dsi2_reg_table[i].name , "DSI2_VM_TIMING3");
	dsi2_reg_table[i++].addr = DSI2_VM_TIMING3;
	strcpy(dsi2_reg_table[i].name , "DSI2_CLK_TIMING");
	dsi2_reg_table[i++].addr = DSI2_CLK_TIMING;
	strcpy(dsi2_reg_table[i].name , "DSI2_TX_FIFO_VC_SIZE");
	dsi2_reg_table[i++].addr = DSI2_TX_FIFO_VC_SIZE;
	strcpy(dsi2_reg_table[i].name , "DSI2_RX_FIFO_VC_SIZE");
	dsi2_reg_table[i++].addr = DSI2_RX_FIFO_VC_SIZE;
	strcpy(dsi2_reg_table[i].name , "DSI2_COMPLEXIO_CFG2");
	dsi2_reg_table[i++].addr = DSI2_COMPLEXIO_CFG2;
	strcpy(dsi2_reg_table[i].name , "DSI2_RX_FIFO_VC_FULLNESS");
	dsi2_reg_table[i++].addr = DSI2_RX_FIFO_VC_FULLNESS;
	strcpy(dsi2_reg_table[i].name , "DSI2_VM_TIMING4");
	dsi2_reg_table[i++].addr = DSI2_VM_TIMING4;
	strcpy(dsi2_reg_table[i].name , "DSI2_TX_FIFO_VC_EMPTINESS");
	dsi2_reg_table[i++].addr = DSI2_TX_FIFO_VC_EMPTINESS;
	strcpy(dsi2_reg_table[i].name , "DSI2_VM_TIMING5");
	dsi2_reg_table[i++].addr = DSI2_VM_TIMING5;
	strcpy(dsi2_reg_table[i].name , "DSI2_VM_TIMING6");
	dsi2_reg_table[i++].addr = DSI2_VM_TIMING6;
	strcpy(dsi2_reg_table[i].name , "DSI2_VM_TIMING7");
	dsi2_reg_table[i++].addr = DSI2_VM_TIMING7;
	strcpy(dsi2_reg_table[i].name , "DSI2_STOPCLK_TIMING");
	dsi2_reg_table[i++].addr = DSI2_STOPCLK_TIMING;
	strcpy(dsi2_reg_table[i].name , "DSI2_CTRL2");
	dsi2_reg_table[i++].addr = DSI2_CTRL2;
	strcpy(dsi2_reg_table[i].name , "DSI2_VM_TIMING8");
	dsi2_reg_table[i++].addr = DSI2_VM_TIMING8;
	strcpy(dsi2_reg_table[i].name , "DSI2_TE_HSYNC_WIDTH_0");
	dsi2_reg_table[i++].addr = DSI2_TE_HSYNC_WIDTH_0;
	strcpy(dsi2_reg_table[i].name , "DSI2_TE_VSYNC_WIDTH_0");
	dsi2_reg_table[i++].addr = DSI2_TE_VSYNC_WIDTH_0;
	strcpy(dsi2_reg_table[i].name , "DSI2_TE_HSYNC_NUMBER_0");
	dsi2_reg_table[i++].addr = DSI2_TE_HSYNC_NUMBER_0;
	strcpy(dsi2_reg_table[i].name , "DSI2_TE_HSYNC_WIDTH_1");
	dsi2_reg_table[i++].addr = DSI2_TE_HSYNC_WIDTH_1;
	strcpy(dsi2_reg_table[i].name , "DSI2_TE_VSYNC_WIDTH_1");
	dsi2_reg_table[i++].addr = DSI2_TE_VSYNC_WIDTH_1;
	strcpy(dsi2_reg_table[i].name , "DSI2_TE_HSYNC_NUMBER_1");
	dsi2_reg_table[i++].addr = DSI2_TE_HSYNC_NUMBER_1;
	strcpy(dsi2_reg_table[i].name , "DSI2_VC_CTRL_1");
	dsi2_reg_table[i++].addr = DSI2_VC_CTRL_1;
	strcpy(dsi2_reg_table[i].name , "DSI2_VC_TE_1");
	dsi2_reg_table[i++].addr = DSI2_VC_TE_1;
	strcpy(dsi2_reg_table[i].name , "DSI2_VC_LONG_PACKET_HEADER_1");
	dsi2_reg_table[i++].addr = DSI2_VC_LONG_PACKET_HEADER_1;
	strcpy(dsi2_reg_table[i].name , "DSI2_VC_LONG_PACKET_PAYLOAD_1");
	dsi2_reg_table[i++].addr = DSI2_VC_LONG_PACKET_PAYLOAD_1;
	strcpy(dsi2_reg_table[i].name , "DSI2_VC_SHORT_PACKET_HEADER_1");
	dsi2_reg_table[i++].addr = DSI2_VC_SHORT_PACKET_HEADER_1;
	strcpy(dsi2_reg_table[i].name , "DSI2_VC_IRQSTATUS_1");
	dsi2_reg_table[i++].addr = DSI2_VC_IRQSTATUS_1;
	strcpy(dsi2_reg_table[i].name , "DSI2_VC_IRQENABLE_1");
	dsi2_reg_table[i++].addr = DSI2_VC_IRQENABLE_1;
	strcpy(dsi2_reg_table[i].name , "DSI2_VC_CTRL_2");
	dsi2_reg_table[i++].addr = DSI2_VC_CTRL_2;
	strcpy(dsi2_reg_table[i].name , "DSI2_VC_TE_2");
	dsi2_reg_table[i++].addr = DSI2_VC_TE_2;
	strcpy(dsi2_reg_table[i].name , "DSI2_VC_LONG_PACKET_HEADER_2");
	dsi2_reg_table[i++].addr = DSI2_VC_LONG_PACKET_HEADER_2;
	strcpy(dsi2_reg_table[i].name , "DSI2_VC_LONG_PACKET_PAYLOAD_2");
	dsi2_reg_table[i++].addr = DSI2_VC_LONG_PACKET_PAYLOAD_2;
	strcpy(dsi2_reg_table[i].name , "DSI2_VC_SHORT_PACKET_HEADER_2");
	dsi2_reg_table[i++].addr = DSI2_VC_SHORT_PACKET_HEADER_2;
	strcpy(dsi2_reg_table[i].name , "DSI2_VC_IRQSTATUS_2");
	dsi2_reg_table[i++].addr = DSI2_VC_IRQSTATUS_2;
	strcpy(dsi2_reg_table[i].name , "DSI2_VC_IRQENABLE_2");
	dsi2_reg_table[i++].addr = DSI2_VC_IRQENABLE_2;
	strcpy(dsi2_reg_table[i].name , "DSI2_VC_CTRL_3");
	dsi2_reg_table[i++].addr = DSI2_VC_CTRL_3;
	strcpy(dsi2_reg_table[i].name , "DSI2_VC_TE_3");
	dsi2_reg_table[i++].addr = DSI2_VC_TE_3;
	strcpy(dsi2_reg_table[i].name , "DSI2_VC_LONG_PACKET_HEADER_3");
	dsi2_reg_table[i++].addr = DSI2_VC_LONG_PACKET_HEADER_3;
	strcpy(dsi2_reg_table[i].name , "DSI2_VC_LONG_PACKET_PAYLOAD_3");
	dsi2_reg_table[i++].addr = DSI2_VC_LONG_PACKET_PAYLOAD_3;
	strcpy(dsi2_reg_table[i].name , "DSI2_VC_SHORT_PACKET_HEADER_3");
	dsi2_reg_table[i++].addr = DSI2_VC_SHORT_PACKET_HEADER_3;
	strcpy(dsi2_reg_table[i].name , "DSI2_VC_IRQSTATUS_3");
	dsi2_reg_table[i++].addr = DSI2_VC_IRQSTATUS_3;
	strcpy(dsi2_reg_table[i].name , "DSI2_VC_IRQENABLE_3");
	dsi2_reg_table[i++].addr = DSI2_VC_IRQENABLE_3;
	strcpy(dsi2_reg_table[i].name , "DSI2_VC_CTRL_4");
	dsi2_reg_table[i++].addr = DSI2_VC_CTRL_4;
	strcpy(dsi2_reg_table[i].name , "DSI2_VC_TE_4");
	dsi2_reg_table[i++].addr = DSI2_VC_TE_4;
	strcpy(dsi2_reg_table[i].name , "DSI2_VC_LONG_PACKET_HEADER_4");
	dsi2_reg_table[i++].addr = DSI2_VC_LONG_PACKET_HEADER_4;
	strcpy(dsi2_reg_table[i].name , "DSI2_VC_LONG_PACKET_PAYLOAD_4");
	dsi2_reg_table[i++].addr = DSI2_VC_LONG_PACKET_PAYLOAD_4;
	strcpy(dsi2_reg_table[i].name , "DSI2_VC_SHORT_PACKET_HEADER_4");
	dsi2_reg_table[i++].addr = DSI2_VC_SHORT_PACKET_HEADER_4;
	strcpy(dsi2_reg_table[i].name , "DSI2_VC_IRQSTATUS_4");
	dsi2_reg_table[i++].addr = DSI2_VC_IRQSTATUS_4;
	strcpy(dsi2_reg_table[i].name , "DSI2_VC_IRQENABLE_4");
	dsi2_reg_table[i++].addr = DSI2_VC_IRQENABLE_4;
	strcpy(dsi2_reg_table[i].name, "END");
	dsi2_reg_table[i].addr = 0;

	/* Init DSI2 PHY registers table */
	i = 0;
	strcpy(dsi2_phy_reg_table[i].name , "DSI2_PHY_REGISTER0");
	dsi2_phy_reg_table[i++].addr = DSI2_PHY_REGISTER0;
	strcpy(dsi2_phy_reg_table[i].name , "DSI2_PHY_REGISTER1");
	dsi2_phy_reg_table[i++].addr = DSI2_PHY_REGISTER1;
	strcpy(dsi2_phy_reg_table[i].name , "DSI2_PHY_REGISTER2");
	dsi2_phy_reg_table[i++].addr = DSI2_PHY_REGISTER2;
	strcpy(dsi2_phy_reg_table[i].name , "DSI2_PHY_REGISTER3");
	dsi2_phy_reg_table[i++].addr = DSI2_PHY_REGISTER3;
	strcpy(dsi2_phy_reg_table[i].name , "DSI2_PHY_REGISTER4");
	dsi2_phy_reg_table[i++].addr = DSI2_PHY_REGISTER4;
	strcpy(dsi2_phy_reg_table[i].name , "DSI2_PHY_REGISTER5");
	dsi2_phy_reg_table[i++].addr = DSI2_PHY_REGISTER5;
	strcpy(dsi2_phy_reg_table[i].name, "END");
	dsi2_phy_reg_table[i].addr = 0;

	/* Init DSI2 PLL registers table */
	i = 0;
	strcpy(dsi2_pll_reg_table[i].name , "DSI2_PLL_CONTROL");
	dsi2_pll_reg_table[i++].addr = DSI2_PLL_CONTROL;
	strcpy(dsi2_pll_reg_table[i].name , "DSI2_PLL_STATUS");
	dsi2_pll_reg_table[i++].addr = DSI2_PLL_STATUS;
	strcpy(dsi2_pll_reg_table[i].name , "DSI2_PLL_GO");
	dsi2_pll_reg_table[i++].addr = DSI2_PLL_GO;
	strcpy(dsi2_pll_reg_table[i].name , "DSI2_PLL_CONFIGURATION1");
	dsi2_pll_reg_table[i++].addr = DSI2_PLL_CONFIGURATION1;
	strcpy(dsi2_pll_reg_table[i].name , "DSI2_PLL_CONFIGURATION2");
	dsi2_pll_reg_table[i++].addr = DSI2_PLL_CONFIGURATION2;
	strcpy(dsi2_pll_reg_table[i].name , "DSI2_PLL_CONFIGURATION3");
	dsi2_pll_reg_table[i++].addr = DSI2_PLL_CONFIGURATION3;
	strcpy(dsi2_pll_reg_table[i].name , "DSI2_PLL_SSC_CONFIGURATION1");
	dsi2_pll_reg_table[i++].addr = DSI2_PLL_SSC_CONFIGURATION1;
	strcpy(dsi2_pll_reg_table[i].name , "DSI2_PLL_SSC_CONFIGURATION2");
	dsi2_pll_reg_table[i++].addr = DSI2_PLL_SSC_CONFIGURATION2;
	strcpy(dsi2_pll_reg_table[i].name , "DSI2_PLL_CONFIG");
	dsi2_pll_reg_table[i++].addr = DSI2_PLL_CONFIG;
	strcpy(dsi2_pll_reg_table[i].name, "END");
	dsi2_pll_reg_table[i].addr = 0;

	/* Init RFBI registers table */
	i = 0;
	strcpy(rfbi_reg_table[i].name , "RFBI_REVISION");
	rfbi_reg_table[i++].addr = RFBI_REVISION;
	strcpy(rfbi_reg_table[i].name , "RFBI_SYSCONFIG");
	rfbi_reg_table[i++].addr = RFBI_SYSCONFIG;
	strcpy(rfbi_reg_table[i].name , "RFBI_SYSSTATUS");
	rfbi_reg_table[i++].addr = RFBI_SYSSTATUS;
	strcpy(rfbi_reg_table[i].name , "RFBI_CONTROL");
	rfbi_reg_table[i++].addr = RFBI_CONTROL;
	strcpy(rfbi_reg_table[i].name , "RFBI_PIXEL_CNT");
	rfbi_reg_table[i++].addr = RFBI_PIXEL_CNT;
	strcpy(rfbi_reg_table[i].name , "RFBI_LINE_NUMBER");
	rfbi_reg_table[i++].addr = RFBI_LINE_NUMBER;
	strcpy(rfbi_reg_table[i].name , "RFBI_CMD");
	rfbi_reg_table[i++].addr = RFBI_CMD;
	strcpy(rfbi_reg_table[i].name , "RFBI_PARAM");
	rfbi_reg_table[i++].addr = RFBI_PARAM;
	strcpy(rfbi_reg_table[i].name , "RFBI_DATA");
	rfbi_reg_table[i++].addr = RFBI_DATA;
	strcpy(rfbi_reg_table[i].name , "RFBI_READ");
	rfbi_reg_table[i++].addr = RFBI_READ;
	strcpy(rfbi_reg_table[i].name , "RFBI_STATUS");
	rfbi_reg_table[i++].addr = RFBI_STATUS;
	strcpy(rfbi_reg_table[i].name , "RFBI_CONFIG");
	rfbi_reg_table[i++].addr = RFBI_CONFIG;
	strcpy(rfbi_reg_table[i].name , "RFBI_ONOFF_TIME");
	rfbi_reg_table[i++].addr = RFBI_ONOFF_TIME;
	strcpy(rfbi_reg_table[i].name , "RFBI_CYCLE_TIME");
	rfbi_reg_table[i++].addr = RFBI_CYCLE_TIME;
	strcpy(rfbi_reg_table[i].name , "RFBI_DATA_CYCLE0");
	rfbi_reg_table[i++].addr = RFBI_DATA_CYCLE0;
	strcpy(rfbi_reg_table[i].name , "RFBI_DATA_CYCLE1");
	rfbi_reg_table[i++].addr = RFBI_DATA_CYCLE1;
	strcpy(rfbi_reg_table[i].name , "RFBI_DATA_CYCLE2");
	rfbi_reg_table[i++].addr = RFBI_DATA_CYCLE2;
	strcpy(rfbi_reg_table[i].name , "RFBI_DATA_CYCLE3");
	rfbi_reg_table[i++].addr = RFBI_DATA_CYCLE3;
	strcpy(rfbi_reg_table[i].name , "RFBI_DATA_CYCLE4");
	rfbi_reg_table[i++].addr = RFBI_DATA_CYCLE4;
	strcpy(rfbi_reg_table[i].name , "RFBI_DATA_CYCLE5");
	rfbi_reg_table[i++].addr = RFBI_DATA_CYCLE5;
	strcpy(rfbi_reg_table[i].name , "RFBI_DATA_CYCLE6");
	rfbi_reg_table[i++].addr = RFBI_DATA_CYCLE6;
	strcpy(rfbi_reg_table[i].name , "RFBI_DATA_CYCLE7");
	rfbi_reg_table[i++].addr = RFBI_DATA_CYCLE7;
	strcpy(rfbi_reg_table[i].name , "RFBI_VSYNC_WIDTH");
	rfbi_reg_table[i++].addr = RFBI_VSYNC_WIDTH;
	strcpy(rfbi_reg_table[i].name , "RFBI_HSYNC_WIDTH");
	rfbi_reg_table[i++].addr = RFBI_HSYNC_WIDTH;
	strcpy(rfbi_reg_table[i].name, "END");
	rfbi_reg_table[i].addr = 0;

	/* Init VENC registers table */
	i = 0;
	strcpy(venc_reg_table[i].name , "VENC_REV_ID");
	venc_reg_table[i++].addr = VENC_REV_ID;
	strcpy(venc_reg_table[i].name , "VENC_STATUS");
	venc_reg_table[i++].addr = VENC_STATUS;
	strcpy(venc_reg_table[i].name , "VENC_F_CONTROL");
	venc_reg_table[i++].addr = VENC_F_CONTROL;
	strcpy(venc_reg_table[i].name , "VENC_VIDOUT_CTRL");
	venc_reg_table[i++].addr = VENC_VIDOUT_CTRL;
	strcpy(venc_reg_table[i].name , "VENC_SYNC_CTRL");
	venc_reg_table[i++].addr = VENC_SYNC_CTRL;
	strcpy(venc_reg_table[i].name , "VENC_LLEN");
	venc_reg_table[i++].addr = VENC_LLEN;
	strcpy(venc_reg_table[i].name , "VENC_FLENS");
	venc_reg_table[i++].addr = VENC_FLENS;
	strcpy(venc_reg_table[i].name , "VENC_HFLTR_CTRL");
	venc_reg_table[i++].addr = VENC_HFLTR_CTRL;
	strcpy(venc_reg_table[i].name , "VENC_CC_CARR_WSS_CARR");
	venc_reg_table[i++].addr = VENC_CC_CARR_WSS_CARR;
	strcpy(venc_reg_table[i].name , "VENC_C_PHASE");
	venc_reg_table[i++].addr = VENC_C_PHASE;
	strcpy(venc_reg_table[i].name , "VENC_GAIN_U");
	venc_reg_table[i++].addr = VENC_GAIN_U;
	strcpy(venc_reg_table[i].name , "VENC_GAIN_V");
	venc_reg_table[i++].addr = VENC_GAIN_V;
	strcpy(venc_reg_table[i].name , "VENC_GAIN_Y");
	venc_reg_table[i++].addr = VENC_GAIN_Y;
	strcpy(venc_reg_table[i].name , "VENC_BLACK_LEVEL");
	venc_reg_table[i++].addr = VENC_BLACK_LEVEL;
	strcpy(venc_reg_table[i].name , "VENC_BLANK_LEVEL");
	venc_reg_table[i++].addr = VENC_BLANK_LEVEL;
	strcpy(venc_reg_table[i].name , "VENC_X_COLOR");
	venc_reg_table[i++].addr = VENC_X_COLOR;
	strcpy(venc_reg_table[i].name , "VENC_M_CONTROL");
	venc_reg_table[i++].addr = VENC_M_CONTROL;
	strcpy(venc_reg_table[i].name , "VENC_BSTAMP_WSS_DATA");
	venc_reg_table[i++].addr = VENC_BSTAMP_WSS_DATA;
	strcpy(venc_reg_table[i].name , "VENC_S_CARR");
	venc_reg_table[i++].addr = VENC_S_CARR;
	strcpy(venc_reg_table[i].name , "VENC_LINE21");
	venc_reg_table[i++].addr = VENC_LINE21;
	strcpy(venc_reg_table[i].name , "VENC_LN_SEL");
	venc_reg_table[i++].addr = VENC_LN_SEL;
	strcpy(venc_reg_table[i].name , "VENC_L21_WC_CTL");
	venc_reg_table[i++].addr = VENC_L21_WC_CTL;
	strcpy(venc_reg_table[i].name , "VENC_HTRIGGER_VTRIGGER");
	venc_reg_table[i++].addr = VENC_HTRIGGER_VTRIGGER;
	strcpy(venc_reg_table[i].name , "VENC_SAVID_EAVID");
	venc_reg_table[i++].addr = VENC_SAVID_EAVID;
	strcpy(venc_reg_table[i].name , "VENC_FLEN_FAL");
	venc_reg_table[i++].addr = VENC_FLEN_FAL;
	strcpy(venc_reg_table[i].name , "VENC_LAL_PHASE_RESET");
	venc_reg_table[i++].addr = VENC_LAL_PHASE_RESET;
	strcpy(venc_reg_table[i].name , "VENC_HS_INT_START_STOP_X");
	venc_reg_table[i++].addr = VENC_HS_INT_START_STOP_X;
	strcpy(venc_reg_table[i].name , "VENC_HS_EXT_START_STOP_X");
	venc_reg_table[i++].addr = VENC_HS_EXT_START_STOP_X;
	strcpy(venc_reg_table[i].name , "VENC_VS_INT_START_X");
	venc_reg_table[i++].addr = VENC_VS_INT_START_X;
	strcpy(venc_reg_table[i].name , "VENC_VS_INT_STOP_X_VS_INT_START_Y");
	venc_reg_table[i++].addr = VENC_VS_INT_STOP_X_VS_INT_START_Y;
	strcpy(venc_reg_table[i].name , "VENC_VS_INT_STOP_Y_VS_EXT_START_X");
	venc_reg_table[i++].addr = VENC_VS_INT_STOP_Y_VS_EXT_START_X;
	strcpy(venc_reg_table[i].name , "VENC_VS_EXT_STOP_X_VS_EXT_START_Y");
	venc_reg_table[i++].addr = VENC_VS_EXT_STOP_X_VS_EXT_START_Y;
	strcpy(venc_reg_table[i].name , "VENC_VS_EXT_STOP_Y");
	venc_reg_table[i++].addr = VENC_VS_EXT_STOP_Y;
	strcpy(venc_reg_table[i].name , "VENC_AVID_START_STOP_X");
	venc_reg_table[i++].addr = VENC_AVID_START_STOP_X;
	strcpy(venc_reg_table[i].name , "VENC_AVID_START_STOP_Y");
	venc_reg_table[i++].addr = VENC_AVID_START_STOP_Y;
	strcpy(venc_reg_table[i].name , "VENC_FID_INT_START_X_FID_INT_START_Y");
	venc_reg_table[i++].addr = VENC_FID_INT_START_X_FID_INT_START_Y;
	strcpy(venc_reg_table[i].name ,
		"VENC_FID_INT_OFFSET_Y_FID_EXT_START_X");
	venc_reg_table[i++].addr = VENC_FID_INT_OFFSET_Y_FID_EXT_START_X;
	strcpy(venc_reg_table[i].name ,
		"VENC_FID_EXT_START_Y_FID_EXT_OFFSET_Y");
	venc_reg_table[i++].addr = VENC_FID_EXT_START_Y_FID_EXT_OFFSET_Y;
	strcpy(venc_reg_table[i].name , "VENC_TVDETGP_INT_START_STOP_X");
	venc_reg_table[i++].addr = VENC_TVDETGP_INT_START_STOP_X;
	strcpy(venc_reg_table[i].name , "VENC_TVDETGP_INT_START_STOP_Y");
	venc_reg_table[i++].addr = VENC_TVDETGP_INT_START_STOP_Y;
	strcpy(venc_reg_table[i].name , "VENC_GEN_CTRL");
	venc_reg_table[i++].addr = VENC_GEN_CTRL;
	strcpy(venc_reg_table[i].name , "VENC_OUTPUT_CONTROL");
	venc_reg_table[i++].addr = VENC_OUTPUT_CONTROL;
	strcpy(venc_reg_table[i].name , "VENC_OUTPUT_TEST");
	venc_reg_table[i++].addr = VENC_OUTPUT_TEST;
	strcpy(venc_reg_table[i].name, "END");
	venc_reg_table[i].addr = 0;

	/* Init DISPC registers table */
	 i = 0;
	strcpy(dispc_reg_table[i].name , "DISPC_REVISION");
	dispc_reg_table[i++].addr = DISPC_REVISION;
	strcpy(dispc_reg_table[i].name , "DISPC_SYSCONFIG");
	dispc_reg_table[i++].addr = DISPC_SYSCONFIG;
	strcpy(dispc_reg_table[i].name , "DISPC_SYSSTATUS");
	dispc_reg_table[i++].addr = DISPC_SYSSTATUS;
	strcpy(dispc_reg_table[i].name , "DISPC_IRQSTATUS");
	dispc_reg_table[i++].addr = DISPC_IRQSTATUS;
	strcpy(dispc_reg_table[i].name , "DISPC_IRQENABLE");
	dispc_reg_table[i++].addr = DISPC_IRQENABLE;
	strcpy(dispc_reg_table[i].name , "DISPC_CONTROL1");
	dispc_reg_table[i++].addr = DISPC_CONTROL1;
	strcpy(dispc_reg_table[i].name , "DISPC_CONFIG1");
	dispc_reg_table[i++].addr = DISPC_CONFIG1;
	strcpy(dispc_reg_table[i].name , "DISPC_DEFAULT_COLOR0");
	dispc_reg_table[i++].addr = DISPC_DEFAULT_COLOR0;
	strcpy(dispc_reg_table[i].name , "DISPC_DEFAULT_COLOR1");
	dispc_reg_table[i++].addr = DISPC_DEFAULT_COLOR1;
	strcpy(dispc_reg_table[i].name , "DISPC_TRANS_COLOR0");
	dispc_reg_table[i++].addr = DISPC_TRANS_COLOR0;
	strcpy(dispc_reg_table[i].name , "DISPC_TRANS_COLOR1");
	dispc_reg_table[i++].addr = DISPC_TRANS_COLOR1;
	strcpy(dispc_reg_table[i].name , "DISPC_LINE_STATUS");
	dispc_reg_table[i++].addr = DISPC_LINE_STATUS;
	strcpy(dispc_reg_table[i].name , "DISPC_LINE_NUMBER");
	dispc_reg_table[i++].addr = DISPC_LINE_NUMBER;
	strcpy(dispc_reg_table[i].name , "DISPC_TIMING_H1");
	dispc_reg_table[i++].addr = DISPC_TIMING_H1;
	strcpy(dispc_reg_table[i].name , "DISPC_TIMING_V1");
	dispc_reg_table[i++].addr = DISPC_TIMING_V1;
	strcpy(dispc_reg_table[i].name , "DISPC_POL_FREQ1");
	dispc_reg_table[i++].addr = DISPC_POL_FREQ1;
	strcpy(dispc_reg_table[i].name , "DISPC_DIVISOR1");
	dispc_reg_table[i++].addr = DISPC_DIVISOR1;
	strcpy(dispc_reg_table[i].name , "DISPC_GLOBAL_ALPHA");
	dispc_reg_table[i++].addr = DISPC_GLOBAL_ALPHA;
	strcpy(dispc_reg_table[i].name , "DISPC_SIZE_TV");
	dispc_reg_table[i++].addr = DISPC_SIZE_TV;
	strcpy(dispc_reg_table[i].name , "DISPC_SIZE_LCD1");
	dispc_reg_table[i++].addr = DISPC_SIZE_LCD1;
	strcpy(dispc_reg_table[i].name , "DISPC_GFX_BA_0");
	dispc_reg_table[i++].addr = DISPC_GFX_BA_0;
	strcpy(dispc_reg_table[i].name , "DISPC_GFX_BA_1");
	dispc_reg_table[i++].addr = DISPC_GFX_BA_1;
	strcpy(dispc_reg_table[i].name , "DISPC_GFX_POSITION");
	dispc_reg_table[i++].addr = DISPC_GFX_POSITION;
	strcpy(dispc_reg_table[i].name , "DISPC_GFX_SIZE");
	dispc_reg_table[i++].addr = DISPC_GFX_SIZE;
	strcpy(dispc_reg_table[i].name , "DISPC_GFX_ATTRIBUTES");
	dispc_reg_table[i++].addr = DISPC_GFX_ATTRIBUTES;
	strcpy(dispc_reg_table[i].name , "DISPC_GFX_BUF_THRESHOLD");
	dispc_reg_table[i++].addr = DISPC_GFX_BUF_THRESHOLD;
	strcpy(dispc_reg_table[i].name , "DISPC_GFX_BUF_SIZE_STATUS");
	dispc_reg_table[i++].addr = DISPC_GFX_BUF_SIZE_STATUS;
	strcpy(dispc_reg_table[i].name , "DISPC_GFX_ROW_INC");
	dispc_reg_table[i++].addr = DISPC_GFX_ROW_INC;
	strcpy(dispc_reg_table[i].name , "DISPC_GFX_PIXEL_INC");
	dispc_reg_table[i++].addr = DISPC_GFX_PIXEL_INC;
	strcpy(dispc_reg_table[i].name , "DISPC_GFX_WINDOW_SKIP");
	dispc_reg_table[i++].addr = DISPC_GFX_WINDOW_SKIP;
	strcpy(dispc_reg_table[i].name , "DISPC_GFX_TABLE_BA");
	dispc_reg_table[i++].addr = DISPC_GFX_TABLE_BA;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_BA_0");
	dispc_reg_table[i++].addr = DISPC_VID1_BA_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_BA_1");
	dispc_reg_table[i++].addr = DISPC_VID1_BA_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_POSITION");
	dispc_reg_table[i++].addr = DISPC_VID1_POSITION;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_SIZE");
	dispc_reg_table[i++].addr = DISPC_VID1_SIZE;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_ATTRIBUTES");
	dispc_reg_table[i++].addr = DISPC_VID1_ATTRIBUTES;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_BUF_THRESHOLD");
	dispc_reg_table[i++].addr = DISPC_VID1_BUF_THRESHOLD;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_BUF_SIZE_STATUS");
	dispc_reg_table[i++].addr = DISPC_VID1_BUF_SIZE_STATUS;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_ROW_INC");
	dispc_reg_table[i++].addr = DISPC_VID1_ROW_INC;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_PIXEL_INC");
	dispc_reg_table[i++].addr = DISPC_VID1_PIXEL_INC;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_PICTURE_SIZE");
	dispc_reg_table[i++].addr = DISPC_VID1_PICTURE_SIZE;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_ACCU_0");
	dispc_reg_table[i++].addr = DISPC_VID1_ACCU_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_ACCU_1");
	dispc_reg_table[i++].addr = DISPC_VID1_ACCU_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR_COEF_H_0");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR_COEF_H_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR_COEF_H_1");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR_COEF_H_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR_COEF_H_2");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR_COEF_H_2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR_COEF_H_3");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR_COEF_H_3;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR_COEF_H_4");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR_COEF_H_4;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR_COEF_H_5");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR_COEF_H_5;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR_COEF_H_6");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR_COEF_H_6;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR_COEF_H_7");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR_COEF_H_7;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR_COEF_HV_0");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR_COEF_HV_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR_COEF_HV_1");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR_COEF_HV_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR_COEF_HV_2");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR_COEF_HV_2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR_COEF_HV_3");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR_COEF_HV_3;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR_COEF_HV_4");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR_COEF_HV_4;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR_COEF_HV_5");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR_COEF_HV_5;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR_COEF_HV_6");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR_COEF_HV_6;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR_COEF_HV_7");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR_COEF_HV_7;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_CONV_COEF0");
	dispc_reg_table[i++].addr = DISPC_VID1_CONV_COEF0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_CONV_COEF1");
	dispc_reg_table[i++].addr = DISPC_VID1_CONV_COEF1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_CONV_COEF2");
	dispc_reg_table[i++].addr = DISPC_VID1_CONV_COEF2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_CONV_COEF3");
	dispc_reg_table[i++].addr = DISPC_VID1_CONV_COEF3;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_CONV_COEF4");
	dispc_reg_table[i++].addr = DISPC_VID1_CONV_COEF4;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_BA_0");
	dispc_reg_table[i++].addr = DISPC_VID2_BA_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_BA_1");
	dispc_reg_table[i++].addr = DISPC_VID2_BA_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_POSITION");
	dispc_reg_table[i++].addr = DISPC_VID2_POSITION;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_SIZE");
	dispc_reg_table[i++].addr = DISPC_VID2_SIZE;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_ATTRIBUTES");
	dispc_reg_table[i++].addr = DISPC_VID2_ATTRIBUTES;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_BUF_THRESHOLD");
	dispc_reg_table[i++].addr = DISPC_VID2_BUF_THRESHOLD;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_BUF_SIZE_STATUS");
	dispc_reg_table[i++].addr = DISPC_VID2_BUF_SIZE_STATUS;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_ROW_INC");
	dispc_reg_table[i++].addr = DISPC_VID2_ROW_INC;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_PIXEL_INC");
	dispc_reg_table[i++].addr = DISPC_VID2_PIXEL_INC;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_PICTURE_SIZE");
	dispc_reg_table[i++].addr = DISPC_VID2_PICTURE_SIZE;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_ACCU_0");
	dispc_reg_table[i++].addr = DISPC_VID2_ACCU_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_ACCU_1");
	dispc_reg_table[i++].addr = DISPC_VID2_ACCU_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR_COEF_H_0");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR_COEF_H_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR_COEF_H_1");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR_COEF_H_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR_COEF_H_2");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR_COEF_H_2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR_COEF_H_3");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR_COEF_H_3;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR_COEF_H_4");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR_COEF_H_4;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR_COEF_H_5");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR_COEF_H_5;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR_COEF_H_6");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR_COEF_H_6;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR_COEF_H_7");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR_COEF_H_7;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR_COEF_HV_0");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR_COEF_HV_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR_COEF_HV_1");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR_COEF_HV_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR_COEF_HV_2");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR_COEF_HV_2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR_COEF_HV_3");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR_COEF_HV_3;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR_COEF_HV_4");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR_COEF_HV_4;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR_COEF_HV_5");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR_COEF_HV_5;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR_COEF_HV_6");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR_COEF_HV_6;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR_COEF_HV_7");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR_COEF_HV_7;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_CONV_COEF0");
	dispc_reg_table[i++].addr = DISPC_VID2_CONV_COEF0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_CONV_COEF1");
	dispc_reg_table[i++].addr = DISPC_VID2_CONV_COEF1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_CONV_COEF2");
	dispc_reg_table[i++].addr = DISPC_VID2_CONV_COEF2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_CONV_COEF3");
	dispc_reg_table[i++].addr = DISPC_VID2_CONV_COEF3;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_CONV_COEF4");
	dispc_reg_table[i++].addr = DISPC_VID2_CONV_COEF4;
	strcpy(dispc_reg_table[i].name , "DISPC_DATA1_CYCLE1");
	dispc_reg_table[i++].addr = DISPC_DATA1_CYCLE1;
	strcpy(dispc_reg_table[i].name , "DISPC_DATA1_CYCLE2");
	dispc_reg_table[i++].addr = DISPC_DATA1_CYCLE2;
	strcpy(dispc_reg_table[i].name , "DISPC_DATA1_CYCLE3");
	dispc_reg_table[i++].addr = DISPC_DATA1_CYCLE3;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR_COEF_V_0");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR_COEF_V_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR_COEF_V_1");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR_COEF_V_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR_COEF_V_2");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR_COEF_V_2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR_COEF_V_3");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR_COEF_V_3;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR_COEF_V_4");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR_COEF_V_4;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR_COEF_V_5");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR_COEF_V_5;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR_COEF_V_6");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR_COEF_V_6;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR_COEF_V_7");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR_COEF_V_7;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR_COEF_V_0");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR_COEF_V_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR_COEF_V_1");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR_COEF_V_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR_COEF_V_2");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR_COEF_V_2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR_COEF_V_3");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR_COEF_V_3;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR_COEF_V_4");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR_COEF_V_4;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR_COEF_V_5");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR_COEF_V_5;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR_COEF_V_6");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR_COEF_V_6;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR_COEF_V_7");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR_COEF_V_7;
	strcpy(dispc_reg_table[i].name , "DISPC_CPR1_COEF_R");
	dispc_reg_table[i++].addr = DISPC_CPR1_COEF_R;
	strcpy(dispc_reg_table[i].name , "DISPC_CPR1_COEF_G");
	dispc_reg_table[i++].addr = DISPC_CPR1_COEF_G;
	strcpy(dispc_reg_table[i].name , "DISPC_CPR1_COEF_B");
	dispc_reg_table[i++].addr = DISPC_CPR1_COEF_B;
	strcpy(dispc_reg_table[i].name , "DISPC_GFX_PRELOAD");
	dispc_reg_table[i++].addr = DISPC_GFX_PRELOAD;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_PRELOAD");
	dispc_reg_table[i++].addr = DISPC_VID1_PRELOAD;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_PRELOAD");
	dispc_reg_table[i++].addr = DISPC_VID2_PRELOAD;
	strcpy(dispc_reg_table[i].name , "DISPC_CONTROL2");
	dispc_reg_table[i++].addr = DISPC_CONTROL2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_ACCU_0");
	dispc_reg_table[i++].addr = DISPC_VID3_ACCU_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_ACCU_1");
	dispc_reg_table[i++].addr = DISPC_VID3_ACCU_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_BA_0");
	dispc_reg_table[i++].addr = DISPC_VID3_BA_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_BA_1");
	dispc_reg_table[i++].addr = DISPC_VID3_BA_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR_COEF_H_0");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR_COEF_H_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR_COEF_H_1");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR_COEF_H_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR_COEF_H_2");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR_COEF_H_2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR_COEF_H_3");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR_COEF_H_3;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR_COEF_H_4");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR_COEF_H_4;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR_COEF_H_5");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR_COEF_H_5;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR_COEF_H_6");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR_COEF_H_6;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR_COEF_H_7");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR_COEF_H_7;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR_COEF_HV_0");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR_COEF_HV_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR_COEF_HV_1");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR_COEF_HV_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR_COEF_HV_2");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR_COEF_HV_2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR_COEF_HV_3");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR_COEF_HV_3;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR_COEF_HV_4");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR_COEF_HV_4;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR_COEF_HV_5");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR_COEF_HV_5;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR_COEF_HV_6");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR_COEF_HV_6;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR_COEF_HV_7");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR_COEF_HV_7;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR_COEF_V_0");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR_COEF_V_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR_COEF_V_1");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR_COEF_V_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR_COEF_V_2");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR_COEF_V_2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR_COEF_V_3");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR_COEF_V_3;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR_COEF_V_4");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR_COEF_V_4;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR_COEF_V_5");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR_COEF_V_5;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR_COEF_V_6");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR_COEF_V_6;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR_COEF_V_7");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR_COEF_V_7;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_ATTRIBUTES");
	dispc_reg_table[i++].addr = DISPC_VID3_ATTRIBUTES;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_CONV_COEF0");
	dispc_reg_table[i++].addr = DISPC_VID3_CONV_COEF0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_CONV_COEF1");
	dispc_reg_table[i++].addr = DISPC_VID3_CONV_COEF1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_CONV_COEF2");
	dispc_reg_table[i++].addr = DISPC_VID3_CONV_COEF2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_CONV_COEF3");
	dispc_reg_table[i++].addr = DISPC_VID3_CONV_COEF3;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_CONV_COEF4");
	dispc_reg_table[i++].addr = DISPC_VID3_CONV_COEF4;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_BUF_SIZE_STATUS");
	dispc_reg_table[i++].addr = DISPC_VID3_BUF_SIZE_STATUS;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_BUF_THRESHOLD");
	dispc_reg_table[i++].addr = DISPC_VID3_BUF_THRESHOLD;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_PICTURE_SIZE");
	dispc_reg_table[i++].addr = DISPC_VID3_PICTURE_SIZE;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_PIXEL_INC");
	dispc_reg_table[i++].addr = DISPC_VID3_PIXEL_INC;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_POSITION");
	dispc_reg_table[i++].addr = DISPC_VID3_POSITION;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_PRELOAD");
	dispc_reg_table[i++].addr = DISPC_VID3_PRELOAD;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_ROW_INC");
	dispc_reg_table[i++].addr = DISPC_VID3_ROW_INC;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_SIZE");
	dispc_reg_table[i++].addr = DISPC_VID3_SIZE;
	strcpy(dispc_reg_table[i].name , "DISPC_DEFAULT_COLOR2");
	dispc_reg_table[i++].addr = DISPC_DEFAULT_COLOR2;
	strcpy(dispc_reg_table[i].name , "DISPC_TRANS_COLOR2");
	dispc_reg_table[i++].addr = DISPC_TRANS_COLOR2;
	strcpy(dispc_reg_table[i].name , "DISPC_CPR2_COEF_B");
	dispc_reg_table[i++].addr = DISPC_CPR2_COEF_B;
	strcpy(dispc_reg_table[i].name , "DISPC_CPR2_COEF_G");
	dispc_reg_table[i++].addr = DISPC_CPR2_COEF_G;
	strcpy(dispc_reg_table[i].name , "DISPC_CPR2_COEF_R");
	dispc_reg_table[i++].addr = DISPC_CPR2_COEF_R;
	strcpy(dispc_reg_table[i].name , "DISPC_DATA2_CYCLE1");
	dispc_reg_table[i++].addr = DISPC_DATA2_CYCLE1;
	strcpy(dispc_reg_table[i].name , "DISPC_DATA2_CYCLE2");
	dispc_reg_table[i++].addr = DISPC_DATA2_CYCLE2;
	strcpy(dispc_reg_table[i].name , "DISPC_DATA2_CYCLE3");
	dispc_reg_table[i++].addr = DISPC_DATA2_CYCLE3;
	strcpy(dispc_reg_table[i].name , "DISPC_SIZE_LCD2");
	dispc_reg_table[i++].addr = DISPC_SIZE_LCD2;
	strcpy(dispc_reg_table[i].name , "DISPC_TIMING_H2");
	dispc_reg_table[i++].addr = DISPC_TIMING_H2;
	strcpy(dispc_reg_table[i].name , "DISPC_TIMING_V2");
	dispc_reg_table[i++].addr = DISPC_TIMING_V2;
	strcpy(dispc_reg_table[i].name , "DISPC_POL_FREQ2");
	dispc_reg_table[i++].addr = DISPC_POL_FREQ2;
	strcpy(dispc_reg_table[i].name , "DISPC_DIVISOR2");
	dispc_reg_table[i++].addr = DISPC_DIVISOR2;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_ACCU_0");
	dispc_reg_table[i++].addr = DISPC_WB_ACCU_0;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_ACCU_1");
	dispc_reg_table[i++].addr = DISPC_WB_ACCU_1;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_BA_0");
	dispc_reg_table[i++].addr = DISPC_WB_BA_0;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_BA_1");
	dispc_reg_table[i++].addr = DISPC_WB_BA_1;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR_COEF_H_0");
	dispc_reg_table[i++].addr = DISPC_WB_FIR_COEF_H_0;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR_COEF_H_1");
	dispc_reg_table[i++].addr = DISPC_WB_FIR_COEF_H_1;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR_COEF_H_2");
	dispc_reg_table[i++].addr = DISPC_WB_FIR_COEF_H_2;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR_COEF_H_3");
	dispc_reg_table[i++].addr = DISPC_WB_FIR_COEF_H_3;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR_COEF_H_4");
	dispc_reg_table[i++].addr = DISPC_WB_FIR_COEF_H_4;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR_COEF_H_5");
	dispc_reg_table[i++].addr = DISPC_WB_FIR_COEF_H_5;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR_COEF_H_6");
	dispc_reg_table[i++].addr = DISPC_WB_FIR_COEF_H_6;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR_COEF_H_7");
	dispc_reg_table[i++].addr = DISPC_WB_FIR_COEF_H_7;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR_COEF_HV_0");
	dispc_reg_table[i++].addr = DISPC_WB_FIR_COEF_HV_0;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR_COEF_HV_1");
	dispc_reg_table[i++].addr = DISPC_WB_FIR_COEF_HV_1;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR_COEF_HV_2");
	dispc_reg_table[i++].addr = DISPC_WB_FIR_COEF_HV_2;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR_COEF_HV_3");
	dispc_reg_table[i++].addr = DISPC_WB_FIR_COEF_HV_3;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR_COEF_HV_4");
	dispc_reg_table[i++].addr = DISPC_WB_FIR_COEF_HV_4;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR_COEF_HV_5");
	dispc_reg_table[i++].addr = DISPC_WB_FIR_COEF_HV_5;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR_COEF_HV_6");
	dispc_reg_table[i++].addr = DISPC_WB_FIR_COEF_HV_6;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR_COEF_HV_7");
	dispc_reg_table[i++].addr = DISPC_WB_FIR_COEF_HV_7;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR_COEF_V_0");
	dispc_reg_table[i++].addr = DISPC_WB_FIR_COEF_V_0;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR_COEF_V_1");
	dispc_reg_table[i++].addr = DISPC_WB_FIR_COEF_V_1;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR_COEF_V_2");
	dispc_reg_table[i++].addr = DISPC_WB_FIR_COEF_V_2;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR_COEF_V_3");
	dispc_reg_table[i++].addr = DISPC_WB_FIR_COEF_V_3;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR_COEF_V_4");
	dispc_reg_table[i++].addr = DISPC_WB_FIR_COEF_V_4;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR_COEF_V_5");
	dispc_reg_table[i++].addr = DISPC_WB_FIR_COEF_V_5;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR_COEF_V_6");
	dispc_reg_table[i++].addr = DISPC_WB_FIR_COEF_V_6;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR_COEF_V_7");
	dispc_reg_table[i++].addr = DISPC_WB_FIR_COEF_V_7;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_ATTRIBUTES");
	dispc_reg_table[i++].addr = DISPC_WB_ATTRIBUTES;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_CONV_COEF0");
	dispc_reg_table[i++].addr = DISPC_WB_CONV_COEF0;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_CONV_COEF1");
	dispc_reg_table[i++].addr = DISPC_WB_CONV_COEF1;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_CONV_COEF2");
	dispc_reg_table[i++].addr = DISPC_WB_CONV_COEF2;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_CONV_COEF3");
	dispc_reg_table[i++].addr = DISPC_WB_CONV_COEF3;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_CONV_COEF4");
	dispc_reg_table[i++].addr = DISPC_WB_CONV_COEF4;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_BUF_SIZE_STATUS");
	dispc_reg_table[i++].addr = DISPC_WB_BUF_SIZE_STATUS;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_BUF_THRESHOLD");
	dispc_reg_table[i++].addr = DISPC_WB_BUF_THRESHOLD;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR");
	dispc_reg_table[i++].addr = DISPC_WB_FIR;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_PICTURE_SIZE");
	dispc_reg_table[i++].addr = DISPC_WB_PICTURE_SIZE;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_PIXEL_INC");
	dispc_reg_table[i++].addr = DISPC_WB_PIXEL_INC;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_ROW_INC");
	dispc_reg_table[i++].addr = DISPC_WB_ROW_INC;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_SIZE");
	dispc_reg_table[i++].addr = DISPC_WB_SIZE;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_BA_UV_0");
	dispc_reg_table[i++].addr = DISPC_VID1_BA_UV_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_BA_UV_1");
	dispc_reg_table[i++].addr = DISPC_VID1_BA_UV_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_BA_UV_0");
	dispc_reg_table[i++].addr = DISPC_VID2_BA_UV_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_BA_UV_1");
	dispc_reg_table[i++].addr = DISPC_VID2_BA_UV_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_BA_UV_0");
	dispc_reg_table[i++].addr = DISPC_VID3_BA_UV_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_BA_UV_1");
	dispc_reg_table[i++].addr = DISPC_VID3_BA_UV_1;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_BA_UV_0");
	dispc_reg_table[i++].addr = DISPC_WB_BA_UV_0;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_BA_UV_1");
	dispc_reg_table[i++].addr = DISPC_WB_BA_UV_1;
	strcpy(dispc_reg_table[i].name , "DISPC_CONFIG2");
	dispc_reg_table[i++].addr = DISPC_CONFIG2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_ATTRIBUTES2");
	dispc_reg_table[i++].addr = DISPC_VID1_ATTRIBUTES2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_ATTRIBUTES2");
	dispc_reg_table[i++].addr = DISPC_VID2_ATTRIBUTES2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_ATTRIBUTES2");
	dispc_reg_table[i++].addr = DISPC_VID3_ATTRIBUTES2;
	strcpy(dispc_reg_table[i].name , "DISPC_GAMMA_TABLE0");
	dispc_reg_table[i++].addr = DISPC_GAMMA_TABLE0;
	strcpy(dispc_reg_table[i].name , "DISPC_GAMMA_TABLE1");
	dispc_reg_table[i++].addr = DISPC_GAMMA_TABLE1;
	strcpy(dispc_reg_table[i].name , "DISPC_GAMMA_TABLE2");
	dispc_reg_table[i++].addr = DISPC_GAMMA_TABLE2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR2");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_ACCU2_0");
	dispc_reg_table[i++].addr = DISPC_VID1_ACCU2_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_ACCU2_1");
	dispc_reg_table[i++].addr = DISPC_VID1_ACCU2_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR2_COEF_H_0");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR2_COEF_H_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR2_COEF_H_1");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR2_COEF_H_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR2_COEF_H_2");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR2_COEF_H_2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR2_COEF_H_3");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR2_COEF_H_3;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR2_COEF_H_4");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR2_COEF_H_4;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR2_COEF_H_5");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR2_COEF_H_5;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR2_COEF_H_6");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR2_COEF_H_6;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR2_COEF_H_7");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR2_COEF_H_7;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR2_COEF_HV_0");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR2_COEF_HV_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR2_COEF_HV_1");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR2_COEF_HV_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR2_COEF_HV_2");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR2_COEF_HV_2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR2_COEF_HV_3");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR2_COEF_HV_3;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR2_COEF_HV_4");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR2_COEF_HV_4;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR2_COEF_HV_5");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR2_COEF_HV_5;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR2_COEF_HV_6");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR2_COEF_HV_6;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR2_COEF_HV_7");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR2_COEF_HV_7;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR2_COEF_V_0");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR2_COEF_V_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR2_COEF_V_1");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR2_COEF_V_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR2_COEF_V_2");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR2_COEF_V_2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR2_COEF_V_3");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR2_COEF_V_3;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR2_COEF_V_4");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR2_COEF_V_4;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR2_COEF_V_5");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR2_COEF_V_5;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR2_COEF_V_6");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR2_COEF_V_6;
	strcpy(dispc_reg_table[i].name , "DISPC_VID1_FIR2_COEF_V_7");
	dispc_reg_table[i++].addr = DISPC_VID1_FIR2_COEF_V_7;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR2");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_ACCU2_0");
	dispc_reg_table[i++].addr = DISPC_VID2_ACCU2_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_ACCU2_1");
	dispc_reg_table[i++].addr = DISPC_VID2_ACCU2_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR2_COEF_H_0");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR2_COEF_H_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR2_COEF_H_1");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR2_COEF_H_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR2_COEF_H_2");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR2_COEF_H_2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR2_COEF_H_3");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR2_COEF_H_3;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR2_COEF_H_4");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR2_COEF_H_4;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR2_COEF_H_5");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR2_COEF_H_5;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR2_COEF_H_6");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR2_COEF_H_6;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR2_COEF_H_7");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR2_COEF_H_7;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR2_COEF_HV_0");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR2_COEF_HV_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR2_COEF_HV_1");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR2_COEF_HV_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR2_COEF_HV_2");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR2_COEF_HV_2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR2_COEF_HV_3");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR2_COEF_HV_3;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR2_COEF_HV_4");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR2_COEF_HV_4;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR2_COEF_HV_5");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR2_COEF_HV_5;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR2_COEF_HV_6");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR2_COEF_HV_6;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR2_COEF_HV_7");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR2_COEF_HV_7;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR2_COEF_V_0");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR2_COEF_V_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR2_COEF_V_1");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR2_COEF_V_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR2_COEF_V_2");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR2_COEF_V_2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR2_COEF_V_3");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR2_COEF_V_3;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR2_COEF_V_4");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR2_COEF_V_4;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR2_COEF_V_5");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR2_COEF_V_5;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR2_COEF_V_6");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR2_COEF_V_6;
	strcpy(dispc_reg_table[i].name , "DISPC_VID2_FIR2_COEF_V_7");
	dispc_reg_table[i++].addr = DISPC_VID2_FIR2_COEF_V_7;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR2");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_ACCU2_0");
	dispc_reg_table[i++].addr = DISPC_VID3_ACCU2_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_ACCU2_1");
	dispc_reg_table[i++].addr = DISPC_VID3_ACCU2_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR2_COEF_H_0");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR2_COEF_H_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR2_COEF_H_1");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR2_COEF_H_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR2_COEF_H_2");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR2_COEF_H_2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR2_COEF_H_3");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR2_COEF_H_3;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR2_COEF_H_4");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR2_COEF_H_4;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR2_COEF_H_5");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR2_COEF_H_5;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR2_COEF_H_6");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR2_COEF_H_6;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR2_COEF_H_7");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR2_COEF_H_7;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR2_COEF_HV_0");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR2_COEF_HV_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR2_COEF_HV_1");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR2_COEF_HV_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR2_COEF_HV_2");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR2_COEF_HV_2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR2_COEF_HV_3");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR2_COEF_HV_3;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR2_COEF_HV_4");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR2_COEF_HV_4;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR2_COEF_HV_5");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR2_COEF_HV_5;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR2_COEF_HV_6");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR2_COEF_HV_6;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR2_COEF_HV_7");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR2_COEF_HV_7;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR2_COEF_V_0");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR2_COEF_V_0;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR2_COEF_V_1");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR2_COEF_V_1;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR2_COEF_V_2");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR2_COEF_V_2;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR2_COEF_V_3");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR2_COEF_V_3;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR2_COEF_V_4");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR2_COEF_V_4;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR2_COEF_V_5");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR2_COEF_V_5;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR2_COEF_V_6");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR2_COEF_V_6;
	strcpy(dispc_reg_table[i].name , "DISPC_VID3_FIR2_COEF_V_7");
	dispc_reg_table[i++].addr = DISPC_VID3_FIR2_COEF_V_7;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR2");
	dispc_reg_table[i++].addr = DISPC_WB_FIR2;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_ACCU2_0");
	dispc_reg_table[i++].addr = DISPC_WB_ACCU2_0;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_ACCU2_1");
	dispc_reg_table[i++].addr = DISPC_WB_ACCU2_1;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR2_COEF_H_0");
	dispc_reg_table[i++].addr = DISPC_WB_FIR2_COEF_H_0;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR2_COEF_H_1");
	dispc_reg_table[i++].addr = DISPC_WB_FIR2_COEF_H_1;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR2_COEF_H_2");
	dispc_reg_table[i++].addr = DISPC_WB_FIR2_COEF_H_2;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR2_COEF_H_3");
	dispc_reg_table[i++].addr = DISPC_WB_FIR2_COEF_H_3;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR2_COEF_H_4");
	dispc_reg_table[i++].addr = DISPC_WB_FIR2_COEF_H_4;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR2_COEF_H_5");
	dispc_reg_table[i++].addr = DISPC_WB_FIR2_COEF_H_5;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR2_COEF_H_6");
	dispc_reg_table[i++].addr = DISPC_WB_FIR2_COEF_H_6;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR2_COEF_H_7");
	dispc_reg_table[i++].addr = DISPC_WB_FIR2_COEF_H_7;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR2_COEF_HV_0");
	dispc_reg_table[i++].addr = DISPC_WB_FIR2_COEF_HV_0;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR2_COEF_HV_1");
	dispc_reg_table[i++].addr = DISPC_WB_FIR2_COEF_HV_1;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR2_COEF_HV_2");
	dispc_reg_table[i++].addr = DISPC_WB_FIR2_COEF_HV_2;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR2_COEF_HV_3");
	dispc_reg_table[i++].addr = DISPC_WB_FIR2_COEF_HV_3;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR2_COEF_HV_4");
	dispc_reg_table[i++].addr = DISPC_WB_FIR2_COEF_HV_4;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR2_COEF_HV_5");
	dispc_reg_table[i++].addr = DISPC_WB_FIR2_COEF_HV_5;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR2_COEF_HV_6");
	dispc_reg_table[i++].addr = DISPC_WB_FIR2_COEF_HV_6;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR2_COEF_HV_7");
	dispc_reg_table[i++].addr = DISPC_WB_FIR2_COEF_HV_7;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR2_COEF_V_0");
	dispc_reg_table[i++].addr = DISPC_WB_FIR2_COEF_V_0;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR2_COEF_V_1");
	dispc_reg_table[i++].addr = DISPC_WB_FIR2_COEF_V_1;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR2_COEF_V_2");
	dispc_reg_table[i++].addr = DISPC_WB_FIR2_COEF_V_2;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR2_COEF_V_3");
	dispc_reg_table[i++].addr = DISPC_WB_FIR2_COEF_V_3;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR2_COEF_V_4");
	dispc_reg_table[i++].addr = DISPC_WB_FIR2_COEF_V_4;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR2_COEF_V_5");
	dispc_reg_table[i++].addr = DISPC_WB_FIR2_COEF_V_5;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR2_COEF_V_6");
	dispc_reg_table[i++].addr = DISPC_WB_FIR2_COEF_V_6;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_FIR2_COEF_V_7");
	dispc_reg_table[i++].addr = DISPC_WB_FIR2_COEF_V_7;
	strcpy(dispc_reg_table[i].name , "DISPC_GLOBAL_BUFFER");
	dispc_reg_table[i++].addr = DISPC_GLOBAL_BUFFER;
	strcpy(dispc_reg_table[i].name , "DISPC_DIVISOR");
	dispc_reg_table[i++].addr = DISPC_DIVISOR;
	strcpy(dispc_reg_table[i].name , "DISPC_WB_ATTRIBUTES2");
	dispc_reg_table[i++].addr = DISPC_WB_ATTRIBUTES2;
	strcpy(dispc_reg_table[i].name, "END");
	dispc_reg_table[i].addr = 0;

	init_done = 1;
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		display44xx_name2addr
 * @BRIEF		retrieve physical address of a register, given its name.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	name: register name
 * @param[in,out]	addr: register address
 * @DESCRIPTION		retrieve physical address of a register, given its name.
 *//*------------------------------------------------------------------------ */
int display44xx_name2addr(char *name, unsigned int *addr)
{
	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!init_done)
		display44xx_init_regtable();

	if (name2addr(name, addr, dss_reg_table) == 0)
		return name2addr(name, addr, dss_reg_table);
	else if (name2addr(name, addr, dsi1_reg_table) == 0)
		return name2addr(name, addr, dsi1_reg_table);
	else if (name2addr(name, addr, dsi1_pll_reg_table) == 0)
		return name2addr(name, addr, dsi1_pll_reg_table);
	else if (name2addr(name, addr, dsi1_phy_reg_table) == 0)
		return name2addr(name, addr, dsi1_phy_reg_table);
	else if (name2addr(name, addr, dsi2_reg_table) == 0)
		return name2addr(name, addr, dsi2_reg_table);
	else if (name2addr(name, addr, dsi2_pll_reg_table) == 0)
		return name2addr(name, addr, dsi2_pll_reg_table);
	else if (name2addr(name, addr, dsi2_phy_reg_table) == 0)
		return name2addr(name, addr, dsi2_phy_reg_table);
	else if (name2addr(name, addr, rfbi_reg_table) == 0)
		return name2addr(name, addr, rfbi_reg_table);
	else if (name2addr(name, addr, venc_reg_table) == 0)
		return name2addr(name, addr, venc_reg_table);
	else if (name2addr(name, addr, dispc_reg_table) == 0)
		return name2addr(name, addr, dispc_reg_table);
	else
		return -1;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		display44xx_clock_is_running
 * @BRIEF		check if selected display clock is running or not.
 * @RETURNS		1 if selected clock is running,
 *			0 if clock is gated or erroneous id.
 * @param[in]		id: module to be dump (i.e. user-entered argv[3])
 * @DESCRIPTION		check if selected display clock is running or not.
 *//*------------------------------------------------------------------------ */
unsigned char display44xx_clock_is_running(display44xx_clock_id id)
{
	unsigned char running;
	unsigned int cm_dss_clkstctrl, cm_dss_dss_clkctrl;
	int ret;

	CHECK_CPU(44xx, 0);

	ret = mem_read(OMAP4430_CM_DSS_CLKSTCTRL, &cm_dss_clkstctrl);
	ret |= mem_read(OMAP4430_CM_DSS_DSS_CLKCTRL, &cm_dss_dss_clkctrl);
	if (ret != 0) {
		running = 0;
		goto display44xx_clock_is_running_end;
	}

	switch (id) {
	case HDMI_PHY_48MHz_FCLK:
		running = extract_bit(cm_dss_clkstctrl, 11);
		break;
	case DSS_ALWON_SYS_CLK:
		running = extract_bit(cm_dss_clkstctrl, 10);
		break;
	case DSS_FCLK:
		running = extract_bit(cm_dss_clkstctrl, 9);
		break;
	case DSS_L3_ICLK:
		running = extract_bit(cm_dss_clkstctrl, 8);
		break;
	case OPTFCLK_TV_FCLK:
		running = extract_bit(cm_dss_dss_clkctrl, 11);
		break;
	case OPTFCLK_SYS_CLK:
		running = extract_bit(cm_dss_dss_clkctrl, 10);
		break;
	case OPTFCLK_48MHZ_CLK:
		running = extract_bit(cm_dss_dss_clkctrl, 9);
		break;
	case OPTFCLK_DSSCLK:
		running = extract_bit(cm_dss_dss_clkctrl, 8);
		break;
	default:
		fprintf(stderr, "%s(): erroneous id (%d)!!!\n", __func__, id);
		running = 0;
	}

display44xx_clock_is_running_end:
	return running;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		display44xx_dump
 * @BRIEF		dump display module registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		display_mod: module to be dump
 *			(i.e. user-entered argv[3])
 * @DESCRIPTION		dump display module registers
 *//*------------------------------------------------------------------------ */
int display44xx_dump(char *display_mod)
{
	int ret;

	CHECK_CPU(44xx, OMAPCONF_ERR_CPU);

	if (!display44xx_clock_is_running(DSS_L3_ICLK)) {
		printf("DSS L3 ICLK stopped, registers not accessible.\n\n");
		ret = OMAPCONF_ERR_REG_ACCESS;
		goto display44xx_dump_end;
	}

	if (!init_done)
		display44xx_init_regtable();

	ret = OMAPCONF_ERR_ARG;
	if ((strcmp(display_mod, "all") == 0) ||
		(strcmp(display_mod, "dss") == 0))
		ret = dumpregs(dss_reg_table);

	if ((strcmp(display_mod, "all") == 0) ||
		(strcmp(display_mod, "dispc") == 0))
		ret = dumpregs(dispc_reg_table);

	if ((strcmp(display_mod, "all") == 0) ||
		(strcmp(display_mod, "dsi1") == 0))
		ret = dumpregs(dsi1_reg_table);

	if ((strcmp(display_mod, "all") == 0) ||
		(strcmp(display_mod, "dsi1_phy") == 0))
		ret = dumpregs(dsi1_phy_reg_table);

	if ((strcmp(display_mod, "all") == 0) ||
		(strcmp(display_mod, "dsi1_pll") == 0))
		ret = dumpregs(dsi1_pll_reg_table);

	if ((strcmp(display_mod, "all") == 0) ||
		(strcmp(display_mod, "dsi2") == 0))
		ret = dumpregs(dsi2_reg_table);

	if ((strcmp(display_mod, "all") == 0) ||
		(strcmp(display_mod, "dsi2_phy") == 0))
		ret = dumpregs(dsi2_phy_reg_table);

	if ((strcmp(display_mod, "all") == 0) ||
		(strcmp(display_mod, "dsi2_pll") == 0))
		ret = dumpregs(dsi2_pll_reg_table);

	if ((strcmp(display_mod, "all") == 0) ||
		(strcmp(display_mod, "rfbi") == 0))
		ret = dumpregs(rfbi_reg_table);

	if ((strcmp(display_mod, "all") == 0) ||
		(strcmp(display_mod, "venc") == 0))
		ret = dumpregs(venc_reg_table);

	if (ret == OMAPCONF_ERR_ARG)
		help(HELP_DISPLAY);

display44xx_dump_end:
	return ret;
}
