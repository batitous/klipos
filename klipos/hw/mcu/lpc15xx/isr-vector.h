/*
 The MIT License (MIT)
 
 Copyright (c) 2014 Baptiste Burles
 
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
#ifndef ISR_VECTOR_LP15XX_H
#define	ISR_VECTOR_LP15XX_H

#ifdef	__cplusplus
extern "C" {
#endif

void WDT_IRQHandler(void) ALIAS(IntDefaultHandler);
void BOD_IRQHandler(void) ALIAS(IntDefaultHandler);
void FMC_IRQHandler(void) ALIAS(IntDefaultHandler);
void EEPROM_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA_IRQHandler(void) ALIAS(IntDefaultHandler);
void GINT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void GINT1_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT1_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT2_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT3_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT4_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT5_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT6_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT7_IRQHandler(void) ALIAS(IntDefaultHandler);
void RIT_IRQHandler(void) ALIAS(IntDefaultHandler);
void SCT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void SCT1_IRQHandler(void) ALIAS(IntDefaultHandler);
void SCT2_IRQHandler(void) ALIAS(IntDefaultHandler);
void SCT3_IRQHandler(void) ALIAS(IntDefaultHandler);
void MRT_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART0_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART1_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART2_IRQHandler(void) ALIAS(IntDefaultHandler);
void I2C0_IRQHandler(void) ALIAS(IntDefaultHandler);
void SPI0_IRQHandler(void) ALIAS(IntDefaultHandler);
void SPI1_IRQHandler(void) ALIAS(IntDefaultHandler);
void CAN_IRQHandler(void) ALIAS(IntDefaultHandler);
void USB_IRQHandler(void) ALIAS(IntDefaultHandler);
void USB_FIQHandler(void) ALIAS(IntDefaultHandler);
void USBWakeup_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC0A_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC0B_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC0_THCMP_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC0_OVR_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC1A_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC1B_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC1_THCMP_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC1_OVR_IRQHandler(void) ALIAS(IntDefaultHandler);
void DAC_IRQHandler(void) ALIAS(IntDefaultHandler);
void ACMP0_IRQHandler(void) ALIAS(IntDefaultHandler);
void ACMP1_IRQHandler(void) ALIAS(IntDefaultHandler);
void ACMP2_IRQHandler(void) ALIAS(IntDefaultHandler);
void ACMP3_IRQHandler(void) ALIAS(IntDefaultHandler);
void QEI_IRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_ALARM_IRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_WAKE_IRQHandler(void) ALIAS(IntDefaultHandler);


#ifdef	__cplusplus
}
#endif

#endif	/* ISR_VECTOR_H */

