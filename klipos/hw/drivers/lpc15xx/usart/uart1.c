/*
 The MIT License (MIT)
 
 Copyright (c) 2015 Baptiste Burles
 
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


//--------------------- private variables:

#define UART_CLOCK    (KERNEL_CPU_FREQ*1000)

#ifndef UART_BUFFER_SIZE
#       define UART_BUFFER_SIZE    64
#endif


static KIOStream uart1Stream;
static uint8_t uart1Buffer[UART_BUFFER_SIZE];
static KTask*   uart1Task;

//--------------------- private functions:

void UART1_IRQHandler(void)
{
    uint8_t data;
    
    //Check if interrupt is pending
    if ( (LPC_USART1->STAT & BIT(0)) != 0 )
    {
        data = LPC_USART1->RXDATA;
        writeByteToIOStream(&uart1Stream,data);
            
        postEventToTask(uart1Task,(uint32_t)data);
    }
}

/*
void setUartClockRate(uint32_t rate, bool fEnable)
{
    uint32_t div, inclk;

    inclk = UART_CLOCK;

    div = inclk / rate;
    if (div == 0) 
    {
        div = 1;
    }

    LPC_SYSCON->UARTCLKDIV = div;

    if (fEnable!=false) 
    {
            uint32_t err;
            uint64_t uart_fra_multiplier;

            err = inclk - (rate * div);
            uart_fra_multiplier = ((uint64_t) err  * 256) / (uint64_t) (rate * div);

            // Enable fractional divider and set multiplier 
            LPC_SYSCTL->FRGCTRL = 0xFF | ((uart_fra_multiplier & 0xFF) << 8);
    }
    else 
    {
            // Disable fractional generator and use integer divider only 
            LPC_SYSCTL->FRGCTRL = 0;
    }

}

uint32_t getUartClockRate(void)
{
    uint64_t inclk;
    uint32_t div;

    div = (uint32_t) LPC_SYSCON->UARTCLKDIV;
    
    uint32_t mult, divmult;

    // Input clock into FRG block is the divided main system clock 
    inclk = (uint64_t) (UART_CLOCK / div);

    divmult = LPC_SYSCTL->FRGCTRL & 0xFFFF;
    if ((divmult & 0xFF) == 0xFF) 
    {
        // Fractional part is enabled, get multiplier
        mult = (divmult >> 8) & 0xFF;

        // Get fractional error
        inclk = (inclk * 256) / (uint64_t) (256 + mult);
    }

    return (uint32_t) inclk;
}*/

//--------------------- public functions:


void initUart1(void)
{
    initIOStream(&uart1Stream,uart1Buffer,UART_BUFFER_SIZE);
    
    LPC_SYSCON->UARTCLKDIV = 1;
    LPC_SYSCTL->FRGCTRL = 0;
    
//    setUartClockRate(UART_CLOCK,false);
    
    // enable uart clock and block
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL[1],18);
    
    SETBIT(LPC_SYSCON->PRESETCTRL[1], 18);
    CLRBIT(LPC_SYSCON->PRESETCTRL[1], 18);
    
    // 8 bit, 1 stop, no parity
    SETBIT(LPC_USART1->CFG,2);
    
    uint32_t baudRateGenerator = UART_CLOCK/*getUartClockRate()*/ / (16 * 115200);
        
    LPC_USART1->BRG = baudRateGenerator - 1;
    
    // enable uart
    SETBIT(LPC_USART1->CFG,0);
    
    // enable irq on rx
    SETBIT(LPC_USART1->INTENSET, 0);
    
    NVIC_EnableIRQ(UART1_IRQn);
    
}

void sendByteToUart1(uint8_t byte)
{
    while( (LPC_USART1->STAT & BIT(2)) == 0 );
    
    LPC_USART1->TXDATA=byte;
}

void sendBufferToUart1(uint8_t * Buffer,uint32_t Count)
{
    uint32_t i;
    
    for(i=0;i<Count;i++)
    {
        sendByteToUart1(Buffer[i]);
    }
}

uint32_t getBufferFromUart1(uint8_t * buffer, uint32_t len)
{
    return readBufferFromIOStream(&uart1Stream, buffer, len);
}

bool getByteFromUart1(uint8_t *data)
{
    return readByteFromIOStream(&uart1Stream, data);
}

uint32_t getByteAvailableOnUart1(void)
{
    return getByteAvailableFromIOStream(&uart1Stream);
}

void assignTaskOnUart1(KTask* t)
{
    uart1Task = t;
}
