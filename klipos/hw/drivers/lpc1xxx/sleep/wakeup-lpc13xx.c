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
#include "../include/libs-klipos.h"


extern void initLowLevelCpu(void);

//-------------------------- Wakeup pin configuration

// see lpc13xx.h to get WAKEUP_IRQ number

#ifdef HARDWARE_IS_LPC13_DEV
/* hardware is the lpc13xx dev board */
/* pin 3.3 */
#       define WAKEUP_PIN              7        /**< bit number in register */
#       define WAKEUP_START_REGISTER   1        /**< register number (0 or 1) */
#       define WAKEUP_IRQ              39        /**< irq number */
#endif


#ifdef HARDWARE_IS_IRBEACON_EMITTER
/* hardware is the lpc13xx dev board */
/* pin 3.3 */
#       define WAKEUP_PIN              12        /**< bit number in register */
#       define WAKEUP_START_REGISTER   0        /**< register number (0 or 1) */
#       define WAKEUP_IRQ              12        /**< irq number , see lpc13xx.h */
#endif



//-------------------------- Macro

// We must use the CONCAT macro in all the macro to let the preprocessor replace parameters
//
// /*!*\ Warning /*!*\ we have to use this macro in a macro of macro to replace correctly the parameters
//
#define CONCAT_A_B(a,b)            a ## b
#define CONCAT_A_B_C(a,b,c)        a ## b ## c


#define STARTLOGIC(reg,pin)        CONCAT_A_B(reg,pin)
#define STARTLOGIC_CLR(reg,pin)    CONCAT_A_B_C(reg,pin,CLR)


#define _WAKEUP_IRQ_HANDLER_(pin)  CONCAT_A_B_C(WAKEUP,pin,_IRQn_Handler)
#define WAKEUP_IRQ_HANDLER         _WAKEUP_IRQ_HANDLER_(WAKEUP_IRQ)

#define _WAKEUP_IRQ_NUMBER(pin)    CONCAT_A_B_C(WAKEUP,pin,_IRQn)
#define WAKEUP_IRQ_NUMBER          _WAKEUP_IRQ_NUMBER(WAKEUP_IRQ)


// in next comments, _xXx_ is the WAKEUP_START_REGISTER parameter

// Macro for LPC_SYSCON->STARTRSRP_xXx_CLR register
#define STARTRSRP_CLR              STARTLOGIC_CLR(LPC_SYSCON->STARTRSRP,WAKEUP_START_REGISTER)

// Macro for LPC_SYSCON->STARTAPRP_xXx_
#define START_APRP                 STARTLOGIC(LPC_SYSCON->STARTAPRP,WAKEUP_START_REGISTER)

// Macro for LPC_SYSCON->STARTERP_xXx_
#define START_ERP                  STARTLOGIC(LPC_SYSCON->STARTERP,WAKEUP_START_REGISTER)


//-------------------------- private functions


void WAKEUP_IRQn_Handler(void)
{   
    // Reset the start logic
    SETBIT(STARTRSRP_CLR,WAKEUP_PIN);
        
    
    // todo ?
    // wait button release
    //while(GetGpioValue(GPIO3_3)==0);
    
    
    // Clear deep sleep flag
/*    SETBIT(LPC_PMU->PCON,8);
    SETBIT(LPC_PMU->PCON,11);
    CLRBIT(SCB->SCR,2);
*/
        
    // Initialize cpu clock
    initLowLevelCpu();
    
    
    // Disable the wakeup pin IRQ
    NVIC_DisableIRQ(WAKEUP_IRQ_NUMBER);
    
    // Disable start logic on this pin
    CLRBIT(START_ERP,WAKEUP_PIN);
    
    
    __NOP();
}


//-------------------------- public functions


void initWakeUp(void)
{
     // Set Falling edge on start logic
     CLRBIT(START_APRP, WAKEUP_PIN);

     // Reset the start logic
     SETBIT(STARTRSRP_CLR,WAKEUP_PIN);

     // Enable start logic
     SETBIT(START_ERP,WAKEUP_PIN);
     
     // Enable wakeup IRQ

     NVIC_ClearPendingIRQ(WAKEUP_IRQ_NUMBER);
     NVIC_EnableIRQ(WAKEUP_IRQ_NUMBER);

     
     //todo SYSAHBCLKCTRL disable peripheral not needed ?
     
     // todo set io mode ?
     //        setIOInLowPowerMode();
 
}



/* code take from nxp app note
void setIOInLowPowerMode(void)
{

	// Configure all IOs as GPIO w/o pull-up & pull-down resistors
	LPC_IOCON->PIO2_6			= 0xC0;
	LPC_IOCON->PIO2_0			= 0xC0;
	LPC_IOCON->RESET_PIO0_0 	= 0xC1;      // RST_BOOT/P0_0

	LPC_IOCON->PIO1_8			= 0xC0;
	LPC_IOCON->PIO0_2			= 0xC0;      // SSEL/CT16B0_CAP0	//Trigger input

	LPC_IOCON->PIO2_7			= 0xC0;
	LPC_IOCON->PIO2_8			= 0xC0;
	LPC_IOCON->PIO2_1			= 0xC0;
	LPC_IOCON->PIO0_3			= 0xC0;      // USB VBUS
	LPC_IOCON->PIO0_4			= 0xC0;      // I2C_SCL, no pull-up, inactive
	LPC_IOCON->PIO0_5			= 0xC0;      // I2C_SDA, no pull-up, inactive
	LPC_IOCON->PIO1_9			= 0xC0;      // CT16B1_MAT0
	LPC_IOCON->PIO3_4			= 0xC0;

	LPC_IOCON->PIO2_4			= 0xC0;
	LPC_IOCON->PIO2_5			= 0xC0;
	LPC_IOCON->PIO3_5			= 0xC0;
	LPC_IOCON->PIO0_6			= 0xC0;      // USB SoftConnect
	LPC_IOCON->PIO0_7			= 0xC0;
	LPC_IOCON->PIO2_9			= 0xC0;
	LPC_IOCON->PIO2_10			= 0xC0;
	LPC_IOCON->PIO2_2			= 0xC0;

	LPC_IOCON->PIO0_8			= 0xC0;		// SSP_MISO/CT16B0_MAT0/TRACE_CLK
	LPC_IOCON->PIO0_9			= 0xC0;		// SSP_MOSI/CT16B0_MAT1/TRACE_SWV
	LPC_IOCON->JTAG_TCK_PIO0_10	= 0xC1;		// JTAG_CLK/P0_10/SSP_CLK/CT16B0_MAT2
	LPC_IOCON->PIO1_10			= 0xC0;		// ADCIN6/CT16B1_MAT1
	LPC_IOCON->PIO2_11			= 0xC0;
	LPC_IOCON->JTAG_TDI_PIO0_11	= 0xC1;		// JTAG_TDI/P0_11/ADCIN0/CT32B0_MAT3
	LPC_IOCON->JTAG_TMS_PIO1_0  = 0xC1;		// JTAG_TMS/P1_0/ADCIN1/CT32B1_CAP0
	LPC_IOCON->JTAG_TDO_PIO1_1  = 0xC1;		// JTAG_TDO/P1_1/ADCIN2/CT32B1_MAT0

	LPC_IOCON->JTAG_nTRST_PIO1_2 = 0xC1;	// JTAG_TRST/P1_2/ADCIN3/CT32B1_MAT1
	LPC_IOCON->PIO3_0			= 0xC0;
	LPC_IOCON->PIO3_1			= 0xC0;
	LPC_IOCON->PIO2_3			= 0xC0;
	LPC_IOCON->ARM_SWDIO_PIO1_3	= 0xC1;		// ARM_SWD/P1_3/ADCIN4/CT32B1_MAT2
	LPC_IOCON->PIO1_4			= 0xC0;		// ADCIN5/CT32B1_MAT3/WAKEUP
	LPC_IOCON->PIO1_11			= 0xC0;		// ADCIN7
	LPC_IOCON->PIO3_2			= 0xC0;

	LPC_IOCON->PIO1_5			= 0xC0;      // UART_DIR/CT32B0_CAP0
	LPC_IOCON->PIO1_6			= 0xC0;      // UART_RXD/CT32B0_MAT0
	LPC_IOCON->PIO1_7			= 0xC0;      // UART_TXD/CT32B0_MAT1
	LPC_IOCON->PIO3_3			= 0xC0;

	//LPC_GPIO1->DIR = ~(1<<4);	//WAKEUP Pin input only
	
        LPC_GPIO2->DIR = 0xFFFFFFFF;
	LPC_GPIO3->DIR = 0xFFFFFFFF;

	// GPIO outputs to LOW
	LPC_GPIO0->DATA  = 0;
	LPC_GPIO1->DATA  = 0;
	LPC_GPIO2->DATA  = 0;
	LPC_GPIO3->DATA  = 0;

	return;
}
*/

