/*
 *
 * @Component			OMAPCONF
 * @Filename			pmi44xx_voltdm.h
 * @Description			OMAP4 PMI Voltage Domain OPP Change Trace
 *				Decoding library
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


#ifndef __PMI44XX_VOLTDM_H__
#define __PMI44XX_VOLTDM_H__

#include <pmi44xx.h>
#include <genlist.h>


typedef enum {
	PMI44XX_VOLTDM_LOGIC_MPU = 0,
	PMI44XX_VOLTDM_LOGIC_IVA = 1,
	PMI44XX_VOLTDM_LOGIC_CORE = 2,
	PMI44XX_VOLTDM_LOGIC_MAX = 3
} pmi44xx_logic_voltdm_id;


typedef enum {
	PMI44XX_VOLTDM_MEM_MPU = 0,
	PMI44XX_VOLTDM_MEM_IVA = 1,
	PMI44XX_VOLTDM_MEM_CORE = 2,
	PMI44XX_VOLTDM_MEM_MAX = 3
} pmi44xx_mem_voltdm_id;


int pmi44xx_voltdm_transitions_extract(char *filename, genlist *transitions);
int pmi44xx_voltdm_transitions_save(genlist *transitions, double duration);


#endif
