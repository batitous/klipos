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
#include "../../../hw/include/libs-default.h"

#include "../../common/include/kcommon.h"

#include "../include/kqueue.h"
#include "../include/ktask.h"
#include "../include/ktimer.h"



//-------------------------- private variables

#define SYSTICK_MAX     0xFFFFFF
#define MAX_TIME_IN_US  233000

#define SHORT_DEADLINE_IN_US  10

static KList timers;
static int32_t currentTime;


//-------------------------- private functions

void SysTick_Handler(void)
{
    KTimer* timer = (KTimer*)timers.next;
    int32_t nextTime = SYSTICK_MAX;
    
    while (timer != (KTimer*)&timers)
    {
        timer->remaining = timer->remaining - currentTime;

        if (timer->remaining <= SHORT_DEADLINE_IN_US)
        {
            timer->remaining = timer->reload + timer->remaining;
            
            postEventToTask(timer->task, 0);
        }
        
        if (timer->remaining > 0 && nextTime > timer->remaining)
        {
            nextTime = timer->remaining;
        }
        
        timer = timer->next;
    }
    

    if (nextTime != SYSTICK_MAX)
    {
        currentTime = nextTime;
        
        if (currentTime>MAX_TIME_IN_US)
        {
            currentTime = MAX_TIME_IN_US;
        }
  
        SysTick_Config( GET_TICK_FROM_US(currentTime));
    }
    
}

void insertTimerWithPriority( KTimer* timer)
{
    KTimer * temp = (KTimer *)timers.next;
    KTimer * p;
    
    while ( temp != (KTimer *)&timers )
    {
        if ( timer->remaining <= temp->remaining )
        {
            break;
        }
        temp = temp->next;
    }
    
    p = temp->prev;
    timer->next = temp;
    timer->prev = p;
    
    p->next = timer;
    temp->prev = timer;
}

//-------------------------- public functions


void initKernelTimers(void)
{
    initKList(&timers);
    
    currentTime = 0;
}

void initTimer(KTimer* timer, uint32_t delayInUs, KTask* task)
{
    timer->remaining = delayInUs;
    timer->reload = delayInUs;
    timer->task = task;
    
    insertTimerWithPriority(timer);
    
    KTimer* first = (KTimer*)timers.next;
    if (currentTime != first->remaining)
    {
        currentTime = first->remaining;
        
        if (currentTime>MAX_TIME_IN_US)
        {
            currentTime = MAX_TIME_IN_US;
        }
        
        SysTick_Config( GET_TICK_FROM_US(currentTime));
    }
    
}
