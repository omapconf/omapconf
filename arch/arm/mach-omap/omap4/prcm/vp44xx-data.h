/*
 *
 * @Component			OMAPCONF
 * @Filename			vp44xx-data.h
 * @Description			OMAP4 VOLTAGE PROCESSOR Golden Settings
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


#ifndef __PRCM_VP44XX_DATA_H__
#define __PRCM_VP44XX_DATA_H__


#include <vp.h>
#include <vp44xx.h>
#include <voltdm44xx.h>
#include <cpuinfo.h>


extern const char vp44xx_mod_names[VP44XX_ID_MAX + 1][12];


extern const vp_audit_settings vp4430_mpu_opp50_golden_settings;
extern const vp_audit_settings vp4430_mpu_opp100_golden_settings;
extern const vp_audit_settings vp4430_mpu_oppturbo_golden_settings;
extern const vp_audit_settings vp4430_mpu_oppnitro_golden_settings;
extern const vp_audit_settings vp4430_mpu_oppnitrosb_golden_settings;
extern const vp_audit_settings *vp4430_mpu_golden_settings[OPP44XX_ID_MAX];

extern const vp_audit_settings vp4430_iva_opp50_golden_settings;
extern const vp_audit_settings vp4430_iva_opp100_golden_settings;
extern const vp_audit_settings vp4430_iva_oppturbo_golden_settings;
extern const vp_audit_settings *vp4430_iva_golden_settings[OPP44XX_ID_MAX];

extern const vp_audit_settings vp4430_core_opp50_golden_settings;
extern const vp_audit_settings vp4430_core_opp100_golden_settings;
extern const vp_audit_settings *vp4430_core_golden_settings[OPP44XX_ID_MAX];

extern const vp_audit_settings **vp4430_golden_settings[VP44XX_ID_MAX];


extern const vp_audit_settings vp4460_mpu_opp50_golden_settings;
extern const vp_audit_settings vp4460_mpu_opp100_golden_settings;
extern const vp_audit_settings vp4460_mpu_oppturbo_golden_settings;
extern const vp_audit_settings vp4460_mpu_oppnitro_golden_settings;
extern const vp_audit_settings vp4460_mpu_oppnitrosb_golden_settings;
extern const vp_audit_settings *vp4460_mpu_golden_settings[OPP44XX_ID_MAX];

extern const vp_audit_settings vp4460_iva_opp50_golden_settings;
extern const vp_audit_settings vp4460_iva_opp100_golden_settings;
extern const vp_audit_settings vp4460_iva_oppturbo_golden_settings;
extern const vp_audit_settings vp4460_iva_oppnitro_golden_settings;
extern const vp_audit_settings vp4460_iva_oppnitrosb_golden_settings;
extern const vp_audit_settings *vp4460_iva_golden_settings[OPP44XX_ID_MAX];

extern const vp_audit_settings vp4460_core_opp50_golden_settings;
extern const vp_audit_settings vp4460_core_opp100_golden_settings;
extern const vp_audit_settings vp4460_core_oppturbo_golden_settings;
extern const vp_audit_settings *vp4460_core_golden_settings[OPP44XX_ID_MAX];

extern const vp_audit_settings **vp4460_golden_settings[VP44XX_ID_MAX];


#if 0 /* FIXME when OMAP4470 golden settings available */
extern const vp_audit_settings vp4470_mpu_opp50_golden_settings;
extern const vp_audit_settings vp4470_mpu_opp100_golden_settings;
extern const vp_audit_settings vp4470_mpu_oppturbo_golden_settings;
extern const vp_audit_settings vp4470_mpu_oppnitro_golden_settings;
extern const vp_audit_settings vp4470_mpu_oppnitrosb_golden_settings;
extern const vp_audit_settings *vp4470_mpu_golden_settings[OPP44XX_ID_MAX];

extern const vp_audit_settings vp4470_iva_opp50_golden_settings;
extern const vp_audit_settings vp4470_iva_opp100_golden_settings;
extern const vp_audit_settings vp4470_iva_oppturbo_golden_settings;
extern const vp_audit_settings vp4470_iva_oppnitro_golden_settings;
extern const vp_audit_settings vp4470_iva_oppnitrosb_golden_settings;
extern const vp_audit_settings *vp4470_iva_golden_settings[OPP44XX_ID_MAX];

extern const vp_audit_settings vp4470_core_opp50_golden_settings;
extern const vp_audit_settings vp4470_core_opp100_golden_settings;
extern const vp_audit_settings vp4470_core_oppturbo_golden_settings;
extern const vp_audit_settings *vp4470_core_golden_settings[OPP44XX_ID_MAX];

extern const vp_audit_settings **vp4470_golden_settings[VP44XX_ID_MAX];
#endif


extern const vp_audit_settings ***vp44xx_golden_settings[OMAP_MAX];


#endif
