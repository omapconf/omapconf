/*
 *
 * @Component			OMAPCONF
 * @Filename			timr54xx.h
 * @Description			OMAP 54XX timers
 * @Author			Frederic Turgis (f-turgis@ti.com)
 * @Date			2012
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


#ifndef __TIMR54XX_H__
#define __TIMR54XX_H__


/* L4 Based Timers */
/*#define OMAP5430_GPTIMER01_BASE       0x4A318000
#define OMAP5430_GPTIMER02_BASE       0x48032000
#define OMAP5430_GPTIMER03_BASE       0x48034000
#define OMAP5430_GPTIMER04_BASE       0x48036000
#define OMAP5430_GPTIMER09_BASE       0x4803E000
#define OMAP5430_GPTIMER10_BASE       0x48086000
#define OMAP5430_GPTIMER11_BASE       0x48088000
#define OMAP5430_WDTIMER2_BASE        0x4A314000*/

#define OMAP5430_REVISION	0x4AE04000
#define OMAP5430_SYSCONFIG	0x4AE04004
#define OMAP5430_CR		0x4AE04030


/* L3 Timers */
/*#define OMAP5430_GPTIMER05_BASE       0x49038000
#define OMAP5430_GPTIMER06_BASE       0x4903A000
#define OMAP5430_GPTIMER07_BASE       0x4903C000
#define OMAP5430_GPTIMER08_BASE       0x4903E000
#define OMAP5430_WDTIMER3_BASE        0x49030000*/

/* A9 Access to L3 Timers */
/*#define OMAP5430_GPTIMER05_A9BASE     0x40138000
#define OMAP5430_GPTIMER06_A9BASE     0x4013A000
#define OMAP5430_GPTIMER07_A9BASE     0x4013C000
#define OMAP5430_GPTIMER08_A9BASE     0x4013E000
#define OMAP5430_WDTIMER3_A9BASE      0x40130000*/

/* DSP Access to L3 Timers */
/*#define OMAP5430_GPTIMER05_DSPBASE    0x01D38000
#define OMAP5430_GPTIMER06_DSPBASE    0x01D3A000
#define OMAP5430_GPTIMER07_DSPBASE    0x01D3C000
#define OMAP5430_GPTIMER08_DSPBASE    0x01D3E000
#define OMAP5430_WDTIMER3_DSPBASE     0x01D30000*/


#endif
