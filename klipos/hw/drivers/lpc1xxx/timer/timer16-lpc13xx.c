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

TimerIrqCallback timer16_0IrqCallback;
TimerIrqCallback timer16_1IrqCallback;

//----------------------------- private functions


void fakeTimer16UserIRQRoutine()
{
}




void TIMER_16_0_IRQn_Handler(void)
{
    // clear IRQ Match
    SETBIT(LPC_TMR16B0->IR,0);
    
    timer16_0IrqCallback();
    
}

/*void TIMER_16_1_IRQn_Handler(void)
{
    // clear IRQ Match
    SETBIT(LPC_TMR16B1->IR,0);
    
    timer16_1IrqCallback();
    
}*/

//----------------------------- public functions

bool initTimer16(Timer* timer, TIMER timerSelected, uint32_t waitInUs)
{
    LPC_TMR_TypeDef * t;
    
    if ( timerSelected==TIMER0)
    {
        timer16_0IrqCallback = &fakeTimer16UserIRQRoutine;
        t = LPC_TMR16B0;
        SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,7);
    }
    else
    {
        timer16_1IrqCallback = &fakeTimer16UserIRQRoutine;
        t = LPC_TMR16B1;
        SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,8);
    }
    
    timer->t = t;
    
    t->MR0 = GET_TICK_FROM_US(waitInUs);
    t->TC = 0;
    
    // interrupt on MR0
    SETBIT(t->MCR,0);
    // reset when MRO match
    SETBIT(t->MCR,1);
    
    // enable IRQ
    if (timerSelected==TIMER0)
    {
        NVIC_SetPriority(TIMER_16_0_IRQn, 0x02);
        NVIC_EnableIRQ(TIMER_16_0_IRQn);
    }
    else
    {
        NVIC_SetPriority(TIMER_16_1_IRQn, 0x03);
        NVIC_EnableIRQ(TIMER_16_1_IRQn);
    }
    
    return true;
}

void setTimer16(Timer* timer, uint32_t waitInUs)
{
    LPC_TMR_TypeDef * t = timer->t;
        
    CLRBIT(t->TCR,0);
        
    t->MR0 = GET_TICK_FROM_US(waitInUs);
    t->TC = 0;
}

void enableTimer16(Timer* timer)
{
    SETBIT(timer->t->TCR,0);
}

void disableTimer16(Timer* timer)
{
    CLRBIT(timer->t->TCR,0);
}

bool isTimer16Enable(Timer* timer)
{
    if ((timer->t->TCR & 0x1) != 0)
    {
        return true;
    }
    
    return false;
}

void setTimer16_0Callback(TimerIrqCallback c)
{
    timer16_0IrqCallback = c;
}

void setTimer16_1Callback(TimerIrqCallback c)
{
    timer16_1IrqCallback = c;
}
