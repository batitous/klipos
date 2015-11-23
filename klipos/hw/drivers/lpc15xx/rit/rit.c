/*
 The MIT License (MIT)
 
 Copyright (c) 2014 Baptiste Burles
 
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
#include "../../../include/libs-klipos.h"



void initRitWithTick(void)
{
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL[1], 1);
        
    // Stop RI timer – otherwise we can't reset the counter
    LPC_RITIMER->CTRL = 0;

    LPC_RITIMER->COMPVAL = 0xffffffff;
    LPC_RITIMER->COMPVAL_H = 0x0000ffff; //0x00000000;

    LPC_RITIMER->COUNTER = 0;
    LPC_RITIMER->COUNTER_H = 0;

    LPC_RITIMER->CTRL = (1<< 1) | (1<< 3);
}

uint64_t getCpuTickFromRit(void)
{
    uint64_t temp = LPC_RITIMER->COUNTER | ((uint64_t)LPC_RITIMER->COUNTER_H << 32);
    return temp;
}

uint32_t getTickFromRit(void)
{
    uint64_t temp;
    
    temp = LPC_RITIMER->COUNTER | ((uint64_t)LPC_RITIMER->COUNTER_H << 32);
    
/*    if (temp > 0x3FFFFF)
    {
        temp = (temp / KERNEL_CPU_FREQ) * 1000;
    }
    else*/
    {
        temp = (temp *1000) / KERNEL_CPU_FREQ;
    }
    
    return temp;
}
