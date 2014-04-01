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
#include "../../../include/libs-klipos.h"


//-------------------------- private variables:


// Frequency is computed has : F = 600 kHz / (2*(1+Divider))
// F = 600 kHz / (2(1+15)) = 18750 Hz
#define WATCHDOG_D      15
#define WATCHDOG_F      1

#define WATCHDOG_FREQ   18750

// Watchdog has a minimum value of 256 and a prescaler value of 4
#define HZ_TO_MS(f)     ((4*256*1000)/f)

//-------------------------- public functions:


void initWatchdog(uint32_t timeInMs)
{
    //todo for lpc1342 check this registers :
    // WDTCLKSEL 
    // WDTCLKUEN
    // WDTCLKDIV
    
    // power the watchdog interface
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,15);
    
    // enable the clock source
    CLRBIT(LPC_SYSCON->PDRUNCFG,6);
    
    // set clock
    LPC_SYSCON->WDTOSCCTRL = BITS(0, WATCHDOG_D) | BITS(5, WATCHDOG_F);

    // select watchdog oscillator as clock source
    SETBIT(LPC_WDT->CLKSEL,0);

    int32_t t = (timeInMs * 256) / HZ_TO_MS(WATCHDOG_FREQ);
    
    if ( t < 0xFF)
    {
        t = 0xFF;
    }
    
    LPC_WDT->TC = t;    
    
    // reset the microcontroller if failed to feed the watchdog
    SETBIT(LPC_WDT->MOD, 1);
    
    // enable !
    SETBIT(LPC_WDT->MOD, 0);
    
}

void feedTheWatchdog(void)
{
    LPC_WDT->FEED = 0xAA;
    LPC_WDT->FEED = 0x55;
}
