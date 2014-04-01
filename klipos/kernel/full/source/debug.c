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
#include "../../common/include/kmemory.h"
#include "../include/kthread.h"
#include "../include/kernel.h"
#include "../include/kernel-private.h"


void dumpKernel(void)
{
//    uint32_t total = 0;
    uint32_t percent = 0;
    KThread * thread = (KThread *)(tasksReady.next);

    printf("[%6d][ Dump Kernel State: current thread %x ]\r\n", tickOfKernel, currentTask);
/*    while( thread != (KThread *)&tasksReady)
    {
        total += thread->cpuUsage;
        thread = thread->next;
    }

    thread = (KThread *)(tasksWaiting.next);
    while( thread != (KThread *)&tasksWaiting)
    {
        total += thread->cpuUsage;
        thread = thread->next;
    }
*/
    thread = (KThread *)(tasksReady.next);
    printf("Thread     Stack     Priority Quantum     Cpu used   Stack Used\r\n");
    while( thread != (KThread *)&tasksReady)
    {
        percent = (thread->cpuUsage); // * 100)/ total;
        printf("%x   %4x   %3d       %2d (%3d)     %5d    %2d\r\n", thread, thread->stack, thread->priority, thread->quantum,thread->cpuRequest, percent, thread->stackUsage);

        thread = thread->next;
    }

    thread = (KThread *)(tasksWaiting.next);
    while( thread != (KThread *)&tasksWaiting)
    {
        percent = (thread->cpuUsage);// * 100)/ total;
        printf("%x   %4x   %3d       %2d (%3d)    %5d    %2d -> waiting\r\n", thread, thread->stack, thread->priority, thread->quantum, thread->cpuRequest, percent,thread->stackUsage);

        thread = thread->next;
    }

    thread = (KThread *)(tasksBlocked.next);
    while( thread != (KThread *)&tasksBlocked)
    {
        percent = (thread->cpuUsage);// * 100)/ total;
        printf("%x   %4x   %3d       %2d (%3d)    %5d    %2d -> blocked\r\n", thread, thread->stack, thread->priority, thread->quantum, thread->cpuRequest, percent,thread->stackUsage);

        thread = thread->next;
    }
}
