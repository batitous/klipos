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

TimerIrqCallback timer0IrqCallback;
TimerIrqCallback timer1IrqCallback;

//----------------------------- private functions


void fakeTimerUserIRQRoutine()
{
}




void TIMER_32_0_IRQn_Handler(void)
{
    // clear IRQ Match
    SETBIT(LPC_TMR32B0->IR,0);
    
    timer0IrqCallback();
    
}


void TIMER_32_1_IRQn_Handler(void)
{
    // clear IRQ Match
    SETBIT(LPC_TMR32B1->IR,0);
    
    timer1IrqCallback();
    
}

//----------------------------- public functions

bool initTimer32(Timer* timer, TIMER timerSelected, uint32_t waitInUs)
{
    LPC_TMR_TypeDef * t;
    
    // IOCON_PIO0_1 CT32B0_MAT2 FUNC=0x2
    // IOCON_R_PIO0_11 CT32B0_MAT3 warning : AD0 FUNC=0x3
    // IOCON_R_PIO1_0 CT32B1_CAP0 warning : AD1 FUNC=0x3
    // IOCON_R_PIO1_1 CT32B1_MAT0 warning : AD2 FUNC=0x3
    // IOCON_R_PIO1_2 CT32B1_MAT1 warning : AD3 FUNC=0x3
    // IOCON_SWDIO_PIO1_3 CT32B1_MAT2 warning : AD4 FUNC=0x3
    // IOCON_PIO1_4 CT32B1_MAT3 warning: AD5 FUNC=0x2
    // IOCON_PIO1_5 CT32B0_CAP0 FUNC=0x2
    // IOCON_PIO1_6 CT32B0_MAT0 warning: RXD FUNC=0x2
    // IOCON_PIO1_7 CT32B0_MAT1 warning: TXD FUNC=0x2
    
    
    
    // SYSAHBCLKCTRL bit9 1 = timer0 bit10 1 =timer1
    if ( timerSelected==TIMER0)
    {
        timer0IrqCallback = &fakeTimerUserIRQRoutine;
        t = LPC_TMR32B0;
        SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,9);
    }
    else
    {
        timer1IrqCallback = &fakeTimerUserIRQRoutine;
        t = LPC_TMR32B1;
        SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,10);
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
        NVIC_SetPriority(TIMER_32_0_IRQn, 0x02);
        NVIC_EnableIRQ(TIMER_32_0_IRQn);
    }
    else
    {
        NVIC_SetPriority(TIMER_32_1_IRQn, 0x03);
        NVIC_EnableIRQ(TIMER_32_1_IRQn);
    }
    
    return true;
}

void setTimer32(Timer* timer, uint32_t waitInUs)
{
    LPC_TMR_TypeDef * t = timer->t;
        
    CLRBIT(t->TCR,0);
        
    t->MR0 = GET_TICK_FROM_US(waitInUs);
    t->TC = 0;
}

void enableTimer32(Timer* timer)
{
    SETBIT(timer->t->TCR,0);
}

void disableTimer32(Timer* timer)
{
    CLRBIT(timer->t->TCR,0);
}

bool isTimer32Enable(Timer* timer)
{
    if ((timer->t->TCR & 0x1) != 0)
    {
        return true;
    }
    
    return false;
}

void setTimer32Callback(Timer* timer, TimerIrqCallback c)
{
    if (timer->t == LPC_TMR32B0)
    {
        timer0IrqCallback = c;
    }
    else
    {
        timer1IrqCallback = c;
    }
}


// it has been tested, ok !
void waitUsPrecise(TIMER timerSelected, uint32_t waitInUs)
{
    LPC_TMR_TypeDef * timer;
    
    if ( timerSelected==TIMER0)
    {
        timer = LPC_TMR32B0;
        SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,9);
    }
    else
    {
        timer = LPC_TMR32B1;
        SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,10);
    }
    
    timer->TCR = 0;
    timer->MR3 = GET_TICK_FROM_US(waitInUs);
    
    timer->TC = 0;
    
    SETBIT(timer->MCR,11);
    SETBIT(timer->TCR,0);
    
    while( (timer->TCR & 0x1) != 0);
}
