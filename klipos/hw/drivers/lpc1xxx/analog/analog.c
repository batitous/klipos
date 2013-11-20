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


//----------------------------- private functions


#ifdef MCU_IS_LPC1311
#       define ANA_CR           LPC_ADC->CR
#       define ANA_RESULT       LPC_ADC->GDR
#       define GET_RESULT(reg)  (reg>>6) & 0x03FF
#endif

#ifdef MCU_IS_LPC1315
#       define ANA_CR           LPC_ADC->CR
#       define ANA_RESULT       LPC_ADC->GDR
#       define GET_RESULT(reg)  (reg>>4) & 0x0FFF
#endif

#ifdef MCU_IS_LPC17XX
#       define ANA_CR           LPC_ADC->ADCR
#       define ANA_RESULT       LPC_ADC->ADGDR
#       define GET_RESULT(reg)  (reg>>4) & 0x0FFF
#endif

//----------------------------- public functions


UInt16 getAnalog(ANALOG_CHANNEL channel)
{
	UInt16 result;
	UInt32 temp;

	// clear previous channel
        CLRBITS(ANA_CR, 0xFF);
	// set channel
	ANA_CR |= channel;
	// start conversion
        SETBIT(ANA_CR,24);

        while( ((temp=ANA_RESULT) & BIT(31) ) == 0);
         
        CLRBIT(ANA_CR,24);

	result = GET_RESULT(temp);
        
	return result;
}
