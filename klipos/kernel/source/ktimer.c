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
#include "../../hw/include/libs-default.h"

#include "../include/klist.h"
#include "../include/kthread.h"
#include "../include/kernel.h"
#include "../include/kernel-private.h"
#include "../include/kevent.h"
#include "../include/ktimer.h"


//-------------------------- private definitions

extern void _postKEvent(UInt32 id, UInt32 message);

//-------------------------- private menbers

KList alarms;


//-------------------------- private functions

void initKAlarm(void)
{
    initKList(&alarms);
}


void manageKTimer(void)
{
    //warning this code is executed in kernel mode !
    KThread * th = (KThread *)(tasksWaiting.next);
    KAlarm * alarm = (KAlarm *)(alarms.next);

    KThread * next;


    // manage wait
    while( th != (KThread *)&tasksWaiting)
    {
        next = th->next;
        if(th->waiting!=0)
        {
            th->waiting = th->waiting -1;

            if(th->waiting == 0)
            {
                kernelSetTaskAsReady(th);
            }
        }

        th = next;
    }

    // manage alarm
    while( alarm!= (KAlarm *)&alarms)
    {
        if(alarm->remaining != 0)
        {
            alarm->remaining = alarm->remaining -1;

            if(alarm->remaining==0)
            {
#ifdef KERNEL_USE_KEVENT
                if(alarm->id!=0)
                {
                    // instead of wakeup a thread, post an event
                    alarm->remaining = alarm->reload;
                    

                    // we can't use the "postEvent" here :-(
                    _postKEvent(KEVENT_ALARM_MASK | alarm->id ,0);

                    extern KThread * kEventThread;
                    kernelSetTaskAsReady(kEventThread);
                }
                else
#endif //KERNEL_USE_KEVENT
                {    
                    if(alarm->thread!=0)
                    {
                        kernelSetTaskAsReady(alarm->thread);
                    }
                }    
            }
        }

        alarm = alarm->next;
    }
}

//-------------------------- public functions

void wait100Us(UInt32 delay)
{
    currentTask->waiting = delay;
    setTaskAsWaiting();
}

void waitMs(UInt32 delay)
{
    wait100Us(delay*10);
}

void initAlarm(KAlarm *alarm, UInt32 delay)
{
    alarm->remaining = 0;
    alarm->reload = delay * 10;
    alarm->thread = (KThread *)currentTask;
    alarm->id = 0;
    
    insertKNodeToEnd(&alarms,(KNode *)alarm);
}

void setDelayOfAlarm(KAlarm * alarm, UInt32 delay)
{
    alarm->reload = delay * 10;
}

void startAlarm(KAlarm * alarm)
{
    alarm->remaining = alarm->reload;
}

void waitAlarm(KAlarm * alarm)
{
    alarm->thread = (KThread *)currentTask;

    setTaskAsWaiting();

    alarm->remaining = alarm->reload;
}

#ifdef KERNEL_USE_KEVENT

static UInt16 kEventLastAlarmId = 1;

void enableEventOnAlarm(KAlarm *alarm, KEventRegister *manager, KEventCallback callback, UInt32 dataForCallback)
{
    alarm->id = kEventLastAlarmId;
    kEventLastAlarmId++;
        
    registerEvent( manager, KEVENT_ALARM_MASK | alarm->id , callback, dataForCallback);
}
#endif
