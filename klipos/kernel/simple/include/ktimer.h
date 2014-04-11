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
#ifndef KLIPOS_KERNEL_KTIMER_H
#define	KLIPOS_KERNEL_KTIMER_H

#ifdef	__cplusplus
extern "C" {
#endif

/** @brief Timer object */
typedef struct _ktimer_
{
    KLink*      next;       /**< pointer to the next timer */
    KLink*      prev;       /**< pointer to the previous timer */
    int32_t     remaining;  /**< time remaining before fireup this timer */
    int32_t     reload;     /**< time to be reloaded */
    KTask*      task;       /**< timer's task */
} KTimer;


#define MS_TO_US(timeInMs)              (timeInMs * 1000)
#define SECOND_TO_US(timeInSecond)      (MS_TO_US(timeInSecond)*1000)

/** Initialize a timer for the task
 * 
 * @param timer         Pointer to an allocated timer
 * @param delayInUs     Delay before time is fired up
 * @param task          Timer wakeup this task
 */
extern void initTimer(KTimer* timer, uint32_t delayInUs, KTask* task);


#ifdef	__cplusplus
}
#endif

#endif	/* KTIME_H */

