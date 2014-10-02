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
#if defined(MCU_IS_LPC15XX)
    uint32_t    t;
#else
    LPC_TMR_TypeDef*    t;
#endif
} Timer;

typedef void (*TimerIrqCallback)(void);


/** Initialize the specified timer interrupt to be fired
 * 
 * By default, the timer is disable, you have to enable manually the timer with enableTimer32
 * 
 * @param timer
 * @param timerSelected         Timer
 * @param waitInUs              Time in microseconds
 * @return false if error
 */
extern bool initTimer32(Timer* timer, TIMER timerSelected, uint32_t waitInUs);

/** Set the time of the specified timer
 * 
 * @param timer
 * @param waitInUs              New time in microseconds
 */
extern void setTimer32(Timer* timer, uint32_t waitInUs);

/** Enable the timer
 * 
 * @param timer
 */
extern void enableTimer32(Timer* timer);

/** Disable the timer
 * 
 * @param timer
 */
extern void disableTimer32(Timer* timer);

/** Is the timer enable ?
 * 
 * @param timer
 * @return true if timer enable
 */
extern bool isTimer32Enable(Timer* timer);

// Set callback for specified Timer
extern void setTimer32Callback(Timer* timer, TimerIrqCallback c);


/** Wait some time
 * 
 * Warning, it use the selected Timer32 !
 * 
 * @param timerSelected
 * @param waitInUs      Time in microseconds
 */
extern void waitUsPrecise(TIMER timerSelected, uint32_t waitInUs);


// Timer 16 bits
extern bool initTimer16(Timer* timer, TIMER timerSelected, uint32_t waitInUs);
extern void setTimer16(Timer* timer, uint32_t waitInUs);
extern void enableTimer16(Timer* timer);
extern void disableTimer16(Timer* timer);
extern bool isTimer16Enable(Timer* timer);
extern void setTimer16Callback(Timer* timer, TimerIrqCallback c);

// Repetitive Interrupt Timer 
extern void initTimerRit(uint32_t timeInUs);
extern uint32_t getTimerRitCounter(void);
extern bool isTimerRitOverflow(void);

#ifdef __cplusplus
 }
#endif

#endif
