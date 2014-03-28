
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


void initTask(KTask* task, KTaskCode c, KPriority prio, UInt32 eventId)
{
    task->code = c;
    task->priority = prio;
    task->eventId = eventId;
    
    initKQueue(&task->events, task->eventsBuffer, TASK_QUEUE_SIZE);
    
    insertTaskWithPriority(task);
}

void scheduleTask(void)
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
    
    if (executed==false)
    {
        idleTask();
    }

}

void postEventToTask(KTask* task, UInt32 data)
{
    if (task->priority == PRIORITY_VERY_HIGH)
    {
        // if very high priority, execute immediatly the task
        task->code(data);
    }
    else
    {
        // else, write into the task's queue
        writeToKQueue(&task->events, data);
    }
}

void postEventToTaskWithId(UInt32 id, UInt32 data)
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
