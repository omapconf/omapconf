/*
 *
 * @Component			OMAPCONF
 * @Filename			crossbar_irq.c
 * @Description			DRA7 IRQ Crossbar
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


#include "lib.h"
#include "help.h"
#include "crossbar.h"
#include "crossbar_irq_data.h"


/* indices to each module crossbar */
#define MPU_IRQ		0
#define DSP1_IRQ	1
#define DSP2_IRQ	2
#define IPU1_IRQ	3
#define IPU2_IRQ	4
#define EVE1_IRQ	5
#define EVE2_IRQ	6
#define PRUSS1_IRQ	7
#define PRUSS2_IRQ	8

#define ASIZE(x) (sizeof(x) / sizeof((x)[0]))


struct irq_crossbar_list {
	struct cross_bar_module_input *ip;
	int size;
	char *name;
	char do_op;
};


static struct irq_crossbar_list dra7_irq_list[] = {
	[MPU_IRQ] = {
		     .ip = dra7_mpu_irq_crossbar,
		     .size = ASIZE(dra7_mpu_irq_crossbar),
		     .name = "mpu",
		     },
	[DSP1_IRQ] = {
		      .ip = dra7_dsp1_irq_crossbar,
		      .size = ASIZE(dra7_dsp1_irq_crossbar),
		      .name = "dsp1",
		      },
	[DSP2_IRQ] = {
		      .ip = dra7_dsp2_irq_crossbar,
		      .size = ASIZE(dra7_dsp2_irq_crossbar),
		      .name = "dsp2",
		      },
	[IPU1_IRQ] = {
		      .ip = dra7_ipu1_irq_crossbar,
		      .size = ASIZE(dra7_ipu1_irq_crossbar),
		      .name = "ipu1",
		      },
	[IPU2_IRQ] = {
		      .ip = dra7_ipu2_irq_crossbar,
		      .size = ASIZE(dra7_ipu2_irq_crossbar),
		      .name = "ipu2",
		      },
	[EVE1_IRQ] = {
		      .ip = dra7_eve1_irq_crossbar,
		      .size = ASIZE(dra7_eve1_irq_crossbar),
		      .name = "eve1",
		      },
	[EVE2_IRQ] = {
		      .ip = dra7_eve2_irq_crossbar,
		      .size = ASIZE(dra7_eve2_irq_crossbar),
		      .name = "eve2",
		      },
	[PRUSS1_IRQ] = {
		      .ip = dra7_pruss1_irq_crossbar,
		      .size = ASIZE(dra7_pruss1_irq_crossbar),
		      .name = "pruss1",
		      },
	[PRUSS2_IRQ] = {
		      .ip = dra7_pruss2_irq_crossbar,
		      .size = ASIZE(dra7_pruss2_irq_crossbar),
		      .name = "pruss2",
		      },
};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		dra7_crossbar_irq_op
 * @BRIEF		Do the IRQ crossbar operations
 * @RETURNS		0 on success
 *			OMAPCONF_ERR_ARG
 * @param[in]		stream: output stream
 * @param[in]		argc:	argument count
 * @param[in]		argv:	argument value
 * @param[in]		dump:	if 1, it does a dump operation, else audits
 *//*------------------------------------------------------------------------ */
static int dra7_crossbar_irq_op(FILE *stream, int argc, char *argv[], int dump)
{
	int r;
	unsigned int i;
	int errors = 0;
	int checks = 0;

	if (argc > 0)
		CHECK_NULL_ARG(argv, OMAPCONF_ERR_ARG);

	if (argc == 0 || !strcmp(argv[0], "all")) {
		for (i = 0; i < ASIZE(dra7_irq_list); i++)
			dra7_irq_list[i].do_op = 1;
	} else {
		/* Do an exact match first */
		for (i = 0; i < ASIZE(dra7_irq_list); i++) {
			if (!strcmp(argv[0], dra7_irq_list[i].name)) {
				dra7_irq_list[i].do_op = 1;
				goto skip_further;
			}
		}
		if (!strcmp(argv[0], "dsp")) {
			dra7_irq_list[DSP1_IRQ].do_op = 1;
			dra7_irq_list[DSP2_IRQ].do_op = 1;
		} else if (!strcmp(argv[0], "ipu")) {
			dra7_irq_list[IPU1_IRQ].do_op = 1;
			dra7_irq_list[IPU2_IRQ].do_op = 1;
		} else if (!strcmp(argv[0], "eve")) {
			dra7_irq_list[EVE1_IRQ].do_op = 1;
			dra7_irq_list[EVE2_IRQ].do_op = 1;
		} else if (!strcmp(argv[0], "pruss")) {
			dra7_irq_list[PRUSS1_IRQ].do_op = 1;
			dra7_irq_list[PRUSS2_IRQ].do_op = 1;
		} else {
			return OMAPCONF_ERR_ARG;
		}
	}

skip_further:
	/* Collect the data first */
	for (i = 0; i < ASIZE(dra7_irq_list); i++) {
		if (!dra7_irq_list[i].do_op)
			continue;

		r = dra7xx_crossbar_input_init(dra7_irq_list[i].name,
					       dra7_irq_list[i].ip,
					       dra7_irq_list[i].size,
					       DRA7_IRQCROSSBAR_MASK);
		if (r) {
			fprintf(stderr,
				"Failed reading %s cross bar registers - %d\n",
				dra7_irq_list[i].name, r);
			return r;
		}
	}

	/* Show the data */
	for (i = 0; i < ASIZE(dra7_irq_list); i++) {
		if (!dra7_irq_list[i].do_op)
			continue;

		if (dump) {
			r = dra7xx_crossbar_dump(stream, "IRQ Crossbar",
						 dra7_irq_list[i].name,
						 dra7_irq_list[i].ip,
						 dra7_irq_list[i].size,
						 dra7_irq_crossbar,
						 ASIZE(dra7_irq_crossbar));
		} else {
			r = dra7xx_crossbar_audit(stream, "IRQ Crossbar",
						  dra7_irq_list[i].name,
						  dra7_irq_list[i].ip,
						  dra7_irq_list[i].size,
						  dra7_irq_crossbar,
						  ASIZE(dra7_irq_crossbar),
						  &errors, &checks);
		}

		if (r) {
			fprintf(stderr,
				"Failed to %s IRQ cross bar %s - %d\n",
				dump ? "dump" : "audit",
				dra7_irq_list[i].name, r);
			return r;
		}
	}

	if (!dump)
		fprintf(stream, "\nCUMULATIVE SUMMARY: CHECKS=%d FAILS = %d\n\n",
			checks, errors);

	return 0;
}


int dra7_dump_crossbar_irq(FILE *stream, int argc, char *argv[])
{
	return dra7_crossbar_irq_op(stream, argc, argv, 1);
}


int dra7_audit_crossbar_irq(FILE *stream, int argc, char *argv[])
{
	return dra7_crossbar_irq_op(stream, argc, argv, 0);
}
