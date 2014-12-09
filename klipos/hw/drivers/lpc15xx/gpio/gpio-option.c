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


void setGpioOption(GPIO_PIN pin, GPIO_MODE mode, bool hysteresis, bool inputInverted)
{
    uint32_t index = pin & 0xFFFF;
    
    if (hysteresis==true)
    {
        SETBIT(LPC_IOCON->PIO[0][index],5);
    }
    else
    {
        CLRBIT(LPC_IOCON->PIO[0][index],5);
    }
    
    if (inputInverted==true)
    {
        SETBIT(LPC_IOCON->PIO[0][index],6);
    }
    else
    {
        CLRBIT(LPC_IOCON->PIO[0][index],6);
    }
    
    
    CLRBIT(LPC_IOCON->PIO[0][index],3);
    CLRBIT(LPC_IOCON->PIO[0][index],4);
    
    LPC_IOCON->PIO[0][index] |= BITS(3, mode);
}
