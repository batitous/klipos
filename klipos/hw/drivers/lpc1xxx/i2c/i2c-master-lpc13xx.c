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
#include "i2c-master-common.h"

//-------------------------- private objects

static const I2cMaster i2c0Master = 
{
    sendBufferToI2c0,
    getBufferFromI2c0
};

//-------------------------- public functions

const I2cMaster * initI2c0(I2C_SPEED speed)
{
    UInt32 reg;
    
    // set pinout as scl and sda 
    SETBIT(LPC_IOCON->PIO0_4,0);
    SETBIT(LPC_IOCON->PIO0_5,0);
            
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,5);
    
    // de-assert reset signal for i2c block
    SETBIT(LPC_SYSCON->PRESETCTRL,1);

    I2C_I2CONCLR = 0xFF;

    // how to compute i2c clock bus :
    // i2c frequency = PCLKI2C / (I2C_SCLL + I2C_SCLH)
    
    // 72 Mhz / ( x + y)
    
    switch(speed)
    {
    case I2C_400_KHZ:
            reg = 125;
            break;
    case I2C_100_KHZ:
    default:
            reg = 500;
            break;
    }
    
    I2C_I2SCLL=reg;
    I2C_I2SCLH=reg;

    // active master mode on i2c bus
    I2C_I2CONSET = 0x40;
    
    return &i2c0Master;
}
