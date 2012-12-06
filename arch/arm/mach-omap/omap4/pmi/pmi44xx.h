/*
 *
 * @Component			OMAPCONF
 * @Filename			pmi44xx.h
 * @Description			Definition file for OMAP44xx PMI Module
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


#ifndef __PMI44XX_H__
#define __PMI44XX_H__

#include <genlist.h>
#include <voltdm44xx.h>

#define OMAP4430_PMI_REGADDR(module, reg) ((module) + (reg))

#define OMAP4430_PMI_BASE	0x4A307F00
#define OMAP4430_PMI_PIR	OMAP4430_PMI_REGADDR(OMAP4430_PMI_BASE, 0x00)
#define OMAP4430_PMI_PSCR	OMAP4430_PMI_REGADDR(OMAP4430_PMI_BASE, 0x10)
#define OMAP4430_PMI_PSR	OMAP4430_PMI_REGADDR(OMAP4430_PMI_BASE, 0x14)
#define OMAP4430_PMI_PCR	OMAP4430_PMI_REGADDR(OMAP4430_PMI_BASE, 0x24)
#define OMAP4430_PMI_PCFR	OMAP4430_PMI_REGADDR(OMAP4430_PMI_BASE, 0x28)
#define OMAP4430_PMI_PTCR	OMAP4430_PMI_REGADDR(OMAP4430_PMI_BASE, 0x2C)
#define OMAP4430_PMI_PSWR	OMAP4430_PMI_REGADDR(OMAP4430_PMI_BASE, 0x30)


typedef enum {
	PMI_VOLTDM_CLASS_LOGIC = 0,
	PMI_VOLTDM_CLASS_MEM = 1,
	PMI_PWRDM_CLASS_LOGIC = 2,
	PMI_PWRDM_CLASS_MEM = 3,
	PMI_EVENT_CLASS_MAX
} pmi_event_class;


typedef enum {
	/*
	 * OMAP4 WORKAROUND:
	 * timestamping clock depends on CORE domain state and OPP...
	 * So always need to capture logic pwrdm & logic voltage events ...
	 *
	 * OMAP4 DECISION: discard memory voltage domain events,
	 * due to HW limitation: OMAP4430 PMI only reports ON & sleep fsm states
	 * for memory domains, not OFF. To track this state, it would be also
	 * necessary to track power domain transitions. This is too much effort
	 * compared to usefulness of the feature (we are really interested in
	 * logic voltage (OPP and smart-reflex adjustments), not LDOs)
	 */
	PMI_EVENT_VOLTDM_OPP_CHANGE = (1 << PMI_VOLTDM_CLASS_LOGIC) +
		(1 << PMI_PWRDM_CLASS_LOGIC),
	PMI_EVENT_PWRDM_TRANSITION = (1 << PMI_PWRDM_CLASS_LOGIC) +
		(1 << PMI_PWRDM_CLASS_MEM) + (1 << PMI_VOLTDM_CLASS_LOGIC),
	PMI_EVENT_MAX
} pmi_event_class_type;

typedef struct {
	pmi_event_class class;
	unsigned int data_msb;
	unsigned int data_lsb;
	double ts; /* relative, in micro-seconds */
} pmi_event;

int pmi44xx_capture_enable(pmi_event_class_type class,
	unsigned int div, unsigned int window_size);
int pmi44xx_capture_disable(void);

int pmi44xx_trace_capture(pmi_event_class_type class,
	unsigned int time, unsigned short delay, char *file);
int pmi44xx_trace_decode(char *etb_trace, unsigned int lts_ref_clk,
	char *pmi_trace, double *duration, opp44xx_id vddcore_opp);
int pmi44xx_events_get(char *filename, genlist *pmi_events);

#endif
