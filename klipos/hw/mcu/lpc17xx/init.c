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
#include "../include/mcu/lpc17xx.h"
#include "../include/types.h"
#include "../include/utils.h"

//
// lpc17xx mcu boot processor code
//

//this code is called at cpu reset: don't call it directly!
void initLowLevelCpu(void)
{    
	//====== CONFIGURE CLOCK & OSCILLATOR ====//

	// Enable OSC for osc < 15 Mhz (olimex= 12MHz)
	// if osc > 15MHz set BIT(4);
       
#ifdef MCU_USE_INTERNAL_OSC
        // nothing to do
#else
        // enable main osc on XTAL1 XTAL2
        LPC_SC->SCS = BIT(5);
        
        // Wait for OSC ready
  	while( (LPC_SC->SCS & BIT(6))==0 );
        
#endif

  	// Disconnect & Disable PLL
	LPC_SC->PLL0CON = 0;
  	LPC_SC->PLL0FEED  = 0xAA;
  	LPC_SC->PLL0FEED  = 0x55;

        // Wait PLL disable
        while( (LPC_SC->PLL0STAT & (BIT(24)|BIT(25)) ) != 0 );
        
        // Set cpu clock:
	// PLL Settings at 300 MHz : set cpu at 100 MHz
        LPC_SC->CCLKCFG   = 2;
        
        // 384 MHz for CPU at 96 MHz
	//LPC_SC->CCLKCFG   = 3;

	// Set peripheral clock: 25 MHz for all, uart0 = 50 MHz
	// datasheet page 57
	LPC_SC->PCLKSEL0 = BITS(6,2);
	LPC_SC->PCLKSEL1 = 0;

	// Selects the main oscillator as a PLL clock source
#ifdef MCU_USE_INTERNAL_OSC
        LPC_SC->CLKSRCSEL = 0;
#else
        LPC_SC->CLKSRCSEL = 1;
#endif
        
        // Set PLL Settings:
        
#ifdef MCU_USE_INTERNAL_OSC
	
        // CPU Clock 96 MHz
        LPC_SC->PLL0CFG = BITS(16,2-1) | BITS(0,96-1);
#else
        // Values comes from olimex source code
        // N value at bit 16, M value at bit 0
	// M = 25 N = 2
        
        //12 MHz
        LPC_SC->PLL0CFG = BITS(16,2-1) | BITS(0,25-1);
        
        //10 MHz
        //LPC_SC->PLL0CFG = BITS(16,1) | BITS(0,15-1);
#endif
     
        LPC_SC->PLL0FEED  = 0xAA;
  	LPC_SC->PLL0FEED  = 0x55;
        
        // TODO set correct value in while
        while( (LPC_SC->PLL0STAT & 0x7FFF) != 24);
        
	// Enable PLL:
	LPC_SC->PLL0CON = 1;
        LPC_SC->PLL0FEED  = 0xAA;
	LPC_SC->PLL0FEED  = 0x55;
        
	// Wait for the PLL to achieve lock
	while( (LPC_SC->PLL0STAT & BIT(26)) ==0 );
               
	// Connect the PLL:
	LPC_SC->PLL0CON = 3;
	LPC_SC->PLL0FEED  = 0xAA;
  	LPC_SC->PLL0FEED  = 0x55;

  	// Wait status ready for PLLE and PLLC bits:
  	while( (LPC_SC->PLL0STAT & (BIT(24)|BIT(25)) ) == 0 );

         // Set usb clock:
        
        // baptiste 1.06.2012 test on prototype byc-v1
	LPC_SC->USBCLKCFG = 5;  //PLL0 divided by 6
        
        //LPC_USB->USBClkCtrl =   (1<<1) |   // Device clk enable
        //                        (1<<3) |   // Port select clk enable
        //                        (1<<4);   
        
        //while((LPC_USB->USBClkSt & ((1<<1) | (1<<3) | (1<<4))) != ((1<<1) | (1<<3) | (1<<4)));
        
        //LPC_USB->USBClkCtrl =   (1<<1) |   // Device clk enable
        //                        (1<<4);    // AHB clk enable

  	// FOR DEBUG ONLY: we can use P1.27 pin to see the clock output of cpu, usb, peripheral : datasheet page 66
  	// LPC_SC->CLKOUTSEL = ;

  	//====== CONFIGURE POWER MODE ====//

  	// power mode control
//  	LPC_SC->PCON = ; j'ai rien compris au datasheet page 61


  	// peripheral power control:
  	// WARNING by default, NOT ALL the peripheral are power up... datasheet page 63
  	// bref si un truc marche pas, voir ce truc!
  	//LPC_SC->PCONP |= 0x80000000; //0x80000000 -> bit 31 - USB


	//====== CONFIGURE FLASH MODULE ====//

	// Flash Access speed : values from datasheet page 70
	LPC_SC->FLASHCFG = 0x303A;

	//====== INTERRUPT ====//

	// by default, the vector table offset is at address 0
//	SCB->VTOR = 0x00000000 ;


}
