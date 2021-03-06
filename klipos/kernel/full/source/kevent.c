/*
 The MIT License (MIT)
 
 Copyright (c) 2013 Baptiste Burles, Christophe Casson, Sylvain Fay-Chatelard
 
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

#include "../../common/include/klist.h"
#include "../include/kthread.h"
#include "../include/kernel.h"
#include "../include/kevent.h"
#include "../include/ktimer.h"
#include "../include/kernel-private.h"


//-------------------------- private menbers:

#define EVENT_MAX                       16      /**< if you have more than 16 events in less than 100 us, then increase */

#define EVENT_THREAD_CPU_TIME           10      /**< 1 ms is given to the event thread */
#define EVENT_THREAD_PRIORITY           100     /**< high priority */

#ifndef EVENT_THREAD_STACK_SIZE
#       define EVENT_THREAD_STACK_SIZE  512     /**< size of event thread stack */
#endif

static uint32_t kEventRead;               /**< read index in kEvents */
static volatile uint32_t kEventWrite;     /**< write index in kEvents */

static KEvent kEvents[EVENT_MAX];       /**< stack of event */

static SList kEventManagers;          /**< list of event callback */
static KThread kEventThread;                 /**< event thread manager */
static uint8_t kEventStack[EVENT_THREAD_STACK_SIZE];

static uint16_t kEventLastAlarmId;      /**< Id for alarm event */

//-------------------------- private functions:

KEventManager * getEventRegister(uint32_t id)
{
    KEventManager * temp = (KEventManager *)kEventManagers.next;

    while(temp!=0)
    {
        if(temp->id==id)
        {
            return temp;
        }
        temp = temp->next;
    }
    
    return 0;
}

void kEventThreadManager(void)
{
    uint32_t size,i;
    KEventManager * manager = kEventManagers.next;
    KEvent * e;
    
    while(1)
    {
        size = kEventWrite;
        
        if(size!=kEventRead)
        {
            for( i = kEventRead ; i != size ; )
            {
                // retrieve the event object from the event posted
                // then, call the event callback
                
                e = kEvents + (i & (EVENT_MAX-1));
                
                if(manager->id!=e->id)
                {
                    manager = getEventRegister(e->id);
                }
                
                
                if(manager!=0)
                {
                    if(manager->callback!=0)
                    {
                        if (e->message==0)
                        {
                            e->message = manager->data;
                        }
                        manager->callback(e);
                    }
                }
                
                i++;
            }
            kEventRead = i;
        }
        
        // if event has been posted during the for loop, then relaunch the loop
        if(kEventWrite==kEventRead)
        {
            setTaskAsBlocked();
        }
    }
}

void _postKEvent(uint32_t id, uint32_t message)
{
    uint32_t tmp = kEventWrite & (EVENT_MAX-1);
    
    kEvents[tmp].id = id;
    kEvents[tmp].message = message;
    kEvents[tmp].time = getCurrentTimeOfKernel();
    
    kEventWrite++;
}

//--------------------------  public menbers:

void initEventManager(void)
{
    uint32_t i;
    
    kEventLastAlarmId = 1;
    
    kEventRead = 0;
    kEventWrite = 0;
    
    initSList(&kEventManagers);
    
    for(i=0;i<EVENT_MAX;i++)
    {
        kEvents[i].time = 0;
        kEvents[i].id = 0;
        kEvents[i].message = 0;
    }
    
    // event manager thread is set with a high priority
    initThread(&kEventThread, &kEventThreadManager, kEventStack, EVENT_THREAD_STACK_SIZE,EVENT_THREAD_CPU_TIME,EVENT_THREAD_PRIORITY);
       
}

bool registerEvent(KEventManager *manager, uint32_t id, KEventCallback user, uint32_t userData)
{
    if( getEventRegister(id) != 0)
    {
        // event already exist !
        //todo add user callback in the event callback list
        return false;
    }
    
    manager->id = id;
    manager->callback = user;
    manager->data = userData;
 
    insertSNodeToStart(&kEventManagers,(KLink *)manager);
    
    return true;
}

void postEvent(uint32_t id, uint32_t message)
{
    _postKEvent(id,message);
    setTaskAsReady(&kEventThread);
}

void postEventFromIrq(uint32_t id, uint32_t message)
{
    _postKEvent(id,message);
    irqSetTaskAsReady(&kEventThread);
}

void enableEventOnAlarm(KAlarm *alarm, KEventManager *manager, KEventCallback callback, uint32_t dataForCallback)
{
    alarm->thread = &kEventThread;
    alarm->id = kEventLastAlarmId;
    kEventLastAlarmId++;
        
    registerEvent( manager, KEVENT_ALARM_MASK | alarm->id , callback, dataForCallback);
}
