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


#define CPHA    7
#define CPOL    6

#define SSE     1

void initSpi(void)
{        
    // de assert reset spi line
    SETBIT(LPC_SYSCON->PRESETCTRL,0);
  
    // enable spi0
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,11);
    
        
    // MOSI GPIO0_9
    SETBIT(LPC_IOCON->PIO0_9,0);
    
    // MISO GPIO0_8
    SETBIT(LPC_IOCON->PIO0_8,0);
    
    // SCK GPIO1_29
#ifdef MCU_IS_LPC1315
    //SETBIT(LPC_IOCON->PIO1_29,0); // bridge & drone prototype
    SETBIT(LPC_IOCON->SWCLK_PIO0_10,1); // drone hardware v1.0
#else
    SETBIT(LPC_IOCON->PIO2_11,0);
#endif
    
    LPC_SYSCON->SSP0CLKDIV = 1;
    
    LPC_SSP0->CR0 = 0x7;
    
    CLRBIT(LPC_SSP0->CR0,CPOL);
    CLRBIT(LPC_SSP0->CR0,CPHA);

    // clock : PCLK / CPSR = 72MHz / 12MHz
    LPC_SSP0->CPSR = 8;
    
    
    // enable ssp0
    SETBIT(LPC_SSP0->CR1,SSE); 
}



UInt8 sendByteToSpi(UInt8 outgoing)
{
    UInt8 incoming;
    
    while ((LPC_SSP0->SR & (0x2 | 0x10)) != 0x2);
    LPC_SSP0->DR = outgoing;

    while ( (LPC_SSP0->SR & (0x10|0x4)) != 0x4 );
    incoming = LPC_SSP0->DR;
    
    return incoming;
}


void sendBufferToSpi(UInt8 * buffer, UInt32 length)
{
    UInt32 i;
    for(i=0; i<length; i++)
    {
        sendByteToSpi(buffer[i]);
    }
}


UInt8 getByteFromSpi(void)
{
    return sendByteToSpi(0x00);
}

void getBufferFromSpi(UInt8 * buffer, UInt32 size)
{
    UInt32 i;
    for (i=0; i<size; i++)
    {
        buffer[i] = getByteFromSpi();
    }
}
