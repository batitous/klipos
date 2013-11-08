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
#ifndef LIBS_HW_BIT_BAND_H
#define LIBS_HW_BIT_BAND_H

#ifdef __cplusplus
extern "C" {
#endif


//take from lpc datasheet: ARM appendix


#define GET_BITBAND( addr , bitnum )  (( (addr) & 0xF0000000 ) + 0x2000000+ (((addr) & 0xFFFFF) << 5) +(bitnum <<2) )


// convert an device address into a bit-band device address
// for an example, see driver/uart.c

// get bit value from an address
#define BITBAND( addr, bitnum )     *((volatile unsigned long *)(GET_BITBAND(addr,bitnum)))


#ifdef __cplusplus
 }
#endif

#endif
