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
#ifndef KLIPOS_KERNEL_THREAD_H
#define KLIPOS_KERNEL_THREAD_H

#define THREAD_CPU_MINIMUM     1        /**< lowest cpu request (don't use it...) */
#define THREAD_CPU_MAXIMUM     255      /**< highest cpu request */

#define THREAD_PRIORITY_MIN     1       /**< lowest scheduler priority (don't use it...) */
#define THREAD_PRIORITY_MAX     255     /**< highest scheduler priority */


/** @brief Kernel thread object
 *
 */
typedef struct _kernel_thread_
{
    KLink *     next;       /**< pointer to the next thread */
    KLink *     prev;       /**< pointer to the previous thread */
    UInt32 *    stack;      /**< thread stack */
    UInt32      waiting;    /**< remaining time to wait for this thread */
    UInt8       quantum;    /**< current quantum of task's scheduler */
    UInt8       cpuRequest; /**< cpu time */
    UInt8       priority;   /**< priority */
    UInt8       isReady;    /**< is this thread in the ready task list ? */
    
#ifdef KERNEL_USE_DEBUG
    UInt32      cpuUsage;   /**< cpu used by the thread */
    UInt32 *    stackBegin; /**< address of stack */
    UInt32      stackUsage; /**< stack used by thread */
#endif
    
} KThread;


/** @brief Create a new thread.
 *
 * @param userCode      Pointer to a function.
 * @param stackSize     Size of stack for this thread.
 * @param cpuTime       Cpu time requested.
 * @param priority      Thread priority.
 * @return
 */
extern void initThread( KThread *thread, void (*userCode)(void), UInt8 *stack, UInt32 stackSize, UInt8 cpuTime, UInt8 priority);


#endif
