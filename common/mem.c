/*
 *
 * @Component			OMAPCONF
 * @Filename			mem.c
 * @Description			OMAP Generic Memory Access Library
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


#include <mem.h>
#include <linux_mem.h>
#include <stdio.h>


static unsigned int last_mem_addr;
static unsigned short fake_mem_access = 0;
static unsigned short mem_read_trace = 0;
static unsigned short mem_write_trace = 0;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mem_read_trace_enable
 * @BRIEF		enable tracing of all memory read access.
 * @param[in]		enable: 0 to disable trace (default), 1 to enable it.
 * @DESCRIPTION		enable tracing of all memory read access.
 *			Print trace with physical address and read value.
 *//*------------------------------------------------------------------------ */
void mem_read_trace_enable(unsigned short enable)
{
	mem_read_trace = enable;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mem_write_trace_enable
 * @BRIEF		enable tracing of all memory write access.
 * @param[in]		enable: 0 to disable trace (default), 1 to enable it.
 * @DESCRIPTION		enable tracing of all memory read access.
 *			Print trace with physical address and written value.
 *//*------------------------------------------------------------------------ */
void mem_write_trace_enable(unsigned short enable)
{
	mem_write_trace = enable;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mem_map
 * @BRIEF		map memory by chunk of 1MB.
 *			Keep it mapped until new address to be mapped is out
 *			of the current chunk.
 * @RETURNS		0 on success
 *			MEM_ERR_MAP
 * @param[in]		addr: 32-bit memory physical address
 * @DESCRIPTION		map memory by chunk of 1MB.
 *			Keep it mapped until new address to be mapped is out
 *			of the current chunk.
 *//*------------------------------------------------------------------------ */
int mem_map(unsigned int addr)
{
	int ret;

	ret = lmem_map(addr);
	if (ret != 0)
		ret = MEM_ERR_MAP;
	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mem_unmap
 * @BRIEF		unmap last 1MB memory chunk.
 *			*** To be called at end of application execution. ***
 * @DESCRIPTION		unmap last 1MB memory chunk.
 *			*** To be called at end of application execution. ***
 *//*------------------------------------------------------------------------ */
void mem_unmap(void)
{
	lmem_unmap();
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mem_map_address
 * @BRIEF		map memory for 1 precise address, 4K mapping.
 *			*** User has to explicitly unmap it. ***
 * @RETURNS		virtual address
 *			NULL if memory could not be mapped
 * @param[in]		addr: 32-bit memory physical address
 * @DESCRIPTION		map memory for 1 precise address, 4K mapping.
 *			*** User has to explicitly unmap it. ***
 *//*------------------------------------------------------------------------ */
void *mem_map_address(unsigned int addr)
{
	return lmem_map_address(addr);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mem_unmap_address
 * @BRIEF		unmap specific virtual address.
 *			*** To be called at end of application execution. ***
 * @DESCRIPTION		unmap specific virtual address.
 *			*** To be called at end of application execution. ***
 *//*------------------------------------------------------------------------ */
void mem_unmap_address(void *vaddr)
{
	lmem_unmap_address(vaddr);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mem_phys2virt
 * @BRIEF		convert memory physical address to virtual address.
 * @RETURNS		memory virtual address
 * @param[in]		addr: memory physical address
 * @DESCRIPTION		convert memory physical address to virtual address.
 *//*------------------------------------------------------------------------ */
void *mem_phys2virt(void *addr)
{
	return lmem_phys2virt(addr);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mem_read
 * @BRIEF		read memory value at given physical address.
 * @RETURNS		0 on success
 *			MEM_ERR_ARG
 *			MEM_ERR_ACCESS
 * @param[in]		addr: 32-bit memory physical address
 * @param[in, out]	val: pointer where to store read value
 * @DESCRIPTION		read memory value at given physical address.
 *			*val == 0xBEEFDEAD in case of error.
 *//*------------------------------------------------------------------------ */
int mem_read(unsigned int addr, unsigned int *val)
{
	int ret;

	if ((void *) val == NULL) {
		fprintf(stderr, "%s(): val == NULL!!!\n", __func__);
		return MEM_ERR_ARG;
	}

	if (addr == 0) {
		fprintf(stderr, "%s(): trying to read address 0!!!\n",
			__func__);
		return MEM_ERR_ARG;
	}

	if (mem_read_trace) {
		printf("omapconf: reading address 0x%08X ...", addr);
		fflush(stdin);
	}

	if (mem_fake_access_get()) {
		*val = (unsigned int) addr;
		ret = 0;
	} else {
		ret = lmem_read(addr, val);
		if (ret != 0)
			ret = MEM_ERR_ACCESS;
	}

	if (mem_read_trace) {
		printf("done => 0x%08X\n", *val);
		fflush(stdin);
	}

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mem_write
 * @BRIEF		write memory value at given physical address.
 * @RETURNS		0 on success
 *			MEM_ERR_ARG
 *			MEM_ERR_ACCESS
 * @param[in]		addr: 32-bit memory physical address
 * @param[in]		val: value to be written in memory
 * @DESCRIPTION		write value at given memory physical address.
 *//*------------------------------------------------------------------------ */
int mem_write(unsigned int addr, unsigned int val)
{
	int ret;

	if (addr == 0) {
		fprintf(stderr, "%s(): trying to write at address 0!!!\n",
			__func__);
		return MEM_ERR_ARG;
	}

	if (mem_write_trace) {
		printf("omapconf: writing 0x%08X at address 0x%08X...",
			val, addr);
		fflush(stdin);
	}

	if (!mem_fake_access_get()) {
		ret = lmem_write(addr, val);
		if (ret != 0)
			ret = MEM_ERR_ACCESS;
	} else {
		ret = 0;
	}

	if (mem_write_trace) {
		printf("OK\n");
		fflush(stdin);
	}

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mem_address_range_read
 * @BRIEF		Fill 'mem_ptr' array of size 'size' with
 *			consecutive memory content read starting at address
 *			'addr'.
 * @RETURNS		0 on success
 *			MEM_ERR_ARG
 *			MEM_ERR_ACCESS
 * @param[in]		addr: 32-bit memory address
 * @param[in, out]	mem_ptr: pointer where to store read value
 * @param[in]		size: number of 32-bit words to read
 * @DESCRIPTION		Fill 'mem_ptr' array of size 'size' with
 *			consecutive memory content read starting at address
 *			'addr'.
 *//*------------------------------------------------------------------------ */
int mem_address_range_read(unsigned int addr, unsigned int *mem_ptr,
	unsigned int size)
{
	unsigned int i;
	int ret = 0;

	if ((void *) mem_ptr == NULL) {
		fprintf(stderr, "%s(): mem_ptr == NULL!!!\n", __func__);
		return MEM_ERR_ARG;
	}

	if ((addr == 0) || (size == 0))
		return MEM_ERR_ARG;

	for (i = 0; i < size; i++) {
		ret = mem_read((addr + (i * 4)), &mem_ptr[i]);
		if (ret)
			return MEM_ERR_ACCESS;
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mem_last_addr_get
 * @BRIEF		return last physical memory address accessed
 *			(useful in case of access failure).
 * @RETURNS		last physical memory address accessed.
 * @DESCRIPTION		return last physical memory address accessed
 *			(useful in case of access failure).
 *//*------------------------------------------------------------------------ */
unsigned int mem_last_addr_get(void)
{
	return last_mem_addr;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mem_fake_access_set
 * @BRIEF		enable/disable "fake" memory access.
 *			When disabled (== 0), true memory R/W access is
 *			performed.
 *			When enabled (!= 0), no memory R/W access is performed.
 * @param[in]		enable: enable/disable "fake" memory access.
 *			== 0: true memory R/W access is performed.
 *			!= 0: no memory R/W access is performed.
 * @DESCRIPTION		enable/disable "fake" memory access.
 *			When disabled (== 0), true memory R/W access is
 *			performed.
 *			When enabled (!= 0), no memory R/W access is performed:
 *			READ access will return physical address read,
 *			WRITE access will be skipped.
 *			### Use for debug purpose only, or to allow running on
 *			a different platform than the target one. ###
 *			e.g. allow code to be develop on x86 (host PC) instead
 *			of on target, saving time.
 *//*------------------------------------------------------------------------ */
void mem_fake_access_set(unsigned short enable)
{
	fake_mem_access = enable;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mem_fake_access_get
 * @BRIEF		return the "fake" memory access status
 *			(enabled/disabled).
 * @RETURNS		0: true memory R/W access is performed.
 *			!= 0: no memory R/W access is performed.
 * @DESCRIPTION		return the "fake" memory access status
 *			(enabled/disabled).
 *//*------------------------------------------------------------------------ */
unsigned short mem_fake_access_get(void)
{
	return fake_mem_access;
}
