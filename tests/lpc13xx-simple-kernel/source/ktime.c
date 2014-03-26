
#include <libs-klipos.h>

#include "../include/kqueue.h"
#include "../include/ktask.h"
#include "../include/ktime.h"


KList timers;
KTime* currentTimer;
Int32 currentTime;

void debugTimer(void)
{
    KTime* next = (KTime*)timers.next;
    
    printf("Current timer %d: remain %d reload %d\r\n", next->task, currentTimer->remaining, currentTimer->reload);
    
    while (next != (KTime*)&timers)
    {
        printf("Timer %d: remain %d reload %d\r\n", next->task, next->remaining, next->reload);
        next = next->next;
    }
}

#define SYSTICK_MAX     0xFFFFFF
#define MAX_TIME_IN_US  233000

void SysTick_Handler(void)
{
    KTime* timer = (KTime*)timers.next;
    Int32 nextTime = SYSTICK_MAX;
    
    while (timer != (KTime*)&timers)
    {
        timer->remaining = timer->remaining - currentTime;
                
        if (timer->remaining == 0)
        {
            timer->remaining = timer->reload;
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
        
        if (SysTick_Config( GET_TICK_FROM_US(currentTime))==1)
        {
            printf("SysTick_Config 1 err %d\r\n",currentTime);
        }
    }
    
}

void insertTimerWithPriority( KTime* timer)
{
    KTime * temp = (KTime *)timers.next;
    KTime * p;
    
    while ( temp != (KTime *)&timers )
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

void initKernelTimers(void)
{
    initKList(&timers);
    
    currentTimer = 0;
    
//    printf("SysTick_Config %d\r\n", SysTick_Config( GET_TICK_FROM_US(100000)) );
}


void initTimer(KTime* timer, UInt32 delayInUs, KTask* task)
{
    timer->remaining = delayInUs;
    timer->reload = delayInUs;
    timer->task = task;
    
    insertTimerWithPriority(timer);
    
    KTime* first = (KTime*)timers.next;
    if (currentTimer != first)
    {
        currentTimer = first;
        currentTime = currentTimer->remaining;
        
        SysTick_Config( GET_TICK_FROM_US(currentTime));
    }
    
}