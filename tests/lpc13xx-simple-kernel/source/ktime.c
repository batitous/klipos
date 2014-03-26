
#include <libs-klipos.h>

#include "../include/kqueue.h"
#include "../include/ktask.h"
#include "../include/ktime.h"


KList timers;
KTimer* currentTimer;
Int32 currentTime;

void debugTimer(void)
{
    KTimer* next = (KTimer*)timers.next;
    
    printf("Current timer %d: remain %d reload %d\r\n", next->task, currentTimer->remaining, currentTimer->reload);
    
    while (next != (KTimer*)&timers)
    {
        printf("Timer %d: remain %d reload %d\r\n", next->task, next->remaining, next->reload);
        next = next->next;
    }
}

#define SYSTICK_MAX     0xFFFFFF
#define MAX_TIME_IN_US  233000

void SysTick_Handler(void)
{
    KTimer* timer = (KTimer*)timers.next;
    Int32 nextTime = SYSTICK_MAX;
    
    while (timer != (KTimer*)&timers)
    {
        timer->remaining = timer->remaining - currentTime;

        if (timer->remaining == 0)
        {
            timer->remaining = timer->reload;
            postEventToTask(timer->task, 0);
            
            if (timer->task->priority == PRIORITY_HIGH_IRQ)
            {
                timer->task->code(0);
            }
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

void initKernelTimers(void)
{
    initKList(&timers);
    
    currentTimer = 0;
    
//    printf("SysTick_Config %d\r\n", SysTick_Config( GET_TICK_FROM_US(100000)) );
}


void initTimer(KTimer* timer, UInt32 delayInUs, KTask* task)
{
    timer->remaining = delayInUs;
    timer->reload = delayInUs;
    timer->task = task;
    
    insertTimerWithPriority(timer);
    
    KTimer* first = (KTimer*)timers.next;
    if (currentTimer != first)
    {
        currentTimer = first;
        currentTime = currentTimer->remaining;
        
        SysTick_Config( GET_TICK_FROM_US(currentTime));
    }
    
}