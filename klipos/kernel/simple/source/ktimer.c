
#include <libs-klipos.h>

#include "../include/kqueue.h"
#include "../include/ktask.h"
#include "../include/ktimer.h"


//-------------------------- private variables

#define SYSTICK_MAX     0xFFFFFF
#define MAX_TIME_IN_US  233000


static KList timers;
static Int32 currentTime;


//-------------------------- private functions

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

//-------------------------- public functions


void initKernelTimers(void)
{
    initKList(&timers);
    
    currentTime = 0;
}

void initTimer(KTimer* timer, UInt32 delayInUs, KTask* task)
{
    timer->remaining = delayInUs;
    timer->reload = delayInUs;
    timer->task = task;
    
    insertTimerWithPriority(timer);
    
    KTimer* first = (KTimer*)timers.next;
    if (currentTime != first->remaining)
    {
        currentTime = first->remaining;
        
        SysTick_Config( GET_TICK_FROM_US(currentTime));
    }
    
}
