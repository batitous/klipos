/*
 The MIT License (MIT)
 
 Copyright (c) 2015 Baptiste Burles
 
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
#ifndef LIB_HW_PINMUX_H
#define	LIB_HW_PINMUX_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "pinmux-pins.h"

/** Select input source for SCT0
 * 
 * @param input         Input 0 to 6
 * @param src
 */
extern void assignSCT0InputSource(uint8_t input, SCT0_INMUX_T src);


/** Select input source for SCT1
 * 
 * @param input         Input 0 to 6
 * @param src
 */
extern void assignSCT1InputSource(uint8_t input, SCT1_INMUX_T src);


/** Select input source for SCT2
 * 
 * @param input         Input 0 to 2
 * @param src
 */
extern void assignSCT2InputSource(uint8_t input, SCT2_INMUX_T src);


/** Select input source for SCT3
 * 
 * @param input         Input 0 to 2
 * @param src
 */
extern void assignSCT3InputSource(uint8_t input, SCT3_INMUX_T src);



#ifdef	__cplusplus
}
#endif

#endif	/* PINMUX_H */

