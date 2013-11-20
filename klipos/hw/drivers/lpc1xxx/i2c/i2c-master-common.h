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

#ifdef MCU_IS_LPC13XX
#       define I2C_I2CONSET    LPC_I2C->CONSET
#       define I2C_I2CONCLR    LPC_I2C->CONCLR
#       define I2C_I2STAT      LPC_I2C->STAT
#       define I2C_I2DAT       LPC_I2C->DAT
#       define I2C_I2SCLL      LPC_I2C->SCLL
#       define I2C_I2SCLH      LPC_I2C->SCLH
#endif

#ifdef MCU_IS_LPC17XX
#       define I2C_I2CONSET    LPC_I2C0->I2CONSET
#       define I2C_I2CONCLR    LPC_I2C0->I2CONCLR
#       define I2C_I2STAT      LPC_I2C0->I2STAT
#       define I2C_I2DAT       LPC_I2C0->I2DAT
#       define I2C_I2SCLL      LPC_I2C0->I2SCLL
#       define I2C_I2SCLH      LPC_I2C0->I2SCLH
#endif
