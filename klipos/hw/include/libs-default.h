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
#ifndef LIBS_HW_DEFAULT_H
#define LIBS_HW_DEFAULT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"
#include "core/bit-band.h"
    
#ifdef MCU_IS_LPC17XX
#include "mcu/lpc17xx.h"
#endif
    
#ifdef MCU_IS_LPC13XX
#include "mcu/lpc13xx.h"
#endif
    
#ifdef MCU_IS_LPC15XX
#include "mcu/lpc1549.h"
#endif
    
#ifdef MCU_IS_LPC8XX
#include "mcu/lpc8xx.h"
#endif
    
#include "libc.h"
#include "math-integer.h"
#include "utils.h"
#include "drivers/sleep.h"

#ifdef __cplusplus
 }
#endif

#endif
