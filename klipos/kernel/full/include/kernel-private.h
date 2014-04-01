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
#ifndef KLIPOS_KERNEL_PRIVATE_H
#define KLIPOS_KERNEL_PRIVATE_H

/** this files include all the private functions and objects of the kernel.
*/


/** @brief Set task as ready and run this task.
 * must be use inside the kernel !
 */
extern void kernelSetTaskAsReady(KThread * thread );

/** @brief Same as previous, but inside an interrupt.
 */
extern void irqSetTaskAsReady(KThread * thread);

/** @brief Set task as ready and execute immediately this task.
 *
 * @warning the thread must be in the wait list !
 *
 * @warning don't use inside the kernel or an interrupt !
 *
 * @param thread        A thread.
 */
extern void setTaskAsReady(KThread * thread);

/** @brief Set the current task as waiting and schedule a new task immediately.
 */
extern void setTaskAsWaiting(void);

/** @brief Set the current task as blocked and schedule a new task immediately.
 */
extern void setTaskAsBlocked(void);

extern void initKAlarm(void);
extern void manageKTimer(void);


extern KList tasksWaiting;
extern KList tasksBlocked;
extern KList tasksReady;
extern volatile KThread * currentTask;
extern volatile uint32_t tickOfKernel;

#endif
