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


//////////////////////////////////////////////
// WARNING: we manage only lqfp48 gpio chip //
//////////////////////////////////////////////


//----------------------------- get/set/clear pin macro

#define GPIODIR         LPC_GPIO->DIR[0]
#define GPIOGET         LPC_GPIO->PIN[0]
#define GPIOSET(pin)    SETBIT(LPC_GPIO->SET[0],pin)
#define GPIOCLR(pin)    SETBIT(LPC_GPIO->CLR[0],pin)
#define GPIOTOGGLE(pin) SETBIT(LPC_GPIO->NOT[0],pin)


//----------------------------- private functions

uint32_t getIRQNumber(uint32_t reg)
{
    uint32_t i;
    
    for (i=0;i<31;i++)
    {
        if ( ((reg >> i)&0x1) != 0)
        {
            return i;
        }
    }
    return 0;
}


//----------------------------- public functions

void initGpio(void)
{
    // enabe iocon block
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL[0], 13);

    // enable gpio port block
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL[0], 14);
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL[0], 15);
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL[0], 16);
}


void setGpioDirection(GPIO_PIN pin, GPIO_DIR dir)
{
    uint32_t thepin = pin & 0xFFFF;
        
    if(dir==GPIO_OUT)
    {
        SETBIT(GPIODIR,thepin);
    }
    else
    {
        CLRBIT(GPIODIR,thepin);
    }
}

void setGpioValue(GPIO_PIN pin, uint32_t bit)
{
    if(bit!=0)
    {
        GPIOSET(pin);
    }
    else
    {
        GPIOCLR(pin);
    }
}

uint32_t getGpioValue(GPIO_PIN pin)
{
    return (GPIOGET >> pin) & 0x1;
}

void toggleGpio(GPIO_PIN pin)
{
    GPIOTOGGLE(pin);
}

