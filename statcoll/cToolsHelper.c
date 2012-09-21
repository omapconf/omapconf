/*
 * cToolsHelper.c
 *
 * cTools Helper public functions.
 *
 * Copyright (C) 2009,2010 Texas Instruments Incorporated - http://www.ti.com/
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

//Note this file to be updated for the specific implementation

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#ifdef __linux__
    #include <fcntl.h>
    #include <sys/mman.h>

    // Mapping paramters
    typedef struct _MapObject {
        void * vAddr;            // Virtural Address
        unsigned int mapSize;    // Map size in Bytes
        struct _MapObject * pPrevMapObj;
        struct _MapObject * pNextMapObj;
    }MapObject;

    MapObject * pMapObjLL = 0; // Map Object Link List Pointer

    static int fd = 0;
    static const unsigned int pageSize = 4096;
    static const unsigned int pageMask = 4096-1;
#endif

// Memory allocation
void * cTools_memAlloc(size_t sizeInBytes)
{
    return((void *)malloc (sizeInBytes));
}

// Memory free
void cTools_memFree(void *p)
{
    free(p);
}

//Returns virtual address to region requested
void * cTools_memMap(unsigned int phyAddr, unsigned int mapSizeInBytes)
{
#ifdef __linux__

    void * pVirtualAddress = NULL;
    unsigned int mapSize = 0;
    MapObject *pMapObj;

    // Only open the /dev/mem device once
    if(0 == fd)
    {
        if((fd = open("/dev/mem", O_RDWR | O_SYNC | O_RSYNC)) == -1)
        {
  #ifdef _DEBUG
            printf("cTools_memMap:: Device '/dev/mem' could not be opened with O_RDWR | O_SYNC attributes.\n");
  #endif
            return NULL;
        }
    }

    // Allocate space for the map object
    if ( ( pMapObj = (MapObject *)cTools_memAlloc(sizeof(MapObject))) == NULL )
    {
        printf("cTools_memMap:: Unable to create map object, malloc failed\n");
        return NULL;
    }

    //Note: phyAddr may need to be aligned to a PAGE_SIZE and mapSizeInBytes may need to be
    //      a multiple of PAGE_SIZE. Since the STM physical size is either 256KB or 1MB
    //      this should not be an issue. It is assumed that the Virtual Address returned will
    //      map to the first location of physical STM space.

    // Adjust mapSizeInBytes to a whole number of pages
    if ((mapSizeInBytes % pageSize) != 0 )
    {
        mapSize = ((mapSizeInBytes/pageSize) + 1 ) * pageSize;
    }
    else
    {
        mapSize = mapSizeInBytes;
    }

    pVirtualAddress = mmap(0, mapSize,  (PROT_READ|PROT_WRITE), MAP_SHARED, fd, phyAddr & ~pageMask);

    if (pVirtualAddress == (void *) -1)
    {
        cTools_memFree(pMapObj);
  #ifdef _DEBUG
        printf("cTools_memMap:: Unable to map physical address 0x%X for %d bytes\n", phyAddr, mapSizeInBytes);
  #endif
        return NULL;
    }

    // Add map object to end of link list
    pMapObj->vAddr = pVirtualAddress;
    pMapObj->mapSize = mapSize;
    pMapObj->pNextMapObj = NULL;
    if ( NULL == pMapObjLL )
    {
        pMapObjLL = pMapObj;
        pMapObj->pPrevMapObj = NULL;
    }
    else
    {
        //search the link list for the current last element
        MapObject *pThisMapObj = pMapObjLL;
        while ( NULL != pThisMapObj->pNextMapObj) {
             pThisMapObj = pThisMapObj->pNextMapObj;
        }

        pThisMapObj->pNextMapObj = pMapObj;
        pMapObj->pPrevMapObj = pThisMapObj;
    }

    // Virtual addres must be adjusted with LS 12 bits of the phyAddr
    pVirtualAddress += phyAddr & pageMask;

    return pVirtualAddress;

#else  // __linux__  not defined

  #ifdef _DEBUG
        printf("cTools_memMap:: Mapping physical address 0x%X for %d bytes\n", phyAddr, mapSizeInBytes);
  #endif
    return (void *)phyAddr;

#endif
}

//Unmap virtual address space of region requested
void cTools_memUnMap(void * vAddr, unsigned int mapSizeInBytes)
{
#ifdef __linux__
    if( munmap(vAddr,  mapSizeInBytes) ==  -1 )
    {
  #ifdef _DEBUG
        printf("cTools_memUnMap:: Unable to unmap address 0x%X for %d bytes\n", (unsigned)vAddr, mapSizeInBytes);
  #endif
        return;
    }

    //Mask address and look it up
    MapObject * pThisMapObj = pMapObjLL;

    while (( (unsigned int)vAddr & ~pageMask ) != (unsigned int)pThisMapObj->vAddr )
    {
        pThisMapObj = pThisMapObj->pNextMapObj;
        if (  NULL == pThisMapObj )
        {
  #ifdef _DEBUG
           printf("cTools_memUnMap:: Failed to find vitural address 0x%X in lookup table\n", (unsigned)vAddr & ~pageMask);
  #endif
           return;
        }
    }

    if( munmap(pThisMapObj->vAddr,  pThisMapObj->mapSize) ==  -1 )
    {
  #ifdef _DEBUG
        printf("cTools_memUnMap:: Unmap failed for address 0x%X for %d bytes\n", (unsigned)pThisMapObj->vAddr, pThisMapObj->mapSize);
  #endif
        return;
    }

    //Fix map object link
    // If this is the only object in the list
    if ( ( NULL == pThisMapObj->pNextMapObj ) &&  ( NULL == pThisMapObj->pPrevMapObj ) )
    {
        pMapObjLL = NULL;
        close(fd); // close memory device handle
        fd = 0;
    }

    // If first in list need to update list pointer to next element
    if ( ( NULL != pThisMapObj->pNextMapObj ) &&  ( NULL == pThisMapObj->pPrevMapObj ) )
    {
        pMapObjLL = pThisMapObj->pNextMapObj;
        pThisMapObj->pNextMapObj->pPrevMapObj = NULL;

    }

    // If last object then just need to make the prev map object the last
    if ( ( NULL == pThisMapObj->pNextMapObj ) &&  ( NULL != pThisMapObj->pPrevMapObj ) )
    {
       pThisMapObj->pPrevMapObj->pNextMapObj = NULL;
    }

    // If in the middle of list then need to remove
    if ( ( NULL != pThisMapObj->pNextMapObj ) &&  ( NULL != pThisMapObj->pPrevMapObj ) )
    {
        // - The previous map object's next pointer is updated with this object's next pointer
        pThisMapObj->pPrevMapObj->pNextMapObj = pThisMapObj->pNextMapObj;
        // - The next map object's previous pointer is updated with this objects previous pointer
        pThisMapObj->pNextMapObj->pPrevMapObj = pThisMapObj->pPrevMapObj;
    }

    // - Free this object
    cTools_memFree(pThisMapObj);

#endif
#ifdef _DEBUG
    printf("cTools_memUnMap:: unmap request for address 0x%X for %d bytes\n", (unsigned)vAddr, mapSizeInBytes);
#endif
}

int cTools_mutexInit(uint32_t mutexId)
{
	mutexId = mutexId; /* dummy instruction to remove compilation warning */
	return 0;
}

int cTools_mutexTrylock(uint32_t mutexId)
{
	mutexId = mutexId; /* dummy instruction to remove compilation warning */
	return 0;
}

int cTools_mutexUnlock(uint32_t mutexId)
{
	mutexId = mutexId; /* dummy instruction to remove compilation warning */
	return 0;
}
