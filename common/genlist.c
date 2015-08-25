/*
 *
 * @Component			OMAPCONF
 * @Filename			genlist.c
 * @Description			Generic List. Implement a single linked list
 *				with unlimited number of elements of any size
 *				(each element may be of different size).
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


#include <genlist.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* #define GENLIST_DEBUG */
#ifdef GENLIST_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		genlist_init
 * @BRIEF		initialize list internal variables
 * @RETURNS		0 in case of success
 *			GENLIST_ERR_ARG
 * @param[in,out]	list: genlist pointer
 * @DESCRIPTION		initialize list internal variables
 *			(must be called before any other function).
 *//*------------------------------------------------------------------------ */
int genlist_init(genlist *list)
{
	if (list == NULL) {
		printf("genlist_init(): list = NULL!\n");
		return GENLIST_ERR_ARG;
	}

	list->count = 0;
	list->head = NULL;
	list->tail = NULL;

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		genlist_getcount
 * @BRIEF		Return the number of elements in the list.
 * @RETURNS		>= 0 the number of elements in the list
 *			GENLIST_ERR_ARG
 * @param[in]		list: genlist pointer
 * @DESCRIPTION		Return the number of elements in the list.
 *//*------------------------------------------------------------------------ */
int genlist_getcount(genlist *list)
{
	if (list == NULL) {
		printf("genlist_getcount(): list = NULL!\n");
		return GENLIST_ERR_ARG;
	}

	return list->count;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		genlist_isempty
 * @BRIEF		used to check if list is empty or not
 * @RETURNS		0 list is not empty
 *			>0 list is empty
 *			GENLIST_ERR_ARG
 * @param[in]		list: genlist pointer
 * @DESCRIPTION		used to check if list is empty or not
 *//*------------------------------------------------------------------------ */
int genlist_isempty(genlist *list)
{
	if (list == NULL) {
		printf("genlist_isempty(): list = NULL!\n");
		return GENLIST_ERR_ARG;
	}

	return (list->head == NULL);
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		genlist_addhead
 * @BRIEF		Add element at the head position of the list
 * @RETURNS		>0 number of element in the list
 *			(after insertion of new element)
 *			GENLIST_ERR_ARG
 *			GENLIST_ERR_MALLOC
 * @param[in,out]	list: genlist pointer
 * @param[in,out]	data: element to add to the list
 * @param[in]		data_size: size of data parameter
 * @DESCRIPTION		Add element at the head position of the list
 *//*------------------------------------------------------------------------ */
int genlist_addhead(genlist *list, void *data, unsigned int data_size)
{
	genlist_elt *new_elt;

	if (list == NULL) {
		printf("genlist_addhead(): list = NULL!\n");
		return GENLIST_ERR_ARG;
	}
	if (data_size == 0) {
		printf("genlist_addhead(): data_size = 0!\n");
		return GENLIST_ERR_ARG;
	}

	/* Allocate memory for new element */
	dprintf("genlist_addhead(): alloc new list element of size %d\n",
		sizeof(genlist_elt));
	new_elt = (genlist_elt *) malloc(sizeof(genlist_elt));
	if (new_elt == NULL) {
		printf("genlist_addtail(): new elt malloc(%d) failed!\n",
			data_size);
		return GENLIST_ERR_MALLOC;
	}
	dprintf("genlist_addhead(): alloc new data buffer of size %d\n",
		data_size);
	new_elt->data = (void *) malloc(data_size);
	if (new_elt->data == NULL) {
		printf("genlist_addhead(): new data malloc(%d) failed!\n",
			data_size);
		return GENLIST_ERR_MALLOC;
	}

	/* Copy data into new element and save data size */
	memcpy(new_elt->data, data, data_size);
	new_elt->data_size = data_size;

	/* Init new element next pointer */
	new_elt->next = (list->head);

	/* Update list pointers and count */
	list->head = new_elt;
	list->count++;

	return list->count;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		genlist_addtail
 * @BRIEF		Add element at the tail position of the list
 * @RETURNS		>0 number of element in the list
 *			(after insertion of new element)
 *			GENLIST_ERR_ARG
 *			GENLIST_ERR_MALLOC
 * @param[in,out]	list: genlist pointer
 * @param[in,out]	data: element to add to the list
 * @param[in]		data_size: size of data parameter
 * @DESCRIPTION		Add element at the tail position of the list
 *//*------------------------------------------------------------------------ */
int genlist_addtail(genlist *list, void *data, unsigned int data_size)
{
	genlist_elt *new_elt;

	if (list == NULL) {
		printf("genlist_addtail(): list = NULL!\n");
		return GENLIST_ERR_ARG;
	}
	if (data_size == 0) {
		printf("genlist_addtail(): data_size = 0!\n");
		return GENLIST_ERR_ARG;
	}

	/* Allocate memory for new element */
	dprintf("genlist_addtail(): alloc new list element of size %d\n",
		sizeof(genlist_elt));
	new_elt = (genlist_elt *) malloc(sizeof(genlist_elt));
	if (new_elt == NULL) {
		printf("genlist_addtail(): new elt malloc(%d) failed!\n",
			data_size);
		return GENLIST_ERR_MALLOC;
	}
	dprintf("genlist_addtail(): alloc new data buffer of size %d\n",
		data_size);
	new_elt->data = (void *) malloc(data_size);
	if (new_elt->data == NULL) {
		printf("genlist_addtail(): new data malloc(%d) failed!\n",
			data_size);
		return GENLIST_ERR_MALLOC;
	}

	/* Copy data into new element and save data size */
	memcpy(new_elt->data, data, data_size);
	new_elt->data_size = data_size;

	/* Init new element next pointer */
	new_elt->next = NULL;

	/* Update list pointers and count */
	if (list->count == 0)
		list->head = new_elt;
	else
		(list->tail)->next = new_elt;
	list->tail = new_elt;
	list->count++;

	return list->count;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		genlist_add
 * @BRIEF		add element at given position in the list
 * @RETURNS		0 in case of success
 *			GENLIST_ERR_ARG
 *			GENLIST_ERR_MALLOC
 * @param[in,out]	list: genlist pointer
 * @param[in,out]	data: element to add to the list
 * @param[in]		data_size: size of data parameter
 * @param[in]		pos: position of element to be removed
 *				(0..genlist_getcount() - 1)
 * @DESCRIPTION		add element at given position in the list
 *//*------------------------------------------------------------------------ */
int genlist_add(genlist *list,
	void *data, unsigned int data_size, unsigned int pos)
{
	genlist_elt *new_elt, *elt;
	unsigned int i;

	if (list == NULL) {
		fprintf(stderr, "%s(): list = NULL!\n", __func__);
		return GENLIST_ERR_ARG;
	}
	if (data == NULL) {
		fprintf(stderr, "%s(): data = NULL!\n", __func__);
		return GENLIST_ERR_ARG;
	}
	if (data_size == 0) {
		printf("genlist_addtail(): data_size = 0!\n");
		return GENLIST_ERR_ARG;
	}
	if (pos >= list->count) {
		fprintf(stderr, "%s(): pos (%d) >= list->count (%d)!\n",
			__func__, pos, list->count);
		return GENLIST_ERR_ARG;
	}

	if (pos == 0)
		return genlist_addhead(list, data, data_size);
	else if (pos == (list->count - 1))
		return genlist_addtail(list, data, data_size);

	/* Allocate memory for new element */
	dprintf("%s(): alloc new list element of size %d\n", __func__,
		sizeof(genlist_elt));
	new_elt = (genlist_elt *) malloc(sizeof(genlist_elt));
	if (new_elt == NULL) {
		printf("%s(): new elt malloc(%d) failed!\n",
			__func__, data_size);
		return GENLIST_ERR_MALLOC;
	}
	dprintf("%s(): alloc new data buffer of size %d\n", __func__,
		data_size);
	new_elt->data = (void *) malloc(data_size);
	if (new_elt->data == NULL) {
		printf("%s(): new data malloc(%d) failed!\n", __func__,
			data_size);
		return GENLIST_ERR_MALLOC;
	}

	/* Copy data into new element and save data size */
	memcpy(new_elt->data, data, data_size);
	new_elt->data_size = data_size;

	/* Insert element in the list at given positon */
	elt = list->head;
	for (i = 0; i < pos - 1; i++)
		elt = elt->next;
	new_elt->next = elt->next;
	elt->next = new_elt;
	list->count++;

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		genlist_get
 * @BRIEF		return element at given position in the list
 * @RETURNS		0 in case of success
 *			GENLIST_ERR_ARG
 *			GENLIST_ERR_EMPTY
 * @param[in]		list: genlist pointer
 * @param[in]		pos: element position in the list
 * @param[in,out]	data: element to get
 * @DESCRIPTION		return element at given position in the list
 *//*------------------------------------------------------------------------ */
int genlist_get(genlist *list, unsigned int pos, void *data)
{
	genlist_elt *elt;
	unsigned int i;

	if (list == NULL) {
		printf("genlist_get(): list = NULL!\n");
		return GENLIST_ERR_ARG;
	}
	if (pos >= list->count) {
		printf("genlist_get(): pos (%d) >= list->count (%d)!\n",
			pos, list->count);
		return GENLIST_ERR_ARG;
	}
	if (data == NULL) {
		printf("genlist_get(): data = NULL!\n");
		return GENLIST_ERR_ARG;
	}
	if (list->count == 0)
		return GENLIST_ERR_EMPTY;

	if (pos == 0) {
		memcpy(data, (list->head)->data, (list->head)->data_size);
	} else if (pos == list->count - 1) {
		memcpy(data, (list->tail)->data, (list->tail)->data_size);
	} else {
		elt = list->head;
		for (i = 0; i < pos; i++)
			elt = elt->next;
		memcpy(data, elt->data, elt->data_size);
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		genlist_gethead
 * @BRIEF		return element at head position in the list
 * @RETURNS		0 in case of success
 *			GENLIST_ERR_ARG
 *			GENLIST_ERR_EMPTY
 * @param[in]		list: genlist pointer
 * @param[in,out]	data: element to get
 * @DESCRIPTION		return element at head position in the list
 *//*------------------------------------------------------------------------ */
int genlist_gethead(genlist *list, void *data)
{
	if (list == NULL) {
		printf("genlist_gethead(): list = NULL!\n");
		return GENLIST_ERR_ARG;
	}
	if (data == NULL) {
		printf("genlist_gethead(): data = NULL!\n");
		return GENLIST_ERR_ARG;
	}
	if (list->count == 0)
		return GENLIST_ERR_EMPTY;

	memcpy(data, (list->head)->data, (list->head)->data_size);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		genlist_gettail
 * @BRIEF		return element at tail position in the list
 * @RETURNS		0 in case of success
 *			GENLIST_ERR_ARG
 *			GENLIST_ERR_EMPTY
 * @param[in]		list: genlist pointer
 * @param[in,out]	data: element to get
 * @DESCRIPTION		return element at tail position in the list
 *//*------------------------------------------------------------------------ */
int genlist_gettail(genlist *list, void *data)
{
	if (list == NULL) {
		printf("genlist_get(): list = NULL!\n");
		return GENLIST_ERR_ARG;
	}
	if (data == NULL) {
		printf("genlist_get(): data = NULL!\n");
		return GENLIST_ERR_ARG;
	}
	if (list->count == 0)
		return GENLIST_ERR_EMPTY;

	memcpy(data, (list->tail)->data, (list->tail)->data_size);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		genlist_removehead
 * @BRIEF		remove element at head position in the list
 * @RETURNS		0 in case of success
 *			GENLIST_ERR_ARG
 *			GENLIST_ERR_EMPTY
 *			GENLIST_ERR_INTERNAL
 * @param[in,out]	list: genlist pointer
 * @DESCRIPTION		remove element at head position in the list
 *//*------------------------------------------------------------------------ */
int genlist_removehead(genlist *list)
{
	genlist_elt *elt;

	/* Check args */
	if (list == NULL) {
		fprintf(stderr, "%s(): list = NULL!\n", __func__);
		return GENLIST_ERR_ARG;
	}
	if (list->count == 0) {
		dprintf("%s(): list is empty!\n", __func__);
		return GENLIST_ERR_EMPTY;
	}

	/* Remove element from list and update head */
	elt = list->head;
	if (list->count == 1) {
		list->head = NULL;
		list->tail = NULL;
	} else {
		list->head = elt->next;
	}
	list->count--;

	/* Free element allocated memory */
	if (elt->data == NULL) {
		fprintf(stderr, "%s(): data = NULL!\n", __func__);
		return GENLIST_ERR_INTERNAL;
	}
	dprintf("%s(): free data of element at head\n", __func__);
	free(elt->data);
	dprintf("%s(): free element at head\n", __func__);
	free(elt);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		genlist_removetail
 * @BRIEF		remove element at tail position in the list
 * @RETURNS		0 in case of success
 *			GENLIST_ERR_ARG
 *			GENLIST_ERR_EMPTY
 *			GENLIST_ERR_INTERNAL
 * @param[in,out]	list: genlist pointer
 * @DESCRIPTION		remove element at tail position in the list
 *//*------------------------------------------------------------------------ */
int genlist_removetail(genlist *list)
{
	genlist_elt *elt = NULL, *elt2 = NULL;
	unsigned int i;

	/* Check args */
	if (list == NULL) {
		fprintf(stderr, "%s(): list = NULL!\n", __func__);
		return GENLIST_ERR_ARG;
	}
	if (list->count == 0) {
		dprintf("%s(): list is empty!\n", __func__);
		return GENLIST_ERR_EMPTY;
	}

	/* Remove element from list and update tail */
	elt = list->head;
	if (list->count == 1) {
		list->head = NULL;
		list->tail = NULL;
	} else {
		for (i = 0; i < list->count - 2; i++)
			elt = elt->next;
		elt2 = list->tail;
		list->tail = elt;
		elt->next = NULL;
	}
	list->count--;

	/* Free element allocated memory */
	if (elt2->data == NULL) {
		fprintf(stderr, "%s(): data = NULL!\n", __func__);
		return GENLIST_ERR_INTERNAL;
	}
	dprintf("%s(): free data of element at head\n", __func__);
	free(elt2->data);
	dprintf("%s(): free element at head\n", __func__);
	free(elt2);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		genlist_remove
 * @BRIEF		remove element at given position in the list
 * @RETURNS		0 in case of success
 *			GENLIST_ERR_ARG
 *			GENLIST_ERR_EMPTY
 *			GENLIST_ERR_INTERNAL
 * @param[in,out]	list: genlist pointer
 * @param[in]		pos: position of element to be removed
 *				(0..genlist_getcount() - 1)
 * @DESCRIPTION		remove element at given position in the list
 *//*------------------------------------------------------------------------ */
int genlist_remove(genlist *list, unsigned int pos)
{
	genlist_elt *elt, *elt2 = NULL;
	unsigned int i;

	/* Check args */
	if (list == NULL) {
		fprintf(stderr, "%s(): list = NULL!\n", __func__);
		return GENLIST_ERR_ARG;
	}
	if (pos >= list->count) {
		fprintf(stderr, "genlist_get(): pos (%d)>=list->count (%d)!\n",
			pos, list->count);
		return GENLIST_ERR_ARG;
	}
	if (list->count == 0) {
		dprintf("%s(): list is empty!\n", __func__);
		return GENLIST_ERR_EMPTY;
	}

	if (pos == 0)
		return genlist_removehead(list);
	else if (pos == (list->count - 1))
		return genlist_removetail(list);

	elt = list->head;
	if (list->count == 1) {
		list->head = NULL;
		list->tail = NULL;
	} else {
		for (i = 0; i < pos - 1; i++)
			elt = elt->next;
		elt2 = elt->next;
		elt->next = elt2->next;
	}
	list->count--;

	/* Free element allocated memory */
	if (elt2->data == NULL) {
		fprintf(stderr, "%s(): data = NULL!\n", __func__);
		return GENLIST_ERR_INTERNAL;
	}
	dprintf("%s(): free data of element at head\n", __func__);
	free(elt2->data);
	dprintf("%s(): free element at head\n", __func__);
	free(elt2);

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		genlist_free
 * @BRIEF		Free all memory buffers allocated for this list
 * @RETURNS		0 in case of success
 *			GENLIST_ERR_ARG
 *			GENLIST_ERR_INTERNAL
 * @param[in,out]	list: genlist pointer
 * @DESCRIPTION		Free all memory buffers allocated for this list
 *//*------------------------------------------------------------------------ */
int genlist_free(genlist *list)
{
	unsigned int i;
	genlist_elt *elt;
	genlist_elt *elt2;

	if (list == NULL) {
		printf("genlist_free(): list = NULL!\n");
		return GENLIST_ERR_ARG;
	}
	if (list->count == 0) {
		dprintf("genlist_free(): list->count == 0, nothing to do.\n");
		return 0;
	}

	elt = list->head;
	for (i = 0; i < list->count; i++) {
		if (elt->data == NULL) {
			printf("genlist_free(): data = NULL! (pos=%d)\n", i);
			return GENLIST_ERR_INTERNAL;
		}
		elt2 = elt;
		elt = elt->next;
		dprintf("genlist_free(): free data of element at pos %d\n", i);
		free(elt2->data);
		dprintf("genlist_free(): free element at pos %d\n", i);
		free(elt2);
	}

	list->count = 0;
	list->head = NULL;
	list->tail = NULL;

	return 0;
}
