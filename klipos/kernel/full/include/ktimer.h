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
#ifndef KLIPOS_KERNEL_TIMER_H
#define KLIPOS_KERNEL_TIMER_H

/** @brief Alarm object
 */
typedef struct _kalarm_
{
    KLink *     next;       /**< pointer to the next alarm */
    KLink *     prev;       /**< pointer to the previous alarm*/
    KThread *   thread;     /**< thread that receive this alarm */
    uint32_t      remaining;  /**< time remaining before alarm */
    uint32_t      reload;     /**< time to be reloaded */
    uint16_t      id;         /**< alarm's id for event post/get, 0 if it's not an event */
} KAlarm;


/** @brief Create a new alarm object.
 *
 * @param delay     in ms
 * @param A new alarm object.
 */
extern void initAlarm(KAlarm *alarm, uint32_t delay);

/** @brief Start the alarm.
 *
 * @param alarm     The alarm to start.
 */
extern void startAlarm(KAlarm * alarm);

/** @brief Wait the alarm.
 *
 * @param alarm     The alarm.
 */
extern void waitAlarm(KAlarm * alarm);


/** @brief Wait some delays...
 *
 * @param delay     Delay to wait in ms, between 1 and 6500.
 */
extern void waitMs(uint32_t delay);

extern void wait100Us(uint32_t delay);

extern void setDelayOfAlarm(KAlarm * alarm, uint32_t delay);

//WARNING Alarm is not started !
extern void enableEventOnAlarm(KAlarm *alarm, KEventManager *manager, KEventCallback callback, uint32_t dataForCallback);

#endif
