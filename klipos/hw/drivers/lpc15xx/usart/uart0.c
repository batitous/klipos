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


//--------------------- private variables:

#ifndef UART_BUFFER_SIZE
#       define UART_BUFFER_SIZE    64
#endif


static KIOStream uartStream;
static uint8_t uartBuffer[UART_BUFFER_SIZE];

static const Uart uart0 = { 
    getByteFromUart0, 
    getBufferFromUart0, 
    sendByteToUart0, 
    sendBufferToUart0,
    getByteAvailableOnUart0
};

#ifdef FIRMWARE_USE_KERNEL_SIMPLE
static KTask*   uartTask;
#endif

//--------------------- private functions:

void UART0_IRQHandler(void)
{
    uint8_t data;
    
    //Check if interrupt is pending
    if ( (LPC_USART0->STAT & BIT(0)) != 0 )
    {
        data = LPC_USART0->RXDATA;
        writeByteToIOStream(&uartStream,data);
            
#ifdef FIRMWARE_USE_KERNEL_FULL
        irqWakeUpTaskFromIOStream(&uartStream);
#endif
            
#ifdef FIRMWARE_USE_KERNEL_SIMPLE
        postEventToTask(uartTask,(uint32_t)data);
#endif

    }
}


//--------------------- public functions:


const Uart * initUart0(void)
{
    initIOStream(&uartStream,uartBuffer,UART_BUFFER_SIZE);
    
    LPC_SYSCON->UARTCLKDIV = 1;
    LPC_SYSCTL->FRGCTRL = 0;
    
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL[1],17);
    SETBIT(LPC_SYSCON->PRESETCTRL[1], 17);
    CLRBIT(LPC_SYSCON->PRESETCTRL[1], 17);
    
    // 8 bit, 1 stop, no parity
    SETBIT(LPC_USART0->CFG,2);
    
    uint32_t baudRateGenerator;
    baudRateGenerator = (12000000) / (16 * 115200);
        
    LPC_USART0->BRG = baudRateGenerator - 1;
    
    // enable uart
    SETBIT(LPC_USART0->CFG,0);
    
    // enable irq on rx
    SETBIT(LPC_USART0->INTENSET, 0);
    
    NVIC_EnableIRQ(UART0_IRQn);
    
    return &uart0;
}

void sendByteToUart0(uint8_t byte)
{
    while( (LPC_USART0->STAT & BIT(2)) == 0 );
    
    LPC_USART0->TXDATA=byte;
}

void sendBufferToUart0(uint8_t * Buffer,uint32_t Count)
{
    uint32_t i;
    
    for(i=0;i<Count;i++)
    {
        sendByteToUart0(Buffer[i]);
    }
}

uint32_t getBufferFromUart0(uint8_t * buffer, uint32_t len)
{
    return readBufferFromIOStream(&uartStream, buffer, len);
}

bool getByteFromUart0(uint8_t *data)
{
    return readByteFromIOStream(&uartStream, data);
}

uint32_t getByteAvailableOnUart0(void)
{
    return getByteAvailableFromIOStream(&uartStream);
}

#ifdef FIRMWARE_USE_KERNEL_FULL

void waitDataFromUart0(void)
{
    waitDataFromIOStream(&uartStream);
}

#endif

#ifdef FIRMWARE_USE_KERNEL_SIMPLE

void setTaskOnUart0(KTask* t)
{
    uartTask = t;
}

#endif
