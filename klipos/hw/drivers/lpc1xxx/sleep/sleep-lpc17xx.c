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
#include "../include/libs-hardware.h"


void setMcuToSleep(SLEEPMODE mode)
{
    // power down not implemented
    
    if(SLEEP_DEEP_POWERDOWN==mode)
    {
        // deep power down sleep
        
        SETBIT(SCB->SCR,2);
        
        // power down
        SETBIT(LPC_SC->PCON,0);
        // deep power down
        SETBIT(LPC_SC->PCON,1);
        
        //fully deactivate brown out
        SETBIT(LPC_SC->PCON,2);
        SETBIT(LPC_SC->PCON,3);
        
        __WFI();
    }
    else if (SLEEP_DEEP==mode)   
    {
        //deep sleep
        LPC_SC->PCON = 0x00;
        
       //fully deactivate brown out 
       SETBIT(LPC_SC->PCON,2);
       SETBIT(LPC_SC->PCON,3);
       
       //Enable sleepdeep 
       SETBIT(SCB->SCR,2);
        
      __WFI();
    }
    else
    {
        // default sleep
        LPC_SC->PCON = 0;
        SCB->SCR = 0;
        
       __WFI();
    }
}
