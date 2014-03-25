
#include <libs-klipos.h>

#include "../include/kqueue.h"
#include "../include/ktask.h"
#include "../include/ktime.h"


KList timers;
UInt32 timerId;
KTime* currentTimer;
UInt32 currentTime;

void debugTimer(void)
{
    KTime* next = (KTime*)timers.next;
    
    printf("Current timer %d: remain %d reload %d\r\n", next->id, currentTimer->remaining, currentTimer->reload);
    
    while (next != (KTime*)&timers)
    {
        printf("Timer %d: remain %d reload %d\r\n", next->id, next->remaining, next->reload);
        next = next->next;
    }
}

#define SYSTICK_MAX     0xFFFFFF

void SysTick_Handler(void)
{
    KTime* timer = (KTime*)timers.next;
    
    UInt32 nextTime = SYSTICK_MAX;
    Int32 test;
    
    while (timer != (KTime*)&timers)
    {
        test = (Int32)timer->remaining - (Int32)currentTime;
        if (test < 0)
        {
            printf("Test=%d\r\n", test);
            test = 0;
        }
        
        timer->remaining = test;
                
        if (timer->remaining == 0)
        {
            timer->remaining = timer->reload;
            postEventToTask(timer->id, 0);
        }
        else
        {
            if (nextTime > timer->remaining)
            {
                nextTime = timer->remaining;
            }
        }
        
        timer = timer->next;
    }
    

    if (nextTime != SYSTICK_MAX)
    {
        currentTime = nextTime;
        
        if (currentTime>233000)
        {
            currentTime = 233000;
        }
        
        if (SysTick_Config( GET_TICK_FROM_US(currentTime))==1)
        {
            printf("SysTick_Config 1 err %d\r\n",currentTime);
        }
    }
    /*else
    {
        printf("----\r\n");
        debugTimer();
        
        timer = (KTime*)timers.next;
        currentTime = timer->remaining;
        
        if (SysTick_Config( GET_TICK_FROM_US(currentTime))==1)
        {
            printf("SysTick_Config 2 err %d\r\n",currentTime);
        }
    }*/
    
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
    
    timerId = 1;
    currentTimer = 0;
    
//    printf("SysTick_Config %d\r\n", SysTick_Config( GET_TICK_FROM_US(100000)) );
}


void initTimer(KTime* timer, UInt32 delayInUs)
{
    timer->remaining = delayInUs;
    timer->reload = delayInUs;
    timer->id = timerId;
    
    timerId++;
    
    insertTimerWithPriority(timer);
    
    KTime* first = (KTime*)timers.next;
    if (currentTimer != first)
    {
        currentTimer = first;
        currentTime = currentTimer->remaining;
        
        SysTick_Config( GET_TICK_FROM_US(currentTime));
    }
    
}