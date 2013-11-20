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

extern LPC_GPIO_TypeDef * getGpioPort(GPIO_PIN pin);

extern UInt32 getIRQNumber(UInt32 reg);

//----------------------------- private object

void defaultIrqCallback();

static GpioIrqCallback gpioIrqCallback = defaultIrqCallback;


//----------------------------- private functions

void defaultIrqCallback(UInt32 gpioIrqEvent, UInt32 gpioIrqEdge)
{
    gpioIrqEvent = 0;
    gpioIrqEdge = 0;
}

UInt32 getEventFromGpio(LPC_GPIO_TypeDef * gpio, UInt32 * edge)
{
    UInt32 thepin = getIRQNumber(gpio->MIS);
        
    //if( ((gpio->RIS >> thepin)&0x1)!=0)
    if( ((gpio->DATA >> thepin)&0x1)!=0)
    {
        // gpio high: rising edge
        *edge = GPIO_RISING_EDGE;
    }
    else
    {
        //gpio low
        *edge = GPIO_FALLING_EDGE;
    }

    //clear irq
    SETBIT(gpio->IC,thepin);
    __NOP();
    __NOP();

    return thepin;
}

void IRQ_Handler(UInt32 eventPort, LPC_GPIO_TypeDef * gpio)
{
    UInt32 edge = 0;
    UInt32 event = getEventFromGpio(gpio, &edge) | eventPort;

    gpioIrqCallback(event,edge);
    
}

void EINT3_IRQn_Handler(void)
{
    IRQ_Handler(GPIO_PORT3,LPC_GPIO3);
}

void EINT2_IRQn_Handler(void)
{
    IRQ_Handler(GPIO_PORT2,LPC_GPIO2);
}

void EINT1_IRQn_Handler(void)
{
    IRQ_Handler(GPIO_PORT1,LPC_GPIO1);
}

void EINT0_IRQn_Handler(void)
{
    IRQ_Handler(GPIO_PORT0,LPC_GPIO0);
}

//----------------------------- public functions

void setGpioIrqCallback(GpioIrqCallback callback)
{
    gpioIrqCallback = callback;
}


void enableGpioIrq(GPIO_PIN pin, GPIO_EDGE edge)
{
    LPC_GPIO_TypeDef * gpio = getGpioPort(pin);
    UInt32 thepin = pin & 0xFFFF;
    

    if(edge==GPIO_BOTH_EDGE)
    {
        SETBIT(gpio->IBE,thepin);
    }
    else
    {
        CLRBIT(gpio->IBE,thepin);
        
        // irq sense: edge (and not level)
        CLRBIT(gpio->IS,thepin);
        
        if(edge==GPIO_FALLING_EDGE)
        {
            CLRBIT(gpio->IEV,thepin);
        }
        else
        {
            SETBIT(gpio->IEV,thepin);
        }
    }

    // enable IRQ
    SETBIT(gpio->IE,thepin);
        
    switch(pin & 0xFFFF0000)
    {
        case GPIO_PORT0:
            NVIC_SetPriority(EINT0_IRQn, 0x05);
            NVIC_EnableIRQ(EINT0_IRQn);
            break;
        case GPIO_PORT1:
            NVIC_SetPriority(EINT1_IRQn, 0x06);
            NVIC_EnableIRQ(EINT1_IRQn);
            break;
        case GPIO_PORT2:
            NVIC_SetPriority(EINT2_IRQn, 0x07);
            NVIC_EnableIRQ(EINT2_IRQn);
            break;
        case GPIO_PORT3:
            NVIC_SetPriority(EINT3_IRQn, 0x08);
            NVIC_EnableIRQ(EINT3_IRQn);
            break;
    }
}

void disableGpioIrq(GPIO_PIN pin)
{
    LPC_GPIO_TypeDef * gpio = getGpioPort(pin);
    UInt32 thepin = pin & 0xFFFF;
    
    // disable IRQ
    CLRBIT(gpio->IE,thepin);
    
}
