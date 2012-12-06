/*
 *
 * @Component			OMAPCONF
 * @Filename			clkdm_dependency.h
 * @Description			Clock Domain Dependencies Common Definitions &
 *				Functions
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


#ifndef __PRCM_CLKDM_DEPENDENCY_H__
#define __PRCM_CLKDM_DEPENDENCY_H__


#include <stdio.h>


#define CLKDMDEP_TYPE_MAX_NAME_LENGTH		8
#define CLKDMDEP_CTRL_TYPE_MAX_NAME_LENGTH	4
#define CLKDMDEP_STATUS_MAX_NAME_LENGTH		9


typedef enum {
	CLKDMDEP_STATIC,
	CLKDMDEP_DYNAMIC,
	CLKDMDEP_TYPE_MAX
} clkdmdep_type;


typedef enum {
	CLKDMDEP_NA, /* not available, does not exist */
	CLKDMDEP_RW, /* available, SW-configurable */
	CLKDMDEP_RO, /* available, not configurable (hard-coded) */
	CLKDMDEP_CONTROL_TYPE_MAX
} clkdmdep_ctrl_type;


typedef enum {
	CLKDMDEP_DIS,		/* dependency is disabled */
	CLKDMDEP_EN,		/* dependency is enabled */
	CLKDMDEP_STATUS_MAX
} clkdmdep_status;



const char *clkdmdep_type_name_get(clkdmdep_type type);
const char *clkdmdep_ctrl_type_name_get(clkdmdep_ctrl_type type);
const char *clkdmdep_status_name_get(clkdmdep_status st);


#endif
