/*
 *
 * @Component			OMAPCONF
 * @Filename			sr44xx-data.c
 * @Description			OMAP4 SMARTREFLEX AVS Definitions &
 *				Golden Settings
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


#include <sr44xx-data.h>


const char sr44xx_mod_names[OMAP4_SR_ID_MAX + 1][12] = {
	"SR MPU",
	"SR IVA",
	"SR CORE",
	"FIXME"};


const sr_audit_settings sr4430_mpu_opp50_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = 0xF5,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings sr4430_mpu_opp100_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = 0xF9,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings sr4430_mpu_oppturbo_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = 0xFA,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings sr4430_mpu_oppnitro_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = 0xFC,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings sr4430_mpu_oppnitrosb_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = 0xFD,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings *sr4430_mpu_golden_settings[OPP44XX_ID_MAX] = {
	&sr4430_mpu_opp50_golden_settings,
	&sr4430_mpu_opp50_golden_settings,
	&sr4430_mpu_opp100_golden_settings,
	&sr4430_mpu_oppturbo_golden_settings,
	&sr4430_mpu_oppnitro_golden_settings,
	&sr4430_mpu_oppnitrosb_golden_settings};


const sr_audit_settings sr4430_iva_opp50_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = 0xF5,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings sr4430_iva_opp100_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = 0xF9,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings sr4430_iva_oppturbo_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = 0xFA,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings *sr4430_iva_golden_settings[OPP44XX_ID_MAX] = {
	&sr4430_iva_opp50_golden_settings,
	&sr4430_iva_opp50_golden_settings,
	&sr4430_iva_opp100_golden_settings,
	&sr4430_iva_oppturbo_golden_settings,
	NULL,
	NULL};


const sr_audit_settings sr4430_core_opp50_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = 0xF5,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings sr4430_core_opp100_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = 0xF9,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings *sr4430_core_golden_settings[OPP44XX_ID_MAX] = {
	&sr4430_core_opp50_golden_settings,
	&sr4430_core_opp50_golden_settings,
	&sr4430_core_opp100_golden_settings,
	NULL,
	NULL,
	NULL};


const sr_audit_settings **sr4430_golden_settings[OMAP4_SR_ID_MAX] = {
	(const sr_audit_settings **) &sr4430_mpu_golden_settings,
	(const sr_audit_settings **) &sr4430_iva_golden_settings,
	(const sr_audit_settings **) &sr4430_core_golden_settings};


const sr_audit_settings sr4460_mpu_opp50_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = 0xF3,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings sr4460_mpu_opp100_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = 0xF8,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings sr4460_mpu_oppturbo_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = 0xFA,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings sr4460_mpu_oppnitro_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = 0xFB,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings sr4460_mpu_oppnitrosb_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = 0xFC,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings *sr4460_mpu_golden_settings[OPP44XX_ID_MAX] = {
	&sr4460_mpu_opp50_golden_settings,
	&sr4460_mpu_opp50_golden_settings,
	&sr4460_mpu_opp100_golden_settings,
	&sr4460_mpu_oppturbo_golden_settings,
	&sr4460_mpu_oppnitro_golden_settings,
	&sr4460_mpu_oppnitrosb_golden_settings};


const sr_audit_settings sr4460_iva_opp50_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = 0xF3,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings sr4460_iva_opp100_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = 0xF8,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings sr4460_iva_oppturbo_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = 0xFA,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings sr4460_iva_oppnitro_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = 0xFB,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings sr4460_iva_oppnitrosb_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = 0xFC,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings *sr4460_iva_golden_settings[OPP44XX_ID_MAX] = {
	&sr4460_iva_opp50_golden_settings,
	&sr4460_iva_opp50_golden_settings,
	&sr4460_iva_opp100_golden_settings,
	&sr4460_iva_oppturbo_golden_settings,
	&sr4460_iva_oppnitro_golden_settings,
	&sr4460_iva_oppnitrosb_golden_settings};


const sr_audit_settings sr4460_core_opp50_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = 0xF3,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings sr4460_core_opp100_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = 0xF8,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings sr4460_core_oppturbo_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = 0xFA,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings *sr4460_core_golden_settings[OPP44XX_ID_MAX] = {
	&sr4460_core_opp50_golden_settings,
	&sr4460_core_opp50_golden_settings,
	&sr4460_core_opp100_golden_settings,
	&sr4460_core_oppturbo_golden_settings,
	NULL,
	NULL};


const sr_audit_settings **sr4460_golden_settings[OMAP4_SR_ID_MAX] = {
	(const sr_audit_settings **) &sr4460_mpu_golden_settings,
	(const sr_audit_settings **) &sr4460_iva_golden_settings,
	(const sr_audit_settings **) &sr4460_core_golden_settings};


#if 0 /* FIXME when OMAP4470 golden settings available */
const sr_audit_settings sr4470_mpu_opp50_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = ,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings sr4470_mpu_opp100_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = ,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings sr4470_mpu_oppturbo_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = ,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings sr4470_mpu_oppnitro_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = ,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings sr4470_mpu_oppnitrosb_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = ,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings *sr4470_mpu_golden_settings[OPP44XX_ID_MAX] = {
	&sr4470_mpu_opp50_golden_settings,
	&sr4470_mpu_opp50_golden_settings,
	&sr4470_mpu_opp100_golden_settings,
	&sr4470_mpu_oppturbo_golden_settings,
	&sr4470_mpu_oppnitro_golden_settings,
	&sr4470_mpu_oppnitrosb_golden_settings};


const sr_audit_settings sr4470_iva_opp50_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = ,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings sr4470_iva_opp100_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = ,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings *sr4470_iva_golden_settings[OPP44XX_ID_MAX] = {
	&sr4470_iva_opp50_golden_settings,
	&sr4470_iva_opp50_golden_settings,
	&sr4470_iva_opp100_golden_settings,
	&sr4470_iva_oppturbo_golden_settings,
	&sr4470_iva_oppnitro_golden_settings,
	&sr4470_iva_oppnitrosb_golden_settings};



const sr_audit_settings sr4470_core_opp50_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = ,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings sr4470_core_opp100_golden_settings = {
	.sr_sysclk = 100.0,
	.irqmode = {0, 0, 0, 0, 1},
	.sensornmode = 1,
	.sensorpmode = 1,
	.minmaxavg_detector_mode = 0,
	.errgen_mode = 1,
	.idle_mode = MOD_SMART_IDLE_WAKEUP,
	.wakeupenable = 1,
	.errminlimit = ,
	.errmaxlimit = 0x02,
	.errweight = 4,
	.converged = 1};


const sr_audit_settings *sr4470_core_golden_settings[OPP44XX_ID_MAX] = {
	&sr4470_core_opp50_golden_settings,
	&sr4470_core_opp50_golden_settings,
	&sr4470_core_opp100_golden_settings,
	&sr4470_core_oppturbo_golden_settings,
	NULL,
	NULL};
#endif


const sr_audit_settings ***sr44xx_golden_settings[OMAP_MAX] = {
	(const sr_audit_settings ***) &sr4430_golden_settings,
	(const sr_audit_settings ***) &sr4460_golden_settings,
	#if 1 /* FIXME when OMAP4470 golden settings available */
	NULL,
	#else
	(const sr_audit_settings ***) &sr4470_golden_settings,
	#endif
	NULL,
	NULL};
