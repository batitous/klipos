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
#include "../../../include/libs-klipos.h"


//-------------------------- private variables:


#define WATCHDOG_FREQ   (503000)

// Watchdog has a minimum value of 256 and a prescaler value of 4
#define HZ_TO_MS(f)     ((4*256*1000)/f)

//-------------------------- public functions:


void initWatchdog(uint32_t timeInMs)
{
    // power the watchdog interface
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL[0],22);
    
    // enable the clock source
    CLRBIT(LPC_SYSCON->PDRUNCFG,20);
    
    // disable watchdog
    LPC_WWDT->MOD       = 0;
    LPC_WWDT->TC        = 0xFF;
    LPC_WWDT->WARNINT   = 0x3FF;
    LPC_WWDT->WINDOW    = 0xFFFFFF;

    
    int32_t t = (timeInMs * 256) / HZ_TO_MS(WATCHDOG_FREQ);
    
    if ( t < 0xFF)
    {
        t = 0xFF;
    }
    
    LPC_WWDT->TC = t;    
    
    // reset the microcontroller if failed to feed the watchdog
    SETBIT(LPC_WWDT->MOD, 1);
    
    // enable !
    SETBIT(LPC_WWDT->MOD, 0);
    
    LPC_WWDT->FEED = 0xAA;
    LPC_WWDT->FEED = 0x55;
}

void feedTheWatchdog(void)
{
    LPC_WWDT->FEED = 0xAA;
    LPC_WWDT->FEED = 0x55;
}
