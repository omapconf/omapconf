/* ======================================================================= *//**
 * @Component			OMAPCONF
 * @Filename			camera44xx.h
 * @Description			OMAP4 Camera Configuration
 * @Author			Sergio Aguirre (saaguirre@ti.com)
 * @Author			Edward Lee (edward.lee@ti.com)
 * @Date			2012
 * @Copyright			TEXAS INSTRUMENTS Incorporated
 *//*======================================================================== */
/*
 * camera44xx.h
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


#ifndef __CAMERA44XX_H__
#define __CAMERA44XX_H__


/* ISS TOP Physical address */
#define ISS_HL_REVISION			0x52000000
#define ISS_HL_SYSCONFIG		0x52000010
#define ISS_HL_IRQSTATUS_RAW(i)		(0x52000020 + (0x10 * (i)))
#define ISS_HL_IRQSTATUS(i)		(0x52000024 + (0x10 * (i)))
#define ISS_HL_IRQENABLE_SET(i)		(0x52000028 + (0x10 * (i)))
#define ISS_CTRL			0x52000080
#define ISS_CLKCTRL			0x52000084
#define ISS_CLKSTAT			0x52000088
#define ISS_PM_STATUS			0x5200008C

/* ISS CSI2 Physical address */
#define CSI2_REVISION			0x52001000
#define CSI2_SYSCONFIG			0x52001010
#define CSI2_SYSSTATUS			0x52001014
#define CSI2_IRQENABLE			0x5200101C
#define CSI2_CTRL			0x52001040
#define CSI2_COMPLEXIO_CFG		0x52001050
#define CSI2_COMPLEXIO_IRQSTATUS	0x52001054
#define CSI2_COMPLEXIO_IRQENABLE	0x52001460
#define CSI2_TIMING			0x5200106C
#define CSI2_CTX_CTRL1(i)		(0x52001070 + (0x20 * (i)))
#define CSI2_CTX_CTRL2(i)		(0x52001074 + (0x20 * (i)))
#define CSI2_CTX_DAT_OFST(i)		(0x52001078 + (0x20 * (i)))
#define CSI2_CTX_DAT_PING_ADDR(i)	(0x5200107C + (0x20 * (i)))
#define CSI2_CTX_DAT_PONG_ADDR(i)	(0x52001080 + (0x20 * (i)))
#define CSI2_CTX_IRQENABLE(i)		(0x52001084 + (0x20 * (i)))
#define CSI2_CTX_IRQSTATUS(i)		(0x52001088 + (0x20 * (i)))
#define CSI2_CTX_CTRL3(i)		(0x5200108C + (0x20 * (i)))

/* ISS CSIPHY Physical address */
#define REGISTER0			0x52001170
#define REGISTER1			0x52001174
#define REGISTER2			0x52001178

/* ISS CCP2 Physical address */
#define CCP2_REVISION			0x52001C00
#define CCP2_SYSCONFIG			0x52001C04
#define CCP2_SYSSTATUS			0x52001C08
#define CCP2_LC01_IRQENABLE		0x52001C0C
#define CCP2_LC01_IRQSTATUS		0x52001C10
#define CCP2_LC23_IRQENABLE		0x52001C14
#define CCP2_LC23_IRQSTATUS		0x52001C18
#define CCP2_LCM_IRQENABLE		0x52001C2C
#define CCP2_LCM_IRQSTATUS		0x52001C30
#define CCP2_CTRL			0x52001C40
#define CCP2_CTRL1			0x52001C4C
#define CCP2_LCx_CTRL(i)		(0x52001C50 + ((i) * 0x30))
#define CCP2_LCx_CODE(i)		(0x52001C54 + ((i) * 0x30))
#define CCP2_LCx_STAT_START(i)		(0x52001C58 + ((i) * 0x30))
#define CCP2_LCx_STAT_SIZE(i)		(0x52001C5C + ((i) * 0x30))
#define CCP2_LCx_SOF_ADDR(i)		(0x52001C60 + ((i) * 0x30))
#define CCP2_LCx_EOF_ADDR(i)		(0x52001C64 + ((i) * 0x30))
#define CCP2_LCx_DAT_START(i)		(0x52001C68 + ((i) * 0x30))
#define CCP2_LCx_DAT_SIZE(i)		(0x52001C6C + ((i) * 0x30))
#define CCP2_LCx_DAT_PING_ADDR(i)	(0x52001C70 + ((i) * 0x30))
#define CCP2_LCx_DAT_PONG_ADDR(i)	(0x52001C74 + ((i) * 0x30))
#define CCP2_LCx_DAT_OFST(i)		(0x52001C78 + ((i) * 0x30))
#define CCP2_LCM_CTRL			0x52001DD0
#define CCP2_LCM_VSIZE			0x52001DD4
#define CCP2_LCM_HSIZE			0x52001DD8
#define CCP2_LCM_PREFETCH		0x52001DDC
#define CCP2_LCM_SRC_ADDR		0x52001DE0
#define CCP2_LCM_SRC_OFST		0x52001DE4
#define CCP2_LCM_DST_ADDR		0x52001DE8
#define CCP2_LCM_DST_OFST		0x52001DEC
#define CCP2_LCM_HISTORY		0x52001DF0


/* CSI2 Pinmuxs */
#define CONTROL_CAMERA_RX				0x4A100608
#define CONTROL_CORE_PAD0_CSI21_DX0_PAD1_CSI21_DY0	0x4A1000A0
#define CONTROL_CORE_PAD0_CSI21_DX1_PAD1_CSI21_DY1	0x4A1000A4
#define CONTROL_CORE_PAD0_CSI21_DX2_PAD1_CSI21_DY2	0x4A1000A8
#define CONTROL_CORE_PAD0_CSI21_DX3_PAD1_CSI21_DY3	0x4A1000AC
#define CONTROL_CORE_PAD0_CSI21_DX4_PAD1_CSI21_DY4	0x4A1000B0
#define CONTROL_CORE_PAD0_CSI22_DX0_PAD1_CSI22_DY0	0x4A1000B4
#define CONTROL_CORE_PAD0_CSI22_DX1_PAD1_CSI22_DY1	0x4A1000B8

/* 4460+ only */
#define CONTROL_CORE_PAD0_DPM_EMU19_PAD1_CSI22_DX2	0x4A1001D4
#define CONTROL_CORE_PAD0_CSI22_DY2			0x4A1001F4

/* CAM_PRM */
#define PM_CAM_PWRSTCTRL				0x4A307000
#define PM_CAM_PWRSTCTRL_CAM_MEM_ONSTATE_MASK		(3 << 16)
#define PM_CAM_PWRSTCTRL_LOWPOWERSTATECHANGE		(1 << 4)
#define PM_CAM_PWRSTCTRL_POWERSTATE_MASK		(3 << 0)
#define PM_CAM_PWRSTCTRL_POWERSTATE_OFF			(0x0 << 0)
#define PM_CAM_PWRSTCTRL_POWERSTATE_INACTIVE		(0x2 << 0)
#define PM_CAM_PWRSTCTRL_POWERSTATE_ON			(0x3 << 0)

/* ISS */
#define ISS_PBASE				0x52000000

#define ISS_TOP_PBASE				ISS_PBASE
#define ISS_TOP_SIZE				256

#define ISS_CAMERARX_CORE1_PBASE		(ISS_PBASE + 0x1170)
#define ISS_CAMERARX_CORE1_SIZE			32

#define ISS_CAMERARX_CORE2_PBASE		(ISS_PBASE + 0x1570)
#define ISS_CAMERARX_CORE2_SIZE			32

#define ISS_CSI2_A_REGS1_PBASE			(ISS_PBASE + 0x1000)
#define ISS_CSI2_A_REGS1_SIZE			368

#define ISS_CSI2_B_REGS1_PBASE			(ISS_PBASE + 0x1400)
#define ISS_CSI2_B_REGS1_SIZE			368

#define ISS_CSI2_C_REGS1_PBASE			(ISS_PBASE + 0x2400)
#define ISS_CSI2_C_REGS1_SIZE			368

#define ISS_CCP2_PBASE				(ISS_PBASE + 0x1C00)
#define ISS_CCP2_SIZE				512

#define ISS_BTE_PBASE				(ISS_PBASE + 0x2000)
#define ISS_BTE_SIZE				512

#define ISS_ISP5_SYS1_PBASE			(ISS_PBASE + 0x10000)
#define ISS_ISP5_SYS1_SIZE			160

#define ISS_ISP5_SYS2_PBASE			(ISS_PBASE + 0x100A0)
#define ISS_ISP5_SYS2_SIZE			864

#define ISS_RESIZER_PBASE			(ISS_PBASE + 0x10400)
#define ISS_RESIZER_SIZE			1024

#define ISS_IPIPE_PBASE				(ISS_PBASE + 0x10800)
#define ISS_IPIPE_SIZE				2048

#define ISS_ISIF_PBASE				(ISS_PBASE + 0x11000)
#define ISS_ISIF_SIZE				512

#define ISS_IPIPEIF_PBASE			(ISS_PBASE + 0x11200)
#define ISS_IPIPEIF_SIZE			128

#define ISS_H3A_PBASE				(ISS_PBASE + 0x11400)
#define ISS_H3A_SIZE				512

#define ISS_LDC_PBASE				(ISS_PBASE + 0x20100)
#define ISS_LDC_SIZE				128

#define ISS_SIMCOP_DMA_PBASE			(ISS_PBASE + 0x20200)
#define ISS_SIMCOP_DMA_SIZE			512

#define ISS_SIMCOP_NSF_PBASE			(ISS_PBASE + 0x20780)
#define ISS_SIMCOP_NSF_SIZE			128

/* ISS_HL */
#define ISS_CLKSTAT_VPORT2_CLK			(1 << 30)
#define ISS_CLKSTAT_VPORT1_CLK			(1 << 29)
#define ISS_CLKSTAT_VPORT0_CLK			(1 << 28)
#define ISS_CLKSTAT_CCP2			(1 << 4)
#define ISS_CLKSTAT_CSI2_B			(1 << 3)
#define ISS_CLKSTAT_CSI2_A			(1 << 2)
#define ISS_CLKSTAT_ISP				(1 << 1)
#define ISS_CLKSTAT_SIMCOP			(1 << 0)

/* CSI2 */
#define CSI2_CTRL_VP_CLK_EN			(1 << 15)
#define CSI2_CTRL_VP_ONLY_EN			(1 << 11)
#define CSI2_CTRL_VP_OUT_CTRL_MASK		(3 << 8)

#define CSI2_CTX_DAT_OFST_MASK			(0xFFF << 5)

#define CSI2_CTX_PING_ADDR(i)			(0x7C + (0x20 * i))
#define CSI2_CTX_PING_ADDR_MASK			~(0x1F << 0)

#define CSI2_CTX_PONG_ADDR(i)			(0x80 + (0x20 * i))
#define CSI2_CTX_PONG_ADDR_MASK			CSI2_CTX_PING_ADDR_MASK

/* CCP2 */
#define CCP2_CTRL_VP_ONLY_EN			(1 << 11)

/* SIMCOP LDC */
#define LDC_PCR					(0x04)
#define LDC_PCR_MODE_MASK			(3 << 3)
#define LDC_PCR_MODE_Y422			(0 << 3)
#define LDC_PCR_MODE_BAYER			(1 << 3)
#define LDC_PCR_MODE_Y420			(2 << 3)

#define LDC_RD_BASE				(0x08)

#define LDC_RD_OFST				(0x0C)

#define LDC_FRAME_SIZE				(0x10)
#define LDC_FRAME_SIZE_H(x)			(((x) & 0x3FFF) << 16)
#define LDC_FRAME_SIZE_H_MASK			(0x3FFF << 16)
#define LDC_FRAME_SIZE_W(x)			(((x) & 0x3FFF) << 0)
#define LDC_FRAME_SIZE_W_MASK			(0x3FFF << 0)

#define LDC_INITXY				(0x14)

#define LDC_WR_BASE						(0x18)
#define LDC_WR_OFST				(0x1C)

#define LDC_CONFIG				(0x28)
#define LDC_CENTER				(0x2C)
#define LDC_KHV					(0x30)
#define LDC_BLOCK				(0x34)
#define LDC_AB					(0x44)
#define LDC_CD					(0x48)
#define LDC_EF					(0x4C)

/* SIMCOP DMA */
#define SIMCOP_DMA_CTRL				(0x1C)

#define SIMCOP_DMA_CHAN_CTRL(x)			(0x80 + ((x) * 0x30))
#define SIMCOP_DMA_CHAN_SMEM_ADDR(x)		(0x84 + ((x) * 0x30))
#define SIMCOP_DMA_CHAN_SMEM_OFST(x)		(0x88 + ((x) * 0x30))
#define SIMCOP_DMA_CHAN_BUF_OFST(x)		(0x8C + ((x) * 0x30))
#define SIMCOP_DMA_CHAN_BUF_ADDR(x)		(0x90 + ((x) * 0x30))
#define SIMCOP_DMA_CHAN_BLOCK_SIZE(x)		(0x94 + ((x) * 0x30))
#define SIMCOP_DMA_CHAN_BLOCK_STEP(x)		(0xA4 + ((x) * 0x30))

/* SIMCOP NSF2 (16-bits) */
#define NSF_CFG				(0x00)
#define NSF_BLKW			(0x02)
#define NSF_BLKH			(0x04)
#define NSF_IOMST			(0x06)
#define NSF_IOMOFST			(0x08)
#define NSF_WMST			(0x0A)
#define NSF_WMOFST			(0x0C)
#define NSF_THR00			(0x0E)
#define NSF_THR01			(0x10)
#define NSF_THR02			(0x12)
#define NSF_THR03			(0x14)
#define NSF_THR04			(0x16)
#define NSF_THR05			(0x18)
#define NSF_THR10			(0x1A)
#define NSF_THR11			(0x1C)
#define NSF_THR12			(0x1E)
#define NSF_THR13			(0x20)
#define NSF_THR14			(0x22)
#define NSF_THR15			(0x24)
#define NSF_THR20			(0x26)
#define NSF_THR21			(0x28)
#define NSF_THR22			(0x2A)
#define NSF_THR23			(0x2C)
#define NSF_THR24			(0x2E)
#define NSF_THR25			(0x30)
#define NSF_SHD_XST			(0x32)
#define NSF_SHD_YST			(0x34)
#define NSF_SHD_HA1			(0x36)
#define NSF_SHD_HA2			(0x38)
#define NSF_SHD_VA1			(0x3A)
#define NSF_SHD_VA2			(0x3C)
#define NSF_SHD_HS			(0x3E)
#define NSF_SHD_VS			(0x40)
#define NSF_SHD_GADJ			(0x42)
#define NSF_SHD_OADJ			(0x44)
#define NSF_MAXG			(0x46)
#define NSF_SFT_SLOPE			(0x48)
#define NSF_EE_L1_SLOPE			(0x4A)
#define NSF_EE_L1_THR1			(0x4C)
#define NSF_EE_L1_THR2			(0x4E)
#define NSF_EE_L1_OFST2			(0x50)
#define NSF_EE_L2_SLOPE			(0x52)
#define NSF_EE_L2_THR1			(0x54)
#define NSF_EE_L2_THR2			(0x56)
#define NSF_EE_L2_OFST2			(0x58)
#define NSF_EE_L3_SLOPE			(0x5A)
#define NSF_EE_L3_THR1			(0x5C)
#define NSF_EE_L3_THR2			(0x5E)
#define NSF_EE_L3_OFST2			(0x60)
#define NSF_IOMSTC			(0x62)
#define NSF_DS_THR			(0x64)
#define NSF_DS_SLOPE1			(0x66)
#define NSF_DS_SLOPE2			(0x68)


int camera44xx_main(int argc, char *argv[]);
int camera44xx_name2addr(char *name, unsigned int *addr);
int camera44xx_dump(char *camera_mod);
int camera44xx_config_show(void);

#endif
