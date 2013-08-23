/*
 *
 * @Component			OMAPCONF
 * @Filename			crossbar.h
 * @Description			DRA7 Crossbar
 * @Author			Nishanth Menon
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
#include <stdlib.h>
#include <stdio.h>

#ifndef _DRA7_CROSS_BAR_H
#define _DRA7_CROSS_BAR_H

/* indexed by input number */
struct cross_bar_input {
	char *name;
	char *source;
	char *description;
};

/* indexed by input number */
struct cross_bar_module_input {
	unsigned int reg;
	int input;
	char *name;
	char *source;
	char *description;
};

/* Generic crossbar helpers */
int dra7xx_crossbar_input_init(char *module_name,
			       struct cross_bar_module_input *minput,
			       int minput_size, unsigned int mask);
int dra7xx_crossbar_dump(FILE * stream, char *type, char *module_name,
			 struct cross_bar_module_input *minput, int minput_size,
			 struct cross_bar_input *cinput, int cinput_size);
int dra7xx_crossbar_audit(FILE * stream, char *type, char *module_name,
			  struct cross_bar_module_input *minput,
			  int minput_size, struct cross_bar_input *cinput,
			  int cinput_size, int *tot_error, int *tot_checks);

/* Specific crossbar calls */
int dra7_dump_crossbar_irq(FILE * stream, int argc, char *argv[]);
int dra7_audit_crossbar_irq(FILE * stream, int argc, char *argv[]);

/* Entry calls */
int dra7_crossbar_dump_main(int argc, char *argv[]);
int dra7_crossbar_audit_main(int argc, char *argv[]);

#endif				/* _DRA7_CROSS_BAR_H */
