/*
 *
 * @Component			OMAPCONF
 * @Filename			prcm_dra7xx.c
 * @Description			OMAPCONF PRCM DRA7 Main file
 * @Author			Jin Zheng (j-zheng@ti.com)
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


#include <prcm_dra7xx.h>
#include <help.h>
#include <lib.h>
#include <string.h>
#include <cpuinfo.h>
#include <prm_dra7xx.h>
#include <cm_dra7xx.h>
#include <powerdomain.h>
#include <clockdomain.h>
#include <module.h>


/* #define PRCM_DRA7XX_DEBUG */
#ifdef PRCM_DRA7XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


typedef enum {
	PRCM_DRA7XX_IDX_EMU,
	PRCM_DRA7XX_IDX_WKUPAON,
	PRCM_DRA7XX_IDX_COREAON,
	PRCM_DRA7XX_IDX_CAM,
	PRCM_DRA7XX_IDX_CORE,
	PRCM_DRA7XX_IDX_DEV,
	PRCM_DRA7XX_IDX_CKGEN,
	PRCM_DRA7XX_IDX_INSTR,
	PRCM_DRA7XX_IDX_DSS,
	PRCM_DRA7XX_IDX_L3INIT,
	PRCM_DRA7XX_IDX_L4PER,
	PRCM_DRA7XX_IDX_DSP,
	PRCM_DRA7XX_IDX_GPU,
	PRCM_DRA7XX_IDX_IVA,
	PRCM_DRA7XX_IDX_MPU,
	PRCM_DRA7XX_IDX_ALL,
	PRCM_DRA7XX_IDX_MAX
} prcm_dra7xx_index;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm_dra7xx_emu_dump
 * @BRIEF		dump EMU PRCM registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump EMU PRCM registers and pretty-print it
 *			in selected output stream.
 *//*------------------------------------------------------------------------ */
static inline int _prcm_dra7xx_emu_dump(FILE *stream)
{
	int ret;

	ret = prm_dra7xx_dump(stream, PRM_DRA7XX_EMU_PRM);
	if (ret != 0)
		return ret;
	return cm_dra7xx_dump(stream, CM_DRA7XX_EMU_CM);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm_dra7xx_wkupaon_dump
 * @BRIEF		dump WKUPAON PRCM registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump WKUPAON PRCM registers and pretty-print it
 *			in selected output stream.
 *//*------------------------------------------------------------------------ */
static int _prcm_dra7xx_wkupaon_dump(FILE *stream)
{
	int ret;

	ret = prm_dra7xx_dump(stream, PRM_DRA7XX_WKUPAON_PRM);
	if (ret != 0)
		return ret;
	return cm_dra7xx_dump(stream, CM_DRA7XX_WKUPAON_CM);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm_dra7xx_coreaon_dump
 * @BRIEF		dump COREAON PRCM registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump COREAON PRCM registers and pretty-print it
 *			in selected output stream.
 *//*------------------------------------------------------------------------ */
static inline int _prcm_dra7xx_coreaon_dump(FILE *stream)
{
	int ret;

	ret = prm_dra7xx_dump(stream, PRM_DRA7XX_COREAON_PRM);
	if (ret != 0)
		return ret;
	return cm_dra7xx_dump(stream, CM_DRA7XX_COREAON_CM_CORE);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm_dra7xx_cam_dump
 * @BRIEF		dump CAM PRCM registers and pretty-print it
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump CAM PRCM registers and pretty-print it
 *			in selected output stream.
 *//*------------------------------------------------------------------------ */
static inline int _prcm_dra7xx_cam_dump(FILE *stream)
{
	int ret;

	ret = prm_dra7xx_dump(stream, PRM_DRA7XX_CAM_PRM);
	if (ret != 0)
		return ret;
	return cm_dra7xx_dump(stream, CM_DRA7XX_CAM_CM_CORE);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm_dra7xx_core_dump
 * @BRIEF		dump CORE PRCM registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump CORE PRCM registers and pretty-print it
 *			in selected output stream.
 *//*------------------------------------------------------------------------ */
static inline int _prcm_dra7xx_core_dump(FILE *stream)
{
	int ret;

	ret = prm_dra7xx_dump(stream, PRM_DRA7XX_CORE_PRM);
	if (ret != 0)
		return ret;
	ret = cm_dra7xx_dump(stream, CM_DRA7XX_CORE_CM_CORE);
	if (ret != 0)
		return ret;
	ret = cm_dra7xx_dump(stream, CM_DRA7XX_RESTORE_CM_CORE_AON);
	if (ret != 0)
		return ret;
	return cm_dra7xx_dump(stream, CM_DRA7XX_RESTORE_CM_CORE);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm_dra7xx_prmdev_dump
 * @BRIEF		dump PRM DEVICE PRCM registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump PRM DEVICE PRCM registers and pretty-print it
 *			in selected output stream.
 *//*------------------------------------------------------------------------ */
static inline int _prcm_dra7xx_prmdev_dump(FILE *stream)
{
	int ret;

	ret = prm_dra7xx_dump(stream, PRM_DRA7XX_CUSTEFUSE_PRM);
	if (ret != 0)
		return ret;
	ret = cm_dra7xx_dump(stream, CM_DRA7XX_CUSTEFUSE_CM_CORE);
	if (ret != 0)
		return ret;
	return prm_dra7xx_dump(stream, PRM_DRA7XX_DEVICE_PRM);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm_dra7xx_ckgen_dump
 * @BRIEF		dump CKGEN PRCM registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump CKGEN PRCM registers and pretty-print it
 *			in selected output stream.
 *//*------------------------------------------------------------------------ */
static inline int _prcm_dra7xx_ckgen_dump(FILE *stream)
{
	int ret;

	ret = prm_dra7xx_dump(stream, PRM_DRA7XX_CKGEN_PRM);
	if (ret != 0)
		return ret;
	ret = cm_dra7xx_dump(stream, CM_DRA7XX_CKGEN_CM_CORE_AON);
	if (ret != 0)
		return ret;
	return cm_dra7xx_dump(stream, CM_DRA7XX_CKGEN_CM_CORE);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm_dra7xx_instr_dump
 * @BRIEF		dump INSTR PRCM registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump INSTR PRCM registers and pretty-print it
 *			in selected output stream.
 *//*------------------------------------------------------------------------ */
static inline int _prcm_dra7xx_instr_dump(FILE *stream)
{
	int ret;

	if (prm_dra7xx_is_profiling_running()) {
		ret = prm_dra7xx_dump(stream, PRM_DRA7XX_INSTR_PRM);
		if (ret != 0)
			return ret;
	} else {
		printf("omapconf: PMI module is not accessible, skipping it.\n\n");
	}

	if (cm_dra7xx_is_profiling_running(CM_DRA7XX_INSTR_CM_CORE_AON)) {
		ret = cm_dra7xx_dump(stream, CM_DRA7XX_INSTR_CM_CORE_AON);
		if (ret != 0)
			return ret;
	} else {
		printf("omapconf: CMI_AON module is not accessible, skipping it.\n\n");
	}

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm_dra7xx_dss_dump
 * @BRIEF		dump DSS PRCM registers and pretty-print it
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump DSS PRCM registers and pretty-print it
 *			in selected output stream
 *//*------------------------------------------------------------------------ */
static inline int _prcm_dra7xx_dss_dump(FILE *stream)
{
	int ret;

	ret = prm_dra7xx_dump(stream, PRM_DRA7XX_DSS_PRM);
	if (ret != 0)
		return ret;
	return cm_dra7xx_dump(stream, CM_DRA7XX_DSS_CM_CORE);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm_dra7xx_l3init_dump
 * @BRIEF		dump L3INIT PRCM registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump L3INIT PRCM registers and pretty-print it
 *			in selected output stream.
 *//*------------------------------------------------------------------------ */
static inline int _prcm_dra7xx_l3init_dump(FILE *stream)
{
	int ret;

	ret = prm_dra7xx_dump(stream, PRM_DRA7XX_L3INIT_PRM);
	if (ret != 0)
		return ret;
	return cm_dra7xx_dump(stream, CM_DRA7XX_L3INIT_CM_CORE);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		l4per_dra7xx_dump
 * @BRIEF		dump L4PER PRCM registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump L4PER PRCM registers and pretty-print it
 *			in selected output stream.
 *//*------------------------------------------------------------------------ */
static inline int _prcm_dra7xx_l4per_dump(FILE *stream)
{
	int ret;

	ret = prm_dra7xx_dump(stream, PRM_DRA7XX_L4PER_PRM);
	if (ret != 0)
		return ret;
	return cm_dra7xx_dump(stream, CM_DRA7XX_L4PER_CM_CORE);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm_dra7xx_dsp_dump
 * @BRIEF		dump DSP PRCM registers and pretty-print it
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump DSP PRCM registers and pretty-print it
 *//*------------------------------------------------------------------------ */
static inline int _prcm_dra7xx_dsp_dump(FILE *stream)
{
	int ret;

	ret = prm_dra7xx_dump(stream, PRM_DRA7XX_DSP_PRM);
	if (ret != 0)
		return ret;
	return cm_dra7xx_dump(stream, CM_DRA7XX_DSP_CM_CORE_AON);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm_dra7xx_gpu_dump
 * @BRIEF		dump GPU PRCM registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump GPU PRCM registers and pretty-print it
 *			in selected output stream.
 *//*------------------------------------------------------------------------ */
static inline int _prcm_dra7xx_gpu_dump(FILE *stream)
{
	int ret;

	ret = prm_dra7xx_dump(stream, PRM_DRA7XX_GPU_PRM);
	if (ret != 0)
		return ret;
	return cm_dra7xx_dump(stream, CM_DRA7XX_GPU_CM_CORE);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm_dra7xx_iva_dump
 * @BRIEF		dump IVA PRCM registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump IVA PRCM registers and pretty-print it
 *			in selected output stream.
 *//*------------------------------------------------------------------------ */
static inline int _prcm_dra7xx_iva_dump(FILE *stream)
{
	int ret;

	ret = prm_dra7xx_dump(stream, PRM_DRA7XX_IVA_PRM);
	if (ret != 0)
		return ret;
	return cm_dra7xx_dump(stream, CM_DRA7XX_IVA_CM_CORE);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm_dra7xx_mpu_dump
 * @BRIEF		dump MPU PRCM registers
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump MPU PRCM registers and pretty-print it
 *			in selected output stream.
 *//*------------------------------------------------------------------------ */
static inline int _prcm_dra7xx_mpu_dump(FILE *stream)
{
	int ret;

	ret = prm_dra7xx_dump(stream, PRM_DRA7XX_OCP_SOCKET_PRM);
	if (ret != 0)
		return ret;
	ret = cm_dra7xx_dump(stream, CM_DRA7XX_OCP_SOCKET_CM_CORE);
	if (ret != 0)
		return ret;
	ret = cm_dra7xx_dump(stream, CM_DRA7XX_OCP_SOCKET_CM_CORE_AON);
	if (ret != 0)
		return ret;
	ret = prm_dra7xx_dump(stream, PRM_DRA7XX_PRCM_MPU_PRM_C0);
	if (ret != 0)
		return ret;
	ret = prm_dra7xx_dump(stream, PRM_DRA7XX_PRCM_MPU_PRM_C1);
	if (ret != 0)
		return ret;
	ret = prm_dra7xx_dump(stream, PRM_DRA7XX_MPU_PRM);
	if (ret != 0)
		return ret;
	return cm_dra7xx_dump(stream, CM_DRA7XX_MPU_CM_CORE_AON);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm_dra7xx_eve_dump
 * @BRIEF		dump EVE PRCM registers and pretty-print it
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump EVE PRCM registers and pretty-print it
 *//*------------------------------------------------------------------------ */
static inline int _prcm_dra7xx_eve_dump(FILE *stream)
{
	int ret;

	ret = prm_dra7xx_dump(stream, PRM_DRA7XX_EVE_PRM);
	if (ret != 0)
		return ret;
	return cm_dra7xx_dump(stream, CM_DRA7XX_EVE_CM_CORE_AON);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm_dra7xx_ipu_dump
 * @BRIEF		dump IPU PRCM registers and pretty-print it
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump IPU PRCM registers and pretty-print it
 *//*------------------------------------------------------------------------ */
static inline int _prcm_dra7xx_ipu_dump(FILE *stream)
{
	int ret;

	ret = prm_dra7xx_dump(stream, PRM_DRA7XX_IPU_PRM);
	if (ret != 0)
		return ret;
	return cm_dra7xx_dump(stream, CM_DRA7XX_IPU_CM_CORE_AON);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm_dra7xx_rtc_dump
 * @BRIEF		dump RTC PRCM registers and pretty-print it
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump rtc PRCM registers and pretty-print it
 *//*------------------------------------------------------------------------ */
static inline int _prcm_dra7xx_rtc_dump(FILE *stream)
{
	int ret;

	ret = prm_dra7xx_dump(stream, PRM_DRA7XX_RTC_PRM);
	if (ret != 0)
		return ret;
	return cm_dra7xx_dump(stream, CM_DRA7XX_RTC_CM_CORE_AON);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		_prcm_dra7xx_vpe_dump
 * @BRIEF		dump VPE PRCM registers and pretty-print it
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in,out]	stream: output stream
 * @DESCRIPTION		dump VPE PRCM registers and pretty-print it
 *//*------------------------------------------------------------------------ */
static inline int _prcm_dra7xx_vpe_dump(FILE *stream)
{
	int ret;

	ret = prm_dra7xx_dump(stream, PRM_DRA7XX_VPE_PRM);
	if (ret != 0)
		return ret;
	return cm_dra7xx_dump(stream, CM_DRA7XX_VPE_CM_CORE_AON);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		prcm_dra7xx_dump
 * @BRIEF		dump (formated in table) PRCM registers related to power
 *			domain provided in string s.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_CPU
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_REG_ACCESS
 * @param[in]		s: power domain
 * @DESCRIPTION		dump (formated in table) PRCM registers related to power
 *			domain provided in string s.
 *//*------------------------------------------------------------------------ */
int prcm_dra7xx_dump(char *s)
{
	int ret = 0;

	if ((s == NULL) || (strcmp(s, "all") == 0)) {
		/* ALL */
		ret = _prcm_dra7xx_emu_dump(stdout);
		ret |= _prcm_dra7xx_wkupaon_dump(stdout);
		ret |= _prcm_dra7xx_coreaon_dump(stdout);
		ret |= _prcm_dra7xx_cam_dump(stdout);
		ret |= _prcm_dra7xx_core_dump(stdout);
		ret |= _prcm_dra7xx_prmdev_dump(stdout);
		ret |= _prcm_dra7xx_ckgen_dump(stdout);
		ret |= _prcm_dra7xx_instr_dump(stdout);
		ret |= _prcm_dra7xx_dss_dump(stdout);
		ret |= _prcm_dra7xx_l3init_dump(stdout);
		ret |= _prcm_dra7xx_l4per_dump(stdout);
		ret |= _prcm_dra7xx_dsp_dump(stdout);
		ret |= _prcm_dra7xx_gpu_dump(stdout);
		ret |= _prcm_dra7xx_iva_dump(stdout);
		ret |= _prcm_dra7xx_mpu_dump(stdout);
		ret |= _prcm_dra7xx_eve_dump(stdout);
		ret |= _prcm_dra7xx_ipu_dump(stdout);
		ret |= _prcm_dra7xx_rtc_dump(stdout);
		ret |= _prcm_dra7xx_vpe_dump(stdout);
		return ret;
	} else if (strcmp(s, "emu") == 0) {
		return _prcm_dra7xx_emu_dump(stdout);
	} else if (strcmp(s, "wkupaon") == 0) {
		return _prcm_dra7xx_wkupaon_dump(stdout);
	} else if (strcmp(s, "coreaon") == 0) {
		return _prcm_dra7xx_coreaon_dump(stdout);
	} else if (strcmp(s, "cam") == 0) {
		return _prcm_dra7xx_cam_dump(stdout);
	} else if (strcmp(s, "core") == 0) {
		return _prcm_dra7xx_core_dump(stdout);
	} else if (strcmp(s, "dev") == 0) {
		return _prcm_dra7xx_prmdev_dump(stdout);
	} else if (strcmp(s, "ckgen") == 0) {
		return _prcm_dra7xx_ckgen_dump(stdout);
	} else if (strcmp(s, "instr") == 0) {
		return _prcm_dra7xx_instr_dump(stdout);
	} else if (strcmp(s, "dss") == 0) {
		return _prcm_dra7xx_dss_dump(stdout);
	} else if (strcmp(s, "l3init") == 0) {
		return _prcm_dra7xx_l3init_dump(stdout);
	} else if (strcmp(s, "l4per") == 0) {
		return _prcm_dra7xx_l4per_dump(stdout);
	} else if (strcmp(s, "dsp") == 0) {
		return _prcm_dra7xx_dsp_dump(stdout);
	} else if (strcmp(s, "gpu") == 0) {
		return _prcm_dra7xx_gpu_dump(stdout);
	} else if (strcmp(s, "iva") == 0) {
		return _prcm_dra7xx_iva_dump(stdout);
	} else if (strcmp(s, "mpu") == 0) {
		return _prcm_dra7xx_mpu_dump(stdout);
	} else if (strcmp(s, "eve") == 0) {
		return _prcm_dra7xx_eve_dump(stdout);
	} else if (strcmp(s, "ipu") == 0) {
		return _prcm_dra7xx_ipu_dump(stdout);
	} else if (strcmp(s, "rtc") == 0) {
		return _prcm_dra7xx_rtc_dump(stdout);
	} else if (strcmp(s, "vpe") == 0) {
		return _prcm_dra7xx_vpe_dump(stdout);
	} else {
		return err_arg_msg_show(HELP_PRCM);
	}
}
