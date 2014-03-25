
#include <libs-klipos.h>

#include "../include/kqueue.h"
#include "../include/ktask.h"

KTask idleTask;
KList tasks;


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

void initTask(KTask* task, KTaskCode c, UInt8 prio, UInt32 eventId)
{
    task->code = c;
    task->priority = prio;
    task->eventId = eventId;
    
    initKQueue(&task->events, task->eventsBuffer, QUEUE_SIZE);
    
    if (task != &idleTask)
    {
        insertTaskWithPriority(task);
    }
}

bool scheduleTask(void)
{
    UInt32 tmp;
    
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
    
    return executed;
}

void postEventToTask(UInt32 id, UInt32 data)
{
    KTask* next = (KTask*)tasks.next;

    while (next != (KTask*)&tasks)
    {
        if ( next->eventId == id)
        {
            if (writeToKQueue(&next->events, data) == false )
            {
            }
        }
        
        next = next->next;
    }
}

void idleCode(UInt32 event)
{
    
}

void initKernel(void)
{
    initKList(&tasks);
    initTask(&idleTask, idleCode, 0, 0);
}

void executeIdleTask(void)
{
    idleCode(0);
}