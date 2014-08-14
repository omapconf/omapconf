/*
 *
 * @Component			OMAPCONF
 * @Filename			lib_am335x.c
 * @Description			OMAPCONF AM335X General Purpose Library
 * @Author			Gilberto Rodriguez <gilrod@ti.com>
 * @Date			2014
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
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


#include <cm_am335x.h>
#include <cpuinfo.h>
#include <lib.h>
#include <lib_am335x.h>
#include <mem.h>
#include <prm_am335x.h>
#include <stdlib.h>
#include <string.h>


#ifdef LIB_AM335X_DEBUG
#define dprintf(format, ...)    printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		reg_am335x_addr_find
 * @BRIEF		find reg. addr corresponding to reg. name given as
 *			argument
 * @RETURNS		0 on success
 *			-1 if reg. addr. not found
 * @param[in]		name: reg. name.
 * @param[in,out]	addr: reg. addr corresponding to reg. name
 * @DESCRIPTION		find reg. addr corresponding to reg. name given as
 *			argument
 *//*------------------------------------------------------------------------ */
int reg_am335x_addr_find(char *name, unsigned int* addr)
{
	dprintf("%s(): looking for addr of register %s...\n", __func__, name);

	if (prm_am335x_name2addr(name, addr) == 0)
		goto reg_addr_found;
	else if (cm_am335x_name2addr(name, addr) == 0)
		goto reg_addr_found;

	dprintf("%s(): register addr not found!\n", __func__);
	return -1;

reg_addr_found:
	dprintf("%s(): register addr found: 0x%x\n", __func__, *addr);
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		am335x_name2addr
 * @BRIEF		convert register name to address
 * @RETURNS		0 on success
 *			-1 if address not found
 * @param[in]		name: register name
 * @param[in,out]	addr: register address
 * @param[in]		mods: array with AM335X modules to corresponding registers
 * @param[in]		mods_regcount: array with number of elements of each module
 * @DESCRIPTION		convert register name to address
 *//*------------------------------------------------------------------------ */
int am335x_name2addr(char *name, unsigned int *addr, reg ****mods)
{
	int i, j;
	reg ***test = *mods;

#ifdef LIB_AM335X_NAME2ADDR_DEBUG
	printf("%s(): name = %s\n", __func__, name);
#endif

	for (i = 0; test[i] != NULL; i += 1) {
		for (j = 0; test[i][j] != NULL; j += 1) {
			if (strcmp(name, test[i][j]->name) == 0) {
				/* register name found */
				*addr = test[i][j]->addr;
#ifdef LIB_AM335X_NAME2ADDR_DEBUG
				printf("%s(): Address(%s) = 0x%x\n",
					__func__,
					name, (*addr));
#endif
				return 0;
			}
		}
	}

	/* Register name not found */
#ifdef LIB_AM335X_NAME2ADDR_DEBUG
	printf("%s(): register name not found! (%s)\n", __func__, name);
#endif

	return -1;
}
