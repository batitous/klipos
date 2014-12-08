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
#include "../../../include/libs-klipos.h"


//----------------------------- private menbers

static volatile uint32_t ritCounter;


//----------------------------- private functions

void RIT_IRQHandler(void)
{
    // Clear interrupt
    LPC_RITIMER->CTRL |= (1<< 0);

    ritCounter++;
}


//----------------------------- public functions

void initTimerRit(uint32_t timeInUs)
{
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL[1], 1);
    
    ritCounter = 0;
    
    // Stop RI timer – otherwise we can't reset the counter
    LPC_RITIMER->CTRL = 0;

    // Init RI timer (we don't need to enable timer – it is always running as per the updated User Manual UM10524)
    LPC_RITIMER->COMPVAL = GET_TICK_FROM_US(timeInUs);
    LPC_RITIMER->COMPVAL_H = 0;

    // Reset counter (otherwise it might already be above the compare value and then it would take a loong time to overflow to zero)
    LPC_RITIMER->COUNTER = 0;
    LPC_RITIMER->COUNTER_H = 0;

    // Set RITENCLR (clear on match), RITENBR (halt timer on debug) and RITEN (start timer)
    LPC_RITIMER->CTRL = (1<< 1) | (1<< 2) | (1<< 3);

    // Enable RIT interrupt
    NVIC_EnableIRQ( RITIMER_IRQn ); 
}
 
uint32_t getTimerRitCounter(void)
{
    return ritCounter;
}
