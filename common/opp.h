/*
 *
 * @Component			OMAPCONF
 * @Filename			opp.h
 * @Description			OPerating Point (OPP) Common Definitions
 *				& Functions
 * @Author			Patrick Titiano (p-titiano@ti.com)
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


#ifndef __OPP_H__
#define __OPP_H__


#include <stdio.h>
#include <genlist.h>


#define OPP_MAX_NAME_LENGTH	16

/* COMMON  OPP */
#define OPP_UNKNOWN		((const char *) "UNKNOWN")

/* OMAP4, OMAP5 OPP */
#define OPP_DPLL_CASC		((const char *) "DPLL_CASC")

/* OMAP4 OPP */
#define OPP_50			((const char *) "OPP50")
#define OPP_50_LOW		((const char *) "OPP50_LOW")
#define OPP_50_HIGH		((const char *) "OPP50_HIGH")
#define OPP_100			((const char *) "OPP100")
#define OPP_100_LOW		((const char *) "OPP100_LOW")
#define OPP_100_HIGH		((const char *) "OPP100_HIGH")
#define OPP_119			((const char *) "OPP119")
#define OPP_119_LOW		((const char *) "OPP119_LOW")
#define OPP_119_HIGH		((const char *) "OPP119_HIGH")
#define OPP_TURBO		((const char *) "OPP_TURBO")
#define OPP_NITRO		((const char *) "OPP_NITRO")
#define OPP_NITROSB		((const char *) "OPP_NITRO_SB")
#define OPP_VHS			((const char *) "OPP_VHS")

/* OMAP5 OPP */
#define OPP_LOW			((const char *) "LOW")
#define OPP_NOM			((const char *) "NOM")
#define OPP_OD			((const char *) "OVERDRIVE")
#define OPP_HIGH		((const char *) "HIGH")
#define OPP_SB			((const char *) "SPEEDBIN")

/* AM335X OPP */
#define OPP_120			((const char *) "OPP120")


typedef struct {
	const char *name;
	int voltage; /* in micro-volt */
	int rate; /* in KHz */
} opp_t;


void opp_init(void);
void opp_deinit(void);

int opp_s2id(const char *opp);

int opp_count_get(const char *voltdm);
const genlist *opp_list_get(const char *voltdm);

const char *opp_get(const char *voltdm, unsigned int quiet);
const char *opp_by_rate_get(const char *voltdm, unsigned short quiet);
#if 0
const char *opp_by_voltage_get(const char *voltdm, unsigned short quiet);
#endif
int opp_set(const char *voltdm, const char *opp);

int opp_show(FILE *stream);

const char *opp_audit(FILE *stream, const char *voltdm,
	unsigned int *err_nbr, unsigned int *wng_nbr);


#endif
