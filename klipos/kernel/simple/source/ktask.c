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


static KList tasks;


//-------------------------- private functions


extern void initKernelTimers(void);


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


void initTask(KTask* task, KTaskCode c, KPriority prio)
{
    task->code = c;
    task->priority = prio;
    task->eventId = 0;
    
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

bool postEventToTask(KTask* task, uint32_t data)
{
    if (task==0)
    {
        return false;
    }
    
    if (task->priority == PRIORITY_VERY_HIGH)
    {
        // execute immediatly the task if high priority
        task->code(data);
        
        return true;
    }

    // else, write into the task's queue
    return writeToKQueue(&task->events, data);
}

void postEventToTaskWithId(uint32_t id, uint32_t data)
{
    KTask* task = (KTask*)tasks.next;

    while (task != (KTask*)&tasks)
    {
        if ( task->eventId == id)
        {
            if (task->priority == PRIORITY_VERY_HIGH)
            {
                task->code(data);
            }
            else
            {
                writeToKQueue(&task->events, data);
            }
        }
        
        task = task->next;
    }
}

void initSimpleKernel(void)
{
    initKList(&tasks);
    initKernelTimers();
}
