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
#include "../../../hw/include/libs-klipos.h"

//----------------------------- private functions


// Manage the input/output interrupt for the KEvent manager
void keventGpioIrqCallback(uint32_t event, uint32_t edge)
{
    postEventFromIrq(KEVENT_GPIO_MASK | event, edge );
}


//----------------------------- public functions

void enableEventOnGpio(GPIO_PIN pin, GPIO_IRQ_TYPE edge, KEventManager *manager, KEventCallback callback)
{
    if ( registerEvent( manager, KEVENT_GPIO_MASK | pin, callback, 0) == false )
    {
        return;
    }
    
    setGpioIrqCallback(keventGpioIrqCallback);
        
    setGpioDirection(pin,GPIO_IN);
    enableGpioIrq(pin,edge);
    
}

