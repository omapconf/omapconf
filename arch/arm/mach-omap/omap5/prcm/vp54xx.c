/*
 *
 * @Component			OMAPCONF
 * @Filename			vp54xx.c
 * @Description			OMAP5 VOLTAGE PROCESSOR (VP) Definitions & Functions
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


#include <vp54xx.h>
#include <vp.h>
#include <lib.h>
#include <cpuinfo.h>
#include <prm54xx-defs.h>
#include <voltdm54xx.h>


/* #define VP54XX_DEBUG */
#ifdef VP54XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		vp54xx_config_show
 * @BRIEF		decode and show VP current configuration
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 * @param[in,out]	stream: output file (NULL: no output (silent))
 * @DESCRIPTION		decode and show VP current configuration
 *//*------------------------------------------------------------------------ */
int vp54xx_config_show(FILE *stream)
{
	vp_registers vp_regs[3];

	/* Store VP MPU registers */
	if (cpu_revision_get() == REV_ES1_0) {
		vp_regs[0].vdd_id = (unsigned int) VDD54XX_MPU;
		vp_regs[0].vp_config = reg_read(&omap5430es1_prm_vp_mpu_config);
		vp_regs[0].vp_status = reg_read(&omap5430es1_prm_vp_mpu_status);
		vp_regs[0].vp_vlimitto = reg_read(&omap5430es1_prm_vp_mpu_vlimitto);
		vp_regs[0].vp_voltage = reg_read(&omap5430es1_prm_vp_mpu_voltage);
		vp_regs[0].vp_vstepmax = reg_read(&omap5430es1_prm_vp_mpu_vstepmax);
		vp_regs[0].vp_vstepmin = reg_read(&omap5430es1_prm_vp_mpu_vstepmin);
	} else {
		vp_regs[0].vdd_id = (unsigned int) VDD54XX_MPU;
		vp_regs[0].vp_config = reg_read(&omap5430_prm_vp_mpu_config);
		vp_regs[0].vp_status = reg_read(&omap5430_prm_vp_mpu_status);
		vp_regs[0].vp_vlimitto = reg_read(&omap5430_prm_vp_mpu_vlimitto);
		vp_regs[0].vp_voltage = reg_read(&omap5430_prm_vp_mpu_voltage);
		vp_regs[0].vp_vstepmax = reg_read(&omap5430_prm_vp_mpu_vstepmax);
		vp_regs[0].vp_vstepmin = reg_read(&omap5430_prm_vp_mpu_vstepmin);
	}

	/* Store VP MM registers */
	if (cpu_revision_get() == REV_ES1_0) {
		vp_regs[1].vdd_id = (unsigned int) VDD54XX_MM;
		vp_regs[1].vp_config = reg_read(&omap5430es1_prm_vp_mm_config);
		vp_regs[1].vp_status = reg_read(&omap5430es1_prm_vp_mm_status);
		vp_regs[1].vp_vlimitto = reg_read(&omap5430es1_prm_vp_mm_vlimitto);
		vp_regs[1].vp_voltage = reg_read(&omap5430es1_prm_vp_mm_voltage);
		vp_regs[1].vp_vstepmax = reg_read(&omap5430es1_prm_vp_mm_vstepmax);
		vp_regs[1].vp_vstepmin = reg_read(&omap5430es1_prm_vp_mm_vstepmin);
	} else {
		vp_regs[1].vdd_id = (unsigned int) VDD54XX_MM;
		vp_regs[1].vp_config = reg_read(&omap5430_prm_vp_mm_config);
		vp_regs[1].vp_status = reg_read(&omap5430_prm_vp_mm_status);
		vp_regs[1].vp_vlimitto = reg_read(&omap5430_prm_vp_mm_vlimitto);
		vp_regs[1].vp_voltage = reg_read(&omap5430_prm_vp_mm_voltage);
		vp_regs[1].vp_vstepmax = reg_read(&omap5430_prm_vp_mm_vstepmax);
		vp_regs[1].vp_vstepmin = reg_read(&omap5430_prm_vp_mm_vstepmin);
	}

	/* Store VP CORE registers */
	if (cpu_revision_get() == REV_ES1_0) {
		vp_regs[2].vdd_id = (unsigned int) VDD54XX_CORE;
		vp_regs[2].vp_config = reg_read(&omap5430es1_prm_vp_core_config);
		vp_regs[2].vp_status = reg_read(&omap5430es1_prm_vp_core_status);
		vp_regs[2].vp_vlimitto = reg_read(&omap5430es1_prm_vp_core_vlimitto);
		vp_regs[2].vp_voltage = reg_read(&omap5430es1_prm_vp_core_voltage);
		vp_regs[2].vp_vstepmax = reg_read(&omap5430es1_prm_vp_core_vstepmax);
		vp_regs[2].vp_vstepmin = reg_read(&omap5430es1_prm_vp_core_vstepmin);
	} else {
		vp_regs[2].vdd_id = (unsigned int) VDD54XX_CORE;
		vp_regs[2].vp_config = reg_read(&omap5430_prm_vp_core_config);
		vp_regs[2].vp_status = reg_read(&omap5430_prm_vp_core_status);
		vp_regs[2].vp_vlimitto = reg_read(&omap5430_prm_vp_core_vlimitto);
		vp_regs[2].vp_voltage = reg_read(&omap5430_prm_vp_core_voltage);
		vp_regs[2].vp_vstepmax = reg_read(&omap5430_prm_vp_core_vstepmax);
		vp_regs[2].vp_vstepmin = reg_read(&omap5430_prm_vp_core_vstepmin);
	}

	return vp_config_show(stream, vp_regs);
}
