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

#include "../../include/libs-klipos.h"


void initGpio(void)
{
    /* Enable AHB clock to the GPIO domain. */
    LPC_SYSCON->SYSAHBCLKCTRL |=  (1 << 6);
    LPC_SYSCON->PRESETCTRL    &= ~(1 << 10);
    LPC_SYSCON->PRESETCTRL    |=  (1 << 10);
}

void setGpioDirection(GPIO_PIN pin, GPIO_DIR dir)
{
    if (dir==GPIO_IN)
    {
        CLRBIT(LPC_GPIO_PORT->DIR0, pin);
    }
    else
    {
        SETBIT(LPC_GPIO_PORT->DIR0, pin);
        
    }
}

UInt32 getGpioValue(GPIO_PIN pin)
{
   return (LPC_GPIO_PORT->PIN0 >> pin) & 0x1;
}

void setGpioValue(GPIO_PIN pin, UInt32 bit)
{
    if (bit==0)
    {
        LPC_GPIO_PORT->CLR0 = BIT(pin);
    }
    else
    {
        LPC_GPIO_PORT->SET0 = BIT(pin);
    }
}

void toggleGpio(GPIO_PIN pin)
{
    LPC_GPIO_PORT->NOT0 = BIT(pin);
}

