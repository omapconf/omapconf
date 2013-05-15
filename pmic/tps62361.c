/*
 *
 * @Component			OMAPCONF
 * @Filename			tps62361.c
 * @Description			OMAP4 TPS 62361 (SMPS Voltage Regulator) Library
 * @Author			Konstantin Shlyakhovoy (x0155534@ti.com)
 *				Patrick Titiano (p-titiano@ti.com)
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


#include <tps62361.h>
#include <lib.h>
#include <mem.h>
#include <cpuinfo.h>
#include <prm44xx.h>


/* #define TPS62361_DEBUG */
#ifdef TPS62361_DEBUG
#include <stdio.h>
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


#define TPS62361_VDCDC1_MIN	500000
#define TPS62361_VDCDC1_STEP	10000
#define TPS62361_PFM_FLAG	0x80



/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tps62361_is_present
 * @BRIEF		return 1 if TPS62361 is present on this platform,
 *			0 otherwise
 * @RETURNS		1 if TPS62361 chip is found
 *			0 otherwise
 * @DESCRIPTION		return 1 if TPS62361 is present on this platform,
 *			0 otherwise
 *//*------------------------------------------------------------------------ */
unsigned short int tps62361_is_present(void)
{
	/*
	 * SR-I2C link is write-only, cannot read-back any chip register ...
	 * Only way to know if this chip is present in the platform is to
	 * read the voltage controler registers and look for particular
	 * TPS62361 VDD_MPU slave address...
	 */
	unsigned int prm_vc_smps_sa;
	int ret;
	unsigned short present;

	switch (cpu_get()) {
	case OMAP_4430:
	case OMAP_4460:
	case OMAP_4470:
		ret = mem_read(OMAP4430_PRM_VC_SMPS_SA, &prm_vc_smps_sa);
		dprintf("%s(): OMAP4430_PRM_VC_SMPS_SA=0x%08X\n",
			__func__, prm_vc_smps_sa);
		if (ret != 0)
			present = 0;
		else
			present = (prm_vc_smps_sa == 0x00601212);
		break;
	case OMAP_5430:
	case OMAP_5432:
		present = 0;
		break;
	default:
		present = 0;
	}

	dprintf("%s(): present=%u\n", __func__, present);
	return present;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tps62361_chip_revision_get
 * @BRIEF		return TPS62361 chip revision
 * @RETURNS		> 0.0 TPS62361 chip revision
 *			OMAPCONF_ERR_NOT_AVAILABLE in case of error
 * @DESCRIPTION		return TPS62361 chip revision
 *//*------------------------------------------------------------------------ */
double tps62361_chip_revision_get(void)
{
	/* SR-I2C link is write-only, cannot read-back any chip register ... */
	return (double) OMAPCONF_ERR_NOT_AVAILABLE;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tps62361_eprom_revision_get
 * @BRIEF		return TPS62361 EPROM revision
 * @RETURNS		> 0.0 TPS62361 EPROM revision
 *			OMAPCONF_ERR_NOT_AVAILABLE in case of error
 * @DESCRIPTION		return TPS62361 EPROM revision
 *//*------------------------------------------------------------------------ */
double tps62361_eprom_revision_get(void)
{
	/* SR-I2C link is write-only, cannot read-back any chip register ... */
	return (double) OMAPCONF_ERR_NOT_AVAILABLE;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tps62361_smps_offset_get
 * @BRIEF		return SMPS regulator voltage offset
 * @RETURNS		voltage offset in microvolts
 * @DESCRIPTION		return SMPS regulator voltage offset
 *//*------------------------------------------------------------------------ */
long tps62361_smps_offset_get(void)
{
	dprintf("%s(): offset=%lduV\n", __func__, (long) TPS62361_VDCDC1_MIN);

	return (long) TPS62361_VDCDC1_MIN;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tps62361_smps_step_get
 * @BRIEF		return SMPS regulator voltage step in microvolts
 * @RETURNS		voltage step in microvolts
 * @DESCRIPTION		return SMPS regulator voltage step in microvolts
 *//*------------------------------------------------------------------------ */
long tps62361_smps_step_get(void)
{
	dprintf("%s(): step=%lduV\n", __func__, (long) TPS62361_VDCDC1_STEP);

	return (long) TPS62361_VDCDC1_STEP;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tps62361_vsel_len_get
 * @BRIEF		return the size of the vsel command
 * @RETURNS		SMPS regulator size of the vsel command
 * @DESCRIPTION		return the size of the vsel command
 *//*------------------------------------------------------------------------ */
int tps62361_vsel_len_get(void)
{
	return 8;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tps62361_vsel_to_uv
 * @BRIEF		for a given rail, convert SMPS vsel command into voltage
 *			in microvolts.
 * @RETURNS		voltage in microvolts corresponding to SMPS vsel command
 * @param[in]		vsel: SMPS vsel command (in microvolts)
 * @DESCRIPTION		for a given rail, convert SMPS vsel command into voltage
 *			in microvolts.
 *//*------------------------------------------------------------------------ */
unsigned long tps62361_vsel_to_uv(unsigned char vsel)
{
	unsigned long uv;

	vsel &= ~TPS62361_PFM_FLAG;
	uv = TPS62361_VDCDC1_MIN + (TPS62361_VDCDC1_STEP * vsel);
	dprintf("%s(%d)=%lduV\n", __func__, vsel, uv);
	return uv;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		tps62361_uv_to_vsel
 * @BRIEF		for a given rail, convert voltage in microvolts into
 *			SMPS vsel command.
 * @RETURNS		SMPS vsel command corresponding to uv
 * @param[in]		uv: voltage to be converted (in microvolts)
 * @DESCRIPTION		for a given rail, convert voltage in microvolts into
 *			SMPS vsel command.
 *//*------------------------------------------------------------------------ */
unsigned char tps62361_uv_to_vsel(unsigned long uv)
{
	unsigned char vsel;

	vsel = (unsigned char)
		DIV_ROUND_UP(uv - TPS62361_VDCDC1_MIN, TPS62361_VDCDC1_STEP);
	dprintf("%s(%lduV)=0x%02X\n", __func__, uv, vsel);
	return vsel;
}
