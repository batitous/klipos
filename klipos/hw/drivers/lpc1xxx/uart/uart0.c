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


//--------------------- private configuration:

#ifdef MCU_IS_LPC1311

void setUartIoCon(void)
{
    CLRBITS(LPC_IOCON->PIO1_6,7);
    LPC_IOCON->PIO1_6 |= 1;
    
    CLRBITS(LPC_IOCON->PIO1_7,7);
    LPC_IOCON->PIO1_7 |= 1;
    
    powerOnUart0();
}
#endif

#ifdef MCU_IS_LPC1315

void setUartIoCon(void)
{
    CLRBITS(LPC_IOCON->PIO0_19,7);
    LPC_IOCON->PIO0_19 |= 1;
    
    CLRBITS(LPC_IOCON->PIO0_18,7);
    LPC_IOCON->PIO0_18 |= 1;
    
    powerOnUart0();
}
#endif

#ifdef MCU_IS_LPC13XX

//115200
#               define setBaudrate()    LPC_UART0->DLL = 39; LPC_UART0->DLM = 0;
//57600
//#               define setBaudrate()    LPC_UART0->DLL = 78; LPC_UART0->DLM = 0;
//38400
//#       define setBaudrate()    LPC_UART0->DLL = 117; LPC_UART0->DLM = 0;
#endif


#ifdef MCU_IS_LPC17XX

void setUartIoCon(void)
{
    // how to compute uart baudrate:
    //
    // uartbaudrate = PCLK / ( 16 x ( 256 x UART0_DLM + UART0_DLL ) )
    // with PCLK = 72MHz
    
    LPC_PINCON->PINSEL0  |= 0x50;
}

#       define setBaudrate()    LPC_UART0->DLL = 27; LPC_UART0->DLM = 0;

#endif

#ifndef UART_BUFFER_SIZE
#       define UART_BUFFER_SIZE    64
#endif

//--------------------- private variables:

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
static KTask*   uartTask = 0;
#endif

//--------------------- private functions:

void UART0_IRQHandler(void)
{
    uint32_t status = LPC_UART0->IIR;
    uint8_t data;
    
    //Check if interrupt is pending
    if( (status & 1)==0)
    {
        status = (status >> 1) & 0x07;
        
        //Receive Data Available
        if(status==0x02)
        {
            data = LPC_UART0->RBR;
            writeByteToIOStream(&uartStream,data);
            
#ifdef FIRMWARE_USE_KERNEL_FULL
            irqWakeUpTaskFromIOStream(&uartStream);
#endif
            
#ifdef FIRMWARE_USE_KERNEL_SIMPLE
            if (uartTask!=0)
            {
                postEventToTask(uartTask,(uint32_t)data);
            }
#endif
            
        }
    }
}

//--------------------- public functions:

void powerOnUart0(void)
{
    // enable uart clock
#ifdef MCU_IS_LPC13XX
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,12);
    LPC_SYSCON->USARTCLKDIV = 1;
#endif
}

void powerOffUart0(void)
{
#ifdef MCU_IS_LPC13XX
    CLRBIT(LPC_SYSCON->SYSAHBCLKCTRL,12);
    LPC_SYSCON->USARTCLKDIV = 0;
#endif
}

const Uart * initUart0(void)
{
    initIOStream(&uartStream,uartBuffer,UART_BUFFER_SIZE);
    
    setUartIoCon();
    
    LPC_UART0->FCR = 0x7;   // enable and reset fifos
    LPC_UART0->LCR = 0x83;	// 8 bits; enable divisor latches
    
    setBaudrate();
    
    LPC_UART0->LCR=3;
    
    LPC_UART0->IER = BIT(0);    // enable receive interrupt
    
    
    NVIC_SetPriority(UART0_IRQn, 0x04);
    NVIC_EnableIRQ(UART0_IRQn); // enable NVIC UART0 Interrupt
    
    return &uart0;
}

void sendByteToUart0(uint8_t byte)
{
	while( (LPC_UART0->LSR & BIT(5) ) ==0 );
    
	// test bit-band memory : LSR register is at +0x14 from the base UART memory
    //	while( ( BITBAND( LPC_UART0_BASE + 0x14, 5) )  == 0 );
    
	LPC_UART0->THR=byte;
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

void assignTaskOnUart0(KTask* t)
{
    uartTask = t;
}

#endif
