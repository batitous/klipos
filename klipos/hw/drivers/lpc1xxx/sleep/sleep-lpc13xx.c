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



//-------------------------- public functions

void setMcuToSleep(SLEEPMODE mode)
{
    if(SLEEP_DEFAULT==mode)
    {
        // Sleep mode:
        // PCON.DPDEN bit 1 = 0
        // SCR.SLEEDEEP bit 2 = 0
        // WFI
        // Sleep mode exit: any IRQ enabled
        
        CLRBIT(LPC_PMU->PCON,1); //PCON.DPDEN bit 1 = 0
        SETBIT(LPC_PMU->PCON,11); //Clear the Deep power-down flag
        CLRBIT(SCB->SCR,2);
        __WFI();
    }
    else if(SLEEP_DEEP==mode)
    {
        // Deep-sleep mode:
        // PCON.DPDEN bit 1 = 0
        // set MAINCLKSEL to IRC
        // set PDAWAKECFG for wakeup

        // external pins used: see start logic register and enable start logic IRQ
        // pin: PIO0_0 to PIO0_11, PIO1_0 to PIO1_11 and PIO2_0 to PIO2_7
        // Enable register pin : STARTERP0
        // 

        // disable all peripherals SYSAHBCLKCTRL
        // SCR.SLEEPDEEP bit 2 = 1
        // WFI

        // Deep-sleep mode exit: GPIO IRQ, RTC alarm, Watchdog timeout, USB
        
        // Use internal clock for the main clock
        LPC_SYSCON->MAINCLKSEL    = 0;

        // Update main clock selection
        LPC_SYSCON->MAINCLKUEN    = 1;
        LPC_SYSCON->MAINCLKUEN    = 0;
        LPC_SYSCON->MAINCLKUEN    = 1;

        // Wait main clock
        while ( !(LPC_SYSCON->MAINCLKUEN & BIT(0)) );

        
        // Clear deep sleep flag
//        SETBIT(LPC_PMU->PCON,8);
        
        // Clear the deep power down flag
        SETBIT(LPC_PMU->PCON,11);
        CLRBIT(LPC_PMU->PCON,1);
        
        // Turn off Watchdog and brown out detector (decrease consumption)
        LPC_SYSCON->PDSLEEPCFG |= 0x00000FFF;
        
        // Select the peripheral to be powered when wakeup
        LPC_SYSCON->PDAWAKECFG = LPC_SYSCON->PDRUNCFG;
        
        // Initialize the wakeup source
        initWakeUp();
        
        // Set Deep Sleep mode
        SETBIT(SCB->SCR,2);
        
        __WFI();
    }
    else if(SLEEP_DEEP_POWERDOWN==mode)
    {
        // We can wakeup only on the Wakeup pin AD5 
        
        // bref j'ai pas vu de difference de consommation 
        // entre le slee deep et le sleep deep powerdown
        
        // todo trouver le machin qui consomme ?
        
        SETBIT(LPC_PMU->PCON,1);
      
        //setIOInLowPowerMode();
        
       // set IRCOUT_PD & IRC_PD bits to 0 (PDRUNCFG Register)  
       // Set bits in PDRUNCFG to power down all perihphics except Flash and BOD powered  
       LPC_SYSCON->PDRUNCFG=0xEDFC; 
       LPC_SYSCON->SYSAHBCLKCTRL = 0;
       
       CLRBIT(LPC_SYSCON->SYSAHBCLKCTRL,5);
       CLRBIT(LPC_SYSCON->SYSAHBCLKCTRL,6);
       CLRBIT(LPC_SYSCON->SYSAHBCLKCTRL,7);
       CLRBIT(LPC_SYSCON->SYSAHBCLKCTRL,11);
       CLRBIT(LPC_SYSCON->SYSAHBCLKCTRL,13);
       CLRBIT(LPC_SYSCON->SYSAHBCLKCTRL,14);
    
       //Write 1 to SLEEPDEEP bit SCR Register
        SETBIT(SCB->SCR,2);
        
        __WFI();
    }
    
    
}

