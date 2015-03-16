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

//--------------------- private functions


#define PINASSIGN_IDX(movable)  (((movable) >> 4))
#define PINSHIFT(movable)       (8 * ((movable) & (0xF)))


//--------------------- public functions


void initSwitchMatrix(void)
{
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL[0],12);
   
    // switchmatrix don't need clear reset ? test failed if decomment next line
    //    CLRBIT(LPC_SYSCON->SYSAHBCLKCTRL[0],12);
}

void assignMovableFunctionToGpio(SwitchMatrixMovableFunction function, GPIO_PIN gpiopin)
{
    uint32_t temp;
    uint32_t pin = ( GET_GPIO_PORT_NUMBER(gpiopin) * 32) + (gpiopin & 0xFFFF);
    
    int pinshift = PINSHIFT(function);
    int regIndex = PINASSIGN_IDX(function);
    
    temp = LPC_SWM->PINASSIGN[regIndex] & (~(0xFF << pinshift));
    LPC_SWM->PINASSIGN[regIndex] = temp | (pin << pinshift);
}

void enableFixedFunction(SwitchMatrixFixexFunction function, bool enable)
{
    uint32_t regOff, pinPos;

    pinPos = ((uint32_t) function) & 0x1F;
    regOff = ((uint32_t) function) >> 7;

    if (enable==true)
    {
        LPC_SWM->PINENABLE[regOff] &= ~(1 << pinPos);
//        CLRBIT(LPC_SWM->PINENABLE[regOff], pinPos);
    }
    else
    {
        LPC_SWM->PINENABLE[regOff] |= (1 << pinPos);
//        SETBIT(LPC_SWM->PINENABLE[regOff], pinPos);
    }
}
