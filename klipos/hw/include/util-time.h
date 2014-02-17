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
#ifndef LIB_HW_UTIL_TIME_H
#define	LIB_HW_UTIL_TIME_H

#ifdef	__cplusplus
extern "C" {
#endif

// Get ticks value from time in microseconds
#define GET_TICK_FROM_US(timeInUs) ((KERNEL_CPU_FREQ/1000)*(timeInUs) -1)
    
    
// Get time in microseconds from ticks value
#define GET_US_FROM_TICK(ticks)    (1+((ticks*1000) / KERNEL_CPU_FREQ))
    
    
/** Wait some times
 * 
 * This functions don't use any timer or kernel code
 * DONT USE THIS FUNCTION FOR PRECISE DELAY !
 * 
 * @param delay
 */
extern void  waitSomeTimeInUs(UInt32  delay);


/** Initialize the systick timer to fire up an interrupt at timeInUs
 * 
 * DONT USE THIS FUNCTION WITH KERNEL ENABLE !
 * 
 * @param timeInUs
 */
extern void initSystickTimer(UInt32 timeInUs);

 
/** Get the number of interrupt fired up by the systick timer
 *
 * @return Number of interrupt fired up.
 */
extern UInt32 getSystickCounter(void);

/** Get the current value in microseconds of the systick timer
 * 
 * @return This value is between [0 - time initialized in initSystickTimer].
 */
extern UInt32 getSysTickCurrentVal(void);



#ifdef	__cplusplus
}
#endif

#endif	/* UTIL_TIME_H */

