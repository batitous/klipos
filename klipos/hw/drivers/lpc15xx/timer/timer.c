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


//------------------------ private menbers

TimerIrqCallback sct0Callback;
TimerIrqCallback sct1Callback;
TimerIrqCallback sct2Callback;
TimerIrqCallback sct3Callback;


//------------------------ private functions

void SCT0_IRQHandler(void)
{
    sct0Callback();
    
    LPC_SCT0->EVFLAG = 0x00000001;
}

void SCT1_IRQHandler(void)
{
    sct1Callback();
    
    LPC_SCT1->EVFLAG = 0x00000001;
}

void SCT2_IRQHandler(void)
{
    sct2Callback();
    
    LPC_SCT2->EVFLAG = 0x00000001;
}

void SCT3_IRQHandler(void)
{
    sct3Callback();
    
    LPC_SCT3->EVFLAG = 0x00000001;
}


//------------------------ public functions

void initScTimer(Timer * timer, TIMER selectedTimer, uint32_t timeInUs, TimerIrqCallback callback)
{
    timer->selected = selectedTimer;
    
    // enable the SCTx clock
    switch(selectedTimer)
    {
        case TIMER0:
            sct0Callback = callback;
            timer->t = LPC_SCT0;
            SETBIT(LPC_SYSCON->SYSAHBCLKCTRL[1],2);
            break;
        case TIMER1:
            sct1Callback = callback;
            timer->t = LPC_SCT1;
            SETBIT(LPC_SYSCON->SYSAHBCLKCTRL[1],3);
            break;
        case TIMER2:
            sct2Callback = callback;
            timer->t = LPC_SCT2;
            SETBIT(LPC_SYSCON->SYSAHBCLKCTRL[1],4);
            break;
        case TIMER3:
            sct3Callback = callback;
            timer->t = LPC_SCT3;
            SETBIT(LPC_SYSCON->SYSAHBCLKCTRL[1],5);
            break;
    }
    
    // disable timer before set
    SETBIT(timer->t->CTRL_U, 2);
    
    timer->t->CONFIG            = (1 << 0) | (1 << 17); // unified 32-bit timer, auto limit

    timer->t->MATCH[0].U        = GET_TICK_FROM_US(timeInUs);
    timer->t->MATCHREL[0].U     = GET_TICK_FROM_US(timeInUs);

    timer->t->EVENT[0].STATE    = 0xFFFFFFFF;    // event 0 happens in all states
    timer->t->EVENT[0].CTRL     = (1 << 12);     // match 0 condition only
    timer->t->EVEN              = (1 << 0);      // event 0 generates an interrupt
    
    
    // enable SCTx interrupt
    switch(selectedTimer)
    {
        case TIMER0:
            NVIC_EnableIRQ(SCT0_IRQn);
            break;
        case TIMER1:
            NVIC_EnableIRQ(SCT1_IRQn);
            break;
        case TIMER2:
            NVIC_EnableIRQ(SCT2_IRQn);
            break;
        case TIMER3:
            NVIC_EnableIRQ(SCT3_IRQn);
            break;
    }
    
}

void setTimeInScTimer(Timer * timer, uint32_t timeInUs)
{
    uint32_t tick = GET_TICK_FROM_US(timeInUs);
    
    timer->t->MATCH[0].U        = tick;
    timer->t->MATCHREL[0].U     = tick;
    timer->t->COUNT_U           = 0;
}

void setScTimer(Timer * timer, uint32_t timeInUs, TimerIrqCallback callback)
{
    setTimeInScTimer(timer, timeInUs);
    
    switch(timer->selected)
    {
        case TIMER0:
            sct0Callback = callback;
            break;
        case TIMER1:
            sct1Callback = callback;
            break;
        case TIMER2:
            sct2Callback = callback;
            break;
        case TIMER3:
            sct3Callback = callback;
            break;
    }
}

void enableScTimer(Timer * timer)
{
    CLRBIT(timer->t->CTRL_U, 2);
}

void disableScTimer(Timer * timer)
{
    SETBIT(timer->t->CTRL_U, 2);
}



