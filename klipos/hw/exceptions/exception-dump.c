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

#include "../include/kernel.h"

#define BFAR    (*(volatile UInt32 *)(0xE000ED38))
#define MMAR    (*(volatile UInt32 *)(0xE000ED34))
#define MMSR    (*(volatile UInt32 *)(0xE000ED28))

void dumpFaultHandler(UInt32 * stack)
{
    UInt32 r0,r1,r2,r3,r12,lr,pc,psr;
    
    r0 = stack[0];
    r1 = stack[1];
    r2 = stack[2];
    r3 = stack[3];
    r12 = stack[4];
    lr = stack[5];
    pc = stack[6];
    psr = stack[7];

    printf("HARDFAULT EXCEPTION\r\n");
    printf("[ Dump stack and fault register from base 0x%x]\r\n", stack );
    printf("R0  = 0x%x\r\n", r0);
    printf("R1  = 0x%x\r\n", r1);
    printf("R2  = 0x%x\r\n", r2);
    printf("R3  = 0x%x\r\n", r3);
    printf("R12 = 0x%x\r\n", r12);
    printf("LR  = 0x%x\r\n", lr);
    printf("PC  = 0x%x\r\n", pc);
    printf("psr = 0x%x\r\n", psr);
    printf("PSP = 0x%x\r\n", __get_PSP() );

    // Bus fault address 
    printf("BFAR = %x\r\n", BFAR );
    // MemManage Fault address 
    printf("MMAR = %x\r\n", MMAR );
    // MemManage Fault Status
    printf("MMSR = %x\r\n", MMSR  );
    // Hard Fault Status
    printf("HSFR = %x\r\n", (*(volatile UInt32 *)(0xE000ED2C)) );
    // Debug Fault Status
    printf("DFSR = %x\r\n", (*(volatile UInt32 *)(0xE000ED30)) );
    // Auxiliary Fault Status
    printf("AFSR = %x\r\n", (*(volatile UInt32 *)(0xE000ED3C)) );
    
#ifdef FIRMWARE_USE_FULL_KERNEL
    dumpKernel();
#endif
    
    while(1);
    
}
