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


//----------------------------- private object

#define PIN_IRQ_MAX     8

void defaultIrqCallback();

static GpioIrqCallback gpioIrqCallback = defaultIrqCallback;
static uint32_t pinIrqFree = 0;
static GPIO_PIN pinIrq[PIN_IRQ_MAX];


//----------------------------- private functions

static uint32_t getIndexFromGpio(GPIO_PIN pin)
{
    uint32_t i;
    
    for (i=0;i<PIN_IRQ_MAX;i++)
    {
        if (pinIrq[i]==pin)
        {
            return i;
        }
    }
    
    // this function never fail...
    return 0;
}

void defaultIrqCallback(uint32_t gpioIrqEvent, uint32_t gpioIrqEdge)
{
    gpioIrqEvent = 0;
    gpioIrqEdge = 0;
}

void PIN_IRQ_Handler(uint32_t irqSlot)
{
    uint32_t edge = 0;
    GPIO_PIN pin = pinIrq[irqSlot];
    
    if ( ((LPC_GPIO_PIN_INT->RISE>>irqSlot) & 0x1)!=0 )
    {
        edge = GPIO_RISING_EDGE;
    }
    else if ( ((LPC_GPIO_PIN_INT->FALL>>irqSlot) & 0x1)!=0 )
    {
        edge = GPIO_FALLING_EDGE;
    }
    
    gpioIrqCallback(pin,edge);
    
    
    // clear falling/rising detection for this pin
    SETBIT(LPC_GPIO_PIN_INT->IST,irqSlot);
}

void PIN_INT0_IRQHandler(void)
{
    PIN_IRQ_Handler(0);
}

void PIN_INT1_IRQHandler(void)
{
    PIN_IRQ_Handler(1);
}

void PIN_INT2_IRQHandler(void)
{
    PIN_IRQ_Handler(2);
}

void PIN_INT3_IRQHandler(void)
{
    PIN_IRQ_Handler(3);
}

void PIN_INT4_IRQHandler(void)
{
    PIN_IRQ_Handler(4);
}

void PIN_INT5_IRQHandler(void)
{
    PIN_IRQ_Handler(5);
}

void PIN_INT6_IRQHandler(void)
{
    PIN_IRQ_Handler(6);
}

void PIN_INT7_IRQHandler(void)
{
    PIN_IRQ_Handler(7);
}


//----------------------------- public functions

void setGpioIrqCallback(GpioIrqCallback callback)
{
    gpioIrqCallback = callback;
}


void enableGpioIrq(GPIO_PIN pin, GPIO_EDGE edge)
{
    uint32_t thepin = pin & 0xFFFF;
    uint32_t portNumber = GET_GPIO_PORT_NUMBER(pin);
    
    if (pinIrqFree>=PIN_IRQ_MAX)
    {
        return;
    }
    
    if (portNumber==1)
    {
        // datasheet dit de mettre +24, mais l'exemple du datasheet ne donne pas ca... wtf ???
        thepin = 24 + thepin;
    }
    
    // set port number and pin number in the pin interrupt selector
    LPC_SYSCON->PINTSEL[pinIrqFree] = BITS(5,portNumber) | thepin;
    
    
    // select gpio irq as edge sensitive
    CLRBIT(LPC_GPIO_PIN_INT->ISEL,pinIrqFree);
    
    if (edge==GPIO_BOTH_EDGE)
    {
        // todo dont work ?
        // test : can't see the falling/rising edge in irq
        SETBIT(LPC_GPIO_PIN_INT->IENR,pinIrqFree);
        SETBIT(LPC_GPIO_PIN_INT->IENF,pinIrqFree);
    }
    else
    {
        if (edge==GPIO_FALLING_EDGE)
        {
            SETBIT(LPC_GPIO_PIN_INT->IENF,pinIrqFree);
        }
        else
        {
            SETBIT(LPC_GPIO_PIN_INT->IENR,pinIrqFree);
        }
    }
    
    // save the user gpio pin
    pinIrq[pinIrqFree] = pin;
    
    // enable interrupt
    NVIC_EnableIRQ(FLEX_INT0_IRQn + pinIrqFree);
    
    pinIrqFree++;
}

void disableGpioIrq(GPIO_PIN pin)
{
    uint32_t irqIndex = getIndexFromGpio(pin);
    
    SETBIT(LPC_GPIO_PIN_INT->CIENF, irqIndex);
    SETBIT(LPC_GPIO_PIN_INT->CIENR, irqIndex);
    
}


