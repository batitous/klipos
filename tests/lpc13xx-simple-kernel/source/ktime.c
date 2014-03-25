
#include <libs-klipos.h>

#include "../include/kqueue.h"
#include "../include/ktask.h"
#include "../include/ktime.h"


KList timers;
KTime* currentTimer;


void debugTimer(void)
{
    KTime* next = (KTime*)timers.next;
    
    printf("Current timer: remain %d reload %d\r\n", currentTimer->remaining, currentTimer->reload);
    
    while (next != (KTime*)&timers)
    {
        printf("Timer: remain %d reload %d\r\n", next->remaining, next->reload);
        next = next->next;
    }
}


void SysTick_Handler(void)
{

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
    
    printf("SysTick_Config %d\r\n", SysTick_Config( GET_TICK_FROM_US(100000)) );
}


void initTimer(KTime* timer, UInt32 delayInUs)
{
    timer->remaining = delayInUs;
    timer->reload = delayInUs;
    timer->id = 0;
    
    insertTimerWithPriority(timer);
    
    if (currentTimer==0)
    {
        currentTimer = (KTime*)timers.next;
    }
    
}