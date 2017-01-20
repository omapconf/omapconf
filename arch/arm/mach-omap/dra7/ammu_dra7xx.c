/*
 *
 * @Component                   OMAPCONF
 * @Filename                    ammu_dra7xx.c
 * @Description                 Functions Related to Parsing AMMU
 * @Author                      Brad Griffis (bgriffis@ti.com)
 * @Date                        2017
 * @Copyright                   Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/
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

#include <stdio.h>
#include <string.h>
#include <ammu.h>
#include <mem.h>
#include <lib.h>

/*
 * Defined in Section 3.14.11 "CM_CORE_AON__IPU Registers" of
 * AM572x TRM, SPRUHZ6 Rev H
 */
#define CM_IPU1_IPU1_CLKCTRL 0x4A005520u

/*
 * Defined in Section 3.14.20 "CM_CORE__CORE Registers" of
 * AM572x TRM, SPRUHZ6 Rev H
 */
#define CM_IPU2_IPU2_CLKCTRL 0x4A008920u

/* ------------------------------------------------------------------------*//**
 * @FUNCTION            dra7xx_ammu_decode
 * @BRIEF               Decodes all the AMMU page mappings
 * @RETURNS             0=success, non-zero error
 * @param[in]           ipu: Can be "all", "ipu1", or "ipu2"
 *//*------------------------------------------------------------------------ */
int dra7xx_ammu_decode(const char *ipu)
{
	unsigned int unicache_addr, ipu_clkctrl;
	int ret;

	if (strcmp(ipu, "all") == 0 ) {
		ret = dra7xx_ammu_decode("ipu1");
		if(ret != 0) return ret;
		ret = dra7xx_ammu_decode("ipu2");
		if(ret != 0) return ret;
	}

	if (strcmp(ipu, "ipu1") == 0) {
		ret = mem_read(CM_IPU1_IPU1_CLKCTRL, &ipu_clkctrl);
		if(ret != 0) return ret;
		if ((ipu_clkctrl & 0x3) == 0) {
			fprintf(stderr, "Cannot read from IPU1 while "
				"CM_IPU1_IPU1_CLKCTRL[1:0] = 0!\n");
			fprintf(stderr, "Linux users may try:\n"
				"echo on > "
				"/sys/bus/platform/devices/58820000.ipu/power/control\n");
			return OMAPCONF_ERR_REG_ACCESS;
		}
		/*
		 * Defined in Section 7.4.4 "IPUx_UNICACHE_MMU (AMMU)
		 * Registers" of AM572x TRM, SPRUHZ6 Rev H
		 */
		unicache_addr = 0x58880800;
		printf("**************************************************\n");
		printf("******   Decoding AMMU Mappings for IPU1    ******\n");
		printf("**************************************************\n\n");
	}

	if (strcmp(ipu, "ipu2") == 0) {
		ret = mem_read(CM_IPU2_IPU2_CLKCTRL, &ipu_clkctrl);
		if(ret != 0) return ret;
		if ((ipu_clkctrl & 0x3) == 0) {
			fprintf(stderr, "Cannot read from IPU2 while "
				"CM_IPU2_IPU2_CLKCTRL[1:0] = 0!\n");
			fprintf(stderr, "Linux users may try:\n"
				"echo on > "
				"/sys/bus/platform/devices/55020000.ipu/power/control\n");
			return OMAPCONF_ERR_REG_ACCESS;
		}
		/*
		 * Defined in Section 7.4.4 "IPUx_UNICACHE_MMU (AMMU)
		 * Registers" of AM572x TRM, SPRUHZ6 Rev H
		 */
		unicache_addr = 0x55080800;
		printf("**************************************************\n");
		printf("******   Decoding AMMU Mappings for IPU2    ******\n");
		printf("**************************************************\n\n");
	}

	/* DRA7xx AMMUs contain 4 large pages */
	ret = ammu_decode_large_page((unsigned int *)unicache_addr, 0u);
	if(ret != 0) return ret;
	ret = ammu_decode_large_page((unsigned int *)unicache_addr, 1u);
	if(ret != 0) return ret;
	ret = ammu_decode_large_page((unsigned int *)unicache_addr, 2u);
	if(ret != 0) return ret;
	ret = ammu_decode_large_page((unsigned int *)unicache_addr, 3u);
	if(ret != 0) return ret;

	/* DRA7xx AMMUs contain 2 medium pages */
	ret = ammu_decode_medium_page((unsigned int *)(unicache_addr + 0x60), 0u);
	if(ret != 0) return ret;
	ret = ammu_decode_medium_page((unsigned int *)(unicache_addr + 0x60), 1u);
	if(ret != 0) return ret;

	/* DRA7xx AMMUs contain 10 small pages */
	ret = ammu_decode_small_page((unsigned int *)(unicache_addr + 0x120), 0u);
	if(ret != 0) return ret;
	ret = ammu_decode_small_page((unsigned int *)(unicache_addr + 0x120), 1u);
	if(ret != 0) return ret;
	ret = ammu_decode_small_page((unsigned int *)(unicache_addr + 0x120), 2u);
	if(ret != 0) return ret;
	ret = ammu_decode_small_page((unsigned int *)(unicache_addr + 0x120), 3u);
	if(ret != 0) return ret;
	ret = ammu_decode_small_page((unsigned int *)(unicache_addr + 0x120), 4u);
	if(ret != 0) return ret;
	ret = ammu_decode_small_page((unsigned int *)(unicache_addr + 0x120), 5u);
	if(ret != 0) return ret;
	ret = ammu_decode_small_page((unsigned int *)(unicache_addr + 0x120), 6u);
	if(ret != 0) return ret;
	ret = ammu_decode_small_page((unsigned int *)(unicache_addr + 0x120), 7u);
	if(ret != 0) return ret;
	ret = ammu_decode_small_page((unsigned int *)(unicache_addr + 0x120), 8u);
	if(ret != 0) return ret;
	ret = ammu_decode_small_page((unsigned int *)(unicache_addr + 0x120), 9u);
	if(ret != 0) return ret;

	return ret;
}
