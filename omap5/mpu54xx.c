/*
 *
 * @Component			OMAPCONF
 * @Filename			mpu54xx.c
 * @Description			OMAP5 PRCM MPU Definitions & Functions
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


#include <mpu54xx.h>
#include <prm54xx.h>
#include <cm54xx.h>


/* #define MPU54XX_DEBUG */
#ifdef MPU54XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mpu54xx_dump
 * @BRIEF		dump MPU PRCM registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump MPU PRCM registers and pretty-print it
 *			in selected output stream.
 *//*------------------------------------------------------------------------ */
inline int mpu54xx_dump(FILE *stream)
{
	int ret;

	ret = prm54xx_dump(stream, PRM54XX_OCP_SOCKET_PRM);
	if (ret != 0)
		return ret;
	ret = prm54xx_dump(stream, PRM54XX_PRCM_MPU_PRM_C0);
	if (ret != 0)
		return ret;
	ret = prm54xx_dump(stream, PRM54XX_PRCM_MPU_PRM_C1);
	if (ret != 0)
		return ret;
	ret = prm54xx_dump(stream, PRM54XX_MPU_PRM);
	if (ret != 0)
		return ret;
	return cm54xx_dump(stream, CM54XX_MPU_CM_CORE_AON);
}
