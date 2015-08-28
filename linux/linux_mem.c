/*
 *
 * @Component			OMAPCONF
 * @Filename			linux_mem.c
 * @Description			Linux Memory Mapping Library
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


#include <linux_mem.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


#define MEM_SIZE (1024 * 1024)
#define MEM_MASK (MEM_SIZE - 1)
#define MEM_SIZE_4K (4 * 1024)
#define MEM_MASK_4K (MEM_SIZE_4K - 1)
#define MEMORY "/dev/mem"


/* #define LMEM_READ_DEBUG */
/* #define LMEM_WRITE_DEBUG */
/* #define LMEM_DEBUG */
#ifdef LMEM_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


static void *mem_map_base = NULL;
static void *mem_offset = NULL;
static int mem_fd;


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		lmem_map
 * @BRIEF		map memory by chunk of 1MB.
 *			Keep it mapped until new address to be mapped is out
 *			of the current chunk.
 * @RETURNS		0 on success
 *			-5 if memory could not be mapped
 * @param[in]		addr: 32-bit memory physical address
 * @DESCRIPTION		map memory by chunk of 1MB.
 *			Keep it mapped until new address to be mapped is out
 *			of the current chunk.
 *//*------------------------------------------------------------------------ */
int lmem_map(unsigned int addr)
{
	if ((mem_offset != NULL) &&
		(addr >= (unsigned int) mem_offset) &&
		(addr < (unsigned int) mem_offset + MEM_SIZE)) {
		/* In same memory chunk already mapped, no need to remap it */
		dprintf("%s(0x%08X): in same mem map\n", __func__, addr);
		return 0;
	}

	/* Unmap previous memory chunk */
	lmem_unmap();

	/* Open device */
	mem_fd = open(MEMORY, O_RDWR|O_SYNC);
	if (mem_fd < 0) {
		fprintf(stderr, "%s(): could not open \"%s\"!\n",
			__func__, MEMORY);
		return -5;
	}

	/* Map memory */
	mem_offset =  (void *) (addr & ~MEM_MASK);
	mem_map_base = mmap(0, MEM_SIZE,
		PROT_READ|PROT_WRITE, MAP_SHARED,
		mem_fd, (off_t) mem_offset);
	if (mem_map_base == (void *) -1) {
		fprintf(stderr, "%s(): could not map memory!\n", __func__);
		close(mem_fd);
		mem_offset = NULL;
		mem_map_base = NULL;
		return -5;
	}
	dprintf("%s(0x%08X): new mem chuck 0x%08X mapped\n",
		__func__, addr, (unsigned int) mem_offset);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		lmem_unmap
 * @BRIEF		unmap last 1MB memory chunk.
 *			*** To be called at end of application execution. ***
 * @DESCRIPTION		unmap last 1MB memory chunk.
 *			*** To be called at end of application execution. ***
 *//*------------------------------------------------------------------------ */
void lmem_unmap(void)
{
	int ret;

	if (mem_map_base != NULL) {
		ret = munmap(mem_map_base, MEM_SIZE);
		if (ret != 0)
			fprintf(stderr, "%s(): unmap failed! (%d)\n",
				__func__, ret);
		close(mem_fd);

		dprintf("%s(): mem chunk 0x%08X unmapped\n",
			__func__, (unsigned int) mem_offset);
		mem_offset = NULL;
		mem_map_base = NULL;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		lmem_map_address
 * @BRIEF		map memory for 1 precise address, 4K mapping.
 *			*** User has to explicitly unmap it. ***
 * @RETURNS		virtual address
 *			NULL if memory could not be mapped
 * @param[in]		addr: 32-bit memory physical address
 * @DESCRIPTION		map memory for 1 precise address, 4K mapping.
 *			*** User has to explicitly unmap it. ***
 *//*------------------------------------------------------------------------ */
void *lmem_map_address(unsigned int addr)
{
	int mem_fd_address;
	void *mem_map_base_address = NULL;

	/* Open device */
	mem_fd_address = open(MEMORY, O_RDWR|O_SYNC);
	if (mem_fd_address < 0) {
		fprintf(stderr, "%s(): could not open \"%s\"!\n", __func__,
			MEMORY);
		return NULL;
	}

	/* Map memory */
	mem_map_base_address = mmap(0, MEM_SIZE_4K, PROT_READ|PROT_WRITE,
		MAP_SHARED, mem_fd_address, (off_t) (addr & ~MEM_MASK_4K));

	close(mem_fd_address);

	if (mem_map_base_address == (void *) -1) {
		fprintf(stderr, "%s(): could not map memory!\n", __func__);
		return NULL;
	}
	dprintf("%s(0x%08X): 0x%08X mapped\n", __func__, addr,
		(unsigned int)(addr & ~MEM_MASK_4K));

	return (void *) ((unsigned int) mem_map_base_address +
		(addr & MEM_MASK_4K));
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		lmem_unmap_address
 * @BRIEF		unmap specific virtual address.
 *			*** To be called at end of application execution. ***
 * @DESCRIPTION		unmap specific virtual address.
 *			*** To be called at end of application execution. ***
 *//*------------------------------------------------------------------------ */
void lmem_unmap_address(void *vaddr)
{
	int ret;
	int mem_fd_address;

	/* Open device */
	mem_fd_address = open(MEMORY, O_RDWR|O_SYNC);
	if (mem_fd_address < 0) {
		fprintf(stderr, "%s(): could not open \"%s\"!\n", __func__,
			MEMORY);
		return;
	}

	ret = munmap((void *)((unsigned int)vaddr & ~MEM_MASK_4K), MEM_SIZE_4K);

	close(mem_fd_address);

	if (ret != 0) {
		fprintf(stderr, "%s(): unmap failed! (%d)\n", __func__, ret);
		return;
	}

	dprintf("%s(): mem chunk 0x%08X unmapped\n", __func__, vaddr);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		mem_phys2virt
 * @BRIEF		convert memory physical address to virtual address.
 * @RETURNS		memory virtual address
 * @param[in]		addr: memory physical address
 * @DESCRIPTION		convert memory physical address to virtual address.
 *//*------------------------------------------------------------------------ */
void *lmem_phys2virt(void *addr)
{
	dprintf("%s(0x%08X)=0x%08X\n", __func__,
		(unsigned int) addr,
		(unsigned int) mem_map_base +
		((unsigned int) addr & MEM_MASK));
	return (void *) ((unsigned int) mem_map_base +
		((unsigned int) addr & MEM_MASK));
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		lmem_read
 * @BRIEF		read memory value at given address
 * @RETURNS		0 on success
 *			-1 in case of incorrect argument
 *			-5 if memory could not be mapped
 *			(with val == 0xBEEFDEAD)
 * @param[in]		addr: 32-bit memory address
 * @param[in, out]	val: pointer where to store read value
 * @DESCRIPTION		read memory value at given address
 *//*------------------------------------------------------------------------ */
int lmem_read(unsigned int addr, unsigned int *val)
{
	int ret;
	void *vaddr;

	if ((void *) val == NULL) {
		fprintf(stderr, "%s(): val == NULL!!!\n", __func__);
		return -1;
	}

	*val = 0xBEEFDEAD;

	if (addr == 0) {
		fprintf(stderr, "%s(): trying to read address 0!!!\n",
			__func__);
		return -1;
	}

	#ifdef LMEM_READ_DEBUG
	printf("%s(): addr=0x%08X\n", __func__, addr);
	#endif

	/* map memory */
	ret = lmem_map(addr);
	if (ret != 0)
		return ret;

	/* translate address */
	vaddr = lmem_phys2virt((void *) addr);

	/* Read memory */
	*val = *((unsigned int *) vaddr);

	#ifdef LMEM_READ_DEBUG
	printf("%s(): *val=0x%08X\n", __func__, *val);
	#endif

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		lmem_write
 * @BRIEF		write memory value at given physical address
 * @RETURNS		0 on success
 *			-1 in case of incorrect argument
 *			-5 if memory could not be mapped
 * @param[in]		addr: 32-bit memory address
 * @param[in]		val: value to be written int memory
 * @DESCRIPTION		write value at given physical address
 *//*------------------------------------------------------------------------ */
int lmem_write(unsigned int addr, unsigned int val)
{
	int ret;
	void *vaddr;

	if (addr == 0) {
		fprintf(stderr, "%s(): trying to write at address 0!!!\n",
			__func__);
		return -1;
	}

	#ifdef LMEM_WRITE_DEBUG
	printf("%s(): addr=0x%08X\n", __func__, addr);
	#endif

	/* map memory */
	ret = lmem_map(addr);
	if (ret != 0)
		return ret;

	/* translate address */
	vaddr = lmem_phys2virt((void *) addr);

	/* Write memory */
	#ifdef LMEM_WRITE_DEBUG
	printf("%s(): Physical address to be written: 0x%08X\n",
		__func__, addr);
	printf("%s(): Virtual address to be written: 0x%08X\n",
		__func__, (unsigned int) vaddr);
	printf("%s(): Value to be written: 0x%08X\n",
		__func__, (unsigned int) val);
	#else
	*((unsigned int *) vaddr) = val;
	#endif

	return 0;
}
