
#include <libs-klipos.h>

#include "../include/kqueue.h"
#include "../include/ktask.h"

//-------------------------- private variables


static KList tasks;


//-------------------------- private functions


void insertTaskWithPriority( KTask * th)
{
    KTask * temp = (KTask *)tasks.next;
    KTask * p;
    
    while ( temp != (KTask *)&tasks )
    {
        if ( th->priority >= temp->priority )
        {
            break;
        }
        temp = temp->next;
    }
    
    p = temp->prev;
    th->next = temp;
    th->prev = p;
    
    p->next = th;
    temp->prev = th;
    
}

void idleTask(void)
{
    setMcuToDefaultSleep();
}


//-------------------------- public functions


void initTask(KTask* task, KTaskCode c, KPriority prio, uint32_t eventId)
{
    task->code = c;
    task->priority = prio;
    task->eventId = eventId;
    
    initKQueue(&task->events, task->eventsBuffer, TASK_QUEUE_SIZE);
    
    insertTaskWithPriority(task);
}

void scheduleTask(void)
{
    uint32_t tmp;
    
    bool executed = false;
    
    KTask* next = (KTask*)tasks.next;
    
    while (next != (KTask*)&tasks)
    {
        while ( readFromKQueue(&next->events, &tmp) != false)
        {
//          printf("Scheduler: execute task prio %d (data = 0x%x %c %d)\n", next->priority,tmp, tmp, tmp);
            
            executed = true;
            next->code(tmp);
        }
        next = next->next;
    }
    
    if (executed==false)
    {
        idleTask();
    }

}

void postEventToTask(KTask* task, uint32_t data)
{
    writeToKQueue(&task->events, data);
}

void postEventToTaskWithId(uint32_t id, uint32_t data)
{
    KTask* next = (KTask*)tasks.next;

    while (next != (KTask*)&tasks)
    {
        if ( next->eventId == id)
        {
            writeToKQueue(&next->events, data);
        }
        
        next = next->next;
    }
}

void initKernel(void)
{
    initKList(&tasks);
}
