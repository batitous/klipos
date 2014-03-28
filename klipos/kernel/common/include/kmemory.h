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
#ifndef KLIPOS_KERNEL_MEMORY_H
#define KLIPOS_KERNEL_MEMORY_H

/** @brief Memory link object */
typedef struct _kernel_link_memory_
{
    UInt16 prev;        /**< previous block of memory */
    UInt16 next;        /**< next block of memory */
} KMemory;


/** @brief
 * 
 * @param mem
 * @param sizeInByte            Maximum value: 131068 bytes (127Kbytes)
 * @return 
 */
extern KMemory * initMemory(const UInt8 * mem, UInt32 sizeInByte);

extern UInt32 getMemoryAvailable(KMemory * mem);

extern void * allocMemory(KMemory * mem, UInt32 sizeInBytes);

extern void freeMemory(KMemory * mem, UInt8 * ptr);



/** @brief Default memory object. */
extern KMemory * defaultMemory;

/** @brief Malloc */
#define malloc(size)     allocMemory(defaultMemory,size)
/** @brief Free */
#define free(ptr)       freeMemory(defaultMemory,ptr)


#endif

