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
#ifndef LIB_HW_ANALOG_H
#define LIB_HW_ANALOG_H

#ifdef __cplusplus
extern "C" {
#endif


typedef enum ANALOG_CHANNEL_
{
	ANA0=0x01,      /**< Channel 0 */
	ANA1=0x02,      /**< Channel 1 */
	ANA2=0x04,      /**< Channel 2 */
	ANA3=0x08,      /**< Channel 3 */
	ANA4=0x10,      /**< Channel 4 */
	ANA5=0x20,      /**< Channel 5 */
	ANA6=0x40,      /**< Channel 6 */
	ANA7=0x80,      /**< Channel 7 */
#if defined(MCU_IS_LPC15XX)
        ANA8=0x100,
        ANA9=0x200,
        ANA10=0x400,
        ANA11=0x800,
#endif
} ANALOG_CHANNEL ;


extern void initAnalog(uint32_t analogChannel);

extern uint16_t getAnalog(ANALOG_CHANNEL channel);


#ifdef __cplusplus
 }
#endif

#endif
