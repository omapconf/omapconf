/*
 *
 * @Component			OMAPCONF
 * @Filename			genlist.h
 * @Description			Generic List Definition File
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


#ifndef __GENLIST_H__
#define __GENLIST_H__


#define GENLIST_ERR_ARG			-1 /* incorrect argument(s) */
#define GENLIST_ERR_MALLOC		-2 /* memory could not be allocated */
#define GENLIST_ERR_INTERNAL		-3 /* internal error */
#define GENLIST_ERR_EMPTY		-4 /* list is empty */


typedef struct {
	void *data;
	unsigned int data_size;
	void *next;
} genlist_elt;


typedef struct {
	genlist_elt *head;
	genlist_elt *tail;
	unsigned int count;
} genlist;


int genlist_init(genlist *list);
int genlist_free(genlist *list);
int genlist_getcount(genlist *list);
int genlist_isempty(genlist *list);
int genlist_addhead(genlist *list, void *data, unsigned int data_size);
int genlist_addtail(genlist *list, void *data, unsigned int data_size);
int genlist_add(genlist *list,
	void *data, unsigned int data_size, unsigned int pos);
int genlist_get(genlist *list, unsigned int pos, void *data);
int genlist_gethead(genlist *list, void *data);
int genlist_gettail(genlist *list, void *data);
int genlist_removehead(genlist *list);
int genlist_removetail(genlist *list);
int genlist_remove(genlist *list, unsigned int pos);


#endif
