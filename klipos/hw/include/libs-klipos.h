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
#ifndef LIBS_HW_H
#define LIBS_HW_H

#ifdef __cplusplus
extern "C" {
#endif


#include "libs-default.h"

    
#include "../../kernel/kernel-klipos.h"

#include "drivers/sleep.h"
#include "drivers/i2c.h"
    
#if !defined(MCU_IS_LPC8XX)
#       include "drivers/uart.h"
#if     !defined(MCU_IS_LPC15XX)
#               include "drivers/timer.h"
#       endif
#       include "drivers/pwm.h"
#       include "drivers/i2c-soft.h"
#else
#       include "drivers/lpc8xx/uart.h"
#endif 
        
#include "drivers/gpio.h"
#include "drivers/gpio-irq.h"
#include "drivers/analog.h"
#include "drivers/i2c-master.h"
#include "drivers/iap.h"
#include "drivers/flash.h"
#include "drivers/eeprom.h"
#include "drivers/watchdog.h"
#include "drivers/spi.h"
#include "drivers/mem-protocol.h"

#if defined(MCU_IS_LPC15XX)
#       include "drivers/lpc15xx/switchmatrix.h"
#       include "drivers/lpc15xx/dac.h"
#       include "drivers/lpc15xx/timer.h"
#endif
    
#ifdef __cplusplus
 }
#endif

#endif
