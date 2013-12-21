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
#ifndef ISR_VECTOR_H
#define	ISR_VECTOR_H

#ifdef	__cplusplus
extern "C" {
#endif


void SPI0_IRQHandler(void) ALIAS(IntDefaultHandler);
void SPI1_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART0_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART1_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART2_IRQHandler(void) ALIAS(IntDefaultHandler);
void I2C_IRQHandler(void) ALIAS(IntDefaultHandler);
void SCT_IRQHandler(void) ALIAS(IntDefaultHandler);
void MRT_IRQHandler(void) ALIAS(IntDefaultHandler);
void CMP_IRQHandler(void) ALIAS(IntDefaultHandler);
void WDT_IRQHandler(void) ALIAS(IntDefaultHandler);
void BOD_IRQHandler(void) ALIAS(IntDefaultHandler);
void WKT_IRQHandler(void) ALIAS(IntDefaultHandler);
void PININT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void PININT1_IRQHandler(void) ALIAS(IntDefaultHandler);
void PININT2_IRQHandler(void) ALIAS(IntDefaultHandler);
void PININT3_IRQHandler(void) ALIAS(IntDefaultHandler);
void PININT4_IRQHandler(void) ALIAS(IntDefaultHandler);
void PININT5_IRQHandler(void) ALIAS(IntDefaultHandler);
void PININT6_IRQHandler(void) ALIAS(IntDefaultHandler);
void PININT7_IRQHandler(void) ALIAS(IntDefaultHandler);


#ifdef	__cplusplus
}
#endif

#endif	/* ISR_VECTOR_H */

