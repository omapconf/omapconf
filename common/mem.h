/*
 *
 * @Component			OMAPCONF
 * @Filename			mem.h
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


#ifndef __MEM_H__
#define __MEM_H__


#define MEM_ERR_ARG			-1 /* incorrect argument(s) */
#define MEM_ERR_ACCESS			-4 /* Memory R/W access failed */
#define MEM_ERR_MAP			-5 /* memory could not be mapped */


void mem_read_trace_enable(unsigned short enable);
void mem_write_trace_enable(unsigned short enable);

int mem_map(unsigned int addr);
void mem_unmap(void);
void *mem_phys2virt(void *addr);

void *mem_map_address(unsigned int addr);
void mem_unmap_address(void *vaddr);

void mem_fake_access_set(unsigned short enable);
unsigned short mem_fake_access_get(void);

unsigned int mem_last_addr_get(void);

int mem_read(unsigned int reg_addr, unsigned int *reg_val);
int mem_address_range_read(unsigned int reg_addr, unsigned int *mem_ptr,
	unsigned int size);
int mem_write(unsigned int reg_addr, unsigned int reg_val);


#endif
