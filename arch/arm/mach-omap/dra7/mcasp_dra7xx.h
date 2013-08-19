/*
 *
 * @Component			OMAPCONF
 * @Filename			mcasp_dra7xx.h
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

#ifndef __MCASP_DRA7XX_H__
#define __MCASP_DRA7XX_H__

#include <stdio.h>

#define MCASP1			1
#define MCASP2			2
#define MCASP3			3
#define MCASP4			4
#define MCASP5			5
#define MCASP6			6
#define MCASP7			7
#define MCASP8			8

#define MCASP1_CFG_BASEADDR	0x48460000
#define MCASP2_CFG_BASEADDR	0x48464000
#define MCASP3_CFG_BASEADDR	0x48468000
#define MCASP4_CFG_BASEADDR	0x4846c000
#define MCASP5_CFG_BASEADDR	0x48470000
#define MCASP6_CFG_BASEADDR	0x48474000
#define MCASP7_CFG_BASEADDR	0x48478000
#define MCASP8_CFG_BASEADDR	0x4847c000

#define MCASP_PID_OFFSET	0x00
#define PWRIDLESYSCONFIG_OFFSET	0x04
#define MCASP_PFUNC_OFFSET	0x10
#define MCASP_PDIR_OFFSET	0x14
#define MCASP_PDOUT_OFFSET	0x18
#define MCASP_PDIN_OFFSET	0x1c
#define MCASP_PDCLR_OFFSET	0x20
#define MCASP_GBLCTL_OFFSET	0x44
#define MCASP_AMUTE_OFFSET	0x48
#define MCASP_LBCTL_OFFSET	0x4c
#define MCASP_TXDITCTL_OFFSET	0x50
#define MCASP_GBLCTLR_OFFSET	0x60
#define MCASP_RXMASK_OFFSET	0x64
#define MCASP_RXFMT_OFFSET	0x68
#define MCASP_RXFMCTL_OFFSET	0x6c
#define MCASP_ACLKRCTL_OFFSET	0x70
#define MCASP_AHCLKRCTL_OFFSET	0x74
#define MCASP_RXTDM_OFFSET	0x78
#define MCASP_EVTCTLR_OFFSET	0x7c
#define MCASP_RXSTAT_OFFSET	0x80
#define MCASP_RXTDMSLOT_OFFSET	0x84
#define MCASP_RXCLKCHK_OFFSET	0x88
#define MCASP_REVTCTL_OFFSET	0x8c
#define MCASP_GBLCTLX_OFFSET	0xa0
#define MCASP_TXMASK_OFFSET	0xa4
#define MCASP_TXFMT_OFFSET	0xa8
#define MCASP_TXFMCTL_OFFSET	0xac
#define MCASP_ACLKXCTL_OFFSET	0xb0
#define MCASP_AHCLKXCTL_OFFSET	0xb4
#define MCASP_TXTDM_OFFSET	0xb8
#define MCASP_EVTCTLX_OFFSET	0xbc
#define MCASP_TXSTAT_OFFSET	0xc0
#define MCASP_TXTDMSLOT_OFFSET	0xc4
#define MCASP_TXCLKCHK_OFFSET	0xc8
#define MCASP_XEVTCTL_OFFSET	0xcc
#define MCASP_CLKADJEN_OFFSET	0xd0
#define MCASP_XRSRCTL_OFFSET(n)	(0x180 + 0x04*(n))

#define MCASP_WFIFOCTL_OFFSET	0x1000
#define MCASP_WFIFOSTS_OFFSET	0x1004
#define MCASP_RFIFOCTL_OFFSET	0x1008
#define MCASP_RFIFOSTS_OFFSET	0x100c

int dra7xx_mcasp_dumpregs(FILE *stream, int argc, char *argv[]);
int dra7xx_mcasp_show(FILE *stream, int argc, char *argv[]);
int dra7xx_mcasp_main(int argc, char *argv[]);

#endif
