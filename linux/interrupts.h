/*
 *
 * @Component			OMAPCONF
 * @Filename			interrupts.h
 * @Description			Linux Kernel /proc/interrupts APIs
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


#ifndef __INTERRUPTS_H__
#define __INTERRUPTS_H__


#include <stdio.h>
#include <stdlib.h>
#include <genlist.h>


#define IRQ_ERR_ARG		-1	/* incorrect argument(s) */
#define IRQ_ERR_CPU		-2	/* CPU architecture not supported */
#define IRQ_ERR_INTERNAL	-3	/* internal error */
#define IRQ_ERR_UNEXPECTED	-7	/* something unexpected occurred */
#define IRQ_ERR_NOT_AVAILABLE	-8	/* does not exist or not available */
#define IRQ_ERR_MALLOC		-13	/* memory allocation failure */


typedef struct {
	unsigned int nbr;
	unsigned int count;
	char dev_name[256];
} irq_info;


int irq_snapshot_save(char *file);

int irq_total_count_get(FILE *fp);
int irq_count_get(unsigned int n, FILE *fp);
char *irq_dev_name_get(unsigned int n, FILE *fp, char name[256]);

int irq_occurred(unsigned int n, FILE *fp1, FILE *fp2);
int irq_occurred_list_get(FILE *fp1, FILE *fp2, genlist *list);
int irq_occurred_list_sort(genlist *list);


#endif
