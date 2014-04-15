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

#ifdef MCU_IS_LPC1311
void WAKEUP_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void I2C_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void TIMER_16_0_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void TIMER_16_1_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void TIMER_32_0_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void TIMER_32_1_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void SSP0_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void UART0_IRQHandler(void) ALIAS(IntDefaultHandler);
void USB_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void USB_FIQn(void) ALIAS(IntDefaultHandler);
void ADC_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void WDT_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void BOD_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void RESERVED_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void EINT3_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void EINT2_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void EINT1_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void EINT0_IRQn_Handler(void) ALIAS(IntDefaultHandler);
#endif



#ifdef MCU_IS_LPC1315
void PIN_INT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT1_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT2_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT3_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT4_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT5_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT6_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT7_IRQHandler(void) ALIAS(IntDefaultHandler);
void GINT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void GINT1_IRQHandler(void) ALIAS(IntDefaultHandler);
void RESERVED_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void SSP1_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void I2C_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void TIMER_16_0_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void TIMER_16_1_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void TIMER_32_0_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void TIMER_32_1_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void SSP0_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void UART0_IRQHandler(void) ALIAS(IntDefaultHandler);
void USB_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void USB_FIQn(void) ALIAS(IntDefaultHandler);
void ADC_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void WDT_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void BOD_IRQn_Handler(void) ALIAS(IntDefaultHandler);
#endif


#ifdef	__cplusplus
}
#endif

#endif	/* ISR_VECTOR_H */

