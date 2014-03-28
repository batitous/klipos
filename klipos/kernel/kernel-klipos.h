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
#ifndef KLIPOS_KERNEL_MAIN_H
#define KLIPOS_KERNEL_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../../hw/include/types.h"
    
    
#ifdef FIRMWARE_USE_KERNEL_FULL
#       include "common/include/klist.h"
#       include "common/include/klock.h"
#       include "common/include/kmemory.h"
#       include "common/include/kmemorystack.h"
#       include "full/include/kernel.h"
#       include "full/include/kthread.h"
#       include "full/include/kchannel.h"
#       include "full/include/kevent.h"
#       include "full/include/ktimer.h"
#       include "common/include/kiostream.h"
#endif

#ifdef FIRMWARE_USE_KERNEL_SIMPLE
#       include "common/include/kcommon.h"
#       include "simple/include/kqueue.h"
#       include "simple/include/ktask.h"
#       include "simple/include/ktimer.h"
#endif
    
#ifdef FIRMWARE_DONT_USE_KERNEL
#       include "common/include/kcommon.h"
#endif

#ifdef __cplusplus
 }
#endif

#endif
