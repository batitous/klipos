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



/* try to manage processor fault */

#ifdef FIRMWARE_USE_DEBUG

extern void dumpFaultHandler(UInt32 * stack);

#endif


// Bus Faults Exception
void BusFault_Handler(void)
{
    // access to invalid memory
    debugPrintf("BUS FAULTS EXCEPTION\r\n");
}

// Memory Management Exception
void MemManage_Handler(void)
{
    // write to a read only memory, access to a undefined mpu region
    debugPrintf("MEMORY MANAGEMENT EXCEPTION\r\n");
}

// Usage Faults Exception
void UsageFault_Handler(void)
{
    debugPrintf("USAGE FAULTS EXCEPTION\r\n");
}


// Hard Faults Exception
//naked : no backup, no restore, no return : we need to do all this things
void HardFault_Handler(void) __attribute__( ( naked ) );
void HardFault_Handler(void)
{
#ifdef FIRMWARE_USE_DEBUG
    // this exception has the highest priority (whitout the reset and nmi) :
    // in most fault case, we are in this exception
    UInt32 reg;
    UInt32 * r;

    // get correct stack : process stack or main stack
    __asm __volatile__ (
        "tst    LR,#4\r\n"
        "ite    eq\r\n"
        "mrseq  %[result],MSP\r\n"
        "mrsne  %[result],PSP"
        : [result]"=r" (reg)
        );

    // function is naked: save LR register !
    __asm__ ("push {lr}");

    
    // dump stack :
    r = (UInt32 *)reg;
    dumpFaultHandler(r);
    

    // function is naked: exit irq by a pop !
    __asm__ ("pop {pc}");
#endif
}
