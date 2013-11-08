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


#include "../../kernel/include/kernel-klipos.h"

#include "drivers/uart.h"
#include "drivers/rom-iap.h"
#include "drivers/flash.h"
#include "drivers/flash-sst25.h"
#include "drivers/i2c.h"
#include "drivers/i2c-soft.h"
#include "drivers/analog.h"
#include "drivers/gpio.h"
#include "drivers/spi.h"
#include "drivers/timer.h"
#include "drivers/pwm.h"
#include "drivers/sleep.h"
#include "drivers/power.h"
#include "drivers/prs-sensor.h"
#include "drivers/compass.h"
#include "drivers/accelerometer.h"
#include "drivers/magnetometer.h"
#include "drivers/mem-protocol.h"
#include "drivers/rgbled.h"
#include "drivers/byc-board.h"
#include "drivers/eeprom.h"
#include "device.h"
    

#ifdef __cplusplus
 }
#endif

#endif
