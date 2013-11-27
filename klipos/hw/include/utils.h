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
#ifndef LIBS_HW_UTILS_H
#define LIBS_HW_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif


// set value at specified position
#define BITS(position,value) 	((value)<<(position))

// set 1 at specified position
#define BIT(position) 		(1<<(position))

// set 1 into register at position
#define SETBIT(reg,position)    reg |= (1<<((UInt32)position))

// clear one bit of register at position
#define CLRBIT(reg,position)  reg &= ~(1<<((UInt32)position))

// clear multiple bits of register
#define CLRBITS(reg,mask)     reg &= ~(mask)
    
    
// get tick from time in microseconds
#define GET_TICK_FROM_US(timeInUs) ((KERNEL_CPU_FREQ/1000)*(timeInUs) -1)
    
// get time in microseconds from ticks
#define GET_US_FROM_TICK(ticks)    (((ticks+1)*1000) / KERNEL_CPU_FREQ)

    
// software delay : this functions don't use any timer or kernel code
// DONT USE THIS FUNCTION FOR PRECISE DELAY !
extern void  waitSomeTimeInUs(UInt32  delay);


extern void initSystickTimer(UInt32 timeInUs);


extern UInt32 getSystickCounter(void);

extern UInt32 getSysTickCurrentVal(void);


#ifdef __cplusplus
 }
#endif

#endif
