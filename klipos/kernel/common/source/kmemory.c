/*
 The MIT License (MIT)
 
 Copyright (c) 2013 Baptiste Burles, Christophe Casson, Sylvain Fay-Chatelard
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "../../../hw/include/types.h"

#include "../include/kmemory.h"
#include "../../../hw/include/utils.h"


//-------------------------- configuration


// WARNING: slow down boot code
//#define USE_MEMORY_TRACE        1


//-------------------------- macro definition

// Get free flag of block
#define GET_FREE_FLAG(node) (0x8000&node)

// Is this block free ?
#define IS_FREE(node)       GET_FREE_FLAG(node) != 0

// convert byte unit to block unit (the +1 is for reserve space for future block)
#define GET_UNIT(byte)      (((byte+3)>>2) + 1)

// get the previous node (without the free flag)
#define GET_PREV(node)         (node&0x7FFF)

// Set block as free
#define SET_FREE(node)          node = (node|0x8000)

// Set block as not free
#define SET_NOT_FREE(node)      node = (node&0x7FFF)


#ifdef USE_MEMORY_TRACE
#   define TRACE_MEM(str)	printf str
#else
#   define TRACE_MEM(str)
#endif

//-------------------------- private functions


uint32_t getSizeOfBlock(const KMemory * block, const KMemory * previous)
{
    if(previous!=0)
    {
        return block->next - previous->next;
    }
    
    return block->next;
}

//-------------------------- public functions


KMemory * initMemory(const uint8_t * mem, uint32_t sizeInByte)
{
    KMemory * start;
    KMemory * end;
    
    start = (KMemory *)mem;
    
    start->prev = 0;
    
    // First block is free
    SET_FREE(start->prev);
    
    // Compute the next link, we remove the start's block and the end's block size !
    start->next = GET_UNIT(sizeInByte) - 2;
    
    // Compute the block address of end's block
    end = (KMemory *)(mem + (start->next<<2));
    
    // The end's block is set as 'used'
    end->prev = 0;
    end->next = 0;
        
    
    TRACE_MEM(("Initialize memoy [0x%x 0x%x] with %d blocks (%d bytes)\n", start, end, start->next, sizeInByte));
    
    
    return start;
}

void * allocMemory(KMemory * mem, uint32_t sizeInBytes)
{
    uint32_t size;
    KMemory * p = mem;
    KMemory * prev = 0;
    KMemory * next;
    
    uint16_t allocatedIndex;
    KMemory * allocated;
    
    uint32_t want = GET_UNIT(sizeInBytes);
    
//    TRACE_MEM(("allocmemory want %d units of memory (user want %d bytes)\r\n", want, sizeInBytes));
    
    
    while( p->next != 0)
    {
        if( IS_FREE(p->prev) )
        {
            size = getSizeOfBlock(p, prev);
            
            if(size == want)
            {
                // We found an exact block of memory, we don't have to split this block !
                // We set the block's flag as 'not free' 
                
                SET_NOT_FREE(p->prev);
                
                TRACE_MEM(("alloc %4d bytes at 0x%x\r\n", sizeInBytes,p));
                
                return (uint8_t *)(p+1);
            }
            else if( size > want)
            {
                // We have found a block larger than we want :
                // we have to create a new block between the current (p) and the next (p->next)
                
                allocatedIndex = (p->next - want);
                allocated = (KMemory *)(mem + allocatedIndex);
                
                next = (KMemory *)(mem + p->next);
                
                allocated->next = p->next;
                p->next = allocatedIndex;
                
                // We don't need to set the 'not free' flag on the new block : by default the 'not free' is set
                
                allocated->prev = GET_PREV(next->prev);
                next->prev = allocatedIndex | GET_FREE_FLAG(next->prev);
                
                
                TRACE_MEM(("alloc %4d bytes at 0x%x (block %4d with %4d units)\r\n", sizeInBytes,allocated,allocatedIndex, want));
                
                return (uint8_t *)(allocated+1);
            }
        }
        
        prev = p; 
        p = (KMemory *)(mem + p->next);
    }
    
    
    TRACE_MEM(("failed to alloc %d bytes\r\n", sizeInBytes));
    
    return 0;
}

void freeMemory(KMemory * mem, uint8_t * ptr)
{
    KMemory * p = (KMemory *)(ptr-4);
    KMemory * prev;
    KMemory * next;
    KMemory * next2;
    uint16_t pprev;
    
    SET_FREE(p->prev);
    
    pprev = GET_PREV(p->prev);
    next = (KMemory *)(mem + p->next);
    
    
    // If the next block is free, merge next block into p and next2
    if( IS_FREE(next->prev))
    {
        next2 = (KMemory *)(mem + next->next);
        
        p->next = next->next;
        next2->prev = GET_PREV(next->prev) | GET_FREE_FLAG(next2->prev);
    }
    
    // If previous block is not the start block, then...
    if(pprev!=0)
    {
        prev = (KMemory *)(mem + pprev);
        
        if( IS_FREE(prev->prev))
        {        
            // The previous block is free, then merge p block into previous and next

            // Reload the next block pointer (maybe p->next has been changed) 
            next = (KMemory *)(mem + p->next);
            
            prev->next = p->next;
            next->prev = pprev | GET_FREE_FLAG(next->prev);
        }
    }
    
    TRACE_MEM(("free memory at 0x%x\r\n",p));
    
}

#ifdef USE_MEMORY_TRACE

uint32_t getMemoryAvailable(KMemory * mem)
{
    KMemory * p = mem;
    KMemory * prev = 0;
    uint32_t count = 0;
    
    while(p->next != 0)
    {
        if( IS_FREE(p->prev))
        {
            count += getSizeOfBlock(p, prev);
        }
        
        prev = p;
        p = (KMemory *)(mem + (p->next));
    }
    
    // Set the size in bytes units
    return count << 2;
}

#endif
