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
#ifndef LIB_HW_TIMER_H
#define LIB_HW_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif


typedef enum _timer_enum_
{
    TIMER0 = 0,
    TIMER1 = 1,
    TIMER2 = 2,
    TIMER3 = 3
} TIMER;


typedef struct _timer_
{
    LPC_TMR_TypeDef*    t;
    bool                enable;
} Timer;

typedef void (*TimerIrqCallback)(void);

extern void setTimer0Callback(TimerIrqCallback c);
extern void setTimer1Callback(TimerIrqCallback c);

/** Initialize the specified timer interrupt to be fired
 * 
 * By default, the timer is disable, you have to enable manually the timer with enableTimer32
 * 
 * @param timer
 * @param timerSelected         Timer
 * @param waitInUs              Time in microseconds
 * @return False if error
 */
extern Bool initTimer32(Timer* timer, TIMER timerSelected, UInt32 waitInUs);

/** Set the time of the specified timer
 * 
 * @param timer
 * @param waitInUs              New time in microseconds
 */
extern void setTimer32(Timer* timer, UInt32 waitInUs);

/** Enable or disable a timer
 * 
 * @param timer
 */
extern void enableTimer32(Timer* timer);


/** Wait some time
 * 
 * @param waitInUs      Time in microseconds
 */
extern void waitUsPrecise(TIMER timerSelected, UInt32 waitInUs);


#ifdef __cplusplus
 }
#endif

#endif
