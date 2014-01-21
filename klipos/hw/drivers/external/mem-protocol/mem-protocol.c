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

#include "../../include/libs-klipos.h"


static UInt32 memoryModuleNumber;
static UInt32 memoryModuleIndex;
static MemoryModule * memoryModules;

MemProtocolSendCallback sendFromModuleToMaster;


void initMemoryModule(UInt32 number, MemProtocolSendCallback func)
{
    memoryModuleIndex = 0;
    memoryModuleNumber = number;
    memoryModules = malloc( sizeof(MemoryModule) * number);
    sendFromModuleToMaster = func;
}

void addMemoryModule(UInt16 virtualAddr, UInt8 * objectAddr, UInt32 objectSize, MemProtocolUpdateCallback update )
{
    memoryModules[memoryModuleIndex].id = virtualAddr;
    memoryModules[memoryModuleIndex].size = objectSize;
    memoryModules[memoryModuleIndex].ptr = objectAddr;
    memoryModules[memoryModuleIndex].update = update;
    
    memoryModuleIndex++;
}

MemoryModule * getMemoryModuleFromAddress(UInt16 address)
{
    UInt32 i;
    MemoryModule * mem;

    for(i=0; i<memoryModuleNumber; i++)
    {
        mem = &memoryModules[i];
        if( address >= mem->id && address <= mem->id + mem->size)
        {
            return mem;
        }
    }

    return 0;
}


void updateMemoryModule(UInt8 *buffer, UInt8 size)
{
    UInt32 i ;
    MemoryModule * mem;
    UInt8* ptr;
    UInt32 offset;
    UInt16 virtualAddr;

    virtualAddr = ((buffer)[1]<<8)|((buffer)[0]);

    mem = getMemoryModuleFromAddress(virtualAddr);

    if ( mem == 0 )
    {
        return;
    }

    offset = virtualAddr - mem->id ;
    ptr     = mem->ptr + offset;

    //debugPrintf("Addr 0x%x FoundId 0x%x Off %d MSiz %d Size %d\r\n", currentSlaveModAddr, mem->id, offset, mem->size, size );

    if ( size == 2)
    {
        // If we have just 2 bytes of data, then it's a write order: 
        // Copy data from memory module to the master:
        sendFromModuleToMaster(virtualAddr, ptr, mem->size - offset);
    }
    else
    {    
        
        // Copy data to memory
        for (i=0; i < (UInt32)(size-2) && i < mem->size ;i++)
        {
            ptr[i] = buffer[i+2];
        }

        // Update the memory module
        if (mem->update!=0)
        {
            mem->update();
        }
    }

}
