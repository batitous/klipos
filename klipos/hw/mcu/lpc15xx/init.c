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
#include "../include/mcu/lpc1549.h"
#include "../include/types.h"
#include "../include/utils.h"

//
// lpc1549 mcu boot processor code
//



//this code is called at cpu reset: don't call it directly!
void initLowLevelCpu(void)
{
    uint32_t i;

        
    //====== CONFIGURE CLOCK & OSCILLATOR ====//

    // Power up system oscillator
    CLRBIT(LPC_SYSCON->PDRUNCFG,22); //system oscillator power on
    
    CLRBIT(LPC_SYSCON->SYSOSCCTRL,0);
  
    for (i = 0; i < 200; i++)
    {
        __NOP();
    }
    
    // Use IRC system oscillator
    LPC_SYSCON->SYSPLLCLKSEL = 0 ;
        
    // Use external oscillator
//    LPC_SYSCON->SYSPLLCLKSEL = 1 ;
        
    
    // Compute M :
    //
    // M = CPU / OSC
    // M = 72MHz / 12MHz
    
    // Compute P :
    //
    // FCC0 = 2 x P x 72MHz AND 156MHz < FCC0 < 320MHz
    //
    // P = 2
    // FCC0 = 2 x 2 x 72MHz = 288MHz
    //
    // MUST SET M-1 AND P-1
    
    // Set system pll clock value
    LPC_SYSCON->SYSPLLCTRL = BITS(0,5) | BITS(6,1);
    
    while (!(LPC_SYSCON->SYSPLLSTAT & BIT(0)) );
    
    // Use system pll clock out for the main clock
    LPC_SYSCON->MAINCLKSELB    = 0x2;
    
    
    //====== Peripheral clock ====//
    
    // System clock divider : 
    // divide the main clock for the core, memory and peripheral
    LPC_SYSCON->SYSAHBCLKDIV  = 1;
     
}
