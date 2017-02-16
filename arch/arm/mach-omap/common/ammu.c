/*
 *
 * @Component                   OMAPCONF
 * @Filename                    ammu.c
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
#include <mem.h>
#include <lib.h>

/* ------------------------------------------------------------------------*//**
 * @FUNCTION            ammu_decode_large_page
 * @BRIEF               decodes the parameters for a large page from the ammu
 * @RETURNS             0=success, non-zero error
 * @param[in]           p_base_addr: pointer to first large page
 * @param[in]           page_num: page 0-3
 *//*------------------------------------------------------------------------ */
int ammu_decode_large_page(unsigned int *p_base_addr, unsigned int page_num) {
	unsigned int phys_addr, logical_addr, policy_reg, size;
	int ret;

	printf("*** Decoding Large Page %d  ***\n", page_num);

	/* Read CACHE_MMU_LARGE_ADDR_i */
	ret = mem_read((unsigned int)&p_base_addr[page_num], &logical_addr);
	if (ret != 0) {
		fprintf(stderr, "internal error (failed to read)!\n");
		return OMAPCONF_ERR_REG_ACCESS;
	}
	printf("CACHE_MMU_LARGE_ADDR_%d = 0x%08X\n", page_num, logical_addr);

	/* Read CACHE_MMU_LARGE_XLTE_i */
	ret = mem_read((unsigned int)&p_base_addr[8+page_num], &phys_addr);
	if (ret != 0) {
		fprintf(stderr, "internal error (failed to read)!\n");
		return OMAPCONF_ERR_REG_ACCESS;
	}
	printf("CACHE_MMU_LARGE_XLTE_%d = 0x%08X\n", page_num, phys_addr);

	/* Read CACHE_MMU_LARGE_POLICY_i */
	ret = mem_read((unsigned int)&p_base_addr[16+page_num], &policy_reg);
	if (ret != 0) {
		fprintf(stderr, "internal error (failed to read)!\n");
		return OMAPCONF_ERR_REG_ACCESS;
	}
	printf("CACHE_MMU_LARGE_POLICY_%d = 0x%08X\n", page_num, policy_reg);

	if( (policy_reg&1) == 0 ) {
		printf("\nPAGE NOT ENABLED\n");
	} else {
		printf("\nPAGE ENABLED\n");

		printf("Logical Address  = 0x%08X", logical_addr);
		if( (policy_reg & 1<<1) == 1<<1 ) {
			size = 512 * 1024 * 1024; /* 512 MB */
		} else {
			size = 32 * 1024 * 1024; /* 32MB */
		}
		printf(" - 0x%08X\n", (logical_addr+size-1));

		if ( (phys_addr&1) == 1 ) { /* "ignore" bit */
			phys_addr = logical_addr;
		}
		printf("Physical address = 0x%08X - 0x%08X\n", phys_addr, phys_addr+size-1);

		printf("Policy\n");

		if( (policy_reg & 1<<19) == 1<<19 ) {
			printf(" * L1 write policy is writeback\n");
		} else {
			printf(" * L1 write policy is writethrough\n");
		}

		if( (policy_reg & 1<<18) == 1<<18 ) {
			printf(" * L1 allocate policy: follow sideband\n");
		} else {
			printf(" * L1 allocate policy: no writes allocated\n");
		}

		if( (policy_reg & 1<<17) == 1<<17 ) {
			printf(" * L1 writes posted\n");
		} else {
			printf(" * L1 writes non-posted\n");
		}

		if( (policy_reg & 1<<16) == 1<<16 ) {
			printf(" * L1 cacheable\n");
		} else {
			printf(" * L1 noncacheable\n");
		}

		if( (policy_reg & 1<<7) == 1<<7 ) {
			printf(" * Send cache exclusion sideband\n");
		} else {
			printf(" * Do not send cache exclusion sideband\n");
		}

		if( (policy_reg & 1<<6) == 1<<6 ) {
			printf(" * Preload enabled\n");
		} else {
			printf(" * Preload disabled\n");
		}

		if( (policy_reg & 1<<5) == 1<<5 ) {
			printf(" * Read-only\n");
		} else {
			printf(" * Read/Write\n");
		}

		if( (policy_reg & 1<<4) == 1<<4 ) {
			printf(" * Execute-only\n");
		} else {
			printf(" * Read/Write/Execute\n");
		}

		if( (policy_reg & 1<<3) == 1<<3 ) {
			printf(" * Follow volatile qualifier\n");
		} else {
			printf(" * Do not follow volatile qualifier\n");
		}

		if( (policy_reg & 1<<1) == 1<<1 ) {
			printf(" * 512 MB page\n");
		} else {
			printf(" * 32 MB page\n");
		}
	}

	printf("\n");

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION            ammu_decode_medium_page
 * @BRIEF               decodes the parameters for a medium page from the ammu
 * @RETURNS             0=success, non-zero error
 * @param[in]           p_base_addr: pointer to first medium page
 * @param[in]           page_num: page 0-1
 *//*------------------------------------------------------------------------ */
int ammu_decode_medium_page(unsigned int *p_base_addr, unsigned int page_num) {
	unsigned int phys_addr, logical_addr, policy_reg, size;
	int ret;

	printf("*** Decoding Medium Page %d  ***\n", page_num);

	/* Read CACHE_MMU_MEDIUM_ADDR_i */
	ret = mem_read((unsigned int)&p_base_addr[page_num], &logical_addr);
	if (ret != 0) {
		fprintf(stderr, "internal error (failed to read)!\n");
		return OMAPCONF_ERR_REG_ACCESS;
	}
	printf("CACHE_MMU_MEDIUM_ADDR_%d = 0x%08X\n", page_num, logical_addr);

	/* Read CACHE_MMU_MEDIUM_XLTE_i */
	ret = mem_read((unsigned int)&p_base_addr[16+page_num], &phys_addr);
	if (ret != 0) {
		fprintf(stderr, "internal error (failed to read)!\n");
		return OMAPCONF_ERR_REG_ACCESS;
	}
	printf("CACHE_MMU_MEDIUM_XLTE_%d = 0x%08X\n", page_num, phys_addr);

	/* Read CACHE_MMU_MEDIUM_POLICY_i */
	ret = mem_read((unsigned int)&p_base_addr[32+page_num], &policy_reg);
	if (ret != 0) {
		fprintf(stderr, "internal error (failed to read)!\n");
		return OMAPCONF_ERR_REG_ACCESS;
	}
	printf("CACHE_MMU_MEDIUM_POLICY_%d = 0x%08X\n", page_num, policy_reg);

	if( (policy_reg&1) == 0 ) {
		printf("\nPAGE NOT ENABLED\n");
	} else {
		printf("\nPAGE ENABLED\n");

		printf("Logical Address  = 0x%08X", logical_addr);
		if( (policy_reg & 1<<1) == 1<<1 ) {
			size = 256 * 1024; /* 256 KB */
		} else {
			size = 128 * 1024; /* 128 KB */
		}
		printf(" - 0x%08X\n", (logical_addr+size-1));

		if ( (phys_addr&1) == 1 ) { /* "ignore" bit */
			phys_addr = logical_addr;
		}
		printf("Physical address = 0x%08X - 0x%08X\n", phys_addr, phys_addr+size-1);

		printf("Policy\n");

		if( (policy_reg & 1<<19) == 1<<19 ) {
			printf(" * L1 write policy is writeback\n");
		} else {
			printf(" * L1 write policy is writethrough\n");
		}

		if( (policy_reg & 1<<18) == 1<<18 ) {
			printf(" * L1 allocate policy: follow sideband\n");
		} else {
			printf(" * L1 allocate policy: no writes allocated\n");
		}

		if( (policy_reg & 1<<17) == 1<<17 ) {
			printf(" * L1 writes posted\n");
		} else {
			printf(" * L1 writes non-posted\n");
		}

		if( (policy_reg & 1<<16) == 1<<16 ) {
			printf(" * L1 cacheable\n");
		} else {
			printf(" * L1 noncacheable\n");
		}

		if( (policy_reg & 1<<7) == 1<<7 ) {
			printf(" * Send cache exclusion sideband\n");
		} else {
			printf(" * Do not send cache exclusion sideband\n");
		}

		if( (policy_reg & 1<<6) == 1<<6 ) {
			printf(" * Preload enabled\n");
		} else {
			printf(" * Preload disabled\n");
		}

		if( (policy_reg & 1<<5) == 1<<5 ) {
			printf(" * Read-only\n");
		} else {
			printf(" * Read/Write\n");
		}

		if( (policy_reg & 1<<4) == 1<<4 ) {
			printf(" * Execute-only\n");
		} else {
			printf(" * Read/Write/Execute\n");
		}

		if( (policy_reg & 1<<3) == 1<<3 ) {
			printf(" * Follow volatile qualifier\n");
		} else {
			printf(" * Do not follow volatile qualifier\n");
		}

		if( (policy_reg & 1<<1) == 1<<1 ) {
			printf(" * 256 KB page\n");
		} else {
			printf(" * 128 KB page\n");
		}
	}

	printf("\n");

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION            ammu_decode_small_page
 * @BRIEF               decodes the parameters for a small page from the ammu
 * @RETURNS             0=success, non-zero error
 * @param[in]           p_base_addr: pointer to first small page
 * @param[in]           page_num: page 0-9
 *//*------------------------------------------------------------------------ */
int ammu_decode_small_page(unsigned int *p_base_addr, unsigned int page_num) {
	unsigned int phys_addr, logical_addr, policy_reg, size;
	int ret;

	printf("*** Decoding Small Page %d  ***\n", page_num);

	/* Read CACHE_MMU_SMALL_ADDR_i */
	ret = mem_read((unsigned int)&p_base_addr[page_num], &logical_addr);
	if (ret != 0) {
		fprintf(stderr, "internal error (failed to read)!\n");
		return OMAPCONF_ERR_REG_ACCESS;
	}
	printf("CACHE_MMU_SMALL_ADDR_%d = 0x%08X\n", page_num, logical_addr);

	/* Read CACHE_MMU_SMALL_XLTE_i */
	ret = mem_read((unsigned int)&p_base_addr[32+page_num], &phys_addr);
	if (ret != 0) {
		fprintf(stderr, "internal error (failed to read)!\n");
		return OMAPCONF_ERR_REG_ACCESS;
	}
	printf("CACHE_MMU_SMALL_XLTE_%d = 0x%08X\n", page_num, phys_addr);

	/* Read CACHE_MMU_SMALL_POLICY_i */
	ret = mem_read((unsigned int)&p_base_addr[64+page_num], &policy_reg);
	if (ret != 0) {
		fprintf(stderr, "internal error (failed to read)!\n");
		return OMAPCONF_ERR_REG_ACCESS;
	}
	printf("CACHE_MMU_SMALL_POLICY_%d = 0x%08X\n", page_num, policy_reg);

	if( (policy_reg&1) == 0 ) {
		printf("\nPAGE NOT ENABLED\n");
	} else {
		printf("\nPAGE ENABLED\n");

		printf("Logical Address  = 0x%08X", logical_addr);
		if( (policy_reg & 1<<1) == 1<<1 ) {
			size = 16 * 1024; /* 16 KB */
		} else {
			size = 4 * 1024; /* 4 KB */
		}
		printf(" - 0x%08X\n", (logical_addr+size-1));

		if ( (phys_addr&1) == 1 ) { /* "ignore" bit */
			phys_addr = logical_addr;
		}
		printf("Physical address = 0x%08X - 0x%08X\n", phys_addr, phys_addr+size-1);

		printf("Policy\n");

		if( (policy_reg & 1<<19) == 1<<19 ) {
			printf(" * L1 write policy is writeback\n");
		} else {
			printf(" * L1 write policy is writethrough\n");
		}

		if( (policy_reg & 1<<18) == 1<<18 ) {
			printf(" * L1 allocate policy: follow sideband\n");
		} else {
			printf(" * L1 allocate policy: no writes allocated\n");
		}

		if( (policy_reg & 1<<17) == 1<<17 ) {
			printf(" * L1 writes posted\n");
		} else {
			printf(" * L1 writes non-posted\n");
		}

		if( (policy_reg & 1<<16) == 1<<16 ) {
			printf(" * L1 cacheable\n");
		} else {
			printf(" * L1 noncacheable\n");
		}

		if( (policy_reg & 1<<7) == 1<<7 ) {
			printf(" * Send cache exclusion sideband\n");
		} else {
			printf(" * Do not send cache exclusion sideband\n");
		}

		if( (policy_reg & 1<<6) == 1<<6 ) {
			printf(" * Preload enabled\n");
		} else {
			printf(" * Preload disabled\n");
		}

		if( (policy_reg & 1<<5) == 1<<5 ) {
			printf(" * Read-only\n");
		} else {
			printf(" * Read/Write\n");
		}

		if( (policy_reg & 1<<4) == 1<<4 ) {
			printf(" * Execute-only\n");
		} else {
			printf(" * Read/Write/Execute\n");
		}

		if( (policy_reg & 1<<3) == 1<<3 ) {
			printf(" * Follow volatile qualifier\n");
		} else {
			printf(" * Do not follow volatile qualifier\n");
		}

		if( (policy_reg & 1<<1) == 1<<1 ) {
			printf(" * 16 KB page\n");
		} else {
			printf(" * 4 KB page\n");
		}
	}

	printf("\n");

	return ret;
}
