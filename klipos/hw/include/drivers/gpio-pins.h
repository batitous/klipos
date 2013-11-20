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
#ifndef LIB_HW_GPIO_PINS_H
#define LIB_HW_GPIO_PINS_H

#ifdef __cplusplus
extern "C" {
#endif

    
/** @brief GPIO Pin names */
typedef enum _GPIO_PIN_
{
    GPIO0_0  = 0x00000,
    GPIO0_1  = 0x00001,
    GPIO0_2  = 0x00002,
    GPIO0_3  = 0x00003,
    GPIO0_4  = 0x00004,
    GPIO0_5  = 0x00005,
    GPIO0_6  = 0x00006,
    GPIO0_7  = 0x00007,
    GPIO0_8  = 0x00008,
    GPIO0_9  = 0x00009,
    GPIO0_10 = 0x0000A,
    GPIO0_11 = 0x0000B,
    GPIO0_12 = 0x0000C,
    GPIO0_13 = 0x0000D,
    GPIO0_14 = 0x0000E,
    GPIO0_15 = 0x0000F,
    GPIO0_16 = 0x00010,
    GPIO0_17 = 0x00011,
    GPIO0_18 = 0x00012,
    GPIO0_19 = 0x00013,
    GPIO0_20 = 0x00014,
    GPIO0_21 = 0x00015,
    GPIO0_22 = 0x00016,
    GPIO0_23 = 0x00017,
    GPIO0_24 = 0x00018,
    GPIO0_25 = 0x00019,
    GPIO0_26 = 0x0001A,
    GPIO0_27 = 0x0001B,
    GPIO0_28 = 0x0001C,
    GPIO0_29 = 0x0001D,
    GPIO0_30 = 0x0001E,
    GPIO0_31 = 0x0001F,
    GPIO1_0  = 0x10000,
    GPIO1_1  = 0x10001,
    GPIO1_2  = 0x10002,
    GPIO1_3  = 0x10003,
    GPIO1_4  = 0x10004,
    GPIO1_5  = 0x10005,
    GPIO1_6  = 0x10006,
    GPIO1_7  = 0x10007,
    GPIO1_8  = 0x10008,
    GPIO1_9  = 0x10009,
    GPIO1_10 = 0x1000A,
    GPIO1_11 = 0x1000B,
    GPIO1_12 = 0x1000C,
    GPIO1_13 = 0x1000D,
    GPIO1_14 = 0x1000E,
    GPIO1_15 = 0x1000F,
    GPIO1_16 = 0x10010,
    GPIO1_17 = 0x10011,
    GPIO1_18 = 0x10012,
    GPIO1_19 = 0x10013,
    GPIO1_20 = 0x10014,
    GPIO1_21 = 0x10015,
    GPIO1_22 = 0x10016,
    GPIO1_23 = 0x10017,
    GPIO1_24 = 0x10018,
    GPIO1_25 = 0x10019,
    GPIO1_26 = 0x1001A,
    GPIO1_27 = 0x1001B,
    GPIO1_28 = 0x1001C,
    GPIO1_29 = 0x1001D,
    GPIO1_30 = 0x1001E,
    GPIO1_31 = 0x1001F,
    GPIO2_0  = 0x20000,
    GPIO2_1  = 0x20001,
    GPIO2_2  = 0x20002,
    GPIO2_3  = 0x20003,
    GPIO2_4  = 0x20004,
    GPIO2_5  = 0x20005,
    GPIO2_6  = 0x20006,
    GPIO2_7  = 0x20007,
    GPIO2_8  = 0x20008,
    GPIO2_9  = 0x20009,
    GPIO2_10 = 0x2000A,
    GPIO2_11 = 0x2000B,
    GPIO2_12 = 0x2000C,
    GPIO3_0  = 0x40000, 
    GPIO3_1  = 0x40001,
    GPIO3_2  = 0x40002,
    GPIO3_3  = 0x40003,
    GPIO3_4  = 0x40004,
    GPIO3_5  = 0x40005
} GPIO_PIN;


#ifdef __cplusplus
 }
#endif

#endif