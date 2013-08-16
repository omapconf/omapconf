/*
 *
 * @Component			OMAPCONF
 * @Filename			voltdomain.h
 * @Description			Generic Voltage Domain Definitions & APIs
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


#ifndef __VOLTDOMAIN_H__
#define __VOLTDOMAIN_H__


#include <genlist.h>
#include <reg.h>


#define VOLTDM_MAX_NAME_LENGTH		16

#define VDD_LDO_WKUP	((const char *) "LDO_WKUP") /* OMAP4 */
#define VDD_WKUP	((const char *) "VDD_WKUP") /* OMAP4 & OMAP5 */
#define VDD_MPU		((const char *) "VDD_MPU") /* Common */
#define VDD_IVA		((const char *) "VDD_IVA") /* OMAP4 & DRA7 */
#define VDD_MM		((const char *) "VDD_MM") /* OMAP5 */
#define VDD_CORE	((const char *) "VDD_CORE") /* Common */
#define VDD_RTC		((const char *) "VDD_RTC") /* DRA7 */
#define VDD_GPU		((const char *) "VDD_GPU") /* DRA7 */
#define VDD_DSPEVE	((const char *) "VDD_DSPEVE") /* DRA7 */


typedef struct {
	const char *name;
	int id;
	reg *voltst;
} voltdm_info;


void voltdm_init(void);
void voltdm_deinit(void);

const genlist *voltdm_list_get(void);
int voltdm_count_get(void);

int voltdm_s2id(const char *voltdm);

int voltdm_count_get(void);
const genlist *voltdm_list_get(void);

int voltdm_voltage_get(const char *voltdm);
int voltdm_voltage_set(const char *voltdm, int uv);

int voltdm_nominal_voltage_get(const char *voltdm);
int voltdm_por_nominal_voltage_get(const char *voltdm, const char *opp);


#endif
