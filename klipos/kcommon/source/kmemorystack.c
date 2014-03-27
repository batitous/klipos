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
#include "../../hw/include/libs-default.h"
#include "../include/kernel-klipos.h"


//-------------------------- debug

//#define MEMSTACK_USE_DEBUG

#ifdef MEMSTACK_USE_DEBUG
#   define TRACE_MEMSTACK(str)	debugPrintf str
#else
#   define TRACE_MEMSTACK(str)
#endif


//-------------------------- public functions

void initMemoryStack(KMemoryStack *stack, UInt8 *address, UInt32 size)
{
    stack->nextFreeAddress = address;
    stack->lastAddress = stack->nextFreeAddress + size;
    
    TRACE_MEMSTACK(("memstack init at 0x%x size %d\r\n", address, size));
}

void * allocMemoryStack(KMemoryStack *stack, UInt32 size)
{
    UInt8 * currentStack = stack->nextFreeAddress;
    
    if( (stack->nextFreeAddress+size) <= stack->lastAddress)
    {
        stack->nextFreeAddress += size;
     
        TRACE_MEMSTACK(("memstack alloc at 0x%x size %d\r\n", currentStack,size));
        
        return (void *)currentStack;
    }
    
    TRACE_MEMSTACK(("memstack full ! next 0x%x last 0x%x\r\n", stack->nextFreeAddress, stack->lastAddress));
    
    return 0;
}
