/*
 *
 * @Component			OMAPCONF
 * @Filename			stm44xx.h
 * @Description			Definition file for OMAP44xx STM Module
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


#ifndef __STM44XX_H__
#define __STM44XX_H__


#define OMAP4430_STM_REGADDR(module, reg) ((module) + (reg))

#define OMAP4430_STM_CFG_BASE	0x54161000
#define OMAP4430_STM_SYSCONFIG	OMAP4430_STM_REGADDR(OMAP4430_STM_CFG_BASE, 0x010)
#define OMAP4430_STM_SYSSTATUS	OMAP4430_STM_REGADDR(OMAP4430_STM_CFG_BASE, 0x014)
#define OMAP4430_STM_SWMCTRL0	OMAP4430_STM_REGADDR(OMAP4430_STM_CFG_BASE, 0x024)
#define OMAP4430_STM_SWMCTRL1	OMAP4430_STM_REGADDR(OMAP4430_STM_CFG_BASE, 0x028)
#define OMAP4430_STM_SWMCTRL2	OMAP4430_STM_REGADDR(OMAP4430_STM_CFG_BASE, 0x02C)
#define OMAP4430_STM_SWMCTRL3	OMAP4430_STM_REGADDR(OMAP4430_STM_CFG_BASE, 0x030)
#define OMAP4430_STM_SWMCTRL4	OMAP4430_STM_REGADDR(OMAP4430_STM_CFG_BASE, 0x034)
#define OMAP4430_STM_HWMCTRL	OMAP4430_STM_REGADDR(OMAP4430_STM_CFG_BASE, 0x038)
#define OMAP4430_PTI_CONFIG	OMAP4430_STM_REGADDR(OMAP4430_STM_CFG_BASE, 0x03C)
#define OMAP4430_PTI_COUNTD	OMAP4430_STM_REGADDR(OMAP4430_STM_CFG_BASE, 0x040)
#define OMAP4430_ATB_CONFIG	OMAP4430_STM_REGADDR(OMAP4430_STM_CFG_BASE, 0x044)
#define OMAP4430_ATB_POINTER	OMAP4430_STM_REGADDR(OMAP4430_STM_CFG_BASE, 0x048)
#define OMAP4430_ATB_ID		OMAP4430_STM_REGADDR(OMAP4430_STM_CFG_BASE, 0x04C)
#define OMAP4430_STM_CTS	OMAP4430_STM_REGADDR(OMAP4430_STM_CFG_BASE, 0xFA0)
#define OMAP4430_STM_CTC	OMAP4430_STM_REGADDR(OMAP4430_STM_CFG_BASE, 0xFA4)
#define OMAP4430_STM_LOCK	OMAP4430_STM_REGADDR(OMAP4430_STM_CFG_BASE, 0xFB0)
#define OMAP4430_STM_LOCK_STS	OMAP4430_STM_REGADDR(OMAP4430_STM_CFG_BASE, 0xFB4)


typedef enum {
	HW_MASTER_PMI = 0x1D,
	HW_MASTER_CMI1 = 0x1E,
	HW_MASTER_CMI2 = 0x1F,
	HW_MASTER_MAX
} stm_hw_masters;


int stm_claim_ownership(void);
int stm_release_ownership(void);
int stm_is_claimed(void);

int stm_dump_regs(void);

int stm_hw_master_enable(stm_hw_masters hwmid, unsigned char pos);
int stm_hw_master_disable(unsigned char pos);

int stm_atb_prescaler_set(unsigned char div);
int stm_atb_prescaler_get(void);

int stm_atb_capture_enable(void);
int stm_atb_capture_disable(void);

int stm_last_header_pos_get(void);


#endif
