/*
 *
 * @Component			OMAPCONF
 * @Filename			l2cc44xx.c
 * @Description			Dump L2CC registers Config/Analyse L2CC events
 * @Author			Steve Korson (s-korson@ti.com)
 * @Date			2012
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
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


#ifndef __L2CC44XX_H__
#define __L2CC44XX_H__

/* Base address */
/* Registers offset */

/* skorson */
/* Defines and Regisers for L2CC (PL310) Defined in mpuss44xx.h */

int l2cc44xx_perf_cnt_enable();
int l2cc44xx_perf_cnt_disable();
unsigned int l2cc44xx_get_perf_cnt(unsigned int counter_inst);
int l2cc44xx_name2addr(char *name, unsigned int *addr);
int l2cc44xx_event2val(char *event, unsigned int *value);
int l2cc44xx_event2desc(char *event, char *desc);
int l2cc44xx_main(int argc, char *argv[]);

int l2cc44xx_perf_cnt_configure(unsigned int counter_inst,
	unsigned int filter, unsigned int reset);
unsigned int l2cc44xx_perf_cnt_get_count(unsigned int counter_inst);

#endif
