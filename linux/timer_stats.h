/*
 *
 * @Component			OMAPCONF
 * @Filename			timer_stats.h
 * @Description			Linux Kernel /proc/timer_stats APIs
 * @Author			Jon Hunter (jon-hunter@ti.com)
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


#ifndef __TIMERSTATS_H__
#define __TIMERSTATS_H__

#include <stdio.h>
#include <stdlib.h>
#include <genlist.h>


#define TIMER_ERR_ARG		-1	/* incorrect argument(s) */
#define TIMER_ERR_UNEXPECTED	-7	/* something unexpected occurred */
#define TIMER_ERR_NOT_AVAILABLE	-8	/* does not exist or not available */

typedef struct {
	unsigned int count;
	char deferrable[256];
	unsigned int pid;
	char name[256];
	char init_fxn[256];
	char callback[256];
} timerstat_info;

int timerstats_enabled(void);
int timerstats_stop(void);
int timerstats_start(void);
int timerstats_save(char *filename);
int timerstats_list_get(FILE *fp, genlist *list);
int timerstats_list_sort(genlist *list);
int timerstats_get_summary(FILE *fp, char *summary);

#endif /* __TIMERSTATS_H__ */
