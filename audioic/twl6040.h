/*
 *
 * @Component			OMAPCONF
 * @Filename			twl6040.h
 * @Description			TWL6040 Audio Companion Chip Functions
 * @Author			Patrick Titiano (p-titiano@ti.com)
 *				Misael Lopez Cruz <misael.lopez@ti.com>
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


#ifndef __TWL6040_H__
#define __TWL6040_H__


#include <stdio.h>


#define TWL6040_I2C_BUS			0
#define TWL6040_I2C_ADDR		0x4B

#define TWL6040_REG_ASICID		0x01
#define TWL6040_REG_ASICREV		0x02
#define TWL6040_REG_INTID		0x03
#define TWL6040_REG_INTMR		0x04
#define TWL6040_REG_NCPCTL		0x05
#define TWL6040_REG_LDOCTL		0x06
#define TWL6040_REG_HPPLLCTL		0x07
#define TWL6040_REG_LPPLLCTL		0x08
#define TWL6040_REG_LPPLLDIV		0x09
#define TWL6040_REG_AMICBCTL		0x0A
#define TWL6040_REG_DMICBCTL		0x0B
#define TWL6040_REG_MICLCTL		0x0C
#define TWL6040_REG_MICRCTL		0x0D
#define TWL6040_REG_MICGAIN		0x0E
#define TWL6040_REG_LINEGAIN		0x0F
#define TWL6040_REG_HSLCTL		0x10
#define TWL6040_REG_HSRCTL		0x11
#define TWL6040_REG_HSGAIN		0x12
#define TWL6040_REG_EARCTL		0x13
#define TWL6040_REG_HFLCTL		0x14
#define TWL6040_REG_HFLGAIN		0x15
#define TWL6040_REG_HFRCTL		0x16
#define TWL6040_REG_HFRGAIN		0x17
#define TWL6040_REG_VIBCTLL		0x18
#define TWL6040_REG_VIBDATL		0x19
#define TWL6040_REG_VIBCTLR		0x1A
#define TWL6040_REG_VIBDATR		0x1B
#define TWL6040_REG_HKCTL1		0x1C
#define TWL6040_REG_HKCTL2		0x1D
#define TWL6040_REG_GPOCTL		0x1E
#define TWL6040_REG_ALB			0x1F
#define TWL6040_REG_DLB			0x20
#define TWL6040_REG_TRIM1		0x28
#define TWL6040_REG_TRIM2		0x29
#define TWL6040_REG_TRIM3		0x2A
#define TWL6040_REG_HSOTRIM		0x2B
#define TWL6040_REG_HFOTRIM		0x2C
#define TWL6040_REG_ACCCTL		0x2D
#define TWL6040_REG_STATUS		0x2E

#define TWL6040_REG_NUM			(TWL6040_REG_STATUS + 1)


float twl6040_chip_revision_get(void);
int twl6040_dumpregs(void);
int twl6040_config(FILE *stream);
int twl6040_gains(FILE *stream);
int twl6040_readreg(const char *reg_addr);
int twl6040_writereg(const char *reg_addr, const char *reg_val);
int twl6040_main(int argc, char *argv[]);


#endif
