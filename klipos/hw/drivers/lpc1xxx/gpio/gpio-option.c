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

extern UInt32 getGpioPortNumber(GPIO_PIN pin);


void setGpioOption(GPIO_PIN pin, bool hysteresis, bool inputInverted, GPIO_MODE mode)
{
    UInt32 thepin = pin & 0xFFFF;
    
    volatile UInt32* ioPin = ((UInt32* ) LPC_IOCON_BASE ) + thepin*4;
    
    if (pin >= GPIO1_0)
    {
        ioPin = ((UInt32* )LPC_IOCON_BASE + 0x060) + thepin*4;
    }
    
    if (hysteresis==true)
    {
        SETBIT(*ioPin,5);
    }
    else
    {
        CLRBIT(*ioPin,5);
    }
    
    
    if (inputInverted==true)
    {
        SETBIT(*ioPin,6);
    }
    else
    {
        CLRBIT(*ioPin,6);
    }
    
    
    CLRBIT(*ioPin,3);
    CLRBIT(*ioPin,4);
    
    *ioPin |= BITS(3, mode);
    
}


